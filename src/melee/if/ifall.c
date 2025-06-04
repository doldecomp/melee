#include "ifall.static.h"

#include "if/ifmagnify.h"
#include "if/ifstatus.h"
#include "if/iftime.h"
#include "un/un_2FC9.h"

#include <baselib/cobj.h>
#include <baselib/gobj.h>

void ifAll_802F3394(void)
{
    ifStatus_802F6898();
    ifTime_802F405C();
    un_802FD450();
    ifMagnify_802FC8E8();
    un_802FD668();
    un_802FD910();
    un_802FF570();
}

void ifAll_802F33CC(void)
{
    ifStatus_802F68F0();
    ifTime_802F40B8();
    un_802FD45C();
    ifMagnify_802FC940();
    un_802FD674();
    un_802FD91C();
    un_802FF620();
}

s32 ifAll_802F3404(void)
{
    return ifAll_804A0FD8.unk_0;
}

UNK_T ifAll_802F3414(void)
{
    return &ifAll_804A0FD8.xC;
}

struct ifAll_804A0FD8_x18_t* ifAll_802F3424(int idx)
{
    return &ifAll_804A0FD8.x18[idx];
}

/// #ifAll_802F343C

UNK_T ifAll_802F3690(void)
{
    return &ifAll_804D6D5C;
}

void ifAll_HideHUD(void)
{
    ifAll_804D6D58 = 1;
}

void ifAll_ShowHUD(void)
{
    ifAll_804D6D58 = 0;
}

u8 ifAll_IsHUDHidden(void)
{
    return ifAll_804D6D58;
}

void fn_802F36B8(HSD_GObj* gobj)
{
    if ((int) ifAll_804D6D58 == 0) {
        if (HSD_CObjSetCurrent(GET_COBJ(gobj))) {
            HSD_GObj_80390ED0(gobj, 0x7);
            HSD_CObjEndCurrent();
        }
    }
}

/// #ifAll_802F370C

/// #ifAll_802F390C

/// #ifAll_802F3A64
