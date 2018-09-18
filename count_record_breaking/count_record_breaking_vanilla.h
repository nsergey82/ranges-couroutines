#ifndef RANGES_COUNT_RECORD_BREAKING_VANILLA_H
#define RANGES_COUNT_RECORD_BREAKING_VANILLA_H

#include "count_helpers.h"
#include <iostream>

unsigned count_breaking_record_vanilla(unsigned n) {
    ScoresGen<int> gen(low, high);
    RecordCounter<int> best(low-1);
    RecordCounter<int> worst(-1*(high+1));
    for(unsigned i = 0; i < n; ++i) {
        auto v = gen();
        best.process(v);
        worst.process(-1 * v);
    }
    return best.get_count() + worst.get_count();
}
#endif //RANGES_COUNT_RECORD_BREAKING_VANILLA_H
