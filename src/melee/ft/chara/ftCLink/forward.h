#ifndef MELEE_FT_CHARA_FTCLINK_FORWARD_H
#define MELEE_FT_CHARA_FTCLINK_FORWARD_H

#include <platform.h>
#include "ft/forward.h"

static Fighter_MotionStateChangeFlags const ftCl_MF_Zair ATTRIBUTE_USED =
    FtStateChange_PreserveFastFall | FtStateChange_SkipUpdateModel |
    FtStateChange_SkipUpdateAnimVel | FtStateChange_Unk_6;

#endif
