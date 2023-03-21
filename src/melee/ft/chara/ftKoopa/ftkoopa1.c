#include "ft/forward.h"
#include "ft/ft_unknown_006.h"
#include "ft/ftcamera.h"
#include "ft/ftcoll.h"
#include "ft/ftcommon.h"
#include "ft/ftparts.h"
#include "ft/types.h"
#include "ftKoopa/ftkoopa.h"
#include "it/forward.h"

MotionState as_table_koopa[] = {
    { 295, 0x00340011, 0x12000000, lbl_80134F48, lbl_801351B0, lbl_80135438,
      lbl_801354F8, func_800761C8 },
    { 296, 0x003C0011, 0x12000000, lbl_80134F9C, lbl_801351B4, lbl_80135458,
      lbl_80135564, func_800761C8 },
    { 297, 0x00340011, 0x12000000, lbl_80135040, lbl_801352F0, lbl_80135478,
      lbl_801355D0, func_800761C8 },
    { 298, 0x00340411, 0x12000000, lbl_8013507C, lbl_801352F4, lbl_80135498,
      lbl_8013563C, func_800761C8 },
    { 299, 0x003C0411, 0x12000000, lbl_801350D0, lbl_801352F8, lbl_801354B8,
      lbl_801356A8, func_800761C8 },
    { 300, 0x00340411, 0x12000000, lbl_80135174, lbl_80135434, lbl_801354D8,
      lbl_80135714, func_800761C8 },
    { 301, 0x00340012, 0x13000000, func_80133654, NULL, lbl_80134224,
      lbl_80134388, func_800761C8 },
    { 302, 0x00340012, 0x13000000, func_801336CC, lbl_80133BF4, lbl_80134288,
      lbl_801343D8, func_800761C8 },
    { 303, 0x00340012, 0x13000000, func_801336CC, lbl_80133BF4, lbl_80134288,
      lbl_801343D8, func_800761C8 },
    { 302, 0x00340012, 0x13000000, lbl_801339AC, lbl_80133E4C, lbl_801342C8,
      lbl_80134428, func_800761C8 },
    { 304, 0x00340012, 0x13000000, lbl_801339B4, NULL, lbl_80134308,
      lbl_80134478, func_800761C8 },
    { 305, 0x00340012, 0x13000000, lbl_80133A90, NULL, lbl_80134328,
      lbl_801344A0, func_800761C8 },
    { 306, 0x00340412, 0x13000000, func_80133690, NULL, lbl_80134244,
      lbl_801343B0, func_800761C8 },
    { 307, 0x00340412, 0x13000000, lbl_8013383C, lbl_80133D20, lbl_801342A8,
      lbl_80134400, func_800761C8 },
    { 308, 0x00340412, 0x13000000, lbl_8013383C, lbl_80133D20, lbl_801342A8,
      lbl_80134400, func_800761C8 },
    { 307, 0x00340012, 0x13000000, lbl_801339B0, lbl_80134038, lbl_801342E8,
      lbl_80134450, func_800761C8 },
    { 309, 0x00340412, 0x13000000, lbl_80133AD4, NULL, lbl_80134348,
      lbl_801344C8, func_800761C8 },
    { 310, 0x00340412, 0x13000000, lbl_80133BB0, NULL, lbl_80134368,
      lbl_801344F0, func_800761C8 },
    { 311, 0x00340213, 0x14000000, func_80135C08, lbl_80135D78, lbl_80135D80,
      lbl_80135E4C, func_800761C8 },
    { 312, 0x00340613, 0x14000000, lbl_80135C60, lbl_80135D7C, lbl_80135DE0,
      lbl_80135F6C, func_800761C8 },
    { 313, 0x00340214, 0x15000000, lbl_8013474C, NULL, lbl_801347C4,
      lbl_801348A0, func_800761C8 },
    { 314, 0x00340614, 0x15000000, lbl_80134788, NULL, lbl_80134804,
      func_801348C0, func_800761C8 },
    { 315, 0x00340214, 0x15000000, lbl_801349C4, NULL, lbl_80134A00,
      lbl_80134A20, func_800761C8 },
};

