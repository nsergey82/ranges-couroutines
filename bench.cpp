#include "fzbz_crtn.h"
#include "fzbz_rng.h"
#include "fzbz_rx.h"
#include "fzbz_vanilla.h"

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


const unsigned left = 1u<<13;
const unsigned right = 1u<<20;

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

BENCHMARK_MAIN();
