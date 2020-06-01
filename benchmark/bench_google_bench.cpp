#include <algorithm>
#include <array>
#include <functional>
#include <memory_resource>
#include <random>
#include <type_traits>
#include <vector>

#include <benchmark/benchmark.h>

#include <dze/function.hpp>

#include "objects.hpp"

constexpr size_t iterations = 4 * 128 * 1024;

int x = 1;

namespace {

void fptr_inline(benchmark::State& state)
{
    for ([[maybe_unused]] auto _ : state)
        benchmark::DoNotOptimize(x += x);
}

void fptr_direct_call(benchmark::State& state)
{
    std::vector<func*> v(iterations);
    auto it = v.begin();

    for ([[maybe_unused]] auto _ : state)
    {
        auto& f = *it++ = get_function_ptr();
        benchmark::DoNotOptimize(f(x));
    }
}

void fptr_std_function(benchmark::State& state)
{
    std::vector<std::function<int&(int&)>> v(iterations);
    auto it = v.begin();

    for ([[maybe_unused]] auto _ : state)
    {
        auto& f = *it++ = get_function_ptr();
        benchmark::DoNotOptimize(f(x));
    }
}

void fptr_dze_function(benchmark::State& state)
{
    std::vector<dze::function<int&(int&)>> v(iterations);
    auto it = v.begin();

    for ([[maybe_unused]] auto _ : state)
    {
        auto& f = *it++ = get_function_ptr();
        benchmark::DoNotOptimize(f(x));
    }
}

void fptr_dze_pmr_function(benchmark::State& state)
{
    std::vector<dze::pmr::function<int&(int&)>> v(iterations);
    auto it = v.begin();

    for ([[maybe_unused]] auto _ : state)
    {
        auto& f = *it++ = get_function_ptr();
        benchmark::DoNotOptimize(f(x));
    }
}

void fptr_dze_pmr_function_with_null_memory_resource(benchmark::State& state)
{
    std::vector<dze::pmr::function<int&(int&)>> v;
    v.reserve(iterations);
    for (size_t i = 0; i != v.capacity(); ++i)
        v.emplace_back(std::pmr::null_memory_resource());
    auto it = v.begin();

    for ([[maybe_unused]] auto _ : state)
    {
        auto& f = *it++ = get_function_ptr();
        benchmark::DoNotOptimize(f(x));
    }
}

void fobj_inline(benchmark::State& state)
{
    for ([[maybe_unused]] auto _ : state)
        benchmark::DoNotOptimize(x += x);
}

void fobj_direct_call(benchmark::State& state)
{
    std::vector<obj> v(iterations);
    auto it = v.begin();

    for ([[maybe_unused]] auto _ : state)
    {
        auto& f = *it++ = get_function_object(x);
        benchmark::DoNotOptimize(f());
    }
}

void fobj_std_function(benchmark::State& state)
{
    std::vector<std::function<int&()>> v(iterations);
    auto it = v.begin();

    for ([[maybe_unused]] auto _ : state)
    {
        auto& f = *it++ = get_function_object(x);
        benchmark::DoNotOptimize(f());
    }
}

void fobj_dze_function(benchmark::State& state)
{
    std::vector<dze::function<int&()>> v(iterations);
    auto it = v.begin();

    for ([[maybe_unused]] auto _ : state)
    {
        auto& f = *it++ = get_function_object(x);
        benchmark::DoNotOptimize(f());
    }
}

void fobj_dze_pmr_function(benchmark::State& state)
{
    std::vector<dze::pmr::function<int&()>> v(iterations);
    auto it = v.begin();

    for ([[maybe_unused]] auto _ : state)
    {
        auto& f = *it++ = get_function_object(x);
        benchmark::DoNotOptimize(f());
    }
}

void fobj_dze_pmr_function_with_null_memory_resource(benchmark::State& state)
{
    std::vector<dze::pmr::function<int&()>> v;
    v.reserve(iterations);
    for (size_t i = 0; i != iterations; ++i)
        v.emplace_back(std::pmr::null_memory_resource());
    auto it = v.begin();

    for ([[maybe_unused]] auto _ : state)
    {
        auto& f = *it++ = get_function_object(x);
        benchmark::DoNotOptimize(f());
    }
}

void large_fobj_inline(benchmark::State& state)
{
    std::array<int, 64> nums;
    std::mt19937 rng;
    std::generate(nums.begin(), nums.end(), rng);

    for ([[maybe_unused]] auto _ : state)
    {
        auto nums2 = nums;
        benchmark::DoNotOptimize(x += nums2[rng() % nums.size()]);
    }
}

void large_fobj_direct_call(benchmark::State& state)
{
    std::array<int, 64> nums;
    std::mt19937 rng;
    std::generate(nums.begin(), nums.end(), rng);

    std::vector<large_obj> v(iterations);
    auto it = v.begin();

    for ([[maybe_unused]] auto _ : state)
    {
        auto& f = *it++ = get_function_object(x, nums);
        benchmark::DoNotOptimize(f(rng() % nums.size()));
    }
}

void large_fobj_std_function(benchmark::State& state)
{
    std::array<int, 64> nums;
    std::mt19937 rng;
    std::generate(nums.begin(), nums.end(), rng);

    std::vector<std::function<int&(size_t)>> v(iterations);
    auto it = v.begin();

    for ([[maybe_unused]] auto _ : state)
    {
        auto& f = *it++ = get_function_object(x, nums);
        benchmark::DoNotOptimize(f(rng() % nums.size()));
    }
}

void large_fobj_dze_function(benchmark::State& state)
{
    std::array<int, 64> nums;
    std::mt19937 rng;
    std::generate(nums.begin(), nums.end(), rng);

    std::vector<dze::function<int&(size_t)>> v(iterations);
    auto it = v.begin();

    for ([[maybe_unused]] auto _ : state)
    {
        auto& f = *it++ = get_function_object(x, nums);
        benchmark::DoNotOptimize(f(rng() % nums.size()));
    }
}

void large_fobj_dze_function_with_monotonic_buffer_resource(benchmark::State& state)
{
    std::array<int, 64> nums;
    std::mt19937 rng;
    std::generate(nums.begin(), nums.end(), rng);

    std::aligned_storage_t<sizeof(large_obj), alignof(large_obj)> buf;
    dze::monotonic_buffer_resource mr{&buf, sizeof(buf)};

    std::vector<dze::function<int&(size_t), dze::monotonic_buffer_resource>> v;
    v.reserve(iterations);
    for (size_t i = 0; i != v.capacity(); ++i)
        v.emplace_back(mr);
    auto it = v.begin();

    for ([[maybe_unused]] auto _ : state)
    {
        auto& f = *it++ = get_function_object(x, nums);
        benchmark::DoNotOptimize(f(rng() % nums.size()));
    }
}

void large_fobj_dze_pmr_function(benchmark::State& state)
{
    std::array<int, 64> nums;
    std::mt19937 rng;
    std::generate(nums.begin(), nums.end(), rng);

    std::vector<dze::pmr::function<int&(size_t)>> v(iterations);
    auto it = v.begin();

    for ([[maybe_unused]] auto _ : state)
    {
        auto& f = *it++ = get_function_object(x, nums);
        benchmark::DoNotOptimize(f(rng() % nums.size()));
    }
}

void large_fobj_dze_pmr_function_with_monotonic_buffer_resource(benchmark::State& state)
{
    std::array<int, 64> nums;
    std::mt19937 rng;
    std::generate(nums.begin(), nums.end(), rng);

    std::aligned_storage_t<sizeof(large_obj), alignof(large_obj)> buf;
    std::pmr::monotonic_buffer_resource mr{&buf, sizeof(buf), std::pmr::null_memory_resource()};

    std::vector<dze::pmr::function<int&(size_t)>> v;
    v.reserve(iterations);
    for (size_t i = 0; i != v.capacity(); ++i)
        v.emplace_back(&mr);
    auto it = v.begin();

    for ([[maybe_unused]] auto _ : state)
    {
        auto& f = *it++ = get_function_object(x, nums);
        benchmark::DoNotOptimize(f(rng() % nums.size()));
        mr.release();
    }
}

} // namespace

