#include <melee/ft/chara/ftGameWatch/ftgamewatch.h>

#include <melee/ft/chara/ftGameWatch/ftgamewatch.h>
#include <melee/ft/ft_unknown_006.h>
#include <melee/ft/ftcamera.h>
#include <melee/ft/ftparts.h>
#include <melee/ft/types.h>

ActionState as_table_gamewatch[] = {
    { 46, 0x002C0201, 0x02800000, ftGameWatch_Attack11_Anim,
      ftGameWatch_Attack11_IASA, ftGameWatch_Attack11_Phys,
      ftGameWatch_Attack11_Coll, func_800761C8 },
    { 49, 0x002C0204, 0x05800000, ftGameWatch_Attack100Start_Anim,
      ftGameWatch_Attack100Start_IASA, ftGameWatch_Attack100Start_Phys,
      ftGameWatch_Attack100Start_Coll, func_800761C8 },
    { 50, 0x002C0204, 0x05800000, ftGameWatch_Attack100Loop_Anim,
      ftGameWatch_Attack100Loop_IASA, ftGameWatch_Attack100Loop_Phys,
      ftGameWatch_Attack100Loop_Coll, func_800761C8 },
    { 51, 0x002C0204, 0x05800000, ftGameWatch_Attack100End_Anim,
      ftGameWatch_Attack100End_IASA, ftGameWatch_Attack100End_Phys,
      ftGameWatch_Attack100End_Coll, func_800761C8 },
    { 59, 0x00240208, 0x09800000, ftGameWatch_AttackLw3_Anim,
      ftGameWatch_AttackLw3_IASA, ftGameWatch_AttackLw3_Phys,
      ftGameWatch_AttackLw3_Coll, func_800761C8 },
    { 62, 0x00240A09, 0x0A800000, ftGameWatch_AttackS4_Anim,
      ftGameWatch_AttackS4_IASA, ftGameWatch_AttackS4_Phys,
      ftGameWatch_AttackS4_Coll, func_800761C8 },
    { 68, 0x0024060C, 0x0D800000, ftGameWatch_AttackAirN_Anim,
      ftGameWatch_AttackAirN_IASA, ftGameWatch_AttackAirN_Phys,
      ftGameWatch_AttackAirN_Coll, func_800761C8 },
    { 70, 0x0024060E, 0x0F800000, ftGameWatch_AttackAirB_Anim,
      ftGameWatch_AttackAirB_IASA, ftGameWatch_AttackAirB_Phys,
      ftGameWatch_AttackAirB_Coll, func_800761C8 },
    { 71, 0x0024060F, 0x10800000, ftGameWatch_AttackAirHi_Anim,
      ftGameWatch_AttackAirHi_IASA, ftGameWatch_AttackAirHi_Phys,
      ftGameWatch_AttackAirHi_Coll, func_800761C8 },
    { 73, 0x0000060C, 0x0DC00000, ftGameWatch_LandingAirN_Anim,
      ftGameWatch_LandingAirN_IASA, ftGameWatch_LandingAirN_Phys,
      ftGameWatch_LandingAirN_Coll, func_800761C8 },
    { 75, 0x0000060E, 0x0FC00000, ftGameWatch_LandingAirB_Anim,
      ftGameWatch_LandingAirB_IASA, ftGameWatch_LandingAirB_Phys,
      ftGameWatch_LandingAirB_Coll, func_800761C8 },
    { 76, 0x0000060F, 0x10C00000, ftGameWatch_LandingAirHi_Anim,
      ftGameWatch_LandingAirHi_IASA, ftGameWatch_LandingAirHi_Phys,
      ftGameWatch_LandingAirHi_Coll, func_800761C8 },
    { 295, 0x00340111, 0x12000000, ftGameWatch_SpecialN_Anim,
      ftGameWatch_SpecialN_IASA, ftGameWatch_SpecialN_Phys,
      ftGameWatch_SpecialN_Coll, func_800761C8 },
    { 296, 0x00340511, 0x12000000, ftGameWatch_SpecialAirN_Anim,
      ftGameWatch_SpecialAirN_IASA, ftGameWatch_SpecialAirN_Phys,
      ftGameWatch_SpecialAirN_Coll, func_800761C8 },
    { 297, 0x00340012, 0x13000000, ftGameWatch_SpecialS_Anim,
      ftGameWatch_SpecialS_IASA, ftGameWatch_SpecialS_Phys,
      ftGameWatch_SpecialS_Coll, func_800761C8 },
    { 298, 0x00340012, 0x13000000, ftGameWatch_SpecialS_Anim,
      ftGameWatch_SpecialS_IASA, ftGameWatch_SpecialS_Phys,
      ftGameWatch_SpecialS_Coll, func_800761C8 },
    { 299, 0x00340012, 0x13000000, ftGameWatch_SpecialS_Anim,
      ftGameWatch_SpecialS_IASA, ftGameWatch_SpecialS_Phys,
      ftGameWatch_SpecialS_Coll, func_800761C8 },
    { 300, 0x00340012, 0x13000000, ftGameWatch_SpecialS_Anim,
      ftGameWatch_SpecialS_IASA, ftGameWatch_SpecialS_Phys,
      ftGameWatch_SpecialS_Coll, func_800761C8 },
    { 301, 0x00340012, 0x13000000, ftGameWatch_SpecialS_Anim,
      ftGameWatch_SpecialS_IASA, ftGameWatch_SpecialS_Phys,
      ftGameWatch_SpecialS_Coll, func_800761C8 },
    { 302, 0x00340012, 0x13000000, ftGameWatch_SpecialS_Anim,
      ftGameWatch_SpecialS_IASA, ftGameWatch_SpecialS_Phys,
      ftGameWatch_SpecialS_Coll, func_800761C8 },
    { 303, 0x00340012, 0x13000000, ftGameWatch_SpecialS_Anim,
      ftGameWatch_SpecialS_IASA, ftGameWatch_SpecialS_Phys,
      ftGameWatch_SpecialS_Coll, func_800761C8 },
    { 304, 0x00340012, 0x13000000, ftGameWatch_SpecialS_Anim,
      ftGameWatch_SpecialS_IASA, ftGameWatch_SpecialS_Phys,
      ftGameWatch_SpecialS_Coll, func_800761C8 },
    { 305, 0x00340012, 0x13000000, ftGameWatch_SpecialS_Anim,
      ftGameWatch_SpecialS_IASA, ftGameWatch_SpecialS_Phys,
      ftGameWatch_SpecialS_Coll, func_800761C8 },
    { 306, 0x00340412, 0x13000000, ftGameWatch_SpecialAirS_Anim,
      ftGameWatch_SpecialAirS_IASA, ftGameWatch_SpecialAirS_Phys,
      ftGameWatch_SpecialAirS_Coll, func_800761C8 },
    { 307, 0x00340412, 0x13000000, ftGameWatch_SpecialAirS_Anim,
      ftGameWatch_SpecialAirS_IASA, ftGameWatch_SpecialAirS_Phys,
      ftGameWatch_SpecialAirS_Coll, func_800761C8 },
    { 308, 0x00340412, 0x13000000, ftGameWatch_SpecialAirS_Anim,
      ftGameWatch_SpecialAirS_IASA, ftGameWatch_SpecialAirS_Phys,
      ftGameWatch_SpecialAirS_Coll, func_800761C8 },
    { 309, 0x00340412, 0x13000000, ftGameWatch_SpecialAirS_Anim,
      ftGameWatch_SpecialAirS_IASA, ftGameWatch_SpecialAirS_Phys,
      ftGameWatch_SpecialAirS_Coll, func_800761C8 },
    { 310, 0x00340412, 0x13000000, ftGameWatch_SpecialAirS_Anim,
      ftGameWatch_SpecialAirS_IASA, ftGameWatch_SpecialAirS_Phys,
      ftGameWatch_SpecialAirS_Coll, func_800761C8 },
    { 311, 0x00340412, 0x13000000, ftGameWatch_SpecialAirS_Anim,
      ftGameWatch_SpecialAirS_IASA, ftGameWatch_SpecialAirS_Phys,
      ftGameWatch_SpecialAirS_Coll, func_800761C8 },
    { 312, 0x00340412, 0x13000000, ftGameWatch_SpecialAirS_Anim,
      ftGameWatch_SpecialAirS_IASA, ftGameWatch_SpecialAirS_Phys,
      ftGameWatch_SpecialAirS_Coll, func_800761C8 },
    { 313, 0x00340412, 0x13000000, ftGameWatch_SpecialAirS_Anim,
      ftGameWatch_SpecialAirS_IASA, ftGameWatch_SpecialAirS_Phys,
      ftGameWatch_SpecialAirS_Coll, func_800761C8 },
    { 314, 0x00340412, 0x13000000, ftGameWatch_SpecialAirS_Anim,
      ftGameWatch_SpecialAirS_IASA, ftGameWatch_SpecialAirS_Phys,
      ftGameWatch_SpecialAirS_Coll, func_800761C8 },
    { 315, 0x00340013, 0x14000000, ftGameWatch_SpecialHi_Anim,
      ftGameWatch_SpecialHi_IASA, ftGameWatch_SpecialHi_Phys,
      ftGameWatch_SpecialHi_Coll, func_800761C8 },
    { 316, 0x00340413, 0x14000000, ftGameWatch_SpecialAirHi_Anim,
      ftGameWatch_SpecialAirHi_IASA, ftGameWatch_SpecialAirHi_Phys,
      ftGameWatch_SpecialAirHi_Coll, func_800761C8 },
    { 317, 0x003C0014, 0x15000000, ftGameWatch_SpecialLw_Anim,
      ftGameWatch_SpecialLw_IASA, ftGameWatch_SpecialLw_Phys,
      ftGameWatch_SpecialLw_Coll, func_800761C8 },
    { 318, 0x00340014, 0x15000000, ftGameWatch_SpecialLwCatch_Anim,
      ftGameWatch_SpecialLwCatch_IASA, ftGameWatch_SpecialLwCatch_Phys,
      ftGameWatch_SpecialLwCatch_Coll, func_800761C8 },
    { 319, 0x00340014, 0x15000000, ftGameWatch_SpecialLwShoot_Anim,
      ftGameWatch_SpecialLwShoot_IASA, ftGameWatch_SpecialLwShoot_Phys,
      ftGameWatch_SpecialLwShoot_Coll, func_800761C8 },
    { 320, 0x003C0414, 0x15000000, ftGameWatch_SpecialAirLw_Anim,
      ftGameWatch_SpecialAirLw_IASA, ftGameWatch_SpecialAirLw_Phys,
      ftGameWatch_SpecialAirLw_Coll, func_800761C8 },
    { 321, 0x00340414, 0x15000000, ftGameWatch_SpecialAirLwCatch_Anim,
      ftGameWatch_SpecialAirLwCatch_IASA, ftGameWatch_SpecialAirLwCatch_Phys,
      ftGameWatch_SpecialAirLwCatch_Coll, func_800761C8 },
    { 322, 0x00340414, 0x15000000, ftGameWatch_SpecialAirLwShoot_Anim,
      ftGameWatch_SpecialAirLwShoot_IASA, ftGameWatch_SpecialAirLwShoot_Phys,
      ftGameWatch_SpecialAirLwShoot_Coll, func_800761C8 },
};

