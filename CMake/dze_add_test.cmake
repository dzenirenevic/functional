set(proj_name dze_add_test)

get_property(${proj_name}_included GLOBAL PROPERTY ${proj_name}_included SET)
if (${proj_name}_included)
    unset(proj_name)
    return()
endif ()

set_property(GLOBAL PROPERTY ${proj_name}_included)

include(add_external_project)
include(thirdparty_common)

add_external_project(
    ${proj_name}
    GIT_REPOSITORY https://github.com/dzenirenevic/dze_add_test
    GIT_TAG 287f7127016b3160c9e80ce6e2f77bb57f20f981
    GIT_SHALLOW true
    PREFIX "${thirdparty_prefix}/${proj_name}"
    SOURCE_DIR "${thirdparty_prefix}/${proj_name}/source"
    SKIP_ADD_SUBDIR)

include(${${proj_name}_SOURCE_DIR}/${proj_name}.cmake)

unset(proj_name)
