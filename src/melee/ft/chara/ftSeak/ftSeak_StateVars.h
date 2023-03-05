#ifndef _FTSEAK_STATEVARS_H_
#define _FTSEAK_STATEVARS_H_

#include <Runtime/platform.h>
#include <sysdolphin/baselib/gobj.h>

typedef struct ftSeakSpecialN {
    s32 x2340;
    s32 x2344;
    s32 x2348;
    s32 x234C;
    s32 x2350;
    s32 x2354;
    s32 x2358;
    s32 x235C;
    s32 x2360;
    s32 x2364;
    s32 x2368;
    s32 x236C;

} ftSeakSpecialN;

typedef struct ftSeakSpecialS {
    s32 x2340;
    s32 x2344;
    s32 x2348;
    s32 x234C;
    s32 x2350;
    s32 x2354;
    s32 x2358;
    s32 x235C;
    s32 x2360;
    s32 x2364;
    s32 x2368;
    s32 x236C;

} ftSeakSpecialS;

typedef struct ftSeakSpecialHi {
    s32 x2340;
    s32 x2344;
    s32 x2348;
    s32 x234C;
    s32 x2350;
    s32 x2354;
    s32 x2358;
    s32 x235C;
    s32 x2360;
    s32 x2364;
    s32 x2368;
    s32 x236C;

} ftSeakSpecialHi;

typedef union ftSeakStateVars {
    ftSeakSpecialN SpecialN;
    ftSeakSpecialS SpecialS;
    ftSeakSpecialHi SpecialHi;

} ftSeakStateVars;

#endif
