#include "gm_186E.h"

#include "gm_unsplit.h"

#include "cm/camera.h"
#include "ef/efasync.h"
#include "ef/eflib.h"
#include "ft/ftdemo.h"
#include "gm/gm_1601.h"
#include "gm/gm_1A45.h"
#include "gr/ground.h"
#include "gr/stage.h"
#include "it/item.h"
#include "lb/lb_00F9.h"
#include "lb/lbarchive.h"
#include "lb/lbaudio_ax.h"
#include "lb/lblanguage.h"
#include "lb/lbspdisplay.h"
#include "mp/mpcoll.h"
#include "pl/player.h"
#include "sc/types.h"

#include <baselib/aobj.h>
#include <baselib/cobj.h>
#include <baselib/dobj.h>
#include <baselib/fog.h>
#include <baselib/gobjgxlink.h>
#include <baselib/gobjobject.h>
#include <baselib/gobjproc.h>
#include <baselib/mobj.h>
#include <baselib/tobj.h>
#include <baselib/util.h>
#include <baselib/wobj.h>
static HSD_Archive* lbl_804D6610;
static SceneDesc* lbl_804D6614;

static struct enterdata {
    int x0, x4;
} lbl_804D6618;

typedef struct gm_804736B0_t {
    int x0, x4;
    HSD_JObj* x8;
    HSD_JObj* xC;
} gm_804736B0_t;

gm_804736B0_t lbl_804736B0;
void fn_80186EFC(HSD_GObj* gobj)
{
    HSD_JObj* jobj = GET_JOBJ(gobj);
    gm_804736B0_t* state = &lbl_804736B0;
    int* counter;
    PAD_STACK(8);
    HSD_JObjReqAnimAll(state->xC, 0.0f);
    HSD_JObjAnimAll(jobj);
    counter = &state->x4;
    if (*counter < 0x8C) {
        (*counter)++;
    } else {
        state->x0 = 1;
    }
}

typedef struct gm_80186F6C_Entry {
    /* 0x00 */ f32 x0;
    /* 0x04 */ f32 x4;
    /* 0x08 */ f32 x8;
    /* 0x0C */ f32 xC;
    /* 0x10 */ f32 x10;
    /* 0x14 */ f32 x14;
} gm_80186F6C_Entry;

static gm_80186F6C_Entry lbl_803D9498[] = {
    { 0.0f, -4.5f, 0.0f, 1.0f, 1.0f, 1.0f },
    { 0.0f, 1.5f, 0.0f, 0.6f, 0.6f, 0.6f },
    { 0.0f, -5.3f, 0.0f, 1.3f, 1.3f, 1.3f },
    { 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f },
    { 0.0f, 5.5f, 0.0f, 0.75f, 0.75f, 0.75f },
    { -1.1f, -2.0f, 0.0f, 0.5f, 0.5f, 0.5f },
    { -1.0f, -3.5f, 0.0f, 1.3f, 1.3f, 1.3f },
    { -1.0f, -0.5f, 0.0f, 1.35f, 1.35f, 1.35f },
    { -1.0f, -2.0f, 0.0f, 1.4f, 1.4f, 1.4f },
    { 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f },
    { 0.0f, -6.0f, 0.0f, 1.0f, 1.0f, 1.0f },
    { -1.0f, -0.5f, 0.0f, 1.1f, 1.1f, 1.1f },
    { -2.0f, -6.5f, 0.0f, 1.3f, 1.3f, 1.3f },
    { -0.5f, 2.5f, 0.0f, 1.0f, 1.0f, 1.0f },
    { -0.8f, 5.0f, 0.0f, 0.7f, 0.7f, 0.7f },
    { -1.0f, 4.0f, 0.0f, 0.8f, 0.8f, 0.8f },
    { 0.0f, -5.0f, 0.0f, 1.0f, 1.0f, 1.0f },
    { 0.0f, 2.0f, 0.0f, 0.9f, 0.9f, 0.9f },
    { -1.0f, -12.5f, 0.0f, 1.8f, 1.8f, 1.8f },
    { -3.5f, 0.0f, 0.0f, 1.8f, 1.8f, 1.8f },
    { 0.0f, -1.0f, 0.0f, 1.0f, 1.0f, 1.0f },
    { 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f },
    { 0.0f, -2.5f, 0.0f, 1.1f, 1.1f, 1.1f },
    { 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f },
    { 0.0f, 5.5f, 0.0f, 0.4f, 0.4f, 0.4f },
    { 1.0f, -11.0f, 0.0f, 1.3f, 1.3f, 1.3f },
    { 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f },
    { -1.1f, 2.5f, 0.0f, 0.4f, 0.4f, 0.4f },
};

