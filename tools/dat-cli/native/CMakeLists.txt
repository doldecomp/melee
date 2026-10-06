# The native archive interface: reads the game's archives into its own C
# types on the host, whatever its byte order and pointer size.
#
# The schema comes from `melee-dat native codegen`, from the types the dat
# build exports (`types.bin`): a descriptor for each type, in a file for
# each header of the game's, in schema/ here. The end-to-end test compares
# the library's walk with `melee-dat native expect` over the game's files:
#
#   cmake -S tools/dat-cli/native -B build/native/x86_64
#   cmake --build build/native/x86_64 && ctest --test-dir build/native/x86_64
#
# For other targets, a toolchain file: `toolchains/i686.cmake` (32-bit
# little-endian), `toolchains/ppc32-linux.cmake` (32-bit big-endian, run
# under qemu).
cmake_minimum_required(VERSION 3.25)
project(dat_native C)

get_filename_component(MELEE_ROOT "${CMAKE_CURRENT_LIST_DIR}/../../.." ABSOLUTE)

# The game's headers as the port builds them (see cmake/MeleeConfig.cmake)
if(DEFINED ENV{AURORA_SRC})
    set(AURORA_SRC "$ENV{AURORA_SRC}" CACHE PATH "Aurora's source" FORCE)
endif()
if(NOT AURORA_SRC)
    message(FATAL_ERROR "AURORA_SRC is not set: configure from the native dev shell")
endif()
add_library(melee_game_headers INTERFACE)
target_include_directories(melee_game_headers INTERFACE
    ${AURORA_SRC}/include
    ${MELEE_ROOT}/src
    ${MELEE_ROOT}/libs/doldecomp/include
)
target_compile_definitions(melee_game_headers INTERFACE TARGET_PC bool=int)

set(MELEE_VERSION GALE01 CACHE STRING "Game version")
set(MELEE_VERSION_NUM 0 CACHE STRING "BUILD_VERSION for MELEE_VERSION")
set(MELEE_DAT_TYPES "${MELEE_ROOT}/build/${MELEE_VERSION}/dat/types.bin"
    CACHE FILEPATH "The types the dat build exports")
set(MELEE_DAT_FILES "${MELEE_ROOT}/orig/${MELEE_VERSION}/files"
    CACHE PATH "The game's files")
set(MELEE_DAT "" CACHE FILEPATH "melee-dat binary; built with cargo if empty")

if(NOT EXISTS "${MELEE_DAT_TYPES}")
    message(FATAL_ERROR
        "No types at MELEE_DAT_TYPES (${MELEE_DAT_TYPES}): build the dat "
        "preset first, or point it at a types.bin")
endif()

set(_dat_config
    "${MELEE_ROOT}/config/${MELEE_VERSION}/dat.yml"
    "${MELEE_ROOT}/config/${MELEE_VERSION}/dat_symbols.txt")

# The schema is generated when configuring, since which files it has depends
# on the types; a change to what it is generated from configures again
if(MELEE_DAT)
    set(_dat_tool "${MELEE_DAT}")
else()
    set(_dat_tool "${CMAKE_CURRENT_BINARY_DIR}/cargo/release/melee-dat")
    find_program(MELEE_CARGO cargo REQUIRED)
    file(GLOB_RECURSE _dat_sources CONFIGURE_DEPENDS
        "${MELEE_ROOT}/tools/dat-cli/src/*.rs")
    set_property(DIRECTORY APPEND PROPERTY CMAKE_CONFIGURE_DEPENDS
        ${_dat_sources} "${MELEE_ROOT}/tools/dat-cli/Cargo.toml")
    message(STATUS "Building melee-dat")
    execute_process(
        COMMAND "${MELEE_CARGO}" build --release
            --manifest-path "${MELEE_ROOT}/tools/dat-cli/Cargo.toml"
            --target-dir "${CMAKE_CURRENT_BINARY_DIR}/cargo"
        COMMAND_ERROR_IS_FATAL ANY
    )
endif()

