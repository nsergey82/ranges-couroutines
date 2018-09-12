#ifndef FZBZ_RX_H
#define FZBZ_RX_H

#include <iostream>
#include "rx.hpp"

namespace rx {

using namespace rxcpp;
using namespace rxcpp::sources;
using namespace rxcpp::operators;
using namespace rxcpp::util;


auto intseq = [](unsigned limit){
    return rxcpp::observable<>::range(1, limit);
};

void test() {
    auto marked_stream = intseq(5).publish();
    marked_stream.subscribe([](unsigned v){ std::cout << "1: " << v << '\n';}, [](){});
    marked_stream.subscribe([](unsigned v){ std::cout << "2: " << v << '\n';}, [](){});
    // Start emitting
    marked_stream.connect();
}



}
#endif
