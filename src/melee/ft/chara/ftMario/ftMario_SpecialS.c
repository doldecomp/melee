#include <ftmario.h>
#include <sysdolphin/baselib/random.h>

#include <melee/it/itkind.h>

extern HSD_GObj* func_802B2560(HSD_GObj*,f32,Vec3*,long,u32);

void ftMario_SpecialS_SetCall(Fighter* ft) 
{
    if(ft->sa.mario.x223C_capeGObj != NULL)
    {
        ft->cb.x21E4_callback_OnDeath2 = ftMario_OnTakeDamage;
        ft->cb.x21DC_callback_OnTakeDamage = ftMario_OnTakeDamage;
    }
    ft->cb.x21D4_callback_EnterHitlag = ftMario_SpecialS_EnterHitlag;
    ft->cb.x21D8_callback_ExitHitlag = ftMario_SpecialS_ExitHitlag;
}

// 0x800E1248
// https://decomp.me/scratch/AmeqW
void ftMario_SpecialS_CreateCape(HSD_GObj* gobj) 
{
    Vec3 coords;
    HSD_GObj* gobj2;
    Fighter* ft = getFighter(gobj);
    ftMarioAttributes* sa = (ftMarioAttributes*)ft->x2D4_specialAttributes;
    u8 padding[8];

    if(ft->x2208_ftcmd_var2 == 0) 
    {
        ft->x2208_ftcmd_var2 = 1;
        func_8000B1CC(ft->x5E8_fighterBones[func_8007500C(ft, 0x31)].x0_jobj,NULL,&coords);

        gobj2 = func_802B2560(gobj,ft->x2C_facing_direction,&coords,func_8007500C(ft, 0x31),sa->x14_MARIO_CAPE_IT_KIND);

        ft->sa.mario.x223C_capeGObj = gobj2;
        ft->x1984_heldItemSpec = ft->sa.mario.x223C_capeGObj;
        ftMario_SpecialS_SetCall(ft);
        ft->cb.x21BC_callback_Accessory4 = NULL;
    }
}

// 0x800E132C
void ftMario_SpecialS_SetNULL(HSD_GObj* gobj) 
{
    Fighter* ft = getFighter(gobj);
    ftMario_SpecialS_ExitHitlag(gobj);
    ft->sa.mario.x223C_capeGObj = NULL;
    ft->cb.x21E4_callback_OnDeath2 = NULL;
    ft->cb.x21DC_callback_OnTakeDamage = NULL;
}

// 0x800E1368
void ftMario_SpecialS_RemoveCape(HSD_GObj* gobj)
{
    Fighter* ft = getFighter(gobj);
    u8 padding[8];

    if(ft->sa.mario.x223C_capeGObj != NULL)
    {
        func_802B2674(ft->sa.mario.x223C_capeGObj);
        ftMario_SpecialS_SetNULL(gobj);
    }
}

// 0x800E13C8
void ftMario_SpecialS_EnterHitlag(HSD_GObj* gobj)
{
    Fighter* ft = getFighter(gobj);
    if(ft->sa.mario.x223C_capeGObj != NULL) 
    {
        func_802B26C0(ft->sa.mario.x223C_capeGObj);
    }
}

// 0x800E13F8
void ftMario_SpecialS_ExitHitlag(HSD_GObj* gobj) 
{
    Fighter* ft = getFighter(gobj);
    if(ft->sa.mario.x223C_capeGObj != NULL)
    {
        func_802B26E0(ft->sa.mario.x223C_capeGObj);
    }
}

// 0x800E1428
BOOL ftMario_SpecialS_CheckItemCapeRemove(HSD_GObj* gobj) 
{
    Fighter* ft = getFighter(gobj);

    s32 var0 = ft->x10_action_state_index;

    if ((var0  >= AS_MARIO_SPECIALS) && (var0  <= AS_MARIO_SPECIALAIRS))
    {
        return FALSE;
    } 
    else
    {
        return TRUE;
    }
}

