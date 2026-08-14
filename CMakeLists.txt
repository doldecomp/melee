cmake_minimum_required(VERSION 3.20)

project(melee-native LANGUAGES C)

include(GNUInstallDirs)

set(SOURCES
    src/sysdolphin/baselib/jobj.c
    src/sysdolphin/baselib/gobj.c
)

add_library(melee STATIC ${SOURCES})

target_include_directories(melee PRIVATE
    $ENV{AURORA_SRC}/include
    src
    src/Runtime
    src/melee
    src/melee/ft/chara
    src/sysdolphin
)

install(TARGETS melee LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}")
