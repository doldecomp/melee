#include "ftCo_Bury.h"

#include "ftCo_AirCatch.h"
#include "ftCo_AttackAir.h"
#include "ftCo_BarrelWait.h"
#include "ftCo_CaptureCut.h"
#include "ftCo_Damage.h"
#include "ftCo_EscapeAir.h"
#include "ftCo_HammerJump.h"
#include "ftCo_HammerWait.h"
#include "ftCo_ItemThrow.h"
#include "ftCo_Lift.h"
#include "ftCo_SpecialAir.h"
#include "ftCo_Throw.h"

#include <placeholder.h>
#include <platform.h>

#include "ef/efsync.h"
#include "ft/fighter.h"

#include "ft/forward.h"

#include "ft/ft_081B.h"
#include "ftCommon/ftCo_Attack100.h"
#include "ft/ftanim.h"
#include "ft/ftcoll.h"
#include "ft/ftcommon.h"
#include "ft/ftparts.h"
#include "ft/types.h"
#include "ftCaptain/types.h"

#include "ftCommon/forward.h"

#include "ftCommon/ftCo_Fall.h"
#include "ftCommon/ftCo_JumpAerial.h"
#include "ftCommon/types.h"
#include "gr/ground.h"

#include "lb/forward.h"

#include "lb/lb_00B0.h"
#include "lb/lbcollision.h"
#include "mp/mplib.h"
#include "pl/player.h"
#include "pl/plbonuslib.h"

#include <common_structs.h>
#include <trigf.h>
#include <dolphin/mtx.h>
#include <baselib/gobj.h>
#include <baselib/jobj.h>

void ftCo_800C0874(Fighter_GObj* gobj, UNK_T arg1, ftCommon_BuryType arg2)
{
    switch (arg2) {
    case BuryType_Unk2:
        ftCo_8009EB18(gobj);
    }
}

void ftCo_800C08A0(Fighter_GObj* gobj, Fighter_GObj* arg1, DynamicsDesc* arg2,
                   ftCommon_BuryType arg3)
{
    float f;
    HitCapsule hit;
    FighterHurtCapsule* p_hurt;
    Fighter* fp = GET_FIGHTER(gobj);
    f = ftColl_800765F0(fp, NULL, arg2->count);
    switch (arg3) {
    case BuryType_Unk2:
        break;
    case BuryType_Unk1:
        fp->bury_timer_1 = p_ftCommonData->bury_timer_unk1;
        break;
    case BuryType_Unk3:
        fp->bury_timer_2 = p_ftCommonData->bury_timer_unk3;
        break;
    }
    if (ftColl_80076640(fp, &f) != 0) {
        p_hurt = &fp->hurt_capsules[0];
        ftColl_80076764(3, arg3, arg1, arg2, fp, p_hurt);

        /// @todo Eliminate cast
        lbColl_80008D30(&hit, (lbColl_80008D30_arg1*) arg2);

        ftColl_80078384(fp, p_hurt, &hit);
    }
    pl_8003EC30(fp->player_id, fp->x221F_b4, arg3, f);
}

void ftCo_800C09B4(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->bury_stage_kind = stage_info.internal_stage_id;
    fp->bury_timer_1 = 0;
    switch (fp->bury_stage_kind) {
    case OLDKONGO:
    case KONGO:
        fp->bury_timer_2 = 0;
        return;
    case STAGEKIND_UNK39:
    case STAGEKIND_UNK32:
    case ZEBES:
        fp->bury_timer_2 = 0;
        return;
    }
}

bool ftCo_800C0A28(Fighter_GObj* gobj, UNK_T arg1, ftCommon_BuryType arg2)
{
    Fighter* fp = GET_FIGHTER(gobj);
    switch (arg2) {
    case BuryType_Unk2: {
        if (fp->bury_timer_2 != 0 || fp->motion_id == ftCo_MS_BarrelWait ||
            fp->x1A6A & 0x20 || fp->x2224_b2)
        {
            return false;
        }
        break;
    }
    case BuryType_Unk3: {
        if (fp->bury_timer_2 != 0) {
            return false;
        }
        break;
    }
    }
    return true;
}

void ftCo_800C0A98(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->bury_timer_1 != 0) {
        --fp->bury_timer_1;
    }
    switch (fp->bury_stage_kind) {
    case OLDKONGO:
    case KONGO:
        if (fp->bury_timer_2 != 0) {
            --fp->bury_timer_2;
            return;
        }
        break;
    case STAGEKIND_UNK39:
    case STAGEKIND_UNK32:
    case ZEBES:
        if (fp->bury_timer_2 != 0) {
            --fp->bury_timer_2;
            return;
        }
        break;
    }
}

