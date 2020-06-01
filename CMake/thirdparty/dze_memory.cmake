set(proj_name dze_memory)

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
    GIT_REPOSITORY https://github.com/dzenirenevic/memory.git
    GIT_TAG 0ee508af21bc70160fa7bdd8b9ebe3e7885693f0
    GIT_SHALLOW true
    PREFIX "${thirdparty_prefix}/${proj_name}"
    SOURCE_DIR "${thirdparty_prefix}/${proj_name}/source"
    BINARY_DIR "${thirdparty_binary_dir}/${proj_name}/bin")

add_subdirectory(${${proj_name}_proj_SOURCE_DIR} ${${proj_name}_proj_BINARY_DIR} EXCLUDE_FROM_ALL)

unset(proj_name)
