#include <melee/ft/chara/ftIceClimber/fticeclimber1.h>

#include <melee/ft/chara/ftIceClimber/fticeclimber.h>
#include <melee/ft/code_80081B38.h>
#include <melee/ft/fighter.h>
#include <melee/ft/forward.h>
#include <melee/ft/ft_unknown_006.h>
#include <melee/ft/ftcamera.h>
#include <melee/ft/ftparts.h>
#include <melee/ft/types.h>
#include <melee/it/code_8027CF30.h>
#include <sysdolphin/baselib/gobj.h>

ActionState as_table_iceclimber[] = {
    { 295, 0x00340111, 0x12800000, lbl_8011F318, lbl_8011F390, lbl_8011F398,
      lbl_8011F3D8, func_800761C8 },
    { 296, 0x00340511, 0x12800000, lbl_8011F354, lbl_8011F394, lbl_8011F3B8,
      lbl_8011F454, func_800761C8 },
    { 297, 0x00340212, 0x13800000, lbl_8011FC78, lbl_8011FF40, lbl_80120080,
      lbl_80120660, func_800761C8 },
    { 298, 0x00340212, 0x13800000, lbl_8011FCD0, lbl_8011FF90, lbl_80120230,
      lbl_80120854, func_800761C8 },
    { 299, 0x00340612, 0x13800000, lbl_8011FD9C, lbl_8011FFE0, lbl_801203E0,
      lbl_80120A48, func_800761C8 },
    { 300, 0x00340612, 0x13800000, lbl_8011FE48, lbl_80120030, lbl_80120520,
      lbl_80120C58, func_800761C8 },
    { 301, 0x00340213, 0x14000000, lbl_801212C4, lbl_801214D4, lbl_801215DC,
      lbl_80121740, func_800761C8 },
    { 302, 0x00340213, 0x14000000, lbl_80121944, lbl_80121AC8, lbl_80121AD0,
      lbl_80121C34, func_800761C8 },
    { 303, 0x00340213, 0x14000000, lbl_801223B8, lbl_8012248C, lbl_80122494,
      lbl_80122664, func_800761C8 },
    { 304, 0x00340213, 0x14000000, lbl_80121E10, lbl_80121EB0, lbl_80121EB8,
      lbl_80121F2C, func_800761C8 },
    { 305, 0x00340213, 0x14000000, lbl_80122110, lbl_801221AC, lbl_801221B4,
      lbl_80122228, func_800761C8 },
    { 306, 0x00340613, 0x14000000, lbl_801213CC, lbl_80121558, lbl_80121680,
      lbl_8012177C, func_800761C8 },
    { 307, 0x00340613, 0x14000000, lbl_801219F4, lbl_80121ACC, lbl_80121B74,
      lbl_80121C70, func_800761C8 },
    { 308, 0x00340613, 0x14000000, lbl_80122410, lbl_80122490, lbl_80122538,
      lbl_801226A0, func_800761C8 },
    { 309, 0x00340613, 0x14000000, lbl_80121E4C, lbl_80121EB4, lbl_80121ED8,
      lbl_80121F68, func_800761C8 },
    { 310, 0x00340613, 0x14000000, lbl_8012214C, lbl_801221B0, lbl_801221D4,
      lbl_80122264, func_800761C8 },
    { 311, 0x00340014, 0x15800000, lbl_80122A0C, lbl_80122B0C, lbl_80122B14,
      lbl_80122C18, func_800761C8 },
    { 312, 0x00340414, 0x15800000, lbl_80122A8C, lbl_80122B10, lbl_80122B34,
      lbl_80122D04, func_800761C8 },
    { 313, 0x00340212, 0x13800000, lbl_80123CA4, lbl_80123E58, lbl_80123E60,
      lbl_80123F98, func_800761C8 },
    { 314, 0x00340612, 0x13800000, lbl_80123D68, lbl_80123E5C, lbl_80123EFC,
      lbl_801241A0, func_800761C8 },
    { 315, 0x00340213, 0x14000000, lbl_80123348, lbl_80123388, lbl_80123390,
      lbl_801233F0, func_800761C8 },
    { 316, 0x00340213, 0x14000000, lbl_80123448, lbl_801234E4, lbl_801234EC,
      lbl_801235BC, func_800761C8 },
    { 317, 0x00340213, 0x14000000, NULL, NULL, NULL, NULL, func_800761C8 },
    { 318, 0x00340613, 0x14000000, lbl_80123384, lbl_8012338C, lbl_801233EC,
      lbl_801233F4, func_800761C8 },
    { 319, 0x00340613, 0x14000000, lbl_80123484, lbl_801234E8, lbl_8012350C,
      lbl_801235F8, func_800761C8 },
    { 320, 0x00340613, 0x14000000, NULL, NULL, NULL, NULL, func_800761C8 },
};

