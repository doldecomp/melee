# Samples of the .dat archives' data, typed by the DWARF build and compared
# with objdiff (see tools/dat-cli). Each archive is a unit, named by its
# module and file (Pl/PlMr), built in four steps: slice (archive →
# target/<unit>.o), codegen (→ src/<unit>.c, which includes a header and
# source per root in src/<unit>/), format (in place)
# and compile (→ base/<unit>.o). The build directory is also the objdiff
# project.
include_guard(GLOBAL)

# Configured through a symlink, the build names the same files by two paths
# (the physical one CMake resolves, and the logical one from $PWD), and
# ninja then reruns CMake and rebuilds everything on every build
file(REAL_PATH "${CMAKE_SOURCE_DIR}" _dat_real_source)
if(NOT _dat_real_source STREQUAL CMAKE_SOURCE_DIR)
    message(FATAL_ERROR "Configure from ${_dat_real_source}, not through a symlink (${CMAKE_SOURCE_DIR}): cd -P there first")
endif()

if(NOT MELEE_DWARF)
    message(FATAL_ERROR "MELEE_DAT_SAMPLES needs MELEE_DWARF: the samples are typed by its DWARF")
endif()

set(MELEE_DAT "" CACHE FILEPATH "melee-dat binary; built with cargo if empty")
set(MELEE_DAT_FILES "${CMAKE_SOURCE_DIR}/orig/${MELEE_VERSION}/files"
    CACHE PATH "The game's files, with its .dat archives")
# What to sample is the user's choice, not the project's
set(MELEE_DAT_SAMPLES_ALL "" CACHE STRING
    "Archives (globs, e.g. PlFx.dat;Gr*.dat) to sample every typed object of, not one instance per type")
set(MELEE_DAT_SAMPLES_EXCLUDE "" CACHE STRING
    "Types (globs on their names) never to sample, e.g. bulky vertex or image records")

set(_dat_all_regexes)
foreach(_glob IN LISTS MELEE_DAT_SAMPLES_ALL)
    string(REPLACE "." "\\." _regex "${_glob}")
    string(REPLACE "*" ".*" _regex "${_regex}")
    string(REPLACE "?" "." _regex "${_regex}")
    list(APPEND _dat_all_regexes "^${_regex}$")
endforeach()
set(_dat_exclude)
foreach(_glob IN LISTS MELEE_DAT_SAMPLES_EXCLUDE)
    list(APPEND _dat_exclude --exclude "${_glob}")
endforeach()

set(_dat_config "${CMAKE_SOURCE_DIR}/config/${MELEE_VERSION}/dat.yml")
set(_dat_symbols "${CMAKE_SOURCE_DIR}/config/${MELEE_VERSION}/dat_symbols.txt")

# The generated C is formatted like the repository's; clang-format comes
# with the clang that compiles it
get_filename_component(_dat_llvm_bin "${CMAKE_C_COMPILER}" DIRECTORY)
find_program(MELEE_CLANG_FORMAT clang-format HINTS "${_dat_llvm_bin}" REQUIRED)

# The tool
if(MELEE_DAT)
    set(_dat_tool "${MELEE_DAT}")
else()
    set(_dat_tool "${CMAKE_CURRENT_BINARY_DIR}/cargo/release/melee-dat")
    find_program(MELEE_CARGO cargo REQUIRED)
    add_custom_command(
        OUTPUT "${_dat_tool}"
        COMMAND "${MELEE_CARGO}" build --release -p melee-dat
            --manifest-path "${CMAKE_SOURCE_DIR}/Cargo.toml"
            --target-dir "${CMAKE_CURRENT_BINARY_DIR}/cargo"
        DEPFILE "${_dat_tool}.d"
        COMMENT "Building melee-dat"
        VERBATIM
    )
endif()

# The generated C isn't the repository's to tidy
file(WRITE "${CMAKE_CURRENT_BINARY_DIR}/src/.clang-tidy" "Checks: '-*'\n")

# The types, deduplicated once for every step
add_custom_command(
    OUTPUT types.bin
    COMMAND "${_dat_tool}" types export --dwarf melee.elf -o types.bin
    DEPENDS melee.elf "${_dat_tool}"
    COMMENT "Exporting types"
    VERBATIM
)