BENCHMARK(fptr_inline)->Iterations(iterations);
BENCHMARK(fptr_direct_call)->Iterations(iterations);
BENCHMARK(fptr_std_function)->Iterations(iterations);
BENCHMARK(fptr_dze_function)->Iterations(iterations);
BENCHMARK(fptr_dze_pmr_function)->Iterations(iterations);
BENCHMARK(fptr_dze_pmr_function_with_null_memory_resource)->Iterations(iterations);
BENCHMARK(fobj_inline)->Iterations(iterations);
BENCHMARK(fobj_direct_call)->Iterations(iterations);
BENCHMARK(fobj_std_function)->Iterations(iterations);
BENCHMARK(fobj_dze_function)->Iterations(iterations);
BENCHMARK(fobj_dze_pmr_function)->Iterations(iterations);
BENCHMARK(fobj_dze_pmr_function_with_null_memory_resource)->Iterations(iterations);
BENCHMARK(large_fobj_inline)->Iterations(iterations);
BENCHMARK(large_fobj_direct_call)->Iterations(iterations);
BENCHMARK(large_fobj_std_function)->Iterations(iterations);
BENCHMARK(large_fobj_dze_function)->Iterations(iterations);
BENCHMARK(large_fobj_dze_function_with_monotonic_buffer_resource)->Iterations(iterations);
BENCHMARK(large_fobj_dze_pmr_function)->Iterations(iterations);
BENCHMARK(large_fobj_dze_pmr_function_with_monotonic_buffer_resource)->Iterations(iterations);

BENCHMARK_MAIN();
