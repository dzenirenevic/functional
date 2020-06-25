set(proj_name nanobench)

include(add_external_project)
include(thirdparty_common)

add_external_project(
    ${proj_name}
    GIT_REPOSITORY https://github.com/martinus/nanobench.git
    GIT_TAG c534992696b9341274c6714931d0064d74239fcb
    GIT_SHALLOW true
    PREFIX "${thirdparty_prefix}/${proj_name}"
    SOURCE_DIR "${thirdparty_prefix}/${proj_name}/source"
    BINARY_DIR "${thirdparty_binary_dir}/${proj_name}/bin"
    SKIP_ADD_SUBDIR)

add_library(nanobench OBJECT ${CMAKE_CURRENT_LIST_DIR}/nanobench_impl.cpp)
target_compile_options(nanobench PUBLIC $<$<CXX_COMPILER_ID:MSVC>:/wd4267>)
target_include_directories(nanobench PUBLIC ${${proj_name}_SOURCE_DIR}/src/include)

unset(proj_name)

if (${PROJECT_NAME}_static_analyzer)
    set_target_properties(
        nanobench
        PROPERTIES
        CXX_CLANG_TIDY "${clang_tidy};-checks=-modernize-*,-readability-*,-performance-noexcept-move-constructor;${clang_tidy_options}")
endif ()
