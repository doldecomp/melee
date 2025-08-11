#include "baselib/forward.h"
#include "pl/forward.h"
#include "sc/forward.h"
#include "un/forward.h"

#include "baselib/jobj.h"
#include "baselib/memory.h"
#include "baselib/sislib.h"
#include "baselib/wobj.h"
#include "cm/camera.h"
#include "gm/gm_unsplit.h"
#include "if/ifall.h"
#include "lb/lb_00B0.h"
#include "lb/lb_00F9.h"
#include "lb/lbarchive.h"
#include "lb/lbvector.h"
#include "mn/mnmain.h"
#include "mn/mnname.h"
#include "pl/player.h"
#include "sc/types.h"
#include "un/types.h"
#include "un/un_2FC9.h"

#include <printf.h>
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

// .data
// IfAll.dat::ScInfPnm_scene_models
//  0- 3 - 1P      - Red, Blue, Yellow, Green
//  4- 7 - 2P      - Red, Blue, Yellow, Green
//  8-11 - 3P      - Red, Blue, Yellow, Green
// 12-15 - 4P      - Red, Blue, Yellow, Green
// 16-19 - CP      - Red, Blue, Gray,   Green
// 20-23 - Nametag - Red, Blue, Yellow, Green
// 24-27 - Heart   - Red, Blue, Yellow, Green
// 28    - Nametag - Gray
// 29-30 - Empty   - Gray
/* 3F98B8 */ static float un_803F98B8[6][5] = {
    {
        0.0,  // 1P Red
        1.0,  // 1P Blue
        3.0,  // 1P Green
        0.0,  // 1P Red
        16.0, // CP Red
    },
    {
        4.0,  // 2P Red
        5.0,  // 2P Blue
        7.0,  // 2P Green
        5.0,  // 2P Blue
        17.0, // CP Blue
    },
    {
        8.0,  // 3P Red
        9.0,  // 3P Blue
        11.0, // 3P Green
        10.0, // 3P Blue
        18.0, // CP Gray
    },
    {
        12.0, // 4P Red
        13.0, // 4P Blue
        15.0, // 4P Green
        15.0, // 4P Green
        19.0, // CP Green
    },
    {
        16.0, // CP Red
        17.0, // CP Blue
        19.0, // CP Green
        18.0, // CP Gray
        18.0, // CP Gray
    },
    {
        24.0, // Heart Red
        25.0, // Heart Blue
        26.0, // Heart Yellow
        27.0, // Heart Green
    },
};
/* 3F992C */ static HSD_WObjDesc nametag_eyepos = { NULL,
                                                    { 0.0f, 0.0f, 300.0f },
                                                    NULL };
/* 3F9940 */ static HSD_WObjDesc nametag_interest = { NULL,
                                                      { 0.0f, 0.0f, 0.0f },
                                                      NULL };
/* 3F9954 */ static HSD_CameraDescFrustum nametag_CObjDesc = {
    NULL,
    0,
    3,
    0,
    640,
    0,
    480,
    0,
    640,
    0,
    480,
    &nametag_eyepos,
    &nametag_interest,
    0.0f,
    NULL,
    0.1f,
    32768.0f,
    0.0f,
    -480.0f,
    0.0f,
    640.0f
};

// .bss
/* 4A1ED0 */ static StaticModelDesc un_804A1ED0;
/* 4A1EE0 */ static HSD_GObj* un_804A1EE0[PL_SLOT_MAX];
/* 4A1EF8 */ static int un_804A1EF8[PL_SLOT_MAX];

// .sbss
/* 4D6D68 */ static HSD_GObj* un_804D6D68;
/* 4D6D6C */ static u8 un_804D6D6C;
/* 4D6D70 */ static u8 un_804D6D70[PL_SLOT_MAX];
/* 4D6D78 */ static HSD_Text* un_804D6D78;
/* 4D6D7C */ static int un_804D6D7C;

// NameTag_Create and un_802FD28C will try to inline this otherwise
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
            if (Player_GetPlayerSlotType(i) != Gm_PKind_Human ||
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

// un_802FD4C8 will try to inline this otherwise
#pragma push
#pragma dont_inline on
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
#pragma pop

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
    if (Player_GetPlayerSlotType(*slot) != Gm_PKind_NA &&
        Player_GetPlayerState(*slot) && Player_GetStocks(*slot) &&
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
        HSD_SisLib_803A746C(un_804D6D78, un_804A1EF8[*slot], vec2.x,
                            vec2.y - 56.0f);
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
        unsigned char* user_data = HSD_MemAlloc(1);
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

void un_802FD4C8(void)
{
    HSD_GObj* gobj;
    int i;
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
    // "Break the targets!" "Race to the finish!" etc strings
    HSD_SisLib_803A62A0(2, "SdIntro.dat", "SIS_IntroData");
    un_804D6D78 = HSD_SisLib_803A6754(2, un_804D6D7C);
    un_804D6D78->x8 = -10.0;
    un_804D6D78->x4A = 1;
    un_802FCBA0();
    for (i = 0; i < PL_SLOT_MAX; i++) {
        NameTag_Create(i);
    }
}
