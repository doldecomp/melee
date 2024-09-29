#ifndef GALE01_0BF260
#define GALE01_0BF260

#include <platform.h>

#include "ft/forward.h"
#include "ftCommon/forward.h"
#include <dolphin/gx/forward.h>
#include <baselib/forward.h>

/* 0BF260 */ void ftMaterial_800BF260(void);
/* 0BF2B8 */ void ftMaterial_800BF2B8(HSD_MObj* mobj, u32 rendermode);
/* 0BF534 */ HSD_TExp* ftMaterial_800BF534(Fighter* fp, HSD_MObj* mobj,
                                           HSD_TExp* texp, u32 rendermode);
/* 0BF6BC */ void ftMaterial_800BF6BC(Fighter* fp, HSD_MObj* mobj,
                                      HSD_TExp* texp);
/* 0BFB4C */ void ftMaterial_800BFB4C(ftCo_GObj* gobj, GXColor* diffuse);
/* 0BFD04 */ void ftMaterial_800BFD04(ftCo_GObj* gobj);
/* 0BFD9C */ void ftMaterial_800BFD9C(ftCo_GObj* gobj);
/* 3C6980 */ extern HSD_MObjInfo ftMObj;

#endif
