#include <melee/ft/chara/ftGameWatch/ftgamewatch.h>

void ftGameWatch_OnDeath(HSD_GObj* fighter_gobj) 
{
    Fighter* fp = fighter_gobj->user_data;
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
    Fighter* fp = fighter_gobj->user_data;
    void** items = fp->x10C_ftData->x48_items;

    fp->x2222_flag.bits.b6 = 0;
    fp->x2223_flag.bits.b1 = 1;
    fp->x2224_flag.bits.b0 = 1;


    PUSH_ATTRS(fp, ftGameWatchAttributes);
    fp->sa.gaw.x2238_panicCharge = GAMEWATCH_PANIC_EMPTY;

    {
        
        ftGameWatchAttributes *attr = fp->x2D4_specialAttributes;
        fp->x34_scale.z = attr->x0_GAMEWATCH_WIDTH;
        fp->x614 = attr->x14_GAMEWATCH_OUTLINE;
        func_800BFB4C(fighter_gobj, &attr->x4_GAMEWATCH_COLOR[fp->x619_costume_id]);
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
    Fighter* fp = getFighter(fighter_gobj);
    if (fp->xE0_ground_or_air == GA_Air) 
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

void ftGameWatch_OnItemPickup(HSD_GObj* fighter_gobj, BOOL bool) {
    Fighter_OnItemPickup(fighter_gobj, bool, 1, 1);
}

void ftGameWatch_OnItemInvisible(HSD_GObj* gobj) {
    Fighter_OnItemInvisible(gobj, 1);
}

// 0x8014A6E0
// https://decomp.me/scratch/ibIxi // Make held item visible (restores picked up item's hand held animation)
void ftGameWatch_OnItemVisible(HSD_GObj* fighter_gobj)
{
    Fighter_OnItemVisible(fighter_gobj, 1);
}

// 0x8014A728
// https://decomp.me/scratch/LR8f5 // OnDropItem callback
void ftGameWatch_OnItemDrop(HSD_GObj* fighter_gobj, s32 dropItemFlag)
{
    Fighter_OnItemDrop(fighter_gobj, dropItemFlag, 1, 1);
}

// 0x8014A77C
// https://decomp.me/scratch/SX2FV // Set Oil Panic Color Overlay
void ftGameWatch_8014A77C(HSD_GObj* fighter_gobj) 
{
    Fighter* fp = getFighter(fighter_gobj);

    if (fp->sa.gaw.x2238_panicCharge >= GAMEWATCH_PANIC_FULL)
    {
        func_800BFFD0(fp, 5, 0);
    }
}

// 0x8014A7B4
// https://decomp.me/scratch/RJvAe // Copy Special Attributes from DAT file struct to Fighter* 
void ftGameWatch_LoadSpecialAttrs(HSD_GObj* gobj) {
    COPY_ATTRS(gobj, ftGameWatchAttributes);
}

// 0x8014A7F4 
// https://decomp.me/scratch/PFWrJ // Apply color to Mr. Game & Watch's items?
void ftGameWatch_8014A7F4(HSD_GObj* fighter_gobj, ItemModStruct* item_mod)
{
    Fighter* fp = getFighter(fighter_gobj);
    ftGameWatchAttributes* gawAttrs = getFtSpecialAttrs(fp);

    item_mod->x0_unk = gawAttrs->x4_GAMEWATCH_COLOR[fp->x619_costume_id];
}

// 0x8014A814 
// https://decomp.me/scratch/BRo1r // Apply alt color to Mr. Game & Watch's items? 
void ftGameWatch_8014A814(HSD_GObj* fighter_gobj, ItemModStruct* item_mod)
{
    Fighter* fp = getFighter(fighter_gobj);
    ftGameWatchAttributes* gawAttrs = getFtSpecialAttrs(fp);

    item_mod->x0_unk = gawAttrs->x14_GAMEWATCH_OUTLINE;
}

// 0x8014A828
// https://decomp.me/scratch/muS2N // Mr. Game & Watch's OnAbsorb callback 
void ftGameWatch_OnAbsorb(HSD_GObj* fighter_gobj)
{
    ftGameWatch_AbsorbThink_DecideAction(fighter_gobj);
}
