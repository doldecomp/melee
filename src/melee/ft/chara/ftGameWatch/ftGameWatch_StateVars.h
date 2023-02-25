#ifndef _FTGAMEWATCH_STATEVARS_H_
#define _FTGAMEWATCH_STATEVARS_H_

#include <Runtime/platform.h>
#include <sysdolphin/baselib/gobj.h>

typedef struct ftGameWatchAttack11 {
    bool unk; // 0x2340 - Set to 0 but never used?

} ftGameWatchAttack11;

typedef struct ftGameWatchSpecialN {
    bool isChefLoopDisable; // 0x2340
    s32 maxSausage; // 0x2344 - Maximum number of sausages able to be spawned
                    // per Chef use

} ftGameWatchSpecialN;

typedef struct ftGameWatchSpecialLw {
    bool isRelease; // 0x2340 - bool to check if Mr. Game & Watch is no longer
                    // holding B
    s32 turnFrames; // 0x2344 - Number of frames it takes Mr. Game & Watch to
                    // turn around on command

} ftGameWatchSpecialLw;

typedef union ftGameWatchVars {
    ftGameWatchAttack11 Attack11;
    ftGameWatchSpecialN SpecialN;
    ftGameWatchSpecialLw SpecialLw;

} ftGameWatchStateVars;

#endif
