#include "ftCh_FingerBeam_0.h"

#include "types.h"

#include <placeholder.h>
#include <platform.h>

#include "baselib/forward.h"

#include "ft/fighter.h"
#include "ft/ft_084E.h"
#include "ft/ft_0877.h"
#include "ft/ftbosslib.h"
#include "ft/inlines.h"
#include "ft/types.h"
#include "ftCrazyHand/ftCh_TagCancel.h"
#include "it/items/itcrazyhandbomb.h"
#include "lb/lb_00B0.h"
#include "pl/player.h"

#include <common_structs.h>
#include <dolphin/mtx.h>
#include <MetroTRK/intrinsics.h>

static void fn_801588B8(HSD_GObj* gobj);

void fn_801587B0(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    Fighter_ChangeMotionState(gobj, 0x169, 0, 0.0f, 1.0f, 0.0f, NULL);
    fp->cmd_vars[0] = 0;
    fp->cmd_vars[1] = 0;
    fp->cmd_vars[2] = 0;
    fp->cmd_vars[3] = 0;
    fp->accessory4_cb = fn_801588B8;
}

void ftCh_FingerBeamStart_Anim(HSD_GObj* gobj)
{
    if (ftAnim_IsFramesRemaining(gobj) == 0) {
        ftCh_GrabUnk1_8015BC88(gobj);
    }
}

void ftCh_FingerBeamStart_IASA(HSD_GObj* gobj)
{
    Fighter* ft = GET_FIGHTER(gobj);
    if (Player_GetPlayerSlotType(ft->player_id) == Gm_PKind_Human) {
        ftBossLib_8015BD20(gobj);
    }
}

void ftCh_FingerBeamStart_Phys(HSD_GObj* gobj)
{
    ft_80085134(gobj);
}

void ftCh_FingerBeamStart_Coll(HSD_GObj* gobj) {}

static void fn_801588B8(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCrazyHand_DatAttrs* da = fp->ft_data->ext_attr;
    Vec3 pos, prev;
    if (fp->cmd_vars[0] != 0) {
        lb_8000B1CC(fp->parts[FtPart_RLegJA].joint, NULL, &pos);
        prev = pos;
        pos.x += da->xA0;
        pos.y += da->xA4;
        it_802F0F6C(gobj, &pos, &prev, It_Kind_CrazyHand_Bomb, fp->facing_dir);
        fp->cmd_vars[0] = 0;
        ft_PlaySFX(fp, 0x4E203, 0x7F, 0x40);
    }
    if (fp->cmd_vars[1] != 0) {
        lb_8000B1CC(fp->parts[FtPart_BustN].joint, NULL, &pos);
        prev = pos;
        pos.x += da->xA8_pos.x;
        pos.y += da->xA8_pos.y;
        it_802F0F6C(gobj, &pos, &prev, It_Kind_CrazyHand_Bomb, fp->facing_dir);
        fp->cmd_vars[1] = 0;
        ft_PlaySFX(fp, 0x4E203, 0x7F, 0x40);
    }
    if (fp->cmd_vars[2] != 0) {
        lb_8000B1CC(fp->parts[FtPart_LHandN].joint, NULL, &pos);
        prev = pos;
        pos.x += da->xB0;
        pos.y += da->xB4;
        it_802F0F6C(gobj, &pos, &prev, It_Kind_CrazyHand_Bomb, fp->facing_dir);
        fp->cmd_vars[2] = 0;
        ft_PlaySFX(fp, 0x4E203, 0x7F, 0x40);
    }
    if (fp->cmd_vars[3] != 0) {
        lb_8000B1CC(fp->parts[FtPart_L3rdNa].joint, NULL, &pos);
        prev = pos;
        pos.x += da->xB8;
        pos.y += da->xBC_pos.x;
        it_802F0F6C(gobj, &pos, &prev, It_Kind_CrazyHand_Bomb, fp->facing_dir);
        fp->cmd_vars[3] = 0;
        ft_PlaySFX(fp, 0x4E203, 0x7F, 0x40);
    }
}
