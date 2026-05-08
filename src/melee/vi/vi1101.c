#include "vi1101.h"

#include "cm/camera.h"
#include "vi.h"

#include "ef/efasync.h"
#include "ef/eflib.h"
#include "ft/forward.h"
#include "ft/ftdemo.h"
#include "gm/gm_1601.h"
#include "gm/gm_1A45.h"
#include "gr/grlib.h"
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
#include "vi/types.h"

#include <baselib/aobj.h>
#include <baselib/cobj.h>
#include <baselib/gobjgxlink.h>
#include <baselib/gobjobject.h>
#include <baselib/gobjproc.h>
#include <baselib/jobj.h>

typedef struct Vi1101Data {
    Vec3 spawns[3];
    char vi1101_dat[0xC];
    char visual1101_scene[0x10];
    char visual1101_cam2_scene[0x14];
} Vi1101Data;

static f32 const un_804DE0D8 = 1.0f;
static f32 const un_804DE0DC = 0.0f;
static f32 const un_804DE0E0 = 432.0f;

static Vi1101Data un_80400200 = {
    { { 0.0f, 0.0f, 0.0f },
      { 15.8512f, 67.0f, 0.0f },
      { -15.7657f, 67.0f, 0.0f } },
    "Vi1101.dat",
    "visual1101Scene",
    "visual1101Cam2Scene",
};

static SceneDesc* un_804D6FC0;
static SceneDesc* un_804D6FC4;
static HSD_Archive* un_804D6FC8;
static HSD_Archive* un_804D6FCC;
static struct {
    HSD_GObj* unk0;
    HSD_GObj* unk4;
} un_804D6FD0;

void un_8031F294(s32 arg0, s32 arg1)
{
    HSD_JObj* jobj;
    VecMtxPtr pmtx;
    char pad[16];

    Camera_80028B9C(6);
    lb_8000FCDC();
    mpColl_80041C78();
    Ground_801C0378(0x40);
    Stage_802251E8(KINOKOROUTE, 0);
    Item_80266FA8();
    Item_80266FCC();
    Stage_8022524C();
    Stage_8022532C(KINOKOROUTE, 0);
    ftDemo_ObjAllocInit();
    Player_InitAllPlayers();
    Player_80036E20(arg0, un_804D6FC8, 3);
    Player_SetPlayerCharacter(0, arg0);
    Player_SetCostumeId(0, arg1);
    Player_SetPlayerId(0, 0);
    Player_SetSlottype(0, Gm_PKind_Demo);
    Player_SetFacingDirection(0, un_804DE0D8);
    Player_80032768(0, un_80400200.spawns);
    Player_80036F34(0, 8);
    pmtx = grLib_801C9A10();
    Player_80036E20(CKIND_MARIO, un_804D6FCC, 5);
    Player_SetPlayerCharacter(1, CKIND_MARIO);
    Player_SetCostumeId(1, 0);
    Player_SetPlayerId(1, 0);
    Player_SetSlottype(1, Gm_PKind_Demo);
    Player_SetFacingDirection(1, un_804DE0DC);
    Player_80032768(1, un_80400200.spawns);
    Player_SetFlagsBit5(1, 1);
    Player_80036F34(1, 0xA);
    un_804D6FD0.unk0 = Player_GetEntity(1);
    jobj = GET_JOBJ(un_804D6FD0.unk0);
    HSD_JObjReqAnimAll(jobj, un_804DE0E0);
    HSD_JObjAnimAll(jobj);
    pmtx[1] = un_80400200.spawns[1];
    HSD_JObjReqAnimAll(jobj, un_804DE0DC);
    if (gm_80164840(7) != 0) {
        Player_80036E20(CKIND_LUIGI, un_804D6FCC, 5);
        Player_SetPlayerCharacter(2, CKIND_LUIGI);
        Player_SetCostumeId(2, 0);
        Player_SetPlayerId(2, 0);
        Player_SetSlottype(2, Gm_PKind_Demo);
        Player_SetFacingDirection(2, un_804DE0DC);
        Player_80032768(2, un_80400200.spawns);
        Player_SetFlagsBit5(2, 1);
        Player_80036F34(2, 0xA);
        un_804D6FD0.unk4 = Player_GetEntity(2);
        jobj = GET_JOBJ(un_804D6FD0.unk4);
        HSD_JObjReqAnimAll(jobj, un_804DE0E0);
        HSD_JObjAnimAll(jobj);
        pmtx[2] = un_80400200.spawns[2];
        HSD_JObjReqAnimAll(jobj, un_804DE0DC);
    }
    lbAudioAx_80026F2C(0x1C);
    lbAudioAx_8002702C(0xC, ((u64) 0x20 << 48) | lbAudioAx_80026E84(arg0));
    lbAudioAx_80027168();
    lbAudioAx_80027648();
}

void fn_8031F548(HSD_GObj* gobj)
{
    HSD_JObjAnimAll(GET_JOBJ(gobj));
}

