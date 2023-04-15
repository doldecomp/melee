#include "ft/forward.h"
#include "it/forward.h"

#include "ft/ft_0877.h"
#include "ft/ftcamera.h"
#include "ft/ftcoll.h"
#include "ft/ftcommon.h"
#include "ft/ftparts.h"
#include "ft/inlines.h"
#include "ft/types.h"
#include "ftKoopa/ftkoopa.h"

MotionState ftKp_Init_MotionStateTable[] = {
    { 295, 0x00340011, 0x12000000, ftKp_Unk3_80134F48, ftKp_Unk3_801351B0,
      ftKp_Unk3_80135438, ftKp_Unk3_801354F8, ftCamera_UpdateCameraBox },
    { 296, 0x003C0011, 0x12000000, ftKp_Unk3_80134F9C, ftKp_Unk3_801351B4,
      ftKp_Unk3_80135458, ftKp_Unk3_80135564, ftCamera_UpdateCameraBox },
    { 297, 0x00340011, 0x12000000, ftKp_Unk3_80135040, ftKp_Unk3_801352F0,
      ftKp_Unk3_80135478, ftKp_Unk3_801355D0, ftCamera_UpdateCameraBox },
    { 298, 0x00340411, 0x12000000, ftKp_Unk3_8013507C, ftKp_Unk3_801352F4,
      ftKp_Unk3_80135498, ftKp_Unk3_8013563C, ftCamera_UpdateCameraBox },
    { 299, 0x003C0411, 0x12000000, ftKp_Unk3_801350D0, ftKp_Unk3_801352F8,
      ftKp_Unk3_801354B8, ftKp_Unk3_801356A8, ftCamera_UpdateCameraBox },
    { 300, 0x00340411, 0x12000000, ftKp_Unk3_80135174, ftKp_Unk3_80135434,
      ftKp_Unk3_801354D8, ftKp_Unk3_80135714, ftCamera_UpdateCameraBox },
    { 301, 0x00340012, 0x13000000, ftKp_Init_80133654, NULL,
      ftKp_Unk3_80134224, ftKp_Unk3_80134388, ftCamera_UpdateCameraBox },
    { 302, 0x00340012, 0x13000000, ftKp_Init_801336CC, ftKp_Unk3_80133BF4,
      ftKp_Unk3_80134288, ftKp_Unk3_801343D8, ftCamera_UpdateCameraBox },
    { 303, 0x00340012, 0x13000000, ftKp_Init_801336CC, ftKp_Unk3_80133BF4,
      ftKp_Unk3_80134288, ftKp_Unk3_801343D8, ftCamera_UpdateCameraBox },
    { 302, 0x00340012, 0x13000000, ftKp_Unk3_801339AC, ftKp_Unk3_80133E4C,
      ftKp_Unk3_801342C8, ftKp_Unk3_80134428, ftCamera_UpdateCameraBox },
    { 304, 0x00340012, 0x13000000, ftKp_Unk3_801339B4, NULL,
      ftKp_Unk3_80134308, ftKp_Unk3_80134478, ftCamera_UpdateCameraBox },
    { 305, 0x00340012, 0x13000000, ftKp_Unk3_80133A90, NULL,
      ftKp_Unk3_80134328, ftKp_Unk3_801344A0, ftCamera_UpdateCameraBox },
    { 306, 0x00340412, 0x13000000, ftKp_Init_80133690, NULL,
      ftKp_Unk3_80134244, ftKp_Unk3_801343B0, ftCamera_UpdateCameraBox },
    { 307, 0x00340412, 0x13000000, ftKp_Unk3_8013383C, ftKp_Unk3_80133D20,
      ftKp_Unk3_801342A8, ftKp_Unk3_80134400, ftCamera_UpdateCameraBox },
    { 308, 0x00340412, 0x13000000, ftKp_Unk3_8013383C, ftKp_Unk3_80133D20,
      ftKp_Unk3_801342A8, ftKp_Unk3_80134400, ftCamera_UpdateCameraBox },
    { 307, 0x00340012, 0x13000000, ftKp_Unk3_801339B0, ftKp_Unk3_80134038,
      ftKp_Unk3_801342E8, ftKp_Unk3_80134450, ftCamera_UpdateCameraBox },
    { 309, 0x00340412, 0x13000000, ftKp_Unk3_80133AD4, NULL,
      ftKp_Unk3_80134348, ftKp_Unk3_801344C8, ftCamera_UpdateCameraBox },
    { 310, 0x00340412, 0x13000000, ftKp_Unk3_80133BB0, NULL,
      ftKp_Unk3_80134368, ftKp_Unk3_801344F0, ftCamera_UpdateCameraBox },
    { 311, 0x00340213, 0x14000000, ftKp_Unk3_80135C08, ftKp_Unk3_80135D78,
      ftKp_Unk3_80135D80, ftKp_Unk3_80135E4C, ftCamera_UpdateCameraBox },
    { 312, 0x00340613, 0x14000000, ftKp_Unk3_80135C60, ftKp_Unk3_80135D7C,
      ftKp_Unk3_80135DE0, ftKp_Unk3_80135F6C, ftCamera_UpdateCameraBox },
    { 313, 0x00340214, 0x15000000, ftKp_Unk3_8013474C, NULL,
      ftKp_Unk3_801347C4, ftKp_Unk3_801348A0, ftCamera_UpdateCameraBox },
    { 314, 0x00340614, 0x15000000, ftKp_Unk3_80134788, NULL,
      ftKp_Unk3_80134804, ftKp_Unk3_801348C0, ftCamera_UpdateCameraBox },
    { 315, 0x00340214, 0x15000000, ftKp_Unk3_801349C4, NULL,
      ftKp_Unk3_80134A00, ftKp_Unk3_80134A20, ftCamera_UpdateCameraBox },
};

