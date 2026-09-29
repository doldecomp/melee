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

option(MELEE_DWARF "Emit DWARF describing the original type layouts" OFF)

include(cmake/MeleeConfig.cmake)

if(MELEE_DWARF)
    include(cmake/Dwarf.cmake)
endif()

install(TARGETS melee LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}")
