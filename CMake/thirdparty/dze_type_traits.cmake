set(proj_name dze_type_traits)

include(add_external_project)
include(thirdparty_common)

add_external_project(
    ${proj_name}
    GIT_REPOSITORY https://github.com/dzenirenevic/type_traits.git
    GIT_TAG d615689e96a1c8154348f0b377a82369b860f103
    GIT_SHALLOW true
    PREFIX "${thirdparty_prefix}/${proj_name}"
    SOURCE_DIR "${thirdparty_prefix}/${proj_name}/source"
    BINARY_DIR "${thirdparty_binary_dir}/${proj_name}/bin")

unset(proj_name)
