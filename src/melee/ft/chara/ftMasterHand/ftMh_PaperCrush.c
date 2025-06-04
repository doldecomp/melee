#include "ftMh_PaperCrush.h"

#include "ftMh_Wait1_2.h"

#include "ft/fighter.h"
#include "ft/ft_081B.h"
#include "ft/ftanim.h"
#include "ft/ftbosslib.h"
#include "ft/types.h"
#include "ftMasterHand/types.h"
#include "pl/player.h"

#include <dolphin/mtx.h>

void ftMh_RockCrushDown_Anim(HSD_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftMh_MS_389_80151018(gobj);
    }
}

void ftMh_RockCrushDown_IASA(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (Player_GetPlayerSlotType(fp->player_id) == 0) {
        ftBossLib_8015BD20(gobj);
    }
}

void ftMh_RockCrushDown_Phys(HSD_GObj* gobj)
{
    ft_80085134(gobj);
}

void ftMh_RockCrushDown_Coll(HSD_GObj* gobj) {}

void ftMh_MS_357_801526D8(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    Fighter_ChangeMotionState(gobj, ftMh_MS_PaperCrush, 0, 0, 1, 0, 0);
    ftAnim_8006EBA4(gobj);
    fp->mv.mh.unk0.x0 = 0;
}

void ftMh_PaperCrush_Anim(HSD_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftMh_MS_389_80151018(gobj);
    }
}

void ftMh_PaperCrush_IASA(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (Player_GetPlayerSlotType(fp->player_id) == 0) {
        ftBossLib_8015BD20(gobj);
    }
}

void ftMh_PaperCrush_Phys(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftMasterHand_SpecialAttrs* da = fp->ft_data->ext_attr;
    ft_80085134(gobj);
    {
        float f = ++fp->mv.mh.unk0.x0;
        if (f > da->xB0 && fp->mv.mh.unk0.x0 < da->xB4) {
            ftBossLib_8015C010(gobj, da->xB8);
        } else {
            fp->self_vel.x = 0;
        }
    }
    ftBossLib_8015C190(gobj);
}
