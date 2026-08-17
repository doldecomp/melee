cmake_minimum_required(VERSION 3.20)

project(melee-native LANGUAGES C)

include(GNUInstallDirs)

set(SOURCES
    src/sysdolphin/baselib/aobj.c
    src/sysdolphin/baselib/archive.c
    src/sysdolphin/baselib/axdriver.c
    src/sysdolphin/baselib/bytecode.c
    src/sysdolphin/baselib/class.c
    src/sysdolphin/baselib/cobj.c
    src/sysdolphin/baselib/controller.c
    src/sysdolphin/baselib/devcom.c
    src/sysdolphin/baselib/dobj.c
    src/sysdolphin/baselib/fobj.c
    src/sysdolphin/baselib/gobj.c
    src/sysdolphin/baselib/gobjgxlink.c
    src/sysdolphin/baselib/gobjobject.c
    src/sysdolphin/baselib/gobjplink.c
    src/sysdolphin/baselib/gobjproc.c
    src/sysdolphin/baselib/gobjuserdata.c
    src/sysdolphin/baselib/hash.c
    src/sysdolphin/baselib/id.c
    src/sysdolphin/baselib/initialize.c
    src/sysdolphin/baselib/jobj.c
    src/sysdolphin/baselib/leak.c
    src/sysdolphin/baselib/list.c
    src/sysdolphin/baselib/lobj.c
    src/sysdolphin/baselib/mobj.c
    src/sysdolphin/baselib/mtx.c
    src/sysdolphin/baselib/objalloc.c
    src/sysdolphin/baselib/object.c
    src/sysdolphin/baselib/perf.c
    src/sysdolphin/baselib/psappsrt.c
    src/sysdolphin/baselib/psdisptev.c
    src/sysdolphin/baselib/quatlib.c
    src/sysdolphin/baselib/random.c
    src/sysdolphin/baselib/robj.c
    src/sysdolphin/baselib/rumble.c
    src/sysdolphin/baselib/shadow.c
    src/sysdolphin/baselib/state.c
    src/sysdolphin/baselib/tev.c
    src/sysdolphin/baselib/texp.c
    src/sysdolphin/baselib/texpdag.c
    src/sysdolphin/baselib/tobj.c
    src/sysdolphin/baselib/util.c
    src/sysdolphin/baselib/wobj.c
)

add_library(melee STATIC ${SOURCES})

target_compile_definitions(melee PRIVATE)

target_include_directories(melee PRIVATE
    $ENV{AURORA_SRC}/include
    src
    src/Runtime
    src/melee
    src/melee/ft/chara
    src/sysdolphin
)

install(TARGETS melee LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}")
