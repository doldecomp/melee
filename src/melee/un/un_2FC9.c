#include "baselib/forward.h"
#include "pl/forward.h"
#include "sc/forward.h"
#include "un/forward.h"

#include "un_2FC9.static.h"

#include "baselib/jobj.h"
#include "baselib/memory.h"
#include "baselib/random.h"
#include "baselib/sislib.h"
#include "cm/camera.h"
#include "gm/gm_unsplit.h"
#include "gm/gm_1A3F.h"
#include "gm/gm_1A45.h"
#include "gm/gm_1B03.h"
#include "gm/gmmain_lib.h"
#include "if/ifall.h"
#include "lb/lb_00B0.h"
#include "lb/lb_00F9.h"
#include "lb/lbarchive.h"
#include "lb/lbaudio_ax.h"
#include "lb/lblanguage.h"
#include "lb/lbvector.h"
#include "mn/mnmain.h"
#include "mn/mnname.h"
#include "pl/player.h"
#include "ty/toy.h"
#include "un/types.h"
#include "un/un_2FC9.h"

#include <printf.h>
#include <stdarg.h>
#include <dolphin/mtx.h>
#include <baselib/cobj.h>
#include <baselib/fog.h>
#include <baselib/gobj.h>
#include <baselib/gobjgxlink.h>
#include <baselib/gobjobject.h>
#include <baselib/gobjplink.h>
#include <baselib/gobjproc.h>
#include <baselib/gobjuserdata.h>
#include <baselib/lobj.h>
#include <baselib/memory.h>
#include <baselib/particle.h>
#include <baselib/sislib.h>
#include <MSL/stdio.h>
#include <MSL/string.h>

#pragma push
#pragma dont_inline on
float un_802FC9B4(unsigned char slot, unsigned char arg1, unsigned char arg2,
                  unsigned char arg3)
{
    u8 player_id = Player_GetPlayerId(slot);
    if (arg2) {
        if (!arg3) {
            return un_803F98B8[player_id][arg1];
        }
        if ((gm_8016B258(player_id) || gm_8016B0E8()) &&
            arg1 == Player_GetTeam(0))
        {
            return un_803F98B8[5][Player_GetPlayerId(0)];
        }
        return un_803F98B8[4][arg1];
    }
    if (!arg3) {
        return un_803F98B8[player_id][3];
    }
    return 18.0; // CP Gray
}
#pragma pop

static void NameTag_RenderCallback(HSD_GObj* gobj, int pass)
{
    HSD_GObj_JObjCallback(gobj, pass);
}

void fn_802FCAC4(HSD_GObj* gobj, int pass)
{
    if (ifAll_IsHUDHidden() || un_804D6D6C) {
        int i;
        for (i = 0; i < PL_SLOT_MAX; i++) {
            int do_it;
            if (Player_GetPlayerSlotType(i) ||
                Player_GetNametagSlotID(i) == 0x78)
            {
                do_it = false;
            } else {
                do_it = true;
            }
            if (do_it) {
                HSD_SisLib_803A746C(un_804D6D78, un_804A1EF8[i], -5000.0f,
                                    0.0f);
            }
        }
    } else if (HSD_CObjSetCurrent(gobj->hsd_obj)) {
        HSD_GObj_80390ED0(gobj, 7);
        HSD_CObjEndCurrent();
    }
}

void un_802FCBA0(void)
{
    HSD_Archive** archive;
    DynamicModelDesc** x;

    archive = ifAll_802F3690();
    lbArchive_LoadSections(*archive, (void**) &x, "ScInfPnm_scene_models", 0);
    un_804A1ED0.joint = x[0]->joint;
    if (x[0]->anims) {
        un_804A1ED0.animjoint = x[0]->anims[0];
    }
    if (x[0]->matanims) {
        un_804A1ED0.matanim_joint = x[0]->matanims[0];
    }
    if (x[0]->shapeanims) {
        un_804A1ED0.shapeanim_joint = x[0]->shapeanims[0];
    }
}

static inline bool has_nametag(int slot)
{
    if (Player_GetPlayerSlotType(slot) != Gm_PKind_Human ||
        Player_GetNametagSlotID(slot) == NAMETAG_DISABLED)
    {
        return false;
    } else {
        return true;
    }
}

void fn_802FCC44(HSD_GObj* gobj)
{
    Vec3 vec;
    Vec3 vec2;
    u8* slot = HSD_GObjGetUserData(gobj);
    HSD_JObj* jobj = gobj->hsd_obj;
    PAD_STACK(8);
    if (Player_GetPlayerSlotType(*slot) != 3 && Player_GetPlayerState(*slot) &&
        Player_GetStocks(*slot) &&
        (un_804D6D70[*slot] || Player_GetNametagSlotID(*slot) != 'x' ||
         Player_80036058(*slot) || gm_8016B258(*slot)))
    {
        HSD_JObjClearFlags(HSD_JObjGetChild(jobj), 0x10);
    } else {
        HSD_JObjSetFlags(HSD_JObjGetChild(jobj), 0x10);
        if (has_nametag(*slot)) {
            HSD_SisLib_803A746C(un_804D6D78, un_804A1EF8[*slot], 5000.0f,
                                0.0f);
        }
        return;
    }
    Player_LoadPlayerCoords(*slot, &vec);
    vec.y += Player_800360D8(*slot);
    vec.y -= 2.5f;
    lbVector_WorldToScreen(Camera_80030A50()->hsd_obj, &vec, &vec2, 0);
    HSD_JObjSetTranslateX(jobj, vec2.x);
    HSD_JObjSetTranslateY(jobj, -vec2.y);
    if (has_nametag(*slot)) {
        HSD_SisLib_803A746C(un_804D6D78, un_804A1EF8[*slot], vec.x,
                            vec.y - 56.0f);
    }
}

static inline float inlineA1(float var_f31)
{
    int q = var_f31;
    if (q >= 16) {
        return 28.0f;
    } else {
        return (q % 4) + 20;
    }
}

