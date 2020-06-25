include(fetch_content)

# Fetch using FetchContent from a git repository and add_subdirectory.
# Arguments to the subdirectories options can be passed as a list in ARGS.
function(add_external_project proj_name)
    get_property(
        external_project_${proj_name}_included
        GLOBAL PROPERTY external_project_${proj_name}_included SET)

    if (external_project_${proj_name}_included)
        return()
    endif ()

    set_property(GLOBAL PROPERTY external_project_${proj_name}_included)

    set(options SKIP_ADD_SUBDIR)
    set(one_value_args "")
    set(multi_value_args ARGS)
    cmake_parse_arguments(
        ARG
        "${options}"
        "${one_value_args}"
        "${multi_value_args}"
        ${ARGN})

    fetch_content(${proj_name} ${ARG_UNPARSED_ARGUMENTS})

    set(${proj_name}_POPULATED ${${proj_name}_POPULATED} PARENT_SCOPE)
    set(${proj_name}_SOURCE_DIR ${${proj_name}_SOURCE_DIR} PARENT_SCOPE)
    set(${proj_name}_BINARY_DIR ${${proj_name}_BINARY_DIR} PARENT_SCOPE)

    if (NOT ${ARG_SKIP_ADD_SUBDIR})
        foreach (arg ${ARG_ARGS})
            STRING(REGEX MATCH "^\(.*\)=\(.*)$" out ${arg})
            set(${CMAKE_MATCH_1} ${CMAKE_MATCH_2})
        endforeach ()

        add_subdirectory(${${proj_name}_SOURCE_DIR} ${${proj_name}_BINARY_DIR} EXCLUDE_FROM_ALL)
    endif ()
endfunction()
