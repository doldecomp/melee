#ifndef _FTCAPTAIN_STATEVARS_H_
#define _FTCAPTAIN_STATEVARS_H_

#include <types.h>
#include <sysdolphin/baselib/gobj.h>

typedef struct ftCaptainSpecialS {

	f32 gravity; // 0x2340 - Gravity of aerial Raptor Boost

} ftCaptainSpecialS;

typedef union ftCaptainStateVars {

	ftCaptainSpecialS specialS;

} ftCaptainStateVars;

#endif