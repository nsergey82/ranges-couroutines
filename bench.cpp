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
        crtn::count_good_bad(state.range(0));
    }
}

static void BM_vn_bg(benchmark::State &state) {
    for(auto _ : state) {
        count_breaking_record_vanilla(state.range(0));
    }
}



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


BENCHMARK_MAIN();
