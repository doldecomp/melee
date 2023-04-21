#include "ftMh_MS_369.h"

#include "ftMh_MS_389.h"

#include "ft/ft_081B.h"
#include "ft/ftbosslib.h"
#include "ft/inlines.h"

#include <dolphin/mtx/types.h>

void ftMh_MS_369_Anim(HSD_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftMh_MS_389_80151018(gobj);
    }
}

void ftMh_MS_369_IASA(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    if (Player_GetPlayerSlotType(fp->xC_playerID) == 0) {
        ftBossLib_8015BD20(gobj);
    }
}

void ftMh_MS_369_Phys(HSD_GObj* gobj)
{
    ft_80085134(gobj);
}

void ftMh_MS_369_Coll(HSD_GObj* gobj) {}

void ftMh_MS_369_80153B90(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftMasterHand_SpecialAttrs* attr = fp->ft_data->ext_attr;
    Vec3 pos;

    Fighter_ChangeMotionState(gobj, ftMh_MS_Ram_StartMotion, 0, 0, 0, 1, 0);
    ftAnim_8006EBA4(gobj);
    fp->mv.mh.unk0.x0 = attr->x6C;
    ftBossLib_8015C208(gobj, &pos);
    fp->cur_pos.x = pos.x;
    fp->cur_pos.y = attr->x68;
    fp->x80_self_vel.x = fp->x80_self_vel.y = fp->x80_self_vel.z = 0;
}

void ftMh_MS_370_Anim(HSD_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        Fighter* fp = GET_FIGHTER(gobj);
        fp->x80_self_vel.x = 0;
        ftMh_MS_389_80151018(gobj);
    }
}

void ftMh_MS_370_IASA(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (Player_GetPlayerSlotType(fp->xC_playerID) == 0) {
        ftBossLib_8015BD20(gobj);
    }
}

void ftMh_MS_370_Phys(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (--fp->mv.mh.unk0.x0 > 0) {
        ftMasterHand_SpecialAttrs* attr = fp->ft_data->ext_attr;
        ftBossLib_8015BF74(gobj, attr->x58);
    } else {
        fp->x80_self_vel.x = 0;
    }
}
