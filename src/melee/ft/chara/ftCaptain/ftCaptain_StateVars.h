#ifndef _FTCAPTAIN_STATEVARS_H_
#define _FTCAPTAIN_STATEVARS_H_

#include <Runtime/platform.h>
#include <sysdolphin/baselib/gobj.h>

typedef struct ftCaptainSpecialS {
    f32 grav; // 0x2340 - Gravity of aerial Raptor Boost
} ftCaptainSpecialS;

typedef union ftCaptainStateVars {
    ftCaptainSpecialS specials;
} ftCaptainStateVars;

#endif
