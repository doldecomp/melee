#include "ftkirby.h"
#include "types.h"

#include <placeholder.h>

#include "baselib/forward.h"

#include "ef/efasync.h"
#include "ft/chara/ftCommon/ftCo_Damage.h"
#include "ft/chara/ftCommon/ftCo_Jump.h"
#include "ft/chara/ftCommon/ftCo_KneeBend.h"
#include "ft/chara/ftCommon/ftCo_Throw.h"
#include "ft/chara/ftCommon/ftCo_ThrownKirby.h"
#include "ft/fighter.h"

#include "ft/forward.h"

#include "ft/ft_081B.h"
#include "ft/ft_084E.h"
#include "ft/ft_0852.h"
#include "ft/ft_0877.h"
#include "ft/ft_0892.h"
#include "ft/ftanim.h"
#include "ft/ftcoll.h"
#include "ft/ftcommon.h"
#include "ft/ftdata.h"
#include "ft/ftparts.h"
#include "ft/ftwalkcommon.h"
#include "ft/inlines.h"
#include "ft/types.h"
#include "ftCommon/ftCo_CaptureKirby.h"
#include "ftCommon/ftCo_CaptureWaitKirby.h"
#include "ftCommon/ftCo_Fall.h"
#include "ftCommon/inlines.h"

#include "ftKirby/forward.h"

#include "it/itCommonItems.h"
#include "it/items/it_2ADA.h"
#include "it/items/it_2F28.h"
#include "it/items/itkirby_2F23.h"
#include "lb/lb_00B0.h"
#include "lb/lbanim.h"
#include "mp/mpcoll.h"

#include <math.h>
#include <stddef.h>
#include <baselib/debug.h>
#include <baselib/gobj.h>
#include <baselib/random.h>

static MotionFlags const ftKb_MF_SpecialN_Coll =
    ftCommon_GroundAirColl_MF | Ft_MF_KeepGfx;
static MotionFlags const ftKb_MF_SpecialN_Capture_Coll =
    ftKb_MF_SpecialN_Coll | Ft_MF_SkipModel;
static MotionFlags const ftKb_MF_SpecialN_EatFall_Coll =
    ftCommon_GroundAirColl_MF | Ft_MF_SkipModel;
static MotionFlags const ftKb_MF_SpecialN_Loop_Coll =
    ftKb_MF_SpecialN_Capture_Coll | Ft_MF_SkipHit | Ft_MF_KeepSfx;
static MotionFlags const ftKb_MF_SpecialN_LoopRumble_Coll =
    ftKb_MF_SpecialN_Loop_Coll | Ft_MF_SkipRumble;

/// Forward declarations
void fn_800F9260(HSD_GObj*);
void fn_800F64C8(Fighter_GObj*, float);
void fn_800F6178(HSD_GObj* gobj);
static void fn_800F6210(HSD_GObj* gobj);
static void fn_800F6280(HSD_GObj* gobj);
static void fn_800F6318(HSD_GObj* gobj);
static void fn_800F6AC8(HSD_GObj* gobj);
float ftKb_SpecialN_800F58AC(Fighter_GObj* gobj, Vec3* victim_self_vel,
                             float victim_facing_dir)
{
    Fighter* ft = GET_FIGHTER(gobj);
    ftKb_DatAttrs* da = ft->dat_attrs;
    victim_self_vel->x = -victim_facing_dir *
                         da->specialn_ground_spit_initial_horizontal_velocity;
    victim_self_vel->z = 0.0f;
    victim_self_vel->y = 0.0f;
    return da->specialn_spit_deceleration_rate;
}

float ftKb_SpecialN_800F58D8(Fighter_GObj* gobj, Vec3* victim_self_vel,
                             float victim_facing_dir)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKb_DatAttrs* da = fp->dat_attrs;
    float cos_val = cosf(da->specialn_spit_out_release_angle);
    float temp = da->specialn_swallow_star_vertical_velocity * cos_val;

    victim_self_vel->x = victim_facing_dir * temp;
    victim_self_vel->y = da->specialn_swallow_star_vertical_velocity *
                         sinf(da->specialn_spit_out_release_angle);
    victim_self_vel->z = 0.0f;

    return da->specialn_swallow_star_gravity;
}

void ftKb_SpecialN_800F5954(Fighter_GObj* gobj)
{
    Fighter* ft = GET_FIGHTER(gobj);
    mpUpdateFloorSkip(&ft->coll_data);
}

bool ftKb_SpecialN_800F597C(Fighter_GObj* gobj)
{
    return M2C_FIELD(GET_FIGHTER(gobj), s32*, 0x840) & 0x100;
}

void ftKb_SpecialN_800F598C(Fighter_GObj* gobj, int arg1)
{
    f32 new_var;
    Fighter* fp = GET_FIGHTER(gobj);
    ftKb_DatAttrs* da = fp->dat_attrs;
    if (fp->ground_or_air == GA_Ground) {
        new_var = (f32) arg1;
        ftKb_SpecialS_800F6BB0(gobj);
        fp->self_vel.y = da->specialn_stop_momentum * new_var;
    }
}

void ftKb_SpecialN_800F5A04(Fighter_GObj* gobj, f32 arg1)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKb_DatAttrs* dat_attr = fp->dat_attrs;
    if (!fp->ground_or_air) {
        fp->gr_vel = arg1 * dat_attr->specialn_stop_momentum;
        return;
    }
    fp->self_vel.x = arg1 * dat_attr->specialn_stop_momentum;
}

bool ftKb_SpecialN_800F5A38(Fighter_GObj* gobj, Fighter* victim_fp)
{
    Fighter* fp = GET_FIGHTER(gobj);
    FtMotionId id = fp->motion_id;
    if (id == ftKb_MS_EatWait || id == ftKb_MS_EatFall) {
        return 1;
    }
    return 0;
}

float ftKb_SpecialN_800F5A60(Fighter_GObj* gobj)
{
    return -GET_FIGHTER(gobj)->facing_dir;
}

float ftKb_SpecialN_800F5A70(void)
{
    ftKb_DatAttrs* ea = gFtDataList[FTKIND_KIRBY]->ext_attr;
    return ea->specialn_gravity_of_inhaled;
}

f32 ftKb_SpecialN_800F5A88(Fighter_GObj* gobj)
{
    ftKb_DatAttrs* da = GET_FIGHTER(gobj)->dat_attrs;
    return da->specialn_star_base_duration;
}

f32 ftKb_SpecialN_800F5A98(void)
{
    ftKb_DatAttrs* ea = gFtDataList[FTKIND_KIRBY]->ext_attr;
    return ea->specialn_spit_spin;
}

f32 ftKb_SpecialN_800F5AB0(Fighter_GObj* gobj)
{
    ftKb_DatAttrs* da = GET_FIGHTER(gobj)->dat_attrs;
    return da->specialn_frames_in_swallow_star;
}

f32 ftKb_SpecialN_800F5AC0(void)
{
    ftKb_DatAttrs* ea = gFtDataList[FTKIND_KIRBY]->ext_attr;
    return ea->specialn_star_duration_divisor;
}

f32 ftKb_SpecialN_800F5AD8(void)
{
    ftKb_DatAttrs* ea = gFtDataList[FTKIND_KIRBY]->ext_attr;
    return ea->specialn_star_deceleration_rate;
}

f32 ftKb_SpecialN_800F5AF0(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKb_DatAttrs* da = fp->dat_attrs;
    return da->specialn_base_duration;
}

f32 ftKb_SpecialN_800F5B00(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKb_DatAttrs* da = fp->dat_attrs;
    return da->specialn_duration_divisor;
}

f32 ftKb_SpecialN_800F5B10(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKb_DatAttrs* da = fp->dat_attrs;
    return da->specialn_inhale_resistance;
}

void ftKb_SpecialN_800F5B20(Fighter_GObj* gobj, Vec2* out)
{
    Fighter* fp = GET_FIGHTER(gobj);
    struct ftKb_DatAttrs* da = fp->dat_attrs;
    out->x = da->specialn_velocity_outer_grab_box;
    out->y = da->specialn_velocity_inner_grab_box;
}

float ftKb_SpecialN_800F5B3C(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    struct ftKb_DatAttrs* da = fp->dat_attrs;
    return da->specialn_gravity_of_inhaled;
}

f32 ftKb_SpecialN_800F5B4C(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKb_DatAttrs* da = fp->dat_attrs;
    return da->specialn_z_offset_inhaled;
}

/// #ftKb_SpecialN_800F5B5C

/// #ftKb_SpecialN_800F5BA4

/// #ftKb_SpecialN_800F5C34

/// #ftKb_SpecialN_800F5D04

/// #ftKb_SpecialN_800F5DE8

/// #ftKb_SpecialN_800F5EA8

/// #ftKb_SpecialN_800F5F68

/// #ftKb_SpecialN_800F6070

/// #fn_800F6178

/// #fn_800F6210

/// #fn_800F6280

/// #fn_800F6318

