#include "vi/vi1201v2.h"

#include "vi.h"

#include "baselib/forward.h"

#include "cm/camera.h"
#include "ef/efasync.h"
#include "ef/eflib.h"
#include "ft/ftdemo.h"
#include "gm/gm_1601.h"
#include "gm/gm_unsplit.h"
#include "gr/ground.h"
#include "gr/stage.h"
#include "it/item.h"
#include "lb/lb_00B0.h"
#include "lb/lbarchive.h"
#include "lb/lbaudio_ax.h"
#include "lb/lbshadow.h"
#include "lb/lbspdisplay.h"
#include "mn/mnmain.h"
#include "mp/mpcoll.h"
#include "pl/player.h"
#include "sc/types.h"
#include "ty/toy.h"
#include "ty/tylist.h"

#include "vi/forward.h"

#include <baselib/aobj.h>
#include <baselib/cobj.h>
#include <baselib/fog.h>
#include <baselib/gobj.h>
#include <baselib/gobjgxlink.h>
#include <baselib/gobjobject.h>
#include <baselib/gobjplink.h>
#include <baselib/gobjproc.h>
#include <baselib/jobj.h>

typedef struct un_80400304_t {
    Vec3 player_spawn;
    char use_quaternion_assert[0x28];
    char vi1201v2_dat[0x10];
    char visual1201v2_scene[0x14];
    char tykoopa_dat[0x0C];
    char toykoopa_model_topn_joint[0x1C];
    char gmrgstnd_dat[0x10];
    char stand_scene[0x0C];
} un_80400304_t;

/// @todo .sdata2 order hack
static void order_sdata2(void)
{
    (void) 0.55f;
    (void) 1.0f;
}

Vec3 un_804002F8 = { 0.0f, 0.0f, 0.0f };
un_80400304_t un_80400304 = {
    { 0.0f, 0.0f, 0.0f }, "!(jobj->flags & JOBJ_USE_QUATERNION)",
    "Vi1201v2.dat",       "visual1201v2Scene",
    "TyKoopa.dat",        "ToyKoopaModel_TopN_joint",
    "GmRgStnd.dat",       "standScene",
};

static SceneDesc* un_804D7010;
static SceneDesc* un_804D7014;
static HSD_Archive* un_804D7018;
static HSD_Archive* un_804D701C;
static HSD_Joint* un_804D7020;
static HSD_JObj* un_804D7024;
GXColor un_804D7028;
static s32 un_804D702C;
HSD_GObj* un_804D7030;
HSD_GObj* un_804D7034;
un_804D7004_t un_804D7038;

void un_803204B0(int arg0, int arg1)
{
    M2C_FIELD(&un_804D7038, u8*, 0) = arg0;
    M2C_FIELD(&un_804D7038, u8*, 1) = arg1;
}

void un_803204C0(HSD_GObj* gobj)
{
    HSD_JObjAnimAll(GET_JOBJ(gobj));
}

void un_803204E4(HSD_GObj* gobj)
{
    HSD_JObjAnimAll(GET_JOBJ(gobj));
}

void un_80320508(CharacterKind char_kind, int costume)
{
    char pad[16];

    Camera_80028B9C(6);
    lb_8000FCDC();
    mpColl_80041C78();
    Ground_801C0378(0x40);
    Stage_802251E8(0x20, 0);
    Item_80266FA8();
    Item_80266FCC();
    Stage_8022524C();
    Stage_8022532C(0x20, 0x1A);
    ftDemo_ObjAllocInit();
    Player_InitAllPlayers();
    Player_80036E20(char_kind, un_804D7018, 3);
    Player_SetPlayerCharacter(0, char_kind);
    Player_SetCostumeId(0, costume);
    Player_SetPlayerId(0, 0);
    Player_SetSlottype(0, 2);
    Player_SetFacingDirection(0, -1.0f);
    Player_80032768(0, &un_804002F8);
    Player_80036F34(0, 8);
    Player_SetPlayerAndEntityFacingDirection(0, 0.0f);
}

