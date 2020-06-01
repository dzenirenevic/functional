# Allocator-aware polymorphic function wrapper

This library introduces `dze::function<S, A>` that aims to be a API-compatible alternative to std::function<S>.

`dze::function<S, A>` acts similar to a container in terms of its usage of allocated memory as it does not release memory when it is cleared or assigned another function object with smaller memory footprint. Furthermore, it is allocator aware and can use the polymorphic memory resources introduced in C++17. It has an inline buffer of 63 bytes aligned as `std::max_align_t`, so storing function objects with smaller size and alignment requirements do not cause allocations.