/// #ftKb_SpecialN_800F6388

/// #ftKb_SpecialN_800F63EC

/// #fn_800F6450

/// #fn_800F64C8

/// #fn_800F6528

/// #fn_800F6588

/// #fn_800F6638

/// #fn_800F66E8

/// #fn_800F6798

/// #fn_800F6848

/// #fn_800F68A8

/// #fn_800F6908

/// #fn_800F697C

/// #fn_800F69E8

/// #fn_800F6A5C

/// #fn_800F6AC8

/// #fn_800F6B3C

/// #ftKb_SpecialS_800F6BB0

/// #fn_800F6C24

/// #fn_800F6C98

/// #fn_800F6D0C

/// #fn_800F6D80

/// #fn_800F6DF4

/// #fn_800F6E68

/// #fn_800F6EDC

/// #fn_800F6F50

/// #fn_800F6FC4

/// #fn_800F702C

/// #ftKb_SpecialN_Anim

/// #ftKb_SpecialAirN_Anim

/// #ftKb_SpecialNLoop_Anim

/// #ftKb_SpecialAirNLoop_Anim

/// #ftKb_SpecialNEnd_Anim

/// #ftKb_SpecialAirNEnd_Anim

/// #ftKb_SpecialNCapture0_Anim

/// #ftKb_SpecialNCapture_Anim

/// #ftKb_SpecialNCapture1_Anim

/// #ftKb_SpecialAirNCapture_Anim

/// #ftKb_Eat_Anim

/// #ftKb_SpecialAirNCaptured_Anim

/// #ftKb_EatWait_Anim

/// #ftKb_SpecialAirNCaptureWait_Anim

/// #ftKb_SpecialNSpit0_Anim

/// #ftKb_SpecialNSpit_Anim

/// #ftKb_SpecialNSpit1_Anim

/// #ftKb_SpecialAirNSpit_Anim

/// #ftKb_SpecialNDrink0_Anim

/// #ftKb_SpecialNDrink_Anim

/// #ftKb_SpecialNDrink1_Anim

/// #ftKb_SpecialAirNDrink_Anim

/// #ftKb_EatTurn_Anim

/// #ftKb_SpecialAirNCaptureTurn_Anim

/// #ftKb_EatWalk_Anim

/// #ftKb_EatJump1_Anim

/// #ftKb_EatJump2_Anim

/// #ftKb_EatLanding_Anim

/// #ftKb_SpecialNLoop_IASA

/// #ftKb_SpecialAirNLoop_IASA

/// #ftKb_EatWait_IASA

/// #ftKb_SpecialAirNCaptureWait_IASA

/// #ftKb_EatWalk_IASA

/// #ftKb_EatJump1_IASA

/// #ftKb_SpecialN_Phys

/// #ftKb_SpecialAirN_Phys

/// #ftKb_SpecialNLoop_Phys

/// #ftKb_SpecialAirNLoop_Phys

/// #ftKb_SpecialNEnd_Phys

/// #ftKb_SpecialAirNEnd_Phys

/// #ftKb_SpecialNCapture0_Phys

/// #ftKb_SpecialNCapture_Phys

/// #ftKb_SpecialNCapture1_Phys

/// #ftKb_SpecialAirNCapture_Phys

/// #ftKb_Eat_Phys

/// #ftKb_SpecialAirNCaptured_Phys

/// #ftKb_EatWait_Phys

/// #ftKb_SpecialAirNCaptureWait_Phys

/// #ftKb_SpecialNSpit0_Phys

/// #ftKb_SpecialNSpit_Phys

/// #ftKb_SpecialNSpit1_Phys

/// #ftKb_SpecialAirNSpit_Phys

/// #ftKb_SpecialNDrink0_Phys

/// #ftKb_SpecialNDrink_Phys

/// #ftKb_SpecialNDrink1_Phys

/// #ftKb_SpecialAirNDrink_Phys

/// #ftKb_EatTurn_Phys

/// #ftKb_SpecialAirNCaptureTurn_Phys

/// #ftKb_EatWalk_Phys

/// #ftKb_EatJump1_Phys

/// #ftKb_EatJump2_Phys

/// #ftKb_EatLanding_Phys

/// #ftKb_SpecialN_Coll

/// #ftKb_SpecialAirN_Coll

/// #ftKb_SpecialNLoop_Coll

/// #ftKb_SpecialAirNLoop_Coll

/// #ftKb_SpecialNEnd_Coll

/// #ftKb_SpecialAirNEnd_Coll

/// #ftKb_SpecialNCapture0_Coll

/// #ftKb_SpecialNCapture_Coll

/// #ftKb_SpecialNCapture1_Coll

/// #ftKb_SpecialAirNCapture_Coll

/// #ftKb_Eat_Coll

/// #ftKb_SpecialAirNCaptured_Coll

/// #ftKb_EatWait_Coll

/// #ftKb_SpecialAirNCaptureWait_Coll

/// #ftKb_SpecialNSpit0_Coll

/// #ftKb_SpecialNSpit_Coll

/// #ftKb_SpecialNSpit1_Coll

/// #ftKb_SpecialAirNSpit_Coll

/// #ftKb_SpecialNDrink0_Coll

/// #ftKb_SpecialNDrink_Coll

/// #ftKb_SpecialNDrink1_Coll

/// #ftKb_SpecialAirNDrink_Coll

/// #ftKb_EatTurn_Coll

/// #ftKb_SpecialAirNCaptureTurn_Coll

/// #ftKb_EatWalk_Coll

/// #ftKb_EatJump1_Coll

/// #ftKb_EatJump2_Coll

/// #ftKb_EatLanding_Coll

/// #ftKb_SpecialN_800F9070

/// #ftKb_SpecialN_800F9090

/// #ftKb_SpecialN_800F9110

/// #ftKb_MrSpecialN_Anim

/// #ftKb_MrSpecialN_IASA

/// #ftKb_MrSpecialN_Phys

/// #ftKb_MrSpecialN_Coll

/// #fn_800F9260

/// #ftKb_SpecialNMr_800F93CC

/// #ftKb_MrSpecialAirN_Anim

/// #ftKb_MrSpecialAirN_IASA

/// #ftKb_MrSpecialAirN_Phys

/// #ftKb_MrSpecialAirN_Coll

/// #ftKb_SpecialNLg_800F951C

/// #ftKb_SpecialNLg_800F9598

/// #ftKb_SpecialNLg_800F9614

/// #ftKb_SpecialNLg_800F9684

/// #ftKb_LgSpecialN_Anim

/// #ftKb_LgSpecialAirN_Anim

/// #ftKb_LgSpecialN_IASA

/// #ftKb_LgSpecialAirN_IASA

/// #ftKb_LgSpecialN_Phys

/// #ftKb_LgSpecialAirN_Phys

/// #ftKb_LgSpecialN_Coll

/// #ftKb_LgSpecialAirN_Coll

/// #fn_800F98F4

/// #ftKb_SpecialNCa_800F99BC

/// #ftKb_SpecialNCa_800F9A54

/// #ftKb_CaSpecialN_Anim

/// #ftKb_CaSpecialAirN_Anim

/// #ftKb_CaSpecialN_IASA

/// #ftKb_CaSpecialAirN_IASA

/// #ftKb_CaSpecialN_Phys

/// #ftKb_CaSpecialAirN_Phys

/// #ftKb_CaSpecialN_Coll

/// #ftKb_CaSpecialAirN_Coll

void ftKb_SpecialN_800F5B5C(Fighter_GObj* gobj, Vec3* output)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKb_DatAttrs* da = fp->dat_attrs;
    *output = fp->cur_pos;
    output->x += da->specialn_x_offset_inhaled * fp->facing_dir;
    output->y += da->specialn_y_offset_inhaled;
}

void ftKb_SpecialN_800F5BA4(Fighter* fp)
{
    ftKb_DatAttrs* da = fp->dat_attrs;
    if ((s32) fp->kind == FTKIND_KIRBY &&
        (s32) fp->u.kb.hat.kind != FTKIND_KIRBY && !fp->u.kb.hat.x8_b0 &&
        (u32) fp->victim_gobj == 0U &&
        fp->dmg.x1860_element != HitElement_Cape &&
        HSD_Randi((s32) da->specialn_odds_lose_ability_on_hit) == 0)
    {
        ftKb_SpecialN_800F5D04(fp->gobj, 1);
    }
}

void ftKb_SpecialN_800F5C34(Fighter* fp)
{
    ftKb_DatAttrs* da = fp->dat_attrs;
    if ((s32) fp->kind == FTKIND_KIRBY &&
        (s32) fp->u.kb.hat.kind != FTKIND_KIRBY && !fp->u.kb.hat.x8_b0 &&
        (u32) fp->victim_gobj == 0U &&
        HSD_Randi((s32) da->specialn_odds_lose_ability_on_hit) == 0)
    {
        s32 msid = fp->motion_id;
        if (msid >= 0x18F && msid < 0x220) {
            ftCo_8008EC90(fp->gobj);
            ftKb_SpecialN_800F5D04(fp->gobj, 1);
            if ((s32) fp->ground_or_air == GA_Ground) {
                ft_8008A2BC(fp->gobj);
            } else {
                ftCo_Fall_Enter(fp->gobj);
            }
            return;
        }
        ftKb_SpecialN_800F5D04(fp->gobj, 1);
    }
}