static void fn_8031F56C(HSD_GObj* gobj, int unused)
{
    HSD_CObj* cobj;
    char pad[8];

    lbShadow_8000F38C(0);
    cobj = gobj->hsd_obj;
    if (HSD_CObjSetCurrent(cobj) != 0) {
        u8* colors = (u8*) &un_804D5B08;
        HSD_SetEraseColor(colors[0], colors[1], colors[2], colors[3]);
        cobj = gobj->hsd_obj;
        HSD_CObjEraseScreen(cobj, 1, 0, 1);
        vi_8031CA04(gobj);
        gobj->gxlink_prios = 0x281;
        HSD_GObj_80390ED0(gobj, 7);
        HSD_CObjEndCurrent();
    }
}

void fn_8031F600(HSD_GObj* gobj)
{
    HSD_CObj* cobj = GET_COBJ(gobj);

    HSD_CObjAnim(cobj);

    if (170.0f == cobj->aobj->curr_frame) {
        if (gm_80164840(7) != 0) {
            vi_8031C9B4(0xD, 0);
            lbAudioAx_800237A8(0x209, 0x7F, 0x40);
        }
    }

    if (190.0f == cobj->aobj->curr_frame) {
        vi_8031C9B4(0xD, 0);
        lbAudioAx_800237A8(0x209, 0x7F, 0x40);
    }

    if (241.0f == cobj->aobj->curr_frame) {
        if (gm_80164840(7) != 0) {
            lbAudioAx_800237A8(0x20A, 0x7F, 0x40);
        }
    }

    if (271.0f == cobj->aobj->curr_frame) {
        lbAudioAx_800237A8(0x20A, 0x7F, 0x40);
    }

    if (cobj->aobj->curr_frame == cobj->aobj->end_frame) {
        lb_800145F4();
        gm_801A4B60();
    }
}

void un_8031F714_OnEnter(void* arg)
{
    HSD_Joint* new_var2;
    SceneDesc* var_r28;
    HSD_CObj* temp_r3;
    HSD_GObj* temp_r28;
    HSD_GObj* temp_r31;
    HSD_JObj* temp_r3_2;
    HSD_GObj* temp_r26;
    u8 new_var3;
    s32 var_r31;
    u8 temp_r29;
    u8* input = arg;
    char* data = (char*) &un_80400200;
    HSD_JObj* new_var;
    lbAudioAx_800236DC();
    efLib_Init();
    temp_r29 = 0;
    efAsync_LoadSync(temp_r29);
    lbAudioAx_80023F28(0x55);
    lbAudioAx_80024E50(1);

    temp_r29 = input[0];
    un_804D6FCC = lbArchive_LoadSymbols(data + 0x24, &un_804D6FC0, data + 0x30,
                                        &un_804D6FC4, data + 0x40, NULL);
    un_804D6FC8 = lbArchive_LoadSymbols(viGetCharAnimByIndex(temp_r29), NULL);

    temp_r28 = GObj_Create(0xB, 3, 0);
    HSD_GObjObject_80390A70(temp_r28, HSD_GObj_804D784A & 0xFFFF,
                            lb_80011AC4(un_804D6FC0->lights));
    GObj_SetupGXLink(temp_r28, HSD_GObj_LObjCallback, 0, 0);

    if (gm_80164840(7) != 0) {
        var_r28 = un_804D6FC0;
    } else {
        var_r28 = un_804D6FC4;
    }

    temp_r31 = GObj_Create(0x13, 0x14, 0);
    temp_r3 = lb_80013B14((HSD_CameraDescPerspective*) var_r28->cameras->desc);
    HSD_GObjObject_80390A70(temp_r31, HSD_GObj_804D784B, temp_r3);
    GObj_SetupGXLinkMax(temp_r31, fn_8031F56C, 5);
    HSD_CObjAddAnim(temp_r3, var_r28->cameras->anims[0]);
    HSD_CObjReqAnim(temp_r3, un_804DE0DC);
    HSD_CObjAnim(temp_r3);
    HSD_GObj_SetupProc(temp_r31, fn_8031F600, 0);

    for (var_r31 = 0; un_804D6FC0->models[var_r31] != NULL; var_r31++) {
        temp_r26 = GObj_Create(0xE, 0xF, 0);
        temp_r3_2 =
            HSD_JObjLoadJoint(new_var2 = un_804D6FC0->models[var_r31]->joint);
        HSD_GObjObject_80390A70(temp_r26, new_var3 = HSD_GObj_804D7849,
                                temp_r3_2);
        GObj_SetupGXLink(temp_r26, HSD_GObj_JObjCallback, 9, 0);
        gm_8016895C(temp_r3_2, un_804D6FC0->models[var_r31], 0);
        HSD_JObjReqAnimAll(temp_r3_2, un_804DE0DC);
        new_var = temp_r3_2;
        HSD_JObjAnimAll(new_var);
        HSD_GObj_SetupProc(temp_r26, fn_8031F548, 0x17);
    }

    un_8031F294(input[0], input[1]);
    lbAudioAx_80024E50(0);
}

void un_8031F960_OnFrame(void)
{
    vi_8031CAAC();
}
