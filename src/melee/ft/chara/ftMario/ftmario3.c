#include "ftmario.h"
#include <sysdolphin/baselib/random.h>

#include <melee/it/id.h>

extern void func_800E1368(HSD_GObj*);
extern void func_8008A4D4(HSD_GObj*);
extern void func_800E0EE0(HSD_GObj*);
extern void func_80084F3C(HSD_GObj*);
extern long func_8007500C(struct _Fighter *, long);
extern void func_8000B1CC(HSD_JObj*, Vec*, Vec*);
extern void func_8029B6F8(f32,HSD_GObj*,Vec*,u8);
extern HSD_GObj* func_802B2560(HSD_GObj*,f32,Vec3*,long,u32);
extern void func_802C0510(HSD_GObj*,Vec*,int,u8,f32);
extern void func_800E13C8(HSD_GObj*);
extern void func_800E13F8(HSD_GObj*);
extern void ef_Spawn(long,...);
//TODO: Replace these
//Currently issues with float placement in sdata2 when replacing these with float literals
extern const ftMarioUnkStruct lbl_803C72A0;
extern s32 lbl_803C5A20[];

void func_800E1450(HSD_GObj* gobj) {
    f32 f1;
    Fighter* ft;
    u8 unused[16];
    ft = gobj->user_data;
    ft->x80_self_vel.y = f1 = 0.0f;

    Fighter_ActionStateChange_800693AC(gobj, 0x159,0,NULL,f1,1.0f,f1);
    func_8006EBA4(gobj);
    ft = gobj->user_data;
    ft->x2208_ftcmd_var2 = 0;
    ft->x2204_ftcmd_var1 = 0;
    ft->x2200_ftcmd_var0 = 0;
    ft->x2340_stateVar1 = 0;
    ft->cb.x21BC_callback_Accessory4 = func_800E1248;
}

void func_800E14C8(HSD_GObj* gobj) {
    f32 f1;
    Fighter* ft = gobj->user_data;
    u8 unused[16];
    
    ft->x80_self_vel.x = (ft->x80_self_vel.x / ((Vec3*)(ft->x2D4_specialAttributes))->x);

    f1 = 0.0f;
    Fighter_ActionStateChange_800693AC(gobj, 0x15A, 0, NULL, f1, 1.0f, f1);
    func_8006EBA4(gobj);
    ft = gobj->user_data;
    ft->x2208_ftcmd_var2 = 0;
    ft->x2204_ftcmd_var1 = 0;
    ft->x2200_ftcmd_var0 = 0;
    ft->x2340_stateVar1 = 0;
    ft->cb.x21BC_callback_Accessory4 = func_800E1248;
}

void func_800E1550(HSD_GObj* gobj) {
    if (func_8006F238(gobj) == 0) {
        func_8008A2BC(gobj);
    }
}

void func_800E158C(HSD_GObj* gobj) {
    if (func_8006F238(gobj) == 0) {
        func_800CC730(gobj);
    }
}

void func_800E15C8(void) {
	return;
}

void func_800E15CC(void) {
	return;
}


#define PI_3 (3.14159265359f / 3.0f)
void func_800E15D0(HSD_GObj* gobj) {    
    u32* sa_tmp;
    u32 x2204_tmp;
    
    Fighter* ft, *ft_2;
    u8 unused0[4];
    Vec3 coords;
    u8 unused1[24];

    ft = gobj->user_data;
    if (ft->x2200_ftcmd_var0 == 1U) {
        ft->x2200_ftcmd_var0 = 2U;
        func_8000B1CC(ft->x5E8_fighterBones[func_8007500C(ft, 0x4)].x0_jobj,NULL,&coords);
		
        coords.x += 3.0f * ft->x2C_facing_direction;
        //func_800119DC(&coords, 0x78, 0.9f, 0.02f, 1.0472f);
		func_800119DC(&coords, 0x78, 0.9f, 0.02f, PI_3);
    }

    func_80084F3C(gobj);
    ft_2 = gobj->user_data;
    x2204_tmp = ft_2->x2204_ftcmd_var1;
    sa_tmp = ((u32*)ft_2->x2D4_specialAttributes);
    if ((x2204_tmp == 1U) && ((s32) ft_2->x2340_stateVar1 == 0)) {
        ft_2->x2340_stateVar1= 1;
        func_8007B23C(gobj, sa_tmp + 0x18, 0);
    }
    else if ((x2204_tmp == 0U) && ((s32) ft_2->x2340_stateVar1 == 1)) {
        ft_2->x2340_stateVar1 = 0;
        ft_2->x2218_flag.bits.b3 = 0;
    }
    func_8007AEF8(gobj);
}