# How the base objects are compiled: the DWARF build's own flags, without
# its debug information
set(_dat_flags "${CMAKE_CURRENT_BINARY_DIR}/clang.rsp")
file(GENERATE OUTPUT "${_dat_flags}" CONTENT "\
--target=${CMAKE_C_COMPILER_TARGET}
-isystem ${NEWLIB_INCLUDE}
-D$<JOIN:$<TARGET_PROPERTY:melee,COMPILE_DEFINITIONS>,\n-D>
-I$<JOIN:$<TARGET_PROPERTY:melee,INCLUDE_DIRECTORIES>,\n-I>
$<JOIN:$<FILTER:$<TARGET_PROPERTY:melee,COMPILE_OPTIONS>,EXCLUDE,^-g|^-fdebug-macro$|^-fno-eliminate-unused-debug-types$>,\n>
-w
-fno-zero-initialized-in-bss
")

# What the generated C includes, from the tool
add_custom_command(
    OUTPUT src/macros.h
    COMMAND "${_dat_tool}" samples macros -o src/macros.h
    DEPENDS "${_dat_tool}"
    COMMENT "Writing src/macros.h"
    VERBATIM
)

file(GLOB _dat_archives CONFIGURE_DEPENDS "${MELEE_DAT_FILES}/*.dat")
set(_dat_sidecars)
set(_dat_bases)
set(_dat_commands)
foreach(_archive IN LISTS _dat_archives)
    get_filename_component(_file "${_archive}" NAME)
    get_filename_component(_stem "${_archive}" NAME_WE)
    # Grouped by module, the name's first two letters: Pl/PlMr, Gr/GrFs
    string(SUBSTRING "${_stem}" 0 2 _module)
    set(_unit "${_module}/${_stem}")
    set(_target "target/${_unit}.o")
    set(_sidecar "target/${_unit}.samples")
    set(_types "metadata/${_unit}.types")
    set(_layout "target/${_unit}.ld")
    set(_rest "target/${_unit}.rest.o")
    set(_object "obj/${_unit}.o")
    set(_source "src/${_unit}.c")
    set(_formatted "metadata/${_unit}.formatted")
    set(_base "base/${_unit}.o")

    set(_all)
    foreach(_regex IN LISTS _dat_all_regexes)
        if(_file MATCHES "${_regex}")
            set(_all --all)
        endif()
    endforeach()
    # A hash of the types this archive leads to, rewritten only when it
    # changes: the other steps depend on it, not on every type
    add_custom_command(
        OUTPUT "${_types}"
        COMMAND "${_dat_tool}" samples types "${_file}" "${_dat_config}"
            -p "${CMAKE_SOURCE_DIR}" --types types.bin
            --files "${MELEE_DAT_FILES}" -o "${_types}"
        DEPENDS "${_archive}" types.bin "${_dat_tool}" "${_dat_config}"
            "${_dat_symbols}"
        COMMENT "Hashing ${_file}'s types"
        VERBATIM
    )
    add_custom_command(
        OUTPUT "${_target}" "${_sidecar}" "${_layout}" "${_rest}"
        COMMAND "${_dat_tool}" samples slice "${_file}" "${_dat_config}"
            -p "${CMAKE_SOURCE_DIR}" --types types.bin
            --files "${MELEE_DAT_FILES}" -o "${_target}" ${_all} ${_dat_exclude}
        DEPENDS "${_archive}" "${_types}" "${_dat_tool}" "${_dat_config}"
            "${_dat_symbols}"
        COMMENT "Slicing ${_file}"
        VERBATIM
    )
    add_custom_command(
        OUTPUT "${_source}"
        COMMAND "${_dat_tool}" samples codegen "${_target}" --types types.bin
            -o "${_source}"
        DEPENDS "${_target}" "${_sidecar}" "${_types}" "${_dat_tool}"
        COMMENT "Generating ${_source}"
        VERBATIM
    )
    add_custom_command(
        OUTPUT "${_formatted}"
        COMMAND "${CMAKE_COMMAND}"
            "-DCLANG_FORMAT=${MELEE_CLANG_FORMAT}"
            "-DSTYLE=${CMAKE_SOURCE_DIR}/.clang-format"
            "-DSOURCE=${CMAKE_CURRENT_BINARY_DIR}/${_source}"
            "-DSTAMP=${CMAKE_CURRENT_BINARY_DIR}/${_formatted}"
            -P "${CMAKE_SOURCE_DIR}/cmake/DatFormat.cmake"
        DEPENDS "${_source}" "${CMAKE_SOURCE_DIR}/.clang-format"
            "${CMAKE_SOURCE_DIR}/cmake/DatFormat.cmake"
        COMMENT "Formatting ${_source}"
        VERBATIM
    )
    add_custom_command(
        OUTPUT "${_base}"
        BYPRODUCTS "${_object}"
        # Each sample in its own section, then linked into .data in the
        # target's order: clang lays variables out where an initializer
        # first points to them
        COMMAND "${CMAKE_C_COMPILER}" "@${_dat_flags}" -fdata-sections
            -MD -MF "${_base}.d" -MT "${_base}"
            -c "${_source}" -o "${_object}"
        # With the rest of the archive the walk explains, by name and size
        COMMAND "${CMAKE_LINKER}" -r -T "${_layout}" "${_object}" "${_rest}"
            -o "${_base}"
        DEPENDS "${_source}" "${_formatted}" "${_layout}" "${_rest}"
            "${_dat_flags}"
            src/macros.h
        DEPFILE "${_base}.d"
        COMMENT "Compiling ${_source}"
        VERBATIM
    )
    list(APPEND _dat_sidecars "${_sidecar}")
    list(APPEND _dat_bases "${_base}")
    list(APPEND _dat_commands "{\
\"directory\": \"${CMAKE_CURRENT_BINARY_DIR}\", \
\"file\": \"${CMAKE_CURRENT_BINARY_DIR}/${_source}\", \
\"arguments\": [\"${CMAKE_C_COMPILER}\", \"@${_dat_flags}\", \"-c\", \"${_source}\", \"-o\", \"${_base}\"]}")
endforeach()

# The same commands for clangd, which looks for the nearest
# compile_commands.json above a source
list(JOIN _dat_commands ",\n" _dat_commands)
file(GENERATE OUTPUT compile_commands.json CONTENT "[\n${_dat_commands}\n]\n")

# The only step that sees every unit
add_custom_command(
    OUTPUT objdiff.json
    COMMAND "${_dat_tool}" samples project ${_dat_sidecars} -o objdiff.json
    DEPENDS ${_dat_sidecars} "${_dat_tool}"
    COMMENT "Writing objdiff.json"
    VERBATIM
)
add_custom_target(dat-samples ALL DEPENDS ${_dat_bases} objdiff.json)
