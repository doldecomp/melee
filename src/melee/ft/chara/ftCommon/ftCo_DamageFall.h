#ifndef GALE01_090824
#define GALE01_090824

#include "common_structs.h"

#include "ftCommon/forward.h"

#include <dolphin/mtx.h>

/* 090574 */ void ftCo_80090574(Fighter_GObj* gobj);
/* 090594 */ void ftCo_80090594(Fighter* fp, enum_t element, int dmg,
                                FtMotionId msid, GroundOrAir ground_or_air,
                                float hitlag_mul);
/* 090690 */ Vec2* ftCo_80090690(Fighter* fp, Vec2* shift);
/* 090718 */ void ftCo_80090718(Fighter* fp);
/* 090780 */ void ftCo_80090780(Fighter_GObj* gobj);
/* 090824 */ void ftCo_DamageFall_Anim(Fighter_GObj* gobj);
/* 090828 */ void ftCo_DamageFall_IASA(Fighter_GObj* gobj);
/* 09093C */ void ftCo_DamageFall_Phys(Fighter_GObj* gobj);
/* 09095C */ void ftCo_DamageFall_Coll(Fighter_GObj* gobj);

#endif