void fn_80186F6C(HSD_GObj* arg0)
{
    Vec3 pos;
    HSD_JObj* jobj = arg0->hsd_obj;
    HSD_JObj* child = lbl_804736B0.x8;
    gm_80186F6C_Entry* entry = lbl_803D9498;
    PAD_STACK(4);

    HSD_JObjGetTranslation(child, &pos);

    pos.x -= 7.0f;
    pos.x += entry[lbl_804D6618.x0].x0;
    pos.y += entry[lbl_804D6618.x0].x4;
    pos.z += entry[lbl_804D6618.x0].x8;

    HSD_JObjSetTranslate(jobj, &pos);

    HSD_JObjSetScaleX(jobj, entry[lbl_804D6618.x0].xC);
    HSD_JObjSetScaleY(jobj, entry[lbl_804D6618.x0].x10);
    HSD_JObjSetScaleZ(jobj, entry[lbl_804D6618.x0].x14);

    {
        HSD_GObj* entity2 = Player_GetEntityAtIndex(0, 1);
        if (entity2 != NULL) {
            HSD_JObj* jobj2 = entity2->hsd_obj;

            HSD_JObjGetTranslation(jobj, &pos);
            pos.x += 3.0f;
            pos.z -= 5.0f;
            pos.y += 4.0f;
            HSD_JObjSetTranslate(jobj2, &pos);

            HSD_JObjGetScale(jobj, &pos);
            HSD_JObjSetScale(jobj2, &pos);
        }
    }
}

#ifdef MUST_MATCH
#pragma push
#pragma dont_inline on
#endif
HSD_GObjProc* fn_801873F0(void)
{
    ftDemo_ObjAllocInit();
    Player_InitAllPlayers();
    Player_80036E20(lbl_804D6618.x0, lbl_804D6610, 1);
    Player_SetPlayerCharacter(0, lbl_804D6618.x0);
    Player_SetCostumeId(0, lbl_804D6618.x4);
    Player_SetPlayerId(0, 0);
    Player_SetSlottype(0, Gm_PKind_Demo);
    Player_SetFacingDirection(0, 0.0f);
    Player_SetModelScale(0, 1.0f);
    Player_80036F34(0, 6);
    return HSD_GObj_SetupProc(Player_GetEntity(0), fn_80186F6C, 0x16U);
}
#ifdef MUST_MATCH
#pragma pop
#endif

void fn_80187494(HSD_GObj* gobj, int arg1)
{
    int temp_ret = HSD_CObjSetCurrent(gobj->hsd_obj);
    PAD_STACK(4);
    if (temp_ret != 0) {
        Camera_800313E0(gobj, 1);
        gobj->gxlink_prios = 0x801;
        HSD_GObj_80390ED0(gobj, 7);
        HSD_CObjEndCurrent();
    }
}