void ftMario_SpecialS_ChangeAction(HSD_GObj* gobj, s32 new_action_state_index) 
{
    Fighter* ft;
    Fighter_ActionStateChange_800693AC(gobj, new_action_state_index,0,NULL,0.0f,1.0f,0.0f);
    func_8006EBA4(gobj);
    ft = getFighter(gobj);
    ft->x2208_ftcmd_var2 = 0;
    ft->x2204_ftcmd_var1 = 0;
    ft->x2200_ftcmd_var0 = 0;
    ft->marioVars[0].SpecialS.isReflect = FALSE;
    ft->cb.x21BC_callback_Accessory4 = ftMario_SpecialS_CreateCape;
}

void ftMario_SpecialS_StartAction(HSD_GObj* gobj)
{
    Fighter* ft;
    u8 unused[8];
    ft = getFighter(gobj);
    ft->x80_self_vel.y = 0.0f;

    ftMario_SpecialS_ChangeAction(gobj, AS_MARIO_SPECIALS);
}


void ftMario_SpecialAirS_StartAction(HSD_GObj* gobj)
{
    Fighter* ft = getFighter(gobj);
    ftMarioAttributes* sa = (ftMarioAttributes*)ft->x2D4_specialAttributes;
    u8 unused[8];

    ft->x80_self_vel.x = (ft->x80_self_vel.x / ((Vec3*)(sa))->x);

    ftMario_SpecialS_ChangeAction(gobj, AS_MARIO_SPECIALAIRS);
}

// 0x800E1550
void ftMario_SpecialS_Anim(HSD_GObj* gobj) 
{
    if (ftAnim_IsFramesRemaining(gobj) == FALSE)
    {
        func_8008A2BC(gobj);
    }
}

// 0x800E158C
void ftMario_SpecialAirS_Anim(HSD_GObj* gobj) 
{
    if (ftAnim_IsFramesRemaining(gobj) == FALSE) 
    {
        func_800CC730(gobj);
    }
}

// 0x800E15C8
void ftMario_SpecialS_IASA(HSD_GObj* gobj) 
{
	return;
}

// 0x800E15CC
void ftMario_SpecialAirS_IASA(HSD_GObj* gobj)
{
	return;
}

extern void ftColl_CreateReflectHit(HSD_GObj*, ReflectDesc*, void(*cb_OnReflect)(HSD_GObj*));

void ftMario_SpecialS_ReflectThink(HSD_GObj* gobj) 
{
    Fighter* ft = getFighter(gobj);
    ftMarioAttributes* sa_tmp = ft->x2D4_specialAttributes;
    
    if ((ft->x2204_ftcmd_var1 == 1U) && ((s32) ft->marioVars[0].SpecialS.isReflect == FALSE)) 
    {
        ft->marioVars[0].SpecialS.isReflect= TRUE;
        ftColl_CreateReflectHit(gobj, &sa_tmp->x60_MARIO_CAPE_REFLECTION, NULL);
    }
    else if ((ft->x2204_ftcmd_var1 == 0U) && ((s32) ft->marioVars[0].SpecialS.isReflect == TRUE)) 
    {
        ft->marioVars[0].SpecialS.isReflect = FALSE;
        ft->x2218_flag.bits.b3 = 0;
    }
    func_8007AEF8(gobj);
}

#define PI_3 (3.14159265359f / 3.0f)

// 0x800E15D0
void ftMario_SpecialS_Phys(HSD_GObj* gobj) 
{
    Fighter* ft;
    u8 unused0[4];
    Vec3 coords;
    u8 unused1[20];

    ft = gobj->user_data;
    if (ft->x2200_ftcmd_var0 == 1U)
    {
        ft->x2200_ftcmd_var0 = 2U;
        func_8000B1CC(ft->x5E8_fighterBones[func_8007500C(ft, 0x4)].x0_jobj,NULL,&coords);

        coords.x += 3.0f * ft->x2C_facing_direction;
		func_800119DC(&coords, 0x78, 0.9f, 0.02f, PI_3);
    }

    func_80084F3C(gobj);
    ftMario_SpecialS_ReflectThink(gobj);
}