char ftKp_Init_DatFilename[] = "PlKp.dat";
char ftKp_Init_DataName[] = "ftDataKoopa";
char ftKp_Init_803CF0B8[] = "PlKpNr.dat";
char ftKp_Init_803CF0C4[] = "PlyKoopa5K_Share_joint";
char ftKp_Init_803CF0DC[] = "PlyKoopa5K_Share_matanim_joint";
char ftKp_Init_803CF0FC[] = "PlKpRe.dat";
char ftKp_Init_803CF108[] = "PlyKoopa5KRe_Share_joint";
char ftKp_Init_803CF124[] = "PlyKoopa5KRe_Share_matanim_joint";
char ftKp_Init_803CF148[] = "PlKpBu.dat";
char ftKp_Init_803CF154[] = "PlyKoopa5KBu_Share_joint";
char ftKp_Init_803CF170[] = "PlyKoopa5KBu_Share_matanim_joint";
char ftKp_Init_803CF194[] = "PlKpBk.dat";
char ftKp_Init_803CF1A0[] = "PlyKoopa5KBk_Share_joint";
char ftKp_Init_803CF1BC[] = "PlyKoopa5KBk_Share_matanim_joint";
char ftKp_Init_AnimDatFilename[] = "PlKpAJ.dat";

Fighter_DemoStrings ftKp_Init_DemoMotionFilenames = {
    "ftDemoResultMotionFileKoopa",
    "ftDemoIntroMotionFileKoopa",
    "ftDemoEndingMotionFileKoopa",
    "ftDemoViWaitMotionFileKoopa",
};

Fighter_CostumeStrings ftKp_Init_CostumeStrings[] = {
    { ftKp_Init_803CF0B8, ftKp_Init_803CF0C4, ftKp_Init_803CF0DC },
    { ftKp_Init_803CF0FC, ftKp_Init_803CF108, ftKp_Init_803CF124 },
    { ftKp_Init_803CF148, ftKp_Init_803CF154, ftKp_Init_803CF170 },
    { ftKp_Init_803CF194, ftKp_Init_803CF1A0, ftKp_Init_803CF1BC },
};

/* static */ extern const f32 lbl_804D9ADC; // = 1.0F
/* static */ extern const f32 lbl_804D9AD8; // = 0.0F

