#ifndef _FTMARIO_STATEVARS_H_
#define _FTMARIO_STATEVARS_H_

#include <Runtime/platform.h>
#include <sysdolphin/baselib/gobj.h>

typedef struct ftMarioSpecialS {
    bool
        isReflect; // 0x2340 - bool to check if reflect bubble should be enabled

} ftMarioSpecialS;

typedef struct ftMarioSpecialLw {
    f32 groundVelX; // 0x2340 - Grounded momentum of Mario / Dr. Tornado
    s32 unk;        // 0x2344 - Set but never used?
    s32 unused;     // 0x2348 - Skipped entirely
    bool isUnkColl; // 0x234C - Checked in collision, related to some angle
                    // calculation

} ftMarioSpecialLw;

typedef union ftMarioStateVars {
    ftMarioSpecialS SpecialS;
    ftMarioSpecialLw SpecialLw;

} ftMarioStateVars;

#endif
