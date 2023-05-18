#ifndef _ftcliffcommon_h_
#define _ftcliffcommon_h_

#include <platform.h>

#include "ft/fighter.h"

#include <baselib/gobj.h>

bool ftCliffCommon_80081298(HSD_GObj* gobj);
void ftCliffCommon_80081370(HSD_GObj* gobj);
void ftCo_CliffCatch_Anim(HSD_GObj* gobj);
void ftCo_CliffCatch_IASA(HSD_GObj*);
void ftCo_CliffCatch_Phys(HSD_GObj* gobj);
void ftCo_Cliff_Cam(HSD_GObj* gobj);

void ftCo_CliffCatch_Coll(HSD_GObj* gobj);

#endif
