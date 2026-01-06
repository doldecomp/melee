#include "ftCo_Shouldered.h"

#include "ftCo_Damage.h"

#include <placeholder.h>
#include <platform.h>

#include "ft/fighter.h"
#include "ft/ftanim.h"
#include "ft/ftcoll.h"
#include "ft/ftcommon.h"
#include "ft/ftparts.h"
#include "ft/types.h"
#include "ftCaptain/types.h"
#include "ftCommon/ftCo_Attack100.h"
#include "ftCommon/ftCo_CaptureCut.h"
#include "ftCommon/ftCo_Throw.h"
#include "ftCommon/types.h"

#include "lb/forward.h"

#include "lb/lb_00B0.h"

#include <common_structs.h>
#include <dolphin/mtx.h>

#pragma force_active on

float const ftCo_804D8750 = 0;
float const ftCo_804D8754 = 1;
double const ftCo_804D8758 = S32_TO_F32;

/* 09C744 */ static void ftCo_8009C744(Fighter_GObj* gobj);

void ftCo_8009C5A4(Fighter_GObj* gobj, FtMotionId msid)
{
    u8 _[8] = { 0 };
    Fighter* fp = gobj->user_data;
    if (fp->motion_id != msid || msid != ftCo_MS_ShoulderedWait) {
        Fighter_ChangeMotionState(
            gobj, msid, fp->x2222_b6 ? Ft_MF_FreezeState : Ft_MF_None, 0, 1, 0,
            fp->victim_gobj);
        ftCommon_8007E2FC(gobj);
        ftCommon_8007E2F4(fp, 0x1FF);
        fp->accessory1_cb = ftCo_800DB464;
    }
}

void ftCo_8009C640(Fighter_GObj* gobj, FtMotionId msid)
{
    Fighter* fp = gobj->user_data;
    ftCommon_InitGrab(fp, 0,
                      (int) (fp->dmg.x1830_percent * p_ftCommonData->x4A0 +
                             p_ftCommonData->x4A4));
    fp->mv.co.shouldered.x0 = 0;
    fp->mv.co.shouldered.x4 = 0;
    ftCo_8009C5A4(gobj, msid);
}

void ftCo_8009C744(Fighter_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    Fighter_GObj* vic_gobj = fp->victim_gobj;
    Fighter* vic_fp = vic_gobj->user_data;
    Vec3 pos;
    u8 _[12] = { 0 };
    HitCapsule* hit = &vic_fp->xDF4[1];
    ftCo_800DC920(vic_gobj, gobj);
    lb_8000B1CC(fp->parts[ftParts_GetBoneIndex(fp, FtPart_XRotN)].joint, NULL,
                &pos);
    fp->dmg.kb_applied = ftColl_80079C70(fp, vic_fp, hit, hit->unk_count);
    fp->dmg.x1848_kb_angle = hit->kb_angle;
    fp->dmg.facing_dir_1 = -vic_fp->facing_dir;
    fp->dmg.x184c_damaged_hurtbox = 1;
    fp->dmg.x1854_collpos = pos;
    fp->dmg.x1860_element = hit->element;
    // ftColl_80078710(gobj);
    Fighter_UnkTakeDamage_8006CC30(fp, hit->damage);
    ftCo_Damage_CalcKnockback(fp);
    ftCo_8008E908(gobj, 0);
}

static inline float inlineA0(Fighter_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    return fp->ground_or_air == GA_Ground
               ? p_ftCommonData->x4A8
               : p_ftCommonData->x4A8 * p_ftCommonData->x4AC;
}

void ftCo_Shouldered_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    fp->mv.co.shouldered.x4 = ftCommon_GrabMash(fp, inlineA0(fp->victim_gobj));
    if (fp->grab_timer <= 0) {
        HitCapsule* hit;
        Fighter_GObj* gobj1 = fp->victim_gobj;
        Fighter* fp1 = gobj1->user_data;
        Fighter_GObj* gobj2 = fp1->victim_gobj;
        {
            Fighter* fp1 = gobj1->user_data;
            Fighter* fp2 = gobj2->user_data;
            Vec3 pos;
            hit = &fp2->xDF4[1];
            lb_8000B1CC(
                fp1->parts[(ftParts_GetBoneIndex(fp1, FtPart_TransN2))].joint,
                NULL, &pos);
            fp1->dmg.kb_applied =
                ftColl_80079C70(fp1, fp2, hit, hit->unk_count);
            fp1->dmg.x1848_kb_angle = hit->kb_angle;
            fp1->dmg.facing_dir_1 = fp1->facing_dir;
            fp1->dmg.x184c_damaged_hurtbox = 1;
            fp2->dmg.x1854_collpos = pos;
            fp1->dmg.x1860_element = hit->element;
            // ftColl_80078710(gobj);
            Fighter_UnkTakeDamage_8006CC30(fp1, hit->damage);
            ftCo_Damage_CalcKnockback(fp1);
            ftCo_8008E908(gobj1, 0);
        }
        ftCo_8009C744(gobj);
        return;
    }
    if (fp->mv.ca.specials.grav) {
        fp->mv.ca.specials.grav -= 1;
    }
    if (fp->mv.co.shouldered.x0 <= 0 && !fp->mv.co.shouldered.x4) {
        ftAnim_SetAnimRate(gobj, 1);
        fp->mv.co.shouldered.x0 = 0;
    }
    if (fp->mv.co.shouldered.x0 <= 0 && fp->mv.co.shouldered.x4 &&
        fp->motion_id == ftCo_MS_ShoulderedWait)
    {
        fp->mv.co.shouldered.x0 = p_ftCommonData->x3B0;
        ftAnim_SetAnimRate(gobj, p_ftCommonData->shouldered_anim_rate);
    }
}

void ftCo_Shouldered_IASA(Fighter_GObj* gobj) {}

void ftCo_Shouldered_Phys(Fighter_GObj* gobj) {}

void ftCo_Shouldered_Coll(Fighter_GObj* gobj) {}