// 0x800E16E0
void ftMario_SpecialAirS_Phys(HSD_GObj* gobj) 
{
    u32 ftcmd_var0_tmp;

    Fighter *ft;
    ftMarioAttributes* sa;

    u8 unused0[4];
    Vec3 coords;
    u8 unused1[24];

    ft = gobj->user_data;

    ftcmd_var0_tmp = ft->x2200_ftcmd_var0;
    sa = (ftMarioAttributes*)ft->x2D4_specialAttributes;

    if (ftcmd_var0_tmp >= 1U) 
    {
        if(ftcmd_var0_tmp == 1U) 
        {
            ft->x2200_ftcmd_var0 = 2U;
            if((s32)ft->sa.mario.x2238_isCapeBoost == FALSE) 
            {
                ft->sa.mario.x2238_isCapeBoost = TRUE;
                ft->x80_self_vel.y = sa->x8_MARIO_CAPE_VEL_Y;
            } 
            else 
            {
                ft->x80_self_vel.y = 0.0f;
            }
            func_8000B1CC(ft->x5E8_fighterBones[func_8007500C(ft, 0x4)].x0_jobj,NULL,&coords);
            coords.x += 3.0f * ft->x2C_facing_direction;
            func_800119DC(&coords, 0x78, 3.0f, 0.1f, PI_3);
        }
        func_8007D494(ft, sa->xC_MARIO_CAPE_GRAVITY, sa->x10_MARIO_CAPE_TERMINAL_VELOCITY);
    } 
    else 
    {
        func_8007D4B8(ft);
    }
    func_8007CE94(ft, sa->x4_MARIO_CAPE_VEL_X);
    ftMario_SpecialS_ReflectThink(gobj);
}

// 0x800E1840
void ftMario_SpecialS_Coll(HSD_GObj* gobj) 
{
    if (func_800827A0(gobj) == FALSE)
    {
        ftMario_SpecialS_GroundToAir(gobj);
    }
}

// 0x800E187C
void ftMario_SpecialAirS_Coll(HSD_GObj* gobj) 
{
    if (func_80081D0C(gobj) != FALSE)
    {
        ftMario_SpecialAirS_AirToGround(gobj);
    }
}

void ftMario_SpecialS_UpdateVarsColl(HSD_GObj* gobj) 
{
    Fighter* ft = getFighter(gobj);
    if ((s32) ft->marioVars[0].SpecialS.isReflect != FALSE) 
    {
        ft->x2218_flag.bits.b3 = 1;
    }
    ftMario_SpecialS_SetCall(ft);
    ft->cb.x21BC_callback_Accessory4 = ftMario_SpecialS_CreateCape;
}

// 0x800E18B8
void ftMario_SpecialS_GroundToAir(HSD_GObj* gobj)
{
    Fighter* ft;
    u8 unused[4];

    ft = getFighter(gobj);
    func_8007D5D4(ft);
    Fighter_ActionStateChange_800693AC(gobj, AS_MARIO_SPECIALAIRS, FTMARIO_SPECIALS_COLL_FLAG, NULL, ft->x894_currentAnimFrame, 1.0f, 0.0f);
    if ((s32) ft->x2200_ftcmd_var0 == 1U) 
    {
        ft->x2200_ftcmd_var0 = 2U;
    }

    ftMario_SpecialS_UpdateVarsColl(gobj);
}

// 0x800E198C
void ftMario_SpecialAirS_AirToGround(HSD_GObj* gobj)
{
    Fighter* ft;
    u8 unused[4];

    ft = gobj->user_data;
    ft->sa.mario.x2238_isCapeBoost = FALSE;
    func_8007D7FC(ft);
    Fighter_ActionStateChange_800693AC(gobj, AS_MARIO_SPECIALS, FTMARIO_SPECIALS_COLL_FLAG, NULL, ft->x894_currentAnimFrame, 1.0f, 0.0f);

    ftMario_SpecialS_UpdateVarsColl(gobj);
}