void ftKb_SpecialN_800F5D04(Fighter_GObj* gobj, bool arg1)
{
    Vec3 vel;
    Vec3 pos;
    Fighter* new_var;
    Fighter* fp = GET_FIGHTER(gobj);
    ftKb_DatAttrs* da;
    PAD_STACK(8);
    ftKb_SpecialN_800F19AC(gobj);
    ftKb_SpecialN_800F190C(gobj, fp->u.kb.hat.kind);
    ftKb_SpecialN_800EEEC4(gobj, fp->u.kb.hat.kind);
    new_var = fp;
    if ((s32) fp->u.kb.hat.kind != FTKIND_KIRBY && arg1 == 1) {
        Fighter* fp2 = GET_FIGHTER(gobj);
        da = fp2->dat_attrs;
        pos.x = fp2->cur_pos.x;
        pos.y = fp2->cur_pos.y + da->specialn_ability_loss_star_x;
        pos.z = 0.0F;
        vel.x = da->specialn_ability_loss_star_y * fp2->facing_dir;
        vel.y = da->specialn_ability_loss_star_z;
        vel.z = 0.0F;
        it_802ADA1C(&pos, &vel, fp2->facing_dir);
        ft_PlaySFX(fp, 0x22305, 0x7F, 0x40);
    }
    new_var->u.kb.hat.kind = FTKIND_KIRBY;
}

void ftKb_SpecialN_800F5DE8(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKb_DatAttrs* da = fp->dat_attrs;
    Vec3 pos = fp->cur_pos;
    PAD_STACK(20);

    pos.x += da->specialn_x_offset_inhaled * fp->facing_dir;
    pos.y += da->specialn_y_offset_inhaled;
    if (it_802F23AC(fp->target_item_gobj, &pos) <
        da->specialn_inhale_velocity * da->specialn_inhale_velocity)
    {
        it_802F2810(fp->target_item_gobj);
        if (fp->ground_or_air == GA_Air) {
            ftKb_SpecialN_800F63EC(gobj);
        } else {
            ftKb_SpecialN_800F6388(gobj);
        }
    }
}

void ftKb_SpecialN_800F5EA8(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKb_DatAttrs* da = fp->dat_attrs;
    Vec3 pos = fp->cur_pos;
    PAD_STACK(20);

    pos.x += da->specialn_x_offset_inhaled * fp->facing_dir;
    pos.y += da->specialn_y_offset_inhaled;
    if (ftCo_800BD19C(fp->victim_gobj, &pos) <
        da->specialn_inhale_velocity * da->specialn_inhale_velocity)
    {
        ftCo_800BD620(fp->victim_gobj);
        if (fp->ground_or_air == GA_Air) {
            ftKb_SpecialN_800F63EC(gobj);
        } else {
            ftKb_SpecialN_800F6388(gobj);
        }
    }
}

void ftKb_SpecialN_800F5F68(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKb_DatAttrs* da = fp->dat_attrs;
    PAD_STACK(4 * 12);

    fp->throw_flags = 0;
    fp->cmd_vars[0] = fp->cmd_vars[1] = 0;
    fp->u.kb.xE0 = 4;

    // Ends up being 00 28 according to data sheet
    fp->u.kb.xE4 = da->jumpaerial_unk;

    fp->u.kb.xE8 = lbAnim_8001E8F8(ftData_80085E50(fp, ftCo_MS_HammerFall));
    fp->u.kb.xEC = lbAnim_8001E8F8(ftData_80085E50(fp, ftCo_MS_HammerJump));
    fp->u.kb.xF0 = lbAnim_8001E8F8(ftData_80085E50(fp, ftCo_MS_HammerLanding));

    Fighter_ChangeMotionState(gobj, ftKb_MS_SpecialN, 0, 0, 1, 0, NULL);
    fp->x2222_b2 = true;
    ftAnim_8006EBA4(gobj);
    {
        Fighter* fp = GET_FIGHTER(gobj);
        ftCommon_8007E2D0(fp, 16, fn_800F6210, fn_800F6178, ftCo_800BD1DC);
        fp->x2225_b1 = true;
    }
}

void ftKb_SpecialN_800F6070(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKb_DatAttrs* da = fp->dat_attrs;
    PAD_STACK(4 * 12);

    fp->throw_flags = 0;
    fp->cmd_vars[0] = fp->cmd_vars[1] = 0;
    fp->u.kb.xE0 = 4;
    fp->u.kb.xE4 = da->jumpaerial_unk;
    fp->u.kb.xE8 = lbAnim_8001E8F8(ftData_80085E50(fp, ftCo_MS_HammerFall));
    fp->u.kb.xEC = lbAnim_8001E8F8(ftData_80085E50(fp, ftCo_MS_HammerJump));
    fp->u.kb.xF0 = lbAnim_8001E8F8(ftData_80085E50(fp, ftCo_MS_HammerLanding));

    Fighter_ChangeMotionState(gobj, ftKb_MS_SpecialAirN, 0, 0, 1, 0, NULL);
    fp->x2222_b2 = true;
    ftAnim_8006EBA4(gobj);
    {
        Fighter* fp = GET_FIGHTER(gobj);
        ftCommon_8007E2D0(fp, 16, fn_800F6318, fn_800F6280, ftCo_800BD1DC);
        fp->x2225_b1 = true;
    }
}

void fn_800F6178(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    it_802F23EC(fp->target_item_gobj, gobj, -fp->facing_dir);
    Fighter_ChangeMotionState(gobj, ftKb_MS_SpecialNCapture1,
                              Ft_MF_KeepGfx | Ft_MF_SkipModel | Ft_MF_KeepSfx,
                              0, 1, 0, NULL);
    fp->x2222_b2 = true;
    fp->u.kb.xF4_b0 = true;
    ftKb_SpecialN_800F9070(gobj);
    ftCommon_8007E2F4(fp, 0x1FF);
}

static void fn_800F6210(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    Fighter_ChangeMotionState(gobj, ftKb_MS_SpecialNCapture0, 0x212, 0.0f,
                              1.0f, 0.0f, NULL);
    fp->x2222_b2 = true;
    fp->u.kb.xF4_b0 = false;
    ftCommon_8007E2F4(fp, 0x1FF);
}

static void fn_800F6280(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    it_802F23EC(fp->target_item_gobj, gobj, -fp->facing_dir);
    Fighter_ChangeMotionState(gobj, ftKb_MS_SpecialAirNCapture1,
                              Ft_MF_KeepGfx | Ft_MF_SkipModel | Ft_MF_KeepSfx,
                              0, 1, 0, NULL);
    fp->x2222_b2 = true;
    fp->u.kb.xF4_b0 = true;
    ftKb_SpecialN_800F9070(gobj);
    ftCommon_8007E2F4(fp, 0x1FF);
}

static void fn_800F6318(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    Fighter_ChangeMotionState(gobj, ftKb_MS_SpecialAirNCapture0, 0x212, 0.0f,
                              1.0f, 0.0f, NULL);
    fp->x2222_b2 = true;
    fp->u.kb.xF4_b0 = false;
    ftCommon_8007E2F4(fp, 0x1FF);
}

void ftKb_SpecialN_800F6388(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    Fighter_ChangeMotionState(gobj, ftKb_MS_Eat, 0x10, 0.0F, 1.0F, 0.0F, NULL);
    ftKb_SpecialN_800F9070(gobj);
    ftCommon_8007E2F4(fp, 0x1FF);
}

void ftKb_SpecialN_800F63EC(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    Fighter_ChangeMotionState(gobj, ftKb_MS_EatAir, 0x10, 0.0F, 1.0F, 0.0F,
                              NULL);
    ftKb_SpecialN_800F9070(gobj);
    ftCommon_8007E2F4(fp, 0x1FF);
}

void fn_800F6450(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCommon_8007D5D4(fp);
    Fighter_ChangeMotionState(gobj, ftKb_MS_EatFall, 0x90, 0.0f, 1.0f, 0.0f,
                              NULL);
    ftKb_SpecialN_800F9070(gobj);
    ftAnim_8006EBA4(gobj);
    ftCommon_8007E2F4(fp, 0x1FF);
}

void fn_800F64C8(Fighter_GObj* gobj, float anim_start)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCo_DatAttrs* ca = getFtAttrs(fp);
    ftKb_DatAttrs* da = fp->dat_attrs;
    ftWalkCommon_800DFCA4(gobj, ftKb_MS_EatWalkSlow, Ft_MF_SkipModel,
                          anim_start, fp->u.kb.xE8, fp->u.kb.xEC, fp->u.kb.xF0,
                          ca->slow_walk_max, ca->mid_walk_point,
                          ca->fast_walk_min, da->specialn_walk_speed);
    ftCommon_8007E2F4(fp, 0x1FF);
}

