# Samples of the .dat archives' data, typed by the DWARF build and compared
# with objdiff (see tools/dat-cli). Each archive is a unit, built in four
# steps: slice (archive → target/<unit>.o), codegen (→ gen/<unit>.c, which
# includes a header and source per root in gen/<unit>/), format (→ src/)
# and compile (→ base/<unit>.o). The build directory is also the objdiff
# project.
include_guard(GLOBAL)

if(NOT MELEE_DWARF)
    message(FATAL_ERROR "MELEE_DAT_SAMPLES needs MELEE_DWARF: the samples are typed by its DWARF")
endif()

set(MELEE_DAT "" CACHE FILEPATH "melee-dat binary; built with cargo if empty")
set(MELEE_DAT_FILES "${CMAKE_SOURCE_DIR}/orig/${MELEE_VERSION}/files"
    CACHE PATH "The game's files, with its .dat archives")

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
    add_custom_command(
        OUTPUT "${_dat_tool}"
        COMMAND cargo build --release -p melee-dat
            --manifest-path "${CMAKE_SOURCE_DIR}/Cargo.toml"
            --target-dir "${CMAKE_CURRENT_BINARY_DIR}/cargo"
        DEPFILE "${_dat_tool}.d"
        COMMENT "Building melee-dat"
        VERBATIM
    )
endif()

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

file(GLOB _dat_archives CONFIGURE_DEPENDS "${MELEE_DAT_FILES}/*.dat")
set(_dat_sidecars)
set(_dat_bases)
set(_dat_commands)
foreach(_archive IN LISTS _dat_archives)
    get_filename_component(_file "${_archive}" NAME)
    get_filename_component(_unit "${_archive}" NAME_WE)
    set(_target "target/${_unit}.o")
    set(_sidecar "target/${_unit}.samples")
    set(_generated "gen/${_unit}.c")
    set(_source "src/${_unit}.c")
    set(_base "base/${_unit}.o")

    add_custom_command(
        OUTPUT "${_target}" "${_sidecar}"
        COMMAND "${_dat_tool}" samples slice "${_file}" "${_dat_config}"
            -p "${CMAKE_SOURCE_DIR}" --types types.bin
            --files "${MELEE_DAT_FILES}" -o "${_target}"
        DEPENDS "${_archive}" types.bin "${_dat_tool}" "${_dat_config}"
            "${_dat_symbols}"
        COMMENT "Slicing ${_file}"
        VERBATIM
    )
    add_custom_command(
        OUTPUT "${_generated}"
        COMMAND "${_dat_tool}" samples codegen "${_target}" --types types.bin
            -o "${_generated}"
        DEPENDS "${_target}" "${_sidecar}" types.bin "${_dat_tool}"
        COMMENT "Generating ${_generated}"
        VERBATIM
    )
    add_custom_command(
        OUTPUT "${_source}"
        COMMAND "${CMAKE_COMMAND}"
            "-DCLANG_FORMAT=${MELEE_CLANG_FORMAT}"
            "-DSTYLE=${CMAKE_SOURCE_DIR}/.clang-format"
            "-DGENERATED=${CMAKE_CURRENT_BINARY_DIR}/${_generated}"
            "-DSOURCE=${CMAKE_CURRENT_BINARY_DIR}/${_source}"
            -P "${CMAKE_SOURCE_DIR}/cmake/DatFormat.cmake"
        DEPENDS "${_generated}" "${CMAKE_SOURCE_DIR}/.clang-format"
            "${CMAKE_SOURCE_DIR}/cmake/DatFormat.cmake"
        COMMENT "Formatting ${_source}"
        VERBATIM
    )
    add_custom_command(
        OUTPUT "${_base}"
        COMMAND "${CMAKE_C_COMPILER}" "@${_dat_flags}" -MD -MF "${_base}.d"
            -c "${_source}" -o "${_base}"
        DEPENDS "${_source}" "${_dat_flags}"
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
