#include <platform.h>
#include "sc/forward.h"
#include <baselib/forward.h>

#include "lb/lb_00F9.h"
#include "lb/lbarchive.h"
#include "lb/lbaudio_ax.h"
#include "mn/inlines.h"
#include "mn/mn_2295.h"
#include "mn/types.h"
#include "sc/types.h"

#include <dolphin/os.h>
#include <baselib/gobj.h>
#include <baselib/gobjgxlink.h>
#include <baselib/gobjobject.h>
#include <baselib/gobjplink.h>
#include <baselib/gobjproc.h>
#include <baselib/gobjuserdata.h>
#include <baselib/jobj.h>
#include <baselib/memory.h>
#include <baselib/sislib.h>

void mnHyaku_8024C68C(HSD_GObj*);
void mnHyaku_8024CB94(u8);
void mnHyaku_8024CD64(u8);

void fn_8024C9F0(HSD_GObj*);
void fn_8024CA50(HSD_GObj*);
void fn_8024CAC8(HSD_GObj*);

extern HSD_GObj* mnHyaku_804D6C58;

void gm_801677E8(void);

void lbAudioAx_8002702C(s32, s32, s32);
void lbAudioAx_80027168(void);
f32 lbAudioAx_80027648(void);

static f32 mnHyaku_803EF668[3] = { 0.0f, 19.0f, -0.1f };
static f32 mnHyaku_803EF674[3] = { 20.0f, 29.0f, -0.1f };

static f32 mnHyaku_803EF680[6] = {
    0.0f, 1.0f, 2.0f, 3.0f, 4.0f, 5.0f,
};

StaticModelDesc mnHyaku_804A08E8;

static inline void mnHyaku_8024C68C_inline(HSD_JObj* jobj, s32 val)
{
    f32 temp_f31 = mn_8022F298(jobj);
    HSD_JObjReqAnimAll(jobj, mnHyaku_803EF680[val]);
    HSD_JObjAnimAll(jobj);
    HSD_JObjReqAnimAll(jobj, temp_f31);
    mn_8022F3D8(jobj, 0xFF, 0x80);
    HSD_JObjAnimAll(jobj);
}

// these are most likely ids to text
static u8 vals[] = { 0xAB, 0xAC, 0xAD, 0xAE, 0xAF, 0xB0, 0x00, 0x00 };

static inline void mnHyaku_8024C68C_inline_2(HSD_GObj* gobj)
{
    Menu* menu = GET_MENU(gobj);
    if (menu->text) {
        HSD_SisLib_803A5CC4(menu->text);
    }
    Menu_InitCenterText(menu, vals[menu->cursor]);
}

void mnHyaku_8024C68C(HSD_GObj* arg0)
{
    u64 ret;
    Menu* menu = GET_MENU(mnHyaku_804D6C58);
    if (mn_804D6BC8.x0 != 0) {
        mn_804D6BC8.x0--;
        mn_804D6BC8.x2 = 0;
        mn_804D6BC8.x4 = 0;
        return;
    }
    ret = mn_804A04F0.x8 = mn_80229624(4);
    if ((ret & 0x20)) {
        lbAudioAx_80024030(0);
        mn_804A04F0.x11 = 0;
        mn_80229894(9, 2, 3);
        return;
    }
    if (ret) {
        lbAudioAx_80024030(1);
        mn_802295AC();
        gm_801677E8();
        switch (menu->cursor) {
        case 0:
            mn_80229860(0x21);
            return;
        case 1:
            mn_80229860(0x22);
            return;
        case 2:
            mn_80229860(0x23);
            return;
        case 3:
            mn_80229860(0x24);
            return;
        case 4:
            mn_80229860(0x25);
            return;
        case 5:
            mn_80229860(0x26);
            return;
        }
    } else {
        if (ret & 4) {
            lbAudioAx_80024030(2);
            menu->cursor = (menu->cursor == 0) ? 5 : (menu->cursor - 1);
            mnHyaku_8024C68C_inline(mnHyaku_804D6C58->hsd_obj, menu->cursor);
            mnHyaku_8024C68C_inline_2(mnHyaku_804D6C58);
            return;
        }
        if (ret & 8) {
            lbAudioAx_80024030(2);
            menu->cursor = (menu->cursor == 5) ? 0 : (menu->cursor + 1);
            mnHyaku_8024C68C_inline(mnHyaku_804D6C58->hsd_obj, menu->cursor);
            mnHyaku_8024C68C_inline_2(mnHyaku_804D6C58);
        }
    }
}

void fn_8024C9F0(HSD_GObj* gobj)
{
    HSD_JObj* jobj = (HSD_JObj*) gobj->hsd_obj;
    f32 ret = mn_8022EC18(jobj, &mnHyaku_803EF674[0], 0x80);
    if (ret >= mnHyaku_803EF674[1]) {
        HSD_GObjPLink_80390228(gobj);
    }
}

