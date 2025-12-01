#include "ftPk_SpecialS.h"

#include "ftPk_SpecialN.h"

#include <platform.h>

#include "ft/fighter.h"
#include "ft/ft_081B.h"
#include "ft/ft_0892.h"
#include "ft/ftanim.h"
#include "ft/ftcoll.h"
#include "ft/ftcommon.h"
#include "ft/types.h"
#include "ftCommon/ftCo_Fall.h"
#include "ftPikachu/types.h"

#include "lb/forward.h"

#include <common_structs.h>
#include <dolphin/mtx.h>

void ftPk_SpecialS_Enter(HSD_GObj* gobj)
{
    u8 _[4];

    Fighter* fp = GET_FIGHTER(gobj);
    ftPikachuAttributes* sa = fp->dat_attrs;

    fp->x21EC = ftPk_SpecialN_80124DC8;

    fp->gr_vel /= sa->x30;
    Fighter_ChangeMotionState(gobj, 343, 0, 0, 1, 0, 0);
    ftAnim_8006EBA4(gobj);
}

void ftPk_SpecialAirS_Enter(HSD_GObj* gobj)
{
    u8 _[4];

    Fighter* fp = GET_FIGHTER(gobj);
    ftPikachuAttributes* sa = fp->dat_attrs;

    fp->x21EC = ftPk_SpecialN_80124DC8;

    fp->self_vel.x /= sa->x30;
    fp->self_vel.y = 0;
    Fighter_ChangeMotionState(gobj, 348, 0, 0, 1, 0, 0);
    ftAnim_8006EBA4(gobj);
}

void ftPk_SpecialS_ZeroVelocity(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->self_vel.x = 0;

    if (fp->self_vel.y >= 0) {
        fp->self_vel.y = 0;
    }

    ftPk_SpecialS_ChangeMotion_Unk12(gobj);
}

void ftPk_SpecialSStart_Anim(HSD_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftPk_SpecialS_ChangeMotion_Unk04(gobj);
    }
}

void ftPk_SpecialAirSStart_Anim(HSD_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftPk_SpecialS_ChangeMotion_Unk05(gobj);
    }
}

void ftPk_SpecialSStart_IASA(HSD_GObj* arg0) {}

void ftPk_SpecialAirSStart_IASA(HSD_GObj* arg0) {}

void ftPk_SpecialSStart_Phys(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftPikachuAttributes* sa = getFtSpecialAttrsD(fp);
    ftCommon_ApplyFrictionGround(fp, sa->specials_start_friction);
    ftCommon_ApplyGroundMovement(gobj);
}

void ftPk_SpecialAirSStart_Phys(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftPikachuAttributes* pika_attr = getFtSpecialAttrsD(fp);
    struct ftCo_DatAttrs* da = &fp->co_attrs;

    if (fp->cmd_vars[0]) {
        ftCommon_Fall(fp, pika_attr->specials_start_gravity, da->terminal_vel);
    }

    ftCommon_ApplyFrictionAir(fp, pika_attr->specials_start_friction);
}

void ftPk_SpecialSStart_Coll(HSD_GObj* gobj)
{
    if (!ft_80082708(gobj)) {
        ftPk_SpecialS_ChangeMotion_Unk00(gobj);
    }
}

void ftPk_SpecialAirSStart_Coll(HSD_GObj* gobj)
{
    if (ft_80081D0C(gobj)) {
        ftPk_SpecialS_ChangeMotion_Unk01(gobj);
    }
}

static const u32 transition_flags0 =
    Ft_MF_KeepColAnimHitStatus | Ft_MF_SkipMatAnim | Ft_MF_KeepSfx |
    Ft_MF_SkipColAnim | Ft_MF_UpdateCmd | Ft_MF_SkipItemVis | Ft_MF_Unk19 |
    Ft_MF_SkipModelPartVis | Ft_MF_SkipModelFlags | Ft_MF_Unk27;

void ftPk_SpecialS_ChangeMotion_Unk00(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCommon_8007D5D4(fp);
    Fighter_ChangeMotionState(gobj, 348, transition_flags0, fp->cur_anim_frame,
                              1, 0, 0);
}

void ftPk_SpecialS_ChangeMotion_Unk01(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCommon_8007D7FC(fp);
    Fighter_ChangeMotionState(gobj, 343, transition_flags0, fp->cur_anim_frame,
                              1.0f, 0.0f, 0);
}

