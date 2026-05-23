#include "ftCh_Poke.h"

#include "ftCh_Init.h"

#include <placeholder.h>
#include <platform.h>

#include "baselib/forward.h"

#include "ft/fighter.h"
#include "ft/ft_084E.h"
#include "ft/ftbosslib.h"
#include "ft/inlines.h"
#include "ft/types.h"
#include "ftCrazyHand/ftCh_TagCancel.h"
#include "ftMasterHand/types.h"
#include "it/items/itmasterhandlaser.h"
#include "lb/lb_00B0.h"
#include "lb/lbaudio_ax.h"
#include "pl/player.h"

#include <common_structs.h>
#include <dolphin/mtx.h>
#include <MetroTRK/intrinsics.h>

void fn_80158534(HSD_GObj* gobj);
void ftCh_Init_8015868C(HSD_GObj* gobj);

void fn_801582D8(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    Fighter_ChangeMotionState(gobj, 0x166, 0, 0.0f, 1.0f, 0.0f, NULL);
    ftAnim_8006EBA4(gobj);
    fp->mv.ch.unk0.x38 = -1;
    fp->mv.ch.unk0.x3C = -1;
    fp->mv.ch.unk0.x40 = -1;
}

void ftCh_PaperCrush_Anim(HSD_GObj* gobj)
{
    if (ftAnim_IsFramesRemaining(gobj) == 0) {
        ftCh_Init_801583E4(gobj);
    }
}

void ftCh_PaperCrush_IASA(HSD_GObj* gobj)
{
    Fighter* ft = GET_FIGHTER(gobj);
    if (Player_GetPlayerSlotType(ft->player_id) == Gm_PKind_Human) {
        ftBossLib_8015BD20(gobj);
    }
}

void ftCh_PaperCrush_Phys(HSD_GObj* gobj)
{
    ft_80085134(gobj);
}

void ftCh_PaperCrush_Coll(HSD_GObj* gobj) {}

void ftCh_Init_801583E4(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    Fighter_ChangeMotionState(gobj, 0x167, 0, 0.0f, 1.0f, 0.0f, NULL);
    ftAnim_8006EBA4(gobj);
    fp->accessory4_cb = fn_80158534;
    fp->cmd_vars[0] = 1;
}

void ftCh_Poke1_Anim(HSD_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        Fighter* fp = GET_FIGHTER(gobj);
        ftCh_Init_8015868C(gobj);
        it_802F046C(fp->mv.ch.grab.x28);
        it_802F046C(fp->mv.ch.grab.x2C);
        it_802F046C(fp->mv.ch.grab.x30);
        it_802F046C(fp->mv.ch.grab.x34);
        fp->mv.ch.grab.x28 = NULL;
        fp->mv.ch.grab.x2C = NULL;
        fp->mv.ch.grab.x30 = NULL;
        fp->mv.ch.grab.x34 = NULL;
    }
}

void ftCh_Poke1_IASA(HSD_GObj* gobj)
{
    Fighter* ft = GET_FIGHTER(gobj);
    if (Player_GetPlayerSlotType(ft->player_id) == Gm_PKind_Human) {
        ftBossLib_8015BD20(gobj);
    }
}

void ftCh_Poke1_Phys(HSD_GObj* gobj)
{
    ft_80085134(gobj);
}

void ftCh_Poke1_Coll(HSD_GObj* gobj) {}

void fn_80158534(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (fp->cmd_vars[0] == 0) {
        return;
    }

    {
        Vec3 vec;
        lb_8000B1CC(fp->parts[FtPart_RLegJA].joint, 0, &vec);
        fp->mv.ch.grab.x28 =
            it_802F0340(gobj, &vec, &vec, FtPart_RLegJA, 125, fp->facing_dir);
        lb_8000B1CC(fp->parts[FtPart_BustN].joint, 0, &vec);
        fp->mv.ch.grab.x2C =
            it_802F0340(gobj, &vec, &vec, FtPart_BustN, 125, fp->facing_dir);
        lb_8000B1CC(fp->parts[FtPart_LHandN].joint, 0, &vec);
        fp->mv.ch.grab.x30 =
            it_802F0340(gobj, &vec, &vec, FtPart_LHandN, 125, fp->facing_dir);
        lb_8000B1CC(fp->parts[FtPart_L3rdNa].joint, 0, &vec);
        fp->mv.ch.grab.x34 =
            it_802F0340(gobj, &vec, &vec, FtPart_L3rdNa, 125, fp->facing_dir);
        fp->mv.ch.unk0.x38 = lbAudioAx_800237A8(320004, 127, 64);
        fp->mv.ch.unk0.x3C = lbAudioAx_800237A8(320005, 127, 64);
        fp->mv.ch.unk0.x40 = lbAudioAx_800237A8(320006, 127, 64);
        fp->cmd_vars[0] = 0;
    }
}

void ftCh_Init_8015868C(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    Fighter_ChangeMotionState(gobj, 0x168, 0, 0.0f, 1.0f, 0.0f, NULL);
    ftAnim_8006EBA4(gobj);
    lbAudioAx_800236B8(fp->mv.ch.unk0.x38);
    lbAudioAx_800236B8(fp->mv.ch.unk0.x3C);
    lbAudioAx_800236B8(fp->mv.ch.unk0.x40);
    fp->mv.ch.unk0.x38 = -1;
    fp->mv.ch.unk0.x3C = -1;
    fp->mv.ch.unk0.x40 = -1;
}

void ftCh_Poke2_Anim(HSD_GObj* gobj)
{
    if (ftAnim_IsFramesRemaining(gobj) == 0) {
        ftCh_GrabUnk1_8015BC88(gobj);
    }
}

void ftCh_Poke2_IASA(HSD_GObj* gobj)
{
    Fighter* ft = GET_FIGHTER(gobj);
    if (Player_GetPlayerSlotType(ft->player_id) == Gm_PKind_Human) {
        ftBossLib_8015BD20(gobj);
    }
}

void ftCh_Poke2_Phys(HSD_GObj* gobj)
{
    ft_80085134(gobj);
}

void ftCh_Poke2_Coll(HSD_GObj* gobj) {}
