#include "vi/vi0102.h"

#include <placeholder.h>

#include "cm/camera.h"
#include "ef/efasync.h"
#include "ef/eflib.h"
#include "ft/ftdemo.h"
#include "gm/gm_unsplit.h"
#include "gr/ground.h"
#include "gr/stage.h"
#include "it/item.h"
#include "lb/lb_00F9.h"
#include "lb/lbarchive.h"
#include "lb/lbaudio_ax.h"
#include "lb/lbshadow.h"
#include "mp/mpcoll.h"
#include "pl/player.h"
#include "sc/types.h"
#include "vi/vi.h"

#include <baselib/forward.h>

#include <dolphin/gx.h>
#include <baselib/aobj.h>
#include <baselib/cobj.h>
#include <baselib/displayfunc.h>
#include <baselib/fog.h>
#include <baselib/gobjgxlink.h>
#include <baselib/gobjobject.h>
#include <baselib/gobjproc.h>
#include <baselib/wobj.h>

extern SceneDesc* un_804D6F30;
extern GXColor erase_colors_vi0102;
extern HSD_Archive* un_804D6F38;
static un_804D6F60_t un_804D6F60;
static f32 un_804DE048;
static Vec3 initial_pos = { 0, 0, 0 };

void vi0102_8031CB00(int mario_costume, int luigi_costume)
{
    Camera_80028B9C(6);
    lb_8000FCDC();
    mpColl_80041C78();
    Ground_801C0378(0x40);
    Stage_802251E8(4, 0);
    Item_80266FA8();
    Item_80266FCC();
    Stage_8022524C();
    Stage_8022532C(4, 0);

    ftDemo_ObjAllocInit();
    Player_InitAllPlayers();

    // Setup Mario
    Player_80036E20(CKIND_MARIO, un_804D6F38, 4);
    Player_SetPlayerCharacter(0, CKIND_MARIO);
    Player_SetCostumeId(0, mario_costume);
    Player_SetPlayerId(0, 0);
    Player_SetSlottype(0, Gm_PKind_Demo);
    Player_SetFacingDirection(0, 1.0f);
    Player_80032768(0, &initial_pos);
    Player_80036F34(0, 9);

    // Setup Luigi
    Player_80036E20(CKIND_LUIGI, un_804D6F38, 4);
    Player_SetPlayerCharacter(1, CKIND_LUIGI);
    Player_SetCostumeId(1, luigi_costume);
    Player_SetPlayerId(1, 0);
    Player_SetSlottype(1, Gm_PKind_Demo);
    Player_SetFacingDirection(1, 1.0f);
    Player_80032768(1, &initial_pos);
    Player_80036F34(1, 9);

    lbAudioAx_80026F2C(0x18);
    lbAudioAx_8002702C(8, 0x400000000);
    lbAudioAx_80027168();
    lbAudioAx_80027648();
}

void vi0102_JObjCallback(HSD_GObj* gobj)
{
    HSD_JObjAnimAll(GET_JOBJ(gobj));
}

void vi0102_CameraCallback(HSD_GObj* gobj, int unused)
{
    HSD_CObj* cobj;
    PAD_STACK(8);
    lbShadow_8000F38C(0);
    cobj = gobj->hsd_obj;
    if (HSD_CObjSetCurrent(cobj)) {
        HSD_SetEraseColor(erase_colors_vi0102.r, erase_colors_vi0102.g,
                          erase_colors_vi0102.b, erase_colors_vi0102.a);
        cobj = gobj->hsd_obj;
        HSD_CObjEraseScreen(cobj, 1, 0, 1);
        vi_8031CA04(gobj);
        gobj->gxlink_prios = 0x881;
        HSD_GObj_80390ED0(gobj, 7);
        HSD_CObjEndCurrent();
    }
}

static void vi0102_RunFrame(HSD_GObj* gobj)
{
    HSD_CObj* cobj;

    cobj = gobj->hsd_obj;
    HSD_CObjAnim(cobj);

    if (un_804DE048 == cobj->eyepos->aobj->curr_frame) {
        vi_8031C9B4(0x21, 0);
    }
    if (cobj->eyepos->aobj->curr_frame == cobj->eyepos->aobj->end_frame) {
        lb_800145F4();
        gm_801A4B60();
    }
}

void vi0102_Initialize_OnEnter(un_804D6F60_t* unk)
{
    HSD_CObj* cobj;
    HSD_GObj* cam_gobj;

    HSD_JObj* jobj;
    HSD_GObj* joint_gobj;

    HSD_Fog* fog;
    HSD_GObj* fog_gobj;

    HSD_LObj* lobj;
    HSD_GObj* light_gobj;

    int i;

    lbAudioAx_800236DC();
    efLib_8005B4B8();
    efAsync_8006737C(0);
    lbAudioAx_80023F28(0x56);
    lbAudioAx_80024E50(1);
    un_804D6F38 = lbArchive_LoadSymbols("Vi0102.dat", &un_804D6F30,
                                        "visual0102Scene", 0);

    cam_gobj = GObj_Create(0x13, 0x14, 0);
    cobj =
        lb_80013B14((HSD_CameraDescPerspective*) un_804D6F30->cameras[0].desc);
    HSD_GObjObject_80390A70(cam_gobj, HSD_GObj_804D784B, cobj);
    GObj_SetupGXLinkMax(cam_gobj, vi0102_CameraCallback, 0x8);
    HSD_CObjAddAnim(cobj, un_804D6F30->cameras[0].anims[0]);
    HSD_CObjReqAnim(cobj, 0.0f);
    HSD_CObjAnim(cobj);
    HSD_GObjProc_8038FD54(cam_gobj, vi0102_RunFrame, 0);

    for (i = 0; un_804D6F30->models[i] != NULL; i++) {
        joint_gobj = GObj_Create(0xE, 0xF, 0);
        jobj = HSD_JObjLoadJoint(un_804D6F30->models[i]->joint);
        HSD_GObjObject_80390A70(joint_gobj, HSD_GObj_804D7849, jobj);
        GObj_SetupGXLink(joint_gobj, HSD_GObj_JObjCallback, 0xB, 0);
        gm_8016895C(jobj, un_804D6F30->models[i], 0);
        HSD_JObjReqAnimAll(jobj, 0.0f);
        HSD_JObjAnimAll(jobj);
        HSD_GObjProc_8038FD54(joint_gobj, vi0102_JObjCallback, 0x17);
    }

    vi0102_8031CB00(unk->unk_1, unk->unk_3);

    fog_gobj = GObj_Create(0xA, 0x3, 0);
    fog = HSD_FogLoadDesc(un_804D6F30->fogs[0].desc);
    HSD_GObjObject_80390A70(fog_gobj, HSD_GObj_804D7848, fog);
    GObj_SetupGXLink(fog_gobj, HSD_GObj_FogCallback, 0, 0);
    erase_colors_vi0102 = fog->color;

    light_gobj = GObj_Create(0xB, 0x3, 0);
    lobj = lb_80011AC4(un_804D6F30->lights);
    HSD_GObjObject_80390A70(light_gobj, HSD_GObj_804D784A, lobj);
    GObj_SetupGXLink(light_gobj, HSD_GObj_LObjCallback, 0, 0);

    lbAudioAx_80024E50(0);
}

void vi0102_8031D000_OnFrame(void)
{
    vi_8031CAAC();
}

void vi0102_8031D020(int arg0, int arg1)
{
    un_804D6F60.unk_0 = arg0;
    un_804D6F60.unk_1 = arg1;
}
