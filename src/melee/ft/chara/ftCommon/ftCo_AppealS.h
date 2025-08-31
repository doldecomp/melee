#ifndef MELEE_FTCO_APPEALS_H
#define MELEE_FTCO_APPEALS_H

#include "ft/forward.h"

/* 0DECF4 */ void ftCo_AppealS_Anim(Fighter_GObj* gobj);
/* 0DED30 */ void ftCo_AppealS_IASA(Fighter_GObj* gobj);
/* 0DEE44 */ void ftCo_AppealS_Phys(Fighter_GObj* gobj);
/* 0DEE64 */ void ftCo_AppealS_Coll(Fighter_GObj* gobj);
/* 0DEE84 */ void ftCo_800DEE84(Fighter_GObj* gobj, int, char*, u32, float,
                                float);
/* 0DEEA8 */ void ftCo_800DEEA8(Fighter_GObj* gobj);
/* 0DEEB8 */ float ftCo_800DEEB8(Fighter* fp, float);
/* 0DEEE8 */ Vec2* ftCo_800DEEE8(Fighter* fp, Vec2* shift);
/* 0DEF38 */ void ftCo_800DEF38(Fighter_GObj* gobj);
/* 0DE9B8 */ bool ftCo_800DE9B8(Fighter_GObj* gobj);
/* 0DE9D8 */ bool ftCo_800DE9D8(Fighter_GObj* gobj);
/* 0DEA28 */ void ftCo_800DEA28(Fighter_GObj* gobj);
/* 0DEAE8 */ void ftCo_800DEAE8(Fighter_GObj* gobj, FtMotionId msid0,
                                FtMotionId msid1);
/* 0DEBD0 */ void ftCo_800DEBD0(Fighter_GObj* gobj);

#endif
