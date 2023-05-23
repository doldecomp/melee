#ifndef GALE01_093C3C
#define GALE01_093C3C

#include <platform.h>
#include "ftCommon/forward.h"
#include "it/forward.h"
#include <baselib/forward.h>

/* 093CF4 */ /* static */ bool ftCo_80094150(HSD_GObj* arg0, HSD_GObj* arg1);
/* 094020 */ /* static */ bool ftCo_8009447C(ftCo_GObj* gobj,
                                             HSD_GObj* item_gobj);
/* 094238 */ /* static */ void ftCo_80094694(HSD_GObj* gobj, FtMotionId msid,
                                             bool loop);
/* 0942A0 */ /* static */ ftCo_GObj* ftCo_800942A0(ftCo_GObj* gobj, u32 flags);
/* 094334 */ bool ft_80094790(HSD_GObj* gobj);
/* 0943BC */ void ft_80094818(HSD_GObj* gobj, bool);
/* 09444C */ /* static */ void ftCo_800948A8(ftCo_GObj* gobj,
                                             Item_GObj* item_gobj);
/* 0945B8 */ void ftCo_ItemGet_Anim(ftCo_GObj* gobj);
/* 0946C4 */ void ftCo_ItemGet_IASA(ftCo_GObj* gobj);
/* 0946C8 */ void ftCo_ItemGet_Phys(ftCo_GObj* gobj);
/* 0946E8 */ void ftCo_ItemGet_Coll(ftCo_GObj* gobj);

#endif
