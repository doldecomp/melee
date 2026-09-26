#ifndef GALE01_31C99C
#define GALE01_31C99C

#include <Runtime/platform.h>

#include <dolphin/gx/GXStruct.h>
#include <sysdolphin/baselib/cobj.h>
#include <sysdolphin/baselib/displayfunc.h>
#include <sysdolphin/baselib/gobj.h>

/* 31C99C */ char* viGetCharAnimByIndex(s32);
/* 31C9B4 */ void vi_8031C9B4(s32, s32);
/* 31CA04 */ void vi_8031CA04(HSD_GObj*);
/* 31CAAC */ void vi_8031CAAC(void);

static inline void vi_RunCamera(HSD_GObj* gobj, GXColor* erase_color, u64 prio)
{
    HSD_CObj* cobj = GET_COBJ(gobj);

    if (HSD_CObjSetCurrent(cobj)) {
        HSD_SetEraseColor(erase_color->r, erase_color->g, erase_color->b,
                          erase_color->a);
        HSD_CObjEraseScreen(GET_COBJ(gobj), 1, 0, 1);
        vi_8031CA04(gobj);
        gobj->gxlink_prios = prio;
        HSD_GObj_80390ED0(gobj, 0x7);
        HSD_CObjEndCurrent();
    }
}

#endif
