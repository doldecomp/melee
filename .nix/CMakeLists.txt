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
    src/melee/gm/gm_16F1.c
    src/melee/gm/gm_17AD.c
    src/melee/gm/gm_17BA.c
    src/melee/gm/gm_19EF.c
    src/melee/gm/gm_1A33.c
    src/melee/gm/gm_1A36.c
    src/melee/gm/gm_1A3F.c
    src/melee/gm/gm_1A7A.c
    src/melee/gm/gm_1A9B.c
    src/melee/gm/gm_1AED.c
    src/melee/gm/gm_1B03.c
    src/melee/gm/gm_1B0FB.c
    src/melee/gm/gm_1B14.c
    src/melee/gm/gm_1BA8.c
    src/melee/gm/gm_1BF9.c
    src/melee/gm/gm_1BFA.c
    src/melee/gm/gmallstar.c
    src/melee/gm/gmapproach.c
    src/melee/gm/gmcamera.c
    src/melee/gm/gmclassic.c
    src/melee/gm/gmfixedcamera.c
    src/melee/gm/gmgiant.c
    src/melee/gm/gmhomerun.c
    src/melee/gm/gmhowto.c
    src/melee/gm/gminvisible.c
    src/melee/gm/gmlightning.c
    src/melee/gm/gmmain.c
    src/melee/gm/gmmenu.c
    src/melee/gm/gmmovieend.c
    src/melee/gm/gmmultiman.c
    src/melee/gm/gmomake15.c
    src/melee/gm/gmopening.c
    src/melee/gm/gmprogressive.c
    src/melee/gm/gmregcommon.c
    src/melee/gm/gmregenddisp.c
    src/melee/gm/gmresult.c
    src/melee/gm/gmscdata.c
    src/melee/gm/gmsinglebutton.c
    src/melee/gm/gmslomo.c
    src/melee/gm/gmstamina.c
    src/melee/gm/gmsupersudden.c
    src/melee/gm/gmtiny.c
    src/melee/gm/gmtitle.c
    src/melee/gm/gmtou_0.c
    src/melee/gm/gmtou_1.c
    src/melee/gm/gmtou_2.c
    src/melee/gm/gmvsdata.c
    src/melee/gm/gmvsmelee.c
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
