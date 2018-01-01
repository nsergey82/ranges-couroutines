#ifndef FZBZ_VN_H
#define FZBZ_VN_H

#include "fzbz_helpers.h"
#include <algorithm>

namespace vanilla {

std::vector<unsigned> fizbuz_mod(unsigned limit) {
    std::vector<unsigned> vec;
    vec.reserve(limit);

    for(unsigned i = 1; i < limit; ++i) {
        if (i % 15 == 0) {
            vec.push_back(15 + helper::marker);
        } else if (i % 5 == 0) {
            vec.push_back(5 + helper::marker);
        } else if (i % 3 == 0) {
            vec.push_back(3 + helper::marker);
        } else {
            vec.push_back(i);
        }
    }
    return vec;
}

std::vector<unsigned> fizbuz_transform(unsigned limit) {
    std::vector<unsigned> vec;
    vec.resize(limit-1);
    for(unsigned i = 1; i < limit; ++i)
        vec[i-1] = i;

    std::transform(//std::execution::par, <-- will this balance the slow modulo?
                   vec.begin(), vec.end(), vec.begin(), [](unsigned i){
        if (i % 15 == 0) {
            return 15 + helper::marker;
        } else if (i % 5 == 0) {
            return 5 + helper::marker;
        } else if (i % 3 == 0) {
            return 3 + helper::marker;
        } else {
            return i;
        }
    });
    return vec;
}


std::vector<unsigned> fizbuz(unsigned limit) {
    std::vector<unsigned> vec;
    vec.reserve(limit);

    //lookup based, no modulo operations, just additions and jump tables
                      // 0123456789abcdef
    const auto encode = "x..f.bf..fb.f..d";
    for(unsigned i = 1, m = 0; i < limit; ++i) {
        ++m;
        switch(encode[m]) {
            case '.':
                vec.push_back(i);
                break;
            case 'd':
                m = 0;
                vec.push_back(15 + helper::marker);
                break;
            case 'f':
                vec.push_back(3 + helper::marker);
                break;
            case 'b':
                vec.push_back(5 + helper::marker);
                break;
        };
    }
    return vec;
}


}
#endif