void ftPk_SpecialSHold_Anim(HSD_GObj* gobj)
{
    u8 _[4];

    Fighter* fp = GET_FIGHTER(gobj);
    ftPikachuAttributes* sa = fp->dat_attrs;

    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftCommon_8007DB24(gobj);
        fp->accessory4_cb = &ftPk_SpecialN_SpawnEffect0;
    }

    fp->mv.pk.unk3.x0++;

    if (fp->mv.pk.unk3.x0 > sa->x24) {
        ftPk_SpecialS_ChangeMotion_Unk08(gobj);
    }
}

void ftPk_SpecialAirSHold_Anim(HSD_GObj* gobj)
{
    u8 _[8];

    Fighter* fp = GET_FIGHTER(gobj);
    ftPikachuAttributes* sa = fp->dat_attrs;

    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftCommon_8007DB24(gobj);
        fp->accessory4_cb = &ftPk_SpecialN_SpawnEffect0;
    }

    fp->mv.pk.unk3.x0++;

    if (fp->mv.pk.unk3.x0 > sa->x24) {
        ftPk_SpecialS_ChangeMotion_Unk09(gobj);
    }
}

void ftPk_SpecialSHold_IASA(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (!(fp->input.held_inputs & HSD_PAD_B)) {
        ftPk_SpecialS_ChangeMotion_Unk08(gobj);
    }
}

void ftPk_SpecialAirSHold_IASA(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (!(fp->input.held_inputs & HSD_PAD_B)) {
        ftPk_SpecialS_ChangeMotion_Unk09(gobj);
    }
}

