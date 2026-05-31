#ifndef GALE01_800C7CA0
#define GALE01_800C7CA0

#include "ft/forward.h"

#include <baselib/dobj.h>
#include <baselib/jobj.h>

extern HSD_MObj* ft_804D6580;

/* 7CA0 */ bool ftCo_800C7CA0(Fighter_GObj* gobj);
/* 7DC4 */ void fn_800C7DC4(HSD_GObj* gobj, s32 motion_state, Vec3* normal,
                           Vec3* offset);
/* 7FC8 */ void ftCo_DownReflect_Anim(Fighter_GObj* gobj);
/* 8004 */ void ftCo_DownReflect_IASA(Fighter_GObj* gobj);
/* 8008 */ void ftCo_DownReflect_Phys(Fighter_GObj* gobj);
/* 8028 */ void ftCo_DownReflect_Coll(Fighter_GObj* gobj);
/* 8064 */ void ftCo_800C8064(void);
/* 80A4 */ void ft_800C80A4(Fighter* fp);

#endif
