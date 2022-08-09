#ifndef _gobjgxlink_h_
#define _gobjgxlink_h_

#include <dolphin/types.h>

#include "sysdolphin/baselib/gobj.h"

void GObj_GXReorder(HSD_GObj* gobj, HSD_GObj* hiprio_gobj);
void GObj_SetupGXLink(HSD_GObj* gobj, void (*render_cb)(HSD_GObj*, s32), u8 gx_link, u32 priority);
void GObj_SetupGXLinkMax(HSD_GObj* gobj, void (*render_cb)(HSD_GObj*, s32), u32 priority);
void GObj_SetupGXLinkMaxSorted(HSD_GObj* gobj, void (*render_cb)(HSD_GObj*, s32), u32 priority);

#endif
