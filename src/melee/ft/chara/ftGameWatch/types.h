#ifndef MELEE_FT_CHARA_FTGAMEWATCH_TYPES_H
#define MELEE_FT_CHARA_FTGAMEWATCH_TYPES_H

#include <platform.h>
#include <baselib/forward.h>

#include <common_structs.h>

typedef union ftGameWatch_MotionVars {
    struct ftGameWatch_Attack11Vars {
        bool unk; // 0x2340 - Set to 0 but never used?
    } Attack11;

    struct ftGameWatch_SpecialNVars {
        // 0x2340
        bool isChefLoopDisable;
        /// 0x2344 - Maximum number of sausages able to be spawned per Chef use
        s32 maxSausage;
    } SpecialN;

    struct ftGameWatch_SpecialLwVars {
        // 0x2340 - bool to check if Mr. Game & Watch is no longer holding B
        bool isRelease;
        //// 0x2344 - Number of frames it takes Mr. Game & Watch to turn around
        /// on
        /// command
        s32 turnFrames;
    } SpecialLw;
} ftGameWatch_MotionVars;

#endif
