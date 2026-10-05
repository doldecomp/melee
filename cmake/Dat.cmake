# Samples of the .dat archives' data, typed by the DWARF build and compared
# with objdiff (see tools/dat-cli). Each archive is a unit, named by its
# module and file (Pl/PlMr). One step chooses the samples across every
# archive (→ metadata/pick/); then each unit is built in four: slice
# (archive → target/<unit>.o), codegen (→ src/<unit>.h, and src/<unit>.c
# if it has samples), format (in place) and compile (→ base/<unit>.o). The
# build directory is also the objdiff project.
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
file(GLOB _dat_archives CONFIGURE_DEPENDS LIST_DIRECTORIES false "${MELEE_DAT_FILES}/*.dat")
if(NOT _dat_archives)
    message(FATAL_ERROR
        "No .dat archives found in MELEE_DAT_FILES (${MELEE_DAT_FILES}). "
        "Extract the game's files there or set MELEE_DAT_FILES to their directory.")
endif()
# What to sample is the user's choice, not the project's
set(MELEE_DAT_SAMPLES_ALL "" CACHE STRING
    "Archives (globs, e.g. PlFx.dat;Gr*.dat) to sample every typed object of, not just the instances chosen to cover each type")
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

# Which archives sample every object; the others sample instances that
# `pick` chooses across all of them
set(_dat_picked)
set(_dat_picks)
foreach(_archive IN LISTS _dat_archives)
    get_filename_component(_file "${_archive}" NAME)
    set(_all FALSE)
    foreach(_regex IN LISTS _dat_all_regexes)
        if(_file MATCHES "${_regex}")
            set(_all TRUE)
        endif()
    endforeach()
    if(NOT _all)
        list(APPEND _dat_picked "${_file}")
        list(APPEND _dat_picks "metadata/pick/${_file}.pick")
    endif()
endforeach()
if(_dat_picked)
    # Each archive's choice is rewritten only when it changes: the other
    # steps depend on it, not on every archive
    add_custom_command(
        OUTPUT ${_dat_picks}
        COMMAND "${_dat_tool}" samples pick ${_dat_picked} "${_dat_config}"
            -p "${CMAKE_SOURCE_DIR}" --types types.bin
            --files "${MELEE_DAT_FILES}" -o metadata/pick ${_dat_exclude}
        DEPENDS ${_dat_archives} types.bin "${_dat_tool}" "${_dat_config}"
            "${_dat_symbols}"
        COMMENT "Choosing samples"
        VERBATIM
    )
endif()

