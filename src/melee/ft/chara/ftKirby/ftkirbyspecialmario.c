#include "ftkirby.h"
#include "types.h"

#include "hsd/forward.h"

#include "ef/efsync.h"
#include "ft/chara/ftCommon/ftCo_Wait.h"
#include "ft/fighter.h"

#include "ft/forward.h"

#include "ft/ft_081B.h"
#include "ft/ft_084E.h"
#include "ft/ft_0892.h"
#include "ft/ftanim.h"
#include "ft/ftcommon.h"
#include "ft/ftparts.h"
#include "ft/inlines.h"
#include "ft/types.h"
#include "ftCommon/ftCo_Fall.h"

#include "ftKirby/forward.h"

#include "it/items/itdrmariopill.h"
#include "it/items/itmariofireball.h"
#include "lb/lb_00B0.h"

#include <stddef.h>
#include <hsd/gobj.h>
#include <hsd/random.h>

void fn_800F9260(HSD_GObj*);

void ftKb_SpecialN_800F9110(Fighter_GObj* gobj)
{
    int new_var;
    Fighter* fp = GET_FIGHTER(gobj);
    ftKirby_MotionState msid = ftKb_MS_MrSpecialN;
    fp->cmd_vars[0] = 0;
    fp->throw_flags = 0;
    {
        Fighter* fp = GET_FIGHTER(gobj);
        if (fp->u.kb.hat.kind != FTKIND_MARIO) {
            msid = (new_var = 0x200);
        }
    }
    Fighter_ChangeMotionState(gobj, msid, 0, 0.0f, 1.0f, 0.0f, NULL);
    ftAnim_8006EBA4(gobj);
    fp->accessory4_cb = fn_800F9260;
}

void ftKb_MrSpecialN_Anim(Fighter_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ft_8008A2BC(gobj);
    }
}

void ftKb_MrSpecialN_IASA(Fighter_GObj* gobj)
{
    Fighter* ft = GET_FIGHTER(gobj);
    if (ft->cmd_vars[0] != 0) {
        ftCo_Wait_IASA(gobj);
    }
}

void ftKb_MrSpecialN_Phys(Fighter_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftKb_MrSpecialN_Coll(Fighter_GObj* gobj)
{
    if (ft_80082708(gobj) == GA_Ground) {
        ftKb_SpecialNLg_800F951C(gobj);
    }
}

static inline s32 fn_800F9260_inline(HSD_GObj* gobj)
{
    Fighter* fp2;
    s32 candidates[9];
    s32 count;
    s32 i;
    s32 pick;

    fp2 = GET_FIGHTER(gobj);
    for (i = count = 0; i < 9; i++) {
        if (i != fp2->u.kb.x68 && i != fp2->u.kb.x6C) {
            candidates[count] = i;
            count++;
        }
    }
    pick = candidates[HSD_Randi(count)];
    fp2->u.kb.x6C = fp2->u.kb.x68;
    fp2->u.kb.x68 = pick;
    return pick;
}

static inline HSD_JObj* fn_800F9260_GetPartJoint(s32 bone, Fighter* fp)
{
    return fp->parts[bone].joint;
}
static inline s32 fn_800F9260_GetLHandBone(Fighter* fp)
{
    return ftParts_GetBoneIndex(fp, FtPart_LHandN);
}
void fn_800F9260(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    Vec3 sp44;
    s32 bone;
    s32 pick;
    HSD_JObj* joint;

    if (fp->u.kb.hat.kind != FTKIND_KIRBY) {
        if (ftCheckThrowB0(fp)) {
            lb_8000B1CC(
                fp->parts[ftParts_GetBoneIndex(fp, FtPart_LHandN)].joint, NULL,
                &sp44);
            if (fp->u.kb.hat.kind == FTKIND_MARIO) {
                it_8029B6F8((Item_GObj*) gobj, &sp44, It_Kind_Kirby_MarioFire,
                            fp->facing_dir);
                bone = fn_800F9260_GetLHandBone(fp);
                joint = fn_800F9260_GetPartJoint(bone, fp);
                efSync_Spawn(0x49F, gobj, joint, &fp->facing_dir);
                return;
            }

            pick = fn_800F9260_inline(gobj);

            itDrMarioPill_Spawn((Item_GObj*) gobj, &sp44, pick,
                                It_Kind_Kirby_DrMarioVitamin, fp->facing_dir);
        }
    }
}

void ftKb_SpecialNMr_800F93CC(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    s32 msid = ftKb_MS_MrSpecialAirN;
    fp->cmd_vars[0] = 0;
    fp->throw_flags = 0;
    if (GET_FIGHTER(gobj)->u.kb.hat.kind != FTKIND_MARIO) {
        msid = ftKb_MS_DrSpecialAirN;
    }
    Fighter_ChangeMotionState(gobj, msid, 0, 0.0F, 1.0F, 0.0F, NULL);
    ftAnim_8006EBA4(gobj);
    fp->accessory4_cb = fn_800F9260;
}

void ftKb_MrSpecialAirN_Anim(Fighter_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftCo_Fall_Enter(gobj);
    }
}

void ftKb_MrSpecialAirN_IASA(Fighter_GObj* gobj)
{
    Fighter* ft = GET_FIGHTER(gobj);
    if (ft->cmd_vars[0] != 0) {
        ftCo_Fall_IASA_Inner(gobj);
    }
}

void ftKb_MrSpecialAirN_Phys(Fighter_GObj* gobj)
{
    ft_80084DB0(gobj);
}

void ftKb_MrSpecialAirN_Coll(Fighter_GObj* gobj)
{
    if (ft_80081D0C(gobj) != GA_Ground) {
        ftKb_SpecialNLg_800F9598(gobj);
    }
}

void ftKb_SpecialNLg_800F951C(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    Fighter* fp2;
    s32 motion_id;
    f32 anim_frame;

    ftCommon_8007D5D4(fp);

    fp2 = gobj->user_data;
    motion_id = 0x190;
    anim_frame = fp->cur_anim_frame;

    if (fp2->u.kb.hat.kind != 0) {
        motion_id = 0x201;
    }

    Fighter_ChangeMotionState(gobj, motion_id, 0x5000, anim_frame, 1.0F, 0.0F,
                              NULL);
    fp->accessory4_cb = fn_800F9260;
}

void ftKb_SpecialNLg_800F9598(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    Fighter* fp2;
    s32 motion_id;
    f32 anim_frame;

    ftCommon_8007D7FC(fp);

    fp2 = gobj->user_data;
    motion_id = 0x18F;
    anim_frame = fp->cur_anim_frame;

    if (fp2->u.kb.hat.kind != 0) {
        motion_id = 0x200;
    }

    Fighter_ChangeMotionState(gobj, motion_id, 0x5000, anim_frame, 1.0f, 0.0f,
                              NULL);
    fp->accessory4_cb = fn_800F9260;
}
