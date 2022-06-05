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

//https://decomp.me/scratch/8zo4V
void func_800E2050(HSD_GObj* gobj) {
    Fighter* ft;
    ft = gobj->user_data;
    
    func_8007592C(ft, 0, 0.0f);
}

//https://decomp.me/scratch/7yi8z
void func_800E207C(HSD_GObj* gobj) {
    f32 temp_f1;

    Fighter* ft;
    Fighter* ft_2;
    Fighter* ft_3;
    Fighter* ft_4;
    Fighter* ft_5;
    ftMarioAttributes* sa;
    ftMarioAttributes* sa_2;
    void* hsd_obj_ptr;
    u8 padding[40];
    
    ft_2 = ft = gobj->user_data;
    sa = (ftMarioAttributes*)ft_2->x2D4_specialAttributes;
    ft->x2208_ftcmd_var2 = 0;
    temp_f1 = 0.0f;
    Fighter_ActionStateChange_800693AC(gobj, 0x15E, 0, NULL, temp_f1, 1.0f, temp_f1);
    func_8006EBA4(gobj);
    ft_2->x80_self_vel.y = (f32) (sa->x38 - sa->x54);
    func_8007D440(ft_2, sa->x40);
    ft_3 = gobj->user_data;
    sa_2 = (ftMarioAttributes*)ft_3->x2D4_specialAttributes;
    ft_3->x2200_ftcmd_var0 = 0;
    ft_3->x2204_ftcmd_var1 = 0;
    ft_3->x2340_f32 = (f32) 0.0f;
    ft_3->x2344_stateVar2_s32 = (s32) (sa_2->x50 + 1);
    ft_3->x234C_stateVar4 = 0;
    ft_4 = gobj->user_data;
    ft_4->cb.x21DC_callback_OnTakeDamage = &func_800E2050;
    ft_4->cb.x21E4_callback_OnDeath2 = &func_800E2050;
    ft_5 = gobj->user_data;
    hsd_obj_ptr = gobj->hsd_obj;
    ef_Spawn(0x47C, gobj, hsd_obj_ptr, ft_3);
    ft_5->x2219_flag.bits.b0 = 1;
    ft_5->cb.x21D4_callback_EnterHitlag = &efLib_PauseAll;
    ft_5->cb.x21D8_callback_ExitHitlag = &efLib_ResumeAll;
    ft_2->cb.x21D4_callback_EnterHitlag = &efLib_PauseAll;
    ft_2->cb.x21D8_callback_ExitHitlag = &efLib_ResumeAll;
}

//https://decomp.me/scratch/nQT5V
void func_800E2194(HSD_GObj* gobj) {
    f32 temp_f1;
    f32 sub_val;

    Fighter* ft;
    Fighter* ft_2;
    Fighter* ft_3;
    Fighter* ft_4;
    Fighter* ft_5;
    ftMarioAttributes* sa;
    ftMarioAttributes* sa_2;
    void* hsd_obj_ptr;
    u8 padding[40];
    
    ft_2 = ft = gobj->user_data;
    sa = (ftMarioAttributes*)ft_2->x2D4_specialAttributes;
    ft->x2208_ftcmd_var2 = 0;
    temp_f1 = 0.0f;
    Fighter_ActionStateChange_800693AC(gobj, 0x15E, 0, NULL, temp_f1, 1.0f, temp_f1);
    func_8006EBA4(gobj);
    if ((s32) ft_2->sa.mario.x2234 != 0) {
        sub_val = 0.0f;
    } else {
        sub_val = sa->x54;
    }
    ft_2->x80_self_vel.y = (f32) (sa->x38 - sub_val);
    func_8007D440(ft_2, sa->x40);
    ft_3 = gobj->user_data;
    sa_2 = (ftMarioAttributes*)ft_3->x2D4_specialAttributes;
    ft_3->x2200_ftcmd_var0 = 0;
    ft_3->x2204_ftcmd_var1 = 0;
    ft_3->x2340_f32 = (f32) 0.0f;
    ft_3->x2344_stateVar2_s32 = (s32) (sa_2->x50 + 1);
    ft_3->x234C_stateVar4 = 0;
    ft_4 = gobj->user_data;
    ft_4->cb.x21DC_callback_OnTakeDamage = &func_800E2050;
    ft_4->cb.x21E4_callback_OnDeath2 = &func_800E2050;
    ft_5 = gobj->user_data;
    hsd_obj_ptr = gobj->hsd_obj;
    ef_Spawn(0x47C, gobj, hsd_obj_ptr);
    ft_5->x2219_flag.bits.b0 = 1;
    ft_5->cb.x21D4_callback_EnterHitlag = &efLib_PauseAll;
    ft_5->cb.x21D8_callback_ExitHitlag = &efLib_ResumeAll;
    ft_2->cb.x21D4_callback_EnterHitlag = &efLib_PauseAll;
    ft_2->cb.x21D8_callback_ExitHitlag = &efLib_ResumeAll;
}

