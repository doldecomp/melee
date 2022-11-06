#ifndef MELEE_FT_CHARA_FTCAPTAIN_FTCAPTAIN_STATEVARS_H
#define MELEE_FT_CHARA_FTCAPTAIN_FTCAPTAIN_STATEVARS_H

#include <ctypes.h>

typedef struct ftCaptainSpecialS {
    /**
     * at 0x2340
     * Gravity of aerial Raptor Boost
     */
    f32 gravity;
} ftCaptainSpecialS;

typedef union ftCaptainStateVars {
    ftCaptainSpecialS SpecialS;
} ftCaptainStateVars;

#endif
