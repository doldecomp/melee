cmake_minimum_required(VERSION 3.20)

project(melee-native LANGUAGES C)

include(GNUInstallDirs)

file(GLOB_RECURSE SOURCES "src/melee/**.c" LIST_DIRECTORIES FALSE)
file(GLOB_RECURSE HSD_SOURCES "src/sysdolphin/**.c" LIST_DIRECTORIES FALSE)
set(SOURCES ${SOURCES} ${HSD_SOURCES})

add_compile_definitions(TARGET_PC)

add_compile_definitions(bool=int)

set(EXCLUSIONS
    "melee/db/dberror.c" # OSContext register usage
    "melee/gm/gmmain.c" # CARDInit
    "melee/lb/lb_0195.c" # PADSetSamplingRate
    "melee/lb/lb_01F8.c" # needs dolphin/thp
    "melee/lb/lbcardnew.c" # CARD ASync
    "melee/lb/lbmthp.c" # needs dolphin/thp
    "sysdolphin/baselib/debug.c" # PPC register usage
    "sysdolphin/baselib/debugconsole_main.c" # PPC register usage
    "sysdolphin/baselib/fog.c" # GXInitFogAdjTable
    "sysdolphin/baselib/hsd_3915.c" # requires debug font from dol
    "sysdolphin/baselib/pobj.c" # nontrivial GXSetArray usage
    "sysdolphin/baselib/sislib_font.c" # requires font from dol
    "sysdolphin/baselib/video.c" # needs VIPadFrameBufferWidth
)

foreach(_exclusion IN LISTS EXCLUSIONS)
    list(REMOVE_ITEM SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/${_exclusion}")
endforeach()

add_library(melee STATIC ${SOURCES})

target_include_directories(melee PRIVATE
    $ENV{AURORA_SRC}/include
    src
)

install(TARGETS melee LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}")
