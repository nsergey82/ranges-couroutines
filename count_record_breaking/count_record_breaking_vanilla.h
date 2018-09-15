#ifndef RANGES_COUNT_RECORD_BREAKING_VANILLA_H
#define RANGES_COUNT_RECORD_BREAKING_VANILLA_H

#include "count_helpers.h"

int count_breaking_record_vanilla(unsigned n) {
    const int low = 1;
    const int high = 9999;
    ScoresGen<int> gen(low, high);
    auto least = high + 1;
    auto best = low - 1;
    unsigned bestcnt = 0;
    unsigned leastcnt = 0;
    for(unsigned i = 0; i < n; ++i) {
        auto v = gen();
        if(v > best) {
            ++bestcnt;
            best = v;
        }
        else if(v < least) {
            ++leastcnt;
            least = v;
        }
    }
    return leastcnt + bestcnt;
}
#endif //RANGES_COUNT_RECORD_BREAKING_VANILLA_H
