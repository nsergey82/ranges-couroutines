#include "fizz_buzz/fzbz_crtn.h"
#include "fizz_buzz/fzbz_rng.h"
#include "fizz_buzz/fzbz_rx.h"
#include "fizz_buzz/fzbz_vanilla.h"

#include "count_record_breaking/count_record_breaking_crtn.h"
#include "count_record_breaking/count_record_breaking_rx.h"
#include "count_record_breaking/count_record_breaking_vanilla.h"

#include "benchmark/include/benchmark/benchmark.h"


using std::cout;

static void BM_crtn_fizbz(benchmark::State &state) {
    for (auto _ : state) {
        crtn::fizbuz(state.range(0));
    }
}

static void BM_rng_fizbz(benchmark::State &state) {
    for (auto _ : state) {
        rng::fizbuz(state.range(0));
    }
}

static void BM_brng_fizbz(benchmark::State &state) {
    for (auto _ : state) {
        brng::fizbuz(state.range(0));
    }
}

static void BM_rx_fizbz(benchmark::State &state) {
    for (auto _ : state) {
        rx::fizbuz(state.range(0));
    }
}

static void BM_vn_fizbz(benchmark::State &state) {
    for (auto _ : state) {
        vanilla::fizbuz(state.range(0));
    }
}

static void BM_vn_fizbz_mod(benchmark::State &state) {
    for (auto _ : state) {
        vanilla::fizbuz_mod(state.range(0));
    }
}

static void BM_vn_fizbz_transform(benchmark::State &state) {
    for (auto _ : state) {
        vanilla::fizbuz_transform(state.range(0));
    }
}


static void BM_crtn_fizbz_s(benchmark::State &state) {
    for (auto _ : state) {
        crtn::fizbuz_str(state.range(0));
    }
}

static void BM_rng_fizbz_s(benchmark::State &state) {
    for (auto _ : state) {
        rng::fizbuz_str(state.range(0));
    }
}

static void BM_brng_fizbz_s(benchmark::State &state) {
    for (auto _ : state) {
        brng::fizbuz_str(state.range(0));
    }
}

static void BM_rx_fizbz_s(benchmark::State &state) {
    for (auto _ : state) {
        rx::fizbuz_str(state.range(0));
    }
}

static void BM_crtn_bg(benchmark::State &state) {
    for(auto _ : state) {
        crtn::count_breaking_record_crtn(state.range(0));
    }
}

static void BM_vn_bg(benchmark::State &state) {
    for(auto _ : state) {
        count_breaking_record_vanilla(state.range(0));
    }
}

static void BM_rx_bg(benchmark::State &state) {
    for(auto _ : state) {
        rx::count_breaking_record_rx(state.range(0));
    }
}


/*
 *
BM_vn_bg/8192          212177 ns     212160 ns       3301
BM_vn_bg/32768         846872 ns     846886 ns        829
BM_vn_bg/262144       6754488 ns    6754703 ns        104
BM_vn_bg/1048576     26980602 ns   26982100 ns         26
BM_crtn_bg/8192       1031067 ns    1031115 ns        680
BM_crtn_bg/32768      3997456 ns    3997648 ns        174
BM_crtn_bg/262144    32134414 ns   32135386 ns         22
BM_crtn_bg/1048576  128451384 ns  128457513 ns          5
BM_rx_bg/8192          524946 ns     524975 ns       1329
BM_rx_bg/32768        2058859 ns    2058972 ns        340
BM_rx_bg/262144      16416116 ns   16417020 ns         43
BM_rx_bg/1048576     65487958 ns   65490170 ns         11
 */

const unsigned left = 1u<<13;
const unsigned right = 1u<<20;

#ifdef FIZZ
    BENCHMARK(BM_crtn_fizbz)->Range(left, right);
    BENCHMARK(BM_rng_fizbz)->Range(left, right);
    BENCHMARK(BM_brng_fizbz)->Range(left, right);
    BENCHMARK(BM_rx_fizbz)->Range(left, right);
    BENCHMARK(BM_vn_fizbz_transform)->Range(left, right);
    BENCHMARK(BM_vn_fizbz_mod)->Range(left, right);
    BENCHMARK(BM_vn_fizbz)->Range(left, right);

    BENCHMARK(BM_crtn_fizbz_s)->Range(left, right);
    BENCHMARK(BM_rng_fizbz_s)->Range(left, right);
    BENCHMARK(BM_brng_fizbz_s)->Range(left, right);
    BENCHMARK(BM_rx_fizbz_s)->Range(left, right);
#endif

BENCHMARK(BM_vn_bg)->Range(left, right);
BENCHMARK(BM_crtn_bg)->Range(left, right);
BENCHMARK(BM_rx_bg)->Range(left, right);


BENCHMARK_MAIN();