void un_803205F4(void)
{
    HSD_GObj* gobj;
    HSD_JObj* jobj;
    char pad[16];

    gobj = GObj_Create(0xE, 0xF, 0);
    jobj = HSD_JObjLoadJoint(un_804D7010->models[1]->joint);
    HSD_GObjObject_80390A70(gobj, HSD_GObj_804D7849, jobj);
    GObj_SetupGXLink(gobj, HSD_GObj_JObjCallback, 0xB, 0);
    gm_8016895C(jobj, un_804D7010->models[1], 0);
    HSD_JObjReqAnimAll(jobj, 251.0f);
    HSD_GObj_SetupProc(gobj, mn_8022EAE0, 0);

    Player_80036E20(0x1D, un_804D701C, 8);
    Player_SetPlayerCharacter(1, 0x1D);
    Player_SetCostumeId(1, 0);
    Player_SetPlayerId(1, 0);
    Player_SetSlottype(1, 2);
    Player_SetFacingDirection(1, -1.0f);
    Player_80032768(1, &un_80400304.player_spawn);
    Player_80036F34(1, 0xF);
    Player_SetScale(1, 1.0f / Player_80032BB0(1));

    lbAudioAx_80026F2C(0x18);
    lbAudioAx_8002702C(8, 0x0020000000000000ULL);
    lbAudioAx_80027168();
    lbAudioAx_80027648();
}

void un_8032074C(HSD_GObj* gobj)
{
    HSD_JObj* jobj = GET_JOBJ(gobj);
    char pad[24];
    HSD_JObjAnimAll(jobj);
    if (mn_8022F298(jobj) == 251.0F) {
        if (un_804D7030 != NULL) {
            HSD_GObjPLink_80390228(un_804D7030);
            un_804D7030 = NULL;
        }
        if (un_804D7034 != NULL) {
            HSD_GObjPLink_80390228(un_804D7034);
            un_804D7034 = NULL;
        }
        un_803205F4();
    }
}

inline HSD_GObj* GET_EVENTDATA(void)
{
    return GObj_Create(0xE, 0xF, 0);
}

void un_803207C4(void)
{
    HSD_GObj* new_var;
    HSD_JObj* jobj;
    HSD_GObj* gobj;
    s32 i = 0;

    while (un_804D7010->models[i] != NULL) {
        if (i != 1) {
            gobj = GET_EVENTDATA();
            jobj = HSD_JObjLoadJoint(un_804D7010->models[i]->joint);
            new_var = gobj;
            HSD_GObjObject_80390A70(new_var, HSD_GObj_804D7849, jobj);
            GObj_SetupGXLink(new_var, HSD_GObj_JObjCallback, 0xB, 0);
            gm_8016895C(jobj, un_804D7010->models[i], 0);
            HSD_JObjReqAnimAll(jobj, 0.0f);
            HSD_JObjAnimAll(jobj);
            if (i == 0) {
                HSD_GObj_SetupProc(new_var, un_8032074C, 0);
                lb_80011E24(jobj, &un_804D7024, 2, -1);
            } else {
                HSD_GObj_SetupProc(new_var, mn_8022EAE0, 0);
            }
        }
        i++;
    }
}

void un_803208F0(HSD_GObj* gobj)
{
    GXColor* colors;
    char pad[8];
    lbShadow_8000F38C(0);
    if (HSD_CObjSetCurrent(GET_COBJ(gobj)) != 0) {
        colors = &un_804D7028;
        HSD_SetEraseColor(colors->r, colors->g, colors->b, colors->a);
        HSD_CObjEraseScreen(GET_COBJ(gobj), 1, 0, 1);
        vi_8031CA04(gobj);
        gobj->gxlink_prios = 0x881;
        HSD_GObj_80390ED0(gobj, 7);
        HSD_CObjEndCurrent();
    }
}

void un_80320984(HSD_GObj* gobj)
{
    HSD_CObj* cobj = GET_COBJ(gobj);
    HSD_CObjAnim(cobj);
    if (cobj->aobj->curr_frame == 130.0F || cobj->aobj->curr_frame == 190.0F) {
        vi_8031C9B4(0xD, 0);
    }
    if (cobj->aobj->curr_frame == 251.0F) {
        vi_8031C9B4(1, 0xDB);
    }
    if (cobj->aobj->curr_frame == cobj->aobj->end_frame) {
        lb_800145F4();
        gm_801A4B60();
    }
}

void fn_80320A1C(HSD_GObj* gobj)
{
    HSD_FogInterpretAnim(gobj->hsd_obj);
}

