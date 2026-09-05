#include "ftmasterhandbackairplane3.h"

#include "ftmasterhandwait12.h"
#include "types.h"

#include <dolphin/mtx.h>
#include <melee/ft/fighter.h>
#include <melee/ft/ft_084E.h>
#include <melee/ft/ftanim.h>
#include <melee/ft/ftbosslib.h>
#include <melee/ft/types.h>
#include <melee/pl/player.h>

void ftMh_BackAirplane3_Anim(HSD_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftMh_MS_389_80151018(gobj);
    }
}

void ftMh_BackAirplane3_IASA(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    if (Player_GetPlayerSlotType(fp->player_id) == 0) {
        ftBossLib_8015BD20(gobj);
    }
}

void ftMh_BackAirplane3_Phys(HSD_GObj* gobj)
{
    ft_80085134(gobj);
}

void ftMh_BackAirplane3_Coll(HSD_GObj* gobj) {}

void ftMh_MS_369_80153B90(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftMasterHand_SpecialAttrs* da = fp->ft_data->ext_attr;
    Vec3 pos;

    Fighter_ChangeMotionState(gobj, ftMh_MS_BackPunch, 0, 0, 1, 0, 0);
    ftAnim_8006EBA4(gobj);
    fp->mv.mh.unk0.x0 = da->x6C;
    ftBossLib_8015C208(gobj, &pos);
    fp->cur_pos.x = pos.x;
    fp->cur_pos.y = da->x68;
    fp->self_vel.x = fp->self_vel.y = fp->self_vel.z = 0;
}

void ftMh_BackPunch_Anim(HSD_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        Fighter* fp = GET_FIGHTER(gobj);
        fp->self_vel.x = 0;
        ftMh_MS_389_80151018(gobj);
    }
}

void ftMh_BackPunch_IASA(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (Player_GetPlayerSlotType(fp->player_id) == 0) {
        ftBossLib_8015BD20(gobj);
    }
}

void ftMh_BackPunch_Phys(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (--fp->mv.mh.unk0.x0 > 0) {
        ftMasterHand_SpecialAttrs* da = fp->ft_data->ext_attr;
        ftBossLib_8015BF74(gobj, da->x58);
    } else {
        fp->self_vel.x = 0;
    }
}
