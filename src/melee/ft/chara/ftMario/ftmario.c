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
extern const f32 lbl_804D9198;
extern const f32 lbl_804D919C;
extern const f32 lbl_804D91A0;
extern const f32 lbl_804D91A4;
extern const f32 lbl_804D91A8;
extern const f32 lbl_804D91AC;
extern const f32 lbl_804D91B0;
extern const f32 lbl_804D91B4;
extern const f32 lbl_804D91B8;
extern const f32 lbl_804D91C0;
extern const f32 lbl_804D91C4;
extern const f64 lbl_804D91C8;
extern const f32 lbl_804D91D0;
extern const f64 lbl_804D91D8;
extern s32 lbl_803C5A20[];

inline int _func_800E0EE0_arr_copy(Fighter* ft_2, int* arr)
{
    int i, outpos;
    for (i = outpos = 0; i < 9; i++) {
        if (i != (int)ft_2->sa.mario.x222C && i != (int)ft_2->sa.mario.x2230) {
            arr[outpos] = i;
            outpos++;
        }
    }
    return outpos;
}

void ftMario_OnDeath(HSD_GObj* gobj) {
    Fighter* ft = gobj->user_data;
    func_80074A4C(gobj, 0, 0);
    ft->sa.mario.x222C = 9;
    ft->sa.mario.x2230 = 9;
    ft->sa.mario.x2234 = 0;
    ft->sa.mario.x2238 = 0;
    ft->sa.mario.x223C = NULL;
    ft->sa.mario.x2240 = 0;
}

void ftMario_OnLoadForDrMario(Fighter* ft) {
	PUSH_ATTRS(ft, ftMarioAttributes);
}

void ftMario_OnLoad(HSD_GObj* gobj) {
    ftData* ftDataInfo;
    void** items;
    ftMarioAttributes *sA;
    Fighter* ft;
    
    ft = (Fighter*)gobj->user_data;
    ftDataInfo = ft->x10C_ftData;
    items = ftDataInfo->x48_items;

    ft->x2224_flag.bits.b7 = 1;
   
	PUSH_ATTRS(ft, ftMarioAttributes);

    sA = (ftMarioAttributes*)ft->x2D4_specialAttributes;    

    func_8026B3F8(items[0], It_Kind_MarioFireball);
    func_8026B3F8(items[2], sA->x14);
}

void func_800E0A00(HSD_GObj* gobj)
{
    func_800E1368(gobj);
}

