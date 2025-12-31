#include "vi0401.h"

#include "vi.h"

#include <placeholder.h>

#include "baselib/forward.h"

#include "cm/camera.h"
#include "ft/ftdemo.h"
#include "gm/gm_unsplit.h"
#include "gr/ground.h"
#include "gr/stage.h"
#include "it/item.h"
#include "lb/lb_00F9.h"
#include "lb/lbaudio_ax.h"
#include "mp/mpcoll.h"
#include "pl/player.h"

#include <baselib/aobj.h>
#include <baselib/cobj.h>
#include <baselib/gobj.h>
#include <baselib/jobj.h>

typedef struct un_804D6F58_t {
    char pad[0x38];
    Vec3 x38;
} un_804D6F58_t;

extern HSD_Archive* un_804D6F54;
extern un_804D6F58_t* un_804D6F58;

static GXColor erase_colors_vi0401;

void un_8031D030(CharacterKind char_kind, int costume)
{
    Vec3 pos;

    Camera_80028B9C(6);
    lb_8000FCDC();
    mpColl_80041C78();
    Ground_801C0378(0x40);
    Stage_802251E8(6, 0);
    Item_80266FA8();
    Item_80266FCC();
    Stage_8022524C();
    Stage_8022532C(6, 0);

    ftDemo_ObjAllocInit();
    Player_InitAllPlayers();

    Player_80036E20(char_kind, un_804D6F54, 3);
    Player_SetPlayerCharacter(0, char_kind);
    Player_SetCostumeId(0, costume);
    Player_SetPlayerId(0, 0);
    Player_SetSlottype(0, Gm_PKind_Demo);
    Player_SetFacingDirection(0, 1.0f);

    assert(un_804D6F58 != NULL);
    pos.x = un_804D6F58->x38.x;
    pos.y = un_804D6F58->x38.y;
    pos.z = un_804D6F58->x38.z;
    Player_80032768(0, &pos);
    Player_80036F34(0, 8);

    lbAudioAx_80026F2C(0x18);
    lbAudioAx_8002702C(8, 0x10000000000ULL);
    lbAudioAx_80027168();
    lbAudioAx_80027648();
    lbAudioAx_80024634(0x88);
}

static void vi0401_8031D18C(HSD_GObj* gobj)
{
    HSD_JObjAnimAll(GET_JOBJ(gobj));
}

static void vi0401_8031D1B0(HSD_GObj* gobj, int unused)
{
    HSD_CObj* cobj;

    cobj = GET_COBJ(gobj);
    if (HSD_CObjSetCurrent(cobj)) {
        HSD_SetEraseColor(erase_colors_vi0401.r, erase_colors_vi0401.g,
                          erase_colors_vi0401.b, erase_colors_vi0401.a);
        cobj = GET_COBJ(gobj);
        HSD_CObjEraseScreen(cobj, 1, 0, 1);
        vi_8031CA04(gobj);
        gobj->gxlink_prios = 0x281;
        HSD_GObj_80390ED0(gobj, 7);
        HSD_CObjEndCurrent();
    }
}

static void vi0401_8031D23C(HSD_GObj* gobj)
{
    HSD_AObj* aobj;
    HSD_CObj* cobj = GET_COBJ(gobj);

    HSD_CObjAnim(cobj);
    aobj = cobj->aobj;
    if (aobj->curr_frame == aobj->end_frame) {
        lb_800145F4();
        gm_801A4B60();
    }
}

void un_8031D698_OnFrame(void)
{
    u64 buttons;
    gm_8017E430();
    buttons = gm_801A36A0(0);
    if ((buttons & 0x1000ULL) != 0) {
        lb_800145F4();
        gm_801A4B60();
    }
}
