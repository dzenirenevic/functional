set(proj_name dze_type_traits)

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
    GIT_REPOSITORY https://github.com/dzenirenevic/type_traits.git
    GIT_TAG d615689e96a1c8154348f0b377a82369b860f103
    GIT_SHALLOW true
    PREFIX "${thirdparty_prefix}/${proj_name}"
    SOURCE_DIR "${thirdparty_prefix}/${proj_name}/source"
    BINARY_DIR "${thirdparty_binary_dir}/${proj_name}/bin")

add_subdirectory(${${proj_name}_proj_SOURCE_DIR} ${${proj_name}_proj_BINARY_DIR} EXCLUDE_FROM_ALL)

unset(proj_name)
