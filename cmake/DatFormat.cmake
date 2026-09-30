# Copies a unit's generated C (gen/<unit>.c and gen/<unit>/) into src/ and
# formats it; run by Dat.cmake's format step with -P.
#   CLANG_FORMAT  clang-format
#   STYLE         the .clang-format file
#   GENERATED     gen/<unit>.c
#   SOURCE        src/<unit>.c
cmake_minimum_required(VERSION 3.20)

cmake_path(REMOVE_EXTENSION GENERATED LAST_ONLY OUTPUT_VARIABLE _gen_dir)
cmake_path(REMOVE_EXTENSION SOURCE LAST_ONLY OUTPUT_VARIABLE _src_dir)
cmake_path(GET SOURCE PARENT_PATH _src_parent)

# The roots of the previous generation may be gone
file(REMOVE_RECURSE "${_src_dir}")
file(COPY "${_gen_dir}" "${GENERATED}" DESTINATION "${_src_parent}")
file(GLOB _files "${_src_dir}/*.[ch]")

execute_process(
    COMMAND "${CLANG_FORMAT}" "--style=file:${STYLE}" -i "${SOURCE}" ${_files}
    COMMAND_ERROR_IS_FATAL ANY
)
