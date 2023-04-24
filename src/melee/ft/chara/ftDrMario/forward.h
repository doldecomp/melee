#ifndef MELEE_FT_CHARA_FTDRMARIO_FORWARD_H
#define MELEE_FT_CHARA_FTDRMARIO_FORWARD_H

#include "ft/forward.h"

static MotionFlags const ftDr_MF_Appeal ATTRIBUTE_USED =
    FtStateChange_PreserveFastFall | FtStateChange_SkipUpdateModel |
    FtStateChange_SkipUpdateAnimVel | FtStateChange_Unk_6;

#endif
