#ifndef _FTGAMEWATCH_STATEVARS_H_
#define _FTGAMEWATCH_STATEVARS_H_

#include <Runtime/platform.h>
#include <sysdolphin/baselib/gobj.h>

typedef union ftGameWatch_StateVars {
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
} ftGameWatch_StateVars;

#endif
