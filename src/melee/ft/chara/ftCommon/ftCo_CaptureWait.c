#include "ftCo_Attack100.h"
#include "ftCo_CaptureCut.h"

#include "ft/fighter.h"
#include "ft/ft_081B.h"
#include "ft/ftcoll.h"
#include "ft/ftcommon.h"
#include "ft/ftparts.h"
#include "ft/inlines.h"
#include "it/items/itlinkhookshot.h"
#include "it/items/itsamusgrapple.h"

#include <melee/ft/chara/ftYoshi/ftyoshi.h>

typedef struct {
    u8 pad_1A4C[0x1A4C];
    f32 x1A4C; // 0x1A4C
    u8 pad_1A58[0x1A58 - 0x1A50];
    void* x1A58; // 0x1A58
    u8 pad_2340[0x2340 - 0x1A5C];
    f32 x2340; // 0x2340
    f32 x2344; // 0x2344
    s32 x2348; // 0x2348
    u8 x234C;  // 0x234C
} FighterOverlay;

bool fn_800DAD18(Fighter_GObj*);
static void fn_800DBBF8(Fighter_GObj*);

void fn_800DB5D8(Fighter_GObj* gobj)
{
    ftHurtboxInit sp18;
    Fighter* fp = GET_FIGHTER(gobj);
    Fighter* victim_fp = GET_FIGHTER(fp->victim_gobj);
    if (victim_fp->kind == FTKIND_YOSHI) {
        fp->invisible = true;
        fp->accessory1_cb = ftCo_800DB464;
        ftColl_8007B0C0(gobj, HurtCapsule_Intangible);
        sp18.bone_idx = ftParts_GetBoneIndex(fp, FtPart_XRotN);
        sp18.height = HurtHeight_Mid;
        sp18.is_grabbable = false;
        sp18.a_offset.x = sp18.a_offset.y = sp18.a_offset.z = 0.0F;
        sp18.b_offset.x = sp18.b_offset.y = sp18.b_offset.z = 0.0F;
        sp18.scale =
            ftYs_Init_8012BAC0(victim_fp) / ftCommon_GetModelScale(fp);
        ftColl_HurtboxInit(fp, fp->hurt_capsules, &sp18);
    }
    ftCommon_8007E2F4(fp, 0x1FF);
}

void fn_800DB6C8(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    Fighter* victim_fp = GET_FIGHTER(fp->victim_gobj);

    if (fp->motion_id == ftCo_MS_CapturePulledHi) {
        fn_800DB790(gobj);
    } else {
        fn_800DBAE4(gobj);
    }

    switch (victim_fp->kind) {
    case FTKIND_YOSHI:
        ftCo_800DB368(victim_fp, fp);
        break;
    case FTKIND_LINK:
    case FTKIND_CLINK:
        if (victim_fp->u.lk.xC != NULL) {
            it_802A7840((HSD_GObj*) victim_fp->u.lk.xC);
        }
        break;
    case FTKIND_SAMUS:
        if (victim_fp->u.ss.x223C != NULL) {
            it_802BAA94(victim_fp->u.ss.x223C);
        }
        break;
    default:
        break;
    }

    ftCommon_8007EBAC(fp, 3, 0);
}

void fn_800DB790(Fighter_GObj* gobj)
{
    ftHurtboxInit hurt;
    Fighter* victim_fp;
    Fighter* fp;

    Fighter_ChangeMotionState(gobj, ftCo_MS_CaptureWaitHi, 0, 0.0F, 1.0F, 0.0F,
                              NULL);

    if ((victim_fp = GET_FIGHTER((fp = GET_FIGHTER(gobj))->victim_gobj))
            ->kind == FTKIND_YOSHI)
    {
        fp->invisible = true;
        fp->accessory1_cb = ftCo_800DB464;
        ftColl_8007B0C0(gobj, HurtCapsule_Intangible);
        hurt.bone_idx = ftParts_GetBoneIndex(fp, FtPart_XRotN);
        hurt.height = HurtHeight_Mid;
        hurt.is_grabbable = false;
        hurt.a_offset.x = hurt.a_offset.y = hurt.a_offset.z = 0.0F;
        hurt.b_offset.x = hurt.b_offset.y = hurt.b_offset.z = 0.0F;
        hurt.scale =
            ftYs_Init_8012BAC0(victim_fp) / ftCommon_GetModelScale(fp);
        ftColl_HurtboxInit(fp, fp->hurt_capsules, &hurt);
    }

    ftCommon_8007E2F4(fp, 0x1FF);
}