void ftKp_Init_OnDeath(HSD_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    Fighter* fp = GET_FIGHTER(gobj);
    ftKoopaAttributes* koopaAttr = fp->x2D4_specialAttributes;

    ftParts_80074A4C(gobj, 0, 0);

    {
        ftKoopaVars* vars = (ftKoopaVars*) &fp->fv.kp.x222C;

        fp->dmg.x18B0 = koopaAttr->x0;
        vars->x0 = koopaAttr->x10;
        vars->x4 = koopaAttr->x18;
    }
}

/* static */ void ftKp_Unk3_80134D78(HSD_GObj* gobj);

void ftKp_Init_UnkMotionStates3(HSD_GObj* gobj)
{
    ftKp_Unk3_80134D78(gobj);
}

void ftKp_OnLoadForGKoopa(Fighter* fp)
{
    PUSH_ATTRS(fp, ftKoopaAttributes);
}

void ftKp_Init_OnLoad(HSD_GObj* gobj)
{
    /// @todo #GET_FIGHTER is 8 bytes too much stack but it should be possible
    Fighter* fp = gobj->user_data;

    ftData* ftDataInfo = fp->ft_data;
    UNK_T* items = ftDataInfo->x48_items;

    PUSH_ATTRS(fp, ftKoopaAttributes);
    it_8026B3F8(items[0], It_Kind_Koopa_Flame);
    fp->x2226_flag.bits.b1 = true;
}

void ftKp_Init_80132B38(void) {}

void ftKp_Init_OnItemPickup(HSD_GObj* gobj, bool bool)
{
    Fighter_OnItemPickup(gobj, bool, true, true);
}

void ftKp_Init_OnItemInvisible(HSD_GObj* gobj)
{
    Fighter_OnItemInvisible(gobj, true);
}

void ftKp_Init_OnItemVisible(HSD_GObj* gobj)
{
    Fighter_OnItemVisible(gobj, true);
}

void ftKp_Init_OnItemDrop(HSD_GObj* gobj, bool bool1)
{
    Fighter_OnItemDrop(gobj, bool1, true, true);
}

void ftKp_Init_LoadSpecialAttrs(HSD_GObj* gobj)
{
    COPY_ATTRS(gobj, ftKoopaAttributes);
}

void ftKp_Init_OnKnockbackEnter(HSD_GObj* gobj)
{
    Fighter_OnKnockbackEnter(gobj, true);
}

void ftKp_Init_OnKnockbackExit(HSD_GObj* gobj)
{
    Fighter_OnKnockbackExit(gobj, true);
}

f32 ftKp_Init_80132DC0(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKoopaAttributes* sa = fp->x2D4_specialAttributes;
    return sa->x4C;
}

f32 ftKp_Init_80132DD0(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKoopaAttributes* sa = fp->x2D4_specialAttributes;
    return sa->x48;
}

f32 ftKp_Init_80132DE0(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKoopaAttributes* sa = fp->x2D4_specialAttributes;
    return sa->x44;
}

f32 ftKp_Init_80132DF0(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKoopaAttributes* sa = fp->x2D4_specialAttributes;
    return sa->x40;
}

f32 ftKp_Init_80132E00(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKoopaAttributes* sa = fp->x2D4_specialAttributes;
    return sa->x3C;
}

f32 ftKp_Init_80132E10(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKoopaAttributes* sa = fp->x2D4_specialAttributes;
    return sa->x34;
}

f32 ftKp_Init_80132E20(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKoopaAttributes* sa = fp->x2D4_specialAttributes;
    return sa->x38;
}

void ftKp_Init_80132E30(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    {
        bool throw_flag;
        if (fp->x2210_ThrowFlags.b4) {
            fp->x2210_ThrowFlags.b4 = false;
            throw_flag = true;
        } else {
            throw_flag = false;
        }

        if (throw_flag) {
            fp->facing_dir = -fp->facing_dir;
            fp->mv.kp.unk1.xC = true;
        }
    }

    if (fp->x2200_ftcmd_var0 == 0) {
        return;
    }

    if (fp->x1A58_interactedFighter == NULL) {
        return;
    }

    {
        HSD_GObj* victim_gobj = fp->x1A58_interactedFighter;
        ftCommon_8007E2F4(fp, 0);
        ft_800DE2A8(gobj, victim_gobj);
        ft_800DE7C0(victim_gobj, 0, 0);
        fp->x2200_ftcmd_var0 = 0;
    }
}

