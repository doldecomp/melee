#include "vi0502.h"

#include "baselib/gobj.h"
#include "baselib/mtx.h"
#include "cm/camera.h"
#include "ef/efasync.h"
#include "ef/eflib.h"

#include "ft/forward.h"

#include "ft/ftdemo.h"
#include "gm/gm_1A36.h"
#include "gm/gm_unsplit.h"
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
#include <baselib/mtx.h>
#include <baselib/wobj.h>

const GXColor erase_colors_vi0502 = { 0, 0, 0, 0 };

Vec3 initial_pos = { 0, 0, 0 };

static HSD_Archive* un_804D6F94;
static HSD_GObj* kirby_gobj;

void vi0502_8031E124(CharacterKind player_kind, s8 player_costume,
                     s8 kirby_costume)
{
    HSD_JObj* jobj;
    VecMtxPtr pmtx;

    Camera_80028B9C(6);
    lb_8000FCDC();
    mpColl_80041C78();
    Ground_801C0378(0x40);
    Stage_802251E8(17, 0);
    Item_80266FA8();
    Item_80266FCC();
    Ground_801C04BC(0.7f);
    Stage_8022524C();
    Stage_8022532C(17, 0);

    ftDemo_ObjAllocInit();
    Player_InitAllPlayers();

    Player_80036E20(player_kind, un_804D6F94, 3);
    Player_SetPlayerCharacter(0, player_kind);
    Player_SetCostumeId(0, player_costume);
    Player_SetPlayerId(0, 0);
    Player_SetSlottype(0, Gm_PKind_Demo);
    Player_SetFacingDirection(0, 1.0f);
    Player_80032768(0, &initial_pos);
    Player_80036F34(0, 8);

    Player_80036E20(CKIND_KIRBY, un_804D6F94, 7);
    Player_SetPlayerCharacter(1, CKIND_KIRBY);
    Player_SetCostumeId(1, kirby_costume);
    Player_SetPlayerId(1, 0);
    Player_SetSlottype(1, Gm_PKind_Demo);
    Player_SetFacingDirection(1, 1.0f);
    Player_80036F34(1, 14);

    kirby_gobj = Player_GetEntity(1);
    jobj = GET_JOBJ(kirby_gobj);
    HSD_JObjReqAnimAll(jobj, 120.0f);
    HSD_JObjAnimAll(jobj);
    jobj = GET_JOBJ(kirby_gobj);
    pmtx = grLib_801C9A10();
    HSD_JObjGetTranslation2(jobj, &pmtx[1]);

    HSD_JObjReqAnimAll(jobj, 0.0f);

    lbAudioAx_80026F2C(0x1C);
    lbAudioAx_8002702C(12, 0x80000004000);
    lbAudioAx_80027168();
    lbAudioAx_80027648();
}

void vi0502_8031E304(HSD_GObj* gobj)
{
    HSD_JObjAnimAll(GET_JOBJ(gobj));
}

void vi0502_8031E328(HSD_GObj* gobj)
{
    HSD_CObj* cobj;
    lbShadow_8000F38C(0);
    cobj = GET_COBJ(gobj);
    if (HSD_CObjSetCurrent(cobj)) {
        HSD_SetEraseColor(erase_colors_vi0502.r, erase_colors_vi0502.g,
                          erase_colors_vi0502.b, erase_colors_vi0502.a);
        cobj = GET_COBJ(gobj);
        HSD_CObjEraseScreen(cobj, 1, 0, 1);
        vi_8031CA04(gobj);
        gobj->gxlink_prios = 0x281;
        HSD_GObj_80390ED0(gobj, 7);
        HSD_CObjEndCurrent();
    }
}

void vi0502_RunFrame(HSD_GObj* gobj)
{
    HSD_CObj* cobj;

    cobj = GET_COBJ(gobj);
    HSD_CObjAnim(cobj);

    if (30.0f == cobj->eyepos->aobj->curr_frame) {
        vi_8031C9B4(14, 0);
        lbAudioAx_800237A8(430009, 0x7F, 0x40);
    }
    if (cobj->eyepos->aobj->curr_frame == cobj->eyepos->aobj->end_frame) {
        lb_800145F4();
        gm_801A4B60();
    }
}