void fn_8024CA50(HSD_GObj* gobj)
{
    HSD_GObjProc* gobj_proc;
    Menu* menu = GET_MENU(gobj);
    if (mn_804A04F0.x0 != 0x21) {
        HSD_GObjProc_8038FE24(HSD_GObj_804D7838);
        gobj_proc = HSD_GObjProc_8038FD54(gobj, fn_8024C9F0, 0U);
        gobj_proc->flags_3 = HSD_GObj_804D783C;
        HSD_SisLib_803A5CC4(menu->text);
    }
}

void fn_8024CAC8(HSD_GObj* gobj)
{
    {
        HSD_GObjProc* gobj_proc;
        Menu* menu = GET_MENU(gobj);
        if (mn_804A04F0.x0 != 0x21) {
            HSD_GObjProc_8038FE24(HSD_GObj_804D7838);
            gobj_proc = HSD_GObjProc_8038FD54(gobj, fn_8024C9F0, 0U);
            gobj_proc->flags_3 = HSD_GObj_804D783C;
            HSD_SisLib_803A5CC4(menu->text);
            return;
        }
    }
    if (mn_8022EC18(gobj->hsd_obj, &mnHyaku_803EF668[0], 0x80) ==
        mnHyaku_803EF668[1])
    {
        HSD_GObjProc* gobj_proc;
        HSD_GObjProc_8038FE24(HSD_GObj_804D7838);
        gobj_proc = HSD_GObjProc_8038FD54(gobj, fn_8024CA50, 0U);
        gobj_proc->flags_3 = HSD_GObj_804D783C;
    }
}

void mnHyaku_8024CB94(u8 arg0)
{
    HSD_GObj* gobj;
    HSD_GObjProc* proc;
    HSD_JObj* jobj;
    u8 temp_r29;
    Menu* menu;
    HSD_GObjProc* temp_r3_4;

    gobj = GObj_Create(HSD_GOBJ_CLASS_ITEM, 7U, 0x80);
    mnHyaku_804D6C58 = gobj;
    jobj = HSD_JObjLoadJoint(mnHyaku_804A08E8.joint);
    temp_r29 = HSD_GObj_804D7849;
    HSD_GObjObject_80390A70(gobj, temp_r29, jobj);
    GObj_SetupGXLink(gobj, HSD_GObj_80391070, 4, 0x80);
    HSD_JObjAddAnimAll(jobj, mnHyaku_804A08E8.animjoint,
                       mnHyaku_804A08E8.matanim_joint,
                       mnHyaku_804A08E8.shapeanim_joint);
    HSD_JObjReqAnimAll(jobj, 0.0F);
    HSD_JObjAnimAll(jobj);
    menu = HSD_MemAlloc(8);
    if (menu == NULL) {
        OSReport("Can't get menu.\n");
        __assert("mnhyaku.c", 344, "menu");
    }
    menu->cursor = arg0;
    menu->text = 0;
    GObj_InitUserData(gobj, 0, HSD_Free, menu);

    mnHyaku_8024C68C_inline(jobj, menu->cursor);
    temp_r3_4 = HSD_GObjProc_8038FD54(gobj, fn_8024CAC8, 0U);
    temp_r3_4->flags_3 = HSD_GObj_804D783C;
    mnHyaku_8024C68C_inline_2(gobj);
}

void mnHyaku_8024CD64(u8 arg0)
{
    HSD_GObjProc* temp_r3;
    HSD_Archive* archive;
    Vec3 pos;

    mn_804D6BC8.x0 = 5;
    mn_804A04F0.x1 = mn_804A04F0.x0;
    mn_804A04F0.x0 = 0x15;
    mn_804A04F0.x2 = 0;

    lbAudioAx_80026F2C(0x12);
    lbAudioAx_8002702C(2, 0, 8);
    lbAudioAx_80027168();
    pos.x = lbAudioAx_80027648();
    pos.y = mnHyaku_803EF668[0];
    pos.z = 0;
    archive = mn_804D6BB8;
    lbArchive_LoadSections(
        archive, (void**) &mnHyaku_804A08E8, "MenMainConKm_Top_joint",
        &mnHyaku_804A08E8.animjoint, "MenMainConKm_Top_animjoint",
        &mnHyaku_804A08E8.matanim_joint, "MenMainConKm_Top_matanim_joint",
        &mnHyaku_804A08E8.shapeanim_joint, "MenMainConKm_Top_shapeanim_joint",
        0);
    mnHyaku_8024CB94(arg0);
    temp_r3 = HSD_GObjProc_8038FD54(GObj_Create(0U, 1U, 0x80U),
                                    mnHyaku_8024C68C, 0U);
    temp_r3->flags_3 = HSD_GObj_804D783C;
    lbAudioAx_800237A8(0x7530, 0x7FU, 0x40U);
}
