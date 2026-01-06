#include "ftYs_Guard.h"

#include "ftYs_Init.h"
#include "ftYs_SpecialN.h"

#include <placeholder.h>

#include "ef/efasync.h"
#include "ft/fighter.h"

#include "ft/forward.h"

#include "ft/ft_0877.h"
#include "ft/ft_0892.h"
#include "ft/ftanim.h"
#include "ft/ftcoll.h"
#include "ft/ftparts.h"
#include "ft/types.h"

#include "ftCommon/forward.h"

#include "ftCommon/ftCo_Attack100.h"
#include "ftCommon/ftCo_Escape.h"
#include "ftCommon/ftCo_Guard.h"
#include "ftCommon/ftCo_ItemThrow.h"
#include "ftCommon/ftCo_Pass.h"
#include "ftYoshi/types.h"

#include <baselib/forward.h>

char ftYs_Init_DatFilename[] = "PlYs.dat";
char ftYs_Init_DataName[] = "ftDataYoshi";
char ftYs_Unk2_803CEAB0[] = "PlYsNr.dat";
char ftYs_Unk2_803CEABC[] = "PlyYoshi5K_Share_joint";
char ftYs_Unk2_803CEAD4[] = "PlyYoshi5K_Share_matanim_joint";
char ftYs_Unk2_803CEAF4[] = "PlYsRe.dat";
char ftYs_Unk2_803CEB00[] = "PlyYoshi5KRe_Share_joint";
char ftYs_Unk2_803CEB1C[] = "PlyYoshi5KRe_Share_matanim_joint";
char ftYs_Unk2_803CEB40[] = "PlYsBu.dat";
char ftYs_Unk2_803CEB4C[] = "PlyYoshi5KBu_Share_joint";
char ftYs_Unk2_803CEB68[] = "PlyYoshi5KBu_Share_matanim_joint";
char ftYs_Unk2_803CEB8C[] = "PlYsYe.dat";
char ftYs_Unk2_803CEB98[] = "PlyYoshi5KYe_Share_joint";
char ftYs_Unk2_803CEBB4[] = "PlyYoshi5KYe_Share_matanim_joint";
char ftYs_Unk2_803CEBD8[] = "PlYsPi.dat";
char ftYs_Unk2_803CEBE4[] = "PlyYoshi5KPi_Share_joint";
char ftYs_Unk2_803CEC00[] = "PlyYoshi5KPi_Share_matanim_joint";
char ftYs_Unk2_803CEC24[] = "PlYsAq.dat";
char ftYs_Unk2_803CEC30[] = "PlyYoshi5KAq_Share_joint";
char ftYs_Unk2_803CEC4C[] = "PlyYoshi5KAq_Share_matanim_joint";
char ftYs_Init_AnimDatFilename[] = "PlYsAJ.dat";

Fighter_DemoStrings ftYs_Init_DemoMotionFilenames = {
    "ftDemoResultMotionFileYoshi",
    "ftDemoIntroMotionFileYoshi",
    "ftDemoEndingMotionFileYoshi",
    "ftDemoViWaitMotionFileYoshi",
};

Fighter_CostumeStrings ftYs_Init_CostumeStrings[] = {
    { ftYs_Unk2_803CEAB0, ftYs_Unk2_803CEABC, ftYs_Unk2_803CEAD4 },
    { ftYs_Unk2_803CEAF4, ftYs_Unk2_803CEB00, ftYs_Unk2_803CEB1C },
    { ftYs_Unk2_803CEB40, ftYs_Unk2_803CEB4C, ftYs_Unk2_803CEB68 },
    { ftYs_Unk2_803CEB8C, ftYs_Unk2_803CEB98, ftYs_Unk2_803CEBB4 },
    { ftYs_Unk2_803CEBD8, ftYs_Unk2_803CEBE4, ftYs_Unk2_803CEC00 },
    { ftYs_Unk2_803CEC24, ftYs_Unk2_803CEC30, ftYs_Unk2_803CEC4C },
};

void ftYs_Init_8012BDA0(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    PAD_STACK(4 * 2);
    {
        ftHurtboxInit hurt;
        PAD_STACK(4 * 4);
        ftColl_8007B0C0(gobj, Intangible);
        hurt.bone_idx = fp->ft_data->x8->x11;
        hurt.height = HurtHeight_Mid;
        hurt.is_grabbable = true;
        hurt.a_offset = hurt.b_offset = ftYs_Unk1_803B75C0;
        hurt.scale = 1;
        ftColl_HurtboxInit(fp, &fp->hurt_capsules[0], &hurt);
    }
}

