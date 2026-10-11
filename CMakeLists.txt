cmake_minimum_required(VERSION 3.20)

# configure.py writes build.ninja to the source root, so configuring here
# would clobber the matching build
if(CMAKE_SOURCE_DIR STREQUAL CMAKE_BINARY_DIR)
    message(FATAL_ERROR
        "In-source builds are not supported; use a preset "
        "(cmake --preset native) or a separate binary directory")
endif()

project(melee LANGUAGES C)

include(GNUInstallDirs)

option(MELEE_DAT_READERS "Build generated archive readers with the native game" OFF)

option(MELEE_DWARF "Emit DWARF describing the original type layouts" OFF)
option(MELEE_DAT_SAMPLES "Sample the .dat archives' types for objdiff (needs MELEE_DWARF)" OFF)

include(cmake/MeleeConfig.cmake)

if(MELEE_DWARF)
    include(cmake/Dwarf.cmake)
endif()

if(MELEE_DAT_SAMPLES)
    include(cmake/Dat.cmake)
endif()

if(NOT MELEE_DWARF)
    if(MELEE_DAT_READERS)
        enable_testing()
        add_subdirectory(tools/dat-cli/native dat-readers)
    endif()
    # TARGET_PC requires the readers, built here or supplied by the consumer.
    target_link_libraries(melee PUBLIC dat_hsd)
    # Match the generated readers' bool=int header layout.
    set_target_properties(melee PROPERTIES C_STANDARD 23 C_EXTENSIONS ON)
endif()

install(TARGETS melee LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}")
