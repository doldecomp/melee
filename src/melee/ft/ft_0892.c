#include "ft/ftlib.h"
#include "ft/inlines.h"
#include "ftCrazyHand/ftCh_Init.h"
#include "ftMasterHand/ftMh_Wait1_2.h"

#include <baselib/gobj.h>

/* 08A348 */ static void ft_8008A348(HSD_GObj*, float);

/// #ft_800892D4

/// #ft_80089460

/// #ft_800895E0

/// #ft_80089768

/// #ft_80089824

union Struct2070* ft_80089884(Fighter_GObj* gobj)
{
    return &GET_FIGHTER(gobj)->x2070;
}

UNK_T ft_80089890(Fighter_GObj* gobj)
{
    return &GET_FIGHTER(gobj)->dmg.x18d4;
}

u16 ft_8008989C(Fighter_GObj* gobj)
{
    return GET_FIGHTER(gobj)->dmg.x18ec_instancehitby;
}

UNK_T ft_800898A8(Fighter_GObj* gobj)
{
    return &GET_FIGHTER(gobj)->x2074;
}

UNK_T ft_800898B4(Fighter_GObj* gobj)
{
    return &GET_FIGHTER(gobj)->dmg.x18d8;
}

/// #ft_800898C0

/// #ft_80089914

/// #fn_8008998C

/// #ft_80089B08

/// #ft_8008A1B8

/// #ft_8008A1FC

/// #ft_8008A244

void ft_8008A2BC(HSD_GObj* gobj)
{
    if (ftLib_800872A4(gobj) == FTKIND_MASTERH) {
        ftMh_MS_389_80151018(gobj);
    } else if (ftLib_800872A4(gobj) == FTKIND_CREZYH) {
        ftCh_GrabUnk1_8015BC88(gobj);
    } else {
        ft_8008A348(gobj, 0);
    }
}

/// #ft_8008A324

/// #ft_8008A348
