set(proj_name nanobench)

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
    GIT_REPOSITORY https://github.com/martinus/nanobench.git
    GIT_TAG c534992696b9341274c6714931d0064d74239fcb
    GIT_SHALLOW true
    PREFIX "${thirdparty_prefix}/${proj_name}"
    SOURCE_DIR "${thirdparty_prefix}/${proj_name}/source"
    BINARY_DIR "${thirdparty_binary_dir}/${proj_name}/bin")

add_library(nanobench OBJECT ${CMAKE_CURRENT_LIST_DIR}/nanobench_impl.cpp)
target_compile_options(nanobench PUBLIC $<$<CXX_COMPILER_ID:MSVC>:/wd4267>)
target_include_directories(nanobench PUBLIC ${${proj_name}_proj_SOURCE_DIR}/src/include)

unset(proj_name)

if (${PROJECT_NAME}_static_analyzer)
    set_target_properties(
        nanobench
        PROPERTIES
        CXX_CLANG_TIDY "${clang_tidy};-checks=-modernize-*,-readability-*,-performance-noexcept-move-constructor;${clang_tidy_options}")
endif ()
