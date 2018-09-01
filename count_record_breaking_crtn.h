#ifndef COUNT_BAD_GOOD_H
#define COUNT_BAD_GOOD_H

#include "crtn_helpers.h"
#include <deque>
#include <vector>
#include <random>

namespace crtn {
//template<typename T=int>
//pull_t<T> _cin_values(unsigned count) {
//    return pull_t<T>(
//            [count](push_t<T> & sink){ //capture by value
//                for(unsigned i=0; i<count; ++i) {
//                    T val;
//                    std::cin >> val;
//                    sink(val);
//
//                }
//            });
//}

template<typename T=int>
pull_t<T> rnd_values(unsigned count, T low, T high) {
    return pull_t<T>(
            [count, low, high](push_t<T> &sink) {
                std::mt19937 mtgen(1);
                std::uniform_int_distribution<T> dis(low, high);
                for (unsigned i = 0; i < count; ++i) {
                    sink(dis(mtgen));
                }
            });
}

void best(int first, push_t<int> &sink, pull_t<int> &source) {
    int best = first;
    unsigned count = 0;
    for (auto v : source) {
        if (v > best) {
            best = v;
            ++count;
            sink(count);
        }
    }
}

int get_last(pull_t<int> &source) {
    int val = 0;
    for (auto v : source) {
        val = v;
    }
    return val;
}

void last(push_t<int> &sink, pull_t<int> &source) {
    sink(get_last(source));
}


void neg(push_t<int> &sink, pull_t<int> &source) {
    for (auto v : source)
        sink(-1 * v);
}

//         __ best _________ last
//        /
// tee(in)
//        \__ neg __ best __ last
//
// 3 4 21 36 10 28 35 5 24 42 --> 4 0
// 10 5 20 20 4 5 2 25 1 --> 2 4
//
int count_good_bad(unsigned n) {
    const int first = 0;

    auto input_gen = rnd_values(n, 1, 9999);

    std::vector<std::deque<int>> queues(2);
    auto gen_pair = tee(input_gen, queues);

    // in docu. boost uses std::bind here, but for me it only works with lambdas
    pull_t<int> best_gen(
            [&](push_t<int> &sink) { best(first, sink, gen_pair.first); });
    pull_t<int> last_best_gen([&](push_t<int> &sink) { last(sink, best_gen); });

    pull_t<int> neg_gen([&](push_t<int> &sink) { neg(sink, gen_pair.second); });
    pull_t<int> least_gen(
            [&](push_t<int> &sink) { best(-1 * first, sink, neg_gen); });
    pull_t<int> last_least_gen(
            [&](push_t<int> &sink) { last(sink, least_gen); });

    //collect the results
    return last_best_gen.get() + last_least_gen.get();
}
}

#endif
