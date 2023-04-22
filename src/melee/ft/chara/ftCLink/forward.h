#ifndef MELEE_FT_CHARA_FTCLINK_FORWARD_H
#define MELEE_FT_CHARA_FTCLINK_FORWARD_H

#include <platform.h>
#include "ft/forward.h"

typedef enum ftCl_MotionFlags {
    ftCl_MF_Zair = FtStateChange_PreserveFastFall |
                   FtStateChange_SkipUpdateModel |
                   FtStateChange_SkipUpdateAnimVel | FtStateChange_Unk_6,
} ftCl_MotionFlags;

#endif