void NameTag_Create(int slot)
{
    HSD_GObj* gobj = GObj_Create(HSD_GOBJ_CLASS_UI, 15, 0);
    PAD_STACK(8);
    un_804A1EE0[slot] = gobj;
    {
        HSD_JObj* jobj = HSD_JObjLoadJoint(un_804A1ED0.joint);
        HSD_GObjObject_80390A70(gobj, HSD_GObj_804D7849, jobj);
        GObj_SetupGXLink(gobj, NameTag_RenderCallback, 9, 0);
        HSD_JObjSetScaleX(jobj, 10.0f);
        HSD_JObjSetScaleY(jobj, 10.0f);
        HSD_JObjSetScaleZ(jobj, 10.0f);
        HSD_JObjAddAnimAll(jobj, un_804A1ED0.animjoint,
                           un_804A1ED0.matanim_joint,
                           un_804A1ED0.shapeanim_joint);
        {
            float f = un_802FC9B4(slot, Player_GetTeam(slot), gm_8016B168(),
                                  Player_GetPlayerSlotType(slot));
            if (has_nametag(slot)) {
                f = inlineA1(f);
                un_804A1EF8[slot] = HSD_SisLib_803A6B98(
                    un_804D6D78, -5000.0f, 0.0f,
                    GetNameText(Player_GetNametagSlotID(slot)));
                HSD_SisLib_803A7548(un_804D6D78, un_804A1EF8[slot], 0.4f,
                                    0.55f);
            }
            HSD_JObjReqAnimAll(jobj, f);
        }
        HSD_JObjAnimAll(jobj);
    }
    {
        char* user_data = HSD_MemAlloc(1);
        GObj_InitUserData(gobj, 0, mn_8022EB04, user_data);
        *user_data = slot;
    }
    HSD_GObjProc_8038FD54(gobj, fn_802FCC44, 17);
}

void un_802FD28C(int slot)
{
    float f;
    HSD_JObj* jobj = un_804A1EE0[slot]->hsd_obj;
    PAD_STACK(16);
    f = un_802FC9B4(slot, Player_GetTeam(slot), gm_8016B168(),
                    Player_GetPlayerSlotType(slot));
    if (has_nametag(slot)) {
        f = inlineA1(f);
        HSD_SisLib_803A75E0(un_804D6D78, un_804A1EF8[slot]);
        un_804A1EF8[slot] =
            HSD_SisLib_803A6B98(un_804D6D78, -5000.0f, 0.0f,
                                GetNameText(Player_GetNametagSlotID(slot)));
        HSD_SisLib_803A7548(un_804D6D78, un_804A1EF8[slot], 0.4f, 0.55f);
    }
    HSD_JObjReqAnimAll(jobj, f);
    HSD_JObjAnimAll(jobj);
}

void un_802FD404(void)
{
    un_804D6D70[0] = 1;
    un_804D6D70[1] = 1;
    un_804D6D70[2] = 1;
    un_804D6D70[3] = 1;
    un_804D6D70[4] = 1;
    un_804D6D70[5] = 1;
}

void un_802FD428(void)
{
    memzero(un_804D6D70, sizeof(un_804D6D70));
}

void un_802FD450(void)
{
    un_804D6D6C = 1;
}

void un_802FD45C(void)
{
    un_804D6D6C = 0;
}

void un_802FD468(void)
{
    int i;
    for (i = 0; i < PL_SLOT_MAX; i++) {
        if (un_804A1EE0[i]) {
            HSD_GObjPLink_80390228(un_804A1EE0[i]);
        }
    }
    HSD_GObjPLink_80390228(un_804D6D68);
}

#pragma push
#pragma dont_inline on
void un_802FD4C8(void)
{
    HSD_GObj* gobj;
    int i = 0;
    un_804A1EE0[0] = NULL;
    un_804A1EE0[1] = NULL;
    un_804A1EE0[2] = NULL;
    un_804A1EE0[3] = NULL;
    un_804A1EE0[4] = NULL;
    un_804A1EE0[5] = NULL;
    un_804D6D68 = NULL;
    un_804D6D6C = 0;
    memzero(un_804D6D70, sizeof(un_804D6D70));
    un_804D6D68 = gobj = GObj_Create(HSD_GOBJ_CLASS_UI, 15, 0);
    HSD_GObjObject_80390A70(
        gobj, HSD_GObj_804D784B,
        lb_80013B14((HSD_CameraDescPerspective*) &nametag_CObjDesc));
    GObj_SetupGXLinkMax(gobj, fn_802FCAC4, 6);
    gobj->gxlink_prios = 0x200;
    un_804D6D7C = HSD_SisLib_803A611C(2, gobj, 14, 15, 0, 9, 6, 0);
    HSD_SisLib_803A62A0(2, "SdIntro.dat", "SIS_IntroData");
    un_804D6D78 = HSD_SisLib_803A6754(2, un_804D6D7C);
    un_804D6D78->x8 = -10.0;
    un_804D6D78->x4A = 1;
    un_802FCBA0();
    for (; i < PL_SLOT_MAX; i++) {
        NameTag_Create(i);
    }
}
#pragma pop

void un_802FD604(int arg)
{
    HSD_JObj* jobj = GET_JOBJ(un_804D6D80);
    HSD_JObjReqAnimAll(jobj, 0.0);
    HSD_JObjAnimAll(jobj);
    un_804D6D84 = arg;
    un_804D6D88 = 1;
}

void un_802FD65C(void)
{
    un_804D6D88 = 0;
}

void un_802FD668(void)
{
    un_804D6D8C = 1;
}

void un_802FD674(void)
{
    un_804D6D8C = 0;
}

void fn_802FD680(HSD_GObj* gobj)
{
    HSD_JObj* jobj = GET_JOBJ(gobj);
    if (un_804D6D84) {
        un_804D6D84--;
        if (un_804D6D84 == 0) {
            un_804D6D88 = 0;
        }
    }
    HSD_JObjAnimAll(jobj);
}

void fn_802FD6CC(HSD_GObj* gobj, int pass)
{
    if (!un_804D6D8C && un_804D6D88) {
        HSD_GObj_JObjCallback(gobj, pass);
    }
}

void un_802FD704(void) {}

void un_802FD708(void* arg0, int arg1)
{
    HSD_GObj* gobj = GObj_Create(HSD_GOBJ_CLASS_UI, 15, 0);
    HSD_JObj* jobj = HSD_JObjLoadJoint(*(HSD_Joint**) arg0);
    HSD_GObjObject_80390A70(gobj, HSD_GObj_804D7849, jobj);
    GObj_SetupGXLink(gobj, fn_802FD6CC, 11, 0);
    gm_8016895C(jobj, arg0, 0);
    HSD_GObjProc_8038FD54(gobj, fn_802FD680, 17);
    un_804D6D88 = 0;
    un_804D6D8C = 0;
    un_804D6D80 = gobj;
    if (!arg1) {
        Vec3 v;
        HSD_JObjGetTranslation(jobj, &v);
        v.x += 18.0f;
        HSD_JObjSetTranslate(jobj, &v);
    }
}

#pragma push
#pragma dont_inline on
void un_802FD8A0(void* arg0)
{
    un_802FD708(arg0, 0);
}

void un_802FD8C4(void* arg0)
{
    un_802FD708(arg0, 1);
}

