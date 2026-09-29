# Cross-compile for the GameCube's 32-bit big-endian PowerPC ABI with clang.
# The C library headers come from newlib; nothing is linked against it.
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR powerpc)

set(CMAKE_C_COMPILER clang)
set(CMAKE_C_COMPILER_TARGET ppc32-none-eabi)
set(CMAKE_AR llvm-ar)
set(CMAKE_RANLIB llvm-ranlib)
set(CMAKE_LINKER ld.lld)

# There is no C runtime to link a test executable against
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

set(NEWLIB_INCLUDE "" CACHE PATH "newlib include directory for powerpc-none-eabi")
if(NEWLIB_INCLUDE)
    set(CMAKE_C_STANDARD_INCLUDE_DIRECTORIES "${NEWLIB_INCLUDE}")
endif()
