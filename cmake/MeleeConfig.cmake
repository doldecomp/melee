# Game sources and the headers/definitions they are built against
include_guard(GLOBAL)

get_filename_component(_melee_root "${CMAKE_CURRENT_LIST_DIR}/.." ABSOLUTE)

# From the dev shell's environment when it has it, else as cached: ninja
# re-runs CMake from wherever it is started (e.g. objdiff)
if(DEFINED ENV{AURORA_SRC})
    set(AURORA_SRC "$ENV{AURORA_SRC}" CACHE PATH "Aurora's source" FORCE)
endif()
if(NOT AURORA_SRC)
    message(FATAL_ERROR "AURORA_SRC is not set: configure from the dev shell")
endif()

add_library(melee_game_headers INTERFACE)
target_include_directories(melee_game_headers INTERFACE
    ${AURORA_SRC}/include
    ${_melee_root}/src
    ${_melee_root}/libs/doldecomp/include
)
target_compile_definitions(melee_game_headers INTERFACE
    TARGET_PC
    bool=int
)

file(GLOB_RECURSE SOURCES "${_melee_root}/src/melee/**.c" LIST_DIRECTORIES FALSE)
file(GLOB_RECURSE HSD_SOURCES "${_melee_root}/src/sysdolphin/**.c" LIST_DIRECTORIES FALSE)
set(SOURCES ${SOURCES} ${HSD_SOURCES})

set(EXCLUSIONS
    melee/db/dberror.c # OSContext register usage
    melee/gm/gmmain.c # CARDInit
    melee/lb/lb_0195.c # PADSetSamplingRate
    melee/lb/lb_01F8.c # needs dolphin/thp
    melee/lb/lbcardnew.c # CARD ASync
    melee/lb/lbmthp.c # needs dolphin/thp
    sysdolphin/baselib/debug.c # PPC register usage
    sysdolphin/baselib/debugconsole_main.c # PPC register usage
    sysdolphin/baselib/fog.c # GXInitFogAdjTable
    sysdolphin/baselib/hsd_3915.c # requires debug font from dol
    sysdolphin/baselib/pobj.c # nontrivial GXSetArray usage
    sysdolphin/baselib/sislib_font.c # requires font from dol
    sysdolphin/baselib/video.c # needs VIPadFrameBufferWidth
)

foreach(_exclusion IN LISTS EXCLUSIONS)
    list(REMOVE_ITEM SOURCES "${_melee_root}/src/${_exclusion}")
endforeach()

add_library(melee STATIC ${SOURCES})
target_link_libraries(melee PRIVATE melee_game_headers)