void un_802FD8E8(void* arg0)
{
    un_802FD708(arg0, 2);
}
#pragma pop

void un_802FD90C(void) {}

void un_802FD910(void)
{
    un_804D6D90 = 1;
}

void un_802FD91C(void)
{
    un_804D6D90 = 0;
}

void un_802FD928(unsigned char slot, int arg1, void* arg2)
{
    if (slot < 4) {
        int i;
        for (i = 0; i < 4; i++) {
            Gm_PKind type = Player_GetPlayerSlotType(slot);
            if (type != Gm_PKind_Cpu && !un_804A1F10.x28[i] &&
                !un_804A1F10.x24[slot])
            {
                un_804A1F10.x24[slot] = 1;
                un_804A1F10.x2C[i] = slot;
                un_804A1F10.x28[i] = arg1;
                un_804A1F10.x14[i] = *(int*) arg2;
                return;
            }
        }
    }
}

void un_802FD9D8(unsigned char slot)
{
    int i;
    for (i = 0; i < 4; i++) {
        if (un_804A1F10.x2C[i] == slot) {
            un_804A1F10.x24[slot] = 0;
            un_804A1F10.x28[i] = 0;
        }
    }
}

void fn_802FDA4C(HSD_GObj* gobj, int pass)
{
    if (un_804D6D90 == 0) {
        HSD_GObj_JObjCallback(gobj, pass);
    }
}

void fn_802FDA78(HSD_GObj* gobj)
{
    HSD_JObj* jobj = gobj->hsd_obj;
    unsigned char* slot = gobj->user_data;
    HSD_JObjSetTranslateZ(jobj, 0.0);
    HSD_JObjSetTranslateZ(jobj, 10000.0);
    HSD_JObjSetRotationZ(jobj, 0.0);
    HSD_JObjSetTranslateY(jobj, 2.6);
    HSD_JObjSetTranslateX(jobj, -25.0);
    HSD_JObjSetRotationZ(jobj, 3.1415927);
    HSD_JObjSetTranslateY(jobj, 2.6);
    HSD_JObjSetTranslateX(jobj, 25.0);
    HSD_JObjAnimAll(jobj);
}

void un_802FE260(void)
{
    HSD_GObj* gobj;
    HSD_JObj* jobj;
    int i;

    un_804D6D90 = 0;
    lbArchive_LoadSections(*ifAll_802F3690(), (void*) &un_804A1F10.x0,
                           "Stc_rarwmdls", 0);
    for (i = 0; i < 4; i++) {
        gobj = GObj_Create(HSD_GOBJ_CLASS_UI, 15, 0);
        jobj = HSD_JObjLoadJoint(un_804A1F10.x0[0]->joint);
        gobj->user_data = &un_804DDBA8[i];
        HSD_GObjObject_80390A70(gobj, HSD_GObj_804D7849, jobj);
        GObj_SetupGXLink(gobj, fn_802FDA4C, 11, 0);
        gm_8016895C(jobj, un_804A1F10.x0[0], 0);
        HSD_GObjProc_8038FD54(gobj, fn_802FDA78, 17);
        HSD_JObjReqAnimAll(jobj, 0.0);
        HSD_JObjAnimAll(jobj);
        un_804A1F10.x24[i] = 0;
        un_804A1F10.x28[i] = 0;
        un_804A1F10.x4[i] = gobj;
    }
    un_804A1F10.x31 = -1;
    un_804A1F10.x32 = 0;
    un_804A1F10.x30 = gm_8016B124();
}

void un_802FE390(void)
{
    int i;
    PAD_STACK(8);
    for (i = 0; i < 4; i++) {
        if (un_804A1F10.x4[i] != 0) {
            HSD_GObjPLink_80390228(un_804A1F10.x4[i]);
            un_804A1F10.x4[i] = 0;
        }
    }
}

/// #un_802FE3F8

void fn_802FE470(HSD_GObj* gobj) {}

void un_802FE6A8(void)
{
    HSD_GObj* gobj_camera;
    HSD_GObj* gobj_light;
    HSD_GObj* gobj_ui;
    HSD_JObj* jobj_ui;
    U8Vec4 color = { 0x5A, 0x5A, 0x5A, 0xFF };
    HSD_Text* text;
    HSD_Text* text2;
    gobj_camera = GObj_Create(HSD_GOBJ_CLASS_CAMERA, 20, 0);
    HSD_GObjObject_80390A70(gobj_camera, HSD_GObj_804D784B,
                            HSD_CObjLoadDesc(un_804D6D9C->cameras[0].desc));
    GObj_SetupGXLinkMax(gobj_camera, HSD_GObj_803910D8, 8);
    gobj_camera->gxlink_prios = 0xC00;
    gobj_light = GObj_Create(HSD_GOBJ_CLASS_LIGHT, 3, 0);
    HSD_GObjObject_80390A70(gobj_light, HSD_GObj_804D784A,
                            lb_80011AC4(un_804D6D9C->lights));
    GObj_SetupGXLink(gobj_light, HSD_GObj_LObjCallback, 10, 0);
    gobj_ui = GObj_Create(HSD_GOBJ_CLASS_UI, 15, 0);
    jobj_ui = HSD_JObjLoadJoint(un_804D6D9C->models[0]->joint);
    HSD_GObjObject_80390A70(gobj_ui, HSD_GObj_804D7849, jobj_ui);
    GObj_SetupGXLink(gobj_ui, HSD_GObj_JObjCallback, 11, 0);
    HSD_GObjProc_8038FD54(gobj_ui, fn_802FE470, 17);
    gm_8016895C(jobj_ui, un_804D6D9C->models[0], 0);
    HSD_JObjReqAnimAll(jobj_ui, 0.0);
    HSD_JObjAnimAll(jobj_ui);
    lb_80011E24(jobj_ui, 0, 2, -1);
    HSD_SisLib_803A611C(2, 0, 9, 20, 0, 14, 0, 18);
    text = HSD_SisLib_803A5ACC(2, 0, 105.0, 202.0, 0.0, 435.0, 75.0);
    text->x48 = 1;
    text->x4A = 1;
    text2 = HSD_SisLib_803A6754(2, 0);
    text2->x4A = 1;
    text2->x49 = 1;
    text2->x30 = color;
}

void un_802FE8CC(void)
{
    HSD_SisLib_803A5F50(2);
}

/// #un_802FE918

void un_802FEBE0_OnEnter(void* arg0)
{
    un_803124BC();
    HSD_Randi(3);
    if (*un_803F9B30 == 66) {
        un_802FE3F8();
        lbArchive_80016DBC(0, 0);
        if (lbLang_IsSavedLanguageUS()) {
            HSD_SisLib_803A62A0(2, "SdPrize.usd", "SIS_PrizeData");
        } else {
            HSD_SisLib_803A62A0(2, "SdPrize.dat", "SIS_PrizeData");
        }
        un_802FE6A8();
        return;
    }
}

