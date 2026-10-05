# Formats a unit's generated C (src/<unit>.h, and src/<unit>.c if it has
# samples) in place, then writes a stamp; run by Dat.cmake's format step with
# -P.
#   CLANG_FORMAT  clang-format
#   STYLE         the .clang-format file
#   UNIT          src/<unit>, without an extension
#   STAMP         metadata/<unit>.formatted, written after formatting so that
#                 it is newer than the sources
cmake_minimum_required(VERSION 3.20)

set(_files "${UNIT}.h")
if(EXISTS "${UNIT}.c")
    list(APPEND _files "${UNIT}.c")
endif()

execute_process(
    COMMAND "${CLANG_FORMAT}" "--style=file:${STYLE}" -i ${_files}
    COMMAND_ERROR_IS_FATAL ANY
)
file(TOUCH "${STAMP}")