char lbl_803CF0A0[] = "PlKp.dat";
char lbl_803CF0AC[] = "ftDataKoopa";
char lbl_803CF0B8[] = "PlKpNr.dat";
char lbl_803CF0C4[] = "PlyKoopa5K_Share_joint";
char lbl_803CF0DC[] = "PlyKoopa5K_Share_matanim_joint";
char lbl_803CF0FC[] = "PlKpRe.dat";
char lbl_803CF108[] = "PlyKoopa5KRe_Share_joint";
char lbl_803CF124[] = "PlyKoopa5KRe_Share_matanim_joint";
char lbl_803CF148[] = "PlKpBu.dat";
char lbl_803CF154[] = "PlyKoopa5KBu_Share_joint";
char lbl_803CF170[] = "PlyKoopa5KBu_Share_matanim_joint";
char lbl_803CF194[] = "PlKpBk.dat";
char lbl_803CF1A0[] = "PlyKoopa5KBk_Share_joint";
char lbl_803CF1BC[] = "PlyKoopa5KBk_Share_matanim_joint";
char lbl_803CF1E0[] = "PlKpAJ.dat";

Fighter_DemoStrings lbl_803CF25C = {
    "ftDemoResultMotionFileKoopa",
    "ftDemoIntroMotionFileKoopa",
    "ftDemoEndingMotionFileKoopa",
    "ftDemoViWaitMotionFileKoopa",
};

Fighter_CostumeStrings lbl_803CF26C[] = {
    { lbl_803CF0B8, lbl_803CF0C4, lbl_803CF0DC },
    { lbl_803CF0FC, lbl_803CF108, lbl_803CF124 },
    { lbl_803CF148, lbl_803CF154, lbl_803CF170 },
    { lbl_803CF194, lbl_803CF1A0, lbl_803CF1BC },
};

/* static */ extern const f32 lbl_804D9ADC; // = 1.0F
/* static */ extern const f32 lbl_804D9AD8; // = 0.0F

void ftKoopa_OnDeath(HSD_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    Fighter* fp = GET_FIGHTER(gobj);
    ftKoopaAttributes* koopaAttr = fp->x2D4_specialAttributes;

    func_80074A4C(gobj, 0, 0);

    {
        ftKoopaVars* vars = (ftKoopaVars*) &fp->fv.kp.x222C;

        fp->dmg.x18B0 = koopaAttr->x0;
        vars->x0 = koopaAttr->x10;
        vars->x4 = koopaAttr->x18;
    }
}

/* static */ void func_80134D78(HSD_GObj* gobj);

void func_80132A64(HSD_GObj* gobj)
{
    func_80134D78(gobj);
}

void ftKoopa_OnLoadForGKoopa(Fighter* fp)
{
    PUSH_ATTRS(fp, ftKoopaAttributes);
}

void ftKoopa_OnLoad(HSD_GObj* gobj)
{
    /// @todo #GET_FIGHTER is 8 bytes too much stack but it should be possible
    Fighter* fp = gobj->user_data;

    ftData* ftDataInfo = fp->x10C_ftData;
    UNK_T* items = ftDataInfo->x48_items;

    PUSH_ATTRS(fp, ftKoopaAttributes);
    func_8026B3F8(items[0], It_Kind_Koopa_Flame);
    fp->x2226_flag.bits.b1 = true;
}

void func_80132B38(void) {}

void ftKoopa_OnItemPickup(HSD_GObj* gobj, bool bool)
{
    Fighter_OnItemPickup(gobj, bool, true, true);
}

void ftKoopa_OnItemInvisible(HSD_GObj* gobj)
{
    Fighter_OnItemInvisible(gobj, true);
}

void ftKoopa_OnItemVisible(HSD_GObj* gobj)
{
    Fighter_OnItemVisible(gobj, true);
}

void ftKoopa_OnItemDrop(HSD_GObj* gobj, bool bool1)
{
    Fighter_OnItemDrop(gobj, bool1, true, true);
}

void ftKoopa_LoadSpecialAttrs(HSD_GObj* gobj)
{
    COPY_ATTRS(gobj, ftKoopaAttributes);
}

void ftKoopa_OnKnockbackEnter(HSD_GObj* gobj)
{
    Fighter_OnKnockbackEnter(gobj, true);
}

void ftKoopa_OnKnockbackExit(HSD_GObj* gobj)
{
    Fighter_OnKnockbackExit(gobj, true);
}

f32 func_80132DC0(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKoopaAttributes* sa = fp->x2D4_specialAttributes;
    return sa->x4C;
}

f32 func_80132DD0(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKoopaAttributes* sa = fp->x2D4_specialAttributes;
    return sa->x48;
}

f32 func_80132DE0(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKoopaAttributes* sa = fp->x2D4_specialAttributes;
    return sa->x44;
}

f32 func_80132DF0(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKoopaAttributes* sa = fp->x2D4_specialAttributes;
    return sa->x40;
}

f32 func_80132E00(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKoopaAttributes* sa = fp->x2D4_specialAttributes;
    return sa->x3C;
}