void un_80320A40_OnEnter(void* arg)
{
    u8* input = arg;
    u8 char_index;
    HSD_CObj* cobj;
    HSD_GObj* gobj;
    HSD_Fog* fog;
    HSD_JObj* child;
    HSD_JObj* jobj;
    HSD_LObj* lobj;
    f32 scale;
    PAD_STACK(16);

    efLib_Init();
    efAsync_LoadSync(0);
    lbAudioAx_80023F28(0x5C);
    lbAudioAx_80024E50(1);

    char_index = input[0];

    un_804D701C = lbArchive_LoadSymbols(un_80400304.vi1201v2_dat, &un_804D7010,
                                        un_80400304.visual1201v2_scene, NULL);
    {
        char* toykoopa_joint = un_80400304.toykoopa_model_topn_joint;
        char* tykoopa_dat = un_80400304.tykoopa_dat;
        lbArchive_LoadSymbols(tykoopa_dat, &un_804D7020, toykoopa_joint, NULL);
    }
    lbArchive_LoadSymbols(un_80400304.gmrgstnd_dat, &un_804D7014,
                          un_80400304.stand_scene, NULL);
    Toy_803124BC();
    un_804D7018 =
        lbArchive_LoadSymbols(viGetCharAnimByIndex(char_index), NULL);

    gobj = GObj_Create(0x13, 0x14, 0);
    cobj =
        lb_80013B14((HSD_CameraDescPerspective*) un_804D7010->cameras->desc);
    HSD_GObjObject_80390A70(gobj, HSD_GObj_804D784B, cobj);
    GObj_SetupGXLinkMax(gobj, (void (*)(HSD_GObj*, int))(Event) un_803208F0,
                        8);
    HSD_CObjAddAnim(cobj, un_804D7010->cameras->anims[0]);
    HSD_CObjReqAnim(cobj, 0.0f);
    HSD_CObjAnim(cobj);
    HSD_GObj_SetupProc(gobj, un_80320984, 0);

    un_803207C4();
    un_80320508(input[0], input[1]);

    gobj = GObj_Create(0xE, 0xF, 0);
    un_804D7030 = gobj;
    jobj = HSD_JObjLoadJoint(un_804D7020);
    HSD_GObjObject_80390A70(gobj, HSD_GObj_804D7849, jobj);
    GObj_SetupGXLink(gobj, HSD_GObj_JObjCallback, 0xB, 0);
    HSD_JObjSetScaleX(jobj, 0.55f);
    HSD_JObjSetScaleY(jobj, 0.55f);
    HSD_JObjSetScaleZ(jobj, 0.55f);
    lb_8000C1C0(jobj, un_804D7024);
    lb_8000C290(jobj, un_804D7024);
    HSD_GObj_SetupProc(gobj, un_803204E4, 0x17);

    gobj = GObj_Create(0xE, 0xF, 0);
    un_804D7034 = gobj;
    jobj = HSD_JObjLoadJoint(un_804D7014->models[0]->joint);
    HSD_GObjObject_80390A70(gobj, HSD_GObj_804D7849, jobj);
    GObj_SetupGXLink(gobj, HSD_GObj_JObjCallback, 0xB, 0);
    HSD_GObj_SetupProc(gobj, un_803204C0, 0x17);

    if (jobj == NULL) {
        child = NULL;
    } else {
        child = jobj->child;
    }

    HSD_JObjSetTranslateXWithMtxDirty(child, -Toy_803060BC(0x1E, 0));
    HSD_JObjSetTranslateYWithMtxDirty(child, -Toy_803060BC(0x1E, 1));
    HSD_JObjSetTranslateZWithMtxDirty(child, -Toy_803060BC(0x1E, 2));

    scale = -Toy_803060BC(0x1E, 5);
    HSD_JObjSetRotationYWithMtxDirty(child, scale);

    scale = 0.55f * (Toy_803060BC(0x1E, 4) * (1.0f / Toy_803060BC(0x1E, 3)));

    HSD_JObjSetScaleXWithMtxDirty(child, scale);
    HSD_JObjSetScaleYWithMtxDirty(child, scale);
    HSD_JObjSetScaleZWithMtxDirty(child, scale);

    lb_8000C1C0(jobj, un_804D7024);
    lb_8000C290(jobj, un_804D7024);

    gobj = GObj_Create(0xB, 3, 0);
    fog = HSD_FogLoadDesc(un_804D7010->fogs->desc);
    HSD_GObjObject_80390A70(gobj, HSD_GObj_804D7848, fog);
    GObj_SetupGXLink(gobj, HSD_GObj_FogCallback, 0, 0);
    HSD_Fog_8037DE7C(fog, un_804D7010->fogs->anims[0]->aobjdesc);
    HSD_FogReqAnim(fog, 0.0f);
    HSD_FogInterpretAnim(fog);
    HSD_GObj_SetupProc(gobj, fn_80320A1C, 0x17);
    un_804D7028 = fog->color;
    un_804D702C = 0;

    gobj = GObj_Create(0xB, 3, 0);
    lobj = lb_80011AC4(un_804D7010->lights);
    HSD_GObjObject_80390A70(gobj, HSD_GObj_804D784A, lobj);
    GObj_SetupGXLink(gobj, HSD_GObj_LObjCallback, 0, 0);

    lbAudioAx_80024E50(0);
}

void un_803210EC_OnFrame(void)
{
    vi_8031CAAC();
}
