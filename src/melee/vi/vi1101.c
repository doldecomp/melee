#include "vi1101.h"

#include "vi.h"

#include "cm/camera.h"
#include "ef/efasync.h"
#include "ef/eflib.h"
#include "ft/ftdemo.h"
#include "gm/gm_1601.h"
#include "gm/gm_1A45.h"
#include "gr/grlib.h"
#include "gr/ground.h"
#include "gr/stage.h"
#include "it/item.h"
#include "lb/lb_00F9.h"
#include "lb/lbaudio_ax.h"
#include "lb/lbshadow.h"
#include "mp/mpcoll.h"
#include "pl/player.h"
#include "sc/types.h"
#include "vi/types.h"

#include <baselib/aobj.h>
#include <baselib/cobj.h>
#include <baselib/gobj.h>
#include <baselib/gobjgxlink.h>
#include <baselib/gobjobject.h>
#include <baselib/gobjproc.h>
#include <baselib/jobj.h>

static SceneDesc* un_804D6FC0;
static SceneDesc* un_804D6FC4;
static HSD_Archive* un_804D6FC8;
static HSD_Archive* un_804D6FCC;

static Vec3 un_80400200[3] = {
    { 0.0f, 0.0f, 0.0f },
    { 15.8512f, 67.0f, 0.0f },
    { -15.7657f, 67.0f, 0.0f },
};

static struct {
    HSD_GObj* p1;
    HSD_GObj* p2;
} un_804D6FD0;

void un_8031F294(int char_index, int costume_index)
{
    HSD_JObj* jobj;
    Vec3* pmtx;
    char pad[40];

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

    Player_80036E20(char_index, un_804D6FC8, 3);
    Player_SetPlayerCharacter(0, char_index);
    Player_SetCostumeId(0, costume_index);
    Player_SetPlayerId(0, 0);
    Player_SetSlottype(0, Gm_PKind_Demo);
    Player_SetFacingDirection(0, 1.0f);
    Player_80032768(0, un_80400200);
    Player_80036F34(0, 8);

    pmtx = grLib_801C9A10();

    Player_80036E20(CKIND_MARIO, un_804D6FCC, 5);
    Player_SetPlayerCharacter(1, CKIND_MARIO);
    Player_SetCostumeId(1, 0);
    Player_SetPlayerId(1, 0);
    Player_SetSlottype(1, Gm_PKind_Demo);
    Player_SetFacingDirection(1, 0.0f);
    Player_80032768(1, un_80400200);
    Player_SetFlagsBit5(1, 1);
    Player_80036F34(1, 0xA);
    un_804D6FD0.p1 = Player_GetEntity(1);
    jobj = un_804D6FD0.p1->hsd_obj;
    HSD_JObjReqAnimAll(jobj, 432.0f);
    HSD_JObjAnimAll(jobj);
    pmtx[1] = un_80400200[1];
    HSD_JObjReqAnimAll(jobj, 0.0f);

    if (gm_80164840(7) != 0) {
        Player_80036E20(CKIND_LUIGI, un_804D6FCC, 5);
        Player_SetPlayerCharacter(2, CKIND_LUIGI);
        Player_SetCostumeId(2, 0);
        Player_SetPlayerId(2, 0);
        Player_SetSlottype(2, Gm_PKind_Demo);
        Player_SetFacingDirection(2, 0.0f);
        Player_80032768(2, un_80400200);
        Player_SetFlagsBit5(2, 1);
        Player_80036F34(2, 0xA);
        un_804D6FD0.p2 = Player_GetEntity(2);
        jobj = un_804D6FD0.p2->hsd_obj;
        HSD_JObjReqAnimAll(jobj, 432.0f);
        HSD_JObjAnimAll(jobj);
        pmtx[2] = un_80400200[2];
        HSD_JObjReqAnimAll(jobj, 0.0f);
    }

    lbAudioAx_80026F2C(0x1C);
    lbAudioAx_8002702C(0xC,
                       lbAudioAx_80026E84(char_index) | 0x0020000000000000ULL);
    lbAudioAx_80027168();
    lbAudioAx_80027648();
}

void fn_8031F548(HSD_GObj* gobj)
{
    HSD_JObjAnimAll(GET_JOBJ(gobj));
}

static void fn_8031F56C(HSD_GObj* gobj)
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

/// #un_8031F714_OnEnter

void un_8031F960_OnFrame(void)
{
    vi_8031CAAC();
}
