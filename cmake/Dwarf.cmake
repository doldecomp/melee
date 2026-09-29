# Debug build of the game against the original 32-bit big-endian ABI, linked
# into a single ELF so the type information can be read without relocations
include_guard(GLOBAL)

# LINT enables the same layout-affecting pragmas as MUST_MATCH without its
# MWCC-specific code, and turns ASSERT_SIZE/ASSERT_OFFSET into static asserts
target_compile_definitions(melee PRIVATE
    LINT
    VERSION_GALE01
    BUILD_VERSION=0
)
target_compile_options(melee PRIVATE
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
