# 32-bit big-endian: the archives' own byte order and pointer size, as
# PowerPC Linux binaries run under qemu's user mode (the native dev shell
# has both), with the cross compiler's C library as qemu's sysroot.
set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR ppc)
set(CMAKE_C_COMPILER powerpc-unknown-linux-gnu-gcc)
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
find_program(QEMU_PPC qemu-ppc REQUIRED)
execute_process(
    COMMAND "${CMAKE_C_COMPILER}" -print-file-name=libc.so.6
    OUTPUT_VARIABLE _libc OUTPUT_STRIP_TRAILING_WHITESPACE)
get_filename_component(_sysroot "${_libc}" DIRECTORY)
get_filename_component(_sysroot "${_sysroot}" DIRECTORY)
set(CMAKE_CROSSCOMPILING_EMULATOR "${QEMU_PPC};-L;${_sysroot}")