void un_802FED10_OnLeave(UNK_T unused) {}

/// #fn_802FED14

void un_802FEFAC(void)
{
    HSD_GObj* gobj_camera;
    HSD_GObj* gobj_light;
    HSD_GObj* gobj_ui;
    HSD_JObj* jobj_ui;
    gobj_camera = GObj_Create(HSD_GOBJ_CLASS_CAMERA, 21, 0);
    HSD_GObjObject_80390A70(gobj_camera, HSD_GObj_804D784B,
                            HSD_CObjLoadDesc(un_804D6DA4->cameras[0].desc));
    GObj_SetupGXLinkMax(gobj_camera, HSD_GObj_803910D8, 9);
    gobj_camera->gxlink_prios = 0x8400;
    gobj_light = GObj_Create(HSD_GOBJ_CLASS_LIGHT, 3, 0);
    HSD_GObjObject_80390A70(gobj_light, HSD_GObj_804D784A,
                            lb_80011AC4(un_804D6DA4->lights));
    GObj_SetupGXLink(gobj_light, HSD_GObj_LObjCallback, 10, 0);
    gobj_ui = GObj_Create(HSD_GOBJ_CLASS_UI, 14, 0);
    jobj_ui = HSD_JObjLoadJoint(un_804D6DA4->models[0]->joint);
    HSD_GObjObject_80390A70(gobj_ui, HSD_GObj_804D7849, jobj_ui);
    GObj_SetupGXLink(gobj_ui, HSD_GObj_JObjCallback, 15, 0);
    HSD_GObjProc_8038FD54(gobj_ui, fn_802FED14, 17);
    gm_8016895C(jobj_ui, un_804D6DA4->models[0], 0);
    HSD_JObjSetFlagsAll(jobj_ui, 0x10);
    HSD_JObjReqAnimAll(jobj_ui, 0.0);
    HSD_JObjAnimAll(jobj_ui);
    un_803F9E08.xC = gobj_ui;
}

void un_802FF128(int arg0, int arg1, int arg2, int arg3)
{
    if (arg3 < 1) {
        arg3 = 1;
    }
    un_803F9E08.x0.b1 = 1;
    un_803F9E08.x0.b234 = arg3;
    un_803F9E08.x0.b567 = arg3;
    un_803F9E08.x1 = 0;
    if (arg2 > 100) {
        arg2 = 100;
    }
    un_803F9E08.x2 = arg2;
    un_803F9E08.x4 = arg0;
    un_803F9E08.x8 = -arg1;
}

void un_802FF190(void)
{
    un_803F9E08.x0.b0 = 0;
    un_803F9E08.x0.b1 = 0;
}

void un_802FF1B4(void)
{
    un_803F9E08.x0.b0 = 1;
    un_803F9E08.x0.b1 = 0;
    un_804D6DA0 = lbArchive_80016DBC("IfCoGet.dat", &un_804D6DA4,
                                     "ScInfCgt_scene_data", 0);
    un_802FEFAC();
}

void fn_802FF218(HSD_GObj* arg0)
{
    int x;
    int y = -1;
    for (x = 0; x < 6; x++) {
        if (un_804A1F58[x].x8.x0 == arg0) {
            y = x;
            break;
        }
    }
    if (y >= 0) {
        if (un_804A1F58[y].x0 == 1) {
            HSD_SisLib_803A70A0(un_804A1F58[y].x8.x4,
                                (void*) un_804A1F58[y].x4, 0);
        } else {
            int s;
            gm_8016B774();
            s = gm_8016C658(y);
            if (s > 9999) {
                s = 9999;
            }
            if (un_804A1F58[y].x0 != s) {
                HSD_SisLib_803A70A0(un_804A1F58[y].x8.x4,
                                    (void*) un_804A1F58[y].x4, 0);
                un_804A1F58[y].x0 = s;
            }
        }
    }
}

void fn_802FF360(void* arg0) {}

void un_802FF364(int slot)
{
    int s;
    Vec3* ifAll;
    struct un_804A1F58_x8_t* thing;
    HSD_GObj* gobj;
    thing = &un_804A1F58[slot].x8;
    gobj = thing->x0;
    ifAll = ifAll_802F3424(slot);
    if (gobj) {
        HSD_GObjPLink_80390228(gobj);
    }
    if (thing->x4) {
        HSD_SisLib_803A5CC4(thing->x4);
    }
    thing->x4 = HSD_SisLib_803A6754(2, un_804A1F58->x0);
    thing->x4->x4A = 1;
    thing->x4->x49 = 1;
    gm_8016B774();
    s = gm_8016C658(slot);
    if (s > 9999) {
        s = 9999;
    }
    thing->x8 =
        HSD_SisLib_803A6B98(thing->x4, ifAll->x, ifAll->y + 3.2f, "%d", s);
    HSD_SisLib_803A7548(thing->x4, thing->x8, 0.06, 0.06);
    thing->x4->x58 = fn_802FF360;
    thing->x0 = GObj_Create(HSD_GOBJ_CLASS_UI, 15, 0);
    HSD_GObjProc_8038FD54(thing->x0, fn_802FF218, 17);
}

void un_802FF498(void)
{
    memzero(un_804A1F58, sizeof(un_804A1F58));
    un_804A1F58->x0 =
        HSD_SisLib_803A611C(2, ifAll_802F3404(), 14, 15, 0, 11, 0, 19);
}

void un_802FF4FC(void)
{
    int i;
    for (i = 0; i < 6; i++) {
        if (un_804A1F58[i].x8.x0) {
            HSD_GObjPLink_80390228(un_804A1F58[i].x8.x0);
        }
        if (un_804A1F58[i].x8.x4) {
            HSD_SisLib_803A5CC4(un_804A1F58[i].x8.x4);
        }
    }
}

void un_802FF570(void)
{
    int i;
    for (i = 0; i < 6; i++) {
        if (un_804A1F58[i].x8.x4) {
            un_804A1F58[i].x8.x4->x4D = 1;
        }
    }
}

void un_802FF620(void)
{
    int i;
    for (i = 0; i < 6; i++) {
        un_804A1F58[i].x0 = 0;
        if (un_804A1F58[i].x8.x4) {
            un_802FF364(i);
            un_804A1F58[i].x8.x4->x4D = 0;
        }
    }
}

