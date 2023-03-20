#ifndef _FTMARIO_STATEVARS_H_
#define _FTMARIO_STATEVARS_H_

#include <platform.h>
#include <baselib/gobj.h>

typedef struct ftMarioSpecialS {
    /// 0x2340 - bool to check if reflect bubble should be enabled
    bool isReflect;
} ftMarioSpecialS;

typedef struct ftMarioSpecialLw {
    f32 groundVelX; // 0x2340 - Grounded momentum of Mario / Dr. Tornado
    s32 unk;        // 0x2344 - Set but never used?
    s32 _;          // 0x2348 - Skipped entirely
    bool isUnkColl; // 0x234C - Checked in collision, related to some angle
                    // calculation

} ftMarioSpecialLw;

typedef union ftMario_StateVars {
    ftMarioSpecialS SpecialS;
    ftMarioSpecialLw SpecialLw;
} ftMario_StateVars;

#endif