char lbl_803D28E8[] = "PlGw.dat";
char lbl_803D28F4[] = "ftDataGamewatch";
char lbl_803D2904[] = "PlGwNr.dat";
char lbl_803D2910[] = "PlyGamewatch5K_Share_joint";
char lbl_803D292C[] = "PlGwAJ.dat";

Fighter_DemoStrings lbl_803D29B8 = {
    "ftDemoResultMotionFileGamewatch",
    "ftDemoIntroMotionFileGamewatch",
    "ftDemoEndingMotionFileGamewatch",
    "ftDemoViWaitMotionFileGamewatch",
};

Fighter_CostumeStrings lbl_803D29C8[] = {
    { lbl_803D2904, lbl_803D2910, NULL },
    { lbl_803D2904, lbl_803D2910, NULL },
    { lbl_803D2904, lbl_803D2910, NULL },
    { lbl_803D2904, lbl_803D2910, NULL },
};

void ftGameWatch_OnDeath(HSD_GObj* fighter_gobj)
{
    Fighter* fp = GET_FIGHTER(fighter_gobj);
    func_80074A4C(fighter_gobj, 0U, 0);
    func_80074A4C(fighter_gobj, 1U, -1);
    func_80074A4C(fighter_gobj, 2U, 0);
    func_80074A4C(fighter_gobj, 3U, 0);
    func_80074A4C(fighter_gobj, 4U, -1);
    func_80074A4C(fighter_gobj, 5U, -1);
    func_80074A4C(fighter_gobj, 6U, -1);
    func_80074A4C(fighter_gobj, 7U, -1);
    func_80074A4C(fighter_gobj, 8U, -1);
    func_80074A4C(fighter_gobj, 9U, -1);
    func_80074A4C(fighter_gobj, 0xAU, -1);
    fp->sa.gaw.x222C_judgeVar1 = 1;
    fp->sa.gaw.x2230_judgeVar2 = 0;
    fp->sa.gaw.x2234 = 0;
    fp->sa.gaw.x223C_panicDamage = 0;
    fp->sa.gaw.x2240_chefVar1 = 1;
    fp->sa.gaw.x2244_chefVar2 = 3;
    fp->sa.gaw.x2248_manholeGObj = NULL;
    fp->sa.gaw.x224C_greenhouseGObj = NULL;
    fp->sa.gaw.x2250_manholeGObj2 = NULL;
    fp->sa.gaw.x2254_fireGObj = NULL;
    fp->sa.gaw.x2258_parachuteGObj = NULL;
    fp->sa.gaw.x225C_turtleGObj = NULL;
    fp->sa.gaw.x2260_sparkyGObj = NULL;
    fp->sa.gaw.x2264_judgementGObj = NULL;
    fp->sa.gaw.x2268_panicGObj = NULL;
    fp->sa.gaw.x226C_rescueGObj = NULL;
}