void un_802FF6A0(void)
{
    HSD_GObj* gobj = GObj_Create(HSD_GOBJ_CLASS_LIGHT, 3, 0);
    HSD_GObjObject_80390A70(gobj, HSD_GObj_804D784A,
                            HSD_LObjLoadDesc(&un_803F9ED4));
    GObj_SetupGXLink(gobj, HSD_GObj_LObjCallback, 0, 0);
}

void un_802FF710(void)
{
    HSD_GObj* gobj = GObj_Create(HSD_GOBJ_CLASS_CAMERA, 20, 0);
    if (gobj) {
        HSD_GObjObject_80390A70(gobj, HSD_GObj_804D784B,
                                HSD_CObjLoadDesc(&un_803F9E60));
        GObj_SetupGXLinkMax(gobj, HSD_GObj_803910D8, 11);
        gobj->gxlink_prios = 0x20000;
    }
}

HSD_GObj* un_802FF78C(void)
{
    HSD_GObj* gobj = DevText_Setup(21, 24, 0, 17, 0, 11);
    if (gobj) {
        un_80304138();
    }
    return gobj;
}

void un_802FF7DC(void)
{
    lbArchive_LoadSymbols(0, 0);
}

bool un_802FF884(char* unused)
{
    return false;
}

int un_802FF88C(void)
{
    un_804D6DB8 = 0;
    un_804D5858 = 0x7F;
    un_804D5854 = 0x7F;
    un_804D5850 = 0x7F;
    un_804D6DB4 = 0;
    un_804D6DB0 = 0;
    un_804D6DC0 = 0;
    un_804D585C = -1;
    un_804D6DBC = lbAudioAx_80024BD0();
    lbAudioAx_800236DC();
    lbAudioAx_800245D4(0x7F);
    lbAudioAx_800245F4(0x7F);
    lbAudioAx_80024614(0x7F);
    if (un_80302DF0()) {
        un_80302DF8(un_80302DF0(), (int) fn_802FFCC8);
    }
    {
        struct {
            int x0;
            struct {
                char pad[8];
                float x8;
                float xC;
            }* x4;
        }* x = un_80302DF0();
        x->x4->x8 = 16.0f;
        x->x4->xC = 32.0f;
    }
    return 1;
}

void un_802FF934(void)
{
    lbAudioAx_80024C08(un_804D6DBC);
}

int un_802FF958(void)
{
    lbAudioAx_800245F4(un_804D5854);
    lbAudioAx_80024614(un_804D5858);
    lbAudioAx_800245D4(un_804D5850);
    return 0;
}

int un_802FF99C(int arg0)
{
    lbAudioAx_80024634(un_804D6DAC);
    un_802FFB58(arg0);
    return 0;
}

/// #un_802FF9DC

int un_802FFB58(int arg0)
{
    if (arg0 == 1) {
        lbAudioAx_80023694();
        lbAudioAx_80023B24(un_804D6DA8[un_804D6DB4]);
    } else if (arg0 == 0) {
        lbAudioAx_80023694();
    }
    return 0;
}

int un_802FFBAC(int arg0)
{
    if (arg0 == 1) {
        if (un_804D585C == un_804D6DB8) {
            int x = (un_804D6DC0 + 1) & 1;
            un_804D6DC0 = x;
            lbAudioAx_80024E50(x);
        } else {
            lbAudioAx_80023F28(un_804D6DB8);
            un_804D6DC0 = 0;
            un_804D585C = un_804D6DB8;
        }
    } else if (arg0 == 0) {
        lbAudioAx_800236DC();
        un_804D585C = -1;
        un_804D6DC0 = 0;
    }
    return 0;
}

bool un_802FFC30(void)
{
    lbAudioAx_800236DC();
    lbAudioAx_800245D4(0x7F);
    lbAudioAx_800245F4(0x7F);
    lbAudioAx_80024614(0x7F);
    return true;
}

bool un_802FFC6C(bool update_scene)
{
    if (update_scene == true) {
        lbAudioAx_80023694();
        lbAudioAx_80024030(0);
        lbAudioAx_800236DC();
        lbAudioAx_800245D4(0x7F);
        lbAudioAx_800245F4(0x7F);
        lbAudioAx_80024614(0x7F);
        gm_801A42F8(MJ_TITLE);
        gm_801A4B60();
    }
    return true;
}

bool fn_802FFCC8(void)
{
    return false;
}

/// #un_802FFCD0

void un_802FFD94(int arg0, int arg1, int arg2)
{
    un_80302DF8_t* d;
    if (arg0 == 1) {
        d = un_80302DF0();
        lbAudioAx_80024030(1);
        un_80304210(d, arg1, 0, -60, 0);
        un_80302DF8(un_80302DF0(), arg2);
    }
}

int fn_802FFE0C(int arg0)
{
    switch (arg0) {
    case 0:
        lbAudioAx_80024030(0);
        un_80304334(un_80302DF0());
        break;
    case 6:
        lbAudioAx_80024030(1);
        gm_SetScenePendingMinor(4);
        gm_801A4B60();
        break;
    }
    return 0;
}

bool fn_802FFE6C(bool update_scene)
{
    bool res = update_scene;
    if (update_scene == false) {
        lbAudioAx_80024030(0);
        un_80304334(un_80302DF0());
        res = false;
    }

    return res;
}

bool un_802FFEA4(bool update_scene)
{
    if (update_scene == true) {
        lbAudioAx_80024030(1);
        gm_SetScenePendingMinor(0x4);
        gm_801A4B60();
    }

    return false;
}

/// #un_802FFEE0

/// #un_802FFF2C

bool un_803001DC(bool update_scene)
{
    if (update_scene == true) {
        lbAudioAx_80024030(1);
        gm_SetScenePendingMinor(0x1);
        gm_801A4B60();
    }

    return false;
}

int un_80300218(void)
{
    lbLang_SetSavedLanguage(un_803FA258.x0);
    return 0;
}

int un_80300248(int arg0)
{
    if (un_803FA258.x4 && arg0 == 1) {
        lbAudioAx_80024030(1);
        gmMainLib_8015FB68();
    }
    return 0;
}

int un_80300290(int arg0)
{
    if (arg0 == 1) {
        un_80302DF8_t* x = un_80302DF0();
        lbAudioAx_80024030(1);
        un_80304210(x, (int) &un_803FA658, 0, -60, 0);
        un_80302DF8(un_80302DF0(), (int) fn_802FFE6C);
    }
    return 0;
}

bool un_803002FC(bool update_scene)
{
    if (update_scene == true) {
        lbAudioAx_80024030(1);
        gm_SetScenePendingMinor(0x2);
        gm_801A4B60();
    }

    return false;
}

/// #un_80300338

/// #un_80300378

/// #un_803003C4

/// #un_80300410

