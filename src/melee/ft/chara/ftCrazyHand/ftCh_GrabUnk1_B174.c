#include "ftCh_GrabUnk1_B174.h"

#include "ftCh_Init.h"

#include "math.h"
#include "types.h"

#include <placeholder.h>
#include <platform.h>

#include "baselib/forward.h"

#include "cm/camera.h"
#include "ft/chara/ftCommon/ftCo_Attack100.h"
#include "ft/chara/ftCommon/ftCo_CaptureCut.h"
#include "ft/chara/ftCommon/ftCo_Lift.h"
#include "ft/chara/ftCommon/ftCo_Throw.h"
#include "ft/chara/ftCommon/ftCo_Thrown.h"
#include "ft/fighter.h"
#include "ft/ft_081B.h"
#include "ft/ft_0877.h"
#include "ft/ft_0881.h"
#include "ft/ft_0D4D.h"
#include "ft/ftbosslib.h"
#include "ft/ftcamera.h"
#include "ft/ftcommon.h"
#include "ft/ftlib.h"
#include "ft/inlines.h"
#include "ft/types.h"

#include "ftCrazyHand/forward.h"

#include "ftMasterHand/types.h"
#include "gr/stage.h"
#include "it/it_26B1.h"
#include "it/items/itcrazyhandbomb.h"
#include "it/items/itmasterhandlaser.h"
#include "lb/lb_00B0.h"
#include "lb/lbaudio_ax.h"
#include "lb/lbvector.h"
#include "mp/mplib.h"
#include "pl/player.h"

#include <common_structs.h>
#include <dolphin/mtx.h>
#include <MetroTRK/intrinsics.h>

static void fn_8015B2C0(HSD_GObj* gobj);
bool fn_8015B4EC(Vec3* vec);

void ftCh_GrabUnk1_8015B174(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCrazyHand_DatAttrs* da = fp->ft_data->ext_attr;
    Fighter_ChangeMotionState(gobj, 0x183, 0, 0.0f, 1.0f, 0.0f, NULL);
    ftAnim_8006EBA4(gobj);
    fp->cur_pos.x = da->x18;
    fp->cur_pos.y = da->x1C;
    fp->cur_pos.z = 0;
    fp->accessory4_cb = fn_8015B2C0;
    fp->mv.ch.unk4.x0 = 0;
    ft_800881D8(fp, 320002, 127, 64);
    ftBossLib_8015C09C(gobj, 1);
}

void ftCh_TagFail_Anim(HSD_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        Fighter* fp = GET_FIGHTER(gobj);
        fp->fv.mh.x2258 = ftMh_MS_Wait1_0;
        ftCh_GrabUnk1_8015BC88(gobj);
    }
}

void ftCh_TagFail_IASA(HSD_GObj* gobj)
{
    Fighter* ft = GET_FIGHTER(gobj);
    if (Player_GetPlayerSlotType(ft->player_id) == Gm_PKind_Human) {
        ftBossLib_8015BD20(gobj);
    }
}

void ftCh_TagFail_Phys(HSD_GObj* gobj) {}

void ftCh_TagFail_Coll(HSD_GObj* gobj) {}

static void fn_8015B2C0(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    u8 _[16];
    switch (fp->mv.ch.unk4.x0) {
    case 0: {
        HSD_GObj* enemy_gobj = ftLib_8008627C(&fp->cur_pos, gobj);
        if (enemy_gobj != NULL) {
            Camera_8002E6FC((int) ftLib_80086BE0(enemy_gobj));
        } else {
            Camera_8002E6FC(0);
        }
        Camera_8002ED9C(40);
        Camera_8002EEC8(45);
        Camera_8002EC7C(-M_PI);
        Camera_8002EF14();
        Camera_8002EC7C(0);
        Camera_8002F0E4(120);
        fp->mv.ch.unk4.x0 = 1;
        return;
    }
    case 1: {
        if (Camera_8002F260() != 0) {
            Camera_8002E948(fn_8015B4EC);
            Camera_8002ED9C(120);
            Camera_8002F0E4(20);
            fp->mv.ch.unk4.x0 = 2;
        }
        return;
    }
    case 2: {
        if (Camera_8002F260() != 0) {
            Camera_8002EC7C(M_PI / 2);
            Camera_8002F0E4(60);
            fp->mv.ch.unk4.x0 = 3;
        }
        return;
    }
    case 3: {
        if (Camera_8002F260() != 0) {
            Camera_8002ED9C(90);
            Camera_8002EC7C(-M_PI / 9);
            Camera_8002EB5C(-M_PI / 12);
            Camera_8002EF14();
            fp->mv.ch.unk4.x0 = 4;
        }
        return;
    }
    case 4: {
        Camera_8002F274();
        fp->mv.ch.unk4.x8 = 120;
        fp->mv.ch.unk4.x0 = 5;
        return;
    }
    case 5: {
        if (--fp->mv.ch.unk4.x8 == 0) {
            Camera_8002EC7C(-M_PI / 9);
            Camera_8002EF14();
            Camera_8002ED9C(120);
            fp->mv.ch.unk4.x8 = 30;
            fp->mv.ch.unk4.x0 = 6;
        }
        return;
    }
    case 6: {
        if (--fp->mv.ch.unk4.x8 == 0) {
            Camera_8002EC7C(M_PI / 9);
            Camera_8002EF14();
            fp->mv.ch.unk4.x8 = 30;
            fp->mv.ch.unk4.x0 = 7;
        }
        return;
    }
    case 7: {
        if (--fp->mv.ch.unk4.x8 == 0) {
            Camera_8002ED9C(180);
            Camera_8002EC7C(-M_PI / 2);
            Camera_8002EB5C(-M_PI / 9);
            Camera_8002EF14();
            fp->mv.ch.unk4.x8 = 50;
            fp->mv.ch.unk4.x0 = 8;
        }
        return;
    }
    case 8: {
        Camera_8002F274();
        fp->mv.ch.unk4.x0 = 9;
        return;
    }
    case 9: {
        if (--fp->mv.ch.unk4.x8 == 0) {
            Camera_8002F474();
            fp->mv.ch.unk4.x0 = 10;
        }
        return;
    }
    }
    // NOTE: maybe add an #ifdef BUGFIX for case 10, like
    // ftMh_MS_343_801511FC?
}

bool fn_8015B4EC(Vec3* vec)
{
    HSD_GObj* gobj = ftBossLib_8015C3E8(28);
    if (gobj != NULL) {
        Fighter* fp = GET_FIGHTER(gobj);
        lb_8000B1CC(fp->parts[FtPart_WaistN].joint, 0, vec);
        return true;
    }
    return false;
}