f32 func_80132E10(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKoopaAttributes* sa = fp->x2D4_specialAttributes;
    return sa->x34;
}

f32 func_80132E20(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    ftKoopaAttributes* sa = fp->x2D4_specialAttributes;
    return sa->x38;
}

void func_80132E30(HSD_GObj* gobj)
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

    if (fp->x2200_ftcmd_var0 == 0)
        return;

    if (fp->x1A58_interactedFighter == NULL)
        return;

    {
        HSD_GObj* victim_gobj = fp->x1A58_interactedFighter;
        func_8007E2F4(fp, 0);
        func_800DE2A8(gobj, victim_gobj);
        func_800DE7C0(victim_gobj, 0, 0);
        fp->x2200_ftcmd_var0 = 0;
    }
}

void ftKoopa_SpecialS_StartAction(HSD_GObj* gobj)
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

    func_8006EBA4(gobj);

    {
        Fighter* fp = GET_FIGHTER(gobj);

        func_8007E2D0(fp, 8, func_8013302C, NULL, func_800BC7E0);

        fp->mv.kp.unk1.x0 = 0;
        fp->mv.kp.unk1.x8 = 0;
    }
}

void ftKoopa_SpecialAirS_StartAction(HSD_GObj* gobj)
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

    func_8006EBA4(gobj);

    {
        Fighter* fp = GET_FIGHTER(gobj);

        func_8007E2D0(fp, 8, func_801330E4, NULL, func_800BC8D4);

        fp->mv.kp.unk1.x0 = 0;
        fp->mv.kp.unk1.x8 = 0;
    }
}

static Fighter_MotionStateChangeFlags const transition_flags0 =
    FtStateChange_SkipUpdateMatAnim;

void func_8013302C(HSD_GObj* gobj)
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
    func_8007E2F4(fp, 511);
    func_8007E2FC(gobj);
    fp->mv.kp.unk1.x0 = 0;
    fp->x2200_ftcmd_var0 = 0;
}

void func_801330E4(HSD_GObj* gobj)
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
    func_8007E2F4(fp, 511);
    func_8007E2FC(gobj);
    fp->mv.kp.unk1.x0 = 0;
    fp->x2200_ftcmd_var0 = 0;
}

static Fighter_MotionStateChangeFlags const transition_flags1 =
    FtStateChange_SkipUpdateHit | FtStateChange_SkipUpdateMatAnim |
    FtStateChange_SkipUpdateColAnim | FtStateChange_UpdateCmd |
    FtStateChange_SkipUpdateItemVis | FtStateChange_Unk_19 |
    FtStateChange_SkipUpdateModelPartVis | FtStateChange_SkipUpdateModelFlag |
    FtStateChange_Unk_27;

void func_8013319C(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    func_8007D5D4(fp);

    Fighter_ChangeMotionState(gobj, 353, transition_flags1, 0,
                              fp->x894_currentAnimFrame, lbl_804D9ADC,
                              lbl_804D9AD8);

    {
        Fighter* fp = GET_FIGHTER(gobj);
        func_8007E2D0(fp, 8, func_801330E4, NULL, func_800BC8D4);
        fp->mv.kp.unk1.x0 = 0;
        fp->mv.kp.unk1.x8 = 0;
    }
}

void func_8013322C(HSD_GObj* gobj)
{
    /// @todo @c fp0 cannot move below @c fp1, which is very strange.
    ///       Perhaps there is a temporary @c Fighter* somewhere.
    Fighter* fp0;
    Fighter* fp1 = GET_FIGHTER(gobj);

    func_8007D7FC(fp1);

    Fighter_ChangeMotionState(gobj, 347, transition_flags1, 0,
                              fp1->x894_currentAnimFrame, lbl_804D9ADC,
                              lbl_804D9AD8);

    {
        fp0 = GET_FIGHTER(gobj);
        func_8007E2D0(fp0, 8, func_8013302C, NULL, func_800BC7E0);
        fp0->mv.kp.unk1.x0 = 0;
        fp0->mv.kp.unk1.x8 = 0;
    }

    fp1->mv.kp.unk1.x0 = 0;
    fp1->x2200_ftcmd_var0 = 0;
}

void func_801332C4(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    HSD_GObj* victim_gobj = fp->x1A58_interactedFighter;

    func_8007D5D4(fp);

    if (victim_gobj != NULL) {
        func_800DC920(gobj, victim_gobj);
        func_800CC730(victim_gobj);
    }

    func_800CC730(gobj);
}

void func_80133324(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    func_8007D7FC(fp);

    Fighter_ChangeMotionState(gobj, 348, transition_flags1, 0,
                              fp->x894_currentAnimFrame, lbl_804D9ADC,
                              lbl_804D9AD8);

    func_8007E2F4(fp, 511);
    func_8007E2FC(gobj);
}