set(_dat_sidecars)
set(_dat_bases)
set(_dat_commands)
set(_dat_optional)
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
    set(_header "src/${_unit}.h")
    set(_formatted "metadata/${_unit}.formatted")
    set(_base "base/${_unit}.o")

    set(_select --all)
    set(_pick)
    if("${_file}" IN_LIST _dat_picked)
        set(_pick "metadata/pick/${_file}.pick")
        set(_select --pick "${_pick}")
    endif()
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
            --files "${MELEE_DAT_FILES}" -o "${_target}" ${_select}
            ${_dat_exclude}
        DEPENDS "${_archive}" "${_types}" "${_dat_tool}" "${_dat_config}"
            "${_dat_symbols}" ${_pick}
        COMMENT "Slicing ${_file}"
        VERBATIM
    )
    add_custom_command(
        # The header always; the source only with samples, so ninja isn't
        # told of it, or it would rebuild the units without
        OUTPUT "${_header}"
        COMMAND "${_dat_tool}" samples codegen "${_target}" --types types.bin
            -o "${_source}"
        DEPENDS "${_target}" "${_sidecar}" "${_types}" "${_dat_tool}"
        COMMENT "Generating src/${_unit}"
        VERBATIM
    )
    add_custom_command(
        OUTPUT "${_formatted}"
        COMMAND "${CMAKE_COMMAND}"
            "-DCLANG_FORMAT=${MELEE_CLANG_FORMAT}"
            "-DSTYLE=${CMAKE_SOURCE_DIR}/.clang-format"
            "-DUNIT=${CMAKE_CURRENT_BINARY_DIR}/src/${_unit}"
            "-DSTAMP=${CMAKE_CURRENT_BINARY_DIR}/${_formatted}"
            -P "${CMAKE_SOURCE_DIR}/cmake/DatFormat.cmake"
        DEPENDS "${_header}" "${CMAKE_SOURCE_DIR}/.clang-format"
            "${CMAKE_SOURCE_DIR}/cmake/DatFormat.cmake"
        COMMENT "Formatting src/${_unit}"
        VERBATIM
    )
    add_custom_command(
        OUTPUT "${_base}"
        # The samples, if any (in obj/<unit>.o, which units without have
        # none of), with the rest of the archive the walk
        # explains, by name and size
        COMMAND "${CMAKE_COMMAND}"
            "-DC_COMPILER=${CMAKE_C_COMPILER}"
            "-DFLAGS=${_dat_flags}"
            "-DLINKER=${CMAKE_LINKER}"
            "-DSOURCE=${CMAKE_CURRENT_BINARY_DIR}/${_source}"
            "-DHEADER=${_header}"
            "-DOBJECT=${_object}"
            "-DLAYOUT=${_layout}"
            "-DREST=${_rest}"
            "-DBASE=${_base}"
            "-DDEPFILE=${_base}.d"
            -P "${CMAKE_SOURCE_DIR}/cmake/DatCompile.cmake"
        DEPENDS "${_header}" "${_formatted}" "${_layout}" "${_rest}"
            "${_dat_flags}" src/macros.h
            "${CMAKE_SOURCE_DIR}/cmake/DatCompile.cmake"
        DEPFILE "${_base}.d"
        COMMENT "Compiling src/${_unit}"
        VERBATIM
    )
    list(APPEND _dat_optional "${_source}" "${_object}")
    list(APPEND _dat_sidecars "${_sidecar}")
    list(APPEND _dat_bases "${_base}")
    list(APPEND _dat_commands "{\
\"directory\": \"${CMAKE_CURRENT_BINARY_DIR}\", \
\"file\": \"${CMAKE_CURRENT_BINARY_DIR}/${_source}\", \
\"arguments\": [\"${CMAKE_C_COMPILER}\", \"@${_dat_flags}\", \"-c\", \"${_source}\", \"-o\", \"${_base}\"]}")
endforeach()

# The sources and objects only units with samples have: ninja isn't told of
# them as outputs, since it would rebuild the units without, so the clean
# target removes them instead
set_property(DIRECTORY APPEND PROPERTY ADDITIONAL_CLEAN_FILES ${_dat_optional})

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

# The native archive interface (tools/dat-cli/native): the archives read
# into the game's own types on the host, from this build's types, with its
# unit and end-to-end tests, which `ctest` runs from here. A project of its
# own, since this one targets the GameCube
set(MELEE_DAT_NATIVE ON CACHE BOOL "Build and test the native archive interface")
if(MELEE_DAT_NATIVE)
    include(ExternalProject)
    find_program(MELEE_HOST_CC NAMES cc gcc clang REQUIRED
        DOC "The host's C compiler, for the native archive interface")
    add_custom_target(dat-types DEPENDS types.bin "${_dat_tool}")
    ExternalProject_Add(dat-native
        SOURCE_DIR "${CMAKE_SOURCE_DIR}/tools/dat-cli/native"
        BINARY_DIR "${CMAKE_CURRENT_BINARY_DIR}/native"
        CMAKE_ARGS
            "-DCMAKE_C_COMPILER=${MELEE_HOST_CC}"
            "-DMELEE_DAT=${_dat_tool}"
            "-DMELEE_DAT_TYPES=${CMAKE_CURRENT_BINARY_DIR}/types.bin"
            "-DMELEE_DAT_FILES=${MELEE_DAT_FILES}"
            "-DMELEE_VERSION=${MELEE_VERSION}"
            "-DMELEE_VERSION_NUM=${MELEE_VERSION_NUM}"
            "-DAURORA_SRC=${AURORA_SRC}"
        BUILD_ALWAYS ON
        INSTALL_COMMAND ""
        DEPENDS dat-types
    )
    enable_testing()
    add_test(NAME dat-native
        COMMAND "${CMAKE_CTEST_COMMAND}" --test-dir native --output-on-failure)
endif()