//https://decomp.me/scratch/FT3Fl
void func_800E22BC(HSD_GObj* gobj) {
    Fighter* ft;
    u8 padding[8];

    if (func_8006F238(gobj) == 0) {
        ft = gobj->user_data;
        ft->cb.x21DC_callback_OnTakeDamage = NULL;
        ft->cb.x21E4_callback_OnDeath2 = NULL;
        func_8008A2BC(gobj);
    }
}

//https://decomp.me/scratch/QF5fb
void func_800E2308(HSD_GObj* gobj) {
    Fighter* ft = getFighter(gobj);
    ftMarioAttributes* sa = (ftMarioAttributes*)ft->x2D4_specialAttributes;
    
    if ((u32) ft->x2204_ftcmd_var1 != 0U) {
        ft->x2204_ftcmd_var1 = 0U;
        ft->sa.mario.x2234 = 1;
    }
    if (func_8006F238(gobj) == 0) {
        Fighter *ft_2 = getFighter(gobj);
        
        ft_2->cb.x21DC_callback_OnTakeDamage = NULL;
        ft_2->cb.x21E4_callback_OnDeath2 = NULL;
        if (0.0d == (f64)sa->x5C) {
            func_800CC730(gobj);
            return;
        }
        func_80096900(gobj, 1, 0, 1, 1.0f, (f32) sa->x5C);
    }
}

void func_800E23DC(void) {
	return;
}

void func_800E23E0(void) {
	return;
}

//https://decomp.me/scratch/aJPK4
void func_800E23E4(HSD_GObj* gobj) {
    f32 flt_var;
    ftMarioAttributes* sa;
    Fighter* ft;
    Fighter* ft_tmp;
    Fighter* ft_2;

    s32 filler[2];

    ft = getFighter(gobj);
    sa = GetMarioAttr(ft);
    
    flt_var = sa->x3C;
    if ((u32) ft->x2200_ftcmd_var0 != 0U) {
        ft->x2340_f32 = (f32) (ft->x2340_f32 - sa->x4C);
        flt_var += ft->x2340_f32;
        if (flt_var < 0.0f) {
            flt_var = 0.0f;
        }
    }
    
    ft_tmp = ft;
    func_8007CADC(ft_tmp, 0.0f, sa->x44, flt_var);
    func_8007CB74(gobj);
    if (((u32) ft->x2208_ftcmd_var2 != 0U) && ((ft->input.x668 & 0x200) != 0)) {
        flt_var = ft->x80_self_vel.y;
        ft->x80_self_vel.y = (f32) (flt_var + sa->x54);
        ft_2 = getFighter(gobj);
        sa = GetMarioAttr(ft_2);
        ft_2->x2208_ftcmd_var2 = 0;
        func_8007D5D4(ft_2);
        Fighter_ActionStateChange_800693AC(gobj, 0x15E, 0x0C4C508A, NULL, ft_2->x894, 1.0f, 0.0f);
        ftComm_ClampFalllSpeed(ft_2, sa->x58);
        func_8007D440(ft_2, sa->x40);
        ft_2->cb.x21D4_callback_EnterHitlag = &efLib_PauseAll;
        ft_2->cb.x21D8_callback_ExitHitlag = &efLib_ResumeAll;
    }
}

//https://decomp.me/scratch/sjB2k
void func_800E2508(HSD_GObj* gobj) {
    f32 flt_var;
    ftMarioAttributes* sa;
    ftMarioAttributes* sa_2;
    Fighter* ft;
    u8 padding[8];

    ft = getFighter(gobj);
    sa = ft->x2D4_specialAttributes;

    if (((s32) ft->sa.mario.x2234 == 0) && ((u32) ft->x2208_ftcmd_var2 != 0U) && ((ft->input.x668 & 0x200) != 0)) {
        func_8007D508(ft, sa->x54, sa->x58);
    }
    func_8007D4B8(ft);
    flt_var = sa->x40;
    sa_2 = ft->x2D4_specialAttributes;
    if ((u32) ft->x2200_ftcmd_var0 != 0U) {
        ft->x2340_f32 = (f32) (ft->x2340_f32 - sa_2->x4C);
        flt_var += ft->x2340_f32;
        if (flt_var < 0.0f) {
            flt_var = 0.0f;
        }
    }
    
    func_8007D3A8(ft, 0.0f, sa->x48, flt_var); 
}