void fn_801874FC(void)
{
    HSD_JObj* sp8;
    HSD_GObj* gobj;
    HSD_JObj* jobj;

    gobj = GObj_Create(0xE, 0xF, 0);
    jobj = HSD_JObjLoadJoint(lbl_804D6614->models[0]->joint);
    HSD_GObjObject_80390A70(gobj, HSD_GObj_JObjKind, jobj);
    GObj_SetupGXLink(gobj, HSD_GObj_JObjCallback, 0xB, 0);
    HSD_GObj_SetupProc(gobj, fn_80186EFC, 0);
    gm_8016895C(jobj, lbl_804D6614->models[0], 0);
    HSD_JObjReqAnimAll(jobj, 0.0f);
    HSD_JObjAnimAll(jobj);
    lb_80011E24(jobj, &sp8, 0x3A, -1);
    HSD_JObjSetTranslateZ(sp8, 10000.0F);
    lb_80011E24(jobj, &sp8, 0x3B, -1);
    HSD_JObjSetTranslateZ(sp8, 10000.0F);
    lb_80011E24(jobj, &lbl_804736B0.x8, 5, -1);
    lb_80011E24(jobj, &lbl_804736B0.xC, 6, -1);
}

/// #fn_801874FC

#ifdef MUST_MATCH
#pragma push
#pragma dont_inline on
#endif
void fn_80187714(void)
{
    Camera_80028B9C(6);
    lb_8000FCDC();
    mpColl_80041C78();
    Ground_801C0378(64);
    Stage_802251E8(St_Kind_Dummy, NULL);
    Stage_8022524C();
    Item_80266FA8();
    Item_80266FCC();
    efLib_Init();
    efAsync_LoadSync(0);
}
#ifdef MUST_MATCH
#pragma pop
#endif

void gm_Scene_IntroAllstar_OnFrame(void)
{
    if (lbl_804736B0.x0 != 0) {
        lbArchive_80016EFC(lbl_804D6610);
        lbAudioAx_800236DC();
        gm_801A4B60();
    }
}

#ifdef MUST_MATCH
#pragma push
#pragma dont_inline on
#endif
void gm_Scene_IntroAllstar_OnEnter(void* arg0_)
{
    struct enterdata* arg0 = arg0_;
    HSD_GObj* temp_r30;
    HSD_GObj* temp_r30_2;
    HSD_GObj* temp_r30_3;
    HSD_LObj* lobj;
    HSD_CObj* cobj;
    HSD_Fog* fog;
    PAD_STACK(8);

    lbl_804736B0.x0 = 0;
    lbl_804736B0.x4 = 0;

    lbl_804D6618 = *arg0;
    fn_80187714();
    lbl_804D6610 = lbArchive_80016DBC("IrAls", &lbl_804D6614,
                                      "ScItrAllstar_scene_data", 0);

    temp_r30 = GObj_Create(0x13, 0x14, 0);
    cobj = HSD_CObjLoadDesc(lbl_804D6614->cameras[0].desc);
    HSD_GObjObject_80390A70(temp_r30, HSD_GObj_CameraKind, cobj);
    GObj_SetupGXLinkMax(temp_r30, fn_80187494, 8);
    temp_r30->gxlink_prios = 0x801;

    temp_r30_2 = GObj_Create(0xB, 3, 0);
    lobj = lb_80011AC4(lbl_804D6614->lights);
    HSD_GObjObject_80390A70(temp_r30_2, HSD_GObj_LightKind, lobj);
    GObj_SetupGXLink(temp_r30_2, HSD_GObj_LObjCallback, 0, 0);
    fn_801874FC();

    temp_r30_3 = GObj_Create(0xE, 0xF, 0);
    fog = HSD_FogLoadDesc(lbl_804D6614->fogs[0].desc);
    HSD_GObjObject_80390A70(temp_r30_3, HSD_GObj_FogKind, fog);
    GObj_SetupGXLink(temp_r30_3, HSD_GObj_FogCallback, 0xB, 0);
    fn_801873F0();
    lbAudioAx_80023F28(0x2D);
}
#ifdef MUST_MATCH
#pragma pop
#endif
