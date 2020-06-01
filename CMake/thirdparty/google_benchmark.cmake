set(proj_name google_benchmark)

get_property(${proj_name}_included GLOBAL PROPERTY ${proj_name}_included SET)
if (${proj_name}_included)
    unset(proj_name)
    return()
endif ()

set_property(GLOBAL PROPERTY ${proj_name}_included)

include(fetch_content)
include(thirdparty_common)

fetch_content(
    ${proj_name}_proj
    GIT_REPOSITORY https://github.com/google/benchmark.git
    GIT_TAG 8039b4030795b1c9b8cedb78e3a2a6fb89574b6e
    GIT_SHALLOW true
    PREFIX "${thirdparty_prefix}/${proj_name}"
    SOURCE_DIR "${thirdparty_prefix}/${proj_name}/source"
    BINARY_DIR "${thirdparty_binary_dir}/${proj_name}/bin")

set(BENCHMARK_ENABLE_TESTING OFF)
add_subdirectory(${${proj_name}_proj_SOURCE_DIR} ${${proj_name}_proj_BINARY_DIR} EXCLUDE_FROM_ALL)

unset(proj_name)

target_compile_options(
    benchmark
    PRIVATE
    -Wno-switch-enum
    -Wno-missing-declarations)

if (${PROJECT_NAME}_static_analyzer)
    set_target_properties(
        benchmark
        PROPERTIES
        CXX_CLANG_TIDY "${clang_tidy};-checks=-clang-analyzer-deadcode.DeadStores,-modernize-*,-readability-*,-performance-unnecessary-value-param;${clang_tidy_options}")
endif ()