/// #un_80300480

/// #un_803004B4

/// #un_803004E8

/// #un_8030051C

/// #un_80300550

/// #un_80300584

/// #un_803005B8

/// #un_803005EC

/// #un_80300620

/// #un_80300654

/// #un_80300688

/// #un_803006BC

/// #un_803006F0

/// #un_80300724

/// #un_80300758

/// #un_80300790

/// #un_803007C8

/// #un_803007FC

/// #un_80300830

/// #un_80300864

/// #un_80300898

/// #un_803008CC

/// #un_80300900

/// #un_80300934

bool un_80300968(bool update_scene)
{
    if (update_scene == true) {
        lbAudioAx_80024030(1);
        gm_801A42F8(MJ_HANYU_CSS);
        gm_801A4B60();
    }

    return false;
}

bool un_803009A4(bool update_scene)
{
    if (update_scene == true) {
        lbAudioAx_80024030(1);
        gm_801A42F8(MJ_HANYU_SSS);
        gm_801A4B60();
    }

    return false;
}

/// #un_803009E0

/// #un_80300A88

bool un_80300AB8(bool update_scene)
{
    if (update_scene == true) {
        lbAudioAx_80024030(1);
        gm_SetScenePendingMinor(0x4);
        gm_801A4B60();
    }

    return false;
}

/// #un_80300AF4

/// #un_80300B58

bool un_80300BBC(bool update_scene)
{
    if (update_scene == true) {
        un_803124BC();
        un_80311680();
        gm_801A42F8(MJ_TOY_GALLERY);
        gm_801A4B60();
    }

    return false;
}

bool un_80300BF8(bool update_scene)
{
    if (update_scene == true) {
        un_803124BC();
        Trophy_SetUnlockState(0xE6, true);
        gm_801A42F8(MJ_MENU);
        gm_801A4B60();
    }

    return false;
}

bool un_80300C3C(bool update_scene)
{
    if (update_scene == true) {
        un_803124BC();
        Trophy_SetUnlockState(0xC9, true);
        gm_801A42F8(MJ_MENU);
        gm_801A4B60();
    }

    return false;
}

/// #un_80300C80

/// #fn_80300CC8

/// #un_80300D78

/// #fn_80300DE0

/// #un_80300E74

/// #fn_80300ED0

/// #un_80300F3C

/// #un_80300F98

bool un_80300FEC(bool update_scene)
{
    if (update_scene == true) {
        lbAudioAx_80024030(1);
        gm_SetScenePendingMinor(0x4);
        gm_801A4B60();
    }

    return false;
}

/// #un_80301028

/// #un_80301074

/// #un_803010C0

/// #fn_8030110C

/// #fn_803011EC

/// #un_80301280

/// #un_803012D4

bool un_80301328(bool update_scene)
{
    if (update_scene == true) {
        lbAudioAx_80024030(1);
        gm_801BF708(0x0);
        gm_801A42F8(MJ_OPENING_MV);
        gm_801A4B60();
    }

    return false;
}

bool un_8030136C(bool update_scene)
{
    if (update_scene == true) {
        lbAudioAx_80024030(1);
        gm_801BF708(0x5);
        gm_801A42F8(MJ_OPENING_MV);
        gm_801A4B60();
    }

    return false;
}

bool un_803013B0(bool update_scene)
{
    if (update_scene == true) {
        lbAudioAx_80024030(1);
        gm_801A42F8(MJ_DEBUG_CUTSCENE);
        gm_801A4B60();
    }

    return false;
}

/// #un_803013EC

/// #un_80301420

bool un_80301454(bool update_scene)
{
    if (update_scene == true) {
        lbAudioAx_80024030(1);
        gm_801A42F8(MJ_BOOT);
        gm_801A4B60();
    }

    return false;
}

bool un_80301490(bool update_scene)
{
    if (update_scene == true) {
        lbAudioAx_80024030(1);
        gm_SetScenePendingMinor(0xD);
        gm_801A4B60();
    }

    return false;
}

bool un_803014CC(bool update_scene)
{
    if (update_scene == true) {
        lbAudioAx_80024030(1);
        gm_SetScenePendingMinor(0x7);
        gm_801A4B60();
    }

    return false;
}

bool un_80301508(bool update_scene)
{
    if (update_scene == true) {
        lbAudioAx_80024030(1);
        gm_SetScenePendingMinor(0x3);
        gm_801A4B60();
    }

    return false;
}

bool un_80301544(bool update_scene)
{
    if (update_scene == true) {
        lbAudioAx_80024030(1);
        gm_SetScenePendingMinor(0x9);
        gm_801A4B60();
    }

    return false;
}

bool un_80301580(bool update_scene)
{
    if (update_scene == true) {
        lbAudioAx_80024030(1);
        gm_SetScenePendingMinor(0xC);
        gm_801A4B60();
    }

    return false;
}

bool un_803015BC(bool update_scene)
{
    if (update_scene == true) {
        lbAudioAx_80024030(1);
        gm_801A42F8(MJ_PROGRESSIVE_SCAN);
        gm_801A4B60();
    }

    return false;
}

bool un_803015F8(bool update_scene)
{
    if (update_scene == true) {
        lbAudioAx_80024030(1);
        gm_SetScenePendingMinor(0xA);
        gm_801A4B60();
    }

    return false;
}

/// #un_80301634

/// #un_803016D8

/// #un_80301734

/// #un_8030178C

/// #un_80301800

/// #un_80301840

/// #un_803018BC

/// #un_8030191C

/// #un_80301964

/// #un_80301A64

/// #un_80301AD4

/// #un_80301B48

/// #un_80301BA8

/// #un_80301C64

/// #un_80301C80

/// #un_80301CE0

bool un_80301D40(bool update_scene)
{
    if (update_scene == true) {
        lbAudioAx_80024030(1);
        gm_801A42F8(MJ_FIXED_CAMERA_VS);
        gm_801A4B60();
    }

    return false;
}

/// #un_80301D7C

bool un_80301DCC(bool update_scene)
{
    if (update_scene == true) {
        lbAudioAx_80024030(1);
        gm_SetScenePendingMinor(0x4);
        gm_801A4B60();
    }

    return false;
}

bool un_80301E08(bool update_scene)
{
    if (update_scene == true) {
        lbAudioAx_80024030(1);
        gm_SetScenePendingMinor(0xE);
        gm_801A4B60();
    }

    return false;
}

int DevText_StrLen(char* str)
{
    if (str) {
        int length = 0;
        while (*str++) {
            length++;
        }
        return length;
    }
    return 0;
}

