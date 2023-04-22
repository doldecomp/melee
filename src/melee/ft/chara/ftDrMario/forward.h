#ifndef MELEE_FT_CHARA_FTDRMARIO_FORWARD_H
#define MELEE_FT_CHARA_FTDRMARIO_FORWARD_H

#include "ft/forward.h"

typedef enum ftDr_MotionFlags {
    ftDr_MF_Appeal = FtStateChange_PreserveFastFall |
                     FtStateChange_SkipUpdateModel |
                     FtStateChange_SkipUpdateAnimVel | FtStateChange_Unk_6,
} ftDr_MotionFlags;
#endif
