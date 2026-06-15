#include "mnsound.h"

#include "gm/gm_1601.h"
#include "gm/gmmain_lib.h"
#include "lb/lbarchive.h"
#include "lb/lbcardgame.h"
#include "mn/inlines.h"
#include "mn/mnmain.h"
#include "mn/types.h"
#include "sc/types.h"

#include <dolphin/os.h>
#include <baselib/controller.h>
#include <baselib/debug.h>
#include <baselib/gobj.h>
#include <baselib/gobjgxlink.h>
#include <baselib/gobjobject.h>
#include <baselib/gobjplink.h>
#include <baselib/gobjproc.h>
#include <baselib/gobjuserdata.h>
#include <baselib/jobj.h>
#include <baselib/memory.h>
#include <baselib/sislib.h>

/* 3EEED8 */ AnimLoopSettings mnSound_803EEED8[] = {
    { 0.0f, 199.0f, 0.0f },  { 0.0f, 29.0f, 0.0f }, { 30.0f, 59.0f, 30.0f },
    { 10.0f, 15.0f, -0.1f }, { 0.0f, 5.0f, -0.1f }, { 0.0f, 3.0f, -0.1f },
    { 4.0f, 7.0f, -0.1f }
};
/* 4A08A8 */ static StaticModelDesc mnSound_804A08A8;
/* 4D6C30 */ static HSD_GObj* mnSound_804D6C30;

static void mnSound_VolumeAnim(HSD_JObj* jobj, s32 sound_music_mix,
                               s32 anim_id)
{
    Vec3 pos_0;
    Vec3 pos_1;
    HSD_JObj* jobj_anim_0;
    HSD_JObj* jobj_anim_1;
    HSD_JObj* jobj_anim_2;
    lb_80011E24(jobj, &jobj_anim_0, 6, -1);
    lb_80011E24(jobj, &jobj_anim_1, 3, -1);
    lb_80011E24(jobj, &jobj_anim_2, 4, -1);
    HSD_JObjGetTranslation(jobj_anim_1, &pos_0);
    HSD_JObjGetTranslation(jobj_anim_2, &pos_1);
    HSD_JObjSetTranslateX(
        jobj_anim_0,
        (((f32) ((s8) sound_music_mix + 100) / 200.0f) * (pos_1.x - pos_0.x)) +
            pos_0.x);
    if (anim_id != -1) {
        HSD_JObjReqAnimAll(jobj_anim_0, mnSound_803EEED8[anim_id].start_frame);
    }
}

static void mnSound_ChannelAnim(HSD_JObj* jobj, s32 channel)
{
    HSD_JObj* jobj_anim[3];
    f32 temp_f30, temp_f31;
    lb_80011E24(jobj, &jobj_anim[0], 8, -1);
    lb_80011E24(jobj, &jobj_anim[1], 10, -1);
    lb_80011E24(jobj, &jobj_anim[2], 9, -1);
    temp_f31 = mn_8022F298(jobj_anim[1]);
    temp_f30 = mn_8022F298(jobj_anim[2]);

    HSD_JObjReqAnimAll(jobj_anim[0], channel);
    HSD_JObjAnimAll(jobj_anim[0]);

    HSD_JObjReqAnimAll(jobj_anim[1], temp_f31);
    mn_8022F3D8(jobj_anim[1], 0xFFU, MOBJ_MASK);
    HSD_JObjAnimAll(jobj_anim[1]);

    HSD_JObjReqAnimAll(jobj_anim[2], temp_f30);
    mn_8022F3D8(jobj_anim[2], 0xFFU, MOBJ_MASK);
    HSD_JObjAnimAll(jobj_anim[2]);
}

static inline void mnSound_InitCenterText(Menu* menu, s32 val)
{
    HSD_Text* text =
        HSD_SisLib_803A5ACC(0, 1, -9.5F, 9.1F, 17.0F, 364.68332F, 38.38772F);
    menu->text = text;
    text->font_size.x = 0.0521F;
    text->font_size.y = 0.0521F;
    HSD_SisLib_803A6368(text, val);
}

