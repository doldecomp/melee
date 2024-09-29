#ifndef _gobjgxlink_h_
#define _gobjgxlink_h_

#include <platform.h>

#include "baselib/forward.h"

#include "baselib/gobj.h"

void GObj_GXReorder(HSD_GObj* gobj, HSD_GObj* hiprio_gobj);
void GObj_SetupGXLink(HSD_GObj* gobj, GObj_RenderFunc render_cb, u8 gx_link,
                      u32 priority);
void GObj_SetupGXLinkMax(HSD_GObj* gobj, GObj_RenderFunc render_cb,
                         u32 priority);
void GObj_SetupGXLinkMaxSorted(HSD_GObj* gobj, GObj_RenderFunc render_cb,
                               u32 priority);
void HSD_GObjGXLink_8039084C(HSD_GObj*);
void HSD_GObjGXLink_80390908(HSD_GObj*, u8 gx_link, u8 priority);
void HSD_GObjGXLink_803909D8(HSD_GObj*, HSD_GObj*);

#endif
