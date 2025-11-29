#include "ftCo_CaptureCut.h"

#include "ftCo_Throw.h"
#include "placeholder.h"
#include "platform.h"

#include "ft/fighter.h"

#include "ft/forward.h"

#include "ft/ft_081B.h"
#include "ft/ftcommon.h"
#include "ft/inlines.h"
#include "ft/types.h"

#include "ftCommon/forward.h"

#include <melee/cm/camera.h>
#include <melee/ef/efsync.h>
#include <melee/ft/chara/ftCommon/ftCo_Attack1.h>
#include <melee/ft/chara/ftCommon/ftCo_AttackHi3.h>
#include <melee/ft/chara/ftCommon/ftCo_AttackHi4.h>
#include <melee/ft/chara/ftCommon/ftCo_AttackLw3.h>
#include <melee/ft/chara/ftCommon/ftCo_AttackLw4.h>
#include <melee/ft/chara/ftCommon/ftCo_AttackS3.h>
#include <melee/ft/chara/ftCommon/ftCo_AttackS4.h>
#include <melee/ft/chara/ftCommon/ftCo_Damage.h>
#include <melee/ft/chara/ftCommon/ftCo_DamageIce.h>
#include <melee/ft/chara/ftCommon/ftCo_Escape.h>
#include <melee/ft/chara/ftCommon/ftCo_FallSpecial.h>
#include <melee/ft/chara/ftCommon/ftCo_Guard.h>
#include <melee/ft/chara/ftCommon/ftCo_Lift.h>
#include <melee/ft/chara/ftCommon/ftCo_SpecialS.h>
#include <melee/ft/ft_0877.h>
#include <melee/ft/ft_0881.h>
#include <melee/ft/ft_0CDD.h>
#include <melee/ft/ftcamera.h>
#include <melee/ft/ftchangeparam.h>
#include <melee/ft/ftcoll.h>
#include <melee/ft/ftlib.h>
#include <melee/ft/ftmaterial.h>
#include <melee/ft/ftmetal.h>
#include <melee/ft/ftparts.h>
#include <melee/gm/gm_unsplit.h>
#include <melee/gr/stage.h>
#include <melee/it/item.h>
#include <melee/it/items/it_2E5A.h>
#include <melee/it/items/itkinoko.h>
#include <melee/lb/lb_00B0.h>
#include <melee/mp/mpcoll.h>
#include <melee/mp/mplib.h>
#include <melee/pl/pl_040D.h>
#include <melee/pl/player.h>
#include <melee/pl/plbonuslib.h>
#include <melee/pl/plstale.h>

void ftCo_CaptureCut_Enter(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    ftCo_800DC920(fp->victim_gobj, gobj);
    if (fp->ground_or_air == GA_Ground) {
        fp->gr_vel = -fp->facing_dir * p_ftCommonData->x370;
    } else {
        fp->self_vel.x = -fp->facing_dir * p_ftCommonData->x370;
    }
    Fighter_ChangeMotionState(gobj, ftCo_MS_CaptureCut, Ft_MF_None, 0.0F, 1.0F,
                              0.0F, NULL);
}

void ftCo_CaptureCut_Anim(Fighter_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftCommon_8007D92C(gobj);
    }
}

void ftCo_CaptureCut_IASA(Fighter_GObj* gobj) {}

void ftCo_CaptureCut_Phys(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    PAD_STACK(8);

    if (fp->ground_or_air == GA_Ground) {
        ftCommon_ApplyFrictionGround(fp, p_ftCommonData->x36C * fp->co_attrs.gr_friction);
        ftCommon_ApplyGroundMovement(gobj);
        return;
    }

    ft_80084DB0(gobj);
}

void ftCo_CaptureCut_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->ground_or_air == GA_Ground) {
        ft_800841B8(gobj, fn_800DC8D8);
        return;
    }
    ft_80083910(gobj, fn_800DC8FC);
}

void fn_800DC8D8(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCommon_8007D5D4(fp);
}

void fn_800DC8FC(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCommon_8007D7FC(fp);
}

