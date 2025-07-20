#include "vi0501.h"

#include "gm/gm_1A36.h"
#include "lb/lb_00F9.h"
#include "lb/lbshadow.h"
#include "vi/vi.h"

#include <dolphin/gx.h>
#include <baselib/aobj.h>
#include <baselib/cobj.h>
#include <baselib/displayfunc.h>
#include <baselib/wobj.h>

static GXColor erase_colors_vi0501;
extern un_804D7004_t un_804D6FA8;

/// #un_8031D9F8

void vi_8031DC80(HSD_GObj* gobj, int unused)
{
    PAD_STACK(8);
    lbShadow_8000F38C(0);
    vi_RunCamera(gobj, (u8*) &erase_colors_vi0501, 0x281);
}

/// #fn_8031DD14

/// #un_8031DE58_OnEnter

void vi_8031E0F0_OnFrame(void)
{
    vi_8031CAAC();
}

void un_8031E110(int arg0, int arg1, int arg2)
{
    M2C_FIELD(&un_804D6FA8, u8*, 0) = arg0;
    M2C_FIELD(&un_804D6FA8, u8*, 1) = arg1;
    M2C_FIELD(&un_804D6FA8, u8*, 3) = arg2;
}
