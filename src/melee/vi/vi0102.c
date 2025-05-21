#include <placeholder.h>

#include <baselib/forward.h>

#include "vi/vi0102.h"

#include "cm/camera.h"
#include "ft/ftdemo.h"
#include "gm/gm_1A36.h"
#include "gr/ground.h"
#include "gr/stage.h"
#include "it/item.h"
#include "lb/lb_00F9.h"
#include "lb/lbaudio_ax.h"
#include "lb/lbshadow.h"
#include "mp/mpcoll.h"
#include "pl/player.h"
#include "vi/vi.h"

#include <baselib/aobj.h>
#include <baselib/cobj.h>
#include <baselib/displayfunc.h>
#include <baselib/wobj.h>

Vec3 un_80400010;

static HSD_Archive* un_804D6F38;
static u8 erase_colors_vi0102[4];
static struct un_804D6F60_t un_804D6F60;

void vi_8031CB00(s8 mario_costume, s8 luigi_costume)
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

    Player_80036E20(8, un_804D6F38, 4);
    Player_SetPlayerCharacter(0, 8);
    Player_SetCostumeId(0, mario_costume);
    Player_SetPlayerId(0, 0);
    Player_SetSlottype(0, 2);
    Player_SetFacingDirection(0, 1.0f);
    Player_80032768(0, &un_80400010);
    Player_80036F34(0, 9);

    Player_80036E20(7, un_804D6F38, 4);
    Player_SetPlayerCharacter(1, 7);
    Player_SetCostumeId(1, luigi_costume);
    Player_SetPlayerId(1, 0);
    Player_SetSlottype(1, 2);
    Player_SetFacingDirection(1, 1.0f);
    Player_80032768(1, &un_80400010);
    Player_80036F34(1, 9);

    lbAudioAx_80026F2C(0x18);
    lbAudioAx_8002702C(8, 0x400000000);
    lbAudioAx_80027168();
    lbAudioAx_80027648();
}

void vi_8031CC68(HSD_GObj* gobj)
{
    HSD_JObjAnimAll(GET_JOBJ(gobj));
}

void vi_8031CC8C(HSD_GObj* gobj)
{
    PAD_STACK(8);
    lbShadow_8000F38C(0);
    vi_EraseScreen(gobj, erase_colors_vi0102, 0x881);
}

void vi_8031CD20(HSD_GObj* gobj)
{
    HSD_CObj* cobj;

    cobj = GET_COBJ(gobj);
    HSD_CObjAnim(cobj);

    if (190.0f == cobj->eyepos->aobj->curr_frame) {
        vi_8031C9B4(33, 0);
    }
    if (cobj->eyepos->aobj->curr_frame == cobj->eyepos->aobj->end_frame) {
        lb_800145F4();
        gm_801A4B60();
    }
}

/// #vi_8031CD94

void vi_8031D000(void)
{
    vi_8031CAAC();
}

void vi_8031D020(s8 arg0, s8 arg1)
{
    un_804D6F60.unk_0 = arg0;
    un_804D6F60.unk_1 = arg1;
}