char lbl_803CD610[] = "PlPp.dat";
char lbl_803CD61C[] = "ftDataPopo";
char lbl_803CD628[] = "PlPpNr.dat";
char lbl_803CD634[] = "PlyPopo5K_Share_joint";
char lbl_803CD64C[] = "PlyPopo5K_Share_matanim_joint";
char lbl_803CD66C[] = "PlPpGr.dat";
char lbl_803CD678[] = "PlyPopo5KGr_Share_joint";
char lbl_803CD690[] = "PlyPopo5KGr_Share_matanim_joint";
char lbl_803CD6B0[] = "PlPpOr.dat";
char lbl_803CD6BC[] = "PlyPopo5KOr_Share_joint";
char lbl_803CD6D4[] = "PlyPopo5KOr_Share_matanim_joint";
char lbl_803CD6F4[] = "PlPpRe.dat";
char lbl_803CD700[] = "PlyPopo5KRe_Share_joint";
char lbl_803CD718[] = "PlyPopo5KRe_Share_matanim_joint";
char lbl_803CD738[] = "PlPpAJ.dat";

Fighter_DemoStrings lbl_803CD7B4 = {
    "ftDemoResultMotionFilePopo",
    "ftDemoIntroMotionFilePopo",
    "ftDemoEndingMotionFilePopo",
    "ftDemoViWaitMotionFilePopo",
};

Fighter_CostumeStrings lbl_803CD7C4[] = {
    { lbl_803CD628, lbl_803CD634, lbl_803CD64C },
    { lbl_803CD66C, lbl_803CD678, lbl_803CD690 },
    { lbl_803CD6B0, lbl_803CD6BC, lbl_803CD6D4 },
    { lbl_803CD6F4, lbl_803CD700, lbl_803CD718 },
};

void ftIceClimber_OnItemPickup(HSD_GObj* fighter_gobj, bool bool)
{
    Fighter_OnItemPickup(fighter_gobj, bool, 1, 1);
}

void ftIceClimber_OnItemInvisible(HSD_GObj* fighter_gobj)
{
    Fighter_OnItemInvisible(fighter_gobj, 1);
}

void ftIceClimber_OnItemVisible(HSD_GObj* fighter_gobj)
{
    Fighter_OnItemVisible(fighter_gobj, 1);
}

void ftIceClimber_OnItemDrop(HSD_GObj* gobj, bool bool1)
{
    Fighter_OnItemDrop(gobj, bool1, 1, 1);
}

void ftIceClimber_OnLoadForNana(Fighter* fp)
{
    PUSH_ATTRS(fp, ftIceClimberAttributes);
}

void ftIceClimber_OnLoad(HSD_GObj* fighter_gobj)
{
    s32 unused;
    Fighter* fp = fighter_gobj->user_data;
    void** item_list = fp->x10C_ftData->x48_items;
    fp->x2222_flag.bits.b5 = 1;

    PUSH_ATTRS(fp, ftIceClimberAttributes);

    {
        ftIceClimberAttributes* attr = fp->x2D4_specialAttributes;
        fp->x40 = attr->x0;
        func_8026B3F8(item_list[0], 0x6AU);
        func_8026B3F8(item_list[1], 0x6BU);
        func_8026B3F8(item_list[2], 0x71U);
    }
}

void ftIceClimber_OnDeath(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fighter_gobj->user_data;
    ftIceClimberAttributes* attr = fp->x2D4_specialAttributes;
    func_80074A4C(fighter_gobj, 0U, 0);
    func_80074A4C(fighter_gobj, 1U, 0);
    fp->sa.nana.x2234 = 0;
    fp->sa.nana.x222C = 0;
    fp->sa.nana.x2230.bits.b0 = 0;
    fp->sa.nana.x2238 = 0;
    fp->sa.nana.x224C = 0;
    fp->sa.nana.x2250 = 0.0f;
}