void ftPk_SpecialSHold_Phys(HSD_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftPk_SpecialAirSHold_Phys(HSD_GObj* gobj)
{
    ft_80084EEC(gobj);
}

void ftPk_SpecialSHold_Coll(HSD_GObj* gobj)
{
    if (!ft_80082708(gobj)) {
        ftPk_SpecialS_ChangeMotion_Unk02(gobj);
    }
}

void ftPk_SpecialAirSHold_Coll(HSD_GObj* gobj)
{
    if (ft_80081D0C(gobj)) {
        ftPk_SpecialS_ChangeMotion_Unk03(gobj);
    }
}

static u32 const transition_flags1 =
    Ft_MF_KeepGfx | Ft_MF_KeepColAnimHitStatus | Ft_MF_SkipMatAnim |
    Ft_MF_KeepSfx | Ft_MF_SkipColAnim | Ft_MF_UpdateCmd | Ft_MF_SkipItemVis |
    Ft_MF_Unk19 | Ft_MF_SkipModelPartVis | Ft_MF_SkipModelFlags | Ft_MF_Unk27;

void ftPk_SpecialS_ChangeMotion_Unk02(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCommon_8007D5D4(fp);
    Fighter_ChangeMotionState(gobj, 349, transition_flags1, fp->cur_anim_frame,
                              1, 0, 0);
}

void ftPk_SpecialS_ChangeMotion_Unk03(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCommon_8007D7FC(fp);
    Fighter_ChangeMotionState(gobj, 344, transition_flags1, fp->cur_anim_frame,
                              1, 0, 0);
}

void ftPk_SpecialS_ChangeMotion_Unk04(HSD_GObj* gobj)
{
    u8 _[8];

    Fighter_ChangeMotionState(gobj, 344, Ft_MF_KeepSfx, 0, 1, 0, 0);

    {
        Fighter* fp = GET_FIGHTER(gobj);
        fp->accessory4_cb = &ftPk_SpecialN_SpawnEffect0;
    }
}

void ftPk_SpecialS_ChangeMotion_Unk05(HSD_GObj* gobj)
{
    u8 _[8];

    Fighter_ChangeMotionState(gobj, 349, Ft_MF_KeepSfx, 0, 1, 0, 0);

    {
        Fighter* fp = GET_FIGHTER(gobj);
        fp->accessory4_cb = &ftPk_SpecialN_SpawnEffect0;
    }
}

void ftPk_SpecialS0_Anim(HSD_GObj* gobj)
{
    u8 _[16];

    Fighter* fp = GET_FIGHTER(gobj);
    ftPikachuAttributes* sa = fp->dat_attrs;

    if (fp->x914[0].state == HitCapsule_Enabled) {
        float damage_amount = fp->mv.pk.unk3.x0 * sa->x2C + sa->x28;
        ftColl_8007ABD0(&fp->x914[0], damage_amount, gobj);
    }

    if (fp->cmd_vars[0]) {
        ftCommon_8007D5D4(fp);
        ftPk_SpecialS_ChangeMotion_Unk10(gobj);
    }
}

void ftPk_SpecialAirS0_Anim(HSD_GObj* gobj)
{
    u8 _[16];

    Fighter* fp = GET_FIGHTER(gobj);
    ftPikachuAttributes* sa = fp->dat_attrs;

    if (fp->x914[0].state == HitCapsule_Enabled) {
        float damage_amount = fp->mv.pk.unk3.x0 * sa->x2C + sa->x28;
        ftColl_8007ABD0(&fp->x914[0], damage_amount, gobj);
    }

    if (fp->cmd_vars[0]) {
        ftPk_SpecialS_ChangeMotion_Unk10(gobj);
    }
}

void ftPk_SpecialS0_IASA(HSD_GObj* arg0) {}

void ftPk_SpecialAirS0_IASA(HSD_GObj* arg0) {}

void ftPk_SpecialS0_Phys(HSD_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftPk_SpecialAirS0_Phys(HSD_GObj* gobj)
{
    ft_80084EEC(gobj);
}

void ftPk_SpecialS0_Coll(HSD_GObj* gobj)
{
    if (!ft_80082708(gobj)) {
        ftPk_SpecialS_ChangeMotion_Unk06(gobj);
    }
}

void ftPk_SpecialAirS0_Coll(HSD_GObj* gobj)
{
    if (ft_80081D0C(gobj)) {
        ftPk_SpecialS_ChangeMotion_Unk07(gobj);
    }
}

static u32 const transition_flags2 =
    Ft_MF_KeepGfx | Ft_MF_KeepColAnimHitStatus | Ft_MF_SkipMatAnim |
    Ft_MF_SkipColAnim | Ft_MF_UpdateCmd | Ft_MF_SkipItemVis | Ft_MF_Unk19 |
    Ft_MF_SkipModelPartVis | Ft_MF_SkipModelFlags | Ft_MF_Unk27;

void ftPk_SpecialS_ChangeMotion_Unk06(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCommon_8007D5D4(fp);
    Fighter_ChangeMotionState(gobj, 352, transition_flags2, fp->cur_anim_frame,
                              1, 0, 0);
}

void ftPk_SpecialS_ChangeMotion_Unk07(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCommon_8007D7FC(fp);
    Fighter_ChangeMotionState(gobj, 347, transition_flags2, fp->cur_anim_frame,
                              1, 0, 0);
}

void ftPk_SpecialS_ChangeMotion_Unk08(HSD_GObj* gobj)
{
    u8 _[8];

    Fighter_ChangeMotionState(gobj, 347, 0, 0, 1, 0, 0);
    {
        Fighter* fp = GET_FIGHTER(gobj);
        fp->cmd_vars[0] = 0;
        ftCommon_8007DB24(gobj);
        fp->accessory4_cb = &ftPk_SpecialN_SpawnEffect1;
    }
}

void ftPk_SpecialS_ChangeMotion_Unk09(HSD_GObj* gobj)
{
    u8 _[8];

    Fighter_ChangeMotionState(gobj, 352, 0, 0, 1, 0, 0);

    {
        Fighter* fp = GET_FIGHTER(gobj);
        fp->cmd_vars[0] = 0;
        ftCommon_8007DB24(gobj);
        fp->accessory4_cb = &ftPk_SpecialN_SpawnEffect1;
    }
}

void ftPk_SpecialS1_Anim(HSD_GObj* arg0) {}

void ftPk_SpecialAirS1_Anim(HSD_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftPk_SpecialS_ChangeMotion_Unk12(gobj);
    }
}

void ftPk_SpecialS1_IASA(HSD_GObj* arg0) {}

void ftPk_SpecialAirS1_IASA(HSD_GObj* arg0) {}

void ftPk_SpecialS1_Phys(HSD_GObj* arg0) {}

void ftPk_SpecialAirS1_Phys(HSD_GObj* gobj)
{
    u8 _[8];

    Fighter* fp = GET_FIGHTER(gobj);
    ftPikachuAttributes* pika_attr = fp->dat_attrs;

    if (fp->cmd_vars[0] != 0) {
        ftCommon_Fall(fp, pika_attr->x58, pika_attr->x4C);
    } else {
        ftCommon_Fall(fp, pika_attr->x48, pika_attr->x4C);
    }

    if (fp->cmd_vars[0] != 0) {
        ftCommon_ApplyFrictionAir(fp, pika_attr->x54);
    }
}

void ftPk_SpecialS1_Coll(HSD_GObj* arg0) {}

void ftPk_SpecialAirS1_Coll(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    CollData* collData = &fp->coll_data;

    if (ft_80081D0C(gobj)) {
        ftCommon_8007D7FC(fp);
        ftPk_SpecialS_ChangeMotion_Unk11(gobj);
    }

    if (collData->env_flags & Collide_LeftWallMask ||
        collData->env_flags & Collide_RightWallMask)
    {
        ftPk_SpecialS_ChangeMotion_Unk12(gobj);
    }
}

static u32 const transition_flags3 = Ft_MF_KeepGfx | Ft_MF_SkipHit;

void ftPk_SpecialS_ChangeMotion_Unk10(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftPikachuAttributes* sa = fp->dat_attrs;

    fp->cmd_vars[0] = 0;

    fp->self_vel.x = sa->x40 * fp->mv.pk.unk3.x0 + sa->x3C;
    fp->self_vel.x *= fp->facing_dir;

    {
        float temp = 0.5f * fp->mv.pk.unk3.x0 / sa->x24;
        fp->self_vel.y = 0.5f * sa->x44 + sa->x44 * temp;
    }

    Fighter_ChangeMotionState(gobj, 350, transition_flags3, fp->cur_anim_frame,
                              1, 0, 0);

    fp->x21F8 = &ftCommon_8007F76C;
    fp->deal_dmg_cb = &ftPk_SpecialS_ZeroVelocity;
}

void ftPk_SpecialSEnd_Anim(HSD_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ft_8008A2BC(gobj);
    }
}