void fn_800DB8A4(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->mv.co.capturewait.x0 += 1.0;
    fp->grab_timer -= p_ftCommonData->grab_timer_decrement;
    fp->mv.co.capturewait.x8 = ftCommon_GrabMash(fp, p_ftCommonData->x3A8);
}

void ftCo_CaptureWaitHi_Anim(Fighter_GObj* gobj)
{
    Fighter* fp;
    FighterOverlay* fp_ovl;
    f32 dec;
    f32 zero;
    fp = GET_FIGHTER(gobj);
    fp_ovl = (FighterOverlay*) fp;
    fp_ovl->x2340 += 1.0;
    fp_ovl->x1A4C -= p_ftCommonData->grab_timer_decrement;
    fp_ovl->x2348 =
        ftCommon_GrabMash(fp, *(f32*) ((u8*) p_ftCommonData + 0x3A8));
    if (fp_ovl->x1A4C <= 0.0F) {
        ftCo_800DA698(fp_ovl->x1A58, 0);
        if (fp_ovl->x234C != 0 || fn_800DC044(gobj)) {
            fn_800DC070(gobj);
            return;
        }

        ftCo_CaptureCut_Enter(gobj);
        return;
    }

    zero = 0.0F;
    if (fp_ovl->x2344 != zero) {
        dec = 1.0F;
        fp_ovl->x2344 -= dec;
        if (fp_ovl->x2344 <= zero && fp_ovl->x2348 == 0) {
            ftAnim_SetAnimRate(gobj, dec);
            fp_ovl->x2344 = 0.0F;
        }
    }

    if (*(volatile f32*) &fp_ovl->x2344 <= 0.0F && fp_ovl->x2348 != 0) {
        fp_ovl->x2344 = *(f32*) ((u8*) p_ftCommonData + 0x3B0);
        ftAnim_SetAnimRate(gobj, *(f32*) ((u8*) p_ftCommonData + 0x3B4));
    }
}

void ftCo_CaptureWaitHi_IASA(Fighter_GObj* gobj)
{
    fn_800DC014(gobj);
}

void ftCo_CaptureWaitHi_Phys(Fighter_GObj* gobj)
{
    fn_800DAD18(gobj);
}

void ftCo_CaptureWaitHi_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (!fp->x2226_b2) {
        ft_80083C00(gobj, fn_800DBAC4);
    }
}

void fn_800DBAC4(Fighter_GObj* gobj)
{
    fn_800DBBF8(gobj);
}

void fn_800DBAE4(Fighter_GObj* gobj)
{
    ftHurtboxInit hurt;
    Fighter* victim_fp;
    Fighter* fp;

    Fighter_ChangeMotionState(gobj, ftCo_MS_CaptureWaitLw, 0, 0.0F, 1.0F, 0.0F,
                              NULL);

    if ((victim_fp = GET_FIGHTER((fp = GET_FIGHTER(gobj))->victim_gobj))
            ->kind == FTKIND_YOSHI)
    {
        fp->invisible = true;
        fp->accessory1_cb = ftCo_800DB464;
        ftColl_8007B0C0(gobj, HurtCapsule_Intangible);
        hurt.bone_idx = ftParts_GetBoneIndex(fp, FtPart_XRotN);
        hurt.height = HurtHeight_Mid;
        hurt.is_grabbable = false;
        hurt.a_offset.x = hurt.a_offset.y = hurt.a_offset.z = 0.0F;
        hurt.b_offset.x = hurt.b_offset.y = hurt.b_offset.z = 0.0F;
        hurt.scale =
            ftYs_Init_8012BAC0(victim_fp) / ftCommon_GetModelScale(fp);
        ftColl_HurtboxInit(fp, fp->hurt_capsules, &hurt);
    }

    ftCommon_8007E2F4(fp, 0x1FF);
}

static inline void fn_800DBBF8_noinline(Fighter_GObj* gobj1, Fighter* gobj2)
{
    Fighter_GObj* fighter = gobj1;
    fn_800DAA40(fighter, gobj2->victim_gobj);
}