void ftIceClimber_8011F060(HSD_GObj* fighter_gobj)
{
    func_8011F190(fighter_gobj);
    func_80122898(fighter_gobj);
    func_80121164(fighter_gobj);
    func_8011F68C(fighter_gobj);
}

void ftIceClimber_LoadSpecialAttrs(HSD_GObj* fighter_gobj)
{
    COPY_ATTRS(fighter_gobj, ftIceClimberAttributes);
}

void ftIceClimber_OnKnockbackEnter(HSD_GObj* fighter_gobj)
{
    Fighter_OnKnockbackEnter(fighter_gobj, true);
}

void ftIceClimber_OnKnockbackExit(HSD_GObj* fighter_gobj)
{
    Fighter_OnKnockbackExit(fighter_gobj, true);
}

void func_8011F16C(HSD_GObj* fighter_gobj, uint i)
{
    Fighter* fp = (Fighter*) HSD_GObjGetUserData(fighter_gobj);

    if (i != fp->sa.nana.x222C)
        return;

    fp->sa.nana.x222C = 0;
    fp->cb.x21E4_callback_OnDeath2 = NULL;
    fp->cb.x21DC_callback_OnTakeDamage = NULL;
}

void func_8011F190(HSD_GObj* fighter_gobj)
{
    Fighter* fp = (Fighter*) HSD_GObjGetUserData(fighter_gobj);

    if (fp->sa.nana.x222C == 0)
        return;

    func_802C17DC(fp->sa.nana.x222C);
    func_8011F16C(fighter_gobj, fp->sa.nana.x222C);
}

extern f32 const lbl_804D9838;
extern f32 const lbl_804D983C;

void ftIceClimber_SpecialN_StartAction(HSD_GObj* fighter_gobj)
{
    Fighter* fp = (Fighter*) HSD_GObjGetUserData(fighter_gobj);
    fp->x2210_ThrowFlags.flags = FLAGS_ZERO;
    fp->x2200_ftcmd_var0 = 0;
    fp->sa.nana.x222C = 0;

    Fighter_ActionStateChange_800693AC(fighter_gobj, 341, 0, NULL, lbl_804D9838,
                                       lbl_804D983C, lbl_804D9838);

    func_8006EBA4(fighter_gobj);
    fp->cb.x21BC_callback_Accessory4 = &lbl_8011F500;
}

extern f32 const lbl_804D9840;

void ftIceClimber_SpecialAirN_StartAction(HSD_GObj* fighter_gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 unused[4];
#endif

    Fighter* fp = (Fighter*) HSD_GObjGetUserData(fighter_gobj);
    ftIceClimberAttributes* icattr = fp->x2D4_specialAttributes;

    fp->x2210_ThrowFlags.flags = FLAGS_ZERO;
    fp->x2200_ftcmd_var0 = 0;
    fp->sa.nana.x222C = 0;

    if ((s32) fp->sa.nana.x224C == false) {
        fp->x80_self_vel.y = icattr->x4;
        fp->sa.nana.x224C = true;
        fp->sa.nana.x2250 = lbl_804D9838;
    } else {
        fp->sa.nana.x2250 = lbl_804D9840;
    }

    Fighter_ActionStateChange_800693AC(fighter_gobj, 342, 0, NULL, lbl_804D9838,
                                       lbl_804D983C, lbl_804D9838);

    func_8006EBA4(fighter_gobj);
    fp->cb.x21BC_callback_Accessory4 = &lbl_8011F500;
}

void lbl_8011F318(HSD_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj))
        func_8008A2BC(gobj);
}

void lbl_8011F354(HSD_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj))
        func_800CC730(gobj);
}

void lbl_8011F390(HSD_GObj* arg0) {}

void lbl_8011F394(HSD_GObj* arg0) {}

void lbl_8011F398(HSD_GObj* gobj)
{
    func_80084F3C(gobj);
}

void lbl_8011F3B8(HSD_GObj* gobj)
{
    func_80084EEC(gobj);
}