void func_800E16E0(HSD_GObj* gobj) {
    u32 *sa_tmp;
    u32 x2204_tmp;
    u32 ftcmd_var0_tmp;
    
    Fighter *ft, *ft_2;
    ftMarioAttributes* sa;
    
    u8 unused0[4];
    Vec3 coords;
    u8 unused1[28];
    
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
            func_800119DC(&coords, 0x78, 3.0f, 0.1f, 1.0472f);
        }
        func_8007D494(ft, sa->x0C, sa->x10);
    } else {
        func_8007D4B8(ft);
    }
    func_8007CE94(ft, sa->x04);
    ft_2 = gobj->user_data;
    x2204_tmp = ft_2->x2204_ftcmd_var1;
    sa_tmp = ((u32*)ft_2->x2D4_specialAttributes);
    if((x2204_tmp == 1U) && ((s32)ft_2->x2340_stateVar1 == 0)) {
        ft_2->x2340_stateVar1 = 1;
        func_8007B23C(gobj, sa_tmp + 0x18, 0);
    } else if ((x2204_tmp == 0U) && ((s32)ft_2->x2340_stateVar1 == 1)) {
        ft_2->x2340_stateVar1 = 0;
        ft_2->x2218_flag.bits.b3 = 0;
    }
    func_8007AEF8(gobj);
}

void func_800E1840(HSD_GObj* gobj) {
    if (func_800827A0(gobj) == 0) {
        func_800E18B8(gobj);
    }
}

void func_800E187C(HSD_GObj* gobj) {
    if (func_80081D0C(gobj) != 0) {
        func_800E198C(gobj);
    }
}

void func_800E18B8(HSD_GObj* gobj) {
    Fighter* ft, *ft_2;
    u8 unused[8];

    ft = gobj->user_data;
    func_8007D5D4(ft);
    Fighter_ActionStateChange_800693AC(gobj, 0x15A, 0x0C4C508C, NULL, ft->x894, 1.0f, 0.0f);
    if ((s32) ft->x2200_ftcmd_var0 == 1U) {
        ft->x2200_ftcmd_var0 = 2U;
    }
    ft_2 = gobj->user_data;
    if ((s32) ft_2->x2340_stateVar1 != 0) {
        ft_2->x2218_flag.bits.b3 = 1;
    }
    if (ft_2->sa.mario.x223C != NULL) {
        ft_2->cb.x21E4_callback_OnDeath2 = func_800E0A00;
        ft_2->cb.x21DC_callback_OnTakeDamage = func_800E0A00;
    }
    ft_2->cb.x21D4_callback_EnterHitlag = func_800E13C8;
    ft_2->cb.x21D8_callback_ExitHitlag = func_800E13F8;
    ft_2->cb.x21BC_callback_Accessory4 = func_800E1248;
}

void func_800E198C(HSD_GObj* gobj) {
    Fighter* ft, *ft_2;
    u8 unused[8];

    ft = gobj->user_data;
    ft->sa.mario.x2238 = 0;
    func_8007D7FC(ft);
    Fighter_ActionStateChange_800693AC(gobj, 0x159, 0x0C4C508C, NULL, ft->x894, 1.0f, 0.0f);
    ft_2 = gobj->user_data;

    if ((s32) ft_2->x2340_stateVar1 != 0) {
        ft_2->x2218_flag.bits.b3 = 1;
    }
    if (ft_2->sa.mario.x223C != NULL) {
        ft_2->cb.x21E4_callback_OnDeath2 = func_800E0A00;
        ft_2->cb.x21DC_callback_OnTakeDamage = func_800E0A00;
    }
    ft_2->cb.x21D4_callback_EnterHitlag = func_800E13C8;
    ft_2->cb.x21D8_callback_ExitHitlag = func_800E13F8;
    ft_2->cb.x21BC_callback_Accessory4 = func_800E1248;
	
}