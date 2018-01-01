#ifndef FZBZ_RX_H
#define FZBZ_RX_H

#include "rx.hpp"
#include "fzbz_helpers.h"

namespace rx {

using namespace rxcpp;
using namespace rxcpp::sources;
using namespace rxcpp::operators;
using namespace rxcpp::util;


auto intseq = [](unsigned limit){
    return rxcpp::observable<>::range(1, limit)
            .map(helper::mark_divisibles<15, int>)
            .map(helper::mark_divisibles<5, int>)
            .map(helper::mark_divisibles<3, int>);
};

std::vector<unsigned> fizbuz(unsigned limit) {
    auto marked_stream = intseq(limit-1);
    std::vector<unsigned> vec;
    vec.reserve(limit);
    marked_stream.subscribe([&vec](unsigned v){ vec.push_back(v);}, [](){});
    return vec;
}

size_t fizbuz_str(unsigned limit) {
    auto str_stream = intseq(limit-1).map(helper::_str_g);
    size_t acc = 0;
    str_stream.subscribe([&acc](const std::string& v){ acc ^= v.size();},
                         [](){});
    return acc;
}


}
#endif
