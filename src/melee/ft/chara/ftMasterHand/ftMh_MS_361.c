#include "ft/forward.h"

#include "ftMh_MS_361.h"

#include "ft/ft_081B.h"
#include "ft/ftbosslib.h"
#include "ft/inlines.h"
#include "it/it_27CF.h"
#include "lb/lb_00B0.h"
#include "lb/lbaudio_ax.h"

#include <dolphin/mtx/types.h>

void ftMh_MS_359_Coll(HSD_GObj* gobj) {}

void ftMh_MS_359_80152BCC(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    Fighter_ChangeMotionState(gobj, ftMh_MS_FingerBeamStart, 0, 0, 0, 1, 0);
    ftAnim_8006EBA4(gobj);
    fp->mv.mh.unk0.x28 = -1;
    fp->mv.mh.unk0.x2C = -1;
    fp->mv.mh.unk0.x30 = -1;
}

void ftMh_MS_361_Anim(HSD_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftMh_MS_361_80152CD8(gobj);
    }
}

void ftMh_MS_361_IASA(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (Player_GetPlayerSlotType(fp->xC_playerID) == 0) {
        ftBossLib_8015BD20(gobj);
    }
}

void ftMh_MS_361_Phys(HSD_GObj* gobj)
{
    ft_80085134(gobj);
}

void ftMh_MS_361_Coll(HSD_GObj* gobj) {}

void ftMh_MS_361_80152CD8(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    Fighter_ChangeMotionState(gobj, ftMh_MS_FingerBeamLoop, 0, 0, 0, 1, 0);
    ftAnim_8006EBA4(gobj);
    fp->cb.x21BC_callback_Accessory4 = ftMh_MS_362_80152E28;
    fp->x2200_ftcmd_var0 = 1;
}

static void ftMh_MS_362_80152F80(HSD_GObj* gobj);

void ftMh_MS_362_Anim(HSD_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        Fighter* fp = GET_FIGHTER(gobj);
        ftMh_MS_362_80152F80(gobj);
        it_802F046C(fp->mv.mh.unk0.x34);
        it_802F046C(fp->mv.mh.unk0.x38);
        it_802F046C(fp->mv.mh.unk0.x3C);
        it_802F046C(fp->mv.mh.unk0.x40);
        fp->mv.mh.unk0.x34 = 0;
        fp->mv.mh.unk0.x38 = 0;
        fp->mv.mh.unk0.x3C = 0;
        fp->mv.mh.unk0.x40 = 0;
    }
}

void ftMh_MS_362_IASA(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (Player_GetPlayerSlotType(fp->xC_playerID) == 0) {
        ftBossLib_8015BD20(gobj);
    }
}

void ftMh_MS_362_Phys(HSD_GObj* gobj)
{
    ft_80085134(gobj);
}

void ftMh_MS_362_Coll(HSD_GObj* gobj) {}

void ftMh_MS_362_80152E28(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (fp->x2200_ftcmd_var0 == 0) {
        return;
    }

    {
        Vec3 vec;
        lb_8000B1CC(fp->parts[FtPart_RLegJA].x0_jobj, 0, &vec);
        fp->mv.mh.unk0.x34 =
            it_802F0340(gobj, &vec, &vec, FtPart_RLegJA, 125, fp->facing_dir);
        lb_8000B1CC(fp->parts[FtPart_BustN].x0_jobj, 0, &vec);
        fp->mv.mh.unk0.x38 =
            it_802F0340(gobj, &vec, &vec, FtPart_BustN, 125, fp->facing_dir);
        lb_8000B1CC(fp->parts[FtPart_LHandN].x0_jobj, 0, &vec);
        fp->mv.mh.unk0.x3C =
            it_802F0340(gobj, &vec, &vec, FtPart_LHandN, 125, fp->facing_dir);
        lb_8000B1CC(fp->parts[FtPart_L3rdNa].x0_jobj, 0, &vec);
        fp->mv.mh.unk0.x40 =
            it_802F0340(gobj, &vec, &vec, FtPart_L3rdNa, 125, fp->facing_dir);
        fp->mv.mh.unk0.x28 = lbAudioAx_800237A8(320004, 127, 64);
        fp->mv.mh.unk0.x2C = lbAudioAx_800237A8(320005, 127, 64);
        fp->mv.mh.unk0.x30 = lbAudioAx_800237A8(320006, 127, 64);
        fp->x2200_ftcmd_var0 = 0;
    }
}

static void ftMh_MS_362_80152F80(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    Fighter_ChangeMotionState(gobj, ftMh_MS_FingerBeamEnd, 0, 0, 0, 1, 0);
    ftAnim_8006EBA4(gobj);
    lbAudioAx_800236B8(fp->mv.mh.unk0.x28);
    lbAudioAx_800236B8(fp->mv.mh.unk0.x2C);
    lbAudioAx_800236B8(fp->mv.mh.unk0.x30);
    fp->mv.mh.unk0.x28 = -1;
    fp->mv.mh.unk0.x2C = -1;
    fp->mv.mh.unk0.x30 = -1;
}
