#include "ftMh_FingerBeam.h"

#include <platform.h>

#include "baselib/forward.h"

#include "ft/fighter.h"
#include "ft/ft_081B.h"
#include "ft/ftanim.h"
#include "ft/ftbosslib.h"
#include "ft/types.h"
#include "ftMasterHand/types.h"
#include "it/items/itmasterhandlaser.h"
#include "lb/lb_00B0.h"
#include "lb/lbaudio_ax.h"
#include "pl/player.h"

#include <dolphin/mtx.h>

void ftMh_Poke1_Coll(HSD_GObj* gobj) {}

void ftMh_MS_359_80152BCC(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    Fighter_ChangeMotionState(gobj, ftMh_MS_FingerBeamStart, 0, 0, 1, 0, 0);
    ftAnim_8006EBA4(gobj);
    fp->mv.mh.unk0.x28 = -1;
    fp->mv.mh.unk0.x2C = -1;
    fp->mv.mh.unk0.x30 = -1;
}

void ftMh_FingerBeamStart_Anim(HSD_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftMh_MS_361_80152CD8(gobj);
    }
}

void ftMh_FingerBeamStart_IASA(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (Player_GetPlayerSlotType(fp->player_id) == 0) {
        ftBossLib_8015BD20(gobj);
    }
}

void ftMh_FingerBeamStart_Phys(HSD_GObj* gobj)
{
    ft_80085134(gobj);
}

void ftMh_FingerBeamStart_Coll(HSD_GObj* gobj) {}

void ftMh_MS_361_80152CD8(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    Fighter_ChangeMotionState(gobj, ftMh_MS_FingerBeamLoop, 0, 0, 1, 0, 0);
    ftAnim_8006EBA4(gobj);
    fp->accessory4_cb = ftMh_MS_362_80152E28;
    fp->cmd_vars[0] = 1;
}

static void ftMh_MS_362_80152F80(HSD_GObj* gobj);

void ftMh_FingerBeamLoop_Anim(HSD_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        Fighter* fp = GET_FIGHTER(gobj);
        ftMh_MS_362_80152F80(gobj);
        it_802F046C(fp->mv.mh.fingerbeam.x34);
        it_802F046C(fp->mv.mh.fingerbeam.x38);
        it_802F046C(fp->mv.mh.fingerbeam.x3C);
        it_802F046C(fp->mv.mh.fingerbeam.x40);
        fp->mv.mh.unk0.x34 = 0;
        fp->mv.mh.unk0.x38 = 0;
        fp->mv.mh.unk0.x3C = 0;
        fp->mv.mh.unk0.x40 = 0;
    }
}

void ftMh_FingerBeamLoop_IASA(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (Player_GetPlayerSlotType(fp->player_id) == 0) {
        ftBossLib_8015BD20(gobj);
    }
}

void ftMh_FingerBeamLoop_Phys(HSD_GObj* gobj)
{
    ft_80085134(gobj);
}

void ftMh_FingerBeamLoop_Coll(HSD_GObj* gobj) {}

void ftMh_MS_362_80152E28(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (fp->cmd_vars[0] == 0) {
        return;
    }

    {
        Vec3 vec;
        lb_8000B1CC(fp->parts[FtPart_RLegJA].joint, 0, &vec);
        fp->mv.mh.fingerbeam.x34 =
            it_802F0340(gobj, &vec, &vec, FtPart_RLegJA, 125, fp->facing_dir);
        lb_8000B1CC(fp->parts[FtPart_BustN].joint, 0, &vec);
        fp->mv.mh.fingerbeam.x38 =
            it_802F0340(gobj, &vec, &vec, FtPart_BustN, 125, fp->facing_dir);
        lb_8000B1CC(fp->parts[FtPart_LHandN].joint, 0, &vec);
        fp->mv.mh.fingerbeam.x3C =
            it_802F0340(gobj, &vec, &vec, FtPart_LHandN, 125, fp->facing_dir);
        lb_8000B1CC(fp->parts[FtPart_L3rdNa].joint, 0, &vec);
        fp->mv.mh.fingerbeam.x40 =
            it_802F0340(gobj, &vec, &vec, FtPart_L3rdNa, 125, fp->facing_dir);
        fp->mv.mh.unk0.x28 = lbAudioAx_800237A8(320004, 127, 64);
        fp->mv.mh.unk0.x2C = lbAudioAx_800237A8(320005, 127, 64);
        fp->mv.mh.unk0.x30 = lbAudioAx_800237A8(320006, 127, 64);
        fp->cmd_vars[0] = 0;
    }
}

static void ftMh_MS_362_80152F80(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    Fighter_ChangeMotionState(gobj, ftMh_MS_FingerBeamEnd, 0, 0, 1, 0, 0);
    ftAnim_8006EBA4(gobj);
    lbAudioAx_800236B8(fp->mv.mh.unk0.x28);
    lbAudioAx_800236B8(fp->mv.mh.unk0.x2C);
    lbAudioAx_800236B8(fp->mv.mh.unk0.x30);
    fp->mv.mh.unk0.x28 = -1;
    fp->mv.mh.unk0.x2C = -1;
    fp->mv.mh.unk0.x30 = -1;
}