void ftYs_Init_8012BE3C(HSD_GObj* gobj)
{
    /// @todo Some kind of inline here.
    ftCo_DatAttrs_xBC_t* xBC;
    Fighter* fp = GET_FIGHTER(gobj);
    ftParts_80074B0C(gobj, 0, 0);
    ftColl_8007B0C0(gobj, 0);
    xBC = &fp->co_attrs.xBC;
    {
        Fighter_Part part = ftParts_GetBoneIndex(fp, 4);
        HSD_JObj* jobj = fp->parts[part].joint;
        Fighter* fp1 = GET_FIGHTER(gobj);
        efAsync_Spawn(gobj, &fp1->x60C, 4, 1231, jobj, xBC);
    }
}

static void ftYs_Init_8012B8A4_no_inline_2(HSD_GObj* gobj)
{
    ftYs_Init_8012B8A4(gobj);
}

static void ftYs_Init_8012B8A4_no_inline(HSD_GObj* gobj)
{
    ftYs_Init_8012B8A4_no_inline_2(gobj);
}

static void ftYs_Init_8012BECC_sub(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    struct {
        u8 _pad[4];
        Vec3 v;
    } s;

    ftColl_8007B0C0(gobj, HurtCapsule_Disabled);
    fp->mv.ys.guard.xC = false;
    fp->mv.ys.guard.x0 = 0;
    fp->mv.ys.guard.x10 = p_ftCommonData->x268;
    fp->mv.ys.guard.x24 = 0;
    fp->mv.ys.guard.x20 = 0;
    s.v.x = s.v.y = s.v.z = 0;
    HSD_JObjSetTranslate(fp->parts[fp->ft_data->x8->x11].joint, &s.v);
    ftYs_Init_8012B8A4_no_inline(gobj);
    ftCo_80091D58(fp);
    ft_PlaySFX(fp, 0x6E, 0x7F, 0x40);
}

void ftYs_Init_8012BECC(Fighter_GObj* gobj)
{
    PAD_STACK(8);
    Fighter_ChangeMotionState(gobj, ftYs_MS_GuardOn_0, 0, 0.0f, 1.0f, 0.0f,
                              NULL);
    ftAnim_8006EBA4(gobj);
    ftCo_80092450(gobj);
    ftYs_Init_8012BECC_sub(gobj);
}

static inline void spawnEffect(HSD_GObj* gobj)
{
    HSD_JObj* jobj;
    Fighter_Part part;
    Fighter* fp2;
    ftCo_DatAttrs_xBC_t* co_xBC;
    Fighter* fp;
    fp = GET_FIGHTER(gobj);
    ftParts_80074B0C(gobj, 0, 0);
    ftColl_8007B0C0(gobj, 0);

    co_xBC = &fp->co_attrs.xBC;
    part = ftParts_GetBoneIndex(fp, FtPart_HipN);
    fp2 = GET_FIGHTER(gobj);
    jobj = fp->parts[part].joint;

    efAsync_Spawn(gobj, &fp2->x60C, FtPart_HipN, 1231, jobj, co_xBC);
}

void ftYs_GuardOn_0_Anim(HSD_GObj* gobj)
{
    u8 _[8];
    Fighter* fp = GET_FIGHTER(gobj);

    fp->mv.ys.guard.x0 += 1.0F;
    ftCo_80092BCC(gobj);
    if (ftCo_800925A4(gobj)) {
        spawnEffect(gobj);
    } else if (!ftAnim_IsFramesRemaining(gobj)) {
        ftCo_800928CC(gobj);
    } else {
        ftYs_Init_8012B8A4(gobj);
    }
}

void ftYs_GuardOn_0_IASA(HSD_GObj* gobj)
{
    RETURN_IF(ftCo_80093694(gobj));
    RETURN_IF(ftCo_8009515C(gobj));
    RETURN_IF(ftCo_80099794(gobj));
    RETURN_IF(ftCo_8009917C(gobj));
    RETURN_IF(ftCo_Catch_CheckInput(gobj));
    RETURN_IF(ftCo_8009A080(gobj));
}

void ftYs_GuardOn_0_Phys(HSD_GObj* arg0)
{
    ftCo_GuardOn_Phys(arg0);
}

void ftYs_GuardOn_0_Coll(HSD_GObj* arg0)
{
    ftCo_GuardOn_Coll(arg0);
}

