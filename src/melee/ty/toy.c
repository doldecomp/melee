#include "toy.h"

#include "baselib/controller.h"
#include "baselib/gobj.h"
#include "baselib/gobjproc.h"
#include "baselib/jobj.h"
#include "baselib/memory.h"
#include "gm/gm_1601.h" // for gm_801677E8
#include "gm/gm_16AE.h"
#include "gm/gm_1A3F.h"
#include "gm/gm_1A45.h"
#include "gm/gmmain_lib.h"
#include "if/textlib.h"
#include "lb/lb_00B0.h"
#include "lb/lbarchive.h"
#include "lb/lbaudio_ax.h"
#include "mn/mnsoundtest.h"

#include "ty/forward.h"

#include "ty/types.h"

#include <melee/if/textlib.h>
#include <MSL/math.h> // for ABS

static u8 un_804D6EA1;

extern char un_803FDD18[];
extern void* un_804D6ECC;
extern void* un_804D6EA8;
extern void* un_804D6EA4;

/// #un_80305058

/// #un_803053C4

/// #Trophy_SetUnlockState

/// #un_80305918

s32 un_80305B88(void)
{
    int i;
    u32 button;
    PAD_STACK(4);

    for (i = 0; i < 4; i++) {
        if ((button = HSD_PadCopyStatus[(u8) i].trigger)) {
            gm_801677E8(i);
            break;
        }
    }
    return button;
}

s32 un_80305C44(void)
{
    int i = 0;
    u32 button;
    PAD_STACK(4);

    for (i = 0; i < 4; i++) {
        if ((button = HSD_PadCopyStatus[(u8) i].button)) {
            gm_801677E8(i);
            break;
        }
    }
    return button;
}

/// #un_80305D00

float un_80305DB0(void)
{
    float ret = 0.0F;
    int i;

    for (i = 0; i < 4; i++) {
        ret = HSD_PadGetNmlStickY(i);

        if (ABS(ret) > 0.1F) {
            gm_801677E8(i);
            break;
        }
    }

    return ret;
}

/// #un_80305EB4

/// #un_80305FB8

/// #un_803060BC

/// #un_803062BC

/// #un_803062EC

/// #un_803063D4

/// #un_803064B8

/// #un_8030663C

/// #un_803067BC

/// #un_803068E0

/// #un_80306930

/// #un_80306954

/// #un_80306A0C

/// #un_80306A48

HSD_GObjProc* un_80306B18(HSD_GObj* gobj, s32 anim_frame, s32 val1, s32 val2)
{
    HSD_GObjProc* proc = NULL;
    Toy* tp = (Toy*) gobj->user_data;

    if (tp != NULL) {
        HSD_JObjClearFlagsAll(gobj->hsd_obj, JOBJ_HIDDEN);
        HSD_JObjReqAnimAll(gobj->hsd_obj, anim_frame);

        tp->x8 = val1;
        tp->x4 = val2;

        proc = HSD_GObjProc_8038FD54(gobj, un_80306BB8, 0);
        HSD_GObj_80390CD4(gobj);
    }
    return proc;
}

void un_80306BB8(HSD_GObj* gobj)
{
    Toy* tp = HSD_GObjGetUserData(gobj);
    HSD_JObj* jobj = gobj->hsd_obj;

    if (tp != NULL) {
        if (tp->x8--) {
            HSD_JObjAnimAll(jobj);
        } else {
            tp->x8 = 0;

            if (tp->x4 != 0) {
                HSD_JObjClearFlagsAll(gobj->hsd_obj, JOBJ_HIDDEN);
            }

            HSD_GObjProc_8038FE24(HSD_GObj_804D7838);
        }
    } else {
        if (!lb_8000B09C(jobj)) {
            HSD_JObjReqAnimAll(jobj, 0.0f);
        }
        HSD_JObjAnimAll(jobj);
    }
}

/// #un_80306C5C

void Toy_RemoveUserData(void* ptr)
{
    HSD_Free(ptr);
}

void un_80306D14(void)
{
    TyModeState* state = (TyModeState*) un_804A284C;

    if (state->x0 == 1) {
        lbAudioAx_800237A8(0xAA, 0x7F, 0x40);
    } else if (state->x0 == 2) {
        lbAudioAx_800237A8(0xAB, 0x7F, 0x40);
    }
}
/// #un_80306D70

/// #un_80306EEC

/// #un_80307018

/// #un_8030715C

/// #un_80307470

/// #un_803075E8

/// #un_80307828

/// #un_803078E4

/// #un_80307BA0

/// #fn_80307E84

/// #un_80307F64

/// #un_8030813C

/// #un_80308250

/// #un_803082F8

/// #un_80308328

/// #un_80308354

/// #un_803083D8

/// #un_803084A0

/// #un_803087F4

/// #un_80308DC8

/// #un_80308F04

/// #un_80309338

/// #fn_80309404

/// #fn_8030B530

/// #fn_8030E110

/// #un_8030FA50

/// #un_8030FE48

void un_803102C4(s8 arg0)
{
    M2C_FIELD(un_804D6E6C, s8*, 4) = arg0;
}

void un_803102D0(void)
{
    char* base = un_803FDD18;

    if (un_804D6ECC == NULL) {
        un_804D6ECC = lbArchive_LoadSymbols(
            base + 0xA58,
            &un_804D6EA8,
            base + 0xA64,
            &un_804D6EA4,
            base + 0xA74,
            NULL
        );
    }
}
/// #un_80310324

/// #un_80310660

/// #un_803109A0

/// #un_80310B48

/// #un_803114E8

/// #un_80311680

/// #un_80311788

/// #un_80311960

/// #un_80311AB0_OnEnter

/// #un_80311F5C

void un_80312018_OnFrame(void)
{
    TyModeState* state = (TyModeState*) un_804A284C;

    if (state->x4 != 0) {
        un_80311F5C();
        gm_801A4B60();
    }
}
/// #un_80312050

void un_803122D0_OnInit(void)
{
    Toy* userData = (Toy*) &un_804A26B8;
    void* targetPtr;

    memzero(&userData->x194, 0x25A);

    un_804D6EA1 = 0;

    if (gm_8016B498() || gm_801A4310() == MJ_TOY_LOTTERY) {
        targetPtr = &userData->x19A;
    } else {
        targetPtr = gmMainLib_8015CC84();
    }

    *(u16*) targetPtr |= 4;

    *(u8*) &userData->x194 = 1;
}

/// #un_8031234C
