#include "ftmario.h"
#include <sysdolphin/baselib/random.h>

#include <melee/it/itkind.h>

extern HSD_GObj* func_802B2560(HSD_GObj*,f32,Vec3*,long,u32);

void _ftMario_check_223C_and_set(Fighter* ft) {
    if(ft->sa.mario.x223C != 0) {
        ft->cb.x21E4_callback_OnDeath2 = ftMario_func_800E0A00;
        ft->cb.x21DC_callback_OnTakeDamage = ftMario_func_800E0A00;
    }
    ft->cb.x21D4_callback_EnterHitlag = ftMario_func_800E13C8;
    ft->cb.x21D8_callback_ExitHitlag = ftMario_func_800E13F8;
}

//https://decomp.me/scratch/AmeqW
void ftMario_func_800E1248(HSD_GObj* gobj) {
    Vec3 coords;
    HSD_GObj* gobj2;
    Fighter* ft = getFighter(gobj);
    ftMarioAttributes* sa = (ftMarioAttributes*)ft->x2D4_specialAttributes;
    u8 padding[8];

    if(ft->x2208_ftcmd_var2 == 0) {
        ft->x2208_ftcmd_var2 = 1;
        func_8000B1CC(ft->x5E8_fighterBones[func_8007500C(ft, 0x31)].x0_jobj,NULL,&coords);

        gobj2 = func_802B2560(gobj,ft->x2C_facing_direction,&coords,func_8007500C(ft, 0x31),sa->x14);

        ft->sa.mario.x223C = gobj2;
        ft->x1984_heldItemSpec = ft->sa.mario.x223C;
        _ftMario_check_223C_and_set(ft);
        ft->cb.x21BC_callback_Accessory4 = NULL;
    }
}

void ftMario_func_800E132C(HSD_GObj* gobj) {
    Fighter* ft = getFighter(gobj);
    ftMario_func_800E13F8(gobj);
    ft->sa.mario.x223C = NULL;
    ft->cb.x21E4_callback_OnDeath2 = NULL;
    ft->cb.x21DC_callback_OnTakeDamage = NULL;
}

void ftMario_func_800E1368(HSD_GObj* gobj) {
    Fighter* ft = getFighter(gobj);
    u8 padding[8];

    if(ft->sa.mario.x223C != NULL){
        func_802B2674(ft->sa.mario.x223C);
        ftMario_func_800E132C(gobj);
    }
}

void ftMario_func_800E13C8(HSD_GObj* gobj) {
    Fighter* ft = getFighter(gobj);
    if(ft->sa.mario.x223C != NULL) {
        func_802B26C0(ft->sa.mario.x223C);
    }
}

void ftMario_func_800E13F8(HSD_GObj* gobj) {
    Fighter* ft = getFighter(gobj);
    if(ft->sa.mario.x223C != NULL) {
        func_802B26E0(ft->sa.mario.x223C);
    }
}

BOOL ftMario_func_800E1428(HSD_GObj* gobj) {
    Fighter* ft = getFighter(gobj);

    s32 var0 = ft->x10_action_state_index;

    if ((var0  >= 0x159) && (var0  <= 0x15A)) {
        return 0;
    } else {
        return 1;
    }
}

void _ftMario_call_FASC_and_set_vars(HSD_GObj* gobj, s32 new_action_state_index) {
    Fighter* ft;
    Fighter_ActionStateChange_800693AC(gobj, new_action_state_index,0,0,0.0f,1.0f,0.0f);
    func_8006EBA4(gobj);
    ft = getFighter(gobj);
    ft->x2208_ftcmd_var2 = 0;
    ft->x2204_ftcmd_var1 = 0;
    ft->x2200_ftcmd_var0 = 0;
    ft->x2340_stateVar1 = 0;
    ft->cb.x21BC_callback_Accessory4 = ftMario_func_800E1248;
}

void ftMario_SpecialS_StartAction(HSD_GObj* gobj) {
    Fighter* ft;
    u8 unused[8];
    ft = getFighter(gobj);
    ft->x80_self_vel.y = 0.0f;

    _ftMario_call_FASC_and_set_vars(gobj, 0x159);
}


void ftMario_SpecialSAir_StartAction(HSD_GObj* gobj) {
    Fighter* ft = getFighter(gobj);
    ftMarioAttributes* sa = (ftMarioAttributes*)ft->x2D4_specialAttributes;
    u8 unused[8];

    ft->x80_self_vel.x = (ft->x80_self_vel.x / ((Vec3*)(sa))->x);

    _ftMario_call_FASC_and_set_vars(gobj, 0x15A);
}

void ftMario_func_800E1550(HSD_GObj* gobj) {
    if (ftAnim_IsFramesRemaining(gobj) == 0) {
        func_8008A2BC(gobj);
    }
}

void ftMario_func_800E158C(HSD_GObj* gobj) {
    if (ftAnim_IsFramesRemaining(gobj) == 0) {
        func_800CC730(gobj);
    }
}

