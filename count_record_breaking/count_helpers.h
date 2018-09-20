#ifndef RANGES_COUNT_HELPERS_H
#define RANGES_COUNT_HELPERS_H
#include <random>
#include <iostream>

constexpr int low = 1;
constexpr int high = 9999;

template<typename T, bool shouldPrint=false>
class ScoresGen {
    std::mt19937 mtgen;
    std::uniform_int_distribution<T> dis;
public:
    ScoresGen(T low = 0, T high = 100, unsigned seed = 1234) : mtgen(seed), dis(low, high)
    {}

    T operator()() {
        if(shouldPrint) {
            T v = dis(mtgen);
            std::cout << v << std::endl;
            return v;
        }
        return dis(mtgen);
    }
};

template<typename T>
class RecordCounter {
    T best;
    unsigned long count;
public:
    explicit RecordCounter(const T& smallerThanValid)
    : best(smallerThanValid), count(0) {}

    unsigned long process(const T& value) {
        if(value > best) {
            ++count;
            best = value;
            return count;
        }
        return 0u;
    }

    unsigned long get_count() const { return count; }
};
#endif //RANGES_COUNT_HELPERS_H
