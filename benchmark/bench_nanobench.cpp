#include <algorithm>
#include <array>
#include <functional>
#include <memory_resource>
#include <type_traits>
#include <vector>

#include <nanobench.h>

#include <dze/function.hpp>

#include "objects.hpp"

int main()
{
    constexpr size_t epochs = 4 * 128;
    constexpr size_t iterations = 1024;

    int x = 1;

    auto bench = ankerl::nanobench::Bench();
    bench.title("function pointer");

    bench.epochs(epochs).epochIterations(iterations).run(
        "inline",
        [&] { ankerl::nanobench::doNotOptimizeAway(x += x); });

    {
        std::vector<func*> v(epochs * iterations);
        auto it = v.begin();
        bench.epochs(epochs).epochIterations(iterations).run(
            "direct call",
            [&]
            {
                auto& f = *it++ = get_function_ptr();
                ankerl::nanobench::doNotOptimizeAway(f(x));
            });
    }

    {
        std::vector<std::function<int&(int&)>> v(epochs * iterations);
        auto it = v.begin();
        bench.epochs(epochs).epochIterations(iterations).run(
            "std::function",
            [&]
            {
                auto& f = *it++ = get_function_ptr();
                ankerl::nanobench::doNotOptimizeAway(f(x));
            });
    }

    {
        std::vector<dze::function<int&(int&)>> v(epochs * iterations);
        auto it = v.begin();
        bench.epochs(epochs).epochIterations(iterations).run(
            "dze::function",
            [&]
            {
                auto& f = *it++ = get_function_ptr();
                ankerl::nanobench::doNotOptimizeAway(f(x));
            });
    }

    {
        std::vector<dze::pmr::function<int&(int&)>> v(epochs * iterations);
        auto it = v.begin();
        bench.epochs(epochs).epochIterations(iterations).run(
            "dze::pmr::function",
            [&]
            {
                auto& f = *it++ = get_function_ptr();
                ankerl::nanobench::doNotOptimizeAway(f(x));
            });
    }

    {
        std::vector<dze::pmr::function<int&(int&)>> v;
        v.reserve(epochs * iterations);
        for (size_t i = 0; i != v.capacity(); ++i)
            v.emplace_back(std::pmr::null_memory_resource());
        auto it = v.begin();
        bench.epochs(epochs).epochIterations(iterations).run(
            "dze::pmr::function with null_memory_resource",
            [&]
            {
                auto& f = *it++ = get_function_ptr();
                ankerl::nanobench::doNotOptimizeAway(f(x));
            });
    }

    bench.title("function object");

    bench.epochs(epochs).epochIterations(iterations).run(
        "inline",
        [&] { ankerl::nanobench::doNotOptimizeAway(x += x); });

    {
        std::vector<obj> v(epochs * iterations);
        auto it = v.begin();
        bench.epochs(epochs).epochIterations(iterations).run(
            "direct call",
            [&]
            {
                auto& f = *it++ = get_function_object(x);
                ankerl::nanobench::doNotOptimizeAway(f());
            });
    }

    {
        std::vector<std::function<int&()>> v(epochs * iterations);
        auto it = v.begin();
        bench.epochs(epochs).epochIterations(iterations).run(
            "std::function",
            [&]
            {
                auto& f = *it++ = get_function_object(x);
                ankerl::nanobench::doNotOptimizeAway(f());
            });
    }

    {
        std::vector<dze::function<int&()>> v(epochs * iterations);
        auto it = v.begin();
        bench.epochs(epochs).epochIterations(iterations).run(
            "dze::function",
            [&]
            {
                auto& f = *it++ = get_function_object(x);
                ankerl::nanobench::doNotOptimizeAway(f());
            });
    }

    {
        std::vector<dze::pmr::function<int&()>> v(epochs * iterations);
        auto it = v.begin();
        bench.epochs(epochs).epochIterations(iterations).run(
            "dze::pmr::function",
            [&]
            {
                auto& f = *it++ = get_function_object(x);
                ankerl::nanobench::doNotOptimizeAway(f());
            });
    }

    {
        std::vector<dze::pmr::function<int&()>> v;
        v.reserve(epochs * iterations);
        for (size_t i = 0; i != v.capacity(); ++i)
            v.emplace_back(std::pmr::null_memory_resource());
        auto it = v.begin();
        bench.epochs(epochs).epochIterations(iterations).run(
            "dze::pmr::function with null_memory_resource",
            [&]
            {
                auto& f = *it++ = get_function_object(x);
                ankerl::nanobench::doNotOptimizeAway(f());
            });
    }

    bench.title("large function object");

    std::array<int, 64> nums;
    std::generate(nums.begin(), nums.end(), ankerl::nanobench::Rng{});

    {
        ankerl::nanobench::Rng rng{0};
        bench.epochs(epochs).epochIterations(iterations).run(
            "inline",
            [&]
            {
                auto nums2 = nums;
                ankerl::nanobench::doNotOptimizeAway(x += nums2[rng.bounded(nums.size())]);
            });
    }

    {
        ankerl::nanobench::Rng rng{0};
        std::vector<large_obj> v(epochs * iterations);
        auto it = v.begin();
        bench.epochs(epochs).epochIterations(iterations).run(
            "direct call",
            [&]
            {
                auto& f = *it++ = get_function_object(x, nums);
                ankerl::nanobench::doNotOptimizeAway(f(rng.bounded(nums.size())));
            });
    }

    {
        ankerl::nanobench::Rng rng{0};
        std::vector<std::function<int&(size_t)>> v(epochs * iterations);
        auto it = v.begin();
        bench.epochs(epochs).epochIterations(iterations).run(
            "std::function",
            [&]
            {
                auto& f = *it++ = get_function_object(x, nums);
                ankerl::nanobench::doNotOptimizeAway(f(rng.bounded(nums.size())));
            });
    }

    {
        ankerl::nanobench::Rng rng{0};
        std::vector<dze::function<int&(size_t)>> v(epochs * iterations);
        auto it = v.begin();
        bench.epochs(epochs).epochIterations(iterations).run(
            "dze::function",
            [&]
            {
                auto& f = *it++ = get_function_object(x, nums);
                ankerl::nanobench::doNotOptimizeAway(f(rng.bounded(nums.size())));
            });
    }

    {
        std::aligned_storage_t<sizeof(large_obj), alignof(large_obj)> buf;
        dze::monotonic_buffer_resource mr{&buf, sizeof(buf)};

        ankerl::nanobench::Rng rng{0};
        std::vector<dze::function<int&(size_t), dze::monotonic_buffer_resource>> v;
        v.reserve(epochs * iterations);
        for (size_t i = 0; i != v.capacity(); ++i)
            v.emplace_back(mr);
        auto it = v.begin();
        bench.epochs(epochs).epochIterations(iterations).run(
            "dze::function with monotonic_buffer_resource",
            [&]
            {
                auto& f = *it++ = get_function_object(x, nums);
                ankerl::nanobench::doNotOptimizeAway(f(rng.bounded(nums.size())));
            });
    }

    {
        ankerl::nanobench::Rng rng{0};
        std::vector<dze::pmr::function<int&(size_t)>> v(epochs * iterations);
        auto it = v.begin();
        bench.epochs(epochs).epochIterations(iterations).run(
            "dze::pmr::function",
            [&]
            {
                auto& f = *it++ = get_function_object(x, nums);
                ankerl::nanobench::doNotOptimizeAway(f(rng.bounded(nums.size())));
            });
    }

    {
        std::aligned_storage_t<sizeof(large_obj), alignof(large_obj)> buf;
        std::pmr::monotonic_buffer_resource mr{&buf, sizeof(buf), std::pmr::null_memory_resource()};

        ankerl::nanobench::Rng rng{0};
        std::vector<dze::pmr::function<int&(size_t)>> v;
        v.reserve(epochs * iterations);
        for (size_t i = 0; i != v.capacity(); ++i)
            v.emplace_back(&mr);
        auto it = v.begin();
        bench.epochs(epochs).epochIterations(iterations).run(
            "dze::pmr::function with monotonic_buffer_resource",
            [&]
            {
                auto& f = *it++ = get_function_object(x, nums);
                ankerl::nanobench::doNotOptimizeAway(f(rng.bounded(nums.size())));
                mr.release();
            });
    }
}
