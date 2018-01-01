#ifndef FZBZ_H
#define FZBZ_H

#include <vector>
#include "crtn_helpers.h"
#include "fzbz_helpers.h"

namespace crtn {
void naturals_g(unsigned limit, push_t<unsigned> &sink) {
    for (unsigned i = 1; i < limit; ++i)
        sink(i);
}

template<unsigned mmod>
void ifmod(push_t<unsigned> &sink, pull_t<unsigned> &source) {
    for (auto v : source)
        sink(helper::mark_divisibles<mmod>(v));
}

// convert numbers and marked numbers
void str_g(push_t<std::string> &sink, pull_t<unsigned> &source) {
    for (auto v : source)
        sink(helper::_str_g(v));
}

std::vector<unsigned> fizbuz(unsigned limit) {
    pull_t<unsigned> naturals_gen(
            [&](push_t<unsigned> &s) { naturals_g(limit, s); });
    auto gen_uptr = naturals_gen | ifmod<15> | ifmod<3> | ifmod<5>;

    std::vector<unsigned> vec;
    vec.reserve(limit);
    for (auto v : *gen_uptr)
        vec.push_back(v);
    return vec;
}


size_t fizbuz_str(unsigned limit) {
    pull_t<unsigned> naturals_gen(
            [&](push_t<unsigned> &s) { naturals_g(limit, s); });
    auto gen_uptr = naturals_gen | ifmod<15> | ifmod<3> | ifmod<5>;
    auto str_gen = chain<std::string>(*gen_uptr, str_g);

    size_t acc = 0;
    for (auto v : str_gen)
        acc ^= v.size();
    return acc;
}

}
#endif
