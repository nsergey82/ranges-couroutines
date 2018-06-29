#ifndef COUNT_BAD_GOOD_H
#define COUNT_BAD_GOOD_H

#include "crtn_helpers.h"
#include <deque>
#include <vector>

template<typename T=int>
pull_t<T> _cin_values(unsigned count) {
    return pull_t<T>(
            [count](push_t<T> & sink){ //capture by value
                for(unsigned i=0; i<count; ++i) {
                    T val;
                    std::cin >> val;
                    sink(val);

                }
            });
}

void best(int first, push_t<int>& sink, pull_t<int>& source) {
    int best = first;
    unsigned count = 0;
    for(auto v : source) {
        if (v > best) {
            best = v;
            ++count;
            sink(count);
        }
    }
}

void last(push_t<int>& sink, pull_t<int>& source) {
    int val = 0;
    for(auto v : source) {
        val = v;
    }
    sink(val);
}



// use outside owned queues object to persist streamed values
void _tee(push_t<int>& sink, pull_t<int>& source,
          unsigned index, std::vector<std::deque<int>>& queues)
{
    while(true) {
        if(queues[index].empty()) {
            auto val = source.get();
            source();
            queues[0].push_front(val);
            queues[1].push_front(val);
        }

        auto val = queues[index].back();
        queues[index].pop_back();
        sink(val);
        if(!source && queues[index].empty())
            break;
    }
};

// create two pull coroutines that utilize the queues to persist streaming data from single source
std::pair<pull_t<int>, pull_t<int>> tee(pull_t<int>& source, std::vector<std::deque<int>>& queues) {
    return std::make_pair(
            pull_t<int>([&](push_t<int>& sink){_tee(sink, source, 0, queues);}),
            pull_t<int>([&](push_t<int>& sink){_tee(sink, source, 1, queues);})
    );
};

void neg(push_t<int>& sink, pull_t<int>& source) {
    for(auto v : source)
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
void count_good_bad(unsigned n) {
    const int first = [](){int v; std::cin >> v; return v;}();

    auto input_gen = _cin_values<int>(n-1);

    std::vector<std::deque<int>> queues(2);
    auto gen_pair = tee(input_gen, queues);

    // in docu. boost uses std::bind here, but for me it only works with lambdas
    pull_t<int> best_gen([&](push_t<int>& sink){ best(first, sink, gen_pair.first);});
    pull_t<int> last_best_gen([&](push_t<int>& sink){ last(sink, best_gen);});

    pull_t<int> neg_gen([&](push_t<int>& sink){ neg(sink, gen_pair.second);});
    pull_t<int> least_gen([&](push_t<int>& sink){ best(-1 * first, sink, neg_gen);});
    pull_t<int> last_least_gen([&](push_t<int>& sink){ last(sink, least_gen);});

    for (auto i: last_best_gen) std::cout << i << ' ';
    for (auto i: last_least_gen) std::cout << i << ' ';
    std::cout << std::endl;
}


#endif