void fn_800F6528(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCommon_8007D7FC(fp);
    Fighter_ChangeMotionState(gobj, ftKb_MS_EatLanding, 0x12, 0.0f, 1.0f, 0.0f,
                              NULL);
    ftKb_SpecialN_800F9070(gobj);
    ftAnim_8006EBA4(gobj);
}

void fn_800F6588(HSD_GObj* gobj)
{
    void* new_var2;
    Fighter* fp = GET_FIGHTER(gobj);
    Fighter* new_var;
    ftCommon_GroundToAirStateChange(gobj, fp, ftKb_MS_SpecialAirN,
                                    ftKb_MF_SpecialN_Loop_Coll);
    new_var = fp;
    Fighter_SetEffectHitlagCallbacks(new_var);
    new_var2 = HSD_GObjGetUserData(gobj);
    fp = (Fighter*) new_var2;
    ftCommon_8007E2D0(fp, 0x10, fn_800F6318, fn_800F6280, ftCo_800BD1DC);
    fp->x2225_b1 = true;
}

void fn_800F6638(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    void* new_var;
    void (*new_var2)(Fighter_GObj* gobj, Fighter_GObj* victim_gobj);
    new_var2 = ftCo_800BD1DC;
    ftCommon_8007D7FC(fp);
    if (new_var2) {
    }
    Fighter_ChangeMotionState(gobj, ftKb_MS_SpecialN, 0x0C4C529A,
                              fp->cur_anim_frame, 1.0f, 0.0f, NULL);
    Fighter_SetEffectHitlagCallbacks(fp);
    new_var = HSD_GObjGetUserData(gobj);
    fp = (Fighter*) new_var;
    ftCommon_8007E2D0(fp, 0x10, fn_800F6210, fn_800F6178, ftCo_800BD1DC);
    fp->x2225_b1 = true;
}

void fn_800F66E8(HSD_GObj* gobj)
{
    Fighter* fp = (Fighter*) HSD_GObjGetUserData(gobj);
    PAD_STACK(8);
    ftCommon_8007D5D4(fp);
    Fighter_ChangeMotionState(gobj, ftKb_MS_SpecialAirNLoop, 0x0C4C5A9A,
                              fp->cur_anim_frame, 1.0f, 0.0f, 0L);
    Fighter_SetEffectHitlagCallbacks(fp);
    fp = (Fighter*) HSD_GObjGetUserData(gobj);
    ftCommon_8007E2D0(fp, 0x10, fn_800F6318, fn_800F6280, ftCo_800BD1DC);
    fp->x2225_b1 = 1;
}

void fn_800F6798(HSD_GObj* gobj)
{
    Fighter* new_var;
    volatile unsigned long long pad;
    Fighter* fp = GET_FIGHTER(gobj);
    ftCommon_AirToGroundStateChange(gobj, fp, ftKb_MS_SpecialNLoop,
                                    ftKb_MF_SpecialN_LoopRumble_Coll);
    Fighter_SetEffectHitlagCallbacks(fp);
    fp = HSD_GObjGetUserData(gobj);
    ftCommon_8007E2D0(fp, 0x10, fn_800F6210, fn_800F6178, ftCo_800BD1DC);
    new_var = fp;
    new_var->x2225_b1 = true;
}

void fn_800F6848(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCommon_GroundToAirStateChange(gobj, fp, ftKb_MS_SpecialAirNEnd,
                                    ftKb_MF_SpecialN_Coll);
}

void fn_800F68A8(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCommon_AirToGroundStateChange(gobj, fp, ftKb_MS_SpecialNEnd,
                                    ftKb_MF_SpecialN_Coll);
}

void fn_800F6908(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCommon_GroundToAirStateChange(gobj, fp, ftKb_MS_SpecialAirNCapture1,
                                    ftKb_MF_SpecialN_Capture_Coll);
    ftKb_SpecialN_800F9070(gobj);
    ftCommon_8007E2F4(fp, 0x1FF);
}

void fn_800F697C(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCommon_GroundToAirStateChange(gobj, fp, ftKb_MS_SpecialAirNCapture0,
                                    ftKb_MF_SpecialN_Capture_Coll);
    ftCommon_8007E2F4(fp, 0x1FF);
}

void fn_800F69E8(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCommon_AirToGroundStateChange(gobj, fp, ftKb_MS_SpecialNCapture1,
                                    ftKb_MF_SpecialN_Capture_Coll);
    ftKb_SpecialN_800F9070(gobj);
    ftCommon_8007E2F4(fp, 0x1FF);
}

void fn_800F6A5C(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCommon_AirToGroundStateChange(gobj, fp, ftKb_MS_SpecialNCapture0,
                                    ftKb_MF_SpecialN_Capture_Coll);
    ftCommon_8007E2F4(fp, 0x1FF);
}

/// Fighter_CollGround_PassLedgeCB
static void fn_800F6AC8(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCommon_GroundToAirStateChange(gobj, fp, ftKb_MS_EatAir,
                                    ftKb_MF_SpecialN_Capture_Coll);
    ftKb_SpecialN_800F9070(gobj);
    ftCommon_8007E2F4(fp, 0x1FF);
}

void fn_800F6B3C(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCommon_AirToGroundStateChange(gobj, fp, ftKb_MS_Eat,
                                    ftKb_MF_SpecialN_Capture_Coll);
    ftKb_SpecialN_800F9070(gobj);
    ftCommon_8007E2F4(fp, 0x1FF);
}

void ftKb_SpecialS_800F6BB0(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCommon_GroundToAirStateChange(gobj, fp, ftKb_MS_EatFall,
                                    ftKb_MF_SpecialN_EatFall_Coll);
    ftKb_SpecialN_800F9070(gobj);
    ftCommon_8007E2F4(fp, 0x1FF);
}

void fn_800F6C24(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCommon_GroundToAirStateChange(gobj, fp, ftKb_MS_SpecialAirNSpit1,
                                    ftKb_MF_SpecialN_Capture_Coll);
    ftKb_SpecialN_800F9070(gobj);
    ftCommon_8007E2F4(fp, 0x1FF);
}

void fn_800F6C98(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCommon_GroundToAirStateChange(gobj, fp, ftKb_MS_SpecialAirNSpit0,
                                    ftKb_MF_SpecialN_Capture_Coll);
    ftKb_SpecialN_800F9070(gobj);
    ftCommon_8007E2F4(fp, 0x1FF);
}

void fn_800F6D0C(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCommon_AirToGroundStateChange(gobj, fp, ftKb_MS_SpecialNSpit1,
                                    ftKb_MF_SpecialN_Capture_Coll);
    ftKb_SpecialN_800F9070(gobj);
    ftCommon_8007E2F4(fp, 0x1FF);
}

void fn_800F6D80(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCommon_AirToGroundStateChange(gobj, fp, ftKb_MS_SpecialNSpit0,
                                    ftKb_MF_SpecialN_Capture_Coll);
    ftKb_SpecialN_800F9070(gobj);
    ftCommon_8007E2F4(fp, 0x1FF);
}

void fn_800F6DF4(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCommon_GroundToAirStateChange(gobj, fp, ftKb_MS_SpecialAirNDrink1,
                                    ftKb_MF_SpecialN_Coll);
    ftKb_SpecialN_800F9070(gobj);
    ftCommon_8007E2F4(fp, 0x1FF);
}

void fn_800F6E68(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCommon_GroundToAirStateChange(gobj, fp, ftKb_MS_SpecialAirNDrink0,
                                    ftKb_MF_SpecialN_Coll);
    ftKb_SpecialN_800F9070(gobj);
    ftCommon_8007E2F4(fp, 0x1FF);
}

void fn_800F6EDC(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCommon_AirToGroundStateChange(gobj, fp, ftKb_MS_SpecialNDrink1,
                                    ftKb_MF_SpecialN_Coll);
    ftKb_SpecialN_800F9070(gobj);
    ftCommon_8007E2F4(fp, 0x1FF);
}

void fn_800F6F50(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCommon_AirToGroundStateChange(gobj, fp, ftKb_MS_SpecialNDrink0,
                                    ftKb_MF_SpecialN_Coll);
    ftKb_SpecialN_800F9070(gobj);
    ftCommon_8007E2F4(fp, 0x1FF);
}

void fn_800F6FC4(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCommon_GroundToAirStateChange(gobj, fp, ftKb_MS_EatTurnAir,
                                    ftKb_MF_SpecialN_Capture_Coll);
    ftKb_SpecialN_800F9070(gobj);
}

void fn_800F702C(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCommon_AirToGroundStateChange(gobj, fp, ftKb_MS_EatTurn,
                                    ftKb_MF_SpecialN_Capture_Coll);
    ftKb_SpecialN_800F9070(gobj);
    ftCommon_8007E2F4(fp, 0x1FF);
}