void ftKp_SpecialS_StartMotion(HSD_GObj* gobj)
{
    {
        Fighter* fp = GET_FIGHTER(gobj);

        fp->x2210_ThrowFlags.flags = 0;
        fp->x2200_ftcmd_var0 = 0;
        fp->mv.kp.unk1.x4 = 0;
        fp->mv.kp.unk1.xC = 0;
    }

    Fighter_ChangeMotionState(gobj, 347, 0, 0, lbl_804D9AD8, lbl_804D9ADC,
                              lbl_804D9AD8);

    ftAnim_8006EBA4(gobj);

    {
        Fighter* fp = GET_FIGHTER(gobj);

        ftCommon_8007E2D0(fp, 8, ftKp_Init_8013302C, NULL, ft_800BC7E0);

        fp->mv.kp.unk1.x0 = 0;
        fp->mv.kp.unk1.x8 = 0;
    }
}

void ftKp_SpecialAirS_StartMotion(HSD_GObj* gobj)
{
    {
        Fighter* fp = GET_FIGHTER(gobj);

        fp->x2210_ThrowFlags.flags = 0;
        fp->x2200_ftcmd_var0 = 0;
        fp->mv.kp.unk1.x4 = 0;
        fp->mv.kp.unk1.xC = 0;
    }

    Fighter_ChangeMotionState(gobj, 353, 0, 0, lbl_804D9AD8, lbl_804D9ADC,
                              lbl_804D9AD8);

    ftAnim_8006EBA4(gobj);

    {
        Fighter* fp = GET_FIGHTER(gobj);

        ftCommon_8007E2D0(fp, 8, ftKp_Init_801330E4, NULL, ft_800BC8D4);

        fp->mv.kp.unk1.x0 = 0;
        fp->mv.kp.unk1.x8 = 0;
    }
}

static Fighter_MotionStateChangeFlags const transition_flags0 =
    FtStateChange_SkipUpdateMatAnim;

void ftKp_Init_8013302C(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if ((signed) fp->mv.kp.unk1.x4 != 0) {
        Fighter_ChangeMotionState(gobj, 349, transition_flags0, 0,
                                  lbl_804D9AD8, lbl_804D9ADC, lbl_804D9AD8);
    } else {
        Fighter_ChangeMotionState(gobj, 348, 0, 0, lbl_804D9AD8, lbl_804D9ADC,
                                  lbl_804D9AD8);
    }

    fp->x2222_flag.bits.b2 = true;
    ftCommon_8007E2F4(fp, 511);
    ftCommon_8007E2FC(gobj);
    fp->mv.kp.unk1.x0 = 0;
    fp->x2200_ftcmd_var0 = 0;
}

void ftKp_Init_801330E4(HSD_GObj* gobj)
{
    Fighter* fp;

    fp = gobj->user_data;
    if ((signed) fp->mv.kp.unk1.x4 != 0) {
        Fighter_ChangeMotionState(gobj, 355, transition_flags0, 0,
                                  lbl_804D9AD8, lbl_804D9ADC, lbl_804D9AD8);
    } else {
        Fighter_ChangeMotionState(gobj, 354, 0, 0, lbl_804D9AD8, lbl_804D9ADC,
                                  lbl_804D9AD8);
    }

    fp->x2222_flag.bits.b2 = true;
    ftCommon_8007E2F4(fp, 511);
    ftCommon_8007E2FC(gobj);
    fp->mv.kp.unk1.x0 = 0;
    fp->x2200_ftcmd_var0 = 0;
}

static Fighter_MotionStateChangeFlags const transition_flags1 =
    FtStateChange_SkipUpdateHit | FtStateChange_SkipUpdateMatAnim |
    FtStateChange_SkipUpdateColAnim | FtStateChange_UpdateCmd |
    FtStateChange_SkipUpdateItemVis | FtStateChange_Unk_19 |
    FtStateChange_SkipUpdateModelPartVis | FtStateChange_SkipUpdateModelFlag |
    FtStateChange_Unk_27;