//https://decomp.me/scratch/CsJXX
void func_800E25C4(HSD_GObj* gobj) {
    ftMarioAttributes* sa;
    
    Fighter* ft_2;
    Fighter* ft_3;
    Fighter* ft_4;
    Fighter* ft;
    Fighter* ft_tmp;

    u8 unused[24];

    ft = getFighter(gobj);

    if (ft->xE0_ground_or_air == GA_Ground) {
        if (func_80082888(gobj, &lbl_803C72A0) == 0) {
            ft_2 = gobj->user_data;
            sa = GetMarioAttr(ft_2);
            ft_2->x2208_ftcmd_var2 = 0;
            func_8007D5D4(ft_2);
            Fighter_ActionStateChange_800693AC(gobj, 0x15E, 0x0C4C508A, NULL, ft_2->x894, 1.0f, 0.0f);
            ftComm_ClampFalllSpeed(ft_2, sa->x58);
            func_8007D440(ft_2, sa->x40);
            ft_2->cb.x21D4_callback_EnterHitlag = &efLib_PauseAll;
            ft_2->cb.x21D8_callback_ExitHitlag = &efLib_ResumeAll;
            ft->x234C_stateVar4 = 0;
        } else {
            ft->x234C_stateVar4 = 1;
        }
    } else {
        if (func_800824A0(gobj, &lbl_803C72A0) == 0) {
            ft_3 = gobj->user_data;
            sa = GetMarioAttr(ft_3);
            ft_3->x2208_ftcmd_var2 = 0;
            func_8007D5D4(ft_3);
            Fighter_ActionStateChange_800693AC(gobj, 0x15E, 0x0C4C508A, NULL, ft_3->x894, 1.0f, 0.0f);
            ftComm_ClampFalllSpeed(ft_3, sa->x58);
            func_8007D440(ft_3, sa->x40);
            ft_3->cb.x21D4_callback_EnterHitlag = &efLib_PauseAll;
            ft_3->cb.x21D8_callback_ExitHitlag = &efLib_ResumeAll;
            ft->x234C_stateVar4 = 0;
        } else {
            ft->x234C_stateVar4 = 1;
        }
    }

    ft_tmp = ft_4 = getFighter(gobj);
    if ((ft_tmp->x220C_ftcmd_var3 != 0U) && ((s32)(ft_tmp->x234C_stateVar4) != 0)) {
        func_8007592C(ft_4, 0, ft_4->x2C_facing_direction * func_someCalcAngle_80022C30(ft_4->x6F0_collData.x154_groundNormal.x, ft_4->x6F0_collData.x154_groundNormal.y));
    } else {
        func_8007592C(ft_4, 0, 0.0f);
    }
    
}

void func_800E2778(HSD_GObj* gobj) {
    f32 flt_var;
    
    ftMarioAttributes* sa;
    Fighter* ft_2;
    Fighter* ft_3;
    Fighter* ft_tmp;
    u8 unused[16];
    

    Fighter* ft = gobj->user_data;
    if (func_800824A0(gobj, &lbl_803C72A0) != 0) {
        ft_2 = gobj->user_data;
        sa = GetMarioAttr(ft_2);
        ft_2->x2208_ftcmd_var2 = 0;
        func_8007D7FC(ft_2);
        flt_var = 0.0f;
        ft_2->x80_self_vel.y = flt_var;
        ft_2->sa.mario.x2234 = 0;
        Fighter_ActionStateChange_800693AC(gobj, 0x15D, 0x0C4C508A, NULL, ft_2->x894, 1.0f, flt_var);
        ft_tmp = ft_2;
        func_8007CC78(sa->x3C, ft_tmp);
        ft_2->cb.x21D4_callback_EnterHitlag = &efLib_PauseAll;
        ft_2->cb.x21D8_callback_ExitHitlag = &efLib_ResumeAll;
        ft->x234C_stateVar4 = 1;
    } else {
        ft->x234C_stateVar4 = 0;
    }

    ft_tmp = ft_3 = getFighter(gobj);
    if ((ft_tmp->x220C_ftcmd_var3 != 0U) && ((s32)(ft_tmp->x234C_stateVar4) != 0)) {
        func_8007592C(ft_3, 0, ft_3->x2C_facing_direction * func_someCalcAngle_80022C30(ft_3->x6F0_collData.x154_groundNormal.x, ft_3->x6F0_collData.x154_groundNormal.y));
    } else {
        func_8007592C(ft_3, 0, 0.0f);
    }
}
