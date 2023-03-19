// This is a file to include all existing StateVar headers until they're
// finalized.

#ifndef _FTSTATEVARS_H_
#define _FTSTATEVARS_H_

#include <platform.h>

typedef struct ftCliffCommonVars {
    s32 ledgeID; // 0x2340 - Used to check against opponent's variable @ 0x213C
                 // while they're occupying a ledge within grab range

} ftCliffCommonVars;

typedef union ftCommonStateVars {
    ftCliffCommonVars CliffCommon;

} ftCommonStateVars;

#endif