void mnSound_802492CC(HSD_GObj* gobj)
{
    Menu* menu = GET_MENU(mnSound_804D6C30);
    u64 events;
    PAD_STACK(8);
    if (mn_804D6BC8.cooldown != 0) {
        Menu_DecrementAnimTimer();
        return;
    }
    events = Menu_GetAllInputs();
    if (events & MenuInput_Back) {
        sfxBack();
        mn_804A04F0.entering_menu = 0;
        gmMainLib_8015ED80(GET_MENU(mnSound_804D6C30)->unk3);
        lb_8001CE00();
        mn_80229894(4, 1, 3);
        return;
    }
    if (events & (MenuInput_Up | MenuInput_Down)) {
        // switch between the two
        sfxMove();
        if ((u8) menu->unk2 == 0) {
            menu->unk2 = 1;
        } else {
            menu->unk2 = 0;
        }
        {
            Menu* menu = GET_MENU(mnSound_804D6C30);
            s32 text_id;
            if (menu->text != NULL) {
                HSD_SisLib_803A5CC4(menu->text);
            }
            if (menu->unk2 == 0) {
                text_id = 0xBB;
            } else {
                text_id = 0xBC;
            }
            mnSound_InitCenterText(menu, text_id);
        }
        return;
    }
    if (events & MenuInput_Left) {
        if (menu->unk2 == 0) {
            if (menu->unk1 == 1) {
                // switch from mono to stereo
                sfxMove();
                menu->unk1 = 0;
                mnSound_ChannelAnim(GET_JOBJ(mnSound_804D6C30), menu->unk1);
                lbAudioAx_80024C08(menu->unk1);
            }
        } else if ((s8) menu->unk3 > -100) {
            u8 mix;
            // move towards sounds
            lbAudioAx_80024030(2);
            menu->unk3 -= 5;
            mix = menu->unk3;
            mnSound_VolumeAnim(GET_JOBJ(mnSound_804D6C30), mix, 15);
            gm_801602C0(mix);
            gmMainLib_8015ED80(GET_MENU(mnSound_804D6C30)->unk3);
        }
    } else if (events & MenuInput_Right) {
        if (menu->unk2 == 0) {
            if (menu->unk1 == 0) {
                // switch from stereo to mono
                sfxMove();
                menu->unk1 = 1;
                mnSound_ChannelAnim(GET_JOBJ(mnSound_804D6C30), menu->unk1);
                lbAudioAx_80024C08(menu->unk1);
            }
        } else if ((s8) menu->unk3 < 100) {
            u8 mix;
            // move towards music
            lbAudioAx_80024030(2);
            menu->unk3 += 5;
            mix = menu->unk3;
            mnSound_VolumeAnim(GET_JOBJ(mnSound_804D6C30), mix, 18);
            gm_801602C0(mix);
            gmMainLib_8015ED80(GET_MENU(mnSound_804D6C30)->unk3);
        }
    }
}

void fn_80249A1C(HSD_GObj* arg0)
{
    Menu* menu = GET_MENU(arg0);
    HSD_JObj* sp40;
    HSD_JObj* sp3C;
    UNUSED u8 pad38[4];
    HSD_JObj* sp34;
    AnimLoopSettings sp28;
    UNUSED u8 pad24[4];
    HSD_JObj* sp20;
    f32 temp_f1;
    u8 temp_r4;
    AnimLoopSettings* anim = mnSound_803EEED8;
    HSD_JObj* jobj = arg0->hsd_obj;
    PAD_STACK(16);
    if ((u8) mn_804A04F0.cur_menu != 0x14) {
        HSD_GObjPLink_80390228(arg0);
        HSD_SisLib_803A5CC4(menu->text);
        return;
    }
    temp_r4 = menu->cursor;
    if (temp_r4 != 0) {
        menu->cursor = (u8) (temp_r4 - 1);
        if ((u8) menu->cursor != 0) {
            HSD_JObjSetFlagsAll(jobj, JOBJ_HIDDEN);
            return;
        }
        HSD_JObjClearFlagsAll(jobj, JOBJ_HIDDEN);
        return;
    }
    if ((u8) menu->unk2 == 0) {
        if ((u8) menu->unk1 == 0) {
            lb_80011E24(jobj, &sp34, 0xA, -1);
        } else {
            lb_80011E24(jobj, &sp34, 9, -1);
        }
        mn_8022EC18(sp34, anim, 0x80);
    }
    lb_80011E24((HSD_JObj*) arg0->hsd_obj, &sp20, 6, -1);
    temp_f1 = mn_8022F298(sp20);
    if ((anim[5].start_frame <= temp_f1) &&
        (temp_f1 <= anim[5].end_frame))
    {
        sp28 = anim[5];
    } else {
        sp28 = anim[6];
    }
    mn_8022ED6C(sp20, &sp28);
    lb_80011E24(jobj, &sp40, 0xE, -1);
    {
        AnimLoopSettings* temp = &anim[menu->unk2];
        mn_8022ED6C(sp40, temp + 1);
    }
    lb_80011E24(jobj, &sp3C, 0xB, -1);
    {
        AnimLoopSettings* temp = &anim[menu->unk1];
        mn_8022ED6C(sp3C, temp + 3);
    }
}

