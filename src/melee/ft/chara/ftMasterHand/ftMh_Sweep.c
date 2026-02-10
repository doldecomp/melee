#include "ftMh_Sweep.h"

#include <platform.h>

#include "ft/fighter.h"
#include "ft/ft_081B.h"
#include "ft/ftanim.h"
#include "ft/ftbosslib.h"
#include "ft/types.h"
#include "ftMasterHand/types.h"
#include "mp/mplib.h"
#include "pl/player.h"

#include <dolphin/mtx.h>

void ftMh_Damage_IASA(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (!Player_GetPlayerSlotType(fp->player_id)) {
        ftBossLib_8015BD20(gobj);
    }
}

void ftMh_Damage_Phys(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftMasterHand_SpecialAttrs* da = fp->ft_data->ext_attr;
    fp->self_vel.y += da->x150;
    fp->self_vel.z += da->x158;
}

void ftMh_Damage_Coll(HSD_GObj* gobj) {}

void ftMh_MS_344_80151828(HSD_GObj* gobj)
{
    Fighter_ChangeMotionState(gobj, ftMh_MS_WaitSweep, 0, 0, 1, 0, 0);
    ftAnim_8006EBA4(gobj);
}

void ftMh_WaitSweep_Anim(HSD_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftMh_MS_346_80151918(gobj);
    }
}

void ftMh_WaitSweep_IASA(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (!Player_GetPlayerSlotType(fp->player_id)) {
        ftBossLib_8015BD20(gobj);
    }
}

void ftMh_WaitSweep_Phys(HSD_GObj* gobj)
{
    ft_80085134(gobj);
}

void ftMh_WaitSweep_Coll(HSD_GObj* gobj) {}

void ftMh_MS_346_80151918(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftMasterHand_SpecialAttrs* da = fp->ft_data->ext_attr;
    fp->mv.mh.unk0.xC.x = fp->cur_pos.x - da->x3C;
    fp->mv.mh.unk0.xC.y = da->x38;
    fp->mv.mh.unk0.xC.z = 0;
    Fighter_ChangeMotionState(gobj, ftMh_MS_SweepLoop, 0, 0, 1, 0, 0);
    ftAnim_8006EBA4(gobj);
}

static void ftMh_MS_347_80151AC8(HSD_GObj* gobj);

void ftMh_SweepLoop_Anim(HSD_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        /// @todo #GET_FIGHTER
        Fighter* fp = gobj->user_data;
        Vec3 pos;

        u8 _[8];
        mpFloorGetLeft(0, &pos);
        if (fp->cur_pos.x < pos.x) {
            ftMh_MS_347_80151AC8(gobj);
            return;
        }
        {
            Fighter* fp = gobj->user_data;
            ftMasterHand_SpecialAttrs* da = fp->ft_data->ext_attr;
            fp->mv.mh.unk0.xC.x = fp->cur_pos.x - da->x3C;
            fp->mv.mh.unk0.xC.y = da->x38;
            fp->mv.mh.unk0.xC.z = 0;
        }
        Fighter_ChangeMotionState(gobj, ftMh_MS_SweepLoop, 0, 0, 1, 0, 0);
        ftAnim_8006EBA4(gobj);
    }
}

void ftMh_SweepLoop_IASA(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (Player_GetPlayerSlotType(fp->player_id) == 0) {
        ftBossLib_8015BD20(gobj);
    }
}

void ftMh_SweepLoop_Phys(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftMasterHand_SpecialAttrs* da = fp->ft_data->ext_attr;
    ftBossLib_8015BE40(gobj, &fp->mv.mh.unk0.xC, &fp->mv.mh.unk0.x18, da->x2C,
                       da->x28);
}

void ftMh_SweepLoop_Coll(HSD_GObj* gobj) {}

static void ftMh_MS_347_80151AC8(HSD_GObj* gobj)
{
    Fighter_ChangeMotionState(gobj, ftMh_MS_SweepWait, 0, 0, 1, 0, 0);
    ftAnim_8006EBA4(gobj);
}