static void fn_800DBBF8(Fighter_GObj* gobj)
{
    ftHurtboxInit hurt;
    Fighter* victim_fp;
    Fighter* fp;
    Fighter* fp_before = GET_FIGHTER(gobj);
    f32 model_scale;

    ftCommon_8007D7FC(fp_before);
    Fighter_ChangeMotionState(gobj, ftCo_MS_CaptureWaitLw, Ft_MF_UpdateCmd,
                              fp_before->cur_anim_frame, 1.0F, 0.0F, NULL);

    if ((victim_fp = GET_FIGHTER((fp = GET_FIGHTER(gobj))->victim_gobj))
            ->kind == FTKIND_YOSHI)
    {
        fp->invisible = true;
        fp->accessory1_cb = ftCo_800DB464;
        ftColl_8007B0C0(gobj, HurtCapsule_Intangible);
        hurt.bone_idx = ftParts_GetBoneIndex(fp, FtPart_XRotN);
        hurt.height = true;
        hurt.is_grabbable = false;
        hurt.a_offset.x = hurt.a_offset.y = hurt.a_offset.z = 0.0F;
        hurt.b_offset.x = hurt.b_offset.y = hurt.b_offset.z = 0.0F;
        model_scale = ftCommon_GetModelScale(fp);
        hurt.scale = ftYs_Init_8012BAC0(victim_fp) / model_scale;
        ftColl_HurtboxInit(fp, fp->hurt_capsules, &hurt);
    }

    ftCommon_8007E2F4(fp, 0x1FF);
    fn_800DBBF8_noinline(gobj, fp_before);
}

void ftCo_CaptureWaitLw_Anim(Fighter_GObj* gobj)
{
    ftCo_CaptureWaitHi_Anim(gobj);
}

void ftCo_CaptureWaitLw_IASA(Fighter_GObj* gobj)
{
    fn_800DC014(gobj);
}

/// #ftCo_CaptureWaitLw_Phys

static inline void ftCo_CaptureWaitLw_Phys_inline(Fighter_GObj* gobj)
{
    register Fighter* temp_r31;
    temp_r31 = GET_FIGHTER(gobj);

    ftCommon_8007D5D4(temp_r31);
    ftCommon_UnlockECB(temp_r31);
    Fighter_ChangeMotionState(gobj, ftCo_MS_CaptureWaitHi, Ft_MF_UpdateCmd,
                              temp_r31->cur_anim_frame, 1.0F, 0.0F, NULL);
    fn_800DB5D8(gobj);
    fn_800DAA40(gobj, temp_r31->victim_gobj);
    if (!GET_FIGHTER(gobj)->x2226_b2) {
        ft_80083C00(gobj, fn_800DBAC4);
    }
    HSD_JObjSetTranslate(GET_JOBJ(gobj), &temp_r31->cur_pos);
}

void ftCo_CaptureWaitLw_Phys(Fighter_GObj* gobj)
{
    PAD_STACK(8);

    if (fn_800DAD18(gobj)) {
        ftCo_CaptureWaitLw_Phys_inline(gobj);
    }
}

void ftCo_CaptureWaitLw_Coll(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (!fp->x2226_b2) {
        ft_8008403C(gobj, fn_800DBED4);
    }
}

static inline void fn_800DBED4_inline(Fighter_GObj* gobj)
{
    Fighter* temp_r31 = GET_FIGHTER(gobj);

    ftCommon_8007D5D4(temp_r31);
    ftCommon_UnlockECB(temp_r31);
    Fighter_ChangeMotionState(gobj, ftCo_MS_CaptureWaitHi, Ft_MF_UpdateCmd,
                              temp_r31->cur_anim_frame, 1.0F, 0.0F, NULL);
    fn_800DB5D8(gobj);
    fn_800DAA40(gobj, temp_r31->victim_gobj);
    if (!GET_FIGHTER(gobj)->x2226_b2) {
        ft_80083C00(gobj, fn_800DBAC4);
    }
    HSD_JObjSetTranslate(GET_JOBJ(gobj), &temp_r31->cur_pos);
}

void fn_800DBED4(Fighter_GObj* gobj)
{
    PAD_STACK(4);
    fn_800DBED4_inline(gobj);
}

void fn_800DC014(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->mv.co.capturewait.x0 < p_ftCommonData->x3AC) {
        if (fp->input.x668 & HSD_PAD_XY) {
            fp->mv.co.capturewait.xC = true;
        }
    }
}

bool fn_800DC044(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->input.lstick.y >= p_ftCommonData->tap_jump_threshold) {
        return true;
    }
    return false;
}
