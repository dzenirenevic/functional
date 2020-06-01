#pragma once

#include <array>

using func = int&(int&);

func* get_function_ptr();

struct obj
{
    int* x;

    int& operator()() const;
};

obj get_function_object(int&);

struct large_obj
{
    int* x;
    alignas(64) std::array<int, 64> nums;

    int& operator()(size_t);
};

large_obj get_function_object(int&, const std::array<int, 64>&);