set(_dat_schema "${CMAKE_CURRENT_BINARY_DIR}/schema")
message(STATUS "Generating the schema in ${_dat_schema}")
execute_process(
    COMMAND "${_dat_tool}" native codegen
        "${MELEE_ROOT}/config/${MELEE_VERSION}/dat.yml"
        -p "${MELEE_ROOT}" --types "${MELEE_DAT_TYPES}"
        --files "${MELEE_DAT_FILES}" --out-dir "${_dat_schema}"
    COMMAND_ERROR_IS_FATAL ANY
)
set_property(DIRECTORY APPEND PROPERTY CMAKE_CONFIGURE_DEPENDS
    "${_dat_tool}" "${MELEE_DAT_TYPES}" ${_dat_config})
file(GLOB_RECURSE _dat_schema_sources "${_dat_schema}/*.c")

# The generated C isn't the repository's to tidy
file(WRITE "${_dat_schema}/.clang-tidy" "Checks: '-*'\n")

add_library(dat_native STATIC src/archive.c)
target_include_directories(dat_native PUBLIC include)
set_target_properties(dat_native PROPERTIES C_STANDARD 11 C_EXTENSIONS ON)
if(NOT MSVC)
    target_compile_options(dat_native PRIVATE -Wall -Wextra)
    target_link_libraries(dat_native PUBLIC m)
endif()

# The schema, compiled against the game's headers as the port builds them
add_library(dat_melee STATIC ${_dat_schema_sources})
target_include_directories(dat_melee PUBLIC "${_dat_schema}")
target_link_libraries(dat_melee PUBLIC dat_native PRIVATE melee_game_headers)
target_compile_definitions(dat_melee PRIVATE
    VERSION_${MELEE_VERSION}
    BUILD_VERSION=${MELEE_VERSION_NUM}
)
# Before C23, <stdbool.h> redefines bool as the 1-byte _Bool, overriding
# bool=int
set_target_properties(dat_melee PROPERTIES C_STANDARD 23 C_EXTENSIONS ON)
target_compile_options(dat_melee PRIVATE -w)

enable_testing()

add_executable(dat_unit tests/unit.c)
target_link_libraries(dat_unit PRIVATE dat_native)
set_target_properties(dat_unit PROPERTIES C_STANDARD 11 C_EXTENSIONS ON)
add_test(NAME unit COMMAND dat_unit)

add_executable(dat_raw_refs tests/raw_refs.c)
target_link_libraries(dat_raw_refs PRIVATE dat_native)
set_target_properties(dat_raw_refs PROPERTIES C_STANDARD 11 C_EXTENSIONS ON)
add_test(NAME raw_refs COMMAND dat_raw_refs)

add_executable(dat_array_refs tests/array_refs.c)
target_link_libraries(dat_array_refs PRIVATE dat_native)
set_target_properties(dat_array_refs PROPERTIES C_STANDARD 11 C_EXTENSIONS ON)
add_test(NAME array_refs COMMAND dat_array_refs)

add_custom_command(
    OUTPUT expect.txt
    COMMAND "${_dat_tool}" native expect
        "${MELEE_ROOT}/config/${MELEE_VERSION}/dat.yml"
        -p "${MELEE_ROOT}" --types "${MELEE_DAT_TYPES}"
        --files "${MELEE_DAT_FILES}" > expect.txt
    DEPENDS "${_dat_tool}" "${MELEE_DAT_TYPES}" ${_dat_config}
    COMMENT "Walking the archives with melee-dat"
)
add_custom_target(dat_expect ALL DEPENDS expect.txt)

add_executable(dat_e2e tests/e2e.c)
target_link_libraries(dat_e2e PRIVATE dat_melee)
set_target_properties(dat_e2e PROPERTIES C_STANDARD 11 C_EXTENSIONS ON)
add_test(NAME e2e
    COMMAND dat_e2e "${CMAKE_CURRENT_BINARY_DIR}/expect.txt"
        "${MELEE_DAT_FILES}")

# The game's own types, read through C's member access
add_executable(dat_types tests/types.c)
target_link_libraries(dat_types PRIVATE dat_melee melee_game_headers)
target_compile_definitions(dat_types PRIVATE
    VERSION_${MELEE_VERSION}
    BUILD_VERSION=${MELEE_VERSION_NUM}
)
set_target_properties(dat_types PROPERTIES C_STANDARD 23 C_EXTENSIONS ON)
target_compile_options(dat_types PRIVATE -w)
add_test(NAME types COMMAND dat_types "${MELEE_DAT_FILES}")
