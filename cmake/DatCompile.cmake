# Builds a unit's base object; run by Dat.cmake's compile step with -P, in
# the build directory.
#   C_COMPILER  the compiler, with its flags in the response file FLAGS
#   LINKER      the linker
#   SOURCE      src/<unit>.c, which a unit with no samples doesn't have
#   HEADER      src/<unit>.h
#   OBJECT      obj/<unit>.o, the compiled samples
#   LAYOUT      target/<unit>.ld
#   REST        target/<unit>.rest.o, the inferred data
#   BASE        base/<unit>.o
#   DEPFILE     its dependencies
cmake_minimum_required(VERSION 3.20)

if(EXISTS "${SOURCE}")
    # Each sample in its own section, then linked into .data in the target's
    # order: clang lays variables out where an initializer first points to
    # them
    execute_process(
        COMMAND "${C_COMPILER}" "@${FLAGS}" -fdata-sections
            -MD -MF "${DEPFILE}" -MT "${BASE}" -c "${SOURCE}" -o "${OBJECT}"
        COMMAND_ERROR_IS_FATAL ANY
    )
    set(_inputs "${OBJECT}" "${REST}")
else()
    # No samples: the inferred data alone
    file(WRITE "${DEPFILE}" "${BASE}: ${HEADER}\n")
    file(REMOVE "${OBJECT}")
    set(_inputs "${REST}")
endif()
execute_process(
    COMMAND "${LINKER}" -r -T "${LAYOUT}" ${_inputs} -o "${BASE}"
    COMMAND_ERROR_IS_FATAL ANY
)
