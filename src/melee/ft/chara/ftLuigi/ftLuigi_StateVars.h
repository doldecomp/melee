#ifndef _FTLUIGI_STATEVARS_H_
#define _FTLUIGI_STATEVARS_H_

#include <baselib/gobj.h>
#include <platform.h>

typedef struct ftLuigiSpecialS {
    s32 chargeFrames; // 0x2340 - Number of frames Green Missile has been
                      // charged
    bool isMisfire;   // 0x2344 - Check if Green Missile will misfire

} ftLuigiSpecialS;

typedef struct ftLuigiSpecialLw {
    f32 groundVelX; // 0x2340 - Grounded momentum of Luigi Cyclone
    s32 unk;        // 0x2344 - Set but never used?
    s32 _;          // 0x2348 - Skipped entirely
    bool isUnkColl; // 0x234C - Checked in collision, related to some angle
                    // calculation

} ftLuigiSpecialLw;

typedef union ftLuigiStateVars {
    ftLuigiSpecialS SpecialS;
    ftLuigiSpecialLw SpecialLw;

} ftLuigiStateVars;

#endif
