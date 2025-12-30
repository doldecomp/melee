#include "vi1101.static.h"

#include <baselib/cobj.h>
#include <baselib/gobj.h>

#include "lb/lb_00B0.h"
#include "vi.h"

extern u8 un_804D5B08;

/// #un_8031F294

/// #fn_8031F548

void fn_8031F56C(HSD_GObj* gobj)
{
    u8* colors;
    char pad[8];
    lbShadow_8000F38C(0);
    if (HSD_CObjSetCurrent(GET_COBJ(gobj)) != 0) {
        colors = &un_804D5B08;
        HSD_SetEraseColor(colors[0], colors[1], colors[2], colors[3]);
        HSD_CObjEraseScreen(GET_COBJ(gobj), 1, 0, 1);
        vi_8031CA04(gobj);
        *(s32*)((char*)gobj + 0x24) = 0x281;
        *(s32*)((char*)gobj + 0x20) = 0;
        HSD_GObj_80390ED0(gobj, 7);
        HSD_CObjEndCurrent();
    }
}

/// #fn_8031F600

/// #un_8031F714_OnEnter

void un_8031F960_OnFrame(void)
{
    vi_8031CAAC();
}

void un_8031F980(int arg0, int arg1)
{
    M2C_FIELD(&un_804D7004, u8*, 0) = arg0;
    M2C_FIELD(&un_804D7004, u8*, 1) = arg1;
}
