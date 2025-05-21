#ifndef GALE01_31C99C
#define GALE01_31C99C

#include <platform.h>

#include <baselib/cobj.h>
#include <baselib/displayfunc.h>
#include <baselib/gobj.h>

/* 31C99C */ char* viGetCharAnimByIndex(s32);
/* 31C9B4 */ void vi_8031C9B4(s32, s32);
/* 31CA04 */ void vi_8031CA04(HSD_GObj*);
/* 31CAAC */ void vi_8031CAAC(void);

inline void vi_EraseScreen(HSD_GObj* gobj, u8 erase_colors[4])
{
    if (HSD_CObjSetCurrent(GET_COBJ(gobj))) {
        HSD_SetEraseColor(erase_colors[0], erase_colors[1], erase_colors[2],
                          erase_colors[3]);
        HSD_CObjEraseScreen(GET_COBJ(gobj), 1, 0, 1);
        vi_8031CA04(gobj);
        gobj->gxlink_prios = 0x881;
        HSD_GObj_80390ED0(gobj, 0x7);
        HSD_CObjEndCurrent();
    }
}

#endif
