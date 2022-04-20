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
extern const f32 lbl_804D9198;
extern const f32 lbl_804D919C;
extern const f32 lbl_804D91A0;
extern const f32 lbl_804D91A4;
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

void func_800E0920(Fighter* ft) {
    ftMarioAttributes* sA2 = (ftMarioAttributes*)ft->x2D8_specialAttributes2;
    ftMarioAttributes* ext_attr = (ftMarioAttributes*)ft->x10C_ftData->ext_attr;
    *sA2 = *ext_attr;
    ft->x2D4_specialAttributes = sA2;
}

void ftMario_OnLoad(HSD_GObj* gobj) {
    ftData* ftDataInfo;
    void** items;
    ftMarioAttributes *sA, *sA2, *ext_attr;
    Fighter* ft;
    
    ft = (Fighter*)gobj->user_data;
    ftDataInfo = ft->x10C_ftData;
    items = ftDataInfo->x48_items;

    ft->x2224_flag.bits.b7 = 1;
   
    sA2 = (ftMarioAttributes*)ft->x2D8_specialAttributes2;
    ext_attr = (ftMarioAttributes*)ft->x10C_ftData->ext_attr;

    *sA2 = *ext_attr;

    (ftMarioAttributes*)ft->x2D4_specialAttributes = sA2;

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
    func_800693AC(gobj,0x157,0,0,lbl_804D9198,lbl_804D919C,lbl_804D9198);
    func_8006EBA4(gobj);
    ft->cb.x21BC_callback_Accessory4 = func_800E0EE0;
}

void func_800E0E18(HSD_GObj* gobj) {
    int res;

    res = func_8006F238(gobj);
    if (res == 0) {
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
    int res;

    res = func_80082708(gobj);
    if (res == 0) {
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
    func_800693AC(gobj,0x158,0,0,lbl_804D9198,lbl_804D919C,lbl_804D9198);
    func_8006EBA4(gobj);
    ft->cb.x21BC_callback_Accessory4 = func_800E0EE0;
}

void func_800E10B0(HSD_GObj* gobj) {
    int res;

    res = func_8006F238(gobj);
    if (res == 0) {
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
    int res;

    res = func_80081D0C(gobj);
    if (res != 0) {
        func_800E11E0(gobj);
    }
}

void func_800E1178(HSD_GObj* gobj) {
    Fighter* ft = gobj->user_data;
    func_8007D5D4(ft);
    func_800693AC(gobj,0x158,0x5000,0,ft->x894,lbl_804D919C,lbl_804D9198);

    ft->cb.x21BC_callback_Accessory4 = func_800E0EE0;
}

void func_800E11E0(HSD_GObj* gobj) {
    Fighter* ft = gobj->user_data;
    func_8007D7FC(ft);
    func_800693AC(gobj,0x157,0x5000,0,ft->x894,lbl_804D919C,lbl_804D9198);

    ft->cb.x21BC_callback_Accessory4 = func_800E0EE0;
}

//https://decomp.me/scratch/AmeqW
void func_800E1248(HSD_GObj* gobj) {
    Vec3 coords;
    HSD_GObj* gobj2;
    Fighter* ft = gobj->user_data;
    ftMarioAttributes* sA = (ftMarioAttributes*)ft->x2D4_specialAttributes;
    u8 padding[8];

    if(ft->x2200_ftcmd_var2 == 0) {
        ft->x2200_ftcmd_var2 = 1;
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

    s32 var0 = ft->x10;

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

    //(((Fighter*)(gobj->user_data))->x80_self_vel).y = lbl_804D91A0;
    //func_800693AC(gobj, 0x159,0,0,lbl_804D91A0,lbl_804D91A4,lbl_804D91A0);
    func_800693AC(gobj, 0x159,0,0,f1,lbl_804D91A4,f1);
    func_8006EBA4(gobj);
    ft = gobj->user_data;
    ft->x2200_ftcmd_var2 = 0;
    ft->x2200_ftcmd_var1 = 0;
    ft->x2200_ftcmd_var0 = 0;
    ft->x2340_stateVar1 = 0;
    ft->cb.x21BC_callback_Accessory4 = func_800E1248;
}
