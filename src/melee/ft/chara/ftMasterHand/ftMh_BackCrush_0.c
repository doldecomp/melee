#include "ftMh_BackCrush_0.h"

#include "ftMh_Wait1_2.h"

#include <platform.h>

#include "ft/fighter.h"
#include "ft/ftanim.h"
#include "ft/ftbosslib.h"
#include "ft/types.h"
#include "ftMasterHand/types.h"
#include "pl/player.h"

#include <dolphin/mtx.h>
#include <baselib/jobj.h>

void ftMh_BackPunch_Coll(HSD_GObj* gobj) {}

/// @todo Figure out how to use #GET_JOBJ instead.
static inline HSD_JObj* get_jobj(HSD_GObj* gobj)
{
    return gobj->hsd_obj;
}

void ftMh_MS_370_80153D2C(HSD_GObj* gobj)
{
    /// @todo #GET_FIGHTER and #GET_JOBJ both cause regswaps here,
    ///       but they probably shouldn't.
    Fighter* fp = gobj->user_data;
    HSD_JObj* jobj = get_jobj(gobj);

    ftMasterHand_SpecialAttrs* da = fp->ft_data->ext_attr;
    Vec3 pos;
    Vec3 scl;

    u8 _[4];

    Fighter_ChangeMotionState(gobj, ftMh_MS_BackCrush, 0, 0, 1, 0, 0);
    ftAnim_8006EBA4(gobj);
    ftBossLib_8015C208(gobj, &pos);
    fp->cur_pos.x = pos.x;
    fp->cur_pos.y = da->x70;

    fp->self_vel.z = 0;
    fp->self_vel.y = 0;
    fp->self_vel.x = 0;

    fp->mv.mh.unk0.x0 = da->x74;
    fp->mv.mh.unk0.x70 = da->x7C;

    HSD_JObjGetScale(jobj, &scl);
    fp->mv.mh.unk0.x64.x = scl.x;
    fp->mv.mh.unk0.x64.y = scl.y;
    fp->mv.mh.unk0.x64.z = scl.z;

    fp->mv.mh.unk0.x58.x = scl.x - da->x78;
    fp->mv.mh.unk0.x58.y = scl.y - da->x78;
    fp->mv.mh.unk0.x58.z = scl.z - da->x78;

    fp->mv.mh.unk0.x58.x /= da->x7C;
    fp->mv.mh.unk0.x58.y /= da->x7C;
    fp->mv.mh.unk0.x58.z /= da->x7C;

    scl.x = da->x78;
    scl.y = da->x78;
    scl.z = da->x78;
    HSD_JObjSetScale(jobj, &scl);

    fp->cmd_vars[0] = 1;
}

void ftMh_BackCrush_Anim(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (fp->cmd_vars[0] != 0) {
        Vec3 scl;
        /// @todo #GET_JOBJ
        HSD_JObj* jobj = get_jobj(gobj);
        if (--fp->mv.mh.unk0.x70 < 0) {
            fp->cmd_vars[0] = 0;
            scl.x = fp->mv.mh.unk0.x64.x;
            scl.y = fp->mv.mh.unk0.x64.y;
            scl.z = fp->mv.mh.unk0.x64.z;
        } else {
            HSD_JObjGetScale(jobj, &scl);
            scl.x += fp->mv.mh.unk0.x58.x;
            scl.y += fp->mv.mh.unk0.x58.y;
            scl.z += fp->mv.mh.unk0.x58.z;
        }
        HSD_JObjSetScale(jobj, &scl);
    }
    if (!ftAnim_IsFramesRemaining(gobj)) {
        Fighter* fp = GET_FIGHTER(gobj);
        fp->self_vel.x = 0;
        ftMh_MS_389_80151018(gobj);
    }
}

void ftMh_BackCrush_IASA(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (Player_GetPlayerSlotType(fp->player_id) == 0) {
        ftBossLib_8015BD20(gobj);
    }
}

void ftMh_BackCrush_Phys(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    u8 _[8];

    if (--fp->mv.mh.unk0.x0 > 0) {
        ftMasterHand_SpecialAttrs* da = fp->ft_data->ext_attr;
        ftBossLib_8015BF74(gobj, da->x58);
    } else {
        fp->self_vel.x = 0;
    }
    ftBossLib_8015C190(gobj);
}