void ftCo_800C0B20(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    DynamicsDesc* unk_anim;
    if (fp->bury_timer_1 == 0) {
        CollData* coll = &fp->coll_data;
        unk_anim = NULL;
        if (fp->coll_data.env_flags & (Collide_FloorPush | Collide_FloorHug)) {
            unk_anim = Ground_801C5700(coll->floor.index);
        }
        if (coll->env_flags & Collide_CeilingMask) {
            unk_anim = Ground_801C5700(coll->ceiling.index);
        }
        if (coll->env_flags & Collide_RightWallMask) {
            unk_anim = Ground_801C5700(coll->right_facing_wall.index);
        }
        if (coll->env_flags & Collide_LeftWallMask) {
            unk_anim = Ground_801C5700(coll->left_facing_wall.index);
        }
        if (unk_anim != NULL) {
            HitCapsule hit;
            Fighter* fp = GET_FIGHTER(gobj);
            float f = ftColl_800765F0(fp, NULL, unk_anim->count);
            fp->bury_timer_1 = p_ftCommonData->bury_timer_unk1;
            if (ftColl_80076640(fp, &f)) {
                FighterHurtCapsule* hurt = &fp->hurt_capsules[0];
                ftColl_80076764(3, 1, 0, unk_anim, fp, hurt);

                /// @todo Eliminate cast
                lbColl_80008D30(&hit, (lbColl_80008D30_arg1*) unk_anim);

                ftColl_80078384(fp, hurt, &hit);
            }
            pl_8003EC30(fp->player_id, fp->x221F_b4, 1, f);
        }
    }
}

bool ftCo_800C0C88(ftCommon_BuryType arg0)
{
    switch (arg0) {
    case BuryType_Unk1:
    case BuryType_Unk3:
        return true;
    default:
    case BuryType_Unk2:
        return false;
    }
}

bool ftCo_800C0CB8(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->dmg.x1860_element == 9 && fp->ground_or_air == GA_Ground &&
        !fp->x2227_b6)
    {
        ftCo_800C0D0C(gobj);
        return true;
    }
    return false;
}

void ftCo_800C0D0C(Fighter_GObj* gobj)
{
    u8 _[8] = { 0 };
    Vec3 joint_pos;
    Vec3 hip_pos;
    Fighter* fp = GET_FIGHTER(gobj);
    ftCommon_8007DB58(gobj);
    ftCo_8009750C(gobj);
    ftCo_800DD168(gobj);
    ftCo_8008DCE0(gobj, -1, 0);
    ftCommon_8007D7FC(fp);
    Fighter_ChangeMotionState(gobj, ftCo_MS_Bury,
                              Ft_MF_SkipMatAnim | Ft_MF_SkipColAnim, 0, 1, 0,
                              NULL);
    ftCommon_8007E2FC(gobj);
    ftCommon_InitGrab(
        fp, 0,
        (fp->dmg.x1830_percent * p_ftCommonData->x60C) +
            ((p_ftCommonData->x5FC *
              (p_ftCommonData->x600 - Player_GetHandicap(fp->player_id))) +
             p_ftCommonData->x5F8 +
             (p_ftCommonData->x604 *
              (p_ftCommonData->x608 - (Player_80033BB8(fp->player_id) + 1)))));
    ftCommon_8007E2F4(fp, 0x1FF);
    fp->x221D_b5 = true;
    fp->x2220_b3 = true;
    fp->x2224_b4 = true;
    fp->mv.co.bury.x0 = p_ftCommonData->x5F4;
    fp->mv.co.bury.x20 = fp->coll_data.floor.index;
    ft_80084CB0(fp, &fp->mv.co.bury.coll_box);
    lb_8000B1CC(fp->parts->joint, NULL, &joint_pos);
    lb_8000B1CC(fp->parts[ftParts_GetBoneIndex(fp, FtPart_HipN)].joint, NULL,
                &hip_pos);
    {
        float y = hip_pos.y - joint_pos.y;
        fp->mv.co.bury.x1C = y / p_ftCommonData->x5F4;
        fp->mv.co.bury.translate = fp->cur_pos;
        efSync_Spawn(1095, gobj, &fp->cur_pos, &fp->x34_scale.y, y);
    }
    fp->x2219_b0 = true;
}

void ftCo_Bury_Anim(Fighter_GObj* gobj)
{
    u8 _[8] = { 0 };
    Fighter* fp = GET_FIGHTER(gobj);
    fp->grab_timer -= p_ftCommonData->x610;
    ftCommon_GrabMash(fp, p_ftCommonData->x614);
    if (fp->grab_timer <= 0) {
        ftCo_800C13BC(gobj);
    }
    --fp->mv.co.bury.x0;
    if (fp->mv.co.bury.x0 == 0) {
        ftCo_800C124C(gobj);
    }
}

void ftCo_Bury_IASA(Fighter_GObj* gobj) {}