static inline void ftKb_SpecialN_SetHitlagCb(Fighter_GObj* gobj, s32 ms,
                                             MotionFlags mf)
{
    Fighter* fp = GET_FIGHTER(gobj);
    Fighter_ChangeMotionState(gobj, ms, mf, 0.0f, 1.0f, 0.0f, NULL);
    fp->x2222_b2 = true;
    Fighter_SetEffectHitlagCallbacks(fp);
}

static inline void
ftKb_SpecialN_SetThrowCb(Fighter_GObj* gobj, s32 mask,
                         HSD_GObjEvent capture_cb, HSD_GObjEvent release_cb,
                         void (*throw_cb)(HSD_GObj*, HSD_GObj*))
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCommon_8007E2D0(fp, mask, capture_cb, release_cb, throw_cb);
    fp->x2225_b1 = true;
}

void ftKb_SpecialN_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    HSD_JObj* joint = fp->parts[FtPart_YRotN].joint;
    PAD_STACK(8);

    if (fp->cmd_vars[0] != 0) {
        efAsync_Spawn(gobj, &fp->x60C, 3, 0x49A, joint, &fp->facing_dir);
        fp->x2219_b0 = true;
        Fighter_SetEffectHitlagCallbacks(fp);
        fp->cmd_vars[0] = 0;
    }
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftKb_SpecialN_SetHitlagCb(gobj, 0x162, 0x212);
        ftKb_SpecialN_SetThrowCb(gobj, 0x10, fn_800F6210, fn_800F6178,
                                 ftCo_800BD1DC);
    }
}

void ftKb_SpecialAirN_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    HSD_JObj* joint = fp->parts[FtPart_YRotN].joint;
    PAD_STACK(8);

    if (fp->cmd_vars[0] != 0) {
        efAsync_Spawn(gobj, &fp->x60C, 3, 0x49A, joint, &fp->facing_dir);
        fp->x2219_b0 = true;
        Fighter_SetEffectHitlagCallbacks(fp);
        fp->cmd_vars[0] = 0;
    }
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftKb_SpecialN_SetHitlagCb(gobj, 0x174, 0x212);
        ftKb_SpecialN_SetThrowCb(gobj, 0x10, fn_800F6318, fn_800F6280,
                                 ftCo_800BD1DC);
    }
}

void ftKb_SpecialNLoop_Anim(Fighter_GObj* gobj) {}

void ftKb_SpecialAirNLoop_Anim(Fighter_GObj* gobj) {}

void ftKb_SpecialNEnd_Anim(Fighter_GObj* gobj)
{
    PAD_STACK(8);
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ft_8008A2BC(gobj);
    }
}

void ftKb_SpecialAirNEnd_Anim(Fighter_GObj* gobj)
{
    PAD_STACK(8);
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftCo_Fall_Enter(gobj);
    }
}

static inline void ftKb_SpecialNCapture_EnterState(Fighter_GObj* gobj, s32 ms)
{
    Fighter* fp = GET_FIGHTER(gobj);
    Fighter_ChangeMotionState(gobj, ms, 0x10, 0.0f, 1.0f, 0.0f, NULL);
    ftKb_SpecialN_800F9070(gobj);
    ftCommon_8007E2F4(fp, 0x1FF);
}

void ftKb_SpecialNCapture0_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = getFighter(gobj);
    ftKb_DatAttrs* da = fp->dat_attrs;
    Vec3 pos = fp->cur_pos;
    u8 _pad[32];

    pos.x += da->specialn_x_offset_inhaled * fp->facing_dir;
    pos.y += da->specialn_y_offset_inhaled;
    if (it_802F23AC(fp->target_item_gobj, &pos) <
        SQ(da->specialn_inhale_velocity))
    {
        it_802F2810(fp->target_item_gobj);
        if (fp->ground_or_air == GA_Air) {
            ftKb_SpecialNCapture_EnterState(gobj, 0x178);
        } else {
            ftKb_SpecialNCapture_EnterState(gobj, 0x166);
        }
        fp->facing_dir = fp->facing_dir; // fake match, via permuter
    }
}

void ftKb_SpecialNCapture_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = getFighter(gobj);
    ftKb_DatAttrs* da = fp->dat_attrs;
    Vec3 pos = fp->cur_pos;
    u8 _pad[32];

    pos.x += da->specialn_x_offset_inhaled * fp->facing_dir;
    pos.y += da->specialn_y_offset_inhaled;
    if (ftCo_800BD19C(fp->victim_gobj, &pos) <
        SQ(da->specialn_inhale_velocity))
    {
        ftCo_800BD620(fp->victim_gobj);
        if (fp->ground_or_air == GA_Air) {
            ftKb_SpecialNCapture_EnterState(gobj, 0x178);
        } else {
            ftKb_SpecialNCapture_EnterState(gobj, 0x166);
        }
        fp->facing_dir = fp->facing_dir; // fake match, via permuter
    }
}

#ifdef MUST_MATCH
#pragma dont_inline on
#endif
void ftKb_SpecialNCapture1_Anim(Fighter_GObj* gobj)
{
    ftKb_SpecialN_800F5DE8(gobj);
}

void ftKb_SpecialAirNCapture_Anim(Fighter_GObj* gobj)
{
    ftKb_SpecialN_800F5EA8(gobj);
}
#ifdef MUST_MATCH
#pragma dont_inline off
#endif

void ftKb_Eat_Anim(HSD_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        Fighter* fp = GET_FIGHTER(gobj);
        PAD_STACK(4);
        Fighter_ChangeMotionState(gobj, ftKb_MS_EatWait, Ft_MF_SkipModel, 0, 1,
                                  0, NULL);
        ftKb_SpecialN_800F9070(gobj);
        ftAnim_8006EBA4(gobj);
        ftCommon_8007E2F4(fp, 0x1FF);
    }
}

void ftKb_SpecialAirNCaptured_Anim(Fighter_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        Fighter* fp = (0, GET_FIGHTER(gobj));
        ftCommon_8007D5D4(fp);
        Fighter_ChangeMotionState(gobj, ftKb_MS_EatFall, 0x90, 0.0f, 1.0f,
                                  0.0f, NULL);
        ftKb_SpecialN_800F9070(gobj);
        ftAnim_8006EBA4(gobj);
        ftCommon_8007E2F4(fp, 0x1FF);
    }
}

void ftKb_EatWait_Anim(Fighter_GObj* gobj) {}

void ftKb_SpecialAirNCaptureWait_Anim(Fighter_GObj* gobj) {}

static inline void ftKb_SpecialNSpit_Anim_inline(Fighter_GObj* gobj,
                                                 Fighter_GObj* victim)
{
    if (victim != NULL) {
        Fighter* fp = GET_FIGHTER(gobj);
        Fighter* victim_fp = victim->user_data;
        ftCommon_8007E2F4(fp, 0);
        ftCo_800DE2CC(gobj, victim);
        ftCo_800BDB58(victim, gobj);
        ftColl_8007B8CC(victim_fp, gobj);
        fp->cmd_vars[0] = 0;
    }
}

void ftKb_SpecialNSpit0_Anim(Fighter_GObj* gobj)
{
    UNUSED u32 unused1;
    Fighter* fp = getFighter(gobj);
    Item_GObj* item_gobj;
    ftKb_DatAttrs* da;
    struct itUnk2_DatAttrs attr;
    PAD_STACK(0x40);

    if (fp->cmd_vars[0] != 0 && (item_gobj = fp->target_item_gobj) != NULL) {
        ftCommon_8007E2F4(fp, 0);
        lb_8000B1CC(fp->parts[ftParts_GetBoneIndex(fp, FtPart_TransN2)].joint,
                    NULL, &attr.pos);
        {
            f32 neg_facing = -fp->facing_dir;
            da = getFighter(gobj)->dat_attrs;
            attr.vel.x = -neg_facing *
                         da->specialn_ground_spit_initial_horizontal_velocity;
            attr.vel.z = 0.0f;
            attr.vel.y = 0.0f;
            attr.float2 = da->specialn_spit_deceleration_rate;
            attr.float1 = ((ftKb_DatAttrs*) getFighter(gobj)->dat_attrs)
                              ->specialn_star_base_duration;
            it_802F28C8(item_gobj, 0, it_802F295C(gobj, &attr));
        }
        fp->x1A64 = NULL;
        fp->target_item_gobj = NULL;
        fp->cmd_vars[0] = 0;
    }
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ft_8008A2BC(gobj);
    }
}

void ftKb_SpecialNSpit_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    PAD_STACK(16);

    if (fp->cmd_vars[0] != 0) {
        ftKb_SpecialNSpit_Anim_inline(gobj, fp->victim_gobj);
    }
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ft_8008A2BC(gobj);
    }
}

