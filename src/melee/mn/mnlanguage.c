#include <sysdolphin/baselib/gobj.h>
#include <sysdolphin/baselib/gobjgxlink.h>
#include <sysdolphin/baselib/gobjobject.h>
#include <sysdolphin/baselib/gobjplink.h>
#include <sysdolphin/baselib/gobjproc.h>
#include <sysdolphin/baselib/jobj.h>
#include <sysdolphin/baselib/memory.h>
#include <sysdolphin/baselib/sislib.h>
#include <melee/lb/lb_00F9.h>
#include <melee/lb/lbarchive.h>
#include <melee/lb/lbcardgame.h>
#include <melee/lb/lblanguage.h>
#include <melee/mn/inlines.h>
#include <melee/mn/mnlanguage.h>
#include <melee/mn/mnmain.h>

extern HSD_Archive* mn_804D6BB8;
static HSD_GObj* mnLanguage_804D6C50;

struct {
    HSD_Joint* x0;
    HSD_AnimJoint* x4;
    HSD_MatAnimJoint* x8;
    HSD_ShapeAnimJoint* xC;
} mnLanguage_804A08D8;

// language id -> frame map
static f32 mnLanguage_804D5018[2] = { 1, 0 };

static Vec3 mnLanguage_803EF5A0 = { 0, 19, -0.1 };
static Vec3 mnLanguage_803EF5AC = { 20, 29, -0.1 };

void mnLanguage_8024BFE0(HSD_GObj* arg0_unused)
{
    u64 temp_r3;
    u8 lang;
    struct {
        u8 x0, x1, x2, x3;
    }* temp_r31;
    HSD_JObj* sp2C;
    u8 _[4];
    HSD_JObj* sp24;

    temp_r31 = HSD_GObjGetUserData(mnLanguage_804D6C50);
    if (mn_804D6BC8.x0 != 0) {
        mn_804D6BC8.x0 -= 1;
        mn_804D6BC8.x2 = 0;
        mn_804D6BC8.x4 = 0;
        return;
    }
    temp_r3 = Menu_GetAllEvents();
    if (temp_r3 & 0x20) {
        lbAudioAx_80024030(0);
        mn_804A04F0.x11 = 0;
        mn_80229894(4, 4, 3);
        return;
    }
    if (temp_r3 & 0x200) {
        temp_r31 = HSD_GObjGetUserData(mnLanguage_804D6C50);
        if (temp_r31->x1 != temp_r31->x0) {
            lbLang_SetSavedLanguage(temp_r31->x0);
            lb_8001CE00();
            lbAudioAx_80027AB0(0xAD);
            mn_80229860(1);
            mn_8022F1A8(1, 9);
            mn_804A04F0.x0 = 4;
            mn_804A04F0.x2 = 4;
        }
    } else if (temp_r31->x2 != 0) {
        if (temp_r3 & 4) {
            lbAudioAx_80024030(2);
            temp_r31->x0 = temp_r31->x0 == 0 ? 1 : 0;
            lang = temp_r31->x0;
            lb_80011E24(mnLanguage_804D6C50->hsd_obj, &sp2C, 1, -1);
            HSD_JObjReqAnimAll(sp2C, mnLanguage_804D5018[lang]);
            mn_8022F3D8(sp2C, -1, JOBJ_MASK);
            HSD_JObjAnimAll(sp2C);
        } else if (temp_r3 & 8) {
            lbAudioAx_80024030(2);
            temp_r31->x0 = temp_r31->x0 == 0 ? 1 : 0;
            lang = temp_r31->x0;
            lb_80011E24(GET_JOBJ(mnLanguage_804D6C50), &sp24, 1, -1);
            HSD_JObjReqAnimAll(sp24, mnLanguage_804D5018[lang]);
            mn_8022F3D8(sp24, -1, JOBJ_MASK);
            HSD_JObjAnimAll(sp24);
        }
    }
}

void fn_8024C210(HSD_GObj* gobj)
{
    u8 _[4];
    HSD_JObj* jobj = GET_JOBJ(gobj);
    if (mn_8022EC18(jobj, &mnLanguage_803EF5AC.x, 0x80) >=
        mnLanguage_803EF5AC.y)
    {
        HSD_GObjPLink_80390228(gobj);
    }
}

void fn_8024C270(HSD_GObj* gobj)
{
    HSD_GObjProc* gobjproc;
    Menu* menu = GET_MENU(gobj);
    u8 _[12];

    if (mn_804A04F0.x0 != 0x17) {
        HSD_GObjProc_8038FE24(HSD_GObj_804D7838);
        gobjproc = HSD_GObjProc_8038FD54(gobj, fn_8024C210, 0);
        gobjproc->flags_3 = HSD_GObj_804D783C;
        HSD_SisLib_803A5CC4(menu->text);
    }
}

