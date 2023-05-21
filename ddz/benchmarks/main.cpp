#include <benchmark/benchmark.h>
#define BENCHMARK_BUILD
#include "utils/CardUtil.hpp"
#include "utils/Collections.hpp"

static void BENCHMARK_stl_shuffle(benchmark::State &state) {
  ddz::CardList list = ddz::makeFullCardList();
  for (auto _ : state) {
    list.shuffle();
  }
}

static void BENCHMARK_my_shuffle(benchmark::State &state) {
  ddz::CardList list = ddz::makeFullCardList();
  for (auto _ : state) {
    list.__shuffle();
  }
}

BENCHMARK(BENCHMARK_my_shuffle);
BENCHMARK(BENCHMARK_stl_shuffle);

BENCHMARK_MAIN();
