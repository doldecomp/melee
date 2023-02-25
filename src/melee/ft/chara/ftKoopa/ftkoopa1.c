#include <melee/ft/chara/ftKoopa/ftkoopa.h>

#include <melee/ft/chara/ftKoopa/ftkoopa.h>
#include <melee/ft/forward.h>
#include <melee/ft/ft_unknown_006.h>
#include <melee/ft/ftcamera.h>
#include <melee/ft/ftcoll.h>
#include <melee/ft/ftcommon.h>
#include <melee/ft/ftparts.h>
#include <melee/ft/types.h>
#include <melee/it/itkind.h>

ActionState as_table_koopa[] = {
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
    Fighter* fp = gobj->user_data;
    ftKoopaAttributes* koopaAttr = fp->x2D4_specialAttributes;
    ftKoopaVars* ftVars;
    f32 unk = 0.0;
    f32 unk1 = 0.0;

    func_80074A4C(gobj, 0, 0);

    ftVars = (ftKoopaVars*) &fp->sa.koopa.x222C;

    fp->dmg.x18B0 = koopaAttr->x0;
    ftVars->x0 = koopaAttr->x10;
    ftVars->x4 = koopaAttr->x18;
}

/* static */ void func_80134D78(HSD_GObj* gobj);

void func_80132A64(HSD_GObj* gobj)
{
    func_80134D78(gobj);
    return;
}

void ftKoopa_OnLoadForGKoopa(Fighter* fp)
{
    PUSH_ATTRS(fp, ftKoopaAttributes);
}

void ftKoopa_OnLoad(HSD_GObj* gobj)
{
    ftData* ftDataInfo;
    void** items;
    Fighter* fp;

    fp = (Fighter*) gobj->user_data;
    ftDataInfo = fp->x10C_ftData;
    items = ftDataInfo->x48_items;

    PUSH_ATTRS(fp, ftKoopaAttributes);

    func_8026B3F8(items[0], It_Kind_Koopa_Flame);

    fp->x2226_flag.bits.b1 = 1;
}

void func_80132B38(void)
{
    return;
}

void ftKoopa_OnItemPickup(HSD_GObj* fighter_gobj, bool bool)
{
    Fighter_OnItemPickup(fighter_gobj, bool, true, true);
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
    Fighter* fp = gobj->user_data;
    return ((ftKoopaAttributes*) fp->x2D4_specialAttributes)->x4C;
}

f32 func_80132DD0(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    return ((ftKoopaAttributes*) fp->x2D4_specialAttributes)->x48;
}

f32 func_80132DE0(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    return ((ftKoopaAttributes*) fp->x2D4_specialAttributes)->x44;
}

f32 func_80132DF0(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    return ((ftKoopaAttributes*) fp->x2D4_specialAttributes)->x40;
}

f32 func_80132E00(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    return ((ftKoopaAttributes*) fp->x2D4_specialAttributes)->x3C;
}

f32 func_80132E10(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    return ((ftKoopaAttributes*) fp->x2D4_specialAttributes)->x34;
}

f32 func_80132E20(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    return ((ftKoopaAttributes*) fp->x2D4_specialAttributes)->x38;
}

void func_80132E30(HSD_GObj* gobj)
{
    Fighter* fp;
    HSD_GObj* temp;
    bool flag_set;

    fp = gobj->user_data;
    if (fp->x2210_ThrowFlags.b4 != 0) {
        fp->x2210_ThrowFlags.b4 = 0;
        flag_set = true;
    } else {
        flag_set = false;
    }
    if (flag_set != false) {
        fp->facing_dir = -fp->facing_dir;
        fp->x234C_stateVar4 = 1;
    }
    if ((u32) fp->x2200_ftcmd_var0 != 0) {
        if (fp->x1A58_interactedFighter != 0) {
            temp = fp->x1A58_interactedFighter;
            func_8007E2F4(fp, 0);
            func_800DE2A8(gobj, temp);
            func_800DE7C0(temp, 0, 0);
            fp->x2200_ftcmd_var0 = 0;
        }
    }
}

void ftKoopa_SpecialS_StartAction(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;

    f64 unk = 0.0;

    fp->x2210_ThrowFlags.flags = 0;
    fp->x2200_ftcmd_var0 = 0;
    fp->x2344_stateVar2 = 0;
    fp->x234C_stateVar4 = 0;

    Fighter_ActionStateChange_800693AC(gobj, 0x15B, 0, 0, lbl_804D9AD8,
                                       lbl_804D9ADC, lbl_804D9AD8);

    func_8006EBA4(gobj);

    fp = gobj->user_data;

    func_8007E2D0(fp, 8, func_8013302C, NULL, func_800BC7E0);

    fp->x2340_stateVar1 = 0;
    fp->x2348_stateVar3 = 0;
}

