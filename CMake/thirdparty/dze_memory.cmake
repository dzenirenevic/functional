set(proj_name dze_memory)

include(add_external_project)
include(thirdparty_common)

add_external_project(
    ${proj_name}
    GIT_REPOSITORY https://github.com/dzenirenevic/memory.git
    GIT_TAG 0ee508af21bc70160fa7bdd8b9ebe3e7885693f0
    GIT_SHALLOW true
    PREFIX "${thirdparty_prefix}/${proj_name}"
    SOURCE_DIR "${thirdparty_prefix}/${proj_name}/source"
    BINARY_DIR "${thirdparty_binary_dir}/${proj_name}/bin")

unset(proj_name)
