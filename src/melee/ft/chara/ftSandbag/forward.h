#ifndef MELEE_FT_CHARA_FTSANDBAG_FORWARD_H
#define MELEE_FT_CHARA_FTSANDBAG_FORWARD_H

#include "ftCommon/forward.h"

typedef enum ftSb_MotionState {
    ftSb_MS_WaitReverse = ftCo_MS_Count,
    ftSb_MS_Count,
    ftSb_MS_SelfCount = ftSb_MS_Count - ftCo_MS_Count,
} ftSb_MotionState;

typedef enum ftSb_Submotion {
    ftSb_SM_WaitReverse = ftCo_SM_Count,
    ftSb_SM_Count,
    ftSb_SM_SelfCount = ftSb_SM_Count - ftCo_SM_Count,
} ftSb_Submotion;

#endif
