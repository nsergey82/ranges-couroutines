#ifndef RANGES_COUNT_HELPERS_H
#define RANGES_COUNT_HELPERS_H
#include <random>

template<typename T>
class ScoresGen {
    std::mt19937 mtgen;
    std::uniform_int_distribution<T> dis;
public:
    ScoresGen(T low, T high, unsigned seed = 1234) : mtgen(seed), dis(low, high)
    {}

    T operator()() {
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
        return 0;
    }
};
#endif //RANGES_COUNT_HELPERS_H