void fn_8024C2E8(HSD_GObj* gobj)
{
    HSD_GObjProc* gobjproc;
    Menu* menu = gobj->user_data;
    HSD_JObj* jobj = GET_JOBJ(gobj);
    f32 tmp;

    if (mn_804A04F0.x0 != 0x17) {
        HSD_GObjProc_8038FE24(HSD_GObj_804D7838);
        gobjproc = HSD_GObjProc_8038FD54(gobj, fn_8024C210, 0);
        gobjproc->flags_3 = HSD_GObj_804D783C;
        HSD_SisLib_803A5CC4(menu->text);
        return;
    }

    tmp = mn_8022EC18(jobj, &mnLanguage_803EF5A0.x, 0x80);
    if (tmp == mnLanguage_803EF5A0.y) {
        HSD_GObjProc_8038FE24(HSD_GObj_804D7838);
        gobjproc = HSD_GObjProc_8038FD54(gobj, fn_8024C270, 0);
        gobjproc->flags_3 = HSD_GObj_804D783C;
        menu->unk2 = 1;
    }
}

// Must not be declared inline, for proper .sdata2 float ordering
static void Menu_InitCenterText_noinline(Menu* menu, u8 val)
{
    HSD_Text* text =
        HSD_SisLib_803A5ACC(0, 1, -9.5F, 9.1F, 17.0F, 364.68332F, 38.38772F);
    menu->text = text;
    text->font_size.x = 0.0521F;
    text->font_size.y = 0.0521F;
    HSD_SisLib_803A6368(text, val);
}

void mnLanguage_8024C3C4(HSD_GObj* arg0_unused)
{
    HSD_GObj* gobj;
    HSD_GObjProc* gobjproc;
    HSD_JObj* jobj;
    HSD_Text* text;
    struct {
        u8 x0, x1, x2;
        u32 x4;
    }* user_data;
    Menu* menu;
    u8 lang;
    u32 _2[2];
    HSD_JObj* sp1C;
    u32 _1[2];

    gobj = GObj_Create(HSD_GOBJ_CLASS_ITEM, 7, 0x80);
    mnLanguage_804D6C50 = gobj;
    jobj = HSD_JObjLoadJoint(mnLanguage_804A08D8.x0);
    HSD_GObjObject_80390A70(gobj, HSD_GObj_804D7849, jobj);
    GObj_SetupGXLink(gobj, HSD_GObj_JObjCallback, 4, 0x80);
    HSD_JObjAddAnimAll(jobj, mnLanguage_804A08D8.x4, mnLanguage_804A08D8.x8,
                       mnLanguage_804A08D8.xC);
    HSD_JObjReqAnimAll(jobj, 0.0F);
    HSD_JObjAnimAll(jobj);
    user_data = HSD_MemAlloc(8);
    if (user_data == NULL) {
        OSReport("Can't get user_data.\n");
        __assert("mnlanguage.c", 0x163, "user_data");
    }
    lang = lbLang_GetSavedLanguage();
    user_data->x0 = lang;
    user_data->x1 = lang;
    user_data->x4 = 0;
    user_data->x2 = 0;
    GObj_InitUserData(gobj, 0, HSD_Free, user_data);
    gobjproc = HSD_GObjProc_8038FD54(gobj, fn_8024C2E8, 0);
    gobjproc->flags_3 = HSD_GObj_804D783C;
    lang = user_data->x0;
    lb_80011E24(GET_JOBJ(gobj), &sp1C, 1, -1);
    HSD_JObjReqAnimAll(sp1C, mnLanguage_804D5018[lang]);
    mn_8022F3D8(sp1C, -1, JOBJ_MASK);
    HSD_JObjAnimAll(sp1C);
    HSD_JObjReqAnimAll(jobj, 0.0F);
    mn_8022F3D8(jobj, -1, MOBJ_MASK);
    HSD_JObjAnimAll(jobj);
    menu = GET_MENU(mnLanguage_804D6C50);
    if (menu->text != NULL) {
        HSD_SisLib_803A5CC4(menu->text);
    }
    Menu_InitCenterText(menu, 0xBF);
}

void mnLanguage_8024C5C0(HSD_GObj* gobj)
{
    HSD_GObjProc* gobjproc;
    HSD_Archive* archive;

    mn_804D6BC8.x0 = 5;
    mn_804A04F0.x1 = mn_804A04F0.x0;
    mn_804A04F0.x0 = 0x17;
    mn_804A04F0.x2 = 0;
    archive = mn_804D6BB8;
    lbArchive_LoadSections(
        archive, (void**) &mnLanguage_804A08D8.x0, "MenMainConLa_Top_joint",
        &mnLanguage_804A08D8.x4, "MenMainConLa_Top_animjoint",
        &mnLanguage_804A08D8.x8, "MenMainConLa_Top_matanim_joint",
        &mnLanguage_804A08D8.xC, "MenMainConLa_Top_shapeanim_joint", 0);
    mnLanguage_8024C3C4(gobj);
    gobjproc =
        HSD_GObjProc_8038FD54(GObj_Create(0, 1, 0x80), mnLanguage_8024BFE0, 0);
    gobjproc->flags_3 = HSD_GObj_804D783C;
}
