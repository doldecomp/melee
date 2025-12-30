#include "vi/vi1201v1.static.h"

#include <baselib/gobj.h>
#include <baselib/jobj.h>

#include "gm/gm_unsplit.h"
#include "lb/lb_00B0.h"
#include "lb/lb_00F9.h"
#include "vi.h"

extern void* un_804D7000;
extern u8 un_804D6FF4;
extern u8 un_804D6FFC;
extern u8 un_804D6FFD;
extern s32 un_804D6FF8;

void un_8031F990(HSD_GObj* gobj)
{
    HSD_JObjAnimAll(GET_JOBJ(gobj));
}

void un_8031F9B4(HSD_GObj* gobj)
{
    HSD_JObjAnimAll(GET_JOBJ(gobj));
}

/// #un_8031F9D8

/// #fn_8031FAA8

void fn_8031FB90(HSD_GObj* gobj)
{
    u8* colors;
    char pad[8];
    if (un_804D7000 != NULL) {
        lbShadow_8000F38C(0);
    }
    if (HSD_CObjSetCurrent(GET_COBJ(gobj)) != 0) {
        colors = &un_804D6FF4;
        HSD_SetEraseColor(colors[0], colors[1], colors[2], colors[3]);
        HSD_CObjEraseScreen(GET_COBJ(gobj), 1, 0, 1);
        vi_8031CA04(gobj);
        *(s32*)((char*)gobj + 0x24) = 0x881;
        *(s32*)((char*)gobj + 0x20) = 0;
        HSD_GObj_80390ED0(gobj, 7);
        HSD_CObjEndCurrent();
    }
}

/// #fn_8031FC30

/// #fn_8031FCBC

/// #un_8031FD18_OnEnter

void un_80320490_OnFrame(void)
{
    vi_8031CAAC();
}

void un_803204B0(int arg0, int arg1)
{
    M2C_FIELD(&un_804D7038, u8*, 0) = arg0;
    M2C_FIELD(&un_804D7038, u8*, 1) = arg1;
}
