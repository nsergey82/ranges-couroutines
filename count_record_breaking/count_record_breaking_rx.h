#ifndef CNT_RX_H
#define CNT_RX_H

#include "rx.hpp"

namespace rx {

using namespace rxcpp;
using namespace rxcpp::sources;
using namespace rxcpp::operators;
using namespace rxcpp::util;


auto intseq = [](unsigned limit){
    return rxcpp::observable<>::range(1, limit);
};


}
#endif
