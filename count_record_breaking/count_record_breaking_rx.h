#ifndef CNT_RX_H
#define CNT_RX_H

#include "rx.hpp"
#include "count_helpers.h"

namespace rx {

using namespace rxcpp;
using namespace rxcpp::sources;
using namespace rxcpp::operators;
using namespace rxcpp::util;


auto get_rnd_source(unsigned n, int low, int high) {
    return rxcpp::observable<>::create<int>(
            [n, low, high](rxcpp::subscriber<int> s) {
                ScoresGen<int> gen(low, high);
                for (int i = 0; i < n; ++i) {
                    if (!s.is_subscribed()) // Stop emitting if nobody is listening
                        break;
                    s.on_next(gen());
                }
                s.on_completed();
            });
}

unsigned count_breaking_record_rx(unsigned n) {
    auto src = get_rnd_source(n, low, high).publish();

    RecordCounter<int> best(low-1);
    auto left = [&best](int v) { return best.process(v);};

    RecordCounter<int> worst(-1 * (high+1));
    auto right = [&worst](int v) { return worst.process(-1 * v);};

    auto cnt1 = src.map(left).filter([](int v){return v > 0;}).distinct().count();
    auto cnt2 = src.map(right).filter([](int v){return v > 0;}).distinct().count();

    unsigned long c1 = 0;
    unsigned long c2 = 0;
    cnt1.subscribe([&](unsigned c) { c1 = c;});
    cnt2.subscribe([&](unsigned c) { c2 = c;});
    src.connect();

    return c1+c2;
}


}
#endif