void ftGameWatch_OnLoad(HSD_GObj* fighter_gobj)
{
    Fighter* fp = GET_FIGHTER(fighter_gobj);
    void** items = fp->x10C_ftData->x48_items;

    fp->x2222_flag.bits.b6 = 0;
    fp->x2223_flag.bits.b1 = 1;
    fp->x2224_flag.bits.b0 = 1;

    PUSH_ATTRS(fp, ftGameWatchAttributes);
    fp->sa.gaw.x2238_panicCharge = GAMEWATCH_PANIC_EMPTY;

    {
        ftGameWatchAttributes* attr = fp->x2D4_specialAttributes;
        fp->x34_scale.z = attr->x0_GAMEWATCH_WIDTH;
        fp->x614 = attr->x14_GAMEWATCH_OUTLINE;
        func_800BFB4C(fighter_gobj,
                      &attr->x4_GAMEWATCH_COLOR[fp->x619_costume_id]);
        fp->x5C8 = items[10];

        func_8026B3F8(items[0], It_Kind_GameWatch_Greenhouse);
        func_8026B3F8(items[1], It_Kind_GameWatch_Manhole);
        func_8026B3F8(items[2], It_Kind_GameWatch_Fire);
        func_8026B3F8(items[3], It_Kind_GameWatch_Parachute);
        func_8026B3F8(items[4], It_Kind_GameWatch_Turtle);
        func_8026B3F8(items[5], It_Kind_GameWatch_Breath);
        func_8026B3F8(items[6], It_Kind_GameWatch_Judge);
        func_8026B3F8(items[7], It_Kind_GameWatch_Panic);
        func_8026B3F8(items[8], It_Kind_GameWatch_Chef);
        func_8026B3F8(items[9], It_Kind_GameWatch_Rescue);
    }
}