static inline void inlineA0(Fighter_GObj* gobj)
{
    FORCE_PAD_STACK(4 * 4);
    {
        Fighter* fp = GET_FIGHTER(gobj);
        ftHurtboxInit hurt;
        ftColl_8007B0C0(gobj, Intangible);
        hurt.bone_idx = fp->ft_data->x8->x11;
        hurt.height = HurtHeight_Mid;
        hurt.is_grabbable = true;
        hurt.a_offset = hurt.b_offset = ftYs_Unk1_803B75C0;
        hurt.scale = 1;
        ftColl_HurtboxInit(fp, fp->hurt_capsules, &hurt);
    }
}

void ftYs_Shield_8012C1D4(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    PAD_STACK(4 * 2);
    Fighter_ChangeMotionState(gobj, ftYs_MS_GuardHold, Ft_MF_None, 0, 1, 0,
                              NULL);
    ftAnim_8006FA58(fp, FtPart_TransN, fp->x108_costume_joint->child);
    ftParts_80074B0C(gobj, 0, 1);
    inlineA0(gobj);
    ftCo_80092450(gobj);
    fp->x221E_b4 = false;
    ftYs_Init_8012B8A4(gobj);
    ftCo_80091D58(fp);
}

void ftYs_GuardHold_Anim(HSD_GObj* gobj)
{
    u8 _[12];

    Fighter* fp = GET_FIGHTER(gobj);

    fp->mv.ys.guard.x0 += 1.0F;
    ftCo_80092BCC(gobj);

    if (ftCo_800925A4(gobj)) {
        spawnEffect(gobj);
    } else if (fp->mv.ys.guard.xC || (!fp->x221B_b0 && !fp->reflecting)) {
        ftCo_80092BE8(gobj);
    } else {
        ftYs_Init_8012B8A4(gobj);
    }
}

void ftYs_GuardHold_IASA(HSD_GObj* gobj)
{
    if (!ftCo_8009515C(gobj) && !ftCo_80099794(gobj) && !ftCo_8009917C(gobj) &&
        !ftCo_Catch_CheckInput(gobj) && !ftCo_8009A080(gobj))
    {
        return;
    }
}

void ftYs_GuardHold_Phys(HSD_GObj* arg0)
{
    ftCo_Guard_Phys(arg0);
}

void ftYs_GuardHold_Coll(HSD_GObj* arg0)
{
    ftCo_Guard_Coll(arg0);
}

void ftYs_Shield_8012C49C(HSD_GObj* gobj)
{
    Fighter_ChangeMotionState(gobj, 343, 0, 0, 1.0F, 0, NULL);

    {
        Fighter* fp0 = GET_FIGHTER(gobj);
        ftParts_80074B0C(gobj, 0, 0);
        ftColl_8007B0C0(gobj, 0);

        {
            u8 _[8];

            ftCo_DatAttrs_xBC_t* co_xBC = &fp0->co_attrs.xBC;

            ssize_t bone_idx = ftParts_GetBoneIndex(fp0, 4);
            Fighter* fp1 = GET_FIGHTER(gobj);

            /// @todo Why is this still using @c fp0?
            HSD_JObj* jobj = fp0->parts[bone_idx].joint;

            efAsync_Spawn(gobj, &fp1->x60C, 4U, 1231, jobj, co_xBC);
        }
    }
}

void ftYs_GuardOff_Anim(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->mv.ys.guard.x0 += 1.0F;

    if (ftAnim_IsFramesRemaining(gobj) == 0) {
        ft_8008A2BC(gobj);
    }
}

void ftYs_GuardOff_IASA(HSD_GObj* gobj)
{
    RETURN_IF(ftCo_80099794(gobj));
}

void ftYs_GuardOff_Phys(HSD_GObj* arg0)
{
    ftCo_GuardOff_Phys(arg0);
}

void ftYs_GuardOff_Coll(HSD_GObj* arg0)
{
    ftCo_GuardOff_Coll(arg0);
}

void ftYs_Shield_8012C600(Fighter_GObj* gobj, bool arg1)
{
    f32 var_f0;
    f32 temp;

    u8 _[16];

    Fighter* fp = GET_FIGHTER(gobj);

    Fighter_ChangeMotionState(gobj, 0x158, 0U, 0.0F, 1.0F, 0.0F, NULL);
    fp->hitlag_cb = (void (*)(HSD_GObj*)) ftCo_80093240;
    fp->x670_timer_lstick_tilt_x = 0xFE;
    fp->post_hitlag_cb = (void (*)(HSD_GObj*)) ftCo_800932DC;
    if (fp->x221C_b2 == 0) {
        ftParts_80074B0C(gobj, 0, 1);
    }
    inlineA0(gobj);
    temp = (p_ftCommonData->x28C *
            (fp->x19A4 * (1.0F - fp->lightshield_amount))) +
           p_ftCommonData->x290;
    if (arg1 == false) {
        fp->gr_vel = temp * p_ftCommonData->x294;
        if (fp->specialn_facing_dir < 0.0F) {
            var_f0 = fp->gr_vel;
        } else {
            var_f0 = -fp->gr_vel;
        }
        fp->gr_vel = var_f0;
    }
    ftCo_80092450(gobj);
    ftCo_80091D58(fp);
}