void ftKb_SpecialNSpit1_Anim(Fighter_GObj* gobj)
{
    UNUSED u32 unused1;
    Fighter* fp = getFighter(gobj);
    Item_GObj* item_gobj;
    ftKb_DatAttrs* da;
    itUnk2_DatAttrs attr;
    PAD_STACK(0x40);

    if (fp->cmd_vars[0] != 0 && (item_gobj = fp->target_item_gobj) != NULL) {
        ftCommon_8007E2F4(fp, 0);
        lb_8000B1CC(fp->parts[ftParts_GetBoneIndex(fp, FtPart_TransN2)].joint,
                    NULL, &attr.pos);
        {
            f32 neg_facing = -fp->facing_dir;
            da = getFighter(gobj)->dat_attrs;
            attr.vel.x = -neg_facing *
                         da->specialn_ground_spit_initial_horizontal_velocity;
            attr.vel.z = 0.0f;
            attr.vel.y = 0.0f;
            attr.float2 = da->specialn_spit_deceleration_rate;
            attr.float1 = ((ftKb_DatAttrs*) getFighter(gobj)->dat_attrs)
                              ->specialn_star_base_duration;
            it_802F28C8(item_gobj, 0, it_802F295C(gobj, &attr));
        }
        fp->x1A64 = NULL;
        fp->target_item_gobj = NULL;
        fp->cmd_vars[0] = 0;
    }
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftCo_Fall_Enter(gobj);
    }
}

void ftKb_SpecialAirNSpit_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    PAD_STACK(16);

    if (fp->cmd_vars[0] != 0) {
        ftKb_SpecialNSpit_Anim_inline(gobj, fp->victim_gobj);
    }
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftCo_Fall_Enter(gobj);
    }
}

void ftKb_SpecialNDrink0_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = getFighter(gobj);
    Item_GObj* item_gobj;
    PAD_STACK(16);
    if (fp->cmd_vars[0] != 0 && (item_gobj = fp->target_item_gobj) != NULL) {
        ftCommon_8007E2F4(fp, 0);
        ft_PlaySFX(fp, 0x222F6, 0x7F, 0x40);
        it_802F28C8(item_gobj, 0, 0.0F);
        fp->x1A64 = NULL;
        fp->target_item_gobj = NULL;
        fp->cmd_vars[0] = 0;
    }
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ft_8008A2BC(gobj);
    }
}

static inline void ftKb_SpecialNDrink_Anim_inline(Fighter_GObj* gobj,
                                                  Fighter_GObj* victim_gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->u.kb.xE0 = ftCo_800BD9E0(gobj, victim_gobj);
    ftKb_SpecialN_800F1BAC(gobj, fp->u.kb.xE0, true);
}

void ftKb_SpecialNDrink_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = getFighter(gobj);
    u8 _pad[24];
    if (fp->cmd_vars[0] != 0) {
        Fighter_GObj* victim_gobj;
        if ((victim_gobj = fp->victim_gobj) != NULL) {
            Fighter* new_fp = fp;
            ftCommon_8007E2F4(new_fp, 0);
            ftCo_800DE2CC(gobj, victim_gobj);
            ftCo_800BE000(victim_gobj, gobj);
            ftKb_SpecialNDrink_Anim_inline(gobj, victim_gobj);
            fp->cmd_vars[0] = 0;
        }
    }
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ft_8008A2BC(gobj);
    }
}

void ftKb_SpecialNDrink1_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = getFighter(gobj);
    Item_GObj* item_gobj;
    PAD_STACK(16);
    if (fp->cmd_vars[0] != 0 && (item_gobj = fp->target_item_gobj) != NULL) {
        ftCommon_8007E2F4(fp, 0);
        ft_PlaySFX(fp, 0x222F6, 0x7F, 0x40);
        it_802F28C8(item_gobj, 0, 0.0F);
        fp->x1A64 = NULL;
        fp->target_item_gobj = NULL;
        fp->cmd_vars[0] = 0;
    }
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftCo_Fall_Enter(gobj);
    }
}

void ftKb_SpecialAirNDrink_Anim(Fighter_GObj* gobj)
{
    Fighter* fp2;
    Fighter_GObj* victim_gobj;
    Fighter* fp = getFighter(gobj);
    Fighter* new_var;
    if (fp->cmd_vars[0] != 0) {
        if ((victim_gobj = fp->victim_gobj) != NULL) {
            new_var = fp;
            ftCommon_8007E2F4(new_var, 0);
            ftCo_800DE2CC(gobj, victim_gobj);
            ftCo_800BE000(victim_gobj, gobj);
            fp2 = getFighter(gobj);
            fp2->u.kb.xE0 = ftCo_800BD9E0(gobj, victim_gobj);
            ftKb_SpecialN_800F1BAC(gobj, fp2->u.kb.xE0, true);
            fp->cmd_vars[0] = 0;
        }
    }
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftCo_Fall_Enter(gobj);
    }
    PAD_STACK(32);
}

void ftKb_EatTurn_Anim(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (!ftAnim_IsFramesRemaining(gobj)) {
        fp->facing_dir = -fp->facing_dir;
        fp = GET_FIGHTER(gobj);
        Fighter_ChangeMotionState(gobj, ftKb_MS_EatWait, Ft_MF_SkipModel, 0.0f,
                                  1.0f, 0.0f, NULL);
        ftKb_SpecialN_800F9070(gobj);
        ftAnim_8006EBA4(gobj);
        ftCommon_8007E2F4(fp, 0x1FF);
    }
}

void ftKb_SpecialAirNCaptureTurn_Anim(Fighter_GObj* gobj)
{
    Fighter_GObj* new_var;
    Fighter_GObj* new_var2;
    Fighter* fp = GET_FIGHTER(gobj);
    new_var = gobj;
    new_var2 = new_var;
    if (!ftAnim_IsFramesRemaining(gobj)) {
        fp->facing_dir = -fp->facing_dir;
        fp = new_var2->user_data;
        ftCommon_8007D5D4(fp);
        Fighter_ChangeMotionState(gobj, ftKb_MS_EatFall, 0x90, 0.0f, 1.0f,
                                  0.0f, NULL);
        ftKb_SpecialN_800F9070(gobj);
        ftAnim_8006EBA4(gobj);
        ftCommon_8007E2F4(fp, 0x1FF);
    }
}

void ftKb_EatWalk_Anim(Fighter_GObj* gobj)
{
    ftWalkCommon_800DFDDC(gobj);
}

void ftKb_EatJump1_Anim(Fighter_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        Fighter* fp = GET_FIGHTER(gobj);
        ftKb_DatAttrs* da = fp->dat_attrs;
        PAD_STACK(24);
        ftCommon_8007D5D4(fp);
        Fighter_ChangeMotionState(gobj, ftKb_MS_EatJump2, 0x92, 0.0f, 1.0f,
                                  0.0f, NULL);
        ftKb_SpecialN_800F9070(gobj);
        ftAnim_8006EBA4(gobj);
        ftCo_800CB110(gobj, true, da->specialn_jump_height);
    }
}

void ftKb_EatJump2_Anim(Fighter_GObj* gobj) {}

void ftKb_EatLanding_Anim(HSD_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        Fighter* fp = GET_FIGHTER(gobj);
        PAD_STACK(4);
        Fighter_ChangeMotionState(gobj, ftKb_MS_EatWait, Ft_MF_SkipModel, 0, 1,
                                  0, NULL);
        ftKb_SpecialN_800F9070(gobj);
        ftAnim_8006EBA4(gobj);
        ftCommon_8007E2F4(fp, 0x1FF);
    }
}

void ftKb_SpecialNLoop_IASA(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (fp->u.kb.xE4 != 0) {
        fp->u.kb.xE4--;
        return;
    }

    if ((fp->input.held_inputs & 0x200) == 0) {
        Fighter_ChangeMotionState(gobj, ftKb_MS_SpecialNEnd, 0, 0.0f, 1.0f,
                                  0.0f, NULL);
    }
}

void ftKb_SpecialAirNLoop_IASA(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (fp->u.kb.xE4 != 0) {
        fp->u.kb.xE4--;
        return;
    }

    if ((fp->input.held_inputs & 0x200) == 0) {
        Fighter_ChangeMotionState(gobj, ftKb_MS_SpecialAirNEnd, 0, 0.0f, 1.0f,
                                  0.0f, NULL);
    }
}

static inline bool ftKb_EatWait_ItemEat(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKb_DatAttrs* da = fp->dat_attrs;

    if (((fp->input.x668 & 0x200) && fp->target_item_gobj != NULL) ||
        ((fp->input.lstick.y < -da->specialn_y_axis_range_jump) &&
         fp->target_item_gobj != NULL))
    {
        Fighter_ChangeMotionState(gobj, 0x170, 2, 0.0f, 1.0f, 0.0f, NULL);
        fp->x2222_b2 = true;
        ftKb_SpecialN_800F9070(gobj);
        ftAnim_8006EBA4(gobj);
        ftCommon_8007E2F4(fp, 0x1FF);
        return true;
    }
    return false;
}

static inline bool ftKb_EatWait_ItemSpit(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if ((fp->input.x668 & 0x100) && fp->target_item_gobj != NULL) {
        Fighter_ChangeMotionState(gobj, 0x172, 0x12, 0.0f, 1.0f, 0.0f, NULL);
        fp->x2222_b2 = true;
        ftKb_SpecialN_800F9070(gobj);
        ftAnim_8006EBA4(gobj);
        ftCommon_8007E2F4(fp, 0x1FF);
        return true;
    }
    return false;
}

