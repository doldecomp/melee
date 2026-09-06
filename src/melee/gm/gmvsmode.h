#ifndef GALE01_1B14A0
#define GALE01_1B14A0

#include <melee/gm/types.h>

typedef enum {
    gmVsMode_State_Css,
    gmVsMode_State_Sss,
    gmVsMode_State_Vs,
    gmVsMode_State_SuddenDeath,
    gmVsMode_State_Results,
    gmVsMode_State_Approach = (2 << 6),
    gmVsMode_State_ApproachVs,
    gmVsMode_State_Prize = (3 << 6),
} gmVsMode_StateId;

/* 3DD9A0 */ extern GameModeState gm_Mode_Vs_States[];
/* 3DDA78 */ extern GameModeState gm_Mode_DebugVs_States[];

#endif