void ftCo_800C0FCC(HSD_GObj* arg0, Fighter_GObj* arg1)
{
    Fighter* fp = GET_FIGHTER(arg1);
    if (mpLib_80054ED8(fp->mv.co.bury.x20)) {
        Vec3 normal;
        Vec3 offset;
        HSD_JObj* jobj = GET_JOBJ(arg0);
        mpLineGetNormal(fp->mv.co.bury.x20, &normal);
        HSD_JObjSetRotationZ(jobj, atan2f(-normal.x, normal.y));
        if (mpGetSpeed(fp->coll_data.floor.index, &fp->mv.co.bury.translate,
                       &offset))
        {
            PSVECAdd(&fp->mv.co.bury.translate, &offset,
                     &fp->mv.co.bury.translate);
            HSD_JObjSetTranslate(jobj, &fp->mv.co.bury.translate);
        }
    }
}

#define MY_MIN(a, b) (((a) < (b)) ? (a) : (b))

void ftCo_Bury_Phys(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCollisionBox* box = &fp->mv.co.bury.coll_box;
    float mv_x18_x = MY_MIN(box->right.y, box->left.y);
    box->bottom += fp->mv.co.bury.x1C;
    if (1 + box->bottom > mv_x18_x) {
        box->bottom = mv_x18_x - 1;
    }
}

void ftCo_Bury_Coll(Fighter_GObj* gobj)
{
    u8 _[8] = { 0 };
    Fighter* fp = GET_FIGHTER(gobj);
    if (!ft_80082888(gobj, &fp->mv.co.bury.coll_box) ||
        fp->mv.co.bury.x20 != fp->coll_data.floor.index ||
        Ground_801C5700(fp->mv.co.bury.x20) != NULL)
    {
        ftCo_800C13BC(gobj);
    }
}

void ftCo_800C124C(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    Fighter_ChangeMotionState(
        gobj, ftCo_MS_BuryWait,
        Ft_MF_KeepGfx | Ft_MF_SkipMatAnim | Ft_MF_SkipColAnim, 0, 1, 0, NULL);
    ftCommon_8007E2FC(gobj);
    ftCommon_8007E2F4(fp, 0x1FF);
    fp->x221D_b5 = true;
    fp->x2220_b3 = true;
    fp->x2224_b4 = true;
}

void ftCo_BuryWait_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->grab_timer -= p_ftCommonData->x610;
    ftCommon_GrabMash(fp, p_ftCommonData->x614);
    if (fp->grab_timer <= 0) {
        ftCo_800C13BC(gobj);
    }
}

void ftCo_BuryWait_IASA(Fighter_GObj* gobj) {}

void ftCo_BuryWait_Phys(Fighter_GObj* gobj) {}

void ftCo_BuryWait_Coll(Fighter_GObj* gobj)
{
    u8 _[8] = { 0 };
    ftCo_Bury_Coll(gobj);
}

void ftCo_800C13BC(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (ftCo_800C5240(gobj)) {
        ftCo_800C5A98(gobj);
        return;
    }
    ftCommon_8007D5D4(fp);
    fp->self_vel.x = 0;
    fp->self_vel.y = p_ftCommonData->x618;
    fp->mv.co.buryjump.x0 = 0;
    Fighter_ChangeMotionState(gobj, ftCo_MS_BuryJump, Ft_MF_None, 0, 1, 0,
                              NULL);
    ftCommon_8007E2F4(fp, 0x1FF);
    ftColl_8007B7A4(gobj, p_ftCommonData->x620);
}

void ftCo_BuryJump_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->mv.co.buryjump.x0 += 1;
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftCo_Fall_Enter(gobj);
    }
}

void ftCo_BuryJump_IASA(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->mv.ca.specials.grav >= p_ftCommonData->x61C) {
        RETURN_IF(ftCo_SpecialAir_CheckInput(gobj));
        RETURN_IF(ftCo_80095328(gobj, NULL));
        RETURN_IF(ftCo_800D7100(gobj));
        RETURN_IF(ftCo_800C3B10(gobj));
        RETURN_IF(ftCo_80099A58(gobj));
        RETURN_IF(ftCo_AttackAir_CheckItemThrowInput(gobj));
        RETURN_IF(ftCo_800D705C(gobj));
        RETURN_IF(ftCo_800CB870(gobj));
    }
}

void ftCo_BuryJump_Phys(Fighter_GObj* gobj)
{
    u8 _[8] = { 0 };
    Fighter* fp = GET_FIGHTER(gobj);
    ftCommon_Fall(fp, fp->co_attrs.grav, fp->co_attrs.terminal_vel);
    ftCommon_8007D268(fp);
}

void ftCo_BuryJump_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->self_vel.y >= 0) {
        ft_80082D40(gobj, fp->self_vel.y);
    } else {
        ftCo_AirCatchHit_Coll(gobj);
    }
}