static inline bool ftKb_EatWait_FighterEat(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKb_DatAttrs* da = fp->dat_attrs;

    if (((fp->input.x668 & 0x200) && fp->victim_gobj != NULL) ||
        ((fp->input.lstick.y < -da->specialn_y_axis_range_jump) &&
         fp->victim_gobj != NULL))
    {
        Fighter_ChangeMotionState(gobj, 0x16F, 2, 0.0f, 1.0f, 0.0f, NULL);
        fp->x2222_b2 = true;
        ftKb_SpecialN_800F9070(gobj);
        ftAnim_8006EBA4(gobj);
        ftCommon_8007E2F4(fp, 0x1FF);
        return true;
    }
    return false;
}

static inline bool ftKb_EatWait_FighterSpit(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if ((fp->input.x668 & 0x100) && fp->victim_gobj != NULL) {
        Fighter_ChangeMotionState(gobj, 0x171, 0x12, 0.0f, 1.0f, 0.0f, NULL);
        fp->x2222_b2 = true;
        ftKb_SpecialN_800F9070(gobj);
        ftAnim_8006EBA4(gobj);
        ftCommon_8007E2F4(fp, 0x1FF);
        return true;
    }
    return false;
}

static inline bool ftKb_EatWait_Turn(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKb_DatAttrs* da = fp->dat_attrs;
    f32 stick_x = fp->input.lstick.x;
    f32 abs_x;

    if (stick_x < 0.0f) {
        abs_x = -stick_x;
    } else {
        abs_x = stick_x;
    }
    if (abs_x < da->specialn_x_axis_range_walk) {
        stick_x = 0.0f;
    }
    if (((stick_x < 0.0f) && (fp->facing_dir == 1.0f)) ||
        ((stick_x > 0.0f) && (fp->facing_dir == -1.0f)))
    {
        Fighter_ChangeMotionState(gobj, 0x16B, 0x92, 0.0f, 1.0f, 0.0f, NULL);
        ftKb_SpecialN_800F9070(gobj);
        ftAnim_8006EBA4(gobj);
        ftCommon_8007E2F4(fp, 0x1FF);
        return true;
    }
    return false;
}

void ftKb_EatWait_IASA(Fighter_GObj* gobj)
{
    enum ftCo_JumpInput jump;
    Fighter* fp = getFighter(gobj);
    s32 r0_2;
    PAD_STACK(0x68);

    if (fp->u.kb.xF4_b0) {
        if (ftKb_EatWait_ItemEat(gobj)) {
            return;
        }
        if (ftKb_EatWait_ItemSpit(gobj)) {
            return;
        }
    } else {
        if (ftKb_EatWait_FighterEat(gobj)) {
            return;
        }
        if (ftKb_EatWait_FighterSpit(gobj)) {
            return;
        }
    }
    if (!ftKb_EatWait_Turn(gobj)) {
        jump = ftCo_Jump_GetInput(gobj);
        if (jump != JumpInput_None) {
            Fighter* fp3 = GET_FIGHTER(gobj);
            fp3->mv.kb.specialhi.x4 = jump;
            fp3->mv.kb.specialhi.x0 = 0;
            Fighter_ChangeMotionState(gobj, 0x16C, 0x92, 0.0f, 1.0f, 0.0f,
                                      NULL);
            ftKb_SpecialN_800F9070(gobj);
            ftAnim_8006EBA4(gobj);
            ftCommon_8007E2F4(fp3, 0x1FF);
            r0_2 = 1;
        } else {
            r0_2 = 0;
        }
        if (r0_2 == 0 && ftWalkCommon_800DFC70(gobj)) {
            Fighter* fp4 = GET_FIGHTER(gobj);
            ftWalkCommon_800DFCA4(
                gobj, 0x168, 0x10, 0.0f, fp4->u.kb.xE8, fp4->u.kb.xEC,
                fp4->u.kb.xF0, fp4->co_attrs.slow_walk_max,
                fp4->co_attrs.mid_walk_point, fp4->co_attrs.fast_walk_min,
                ((ftKb_DatAttrs*) fp4->dat_attrs)->specialn_walk_speed);
            ftCommon_8007E2F4(fp4, 0x1FF);
        }
    }
}

static inline bool ftKb_SpecialAirNCaptureWait_ItemEat(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKb_DatAttrs* da = fp->dat_attrs;

    if (((fp->input.x668 & 0x200) && fp->target_item_gobj != NULL) ||
        ((fp->input.lstick.y < -da->specialn_y_axis_range_jump) &&
         fp->target_item_gobj != NULL))
    {
        Fighter_ChangeMotionState(gobj, 0x17B, 2, 0.0f, 1.0f, 0.0f, NULL);
        fp->x2222_b2 = true;
        ftKb_SpecialN_800F9070(gobj);
        ftAnim_8006EBA4(gobj);
        ftCommon_8007E2F4(fp, 0x1FF);
        return true;
    }
    return false;
}

static inline bool ftKb_SpecialAirNCaptureWait_ItemSpit(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if ((fp->input.x668 & 0x100) && fp->target_item_gobj != NULL) {
        Fighter_ChangeMotionState(gobj, 0x17D, 0x12, 0.0f, 1.0f, 0.0f, NULL);
        fp->x2222_b2 = true;
        ftKb_SpecialN_800F9070(gobj);
        ftAnim_8006EBA4(gobj);
        ftCommon_8007E2F4(fp, 0x1FF);
        return true;
    }
    return false;
}

static inline bool ftKb_SpecialAirNCaptureWait_FighterEat(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKb_DatAttrs* da = fp->dat_attrs;

    if (((fp->input.x668 & 0x200) && fp->victim_gobj != NULL) ||
        ((fp->input.lstick.y < -da->specialn_y_axis_range_jump) &&
         fp->victim_gobj != NULL))
    {
        Fighter_ChangeMotionState(gobj, 0x17A, 2, 0.0f, 1.0f, 0.0f, NULL);
        fp->x2222_b2 = true;
        ftKb_SpecialN_800F9070(gobj);
        ftAnim_8006EBA4(gobj);
        ftCommon_8007E2F4(fp, 0x1FF);
        return true;
    }
    return false;
}

static inline bool ftKb_SpecialAirNCaptureWait_FighterSpit(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if ((fp->input.x668 & 0x100) && fp->victim_gobj != NULL) {
        Fighter_ChangeMotionState(gobj, 0x17C, 0x12, 0.0f, 1.0f, 0.0f, NULL);
        fp->x2222_b2 = true;
        ftKb_SpecialN_800F9070(gobj);
        ftAnim_8006EBA4(gobj);
        ftCommon_8007E2F4(fp, 0x1FF);
        return true;
    }
    return false;
}

static inline bool ftKb_SpecialAirNCaptureWait_Turn(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKb_DatAttrs* da = fp->dat_attrs;
    f32 stick_x = fp->input.lstick.x;
    f32 abs_x;

    if (stick_x < 0.0f) {
        abs_x = -stick_x;
    } else {
        abs_x = stick_x;
    }
    if (abs_x < da->specialn_x_axis_range_walk) {
        stick_x = 0.0f;
    }
    if (((stick_x < 0.0f) && (fp->facing_dir == 1.0f)) ||
        ((stick_x > 0.0f) && (fp->facing_dir == -1.0f)))
    {
        Fighter_ChangeMotionState(gobj, 0x17E, 0x92, 0.0f, 1.0f, 0.0f, NULL);
        ftKb_SpecialN_800F9070(gobj);
        ftAnim_8006EBA4(gobj);
        ftCommon_8007E2F4(fp, 0x1FF);
        return true;
    }
    return false;
}

void ftKb_SpecialAirNCaptureWait_IASA(Fighter_GObj* gobj)
{
    Fighter* fp = getFighter(gobj);
    Fighter_GObj* gobj2 = gobj;
    PAD_STACK(0x38);

    if (fp->u.kb.xF4_b0) {
        if (ftKb_SpecialAirNCaptureWait_ItemEat(gobj2)) {
            return;
        }
        if (ftKb_SpecialAirNCaptureWait_ItemSpit(gobj2)) {
            return;
        }
    } else {
        if (ftKb_SpecialAirNCaptureWait_FighterEat(gobj2)) {
            return;
        }
        if (ftKb_SpecialAirNCaptureWait_FighterSpit(gobj2)) {
            return;
        }
    }
    if (!ftKb_SpecialAirNCaptureWait_Turn(gobj2)) {
        return;
    }
}