void DevText_NumToStr(int num, char* str)
{
    int length = 0;
    int i;
    char* strEnd;

    if (num < 0) {
        *str = '-';
        num = -num;
        str++;
    }

    strEnd = str;
    do {
        *strEnd = (num % 10) + '0';
        num = num / 10;
        strEnd++;
        length++;
    } while (num != 0);
    *strEnd = '\0';
    strEnd--;

    for (i = 0; i != length / 2; i++) {
        char temp = *str;
        *str = *strEnd;
        *strEnd = temp;
        strEnd--;
        str++;
    }
}

HSD_GObj* DevText_GetGObj(void)
{
    return devtext_gobj;
}

void DevText_InitPool(void)
{
    DevText* text = devtext_pool;
    int i;
    devtext_pool[0].prev = NULL;
    for (i = 0; i < 31; i++) {
        devtext_pool[i + 1].prev = &devtext_pool[i];
        devtext_pool[i].next = &devtext_pool[i + 1];
    }
    devtext_pool[31].next = NULL;
    devtext_drawlist = NULL;
    devtext_poolhead = devtext_pool;
}

void fn_803020F8(void) {}

void DevText_Remove(DevText** ptext)
{
    DevText* text = *ptext;
    if (text->next) {
        text->next->prev = text->prev;
    }
    text = *ptext;
    if (text->prev) {
        text->prev->next = text->next;
    } else {
        if (text->next) {
            *ptext = text->next;
        } else {
            *ptext = NULL;
        }
    }
    text->next = devtext_poolhead;
    text->prev = NULL;
    devtext_poolhead = text;
}

void DevText_SetupCObj(void)
{
    if (devtext_cobj == NULL) {
        HSD_RectS16 viewport;
        Scissor scissor;
        Vec3 eyepos = { 0, 0, 1 };
        Vec3 interest = { 0, 0, 0 };
        float roll = 0;
        float near = 0;
        float far = 2;
        float top = -20;
        float bottom = 500;
        float left = -20;
        float right = 660;

        viewport.xmin = 0;
        viewport.xmax = 640;
        viewport.ymin = 0;
        viewport.ymax = 480;

        scissor.left = 0;
        scissor.right = 640;
        scissor.top = 0;
        scissor.bottom = 480;

        devtext_cobj = HSD_CObjAlloc();
        HSD_CObjSetProjectionType(devtext_cobj, 3);
        HSD_CObjSetViewport(devtext_cobj, &viewport);
        HSD_CObjSetScissor(devtext_cobj, &scissor);
        HSD_CObjSetEyePosition(devtext_cobj, &eyepos);
        HSD_CObjSetInterest(devtext_cobj, &interest);
        HSD_CObjSetRoll(devtext_cobj, roll);
        HSD_CObjSetNear(devtext_cobj, near);
        HSD_CObjSetFar(devtext_cobj, far);
        HSD_CObjSetOrtho(devtext_cobj, top, bottom, left, right);
    }
    HSD_CObjSetCurrent(devtext_cobj);
}

void DevText_Draw(DevText* text)
{
    hsd_80391A04(text->scale_x, text->scale_y, text->line_width);
    if ((text->flags & DEVTEXT_FLAG_HIDEBACKGROUND) == 0) {
        DrawRectangle(text->x - 8, text->y - 8, text->scale_x * text->w + 8,
                      text->scale_y * text->h + 8, &text->bg_color);
        DrawRectangle(text->x - 4, text->y - 4, text->scale_x * text->w + 4,
                      text->scale_y * text->h + 4, &text->bg_color);
    }
    if ((text->flags & DEVTEXT_FLAG_HIDETEXT) == 0) {
        int row = 0;
        int y = text->y;
        while (row < text->h) {
            int col = 0;
            int x = text->x;
            while (col < text->w) {
                int index = (col + text->w * row) * 2;
                int chr = text->buf[index];
                if (chr) {
                    GXColor* color =
                        &text->text_colors[text->buf[index + 1] >> 6];
                    DrawASCII(chr, x, y, color);
                }
                x += text->scale_x;
                col++;
            }
            y += text->scale_y;
            row++;
        }
    }
    if ((text->flags & DEVTEXT_FLAG_SHOWCURSOR) == 1) {
        text->unk++;
        if (text->unk < 17) {
            if (8 < text->unk) {
                GXColor color = { 0xFF, 0xFF, 0xFF, 0xC0 };
                DrawRectangle(text->x + text->scale_x * text->cursor_x,
                              text->y + text->scale_y * text->cursor_y,
                              text->scale_x, text->scale_y, &color);
            }
        } else {
            text->unk = 0;
        }
    }
}

void DevText_DrawAll(HSD_GObj* gobj, int pass)
{
    PAD_STACK(8);

    if ((unsigned int) pass == HSD_RP_BOTTOMHALF) {
        DevText* text = devtext_drawlist;
        HSD_FogSet(NULL);
        DevText_SetupCObj();
        while (text) {
            DevText_Draw(text);
            text = text->next;
        }
    }
}

void DevText_CreateCObj(int classifier, int p_link, int gobj_priority,
                        int gx_link, u8 gx_priority)
{
    HSD_GObj* gobj = GObj_Create(classifier, p_link, gobj_priority);
    if (gobj) {
        HSD_CObj* cobj = HSD_CObjLoadDesc((HSD_CObjDesc*) &devtext_CObjDesc);
        if (cobj) {
            HSD_GObjObject_80390A70(gobj, HSD_GObj_804D784B, cobj);
            GObj_SetupGXLinkMax(gobj, HSD_GObj_803910D8, gx_priority);
            gobj->gxlink_prios = 1LL << gx_link;
        } else {
            HSD_GObjPLink_80390228(gobj);
        }
    }
}

#pragma push
#pragma dont_inline on
HSD_GObj* DevText_Setup(int classifier, int p_link, int priority, int gx_link,
                        int render_priority, u8 camera_priority)
{
    HSD_GObj* gobj;

    devtext_setup_classifier = classifier;
    devtext_setup_p_link = p_link;
    devtext_setup_priority = priority;
    devtext_setup_gx_link = gx_link;
    devtext_setup_render_priority = render_priority;
    devtext_cobj = NULL;

    DevText_CreateCObj(classifier, p_link, priority, gx_link, camera_priority);
    DevText_InitPool();
    gobj = GObj_Create(devtext_setup_classifier, devtext_setup_p_link,
                       devtext_setup_priority);
    if (gobj) {
        GObj_SetupGXLink(gobj, DevText_DrawAll, devtext_setup_gx_link,
                         devtext_setup_render_priority);
    }
    devtext_gobj = gobj;
    return devtext_gobj;
}
#pragma pop