void func_80133398(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    HSD_GObj* victim_gobj = fp->x1A58_interactedFighter;

    func_8007D5D4(fp);

    if (victim_gobj != NULL) {
        func_800DC920(gobj, victim_gobj);
        func_800CC730(victim_gobj);
    }

    func_800CC730(gobj);
}
/// @todo Combine common flags with #transition_flags0.
static u32 const transition_flags2 =
    FtStateChange_SkipUpdateMatAnim | FtStateChange_SkipUpdateColAnim |
    FtStateChange_SkipUpdateItemVis | FtStateChange_Unk_19 |
    FtStateChange_SkipUpdateModelPartVis | FtStateChange_SkipUpdateModelFlag;

void func_801333F8(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    func_8007D7FC(fp);

    Fighter_ChangeMotionState(gobj, 350, transition_flags2, 0,
                              fp->x894_currentAnimFrame, lbl_804D9ADC,
                              lbl_804D9AD8);

    func_8007E2F4(fp, 511);
    func_8007E2FC(gobj);
    func_8006F0FC(gobj, lbl_804D9AD8);
    fp->mv.kp.unk1.x0 = 0;
    fp->x2200_ftcmd_var0 = 0;
}

void func_80133484(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    HSD_GObj* victim_gobj = fp->x1A58_interactedFighter;

    func_8007D5D4(fp);

    if (victim_gobj != NULL) {
        func_800DC920(gobj, victim_gobj);
        func_800CC730(victim_gobj);
    }

    func_800CC730(gobj);
}

void func_801334E4(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    func_8007D7FC(fp);

    if ((signed) fp->mv.kp.unk1.xC != 0)
        fp->facing_dir = -fp->facing_dir;

    Fighter_ChangeMotionState(gobj, 351, transition_flags1, 0,
                              fp->x894_currentAnimFrame, lbl_804D9ADC,
                              lbl_804D9AD8);

    if ((s32) fp->mv.kp.unk1.xC != 0)
        fp->facing_dir = -fp->facing_dir;

    if (fp->x1A58_interactedFighter != NULL)
        func_800BCE64(fp->x1A58_interactedFighter, ftCo_MS_ThrownKoopaF);

    func_8007E2F4(fp, 511);
    func_8007E2FC(gobj);
}

void func_8013359C(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    func_8007D7FC(fp);

    if ((signed) fp->mv.kp.unk1.xC != 0)
        fp->facing_dir = -fp->facing_dir;

    Fighter_ChangeMotionState(gobj, 352, transition_flags1, 0,
                              fp->x894_currentAnimFrame, lbl_804D9ADC,
                              lbl_804D9AD8);

    if ((signed) fp->mv.kp.unk1.xC != 0)
        fp->facing_dir = -fp->facing_dir;

    if (fp->x1A58_interactedFighter != NULL)
        func_800BCE64(fp->x1A58_interactedFighter, ftCo_MS_ThrownKoopaB);

    func_8007E2F4(fp, 511);
    func_8007E2FC(gobj);
}

void func_80133654(HSD_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj))
        func_8008A2BC(gobj);
}

void func_80133690(HSD_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj))
        func_800CC730(gobj);
}

static Fighter_MotionStateChangeFlags const transition_flags3 =
    FtStateChange_SkipUpdateMatAnim | FtStateChange_Unk_19;

void func_801336CC(HSD_GObj* gobj)
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
                func_8007ABD0(&fp1->x914[0], koopaAttr->x2C, gobj);
                fp1->x2200_ftcmd_var0 = 0;
            }
        }

        if (ftAnim_IsFramesRemaining(gobj))
            return;

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
                func_8007E2F4(fp0, 511);
                func_8007E2FC(gobj);
                fp0->mv.kp.unk1.x0 = 0;
                fp0->x2200_ftcmd_var0 = 0;
            }

            func_800BC9C8(fp1->x1A58_interactedFighter);

        } else {
            /// @todo Combine @c fp0 with other branch somehow
            fp0 = GET_FIGHTER(gobj);
            Fighter_ChangeMotionState(gobj, 350, transition_flags3, 0,
                                      fp0->x894_currentAnimFrame, lbl_804D9ADC,
                                      lbl_804D9AD8);

            func_8006F0FC(gobj, lbl_804D9AD8);
            fp0->mv.kp.unk1.x0 = 0;
            fp0->x2200_ftcmd_var0 = 0;
            func_8007E2F4(fp0, 511);
        }
    }
}
