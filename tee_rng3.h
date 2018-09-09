#ifndef RANGES_TEE_RNG3_H
#define RANGES_TEE_RNG3_H

#include <range/v3/all.hpp>
#include <deque>
#include <vector>

template<typename Source>
class TeeStore {
    Source source;
    using It = decltype(source.begin());
    It begin;

    std::deque<int>* const queue1;
    std::deque<int>* const queue2;

    int get(std::deque<int>* const queue) const {
        auto val = queue->back();
        queue->pop_back();
        return val;
    }

    void next(std::deque<int>* const queue) {
        if(queue->empty()) {
            auto val = *begin;
            ++begin;
            queue1->push_front(val);
            queue2->push_front(val);
        }
    }

public:
    explicit TeeStore(Source&& s, std::deque<int>& q1, std::deque<int>& q2 )
            : source(std::move(s)), begin(s.begin()), queue1(&q1), queue2(&q2) {}


    auto get(int index) const {
        auto val = get(index ? queue2 : queue1);
        assert(has(index));
        return val;
    }

    void next(int index) {
        next(index ? queue2 : queue1);
    }

    bool has(int index) const { return true; }
};



template<typename Source>
struct TeeRng : ranges::view_facade<TeeRng<Source>> {
private:
    friend struct ranges::range_access;
    TeeStore<Source>* tee;
    int index;

    auto read()  const { return tee->get(index);  }
    bool equal(const TeeRng &that) const { return !tee->has(index); }
    bool equal(ranges::default_sentinel) const { return !tee->has(index); }
    void next() { tee->next(index); }
    void prev() {}
public:
    TeeRng(TeeStore<Source>* t = nullptr, int id = 0) : tee(t), index(id) {
        tee->next(0);
    }
};

#endif //RANGES_TEE_RNG3_H