void ftPk_SpecialAirSEnd_Anim(HSD_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftCo_Fall_Enter(gobj);
    }
}

void ftPk_SpecialSEnd_IASA(HSD_GObj* arg0) {}

void ftPk_SpecialAirSEnd_IASA(HSD_GObj* arg0) {}

void ftPk_SpecialSEnd_Phys(HSD_GObj* gobj)
{
    u8 _[8];

    Fighter* fp = GET_FIGHTER(gobj);
    ftPikachuAttributes* sa = fp->dat_attrs;
    ftCommon_ApplyFrictionGround(fp, sa->x54);
    ftCommon_ApplyGroundMovement(gobj);
}

void ftPk_SpecialAirSEnd_Phys(HSD_GObj* gobj)
{
    u8 _[8];

    Fighter* fp = GET_FIGHTER(gobj);
    ftPikachuAttributes* sa = fp->dat_attrs;
    ftCommon_Fall(fp, sa->x58, fp->co_attrs.terminal_vel);
    ftCommon_ApplyFrictionAir(fp, sa->x54);
}

void ftPk_SpecialSEnd_Coll(HSD_GObj* gobj)
{
    if (!ft_80082708(gobj)) {
        ftCo_Fall_Enter(gobj);
    }
}

void ftPk_SpecialAirSEnd_Coll(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (ft_80081D0C(gobj)) {
        ftCommon_8007D7FC(fp);
        ftPk_SpecialS_ChangeMotion_Unk11(gobj);
    }
}

void ftPk_SpecialS_ChangeMotion_Unk11(HSD_GObj* gobj)
{
    u8 _[8];

    Fighter* fp = GET_FIGHTER(gobj);
    ftPikachuAttributes* sa = fp->dat_attrs;

    fp->cmd_vars[0] = 0;
    fp->gr_vel /= sa->x50;

    Fighter_ChangeMotionState(gobj, 346, 0, 0, 1, 0, 0);
}

void ftPk_SpecialS_ChangeMotion_Unk12(HSD_GObj* gobj)
{
    u8 _[8];

    Fighter* fp = GET_FIGHTER(gobj);
    ftPikachuAttributes* sa = fp->dat_attrs;

    fp->cmd_vars[0] = 0;
    fp->self_vel.x /= sa->x50;

    Fighter_ChangeMotionState(gobj, 351, 0, 0, 1, 0, 0);
}