void func_800E0A20(HSD_GObj* gobj, s32 arg1) {
    s32 switched_res, result, unused;

    Fighter* ft = gobj->user_data;
    result = func_8026B2B4(ft->x1974_heldItem);

    if (result == 0) {
        switched_res = func_8026B320(ft->x1974_heldItem);
        switch (switched_res) {
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

        if (arg1 != 0) {
            func_80070C48(gobj, 1);
        }
    }
}

void func_800E0B00(HSD_GObj* gobj) {
    Fighter* ft = gobj->user_data;

    if (func_8026B2B4(ft->x1974_heldItem) == 0) {
        func_80070CC4(gobj, 1);
    }
}

void func_800E0B48(HSD_GObj* gobj) {
    Fighter* ft = gobj->user_data;

    if (func_8026B2B4(ft->x1974_heldItem) == 0) {
        func_80070C48(gobj, 1);
    }
}

void func_800E0B90(HSD_GObj* gobj, s32 arg1)
{
    func_80070FB4(gobj, 1, -1);
    if (arg1 != 0) {
        func_80070CC4(gobj, 1);
    }
}

void func_800E0BE4(HSD_GObj* gobj) {
    Fighter* ft;
    ftData* ftDataInfo;
    ftMarioAttributes *sA, *ext_attr;

    ft = gobj->user_data;
    ftDataInfo = ft->x10C_ftData;
    
    ext_attr = (ftMarioAttributes*)ft->x10C_ftData->ext_attr;
    sA = (ftMarioAttributes*)ft->x2D4_specialAttributes;

    *sA = *ext_attr;
    
}

void func_800E0C24(HSD_GObj* gobj) {
    func_800704F0(gobj, 1, 3.0f);
    func_800704F0(gobj, 0, 3.0f);
}

void func_800E0C68(HSD_GObj* gobj) {
    func_800704F0(gobj, 1, 0.0f);
    func_800704F0(gobj, 0, 0.0f);
}

void func_800E0CAC(s32 arg0, u32* arg1, u32* arg2) {
    if (arg0 != 10) {
        if (arg0 >= 10)
            return;
        if (arg0 < 9)
            return;
        *arg2 = 0xe;
        *arg1 = 0xe;
    } else {
        *arg2 = 0xf;
        *arg1 = 0xf;
    }
}

s32 func_800E0CE0(s32 arg0) {
    int offset;
    
    switch (arg0) {
        case 9:
            offset = 0xe;
            break;
        case 10:
            offset = 0xf;
    }

    return lbl_803C5A20[offset - 0xe];
}

//https://decomp.me/scratch/cdQ5o
int func_800E0D1C(HSD_GObj* gobj) {
    
    Fighter* ft;
    int arr[9];
    int r3,i,outpos;

    u8 padding[8];
    
    ft = gobj->user_data;
    for (i = outpos = 0; i < 9; i++) {
        if (i != (int)ft->sa.mario.x222C && i != (int)ft->sa.mario.x2230) {
            arr[outpos] = i;
            outpos++;
        }
    }

    r3 = (int)arr[HSD_Randi(outpos)];
    ft->sa.mario.x2230 = ft->sa.mario.x222C;
    ft->sa.mario.x222C = r3;

    return r3;
}

void func_800E0DA8(HSD_GObj* gobj) {
    Fighter* ft = gobj->user_data;
    ft->x2200_ftcmd_var0 = 0;
    ft->x2210_ThrowFlags.flags = 0;
    Fighter_ActionStateChange_800693AC(gobj,0x157,0,NULL,lbl_804D9198,lbl_804D919C,lbl_804D9198);
    func_8006EBA4(gobj);
    ft->cb.x21BC_callback_Accessory4 = func_800E0EE0;
}

void func_800E0E18(HSD_GObj* gobj) {
    if (func_8006F238(gobj) == 0) {
        func_8008A2BC(gobj);
    }
}

void func_800E0E54(HSD_GObj* gobj) {
    Fighter* ft;
    ft = gobj->user_data;
    if(ft->x2200_ftcmd_var0 != 0) {
        func_8008A4D4(gobj);
    }
}

void func_800E0E84(HSD_GObj* gobj) {
    func_80084F3C(gobj);
}

void func_800E0EA4(HSD_GObj* gobj) {
    if (func_80082708(gobj) == 0) {
        func_800E1178(gobj);
    }
}

//https://decomp.me/scratch/yJ6cV
void func_800E0EE0(HSD_GObj* gobj) {
    Vec3 coords;
    Fighter* ft;
    Fighter* ft_2;
    
    
    s32 flag_res;
    
    int arr[11];
    int outsize;
    int tmp, tmp2;
    u8 padding[8];

    ft = gobj->user_data;
    
    if (ft->x2210_ThrowFlags.b0 != 0) {
        ft->x2210_ThrowFlags.b0 = 0;
        flag_res = 1;
        
    } else {
        flag_res = 0;
        
    }
    
    if (flag_res != 0) {
        func_8000B1CC(ft->x5E8_fighterBones[func_8007500C(ft, 0x17)].x0_jobj,NULL,&coords);

        if(ft->x4_fighterKind == 0) {
            func_8029B6F8(ft->x2C_facing_direction, gobj,&coords,0x30);
            ef_Spawn(0x47a,gobj,ft->x5E8_fighterBones[func_8007500C(ft, 0x17)].x0_jobj,&ft->x2C_facing_direction);
        } else {
            ft_2 = gobj->user_data;

            outsize = _func_800E0EE0_arr_copy(ft_2, arr);
            tmp = tmp2 = arr[HSD_Randi(outsize)];
            ft_2->sa.mario.x2230 = ft_2->sa.mario.x222C;
            ft_2->sa.mario.x222C = tmp2;
            func_802C0510(gobj, &coords, tmp, 0x31, ft->x2C_facing_direction);
        }
    }
}

void func_800E1040(HSD_GObj* gobj) {
    Fighter* ft = gobj->user_data;
    ft->x2200_ftcmd_var0 = 0;
    ft->x2210_ThrowFlags.flags = 0;
    Fighter_ActionStateChange_800693AC(gobj,0x158,0,NULL,lbl_804D9198,lbl_804D919C,lbl_804D9198);
    func_8006EBA4(gobj);
    ft->cb.x21BC_callback_Accessory4 = func_800E0EE0;
}

void func_800E10B0(HSD_GObj* gobj) {
    if (func_8006F238(gobj) == 0) {
        func_800CC730(gobj);
    }
}

void func_800E10EC(HSD_GObj* gobj) {
    Fighter* ft = gobj->user_data;
    if (ft->x2200_ftcmd_var0 != 0) {
        func_800CCAAC(gobj);
    }
}

void func_800E111C(void) {
    func_80084DB0();
}

void func_800E113C(HSD_GObj* gobj) {
    if (func_80081D0C(gobj) != 0) {
        func_800E11E0(gobj);
    }
}

void func_800E1178(HSD_GObj* gobj) {
    Fighter* ft = gobj->user_data;
    func_8007D5D4(ft);
    Fighter_ActionStateChange_800693AC(gobj,0x158,0x5000,NULL,ft->x894,lbl_804D919C,lbl_804D9198);

    ft->cb.x21BC_callback_Accessory4 = func_800E0EE0;
}

void func_800E11E0(HSD_GObj* gobj) {
    Fighter* ft = gobj->user_data;
    func_8007D7FC(ft);
    Fighter_ActionStateChange_800693AC(gobj,0x157,0x5000,NULL,ft->x894,lbl_804D919C,lbl_804D9198);

    ft->cb.x21BC_callback_Accessory4 = func_800E0EE0;
}

//https://decomp.me/scratch/AmeqW
void func_800E1248(HSD_GObj* gobj) {
    Vec3 coords;
    HSD_GObj* gobj2;
    Fighter* ft = gobj->user_data;
    ftMarioAttributes* sA = (ftMarioAttributes*)ft->x2D4_specialAttributes;
    u8 padding[8];

    if(ft->x2208_ftcmd_var2 == 0) {
        ft->x2208_ftcmd_var2 = 1;
        func_8000B1CC(ft->x5E8_fighterBones[func_8007500C(ft, 0x31)].x0_jobj,NULL,&coords);

        gobj2 = func_802B2560(gobj,ft->x2C_facing_direction,&coords,func_8007500C(ft, 0x31),sA->x14);
        
        ft->sa.mario.x223C = gobj2;
        ft->x1984_heldItemSpec = ft->sa.mario.x223C;
        if(ft->sa.mario.x223C != NULL) {
            ft->cb.x21E4_callback_OnDeath2 = func_800E0A00;
            ft->cb.x21DC_callback_OnTakeDamage = func_800E0A00;
        }
        ft->cb.x21D4_callback_EnterHitlag = func_800E13C8;
        ft->cb.x21D8_callback_ExitHitlag = func_800E13F8;
        ft->cb.x21BC_callback_Accessory4 = NULL;
    }
}

void func_800E132C(HSD_GObj* gobj) {
    Fighter* ft = gobj->user_data;
    func_800E13F8(gobj);
    ft->sa.mario.x223C = NULL;
    ft->cb.x21E4_callback_OnDeath2 = NULL;
    ft->cb.x21DC_callback_OnTakeDamage = NULL;
}

void func_800E1368(HSD_GObj* gobj) {
    Fighter* ft = gobj->user_data;
    int unused, unused2;

    if(ft->sa.mario.x223C != NULL){
        func_802B2674(ft->sa.mario.x223C);
        func_800E132C(gobj);
    }
}

void func_800E13C8(HSD_GObj* gobj) {
    Fighter* ft = gobj->user_data;
    if(ft->sa.mario.x223C != NULL) {
        func_802B26C0(ft->sa.mario.x223C);
    }
}

void func_800E13F8(HSD_GObj* gobj) {
    Fighter* ft = gobj->user_data;
    if(ft->sa.mario.x223C != NULL) {
        func_802B26E0(ft->sa.mario.x223C);
    }
}

BOOL func_800E1428(HSD_GObj* gobj) {
    Fighter* ft = gobj->user_data;

    s32 var0 = ft->x10_action_state_index;

    if ((var0  >= 0x159) && (var0  <= 0x15A)) {
        return 0;
    } else {
        return 1;
    }
}

void func_800E1450(HSD_GObj* gobj) {
    f32 f1;
    Fighter* ft;
    u8 unused[16];
    ft = gobj->user_data;
    ft->x80_self_vel.y = f1 = lbl_804D91A0;

    Fighter_ActionStateChange_800693AC(gobj, 0x159,0,NULL,f1,lbl_804D91A4,f1);
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

    f1 = lbl_804D91A0;
    Fighter_ActionStateChange_800693AC(gobj, 0x15A, 0, NULL, f1, lbl_804D91A4, f1);
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
		
        coords.x += lbl_804D91A8 * ft->x2C_facing_direction;
        func_800119DC(&coords, 0x78, lbl_804D91AC, lbl_804D91B0, lbl_804D91B4);
        
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
                ft->x80_self_vel.y = lbl_804D91A0;
            }
            func_8000B1CC(ft->x5E8_fighterBones[func_8007500C(ft, 0x4)].x0_jobj,NULL,&coords);
            coords.x += lbl_804D91A8 * ft->x2C_facing_direction;
            func_800119DC(&coords, 0x78, lbl_804D91A8, lbl_804D91B8, lbl_804D91B4);
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
    Fighter_ActionStateChange_800693AC(gobj, 0x15A, 0x0C4C508C, NULL, ft->x894, lbl_804D91A4, lbl_804D91A0);
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
    Fighter_ActionStateChange_800693AC(gobj, 0x159, 0x0C4C508C, NULL, ft->x894, lbl_804D91A4, lbl_804D91A0);
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

void func_800E1A54(HSD_GObj* gobj) {
    Fighter* ft;

    ft = gobj->user_data;
    ft->x2200_ftcmd_var0 = 0;
    ft->x2210_ThrowFlags.flags = 0;
	Fighter_ActionStateChange_800693AC(gobj, 0x15B, 0, NULL, lbl_804D91C0, lbl_804D91C4, lbl_804D91C0);
    func_8006EBA4(gobj);
}

void func_800E1AB0(HSD_GObj* gobj) {
    f32 temp_f1;
    Fighter* ft;
    ftMarioAttributes *sA;
    u8 unused[8];

    ft = gobj->user_data;
    sA = (ftMarioAttributes*)ft->x2D4_specialAttributes;
    ft->x2200_ftcmd_var0 = 0;
    ft->x2210_ThrowFlags.flags = 0;
    ft->x80_self_vel.y = temp_f1 = lbl_804D91C0;
    ft->x80_self_vel.x = (f32) (ft->x80_self_vel.x * sA->x2C);
    Fighter_ActionStateChange_800693AC(gobj, 0x15C, 0, NULL, temp_f1, lbl_804D91C4, temp_f1);
    func_8006EBA4(gobj);
}

void func_800E1B24(HSD_GObj* gobj) {
    Fighter* ft;
    ftMarioAttributes *sA;
    u8 unused[8];

    ft = gobj->user_data;
    sA = (ftMarioAttributes*)ft->x2D4_specialAttributes;
    if (func_8006F238(gobj) == 0) {
            func_80096900(gobj, 0, 1, 0, sA->x18, sA->x1C);
    }
}

void func_800E1B84(HSD_GObj* gobj) {
    Fighter* ft;
    ftMarioAttributes *sA;
    u8 unused[16];

    ft = gobj->user_data;
    sA = (ftMarioAttributes*)ft->x2D4_specialAttributes;
    if (func_8006F238(gobj) == 0) {
            func_80096900(gobj, 0, 1, 0, sA->x18, sA->x1C);
    }
}

#ifdef NON_MATCHING
//https://decomp.me/scratch/9AoMu
//TODO: This all matches, just keeping in NON_MATCHING for now until label issues are cleared up
inline void func_800E1BE4_and_800E1D2C(HSD_GObj* gobj) {
    Fighter* ft;
    ftMarioAttributes* sa;

    f32  inputStickangle, lstick_x;
    f32 tmp_expr;
    f32 tmp;

    s32 throwflag_flag;
    ft = gobj->user_data;
    
    sa = (ftMarioAttributes*)ft->x2D4_specialAttributes;

    lstick_x = abs(ft->input.x620_lstick_x);

    if ((s32) ft->x2200_ftcmd_var0 == 0U) {
        if(lstick_x > sa->x24) {
            tmp_expr = (f32) ((f64) sa->x28 * 
                ((f64) (lstick_x - sa->x24) / (1.0d - (f64) sa->x24)));

            tmp = (ft->input.x620_lstick_x > 0.0f) ? -(DEGREES_TO_RADIANS * tmp_expr) : (DEGREES_TO_RADIANS * tmp_expr);
            inputStickangle = ft->x6BC_inputStickangle;

            if (abs(tmp) > abs(inputStickangle)) {
                ft->x6BC_inputStickangle = tmp;
            }
        }
    }

    if (ft->x2210_ThrowFlags.b3 != 0) {
        ft->x2210_ThrowFlags.b3 = 0;
        throwflag_flag= 1;
    } else {
        throwflag_flag = 0;
    }
    if (throwflag_flag != 0) {
        if (abs(ft->input.x620_lstick_x) > sa->x20) {
            func_8007D9FC(ft);
            func_80075AF0(ft, 0, (f32) (HALF_PI * (f64) ft->x2C_facing_direction));
        }
    }
}

void func_800E1BE4(HSD_GObj* gobj) {
    func_800E1BE4_and_800E1D2C(gobj);
}

void func_800E1D2C(HSD_GObj* gobj) {
    u8 padding[16];
    func_800E1BE4_and_800E1D2C(gobj);
}
#else
#define _SDA2_BASE_ 0x804DF9E0
#define lbl_804D91C0_tmp 0x804D91C0
#define lbl_804D91C8 0x804D91C8
#define lbl_804D91D0 0x804D91D0
#define lbl_804D91D8 0x804D91D8
asm void func_800E1BE4(HSD_GObj* gobj) {
	nofralloc
/* 800E1BE4 000DE7C4  7C 08 02 A6 */	mflr r0
/* 800E1BE8 000DE7C8  90 01 00 04 */	stw r0, 4(r1)
/* 800E1BEC 000DE7CC  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 800E1BF0 000DE7D0  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 800E1BF4 000DE7D4  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 800E1BF8 000DE7D8  C0 02 97 E0 */	lfs f0, lbl_804D91C0_tmp-_SDA2_BASE_(r2)
/* 800E1BFC 000DE7DC  C0 9F 06 20 */	lfs f4, 0x620(r31)
/* 800E1C00 000DE7E0  80 9F 02 D4 */	lwz r4, 0x2d4(r31)
/* 800E1C04 000DE7E4  FC 04 00 40 */	fcmpo cr0, f4, f0
/* 800E1C08 000DE7E8  40 80 00 0C */	bge lbl_800E1C14
/* 800E1C0C 000DE7EC  FC 00 20 50 */	fneg f0, f4
/* 800E1C10 000DE7F0  48 00 00 08 */	b lbl_800E1C18
lbl_800E1C14:
/* 800E1C14 000DE7F4  FC 00 20 90 */	fmr f0, f4
lbl_800E1C18:
/* 800E1C18 000DE7F8  80 1F 22 00 */	lwz r0, 0x2200(r31)
/* 800E1C1C 000DE7FC  28 00 00 00 */	cmplwi r0, 0
/* 800E1C20 000DE800  40 82 00 88 */	bne lbl_800E1CA8
/* 800E1C24 000DE804  C0 64 00 24 */	lfs f3, 0x24(r4)
/* 800E1C28 000DE808  FC 00 18 40 */	fcmpo cr0, f0, f3
/* 800E1C2C 000DE80C  40 81 00 7C */	ble lbl_800E1CA8
/* 800E1C30 000DE810  C8 22 97 E8 */	lfd f1, lbl_804D91C8-_SDA2_BASE_(r2)
/* 800E1C34 000DE814  EC 40 18 28 */	fsubs f2, f0, f3
/* 800E1C38 000DE818  C0 02 97 E0 */	lfs f0, lbl_804D91C0_tmp-_SDA2_BASE_(r2)
/* 800E1C3C 000DE81C  FC 21 18 28 */	fsub f1, f1, f3
/* 800E1C40 000DE820  C0 64 00 28 */	lfs f3, 0x28(r4)
/* 800E1C44 000DE824  FC 04 00 40 */	fcmpo cr0, f4, f0
/* 800E1C48 000DE828  FC 02 08 24 */	fdiv f0, f2, f1
/* 800E1C4C 000DE82C  FC 23 00 32 */	fmul f1, f3, f0
/* 800E1C50 000DE830  FC 20 08 18 */	frsp f1, f1
/* 800E1C54 000DE834  40 81 00 14 */	ble lbl_800E1C68
/* 800E1C58 000DE838  C0 02 97 F0 */	lfs f0, lbl_804D91D0-_SDA2_BASE_(r2)
/* 800E1C5C 000DE83C  EC 00 00 72 */	fmuls f0, f0, f1
/* 800E1C60 000DE840  FC 20 00 50 */	fneg f1, f0
/* 800E1C64 000DE844  48 00 00 0C */	b lbl_800E1C70
lbl_800E1C68:
/* 800E1C68 000DE848  C0 02 97 F0 */	lfs f0, lbl_804D91D0-_SDA2_BASE_(r2)
/* 800E1C6C 000DE84C  EC 20 00 72 */	fmuls f1, f0, f1
lbl_800E1C70:
/* 800E1C70 000DE850  C0 5F 06 BC */	lfs f2, 0x6bc(r31)
/* 800E1C74 000DE854  C0 02 97 E0 */	lfs f0, lbl_804D91C0_tmp-_SDA2_BASE_(r2)
/* 800E1C78 000DE858  FC 02 00 40 */	fcmpo cr0, f2, f0
/* 800E1C7C 000DE85C  40 80 00 08 */	bge lbl_800E1C84
/* 800E1C80 000DE860  FC 40 10 50 */	fneg f2, f2
lbl_800E1C84:
/* 800E1C84 000DE864  C0 02 97 E0 */	lfs f0, lbl_804D91C0_tmp-_SDA2_BASE_(r2)
/* 800E1C88 000DE868  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 800E1C8C 000DE86C  40 80 00 0C */	bge lbl_800E1C98
/* 800E1C90 000DE870  FC 00 08 50 */	fneg f0, f1
/* 800E1C94 000DE874  48 00 00 08 */	b lbl_800E1C9C
lbl_800E1C98:
/* 800E1C98 000DE878  FC 00 08 90 */	fmr f0, f1
lbl_800E1C9C:
/* 800E1C9C 000DE87C  FC 00 10 40 */	fcmpo cr0, f0, f2
/* 800E1CA0 000DE880  40 81 00 08 */	ble lbl_800E1CA8
/* 800E1CA4 000DE884  D0 3F 06 BC */	stfs f1, 0x6bc(r31)
lbl_800E1CA8:
/* 800E1CA8 000DE888  88 7F 22 10 */	lbz r3, 0x2210(r31)
/* 800E1CAC 000DE88C  54 60 E7 FF */	rlwinm. r0, r3, 0x1c, 0x1f, 0x1f
/* 800E1CB0 000DE890  41 82 00 18 */	beq lbl_800E1CC8
/* 800E1CB4 000DE894  38 00 00 00 */	li r0, 0
/* 800E1CB8 000DE898  50 03 26 F6 */	rlwimi r3, r0, 4, 0x1b, 0x1b
/* 800E1CBC 000DE89C  98 7F 22 10 */	stb r3, 0x2210(r31)
/* 800E1CC0 000DE8A0  38 00 00 01 */	li r0, 1
/* 800E1CC4 000DE8A4  48 00 00 08 */	b lbl_800E1CCC
lbl_800E1CC8:
/* 800E1CC8 000DE8A8  38 00 00 00 */	li r0, 0
lbl_800E1CCC:
/* 800E1CCC 000DE8AC  2C 00 00 00 */	cmpwi r0, 0
/* 800E1CD0 000DE8B0  41 82 00 48 */	beq lbl_800E1D18
/* 800E1CD4 000DE8B4  C0 3F 06 20 */	lfs f1, 0x620(r31)
/* 800E1CD8 000DE8B8  C0 02 97 E0 */	lfs f0, lbl_804D91C0_tmp-_SDA2_BASE_(r2)
/* 800E1CDC 000DE8BC  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 800E1CE0 000DE8C0  40 80 00 08 */	bge lbl_800E1CE8
/* 800E1CE4 000DE8C4  FC 20 08 50 */	fneg f1, f1
lbl_800E1CE8:
/* 800E1CE8 000DE8C8  C0 04 00 20 */	lfs f0, 0x20(r4)
/* 800E1CEC 000DE8CC  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 800E1CF0 000DE8D0  40 81 00 28 */	ble lbl_800E1D18
/* 800E1CF4 000DE8D4  7F E3 FB 78 */	mr r3, r31
/* 800E1CF8 000DE8D8  4B F9 BD 05 */	bl func_8007D9FC
/* 800E1CFC 000DE8DC  C8 22 97 F8 */	lfd f1, lbl_804D91D8-_SDA2_BASE_(r2)
/* 800E1D00 000DE8E0  7F E3 FB 78 */	mr r3, r31
/* 800E1D04 000DE8E4  C0 1F 00 2C */	lfs f0, 0x2c(r31)
/* 800E1D08 000DE8E8  38 80 00 00 */	li r4, 0
/* 800E1D0C 000DE8EC  FC 21 00 32 */	fmul f1, f1, f0
/* 800E1D10 000DE8F0  FC 20 08 18 */	frsp f1, f1
/* 800E1D14 000DE8F4  4B F9 3D DD */	bl func_80075AF0
lbl_800E1D18:
/* 800E1D18 000DE8F8  80 01 00 24 */	lwz r0, 0x24(r1)
/* 800E1D1C 000DE8FC  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 800E1D20 000DE900  38 21 00 20 */	addi r1, r1, 0x20
/* 800E1D24 000DE904  7C 08 03 A6 */	mtlr r0
/* 800E1D28 000DE908  4E 80 00 20 */	blr 
}
#pragma peephole on

asm void func_800E1D2C(HSD_GObj* gobj) {
	nofralloc
/* 800E1D2C 000DE90C  7C 08 02 A6 */	mflr r0
/* 800E1D30 000DE910  90 01 00 04 */	stw r0, 4(r1)
/* 800E1D34 000DE914  94 21 FF D0 */	stwu r1, -0x30(r1)
/* 800E1D38 000DE918  93 E1 00 2C */	stw r31, 0x2c(r1)
/* 800E1D3C 000DE91C  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 800E1D40 000DE920  C0 02 97 E0 */	lfs f0, lbl_804D91C0_tmp-_SDA2_BASE_(r2)
/* 800E1D44 000DE924  C0 9F 06 20 */	lfs f4, 0x620(r31)
/* 800E1D48 000DE928  80 9F 02 D4 */	lwz r4, 0x2d4(r31)
/* 800E1D4C 000DE92C  FC 04 00 40 */	fcmpo cr0, f4, f0
/* 800E1D50 000DE930  40 80 00 0C */	bge lbl_800E1D5C
/* 800E1D54 000DE934  FC 00 20 50 */	fneg f0, f4
/* 800E1D58 000DE938  48 00 00 08 */	b lbl_800E1D60
lbl_800E1D5C:
/* 800E1D5C 000DE93C  FC 00 20 90 */	fmr f0, f4
lbl_800E1D60:
/* 800E1D60 000DE940  80 1F 22 00 */	lwz r0, 0x2200(r31)
/* 800E1D64 000DE944  28 00 00 00 */	cmplwi r0, 0
/* 800E1D68 000DE948  40 82 00 88 */	bne lbl_800E1DF0
/* 800E1D6C 000DE94C  C0 64 00 24 */	lfs f3, 0x24(r4)
/* 800E1D70 000DE950  FC 00 18 40 */	fcmpo cr0, f0, f3
/* 800E1D74 000DE954  40 81 00 7C */	ble lbl_800E1DF0
/* 800E1D78 000DE958  C8 22 97 E8 */	lfd f1, lbl_804D91C8-_SDA2_BASE_(r2)
/* 800E1D7C 000DE95C  EC 40 18 28 */	fsubs f2, f0, f3
/* 800E1D80 000DE960  C0 02 97 E0 */	lfs f0, lbl_804D91C0_tmp-_SDA2_BASE_(r2)
/* 800E1D84 000DE964  FC 21 18 28 */	fsub f1, f1, f3
/* 800E1D88 000DE968  C0 64 00 28 */	lfs f3, 0x28(r4)
/* 800E1D8C 000DE96C  FC 04 00 40 */	fcmpo cr0, f4, f0
/* 800E1D90 000DE970  FC 02 08 24 */	fdiv f0, f2, f1
/* 800E1D94 000DE974  FC 23 00 32 */	fmul f1, f3, f0
/* 800E1D98 000DE978  FC 20 08 18 */	frsp f1, f1
/* 800E1D9C 000DE97C  40 81 00 14 */	ble lbl_800E1DB0
/* 800E1DA0 000DE980  C0 02 97 F0 */	lfs f0, lbl_804D91D0-_SDA2_BASE_(r2)
/* 800E1DA4 000DE984  EC 00 00 72 */	fmuls f0, f0, f1
/* 800E1DA8 000DE988  FC 20 00 50 */	fneg f1, f0
/* 800E1DAC 000DE98C  48 00 00 0C */	b lbl_800E1DB8
lbl_800E1DB0:
/* 800E1DB0 000DE990  C0 02 97 F0 */	lfs f0, lbl_804D91D0-_SDA2_BASE_(r2)
/* 800E1DB4 000DE994  EC 20 00 72 */	fmuls f1, f0, f1
lbl_800E1DB8:
/* 800E1DB8 000DE998  C0 5F 06 BC */	lfs f2, 0x6bc(r31)
/* 800E1DBC 000DE99C  C0 02 97 E0 */	lfs f0, lbl_804D91C0_tmp-_SDA2_BASE_(r2)
/* 800E1DC0 000DE9A0  FC 02 00 40 */	fcmpo cr0, f2, f0
/* 800E1DC4 000DE9A4  40 80 00 08 */	bge lbl_800E1DCC
/* 800E1DC8 000DE9A8  FC 40 10 50 */	fneg f2, f2
lbl_800E1DCC:
/* 800E1DCC 000DE9AC  C0 02 97 E0 */	lfs f0, lbl_804D91C0_tmp-_SDA2_BASE_(r2)
/* 800E1DD0 000DE9B0  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 800E1DD4 000DE9B4  40 80 00 0C */	bge lbl_800E1DE0
/* 800E1DD8 000DE9B8  FC 00 08 50 */	fneg f0, f1
/* 800E1DDC 000DE9BC  48 00 00 08 */	b lbl_800E1DE4
lbl_800E1DE0:
/* 800E1DE0 000DE9C0  FC 00 08 90 */	fmr f0, f1
lbl_800E1DE4:
/* 800E1DE4 000DE9C4  FC 00 10 40 */	fcmpo cr0, f0, f2
/* 800E1DE8 000DE9C8  40 81 00 08 */	ble lbl_800E1DF0
/* 800E1DEC 000DE9CC  D0 3F 06 BC */	stfs f1, 0x6bc(r31)
lbl_800E1DF0:
/* 800E1DF0 000DE9D0  88 7F 22 10 */	lbz r3, 0x2210(r31)
/* 800E1DF4 000DE9D4  54 60 E7 FF */	rlwinm. r0, r3, 0x1c, 0x1f, 0x1f
/* 800E1DF8 000DE9D8  41 82 00 18 */	beq lbl_800E1E10
/* 800E1DFC 000DE9DC  38 00 00 00 */	li r0, 0
/* 800E1E00 000DE9E0  50 03 26 F6 */	rlwimi r3, r0, 4, 0x1b, 0x1b
/* 800E1E04 000DE9E4  98 7F 22 10 */	stb r3, 0x2210(r31)
/* 800E1E08 000DE9E8  38 00 00 01 */	li r0, 1
/* 800E1E0C 000DE9EC  48 00 00 08 */	b lbl_800E1E14
lbl_800E1E10:
/* 800E1E10 000DE9F0  38 00 00 00 */	li r0, 0
lbl_800E1E14:
/* 800E1E14 000DE9F4  2C 00 00 00 */	cmpwi r0, 0
/* 800E1E18 000DE9F8  41 82 00 48 */	beq lbl_800E1E60
/* 800E1E1C 000DE9FC  C0 3F 06 20 */	lfs f1, 0x620(r31)
/* 800E1E20 000DEA00  C0 02 97 E0 */	lfs f0, lbl_804D91C0_tmp-_SDA2_BASE_(r2)
/* 800E1E24 000DEA04  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 800E1E28 000DEA08  40 80 00 08 */	bge lbl_800E1E30
/* 800E1E2C 000DEA0C  FC 20 08 50 */	fneg f1, f1
lbl_800E1E30:
/* 800E1E30 000DEA10  C0 04 00 20 */	lfs f0, 0x20(r4)
/* 800E1E34 000DEA14  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 800E1E38 000DEA18  40 81 00 28 */	ble lbl_800E1E60
/* 800E1E3C 000DEA1C  7F E3 FB 78 */	mr r3, r31
/* 800E1E40 000DEA20  4B F9 BB BD */	bl func_8007D9FC
/* 800E1E44 000DEA24  C8 22 97 F8 */	lfd f1, lbl_804D91D8-_SDA2_BASE_(r2)
/* 800E1E48 000DEA28  7F E3 FB 78 */	mr r3, r31
/* 800E1E4C 000DEA2C  C0 1F 00 2C */	lfs f0, 0x2c(r31)
/* 800E1E50 000DEA30  38 80 00 00 */	li r4, 0
/* 800E1E54 000DEA34  FC 21 00 32 */	fmul f1, f1, f0
/* 800E1E58 000DEA38  FC 20 08 18 */	frsp f1, f1
/* 800E1E5C 000DEA3C  4B F9 3C 95 */	bl func_80075AF0
lbl_800E1E60:
/* 800E1E60 000DEA40  80 01 00 34 */	lwz r0, 0x34(r1)
/* 800E1E64 000DEA44  83 E1 00 2C */	lwz r31, 0x2c(r1)
/* 800E1E68 000DEA48  38 21 00 30 */	addi r1, r1, 0x30
/* 800E1E6C 000DEA4C  7C 08 03 A6 */	mtlr r0
/* 800E1E70 000DEA50  4E 80 00 20 */	blr 
}
#pragma peephole on
#endif

//https://decomp.me/scratch/8axfI
void func_800E1E74(HSD_GObj* gobj) {
    Fighter* ft = gobj->user_data;
    if (ft->xE0_ground_or_air == 1) {
        func_80085154(gobj);
    } else {
        func_80084FA8(gobj);
    }
}

//https://decomp.me/scratch/1jYsR
void func_800E1EAC(HSD_GObj* gobj) {
    Fighter* ft;
    ftMarioAttributes* sa;
    struct attr* attr_ptr;
    u8 padding[8];
    
    ft = gobj->user_data;
    sa = (ftMarioAttributes*)ft->x2D4_specialAttributes;
    attr_ptr = &(ft->x110_attr);
    
    if ((u32) ft->x2200_ftcmd_var0 != 0U) {
        func_80085154(gobj);
        ft->x80_self_vel.x = (f32) (ft->x80_self_vel.x * sa->x34);
        ft->x80_self_vel.y = (f32) (ft->x80_self_vel.y * sa->x34);
        ft->x80_self_vel.z = (f32) (ft->x80_self_vel.z * sa->x34);
        return;
    }
    //func_8007D494(ft, sa->x30, (ft + 0x110)->unk60);
    func_8007D494(ft, sa->x30, attr_ptr->x170_TerminalVelocity);
    func_8007CF58(ft);
}

//https://decomp.me/scratch/5eIAp
void func_800E1F40(HSD_GObj* gobj) {
    Fighter* ft;
    ftMarioAttributes* sa;

    ft = gobj->user_data;
    

    sa = (ftMarioAttributes*)ft->x2D4_specialAttributes;
    func_800D5CB0(gobj, 0, sa->x1C);
}
