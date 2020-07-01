set(proj_name dze_memory)

include(add_external_project)
include(thirdparty_common)

add_external_project(
    ${proj_name}
    GIT_REPOSITORY https://github.com/dzenirenevic/memory.git
    GIT_TAG 1f0813b65fab42c66c9aa10ce86d4563e00c55c3
    GIT_SHALLOW true
    PREFIX "${thirdparty_prefix}/${proj_name}"
    SOURCE_DIR "${thirdparty_prefix}/${proj_name}/source"
    BINARY_DIR "${thirdparty_binary_dir}/${proj_name}/bin")

unset(proj_name)