void ftKp_Init_8013319C(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftCommon_8007D5D4(fp);

    Fighter_ChangeMotionState(gobj, 353, transition_flags1, 0,
                              fp->x894_currentAnimFrame, lbl_804D9ADC,
                              lbl_804D9AD8);

    {
        Fighter* fp = GET_FIGHTER(gobj);
        ftCommon_8007E2D0(fp, 8, ftKp_Init_801330E4, NULL, ft_800BC8D4);
        fp->mv.kp.unk1.x0 = 0;
        fp->mv.kp.unk1.x8 = 0;
    }
}

void ftKp_Init_8013322C(HSD_GObj* gobj)
{
    /// @todo @c fp0 cannot move below @c fp1, which is very strange.
    ///       Perhaps there is a temporary @c Fighter* somewhere.
    Fighter* fp0;
    Fighter* fp1 = GET_FIGHTER(gobj);

    ftCommon_8007D7FC(fp1);

    Fighter_ChangeMotionState(gobj, 347, transition_flags1, 0,
                              fp1->x894_currentAnimFrame, lbl_804D9ADC,
                              lbl_804D9AD8);

    {
        fp0 = GET_FIGHTER(gobj);
        ftCommon_8007E2D0(fp0, 8, ftKp_Init_8013302C, NULL, ft_800BC7E0);
        fp0->mv.kp.unk1.x0 = 0;
        fp0->mv.kp.unk1.x8 = 0;
    }

    fp1->mv.kp.unk1.x0 = 0;
    fp1->x2200_ftcmd_var0 = 0;
}

void ftKp_Init_801332C4(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    HSD_GObj* victim_gobj = fp->x1A58_interactedFighter;

    ftCommon_8007D5D4(fp);

    if (victim_gobj != NULL) {
        ft_800DC920(gobj, victim_gobj);
        ft_800CC730(victim_gobj);
    }

    ft_800CC730(gobj);
}

void ftKp_Init_80133324(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    ftCommon_8007D7FC(fp);

    Fighter_ChangeMotionState(gobj, 348, transition_flags1, 0,
                              fp->x894_currentAnimFrame, lbl_804D9ADC,
                              lbl_804D9AD8);

    ftCommon_8007E2F4(fp, 511);
    ftCommon_8007E2FC(gobj);
}

void ftKp_Init_80133398(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    HSD_GObj* victim_gobj = fp->x1A58_interactedFighter;

    ftCommon_8007D5D4(fp);

    if (victim_gobj != NULL) {
        ft_800DC920(gobj, victim_gobj);
        ft_800CC730(victim_gobj);
    }

    ft_800CC730(gobj);
}
/// @todo Combine common flags with #transition_flags0.
static u32 const transition_flags2 =
    FtStateChange_SkipUpdateMatAnim | FtStateChange_SkipUpdateColAnim |
    FtStateChange_SkipUpdateItemVis | FtStateChange_Unk_19 |
    FtStateChange_SkipUpdateModelPartVis | FtStateChange_SkipUpdateModelFlag;

void ftKp_Init_801333F8(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    ftCommon_8007D7FC(fp);

    Fighter_ChangeMotionState(gobj, 350, transition_flags2, 0,
                              fp->x894_currentAnimFrame, lbl_804D9ADC,
                              lbl_804D9AD8);

    ftCommon_8007E2F4(fp, 511);
    ftCommon_8007E2FC(gobj);
    ftAnim_8006F0FC(gobj, lbl_804D9AD8);
    fp->mv.kp.unk1.x0 = 0;
    fp->x2200_ftcmd_var0 = 0;
}

void ftKp_Init_80133484(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    HSD_GObj* victim_gobj = fp->x1A58_interactedFighter;

    ftCommon_8007D5D4(fp);

    if (victim_gobj != NULL) {
        ft_800DC920(gobj, victim_gobj);
        ft_800CC730(victim_gobj);
    }

    ft_800CC730(gobj);
}

