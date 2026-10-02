# Cross-compile for the GameCube's 32-bit big-endian PowerPC ABI with clang.
# The C library headers come from newlib; nothing is linked against it.
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR powerpc)

set(CMAKE_C_COMPILER clang)
set(CMAKE_C_COMPILER_TARGET ppc32-none-eabi)
# By absolute path, so that the build doesn't need the dev shell's PATH
find_program(MELEE_LLVM_AR llvm-ar REQUIRED)
find_program(MELEE_LLVM_RANLIB llvm-ranlib REQUIRED)
find_program(MELEE_LLD ld.lld REQUIRED)
set(CMAKE_AR "${MELEE_LLVM_AR}")
set(CMAKE_RANLIB "${MELEE_LLVM_RANLIB}")
set(CMAKE_LINKER "${MELEE_LLD}")

# There is no C runtime to link a test executable against
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

# From the dev shell's environment when it has it, else as cached: ninja
# re-runs CMake from wherever it is started (e.g. objdiff)
set(_doc "newlib include directory for powerpc-none-eabi")
if(DEFINED ENV{NEWLIB_INCLUDE})
    set(NEWLIB_INCLUDE "$ENV{NEWLIB_INCLUDE}" CACHE PATH "${_doc}" FORCE)
else()
    set(NEWLIB_INCLUDE "" CACHE PATH "${_doc}")
endif()
if(NEWLIB_INCLUDE)
    set(CMAKE_C_STANDARD_INCLUDE_DIRECTORIES "${NEWLIB_INCLUDE}")
endif()
