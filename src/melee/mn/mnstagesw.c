#include "mnstagesw.h"

#include <sysdolphin/baselib/gobj.h>
#include <sysdolphin/baselib/gobjgxlink.h>
#include <sysdolphin/baselib/gobjobject.h>
#include <sysdolphin/baselib/gobjplink.h>
#include <sysdolphin/baselib/gobjproc.h>
#include <sysdolphin/baselib/gobjuserdata.h>
#include <sysdolphin/baselib/jobj.h>
#include <sysdolphin/baselib/memory.h>
#include <sysdolphin/baselib/sislib.h>
#include <melee/gm/gm_1601.h>
#include <melee/gm/gm_1A3F.h>
#include <melee/gm/gmmain_lib.h>
#include <melee/lb/lb_00B0.h>
#include <melee/lb/lb_00F9.h>
#include <melee/lb/lbaudio_ax.h>
#include <melee/lb/lbcardgame.h>
#include <melee/mn/mnmain.h>
#include <melee/mn/mnruleplus.h>
#include <melee/sc/types.h>

#define NUM_STAGES 29

/// Stage switch toggle indices - maps menu position to internal stage ID
static u8 mnStageSw_803ED4C4[NUM_STAGES] = {
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09,
    0x0B, 0x0A, 0x18, 0x1A, 0x1C, 0x0C, 0x0D, 0x0E, 0x0F, 0x10,
    0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x19, 0x1B,
};

/// Stage switch icon indices
static u8 mnStageSw_stageIcons[NUM_STAGES] = {
    0x08, 0x09, 0x11, 0x0A, 0x0C, 0x06, 0x0B, 0x07, 0x0E, 0x0D,
    0x1D, 0x17, 0x0F, 0x10, 0x12, 0x13, 0x14, 0x15, 0x1A, 0x1B,
    0x1C, 0x16, 0x18, 0x1F, 0x20, 0x21, 0x22, 0x23, 0x24,
};

static HSD_GObj* mnStageSw_804D6BF0;
static s8 mnStageSw_804D6BF4;

/* 23593C */ static void mnStageSw_8023593C(HSD_GObj* gobj);
/* 2359C8 */ static void mnStageSw_802359C8(HSD_GObj* gobj);
/* 235C58 */ static s32 mnStageSw_80235C58(u8 arg0);
/* 235DC8 */ static void mnStageSw_80235DC8(u8* user_data, s32 buttons);
/* 235F80 */ static void fn_80235F80(HSD_GObj* gobj);
/* 236178 */ static void mnStageSw_80236178(HSD_GObj* gobj, u8 idx);
/* 2364A0 */ static HSD_JObj* mnStageSw_802364A0(HSD_GObj* gobj, u8 idx);
/* 236548 */ static void mnStageSw_80236548(HSD_GObj* gobj, u8 arg1, u8 arg2);
/* 236998 */ static void fn_80236998(HSD_GObj* gobj);
/* 236CBC */ static HSD_GObj* mnStageSw_80236CBC(s8 arg0);

/// Sync stage toggle states from user data to unlock system.
/// For each stage, if it's unlocked, set its enable state from user_data[i+2].
/// Stack padding required to match original frame size.
static void mnStageSw_8023593C(HSD_GObj* gobj)
{
    u8* arr = mnStageSw_803ED4C4;
    u8* ptr = arr;
    s32 i = 0;
    u8* user_data = gobj->user_data;
    u8* p;
    u8 pad[8];
    (void) pad;

    do {
        p = arr + (u8) i;
        if (gm_80164430(gm_801641CC(*p)) != 0) {
            gm_801641E4(*ptr, user_data[i + 2]);
        }
        i++;
        ptr++;
    } while (i < NUM_STAGES);
}

/// #mnStageSw_802359C8

/// #mnStageSw_80235C58

/// #mnStageSw_80235DC8

/// #fn_80235F80

/// Position stage icon JObj based on index
/// Uses stored reference JObjs to calculate X/Y position
static void mnStageSw_80236178(HSD_GObj* gobj, u8 idx)
{
    HSD_JObj* jobj;
    HSD_JObj* ref_jobj;
    f32 delta;

    jobj = GET_JOBJ(gobj);
    HSD_JObjClearFlagsAll(jobj, JOBJ_HIDDEN);

    delta = HSD_JObjGetTranslationY((HSD_JObj*) gobj->user_data_remove_func) -
            HSD_JObjGetTranslationY((HSD_JObj*) gobj->user_data);

    if ((u8) idx < 15) {
        ref_jobj = (HSD_JObj*) gobj->user_data;
        HSD_JObjSetTranslateX(jobj, HSD_JObjGetTranslationX(ref_jobj));
        HSD_JObjSetTranslateY(
            jobj, delta * (f32) (u8) idx +
                      HSD_JObjGetTranslationY((HSD_JObj*) gobj->user_data));
    } else {
        ref_jobj = (HSD_JObj*) gobj->x34_unk;
        HSD_JObjSetTranslateX(jobj, HSD_JObjGetTranslationX(ref_jobj));
        HSD_JObjSetTranslateY(
            jobj, delta * (f32) ((u8) idx - 15) +
                      HSD_JObjGetTranslationY((HSD_JObj*) gobj->user_data));
    }
}

/// Get JObj for stage icon at given index
/// Navigates JObj tree stored in gobj->user_data (idx < 15) or gobj->x34_unk
/// (idx >= 15)
static HSD_JObj* mnStageSw_802364A0(HSD_GObj* gobj, u8 idx)
{
    HSD_JObj* jobj;
    HSD_JObj* temp;
    u8 i;

    if ((u8) idx >= 15) {
        jobj = (HSD_JObj*) gobj->x34_unk;
        if (jobj == NULL) {
            temp = NULL;
        } else {
            temp = jobj->child;
        }
        jobj = temp;
        for (i = 15; (u8) i < (u8) idx; i++) {
            if (jobj == NULL) {
                temp = NULL;
            } else {
                temp = jobj->next;
            }
            jobj = temp;
        }
    } else {
        jobj = (HSD_JObj*) gobj->user_data;
        if (jobj == NULL) {
            temp = NULL;
        } else {
            temp = jobj->child;
        }
        jobj = temp;
        for (i = 0; (u8) i < (u8) idx; i++) {
            if (jobj == NULL) {
                temp = NULL;
            } else {
                temp = jobj->next;
            }
            jobj = temp;
        }
    }
    return jobj;
}

/// #mnStageSw_80236548

/// #fn_80236998

/// #mnStageSw_80236CBC

void mnStageSw_80237410(void)
{
    HSD_GObj* gobj;
    HSD_GObjProc* proc;

    mn_804A04F0.prev_menu = mn_804A04F0.cur_menu;
    mn_804A04F0.cur_menu = 0x11;
    mn_804A04F0.hovered_selection = mnStageSw_80235C58(0);
    mnStageSw_804D6BF4 = 1;
    gobj = mnStageSw_80236CBC(1);
    HSD_GObj_80390CD4(gobj);
    gobj = GObj_Create(0, 1, 0x80);
    proc = HSD_GObjProc_8038FD54(gobj, fn_80235F80, 0);
    proc->flags_3 = HSD_GObj_804D783C;
}
