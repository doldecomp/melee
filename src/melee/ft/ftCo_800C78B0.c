#include "ft_0C31.h"
#include "ftcommon.h"

#include <placeholder.h>

#include "ft/fighter.h"
#include "ft/ftanim.h"
#include "ft/ftcoll.h"
#include "ft/types.h"

#include "ftCommon/forward.h"

#include "ftCommon/ftCo_Damage.h"
#include "ftCommon/ftCo_Lift.h"
#include "ftCommon/ftCo_Throw.h"
#include "it/it_26B1.h"
#include "it/items/itlikelike.h"
#include "lb/lbcollision.h"
#include "mp/mpcoll.h"
#include "pl/player.h"

/* 0C7890 */ void fn_800C7890(Fighter_GObj* gobj);

void ftCo_800C78B0(HSD_GObj* gobj, HSD_GObj* owner)
{
    ftCommonData* cd;
    Fighter* fp = GET_FIGHTER(gobj);

    ftCommon_8007DB58(gobj);
    ftCo_8009750C(gobj);
    ftCo_800DD168(gobj);
    Fighter_ChangeMotionState(gobj, ftCo_MS_CaptureLikelike, 0x1080, 0.0f, 1.0f,
                              0.0f, NULL);
    ftAnim_8006EBA4(gobj);
    fp->accessory1_cb = fn_800C7AE0;
    fp->death2_cb = fn_800C7890;
    fp->take_dmg_cb = ftCo_800C7A30;
    fp->x221D_b5 = true;
    fp->mv.co.capturelikelike.x0 = (Item_GObj*) owner;
    fp->mv.co.capturelikelike.x4 = 0;
    ftCommon_8007E2FC(gobj);
    cd = p_ftCommonData;

    {
        f32 tmp1 =
            cd->x74C * (cd->x750 - (f32) (Player_80033BB8(fp->player_id) + 1));
        f32 tmp2 = (cd->x744 * (cd->x748 - Player_GetHandicap(fp->player_id)) +
                    cd->x740);
        tmp2 += tmp1;
        ftCommon_InitGrab(fp, 0, fp->dmg.x1830_percent * cd->x754 + tmp2);
    }
    fp->x1988 = 2;
    fp->invisible = true;
    ftCommon_8007E2F4(fp, 0x1FF);
}

void ftCo_800C7A30(Fighter_GObj* gobj)
{
    it_802DBA68(GET_FIGHTER(gobj)->mv.co.capturelikelike.x0);
}

void ftCo_CaptureLikelike_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    fp->grab_timer -= p_ftCommonData->x758;
    ftCommon_GrabMash(fp, p_ftCommonData->x75C);

    if (*(int*) &fp->mv.co.mushroom.x4 == 0) {
        if (fp->grab_timer <= 0.0f) {
            void it_802DB9F4(Item_GObj*);
            it_802DB9F4(fp->mv.co.capturelikelike.x0);
            *(int*) &fp->mv.co.mushroom.x4 = 1;
        }
    }
}

void ftCo_CaptureLikelike_IASA(Fighter_GObj* gobj) {}

void ftCo_CaptureLikelike_Phys(Fighter_GObj* gobj) {}

void ftCo_CaptureLikelike_Coll(Fighter_GObj* gobj) {}

void fn_800C7AE0(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    it_8026B294(fp->mv.co.captureleadead.x0, &fp->cur_pos);
}

void ftCo_800C7B0C(Fighter_GObj* gobj, Vec3* arg1, Vec3* arg2,
                   lbColl_80008D30_arg1* arg3, f32 arg4)
{
    HitCapsule hit;
    Fighter* fp = GET_FIGHTER(gobj);
    CollData* coll = &fp->coll_data;
    f32 angle;

    fp->coll_data.last_pos = *arg2;
    mpColl_80043670(coll);
    angle = arg4;
    coll->cur_pos = *arg1;
    mpColl_800471F8(coll);
    fp->cur_pos = coll->cur_pos;
    lbColl_80008D30(&hit, arg3);
    ftColl_800788D4(gobj);
    if (angle < 0.0f) {
        angle += 360.0f;
    }
    angle = fp->facing_dir < 0.0f ? angle : 180.0f - angle;
    fp->dmg.kb_applied = ftColl_80079EA8(fp, &hit, hit.unk_count);
    fp->dmg.x1848_kb_angle = angle;
    fp->dmg.facing_dir_1 = fp->facing_dir;
    fp->dmg.x184c_damaged_hurtbox = 0;
    fp->dmg.x1854_collpos = fp->cur_pos;
    fp->dmg.x1860_element = hit.element;
    Fighter_UnkTakeDamage_8006CC30(fp, hit.damage);
    ftCo_Damage_CalcKnockback(fp);
    ftCo_8008E908(gobj, 0.0f);
}

void ftCo_800C7C60(Fighter_GObj* gobj, int damage_amount)
{
    Fighter_TakeDamage_8006CC7C(GET_FIGHTER(gobj), damage_amount);
}
