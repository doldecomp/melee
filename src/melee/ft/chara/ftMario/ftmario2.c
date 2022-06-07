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

inline int _func_800E0D1C_helper(Fighter* ft, int* arr, int outpos) {
    int r3;
    r3 = (int)arr[HSD_Randi(outpos)];
    ft->sa.mario.x2230 = ft->sa.mario.x222C;
    ft->sa.mario.x222C = r3;
    return r3;
}

//https://decomp.me/scratch/od8nq
int func_800E0D1C(HSD_GObj* gobj) {
    Fighter* ft;
    int arr[9];
    int r3,i;

    ft = gobj->user_data;

    for (i = r3 = 0; i < 9; i++) {
        if (i != (int)ft->sa.mario.x222C && i != (int)ft->sa.mario.x2230) {
            arr[r3] = i;
            r3++;
        }
    }

    r3 = _func_800E0D1C_helper(ft, arr, r3);

    return r3;
}

void func_800E0DA8(HSD_GObj* gobj) {
    Fighter* ft = gobj->user_data;
    ft->x2200_ftcmd_var0 = 0;
    ft->x2210_ThrowFlags.flags = 0;
    Fighter_ActionStateChange_800693AC(gobj,0x157,0,NULL,0.0f,1.0f,0.0f);
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

//https://decomp.me/scratch/Of8qP
void func_800E0EE0(HSD_GObj* gobj) {
    Vec3 coords;
    Fighter* ft;
    Fighter* ft_2;


    s32 flag_res;

    int rand_val_800E0D1C;

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
            rand_val_800E0D1C = func_800E0D1C(gobj);
            func_802C0510(gobj, &coords, rand_val_800E0D1C, 0x31, ft->x2C_facing_direction);
        }
    }
}

void func_800E1040(HSD_GObj* gobj) {
    Fighter* ft = gobj->user_data;
    ft->x2200_ftcmd_var0 = 0;
    ft->x2210_ThrowFlags.flags = 0;
    Fighter_ActionStateChange_800693AC(gobj,0x158,0,NULL,0.0f,1.0f,0.0f);
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
    Fighter_ActionStateChange_800693AC(gobj,0x158,0x5000,NULL,ft->x894,1.0f,0.0f);

    ft->cb.x21BC_callback_Accessory4 = func_800E0EE0;
}

void func_800E11E0(HSD_GObj* gobj) {
    Fighter* ft = gobj->user_data;
    func_8007D7FC(ft);
    Fighter_ActionStateChange_800693AC(gobj,0x157,0x5000,NULL,ft->x894,1.0f,0.0f);

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
