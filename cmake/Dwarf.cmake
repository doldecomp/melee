# Debug build of the game against the original 32-bit big-endian ABI, linked
# into a single ELF so the type information can be read without relocations
include_guard(GLOBAL)

# LINT enables the same layout-affecting pragmas as MUST_MATCH without its
# MWCC-specific code, and turns ASSERT_SIZE/ASSERT_OFFSET into static asserts
# The game version: its defines can change code paths and types, so each
# version has its own DWARF. Same list and numbering as configure.py's
# VERSIONS
set(MELEE_VERSIONS GALE01)
set(MELEE_VERSION GALE01 CACHE STRING "Game version (${MELEE_VERSIONS})")
list(FIND MELEE_VERSIONS "${MELEE_VERSION}" MELEE_VERSION_NUM)
if(MELEE_VERSION_NUM EQUAL -1)
    message(FATAL_ERROR "Unknown MELEE_VERSION ${MELEE_VERSION}; one of: ${MELEE_VERSIONS}")
endif()

if(NOT NEWLIB_INCLUDE)
    message(FATAL_ERROR "NEWLIB_INCLUDE is not set: configure from the native dev shell (nix develop .#native)")
endif()

target_compile_definitions(melee PRIVATE
    LINT
    DAT_ANNOTATIONS
    VERSION_${MELEE_VERSION}
    BUILD_VERSION=${MELEE_VERSION_NUM}
)
target_compile_options(melee PRIVATE
    # Aurora's headers in their console layout, like the game's: TARGET_PC
    # makes GXBool a bool (an int, with bool=int) and grows GXTexObj and
    # GXTlutObj
    -UTARGET_PC
    # Before C23, <stdbool.h> redefines bool as the 1-byte _Bool, overriding
    # bool=int and shrinking every bool field relative to MWCC
    -std=gnu23
    -O0
    -g3
    -gdwarf-5
    -fdebug-macro
    -fno-eliminate-unused-debug-types
)

add_custom_command(
    OUTPUT melee.elf
    COMMAND "${CMAKE_LINKER}"
        --whole-archive "$<TARGET_FILE:melee>" --no-whole-archive
        --unresolved-symbols=ignore-all
        --allow-multiple-definition
        --noinhibit-exec
        -o melee.elf
    DEPENDS melee
    COMMENT "Linking melee.elf"
    VERBATIM
)
add_custom_target(melee_elf ALL DEPENDS melee.elf)

install(FILES "${CMAKE_CURRENT_BINARY_DIR}/melee.elf" DESTINATION .)
install(
    DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/CMakeFiles/melee.dir/src/"
    DESTINATION obj
    FILES_MATCHING PATTERN "*${CMAKE_C_OUTPUT_EXTENSION}"
)
