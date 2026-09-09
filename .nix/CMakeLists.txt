cmake_minimum_required(VERSION 3.20)

project(melee-native LANGUAGES C)

include(GNUInstallDirs)

file(GLOB_RECURSE SOURCES "src/melee/**.c" LIST_DIRECTORIES FALSE)
file(GLOB_RECURSE HSD_SOURCES "src/sysdolphin/**.c" LIST_DIRECTORIES FALSE)
set(SOURCES ${SOURCES} ${HSD_SOURCES})

add_compile_definitions(TARGET_PC)

add_compile_definitions(bool=int)

list(FILTER SOURCES EXCLUDE REGEX "dberror.c") # OSContext register usage
list(FILTER SOURCES EXCLUDE REGEX "debug.c") # PPC register usage
list(FILTER SOURCES EXCLUDE REGEX "debugconsole_main.c") # PPC register usage
list(FILTER SOURCES EXCLUDE REGEX "fog.c") # GXInitFogAdjTable
list(FILTER SOURCES EXCLUDE REGEX "gmmain.c") # CARDInit
list(FILTER SOURCES EXCLUDE REGEX "hsd_3915.c") # requires debug font from dol
list(FILTER SOURCES EXCLUDE REGEX "lb_0195.c") # PADSetSamplingRate
list(FILTER SOURCES EXCLUDE REGEX "lb_01F8.c") # needs dolphin/thp
list(FILTER SOURCES EXCLUDE REGEX "lbcardnew.c") # CARD ASync
list(FILTER SOURCES EXCLUDE REGEX "lbmthp.c") # needs dolphin/thp
list(FILTER SOURCES EXCLUDE REGEX "pobj.c") # nontrivial GXSetArray usage
list(FILTER SOURCES EXCLUDE REGEX "sislib_font.c") # requires font from dol
list(FILTER SOURCES EXCLUDE REGEX "video.c") # needs VIPadFrameBufferWidth


add_library(melee STATIC ${SOURCES})

target_include_directories(melee PRIVATE
    $ENV{AURORA_SRC}/include
    src
)

install(TARGETS melee LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}")
