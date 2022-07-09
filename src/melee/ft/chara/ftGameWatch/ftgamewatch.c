#include "ftgamewatch.h"

void ftGameWatch_OnDeath(HSD_GObj* fighter_gobj) 
{
    Fighter* fighter = fighter_gobj->user_data;
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
    fighter->sa.gaw.x222C_judgeVar1 = 1;
    fighter->sa.gaw.x2230_judgeVar2 = 0;
    fighter->sa.gaw.x2234 = 0;
    fighter->sa.gaw.x223C_panicDamage = 0;
    fighter->sa.gaw.x2240 = 1;
    fighter->sa.gaw.x2244 = 3;
    fighter->sa.gaw.x2248_manholeGObj = NULL;
    fighter->sa.gaw.x224C_greenhouseGObj = NULL;
    fighter->sa.gaw.x2250_manholeGObj2 = NULL;
    fighter->sa.gaw.x2254_fireGObj = NULL;
    fighter->sa.gaw.x2258_parachuteGObj = NULL;
    fighter->sa.gaw.x225C_turtleGObj = NULL;
    fighter->sa.gaw.x2260_sparkyGObj = NULL;
    fighter->sa.gaw.x2264_judgementGObj = NULL;
    fighter->sa.gaw.x2268_panicGObj = NULL;
    fighter->sa.gaw.x226C_rescueGObj = NULL;
}

void ftGameWatch_OnLoad(HSD_GObj* fighter_gobj) 
{
    Fighter* fighter = fighter_gobj->user_data;
    void** items = fighter->x10C_ftData->x48_items;

    fighter->x2222_flag.bits.b6 = 0;
    fighter->x2223_flag.bits.b1 = 1;
    fighter->x2224_flag.bits.b0 = 1;


    PUSH_ATTRS(fighter, ftGameWatchAttributes);
    fighter->sa.gaw.x2238_panicCharge = GAMEWATCH_PANIC_EMPTY;

    {
        
        ftGameWatchAttributes *attr = fighter->x2D4_specialAttributes;
        fighter->x34_scale.z = attr->x0_GAMEWATCH_WIDTH;
        fighter->x614 = attr->x14_GAMEWATCH_UNK2;
        func_800BFB4C(fighter_gobj, &attr->x4_GAMEWATCH_UNK[fighter->x619_costume_id]);
        fighter->x5C8 = items[10];
        
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
    Fighter* fighter = getFighter(fighter_gobj);
    if (fighter->xE0_ground_or_air == GA_Air) 
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
}

void ftGameWatch_OnItemPickup(HSD_GObj* gobj, BOOL arg1)
{
    s32 result, switched_res, unused;

    Fighter* ft = gobj->user_data;
    result = func_8026B2B4(ft->x1974_heldItem);

    if (result == 0) 
    {
        switched_res = func_8026B320(ft->x1974_heldItem);
        switch (switched_res) 
        {
            case 1:
                func_80070FB4(gobj, 1, 1);
                break;
            case 2:
                func_80070FB4(gobj, 1, 0);
                break;
            case 3:
                func_80070FB4(gobj, 1, 2);
                break;
            case 4:
                func_80070FB4(gobj, 1, 3);
                break;
        }

        if (arg1 != 0) 
        {
            func_80070C48(gobj, 1);
        }
    }
}

// 0x8014A698
// https://decomp.me/scratch/2padD // Make held item invisible (temporarily overrides picked up item's hand held animation, mainly for fighter-exclusive held items)
void func_8014A698(HSD_GObj* fighter_gobj)
{
    Fighter* fp = getFighter(fighter_gobj);

    if (func_8026B2B4(fp->x1974_heldItem) == 0)
    {
        func_80070CC4(fighter_gobj, 1);
    }
}

// 0x8014A6E0
// https://decomp.me/scratch/ibIxi // Make held item visible (restores picked up item's hand held animation)
void func_8014A6E0(HSD_GObj* fighter_gobj)
{
    Fighter* fp = getFighter(fighter_gobj);

    if (func_8026B2B4(fp->x1974_heldItem) == 0)
    {
        func_80070C48(fighter_gobj, 1);
    }
}

// 0x8014A728
// https://decomp.me/scratch/LR8f5 // OnDropItem callback
void func_8014A728(HSD_GObj* fighter_gobj, s32 dropItemFlag)
{
    func_80070FB4(fighter_gobj, 1, -1);
    if (dropItemFlag != 0)
    {
        func_80070CC4(fighter_gobj, 1);
    }
}

// 0x8014A77C
// https://decomp.me/scratch/SX2FV // Set Oil Panic Color Overlay
void func_8014A77C(HSD_GObj* fighter_gobj) 
{
    Fighter* fp = getFighter(fighter_gobj);

    if ((s32)fp->sa.gaw.x2238_panicCharge >= GAMEWATCH_PANIC_FULL)
    {
        func_800BFFD0(fp, 5, 0);
    }
}

// 0x8014A7B4
// https://decomp.me/scratch/RJvAe // Copy Special Attributes from DAT file struct to Fighter* 
void ftGameWatch_CopySpecialAttrs(HSD_GObj* fighter_gobj)
{
    Fighter* fp = getFighter(fighter_gobj);

    ftGameWatchAttributes* ftDataAttrs = (ftGameWatchAttributes*)fp->x10C_ftData->ext_attr;
    ftGameWatchAttributes* copySpecialAttrs = (ftGameWatchAttributes*)fp->x2D4_specialAttributes;

    *copySpecialAttrs = *ftDataAttrs;
}

// 0x8014A7F4 
// https://decomp.me/scratch/PFWrJ // Apply color to Mr. Game & Watch's items?
void func_8014A7F4(HSD_GObj* fighter_gobj, ItemModStruct* item_mod)
{
    Fighter* fp = getFighter(fighter_gobj);
    ftGameWatchAttributes* gawAttrs = getFtSpecialAttrs(fp);

    item_mod->x0_unk = gawAttrs->x4_GAMEWATCH_UNK[fp->x619_costume_id];
}

// 0x8014A814 
// https://decomp.me/scratch/BRo1r // Apply alt color to Mr. Game & Watch's items? 
void func_8014A814(HSD_GObj* fighter_gobj, ItemModStruct* item_mod)
{
    Fighter* fp = getFighter(fighter_gobj);
    ftGameWatchAttributes* gawAttrs = getFtSpecialAttrs(fp);

    item_mod->x0_unk = gawAttrs->x14_GAMEWATCH_UNK2;
}

// 0x8014A828
// https://decomp.me/scratch/muS2N // Mr. Game & Watch's OnAbsorb callback 
void ftGameWatch_OnAbsorb(HSD_GObj* fighter_gobj)
{
    ftGameWatch_AbsorbThink_DecideAction(fighter_gobj);
}