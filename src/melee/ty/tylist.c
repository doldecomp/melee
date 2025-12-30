
<<<<<<< HEAD
=======
#include "lb/lb_00B0.h"

#include <baselib/cobj.h>
#include <baselib/displayfunc.h>
#include <baselib/fog.h>
#include <baselib/gobj.h>
#include <baselib/gobjgxlink.h>
#include <baselib/video.h>
#include <string.h>

typedef struct {
    u8 pad[0x28];
    HSD_CObj* cobj;
} TyListData;

extern u8 un_804A2AA8[];
extern void* un_804D6ED0;
extern void* un_804D6EC4;
extern void* un_804D6EC0;
extern void* un_804D6EBC;
extern void* un_804D6EB8;
extern void* un_804D6EB4;
extern void* un_804D6EB0;
extern void* un_804D6EAC;
extern void* un_804D6ECC;
extern void* un_804D6EA8;
extern void* un_804D6EA4;
extern void* un_804D6EC8;

/// #un_803124BC

/// #un_8031263C

void un_803127D4(void)
{
    un_804D6ED0 = NULL;
    un_804D6EC4 = NULL;
    un_804D6EC0 = NULL;
    un_804D6EBC = NULL;
    un_804D6EB8 = NULL;
    un_804D6EB4 = NULL;
    un_804D6EB0 = NULL;
    un_804D6EAC = NULL;
    un_804D6ECC = NULL;
    un_804D6EA8 = NULL;
    un_804D6EA4 = NULL;
    un_804D6EC8 = NULL;
    memzero(un_804A2AA8, 0x14);
}

/// #un_80312834

/// #un_80312904

/// #un_80312BAC

/// #un_80312E88

/// #un_8031305C

/// #un_80313358

/// #un_80313464

/// #un_80313508

/// #un_80313774

/// #fn_80313BD8

/// #fn_8031438C

void fn_80314504(HSD_GObj* gobj)
{
    TyListData* data = (TyListData*) gobj;

    if ((s32) HSD_CObjSetCurrent(data->cobj) != 0) {
        HSD_SetEraseColor(0, 0, 0, 0xFF);
        HSD_CObjEraseScreen(data->cobj, 1, 0, 0);
        HSD_GObj_80390ED0(gobj, 7);
        HSD_FogSet(0);
        HSD_CObjEndCurrent();
    }
}

/// #un_8031457C

/// #un_803147C4

/// #un_803148E4
>>>>>>> 8c8cc9bff (Fix build: add missing includes and prototypes for ty module)
