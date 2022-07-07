#include "ftmario.h"
#include <sysdolphin/baselib/random.h>

#include <melee/it/itkind.h>

int _func_800E0D1C_helper(Fighter* ft, int* arr, int outpos) {
    int r3;
    r3 = (int)arr[HSD_Randi(outpos)];
    ft->sa.mario.x2230 = ft->sa.mario.x222C;
    ft->sa.mario.x222C = r3;
    return r3;
}

//https://decomp.me/scratch/od8nq
int ftMario_func_800E0D1C(HSD_GObj* gobj) {
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

void ftMario_SpecialN_StartAction(HSD_GObj* gobj) {
    Fighter* ft = getFighter(gobj);
    ft->x2200_ftcmd_var0 = 0;
    ft->x2210_ThrowFlags.flags = 0;
    Fighter_ActionStateChange_800693AC(gobj,0x157,0,NULL,0.0f,1.0f,0.0f);
    func_8006EBA4(gobj);
    ft->cb.x21BC_callback_Accessory4 = ftMario_func_800E0EE0;
}

void ftMario_func_800E0E18(HSD_GObj* gobj) {
    if (ftAnim_IsFramesRemaining(gobj) == 0) {
        func_8008A2BC(gobj);
    }
}

void ftMario_func_800E0E54(HSD_GObj* gobj) {
    Fighter* ft;
    ft = getFighter(gobj);
    if(ft->x2200_ftcmd_var0 != 0) {
        func_8008A4D4(gobj);
    }
}

void ftMario_func_800E0E84(HSD_GObj* gobj) {
    func_80084F3C(gobj);
}

void ftMario_func_800E0EA4(HSD_GObj* gobj) {
    if (func_80082708(gobj) == 0) {
        ftMario_func_800E1178(gobj);
    }
}

//https://decomp.me/scratch/Of8qP
void ftMario_func_800E0EE0(HSD_GObj* gobj) {
    Vec3 coords;
    Fighter* ft;

    s32 flag_res;

    int rand_val_800E0D1C;

    u8 padding[4];

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
            rand_val_800E0D1C = ftMario_func_800E0D1C(gobj);
            func_802C0510(gobj, &coords, rand_val_800E0D1C, 0x31, ft->x2C_facing_direction);
        }
    }
}

void ftMario_SpecialNAir_StartAction(HSD_GObj* gobj) {
    Fighter* ft = getFighter(gobj);
    ft->x2200_ftcmd_var0 = 0;
    ft->x2210_ThrowFlags.flags = 0;
    Fighter_ActionStateChange_800693AC(gobj,0x158,0,NULL,0.0f,1.0f,0.0f);
    func_8006EBA4(gobj);
    ft->cb.x21BC_callback_Accessory4 = ftMario_func_800E0EE0;
}

void ftMario_func_800E10B0(HSD_GObj* gobj) {
    if (ftAnim_IsFramesRemaining(gobj) == 0) {
        func_800CC730(gobj);
    }
}

void ftMario_func_800E10EC(HSD_GObj* gobj) {
    Fighter* ft = getFighter(gobj);
    if (ft->x2200_ftcmd_var0 != 0) {
        func_800CCAAC(gobj);
    }
}

void ftMario_func_800E111C(void) {
    func_80084DB0();
}

void ftMario_func_800E113C(HSD_GObj* gobj) {
    if (func_80081D0C(gobj) != 0) {
        ftMario_func_800E11E0(gobj);
    }
}

void ftMario_func_800E1178(HSD_GObj* gobj) {
    Fighter* ft = getFighter(gobj);
    func_8007D5D4(ft);
    Fighter_ActionStateChange_800693AC(gobj,0x158,0x5000,NULL,ft->x894_currentAnimFrame,1.0f,0.0f);

    ft->cb.x21BC_callback_Accessory4 = ftMario_func_800E0EE0;
}

void ftMario_func_800E11E0(HSD_GObj* gobj) {
    Fighter* ft = getFighter(gobj);
    func_8007D7FC(ft);
    Fighter_ActionStateChange_800693AC(gobj,0x157,0x5000,NULL,ft->x894_currentAnimFrame,1.0f,0.0f);

    ft->cb.x21BC_callback_Accessory4 = ftMario_func_800E0EE0;
}