void ftMario_func_800E15C8(void) {
	return;
}

void ftMario_func_800E15CC(void) {
	return;
}

void _ftMario_800E15D0_800E16E0_helper(HSD_GObj* gobj) {
    Fighter* ft = getFighter(gobj);
    u32* sa_tmp  = ((u32*)ft->x2D4_specialAttributes);
    
    if ((ft->x2204_ftcmd_var1 == 1U) && ((s32) ft->x2340_stateVar1 == 0)) {
        ft->x2340_stateVar1= 1;
        ftColl_CreateReflectHit(gobj, sa_tmp + 0x18, 0);
    }
    else if ((ft->x2204_ftcmd_var1 == 0U) && ((s32) ft->x2340_stateVar1 == 1)) {
        ft->x2340_stateVar1 = 0;
        ft->x2218_flag.bits.b3 = 0;
    }
    func_8007AEF8(gobj);
}

#define PI_3 (3.14159265359f / 3.0f)
void ftMario_func_800E15D0(HSD_GObj* gobj) {
    Fighter* ft;
    u8 unused0[4];
    Vec3 coords;
    u8 unused1[20];

    ft = gobj->user_data;
    if (ft->x2200_ftcmd_var0 == 1U) {
        ft->x2200_ftcmd_var0 = 2U;
        func_8000B1CC(ft->x5E8_fighterBones[func_8007500C(ft, 0x4)].x0_jobj,NULL,&coords);

        coords.x += 3.0f * ft->x2C_facing_direction;
		func_800119DC(&coords, 0x78, 0.9f, 0.02f, PI_3);
    }

    func_80084F3C(gobj);
    _ftMario_800E15D0_800E16E0_helper(gobj);
}

void ftMario_func_800E16E0(HSD_GObj* gobj) {
    u32 ftcmd_var0_tmp;

    Fighter *ft;
    ftMarioAttributes* sa;

    u8 unused0[4];
    Vec3 coords;
    u8 unused1[24];

    ft = gobj->user_data;

    ftcmd_var0_tmp = ft->x2200_ftcmd_var0;
    sa = (ftMarioAttributes*)ft->x2D4_specialAttributes;

    if (ftcmd_var0_tmp >= 1U) {
        if(ftcmd_var0_tmp == 1U) {
            ft->x2200_ftcmd_var0 = 2U;
            if((s32)ft->sa.mario.x2238 == 0) {
                ft->sa.mario.x2238 = 1;
                ft->x80_self_vel.y = sa->x08;
            } else {
                ft->x80_self_vel.y = 0.0f;
            }
            func_8000B1CC(ft->x5E8_fighterBones[func_8007500C(ft, 0x4)].x0_jobj,NULL,&coords);
            coords.x += 3.0f * ft->x2C_facing_direction;
            func_800119DC(&coords, 0x78, 3.0f, 0.1f, PI_3);
        }
        func_8007D494(ft, sa->x0C, sa->x10);
    } else {
        func_8007D4B8(ft);
    }
    func_8007CE94(ft, sa->x04);
    _ftMario_800E15D0_800E16E0_helper(gobj);
}

void ftMario_func_800E1840(HSD_GObj* gobj) {
    if (func_800827A0(gobj) == 0) {
        ftMario_func_800E18B8(gobj);
    }
}

void ftMario_func_800E187C(HSD_GObj* gobj) {
    if (func_80081D0C(gobj) != 0) {
        ftMario_func_800E198C(gobj);
    }
}

void _ftMario_800E18B8_800E198C_helper(HSD_GObj* gobj) {
    Fighter* ft = getFighter(gobj);
    if ((s32) ft->x2340_stateVar1 != 0) {
        ft->x2218_flag.bits.b3 = 1;
    }
    _ftMario_check_223C_and_set(ft);
    ft->cb.x21BC_callback_Accessory4 = ftMario_func_800E1248;
}

void ftMario_func_800E18B8(HSD_GObj* gobj) {
    Fighter* ft;
    u8 unused[4];

    ft = getFighter(gobj);
    func_8007D5D4(ft);
    Fighter_ActionStateChange_800693AC(gobj, 0x15A, 0x0C4C508C, NULL, ft->x894_currentAnimFrame, 1.0f, 0.0f);
    if ((s32) ft->x2200_ftcmd_var0 == 1U) {
        ft->x2200_ftcmd_var0 = 2U;
    }

    _ftMario_800E18B8_800E198C_helper(gobj);
}

void ftMario_func_800E198C(HSD_GObj* gobj) {
    Fighter* ft;
    u8 unused[4];

    ft = gobj->user_data;
    ft->sa.mario.x2238 = 0;
    func_8007D7FC(ft);
    Fighter_ActionStateChange_800693AC(gobj, 0x159, 0x0C4C508C, NULL, ft->x894_currentAnimFrame, 1.0f, 0.0f);

    _ftMario_800E18B8_800E198C_helper(gobj);
}
