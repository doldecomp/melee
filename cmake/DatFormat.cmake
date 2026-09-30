# Formats a unit's generated C (src/<unit>.c and src/<unit>/) in place, then
# writes a stamp; run by Dat.cmake's format step with -P.
#   CLANG_FORMAT  clang-format
#   STYLE         the .clang-format file
#   SOURCE        src/<unit>.c
#   STAMP         stamp/<unit>.formatted, written after formatting so that
#                 it is newer than the sources
cmake_minimum_required(VERSION 3.20)

cmake_path(REMOVE_EXTENSION SOURCE LAST_ONLY OUTPUT_VARIABLE _dir)
file(GLOB _files "${_dir}/*.[ch]")

execute_process(
    COMMAND "${CLANG_FORMAT}" "--style=file:${STYLE}" -i "${SOURCE}" ${_files}
    COMMAND_ERROR_IS_FATAL ANY
)
file(TOUCH "${STAMP}")
