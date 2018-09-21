#ifndef RANGES__RNG_H
#define RANGES__RNG_H

#include "tee_rng3.h"
#include "count_helpers.h"


struct GenRndRng : ranges::view_facade<GenRndRng> {
private:
    friend struct ranges::range_access;
    ScoresGen<int>* rgen;
    int value;

    auto read()  const { return value;  }
    bool equal(const GenRndRng &that) const { return false; }
    bool equal(ranges::default_sentinel) const { return false; }
    void next() { value = (*rgen)(); }
    void prev() {}
public:
    GenRndRng(ScoresGen<int>* g = nullptr) : rgen(g), value((*rgen)()) {
    }
};

unsigned count_breaking_record_rng_seq(unsigned limit) {
    using namespace ranges;
    ScoresGen<int> rgen(low, high);

    std::deque<int> q1;
    std::deque<int> q2;
    TeeStore<GenRndRng> teestore(GenRndRng(&rgen), q1, q2);
    TeeRng<GenRndRng> left(&teestore, 0);
    TeeRng<GenRndRng> right(&teestore, 1);

    RecordCounter<int> best(low-1);
    auto best_trn = [&best](int v) { return best.process(v); };
    RecordCounter<int> worst(-1 * (high+1));
    auto worst_trn = [&worst](int v) { return worst.process(-1 * v); };

    auto notzero = [](unsigned long v){ return v > 0; };

    return ranges::count_if(right | view::take(limit) | view::transform(worst_trn), notzero) +
           ranges::count_if(left  | view::take(limit) | view::transform(best_trn), notzero);
}

unsigned count_breaking_record_rng_par(unsigned limit) {
    using namespace ranges;
    ScoresGen<int> rgen(low, high);

    std::deque<int> q1;
    std::deque<int> q2;
    TeeStore<GenRndRng> teestore(GenRndRng(&rgen), q1, q2);
    TeeRng<GenRndRng> left(&teestore, 0);
    TeeRng<GenRndRng> right(&teestore, 1);

    //
    RecordCounter<int> best(low-1);
    RecordCounter<int> worst(-1 * (high+1));
    auto trn = [&best, &worst](std::tuple<int,int> v) {
        return worst.process(-1 * std::get<1>(v)) + best.process(std::get<0>(v)); };

    auto dummy = ranges::accumulate(view::zip(left, right) | view::take(limit) | view::transform(trn), 0u);

    return best.get_count() + worst.get_count();
}
#endif //RANGES_RNG_H