void ftKoopa_SpecialAirS_StartAction(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;

    f64 unk = 0.0;

    fp->x2210_ThrowFlags.flags = 0;
    fp->x2200_ftcmd_var0 = 0;
    fp->x2344_stateVar2 = 0;
    fp->x234C_stateVar4 = 0;

    Fighter_ActionStateChange_800693AC(gobj, 0x161, 0, 0, lbl_804D9AD8,
                                       lbl_804D9ADC, lbl_804D9AD8);

    func_8006EBA4(gobj);

    fp = gobj->user_data;

    func_8007E2D0(fp, 8, func_801330E4, NULL, func_800BC8D4);

    fp->x2340_stateVar1 = 0;
    fp->x2348_stateVar3 = 0;
}

void func_8013302C(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;

    if ((s32) fp->x2344_stateVar2 != 0) {
        Fighter_ActionStateChange_800693AC(gobj, 349, 0x80, 0, lbl_804D9AD8,
                                           lbl_804D9ADC, lbl_804D9AD8);
    } else {
        Fighter_ActionStateChange_800693AC(gobj, 348, 0x0, 0, lbl_804D9AD8,
                                           lbl_804D9ADC, lbl_804D9AD8);
    }
    fp->x2222_flag.bits.b2 = 1;
    func_8007E2F4(fp, 0x1FF);
    func_8007E2FC(gobj);
    fp->x2340_stateVar1 = 0;
    fp->x2200_ftcmd_var0 = 0;
}

void func_801330E4(HSD_GObj* gobj)
{
    Fighter* fp;

    fp = gobj->user_data;
    if ((s32) fp->x2344_stateVar2 != 0) {
        Fighter_ActionStateChange_800693AC(gobj, 0x163, 0x80, 0, lbl_804D9AD8,
                                           lbl_804D9ADC, lbl_804D9AD8);
    } else {
        Fighter_ActionStateChange_800693AC(gobj, 0x162, 0, 0, lbl_804D9AD8,
                                           lbl_804D9ADC, lbl_804D9AD8);
    }

    fp->x2222_flag.bits.b2 = 1;
    func_8007E2F4(fp, 0x1FF);
    func_8007E2FC(gobj);
    fp->x2340_stateVar1 = 0;
    fp->x2200_ftcmd_var0 = 0;
}

void func_8013319C(HSD_GObj* gobj)
{
    Fighter* fp;

    double unk = 0.0;

    fp = gobj->user_data;
    func_8007D5D4(fp);
    Fighter_ActionStateChange_800693AC(gobj, 0x161, 0x0C4C5088, 0,
                                       fp->x894_currentAnimFrame, lbl_804D9ADC,
                                       lbl_804D9AD8);
    fp = gobj->user_data;
    func_8007E2D0(fp, 8, func_801330E4, NULL, func_800BC8D4);
    fp->x2340_stateVar1 = 0;
    fp->x2348_stateVar3 = 0;
}

void func_8013322C(HSD_GObj* gobj)
{
    Fighter* ft1;
    Fighter* ft2;

    double unk = 0.0;

    ft2 = gobj->user_data;
    func_8007D7FC(ft2);

    Fighter_ActionStateChange_800693AC(gobj, 0x15B, 0x0C4C5088, 0,
                                       ft2->x894_currentAnimFrame, lbl_804D9ADC,
                                       lbl_804D9AD8);

    ft1 = gobj->user_data;
    func_8007E2D0(ft1, 8, func_8013302C, NULL, func_800BC7E0);
    ft1->x2340_stateVar1 = 0;
    ft1->x2348_stateVar3 = 0;
    ft2->x2340_stateVar1 = 0;
    ft2->x2200_ftcmd_var0 = 0;
}

void func_801332C4(HSD_GObj* gobj)
{
    HSD_GObj* temp_r31;
    Fighter* fp;

    fp = gobj->user_data;
    temp_r31 = fp->x1A58_interactedFighter;
    func_8007D5D4(fp);

    if (temp_r31 != NULL) {
        func_800DC920(gobj, temp_r31);
        func_800CC730(temp_r31);
    }

    func_800CC730(gobj);
}

void func_80133324(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;

    func_8007D7FC(fp);

    Fighter_ActionStateChange_800693AC(gobj, 0x15C, 0x0C4C5088, 0,
                                       fp->x894_currentAnimFrame, lbl_804D9ADC,
                                       lbl_804D9AD8);

    func_8007E2F4(fp, 0x1FF);
    func_8007E2FC(gobj);
}

void func_80133398(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    HSD_GObj* unk_gobj = fp->x1A58_interactedFighter;

    func_8007D5D4(fp);

    if (unk_gobj != NULL) {
        func_800DC920(gobj, unk_gobj);
        func_800CC730(unk_gobj);
    }

    func_800CC730(gobj);
}