void ftKb_EatWalk_IASA(Fighter_GObj* gobj)
{
    ftCo_JumpInput jump_input;
    s32 var;
    PAD_STACK(8);

    jump_input = ftCo_Jump_GetInput(gobj);
    if (jump_input != JumpInput_None) {
        Fighter* fp = GET_FIGHTER(gobj);
        fp->mv.kb.specialhi.x4 = jump_input;
        fp->mv.kb.specialhi.x0 = 0;
        Fighter_ChangeMotionState(gobj, ftKb_MS_EatJump1,
                                  Ft_MF_KeepGfx | Ft_MF_SkipModel |
                                      Ft_MF_SkipMatAnim,
                                  0, 1, 0, NULL);
        ftKb_SpecialN_800F9070(gobj);
        ftAnim_8006EBA4(gobj);
        ftCommon_8007E2F4(fp, 0x1FF);
        var = 1;
    } else {
        var = 0;
    }
    if (var == 0) {
        if (ft_8008A1FC(gobj)) {
            Fighter* fp = GET_FIGHTER(gobj);
            Fighter_ChangeMotionState(gobj, ftKb_MS_EatWait, Ft_MF_SkipModel,
                                      0, 1, 0, NULL);
            ftKb_SpecialN_800F9070(gobj);
            ftAnim_8006EBA4(gobj);
            ftCommon_8007E2F4(fp, 0x1FF);
            return;
        }
        ftWalkCommon_800DFEC8(gobj, fn_800F64C8);
    }
}

void ftKb_EatJump1_IASA(Fighter_GObj* gobj)
{
    ftCo_KneeBend_Check_ShortHop(gobj);
}

void ftKb_SpecialN_Phys(Fighter_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftKb_SpecialAirN_Phys(Fighter_GObj* gobj)
{
    ft_80084EEC(gobj);
}

void ftKb_SpecialNLoop_Phys(HSD_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftKb_SpecialAirNLoop_Phys(Fighter_GObj* gobj)
{
    ft_80084EEC(gobj);
}

void ftKb_SpecialNEnd_Phys(Fighter_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftKb_SpecialAirNEnd_Phys(Fighter_GObj* gobj)
{
    ft_80084EEC(gobj);
}

void ftKb_SpecialNCapture0_Phys(Fighter_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftKb_SpecialNCapture_Phys(Fighter_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftKb_SpecialNCapture1_Phys(Fighter_GObj* gobj)
{
    ft_80084EEC(gobj);
}

void ftKb_SpecialAirNCapture_Phys(Fighter_GObj* gobj)
{
    ft_80084EEC(gobj);
}

void ftKb_Eat_Phys(HSD_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftKb_SpecialAirNCaptured_Phys(Fighter_GObj* gobj)
{
    ft_80084EEC(gobj);
}

void ftKb_EatWait_Phys(Fighter_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftKb_SpecialAirNCaptureWait_Phys(Fighter_GObj* gobj)
{
    ft_80084EEC(gobj);
}

void ftKb_SpecialNSpit0_Phys(Fighter_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftKb_SpecialNSpit_Phys(Fighter_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftKb_SpecialNSpit1_Phys(Fighter_GObj* gobj)
{
    ft_80084EEC(gobj);
}

void ftKb_SpecialAirNSpit_Phys(Fighter_GObj* gobj)
{
    ft_80084EEC(gobj);
}

void ftKb_SpecialNDrink0_Phys(Fighter_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftKb_SpecialNDrink_Phys(Fighter_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftKb_SpecialNDrink1_Phys(Fighter_GObj* gobj)
{
    ft_80084EEC(gobj);
}

void ftKb_SpecialAirNDrink_Phys(Fighter_GObj* gobj)
{
    ft_80084EEC(gobj);
}

void ftKb_EatTurn_Phys(Fighter_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftKb_SpecialAirNCaptureTurn_Phys(Fighter_GObj* gobj)
{
    ft_80084EEC(gobj);
}

void ftKb_EatWalk_Phys(Fighter_GObj* gobj)
{
    ftWalkCommon_800E0060(gobj);
}

void ftKb_EatJump1_Phys(Fighter_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftKb_EatJump2_Phys(Fighter_GObj* gobj)
{
    ftCo_Jump_Phys_Inner(gobj);
}

void ftKb_EatLanding_Phys(Fighter_GObj* gobj)
{
    ft_80084F3C(gobj);
}

void ftKb_SpecialN_Coll(Fighter_GObj* gobj)
{
    ft_8008403C(gobj, fn_800F6588);
}

void ftKb_SpecialAirN_Coll(Fighter_GObj* gobj)
{
    ft_80082C74(gobj, fn_800F6638);
}

void ftKb_SpecialNLoop_Coll(Fighter_GObj* gobj)
{
    ft_8008403C(gobj, fn_800F66E8);
}

void ftKb_SpecialAirNLoop_Coll(Fighter_GObj* gobj)
{
    ft_80082C74(gobj, fn_800F6798);
}

void ftKb_SpecialNEnd_Coll(Fighter_GObj* gobj)
{
    ft_8008403C(gobj, fn_800F6848);
}

void ftKb_SpecialAirNEnd_Coll(Fighter_GObj* gobj)
{
    ft_80082C74(gobj, fn_800F68A8);
}

void ftKb_SpecialNCapture0_Coll(Fighter_GObj* gobj)
{
    ft_8008403C(gobj, fn_800F6908);
}

void ftKb_SpecialNCapture_Coll(Fighter_GObj* gobj)
{
    ft_8008403C(gobj, fn_800F697C);
}

void ftKb_SpecialNCapture1_Coll(Fighter_GObj* gobj)
{
    ft_80082C74(gobj, fn_800F69E8);
}

void ftKb_SpecialAirNCapture_Coll(Fighter_GObj* gobj)
{
    ft_80082C74(gobj, fn_800F6A5C);
}

void ftKb_Eat_Coll(HSD_GObj* gobj)
{
    ft_8008403C(gobj, fn_800F6AC8);
}

void ftKb_SpecialAirNCaptured_Coll(Fighter_GObj* gobj)
{
    ft_80082C74(gobj, fn_800F6B3C);
}

void ftKb_EatWait_Coll(Fighter_GObj* gobj)
{
    ft_8008403C(gobj, ftKb_SpecialS_800F6BB0);
}

void ftKb_SpecialAirNCaptureWait_Coll(Fighter_GObj* gobj)
{
    ft_80082C74(gobj, fn_800F6528);
}

void ftKb_SpecialNSpit0_Coll(Fighter_GObj* gobj)
{
    ft_8008403C(gobj, fn_800F6C24);
}

void ftKb_SpecialNSpit_Coll(Fighter_GObj* gobj)
{
    ft_8008403C(gobj, fn_800F6C98);
}

void ftKb_SpecialNSpit1_Coll(Fighter_GObj* gobj)
{
    ft_80082C74(gobj, fn_800F6D0C);
}

void ftKb_SpecialAirNSpit_Coll(Fighter_GObj* gobj)
{
    ft_80082C74(gobj, fn_800F6D80);
}

void ftKb_SpecialNDrink0_Coll(Fighter_GObj* gobj)
{
    ft_8008403C(gobj, fn_800F6DF4);
}

void ftKb_SpecialNDrink_Coll(Fighter_GObj* gobj)
{
    ft_8008403C(gobj, fn_800F6E68);
}

void ftKb_SpecialNDrink1_Coll(Fighter_GObj* gobj)
{
    ft_80082C74(gobj, fn_800F6EDC);
}

void ftKb_SpecialAirNDrink_Coll(Fighter_GObj* gobj)
{
    ft_80082C74(gobj, fn_800F6F50);
}

void ftKb_EatTurn_Coll(Fighter_GObj* gobj)
{
    ft_8008403C(gobj, fn_800F6FC4);
}

void ftKb_SpecialAirNCaptureTurn_Coll(Fighter_GObj* gobj)
{
    ft_80082C74(gobj, fn_800F702C);
}

void ftKb_EatWalk_Coll(Fighter_GObj* gobj)
{
    ft_8008403C(gobj, fn_800F6450);
}

void ftKb_EatJump1_Coll(Fighter_GObj* gobj)
{
    ft_8008403C(gobj, fn_800F6450);
}

void ftKb_EatJump2_Coll(Fighter_GObj* gobj)
{
    ft_80082C74(gobj, fn_800F6528);
}

void ftKb_EatLanding_Coll(Fighter_GObj* gobj)
{
    ft_8008403C(gobj, fn_800F6450);
}

void ftKb_SpecialN_800F9070(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->death3_cb = ftKb_Init_800EE74C;
    fp->death1_cb = ftKb_Init_800EE7B8;
}

void ftKb_SpecialN_800F9090(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->target_item_gobj != NULL && fp->kind == FTKIND_KIRBY &&
        fp->u.kb.hat.kind == FTKIND_KIRBY)
    {
        bool capturing = false;
        if (fp->motion_id == ftKb_MS_SpecialNCapture1 ||
            fp->motion_id == ftKb_MS_SpecialAirNCapture1)
        {
            capturing = true;
        }
        it_802F28C8(fp->target_item_gobj, capturing, 0);
        fp->x1A64 = NULL;
        fp->target_item_gobj = NULL;
    }
}
