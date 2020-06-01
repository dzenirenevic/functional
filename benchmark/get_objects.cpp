#include "objects.hpp"

inline int& captureless(int& x)
{
    return x += x;
}

func* get_function_ptr()
{
    return captureless;
}

int& obj::operator()() const { return *x += *x; }

obj get_function_object(int& x)
{
    return obj{&x};
}

int& large_obj::operator()(const size_t idx) { return *x += nums[idx]; }

large_obj get_function_object(int& x, const std::array<int, 64>& nums)
{
    return large_obj{&x, nums};
}
