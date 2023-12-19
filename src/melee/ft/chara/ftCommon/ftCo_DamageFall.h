#ifndef GALE01_090824
#define GALE01_090824

#include <platform.h>
#include "ft/forward.h"
#include "ftCommon/forward.h"

#include <placeholder.h>

/* 090574 */ void ftCo_80090574(ftCo_GObj* gobj);
/* 090594 */ void ftCo_80090594(ftCo_Fighter* fp, enum_t arg1, int dmg,
                                FtMotionId msid, enum_t arg4,
                                float hitlag_mul);
/* 090690 */ Vec2* ftCo_80090690(ftCo_Fighter* fp, Vec2* shift);
/* 090718 */ void ftCo_80090718(ftCo_Fighter* fp);
/* 090780 */ void ftCo_80090780(ftCo_GObj* gobj);
/* 090824 */ void ftCo_DamageFall_Anim(ftCo_GObj* gobj);
/* 090828 */ void ftCo_DamageFall_IASA(ftCo_GObj* gobj);
/* 09093C */ void ftCo_DamageFall_Phys(ftCo_GObj* gobj);
/* 09095C */ void ftCo_DamageFall_Coll(ftCo_GObj* gobj);

#endif
