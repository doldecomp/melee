#include "ft/ftlib.h"
#include "ftCrazyHand/ftCh_Init.h"
#include "ftMasterHand/ftMh_Wait1_2.h"

#include <baselib/gobj.h>

/* 08A348 */ static void ft_8008A348(HSD_GObj*, float);

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