void ftGameWatch_OnDamage(HSD_GObj* fighter_gobj)
{
    ftGameWatch_ItemGreenhouseRemove(fighter_gobj);
    ftGameWatch_ItemManholeOnDamage(fighter_gobj);
    ftGameWatch_ItemTorchOnDamage(fighter_gobj);
    ftGameWatch_ItemParachuteRemove(fighter_gobj);
    ftGameWatch_ItemTurtleRemove(fighter_gobj);
    ftGameWatch_ItemSparkyRemove(fighter_gobj);
    ftGameWatch_ItemJudgementRemove(fighter_gobj);
    ftGameWatch_ItemPanicRemove(fighter_gobj);
    ftGameWatch_ItemRescueRemove(fighter_gobj);
}

void ftGameWatch_8014A538(HSD_GObj* fighter_gobj)
{
    Fighter* fp = GET_FIGHTER(fighter_gobj);
    if (fp->xE0_ground_or_air == GA_Air) {
        ftGameWatch_ItemGreenhouseRemove(fighter_gobj);
        ftGameWatch_ItemManholeOnDamage(fighter_gobj);
        ftGameWatch_ItemTorchOnDamage(fighter_gobj);
        ftGameWatch_ItemParachuteRemove(fighter_gobj);
        ftGameWatch_ItemTurtleRemove(fighter_gobj);
        ftGameWatch_ItemSparkyRemove(fighter_gobj);
        ftGameWatch_ItemJudgementRemove(fighter_gobj);
        ftGameWatch_ItemPanicRemove(fighter_gobj);
        ftGameWatch_ItemRescueRemove(fighter_gobj);
    }
}