void DevText_AddToList(DevText** list, DevText* text)
{
    if (*list) {
        DevText* next = *list;
        DevText* prev = NULL;

        while (next) {
            if (text->id >= next->id) {
                prev = next;
                next = next->next;
            } else {
                break;
            }
        }

        text->next = next;
        // next->prev = text;

        if (prev) {
            prev->next = text;
            text->prev = prev;
        } else {
            text->prev = NULL;
            *list = text;
        }
    } else {
        *list = text;
    }
}

void DevText_Show(HSD_GObj* gobj, DevText* text)
{
    DevText_AddToList(&devtext_drawlist, text);
}

/// #DevText_Create

void DevText_EraseFirstLine(DevText* text)
{
    char* start_of_line = text->buf;
    int line_length = text->w * 2;
    int line_number;

    for (line_number = 0; line_number < text->h - 1; line_number++) {
        memcpy(start_of_line, start_of_line + line_length, line_length);
        start_of_line += line_length;
    }
    memzero(start_of_line, line_length);
}

inline int DevText_Clamp(int val, int max)
{
    if (max <= val) {
        return max - 1;
    } else if (val < 0) {
        return 0;
    } else {
        return val;
    }
}

void DevText_SetCursorXY(DevText* text, int x, int y)
{
    text->cursor_x = DevText_Clamp(x, text->w);
    text->cursor_y = DevText_Clamp(y, text->h);
}

void DevText_SetCursorX(DevText* text, int x)
{
    text->cursor_x = DevText_Clamp(x, text->w);
}

void DevText_HideCursor(DevText* text)
{
    text->flags &= ~(1 << 4);
}

void DevText_80302AC0(DevText* text)
{
    text->flags |= (1 << 5);
}

void DevText_ShowBackground(DevText* text)
{
    text->flags &= ~(1 << 6);
}

void DevText_HideBackground(DevText* text)
{
    text->flags |= (1 << 6);
}

void DevText_ShowText(DevText* text)
{
    text->flags &= ~(1 << 7);
}

void DevText_HideText(DevText* text)
{
    text->flags |= (1 << 7);
}

void DevText_SetScale(DevText* text, f32 x, f32 y)
{
    text->scale_x = x;
    text->scale_y = y;
}

void DevText_SetXY(DevText* text, int x, int y)
{
    if (x < 8) {
        x = 8;
    }
    if (y < 8) {
        y = 8;
    }
    text->x = x;
    text->y = y;
}

u8 DevText_StoreColorIndex(DevText* text, u8 index)
{
    u8 old = text->current_color;
    text->current_color = index;
    return old;
}

GXColor DevText_SetTextColor(DevText* text, GXColor color)
{
    int index = text->current_color;
    GXColor old = text->text_colors[index];
    text->text_colors[index] = color;
    return old;
}

GXColor DevText_SetBGColor(DevText* text, GXColor color)
{
    GXColor old = text->bg_color;
    text->bg_color = color;
    return old;
}

void DevText_Erase(DevText* text)
{
    memzero(text->buf, 2 * text->w * text->h);
}

inline void DevText_AdvanceLine(DevText* text)
{
    text->cursor_x = 0;
    if (text->cursor_y < text->h - 1) {
        text->cursor_y++;
    } else {
        DevText_EraseFirstLine(text);
    }
}

void DevText_Print(DevText* text, char* str)
{
    if (str) {
        while (*str) {
            if (*str != '\n') {
                int index = (text->cursor_x + text->cursor_y * text->w) * 2;
                text->buf[index] = *str;
                text->buf[index + 1] = text->current_color << 6;
                if (text->cursor_x < text->w - 1) {
                    text->cursor_x++;
                } else if ((text->flags & DEVTEXT_FLAG_NOWRAP) == 0) {
                    DevText_AdvanceLine(text);
                }
            } else {
                DevText_AdvanceLine(text);
            }
            str++;
        }
    }
}

void DevText_PrintInt(DevText* text, int num)
{
    char str[16];
    DevText_NumToStr(num, str);
    DevText_Print(text, str);
}

void DevText_Printf(DevText* text, char* format, ...)
{
    char str[64];
    va_list args;
    va_start(args, format);
    vsnprintf(str, -1, format, args);
    va_end(args);
    DevText_Print(text, str);
}

UNK_T un_80302DF0(void)
{
    return un_804D6E44;
}

void un_80302DF8(un_80302DF8_t* arg0, int arg1)
{
    arg0->xC = arg1;
}

/// #un_80302E00

/// #un_80302EA4

/// #un_80302FFC

/// #un_80303444

/// #un_80303720

/// #un_803039A4

/// #un_80303AC4

/// #fn_80303EF4

/// #un_80303FD4

/// #un_80304138

void un_80304138(void)
{
    HSD_ObjAllocInit(&un_804A2688, sizeof(struct un_80304138_objalloc_t), 4);
}

/// #un_80304168

/// #un_80304210

void un_80304334(un_80304334_t* arg0)
{
    arg0->x1 |= (1 << 7);
}

/// #un_80304344

/// #un_80304470

/// #un_80304510

/// #un_803045A0

/// #un_80304690

/// #un_80304780

/// #un_80304870

/// #un_803048C0

/// #un_80304924

/// #un_80304988

/// #un_803049F4

/// #un_80304A58

/// #un_80304B0C

/// #un_80304B94
int un_80304B94(int option)
{
    int res;
    switch (option) {
    case 0:
        if (lbLang_IsSettingJP()) {
            res = 0x4;
        } else {
            res = 0x4;
        }
        break;
    case 1:
        if (lbLang_IsSettingJP()) {
            res = 0xA;
        } else {
            res = 0xA;
        }
        break;
    case 2:
        if (lbLang_IsSettingJP()) {
            res = 0x11;
        } else {
            res = 0x10;
        }
        break;
    case 3:
        if (lbLang_IsSettingJP()) {
            res = 0x17;
        } else {
            res = 0x17;
        }
        break;
    case 4:
        if (lbLang_IsSettingJP()) {
            res = 0xC;
        } else {
            res = 0xC;
        }
        break;
    case 5:
        if (lbLang_IsSettingJP()) {
            res = 0x48;
        } else {
            res = 0x48;
        }
        break;
    case 6:
        if (lbLang_IsSettingJP()) {
            res = 0x1B;
        } else {
            res = 0x1B;
        }
        break;
    case 7:
        if (lbLang_IsSettingJP()) {
            res = 0x7E;
        } else {
            res = 0x7E;
        }
        break;
    case 8:
        if (lbLang_IsSettingJP()) {
            res = 0x2;
        } else {
            res = 0x2;
        }
        break;
    }
    return res;
}

/// #un_80304CC8

/// #un_80304D30
