#include <melee/ft/chara/ftLuigi/ftluigi.h>

// 0x8014267C
// https://decomp.me/scratch/dB9mj // Luigi's grounded Fireball Action State handler
void ftLuigi_SpecialN_StartAction(HSD_GObj* fighter_gobj)
{
    Fighter* fp = getFighter(fighter_gobj);

    fp->x2200_ftcmd_var0 = 0;
    fp->x2210_ThrowFlags.flags = 0;
    Fighter_ActionStateChange_800693AC(fighter_gobj, AS_LUIGI_SPECIALN, 0, NULL, 0.0f, 1.0f, 0.0f);
    func_8006EBA4(fighter_gobj);
    fp->cb.x21BC_callback_Accessory4 = &ftLuigi_SpecialN_FireSpawn;
}

// 0x801426EC - Luigi's aerial Fireball Action State handler
void ftLuigi_SpecialAirN_StartAction(HSD_GObj* fighter_gobj)
{
    Fighter* fp = getFighter(fighter_gobj);

    fp->x2200_ftcmd_var0 = 0;
    fp->x2210_ThrowFlags.flags = 0;
    Fighter_ActionStateChange_800693AC(fighter_gobj, AS_LUIGI_SPECIALAIRN, 0, NULL, 0.0f, 1.0f, 0.0f);
    func_8006EBA4(fighter_gobj);
    fp->cb.x21BC_callback_Accessory4 = &ftLuigi_SpecialN_FireSpawn;
}

// 0x8014275C
// https://decomp.me/scratch/X40ls // Luigi's grounded Fireball Animation callback
void ftLuigi_SpecialN_Anim(HSD_GObj* fighter_gobj) 
{
    if (ftAnim_IsFramesRemaining(fighter_gobj) == FALSE)
    {
        func_8008A2BC(fighter_gobj);
    }
}

// 0x80142798 - Luigi's aerial Fireball Animation callback
void ftLuigi_SpecialAirN_Anim(HSD_GObj* fighter_gobj)
{
    if (ftAnim_IsFramesRemaining(fighter_gobj) == FALSE)
    {
        func_800CC730(fighter_gobj);
    }
}

extern void func_8008A4D4(HSD_GObj*);
extern void func_800CCAAC(HSD_GObj*);

// 0x801427D4
// https://decomp.me/scratch/JesBp // Luigi's grounded Fireball IASA callback
void ftLuigi_SpecialN_IASA(HSD_GObj* fighter_gobj)
{
    if (getFighter(fighter_gobj)->x2200_ftcmd_var0 != 0U)
    {
        func_8008A4D4(fighter_gobj);
    }
}

// 0x80142804 - Luigi's aerial Fireball IASA callback
void ftLuigi_SpecialAirN_IASA(HSD_GObj* fighter_gobj)
{
    if (getFighter(fighter_gobj)->x2200_ftcmd_var0 != 0U)
    {
        func_800CCAAC(fighter_gobj);
    }
}

extern void func_80084F3C(HSD_GObj*);
extern void func_80084DB0(HSD_GObj*);

// 0x80142834 - Luigi's grounded Fireball Physics callback
void ftLuigi_SpecialN_Phys(HSD_GObj* fighter_gobj)
{
    func_80084F3C(fighter_gobj);
}

// 0x80142854 - Luigi's aerial Fireball Physics callback
void ftLuigi_SpecialAirN_Phys(HSD_GObj* fighter_gobj)
{
    func_80084DB0(fighter_gobj);
}

// func_80081D0C

// 0x80142874
// https://decomp.me/scratch/xtPSc // Luigi's grounded Fireball Collision callback
void ftLuigi_SpecialN_Coll(HSD_GObj* fighter_gobj)
{
    Fighter* fp;

    if (func_80082708(fighter_gobj) == FALSE)
    {
        fp = getFighter(fighter_gobj);
        func_8007D5D4(fp);
        Fighter_ActionStateChange_800693AC(fighter_gobj, AS_LUIGI_SPECIALAIRN, FTLUIGI_SPECIALN_COLL_FLAG, NULL, fp->x894_currentAnimFrame, 1.0f, 0.0f);
        fp->cb.x21BC_callback_Accessory4 = &ftLuigi_SpecialN_FireSpawn;
    }
}

// 0x801428E8 - Luigi's aerial Fireball Collision callback
void ftLuigi_SpecialAirN_Coll(HSD_GObj* fighter_gobj)
{
    Fighter* fp;

    if (func_80081D0C(fighter_gobj) != FALSE)
    {
        fp = getFighter(fighter_gobj);
        func_8007D7FC(fp);
        Fighter_ActionStateChange_800693AC(fighter_gobj, AS_LUIGI_SPECIALN, FTLUIGI_SPECIALN_COLL_FLAG, NULL, fp->x894_currentAnimFrame, 1.0f, 0.0f);
        fp->cb.x21BC_callback_Accessory4 = &ftLuigi_SpecialN_FireSpawn;
    }
}

extern void func_802C01AC(HSD_GObj*, Vec3*, s32, f32);

// 0x8014295C
// https://decomp.me/scratch/6miNL // Luigi's Fireball Spawn callback
void ftLuigi_SpecialN_FireSpawn(HSD_GObj* fighter_gobj)
{
    Vec3 sp10;
    Fighter* fp = fighter_gobj->user_data;
    s32 unused;
    BOOL flag;


    if (fp->x2210_ThrowFlags.b0 != 0)
    {
        fp->x2210_ThrowFlags.b0 = 0;
        flag = TRUE;
    }
    else flag = FALSE;

    if (flag != FALSE)
    {
        func_8000B1CC(fp->x5E8_fighterBones[func_8007500C(fp, 0x17)].x0_jobj, NULL, &sp10);
        func_802C01AC(fighter_gobj, &sp10, It_Kind_Luigi_Fire, fp->x2C_facing_direction);
        ef_Spawn(0x507, fighter_gobj, fp->x5E8_fighterBones[func_8007500C(fp, 0x17)].x0_jobj, &fp->x2C_facing_direction);
    }
}