void ftKp_Init_801334E4(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    ftCommon_8007D7FC(fp);

    if ((signed) fp->mv.kp.unk1.xC != 0) {
        fp->facing_dir = -fp->facing_dir;
    }

    Fighter_ChangeMotionState(gobj, 351, transition_flags1, 0,
                              fp->x894_currentAnimFrame, lbl_804D9ADC,
                              lbl_804D9AD8);

    if ((s32) fp->mv.kp.unk1.xC != 0) {
        fp->facing_dir = -fp->facing_dir;
    }

    if (fp->x1A58_interactedFighter != NULL) {
        ft_800BCE64(fp->x1A58_interactedFighter, ftCo_MS_ThrownKoopaF);
    }

    ftCommon_8007E2F4(fp, 511);
    ftCommon_8007E2FC(gobj);
}

void ftKp_Init_8013359C(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    ftCommon_8007D7FC(fp);

    if ((signed) fp->mv.kp.unk1.xC != 0) {
        fp->facing_dir = -fp->facing_dir;
    }

    Fighter_ChangeMotionState(gobj, 352, transition_flags1, 0,
                              fp->x894_currentAnimFrame, lbl_804D9ADC,
                              lbl_804D9AD8);

    if ((signed) fp->mv.kp.unk1.xC != 0) {
        fp->facing_dir = -fp->facing_dir;
    }

    if (fp->x1A58_interactedFighter != NULL) {
        ft_800BCE64(fp->x1A58_interactedFighter, ftCo_MS_ThrownKoopaB);
    }

    ftCommon_8007E2F4(fp, 511);
    ftCommon_8007E2FC(gobj);
}

void ftKp_Init_80133654(HSD_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ft_8008A2BC(gobj);
    }
}

void ftKp_Init_80133690(HSD_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ft_800CC730(gobj);
    }
}

static Fighter_MotionStateChangeFlags const transition_flags3 =
    FtStateChange_SkipUpdateMatAnim | FtStateChange_Unk_19;

void ftKp_Init_801336CC(HSD_GObj* gobj)
{
    Fighter* fp0 = GET_FIGHTER(gobj);

    {
        /// @todo Unused stack.
#ifdef MUST_MATCH
        u8 unused0[8];
#endif

        Fighter* fp1 = fp0;

        {
            ftKoopaAttributes* koopaAttr = fp1->x2D4_specialAttributes;

            if (fp1->x2200_ftcmd_var0 != 0 && (signed) fp1->mv.kp.unk1.x4 != 0)
            {
                ftColl_8007ABD0(&fp1->x914[0], koopaAttr->x2C, gobj);
                fp1->x2200_ftcmd_var0 = 0;
            }
        }

        if (ftAnim_IsFramesRemaining(gobj)) {
            return;
        }

        if ((signed) fp1->mv.kp.unk1.x0 != 0) {
            fp1->mv.kp.unk1.x4 = true;

            {
                /// @todo Combine @c fp0 with other branch somehow
                fp0 = GET_FIGHTER(gobj);

                if ((signed) fp0->mv.kp.unk1.x4 != false) {
                    Fighter_ChangeMotionState(gobj, 349, transition_flags0, 0,
                                              lbl_804D9AD8, lbl_804D9ADC,
                                              lbl_804D9AD8);
                } else {
                    Fighter_ChangeMotionState(gobj, 348, FtStateChange_None, 0,
                                              lbl_804D9AD8, lbl_804D9ADC,
                                              lbl_804D9AD8);
                }

                fp0->x2222_flag.bits.b2 = true;
                ftCommon_8007E2F4(fp0, 511);
                ftCommon_8007E2FC(gobj);
                fp0->mv.kp.unk1.x0 = 0;
                fp0->x2200_ftcmd_var0 = 0;
            }

            ft_800BC9C8(fp1->x1A58_interactedFighter);

        } else {
            /// @todo Combine @c fp0 with other branch somehow
            fp0 = GET_FIGHTER(gobj);
            Fighter_ChangeMotionState(gobj, 350, transition_flags3, 0,
                                      fp0->x894_currentAnimFrame, lbl_804D9ADC,
                                      lbl_804D9AD8);

            ftAnim_8006F0FC(gobj, lbl_804D9AD8);
            fp0->mv.kp.unk1.x0 = 0;
            fp0->x2200_ftcmd_var0 = 0;
            ftCommon_8007E2F4(fp0, 511);
        }
    }
}