void mnSound_80249C08(int unused)
{
    HSD_GObj* gobj = GObj_Create(HSD_GOBJ_CLASS_ITEM, 7U, 0x80U);
    HSD_JObj* jobj;
    Menu* user_data;
    HSD_GObjProc* proc;
    PAD_STACK(24);
    mnSound_804D6C30 = gobj;
    jobj = HSD_JObjLoadJoint(mnSound_804A08A8.joint);
    HSD_GObjObject_80390A70((HSD_GObj*) gobj, (u8) HSD_GObj_804D7849, jobj);
    GObj_SetupGXLink((HSD_GObj*) gobj, HSD_GObj_JObjCallback, 4U, 0x80);
    HSD_JObjAddAnimAll(jobj, mnSound_804A08A8.animjoint,
                       mnSound_804A08A8.matanim_joint,
                       mnSound_804A08A8.shapeanim_joint);
    HSD_JObjReqAnimAll(jobj, 0.0F);
    {
        Menu* alloc = HSD_MemAlloc(8);
        user_data = alloc;
    }
    HSD_ASSERTREPORT(0x22CU, user_data, "Can't get user_data.\n");
    gmMainLib_8015CC34();
    user_data->cursor = 0x14;
    user_data->unk1 = lbAudioAx_80024BD0();
    user_data->unk2 = 0U;
    user_data->unk3 = gmMainLib_8015ED74();
    user_data->text = NULL;
    GObj_InitUserData(gobj, 0U, HSD_Free, user_data);
    proc = HSD_GObj_SetupProc(gobj, fn_80249A1C, 0U);
    proc->flags_3 = HSD_GObj_804D783C;

    {
        Menu* menu = GET_MENU(mnSound_804D6C30);
        s32 text_id;
        if (menu->text != NULL) {
            HSD_SisLib_803A5CC4(menu->text);
        }
        if (menu->unk2 == 0) {
            text_id = 0xBB;
        } else {
            text_id = 0xBC;
        }
        mnSound_InitCenterText(menu, text_id);
    }

    mnSound_ChannelAnim(GET_JOBJ(gobj), user_data->unk1);

    {
        HSD_JObj* sp5C;
        lb_80011E24(jobj, &sp5C, 6, -1);
        HSD_JObjReqAnimAll(sp5C, mnSound_803EEED8[5].end_frame);
        HSD_JObjAnimAll(sp5C);
    }

    mnSound_VolumeAnim(GET_JOBJ(gobj), user_data->unk3, -1);

    {
        HSD_JObj* sp64;
        HSD_JObj* sp60;
        gm_801602C0(user_data->unk3);
        lb_80011E24(jobj, &sp64, 0xE, -1);
        {
            AnimLoopSettings* anim = &mnSound_803EEED8[user_data->unk2];
            mn_8022ED6C(sp64, anim + 1);
        }
        lb_80011E24(jobj, &sp60, 0xB, -1);
        HSD_JObjReqAnimAll(sp60, mnSound_803EEED8[user_data->unk1 + 3].end_frame);
        HSD_JObjAnimAll(sp60);
        HSD_JObjSetFlagsAll(jobj, JOBJ_HIDDEN);
    }
}

void mnSound_8024A09C(int arg0)
{
    s32 spC;
    HSD_GObjProc* temp_r3;
    HSD_Archive* archive;

    mn_804D6BC8.cooldown = 5;
    mn_804A04F0.prev_menu = mn_804A04F0.cur_menu;
    mn_804A04F0.cur_menu = 0x14; // @note: could this be an enum??
    mn_804A04F0.hovered_selection = 0;
    archive = mn_804D6BB8;
    lbArchive_LoadSections(
        archive, (void**) &mnSound_804A08A8.joint, "MenMainConSo_Top_joint",
        &mnSound_804A08A8.animjoint, "MenMainConSo_Top_animjoint",
        &mnSound_804A08A8.matanim_joint, "MenMainConSo_Top_matanim_joint",
        &mnSound_804A08A8.shapeanim_joint, "MenMainConSo_Top_shapeanim_joint",
        0);
    mnSound_80249C08(arg0);
    temp_r3 = HSD_GObj_SetupProc(GObj_Create(0, 1, 0x80), mnSound_802492CC, 0);
    temp_r3->flags_3 = HSD_GObj_804D783C;
}