void ftGameWatch_OnItemPickup(HSD_GObj* fighter_gobj, bool bool)
{
    Fighter_OnItemPickup(fighter_gobj, bool, 1, 1);
}

void ftGameWatch_OnItemInvisible(HSD_GObj* gobj)
{
    Fighter_OnItemInvisible(gobj, 1);
}

// 0x8014A6E0
// https://decomp.me/scratch/ibIxi // Make held item visible (restores picked up
// item's hand held animation)
void ftGameWatch_OnItemVisible(HSD_GObj* fighter_gobj)
{
    Fighter_OnItemVisible(fighter_gobj, 1);
}

// 0x8014A728
// https://decomp.me/scratch/LR8f5 // OnDropItem callback
void ftGameWatch_OnItemDrop(HSD_GObj* fighter_gobj, bool dropItemFlag)
{
    Fighter_OnItemDrop(fighter_gobj, dropItemFlag, 1, 1);
}

// 0x8014A77C
// https://decomp.me/scratch/SX2FV // Set Oil Panic Color Overlay
void ftGameWatch_8014A77C(HSD_GObj* fighter_gobj)
{
    Fighter* fp = GET_FIGHTER(fighter_gobj);

    if (fp->sa.gaw.x2238_panicCharge >= GAMEWATCH_PANIC_FULL) {
        func_800BFFD0(fp, 5, 0);
    }
}

// 0x8014A7B4
// https://decomp.me/scratch/RJvAe // Copy Special Attributes from DAT file
// struct to Fighter*
void ftGameWatch_LoadSpecialAttrs(HSD_GObj* gobj)
{
    COPY_ATTRS(gobj, ftGameWatchAttributes);
}

// 0x8014A7F4
// https://decomp.me/scratch/PFWrJ // Apply color to Mr. Game & Watch's items?
void ftGameWatch_8014A7F4(HSD_GObj* fighter_gobj, ItemModStruct* item_mod)
{
    Fighter* fp = GET_FIGHTER(fighter_gobj);
    ftGameWatchAttributes* gawAttrs = getFtSpecialAttrs(fp);

    item_mod->x0_unk = gawAttrs->x4_GAMEWATCH_COLOR[fp->x619_costume_id];
}

// 0x8014A814
// https://decomp.me/scratch/BRo1r // Apply alt color to Mr. Game & Watch's
// items?
void ftGameWatch_8014A814(HSD_GObj* fighter_gobj, ItemModStruct* item_mod)
{
    Fighter* fp = GET_FIGHTER(fighter_gobj);
    ftGameWatchAttributes* gawAttrs = getFtSpecialAttrs(fp);

    item_mod->x0_unk = gawAttrs->x14_GAMEWATCH_OUTLINE;
}

// 0x8014A828
// https://decomp.me/scratch/muS2N // Mr. Game & Watch's OnAbsorb callback
void ftGameWatch_OnAbsorb(HSD_GObj* fighter_gobj)
{
    ftGameWatch_AbsorbThink_DecideAction(fighter_gobj);
}
