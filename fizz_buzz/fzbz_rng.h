#ifndef FZBZ_RNG_H
#define FZBZ_RNG_H

#include <range/v3/all.hpp>
#include <boost/range/adaptor/transformed.hpp>
#include <boost/range/irange.hpp>

#include "fzbz_helpers.h"

namespace rng {

auto intseq = [](){
    using namespace ranges;
    return view::ints(1) |
                view::transform(helper::mark_divisibles<15, int>) |
                view::transform(helper::mark_divisibles<5, int>) |
                view::transform(helper::mark_divisibles<3, int>);
};

std::vector<unsigned> fizbuz(unsigned limit) {
    using namespace ranges;
    auto marked_stream = intseq();

    std::vector<unsigned> vec;
    vec.reserve(limit);
    RANGES_FOR(auto v, marked_stream | view::take(limit-1)) {
        vec.push_back(v);
    }
    return vec;
}


size_t fizbuz_str(unsigned limit) {
    using namespace ranges;
    auto marked_stream = intseq() | view::transform(helper::_str_g);

    size_t sum = 0;
    RANGES_FOR(auto v, marked_stream | view::take(limit-1)) {
        sum ^= v.size();
    }
    return sum;
}
}

namespace brng {

auto intseq = [](unsigned limit){
    using namespace boost::adaptors;
    return boost::irange(1u, limit) |
            transformed(helper::mark_divisibles<15, int>) |
            transformed(helper::mark_divisibles<5, int>) |
            transformed(helper::mark_divisibles<3, int>);
};

std::vector<unsigned> fizbuz(unsigned limit) {
    auto marked_stream = intseq(limit);

    std::vector<unsigned> vec;
    vec.reserve(limit);
    for(auto v : marked_stream)
        vec.push_back(v);
    return vec;
}

size_t fizbuz_str(unsigned limit) {
    using namespace boost::adaptors;
    auto marked_stream = intseq(limit) | transformed(helper::_str_g);

    size_t acc = 0;
    for(auto v : marked_stream) {
        acc ^= v.size();
    }
    return acc;
}


}
#endif