void ftYs_GuardDamage_Anim(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    ftCo_80093BC0(gobj);
    if (!ftAnim_IsFramesRemaining(gobj)) {
        if (fp->mv.ys.guard.xC) {
            ftCo_80092BE8(gobj);
        } else {
            ftCo_800928CC(gobj);
        }
    }
}

void ftYs_GuardDamage_IASA(HSD_GObj* arg0) {}

void ftYs_GuardDamage_Phys(Fighter_GObj* gobj)
{
    ftCo_GuardSetOff_Phys(gobj);
}

void ftYs_GuardDamage_Coll(Fighter_GObj* gobj)
{
    ftCo_GuardSetOff_Coll(gobj);
}

void ftYs_Shield_8012C850(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    Fighter_ChangeMotionState(gobj, ftYs_MS_GuardOn_1, 16, fp->cur_anim_frame,
                              1, 0, NULL);
    fp->x672_input_timer_counter = 254;
    fp->x221A_b7 = false;
    fp->x221B_b0 = false;
    fp->x221C_b3 = true;
    fp->x221C_b1 = true;
    fp->x221C_b2 = true;

    fp->mv.ys.guard.x14 = p_ftCommonData->x2A4;
    fp->mv.ys.guard.x18 = p_ftCommonData->x2B4;
    ftCo_8009370C(gobj, ftYs_Shield_8012CACC);
}

static inline void ftYs_Shield_8012C914_inline(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    Vec3 translate;

    ftColl_8007B0C0(gobj, HurtCapsule_Disabled);
    fp->mv.ys.guard.xC = false;
    fp->mv.ys.guard.x0 = 0.0F;
    fp->mv.ys.guard.x10 = p_ftCommonData->x268;
    fp->mv.ys.guard.x24 = 0;
    fp->mv.ys.guard.x20 = 0;
    translate.x = translate.y = translate.z = 0.0F;

    HSD_JObjSetTranslate(fp->parts[fp->ft_data->x8->x11].joint, &translate);
    ftYs_Init_8012B8A4(gobj);
    ftCo_80091D58(fp);
    ft_PlaySFX(fp, 0x6E, 0x7F, 0x40);
}

void ftYs_Shield_8012C914(Fighter_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    Fighter_ChangeMotionState(gobj, ftYs_MS_GuardOn_1, 0, 0.0F, 1.0F, 0.0F,
                              NULL);
    ftAnim_8006EBA4(gobj);
    fp->x672_input_timer_counter = 254;
    fp->x221C_b3 = true;
    fp->x221C_b1 = true;
    fp->x221C_b2 = true;
    fp->mv.ys.guard.x14 = p_ftCommonData->x2A4;
    fp->mv.ys.guard.x18 = p_ftCommonData->x2B4;
    ftCo_8009370C(gobj, ftYs_Shield_8012CACC);
    ftYs_Shield_8012C914_inline(gobj);
}

void ftYs_Shield_8012CACC(HSD_GObj* arg0) {}

void ftYs_GuardOn_1_Anim(HSD_GObj* gobj)
{
    Fighter* fp;
    u8 _[12];

    ftCo_80093BC0(gobj);
    fp = GET_FIGHTER(gobj);
    fp->mv.ys.guard.x0 += 1.0F;
    ftCo_80092BCC(gobj);
    if (ftCo_800925A4(gobj)) {
        spawnEffect(gobj);
    } else if (!ftAnim_IsFramesRemaining(gobj)) {
        ftCo_800928CC(gobj);
    } else {
        ftYs_Init_8012B8A4(gobj);
    }
}

void ftYs_GuardOn_1_IASA(Fighter_GObj* gobj)
{
    ftCo_GuardReflect_IASA(gobj);
}

void ftYs_GuardOn_1_Phys(Fighter_GObj* gobj)
{
    ftCo_GuardReflect_Phys(gobj);
}

void ftYs_GuardOn_1_Coll(Fighter_GObj* gobj)
{
    ftCo_GuardReflect_Coll(gobj);
}

bool ftYs_Shield_8012CC1C(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if ((fp->input.held_inputs & HSD_PAD_LR) && (fp->shield_health >= 0)) {
        ftCo_800928CC(gobj);
        return true;
    }

    return false;
}
