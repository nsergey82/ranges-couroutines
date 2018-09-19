#ifndef RANGES__RNG_H
#define RANGES__RNG_H

#include "tee_rng3.h"
#include "count_helpers.h"


struct GenRndRng : ranges::view_facade<GenRndRng> {
private:
    friend struct ranges::range_access;
    ScoresGen<int,true>* rgen;
    int value;

    auto read()  const { return value;  }
    bool equal(const GenRndRng &that) const { return false; }
    bool equal(ranges::default_sentinel) const { return false; }
    void next() { value = (*rgen)(); }
    void prev() {}
public:
    GenRndRng(ScoresGen<int,true>* g = nullptr) : rgen(g), value((*rgen)()) {
    }
};

unsigned test(unsigned limit) {
    using namespace ranges;
    ScoresGen<int,true> rgen(low, high);

    std::deque<int> q1;
    std::deque<int> q2;
    TeeStore<GenRndRng> teestore(GenRndRng(&rgen), q1, q2);
    TeeRng<GenRndRng> left(&teestore, 0);
    TeeRng<GenRndRng> right(&teestore, 1);
    RANGES_FOR(auto v, left | view::take(limit-1)) {
        std::cout << v << std::endl;
   }
   return 0;
}

#endif //RANGES_RNG_H
