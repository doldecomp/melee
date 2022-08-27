#include <ft_unknown_006.h>

#include "fighter.h"
#include "ftcommon.h"

#define FIGHTER ((Fighter*) fighterObj->user_data)

// extern HSD_GObjList* lbl_804D782C;
// extern s32 func_80023220(s32);
// extern s32 func_800230C8(s32, s32*, s32*);
// extern s32 func_80023130();
// extern s32 func_800233EC(s32);
// extern s32 func_800C06B4(struct _Fighter*);

//Matches in decomp.me https://decomp.me/scratch/OuucG
s32 func_800877F8(HSD_GObj* fighterObj, s32 arg1)
{
    if (((Fighter*) fighterObj->user_data)->input.x65C_heldInputs & arg1) {
        return 1;
    } else {
        return 0;
    }
}

/*

s32 func_80087818(HSD_GObj* fighterObj, s32 arg1)
{
    if (FIGHTER->input.x668 & arg1) {
        return 1;
    } else {
        return 0;
    }
}

s32 func_80087838(HSD_GObj* fighterObj)
{
    if (FIGHTER->x221D_flag.bits.b7 & 1) {
        return 1;
    } else {
        return 0;
    }
}

s32 func_80087858(HSD_GObj* fighterObj)
{
    if (FIGHTER->x2227_flag.bits.b1 & 1) {
        return 1;
    } else {
        return 0;
    }
}

s32 func_80087878(HSD_GObj* fighterObj, s32 arg1)
{
    if ((FIGHTER->x1968_jumpsUsed <= 1) && (FIGHTER->x10_action_state_index == 0) && (arg1 != 0x23) && (arg1 != 0x24) && (arg1 != 0x25)) {
        return 1;
    } else {
        return 0;
    }
}

s32 func_800878BC(HSD_GObj* fighterObj)
{
    if ((FIGHTER->x1974_heldItem != NULL) && (func_8026B2B4(FIGHTER->x1974_heldItem) == 1)) {
        return 1;
    }
    return 0;
}

s32 func_80087900(HSD_GObj* fighterObj)
{
    if ((FIGHTER->x1974_heldItem != NULL) && (itGetKind(FIGHTER->x1974_heldItem) == 0x1E)) {
        return 1;
    } else {
        return 0;
    }
}

s32 func_80087944(HSD_GObj* fighterObj)
{
    if ((FIGHTER->x1974_heldItem != NULL) && (itGetKind(FIGHTER->x1974_heldItem) == 0x7)) {
        return 1;
    } else {
        return 0;
    }
}

s32 func_80087988(HSD_GObj* fighterObj)
{
    if ((ftGetParasolStatus(fighterObj) == 4) || (ftGetParasolStatus(fighterObj) == 5)) {
        return 1;
    } else {
        return 0;
    }
}

s32 func_800879D8(HSD_GObj* fighterObj)
{
    if (FIGHTER->x1980 != 0) {
        return 1;
    } else {
        return 0;
    }
}

s32 func_800879F8(HSD_GObj* fighterObj)
{
    if (FIGHTER->x221D_flag.bits.b6 & 1) {
        return 1;
    } else {
        return 0;
    }
}

s32 func_80087A18(HSD_GObj* fighterObj)
{
    s32 var1;
    Fighter* fp = fighterObj->user_data;
    if ((fp->x2226_flag.bits.b4) && ((var1 = func_800C06B4(fp), ((var1 == 0x7B) != 0)) || (var1 == 0x80)) && ((fp->x2226_flag.bits.b5))) {
        return 1;
    } else {
        return 0;
    }
}

u8 func_80087A80(HSD_GObj* fighterObj)
{
    return FIGHTER->x2114_SmashAttr.x2134_vibrateFrame;
}

f32 func_80087A8C(HSD_GObj* fighterObj)
{
    return FIGHTER->x2114_SmashAttr.x2138_smashSinceHitbox;
}

s32 func_80087A98(HSD_GObj* fighterObj)
{
    return FIGHTER->x213C;
}

u8 func_80087AA4(HSD_GObj* fighterObj)
{
    return FIGHTER->x2227_flag.bits.b5;
}

u8 func_80087AB4(HSD_GObj* fighterObj)
{
    return FIGHTER->x1968_jumpsUsed;
}

void func_80087AC0(HSD_GObj* fighterObj, s32 arg1)
{
    s32 var0;
    u8 var1;
    u8 var2;
    Fighter* fp = getFighter(fighterObj);
    if (arg1 != 0) {
        var1 = 0;
    } else {
        var1 = 1;
    }
    var0 = var1;
    var2 = fp->x221E_flag.bits.b7;
    var2 = var0;
    fp->x221E_flag.bits.b0 = var2;
}

s32 func_80087AEC(HSD_GObj* fighterObj)
{
    Fighter* fp;

    fp = fighterObj->user_data;
    if ((fp->x34_scale.y != fp->x34_scale.x) || ((fp->x2226_flag.bits.b4) || (fp->x2223_flag.bits.b7) || (fp->x197C != 0))) {
        return 1;
    }
    return 0;
}

s32 func_80087B34(HSD_GObj* fighter_gobj)
{
    f32 atk_shield_kb_x;
    f32* atk_shield_kb_y;
    f32 fVar1;
    f32 fVar2;
    Fighter* fp;
    fp = getFighter(fighter_gobj);
    atk_shield_kb_x = fp->x98_atk_shield_kb.x;
    fVar1 = (fp->x80_self_vel.x * fp->x80_self_vel.x) + (fp->x80_self_vel.y * fp->x80_self_vel.y);
    atk_shield_kb_y = &fp->x98_atk_shield_kb.y;
    fVar2 = (atk_shield_kb_x * atk_shield_kb_x) + ((*atk_shield_kb_y) * (*atk_shield_kb_y));
    if (fVar1 > ((fp->x8c_kb_vel.x * fp->x8c_kb_vel.x) + (fp->x8c_kb_vel.y * fp->x8c_kb_vel.y))) {
        if (fVar1 > ((atk_shield_kb_x * atk_shield_kb_x) + (fp->x98_atk_shield_kb.y * fp->x98_atk_shield_kb.y))) {
            return 0;
        }
        return 2;
    }
    if ((fp->x8c_kb_vel.x * fp->x8c_kb_vel.x) + (fp->x8c_kb_vel.y * fp->x8c_kb_vel.y) > fVar2) {
        return 1;
    }
    return 2;
}

void func_80087BAC(HSD_GObj* fighterObj, s32 arg1)
{
    Fighter* fp = getFighter(fighterObj);
    fp->x2228_flag.bits.b5 = arg1;
}

void func_80087BC0(HSD_GObj* fighterObj, s8 arg1)
{
    Fighter* fp;
    u64 var0;
    fp = getFighter(fighterObj);
    var0 = fp->x1A98;
    func_800A101C(fp, arg1, var0, fp->x1A9C);
}

void func_80087BEC(HSD_GObj* fighterObj, u8 arg1)
{
    Fighter* fp;
    u64 var0;
    fp = getFighter(fighterObj);
    var0 = fp->x1A94;
    func_800A101C(fp, var0, arg1, fp->x1A9C);
}

s32 func_80087C1C()
{
    s32 ftKind;
    u32 var0;
    HSD_GObj* fighterObj;

    var0 = 0;
    for (fighterObj = lbl_804D782C->x20_fighters; fighterObj != 0; fighterObj = fighterObj->next) {
        ftKind = ((Fighter*) fighterObj->user_data)->x4_fighterKind;
        if (ftKind < 27) {
            var0 = var0 | 1 << ftKind;
        }
    }
    return var0;
}

s32 func_80087C58(HSD_GObj* fighterObj)
{
    return FIGHTER->x1988;
}

void func_80087C64(HSD_GObj* fighterObj, s32 arg1)
{
    FIGHTER->x1988 = arg1;
}

s32 func_80087C70(Fighter* fp, s32 arg1)
{
    s32 temp_r0;
    s32 var_r4;
    u8 temp_r3;
    u8 temp_r3_2;
    u8 temp_r3_3;

    var_r4 = arg1;
    temp_r0 = (fp->x2228_flag.bits.b3) & 3;
    switch (temp_r0) {
    case 0:
        temp_r3 = fp->x2220_flag.flags;
        if ((temp_r3 >> 2U) & 1) {
            var_r4 += 1;
        } else if ((temp_r3 >> 1U) & 1) {
            var_r4 += 2;
        }
        break;
    case 1:
        temp_r3_2 = fp->x2220_flag.flags;
        if (!((temp_r3_2 >> 2U) & 1)) {
            if ((temp_r3_2 >> 1U) & 1) {
                var_r4 += 2;
            } else {
                var_r4 += 2;
            }
        }
        break;
    case 2:
        temp_r3_3 = fp->x2220_flag.flags;
        if ((temp_r3_3 >> 2U) & 1) {
            var_r4 += 1;
        } else if (!((temp_r3_3 >> 1U) & 1)) {
            var_r4 += 1;
        }
        break;
    }
    return var_r4;
}
*/