void ftCo_800DC920(Fighter_GObj* arg0, Fighter_GObj* gobj)
{
    Vec3 sp4C;
    f32 sp48;
    Vec3 sp3C;
    Vec3 tmp;

    Fighter* var_r31;
    Fighter* var_r30;

    HSD_JObj* temp_r29;
    bool var_r29;
    CollData* temp_r28_2;
    HSD_JObj* temp_r28;
    int temp_r3_2;
    bool var_r3_3;

    var_r31 = GET_FIGHTER(arg0);
    Fighter_UnkSetFlag_8006CFBC(arg0);
    Fighter_UnkSetFlag_8006CFBC(gobj);
    if (var_r31->x221B_b7) {
        var_r30 = var_r31;
        var_r31 = GET_FIGHTER(gobj);
    } else {
        var_r30 = GET_FIGHTER(gobj);
    }
    var_r31->x1A5C = NULL;
    var_r29 = false;
    var_r31->victim_gobj = NULL;
    var_r31->x221B_b5 = false;
    var_r31->x221B_b7 = false;
    if (var_r30->x2226_b2) {
        if (var_r31->kind == FTKIND_KIRBY &&
            (var_r31->motion_id == ftKb_MS_SpecialNCapture0 ||
             var_r31->motion_id == ftKb_MS_SpecialAirNCapture0))
        {
            Fighter_UpdateModelScale(var_r30->gobj);
            var_r30->x2226_b2 = false;
            sp4C = var_r30->cur_pos;
        } else if (var_r30->x2226_b2) {
            temp_r28 =
                var_r30->parts[ftParts_GetBoneIndex(var_r30, FtPart_XRotN)]
                    .joint;
            lb_8000B1CC(temp_r28, NULL, &sp4C);
            sp4C.x += var_r30->facing_dir *
                      (var_r30->x1A70.z * var_r30->x34_scale.y);
            sp4C.y += var_r30->x1A70.y * var_r30->x34_scale.y;
            sp4C.z = 0.0F;
            lb_8000C390(temp_r28);
            var_r30->x2226_b2 = false;

            HSD_JObjSetTranslate(temp_r28, &var_r30->x2174);
        }
        if (mpLib_80054ED8(var_r31->coll_data.floor.index) != 0) {
            temp_r3_2 = mpLib_8005199C_Floor(&sp4C, -1, -1);
            if (temp_r3_2 != -1) {
                int tmp = var_r31->coll_data.floor.index;
                if (mpLinesConnected(temp_r3_2, tmp)) {
                    var_r30->coll_data.floor.index = temp_r3_2;
                    mpLib_8004DD90_Floor(temp_r3_2, &sp4C, &sp48, 0, NULL);
                    if (sp48 >= p_ftCommonData->x3BC) {
                        var_r30->cur_pos.x = sp4C.x;
                        var_r30->cur_pos.y = sp4C.y + sp48;
                        var_r30->cur_pos.z = sp4C.z;
                        mpColl_80043680(&var_r30->coll_data,
                                        &var_r30->cur_pos);
                        var_r29 = true;
                    }
                }
            }
        }
        if (!var_r29) {
            temp_r28_2 = &var_r30->coll_data;
            temp_r29 = GET_JOBJ(var_r30->gobj);
            tmp.x = 0;
            tmp.y = 0.5F * (var_r31->coll_data.ecb.top.y +
                            var_r31->coll_data.ecb.bottom.y);
            tmp.z = 0;
            sp3C.x = var_r31->cur_pos.x + tmp.x;
            sp3C.y = var_r31->cur_pos.y + tmp.y;
            sp3C.z = var_r31->cur_pos.z + tmp.z;

            temp_r28_2->last_pos = sp3C;
            mpColl_80043670(temp_r28_2);
            temp_r28_2->cur_pos = sp4C;

            HSD_JObjSetTranslate(temp_r29, &sp4C);

            if (var_r30->ground_or_air == GA_Ground) {
                var_r3_3 = mpColl_80048654(temp_r28_2);
            } else {
                ftCommon_UnlockECB(var_r30);
                var_r3_3 = mpColl_800477E0(temp_r28_2);
            }
            if (var_r3_3) {
                if (var_r30->ground_or_air != GA_Ground) {
                    ftCommon_8007D7FC(var_r30);
                }
                var_r30->cur_pos = temp_r28_2->cur_pos;
            } else {
                if (var_r30->ground_or_air != GA_Air) {
                    ftCommon_8007D5D4(var_r30);
                }
                var_r30->cur_pos = sp4C;
            }
            HSD_JObjSetTranslate(temp_r29, &var_r30->cur_pos);
        }
    }
    var_r30->x1A5C = NULL;
    var_r30->victim_gobj = NULL;
    var_r30->x221B_b5 = false;
    var_r30->x221B_b7 = false;
}

void ftCo_800DCE34(Fighter_GObj* gobj0, Fighter_GObj* gobj1)
{
    Fighter* fp1 = GET_FIGHTER(gobj1);
    ftCo_800DC920(gobj0, gobj1);
    if (fp1->x221B_b7) {
        Fighter* fp0 = GET_FIGHTER(gobj0);
        HSD_JObjSetTranslate(GET_JOBJ(gobj0), &fp0->cur_pos);
    } else {
        HSD_JObjSetTranslate(GET_JOBJ(gobj1), &fp1->cur_pos);
    }
}

void ftCo_800DCFD4(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    Fighter* victim_fp = GET_FIGHTER(fp->victim_gobj);
    HitCapsule* hit = &victim_fp->xDF4[1];
    Vec3 sp18;

    if (fp->x1988 != 0) {
        ftColl_8007B62C(gobj, 0);
    }
    ftCommon_8007D5D4(fp);
    ftColl_8007891C(fp->victim_gobj, gobj, hit->damage);

    lb_8000B1CC(fp->parts[ftParts_GetBoneIndex(fp, FtPart_XRotN)].joint, NULL,
                &sp18);
    fp->dmg.kb_applied = ftColl_80079C70(fp, victim_fp, hit, hit->unk_count);
    fp->dmg.x1848_kb_angle = hit->kb_angle;
    fp->dmg.facing_dir_1 = -victim_fp->facing_dir;
    fp->dmg.x184c_damaged_hurtbox = 1;
    fp->dmg.x1854_collpos = sp18;
    fp->dmg.x1860_element = hit->element;

    ftColl_80078710(fp->victim_gobj, gobj, &fp->dmg.facing_dir_1);
    Fighter_UnkTakeDamage_8006CC30(fp, hit->damage);
    ftCo_Damage_CalcKnockback(fp);
    ftCo_8008E908(gobj, 0.0F);
}
