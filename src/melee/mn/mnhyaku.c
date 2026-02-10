#include "mnhyaku.h"

#include "lb/lbarchive.h"
#include "lb/lbaudio_ax.h"
#include "mn/inlines.h"
#include "mn/mnmain.h"
#include "mn/types.h"

#include "sc/forward.h"

#include "sc/types.h"

static HSD_GObj* mnHyaku_804D6C58;

void gm_801677E8(void);

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
    // TODO: 0xFF seems to signal a "stopped" animation
    mn_8022F3D8(jobj, 0xFF, MOBJ_MASK);
    HSD_JObjAnimAll(jobj);
}

/// these are most likely ids to text
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
    u64 events;
    Menu* menu = GET_MENU(mnHyaku_804D6C58);
    PAD_STACK(8);

    if (mn_804D6BC8.cooldown != 0) {
        Menu_DecrementAnimTimer();
        return;
    }
    events = Menu_GetAllInputs();
    if (events & MenuInput_Back) {
        sfxBack();
        mn_804A04F0.entering_menu = 0;
        mn_80229894(9, 2, 3);
        return;
    }
    if (events & MenuInput_Confirm) {
        sfxForward();
        mn_802295AC();
        gm_801677E8();
        // load the different multi-man melee modes
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
        if (events & MenuInput_Left) {
            sfxMove();
            if (menu->cursor == 0) {
                menu->cursor = 5;
            } else {
                menu->cursor--;
            }
            mnHyaku_8024C68C_inline(mnHyaku_804D6C58->hsd_obj, menu->cursor);
            mnHyaku_8024C68C_inline_2(mnHyaku_804D6C58);
            return;
        }
        if (events & MenuInput_Right) {
            sfxMove();
            if (menu->cursor == 5) {
                menu->cursor = 0;
            } else {
                menu->cursor++;
            }
            mnHyaku_8024C68C_inline(mnHyaku_804D6C58->hsd_obj, menu->cursor);
            mnHyaku_8024C68C_inline_2(mnHyaku_804D6C58);
        }
    }
}

void mnHyaku_8024C9F0(HSD_GObj* gobj)
{
    HSD_JObj* jobj = (HSD_JObj*) gobj->hsd_obj;
    f32 ret = mn_8022EC18(jobj, &mnHyaku_803EF674[0], 0x80);
    if (ret >= mnHyaku_803EF674[1]) {
        HSD_GObjPLink_80390228(gobj);
    }
}

void mnHyaku_8024CA50(HSD_GObj* gobj)
{
    HSD_GObjProc* gobj_proc;
    Menu* menu = GET_MENU(gobj);
    if (mn_804A04F0.cur_menu != 0x21) {
        HSD_GObjProc_8038FE24(HSD_GObj_804D7838);
        gobj_proc = HSD_GObjProc_8038FD54(gobj, mnHyaku_8024C9F0, 0U);
        gobj_proc->flags_3 = HSD_GObj_804D783C;
        HSD_SisLib_803A5CC4(menu->text);
    }
}

void mnHyaku_8024CAC8(HSD_GObj* gobj)
{
    HSD_JObj* jobj;
    HSD_GObjProc* gobj_proc;
    Menu* menu;
    f32 res;
    PAD_STACK(12);

    jobj = (HSD_JObj*) gobj->hsd_obj;
    menu = GET_MENU(gobj);
    if (mn_804A04F0.cur_menu != 0x21) {
        HSD_GObjProc_8038FE24(HSD_GObj_804D7838);
        gobj_proc = HSD_GObjProc_8038FD54(gobj, mnHyaku_8024C9F0, 0U);
        gobj_proc->flags_3 = HSD_GObj_804D783C;
        HSD_SisLib_803A5CC4(menu->text);
        return;
    }
    res = mn_8022EC18(jobj, &mnHyaku_803EF668[0], 0x80);
    if (res == mnHyaku_803EF668[1]) {
        HSD_GObjProc_8038FE24(HSD_GObj_804D7838);
        gobj_proc = HSD_GObjProc_8038FD54(gobj, mnHyaku_8024CA50, 0U);
        gobj_proc->flags_3 = HSD_GObj_804D783C;
    }
}

inline static Menu* allocMenu(u8 arg0, HSD_GObj* gobj)
{
    Menu* user_data;

    user_data = HSD_MemAlloc(8);
    if (user_data == NULL) {
        OSReport("Can't get user_data.\n");
        __assert(__FILE__, 360, "user_data");
    }
    user_data->cursor = arg0;
    user_data->text = 0;
    GObj_InitUserData(gobj, 0, HSD_Free, user_data);
    return user_data;
}

void mnHyaku_8024CB94(u8 arg0)
{
    HSD_GObj* gobj;
    HSD_GObjProc* proc;
    HSD_JObj* jobj;
    Menu* menu;

    gobj = GObj_Create(HSD_GOBJ_CLASS_ITEM, 7U, 0x80);
    mnHyaku_804D6C58 = gobj;
    jobj = HSD_JObjLoadJoint(mnHyaku_804A08E8.joint);
    HSD_GObjObject_80390A70(gobj, HSD_GObj_804D7849, jobj);
    GObj_SetupGXLink(gobj, HSD_GObj_JObjCallback, 4, 0x80);
    HSD_JObjAddAnimAll(jobj, mnHyaku_804A08E8.animjoint,
                       mnHyaku_804A08E8.matanim_joint,
                       mnHyaku_804A08E8.shapeanim_joint);
    HSD_JObjReqAnimAll(jobj, 0.0F);
    HSD_JObjAnimAll(jobj);

    menu = allocMenu(arg0, gobj);
    mnHyaku_8024C68C_inline(jobj, menu->cursor);

    proc = HSD_GObjProc_8038FD54(gobj, mnHyaku_8024CAC8, 0U);
    proc->flags_3 = HSD_GObj_804D783C;

    menu = gobj->user_data;
    if (menu->text) {
        HSD_SisLib_803A5CC4(menu->text);
    }
    Menu_InitCenterText(menu, vals[menu->cursor]);
}

void mnHyaku_8024CD64(u8 arg0)
{
    HSD_GObjProc* proc;
    HSD_Archive* archive;

    mn_804D6BC8.cooldown = 5;
    mn_804A04F0.prev_menu = mn_804A04F0.cur_menu;
    mn_804A04F0.cur_menu = 33;
    mn_804A04F0.hovered_selection = 0;

    lbAudioAx_80026F2C(0x12);
    lbAudioAx_8002702C(2, 8);
    lbAudioAx_80027168();
    lbAudioAx_80027648();
    archive = mn_804D6BB8;
    lbArchive_LoadSections(
        archive, (void**) &mnHyaku_804A08E8, "MenMainConKm_Top_joint",
        &mnHyaku_804A08E8.animjoint, "MenMainConKm_Top_animjoint",
        &mnHyaku_804A08E8.matanim_joint, "MenMainConKm_Top_matanim_joint",
        &mnHyaku_804A08E8.shapeanim_joint, "MenMainConKm_Top_shapeanim_joint",
        0);
    mnHyaku_8024CB94(arg0);
    proc = HSD_GObjProc_8038FD54(GObj_Create(0U, 1U, 0x80U), mnHyaku_8024C68C,
                                 0U);
    proc->flags_3 = HSD_GObj_804D783C;
    lbAudioAx_800237A8(0x7530, 0x7FU, 0x40U);
}
