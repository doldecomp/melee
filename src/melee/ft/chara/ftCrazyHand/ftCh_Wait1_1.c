#include "ftCh_Wait1_1.h"

#include "ftCh_Init.h"
#include "types.h"

#include <placeholder.h>
#include <platform.h>

#include "baselib/forward.h"

#include "ft/fighter.h"
#include "ft/ftbosslib.h"
#include "ft/inlines.h"
#include "ft/types.h"
#include "ftCrazyHand/ftCh_TagCancel.h"
#include "ftMasterHand/types.h"
#include "pl/player.h"

#include <common_structs.h>
#include <dolphin/mtx.h>
#include <MetroTRK/intrinsics.h>

/// @todo Figure out how to use #GET_JOBJ instead.
static inline HSD_JObj* get_jobj(HSD_GObj* gobj)
{
    return gobj->hsd_obj;
}

void fn_80159AA4(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    HSD_JObj* jobj = get_jobj(gobj);

    ftCrazyHand_DatAttrs* da = fp->ft_data->ext_attr;
    Vec3 pos;
    Vec3 scl;

    u8 _[4];

    Fighter_ChangeMotionState(gobj, 0x175, 0, 0, 1, 0, 0);
    ftAnim_8006EBA4(gobj);
    ftBossLib_8015C208(gobj, &pos);
    fp->cur_pos.x = pos.x;
    fp->cur_pos.y = da->xF4;

    fp->self_vel.z = 0;
    fp->self_vel.y = 0;
    fp->self_vel.x = 0;

    fp->mv.ch.unk0.x0 = da->xF8;
    fp->mv.ch.ch_backcrush.x5C = da->x100;

    HSD_JObjGetScale(jobj, &scl);
    fp->mv.ch.ch_backcrush.x50.x = scl.x;
    fp->mv.ch.ch_backcrush.x50.y = scl.y;
    fp->mv.ch.ch_backcrush.x50.z = scl.z;

    fp->mv.ch.ch_backcrush.x44.x = scl.x - da->xFC;
    fp->mv.ch.ch_backcrush.x44.y = scl.y - da->xFC;
    fp->mv.ch.ch_backcrush.x44.z = scl.z - da->xFC;

    fp->mv.ch.ch_backcrush.x44.x /= da->x100;
    fp->mv.ch.ch_backcrush.x44.y /= da->x100;
    fp->mv.ch.ch_backcrush.x44.z /= da->x100;

    scl.x = da->xFC;
    scl.y = da->xFC;
    scl.z = da->xFC;
    HSD_JObjSetScale(jobj, &scl);

    fp->cmd_vars[0] = 1;
}

void ftCh_Wait1_1_Anim(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (fp->cmd_vars[0] != 0) {
        Vec3 scl;
        /// @todo #GET_JOBJ
        HSD_JObj* jobj = get_jobj(gobj);
        if (--fp->mv.ch.ch_backcrush.x5C < 0) {
            fp->cmd_vars[0] = 0;
            scl.x = fp->mv.ch.ch_backcrush.x50.x;
            scl.y = fp->mv.ch.ch_backcrush.x50.y;
            scl.z = fp->mv.ch.ch_backcrush.x50.z;
        } else {
            HSD_JObjGetScale(jobj, &scl);
            scl.x += fp->mv.ch.ch_backcrush.x44.x;
            scl.y += fp->mv.ch.ch_backcrush.x44.y;
            scl.z += fp->mv.ch.ch_backcrush.x44.z;
        }
        HSD_JObjSetScale(jobj, &scl);
    }
    if (!ftAnim_IsFramesRemaining(gobj)) {
        Fighter* fp = GET_FIGHTER(gobj);
        fp->self_vel.x = 0;
        ftCh_GrabUnk1_8015BC88(gobj);
    }
}

void ftCh_Wait1_1_IASA(HSD_GObj* gobj)
{
    Fighter* ft = GET_FIGHTER(gobj);
    if (Player_GetPlayerSlotType(ft->player_id) == Gm_PKind_Human) {
        ftBossLib_8015BD20(gobj);
    }
}

void ftCh_Wait1_1_Phys(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (--fp->mv.ch.unk0.x0 > 0) {
        ftCrazyHand_DatAttrs* da = fp->ft_data->ext_attr;
        ftBossLib_8015BF74(gobj, da->xDC);
    } else {
        fp->self_vel.x = 0;
    }
    ftBossLib_8015C190(gobj);
}

void ftCh_Wait1_1_Coll(HSD_GObj* gobj) {}