void func_801333F8(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;

    func_8007D7FC(fp);

    Fighter_ActionStateChange_800693AC(gobj, 0x15E, 0x044C1080, 0,
                                       fp->x894_currentAnimFrame, lbl_804D9ADC,
                                       lbl_804D9AD8);

    func_8007E2F4(fp, 0x1FF);
    func_8007E2FC(gobj);
    func_8006F0FC(gobj, lbl_804D9AD8);
    fp->x2340_stateVar1 = 0;
    fp->x2200_ftcmd_var0 = 0;
}

void func_80133484(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    HSD_GObj* unk_gobj = fp->x1A58_interactedFighter;

    func_8007D5D4(fp);

    if (unk_gobj != NULL) {
        func_800DC920(gobj, unk_gobj);
        func_800CC730(unk_gobj);
    }

    func_800CC730(gobj);
}

void func_801334E4(HSD_GObj* gobj)
{
    u32 x = 0;
    Fighter* fp = gobj->user_data;

    func_8007D7FC(fp);

    if ((s32) fp->x234C_stateVar4 != 0)
        fp->facing_dir = -fp->facing_dir;

    Fighter_ActionStateChange_800693AC(gobj, 0x15F, 0x0C4C5088, 0,
                                       fp->x894_currentAnimFrame, lbl_804D9ADC,
                                       lbl_804D9AD8);

    if ((s32) fp->x234C_stateVar4 != 0)
        fp->facing_dir = -fp->facing_dir;

    if (fp->x1A58_interactedFighter != 0)
        func_800BCE64(fp->x1A58_interactedFighter, 0x119);

    func_8007E2F4(fp, 0x1FF);
    func_8007E2FC(gobj);
}

void func_8013359C(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    func_8007D7FC(fp);

    if ((s32) fp->x234C_stateVar4 != 0)
        fp->facing_dir = -fp->facing_dir;

    Fighter_ActionStateChange_800693AC(gobj, 0x160, 0x0C4C5088, 0,
                                       fp->x894_currentAnimFrame, lbl_804D9ADC,
                                       lbl_804D9AD8);

    if ((s32) fp->x234C_stateVar4 != 0)
        fp->facing_dir = -fp->facing_dir;

    if (fp->x1A58_interactedFighter != NULL)
        func_800BCE64(fp->x1A58_interactedFighter, 0x11A);

    func_8007E2F4(fp, 0x1FF);
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

void func_801336CC(HSD_GObj* gobj)
{
    Fighter* ft_temp;
    Fighter* fp;

    ftKoopaAttributes* koopaAttr;

    double unk = 0.0;
    double unk1 = 0.0;

    fp = ft_temp = gobj->user_data;
    koopaAttr = (ftKoopaAttributes*) fp->x2D4_specialAttributes;
    if (((u32) fp->x2200_ftcmd_var0 != 0) && ((s32) fp->x2344_stateVar2 != 0)) {
        func_8007ABD0(&fp->x914[0], koopaAttr->x2C, gobj);
        fp->x2200_ftcmd_var0 = 0;
    }

    if (!ftAnim_IsFramesRemaining(gobj)) {
        if ((s32) fp->x2340_stateVar1 != 0) {
            fp->x2344_stateVar2 = 1;
            ft_temp = gobj->user_data;
            if ((s32) ft_temp->x2344_stateVar2 != 0) {
                Fighter_ActionStateChange_800693AC(gobj, 0x15D, 0x80, 0,
                                                   lbl_804D9AD8, lbl_804D9ADC,
                                                   lbl_804D9AD8);
            } else {
                Fighter_ActionStateChange_800693AC(gobj, 0x15C, 0, 0,
                                                   lbl_804D9AD8, lbl_804D9ADC,
                                                   lbl_804D9AD8);
            }
            ft_temp->x2222_flag.bits.b2 = true;
            func_8007E2F4(ft_temp, 0x1FF);
            func_8007E2FC(gobj);
            ft_temp->x2340_stateVar1 = 0;
            ft_temp->x2200_ftcmd_var0 = 0;
            func_800BC9C8(fp->x1A58_interactedFighter);
            return;
        }

        fp = gobj->user_data;
        Fighter_ActionStateChange_800693AC(gobj, 0x15E, 0x80080, 0,
                                           fp->x894_currentAnimFrame,
                                           lbl_804D9ADC, lbl_804D9AD8);

        func_8006F0FC(gobj, lbl_804D9AD8);
        fp->x2340_stateVar1 = 0;
        fp->x2200_ftcmd_var0 = 0;
        func_8007E2F4(fp, 0x1FF);
    }
}
