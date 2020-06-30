set(proj_name catch2)

include(add_external_project)
include(thirdparty_common)

add_external_project(
    ${proj_name}
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG v2.12.3
    GIT_SHALLOW true
    PREFIX "${thirdparty_prefix}/${proj_name}"
    SOURCE_DIR "${thirdparty_prefix}/${proj_name}/source"
    BINARY_DIR "${thirdparty_binary_dir}/${proj_name}/bin")

if (${${proj_name}_ADDED})
    add_library(Catch2Main OBJECT ${CMAKE_CURRENT_LIST_DIR}/catch_with_main.cpp)
    target_link_libraries(Catch2Main Catch2)
    add_library(Catch2::Main ALIAS Catch2Main)
endif ()

unset(proj_name)
