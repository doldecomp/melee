#include <melee/ft/ft_unknown_006.h>

#include <melee/lb/lbunknown_001.h>

#include <sysdolphin/baselib/mtx.h>

#include <melee/ft/chara/ftCLink/ftclink.h>
#include <melee/ft/chara/ftDonkey/ftdonkey.h>
#include <melee/ft/chara/ftFox/ftfox.h>
#include <melee/ft/chara/ftGameWatch/ftgamewatch.h>
#include <melee/ft/chara/ftNess/ftNess.h>
#include <melee/ft/chara/ftYoshi/ftyoshi.h>
#include <melee/ft/code_80081B38.h>
#include <melee/ft/fighter.h>
#include <melee/ft/ftcoll.h>
#include <melee/ft/ftcommon.h>
#include <melee/ft/ftcoll.h>

#include <melee/it/item.h>

#define TEST(expr) (expr) ? TRUE : FALSE

extern s32 func_80023220(s32);
extern s32 func_800230C8(s32, s32*, s32*);
extern s32 func_80023130();
extern s32 func_800233EC(s32);
extern s32 func_800C06B4(struct _Fighter*);

s32 func_800877F8(HSD_GObj* fighter_gobj, s32 arg1)
{
    Fighter* fp = getFighter(fighter_gobj);
    return TEST(fp->input.x65C_heldInputs & arg1);
}

s32 func_80087818(HSD_GObj* fighter_gobj, s32 arg1)
{
    Fighter* fp = getFighter(fighter_gobj);
    return TEST(fp->input.x668 & arg1);
}

s32 func_80087838(HSD_GObj* fighter_gobj)
{
    Fighter* fp = getFighter(fighter_gobj);
    return TEST(fp->x221D_flag.bits.b7 & 1);
}

s32 func_80087858(HSD_GObj* fighter_gobj)
{
    Fighter* fp = getFighter(fighter_gobj);
    return TEST(fp->x2227_flag.bits.b1 & 1);
}

s32 func_80087878(HSD_GObj* fighter_gobj, s32 arg1)
{
    Fighter* fp = getFighter(fighter_gobj);

    if ((fp->x1968_jumpsUsed <= 1) && (fp->x10_action_state_index == 0) && (arg1 != 0x23) && (arg1 != 0x24) && (arg1 != 0x25))
        return TRUE;

    return FALSE;
}

s32 func_800878BC(HSD_GObj* fighter_gobj)
{
    Fighter* fp = getFighter(fighter_gobj);

    if ((fp->x1974_heldItem != NULL) && (func_8026B2B4(fp->x1974_heldItem) == 1))
        return TRUE;

    return FALSE;
}

s32 func_80087900(HSD_GObj* fighter_gobj)
{
    Fighter* fp = getFighter(fighter_gobj);

    if ((fp->x1974_heldItem != NULL) && (itGetKind(fp->x1974_heldItem) == 0x1E))
        return TRUE;

    return FALSE;
}

s32 func_80087944(HSD_GObj* fighter_gobj)
{
    Fighter* fp = getFighter(fighter_gobj);

    if ((fp->x1974_heldItem != NULL) && (itGetKind(fp->x1974_heldItem) == 0x7))
        return TRUE;

    return FALSE;
}

s32 func_80087988(HSD_GObj* fighter_gobj)
{
    if ((ftGetParasolStatus(fighter_gobj) == 4) || (ftGetParasolStatus(fighter_gobj) == 5))
        return TRUE;

    return FALSE;
}

s32 func_800879D8(HSD_GObj* fighter_gobj)
{
    Fighter* fp = getFighter(fighter_gobj);

    if (fp->x1980 != 0)
        return TRUE;

    return FALSE;
}

s32 func_800879F8(HSD_GObj* fighter_gobj)
{
    Fighter* fp = getFighter(fighter_gobj);

    if (fp->x221D_flag.bits.b6 & 1)
        return TRUE;

    return FALSE;
}

s32 func_80087A18(HSD_GObj* fighter_gobj)
{
    s32 var1;
    Fighter* fp = fighter_gobj->user_data;

    if ((fp->x2226_flag.bits.b4) && ((var1 = func_800C06B4(fp), ((var1 == 0x7B) != 0)) || (var1 == 0x80)) && ((fp->x2226_flag.bits.b5)))
        return TRUE;

    return FALSE;
}

u8 func_80087A80(HSD_GObj* fighter_gobj)
{
    Fighter* fp = getFighter(fighter_gobj);
    return fp->x2114_SmashAttr.x2134_vibrateFrame;
}

f32 func_80087A8C(HSD_GObj* fighter_gobj)
{
    Fighter* fp = getFighter(fighter_gobj);
    return fp->x2114_SmashAttr.x2138_smashSinceHitbox;
}

s32 func_80087A98(HSD_GObj* fighter_gobj)
{
    Fighter* fp = getFighter(fighter_gobj);
    return fp->x213C;
}

u8 func_80087AA4(HSD_GObj* fighter_gobj)
{
    Fighter* fp = getFighter(fighter_gobj);
    return fp->x2227_flag.bits.b5;
}

u8 func_80087AB4(HSD_GObj* fighter_gobj)
{
    Fighter* fp = getFighter(fighter_gobj);
    return fp->x1968_jumpsUsed;
}

void func_80087AC0(HSD_GObj* fighter_gobj, s32 arg1)
{
    s32 var0;
    u8 var1;
    u8 var2;
    Fighter* fp = getFighter(fighter_gobj);
    if (arg1 != 0) {
        var1 = FALSE;
    } else {
        var1 = TRUE;
    }
    var0 = var1;
    var2 = fp->x221E_flag.bits.b7;
    var2 = var0;
    fp->x221E_flag.bits.b0 = var2;
}

s32 func_80087AEC(HSD_GObj* fighter_gobj)
{
    Fighter* fp = fighter_gobj->user_data;

    if ((fp->x34_scale.y != fp->x34_scale.x) || ((fp->x2226_flag.bits.b4) || (fp->x2223_flag.bits.b7) || (fp->x197C != 0)))
        return TRUE;

    return FALSE;
}

s32 func_80087B34(HSD_GObj* fighter_gobj)
{
    Fighter* fp = getFighter(fighter_gobj);
    f32 atk_shield_kb_x = fp->x98_atk_shield_kb.x;
    f32 fVar1 = (fp->x80_self_vel.x * fp->x80_self_vel.x) + (fp->x80_self_vel.y * fp->x80_self_vel.y);
    f32* atk_shield_kb_y = &fp->x98_atk_shield_kb.y;
    f32 fVar2 = (atk_shield_kb_x * atk_shield_kb_x) + ((*atk_shield_kb_y) * (*atk_shield_kb_y));

    if (fVar1 > ((fp->x8c_kb_vel.x * fp->x8c_kb_vel.x) + (fp->x8c_kb_vel.y * fp->x8c_kb_vel.y))) {
        if (fVar1 > ((atk_shield_kb_x * atk_shield_kb_x) + (fp->x98_atk_shield_kb.y * fp->x98_atk_shield_kb.y)))
            return 0;

        return 2;
    }

    if ((fp->x8c_kb_vel.x * fp->x8c_kb_vel.x) + (fp->x8c_kb_vel.y * fp->x8c_kb_vel.y) > fVar2)
        return 1;

    return 2;
}

void func_80087BAC(HSD_GObj* fighter_gobj, s32 arg1)
{
    Fighter* fp = getFighter(fighter_gobj);
    fp->x2228_flag.bits.b5 = arg1;
}

void func_80087BC0(HSD_GObj* fighter_gobj, s8 arg1)
{
    Fighter* fp = getFighter(fighter_gobj);
    u64 var0 = fp->x1A98;
    func_800A101C(fp, arg1, var0, fp->x1A9C);
}

void func_80087BEC(HSD_GObj* fighter_gobj, u8 arg1)
{
    Fighter* fp = getFighter(fighter_gobj);
    u64 var0 = fp->x1A94;
    func_800A101C(fp, var0, arg1, fp->x1A9C);
}

s32 func_80087C1C()
{
    HSD_GObj* fighter_gobj;
    s32 ftKind;
    u32 result = 0;

    for (fighter_gobj = lbl_804D782C->x20_fighters; fighter_gobj != 0; fighter_gobj = fighter_gobj->next) {
        ftKind = ((Fighter*) fighter_gobj->user_data)->x4_fighterKind;
        if (ftKind < 27) {
            result = result | 1 << ftKind;
        }
    }
    return result;
}

s32 func_80087C58(HSD_GObj* fighter_gobj)
{
    Fighter* fp = getFighter(fighter_gobj);
    return fp->x1988;
}

void func_80087C64(HSD_GObj* fighter_gobj, s32 arg1)
{
    Fighter* fp = getFighter(fighter_gobj);
    fp->x1988 = arg1;
}

s32 func_80087C70(Fighter* fp, s32 arg1)
{
    u8 temp_r3;
    u8 temp_r3_2;
    u8 temp_r3_3;

    s32 var_r4 = arg1;
    s32 temp_r0 = (fp->x2228_flag.bits.b3) & 3;

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

#ifdef NON_MATCHING

// https://decomp.me/scratch/QCKGz
s32 func_80087D0C(Fighter* fighter, s32 arg1)
{
    s32 sp18;
    s32 sp14;
    enum FighterKind ftKind;
    s32 var_r30;
    s32 sfx_id;
    int new_var;
    s32 ssm_id;
    s32 var_r4;

    sfx_id = func_800233EC(arg1);
    ssm_id = func_80023130();
    switch (ssm_id) {
    case 0:
        switch (sfx_id) {
        case 0x197:
        case 0x1D3:
        case 0x1F7:
        case 0x203:
        case 0x46D03:
        case 0x1FD:
        case 0x1E5:
        case 0x1EB:
        case 0x1DF:
        case 0x1D9:
        case 0x1B5:
        case 0x1C7:
        case 0x1CD:
        case 0x1C1:
        case 0x1BB:
        case 0x1A9:
        case 0x1AF:
        case 0x1A3:
        case 0x19D:
        case 0x179:
        case 0x18B:
        case 0x191:
        case 0x185:
        case 0x17F:
        case 0x173:
            sfx_id = func_80087C70(fighter, sfx_id); // Player_AdjustSFXIDForSizeModifier(r3=fighter,r4=sfxID)
            if (fighter->x2223_flag.bits.b7) {
                sfx_id += 3;
            }
            break;
        case 0x167:
        case 0x170:
        case 0x16D:
        case 0x16A:
        case 0x158:
        case 0x161:
        case 0x164:
        case 0x15E:
        case 0x15B:
        case 0x152:
        case 0x155:
        case 0x14F:
        case 0x14C:
            sfx_id = func_80087C70(fighter, sfx_id); // Player_AdjustSFXIDForSizeModifier(r3=fighter,r4=sfxID)
            break;
        }
        break;
    case 13:
        ftKind = fighter->x4_fighterKind;
        if ((ftKind < 0xc) && (10 > ftKind)) {

            if ((0x1fbfd < sfx_id) &&
                ((sfx_id < 0x1fc62 && (func_80080144(fighter) == 1)))) {
                sfx_id += 0x66;
            }
            if (((0x1fc63 < sfx_id) && (sfx_id < 0x1fcc8)) && (func_80080144(fighter) != 1)) {
                sfx_id -= 0x66;
            }
        }
    case 6:
    case 7:
    case 8:
    case 9:
    case 10:
    case 11:
    case 12:
    case 14:
    case 15:
    case 16:
    case 17:
    case 18:
    case 19:
    case 20:
    case 21:
    case 22:
    case 23:
    case 24:
    case 25:
    case 26:
    case 27:
    case 28:
    case 29:
    case 30:
    case 31:
    case 33:
        if ((func_800230C8(ssm_id, &sp18, &sp14) == 0) && (sfx_id >= ((s32) (sp18 + func_80023220(ssm_id))))) {
            sfx_id = func_80087C70(fighter, sfx_id);
        }
        break;
    default:
        break;
    }

    return sfx_id;
}

#else

#pragma push
asm s32 func_80087D0C(Fighter* fighter, s32 arg1)
{ // clang-format off
    nofralloc
/* 80087D0C 000848EC  7C 08 02 A6 */	mflr r0
/* 80087D10 000848F0  90 01 00 04 */	stw r0, 4(r1)
/* 80087D14 000848F4  94 21 FF D0 */	stwu r1, -0x30(r1)
/* 80087D18 000848F8  93 E1 00 2C */	stw r31, 0x2c(r1)
/* 80087D1C 000848FC  93 C1 00 28 */	stw r30, 0x28(r1)
/* 80087D20 00084900  93 A1 00 24 */	stw r29, 0x24(r1)
/* 80087D24 00084904  3B A3 00 00 */	addi r29, r3, 0
/* 80087D28 00084908  38 64 00 00 */	addi r3, r4, 0
/* 80087D2C 0008490C  4B F9 B6 C1 */	bl func_800233EC
/* 80087D30 00084910  7C 7F 1B 78 */	mr r31, r3
/* 80087D34 00084914  4B F9 B3 FD */	bl func_80023130
/* 80087D38 00084918  3B C3 00 00 */	addi r30, r3, 0
/* 80087D3C 0008491C  2C 1E 00 0D */	cmpwi r30, 0xd
/* 80087D40 00084920  41 82 02 44 */	beq lbl_80087F84
/* 80087D44 00084924  40 80 00 1C */	bge lbl_80087D60
/* 80087D48 00084928  2C 1E 00 00 */	cmpwi r30, 0
/* 80087D4C 0008492C  41 82 00 2C */	beq lbl_80087D78
/* 80087D50 00084930  41 80 02 EC */	blt lbl_8008803C
/* 80087D54 00084934  2C 1E 00 06 */	cmpwi r30, 6
/* 80087D58 00084938  40 80 02 A4 */	bge lbl_80087FFC
/* 80087D5C 0008493C  48 00 02 E0 */	b lbl_8008803C
lbl_80087D60:
/* 80087D60 00084940  2C 1E 00 21 */	cmpwi r30, 0x21
/* 80087D64 00084944  41 82 02 98 */	beq lbl_80087FFC
/* 80087D68 00084948  40 80 02 D4 */	bge lbl_8008803C
/* 80087D6C 0008494C  2C 1E 00 20 */	cmpwi r30, 0x20
/* 80087D70 00084950  40 80 02 CC */	bge lbl_8008803C
/* 80087D74 00084954  48 00 02 88 */	b lbl_80087FFC
lbl_80087D78:
/* 80087D78 00084958  2C 1F 01 97 */	cmpwi r31, 0x197
/* 80087D7C 0008495C  41 82 01 CC */	beq lbl_80087F48
/* 80087D80 00084960  40 80 00 E8 */	bge lbl_80087E68
/* 80087D84 00084964  2C 1F 01 67 */	cmpwi r31, 0x167
/* 80087D88 00084968  41 82 01 E8 */	beq lbl_80087F70
/* 80087D8C 0008496C  40 80 00 70 */	bge lbl_80087DFC
/* 80087D90 00084970  2C 1F 01 58 */	cmpwi r31, 0x158
/* 80087D94 00084974  41 82 01 DC */	beq lbl_80087F70
/* 80087D98 00084978  40 80 00 34 */	bge lbl_80087DCC
/* 80087D9C 0008497C  2C 1F 01 52 */	cmpwi r31, 0x152
/* 80087DA0 00084980  41 82 01 D0 */	beq lbl_80087F70
/* 80087DA4 00084984  40 80 00 1C */	bge lbl_80087DC0
/* 80087DA8 00084988  2C 1F 01 4F */	cmpwi r31, 0x14f
/* 80087DAC 0008498C  41 82 01 C4 */	beq lbl_80087F70
/* 80087DB0 00084990  40 80 02 8C */	bge lbl_8008803C
/* 80087DB4 00084994  2C 1F 01 4C */	cmpwi r31, 0x14c
/* 80087DB8 00084998  41 82 01 B8 */	beq lbl_80087F70
/* 80087DBC 0008499C  48 00 02 80 */	b lbl_8008803C
lbl_80087DC0:
/* 80087DC0 000849A0  2C 1F 01 55 */	cmpwi r31, 0x155
/* 80087DC4 000849A4  41 82 01 AC */	beq lbl_80087F70
/* 80087DC8 000849A8  48 00 02 74 */	b lbl_8008803C
lbl_80087DCC:
/* 80087DCC 000849AC  2C 1F 01 61 */	cmpwi r31, 0x161
/* 80087DD0 000849B0  41 82 01 A0 */	beq lbl_80087F70
/* 80087DD4 000849B4  40 80 00 1C */	bge lbl_80087DF0
/* 80087DD8 000849B8  2C 1F 01 5E */	cmpwi r31, 0x15e
/* 80087DDC 000849BC  41 82 01 94 */	beq lbl_80087F70
/* 80087DE0 000849C0  40 80 02 5C */	bge lbl_8008803C
/* 80087DE4 000849C4  2C 1F 01 5B */	cmpwi r31, 0x15b
/* 80087DE8 000849C8  41 82 01 88 */	beq lbl_80087F70
/* 80087DEC 000849CC  48 00 02 50 */	b lbl_8008803C
lbl_80087DF0:
/* 80087DF0 000849D0  2C 1F 01 64 */	cmpwi r31, 0x164
/* 80087DF4 000849D4  41 82 01 7C */	beq lbl_80087F70
/* 80087DF8 000849D8  48 00 02 44 */	b lbl_8008803C
lbl_80087DFC:
/* 80087DFC 000849DC  2C 1F 01 79 */	cmpwi r31, 0x179
/* 80087E00 000849E0  41 82 01 48 */	beq lbl_80087F48
/* 80087E04 000849E4  40 80 00 34 */	bge lbl_80087E38
/* 80087E08 000849E8  2C 1F 01 70 */	cmpwi r31, 0x170
/* 80087E0C 000849EC  41 82 01 64 */	beq lbl_80087F70
/* 80087E10 000849F0  40 80 00 1C */	bge lbl_80087E2C
/* 80087E14 000849F4  2C 1F 01 6D */	cmpwi r31, 0x16d
/* 80087E18 000849F8  41 82 01 58 */	beq lbl_80087F70
/* 80087E1C 000849FC  40 80 02 20 */	bge lbl_8008803C
/* 80087E20 00084A00  2C 1F 01 6A */	cmpwi r31, 0x16a
/* 80087E24 00084A04  41 82 01 4C */	beq lbl_80087F70
/* 80087E28 00084A08  48 00 02 14 */	b lbl_8008803C
lbl_80087E2C:
/* 80087E2C 00084A0C  2C 1F 01 73 */	cmpwi r31, 0x173
/* 80087E30 00084A10  41 82 01 18 */	beq lbl_80087F48
/* 80087E34 00084A14  48 00 02 08 */	b lbl_8008803C
lbl_80087E38:
/* 80087E38 00084A18  2C 1F 01 8B */	cmpwi r31, 0x18b
/* 80087E3C 00084A1C  41 82 01 0C */	beq lbl_80087F48
/* 80087E40 00084A20  40 80 00 1C */	bge lbl_80087E5C
/* 80087E44 00084A24  2C 1F 01 85 */	cmpwi r31, 0x185
/* 80087E48 00084A28  41 82 01 00 */	beq lbl_80087F48
/* 80087E4C 00084A2C  40 80 01 F0 */	bge lbl_8008803C
/* 80087E50 00084A30  2C 1F 01 7F */	cmpwi r31, 0x17f
/* 80087E54 00084A34  41 82 00 F4 */	beq lbl_80087F48
/* 80087E58 00084A38  48 00 01 E4 */	b lbl_8008803C
lbl_80087E5C:
/* 80087E5C 00084A3C  2C 1F 01 91 */	cmpwi r31, 0x191
/* 80087E60 00084A40  41 82 00 E8 */	beq lbl_80087F48
/* 80087E64 00084A44  48 00 01 D8 */	b lbl_8008803C
lbl_80087E68:
/* 80087E68 00084A48  2C 1F 01 D3 */	cmpwi r31, 0x1d3
/* 80087E6C 00084A4C  41 82 00 DC */	beq lbl_80087F48
/* 80087E70 00084A50  40 80 00 70 */	bge lbl_80087EE0
/* 80087E74 00084A54  2C 1F 01 B5 */	cmpwi r31, 0x1b5
/* 80087E78 00084A58  41 82 00 D0 */	beq lbl_80087F48
/* 80087E7C 00084A5C  40 80 00 34 */	bge lbl_80087EB0
/* 80087E80 00084A60  2C 1F 01 A9 */	cmpwi r31, 0x1a9
/* 80087E84 00084A64  41 82 00 C4 */	beq lbl_80087F48
/* 80087E88 00084A68  40 80 00 1C */	bge lbl_80087EA4
/* 80087E8C 00084A6C  2C 1F 01 A3 */	cmpwi r31, 0x1a3
/* 80087E90 00084A70  41 82 00 B8 */	beq lbl_80087F48
/* 80087E94 00084A74  40 80 01 A8 */	bge lbl_8008803C
/* 80087E98 00084A78  2C 1F 01 9D */	cmpwi r31, 0x19d
/* 80087E9C 00084A7C  41 82 00 AC */	beq lbl_80087F48
/* 80087EA0 00084A80  48 00 01 9C */	b lbl_8008803C
lbl_80087EA4:
/* 80087EA4 00084A84  2C 1F 01 AF */	cmpwi r31, 0x1af
/* 80087EA8 00084A88  41 82 00 A0 */	beq lbl_80087F48
/* 80087EAC 00084A8C  48 00 01 90 */	b lbl_8008803C
lbl_80087EB0:
/* 80087EB0 00084A90  2C 1F 01 C7 */	cmpwi r31, 0x1c7
/* 80087EB4 00084A94  41 82 00 94 */	beq lbl_80087F48
/* 80087EB8 00084A98  40 80 00 1C */	bge lbl_80087ED4
/* 80087EBC 00084A9C  2C 1F 01 C1 */	cmpwi r31, 0x1c1
/* 80087EC0 00084AA0  41 82 00 88 */	beq lbl_80087F48
/* 80087EC4 00084AA4  40 80 01 78 */	bge lbl_8008803C
/* 80087EC8 00084AA8  2C 1F 01 BB */	cmpwi r31, 0x1bb
/* 80087ECC 00084AAC  41 82 00 7C */	beq lbl_80087F48
/* 80087ED0 00084AB0  48 00 01 6C */	b lbl_8008803C
lbl_80087ED4:
/* 80087ED4 00084AB4  2C 1F 01 CD */	cmpwi r31, 0x1cd
/* 80087ED8 00084AB8  41 82 00 70 */	beq lbl_80087F48
/* 80087EDC 00084ABC  48 00 01 60 */	b lbl_8008803C
lbl_80087EE0:
/* 80087EE0 00084AC0  2C 1F 01 F7 */	cmpwi r31, 0x1f7
/* 80087EE4 00084AC4  41 82 00 64 */	beq lbl_80087F48
/* 80087EE8 00084AC8  40 80 00 34 */	bge lbl_80087F1C
/* 80087EEC 00084ACC  2C 1F 01 E5 */	cmpwi r31, 0x1e5
/* 80087EF0 00084AD0  41 82 00 58 */	beq lbl_80087F48
/* 80087EF4 00084AD4  40 80 00 1C */	bge lbl_80087F10
/* 80087EF8 00084AD8  2C 1F 01 DF */	cmpwi r31, 0x1df
/* 80087EFC 00084ADC  41 82 00 4C */	beq lbl_80087F48
/* 80087F00 00084AE0  40 80 01 3C */	bge lbl_8008803C
/* 80087F04 00084AE4  2C 1F 01 D9 */	cmpwi r31, 0x1d9
/* 80087F08 00084AE8  41 82 00 40 */	beq lbl_80087F48
/* 80087F0C 00084AEC  48 00 01 30 */	b lbl_8008803C
lbl_80087F10:
/* 80087F10 00084AF0  2C 1F 01 EB */	cmpwi r31, 0x1eb
/* 80087F14 00084AF4  41 82 00 34 */	beq lbl_80087F48
/* 80087F18 00084AF8  48 00 01 24 */	b lbl_8008803C
lbl_80087F1C:
/* 80087F1C 00084AFC  2C 1F 02 03 */	cmpwi r31, 0x203
/* 80087F20 00084B00  41 82 00 28 */	beq lbl_80087F48
/* 80087F24 00084B04  40 80 00 10 */	bge lbl_80087F34
/* 80087F28 00084B08  2C 1F 01 FD */	cmpwi r31, 0x1fd
/* 80087F2C 00084B0C  41 82 00 1C */	beq lbl_80087F48
/* 80087F30 00084B10  48 00 01 0C */	b lbl_8008803C
lbl_80087F34:
/* 80087F34 00084B14  3C 60 00 04 */	lis r3, 0x00046D03@ha
/* 80087F38 00084B18  38 03 6D 03 */	addi r0, r3, 0x00046D03@l
/* 80087F3C 00084B1C  7C 1F 00 00 */	cmpw r31, r0
/* 80087F40 00084B20  41 82 00 08 */	beq lbl_80087F48
/* 80087F44 00084B24  48 00 00 F8 */	b lbl_8008803C
lbl_80087F48:
/* 80087F48 00084B28  38 7D 00 00 */	addi r3, r29, 0
/* 80087F4C 00084B2C  38 9F 00 00 */	addi r4, r31, 0
/* 80087F50 00084B30  4B FF FD 21 */	bl func_80087C70
/* 80087F54 00084B34  88 1D 22 23 */	lbz r0, 0x2223(r29)
/* 80087F58 00084B38  38 83 00 00 */	addi r4, r3, 0
/* 80087F5C 00084B3C  54 00 07 FF */	clrlwi. r0, r0, 0x1f
/* 80087F60 00084B40  41 82 00 08 */	beq lbl_80087F68
/* 80087F64 00084B44  38 84 00 03 */	addi r4, r4, 3
lbl_80087F68:
/* 80087F68 00084B48  7C 9F 23 78 */	mr r31, r4
/* 80087F6C 00084B4C  48 00 00 D0 */	b lbl_8008803C
lbl_80087F70:
/* 80087F70 00084B50  38 7D 00 00 */	addi r3, r29, 0
/* 80087F74 00084B54  38 9F 00 00 */	addi r4, r31, 0
/* 80087F78 00084B58  4B FF FC F9 */	bl func_80087C70
/* 80087F7C 00084B5C  7C 7F 1B 78 */	mr r31, r3
/* 80087F80 00084B60  48 00 00 BC */	b lbl_8008803C
lbl_80087F84:
/* 80087F84 00084B64  80 1D 00 04 */	lwz r0, 4(r29)
/* 80087F88 00084B68  2C 00 00 0C */	cmpwi r0, 0xc
/* 80087F8C 00084B6C  40 80 00 70 */	bge lbl_80087FFC
/* 80087F90 00084B70  2C 00 00 0A */	cmpwi r0, 0xa
/* 80087F94 00084B74  40 80 00 08 */	bge lbl_80087F9C
/* 80087F98 00084B78  48 00 00 64 */	b lbl_80087FFC
lbl_80087F9C:
/* 80087F9C 00084B7C  3C 60 00 02 */	lis r3, 0x0001FBFD@ha
/* 80087FA0 00084B80  38 03 FB FD */	addi r0, r3, 0x0001FBFD@l
/* 80087FA4 00084B84  7C 00 F8 00 */	cmpw r0, r31
/* 80087FA8 00084B88  41 81 00 24 */	bgt lbl_80087FCC
/* 80087FAC 00084B8C  38 03 FC 62 */	addi r0, r3, -926
/* 80087FB0 00084B90  7C 1F 00 00 */	cmpw r31, r0
/* 80087FB4 00084B94  41 81 00 18 */	bgt lbl_80087FCC
/* 80087FB8 00084B98  7F A3 EB 78 */	mr r3, r29
/* 80087FBC 00084B9C  4B FF 81 89 */	bl func_80080144
/* 80087FC0 00084BA0  2C 03 00 01 */	cmpwi r3, 1
/* 80087FC4 00084BA4  40 82 00 08 */	bne lbl_80087FCC
/* 80087FC8 00084BA8  3B FF 00 66 */	addi r31, r31, 0x66
lbl_80087FCC:
/* 80087FCC 00084BAC  3C 60 00 02 */	lis r3, 0x0001FC63@ha
/* 80087FD0 00084BB0  38 03 FC 63 */	addi r0, r3, 0x0001FC63@l
/* 80087FD4 00084BB4  7C 00 F8 00 */	cmpw r0, r31
/* 80087FD8 00084BB8  41 81 00 24 */	bgt lbl_80087FFC
/* 80087FDC 00084BBC  38 03 FC C8 */	addi r0, r3, -824
/* 80087FE0 00084BC0  7C 1F 00 00 */	cmpw r31, r0
/* 80087FE4 00084BC4  41 81 00 18 */	bgt lbl_80087FFC
/* 80087FE8 00084BC8  7F A3 EB 78 */	mr r3, r29
/* 80087FEC 00084BCC  4B FF 81 59 */	bl func_80080144
/* 80087FF0 00084BD0  2C 03 00 01 */	cmpwi r3, 1
/* 80087FF4 00084BD4  41 82 00 08 */	beq lbl_80087FFC
/* 80087FF8 00084BD8  3B FF FF 9A */	addi r31, r31, -102
lbl_80087FFC:
/* 80087FFC 00084BDC  38 7E 00 00 */	addi r3, r30, 0
/* 80088000 00084BE0  38 81 00 18 */	addi r4, r1, 0x18
/* 80088004 00084BE4  38 A1 00 14 */	addi r5, r1, 0x14
/* 80088008 00084BE8  4B F9 B0 C1 */	bl func_800230C8
/* 8008800C 00084BEC  2C 03 00 00 */	cmpwi r3, 0
/* 80088010 00084BF0  40 82 00 2C */	bne lbl_8008803C
/* 80088014 00084BF4  7F C3 F3 78 */	mr r3, r30
/* 80088018 00084BF8  4B F9 B2 09 */	bl func_80023220
/* 8008801C 00084BFC  80 01 00 18 */	lwz r0, 0x18(r1)
/* 80088020 00084C00  7C 00 1A 14 */	add r0, r0, r3
/* 80088024 00084C04  7C 1F 00 00 */	cmpw r31, r0
/* 80088028 00084C08  41 80 00 14 */	blt lbl_8008803C
/* 8008802C 00084C0C  38 7D 00 00 */	addi r3, r29, 0
/* 80088030 00084C10  38 9F 00 00 */	addi r4, r31, 0
/* 80088034 00084C14  4B FF FC 3D */	bl func_80087C70
/* 80088038 00084C18  7C 7F 1B 78 */	mr r31, r3
lbl_8008803C:
/* 8008803C 00084C1C  7F E3 FB 78 */	mr r3, r31
/* 80088040 00084C20  80 01 00 34 */	lwz r0, 0x34(r1)
/* 80088044 00084C24  83 E1 00 2C */	lwz r31, 0x2c(r1)
/* 80088048 00084C28  83 C1 00 28 */	lwz r30, 0x28(r1)
/* 8008804C 00084C2C  83 A1 00 24 */	lwz r29, 0x24(r1)
/* 80088050 00084C30  38 21 00 30 */	addi r1, r1, 0x30
/* 80088054 00084C34  7C 08 03 A6 */	mtlr r0
/* 80088058 00084C38  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

#endif

void func_8008805C(Fighter* arg0, s32 arg1)
{
    func_80087D0C(arg0, arg1);
    func_80024DC4();
}

void func_80088080(Fighter* fp)
{
    fp->x2164 += 1;
    func_80024FDC();
}

void func_800880AC(Fighter* fp)
{
    fp->x2168 += 1;
    func_80024FF4();
}

void func_800880D8(Fighter* fp)
{
    func_8002500C(fp->x2164);
    fp->x2164 = 0;
}

void func_80088110(Fighter* fp)
{
    func_80025038(fp->x2168);
    fp->x2168 = 0;
}

extern unk_t func_80024B94();

#pragma push
asm void func_80088148(Fighter*, u32, u32, u32)
{ // clang-format off
    nofralloc
/* 80088148 00084D28  7C 08 02 A6 */	mflr r0
/* 8008814C 00084D2C  90 01 00 04 */	stw r0, 4(r1)
/* 80088150 00084D30  94 21 FF D8 */	stwu r1, -0x28(r1)
/* 80088154 00084D34  93 E1 00 24 */	stw r31, 0x24(r1)
/* 80088158 00084D38  3B E6 00 00 */	addi r31, r6, 0
/* 8008815C 00084D3C  93 C1 00 20 */	stw r30, 0x20(r1)
/* 80088160 00084D40  3B C5 00 00 */	addi r30, r5, 0
/* 80088164 00084D44  93 A1 00 1C */	stw r29, 0x1c(r1)
/* 80088168 00084D48  3B A4 00 00 */	addi r29, r4, 0
/* 8008816C 00084D4C  93 81 00 18 */	stw r28, 0x18(r1)
/* 80088170 00084D50  3B 83 00 00 */	addi r28, r3, 0
/* 80088174 00084D54  4B FF FB 99 */	bl func_80087D0C
/* 80088178 00084D58  3B A3 00 00 */	addi r29, r3, 0
/* 8008817C 00084D5C  57 C4 06 3E */	clrlwi r4, r30, 0x18
/* 80088180 00084D60  57 E5 06 3E */	clrlwi r5, r31, 0x18
/* 80088184 00084D64  4B F9 B6 25 */	bl func_800237A8
/* 80088188 00084D68  2C 1D 01 4C */	cmpwi r29, 0x14c
/* 8008818C 00084D6C  90 7C 21 60 */	stw r3, 0x2160(r28)
/* 80088190 00084D70  41 80 00 1C */	blt lbl_800881AC
/* 80088194 00084D74  2C 1D 01 72 */	cmpwi r29, 0x172
/* 80088198 00084D78  41 81 00 14 */	bgt lbl_800881AC
/* 8008819C 00084D7C  38 60 00 C8 */	li r3, 0xc8
/* 800881A0 00084D80  48 2F 83 E1 */	bl HSD_Randi
/* 800881A4 00084D84  38 83 FF 9C */	addi r4, r3, -100
/* 800881A8 00084D88  48 00 00 08 */	b lbl_800881B0
lbl_800881AC:
/* 800881AC 00084D8C  38 80 00 00 */	li r4, 0
lbl_800881B0:
/* 800881B0 00084D90  80 7C 21 60 */	lwz r3, 0x2160(r28)
/* 800881B4 00084D94  4B F9 C9 E1 */	bl func_80024B94
/* 800881B8 00084D98  80 01 00 2C */	lwz r0, 0x2c(r1)
/* 800881BC 00084D9C  83 E1 00 24 */	lwz r31, 0x24(r1)
/* 800881C0 00084DA0  83 C1 00 20 */	lwz r30, 0x20(r1)
/* 800881C4 00084DA4  83 A1 00 1C */	lwz r29, 0x1c(r1)
/* 800881C8 00084DA8  83 81 00 18 */	lwz r28, 0x18(r1)
/* 800881CC 00084DAC  38 21 00 28 */	addi r1, r1, 0x28
/* 800881D0 00084DB0  7C 08 03 A6 */	mtlr r0
/* 800881D4 00084DB4  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

extern unk_t func_80023870();
extern unk_t func_80088770();

#pragma push
asm void func_800881D8(Fighter*, u32, u32, u32)
{ // clang-format off
    nofralloc
/* 800881D8 00084DB8  7C 08 02 A6 */	mflr r0
/* 800881DC 00084DBC  90 01 00 04 */	stw r0, 4(r1)
/* 800881E0 00084DC0  94 21 FF D8 */	stwu r1, -0x28(r1)
/* 800881E4 00084DC4  93 E1 00 24 */	stw r31, 0x24(r1)
/* 800881E8 00084DC8  7C 7F 1B 78 */	mr r31, r3
/* 800881EC 00084DCC  93 C1 00 20 */	stw r30, 0x20(r1)
/* 800881F0 00084DD0  3B C4 00 00 */	addi r30, r4, 0
/* 800881F4 00084DD4  93 A1 00 1C */	stw r29, 0x1c(r1)
/* 800881F8 00084DD8  3B A6 00 00 */	addi r29, r6, 0
/* 800881FC 00084DDC  93 81 00 18 */	stw r28, 0x18(r1)
/* 80088200 00084DE0  3B 85 00 00 */	addi r28, r5, 0
/* 80088204 00084DE4  88 03 22 25 */	lbz r0, 0x2225(r3)
/* 80088208 00084DE8  54 00 FF FF */	rlwinm. r0, r0, 0x1f, 0x1f, 0x1f
/* 8008820C 00084DEC  40 82 00 74 */	bne lbl_80088280
/* 80088210 00084DF0  3C 1E FF F8 */	addis r0, r30, 0xfff8
/* 80088214 00084DF4  28 00 3D 60 */	cmplwi r0, 0x3d60
/* 80088218 00084DF8  41 82 00 F0 */	beq lbl_80088308
/* 8008821C 00084DFC  28 00 3D 61 */	cmplwi r0, 0x3d61
/* 80088220 00084E00  41 82 00 54 */	beq lbl_80088274
/* 80088224 00084E04  38 7F 00 00 */	addi r3, r31, 0
/* 80088228 00084E08  38 9E 00 00 */	addi r4, r30, 0
/* 8008822C 00084E0C  4B FF FA E1 */	bl func_80087D0C
/* 80088230 00084E10  3B C3 00 00 */	addi r30, r3, 0
/* 80088234 00084E14  38 7F 00 00 */	addi r3, r31, 0
/* 80088238 00084E18  48 00 05 39 */	bl func_80088770
/* 8008823C 00084E1C  7F E3 FB 78 */	mr r3, r31
/* 80088240 00084E20  48 00 05 8D */	bl func_800887CC
/* 80088244 00084E24  88 BF 22 1F */	lbz r5, 0x221f(r31)
/* 80088248 00084E28  7F C3 F3 78 */	mr r3, r30
/* 8008824C 00084E2C  88 1F 00 0C */	lbz r0, 0xc(r31)
/* 80088250 00084E30  57 84 06 3E */	clrlwi r4, r28, 0x18
/* 80088254 00084E34  54 A5 EF FE */	rlwinm r5, r5, 0x1d, 0x1f, 0x1f
/* 80088258 00084E38  54 00 08 3C */	slwi r0, r0, 1
/* 8008825C 00084E3C  7C C0 2A 14 */	add r6, r0, r5
/* 80088260 00084E40  57 A5 06 3E */	clrlwi r5, r29, 0x18
/* 80088264 00084E44  38 C6 00 1E */	addi r6, r6, 0x1e
/* 80088268 00084E48  4B F9 B6 09 */	bl func_80023870
/* 8008826C 00084E4C  90 7F 21 44 */	stw r3, 0x2144(r31)
/* 80088270 00084E50  48 00 00 98 */	b lbl_80088308
lbl_80088274:
/* 80088274 00084E54  7F E3 FB 78 */	mr r3, r31
/* 80088278 00084E58  48 00 04 F9 */	bl func_80088770
/* 8008827C 00084E5C  48 00 00 8C */	b lbl_80088308
lbl_80088280:
/* 80088280 00084E60  80 1F 00 04 */	lwz r0, 4(r31)
/* 80088284 00084E64  2C 00 00 18 */	cmpwi r0, 0x18
/* 80088288 00084E68  41 82 00 14 */	beq lbl_8008829C
/* 8008828C 00084E6C  40 80 00 7C */	bge lbl_80088308
/* 80088290 00084E70  2C 00 00 0D */	cmpwi r0, 0xd
/* 80088294 00084E74  41 82 00 08 */	beq lbl_8008829C
/* 80088298 00084E78  48 00 00 70 */	b lbl_80088308
lbl_8008829C:
/* 8008829C 00084E7C  3C 1E FF F8 */	addis r0, r30, 0xfff8
/* 800882A0 00084E80  28 00 3D 60 */	cmplwi r0, 0x3d60
/* 800882A4 00084E84  41 82 00 64 */	beq lbl_80088308
/* 800882A8 00084E88  28 00 3D 61 */	cmplwi r0, 0x3d61
/* 800882AC 00084E8C  41 82 00 54 */	beq lbl_80088300
/* 800882B0 00084E90  38 7F 00 00 */	addi r3, r31, 0
/* 800882B4 00084E94  38 9E 00 00 */	addi r4, r30, 0
/* 800882B8 00084E98  4B FF FA 55 */	bl func_80087D0C
/* 800882BC 00084E9C  3B C3 00 00 */	addi r30, r3, 0
/* 800882C0 00084EA0  38 7F 00 00 */	addi r3, r31, 0
/* 800882C4 00084EA4  48 00 04 AD */	bl func_80088770
/* 800882C8 00084EA8  7F E3 FB 78 */	mr r3, r31
/* 800882CC 00084EAC  48 00 05 01 */	bl func_800887CC
/* 800882D0 00084EB0  88 BF 22 1F */	lbz r5, 0x221f(r31)
/* 800882D4 00084EB4  7F C3 F3 78 */	mr r3, r30
/* 800882D8 00084EB8  88 1F 00 0C */	lbz r0, 0xc(r31)
/* 800882DC 00084EBC  57 84 06 3E */	clrlwi r4, r28, 0x18
/* 800882E0 00084EC0  54 A5 EF FE */	rlwinm r5, r5, 0x1d, 0x1f, 0x1f
/* 800882E4 00084EC4  54 00 08 3C */	slwi r0, r0, 1
/* 800882E8 00084EC8  7C C0 2A 14 */	add r6, r0, r5
/* 800882EC 00084ECC  57 A5 06 3E */	clrlwi r5, r29, 0x18
/* 800882F0 00084ED0  38 C6 00 1E */	addi r6, r6, 0x1e
/* 800882F4 00084ED4  4B F9 B5 7D */	bl func_80023870
/* 800882F8 00084ED8  90 7F 21 44 */	stw r3, 0x2144(r31)
/* 800882FC 00084EDC  48 00 00 0C */	b lbl_80088308
lbl_80088300:
/* 80088300 00084EE0  7F E3 FB 78 */	mr r3, r31
/* 80088304 00084EE4  48 00 04 6D */	bl func_80088770
lbl_80088308:
/* 80088308 00084EE8  80 01 00 2C */	lwz r0, 0x2c(r1)
/* 8008830C 00084EEC  83 E1 00 24 */	lwz r31, 0x24(r1)
/* 80088310 00084EF0  83 C1 00 20 */	lwz r30, 0x20(r1)
/* 80088314 00084EF4  83 A1 00 1C */	lwz r29, 0x1c(r1)
/* 80088318 00084EF8  83 81 00 18 */	lwz r28, 0x18(r1)
/* 8008831C 00084EFC  38 21 00 28 */	addi r1, r1, 0x28
/* 80088320 00084F00  7C 08 03 A6 */	mtlr r0
/* 80088324 00084F04  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

#pragma push
asm unk_t func_80088328()
{ // clang-format off
    nofralloc
/* 80088328 00084F08  7C 08 02 A6 */	mflr r0
/* 8008832C 00084F0C  90 01 00 04 */	stw r0, 4(r1)
/* 80088330 00084F10  94 21 FF D8 */	stwu r1, -0x28(r1)
/* 80088334 00084F14  93 E1 00 24 */	stw r31, 0x24(r1)
/* 80088338 00084F18  7C 7F 1B 78 */	mr r31, r3
/* 8008833C 00084F1C  93 C1 00 20 */	stw r30, 0x20(r1)
/* 80088340 00084F20  3B C4 00 00 */	addi r30, r4, 0
/* 80088344 00084F24  93 A1 00 1C */	stw r29, 0x1c(r1)
/* 80088348 00084F28  3B A6 00 00 */	addi r29, r6, 0
/* 8008834C 00084F2C  93 81 00 18 */	stw r28, 0x18(r1)
/* 80088350 00084F30  3B 85 00 00 */	addi r28, r5, 0
/* 80088354 00084F34  88 03 22 25 */	lbz r0, 0x2225(r3)
/* 80088358 00084F38  54 00 FF FF */	rlwinm. r0, r0, 0x1f, 0x1f, 0x1f
/* 8008835C 00084F3C  40 82 00 74 */	bne lbl_800883D0
/* 80088360 00084F40  3C 1E FF F8 */	addis r0, r30, 0xfff8
/* 80088364 00084F44  28 00 3D 60 */	cmplwi r0, 0x3d60
/* 80088368 00084F48  41 82 00 F0 */	beq lbl_80088458
/* 8008836C 00084F4C  28 00 3D 61 */	cmplwi r0, 0x3d61
/* 80088370 00084F50  41 82 00 54 */	beq lbl_800883C4
/* 80088374 00084F54  38 7F 00 00 */	addi r3, r31, 0
/* 80088378 00084F58  38 9E 00 00 */	addi r4, r30, 0
/* 8008837C 00084F5C  4B FF F9 91 */	bl func_80087D0C
/* 80088380 00084F60  3B C3 00 00 */	addi r30, r3, 0
/* 80088384 00084F64  38 7F 00 00 */	addi r3, r31, 0
/* 80088388 00084F68  48 00 03 E9 */	bl func_80088770
/* 8008838C 00084F6C  7F E3 FB 78 */	mr r3, r31
/* 80088390 00084F70  48 00 04 3D */	bl func_800887CC
/* 80088394 00084F74  88 BF 22 1F */	lbz r5, 0x221f(r31)
/* 80088398 00084F78  7F C3 F3 78 */	mr r3, r30
/* 8008839C 00084F7C  88 1F 00 0C */	lbz r0, 0xc(r31)
/* 800883A0 00084F80  57 84 06 3E */	clrlwi r4, r28, 0x18
/* 800883A4 00084F84  54 A5 EF FE */	rlwinm r5, r5, 0x1d, 0x1f, 0x1f
/* 800883A8 00084F88  54 00 08 3C */	slwi r0, r0, 1
/* 800883AC 00084F8C  7C C0 2A 14 */	add r6, r0, r5
/* 800883B0 00084F90  57 A5 06 3E */	clrlwi r5, r29, 0x18
/* 800883B4 00084F94  38 C6 00 2A */	addi r6, r6, 0x2a
/* 800883B8 00084F98  4B F9 B4 B9 */	bl func_80023870
/* 800883BC 00084F9C  90 7F 21 48 */	stw r3, 0x2148(r31)
/* 800883C0 00084FA0  48 00 00 98 */	b lbl_80088458
lbl_800883C4:
/* 800883C4 00084FA4  7F E3 FB 78 */	mr r3, r31
/* 800883C8 00084FA8  48 00 04 05 */	bl func_800887CC
/* 800883CC 00084FAC  48 00 00 8C */	b lbl_80088458
lbl_800883D0:
/* 800883D0 00084FB0  80 1F 00 04 */	lwz r0, 4(r31)
/* 800883D4 00084FB4  2C 00 00 18 */	cmpwi r0, 0x18
/* 800883D8 00084FB8  41 82 00 14 */	beq lbl_800883EC
/* 800883DC 00084FBC  40 80 00 7C */	bge lbl_80088458
/* 800883E0 00084FC0  2C 00 00 0D */	cmpwi r0, 0xd
/* 800883E4 00084FC4  41 82 00 08 */	beq lbl_800883EC
/* 800883E8 00084FC8  48 00 00 70 */	b lbl_80088458
lbl_800883EC:
/* 800883EC 00084FCC  3C 1E FF F8 */	addis r0, r30, 0xfff8
/* 800883F0 00084FD0  28 00 3D 60 */	cmplwi r0, 0x3d60
/* 800883F4 00084FD4  41 82 00 64 */	beq lbl_80088458
/* 800883F8 00084FD8  28 00 3D 61 */	cmplwi r0, 0x3d61
/* 800883FC 00084FDC  41 82 00 54 */	beq lbl_80088450
/* 80088400 00084FE0  38 7F 00 00 */	addi r3, r31, 0
/* 80088404 00084FE4  38 9E 00 00 */	addi r4, r30, 0
/* 80088408 00084FE8  4B FF F9 05 */	bl func_80087D0C
/* 8008840C 00084FEC  3B C3 00 00 */	addi r30, r3, 0
/* 80088410 00084FF0  38 7F 00 00 */	addi r3, r31, 0
/* 80088414 00084FF4  48 00 03 5D */	bl func_80088770
/* 80088418 00084FF8  7F E3 FB 78 */	mr r3, r31
/* 8008841C 00084FFC  48 00 03 B1 */	bl func_800887CC
/* 80088420 00085000  88 BF 22 1F */	lbz r5, 0x221f(r31)
/* 80088424 00085004  7F C3 F3 78 */	mr r3, r30
/* 80088428 00085008  88 1F 00 0C */	lbz r0, 0xc(r31)
/* 8008842C 0008500C  57 84 06 3E */	clrlwi r4, r28, 0x18
/* 80088430 00085010  54 A5 EF FE */	rlwinm r5, r5, 0x1d, 0x1f, 0x1f
/* 80088434 00085014  54 00 08 3C */	slwi r0, r0, 1
/* 80088438 00085018  7C C0 2A 14 */	add r6, r0, r5
/* 8008843C 0008501C  57 A5 06 3E */	clrlwi r5, r29, 0x18
/* 80088440 00085020  38 C6 00 2A */	addi r6, r6, 0x2a
/* 80088444 00085024  4B F9 B4 2D */	bl func_80023870
/* 80088448 00085028  90 7F 21 48 */	stw r3, 0x2148(r31)
/* 8008844C 0008502C  48 00 00 0C */	b lbl_80088458
lbl_80088450:
/* 80088450 00085030  7F E3 FB 78 */	mr r3, r31
/* 80088454 00085034  48 00 03 79 */	bl func_800887CC
lbl_80088458:
/* 80088458 00085038  80 01 00 2C */	lwz r0, 0x2c(r1)
/* 8008845C 0008503C  83 E1 00 24 */	lwz r31, 0x24(r1)
/* 80088460 00085040  83 C1 00 20 */	lwz r30, 0x20(r1)
/* 80088464 00085044  83 A1 00 1C */	lwz r29, 0x1c(r1)
/* 80088468 00085048  83 81 00 18 */	lwz r28, 0x18(r1)
/* 8008846C 0008504C  38 21 00 28 */	addi r1, r1, 0x28
/* 80088470 00085050  7C 08 03 A6 */	mtlr r0
/* 80088474 00085054  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

extern unk_t func_80088828();

#pragma push
asm unk_t func_80088478()
{ // clang-format off
    nofralloc
/* 80088478 00085058  7C 08 02 A6 */	mflr r0
/* 8008847C 0008505C  90 01 00 04 */	stw r0, 4(r1)
/* 80088480 00085060  3C 04 FF F8 */	addis r0, r4, 0xfff8
/* 80088484 00085064  28 00 3D 60 */	cmplwi r0, 0x3d60
/* 80088488 00085068  94 21 FF D8 */	stwu r1, -0x28(r1)
/* 8008848C 0008506C  93 E1 00 24 */	stw r31, 0x24(r1)
/* 80088490 00085070  3B E6 00 00 */	addi r31, r6, 0
/* 80088494 00085074  93 C1 00 20 */	stw r30, 0x20(r1)
/* 80088498 00085078  3B C5 00 00 */	addi r30, r5, 0
/* 8008849C 0008507C  93 A1 00 1C */	stw r29, 0x1c(r1)
/* 800884A0 00085080  3B A3 00 00 */	addi r29, r3, 0
/* 800884A4 00085084  41 82 00 50 */	beq lbl_800884F4
/* 800884A8 00085088  28 00 3D 61 */	cmplwi r0, 0x3d61
/* 800884AC 0008508C  41 82 00 40 */	beq lbl_800884EC
/* 800884B0 00085090  7F A3 EB 78 */	mr r3, r29
/* 800884B4 00085094  4B FF F8 59 */	bl func_80087D0C
/* 800884B8 00085098  88 1D 00 0C */	lbz r0, 0xc(r29)
/* 800884BC 0008509C  38 83 00 00 */	addi r4, r3, 0
/* 800884C0 000850A0  88 BD 22 1F */	lbz r5, 0x221f(r29)
/* 800884C4 000850A4  54 00 08 3C */	slwi r0, r0, 1
/* 800884C8 000850A8  54 A3 EF FE */	rlwinm r3, r5, 0x1d, 0x1f, 0x1f
/* 800884CC 000850AC  7C C0 1A 14 */	add r6, r0, r3
/* 800884D0 000850B0  38 64 00 00 */	addi r3, r4, 0
/* 800884D4 000850B4  57 C4 06 3E */	clrlwi r4, r30, 0x18
/* 800884D8 000850B8  57 E5 06 3E */	clrlwi r5, r31, 0x18
/* 800884DC 000850BC  38 C6 00 36 */	addi r6, r6, 0x36
/* 800884E0 000850C0  4B F9 B3 91 */	bl func_80023870
/* 800884E4 000850C4  90 7D 21 4C */	stw r3, 0x214c(r29)
/* 800884E8 000850C8  48 00 00 0C */	b lbl_800884F4
lbl_800884EC:
/* 800884EC 000850CC  7F A3 EB 78 */	mr r3, r29
/* 800884F0 000850D0  48 00 03 39 */	bl func_80088828
lbl_800884F4:
/* 800884F4 000850D4  80 01 00 2C */	lwz r0, 0x2c(r1)
/* 800884F8 000850D8  83 E1 00 24 */	lwz r31, 0x24(r1)
/* 800884FC 000850DC  83 C1 00 20 */	lwz r30, 0x20(r1)
/* 80088500 000850E0  83 A1 00 1C */	lwz r29, 0x1c(r1)
/* 80088504 000850E4  38 21 00 28 */	addi r1, r1, 0x28
/* 80088508 000850E8  7C 08 03 A6 */	mtlr r0
/* 8008850C 000850EC  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

#pragma push
asm unk_t func_80088510()
{ // clang-format off
    nofralloc
/* 80088510 000850F0  7C 08 02 A6 */	mflr r0
/* 80088514 000850F4  90 01 00 04 */	stw r0, 4(r1)
/* 80088518 000850F8  3C 04 FF F8 */	addis r0, r4, 0xfff8
/* 8008851C 000850FC  28 00 3D 60 */	cmplwi r0, 0x3d60
/* 80088520 00085100  94 21 FF D8 */	stwu r1, -0x28(r1)
/* 80088524 00085104  93 E1 00 24 */	stw r31, 0x24(r1)
/* 80088528 00085108  3B E6 00 00 */	addi r31, r6, 0
/* 8008852C 0008510C  93 C1 00 20 */	stw r30, 0x20(r1)
/* 80088530 00085110  3B C5 00 00 */	addi r30, r5, 0
/* 80088534 00085114  93 A1 00 1C */	stw r29, 0x1c(r1)
/* 80088538 00085118  3B A3 00 00 */	addi r29, r3, 0
/* 8008853C 0008511C  41 82 00 50 */	beq lbl_8008858C
/* 80088540 00085120  28 00 3D 61 */	cmplwi r0, 0x3d61
/* 80088544 00085124  41 82 00 40 */	beq lbl_80088584
/* 80088548 00085128  7F A3 EB 78 */	mr r3, r29
/* 8008854C 0008512C  4B FF F7 C1 */	bl func_80087D0C
/* 80088550 00085130  88 1D 00 0C */	lbz r0, 0xc(r29)
/* 80088554 00085134  38 83 00 00 */	addi r4, r3, 0
/* 80088558 00085138  88 BD 22 1F */	lbz r5, 0x221f(r29)
/* 8008855C 0008513C  54 00 08 3C */	slwi r0, r0, 1
/* 80088560 00085140  54 A3 EF FE */	rlwinm r3, r5, 0x1d, 0x1f, 0x1f
/* 80088564 00085144  7C C0 1A 14 */	add r6, r0, r3
/* 80088568 00085148  38 64 00 00 */	addi r3, r4, 0
/* 8008856C 0008514C  57 C4 06 3E */	clrlwi r4, r30, 0x18
/* 80088570 00085150  57 E5 06 3E */	clrlwi r5, r31, 0x18
/* 80088574 00085154  38 C6 00 42 */	addi r6, r6, 0x42
/* 80088578 00085158  4B F9 B2 F9 */	bl func_80023870
/* 8008857C 0008515C  90 7D 21 50 */	stw r3, 0x2150(r29)
/* 80088580 00085160  48 00 00 0C */	b lbl_8008858C
lbl_80088584:
/* 80088584 00085164  7F A3 EB 78 */	mr r3, r29
/* 80088588 00085168  48 00 02 FD */	bl func_80088884
lbl_8008858C:
/* 8008858C 0008516C  80 01 00 2C */	lwz r0, 0x2c(r1)
/* 80088590 00085170  83 E1 00 24 */	lwz r31, 0x24(r1)
/* 80088594 00085174  83 C1 00 20 */	lwz r30, 0x20(r1)
/* 80088598 00085178  83 A1 00 1C */	lwz r29, 0x1c(r1)
/* 8008859C 0008517C  38 21 00 28 */	addi r1, r1, 0x28
/* 800885A0 00085180  7C 08 03 A6 */	mtlr r0
/* 800885A4 00085184  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

#pragma push
asm unk_t func_800885A8()
{ // clang-format off
    nofralloc
/* 800885A8 00085188  7C 08 02 A6 */	mflr r0
/* 800885AC 0008518C  90 01 00 04 */	stw r0, 4(r1)
/* 800885B0 00085190  3C 04 FF F8 */	addis r0, r4, 0xfff8
/* 800885B4 00085194  28 00 3D 60 */	cmplwi r0, 0x3d60
/* 800885B8 00085198  94 21 FF D8 */	stwu r1, -0x28(r1)
/* 800885BC 0008519C  93 E1 00 24 */	stw r31, 0x24(r1)
/* 800885C0 000851A0  3B E6 00 00 */	addi r31, r6, 0
/* 800885C4 000851A4  93 C1 00 20 */	stw r30, 0x20(r1)
/* 800885C8 000851A8  3B C5 00 00 */	addi r30, r5, 0
/* 800885CC 000851AC  93 A1 00 1C */	stw r29, 0x1c(r1)
/* 800885D0 000851B0  3B A3 00 00 */	addi r29, r3, 0
/* 800885D4 000851B4  41 82 00 50 */	beq lbl_80088624
/* 800885D8 000851B8  28 00 3D 61 */	cmplwi r0, 0x3d61
/* 800885DC 000851BC  41 82 00 40 */	beq lbl_8008861C
/* 800885E0 000851C0  7F A3 EB 78 */	mr r3, r29
/* 800885E4 000851C4  4B FF F7 29 */	bl func_80087D0C
/* 800885E8 000851C8  88 1D 00 0C */	lbz r0, 0xc(r29)
/* 800885EC 000851CC  38 83 00 00 */	addi r4, r3, 0
/* 800885F0 000851D0  88 BD 22 1F */	lbz r5, 0x221f(r29)
/* 800885F4 000851D4  54 00 08 3C */	slwi r0, r0, 1
/* 800885F8 000851D8  54 A3 EF FE */	rlwinm r3, r5, 0x1d, 0x1f, 0x1f
/* 800885FC 000851DC  7C C0 1A 14 */	add r6, r0, r3
/* 80088600 000851E0  38 64 00 00 */	addi r3, r4, 0
/* 80088604 000851E4  57 C4 06 3E */	clrlwi r4, r30, 0x18
/* 80088608 000851E8  57 E5 06 3E */	clrlwi r5, r31, 0x18
/* 8008860C 000851EC  38 C6 00 4E */	addi r6, r6, 0x4e
/* 80088610 000851F0  4B F9 B2 61 */	bl func_80023870
/* 80088614 000851F4  90 7D 21 54 */	stw r3, 0x2154(r29)
/* 80088618 000851F8  48 00 00 0C */	b lbl_80088624
lbl_8008861C:
/* 8008861C 000851FC  7F A3 EB 78 */	mr r3, r29
/* 80088620 00085200  48 00 02 C1 */	bl func_800888E0
lbl_80088624:
/* 80088624 00085204  80 01 00 2C */	lwz r0, 0x2c(r1)
/* 80088628 00085208  83 E1 00 24 */	lwz r31, 0x24(r1)
/* 8008862C 0008520C  83 C1 00 20 */	lwz r30, 0x20(r1)
/* 80088630 00085210  83 A1 00 1C */	lwz r29, 0x1c(r1)
/* 80088634 00085214  38 21 00 28 */	addi r1, r1, 0x28
/* 80088638 00085218  7C 08 03 A6 */	mtlr r0
/* 8008863C 0008521C  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

extern unk_t func_8008893C();

#pragma push
asm unk_t func_80088640()
{ // clang-format off
    nofralloc
/* 80088640 00085220  7C 08 02 A6 */	mflr r0
/* 80088644 00085224  90 01 00 04 */	stw r0, 4(r1)
/* 80088648 00085228  3C 04 FF F8 */	addis r0, r4, 0xfff8
/* 8008864C 0008522C  28 00 3D 60 */	cmplwi r0, 0x3d60
/* 80088650 00085230  94 21 FF D8 */	stwu r1, -0x28(r1)
/* 80088654 00085234  93 E1 00 24 */	stw r31, 0x24(r1)
/* 80088658 00085238  3B E6 00 00 */	addi r31, r6, 0
/* 8008865C 0008523C  93 C1 00 20 */	stw r30, 0x20(r1)
/* 80088660 00085240  3B C5 00 00 */	addi r30, r5, 0
/* 80088664 00085244  93 A1 00 1C */	stw r29, 0x1c(r1)
/* 80088668 00085248  3B A3 00 00 */	addi r29, r3, 0
/* 8008866C 0008524C  41 82 00 50 */	beq lbl_800886BC
/* 80088670 00085250  28 00 3D 61 */	cmplwi r0, 0x3d61
/* 80088674 00085254  41 82 00 40 */	beq lbl_800886B4
/* 80088678 00085258  7F A3 EB 78 */	mr r3, r29
/* 8008867C 0008525C  4B FF F6 91 */	bl func_80087D0C
/* 80088680 00085260  88 1D 00 0C */	lbz r0, 0xc(r29)
/* 80088684 00085264  38 83 00 00 */	addi r4, r3, 0
/* 80088688 00085268  88 BD 22 1F */	lbz r5, 0x221f(r29)
/* 8008868C 0008526C  54 00 08 3C */	slwi r0, r0, 1
/* 80088690 00085270  54 A3 EF FE */	rlwinm r3, r5, 0x1d, 0x1f, 0x1f
/* 80088694 00085274  7C C0 1A 14 */	add r6, r0, r3
/* 80088698 00085278  38 64 00 00 */	addi r3, r4, 0
/* 8008869C 0008527C  57 C4 06 3E */	clrlwi r4, r30, 0x18
/* 800886A0 00085280  57 E5 06 3E */	clrlwi r5, r31, 0x18
/* 800886A4 00085284  38 C6 00 5A */	addi r6, r6, 0x5a
/* 800886A8 00085288  4B F9 B1 C9 */	bl func_80023870
/* 800886AC 0008528C  90 7D 21 58 */	stw r3, 0x2158(r29)
/* 800886B0 00085290  48 00 00 0C */	b lbl_800886BC
lbl_800886B4:
/* 800886B4 00085294  7F A3 EB 78 */	mr r3, r29
/* 800886B8 00085298  48 00 02 85 */	bl func_8008893C
lbl_800886BC:
/* 800886BC 0008529C  80 01 00 2C */	lwz r0, 0x2c(r1)
/* 800886C0 000852A0  83 E1 00 24 */	lwz r31, 0x24(r1)
/* 800886C4 000852A4  83 C1 00 20 */	lwz r30, 0x20(r1)
/* 800886C8 000852A8  83 A1 00 1C */	lwz r29, 0x1c(r1)
/* 800886CC 000852AC  38 21 00 28 */	addi r1, r1, 0x28
/* 800886D0 000852B0  7C 08 03 A6 */	mtlr r0
/* 800886D4 000852B4  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

extern unk_t func_80088998();

#pragma push
asm unk_t func_800886D8()
{ // clang-format off
    nofralloc
/* 800886D8 000852B8  7C 08 02 A6 */	mflr r0
/* 800886DC 000852BC  90 01 00 04 */	stw r0, 4(r1)
/* 800886E0 000852C0  3C 04 FF F8 */	addis r0, r4, 0xfff8
/* 800886E4 000852C4  28 00 3D 60 */	cmplwi r0, 0x3d60
/* 800886E8 000852C8  94 21 FF D8 */	stwu r1, -0x28(r1)
/* 800886EC 000852CC  93 E1 00 24 */	stw r31, 0x24(r1)
/* 800886F0 000852D0  3B E6 00 00 */	addi r31, r6, 0
/* 800886F4 000852D4  93 C1 00 20 */	stw r30, 0x20(r1)
/* 800886F8 000852D8  3B C5 00 00 */	addi r30, r5, 0
/* 800886FC 000852DC  93 A1 00 1C */	stw r29, 0x1c(r1)
/* 80088700 000852E0  3B A3 00 00 */	addi r29, r3, 0
/* 80088704 000852E4  41 82 00 50 */	beq lbl_80088754
/* 80088708 000852E8  28 00 3D 61 */	cmplwi r0, 0x3d61
/* 8008870C 000852EC  41 82 00 40 */	beq lbl_8008874C
/* 80088710 000852F0  7F A3 EB 78 */	mr r3, r29
/* 80088714 000852F4  4B FF F5 F9 */	bl func_80087D0C
/* 80088718 000852F8  88 1D 00 0C */	lbz r0, 0xc(r29)
/* 8008871C 000852FC  38 83 00 00 */	addi r4, r3, 0
/* 80088720 00085300  88 BD 22 1F */	lbz r5, 0x221f(r29)
/* 80088724 00085304  54 00 08 3C */	slwi r0, r0, 1
/* 80088728 00085308  54 A3 EF FE */	rlwinm r3, r5, 0x1d, 0x1f, 0x1f
/* 8008872C 0008530C  7C C0 1A 14 */	add r6, r0, r3
/* 80088730 00085310  38 64 00 00 */	addi r3, r4, 0
/* 80088734 00085314  57 C4 06 3E */	clrlwi r4, r30, 0x18
/* 80088738 00085318  57 E5 06 3E */	clrlwi r5, r31, 0x18
/* 8008873C 0008531C  38 C6 00 72 */	addi r6, r6, 0x72
/* 80088740 00085320  4B F9 B1 31 */	bl func_80023870
/* 80088744 00085324  90 7D 21 5C */	stw r3, 0x215c(r29)
/* 80088748 00085328  48 00 00 0C */	b lbl_80088754
lbl_8008874C:
/* 8008874C 0008532C  7F A3 EB 78 */	mr r3, r29
/* 80088750 00085330  48 00 02 49 */	bl func_80088998
lbl_80088754:
/* 80088754 00085334  80 01 00 2C */	lwz r0, 0x2c(r1)
/* 80088758 00085338  83 E1 00 24 */	lwz r31, 0x24(r1)
/* 8008875C 0008533C  83 C1 00 20 */	lwz r30, 0x20(r1)
/* 80088760 00085340  83 A1 00 1C */	lwz r29, 0x1c(r1)
/* 80088764 00085344  38 21 00 28 */	addi r1, r1, 0x28
/* 80088768 00085348  7C 08 03 A6 */	mtlr r0
/* 8008876C 0008534C  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

#pragma push
asm unk_t func_80088770()
{ // clang-format off
    nofralloc
/* 80088770 00085350  7C 08 02 A6 */	mflr r0
/* 80088774 00085354  38 A0 00 40 */	li r5, 0x40
/* 80088778 00085358  90 01 00 04 */	stw r0, 4(r1)
/* 8008877C 0008535C  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 80088780 00085360  93 E1 00 14 */	stw r31, 0x14(r1)
/* 80088784 00085364  7C 7F 1B 78 */	mr r31, r3
/* 80088788 00085368  88 83 22 1F */	lbz r4, 0x221f(r3)
/* 8008878C 0008536C  3C 60 00 08 */	lis r3, 0x00083D61@ha
/* 80088790 00085370  88 1F 00 0C */	lbz r0, 0xc(r31)
/* 80088794 00085374  38 63 3D 61 */	addi r3, r3, 0x00083D61@l
/* 80088798 00085378  54 84 EF FE */	rlwinm r4, r4, 0x1d, 0x1f, 0x1f
/* 8008879C 0008537C  54 00 08 3C */	slwi r0, r0, 1
/* 800887A0 00085380  7C C0 22 14 */	add r6, r0, r4
/* 800887A4 00085384  38 80 00 00 */	li r4, 0
/* 800887A8 00085388  38 C6 00 1E */	addi r6, r6, 0x1e
/* 800887AC 0008538C  4B F9 B0 C5 */	bl func_80023870
/* 800887B0 00085390  38 00 FF FF */	li r0, -1
/* 800887B4 00085394  90 1F 21 44 */	stw r0, 0x2144(r31)
/* 800887B8 00085398  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 800887BC 0008539C  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 800887C0 000853A0  38 21 00 18 */	addi r1, r1, 0x18
/* 800887C4 000853A4  7C 08 03 A6 */	mtlr r0
/* 800887C8 000853A8  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

#pragma push
asm void func_800887CC(Fighter* fp)
{ // clang-format off
    nofralloc
/* 800887CC 000853AC  7C 08 02 A6 */	mflr r0
/* 800887D0 000853B0  38 A0 00 40 */	li r5, 0x40
/* 800887D4 000853B4  90 01 00 04 */	stw r0, 4(r1)
/* 800887D8 000853B8  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 800887DC 000853BC  93 E1 00 14 */	stw r31, 0x14(r1)
/* 800887E0 000853C0  7C 7F 1B 78 */	mr r31, r3
/* 800887E4 000853C4  88 83 22 1F */	lbz r4, 0x221f(r3)
/* 800887E8 000853C8  3C 60 00 08 */	lis r3, 0x00083D61@ha
/* 800887EC 000853CC  88 1F 00 0C */	lbz r0, 0xc(r31)
/* 800887F0 000853D0  38 63 3D 61 */	addi r3, r3, 0x00083D61@l
/* 800887F4 000853D4  54 84 EF FE */	rlwinm r4, r4, 0x1d, 0x1f, 0x1f
/* 800887F8 000853D8  54 00 08 3C */	slwi r0, r0, 1
/* 800887FC 000853DC  7C C0 22 14 */	add r6, r0, r4
/* 80088800 000853E0  38 80 00 00 */	li r4, 0
/* 80088804 000853E4  38 C6 00 2A */	addi r6, r6, 0x2a
/* 80088808 000853E8  4B F9 B0 69 */	bl func_80023870
/* 8008880C 000853EC  38 00 FF FF */	li r0, -1
/* 80088810 000853F0  90 1F 21 48 */	stw r0, 0x2148(r31)
/* 80088814 000853F4  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 80088818 000853F8  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 8008881C 000853FC  38 21 00 18 */	addi r1, r1, 0x18
/* 80088820 00085400  7C 08 03 A6 */	mtlr r0
/* 80088824 00085404  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

#pragma push
asm unk_t func_80088828()
{ // clang-format off
    nofralloc
/* 80088828 00085408  7C 08 02 A6 */	mflr r0
/* 8008882C 0008540C  38 A0 00 40 */	li r5, 0x40
/* 80088830 00085410  90 01 00 04 */	stw r0, 4(r1)
/* 80088834 00085414  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 80088838 00085418  93 E1 00 14 */	stw r31, 0x14(r1)
/* 8008883C 0008541C  7C 7F 1B 78 */	mr r31, r3
/* 80088840 00085420  88 83 22 1F */	lbz r4, 0x221f(r3)
/* 80088844 00085424  3C 60 00 08 */	lis r3, 0x00083D61@ha
/* 80088848 00085428  88 1F 00 0C */	lbz r0, 0xc(r31)
/* 8008884C 0008542C  38 63 3D 61 */	addi r3, r3, 0x00083D61@l
/* 80088850 00085430  54 84 EF FE */	rlwinm r4, r4, 0x1d, 0x1f, 0x1f
/* 80088854 00085434  54 00 08 3C */	slwi r0, r0, 1
/* 80088858 00085438  7C C0 22 14 */	add r6, r0, r4
/* 8008885C 0008543C  38 80 00 00 */	li r4, 0
/* 80088860 00085440  38 C6 00 36 */	addi r6, r6, 0x36
/* 80088864 00085444  4B F9 B0 0D */	bl func_80023870
/* 80088868 00085448  38 00 FF FF */	li r0, -1
/* 8008886C 0008544C  90 1F 21 4C */	stw r0, 0x214c(r31)
/* 80088870 00085450  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 80088874 00085454  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 80088878 00085458  38 21 00 18 */	addi r1, r1, 0x18
/* 8008887C 0008545C  7C 08 03 A6 */	mtlr r0
/* 80088880 00085460  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

#pragma push
asm void func_80088884(Fighter* fp)
{ // clang-format off
    nofralloc
/* 80088884 00085464  7C 08 02 A6 */	mflr r0
/* 80088888 00085468  38 A0 00 40 */	li r5, 0x40
/* 8008888C 0008546C  90 01 00 04 */	stw r0, 4(r1)
/* 80088890 00085470  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 80088894 00085474  93 E1 00 14 */	stw r31, 0x14(r1)
/* 80088898 00085478  7C 7F 1B 78 */	mr r31, r3
/* 8008889C 0008547C  88 83 22 1F */	lbz r4, 0x221f(r3)
/* 800888A0 00085480  3C 60 00 08 */	lis r3, 0x00083D61@ha
/* 800888A4 00085484  88 1F 00 0C */	lbz r0, 0xc(r31)
/* 800888A8 00085488  38 63 3D 61 */	addi r3, r3, 0x00083D61@l
/* 800888AC 0008548C  54 84 EF FE */	rlwinm r4, r4, 0x1d, 0x1f, 0x1f
/* 800888B0 00085490  54 00 08 3C */	slwi r0, r0, 1
/* 800888B4 00085494  7C C0 22 14 */	add r6, r0, r4
/* 800888B8 00085498  38 80 00 00 */	li r4, 0
/* 800888BC 0008549C  38 C6 00 42 */	addi r6, r6, 0x42
/* 800888C0 000854A0  4B F9 AF B1 */	bl func_80023870
/* 800888C4 000854A4  38 00 FF FF */	li r0, -1
/* 800888C8 000854A8  90 1F 21 50 */	stw r0, 0x2150(r31)
/* 800888CC 000854AC  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 800888D0 000854B0  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 800888D4 000854B4  38 21 00 18 */	addi r1, r1, 0x18
/* 800888D8 000854B8  7C 08 03 A6 */	mtlr r0
/* 800888DC 000854BC  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

#pragma push
asm void func_800888E0(Fighter* fp)
{ // clang-format off
    nofralloc
/* 800888E0 000854C0  7C 08 02 A6 */	mflr r0
/* 800888E4 000854C4  38 A0 00 40 */	li r5, 0x40
/* 800888E8 000854C8  90 01 00 04 */	stw r0, 4(r1)
/* 800888EC 000854CC  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 800888F0 000854D0  93 E1 00 14 */	stw r31, 0x14(r1)
/* 800888F4 000854D4  7C 7F 1B 78 */	mr r31, r3
/* 800888F8 000854D8  88 83 22 1F */	lbz r4, 0x221f(r3)
/* 800888FC 000854DC  3C 60 00 08 */	lis r3, 0x00083D61@ha
/* 80088900 000854E0  88 1F 00 0C */	lbz r0, 0xc(r31)
/* 80088904 000854E4  38 63 3D 61 */	addi r3, r3, 0x00083D61@l
/* 80088908 000854E8  54 84 EF FE */	rlwinm r4, r4, 0x1d, 0x1f, 0x1f
/* 8008890C 000854EC  54 00 08 3C */	slwi r0, r0, 1
/* 80088910 000854F0  7C C0 22 14 */	add r6, r0, r4
/* 80088914 000854F4  38 80 00 00 */	li r4, 0
/* 80088918 000854F8  38 C6 00 4E */	addi r6, r6, 0x4e
/* 8008891C 000854FC  4B F9 AF 55 */	bl func_80023870
/* 80088920 00085500  38 00 FF FF */	li r0, -1
/* 80088924 00085504  90 1F 21 54 */	stw r0, 0x2154(r31)
/* 80088928 00085508  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 8008892C 0008550C  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 80088930 00085510  38 21 00 18 */	addi r1, r1, 0x18
/* 80088934 00085514  7C 08 03 A6 */	mtlr r0
/* 80088938 00085518  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

#pragma push
asm unk_t func_8008893C()
{ // clang-format off
    nofralloc
/* 8008893C 0008551C  7C 08 02 A6 */	mflr r0
/* 80088940 00085520  38 A0 00 40 */	li r5, 0x40
/* 80088944 00085524  90 01 00 04 */	stw r0, 4(r1)
/* 80088948 00085528  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 8008894C 0008552C  93 E1 00 14 */	stw r31, 0x14(r1)
/* 80088950 00085530  7C 7F 1B 78 */	mr r31, r3
/* 80088954 00085534  88 83 22 1F */	lbz r4, 0x221f(r3)
/* 80088958 00085538  3C 60 00 08 */	lis r3, 0x00083D61@ha
/* 8008895C 0008553C  88 1F 00 0C */	lbz r0, 0xc(r31)
/* 80088960 00085540  38 63 3D 61 */	addi r3, r3, 0x00083D61@l
/* 80088964 00085544  54 84 EF FE */	rlwinm r4, r4, 0x1d, 0x1f, 0x1f
/* 80088968 00085548  54 00 08 3C */	slwi r0, r0, 1
/* 8008896C 0008554C  7C C0 22 14 */	add r6, r0, r4
/* 80088970 00085550  38 80 00 00 */	li r4, 0
/* 80088974 00085554  38 C6 00 5A */	addi r6, r6, 0x5a
/* 80088978 00085558  4B F9 AE F9 */	bl func_80023870
/* 8008897C 0008555C  38 00 FF FF */	li r0, -1
/* 80088980 00085560  90 1F 21 58 */	stw r0, 0x2158(r31)
/* 80088984 00085564  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 80088988 00085568  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 8008898C 0008556C  38 21 00 18 */	addi r1, r1, 0x18
/* 80088990 00085570  7C 08 03 A6 */	mtlr r0
/* 80088994 00085574  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

#pragma push
asm unk_t func_80088998()
{ // clang-format off
    nofralloc
/* 80088998 00085578  7C 08 02 A6 */	mflr r0
/* 8008899C 0008557C  38 A0 00 40 */	li r5, 0x40
/* 800889A0 00085580  90 01 00 04 */	stw r0, 4(r1)
/* 800889A4 00085584  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 800889A8 00085588  93 E1 00 14 */	stw r31, 0x14(r1)
/* 800889AC 0008558C  7C 7F 1B 78 */	mr r31, r3
/* 800889B0 00085590  88 83 22 1F */	lbz r4, 0x221f(r3)
/* 800889B4 00085594  3C 60 00 08 */	lis r3, 0x00083D61@ha
/* 800889B8 00085598  88 1F 00 0C */	lbz r0, 0xc(r31)
/* 800889BC 0008559C  38 63 3D 61 */	addi r3, r3, 0x00083D61@l
/* 800889C0 000855A0  54 84 EF FE */	rlwinm r4, r4, 0x1d, 0x1f, 0x1f
/* 800889C4 000855A4  54 00 08 3C */	slwi r0, r0, 1
/* 800889C8 000855A8  7C C0 22 14 */	add r6, r0, r4
/* 800889CC 000855AC  38 80 00 00 */	li r4, 0
/* 800889D0 000855B0  38 C6 00 72 */	addi r6, r6, 0x72
/* 800889D4 000855B4  4B F9 AE 9D */	bl func_80023870
/* 800889D8 000855B8  38 00 FF FF */	li r0, -1
/* 800889DC 000855BC  90 1F 21 5C */	stw r0, 0x215c(r31)
/* 800889E0 000855C0  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 800889E4 000855C4  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 800889E8 000855C8  38 21 00 18 */	addi r1, r1, 0x18
/* 800889EC 000855CC  7C 08 03 A6 */	mtlr r0
/* 800889F0 000855D0  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

#pragma push
asm unk_t func_800889F4()
{ // clang-format off
    nofralloc
/* 800889F4 000855D4  7C 08 02 A6 */	mflr r0
/* 800889F8 000855D8  90 01 00 04 */	stw r0, 4(r1)
/* 800889FC 000855DC  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 80088A00 000855E0  93 E1 00 14 */	stw r31, 0x14(r1)
/* 80088A04 000855E4  7C 9F 23 79 */	or. r31, r4, r4
/* 80088A08 000855E8  93 C1 00 10 */	stw r30, 0x10(r1)
/* 80088A0C 000855EC  3B C3 00 00 */	addi r30, r3, 0
/* 80088A10 000855F0  41 82 00 28 */	beq lbl_80088A38
/* 80088A14 000855F4  80 7F 00 00 */	lwz r3, 0(r31)
/* 80088A18 000855F8  48 2F 7B 69 */	bl HSD_Randi
/* 80088A1C 000855FC  80 9F 00 04 */	lwz r4, 4(r31)
/* 80088A20 00085600  54 60 10 3A */	slwi r0, r3, 2
/* 80088A24 00085604  38 7E 00 00 */	addi r3, r30, 0
/* 80088A28 00085608  7C 84 00 2E */	lwzx r4, r4, r0
/* 80088A2C 0008560C  38 A0 00 7F */	li r5, 0x7f
/* 80088A30 00085610  38 C0 00 40 */	li r6, 0x40
/* 80088A34 00085614  4B FF F7 A5 */	bl func_800881D8
lbl_80088A38:
/* 80088A38 00085618  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 80088A3C 0008561C  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 80088A40 00085620  83 C1 00 10 */	lwz r30, 0x10(r1)
/* 80088A44 00085624  38 21 00 18 */	addi r1, r1, 0x18
/* 80088A48 00085628  7C 08 03 A6 */	mtlr r0
/* 80088A4C 0008562C  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

#pragma push
asm void func_80088A50(Fighter* fp)
{ // clang-format off
    nofralloc
/* 80088A50 00085630  7C 08 02 A6 */	mflr r0
/* 80088A54 00085634  38 A0 00 40 */	li r5, 0x40
/* 80088A58 00085638  90 01 00 04 */	stw r0, 4(r1)
/* 80088A5C 0008563C  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 80088A60 00085640  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 80088A64 00085644  93 C1 00 18 */	stw r30, 0x18(r1)
/* 80088A68 00085648  3F C0 00 08 */	lis r30, 0x00083D61@ha
/* 80088A6C 0008564C  93 A1 00 14 */	stw r29, 0x14(r1)
/* 80088A70 00085650  7C 7D 1B 78 */	mr r29, r3
/* 80088A74 00085654  88 03 00 0C */	lbz r0, 0xc(r3)
/* 80088A78 00085658  38 7E 3D 61 */	addi r3, r30, 0x00083D61@l
/* 80088A7C 0008565C  54 04 08 3C */	slwi r4, r0, 1
/* 80088A80 00085660  38 C4 00 36 */	addi r6, r4, 0x36
/* 80088A84 00085664  38 80 00 00 */	li r4, 0
/* 80088A88 00085668  4B F9 AD E9 */	bl func_80023870
/* 80088A8C 0008566C  88 1D 00 0C */	lbz r0, 0xc(r29)
/* 80088A90 00085670  38 7E 3D 61 */	addi r3, r30, 0x3d61
/* 80088A94 00085674  38 80 00 00 */	li r4, 0
/* 80088A98 00085678  54 05 08 3C */	slwi r5, r0, 1
/* 80088A9C 0008567C  38 C5 00 37 */	addi r6, r5, 0x37
/* 80088AA0 00085680  38 A0 00 40 */	li r5, 0x40
/* 80088AA4 00085684  4B F9 AD CD */	bl func_80023870
/* 80088AA8 00085688  3B E0 FF FF */	li r31, -1
/* 80088AAC 0008568C  93 FD 21 4C */	stw r31, 0x214c(r29)
/* 80088AB0 00085690  38 7E 3D 61 */	addi r3, r30, 0x3d61
/* 80088AB4 00085694  38 80 00 00 */	li r4, 0
/* 80088AB8 00085698  88 1D 00 0C */	lbz r0, 0xc(r29)
/* 80088ABC 0008569C  38 A0 00 40 */	li r5, 0x40
/* 80088AC0 000856A0  54 06 08 3C */	slwi r6, r0, 1
/* 80088AC4 000856A4  38 C6 00 1E */	addi r6, r6, 0x1e
/* 80088AC8 000856A8  4B F9 AD A9 */	bl func_80023870
/* 80088ACC 000856AC  88 1D 00 0C */	lbz r0, 0xc(r29)
/* 80088AD0 000856B0  38 7E 3D 61 */	addi r3, r30, 0x3d61
/* 80088AD4 000856B4  38 80 00 00 */	li r4, 0
/* 80088AD8 000856B8  54 05 08 3C */	slwi r5, r0, 1
/* 80088ADC 000856BC  38 C5 00 1F */	addi r6, r5, 0x1f
/* 80088AE0 000856C0  38 A0 00 40 */	li r5, 0x40
/* 80088AE4 000856C4  4B F9 AD 8D */	bl func_80023870
/* 80088AE8 000856C8  93 FD 21 44 */	stw r31, 0x2144(r29)
/* 80088AEC 000856CC  38 7E 3D 61 */	addi r3, r30, 0x3d61
/* 80088AF0 000856D0  38 80 00 00 */	li r4, 0
/* 80088AF4 000856D4  88 1D 00 0C */	lbz r0, 0xc(r29)
/* 80088AF8 000856D8  38 A0 00 40 */	li r5, 0x40
/* 80088AFC 000856DC  54 06 08 3C */	slwi r6, r0, 1
/* 80088B00 000856E0  38 C6 00 2A */	addi r6, r6, 0x2a
/* 80088B04 000856E4  4B F9 AD 6D */	bl func_80023870
/* 80088B08 000856E8  88 1D 00 0C */	lbz r0, 0xc(r29)
/* 80088B0C 000856EC  38 7E 3D 61 */	addi r3, r30, 0x3d61
/* 80088B10 000856F0  38 80 00 00 */	li r4, 0
/* 80088B14 000856F4  54 05 08 3C */	slwi r5, r0, 1
/* 80088B18 000856F8  38 C5 00 2B */	addi r6, r5, 0x2b
/* 80088B1C 000856FC  38 A0 00 40 */	li r5, 0x40
/* 80088B20 00085700  4B F9 AD 51 */	bl func_80023870
/* 80088B24 00085704  93 FD 21 48 */	stw r31, 0x2148(r29)
/* 80088B28 00085708  38 7E 3D 61 */	addi r3, r30, 0x3d61
/* 80088B2C 0008570C  38 80 00 00 */	li r4, 0
/* 80088B30 00085710  88 1D 00 0C */	lbz r0, 0xc(r29)
/* 80088B34 00085714  38 A0 00 40 */	li r5, 0x40
/* 80088B38 00085718  54 06 08 3C */	slwi r6, r0, 1
/* 80088B3C 0008571C  38 C6 00 42 */	addi r6, r6, 0x42
/* 80088B40 00085720  4B F9 AD 31 */	bl func_80023870
/* 80088B44 00085724  88 1D 00 0C */	lbz r0, 0xc(r29)
/* 80088B48 00085728  38 7E 3D 61 */	addi r3, r30, 0x3d61
/* 80088B4C 0008572C  38 80 00 00 */	li r4, 0
/* 80088B50 00085730  54 05 08 3C */	slwi r5, r0, 1
/* 80088B54 00085734  38 C5 00 43 */	addi r6, r5, 0x43
/* 80088B58 00085738  38 A0 00 40 */	li r5, 0x40
/* 80088B5C 0008573C  4B F9 AD 15 */	bl func_80023870
/* 80088B60 00085740  93 FD 21 50 */	stw r31, 0x2150(r29)
/* 80088B64 00085744  38 7E 3D 61 */	addi r3, r30, 0x3d61
/* 80088B68 00085748  38 80 00 00 */	li r4, 0
/* 80088B6C 0008574C  88 1D 00 0C */	lbz r0, 0xc(r29)
/* 80088B70 00085750  38 A0 00 40 */	li r5, 0x40
/* 80088B74 00085754  54 06 08 3C */	slwi r6, r0, 1
/* 80088B78 00085758  38 C6 00 4E */	addi r6, r6, 0x4e
/* 80088B7C 0008575C  4B F9 AC F5 */	bl func_80023870
/* 80088B80 00085760  88 1D 00 0C */	lbz r0, 0xc(r29)
/* 80088B84 00085764  38 7E 3D 61 */	addi r3, r30, 0x3d61
/* 80088B88 00085768  38 80 00 00 */	li r4, 0
/* 80088B8C 0008576C  54 05 08 3C */	slwi r5, r0, 1
/* 80088B90 00085770  38 C5 00 4F */	addi r6, r5, 0x4f
/* 80088B94 00085774  38 A0 00 40 */	li r5, 0x40
/* 80088B98 00085778  4B F9 AC D9 */	bl func_80023870
/* 80088B9C 0008577C  93 FD 21 54 */	stw r31, 0x2154(r29)
/* 80088BA0 00085780  38 7E 3D 61 */	addi r3, r30, 0x3d61
/* 80088BA4 00085784  38 80 00 00 */	li r4, 0
/* 80088BA8 00085788  88 1D 00 0C */	lbz r0, 0xc(r29)
/* 80088BAC 0008578C  38 A0 00 40 */	li r5, 0x40
/* 80088BB0 00085790  54 06 08 3C */	slwi r6, r0, 1
/* 80088BB4 00085794  38 C6 00 5A */	addi r6, r6, 0x5a
/* 80088BB8 00085798  4B F9 AC B9 */	bl func_80023870
/* 80088BBC 0008579C  88 1D 00 0C */	lbz r0, 0xc(r29)
/* 80088BC0 000857A0  38 7E 3D 61 */	addi r3, r30, 0x3d61
/* 80088BC4 000857A4  38 80 00 00 */	li r4, 0
/* 80088BC8 000857A8  54 05 08 3C */	slwi r5, r0, 1
/* 80088BCC 000857AC  38 C5 00 5B */	addi r6, r5, 0x5b
/* 80088BD0 000857B0  38 A0 00 40 */	li r5, 0x40
/* 80088BD4 000857B4  4B F9 AC 9D */	bl func_80023870
/* 80088BD8 000857B8  93 FD 21 58 */	stw r31, 0x2158(r29)
/* 80088BDC 000857BC  38 7E 3D 61 */	addi r3, r30, 0x3d61
/* 80088BE0 000857C0  38 80 00 00 */	li r4, 0
/* 80088BE4 000857C4  88 1D 00 0C */	lbz r0, 0xc(r29)
/* 80088BE8 000857C8  38 A0 00 40 */	li r5, 0x40
/* 80088BEC 000857CC  54 06 08 3C */	slwi r6, r0, 1
/* 80088BF0 000857D0  38 C6 00 72 */	addi r6, r6, 0x72
/* 80088BF4 000857D4  4B F9 AC 7D */	bl func_80023870
/* 80088BF8 000857D8  88 1D 00 0C */	lbz r0, 0xc(r29)
/* 80088BFC 000857DC  38 7E 3D 61 */	addi r3, r30, 0x3d61
/* 80088C00 000857E0  38 80 00 00 */	li r4, 0
/* 80088C04 000857E4  54 05 08 3C */	slwi r5, r0, 1
/* 80088C08 000857E8  38 C5 00 73 */	addi r6, r5, 0x73
/* 80088C0C 000857EC  38 A0 00 40 */	li r5, 0x40
/* 80088C10 000857F0  4B F9 AC 61 */	bl func_80023870
/* 80088C14 000857F4  93 FD 21 5C */	stw r31, 0x215c(r29)
/* 80088C18 000857F8  93 FD 21 60 */	stw r31, 0x2160(r29)
/* 80088C1C 000857FC  80 7D 21 64 */	lwz r3, 0x2164(r29)
/* 80088C20 00085800  4B F9 C3 ED */	bl func_8002500C
/* 80088C24 00085804  3B C0 00 00 */	li r30, 0
/* 80088C28 00085808  93 DD 21 64 */	stw r30, 0x2164(r29)
/* 80088C2C 0008580C  80 7D 21 68 */	lwz r3, 0x2168(r29)
/* 80088C30 00085810  4B F9 C4 09 */	bl func_80025038
/* 80088C34 00085814  93 DD 21 68 */	stw r30, 0x2168(r29)
/* 80088C38 00085818  93 DD 21 68 */	stw r30, 0x2168(r29)
/* 80088C3C 0008581C  93 DD 21 64 */	stw r30, 0x2164(r29)
/* 80088C40 00085820  80 01 00 24 */	lwz r0, 0x24(r1)
/* 80088C44 00085824  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 80088C48 00085828  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 80088C4C 0008582C  83 A1 00 14 */	lwz r29, 0x14(r1)
/* 80088C50 00085830  38 21 00 20 */	addi r1, r1, 0x20
/* 80088C54 00085834  7C 08 03 A6 */	mtlr r0
/* 80088C58 00085838  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

extern unk_t func_800265C4();
extern void func_80026510(HSD_GObj*);

#pragma push
asm void func_80088C5C(HSD_GObj* fighter_gobj)
{ // clang-format off
    nofralloc
/* 80088C5C 0008583C  7C 08 02 A6 */	mflr r0
/* 80088C60 00085840  90 01 00 04 */	stw r0, 4(r1)
/* 80088C64 00085844  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 80088C68 00085848  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 80088C6C 0008584C  93 C1 00 18 */	stw r30, 0x18(r1)
/* 80088C70 00085850  7C 7E 1B 78 */	mr r30, r3
/* 80088C74 00085854  93 A1 00 14 */	stw r29, 0x14(r1)
/* 80088C78 00085858  83 A3 00 2C */	lwz r29, 0x2c(r3)
/* 80088C7C 0008585C  4B F9 D8 95 */	bl func_80026510
/* 80088C80 00085860  80 9D 21 60 */	lwz r4, 0x2160(r29)
/* 80088C84 00085864  2C 04 FF FF */	cmpwi r4, -1
/* 80088C88 00085868  41 82 00 14 */	beq lbl_80088C9C
/* 80088C8C 0008586C  7F C3 F3 78 */	mr r3, r30
/* 80088C90 00085870  4B F9 D9 35 */	bl func_800265C4
/* 80088C94 00085874  38 00 FF FF */	li r0, -1
/* 80088C98 00085878  90 1D 21 60 */	stw r0, 0x2160(r29)
lbl_80088C9C:
/* 80088C9C 0008587C  80 9D 21 4C */	lwz r4, 0x214c(r29)
/* 80088CA0 00085880  2C 04 FF FF */	cmpwi r4, -1
/* 80088CA4 00085884  41 82 00 48 */	beq lbl_80088CEC
/* 80088CA8 00085888  7F C3 F3 78 */	mr r3, r30
/* 80088CAC 0008588C  4B F9 D9 19 */	bl func_800265C4
/* 80088CB0 00085890  2C 03 00 01 */	cmpwi r3, 1
/* 80088CB4 00085894  40 82 00 38 */	bne lbl_80088CEC
/* 80088CB8 00085898  88 9D 22 1F */	lbz r4, 0x221f(r29)
/* 80088CBC 0008589C  3C 60 00 08 */	lis r3, 0x00083D61@ha
/* 80088CC0 000858A0  88 1D 00 0C */	lbz r0, 0xc(r29)
/* 80088CC4 000858A4  38 63 3D 61 */	addi r3, r3, 0x00083D61@l
/* 80088CC8 000858A8  54 84 EF FE */	rlwinm r4, r4, 0x1d, 0x1f, 0x1f
/* 80088CCC 000858AC  54 00 08 3C */	slwi r0, r0, 1
/* 80088CD0 000858B0  7C C0 22 14 */	add r6, r0, r4
/* 80088CD4 000858B4  38 80 00 00 */	li r4, 0
/* 80088CD8 000858B8  38 A0 00 40 */	li r5, 0x40
/* 80088CDC 000858BC  38 C6 00 36 */	addi r6, r6, 0x36
/* 80088CE0 000858C0  4B F9 AB 91 */	bl func_80023870
/* 80088CE4 000858C4  38 00 FF FF */	li r0, -1
/* 80088CE8 000858C8  90 1D 21 4C */	stw r0, 0x214c(r29)
lbl_80088CEC:
/* 80088CEC 000858CC  80 9D 21 44 */	lwz r4, 0x2144(r29)
/* 80088CF0 000858D0  2C 04 FF FF */	cmpwi r4, -1
/* 80088CF4 000858D4  41 82 00 48 */	beq lbl_80088D3C
/* 80088CF8 000858D8  7F C3 F3 78 */	mr r3, r30
/* 80088CFC 000858DC  4B F9 D8 C9 */	bl func_800265C4
/* 80088D00 000858E0  2C 03 00 01 */	cmpwi r3, 1
/* 80088D04 000858E4  40 82 00 38 */	bne lbl_80088D3C
/* 80088D08 000858E8  88 9D 22 1F */	lbz r4, 0x221f(r29)
/* 80088D0C 000858EC  3C 60 00 08 */	lis r3, 0x00083D61@ha
/* 80088D10 000858F0  88 1D 00 0C */	lbz r0, 0xc(r29)
/* 80088D14 000858F4  38 63 3D 61 */	addi r3, r3, 0x00083D61@l
/* 80088D18 000858F8  54 84 EF FE */	rlwinm r4, r4, 0x1d, 0x1f, 0x1f
/* 80088D1C 000858FC  54 00 08 3C */	slwi r0, r0, 1
/* 80088D20 00085900  7C C0 22 14 */	add r6, r0, r4
/* 80088D24 00085904  38 80 00 00 */	li r4, 0
/* 80088D28 00085908  38 A0 00 40 */	li r5, 0x40
/* 80088D2C 0008590C  38 C6 00 1E */	addi r6, r6, 0x1e
/* 80088D30 00085910  4B F9 AB 41 */	bl func_80023870
/* 80088D34 00085914  38 00 FF FF */	li r0, -1
/* 80088D38 00085918  90 1D 21 44 */	stw r0, 0x2144(r29)
lbl_80088D3C:
/* 80088D3C 0008591C  80 9D 21 48 */	lwz r4, 0x2148(r29)
/* 80088D40 00085920  2C 04 FF FF */	cmpwi r4, -1
/* 80088D44 00085924  41 82 00 48 */	beq lbl_80088D8C
/* 80088D48 00085928  7F C3 F3 78 */	mr r3, r30
/* 80088D4C 0008592C  4B F9 D8 79 */	bl func_800265C4
/* 80088D50 00085930  2C 03 00 01 */	cmpwi r3, 1
/* 80088D54 00085934  40 82 00 38 */	bne lbl_80088D8C
/* 80088D58 00085938  88 9D 22 1F */	lbz r4, 0x221f(r29)
/* 80088D5C 0008593C  3C 60 00 08 */	lis r3, 0x00083D61@ha
/* 80088D60 00085940  88 1D 00 0C */	lbz r0, 0xc(r29)
/* 80088D64 00085944  38 63 3D 61 */	addi r3, r3, 0x00083D61@l
/* 80088D68 00085948  54 84 EF FE */	rlwinm r4, r4, 0x1d, 0x1f, 0x1f
/* 80088D6C 0008594C  54 00 08 3C */	slwi r0, r0, 1
/* 80088D70 00085950  7C C0 22 14 */	add r6, r0, r4
/* 80088D74 00085954  38 80 00 00 */	li r4, 0
/* 80088D78 00085958  38 A0 00 40 */	li r5, 0x40
/* 80088D7C 0008595C  38 C6 00 2A */	addi r6, r6, 0x2a
/* 80088D80 00085960  4B F9 AA F1 */	bl func_80023870
/* 80088D84 00085964  38 00 FF FF */	li r0, -1
/* 80088D88 00085968  90 1D 21 48 */	stw r0, 0x2148(r29)
lbl_80088D8C:
/* 80088D8C 0008596C  80 9D 21 50 */	lwz r4, 0x2150(r29)
/* 80088D90 00085970  2C 04 FF FF */	cmpwi r4, -1
/* 80088D94 00085974  41 82 00 48 */	beq lbl_80088DDC
/* 80088D98 00085978  7F C3 F3 78 */	mr r3, r30
/* 80088D9C 0008597C  4B F9 D8 29 */	bl func_800265C4
/* 80088DA0 00085980  2C 03 00 01 */	cmpwi r3, 1
/* 80088DA4 00085984  40 82 00 38 */	bne lbl_80088DDC
/* 80088DA8 00085988  88 9D 22 1F */	lbz r4, 0x221f(r29)
/* 80088DAC 0008598C  3C 60 00 08 */	lis r3, 0x00083D61@ha
/* 80088DB0 00085990  88 1D 00 0C */	lbz r0, 0xc(r29)
/* 80088DB4 00085994  38 63 3D 61 */	addi r3, r3, 0x00083D61@l
/* 80088DB8 00085998  54 84 EF FE */	rlwinm r4, r4, 0x1d, 0x1f, 0x1f
/* 80088DBC 0008599C  54 00 08 3C */	slwi r0, r0, 1
/* 80088DC0 000859A0  7C C0 22 14 */	add r6, r0, r4
/* 80088DC4 000859A4  38 80 00 00 */	li r4, 0
/* 80088DC8 000859A8  38 A0 00 40 */	li r5, 0x40
/* 80088DCC 000859AC  38 C6 00 42 */	addi r6, r6, 0x42
/* 80088DD0 000859B0  4B F9 AA A1 */	bl func_80023870
/* 80088DD4 000859B4  38 00 FF FF */	li r0, -1
/* 80088DD8 000859B8  90 1D 21 50 */	stw r0, 0x2150(r29)
lbl_80088DDC:
/* 80088DDC 000859BC  80 9D 21 54 */	lwz r4, 0x2154(r29)
/* 80088DE0 000859C0  2C 04 FF FF */	cmpwi r4, -1
/* 80088DE4 000859C4  41 82 00 48 */	beq lbl_80088E2C
/* 80088DE8 000859C8  7F C3 F3 78 */	mr r3, r30
/* 80088DEC 000859CC  4B F9 D7 D9 */	bl func_800265C4
/* 80088DF0 000859D0  2C 03 00 01 */	cmpwi r3, 1
/* 80088DF4 000859D4  40 82 00 38 */	bne lbl_80088E2C
/* 80088DF8 000859D8  88 9D 22 1F */	lbz r4, 0x221f(r29)
/* 80088DFC 000859DC  3C 60 00 08 */	lis r3, 0x00083D61@ha
/* 80088E00 000859E0  88 1D 00 0C */	lbz r0, 0xc(r29)
/* 80088E04 000859E4  38 63 3D 61 */	addi r3, r3, 0x00083D61@l
/* 80088E08 000859E8  54 84 EF FE */	rlwinm r4, r4, 0x1d, 0x1f, 0x1f
/* 80088E0C 000859EC  54 00 08 3C */	slwi r0, r0, 1
/* 80088E10 000859F0  7C C0 22 14 */	add r6, r0, r4
/* 80088E14 000859F4  38 80 00 00 */	li r4, 0
/* 80088E18 000859F8  38 A0 00 40 */	li r5, 0x40
/* 80088E1C 000859FC  38 C6 00 4E */	addi r6, r6, 0x4e
/* 80088E20 00085A00  4B F9 AA 51 */	bl func_80023870
/* 80088E24 00085A04  38 00 FF FF */	li r0, -1
/* 80088E28 00085A08  90 1D 21 54 */	stw r0, 0x2154(r29)
lbl_80088E2C:
/* 80088E2C 00085A0C  80 9D 21 58 */	lwz r4, 0x2158(r29)
/* 80088E30 00085A10  2C 04 FF FF */	cmpwi r4, -1
/* 80088E34 00085A14  41 82 00 48 */	beq lbl_80088E7C
/* 80088E38 00085A18  7F C3 F3 78 */	mr r3, r30
/* 80088E3C 00085A1C  4B F9 D7 89 */	bl func_800265C4
/* 80088E40 00085A20  2C 03 00 01 */	cmpwi r3, 1
/* 80088E44 00085A24  40 82 00 38 */	bne lbl_80088E7C
/* 80088E48 00085A28  88 9D 22 1F */	lbz r4, 0x221f(r29)
/* 80088E4C 00085A2C  3C 60 00 08 */	lis r3, 0x00083D61@ha
/* 80088E50 00085A30  88 1D 00 0C */	lbz r0, 0xc(r29)
/* 80088E54 00085A34  38 63 3D 61 */	addi r3, r3, 0x00083D61@l
/* 80088E58 00085A38  54 84 EF FE */	rlwinm r4, r4, 0x1d, 0x1f, 0x1f
/* 80088E5C 00085A3C  54 00 08 3C */	slwi r0, r0, 1
/* 80088E60 00085A40  7C C0 22 14 */	add r6, r0, r4
/* 80088E64 00085A44  38 80 00 00 */	li r4, 0
/* 80088E68 00085A48  38 A0 00 40 */	li r5, 0x40
/* 80088E6C 00085A4C  38 C6 00 5A */	addi r6, r6, 0x5a
/* 80088E70 00085A50  4B F9 AA 01 */	bl func_80023870
/* 80088E74 00085A54  38 00 FF FF */	li r0, -1
/* 80088E78 00085A58  90 1D 21 58 */	stw r0, 0x2158(r29)
lbl_80088E7C:
/* 80088E7C 00085A5C  80 9D 21 5C */	lwz r4, 0x215c(r29)
/* 80088E80 00085A60  2C 04 FF FF */	cmpwi r4, -1
/* 80088E84 00085A64  41 82 00 48 */	beq lbl_80088ECC
/* 80088E88 00085A68  7F C3 F3 78 */	mr r3, r30
/* 80088E8C 00085A6C  4B F9 D7 39 */	bl func_800265C4
/* 80088E90 00085A70  2C 03 00 01 */	cmpwi r3, 1
/* 80088E94 00085A74  40 82 00 38 */	bne lbl_80088ECC
/* 80088E98 00085A78  88 9D 22 1F */	lbz r4, 0x221f(r29)
/* 80088E9C 00085A7C  3C 60 00 08 */	lis r3, 0x00083D61@ha
/* 80088EA0 00085A80  88 1D 00 0C */	lbz r0, 0xc(r29)
/* 80088EA4 00085A84  38 63 3D 61 */	addi r3, r3, 0x00083D61@l
/* 80088EA8 00085A88  54 84 EF FE */	rlwinm r4, r4, 0x1d, 0x1f, 0x1f
/* 80088EAC 00085A8C  54 00 08 3C */	slwi r0, r0, 1
/* 80088EB0 00085A90  7C C0 22 14 */	add r6, r0, r4
/* 80088EB4 00085A94  38 80 00 00 */	li r4, 0
/* 80088EB8 00085A98  38 A0 00 40 */	li r5, 0x40
/* 80088EBC 00085A9C  38 C6 00 72 */	addi r6, r6, 0x72
/* 80088EC0 00085AA0  4B F9 A9 B1 */	bl func_80023870
/* 80088EC4 00085AA4  38 00 FF FF */	li r0, -1
/* 80088EC8 00085AA8  90 1D 21 5C */	stw r0, 0x215c(r29)
lbl_80088ECC:
/* 80088ECC 00085AAC  88 1D 00 0C */	lbz r0, 0xc(r29)
/* 80088ED0 00085AB0  3F C0 00 08 */	lis r30, 0x00083D61@ha
/* 80088ED4 00085AB4  38 7E 3D 61 */	addi r3, r30, 0x00083D61@l
/* 80088ED8 00085AB8  54 04 08 3C */	slwi r4, r0, 1
/* 80088EDC 00085ABC  38 C4 00 36 */	addi r6, r4, 0x36
/* 80088EE0 00085AC0  38 80 00 00 */	li r4, 0
/* 80088EE4 00085AC4  38 A0 00 40 */	li r5, 0x40
/* 80088EE8 00085AC8  4B F9 A9 89 */	bl func_80023870
/* 80088EEC 00085ACC  88 1D 00 0C */	lbz r0, 0xc(r29)
/* 80088EF0 00085AD0  38 7E 3D 61 */	addi r3, r30, 0x3d61
/* 80088EF4 00085AD4  38 80 00 00 */	li r4, 0
/* 80088EF8 00085AD8  54 05 08 3C */	slwi r5, r0, 1
/* 80088EFC 00085ADC  38 C5 00 37 */	addi r6, r5, 0x37
/* 80088F00 00085AE0  38 A0 00 40 */	li r5, 0x40
/* 80088F04 00085AE4  4B F9 A9 6D */	bl func_80023870
/* 80088F08 00085AE8  3B E0 FF FF */	li r31, -1
/* 80088F0C 00085AEC  93 FD 21 4C */	stw r31, 0x214c(r29)
/* 80088F10 00085AF0  38 7E 3D 61 */	addi r3, r30, 0x3d61
/* 80088F14 00085AF4  38 80 00 00 */	li r4, 0
/* 80088F18 00085AF8  88 1D 00 0C */	lbz r0, 0xc(r29)
/* 80088F1C 00085AFC  38 A0 00 40 */	li r5, 0x40
/* 80088F20 00085B00  54 06 08 3C */	slwi r6, r0, 1
/* 80088F24 00085B04  38 C6 00 1E */	addi r6, r6, 0x1e
/* 80088F28 00085B08  4B F9 A9 49 */	bl func_80023870
/* 80088F2C 00085B0C  88 1D 00 0C */	lbz r0, 0xc(r29)
/* 80088F30 00085B10  38 7E 3D 61 */	addi r3, r30, 0x3d61
/* 80088F34 00085B14  38 80 00 00 */	li r4, 0
/* 80088F38 00085B18  54 05 08 3C */	slwi r5, r0, 1
/* 80088F3C 00085B1C  38 C5 00 1F */	addi r6, r5, 0x1f
/* 80088F40 00085B20  38 A0 00 40 */	li r5, 0x40
/* 80088F44 00085B24  4B F9 A9 2D */	bl func_80023870
/* 80088F48 00085B28  93 FD 21 44 */	stw r31, 0x2144(r29)
/* 80088F4C 00085B2C  38 7E 3D 61 */	addi r3, r30, 0x3d61
/* 80088F50 00085B30  38 80 00 00 */	li r4, 0
/* 80088F54 00085B34  88 1D 00 0C */	lbz r0, 0xc(r29)
/* 80088F58 00085B38  38 A0 00 40 */	li r5, 0x40
/* 80088F5C 00085B3C  54 06 08 3C */	slwi r6, r0, 1
/* 80088F60 00085B40  38 C6 00 2A */	addi r6, r6, 0x2a
/* 80088F64 00085B44  4B F9 A9 0D */	bl func_80023870
/* 80088F68 00085B48  88 1D 00 0C */	lbz r0, 0xc(r29)
/* 80088F6C 00085B4C  38 7E 3D 61 */	addi r3, r30, 0x3d61
/* 80088F70 00085B50  38 80 00 00 */	li r4, 0
/* 80088F74 00085B54  54 05 08 3C */	slwi r5, r0, 1
/* 80088F78 00085B58  38 C5 00 2B */	addi r6, r5, 0x2b
/* 80088F7C 00085B5C  38 A0 00 40 */	li r5, 0x40
/* 80088F80 00085B60  4B F9 A8 F1 */	bl func_80023870
/* 80088F84 00085B64  93 FD 21 48 */	stw r31, 0x2148(r29)
/* 80088F88 00085B68  38 7E 3D 61 */	addi r3, r30, 0x3d61
/* 80088F8C 00085B6C  38 80 00 00 */	li r4, 0
/* 80088F90 00085B70  88 1D 00 0C */	lbz r0, 0xc(r29)
/* 80088F94 00085B74  38 A0 00 40 */	li r5, 0x40
/* 80088F98 00085B78  54 06 08 3C */	slwi r6, r0, 1
/* 80088F9C 00085B7C  38 C6 00 42 */	addi r6, r6, 0x42
/* 80088FA0 00085B80  4B F9 A8 D1 */	bl func_80023870
/* 80088FA4 00085B84  88 1D 00 0C */	lbz r0, 0xc(r29)
/* 80088FA8 00085B88  38 7E 3D 61 */	addi r3, r30, 0x3d61
/* 80088FAC 00085B8C  38 80 00 00 */	li r4, 0
/* 80088FB0 00085B90  54 05 08 3C */	slwi r5, r0, 1
/* 80088FB4 00085B94  38 C5 00 43 */	addi r6, r5, 0x43
/* 80088FB8 00085B98  38 A0 00 40 */	li r5, 0x40
/* 80088FBC 00085B9C  4B F9 A8 B5 */	bl func_80023870
/* 80088FC0 00085BA0  93 FD 21 50 */	stw r31, 0x2150(r29)
/* 80088FC4 00085BA4  38 7E 3D 61 */	addi r3, r30, 0x3d61
/* 80088FC8 00085BA8  38 80 00 00 */	li r4, 0
/* 80088FCC 00085BAC  88 1D 00 0C */	lbz r0, 0xc(r29)
/* 80088FD0 00085BB0  38 A0 00 40 */	li r5, 0x40
/* 80088FD4 00085BB4  54 06 08 3C */	slwi r6, r0, 1
/* 80088FD8 00085BB8  38 C6 00 4E */	addi r6, r6, 0x4e
/* 80088FDC 00085BBC  4B F9 A8 95 */	bl func_80023870
/* 80088FE0 00085BC0  88 1D 00 0C */	lbz r0, 0xc(r29)
/* 80088FE4 00085BC4  38 7E 3D 61 */	addi r3, r30, 0x3d61
/* 80088FE8 00085BC8  38 80 00 00 */	li r4, 0
/* 80088FEC 00085BCC  54 05 08 3C */	slwi r5, r0, 1
/* 80088FF0 00085BD0  38 C5 00 4F */	addi r6, r5, 0x4f
/* 80088FF4 00085BD4  38 A0 00 40 */	li r5, 0x40
/* 80088FF8 00085BD8  4B F9 A8 79 */	bl func_80023870
/* 80088FFC 00085BDC  93 FD 21 54 */	stw r31, 0x2154(r29)
/* 80089000 00085BE0  38 7E 3D 61 */	addi r3, r30, 0x3d61
/* 80089004 00085BE4  38 80 00 00 */	li r4, 0
/* 80089008 00085BE8  88 1D 00 0C */	lbz r0, 0xc(r29)
/* 8008900C 00085BEC  38 A0 00 40 */	li r5, 0x40
/* 80089010 00085BF0  54 06 08 3C */	slwi r6, r0, 1
/* 80089014 00085BF4  38 C6 00 5A */	addi r6, r6, 0x5a
/* 80089018 00085BF8  4B F9 A8 59 */	bl func_80023870
/* 8008901C 00085BFC  88 1D 00 0C */	lbz r0, 0xc(r29)
/* 80089020 00085C00  38 7E 3D 61 */	addi r3, r30, 0x3d61
/* 80089024 00085C04  38 80 00 00 */	li r4, 0
/* 80089028 00085C08  54 05 08 3C */	slwi r5, r0, 1
/* 8008902C 00085C0C  38 C5 00 5B */	addi r6, r5, 0x5b
/* 80089030 00085C10  38 A0 00 40 */	li r5, 0x40
/* 80089034 00085C14  4B F9 A8 3D */	bl func_80023870
/* 80089038 00085C18  93 FD 21 58 */	stw r31, 0x2158(r29)
/* 8008903C 00085C1C  38 7E 3D 61 */	addi r3, r30, 0x3d61
/* 80089040 00085C20  38 80 00 00 */	li r4, 0
/* 80089044 00085C24  88 1D 00 0C */	lbz r0, 0xc(r29)
/* 80089048 00085C28  38 A0 00 40 */	li r5, 0x40
/* 8008904C 00085C2C  54 06 08 3C */	slwi r6, r0, 1
/* 80089050 00085C30  38 C6 00 72 */	addi r6, r6, 0x72
/* 80089054 00085C34  4B F9 A8 1D */	bl func_80023870
/* 80089058 00085C38  88 1D 00 0C */	lbz r0, 0xc(r29)
/* 8008905C 00085C3C  38 7E 3D 61 */	addi r3, r30, 0x3d61
/* 80089060 00085C40  38 80 00 00 */	li r4, 0
/* 80089064 00085C44  54 05 08 3C */	slwi r5, r0, 1
/* 80089068 00085C48  38 C5 00 73 */	addi r6, r5, 0x73
/* 8008906C 00085C4C  38 A0 00 40 */	li r5, 0x40
/* 80089070 00085C50  4B F9 A8 01 */	bl func_80023870
/* 80089074 00085C54  93 FD 21 5C */	stw r31, 0x215c(r29)
/* 80089078 00085C58  93 FD 21 60 */	stw r31, 0x2160(r29)
/* 8008907C 00085C5C  80 7D 21 64 */	lwz r3, 0x2164(r29)
/* 80089080 00085C60  4B F9 BF 8D */	bl func_8002500C
/* 80089084 00085C64  3B C0 00 00 */	li r30, 0
/* 80089088 00085C68  93 DD 21 64 */	stw r30, 0x2164(r29)
/* 8008908C 00085C6C  80 7D 21 68 */	lwz r3, 0x2168(r29)
/* 80089090 00085C70  4B F9 BF A9 */	bl func_80025038
/* 80089094 00085C74  93 DD 21 68 */	stw r30, 0x2168(r29)
/* 80089098 00085C78  93 DD 21 68 */	stw r30, 0x2168(r29)
/* 8008909C 00085C7C  93 DD 21 64 */	stw r30, 0x2164(r29)
/* 800890A0 00085C80  80 01 00 24 */	lwz r0, 0x24(r1)
/* 800890A4 00085C84  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 800890A8 00085C88  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 800890AC 00085C8C  83 A1 00 14 */	lwz r29, 0x14(r1)
/* 800890B0 00085C90  38 21 00 20 */	addi r1, r1, 0x20
/* 800890B4 00085C94  7C 08 03 A6 */	mtlr r0
/* 800890B8 00085C98  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

#pragma push
asm void func_800890BC(Fighter* fp)
{ // clang-format off
    nofralloc
/* 800890BC 00085C9C  38 00 00 01 */	li r0, 1
/* 800890C0 00085CA0  90 03 20 68 */	stw r0, 0x2068(r3)
/* 800890C4 00085CA4  38 00 00 00 */	li r0, 0
/* 800890C8 00085CA8  B0 03 20 6C */	sth r0, 0x206c(r3)
/* 800890CC 00085CAC  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

extern unk_t func_80037208();

#pragma push
asm void func_800890D0(Fighter* fp, u8 move_id)
{ // clang-format off
    nofralloc
/* 800890D0 00085CB0  7C 08 02 A6 */	mflr r0
/* 800890D4 00085CB4  28 04 00 01 */	cmplwi r4, 1
/* 800890D8 00085CB8  90 01 00 04 */	stw r0, 4(r1)
/* 800890DC 00085CBC  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 800890E0 00085CC0  93 E1 00 14 */	stw r31, 0x14(r1)
/* 800890E4 00085CC4  3B E3 00 00 */	addi r31, r3, 0
/* 800890E8 00085CC8  41 82 00 10 */	beq lbl_800890F8
/* 800890EC 00085CCC  80 1F 20 68 */	lwz r0, 0x2068(r31)
/* 800890F0 00085CD0  7C 04 00 40 */	cmplw r4, r0
/* 800890F4 00085CD4  41 82 00 10 */	beq lbl_80089104
lbl_800890F8:
/* 800890F8 00085CD8  90 9F 20 68 */	stw r4, 0x2068(r31)
/* 800890FC 00085CDC  4B FA E1 0D */	bl func_80037208
/* 80089100 00085CE0  B0 7F 20 6C */	sth r3, 0x206c(r31)
lbl_80089104:
/* 80089104 00085CE4  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 80089108 00085CE8  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 8008910C 00085CEC  38 21 00 18 */	addi r1, r1, 0x18
/* 80089110 00085CF0  7C 08 03 A6 */	mtlr r0
/* 80089114 00085CF4  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

extern f32 const lbl_804D83E0;

#pragma push
asm unk_t func_80089118()
{ // clang-format off
    nofralloc
/* 80089118 00085CF8  80 A3 00 00 */	lwz r5, 0(r3)
/* 8008911C 00085CFC  C0 22 8A 00 */	lfs f1, lbl_804D83E0(r2)
/* 80089120 00085D00  2C 05 00 00 */	cmpwi r5, 0
/* 80089124 00085D04  41 82 00 0C */	beq lbl_80089130
/* 80089128 00085D08  38 05 FF FF */	addi r0, r5, -1
/* 8008912C 00085D0C  48 00 00 08 */	b lbl_80089134
lbl_80089130:
/* 80089130 00085D10  38 00 00 09 */	li r0, 9
lbl_80089134:
/* 80089134 00085D14  2C 04 00 01 */	cmpwi r4, 1
/* 80089138 00085D18  7C 08 03 78 */	mr r8, r0
/* 8008913C 00085D1C  40 82 00 0C */	bne lbl_80089148
/* 80089140 00085D20  C0 22 8A 00 */	lfs f1, lbl_804D83E0(r2)
/* 80089144 00085D24  4E 80 00 20 */	blr 
lbl_80089148:
/* 80089148 00085D28  38 00 00 03 */	li r0, 3
/* 8008914C 00085D2C  80 CD AE A8 */	lwz r6, lbl_804D6548(r13)
/* 80089150 00085D30  7C 09 03 A6 */	mtctr r0
/* 80089154 00085D34  38 E0 00 00 */	li r7, 0
lbl_80089158:
/* 80089158 00085D38  55 05 10 3A */	slwi r5, r8, 2
/* 8008915C 00085D3C  38 05 00 04 */	addi r0, r5, 4
/* 80089160 00085D40  7C 03 02 2E */	lhzx r0, r3, r0
/* 80089164 00085D44  28 00 00 00 */	cmplwi r0, 0
/* 80089168 00085D48  4D 82 00 20 */	beqlr 
/* 8008916C 00085D4C  7C 04 00 00 */	cmpw r4, r0
/* 80089170 00085D50  40 82 00 0C */	bne lbl_8008917C
/* 80089174 00085D54  C0 06 00 00 */	lfs f0, 0(r6)
/* 80089178 00085D58  EC 21 00 28 */	fsubs f1, f1, f0
lbl_8008917C:
/* 8008917C 00085D5C  2C 08 00 00 */	cmpwi r8, 0
/* 80089180 00085D60  41 82 00 0C */	beq lbl_8008918C
/* 80089184 00085D64  38 08 FF FF */	addi r0, r8, -1
/* 80089188 00085D68  48 00 00 08 */	b lbl_80089190
lbl_8008918C:
/* 8008918C 00085D6C  38 00 00 09 */	li r0, 9
lbl_80089190:
/* 80089190 00085D70  54 05 10 3A */	slwi r5, r0, 2
/* 80089194 00085D74  7C 08 03 78 */	mr r8, r0
/* 80089198 00085D78  38 05 00 04 */	addi r0, r5, 4
/* 8008919C 00085D7C  7C 03 02 2E */	lhzx r0, r3, r0
/* 800891A0 00085D80  38 C6 00 04 */	addi r6, r6, 4
/* 800891A4 00085D84  28 00 00 00 */	cmplwi r0, 0
/* 800891A8 00085D88  4D 82 00 20 */	beqlr 
/* 800891AC 00085D8C  7C 04 00 00 */	cmpw r4, r0
/* 800891B0 00085D90  40 82 00 0C */	bne lbl_800891BC
/* 800891B4 00085D94  C0 06 00 00 */	lfs f0, 0(r6)
/* 800891B8 00085D98  EC 21 00 28 */	fsubs f1, f1, f0
lbl_800891BC:
/* 800891BC 00085D9C  2C 08 00 00 */	cmpwi r8, 0
/* 800891C0 00085DA0  41 82 00 0C */	beq lbl_800891CC
/* 800891C4 00085DA4  38 08 FF FF */	addi r0, r8, -1
/* 800891C8 00085DA8  48 00 00 08 */	b lbl_800891D0
lbl_800891CC:
/* 800891CC 00085DAC  38 00 00 09 */	li r0, 9
lbl_800891D0:
/* 800891D0 00085DB0  54 05 10 3A */	slwi r5, r0, 2
/* 800891D4 00085DB4  7C 08 03 78 */	mr r8, r0
/* 800891D8 00085DB8  38 05 00 04 */	addi r0, r5, 4
/* 800891DC 00085DBC  7C 03 02 2E */	lhzx r0, r3, r0
/* 800891E0 00085DC0  38 C6 00 04 */	addi r6, r6, 4
/* 800891E4 00085DC4  38 E7 00 01 */	addi r7, r7, 1
/* 800891E8 00085DC8  28 00 00 00 */	cmplwi r0, 0
/* 800891EC 00085DCC  4D 82 00 20 */	beqlr 
/* 800891F0 00085DD0  7C 04 00 00 */	cmpw r4, r0
/* 800891F4 00085DD4  40 82 00 0C */	bne lbl_80089200
/* 800891F8 00085DD8  C0 06 00 00 */	lfs f0, 0(r6)
/* 800891FC 00085DDC  EC 21 00 28 */	fsubs f1, f1, f0
lbl_80089200:
/* 80089200 00085DE0  2C 08 00 00 */	cmpwi r8, 0
/* 80089204 00085DE4  41 82 00 0C */	beq lbl_80089210
/* 80089208 00085DE8  38 08 FF FF */	addi r0, r8, -1
/* 8008920C 00085DEC  48 00 00 08 */	b lbl_80089214
lbl_80089210:
/* 80089210 00085DF0  38 00 00 09 */	li r0, 9
lbl_80089214:
/* 80089214 00085DF4  7C 08 03 78 */	mr r8, r0
/* 80089218 00085DF8  38 C6 00 04 */	addi r6, r6, 4
/* 8008921C 00085DFC  38 E7 00 01 */	addi r7, r7, 1
/* 80089220 00085E00  42 00 FF 38 */	bdnz lbl_80089158
/* 80089224 00085E04  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

#pragma push
asm unk_t func_80089228()
{ // clang-format off
    nofralloc
/* 80089228 00085E08  7C 08 02 A6 */	mflr r0
/* 8008922C 00085E0C  90 01 00 04 */	stw r0, 4(r1)
/* 80089230 00085E10  94 21 FF D8 */	stwu r1, -0x28(r1)
/* 80089234 00085E14  DB E1 00 20 */	stfd f31, 0x20(r1)
/* 80089238 00085E18  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 8008923C 00085E1C  3B E5 00 00 */	addi r31, r5, 0
/* 80089240 00085E20  93 C1 00 18 */	stw r30, 0x18(r1)
/* 80089244 00085E24  3B C4 00 00 */	addi r30, r4, 0
/* 80089248 00085E28  80 0D 93 68 */	lwz r0, g_debugLevel(r13)
/* 8008924C 00085E2C  2C 00 00 03 */	cmpwi r0, 3
/* 80089250 00085E30  41 80 00 08 */	blt lbl_80089258
/* 80089254 00085E34  48 00 00 30 */	b lbl_80089284
lbl_80089258:
/* 80089258 00085E38  FF E0 08 90 */	fmr f31, f1
/* 8008925C 00085E3C  88 63 00 0C */	lbz r3, 0xc(r3)
/* 80089260 00085E40  4B FA CF E5 */	bl Player_GetStaleMoveTableIndexPtr
/* 80089264 00085E44  38 9E 00 00 */	addi r4, r30, 0
/* 80089268 00085E48  38 BF 00 00 */	addi r5, r31, 0
/* 8008926C 00085E4C  4B FF FE AD */	bl func_80089118
/* 80089270 00085E50  C0 02 8A 00 */	lfs f0, lbl_804D83E0(r2)
/* 80089274 00085E54  FC 00 08 00 */	fcmpu cr0, f0, f1
/* 80089278 00085E58  41 82 00 08 */	beq lbl_80089280
/* 8008927C 00085E5C  EF FF 00 72 */	fmuls f31, f31, f1
lbl_80089280:
/* 80089280 00085E60  FC 20 F8 90 */	fmr f1, f31
lbl_80089284:
/* 80089284 00085E64  80 01 00 2C */	lwz r0, 0x2c(r1)
/* 80089288 00085E68  CB E1 00 20 */	lfd f31, 0x20(r1)
/* 8008928C 00085E6C  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 80089290 00085E70  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 80089294 00085E74  38 21 00 28 */	addi r1, r1, 0x28
/* 80089298 00085E78  7C 08 03 A6 */	mtlr r0
/* 8008929C 00085E7C  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

#pragma push
asm void func_800892A0(HSD_GObj* fighter_gobj)
{ // clang-format off
    nofralloc
/* 800892A0 00085E80  7C 08 02 A6 */	mflr r0
/* 800892A4 00085E84  90 01 00 04 */	stw r0, 4(r1)
/* 800892A8 00085E88  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 800892AC 00085E8C  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 800892B0 00085E90  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 800892B4 00085E94  80 1F 20 68 */	lwz r0, 0x2068(r31)
/* 800892B8 00085E98  4B FA DF 51 */	bl func_80037208
/* 800892BC 00085E9C  B0 7F 20 6C */	sth r3, 0x206c(r31)
/* 800892C0 00085EA0  80 01 00 24 */	lwz r0, 0x24(r1)
/* 800892C4 00085EA4  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 800892C8 00085EA8  38 21 00 20 */	addi r1, r1, 0x20
/* 800892CC 00085EAC  7C 08 03 A6 */	mtlr r0
/* 800892D0 00085EB0  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

extern f32 const lbl_804D83E8;

#pragma push
asm void func_800892D4(Fighter* fp)
{ // clang-format off
    nofralloc
/* 800892D4 00085EB4  94 21 FF F0 */	stwu r1, -0x10(r1)
/* 800892D8 00085EB8  38 00 00 00 */	li r0, 0
/* 800892DC 00085EBC  38 A0 00 06 */	li r5, 6
/* 800892E0 00085EC0  90 01 00 0C */	stw r0, 0xc(r1)
/* 800892E4 00085EC4  80 81 00 0C */	lwz r4, 0xc(r1)
/* 800892E8 00085EC8  90 83 18 D4 */	stw r4, 0x18d4(r3)
/* 800892EC 00085ECC  80 83 18 D4 */	lwz r4, 0x18d4(r3)
/* 800892F0 00085ED0  90 83 20 70 */	stw r4, 0x2070(r3)
/* 800892F4 00085ED4  90 03 20 74 */	stw r0, 0x2074(r3)
/* 800892F8 00085ED8  90 03 20 78 */	stw r0, 0x2078(r3)
/* 800892FC 00085EDC  C0 02 8A 08 */	lfs f0, lbl_804D83E8(r2)
/* 80089300 00085EE0  D0 03 20 7C */	stfs f0, 0x207c(r3)
/* 80089304 00085EE4  90 A3 20 80 */	stw r5, 0x2080(r3)
/* 80089308 00085EE8  88 83 20 84 */	lbz r4, 0x2084(r3)
/* 8008930C 00085EEC  50 04 3E 30 */	rlwimi r4, r0, 7, 0x18, 0x18
/* 80089310 00085EF0  98 83 20 84 */	stb r4, 0x2084(r3)
/* 80089314 00085EF4  88 83 20 85 */	lbz r4, 0x2085(r3)
/* 80089318 00085EF8  50 04 26 F6 */	rlwimi r4, r0, 4, 0x1b, 0x1b
/* 8008931C 00085EFC  98 83 20 85 */	stb r4, 0x2085(r3)
/* 80089320 00085F00  88 83 20 84 */	lbz r4, 0x2084(r3)
/* 80089324 00085F04  50 04 36 72 */	rlwimi r4, r0, 6, 0x19, 0x19
/* 80089328 00085F08  98 83 20 84 */	stb r4, 0x2084(r3)
/* 8008932C 00085F0C  88 83 20 84 */	lbz r4, 0x2084(r3)
/* 80089330 00085F10  50 04 2E B4 */	rlwimi r4, r0, 5, 0x1a, 0x1a
/* 80089334 00085F14  98 83 20 84 */	stb r4, 0x2084(r3)
/* 80089338 00085F18  88 83 20 84 */	lbz r4, 0x2084(r3)
/* 8008933C 00085F1C  50 04 26 F6 */	rlwimi r4, r0, 4, 0x1b, 0x1b
/* 80089340 00085F20  98 83 20 84 */	stb r4, 0x2084(r3)
/* 80089344 00085F24  88 83 20 84 */	lbz r4, 0x2084(r3)
/* 80089348 00085F28  50 04 1F 38 */	rlwimi r4, r0, 3, 0x1c, 0x1c
/* 8008934C 00085F2C  98 83 20 84 */	stb r4, 0x2084(r3)
/* 80089350 00085F30  88 83 20 84 */	lbz r4, 0x2084(r3)
/* 80089354 00085F34  50 04 17 7A */	rlwimi r4, r0, 2, 0x1d, 0x1d
/* 80089358 00085F38  98 83 20 84 */	stb r4, 0x2084(r3)
/* 8008935C 00085F3C  88 83 20 84 */	lbz r4, 0x2084(r3)
/* 80089360 00085F40  50 04 0F BC */	rlwimi r4, r0, 1, 0x1e, 0x1e
/* 80089364 00085F44  98 83 20 84 */	stb r4, 0x2084(r3)
/* 80089368 00085F48  88 83 20 84 */	lbz r4, 0x2084(r3)
/* 8008936C 00085F4C  50 04 07 FE */	rlwimi r4, r0, 0, 0x1f, 0x1f
/* 80089370 00085F50  98 83 20 84 */	stb r4, 0x2084(r3)
/* 80089374 00085F54  88 83 20 85 */	lbz r4, 0x2085(r3)
/* 80089378 00085F58  50 04 3E 30 */	rlwimi r4, r0, 7, 0x18, 0x18
/* 8008937C 00085F5C  98 83 20 85 */	stb r4, 0x2085(r3)
/* 80089380 00085F60  88 83 20 85 */	lbz r4, 0x2085(r3)
/* 80089384 00085F64  50 04 36 72 */	rlwimi r4, r0, 6, 0x19, 0x19
/* 80089388 00085F68  98 83 20 85 */	stb r4, 0x2085(r3)
/* 8008938C 00085F6C  88 83 20 85 */	lbz r4, 0x2085(r3)
/* 80089390 00085F70  50 04 2E B4 */	rlwimi r4, r0, 5, 0x1a, 0x1a
/* 80089394 00085F74  98 83 20 85 */	stb r4, 0x2085(r3)
/* 80089398 00085F78  88 83 20 85 */	lbz r4, 0x2085(r3)
/* 8008939C 00085F7C  50 04 1F 38 */	rlwimi r4, r0, 3, 0x1c, 0x1c
/* 800893A0 00085F80  98 83 20 85 */	stb r4, 0x2085(r3)
/* 800893A4 00085F84  90 03 18 D8 */	stw r0, 0x18d8(r3)
/* 800893A8 00085F88  90 03 18 DC */	stw r0, 0x18dc(r3)
/* 800893AC 00085F8C  D0 03 18 E0 */	stfs f0, 0x18e0(r3)
/* 800893B0 00085F90  90 A3 18 E4 */	stw r5, 0x18e4(r3)
/* 800893B4 00085F94  88 83 18 E8 */	lbz r4, 0x18e8(r3)
/* 800893B8 00085F98  50 04 3E 30 */	rlwimi r4, r0, 7, 0x18, 0x18
/* 800893BC 00085F9C  98 83 18 E8 */	stb r4, 0x18e8(r3)
/* 800893C0 00085FA0  88 83 18 E9 */	lbz r4, 0x18e9(r3)
/* 800893C4 00085FA4  50 04 26 F6 */	rlwimi r4, r0, 4, 0x1b, 0x1b
/* 800893C8 00085FA8  98 83 18 E9 */	stb r4, 0x18e9(r3)
/* 800893CC 00085FAC  88 83 18 E8 */	lbz r4, 0x18e8(r3)
/* 800893D0 00085FB0  50 04 36 72 */	rlwimi r4, r0, 6, 0x19, 0x19
/* 800893D4 00085FB4  98 83 18 E8 */	stb r4, 0x18e8(r3)
/* 800893D8 00085FB8  88 83 18 E8 */	lbz r4, 0x18e8(r3)
/* 800893DC 00085FBC  50 04 2E B4 */	rlwimi r4, r0, 5, 0x1a, 0x1a
/* 800893E0 00085FC0  98 83 18 E8 */	stb r4, 0x18e8(r3)
/* 800893E4 00085FC4  88 83 18 E8 */	lbz r4, 0x18e8(r3)
/* 800893E8 00085FC8  50 04 26 F6 */	rlwimi r4, r0, 4, 0x1b, 0x1b
/* 800893EC 00085FCC  98 83 18 E8 */	stb r4, 0x18e8(r3)
/* 800893F0 00085FD0  88 83 18 E8 */	lbz r4, 0x18e8(r3)
/* 800893F4 00085FD4  50 04 1F 38 */	rlwimi r4, r0, 3, 0x1c, 0x1c
/* 800893F8 00085FD8  98 83 18 E8 */	stb r4, 0x18e8(r3)
/* 800893FC 00085FDC  88 83 18 E8 */	lbz r4, 0x18e8(r3)
/* 80089400 00085FE0  50 04 17 7A */	rlwimi r4, r0, 2, 0x1d, 0x1d
/* 80089404 00085FE4  98 83 18 E8 */	stb r4, 0x18e8(r3)
/* 80089408 00085FE8  88 83 18 E8 */	lbz r4, 0x18e8(r3)
/* 8008940C 00085FEC  50 04 0F BC */	rlwimi r4, r0, 1, 0x1e, 0x1e
/* 80089410 00085FF0  98 83 18 E8 */	stb r4, 0x18e8(r3)
/* 80089414 00085FF4  88 83 18 E8 */	lbz r4, 0x18e8(r3)
/* 80089418 00085FF8  50 04 07 FE */	rlwimi r4, r0, 0, 0x1f, 0x1f
/* 8008941C 00085FFC  98 83 18 E8 */	stb r4, 0x18e8(r3)
/* 80089420 00086000  88 83 18 E9 */	lbz r4, 0x18e9(r3)
/* 80089424 00086004  50 04 3E 30 */	rlwimi r4, r0, 7, 0x18, 0x18
/* 80089428 00086008  98 83 18 E9 */	stb r4, 0x18e9(r3)
/* 8008942C 0008600C  88 83 18 E9 */	lbz r4, 0x18e9(r3)
/* 80089430 00086010  50 04 36 72 */	rlwimi r4, r0, 6, 0x19, 0x19
/* 80089434 00086014  98 83 18 E9 */	stb r4, 0x18e9(r3)
/* 80089438 00086018  88 83 18 E9 */	lbz r4, 0x18e9(r3)
/* 8008943C 0008601C  50 04 2E B4 */	rlwimi r4, r0, 5, 0x1a, 0x1a
/* 80089440 00086020  98 83 18 E9 */	stb r4, 0x18e9(r3)
/* 80089444 00086024  88 83 18 E9 */	lbz r4, 0x18e9(r3)
/* 80089448 00086028  50 04 1F 38 */	rlwimi r4, r0, 3, 0x1c, 0x1c
/* 8008944C 0008602C  98 83 18 E9 */	stb r4, 0x18e9(r3)
/* 80089450 00086030  B0 03 18 EC */	sth r0, 0x18ec(r3)
/* 80089454 00086034  B0 03 20 88 */	sth r0, 0x2088(r3)
/* 80089458 00086038  38 21 00 10 */	addi r1, r1, 0x10
/* 8008945C 0008603C  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

#pragma push
asm unk_t func_80089460()
{ // clang-format off
    nofralloc
/* 80089460 00086040  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 80089464 00086044  38 80 00 00 */	li r4, 0
/* 80089468 00086048  38 00 00 06 */	li r0, 6
/* 8008946C 0008604C  90 83 20 74 */	stw r4, 0x2074(r3)
/* 80089470 00086050  90 83 20 78 */	stw r4, 0x2078(r3)
/* 80089474 00086054  C0 02 8A 08 */	lfs f0, lbl_804D83E8(r2)
/* 80089478 00086058  D0 03 20 7C */	stfs f0, 0x207c(r3)
/* 8008947C 0008605C  90 03 20 80 */	stw r0, 0x2080(r3)
/* 80089480 00086060  88 03 20 84 */	lbz r0, 0x2084(r3)
/* 80089484 00086064  50 80 3E 30 */	rlwimi r0, r4, 7, 0x18, 0x18
/* 80089488 00086068  98 03 20 84 */	stb r0, 0x2084(r3)
/* 8008948C 0008606C  88 03 20 85 */	lbz r0, 0x2085(r3)
/* 80089490 00086070  50 80 26 F6 */	rlwimi r0, r4, 4, 0x1b, 0x1b
/* 80089494 00086074  98 03 20 85 */	stb r0, 0x2085(r3)
/* 80089498 00086078  88 03 20 84 */	lbz r0, 0x2084(r3)
/* 8008949C 0008607C  50 80 36 72 */	rlwimi r0, r4, 6, 0x19, 0x19
/* 800894A0 00086080  98 03 20 84 */	stb r0, 0x2084(r3)
/* 800894A4 00086084  88 03 20 84 */	lbz r0, 0x2084(r3)
/* 800894A8 00086088  50 80 2E B4 */	rlwimi r0, r4, 5, 0x1a, 0x1a
/* 800894AC 0008608C  98 03 20 84 */	stb r0, 0x2084(r3)
/* 800894B0 00086090  88 03 20 84 */	lbz r0, 0x2084(r3)
/* 800894B4 00086094  50 80 26 F6 */	rlwimi r0, r4, 4, 0x1b, 0x1b
/* 800894B8 00086098  98 03 20 84 */	stb r0, 0x2084(r3)
/* 800894BC 0008609C  88 03 20 84 */	lbz r0, 0x2084(r3)
/* 800894C0 000860A0  50 80 1F 38 */	rlwimi r0, r4, 3, 0x1c, 0x1c
/* 800894C4 000860A4  98 03 20 84 */	stb r0, 0x2084(r3)
/* 800894C8 000860A8  88 03 20 84 */	lbz r0, 0x2084(r3)
/* 800894CC 000860AC  50 80 17 7A */	rlwimi r0, r4, 2, 0x1d, 0x1d
/* 800894D0 000860B0  98 03 20 84 */	stb r0, 0x2084(r3)
/* 800894D4 000860B4  88 03 20 84 */	lbz r0, 0x2084(r3)
/* 800894D8 000860B8  50 80 0F BC */	rlwimi r0, r4, 1, 0x1e, 0x1e
/* 800894DC 000860BC  98 03 20 84 */	stb r0, 0x2084(r3)
/* 800894E0 000860C0  88 03 20 84 */	lbz r0, 0x2084(r3)
/* 800894E4 000860C4  50 80 07 FE */	rlwimi r0, r4, 0, 0x1f, 0x1f
/* 800894E8 000860C8  98 03 20 84 */	stb r0, 0x2084(r3)
/* 800894EC 000860CC  88 03 20 85 */	lbz r0, 0x2085(r3)
/* 800894F0 000860D0  50 80 3E 30 */	rlwimi r0, r4, 7, 0x18, 0x18
/* 800894F4 000860D4  98 03 20 85 */	stb r0, 0x2085(r3)
/* 800894F8 000860D8  88 03 20 85 */	lbz r0, 0x2085(r3)
/* 800894FC 000860DC  50 80 36 72 */	rlwimi r0, r4, 6, 0x19, 0x19
/* 80089500 000860E0  98 03 20 85 */	stb r0, 0x2085(r3)
/* 80089504 000860E4  88 03 20 85 */	lbz r0, 0x2085(r3)
/* 80089508 000860E8  50 80 2E B4 */	rlwimi r0, r4, 5, 0x1a, 0x1a
/* 8008950C 000860EC  98 03 20 85 */	stb r0, 0x2085(r3)
/* 80089510 000860F0  88 03 20 85 */	lbz r0, 0x2085(r3)
/* 80089514 000860F4  50 80 1F 38 */	rlwimi r0, r4, 3, 0x1c, 0x1c
/* 80089518 000860F8  98 03 20 85 */	stb r0, 0x2085(r3)
/* 8008951C 000860FC  C0 03 18 30 */	lfs f0, 0x1830(r3)
/* 80089520 00086100  FC 00 00 1E */	fctiwz f0, f0
/* 80089524 00086104  D8 01 00 10 */	stfd f0, 0x10(r1)
/* 80089528 00086108  80 01 00 14 */	lwz r0, 0x14(r1)
/* 8008952C 0008610C  90 03 20 74 */	stw r0, 0x2074(r3)
/* 80089530 00086110  88 03 22 23 */	lbz r0, 0x2223(r3)
/* 80089534 00086114  54 00 07 FF */	clrlwi. r0, r0, 0x1f
/* 80089538 00086118  41 82 00 14 */	beq lbl_8008954C
/* 8008953C 0008611C  88 03 20 84 */	lbz r0, 0x2084(r3)
/* 80089540 00086120  38 80 00 01 */	li r4, 1
/* 80089544 00086124  50 80 36 72 */	rlwimi r0, r4, 6, 0x19, 0x19
/* 80089548 00086128  98 03 20 84 */	stb r0, 0x2084(r3)
lbl_8008954C:
/* 8008954C 0008612C  80 03 19 7C */	lwz r0, 0x197c(r3)
/* 80089550 00086130  28 00 00 00 */	cmplwi r0, 0
/* 80089554 00086134  41 82 00 14 */	beq lbl_80089568
/* 80089558 00086138  88 03 20 84 */	lbz r0, 0x2084(r3)
/* 8008955C 0008613C  38 80 00 01 */	li r4, 1
/* 80089560 00086140  50 80 2E B4 */	rlwimi r0, r4, 5, 0x1a, 0x1a
/* 80089564 00086144  98 03 20 84 */	stb r0, 0x2084(r3)
lbl_80089568:
/* 80089568 00086148  88 03 22 1D */	lbz r0, 0x221d(r3)
/* 8008956C 0008614C  54 00 FF FF */	rlwinm. r0, r0, 0x1f, 0x1f, 0x1f
/* 80089570 00086150  41 82 00 14 */	beq lbl_80089584
/* 80089574 00086154  88 03 20 84 */	lbz r0, 0x2084(r3)
/* 80089578 00086158  38 80 00 01 */	li r4, 1
/* 8008957C 0008615C  50 80 26 F6 */	rlwimi r0, r4, 4, 0x1b, 0x1b
/* 80089580 00086160  98 03 20 84 */	stb r0, 0x2084(r3)
lbl_80089584:
/* 80089584 00086164  88 03 22 26 */	lbz r0, 0x2226(r3)
/* 80089588 00086168  54 00 EF FF */	rlwinm. r0, r0, 0x1d, 0x1f, 0x1f
/* 8008958C 0008616C  41 82 00 14 */	beq lbl_800895A0
/* 80089590 00086170  88 03 20 84 */	lbz r0, 0x2084(r3)
/* 80089594 00086174  38 80 00 01 */	li r4, 1
/* 80089598 00086178  50 80 1F 38 */	rlwimi r0, r4, 3, 0x1c, 0x1c
/* 8008959C 0008617C  98 03 20 84 */	stb r0, 0x2084(r3)
lbl_800895A0:
/* 800895A0 00086180  88 03 22 20 */	lbz r0, 0x2220(r3)
/* 800895A4 00086184  54 00 F7 FF */	rlwinm. r0, r0, 0x1e, 0x1f, 0x1f
/* 800895A8 00086188  41 82 00 14 */	beq lbl_800895BC
/* 800895AC 0008618C  88 03 20 84 */	lbz r0, 0x2084(r3)
/* 800895B0 00086190  38 80 00 01 */	li r4, 1
/* 800895B4 00086194  50 80 17 7A */	rlwimi r0, r4, 2, 0x1d, 0x1d
/* 800895B8 00086198  98 03 20 84 */	stb r0, 0x2084(r3)
lbl_800895BC:
/* 800895BC 0008619C  88 03 22 20 */	lbz r0, 0x2220(r3)
/* 800895C0 000861A0  54 00 FF FF */	rlwinm. r0, r0, 0x1f, 0x1f, 0x1f
/* 800895C4 000861A4  41 82 00 14 */	beq lbl_800895D8
/* 800895C8 000861A8  88 03 20 84 */	lbz r0, 0x2084(r3)
/* 800895CC 000861AC  38 80 00 01 */	li r4, 1
/* 800895D0 000861B0  50 80 0F BC */	rlwimi r0, r4, 1, 0x1e, 0x1e
/* 800895D4 000861B4  98 03 20 84 */	stb r0, 0x2084(r3)
lbl_800895D8:
/* 800895D8 000861B8  38 21 00 18 */	addi r1, r1, 0x18
/* 800895DC 000861BC  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

extern unk_t func_80089768();
extern unk_t func_80037B08();

#pragma push
asm void func_800895E0(Fighter* fp, s32 flags)
{ // clang-format off
    nofralloc
/* 800895E0 000861C0  7C 08 02 A6 */	mflr r0
/* 800895E4 000861C4  90 01 00 04 */	stw r0, 4(r1)
/* 800895E8 000861C8  94 21 FF D0 */	stwu r1, -0x30(r1)
/* 800895EC 000861CC  93 E1 00 2C */	stw r31, 0x2c(r1)
/* 800895F0 000861D0  7C 7F 1B 78 */	mr r31, r3
/* 800895F4 000861D4  93 C1 00 28 */	stw r30, 0x28(r1)
/* 800895F8 000861D8  90 81 00 0C */	stw r4, 0xc(r1)
/* 800895FC 000861DC  80 01 00 0C */	lwz r0, 0xc(r1)
/* 80089600 000861E0  90 01 00 1C */	stw r0, 0x1c(r1)
/* 80089604 000861E4  8B C1 00 1F */	lbz r30, 0x1f(r1)
/* 80089608 000861E8  28 1E 00 00 */	cmplwi r30, 0
/* 8008960C 000861EC  41 82 00 10 */	beq lbl_8008961C
/* 80089610 000861F0  88 1F 20 73 */	lbz r0, 0x2073(r31)
/* 80089614 000861F4  7C 1E 00 40 */	cmplw r30, r0
/* 80089618 000861F8  41 82 00 0C */	beq lbl_80089624
lbl_8008961C:
/* 8008961C 000861FC  4B FA E4 ED */	bl func_80037B08
/* 80089620 00086200  B0 7F 20 88 */	sth r3, 0x2088(r31)
lbl_80089624:
/* 80089624 00086204  80 1F 00 04 */	lwz r0, 4(r31)
/* 80089628 00086208  2C 00 00 11 */	cmpwi r0, 0x11
/* 8008962C 0008620C  40 82 00 20 */	bne lbl_8008964C
/* 80089630 00086210  28 1E 00 71 */	cmplwi r30, 0x71
/* 80089634 00086214  40 82 00 18 */	bne lbl_8008964C
/* 80089638 00086218  3C 60 00 24 */	lis r3, 0x00240063@ha
/* 8008963C 0008621C  38 03 00 63 */	addi r0, r3, 0x00240063@l
/* 80089640 00086220  90 01 00 18 */	stw r0, 0x18(r1)
/* 80089644 00086224  80 01 00 18 */	lwz r0, 0x18(r1)
/* 80089648 00086228  90 01 00 1C */	stw r0, 0x1c(r1)
lbl_8008964C:
/* 8008964C 0008622C  88 01 00 1F */	lbz r0, 0x1f(r1)
/* 80089650 00086230  28 00 00 62 */	cmplwi r0, 0x62
/* 80089654 00086234  40 82 00 30 */	bne lbl_80089684
/* 80089658 00086238  80 7F 19 74 */	lwz r3, 0x1974(r31)
/* 8008965C 0008623C  28 03 00 00 */	cmplwi r3, 0
/* 80089660 00086240  41 82 00 24 */	beq lbl_80089684
/* 80089664 00086244  48 1E 20 65 */	bl func_8026B6C8
/* 80089668 00086248  2C 03 00 00 */	cmpwi r3, 0
/* 8008966C 0008624C  41 82 00 18 */	beq lbl_80089684
/* 80089670 00086250  3C 60 00 44 */	lis r3, 0x0044003D@ha
/* 80089674 00086254  38 03 00 3D */	addi r0, r3, 0x0044003D@l
/* 80089678 00086258  90 01 00 14 */	stw r0, 0x14(r1)
/* 8008967C 0008625C  80 01 00 14 */	lwz r0, 0x14(r1)
/* 80089680 00086260  90 01 00 1C */	stw r0, 0x1c(r1)
lbl_80089684:
/* 80089684 00086264  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 80089688 00086268  38 7F 20 74 */	addi r3, r31, 0x2074
/* 8008968C 0008626C  90 1F 20 70 */	stw r0, 0x2070(r31)
/* 80089690 00086270  48 00 00 D9 */	bl func_80089768
/* 80089694 00086274  C0 1F 18 30 */	lfs f0, 0x1830(r31)
/* 80089698 00086278  FC 00 00 1E */	fctiwz f0, f0
/* 8008969C 0008627C  D8 01 00 20 */	stfd f0, 0x20(r1)
/* 800896A0 00086280  80 01 00 24 */	lwz r0, 0x24(r1)
/* 800896A4 00086284  90 1F 20 74 */	stw r0, 0x2074(r31)
/* 800896A8 00086288  88 1F 22 23 */	lbz r0, 0x2223(r31)
/* 800896AC 0008628C  54 00 07 FF */	clrlwi. r0, r0, 0x1f
/* 800896B0 00086290  41 82 00 14 */	beq lbl_800896C4
/* 800896B4 00086294  88 1F 20 84 */	lbz r0, 0x2084(r31)
/* 800896B8 00086298  38 60 00 01 */	li r3, 1
/* 800896BC 0008629C  50 60 36 72 */	rlwimi r0, r3, 6, 0x19, 0x19
/* 800896C0 000862A0  98 1F 20 84 */	stb r0, 0x2084(r31)
lbl_800896C4:
/* 800896C4 000862A4  80 1F 19 7C */	lwz r0, 0x197c(r31)
/* 800896C8 000862A8  28 00 00 00 */	cmplwi r0, 0
/* 800896CC 000862AC  41 82 00 14 */	beq lbl_800896E0
/* 800896D0 000862B0  88 1F 20 84 */	lbz r0, 0x2084(r31)
/* 800896D4 000862B4  38 60 00 01 */	li r3, 1
/* 800896D8 000862B8  50 60 2E B4 */	rlwimi r0, r3, 5, 0x1a, 0x1a
/* 800896DC 000862BC  98 1F 20 84 */	stb r0, 0x2084(r31)
lbl_800896E0:
/* 800896E0 000862C0  88 1F 22 1D */	lbz r0, 0x221d(r31)
/* 800896E4 000862C4  54 00 FF FF */	rlwinm. r0, r0, 0x1f, 0x1f, 0x1f
/* 800896E8 000862C8  41 82 00 14 */	beq lbl_800896FC
/* 800896EC 000862CC  88 1F 20 84 */	lbz r0, 0x2084(r31)
/* 800896F0 000862D0  38 60 00 01 */	li r3, 1
/* 800896F4 000862D4  50 60 26 F6 */	rlwimi r0, r3, 4, 0x1b, 0x1b
/* 800896F8 000862D8  98 1F 20 84 */	stb r0, 0x2084(r31)
lbl_800896FC:
/* 800896FC 000862DC  88 1F 22 26 */	lbz r0, 0x2226(r31)
/* 80089700 000862E0  54 00 EF FF */	rlwinm. r0, r0, 0x1d, 0x1f, 0x1f
/* 80089704 000862E4  41 82 00 14 */	beq lbl_80089718
/* 80089708 000862E8  88 1F 20 84 */	lbz r0, 0x2084(r31)
/* 8008970C 000862EC  38 60 00 01 */	li r3, 1
/* 80089710 000862F0  50 60 1F 38 */	rlwimi r0, r3, 3, 0x1c, 0x1c
/* 80089714 000862F4  98 1F 20 84 */	stb r0, 0x2084(r31)
lbl_80089718:
/* 80089718 000862F8  88 1F 22 20 */	lbz r0, 0x2220(r31)
/* 8008971C 000862FC  54 00 F7 FF */	rlwinm. r0, r0, 0x1e, 0x1f, 0x1f
/* 80089720 00086300  41 82 00 14 */	beq lbl_80089734
/* 80089724 00086304  88 1F 20 84 */	lbz r0, 0x2084(r31)
/* 80089728 00086308  38 60 00 01 */	li r3, 1
/* 8008972C 0008630C  50 60 17 7A */	rlwimi r0, r3, 2, 0x1d, 0x1d
/* 80089730 00086310  98 1F 20 84 */	stb r0, 0x2084(r31)
lbl_80089734:
/* 80089734 00086314  88 1F 22 20 */	lbz r0, 0x2220(r31)
/* 80089738 00086318  54 00 FF FF */	rlwinm. r0, r0, 0x1f, 0x1f, 0x1f
/* 8008973C 0008631C  41 82 00 14 */	beq lbl_80089750
/* 80089740 00086320  88 1F 20 84 */	lbz r0, 0x2084(r31)
/* 80089744 00086324  38 60 00 01 */	li r3, 1
/* 80089748 00086328  50 60 0F BC */	rlwimi r0, r3, 1, 0x1e, 0x1e
/* 8008974C 0008632C  98 1F 20 84 */	stb r0, 0x2084(r31)
lbl_80089750:
/* 80089750 00086330  80 01 00 34 */	lwz r0, 0x34(r1)
/* 80089754 00086334  83 E1 00 2C */	lwz r31, 0x2c(r1)
/* 80089758 00086338  83 C1 00 28 */	lwz r30, 0x28(r1)
/* 8008975C 0008633C  38 21 00 30 */	addi r1, r1, 0x30
/* 80089760 00086340  7C 08 03 A6 */	mtlr r0
/* 80089764 00086344  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

#pragma push
asm unk_t func_80089768()
{ // clang-format off
    nofralloc
/* 80089768 00086348  38 80 00 00 */	li r4, 0
/* 8008976C 0008634C  90 83 00 00 */	stw r4, 0(r3)
/* 80089770 00086350  38 00 00 06 */	li r0, 6
/* 80089774 00086354  90 83 00 04 */	stw r4, 4(r3)
/* 80089778 00086358  C0 02 8A 08 */	lfs f0, lbl_804D83E8(r2)
/* 8008977C 0008635C  D0 03 00 08 */	stfs f0, 8(r3)
/* 80089780 00086360  90 03 00 0C */	stw r0, 0xc(r3)
/* 80089784 00086364  88 03 00 10 */	lbz r0, 0x10(r3)
/* 80089788 00086368  50 80 3E 30 */	rlwimi r0, r4, 7, 0x18, 0x18
/* 8008978C 0008636C  98 03 00 10 */	stb r0, 0x10(r3)
/* 80089790 00086370  88 03 00 11 */	lbz r0, 0x11(r3)
/* 80089794 00086374  50 80 26 F6 */	rlwimi r0, r4, 4, 0x1b, 0x1b
/* 80089798 00086378  98 03 00 11 */	stb r0, 0x11(r3)
/* 8008979C 0008637C  88 03 00 10 */	lbz r0, 0x10(r3)
/* 800897A0 00086380  50 80 36 72 */	rlwimi r0, r4, 6, 0x19, 0x19
/* 800897A4 00086384  98 03 00 10 */	stb r0, 0x10(r3)
/* 800897A8 00086388  88 03 00 10 */	lbz r0, 0x10(r3)
/* 800897AC 0008638C  50 80 2E B4 */	rlwimi r0, r4, 5, 0x1a, 0x1a
/* 800897B0 00086390  98 03 00 10 */	stb r0, 0x10(r3)
/* 800897B4 00086394  88 03 00 10 */	lbz r0, 0x10(r3)
/* 800897B8 00086398  50 80 26 F6 */	rlwimi r0, r4, 4, 0x1b, 0x1b
/* 800897BC 0008639C  98 03 00 10 */	stb r0, 0x10(r3)
/* 800897C0 000863A0  88 03 00 10 */	lbz r0, 0x10(r3)
/* 800897C4 000863A4  50 80 1F 38 */	rlwimi r0, r4, 3, 0x1c, 0x1c
/* 800897C8 000863A8  98 03 00 10 */	stb r0, 0x10(r3)
/* 800897CC 000863AC  88 03 00 10 */	lbz r0, 0x10(r3)
/* 800897D0 000863B0  50 80 17 7A */	rlwimi r0, r4, 2, 0x1d, 0x1d
/* 800897D4 000863B4  98 03 00 10 */	stb r0, 0x10(r3)
/* 800897D8 000863B8  88 03 00 10 */	lbz r0, 0x10(r3)
/* 800897DC 000863BC  50 80 0F BC */	rlwimi r0, r4, 1, 0x1e, 0x1e
/* 800897E0 000863C0  98 03 00 10 */	stb r0, 0x10(r3)
/* 800897E4 000863C4  88 03 00 10 */	lbz r0, 0x10(r3)
/* 800897E8 000863C8  50 80 07 FE */	rlwimi r0, r4, 0, 0x1f, 0x1f
/* 800897EC 000863CC  98 03 00 10 */	stb r0, 0x10(r3)
/* 800897F0 000863D0  88 03 00 11 */	lbz r0, 0x11(r3)
/* 800897F4 000863D4  50 80 3E 30 */	rlwimi r0, r4, 7, 0x18, 0x18
/* 800897F8 000863D8  98 03 00 11 */	stb r0, 0x11(r3)
/* 800897FC 000863DC  88 03 00 11 */	lbz r0, 0x11(r3)
/* 80089800 000863E0  50 80 36 72 */	rlwimi r0, r4, 6, 0x19, 0x19
/* 80089804 000863E4  98 03 00 11 */	stb r0, 0x11(r3)
/* 80089808 000863E8  88 03 00 11 */	lbz r0, 0x11(r3)
/* 8008980C 000863EC  50 80 2E B4 */	rlwimi r0, r4, 5, 0x1a, 0x1a
/* 80089810 000863F0  98 03 00 11 */	stb r0, 0x11(r3)
/* 80089814 000863F4  88 03 00 11 */	lbz r0, 0x11(r3)
/* 80089818 000863F8  50 80 1F 38 */	rlwimi r0, r4, 3, 0x1c, 0x1c
/* 8008981C 000863FC  98 03 00 11 */	stb r0, 0x11(r3)
/* 80089820 00086400  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

#pragma push
asm void func_80089824(HSD_GObj* fighter_gobj)
{ // clang-format off
    nofralloc
/* 80089824 00086404  7C 08 02 A6 */	mflr r0
/* 80089828 00086408  90 01 00 04 */	stw r0, 4(r1)
/* 8008982C 0008640C  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 80089830 00086410  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 80089834 00086414  93 C1 00 18 */	stw r30, 0x18(r1)
/* 80089838 00086418  7C 7E 1B 78 */	mr r30, r3
/* 8008983C 0008641C  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 80089840 00086420  80 1F 20 70 */	lwz r0, 0x2070(r31)
/* 80089844 00086424  7F E3 FB 78 */	mr r3, r31
/* 80089848 00086428  90 01 00 10 */	stw r0, 0x10(r1)
/* 8008984C 0008642C  80 01 00 10 */	lwz r0, 0x10(r1)
/* 80089850 00086430  90 1F 20 70 */	stw r0, 0x2070(r31)
/* 80089854 00086434  4B FF FC 0D */	bl func_80089460
/* 80089858 00086438  4B FA E2 B1 */	bl func_80037B08
/* 8008985C 0008643C  B0 7F 20 88 */	sth r3, 0x2088(r31)
/* 80089860 00086440  38 7E 00 00 */	addi r3, r30, 0
/* 80089864 00086444  38 80 00 00 */	li r4, 0
/* 80089868 00086448  4B FA E3 F9 */	bl func_80037C60
/* 8008986C 0008644C  80 01 00 24 */	lwz r0, 0x24(r1)
/* 80089870 00086450  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 80089874 00086454  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 80089878 00086458  38 21 00 20 */	addi r1, r1, 0x20
/* 8008987C 0008645C  7C 08 03 A6 */	mtlr r0
/* 80089880 00086460  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

#pragma push
asm unk_t func_80089884()
{ // clang-format off
    nofralloc
/* 80089884 00086464  80 63 00 2C */	lwz r3, 0x2c(r3)
/* 80089888 00086468  38 63 20 70 */	addi r3, r3, 0x2070
/* 8008988C 0008646C  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

#pragma push
asm unk_t func_80089890()
{ // clang-format off
    nofralloc
/* 80089890 00086470  80 63 00 2C */	lwz r3, 0x2c(r3)
/* 80089894 00086474  38 63 18 D4 */	addi r3, r3, 0x18d4
/* 80089898 00086478  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

#pragma push
asm unk_t func_8008989C()
{ // clang-format off
    nofralloc
/* 8008989C 0008647C  80 63 00 2C */	lwz r3, 0x2c(r3)
/* 800898A0 00086480  A0 63 18 EC */	lhz r3, 0x18ec(r3)
/* 800898A4 00086484  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

#pragma push
asm unk_t func_800898A8()
{ // clang-format off
    nofralloc
/* 800898A8 00086488  80 63 00 2C */	lwz r3, 0x2c(r3)
/* 800898AC 0008648C  38 63 20 74 */	addi r3, r3, 0x2074
/* 800898B0 00086490  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

#pragma push
asm unk_t func_800898B4()
{ // clang-format off
    nofralloc
/* 800898B4 00086494  80 63 00 2C */	lwz r3, 0x2c(r3)
/* 800898B8 00086498  38 63 18 D8 */	addi r3, r3, 0x18d8
/* 800898BC 0008649C  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

#pragma push
asm unk_t func_800898C0()
{ // clang-format off
    nofralloc
/* 800898C0 000864A0  7C 08 02 A6 */	mflr r0
/* 800898C4 000864A4  90 01 00 04 */	stw r0, 4(r1)
/* 800898C8 000864A8  94 21 FF F8 */	stwu r1, -8(r1)
/* 800898CC 000864AC  80 63 00 2C */	lwz r3, 0x2c(r3)
/* 800898D0 000864B0  88 03 20 73 */	lbz r0, 0x2073(r3)
/* 800898D4 000864B4  28 00 00 71 */	cmplwi r0, 0x71
/* 800898D8 000864B8  41 82 00 20 */	beq lbl_800898F8
/* 800898DC 000864BC  28 00 00 72 */	cmplwi r0, 0x72
/* 800898E0 000864C0  41 82 00 18 */	beq lbl_800898F8
/* 800898E4 000864C4  28 00 00 63 */	cmplwi r0, 0x63
/* 800898E8 000864C8  41 82 00 10 */	beq lbl_800898F8
/* 800898EC 000864CC  48 05 C0 85 */	bl ftFox_AppealS_CheckIfUsed
/* 800898F0 000864D0  2C 03 00 00 */	cmpwi r3, 0
/* 800898F4 000864D4  41 82 00 0C */	beq lbl_80089900
lbl_800898F8:
/* 800898F8 000864D8  38 60 00 01 */	li r3, 1
/* 800898FC 000864DC  48 00 00 08 */	b lbl_80089904
lbl_80089900:
/* 80089900 000864E0  38 60 00 00 */	li r3, 0
lbl_80089904:
/* 80089904 000864E4  80 01 00 0C */	lwz r0, 0xc(r1)
/* 80089908 000864E8  38 21 00 08 */	addi r1, r1, 8
/* 8008990C 000864EC  7C 08 03 A6 */	mtlr r0
/* 80089910 000864F0  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

#pragma push
asm unk_t func_80089914()
{ // clang-format off
    nofralloc
/* 80089914 000864F4  2C 04 00 33 */	cmpwi r4, 0x33
/* 80089918 000864F8  80 63 00 2C */	lwz r3, 0x2c(r3)
/* 8008991C 000864FC  41 80 00 0C */	blt lbl_80089928
/* 80089920 00086500  2C 04 00 3D */	cmpwi r4, 0x3d
/* 80089924 00086504  40 81 00 0C */	ble lbl_80089930
lbl_80089928:
/* 80089928 00086508  38 60 00 00 */	li r3, 0
/* 8008992C 0008650C  4E 80 00 20 */	blr 
lbl_80089930:
/* 80089930 00086510  80 63 00 04 */	lwz r3, 4(r3)
/* 80089934 00086514  2C 03 00 01 */	cmpwi r3, 1
/* 80089938 00086518  40 82 00 18 */	bne lbl_80089950
/* 8008993C 0008651C  38 04 FF CA */	addi r0, r4, -54
/* 80089940 00086520  28 00 00 02 */	cmplwi r0, 2
/* 80089944 00086524  41 81 00 0C */	bgt lbl_80089950
/* 80089948 00086528  38 60 00 00 */	li r3, 0
/* 8008994C 0008652C  4E 80 00 20 */	blr 
lbl_80089950:
/* 80089950 00086530  2C 03 00 16 */	cmpwi r3, 0x16
/* 80089954 00086534  40 82 00 18 */	bne lbl_8008996C
/* 80089958 00086538  38 04 FF CA */	addi r0, r4, -54
/* 8008995C 0008653C  28 00 00 02 */	cmplwi r0, 2
/* 80089960 00086540  41 81 00 0C */	bgt lbl_8008996C
/* 80089964 00086544  38 60 00 00 */	li r3, 0
/* 80089968 00086548  4E 80 00 20 */	blr 
lbl_8008996C:
/* 8008996C 0008654C  2C 03 00 10 */	cmpwi r3, 0x10
/* 80089970 00086550  40 82 00 14 */	bne lbl_80089984
/* 80089974 00086554  2C 04 00 35 */	cmpwi r4, 0x35
/* 80089978 00086558  40 82 00 0C */	bne lbl_80089984
/* 8008997C 0008655C  38 60 00 00 */	li r3, 0
/* 80089980 00086560  4E 80 00 20 */	blr 
lbl_80089984:
/* 80089984 00086564  38 60 00 01 */	li r3, 1
/* 80089988 00086568  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

extern char* lbl_804D3AD0;
extern char* lbl_804D3AD8;
extern f32 const lbl_804D83F0;
extern f32 const lbl_804D83F4;
extern f32 const lbl_804D83F8;
extern f32 const lbl_804D83FC;
extern unk_t func_8004DD90();

#pragma push
asm unk_t func_8008998C()
{ // clang-format off
    nofralloc
/* 8008998C 0008656C  7C 08 02 A6 */	mflr r0
/* 80089990 00086570  90 01 00 04 */	stw r0, 4(r1)
/* 80089994 00086574  94 21 FF A8 */	stwu r1, -0x58(r1)
/* 80089998 00086578  93 E1 00 54 */	stw r31, 0x54(r1)
/* 8008999C 0008657C  93 C1 00 50 */	stw r30, 0x50(r1)
/* 800899A0 00086580  3B C4 00 3C */	addi r30, r4, 0x3c
/* 800899A4 00086584  93 A1 00 4C */	stw r29, 0x4c(r1)
/* 800899A8 00086588  3B A5 00 00 */	addi r29, r5, 0
/* 800899AC 0008658C  93 81 00 48 */	stw r28, 0x48(r1)
/* 800899B0 00086590  7C 7C 1B 78 */	mr r28, r3
/* 800899B4 00086594  80 63 00 00 */	lwz r3, 0(r3)
/* 800899B8 00086598  83 E3 00 28 */	lwz r31, 0x28(r3)
/* 800899BC 0008659C  28 1F 00 00 */	cmplwi r31, 0
/* 800899C0 000865A0  40 82 00 14 */	bne lbl_800899D4
/* 800899C4 000865A4  38 6D 84 30 */	addi r3, r13, lbl_804D3AD0
/* 800899C8 000865A8  38 80 03 D3 */	li r4, 0x3d3
/* 800899CC 000865AC  38 AD 84 38 */	addi r5, r13, lbl_804D3AD8
/* 800899D0 000865B0  48 2F E8 51 */	bl __assert
lbl_800899D4:
/* 800899D4 000865B4  80 7F 00 38 */	lwz r3, 0x38(r31)
/* 800899D8 000865B8  7F C4 F3 78 */	mr r4, r30
/* 800899DC 000865BC  80 1F 00 3C */	lwz r0, 0x3c(r31)
/* 800899E0 000865C0  7F A7 EB 78 */	mr r7, r29
/* 800899E4 000865C4  C0 02 8A 10 */	lfs f0, lbl_804D83F0(r2)
/* 800899E8 000865C8  90 61 00 30 */	stw r3, 0x30(r1)
/* 800899EC 000865CC  38 A1 00 1C */	addi r5, r1, 0x1c
/* 800899F0 000865D0  38 C1 00 18 */	addi r6, r1, 0x18
/* 800899F4 000865D4  90 01 00 34 */	stw r0, 0x34(r1)
/* 800899F8 000865D8  80 1F 00 40 */	lwz r0, 0x40(r31)
/* 800899FC 000865DC  90 01 00 38 */	stw r0, 0x38(r1)
/* 80089A00 000865E0  D0 1D 00 08 */	stfs f0, 8(r29)
/* 80089A04 000865E4  D0 1D 00 04 */	stfs f0, 4(r29)
/* 80089A08 000865E8  D0 1D 00 00 */	stfs f0, 0(r29)
/* 80089A0C 000865EC  80 7C 08 3C */	lwz r3, 0x83c(r28)
/* 80089A10 000865F0  4B FC 43 81 */	bl func_8004DD90
/* 80089A14 000865F4  2C 03 FF FF */	cmpwi r3, -1
/* 80089A18 000865F8  41 82 00 1C */	beq lbl_80089A34
/* 80089A1C 000865FC  C0 5E 00 04 */	lfs f2, 4(r30)
/* 80089A20 00086600  C0 21 00 1C */	lfs f1, 0x1c(r1)
/* 80089A24 00086604  C0 01 00 34 */	lfs f0, 0x34(r1)
/* 80089A28 00086608  EC 22 08 2A */	fadds f1, f2, f1
/* 80089A2C 0008660C  EC 61 00 28 */	fsubs f3, f1, f0
/* 80089A30 00086610  48 00 00 38 */	b lbl_80089A68
lbl_80089A34:
/* 80089A34 00086614  80 7C 08 3C */	lwz r3, 0x83c(r28)
/* 80089A38 00086618  38 81 00 20 */	addi r4, r1, 0x20
/* 80089A3C 0008661C  4B FC A7 1D */	bl func_80054158
/* 80089A40 00086620  C0 3E 00 00 */	lfs f1, 0(r30)
/* 80089A44 00086624  C0 01 00 20 */	lfs f0, 0x20(r1)
/* 80089A48 00086628  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 80089A4C 0008662C  40 81 00 10 */	ble lbl_80089A5C
/* 80089A50 00086630  80 7C 08 3C */	lwz r3, 0x83c(r28)
/* 80089A54 00086634  38 81 00 20 */	addi r4, r1, 0x20
/* 80089A58 00086638  4B FC A5 9D */	bl func_80053FF4
lbl_80089A5C:
/* 80089A5C 0008663C  C0 21 00 24 */	lfs f1, 0x24(r1)
/* 80089A60 00086640  C0 01 00 34 */	lfs f0, 0x34(r1)
/* 80089A64 00086644  EC 61 00 28 */	fsubs f3, f1, f0
lbl_80089A68:
/* 80089A68 00086648  C0 02 8A 10 */	lfs f0, lbl_804D83F0(r2)
/* 80089A6C 0008664C  FC 03 00 40 */	fcmpo cr0, f3, f0
/* 80089A70 00086650  40 80 00 0C */	bge lbl_80089A7C
/* 80089A74 00086654  FC 20 18 50 */	fneg f1, f3
/* 80089A78 00086658  48 00 00 08 */	b lbl_80089A80
lbl_80089A7C:
/* 80089A7C 0008665C  FC 20 18 90 */	fmr f1, f3
lbl_80089A80:
/* 80089A80 00086660  C0 02 8A 14 */	lfs f0, lbl_804D83F4(r2)
/* 80089A84 00086664  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 80089A88 00086668  40 80 00 0C */	bge lbl_80089A94
/* 80089A8C 0008666C  38 60 00 00 */	li r3, 0
/* 80089A90 00086670  48 00 00 58 */	b lbl_80089AE8
lbl_80089A94:
/* 80089A94 00086674  C0 3E 00 00 */	lfs f1, 0(r30)
/* 80089A98 00086678  C0 01 00 30 */	lfs f0, 0x30(r1)
/* 80089A9C 0008667C  FC 01 00 00 */	fcmpu cr0, f1, f0
/* 80089AA0 00086680  41 82 00 34 */	beq lbl_80089AD4
/* 80089AA4 00086684  EC 41 00 28 */	fsubs f2, f1, f0
/* 80089AA8 00086688  C0 02 8A 18 */	lfs f0, lbl_804D83F8(r2)
/* 80089AAC 0008668C  EC 23 10 24 */	fdivs f1, f3, f2
/* 80089AB0 00086690  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 80089AB4 00086694  40 81 00 0C */	ble lbl_80089AC0
/* 80089AB8 00086698  EC 60 00 B2 */	fmuls f3, f0, f2
/* 80089ABC 0008669C  48 00 00 1C */	b lbl_80089AD8
lbl_80089AC0:
/* 80089AC0 000866A0  C0 02 8A 1C */	lfs f0, lbl_804D83FC(r2)
/* 80089AC4 000866A4  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 80089AC8 000866A8  40 80 00 10 */	bge lbl_80089AD8
/* 80089ACC 000866AC  EC 60 00 B2 */	fmuls f3, f0, f2
/* 80089AD0 000866B0  48 00 00 08 */	b lbl_80089AD8
lbl_80089AD4:
/* 80089AD4 000866B4  C0 62 8A 10 */	lfs f3, lbl_804D83F0(r2)
lbl_80089AD8:
/* 80089AD8 000866B8  C0 1E 00 04 */	lfs f0, 4(r30)
/* 80089ADC 000866BC  38 60 00 01 */	li r3, 1
/* 80089AE0 000866C0  EC 00 18 2A */	fadds f0, f0, f3
/* 80089AE4 000866C4  D0 1E 00 04 */	stfs f0, 4(r30)
lbl_80089AE8:
/* 80089AE8 000866C8  80 01 00 5C */	lwz r0, 0x5c(r1)
/* 80089AEC 000866CC  83 E1 00 54 */	lwz r31, 0x54(r1)
/* 80089AF0 000866D0  83 C1 00 50 */	lwz r30, 0x50(r1)
/* 80089AF4 000866D4  83 A1 00 4C */	lwz r29, 0x4c(r1)
/* 80089AF8 000866D8  83 81 00 48 */	lwz r28, 0x48(r1)
/* 80089AFC 000866DC  38 21 00 58 */	addi r1, r1, 0x58
/* 80089B00 000866E0  7C 08 03 A6 */	mtlr r0
/* 80089B04 000866E4  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

extern unk_t lbl_804D4AF8;
extern f32 const lbl_804D8400;
extern f32 const lbl_804D8404;
extern f32 const lbl_804D8408;
extern f32 const lbl_804D840C;
extern f32 const lbl_804D8410;
extern f64 const lbl_804D8418;
extern f64 const lbl_804D8420;
extern f32 const lbl_804D8428;
extern f32 const lbl_804D842C;
extern f32 const lbl_804D8430;
extern f32 const lbl_804D8434;
extern unk_t func_8004DC04();
extern unk_t func_80054DFC();
extern unk_t func_80054C6C();
extern unk_t func_8004DB78();
extern unk_t func_80054BC0();
extern unk_t func_80054B14();
extern unk_t func_80020E38();
extern unk_t func_80021410();

#pragma push
asm void func_80089B08(HSD_GObj* pPlayerEntityStruct)
{ // clang-format off
    nofralloc
/* 80089B08 000866E8  7C 08 02 A6 */	mflr r0
/* 80089B0C 000866EC  90 01 00 04 */	stw r0, 4(r1)
/* 80089B10 000866F0  94 21 FE D0 */	stwu r1, -0x130(r1)
/* 80089B14 000866F4  DB E1 01 28 */	stfd f31, 0x128(r1)
/* 80089B18 000866F8  DB C1 01 20 */	stfd f30, 0x120(r1)
/* 80089B1C 000866FC  93 E1 01 1C */	stw r31, 0x11c(r1)
/* 80089B20 00086700  93 C1 01 18 */	stw r30, 0x118(r1)
/* 80089B24 00086704  93 A1 01 14 */	stw r29, 0x114(r1)
/* 80089B28 00086708  93 81 01 10 */	stw r28, 0x110(r1)
/* 80089B2C 0008670C  80 63 00 2C */	lwz r3, 0x2c(r3)
/* 80089B30 00086710  88 03 22 19 */	lbz r0, 0x2219(r3)
/* 80089B34 00086714  3B E3 00 00 */	addi r31, r3, 0
/* 80089B38 00086718  54 00 F7 FF */	rlwinm. r0, r0, 0x1e, 0x1f, 0x1f
/* 80089B3C 0008671C  40 82 06 54 */	bne lbl_8008A190
/* 80089B40 00086720  80 1F 00 E0 */	lwz r0, 0xe0(r31)
/* 80089B44 00086724  2C 00 00 00 */	cmpwi r0, 0
/* 80089B48 00086728  40 82 06 48 */	bne lbl_8008A190
/* 80089B4C 0008672C  80 0D 94 58 */	lwz r0, lbl_804D4AF8(r13)
/* 80089B50 00086730  2C 00 00 00 */	cmpwi r0, 0
/* 80089B54 00086734  41 82 04 78 */	beq lbl_80089FCC
/* 80089B58 00086738  80 7F 01 0C */	lwz r3, 0x10c(r31)
/* 80089B5C 0008673C  C0 5F 00 38 */	lfs f2, 0x38(r31)
/* 80089B60 00086740  80 63 00 58 */	lwz r3, 0x58(r3)
/* 80089B64 00086744  C0 03 00 04 */	lfs f0, 4(r3)
/* 80089B68 00086748  EC 00 00 B2 */	fmuls f0, f0, f2
/* 80089B6C 0008674C  D0 01 00 F8 */	stfs f0, 0xf8(r1)
/* 80089B70 00086750  80 7F 01 0C */	lwz r3, 0x10c(r31)
/* 80089B74 00086754  80 63 00 58 */	lwz r3, 0x58(r3)
/* 80089B78 00086758  C0 23 00 0C */	lfs f1, 0xc(r3)
/* 80089B7C 0008675C  C0 03 00 18 */	lfs f0, 0x18(r3)
/* 80089B80 00086760  EC 01 00 2A */	fadds f0, f1, f0
/* 80089B84 00086764  EC 02 00 32 */	fmuls f0, f2, f0
/* 80089B88 00086768  D0 01 00 FC */	stfs f0, 0xfc(r1)
/* 80089B8C 0008676C  A0 1F 22 1C */	lhz r0, 0x221c(r31)
/* 80089B90 00086770  54 00 D7 BD */	rlwinm. r0, r0, 0x1a, 0x1e, 0x1e
/* 80089B94 00086774  41 82 02 18 */	beq lbl_80089DAC
/* 80089B98 00086778  80 7F 01 0C */	lwz r3, 0x10c(r31)
/* 80089B9C 0008677C  38 A1 00 BC */	addi r5, r1, 0xbc
/* 80089BA0 00086780  80 DF 05 E8 */	lwz r6, 0x5e8(r31)
/* 80089BA4 00086784  38 80 00 00 */	li r4, 0
/* 80089BA8 00086788  80 63 00 58 */	lwz r3, 0x58(r3)
/* 80089BAC 0008678C  88 03 00 00 */	lbz r0, 0(r3)
/* 80089BB0 00086790  54 00 20 36 */	slwi r0, r0, 4
/* 80089BB4 00086794  7C 06 00 2E */	lwzx r0, r6, r0
/* 80089BB8 00086798  90 01 00 B0 */	stw r0, 0xb0(r1)
/* 80089BBC 0008679C  80 7F 01 0C */	lwz r3, 0x10c(r31)
/* 80089BC0 000867A0  80 DF 05 E8 */	lwz r6, 0x5e8(r31)
/* 80089BC4 000867A4  80 63 00 58 */	lwz r3, 0x58(r3)
/* 80089BC8 000867A8  88 03 00 08 */	lbz r0, 8(r3)
/* 80089BCC 000867AC  54 00 20 36 */	slwi r0, r0, 4
/* 80089BD0 000867B0  7C 06 00 2E */	lwzx r0, r6, r0
/* 80089BD4 000867B4  90 01 00 B4 */	stw r0, 0xb4(r1)
/* 80089BD8 000867B8  80 7F 01 0C */	lwz r3, 0x10c(r31)
/* 80089BDC 000867BC  80 DF 05 E8 */	lwz r6, 0x5e8(r31)
/* 80089BE0 000867C0  80 63 00 58 */	lwz r3, 0x58(r3)
/* 80089BE4 000867C4  88 03 00 10 */	lbz r0, 0x10(r3)
/* 80089BE8 000867C8  54 00 20 36 */	slwi r0, r0, 4
/* 80089BEC 000867CC  7C 06 00 2E */	lwzx r0, r6, r0
/* 80089BF0 000867D0  90 01 00 B8 */	stw r0, 0xb8(r1)
/* 80089BF4 000867D4  C0 22 8A 20 */	lfs f1, lbl_804D8400(r2)
/* 80089BF8 000867D8  C0 02 8A 24 */	lfs f0, lbl_804D8404(r2)
/* 80089BFC 000867DC  D0 21 01 00 */	stfs f1, 0x100(r1)
/* 80089C00 000867E0  D0 01 01 04 */	stfs f0, 0x104(r1)
/* 80089C04 000867E4  80 61 00 B0 */	lwz r3, 0xb0(r1)
/* 80089C08 000867E8  4B F8 15 C5 */	bl func_8000B1CC
/* 80089C0C 000867EC  3B C1 00 C8 */	addi r30, r1, 0xc8
/* 80089C10 000867F0  80 61 00 B4 */	lwz r3, 0xb4(r1)
/* 80089C14 000867F4  38 BE 00 00 */	addi r5, r30, 0
/* 80089C18 000867F8  38 80 00 00 */	li r4, 0
/* 80089C1C 000867FC  4B F8 15 B1 */	bl func_8000B1CC
/* 80089C20 00086800  3B A1 00 D4 */	addi r29, r1, 0xd4
/* 80089C24 00086804  80 61 00 B8 */	lwz r3, 0xb8(r1)
/* 80089C28 00086808  38 BD 00 00 */	addi r5, r29, 0
/* 80089C2C 0008680C  38 80 00 00 */	li r4, 0
/* 80089C30 00086810  4B F8 15 9D */	bl func_8000B1CC
/* 80089C34 00086814  3B 81 00 E0 */	addi r28, r1, 0xe0
/* 80089C38 00086818  38 7D 00 00 */	addi r3, r29, 0
/* 80089C3C 0008681C  38 9E 00 00 */	addi r4, r30, 0
/* 80089C40 00086820  38 BC 00 00 */	addi r5, r28, 0
/* 80089C44 00086824  4B F8 38 B5 */	bl lbvector_Diff
/* 80089C48 00086828  C3 E1 00 FC */	lfs f31, 0xfc(r1)
/* 80089C4C 0008682C  7F 83 E3 78 */	mr r3, r28
/* 80089C50 00086830  4B F8 36 9D */	bl lbvector_Normalize
/* 80089C54 00086834  C0 01 00 E0 */	lfs f0, 0xe0(r1)
/* 80089C58 00086838  38 7C 00 00 */	addi r3, r28, 0
/* 80089C5C 0008683C  38 9E 00 00 */	addi r4, r30, 0
/* 80089C60 00086840  EC 00 07 F2 */	fmuls f0, f0, f31
/* 80089C64 00086844  D0 01 00 E0 */	stfs f0, 0xe0(r1)
/* 80089C68 00086848  C0 01 00 E4 */	lfs f0, 0xe4(r1)
/* 80089C6C 0008684C  EC 00 07 F2 */	fmuls f0, f0, f31
/* 80089C70 00086850  D0 01 00 E4 */	stfs f0, 0xe4(r1)
/* 80089C74 00086854  C0 01 00 E8 */	lfs f0, 0xe8(r1)
/* 80089C78 00086858  EC 00 07 F2 */	fmuls f0, f0, f31
/* 80089C7C 0008685C  D0 01 00 E8 */	stfs f0, 0xe8(r1)
/* 80089C80 00086860  4B F8 37 ED */	bl lbvector_Add
/* 80089C84 00086864  80 C1 00 E0 */	lwz r6, 0xe0(r1)
/* 80089C88 00086868  7F E3 FB 78 */	mr r3, r31
/* 80089C8C 0008686C  80 01 00 E4 */	lwz r0, 0xe4(r1)
/* 80089C90 00086870  38 81 00 B0 */	addi r4, r1, 0xb0
/* 80089C94 00086874  38 A1 00 A4 */	addi r5, r1, 0xa4
/* 80089C98 00086878  90 C1 00 EC */	stw r6, 0xec(r1)
/* 80089C9C 0008687C  90 01 00 F0 */	stw r0, 0xf0(r1)
/* 80089CA0 00086880  80 01 00 E8 */	lwz r0, 0xe8(r1)
/* 80089CA4 00086884  90 01 00 F4 */	stw r0, 0xf4(r1)
/* 80089CA8 00086888  80 E1 00 B0 */	lwz r7, 0xb0(r1)
/* 80089CAC 0008688C  80 C7 00 1C */	lwz r6, 0x1c(r7)
/* 80089CB0 00086890  80 07 00 20 */	lwz r0, 0x20(r7)
/* 80089CB4 00086894  90 C1 00 94 */	stw r6, 0x94(r1)
/* 80089CB8 00086898  90 01 00 98 */	stw r0, 0x98(r1)
/* 80089CBC 0008689C  80 C7 00 24 */	lwz r6, 0x24(r7)
/* 80089CC0 000868A0  80 07 00 28 */	lwz r0, 0x28(r7)
/* 80089CC4 000868A4  90 C1 00 9C */	stw r6, 0x9c(r1)
/* 80089CC8 000868A8  90 01 00 A0 */	stw r0, 0xa0(r1)
/* 80089CCC 000868AC  80 E1 00 B4 */	lwz r7, 0xb4(r1)
/* 80089CD0 000868B0  80 C7 00 1C */	lwz r6, 0x1c(r7)
/* 80089CD4 000868B4  80 07 00 20 */	lwz r0, 0x20(r7)
/* 80089CD8 000868B8  90 C1 00 84 */	stw r6, 0x84(r1)
/* 80089CDC 000868BC  90 01 00 88 */	stw r0, 0x88(r1)
/* 80089CE0 000868C0  80 C7 00 24 */	lwz r6, 0x24(r7)
/* 80089CE4 000868C4  80 07 00 28 */	lwz r0, 0x28(r7)
/* 80089CE8 000868C8  90 C1 00 8C */	stw r6, 0x8c(r1)
/* 80089CEC 000868CC  90 01 00 90 */	stw r0, 0x90(r1)
/* 80089CF0 000868D0  80 E1 00 B8 */	lwz r7, 0xb8(r1)
/* 80089CF4 000868D4  80 C7 00 1C */	lwz r6, 0x1c(r7)
/* 80089CF8 000868D8  80 07 00 20 */	lwz r0, 0x20(r7)
/* 80089CFC 000868DC  90 C1 00 74 */	stw r6, 0x74(r1)
/* 80089D00 000868E0  90 01 00 78 */	stw r0, 0x78(r1)
/* 80089D04 000868E4  80 C7 00 24 */	lwz r6, 0x24(r7)
/* 80089D08 000868E8  80 07 00 28 */	lwz r0, 0x28(r7)
/* 80089D0C 000868EC  90 C1 00 7C */	stw r6, 0x7c(r1)
/* 80089D10 000868F0  90 01 00 80 */	stw r0, 0x80(r1)
/* 80089D14 000868F4  4B FF FC 79 */	bl func_8008998C
/* 80089D18 000868F8  2C 03 00 00 */	cmpwi r3, 0
/* 80089D1C 000868FC  41 82 00 0C */	beq lbl_80089D28
/* 80089D20 00086900  38 61 00 B0 */	addi r3, r1, 0xb0
/* 80089D24 00086904  4B F9 76 ED */	bl func_80021410
lbl_80089D28:
/* 80089D28 00086908  C0 22 8A 28 */	lfs f1, lbl_804D8408(r2)
/* 80089D2C 0008690C  38 81 00 A4 */	addi r4, r1, 0xa4
/* 80089D30 00086910  80 61 00 B8 */	lwz r3, 0xb8(r1)
/* 80089D34 00086914  FC 40 08 90 */	fmr f2, f1
/* 80089D38 00086918  C0 62 8A 2C */	lfs f3, lbl_804D840C(r2)
/* 80089D3C 0008691C  4B F9 70 FD */	bl func_80020E38
/* 80089D40 00086920  80 81 00 B0 */	lwz r4, 0xb0(r1)
/* 80089D44 00086924  80 61 00 94 */	lwz r3, 0x94(r1)
/* 80089D48 00086928  80 01 00 98 */	lwz r0, 0x98(r1)
/* 80089D4C 0008692C  90 64 00 1C */	stw r3, 0x1c(r4)
/* 80089D50 00086930  90 04 00 20 */	stw r0, 0x20(r4)
/* 80089D54 00086934  80 61 00 9C */	lwz r3, 0x9c(r1)
/* 80089D58 00086938  80 01 00 A0 */	lwz r0, 0xa0(r1)
/* 80089D5C 0008693C  90 64 00 24 */	stw r3, 0x24(r4)
/* 80089D60 00086940  90 04 00 28 */	stw r0, 0x28(r4)
/* 80089D64 00086944  80 81 00 B4 */	lwz r4, 0xb4(r1)
/* 80089D68 00086948  80 61 00 84 */	lwz r3, 0x84(r1)
/* 80089D6C 0008694C  80 01 00 88 */	lwz r0, 0x88(r1)
/* 80089D70 00086950  90 64 00 1C */	stw r3, 0x1c(r4)
/* 80089D74 00086954  90 04 00 20 */	stw r0, 0x20(r4)
/* 80089D78 00086958  80 61 00 8C */	lwz r3, 0x8c(r1)
/* 80089D7C 0008695C  80 01 00 90 */	lwz r0, 0x90(r1)
/* 80089D80 00086960  90 64 00 24 */	stw r3, 0x24(r4)
/* 80089D84 00086964  90 04 00 28 */	stw r0, 0x28(r4)
/* 80089D88 00086968  80 81 00 B8 */	lwz r4, 0xb8(r1)
/* 80089D8C 0008696C  80 61 00 74 */	lwz r3, 0x74(r1)
/* 80089D90 00086970  80 01 00 78 */	lwz r0, 0x78(r1)
/* 80089D94 00086974  90 64 00 1C */	stw r3, 0x1c(r4)
/* 80089D98 00086978  90 04 00 20 */	stw r0, 0x20(r4)
/* 80089D9C 0008697C  80 61 00 7C */	lwz r3, 0x7c(r1)
/* 80089DA0 00086980  80 01 00 80 */	lwz r0, 0x80(r1)
/* 80089DA4 00086984  90 64 00 24 */	stw r3, 0x24(r4)
/* 80089DA8 00086988  90 04 00 28 */	stw r0, 0x28(r4)
lbl_80089DAC:
/* 80089DAC 0008698C  A0 1F 22 1C */	lhz r0, 0x221c(r31)
/* 80089DB0 00086990  54 00 D7 FF */	rlwinm. r0, r0, 0x1a, 0x1f, 0x1f
/* 80089DB4 00086994  41 82 02 18 */	beq lbl_80089FCC
/* 80089DB8 00086998  80 7F 01 0C */	lwz r3, 0x10c(r31)
/* 80089DBC 0008699C  38 A1 00 BC */	addi r5, r1, 0xbc
/* 80089DC0 000869A0  80 DF 05 E8 */	lwz r6, 0x5e8(r31)
/* 80089DC4 000869A4  38 80 00 00 */	li r4, 0
/* 80089DC8 000869A8  80 63 00 58 */	lwz r3, 0x58(r3)
/* 80089DCC 000869AC  88 03 00 01 */	lbz r0, 1(r3)
/* 80089DD0 000869B0  54 00 20 36 */	slwi r0, r0, 4
/* 80089DD4 000869B4  7C 06 00 2E */	lwzx r0, r6, r0
/* 80089DD8 000869B8  90 01 00 B0 */	stw r0, 0xb0(r1)
/* 80089DDC 000869BC  80 7F 01 0C */	lwz r3, 0x10c(r31)
/* 80089DE0 000869C0  80 DF 05 E8 */	lwz r6, 0x5e8(r31)
/* 80089DE4 000869C4  80 63 00 58 */	lwz r3, 0x58(r3)
/* 80089DE8 000869C8  88 03 00 09 */	lbz r0, 9(r3)
/* 80089DEC 000869CC  54 00 20 36 */	slwi r0, r0, 4
/* 80089DF0 000869D0  7C 06 00 2E */	lwzx r0, r6, r0
/* 80089DF4 000869D4  90 01 00 B4 */	stw r0, 0xb4(r1)
/* 80089DF8 000869D8  80 7F 01 0C */	lwz r3, 0x10c(r31)
/* 80089DFC 000869DC  80 DF 05 E8 */	lwz r6, 0x5e8(r31)
/* 80089E00 000869E0  80 63 00 58 */	lwz r3, 0x58(r3)
/* 80089E04 000869E4  88 03 00 11 */	lbz r0, 0x11(r3)
/* 80089E08 000869E8  54 00 20 36 */	slwi r0, r0, 4
/* 80089E0C 000869EC  7C 06 00 2E */	lwzx r0, r6, r0
/* 80089E10 000869F0  90 01 00 B8 */	stw r0, 0xb8(r1)
/* 80089E14 000869F4  C0 22 8A 20 */	lfs f1, lbl_804D8400(r2)
/* 80089E18 000869F8  C0 02 8A 24 */	lfs f0, lbl_804D8404(r2)
/* 80089E1C 000869FC  D0 21 01 00 */	stfs f1, 0x100(r1)
/* 80089E20 00086A00  D0 01 01 04 */	stfs f0, 0x104(r1)
/* 80089E24 00086A04  80 61 00 B0 */	lwz r3, 0xb0(r1)
/* 80089E28 00086A08  4B F8 13 A5 */	bl func_8000B1CC
/* 80089E2C 00086A0C  3B 81 00 C8 */	addi r28, r1, 0xc8
/* 80089E30 00086A10  80 61 00 B4 */	lwz r3, 0xb4(r1)
/* 80089E34 00086A14  38 BC 00 00 */	addi r5, r28, 0
/* 80089E38 00086A18  38 80 00 00 */	li r4, 0
/* 80089E3C 00086A1C  4B F8 13 91 */	bl func_8000B1CC
/* 80089E40 00086A20  3B A1 00 D4 */	addi r29, r1, 0xd4
/* 80089E44 00086A24  80 61 00 B8 */	lwz r3, 0xb8(r1)
/* 80089E48 00086A28  38 BD 00 00 */	addi r5, r29, 0
/* 80089E4C 00086A2C  38 80 00 00 */	li r4, 0
/* 80089E50 00086A30  4B F8 13 7D */	bl func_8000B1CC
/* 80089E54 00086A34  3B C1 00 E0 */	addi r30, r1, 0xe0
/* 80089E58 00086A38  38 7D 00 00 */	addi r3, r29, 0
/* 80089E5C 00086A3C  38 9C 00 00 */	addi r4, r28, 0
/* 80089E60 00086A40  38 BE 00 00 */	addi r5, r30, 0
/* 80089E64 00086A44  4B F8 36 95 */	bl lbvector_Diff
/* 80089E68 00086A48  C3 E1 00 FC */	lfs f31, 0xfc(r1)
/* 80089E6C 00086A4C  7F C3 F3 78 */	mr r3, r30
/* 80089E70 00086A50  4B F8 34 7D */	bl lbvector_Normalize
/* 80089E74 00086A54  C0 01 00 E0 */	lfs f0, 0xe0(r1)
/* 80089E78 00086A58  38 7E 00 00 */	addi r3, r30, 0
/* 80089E7C 00086A5C  38 9C 00 00 */	addi r4, r28, 0
/* 80089E80 00086A60  EC 00 07 F2 */	fmuls f0, f0, f31
/* 80089E84 00086A64  D0 01 00 E0 */	stfs f0, 0xe0(r1)
/* 80089E88 00086A68  C0 01 00 E4 */	lfs f0, 0xe4(r1)
/* 80089E8C 00086A6C  EC 00 07 F2 */	fmuls f0, f0, f31
/* 80089E90 00086A70  D0 01 00 E4 */	stfs f0, 0xe4(r1)
/* 80089E94 00086A74  C0 01 00 E8 */	lfs f0, 0xe8(r1)
/* 80089E98 00086A78  EC 00 07 F2 */	fmuls f0, f0, f31
/* 80089E9C 00086A7C  D0 01 00 E8 */	stfs f0, 0xe8(r1)
/* 80089EA0 00086A80  4B F8 35 CD */	bl lbvector_Add
/* 80089EA4 00086A84  80 C1 00 E0 */	lwz r6, 0xe0(r1)
/* 80089EA8 00086A88  7F E3 FB 78 */	mr r3, r31
/* 80089EAC 00086A8C  80 01 00 E4 */	lwz r0, 0xe4(r1)
/* 80089EB0 00086A90  38 81 00 B0 */	addi r4, r1, 0xb0
/* 80089EB4 00086A94  38 A1 00 A4 */	addi r5, r1, 0xa4
/* 80089EB8 00086A98  90 C1 00 EC */	stw r6, 0xec(r1)
/* 80089EBC 00086A9C  90 01 00 F0 */	stw r0, 0xf0(r1)
/* 80089EC0 00086AA0  80 01 00 E8 */	lwz r0, 0xe8(r1)
/* 80089EC4 00086AA4  90 01 00 F4 */	stw r0, 0xf4(r1)
/* 80089EC8 00086AA8  80 E1 00 B0 */	lwz r7, 0xb0(r1)
/* 80089ECC 00086AAC  80 C7 00 1C */	lwz r6, 0x1c(r7)
/* 80089ED0 00086AB0  80 07 00 20 */	lwz r0, 0x20(r7)
/* 80089ED4 00086AB4  90 C1 00 64 */	stw r6, 0x64(r1)
/* 80089ED8 00086AB8  90 01 00 68 */	stw r0, 0x68(r1)
/* 80089EDC 00086ABC  80 C7 00 24 */	lwz r6, 0x24(r7)
/* 80089EE0 00086AC0  80 07 00 28 */	lwz r0, 0x28(r7)
/* 80089EE4 00086AC4  90 C1 00 6C */	stw r6, 0x6c(r1)
/* 80089EE8 00086AC8  90 01 00 70 */	stw r0, 0x70(r1)
/* 80089EEC 00086ACC  80 E1 00 B4 */	lwz r7, 0xb4(r1)
/* 80089EF0 00086AD0  80 C7 00 1C */	lwz r6, 0x1c(r7)
/* 80089EF4 00086AD4  80 07 00 20 */	lwz r0, 0x20(r7)
/* 80089EF8 00086AD8  90 C1 00 54 */	stw r6, 0x54(r1)
/* 80089EFC 00086ADC  90 01 00 58 */	stw r0, 0x58(r1)
/* 80089F00 00086AE0  80 C7 00 24 */	lwz r6, 0x24(r7)
/* 80089F04 00086AE4  80 07 00 28 */	lwz r0, 0x28(r7)
/* 80089F08 00086AE8  90 C1 00 5C */	stw r6, 0x5c(r1)
/* 80089F0C 00086AEC  90 01 00 60 */	stw r0, 0x60(r1)
/* 80089F10 00086AF0  80 E1 00 B8 */	lwz r7, 0xb8(r1)
/* 80089F14 00086AF4  80 C7 00 1C */	lwz r6, 0x1c(r7)
/* 80089F18 00086AF8  80 07 00 20 */	lwz r0, 0x20(r7)
/* 80089F1C 00086AFC  90 C1 00 44 */	stw r6, 0x44(r1)
/* 80089F20 00086B00  90 01 00 48 */	stw r0, 0x48(r1)
/* 80089F24 00086B04  80 C7 00 24 */	lwz r6, 0x24(r7)
/* 80089F28 00086B08  80 07 00 28 */	lwz r0, 0x28(r7)
/* 80089F2C 00086B0C  90 C1 00 4C */	stw r6, 0x4c(r1)
/* 80089F30 00086B10  90 01 00 50 */	stw r0, 0x50(r1)
/* 80089F34 00086B14  4B FF FA 59 */	bl func_8008998C
/* 80089F38 00086B18  2C 03 00 00 */	cmpwi r3, 0
/* 80089F3C 00086B1C  41 82 00 0C */	beq lbl_80089F48
/* 80089F40 00086B20  38 61 00 B0 */	addi r3, r1, 0xb0
/* 80089F44 00086B24  4B F9 74 CD */	bl func_80021410
lbl_80089F48:
/* 80089F48 00086B28  C0 22 8A 28 */	lfs f1, lbl_804D8408(r2)
/* 80089F4C 00086B2C  38 81 00 A4 */	addi r4, r1, 0xa4
/* 80089F50 00086B30  80 61 00 B8 */	lwz r3, 0xb8(r1)
/* 80089F54 00086B34  FC 40 08 90 */	fmr f2, f1
/* 80089F58 00086B38  C0 62 8A 30 */	lfs f3, lbl_804D8410(r2)
/* 80089F5C 00086B3C  4B F9 6E DD */	bl func_80020E38
/* 80089F60 00086B40  80 81 00 B0 */	lwz r4, 0xb0(r1)
/* 80089F64 00086B44  80 61 00 64 */	lwz r3, 0x64(r1)
/* 80089F68 00086B48  80 01 00 68 */	lwz r0, 0x68(r1)
/* 80089F6C 00086B4C  90 64 00 1C */	stw r3, 0x1c(r4)
/* 80089F70 00086B50  90 04 00 20 */	stw r0, 0x20(r4)
/* 80089F74 00086B54  80 61 00 6C */	lwz r3, 0x6c(r1)
/* 80089F78 00086B58  80 01 00 70 */	lwz r0, 0x70(r1)
/* 80089F7C 00086B5C  90 64 00 24 */	stw r3, 0x24(r4)
/* 80089F80 00086B60  90 04 00 28 */	stw r0, 0x28(r4)
/* 80089F84 00086B64  80 81 00 B4 */	lwz r4, 0xb4(r1)
/* 80089F88 00086B68  80 61 00 54 */	lwz r3, 0x54(r1)
/* 80089F8C 00086B6C  80 01 00 58 */	lwz r0, 0x58(r1)
/* 80089F90 00086B70  90 64 00 1C */	stw r3, 0x1c(r4)
/* 80089F94 00086B74  90 04 00 20 */	stw r0, 0x20(r4)
/* 80089F98 00086B78  80 61 00 5C */	lwz r3, 0x5c(r1)
/* 80089F9C 00086B7C  80 01 00 60 */	lwz r0, 0x60(r1)
/* 80089FA0 00086B80  90 64 00 24 */	stw r3, 0x24(r4)
/* 80089FA4 00086B84  90 04 00 28 */	stw r0, 0x28(r4)
/* 80089FA8 00086B88  80 81 00 B8 */	lwz r4, 0xb8(r1)
/* 80089FAC 00086B8C  80 61 00 44 */	lwz r3, 0x44(r1)
/* 80089FB0 00086B90  80 01 00 48 */	lwz r0, 0x48(r1)
/* 80089FB4 00086B94  90 64 00 1C */	stw r3, 0x1c(r4)
/* 80089FB8 00086B98  90 04 00 20 */	stw r0, 0x20(r4)
/* 80089FBC 00086B9C  80 61 00 4C */	lwz r3, 0x4c(r1)
/* 80089FC0 00086BA0  80 01 00 50 */	lwz r0, 0x50(r1)
/* 80089FC4 00086BA4  90 64 00 24 */	stw r3, 0x24(r4)
/* 80089FC8 00086BA8  90 04 00 28 */	stw r0, 0x28(r4)
lbl_80089FCC:
/* 80089FCC 00086BAC  A0 1F 22 1C */	lhz r0, 0x221c(r31)
/* 80089FD0 00086BB0  54 00 D7 7B */	rlwinm. r0, r0, 0x1a, 0x1d, 0x1d
/* 80089FD4 00086BB4  41 82 01 BC */	beq lbl_8008A190
/* 80089FD8 00086BB8  83 9F 08 3C */	lwz r28, 0x83c(r31)
/* 80089FDC 00086BBC  C0 3F 08 44 */	lfs f1, 0x844(r31)
/* 80089FE0 00086BC0  C0 5F 08 48 */	lfs f2, 0x848(r31)
/* 80089FE4 00086BC4  4B F9 8C 4D */	bl atan2f
/* 80089FE8 00086BC8  C0 1F 00 2C */	lfs f0, 0x2c(r31)
/* 80089FEC 00086BCC  38 7C 00 00 */	addi r3, r28, 0
/* 80089FF0 00086BD0  38 81 00 38 */	addi r4, r1, 0x38
/* 80089FF4 00086BD4  EF E0 00 72 */	fmuls f31, f0, f1
/* 80089FF8 00086BD8  4B FC AB 1D */	bl func_80054B14
/* 80089FFC 00086BDC  38 7C 00 00 */	addi r3, r28, 0
/* 8008A000 00086BE0  38 81 00 2C */	addi r4, r1, 0x2c
/* 8008A004 00086BE4  4B FC AB BD */	bl func_80054BC0
/* 8008A008 00086BE8  C0 21 00 3C */	lfs f1, 0x3c(r1)
/* 8008A00C 00086BEC  C0 01 00 30 */	lfs f0, 0x30(r1)
/* 8008A010 00086BF0  C0 41 00 38 */	lfs f2, 0x38(r1)
/* 8008A014 00086BF4  EC 61 00 28 */	fsubs f3, f1, f0
/* 8008A018 00086BF8  C0 21 00 2C */	lfs f1, 0x2c(r1)
/* 8008A01C 00086BFC  C0 02 8A 10 */	lfs f0, lbl_804D83F0(r2)
/* 8008A020 00086C00  EC 42 08 28 */	fsubs f2, f2, f1
/* 8008A024 00086C04  EC 23 00 F2 */	fmuls f1, f3, f3
/* 8008A028 00086C08  EC 82 08 BA */	fmadds f4, f2, f2, f1
/* 8008A02C 00086C0C  FC 04 00 40 */	fcmpo cr0, f4, f0
/* 8008A030 00086C10  40 81 00 50 */	ble lbl_8008A080
/* 8008A034 00086C14  FC 20 20 34 */	frsqrte f1, f4
/* 8008A038 00086C18  C8 62 8A 38 */	lfd f3, lbl_804D8418(r2)
/* 8008A03C 00086C1C  C8 42 8A 40 */	lfd f2, lbl_804D8420(r2)
/* 8008A040 00086C20  FC 01 00 72 */	fmul f0, f1, f1
/* 8008A044 00086C24  FC 23 00 72 */	fmul f1, f3, f1
/* 8008A048 00086C28  FC 04 10 3C */	fnmsub f0, f4, f0, f2
/* 8008A04C 00086C2C  FC 21 00 32 */	fmul f1, f1, f0
/* 8008A050 00086C30  FC 01 00 72 */	fmul f0, f1, f1
/* 8008A054 00086C34  FC 23 00 72 */	fmul f1, f3, f1
/* 8008A058 00086C38  FC 04 10 3C */	fnmsub f0, f4, f0, f2
/* 8008A05C 00086C3C  FC 21 00 32 */	fmul f1, f1, f0
/* 8008A060 00086C40  FC 01 00 72 */	fmul f0, f1, f1
/* 8008A064 00086C44  FC 23 00 72 */	fmul f1, f3, f1
/* 8008A068 00086C48  FC 04 10 3C */	fnmsub f0, f4, f0, f2
/* 8008A06C 00086C4C  FC 01 00 32 */	fmul f0, f1, f0
/* 8008A070 00086C50  FC 04 00 32 */	fmul f0, f4, f0
/* 8008A074 00086C54  FC 00 00 18 */	frsp f0, f0
/* 8008A078 00086C58  D0 01 00 18 */	stfs f0, 0x18(r1)
/* 8008A07C 00086C5C  C0 81 00 18 */	lfs f4, 0x18(r1)
lbl_8008A080:
/* 8008A080 00086C60  C0 02 8A 48 */	lfs f0, lbl_804D8428(r2)
/* 8008A084 00086C64  FC 04 00 40 */	fcmpo cr0, f4, f0
/* 8008A088 00086C68  40 80 00 C8 */	bge lbl_8008A150
/* 8008A08C 00086C6C  C3 C2 8A 10 */	lfs f30, lbl_804D83F0(r2)
/* 8008A090 00086C70  7F 83 E3 78 */	mr r3, r28
/* 8008A094 00086C74  4B FC 3A E5 */	bl func_8004DB78
/* 8008A098 00086C78  2C 03 FF FF */	cmpwi r3, -1
/* 8008A09C 00086C7C  3B A3 00 00 */	addi r29, r3, 0
/* 8008A0A0 00086C80  41 82 00 34 */	beq lbl_8008A0D4
/* 8008A0A4 00086C84  7F A3 EB 78 */	mr r3, r29
/* 8008A0A8 00086C88  4B FC AB C5 */	bl func_80054C6C
/* 8008A0AC 00086C8C  54 60 07 FF */	clrlwi. r0, r3, 0x1f
/* 8008A0B0 00086C90  41 82 00 24 */	beq lbl_8008A0D4
/* 8008A0B4 00086C94  38 7D 00 00 */	addi r3, r29, 0
/* 8008A0B8 00086C98  38 81 00 1C */	addi r4, r1, 0x1c
/* 8008A0BC 00086C9C  4B FC AD 41 */	bl func_80054DFC
/* 8008A0C0 00086CA0  C0 21 00 1C */	lfs f1, 0x1c(r1)
/* 8008A0C4 00086CA4  C0 41 00 20 */	lfs f2, 0x20(r1)
/* 8008A0C8 00086CA8  4B F9 8B 69 */	bl atan2f
/* 8008A0CC 00086CAC  C0 1F 00 2C */	lfs f0, 0x2c(r31)
/* 8008A0D0 00086CB0  EF C0 00 72 */	fmuls f30, f0, f1
lbl_8008A0D4:
/* 8008A0D4 00086CB4  7F 83 E3 78 */	mr r3, r28
/* 8008A0D8 00086CB8  4B FC 3B 2D */	bl func_8004DC04
/* 8008A0DC 00086CBC  2C 03 FF FF */	cmpwi r3, -1
/* 8008A0E0 00086CC0  3B 83 00 00 */	addi r28, r3, 0
/* 8008A0E4 00086CC4  41 82 00 3C */	beq lbl_8008A120
/* 8008A0E8 00086CC8  7F 83 E3 78 */	mr r3, r28
/* 8008A0EC 00086CCC  4B FC AB 81 */	bl func_80054C6C
/* 8008A0F0 00086CD0  54 60 07 FF */	clrlwi. r0, r3, 0x1f
/* 8008A0F4 00086CD4  41 82 00 2C */	beq lbl_8008A120
/* 8008A0F8 00086CD8  38 7C 00 00 */	addi r3, r28, 0
/* 8008A0FC 00086CDC  38 81 00 1C */	addi r4, r1, 0x1c
/* 8008A100 00086CE0  4B FC AC FD */	bl func_80054DFC
/* 8008A104 00086CE4  C0 21 00 1C */	lfs f1, 0x1c(r1)
/* 8008A108 00086CE8  C0 41 00 20 */	lfs f2, 0x20(r1)
/* 8008A10C 00086CEC  4B F9 8B 25 */	bl atan2f
/* 8008A110 00086CF0  C0 5F 00 2C */	lfs f2, 0x2c(r31)
/* 8008A114 00086CF4  C0 02 8A 4C */	lfs f0, lbl_804D842C(r2)
/* 8008A118 00086CF8  EC 22 F0 7A */	fmadds f1, f2, f1, f30
/* 8008A11C 00086CFC  EF C0 00 72 */	fmuls f30, f0, f1
lbl_8008A120:
/* 8008A120 00086D00  EC 3E F8 28 */	fsubs f1, f30, f31
/* 8008A124 00086D04  C0 02 8A 10 */	lfs f0, lbl_804D83F0(r2)
/* 8008A128 00086D08  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8008A12C 00086D0C  FC 00 08 90 */	fmr f0, f1
/* 8008A130 00086D10  40 80 00 0C */	bge lbl_8008A13C
/* 8008A134 00086D14  FC 20 00 50 */	fneg f1, f0
/* 8008A138 00086D18  48 00 00 08 */	b lbl_8008A140
lbl_8008A13C:
/* 8008A13C 00086D1C  FC 20 00 90 */	fmr f1, f0
lbl_8008A140:
/* 8008A140 00086D20  C0 02 8A 50 */	lfs f0, lbl_804D8430(r2)
/* 8008A144 00086D24  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8008A148 00086D28  40 81 00 08 */	ble lbl_8008A150
/* 8008A14C 00086D2C  FF E0 F0 90 */	fmr f31, f30
lbl_8008A150:
/* 8008A150 00086D30  80 6D AE B4 */	lwz r3, p_ftCommonData(r13)
/* 8008A154 00086D34  C0 22 8A 54 */	lfs f1, lbl_804D8434(r2)
/* 8008A158 00086D38  C0 03 08 04 */	lfs f0, 0x804(r3)
/* 8008A15C 00086D3C  EC 01 00 32 */	fmuls f0, f1, f0
/* 8008A160 00086D40  FC 1F 00 40 */	fcmpo cr0, f31, f0
/* 8008A164 00086D44  40 81 00 0C */	ble lbl_8008A170
/* 8008A168 00086D48  FF E0 00 90 */	fmr f31, f0
/* 8008A16C 00086D4C  48 00 00 14 */	b lbl_8008A180
lbl_8008A170:
/* 8008A170 00086D50  FC 00 00 50 */	fneg f0, f0
/* 8008A174 00086D54  FC 1F 00 40 */	fcmpo cr0, f31, f0
/* 8008A178 00086D58  40 80 00 08 */	bge lbl_8008A180
/* 8008A17C 00086D5C  FF E0 00 90 */	fmr f31, f0
lbl_8008A180:
/* 8008A180 00086D60  FC 20 F8 90 */	fmr f1, f31
/* 8008A184 00086D64  38 7F 00 00 */	addi r3, r31, 0
/* 8008A188 00086D68  38 80 00 00 */	li r4, 0
/* 8008A18C 00086D6C  4B FE B7 A1 */	bl func_8007592C
lbl_8008A190:
/* 8008A190 00086D70  80 01 01 34 */	lwz r0, 0x134(r1)
/* 8008A194 00086D74  CB E1 01 28 */	lfd f31, 0x128(r1)
/* 8008A198 00086D78  CB C1 01 20 */	lfd f30, 0x120(r1)
/* 8008A19C 00086D7C  83 E1 01 1C */	lwz r31, 0x11c(r1)
/* 8008A1A0 00086D80  83 C1 01 18 */	lwz r30, 0x118(r1)
/* 8008A1A4 00086D84  83 A1 01 14 */	lwz r29, 0x114(r1)
/* 8008A1A8 00086D88  83 81 01 10 */	lwz r28, 0x110(r1)
/* 8008A1AC 00086D8C  38 21 01 30 */	addi r1, r1, 0x130
/* 8008A1B0 00086D90  7C 08 03 A6 */	mtlr r0
/* 8008A1B4 00086D94  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

#pragma push
asm unk_t func_8008A1B8()
{ // clang-format off
    nofralloc
/* 8008A1B8 00086D98  7C 08 02 A6 */	mflr r0
/* 8008A1BC 00086D9C  90 01 00 04 */	stw r0, 4(r1)
/* 8008A1C0 00086DA0  54 80 07 7B */	rlwinm. r0, r4, 0, 0x1d, 0x1d
/* 8008A1C4 00086DA4  94 21 FF F8 */	stwu r1, -8(r1)
/* 8008A1C8 00086DA8  80 A3 00 2C */	lwz r5, 0x2c(r3)
/* 8008A1CC 00086DAC  A0 65 22 1C */	lhz r3, 0x221c(r5)
/* 8008A1D0 00086DB0  50 83 35 F2 */	rlwimi r3, r4, 6, 0x17, 0x19
/* 8008A1D4 00086DB4  B0 65 22 1C */	sth r3, 0x221c(r5)
/* 8008A1D8 00086DB8  7C A3 2B 78 */	mr r3, r5
/* 8008A1DC 00086DBC  40 82 00 10 */	bne lbl_8008A1EC
/* 8008A1E0 00086DC0  C0 22 8A 10 */	lfs f1, lbl_804D83F0(r2)
/* 8008A1E4 00086DC4  38 80 00 00 */	li r4, 0
/* 8008A1E8 00086DC8  4B FE B7 45 */	bl func_8007592C
lbl_8008A1EC:
/* 8008A1EC 00086DCC  80 01 00 0C */	lwz r0, 0xc(r1)
/* 8008A1F0 00086DD0  38 21 00 08 */	addi r1, r1, 8
/* 8008A1F4 00086DD4  7C 08 03 A6 */	mtlr r0
/* 8008A1F8 00086DD8  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

extern f32 const lbl_804D8438;

#pragma push
asm unk_t func_8008A1FC()
{ // clang-format off
    nofralloc
/* 8008A1FC 00086DDC  80 63 00 2C */	lwz r3, 0x2c(r3)
/* 8008A200 00086DE0  C0 02 8A 58 */	lfs f0, lbl_804D8438(r2)
/* 8008A204 00086DE4  C0 43 06 20 */	lfs f2, 0x620(r3)
/* 8008A208 00086DE8  C0 23 00 2C */	lfs f1, 0x2c(r3)
/* 8008A20C 00086DEC  EC 22 00 72 */	fmuls f1, f2, f1
/* 8008A210 00086DF0  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8008A214 00086DF4  41 80 00 20 */	blt lbl_8008A234
/* 8008A218 00086DF8  FC 02 00 40 */	fcmpo cr0, f2, f0
/* 8008A21C 00086DFC  40 80 00 08 */	bge lbl_8008A224
/* 8008A220 00086E00  FC 40 10 50 */	fneg f2, f2
lbl_8008A224:
/* 8008A224 00086E04  80 6D AE B4 */	lwz r3, p_ftCommonData(r13)
/* 8008A228 00086E08  C0 03 00 24 */	lfs f0, 0x24(r3)
/* 8008A22C 00086E0C  FC 02 00 40 */	fcmpo cr0, f2, f0
/* 8008A230 00086E10  40 80 00 0C */	bge lbl_8008A23C
lbl_8008A234:
/* 8008A234 00086E14  38 60 00 01 */	li r3, 1
/* 8008A238 00086E18  4E 80 00 20 */	blr 
lbl_8008A23C:
/* 8008A23C 00086E1C  38 60 00 00 */	li r3, 0
/* 8008A240 00086E20  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

#pragma push
asm unk_t func_8008A244()
{ // clang-format off
    nofralloc
/* 8008A244 00086E24  7C 08 02 A6 */	mflr r0
/* 8008A248 00086E28  90 01 00 04 */	stw r0, 4(r1)
/* 8008A24C 00086E2C  94 21 FF F8 */	stwu r1, -8(r1)
/* 8008A250 00086E30  80 83 00 2C */	lwz r4, 0x2c(r3)
/* 8008A254 00086E34  C0 02 8A 58 */	lfs f0, lbl_804D8438(r2)
/* 8008A258 00086E38  C0 44 06 20 */	lfs f2, 0x620(r4)
/* 8008A25C 00086E3C  C0 24 00 2C */	lfs f1, 0x2c(r4)
/* 8008A260 00086E40  EC 22 00 72 */	fmuls f1, f2, f1
/* 8008A264 00086E44  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8008A268 00086E48  41 80 00 20 */	blt lbl_8008A288
/* 8008A26C 00086E4C  FC 02 00 40 */	fcmpo cr0, f2, f0
/* 8008A270 00086E50  40 80 00 08 */	bge lbl_8008A278
/* 8008A274 00086E54  FC 40 10 50 */	fneg f2, f2
lbl_8008A278:
/* 8008A278 00086E58  80 8D AE B4 */	lwz r4, p_ftCommonData(r13)
/* 8008A27C 00086E5C  C0 04 00 24 */	lfs f0, 0x24(r4)
/* 8008A280 00086E60  FC 02 00 40 */	fcmpo cr0, f2, f0
/* 8008A284 00086E64  40 80 00 0C */	bge lbl_8008A290
lbl_8008A288:
/* 8008A288 00086E68  38 00 00 01 */	li r0, 1
/* 8008A28C 00086E6C  48 00 00 08 */	b lbl_8008A294
lbl_8008A290:
/* 8008A290 00086E70  38 00 00 00 */	li r0, 0
lbl_8008A294:
/* 8008A294 00086E74  2C 00 00 00 */	cmpwi r0, 0
/* 8008A298 00086E78  41 82 00 10 */	beq lbl_8008A2A8
/* 8008A29C 00086E7C  48 00 00 21 */	bl func_8008A2BC
/* 8008A2A0 00086E80  38 60 00 01 */	li r3, 1
/* 8008A2A4 00086E84  48 00 00 08 */	b lbl_8008A2AC
lbl_8008A2A8:
/* 8008A2A8 00086E88  38 60 00 00 */	li r3, 0
lbl_8008A2AC:
/* 8008A2AC 00086E8C  80 01 00 0C */	lwz r0, 0xc(r1)
/* 8008A2B0 00086E90  38 21 00 08 */	addi r1, r1, 8
/* 8008A2B4 00086E94  7C 08 03 A6 */	mtlr r0
/* 8008A2B8 00086E98  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

extern unk_t func_8008A348();
extern unk_t func_8015BC88();
extern unk_t func_8015BC88();

#pragma push
asm void func_8008A2BC(HSD_GObj* fighter_gobj)
{ // clang-format off
    nofralloc
/* 8008A2BC 00086E9C  7C 08 02 A6 */	mflr r0
/* 8008A2C0 00086EA0  90 01 00 04 */	stw r0, 4(r1)
/* 8008A2C4 00086EA4  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 8008A2C8 00086EA8  93 E1 00 14 */	stw r31, 0x14(r1)
/* 8008A2CC 00086EAC  7C 7F 1B 78 */	mr r31, r3
/* 8008A2D0 00086EB0  4B FF CF D5 */	bl func_800872A4
/* 8008A2D4 00086EB4  2C 03 00 1B */	cmpwi r3, 0x1b
/* 8008A2D8 00086EB8  40 82 00 10 */	bne lbl_8008A2E8
/* 8008A2DC 00086EBC  7F E3 FB 78 */	mr r3, r31
/* 8008A2E0 00086EC0  48 0C 6D 39 */	bl func_80151018
/* 8008A2E4 00086EC4  48 00 00 2C */	b lbl_8008A310
lbl_8008A2E8:
/* 8008A2E8 00086EC8  7F E3 FB 78 */	mr r3, r31
/* 8008A2EC 00086ECC  4B FF CF B9 */	bl func_800872A4
/* 8008A2F0 00086ED0  2C 03 00 1C */	cmpwi r3, 0x1c
/* 8008A2F4 00086ED4  40 82 00 10 */	bne lbl_8008A304
/* 8008A2F8 00086ED8  7F E3 FB 78 */	mr r3, r31
/* 8008A2FC 00086EDC  48 0D 19 8D */	bl func_8015BC88
/* 8008A300 00086EE0  48 00 00 10 */	b lbl_8008A310
lbl_8008A304:
/* 8008A304 00086EE4  7F E3 FB 78 */	mr r3, r31
/* 8008A308 00086EE8  C0 22 8A 58 */	lfs f1, lbl_804D8438(r2)
/* 8008A30C 00086EEC  48 00 00 3D */	bl func_8008A348
lbl_8008A310:
/* 8008A310 00086EF0  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 8008A314 00086EF4  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 8008A318 00086EF8  38 21 00 18 */	addi r1, r1, 0x18
/* 8008A31C 00086EFC  7C 08 03 A6 */	mtlr r0
/* 8008A320 00086F00  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

extern f32 const lbl_804D843C;

#pragma push
asm void func_8008A324(HSD_GObj* fighter_gobj)
{ // clang-format off
    nofralloc
/* 8008A324 00086F04  7C 08 02 A6 */	mflr r0
/* 8008A328 00086F08  90 01 00 04 */	stw r0, 4(r1)
/* 8008A32C 00086F0C  94 21 FF F8 */	stwu r1, -8(r1)
/* 8008A330 00086F10  C0 22 8A 5C */	lfs f1, lbl_804D843C(r2)
/* 8008A334 00086F14  48 00 00 15 */	bl func_8008A348
/* 8008A338 00086F18  80 01 00 0C */	lwz r0, 0xc(r1)
/* 8008A33C 00086F1C  38 21 00 08 */	addi r1, r1, 8
/* 8008A340 00086F20  7C 08 03 A6 */	mtlr r0
/* 8008A344 00086F24  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

extern f32 const lbl_804D8440;
extern unk_t func_800EB3BC();
extern unk_t func_8008A6D8();
extern unk_t func_80085FD4();
extern unk_t func_8008A698();
extern unk_t func_802BDB94();
extern unk_t func_800C4ED8();
extern BOOL func_800C5240(HSD_GObj* fighter_gobj);
extern unk_t func_800C8B74();

#pragma push
asm unk_t func_8008A348()
{ // clang-format off
    nofralloc
/* 8008A348 00086F28  7C 08 02 A6 */	mflr r0
/* 8008A34C 00086F2C  90 01 00 04 */	stw r0, 4(r1)
/* 8008A350 00086F30  94 21 FF D8 */	stwu r1, -0x28(r1)
/* 8008A354 00086F34  DB E1 00 20 */	stfd f31, 0x20(r1)
/* 8008A358 00086F38  FF E0 08 90 */	fmr f31, f1
/* 8008A35C 00086F3C  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 8008A360 00086F40  93 C1 00 18 */	stw r30, 0x18(r1)
/* 8008A364 00086F44  7C 7E 1B 78 */	mr r30, r3
/* 8008A368 00086F48  80 63 00 2C */	lwz r3, 0x2c(r3)
/* 8008A36C 00086F4C  88 03 22 24 */	lbz r0, 0x2224(r3)
/* 8008A370 00086F50  3B E3 00 00 */	addi r31, r3, 0
/* 8008A374 00086F54  54 00 DF FF */	rlwinm. r0, r0, 0x1b, 0x1f, 0x1f
/* 8008A378 00086F58  41 82 00 10 */	beq lbl_8008A388
/* 8008A37C 00086F5C  7F C3 F3 78 */	mr r3, r30
/* 8008A380 00086F60  48 03 E7 F5 */	bl func_800C8B74
/* 8008A384 00086F64  48 00 00 F4 */	b lbl_8008A478
lbl_8008A388:
/* 8008A388 00086F68  7F C3 F3 78 */	mr r3, r30
/* 8008A38C 00086F6C  48 03 AE B5 */	bl func_800C5240
/* 8008A390 00086F70  2C 03 00 00 */	cmpwi r3, 0
/* 8008A394 00086F74  41 82 00 10 */	beq lbl_8008A3A4
/* 8008A398 00086F78  7F C3 F3 78 */	mr r3, r30
/* 8008A39C 00086F7C  48 03 AB 3D */	bl func_800C4ED8
/* 8008A3A0 00086F80  48 00 00 D8 */	b lbl_8008A478
lbl_8008A3A4:
/* 8008A3A4 00086F84  80 1F 00 E0 */	lwz r0, 0xe0(r31)
/* 8008A3A8 00086F88  2C 00 00 01 */	cmpwi r0, 1
/* 8008A3AC 00086F8C  40 82 00 0C */	bne lbl_8008A3B8
/* 8008A3B0 00086F90  7F E3 FB 78 */	mr r3, r31
/* 8008A3B4 00086F94  4B FF 34 49 */	bl func_8007D7FC
lbl_8008A3B8:
/* 8008A3B8 00086F98  80 1F 00 04 */	lwz r0, 4(r31)
/* 8008A3BC 00086F9C  2C 00 00 09 */	cmpwi r0, 9
/* 8008A3C0 00086FA0  40 82 00 24 */	bne lbl_8008A3E4
/* 8008A3C4 00086FA4  80 7F 19 74 */	lwz r3, 0x1974(r31)
/* 8008A3C8 00086FA8  28 03 00 00 */	cmplwi r3, 0
/* 8008A3CC 00086FAC  41 82 00 18 */	beq lbl_8008A3E4
/* 8008A3D0 00086FB0  48 1E 0F 31 */	bl itGetKind
/* 8008A3D4 00086FB4  2C 03 00 67 */	cmpwi r3, 0x67
/* 8008A3D8 00086FB8  40 82 00 0C */	bne lbl_8008A3E4
/* 8008A3DC 00086FBC  80 7F 19 74 */	lwz r3, 0x1974(r31)
/* 8008A3E0 00086FC0  48 23 37 B5 */	bl func_802BDB94
lbl_8008A3E4:
/* 8008A3E4 00086FC4  FC 60 F8 90 */	fmr f3, f31
/* 8008A3E8 00086FC8  C0 22 8A 58 */	lfs f1, lbl_804D8438(r2)
/* 8008A3EC 00086FCC  C0 42 8A 60 */	lfs f2, lbl_804D8440(r2)
/* 8008A3F0 00086FD0  38 7E 00 00 */	addi r3, r30, 0
/* 8008A3F4 00086FD4  38 80 00 0E */	li r4, 0xe
/* 8008A3F8 00086FD8  38 A0 00 00 */	li r5, 0
/* 8008A3FC 00086FDC  38 C0 00 00 */	li r6, 0
/* 8008A400 00086FE0  4B FD EF AD */	bl Fighter_ActionStateChange_800693AC
/* 8008A404 00086FE4  7F E3 FB 78 */	mr r3, r31
/* 8008A408 00086FE8  48 00 02 91 */	bl func_8008A698
/* 8008A40C 00086FEC  2C 03 00 00 */	cmpwi r3, 0
/* 8008A410 00086FF0  41 82 00 28 */	beq lbl_8008A438
/* 8008A414 00086FF4  38 7F 00 00 */	addi r3, r31, 0
/* 8008A418 00086FF8  38 80 00 06 */	li r4, 6
/* 8008A41C 00086FFC  4B FF BB B9 */	bl func_80085FD4
/* 8008A420 00087000  80 03 00 08 */	lwz r0, 8(r3)
/* 8008A424 00087004  28 00 00 00 */	cmplwi r0, 0
/* 8008A428 00087008  41 82 00 10 */	beq lbl_8008A438
/* 8008A42C 0008700C  38 7E 00 00 */	addi r3, r30, 0
/* 8008A430 00087010  38 80 00 06 */	li r4, 6
/* 8008A434 00087014  48 00 02 A5 */	bl func_8008A6D8
lbl_8008A438:
/* 8008A438 00087018  80 8D AE B4 */	lwz r4, p_ftCommonData(r13)
/* 8008A43C 0008701C  7F E3 FB 78 */	mr r3, r31
/* 8008A440 00087020  80 84 05 F0 */	lwz r4, 0x5f0(r4)
/* 8008A444 00087024  4B FF 4B 7D */	bl func_8007EFC0
/* 8008A448 00087028  80 1F 00 04 */	lwz r0, 4(r31)
/* 8008A44C 0008702C  2C 00 00 14 */	cmpwi r0, 0x14
/* 8008A450 00087030  41 82 00 20 */	beq lbl_8008A470
/* 8008A454 00087034  40 80 00 24 */	bge lbl_8008A478
/* 8008A458 00087038  2C 00 00 06 */	cmpwi r0, 6
/* 8008A45C 0008703C  41 82 00 08 */	beq lbl_8008A464
/* 8008A460 00087040  48 00 00 18 */	b lbl_8008A478
lbl_8008A464:
/* 8008A464 00087044  7F C3 F3 78 */	mr r3, r30
/* 8008A468 00087048  48 06 0F 55 */	bl func_800EB3BC
/* 8008A46C 0008704C  48 00 00 0C */	b lbl_8008A478
lbl_8008A470:
/* 8008A470 00087050  7F C3 F3 78 */	mr r3, r30
/* 8008A474 00087054  48 0B ED 29 */	bl func_8014919C
lbl_8008A478:
/* 8008A478 00087058  80 01 00 2C */	lwz r0, 0x2c(r1)
/* 8008A47C 0008705C  CB E1 00 20 */	lfd f31, 0x20(r1)
/* 8008A480 00087060  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 8008A484 00087064  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 8008A488 00087068  38 21 00 28 */	addi r1, r1, 0x28
/* 8008A48C 0008706C  7C 08 03 A6 */	mtlr r0
/* 8008A490 00087070  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

extern unk_t func_8008A7A8();

#pragma push
asm unk_t func_8008A494()
{ // clang-format off
    nofralloc
/* 8008A494 00087074  7C 08 02 A6 */	mflr r0
/* 8008A498 00087078  90 01 00 04 */	stw r0, 4(r1)
/* 8008A49C 0008707C  94 21 FF F8 */	stwu r1, -8(r1)
/* 8008A4A0 00087080  80 83 00 2C */	lwz r4, 0x2c(r3)
/* 8008A4A4 00087084  88 04 22 24 */	lbz r0, 0x2224(r4)
/* 8008A4A8 00087088  54 00 DF FF */	rlwinm. r0, r0, 0x1b, 0x1f, 0x1f
/* 8008A4AC 0008708C  41 82 00 0C */	beq lbl_8008A4B8
/* 8008A4B0 00087090  48 03 E6 C5 */	bl func_800C8B74
/* 8008A4B4 00087094  48 00 00 10 */	b lbl_8008A4C4
lbl_8008A4B8:
/* 8008A4B8 00087098  80 84 01 0C */	lwz r4, 0x10c(r4)
/* 8008A4BC 0008709C  80 84 00 24 */	lwz r4, 0x24(r4)
/* 8008A4C0 000870A0  48 00 02 E9 */	bl func_8008A7A8
lbl_8008A4C4:
/* 8008A4C4 000870A4  80 01 00 0C */	lwz r0, 0xc(r1)
/* 8008A4C8 000870A8  38 21 00 08 */	addi r1, r1, 8
/* 8008A4CC 000870AC  7C 08 03 A6 */	mtlr r0
/* 8008A4D0 000870B0  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

extern unk_t func_800C9468();
extern unk_t func_800C97DC();
extern unk_t func_800D5FB0();
extern unk_t func_800CA094();
extern unk_t func_800CAED0();
extern unk_t func_80091A4C();
extern unk_t func_800DE9D8();
extern BOOL func_800D68C0(HSD_GObj* fighter_gobj);
extern BOOL func_800D6824(HSD_GObj* fighter_gobj);
extern BOOL func_800D695C(HSD_GObj* fighter_gobj);
extern BOOL func_80096540(HSD_GObj* fighter_gobj);

#pragma push
asm unk_t func_8008A4D4()
{ // clang-format off
    nofralloc
/* 8008A4D4 000870B4  7C 08 02 A6 */	mflr r0
/* 8008A4D8 000870B8  90 01 00 04 */	stw r0, 4(r1)
/* 8008A4DC 000870BC  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 8008A4E0 000870C0  93 E1 00 14 */	stw r31, 0x14(r1)
/* 8008A4E4 000870C4  7C 7F 1B 78 */	mr r31, r3
/* 8008A4E8 000870C8  48 00 C0 59 */	bl func_80096540
/* 8008A4EC 000870CC  2C 03 00 00 */	cmpwi r3, 0
/* 8008A4F0 000870D0  40 82 01 40 */	bne lbl_8008A630
/* 8008A4F4 000870D4  7F E3 FB 78 */	mr r3, r31
/* 8008A4F8 000870D8  48 04 C4 65 */	bl func_800D695C
/* 8008A4FC 000870DC  2C 03 00 00 */	cmpwi r3, 0
/* 8008A500 000870E0  40 82 01 30 */	bne lbl_8008A630
/* 8008A504 000870E4  7F E3 FB 78 */	mr r3, r31
/* 8008A508 000870E8  48 04 C3 1D */	bl func_800D6824
/* 8008A50C 000870EC  2C 03 00 00 */	cmpwi r3, 0
/* 8008A510 000870F0  40 82 01 20 */	bne lbl_8008A630
/* 8008A514 000870F4  7F E3 FB 78 */	mr r3, r31
/* 8008A518 000870F8  48 04 C3 A9 */	bl func_800D68C0
/* 8008A51C 000870FC  2C 03 00 00 */	cmpwi r3, 0
/* 8008A520 00087100  40 82 01 10 */	bne lbl_8008A630
/* 8008A524 00087104  7F E3 FB 78 */	mr r3, r31
/* 8008A528 00087108  48 04 E4 69 */	bl func_800D8990
/* 8008A52C 0008710C  2C 03 00 00 */	cmpwi r3, 0
/* 8008A530 00087110  40 82 01 00 */	bne lbl_8008A630
/* 8008A534 00087114  7F E3 FB 78 */	mr r3, r31
/* 8008A538 00087118  48 00 1A 8D */	bl func_8008BFC4
/* 8008A53C 0008711C  2C 03 00 00 */	cmpwi r3, 0
/* 8008A540 00087120  40 82 00 F0 */	bne lbl_8008A630
/* 8008A544 00087124  7F E3 FB 78 */	mr r3, r31
/* 8008A548 00087128  48 00 22 E9 */	bl func_8008C830
/* 8008A54C 0008712C  2C 03 00 00 */	cmpwi r3, 0
/* 8008A550 00087130  40 82 00 E0 */	bne lbl_8008A630
/* 8008A554 00087134  7F E3 FB 78 */	mr r3, r31
/* 8008A558 00087138  48 00 25 ED */	bl func_8008CB44
/* 8008A55C 0008713C  2C 03 00 00 */	cmpwi r3, 0
/* 8008A560 00087140  40 82 00 D0 */	bne lbl_8008A630
/* 8008A564 00087144  7F E3 FB 78 */	mr r3, r31
/* 8008A568 00087148  48 00 10 F1 */	bl func_8008B658
/* 8008A56C 0008714C  2C 03 00 00 */	cmpwi r3, 0
/* 8008A570 00087150  40 82 00 C0 */	bne lbl_8008A630
/* 8008A574 00087154  7F E3 FB 78 */	mr r3, r31
/* 8008A578 00087158  48 00 14 09 */	bl func_8008B980
/* 8008A57C 0008715C  2C 03 00 00 */	cmpwi r3, 0
/* 8008A580 00087160  40 82 00 B0 */	bne lbl_8008A630
/* 8008A584 00087164  7F E3 FB 78 */	mr r3, r31
/* 8008A588 00087168  48 00 15 BD */	bl func_8008BB44
/* 8008A58C 0008716C  2C 03 00 00 */	cmpwi r3, 0
/* 8008A590 00087170  40 82 00 A0 */	bne lbl_8008A630
/* 8008A594 00087174  7F E3 FB 78 */	mr r3, r31
/* 8008A598 00087178  48 00 04 61 */	bl func_8008A9F8
/* 8008A59C 0008717C  2C 03 00 00 */	cmpwi r3, 0
/* 8008A5A0 00087180  40 82 00 90 */	bne lbl_8008A630
/* 8008A5A4 00087184  7F E3 FB 78 */	mr r3, r31
/* 8008A5A8 00087188  48 00 F1 ED */	bl func_80099794
/* 8008A5AC 0008718C  2C 03 00 00 */	cmpwi r3, 0
/* 8008A5B0 00087190  40 82 00 80 */	bne lbl_8008A630
/* 8008A5B4 00087194  7F E3 FB 78 */	mr r3, r31
/* 8008A5B8 00087198  48 00 74 95 */	bl func_80091A4C
/* 8008A5BC 0008719C  2C 03 00 00 */	cmpwi r3, 0
/* 8008A5C0 000871A0  40 82 00 70 */	bne lbl_8008A630
/* 8008A5C4 000871A4  7F E3 FB 78 */	mr r3, r31
/* 8008A5C8 000871A8  48 05 B3 F5 */	bl ftFox_AppealS_CheckInput
/* 8008A5CC 000871AC  2C 03 00 00 */	cmpwi r3, 0
/* 8008A5D0 000871B0  40 82 00 60 */	bne lbl_8008A630
/* 8008A5D4 000871B4  7F E3 FB 78 */	mr r3, r31
/* 8008A5D8 000871B8  48 05 44 01 */	bl func_800DE9D8
/* 8008A5DC 000871BC  2C 03 00 00 */	cmpwi r3, 0
/* 8008A5E0 000871C0  40 82 00 50 */	bne lbl_8008A630
/* 8008A5E4 000871C4  7F E3 FB 78 */	mr r3, r31
/* 8008A5E8 000871C8  48 04 08 E9 */	bl func_800CAED0
/* 8008A5EC 000871CC  2C 03 00 00 */	cmpwi r3, 0
/* 8008A5F0 000871D0  40 82 00 40 */	bne lbl_8008A630
/* 8008A5F4 000871D4  7F E3 FB 78 */	mr r3, r31
/* 8008A5F8 000871D8  48 03 FA 9D */	bl func_800CA094
/* 8008A5FC 000871DC  2C 03 00 00 */	cmpwi r3, 0
/* 8008A600 000871E0  40 82 00 30 */	bne lbl_8008A630
/* 8008A604 000871E4  7F E3 FB 78 */	mr r3, r31
/* 8008A608 000871E8  48 04 B9 A9 */	bl func_800D5FB0
/* 8008A60C 000871EC  2C 03 00 00 */	cmpwi r3, 0
/* 8008A610 000871F0  40 82 00 20 */	bne lbl_8008A630
/* 8008A614 000871F4  7F E3 FB 78 */	mr r3, r31
/* 8008A618 000871F8  48 03 F1 C5 */	bl func_800C97DC
/* 8008A61C 000871FC  2C 03 00 00 */	cmpwi r3, 0
/* 8008A620 00087200  40 82 00 10 */	bne lbl_8008A630
/* 8008A624 00087204  7F E3 FB 78 */	mr r3, r31
/* 8008A628 00087208  48 03 EE 41 */	bl func_800C9468
/* 8008A62C 0008720C  2C 03 00 00 */	cmpwi r3, 0
lbl_8008A630:
/* 8008A630 00087210  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 8008A634 00087214  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 8008A638 00087218  38 21 00 18 */	addi r1, r1, 0x18
/* 8008A63C 0008721C  7C 08 03 A6 */	mtlr r0
/* 8008A640 00087220  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

void func_80084F3C(HSD_GObj* fighter_gobj);

#pragma push
asm unk_t func_8008A644()
{ // clang-format off
    nofralloc
/* 8008A644 00087224  7C 08 02 A6 */	mflr r0
/* 8008A648 00087228  90 01 00 04 */	stw r0, 4(r1)
/* 8008A64C 0008722C  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 8008A650 00087230  93 E1 00 14 */	stw r31, 0x14(r1)
/* 8008A654 00087234  7C 7F 1B 78 */	mr r31, r3
/* 8008A658 00087238  4B FF A8 E5 */	bl func_80084F3C
/* 8008A65C 0008723C  7F E3 FB 78 */	mr r3, r31
/* 8008A660 00087240  4B FF 08 81 */	bl func_8007AEE0
/* 8008A664 00087244  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 8008A668 00087248  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 8008A66C 0008724C  38 21 00 18 */	addi r1, r1, 0x18
/* 8008A670 00087250  7C 08 03 A6 */	mtlr r0
/* 8008A674 00087254  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

extern void func_80084280(HSD_GObj* fighter_gobj);

#pragma push
asm unk_t func_8008A678()
{ // clang-format off
    nofralloc
/* 8008A678 00087258  7C 08 02 A6 */	mflr r0
/* 8008A67C 0008725C  90 01 00 04 */	stw r0, 4(r1)
/* 8008A680 00087260  94 21 FF F8 */	stwu r1, -8(r1)
/* 8008A684 00087264  4B FF 9B FD */	bl func_80084280
/* 8008A688 00087268  80 01 00 0C */	lwz r0, 0xc(r1)
/* 8008A68C 0008726C  38 21 00 08 */	addi r1, r1, 8
/* 8008A690 00087270  7C 08 03 A6 */	mtlr r0
/* 8008A694 00087274  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

#pragma push
asm unk_t func_8008A698()
{ // clang-format off
    nofralloc
/* 8008A698 00087278  7C 08 02 A6 */	mflr r0
/* 8008A69C 0008727C  90 01 00 04 */	stw r0, 4(r1)
/* 8008A6A0 00087280  94 21 FF F8 */	stwu r1, -8(r1)
/* 8008A6A4 00087284  80 63 19 74 */	lwz r3, 0x1974(r3)
/* 8008A6A8 00087288  28 03 00 00 */	cmplwi r3, 0
/* 8008A6AC 0008728C  41 82 00 18 */	beq lbl_8008A6C4
/* 8008A6B0 00087290  48 1E 0C 71 */	bl func_8026B320
/* 8008A6B4 00087294  2C 03 00 02 */	cmpwi r3, 2
/* 8008A6B8 00087298  41 82 00 0C */	beq lbl_8008A6C4
/* 8008A6BC 0008729C  38 60 00 01 */	li r3, 1
/* 8008A6C0 000872A0  48 00 00 08 */	b lbl_8008A6C8
lbl_8008A6C4:
/* 8008A6C4 000872A4  38 60 00 00 */	li r3, 0
lbl_8008A6C8:
/* 8008A6C8 000872A8  80 01 00 0C */	lwz r0, 0xc(r1)
/* 8008A6CC 000872AC  38 21 00 08 */	addi r1, r1, 8
/* 8008A6D0 000872B0  7C 08 03 A6 */	mtlr r0
/* 8008A6D4 000872B4  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

extern f32 const lbl_804D8448;
extern f32 const lbl_804D844C;
extern f64 const lbl_804D8450;

#pragma push
asm unk_t func_8008A6D8()
{ // clang-format off
    nofralloc
/* 8008A6D8 000872B8  7C 08 02 A6 */	mflr r0
/* 8008A6DC 000872BC  90 01 00 04 */	stw r0, 4(r1)
/* 8008A6E0 000872C0  94 21 FF C8 */	stwu r1, -0x38(r1)
/* 8008A6E4 000872C4  BF 61 00 24 */	stmw r27, 0x24(r1)
/* 8008A6E8 000872C8  3B 84 00 00 */	addi r28, r4, 0
/* 8008A6EC 000872CC  2C 1C FF FF */	cmpwi r28, -1
/* 8008A6F0 000872D0  3B 63 00 00 */	addi r27, r3, 0
/* 8008A6F4 000872D4  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 8008A6F8 000872D8  41 82 00 9C */	beq lbl_8008A794
/* 8008A6FC 000872DC  1C FC 00 18 */	mulli r7, r28, 0x18
/* 8008A700 000872E0  81 1F 00 24 */	lwz r8, 0x24(r31)
/* 8008A704 000872E4  80 DF 00 28 */	lwz r6, 0x28(r31)
/* 8008A708 000872E8  57 80 08 3C */	slwi r0, r28, 1
/* 8008A70C 000872EC  38 7F 00 00 */	addi r3, r31, 0
/* 8008A710 000872F0  38 9F 00 00 */	addi r4, r31, 0
/* 8008A714 000872F4  38 BC 00 00 */	addi r5, r28, 0
/* 8008A718 000872F8  7F C8 3A 14 */	add r30, r8, r7
/* 8008A71C 000872FC  7F A6 02 14 */	add r29, r6, r0
/* 8008A720 00087300  4B FF B5 B9 */	bl func_80085CD8
/* 8008A724 00087304  93 9F 00 14 */	stw r28, 0x14(r31)
/* 8008A728 00087308  38 7F 00 00 */	addi r3, r31, 0
/* 8008A72C 0008730C  38 9D 00 00 */	addi r4, r29, 0
/* 8008A730 00087310  48 01 40 85 */	bl func_8009E7B4
/* 8008A734 00087314  80 7E 00 0C */	lwz r3, 0xc(r30)
/* 8008A738 00087318  38 00 00 00 */	li r0, 0
/* 8008A73C 0008731C  90 7F 03 EC */	stw r3, 0x3ec(r31)
/* 8008A740 00087320  90 1F 03 F0 */	stw r0, 0x3f0(r31)
/* 8008A744 00087324  80 1F 05 90 */	lwz r0, 0x590(r31)
/* 8008A748 00087328  28 00 00 00 */	cmplwi r0, 0
/* 8008A74C 0008732C  41 82 00 38 */	beq lbl_8008A784
/* 8008A750 00087330  80 9E 00 10 */	lwz r4, 0x10(r30)
/* 8008A754 00087334  3C 00 43 30 */	lis r0, 0x4330
/* 8008A758 00087338  38 7B 00 00 */	addi r3, r27, 0
/* 8008A75C 0008733C  90 9F 05 94 */	stw r4, 0x594(r31)
/* 8008A760 00087340  88 9D 00 00 */	lbz r4, 0(r29)
/* 8008A764 00087344  C8 62 8A 70 */	lfd f3, lbl_804D8450(r2)
/* 8008A768 00087348  90 81 00 1C */	stw r4, 0x1c(r1)
/* 8008A76C 0008734C  C0 22 8A 68 */	lfs f1, lbl_804D8448(r2)
/* 8008A770 00087350  90 01 00 18 */	stw r0, 0x18(r1)
/* 8008A774 00087354  C0 42 8A 6C */	lfs f2, lbl_804D844C(r2)
/* 8008A778 00087358  C8 01 00 18 */	lfd f0, 0x18(r1)
/* 8008A77C 0008735C  EC 60 18 28 */	fsubs f3, f0, f3
/* 8008A780 00087360  4B FE 44 69 */	bl func_8006EBE8
lbl_8008A784:
/* 8008A784 00087364  C0 02 8A 68 */	lfs f0, lbl_804D8448(r2)
/* 8008A788 00087368  7F 63 DB 78 */	mr r3, r27
/* 8008A78C 0008736C  D0 1F 03 E4 */	stfs f0, 0x3e4(r31)
/* 8008A790 00087370  4B FE 44 15 */	bl func_8006EBA4
lbl_8008A794:
/* 8008A794 00087374  BB 61 00 24 */	lmw r27, 0x24(r1)
/* 8008A798 00087378  80 01 00 3C */	lwz r0, 0x3c(r1)
/* 8008A79C 0008737C  38 21 00 38 */	addi r1, r1, 0x38
/* 8008A7A0 00087380  7C 08 03 A6 */	mtlr r0
/* 8008A7A4 00087384  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

extern char* lbl_803C54A8;
extern char* lbl_803C54C4;
extern char* lbl_804D3AE0;

#pragma push
asm unk_t func_8008A7A8()
{ // clang-format off
    nofralloc
/* 8008A7A8 00087388  7C 08 02 A6 */	mflr r0
/* 8008A7AC 0008738C  90 01 00 04 */	stw r0, 4(r1)
/* 8008A7B0 00087390  94 21 FF B8 */	stwu r1, -0x48(r1)
/* 8008A7B4 00087394  BF 21 00 2C */	stmw r25, 0x2c(r1)
/* 8008A7B8 00087398  7C 7D 1B 78 */	mr r29, r3
/* 8008A7BC 0008739C  7C 9E 23 78 */	mr r30, r4
/* 8008A7C0 000873A0  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 8008A7C4 000873A4  4B FE 4A 75 */	bl ftAnim_IsFramesRemaining
/* 8008A7C8 000873A8  2C 03 00 00 */	cmpwi r3, 0
/* 8008A7CC 000873AC  40 82 02 18 */	bne lbl_8008A9E4
/* 8008A7D0 000873B0  28 1E 00 00 */	cmplwi r30, 0
/* 8008A7D4 000873B4  41 82 00 24 */	beq lbl_8008A7F8
/* 8008A7D8 000873B8  80 1F 19 74 */	lwz r0, 0x1974(r31)
/* 8008A7DC 000873BC  28 00 00 00 */	cmplwi r0, 0
/* 8008A7E0 000873C0  41 82 00 C4 */	beq lbl_8008A8A4
/* 8008A7E4 000873C4  80 1F 00 04 */	lwz r0, 4(r31)
/* 8008A7E8 000873C8  2C 00 00 10 */	cmpwi r0, 0x10
/* 8008A7EC 000873CC  41 82 00 B8 */	beq lbl_8008A8A4
/* 8008A7F0 000873D0  2C 00 00 01 */	cmpwi r0, 1
/* 8008A7F4 000873D4  41 82 00 B0 */	beq lbl_8008A8A4
lbl_8008A7F8:
/* 8008A7F8 000873D8  83 FF 00 14 */	lwz r31, 0x14(r31)
/* 8008A7FC 000873DC  83 DD 00 2C */	lwz r30, 0x2c(r29)
/* 8008A800 000873E0  2C 1F FF FF */	cmpwi r31, -1
/* 8008A804 000873E4  41 82 01 E0 */	beq lbl_8008A9E4
/* 8008A808 000873E8  1C FF 00 18 */	mulli r7, r31, 0x18
/* 8008A80C 000873EC  81 1E 00 24 */	lwz r8, 0x24(r30)
/* 8008A810 000873F0  80 DE 00 28 */	lwz r6, 0x28(r30)
/* 8008A814 000873F4  57 E0 08 3C */	slwi r0, r31, 1
/* 8008A818 000873F8  38 7E 00 00 */	addi r3, r30, 0
/* 8008A81C 000873FC  38 9E 00 00 */	addi r4, r30, 0
/* 8008A820 00087400  38 BF 00 00 */	addi r5, r31, 0
/* 8008A824 00087404  7F 88 3A 14 */	add r28, r8, r7
/* 8008A828 00087408  7F 66 02 14 */	add r27, r6, r0
/* 8008A82C 0008740C  4B FF B4 AD */	bl func_80085CD8
/* 8008A830 00087410  93 FE 00 14 */	stw r31, 0x14(r30)
/* 8008A834 00087414  38 7E 00 00 */	addi r3, r30, 0
/* 8008A838 00087418  38 9B 00 00 */	addi r4, r27, 0
/* 8008A83C 0008741C  48 01 3F 79 */	bl func_8009E7B4
/* 8008A840 00087420  80 7C 00 0C */	lwz r3, 0xc(r28)
/* 8008A844 00087424  38 00 00 00 */	li r0, 0
/* 8008A848 00087428  90 7E 03 EC */	stw r3, 0x3ec(r30)
/* 8008A84C 0008742C  90 1E 03 F0 */	stw r0, 0x3f0(r30)
/* 8008A850 00087430  80 1E 05 90 */	lwz r0, 0x590(r30)
/* 8008A854 00087434  28 00 00 00 */	cmplwi r0, 0
/* 8008A858 00087438  41 82 00 38 */	beq lbl_8008A890
/* 8008A85C 0008743C  80 9C 00 10 */	lwz r4, 0x10(r28)
/* 8008A860 00087440  3C 00 43 30 */	lis r0, 0x4330
/* 8008A864 00087444  38 7D 00 00 */	addi r3, r29, 0
/* 8008A868 00087448  90 9E 05 94 */	stw r4, 0x594(r30)
/* 8008A86C 0008744C  88 9B 00 00 */	lbz r4, 0(r27)
/* 8008A870 00087450  C8 62 8A 70 */	lfd f3, lbl_804D8450(r2)
/* 8008A874 00087454  90 81 00 24 */	stw r4, 0x24(r1)
/* 8008A878 00087458  C0 22 8A 68 */	lfs f1, lbl_804D8448(r2)
/* 8008A87C 0008745C  90 01 00 20 */	stw r0, 0x20(r1)
/* 8008A880 00087460  C0 42 8A 6C */	lfs f2, lbl_804D844C(r2)
/* 8008A884 00087464  C8 01 00 20 */	lfd f0, 0x20(r1)
/* 8008A888 00087468  EC 60 18 28 */	fsubs f3, f0, f3
/* 8008A88C 0008746C  4B FE 43 5D */	bl func_8006EBE8
lbl_8008A890:
/* 8008A890 00087470  C0 02 8A 68 */	lfs f0, lbl_804D8448(r2)
/* 8008A894 00087474  7F A3 EB 78 */	mr r3, r29
/* 8008A898 00087478  D0 1E 03 E4 */	stfs f0, 0x3e4(r30)
/* 8008A89C 0008747C  4B FE 43 09 */	bl func_8006EBA4
/* 8008A8A0 00087480  48 00 01 44 */	b lbl_8008A9E4
lbl_8008A8A4:
/* 8008A8A4 00087484  3C 80 80 3C */	lis r4, lbl_803C54A8@ha
/* 8008A8A8 00087488  3C 60 80 3C */	lis r3, lbl_803C54C4@ha
/* 8008A8AC 0008748C  3B 64 54 A8 */	addi r27, r4, lbl_803C54A8@l
/* 8008A8B0 00087490  3B 83 54 C4 */	addi r28, r3, lbl_803C54C4@l
lbl_8008A8B4:
/* 8008A8B4 00087494  3B 3E 00 00 */	addi r25, r30, 0
/* 8008A8B8 00087498  38 60 00 64 */	li r3, 0x64
/* 8008A8BC 0008749C  48 2F 5C C5 */	bl HSD_Randi
/* 8008A8C0 000874A0  38 83 00 01 */	addi r4, r3, 1
/* 8008A8C4 000874A4  38 60 00 00 */	li r3, 0
/* 8008A8C8 000874A8  48 00 00 20 */	b lbl_8008A8E8
lbl_8008A8CC:
/* 8008A8CC 000874AC  80 19 00 04 */	lwz r0, 4(r25)
/* 8008A8D0 000874B0  7C 63 02 14 */	add r3, r3, r0
/* 8008A8D4 000874B4  7C 04 18 00 */	cmpw r4, r3
/* 8008A8D8 000874B8  41 81 00 0C */	bgt lbl_8008A8E4
/* 8008A8DC 000874BC  83 59 00 00 */	lwz r26, 0(r25)
/* 8008A8E0 000874C0  48 00 00 30 */	b lbl_8008A910
lbl_8008A8E4:
/* 8008A8E4 000874C4  3B 39 00 08 */	addi r25, r25, 8
lbl_8008A8E8:
/* 8008A8E8 000874C8  80 19 00 00 */	lwz r0, 0(r25)
/* 8008A8EC 000874CC  2C 00 FF FF */	cmpwi r0, -1
/* 8008A8F0 000874D0  40 82 FF DC */	bne lbl_8008A8CC
/* 8008A8F4 000874D4  38 7B 00 00 */	addi r3, r27, 0
/* 8008A8F8 000874D8  4C C6 31 82 */	crclr 6
/* 8008A8FC 000874DC  48 2B AD AD */	bl OSReport
/* 8008A900 000874E0  38 7C 00 00 */	addi r3, r28, 0
/* 8008A904 000874E4  38 80 00 56 */	li r4, 0x56
/* 8008A908 000874E8  38 AD 84 40 */	addi r5, r13, lbl_804D3AE0
/* 8008A90C 000874EC  48 2F D9 15 */	bl __assert
lbl_8008A910:
/* 8008A910 000874F0  80 7F 00 14 */	lwz r3, 0x14(r31)
/* 8008A914 000874F4  38 BA 00 00 */	addi r5, r26, 0
/* 8008A918 000874F8  2C 03 00 02 */	cmpwi r3, 2
/* 8008A91C 000874FC  41 82 00 0C */	beq lbl_8008A928
/* 8008A920 00087500  2C 03 00 1F */	cmpwi r3, 0x1f
/* 8008A924 00087504  40 82 00 0C */	bne lbl_8008A930
lbl_8008A928:
/* 8008A928 00087508  38 00 00 01 */	li r0, 1
/* 8008A92C 0008750C  48 00 00 08 */	b lbl_8008A934
lbl_8008A930:
/* 8008A930 00087510  38 00 00 00 */	li r0, 0
lbl_8008A934:
/* 8008A934 00087514  2C 00 00 00 */	cmpwi r0, 0
/* 8008A938 00087518  40 82 00 0C */	bne lbl_8008A944
/* 8008A93C 0008751C  7C 03 28 00 */	cmpw r3, r5
/* 8008A940 00087520  41 82 FF 74 */	beq lbl_8008A8B4
lbl_8008A944:
/* 8008A944 00087524  2C 05 FF FF */	cmpwi r5, -1
/* 8008A948 00087528  83 9D 00 2C */	lwz r28, 0x2c(r29)
/* 8008A94C 0008752C  41 82 00 98 */	beq lbl_8008A9E4
/* 8008A950 00087530  1C E5 00 18 */	mulli r7, r5, 0x18
/* 8008A954 00087534  81 1C 00 24 */	lwz r8, 0x24(r28)
/* 8008A958 00087538  80 DC 00 28 */	lwz r6, 0x28(r28)
/* 8008A95C 0008753C  54 A0 08 3C */	slwi r0, r5, 1
/* 8008A960 00087540  38 7C 00 00 */	addi r3, r28, 0
/* 8008A964 00087544  38 9C 00 00 */	addi r4, r28, 0
/* 8008A968 00087548  7F 68 3A 14 */	add r27, r8, r7
/* 8008A96C 0008754C  7F 26 02 14 */	add r25, r6, r0
/* 8008A970 00087550  4B FF B3 69 */	bl func_80085CD8
/* 8008A974 00087554  93 5C 00 14 */	stw r26, 0x14(r28)
/* 8008A978 00087558  38 7C 00 00 */	addi r3, r28, 0
/* 8008A97C 0008755C  38 99 00 00 */	addi r4, r25, 0
/* 8008A980 00087560  48 01 3E 35 */	bl func_8009E7B4
/* 8008A984 00087564  80 7B 00 0C */	lwz r3, 0xc(r27)
/* 8008A988 00087568  38 00 00 00 */	li r0, 0
/* 8008A98C 0008756C  90 7C 03 EC */	stw r3, 0x3ec(r28)
/* 8008A990 00087570  90 1C 03 F0 */	stw r0, 0x3f0(r28)
/* 8008A994 00087574  80 1C 05 90 */	lwz r0, 0x590(r28)
/* 8008A998 00087578  28 00 00 00 */	cmplwi r0, 0
/* 8008A99C 0008757C  41 82 00 38 */	beq lbl_8008A9D4
/* 8008A9A0 00087580  80 9B 00 10 */	lwz r4, 0x10(r27)
/* 8008A9A4 00087584  3C 00 43 30 */	lis r0, 0x4330
/* 8008A9A8 00087588  38 7D 00 00 */	addi r3, r29, 0
/* 8008A9AC 0008758C  90 9C 05 94 */	stw r4, 0x594(r28)
/* 8008A9B0 00087590  88 99 00 00 */	lbz r4, 0(r25)
/* 8008A9B4 00087594  C8 62 8A 70 */	lfd f3, lbl_804D8450(r2)
/* 8008A9B8 00087598  90 81 00 24 */	stw r4, 0x24(r1)
/* 8008A9BC 0008759C  C0 22 8A 68 */	lfs f1, lbl_804D8448(r2)
/* 8008A9C0 000875A0  90 01 00 20 */	stw r0, 0x20(r1)
/* 8008A9C4 000875A4  C0 42 8A 6C */	lfs f2, lbl_804D844C(r2)
/* 8008A9C8 000875A8  C8 01 00 20 */	lfd f0, 0x20(r1)
/* 8008A9CC 000875AC  EC 60 18 28 */	fsubs f3, f0, f3
/* 8008A9D0 000875B0  4B FE 42 19 */	bl func_8006EBE8
lbl_8008A9D4:
/* 8008A9D4 000875B4  C0 02 8A 68 */	lfs f0, lbl_804D8448(r2)
/* 8008A9D8 000875B8  7F A3 EB 78 */	mr r3, r29
/* 8008A9DC 000875BC  D0 1C 03 E4 */	stfs f0, 0x3e4(r28)
/* 8008A9E0 000875C0  4B FE 41 C5 */	bl func_8006EBA4
lbl_8008A9E4:
/* 8008A9E4 000875C4  BB 21 00 2C */	lmw r25, 0x2c(r1)
/* 8008A9E8 000875C8  80 01 00 4C */	lwz r0, 0x4c(r1)
/* 8008A9EC 000875CC  38 21 00 48 */	addi r1, r1, 0x48
/* 8008A9F0 000875D0  7C 08 03 A6 */	mtlr r0
/* 8008A9F4 000875D4  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

extern f32 const lbl_804D8458;
extern f32 const lbl_804D845C;
extern unk_t func_8008AB84();
extern unk_t func_8008B194();
extern unk_t func_8008AE30();
extern unk_t func_800CDD14();
extern unk_t func_800CCF58();
extern unk_t func_800957F4();

#pragma push
asm BOOL func_8008A9F8(HSD_GObj* fighter_gobj)
{ // clang-format off
    nofralloc
/* 8008A9F8 000875D8  7C 08 02 A6 */	mflr r0
/* 8008A9FC 000875DC  90 01 00 04 */	stw r0, 4(r1)
/* 8008AA00 000875E0  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 8008AA04 000875E4  93 E1 00 14 */	stw r31, 0x14(r1)
/* 8008AA08 000875E8  93 C1 00 10 */	stw r30, 0x10(r1)
/* 8008AA0C 000875EC  7C 7E 1B 78 */	mr r30, r3
/* 8008AA10 000875F0  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 8008AA14 000875F4  80 1F 06 68 */	lwz r0, 0x668(r31)
/* 8008AA18 000875F8  54 00 05 EF */	rlwinm. r0, r0, 0, 0x17, 0x17
/* 8008AA1C 000875FC  41 82 00 FC */	beq lbl_8008AB18
/* 8008AA20 00087600  80 7F 19 74 */	lwz r3, 0x1974(r31)
/* 8008AA24 00087604  28 03 00 00 */	cmplwi r3, 0
/* 8008AA28 00087608  41 82 00 88 */	beq lbl_8008AAB0
/* 8008AA2C 0008760C  48 1E 08 E1 */	bl func_8026B30C
/* 8008AA30 00087610  2C 03 00 00 */	cmpwi r3, 0
/* 8008AA34 00087614  40 82 00 18 */	bne lbl_8008AA4C
/* 8008AA38 00087618  38 7E 00 00 */	addi r3, r30, 0
/* 8008AA3C 0008761C  38 80 00 5E */	li r4, 0x5e
/* 8008AA40 00087620  48 00 AD B5 */	bl func_800957F4
/* 8008AA44 00087624  38 60 00 01 */	li r3, 1
/* 8008AA48 00087628  48 00 00 F0 */	b lbl_8008AB38
lbl_8008AA4C:
/* 8008AA4C 0008762C  80 1F 06 5C */	lwz r0, 0x65c(r31)
/* 8008AA50 00087630  54 00 00 01 */	rlwinm. r0, r0, 0, 0, 0
/* 8008AA54 00087634  41 82 00 18 */	beq lbl_8008AA6C
/* 8008AA58 00087638  38 7E 00 00 */	addi r3, r30, 0
/* 8008AA5C 0008763C  38 80 00 63 */	li r4, 0x63
/* 8008AA60 00087640  48 00 AD 95 */	bl func_800957F4
/* 8008AA64 00087644  38 60 00 01 */	li r3, 1
/* 8008AA68 00087648  48 00 00 D0 */	b lbl_8008AB38
lbl_8008AA6C:
/* 8008AA6C 0008764C  80 7F 19 74 */	lwz r3, 0x1974(r31)
/* 8008AA70 00087650  48 1E 08 9D */	bl func_8026B30C
/* 8008AA74 00087654  2C 03 00 03 */	cmpwi r3, 3
/* 8008AA78 00087658  41 82 00 28 */	beq lbl_8008AAA0
/* 8008AA7C 0008765C  40 80 00 34 */	bge lbl_8008AAB0
/* 8008AA80 00087660  2C 03 00 02 */	cmpwi r3, 2
/* 8008AA84 00087664  40 80 00 08 */	bge lbl_8008AA8C
/* 8008AA88 00087668  48 00 00 28 */	b lbl_8008AAB0
lbl_8008AA8C:
/* 8008AA8C 0008766C  38 7E 00 00 */	addi r3, r30, 0
/* 8008AA90 00087670  38 80 00 00 */	li r4, 0
/* 8008AA94 00087674  48 04 24 C5 */	bl func_800CCF58
/* 8008AA98 00087678  38 60 00 01 */	li r3, 1
/* 8008AA9C 0008767C  48 00 00 9C */	b lbl_8008AB38
lbl_8008AAA0:
/* 8008AAA0 00087680  7F C3 F3 78 */	mr r3, r30
/* 8008AAA4 00087684  48 04 32 71 */	bl func_800CDD14
/* 8008AAA8 00087688  38 60 00 01 */	li r3, 1
/* 8008AAAC 0008768C  48 00 00 8C */	b lbl_8008AB38
lbl_8008AAB0:
/* 8008AAB0 00087690  C0 3F 19 6C */	lfs f1, 0x196c(r31)
/* 8008AAB4 00087694  C0 02 8A 78 */	lfs f0, lbl_804D8458(r2)
/* 8008AAB8 00087698  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8008AABC 0008769C  40 81 00 4C */	ble lbl_8008AB08
/* 8008AAC0 000876A0  88 1F 22 18 */	lbz r0, 0x2218(r31)
/* 8008AAC4 000876A4  54 00 D7 FF */	rlwinm. r0, r0, 0x1a, 0x1f, 0x1f
/* 8008AAC8 000876A8  41 82 00 40 */	beq lbl_8008AB08
/* 8008AACC 000876AC  80 1F 19 70 */	lwz r0, 0x1970(r31)
/* 8008AAD0 000876B0  2C 00 00 2D */	cmpwi r0, 0x2d
/* 8008AAD4 000876B4  41 82 00 24 */	beq lbl_8008AAF8
/* 8008AAD8 000876B8  40 80 00 40 */	bge lbl_8008AB18
/* 8008AADC 000876BC  2C 00 00 2C */	cmpwi r0, 0x2c
/* 8008AAE0 000876C0  40 80 00 08 */	bge lbl_8008AAE8
/* 8008AAE4 000876C4  48 00 00 34 */	b lbl_8008AB18
lbl_8008AAE8:
/* 8008AAE8 000876C8  7F C3 F3 78 */	mr r3, r30
/* 8008AAEC 000876CC  48 00 03 45 */	bl func_8008AE30
/* 8008AAF0 000876D0  38 60 00 01 */	li r3, 1
/* 8008AAF4 000876D4  48 00 00 44 */	b lbl_8008AB38
lbl_8008AAF8:
/* 8008AAF8 000876D8  7F C3 F3 78 */	mr r3, r30
/* 8008AAFC 000876DC  48 00 06 99 */	bl func_8008B194
/* 8008AB00 000876E0  38 60 00 01 */	li r3, 1
/* 8008AB04 000876E4  48 00 00 34 */	b lbl_8008AB38
lbl_8008AB08:
/* 8008AB08 000876E8  7F C3 F3 78 */	mr r3, r30
/* 8008AB0C 000876EC  48 00 00 79 */	bl func_8008AB84
/* 8008AB10 000876F0  38 60 00 01 */	li r3, 1
/* 8008AB14 000876F4  48 00 00 24 */	b lbl_8008AB38
lbl_8008AB18:
/* 8008AB18 000876F8  C0 3F 19 6C */	lfs f1, 0x196c(r31)
/* 8008AB1C 000876FC  C0 02 8A 78 */	lfs f0, lbl_804D8458(r2)
/* 8008AB20 00087700  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8008AB24 00087704  40 81 00 10 */	ble lbl_8008AB34
/* 8008AB28 00087708  C0 02 8A 7C */	lfs f0, lbl_804D845C(r2)
/* 8008AB2C 0008770C  EC 01 00 28 */	fsubs f0, f1, f0
/* 8008AB30 00087710  D0 1F 19 6C */	stfs f0, 0x196c(r31)
lbl_8008AB34:
/* 8008AB34 00087714  38 60 00 00 */	li r3, 0
lbl_8008AB38:
/* 8008AB38 00087718  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 8008AB3C 0008771C  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 8008AB40 00087720  83 C1 00 10 */	lwz r30, 0x10(r1)
/* 8008AB44 00087724  38 21 00 18 */	addi r1, r1, 0x18
/* 8008AB48 00087728  7C 08 03 A6 */	mtlr r0
/* 8008AB4C 0008772C  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

#pragma push
asm unk_t lbl_8008AB50()
{ // clang-format off
    nofralloc
/* 8008AB50 00087730  7C 08 02 A6 */	mflr r0
/* 8008AB54 00087734  90 01 00 04 */	stw r0, 4(r1)
/* 8008AB58 00087738  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 8008AB5C 0008773C  93 E1 00 14 */	stw r31, 0x14(r1)
/* 8008AB60 00087740  7C 7F 1B 78 */	mr r31, r3
/* 8008AB64 00087744  4B FF E7 3D */	bl func_800892A0
/* 8008AB68 00087748  7F E3 FB 78 */	mr r3, r31
/* 8008AB6C 0008774C  4B FF EC B9 */	bl func_80089824
/* 8008AB70 00087750  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 8008AB74 00087754  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 8008AB78 00087758  38 21 00 18 */	addi r1, r1, 0x18
/* 8008AB7C 0008775C  7C 08 03 A6 */	mtlr r0
/* 8008AB80 00087760  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

extern unk_t func_8008ABC0();

#pragma push
asm unk_t func_8008AB84()
{ // clang-format off
    nofralloc
/* 8008AB84 00087764  7C 08 02 A6 */	mflr r0
/* 8008AB88 00087768  90 01 00 04 */	stw r0, 4(r1)
/* 8008AB8C 0008776C  94 21 FF F8 */	stwu r1, -8(r1)
/* 8008AB90 00087770  80 83 00 2C */	lwz r4, 0x2c(r3)
/* 8008AB94 00087774  80 04 00 04 */	lwz r0, 4(r4)
/* 8008AB98 00087778  2C 00 00 18 */	cmpwi r0, 0x18
/* 8008AB9C 0008777C  41 82 00 08 */	beq lbl_8008ABA4
/* 8008ABA0 00087780  48 00 00 0C */	b lbl_8008ABAC
lbl_8008ABA4:
/* 8008ABA4 00087784  48 0C 14 D9 */	bl ftGameWatch_Attack11_Action
/* 8008ABA8 00087788  48 00 00 08 */	b lbl_8008ABB0
lbl_8008ABAC:
/* 8008ABAC 0008778C  48 00 00 15 */	bl func_8008ABC0
lbl_8008ABB0:
/* 8008ABB0 00087790  80 01 00 0C */	lwz r0, 0xc(r1)
/* 8008ABB4 00087794  38 21 00 08 */	addi r1, r1, 8
/* 8008ABB8 00087798  7C 08 03 A6 */	mtlr r0
/* 8008ABBC 0008779C  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

extern BOOL func_80094790(HSD_GObj* fighter_gobj);

#pragma push
asm unk_t func_8008ABC0()
{ // clang-format off
    nofralloc
/* 8008ABC0 000877A0  7C 08 02 A6 */	mflr r0
/* 8008ABC4 000877A4  90 01 00 04 */	stw r0, 4(r1)
/* 8008ABC8 000877A8  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 8008ABCC 000877AC  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 8008ABD0 000877B0  93 C1 00 18 */	stw r30, 0x18(r1)
/* 8008ABD4 000877B4  7C 7E 1B 78 */	mr r30, r3
/* 8008ABD8 000877B8  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 8008ABDC 000877BC  48 00 9B B5 */	bl func_80094790
/* 8008ABE0 000877C0  2C 03 00 00 */	cmpwi r3, 0
/* 8008ABE4 000877C4  40 82 00 A0 */	bne lbl_8008AC84
/* 8008ABE8 000877C8  88 1F 22 18 */	lbz r0, 0x2218(r31)
/* 8008ABEC 000877CC  38 60 00 00 */	li r3, 0
/* 8008ABF0 000877D0  50 60 3E 30 */	rlwimi r0, r3, 7, 0x18, 0x18
/* 8008ABF4 000877D4  98 1F 22 18 */	stb r0, 0x2218(r31)
/* 8008ABF8 000877D8  88 1F 22 18 */	lbz r0, 0x2218(r31)
/* 8008ABFC 000877DC  50 60 36 72 */	rlwimi r0, r3, 6, 0x19, 0x19
/* 8008AC00 000877E0  98 1F 22 18 */	stb r0, 0x2218(r31)
/* 8008AC04 000877E4  80 1F 00 04 */	lwz r0, 4(r31)
/* 8008AC08 000877E8  2C 00 00 17 */	cmpwi r0, 0x17
/* 8008AC0C 000877EC  41 82 00 14 */	beq lbl_8008AC20
/* 8008AC10 000877F0  40 80 00 24 */	bge lbl_8008AC34
/* 8008AC14 000877F4  2C 00 00 0C */	cmpwi r0, 0xc
/* 8008AC18 000877F8  41 82 00 08 */	beq lbl_8008AC20
/* 8008AC1C 000877FC  48 00 00 18 */	b lbl_8008AC34
lbl_8008AC20:
/* 8008AC20 00087800  3C 60 80 09 */	lis r3, lbl_8008AB50@ha
/* 8008AC24 00087804  38 03 AB 50 */	addi r0, r3, lbl_8008AB50@l
/* 8008AC28 00087808  90 1F 21 EC */	stw r0, 0x21ec(r31)
/* 8008AC2C 0008780C  3C A0 02 00 */	lis r5, 0x200
/* 8008AC30 00087810  48 00 00 08 */	b lbl_8008AC38
lbl_8008AC34:
/* 8008AC34 00087814  38 A0 00 00 */	li r5, 0
lbl_8008AC38:
/* 8008AC38 00087818  C0 22 8A 78 */	lfs f1, lbl_804D8458(r2)
/* 8008AC3C 0008781C  7F C3 F3 78 */	mr r3, r30
/* 8008AC40 00087820  C0 42 8A 7C */	lfs f2, lbl_804D845C(r2)
/* 8008AC44 00087824  38 80 00 2C */	li r4, 0x2c
/* 8008AC48 00087828  FC 60 08 90 */	fmr f3, f1
/* 8008AC4C 0008782C  38 C0 00 00 */	li r6, 0
/* 8008AC50 00087830  4B FD E7 5D */	bl Fighter_ActionStateChange_800693AC
/* 8008AC54 00087834  7F C3 F3 78 */	mr r3, r30
/* 8008AC58 00087838  4B FE 3F 4D */	bl func_8006EBA4
/* 8008AC5C 0008783C  C0 1F 01 8C */	lfs f0, 0x18c(r31)
/* 8008AC60 00087840  38 00 00 2C */	li r0, 0x2c
/* 8008AC64 00087844  38 60 00 00 */	li r3, 0
/* 8008AC68 00087848  D0 1F 19 6C */	stfs f0, 0x196c(r31)
/* 8008AC6C 0008784C  90 1F 19 70 */	stw r0, 0x1970(r31)
/* 8008AC70 00087850  88 1F 22 18 */	lbz r0, 0x2218(r31)
/* 8008AC74 00087854  50 60 2E B4 */	rlwimi r0, r3, 5, 0x1a, 0x1a
/* 8008AC78 00087858  98 1F 22 18 */	stb r0, 0x2218(r31)
/* 8008AC7C 0008785C  90 7F 23 40 */	stw r3, 0x2340(r31)
/* 8008AC80 00087860  90 7F 1A 54 */	stw r3, 0x1a54(r31)
lbl_8008AC84:
/* 8008AC84 00087864  80 01 00 24 */	lwz r0, 0x24(r1)
/* 8008AC88 00087868  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 8008AC8C 0008786C  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 8008AC90 00087870  38 21 00 20 */	addi r1, r1, 0x20
/* 8008AC94 00087874  7C 08 03 A6 */	mtlr r0
/* 8008AC98 00087878  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

#pragma push
asm unk_t func_8008AC9C()
{ // clang-format off
    nofralloc
/* 8008AC9C 0008787C  7C 08 02 A6 */	mflr r0
/* 8008ACA0 00087880  90 01 00 04 */	stw r0, 4(r1)
/* 8008ACA4 00087884  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 8008ACA8 00087888  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 8008ACAC 0008788C  7C 7F 1B 78 */	mr r31, r3
/* 8008ACB0 00087890  4B FE 45 89 */	bl ftAnim_IsFramesRemaining
/* 8008ACB4 00087894  2C 03 00 00 */	cmpwi r3, 0
/* 8008ACB8 00087898  40 82 00 0C */	bne lbl_8008ACC4
/* 8008ACBC 0008789C  7F E3 FB 78 */	mr r3, r31
/* 8008ACC0 000878A0  4B FF F5 FD */	bl func_8008A2BC
lbl_8008ACC4:
/* 8008ACC4 000878A4  80 01 00 24 */	lwz r0, 0x24(r1)
/* 8008ACC8 000878A8  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 8008ACCC 000878AC  38 21 00 20 */	addi r1, r1, 0x20
/* 8008ACD0 000878B0  7C 08 03 A6 */	mtlr r0
/* 8008ACD4 000878B4  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

extern unk_t func_8008AF0C();
extern unk_t func_800D6A50();

#pragma push
asm unk_t func_8008ACD8()
{ // clang-format off
    nofralloc
/* 8008ACD8 000878B8  7C 08 02 A6 */	mflr r0
/* 8008ACDC 000878BC  90 01 00 04 */	stw r0, 4(r1)
/* 8008ACE0 000878C0  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 8008ACE4 000878C4  93 E1 00 14 */	stw r31, 0x14(r1)
/* 8008ACE8 000878C8  93 C1 00 10 */	stw r30, 0x10(r1)
/* 8008ACEC 000878CC  7C 7E 1B 78 */	mr r30, r3
/* 8008ACF0 000878D0  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 8008ACF4 000878D4  88 1F 22 18 */	lbz r0, 0x2218(r31)
/* 8008ACF8 000878D8  54 00 CF FF */	rlwinm. r0, r0, 0x19, 0x1f, 0x1f
/* 8008ACFC 000878DC  41 82 00 64 */	beq lbl_8008AD60
/* 8008AD00 000878E0  7F C3 F3 78 */	mr r3, r30
/* 8008AD04 000878E4  48 00 12 C1 */	bl func_8008BFC4
/* 8008AD08 000878E8  2C 03 00 00 */	cmpwi r3, 0
/* 8008AD0C 000878EC  40 82 00 CC */	bne lbl_8008ADD8
/* 8008AD10 000878F0  7F C3 F3 78 */	mr r3, r30
/* 8008AD14 000878F4  48 00 1B 1D */	bl func_8008C830
/* 8008AD18 000878F8  2C 03 00 00 */	cmpwi r3, 0
/* 8008AD1C 000878FC  40 82 00 BC */	bne lbl_8008ADD8
/* 8008AD20 00087900  7F C3 F3 78 */	mr r3, r30
/* 8008AD24 00087904  48 00 1E 21 */	bl func_8008CB44
/* 8008AD28 00087908  2C 03 00 00 */	cmpwi r3, 0
/* 8008AD2C 0008790C  40 82 00 AC */	bne lbl_8008ADD8
/* 8008AD30 00087910  7F C3 F3 78 */	mr r3, r30
/* 8008AD34 00087914  48 00 09 25 */	bl func_8008B658
/* 8008AD38 00087918  2C 03 00 00 */	cmpwi r3, 0
/* 8008AD3C 0008791C  40 82 00 9C */	bne lbl_8008ADD8
/* 8008AD40 00087920  7F C3 F3 78 */	mr r3, r30
/* 8008AD44 00087924  48 00 0C 3D */	bl func_8008B980
/* 8008AD48 00087928  2C 03 00 00 */	cmpwi r3, 0
/* 8008AD4C 0008792C  40 82 00 8C */	bne lbl_8008ADD8
/* 8008AD50 00087930  7F C3 F3 78 */	mr r3, r30
/* 8008AD54 00087934  48 00 0D F1 */	bl func_8008BB44
/* 8008AD58 00087938  2C 03 00 00 */	cmpwi r3, 0
/* 8008AD5C 0008793C  40 82 00 7C */	bne lbl_8008ADD8
lbl_8008AD60:
/* 8008AD60 00087940  7F C3 F3 78 */	mr r3, r30
/* 8008AD64 00087944  48 04 BC ED */	bl func_800D6A50
/* 8008AD68 00087948  2C 03 00 00 */	cmpwi r3, 0
/* 8008AD6C 0008794C  40 82 00 6C */	bne lbl_8008ADD8
/* 8008AD70 00087950  7F C3 F3 78 */	mr r3, r30
/* 8008AD74 00087954  48 00 01 99 */	bl func_8008AF0C
/* 8008AD78 00087958  2C 03 00 00 */	cmpwi r3, 0
/* 8008AD7C 0008795C  40 82 00 5C */	bne lbl_8008ADD8
/* 8008AD80 00087960  88 1F 22 18 */	lbz r0, 0x2218(r31)
/* 8008AD84 00087964  54 00 CF FF */	rlwinm. r0, r0, 0x19, 0x1f, 0x1f
/* 8008AD88 00087968  41 82 00 50 */	beq lbl_8008ADD8
/* 8008AD8C 0008796C  7F C3 F3 78 */	mr r3, r30
/* 8008AD90 00087970  48 04 01 41 */	bl func_800CAED0
/* 8008AD94 00087974  2C 03 00 00 */	cmpwi r3, 0
/* 8008AD98 00087978  40 82 00 40 */	bne lbl_8008ADD8
/* 8008AD9C 0008797C  7F C3 F3 78 */	mr r3, r30
/* 8008ADA0 00087980  48 03 F2 F5 */	bl func_800CA094
/* 8008ADA4 00087984  2C 03 00 00 */	cmpwi r3, 0
/* 8008ADA8 00087988  40 82 00 30 */	bne lbl_8008ADD8
/* 8008ADAC 0008798C  7F C3 F3 78 */	mr r3, r30
/* 8008ADB0 00087990  48 04 B2 01 */	bl func_800D5FB0
/* 8008ADB4 00087994  2C 03 00 00 */	cmpwi r3, 0
/* 8008ADB8 00087998  40 82 00 20 */	bne lbl_8008ADD8
/* 8008ADBC 0008799C  7F C3 F3 78 */	mr r3, r30
/* 8008ADC0 000879A0  48 03 EA 1D */	bl func_800C97DC
/* 8008ADC4 000879A4  2C 03 00 00 */	cmpwi r3, 0
/* 8008ADC8 000879A8  40 82 00 10 */	bne lbl_8008ADD8
/* 8008ADCC 000879AC  7F C3 F3 78 */	mr r3, r30
/* 8008ADD0 000879B0  48 03 E6 99 */	bl func_800C9468
/* 8008ADD4 000879B4  2C 03 00 00 */	cmpwi r3, 0
lbl_8008ADD8:
/* 8008ADD8 000879B8  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 8008ADDC 000879BC  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 8008ADE0 000879C0  83 C1 00 10 */	lwz r30, 0x10(r1)
/* 8008ADE4 000879C4  38 21 00 18 */	addi r1, r1, 0x18
/* 8008ADE8 000879C8  7C 08 03 A6 */	mtlr r0
/* 8008ADEC 000879CC  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

extern void func_80084FA8(HSD_GObj* fighter_gobj);

#pragma push
asm unk_t func_8008ADF0()
{ // clang-format off
    nofralloc
/* 8008ADF0 000879D0  7C 08 02 A6 */	mflr r0
/* 8008ADF4 000879D4  90 01 00 04 */	stw r0, 4(r1)
/* 8008ADF8 000879D8  94 21 FF F8 */	stwu r1, -8(r1)
/* 8008ADFC 000879DC  4B FF A1 AD */	bl func_80084FA8
/* 8008AE00 000879E0  80 01 00 0C */	lwz r0, 0xc(r1)
/* 8008AE04 000879E4  38 21 00 08 */	addi r1, r1, 8
/* 8008AE08 000879E8  7C 08 03 A6 */	mtlr r0
/* 8008AE0C 000879EC  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

extern void func_80084104(HSD_GObj* fighter_gobj);

#pragma push
asm unk_t func_8008AE10()
{ // clang-format off
    nofralloc
/* 8008AE10 000879F0  7C 08 02 A6 */	mflr r0
/* 8008AE14 000879F4  90 01 00 04 */	stw r0, 4(r1)
/* 8008AE18 000879F8  94 21 FF F8 */	stwu r1, -8(r1)
/* 8008AE1C 000879FC  4B FF 92 E9 */	bl func_80084104
/* 8008AE20 00087A00  80 01 00 0C */	lwz r0, 0xc(r1)
/* 8008AE24 00087A04  38 21 00 08 */	addi r1, r1, 8
/* 8008AE28 00087A08  7C 08 03 A6 */	mtlr r0
/* 8008AE2C 00087A0C  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

#pragma push
asm unk_t func_8008AE30()
{ // clang-format off
    nofralloc
/* 8008AE30 00087A10  7C 08 02 A6 */	mflr r0
/* 8008AE34 00087A14  90 01 00 04 */	stw r0, 4(r1)
/* 8008AE38 00087A18  94 21 FF D0 */	stwu r1, -0x30(r1)
/* 8008AE3C 00087A1C  93 E1 00 2C */	stw r31, 0x2c(r1)
/* 8008AE40 00087A20  93 C1 00 28 */	stw r30, 0x28(r1)
/* 8008AE44 00087A24  93 A1 00 24 */	stw r29, 0x24(r1)
/* 8008AE48 00087A28  7C 7D 1B 78 */	mr r29, r3
/* 8008AE4C 00087A2C  83 C3 00 2C */	lwz r30, 0x2c(r3)
/* 8008AE50 00087A30  80 1E 00 04 */	lwz r0, 4(r30)
/* 8008AE54 00087A34  2C 00 00 17 */	cmpwi r0, 0x17
/* 8008AE58 00087A38  41 82 00 14 */	beq lbl_8008AE6C
/* 8008AE5C 00087A3C  40 80 00 34 */	bge lbl_8008AE90
/* 8008AE60 00087A40  2C 00 00 0C */	cmpwi r0, 0xc
/* 8008AE64 00087A44  41 82 00 08 */	beq lbl_8008AE6C
/* 8008AE68 00087A48  48 00 00 28 */	b lbl_8008AE90
lbl_8008AE6C:
/* 8008AE6C 00087A4C  2C 00 00 18 */	cmpwi r0, 0x18
/* 8008AE70 00087A50  41 82 00 08 */	beq lbl_8008AE78
/* 8008AE74 00087A54  48 00 00 10 */	b lbl_8008AE84
lbl_8008AE78:
/* 8008AE78 00087A58  7F A3 EB 78 */	mr r3, r29
/* 8008AE7C 00087A5C  48 0C 12 01 */	bl ftGameWatch_Attack11_Action
/* 8008AE80 00087A60  48 00 00 70 */	b lbl_8008AEF0
lbl_8008AE84:
/* 8008AE84 00087A64  7F A3 EB 78 */	mr r3, r29
/* 8008AE88 00087A68  4B FF FD 39 */	bl func_8008ABC0
/* 8008AE8C 00087A6C  48 00 00 64 */	b lbl_8008AEF0
lbl_8008AE90:
/* 8008AE90 00087A70  7F A3 EB 78 */	mr r3, r29
/* 8008AE94 00087A74  48 00 98 FD */	bl func_80094790
/* 8008AE98 00087A78  2C 03 00 00 */	cmpwi r3, 0
/* 8008AE9C 00087A7C  40 82 00 54 */	bne lbl_8008AEF0
/* 8008AEA0 00087A80  88 1E 22 18 */	lbz r0, 0x2218(r30)
/* 8008AEA4 00087A84  3B E0 00 00 */	li r31, 0
/* 8008AEA8 00087A88  53 E0 3E 30 */	rlwimi r0, r31, 7, 0x18, 0x18
/* 8008AEAC 00087A8C  98 1E 22 18 */	stb r0, 0x2218(r30)
/* 8008AEB0 00087A90  38 7D 00 00 */	addi r3, r29, 0
/* 8008AEB4 00087A94  38 80 00 2D */	li r4, 0x2d
/* 8008AEB8 00087A98  88 1E 22 18 */	lbz r0, 0x2218(r30)
/* 8008AEBC 00087A9C  53 E0 36 72 */	rlwimi r0, r31, 6, 0x19, 0x19
/* 8008AEC0 00087AA0  38 A0 00 00 */	li r5, 0
/* 8008AEC4 00087AA4  98 1E 22 18 */	stb r0, 0x2218(r30)
/* 8008AEC8 00087AA8  38 C0 00 00 */	li r6, 0
/* 8008AECC 00087AAC  C0 22 8A 78 */	lfs f1, lbl_804D8458(r2)
/* 8008AED0 00087AB0  C0 42 8A 7C */	lfs f2, lbl_804D845C(r2)
/* 8008AED4 00087AB4  FC 60 08 90 */	fmr f3, f1
/* 8008AED8 00087AB8  4B FD E4 D5 */	bl Fighter_ActionStateChange_800693AC
/* 8008AEDC 00087ABC  C0 1E 01 90 */	lfs f0, 0x190(r30)
/* 8008AEE0 00087AC0  38 00 00 2D */	li r0, 0x2d
/* 8008AEE4 00087AC4  D0 1E 19 6C */	stfs f0, 0x196c(r30)
/* 8008AEE8 00087AC8  90 1E 19 70 */	stw r0, 0x1970(r30)
/* 8008AEEC 00087ACC  93 FE 23 40 */	stw r31, 0x2340(r30)
lbl_8008AEF0:
/* 8008AEF0 00087AD0  80 01 00 34 */	lwz r0, 0x34(r1)
/* 8008AEF4 00087AD4  83 E1 00 2C */	lwz r31, 0x2c(r1)
/* 8008AEF8 00087AD8  83 C1 00 28 */	lwz r30, 0x28(r1)
/* 8008AEFC 00087ADC  83 A1 00 24 */	lwz r29, 0x24(r1)
/* 8008AF00 00087AE0  38 21 00 30 */	addi r1, r1, 0x30
/* 8008AF04 00087AE4  7C 08 03 A6 */	mtlr r0
/* 8008AF08 00087AE8  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

#pragma push
asm unk_t func_8008AF0C()
{ // clang-format off
    nofralloc
/* 8008AF0C 00087AEC  7C 08 02 A6 */	mflr r0
/* 8008AF10 00087AF0  90 01 00 04 */	stw r0, 4(r1)
/* 8008AF14 00087AF4  94 21 FF C0 */	stwu r1, -0x40(r1)
/* 8008AF18 00087AF8  93 E1 00 3C */	stw r31, 0x3c(r1)
/* 8008AF1C 00087AFC  93 C1 00 38 */	stw r30, 0x38(r1)
/* 8008AF20 00087B00  93 A1 00 34 */	stw r29, 0x34(r1)
/* 8008AF24 00087B04  7C 7D 1B 78 */	mr r29, r3
/* 8008AF28 00087B08  80 63 00 2C */	lwz r3, 0x2c(r3)
/* 8008AF2C 00087B0C  C0 02 8A 78 */	lfs f0, lbl_804D8458(r2)
/* 8008AF30 00087B10  C0 23 19 6C */	lfs f1, 0x196c(r3)
/* 8008AF34 00087B14  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8008AF38 00087B18  40 81 00 24 */	ble lbl_8008AF5C
/* 8008AF3C 00087B1C  C0 02 8A 7C */	lfs f0, lbl_804D845C(r2)
/* 8008AF40 00087B20  EC 01 00 28 */	fsubs f0, f1, f0
/* 8008AF44 00087B24  D0 03 19 6C */	stfs f0, 0x196c(r3)
/* 8008AF48 00087B28  80 03 06 68 */	lwz r0, 0x668(r3)
/* 8008AF4C 00087B2C  54 00 05 EF */	rlwinm. r0, r0, 0, 0x17, 0x17
/* 8008AF50 00087B30  41 82 00 0C */	beq lbl_8008AF5C
/* 8008AF54 00087B34  38 00 00 01 */	li r0, 1
/* 8008AF58 00087B38  90 03 23 40 */	stw r0, 0x2340(r3)
lbl_8008AF5C:
/* 8008AF5C 00087B3C  80 03 23 40 */	lwz r0, 0x2340(r3)
/* 8008AF60 00087B40  2C 00 00 00 */	cmpwi r0, 0
/* 8008AF64 00087B44  41 82 00 BC */	beq lbl_8008B020
/* 8008AF68 00087B48  88 03 22 18 */	lbz r0, 0x2218(r3)
/* 8008AF6C 00087B4C  54 00 D7 FF */	rlwinm. r0, r0, 0x1a, 0x1f, 0x1f
/* 8008AF70 00087B50  41 82 00 B0 */	beq lbl_8008B020
/* 8008AF74 00087B54  83 DD 00 2C */	lwz r30, 0x2c(r29)
/* 8008AF78 00087B58  80 1E 00 04 */	lwz r0, 4(r30)
/* 8008AF7C 00087B5C  2C 00 00 17 */	cmpwi r0, 0x17
/* 8008AF80 00087B60  41 82 00 14 */	beq lbl_8008AF94
/* 8008AF84 00087B64  40 80 00 34 */	bge lbl_8008AFB8
/* 8008AF88 00087B68  2C 00 00 0C */	cmpwi r0, 0xc
/* 8008AF8C 00087B6C  41 82 00 08 */	beq lbl_8008AF94
/* 8008AF90 00087B70  48 00 00 28 */	b lbl_8008AFB8
lbl_8008AF94:
/* 8008AF94 00087B74  2C 00 00 18 */	cmpwi r0, 0x18
/* 8008AF98 00087B78  41 82 00 08 */	beq lbl_8008AFA0
/* 8008AF9C 00087B7C  48 00 00 10 */	b lbl_8008AFAC
lbl_8008AFA0:
/* 8008AFA0 00087B80  7F A3 EB 78 */	mr r3, r29
/* 8008AFA4 00087B84  48 0C 10 D9 */	bl ftGameWatch_Attack11_Action
/* 8008AFA8 00087B88  48 00 00 70 */	b lbl_8008B018
lbl_8008AFAC:
/* 8008AFAC 00087B8C  7F A3 EB 78 */	mr r3, r29
/* 8008AFB0 00087B90  4B FF FC 11 */	bl func_8008ABC0
/* 8008AFB4 00087B94  48 00 00 64 */	b lbl_8008B018
lbl_8008AFB8:
/* 8008AFB8 00087B98  7F A3 EB 78 */	mr r3, r29
/* 8008AFBC 00087B9C  48 00 97 D5 */	bl func_80094790
/* 8008AFC0 00087BA0  2C 03 00 00 */	cmpwi r3, 0
/* 8008AFC4 00087BA4  40 82 00 54 */	bne lbl_8008B018
/* 8008AFC8 00087BA8  88 1E 22 18 */	lbz r0, 0x2218(r30)
/* 8008AFCC 00087BAC  3B E0 00 00 */	li r31, 0
/* 8008AFD0 00087BB0  53 E0 3E 30 */	rlwimi r0, r31, 7, 0x18, 0x18
/* 8008AFD4 00087BB4  98 1E 22 18 */	stb r0, 0x2218(r30)
/* 8008AFD8 00087BB8  38 7D 00 00 */	addi r3, r29, 0
/* 8008AFDC 00087BBC  38 80 00 2D */	li r4, 0x2d
/* 8008AFE0 00087BC0  88 1E 22 18 */	lbz r0, 0x2218(r30)
/* 8008AFE4 00087BC4  53 E0 36 72 */	rlwimi r0, r31, 6, 0x19, 0x19
/* 8008AFE8 00087BC8  38 A0 00 00 */	li r5, 0
/* 8008AFEC 00087BCC  98 1E 22 18 */	stb r0, 0x2218(r30)
/* 8008AFF0 00087BD0  38 C0 00 00 */	li r6, 0
/* 8008AFF4 00087BD4  C0 22 8A 78 */	lfs f1, lbl_804D8458(r2)
/* 8008AFF8 00087BD8  C0 42 8A 7C */	lfs f2, lbl_804D845C(r2)
/* 8008AFFC 00087BDC  FC 60 08 90 */	fmr f3, f1
/* 8008B000 00087BE0  4B FD E3 AD */	bl Fighter_ActionStateChange_800693AC
/* 8008B004 00087BE4  C0 1E 01 90 */	lfs f0, 0x190(r30)
/* 8008B008 00087BE8  38 00 00 2D */	li r0, 0x2d
/* 8008B00C 00087BEC  D0 1E 19 6C */	stfs f0, 0x196c(r30)
/* 8008B010 00087BF0  90 1E 19 70 */	stw r0, 0x1970(r30)
/* 8008B014 00087BF4  93 FE 23 40 */	stw r31, 0x2340(r30)
lbl_8008B018:
/* 8008B018 00087BF8  38 60 00 01 */	li r3, 1
/* 8008B01C 00087BFC  48 00 00 08 */	b lbl_8008B024
lbl_8008B020:
/* 8008B020 00087C00  38 60 00 00 */	li r3, 0
lbl_8008B024:
/* 8008B024 00087C04  80 01 00 44 */	lwz r0, 0x44(r1)
/* 8008B028 00087C08  83 E1 00 3C */	lwz r31, 0x3c(r1)
/* 8008B02C 00087C0C  83 C1 00 38 */	lwz r30, 0x38(r1)
/* 8008B030 00087C10  83 A1 00 34 */	lwz r29, 0x34(r1)
/* 8008B034 00087C14  38 21 00 40 */	addi r1, r1, 0x40
/* 8008B038 00087C18  7C 08 03 A6 */	mtlr r0
/* 8008B03C 00087C1C  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

#pragma push
asm unk_t func_8008B040()
{ // clang-format off
    nofralloc
/* 8008B040 00087C20  7C 08 02 A6 */	mflr r0
/* 8008B044 00087C24  90 01 00 04 */	stw r0, 4(r1)
/* 8008B048 00087C28  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 8008B04C 00087C2C  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 8008B050 00087C30  7C 7F 1B 78 */	mr r31, r3
/* 8008B054 00087C34  4B FE 41 E5 */	bl ftAnim_IsFramesRemaining
/* 8008B058 00087C38  2C 03 00 00 */	cmpwi r3, 0
/* 8008B05C 00087C3C  40 82 00 0C */	bne lbl_8008B068
/* 8008B060 00087C40  7F E3 FB 78 */	mr r3, r31
/* 8008B064 00087C44  4B FF F2 59 */	bl func_8008A2BC
lbl_8008B068:
/* 8008B068 00087C48  80 01 00 24 */	lwz r0, 0x24(r1)
/* 8008B06C 00087C4C  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 8008B070 00087C50  38 21 00 20 */	addi r1, r1, 0x20
/* 8008B074 00087C54  7C 08 03 A6 */	mtlr r0
/* 8008B078 00087C58  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

extern unk_t func_8008B248();

#pragma push
asm unk_t func_8008B07C()
{ // clang-format off
    nofralloc
/* 8008B07C 00087C5C  7C 08 02 A6 */	mflr r0
/* 8008B080 00087C60  90 01 00 04 */	stw r0, 4(r1)
/* 8008B084 00087C64  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 8008B088 00087C68  93 E1 00 14 */	stw r31, 0x14(r1)
/* 8008B08C 00087C6C  93 C1 00 10 */	stw r30, 0x10(r1)
/* 8008B090 00087C70  7C 7E 1B 78 */	mr r30, r3
/* 8008B094 00087C74  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 8008B098 00087C78  88 1F 22 18 */	lbz r0, 0x2218(r31)
/* 8008B09C 00087C7C  54 00 CF FF */	rlwinm. r0, r0, 0x19, 0x1f, 0x1f
/* 8008B0A0 00087C80  41 82 00 64 */	beq lbl_8008B104
/* 8008B0A4 00087C84  7F C3 F3 78 */	mr r3, r30
/* 8008B0A8 00087C88  48 00 0F 1D */	bl func_8008BFC4
/* 8008B0AC 00087C8C  2C 03 00 00 */	cmpwi r3, 0
/* 8008B0B0 00087C90  40 82 00 CC */	bne lbl_8008B17C
/* 8008B0B4 00087C94  7F C3 F3 78 */	mr r3, r30
/* 8008B0B8 00087C98  48 00 17 79 */	bl func_8008C830
/* 8008B0BC 00087C9C  2C 03 00 00 */	cmpwi r3, 0
/* 8008B0C0 00087CA0  40 82 00 BC */	bne lbl_8008B17C
/* 8008B0C4 00087CA4  7F C3 F3 78 */	mr r3, r30
/* 8008B0C8 00087CA8  48 00 1A 7D */	bl func_8008CB44
/* 8008B0CC 00087CAC  2C 03 00 00 */	cmpwi r3, 0
/* 8008B0D0 00087CB0  40 82 00 AC */	bne lbl_8008B17C
/* 8008B0D4 00087CB4  7F C3 F3 78 */	mr r3, r30
/* 8008B0D8 00087CB8  48 00 05 81 */	bl func_8008B658
/* 8008B0DC 00087CBC  2C 03 00 00 */	cmpwi r3, 0
/* 8008B0E0 00087CC0  40 82 00 9C */	bne lbl_8008B17C
/* 8008B0E4 00087CC4  7F C3 F3 78 */	mr r3, r30
/* 8008B0E8 00087CC8  48 00 08 99 */	bl func_8008B980
/* 8008B0EC 00087CCC  2C 03 00 00 */	cmpwi r3, 0
/* 8008B0F0 00087CD0  40 82 00 8C */	bne lbl_8008B17C
/* 8008B0F4 00087CD4  7F C3 F3 78 */	mr r3, r30
/* 8008B0F8 00087CD8  48 00 0A 4D */	bl func_8008BB44
/* 8008B0FC 00087CDC  2C 03 00 00 */	cmpwi r3, 0
/* 8008B100 00087CE0  40 82 00 7C */	bne lbl_8008B17C
lbl_8008B104:
/* 8008B104 00087CE4  7F C3 F3 78 */	mr r3, r30
/* 8008B108 00087CE8  48 04 B9 49 */	bl func_800D6A50
/* 8008B10C 00087CEC  2C 03 00 00 */	cmpwi r3, 0
/* 8008B110 00087CF0  40 82 00 6C */	bne lbl_8008B17C
/* 8008B114 00087CF4  7F C3 F3 78 */	mr r3, r30
/* 8008B118 00087CF8  48 00 01 31 */	bl func_8008B248
/* 8008B11C 00087CFC  2C 03 00 00 */	cmpwi r3, 0
/* 8008B120 00087D00  40 82 00 5C */	bne lbl_8008B17C
/* 8008B124 00087D04  88 1F 22 18 */	lbz r0, 0x2218(r31)
/* 8008B128 00087D08  54 00 CF FF */	rlwinm. r0, r0, 0x19, 0x1f, 0x1f
/* 8008B12C 00087D0C  41 82 00 50 */	beq lbl_8008B17C
/* 8008B130 00087D10  7F C3 F3 78 */	mr r3, r30
/* 8008B134 00087D14  48 03 FD 9D */	bl func_800CAED0
/* 8008B138 00087D18  2C 03 00 00 */	cmpwi r3, 0
/* 8008B13C 00087D1C  40 82 00 40 */	bne lbl_8008B17C
/* 8008B140 00087D20  7F C3 F3 78 */	mr r3, r30
/* 8008B144 00087D24  48 03 EF 51 */	bl func_800CA094
/* 8008B148 00087D28  2C 03 00 00 */	cmpwi r3, 0
/* 8008B14C 00087D2C  40 82 00 30 */	bne lbl_8008B17C
/* 8008B150 00087D30  7F C3 F3 78 */	mr r3, r30
/* 8008B154 00087D34  48 04 AE 5D */	bl func_800D5FB0
/* 8008B158 00087D38  2C 03 00 00 */	cmpwi r3, 0
/* 8008B15C 00087D3C  40 82 00 20 */	bne lbl_8008B17C
/* 8008B160 00087D40  7F C3 F3 78 */	mr r3, r30
/* 8008B164 00087D44  48 03 E6 79 */	bl func_800C97DC
/* 8008B168 00087D48  2C 03 00 00 */	cmpwi r3, 0
/* 8008B16C 00087D4C  40 82 00 10 */	bne lbl_8008B17C
/* 8008B170 00087D50  7F C3 F3 78 */	mr r3, r30
/* 8008B174 00087D54  48 03 E2 F5 */	bl func_800C9468
/* 8008B178 00087D58  2C 03 00 00 */	cmpwi r3, 0
lbl_8008B17C:
/* 8008B17C 00087D5C  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 8008B180 00087D60  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 8008B184 00087D64  83 C1 00 10 */	lwz r30, 0x10(r1)
/* 8008B188 00087D68  38 21 00 18 */	addi r1, r1, 0x18
/* 8008B18C 00087D6C  7C 08 03 A6 */	mtlr r0
/* 8008B190 00087D70  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

#pragma push
asm unk_t func_8008B194()
{ // clang-format off
    nofralloc
/* 8008B194 00087D74  7C 08 02 A6 */	mflr r0
/* 8008B198 00087D78  90 01 00 04 */	stw r0, 4(r1)
/* 8008B19C 00087D7C  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 8008B1A0 00087D80  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 8008B1A4 00087D84  93 C1 00 18 */	stw r30, 0x18(r1)
/* 8008B1A8 00087D88  7C 7E 1B 78 */	mr r30, r3
/* 8008B1AC 00087D8C  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 8008B1B0 00087D90  80 1F 00 04 */	lwz r0, 4(r31)
/* 8008B1B4 00087D94  2C 00 00 12 */	cmpwi r0, 0x12
/* 8008B1B8 00087D98  41 82 00 08 */	beq lbl_8008B1C0
/* 8008B1BC 00087D9C  48 00 00 28 */	b lbl_8008B1E4
lbl_8008B1C0:
/* 8008B1C0 00087DA0  2C 00 00 18 */	cmpwi r0, 0x18
/* 8008B1C4 00087DA4  41 82 00 08 */	beq lbl_8008B1CC
/* 8008B1C8 00087DA8  48 00 00 10 */	b lbl_8008B1D8
lbl_8008B1CC:
/* 8008B1CC 00087DAC  7F C3 F3 78 */	mr r3, r30
/* 8008B1D0 00087DB0  48 0C 0E AD */	bl ftGameWatch_Attack11_Action
/* 8008B1D4 00087DB4  48 00 00 5C */	b lbl_8008B230
lbl_8008B1D8:
/* 8008B1D8 00087DB8  7F C3 F3 78 */	mr r3, r30
/* 8008B1DC 00087DBC  4B FF F9 E5 */	bl func_8008ABC0
/* 8008B1E0 00087DC0  48 00 00 50 */	b lbl_8008B230
lbl_8008B1E4:
/* 8008B1E4 00087DC4  7F C3 F3 78 */	mr r3, r30
/* 8008B1E8 00087DC8  48 00 95 A9 */	bl func_80094790
/* 8008B1EC 00087DCC  2C 03 00 00 */	cmpwi r3, 0
/* 8008B1F0 00087DD0  40 82 00 40 */	bne lbl_8008B230
/* 8008B1F4 00087DD4  88 1F 22 18 */	lbz r0, 0x2218(r31)
/* 8008B1F8 00087DD8  38 A0 00 00 */	li r5, 0
/* 8008B1FC 00087DDC  50 A0 3E 30 */	rlwimi r0, r5, 7, 0x18, 0x18
/* 8008B200 00087DE0  98 1F 22 18 */	stb r0, 0x2218(r31)
/* 8008B204 00087DE4  38 7E 00 00 */	addi r3, r30, 0
/* 8008B208 00087DE8  38 80 00 2E */	li r4, 0x2e
/* 8008B20C 00087DEC  88 1F 22 18 */	lbz r0, 0x2218(r31)
/* 8008B210 00087DF0  50 A0 36 72 */	rlwimi r0, r5, 6, 0x19, 0x19
/* 8008B214 00087DF4  38 A0 00 00 */	li r5, 0
/* 8008B218 00087DF8  98 1F 22 18 */	stb r0, 0x2218(r31)
/* 8008B21C 00087DFC  38 C0 00 00 */	li r6, 0
/* 8008B220 00087E00  C0 22 8A 78 */	lfs f1, lbl_804D8458(r2)
/* 8008B224 00087E04  C0 42 8A 7C */	lfs f2, lbl_804D845C(r2)
/* 8008B228 00087E08  FC 60 08 90 */	fmr f3, f1
/* 8008B22C 00087E0C  4B FD E1 81 */	bl Fighter_ActionStateChange_800693AC
lbl_8008B230:
/* 8008B230 00087E10  80 01 00 24 */	lwz r0, 0x24(r1)
/* 8008B234 00087E14  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 8008B238 00087E18  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 8008B23C 00087E1C  38 21 00 20 */	addi r1, r1, 0x20
/* 8008B240 00087E20  7C 08 03 A6 */	mtlr r0
/* 8008B244 00087E24  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

#pragma push
asm unk_t func_8008B248()
{ // clang-format off
    nofralloc
/* 8008B248 00087E28  7C 08 02 A6 */	mflr r0
/* 8008B24C 00087E2C  90 01 00 04 */	stw r0, 4(r1)
/* 8008B250 00087E30  94 21 FF D8 */	stwu r1, -0x28(r1)
/* 8008B254 00087E34  93 E1 00 24 */	stw r31, 0x24(r1)
/* 8008B258 00087E38  93 C1 00 20 */	stw r30, 0x20(r1)
/* 8008B25C 00087E3C  7C 7E 1B 78 */	mr r30, r3
/* 8008B260 00087E40  80 63 00 2C */	lwz r3, 0x2c(r3)
/* 8008B264 00087E44  C0 02 8A 78 */	lfs f0, lbl_804D8458(r2)
/* 8008B268 00087E48  C0 23 19 6C */	lfs f1, 0x196c(r3)
/* 8008B26C 00087E4C  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8008B270 00087E50  40 81 00 24 */	ble lbl_8008B294
/* 8008B274 00087E54  C0 02 8A 7C */	lfs f0, lbl_804D845C(r2)
/* 8008B278 00087E58  EC 01 00 28 */	fsubs f0, f1, f0
/* 8008B27C 00087E5C  D0 03 19 6C */	stfs f0, 0x196c(r3)
/* 8008B280 00087E60  80 03 06 68 */	lwz r0, 0x668(r3)
/* 8008B284 00087E64  54 00 05 EF */	rlwinm. r0, r0, 0, 0x17, 0x17
/* 8008B288 00087E68  41 82 00 0C */	beq lbl_8008B294
/* 8008B28C 00087E6C  38 00 00 01 */	li r0, 1
/* 8008B290 00087E70  90 03 23 40 */	stw r0, 0x2340(r3)
lbl_8008B294:
/* 8008B294 00087E74  80 03 23 40 */	lwz r0, 0x2340(r3)
/* 8008B298 00087E78  2C 00 00 00 */	cmpwi r0, 0
/* 8008B29C 00087E7C  41 82 00 9C */	beq lbl_8008B338
/* 8008B2A0 00087E80  88 03 22 18 */	lbz r0, 0x2218(r3)
/* 8008B2A4 00087E84  54 00 D7 FF */	rlwinm. r0, r0, 0x1a, 0x1f, 0x1f
/* 8008B2A8 00087E88  41 82 00 90 */	beq lbl_8008B338
/* 8008B2AC 00087E8C  83 FE 00 2C */	lwz r31, 0x2c(r30)
/* 8008B2B0 00087E90  80 1F 00 04 */	lwz r0, 4(r31)
/* 8008B2B4 00087E94  2C 00 00 12 */	cmpwi r0, 0x12
/* 8008B2B8 00087E98  41 82 00 08 */	beq lbl_8008B2C0
/* 8008B2BC 00087E9C  48 00 00 28 */	b lbl_8008B2E4
lbl_8008B2C0:
/* 8008B2C0 00087EA0  2C 00 00 18 */	cmpwi r0, 0x18
/* 8008B2C4 00087EA4  41 82 00 08 */	beq lbl_8008B2CC
/* 8008B2C8 00087EA8  48 00 00 10 */	b lbl_8008B2D8
lbl_8008B2CC:
/* 8008B2CC 00087EAC  7F C3 F3 78 */	mr r3, r30
/* 8008B2D0 00087EB0  48 0C 0D AD */	bl ftGameWatch_Attack11_Action
/* 8008B2D4 00087EB4  48 00 00 5C */	b lbl_8008B330
lbl_8008B2D8:
/* 8008B2D8 00087EB8  7F C3 F3 78 */	mr r3, r30
/* 8008B2DC 00087EBC  4B FF F8 E5 */	bl func_8008ABC0
/* 8008B2E0 00087EC0  48 00 00 50 */	b lbl_8008B330
lbl_8008B2E4:
/* 8008B2E4 00087EC4  7F C3 F3 78 */	mr r3, r30
/* 8008B2E8 00087EC8  48 00 94 A9 */	bl func_80094790
/* 8008B2EC 00087ECC  2C 03 00 00 */	cmpwi r3, 0
/* 8008B2F0 00087ED0  40 82 00 40 */	bne lbl_8008B330
/* 8008B2F4 00087ED4  88 1F 22 18 */	lbz r0, 0x2218(r31)
/* 8008B2F8 00087ED8  38 A0 00 00 */	li r5, 0
/* 8008B2FC 00087EDC  50 A0 3E 30 */	rlwimi r0, r5, 7, 0x18, 0x18
/* 8008B300 00087EE0  98 1F 22 18 */	stb r0, 0x2218(r31)
/* 8008B304 00087EE4  38 7E 00 00 */	addi r3, r30, 0
/* 8008B308 00087EE8  38 80 00 2E */	li r4, 0x2e
/* 8008B30C 00087EEC  88 1F 22 18 */	lbz r0, 0x2218(r31)
/* 8008B310 00087EF0  50 A0 36 72 */	rlwimi r0, r5, 6, 0x19, 0x19
/* 8008B314 00087EF4  38 A0 00 00 */	li r5, 0
/* 8008B318 00087EF8  98 1F 22 18 */	stb r0, 0x2218(r31)
/* 8008B31C 00087EFC  38 C0 00 00 */	li r6, 0
/* 8008B320 00087F00  C0 22 8A 78 */	lfs f1, lbl_804D8458(r2)
/* 8008B324 00087F04  C0 42 8A 7C */	lfs f2, lbl_804D845C(r2)
/* 8008B328 00087F08  FC 60 08 90 */	fmr f3, f1
/* 8008B32C 00087F0C  4B FD E0 81 */	bl Fighter_ActionStateChange_800693AC
lbl_8008B330:
/* 8008B330 00087F10  38 60 00 01 */	li r3, 1
/* 8008B334 00087F14  48 00 00 08 */	b lbl_8008B33C
lbl_8008B338:
/* 8008B338 00087F18  38 60 00 00 */	li r3, 0
lbl_8008B33C:
/* 8008B33C 00087F1C  80 01 00 2C */	lwz r0, 0x2c(r1)
/* 8008B340 00087F20  83 E1 00 24 */	lwz r31, 0x24(r1)
/* 8008B344 00087F24  83 C1 00 20 */	lwz r30, 0x20(r1)
/* 8008B348 00087F28  38 21 00 28 */	addi r1, r1, 0x28
/* 8008B34C 00087F2C  7C 08 03 A6 */	mtlr r0
/* 8008B350 00087F30  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

#pragma push
asm unk_t func_8008B354()
{ // clang-format off
    nofralloc
/* 8008B354 00087F34  7C 08 02 A6 */	mflr r0
/* 8008B358 00087F38  90 01 00 04 */	stw r0, 4(r1)
/* 8008B35C 00087F3C  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 8008B360 00087F40  93 E1 00 14 */	stw r31, 0x14(r1)
/* 8008B364 00087F44  7C 7F 1B 78 */	mr r31, r3
/* 8008B368 00087F48  4B FE 3E D1 */	bl ftAnim_IsFramesRemaining
/* 8008B36C 00087F4C  2C 03 00 00 */	cmpwi r3, 0
/* 8008B370 00087F50  40 82 00 0C */	bne lbl_8008B37C
/* 8008B374 00087F54  7F E3 FB 78 */	mr r3, r31
/* 8008B378 00087F58  4B FF EF 45 */	bl func_8008A2BC
lbl_8008B37C:
/* 8008B37C 00087F5C  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 8008B380 00087F60  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 8008B384 00087F64  38 21 00 18 */	addi r1, r1, 0x18
/* 8008B388 00087F68  7C 08 03 A6 */	mtlr r0
/* 8008B38C 00087F6C  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

#pragma push
asm unk_t func_8008B390()
{ // clang-format off
    nofralloc
/* 8008B390 00087F70  7C 08 02 A6 */	mflr r0
/* 8008B394 00087F74  90 01 00 04 */	stw r0, 4(r1)
/* 8008B398 00087F78  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 8008B39C 00087F7C  93 E1 00 14 */	stw r31, 0x14(r1)
/* 8008B3A0 00087F80  93 C1 00 10 */	stw r30, 0x10(r1)
/* 8008B3A4 00087F84  7C 7E 1B 78 */	mr r30, r3
/* 8008B3A8 00087F88  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 8008B3AC 00087F8C  48 04 B6 A5 */	bl func_800D6A50
/* 8008B3B0 00087F90  2C 03 00 00 */	cmpwi r3, 0
/* 8008B3B4 00087F94  40 82 00 18 */	bne lbl_8008B3CC
/* 8008B3B8 00087F98  88 1F 22 18 */	lbz r0, 0x2218(r31)
/* 8008B3BC 00087F9C  54 00 CF FF */	rlwinm. r0, r0, 0x19, 0x1f, 0x1f
/* 8008B3C0 00087FA0  41 82 00 0C */	beq lbl_8008B3CC
/* 8008B3C4 00087FA4  7F C3 F3 78 */	mr r3, r30
/* 8008B3C8 00087FA8  4B FF F1 0D */	bl func_8008A4D4
lbl_8008B3CC:
/* 8008B3CC 00087FAC  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 8008B3D0 00087FB0  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 8008B3D4 00087FB4  83 C1 00 10 */	lwz r30, 0x10(r1)
/* 8008B3D8 00087FB8  38 21 00 18 */	addi r1, r1, 0x18
/* 8008B3DC 00087FBC  7C 08 03 A6 */	mtlr r0
/* 8008B3E0 00087FC0  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

extern unk_t func_8008B498();

#pragma push
asm unk_t func_8008B3E4()
{ // clang-format off
    nofralloc
/* 8008B3E4 00087FC4  7C 08 02 A6 */	mflr r0
/* 8008B3E8 00087FC8  90 01 00 04 */	stw r0, 4(r1)
/* 8008B3EC 00087FCC  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 8008B3F0 00087FD0  93 E1 00 14 */	stw r31, 0x14(r1)
/* 8008B3F4 00087FD4  93 C1 00 10 */	stw r30, 0x10(r1)
/* 8008B3F8 00087FD8  7C 7E 1B 78 */	mr r30, r3
/* 8008B3FC 00087FDC  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 8008B400 00087FE0  80 1F 06 68 */	lwz r0, 0x668(r31)
/* 8008B404 00087FE4  54 00 05 EF */	rlwinm. r0, r0, 0, 0x17, 0x17
/* 8008B408 00087FE8  41 82 00 74 */	beq lbl_8008B47C
/* 8008B40C 00087FEC  80 7F 19 74 */	lwz r3, 0x1974(r31)
/* 8008B410 00087FF0  28 03 00 00 */	cmplwi r3, 0
/* 8008B414 00087FF4  41 82 00 58 */	beq lbl_8008B46C
/* 8008B418 00087FF8  80 1F 06 5C */	lwz r0, 0x65c(r31)
/* 8008B41C 00087FFC  54 00 00 01 */	rlwinm. r0, r0, 0, 0, 0
/* 8008B420 00088000  40 82 00 10 */	bne lbl_8008B430
/* 8008B424 00088004  48 1D FE E9 */	bl func_8026B30C
/* 8008B428 00088008  2C 03 00 00 */	cmpwi r3, 0
/* 8008B42C 0008800C  40 82 00 18 */	bne lbl_8008B444
lbl_8008B430:
/* 8008B430 00088010  38 7E 00 00 */	addi r3, r30, 0
/* 8008B434 00088014  38 80 00 62 */	li r4, 0x62
/* 8008B438 00088018  48 00 A3 BD */	bl func_800957F4
/* 8008B43C 0008801C  38 60 00 01 */	li r3, 1
/* 8008B440 00088020  48 00 00 40 */	b lbl_8008B480
lbl_8008B444:
/* 8008B444 00088024  80 7F 19 74 */	lwz r3, 0x1974(r31)
/* 8008B448 00088028  48 1D FE C5 */	bl func_8026B30C
/* 8008B44C 0008802C  2C 03 00 02 */	cmpwi r3, 2
/* 8008B450 00088030  41 82 00 08 */	beq lbl_8008B458
/* 8008B454 00088034  48 00 00 18 */	b lbl_8008B46C
lbl_8008B458:
/* 8008B458 00088038  38 7E 00 00 */	addi r3, r30, 0
/* 8008B45C 0008803C  38 80 00 04 */	li r4, 4
/* 8008B460 00088040  48 04 1A F9 */	bl func_800CCF58
/* 8008B464 00088044  38 60 00 01 */	li r3, 1
/* 8008B468 00088048  48 00 00 18 */	b lbl_8008B480
lbl_8008B46C:
/* 8008B46C 0008804C  7F C3 F3 78 */	mr r3, r30
/* 8008B470 00088050  48 00 00 29 */	bl func_8008B498
/* 8008B474 00088054  38 60 00 01 */	li r3, 1
/* 8008B478 00088058  48 00 00 08 */	b lbl_8008B480
lbl_8008B47C:
/* 8008B47C 0008805C  38 60 00 00 */	li r3, 0
lbl_8008B480:
/* 8008B480 00088060  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 8008B484 00088064  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 8008B488 00088068  83 C1 00 10 */	lwz r30, 0x10(r1)
/* 8008B48C 0008806C  38 21 00 18 */	addi r1, r1, 0x18
/* 8008B490 00088070  7C 08 03 A6 */	mtlr r0
/* 8008B494 00088074  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

extern unk_t func_8008B4D4();
extern unk_t func_800F1F68();

#pragma push
asm unk_t func_8008B498()
{ // clang-format off
    nofralloc
/* 8008B498 00088078  7C 08 02 A6 */	mflr r0
/* 8008B49C 0008807C  90 01 00 04 */	stw r0, 4(r1)
/* 8008B4A0 00088080  94 21 FF F8 */	stwu r1, -8(r1)
/* 8008B4A4 00088084  80 83 00 2C */	lwz r4, 0x2c(r3)
/* 8008B4A8 00088088  80 04 00 04 */	lwz r0, 4(r4)
/* 8008B4AC 0008808C  2C 00 00 04 */	cmpwi r0, 4
/* 8008B4B0 00088090  41 82 00 08 */	beq lbl_8008B4B8
/* 8008B4B4 00088094  48 00 00 0C */	b lbl_8008B4C0
lbl_8008B4B8:
/* 8008B4B8 00088098  48 06 6A B1 */	bl func_800F1F68
/* 8008B4BC 0008809C  48 00 00 08 */	b lbl_8008B4C4
lbl_8008B4C0:
/* 8008B4C0 000880A0  48 00 00 15 */	bl func_8008B4D4
lbl_8008B4C4:
/* 8008B4C4 000880A4  80 01 00 0C */	lwz r0, 0xc(r1)
/* 8008B4C8 000880A8  38 21 00 08 */	addi r1, r1, 8
/* 8008B4CC 000880AC  7C 08 03 A6 */	mtlr r0
/* 8008B4D0 000880B0  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

extern f32 const lbl_804D8460;
extern f32 const lbl_804D8464;

#pragma push
asm unk_t func_8008B4D4()
{ // clang-format off
    nofralloc
/* 8008B4D4 000880B4  7C 08 02 A6 */	mflr r0
/* 8008B4D8 000880B8  38 80 00 32 */	li r4, 0x32
/* 8008B4DC 000880BC  90 01 00 04 */	stw r0, 4(r1)
/* 8008B4E0 000880C0  38 A0 00 00 */	li r5, 0
/* 8008B4E4 000880C4  38 C0 00 00 */	li r6, 0
/* 8008B4E8 000880C8  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 8008B4EC 000880CC  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 8008B4F0 000880D0  3B E0 00 00 */	li r31, 0
/* 8008B4F4 000880D4  93 C1 00 18 */	stw r30, 0x18(r1)
/* 8008B4F8 000880D8  93 A1 00 14 */	stw r29, 0x14(r1)
/* 8008B4FC 000880DC  7C 7D 1B 78 */	mr r29, r3
/* 8008B500 000880E0  83 C3 00 2C */	lwz r30, 0x2c(r3)
/* 8008B504 000880E4  88 1E 22 18 */	lbz r0, 0x2218(r30)
/* 8008B508 000880E8  53 E0 3E 30 */	rlwimi r0, r31, 7, 0x18, 0x18
/* 8008B50C 000880EC  98 1E 22 18 */	stb r0, 0x2218(r30)
/* 8008B510 000880F0  C0 22 8A 80 */	lfs f1, lbl_804D8460(r2)
/* 8008B514 000880F4  C0 42 8A 84 */	lfs f2, lbl_804D8464(r2)
/* 8008B518 000880F8  FC 60 08 90 */	fmr f3, f1
/* 8008B51C 000880FC  4B FD DE 91 */	bl Fighter_ActionStateChange_800693AC
/* 8008B520 00088100  7F A3 EB 78 */	mr r3, r29
/* 8008B524 00088104  4B FE 36 81 */	bl func_8006EBA4
/* 8008B528 00088108  93 FE 23 40 */	stw r31, 0x2340(r30)
/* 8008B52C 0008810C  80 01 00 24 */	lwz r0, 0x24(r1)
/* 8008B530 00088110  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 8008B534 00088114  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 8008B538 00088118  83 A1 00 14 */	lwz r29, 0x14(r1)
/* 8008B53C 0008811C  38 21 00 20 */	addi r1, r1, 0x20
/* 8008B540 00088120  7C 08 03 A6 */	mtlr r0
/* 8008B544 00088124  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

#pragma push
asm unk_t func_8008B548()
{ // clang-format off
    nofralloc
/* 8008B548 00088128  7C 08 02 A6 */	mflr r0
/* 8008B54C 0008812C  90 01 00 04 */	stw r0, 4(r1)
/* 8008B550 00088130  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 8008B554 00088134  93 E1 00 14 */	stw r31, 0x14(r1)
/* 8008B558 00088138  7C 7F 1B 78 */	mr r31, r3
/* 8008B55C 0008813C  4B FE 3C DD */	bl ftAnim_IsFramesRemaining
/* 8008B560 00088140  2C 03 00 00 */	cmpwi r3, 0
/* 8008B564 00088144  40 82 00 0C */	bne lbl_8008B570
/* 8008B568 00088148  7F E3 FB 78 */	mr r3, r31
/* 8008B56C 0008814C  4B FF ED 51 */	bl func_8008A2BC
lbl_8008B570:
/* 8008B570 00088150  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 8008B574 00088154  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 8008B578 00088158  38 21 00 18 */	addi r1, r1, 0x18
/* 8008B57C 0008815C  7C 08 03 A6 */	mtlr r0
/* 8008B580 00088160  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

#pragma push
asm unk_t func_8008B584()
{ // clang-format off
    nofralloc
/* 8008B584 00088164  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 8008B588 00088168  80 8D AE B4 */	lwz r4, p_ftCommonData(r13)
/* 8008B58C 0008816C  80 63 00 2C */	lwz r3, 0x2c(r3)
/* 8008B590 00088170  C0 04 00 68 */	lfs f0, 0x68(r4)
/* 8008B594 00088174  FC 00 00 1E */	fctiwz f0, f0
/* 8008B598 00088178  D8 01 00 18 */	stfd f0, 0x18(r1)
/* 8008B59C 0008817C  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 8008B5A0 00088180  90 03 23 40 */	stw r0, 0x2340(r3)
/* 8008B5A4 00088184  38 21 00 20 */	addi r1, r1, 0x20
/* 8008B5A8 00088188  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

extern unk_t func_800D8AE0();

#pragma push
asm unk_t func_8008B5AC()
{ // clang-format off
    nofralloc
/* 8008B5AC 0008818C  7C 08 02 A6 */	mflr r0
/* 8008B5B0 00088190  90 01 00 04 */	stw r0, 4(r1)
/* 8008B5B4 00088194  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 8008B5B8 00088198  93 E1 00 14 */	stw r31, 0x14(r1)
/* 8008B5BC 0008819C  93 C1 00 10 */	stw r30, 0x10(r1)
/* 8008B5C0 000881A0  7C 7E 1B 78 */	mr r30, r3
/* 8008B5C4 000881A4  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 8008B5C8 000881A8  48 04 D5 19 */	bl func_800D8AE0
/* 8008B5CC 000881AC  2C 03 00 00 */	cmpwi r3, 0
/* 8008B5D0 000881B0  40 82 00 18 */	bne lbl_8008B5E8
/* 8008B5D4 000881B4  88 1F 22 18 */	lbz r0, 0x2218(r31)
/* 8008B5D8 000881B8  54 00 CF FF */	rlwinm. r0, r0, 0x19, 0x1f, 0x1f
/* 8008B5DC 000881BC  41 82 00 0C */	beq lbl_8008B5E8
/* 8008B5E0 000881C0  7F C3 F3 78 */	mr r3, r30
/* 8008B5E4 000881C4  4B FF EE F1 */	bl func_8008A4D4
lbl_8008B5E8:
/* 8008B5E8 000881C8  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 8008B5EC 000881CC  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 8008B5F0 000881D0  83 C1 00 10 */	lwz r30, 0x10(r1)
/* 8008B5F4 000881D4  38 21 00 18 */	addi r1, r1, 0x18
/* 8008B5F8 000881D8  7C 08 03 A6 */	mtlr r0
/* 8008B5FC 000881DC  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

extern unk_t func_80085030();

#pragma push
asm unk_t func_8008B600()
{ // clang-format off
    nofralloc
/* 8008B600 000881E0  7C 08 02 A6 */	mflr r0
/* 8008B604 000881E4  90 01 00 04 */	stw r0, 4(r1)
/* 8008B608 000881E8  94 21 FF F8 */	stwu r1, -8(r1)
/* 8008B60C 000881EC  80 A3 00 2C */	lwz r5, 0x2c(r3)
/* 8008B610 000881F0  80 8D AE B4 */	lwz r4, p_ftCommonData(r13)
/* 8008B614 000881F4  C0 05 01 28 */	lfs f0, 0x128(r5)
/* 8008B618 000881F8  C0 24 00 50 */	lfs f1, 0x50(r4)
/* 8008B61C 000881FC  C0 45 00 2C */	lfs f2, 0x2c(r5)
/* 8008B620 00088200  EC 21 00 32 */	fmuls f1, f1, f0
/* 8008B624 00088204  4B FF 9A 0D */	bl func_80085030
/* 8008B628 00088208  80 01 00 0C */	lwz r0, 0xc(r1)
/* 8008B62C 0008820C  38 21 00 08 */	addi r1, r1, 8
/* 8008B630 00088210  7C 08 03 A6 */	mtlr r0
/* 8008B634 00088214  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

#pragma push
asm unk_t func_8008B638()
{ // clang-format off
    nofralloc
/* 8008B638 00088218  7C 08 02 A6 */	mflr r0
/* 8008B63C 0008821C  90 01 00 04 */	stw r0, 4(r1)
/* 8008B640 00088220  94 21 FF F8 */	stwu r1, -8(r1)
/* 8008B644 00088224  4B FF 8A C1 */	bl func_80084104
/* 8008B648 00088228  80 01 00 0C */	lwz r0, 0xc(r1)
/* 8008B64C 0008822C  38 21 00 08 */	addi r1, r1, 8
/* 8008B650 00088230  7C 08 03 A6 */	mtlr r0
/* 8008B654 00088234  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

extern f32 const lbl_804D8468;
extern unk_t func_8008B788();

#pragma push
asm BOOL func_8008B658(HSD_GObj* fighter_gobj)
{ // clang-format off
    nofralloc
/* 8008B658 00088238  7C 08 02 A6 */	mflr r0
/* 8008B65C 0008823C  90 01 00 04 */	stw r0, 4(r1)
/* 8008B660 00088240  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 8008B664 00088244  93 E1 00 14 */	stw r31, 0x14(r1)
/* 8008B668 00088248  93 C1 00 10 */	stw r30, 0x10(r1)
/* 8008B66C 0008824C  7C 7E 1B 78 */	mr r30, r3
/* 8008B670 00088250  80 63 00 2C */	lwz r3, 0x2c(r3)
/* 8008B674 00088254  80 03 06 68 */	lwz r0, 0x668(r3)
/* 8008B678 00088258  3B E3 00 00 */	addi r31, r3, 0
/* 8008B67C 0008825C  54 00 05 EF */	rlwinm. r0, r0, 0, 0x17, 0x17
/* 8008B680 00088260  41 82 00 EC */	beq lbl_8008B76C
/* 8008B684 00088264  C0 3F 06 20 */	lfs f1, 0x620(r31)
/* 8008B688 00088268  C0 1F 00 2C */	lfs f0, 0x2c(r31)
/* 8008B68C 0008826C  80 6D AE B4 */	lwz r3, p_ftCommonData(r13)
/* 8008B690 00088270  EC 21 00 32 */	fmuls f1, f1, f0
/* 8008B694 00088274  C0 03 00 98 */	lfs f0, 0x98(r3)
/* 8008B698 00088278  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8008B69C 0008827C  4C 41 13 82 */	cror 2, 1, 2
/* 8008B6A0 00088280  40 82 00 CC */	bne lbl_8008B76C
/* 8008B6A4 00088284  7F E3 FB 78 */	mr r3, r31
/* 8008B6A8 00088288  4B FF 22 BD */	bl func_8007D964
/* 8008B6AC 0008828C  C0 02 8A 88 */	lfs f0, lbl_804D8468(r2)
/* 8008B6B0 00088290  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8008B6B4 00088294  40 80 00 14 */	bge lbl_8008B6C8
/* 8008B6B8 00088298  7F E3 FB 78 */	mr r3, r31
/* 8008B6BC 0008829C  4B FF 22 A9 */	bl func_8007D964
/* 8008B6C0 000882A0  FC 20 08 50 */	fneg f1, f1
/* 8008B6C4 000882A4  48 00 00 0C */	b lbl_8008B6D0
lbl_8008B6C8:
/* 8008B6C8 000882A8  7F E3 FB 78 */	mr r3, r31
/* 8008B6CC 000882AC  4B FF 22 99 */	bl func_8007D964
lbl_8008B6D0:
/* 8008B6D0 000882B0  80 6D AE B4 */	lwz r3, p_ftCommonData(r13)
/* 8008B6D4 000882B4  C0 03 00 20 */	lfs f0, 0x20(r3)
/* 8008B6D8 000882B8  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8008B6DC 000882BC  40 80 00 90 */	bge lbl_8008B76C
/* 8008B6E0 000882C0  80 7F 19 74 */	lwz r3, 0x1974(r31)
/* 8008B6E4 000882C4  28 03 00 00 */	cmplwi r3, 0
/* 8008B6E8 000882C8  41 82 00 74 */	beq lbl_8008B75C
/* 8008B6EC 000882CC  80 1F 06 5C */	lwz r0, 0x65c(r31)
/* 8008B6F0 000882D0  54 00 00 01 */	rlwinm. r0, r0, 0, 0, 0
/* 8008B6F4 000882D4  40 82 00 10 */	bne lbl_8008B704
/* 8008B6F8 000882D8  48 1D FC 15 */	bl func_8026B30C
/* 8008B6FC 000882DC  2C 03 00 00 */	cmpwi r3, 0
/* 8008B700 000882E0  40 82 00 18 */	bne lbl_8008B718
lbl_8008B704:
/* 8008B704 000882E4  38 7E 00 00 */	addi r3, r30, 0
/* 8008B708 000882E8  38 80 00 5E */	li r4, 0x5e
/* 8008B70C 000882EC  48 00 A0 E9 */	bl func_800957F4
/* 8008B710 000882F0  38 60 00 01 */	li r3, 1
/* 8008B714 000882F4  48 00 00 5C */	b lbl_8008B770
lbl_8008B718:
/* 8008B718 000882F8  80 7F 19 74 */	lwz r3, 0x1974(r31)
/* 8008B71C 000882FC  48 1D FB F1 */	bl func_8026B30C
/* 8008B720 00088300  2C 03 00 03 */	cmpwi r3, 3
/* 8008B724 00088304  41 82 00 28 */	beq lbl_8008B74C
/* 8008B728 00088308  40 80 00 34 */	bge lbl_8008B75C
/* 8008B72C 0008830C  2C 03 00 02 */	cmpwi r3, 2
/* 8008B730 00088310  40 80 00 08 */	bge lbl_8008B738
/* 8008B734 00088314  48 00 00 28 */	b lbl_8008B75C
lbl_8008B738:
/* 8008B738 00088318  38 7E 00 00 */	addi r3, r30, 0
/* 8008B73C 0008831C  38 80 00 01 */	li r4, 1
/* 8008B740 00088320  48 04 18 19 */	bl func_800CCF58
/* 8008B744 00088324  38 60 00 01 */	li r3, 1
/* 8008B748 00088328  48 00 00 28 */	b lbl_8008B770
lbl_8008B74C:
/* 8008B74C 0008832C  7F C3 F3 78 */	mr r3, r30
/* 8008B750 00088330  48 04 25 C5 */	bl func_800CDD14
/* 8008B754 00088334  38 60 00 01 */	li r3, 1
/* 8008B758 00088338  48 00 00 18 */	b lbl_8008B770
lbl_8008B75C:
/* 8008B75C 0008833C  7F C3 F3 78 */	mr r3, r30
/* 8008B760 00088340  48 00 00 29 */	bl func_8008B788
/* 8008B764 00088344  38 60 00 01 */	li r3, 1
/* 8008B768 00088348  48 00 00 08 */	b lbl_8008B770
lbl_8008B76C:
/* 8008B76C 0008834C  38 60 00 00 */	li r3, 0
lbl_8008B770:
/* 8008B770 00088350  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 8008B774 00088354  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 8008B778 00088358  83 C1 00 10 */	lwz r30, 0x10(r1)
/* 8008B77C 0008835C  38 21 00 18 */	addi r1, r1, 0x18
/* 8008B780 00088360  7C 08 03 A6 */	mtlr r0
/* 8008B784 00088364  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

extern f32 const lbl_804D846C;

#pragma push
asm unk_t func_8008B788()
{ // clang-format off
    nofralloc
/* 8008B788 00088368  7C 08 02 A6 */	mflr r0
/* 8008B78C 0008836C  90 01 00 04 */	stw r0, 4(r1)
/* 8008B790 00088370  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 8008B794 00088374  DB E1 00 18 */	stfd f31, 0x18(r1)
/* 8008B798 00088378  93 E1 00 14 */	stw r31, 0x14(r1)
/* 8008B79C 0008837C  93 C1 00 10 */	stw r30, 0x10(r1)
/* 8008B7A0 00088380  7C 7E 1B 78 */	mr r30, r3
/* 8008B7A4 00088384  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 8008B7A8 00088388  48 00 8F E9 */	bl func_80094790
/* 8008B7AC 0008838C  2C 03 00 00 */	cmpwi r3, 0
/* 8008B7B0 00088390  40 82 01 08 */	bne lbl_8008B8B8
/* 8008B7B4 00088394  7F E3 FB 78 */	mr r3, r31
/* 8008B7B8 00088398  4B FF 21 AD */	bl func_8007D964
/* 8008B7BC 0008839C  80 6D AE B4 */	lwz r3, p_ftCommonData(r13)
/* 8008B7C0 000883A0  FF E0 08 90 */	fmr f31, f1
/* 8008B7C4 000883A4  C0 03 00 9C */	lfs f0, 0x9c(r3)
/* 8008B7C8 000883A8  FC 1F 00 40 */	fcmpo cr0, f31, f0
/* 8008B7CC 000883AC  40 81 00 24 */	ble lbl_8008B7F0
/* 8008B7D0 000883B0  38 7F 00 00 */	addi r3, r31, 0
/* 8008B7D4 000883B4  38 80 00 35 */	li r4, 0x35
/* 8008B7D8 000883B8  4B FF A7 FD */	bl func_80085FD4
/* 8008B7DC 000883BC  80 03 00 08 */	lwz r0, 8(r3)
/* 8008B7E0 000883C0  28 00 00 00 */	cmplwi r0, 0
/* 8008B7E4 000883C4  41 82 00 0C */	beq lbl_8008B7F0
/* 8008B7E8 000883C8  38 80 00 33 */	li r4, 0x33
/* 8008B7EC 000883CC  48 00 00 98 */	b lbl_8008B884
lbl_8008B7F0:
/* 8008B7F0 000883D0  80 6D AE B4 */	lwz r3, p_ftCommonData(r13)
/* 8008B7F4 000883D4  C0 03 00 A0 */	lfs f0, 0xa0(r3)
/* 8008B7F8 000883D8  FC 1F 00 40 */	fcmpo cr0, f31, f0
/* 8008B7FC 000883DC  40 81 00 24 */	ble lbl_8008B820
/* 8008B800 000883E0  38 7F 00 00 */	addi r3, r31, 0
/* 8008B804 000883E4  38 80 00 36 */	li r4, 0x36
/* 8008B808 000883E8  4B FF A7 CD */	bl func_80085FD4
/* 8008B80C 000883EC  80 03 00 08 */	lwz r0, 8(r3)
/* 8008B810 000883F0  28 00 00 00 */	cmplwi r0, 0
/* 8008B814 000883F4  41 82 00 0C */	beq lbl_8008B820
/* 8008B818 000883F8  38 80 00 34 */	li r4, 0x34
/* 8008B81C 000883FC  48 00 00 68 */	b lbl_8008B884
lbl_8008B820:
/* 8008B820 00088400  80 6D AE B4 */	lwz r3, p_ftCommonData(r13)
/* 8008B824 00088404  C0 03 00 A8 */	lfs f0, 0xa8(r3)
/* 8008B828 00088408  FC 1F 00 40 */	fcmpo cr0, f31, f0
/* 8008B82C 0008840C  40 80 00 24 */	bge lbl_8008B850
/* 8008B830 00088410  38 7F 00 00 */	addi r3, r31, 0
/* 8008B834 00088414  38 80 00 39 */	li r4, 0x39
/* 8008B838 00088418  4B FF A7 9D */	bl func_80085FD4
/* 8008B83C 0008841C  80 03 00 08 */	lwz r0, 8(r3)
/* 8008B840 00088420  28 00 00 00 */	cmplwi r0, 0
/* 8008B844 00088424  41 82 00 0C */	beq lbl_8008B850
/* 8008B848 00088428  38 80 00 37 */	li r4, 0x37
/* 8008B84C 0008842C  48 00 00 38 */	b lbl_8008B884
lbl_8008B850:
/* 8008B850 00088430  80 6D AE B4 */	lwz r3, p_ftCommonData(r13)
/* 8008B854 00088434  C0 03 00 A4 */	lfs f0, 0xa4(r3)
/* 8008B858 00088438  FC 1F 00 40 */	fcmpo cr0, f31, f0
/* 8008B85C 0008843C  40 80 00 24 */	bge lbl_8008B880
/* 8008B860 00088440  38 7F 00 00 */	addi r3, r31, 0
/* 8008B864 00088444  38 80 00 38 */	li r4, 0x38
/* 8008B868 00088448  4B FF A7 6D */	bl func_80085FD4
/* 8008B86C 0008844C  80 03 00 08 */	lwz r0, 8(r3)
/* 8008B870 00088450  28 00 00 00 */	cmplwi r0, 0
/* 8008B874 00088454  41 82 00 0C */	beq lbl_8008B880
/* 8008B878 00088458  38 80 00 36 */	li r4, 0x36
/* 8008B87C 0008845C  48 00 00 08 */	b lbl_8008B884
lbl_8008B880:
/* 8008B880 00088460  38 80 00 35 */	li r4, 0x35
lbl_8008B884:
/* 8008B884 00088464  88 1F 22 18 */	lbz r0, 0x2218(r31)
/* 8008B888 00088468  38 60 00 00 */	li r3, 0
/* 8008B88C 0008846C  50 60 3E 30 */	rlwimi r0, r3, 7, 0x18, 0x18
/* 8008B890 00088470  98 1F 22 18 */	stb r0, 0x2218(r31)
/* 8008B894 00088474  7F C3 F3 78 */	mr r3, r30
/* 8008B898 00088478  38 A0 00 00 */	li r5, 0
/* 8008B89C 0008847C  C0 22 8A 88 */	lfs f1, lbl_804D8468(r2)
/* 8008B8A0 00088480  38 C0 00 00 */	li r6, 0
/* 8008B8A4 00088484  C0 42 8A 8C */	lfs f2, lbl_804D846C(r2)
/* 8008B8A8 00088488  FC 60 08 90 */	fmr f3, f1
/* 8008B8AC 0008848C  4B FD DB 01 */	bl Fighter_ActionStateChange_800693AC
/* 8008B8B0 00088490  7F C3 F3 78 */	mr r3, r30
/* 8008B8B4 00088494  4B FE 32 F1 */	bl func_8006EBA4
lbl_8008B8B8:
/* 8008B8B8 00088498  80 01 00 24 */	lwz r0, 0x24(r1)
/* 8008B8BC 0008849C  CB E1 00 18 */	lfd f31, 0x18(r1)
/* 8008B8C0 000884A0  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 8008B8C4 000884A4  83 C1 00 10 */	lwz r30, 0x10(r1)
/* 8008B8C8 000884A8  38 21 00 20 */	addi r1, r1, 0x20
/* 8008B8CC 000884AC  7C 08 03 A6 */	mtlr r0
/* 8008B8D0 000884B0  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

#pragma push
asm unk_t func_8008B8D4()
{ // clang-format off
    nofralloc
/* 8008B8D4 000884B4  7C 08 02 A6 */	mflr r0
/* 8008B8D8 000884B8  90 01 00 04 */	stw r0, 4(r1)
/* 8008B8DC 000884BC  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 8008B8E0 000884C0  93 E1 00 14 */	stw r31, 0x14(r1)
/* 8008B8E4 000884C4  7C 7F 1B 78 */	mr r31, r3
/* 8008B8E8 000884C8  4B FE 39 51 */	bl ftAnim_IsFramesRemaining
/* 8008B8EC 000884CC  2C 03 00 00 */	cmpwi r3, 0
/* 8008B8F0 000884D0  40 82 00 0C */	bne lbl_8008B8FC
/* 8008B8F4 000884D4  7F E3 FB 78 */	mr r3, r31
/* 8008B8F8 000884D8  4B FF E9 C5 */	bl func_8008A2BC
lbl_8008B8FC:
/* 8008B8FC 000884DC  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 8008B900 000884E0  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 8008B904 000884E4  38 21 00 18 */	addi r1, r1, 0x18
/* 8008B908 000884E8  7C 08 03 A6 */	mtlr r0
/* 8008B90C 000884EC  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

#pragma push
asm unk_t func_8008B910()
{ // clang-format off
    nofralloc
/* 8008B910 000884F0  7C 08 02 A6 */	mflr r0
/* 8008B914 000884F4  90 01 00 04 */	stw r0, 4(r1)
/* 8008B918 000884F8  94 21 FF F8 */	stwu r1, -8(r1)
/* 8008B91C 000884FC  80 83 00 2C */	lwz r4, 0x2c(r3)
/* 8008B920 00088500  88 04 22 18 */	lbz r0, 0x2218(r4)
/* 8008B924 00088504  54 00 CF FF */	rlwinm. r0, r0, 0x19, 0x1f, 0x1f
/* 8008B928 00088508  41 82 00 08 */	beq lbl_8008B930
/* 8008B92C 0008850C  4B FF EB A9 */	bl func_8008A4D4
lbl_8008B930:
/* 8008B930 00088510  80 01 00 0C */	lwz r0, 0xc(r1)
/* 8008B934 00088514  38 21 00 08 */	addi r1, r1, 8
/* 8008B938 00088518  7C 08 03 A6 */	mtlr r0
/* 8008B93C 0008851C  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

#pragma push
asm unk_t func_8008B940()
{ // clang-format off
    nofralloc
/* 8008B940 00088520  7C 08 02 A6 */	mflr r0
/* 8008B944 00088524  90 01 00 04 */	stw r0, 4(r1)
/* 8008B948 00088528  94 21 FF F8 */	stwu r1, -8(r1)
/* 8008B94C 0008852C  4B FF 95 F1 */	bl func_80084F3C
/* 8008B950 00088530  80 01 00 0C */	lwz r0, 0xc(r1)
/* 8008B954 00088534  38 21 00 08 */	addi r1, r1, 8
/* 8008B958 00088538  7C 08 03 A6 */	mtlr r0
/* 8008B95C 0008853C  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

#pragma push
asm unk_t func_8008B960()
{ // clang-format off
    nofralloc
/* 8008B960 00088540  7C 08 02 A6 */	mflr r0
/* 8008B964 00088544  90 01 00 04 */	stw r0, 4(r1)
/* 8008B968 00088548  94 21 FF F8 */	stwu r1, -8(r1)
/* 8008B96C 0008854C  4B FF 87 99 */	bl func_80084104
/* 8008B970 00088550  80 01 00 0C */	lwz r0, 0xc(r1)
/* 8008B974 00088554  38 21 00 08 */	addi r1, r1, 8
/* 8008B978 00088558  7C 08 03 A6 */	mtlr r0
/* 8008B97C 0008855C  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

extern unk_t func_8008BA38();
extern unk_t func_80094E54();

#pragma push
asm BOOL func_8008B980(HSD_GObj* fighter_gobj)
{ // clang-format off
    nofralloc
/* 8008B980 00088560  7C 08 02 A6 */	mflr r0
/* 8008B984 00088564  90 01 00 04 */	stw r0, 4(r1)
/* 8008B988 00088568  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 8008B98C 0008856C  93 E1 00 14 */	stw r31, 0x14(r1)
/* 8008B990 00088570  93 C1 00 10 */	stw r30, 0x10(r1)
/* 8008B994 00088574  7C 7E 1B 78 */	mr r30, r3
/* 8008B998 00088578  80 63 00 2C */	lwz r3, 0x2c(r3)
/* 8008B99C 0008857C  80 03 06 68 */	lwz r0, 0x668(r3)
/* 8008B9A0 00088580  3B E3 00 00 */	addi r31, r3, 0
/* 8008B9A4 00088584  54 00 05 EF */	rlwinm. r0, r0, 0, 0x17, 0x17
/* 8008B9A8 00088588  41 82 00 74 */	beq lbl_8008BA1C
/* 8008B9AC 0008858C  80 6D AE B4 */	lwz r3, p_ftCommonData(r13)
/* 8008B9B0 00088590  C0 3F 06 24 */	lfs f1, 0x624(r31)
/* 8008B9B4 00088594  C0 03 00 AC */	lfs f0, 0xac(r3)
/* 8008B9B8 00088598  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8008B9BC 0008859C  4C 41 13 82 */	cror 2, 1, 2
/* 8008B9C0 000885A0  40 82 00 5C */	bne lbl_8008BA1C
/* 8008B9C4 000885A4  7F E3 FB 78 */	mr r3, r31
/* 8008B9C8 000885A8  4B FF 1F 9D */	bl func_8007D964
/* 8008B9CC 000885AC  80 6D AE B4 */	lwz r3, p_ftCommonData(r13)
/* 8008B9D0 000885B0  C0 03 00 20 */	lfs f0, 0x20(r3)
/* 8008B9D4 000885B4  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8008B9D8 000885B8  40 81 00 44 */	ble lbl_8008BA1C
/* 8008B9DC 000885BC  80 1F 19 74 */	lwz r0, 0x1974(r31)
/* 8008B9E0 000885C0  28 00 00 00 */	cmplwi r0, 0
/* 8008B9E4 000885C4  41 82 00 28 */	beq lbl_8008BA0C
/* 8008B9E8 000885C8  7F E3 FB 78 */	mr r3, r31
/* 8008B9EC 000885CC  48 00 94 69 */	bl func_80094E54
/* 8008B9F0 000885D0  2C 03 00 00 */	cmpwi r3, 0
/* 8008B9F4 000885D4  41 82 00 18 */	beq lbl_8008BA0C
/* 8008B9F8 000885D8  38 7E 00 00 */	addi r3, r30, 0
/* 8008B9FC 000885DC  38 80 00 60 */	li r4, 0x60
/* 8008BA00 000885E0  48 00 9D F5 */	bl func_800957F4
/* 8008BA04 000885E4  38 60 00 01 */	li r3, 1
/* 8008BA08 000885E8  48 00 00 18 */	b lbl_8008BA20
lbl_8008BA0C:
/* 8008BA0C 000885EC  7F C3 F3 78 */	mr r3, r30
/* 8008BA10 000885F0  48 00 00 29 */	bl func_8008BA38
/* 8008BA14 000885F4  38 60 00 01 */	li r3, 1
/* 8008BA18 000885F8  48 00 00 08 */	b lbl_8008BA20
lbl_8008BA1C:
/* 8008BA1C 000885FC  38 60 00 00 */	li r3, 0
lbl_8008BA20:
/* 8008BA20 00088600  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 8008BA24 00088604  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 8008BA28 00088608  83 C1 00 10 */	lwz r30, 0x10(r1)
/* 8008BA2C 0008860C  38 21 00 18 */	addi r1, r1, 0x18
/* 8008BA30 00088610  7C 08 03 A6 */	mtlr r0
/* 8008BA34 00088614  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

extern f32 const lbl_804D8470;
extern f32 const lbl_804D8474;

#pragma push
asm unk_t func_8008BA38()
{ // clang-format off
    nofralloc
/* 8008BA38 00088618  7C 08 02 A6 */	mflr r0
/* 8008BA3C 0008861C  38 80 00 00 */	li r4, 0
/* 8008BA40 00088620  90 01 00 04 */	stw r0, 4(r1)
/* 8008BA44 00088624  38 C0 00 00 */	li r6, 0
/* 8008BA48 00088628  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 8008BA4C 0008862C  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 8008BA50 00088630  7C 7F 1B 78 */	mr r31, r3
/* 8008BA54 00088634  80 A3 00 2C */	lwz r5, 0x2c(r3)
/* 8008BA58 00088638  88 05 22 18 */	lbz r0, 0x2218(r5)
/* 8008BA5C 0008863C  50 80 3E 30 */	rlwimi r0, r4, 7, 0x18, 0x18
/* 8008BA60 00088640  38 80 00 38 */	li r4, 0x38
/* 8008BA64 00088644  98 05 22 18 */	stb r0, 0x2218(r5)
/* 8008BA68 00088648  38 A0 00 00 */	li r5, 0
/* 8008BA6C 0008864C  C0 22 8A 90 */	lfs f1, lbl_804D8470(r2)
/* 8008BA70 00088650  C0 42 8A 94 */	lfs f2, lbl_804D8474(r2)
/* 8008BA74 00088654  FC 60 08 90 */	fmr f3, f1
/* 8008BA78 00088658  4B FD D9 35 */	bl Fighter_ActionStateChange_800693AC
/* 8008BA7C 0008865C  7F E3 FB 78 */	mr r3, r31
/* 8008BA80 00088660  4B FE 31 25 */	bl func_8006EBA4
/* 8008BA84 00088664  80 01 00 24 */	lwz r0, 0x24(r1)
/* 8008BA88 00088668  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 8008BA8C 0008866C  38 21 00 20 */	addi r1, r1, 0x20
/* 8008BA90 00088670  7C 08 03 A6 */	mtlr r0
/* 8008BA94 00088674  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

#pragma push
asm unk_t func_8008BA98()
{ // clang-format off
    nofralloc
/* 8008BA98 00088678  7C 08 02 A6 */	mflr r0
/* 8008BA9C 0008867C  90 01 00 04 */	stw r0, 4(r1)
/* 8008BAA0 00088680  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 8008BAA4 00088684  93 E1 00 14 */	stw r31, 0x14(r1)
/* 8008BAA8 00088688  7C 7F 1B 78 */	mr r31, r3
/* 8008BAAC 0008868C  4B FE 37 8D */	bl ftAnim_IsFramesRemaining
/* 8008BAB0 00088690  2C 03 00 00 */	cmpwi r3, 0
/* 8008BAB4 00088694  40 82 00 0C */	bne lbl_8008BAC0
/* 8008BAB8 00088698  7F E3 FB 78 */	mr r3, r31
/* 8008BABC 0008869C  4B FF E8 01 */	bl func_8008A2BC
lbl_8008BAC0:
/* 8008BAC0 000886A0  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 8008BAC4 000886A4  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 8008BAC8 000886A8  38 21 00 18 */	addi r1, r1, 0x18
/* 8008BACC 000886AC  7C 08 03 A6 */	mtlr r0
/* 8008BAD0 000886B0  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

#pragma push
asm unk_t func_8008BAD4()
{ // clang-format off
    nofralloc
/* 8008BAD4 000886B4  7C 08 02 A6 */	mflr r0
/* 8008BAD8 000886B8  90 01 00 04 */	stw r0, 4(r1)
/* 8008BADC 000886BC  94 21 FF F8 */	stwu r1, -8(r1)
/* 8008BAE0 000886C0  80 83 00 2C */	lwz r4, 0x2c(r3)
/* 8008BAE4 000886C4  88 04 22 18 */	lbz r0, 0x2218(r4)
/* 8008BAE8 000886C8  54 00 CF FF */	rlwinm. r0, r0, 0x19, 0x1f, 0x1f
/* 8008BAEC 000886CC  41 82 00 08 */	beq lbl_8008BAF4
/* 8008BAF0 000886D0  4B FF E9 E5 */	bl func_8008A4D4
lbl_8008BAF4:
/* 8008BAF4 000886D4  80 01 00 0C */	lwz r0, 0xc(r1)
/* 8008BAF8 000886D8  38 21 00 08 */	addi r1, r1, 8
/* 8008BAFC 000886DC  7C 08 03 A6 */	mtlr r0
/* 8008BB00 000886E0  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

#pragma push
asm unk_t func_8008BB04()
{ // clang-format off
    nofralloc
/* 8008BB04 000886E4  7C 08 02 A6 */	mflr r0
/* 8008BB08 000886E8  90 01 00 04 */	stw r0, 4(r1)
/* 8008BB0C 000886EC  94 21 FF F8 */	stwu r1, -8(r1)
/* 8008BB10 000886F0  4B FF 94 2D */	bl func_80084F3C
/* 8008BB14 000886F4  80 01 00 0C */	lwz r0, 0xc(r1)
/* 8008BB18 000886F8  38 21 00 08 */	addi r1, r1, 8
/* 8008BB1C 000886FC  7C 08 03 A6 */	mtlr r0
/* 8008BB20 00088700  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

#pragma push
asm unk_t func_8008BB24()
{ // clang-format off
    nofralloc
/* 8008BB24 00088704  7C 08 02 A6 */	mflr r0
/* 8008BB28 00088708  90 01 00 04 */	stw r0, 4(r1)
/* 8008BB2C 0008870C  94 21 FF F8 */	stwu r1, -8(r1)
/* 8008BB30 00088710  4B FF 85 D5 */	bl func_80084104
/* 8008BB34 00088714  80 01 00 0C */	lwz r0, 0xc(r1)
/* 8008BB38 00088718  38 21 00 08 */	addi r1, r1, 8
/* 8008BB3C 0008871C  7C 08 03 A6 */	mtlr r0
/* 8008BB40 00088720  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

extern unk_t func_8008BC34();

#pragma push
asm BOOL func_8008BB44(HSD_GObj* fighter_gobj)
{ // clang-format off
    nofralloc
/* 8008BB44 00088724  7C 08 02 A6 */	mflr r0
/* 8008BB48 00088728  90 01 00 04 */	stw r0, 4(r1)
/* 8008BB4C 0008872C  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 8008BB50 00088730  93 E1 00 14 */	stw r31, 0x14(r1)
/* 8008BB54 00088734  93 C1 00 10 */	stw r30, 0x10(r1)
/* 8008BB58 00088738  7C 7E 1B 78 */	mr r30, r3
/* 8008BB5C 0008873C  80 63 00 2C */	lwz r3, 0x2c(r3)
/* 8008BB60 00088740  80 03 06 68 */	lwz r0, 0x668(r3)
/* 8008BB64 00088744  3B E3 00 00 */	addi r31, r3, 0
/* 8008BB68 00088748  54 00 05 EF */	rlwinm. r0, r0, 0, 0x17, 0x17
/* 8008BB6C 0008874C  41 82 00 78 */	beq lbl_8008BBE4
/* 8008BB70 00088750  80 6D AE B4 */	lwz r3, p_ftCommonData(r13)
/* 8008BB74 00088754  C0 3F 06 24 */	lfs f1, 0x624(r31)
/* 8008BB78 00088758  C0 03 00 B0 */	lfs f0, 0xb0(r3)
/* 8008BB7C 0008875C  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8008BB80 00088760  4C 40 13 82 */	cror 2, 0, 2
/* 8008BB84 00088764  40 82 00 60 */	bne lbl_8008BBE4
/* 8008BB88 00088768  7F E3 FB 78 */	mr r3, r31
/* 8008BB8C 0008876C  4B FF 1D D9 */	bl func_8007D964
/* 8008BB90 00088770  80 6D AE B4 */	lwz r3, p_ftCommonData(r13)
/* 8008BB94 00088774  C0 03 00 20 */	lfs f0, 0x20(r3)
/* 8008BB98 00088778  FC 00 00 50 */	fneg f0, f0
/* 8008BB9C 0008877C  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8008BBA0 00088780  40 80 00 44 */	bge lbl_8008BBE4
/* 8008BBA4 00088784  80 1F 19 74 */	lwz r0, 0x1974(r31)
/* 8008BBA8 00088788  28 00 00 00 */	cmplwi r0, 0
/* 8008BBAC 0008878C  41 82 00 28 */	beq lbl_8008BBD4
/* 8008BBB0 00088790  7F E3 FB 78 */	mr r3, r31
/* 8008BBB4 00088794  48 00 92 A1 */	bl func_80094E54
/* 8008BBB8 00088798  2C 03 00 00 */	cmpwi r3, 0
/* 8008BBBC 0008879C  41 82 00 18 */	beq lbl_8008BBD4
/* 8008BBC0 000887A0  38 7E 00 00 */	addi r3, r30, 0
/* 8008BBC4 000887A4  38 80 00 61 */	li r4, 0x61
/* 8008BBC8 000887A8  48 00 9C 2D */	bl func_800957F4
/* 8008BBCC 000887AC  38 60 00 01 */	li r3, 1
/* 8008BBD0 000887B0  48 00 00 18 */	b lbl_8008BBE8
lbl_8008BBD4:
/* 8008BBD4 000887B4  7F C3 F3 78 */	mr r3, r30
/* 8008BBD8 000887B8  48 00 00 5D */	bl func_8008BC34
/* 8008BBDC 000887BC  38 60 00 01 */	li r3, 1
/* 8008BBE0 000887C0  48 00 00 08 */	b lbl_8008BBE8
lbl_8008BBE4:
/* 8008BBE4 000887C4  38 60 00 00 */	li r3, 0
lbl_8008BBE8:
/* 8008BBE8 000887C8  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 8008BBEC 000887CC  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 8008BBF0 000887D0  83 C1 00 10 */	lwz r30, 0x10(r1)
/* 8008BBF4 000887D4  38 21 00 18 */	addi r1, r1, 0x18
/* 8008BBF8 000887D8  7C 08 03 A6 */	mtlr r0
/* 8008BBFC 000887DC  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

#pragma push
asm unk_t lbl_8008BC00()
{ // clang-format off
    nofralloc
/* 8008BC00 000887E0  7C 08 02 A6 */	mflr r0
/* 8008BC04 000887E4  90 01 00 04 */	stw r0, 4(r1)
/* 8008BC08 000887E8  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 8008BC0C 000887EC  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 8008BC10 000887F0  7C 7F 1B 78 */	mr r31, r3
/* 8008BC14 000887F4  4B FF D6 8D */	bl func_800892A0
/* 8008BC18 000887F8  7F E3 FB 78 */	mr r3, r31
/* 8008BC1C 000887FC  4B FF DC 09 */	bl func_80089824
/* 8008BC20 00088800  80 01 00 24 */	lwz r0, 0x24(r1)
/* 8008BC24 00088804  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 8008BC28 00088808  38 21 00 20 */	addi r1, r1, 0x20
/* 8008BC2C 0008880C  7C 08 03 A6 */	mtlr r0
/* 8008BC30 00088810  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

extern unk_t func_8008BC70();

#pragma push
asm unk_t func_8008BC34()
{ // clang-format off
    nofralloc
/* 8008BC34 00088814  7C 08 02 A6 */	mflr r0
/* 8008BC38 00088818  90 01 00 04 */	stw r0, 4(r1)
/* 8008BC3C 0008881C  94 21 FF F8 */	stwu r1, -8(r1)
/* 8008BC40 00088820  80 83 00 2C */	lwz r4, 0x2c(r3)
/* 8008BC44 00088824  80 04 00 04 */	lwz r0, 4(r4)
/* 8008BC48 00088828  2C 00 00 18 */	cmpwi r0, 0x18
/* 8008BC4C 0008882C  41 82 00 08 */	beq lbl_8008BC54
/* 8008BC50 00088830  48 00 00 0C */	b lbl_8008BC5C
lbl_8008BC54:
/* 8008BC54 00088834  48 0B F1 65 */	bl ftGameWatch_AttackLw3_Action
/* 8008BC58 00088838  48 00 00 08 */	b lbl_8008BC60
lbl_8008BC5C:
/* 8008BC5C 0008883C  48 00 00 15 */	bl func_8008BC70
lbl_8008BC60:
/* 8008BC60 00088840  80 01 00 0C */	lwz r0, 0xc(r1)
/* 8008BC64 00088844  38 21 00 08 */	addi r1, r1, 8
/* 8008BC68 00088848  7C 08 03 A6 */	mtlr r0
/* 8008BC6C 0008884C  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

extern f32 const lbl_804D8478;
extern f32 const lbl_804D847C;

#pragma push
asm unk_t func_8008BC70()
{ // clang-format off
    nofralloc
/* 8008BC70 00088850  7C 08 02 A6 */	mflr r0
/* 8008BC74 00088854  90 01 00 04 */	stw r0, 4(r1)
/* 8008BC78 00088858  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 8008BC7C 0008885C  93 E1 00 14 */	stw r31, 0x14(r1)
/* 8008BC80 00088860  93 C1 00 10 */	stw r30, 0x10(r1)
/* 8008BC84 00088864  7C 7E 1B 78 */	mr r30, r3
/* 8008BC88 00088868  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 8008BC8C 0008886C  48 00 8B 05 */	bl func_80094790
/* 8008BC90 00088870  2C 03 00 00 */	cmpwi r3, 0
/* 8008BC94 00088874  40 82 00 50 */	bne lbl_8008BCE4
/* 8008BC98 00088878  38 C0 00 00 */	li r6, 0
/* 8008BC9C 0008887C  90 DF 22 00 */	stw r6, 0x2200(r31)
/* 8008BCA0 00088880  3C 60 80 09 */	lis r3, lbl_8008BC00@ha
/* 8008BCA4 00088884  38 03 BC 00 */	addi r0, r3, lbl_8008BC00@l
/* 8008BCA8 00088888  88 9F 22 18 */	lbz r4, 0x2218(r31)
/* 8008BCAC 0008888C  50 C4 3E 30 */	rlwimi r4, r6, 7, 0x18, 0x18
/* 8008BCB0 00088890  38 7E 00 00 */	addi r3, r30, 0
/* 8008BCB4 00088894  98 9F 22 18 */	stb r4, 0x2218(r31)
/* 8008BCB8 00088898  38 80 00 39 */	li r4, 0x39
/* 8008BCBC 0008889C  3C A0 02 00 */	lis r5, 0x200
/* 8008BCC0 000888A0  90 DF 23 40 */	stw r6, 0x2340(r31)
/* 8008BCC4 000888A4  38 C0 00 00 */	li r6, 0
/* 8008BCC8 000888A8  90 1F 21 EC */	stw r0, 0x21ec(r31)
/* 8008BCCC 000888AC  C0 22 8A 98 */	lfs f1, lbl_804D8478(r2)
/* 8008BCD0 000888B0  C0 42 8A 9C */	lfs f2, lbl_804D847C(r2)
/* 8008BCD4 000888B4  FC 60 08 90 */	fmr f3, f1
/* 8008BCD8 000888B8  4B FD D6 D5 */	bl Fighter_ActionStateChange_800693AC
/* 8008BCDC 000888BC  7F C3 F3 78 */	mr r3, r30
/* 8008BCE0 000888C0  4B FE 2E C5 */	bl func_8006EBA4
lbl_8008BCE4:
/* 8008BCE4 000888C4  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 8008BCE8 000888C8  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 8008BCEC 000888CC  83 C1 00 10 */	lwz r30, 0x10(r1)
/* 8008BCF0 000888D0  38 21 00 18 */	addi r1, r1, 0x18
/* 8008BCF4 000888D4  7C 08 03 A6 */	mtlr r0
/* 8008BCF8 000888D8  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

#pragma push
asm unk_t func_8008BCFC()
{ // clang-format off
    nofralloc
/* 8008BCFC 000888DC  7C 08 02 A6 */	mflr r0
/* 8008BD00 000888E0  90 01 00 04 */	stw r0, 4(r1)
/* 8008BD04 000888E4  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 8008BD08 000888E8  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 8008BD0C 000888EC  7C 7F 1B 78 */	mr r31, r3
/* 8008BD10 000888F0  80 63 00 2C */	lwz r3, 0x2c(r3)
/* 8008BD14 000888F4  80 03 22 00 */	lwz r0, 0x2200(r3)
/* 8008BD18 000888F8  28 00 00 00 */	cmplwi r0, 0
/* 8008BD1C 000888FC  41 82 00 38 */	beq lbl_8008BD54
/* 8008BD20 00088900  80 03 23 40 */	lwz r0, 0x2340(r3)
/* 8008BD24 00088904  2C 00 00 00 */	cmpwi r0, 0
/* 8008BD28 00088908  41 82 00 2C */	beq lbl_8008BD54
/* 8008BD2C 0008890C  80 03 00 04 */	lwz r0, 4(r3)
/* 8008BD30 00088910  2C 00 00 18 */	cmpwi r0, 0x18
/* 8008BD34 00088914  41 82 00 08 */	beq lbl_8008BD3C
/* 8008BD38 00088918  48 00 00 10 */	b lbl_8008BD48
lbl_8008BD3C:
/* 8008BD3C 0008891C  7F E3 FB 78 */	mr r3, r31
/* 8008BD40 00088920  48 0B F0 79 */	bl ftGameWatch_AttackLw3_Action
/* 8008BD44 00088924  48 00 00 28 */	b lbl_8008BD6C
lbl_8008BD48:
/* 8008BD48 00088928  7F E3 FB 78 */	mr r3, r31
/* 8008BD4C 0008892C  4B FF FF 25 */	bl func_8008BC70
/* 8008BD50 00088930  48 00 00 1C */	b lbl_8008BD6C
lbl_8008BD54:
/* 8008BD54 00088934  7F E3 FB 78 */	mr r3, r31
/* 8008BD58 00088938  4B FE 34 E1 */	bl ftAnim_IsFramesRemaining
/* 8008BD5C 0008893C  2C 03 00 00 */	cmpwi r3, 0
/* 8008BD60 00088940  40 82 00 0C */	bne lbl_8008BD6C
/* 8008BD64 00088944  7F E3 FB 78 */	mr r3, r31
/* 8008BD68 00088948  48 04 A6 25 */	bl func_800D638C
lbl_8008BD6C:
/* 8008BD6C 0008894C  80 01 00 24 */	lwz r0, 0x24(r1)
/* 8008BD70 00088950  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 8008BD74 00088954  38 21 00 20 */	addi r1, r1, 0x20
/* 8008BD78 00088958  7C 08 03 A6 */	mtlr r0
/* 8008BD7C 0008895C  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

#pragma push
asm unk_t func_8008BD80()
{ // clang-format off
    nofralloc
/* 8008BD80 00088960  7C 08 02 A6 */	mflr r0
/* 8008BD84 00088964  90 01 00 04 */	stw r0, 4(r1)
/* 8008BD88 00088968  94 21 FF D0 */	stwu r1, -0x30(r1)
/* 8008BD8C 0008896C  93 E1 00 2C */	stw r31, 0x2c(r1)
/* 8008BD90 00088970  7C 7F 1B 78 */	mr r31, r3
/* 8008BD94 00088974  93 C1 00 28 */	stw r30, 0x28(r1)
/* 8008BD98 00088978  83 C3 00 2C */	lwz r30, 0x2c(r3)
/* 8008BD9C 0008897C  88 1E 22 18 */	lbz r0, 0x2218(r30)
/* 8008BDA0 00088980  54 00 CF FF */	rlwinm. r0, r0, 0x19, 0x1f, 0x1f
/* 8008BDA4 00088984  41 82 00 54 */	beq lbl_8008BDF8
/* 8008BDA8 00088988  7F E3 FB 78 */	mr r3, r31
/* 8008BDAC 0008898C  48 00 02 19 */	bl func_8008BFC4
/* 8008BDB0 00088990  2C 03 00 00 */	cmpwi r3, 0
/* 8008BDB4 00088994  40 82 01 B8 */	bne lbl_8008BF6C
/* 8008BDB8 00088998  7F E3 FB 78 */	mr r3, r31
/* 8008BDBC 0008899C  48 00 0A 75 */	bl func_8008C830
/* 8008BDC0 000889A0  2C 03 00 00 */	cmpwi r3, 0
/* 8008BDC4 000889A4  40 82 01 A8 */	bne lbl_8008BF6C
/* 8008BDC8 000889A8  7F E3 FB 78 */	mr r3, r31
/* 8008BDCC 000889AC  48 00 0D 79 */	bl func_8008CB44
/* 8008BDD0 000889B0  2C 03 00 00 */	cmpwi r3, 0
/* 8008BDD4 000889B4  40 82 01 98 */	bne lbl_8008BF6C
/* 8008BDD8 000889B8  7F E3 FB 78 */	mr r3, r31
/* 8008BDDC 000889BC  4B FF F8 7D */	bl func_8008B658
/* 8008BDE0 000889C0  2C 03 00 00 */	cmpwi r3, 0
/* 8008BDE4 000889C4  40 82 01 88 */	bne lbl_8008BF6C
/* 8008BDE8 000889C8  7F E3 FB 78 */	mr r3, r31
/* 8008BDEC 000889CC  4B FF FB 95 */	bl func_8008B980
/* 8008BDF0 000889D0  2C 03 00 00 */	cmpwi r3, 0
/* 8008BDF4 000889D4  40 82 01 78 */	bne lbl_8008BF6C
lbl_8008BDF8:
/* 8008BDF8 000889D8  80 7F 00 2C */	lwz r3, 0x2c(r31)
/* 8008BDFC 000889DC  80 03 06 68 */	lwz r0, 0x668(r3)
/* 8008BE00 000889E0  54 00 05 EF */	rlwinm. r0, r0, 0, 0x17, 0x17
/* 8008BE04 000889E4  41 82 00 44 */	beq lbl_8008BE48
/* 8008BE08 000889E8  80 03 22 00 */	lwz r0, 0x2200(r3)
/* 8008BE0C 000889EC  28 00 00 00 */	cmplwi r0, 0
/* 8008BE10 000889F0  41 82 00 30 */	beq lbl_8008BE40
/* 8008BE14 000889F4  80 03 00 04 */	lwz r0, 4(r3)
/* 8008BE18 000889F8  2C 00 00 18 */	cmpwi r0, 0x18
/* 8008BE1C 000889FC  41 82 00 08 */	beq lbl_8008BE24
/* 8008BE20 00088A00  48 00 00 10 */	b lbl_8008BE30
lbl_8008BE24:
/* 8008BE24 00088A04  7F E3 FB 78 */	mr r3, r31
/* 8008BE28 00088A08  48 0B EF 91 */	bl ftGameWatch_AttackLw3_Action
/* 8008BE2C 00088A0C  48 00 00 0C */	b lbl_8008BE38
lbl_8008BE30:
/* 8008BE30 00088A10  7F E3 FB 78 */	mr r3, r31
/* 8008BE34 00088A14  4B FF FE 3D */	bl func_8008BC70
lbl_8008BE38:
/* 8008BE38 00088A18  38 00 00 01 */	li r0, 1
/* 8008BE3C 00088A1C  48 00 00 10 */	b lbl_8008BE4C
lbl_8008BE40:
/* 8008BE40 00088A20  38 00 00 01 */	li r0, 1
/* 8008BE44 00088A24  90 03 23 40 */	stw r0, 0x2340(r3)
lbl_8008BE48:
/* 8008BE48 00088A28  38 00 00 00 */	li r0, 0
lbl_8008BE4C:
/* 8008BE4C 00088A2C  2C 00 00 00 */	cmpwi r0, 0
/* 8008BE50 00088A30  40 82 01 1C */	bne lbl_8008BF6C
/* 8008BE54 00088A34  88 1E 22 18 */	lbz r0, 0x2218(r30)
/* 8008BE58 00088A38  54 00 CF FF */	rlwinm. r0, r0, 0x19, 0x1f, 0x1f
/* 8008BE5C 00088A3C  41 82 01 10 */	beq lbl_8008BF6C
/* 8008BE60 00088A40  83 DF 00 2C */	lwz r30, 0x2c(r31)
/* 8008BE64 00088A44  80 1E 06 68 */	lwz r0, 0x668(r30)
/* 8008BE68 00088A48  54 00 05 EF */	rlwinm. r0, r0, 0, 0x17, 0x17
/* 8008BE6C 00088A4C  41 82 00 98 */	beq lbl_8008BF04
/* 8008BE70 00088A50  80 6D AE B4 */	lwz r3, p_ftCommonData(r13)
/* 8008BE74 00088A54  C0 3E 06 24 */	lfs f1, 0x624(r30)
/* 8008BE78 00088A58  C0 03 00 B0 */	lfs f0, 0xb0(r3)
/* 8008BE7C 00088A5C  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8008BE80 00088A60  4C 40 13 82 */	cror 2, 0, 2
/* 8008BE84 00088A64  40 82 00 80 */	bne lbl_8008BF04
/* 8008BE88 00088A68  7F C3 F3 78 */	mr r3, r30
/* 8008BE8C 00088A6C  4B FF 1A D9 */	bl func_8007D964
/* 8008BE90 00088A70  80 6D AE B4 */	lwz r3, p_ftCommonData(r13)
/* 8008BE94 00088A74  C0 03 00 20 */	lfs f0, 0x20(r3)
/* 8008BE98 00088A78  FC 00 00 50 */	fneg f0, f0
/* 8008BE9C 00088A7C  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8008BEA0 00088A80  40 80 00 64 */	bge lbl_8008BF04
/* 8008BEA4 00088A84  80 1E 19 74 */	lwz r0, 0x1974(r30)
/* 8008BEA8 00088A88  28 00 00 00 */	cmplwi r0, 0
/* 8008BEAC 00088A8C  41 82 00 28 */	beq lbl_8008BED4
/* 8008BEB0 00088A90  7F C3 F3 78 */	mr r3, r30
/* 8008BEB4 00088A94  48 00 8F A1 */	bl func_80094E54
/* 8008BEB8 00088A98  2C 03 00 00 */	cmpwi r3, 0
/* 8008BEBC 00088A9C  41 82 00 18 */	beq lbl_8008BED4
/* 8008BEC0 00088AA0  38 7F 00 00 */	addi r3, r31, 0
/* 8008BEC4 00088AA4  38 80 00 61 */	li r4, 0x61
/* 8008BEC8 00088AA8  48 00 99 2D */	bl func_800957F4
/* 8008BECC 00088AAC  38 00 00 01 */	li r0, 1
/* 8008BED0 00088AB0  48 00 00 38 */	b lbl_8008BF08
lbl_8008BED4:
/* 8008BED4 00088AB4  80 7F 00 2C */	lwz r3, 0x2c(r31)
/* 8008BED8 00088AB8  80 03 00 04 */	lwz r0, 4(r3)
/* 8008BEDC 00088ABC  2C 00 00 18 */	cmpwi r0, 0x18
/* 8008BEE0 00088AC0  41 82 00 08 */	beq lbl_8008BEE8
/* 8008BEE4 00088AC4  48 00 00 10 */	b lbl_8008BEF4
lbl_8008BEE8:
/* 8008BEE8 00088AC8  7F E3 FB 78 */	mr r3, r31
/* 8008BEEC 00088ACC  48 0B EE CD */	bl ftGameWatch_AttackLw3_Action
/* 8008BEF0 00088AD0  48 00 00 0C */	b lbl_8008BEFC
lbl_8008BEF4:
/* 8008BEF4 00088AD4  7F E3 FB 78 */	mr r3, r31
/* 8008BEF8 00088AD8  4B FF FD 79 */	bl func_8008BC70
lbl_8008BEFC:
/* 8008BEFC 00088ADC  38 00 00 01 */	li r0, 1
/* 8008BF00 00088AE0  48 00 00 08 */	b lbl_8008BF08
lbl_8008BF04:
/* 8008BF04 00088AE4  38 00 00 00 */	li r0, 0
lbl_8008BF08:
/* 8008BF08 00088AE8  2C 00 00 00 */	cmpwi r0, 0
/* 8008BF0C 00088AEC  40 82 00 60 */	bne lbl_8008BF6C
/* 8008BF10 00088AF0  7F E3 FB 78 */	mr r3, r31
/* 8008BF14 00088AF4  4B FF EA E5 */	bl func_8008A9F8
/* 8008BF18 00088AF8  2C 03 00 00 */	cmpwi r3, 0
/* 8008BF1C 00088AFC  40 82 00 50 */	bne lbl_8008BF6C
/* 8008BF20 00088B00  7F E3 FB 78 */	mr r3, r31
/* 8008BF24 00088B04  48 03 EF AD */	bl func_800CAED0
/* 8008BF28 00088B08  2C 03 00 00 */	cmpwi r3, 0
/* 8008BF2C 00088B0C  40 82 00 40 */	bne lbl_8008BF6C
/* 8008BF30 00088B10  7F E3 FB 78 */	mr r3, r31
/* 8008BF34 00088B14  48 03 E1 61 */	bl func_800CA094
/* 8008BF38 00088B18  2C 03 00 00 */	cmpwi r3, 0
/* 8008BF3C 00088B1C  40 82 00 30 */	bne lbl_8008BF6C
/* 8008BF40 00088B20  7F E3 FB 78 */	mr r3, r31
/* 8008BF44 00088B24  48 04 A0 15 */	bl func_800D5F58
/* 8008BF48 00088B28  2C 03 00 00 */	cmpwi r3, 0
/* 8008BF4C 00088B2C  40 82 00 20 */	bne lbl_8008BF6C
/* 8008BF50 00088B30  7F E3 FB 78 */	mr r3, r31
/* 8008BF54 00088B34  48 03 D8 89 */	bl func_800C97DC
/* 8008BF58 00088B38  2C 03 00 00 */	cmpwi r3, 0
/* 8008BF5C 00088B3C  40 82 00 10 */	bne lbl_8008BF6C
/* 8008BF60 00088B40  7F E3 FB 78 */	mr r3, r31
/* 8008BF64 00088B44  48 03 D5 05 */	bl func_800C9468
/* 8008BF68 00088B48  2C 03 00 00 */	cmpwi r3, 0
lbl_8008BF6C:
/* 8008BF6C 00088B4C  80 01 00 34 */	lwz r0, 0x34(r1)
/* 8008BF70 00088B50  83 E1 00 2C */	lwz r31, 0x2c(r1)
/* 8008BF74 00088B54  83 C1 00 28 */	lwz r30, 0x28(r1)
/* 8008BF78 00088B58  38 21 00 30 */	addi r1, r1, 0x30
/* 8008BF7C 00088B5C  7C 08 03 A6 */	mtlr r0
/* 8008BF80 00088B60  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

#pragma push
asm unk_t func_8008BF84()
{ // clang-format off
    nofralloc
/* 8008BF84 00088B64  7C 08 02 A6 */	mflr r0
/* 8008BF88 00088B68  90 01 00 04 */	stw r0, 4(r1)
/* 8008BF8C 00088B6C  94 21 FF F8 */	stwu r1, -8(r1)
/* 8008BF90 00088B70  4B FF 8F AD */	bl func_80084F3C
/* 8008BF94 00088B74  80 01 00 0C */	lwz r0, 0xc(r1)
/* 8008BF98 00088B78  38 21 00 08 */	addi r1, r1, 8
/* 8008BF9C 00088B7C  7C 08 03 A6 */	mtlr r0
/* 8008BFA0 00088B80  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

#pragma push
asm unk_t func_8008BFA4()
{ // clang-format off
    nofralloc
/* 8008BFA4 00088B84  7C 08 02 A6 */	mflr r0
/* 8008BFA8 00088B88  90 01 00 04 */	stw r0, 4(r1)
/* 8008BFAC 00088B8C  94 21 FF F8 */	stwu r1, -8(r1)
/* 8008BFB0 00088B90  4B FF 81 55 */	bl func_80084104
/* 8008BFB4 00088B94  80 01 00 0C */	lwz r0, 0xc(r1)
/* 8008BFB8 00088B98  38 21 00 08 */	addi r1, r1, 8
/* 8008BFBC 00088B9C  7C 08 03 A6 */	mtlr r0
/* 8008BFC0 00088BA0  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

extern f32 const lbl_804D8480;
extern f32 const lbl_804D8484;
extern f32 const lbl_804D8488;
extern unk_t func_8008C348();
extern unk_t func_8008C22C();
extern unk_t func_800DF1C8();

#pragma push
asm BOOL func_8008BFC4(HSD_GObj* fighter_gobj)
{ // clang-format off
    nofralloc
/* 8008BFC4 00088BA4  7C 08 02 A6 */	mflr r0
/* 8008BFC8 00088BA8  90 01 00 04 */	stw r0, 4(r1)
/* 8008BFCC 00088BAC  94 21 FF D8 */	stwu r1, -0x28(r1)
/* 8008BFD0 00088BB0  DB E1 00 20 */	stfd f31, 0x20(r1)
/* 8008BFD4 00088BB4  DB C1 00 18 */	stfd f30, 0x18(r1)
/* 8008BFD8 00088BB8  93 E1 00 14 */	stw r31, 0x14(r1)
/* 8008BFDC 00088BBC  93 C1 00 10 */	stw r30, 0x10(r1)
/* 8008BFE0 00088BC0  7C 7E 1B 78 */	mr r30, r3
/* 8008BFE4 00088BC4  80 63 00 2C */	lwz r3, 0x2c(r3)
/* 8008BFE8 00088BC8  80 03 06 68 */	lwz r0, 0x668(r3)
/* 8008BFEC 00088BCC  3B E3 00 00 */	addi r31, r3, 0
/* 8008BFF0 00088BD0  54 00 05 EF */	rlwinm. r0, r0, 0, 0x17, 0x17
/* 8008BFF4 00088BD4  41 82 00 44 */	beq lbl_8008C038
/* 8008BFF8 00088BD8  C0 3F 06 20 */	lfs f1, 0x620(r31)
/* 8008BFFC 00088BDC  C0 02 8A A0 */	lfs f0, lbl_804D8480(r2)
/* 8008C000 00088BE0  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8008C004 00088BE4  40 80 00 08 */	bge lbl_8008C00C
/* 8008C008 00088BE8  FC 20 08 50 */	fneg f1, f1
lbl_8008C00C:
/* 8008C00C 00088BEC  80 8D AE B4 */	lwz r4, p_ftCommonData(r13)
/* 8008C010 00088BF0  C0 04 00 3C */	lfs f0, 0x3c(r4)
/* 8008C014 00088BF4  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8008C018 00088BF8  4C 41 13 82 */	cror 2, 1, 2
/* 8008C01C 00088BFC  40 82 00 1C */	bne lbl_8008C038
/* 8008C020 00088C00  88 7F 06 70 */	lbz r3, 0x670(r31)
/* 8008C024 00088C04  80 04 00 40 */	lwz r0, 0x40(r4)
/* 8008C028 00088C08  7C 03 00 00 */	cmpw r3, r0
/* 8008C02C 00088C0C  40 80 00 0C */	bge lbl_8008C038
/* 8008C030 00088C10  38 00 00 01 */	li r0, 1
/* 8008C034 00088C14  48 00 00 08 */	b lbl_8008C03C
lbl_8008C038:
/* 8008C038 00088C18  38 00 00 00 */	li r0, 0
lbl_8008C03C:
/* 8008C03C 00088C1C  2C 00 00 00 */	cmpwi r0, 0
/* 8008C040 00088C20  41 82 00 38 */	beq lbl_8008C078
/* 8008C044 00088C24  C0 3F 06 20 */	lfs f1, 0x620(r31)
/* 8008C048 00088C28  C0 02 8A A0 */	lfs f0, lbl_804D8480(r2)
/* 8008C04C 00088C2C  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8008C050 00088C30  4C 41 13 82 */	cror 2, 1, 2
/* 8008C054 00088C34  40 82 00 0C */	bne lbl_8008C060
/* 8008C058 00088C38  C0 02 8A A4 */	lfs f0, lbl_804D8484(r2)
/* 8008C05C 00088C3C  48 00 00 08 */	b lbl_8008C064
lbl_8008C060:
/* 8008C060 00088C40  C0 02 8A A8 */	lfs f0, lbl_804D8488(r2)
lbl_8008C064:
/* 8008C064 00088C44  FF E0 00 90 */	fmr f31, f0
/* 8008C068 00088C48  7F E3 FB 78 */	mr r3, r31
/* 8008C06C 00088C4C  4B FF 18 F9 */	bl func_8007D964
/* 8008C070 00088C50  FF C0 08 90 */	fmr f30, f1
/* 8008C074 00088C54  48 00 00 50 */	b lbl_8008C0C4
lbl_8008C078:
/* 8008C078 00088C58  7F E3 FB 78 */	mr r3, r31
/* 8008C07C 00088C5C  48 05 31 4D */	bl func_800DF1C8
/* 8008C080 00088C60  2C 03 00 00 */	cmpwi r3, 0
/* 8008C084 00088C64  41 82 00 38 */	beq lbl_8008C0BC
/* 8008C088 00088C68  C0 3F 06 38 */	lfs f1, 0x638(r31)
/* 8008C08C 00088C6C  C0 02 8A A0 */	lfs f0, lbl_804D8480(r2)
/* 8008C090 00088C70  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8008C094 00088C74  4C 41 13 82 */	cror 2, 1, 2
/* 8008C098 00088C78  40 82 00 0C */	bne lbl_8008C0A4
/* 8008C09C 00088C7C  C0 02 8A A4 */	lfs f0, lbl_804D8484(r2)
/* 8008C0A0 00088C80  48 00 00 08 */	b lbl_8008C0A8
lbl_8008C0A4:
/* 8008C0A4 00088C84  C0 02 8A A8 */	lfs f0, lbl_804D8488(r2)
lbl_8008C0A8:
/* 8008C0A8 00088C88  FF E0 00 90 */	fmr f31, f0
/* 8008C0AC 00088C8C  7F E3 FB 78 */	mr r3, r31
/* 8008C0B0 00088C90  4B FF 18 ED */	bl func_8007D99C
/* 8008C0B4 00088C94  FF C0 08 90 */	fmr f30, f1
/* 8008C0B8 00088C98  48 00 00 0C */	b lbl_8008C0C4
lbl_8008C0BC:
/* 8008C0BC 00088C9C  38 60 00 00 */	li r3, 0
/* 8008C0C0 00088CA0  48 00 00 34 */	b lbl_8008C0F4
lbl_8008C0C4:
/* 8008C0C4 00088CA4  7F C3 F3 78 */	mr r3, r30
/* 8008C0C8 00088CA8  FC 20 F8 90 */	fmr f1, f31
/* 8008C0CC 00088CAC  48 00 01 61 */	bl func_8008C22C
/* 8008C0D0 00088CB0  2C 03 00 00 */	cmpwi r3, 0
/* 8008C0D4 00088CB4  41 82 00 0C */	beq lbl_8008C0E0
/* 8008C0D8 00088CB8  38 60 00 01 */	li r3, 1
/* 8008C0DC 00088CBC  48 00 00 18 */	b lbl_8008C0F4
lbl_8008C0E0:
/* 8008C0E0 00088CC0  FC 20 F8 90 */	fmr f1, f31
/* 8008C0E4 00088CC4  7F C3 F3 78 */	mr r3, r30
/* 8008C0E8 00088CC8  FC 40 F0 90 */	fmr f2, f30
/* 8008C0EC 00088CCC  48 00 02 5D */	bl func_8008C348
/* 8008C0F0 00088CD0  38 60 00 01 */	li r3, 1
lbl_8008C0F4:
/* 8008C0F4 00088CD4  80 01 00 2C */	lwz r0, 0x2c(r1)
/* 8008C0F8 00088CD8  CB E1 00 20 */	lfd f31, 0x20(r1)
/* 8008C0FC 00088CDC  CB C1 00 18 */	lfd f30, 0x18(r1)
/* 8008C100 00088CE0  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 8008C104 00088CE4  83 C1 00 10 */	lwz r30, 0x10(r1)
/* 8008C108 00088CE8  38 21 00 28 */	addi r1, r1, 0x28
/* 8008C10C 00088CEC  7C 08 03 A6 */	mtlr r0
/* 8008C110 00088CF0  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

#pragma push
asm unk_t func_8008C114()
{ // clang-format off
    nofralloc
/* 8008C114 00088CF4  7C 08 02 A6 */	mflr r0
/* 8008C118 00088CF8  90 01 00 04 */	stw r0, 4(r1)
/* 8008C11C 00088CFC  94 21 FF D8 */	stwu r1, -0x28(r1)
/* 8008C120 00088D00  DB E1 00 20 */	stfd f31, 0x20(r1)
/* 8008C124 00088D04  DB C1 00 18 */	stfd f30, 0x18(r1)
/* 8008C128 00088D08  93 E1 00 14 */	stw r31, 0x14(r1)
/* 8008C12C 00088D0C  93 C1 00 10 */	stw r30, 0x10(r1)
/* 8008C130 00088D10  7C 7E 1B 78 */	mr r30, r3
/* 8008C134 00088D14  80 63 00 2C */	lwz r3, 0x2c(r3)
/* 8008C138 00088D18  80 03 06 68 */	lwz r0, 0x668(r3)
/* 8008C13C 00088D1C  3B E3 00 00 */	addi r31, r3, 0
/* 8008C140 00088D20  54 00 05 EF */	rlwinm. r0, r0, 0, 0x17, 0x17
/* 8008C144 00088D24  41 82 00 2C */	beq lbl_8008C170
/* 8008C148 00088D28  C0 3F 06 20 */	lfs f1, 0x620(r31)
/* 8008C14C 00088D2C  C0 1F 00 2C */	lfs f0, 0x2c(r31)
/* 8008C150 00088D30  80 6D AE B4 */	lwz r3, p_ftCommonData(r13)
/* 8008C154 00088D34  EC 21 00 32 */	fmuls f1, f1, f0
/* 8008C158 00088D38  C0 03 00 3C */	lfs f0, 0x3c(r3)
/* 8008C15C 00088D3C  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8008C160 00088D40  4C 41 13 82 */	cror 2, 1, 2
/* 8008C164 00088D44  40 82 00 0C */	bne lbl_8008C170
/* 8008C168 00088D48  38 00 00 01 */	li r0, 1
/* 8008C16C 00088D4C  48 00 00 08 */	b lbl_8008C174
lbl_8008C170:
/* 8008C170 00088D50  38 00 00 00 */	li r0, 0
lbl_8008C174:
/* 8008C174 00088D54  2C 00 00 00 */	cmpwi r0, 0
/* 8008C178 00088D58  41 82 00 18 */	beq lbl_8008C190
/* 8008C17C 00088D5C  C3 FF 00 2C */	lfs f31, 0x2c(r31)
/* 8008C180 00088D60  7F E3 FB 78 */	mr r3, r31
/* 8008C184 00088D64  4B FF 17 E1 */	bl func_8007D964
/* 8008C188 00088D68  FF C0 08 90 */	fmr f30, f1
/* 8008C18C 00088D6C  48 00 00 50 */	b lbl_8008C1DC
lbl_8008C190:
/* 8008C190 00088D70  7F E3 FB 78 */	mr r3, r31
/* 8008C194 00088D74  48 05 30 35 */	bl func_800DF1C8
/* 8008C198 00088D78  2C 03 00 00 */	cmpwi r3, 0
/* 8008C19C 00088D7C  41 82 00 38 */	beq lbl_8008C1D4
/* 8008C1A0 00088D80  C0 3F 06 38 */	lfs f1, 0x638(r31)
/* 8008C1A4 00088D84  C0 02 8A A0 */	lfs f0, lbl_804D8480(r2)
/* 8008C1A8 00088D88  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8008C1AC 00088D8C  4C 41 13 82 */	cror 2, 1, 2
/* 8008C1B0 00088D90  40 82 00 0C */	bne lbl_8008C1BC
/* 8008C1B4 00088D94  C0 02 8A A4 */	lfs f0, lbl_804D8484(r2)
/* 8008C1B8 00088D98  48 00 00 08 */	b lbl_8008C1C0
lbl_8008C1BC:
/* 8008C1BC 00088D9C  C0 02 8A A8 */	lfs f0, lbl_804D8488(r2)
lbl_8008C1C0:
/* 8008C1C0 00088DA0  FF E0 00 90 */	fmr f31, f0
/* 8008C1C4 00088DA4  7F E3 FB 78 */	mr r3, r31
/* 8008C1C8 00088DA8  4B FF 17 D5 */	bl func_8007D99C
/* 8008C1CC 00088DAC  FF C0 08 90 */	fmr f30, f1
/* 8008C1D0 00088DB0  48 00 00 0C */	b lbl_8008C1DC
lbl_8008C1D4:
/* 8008C1D4 00088DB4  38 60 00 00 */	li r3, 0
/* 8008C1D8 00088DB8  48 00 00 34 */	b lbl_8008C20C
lbl_8008C1DC:
/* 8008C1DC 00088DBC  7F C3 F3 78 */	mr r3, r30
/* 8008C1E0 00088DC0  FC 20 F8 90 */	fmr f1, f31
/* 8008C1E4 00088DC4  48 00 00 49 */	bl func_8008C22C
/* 8008C1E8 00088DC8  2C 03 00 00 */	cmpwi r3, 0
/* 8008C1EC 00088DCC  41 82 00 0C */	beq lbl_8008C1F8
/* 8008C1F0 00088DD0  38 60 00 01 */	li r3, 1
/* 8008C1F4 00088DD4  48 00 00 18 */	b lbl_8008C20C
lbl_8008C1F8:
/* 8008C1F8 00088DD8  FC 20 F8 90 */	fmr f1, f31
/* 8008C1FC 00088DDC  7F C3 F3 78 */	mr r3, r30
/* 8008C200 00088DE0  FC 40 F0 90 */	fmr f2, f30
/* 8008C204 00088DE4  48 00 01 45 */	bl func_8008C348
/* 8008C208 00088DE8  38 60 00 01 */	li r3, 1
lbl_8008C20C:
/* 8008C20C 00088DEC  80 01 00 2C */	lwz r0, 0x2c(r1)
/* 8008C210 00088DF0  CB E1 00 20 */	lfd f31, 0x20(r1)
/* 8008C214 00088DF4  CB C1 00 18 */	lfd f30, 0x18(r1)
/* 8008C218 00088DF8  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 8008C21C 00088DFC  83 C1 00 10 */	lwz r30, 0x10(r1)
/* 8008C220 00088E00  38 21 00 28 */	addi r1, r1, 0x28
/* 8008C224 00088E04  7C 08 03 A6 */	mtlr r0
/* 8008C228 00088E08  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

extern unk_t func_800DF21C();

#pragma push
asm unk_t func_8008C22C()
{ // clang-format off
    nofralloc
/* 8008C22C 00088E0C  7C 08 02 A6 */	mflr r0
/* 8008C230 00088E10  90 01 00 04 */	stw r0, 4(r1)
/* 8008C234 00088E14  94 21 FF D8 */	stwu r1, -0x28(r1)
/* 8008C238 00088E18  DB E1 00 20 */	stfd f31, 0x20(r1)
/* 8008C23C 00088E1C  FF E0 08 90 */	fmr f31, f1
/* 8008C240 00088E20  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 8008C244 00088E24  93 C1 00 18 */	stw r30, 0x18(r1)
/* 8008C248 00088E28  7C 7E 1B 78 */	mr r30, r3
/* 8008C24C 00088E2C  80 83 00 2C */	lwz r4, 0x2c(r3)
/* 8008C250 00088E30  80 64 19 74 */	lwz r3, 0x1974(r4)
/* 8008C254 00088E34  3B E4 00 00 */	addi r31, r4, 0
/* 8008C258 00088E38  28 03 00 00 */	cmplwi r3, 0
/* 8008C25C 00088E3C  41 82 00 CC */	beq lbl_8008C328
/* 8008C260 00088E40  80 1F 06 5C */	lwz r0, 0x65c(r31)
/* 8008C264 00088E44  54 00 00 01 */	rlwinm. r0, r0, 0, 0, 0
/* 8008C268 00088E48  40 82 00 40 */	bne lbl_8008C2A8
/* 8008C26C 00088E4C  48 1D F0 A1 */	bl func_8026B30C
/* 8008C270 00088E50  2C 03 00 00 */	cmpwi r3, 0
/* 8008C274 00088E54  41 82 00 34 */	beq lbl_8008C2A8
/* 8008C278 00088E58  80 7F 19 74 */	lwz r3, 0x1974(r31)
/* 8008C27C 00088E5C  48 1D F0 91 */	bl func_8026B30C
/* 8008C280 00088E60  2C 03 00 03 */	cmpwi r3, 3
/* 8008C284 00088E64  40 82 00 14 */	bne lbl_8008C298
/* 8008C288 00088E68  80 7F 19 74 */	lwz r3, 0x1974(r31)
/* 8008C28C 00088E6C  48 1D F3 09 */	bl func_8026B594
/* 8008C290 00088E70  2C 03 00 00 */	cmpwi r3, 0
/* 8008C294 00088E74  40 82 00 14 */	bne lbl_8008C2A8
lbl_8008C298:
/* 8008C298 00088E78  7F E3 FB 78 */	mr r3, r31
/* 8008C29C 00088E7C  48 05 2F 81 */	bl func_800DF21C
/* 8008C2A0 00088E80  2C 03 00 00 */	cmpwi r3, 0
/* 8008C2A4 00088E84  41 82 00 38 */	beq lbl_8008C2DC
lbl_8008C2A8:
/* 8008C2A8 00088E88  C0 3F 00 2C */	lfs f1, 0x2c(r31)
/* 8008C2AC 00088E8C  C0 02 8A A0 */	lfs f0, lbl_804D8480(r2)
/* 8008C2B0 00088E90  EC 3F 00 72 */	fmuls f1, f31, f1
/* 8008C2B4 00088E94  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8008C2B8 00088E98  4C 41 13 82 */	cror 2, 1, 2
/* 8008C2BC 00088E9C  40 82 00 0C */	bne lbl_8008C2C8
/* 8008C2C0 00088EA0  38 80 00 6C */	li r4, 0x6c
/* 8008C2C4 00088EA4  48 00 00 08 */	b lbl_8008C2CC
lbl_8008C2C8:
/* 8008C2C8 00088EA8  38 80 00 6D */	li r4, 0x6d
lbl_8008C2CC:
/* 8008C2CC 00088EAC  7F C3 F3 78 */	mr r3, r30
/* 8008C2D0 00088EB0  48 00 95 25 */	bl func_800957F4
/* 8008C2D4 00088EB4  38 60 00 01 */	li r3, 1
/* 8008C2D8 00088EB8  48 00 00 54 */	b lbl_8008C32C
lbl_8008C2DC:
/* 8008C2DC 00088EBC  80 7F 19 74 */	lwz r3, 0x1974(r31)
/* 8008C2E0 00088EC0  48 1D F0 2D */	bl func_8026B30C
/* 8008C2E4 00088EC4  2C 03 00 03 */	cmpwi r3, 3
/* 8008C2E8 00088EC8  41 82 00 2C */	beq lbl_8008C314
/* 8008C2EC 00088ECC  40 80 00 3C */	bge lbl_8008C328
/* 8008C2F0 00088ED0  2C 03 00 02 */	cmpwi r3, 2
/* 8008C2F4 00088ED4  40 80 00 08 */	bge lbl_8008C2FC
/* 8008C2F8 00088ED8  48 00 00 30 */	b lbl_8008C328
lbl_8008C2FC:
/* 8008C2FC 00088EDC  D3 FF 00 2C */	stfs f31, 0x2c(r31)
/* 8008C300 00088EE0  38 7E 00 00 */	addi r3, r30, 0
/* 8008C304 00088EE4  38 80 00 02 */	li r4, 2
/* 8008C308 00088EE8  48 04 0C 51 */	bl func_800CCF58
/* 8008C30C 00088EEC  38 60 00 01 */	li r3, 1
/* 8008C310 00088EF0  48 00 00 1C */	b lbl_8008C32C
lbl_8008C314:
/* 8008C314 00088EF4  D3 FF 00 2C */	stfs f31, 0x2c(r31)
/* 8008C318 00088EF8  7F C3 F3 78 */	mr r3, r30
/* 8008C31C 00088EFC  48 04 19 F9 */	bl func_800CDD14
/* 8008C320 00088F00  38 60 00 01 */	li r3, 1
/* 8008C324 00088F04  48 00 00 08 */	b lbl_8008C32C
lbl_8008C328:
/* 8008C328 00088F08  38 60 00 00 */	li r3, 0
lbl_8008C32C:
/* 8008C32C 00088F0C  80 01 00 2C */	lwz r0, 0x2c(r1)
/* 8008C330 00088F10  CB E1 00 20 */	lfd f31, 0x20(r1)
/* 8008C334 00088F14  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 8008C338 00088F18  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 8008C33C 00088F1C  38 21 00 28 */	addi r1, r1, 0x28
/* 8008C340 00088F20  7C 08 03 A6 */	mtlr r0
/* 8008C344 00088F24  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

extern jtbl_t jtbl_803C54D8;
extern unk_t func_8008C3E0();
extern unk_t ftPeach_8011C1C0();
void lbl_8008C388(void);
void lbl_8008C390(void);
void lbl_8008C398(void);
void lbl_8008C3A0(void);
void lbl_8008C3C4(void);

#pragma push
asm unk_t func_8008C348()
{ // clang-format off
    nofralloc
/* 8008C348 00088F28  7C 08 02 A6 */	mflr r0
/* 8008C34C 00088F2C  90 01 00 04 */	stw r0, 4(r1)
/* 8008C350 00088F30  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 8008C354 00088F34  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 8008C358 00088F38  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 8008C35C 00088F3C  D0 3F 00 2C */	stfs f1, 0x2c(r31)
/* 8008C360 00088F40  80 9F 00 04 */	lwz r4, 4(r31)
/* 8008C364 00088F44  38 04 FF F8 */	addi r0, r4, -8
/* 8008C368 00088F48  28 00 00 10 */	cmplwi r0, 0x10
/* 8008C36C 00088F4C  41 81 00 58 */	bgt lbl_8008C3C4
/* 8008C370 00088F50  3C 80 80 3C */	lis r4, jtbl_803C54D8@ha
/* 8008C374 00088F54  38 84 54 D8 */	addi r4, r4, jtbl_803C54D8@l
/* 8008C378 00088F58  54 00 10 3A */	slwi r0, r0, 2
/* 8008C37C 00088F5C  7C 04 00 2E */	lwzx r0, r4, r0
/* 8008C380 00088F60  7C 09 03 A6 */	mtctr r0
/* 8008C384 00088F64  4E 80 04 20 */	bctr 
entry lbl_8008C388
/* 8008C388 00088F68  48 08 88 9D */	bl ftNess_AttackS4_Action
/* 8008C38C 00088F6C  48 00 00 40 */	b lbl_8008C3CC
entry lbl_8008C390
/* 8008C390 00088F70  48 08 FE 31 */	bl ftPeach_8011C1C0
/* 8008C394 00088F74  48 00 00 38 */	b lbl_8008C3CC
entry lbl_8008C398
/* 8008C398 00088F78  48 0B E6 79 */	bl ftGameWatch_AttackS4_Action
/* 8008C39C 00088F7C  48 00 00 30 */	b lbl_8008C3CC
entry lbl_8008C3A0
/* 8008C3A0 00088F80  FC 20 10 90 */	fmr f1, f2
/* 8008C3A4 00088F84  48 00 00 3D */	bl func_8008C3E0
/* 8008C3A8 00088F88  3C 60 80 06 */	lis r3, efLib_PauseAll@ha
/* 8008C3AC 00088F8C  38 03 BA 40 */	addi r0, r3, efLib_PauseAll@l
/* 8008C3B0 00088F90  3C 60 80 06 */	lis r3, efLib_ResumeAll@ha
/* 8008C3B4 00088F94  90 1F 21 D4 */	stw r0, 0x21d4(r31)
/* 8008C3B8 00088F98  38 03 BA C4 */	addi r0, r3, efLib_ResumeAll@l
/* 8008C3BC 00088F9C  90 1F 21 D8 */	stw r0, 0x21d8(r31)
/* 8008C3C0 00088FA0  48 00 00 0C */	b lbl_8008C3CC
entry lbl_8008C3C4
/* 8008C3C4 00088FA4  FC 20 10 90 */	fmr f1, f2
/* 8008C3C8 00088FA8  48 00 00 19 */	bl func_8008C3E0
lbl_8008C3CC:
/* 8008C3CC 00088FAC  80 01 00 24 */	lwz r0, 0x24(r1)
/* 8008C3D0 00088FB0  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 8008C3D4 00088FB4  38 21 00 20 */	addi r1, r1, 0x20
/* 8008C3D8 00088FB8  7C 08 03 A6 */	mtlr r0
/* 8008C3DC 00088FBC  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

#pragma push
asm unk_t func_8008C3E0()
{ // clang-format off
    nofralloc
/* 8008C3E0 00088FC0  7C 08 02 A6 */	mflr r0
/* 8008C3E4 00088FC4  90 01 00 04 */	stw r0, 4(r1)
/* 8008C3E8 00088FC8  94 21 FF D8 */	stwu r1, -0x28(r1)
/* 8008C3EC 00088FCC  DB E1 00 20 */	stfd f31, 0x20(r1)
/* 8008C3F0 00088FD0  FF E0 08 90 */	fmr f31, f1
/* 8008C3F4 00088FD4  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 8008C3F8 00088FD8  93 C1 00 18 */	stw r30, 0x18(r1)
/* 8008C3FC 00088FDC  7C 7E 1B 78 */	mr r30, r3
/* 8008C400 00088FE0  80 8D AE B4 */	lwz r4, p_ftCommonData(r13)
/* 8008C404 00088FE4  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 8008C408 00088FE8  C0 04 00 B8 */	lfs f0, 0xb8(r4)
/* 8008C40C 00088FEC  FC 1F 00 40 */	fcmpo cr0, f31, f0
/* 8008C410 00088FF0  40 81 00 24 */	ble lbl_8008C434
/* 8008C414 00088FF4  38 7F 00 00 */	addi r3, r31, 0
/* 8008C418 00088FF8  38 80 00 3C */	li r4, 0x3c
/* 8008C41C 00088FFC  4B FF 9B B9 */	bl func_80085FD4
/* 8008C420 00089000  80 03 00 08 */	lwz r0, 8(r3)
/* 8008C424 00089004  28 00 00 00 */	cmplwi r0, 0
/* 8008C428 00089008  41 82 00 0C */	beq lbl_8008C434
/* 8008C42C 0008900C  38 80 00 3A */	li r4, 0x3a
/* 8008C430 00089010  48 00 00 98 */	b lbl_8008C4C8
lbl_8008C434:
/* 8008C434 00089014  80 6D AE B4 */	lwz r3, p_ftCommonData(r13)
/* 8008C438 00089018  C0 03 00 BC */	lfs f0, 0xbc(r3)
/* 8008C43C 0008901C  FC 1F 00 40 */	fcmpo cr0, f31, f0
/* 8008C440 00089020  40 81 00 24 */	ble lbl_8008C464
/* 8008C444 00089024  38 7F 00 00 */	addi r3, r31, 0
/* 8008C448 00089028  38 80 00 3D */	li r4, 0x3d
/* 8008C44C 0008902C  4B FF 9B 89 */	bl func_80085FD4
/* 8008C450 00089030  80 03 00 08 */	lwz r0, 8(r3)
/* 8008C454 00089034  28 00 00 00 */	cmplwi r0, 0
/* 8008C458 00089038  41 82 00 0C */	beq lbl_8008C464
/* 8008C45C 0008903C  38 80 00 3B */	li r4, 0x3b
/* 8008C460 00089040  48 00 00 68 */	b lbl_8008C4C8
lbl_8008C464:
/* 8008C464 00089044  80 6D AE B4 */	lwz r3, p_ftCommonData(r13)
/* 8008C468 00089048  C0 03 00 C4 */	lfs f0, 0xc4(r3)
/* 8008C46C 0008904C  FC 1F 00 40 */	fcmpo cr0, f31, f0
/* 8008C470 00089050  40 80 00 24 */	bge lbl_8008C494
/* 8008C474 00089054  38 7F 00 00 */	addi r3, r31, 0
/* 8008C478 00089058  38 80 00 40 */	li r4, 0x40
/* 8008C47C 0008905C  4B FF 9B 59 */	bl func_80085FD4
/* 8008C480 00089060  80 03 00 08 */	lwz r0, 8(r3)
/* 8008C484 00089064  28 00 00 00 */	cmplwi r0, 0
/* 8008C488 00089068  41 82 00 0C */	beq lbl_8008C494
/* 8008C48C 0008906C  38 80 00 3E */	li r4, 0x3e
/* 8008C490 00089070  48 00 00 38 */	b lbl_8008C4C8
lbl_8008C494:
/* 8008C494 00089074  80 6D AE B4 */	lwz r3, p_ftCommonData(r13)
/* 8008C498 00089078  C0 03 00 C0 */	lfs f0, 0xc0(r3)
/* 8008C49C 0008907C  FC 1F 00 40 */	fcmpo cr0, f31, f0
/* 8008C4A0 00089080  40 80 00 24 */	bge lbl_8008C4C4
/* 8008C4A4 00089084  38 7F 00 00 */	addi r3, r31, 0
/* 8008C4A8 00089088  38 80 00 3F */	li r4, 0x3f
/* 8008C4AC 0008908C  4B FF 9B 29 */	bl func_80085FD4
/* 8008C4B0 00089090  80 03 00 08 */	lwz r0, 8(r3)
/* 8008C4B4 00089094  28 00 00 00 */	cmplwi r0, 0
/* 8008C4B8 00089098  41 82 00 0C */	beq lbl_8008C4C4
/* 8008C4BC 0008909C  38 80 00 3D */	li r4, 0x3d
/* 8008C4C0 000890A0  48 00 00 08 */	b lbl_8008C4C8
lbl_8008C4C4:
/* 8008C4C4 000890A4  38 80 00 3C */	li r4, 0x3c
lbl_8008C4C8:
/* 8008C4C8 000890A8  88 1F 22 18 */	lbz r0, 0x2218(r31)
/* 8008C4CC 000890AC  38 E0 00 00 */	li r7, 0
/* 8008C4D0 000890B0  50 E0 3E 30 */	rlwimi r0, r7, 7, 0x18, 0x18
/* 8008C4D4 000890B4  98 1F 22 18 */	stb r0, 0x2218(r31)
/* 8008C4D8 000890B8  7F C3 F3 78 */	mr r3, r30
/* 8008C4DC 000890BC  38 A0 00 00 */	li r5, 0
/* 8008C4E0 000890C0  90 FF 22 00 */	stw r7, 0x2200(r31)
/* 8008C4E4 000890C4  38 C0 00 00 */	li r6, 0
/* 8008C4E8 000890C8  90 FF 22 10 */	stw r7, 0x2210(r31)
/* 8008C4EC 000890CC  C0 22 8A A0 */	lfs f1, lbl_804D8480(r2)
/* 8008C4F0 000890D0  C0 42 8A A4 */	lfs f2, lbl_804D8484(r2)
/* 8008C4F4 000890D4  FC 60 08 90 */	fmr f3, f1
/* 8008C4F8 000890D8  4B FD CE B5 */	bl Fighter_ActionStateChange_800693AC
/* 8008C4FC 000890DC  7F C3 F3 78 */	mr r3, r30
/* 8008C500 000890E0  4B FE 26 A5 */	bl func_8006EBA4
/* 8008C504 000890E4  80 01 00 2C */	lwz r0, 0x2c(r1)
/* 8008C508 000890E8  CB E1 00 20 */	lfd f31, 0x20(r1)
/* 8008C50C 000890EC  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 8008C510 000890F0  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 8008C514 000890F4  38 21 00 28 */	addi r1, r1, 0x28
/* 8008C518 000890F8  7C 08 03 A6 */	mtlr r0
/* 8008C51C 000890FC  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

#pragma push
asm unk_t func_8008C520()
{ // clang-format off
    nofralloc
/* 8008C520 00089100  7C 08 02 A6 */	mflr r0
/* 8008C524 00089104  90 01 00 04 */	stw r0, 4(r1)
/* 8008C528 00089108  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 8008C52C 0008910C  93 E1 00 14 */	stw r31, 0x14(r1)
/* 8008C530 00089110  7C 7F 1B 78 */	mr r31, r3
/* 8008C534 00089114  4B FE 2D 05 */	bl ftAnim_IsFramesRemaining
/* 8008C538 00089118  2C 03 00 00 */	cmpwi r3, 0
/* 8008C53C 0008911C  40 82 00 0C */	bne lbl_8008C548
/* 8008C540 00089120  7F E3 FB 78 */	mr r3, r31
/* 8008C544 00089124  4B FF DD 79 */	bl func_8008A2BC
lbl_8008C548:
/* 8008C548 00089128  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 8008C54C 0008912C  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 8008C550 00089130  38 21 00 18 */	addi r1, r1, 0x18
/* 8008C554 00089134  7C 08 03 A6 */	mtlr r0
/* 8008C558 00089138  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

extern unk_t func_800CECE8();

#pragma push
asm unk_t func_8008C55C()
{ // clang-format off
    nofralloc
/* 8008C55C 0008913C  7C 08 02 A6 */	mflr r0
/* 8008C560 00089140  90 01 00 04 */	stw r0, 4(r1)
/* 8008C564 00089144  94 21 FF D0 */	stwu r1, -0x30(r1)
/* 8008C568 00089148  DB E1 00 28 */	stfd f31, 0x28(r1)
/* 8008C56C 0008914C  DB C1 00 20 */	stfd f30, 0x20(r1)
/* 8008C570 00089150  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 8008C574 00089154  93 C1 00 18 */	stw r30, 0x18(r1)
/* 8008C578 00089158  7C 7E 1B 78 */	mr r30, r3
/* 8008C57C 0008915C  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 8008C580 00089160  88 1F 22 18 */	lbz r0, 0x2218(r31)
/* 8008C584 00089164  54 00 CF FF */	rlwinm. r0, r0, 0x19, 0x1f, 0x1f
/* 8008C588 00089168  41 82 00 54 */	beq lbl_8008C5DC
/* 8008C58C 0008916C  7F C3 F3 78 */	mr r3, r30
/* 8008C590 00089170  48 00 9F B1 */	bl func_80096540
/* 8008C594 00089174  2C 03 00 00 */	cmpwi r3, 0
/* 8008C598 00089178  40 82 02 38 */	bne lbl_8008C7D0
/* 8008C59C 0008917C  7F C3 F3 78 */	mr r3, r30
/* 8008C5A0 00089180  48 04 A3 BD */	bl func_800D695C
/* 8008C5A4 00089184  2C 03 00 00 */	cmpwi r3, 0
/* 8008C5A8 00089188  40 82 02 28 */	bne lbl_8008C7D0
/* 8008C5AC 0008918C  7F C3 F3 78 */	mr r3, r30
/* 8008C5B0 00089190  48 04 A2 75 */	bl func_800D6824
/* 8008C5B4 00089194  2C 03 00 00 */	cmpwi r3, 0
/* 8008C5B8 00089198  40 82 02 18 */	bne lbl_8008C7D0
/* 8008C5BC 0008919C  7F C3 F3 78 */	mr r3, r30
/* 8008C5C0 000891A0  48 04 A3 01 */	bl func_800D68C0
/* 8008C5C4 000891A4  2C 03 00 00 */	cmpwi r3, 0
/* 8008C5C8 000891A8  40 82 02 08 */	bne lbl_8008C7D0
/* 8008C5CC 000891AC  7F C3 F3 78 */	mr r3, r30
/* 8008C5D0 000891B0  48 04 C3 C1 */	bl func_800D8990
/* 8008C5D4 000891B4  2C 03 00 00 */	cmpwi r3, 0
/* 8008C5D8 000891B8  40 82 01 F8 */	bne lbl_8008C7D0
lbl_8008C5DC:
/* 8008C5DC 000891BC  7F C3 F3 78 */	mr r3, r30
/* 8008C5E0 000891C0  48 04 27 09 */	bl func_800CECE8
/* 8008C5E4 000891C4  2C 03 00 00 */	cmpwi r3, 0
/* 8008C5E8 000891C8  40 82 01 E8 */	bne lbl_8008C7D0
/* 8008C5EC 000891CC  88 1F 22 18 */	lbz r0, 0x2218(r31)
/* 8008C5F0 000891D0  54 00 CF FF */	rlwinm. r0, r0, 0x19, 0x1f, 0x1f
/* 8008C5F4 000891D4  41 82 01 DC */	beq lbl_8008C7D0
/* 8008C5F8 000891D8  83 FE 00 2C */	lwz r31, 0x2c(r30)
/* 8008C5FC 000891DC  80 1F 06 68 */	lwz r0, 0x668(r31)
/* 8008C600 000891E0  54 00 05 EF */	rlwinm. r0, r0, 0, 0x17, 0x17
/* 8008C604 000891E4  41 82 00 44 */	beq lbl_8008C648
/* 8008C608 000891E8  C0 3F 06 20 */	lfs f1, 0x620(r31)
/* 8008C60C 000891EC  C0 02 8A A0 */	lfs f0, lbl_804D8480(r2)
/* 8008C610 000891F0  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8008C614 000891F4  40 80 00 08 */	bge lbl_8008C61C
/* 8008C618 000891F8  FC 20 08 50 */	fneg f1, f1
lbl_8008C61C:
/* 8008C61C 000891FC  80 8D AE B4 */	lwz r4, p_ftCommonData(r13)
/* 8008C620 00089200  C0 04 00 3C */	lfs f0, 0x3c(r4)
/* 8008C624 00089204  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8008C628 00089208  4C 41 13 82 */	cror 2, 1, 2
/* 8008C62C 0008920C  40 82 00 1C */	bne lbl_8008C648
/* 8008C630 00089210  88 7F 06 70 */	lbz r3, 0x670(r31)
/* 8008C634 00089214  80 04 00 40 */	lwz r0, 0x40(r4)
/* 8008C638 00089218  7C 03 00 00 */	cmpw r3, r0
/* 8008C63C 0008921C  40 80 00 0C */	bge lbl_8008C648
/* 8008C640 00089220  38 00 00 01 */	li r0, 1
/* 8008C644 00089224  48 00 00 08 */	b lbl_8008C64C
lbl_8008C648:
/* 8008C648 00089228  38 00 00 00 */	li r0, 0
lbl_8008C64C:
/* 8008C64C 0008922C  2C 00 00 00 */	cmpwi r0, 0
/* 8008C650 00089230  41 82 00 34 */	beq lbl_8008C684
/* 8008C654 00089234  C0 3F 06 20 */	lfs f1, 0x620(r31)
/* 8008C658 00089238  C0 02 8A A0 */	lfs f0, lbl_804D8480(r2)
/* 8008C65C 0008923C  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8008C660 00089240  4C 41 13 82 */	cror 2, 1, 2
/* 8008C664 00089244  40 82 00 0C */	bne lbl_8008C670
/* 8008C668 00089248  C3 C2 8A A4 */	lfs f30, lbl_804D8484(r2)
/* 8008C66C 0008924C  48 00 00 08 */	b lbl_8008C674
lbl_8008C670:
/* 8008C670 00089250  C3 C2 8A A8 */	lfs f30, lbl_804D8488(r2)
lbl_8008C674:
/* 8008C674 00089254  7F E3 FB 78 */	mr r3, r31
/* 8008C678 00089258  4B FF 12 ED */	bl func_8007D964
/* 8008C67C 0008925C  FF E0 08 90 */	fmr f31, f1
/* 8008C680 00089260  48 00 00 4C */	b lbl_8008C6CC
lbl_8008C684:
/* 8008C684 00089264  7F E3 FB 78 */	mr r3, r31
/* 8008C688 00089268  48 05 2B 41 */	bl func_800DF1C8
/* 8008C68C 0008926C  2C 03 00 00 */	cmpwi r3, 0
/* 8008C690 00089270  41 82 00 34 */	beq lbl_8008C6C4
/* 8008C694 00089274  C0 3F 06 38 */	lfs f1, 0x638(r31)
/* 8008C698 00089278  C0 02 8A A0 */	lfs f0, lbl_804D8480(r2)
/* 8008C69C 0008927C  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8008C6A0 00089280  4C 41 13 82 */	cror 2, 1, 2
/* 8008C6A4 00089284  40 82 00 0C */	bne lbl_8008C6B0
/* 8008C6A8 00089288  C3 C2 8A A4 */	lfs f30, lbl_804D8484(r2)
/* 8008C6AC 0008928C  48 00 00 08 */	b lbl_8008C6B4
lbl_8008C6B0:
/* 8008C6B0 00089290  C3 C2 8A A8 */	lfs f30, lbl_804D8488(r2)
lbl_8008C6B4:
/* 8008C6B4 00089294  7F E3 FB 78 */	mr r3, r31
/* 8008C6B8 00089298  4B FF 12 E5 */	bl func_8007D99C
/* 8008C6BC 0008929C  FF E0 08 90 */	fmr f31, f1
/* 8008C6C0 000892A0  48 00 00 0C */	b lbl_8008C6CC
lbl_8008C6C4:
/* 8008C6C4 000892A4  38 00 00 00 */	li r0, 0
/* 8008C6C8 000892A8  48 00 00 34 */	b lbl_8008C6FC
lbl_8008C6CC:
/* 8008C6CC 000892AC  7F C3 F3 78 */	mr r3, r30
/* 8008C6D0 000892B0  FC 20 F0 90 */	fmr f1, f30
/* 8008C6D4 000892B4  4B FF FB 59 */	bl func_8008C22C
/* 8008C6D8 000892B8  2C 03 00 00 */	cmpwi r3, 0
/* 8008C6DC 000892BC  41 82 00 0C */	beq lbl_8008C6E8
/* 8008C6E0 000892C0  38 00 00 01 */	li r0, 1
/* 8008C6E4 000892C4  48 00 00 18 */	b lbl_8008C6FC
lbl_8008C6E8:
/* 8008C6E8 000892C8  FC 20 F0 90 */	fmr f1, f30
/* 8008C6EC 000892CC  7F C3 F3 78 */	mr r3, r30
/* 8008C6F0 000892D0  FC 40 F8 90 */	fmr f2, f31
/* 8008C6F4 000892D4  4B FF FC 55 */	bl func_8008C348
/* 8008C6F8 000892D8  38 00 00 01 */	li r0, 1
lbl_8008C6FC:
/* 8008C6FC 000892DC  2C 00 00 00 */	cmpwi r0, 0
/* 8008C700 000892E0  40 82 00 D0 */	bne lbl_8008C7D0
/* 8008C704 000892E4  7F C3 F3 78 */	mr r3, r30
/* 8008C708 000892E8  48 00 01 29 */	bl func_8008C830
/* 8008C70C 000892EC  2C 03 00 00 */	cmpwi r3, 0
/* 8008C710 000892F0  40 82 00 C0 */	bne lbl_8008C7D0
/* 8008C714 000892F4  7F C3 F3 78 */	mr r3, r30
/* 8008C718 000892F8  48 00 04 2D */	bl func_8008CB44
/* 8008C71C 000892FC  2C 03 00 00 */	cmpwi r3, 0
/* 8008C720 00089300  40 82 00 B0 */	bne lbl_8008C7D0
/* 8008C724 00089304  7F C3 F3 78 */	mr r3, r30
/* 8008C728 00089308  4B FF EF 31 */	bl func_8008B658
/* 8008C72C 0008930C  2C 03 00 00 */	cmpwi r3, 0
/* 8008C730 00089310  40 82 00 A0 */	bne lbl_8008C7D0
/* 8008C734 00089314  7F C3 F3 78 */	mr r3, r30
/* 8008C738 00089318  4B FF F2 49 */	bl func_8008B980
/* 8008C73C 0008931C  2C 03 00 00 */	cmpwi r3, 0
/* 8008C740 00089320  40 82 00 90 */	bne lbl_8008C7D0
/* 8008C744 00089324  7F C3 F3 78 */	mr r3, r30
/* 8008C748 00089328  4B FF F3 FD */	bl func_8008BB44
/* 8008C74C 0008932C  2C 03 00 00 */	cmpwi r3, 0
/* 8008C750 00089330  40 82 00 80 */	bne lbl_8008C7D0
/* 8008C754 00089334  7F C3 F3 78 */	mr r3, r30
/* 8008C758 00089338  4B FF E2 A1 */	bl func_8008A9F8
/* 8008C75C 0008933C  2C 03 00 00 */	cmpwi r3, 0
/* 8008C760 00089340  40 82 00 70 */	bne lbl_8008C7D0
/* 8008C764 00089344  7F C3 F3 78 */	mr r3, r30
/* 8008C768 00089348  48 00 52 E5 */	bl func_80091A4C
/* 8008C76C 0008934C  2C 03 00 00 */	cmpwi r3, 0
/* 8008C770 00089350  40 82 00 60 */	bne lbl_8008C7D0
/* 8008C774 00089354  7F C3 F3 78 */	mr r3, r30
/* 8008C778 00089358  48 05 22 61 */	bl func_800DE9D8
/* 8008C77C 0008935C  2C 03 00 00 */	cmpwi r3, 0
/* 8008C780 00089360  40 82 00 50 */	bne lbl_8008C7D0
/* 8008C784 00089364  7F C3 F3 78 */	mr r3, r30
/* 8008C788 00089368  48 03 E7 49 */	bl func_800CAED0
/* 8008C78C 0008936C  2C 03 00 00 */	cmpwi r3, 0
/* 8008C790 00089370  40 82 00 40 */	bne lbl_8008C7D0
/* 8008C794 00089374  7F C3 F3 78 */	mr r3, r30
/* 8008C798 00089378  48 03 D8 FD */	bl func_800CA094
/* 8008C79C 0008937C  2C 03 00 00 */	cmpwi r3, 0
/* 8008C7A0 00089380  40 82 00 30 */	bne lbl_8008C7D0
/* 8008C7A4 00089384  7F C3 F3 78 */	mr r3, r30
/* 8008C7A8 00089388  48 04 98 09 */	bl func_800D5FB0
/* 8008C7AC 0008938C  2C 03 00 00 */	cmpwi r3, 0
/* 8008C7B0 00089390  40 82 00 20 */	bne lbl_8008C7D0
/* 8008C7B4 00089394  7F C3 F3 78 */	mr r3, r30
/* 8008C7B8 00089398  48 03 D0 25 */	bl func_800C97DC
/* 8008C7BC 0008939C  2C 03 00 00 */	cmpwi r3, 0
/* 8008C7C0 000893A0  40 82 00 10 */	bne lbl_8008C7D0
/* 8008C7C4 000893A4  7F C3 F3 78 */	mr r3, r30
/* 8008C7C8 000893A8  48 03 CC A1 */	bl func_800C9468
/* 8008C7CC 000893AC  2C 03 00 00 */	cmpwi r3, 0
lbl_8008C7D0:
/* 8008C7D0 000893B0  80 01 00 34 */	lwz r0, 0x34(r1)
/* 8008C7D4 000893B4  CB E1 00 28 */	lfd f31, 0x28(r1)
/* 8008C7D8 000893B8  CB C1 00 20 */	lfd f30, 0x20(r1)
/* 8008C7DC 000893BC  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 8008C7E0 000893C0  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 8008C7E4 000893C4  38 21 00 30 */	addi r1, r1, 0x30
/* 8008C7E8 000893C8  7C 08 03 A6 */	mtlr r0
/* 8008C7EC 000893CC  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

#pragma push
asm unk_t func_8008C7F0()
{ // clang-format off
    nofralloc
/* 8008C7F0 000893D0  7C 08 02 A6 */	mflr r0
/* 8008C7F4 000893D4  90 01 00 04 */	stw r0, 4(r1)
/* 8008C7F8 000893D8  94 21 FF F8 */	stwu r1, -8(r1)
/* 8008C7FC 000893DC  4B FF 87 AD */	bl func_80084FA8
/* 8008C800 000893E0  80 01 00 0C */	lwz r0, 0xc(r1)
/* 8008C804 000893E4  38 21 00 08 */	addi r1, r1, 8
/* 8008C808 000893E8  7C 08 03 A6 */	mtlr r0
/* 8008C80C 000893EC  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

#pragma push
asm unk_t func_8008C810()
{ // clang-format off
    nofralloc
/* 8008C810 000893F0  7C 08 02 A6 */	mflr r0
/* 8008C814 000893F4  90 01 00 04 */	stw r0, 4(r1)
/* 8008C818 000893F8  94 21 FF F8 */	stwu r1, -8(r1)
/* 8008C81C 000893FC  4B FF 78 E9 */	bl func_80084104
/* 8008C820 00089400  80 01 00 0C */	lwz r0, 0xc(r1)
/* 8008C824 00089404  38 21 00 08 */	addi r1, r1, 8
/* 8008C828 00089408  7C 08 03 A6 */	mtlr r0
/* 8008C82C 0008940C  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

extern f64 const lbl_804D8490;
extern unk_t func_8008CA38();
extern unk_t func_800DF30C();
extern unk_t func_800DF2D8();

#pragma push
asm BOOL func_8008C830(HSD_GObj* fighter_gobj)
{ // clang-format off
    nofralloc
/* 8008C830 00089410  7C 08 02 A6 */	mflr r0
/* 8008C834 00089414  90 01 00 04 */	stw r0, 4(r1)
/* 8008C838 00089418  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 8008C83C 0008941C  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 8008C840 00089420  93 C1 00 18 */	stw r30, 0x18(r1)
/* 8008C844 00089424  7C 7E 1B 78 */	mr r30, r3
/* 8008C848 00089428  80 63 00 2C */	lwz r3, 0x2c(r3)
/* 8008C84C 0008942C  80 03 06 68 */	lwz r0, 0x668(r3)
/* 8008C850 00089430  3B E3 00 00 */	addi r31, r3, 0
/* 8008C854 00089434  54 00 05 EF */	rlwinm. r0, r0, 0, 0x17, 0x17
/* 8008C858 00089438  41 82 00 4C */	beq lbl_8008C8A4
/* 8008C85C 0008943C  80 8D AE B4 */	lwz r4, p_ftCommonData(r13)
/* 8008C860 00089440  C0 3F 06 24 */	lfs f1, 0x624(r31)
/* 8008C864 00089444  C0 04 00 CC */	lfs f0, 0xcc(r4)
/* 8008C868 00089448  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8008C86C 0008944C  4C 41 13 82 */	cror 2, 1, 2
/* 8008C870 00089450  40 82 00 34 */	bne lbl_8008C8A4
/* 8008C874 00089454  88 7F 06 71 */	lbz r3, 0x671(r31)
/* 8008C878 00089458  3C 00 43 30 */	lis r0, 0x4330
/* 8008C87C 0008945C  C8 42 8A B0 */	lfd f2, lbl_804D8490(r2)
/* 8008C880 00089460  90 61 00 14 */	stw r3, 0x14(r1)
/* 8008C884 00089464  C0 04 00 D0 */	lfs f0, 0xd0(r4)
/* 8008C888 00089468  90 01 00 10 */	stw r0, 0x10(r1)
/* 8008C88C 0008946C  C8 21 00 10 */	lfd f1, 0x10(r1)
/* 8008C890 00089470  EC 21 10 28 */	fsubs f1, f1, f2
/* 8008C894 00089474  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8008C898 00089478  40 80 00 0C */	bge lbl_8008C8A4
/* 8008C89C 0008947C  38 00 00 01 */	li r0, 1
/* 8008C8A0 00089480  48 00 00 08 */	b lbl_8008C8A8
lbl_8008C8A4:
/* 8008C8A4 00089484  38 00 00 00 */	li r0, 0
lbl_8008C8A8:
/* 8008C8A8 00089488  2C 00 00 00 */	cmpwi r0, 0
/* 8008C8AC 0008948C  40 82 00 14 */	bne lbl_8008C8C0
/* 8008C8B0 00089490  7F E3 FB 78 */	mr r3, r31
/* 8008C8B4 00089494  48 05 2A 25 */	bl func_800DF2D8
/* 8008C8B8 00089498  2C 03 00 00 */	cmpwi r3, 0
/* 8008C8BC 0008949C  41 82 00 70 */	beq lbl_8008C92C
lbl_8008C8C0:
/* 8008C8C0 000894A0  80 1F 19 74 */	lwz r0, 0x1974(r31)
/* 8008C8C4 000894A4  28 00 00 00 */	cmplwi r0, 0
/* 8008C8C8 000894A8  41 82 00 38 */	beq lbl_8008C900
/* 8008C8CC 000894AC  7F E3 FB 78 */	mr r3, r31
/* 8008C8D0 000894B0  48 00 85 85 */	bl func_80094E54
/* 8008C8D4 000894B4  2C 03 00 00 */	cmpwi r3, 0
/* 8008C8D8 000894B8  40 82 00 14 */	bne lbl_8008C8EC
/* 8008C8DC 000894BC  7F E3 FB 78 */	mr r3, r31
/* 8008C8E0 000894C0  48 05 2A 2D */	bl func_800DF30C
/* 8008C8E4 000894C4  2C 03 00 00 */	cmpwi r3, 0
/* 8008C8E8 000894C8  41 82 00 18 */	beq lbl_8008C900
lbl_8008C8EC:
/* 8008C8EC 000894CC  38 7E 00 00 */	addi r3, r30, 0
/* 8008C8F0 000894D0  38 80 00 6E */	li r4, 0x6e
/* 8008C8F4 000894D4  48 00 8F 01 */	bl func_800957F4
/* 8008C8F8 000894D8  38 60 00 01 */	li r3, 1
/* 8008C8FC 000894DC  48 00 00 34 */	b lbl_8008C930
lbl_8008C900:
/* 8008C900 000894E0  80 1F 00 04 */	lwz r0, 4(r31)
/* 8008C904 000894E4  2C 00 00 08 */	cmpwi r0, 8
/* 8008C908 000894E8  41 82 00 08 */	beq lbl_8008C910
/* 8008C90C 000894EC  48 00 00 10 */	b lbl_8008C91C
lbl_8008C910:
/* 8008C910 000894F0  7F C3 F3 78 */	mr r3, r30
/* 8008C914 000894F4  48 08 92 9D */	bl ftNess_AttackHi4_Action
/* 8008C918 000894F8  48 00 00 0C */	b lbl_8008C924
lbl_8008C91C:
/* 8008C91C 000894FC  7F C3 F3 78 */	mr r3, r30
/* 8008C920 00089500  48 00 01 19 */	bl func_8008CA38
lbl_8008C924:
/* 8008C924 00089504  38 60 00 01 */	li r3, 1
/* 8008C928 00089508  48 00 00 08 */	b lbl_8008C930
lbl_8008C92C:
/* 8008C92C 0008950C  38 60 00 00 */	li r3, 0
lbl_8008C930:
/* 8008C930 00089510  80 01 00 24 */	lwz r0, 0x24(r1)
/* 8008C934 00089514  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 8008C938 00089518  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 8008C93C 0008951C  38 21 00 20 */	addi r1, r1, 0x20
/* 8008C940 00089520  7C 08 03 A6 */	mtlr r0
/* 8008C944 00089524  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

#pragma push
asm unk_t func_8008C948()
{ // clang-format off
    nofralloc
/* 8008C948 00089528  7C 08 02 A6 */	mflr r0
/* 8008C94C 0008952C  90 01 00 04 */	stw r0, 4(r1)
/* 8008C950 00089530  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 8008C954 00089534  93 E1 00 14 */	stw r31, 0x14(r1)
/* 8008C958 00089538  93 C1 00 10 */	stw r30, 0x10(r1)
/* 8008C95C 0008953C  7C 7E 1B 78 */	mr r30, r3
/* 8008C960 00089540  80 63 00 2C */	lwz r3, 0x2c(r3)
/* 8008C964 00089544  80 03 06 68 */	lwz r0, 0x668(r3)
/* 8008C968 00089548  3B E3 00 00 */	addi r31, r3, 0
/* 8008C96C 0008954C  54 00 05 EF */	rlwinm. r0, r0, 0, 0x17, 0x17
/* 8008C970 00089550  41 82 00 24 */	beq lbl_8008C994
/* 8008C974 00089554  80 6D AE B4 */	lwz r3, p_ftCommonData(r13)
/* 8008C978 00089558  C0 3F 06 24 */	lfs f1, 0x624(r31)
/* 8008C97C 0008955C  C0 03 00 CC */	lfs f0, 0xcc(r3)
/* 8008C980 00089560  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8008C984 00089564  4C 41 13 82 */	cror 2, 1, 2
/* 8008C988 00089568  40 82 00 0C */	bne lbl_8008C994
/* 8008C98C 0008956C  38 00 00 01 */	li r0, 1
/* 8008C990 00089570  48 00 00 08 */	b lbl_8008C998
lbl_8008C994:
/* 8008C994 00089574  38 00 00 00 */	li r0, 0
lbl_8008C998:
/* 8008C998 00089578  2C 00 00 00 */	cmpwi r0, 0
/* 8008C99C 0008957C  40 82 00 14 */	bne lbl_8008C9B0
/* 8008C9A0 00089580  7F E3 FB 78 */	mr r3, r31
/* 8008C9A4 00089584  48 05 29 35 */	bl func_800DF2D8
/* 8008C9A8 00089588  2C 03 00 00 */	cmpwi r3, 0
/* 8008C9AC 0008958C  41 82 00 70 */	beq lbl_8008CA1C
lbl_8008C9B0:
/* 8008C9B0 00089590  80 1F 19 74 */	lwz r0, 0x1974(r31)
/* 8008C9B4 00089594  28 00 00 00 */	cmplwi r0, 0
/* 8008C9B8 00089598  41 82 00 38 */	beq lbl_8008C9F0
/* 8008C9BC 0008959C  7F E3 FB 78 */	mr r3, r31
/* 8008C9C0 000895A0  48 00 84 95 */	bl func_80094E54
/* 8008C9C4 000895A4  2C 03 00 00 */	cmpwi r3, 0
/* 8008C9C8 000895A8  40 82 00 14 */	bne lbl_8008C9DC
/* 8008C9CC 000895AC  7F E3 FB 78 */	mr r3, r31
/* 8008C9D0 000895B0  48 05 29 3D */	bl func_800DF30C
/* 8008C9D4 000895B4  2C 03 00 00 */	cmpwi r3, 0
/* 8008C9D8 000895B8  41 82 00 18 */	beq lbl_8008C9F0
lbl_8008C9DC:
/* 8008C9DC 000895BC  38 7E 00 00 */	addi r3, r30, 0
/* 8008C9E0 000895C0  38 80 00 6E */	li r4, 0x6e
/* 8008C9E4 000895C4  48 00 8E 11 */	bl func_800957F4
/* 8008C9E8 000895C8  38 60 00 01 */	li r3, 1
/* 8008C9EC 000895CC  48 00 00 34 */	b lbl_8008CA20
lbl_8008C9F0:
/* 8008C9F0 000895D0  80 1F 00 04 */	lwz r0, 4(r31)
/* 8008C9F4 000895D4  2C 00 00 08 */	cmpwi r0, 8
/* 8008C9F8 000895D8  41 82 00 08 */	beq lbl_8008CA00
/* 8008C9FC 000895DC  48 00 00 10 */	b lbl_8008CA0C
lbl_8008CA00:
/* 8008CA00 000895E0  7F C3 F3 78 */	mr r3, r30
/* 8008CA04 000895E4  48 08 91 AD */	bl ftNess_AttackHi4_Action
/* 8008CA08 000895E8  48 00 00 0C */	b lbl_8008CA14
lbl_8008CA0C:
/* 8008CA0C 000895EC  7F C3 F3 78 */	mr r3, r30
/* 8008CA10 000895F0  48 00 00 29 */	bl func_8008CA38
lbl_8008CA14:
/* 8008CA14 000895F4  38 60 00 01 */	li r3, 1
/* 8008CA18 000895F8  48 00 00 08 */	b lbl_8008CA20
lbl_8008CA1C:
/* 8008CA1C 000895FC  38 60 00 00 */	li r3, 0
lbl_8008CA20:
/* 8008CA20 00089600  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 8008CA24 00089604  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 8008CA28 00089608  83 C1 00 10 */	lwz r30, 0x10(r1)
/* 8008CA2C 0008960C  38 21 00 18 */	addi r1, r1, 0x18
/* 8008CA30 00089610  7C 08 03 A6 */	mtlr r0
/* 8008CA34 00089614  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

extern f32 const lbl_804D8498;
extern f32 const lbl_804D849C;

#pragma push
asm unk_t func_8008CA38()
{ // clang-format off
    nofralloc
/* 8008CA38 00089618  7C 08 02 A6 */	mflr r0
/* 8008CA3C 0008961C  38 80 00 00 */	li r4, 0
/* 8008CA40 00089620  90 01 00 04 */	stw r0, 4(r1)
/* 8008CA44 00089624  38 C0 00 00 */	li r6, 0
/* 8008CA48 00089628  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 8008CA4C 0008962C  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 8008CA50 00089630  7C 7F 1B 78 */	mr r31, r3
/* 8008CA54 00089634  80 A3 00 2C */	lwz r5, 0x2c(r3)
/* 8008CA58 00089638  88 05 22 18 */	lbz r0, 0x2218(r5)
/* 8008CA5C 0008963C  50 80 3E 30 */	rlwimi r0, r4, 7, 0x18, 0x18
/* 8008CA60 00089640  38 80 00 3F */	li r4, 0x3f
/* 8008CA64 00089644  98 05 22 18 */	stb r0, 0x2218(r5)
/* 8008CA68 00089648  38 A0 00 00 */	li r5, 0
/* 8008CA6C 0008964C  C0 22 8A B8 */	lfs f1, lbl_804D8498(r2)
/* 8008CA70 00089650  C0 42 8A BC */	lfs f2, lbl_804D849C(r2)
/* 8008CA74 00089654  FC 60 08 90 */	fmr f3, f1
/* 8008CA78 00089658  4B FD C9 35 */	bl Fighter_ActionStateChange_800693AC
/* 8008CA7C 0008965C  7F E3 FB 78 */	mr r3, r31
/* 8008CA80 00089660  4B FE 21 25 */	bl func_8006EBA4
/* 8008CA84 00089664  80 01 00 24 */	lwz r0, 0x24(r1)
/* 8008CA88 00089668  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 8008CA8C 0008966C  38 21 00 20 */	addi r1, r1, 0x20
/* 8008CA90 00089670  7C 08 03 A6 */	mtlr r0
/* 8008CA94 00089674  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

#pragma push
asm unk_t func_8008CA98()
{ // clang-format off
    nofralloc
/* 8008CA98 00089678  7C 08 02 A6 */	mflr r0
/* 8008CA9C 0008967C  90 01 00 04 */	stw r0, 4(r1)
/* 8008CAA0 00089680  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 8008CAA4 00089684  93 E1 00 14 */	stw r31, 0x14(r1)
/* 8008CAA8 00089688  7C 7F 1B 78 */	mr r31, r3
/* 8008CAAC 0008968C  4B FE 27 8D */	bl ftAnim_IsFramesRemaining
/* 8008CAB0 00089690  2C 03 00 00 */	cmpwi r3, 0
/* 8008CAB4 00089694  40 82 00 0C */	bne lbl_8008CAC0
/* 8008CAB8 00089698  7F E3 FB 78 */	mr r3, r31
/* 8008CABC 0008969C  4B FF D8 01 */	bl func_8008A2BC
lbl_8008CAC0:
/* 8008CAC0 000896A0  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 8008CAC4 000896A4  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 8008CAC8 000896A8  38 21 00 18 */	addi r1, r1, 0x18
/* 8008CACC 000896AC  7C 08 03 A6 */	mtlr r0
/* 8008CAD0 000896B0  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

#pragma push
asm unk_t func_8008CAD4()
{ // clang-format off
    nofralloc
/* 8008CAD4 000896B4  7C 08 02 A6 */	mflr r0
/* 8008CAD8 000896B8  90 01 00 04 */	stw r0, 4(r1)
/* 8008CADC 000896BC  94 21 FF F8 */	stwu r1, -8(r1)
/* 8008CAE0 000896C0  80 83 00 2C */	lwz r4, 0x2c(r3)
/* 8008CAE4 000896C4  88 04 22 18 */	lbz r0, 0x2218(r4)
/* 8008CAE8 000896C8  54 00 CF FF */	rlwinm. r0, r0, 0x19, 0x1f, 0x1f
/* 8008CAEC 000896CC  41 82 00 08 */	beq lbl_8008CAF4
/* 8008CAF0 000896D0  4B FF D9 E5 */	bl func_8008A4D4
lbl_8008CAF4:
/* 8008CAF4 000896D4  80 01 00 0C */	lwz r0, 0xc(r1)
/* 8008CAF8 000896D8  38 21 00 08 */	addi r1, r1, 8
/* 8008CAFC 000896DC  7C 08 03 A6 */	mtlr r0
/* 8008CB00 000896E0  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

#pragma push
asm unk_t func_8008CB04()
{ // clang-format off
    nofralloc
/* 8008CB04 000896E4  7C 08 02 A6 */	mflr r0
/* 8008CB08 000896E8  90 01 00 04 */	stw r0, 4(r1)
/* 8008CB0C 000896EC  94 21 FF F8 */	stwu r1, -8(r1)
/* 8008CB10 000896F0  4B FF 84 2D */	bl func_80084F3C
/* 8008CB14 000896F4  80 01 00 0C */	lwz r0, 0xc(r1)
/* 8008CB18 000896F8  38 21 00 08 */	addi r1, r1, 8
/* 8008CB1C 000896FC  7C 08 03 A6 */	mtlr r0
/* 8008CB20 00089700  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

#pragma push
asm unk_t func_8008CB24()
{ // clang-format off
    nofralloc
/* 8008CB24 00089704  7C 08 02 A6 */	mflr r0
/* 8008CB28 00089708  90 01 00 04 */	stw r0, 4(r1)
/* 8008CB2C 0008970C  94 21 FF F8 */	stwu r1, -8(r1)
/* 8008CB30 00089710  4B FF 75 D5 */	bl func_80084104
/* 8008CB34 00089714  80 01 00 0C */	lwz r0, 0xc(r1)
/* 8008CB38 00089718  38 21 00 08 */	addi r1, r1, 8
/* 8008CB3C 0008971C  7C 08 03 A6 */	mtlr r0
/* 8008CB40 00089720  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

extern f64 const lbl_804D84A0;
extern unk_t func_8008CC5C();
extern unk_t func_800DF3DC();
extern unk_t func_800DF3A8();
extern unk_t func_8008CC5C();

#pragma push
asm BOOL func_8008CB44(HSD_GObj* fighter_gobj)
{ // clang-format off
    nofralloc
/* 8008CB44 00089724  7C 08 02 A6 */	mflr r0
/* 8008CB48 00089728  90 01 00 04 */	stw r0, 4(r1)
/* 8008CB4C 0008972C  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 8008CB50 00089730  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 8008CB54 00089734  93 C1 00 18 */	stw r30, 0x18(r1)
/* 8008CB58 00089738  7C 7E 1B 78 */	mr r30, r3
/* 8008CB5C 0008973C  80 63 00 2C */	lwz r3, 0x2c(r3)
/* 8008CB60 00089740  80 03 06 68 */	lwz r0, 0x668(r3)
/* 8008CB64 00089744  3B E3 00 00 */	addi r31, r3, 0
/* 8008CB68 00089748  54 00 05 EF */	rlwinm. r0, r0, 0, 0x17, 0x17
/* 8008CB6C 0008974C  41 82 00 4C */	beq lbl_8008CBB8
/* 8008CB70 00089750  80 8D AE B4 */	lwz r4, p_ftCommonData(r13)
/* 8008CB74 00089754  C0 3F 06 24 */	lfs f1, 0x624(r31)
/* 8008CB78 00089758  C0 04 00 D4 */	lfs f0, 0xd4(r4)
/* 8008CB7C 0008975C  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8008CB80 00089760  4C 40 13 82 */	cror 2, 0, 2
/* 8008CB84 00089764  40 82 00 34 */	bne lbl_8008CBB8
/* 8008CB88 00089768  88 7F 06 71 */	lbz r3, 0x671(r31)
/* 8008CB8C 0008976C  3C 00 43 30 */	lis r0, 0x4330
/* 8008CB90 00089770  C8 42 8A C0 */	lfd f2, lbl_804D84A0(r2)
/* 8008CB94 00089774  90 61 00 14 */	stw r3, 0x14(r1)
/* 8008CB98 00089778  C0 04 00 D8 */	lfs f0, 0xd8(r4)
/* 8008CB9C 0008977C  90 01 00 10 */	stw r0, 0x10(r1)
/* 8008CBA0 00089780  C8 21 00 10 */	lfd f1, 0x10(r1)
/* 8008CBA4 00089784  EC 21 10 28 */	fsubs f1, f1, f2
/* 8008CBA8 00089788  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8008CBAC 0008978C  40 80 00 0C */	bge lbl_8008CBB8
/* 8008CBB0 00089790  38 00 00 01 */	li r0, 1
/* 8008CBB4 00089794  48 00 00 08 */	b lbl_8008CBBC
lbl_8008CBB8:
/* 8008CBB8 00089798  38 00 00 00 */	li r0, 0
lbl_8008CBBC:
/* 8008CBBC 0008979C  2C 00 00 00 */	cmpwi r0, 0
/* 8008CBC0 000897A0  40 82 00 14 */	bne lbl_8008CBD4
/* 8008CBC4 000897A4  7F E3 FB 78 */	mr r3, r31
/* 8008CBC8 000897A8  48 05 27 E1 */	bl func_800DF3A8
/* 8008CBCC 000897AC  2C 03 00 00 */	cmpwi r3, 0
/* 8008CBD0 000897B0  41 82 00 70 */	beq lbl_8008CC40
lbl_8008CBD4:
/* 8008CBD4 000897B4  80 1F 19 74 */	lwz r0, 0x1974(r31)
/* 8008CBD8 000897B8  28 00 00 00 */	cmplwi r0, 0
/* 8008CBDC 000897BC  41 82 00 38 */	beq lbl_8008CC14
/* 8008CBE0 000897C0  7F E3 FB 78 */	mr r3, r31
/* 8008CBE4 000897C4  48 00 82 71 */	bl func_80094E54
/* 8008CBE8 000897C8  2C 03 00 00 */	cmpwi r3, 0
/* 8008CBEC 000897CC  40 82 00 14 */	bne lbl_8008CC00
/* 8008CBF0 000897D0  7F E3 FB 78 */	mr r3, r31
/* 8008CBF4 000897D4  48 05 27 E9 */	bl func_800DF3DC
/* 8008CBF8 000897D8  2C 03 00 00 */	cmpwi r3, 0
/* 8008CBFC 000897DC  41 82 00 18 */	beq lbl_8008CC14
lbl_8008CC00:
/* 8008CC00 000897E0  38 7E 00 00 */	addi r3, r30, 0
/* 8008CC04 000897E4  38 80 00 6F */	li r4, 0x6f
/* 8008CC08 000897E8  48 00 8B ED */	bl func_800957F4
/* 8008CC0C 000897EC  38 60 00 01 */	li r3, 1
/* 8008CC10 000897F0  48 00 00 34 */	b lbl_8008CC44
lbl_8008CC14:
/* 8008CC14 000897F4  80 1F 00 04 */	lwz r0, 4(r31)
/* 8008CC18 000897F8  2C 00 00 08 */	cmpwi r0, 8
/* 8008CC1C 000897FC  41 82 00 08 */	beq lbl_8008CC24
/* 8008CC20 00089800  48 00 00 10 */	b lbl_8008CC30
lbl_8008CC24:
/* 8008CC24 00089804  7F C3 F3 78 */	mr r3, r30
/* 8008CC28 00089808  48 08 99 75 */	bl ftNess_AttackLw4_Action
/* 8008CC2C 0008980C  48 00 00 0C */	b lbl_8008CC38
lbl_8008CC30:
/* 8008CC30 00089810  7F C3 F3 78 */	mr r3, r30
/* 8008CC34 00089814  48 00 00 29 */	bl func_8008CC5C
lbl_8008CC38:
/* 8008CC38 00089818  38 60 00 01 */	li r3, 1
/* 8008CC3C 0008981C  48 00 00 08 */	b lbl_8008CC44
lbl_8008CC40:
/* 8008CC40 00089820  38 60 00 00 */	li r3, 0
lbl_8008CC44:
/* 8008CC44 00089824  80 01 00 24 */	lwz r0, 0x24(r1)
/* 8008CC48 00089828  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 8008CC4C 0008982C  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 8008CC50 00089830  38 21 00 20 */	addi r1, r1, 0x20
/* 8008CC54 00089834  7C 08 03 A6 */	mtlr r0
/* 8008CC58 00089838  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

extern f32 const lbl_804D84A8;
extern f32 const lbl_804D84AC;

#pragma push
asm unk_t func_8008CC5C()
{ // clang-format off
    nofralloc
/* 8008CC5C 0008983C  7C 08 02 A6 */	mflr r0
/* 8008CC60 00089840  38 80 00 00 */	li r4, 0
/* 8008CC64 00089844  90 01 00 04 */	stw r0, 4(r1)
/* 8008CC68 00089848  38 C0 00 00 */	li r6, 0
/* 8008CC6C 0008984C  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 8008CC70 00089850  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 8008CC74 00089854  7C 7F 1B 78 */	mr r31, r3
/* 8008CC78 00089858  80 A3 00 2C */	lwz r5, 0x2c(r3)
/* 8008CC7C 0008985C  88 05 22 18 */	lbz r0, 0x2218(r5)
/* 8008CC80 00089860  50 80 3E 30 */	rlwimi r0, r4, 7, 0x18, 0x18
/* 8008CC84 00089864  38 80 00 40 */	li r4, 0x40
/* 8008CC88 00089868  98 05 22 18 */	stb r0, 0x2218(r5)
/* 8008CC8C 0008986C  38 A0 00 00 */	li r5, 0
/* 8008CC90 00089870  C0 22 8A C8 */	lfs f1, lbl_804D84A8(r2)
/* 8008CC94 00089874  C0 42 8A CC */	lfs f2, lbl_804D84AC(r2)
/* 8008CC98 00089878  FC 60 08 90 */	fmr f3, f1
/* 8008CC9C 0008987C  4B FD C7 11 */	bl Fighter_ActionStateChange_800693AC
/* 8008CCA0 00089880  7F E3 FB 78 */	mr r3, r31
/* 8008CCA4 00089884  4B FE 1F 01 */	bl func_8006EBA4
/* 8008CCA8 00089888  80 01 00 24 */	lwz r0, 0x24(r1)
/* 8008CCAC 0008988C  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 8008CCB0 00089890  38 21 00 20 */	addi r1, r1, 0x20
/* 8008CCB4 00089894  7C 08 03 A6 */	mtlr r0
/* 8008CCB8 00089898  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

#pragma push
asm unk_t func_8008CCBC()
{ // clang-format off
    nofralloc
/* 8008CCBC 0008989C  7C 08 02 A6 */	mflr r0
/* 8008CCC0 000898A0  90 01 00 04 */	stw r0, 4(r1)
/* 8008CCC4 000898A4  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 8008CCC8 000898A8  93 E1 00 14 */	stw r31, 0x14(r1)
/* 8008CCCC 000898AC  7C 7F 1B 78 */	mr r31, r3
/* 8008CCD0 000898B0  4B FE 25 69 */	bl ftAnim_IsFramesRemaining
/* 8008CCD4 000898B4  2C 03 00 00 */	cmpwi r3, 0
/* 8008CCD8 000898B8  40 82 00 0C */	bne lbl_8008CCE4
/* 8008CCDC 000898BC  7F E3 FB 78 */	mr r3, r31
/* 8008CCE0 000898C0  4B FF D5 DD */	bl func_8008A2BC
lbl_8008CCE4:
/* 8008CCE4 000898C4  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 8008CCE8 000898C8  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 8008CCEC 000898CC  38 21 00 18 */	addi r1, r1, 0x18
/* 8008CCF0 000898D0  7C 08 03 A6 */	mtlr r0
/* 8008CCF4 000898D4  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

#pragma push
asm unk_t func_8008CCF8()
{ // clang-format off
    nofralloc
/* 8008CCF8 000898D8  7C 08 02 A6 */	mflr r0
/* 8008CCFC 000898DC  90 01 00 04 */	stw r0, 4(r1)
/* 8008CD00 000898E0  94 21 FF F8 */	stwu r1, -8(r1)
/* 8008CD04 000898E4  80 83 00 2C */	lwz r4, 0x2c(r3)
/* 8008CD08 000898E8  88 04 22 18 */	lbz r0, 0x2218(r4)
/* 8008CD0C 000898EC  54 00 CF FF */	rlwinm. r0, r0, 0x19, 0x1f, 0x1f
/* 8008CD10 000898F0  41 82 00 08 */	beq lbl_8008CD18
/* 8008CD14 000898F4  4B FF D7 C1 */	bl func_8008A4D4
lbl_8008CD18:
/* 8008CD18 000898F8  80 01 00 0C */	lwz r0, 0xc(r1)
/* 8008CD1C 000898FC  38 21 00 08 */	addi r1, r1, 8
/* 8008CD20 00089900  7C 08 03 A6 */	mtlr r0
/* 8008CD24 00089904  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

#pragma push
asm unk_t func_8008CD28()
{ // clang-format off
    nofralloc
/* 8008CD28 00089908  7C 08 02 A6 */	mflr r0
/* 8008CD2C 0008990C  90 01 00 04 */	stw r0, 4(r1)
/* 8008CD30 00089910  94 21 FF F8 */	stwu r1, -8(r1)
/* 8008CD34 00089914  4B FF 82 09 */	bl func_80084F3C
/* 8008CD38 00089918  80 01 00 0C */	lwz r0, 0xc(r1)
/* 8008CD3C 0008991C  38 21 00 08 */	addi r1, r1, 8
/* 8008CD40 00089920  7C 08 03 A6 */	mtlr r0
/* 8008CD44 00089924  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

#pragma push
asm unk_t func_8008CD48()
{ // clang-format off
    nofralloc
/* 8008CD48 00089928  7C 08 02 A6 */	mflr r0
/* 8008CD4C 0008992C  90 01 00 04 */	stw r0, 4(r1)
/* 8008CD50 00089930  94 21 FF F8 */	stwu r1, -8(r1)
/* 8008CD54 00089934  4B FF 73 B1 */	bl func_80084104
/* 8008CD58 00089938  80 01 00 0C */	lwz r0, 0xc(r1)
/* 8008CD5C 0008993C  38 21 00 08 */	addi r1, r1, 8
/* 8008CD60 00089940  7C 08 03 A6 */	mtlr r0
/* 8008CD64 00089944  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

extern unk_t func_8008CE0C();
extern unk_t func_800CDDA0();
extern unk_t func_800DF478();

#pragma push
asm unk_t func_8008CD68()
{ // clang-format off
    nofralloc
/* 8008CD68 00089948  7C 08 02 A6 */	mflr r0
/* 8008CD6C 0008994C  90 01 00 04 */	stw r0, 4(r1)
/* 8008CD70 00089950  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 8008CD74 00089954  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 8008CD78 00089958  93 C1 00 18 */	stw r30, 0x18(r1)
/* 8008CD7C 0008995C  7C 7E 1B 78 */	mr r30, r3
/* 8008CD80 00089960  80 63 00 2C */	lwz r3, 0x2c(r3)
/* 8008CD84 00089964  80 03 06 68 */	lwz r0, 0x668(r3)
/* 8008CD88 00089968  3B E3 00 00 */	addi r31, r3, 0
/* 8008CD8C 0008996C  54 00 05 EF */	rlwinm. r0, r0, 0, 0x17, 0x17
/* 8008CD90 00089970  40 82 00 14 */	bne lbl_8008CDA4
/* 8008CD94 00089974  7F E3 FB 78 */	mr r3, r31
/* 8008CD98 00089978  48 05 26 E1 */	bl func_800DF478
/* 8008CD9C 0008997C  2C 03 00 00 */	cmpwi r3, 0
/* 8008CDA0 00089980  41 82 00 50 */	beq lbl_8008CDF0
lbl_8008CDA4:
/* 8008CDA4 00089984  7F E3 FB 78 */	mr r3, r31
/* 8008CDA8 00089988  48 00 00 C1 */	bl func_8008CE68
/* 8008CDAC 0008998C  38 03 FF BF */	addi r0, r3, -65
/* 8008CDB0 00089990  28 00 00 01 */	cmplwi r0, 1
/* 8008CDB4 00089994  41 81 00 2C */	bgt lbl_8008CDE0
/* 8008CDB8 00089998  80 7F 19 74 */	lwz r3, 0x1974(r31)
/* 8008CDBC 0008999C  28 03 00 00 */	cmplwi r3, 0
/* 8008CDC0 000899A0  41 82 00 20 */	beq lbl_8008CDE0
/* 8008CDC4 000899A4  48 1D E5 49 */	bl func_8026B30C
/* 8008CDC8 000899A8  2C 03 00 03 */	cmpwi r3, 3
/* 8008CDCC 000899AC  40 82 00 14 */	bne lbl_8008CDE0
/* 8008CDD0 000899B0  7F C3 F3 78 */	mr r3, r30
/* 8008CDD4 000899B4  48 04 0F CD */	bl func_800CDDA0
/* 8008CDD8 000899B8  38 60 00 01 */	li r3, 1
/* 8008CDDC 000899BC  48 00 00 18 */	b lbl_8008CDF4
lbl_8008CDE0:
/* 8008CDE0 000899C0  7F C3 F3 78 */	mr r3, r30
/* 8008CDE4 000899C4  48 00 00 29 */	bl func_8008CE0C
/* 8008CDE8 000899C8  38 60 00 01 */	li r3, 1
/* 8008CDEC 000899CC  48 00 00 08 */	b lbl_8008CDF4
lbl_8008CDF0:
/* 8008CDF0 000899D0  38 60 00 00 */	li r3, 0
lbl_8008CDF4:
/* 8008CDF4 000899D4  80 01 00 24 */	lwz r0, 0x24(r1)
/* 8008CDF8 000899D8  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 8008CDFC 000899DC  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 8008CE00 000899E0  38 21 00 20 */	addi r1, r1, 0x20
/* 8008CE04 000899E4  7C 08 03 A6 */	mtlr r0
/* 8008CE08 000899E8  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

extern unk_t func_8008CF70();
extern unk_t func_800EB42C();

#pragma push
asm unk_t func_8008CE0C()
{ // clang-format off
    nofralloc
/* 8008CE0C 000899EC  7C 08 02 A6 */	mflr r0
/* 8008CE10 000899F0  90 01 00 04 */	stw r0, 4(r1)
/* 8008CE14 000899F4  94 21 FF F8 */	stwu r1, -8(r1)
/* 8008CE18 000899F8  80 83 00 2C */	lwz r4, 0x2c(r3)
/* 8008CE1C 000899FC  80 04 00 04 */	lwz r0, 4(r4)
/* 8008CE20 00089A00  2C 00 00 14 */	cmpwi r0, 0x14
/* 8008CE24 00089A04  41 82 00 20 */	beq lbl_8008CE44
/* 8008CE28 00089A08  40 80 00 10 */	bge lbl_8008CE38
/* 8008CE2C 00089A0C  2C 00 00 06 */	cmpwi r0, 6
/* 8008CE30 00089A10  41 82 00 14 */	beq lbl_8008CE44
/* 8008CE34 00089A14  48 00 00 20 */	b lbl_8008CE54
lbl_8008CE38:
/* 8008CE38 00089A18  2C 00 00 18 */	cmpwi r0, 0x18
/* 8008CE3C 00089A1C  41 82 00 10 */	beq lbl_8008CE4C
/* 8008CE40 00089A20  48 00 00 14 */	b lbl_8008CE54
lbl_8008CE44:
/* 8008CE44 00089A24  48 05 E5 E9 */	bl func_800EB42C
/* 8008CE48 00089A28  48 00 00 10 */	b lbl_8008CE58
lbl_8008CE4C:
/* 8008CE4C 00089A2C  48 0B E8 01 */	bl ftGameWatch_AttackAir_DecideAction
/* 8008CE50 00089A30  48 00 00 08 */	b lbl_8008CE58
lbl_8008CE54:
/* 8008CE54 00089A34  48 00 01 1D */	bl func_8008CF70
lbl_8008CE58:
/* 8008CE58 00089A38  80 01 00 0C */	lwz r0, 0xc(r1)
/* 8008CE5C 00089A3C  38 21 00 08 */	addi r1, r1, 8
/* 8008CE60 00089A40  7C 08 03 A6 */	mtlr r0
/* 8008CE64 00089A44  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

extern f32 const lbl_804D84B0;

#pragma push
asm s32 func_8008CE68(Fighter* fp)
{ // clang-format off
    nofralloc
/* 8008CE68 00089A48  7C 08 02 A6 */	mflr r0
/* 8008CE6C 00089A4C  90 01 00 04 */	stw r0, 4(r1)
/* 8008CE70 00089A50  94 21 FF D8 */	stwu r1, -0x28(r1)
/* 8008CE74 00089A54  DB E1 00 20 */	stfd f31, 0x20(r1)
/* 8008CE78 00089A58  DB C1 00 18 */	stfd f30, 0x18(r1)
/* 8008CE7C 00089A5C  93 E1 00 14 */	stw r31, 0x14(r1)
/* 8008CE80 00089A60  7C 7F 1B 78 */	mr r31, r3
/* 8008CE84 00089A64  48 05 25 F5 */	bl func_800DF478
/* 8008CE88 00089A68  2C 03 00 00 */	cmpwi r3, 0
/* 8008CE8C 00089A6C  41 82 00 18 */	beq lbl_8008CEA4
/* 8008CE90 00089A70  C3 FF 06 38 */	lfs f31, 0x638(r31)
/* 8008CE94 00089A74  7F E3 FB 78 */	mr r3, r31
/* 8008CE98 00089A78  C3 DF 06 3C */	lfs f30, 0x63c(r31)
/* 8008CE9C 00089A7C  4B FF 0B 01 */	bl func_8007D99C
/* 8008CEA0 00089A80  48 00 00 14 */	b lbl_8008CEB4
lbl_8008CEA4:
/* 8008CEA4 00089A84  C3 FF 06 20 */	lfs f31, 0x620(r31)
/* 8008CEA8 00089A88  7F E3 FB 78 */	mr r3, r31
/* 8008CEAC 00089A8C  C3 DF 06 24 */	lfs f30, 0x624(r31)
/* 8008CEB0 00089A90  4B FF 0A B5 */	bl func_8007D964
lbl_8008CEB4:
/* 8008CEB4 00089A94  C0 02 8A D0 */	lfs f0, lbl_804D84B0(r2)
/* 8008CEB8 00089A98  FC 1F 00 40 */	fcmpo cr0, f31, f0
/* 8008CEBC 00089A9C  40 80 00 0C */	bge lbl_8008CEC8
/* 8008CEC0 00089AA0  FC 40 F8 50 */	fneg f2, f31
/* 8008CEC4 00089AA4  48 00 00 08 */	b lbl_8008CECC
lbl_8008CEC8:
/* 8008CEC8 00089AA8  FC 40 F8 90 */	fmr f2, f31
lbl_8008CECC:
/* 8008CECC 00089AAC  80 6D AE B4 */	lwz r3, p_ftCommonData(r13)
/* 8008CED0 00089AB0  C0 03 00 DC */	lfs f0, 0xdc(r3)
/* 8008CED4 00089AB4  FC 02 00 40 */	fcmpo cr0, f2, f0
/* 8008CED8 00089AB8  40 80 00 30 */	bge lbl_8008CF08
/* 8008CEDC 00089ABC  C0 02 8A D0 */	lfs f0, lbl_804D84B0(r2)
/* 8008CEE0 00089AC0  FC 1E 00 40 */	fcmpo cr0, f30, f0
/* 8008CEE4 00089AC4  40 80 00 0C */	bge lbl_8008CEF0
/* 8008CEE8 00089AC8  FC 40 F0 50 */	fneg f2, f30
/* 8008CEEC 00089ACC  48 00 00 08 */	b lbl_8008CEF4
lbl_8008CEF0:
/* 8008CEF0 00089AD0  FC 40 F0 90 */	fmr f2, f30
lbl_8008CEF4:
/* 8008CEF4 00089AD4  C0 03 00 E0 */	lfs f0, 0xe0(r3)
/* 8008CEF8 00089AD8  FC 02 00 40 */	fcmpo cr0, f2, f0
/* 8008CEFC 00089ADC  40 80 00 0C */	bge lbl_8008CF08
/* 8008CF00 00089AE0  38 60 00 41 */	li r3, 0x41
/* 8008CF04 00089AE4  48 00 00 50 */	b lbl_8008CF54
lbl_8008CF08:
/* 8008CF08 00089AE8  C0 03 00 20 */	lfs f0, 0x20(r3)
/* 8008CF0C 00089AEC  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8008CF10 00089AF0  40 81 00 0C */	ble lbl_8008CF1C
/* 8008CF14 00089AF4  38 60 00 44 */	li r3, 0x44
/* 8008CF18 00089AF8  48 00 00 3C */	b lbl_8008CF54
lbl_8008CF1C:
/* 8008CF1C 00089AFC  FC 00 00 50 */	fneg f0, f0
/* 8008CF20 00089B00  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8008CF24 00089B04  40 80 00 0C */	bge lbl_8008CF30
/* 8008CF28 00089B08  38 60 00 45 */	li r3, 0x45
/* 8008CF2C 00089B0C  48 00 00 28 */	b lbl_8008CF54
lbl_8008CF30:
/* 8008CF30 00089B10  C0 3F 00 2C */	lfs f1, 0x2c(r31)
/* 8008CF34 00089B14  C0 02 8A D0 */	lfs f0, lbl_804D84B0(r2)
/* 8008CF38 00089B18  EC 3F 00 72 */	fmuls f1, f31, f1
/* 8008CF3C 00089B1C  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8008CF40 00089B20  4C 41 13 82 */	cror 2, 1, 2
/* 8008CF44 00089B24  40 82 00 0C */	bne lbl_8008CF50
/* 8008CF48 00089B28  38 60 00 42 */	li r3, 0x42
/* 8008CF4C 00089B2C  48 00 00 08 */	b lbl_8008CF54
lbl_8008CF50:
/* 8008CF50 00089B30  38 60 00 43 */	li r3, 0x43
lbl_8008CF54:
/* 8008CF54 00089B34  80 01 00 2C */	lwz r0, 0x2c(r1)
/* 8008CF58 00089B38  CB E1 00 20 */	lfd f31, 0x20(r1)
/* 8008CF5C 00089B3C  CB C1 00 18 */	lfd f30, 0x18(r1)
/* 8008CF60 00089B40  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 8008CF64 00089B44  38 21 00 28 */	addi r1, r1, 0x28
/* 8008CF68 00089B48  7C 08 03 A6 */	mtlr r0
/* 8008CF6C 00089B4C  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

#pragma push
asm unk_t func_8008CF70()
{ // clang-format off
    nofralloc
/* 8008CF70 00089B50  7C 08 02 A6 */	mflr r0
/* 8008CF74 00089B54  90 01 00 04 */	stw r0, 4(r1)
/* 8008CF78 00089B58  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 8008CF7C 00089B5C  93 E1 00 14 */	stw r31, 0x14(r1)
/* 8008CF80 00089B60  7C 7F 1B 78 */	mr r31, r3
/* 8008CF84 00089B64  80 63 00 2C */	lwz r3, 0x2c(r3)
/* 8008CF88 00089B68  4B FF FE E1 */	bl func_8008CE68
/* 8008CF8C 00089B6C  38 83 00 00 */	addi r4, r3, 0
/* 8008CF90 00089B70  38 7F 00 00 */	addi r3, r31, 0
/* 8008CF94 00089B74  48 00 00 19 */	bl func_8008CFAC
/* 8008CF98 00089B78  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 8008CF9C 00089B7C  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 8008CFA0 00089B80  38 21 00 18 */	addi r1, r1, 0x18
/* 8008CFA4 00089B84  7C 08 03 A6 */	mtlr r0
/* 8008CFA8 00089B88  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

extern f32 const lbl_804D84B4;

#pragma push
asm void func_8008CFAC(HSD_GObj* fighter_gobj, s32 asid)
{ // clang-format off
    nofralloc
/* 8008CFAC 00089B8C  7C 08 02 A6 */	mflr r0
/* 8008CFB0 00089B90  38 E0 00 00 */	li r7, 0
/* 8008CFB4 00089B94  90 01 00 04 */	stw r0, 4(r1)
/* 8008CFB8 00089B98  38 A0 00 01 */	li r5, 1
/* 8008CFBC 00089B9C  38 C0 00 00 */	li r6, 0
/* 8008CFC0 00089BA0  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 8008CFC4 00089BA4  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 8008CFC8 00089BA8  7C 7F 1B 78 */	mr r31, r3
/* 8008CFCC 00089BAC  81 03 00 2C */	lwz r8, 0x2c(r3)
/* 8008CFD0 00089BB0  88 08 22 18 */	lbz r0, 0x2218(r8)
/* 8008CFD4 00089BB4  50 E0 3E 30 */	rlwimi r0, r7, 7, 0x18, 0x18
/* 8008CFD8 00089BB8  98 08 22 18 */	stb r0, 0x2218(r8)
/* 8008CFDC 00089BBC  90 E8 22 00 */	stw r7, 0x2200(r8)
/* 8008CFE0 00089BC0  90 E8 22 10 */	stw r7, 0x2210(r8)
/* 8008CFE4 00089BC4  C0 22 8A D0 */	lfs f1, lbl_804D84B0(r2)
/* 8008CFE8 00089BC8  C0 42 8A D4 */	lfs f2, lbl_804D84B4(r2)
/* 8008CFEC 00089BCC  FC 60 08 90 */	fmr f3, f1
/* 8008CFF0 00089BD0  4B FD C3 BD */	bl Fighter_ActionStateChange_800693AC
/* 8008CFF4 00089BD4  7F E3 FB 78 */	mr r3, r31
/* 8008CFF8 00089BD8  4B FE 1B AD */	bl func_8006EBA4
/* 8008CFFC 00089BDC  80 01 00 24 */	lwz r0, 0x24(r1)
/* 8008D000 00089BE0  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 8008D004 00089BE4  38 21 00 20 */	addi r1, r1, 0x20
/* 8008D008 00089BE8  7C 08 03 A6 */	mtlr r0
/* 8008D00C 00089BEC  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

#pragma push
asm unk_t func_8008D010()
{ // clang-format off
    nofralloc
/* 8008D010 00089BF0  7C 08 02 A6 */	mflr r0
/* 8008D014 00089BF4  90 01 00 04 */	stw r0, 4(r1)
/* 8008D018 00089BF8  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 8008D01C 00089BFC  93 E1 00 14 */	stw r31, 0x14(r1)
/* 8008D020 00089C00  7C 7F 1B 78 */	mr r31, r3
/* 8008D024 00089C04  80 83 00 2C */	lwz r4, 0x2c(r3)
/* 8008D028 00089C08  88 64 22 10 */	lbz r3, 0x2210(r4)
/* 8008D02C 00089C0C  54 60 E7 FF */	rlwinm. r0, r3, 0x1c, 0x1f, 0x1f
/* 8008D030 00089C10  41 82 00 18 */	beq lbl_8008D048
/* 8008D034 00089C14  38 00 00 00 */	li r0, 0
/* 8008D038 00089C18  50 03 26 F6 */	rlwimi r3, r0, 4, 0x1b, 0x1b
/* 8008D03C 00089C1C  98 64 22 10 */	stb r3, 0x2210(r4)
/* 8008D040 00089C20  38 00 00 01 */	li r0, 1
/* 8008D044 00089C24  48 00 00 08 */	b lbl_8008D04C
lbl_8008D048:
/* 8008D048 00089C28  38 00 00 00 */	li r0, 0
lbl_8008D04C:
/* 8008D04C 00089C2C  2C 00 00 00 */	cmpwi r0, 0
/* 8008D050 00089C30  41 82 00 10 */	beq lbl_8008D060
/* 8008D054 00089C34  C0 04 00 2C */	lfs f0, 0x2c(r4)
/* 8008D058 00089C38  FC 00 00 50 */	fneg f0, f0
/* 8008D05C 00089C3C  D0 04 00 2C */	stfs f0, 0x2c(r4)
lbl_8008D060:
/* 8008D060 00089C40  7F E3 FB 78 */	mr r3, r31
/* 8008D064 00089C44  4B FE 21 D5 */	bl ftAnim_IsFramesRemaining
/* 8008D068 00089C48  2C 03 00 00 */	cmpwi r3, 0
/* 8008D06C 00089C4C  40 82 00 0C */	bne lbl_8008D078
/* 8008D070 00089C50  7F E3 FB 78 */	mr r3, r31
/* 8008D074 00089C54  48 03 F6 BD */	bl func_800CC730
lbl_8008D078:
/* 8008D078 00089C58  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 8008D07C 00089C5C  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 8008D080 00089C60  38 21 00 18 */	addi r1, r1, 0x18
/* 8008D084 00089C64  7C 08 03 A6 */	mtlr r0
/* 8008D088 00089C68  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

extern unk_t func_800D705C();
extern unk_t func_800C3B10();
extern unk_t func_800D7100();
extern unk_t func_80095328();

#pragma push
asm unk_t func_8008D08C()
{ // clang-format off
    nofralloc
/* 8008D08C 00089C6C  7C 08 02 A6 */	mflr r0
/* 8008D090 00089C70  90 01 00 04 */	stw r0, 4(r1)
/* 8008D094 00089C74  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 8008D098 00089C78  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 8008D09C 00089C7C  93 C1 00 18 */	stw r30, 0x18(r1)
/* 8008D0A0 00089C80  7C 7E 1B 78 */	mr r30, r3
/* 8008D0A4 00089C84  80 63 00 2C */	lwz r3, 0x2c(r3)
/* 8008D0A8 00089C88  88 03 22 18 */	lbz r0, 0x2218(r3)
/* 8008D0AC 00089C8C  54 00 CF FF */	rlwinm. r0, r0, 0x19, 0x1f, 0x1f
/* 8008D0B0 00089C90  41 82 00 CC */	beq lbl_8008D17C
/* 8008D0B4 00089C94  38 7E 00 00 */	addi r3, r30, 0
/* 8008D0B8 00089C98  38 80 00 00 */	li r4, 0
/* 8008D0BC 00089C9C  48 00 82 6D */	bl func_80095328
/* 8008D0C0 00089CA0  2C 03 00 00 */	cmpwi r3, 0
/* 8008D0C4 00089CA4  40 82 00 B8 */	bne lbl_8008D17C
/* 8008D0C8 00089CA8  7F C3 F3 78 */	mr r3, r30
/* 8008D0CC 00089CAC  48 04 A0 35 */	bl func_800D7100
/* 8008D0D0 00089CB0  2C 03 00 00 */	cmpwi r3, 0
/* 8008D0D4 00089CB4  40 82 00 A8 */	bne lbl_8008D17C
/* 8008D0D8 00089CB8  7F C3 F3 78 */	mr r3, r30
/* 8008D0DC 00089CBC  48 03 6A 35 */	bl func_800C3B10
/* 8008D0E0 00089CC0  2C 03 00 00 */	cmpwi r3, 0
/* 8008D0E4 00089CC4  40 82 00 98 */	bne lbl_8008D17C
/* 8008D0E8 00089CC8  83 FE 00 2C */	lwz r31, 0x2c(r30)
/* 8008D0EC 00089CCC  80 1F 06 68 */	lwz r0, 0x668(r31)
/* 8008D0F0 00089CD0  54 00 05 EF */	rlwinm. r0, r0, 0, 0x17, 0x17
/* 8008D0F4 00089CD4  40 82 00 14 */	bne lbl_8008D108
/* 8008D0F8 00089CD8  7F E3 FB 78 */	mr r3, r31
/* 8008D0FC 00089CDC  48 05 23 7D */	bl func_800DF478
/* 8008D100 00089CE0  2C 03 00 00 */	cmpwi r3, 0
/* 8008D104 00089CE4  41 82 00 50 */	beq lbl_8008D154
lbl_8008D108:
/* 8008D108 00089CE8  7F E3 FB 78 */	mr r3, r31
/* 8008D10C 00089CEC  4B FF FD 5D */	bl func_8008CE68
/* 8008D110 00089CF0  38 03 FF BF */	addi r0, r3, -65
/* 8008D114 00089CF4  28 00 00 01 */	cmplwi r0, 1
/* 8008D118 00089CF8  41 81 00 2C */	bgt lbl_8008D144
/* 8008D11C 00089CFC  80 7F 19 74 */	lwz r3, 0x1974(r31)
/* 8008D120 00089D00  28 03 00 00 */	cmplwi r3, 0
/* 8008D124 00089D04  41 82 00 20 */	beq lbl_8008D144
/* 8008D128 00089D08  48 1D E1 E5 */	bl func_8026B30C
/* 8008D12C 00089D0C  2C 03 00 03 */	cmpwi r3, 3
/* 8008D130 00089D10  40 82 00 14 */	bne lbl_8008D144
/* 8008D134 00089D14  7F C3 F3 78 */	mr r3, r30
/* 8008D138 00089D18  48 04 0C 69 */	bl func_800CDDA0
/* 8008D13C 00089D1C  38 00 00 01 */	li r0, 1
/* 8008D140 00089D20  48 00 00 18 */	b lbl_8008D158
lbl_8008D144:
/* 8008D144 00089D24  7F C3 F3 78 */	mr r3, r30
/* 8008D148 00089D28  4B FF FC C5 */	bl func_8008CE0C
/* 8008D14C 00089D2C  38 00 00 01 */	li r0, 1
/* 8008D150 00089D30  48 00 00 08 */	b lbl_8008D158
lbl_8008D154:
/* 8008D154 00089D34  38 00 00 00 */	li r0, 0
lbl_8008D158:
/* 8008D158 00089D38  2C 00 00 00 */	cmpwi r0, 0
/* 8008D15C 00089D3C  40 82 00 20 */	bne lbl_8008D17C
/* 8008D160 00089D40  7F C3 F3 78 */	mr r3, r30
/* 8008D164 00089D44  48 04 9E F9 */	bl func_800D705C
/* 8008D168 00089D48  2C 03 00 00 */	cmpwi r3, 0
/* 8008D16C 00089D4C  40 82 00 10 */	bne lbl_8008D17C
/* 8008D170 00089D50  7F C3 F3 78 */	mr r3, r30
/* 8008D174 00089D54  48 03 E6 FD */	bl func_800CB870
/* 8008D178 00089D58  2C 03 00 00 */	cmpwi r3, 0
lbl_8008D17C:
/* 8008D17C 00089D5C  80 01 00 24 */	lwz r0, 0x24(r1)
/* 8008D180 00089D60  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 8008D184 00089D64  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 8008D188 00089D68  38 21 00 20 */	addi r1, r1, 0x20
/* 8008D18C 00089D6C  7C 08 03 A6 */	mtlr r0
/* 8008D190 00089D70  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

#pragma push
asm unk_t func_8008D194()
{ // clang-format off
    nofralloc
/* 8008D194 00089D74  7C 08 02 A6 */	mflr r0
/* 8008D198 00089D78  90 01 00 04 */	stw r0, 4(r1)
/* 8008D19C 00089D7C  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 8008D1A0 00089D80  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 8008D1A4 00089D84  93 C1 00 18 */	stw r30, 0x18(r1)
/* 8008D1A8 00089D88  7C 7E 1B 78 */	mr r30, r3
/* 8008D1AC 00089D8C  80 63 00 2C */	lwz r3, 0x2c(r3)
/* 8008D1B0 00089D90  88 03 22 18 */	lbz r0, 0x2218(r3)
/* 8008D1B4 00089D94  54 00 CF FF */	rlwinm. r0, r0, 0x19, 0x1f, 0x1f
/* 8008D1B8 00089D98  41 82 00 CC */	beq lbl_8008D284
/* 8008D1BC 00089D9C  38 7E 00 00 */	addi r3, r30, 0
/* 8008D1C0 00089DA0  38 80 00 00 */	li r4, 0
/* 8008D1C4 00089DA4  48 00 81 65 */	bl func_80095328
/* 8008D1C8 00089DA8  2C 03 00 00 */	cmpwi r3, 0
/* 8008D1CC 00089DAC  40 82 00 B8 */	bne lbl_8008D284
/* 8008D1D0 00089DB0  7F C3 F3 78 */	mr r3, r30
/* 8008D1D4 00089DB4  48 04 9F 2D */	bl func_800D7100
/* 8008D1D8 00089DB8  2C 03 00 00 */	cmpwi r3, 0
/* 8008D1DC 00089DBC  40 82 00 A8 */	bne lbl_8008D284
/* 8008D1E0 00089DC0  7F C3 F3 78 */	mr r3, r30
/* 8008D1E4 00089DC4  48 03 69 2D */	bl func_800C3B10
/* 8008D1E8 00089DC8  2C 03 00 00 */	cmpwi r3, 0
/* 8008D1EC 00089DCC  40 82 00 98 */	bne lbl_8008D284
/* 8008D1F0 00089DD0  83 FE 00 2C */	lwz r31, 0x2c(r30)
/* 8008D1F4 00089DD4  80 1F 06 68 */	lwz r0, 0x668(r31)
/* 8008D1F8 00089DD8  54 00 05 EF */	rlwinm. r0, r0, 0, 0x17, 0x17
/* 8008D1FC 00089DDC  40 82 00 14 */	bne lbl_8008D210
/* 8008D200 00089DE0  7F E3 FB 78 */	mr r3, r31
/* 8008D204 00089DE4  48 05 22 75 */	bl func_800DF478
/* 8008D208 00089DE8  2C 03 00 00 */	cmpwi r3, 0
/* 8008D20C 00089DEC  41 82 00 50 */	beq lbl_8008D25C
lbl_8008D210:
/* 8008D210 00089DF0  7F E3 FB 78 */	mr r3, r31
/* 8008D214 00089DF4  4B FF FC 55 */	bl func_8008CE68
/* 8008D218 00089DF8  38 03 FF BF */	addi r0, r3, -65
/* 8008D21C 00089DFC  28 00 00 01 */	cmplwi r0, 1
/* 8008D220 00089E00  41 81 00 2C */	bgt lbl_8008D24C
/* 8008D224 00089E04  80 7F 19 74 */	lwz r3, 0x1974(r31)
/* 8008D228 00089E08  28 03 00 00 */	cmplwi r3, 0
/* 8008D22C 00089E0C  41 82 00 20 */	beq lbl_8008D24C
/* 8008D230 00089E10  48 1D E0 DD */	bl func_8026B30C
/* 8008D234 00089E14  2C 03 00 03 */	cmpwi r3, 3
/* 8008D238 00089E18  40 82 00 14 */	bne lbl_8008D24C
/* 8008D23C 00089E1C  7F C3 F3 78 */	mr r3, r30
/* 8008D240 00089E20  48 04 0B 61 */	bl func_800CDDA0
/* 8008D244 00089E24  38 00 00 01 */	li r0, 1
/* 8008D248 00089E28  48 00 00 18 */	b lbl_8008D260
lbl_8008D24C:
/* 8008D24C 00089E2C  7F C3 F3 78 */	mr r3, r30
/* 8008D250 00089E30  4B FF FB BD */	bl func_8008CE0C
/* 8008D254 00089E34  38 00 00 01 */	li r0, 1
/* 8008D258 00089E38  48 00 00 08 */	b lbl_8008D260
lbl_8008D25C:
/* 8008D25C 00089E3C  38 00 00 00 */	li r0, 0
lbl_8008D260:
/* 8008D260 00089E40  2C 00 00 00 */	cmpwi r0, 0
/* 8008D264 00089E44  40 82 00 20 */	bne lbl_8008D284
/* 8008D268 00089E48  7F C3 F3 78 */	mr r3, r30
/* 8008D26C 00089E4C  48 04 9D F1 */	bl func_800D705C
/* 8008D270 00089E50  2C 03 00 00 */	cmpwi r3, 0
/* 8008D274 00089E54  40 82 00 10 */	bne lbl_8008D284
/* 8008D278 00089E58  7F C3 F3 78 */	mr r3, r30
/* 8008D27C 00089E5C  48 03 E5 F5 */	bl func_800CB870
/* 8008D280 00089E60  2C 03 00 00 */	cmpwi r3, 0
lbl_8008D284:
/* 8008D284 00089E64  80 01 00 24 */	lwz r0, 0x24(r1)
/* 8008D288 00089E68  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 8008D28C 00089E6C  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 8008D290 00089E70  38 21 00 20 */	addi r1, r1, 0x20
/* 8008D294 00089E74  7C 08 03 A6 */	mtlr r0
/* 8008D298 00089E78  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

#pragma push
asm unk_t func_8008D29C()
{ // clang-format off
    nofralloc
/* 8008D29C 00089E7C  7C 08 02 A6 */	mflr r0
/* 8008D2A0 00089E80  90 01 00 04 */	stw r0, 4(r1)
/* 8008D2A4 00089E84  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 8008D2A8 00089E88  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 8008D2AC 00089E8C  93 C1 00 18 */	stw r30, 0x18(r1)
/* 8008D2B0 00089E90  7C 7E 1B 78 */	mr r30, r3
/* 8008D2B4 00089E94  80 63 00 2C */	lwz r3, 0x2c(r3)
/* 8008D2B8 00089E98  88 03 22 18 */	lbz r0, 0x2218(r3)
/* 8008D2BC 00089E9C  54 00 CF FF */	rlwinm. r0, r0, 0x19, 0x1f, 0x1f
/* 8008D2C0 00089EA0  41 82 00 CC */	beq lbl_8008D38C
/* 8008D2C4 00089EA4  38 7E 00 00 */	addi r3, r30, 0
/* 8008D2C8 00089EA8  38 80 00 00 */	li r4, 0
/* 8008D2CC 00089EAC  48 00 80 5D */	bl func_80095328
/* 8008D2D0 00089EB0  2C 03 00 00 */	cmpwi r3, 0
/* 8008D2D4 00089EB4  40 82 00 B8 */	bne lbl_8008D38C
/* 8008D2D8 00089EB8  7F C3 F3 78 */	mr r3, r30
/* 8008D2DC 00089EBC  48 04 9E 25 */	bl func_800D7100
/* 8008D2E0 00089EC0  2C 03 00 00 */	cmpwi r3, 0
/* 8008D2E4 00089EC4  40 82 00 A8 */	bne lbl_8008D38C
/* 8008D2E8 00089EC8  7F C3 F3 78 */	mr r3, r30
/* 8008D2EC 00089ECC  48 03 68 25 */	bl func_800C3B10
/* 8008D2F0 00089ED0  2C 03 00 00 */	cmpwi r3, 0
/* 8008D2F4 00089ED4  40 82 00 98 */	bne lbl_8008D38C
/* 8008D2F8 00089ED8  83 FE 00 2C */	lwz r31, 0x2c(r30)
/* 8008D2FC 00089EDC  80 1F 06 68 */	lwz r0, 0x668(r31)
/* 8008D300 00089EE0  54 00 05 EF */	rlwinm. r0, r0, 0, 0x17, 0x17
/* 8008D304 00089EE4  40 82 00 14 */	bne lbl_8008D318
/* 8008D308 00089EE8  7F E3 FB 78 */	mr r3, r31
/* 8008D30C 00089EEC  48 05 21 6D */	bl func_800DF478
/* 8008D310 00089EF0  2C 03 00 00 */	cmpwi r3, 0
/* 8008D314 00089EF4  41 82 00 50 */	beq lbl_8008D364
lbl_8008D318:
/* 8008D318 00089EF8  7F E3 FB 78 */	mr r3, r31
/* 8008D31C 00089EFC  4B FF FB 4D */	bl func_8008CE68
/* 8008D320 00089F00  38 03 FF BF */	addi r0, r3, -65
/* 8008D324 00089F04  28 00 00 01 */	cmplwi r0, 1
/* 8008D328 00089F08  41 81 00 2C */	bgt lbl_8008D354
/* 8008D32C 00089F0C  80 7F 19 74 */	lwz r3, 0x1974(r31)
/* 8008D330 00089F10  28 03 00 00 */	cmplwi r3, 0
/* 8008D334 00089F14  41 82 00 20 */	beq lbl_8008D354
/* 8008D338 00089F18  48 1D DF D5 */	bl func_8026B30C
/* 8008D33C 00089F1C  2C 03 00 03 */	cmpwi r3, 3
/* 8008D340 00089F20  40 82 00 14 */	bne lbl_8008D354
/* 8008D344 00089F24  7F C3 F3 78 */	mr r3, r30
/* 8008D348 00089F28  48 04 0A 59 */	bl func_800CDDA0
/* 8008D34C 00089F2C  38 00 00 01 */	li r0, 1
/* 8008D350 00089F30  48 00 00 18 */	b lbl_8008D368
lbl_8008D354:
/* 8008D354 00089F34  7F C3 F3 78 */	mr r3, r30
/* 8008D358 00089F38  4B FF FA B5 */	bl func_8008CE0C
/* 8008D35C 00089F3C  38 00 00 01 */	li r0, 1
/* 8008D360 00089F40  48 00 00 08 */	b lbl_8008D368
lbl_8008D364:
/* 8008D364 00089F44  38 00 00 00 */	li r0, 0
lbl_8008D368:
/* 8008D368 00089F48  2C 00 00 00 */	cmpwi r0, 0
/* 8008D36C 00089F4C  40 82 00 20 */	bne lbl_8008D38C
/* 8008D370 00089F50  7F C3 F3 78 */	mr r3, r30
/* 8008D374 00089F54  48 04 9C E9 */	bl func_800D705C
/* 8008D378 00089F58  2C 03 00 00 */	cmpwi r3, 0
/* 8008D37C 00089F5C  40 82 00 10 */	bne lbl_8008D38C
/* 8008D380 00089F60  7F C3 F3 78 */	mr r3, r30
/* 8008D384 00089F64  48 03 E4 ED */	bl func_800CB870
/* 8008D388 00089F68  2C 03 00 00 */	cmpwi r3, 0
lbl_8008D38C:
/* 8008D38C 00089F6C  80 01 00 24 */	lwz r0, 0x24(r1)
/* 8008D390 00089F70  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 8008D394 00089F74  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 8008D398 00089F78  38 21 00 20 */	addi r1, r1, 0x20
/* 8008D39C 00089F7C  7C 08 03 A6 */	mtlr r0
/* 8008D3A0 00089F80  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

#pragma push
asm unk_t func_8008D3A4()
{ // clang-format off
    nofralloc
/* 8008D3A4 00089F84  7C 08 02 A6 */	mflr r0
/* 8008D3A8 00089F88  90 01 00 04 */	stw r0, 4(r1)
/* 8008D3AC 00089F8C  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 8008D3B0 00089F90  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 8008D3B4 00089F94  93 C1 00 18 */	stw r30, 0x18(r1)
/* 8008D3B8 00089F98  7C 7E 1B 78 */	mr r30, r3
/* 8008D3BC 00089F9C  80 63 00 2C */	lwz r3, 0x2c(r3)
/* 8008D3C0 00089FA0  88 03 22 18 */	lbz r0, 0x2218(r3)
/* 8008D3C4 00089FA4  54 00 CF FF */	rlwinm. r0, r0, 0x19, 0x1f, 0x1f
/* 8008D3C8 00089FA8  41 82 00 CC */	beq lbl_8008D494
/* 8008D3CC 00089FAC  38 7E 00 00 */	addi r3, r30, 0
/* 8008D3D0 00089FB0  38 80 00 00 */	li r4, 0
/* 8008D3D4 00089FB4  48 00 7F 55 */	bl func_80095328
/* 8008D3D8 00089FB8  2C 03 00 00 */	cmpwi r3, 0
/* 8008D3DC 00089FBC  40 82 00 B8 */	bne lbl_8008D494
/* 8008D3E0 00089FC0  7F C3 F3 78 */	mr r3, r30
/* 8008D3E4 00089FC4  48 04 9D 1D */	bl func_800D7100
/* 8008D3E8 00089FC8  2C 03 00 00 */	cmpwi r3, 0
/* 8008D3EC 00089FCC  40 82 00 A8 */	bne lbl_8008D494
/* 8008D3F0 00089FD0  7F C3 F3 78 */	mr r3, r30
/* 8008D3F4 00089FD4  48 03 67 1D */	bl func_800C3B10
/* 8008D3F8 00089FD8  2C 03 00 00 */	cmpwi r3, 0
/* 8008D3FC 00089FDC  40 82 00 98 */	bne lbl_8008D494
/* 8008D400 00089FE0  83 FE 00 2C */	lwz r31, 0x2c(r30)
/* 8008D404 00089FE4  80 1F 06 68 */	lwz r0, 0x668(r31)
/* 8008D408 00089FE8  54 00 05 EF */	rlwinm. r0, r0, 0, 0x17, 0x17
/* 8008D40C 00089FEC  40 82 00 14 */	bne lbl_8008D420
/* 8008D410 00089FF0  7F E3 FB 78 */	mr r3, r31
/* 8008D414 00089FF4  48 05 20 65 */	bl func_800DF478
/* 8008D418 00089FF8  2C 03 00 00 */	cmpwi r3, 0
/* 8008D41C 00089FFC  41 82 00 50 */	beq lbl_8008D46C
lbl_8008D420:
/* 8008D420 0008A000  7F E3 FB 78 */	mr r3, r31
/* 8008D424 0008A004  4B FF FA 45 */	bl func_8008CE68
/* 8008D428 0008A008  38 03 FF BF */	addi r0, r3, -65
/* 8008D42C 0008A00C  28 00 00 01 */	cmplwi r0, 1
/* 8008D430 0008A010  41 81 00 2C */	bgt lbl_8008D45C
/* 8008D434 0008A014  80 7F 19 74 */	lwz r3, 0x1974(r31)
/* 8008D438 0008A018  28 03 00 00 */	cmplwi r3, 0
/* 8008D43C 0008A01C  41 82 00 20 */	beq lbl_8008D45C
/* 8008D440 0008A020  48 1D DE CD */	bl func_8026B30C
/* 8008D444 0008A024  2C 03 00 03 */	cmpwi r3, 3
/* 8008D448 0008A028  40 82 00 14 */	bne lbl_8008D45C
/* 8008D44C 0008A02C  7F C3 F3 78 */	mr r3, r30
/* 8008D450 0008A030  48 04 09 51 */	bl func_800CDDA0
/* 8008D454 0008A034  38 00 00 01 */	li r0, 1
/* 8008D458 0008A038  48 00 00 18 */	b lbl_8008D470
lbl_8008D45C:
/* 8008D45C 0008A03C  7F C3 F3 78 */	mr r3, r30
/* 8008D460 0008A040  4B FF F9 AD */	bl func_8008CE0C
/* 8008D464 0008A044  38 00 00 01 */	li r0, 1
/* 8008D468 0008A048  48 00 00 08 */	b lbl_8008D470
lbl_8008D46C:
/* 8008D46C 0008A04C  38 00 00 00 */	li r0, 0
lbl_8008D470:
/* 8008D470 0008A050  2C 00 00 00 */	cmpwi r0, 0
/* 8008D474 0008A054  40 82 00 20 */	bne lbl_8008D494
/* 8008D478 0008A058  7F C3 F3 78 */	mr r3, r30
/* 8008D47C 0008A05C  48 04 9B E1 */	bl func_800D705C
/* 8008D480 0008A060  2C 03 00 00 */	cmpwi r3, 0
/* 8008D484 0008A064  40 82 00 10 */	bne lbl_8008D494
/* 8008D488 0008A068  7F C3 F3 78 */	mr r3, r30
/* 8008D48C 0008A06C  48 03 E3 E5 */	bl func_800CB870
/* 8008D490 0008A070  2C 03 00 00 */	cmpwi r3, 0
lbl_8008D494:
/* 8008D494 0008A074  80 01 00 24 */	lwz r0, 0x24(r1)
/* 8008D498 0008A078  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 8008D49C 0008A07C  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 8008D4A0 0008A080  38 21 00 20 */	addi r1, r1, 0x20
/* 8008D4A4 0008A084  7C 08 03 A6 */	mtlr r0
/* 8008D4A8 0008A088  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

#pragma push
asm unk_t func_8008D4AC()
{ // clang-format off
    nofralloc
/* 8008D4AC 0008A08C  7C 08 02 A6 */	mflr r0
/* 8008D4B0 0008A090  90 01 00 04 */	stw r0, 4(r1)
/* 8008D4B4 0008A094  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 8008D4B8 0008A098  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 8008D4BC 0008A09C  93 C1 00 18 */	stw r30, 0x18(r1)
/* 8008D4C0 0008A0A0  7C 7E 1B 78 */	mr r30, r3
/* 8008D4C4 0008A0A4  80 63 00 2C */	lwz r3, 0x2c(r3)
/* 8008D4C8 0008A0A8  88 03 22 18 */	lbz r0, 0x2218(r3)
/* 8008D4CC 0008A0AC  54 00 CF FF */	rlwinm. r0, r0, 0x19, 0x1f, 0x1f
/* 8008D4D0 0008A0B0  41 82 00 CC */	beq lbl_8008D59C
/* 8008D4D4 0008A0B4  38 7E 00 00 */	addi r3, r30, 0
/* 8008D4D8 0008A0B8  38 80 00 00 */	li r4, 0
/* 8008D4DC 0008A0BC  48 00 7E 4D */	bl func_80095328
/* 8008D4E0 0008A0C0  2C 03 00 00 */	cmpwi r3, 0
/* 8008D4E4 0008A0C4  40 82 00 B8 */	bne lbl_8008D59C
/* 8008D4E8 0008A0C8  7F C3 F3 78 */	mr r3, r30
/* 8008D4EC 0008A0CC  48 04 9C 15 */	bl func_800D7100
/* 8008D4F0 0008A0D0  2C 03 00 00 */	cmpwi r3, 0
/* 8008D4F4 0008A0D4  40 82 00 A8 */	bne lbl_8008D59C
/* 8008D4F8 0008A0D8  7F C3 F3 78 */	mr r3, r30
/* 8008D4FC 0008A0DC  48 03 66 15 */	bl func_800C3B10
/* 8008D500 0008A0E0  2C 03 00 00 */	cmpwi r3, 0
/* 8008D504 0008A0E4  40 82 00 98 */	bne lbl_8008D59C
/* 8008D508 0008A0E8  83 FE 00 2C */	lwz r31, 0x2c(r30)
/* 8008D50C 0008A0EC  80 1F 06 68 */	lwz r0, 0x668(r31)
/* 8008D510 0008A0F0  54 00 05 EF */	rlwinm. r0, r0, 0, 0x17, 0x17
/* 8008D514 0008A0F4  40 82 00 14 */	bne lbl_8008D528
/* 8008D518 0008A0F8  7F E3 FB 78 */	mr r3, r31
/* 8008D51C 0008A0FC  48 05 1F 5D */	bl func_800DF478
/* 8008D520 0008A100  2C 03 00 00 */	cmpwi r3, 0
/* 8008D524 0008A104  41 82 00 50 */	beq lbl_8008D574
lbl_8008D528:
/* 8008D528 0008A108  7F E3 FB 78 */	mr r3, r31
/* 8008D52C 0008A10C  4B FF F9 3D */	bl func_8008CE68
/* 8008D530 0008A110  38 03 FF BF */	addi r0, r3, -65
/* 8008D534 0008A114  28 00 00 01 */	cmplwi r0, 1
/* 8008D538 0008A118  41 81 00 2C */	bgt lbl_8008D564
/* 8008D53C 0008A11C  80 7F 19 74 */	lwz r3, 0x1974(r31)
/* 8008D540 0008A120  28 03 00 00 */	cmplwi r3, 0
/* 8008D544 0008A124  41 82 00 20 */	beq lbl_8008D564
/* 8008D548 0008A128  48 1D DD C5 */	bl func_8026B30C
/* 8008D54C 0008A12C  2C 03 00 03 */	cmpwi r3, 3
/* 8008D550 0008A130  40 82 00 14 */	bne lbl_8008D564
/* 8008D554 0008A134  7F C3 F3 78 */	mr r3, r30
/* 8008D558 0008A138  48 04 08 49 */	bl func_800CDDA0
/* 8008D55C 0008A13C  38 00 00 01 */	li r0, 1
/* 8008D560 0008A140  48 00 00 18 */	b lbl_8008D578
lbl_8008D564:
/* 8008D564 0008A144  7F C3 F3 78 */	mr r3, r30
/* 8008D568 0008A148  4B FF F8 A5 */	bl func_8008CE0C
/* 8008D56C 0008A14C  38 00 00 01 */	li r0, 1
/* 8008D570 0008A150  48 00 00 08 */	b lbl_8008D578
lbl_8008D574:
/* 8008D574 0008A154  38 00 00 00 */	li r0, 0
lbl_8008D578:
/* 8008D578 0008A158  2C 00 00 00 */	cmpwi r0, 0
/* 8008D57C 0008A15C  40 82 00 20 */	bne lbl_8008D59C
/* 8008D580 0008A160  7F C3 F3 78 */	mr r3, r30
/* 8008D584 0008A164  48 04 9A D9 */	bl func_800D705C
/* 8008D588 0008A168  2C 03 00 00 */	cmpwi r3, 0
/* 8008D58C 0008A16C  40 82 00 10 */	bne lbl_8008D59C
/* 8008D590 0008A170  7F C3 F3 78 */	mr r3, r30
/* 8008D594 0008A174  48 03 E2 DD */	bl func_800CB870
/* 8008D598 0008A178  2C 03 00 00 */	cmpwi r3, 0
lbl_8008D59C:
/* 8008D59C 0008A17C  80 01 00 24 */	lwz r0, 0x24(r1)
/* 8008D5A0 0008A180  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 8008D5A4 0008A184  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 8008D5A8 0008A188  38 21 00 20 */	addi r1, r1, 0x20
/* 8008D5AC 0008A18C  7C 08 03 A6 */	mtlr r0
/* 8008D5B0 0008A190  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

#pragma push
asm unk_t func_8008D5B4()
{ // clang-format off
    nofralloc
/* 8008D5B4 0008A194  7C 08 02 A6 */	mflr r0
/* 8008D5B8 0008A198  90 01 00 04 */	stw r0, 4(r1)
/* 8008D5BC 0008A19C  94 21 FF F8 */	stwu r1, -8(r1)
/* 8008D5C0 0008A1A0  4B FF 77 F1 */	bl func_80084DB0
/* 8008D5C4 0008A1A4  80 01 00 0C */	lwz r0, 0xc(r1)
/* 8008D5C8 0008A1A8  38 21 00 08 */	addi r1, r1, 8
/* 8008D5CC 0008A1AC  7C 08 03 A6 */	mtlr r0
/* 8008D5D0 0008A1B0  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

extern unk_t func_8008D5FC();

#pragma push
asm unk_t func_8008D5D4()
{ // clang-format off
    nofralloc
/* 8008D5D4 0008A1B4  7C 08 02 A6 */	mflr r0
/* 8008D5D8 0008A1B8  3C 80 80 09 */	lis r4, func_8008D5FC@ha
/* 8008D5DC 0008A1BC  90 01 00 04 */	stw r0, 4(r1)
/* 8008D5E0 0008A1C0  38 84 D5 FC */	addi r4, r4, func_8008D5FC@l
/* 8008D5E4 0008A1C4  94 21 FF F8 */	stwu r1, -8(r1)
/* 8008D5E8 0008A1C8  4B FF 56 8D */	bl func_80082C74
/* 8008D5EC 0008A1CC  80 01 00 0C */	lwz r0, 0xc(r1)
/* 8008D5F0 0008A1D0  38 21 00 08 */	addi r1, r1, 8
/* 8008D5F4 0008A1D4  7C 08 03 A6 */	mtlr r0
/* 8008D5F8 0008A1D8  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

extern f64 const lbl_804D84B8;

#pragma push
asm unk_t func_8008D5FC()
{ // clang-format off
    nofralloc
/* 8008D5FC 0008A1DC  7C 08 02 A6 */	mflr r0
/* 8008D600 0008A1E0  38 80 FF FF */	li r4, -1
/* 8008D604 0008A1E4  90 01 00 04 */	stw r0, 4(r1)
/* 8008D608 0008A1E8  94 21 FF C8 */	stwu r1, -0x38(r1)
/* 8008D60C 0008A1EC  80 A3 00 2C */	lwz r5, 0x2c(r3)
/* 8008D610 0008A1F0  80 05 22 00 */	lwz r0, 0x2200(r5)
/* 8008D614 0008A1F4  28 00 00 00 */	cmplwi r0, 0
/* 8008D618 0008A1F8  41 82 00 CC */	beq lbl_8008D6E4
/* 8008D61C 0008A1FC  80 05 00 10 */	lwz r0, 0x10(r5)
/* 8008D620 0008A200  2C 00 00 43 */	cmpwi r0, 0x43
/* 8008D624 0008A204  41 82 00 40 */	beq lbl_8008D664
/* 8008D628 0008A208  40 80 00 14 */	bge lbl_8008D63C
/* 8008D62C 0008A20C  2C 00 00 41 */	cmpwi r0, 0x41
/* 8008D630 0008A210  41 82 00 1C */	beq lbl_8008D64C
/* 8008D634 0008A214  40 80 00 24 */	bge lbl_8008D658
/* 8008D638 0008A218  48 00 00 4C */	b lbl_8008D684
lbl_8008D63C:
/* 8008D63C 0008A21C  2C 00 00 45 */	cmpwi r0, 0x45
/* 8008D640 0008A220  41 82 00 3C */	beq lbl_8008D67C
/* 8008D644 0008A224  40 80 00 40 */	bge lbl_8008D684
/* 8008D648 0008A228  48 00 00 28 */	b lbl_8008D670
lbl_8008D64C:
/* 8008D64C 0008A22C  C0 25 01 F8 */	lfs f1, 0x1f8(r5)
/* 8008D650 0008A230  38 80 00 46 */	li r4, 0x46
/* 8008D654 0008A234  48 00 00 30 */	b lbl_8008D684
lbl_8008D658:
/* 8008D658 0008A238  C0 25 01 FC */	lfs f1, 0x1fc(r5)
/* 8008D65C 0008A23C  38 80 00 47 */	li r4, 0x47
/* 8008D660 0008A240  48 00 00 24 */	b lbl_8008D684
lbl_8008D664:
/* 8008D664 0008A244  C0 25 02 00 */	lfs f1, 0x200(r5)
/* 8008D668 0008A248  38 80 00 48 */	li r4, 0x48
/* 8008D66C 0008A24C  48 00 00 18 */	b lbl_8008D684
lbl_8008D670:
/* 8008D670 0008A250  C0 25 02 04 */	lfs f1, 0x204(r5)
/* 8008D674 0008A254  38 80 00 49 */	li r4, 0x49
/* 8008D678 0008A258  48 00 00 0C */	b lbl_8008D684
lbl_8008D67C:
/* 8008D67C 0008A25C  38 80 00 4A */	li r4, 0x4a
/* 8008D680 0008A260  C0 25 02 08 */	lfs f1, 0x208(r5)
lbl_8008D684:
/* 8008D684 0008A264  2C 04 FF FF */	cmpwi r4, -1
/* 8008D688 0008A268  41 82 00 5C */	beq lbl_8008D6E4
/* 8008D68C 0008A26C  80 CD AE B4 */	lwz r6, p_ftCommonData(r13)
/* 8008D690 0008A270  88 A5 06 7F */	lbz r5, 0x67f(r5)
/* 8008D694 0008A274  80 06 00 E4 */	lwz r0, 0xe4(r6)
/* 8008D698 0008A278  7C 05 00 00 */	cmpw r5, r0
/* 8008D69C 0008A27C  40 80 00 48 */	bge lbl_8008D6E4
/* 8008D6A0 0008A280  C0 06 00 E8 */	lfs f0, 0xe8(r6)
/* 8008D6A4 0008A284  EC 01 00 24 */	fdivs f0, f1, f0
/* 8008D6A8 0008A288  FC 00 00 1E */	fctiwz f0, f0
/* 8008D6AC 0008A28C  D8 01 00 28 */	stfd f0, 0x28(r1)
/* 8008D6B0 0008A290  80 01 00 2C */	lwz r0, 0x2c(r1)
/* 8008D6B4 0008A294  D8 01 00 30 */	stfd f0, 0x30(r1)
/* 8008D6B8 0008A298  2C 00 00 00 */	cmpwi r0, 0
/* 8008D6BC 0008A29C  80 01 00 34 */	lwz r0, 0x34(r1)
/* 8008D6C0 0008A2A0  40 82 00 08 */	bne lbl_8008D6C8
/* 8008D6C4 0008A2A4  38 00 00 01 */	li r0, 1
lbl_8008D6C8:
/* 8008D6C8 0008A2A8  6C 00 80 00 */	xoris r0, r0, 0x8000
/* 8008D6CC 0008A2AC  C8 22 8A D8 */	lfd f1, lbl_804D84B8(r2)
/* 8008D6D0 0008A2B0  90 01 00 2C */	stw r0, 0x2c(r1)
/* 8008D6D4 0008A2B4  3C 00 43 30 */	lis r0, 0x4330
/* 8008D6D8 0008A2B8  90 01 00 28 */	stw r0, 0x28(r1)
/* 8008D6DC 0008A2BC  C8 01 00 28 */	lfd f0, 0x28(r1)
/* 8008D6E0 0008A2C0  EC 20 08 28 */	fsubs f1, f0, f1
lbl_8008D6E4:
/* 8008D6E4 0008A2C4  2C 04 FF FF */	cmpwi r4, -1
/* 8008D6E8 0008A2C8  41 82 00 0C */	beq lbl_8008D6F4
/* 8008D6EC 0008A2CC  48 00 00 1D */	bl func_8008D708
/* 8008D6F0 0008A2D0  48 00 00 08 */	b lbl_8008D6F8
lbl_8008D6F4:
/* 8008D6F4 0008A2D4  48 04 85 05 */	bl func_800D5BF8
lbl_8008D6F8:
/* 8008D6F8 0008A2D8  80 01 00 3C */	lwz r0, 0x3c(r1)
/* 8008D6FC 0008A2DC  38 21 00 38 */	addi r1, r1, 0x38
/* 8008D700 0008A2E0  7C 08 03 A6 */	mtlr r0
/* 8008D704 0008A2E4  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

extern f32 const lbl_804D84C0;
extern f32 const lbl_804D84C4;
extern f32 const lbl_804D84C8;

#pragma push
asm void func_8008D708(HSD_GObj* fighter_gobj, s32 asid, f32 lag)
{ // clang-format off
    nofralloc
/* 8008D708 0008A2E8  7C 08 02 A6 */	mflr r0
/* 8008D70C 0008A2EC  90 01 00 04 */	stw r0, 4(r1)
/* 8008D710 0008A2F0  94 21 FF D0 */	stwu r1, -0x30(r1)
/* 8008D714 0008A2F4  DB E1 00 28 */	stfd f31, 0x28(r1)
/* 8008D718 0008A2F8  FF E0 08 90 */	fmr f31, f1
/* 8008D71C 0008A2FC  93 E1 00 24 */	stw r31, 0x24(r1)
/* 8008D720 0008A300  7C 9F 23 78 */	mr r31, r4
/* 8008D724 0008A304  93 C1 00 20 */	stw r30, 0x20(r1)
/* 8008D728 0008A308  7C 7E 1B 78 */	mr r30, r3
/* 8008D72C 0008A30C  80 63 00 2C */	lwz r3, 0x2c(r3)
/* 8008D730 0008A310  4B FF 00 CD */	bl func_8007D7FC
/* 8008D734 0008A314  C0 22 8A E0 */	lfs f1, lbl_804D84C0(r2)
/* 8008D738 0008A318  7F C3 F3 78 */	mr r3, r30
/* 8008D73C 0008A31C  C0 42 8A E4 */	lfs f2, lbl_804D84C4(r2)
/* 8008D740 0008A320  7F E4 FB 78 */	mr r4, r31
/* 8008D744 0008A324  FC 60 08 90 */	fmr f3, f1
/* 8008D748 0008A328  38 A0 00 00 */	li r5, 0
/* 8008D74C 0008A32C  38 C0 00 00 */	li r6, 0
/* 8008D750 0008A330  4B FD BC 5D */	bl Fighter_ActionStateChange_800693AC
/* 8008D754 0008A334  7F C3 F3 78 */	mr r3, r30
/* 8008D758 0008A338  4B FE 1D 2D */	bl func_8006F484
/* 8008D75C 0008A33C  C0 02 8A E8 */	lfs f0, lbl_804D84C8(r2)
/* 8008D760 0008A340  7F C3 F3 78 */	mr r3, r30
/* 8008D764 0008A344  EC 00 08 2A */	fadds f0, f0, f1
/* 8008D768 0008A348  EC 20 F8 24 */	fdivs f1, f0, f31
/* 8008D76C 0008A34C  4B FE 1A 25 */	bl ftAnim_SetAnimRate
/* 8008D770 0008A350  80 01 00 34 */	lwz r0, 0x34(r1)
/* 8008D774 0008A354  CB E1 00 28 */	lfd f31, 0x28(r1)
/* 8008D778 0008A358  83 E1 00 24 */	lwz r31, 0x24(r1)
/* 8008D77C 0008A35C  83 C1 00 20 */	lwz r30, 0x20(r1)
/* 8008D780 0008A360  38 21 00 30 */	addi r1, r1, 0x30
/* 8008D784 0008A364  7C 08 03 A6 */	mtlr r0
/* 8008D788 0008A368  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

#pragma push
asm unk_t func_8008D78C()
{ // clang-format off
    nofralloc
/* 8008D78C 0008A36C  7C 08 02 A6 */	mflr r0
/* 8008D790 0008A370  90 01 00 04 */	stw r0, 4(r1)
/* 8008D794 0008A374  94 21 FF F8 */	stwu r1, -8(r1)
/* 8008D798 0008A378  48 04 85 A5 */	bl func_800D5D3C
/* 8008D79C 0008A37C  80 01 00 0C */	lwz r0, 0xc(r1)
/* 8008D7A0 0008A380  38 21 00 08 */	addi r1, r1, 8
/* 8008D7A4 0008A384  7C 08 03 A6 */	mtlr r0
/* 8008D7A8 0008A388  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

void func_8008D7AC(void)
{
    return;
}

#pragma push
asm unk_t func_8008D7B0()
{ // clang-format off
    nofralloc
/* 8008D7B0 0008A390  7C 08 02 A6 */	mflr r0
/* 8008D7B4 0008A394  90 01 00 04 */	stw r0, 4(r1)
/* 8008D7B8 0008A398  94 21 FF F8 */	stwu r1, -8(r1)
/* 8008D7BC 0008A39C  48 04 87 5D */	bl func_800D5F18
/* 8008D7C0 0008A3A0  80 01 00 0C */	lwz r0, 0xc(r1)
/* 8008D7C4 0008A3A4  38 21 00 08 */	addi r1, r1, 8
/* 8008D7C8 0008A3A8  7C 08 03 A6 */	mtlr r0
/* 8008D7CC 0008A3AC  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

#pragma push
asm unk_t func_8008D7D0()
{ // clang-format off
    nofralloc
/* 8008D7D0 0008A3B0  7C 08 02 A6 */	mflr r0
/* 8008D7D4 0008A3B4  90 01 00 04 */	stw r0, 4(r1)
/* 8008D7D8 0008A3B8  94 21 FF F8 */	stwu r1, -8(r1)
/* 8008D7DC 0008A3BC  48 04 87 5D */	bl func_800D5F38
/* 8008D7E0 0008A3C0  80 01 00 0C */	lwz r0, 0xc(r1)
/* 8008D7E4 0008A3C4  38 21 00 08 */	addi r1, r1, 8
/* 8008D7E8 0008A3C8  7C 08 03 A6 */	mtlr r0
/* 8008D7EC 0008A3CC  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

extern f32 const lbl_804D84D0;
extern f32 const lbl_804D84D4;
extern f32 const lbl_804D84D8;
extern f64 const lbl_804D84E0;
extern unk_t func_8007AC68();

#pragma push
asm f32 func_8008D7F0(Fighter* fp)
{ // clang-format off
    nofralloc
/* 8008D7F0 0008A3D0  7C 08 02 A6 */	mflr r0
/* 8008D7F4 0008A3D4  90 01 00 04 */	stw r0, 4(r1)
/* 8008D7F8 0008A3D8  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 8008D7FC 0008A3DC  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 8008D800 0008A3E0  7C 7F 1B 78 */	mr r31, r3
/* 8008D804 0008A3E4  80 63 18 48 */	lwz r3, 0x1848(r3)
/* 8008D808 0008A3E8  2C 03 01 69 */	cmpwi r3, 0x169
/* 8008D80C 0008A3EC  41 82 00 50 */	beq lbl_8008D85C
/* 8008D810 0008A3F0  4B FE D4 59 */	bl func_8007AC68
/* 8008D814 0008A3F4  2C 03 00 00 */	cmpwi r3, 0
/* 8008D818 0008A3F8  41 82 00 18 */	beq lbl_8008D830
/* 8008D81C 0008A3FC  38 00 00 01 */	li r0, 1
/* 8008D820 0008A400  98 1F 23 5A */	stb r0, 0x235a(r31)
/* 8008D824 0008A404  80 6D AE B4 */	lwz r3, p_ftCommonData(r13)
/* 8008D828 0008A408  80 03 07 F0 */	lwz r0, 0x7f0(r3)
/* 8008D82C 0008A40C  98 1F 23 5B */	stb r0, 0x235b(r31)
lbl_8008D830:
/* 8008D830 0008A410  80 7F 18 48 */	lwz r3, 0x1848(r31)
/* 8008D834 0008A414  3C 00 43 30 */	lis r0, 0x4330
/* 8008D838 0008A418  C8 22 8B 00 */	lfd f1, lbl_804D84E0(r2)
/* 8008D83C 0008A41C  6C 63 80 00 */	xoris r3, r3, 0x8000
/* 8008D840 0008A420  C0 42 8A F0 */	lfs f2, lbl_804D84D0(r2)
/* 8008D844 0008A424  90 61 00 14 */	stw r3, 0x14(r1)
/* 8008D848 0008A428  90 01 00 10 */	stw r0, 0x10(r1)
/* 8008D84C 0008A42C  C8 01 00 10 */	lfd f0, 0x10(r1)
/* 8008D850 0008A430  EC 00 08 28 */	fsubs f0, f0, f1
/* 8008D854 0008A434  EC 22 00 32 */	fmuls f1, f2, f0
/* 8008D858 0008A438  48 00 00 6C */	b lbl_8008D8C4
lbl_8008D85C:
/* 8008D85C 0008A43C  80 1F 00 E0 */	lwz r0, 0xe0(r31)
/* 8008D860 0008A440  2C 00 00 01 */	cmpwi r0, 1
/* 8008D864 0008A444  40 82 00 10 */	bne lbl_8008D874
/* 8008D868 0008A448  80 6D AE B4 */	lwz r3, p_ftCommonData(r13)
/* 8008D86C 0008A44C  C0 23 01 44 */	lfs f1, 0x144(r3)
/* 8008D870 0008A450  48 00 00 54 */	b lbl_8008D8C4
lbl_8008D874:
/* 8008D874 0008A454  80 6D AE B4 */	lwz r3, p_ftCommonData(r13)
/* 8008D878 0008A458  C0 63 01 4C */	lfs f3, 0x14c(r3)
/* 8008D87C 0008A45C  FC 01 18 40 */	fcmpo cr0, f1, f3
/* 8008D880 0008A460  40 80 00 0C */	bge lbl_8008D88C
/* 8008D884 0008A464  C0 22 8A F4 */	lfs f1, lbl_804D84D4(r2)
/* 8008D888 0008A468  48 00 00 3C */	b lbl_8008D8C4
lbl_8008D88C:
/* 8008D88C 0008A46C  C0 03 01 50 */	lfs f0, 0x150(r3)
/* 8008D890 0008A470  EC 41 18 28 */	fsubs f2, f1, f3
/* 8008D894 0008A474  C0 83 01 48 */	lfs f4, 0x148(r3)
/* 8008D898 0008A478  EC 20 18 28 */	fsubs f1, f0, f3
/* 8008D89C 0008A47C  C0 62 8A F0 */	lfs f3, lbl_804D84D0(r2)
/* 8008D8A0 0008A480  C0 02 8A F8 */	lfs f0, lbl_804D84D8(r2)
/* 8008D8A4 0008A484  EC A3 01 32 */	fmuls f5, f3, f4
/* 8008D8A8 0008A488  EC 22 08 24 */	fdivs f1, f2, f1
/* 8008D8AC 0008A48C  EC 04 00 7A */	fmadds f0, f4, f1, f0
/* 8008D8B0 0008A490  EC 03 00 32 */	fmuls f0, f3, f0
/* 8008D8B4 0008A494  FC 00 28 40 */	fcmpo cr0, f0, f5
/* 8008D8B8 0008A498  FC 20 00 90 */	fmr f1, f0
/* 8008D8BC 0008A49C  40 81 00 08 */	ble lbl_8008D8C4
/* 8008D8C0 0008A4A0  FC 20 28 90 */	fmr f1, f5
lbl_8008D8C4:
/* 8008D8C4 0008A4A4  80 01 00 24 */	lwz r0, 0x24(r1)
/* 8008D8C8 0008A4A8  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 8008D8CC 0008A4AC  38 21 00 20 */	addi r1, r1, 0x20
/* 8008D8D0 0008A4B0  7C 08 03 A6 */	mtlr r0
/* 8008D8D4 0008A4B4  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

#pragma push
asm f32 scaleBy154_8008D8D8(f32 force)
{ // clang-format off
    nofralloc
/* 8008D8D8 0008A4B8  80 6D AE B4 */	lwz r3, p_ftCommonData(r13)
/* 8008D8DC 0008A4BC  C0 03 01 54 */	lfs f0, 0x154(r3)
/* 8008D8E0 0008A4C0  EC 21 00 32 */	fmuls f1, f1, f0
/* 8008D8E4 0008A4C4  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

#pragma push
asm BOOL func_8008D8E8(f32 force)
{ // clang-format off
    nofralloc
/* 8008D8E8 0008A4C8  80 6D AE B4 */	lwz r3, p_ftCommonData(r13)
/* 8008D8EC 0008A4CC  C0 03 01 58 */	lfs f0, 0x158(r3)
/* 8008D8F0 0008A4D0  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8008D8F4 0008A4D4  40 80 00 0C */	bge lbl_8008D900
/* 8008D8F8 0008A4D8  38 60 00 00 */	li r3, 0
/* 8008D8FC 0008A4DC  4E 80 00 20 */	blr 
lbl_8008D900:
/* 8008D900 0008A4E0  C0 03 01 5C */	lfs f0, 0x15c(r3)
/* 8008D904 0008A4E4  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8008D908 0008A4E8  40 80 00 0C */	bge lbl_8008D914
/* 8008D90C 0008A4EC  38 60 00 01 */	li r3, 1
/* 8008D910 0008A4F0  4E 80 00 20 */	blr 
lbl_8008D914:
/* 8008D914 0008A4F4  C0 03 01 60 */	lfs f0, 0x160(r3)
/* 8008D918 0008A4F8  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8008D91C 0008A4FC  40 80 00 0C */	bge lbl_8008D928
/* 8008D920 0008A500  38 60 00 02 */	li r3, 2
/* 8008D924 0008A504  4E 80 00 20 */	blr 
lbl_8008D928:
/* 8008D928 0008A508  38 60 00 03 */	li r3, 3
/* 8008D92C 0008A50C  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

extern unk_t func_800CF594();

#pragma push
asm unk_t func_8008D930()
{ // clang-format off
    nofralloc
/* 8008D930 0008A510  7C 08 02 A6 */	mflr r0
/* 8008D934 0008A514  90 01 00 04 */	stw r0, 4(r1)
/* 8008D938 0008A518  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 8008D93C 0008A51C  93 E1 00 14 */	stw r31, 0x14(r1)
/* 8008D940 0008A520  7C 7F 1B 78 */	mr r31, r3
/* 8008D944 0008A524  C0 02 8A F4 */	lfs f0, lbl_804D84D4(r2)
/* 8008D948 0008A528  C0 23 18 50 */	lfs f1, 0x1850(r3)
/* 8008D94C 0008A52C  FC 01 00 00 */	fcmpu cr0, f1, f0
/* 8008D950 0008A530  41 82 00 E8 */	beq lbl_8008DA38
/* 8008D954 0008A534  80 1F 00 10 */	lwz r0, 0x10(r31)
/* 8008D958 0008A538  2C 00 00 27 */	cmpwi r0, 0x27
/* 8008D95C 0008A53C  41 82 00 0C */	beq lbl_8008D968
/* 8008D960 0008A540  2C 00 00 28 */	cmpwi r0, 0x28
/* 8008D964 0008A544  40 82 00 18 */	bne lbl_8008D97C
lbl_8008D968:
/* 8008D968 0008A548  80 6D AE B4 */	lwz r3, p_ftCommonData(r13)
/* 8008D96C 0008A54C  C0 3F 18 50 */	lfs f1, 0x1850(r31)
/* 8008D970 0008A550  C0 03 01 24 */	lfs f0, 0x124(r3)
/* 8008D974 0008A554  EC 01 00 32 */	fmuls f0, f1, f0
/* 8008D978 0008A558  D0 1F 18 50 */	stfs f0, 0x1850(r31)
lbl_8008D97C:
/* 8008D97C 0008A55C  80 1F 00 10 */	lwz r0, 0x10(r31)
/* 8008D980 0008A560  2C 00 01 45 */	cmpwi r0, 0x145
/* 8008D984 0008A564  40 82 00 18 */	bne lbl_8008D99C
/* 8008D988 0008A568  80 6D AE B4 */	lwz r3, p_ftCommonData(r13)
/* 8008D98C 0008A56C  C0 3F 18 50 */	lfs f1, 0x1850(r31)
/* 8008D990 0008A570  C0 03 07 18 */	lfs f0, 0x718(r3)
/* 8008D994 0008A574  EC 01 00 32 */	fmuls f0, f1, f0
/* 8008D998 0008A578  D0 1F 18 50 */	stfs f0, 0x1850(r31)
lbl_8008D99C:
/* 8008D99C 0008A57C  80 1F 21 14 */	lwz r0, 0x2114(r31)
/* 8008D9A0 0008A580  2C 00 00 02 */	cmpwi r0, 2
/* 8008D9A4 0008A584  40 82 00 18 */	bne lbl_8008D9BC
/* 8008D9A8 0008A588  80 6D AE B4 */	lwz r3, p_ftCommonData(r13)
/* 8008D9AC 0008A58C  C0 3F 18 50 */	lfs f1, 0x1850(r31)
/* 8008D9B0 0008A590  C0 03 07 C4 */	lfs f0, 0x7c4(r3)
/* 8008D9B4 0008A594  EC 01 00 32 */	fmuls f0, f1, f0
/* 8008D9B8 0008A598  D0 1F 18 50 */	stfs f0, 0x1850(r31)
lbl_8008D9BC:
/* 8008D9BC 0008A59C  C0 02 8A F8 */	lfs f0, lbl_804D84D8(r2)
/* 8008D9C0 0008A5A0  C0 5F 00 38 */	lfs f2, 0x38(r31)
/* 8008D9C4 0008A5A4  FC 00 10 00 */	fcmpu cr0, f0, f2
/* 8008D9C8 0008A5A8  41 82 00 18 */	beq lbl_8008D9E0
/* 8008D9CC 0008A5AC  80 6D AE 84 */	lwz r3, lbl_804D6524(r13)
/* 8008D9D0 0008A5B0  C0 3F 18 50 */	lfs f1, 0x1850(r31)
/* 8008D9D4 0008A5B4  C0 63 00 00 */	lfs f3, 0(r3)
/* 8008D9D8 0008A5B8  48 04 1B BD */	bl func_800CF594
/* 8008D9DC 0008A5BC  D0 3F 18 50 */	stfs f1, 0x1850(r31)
lbl_8008D9E0:
/* 8008D9E0 0008A5C0  C0 1F 18 B0 */	lfs f0, 0x18b0(r31)
/* 8008D9E4 0008A5C4  C0 3F 18 B4 */	lfs f1, 0x18b4(r31)
/* 8008D9E8 0008A5C8  FC 00 08 40 */	fcmpo cr0, f0, f1
/* 8008D9EC 0008A5CC  40 81 00 08 */	ble lbl_8008D9F4
/* 8008D9F0 0008A5D0  48 00 00 08 */	b lbl_8008D9F8
lbl_8008D9F4:
/* 8008D9F4 0008A5D4  FC 00 08 90 */	fmr f0, f1
lbl_8008D9F8:
/* 8008D9F8 0008A5D8  88 1F 22 23 */	lbz r0, 0x2223(r31)
/* 8008D9FC 0008A5DC  FC 20 00 90 */	fmr f1, f0
/* 8008DA00 0008A5E0  54 00 07 FF */	clrlwi. r0, r0, 0x1f
/* 8008DA04 0008A5E4  41 82 00 10 */	beq lbl_8008DA14
/* 8008DA08 0008A5E8  80 6D AE B4 */	lwz r3, p_ftCommonData(r13)
/* 8008DA0C 0008A5EC  C0 03 06 F0 */	lfs f0, 0x6f0(r3)
/* 8008DA10 0008A5F0  EC 21 00 2A */	fadds f1, f1, f0
lbl_8008DA14:
/* 8008DA14 0008A5F4  C0 1F 18 50 */	lfs f0, 0x1850(r31)
/* 8008DA18 0008A5F8  EC 00 08 28 */	fsubs f0, f0, f1
/* 8008DA1C 0008A5FC  D0 1F 18 50 */	stfs f0, 0x1850(r31)
/* 8008DA20 0008A600  80 6D AE B4 */	lwz r3, p_ftCommonData(r13)
/* 8008DA24 0008A604  C0 1F 18 50 */	lfs f0, 0x1850(r31)
/* 8008DA28 0008A608  C0 23 01 04 */	lfs f1, 0x104(r3)
/* 8008DA2C 0008A60C  FC 00 08 40 */	fcmpo cr0, f0, f1
/* 8008DA30 0008A610  40 80 00 08 */	bge lbl_8008DA38
/* 8008DA34 0008A614  D0 3F 18 50 */	stfs f1, 0x1850(r31)
lbl_8008DA38:
/* 8008DA38 0008A618  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 8008DA3C 0008A61C  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 8008DA40 0008A620  38 21 00 18 */	addi r1, r1, 0x18
/* 8008DA44 0008A624  7C 08 03 A6 */	mtlr r0
/* 8008DA48 0008A628  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

#pragma push
asm unk_t func_8008DA4C()
{ // clang-format off
    nofralloc
/* 8008DA4C 0008A62C  7C 08 02 A6 */	mflr r0
/* 8008DA50 0008A630  90 01 00 04 */	stw r0, 4(r1)
/* 8008DA54 0008A634  94 21 FF F8 */	stwu r1, -8(r1)
/* 8008DA58 0008A638  80 63 00 2C */	lwz r3, 0x2c(r3)
/* 8008DA5C 0008A63C  C0 02 8A F4 */	lfs f0, lbl_804D84D4(r2)
/* 8008DA60 0008A640  C0 23 18 38 */	lfs f1, 0x1838(r3)
/* 8008DA64 0008A644  FC 01 00 00 */	fcmpu cr0, f1, f0
/* 8008DA68 0008A648  41 82 00 94 */	beq lbl_8008DAFC
/* 8008DA6C 0008A64C  2C 04 00 05 */	cmpwi r4, 5
/* 8008DA70 0008A650  41 82 00 54 */	beq lbl_8008DAC4
/* 8008DA74 0008A654  40 80 00 1C */	bge lbl_8008DA90
/* 8008DA78 0008A658  2C 04 00 02 */	cmpwi r4, 2
/* 8008DA7C 0008A65C  41 82 00 34 */	beq lbl_8008DAB0
/* 8008DA80 0008A660  40 80 00 6C */	bge lbl_8008DAEC
/* 8008DA84 0008A664  2C 04 00 01 */	cmpwi r4, 1
/* 8008DA88 0008A668  40 80 00 14 */	bge lbl_8008DA9C
/* 8008DA8C 0008A66C  48 00 00 60 */	b lbl_8008DAEC
lbl_8008DA90:
/* 8008DA90 0008A670  2C 04 00 0D */	cmpwi r4, 0xd
/* 8008DA94 0008A674  41 82 00 44 */	beq lbl_8008DAD8
/* 8008DA98 0008A678  48 00 00 54 */	b lbl_8008DAEC
lbl_8008DA9C:
/* 8008DA9C 0008A67C  38 85 00 0B */	addi r4, r5, 0xb
/* 8008DAA0 0008A680  38 A0 00 00 */	li r5, 0
/* 8008DAA4 0008A684  48 03 25 2D */	bl func_800BFFD0
/* 8008DAA8 0008A688  7C 60 1B 78 */	mr r0, r3
/* 8008DAAC 0008A68C  48 00 00 50 */	b lbl_8008DAFC
lbl_8008DAB0:
/* 8008DAB0 0008A690  38 85 00 0F */	addi r4, r5, 0xf
/* 8008DAB4 0008A694  38 A0 00 00 */	li r5, 0
/* 8008DAB8 0008A698  48 03 25 19 */	bl func_800BFFD0
/* 8008DABC 0008A69C  7C 60 1B 78 */	mr r0, r3
/* 8008DAC0 0008A6A0  48 00 00 3C */	b lbl_8008DAFC
lbl_8008DAC4:
/* 8008DAC4 0008A6A4  38 85 00 1F */	addi r4, r5, 0x1f
/* 8008DAC8 0008A6A8  38 A0 00 00 */	li r5, 0
/* 8008DACC 0008A6AC  48 03 25 05 */	bl func_800BFFD0
/* 8008DAD0 0008A6B0  7C 60 1B 78 */	mr r0, r3
/* 8008DAD4 0008A6B4  48 00 00 28 */	b lbl_8008DAFC
lbl_8008DAD8:
/* 8008DAD8 0008A6B8  38 85 00 23 */	addi r4, r5, 0x23
/* 8008DADC 0008A6BC  38 A0 00 00 */	li r5, 0
/* 8008DAE0 0008A6C0  48 03 24 F1 */	bl func_800BFFD0
/* 8008DAE4 0008A6C4  7C 60 1B 78 */	mr r0, r3
/* 8008DAE8 0008A6C8  48 00 00 14 */	b lbl_8008DAFC
lbl_8008DAEC:
/* 8008DAEC 0008A6CC  38 80 00 04 */	li r4, 4
/* 8008DAF0 0008A6D0  38 A0 00 00 */	li r5, 0
/* 8008DAF4 0008A6D4  48 03 24 DD */	bl func_800BFFD0
/* 8008DAF8 0008A6D8  7C 60 1B 78 */	mr r0, r3
lbl_8008DAFC:
/* 8008DAFC 0008A6DC  7C 03 03 78 */	mr r3, r0
/* 8008DB00 0008A6E0  80 01 00 0C */	lwz r0, 0xc(r1)
/* 8008DB04 0008A6E4  38 21 00 08 */	addi r1, r1, 8
/* 8008DB08 0008A6E8  7C 08 03 A6 */	mtlr r0
/* 8008DB0C 0008A6EC  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

#pragma push
asm unk_t func_8008DB10()
{ // clang-format off
    nofralloc
/* 8008DB10 0008A6F0  7C 08 02 A6 */	mflr r0
/* 8008DB14 0008A6F4  90 01 00 04 */	stw r0, 4(r1)
/* 8008DB18 0008A6F8  94 21 FF F8 */	stwu r1, -8(r1)
/* 8008DB1C 0008A6FC  80 63 00 2C */	lwz r3, 0x2c(r3)
/* 8008DB20 0008A700  C0 02 8A F4 */	lfs f0, lbl_804D84D4(r2)
/* 8008DB24 0008A704  C0 43 18 38 */	lfs f2, 0x1838(r3)
/* 8008DB28 0008A708  FC 02 00 00 */	fcmpu cr0, f2, f0
/* 8008DB2C 0008A70C  41 82 00 D0 */	beq lbl_8008DBFC
/* 8008DB30 0008A710  2C 04 00 05 */	cmpwi r4, 5
/* 8008DB34 0008A714  41 82 00 6C */	beq lbl_8008DBA0
/* 8008DB38 0008A718  40 80 00 1C */	bge lbl_8008DB54
/* 8008DB3C 0008A71C  2C 04 00 02 */	cmpwi r4, 2
/* 8008DB40 0008A720  41 82 00 40 */	beq lbl_8008DB80
/* 8008DB44 0008A724  40 80 00 9C */	bge lbl_8008DBE0
/* 8008DB48 0008A728  2C 04 00 01 */	cmpwi r4, 1
/* 8008DB4C 0008A72C  40 80 00 14 */	bge lbl_8008DB60
/* 8008DB50 0008A730  48 00 00 90 */	b lbl_8008DBE0
lbl_8008DB54:
/* 8008DB54 0008A734  2C 04 00 0D */	cmpwi r4, 0xd
/* 8008DB58 0008A738  41 82 00 68 */	beq lbl_8008DBC0
/* 8008DB5C 0008A73C  48 00 00 84 */	b lbl_8008DBE0
lbl_8008DB60:
/* 8008DB60 0008A740  80 6D AE B4 */	lwz r3, p_ftCommonData(r13)
/* 8008DB64 0008A744  C0 03 01 7C */	lfs f0, 0x17c(r3)
/* 8008DB68 0008A748  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8008DB6C 0008A74C  40 81 00 90 */	ble lbl_8008DBFC
/* 8008DB70 0008A750  38 60 00 03 */	li r3, 3
/* 8008DB74 0008A754  38 80 00 00 */	li r4, 0
/* 8008DB78 0008A758  4B F9 40 D1 */	bl func_80021C48
/* 8008DB7C 0008A75C  48 00 00 80 */	b lbl_8008DBFC
lbl_8008DB80:
/* 8008DB80 0008A760  80 6D AE B4 */	lwz r3, p_ftCommonData(r13)
/* 8008DB84 0008A764  C0 03 01 80 */	lfs f0, 0x180(r3)
/* 8008DB88 0008A768  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8008DB8C 0008A76C  40 81 00 70 */	ble lbl_8008DBFC
/* 8008DB90 0008A770  38 60 00 04 */	li r3, 4
/* 8008DB94 0008A774  38 80 00 00 */	li r4, 0
/* 8008DB98 0008A778  4B F9 40 B1 */	bl func_80021C48
/* 8008DB9C 0008A77C  48 00 00 60 */	b lbl_8008DBFC
lbl_8008DBA0:
/* 8008DBA0 0008A780  80 6D AE B4 */	lwz r3, p_ftCommonData(r13)
/* 8008DBA4 0008A784  C0 03 01 84 */	lfs f0, 0x184(r3)
/* 8008DBA8 0008A788  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8008DBAC 0008A78C  40 81 00 50 */	ble lbl_8008DBFC
/* 8008DBB0 0008A790  38 60 00 05 */	li r3, 5
/* 8008DBB4 0008A794  38 80 00 00 */	li r4, 0
/* 8008DBB8 0008A798  4B F9 40 91 */	bl func_80021C48
/* 8008DBBC 0008A79C  48 00 00 40 */	b lbl_8008DBFC
lbl_8008DBC0:
/* 8008DBC0 0008A7A0  80 6D AE B4 */	lwz r3, p_ftCommonData(r13)
/* 8008DBC4 0008A7A4  C0 03 01 88 */	lfs f0, 0x188(r3)
/* 8008DBC8 0008A7A8  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8008DBCC 0008A7AC  40 81 00 30 */	ble lbl_8008DBFC
/* 8008DBD0 0008A7B0  38 60 00 06 */	li r3, 6
/* 8008DBD4 0008A7B4  38 80 00 00 */	li r4, 0
/* 8008DBD8 0008A7B8  4B F9 40 71 */	bl func_80021C48
/* 8008DBDC 0008A7BC  48 00 00 20 */	b lbl_8008DBFC
lbl_8008DBE0:
/* 8008DBE0 0008A7C0  80 6D AE B4 */	lwz r3, p_ftCommonData(r13)
/* 8008DBE4 0008A7C4  C0 03 01 78 */	lfs f0, 0x178(r3)
/* 8008DBE8 0008A7C8  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8008DBEC 0008A7CC  40 81 00 10 */	ble lbl_8008DBFC
/* 8008DBF0 0008A7D0  38 60 00 02 */	li r3, 2
/* 8008DBF4 0008A7D4  38 80 00 00 */	li r4, 0
/* 8008DBF8 0008A7D8  4B F9 40 51 */	bl func_80021C48
lbl_8008DBFC:
/* 8008DBFC 0008A7DC  80 01 00 0C */	lwz r0, 0xc(r1)
/* 8008DC00 0008A7E0  38 21 00 08 */	addi r1, r1, 8
/* 8008DC04 0008A7E4  7C 08 03 A6 */	mtlr r0
/* 8008DC08 0008A7E8  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

#pragma push
asm unk_t func_8008DC0C()
{ // clang-format off
    nofralloc
/* 8008DC0C 0008A7EC  80 8D AE B4 */	lwz r4, p_ftCommonData(r13)
/* 8008DC10 0008A7F0  80 A3 18 AC */	lwz r5, 0x18ac(r3)
/* 8008DC14 0008A7F4  80 04 00 FC */	lwz r0, 0xfc(r4)
/* 8008DC18 0008A7F8  7C 05 00 00 */	cmpw r5, r0
/* 8008DC1C 0008A7FC  40 80 00 10 */	bge lbl_8008DC2C
/* 8008DC20 0008A800  D0 23 00 8C */	stfs f1, 0x8c(r3)
/* 8008DC24 0008A804  D0 43 00 90 */	stfs f2, 0x90(r3)
/* 8008DC28 0008A808  4E 80 00 20 */	blr 
lbl_8008DC2C:
/* 8008DC2C 0008A80C  C0 83 00 8C */	lfs f4, 0x8c(r3)
/* 8008DC30 0008A810  C0 02 8A F4 */	lfs f0, lbl_804D84D4(r2)
/* 8008DC34 0008A814  EC 64 00 72 */	fmuls f3, f4, f1
/* 8008DC38 0008A818  C0 A3 00 90 */	lfs f5, 0x90(r3)
/* 8008DC3C 0008A81C  FC 03 00 40 */	fcmpo cr0, f3, f0
/* 8008DC40 0008A820  40 80 00 10 */	bge lbl_8008DC50
/* 8008DC44 0008A824  EC 04 08 2A */	fadds f0, f4, f1
/* 8008DC48 0008A828  D0 03 00 8C */	stfs f0, 0x8c(r3)
/* 8008DC4C 0008A82C  48 00 00 3C */	b lbl_8008DC88
lbl_8008DC50:
/* 8008DC50 0008A830  FC 04 00 40 */	fcmpo cr0, f4, f0
/* 8008DC54 0008A834  40 80 00 0C */	bge lbl_8008DC60
/* 8008DC58 0008A838  FC 60 20 50 */	fneg f3, f4
/* 8008DC5C 0008A83C  48 00 00 08 */	b lbl_8008DC64
lbl_8008DC60:
/* 8008DC60 0008A840  FC 60 20 90 */	fmr f3, f4
lbl_8008DC64:
/* 8008DC64 0008A844  C0 02 8A F4 */	lfs f0, lbl_804D84D4(r2)
/* 8008DC68 0008A848  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8008DC6C 0008A84C  40 80 00 0C */	bge lbl_8008DC78
/* 8008DC70 0008A850  FC 00 08 50 */	fneg f0, f1
/* 8008DC74 0008A854  48 00 00 08 */	b lbl_8008DC7C
lbl_8008DC78:
/* 8008DC78 0008A858  FC 00 08 90 */	fmr f0, f1
lbl_8008DC7C:
/* 8008DC7C 0008A85C  FC 00 18 40 */	fcmpo cr0, f0, f3
/* 8008DC80 0008A860  40 81 00 08 */	ble lbl_8008DC88
/* 8008DC84 0008A864  D0 23 00 8C */	stfs f1, 0x8c(r3)
lbl_8008DC88:
/* 8008DC88 0008A868  EC 25 00 B2 */	fmuls f1, f5, f2
/* 8008DC8C 0008A86C  C0 02 8A F4 */	lfs f0, lbl_804D84D4(r2)
/* 8008DC90 0008A870  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8008DC94 0008A874  40 80 00 10 */	bge lbl_8008DCA4
/* 8008DC98 0008A878  EC 05 10 2A */	fadds f0, f5, f2
/* 8008DC9C 0008A87C  D0 03 00 90 */	stfs f0, 0x90(r3)
/* 8008DCA0 0008A880  4E 80 00 20 */	blr 
lbl_8008DCA4:
/* 8008DCA4 0008A884  FC 05 00 40 */	fcmpo cr0, f5, f0
/* 8008DCA8 0008A888  40 80 00 0C */	bge lbl_8008DCB4
/* 8008DCAC 0008A88C  FC 20 28 50 */	fneg f1, f5
/* 8008DCB0 0008A890  48 00 00 08 */	b lbl_8008DCB8
lbl_8008DCB4:
/* 8008DCB4 0008A894  FC 20 28 90 */	fmr f1, f5
lbl_8008DCB8:
/* 8008DCB8 0008A898  C0 02 8A F4 */	lfs f0, lbl_804D84D4(r2)
/* 8008DCBC 0008A89C  FC 02 00 40 */	fcmpo cr0, f2, f0
/* 8008DCC0 0008A8A0  40 80 00 0C */	bge lbl_8008DCCC
/* 8008DCC4 0008A8A4  FC 00 10 50 */	fneg f0, f2
/* 8008DCC8 0008A8A8  48 00 00 08 */	b lbl_8008DCD0
lbl_8008DCCC:
/* 8008DCCC 0008A8AC  FC 00 10 90 */	fmr f0, f2
lbl_8008DCD0:
/* 8008DCD0 0008A8B0  FC 00 08 40 */	fcmpo cr0, f0, f1
/* 8008DCD4 0008A8B4  4C 81 00 20 */	blelr 
/* 8008DCD8 0008A8B8  D0 43 00 90 */	stfs f2, 0x90(r3)
/* 8008DCDC 0008A8BC  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

extern f32 lbl_804D84E8;
extern f32 lbl_804D84EC;
extern f64 lbl_804D84F0;
extern u32 lbl_803C5520[];
extern unk_t lbl_8008E4F0();
extern unk_t lbl_8008E714();
extern unk_t func_80090B60();
extern unk_t func_80030E44();
extern unk_t func_8008FCB8();
extern unk_t func_8007B6A0();
extern unk_t func_8016B014();
extern unk_t func_8032233C();
extern unk_t func_803222EC();
extern unk_t func_8008E498();
extern unk_t func_80040270();

#pragma push
asm void func_8008DCE0(HSD_GObj* fighter_gobj, s32 asid, f32)
{ // clang-format off
    nofralloc
/* 8008DCE0 0008A8C0  7C 08 02 A6 */	mflr r0
/* 8008DCE4 0008A8C4  3C A0 80 3C */	lis r5, lbl_803C5520@ha
/* 8008DCE8 0008A8C8  90 01 00 04 */	stw r0, 4(r1)
/* 8008DCEC 0008A8CC  94 21 FF 38 */	stwu r1, -0xc8(r1)
/* 8008DCF0 0008A8D0  DB E1 00 C0 */	stfd f31, 0xc0(r1)
/* 8008DCF4 0008A8D4  DB C1 00 B8 */	stfd f30, 0xb8(r1)
/* 8008DCF8 0008A8D8  DB A1 00 B0 */	stfd f29, 0xb0(r1)
/* 8008DCFC 0008A8DC  DB 81 00 A8 */	stfd f28, 0xa8(r1)
/* 8008DD00 0008A8E0  DB 61 00 A0 */	stfd f27, 0xa0(r1)
/* 8008DD04 0008A8E4  FF 60 08 90 */	fmr f27, f1
/* 8008DD08 0008A8E8  DB 41 00 98 */	stfd f26, 0x98(r1)
/* 8008DD0C 0008A8EC  DB 21 00 90 */	stfd f25, 0x90(r1)
/* 8008DD10 0008A8F0  BF 01 00 70 */	stmw r24, 0x70(r1)
/* 8008DD14 0008A8F4  3B 24 00 00 */	addi r25, r4, 0
/* 8008DD18 0008A8F8  7C 78 1B 78 */	mr r24, r3
/* 8008DD1C 0008A8FC  3B E5 55 20 */	addi r31, r5, lbl_803C5520@l
/* 8008DD20 0008A900  3B 60 00 01 */	li r27, 1
/* 8008DD24 0008A904  83 A3 00 2C */	lwz r29, 0x2c(r3)
/* 8008DD28 0008A908  C0 1D 18 38 */	lfs f0, 0x1838(r29)
/* 8008DD2C 0008A90C  7F A3 EB 78 */	mr r3, r29
/* 8008DD30 0008A910  C3 9D 18 50 */	lfs f28, 0x1850(r29)
/* 8008DD34 0008A914  FC 00 00 1E */	fctiwz f0, f0
/* 8008DD38 0008A918  D8 01 00 68 */	stfd f0, 0x68(r1)
/* 8008DD3C 0008A91C  80 81 00 6C */	lwz r4, 0x6c(r1)
/* 8008DD40 0008A920  4B FD F0 65 */	bl Fighter_8006CDA4
/* 8008DD44 0008A924  D3 9D 18 E0 */	stfs f28, 0x18e0(r29)
/* 8008DD48 0008A928  FC 20 E0 90 */	fmr f1, f28
/* 8008DD4C 0008A92C  88 9D 22 1F */	lbz r4, 0x221f(r29)
/* 8008DD50 0008A930  88 7D 00 0C */	lbz r3, 0xc(r29)
/* 8008DD54 0008A934  54 84 EF FE */	rlwinm r4, r4, 0x1d, 0x1f, 0x1f
/* 8008DD58 0008A938  4B FB 25 19 */	bl func_80040270
/* 8008DD5C 0008A93C  80 6D AE B4 */	lwz r3, p_ftCommonData(r13)
/* 8008DD60 0008A940  3C 00 43 30 */	lis r0, 0x4330
/* 8008DD64 0008A944  C8 22 8B 00 */	lfd f1, lbl_804D84E0(r2)
/* 8008DD68 0008A948  C0 03 01 54 */	lfs f0, 0x154(r3)
/* 8008DD6C 0008A94C  EF DC 00 32 */	fmuls f30, f28, f0
/* 8008DD70 0008A950  FC 00 F0 1E */	fctiwz f0, f30
/* 8008DD74 0008A954  D8 01 00 60 */	stfd f0, 0x60(r1)
/* 8008DD78 0008A958  80 61 00 64 */	lwz r3, 0x64(r1)
/* 8008DD7C 0008A95C  6C 63 80 00 */	xoris r3, r3, 0x8000
/* 8008DD80 0008A960  90 61 00 5C */	stw r3, 0x5c(r1)
/* 8008DD84 0008A964  90 01 00 58 */	stw r0, 0x58(r1)
/* 8008DD88 0008A968  C8 01 00 58 */	lfd f0, 0x58(r1)
/* 8008DD8C 0008A96C  EC 00 08 28 */	fsubs f0, f0, f1
/* 8008DD90 0008A970  D0 1D 23 40 */	stfs f0, 0x2340(r29)
/* 8008DD94 0008A974  C0 3D 23 40 */	lfs f1, 0x2340(r29)
/* 8008DD98 0008A978  C0 02 8A F4 */	lfs f0, lbl_804D84D4(r2)
/* 8008DD9C 0008A97C  FC 01 00 00 */	fcmpu cr0, f1, f0
/* 8008DDA0 0008A980  40 82 00 0C */	bne lbl_8008DDAC
/* 8008DDA4 0008A984  C0 02 8A F8 */	lfs f0, lbl_804D84D8(r2)
/* 8008DDA8 0008A988  D0 1D 23 40 */	stfs f0, 0x2340(r29)
lbl_8008DDAC:
/* 8008DDAC 0008A98C  80 6D AE B4 */	lwz r3, p_ftCommonData(r13)
/* 8008DDB0 0008A990  C0 03 01 58 */	lfs f0, 0x158(r3)
/* 8008DDB4 0008A994  FC 1E 00 40 */	fcmpo cr0, f30, f0
/* 8008DDB8 0008A998  40 80 00 0C */	bge lbl_8008DDC4
/* 8008DDBC 0008A99C  3B C0 00 00 */	li r30, 0
/* 8008DDC0 0008A9A0  48 00 00 30 */	b lbl_8008DDF0
lbl_8008DDC4:
/* 8008DDC4 0008A9A4  C0 03 01 5C */	lfs f0, 0x15c(r3)
/* 8008DDC8 0008A9A8  FC 1E 00 40 */	fcmpo cr0, f30, f0
/* 8008DDCC 0008A9AC  40 80 00 0C */	bge lbl_8008DDD8
/* 8008DDD0 0008A9B0  3B C0 00 01 */	li r30, 1
/* 8008DDD4 0008A9B4  48 00 00 1C */	b lbl_8008DDF0
lbl_8008DDD8:
/* 8008DDD8 0008A9B8  C0 03 01 60 */	lfs f0, 0x160(r3)
/* 8008DDDC 0008A9BC  FC 1E 00 40 */	fcmpo cr0, f30, f0
/* 8008DDE0 0008A9C0  40 80 00 0C */	bge lbl_8008DDEC
/* 8008DDE4 0008A9C4  3B C0 00 02 */	li r30, 2
/* 8008DDE8 0008A9C8  48 00 00 08 */	b lbl_8008DDF0
lbl_8008DDEC:
/* 8008DDEC 0008A9CC  3B C0 00 03 */	li r30, 3
lbl_8008DDF0:
/* 8008DDF0 0008A9D0  2C 19 FF FF */	cmpwi r25, -1
/* 8008DDF4 0008A9D4  3B 9E 00 00 */	addi r28, r30, 0
/* 8008DDF8 0008A9D8  41 82 00 08 */	beq lbl_8008DE00
/* 8008DDFC 0008A9DC  3B 80 00 03 */	li r28, 3
lbl_8008DE00:
/* 8008DE00 0008A9E0  C0 03 01 00 */	lfs f0, 0x100(r3)
/* 8008DE04 0008A9E4  38 00 00 00 */	li r0, 0
/* 8008DE08 0008A9E8  FC 20 E0 90 */	fmr f1, f28
/* 8008DE0C 0008A9EC  7F A3 EB 78 */	mr r3, r29
/* 8008DE10 0008A9F0  98 1D 23 5A */	stb r0, 0x235a(r29)
/* 8008DE14 0008A9F4  EF FC 00 32 */	fmuls f31, f28, f0
/* 8008DE18 0008A9F8  C0 02 8A F4 */	lfs f0, lbl_804D84D4(r2)
/* 8008DE1C 0008A9FC  D0 1D 23 54 */	stfs f0, 0x2354(r29)
/* 8008DE20 0008AA00  4B FF F9 D1 */	bl func_8008D7F0
/* 8008DE24 0008AA04  2C 1E 00 02 */	cmpwi r30, 2
/* 8008DE28 0008AA08  FF A0 08 90 */	fmr f29, f1
/* 8008DE2C 0008AA0C  41 80 00 70 */	blt lbl_8008DE9C
/* 8008DE30 0008AA10  80 1D 18 60 */	lwz r0, 0x1860(r29)
/* 8008DE34 0008AA14  28 00 00 05 */	cmplwi r0, 5
/* 8008DE38 0008AA18  40 82 00 64 */	bne lbl_8008DE9C
/* 8008DE3C 0008AA1C  C0 22 8B 08 */	lfs f1, lbl_804D84E8(r2)
/* 8008DE40 0008AA20  48 29 84 01 */	bl cosf
/* 8008DE44 0008AA24  FF 40 08 90 */	fmr f26, f1
/* 8008DE48 0008AA28  FC 20 E8 90 */	fmr f1, f29
/* 8008DE4C 0008AA2C  48 29 83 F5 */	bl cosf
/* 8008DE50 0008AA30  C0 02 8B 08 */	lfs f0, lbl_804D84E8(r2)
/* 8008DE54 0008AA34  EF 21 D0 2A */	fadds f25, f1, f26
/* 8008DE58 0008AA38  FC 20 00 90 */	fmr f1, f0
/* 8008DE5C 0008AA3C  48 29 85 79 */	bl sinf
/* 8008DE60 0008AA40  FF 40 08 90 */	fmr f26, f1
/* 8008DE64 0008AA44  FC 20 E8 90 */	fmr f1, f29
/* 8008DE68 0008AA48  48 29 85 6D */	bl sinf
/* 8008DE6C 0008AA4C  EC 21 D0 2A */	fadds f1, f1, f26
/* 8008DE70 0008AA50  C0 02 8B 0C */	lfs f0, lbl_804D84EC(r2)
/* 8008DE74 0008AA54  EC 41 00 72 */	fmuls f2, f1, f1
/* 8008DE78 0008AA58  EC 59 16 7A */	fmadds f2, f25, f25, f2
/* 8008DE7C 0008AA5C  FC 02 00 40 */	fcmpo cr0, f2, f0
/* 8008DE80 0008AA60  4C 40 13 82 */	cror 2, 0, 2
/* 8008DE84 0008AA64  40 82 00 0C */	bne lbl_8008DE90
/* 8008DE88 0008AA68  C0 22 8A F4 */	lfs f1, lbl_804D84D4(r2)
/* 8008DE8C 0008AA6C  48 00 00 0C */	b lbl_8008DE98
lbl_8008DE90:
/* 8008DE90 0008AA70  FC 40 C8 90 */	fmr f2, f25
/* 8008DE94 0008AA74  4B F9 4D 9D */	bl atan2f
lbl_8008DE98:
/* 8008DE98 0008AA78  FF A0 08 90 */	fmr f29, f1
lbl_8008DE9C:
/* 8008DE9C 0008AA7C  FC 20 E8 90 */	fmr f1, f29
/* 8008DEA0 0008AA80  48 29 83 A1 */	bl cosf
/* 8008DEA4 0008AA84  EF 3F 00 72 */	fmuls f25, f31, f1
/* 8008DEA8 0008AA88  FC 20 E8 90 */	fmr f1, f29
/* 8008DEAC 0008AA8C  48 29 85 29 */	bl sinf
/* 8008DEB0 0008AA90  C0 1D 18 44 */	lfs f0, 0x1844(r29)
/* 8008DEB4 0008AA94  EF 5F 00 72 */	fmuls f26, f31, f1
/* 8008DEB8 0008AA98  D0 1D 00 2C */	stfs f0, 0x2c(r29)
/* 8008DEBC 0008AA9C  80 1D 00 E0 */	lwz r0, 0xe0(r29)
/* 8008DEC0 0008AAA0  2C 00 00 01 */	cmpwi r0, 1
/* 8008DEC4 0008AAA4  40 82 00 74 */	bne lbl_8008DF38
/* 8008DEC8 0008AAA8  1C 7C 00 0C */	mulli r3, r28, 0xc
/* 8008DECC 0008AAAC  80 1D 18 4C */	lwz r0, 0x184c(r29)
/* 8008DED0 0008AAB0  7C 7F 1A 14 */	add r3, r31, r3
/* 8008DED4 0008AAB4  54 00 10 3A */	slwi r0, r0, 2
/* 8008DED8 0008AAB8  7C 63 02 14 */	add r3, r3, r0
/* 8008DEDC 0008AABC  83 E3 00 30 */	lwz r31, 0x30(r3)
/* 8008DEE0 0008AAC0  7F A3 EB 78 */	mr r3, r29
/* 8008DEE4 0008AAC4  48 00 05 B5 */	bl func_8008E498
/* 8008DEE8 0008AAC8  2C 03 00 00 */	cmpwi r3, 0
/* 8008DEEC 0008AACC  41 82 00 28 */	beq lbl_8008DF14
/* 8008DEF0 0008AAD0  80 6D AE B4 */	lwz r3, p_ftCommonData(r13)
/* 8008DEF4 0008AAD4  FC 20 E8 90 */	fmr f1, f29
/* 8008DEF8 0008AAD8  C0 03 01 90 */	lfs f0, 0x190(r3)
/* 8008DEFC 0008AADC  EF FF 00 32 */	fmuls f31, f31, f0
/* 8008DF00 0008AAE0  48 29 83 41 */	bl cosf
/* 8008DF04 0008AAE4  EF 3F 00 72 */	fmuls f25, f31, f1
/* 8008DF08 0008AAE8  FC 20 E8 90 */	fmr f1, f29
/* 8008DF0C 0008AAEC  48 29 84 C9 */	bl sinf
/* 8008DF10 0008AAF0  EF 5F 00 72 */	fmuls f26, f31, f1
lbl_8008DF14:
/* 8008DF14 0008AAF4  FC 20 C8 50 */	fneg f1, f25
/* 8008DF18 0008AAF8  C0 1D 00 2C */	lfs f0, 0x2c(r29)
/* 8008DF1C 0008AAFC  FC 40 D0 90 */	fmr f2, f26
/* 8008DF20 0008AB00  7F A3 EB 78 */	mr r3, r29
/* 8008DF24 0008AB04  EC 21 00 32 */	fmuls f1, f1, f0
/* 8008DF28 0008AB08  4B FF FC E5 */	bl func_8008DC0C
/* 8008DF2C 0008AB0C  C0 02 8A F4 */	lfs f0, lbl_804D84D4(r2)
/* 8008DF30 0008AB10  D0 1D 00 F0 */	stfs f0, 0xf0(r29)
/* 8008DF34 0008AB14  48 00 01 74 */	b lbl_8008E0A8
lbl_8008DF38:
/* 8008DF38 0008AB18  FC 20 C8 50 */	fneg f1, f25
/* 8008DF3C 0008AB1C  C0 1D 00 2C */	lfs f0, 0x2c(r29)
/* 8008DF40 0008AB20  3B 5D 08 44 */	addi r26, r29, 0x844
/* 8008DF44 0008AB24  38 7A 00 00 */	addi r3, r26, 0
/* 8008DF48 0008AB28  EC 01 00 32 */	fmuls f0, f1, f0
/* 8008DF4C 0008AB2C  38 81 00 44 */	addi r4, r1, 0x44
/* 8008DF50 0008AB30  D0 01 00 44 */	stfs f0, 0x44(r1)
/* 8008DF54 0008AB34  D3 41 00 48 */	stfs f26, 0x48(r1)
/* 8008DF58 0008AB38  C0 02 8A F4 */	lfs f0, lbl_804D84D4(r2)
/* 8008DF5C 0008AB3C  D0 01 00 4C */	stfs f0, 0x4c(r1)
/* 8008DF60 0008AB40  4B F7 F6 C1 */	bl lbvector_Angle
/* 8008DF64 0008AB44  FF 40 08 90 */	fmr f26, f1
/* 8008DF68 0008AB48  C0 02 8B 08 */	lfs f0, lbl_804D84E8(r2)
/* 8008DF6C 0008AB4C  FC 1A 00 40 */	fcmpo cr0, f26, f0
/* 8008DF70 0008AB50  40 80 00 3C */	bge lbl_8008DFAC
/* 8008DF74 0008AB54  80 1D 18 4C */	lwz r0, 0x184c(r29)
/* 8008DF78 0008AB58  1C 7C 00 0C */	mulli r3, r28, 0xc
/* 8008DF7C 0008AB5C  54 00 10 3A */	slwi r0, r0, 2
/* 8008DF80 0008AB60  7C 03 02 14 */	add r0, r3, r0
/* 8008DF84 0008AB64  7F FF 00 2E */	lwzx r31, r31, r0
/* 8008DF88 0008AB68  7F A3 EB 78 */	mr r3, r29
/* 8008DF8C 0008AB6C  4B FE F6 49 */	bl func_8007D5D4
/* 8008DF90 0008AB70  C0 21 00 44 */	lfs f1, 0x44(r1)
/* 8008DF94 0008AB74  7F A3 EB 78 */	mr r3, r29
/* 8008DF98 0008AB78  C0 41 00 48 */	lfs f2, 0x48(r1)
/* 8008DF9C 0008AB7C  4B FF FC 71 */	bl func_8008DC0C
/* 8008DFA0 0008AB80  C0 02 8A F4 */	lfs f0, lbl_804D84D4(r2)
/* 8008DFA4 0008AB84  D0 1D 00 F0 */	stfs f0, 0xf0(r29)
/* 8008DFA8 0008AB88  48 00 01 00 */	b lbl_8008E0A8
lbl_8008DFAC:
/* 8008DFAC 0008AB8C  2C 1C 00 03 */	cmpwi r28, 3
/* 8008DFB0 0008AB90  40 82 00 BC */	bne lbl_8008E06C
/* 8008DFB4 0008AB94  7F A3 EB 78 */	mr r3, r29
/* 8008DFB8 0008AB98  4B FE F6 1D */	bl func_8007D5D4
/* 8008DFBC 0008AB9C  80 8D AE B4 */	lwz r4, p_ftCommonData(r13)
/* 8008DFC0 0008ABA0  1C 7C 00 0C */	mulli r3, r28, 0xc
/* 8008DFC4 0008ABA4  80 1D 18 4C */	lwz r0, 0x184c(r29)
/* 8008DFC8 0008ABA8  C8 22 8B 10 */	lfd f1, lbl_804D84F0(r2)
/* 8008DFCC 0008ABAC  C0 04 01 E8 */	lfs f0, 0x1e8(r4)
/* 8008DFD0 0008ABB0  54 00 10 3A */	slwi r0, r0, 2
/* 8008DFD4 0008ABB4  7C 03 02 14 */	add r0, r3, r0
/* 8008DFD8 0008ABB8  FC 01 00 2A */	fadd f0, f1, f0
/* 8008DFDC 0008ABBC  7F FF 00 2E */	lwzx r31, r31, r0
/* 8008DFE0 0008ABC0  FC 1A 00 40 */	fcmpo cr0, f26, f0
/* 8008DFE4 0008ABC4  40 81 00 6C */	ble lbl_8008E050
/* 8008DFE8 0008ABC8  C0 21 00 48 */	lfs f1, 0x48(r1)
/* 8008DFEC 0008ABCC  7F A3 EB 78 */	mr r3, r29
/* 8008DFF0 0008ABD0  C0 04 01 EC */	lfs f0, 0x1ec(r4)
/* 8008DFF4 0008ABD4  FC 40 08 50 */	fneg f2, f1
/* 8008DFF8 0008ABD8  C0 21 00 44 */	lfs f1, 0x44(r1)
/* 8008DFFC 0008ABDC  EC 42 00 32 */	fmuls f2, f2, f0
/* 8008E000 0008ABE0  4B FF FC 0D */	bl func_8008DC0C
/* 8008E004 0008ABE4  C0 02 8A F4 */	lfs f0, lbl_804D84D4(r2)
/* 8008E008 0008ABE8  3B 60 00 00 */	li r27, 0
/* 8008E00C 0008ABEC  D0 1D 00 F0 */	stfs f0, 0xf0(r29)
/* 8008E010 0008ABF0  C0 1A 00 00 */	lfs f0, 0(r26)
/* 8008E014 0008ABF4  C0 5A 00 04 */	lfs f2, 4(r26)
/* 8008E018 0008ABF8  FC 20 00 50 */	fneg f1, f0
/* 8008E01C 0008ABFC  4B F9 4C 15 */	bl atan2f
/* 8008E020 0008AC00  D0 21 00 40 */	stfs f1, 0x40(r1)
/* 8008E024 0008AC04  38 78 00 00 */	addi r3, r24, 0
/* 8008E028 0008AC08  39 01 00 40 */	addi r8, r1, 0x40
/* 8008E02C 0008AC0C  4C C6 31 82 */	crclr 6
/* 8008E030 0008AC10  80 9D 05 E8 */	lwz r4, 0x5e8(r29)
/* 8008E034 0008AC14  81 38 00 2C */	lwz r9, 0x2c(r24)
/* 8008E038 0008AC18  38 A0 00 04 */	li r5, 4
/* 8008E03C 0008AC1C  80 E4 00 00 */	lwz r7, 0(r4)
/* 8008E040 0008AC20  38 C0 04 06 */	li r6, 0x406
/* 8008E044 0008AC24  38 89 06 0C */	addi r4, r9, 0x60c
/* 8008E048 0008AC28  4B FD 96 A9 */	bl efAsync_Spawn
/* 8008E04C 0008AC2C  48 00 00 5C */	b lbl_8008E0A8
lbl_8008E050:
/* 8008E050 0008AC30  C0 21 00 44 */	lfs f1, 0x44(r1)
/* 8008E054 0008AC34  7F A3 EB 78 */	mr r3, r29
/* 8008E058 0008AC38  C0 41 00 48 */	lfs f2, 0x48(r1)
/* 8008E05C 0008AC3C  4B FF FB B1 */	bl func_8008DC0C
/* 8008E060 0008AC40  C0 02 8A F4 */	lfs f0, lbl_804D84D4(r2)
/* 8008E064 0008AC44  D0 1D 00 F0 */	stfs f0, 0xf0(r29)
/* 8008E068 0008AC48  48 00 00 40 */	b lbl_8008E0A8
lbl_8008E06C:
/* 8008E06C 0008AC4C  80 1D 18 4C */	lwz r0, 0x184c(r29)
/* 8008E070 0008AC50  1C 7C 00 0C */	mulli r3, r28, 0xc
/* 8008E074 0008AC54  C0 01 00 44 */	lfs f0, 0x44(r1)
/* 8008E078 0008AC58  54 00 10 3A */	slwi r0, r0, 2
/* 8008E07C 0008AC5C  7C 03 02 14 */	add r0, r3, r0
/* 8008E080 0008AC60  7F FF 00 2E */	lwzx r31, r31, r0
/* 8008E084 0008AC64  7F A3 EB 78 */	mr r3, r29
/* 8008E088 0008AC68  D0 1D 00 F0 */	stfs f0, 0xf0(r29)
/* 8008E08C 0008AC6C  C0 1A 00 00 */	lfs f0, 0(r26)
/* 8008E090 0008AC70  C0 5D 00 F0 */	lfs f2, 0xf0(r29)
/* 8008E094 0008AC74  FC 00 00 50 */	fneg f0, f0
/* 8008E098 0008AC78  C0 3A 00 04 */	lfs f1, 4(r26)
/* 8008E09C 0008AC7C  EC 21 00 B2 */	fmuls f1, f1, f2
/* 8008E0A0 0008AC80  EC 40 00 B2 */	fmuls f2, f0, f2
/* 8008E0A4 0008AC84  4B FF FB 69 */	bl func_8008DC0C
lbl_8008E0A8:
/* 8008E0A8 0008AC88  C0 02 8A F4 */	lfs f0, lbl_804D84D4(r2)
/* 8008E0AC 0008AC8C  2C 1C 00 03 */	cmpwi r28, 3
/* 8008E0B0 0008AC90  D0 1D 00 88 */	stfs f0, 0x88(r29)
/* 8008E0B4 0008AC94  D0 1D 00 84 */	stfs f0, 0x84(r29)
/* 8008E0B8 0008AC98  D0 1D 00 80 */	stfs f0, 0x80(r29)
/* 8008E0BC 0008AC9C  D0 1D 00 EC */	stfs f0, 0xec(r29)
/* 8008E0C0 0008ACA0  40 82 00 7C */	bne lbl_8008E13C
/* 8008E0C4 0008ACA4  80 1D 00 E0 */	lwz r0, 0xe0(r29)
/* 8008E0C8 0008ACA8  2C 00 00 01 */	cmpwi r0, 1
/* 8008E0CC 0008ACAC  40 82 00 70 */	bne lbl_8008E13C
/* 8008E0D0 0008ACB0  80 6D AE B4 */	lwz r3, p_ftCommonData(r13)
/* 8008E0D4 0008ACB4  C0 03 02 34 */	lfs f0, 0x234(r3)
/* 8008E0D8 0008ACB8  FC 1D 00 40 */	fcmpo cr0, f29, f0
/* 8008E0DC 0008ACBC  40 81 00 18 */	ble lbl_8008E0F4
/* 8008E0E0 0008ACC0  C0 03 02 38 */	lfs f0, 0x238(r3)
/* 8008E0E4 0008ACC4  FC 1D 00 40 */	fcmpo cr0, f29, f0
/* 8008E0E8 0008ACC8  40 80 00 0C */	bge lbl_8008E0F4
/* 8008E0EC 0008ACCC  3B E0 00 5A */	li r31, 0x5a
/* 8008E0F0 0008ACD0  48 00 00 4C */	b lbl_8008E13C
lbl_8008E0F4:
/* 8008E0F4 0008ACD4  80 63 02 3C */	lwz r3, 0x23c(r3)
/* 8008E0F8 0008ACD8  3C 00 43 30 */	lis r0, 0x4330
/* 8008E0FC 0008ACDC  C8 22 8B 00 */	lfd f1, lbl_804D84E0(r2)
/* 8008E100 0008ACE0  6C 63 80 00 */	xoris r3, r3, 0x8000
/* 8008E104 0008ACE4  C0 5D 18 30 */	lfs f2, 0x1830(r29)
/* 8008E108 0008ACE8  90 61 00 5C */	stw r3, 0x5c(r1)
/* 8008E10C 0008ACEC  90 01 00 58 */	stw r0, 0x58(r1)
/* 8008E110 0008ACF0  C8 01 00 58 */	lfd f0, 0x58(r1)
/* 8008E114 0008ACF4  EC 00 08 28 */	fsubs f0, f0, f1
/* 8008E118 0008ACF8  FC 02 00 40 */	fcmpo cr0, f2, f0
/* 8008E11C 0008ACFC  4C 41 13 82 */	cror 2, 1, 2
/* 8008E120 0008AD00  40 82 00 1C */	bne lbl_8008E13C
/* 8008E124 0008AD04  48 2F 24 05 */	bl HSD_Randf
/* 8008E128 0008AD08  80 6D AE B4 */	lwz r3, p_ftCommonData(r13)
/* 8008E12C 0008AD0C  C0 03 02 40 */	lfs f0, 0x240(r3)
/* 8008E130 0008AD10  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8008E134 0008AD14  40 80 00 08 */	bge lbl_8008E13C
/* 8008E138 0008AD18  3B E0 00 5B */	li r31, 0x5b
lbl_8008E13C:
/* 8008E13C 0008AD1C  2C 19 FF FF */	cmpwi r25, -1
/* 8008E140 0008AD20  41 82 00 08 */	beq lbl_8008E148
/* 8008E144 0008AD24  7F 3F CB 78 */	mr r31, r25
lbl_8008E148:
/* 8008E148 0008AD28  2C 1F 01 45 */	cmpwi r31, 0x145
/* 8008E14C 0008AD2C  41 82 00 1C */	beq lbl_8008E168
/* 8008E150 0008AD30  2C 1E 00 02 */	cmpwi r30, 2
/* 8008E154 0008AD34  41 80 00 14 */	blt lbl_8008E168
/* 8008E158 0008AD38  80 1D 18 60 */	lwz r0, 0x1860(r29)
/* 8008E15C 0008AD3C  28 00 00 05 */	cmplwi r0, 5
/* 8008E160 0008AD40  40 82 00 08 */	bne lbl_8008E168
/* 8008E164 0008AD44  3B E0 00 5A */	li r31, 0x5a
lbl_8008E168:
/* 8008E168 0008AD48  FC 20 E0 90 */	fmr f1, f28
/* 8008E16C 0008AD4C  FC 40 E8 90 */	fmr f2, f29
/* 8008E170 0008AD50  48 29 41 7D */	bl func_803222EC
/* 8008E174 0008AD54  D0 3D 18 A4 */	stfs f1, 0x18a4(r29)
/* 8008E178 0008AD58  80 7D 18 C0 */	lwz r3, 0x18c0(r29)
/* 8008E17C 0008AD5C  80 9D 00 08 */	lwz r4, 8(r29)
/* 8008E180 0008AD60  48 29 41 BD */	bl func_8032233C
/* 8008E184 0008AD64  C0 02 8A F4 */	lfs f0, lbl_804D84D4(r2)
/* 8008E188 0008AD68  FC 1B 00 00 */	fcmpu cr0, f27, f0
/* 8008E18C 0008AD6C  41 82 00 08 */	beq lbl_8008E194
/* 8008E190 0008AD70  D3 7D 00 2C */	stfs f27, 0x2c(r29)
lbl_8008E194:
/* 8008E194 0008AD74  80 78 00 2C */	lwz r3, 0x2c(r24)
/* 8008E198 0008AD78  C0 02 8A F4 */	lfs f0, lbl_804D84D4(r2)
/* 8008E19C 0008AD7C  C0 23 18 38 */	lfs f1, 0x1838(r3)
/* 8008E1A0 0008AD80  80 1D 18 60 */	lwz r0, 0x1860(r29)
/* 8008E1A4 0008AD84  FC 01 00 00 */	fcmpu cr0, f1, f0
/* 8008E1A8 0008AD88  41 82 00 80 */	beq lbl_8008E228
/* 8008E1AC 0008AD8C  2C 00 00 05 */	cmpwi r0, 5
/* 8008E1B0 0008AD90  41 82 00 4C */	beq lbl_8008E1FC
/* 8008E1B4 0008AD94  40 80 00 1C */	bge lbl_8008E1D0
/* 8008E1B8 0008AD98  2C 00 00 02 */	cmpwi r0, 2
/* 8008E1BC 0008AD9C  41 82 00 30 */	beq lbl_8008E1EC
/* 8008E1C0 0008ADA0  40 80 00 5C */	bge lbl_8008E21C
/* 8008E1C4 0008ADA4  2C 00 00 01 */	cmpwi r0, 1
/* 8008E1C8 0008ADA8  40 80 00 14 */	bge lbl_8008E1DC
/* 8008E1CC 0008ADAC  48 00 00 50 */	b lbl_8008E21C
lbl_8008E1D0:
/* 8008E1D0 0008ADB0  2C 00 00 0D */	cmpwi r0, 0xd
/* 8008E1D4 0008ADB4  41 82 00 38 */	beq lbl_8008E20C
/* 8008E1D8 0008ADB8  48 00 00 44 */	b lbl_8008E21C
lbl_8008E1DC:
/* 8008E1DC 0008ADBC  38 9C 00 0B */	addi r4, r28, 0xb
/* 8008E1E0 0008ADC0  38 A0 00 00 */	li r5, 0
/* 8008E1E4 0008ADC4  48 03 1D ED */	bl func_800BFFD0
/* 8008E1E8 0008ADC8  48 00 00 40 */	b lbl_8008E228
lbl_8008E1EC:
/* 8008E1EC 0008ADCC  38 9C 00 0F */	addi r4, r28, 0xf
/* 8008E1F0 0008ADD0  38 A0 00 00 */	li r5, 0
/* 8008E1F4 0008ADD4  48 03 1D DD */	bl func_800BFFD0
/* 8008E1F8 0008ADD8  48 00 00 30 */	b lbl_8008E228
lbl_8008E1FC:
/* 8008E1FC 0008ADDC  38 9C 00 1F */	addi r4, r28, 0x1f
/* 8008E200 0008ADE0  38 A0 00 00 */	li r5, 0
/* 8008E204 0008ADE4  48 03 1D CD */	bl func_800BFFD0
/* 8008E208 0008ADE8  48 00 00 20 */	b lbl_8008E228
lbl_8008E20C:
/* 8008E20C 0008ADEC  38 9C 00 23 */	addi r4, r28, 0x23
/* 8008E210 0008ADF0  38 A0 00 00 */	li r5, 0
/* 8008E214 0008ADF4  48 03 1D BD */	bl func_800BFFD0
/* 8008E218 0008ADF8  48 00 00 10 */	b lbl_8008E228
lbl_8008E21C:
/* 8008E21C 0008ADFC  38 80 00 04 */	li r4, 4
/* 8008E220 0008AE00  38 A0 00 00 */	li r5, 0
/* 8008E224 0008AE04  48 03 1D AD */	bl func_800BFFD0
lbl_8008E228:
/* 8008E228 0008AE08  FC 20 E0 90 */	fmr f1, f28
/* 8008E22C 0008AE0C  80 9D 18 60 */	lwz r4, 0x1860(r29)
/* 8008E230 0008AE10  7F 03 C3 78 */	mr r3, r24
/* 8008E234 0008AE14  4B FF F8 DD */	bl func_8008DB10
/* 8008E238 0008AE18  C0 22 8A F4 */	lfs f1, lbl_804D84D4(r2)
/* 8008E23C 0008AE1C  7F 03 C3 78 */	mr r3, r24
/* 8008E240 0008AE20  C0 42 8A F8 */	lfs f2, lbl_804D84D8(r2)
/* 8008E244 0008AE24  7F E4 FB 78 */	mr r4, r31
/* 8008E248 0008AE28  FC 60 08 90 */	fmr f3, f1
/* 8008E24C 0008AE2C  38 A0 00 40 */	li r5, 0x40
/* 8008E250 0008AE30  38 C0 00 00 */	li r6, 0
/* 8008E254 0008AE34  4B FD B1 59 */	bl Fighter_ActionStateChange_800693AC
/* 8008E258 0008AE38  7F 03 C3 78 */	mr r3, r24
/* 8008E25C 0008AE3C  4B FE 09 49 */	bl func_8006EBA4
/* 8008E260 0008AE40  48 0D CD B5 */	bl func_8016B014
/* 8008E264 0008AE44  2C 03 00 00 */	cmpwi r3, 0
/* 8008E268 0008AE48  41 82 00 1C */	beq lbl_8008E284
/* 8008E26C 0008AE4C  7F 03 C3 78 */	mr r3, r24
/* 8008E270 0008AE50  4B FE D4 31 */	bl func_8007B6A0
/* 8008E274 0008AE54  88 1D 22 21 */	lbz r0, 0x2221(r29)
/* 8008E278 0008AE58  38 60 00 01 */	li r3, 1
/* 8008E27C 0008AE5C  50 60 36 72 */	rlwimi r0, r3, 6, 0x19, 0x19
/* 8008E280 0008AE60  98 1D 22 21 */	stb r0, 0x2221(r29)
lbl_8008E284:
/* 8008E284 0008AE64  80 6D AE B4 */	lwz r3, p_ftCommonData(r13)
/* 8008E288 0008AE68  C0 03 01 2C */	lfs f0, 0x12c(r3)
/* 8008E28C 0008AE6C  FC 1C 00 40 */	fcmpo cr0, f28, f0
/* 8008E290 0008AE70  40 81 00 0C */	ble lbl_8008E29C
/* 8008E294 0008AE74  38 00 00 01 */	li r0, 1
/* 8008E298 0008AE78  48 00 00 08 */	b lbl_8008E2A0
lbl_8008E29C:
/* 8008E29C 0008AE7C  38 00 00 00 */	li r0, 0
lbl_8008E2A0:
/* 8008E2A0 0008AE80  90 1D 23 44 */	stw r0, 0x2344(r29)
/* 8008E2A4 0008AE84  38 A0 00 00 */	li r5, 0
/* 8008E2A8 0008AE88  3C 60 80 09 */	lis r3, lbl_8008E4F0@ha
/* 8008E2AC 0008AE8C  98 BD 23 59 */	stb r5, 0x2359(r29)
/* 8008E2B0 0008AE90  38 03 E4 F0 */	addi r0, r3, lbl_8008E4F0@l
/* 8008E2B4 0008AE94  3C 60 80 09 */	lis r3, lbl_8008E714@ha
/* 8008E2B8 0008AE98  90 1D 21 D0 */	stw r0, 0x21d0(r29)
/* 8008E2BC 0008AE9C  38 80 00 FE */	li r4, 0xfe
/* 8008E2C0 0008AEA0  38 03 E7 14 */	addi r0, r3, lbl_8008E714@l
/* 8008E2C4 0008AEA4  98 9D 06 70 */	stb r4, 0x670(r29)
/* 8008E2C8 0008AEA8  38 60 00 01 */	li r3, 1
/* 8008E2CC 0008AEAC  2C 1F 00 5B */	cmpwi r31, 0x5b
/* 8008E2D0 0008AEB0  98 9D 06 71 */	stb r4, 0x671(r29)
/* 8008E2D4 0008AEB4  90 1D 21 D8 */	stw r0, 0x21d8(r29)
/* 8008E2D8 0008AEB8  C0 1D 18 50 */	lfs f0, 0x1850(r29)
/* 8008E2DC 0008AEBC  D0 1D 18 A8 */	stfs f0, 0x18a8(r29)
/* 8008E2E0 0008AEC0  88 1D 22 1C */	lbz r0, 0x221c(r29)
/* 8008E2E4 0008AEC4  50 60 0F BC */	rlwimi r0, r3, 1, 0x1e, 0x1e
/* 8008E2E8 0008AEC8  98 1D 22 1C */	stb r0, 0x221c(r29)
/* 8008E2EC 0008AECC  90 BD 18 AC */	stw r5, 0x18ac(r29)
/* 8008E2F0 0008AED0  40 82 00 48 */	bne lbl_8008E338
/* 8008E2F4 0008AED4  83 38 00 2C */	lwz r25, 0x2c(r24)
/* 8008E2F8 0008AED8  C0 79 00 80 */	lfs f3, 0x80(r25)
/* 8008E2FC 0008AEDC  C0 39 00 8C */	lfs f1, 0x8c(r25)
/* 8008E300 0008AEE0  C0 59 00 84 */	lfs f2, 0x84(r25)
/* 8008E304 0008AEE4  C0 19 00 90 */	lfs f0, 0x90(r25)
/* 8008E308 0008AEE8  EC 23 08 2A */	fadds f1, f3, f1
/* 8008E30C 0008AEEC  EC 42 00 2A */	fadds f2, f2, f0
/* 8008E310 0008AEF0  4B F9 49 21 */	bl atan2f
/* 8008E314 0008AEF4  C0 19 00 2C */	lfs f0, 0x2c(r25)
/* 8008E318 0008AEF8  38 79 00 00 */	addi r3, r25, 0
/* 8008E31C 0008AEFC  38 80 00 02 */	li r4, 2
/* 8008E320 0008AF00  EF 60 00 72 */	fmuls f27, f0, f1
/* 8008E324 0008AF04  4B FE 6C E9 */	bl func_8007500C
/* 8008E328 0008AF08  FC 20 D8 90 */	fmr f1, f27
/* 8008E32C 0008AF0C  38 83 00 00 */	addi r4, r3, 0
/* 8008E330 0008AF10  38 79 00 00 */	addi r3, r25, 0
/* 8008E334 0008AF14  4B FE 75 F9 */	bl func_8007592C
lbl_8008E338:
/* 8008E338 0008AF18  38 00 00 FF */	li r0, 0xff
/* 8008E33C 0008AF1C  98 1D 06 7F */	stb r0, 0x67f(r29)
/* 8008E340 0008AF20  7F A3 EB 78 */	mr r3, r29
/* 8008E344 0008AF24  48 00 19 75 */	bl func_8008FCB8
/* 8008E348 0008AF28  80 1D 23 48 */	lwz r0, 0x2348(r29)
/* 8008E34C 0008AF2C  2C 00 00 00 */	cmpwi r0, 0
/* 8008E350 0008AF30  41 82 00 0C */	beq lbl_8008E35C
/* 8008E354 0008AF34  38 00 00 01 */	li r0, 1
/* 8008E358 0008AF38  90 1D 23 48 */	stw r0, 0x2348(r29)
lbl_8008E35C:
/* 8008E35C 0008AF3C  2C 1C 00 03 */	cmpwi r28, 3
/* 8008E360 0008AF40  40 82 00 24 */	bne lbl_8008E384
/* 8008E364 0008AF44  80 8D AE B4 */	lwz r4, p_ftCommonData(r13)
/* 8008E368 0008AF48  C0 04 05 E8 */	lfs f0, 0x5e8(r4)
/* 8008E36C 0008AF4C  FC 1F 00 40 */	fcmpo cr0, f31, f0
/* 8008E370 0008AF50  4C 41 13 82 */	cror 2, 1, 2
/* 8008E374 0008AF54  40 82 00 10 */	bne lbl_8008E384
/* 8008E378 0008AF58  7F A3 EB 78 */	mr r3, r29
/* 8008E37C 0008AF5C  80 84 05 EC */	lwz r4, 0x5ec(r4)
/* 8008E380 0008AF60  4B FF 0C 41 */	bl func_8007EFC0
lbl_8008E384:
/* 8008E384 0008AF64  2C 1B 00 00 */	cmpwi r27, 0
/* 8008E388 0008AF68  41 82 00 5C */	beq lbl_8008E3E4
/* 8008E38C 0008AF6C  80 6D AE B4 */	lwz r3, p_ftCommonData(r13)
/* 8008E390 0008AF70  C0 03 02 0C */	lfs f0, 0x20c(r3)
/* 8008E394 0008AF74  FC 1E 00 40 */	fcmpo cr0, f30, f0
/* 8008E398 0008AF78  4C 41 13 82 */	cror 2, 1, 2
/* 8008E39C 0008AF7C  40 82 00 20 */	bne lbl_8008E3BC
/* 8008E3A0 0008AF80  38 00 00 4F */	li r0, 0x4f
/* 8008E3A4 0008AF84  90 1D 19 08 */	stw r0, 0x1908(r29)
/* 8008E3A8 0008AF88  80 7D 01 0C */	lwz r3, 0x10c(r29)
/* 8008E3AC 0008AF8C  80 63 00 4C */	lwz r3, 0x4c(r3)
/* 8008E3B0 0008AF90  80 03 00 20 */	lwz r0, 0x20(r3)
/* 8008E3B4 0008AF94  90 1D 19 0C */	stw r0, 0x190c(r29)
/* 8008E3B8 0008AF98  48 00 00 2C */	b lbl_8008E3E4
lbl_8008E3BC:
/* 8008E3BC 0008AF9C  C0 03 02 08 */	lfs f0, 0x208(r3)
/* 8008E3C0 0008AFA0  FC 1E 00 40 */	fcmpo cr0, f30, f0
/* 8008E3C4 0008AFA4  4C 41 13 82 */	cror 2, 1, 2
/* 8008E3C8 0008AFA8  40 82 00 1C */	bne lbl_8008E3E4
/* 8008E3CC 0008AFAC  38 00 00 50 */	li r0, 0x50
/* 8008E3D0 0008AFB0  90 1D 19 08 */	stw r0, 0x1908(r29)
/* 8008E3D4 0008AFB4  80 7D 01 0C */	lwz r3, 0x10c(r29)
/* 8008E3D8 0008AFB8  80 63 00 4C */	lwz r3, 0x4c(r3)
/* 8008E3DC 0008AFBC  80 03 00 1C */	lwz r0, 0x1c(r3)
/* 8008E3E0 0008AFC0  90 1D 19 0C */	stw r0, 0x190c(r29)
lbl_8008E3E4:
/* 8008E3E4 0008AFC4  2C 1C 00 03 */	cmpwi r28, 3
/* 8008E3E8 0008AFC8  40 82 00 50 */	bne lbl_8008E438
/* 8008E3EC 0008AFCC  80 1D 00 E0 */	lwz r0, 0xe0(r29)
/* 8008E3F0 0008AFD0  2C 00 00 01 */	cmpwi r0, 1
/* 8008E3F4 0008AFD4  40 82 00 44 */	bne lbl_8008E438
/* 8008E3F8 0008AFD8  80 6D AE B4 */	lwz r3, p_ftCommonData(r13)
/* 8008E3FC 0008AFDC  C0 03 01 74 */	lfs f0, 0x174(r3)
/* 8008E400 0008AFE0  FC 1E 00 40 */	fcmpo cr0, f30, f0
/* 8008E404 0008AFE4  4C 41 13 82 */	cror 2, 1, 2
/* 8008E408 0008AFE8  40 82 00 0C */	bne lbl_8008E414
/* 8008E40C 0008AFEC  38 60 00 04 */	li r3, 4
/* 8008E410 0008AFF0  48 00 00 20 */	b lbl_8008E430
lbl_8008E414:
/* 8008E414 0008AFF4  C0 03 01 70 */	lfs f0, 0x170(r3)
/* 8008E418 0008AFF8  FC 1E 00 40 */	fcmpo cr0, f30, f0
/* 8008E41C 0008AFFC  4C 41 13 82 */	cror 2, 1, 2
/* 8008E420 0008B000  40 82 00 0C */	bne lbl_8008E42C
/* 8008E424 0008B004  38 60 00 03 */	li r3, 3
/* 8008E428 0008B008  48 00 00 08 */	b lbl_8008E430
lbl_8008E42C:
/* 8008E42C 0008B00C  38 60 00 02 */	li r3, 2
lbl_8008E430:
/* 8008E430 0008B010  38 9D 00 B0 */	addi r4, r29, 0xb0
/* 8008E434 0008B014  4B FA 2A 11 */	bl func_80030E44
lbl_8008E438:
/* 8008E438 0008B018  7F 03 C3 78 */	mr r3, r24
/* 8008E43C 0008B01C  4B FF 13 E9 */	bl func_8007F824
/* 8008E440 0008B020  80 1D 00 10 */	lwz r0, 0x10(r29)
/* 8008E444 0008B024  2C 00 01 45 */	cmpwi r0, 0x145
/* 8008E448 0008B028  41 82 00 20 */	beq lbl_8008E468
/* 8008E44C 0008B02C  2C 1E 00 02 */	cmpwi r30, 2
/* 8008E450 0008B030  41 80 00 18 */	blt lbl_8008E468
/* 8008E454 0008B034  80 1D 18 60 */	lwz r0, 0x1860(r29)
/* 8008E458 0008B038  28 00 00 05 */	cmplwi r0, 5
/* 8008E45C 0008B03C  40 82 00 0C */	bne lbl_8008E468
/* 8008E460 0008B040  7F 03 C3 78 */	mr r3, r24
/* 8008E464 0008B044  48 00 26 FD */	bl func_80090B60
lbl_8008E468:
/* 8008E468 0008B048  BB 01 00 70 */	lmw r24, 0x70(r1)
/* 8008E46C 0008B04C  80 01 00 CC */	lwz r0, 0xcc(r1)
/* 8008E470 0008B050  CB E1 00 C0 */	lfd f31, 0xc0(r1)
/* 8008E474 0008B054  CB C1 00 B8 */	lfd f30, 0xb8(r1)
/* 8008E478 0008B058  CB A1 00 B0 */	lfd f29, 0xb0(r1)
/* 8008E47C 0008B05C  CB 81 00 A8 */	lfd f28, 0xa8(r1)
/* 8008E480 0008B060  CB 61 00 A0 */	lfd f27, 0xa0(r1)
/* 8008E484 0008B064  CB 41 00 98 */	lfd f26, 0x98(r1)
/* 8008E488 0008B068  CB 21 00 90 */	lfd f25, 0x90(r1)
/* 8008E48C 0008B06C  38 21 00 C8 */	addi r1, r1, 0xc8
/* 8008E490 0008B070  7C 08 03 A6 */	mtlr r0
/* 8008E494 0008B074  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

#pragma push
asm unk_t func_8008E498()
{ // clang-format off
    nofralloc
/* 8008E498 0008B078  80 03 00 10 */	lwz r0, 0x10(r3)
/* 8008E49C 0008B07C  2C 00 00 EC */	cmpwi r0, 0xec
/* 8008E4A0 0008B080  41 82 00 1C */	beq lbl_8008E4BC
/* 8008E4A4 0008B084  40 80 00 44 */	bge lbl_8008E4E8
/* 8008E4A8 0008B088  2C 00 00 27 */	cmpwi r0, 0x27
/* 8008E4AC 0008B08C  40 80 00 3C */	bge lbl_8008E4E8
/* 8008E4B0 0008B090  2C 00 00 19 */	cmpwi r0, 0x19
/* 8008E4B4 0008B094  40 80 00 08 */	bge lbl_8008E4BC
/* 8008E4B8 0008B098  48 00 00 30 */	b lbl_8008E4E8
lbl_8008E4BC:
/* 8008E4BC 0008B09C  80 AD AE B4 */	lwz r5, p_ftCommonData(r13)
/* 8008E4C0 0008B0A0  88 83 06 80 */	lbz r4, 0x680(r3)
/* 8008E4C4 0008B0A4  80 05 01 8C */	lwz r0, 0x18c(r5)
/* 8008E4C8 0008B0A8  7C 04 00 00 */	cmpw r4, r0
/* 8008E4CC 0008B0AC  41 81 00 1C */	bgt lbl_8008E4E8
/* 8008E4D0 0008B0B0  88 63 06 84 */	lbz r3, 0x684(r3)
/* 8008E4D4 0008B0B4  80 05 00 1C */	lwz r0, 0x1c(r5)
/* 8008E4D8 0008B0B8  7C 03 00 00 */	cmpw r3, r0
/* 8008E4DC 0008B0BC  41 80 00 0C */	blt lbl_8008E4E8
/* 8008E4E0 0008B0C0  38 60 00 01 */	li r3, 1
/* 8008E4E4 0008B0C4  4E 80 00 20 */	blr 
lbl_8008E4E8:
/* 8008E4E8 0008B0C8  38 60 00 00 */	li r3, 0
/* 8008E4EC 0008B0CC  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

extern unk_t func_800401F0();

#pragma push
asm unk_t lbl_8008E4F0()
{ // clang-format off
    nofralloc
/* 8008E4F0 0008B0D0  7C 08 02 A6 */	mflr r0
/* 8008E4F4 0008B0D4  90 01 00 04 */	stw r0, 4(r1)
/* 8008E4F8 0008B0D8  94 21 FF F8 */	stwu r1, -8(r1)
/* 8008E4FC 0008B0DC  80 63 00 2C */	lwz r3, 0x2c(r3)
/* 8008E500 0008B0E0  88 03 22 1A */	lbz r0, 0x221a(r3)
/* 8008E504 0008B0E4  54 00 DF FF */	rlwinm. r0, r0, 0x1b, 0x1f, 0x1f
/* 8008E508 0008B0E8  41 82 00 8C */	beq lbl_8008E594
/* 8008E50C 0008B0EC  C0 63 06 20 */	lfs f3, 0x620(r3)
/* 8008E510 0008B0F0  C0 43 06 24 */	lfs f2, 0x624(r3)
/* 8008E514 0008B0F4  80 8D AE B4 */	lwz r4, p_ftCommonData(r13)
/* 8008E518 0008B0F8  EC 23 00 F2 */	fmuls f1, f3, f3
/* 8008E51C 0008B0FC  EC 02 00 B2 */	fmuls f0, f2, f2
/* 8008E520 0008B100  C0 84 04 B0 */	lfs f4, 0x4b0(r4)
/* 8008E524 0008B104  EC 21 00 2A */	fadds f1, f1, f0
/* 8008E528 0008B108  EC 04 01 32 */	fmuls f0, f4, f4
/* 8008E52C 0008B10C  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8008E530 0008B110  4C 41 13 82 */	cror 2, 1, 2
/* 8008E534 0008B114  40 82 00 60 */	bne lbl_8008E594
/* 8008E538 0008B118  88 03 06 70 */	lbz r0, 0x670(r3)
/* 8008E53C 0008B11C  80 A4 04 B4 */	lwz r5, 0x4b4(r4)
/* 8008E540 0008B120  7C 00 28 00 */	cmpw r0, r5
/* 8008E544 0008B124  41 80 00 10 */	blt lbl_8008E554
/* 8008E548 0008B128  88 03 06 71 */	lbz r0, 0x671(r3)
/* 8008E54C 0008B12C  7C 00 28 00 */	cmpw r0, r5
/* 8008E550 0008B130  40 80 00 44 */	bge lbl_8008E594
lbl_8008E554:
/* 8008E554 0008B134  C0 84 04 B8 */	lfs f4, 0x4b8(r4)
/* 8008E558 0008B138  38 00 00 FE */	li r0, 0xfe
/* 8008E55C 0008B13C  C0 03 00 B0 */	lfs f0, 0xb0(r3)
/* 8008E560 0008B140  EC 23 01 32 */	fmuls f1, f3, f4
/* 8008E564 0008B144  EC 42 01 32 */	fmuls f2, f2, f4
/* 8008E568 0008B148  EC 00 08 2A */	fadds f0, f0, f1
/* 8008E56C 0008B14C  D0 03 00 B0 */	stfs f0, 0xb0(r3)
/* 8008E570 0008B150  C0 03 00 B4 */	lfs f0, 0xb4(r3)
/* 8008E574 0008B154  EC 00 10 2A */	fadds f0, f0, f2
/* 8008E578 0008B158  D0 03 00 B4 */	stfs f0, 0xb4(r3)
/* 8008E57C 0008B15C  98 03 06 70 */	stb r0, 0x670(r3)
/* 8008E580 0008B160  98 03 06 71 */	stb r0, 0x671(r3)
/* 8008E584 0008B164  88 83 22 1F */	lbz r4, 0x221f(r3)
/* 8008E588 0008B168  88 63 00 0C */	lbz r3, 0xc(r3)
/* 8008E58C 0008B16C  54 84 EF FE */	rlwinm r4, r4, 0x1d, 0x1f, 0x1f
/* 8008E590 0008B170  4B FB 1C 61 */	bl func_800401F0
lbl_8008E594:
/* 8008E594 0008B174  80 01 00 0C */	lwz r0, 0xc(r1)
/* 8008E598 0008B178  38 21 00 08 */	addi r1, r1, 8
/* 8008E59C 0008B17C  7C 08 03 A6 */	mtlr r0
/* 8008E5A0 0008B180  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

extern f64 const lbl_804D8500;
extern f64 const lbl_804D8508;
extern f32 const lbl_804D84F8;
extern unk_t PSVECCrossProduct();

#pragma push
asm unk_t func_8008E5A4()
{ // clang-format off
    nofralloc
/* 8008E5A4 0008B184  7C 08 02 A6 */	mflr r0
/* 8008E5A8 0008B188  90 01 00 04 */	stw r0, 4(r1)
/* 8008E5AC 0008B18C  94 21 FF A8 */	stwu r1, -0x58(r1)
/* 8008E5B0 0008B190  DB E1 00 50 */	stfd f31, 0x50(r1)
/* 8008E5B4 0008B194  DB C1 00 48 */	stfd f30, 0x48(r1)
/* 8008E5B8 0008B198  DB A1 00 40 */	stfd f29, 0x40(r1)
/* 8008E5BC 0008B19C  DB 81 00 38 */	stfd f28, 0x38(r1)
/* 8008E5C0 0008B1A0  93 E1 00 34 */	stw r31, 0x34(r1)
/* 8008E5C4 0008B1A4  7C 7F 1B 78 */	mr r31, r3
/* 8008E5C8 0008B1A8  C0 22 8A F4 */	lfs f1, lbl_804D84D4(r2)
/* 8008E5CC 0008B1AC  C0 63 06 20 */	lfs f3, 0x620(r3)
/* 8008E5D0 0008B1B0  FC 03 08 00 */	fcmpu cr0, f3, f1
/* 8008E5D4 0008B1B4  40 82 00 10 */	bne lbl_8008E5E4
/* 8008E5D8 0008B1B8  C0 1F 06 24 */	lfs f0, 0x624(r31)
/* 8008E5DC 0008B1BC  FC 00 08 00 */	fcmpu cr0, f0, f1
/* 8008E5E0 0008B1C0  41 82 01 10 */	beq lbl_8008E6F0
lbl_8008E5E4:
/* 8008E5E4 0008B1C4  C0 3F 00 8C */	lfs f1, 0x8c(r31)
/* 8008E5E8 0008B1C8  C3 9F 00 90 */	lfs f28, 0x90(r31)
/* 8008E5EC 0008B1CC  FC 80 08 50 */	fneg f4, f1
/* 8008E5F0 0008B1D0  C0 02 8B 18 */	lfs f0, lbl_804D84F8(r2)
/* 8008E5F4 0008B1D4  EF FC 07 32 */	fmuls f31, f28, f28
/* 8008E5F8 0008B1D8  FF A0 08 90 */	fmr f29, f1
/* 8008E5FC 0008B1DC  EC 44 F9 3A */	fmadds f2, f4, f4, f31
/* 8008E600 0008B1E0  FC 02 00 40 */	fcmpo cr0, f2, f0
/* 8008E604 0008B1E4  41 80 00 EC */	blt lbl_8008E6F0
/* 8008E608 0008B1E8  C0 3F 06 24 */	lfs f1, 0x624(r31)
/* 8008E60C 0008B1EC  38 7F 00 8C */	addi r3, r31, 0x8c
/* 8008E610 0008B1F0  C0 02 8A F4 */	lfs f0, lbl_804D84D4(r2)
/* 8008E614 0008B1F4  38 81 00 20 */	addi r4, r1, 0x20
/* 8008E618 0008B1F8  EC 24 00 72 */	fmuls f1, f4, f1
/* 8008E61C 0008B1FC  D0 61 00 20 */	stfs f3, 0x20(r1)
/* 8008E620 0008B200  38 A1 00 14 */	addi r5, r1, 0x14
/* 8008E624 0008B204  EC 7C 08 FA */	fmadds f3, f28, f3, f1
/* 8008E628 0008B208  C0 3F 06 24 */	lfs f1, 0x624(r31)
/* 8008E62C 0008B20C  D0 21 00 24 */	stfs f1, 0x24(r1)
/* 8008E630 0008B210  EC 23 00 F2 */	fmuls f1, f3, f3
/* 8008E634 0008B214  D0 01 00 28 */	stfs f0, 0x28(r1)
/* 8008E638 0008B218  EF C1 10 24 */	fdivs f30, f1, f2
/* 8008E63C 0008B21C  48 2B 48 1D */	bl PSVECCrossProduct
/* 8008E640 0008B220  C0 21 00 1C */	lfs f1, 0x1c(r1)
/* 8008E644 0008B224  C0 02 8A F4 */	lfs f0, lbl_804D84D4(r2)
/* 8008E648 0008B228  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8008E64C 0008B22C  40 80 00 08 */	bge lbl_8008E654
/* 8008E650 0008B230  FF C0 F0 50 */	fneg f30, f30
lbl_8008E654:
/* 8008E654 0008B234  FC 20 E0 90 */	fmr f1, f28
/* 8008E658 0008B238  FC 40 E8 90 */	fmr f2, f29
/* 8008E65C 0008B23C  4B F9 45 D5 */	bl atan2f
/* 8008E660 0008B240  EF FD FF 7A */	fmadds f31, f29, f29, f31
/* 8008E664 0008B244  C0 02 8A F4 */	lfs f0, lbl_804D84D4(r2)
/* 8008E668 0008B248  FC 1F 00 40 */	fcmpo cr0, f31, f0
/* 8008E66C 0008B24C  40 81 00 50 */	ble lbl_8008E6BC
/* 8008E670 0008B250  FC 40 F8 34 */	frsqrte f2, f31
/* 8008E674 0008B254  C8 82 8B 20 */	lfd f4, lbl_804D8500(r2)
/* 8008E678 0008B258  C8 62 8B 28 */	lfd f3, lbl_804D8508(r2)
/* 8008E67C 0008B25C  FC 02 00 B2 */	fmul f0, f2, f2
/* 8008E680 0008B260  FC 44 00 B2 */	fmul f2, f4, f2
/* 8008E684 0008B264  FC 1F 18 3C */	fnmsub f0, f31, f0, f3
/* 8008E688 0008B268  FC 42 00 32 */	fmul f2, f2, f0
/* 8008E68C 0008B26C  FC 02 00 B2 */	fmul f0, f2, f2
/* 8008E690 0008B270  FC 44 00 B2 */	fmul f2, f4, f2
/* 8008E694 0008B274  FC 1F 18 3C */	fnmsub f0, f31, f0, f3
/* 8008E698 0008B278  FC 42 00 32 */	fmul f2, f2, f0
/* 8008E69C 0008B27C  FC 02 00 B2 */	fmul f0, f2, f2
/* 8008E6A0 0008B280  FC 44 00 B2 */	fmul f2, f4, f2
/* 8008E6A4 0008B284  FC 1F 18 3C */	fnmsub f0, f31, f0, f3
/* 8008E6A8 0008B288  FC 02 00 32 */	fmul f0, f2, f0
/* 8008E6AC 0008B28C  FC 1F 00 32 */	fmul f0, f31, f0
/* 8008E6B0 0008B290  FC 00 00 18 */	frsp f0, f0
/* 8008E6B4 0008B294  D0 01 00 0C */	stfs f0, 0xc(r1)
/* 8008E6B8 0008B298  C3 E1 00 0C */	lfs f31, 0xc(r1)
lbl_8008E6BC:
/* 8008E6BC 0008B29C  80 6D AE B4 */	lwz r3, p_ftCommonData(r13)
/* 8008E6C0 0008B2A0  C0 42 8A F0 */	lfs f2, lbl_804D84D0(r2)
/* 8008E6C4 0008B2A4  C0 03 01 A8 */	lfs f0, 0x1a8(r3)
/* 8008E6C8 0008B2A8  EC 02 00 32 */	fmuls f0, f2, f0
/* 8008E6CC 0008B2AC  EF 80 0F BA */	fmadds f28, f0, f30, f1
/* 8008E6D0 0008B2B0  FC 20 E0 90 */	fmr f1, f28
/* 8008E6D4 0008B2B4  48 29 7B 6D */	bl cosf
/* 8008E6D8 0008B2B8  EC 1F 00 72 */	fmuls f0, f31, f1
/* 8008E6DC 0008B2BC  FC 20 E0 90 */	fmr f1, f28
/* 8008E6E0 0008B2C0  D0 1F 00 8C */	stfs f0, 0x8c(r31)
/* 8008E6E4 0008B2C4  48 29 7C F1 */	bl sinf
/* 8008E6E8 0008B2C8  EC 1F 00 72 */	fmuls f0, f31, f1
/* 8008E6EC 0008B2CC  D0 1F 00 90 */	stfs f0, 0x90(r31)
lbl_8008E6F0:
/* 8008E6F0 0008B2D0  80 01 00 5C */	lwz r0, 0x5c(r1)
/* 8008E6F4 0008B2D4  CB E1 00 50 */	lfd f31, 0x50(r1)
/* 8008E6F8 0008B2D8  CB C1 00 48 */	lfd f30, 0x48(r1)
/* 8008E6FC 0008B2DC  CB A1 00 40 */	lfd f29, 0x40(r1)
/* 8008E700 0008B2E0  CB 81 00 38 */	lfd f28, 0x38(r1)
/* 8008E704 0008B2E4  83 E1 00 34 */	lwz r31, 0x34(r1)
/* 8008E708 0008B2E8  38 21 00 58 */	addi r1, r1, 0x58
/* 8008E70C 0008B2EC  7C 08 03 A6 */	mtlr r0
/* 8008E710 0008B2F0  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

extern unk_t func_800DF608();

#pragma push
asm unk_t lbl_8008E714()
{ // clang-format off
    nofralloc
/* 8008E714 0008B2F4  7C 08 02 A6 */	mflr r0
/* 8008E718 0008B2F8  90 01 00 04 */	stw r0, 4(r1)
/* 8008E71C 0008B2FC  94 21 FF D0 */	stwu r1, -0x30(r1)
/* 8008E720 0008B300  DB E1 00 28 */	stfd f31, 0x28(r1)
/* 8008E724 0008B304  DB C1 00 20 */	stfd f30, 0x20(r1)
/* 8008E728 0008B308  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 8008E72C 0008B30C  93 C1 00 18 */	stw r30, 0x18(r1)
/* 8008E730 0008B310  7C 7E 1B 78 */	mr r30, r3
/* 8008E734 0008B314  83 FE 00 2C */	lwz r31, 0x2c(r30)
/* 8008E738 0008B318  80 6D AE B4 */	lwz r3, p_ftCommonData(r13)
/* 8008E73C 0008B31C  C0 5F 06 20 */	lfs f2, 0x620(r31)
/* 8008E740 0008B320  C0 3F 06 24 */	lfs f1, 0x624(r31)
/* 8008E744 0008B324  EC 42 00 B2 */	fmuls f2, f2, f2
/* 8008E748 0008B328  C0 03 04 B0 */	lfs f0, 0x4b0(r3)
/* 8008E74C 0008B32C  EC 21 00 72 */	fmuls f1, f1, f1
/* 8008E750 0008B330  EC 00 00 32 */	fmuls f0, f0, f0
/* 8008E754 0008B334  EC 22 08 2A */	fadds f1, f2, f1
/* 8008E758 0008B338  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8008E75C 0008B33C  4C 41 13 82 */	cror 2, 1, 2
/* 8008E760 0008B340  40 82 00 0C */	bne lbl_8008E76C
/* 8008E764 0008B344  38 00 00 01 */	li r0, 1
/* 8008E768 0008B348  48 00 00 08 */	b lbl_8008E770
lbl_8008E76C:
/* 8008E76C 0008B34C  38 00 00 00 */	li r0, 0
lbl_8008E770:
/* 8008E770 0008B350  2C 00 00 00 */	cmpwi r0, 0
/* 8008E774 0008B354  40 82 00 14 */	bne lbl_8008E788
/* 8008E778 0008B358  7F E3 FB 78 */	mr r3, r31
/* 8008E77C 0008B35C  48 05 0E 8D */	bl func_800DF608
/* 8008E780 0008B360  2C 03 00 00 */	cmpwi r3, 0
/* 8008E784 0008B364  41 82 00 70 */	beq lbl_8008E7F4
lbl_8008E788:
/* 8008E788 0008B368  7F E3 FB 78 */	mr r3, r31
/* 8008E78C 0008B36C  48 05 0E 7D */	bl func_800DF608
/* 8008E790 0008B370  2C 03 00 00 */	cmpwi r3, 0
/* 8008E794 0008B374  41 82 00 20 */	beq lbl_8008E7B4
/* 8008E798 0008B378  80 6D AE B4 */	lwz r3, p_ftCommonData(r13)
/* 8008E79C 0008B37C  C0 3F 06 38 */	lfs f1, 0x638(r31)
/* 8008E7A0 0008B380  C0 43 04 BC */	lfs f2, 0x4bc(r3)
/* 8008E7A4 0008B384  C0 1F 06 3C */	lfs f0, 0x63c(r31)
/* 8008E7A8 0008B388  EC 21 00 B2 */	fmuls f1, f1, f2
/* 8008E7AC 0008B38C  EC 40 00 B2 */	fmuls f2, f0, f2
/* 8008E7B0 0008B390  48 00 00 1C */	b lbl_8008E7CC
lbl_8008E7B4:
/* 8008E7B4 0008B394  80 6D AE B4 */	lwz r3, p_ftCommonData(r13)
/* 8008E7B8 0008B398  C0 3F 06 20 */	lfs f1, 0x620(r31)
/* 8008E7BC 0008B39C  C0 43 04 BC */	lfs f2, 0x4bc(r3)
/* 8008E7C0 0008B3A0  C0 1F 06 24 */	lfs f0, 0x624(r31)
/* 8008E7C4 0008B3A4  EC 21 00 B2 */	fmuls f1, f1, f2
/* 8008E7C8 0008B3A8  EC 40 00 B2 */	fmuls f2, f0, f2
lbl_8008E7CC:
/* 8008E7CC 0008B3AC  C0 1F 00 B0 */	lfs f0, 0xb0(r31)
/* 8008E7D0 0008B3B0  EC 00 08 2A */	fadds f0, f0, f1
/* 8008E7D4 0008B3B4  D0 1F 00 B0 */	stfs f0, 0xb0(r31)
/* 8008E7D8 0008B3B8  C0 1F 00 B4 */	lfs f0, 0xb4(r31)
/* 8008E7DC 0008B3BC  EC 00 10 2A */	fadds f0, f0, f2
/* 8008E7E0 0008B3C0  D0 1F 00 B4 */	stfs f0, 0xb4(r31)
/* 8008E7E4 0008B3C4  88 9F 22 1F */	lbz r4, 0x221f(r31)
/* 8008E7E8 0008B3C8  88 7F 00 0C */	lbz r3, 0xc(r31)
/* 8008E7EC 0008B3CC  54 84 EF FE */	rlwinm r4, r4, 0x1d, 0x1f, 0x1f
/* 8008E7F0 0008B3D0  4B FB 1A 01 */	bl func_800401F0
lbl_8008E7F4:
/* 8008E7F4 0008B3D4  80 1F 23 44 */	lwz r0, 0x2344(r31)
/* 8008E7F8 0008B3D8  2C 00 00 00 */	cmpwi r0, 0
/* 8008E7FC 0008B3DC  41 82 00 1C */	beq lbl_8008E818
/* 8008E800 0008B3E0  38 00 00 00 */	li r0, 0
/* 8008E804 0008B3E4  90 1F 23 44 */	stw r0, 0x2344(r31)
/* 8008E808 0008B3E8  7F C3 F3 78 */	mr r3, r30
/* 8008E80C 0008B3EC  80 8D AE B4 */	lwz r4, p_ftCommonData(r13)
/* 8008E810 0008B3F0  80 84 01 30 */	lwz r4, 0x130(r4)
/* 8008E814 0008B3F4  4B FE CF 91 */	bl func_8007B7A4
lbl_8008E818:
/* 8008E818 0008B3F8  7F E3 FB 78 */	mr r3, r31
/* 8008E81C 0008B3FC  4B FF FD 89 */	bl func_8008E5A4
/* 8008E820 0008B400  80 1F 06 5C */	lwz r0, 0x65c(r31)
/* 8008E824 0008B404  54 00 00 01 */	rlwinm. r0, r0, 0, 0, 0
/* 8008E828 0008B408  41 82 00 C0 */	beq lbl_8008E8E8
/* 8008E82C 0008B40C  C0 3F 00 8C */	lfs f1, 0x8c(r31)
/* 8008E830 0008B410  C0 02 8A F4 */	lfs f0, lbl_804D84D4(r2)
/* 8008E834 0008B414  FF E0 08 90 */	fmr f31, f1
/* 8008E838 0008B418  C3 DF 00 90 */	lfs f30, 0x90(r31)
/* 8008E83C 0008B41C  FC 01 00 00 */	fcmpu cr0, f1, f0
/* 8008E840 0008B420  40 82 00 0C */	bne lbl_8008E84C
/* 8008E844 0008B424  FC 1E 00 00 */	fcmpu cr0, f30, f0
/* 8008E848 0008B428  41 82 00 A0 */	beq lbl_8008E8E8
lbl_8008E84C:
/* 8008E84C 0008B42C  FC 20 F0 90 */	fmr f1, f30
/* 8008E850 0008B430  FC 40 F8 90 */	fmr f2, f31
/* 8008E854 0008B434  4B F9 43 DD */	bl atan2f
/* 8008E858 0008B438  EC 5E 07 B2 */	fmuls f2, f30, f30
/* 8008E85C 0008B43C  C0 02 8A F4 */	lfs f0, lbl_804D84D4(r2)
/* 8008E860 0008B440  EC 9F 17 FA */	fmadds f4, f31, f31, f2
/* 8008E864 0008B444  FF E0 08 90 */	fmr f31, f1
/* 8008E868 0008B448  FC 04 00 40 */	fcmpo cr0, f4, f0
/* 8008E86C 0008B44C  40 81 00 50 */	ble lbl_8008E8BC
/* 8008E870 0008B450  FC 20 20 34 */	frsqrte f1, f4
/* 8008E874 0008B454  C8 62 8B 20 */	lfd f3, lbl_804D8500(r2)
/* 8008E878 0008B458  C8 42 8B 28 */	lfd f2, lbl_804D8508(r2)
/* 8008E87C 0008B45C  FC 01 00 72 */	fmul f0, f1, f1
/* 8008E880 0008B460  FC 23 00 72 */	fmul f1, f3, f1
/* 8008E884 0008B464  FC 04 10 3C */	fnmsub f0, f4, f0, f2
/* 8008E888 0008B468  FC 21 00 32 */	fmul f1, f1, f0
/* 8008E88C 0008B46C  FC 01 00 72 */	fmul f0, f1, f1
/* 8008E890 0008B470  FC 23 00 72 */	fmul f1, f3, f1
/* 8008E894 0008B474  FC 04 10 3C */	fnmsub f0, f4, f0, f2
/* 8008E898 0008B478  FC 21 00 32 */	fmul f1, f1, f0
/* 8008E89C 0008B47C  FC 01 00 72 */	fmul f0, f1, f1
/* 8008E8A0 0008B480  FC 23 00 72 */	fmul f1, f3, f1
/* 8008E8A4 0008B484  FC 04 10 3C */	fnmsub f0, f4, f0, f2
/* 8008E8A8 0008B488  FC 01 00 32 */	fmul f0, f1, f0
/* 8008E8AC 0008B48C  FC 04 00 32 */	fmul f0, f4, f0
/* 8008E8B0 0008B490  FC 00 00 18 */	frsp f0, f0
/* 8008E8B4 0008B494  D0 01 00 10 */	stfs f0, 0x10(r1)
/* 8008E8B8 0008B498  C0 81 00 10 */	lfs f4, 0x10(r1)
lbl_8008E8BC:
/* 8008E8BC 0008B49C  80 6D AE B4 */	lwz r3, p_ftCommonData(r13)
/* 8008E8C0 0008B4A0  FC 20 F8 90 */	fmr f1, f31
/* 8008E8C4 0008B4A4  C0 03 01 AC */	lfs f0, 0x1ac(r3)
/* 8008E8C8 0008B4A8  EF C0 01 32 */	fmuls f30, f0, f4
/* 8008E8CC 0008B4AC  48 29 79 75 */	bl cosf
/* 8008E8D0 0008B4B0  EC 1E 00 72 */	fmuls f0, f30, f1
/* 8008E8D4 0008B4B4  FC 20 F8 90 */	fmr f1, f31
/* 8008E8D8 0008B4B8  D0 1F 00 8C */	stfs f0, 0x8c(r31)
/* 8008E8DC 0008B4BC  48 29 7A F9 */	bl sinf
/* 8008E8E0 0008B4C0  EC 1E 00 72 */	fmuls f0, f30, f1
/* 8008E8E4 0008B4C4  D0 1F 00 90 */	stfs f0, 0x90(r31)
lbl_8008E8E8:
/* 8008E8E8 0008B4C8  80 01 00 34 */	lwz r0, 0x34(r1)
/* 8008E8EC 0008B4CC  CB E1 00 28 */	lfd f31, 0x28(r1)
/* 8008E8F0 0008B4D0  CB C1 00 20 */	lfd f30, 0x20(r1)
/* 8008E8F4 0008B4D4  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 8008E8F8 0008B4D8  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 8008E8FC 0008B4DC  38 21 00 30 */	addi r1, r1, 0x30
/* 8008E900 0008B4E0  7C 08 03 A6 */	mtlr r0
/* 8008E904 0008B4E4  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

extern unk_t func_800C318C();

#pragma push
asm void func_8008E908(HSD_GObj* fighter_gobj, f32)
{ // clang-format off
    nofralloc
/* 8008E908 0008B4E8  7C 08 02 A6 */	mflr r0
/* 8008E90C 0008B4EC  90 01 00 04 */	stw r0, 4(r1)
/* 8008E910 0008B4F0  94 21 FF F8 */	stwu r1, -8(r1)
/* 8008E914 0008B4F4  80 A3 00 2C */	lwz r5, 0x2c(r3)
/* 8008E918 0008B4F8  88 05 22 1D */	lbz r0, 0x221d(r5)
/* 8008E91C 0008B4FC  54 00 07 FF */	clrlwi. r0, r0, 0x1f
/* 8008E920 0008B500  41 82 00 10 */	beq lbl_8008E930
/* 8008E924 0008B504  80 8D AE B4 */	lwz r4, p_ftCommonData(r13)
/* 8008E928 0008B508  80 04 04 98 */	lwz r0, 0x498(r4)
/* 8008E92C 0008B50C  90 05 20 64 */	stw r0, 0x2064(r5)
lbl_8008E930:
/* 8008E930 0008B510  80 85 18 60 */	lwz r4, 0x1860(r5)
/* 8008E934 0008B514  28 04 00 06 */	cmplwi r4, 6
/* 8008E938 0008B518  41 82 00 0C */	beq lbl_8008E944
/* 8008E93C 0008B51C  28 04 00 07 */	cmplwi r4, 7
/* 8008E940 0008B520  40 82 00 2C */	bne lbl_8008E96C
lbl_8008E944:
/* 8008E944 0008B524  88 05 22 28 */	lbz r0, 0x2228(r5)
/* 8008E948 0008B528  54 00 DF FF */	rlwinm. r0, r0, 0x1b, 0x1f, 0x1f
/* 8008E94C 0008B52C  40 82 00 20 */	bne lbl_8008E96C
/* 8008E950 0008B530  28 04 00 06 */	cmplwi r4, 6
/* 8008E954 0008B534  40 82 00 0C */	bne lbl_8008E960
/* 8008E958 0008B538  38 80 00 00 */	li r4, 0
/* 8008E95C 0008B53C  48 00 00 08 */	b lbl_8008E964
lbl_8008E960:
/* 8008E960 0008B540  38 80 00 01 */	li r4, 1
lbl_8008E964:
/* 8008E964 0008B544  48 03 48 29 */	bl func_800C318C
/* 8008E968 0008B548  48 00 00 0C */	b lbl_8008E974
lbl_8008E96C:
/* 8008E96C 0008B54C  38 80 FF FF */	li r4, -1
/* 8008E970 0008B550  4B FF F3 71 */	bl func_8008DCE0
lbl_8008E974:
/* 8008E974 0008B554  80 01 00 0C */	lwz r0, 0xc(r1)
/* 8008E978 0008B558  38 21 00 08 */	addi r1, r1, 8
/* 8008E97C 0008B55C  7C 08 03 A6 */	mtlr r0
/* 8008E980 0008B560  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

#pragma push
asm BOOL func_8008E984(Fighter* fp)
{ // clang-format off
    nofralloc
/* 8008E984 0008B564  C0 02 8A F4 */	lfs f0, lbl_804D84D4(r2)
/* 8008E988 0008B568  C0 43 18 50 */	lfs f2, 0x1850(r3)
/* 8008E98C 0008B56C  FC 00 10 00 */	fcmpu cr0, f0, f2
/* 8008E990 0008B570  41 82 00 30 */	beq lbl_8008E9C0
/* 8008E994 0008B574  88 83 22 1A */	lbz r4, 0x221a(r3)
/* 8008E998 0008B578  54 80 DF FF */	rlwinm. r0, r4, 0x1b, 0x1f, 0x1f
/* 8008E99C 0008B57C  41 82 00 2C */	beq lbl_8008E9C8
/* 8008E9A0 0008B580  54 80 E7 FF */	rlwinm. r0, r4, 0x1c, 0x1f, 0x1f
/* 8008E9A4 0008B584  41 82 00 24 */	beq lbl_8008E9C8
/* 8008E9A8 0008B588  80 8D AE B4 */	lwz r4, p_ftCommonData(r13)
/* 8008E9AC 0008B58C  C0 23 18 A8 */	lfs f1, 0x18a8(r3)
/* 8008E9B0 0008B590  C0 04 01 40 */	lfs f0, 0x140(r4)
/* 8008E9B4 0008B594  EC 01 00 2A */	fadds f0, f1, f0
/* 8008E9B8 0008B598  FC 02 00 40 */	fcmpo cr0, f2, f0
/* 8008E9BC 0008B59C  40 80 00 0C */	bge lbl_8008E9C8
lbl_8008E9C0:
/* 8008E9C0 0008B5A0  38 60 00 01 */	li r3, 1
/* 8008E9C4 0008B5A4  4E 80 00 20 */	blr 
lbl_8008E9C8:
/* 8008E9C8 0008B5A8  38 60 00 00 */	li r3, 0
/* 8008E9CC 0008B5AC  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

extern unk_t func_800DC3A4();
extern unk_t func_800DC284();

#pragma push
asm void func_8008E9D0(HSD_GObj* fighter_gobj)
{ // clang-format off
    nofralloc
/* 8008E9D0 0008B5B0  7C 08 02 A6 */	mflr r0
/* 8008E9D4 0008B5B4  90 01 00 04 */	stw r0, 4(r1)
/* 8008E9D8 0008B5B8  94 21 FF D0 */	stwu r1, -0x30(r1)
/* 8008E9DC 0008B5BC  93 E1 00 2C */	stw r31, 0x2c(r1)
/* 8008E9E0 0008B5C0  93 C1 00 28 */	stw r30, 0x28(r1)
/* 8008E9E4 0008B5C4  93 A1 00 24 */	stw r29, 0x24(r1)
/* 8008E9E8 0008B5C8  7C 7D 1B 78 */	mr r29, r3
/* 8008E9EC 0008B5CC  83 C3 00 2C */	lwz r30, 0x2c(r3)
/* 8008E9F0 0008B5D0  48 03 A3 11 */	bl func_800C8D00
/* 8008E9F4 0008B5D4  80 1E 00 10 */	lwz r0, 0x10(r30)
/* 8008E9F8 0008B5D8  2C 00 00 E0 */	cmpwi r0, 0xe0
/* 8008E9FC 0008B5DC  41 82 00 0C */	beq lbl_8008EA08
/* 8008EA00 0008B5E0  2C 00 00 E1 */	cmpwi r0, 0xe1
/* 8008EA04 0008B5E4  40 82 00 0C */	bne lbl_8008EA10
lbl_8008EA08:
/* 8008EA08 0008B5E8  7F A3 EB 78 */	mr r3, r29
/* 8008EA0C 0008B5EC  48 04 D8 79 */	bl func_800DC284
lbl_8008EA10:
/* 8008EA10 0008B5F0  80 1E 00 10 */	lwz r0, 0x10(r30)
/* 8008EA14 0008B5F4  2C 00 00 E3 */	cmpwi r0, 0xe3
/* 8008EA18 0008B5F8  41 82 00 0C */	beq lbl_8008EA24
/* 8008EA1C 0008B5FC  2C 00 00 E4 */	cmpwi r0, 0xe4
/* 8008EA20 0008B600  40 82 00 0C */	bne lbl_8008EA2C
lbl_8008EA24:
/* 8008EA24 0008B604  7F A3 EB 78 */	mr r3, r29
/* 8008EA28 0008B608  48 04 D9 7D */	bl func_800DC3A4
lbl_8008EA2C:
/* 8008EA2C 0008B60C  80 6D AE B4 */	lwz r3, p_ftCommonData(r13)
/* 8008EA30 0008B610  C0 5E 18 50 */	lfs f2, 0x1850(r30)
/* 8008EA34 0008B614  C0 23 01 54 */	lfs f1, 0x154(r3)
/* 8008EA38 0008B618  C0 03 01 58 */	lfs f0, 0x158(r3)
/* 8008EA3C 0008B61C  EC 22 00 72 */	fmuls f1, f2, f1
/* 8008EA40 0008B620  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8008EA44 0008B624  40 80 00 0C */	bge lbl_8008EA50
/* 8008EA48 0008B628  38 80 00 00 */	li r4, 0
/* 8008EA4C 0008B62C  48 00 00 30 */	b lbl_8008EA7C
lbl_8008EA50:
/* 8008EA50 0008B630  C0 03 01 5C */	lfs f0, 0x15c(r3)
/* 8008EA54 0008B634  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8008EA58 0008B638  40 80 00 0C */	bge lbl_8008EA64
/* 8008EA5C 0008B63C  38 80 00 01 */	li r4, 1
/* 8008EA60 0008B640  48 00 00 1C */	b lbl_8008EA7C
lbl_8008EA64:
/* 8008EA64 0008B644  C0 03 01 60 */	lfs f0, 0x160(r3)
/* 8008EA68 0008B648  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8008EA6C 0008B64C  40 80 00 0C */	bge lbl_8008EA78
/* 8008EA70 0008B650  38 80 00 02 */	li r4, 2
/* 8008EA74 0008B654  48 00 00 08 */	b lbl_8008EA7C
lbl_8008EA78:
/* 8008EA78 0008B658  38 80 00 03 */	li r4, 3
lbl_8008EA7C:
/* 8008EA7C 0008B65C  80 7D 00 2C */	lwz r3, 0x2c(r29)
/* 8008EA80 0008B660  C0 02 8A F4 */	lfs f0, lbl_804D84D4(r2)
/* 8008EA84 0008B664  C0 23 18 38 */	lfs f1, 0x1838(r3)
/* 8008EA88 0008B668  80 1E 18 60 */	lwz r0, 0x1860(r30)
/* 8008EA8C 0008B66C  FC 01 00 00 */	fcmpu cr0, f1, f0
/* 8008EA90 0008B670  41 82 00 94 */	beq lbl_8008EB24
/* 8008EA94 0008B674  2C 00 00 05 */	cmpwi r0, 5
/* 8008EA98 0008B678  41 82 00 54 */	beq lbl_8008EAEC
/* 8008EA9C 0008B67C  40 80 00 1C */	bge lbl_8008EAB8
/* 8008EAA0 0008B680  2C 00 00 02 */	cmpwi r0, 2
/* 8008EAA4 0008B684  41 82 00 34 */	beq lbl_8008EAD8
/* 8008EAA8 0008B688  40 80 00 6C */	bge lbl_8008EB14
/* 8008EAAC 0008B68C  2C 00 00 01 */	cmpwi r0, 1
/* 8008EAB0 0008B690  40 80 00 14 */	bge lbl_8008EAC4
/* 8008EAB4 0008B694  48 00 00 60 */	b lbl_8008EB14
lbl_8008EAB8:
/* 8008EAB8 0008B698  2C 00 00 0D */	cmpwi r0, 0xd
/* 8008EABC 0008B69C  41 82 00 44 */	beq lbl_8008EB00
/* 8008EAC0 0008B6A0  48 00 00 54 */	b lbl_8008EB14
lbl_8008EAC4:
/* 8008EAC4 0008B6A4  38 84 00 0B */	addi r4, r4, 0xb
/* 8008EAC8 0008B6A8  38 A0 00 00 */	li r5, 0
/* 8008EACC 0008B6AC  48 03 15 05 */	bl func_800BFFD0
/* 8008EAD0 0008B6B0  7C 7F 1B 78 */	mr r31, r3
/* 8008EAD4 0008B6B4  48 00 00 50 */	b lbl_8008EB24
lbl_8008EAD8:
/* 8008EAD8 0008B6B8  38 84 00 0F */	addi r4, r4, 0xf
/* 8008EADC 0008B6BC  38 A0 00 00 */	li r5, 0
/* 8008EAE0 0008B6C0  48 03 14 F1 */	bl func_800BFFD0
/* 8008EAE4 0008B6C4  7C 7F 1B 78 */	mr r31, r3
/* 8008EAE8 0008B6C8  48 00 00 3C */	b lbl_8008EB24
lbl_8008EAEC:
/* 8008EAEC 0008B6CC  38 84 00 1F */	addi r4, r4, 0x1f
/* 8008EAF0 0008B6D0  38 A0 00 00 */	li r5, 0
/* 8008EAF4 0008B6D4  48 03 14 DD */	bl func_800BFFD0
/* 8008EAF8 0008B6D8  7C 7F 1B 78 */	mr r31, r3
/* 8008EAFC 0008B6DC  48 00 00 28 */	b lbl_8008EB24
lbl_8008EB00:
/* 8008EB00 0008B6E0  38 84 00 23 */	addi r4, r4, 0x23
/* 8008EB04 0008B6E4  38 A0 00 00 */	li r5, 0
/* 8008EB08 0008B6E8  48 03 14 C9 */	bl func_800BFFD0
/* 8008EB0C 0008B6EC  7C 7F 1B 78 */	mr r31, r3
/* 8008EB10 0008B6F0  48 00 00 14 */	b lbl_8008EB24
lbl_8008EB14:
/* 8008EB14 0008B6F4  38 80 00 04 */	li r4, 4
/* 8008EB18 0008B6F8  38 A0 00 00 */	li r5, 0
/* 8008EB1C 0008B6FC  48 03 14 B5 */	bl func_800BFFD0
/* 8008EB20 0008B700  7C 7F 1B 78 */	mr r31, r3
lbl_8008EB24:
/* 8008EB24 0008B704  2C 1F 00 00 */	cmpwi r31, 0
/* 8008EB28 0008B708  41 82 00 0C */	beq lbl_8008EB34
/* 8008EB2C 0008B70C  7F A3 EB 78 */	mr r3, r29
/* 8008EB30 0008B710  48 03 18 D9 */	bl func_800C0408
lbl_8008EB34:
/* 8008EB34 0008B714  7F C3 F3 78 */	mr r3, r30
/* 8008EB38 0008B718  4B FF 19 C5 */	bl func_800804FC
/* 8008EB3C 0008B71C  80 01 00 34 */	lwz r0, 0x34(r1)
/* 8008EB40 0008B720  83 E1 00 2C */	lwz r31, 0x2c(r1)
/* 8008EB44 0008B724  83 C1 00 28 */	lwz r30, 0x28(r1)
/* 8008EB48 0008B728  83 A1 00 24 */	lwz r29, 0x24(r1)
/* 8008EB4C 0008B72C  38 21 00 30 */	addi r1, r1, 0x30
/* 8008EB50 0008B730  7C 08 03 A6 */	mtlr r0
/* 8008EB54 0008B734  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

#pragma push
asm void func_8008EB58(HSD_GObj* fighter_gobj)
{ // clang-format off
    nofralloc
/* 8008EB58 0008B738  7C 08 02 A6 */	mflr r0
/* 8008EB5C 0008B73C  90 01 00 04 */	stw r0, 4(r1)
/* 8008EB60 0008B740  94 21 FF D0 */	stwu r1, -0x30(r1)
/* 8008EB64 0008B744  93 E1 00 2C */	stw r31, 0x2c(r1)
/* 8008EB68 0008B748  93 C1 00 28 */	stw r30, 0x28(r1)
/* 8008EB6C 0008B74C  7C 7E 1B 78 */	mr r30, r3
/* 8008EB70 0008B750  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 8008EB74 0008B754  C0 02 8A F4 */	lfs f0, lbl_804D84D4(r2)
/* 8008EB78 0008B758  C0 5F 18 50 */	lfs f2, 0x1850(r31)
/* 8008EB7C 0008B75C  FC 00 10 00 */	fcmpu cr0, f0, f2
/* 8008EB80 0008B760  41 82 00 30 */	beq lbl_8008EBB0
/* 8008EB84 0008B764  88 7F 22 1A */	lbz r3, 0x221a(r31)
/* 8008EB88 0008B768  54 60 DF FF */	rlwinm. r0, r3, 0x1b, 0x1f, 0x1f
/* 8008EB8C 0008B76C  41 82 00 2C */	beq lbl_8008EBB8
/* 8008EB90 0008B770  54 60 E7 FF */	rlwinm. r0, r3, 0x1c, 0x1f, 0x1f
/* 8008EB94 0008B774  41 82 00 24 */	beq lbl_8008EBB8
/* 8008EB98 0008B778  80 6D AE B4 */	lwz r3, p_ftCommonData(r13)
/* 8008EB9C 0008B77C  C0 3F 18 A8 */	lfs f1, 0x18a8(r31)
/* 8008EBA0 0008B780  C0 03 01 40 */	lfs f0, 0x140(r3)
/* 8008EBA4 0008B784  EC 01 00 2A */	fadds f0, f1, f0
/* 8008EBA8 0008B788  FC 02 00 40 */	fcmpo cr0, f2, f0
/* 8008EBAC 0008B78C  40 80 00 0C */	bge lbl_8008EBB8
lbl_8008EBB0:
/* 8008EBB0 0008B790  38 00 00 01 */	li r0, 1
/* 8008EBB4 0008B794  48 00 00 08 */	b lbl_8008EBBC
lbl_8008EBB8:
/* 8008EBB8 0008B798  38 00 00 00 */	li r0, 0
lbl_8008EBBC:
/* 8008EBBC 0008B79C  2C 00 00 00 */	cmpwi r0, 0
/* 8008EBC0 0008B7A0  41 82 00 B8 */	beq lbl_8008EC78
/* 8008EBC4 0008B7A4  7F C3 F3 78 */	mr r3, r30
/* 8008EBC8 0008B7A8  48 03 A1 39 */	bl func_800C8D00
/* 8008EBCC 0008B7AC  80 1F 00 10 */	lwz r0, 0x10(r31)
/* 8008EBD0 0008B7B0  2C 00 00 E0 */	cmpwi r0, 0xe0
/* 8008EBD4 0008B7B4  41 82 00 0C */	beq lbl_8008EBE0
/* 8008EBD8 0008B7B8  2C 00 00 E1 */	cmpwi r0, 0xe1
/* 8008EBDC 0008B7BC  40 82 00 0C */	bne lbl_8008EBE8
lbl_8008EBE0:
/* 8008EBE0 0008B7C0  7F C3 F3 78 */	mr r3, r30
/* 8008EBE4 0008B7C4  48 04 D6 A1 */	bl func_800DC284
lbl_8008EBE8:
/* 8008EBE8 0008B7C8  80 1F 00 10 */	lwz r0, 0x10(r31)
/* 8008EBEC 0008B7CC  2C 00 00 E3 */	cmpwi r0, 0xe3
/* 8008EBF0 0008B7D0  41 82 00 0C */	beq lbl_8008EBFC
/* 8008EBF4 0008B7D4  2C 00 00 E4 */	cmpwi r0, 0xe4
/* 8008EBF8 0008B7D8  40 82 00 0C */	bne lbl_8008EC04
lbl_8008EBFC:
/* 8008EBFC 0008B7DC  7F C3 F3 78 */	mr r3, r30
/* 8008EC00 0008B7E0  48 04 D7 A5 */	bl func_800DC3A4
lbl_8008EC04:
/* 8008EC04 0008B7E4  80 6D AE B4 */	lwz r3, p_ftCommonData(r13)
/* 8008EC08 0008B7E8  C0 5F 18 50 */	lfs f2, 0x1850(r31)
/* 8008EC0C 0008B7EC  C0 23 01 54 */	lfs f1, 0x154(r3)
/* 8008EC10 0008B7F0  C0 03 01 58 */	lfs f0, 0x158(r3)
/* 8008EC14 0008B7F4  EC 22 00 72 */	fmuls f1, f2, f1
/* 8008EC18 0008B7F8  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8008EC1C 0008B7FC  40 80 00 0C */	bge lbl_8008EC28
/* 8008EC20 0008B800  38 A0 00 00 */	li r5, 0
/* 8008EC24 0008B804  48 00 00 30 */	b lbl_8008EC54
lbl_8008EC28:
/* 8008EC28 0008B808  C0 03 01 5C */	lfs f0, 0x15c(r3)
/* 8008EC2C 0008B80C  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8008EC30 0008B810  40 80 00 0C */	bge lbl_8008EC3C
/* 8008EC34 0008B814  38 A0 00 01 */	li r5, 1
/* 8008EC38 0008B818  48 00 00 1C */	b lbl_8008EC54
lbl_8008EC3C:
/* 8008EC3C 0008B81C  C0 03 01 60 */	lfs f0, 0x160(r3)
/* 8008EC40 0008B820  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8008EC44 0008B824  40 80 00 0C */	bge lbl_8008EC50
/* 8008EC48 0008B828  38 A0 00 02 */	li r5, 2
/* 8008EC4C 0008B82C  48 00 00 08 */	b lbl_8008EC54
lbl_8008EC50:
/* 8008EC50 0008B830  38 A0 00 03 */	li r5, 3
lbl_8008EC54:
/* 8008EC54 0008B834  80 9F 18 60 */	lwz r4, 0x1860(r31)
/* 8008EC58 0008B838  7F C3 F3 78 */	mr r3, r30
/* 8008EC5C 0008B83C  4B FF ED F1 */	bl func_8008DA4C
/* 8008EC60 0008B840  2C 03 00 00 */	cmpwi r3, 0
/* 8008EC64 0008B844  41 82 00 0C */	beq lbl_8008EC70
/* 8008EC68 0008B848  7F C3 F3 78 */	mr r3, r30
/* 8008EC6C 0008B84C  48 03 17 9D */	bl func_800C0408
lbl_8008EC70:
/* 8008EC70 0008B850  7F E3 FB 78 */	mr r3, r31
/* 8008EC74 0008B854  4B FF 18 89 */	bl func_800804FC
lbl_8008EC78:
/* 8008EC78 0008B858  80 01 00 34 */	lwz r0, 0x34(r1)
/* 8008EC7C 0008B85C  83 E1 00 2C */	lwz r31, 0x2c(r1)
/* 8008EC80 0008B860  83 C1 00 28 */	lwz r30, 0x28(r1)
/* 8008EC84 0008B864  38 21 00 30 */	addi r1, r1, 0x30
/* 8008EC88 0008B868  7C 08 03 A6 */	mtlr r0
/* 8008EC8C 0008B86C  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

extern unk_t func_800C3598();
extern unk_t func_800C74F4();
extern unk_t func_80091030();
extern unk_t func_800C0CB8();
extern unk_t func_8009F0F0();
extern unk_t func_800DCFD4();
extern unk_t func_800DE2F0();
extern unk_t func_800DCE34();
extern unk_t func_800DE854();
extern unk_t func_800D2FA4();
extern unk_t func_800C44CC();
extern unk_t func_800C3538();

#pragma push
asm void func_8008EC90(HSD_GObj* fighter_gobj)
{ // clang-format off
    nofralloc
/* 8008EC90 0008B870  7C 08 02 A6 */	mflr r0
/* 8008EC94 0008B874  90 01 00 04 */	stw r0, 4(r1)
/* 8008EC98 0008B878  94 21 FF 50 */	stwu r1, -0xb0(r1)
/* 8008EC9C 0008B87C  DB E1 00 A8 */	stfd f31, 0xa8(r1)
/* 8008ECA0 0008B880  BF 61 00 94 */	stmw r27, 0x94(r1)
/* 8008ECA4 0008B884  7C 7F 1B 78 */	mr r31, r3
/* 8008ECA8 0008B888  3B C0 00 00 */	li r30, 0
/* 8008ECAC 0008B88C  83 A3 00 2C */	lwz r29, 0x2c(r3)
/* 8008ECB0 0008B890  C3 E2 8A F4 */	lfs f31, lbl_804D84D4(r2)
/* 8008ECB4 0008B894  88 7D 22 20 */	lbz r3, 0x2220(r29)
/* 8008ECB8 0008B898  54 60 E7 FF */	rlwinm. r0, r3, 0x1c, 0x1f, 0x1f
/* 8008ECBC 0008B89C  40 82 00 18 */	bne lbl_8008ECD4
/* 8008ECC0 0008B8A0  54 60 EF FF */	rlwinm. r0, r3, 0x1d, 0x1f, 0x1f
/* 8008ECC4 0008B8A4  40 82 00 10 */	bne lbl_8008ECD4
/* 8008ECC8 0008B8A8  C0 1D 18 50 */	lfs f0, 0x1850(r29)
/* 8008ECCC 0008B8AC  FC 00 F8 00 */	fcmpu cr0, f0, f31
/* 8008ECD0 0008B8B0  40 82 00 BC */	bne lbl_8008ED8C
lbl_8008ECD4:
/* 8008ECD4 0008B8B4  7F E3 FB 78 */	mr r3, r31
/* 8008ECD8 0008B8B8  48 03 A0 29 */	bl func_800C8D00
/* 8008ECDC 0008B8BC  80 1D 00 10 */	lwz r0, 0x10(r29)
/* 8008ECE0 0008B8C0  2C 00 00 E0 */	cmpwi r0, 0xe0
/* 8008ECE4 0008B8C4  41 82 00 0C */	beq lbl_8008ECF0
/* 8008ECE8 0008B8C8  2C 00 00 E1 */	cmpwi r0, 0xe1
/* 8008ECEC 0008B8CC  40 82 00 0C */	bne lbl_8008ECF8
lbl_8008ECF0:
/* 8008ECF0 0008B8D0  7F E3 FB 78 */	mr r3, r31
/* 8008ECF4 0008B8D4  48 04 D5 91 */	bl func_800DC284
lbl_8008ECF8:
/* 8008ECF8 0008B8D8  80 1D 00 10 */	lwz r0, 0x10(r29)
/* 8008ECFC 0008B8DC  2C 00 00 E3 */	cmpwi r0, 0xe3
/* 8008ED00 0008B8E0  41 82 00 0C */	beq lbl_8008ED0C
/* 8008ED04 0008B8E4  2C 00 00 E4 */	cmpwi r0, 0xe4
/* 8008ED08 0008B8E8  40 82 00 0C */	bne lbl_8008ED14
lbl_8008ED0C:
/* 8008ED0C 0008B8EC  7F E3 FB 78 */	mr r3, r31
/* 8008ED10 0008B8F0  48 04 D6 95 */	bl func_800DC3A4
lbl_8008ED14:
/* 8008ED14 0008B8F4  80 6D AE B4 */	lwz r3, p_ftCommonData(r13)
/* 8008ED18 0008B8F8  C0 5D 18 50 */	lfs f2, 0x1850(r29)
/* 8008ED1C 0008B8FC  C0 23 01 54 */	lfs f1, 0x154(r3)
/* 8008ED20 0008B900  C0 03 01 58 */	lfs f0, 0x158(r3)
/* 8008ED24 0008B904  EC 22 00 72 */	fmuls f1, f2, f1
/* 8008ED28 0008B908  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8008ED2C 0008B90C  40 80 00 0C */	bge lbl_8008ED38
/* 8008ED30 0008B910  38 A0 00 00 */	li r5, 0
/* 8008ED34 0008B914  48 00 00 30 */	b lbl_8008ED64
lbl_8008ED38:
/* 8008ED38 0008B918  C0 03 01 5C */	lfs f0, 0x15c(r3)
/* 8008ED3C 0008B91C  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8008ED40 0008B920  40 80 00 0C */	bge lbl_8008ED4C
/* 8008ED44 0008B924  38 A0 00 01 */	li r5, 1
/* 8008ED48 0008B928  48 00 00 1C */	b lbl_8008ED64
lbl_8008ED4C:
/* 8008ED4C 0008B92C  C0 03 01 60 */	lfs f0, 0x160(r3)
/* 8008ED50 0008B930  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8008ED54 0008B934  40 80 00 0C */	bge lbl_8008ED60
/* 8008ED58 0008B938  38 A0 00 02 */	li r5, 2
/* 8008ED5C 0008B93C  48 00 00 08 */	b lbl_8008ED64
lbl_8008ED60:
/* 8008ED60 0008B940  38 A0 00 03 */	li r5, 3
lbl_8008ED64:
/* 8008ED64 0008B944  80 9D 18 60 */	lwz r4, 0x1860(r29)
/* 8008ED68 0008B948  7F E3 FB 78 */	mr r3, r31
/* 8008ED6C 0008B94C  4B FF EC E1 */	bl func_8008DA4C
/* 8008ED70 0008B950  2C 03 00 00 */	cmpwi r3, 0
/* 8008ED74 0008B954  41 82 00 0C */	beq lbl_8008ED80
/* 8008ED78 0008B958  7F E3 FB 78 */	mr r3, r31
/* 8008ED7C 0008B95C  48 03 16 8D */	bl func_800C0408
lbl_8008ED80:
/* 8008ED80 0008B960  7F A3 EB 78 */	mr r3, r29
/* 8008ED84 0008B964  4B FF 17 79 */	bl func_800804FC
/* 8008ED88 0008B968  48 00 09 94 */	b lbl_8008F71C
lbl_8008ED8C:
/* 8008ED8C 0008B96C  80 1D 18 60 */	lwz r0, 0x1860(r29)
/* 8008ED90 0008B970  28 00 00 0A */	cmplwi r0, 0xa
/* 8008ED94 0008B974  40 82 00 1C */	bne lbl_8008EDB0
/* 8008ED98 0008B978  7F E3 FB 78 */	mr r3, r31
/* 8008ED9C 0008B97C  48 03 47 9D */	bl func_800C3538
/* 8008EDA0 0008B980  2C 03 00 00 */	cmpwi r3, 0
/* 8008EDA4 0008B984  40 82 09 78 */	bne lbl_8008F71C
/* 8008EDA8 0008B988  C3 FD 00 2C */	lfs f31, 0x2c(r29)
/* 8008EDAC 0008B98C  3B C0 00 01 */	li r30, 1
lbl_8008EDB0:
/* 8008EDB0 0008B990  7F E3 FB 78 */	mr r3, r31
/* 8008EDB4 0008B994  48 03 57 19 */	bl func_800C44CC
/* 8008EDB8 0008B998  2C 03 00 00 */	cmpwi r3, 0
/* 8008EDBC 0008B99C  40 82 09 60 */	bne lbl_8008F71C
/* 8008EDC0 0008B9A0  7F E3 FB 78 */	mr r3, r31
/* 8008EDC4 0008B9A4  48 04 41 E1 */	bl func_800D2FA4
/* 8008EDC8 0008B9A8  2C 03 00 00 */	cmpwi r3, 0
/* 8008EDCC 0008B9AC  40 82 09 50 */	bne lbl_8008F71C
/* 8008EDD0 0008B9B0  80 9D 1A 58 */	lwz r4, 0x1a58(r29)
/* 8008EDD4 0008B9B4  28 04 00 00 */	cmplwi r4, 0
/* 8008EDD8 0008B9B8  41 82 08 48 */	beq lbl_8008F620
/* 8008EDDC 0008B9BC  88 1D 22 1B */	lbz r0, 0x221b(r29)
/* 8008EDE0 0008B9C0  54 00 F7 FF */	rlwinm. r0, r0, 0x1e, 0x1f, 0x1f
/* 8008EDE4 0008B9C4  40 82 04 8C */	bne lbl_8008F270
/* 8008EDE8 0008B9C8  2C 1E 00 00 */	cmpwi r30, 0
/* 8008EDEC 0008B9CC  83 64 00 2C */	lwz r27, 0x2c(r4)
/* 8008EDF0 0008B9D0  7C 9C 23 78 */	mr r28, r4
/* 8008EDF4 0008B9D4  40 82 03 4C */	bne lbl_8008F140
/* 8008EDF8 0008B9D8  88 1D 22 1C */	lbz r0, 0x221c(r29)
/* 8008EDFC 0008B9DC  54 00 CF FF */	rlwinm. r0, r0, 0x19, 0x1f, 0x1f
/* 8008EE00 0008B9E0  41 82 00 0C */	beq lbl_8008EE0C
/* 8008EE04 0008B9E4  38 00 00 01 */	li r0, 1
/* 8008EE08 0008B9E8  48 00 00 40 */	b lbl_8008EE48
lbl_8008EE0C:
/* 8008EE0C 0008B9EC  80 6D AE B4 */	lwz r3, p_ftCommonData(r13)
/* 8008EE10 0008B9F0  3C 00 43 30 */	lis r0, 0x4330
/* 8008EE14 0008B9F4  C8 22 8B 00 */	lfd f1, lbl_804D84E0(r2)
/* 8008EE18 0008B9F8  80 63 03 C0 */	lwz r3, 0x3c0(r3)
/* 8008EE1C 0008B9FC  C0 5D 18 38 */	lfs f2, 0x1838(r29)
/* 8008EE20 0008BA00  6C 63 80 00 */	xoris r3, r3, 0x8000
/* 8008EE24 0008BA04  90 61 00 8C */	stw r3, 0x8c(r1)
/* 8008EE28 0008BA08  90 01 00 88 */	stw r0, 0x88(r1)
/* 8008EE2C 0008BA0C  C8 01 00 88 */	lfd f0, 0x88(r1)
/* 8008EE30 0008BA10  EC 00 08 28 */	fsubs f0, f0, f1
/* 8008EE34 0008BA14  FC 02 00 40 */	fcmpo cr0, f2, f0
/* 8008EE38 0008BA18  40 80 00 0C */	bge lbl_8008EE44
/* 8008EE3C 0008BA1C  38 00 00 01 */	li r0, 1
/* 8008EE40 0008BA20  48 00 00 08 */	b lbl_8008EE48
lbl_8008EE44:
/* 8008EE44 0008BA24  38 00 00 00 */	li r0, 0
lbl_8008EE48:
/* 8008EE48 0008BA28  2C 00 00 00 */	cmpwi r0, 0
/* 8008EE4C 0008BA2C  41 82 02 F4 */	beq lbl_8008F140
/* 8008EE50 0008BA30  C0 5B 18 50 */	lfs f2, 0x1850(r27)
/* 8008EE54 0008BA34  C0 02 8A F4 */	lfs f0, lbl_804D84D4(r2)
/* 8008EE58 0008BA38  FC 02 00 00 */	fcmpu cr0, f2, f0
/* 8008EE5C 0008BA3C  41 82 01 BC */	beq lbl_8008F018
/* 8008EE60 0008BA40  FC 00 10 00 */	fcmpu cr0, f0, f2
/* 8008EE64 0008BA44  40 82 00 0C */	bne lbl_8008EE70
/* 8008EE68 0008BA48  38 00 00 01 */	li r0, 1
/* 8008EE6C 0008BA4C  48 00 00 3C */	b lbl_8008EEA8
lbl_8008EE70:
/* 8008EE70 0008BA50  88 7B 22 1A */	lbz r3, 0x221a(r27)
/* 8008EE74 0008BA54  54 60 DF FF */	rlwinm. r0, r3, 0x1b, 0x1f, 0x1f
/* 8008EE78 0008BA58  41 82 00 2C */	beq lbl_8008EEA4
/* 8008EE7C 0008BA5C  54 60 E7 FF */	rlwinm. r0, r3, 0x1c, 0x1f, 0x1f
/* 8008EE80 0008BA60  41 82 00 24 */	beq lbl_8008EEA4
/* 8008EE84 0008BA64  80 6D AE B4 */	lwz r3, p_ftCommonData(r13)
/* 8008EE88 0008BA68  C0 3B 18 A8 */	lfs f1, 0x18a8(r27)
/* 8008EE8C 0008BA6C  C0 03 01 40 */	lfs f0, 0x140(r3)
/* 8008EE90 0008BA70  EC 01 00 2A */	fadds f0, f1, f0
/* 8008EE94 0008BA74  FC 02 00 40 */	fcmpo cr0, f2, f0
/* 8008EE98 0008BA78  40 80 00 0C */	bge lbl_8008EEA4
/* 8008EE9C 0008BA7C  38 00 00 01 */	li r0, 1
/* 8008EEA0 0008BA80  48 00 00 08 */	b lbl_8008EEA8
lbl_8008EEA4:
/* 8008EEA4 0008BA84  38 00 00 00 */	li r0, 0
lbl_8008EEA8:
/* 8008EEA8 0008BA88  2C 00 00 00 */	cmpwi r0, 0
/* 8008EEAC 0008BA8C  41 82 00 D8 */	beq lbl_8008EF84
/* 8008EEB0 0008BA90  83 9F 00 2C */	lwz r28, 0x2c(r31)
/* 8008EEB4 0008BA94  7F E3 FB 78 */	mr r3, r31
/* 8008EEB8 0008BA98  48 03 9E 49 */	bl func_800C8D00
/* 8008EEBC 0008BA9C  80 1C 00 10 */	lwz r0, 0x10(r28)
/* 8008EEC0 0008BAA0  2C 00 00 E0 */	cmpwi r0, 0xe0
/* 8008EEC4 0008BAA4  41 82 00 0C */	beq lbl_8008EED0
/* 8008EEC8 0008BAA8  2C 00 00 E1 */	cmpwi r0, 0xe1
/* 8008EECC 0008BAAC  40 82 00 0C */	bne lbl_8008EED8
lbl_8008EED0:
/* 8008EED0 0008BAB0  7F E3 FB 78 */	mr r3, r31
/* 8008EED4 0008BAB4  48 04 D3 B1 */	bl func_800DC284
lbl_8008EED8:
/* 8008EED8 0008BAB8  80 1C 00 10 */	lwz r0, 0x10(r28)
/* 8008EEDC 0008BABC  2C 00 00 E3 */	cmpwi r0, 0xe3
/* 8008EEE0 0008BAC0  41 82 00 0C */	beq lbl_8008EEEC
/* 8008EEE4 0008BAC4  2C 00 00 E4 */	cmpwi r0, 0xe4
/* 8008EEE8 0008BAC8  40 82 00 0C */	bne lbl_8008EEF4
lbl_8008EEEC:
/* 8008EEEC 0008BACC  7F E3 FB 78 */	mr r3, r31
/* 8008EEF0 0008BAD0  48 04 D4 B5 */	bl func_800DC3A4
lbl_8008EEF4:
/* 8008EEF4 0008BAD4  80 6D AE B4 */	lwz r3, p_ftCommonData(r13)
/* 8008EEF8 0008BAD8  C0 5C 18 50 */	lfs f2, 0x1850(r28)
/* 8008EEFC 0008BADC  C0 23 01 54 */	lfs f1, 0x154(r3)
/* 8008EF00 0008BAE0  C0 03 01 58 */	lfs f0, 0x158(r3)
/* 8008EF04 0008BAE4  EC 22 00 72 */	fmuls f1, f2, f1
/* 8008EF08 0008BAE8  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8008EF0C 0008BAEC  40 80 00 0C */	bge lbl_8008EF18
/* 8008EF10 0008BAF0  38 A0 00 00 */	li r5, 0
/* 8008EF14 0008BAF4  48 00 00 30 */	b lbl_8008EF44
lbl_8008EF18:
/* 8008EF18 0008BAF8  C0 03 01 5C */	lfs f0, 0x15c(r3)
/* 8008EF1C 0008BAFC  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8008EF20 0008BB00  40 80 00 0C */	bge lbl_8008EF2C
/* 8008EF24 0008BB04  38 A0 00 01 */	li r5, 1
/* 8008EF28 0008BB08  48 00 00 1C */	b lbl_8008EF44
lbl_8008EF2C:
/* 8008EF2C 0008BB0C  C0 03 01 60 */	lfs f0, 0x160(r3)
/* 8008EF30 0008BB10  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8008EF34 0008BB14  40 80 00 0C */	bge lbl_8008EF40
/* 8008EF38 0008BB18  38 A0 00 02 */	li r5, 2
/* 8008EF3C 0008BB1C  48 00 00 08 */	b lbl_8008EF44
lbl_8008EF40:
/* 8008EF40 0008BB20  38 A0 00 03 */	li r5, 3
lbl_8008EF44:
/* 8008EF44 0008BB24  80 9C 18 60 */	lwz r4, 0x1860(r28)
/* 8008EF48 0008BB28  7F E3 FB 78 */	mr r3, r31
/* 8008EF4C 0008BB2C  4B FF EB 01 */	bl func_8008DA4C
/* 8008EF50 0008BB30  2C 03 00 00 */	cmpwi r3, 0
/* 8008EF54 0008BB34  41 82 00 0C */	beq lbl_8008EF60
/* 8008EF58 0008BB38  7F E3 FB 78 */	mr r3, r31
/* 8008EF5C 0008BB3C  48 03 14 AD */	bl func_800C0408
lbl_8008EF60:
/* 8008EF60 0008BB40  7F 83 E3 78 */	mr r3, r28
/* 8008EF64 0008BB44  4B FF 15 99 */	bl func_800804FC
/* 8008EF68 0008BB48  80 7B 18 3C */	lwz r3, 0x183c(r27)
/* 8008EF6C 0008BB4C  38 00 00 03 */	li r0, 3
/* 8008EF70 0008BB50  90 7D 18 3C */	stw r3, 0x183c(r29)
/* 8008EF74 0008BB54  C0 1B 19 60 */	lfs f0, 0x1960(r27)
/* 8008EF78 0008BB58  D0 1D 19 60 */	stfs f0, 0x1960(r29)
/* 8008EF7C 0008BB5C  90 1B 18 28 */	stw r0, 0x1828(r27)
/* 8008EF80 0008BB60  48 00 07 9C */	b lbl_8008F71C
lbl_8008EF84:
/* 8008EF84 0008BB64  7F E3 FB 78 */	mr r3, r31
/* 8008EF88 0008BB68  48 04 F8 CD */	bl func_800DE854
/* 8008EF8C 0008BB6C  38 7C 00 00 */	addi r3, r28, 0
/* 8008EF90 0008BB70  38 9F 00 00 */	addi r4, r31, 0
/* 8008EF94 0008BB74  48 04 DE A1 */	bl func_800DCE34
/* 8008EF98 0008BB78  7F E3 FB 78 */	mr r3, r31
/* 8008EF9C 0008BB7C  4B FE EB BD */	bl func_8007DB58
/* 8008EFA0 0008BB80  80 9F 00 2C */	lwz r4, 0x2c(r31)
/* 8008EFA4 0008BB84  88 04 22 1D */	lbz r0, 0x221d(r4)
/* 8008EFA8 0008BB88  54 00 07 FF */	clrlwi. r0, r0, 0x1f
/* 8008EFAC 0008BB8C  41 82 00 10 */	beq lbl_8008EFBC
/* 8008EFB0 0008BB90  80 6D AE B4 */	lwz r3, p_ftCommonData(r13)
/* 8008EFB4 0008BB94  80 03 04 98 */	lwz r0, 0x498(r3)
/* 8008EFB8 0008BB98  90 04 20 64 */	stw r0, 0x2064(r4)
lbl_8008EFBC:
/* 8008EFBC 0008BB9C  80 64 18 60 */	lwz r3, 0x1860(r4)
/* 8008EFC0 0008BBA0  28 03 00 06 */	cmplwi r3, 6
/* 8008EFC4 0008BBA4  41 82 00 0C */	beq lbl_8008EFD0
/* 8008EFC8 0008BBA8  28 03 00 07 */	cmplwi r3, 7
/* 8008EFCC 0008BBAC  40 82 00 30 */	bne lbl_8008EFFC
lbl_8008EFD0:
/* 8008EFD0 0008BBB0  88 04 22 28 */	lbz r0, 0x2228(r4)
/* 8008EFD4 0008BBB4  54 00 DF FF */	rlwinm. r0, r0, 0x1b, 0x1f, 0x1f
/* 8008EFD8 0008BBB8  40 82 00 24 */	bne lbl_8008EFFC
/* 8008EFDC 0008BBBC  28 03 00 06 */	cmplwi r3, 6
/* 8008EFE0 0008BBC0  40 82 00 0C */	bne lbl_8008EFEC
/* 8008EFE4 0008BBC4  38 80 00 00 */	li r4, 0
/* 8008EFE8 0008BBC8  48 00 00 08 */	b lbl_8008EFF0
lbl_8008EFEC:
/* 8008EFEC 0008BBCC  38 80 00 01 */	li r4, 1
lbl_8008EFF0:
/* 8008EFF0 0008BBD0  7F E3 FB 78 */	mr r3, r31
/* 8008EFF4 0008BBD4  48 03 41 99 */	bl func_800C318C
/* 8008EFF8 0008BBD8  48 00 00 14 */	b lbl_8008F00C
lbl_8008EFFC:
/* 8008EFFC 0008BBDC  FC 20 F8 90 */	fmr f1, f31
/* 8008F000 0008BBE0  38 7F 00 00 */	addi r3, r31, 0
/* 8008F004 0008BBE4  38 80 FF FF */	li r4, -1
/* 8008F008 0008BBE8  4B FF EC D9 */	bl func_8008DCE0
lbl_8008F00C:
/* 8008F00C 0008BBEC  38 00 00 01 */	li r0, 1
/* 8008F010 0008BBF0  90 1B 18 28 */	stw r0, 0x1828(r27)
/* 8008F014 0008BBF4  48 00 07 08 */	b lbl_8008F71C
lbl_8008F018:
/* 8008F018 0008BBF8  80 7D 18 3C */	lwz r3, 0x183c(r29)
/* 8008F01C 0008BBFC  2C 03 00 00 */	cmpwi r3, 0
/* 8008F020 0008BC00  41 82 00 58 */	beq lbl_8008F078
/* 8008F024 0008BC04  80 9B 00 10 */	lwz r4, 0x10(r27)
/* 8008F028 0008BC08  C0 3B 19 60 */	lfs f1, 0x1960(r27)
/* 8008F02C 0008BC0C  4B FE EA 49 */	bl func_8007DA74
/* 8008F030 0008BC10  D0 3B 19 5C */	stfs f1, 0x195c(r27)
/* 8008F034 0008BC14  38 60 00 01 */	li r3, 1
/* 8008F038 0008BC18  88 1B 22 1A */	lbz r0, 0x221a(r27)
/* 8008F03C 0008BC1C  50 60 2E B4 */	rlwimi r0, r3, 5, 0x1a, 0x1a
/* 8008F040 0008BC20  98 1B 22 1A */	stb r0, 0x221a(r27)
/* 8008F044 0008BC24  88 1B 22 19 */	lbz r0, 0x2219(r27)
/* 8008F048 0008BC28  54 00 F7 FF */	rlwinm. r0, r0, 0x1e, 0x1f, 0x1f
/* 8008F04C 0008BC2C  40 82 00 2C */	bne lbl_8008F078
/* 8008F050 0008BC30  81 9B 21 D4 */	lwz r12, 0x21d4(r27)
/* 8008F054 0008BC34  28 0C 00 00 */	cmplwi r12, 0
/* 8008F058 0008BC38  41 82 00 10 */	beq lbl_8008F068
/* 8008F05C 0008BC3C  7D 88 03 A6 */	mtlr r12
/* 8008F060 0008BC40  38 7F 00 00 */	addi r3, r31, 0
/* 8008F064 0008BC44  4E 80 00 21 */	blrl 
lbl_8008F068:
/* 8008F068 0008BC48  88 1B 22 19 */	lbz r0, 0x2219(r27)
/* 8008F06C 0008BC4C  38 60 00 01 */	li r3, 1
/* 8008F070 0008BC50  50 60 17 7A */	rlwimi r0, r3, 2, 0x1d, 0x1d
/* 8008F074 0008BC54  98 1B 22 19 */	stb r0, 0x2219(r27)
lbl_8008F078:
/* 8008F078 0008BC58  38 00 00 00 */	li r0, 0
/* 8008F07C 0008BC5C  90 1D 06 6C */	stw r0, 0x66c(r29)
/* 8008F080 0008BC60  7F E3 FB 78 */	mr r3, r31
/* 8008F084 0008BC64  90 1D 06 68 */	stw r0, 0x668(r29)
/* 8008F088 0008BC68  83 7F 00 2C */	lwz r27, 0x2c(r31)
/* 8008F08C 0008BC6C  48 03 9C 75 */	bl func_800C8D00
/* 8008F090 0008BC70  80 1B 00 10 */	lwz r0, 0x10(r27)
/* 8008F094 0008BC74  2C 00 00 E0 */	cmpwi r0, 0xe0
/* 8008F098 0008BC78  41 82 00 0C */	beq lbl_8008F0A4
/* 8008F09C 0008BC7C  2C 00 00 E1 */	cmpwi r0, 0xe1
/* 8008F0A0 0008BC80  40 82 00 0C */	bne lbl_8008F0AC
lbl_8008F0A4:
/* 8008F0A4 0008BC84  7F E3 FB 78 */	mr r3, r31
/* 8008F0A8 0008BC88  48 04 D1 DD */	bl func_800DC284
lbl_8008F0AC:
/* 8008F0AC 0008BC8C  80 1B 00 10 */	lwz r0, 0x10(r27)
/* 8008F0B0 0008BC90  2C 00 00 E3 */	cmpwi r0, 0xe3
/* 8008F0B4 0008BC94  41 82 00 0C */	beq lbl_8008F0C0
/* 8008F0B8 0008BC98  2C 00 00 E4 */	cmpwi r0, 0xe4
/* 8008F0BC 0008BC9C  40 82 00 0C */	bne lbl_8008F0C8
lbl_8008F0C0:
/* 8008F0C0 0008BCA0  7F E3 FB 78 */	mr r3, r31
/* 8008F0C4 0008BCA4  48 04 D2 E1 */	bl func_800DC3A4
lbl_8008F0C8:
/* 8008F0C8 0008BCA8  80 6D AE B4 */	lwz r3, p_ftCommonData(r13)
/* 8008F0CC 0008BCAC  C0 5B 18 50 */	lfs f2, 0x1850(r27)
/* 8008F0D0 0008BCB0  C0 23 01 54 */	lfs f1, 0x154(r3)
/* 8008F0D4 0008BCB4  C0 03 01 58 */	lfs f0, 0x158(r3)
/* 8008F0D8 0008BCB8  EC 22 00 72 */	fmuls f1, f2, f1
/* 8008F0DC 0008BCBC  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8008F0E0 0008BCC0  40 80 00 0C */	bge lbl_8008F0EC
/* 8008F0E4 0008BCC4  38 A0 00 00 */	li r5, 0
/* 8008F0E8 0008BCC8  48 00 00 30 */	b lbl_8008F118
lbl_8008F0EC:
/* 8008F0EC 0008BCCC  C0 03 01 5C */	lfs f0, 0x15c(r3)
/* 8008F0F0 0008BCD0  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8008F0F4 0008BCD4  40 80 00 0C */	bge lbl_8008F100
/* 8008F0F8 0008BCD8  38 A0 00 01 */	li r5, 1
/* 8008F0FC 0008BCDC  48 00 00 1C */	b lbl_8008F118
lbl_8008F100:
/* 8008F100 0008BCE0  C0 03 01 60 */	lfs f0, 0x160(r3)
/* 8008F104 0008BCE4  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8008F108 0008BCE8  40 80 00 0C */	bge lbl_8008F114
/* 8008F10C 0008BCEC  38 A0 00 02 */	li r5, 2
/* 8008F110 0008BCF0  48 00 00 08 */	b lbl_8008F118
lbl_8008F114:
/* 8008F114 0008BCF4  38 A0 00 03 */	li r5, 3
lbl_8008F118:
/* 8008F118 0008BCF8  80 9B 18 60 */	lwz r4, 0x1860(r27)
/* 8008F11C 0008BCFC  7F E3 FB 78 */	mr r3, r31
/* 8008F120 0008BD00  4B FF E9 2D */	bl func_8008DA4C
/* 8008F124 0008BD04  2C 03 00 00 */	cmpwi r3, 0
/* 8008F128 0008BD08  41 82 00 0C */	beq lbl_8008F134
/* 8008F12C 0008BD0C  7F E3 FB 78 */	mr r3, r31
/* 8008F130 0008BD10  48 03 12 D9 */	bl func_800C0408
lbl_8008F134:
/* 8008F134 0008BD14  7F 63 DB 78 */	mr r3, r27
/* 8008F138 0008BD18  4B FF 13 C5 */	bl func_800804FC
/* 8008F13C 0008BD1C  48 00 05 E0 */	b lbl_8008F71C
lbl_8008F140:
/* 8008F140 0008BD20  C0 3B 18 50 */	lfs f1, 0x1850(r27)
/* 8008F144 0008BD24  C0 02 8A F4 */	lfs f0, lbl_804D84D4(r2)
/* 8008F148 0008BD28  FC 01 00 00 */	fcmpu cr0, f1, f0
/* 8008F14C 0008BD2C  41 82 00 90 */	beq lbl_8008F1DC
/* 8008F150 0008BD30  38 7C 00 00 */	addi r3, r28, 0
/* 8008F154 0008BD34  38 9F 00 00 */	addi r4, r31, 0
/* 8008F158 0008BD38  48 04 DC DD */	bl func_800DCE34
/* 8008F15C 0008BD3C  7F E3 FB 78 */	mr r3, r31
/* 8008F160 0008BD40  4B FE E9 F9 */	bl func_8007DB58
/* 8008F164 0008BD44  80 9F 00 2C */	lwz r4, 0x2c(r31)
/* 8008F168 0008BD48  88 04 22 1D */	lbz r0, 0x221d(r4)
/* 8008F16C 0008BD4C  54 00 07 FF */	clrlwi. r0, r0, 0x1f
/* 8008F170 0008BD50  41 82 00 10 */	beq lbl_8008F180
/* 8008F174 0008BD54  80 6D AE B4 */	lwz r3, p_ftCommonData(r13)
/* 8008F178 0008BD58  80 03 04 98 */	lwz r0, 0x498(r3)
/* 8008F17C 0008BD5C  90 04 20 64 */	stw r0, 0x2064(r4)
lbl_8008F180:
/* 8008F180 0008BD60  80 64 18 60 */	lwz r3, 0x1860(r4)
/* 8008F184 0008BD64  28 03 00 06 */	cmplwi r3, 6
/* 8008F188 0008BD68  41 82 00 0C */	beq lbl_8008F194
/* 8008F18C 0008BD6C  28 03 00 07 */	cmplwi r3, 7
/* 8008F190 0008BD70  40 82 00 30 */	bne lbl_8008F1C0
lbl_8008F194:
/* 8008F194 0008BD74  88 04 22 28 */	lbz r0, 0x2228(r4)
/* 8008F198 0008BD78  54 00 DF FF */	rlwinm. r0, r0, 0x1b, 0x1f, 0x1f
/* 8008F19C 0008BD7C  40 82 00 24 */	bne lbl_8008F1C0
/* 8008F1A0 0008BD80  28 03 00 06 */	cmplwi r3, 6
/* 8008F1A4 0008BD84  40 82 00 0C */	bne lbl_8008F1B0
/* 8008F1A8 0008BD88  38 80 00 00 */	li r4, 0
/* 8008F1AC 0008BD8C  48 00 00 08 */	b lbl_8008F1B4
lbl_8008F1B0:
/* 8008F1B0 0008BD90  38 80 00 01 */	li r4, 1
lbl_8008F1B4:
/* 8008F1B4 0008BD94  7F E3 FB 78 */	mr r3, r31
/* 8008F1B8 0008BD98  48 03 3F D5 */	bl func_800C318C
/* 8008F1BC 0008BD9C  48 00 00 14 */	b lbl_8008F1D0
lbl_8008F1C0:
/* 8008F1C0 0008BDA0  FC 20 F8 90 */	fmr f1, f31
/* 8008F1C4 0008BDA4  38 7F 00 00 */	addi r3, r31, 0
/* 8008F1C8 0008BDA8  38 80 FF FF */	li r4, -1
/* 8008F1CC 0008BDAC  4B FF EB 15 */	bl func_8008DCE0
lbl_8008F1D0:
/* 8008F1D0 0008BDB0  38 00 00 01 */	li r0, 1
/* 8008F1D4 0008BDB4  90 1B 18 28 */	stw r0, 0x1828(r27)
/* 8008F1D8 0008BDB8  48 00 05 44 */	b lbl_8008F71C
lbl_8008F1DC:
/* 8008F1DC 0008BDBC  38 7C 00 00 */	addi r3, r28, 0
/* 8008F1E0 0008BDC0  38 9F 00 00 */	addi r4, r31, 0
/* 8008F1E4 0008BDC4  48 04 DC 51 */	bl func_800DCE34
/* 8008F1E8 0008BDC8  7F E3 FB 78 */	mr r3, r31
/* 8008F1EC 0008BDCC  4B FE E9 6D */	bl func_8007DB58
/* 8008F1F0 0008BDD0  80 9F 00 2C */	lwz r4, 0x2c(r31)
/* 8008F1F4 0008BDD4  88 04 22 1D */	lbz r0, 0x221d(r4)
/* 8008F1F8 0008BDD8  54 00 07 FF */	clrlwi. r0, r0, 0x1f
/* 8008F1FC 0008BDDC  41 82 00 10 */	beq lbl_8008F20C
/* 8008F200 0008BDE0  80 6D AE B4 */	lwz r3, p_ftCommonData(r13)
/* 8008F204 0008BDE4  80 03 04 98 */	lwz r0, 0x498(r3)
/* 8008F208 0008BDE8  90 04 20 64 */	stw r0, 0x2064(r4)
lbl_8008F20C:
/* 8008F20C 0008BDEC  80 64 18 60 */	lwz r3, 0x1860(r4)
/* 8008F210 0008BDF0  28 03 00 06 */	cmplwi r3, 6
/* 8008F214 0008BDF4  41 82 00 0C */	beq lbl_8008F220
/* 8008F218 0008BDF8  28 03 00 07 */	cmplwi r3, 7
/* 8008F21C 0008BDFC  40 82 00 30 */	bne lbl_8008F24C
lbl_8008F220:
/* 8008F220 0008BE00  88 04 22 28 */	lbz r0, 0x2228(r4)
/* 8008F224 0008BE04  54 00 DF FF */	rlwinm. r0, r0, 0x1b, 0x1f, 0x1f
/* 8008F228 0008BE08  40 82 00 24 */	bne lbl_8008F24C
/* 8008F22C 0008BE0C  28 03 00 06 */	cmplwi r3, 6
/* 8008F230 0008BE10  40 82 00 0C */	bne lbl_8008F23C
/* 8008F234 0008BE14  38 80 00 00 */	li r4, 0
/* 8008F238 0008BE18  48 00 00 08 */	b lbl_8008F240
lbl_8008F23C:
/* 8008F23C 0008BE1C  38 80 00 01 */	li r4, 1
lbl_8008F240:
/* 8008F240 0008BE20  7F E3 FB 78 */	mr r3, r31
/* 8008F244 0008BE24  48 03 3F 49 */	bl func_800C318C
/* 8008F248 0008BE28  48 00 00 14 */	b lbl_8008F25C
lbl_8008F24C:
/* 8008F24C 0008BE2C  FC 20 F8 90 */	fmr f1, f31
/* 8008F250 0008BE30  38 7F 00 00 */	addi r3, r31, 0
/* 8008F254 0008BE34  38 80 FF FF */	li r4, -1
/* 8008F258 0008BE38  4B FF EA 89 */	bl func_8008DCE0
lbl_8008F25C:
/* 8008F25C 0008BE3C  7F 83 E3 78 */	mr r3, r28
/* 8008F260 0008BE40  4B FE E8 F9 */	bl func_8007DB58
/* 8008F264 0008BE44  7F 83 E3 78 */	mr r3, r28
/* 8008F268 0008BE48  48 04 F0 89 */	bl func_800DE2F0
/* 8008F26C 0008BE4C  48 00 04 B0 */	b lbl_8008F71C
lbl_8008F270:
/* 8008F270 0008BE50  C0 02 8A F4 */	lfs f0, lbl_804D84D4(r2)
/* 8008F274 0008BE54  C0 5D 18 50 */	lfs f2, 0x1850(r29)
/* 8008F278 0008BE58  83 64 00 2C */	lwz r27, 0x2c(r4)
/* 8008F27C 0008BE5C  FC 00 10 00 */	fcmpu cr0, f0, f2
/* 8008F280 0008BE60  40 82 00 0C */	bne lbl_8008F28C
/* 8008F284 0008BE64  38 00 00 01 */	li r0, 1
/* 8008F288 0008BE68  48 00 00 3C */	b lbl_8008F2C4
lbl_8008F28C:
/* 8008F28C 0008BE6C  88 7D 22 1A */	lbz r3, 0x221a(r29)
/* 8008F290 0008BE70  54 60 DF FF */	rlwinm. r0, r3, 0x1b, 0x1f, 0x1f
/* 8008F294 0008BE74  41 82 00 2C */	beq lbl_8008F2C0
/* 8008F298 0008BE78  54 60 E7 FF */	rlwinm. r0, r3, 0x1c, 0x1f, 0x1f
/* 8008F29C 0008BE7C  41 82 00 24 */	beq lbl_8008F2C0
/* 8008F2A0 0008BE80  80 6D AE B4 */	lwz r3, p_ftCommonData(r13)
/* 8008F2A4 0008BE84  C0 3D 18 A8 */	lfs f1, 0x18a8(r29)
/* 8008F2A8 0008BE88  C0 03 01 40 */	lfs f0, 0x140(r3)
/* 8008F2AC 0008BE8C  EC 01 00 2A */	fadds f0, f1, f0
/* 8008F2B0 0008BE90  FC 02 00 40 */	fcmpo cr0, f2, f0
/* 8008F2B4 0008BE94  40 80 00 0C */	bge lbl_8008F2C0
/* 8008F2B8 0008BE98  38 00 00 01 */	li r0, 1
/* 8008F2BC 0008BE9C  48 00 00 08 */	b lbl_8008F2C4
lbl_8008F2C0:
/* 8008F2C0 0008BEA0  38 00 00 00 */	li r0, 0
lbl_8008F2C4:
/* 8008F2C4 0008BEA4  2C 00 00 00 */	cmpwi r0, 0
/* 8008F2C8 0008BEA8  41 82 01 C8 */	beq lbl_8008F490
/* 8008F2CC 0008BEAC  C0 3B 18 50 */	lfs f1, 0x1850(r27)
/* 8008F2D0 0008BEB0  C0 02 8A F4 */	lfs f0, lbl_804D84D4(r2)
/* 8008F2D4 0008BEB4  FC 01 00 00 */	fcmpu cr0, f1, f0
/* 8008F2D8 0008BEB8  41 82 01 5C */	beq lbl_8008F434
/* 8008F2DC 0008BEBC  88 1B 22 1C */	lbz r0, 0x221c(r27)
/* 8008F2E0 0008BEC0  54 00 CF FF */	rlwinm. r0, r0, 0x19, 0x1f, 0x1f
/* 8008F2E4 0008BEC4  41 82 00 0C */	beq lbl_8008F2F0
/* 8008F2E8 0008BEC8  38 00 00 01 */	li r0, 1
/* 8008F2EC 0008BECC  48 00 00 40 */	b lbl_8008F32C
lbl_8008F2F0:
/* 8008F2F0 0008BED0  80 6D AE B4 */	lwz r3, p_ftCommonData(r13)
/* 8008F2F4 0008BED4  3C 00 43 30 */	lis r0, 0x4330
/* 8008F2F8 0008BED8  C8 22 8B 00 */	lfd f1, lbl_804D84E0(r2)
/* 8008F2FC 0008BEDC  80 63 03 C0 */	lwz r3, 0x3c0(r3)
/* 8008F300 0008BEE0  C0 5B 18 38 */	lfs f2, 0x1838(r27)
/* 8008F304 0008BEE4  6C 63 80 00 */	xoris r3, r3, 0x8000
/* 8008F308 0008BEE8  90 61 00 8C */	stw r3, 0x8c(r1)
/* 8008F30C 0008BEEC  90 01 00 88 */	stw r0, 0x88(r1)
/* 8008F310 0008BEF0  C8 01 00 88 */	lfd f0, 0x88(r1)
/* 8008F314 0008BEF4  EC 00 08 28 */	fsubs f0, f0, f1
/* 8008F318 0008BEF8  FC 02 00 40 */	fcmpo cr0, f2, f0
/* 8008F31C 0008BEFC  40 80 00 0C */	bge lbl_8008F328
/* 8008F320 0008BF00  38 00 00 01 */	li r0, 1
/* 8008F324 0008BF04  48 00 00 08 */	b lbl_8008F32C
lbl_8008F328:
/* 8008F328 0008BF08  38 00 00 00 */	li r0, 0
lbl_8008F32C:
/* 8008F32C 0008BF0C  2C 00 00 00 */	cmpwi r0, 0
/* 8008F330 0008BF10  41 82 00 7C */	beq lbl_8008F3AC
/* 8008F334 0008BF14  80 1D 18 3C */	lwz r0, 0x183c(r29)
/* 8008F338 0008BF18  90 1B 18 3C */	stw r0, 0x183c(r27)
/* 8008F33C 0008BF1C  C0 1D 19 60 */	lfs f0, 0x1960(r29)
/* 8008F340 0008BF20  D0 1B 19 60 */	stfs f0, 0x1960(r27)
/* 8008F344 0008BF24  80 9F 00 2C */	lwz r4, 0x2c(r31)
/* 8008F348 0008BF28  C0 02 8A F4 */	lfs f0, lbl_804D84D4(r2)
/* 8008F34C 0008BF2C  C0 44 18 50 */	lfs f2, 0x1850(r4)
/* 8008F350 0008BF30  FC 00 10 00 */	fcmpu cr0, f0, f2
/* 8008F354 0008BF34  41 82 00 30 */	beq lbl_8008F384
/* 8008F358 0008BF38  88 64 22 1A */	lbz r3, 0x221a(r4)
/* 8008F35C 0008BF3C  54 60 DF FF */	rlwinm. r0, r3, 0x1b, 0x1f, 0x1f
/* 8008F360 0008BF40  41 82 00 2C */	beq lbl_8008F38C
/* 8008F364 0008BF44  54 60 E7 FF */	rlwinm. r0, r3, 0x1c, 0x1f, 0x1f
/* 8008F368 0008BF48  41 82 00 24 */	beq lbl_8008F38C
/* 8008F36C 0008BF4C  80 6D AE B4 */	lwz r3, p_ftCommonData(r13)
/* 8008F370 0008BF50  C0 24 18 A8 */	lfs f1, 0x18a8(r4)
/* 8008F374 0008BF54  C0 03 01 40 */	lfs f0, 0x140(r3)
/* 8008F378 0008BF58  EC 01 00 2A */	fadds f0, f1, f0
/* 8008F37C 0008BF5C  FC 02 00 40 */	fcmpo cr0, f2, f0
/* 8008F380 0008BF60  40 80 00 0C */	bge lbl_8008F38C
lbl_8008F384:
/* 8008F384 0008BF64  38 00 00 01 */	li r0, 1
/* 8008F388 0008BF68  48 00 00 08 */	b lbl_8008F390
lbl_8008F38C:
/* 8008F38C 0008BF6C  38 00 00 00 */	li r0, 0
lbl_8008F390:
/* 8008F390 0008BF70  2C 00 00 00 */	cmpwi r0, 0
/* 8008F394 0008BF74  41 82 00 0C */	beq lbl_8008F3A0
/* 8008F398 0008BF78  7F E3 FB 78 */	mr r3, r31
/* 8008F39C 0008BF7C  4B FF F6 35 */	bl func_8008E9D0
lbl_8008F3A0:
/* 8008F3A0 0008BF80  38 00 00 02 */	li r0, 2
/* 8008F3A4 0008BF84  90 1B 18 28 */	stw r0, 0x1828(r27)
/* 8008F3A8 0008BF88  48 00 03 74 */	b lbl_8008F71C
lbl_8008F3AC:
/* 8008F3AC 0008BF8C  7F E3 FB 78 */	mr r3, r31
/* 8008F3B0 0008BF90  48 04 DA 85 */	bl func_800DCE34
/* 8008F3B4 0008BF94  7F E3 FB 78 */	mr r3, r31
/* 8008F3B8 0008BF98  4B FE E7 A1 */	bl func_8007DB58
/* 8008F3BC 0008BF9C  80 9F 00 2C */	lwz r4, 0x2c(r31)
/* 8008F3C0 0008BFA0  88 04 22 1D */	lbz r0, 0x221d(r4)
/* 8008F3C4 0008BFA4  54 00 07 FF */	clrlwi. r0, r0, 0x1f
/* 8008F3C8 0008BFA8  41 82 00 10 */	beq lbl_8008F3D8
/* 8008F3CC 0008BFAC  80 6D AE B4 */	lwz r3, p_ftCommonData(r13)
/* 8008F3D0 0008BFB0  80 03 04 98 */	lwz r0, 0x498(r3)
/* 8008F3D4 0008BFB4  90 04 20 64 */	stw r0, 0x2064(r4)
lbl_8008F3D8:
/* 8008F3D8 0008BFB8  80 64 18 60 */	lwz r3, 0x1860(r4)
/* 8008F3DC 0008BFBC  28 03 00 06 */	cmplwi r3, 6
/* 8008F3E0 0008BFC0  41 82 00 0C */	beq lbl_8008F3EC
/* 8008F3E4 0008BFC4  28 03 00 07 */	cmplwi r3, 7
/* 8008F3E8 0008BFC8  40 82 00 30 */	bne lbl_8008F418
lbl_8008F3EC:
/* 8008F3EC 0008BFCC  88 04 22 28 */	lbz r0, 0x2228(r4)
/* 8008F3F0 0008BFD0  54 00 DF FF */	rlwinm. r0, r0, 0x1b, 0x1f, 0x1f
/* 8008F3F4 0008BFD4  40 82 00 24 */	bne lbl_8008F418
/* 8008F3F8 0008BFD8  28 03 00 06 */	cmplwi r3, 6
/* 8008F3FC 0008BFDC  40 82 00 0C */	bne lbl_8008F408
/* 8008F400 0008BFE0  38 80 00 00 */	li r4, 0
/* 8008F404 0008BFE4  48 00 00 08 */	b lbl_8008F40C
lbl_8008F408:
/* 8008F408 0008BFE8  38 80 00 01 */	li r4, 1
lbl_8008F40C:
/* 8008F40C 0008BFEC  7F E3 FB 78 */	mr r3, r31
/* 8008F410 0008BFF0  48 03 3D 7D */	bl func_800C318C
/* 8008F414 0008BFF4  48 00 00 14 */	b lbl_8008F428
lbl_8008F418:
/* 8008F418 0008BFF8  FC 20 F8 90 */	fmr f1, f31
/* 8008F41C 0008BFFC  38 7F 00 00 */	addi r3, r31, 0
/* 8008F420 0008C000  38 80 FF FF */	li r4, -1
/* 8008F424 0008C004  4B FF E8 BD */	bl func_8008DCE0
lbl_8008F428:
/* 8008F428 0008C008  38 00 00 01 */	li r0, 1
/* 8008F42C 0008C00C  90 1B 18 28 */	stw r0, 0x1828(r27)
/* 8008F430 0008C010  48 00 02 EC */	b lbl_8008F71C
lbl_8008F434:
/* 8008F434 0008C014  80 9F 00 2C */	lwz r4, 0x2c(r31)
/* 8008F438 0008C018  C0 44 18 50 */	lfs f2, 0x1850(r4)
/* 8008F43C 0008C01C  FC 00 10 00 */	fcmpu cr0, f0, f2
/* 8008F440 0008C020  41 82 00 30 */	beq lbl_8008F470
/* 8008F444 0008C024  88 64 22 1A */	lbz r3, 0x221a(r4)
/* 8008F448 0008C028  54 60 DF FF */	rlwinm. r0, r3, 0x1b, 0x1f, 0x1f
/* 8008F44C 0008C02C  41 82 00 2C */	beq lbl_8008F478
/* 8008F450 0008C030  54 60 E7 FF */	rlwinm. r0, r3, 0x1c, 0x1f, 0x1f
/* 8008F454 0008C034  41 82 00 24 */	beq lbl_8008F478
/* 8008F458 0008C038  80 6D AE B4 */	lwz r3, p_ftCommonData(r13)
/* 8008F45C 0008C03C  C0 24 18 A8 */	lfs f1, 0x18a8(r4)
/* 8008F460 0008C040  C0 03 01 40 */	lfs f0, 0x140(r3)
/* 8008F464 0008C044  EC 01 00 2A */	fadds f0, f1, f0
/* 8008F468 0008C048  FC 02 00 40 */	fcmpo cr0, f2, f0
/* 8008F46C 0008C04C  40 80 00 0C */	bge lbl_8008F478
lbl_8008F470:
/* 8008F470 0008C050  38 00 00 01 */	li r0, 1
/* 8008F474 0008C054  48 00 00 08 */	b lbl_8008F47C
lbl_8008F478:
/* 8008F478 0008C058  38 00 00 00 */	li r0, 0
lbl_8008F47C:
/* 8008F47C 0008C05C  2C 00 00 00 */	cmpwi r0, 0
/* 8008F480 0008C060  41 82 02 9C */	beq lbl_8008F71C
/* 8008F484 0008C064  7F E3 FB 78 */	mr r3, r31
/* 8008F488 0008C068  4B FF F5 49 */	bl func_8008E9D0
/* 8008F48C 0008C06C  48 00 02 90 */	b lbl_8008F71C
lbl_8008F490:
/* 8008F490 0008C070  C0 3B 18 50 */	lfs f1, 0x1850(r27)
/* 8008F494 0008C074  C0 02 8A F4 */	lfs f0, lbl_804D84D4(r2)
/* 8008F498 0008C078  FC 01 00 00 */	fcmpu cr0, f1, f0
/* 8008F49C 0008C07C  41 82 00 F0 */	beq lbl_8008F58C
/* 8008F4A0 0008C080  88 1B 22 1C */	lbz r0, 0x221c(r27)
/* 8008F4A4 0008C084  54 00 CF FF */	rlwinm. r0, r0, 0x19, 0x1f, 0x1f
/* 8008F4A8 0008C088  41 82 00 0C */	beq lbl_8008F4B4
/* 8008F4AC 0008C08C  38 00 00 01 */	li r0, 1
/* 8008F4B0 0008C090  48 00 00 40 */	b lbl_8008F4F0
lbl_8008F4B4:
/* 8008F4B4 0008C094  80 6D AE B4 */	lwz r3, p_ftCommonData(r13)
/* 8008F4B8 0008C098  3C 00 43 30 */	lis r0, 0x4330
/* 8008F4BC 0008C09C  C8 22 8B 00 */	lfd f1, lbl_804D84E0(r2)
/* 8008F4C0 0008C0A0  80 63 03 C0 */	lwz r3, 0x3c0(r3)
/* 8008F4C4 0008C0A4  C0 5B 18 38 */	lfs f2, 0x1838(r27)
/* 8008F4C8 0008C0A8  6C 63 80 00 */	xoris r3, r3, 0x8000
/* 8008F4CC 0008C0AC  90 61 00 8C */	stw r3, 0x8c(r1)
/* 8008F4D0 0008C0B0  90 01 00 88 */	stw r0, 0x88(r1)
/* 8008F4D4 0008C0B4  C8 01 00 88 */	lfd f0, 0x88(r1)
/* 8008F4D8 0008C0B8  EC 00 08 28 */	fsubs f0, f0, f1
/* 8008F4DC 0008C0BC  FC 02 00 40 */	fcmpo cr0, f2, f0
/* 8008F4E0 0008C0C0  40 80 00 0C */	bge lbl_8008F4EC
/* 8008F4E4 0008C0C4  38 00 00 01 */	li r0, 1
/* 8008F4E8 0008C0C8  48 00 00 08 */	b lbl_8008F4F0
lbl_8008F4EC:
/* 8008F4EC 0008C0CC  38 00 00 00 */	li r0, 0
lbl_8008F4F0:
/* 8008F4F0 0008C0D0  2C 00 00 00 */	cmpwi r0, 0
/* 8008F4F4 0008C0D4  41 82 00 0C */	beq lbl_8008F500
/* 8008F4F8 0008C0D8  7C 83 23 78 */	mr r3, r4
/* 8008F4FC 0008C0DC  48 04 F3 59 */	bl func_800DE854
lbl_8008F500:
/* 8008F500 0008C0E0  7F E3 FB 78 */	mr r3, r31
/* 8008F504 0008C0E4  80 9D 1A 58 */	lwz r4, 0x1a58(r29)
/* 8008F508 0008C0E8  48 04 D9 2D */	bl func_800DCE34
/* 8008F50C 0008C0EC  7F E3 FB 78 */	mr r3, r31
/* 8008F510 0008C0F0  4B FE E6 49 */	bl func_8007DB58
/* 8008F514 0008C0F4  80 9F 00 2C */	lwz r4, 0x2c(r31)
/* 8008F518 0008C0F8  88 04 22 1D */	lbz r0, 0x221d(r4)
/* 8008F51C 0008C0FC  54 00 07 FF */	clrlwi. r0, r0, 0x1f
/* 8008F520 0008C100  41 82 00 10 */	beq lbl_8008F530
/* 8008F524 0008C104  80 6D AE B4 */	lwz r3, p_ftCommonData(r13)
/* 8008F528 0008C108  80 03 04 98 */	lwz r0, 0x498(r3)
/* 8008F52C 0008C10C  90 04 20 64 */	stw r0, 0x2064(r4)
lbl_8008F530:
/* 8008F530 0008C110  80 64 18 60 */	lwz r3, 0x1860(r4)
/* 8008F534 0008C114  28 03 00 06 */	cmplwi r3, 6
/* 8008F538 0008C118  41 82 00 0C */	beq lbl_8008F544
/* 8008F53C 0008C11C  28 03 00 07 */	cmplwi r3, 7
/* 8008F540 0008C120  40 82 00 30 */	bne lbl_8008F570
lbl_8008F544:
/* 8008F544 0008C124  88 04 22 28 */	lbz r0, 0x2228(r4)
/* 8008F548 0008C128  54 00 DF FF */	rlwinm. r0, r0, 0x1b, 0x1f, 0x1f
/* 8008F54C 0008C12C  40 82 00 24 */	bne lbl_8008F570
/* 8008F550 0008C130  28 03 00 06 */	cmplwi r3, 6
/* 8008F554 0008C134  40 82 00 0C */	bne lbl_8008F560
/* 8008F558 0008C138  38 80 00 00 */	li r4, 0
/* 8008F55C 0008C13C  48 00 00 08 */	b lbl_8008F564
lbl_8008F560:
/* 8008F560 0008C140  38 80 00 01 */	li r4, 1
lbl_8008F564:
/* 8008F564 0008C144  7F E3 FB 78 */	mr r3, r31
/* 8008F568 0008C148  48 03 3C 25 */	bl func_800C318C
/* 8008F56C 0008C14C  48 00 00 14 */	b lbl_8008F580
lbl_8008F570:
/* 8008F570 0008C150  FC 20 F8 90 */	fmr f1, f31
/* 8008F574 0008C154  38 7F 00 00 */	addi r3, r31, 0
/* 8008F578 0008C158  38 80 FF FF */	li r4, -1
/* 8008F57C 0008C15C  4B FF E7 65 */	bl func_8008DCE0
lbl_8008F580:
/* 8008F580 0008C160  38 00 00 01 */	li r0, 1
/* 8008F584 0008C164  90 1B 18 28 */	stw r0, 0x1828(r27)
/* 8008F588 0008C168  48 00 01 94 */	b lbl_8008F71C
lbl_8008F58C:
/* 8008F58C 0008C16C  7C 83 23 78 */	mr r3, r4
/* 8008F590 0008C170  4B FE E5 C9 */	bl func_8007DB58
/* 8008F594 0008C174  80 7D 1A 58 */	lwz r3, 0x1a58(r29)
/* 8008F598 0008C178  48 04 DA 3D */	bl func_800DCFD4
/* 8008F59C 0008C17C  7F E3 FB 78 */	mr r3, r31
/* 8008F5A0 0008C180  80 9D 1A 58 */	lwz r4, 0x1a58(r29)
/* 8008F5A4 0008C184  48 04 D8 91 */	bl func_800DCE34
/* 8008F5A8 0008C188  7F E3 FB 78 */	mr r3, r31
/* 8008F5AC 0008C18C  4B FE E5 AD */	bl func_8007DB58
/* 8008F5B0 0008C190  80 9F 00 2C */	lwz r4, 0x2c(r31)
/* 8008F5B4 0008C194  88 04 22 1D */	lbz r0, 0x221d(r4)
/* 8008F5B8 0008C198  54 00 07 FF */	clrlwi. r0, r0, 0x1f
/* 8008F5BC 0008C19C  41 82 00 10 */	beq lbl_8008F5CC
/* 8008F5C0 0008C1A0  80 6D AE B4 */	lwz r3, p_ftCommonData(r13)
/* 8008F5C4 0008C1A4  80 03 04 98 */	lwz r0, 0x498(r3)
/* 8008F5C8 0008C1A8  90 04 20 64 */	stw r0, 0x2064(r4)
lbl_8008F5CC:
/* 8008F5CC 0008C1AC  80 64 18 60 */	lwz r3, 0x1860(r4)
/* 8008F5D0 0008C1B0  28 03 00 06 */	cmplwi r3, 6
/* 8008F5D4 0008C1B4  41 82 00 0C */	beq lbl_8008F5E0
/* 8008F5D8 0008C1B8  28 03 00 07 */	cmplwi r3, 7
/* 8008F5DC 0008C1BC  40 82 00 30 */	bne lbl_8008F60C
lbl_8008F5E0:
/* 8008F5E0 0008C1C0  88 04 22 28 */	lbz r0, 0x2228(r4)
/* 8008F5E4 0008C1C4  54 00 DF FF */	rlwinm. r0, r0, 0x1b, 0x1f, 0x1f
/* 8008F5E8 0008C1C8  40 82 00 24 */	bne lbl_8008F60C
/* 8008F5EC 0008C1CC  28 03 00 06 */	cmplwi r3, 6
/* 8008F5F0 0008C1D0  40 82 00 0C */	bne lbl_8008F5FC
/* 8008F5F4 0008C1D4  38 80 00 00 */	li r4, 0
/* 8008F5F8 0008C1D8  48 00 00 08 */	b lbl_8008F600
lbl_8008F5FC:
/* 8008F5FC 0008C1DC  38 80 00 01 */	li r4, 1
lbl_8008F600:
/* 8008F600 0008C1E0  7F E3 FB 78 */	mr r3, r31
/* 8008F604 0008C1E4  48 03 3B 89 */	bl func_800C318C
/* 8008F608 0008C1E8  48 00 01 14 */	b lbl_8008F71C
lbl_8008F60C:
/* 8008F60C 0008C1EC  FC 20 F8 90 */	fmr f1, f31
/* 8008F610 0008C1F0  38 7F 00 00 */	addi r3, r31, 0
/* 8008F614 0008C1F4  38 80 FF FF */	li r4, -1
/* 8008F618 0008C1F8  4B FF E6 C9 */	bl func_8008DCE0
/* 8008F61C 0008C1FC  48 00 01 00 */	b lbl_8008F71C
lbl_8008F620:
/* 8008F620 0008C200  80 7D 19 74 */	lwz r3, 0x1974(r29)
/* 8008F624 0008C204  28 03 00 00 */	cmplwi r3, 0
/* 8008F628 0008C208  41 82 00 28 */	beq lbl_8008F650
/* 8008F62C 0008C20C  48 1D BC AD */	bl func_8026B2D8
/* 8008F630 0008C210  2C 03 00 00 */	cmpwi r3, 0
/* 8008F634 0008C214  41 82 00 1C */	beq lbl_8008F650
/* 8008F638 0008C218  88 1D 22 22 */	lbz r0, 0x2222(r29)
/* 8008F63C 0008C21C  54 00 CF FF */	rlwinm. r0, r0, 0x19, 0x1f, 0x1f
/* 8008F640 0008C220  41 82 00 10 */	beq lbl_8008F650
/* 8008F644 0008C224  7F E3 FB 78 */	mr r3, r31
/* 8008F648 0008C228  48 05 10 91 */	bl ftDonkey_800E06D8
/* 8008F64C 0008C22C  48 00 00 D0 */	b lbl_8008F71C
lbl_8008F650:
/* 8008F650 0008C230  7F E3 FB 78 */	mr r3, r31
/* 8008F654 0008C234  48 00 FA 9D */	bl func_8009F0F0
/* 8008F658 0008C238  2C 03 00 00 */	cmpwi r3, 0
/* 8008F65C 0008C23C  40 82 00 C0 */	bne lbl_8008F71C
/* 8008F660 0008C240  7F E3 FB 78 */	mr r3, r31
/* 8008F664 0008C244  48 03 16 55 */	bl func_800C0CB8
/* 8008F668 0008C248  2C 03 00 00 */	cmpwi r3, 0
/* 8008F66C 0008C24C  40 82 00 B0 */	bne lbl_8008F71C
/* 8008F670 0008C250  80 1D 00 10 */	lwz r0, 0x10(r29)
/* 8008F674 0008C254  2C 00 01 45 */	cmpwi r0, 0x145
/* 8008F678 0008C258  40 82 00 20 */	bne lbl_8008F698
/* 8008F67C 0008C25C  C0 3D 00 2C */	lfs f1, 0x2c(r29)
/* 8008F680 0008C260  38 7F 00 00 */	addi r3, r31, 0
/* 8008F684 0008C264  38 80 01 45 */	li r4, 0x145
/* 8008F688 0008C268  4B FF E6 59 */	bl func_8008DCE0
/* 8008F68C 0008C26C  7F E3 FB 78 */	mr r3, r31
/* 8008F690 0008C270  48 00 19 A1 */	bl func_80091030
/* 8008F694 0008C274  48 00 00 88 */	b lbl_8008F71C
lbl_8008F698:
/* 8008F698 0008C278  7F E3 FB 78 */	mr r3, r31
/* 8008F69C 0008C27C  48 03 7E 59 */	bl func_800C74F4
/* 8008F6A0 0008C280  2C 03 00 00 */	cmpwi r3, 0
/* 8008F6A4 0008C284  40 82 00 78 */	bne lbl_8008F71C
/* 8008F6A8 0008C288  7F E3 FB 78 */	mr r3, r31
/* 8008F6AC 0008C28C  4B FE E4 AD */	bl func_8007DB58
/* 8008F6B0 0008C290  80 9F 00 2C */	lwz r4, 0x2c(r31)
/* 8008F6B4 0008C294  88 04 22 1D */	lbz r0, 0x221d(r4)
/* 8008F6B8 0008C298  54 00 07 FF */	clrlwi. r0, r0, 0x1f
/* 8008F6BC 0008C29C  41 82 00 10 */	beq lbl_8008F6CC
/* 8008F6C0 0008C2A0  80 6D AE B4 */	lwz r3, p_ftCommonData(r13)
/* 8008F6C4 0008C2A4  80 03 04 98 */	lwz r0, 0x498(r3)
/* 8008F6C8 0008C2A8  90 04 20 64 */	stw r0, 0x2064(r4)
lbl_8008F6CC:
/* 8008F6CC 0008C2AC  80 64 18 60 */	lwz r3, 0x1860(r4)
/* 8008F6D0 0008C2B0  28 03 00 06 */	cmplwi r3, 6
/* 8008F6D4 0008C2B4  41 82 00 0C */	beq lbl_8008F6E0
/* 8008F6D8 0008C2B8  28 03 00 07 */	cmplwi r3, 7
/* 8008F6DC 0008C2BC  40 82 00 30 */	bne lbl_8008F70C
lbl_8008F6E0:
/* 8008F6E0 0008C2C0  88 04 22 28 */	lbz r0, 0x2228(r4)
/* 8008F6E4 0008C2C4  54 00 DF FF */	rlwinm. r0, r0, 0x1b, 0x1f, 0x1f
/* 8008F6E8 0008C2C8  40 82 00 24 */	bne lbl_8008F70C
/* 8008F6EC 0008C2CC  28 03 00 06 */	cmplwi r3, 6
/* 8008F6F0 0008C2D0  40 82 00 0C */	bne lbl_8008F6FC
/* 8008F6F4 0008C2D4  38 80 00 00 */	li r4, 0
/* 8008F6F8 0008C2D8  48 00 00 08 */	b lbl_8008F700
lbl_8008F6FC:
/* 8008F6FC 0008C2DC  38 80 00 01 */	li r4, 1
lbl_8008F700:
/* 8008F700 0008C2E0  7F E3 FB 78 */	mr r3, r31
/* 8008F704 0008C2E4  48 03 3A 89 */	bl func_800C318C
/* 8008F708 0008C2E8  48 00 00 14 */	b lbl_8008F71C
lbl_8008F70C:
/* 8008F70C 0008C2EC  FC 20 F8 90 */	fmr f1, f31
/* 8008F710 0008C2F0  38 7F 00 00 */	addi r3, r31, 0
/* 8008F714 0008C2F4  38 80 FF FF */	li r4, -1
/* 8008F718 0008C2F8  4B FF E5 C9 */	bl func_8008DCE0
lbl_8008F71C:
/* 8008F71C 0008C2FC  2C 1E 00 00 */	cmpwi r30, 0
/* 8008F720 0008C300  41 82 00 0C */	beq lbl_8008F72C
/* 8008F724 0008C304  7F E3 FB 78 */	mr r3, r31
/* 8008F728 0008C308  48 03 3E 71 */	bl func_800C3598
lbl_8008F72C:
/* 8008F72C 0008C30C  BB 61 00 94 */	lmw r27, 0x94(r1)
/* 8008F730 0008C310  80 01 00 B4 */	lwz r0, 0xb4(r1)
/* 8008F734 0008C314  CB E1 00 A8 */	lfd f31, 0xa8(r1)
/* 8008F738 0008C318  38 21 00 B0 */	addi r1, r1, 0xb0
/* 8008F73C 0008C31C  7C 08 03 A6 */	mtlr r0
/* 8008F740 0008C320  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

extern unk_t func_800C554C();
extern unk_t func_800C554C();

#pragma push
asm unk_t func_8008F744()
{ // clang-format off
    nofralloc
/* 8008F744 0008C324  7C 08 02 A6 */	mflr r0
/* 8008F748 0008C328  90 01 00 04 */	stw r0, 4(r1)
/* 8008F74C 0008C32C  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 8008F750 0008C330  93 E1 00 14 */	stw r31, 0x14(r1)
/* 8008F754 0008C334  93 C1 00 10 */	stw r30, 0x10(r1)
/* 8008F758 0008C338  7C 7E 1B 78 */	mr r30, r3
/* 8008F75C 0008C33C  80 63 00 2C */	lwz r3, 0x2c(r3)
/* 8008F760 0008C340  C0 02 8A F4 */	lfs f0, lbl_804D84D4(r2)
/* 8008F764 0008C344  C0 23 23 40 */	lfs f1, 0x2340(r3)
/* 8008F768 0008C348  7C 7F 1B 78 */	mr r31, r3
/* 8008F76C 0008C34C  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8008F770 0008C350  40 81 00 10 */	ble lbl_8008F780
/* 8008F774 0008C354  C0 02 8A F8 */	lfs f0, lbl_804D84D8(r2)
/* 8008F778 0008C358  EC 01 00 28 */	fsubs f0, f1, f0
/* 8008F77C 0008C35C  D0 1F 23 40 */	stfs f0, 0x2340(r31)
lbl_8008F780:
/* 8008F780 0008C360  88 7F 22 1C */	lbz r3, 0x221c(r31)
/* 8008F784 0008C364  54 60 FF FF */	rlwinm. r0, r3, 0x1f, 0x1f, 0x1f
/* 8008F788 0008C368  41 82 00 50 */	beq lbl_8008F7D8
/* 8008F78C 0008C36C  C0 3F 23 40 */	lfs f1, 0x2340(r31)
/* 8008F790 0008C370  C0 02 8A F4 */	lfs f0, lbl_804D84D4(r2)
/* 8008F794 0008C374  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8008F798 0008C378  4C 40 13 82 */	cror 2, 0, 2
/* 8008F79C 0008C37C  40 82 00 3C */	bne lbl_8008F7D8
/* 8008F7A0 0008C380  38 00 00 00 */	li r0, 0
/* 8008F7A4 0008C384  50 03 0F BC */	rlwimi r3, r0, 1, 0x1e, 0x1e
/* 8008F7A8 0008C388  98 7F 22 1C */	stb r3, 0x221c(r31)
/* 8008F7AC 0008C38C  7F C3 F3 78 */	mr r3, r30
/* 8008F7B0 0008C390  80 8D AE B4 */	lwz r4, p_ftCommonData(r13)
/* 8008F7B4 0008C394  80 04 04 CC */	lwz r0, 0x4cc(r4)
/* 8008F7B8 0008C398  B0 1F 20 98 */	sth r0, 0x2098(r31)
/* 8008F7BC 0008C39C  4B FF 00 B1 */	bl func_8007F86C
/* 8008F7C0 0008C3A0  7F C3 F3 78 */	mr r3, r30
/* 8008F7C4 0008C3A4  48 03 5A 7D */	bl func_800C5240
/* 8008F7C8 0008C3A8  2C 03 00 00 */	cmpwi r3, 0
/* 8008F7CC 0008C3AC  41 82 00 0C */	beq lbl_8008F7D8
/* 8008F7D0 0008C3B0  7F E3 FB 78 */	mr r3, r31
/* 8008F7D4 0008C3B4  48 03 5D 79 */	bl func_800C554C
lbl_8008F7D8:
/* 8008F7D8 0008C3B8  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 8008F7DC 0008C3BC  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 8008F7E0 0008C3C0  83 C1 00 10 */	lwz r30, 0x10(r1)
/* 8008F7E4 0008C3C4  38 21 00 18 */	addi r1, r1, 0x18
/* 8008F7E8 0008C3C8  7C 08 03 A6 */	mtlr r0
/* 8008F7EC 0008C3CC  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

#pragma push
asm unk_t func_8008F7F0()
{ // clang-format off
    nofralloc
/* 8008F7F0 0008C3D0  7C 08 02 A6 */	mflr r0
/* 8008F7F4 0008C3D4  90 01 00 04 */	stw r0, 4(r1)
/* 8008F7F8 0008C3D8  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 8008F7FC 0008C3DC  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 8008F800 0008C3E0  7C 7F 1B 78 */	mr r31, r3
/* 8008F804 0008C3E4  93 C1 00 18 */	stw r30, 0x18(r1)
/* 8008F808 0008C3E8  83 C3 00 2C */	lwz r30, 0x2c(r3)
/* 8008F80C 0008C3EC  C0 02 8A F4 */	lfs f0, lbl_804D84D4(r2)
/* 8008F810 0008C3F0  C0 3E 23 40 */	lfs f1, 0x2340(r30)
/* 8008F814 0008C3F4  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8008F818 0008C3F8  40 81 00 10 */	ble lbl_8008F828
/* 8008F81C 0008C3FC  C0 02 8A F8 */	lfs f0, lbl_804D84D8(r2)
/* 8008F820 0008C400  EC 01 00 28 */	fsubs f0, f1, f0
/* 8008F824 0008C404  D0 1E 23 40 */	stfs f0, 0x2340(r30)
lbl_8008F828:
/* 8008F828 0008C408  88 7E 22 1C */	lbz r3, 0x221c(r30)
/* 8008F82C 0008C40C  54 60 FF FF */	rlwinm. r0, r3, 0x1f, 0x1f, 0x1f
/* 8008F830 0008C410  41 82 00 50 */	beq lbl_8008F880
/* 8008F834 0008C414  C0 3E 23 40 */	lfs f1, 0x2340(r30)
/* 8008F838 0008C418  C0 02 8A F4 */	lfs f0, lbl_804D84D4(r2)
/* 8008F83C 0008C41C  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8008F840 0008C420  4C 40 13 82 */	cror 2, 0, 2
/* 8008F844 0008C424  40 82 00 3C */	bne lbl_8008F880
/* 8008F848 0008C428  38 00 00 00 */	li r0, 0
/* 8008F84C 0008C42C  50 03 0F BC */	rlwimi r3, r0, 1, 0x1e, 0x1e
/* 8008F850 0008C430  98 7E 22 1C */	stb r3, 0x221c(r30)
/* 8008F854 0008C434  7F E3 FB 78 */	mr r3, r31
/* 8008F858 0008C438  80 8D AE B4 */	lwz r4, p_ftCommonData(r13)
/* 8008F85C 0008C43C  80 04 04 CC */	lwz r0, 0x4cc(r4)
/* 8008F860 0008C440  B0 1E 20 98 */	sth r0, 0x2098(r30)
/* 8008F864 0008C444  4B FF 00 09 */	bl func_8007F86C
/* 8008F868 0008C448  7F E3 FB 78 */	mr r3, r31
/* 8008F86C 0008C44C  48 03 59 D5 */	bl func_800C5240
/* 8008F870 0008C450  2C 03 00 00 */	cmpwi r3, 0
/* 8008F874 0008C454  41 82 00 0C */	beq lbl_8008F880
/* 8008F878 0008C458  7F C3 F3 78 */	mr r3, r30
/* 8008F87C 0008C45C  48 03 5C D1 */	bl func_800C554C
lbl_8008F880:
/* 8008F880 0008C460  7F E3 FB 78 */	mr r3, r31
/* 8008F884 0008C464  4B FD F9 B5 */	bl ftAnim_IsFramesRemaining
/* 8008F888 0008C468  2C 03 00 00 */	cmpwi r3, 0
/* 8008F88C 0008C46C  40 82 00 94 */	bne lbl_8008F920
/* 8008F890 0008C470  88 1E 22 1C */	lbz r0, 0x221c(r30)
/* 8008F894 0008C474  54 00 FF FF */	rlwinm. r0, r0, 0x1f, 0x1f, 0x1f
/* 8008F898 0008C478  40 82 00 88 */	bne lbl_8008F920
/* 8008F89C 0008C47C  80 1E 00 E0 */	lwz r0, 0xe0(r30)
/* 8008F8A0 0008C480  2C 00 00 01 */	cmpwi r0, 1
/* 8008F8A4 0008C484  40 82 00 74 */	bne lbl_8008F918
/* 8008F8A8 0008C488  88 1E 22 24 */	lbz r0, 0x2224(r30)
/* 8008F8AC 0008C48C  54 00 DF FF */	rlwinm. r0, r0, 0x1b, 0x1f, 0x1f
/* 8008F8B0 0008C490  41 82 00 10 */	beq lbl_8008F8C0
/* 8008F8B4 0008C494  7F E3 FB 78 */	mr r3, r31
/* 8008F8B8 0008C498  48 00 0E C9 */	bl func_80090780
/* 8008F8BC 0008C49C  48 00 00 64 */	b lbl_8008F920
lbl_8008F8C0:
/* 8008F8C0 0008C4A0  80 9F 00 2C */	lwz r4, 0x2c(r31)
/* 8008F8C4 0008C4A4  C0 02 8A F4 */	lfs f0, lbl_804D84D4(r2)
/* 8008F8C8 0008C4A8  C0 24 23 54 */	lfs f1, 0x2354(r4)
/* 8008F8CC 0008C4AC  FC 01 00 00 */	fcmpu cr0, f1, f0
/* 8008F8D0 0008C4B0  41 82 00 30 */	beq lbl_8008F900
/* 8008F8D4 0008C4B4  80 6D AE B4 */	lwz r3, p_ftCommonData(r13)
/* 8008F8D8 0008C4B8  C0 03 01 D0 */	lfs f0, 0x1d0(r3)
/* 8008F8DC 0008C4BC  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8008F8E0 0008C4C0  4C 40 13 82 */	cror 2, 0, 2
/* 8008F8E4 0008C4C4  40 82 00 1C */	bne lbl_8008F900
/* 8008F8E8 0008C4C8  80 04 06 68 */	lwz r0, 0x668(r4)
/* 8008F8EC 0008C4CC  38 7F 00 00 */	addi r3, r31, 0
/* 8008F8F0 0008C4D0  60 00 0C 00 */	ori r0, r0, 0xc00
/* 8008F8F4 0008C4D4  90 04 06 68 */	stw r0, 0x668(r4)
/* 8008F8F8 0008C4D8  48 03 BF 79 */	bl func_800CB870
/* 8008F8FC 0008C4DC  48 00 00 08 */	b lbl_8008F904
lbl_8008F900:
/* 8008F900 0008C4E0  38 60 00 00 */	li r3, 0
lbl_8008F904:
/* 8008F904 0008C4E4  2C 03 00 00 */	cmpwi r3, 0
/* 8008F908 0008C4E8  40 82 00 18 */	bne lbl_8008F920
/* 8008F90C 0008C4EC  7F E3 FB 78 */	mr r3, r31
/* 8008F910 0008C4F0  48 03 CE 21 */	bl func_800CC730
/* 8008F914 0008C4F4  48 00 00 0C */	b lbl_8008F920
lbl_8008F918:
/* 8008F918 0008C4F8  7F E3 FB 78 */	mr r3, r31
/* 8008F91C 0008C4FC  4B FF A9 A1 */	bl func_8008A2BC
lbl_8008F920:
/* 8008F920 0008C500  80 01 00 24 */	lwz r0, 0x24(r1)
/* 8008F924 0008C504  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 8008F928 0008C508  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 8008F92C 0008C50C  38 21 00 20 */	addi r1, r1, 0x20
/* 8008F930 0008C510  7C 08 03 A6 */	mtlr r0
/* 8008F934 0008C514  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

extern unk_t func_800CB8E0();
extern unk_t func_800D69C4();

#pragma push
asm unk_t func_8008F938()
{ // clang-format off
    nofralloc
/* 8008F938 0008C518  7C 08 02 A6 */	mflr r0
/* 8008F93C 0008C51C  90 01 00 04 */	stw r0, 4(r1)
/* 8008F940 0008C520  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 8008F944 0008C524  93 E1 00 14 */	stw r31, 0x14(r1)
/* 8008F948 0008C528  93 C1 00 10 */	stw r30, 0x10(r1)
/* 8008F94C 0008C52C  7C 7E 1B 78 */	mr r30, r3
/* 8008F950 0008C530  80 63 00 2C */	lwz r3, 0x2c(r3)
/* 8008F954 0008C534  88 03 23 5A */	lbz r0, 0x235a(r3)
/* 8008F958 0008C538  3B E3 00 00 */	addi r31, r3, 0
/* 8008F95C 0008C53C  28 00 00 00 */	cmplwi r0, 0
/* 8008F960 0008C540  41 82 00 A8 */	beq lbl_8008FA08
/* 8008F964 0008C544  88 7F 23 5B */	lbz r3, 0x235b(r31)
/* 8008F968 0008C548  28 03 00 00 */	cmplwi r3, 0
/* 8008F96C 0008C54C  41 82 00 0C */	beq lbl_8008F978
/* 8008F970 0008C550  38 03 FF FF */	addi r0, r3, -1
/* 8008F974 0008C554  98 1F 23 5B */	stb r0, 0x235b(r31)
lbl_8008F978:
/* 8008F978 0008C558  88 1F 23 5B */	lbz r0, 0x235b(r31)
/* 8008F97C 0008C55C  28 00 00 00 */	cmplwi r0, 0
/* 8008F980 0008C560  40 82 00 88 */	bne lbl_8008FA08
/* 8008F984 0008C564  80 1F 00 E0 */	lwz r0, 0xe0(r31)
/* 8008F988 0008C568  2C 00 00 01 */	cmpwi r0, 1
/* 8008F98C 0008C56C  40 82 00 7C */	bne lbl_8008FA08
/* 8008F990 0008C570  C0 3F 00 90 */	lfs f1, 0x90(r31)
/* 8008F994 0008C574  C0 02 8A F4 */	lfs f0, lbl_804D84D4(r2)
/* 8008F998 0008C578  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8008F99C 0008C57C  40 80 00 6C */	bge lbl_8008FA08
/* 8008F9A0 0008C580  7F C3 F3 78 */	mr r3, r30
/* 8008F9A4 0008C584  48 04 70 21 */	bl func_800D69C4
/* 8008F9A8 0008C588  2C 03 00 00 */	cmpwi r3, 0
/* 8008F9AC 0008C58C  40 82 00 14 */	bne lbl_8008F9C0
/* 8008F9B0 0008C590  7F C3 F3 78 */	mr r3, r30
/* 8008F9B4 0008C594  48 03 BF 2D */	bl func_800CB8E0
/* 8008F9B8 0008C598  2C 03 00 00 */	cmpwi r3, 0
/* 8008F9BC 0008C59C  41 82 00 4C */	beq lbl_8008FA08
lbl_8008F9C0:
/* 8008F9C0 0008C5A0  C0 02 8A F4 */	lfs f0, lbl_804D84D4(r2)
/* 8008F9C4 0008C5A4  38 7F 00 00 */	addi r3, r31, 0
/* 8008F9C8 0008C5A8  38 80 00 0C */	li r4, 0xc
/* 8008F9CC 0008C5AC  D0 1F 00 94 */	stfs f0, 0x94(r31)
/* 8008F9D0 0008C5B0  38 A0 00 00 */	li r5, 0
/* 8008F9D4 0008C5B4  D0 1F 00 90 */	stfs f0, 0x90(r31)
/* 8008F9D8 0008C5B8  D0 1F 00 8C */	stfs f0, 0x8c(r31)
/* 8008F9DC 0008C5BC  4B FE F1 D1 */	bl func_8007EBAC
/* 8008F9E0 0008C5C0  38 7F 00 00 */	addi r3, r31, 0
/* 8008F9E4 0008C5C4  38 80 00 79 */	li r4, 0x79
/* 8008F9E8 0008C5C8  38 A0 00 00 */	li r5, 0
/* 8008F9EC 0008C5CC  48 03 05 E5 */	bl func_800BFFD0
/* 8008F9F0 0008C5D0  88 1F 22 27 */	lbz r0, 0x2227(r31)
/* 8008F9F4 0008C5D4  38 60 00 01 */	li r3, 1
/* 8008F9F8 0008C5D8  50 60 1F 38 */	rlwimi r0, r3, 3, 0x1c, 0x1c
/* 8008F9FC 0008C5DC  98 1F 22 27 */	stb r0, 0x2227(r31)
/* 8008FA00 0008C5E0  38 60 00 01 */	li r3, 1
/* 8008FA04 0008C5E4  48 00 00 28 */	b lbl_8008FA2C
lbl_8008FA08:
/* 8008FA08 0008C5E8  7F C3 F3 78 */	mr r3, r30
/* 8008FA0C 0008C5EC  48 03 B4 75 */	bl func_800CAE80
/* 8008FA10 0008C5F0  2C 03 00 00 */	cmpwi r3, 0
/* 8008FA14 0008C5F4  41 82 00 14 */	beq lbl_8008FA28
/* 8008FA18 0008C5F8  C0 1F 23 40 */	lfs f0, 0x2340(r31)
/* 8008FA1C 0008C5FC  38 60 00 01 */	li r3, 1
/* 8008FA20 0008C600  D0 1F 23 54 */	stfs f0, 0x2354(r31)
/* 8008FA24 0008C604  48 00 00 08 */	b lbl_8008FA2C
lbl_8008FA28:
/* 8008FA28 0008C608  38 60 00 00 */	li r3, 0
lbl_8008FA2C:
/* 8008FA2C 0008C60C  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 8008FA30 0008C610  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 8008FA34 0008C614  83 C1 00 10 */	lwz r30, 0x10(r1)
/* 8008FA38 0008C618  38 21 00 18 */	addi r1, r1, 0x18
/* 8008FA3C 0008C61C  7C 08 03 A6 */	mtlr r0
/* 8008FA40 0008C620  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

extern unk_t func_800C5074();
extern unk_t func_800C5E94();

#pragma push
asm unk_t func_8008FA44()
{ // clang-format off
    nofralloc
/* 8008FA44 0008C624  7C 08 02 A6 */	mflr r0
/* 8008FA48 0008C628  90 01 00 04 */	stw r0, 4(r1)
/* 8008FA4C 0008C62C  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 8008FA50 0008C630  93 E1 00 14 */	stw r31, 0x14(r1)
/* 8008FA54 0008C634  93 C1 00 10 */	stw r30, 0x10(r1)
/* 8008FA58 0008C638  7C 7E 1B 78 */	mr r30, r3
/* 8008FA5C 0008C63C  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 8008FA60 0008C640  88 1F 22 1C */	lbz r0, 0x221c(r31)
/* 8008FA64 0008C644  54 00 FF FF */	rlwinm. r0, r0, 0x1f, 0x1f, 0x1f
/* 8008FA68 0008C648  40 82 00 8C */	bne lbl_8008FAF4
/* 8008FA6C 0008C64C  7F C3 F3 78 */	mr r3, r30
/* 8008FA70 0008C650  48 03 57 D1 */	bl func_800C5240
/* 8008FA74 0008C654  2C 03 00 00 */	cmpwi r3, 0
/* 8008FA78 0008C658  41 82 00 28 */	beq lbl_8008FAA0
/* 8008FA7C 0008C65C  80 1F 00 E0 */	lwz r0, 0xe0(r31)
/* 8008FA80 0008C660  2C 00 00 01 */	cmpwi r0, 1
/* 8008FA84 0008C664  40 82 00 10 */	bne lbl_8008FA94
/* 8008FA88 0008C668  7F C3 F3 78 */	mr r3, r30
/* 8008FA8C 0008C66C  48 03 64 09 */	bl func_800C5E94
/* 8008FA90 0008C670  48 00 00 70 */	b lbl_8008FB00
lbl_8008FA94:
/* 8008FA94 0008C674  7F C3 F3 78 */	mr r3, r30
/* 8008FA98 0008C678  48 03 55 DD */	bl func_800C5074
/* 8008FA9C 0008C67C  48 00 00 64 */	b lbl_8008FB00
lbl_8008FAA0:
/* 8008FAA0 0008C680  C0 3F 23 54 */	lfs f1, 0x2354(r31)
/* 8008FAA4 0008C684  C0 02 8A F4 */	lfs f0, lbl_804D84D4(r2)
/* 8008FAA8 0008C688  FC 01 00 00 */	fcmpu cr0, f1, f0
/* 8008FAAC 0008C68C  41 82 00 24 */	beq lbl_8008FAD0
/* 8008FAB0 0008C690  80 6D AE B4 */	lwz r3, p_ftCommonData(r13)
/* 8008FAB4 0008C694  C0 03 01 D0 */	lfs f0, 0x1d0(r3)
/* 8008FAB8 0008C698  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8008FABC 0008C69C  4C 40 13 82 */	cror 2, 0, 2
/* 8008FAC0 0008C6A0  40 82 00 10 */	bne lbl_8008FAD0
/* 8008FAC4 0008C6A4  80 1F 06 68 */	lwz r0, 0x668(r31)
/* 8008FAC8 0008C6A8  60 00 0C 00 */	ori r0, r0, 0xc00
/* 8008FACC 0008C6AC  90 1F 06 68 */	stw r0, 0x668(r31)
lbl_8008FAD0:
/* 8008FAD0 0008C6B0  80 1F 00 E0 */	lwz r0, 0xe0(r31)
/* 8008FAD4 0008C6B4  2C 00 00 01 */	cmpwi r0, 1
/* 8008FAD8 0008C6B8  40 82 00 10 */	bne lbl_8008FAE8
/* 8008FADC 0008C6BC  7F C3 F3 78 */	mr r3, r30
/* 8008FAE0 0008C6C0  48 03 CF CD */	bl func_800CCAAC
/* 8008FAE4 0008C6C4  48 00 00 1C */	b lbl_8008FB00
lbl_8008FAE8:
/* 8008FAE8 0008C6C8  7F C3 F3 78 */	mr r3, r30
/* 8008FAEC 0008C6CC  4B FF A9 E9 */	bl func_8008A4D4
/* 8008FAF0 0008C6D0  48 00 00 10 */	b lbl_8008FB00
lbl_8008FAF4:
/* 8008FAF4 0008C6D4  7F C3 F3 78 */	mr r3, r30
/* 8008FAF8 0008C6D8  4B FF FE 41 */	bl func_8008F938
/* 8008FAFC 0008C6DC  2C 03 00 00 */	cmpwi r3, 0
lbl_8008FB00:
/* 8008FB00 0008C6E0  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 8008FB04 0008C6E4  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 8008FB08 0008C6E8  83 C1 00 10 */	lwz r30, 0x10(r1)
/* 8008FB0C 0008C6EC  38 21 00 18 */	addi r1, r1, 0x18
/* 8008FB10 0008C6F0  7C 08 03 A6 */	mtlr r0
/* 8008FB14 0008C6F4  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

#pragma push
asm unk_t func_8008FB18()
{ // clang-format off
    nofralloc
/* 8008FB18 0008C6F8  7C 08 02 A6 */	mflr r0
/* 8008FB1C 0008C6FC  90 01 00 04 */	stw r0, 4(r1)
/* 8008FB20 0008C700  94 21 FF F8 */	stwu r1, -8(r1)
/* 8008FB24 0008C704  80 83 00 2C */	lwz r4, 0x2c(r3)
/* 8008FB28 0008C708  80 04 00 E0 */	lwz r0, 0xe0(r4)
/* 8008FB2C 0008C70C  2C 00 00 01 */	cmpwi r0, 1
/* 8008FB30 0008C710  40 82 00 20 */	bne lbl_8008FB50
/* 8008FB34 0008C714  88 04 22 1C */	lbz r0, 0x221c(r4)
/* 8008FB38 0008C718  54 00 FF FF */	rlwinm. r0, r0, 0x1f, 0x1f, 0x1f
/* 8008FB3C 0008C71C  40 82 00 0C */	bne lbl_8008FB48
/* 8008FB40 0008C720  4B FF 52 71 */	bl func_80084DB0
/* 8008FB44 0008C724  48 00 00 10 */	b lbl_8008FB54
lbl_8008FB48:
/* 8008FB48 0008C728  4B FF 53 A5 */	bl func_80084EEC
/* 8008FB4C 0008C72C  48 00 00 08 */	b lbl_8008FB54
lbl_8008FB50:
/* 8008FB50 0008C730  4B FF 53 ED */	bl func_80084F3C
lbl_8008FB54:
/* 8008FB54 0008C734  80 01 00 0C */	lwz r0, 0xc(r1)
/* 8008FB58 0008C738  38 21 00 08 */	addi r1, r1, 8
/* 8008FB5C 0008C73C  7C 08 03 A6 */	mtlr r0
/* 8008FB60 0008C740  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

extern unk_t func_8008FC94();

#pragma push
asm unk_t func_8008FB64()
{ // clang-format off
    nofralloc
/* 8008FB64 0008C744  7C 08 02 A6 */	mflr r0
/* 8008FB68 0008C748  90 01 00 04 */	stw r0, 4(r1)
/* 8008FB6C 0008C74C  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 8008FB70 0008C750  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 8008FB74 0008C754  93 C1 00 18 */	stw r30, 0x18(r1)
/* 8008FB78 0008C758  7C 7E 1B 78 */	mr r30, r3
/* 8008FB7C 0008C75C  80 63 00 2C */	lwz r3, 0x2c(r3)
/* 8008FB80 0008C760  80 03 00 E0 */	lwz r0, 0xe0(r3)
/* 8008FB84 0008C764  3B E3 00 00 */	addi r31, r3, 0
/* 8008FB88 0008C768  2C 00 00 00 */	cmpwi r0, 0
/* 8008FB8C 0008C76C  40 82 00 18 */	bne lbl_8008FBA4
/* 8008FB90 0008C770  3C 60 80 09 */	lis r3, func_8008FC94@ha
/* 8008FB94 0008C774  38 83 FC 94 */	addi r4, r3, func_8008FC94@l
/* 8008FB98 0008C778  38 7E 00 00 */	addi r3, r30, 0
/* 8008FB9C 0008C77C  4B FF 4D 41 */	bl func_800848DC
/* 8008FBA0 0008C780  48 00 00 DC */	b lbl_8008FC7C
lbl_8008FBA4:
/* 8008FBA4 0008C784  7F C3 F3 78 */	mr r3, r30
/* 8008FBA8 0008C788  4B FF 22 2D */	bl func_80081DD4
/* 8008FBAC 0008C78C  2C 03 00 00 */	cmpwi r3, 0
/* 8008FBB0 0008C790  41 82 00 CC */	beq lbl_8008FC7C
/* 8008FBB4 0008C794  88 1F 22 24 */	lbz r0, 0x2224(r31)
/* 8008FBB8 0008C798  54 00 DF FF */	rlwinm. r0, r0, 0x1b, 0x1f, 0x1f
/* 8008FBBC 0008C79C  41 82 00 10 */	beq lbl_8008FBCC
/* 8008FBC0 0008C7A0  7F C3 F3 78 */	mr r3, r30
/* 8008FBC4 0008C7A4  48 00 81 7D */	bl func_80097D40
/* 8008FBC8 0008C7A8  48 00 00 B4 */	b lbl_8008FC7C
lbl_8008FBCC:
/* 8008FBCC 0008C7AC  C0 1F 00 8C */	lfs f0, 0x8c(r31)
/* 8008FBD0 0008C7B0  C0 3F 00 90 */	lfs f1, 0x90(r31)
/* 8008FBD4 0008C7B4  EC 40 00 32 */	fmuls f2, f0, f0
/* 8008FBD8 0008C7B8  C0 02 8A F4 */	lfs f0, lbl_804D84D4(r2)
/* 8008FBDC 0008C7BC  EC 21 00 72 */	fmuls f1, f1, f1
/* 8008FBE0 0008C7C0  EC 82 08 2A */	fadds f4, f2, f1
/* 8008FBE4 0008C7C4  FC 04 00 40 */	fcmpo cr0, f4, f0
/* 8008FBE8 0008C7C8  40 81 00 50 */	ble lbl_8008FC38
/* 8008FBEC 0008C7CC  FC 20 20 34 */	frsqrte f1, f4
/* 8008FBF0 0008C7D0  C8 62 8B 20 */	lfd f3, lbl_804D8500(r2)
/* 8008FBF4 0008C7D4  C8 42 8B 28 */	lfd f2, lbl_804D8508(r2)
/* 8008FBF8 0008C7D8  FC 01 00 72 */	fmul f0, f1, f1
/* 8008FBFC 0008C7DC  FC 23 00 72 */	fmul f1, f3, f1
/* 8008FC00 0008C7E0  FC 04 10 3C */	fnmsub f0, f4, f0, f2
/* 8008FC04 0008C7E4  FC 21 00 32 */	fmul f1, f1, f0
/* 8008FC08 0008C7E8  FC 01 00 72 */	fmul f0, f1, f1
/* 8008FC0C 0008C7EC  FC 23 00 72 */	fmul f1, f3, f1
/* 8008FC10 0008C7F0  FC 04 10 3C */	fnmsub f0, f4, f0, f2
/* 8008FC14 0008C7F4  FC 21 00 32 */	fmul f1, f1, f0
/* 8008FC18 0008C7F8  FC 01 00 72 */	fmul f0, f1, f1
/* 8008FC1C 0008C7FC  FC 23 00 72 */	fmul f1, f3, f1
/* 8008FC20 0008C800  FC 04 10 3C */	fnmsub f0, f4, f0, f2
/* 8008FC24 0008C804  FC 01 00 32 */	fmul f0, f1, f0
/* 8008FC28 0008C808  FC 04 00 32 */	fmul f0, f4, f0
/* 8008FC2C 0008C80C  FC 00 00 18 */	frsp f0, f0
/* 8008FC30 0008C810  D0 01 00 10 */	stfs f0, 0x10(r1)
/* 8008FC34 0008C814  C0 81 00 10 */	lfs f4, 0x10(r1)
lbl_8008FC38:
/* 8008FC38 0008C818  80 6D AE B4 */	lwz r3, p_ftCommonData(r13)
/* 8008FC3C 0008C81C  C0 03 01 E0 */	lfs f0, 0x1e0(r3)
/* 8008FC40 0008C820  FC 04 00 40 */	fcmpo cr0, f4, f0
/* 8008FC44 0008C824  4C 41 13 82 */	cror 2, 1, 2
/* 8008FC48 0008C828  40 82 00 10 */	bne lbl_8008FC58
/* 8008FC4C 0008C82C  7F C3 F3 78 */	mr r3, r30
/* 8008FC50 0008C830  48 00 80 F1 */	bl func_80097D40
/* 8008FC54 0008C834  48 00 00 28 */	b lbl_8008FC7C
lbl_8008FC58:
/* 8008FC58 0008C838  C0 03 01 E4 */	lfs f0, 0x1e4(r3)
/* 8008FC5C 0008C83C  FC 04 00 40 */	fcmpo cr0, f4, f0
/* 8008FC60 0008C840  4C 41 13 82 */	cror 2, 1, 2
/* 8008FC64 0008C844  40 82 00 10 */	bne lbl_8008FC74
/* 8008FC68 0008C848  7F C3 F3 78 */	mr r3, r30
/* 8008FC6C 0008C84C  48 04 5F 8D */	bl func_800D5BF8
/* 8008FC70 0008C850  48 00 00 0C */	b lbl_8008FC7C
lbl_8008FC74:
/* 8008FC74 0008C854  7F E3 FB 78 */	mr r3, r31
/* 8008FC78 0008C858  4B FE DB 85 */	bl func_8007D7FC
lbl_8008FC7C:
/* 8008FC7C 0008C85C  80 01 00 24 */	lwz r0, 0x24(r1)
/* 8008FC80 0008C860  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 8008FC84 0008C864  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 8008FC88 0008C868  38 21 00 20 */	addi r1, r1, 0x20
/* 8008FC8C 0008C86C  7C 08 03 A6 */	mtlr r0
/* 8008FC90 0008C870  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

#pragma push
asm unk_t func_8008FC94()
{ // clang-format off
    nofralloc
/* 8008FC94 0008C874  7C 08 02 A6 */	mflr r0
/* 8008FC98 0008C878  90 01 00 04 */	stw r0, 4(r1)
/* 8008FC9C 0008C87C  94 21 FF F8 */	stwu r1, -8(r1)
/* 8008FCA0 0008C880  80 63 00 2C */	lwz r3, 0x2c(r3)
/* 8008FCA4 0008C884  4B FE D9 31 */	bl func_8007D5D4
/* 8008FCA8 0008C888  80 01 00 0C */	lwz r0, 0xc(r1)
/* 8008FCAC 0008C88C  38 21 00 08 */	addi r1, r1, 8
/* 8008FCB0 0008C890  7C 08 03 A6 */	mtlr r0
/* 8008FCB4 0008C894  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

extern f32 sqrtf__Ff(f32);

#pragma push
asm unk_t func_8008FCB8()
{ // clang-format off
    nofralloc
/* 8008FCB8 0008C898  7C 08 02 A6 */	mflr r0
/* 8008FCBC 0008C89C  90 01 00 04 */	stw r0, 4(r1)
/* 8008FCC0 0008C8A0  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 8008FCC4 0008C8A4  93 E1 00 14 */	stw r31, 0x14(r1)
/* 8008FCC8 0008C8A8  7C 7F 1B 78 */	mr r31, r3
/* 8008FCCC 0008C8AC  80 03 00 E0 */	lwz r0, 0xe0(r3)
/* 8008FCD0 0008C8B0  2C 00 00 01 */	cmpwi r0, 1
/* 8008FCD4 0008C8B4  40 82 00 2C */	bne lbl_8008FD00
/* 8008FCD8 0008C8B8  C0 3F 00 8C */	lfs f1, 0x8c(r31)
/* 8008FCDC 0008C8BC  C0 1F 00 90 */	lfs f0, 0x90(r31)
/* 8008FCE0 0008C8C0  EC 21 00 72 */	fmuls f1, f1, f1
/* 8008FCE4 0008C8C4  C0 5F 00 94 */	lfs f2, 0x94(r31)
/* 8008FCE8 0008C8C8  EC 00 00 32 */	fmuls f0, f0, f0
/* 8008FCEC 0008C8CC  EC 42 00 B2 */	fmuls f2, f2, f2
/* 8008FCF0 0008C8D0  EC 01 00 2A */	fadds f0, f1, f0
/* 8008FCF4 0008C8D4  EC 22 00 2A */	fadds f1, f2, f0
/* 8008FCF8 0008C8D8  4B F7 D8 C5 */	bl sqrtf__Ff
/* 8008FCFC 0008C8DC  48 00 00 18 */	b lbl_8008FD14
lbl_8008FD00:
/* 8008FD00 0008C8E0  C0 3F 00 F0 */	lfs f1, 0xf0(r31)
/* 8008FD04 0008C8E4  C0 02 8A F4 */	lfs f0, lbl_804D84D4(r2)
/* 8008FD08 0008C8E8  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8008FD0C 0008C8EC  40 80 00 08 */	bge lbl_8008FD14
/* 8008FD10 0008C8F0  FC 20 08 50 */	fneg f1, f1
lbl_8008FD14:
/* 8008FD14 0008C8F4  80 6D AE B4 */	lwz r3, p_ftCommonData(r13)
/* 8008FD18 0008C8F8  C0 03 05 68 */	lfs f0, 0x568(r3)
/* 8008FD1C 0008C8FC  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8008FD20 0008C900  40 80 00 0C */	bge lbl_8008FD2C
/* 8008FD24 0008C904  38 00 00 00 */	li r0, 0
/* 8008FD28 0008C908  48 00 00 58 */	b lbl_8008FD80
lbl_8008FD2C:
/* 8008FD2C 0008C90C  C0 03 05 6C */	lfs f0, 0x56c(r3)
/* 8008FD30 0008C910  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8008FD34 0008C914  40 80 00 0C */	bge lbl_8008FD40
/* 8008FD38 0008C918  80 03 05 7C */	lwz r0, 0x57c(r3)
/* 8008FD3C 0008C91C  48 00 00 44 */	b lbl_8008FD80
lbl_8008FD40:
/* 8008FD40 0008C920  C0 03 05 70 */	lfs f0, 0x570(r3)
/* 8008FD44 0008C924  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8008FD48 0008C928  40 80 00 0C */	bge lbl_8008FD54
/* 8008FD4C 0008C92C  80 03 05 7C */	lwz r0, 0x57c(r3)
/* 8008FD50 0008C930  48 00 00 30 */	b lbl_8008FD80
lbl_8008FD54:
/* 8008FD54 0008C934  C0 03 05 74 */	lfs f0, 0x574(r3)
/* 8008FD58 0008C938  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8008FD5C 0008C93C  40 80 00 0C */	bge lbl_8008FD68
/* 8008FD60 0008C940  80 03 05 80 */	lwz r0, 0x580(r3)
/* 8008FD64 0008C944  48 00 00 1C */	b lbl_8008FD80
lbl_8008FD68:
/* 8008FD68 0008C948  C0 03 05 78 */	lfs f0, 0x578(r3)
/* 8008FD6C 0008C94C  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8008FD70 0008C950  40 80 00 0C */	bge lbl_8008FD7C
/* 8008FD74 0008C954  80 03 05 84 */	lwz r0, 0x584(r3)
/* 8008FD78 0008C958  48 00 00 08 */	b lbl_8008FD80
lbl_8008FD7C:
/* 8008FD7C 0008C95C  80 03 05 88 */	lwz r0, 0x588(r3)
lbl_8008FD80:
/* 8008FD80 0008C960  90 1F 23 48 */	stw r0, 0x2348(r31)
/* 8008FD84 0008C964  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 8008FD88 0008C968  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 8008FD8C 0008C96C  38 21 00 18 */	addi r1, r1, 0x18
/* 8008FD90 0008C970  7C 08 03 A6 */	mtlr r0
/* 8008FD94 0008C974  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

#pragma push
asm unk_t func_8008FD98()
{ // clang-format off
    nofralloc
/* 8008FD98 0008C978  7C 08 02 A6 */	mflr r0
/* 8008FD9C 0008C97C  90 01 00 04 */	stw r0, 4(r1)
/* 8008FDA0 0008C980  94 21 FF C0 */	stwu r1, -0x40(r1)
/* 8008FDA4 0008C984  93 E1 00 3C */	stw r31, 0x3c(r1)
/* 8008FDA8 0008C988  7C 7F 1B 78 */	mr r31, r3
/* 8008FDAC 0008C98C  93 C1 00 38 */	stw r30, 0x38(r1)
/* 8008FDB0 0008C990  93 A1 00 34 */	stw r29, 0x34(r1)
/* 8008FDB4 0008C994  83 C3 00 2C */	lwz r30, 0x2c(r3)
/* 8008FDB8 0008C998  80 7E 23 48 */	lwz r3, 0x2348(r30)
/* 8008FDBC 0008C99C  2C 03 00 00 */	cmpwi r3, 0
/* 8008FDC0 0008C9A0  41 82 00 84 */	beq lbl_8008FE44
/* 8008FDC4 0008C9A4  38 03 FF FF */	addi r0, r3, -1
/* 8008FDC8 0008C9A8  90 1E 23 48 */	stw r0, 0x2348(r30)
/* 8008FDCC 0008C9AC  80 1E 23 48 */	lwz r0, 0x2348(r30)
/* 8008FDD0 0008C9B0  2C 00 00 00 */	cmpwi r0, 0
/* 8008FDD4 0008C9B4  40 82 00 70 */	bne lbl_8008FE44
/* 8008FDD8 0008C9B8  80 1E 00 E0 */	lwz r0, 0xe0(r30)
/* 8008FDDC 0008C9BC  2C 00 00 01 */	cmpwi r0, 1
/* 8008FDE0 0008C9C0  40 82 00 10 */	bne lbl_8008FDF0
/* 8008FDE4 0008C9C4  C0 3E 00 8C */	lfs f1, 0x8c(r30)
/* 8008FDE8 0008C9C8  C0 5E 00 90 */	lfs f2, 0x90(r30)
/* 8008FDEC 0008C9CC  48 00 00 1C */	b lbl_8008FE08
lbl_8008FDF0:
/* 8008FDF0 0008C9D0  C0 1E 08 44 */	lfs f0, 0x844(r30)
/* 8008FDF4 0008C9D4  C0 5E 00 F0 */	lfs f2, 0xf0(r30)
/* 8008FDF8 0008C9D8  FC 00 00 50 */	fneg f0, f0
/* 8008FDFC 0008C9DC  C0 3E 08 48 */	lfs f1, 0x848(r30)
/* 8008FE00 0008C9E0  EC 21 00 B2 */	fmuls f1, f1, f2
/* 8008FE04 0008C9E4  EC 40 00 B2 */	fmuls f2, f0, f2
lbl_8008FE08:
/* 8008FE08 0008C9E8  FC 20 08 50 */	fneg f1, f1
/* 8008FE0C 0008C9EC  4B F9 2E 25 */	bl atan2f
/* 8008FE10 0008C9F0  D0 21 00 28 */	stfs f1, 0x28(r1)
/* 8008FE14 0008C9F4  38 7F 00 00 */	addi r3, r31, 0
/* 8008FE18 0008C9F8  39 01 00 28 */	addi r8, r1, 0x28
/* 8008FE1C 0008C9FC  4C C6 31 82 */	crclr 6
/* 8008FE20 0008CA00  80 9E 05 E8 */	lwz r4, 0x5e8(r30)
/* 8008FE24 0008CA04  81 3F 00 2C */	lwz r9, 0x2c(r31)
/* 8008FE28 0008CA08  38 A0 00 04 */	li r5, 4
/* 8008FE2C 0008CA0C  80 E4 00 00 */	lwz r7, 0(r4)
/* 8008FE30 0008CA10  38 C0 04 08 */	li r6, 0x408
/* 8008FE34 0008CA14  38 89 06 0C */	addi r4, r9, 0x60c
/* 8008FE38 0008CA18  4B FD 78 B9 */	bl efAsync_Spawn
/* 8008FE3C 0008CA1C  7F C3 F3 78 */	mr r3, r30
/* 8008FE40 0008CA20  4B FF FE 79 */	bl func_8008FCB8
lbl_8008FE44:
/* 8008FE44 0008CA24  83 BF 00 2C */	lwz r29, 0x2c(r31)
/* 8008FE48 0008CA28  C0 02 8A F4 */	lfs f0, lbl_804D84D4(r2)
/* 8008FE4C 0008CA2C  C0 3D 23 40 */	lfs f1, 0x2340(r29)
/* 8008FE50 0008CA30  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8008FE54 0008CA34  40 81 00 10 */	ble lbl_8008FE64
/* 8008FE58 0008CA38  C0 02 8A F8 */	lfs f0, lbl_804D84D8(r2)
/* 8008FE5C 0008CA3C  EC 01 00 28 */	fsubs f0, f1, f0
/* 8008FE60 0008CA40  D0 1D 23 40 */	stfs f0, 0x2340(r29)
lbl_8008FE64:
/* 8008FE64 0008CA44  88 7D 22 1C */	lbz r3, 0x221c(r29)
/* 8008FE68 0008CA48  54 60 FF FF */	rlwinm. r0, r3, 0x1f, 0x1f, 0x1f
/* 8008FE6C 0008CA4C  41 82 00 50 */	beq lbl_8008FEBC
/* 8008FE70 0008CA50  C0 3D 23 40 */	lfs f1, 0x2340(r29)
/* 8008FE74 0008CA54  C0 02 8A F4 */	lfs f0, lbl_804D84D4(r2)
/* 8008FE78 0008CA58  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8008FE7C 0008CA5C  4C 40 13 82 */	cror 2, 0, 2
/* 8008FE80 0008CA60  40 82 00 3C */	bne lbl_8008FEBC
/* 8008FE84 0008CA64  38 00 00 00 */	li r0, 0
/* 8008FE88 0008CA68  50 03 0F BC */	rlwimi r3, r0, 1, 0x1e, 0x1e
/* 8008FE8C 0008CA6C  98 7D 22 1C */	stb r3, 0x221c(r29)
/* 8008FE90 0008CA70  7F E3 FB 78 */	mr r3, r31
/* 8008FE94 0008CA74  80 8D AE B4 */	lwz r4, p_ftCommonData(r13)
/* 8008FE98 0008CA78  80 04 04 CC */	lwz r0, 0x4cc(r4)
/* 8008FE9C 0008CA7C  B0 1D 20 98 */	sth r0, 0x2098(r29)
/* 8008FEA0 0008CA80  4B FE F9 CD */	bl func_8007F86C
/* 8008FEA4 0008CA84  7F E3 FB 78 */	mr r3, r31
/* 8008FEA8 0008CA88  48 03 53 99 */	bl func_800C5240
/* 8008FEAC 0008CA8C  2C 03 00 00 */	cmpwi r3, 0
/* 8008FEB0 0008CA90  41 82 00 0C */	beq lbl_8008FEBC
/* 8008FEB4 0008CA94  7F A3 EB 78 */	mr r3, r29
/* 8008FEB8 0008CA98  48 03 56 95 */	bl func_800C554C
lbl_8008FEBC:
/* 8008FEBC 0008CA9C  7F E3 FB 78 */	mr r3, r31
/* 8008FEC0 0008CAA0  4B FD F3 79 */	bl ftAnim_IsFramesRemaining
/* 8008FEC4 0008CAA4  2C 03 00 00 */	cmpwi r3, 0
/* 8008FEC8 0008CAA8  40 82 00 64 */	bne lbl_8008FF2C
/* 8008FECC 0008CAAC  88 1E 22 1C */	lbz r0, 0x221c(r30)
/* 8008FED0 0008CAB0  54 00 FF FF */	rlwinm. r0, r0, 0x1f, 0x1f, 0x1f
/* 8008FED4 0008CAB4  40 82 00 58 */	bne lbl_8008FF2C
/* 8008FED8 0008CAB8  80 9F 00 2C */	lwz r4, 0x2c(r31)
/* 8008FEDC 0008CABC  C0 02 8A F4 */	lfs f0, lbl_804D84D4(r2)
/* 8008FEE0 0008CAC0  C0 24 23 54 */	lfs f1, 0x2354(r4)
/* 8008FEE4 0008CAC4  FC 01 00 00 */	fcmpu cr0, f1, f0
/* 8008FEE8 0008CAC8  41 82 00 30 */	beq lbl_8008FF18
/* 8008FEEC 0008CACC  80 6D AE B4 */	lwz r3, p_ftCommonData(r13)
/* 8008FEF0 0008CAD0  C0 03 01 D0 */	lfs f0, 0x1d0(r3)
/* 8008FEF4 0008CAD4  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8008FEF8 0008CAD8  4C 40 13 82 */	cror 2, 0, 2
/* 8008FEFC 0008CADC  40 82 00 1C */	bne lbl_8008FF18
/* 8008FF00 0008CAE0  80 04 06 68 */	lwz r0, 0x668(r4)
/* 8008FF04 0008CAE4  38 7F 00 00 */	addi r3, r31, 0
/* 8008FF08 0008CAE8  60 00 0C 00 */	ori r0, r0, 0xc00
/* 8008FF0C 0008CAEC  90 04 06 68 */	stw r0, 0x668(r4)
/* 8008FF10 0008CAF0  48 03 B9 61 */	bl func_800CB870
/* 8008FF14 0008CAF4  48 00 00 08 */	b lbl_8008FF1C
lbl_8008FF18:
/* 8008FF18 0008CAF8  38 60 00 00 */	li r3, 0
lbl_8008FF1C:
/* 8008FF1C 0008CAFC  2C 03 00 00 */	cmpwi r3, 0
/* 8008FF20 0008CB00  40 82 00 0C */	bne lbl_8008FF2C
/* 8008FF24 0008CB04  7F E3 FB 78 */	mr r3, r31
/* 8008FF28 0008CB08  48 00 08 59 */	bl func_80090780
lbl_8008FF2C:
/* 8008FF2C 0008CB0C  80 01 00 44 */	lwz r0, 0x44(r1)
/* 8008FF30 0008CB10  83 E1 00 3C */	lwz r31, 0x3c(r1)
/* 8008FF34 0008CB14  83 C1 00 38 */	lwz r30, 0x38(r1)
/* 8008FF38 0008CB18  83 A1 00 34 */	lwz r29, 0x34(r1)
/* 8008FF3C 0008CB1C  38 21 00 40 */	addi r1, r1, 0x40
/* 8008FF40 0008CB20  7C 08 03 A6 */	mtlr r0
/* 8008FF44 0008CB24  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

#pragma push
asm unk_t func_8008FF48()
{ // clang-format off
    nofralloc
/* 8008FF48 0008CB28  7C 08 02 A6 */	mflr r0
/* 8008FF4C 0008CB2C  90 01 00 04 */	stw r0, 4(r1)
/* 8008FF50 0008CB30  94 21 FF F8 */	stwu r1, -8(r1)
/* 8008FF54 0008CB34  80 83 00 2C */	lwz r4, 0x2c(r3)
/* 8008FF58 0008CB38  88 04 22 1C */	lbz r0, 0x221c(r4)
/* 8008FF5C 0008CB3C  54 00 FF FF */	rlwinm. r0, r0, 0x1f, 0x1f, 0x1f
/* 8008FF60 0008CB40  40 82 00 0C */	bne lbl_8008FF6C
/* 8008FF64 0008CB44  48 00 08 C5 */	bl func_80090828
/* 8008FF68 0008CB48  48 00 00 0C */	b lbl_8008FF74
lbl_8008FF6C:
/* 8008FF6C 0008CB4C  4B FF F9 CD */	bl func_8008F938
/* 8008FF70 0008CB50  2C 03 00 00 */	cmpwi r3, 0
lbl_8008FF74:
/* 8008FF74 0008CB54  80 01 00 0C */	lwz r0, 0xc(r1)
/* 8008FF78 0008CB58  38 21 00 08 */	addi r1, r1, 8
/* 8008FF7C 0008CB5C  7C 08 03 A6 */	mtlr r0
/* 8008FF80 0008CB60  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

#pragma push
asm unk_t func_8008FF84()
{ // clang-format off
    nofralloc
/* 8008FF84 0008CB64  7C 08 02 A6 */	mflr r0
/* 8008FF88 0008CB68  90 01 00 04 */	stw r0, 4(r1)
/* 8008FF8C 0008CB6C  94 21 FF C8 */	stwu r1, -0x38(r1)
/* 8008FF90 0008CB70  DB E1 00 30 */	stfd f31, 0x30(r1)
/* 8008FF94 0008CB74  93 E1 00 2C */	stw r31, 0x2c(r1)
/* 8008FF98 0008CB78  93 C1 00 28 */	stw r30, 0x28(r1)
/* 8008FF9C 0008CB7C  93 A1 00 24 */	stw r29, 0x24(r1)
/* 8008FFA0 0008CB80  7C 7D 1B 78 */	mr r29, r3
/* 8008FFA4 0008CB84  83 C3 00 2C */	lwz r30, 0x2c(r3)
/* 8008FFA8 0008CB88  80 1E 00 E0 */	lwz r0, 0xe0(r30)
/* 8008FFAC 0008CB8C  2C 00 00 01 */	cmpwi r0, 1
/* 8008FFB0 0008CB90  40 82 00 28 */	bne lbl_8008FFD8
/* 8008FFB4 0008CB94  88 1E 22 1C */	lbz r0, 0x221c(r30)
/* 8008FFB8 0008CB98  54 00 FF FF */	rlwinm. r0, r0, 0x1f, 0x1f, 0x1f
/* 8008FFBC 0008CB9C  40 82 00 10 */	bne lbl_8008FFCC
/* 8008FFC0 0008CBA0  7F A3 EB 78 */	mr r3, r29
/* 8008FFC4 0008CBA4  4B FF 4D ED */	bl func_80084DB0
/* 8008FFC8 0008CBA8  48 00 00 18 */	b lbl_8008FFE0
lbl_8008FFCC:
/* 8008FFCC 0008CBAC  7F A3 EB 78 */	mr r3, r29
/* 8008FFD0 0008CBB0  4B FF 4F 1D */	bl func_80084EEC
/* 8008FFD4 0008CBB4  48 00 00 0C */	b lbl_8008FFE0
lbl_8008FFD8:
/* 8008FFD8 0008CBB8  7F A3 EB 78 */	mr r3, r29
/* 8008FFDC 0008CBBC  4B FF 4F 61 */	bl func_80084F3C
lbl_8008FFE0:
/* 8008FFE0 0008CBC0  80 1E 00 10 */	lwz r0, 0x10(r30)
/* 8008FFE4 0008CBC4  2C 00 00 5B */	cmpwi r0, 0x5b
/* 8008FFE8 0008CBC8  40 82 00 48 */	bne lbl_80090030
/* 8008FFEC 0008CBCC  83 FD 00 2C */	lwz r31, 0x2c(r29)
/* 8008FFF0 0008CBD0  C0 7F 00 80 */	lfs f3, 0x80(r31)
/* 8008FFF4 0008CBD4  C0 3F 00 8C */	lfs f1, 0x8c(r31)
/* 8008FFF8 0008CBD8  C0 5F 00 84 */	lfs f2, 0x84(r31)
/* 8008FFFC 0008CBDC  C0 1F 00 90 */	lfs f0, 0x90(r31)
/* 80090000 0008CBE0  EC 23 08 2A */	fadds f1, f3, f1
/* 80090004 0008CBE4  EC 42 00 2A */	fadds f2, f2, f0
/* 80090008 0008CBE8  4B F9 2C 29 */	bl atan2f
/* 8009000C 0008CBEC  C0 1F 00 2C */	lfs f0, 0x2c(r31)
/* 80090010 0008CBF0  38 7F 00 00 */	addi r3, r31, 0
/* 80090014 0008CBF4  38 80 00 02 */	li r4, 2
/* 80090018 0008CBF8  EF E0 00 72 */	fmuls f31, f0, f1
/* 8009001C 0008CBFC  4B FE 4F F1 */	bl func_8007500C
/* 80090020 0008CC00  FC 20 F8 90 */	fmr f1, f31
/* 80090024 0008CC04  38 83 00 00 */	addi r4, r3, 0
/* 80090028 0008CC08  38 7F 00 00 */	addi r3, r31, 0
/* 8009002C 0008CC0C  4B FE 59 01 */	bl func_8007592C
lbl_80090030:
/* 80090030 0008CC10  80 1E 11 98 */	lwz r0, 0x1198(r30)
/* 80090034 0008CC14  28 00 00 00 */	cmplwi r0, 0
/* 80090038 0008CC18  41 82 00 94 */	beq lbl_800900CC
/* 8009003C 0008CC1C  C0 3E 00 8C */	lfs f1, 0x8c(r30)
/* 80090040 0008CC20  C0 1E 00 90 */	lfs f0, 0x90(r30)
/* 80090044 0008CC24  EC 41 00 72 */	fmuls f2, f1, f1
/* 80090048 0008CC28  C0 7E 00 94 */	lfs f3, 0x94(r30)
/* 8009004C 0008CC2C  EC 20 00 32 */	fmuls f1, f0, f0
/* 80090050 0008CC30  C0 02 8A F4 */	lfs f0, lbl_804D84D4(r2)
/* 80090054 0008CC34  EC 63 00 F2 */	fmuls f3, f3, f3
/* 80090058 0008CC38  EC 22 08 2A */	fadds f1, f2, f1
/* 8009005C 0008CC3C  EC 83 08 2A */	fadds f4, f3, f1
/* 80090060 0008CC40  FC 04 00 40 */	fcmpo cr0, f4, f0
/* 80090064 0008CC44  40 81 00 50 */	ble lbl_800900B4
/* 80090068 0008CC48  FC 20 20 34 */	frsqrte f1, f4
/* 8009006C 0008CC4C  C8 62 8B 20 */	lfd f3, lbl_804D8500(r2)
/* 80090070 0008CC50  C8 42 8B 28 */	lfd f2, lbl_804D8508(r2)
/* 80090074 0008CC54  FC 01 00 72 */	fmul f0, f1, f1
/* 80090078 0008CC58  FC 23 00 72 */	fmul f1, f3, f1
/* 8009007C 0008CC5C  FC 04 10 3C */	fnmsub f0, f4, f0, f2
/* 80090080 0008CC60  FC 21 00 32 */	fmul f1, f1, f0
/* 80090084 0008CC64  FC 01 00 72 */	fmul f0, f1, f1
/* 80090088 0008CC68  FC 23 00 72 */	fmul f1, f3, f1
/* 8009008C 0008CC6C  FC 04 10 3C */	fnmsub f0, f4, f0, f2
/* 80090090 0008CC70  FC 21 00 32 */	fmul f1, f1, f0
/* 80090094 0008CC74  FC 01 00 72 */	fmul f0, f1, f1
/* 80090098 0008CC78  FC 23 00 72 */	fmul f1, f3, f1
/* 8009009C 0008CC7C  FC 04 10 3C */	fnmsub f0, f4, f0, f2
/* 800900A0 0008CC80  FC 01 00 32 */	fmul f0, f1, f0
/* 800900A4 0008CC84  FC 04 00 32 */	fmul f0, f4, f0
/* 800900A8 0008CC88  FC 00 00 18 */	frsp f0, f0
/* 800900AC 0008CC8C  D0 01 00 18 */	stfs f0, 0x18(r1)
/* 800900B0 0008CC90  C0 81 00 18 */	lfs f4, 0x18(r1)
lbl_800900B4:
/* 800900B4 0008CC94  80 6D AE B4 */	lwz r3, p_ftCommonData(r13)
/* 800900B8 0008CC98  C0 03 01 C8 */	lfs f0, 0x1c8(r3)
/* 800900BC 0008CC9C  FC 04 00 40 */	fcmpo cr0, f4, f0
/* 800900C0 0008CCA0  40 80 00 0C */	bge lbl_800900CC
/* 800900C4 0008CCA4  7F A3 EB 78 */	mr r3, r29
/* 800900C8 0008CCA8  4B FE AF 31 */	bl func_8007AFF8
lbl_800900CC:
/* 800900CC 0008CCAC  80 01 00 3C */	lwz r0, 0x3c(r1)
/* 800900D0 0008CCB0  CB E1 00 30 */	lfd f31, 0x30(r1)
/* 800900D4 0008CCB4  83 E1 00 2C */	lwz r31, 0x2c(r1)
/* 800900D8 0008CCB8  83 C1 00 28 */	lwz r30, 0x28(r1)
/* 800900DC 0008CCBC  83 A1 00 24 */	lwz r29, 0x24(r1)
/* 800900E0 0008CCC0  38 21 00 38 */	addi r1, r1, 0x38
/* 800900E4 0008CCC4  7C 08 03 A6 */	mtlr r0
/* 800900E8 0008CCC8  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

extern unk_t func_800C17CC();
extern unk_t func_800C23A0();
extern unk_t func_800C1D38();
extern unk_t func_80090184();

#pragma push
asm unk_t func_800900EC()
{ // clang-format off
    nofralloc
/* 800900EC 0008CCCC  7C 08 02 A6 */	mflr r0
/* 800900F0 0008CCD0  90 01 00 04 */	stw r0, 4(r1)
/* 800900F4 0008CCD4  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 800900F8 0008CCD8  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 800900FC 0008CCDC  93 C1 00 18 */	stw r30, 0x18(r1)
/* 80090100 0008CCE0  7C 7E 1B 78 */	mr r30, r3
/* 80090104 0008CCE4  80 83 00 2C */	lwz r4, 0x2c(r3)
/* 80090108 0008CCE8  3B E4 06 F0 */	addi r31, r4, 0x6f0
/* 8009010C 0008CCEC  4B FF 1C C9 */	bl func_80081DD4
/* 80090110 0008CCF0  2C 03 00 00 */	cmpwi r3, 0
/* 80090114 0008CCF4  41 82 00 10 */	beq lbl_80090124
/* 80090118 0008CCF8  7F C3 F3 78 */	mr r3, r30
/* 8009011C 0008CCFC  48 00 00 69 */	bl func_80090184
/* 80090120 0008CD00  48 00 00 4C */	b lbl_8009016C
lbl_80090124:
/* 80090124 0008CD04  80 7F 01 34 */	lwz r3, 0x134(r31)
/* 80090128 0008CD08  54 60 05 29 */	rlwinm. r0, r3, 0, 0x14, 0x14
/* 8009012C 0008CD0C  40 82 00 14 */	bne lbl_80090140
/* 80090130 0008CD10  54 60 06 B5 */	rlwinm. r0, r3, 0, 0x1a, 0x1a
/* 80090134 0008CD14  40 82 00 0C */	bne lbl_80090140
/* 80090138 0008CD18  54 60 04 63 */	rlwinm. r0, r3, 0, 0x11, 0x11
/* 8009013C 0008CD1C  41 82 00 30 */	beq lbl_8009016C
lbl_80090140:
/* 80090140 0008CD20  7F C3 F3 78 */	mr r3, r30
/* 80090144 0008CD24  48 03 1B F5 */	bl func_800C1D38
/* 80090148 0008CD28  2C 03 00 00 */	cmpwi r3, 0
/* 8009014C 0008CD2C  40 82 00 20 */	bne lbl_8009016C
/* 80090150 0008CD30  7F C3 F3 78 */	mr r3, r30
/* 80090154 0008CD34  48 03 22 4D */	bl func_800C23A0
/* 80090158 0008CD38  2C 03 00 00 */	cmpwi r3, 0
/* 8009015C 0008CD3C  40 82 00 10 */	bne lbl_8009016C
/* 80090160 0008CD40  7F C3 F3 78 */	mr r3, r30
/* 80090164 0008CD44  48 03 16 69 */	bl func_800C17CC
/* 80090168 0008CD48  2C 03 00 00 */	cmpwi r3, 0
lbl_8009016C:
/* 8009016C 0008CD4C  80 01 00 24 */	lwz r0, 0x24(r1)
/* 80090170 0008CD50  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 80090174 0008CD54  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 80090178 0008CD58  38 21 00 20 */	addi r1, r1, 0x20
/* 8009017C 0008CD5C  7C 08 03 A6 */	mtlr r0
/* 80090180 0008CD60  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

extern unk_t func_8009872C();
extern unk_t func_80098928();

#pragma push
asm unk_t func_80090184()
{ // clang-format off
    nofralloc
/* 80090184 0008CD64  7C 08 02 A6 */	mflr r0
/* 80090188 0008CD68  90 01 00 04 */	stw r0, 4(r1)
/* 8009018C 0008CD6C  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 80090190 0008CD70  93 E1 00 14 */	stw r31, 0x14(r1)
/* 80090194 0008CD74  7C 7F 1B 78 */	mr r31, r3
/* 80090198 0008CD78  48 00 87 91 */	bl func_80098928
/* 8009019C 0008CD7C  2C 03 00 00 */	cmpwi r3, 0
/* 800901A0 0008CD80  40 82 00 1C */	bne lbl_800901BC
/* 800901A4 0008CD84  7F E3 FB 78 */	mr r3, r31
/* 800901A8 0008CD88  48 00 85 85 */	bl func_8009872C
/* 800901AC 0008CD8C  2C 03 00 00 */	cmpwi r3, 0
/* 800901B0 0008CD90  40 82 00 0C */	bne lbl_800901BC
/* 800901B4 0008CD94  7F E3 FB 78 */	mr r3, r31
/* 800901B8 0008CD98  48 00 7B 89 */	bl func_80097D40
lbl_800901BC:
/* 800901BC 0008CD9C  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 800901C0 0008CDA0  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 800901C4 0008CDA4  38 21 00 18 */	addi r1, r1, 0x18
/* 800901C8 0008CDA8  7C 08 03 A6 */	mtlr r0
/* 800901CC 0008CDAC  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

#pragma push
asm unk_t func_800901D0()
{ // clang-format off
    nofralloc
/* 800901D0 0008CDB0  7C 08 02 A6 */	mflr r0
/* 800901D4 0008CDB4  90 01 00 04 */	stw r0, 4(r1)
/* 800901D8 0008CDB8  94 21 FF C0 */	stwu r1, -0x40(r1)
/* 800901DC 0008CDBC  93 E1 00 3C */	stw r31, 0x3c(r1)
/* 800901E0 0008CDC0  7C 7F 1B 78 */	mr r31, r3
/* 800901E4 0008CDC4  93 C1 00 38 */	stw r30, 0x38(r1)
/* 800901E8 0008CDC8  93 A1 00 34 */	stw r29, 0x34(r1)
/* 800901EC 0008CDCC  83 C3 00 2C */	lwz r30, 0x2c(r3)
/* 800901F0 0008CDD0  80 7E 23 48 */	lwz r3, 0x2348(r30)
/* 800901F4 0008CDD4  2C 03 00 00 */	cmpwi r3, 0
/* 800901F8 0008CDD8  41 82 00 84 */	beq lbl_8009027C
/* 800901FC 0008CDDC  38 03 FF FF */	addi r0, r3, -1
/* 80090200 0008CDE0  90 1E 23 48 */	stw r0, 0x2348(r30)
/* 80090204 0008CDE4  80 1E 23 48 */	lwz r0, 0x2348(r30)
/* 80090208 0008CDE8  2C 00 00 00 */	cmpwi r0, 0
/* 8009020C 0008CDEC  40 82 00 70 */	bne lbl_8009027C
/* 80090210 0008CDF0  80 1E 00 E0 */	lwz r0, 0xe0(r30)
/* 80090214 0008CDF4  2C 00 00 01 */	cmpwi r0, 1
/* 80090218 0008CDF8  40 82 00 10 */	bne lbl_80090228
/* 8009021C 0008CDFC  C0 3E 00 8C */	lfs f1, 0x8c(r30)
/* 80090220 0008CE00  C0 5E 00 90 */	lfs f2, 0x90(r30)
/* 80090224 0008CE04  48 00 00 1C */	b lbl_80090240
lbl_80090228:
/* 80090228 0008CE08  C0 1E 08 44 */	lfs f0, 0x844(r30)
/* 8009022C 0008CE0C  C0 5E 00 F0 */	lfs f2, 0xf0(r30)
/* 80090230 0008CE10  FC 00 00 50 */	fneg f0, f0
/* 80090234 0008CE14  C0 3E 08 48 */	lfs f1, 0x848(r30)
/* 80090238 0008CE18  EC 21 00 B2 */	fmuls f1, f1, f2
/* 8009023C 0008CE1C  EC 40 00 B2 */	fmuls f2, f0, f2
lbl_80090240:
/* 80090240 0008CE20  FC 20 08 50 */	fneg f1, f1
/* 80090244 0008CE24  4B F9 29 ED */	bl atan2f
/* 80090248 0008CE28  D0 21 00 24 */	stfs f1, 0x24(r1)
/* 8009024C 0008CE2C  38 7F 00 00 */	addi r3, r31, 0
/* 80090250 0008CE30  39 01 00 24 */	addi r8, r1, 0x24
/* 80090254 0008CE34  4C C6 31 82 */	crclr 6
/* 80090258 0008CE38  80 9E 05 E8 */	lwz r4, 0x5e8(r30)
/* 8009025C 0008CE3C  81 3F 00 2C */	lwz r9, 0x2c(r31)
/* 80090260 0008CE40  38 A0 00 04 */	li r5, 4
/* 80090264 0008CE44  80 E4 00 00 */	lwz r7, 0(r4)
/* 80090268 0008CE48  38 C0 04 08 */	li r6, 0x408
/* 8009026C 0008CE4C  38 89 06 0C */	addi r4, r9, 0x60c
/* 80090270 0008CE50  4B FD 74 81 */	bl efAsync_Spawn
/* 80090274 0008CE54  7F C3 F3 78 */	mr r3, r30
/* 80090278 0008CE58  4B FF FA 41 */	bl func_8008FCB8
lbl_8009027C:
/* 8009027C 0008CE5C  83 BF 00 2C */	lwz r29, 0x2c(r31)
/* 80090280 0008CE60  C0 02 8A F4 */	lfs f0, lbl_804D84D4(r2)
/* 80090284 0008CE64  C0 3D 23 40 */	lfs f1, 0x2340(r29)
/* 80090288 0008CE68  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8009028C 0008CE6C  40 81 00 10 */	ble lbl_8009029C
/* 80090290 0008CE70  C0 02 8A F8 */	lfs f0, lbl_804D84D8(r2)
/* 80090294 0008CE74  EC 01 00 28 */	fsubs f0, f1, f0
/* 80090298 0008CE78  D0 1D 23 40 */	stfs f0, 0x2340(r29)
lbl_8009029C:
/* 8009029C 0008CE7C  88 7D 22 1C */	lbz r3, 0x221c(r29)
/* 800902A0 0008CE80  54 60 FF FF */	rlwinm. r0, r3, 0x1f, 0x1f, 0x1f
/* 800902A4 0008CE84  41 82 00 50 */	beq lbl_800902F4
/* 800902A8 0008CE88  C0 3D 23 40 */	lfs f1, 0x2340(r29)
/* 800902AC 0008CE8C  C0 02 8A F4 */	lfs f0, lbl_804D84D4(r2)
/* 800902B0 0008CE90  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 800902B4 0008CE94  4C 40 13 82 */	cror 2, 0, 2
/* 800902B8 0008CE98  40 82 00 3C */	bne lbl_800902F4
/* 800902BC 0008CE9C  38 00 00 00 */	li r0, 0
/* 800902C0 0008CEA0  50 03 0F BC */	rlwimi r3, r0, 1, 0x1e, 0x1e
/* 800902C4 0008CEA4  98 7D 22 1C */	stb r3, 0x221c(r29)
/* 800902C8 0008CEA8  7F E3 FB 78 */	mr r3, r31
/* 800902CC 0008CEAC  80 8D AE B4 */	lwz r4, p_ftCommonData(r13)
/* 800902D0 0008CEB0  80 04 04 CC */	lwz r0, 0x4cc(r4)
/* 800902D4 0008CEB4  B0 1D 20 98 */	sth r0, 0x2098(r29)
/* 800902D8 0008CEB8  4B FE F5 95 */	bl func_8007F86C
/* 800902DC 0008CEBC  7F E3 FB 78 */	mr r3, r31
/* 800902E0 0008CEC0  48 03 4F 61 */	bl func_800C5240
/* 800902E4 0008CEC4  2C 03 00 00 */	cmpwi r3, 0
/* 800902E8 0008CEC8  41 82 00 0C */	beq lbl_800902F4
/* 800902EC 0008CECC  7F A3 EB 78 */	mr r3, r29
/* 800902F0 0008CED0  48 03 52 5D */	bl func_800C554C
lbl_800902F4:
/* 800902F4 0008CED4  88 1E 22 1C */	lbz r0, 0x221c(r30)
/* 800902F8 0008CED8  54 00 FF FF */	rlwinm. r0, r0, 0x1f, 0x1f, 0x1f
/* 800902FC 0008CEDC  40 82 00 0C */	bne lbl_80090308
/* 80090300 0008CEE0  7F E3 FB 78 */	mr r3, r31
/* 80090304 0008CEE4  48 00 04 7D */	bl func_80090780
lbl_80090308:
/* 80090308 0008CEE8  80 01 00 44 */	lwz r0, 0x44(r1)
/* 8009030C 0008CEEC  83 E1 00 3C */	lwz r31, 0x3c(r1)
/* 80090310 0008CEF0  83 C1 00 38 */	lwz r30, 0x38(r1)
/* 80090314 0008CEF4  83 A1 00 34 */	lwz r29, 0x34(r1)
/* 80090318 0008CEF8  38 21 00 40 */	addi r1, r1, 0x40
/* 8009031C 0008CEFC  7C 08 03 A6 */	mtlr r0
/* 80090320 0008CF00  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

#pragma push
asm unk_t func_80090324()
{ // clang-format off
    nofralloc
/* 80090324 0008CF04  7C 08 02 A6 */	mflr r0
/* 80090328 0008CF08  90 01 00 04 */	stw r0, 4(r1)
/* 8009032C 0008CF0C  94 21 FF F8 */	stwu r1, -8(r1)
/* 80090330 0008CF10  80 83 00 2C */	lwz r4, 0x2c(r3)
/* 80090334 0008CF14  88 04 22 1C */	lbz r0, 0x221c(r4)
/* 80090338 0008CF18  54 00 FF FF */	rlwinm. r0, r0, 0x1f, 0x1f, 0x1f
/* 8009033C 0008CF1C  40 82 00 0C */	bne lbl_80090348
/* 80090340 0008CF20  48 00 04 E9 */	bl func_80090828
/* 80090344 0008CF24  48 00 00 08 */	b lbl_8009034C
lbl_80090348:
/* 80090348 0008CF28  4B FF F5 F1 */	bl func_8008F938
lbl_8009034C:
/* 8009034C 0008CF2C  80 01 00 0C */	lwz r0, 0xc(r1)
/* 80090350 0008CF30  38 21 00 08 */	addi r1, r1, 8
/* 80090354 0008CF34  7C 08 03 A6 */	mtlr r0
/* 80090358 0008CF38  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

#pragma push
asm unk_t func_8009035C()
{ // clang-format off
    nofralloc
/* 8009035C 0008CF3C  7C 08 02 A6 */	mflr r0
/* 80090360 0008CF40  90 01 00 04 */	stw r0, 4(r1)
/* 80090364 0008CF44  94 21 FF C8 */	stwu r1, -0x38(r1)
/* 80090368 0008CF48  DB E1 00 30 */	stfd f31, 0x30(r1)
/* 8009036C 0008CF4C  93 E1 00 2C */	stw r31, 0x2c(r1)
/* 80090370 0008CF50  93 C1 00 28 */	stw r30, 0x28(r1)
/* 80090374 0008CF54  93 A1 00 24 */	stw r29, 0x24(r1)
/* 80090378 0008CF58  7C 7D 1B 78 */	mr r29, r3
/* 8009037C 0008CF5C  83 C3 00 2C */	lwz r30, 0x2c(r3)
/* 80090380 0008CF60  80 1E 00 E0 */	lwz r0, 0xe0(r30)
/* 80090384 0008CF64  2C 00 00 01 */	cmpwi r0, 1
/* 80090388 0008CF68  40 82 00 28 */	bne lbl_800903B0
/* 8009038C 0008CF6C  88 1E 22 1C */	lbz r0, 0x221c(r30)
/* 80090390 0008CF70  54 00 FF FF */	rlwinm. r0, r0, 0x1f, 0x1f, 0x1f
/* 80090394 0008CF74  40 82 00 10 */	bne lbl_800903A4
/* 80090398 0008CF78  7F A3 EB 78 */	mr r3, r29
/* 8009039C 0008CF7C  4B FF 4A 15 */	bl func_80084DB0
/* 800903A0 0008CF80  48 00 00 18 */	b lbl_800903B8
lbl_800903A4:
/* 800903A4 0008CF84  7F A3 EB 78 */	mr r3, r29
/* 800903A8 0008CF88  4B FF 4B 45 */	bl func_80084EEC
/* 800903AC 0008CF8C  48 00 00 0C */	b lbl_800903B8
lbl_800903B0:
/* 800903B0 0008CF90  7F A3 EB 78 */	mr r3, r29
/* 800903B4 0008CF94  4B FF 4B 89 */	bl func_80084F3C
lbl_800903B8:
/* 800903B8 0008CF98  80 1E 00 10 */	lwz r0, 0x10(r30)
/* 800903BC 0008CF9C  2C 00 00 5B */	cmpwi r0, 0x5b
/* 800903C0 0008CFA0  40 82 00 48 */	bne lbl_80090408
/* 800903C4 0008CFA4  83 FD 00 2C */	lwz r31, 0x2c(r29)
/* 800903C8 0008CFA8  C0 7F 00 80 */	lfs f3, 0x80(r31)
/* 800903CC 0008CFAC  C0 3F 00 8C */	lfs f1, 0x8c(r31)
/* 800903D0 0008CFB0  C0 5F 00 84 */	lfs f2, 0x84(r31)
/* 800903D4 0008CFB4  C0 1F 00 90 */	lfs f0, 0x90(r31)
/* 800903D8 0008CFB8  EC 23 08 2A */	fadds f1, f3, f1
/* 800903DC 0008CFBC  EC 42 00 2A */	fadds f2, f2, f0
/* 800903E0 0008CFC0  4B F9 28 51 */	bl atan2f
/* 800903E4 0008CFC4  C0 1F 00 2C */	lfs f0, 0x2c(r31)
/* 800903E8 0008CFC8  38 7F 00 00 */	addi r3, r31, 0
/* 800903EC 0008CFCC  38 80 00 02 */	li r4, 2
/* 800903F0 0008CFD0  EF E0 00 72 */	fmuls f31, f0, f1
/* 800903F4 0008CFD4  4B FE 4C 19 */	bl func_8007500C
/* 800903F8 0008CFD8  FC 20 F8 90 */	fmr f1, f31
/* 800903FC 0008CFDC  38 83 00 00 */	addi r4, r3, 0
/* 80090400 0008CFE0  38 7F 00 00 */	addi r3, r31, 0
/* 80090404 0008CFE4  4B FE 55 29 */	bl func_8007592C
lbl_80090408:
/* 80090408 0008CFE8  80 1E 11 98 */	lwz r0, 0x1198(r30)
/* 8009040C 0008CFEC  28 00 00 00 */	cmplwi r0, 0
/* 80090410 0008CFF0  41 82 00 40 */	beq lbl_80090450
/* 80090414 0008CFF4  C0 3E 00 8C */	lfs f1, 0x8c(r30)
/* 80090418 0008CFF8  C0 1E 00 90 */	lfs f0, 0x90(r30)
/* 8009041C 0008CFFC  EC 21 00 72 */	fmuls f1, f1, f1
/* 80090420 0008D000  C0 5E 00 94 */	lfs f2, 0x94(r30)
/* 80090424 0008D004  EC 00 00 32 */	fmuls f0, f0, f0
/* 80090428 0008D008  EC 42 00 B2 */	fmuls f2, f2, f2
/* 8009042C 0008D00C  EC 01 00 2A */	fadds f0, f1, f0
/* 80090430 0008D010  EC 22 00 2A */	fadds f1, f2, f0
/* 80090434 0008D014  4B F7 D1 89 */	bl sqrtf__Ff
/* 80090438 0008D018  80 6D AE B4 */	lwz r3, p_ftCommonData(r13)
/* 8009043C 0008D01C  C0 03 01 C8 */	lfs f0, 0x1c8(r3)
/* 80090440 0008D020  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 80090444 0008D024  40 80 00 0C */	bge lbl_80090450
/* 80090448 0008D028  7F A3 EB 78 */	mr r3, r29
/* 8009044C 0008D02C  4B FE AB AD */	bl func_8007AFF8
lbl_80090450:
/* 80090450 0008D030  80 1E 00 10 */	lwz r0, 0x10(r30)
/* 80090454 0008D034  2C 00 00 5B */	cmpwi r0, 0x5b
/* 80090458 0008D038  40 82 00 48 */	bne lbl_800904A0
/* 8009045C 0008D03C  83 FD 00 2C */	lwz r31, 0x2c(r29)
/* 80090460 0008D040  C0 7F 00 80 */	lfs f3, 0x80(r31)
/* 80090464 0008D044  C0 3F 00 8C */	lfs f1, 0x8c(r31)
/* 80090468 0008D048  C0 5F 00 84 */	lfs f2, 0x84(r31)
/* 8009046C 0008D04C  C0 1F 00 90 */	lfs f0, 0x90(r31)
/* 80090470 0008D050  EC 23 08 2A */	fadds f1, f3, f1
/* 80090474 0008D054  EC 42 00 2A */	fadds f2, f2, f0
/* 80090478 0008D058  4B F9 27 B9 */	bl atan2f
/* 8009047C 0008D05C  C0 1F 00 2C */	lfs f0, 0x2c(r31)
/* 80090480 0008D060  38 7F 00 00 */	addi r3, r31, 0
/* 80090484 0008D064  38 80 00 02 */	li r4, 2
/* 80090488 0008D068  EF E0 00 72 */	fmuls f31, f0, f1
/* 8009048C 0008D06C  4B FE 4B 81 */	bl func_8007500C
/* 80090490 0008D070  FC 20 F8 90 */	fmr f1, f31
/* 80090494 0008D074  38 83 00 00 */	addi r4, r3, 0
/* 80090498 0008D078  38 7F 00 00 */	addi r3, r31, 0
/* 8009049C 0008D07C  4B FE 54 91 */	bl func_8007592C
lbl_800904A0:
/* 800904A0 0008D080  80 01 00 3C */	lwz r0, 0x3c(r1)
/* 800904A4 0008D084  CB E1 00 30 */	lfd f31, 0x30(r1)
/* 800904A8 0008D088  83 E1 00 2C */	lwz r31, 0x2c(r1)
/* 800904AC 0008D08C  83 C1 00 28 */	lwz r30, 0x28(r1)
/* 800904B0 0008D090  83 A1 00 24 */	lwz r29, 0x24(r1)
/* 800904B4 0008D094  38 21 00 38 */	addi r1, r1, 0x38
/* 800904B8 0008D098  7C 08 03 A6 */	mtlr r0
/* 800904BC 0008D09C  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

#pragma push
asm unk_t func_800904C0()
{ // clang-format off
    nofralloc
/* 800904C0 0008D0A0  7C 08 02 A6 */	mflr r0
/* 800904C4 0008D0A4  90 01 00 04 */	stw r0, 4(r1)
/* 800904C8 0008D0A8  94 21 FF D8 */	stwu r1, -0x28(r1)
/* 800904CC 0008D0AC  93 E1 00 24 */	stw r31, 0x24(r1)
/* 800904D0 0008D0B0  93 C1 00 20 */	stw r30, 0x20(r1)
/* 800904D4 0008D0B4  7C 7E 1B 78 */	mr r30, r3
/* 800904D8 0008D0B8  80 83 00 2C */	lwz r4, 0x2c(r3)
/* 800904DC 0008D0BC  3B E4 06 F0 */	addi r31, r4, 0x6f0
/* 800904E0 0008D0C0  4B FF 18 F5 */	bl func_80081DD4
/* 800904E4 0008D0C4  2C 03 00 00 */	cmpwi r3, 0
/* 800904E8 0008D0C8  41 82 00 30 */	beq lbl_80090518
/* 800904EC 0008D0CC  7F C3 F3 78 */	mr r3, r30
/* 800904F0 0008D0D0  48 00 84 39 */	bl func_80098928
/* 800904F4 0008D0D4  2C 03 00 00 */	cmpwi r3, 0
/* 800904F8 0008D0D8  40 82 00 64 */	bne lbl_8009055C
/* 800904FC 0008D0DC  7F C3 F3 78 */	mr r3, r30
/* 80090500 0008D0E0  48 00 82 2D */	bl func_8009872C
/* 80090504 0008D0E4  2C 03 00 00 */	cmpwi r3, 0
/* 80090508 0008D0E8  40 82 00 54 */	bne lbl_8009055C
/* 8009050C 0008D0EC  7F C3 F3 78 */	mr r3, r30
/* 80090510 0008D0F0  48 00 78 31 */	bl func_80097D40
/* 80090514 0008D0F4  48 00 00 48 */	b lbl_8009055C
lbl_80090518:
/* 80090518 0008D0F8  80 7F 01 34 */	lwz r3, 0x134(r31)
/* 8009051C 0008D0FC  54 60 05 29 */	rlwinm. r0, r3, 0, 0x14, 0x14
/* 80090520 0008D100  40 82 00 14 */	bne lbl_80090534
/* 80090524 0008D104  54 60 06 B5 */	rlwinm. r0, r3, 0, 0x1a, 0x1a
/* 80090528 0008D108  40 82 00 0C */	bne lbl_80090534
/* 8009052C 0008D10C  54 60 04 63 */	rlwinm. r0, r3, 0, 0x11, 0x11
/* 80090530 0008D110  41 82 00 2C */	beq lbl_8009055C
lbl_80090534:
/* 80090534 0008D114  7F C3 F3 78 */	mr r3, r30
/* 80090538 0008D118  48 03 18 01 */	bl func_800C1D38
/* 8009053C 0008D11C  2C 03 00 00 */	cmpwi r3, 0
/* 80090540 0008D120  40 82 00 1C */	bne lbl_8009055C
/* 80090544 0008D124  7F C3 F3 78 */	mr r3, r30
/* 80090548 0008D128  48 03 1E 59 */	bl func_800C23A0
/* 8009054C 0008D12C  2C 03 00 00 */	cmpwi r3, 0
/* 80090550 0008D130  40 82 00 0C */	bne lbl_8009055C
/* 80090554 0008D134  7F C3 F3 78 */	mr r3, r30
/* 80090558 0008D138  48 03 12 75 */	bl func_800C17CC
lbl_8009055C:
/* 8009055C 0008D13C  80 01 00 2C */	lwz r0, 0x2c(r1)
/* 80090560 0008D140  83 E1 00 24 */	lwz r31, 0x24(r1)
/* 80090564 0008D144  83 C1 00 20 */	lwz r30, 0x20(r1)
/* 80090568 0008D148  38 21 00 28 */	addi r1, r1, 0x28
/* 8009056C 0008D14C  7C 08 03 A6 */	mtlr r0
/* 80090570 0008D150  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

#pragma push
asm unk_t func_80090574()
{ // clang-format off
    nofralloc
/* 80090574 0008D154  7C 08 02 A6 */	mflr r0
/* 80090578 0008D158  90 01 00 04 */	stw r0, 4(r1)
/* 8009057C 0008D15C  94 21 FF F8 */	stwu r1, -8(r1)
/* 80090580 0008D160  4B FF 18 55 */	bl func_80081DD4
/* 80090584 0008D164  80 01 00 0C */	lwz r0, 0xc(r1)
/* 80090588 0008D168  38 21 00 08 */	addi r1, r1, 8
/* 8009058C 0008D16C  7C 08 03 A6 */	mtlr r0
/* 80090590 0008D170  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

#pragma push
asm func_80090594(Fighter* fp, s32 damage_dealt, BOOL bool, s32 action_state_index, GroundOrAir ground_or_air, f32 vibrate_mult)
{ // clang-format off
    nofralloc
/* 80090594 0008D174  7C 08 02 A6 */	mflr r0
/* 80090598 0008D178  90 01 00 04 */	stw r0, 4(r1)
/* 8009059C 0008D17C  94 21 FF C0 */	stwu r1, -0x40(r1)
/* 800905A0 0008D180  93 E1 00 3C */	stw r31, 0x3c(r1)
/* 800905A4 0008D184  3B E3 00 00 */	addi r31, r3, 0
/* 800905A8 0008D188  93 C1 00 38 */	stw r30, 0x38(r1)
/* 800905AC 0008D18C  93 A1 00 34 */	stw r29, 0x34(r1)
/* 800905B0 0008D190  3B A7 00 00 */	addi r29, r7, 0
/* 800905B4 0008D194  93 81 00 30 */	stw r28, 0x30(r1)
/* 800905B8 0008D198  3B 84 00 00 */	addi r28, r4, 0
/* 800905BC 0008D19C  2C 1C 00 0A */	cmpwi r28, 0xa
/* 800905C0 0008D1A0  41 82 00 B0 */	beq lbl_80090670
/* 800905C4 0008D1A4  2C 1C 00 0C */	cmpwi r28, 0xc
/* 800905C8 0008D1A8  41 82 00 A8 */	beq lbl_80090670
/* 800905CC 0008D1AC  38 1C FF FA */	addi r0, r28, -6
/* 800905D0 0008D1B0  28 00 00 01 */	cmplwi r0, 1
/* 800905D4 0008D1B4  41 81 00 08 */	bgt lbl_800905DC
/* 800905D8 0008D1B8  48 00 00 98 */	b lbl_80090670
lbl_800905DC:
/* 800905DC 0008D1BC  80 1F 00 10 */	lwz r0, 0x10(r31)
/* 800905E0 0008D1C0  2C 00 01 45 */	cmpwi r0, 0x145
/* 800905E4 0008D1C4  41 82 00 8C */	beq lbl_80090670
/* 800905E8 0008D1C8  83 CD AE B4 */	lwz r30, p_ftCommonData(r13)
/* 800905EC 0008D1CC  38 65 00 00 */	addi r3, r5, 0
/* 800905F0 0008D1D0  38 86 00 00 */	addi r4, r6, 0
/* 800905F4 0008D1D4  4B FE D4 81 */	bl func_8007DA74
/* 800905F8 0008D1D8  C0 5E 01 68 */	lfs f2, 0x168(r30)
/* 800905FC 0008D1DC  2C 1C 00 02 */	cmpwi r28, 2
/* 80090600 0008D1E0  C0 1E 01 6C */	lfs f0, 0x16c(r30)
/* 80090604 0008D1E4  38 00 00 00 */	li r0, 0
/* 80090608 0008D1E8  EC 02 00 7A */	fmadds f0, f2, f1, f0
/* 8009060C 0008D1EC  FC 00 00 1E */	fctiwz f0, f0
/* 80090610 0008D1F0  D8 01 00 28 */	stfd f0, 0x28(r1)
/* 80090614 0008D1F4  80 61 00 2C */	lwz r3, 0x2c(r1)
/* 80090618 0008D1F8  B0 7F 18 FA */	sth r3, 0x18fa(r31)
/* 8009061C 0008D1FC  98 1F 18 FC */	stb r0, 0x18fc(r31)
/* 80090620 0008D200  40 82 00 10 */	bne lbl_80090630
/* 80090624 0008D204  38 00 00 02 */	li r0, 2
/* 80090628 0008D208  98 1F 18 F8 */	stb r0, 0x18f8(r31)
/* 8009062C 0008D20C  48 00 00 2C */	b lbl_80090658
lbl_80090630:
/* 80090630 0008D210  2C 1D 00 01 */	cmpwi r29, 1
/* 80090634 0008D214  40 82 00 0C */	bne lbl_80090640
/* 80090638 0008D218  98 1F 18 F8 */	stb r0, 0x18f8(r31)
/* 8009063C 0008D21C  48 00 00 1C */	b lbl_80090658
lbl_80090640:
/* 80090640 0008D220  38 00 00 01 */	li r0, 1
/* 80090644 0008D224  98 1F 18 F8 */	stb r0, 0x18f8(r31)
/* 80090648 0008D228  C0 1F 08 44 */	lfs f0, 0x844(r31)
/* 8009064C 0008D22C  D0 1F 19 00 */	stfs f0, 0x1900(r31)
/* 80090650 0008D230  C0 1F 08 48 */	lfs f0, 0x848(r31)
/* 80090654 0008D234  D0 1F 19 04 */	stfs f0, 0x1904(r31)
lbl_80090658:
/* 80090658 0008D238  88 1F 18 F8 */	lbz r0, 0x18f8(r31)
/* 8009065C 0008D23C  80 6D AE 90 */	lwz r3, lbl_804D6530(r13)
/* 80090660 0008D240  54 00 18 38 */	slwi r0, r0, 3
/* 80090664 0008D244  7C 63 02 14 */	add r3, r3, r0
/* 80090668 0008D248  80 03 00 04 */	lwz r0, 4(r3)
/* 8009066C 0008D24C  98 1F 18 FD */	stb r0, 0x18fd(r31)
lbl_80090670:
/* 80090670 0008D250  80 01 00 44 */	lwz r0, 0x44(r1)
/* 80090674 0008D254  83 E1 00 3C */	lwz r31, 0x3c(r1)
/* 80090678 0008D258  83 C1 00 38 */	lwz r30, 0x38(r1)
/* 8009067C 0008D25C  83 A1 00 34 */	lwz r29, 0x34(r1)
/* 80090680 0008D260  83 81 00 30 */	lwz r28, 0x30(r1)
/* 80090684 0008D264  38 21 00 40 */	addi r1, r1, 0x40
/* 80090688 0008D268  7C 08 03 A6 */	mtlr r0
/* 8009068C 0008D26C  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

#pragma push
asm u32 func_80090690(Fighter* fp, Vec2* shift)
{ // clang-format off
    nofralloc
/* 80090690 0008D270  A0 03 18 FA */	lhz r0, 0x18fa(r3)
/* 80090694 0008D274  28 00 00 00 */	cmplwi r0, 0
/* 80090698 0008D278  41 82 00 78 */	beq lbl_80090710
/* 8009069C 0008D27C  88 E3 18 F8 */	lbz r7, 0x18f8(r3)
/* 800906A0 0008D280  80 CD AE 90 */	lwz r6, lbl_804D6530(r13)
/* 800906A4 0008D284  54 E5 18 38 */	slwi r5, r7, 3
/* 800906A8 0008D288  88 03 18 FC */	lbz r0, 0x18fc(r3)
/* 800906AC 0008D28C  28 07 00 01 */	cmplwi r7, 1
/* 800906B0 0008D290  7C A6 28 2E */	lwzx r5, r6, r5
/* 800906B4 0008D294  54 00 18 38 */	slwi r0, r0, 3
/* 800906B8 0008D298  7C A5 02 14 */	add r5, r5, r0
/* 800906BC 0008D29C  40 82 00 34 */	bne lbl_800906F0
/* 800906C0 0008D2A0  C0 45 00 00 */	lfs f2, 0(r5)
/* 800906C4 0008D2A4  C0 23 00 2C */	lfs f1, 0x2c(r3)
/* 800906C8 0008D2A8  C0 03 19 04 */	lfs f0, 0x1904(r3)
/* 800906CC 0008D2AC  EC 42 00 72 */	fmuls f2, f2, f1
/* 800906D0 0008D2B0  EC 00 00 B2 */	fmuls f0, f0, f2
/* 800906D4 0008D2B4  D0 04 00 00 */	stfs f0, 0(r4)
/* 800906D8 0008D2B8  C0 23 19 00 */	lfs f1, 0x1900(r3)
/* 800906DC 0008D2BC  C0 05 00 04 */	lfs f0, 4(r5)
/* 800906E0 0008D2C0  FC 20 08 50 */	fneg f1, f1
/* 800906E4 0008D2C4  EC 01 00 BA */	fmadds f0, f1, f2, f0
/* 800906E8 0008D2C8  D0 04 00 04 */	stfs f0, 4(r4)
/* 800906EC 0008D2CC  48 00 00 1C */	b lbl_80090708
lbl_800906F0:
/* 800906F0 0008D2D0  C0 25 00 00 */	lfs f1, 0(r5)
/* 800906F4 0008D2D4  C0 03 00 2C */	lfs f0, 0x2c(r3)
/* 800906F8 0008D2D8  EC 01 00 32 */	fmuls f0, f1, f0
/* 800906FC 0008D2DC  D0 04 00 00 */	stfs f0, 0(r4)
/* 80090700 0008D2E0  C0 05 00 04 */	lfs f0, 4(r5)
/* 80090704 0008D2E4  D0 04 00 04 */	stfs f0, 4(r4)
lbl_80090708:
/* 80090708 0008D2E8  7C 83 23 78 */	mr r3, r4
/* 8009070C 0008D2EC  4E 80 00 20 */	blr 
lbl_80090710:
/* 80090710 0008D2F0  38 60 00 00 */	li r3, 0
/* 80090714 0008D2F4  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

#pragma push
asm void func_80090718(Fighter* fp)
{ // clang-format off
    nofralloc
/* 80090718 0008D2F8  7C 08 02 A6 */	mflr r0
/* 8009071C 0008D2FC  90 01 00 04 */	stw r0, 4(r1)
/* 80090720 0008D300  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 80090724 0008D304  93 E1 00 14 */	stw r31, 0x14(r1)
/* 80090728 0008D308  7C 7F 1B 78 */	mr r31, r3
/* 8009072C 0008D30C  80 83 19 08 */	lwz r4, 0x1908(r3)
/* 80090730 0008D310  2C 04 FF FF */	cmpwi r4, -1
/* 80090734 0008D314  41 82 00 1C */	beq lbl_80090750
/* 80090738 0008D318  38 7F 00 00 */	addi r3, r31, 0
/* 8009073C 0008D31C  38 A0 00 7F */	li r5, 0x7f
/* 80090740 0008D320  38 C0 00 40 */	li r6, 0x40
/* 80090744 0008D324  4B FF 7A 05 */	bl func_80088148
/* 80090748 0008D328  38 00 FF FF */	li r0, -1
/* 8009074C 0008D32C  90 1F 19 08 */	stw r0, 0x1908(r31)
lbl_80090750:
/* 80090750 0008D330  80 9F 19 0C */	lwz r4, 0x190c(r31)
/* 80090754 0008D334  28 04 00 00 */	cmplwi r4, 0
/* 80090758 0008D338  41 82 00 14 */	beq lbl_8009076C
/* 8009075C 0008D33C  7F E3 FB 78 */	mr r3, r31
/* 80090760 0008D340  4B FF 82 95 */	bl func_800889F4
/* 80090764 0008D344  38 00 00 00 */	li r0, 0
/* 80090768 0008D348  90 1F 19 0C */	stw r0, 0x190c(r31)
lbl_8009076C:
/* 8009076C 0008D34C  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 80090770 0008D350  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 80090774 0008D354  38 21 00 18 */	addi r1, r1, 0x18
/* 80090778 0008D358  7C 08 03 A6 */	mtlr r0
/* 8009077C 0008D35C  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

extern f32 const lbl_804D8510;
extern f32 const lbl_804D8514;
extern unk_t func_800CF4DC();

#pragma push
asm void func_80090780(HSD_GObj* fighter_gobj)
{ // clang-format off
    nofralloc
/* 80090780 0008D360  7C 08 02 A6 */	mflr r0
/* 80090784 0008D364  90 01 00 04 */	stw r0, 4(r1)
/* 80090788 0008D368  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 8009078C 0008D36C  93 E1 00 14 */	stw r31, 0x14(r1)
/* 80090790 0008D370  93 C1 00 10 */	stw r30, 0x10(r1)
/* 80090794 0008D374  7C 7E 1B 78 */	mr r30, r3
/* 80090798 0008D378  80 63 00 2C */	lwz r3, 0x2c(r3)
/* 8009079C 0008D37C  80 03 00 E0 */	lwz r0, 0xe0(r3)
/* 800907A0 0008D380  3B E3 00 00 */	addi r31, r3, 0
/* 800907A4 0008D384  2C 00 00 00 */	cmpwi r0, 0
/* 800907A8 0008D388  40 82 00 0C */	bne lbl_800907B4
/* 800907AC 0008D38C  7F E3 FB 78 */	mr r3, r31
/* 800907B0 0008D390  4B FE CE 25 */	bl func_8007D5D4
lbl_800907B4:
/* 800907B4 0008D394  7F C3 F3 78 */	mr r3, r30
/* 800907B8 0008D398  4B FE E1 DD */	bl ftGetParasolStatus
/* 800907BC 0008D39C  2C 03 FF FF */	cmpwi r3, -1
/* 800907C0 0008D3A0  41 82 00 10 */	beq lbl_800907D0
/* 800907C4 0008D3A4  7F C3 F3 78 */	mr r3, r30
/* 800907C8 0008D3A8  48 03 ED 15 */	bl func_800CF4DC
/* 800907CC 0008D3AC  48 00 00 40 */	b lbl_8009080C
lbl_800907D0:
/* 800907D0 0008D3B0  C0 22 8B 30 */	lfs f1, lbl_804D8510(r2)
/* 800907D4 0008D3B4  3C 80 00 02 */	lis r4, 0x00018001@ha
/* 800907D8 0008D3B8  C0 42 8B 34 */	lfs f2, lbl_804D8514(r2)
/* 800907DC 0008D3BC  7F C3 F3 78 */	mr r3, r30
/* 800907E0 0008D3C0  FC 60 08 90 */	fmr f3, f1
/* 800907E4 0008D3C4  38 A4 80 01 */	addi r5, r4, 0x00018001@l
/* 800907E8 0008D3C8  38 80 00 26 */	li r4, 0x26
/* 800907EC 0008D3CC  38 C0 00 00 */	li r6, 0
/* 800907F0 0008D3D0  4B FD 8B BD */	bl Fighter_ActionStateChange_800693AC
/* 800907F4 0008D3D4  7F E3 FB 78 */	mr r3, r31
/* 800907F8 0008D3D8  4B FE CC 71 */	bl func_8007D468
/* 800907FC 0008D3DC  38 7F 00 00 */	addi r3, r31, 0
/* 80090800 0008D3E0  38 80 00 08 */	li r4, 8
/* 80090804 0008D3E4  38 A0 00 00 */	li r5, 0
/* 80090808 0008D3E8  4B FE E3 A5 */	bl func_8007EBAC
lbl_8009080C:
/* 8009080C 0008D3EC  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 80090810 0008D3F0  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 80090814 0008D3F4  83 C1 00 10 */	lwz r30, 0x10(r1)
/* 80090818 0008D3F8  38 21 00 18 */	addi r1, r1, 0x18
/* 8009081C 0008D3FC  7C 08 03 A6 */	mtlr r0
/* 80090820 0008D400  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

void func_80090824(HSD_GObj* fighter_gobj)
{
    return;
}

extern unk_t func_800C5CD4();
extern unk_t func_800C5DDC();
extern unk_t func_8009665C();

#pragma push
asm unk_t func_80090828()
{ // clang-format off
    nofralloc
/* 80090828 0008D408  7C 08 02 A6 */	mflr r0
/* 8009082C 0008D40C  90 01 00 04 */	stw r0, 4(r1)
/* 80090830 0008D410  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 80090834 0008D414  93 E1 00 14 */	stw r31, 0x14(r1)
/* 80090838 0008D418  93 C1 00 10 */	stw r30, 0x10(r1)
/* 8009083C 0008D41C  7C 7E 1B 78 */	mr r30, r3
/* 80090840 0008D420  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 80090844 0008D424  48 03 49 FD */	bl func_800C5240
/* 80090848 0008D428  2C 03 00 00 */	cmpwi r3, 0
/* 8009084C 0008D42C  40 82 00 BC */	bne lbl_80090908
/* 80090850 0008D430  7F C3 F3 78 */	mr r3, r30
/* 80090854 0008D434  48 00 5E 09 */	bl func_8009665C
/* 80090858 0008D438  2C 03 00 00 */	cmpwi r3, 0
/* 8009085C 0008D43C  40 82 00 C8 */	bne lbl_80090924
/* 80090860 0008D440  38 7E 00 00 */	addi r3, r30, 0
/* 80090864 0008D444  38 80 00 00 */	li r4, 0
/* 80090868 0008D448  48 00 4A C1 */	bl func_80095328
/* 8009086C 0008D44C  2C 03 00 00 */	cmpwi r3, 0
/* 80090870 0008D450  40 82 00 B4 */	bne lbl_80090924
/* 80090874 0008D454  7F C3 F3 78 */	mr r3, r30
/* 80090878 0008D458  48 04 68 89 */	bl func_800D7100
/* 8009087C 0008D45C  2C 03 00 00 */	cmpwi r3, 0
/* 80090880 0008D460  40 82 00 A4 */	bne lbl_80090924
/* 80090884 0008D464  7F C3 F3 78 */	mr r3, r30
/* 80090888 0008D468  48 03 32 89 */	bl func_800C3B10
/* 8009088C 0008D46C  2C 03 00 00 */	cmpwi r3, 0
/* 80090890 0008D470  40 82 00 94 */	bne lbl_80090924
/* 80090894 0008D474  7F C3 F3 78 */	mr r3, r30
/* 80090898 0008D478  4B FF C4 D1 */	bl func_8008CD68
/* 8009089C 0008D47C  2C 03 00 00 */	cmpwi r3, 0
/* 800908A0 0008D480  40 82 00 84 */	bne lbl_80090924
/* 800908A4 0008D484  7F C3 F3 78 */	mr r3, r30
/* 800908A8 0008D488  48 04 67 B5 */	bl func_800D705C
/* 800908AC 0008D48C  2C 03 00 00 */	cmpwi r3, 0
/* 800908B0 0008D490  40 82 00 74 */	bne lbl_80090924
/* 800908B4 0008D494  7F C3 F3 78 */	mr r3, r30
/* 800908B8 0008D498  48 03 AF B9 */	bl func_800CB870
/* 800908BC 0008D49C  2C 03 00 00 */	cmpwi r3, 0
/* 800908C0 0008D4A0  40 82 00 64 */	bne lbl_80090924
/* 800908C4 0008D4A4  C0 3F 06 20 */	lfs f1, 0x620(r31)
/* 800908C8 0008D4A8  C0 02 8B 30 */	lfs f0, lbl_804D8510(r2)
/* 800908CC 0008D4AC  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 800908D0 0008D4B0  40 80 00 08 */	bge lbl_800908D8
/* 800908D4 0008D4B4  FC 20 08 50 */	fneg f1, f1
lbl_800908D8:
/* 800908D8 0008D4B8  80 8D AE B4 */	lwz r4, p_ftCommonData(r13)
/* 800908DC 0008D4BC  C0 04 02 10 */	lfs f0, 0x210(r4)
/* 800908E0 0008D4C0  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 800908E4 0008D4C4  4C 41 13 82 */	cror 2, 1, 2
/* 800908E8 0008D4C8  40 82 00 20 */	bne lbl_80090908
/* 800908EC 0008D4CC  88 7F 06 70 */	lbz r3, 0x670(r31)
/* 800908F0 0008D4D0  80 04 02 14 */	lwz r0, 0x214(r4)
/* 800908F4 0008D4D4  7C 03 00 00 */	cmpw r3, r0
/* 800908F8 0008D4D8  40 80 00 10 */	bge lbl_80090908
/* 800908FC 0008D4DC  7F C3 F3 78 */	mr r3, r30
/* 80090900 0008D4E0  48 03 BE 31 */	bl func_800CC730
/* 80090904 0008D4E4  48 00 00 20 */	b lbl_80090924
lbl_80090908:
/* 80090908 0008D4E8  7F C3 F3 78 */	mr r3, r30
/* 8009090C 0008D4EC  48 03 54 D1 */	bl func_800C5DDC
/* 80090910 0008D4F0  2C 03 00 00 */	cmpwi r3, 0
/* 80090914 0008D4F4  40 82 00 10 */	bne lbl_80090924
/* 80090918 0008D4F8  7F C3 F3 78 */	mr r3, r30
/* 8009091C 0008D4FC  48 03 53 B9 */	bl func_800C5CD4
/* 80090920 0008D500  2C 03 00 00 */	cmpwi r3, 0
lbl_80090924:
/* 80090924 0008D504  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 80090928 0008D508  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 8009092C 0008D50C  83 C1 00 10 */	lwz r30, 0x10(r1)
/* 80090930 0008D510  38 21 00 18 */	addi r1, r1, 0x18
/* 80090934 0008D514  7C 08 03 A6 */	mtlr r0
/* 80090938 0008D518  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

#pragma push
asm unk_t func_8009093C()
{ // clang-format off
    nofralloc
/* 8009093C 0008D51C  7C 08 02 A6 */	mflr r0
/* 80090940 0008D520  90 01 00 04 */	stw r0, 4(r1)
/* 80090944 0008D524  94 21 FF F8 */	stwu r1, -8(r1)
/* 80090948 0008D528  4B FF 44 69 */	bl func_80084DB0
/* 8009094C 0008D52C  80 01 00 0C */	lwz r0, 0xc(r1)
/* 80090950 0008D530  38 21 00 08 */	addi r1, r1, 8
/* 80090954 0008D534  7C 08 03 A6 */	mtlr r0
/* 80090958 0008D538  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

extern unk_t lbl_80090984();

#pragma push
asm unk_t func_8009095C()
{ // clang-format off
    nofralloc
/* 8009095C 0008D53C  7C 08 02 A6 */	mflr r0
/* 80090960 0008D540  3C 80 80 09 */	lis r4, lbl_80090984@ha
/* 80090964 0008D544  90 01 00 04 */	stw r0, 4(r1)
/* 80090968 0008D548  38 84 09 84 */	addi r4, r4, lbl_80090984@l
/* 8009096C 0008D54C  94 21 FF F8 */	stwu r1, -8(r1)
/* 80090970 0008D550  4B FF 2D 9D */	bl func_8008370C
/* 80090974 0008D554  80 01 00 0C */	lwz r0, 0xc(r1)
/* 80090978 0008D558  38 21 00 08 */	addi r1, r1, 8
/* 8009097C 0008D55C  7C 08 03 A6 */	mtlr r0
/* 80090980 0008D560  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

#pragma push
asm unk_t lbl_80090984()
{ // clang-format off
    nofralloc
/* 80090984 0008D564  7C 08 02 A6 */	mflr r0
/* 80090988 0008D568  90 01 00 04 */	stw r0, 4(r1)
/* 8009098C 0008D56C  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 80090990 0008D570  93 E1 00 14 */	stw r31, 0x14(r1)
/* 80090994 0008D574  7C 7F 1B 78 */	mr r31, r3
/* 80090998 0008D578  48 00 7F 91 */	bl func_80098928
/* 8009099C 0008D57C  2C 03 00 00 */	cmpwi r3, 0
/* 800909A0 0008D580  40 82 00 1C */	bne lbl_800909BC
/* 800909A4 0008D584  7F E3 FB 78 */	mr r3, r31
/* 800909A8 0008D588  48 00 7D 85 */	bl func_8009872C
/* 800909AC 0008D58C  2C 03 00 00 */	cmpwi r3, 0
/* 800909B0 0008D590  40 82 00 0C */	bne lbl_800909BC
/* 800909B4 0008D594  7F E3 FB 78 */	mr r3, r31
/* 800909B8 0008D598  48 00 73 89 */	bl func_80097D40
lbl_800909BC:
/* 800909BC 0008D59C  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 800909C0 0008D5A0  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 800909C4 0008D5A4  38 21 00 18 */	addi r1, r1, 0x18
/* 800909C8 0008D5A8  7C 08 03 A6 */	mtlr r0
/* 800909CC 0008D5AC  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

extern f32 const lbl_804D8518;

#pragma push
asm unk_t func_800909D0()
{ // clang-format off
    nofralloc
/* 800909D0 0008D5B0  7C 08 02 A6 */	mflr r0
/* 800909D4 0008D5B4  38 80 00 00 */	li r4, 0
/* 800909D8 0008D5B8  90 01 00 04 */	stw r0, 4(r1)
/* 800909DC 0008D5BC  94 21 FF C0 */	stwu r1, -0x40(r1)
/* 800909E0 0008D5C0  DB E1 00 38 */	stfd f31, 0x38(r1)
/* 800909E4 0008D5C4  38 A1 00 10 */	addi r5, r1, 0x10
/* 800909E8 0008D5C8  93 E1 00 34 */	stw r31, 0x34(r1)
/* 800909EC 0008D5CC  7C 7F 1B 78 */	mr r31, r3
/* 800909F0 0008D5D0  C0 23 00 38 */	lfs f1, 0x38(r3)
/* 800909F4 0008D5D4  C0 03 02 5C */	lfs f0, 0x25c(r3)
/* 800909F8 0008D5D8  80 63 05 E8 */	lwz r3, 0x5e8(r3)
/* 800909FC 0008D5DC  EF E1 00 32 */	fmuls f31, f1, f0
/* 80090A00 0008D5E0  80 63 00 00 */	lwz r3, 0(r3)
/* 80090A04 0008D5E4  4B F7 A7 C9 */	bl func_8000B1CC
/* 80090A08 0008D5E8  38 7F 00 00 */	addi r3, r31, 0
/* 80090A0C 0008D5EC  38 80 00 02 */	li r4, 2
/* 80090A10 0008D5F0  4B FE 45 FD */	bl func_8007500C
/* 80090A14 0008D5F4  80 9F 05 E8 */	lwz r4, 0x5e8(r31)
/* 80090A18 0008D5F8  54 60 20 36 */	slwi r0, r3, 4
/* 80090A1C 0008D5FC  38 A1 00 1C */	addi r5, r1, 0x1c
/* 80090A20 0008D600  7C 64 00 2E */	lwzx r3, r4, r0
/* 80090A24 0008D604  38 80 00 00 */	li r4, 0
/* 80090A28 0008D608  4B F7 A7 A5 */	bl func_8000B1CC
/* 80090A2C 0008D60C  38 61 00 1C */	addi r3, r1, 0x1c
/* 80090A30 0008D610  38 81 00 10 */	addi r4, r1, 0x10
/* 80090A34 0008D614  4B F7 CA 91 */	bl lbvector_Sub
/* 80090A38 0008D618  C0 01 00 20 */	lfs f0, 0x20(r1)
/* 80090A3C 0008D61C  FC 40 F8 50 */	fneg f2, f31
/* 80090A40 0008D620  7F E3 FB 78 */	mr r3, r31
/* 80090A44 0008D624  EC 1F 00 2A */	fadds f0, f31, f0
/* 80090A48 0008D628  D0 1F 23 48 */	stfs f0, 0x2348(r31)
/* 80090A4C 0008D62C  C0 01 00 20 */	lfs f0, 0x20(r1)
/* 80090A50 0008D630  EC 02 00 2A */	fadds f0, f2, f0
/* 80090A54 0008D634  D0 1F 23 4C */	stfs f0, 0x234c(r31)
/* 80090A58 0008D638  C0 01 00 1C */	lfs f0, 0x1c(r1)
/* 80090A5C 0008D63C  EC 1F 00 2A */	fadds f0, f31, f0
/* 80090A60 0008D640  D0 1F 23 58 */	stfs f0, 0x2358(r31)
/* 80090A64 0008D644  C0 22 8B 38 */	lfs f1, lbl_804D8518(r2)
/* 80090A68 0008D648  D0 3F 23 5C */	stfs f1, 0x235c(r31)
/* 80090A6C 0008D64C  C0 01 00 1C */	lfs f0, 0x1c(r1)
/* 80090A70 0008D650  EC 02 00 2A */	fadds f0, f2, f0
/* 80090A74 0008D654  D0 1F 23 50 */	stfs f0, 0x2350(r31)
/* 80090A78 0008D658  D0 3F 23 54 */	stfs f1, 0x2354(r31)
/* 80090A7C 0008D65C  4B FE CB 41 */	bl func_8007D5BC
/* 80090A80 0008D660  80 1F 00 E0 */	lwz r0, 0xe0(r31)
/* 80090A84 0008D664  2C 00 00 01 */	cmpwi r0, 1
/* 80090A88 0008D668  40 82 00 14 */	bne lbl_80090A9C
/* 80090A8C 0008D66C  80 7F 00 00 */	lwz r3, 0(r31)
/* 80090A90 0008D670  38 9F 23 48 */	addi r4, r31, 0x2348
/* 80090A94 0008D674  4B FF 1B A5 */	bl func_80082638
/* 80090A98 0008D678  48 00 00 10 */	b lbl_80090AA8
lbl_80090A9C:
/* 80090A9C 0008D67C  80 7F 00 00 */	lwz r3, 0(r31)
/* 80090AA0 0008D680  38 9F 23 48 */	addi r4, r31, 0x2348
/* 80090AA4 0008D684  4B FF 1D E5 */	bl func_80082888
lbl_80090AA8:
/* 80090AA8 0008D688  80 01 00 44 */	lwz r0, 0x44(r1)
/* 80090AAC 0008D68C  CB E1 00 38 */	lfd f31, 0x38(r1)
/* 80090AB0 0008D690  83 E1 00 34 */	lwz r31, 0x34(r1)
/* 80090AB4 0008D694  38 21 00 40 */	addi r1, r1, 0x40
/* 80090AB8 0008D698  7C 08 03 A6 */	mtlr r0
/* 80090ABC 0008D69C  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

#pragma push
asm unk_t func_80090AC0()
{ // clang-format off
    nofralloc
/* 80090AC0 0008D6A0  7C 08 02 A6 */	mflr r0
/* 80090AC4 0008D6A4  38 80 00 02 */	li r4, 2
/* 80090AC8 0008D6A8  90 01 00 04 */	stw r0, 4(r1)
/* 80090ACC 0008D6AC  94 21 FF D8 */	stwu r1, -0x28(r1)
/* 80090AD0 0008D6B0  93 E1 00 24 */	stw r31, 0x24(r1)
/* 80090AD4 0008D6B4  3B E3 00 00 */	addi r31, r3, 0
/* 80090AD8 0008D6B8  4B FE 45 35 */	bl func_8007500C
/* 80090ADC 0008D6BC  C0 3F 00 38 */	lfs f1, 0x38(r31)
/* 80090AE0 0008D6C0  54 60 20 36 */	slwi r0, r3, 4
/* 80090AE4 0008D6C4  C0 1F 02 5C */	lfs f0, 0x25c(r31)
/* 80090AE8 0008D6C8  39 01 00 18 */	addi r8, r1, 0x18
/* 80090AEC 0008D6CC  80 6D AE B4 */	lwz r3, p_ftCommonData(r13)
/* 80090AF0 0008D6D0  EC 21 00 32 */	fmuls f1, f1, f0
/* 80090AF4 0008D6D4  80 9F 05 E8 */	lwz r4, 0x5e8(r31)
/* 80090AF8 0008D6D8  C0 03 07 A0 */	lfs f0, 0x7a0(r3)
/* 80090AFC 0008D6DC  4C C6 31 82 */	crclr 6
/* 80090B00 0008D6E0  7C E4 00 2E */	lwzx r7, r4, r0
/* 80090B04 0008D6E4  EC 01 00 24 */	fdivs f0, f1, f0
/* 80090B08 0008D6E8  38 A0 00 03 */	li r5, 3
/* 80090B0C 0008D6EC  38 C0 04 15 */	li r6, 0x415
/* 80090B10 0008D6F0  D0 01 00 18 */	stfs f0, 0x18(r1)
/* 80090B14 0008D6F4  80 7F 00 00 */	lwz r3, 0(r31)
/* 80090B18 0008D6F8  80 83 00 2C */	lwz r4, 0x2c(r3)
/* 80090B1C 0008D6FC  38 84 06 0C */	addi r4, r4, 0x60c
/* 80090B20 0008D700  4B FD 6B D1 */	bl efAsync_Spawn
/* 80090B24 0008D704  88 1F 22 19 */	lbz r0, 0x2219(r31)
/* 80090B28 0008D708  38 60 00 01 */	li r3, 1
/* 80090B2C 0008D70C  50 60 3E 30 */	rlwimi r0, r3, 7, 0x18, 0x18
/* 80090B30 0008D710  98 1F 22 19 */	stb r0, 0x2219(r31)
/* 80090B34 0008D714  80 01 00 2C */	lwz r0, 0x2c(r1)
/* 80090B38 0008D718  83 E1 00 24 */	lwz r31, 0x24(r1)
/* 80090B3C 0008D71C  38 21 00 28 */	addi r1, r1, 0x28
/* 80090B40 0008D720  7C 08 03 A6 */	mtlr r0
/* 80090B44 0008D724  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

#pragma push
asm unk_t lbl_80090B48()
{ // clang-format off
    nofralloc
/* 80090B48 0008D728  80 63 00 2C */	lwz r3, 0x2c(r3)
/* 80090B4C 0008D72C  38 80 00 00 */	li r4, 0
/* 80090B50 0008D730  88 03 22 27 */	lbz r0, 0x2227(r3)
/* 80090B54 0008D734  50 80 0F BC */	rlwimi r0, r4, 1, 0x1e, 0x1e
/* 80090B58 0008D738  98 03 22 27 */	stb r0, 0x2227(r3)
/* 80090B5C 0008D73C  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

extern char* lbl_804D3AE8;
extern char* lbl_804D3AF0;
extern f32 const lbl_804D851C;
extern Vec const lbl_803B74B0;
extern unk_t lbl_80091274();
extern unk_t func_8009E140();

// todo: headers are too messy to use dolphin/mtx.h
extern void PSMTXConcat(const Mtx a, const Mtx b, Mtx ab);
extern void PSMTXTranspose(const Mtx src, Mtx xPose);

#pragma push
asm unk_t func_80090B60()
{ // clang-format off
    nofralloc
/* 80090B60 0008D740  7C 08 02 A6 */	mflr r0
/* 80090B64 0008D744  90 01 00 04 */	stw r0, 4(r1)
/* 80090B68 0008D748  94 21 FE 30 */	stwu r1, -0x1d0(r1)
/* 80090B6C 0008D74C  DB E1 01 C8 */	stfd f31, 0x1c8(r1)
/* 80090B70 0008D750  93 E1 01 C4 */	stw r31, 0x1c4(r1)
/* 80090B74 0008D754  93 C1 01 C0 */	stw r30, 0x1c0(r1)
/* 80090B78 0008D758  93 A1 01 BC */	stw r29, 0x1bc(r1)
/* 80090B7C 0008D75C  93 81 01 B8 */	stw r28, 0x1b8(r1)
/* 80090B80 0008D760  7C 7C 1B 78 */	mr r28, r3
/* 80090B84 0008D764  83 A3 00 2C */	lwz r29, 0x2c(r3)
/* 80090B88 0008D768  48 00 69 85 */	bl func_8009750C
/* 80090B8C 0008D76C  7F 83 E3 78 */	mr r3, r28
/* 80090B90 0008D770  48 04 C5 D9 */	bl func_800DD168
/* 80090B94 0008D774  88 1D 22 27 */	lbz r0, 0x2227(r29)
/* 80090B98 0008D778  38 60 00 01 */	li r3, 1
/* 80090B9C 0008D77C  50 60 0F BC */	rlwimi r0, r3, 1, 0x1e, 0x1e
/* 80090BA0 0008D780  98 1D 22 27 */	stb r0, 0x2227(r29)
/* 80090BA4 0008D784  38 7C 00 00 */	addi r3, r28, 0
/* 80090BA8 0008D788  38 80 01 45 */	li r4, 0x145
/* 80090BAC 0008D78C  C0 22 8B 38 */	lfs f1, lbl_804D8518(r2)
/* 80090BB0 0008D790  38 A0 00 40 */	li r5, 0x40
/* 80090BB4 0008D794  C0 42 8B 3C */	lfs f2, lbl_804D851C(r2)
/* 80090BB8 0008D798  38 C0 00 00 */	li r6, 0
/* 80090BBC 0008D79C  FC 60 08 90 */	fmr f3, f1
/* 80090BC0 0008D7A0  4B FD 87 ED */	bl Fighter_ActionStateChange_800693AC
/* 80090BC4 0008D7A4  80 AD AE B4 */	lwz r5, p_ftCommonData(r13)
/* 80090BC8 0008D7A8  7F A3 EB 78 */	mr r3, r29
/* 80090BCC 0008D7AC  C0 3D 18 38 */	lfs f1, 0x1838(r29)
/* 80090BD0 0008D7B0  38 80 00 00 */	li r4, 0
/* 80090BD4 0008D7B4  C0 05 07 90 */	lfs f0, 0x790(r5)
/* 80090BD8 0008D7B8  EC 21 00 32 */	fmuls f1, f1, f0
/* 80090BDC 0008D7BC  4B FE CF F1 */	bl func_8007DBCC
/* 80090BE0 0008D7C0  38 7D 00 00 */	addi r3, r29, 0
/* 80090BE4 0008D7C4  38 80 00 02 */	li r4, 2
/* 80090BE8 0008D7C8  4B FE 44 25 */	bl func_8007500C
/* 80090BEC 0008D7CC  80 9D 05 E8 */	lwz r4, 0x5e8(r29)
/* 80090BF0 0008D7D0  54 60 20 36 */	slwi r0, r3, 4
/* 80090BF4 0008D7D4  38 7D 00 00 */	addi r3, r29, 0
/* 80090BF8 0008D7D8  7F 84 00 2E */	lwzx r28, r4, r0
/* 80090BFC 0008D7DC  38 80 00 03 */	li r4, 3
/* 80090C00 0008D7E0  4B FE 44 0D */	bl func_8007500C
/* 80090C04 0008D7E4  80 9D 05 E8 */	lwz r4, 0x5e8(r29)
/* 80090C08 0008D7E8  54 60 20 36 */	slwi r0, r3, 4
/* 80090C0C 0008D7EC  C0 02 8B 38 */	lfs f0, lbl_804D8518(r2)
/* 80090C10 0008D7F0  38 61 00 EC */	addi r3, r1, 0xec
/* 80090C14 0008D7F4  7F E4 00 2E */	lwzx r31, r4, r0
/* 80090C18 0008D7F8  D0 01 01 AC */	stfs f0, 0x1ac(r1)
/* 80090C1C 0008D7FC  C0 1D 02 64 */	lfs f0, 0x264(r29)
/* 80090C20 0008D800  D0 01 01 B0 */	stfs f0, 0x1b0(r1)
/* 80090C24 0008D804  C0 1D 02 60 */	lfs f0, 0x260(r29)
/* 80090C28 0008D808  D0 01 01 B4 */	stfs f0, 0x1b4(r1)
/* 80090C2C 0008D80C  C0 21 01 AC */	lfs f1, 0x1ac(r1)
/* 80090C30 0008D810  C0 41 01 B0 */	lfs f2, 0x1b0(r1)
/* 80090C34 0008D814  C0 61 01 B4 */	lfs f3, 0x1b4(r1)
/* 80090C38 0008D818  48 2B 19 FD */	bl PSMTXTrans
/* 80090C3C 0008D81C  28 1F 00 00 */	cmplwi r31, 0
/* 80090C40 0008D820  40 82 00 14 */	bne lbl_80090C54
/* 80090C44 0008D824  38 6D 84 48 */	addi r3, r13, lbl_804D3AE8
/* 80090C48 0008D828  38 80 02 BB */	li r4, 0x2bb
/* 80090C4C 0008D82C  38 AD 84 50 */	addi r5, r13, lbl_804D3AF0
/* 80090C50 0008D830  48 2F 75 D1 */	bl __assert
lbl_80090C54:
/* 80090C54 0008D834  80 7F 00 1C */	lwz r3, 0x1c(r31)
/* 80090C58 0008D838  80 1F 00 20 */	lwz r0, 0x20(r31)
/* 80090C5C 0008D83C  90 61 00 DC */	stw r3, 0xdc(r1)
/* 80090C60 0008D840  90 01 00 E0 */	stw r0, 0xe0(r1)
/* 80090C64 0008D844  80 7F 00 24 */	lwz r3, 0x24(r31)
/* 80090C68 0008D848  80 1F 00 28 */	lwz r0, 0x28(r31)
/* 80090C6C 0008D84C  90 61 00 E4 */	stw r3, 0xe4(r1)
/* 80090C70 0008D850  90 01 00 E8 */	stw r0, 0xe8(r1)
/* 80090C74 0008D854  80 1F 00 14 */	lwz r0, 0x14(r31)
/* 80090C78 0008D858  54 00 03 9D */	rlwinm. r0, r0, 0, 0xe, 0xe
/* 80090C7C 0008D85C  40 82 00 14 */	bne lbl_80090C90
/* 80090C80 0008D860  38 61 00 AC */	addi r3, r1, 0xac
/* 80090C84 0008D864  38 81 00 DC */	addi r4, r1, 0xdc
/* 80090C88 0008D868  48 2E 94 99 */	bl HSD_MkRotationMtx
/* 80090C8C 0008D86C  48 00 00 10 */	b lbl_80090C9C
lbl_80090C90:
/* 80090C90 0008D870  38 61 00 AC */	addi r3, r1, 0xac
/* 80090C94 0008D874  38 81 00 DC */	addi r4, r1, 0xdc
/* 80090C98 0008D878  48 2E 95 99 */	bl func_8037A230
lbl_80090C9C:
/* 80090C9C 0008D87C  38 61 00 AC */	addi r3, r1, 0xac
/* 80090CA0 0008D880  38 81 01 1C */	addi r4, r1, 0x11c
/* 80090CA4 0008D884  48 2B 16 2D */	bl PSMTXTranspose
/* 80090CA8 0008D888  28 1C 00 00 */	cmplwi r28, 0
/* 80090CAC 0008D88C  40 82 00 14 */	bne lbl_80090CC0
/* 80090CB0 0008D890  38 6D 84 48 */	addi r3, r13, lbl_804D3AE8
/* 80090CB4 0008D894  38 80 02 BB */	li r4, 0x2bb
/* 80090CB8 0008D898  38 AD 84 50 */	addi r5, r13, lbl_804D3AF0
/* 80090CBC 0008D89C  48 2F 75 65 */	bl __assert
lbl_80090CC0:
/* 80090CC0 0008D8A0  80 7C 00 1C */	lwz r3, 0x1c(r28)
/* 80090CC4 0008D8A4  80 1C 00 20 */	lwz r0, 0x20(r28)
/* 80090CC8 0008D8A8  90 61 00 98 */	stw r3, 0x98(r1)
/* 80090CCC 0008D8AC  90 01 00 9C */	stw r0, 0x9c(r1)
/* 80090CD0 0008D8B0  80 7C 00 24 */	lwz r3, 0x24(r28)
/* 80090CD4 0008D8B4  80 1C 00 28 */	lwz r0, 0x28(r28)
/* 80090CD8 0008D8B8  90 61 00 A0 */	stw r3, 0xa0(r1)
/* 80090CDC 0008D8BC  90 01 00 A4 */	stw r0, 0xa4(r1)
/* 80090CE0 0008D8C0  80 1C 00 14 */	lwz r0, 0x14(r28)
/* 80090CE4 0008D8C4  54 00 03 9D */	rlwinm. r0, r0, 0, 0xe, 0xe
/* 80090CE8 0008D8C8  40 82 00 14 */	bne lbl_80090CFC
/* 80090CEC 0008D8CC  38 61 00 68 */	addi r3, r1, 0x68
/* 80090CF0 0008D8D0  38 81 00 98 */	addi r4, r1, 0x98
/* 80090CF4 0008D8D4  48 2E 94 2D */	bl HSD_MkRotationMtx
/* 80090CF8 0008D8D8  48 00 00 10 */	b lbl_80090D08
lbl_80090CFC:
/* 80090CFC 0008D8DC  38 61 00 68 */	addi r3, r1, 0x68
/* 80090D00 0008D8E0  38 81 00 98 */	addi r4, r1, 0x98
/* 80090D04 0008D8E4  48 2E 95 2D */	bl func_8037A230
lbl_80090D08:
/* 80090D08 0008D8E8  38 61 00 68 */	addi r3, r1, 0x68
/* 80090D0C 0008D8EC  38 81 01 4C */	addi r4, r1, 0x14c
/* 80090D10 0008D8F0  48 2B 15 C1 */	bl PSMTXTranspose
/* 80090D14 0008D8F4  38 61 00 EC */	addi r3, r1, 0xec
/* 80090D18 0008D8F8  38 81 01 1C */	addi r4, r1, 0x11c
/* 80090D1C 0008D8FC  38 A1 01 7C */	addi r5, r1, 0x17c
/* 80090D20 0008D900  48 2B 14 E5 */	bl PSMTXConcat
/* 80090D24 0008D904  38 61 01 7C */	addi r3, r1, 0x17c
/* 80090D28 0008D908  38 A3 00 00 */	addi r5, r3, 0
/* 80090D2C 0008D90C  38 81 01 4C */	addi r4, r1, 0x14c
/* 80090D30 0008D910  48 2B 14 D5 */	bl PSMTXConcat
/* 80090D34 0008D914  38 61 01 7C */	addi r3, r1, 0x17c
/* 80090D38 0008D918  38 81 01 AC */	addi r4, r1, 0x1ac
/* 80090D3C 0008D91C  48 2E 92 31 */	bl HSD_MtxGetTranslate
/* 80090D40 0008D920  28 1F 00 00 */	cmplwi r31, 0
/* 80090D44 0008D924  C3 E1 01 B0 */	lfs f31, 0x1b0(r1)
/* 80090D48 0008D928  40 82 00 14 */	bne lbl_80090D5C
/* 80090D4C 0008D92C  38 6D 84 48 */	addi r3, r13, lbl_804D3AE8
/* 80090D50 0008D930  38 80 04 5A */	li r4, 0x45a
/* 80090D54 0008D934  38 AD 84 50 */	addi r5, r13, lbl_804D3AF0
/* 80090D58 0008D938  48 2F 74 C9 */	bl __assert
lbl_80090D5C:
/* 80090D5C 0008D93C  C0 1F 00 3C */	lfs f0, 0x3c(r31)
/* 80090D60 0008D940  EC 00 F8 2A */	fadds f0, f0, f31
/* 80090D64 0008D944  D0 1F 00 3C */	stfs f0, 0x3c(r31)
/* 80090D68 0008D948  80 1F 00 14 */	lwz r0, 0x14(r31)
/* 80090D6C 0008D94C  54 00 01 8D */	rlwinm. r0, r0, 0, 6, 6
/* 80090D70 0008D950  40 82 00 4C */	bne lbl_80090DBC
/* 80090D74 0008D954  28 1F 00 00 */	cmplwi r31, 0
/* 80090D78 0008D958  41 82 00 44 */	beq lbl_80090DBC
/* 80090D7C 0008D95C  40 82 00 14 */	bne lbl_80090D90
/* 80090D80 0008D960  38 6D 84 48 */	addi r3, r13, lbl_804D3AE8
/* 80090D84 0008D964  38 80 02 34 */	li r4, 0x234
/* 80090D88 0008D968  38 AD 84 50 */	addi r5, r13, lbl_804D3AF0
/* 80090D8C 0008D96C  48 2F 74 95 */	bl __assert
lbl_80090D90:
/* 80090D90 0008D970  80 9F 00 14 */	lwz r4, 0x14(r31)
/* 80090D94 0008D974  38 60 00 00 */	li r3, 0
/* 80090D98 0008D978  54 80 02 11 */	rlwinm. r0, r4, 0, 8, 8
/* 80090D9C 0008D97C  40 82 00 10 */	bne lbl_80090DAC
/* 80090DA0 0008D980  54 80 06 73 */	rlwinm. r0, r4, 0, 0x19, 0x19
/* 80090DA4 0008D984  41 82 00 08 */	beq lbl_80090DAC
/* 80090DA8 0008D988  38 60 00 01 */	li r3, 1
lbl_80090DAC:
/* 80090DAC 0008D98C  2C 03 00 00 */	cmpwi r3, 0
/* 80090DB0 0008D990  40 82 00 0C */	bne lbl_80090DBC
/* 80090DB4 0008D994  7F E3 FB 78 */	mr r3, r31
/* 80090DB8 0008D998  48 2E 25 31 */	bl HSD_JObjSetMtxDirtySub
lbl_80090DBC:
/* 80090DBC 0008D99C  28 1F 00 00 */	cmplwi r31, 0
/* 80090DC0 0008D9A0  C3 E1 01 B4 */	lfs f31, 0x1b4(r1)
/* 80090DC4 0008D9A4  40 82 00 14 */	bne lbl_80090DD8
/* 80090DC8 0008D9A8  38 6D 84 48 */	addi r3, r13, lbl_804D3AE8
/* 80090DCC 0008D9AC  38 80 04 66 */	li r4, 0x466
/* 80090DD0 0008D9B0  38 AD 84 50 */	addi r5, r13, lbl_804D3AF0
/* 80090DD4 0008D9B4  48 2F 74 4D */	bl __assert
lbl_80090DD8:
/* 80090DD8 0008D9B8  C0 1F 00 40 */	lfs f0, 0x40(r31)
/* 80090DDC 0008D9BC  EC 00 F8 2A */	fadds f0, f0, f31
/* 80090DE0 0008D9C0  D0 1F 00 40 */	stfs f0, 0x40(r31)
/* 80090DE4 0008D9C4  80 1F 00 14 */	lwz r0, 0x14(r31)
/* 80090DE8 0008D9C8  54 00 01 8D */	rlwinm. r0, r0, 0, 6, 6
/* 80090DEC 0008D9CC  40 82 00 4C */	bne lbl_80090E38
/* 80090DF0 0008D9D0  28 1F 00 00 */	cmplwi r31, 0
/* 80090DF4 0008D9D4  41 82 00 44 */	beq lbl_80090E38
/* 80090DF8 0008D9D8  40 82 00 14 */	bne lbl_80090E0C
/* 80090DFC 0008D9DC  38 6D 84 48 */	addi r3, r13, lbl_804D3AE8
/* 80090E00 0008D9E0  38 80 02 34 */	li r4, 0x234
/* 80090E04 0008D9E4  38 AD 84 50 */	addi r5, r13, lbl_804D3AF0
/* 80090E08 0008D9E8  48 2F 74 19 */	bl __assert
lbl_80090E0C:
/* 80090E0C 0008D9EC  80 9F 00 14 */	lwz r4, 0x14(r31)
/* 80090E10 0008D9F0  38 60 00 00 */	li r3, 0
/* 80090E14 0008D9F4  54 80 02 11 */	rlwinm. r0, r4, 0, 8, 8
/* 80090E18 0008D9F8  40 82 00 10 */	bne lbl_80090E28
/* 80090E1C 0008D9FC  54 80 06 73 */	rlwinm. r0, r4, 0, 0x19, 0x19
/* 80090E20 0008DA00  41 82 00 08 */	beq lbl_80090E28
/* 80090E24 0008DA04  38 60 00 01 */	li r3, 1
lbl_80090E28:
/* 80090E28 0008DA08  2C 03 00 00 */	cmpwi r3, 0
/* 80090E2C 0008DA0C  40 82 00 0C */	bne lbl_80090E38
/* 80090E30 0008DA10  7F E3 FB 78 */	mr r3, r31
/* 80090E34 0008DA14  48 2E 24 B5 */	bl HSD_JObjSetMtxDirtySub
lbl_80090E38:
/* 80090E38 0008DA18  38 7D 00 00 */	addi r3, r29, 0
/* 80090E3C 0008DA1C  38 80 00 00 */	li r4, 0
/* 80090E40 0008DA20  48 00 D3 01 */	bl func_8009E140
/* 80090E44 0008DA24  80 7D 00 00 */	lwz r3, 0(r29)
/* 80090E48 0008DA28  4B FE E9 DD */	bl func_8007F824
/* 80090E4C 0008DA2C  88 1D 22 22 */	lbz r0, 0x2222(r29)
/* 80090E50 0008DA30  38 60 00 01 */	li r3, 1
/* 80090E54 0008DA34  50 60 26 F6 */	rlwimi r0, r3, 4, 0x1b, 0x1b
/* 80090E58 0008DA38  98 1D 22 22 */	stb r0, 0x2222(r29)
/* 80090E5C 0008DA3C  80 1D 00 E0 */	lwz r0, 0xe0(r29)
/* 80090E60 0008DA40  2C 00 00 01 */	cmpwi r0, 1
/* 80090E64 0008DA44  40 82 00 30 */	bne lbl_80090E94
/* 80090E68 0008DA48  80 7D 00 8C */	lwz r3, 0x8c(r29)
/* 80090E6C 0008DA4C  80 1D 00 90 */	lwz r0, 0x90(r29)
/* 80090E70 0008DA50  90 7D 00 80 */	stw r3, 0x80(r29)
/* 80090E74 0008DA54  90 1D 00 84 */	stw r0, 0x84(r29)
/* 80090E78 0008DA58  80 1D 00 94 */	lwz r0, 0x94(r29)
/* 80090E7C 0008DA5C  90 1D 00 88 */	stw r0, 0x88(r29)
/* 80090E80 0008DA60  C0 02 8B 38 */	lfs f0, lbl_804D8518(r2)
/* 80090E84 0008DA64  D0 1D 00 94 */	stfs f0, 0x94(r29)
/* 80090E88 0008DA68  D0 1D 00 90 */	stfs f0, 0x90(r29)
/* 80090E8C 0008DA6C  D0 1D 00 8C */	stfs f0, 0x8c(r29)
/* 80090E90 0008DA70  48 00 00 14 */	b lbl_80090EA4
lbl_80090E94:
/* 80090E94 0008DA74  C0 1D 00 F0 */	lfs f0, 0xf0(r29)
/* 80090E98 0008DA78  D0 1D 00 EC */	stfs f0, 0xec(r29)
/* 80090E9C 0008DA7C  C0 02 8B 38 */	lfs f0, lbl_804D8518(r2)
/* 80090EA0 0008DA80  D0 1D 00 F0 */	stfs f0, 0xf0(r29)
lbl_80090EA4:
/* 80090EA4 0008DA84  38 7D 00 00 */	addi r3, r29, 0
/* 80090EA8 0008DA88  38 80 01 FF */	li r4, 0x1ff
/* 80090EAC 0008DA8C  4B FE D4 49 */	bl func_8007E2F4
/* 80090EB0 0008DA90  3B E0 00 00 */	li r31, 0
/* 80090EB4 0008DA94  9B FD 23 40 */	stb r31, 0x2340(r29)
/* 80090EB8 0008DA98  48 2E F6 71 */	bl HSD_Randf
/* 80090EBC 0008DA9C  80 8D AE B4 */	lwz r4, p_ftCommonData(r13)
/* 80090EC0 0008DAA0  7F A3 EB 78 */	mr r3, r29
/* 80090EC4 0008DAA4  C0 44 07 88 */	lfs f2, 0x788(r4)
/* 80090EC8 0008DAA8  C0 04 07 8C */	lfs f0, 0x78c(r4)
/* 80090ECC 0008DAAC  EC 00 10 28 */	fsubs f0, f0, f2
/* 80090ED0 0008DAB0  EC 00 10 7A */	fmadds f0, f0, f1, f2
/* 80090ED4 0008DAB4  D0 1D 23 44 */	stfs f0, 0x2344(r29)
/* 80090ED8 0008DAB8  4B FF FA F9 */	bl func_800909D0
/* 80090EDC 0008DABC  38 7D 00 00 */	addi r3, r29, 0
/* 80090EE0 0008DAC0  38 80 00 02 */	li r4, 2
/* 80090EE4 0008DAC4  4B FE 41 29 */	bl func_8007500C
/* 80090EE8 0008DAC8  C0 3D 00 38 */	lfs f1, 0x38(r29)
/* 80090EEC 0008DACC  54 60 20 36 */	slwi r0, r3, 4
/* 80090EF0 0008DAD0  C0 1D 02 5C */	lfs f0, 0x25c(r29)
/* 80090EF4 0008DAD4  3B DD 02 5C */	addi r30, r29, 0x25c
/* 80090EF8 0008DAD8  80 8D AE B4 */	lwz r4, p_ftCommonData(r13)
/* 80090EFC 0008DADC  EC 21 00 32 */	fmuls f1, f1, f0
/* 80090F00 0008DAE0  80 7D 05 E8 */	lwz r3, 0x5e8(r29)
/* 80090F04 0008DAE4  C0 04 07 A0 */	lfs f0, 0x7a0(r4)
/* 80090F08 0008DAE8  39 01 00 5C */	addi r8, r1, 0x5c
/* 80090F0C 0008DAEC  7C E3 00 2E */	lwzx r7, r3, r0
/* 80090F10 0008DAF0  EC 01 00 24 */	fdivs f0, f1, f0
/* 80090F14 0008DAF4  4C C6 31 82 */	crclr 6
/* 80090F18 0008DAF8  38 A0 00 03 */	li r5, 3
/* 80090F1C 0008DAFC  38 C0 04 15 */	li r6, 0x415
/* 80090F20 0008DB00  D0 01 00 5C */	stfs f0, 0x5c(r1)
/* 80090F24 0008DB04  80 7D 00 00 */	lwz r3, 0(r29)
/* 80090F28 0008DB08  80 83 00 2C */	lwz r4, 0x2c(r3)
/* 80090F2C 0008DB0C  38 84 06 0C */	addi r4, r4, 0x60c
/* 80090F30 0008DB10  4B FD 67 C1 */	bl efAsync_Spawn
/* 80090F34 0008DB14  88 1D 22 19 */	lbz r0, 0x2219(r29)
/* 80090F38 0008DB18  3B 80 00 01 */	li r28, 1
/* 80090F3C 0008DB1C  53 80 3E 30 */	rlwimi r0, r28, 7, 0x18, 0x18
/* 80090F40 0008DB20  98 1D 22 19 */	stb r0, 0x2219(r29)
/* 80090F44 0008DB24  38 80 00 02 */	li r4, 2
/* 80090F48 0008DB28  80 7D 00 00 */	lwz r3, 0(r29)
/* 80090F4C 0008DB2C  4B FE A1 75 */	bl func_8007B0C0
/* 80090F50 0008DB30  3C 60 80 3B */	lis r3, lbl_803B74B0@ha
/* 80090F54 0008DB34  38 C3 74 B0 */	addi r6, r3, lbl_803B74B0@l
/* 80090F58 0008DB38  80 A6 00 00 */	lwz r5, 0(r6)
/* 80090F5C 0008DB3C  7F A3 EB 78 */	mr r3, r29
/* 80090F60 0008DB40  80 06 00 04 */	lwz r0, 4(r6)
/* 80090F64 0008DB44  38 80 00 02 */	li r4, 2
/* 80090F68 0008DB48  90 A1 00 28 */	stw r5, 0x28(r1)
/* 80090F6C 0008DB4C  90 01 00 2C */	stw r0, 0x2c(r1)
/* 80090F70 0008DB50  80 06 00 08 */	lwz r0, 8(r6)
/* 80090F74 0008DB54  90 01 00 30 */	stw r0, 0x30(r1)
/* 80090F78 0008DB58  4B FE 40 95 */	bl func_8007500C
/* 80090F7C 0008DB5C  90 61 00 34 */	stw r3, 0x34(r1)
/* 80090F80 0008DB60  7F A3 EB 78 */	mr r3, r29
/* 80090F84 0008DB64  80 E1 00 28 */	lwz r7, 0x28(r1)
/* 80090F88 0008DB68  38 9D 11 A0 */	addi r4, r29, 0x11a0
/* 80090F8C 0008DB6C  93 81 00 38 */	stw r28, 0x38(r1)
/* 80090F90 0008DB70  80 C1 00 2C */	lwz r6, 0x2c(r1)
/* 80090F94 0008DB74  38 A1 00 34 */	addi r5, r1, 0x34
/* 80090F98 0008DB78  93 E1 00 3C */	stw r31, 0x3c(r1)
/* 80090F9C 0008DB7C  80 01 00 30 */	lwz r0, 0x30(r1)
/* 80090FA0 0008DB80  90 E1 00 4C */	stw r7, 0x4c(r1)
/* 80090FA4 0008DB84  90 C1 00 50 */	stw r6, 0x50(r1)
/* 80090FA8 0008DB88  90 01 00 54 */	stw r0, 0x54(r1)
/* 80090FAC 0008DB8C  80 C1 00 4C */	lwz r6, 0x4c(r1)
/* 80090FB0 0008DB90  80 01 00 50 */	lwz r0, 0x50(r1)
/* 80090FB4 0008DB94  90 C1 00 40 */	stw r6, 0x40(r1)
/* 80090FB8 0008DB98  90 01 00 44 */	stw r0, 0x44(r1)
/* 80090FBC 0008DB9C  80 01 00 54 */	lwz r0, 0x54(r1)
/* 80090FC0 0008DBA0  90 01 00 48 */	stw r0, 0x48(r1)
/* 80090FC4 0008DBA4  C0 1E 00 00 */	lfs f0, 0(r30)
/* 80090FC8 0008DBA8  D0 01 00 58 */	stfs f0, 0x58(r1)
/* 80090FCC 0008DBAC  4B FE A5 E1 */	bl func_8007B5AC
/* 80090FD0 0008DBB0  38 7D 00 00 */	addi r3, r29, 0
/* 80090FD4 0008DBB4  38 80 00 01 */	li r4, 1
/* 80090FD8 0008DBB8  38 A0 00 00 */	li r5, 0
/* 80090FDC 0008DBBC  4B FE DB D1 */	bl func_8007EBAC
/* 80090FE0 0008DBC0  3C 60 80 09 */	lis r3, lbl_80091274@ha
/* 80090FE4 0008DBC4  38 03 12 74 */	addi r0, r3, lbl_80091274@l
/* 80090FE8 0008DBC8  3C 60 80 09 */	lis r3, lbl_80090B48@ha
/* 80090FEC 0008DBCC  90 1D 21 F0 */	stw r0, 0x21f0(r29)
/* 80090FF0 0008DBD0  38 03 0B 48 */	addi r0, r3, lbl_80090B48@l
/* 80090FF4 0008DBD4  90 1D 21 DC */	stw r0, 0x21dc(r29)
/* 80090FF8 0008DBD8  38 7D 00 00 */	addi r3, r29, 0
/* 80090FFC 0008DBDC  38 80 01 22 */	li r4, 0x122
/* 80091000 0008DBE0  38 A0 00 7F */	li r5, 0x7f
/* 80091004 0008DBE4  38 C0 00 40 */	li r6, 0x40
/* 80091008 0008DBE8  4B FF 76 D1 */	bl func_800886D8
/* 8009100C 0008DBEC  80 01 01 D4 */	lwz r0, 0x1d4(r1)
/* 80091010 0008DBF0  CB E1 01 C8 */	lfd f31, 0x1c8(r1)
/* 80091014 0008DBF4  83 E1 01 C4 */	lwz r31, 0x1c4(r1)
/* 80091018 0008DBF8  83 C1 01 C0 */	lwz r30, 0x1c0(r1)
/* 8009101C 0008DBFC  83 A1 01 BC */	lwz r29, 0x1bc(r1)
/* 80091020 0008DC00  83 81 01 B8 */	lwz r28, 0x1b8(r1)
/* 80091024 0008DC04  38 21 01 D0 */	addi r1, r1, 0x1d0
/* 80091028 0008DC08  7C 08 03 A6 */	mtlr r0
/* 8009102C 0008DC0C  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

#pragma push
asm unk_t func_80091030()
{ // clang-format off
    nofralloc
/* 80091030 0008DC10  7C 08 02 A6 */	mflr r0
/* 80091034 0008DC14  90 01 00 04 */	stw r0, 4(r1)
/* 80091038 0008DC18  94 21 FF 90 */	stwu r1, -0x70(r1)
/* 8009103C 0008DC1C  93 E1 00 6C */	stw r31, 0x6c(r1)
/* 80091040 0008DC20  93 C1 00 68 */	stw r30, 0x68(r1)
/* 80091044 0008DC24  7C 7E 1B 78 */	mr r30, r3
/* 80091048 0008DC28  93 A1 00 64 */	stw r29, 0x64(r1)
/* 8009104C 0008DC2C  93 81 00 60 */	stw r28, 0x60(r1)
/* 80091050 0008DC30  83 A3 00 2C */	lwz r29, 0x2c(r3)
/* 80091054 0008DC34  4B FE CB 05 */	bl func_8007DB58
/* 80091058 0008DC38  7F C3 F3 78 */	mr r3, r30
/* 8009105C 0008DC3C  48 00 64 B1 */	bl func_8009750C
/* 80091060 0008DC40  7F C3 F3 78 */	mr r3, r30
/* 80091064 0008DC44  48 04 C1 05 */	bl func_800DD168
/* 80091068 0008DC48  88 1D 22 27 */	lbz r0, 0x2227(r29)
/* 8009106C 0008DC4C  3B 80 00 01 */	li r28, 1
/* 80091070 0008DC50  53 80 0F BC */	rlwimi r0, r28, 1, 0x1e, 0x1e
/* 80091074 0008DC54  98 1D 22 27 */	stb r0, 0x2227(r29)
/* 80091078 0008DC58  38 7E 00 00 */	addi r3, r30, 0
/* 8009107C 0008DC5C  38 80 01 45 */	li r4, 0x145
/* 80091080 0008DC60  C0 22 8B 38 */	lfs f1, lbl_804D8518(r2)
/* 80091084 0008DC64  38 A0 00 42 */	li r5, 0x42
/* 80091088 0008DC68  C0 42 8B 3C */	lfs f2, lbl_804D851C(r2)
/* 8009108C 0008DC6C  38 C0 00 00 */	li r6, 0
/* 80091090 0008DC70  FC 60 08 90 */	fmr f3, f1
/* 80091094 0008DC74  4B FD 83 19 */	bl Fighter_ActionStateChange_800693AC
/* 80091098 0008DC78  38 7D 00 00 */	addi r3, r29, 0
/* 8009109C 0008DC7C  38 80 00 00 */	li r4, 0
/* 800910A0 0008DC80  48 00 D0 A1 */	bl func_8009E140
/* 800910A4 0008DC84  80 7D 00 00 */	lwz r3, 0(r29)
/* 800910A8 0008DC88  4B FE E7 7D */	bl func_8007F824
/* 800910AC 0008DC8C  88 1D 22 22 */	lbz r0, 0x2222(r29)
/* 800910B0 0008DC90  53 80 26 F6 */	rlwimi r0, r28, 4, 0x1b, 0x1b
/* 800910B4 0008DC94  98 1D 22 22 */	stb r0, 0x2222(r29)
/* 800910B8 0008DC98  80 1D 00 E0 */	lwz r0, 0xe0(r29)
/* 800910BC 0008DC9C  2C 00 00 01 */	cmpwi r0, 1
/* 800910C0 0008DCA0  40 82 00 30 */	bne lbl_800910F0
/* 800910C4 0008DCA4  80 7D 00 8C */	lwz r3, 0x8c(r29)
/* 800910C8 0008DCA8  80 1D 00 90 */	lwz r0, 0x90(r29)
/* 800910CC 0008DCAC  90 7D 00 80 */	stw r3, 0x80(r29)
/* 800910D0 0008DCB0  90 1D 00 84 */	stw r0, 0x84(r29)
/* 800910D4 0008DCB4  80 1D 00 94 */	lwz r0, 0x94(r29)
/* 800910D8 0008DCB8  90 1D 00 88 */	stw r0, 0x88(r29)
/* 800910DC 0008DCBC  C0 02 8B 38 */	lfs f0, lbl_804D8518(r2)
/* 800910E0 0008DCC0  D0 1D 00 94 */	stfs f0, 0x94(r29)
/* 800910E4 0008DCC4  D0 1D 00 90 */	stfs f0, 0x90(r29)
/* 800910E8 0008DCC8  D0 1D 00 8C */	stfs f0, 0x8c(r29)
/* 800910EC 0008DCCC  48 00 00 14 */	b lbl_80091100
lbl_800910F0:
/* 800910F0 0008DCD0  C0 1D 00 F0 */	lfs f0, 0xf0(r29)
/* 800910F4 0008DCD4  D0 1D 00 EC */	stfs f0, 0xec(r29)
/* 800910F8 0008DCD8  C0 02 8B 38 */	lfs f0, lbl_804D8518(r2)
/* 800910FC 0008DCDC  D0 1D 00 F0 */	stfs f0, 0xf0(r29)
lbl_80091100:
/* 80091100 0008DCE0  38 7D 00 00 */	addi r3, r29, 0
/* 80091104 0008DCE4  38 80 01 FF */	li r4, 0x1ff
/* 80091108 0008DCE8  4B FE D1 ED */	bl func_8007E2F4
/* 8009110C 0008DCEC  3B E0 00 00 */	li r31, 0
/* 80091110 0008DCF0  9B FD 23 40 */	stb r31, 0x2340(r29)
/* 80091114 0008DCF4  48 2E F4 15 */	bl HSD_Randf
/* 80091118 0008DCF8  80 8D AE B4 */	lwz r4, p_ftCommonData(r13)
/* 8009111C 0008DCFC  7F A3 EB 78 */	mr r3, r29
/* 80091120 0008DD00  C0 44 07 88 */	lfs f2, 0x788(r4)
/* 80091124 0008DD04  C0 04 07 8C */	lfs f0, 0x78c(r4)
/* 80091128 0008DD08  EC 00 10 28 */	fsubs f0, f0, f2
/* 8009112C 0008DD0C  EC 00 10 7A */	fmadds f0, f0, f1, f2
/* 80091130 0008DD10  D0 1D 23 44 */	stfs f0, 0x2344(r29)
/* 80091134 0008DD14  4B FF F8 9D */	bl func_800909D0
/* 80091138 0008DD18  38 7D 00 00 */	addi r3, r29, 0
/* 8009113C 0008DD1C  38 80 00 02 */	li r4, 2
/* 80091140 0008DD20  4B FE 3E CD */	bl func_8007500C
/* 80091144 0008DD24  C0 3D 00 38 */	lfs f1, 0x38(r29)
/* 80091148 0008DD28  54 60 20 36 */	slwi r0, r3, 4
/* 8009114C 0008DD2C  C0 1D 02 5C */	lfs f0, 0x25c(r29)
/* 80091150 0008DD30  3B DD 02 5C */	addi r30, r29, 0x25c
/* 80091154 0008DD34  80 8D AE B4 */	lwz r4, p_ftCommonData(r13)
/* 80091158 0008DD38  EC 21 00 32 */	fmuls f1, f1, f0
/* 8009115C 0008DD3C  80 7D 05 E8 */	lwz r3, 0x5e8(r29)
/* 80091160 0008DD40  C0 04 07 A0 */	lfs f0, 0x7a0(r4)
/* 80091164 0008DD44  39 01 00 54 */	addi r8, r1, 0x54
/* 80091168 0008DD48  7C E3 00 2E */	lwzx r7, r3, r0
/* 8009116C 0008DD4C  EC 01 00 24 */	fdivs f0, f1, f0
/* 80091170 0008DD50  4C C6 31 82 */	crclr 6
/* 80091174 0008DD54  38 A0 00 03 */	li r5, 3
/* 80091178 0008DD58  38 C0 04 15 */	li r6, 0x415
/* 8009117C 0008DD5C  D0 01 00 54 */	stfs f0, 0x54(r1)
/* 80091180 0008DD60  80 7D 00 00 */	lwz r3, 0(r29)
/* 80091184 0008DD64  80 83 00 2C */	lwz r4, 0x2c(r3)
/* 80091188 0008DD68  38 84 06 0C */	addi r4, r4, 0x60c
/* 8009118C 0008DD6C  4B FD 65 65 */	bl efAsync_Spawn
/* 80091190 0008DD70  88 1D 22 19 */	lbz r0, 0x2219(r29)
/* 80091194 0008DD74  3B 80 00 01 */	li r28, 1
/* 80091198 0008DD78  53 80 3E 30 */	rlwimi r0, r28, 7, 0x18, 0x18
/* 8009119C 0008DD7C  98 1D 22 19 */	stb r0, 0x2219(r29)
/* 800911A0 0008DD80  38 80 00 02 */	li r4, 2
/* 800911A4 0008DD84  80 7D 00 00 */	lwz r3, 0(r29)
/* 800911A8 0008DD88  4B FE 9F 19 */	bl func_8007B0C0
/* 800911AC 0008DD8C  3C 60 80 3B */	lis r3, lbl_803B74B0@ha
/* 800911B0 0008DD90  38 C3 74 B0 */	addi r6, r3, lbl_803B74B0@l
/* 800911B4 0008DD94  80 A6 00 00 */	lwz r5, 0(r6)
/* 800911B8 0008DD98  7F A3 EB 78 */	mr r3, r29
/* 800911BC 0008DD9C  80 06 00 04 */	lwz r0, 4(r6)
/* 800911C0 0008DDA0  38 80 00 02 */	li r4, 2
/* 800911C4 0008DDA4  90 A1 00 20 */	stw r5, 0x20(r1)
/* 800911C8 0008DDA8  90 01 00 24 */	stw r0, 0x24(r1)
/* 800911CC 0008DDAC  80 06 00 08 */	lwz r0, 8(r6)
/* 800911D0 0008DDB0  90 01 00 28 */	stw r0, 0x28(r1)
/* 800911D4 0008DDB4  4B FE 3E 39 */	bl func_8007500C
/* 800911D8 0008DDB8  90 61 00 2C */	stw r3, 0x2c(r1)
/* 800911DC 0008DDBC  7F A3 EB 78 */	mr r3, r29
/* 800911E0 0008DDC0  80 E1 00 20 */	lwz r7, 0x20(r1)
/* 800911E4 0008DDC4  38 9D 11 A0 */	addi r4, r29, 0x11a0
/* 800911E8 0008DDC8  93 81 00 30 */	stw r28, 0x30(r1)
/* 800911EC 0008DDCC  80 C1 00 24 */	lwz r6, 0x24(r1)
/* 800911F0 0008DDD0  38 A1 00 2C */	addi r5, r1, 0x2c
/* 800911F4 0008DDD4  93 E1 00 34 */	stw r31, 0x34(r1)
/* 800911F8 0008DDD8  80 01 00 28 */	lwz r0, 0x28(r1)
/* 800911FC 0008DDDC  90 E1 00 44 */	stw r7, 0x44(r1)
/* 80091200 0008DDE0  90 C1 00 48 */	stw r6, 0x48(r1)
/* 80091204 0008DDE4  90 01 00 4C */	stw r0, 0x4c(r1)
/* 80091208 0008DDE8  80 C1 00 44 */	lwz r6, 0x44(r1)
/* 8009120C 0008DDEC  80 01 00 48 */	lwz r0, 0x48(r1)
/* 80091210 0008DDF0  90 C1 00 38 */	stw r6, 0x38(r1)
/* 80091214 0008DDF4  90 01 00 3C */	stw r0, 0x3c(r1)
/* 80091218 0008DDF8  80 01 00 4C */	lwz r0, 0x4c(r1)
/* 8009121C 0008DDFC  90 01 00 40 */	stw r0, 0x40(r1)
/* 80091220 0008DE00  C0 1E 00 00 */	lfs f0, 0(r30)
/* 80091224 0008DE04  D0 01 00 50 */	stfs f0, 0x50(r1)
/* 80091228 0008DE08  4B FE A3 85 */	bl func_8007B5AC
/* 8009122C 0008DE0C  38 7D 00 00 */	addi r3, r29, 0
/* 80091230 0008DE10  38 80 00 01 */	li r4, 1
/* 80091234 0008DE14  38 A0 00 00 */	li r5, 0
/* 80091238 0008DE18  4B FE D9 75 */	bl func_8007EBAC
/* 8009123C 0008DE1C  3C 60 80 09 */	lis r3, lbl_80091274@ha
/* 80091240 0008DE20  38 03 12 74 */	addi r0, r3, lbl_80091274@l
/* 80091244 0008DE24  3C 60 80 09 */	lis r3, lbl_80090B48@ha
/* 80091248 0008DE28  90 1D 21 F0 */	stw r0, 0x21f0(r29)
/* 8009124C 0008DE2C  38 03 0B 48 */	addi r0, r3, lbl_80090B48@l
/* 80091250 0008DE30  90 1D 21 DC */	stw r0, 0x21dc(r29)
/* 80091254 0008DE34  80 01 00 74 */	lwz r0, 0x74(r1)
/* 80091258 0008DE38  83 E1 00 6C */	lwz r31, 0x6c(r1)
/* 8009125C 0008DE3C  83 C1 00 68 */	lwz r30, 0x68(r1)
/* 80091260 0008DE40  83 A1 00 64 */	lwz r29, 0x64(r1)
/* 80091264 0008DE44  83 81 00 60 */	lwz r28, 0x60(r1)
/* 80091268 0008DE48  38 21 00 70 */	addi r1, r1, 0x70
/* 8009126C 0008DE4C  7C 08 03 A6 */	mtlr r0
/* 80091270 0008DE50  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

#pragma push
asm unk_t lbl_80091274()
{ // clang-format off
    nofralloc
/* 80091274 0008DE54  80 83 00 2C */	lwz r4, 0x2c(r3)
/* 80091278 0008DE58  80 6D AE B4 */	lwz r3, p_ftCommonData(r13)
/* 8009127C 0008DE5C  C0 44 18 38 */	lfs f2, 0x1838(r4)
/* 80091280 0008DE60  C0 23 07 9C */	lfs f1, 0x79c(r3)
/* 80091284 0008DE64  C0 04 1A 4C */	lfs f0, 0x1a4c(r4)
/* 80091288 0008DE68  EC 02 00 7C */	fnmsubs f0, f2, f1, f0
/* 8009128C 0008DE6C  D0 04 1A 4C */	stfs f0, 0x1a4c(r4)
/* 80091290 0008DE70  80 04 18 60 */	lwz r0, 0x1860(r4)
/* 80091294 0008DE74  28 00 00 01 */	cmplwi r0, 1
/* 80091298 0008DE78  4C 82 00 20 */	bnelr 
/* 8009129C 0008DE7C  C0 02 8B 38 */	lfs f0, lbl_804D8518(r2)
/* 800912A0 0008DE80  D0 04 1A 4C */	stfs f0, 0x1a4c(r4)
/* 800912A4 0008DE84  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

extern unk_t func_80091854();

#pragma push
asm unk_t func_800912A8()
{ // clang-format off
    nofralloc
/* 800912A8 0008DE88  7C 08 02 A6 */	mflr r0
/* 800912AC 0008DE8C  90 01 00 04 */	stw r0, 4(r1)
/* 800912B0 0008DE90  94 21 FF D8 */	stwu r1, -0x28(r1)
/* 800912B4 0008DE94  DB E1 00 20 */	stfd f31, 0x20(r1)
/* 800912B8 0008DE98  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 800912BC 0008DE9C  93 C1 00 18 */	stw r30, 0x18(r1)
/* 800912C0 0008DEA0  93 A1 00 14 */	stw r29, 0x14(r1)
/* 800912C4 0008DEA4  7C 7D 1B 78 */	mr r29, r3
/* 800912C8 0008DEA8  80 63 00 2C */	lwz r3, 0x2c(r3)
/* 800912CC 0008DEAC  80 03 00 E0 */	lwz r0, 0xe0(r3)
/* 800912D0 0008DEB0  3B C3 00 00 */	addi r30, r3, 0
/* 800912D4 0008DEB4  2C 00 00 01 */	cmpwi r0, 1
/* 800912D8 0008DEB8  40 82 00 98 */	bne lbl_80091370
/* 800912DC 0008DEBC  C3 FE 23 44 */	lfs f31, 0x2344(r30)
/* 800912E0 0008DEC0  38 7E 00 00 */	addi r3, r30, 0
/* 800912E4 0008DEC4  38 80 00 02 */	li r4, 2
/* 800912E8 0008DEC8  4B FE 3D 25 */	bl func_8007500C
/* 800912EC 0008DECC  80 9E 05 E8 */	lwz r4, 0x5e8(r30)
/* 800912F0 0008DED0  54 60 20 36 */	slwi r0, r3, 4
/* 800912F4 0008DED4  7F E4 00 2E */	lwzx r31, r4, r0
/* 800912F8 0008DED8  28 1F 00 00 */	cmplwi r31, 0
/* 800912FC 0008DEDC  40 82 00 14 */	bne lbl_80091310
/* 80091300 0008DEE0  38 6D 84 48 */	addi r3, r13, lbl_804D3AE8
/* 80091304 0008DEE4  38 80 04 05 */	li r4, 0x405
/* 80091308 0008DEE8  38 AD 84 50 */	addi r5, r13, lbl_804D3AF0
/* 8009130C 0008DEEC  48 2F 6F 15 */	bl __assert
lbl_80091310:
/* 80091310 0008DEF0  C0 1F 00 1C */	lfs f0, 0x1c(r31)
/* 80091314 0008DEF4  EC 00 F8 2A */	fadds f0, f0, f31
/* 80091318 0008DEF8  D0 1F 00 1C */	stfs f0, 0x1c(r31)
/* 8009131C 0008DEFC  80 1F 00 14 */	lwz r0, 0x14(r31)
/* 80091320 0008DF00  54 00 01 8D */	rlwinm. r0, r0, 0, 6, 6
/* 80091324 0008DF04  40 82 00 4C */	bne lbl_80091370
/* 80091328 0008DF08  28 1F 00 00 */	cmplwi r31, 0
/* 8009132C 0008DF0C  41 82 00 44 */	beq lbl_80091370
/* 80091330 0008DF10  40 82 00 14 */	bne lbl_80091344
/* 80091334 0008DF14  38 6D 84 48 */	addi r3, r13, lbl_804D3AE8
/* 80091338 0008DF18  38 80 02 34 */	li r4, 0x234
/* 8009133C 0008DF1C  38 AD 84 50 */	addi r5, r13, lbl_804D3AF0
/* 80091340 0008DF20  48 2F 6E E1 */	bl __assert
lbl_80091344:
/* 80091344 0008DF24  80 9F 00 14 */	lwz r4, 0x14(r31)
/* 80091348 0008DF28  38 60 00 00 */	li r3, 0
/* 8009134C 0008DF2C  54 80 02 11 */	rlwinm. r0, r4, 0, 8, 8
/* 80091350 0008DF30  40 82 00 10 */	bne lbl_80091360
/* 80091354 0008DF34  54 80 06 73 */	rlwinm. r0, r4, 0, 0x19, 0x19
/* 80091358 0008DF38  41 82 00 08 */	beq lbl_80091360
/* 8009135C 0008DF3C  38 60 00 01 */	li r3, 1
lbl_80091360:
/* 80091360 0008DF40  2C 03 00 00 */	cmpwi r3, 0
/* 80091364 0008DF44  40 82 00 0C */	bne lbl_80091370
/* 80091368 0008DF48  7F E3 FB 78 */	mr r3, r31
/* 8009136C 0008DF4C  48 2E 1F 7D */	bl HSD_JObjSetMtxDirtySub
lbl_80091370:
/* 80091370 0008DF50  88 1E 22 24 */	lbz r0, 0x2224(r30)
/* 80091374 0008DF54  54 00 DF FF */	rlwinm. r0, r0, 0x1b, 0x1f, 0x1f
/* 80091378 0008DF58  40 82 00 18 */	bne lbl_80091390
/* 8009137C 0008DF5C  80 6D AE B4 */	lwz r3, p_ftCommonData(r13)
/* 80091380 0008DF60  C0 3E 1A 4C */	lfs f1, 0x1a4c(r30)
/* 80091384 0008DF64  C0 03 07 94 */	lfs f0, 0x794(r3)
/* 80091388 0008DF68  EC 01 00 28 */	fsubs f0, f1, f0
/* 8009138C 0008DF6C  D0 1E 1A 4C */	stfs f0, 0x1a4c(r30)
lbl_80091390:
/* 80091390 0008DF70  80 8D AE B4 */	lwz r4, p_ftCommonData(r13)
/* 80091394 0008DF74  7F C3 F3 78 */	mr r3, r30
/* 80091398 0008DF78  C0 24 07 98 */	lfs f1, 0x798(r4)
/* 8009139C 0008DF7C  4B FE C8 6D */	bl func_8007DC08
/* 800913A0 0008DF80  C0 3E 1A 4C */	lfs f1, 0x1a4c(r30)
/* 800913A4 0008DF84  C0 02 8B 38 */	lfs f0, lbl_804D8518(r2)
/* 800913A8 0008DF88  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 800913AC 0008DF8C  4C 40 13 82 */	cror 2, 0, 2
/* 800913B0 0008DF90  40 82 00 0C */	bne lbl_800913BC
/* 800913B4 0008DF94  7F A3 EB 78 */	mr r3, r29
/* 800913B8 0008DF98  48 00 04 9D */	bl func_80091854
lbl_800913BC:
/* 800913BC 0008DF9C  80 01 00 2C */	lwz r0, 0x2c(r1)
/* 800913C0 0008DFA0  CB E1 00 20 */	lfd f31, 0x20(r1)
/* 800913C4 0008DFA4  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 800913C8 0008DFA8  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 800913CC 0008DFAC  83 A1 00 14 */	lwz r29, 0x14(r1)
/* 800913D0 0008DFB0  38 21 00 28 */	addi r1, r1, 0x28
/* 800913D4 0008DFB4  7C 08 03 A6 */	mtlr r0
/* 800913D8 0008DFB8  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

void func_800913DC(void)
{
    return;
}

#pragma push
asm unk_t func_800913E0()
{ // clang-format off
    nofralloc
/* 800913E0 0008DFC0  7C 08 02 A6 */	mflr r0
/* 800913E4 0008DFC4  90 01 00 04 */	stw r0, 4(r1)
/* 800913E8 0008DFC8  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 800913EC 0008DFCC  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 800913F0 0008DFD0  93 C1 00 18 */	stw r30, 0x18(r1)
/* 800913F4 0008DFD4  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 800913F8 0008DFD8  80 1F 00 E0 */	lwz r0, 0xe0(r31)
/* 800913FC 0008DFDC  3B DF 01 10 */	addi r30, r31, 0x110
/* 80091400 0008DFE0  2C 00 00 01 */	cmpwi r0, 1
/* 80091404 0008DFE4  40 82 00 2C */	bne lbl_80091430
/* 80091408 0008DFE8  7F E3 FB 78 */	mr r3, r31
/* 8009140C 0008DFEC  4B FE BA E9 */	bl func_8007CEF4
/* 80091410 0008DFF0  80 8D AE B4 */	lwz r4, p_ftCommonData(r13)
/* 80091414 0008DFF4  7F E3 FB 78 */	mr r3, r31
/* 80091418 0008DFF8  C0 3E 00 5C */	lfs f1, 0x5c(r30)
/* 8009141C 0008DFFC  C0 04 07 7C */	lfs f0, 0x77c(r4)
/* 80091420 0008E000  C0 5E 00 60 */	lfs f2, 0x60(r30)
/* 80091424 0008E004  EC 21 00 32 */	fmuls f1, f1, f0
/* 80091428 0008E008  4B FE C0 6D */	bl func_8007D494
/* 8009142C 0008E00C  48 00 00 08 */	b lbl_80091434
lbl_80091430:
/* 80091430 0008E010  4B FF 3B 0D */	bl func_80084F3C
lbl_80091434:
/* 80091434 0008E014  80 01 00 24 */	lwz r0, 0x24(r1)
/* 80091438 0008E018  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 8009143C 0008E01C  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 80091440 0008E020  38 21 00 20 */	addi r1, r1, 0x20
/* 80091444 0008E024  7C 08 03 A6 */	mtlr r0
/* 80091448 0008E028  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

extern unk_t func_800914A4();

#pragma push
asm unk_t func_8009144C()
{ // clang-format off
    nofralloc
/* 8009144C 0008E02C  7C 08 02 A6 */	mflr r0
/* 80091450 0008E030  90 01 00 04 */	stw r0, 4(r1)
/* 80091454 0008E034  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 80091458 0008E038  93 E1 00 14 */	stw r31, 0x14(r1)
/* 8009145C 0008E03C  80 83 00 2C */	lwz r4, 0x2c(r3)
/* 80091460 0008E040  80 04 00 E0 */	lwz r0, 0xe0(r4)
/* 80091464 0008E044  3B E4 00 00 */	addi r31, r4, 0
/* 80091468 0008E048  2C 00 00 01 */	cmpwi r0, 1
/* 8009146C 0008E04C  40 82 00 0C */	bne lbl_80091478
/* 80091470 0008E050  48 00 00 35 */	bl func_800914A4
/* 80091474 0008E054  48 00 00 1C */	b lbl_80091490
lbl_80091478:
/* 80091478 0008E058  38 9F 23 48 */	addi r4, r31, 0x2348
/* 8009147C 0008E05C  4B FF 14 0D */	bl func_80082888
/* 80091480 0008E060  2C 03 00 00 */	cmpwi r3, 0
/* 80091484 0008E064  40 82 00 0C */	bne lbl_80091490
/* 80091488 0008E068  7F E3 FB 78 */	mr r3, r31
/* 8009148C 0008E06C  4B FE C1 49 */	bl func_8007D5D4
lbl_80091490:
/* 80091490 0008E070  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 80091494 0008E074  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 80091498 0008E078  38 21 00 18 */	addi r1, r1, 0x18
/* 8009149C 0008E07C  7C 08 03 A6 */	mtlr r0
/* 800914A0 0008E080  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

extern f32 const lbl_804D8520;
extern unk_t func_80091620();
extern unk_t func_800F1F1C();

#pragma push
asm unk_t func_800914A4()
{ // clang-format off
    nofralloc
/* 800914A4 0008E084  7C 08 02 A6 */	mflr r0
/* 800914A8 0008E088  90 01 00 04 */	stw r0, 4(r1)
/* 800914AC 0008E08C  94 21 FF C8 */	stwu r1, -0x38(r1)
/* 800914B0 0008E090  93 E1 00 34 */	stw r31, 0x34(r1)
/* 800914B4 0008E094  93 C1 00 30 */	stw r30, 0x30(r1)
/* 800914B8 0008E098  93 A1 00 2C */	stw r29, 0x2c(r1)
/* 800914BC 0008E09C  7C 7D 1B 78 */	mr r29, r3
/* 800914C0 0008E0A0  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 800914C4 0008E0A4  C0 02 8B 40 */	lfs f0, lbl_804D8520(r2)
/* 800914C8 0008E0A8  C0 3F 08 94 */	lfs f1, 0x894(r31)
/* 800914CC 0008E0AC  3B DF 06 F0 */	addi r30, r31, 0x6f0
/* 800914D0 0008E0B0  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 800914D4 0008E0B4  4C 40 13 82 */	cror 2, 0, 2
/* 800914D8 0008E0B8  40 82 00 14 */	bne lbl_800914EC
/* 800914DC 0008E0BC  38 7D 00 00 */	addi r3, r29, 0
/* 800914E0 0008E0C0  38 9F 23 48 */	addi r4, r31, 0x2348
/* 800914E4 0008E0C4  4B FF 11 55 */	bl func_80082638
/* 800914E8 0008E0C8  48 00 00 10 */	b lbl_800914F8
lbl_800914EC:
/* 800914EC 0008E0CC  38 7D 00 00 */	addi r3, r29, 0
/* 800914F0 0008E0D0  38 9F 23 48 */	addi r4, r31, 0x2348
/* 800914F4 0008E0D4  4B FF 0F AD */	bl func_800824A0
lbl_800914F8:
/* 800914F8 0008E0D8  80 9E 01 34 */	lwz r4, 0x134(r30)
/* 800914FC 0008E0DC  54 80 05 29 */	rlwinm. r0, r4, 0, 0x14, 0x14
/* 80091500 0008E0E0  41 82 00 50 */	beq lbl_80091550
/* 80091504 0008E0E4  88 1F 23 40 */	lbz r0, 0x2340(r31)
/* 80091508 0008E0E8  28 00 00 01 */	cmplwi r0, 1
/* 8009150C 0008E0EC  41 82 00 44 */	beq lbl_80091550
/* 80091510 0008E0F0  C0 3E 00 BC */	lfs f1, 0xbc(r30)
/* 80091514 0008E0F4  7F A3 EB 78 */	mr r3, r29
/* 80091518 0008E0F8  C0 02 8B 38 */	lfs f0, lbl_804D8518(r2)
/* 8009151C 0008E0FC  38 81 00 1C */	addi r4, r1, 0x1c
/* 80091520 0008E100  D0 21 00 1C */	stfs f1, 0x1c(r1)
/* 80091524 0008E104  C0 3E 00 C0 */	lfs f1, 0xc0(r30)
/* 80091528 0008E108  D0 21 00 20 */	stfs f1, 0x20(r1)
/* 8009152C 0008E10C  D0 01 00 24 */	stfs f0, 0x24(r1)
/* 80091530 0008E110  48 06 09 ED */	bl func_800F1F1C
/* 80091534 0008E114  38 9E 01 7C */	addi r4, r30, 0x17c
/* 80091538 0008E118  38 7D 00 00 */	addi r3, r29, 0
/* 8009153C 0008E11C  38 A1 00 1C */	addi r5, r1, 0x1c
/* 80091540 0008E120  48 00 00 E1 */	bl func_80091620
/* 80091544 0008E124  38 00 00 01 */	li r0, 1
/* 80091548 0008E128  98 1F 23 40 */	stb r0, 0x2340(r31)
/* 8009154C 0008E12C  48 00 00 B8 */	b lbl_80091604
lbl_80091550:
/* 80091550 0008E130  54 80 06 B5 */	rlwinm. r0, r4, 0, 0x1a, 0x1a
/* 80091554 0008E134  41 82 00 50 */	beq lbl_800915A4
/* 80091558 0008E138  88 1F 23 40 */	lbz r0, 0x2340(r31)
/* 8009155C 0008E13C  28 00 00 02 */	cmplwi r0, 2
/* 80091560 0008E140  41 82 00 44 */	beq lbl_800915A4
/* 80091564 0008E144  C0 3E 00 B4 */	lfs f1, 0xb4(r30)
/* 80091568 0008E148  7F A3 EB 78 */	mr r3, r29
/* 8009156C 0008E14C  C0 02 8B 38 */	lfs f0, lbl_804D8518(r2)
/* 80091570 0008E150  38 81 00 1C */	addi r4, r1, 0x1c
/* 80091574 0008E154  D0 21 00 1C */	stfs f1, 0x1c(r1)
/* 80091578 0008E158  C0 3E 00 B8 */	lfs f1, 0xb8(r30)
/* 8009157C 0008E15C  D0 21 00 20 */	stfs f1, 0x20(r1)
/* 80091580 0008E160  D0 01 00 24 */	stfs f0, 0x24(r1)
/* 80091584 0008E164  48 06 09 99 */	bl func_800F1F1C
/* 80091588 0008E168  38 9E 01 68 */	addi r4, r30, 0x168
/* 8009158C 0008E16C  38 7D 00 00 */	addi r3, r29, 0
/* 80091590 0008E170  38 A1 00 1C */	addi r5, r1, 0x1c
/* 80091594 0008E174  48 00 00 8D */	bl func_80091620
/* 80091598 0008E178  38 00 00 02 */	li r0, 2
/* 8009159C 0008E17C  98 1F 23 40 */	stb r0, 0x2340(r31)
/* 800915A0 0008E180  48 00 00 64 */	b lbl_80091604
lbl_800915A4:
/* 800915A4 0008E184  54 80 04 63 */	rlwinm. r0, r4, 0, 0x11, 0x11
/* 800915A8 0008E188  41 82 00 4C */	beq lbl_800915F4
/* 800915AC 0008E18C  88 1F 23 40 */	lbz r0, 0x2340(r31)
/* 800915B0 0008E190  28 00 00 03 */	cmplwi r0, 3
/* 800915B4 0008E194  41 82 00 40 */	beq lbl_800915F4
/* 800915B8 0008E198  C0 22 8B 38 */	lfs f1, lbl_804D8518(r2)
/* 800915BC 0008E19C  38 7D 00 00 */	addi r3, r29, 0
/* 800915C0 0008E1A0  38 81 00 1C */	addi r4, r1, 0x1c
/* 800915C4 0008E1A4  D0 21 00 1C */	stfs f1, 0x1c(r1)
/* 800915C8 0008E1A8  C0 1E 00 A8 */	lfs f0, 0xa8(r30)
/* 800915CC 0008E1AC  D0 01 00 20 */	stfs f0, 0x20(r1)
/* 800915D0 0008E1B0  D0 21 00 24 */	stfs f1, 0x24(r1)
/* 800915D4 0008E1B4  48 06 09 49 */	bl func_800F1F1C
/* 800915D8 0008E1B8  38 9E 01 90 */	addi r4, r30, 0x190
/* 800915DC 0008E1BC  38 7D 00 00 */	addi r3, r29, 0
/* 800915E0 0008E1C0  38 A1 00 1C */	addi r5, r1, 0x1c
/* 800915E4 0008E1C4  48 00 00 3D */	bl func_80091620
/* 800915E8 0008E1C8  38 00 00 03 */	li r0, 3
/* 800915EC 0008E1CC  98 1F 23 40 */	stb r0, 0x2340(r31)
/* 800915F0 0008E1D0  48 00 00 14 */	b lbl_80091604
lbl_800915F4:
/* 800915F4 0008E1D4  2C 03 00 00 */	cmpwi r3, 0
/* 800915F8 0008E1D8  41 82 00 0C */	beq lbl_80091604
/* 800915FC 0008E1DC  7F E3 FB 78 */	mr r3, r31
/* 80091600 0008E1E0  4B FE C1 FD */	bl func_8007D7FC
lbl_80091604:
/* 80091604 0008E1E4  80 01 00 3C */	lwz r0, 0x3c(r1)
/* 80091608 0008E1E8  83 E1 00 34 */	lwz r31, 0x34(r1)
/* 8009160C 0008E1EC  83 C1 00 30 */	lwz r30, 0x30(r1)
/* 80091610 0008E1F0  83 A1 00 2C */	lwz r29, 0x2c(r1)
/* 80091614 0008E1F4  38 21 00 38 */	addi r1, r1, 0x38
/* 80091618 0008E1F8  7C 08 03 A6 */	mtlr r0
/* 8009161C 0008E1FC  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

extern f32 const lbl_804D8528;
extern f64 const lbl_804D8530;

#pragma push
asm unk_t func_80091620()
{ // clang-format off
    nofralloc
/* 80091620 0008E200  7C 08 02 A6 */	mflr r0
/* 80091624 0008E204  90 01 00 04 */	stw r0, 4(r1)
/* 80091628 0008E208  94 21 FF A0 */	stwu r1, -0x60(r1)
/* 8009162C 0008E20C  BF 61 00 4C */	stmw r27, 0x4c(r1)
/* 80091630 0008E210  7C 7B 1B 78 */	mr r27, r3
/* 80091634 0008E214  7C BD 2B 78 */	mr r29, r5
/* 80091638 0008E218  7C 9C 23 78 */	mr r28, r4
/* 8009163C 0008E21C  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 80091640 0008E220  C0 05 00 00 */	lfs f0, 0(r5)
/* 80091644 0008E224  C0 3F 00 B0 */	lfs f1, 0xb0(r31)
/* 80091648 0008E228  3B DF 06 F0 */	addi r30, r31, 0x6f0
/* 8009164C 0008E22C  EC 01 00 2A */	fadds f0, f1, f0
/* 80091650 0008E230  D0 01 00 2C */	stfs f0, 0x2c(r1)
/* 80091654 0008E234  C0 3F 00 B4 */	lfs f1, 0xb4(r31)
/* 80091658 0008E238  C0 05 00 04 */	lfs f0, 4(r5)
/* 8009165C 0008E23C  EC 01 00 2A */	fadds f0, f1, f0
/* 80091660 0008E240  D0 01 00 30 */	stfs f0, 0x30(r1)
/* 80091664 0008E244  C0 3F 00 B8 */	lfs f1, 0xb8(r31)
/* 80091668 0008E248  C0 05 00 08 */	lfs f0, 8(r5)
/* 8009166C 0008E24C  EC 01 00 2A */	fadds f0, f1, f0
/* 80091670 0008E250  D0 01 00 34 */	stfs f0, 0x34(r1)
/* 80091674 0008E254  C0 04 00 00 */	lfs f0, 0(r4)
/* 80091678 0008E258  C0 44 00 04 */	lfs f2, 4(r4)
/* 8009167C 0008E25C  FC 20 00 50 */	fneg f1, f0
/* 80091680 0008E260  4B F9 15 B1 */	bl atan2f
/* 80091684 0008E264  D0 21 00 24 */	stfs f1, 0x24(r1)
/* 80091688 0008E268  38 7B 00 00 */	addi r3, r27, 0
/* 8009168C 0008E26C  39 01 00 2C */	addi r8, r1, 0x2c
/* 80091690 0008E270  4C C6 31 82 */	crclr 6
/* 80091694 0008E274  80 9B 00 2C */	lwz r4, 0x2c(r27)
/* 80091698 0008E278  39 21 00 24 */	addi r9, r1, 0x24
/* 8009169C 0008E27C  38 84 06 0C */	addi r4, r4, 0x60c
/* 800916A0 0008E280  38 A0 00 05 */	li r5, 5
/* 800916A4 0008E284  38 C0 04 06 */	li r6, 0x406
/* 800916A8 0008E288  38 E0 00 00 */	li r7, 0
/* 800916AC 0008E28C  4B FD 60 45 */	bl efAsync_Spawn
/* 800916B0 0008E290  38 60 00 02 */	li r3, 2
/* 800916B4 0008E294  38 81 00 2C */	addi r4, r1, 0x2c
/* 800916B8 0008E298  4B F9 F7 8D */	bl func_80030E44
/* 800916BC 0008E29C  38 7F 00 00 */	addi r3, r31, 0
/* 800916C0 0008E2A0  38 80 00 07 */	li r4, 7
/* 800916C4 0008E2A4  38 A0 00 00 */	li r5, 0
/* 800916C8 0008E2A8  4B FE D4 E5 */	bl func_8007EBAC
/* 800916CC 0008E2AC  38 7F 00 00 */	addi r3, r31, 0
/* 800916D0 0008E2B0  38 80 01 23 */	li r4, 0x123
/* 800916D4 0008E2B4  38 A0 00 7F */	li r5, 0x7f
/* 800916D8 0008E2B8  38 C0 00 40 */	li r6, 0x40
/* 800916DC 0008E2BC  4B FF 6A 6D */	bl func_80088148
/* 800916E0 0008E2C0  C0 3F 00 80 */	lfs f1, 0x80(r31)
/* 800916E4 0008E2C4  C0 1F 00 84 */	lfs f0, 0x84(r31)
/* 800916E8 0008E2C8  EC 41 00 72 */	fmuls f2, f1, f1
/* 800916EC 0008E2CC  C0 7F 00 88 */	lfs f3, 0x88(r31)
/* 800916F0 0008E2D0  EC 20 00 32 */	fmuls f1, f0, f0
/* 800916F4 0008E2D4  C0 02 8B 38 */	lfs f0, lbl_804D8518(r2)
/* 800916F8 0008E2D8  EC 63 00 F2 */	fmuls f3, f3, f3
/* 800916FC 0008E2DC  EC 22 08 2A */	fadds f1, f2, f1
/* 80091700 0008E2E0  EC 83 08 2A */	fadds f4, f3, f1
/* 80091704 0008E2E4  FC 04 00 40 */	fcmpo cr0, f4, f0
/* 80091708 0008E2E8  40 81 00 50 */	ble lbl_80091758
/* 8009170C 0008E2EC  FC 20 20 34 */	frsqrte f1, f4
/* 80091710 0008E2F0  C8 62 8B 48 */	lfd f3, lbl_804D8528(r2)
/* 80091714 0008E2F4  C8 42 8B 50 */	lfd f2, lbl_804D8530(r2)
/* 80091718 0008E2F8  FC 01 00 72 */	fmul f0, f1, f1
/* 8009171C 0008E2FC  FC 23 00 72 */	fmul f1, f3, f1
/* 80091720 0008E300  FC 04 10 3C */	fnmsub f0, f4, f0, f2
/* 80091724 0008E304  FC 21 00 32 */	fmul f1, f1, f0
/* 80091728 0008E308  FC 01 00 72 */	fmul f0, f1, f1
/* 8009172C 0008E30C  FC 23 00 72 */	fmul f1, f3, f1
/* 80091730 0008E310  FC 04 10 3C */	fnmsub f0, f4, f0, f2
/* 80091734 0008E314  FC 21 00 32 */	fmul f1, f1, f0
/* 80091738 0008E318  FC 01 00 72 */	fmul f0, f1, f1
/* 8009173C 0008E31C  FC 23 00 72 */	fmul f1, f3, f1
/* 80091740 0008E320  FC 04 10 3C */	fnmsub f0, f4, f0, f2
/* 80091744 0008E324  FC 01 00 32 */	fmul f0, f1, f0
/* 80091748 0008E328  FC 04 00 32 */	fmul f0, f4, f0
/* 8009174C 0008E32C  FC 00 00 18 */	frsp f0, f0
/* 80091750 0008E330  D0 01 00 20 */	stfs f0, 0x20(r1)
/* 80091754 0008E334  C0 81 00 20 */	lfs f4, 0x20(r1)
lbl_80091758:
/* 80091758 0008E338  80 6D AE B4 */	lwz r3, p_ftCommonData(r13)
/* 8009175C 0008E33C  C0 03 07 80 */	lfs f0, 0x780(r3)
/* 80091760 0008E340  FC 04 00 40 */	fcmpo cr0, f4, f0
/* 80091764 0008E344  40 81 00 4C */	ble lbl_800917B0
/* 80091768 0008E348  38 7F 00 00 */	addi r3, r31, 0
/* 8009176C 0008E34C  38 80 01 23 */	li r4, 0x123
/* 80091770 0008E350  38 A0 00 7F */	li r5, 0x7f
/* 80091774 0008E354  38 C0 00 40 */	li r6, 0x40
/* 80091778 0008E358  4B FF 69 D1 */	bl func_80088148
/* 8009177C 0008E35C  80 A1 00 2C */	lwz r5, 0x2c(r1)
/* 80091780 0008E360  38 80 00 00 */	li r4, 0
/* 80091784 0008E364  80 01 00 30 */	lwz r0, 0x30(r1)
/* 80091788 0008E368  7F 63 DB 78 */	mr r3, r27
/* 8009178C 0008E36C  90 BF 00 B0 */	stw r5, 0xb0(r31)
/* 80091790 0008E370  90 1F 00 B4 */	stw r0, 0xb4(r31)
/* 80091794 0008E374  80 01 00 34 */	lwz r0, 0x34(r1)
/* 80091798 0008E378  90 1F 00 B8 */	stw r0, 0xb8(r31)
/* 8009179C 0008E37C  88 1F 22 27 */	lbz r0, 0x2227(r31)
/* 800917A0 0008E380  50 80 0F BC */	rlwimi r0, r4, 1, 0x1e, 0x1e
/* 800917A4 0008E384  98 1F 22 27 */	stb r0, 0x2227(r31)
/* 800917A8 0008E388  4B FF EF D9 */	bl func_80090780
/* 800917AC 0008E38C  48 00 00 94 */	b lbl_80091840
lbl_800917B0:
/* 800917B0 0008E390  38 7F 00 80 */	addi r3, r31, 0x80
/* 800917B4 0008E394  38 9C 00 00 */	addi r4, r28, 0
/* 800917B8 0008E398  4B F7 C4 B5 */	bl lbvector_Mirror
/* 800917BC 0008E39C  80 6D AE B4 */	lwz r3, p_ftCommonData(r13)
/* 800917C0 0008E3A0  C0 1F 00 80 */	lfs f0, 0x80(r31)
/* 800917C4 0008E3A4  C0 23 07 84 */	lfs f1, 0x784(r3)
/* 800917C8 0008E3A8  EC 00 00 72 */	fmuls f0, f0, f1
/* 800917CC 0008E3AC  D0 1F 00 80 */	stfs f0, 0x80(r31)
/* 800917D0 0008E3B0  C0 1F 00 84 */	lfs f0, 0x84(r31)
/* 800917D4 0008E3B4  EC 00 00 72 */	fmuls f0, f0, f1
/* 800917D8 0008E3B8  D0 1F 00 84 */	stfs f0, 0x84(r31)
/* 800917DC 0008E3BC  80 1E 01 34 */	lwz r0, 0x134(r30)
/* 800917E0 0008E3C0  54 00 05 29 */	rlwinm. r0, r0, 0, 0x14, 0x14
/* 800917E4 0008E3C4  40 82 00 08 */	bne lbl_800917EC
/* 800917E8 0008E3C8  41 82 00 28 */	beq lbl_80091810
lbl_800917EC:
/* 800917EC 0008E3CC  C0 5F 00 2C */	lfs f2, 0x2c(r31)
/* 800917F0 0008E3D0  C0 3F 00 B0 */	lfs f1, 0xb0(r31)
/* 800917F4 0008E3D4  C0 1D 00 00 */	lfs f0, 0(r29)
/* 800917F8 0008E3D8  FC 40 10 50 */	fneg f2, f2
/* 800917FC 0008E3DC  C0 7F 06 94 */	lfs f3, 0x694(r31)
/* 80091800 0008E3E0  EC 01 00 2A */	fadds f0, f1, f0
/* 80091804 0008E3E4  EC 03 00 BC */	fnmsubs f0, f3, f2, f0
/* 80091808 0008E3E8  D0 1F 00 B0 */	stfs f0, 0xb0(r31)
/* 8009180C 0008E3EC  48 00 00 1C */	b lbl_80091828
lbl_80091810:
/* 80091810 0008E3F0  C0 3F 00 B4 */	lfs f1, 0xb4(r31)
/* 80091814 0008E3F4  C0 1D 00 04 */	lfs f0, 4(r29)
/* 80091818 0008E3F8  C0 5F 06 90 */	lfs f2, 0x690(r31)
/* 8009181C 0008E3FC  EC 01 00 2A */	fadds f0, f1, f0
/* 80091820 0008E400  EC 02 00 2A */	fadds f0, f2, f0
/* 80091824 0008E404  D0 1F 00 B4 */	stfs f0, 0xb4(r31)
lbl_80091828:
/* 80091828 0008E408  7F 63 DB 78 */	mr r3, r27
/* 8009182C 0008E40C  4B FF 04 E1 */	bl func_80081D0C
/* 80091830 0008E410  2C 03 00 00 */	cmpwi r3, 0
/* 80091834 0008E414  41 82 00 0C */	beq lbl_80091840
/* 80091838 0008E418  7F E3 FB 78 */	mr r3, r31
/* 8009183C 0008E41C  4B FE BF C1 */	bl func_8007D7FC
lbl_80091840:
/* 80091840 0008E420  BB 61 00 4C */	lmw r27, 0x4c(r1)
/* 80091844 0008E424  80 01 00 64 */	lwz r0, 0x64(r1)
/* 80091848 0008E428  38 21 00 60 */	addi r1, r1, 0x60
/* 8009184C 0008E42C  7C 08 03 A6 */	mtlr r0
/* 80091850 0008E430  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

extern Vec const lbl_803B74BC;
extern unk_t func_800C5A98();

#pragma push
asm unk_t func_80091854()
{ // clang-format off
    nofralloc
/* 80091854 0008E434  7C 08 02 A6 */	mflr r0
/* 80091858 0008E438  90 01 00 04 */	stw r0, 4(r1)
/* 8009185C 0008E43C  94 21 FF C0 */	stwu r1, -0x40(r1)
/* 80091860 0008E440  93 E1 00 3C */	stw r31, 0x3c(r1)
/* 80091864 0008E444  93 C1 00 38 */	stw r30, 0x38(r1)
/* 80091868 0008E448  7C 7E 1B 78 */	mr r30, r3
/* 8009186C 0008E44C  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 80091870 0008E450  48 03 39 D1 */	bl func_800C5240
/* 80091874 0008E454  2C 03 00 00 */	cmpwi r3, 0
/* 80091878 0008E458  41 82 00 10 */	beq lbl_80091888
/* 8009187C 0008E45C  7F C3 F3 78 */	mr r3, r30
/* 80091880 0008E460  48 03 42 19 */	bl func_800C5A98
/* 80091884 0008E464  48 00 00 EC */	b lbl_80091970
lbl_80091888:
/* 80091888 0008E468  7F E3 FB 78 */	mr r3, r31
/* 8009188C 0008E46C  4B FE BD 49 */	bl func_8007D5D4
/* 80091890 0008E470  88 1F 22 27 */	lbz r0, 0x2227(r31)
/* 80091894 0008E474  38 60 00 00 */	li r3, 0
/* 80091898 0008E478  50 60 0F BC */	rlwimi r0, r3, 1, 0x1e, 0x1e
/* 8009189C 0008E47C  98 1F 22 27 */	stb r0, 0x2227(r31)
/* 800918A0 0008E480  38 7E 00 00 */	addi r3, r30, 0
/* 800918A4 0008E484  38 80 01 46 */	li r4, 0x146
/* 800918A8 0008E488  C0 22 8B 38 */	lfs f1, lbl_804D8518(r2)
/* 800918AC 0008E48C  38 A0 00 40 */	li r5, 0x40
/* 800918B0 0008E490  38 C0 00 00 */	li r6, 0
/* 800918B4 0008E494  FC 40 08 90 */	fmr f2, f1
/* 800918B8 0008E498  FC 60 08 90 */	fmr f3, f1
/* 800918BC 0008E49C  4B FD 7A F1 */	bl Fighter_ActionStateChange_800693AC
/* 800918C0 0008E4A0  38 7F 00 00 */	addi r3, r31, 0
/* 800918C4 0008E4A4  38 80 01 23 */	li r4, 0x123
/* 800918C8 0008E4A8  38 A0 00 7F */	li r5, 0x7f
/* 800918CC 0008E4AC  38 C0 00 40 */	li r6, 0x40
/* 800918D0 0008E4B0  4B FF 68 79 */	bl func_80088148
/* 800918D4 0008E4B4  38 7F 00 00 */	addi r3, r31, 0
/* 800918D8 0008E4B8  38 80 00 02 */	li r4, 2
/* 800918DC 0008E4BC  4B FE 37 31 */	bl func_8007500C
/* 800918E0 0008E4C0  3C A0 80 3B */	lis r5, lbl_803B74BC@ha
/* 800918E4 0008E4C4  80 DF 05 E8 */	lwz r6, 0x5e8(r31)
/* 800918E8 0008E4C8  54 60 20 36 */	slwi r0, r3, 4
/* 800918EC 0008E4CC  80 8D AE B4 */	lwz r4, p_ftCommonData(r13)
/* 800918F0 0008E4D0  39 45 74 BC */	addi r10, r5, lbl_803B74BC@l
/* 800918F4 0008E4D4  7C E6 00 2E */	lwzx r7, r6, r0
/* 800918F8 0008E4D8  80 AA 00 00 */	lwz r5, 0(r10)
/* 800918FC 0008E4DC  7F C3 F3 78 */	mr r3, r30
/* 80091900 0008E4E0  80 0A 00 04 */	lwz r0, 4(r10)
/* 80091904 0008E4E4  39 01 00 28 */	addi r8, r1, 0x28
/* 80091908 0008E4E8  39 21 00 24 */	addi r9, r1, 0x24
/* 8009190C 0008E4EC  90 A1 00 28 */	stw r5, 0x28(r1)
/* 80091910 0008E4F0  4C C6 31 82 */	crclr 6
/* 80091914 0008E4F4  38 A0 00 05 */	li r5, 5
/* 80091918 0008E4F8  90 01 00 2C */	stw r0, 0x2c(r1)
/* 8009191C 0008E4FC  38 C0 04 43 */	li r6, 0x443
/* 80091920 0008E500  80 0A 00 08 */	lwz r0, 8(r10)
/* 80091924 0008E504  90 01 00 30 */	stw r0, 0x30(r1)
/* 80091928 0008E508  C0 5F 00 38 */	lfs f2, 0x38(r31)
/* 8009192C 0008E50C  C0 3F 02 5C */	lfs f1, 0x25c(r31)
/* 80091930 0008E510  C0 04 07 A0 */	lfs f0, 0x7a0(r4)
/* 80091934 0008E514  EC 22 00 72 */	fmuls f1, f2, f1
/* 80091938 0008E518  EC 01 00 24 */	fdivs f0, f1, f0
/* 8009193C 0008E51C  D0 01 00 24 */	stfs f0, 0x24(r1)
/* 80091940 0008E520  80 9E 00 2C */	lwz r4, 0x2c(r30)
/* 80091944 0008E524  38 84 06 0C */	addi r4, r4, 0x60c
/* 80091948 0008E528  4B FD 5D A9 */	bl efAsync_Spawn
/* 8009194C 0008E52C  C0 3F 06 20 */	lfs f1, 0x620(r31)
/* 80091950 0008E530  C0 1F 02 6C */	lfs f0, 0x26c(r31)
/* 80091954 0008E534  EC 01 00 32 */	fmuls f0, f1, f0
/* 80091958 0008E538  D0 1F 00 80 */	stfs f0, 0x80(r31)
/* 8009195C 0008E53C  C0 1F 02 68 */	lfs f0, 0x268(r31)
/* 80091960 0008E540  D0 1F 00 84 */	stfs f0, 0x84(r31)
/* 80091964 0008E544  80 6D AE B4 */	lwz r3, p_ftCommonData(r13)
/* 80091968 0008E548  C0 03 07 A4 */	lfs f0, 0x7a4(r3)
/* 8009196C 0008E54C  D0 1F 23 40 */	stfs f0, 0x2340(r31)
lbl_80091970:
/* 80091970 0008E550  80 01 00 44 */	lwz r0, 0x44(r1)
/* 80091974 0008E554  83 E1 00 3C */	lwz r31, 0x3c(r1)
/* 80091978 0008E558  83 C1 00 38 */	lwz r30, 0x38(r1)
/* 8009197C 0008E55C  38 21 00 40 */	addi r1, r1, 0x40
/* 80091980 0008E560  7C 08 03 A6 */	mtlr r0
/* 80091984 0008E564  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

#pragma push
asm unk_t func_80091988()
{ // clang-format off
    nofralloc
/* 80091988 0008E568  7C 08 02 A6 */	mflr r0
/* 8009198C 0008E56C  90 01 00 04 */	stw r0, 4(r1)
/* 80091990 0008E570  94 21 FF F8 */	stwu r1, -8(r1)
/* 80091994 0008E574  80 83 00 2C */	lwz r4, 0x2c(r3)
/* 80091998 0008E578  C0 22 8B 38 */	lfs f1, lbl_804D8518(r2)
/* 8009199C 0008E57C  C0 44 23 40 */	lfs f2, 0x2340(r4)
/* 800919A0 0008E580  FC 02 08 40 */	fcmpo cr0, f2, f1
/* 800919A4 0008E584  40 81 00 24 */	ble lbl_800919C8
/* 800919A8 0008E588  C0 02 8B 3C */	lfs f0, lbl_804D851C(r2)
/* 800919AC 0008E58C  EC 02 00 28 */	fsubs f0, f2, f0
/* 800919B0 0008E590  D0 04 23 40 */	stfs f0, 0x2340(r4)
/* 800919B4 0008E594  C0 04 23 40 */	lfs f0, 0x2340(r4)
/* 800919B8 0008E598  FC 00 08 40 */	fcmpo cr0, f0, f1
/* 800919BC 0008E59C  4C 40 13 82 */	cror 2, 0, 2
/* 800919C0 0008E5A0  40 82 00 08 */	bne lbl_800919C8
/* 800919C4 0008E5A4  48 03 AD 6D */	bl func_800CC730
lbl_800919C8:
/* 800919C8 0008E5A8  80 01 00 0C */	lwz r0, 0xc(r1)
/* 800919CC 0008E5AC  38 21 00 08 */	addi r1, r1, 8
/* 800919D0 0008E5B0  7C 08 03 A6 */	mtlr r0
/* 800919D4 0008E5B4  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

void func_800919D8(void)
{
    return;
}

#pragma push
asm unk_t func_800919DC()
{ // clang-format off
    nofralloc
/* 800919DC 0008E5BC  7C 08 02 A6 */	mflr r0
/* 800919E0 0008E5C0  90 01 00 04 */	stw r0, 4(r1)
/* 800919E4 0008E5C4  94 21 FF F8 */	stwu r1, -8(r1)
/* 800919E8 0008E5C8  4B FF 35 05 */	bl func_80084EEC
/* 800919EC 0008E5CC  80 01 00 0C */	lwz r0, 0xc(r1)
/* 800919F0 0008E5D0  38 21 00 08 */	addi r1, r1, 8
/* 800919F4 0008E5D4  7C 08 03 A6 */	mtlr r0
/* 800919F8 0008E5D8  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

#pragma push
asm unk_t func_800919FC()
{ // clang-format off
    nofralloc
/* 800919FC 0008E5DC  7C 08 02 A6 */	mflr r0
/* 80091A00 0008E5E0  3C 80 80 09 */	lis r4, func_80096CC8@ha
/* 80091A04 0008E5E4  90 01 00 04 */	stw r0, 4(r1)
/* 80091A08 0008E5E8  3C A0 80 08 */	lis r5, func_80082B1C@ha
/* 80091A0C 0008E5EC  38 84 6C C8 */	addi r4, r4, func_80096CC8@l
/* 80091A10 0008E5F0  94 21 FF F8 */	stwu r1, -8(r1)
/* 80091A14 0008E5F4  38 A5 2B 1C */	addi r5, r5, func_80082B1C@l
/* 80091A18 0008E5F8  4B FF 17 B5 */	bl func_800831CC
/* 80091A1C 0008E5FC  80 01 00 0C */	lwz r0, 0xc(r1)
/* 80091A20 0008E600  38 21 00 08 */	addi r1, r1, 8
/* 80091A24 0008E604  7C 08 03 A6 */	mtlr r0
/* 80091A28 0008E608  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

#pragma push
asm unk_t func_80091A2C()
{ // clang-format off
    nofralloc
/* 80091A2C 0008E60C  80 63 00 2C */	lwz r3, 0x2c(r3)
/* 80091A30 0008E610  80 03 06 5C */	lwz r0, 0x65c(r3)
/* 80091A34 0008E614  54 00 00 01 */	rlwinm. r0, r0, 0, 0, 0
/* 80091A38 0008E618  41 82 00 0C */	beq lbl_80091A44
/* 80091A3C 0008E61C  38 60 00 01 */	li r3, 1
/* 80091A40 0008E620  4E 80 00 20 */	blr 
lbl_80091A44:
/* 80091A44 0008E624  38 60 00 00 */	li r3, 0
/* 80091A48 0008E628  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

extern f32 const lbl_804D8538;
extern unk_t func_800923B4();
extern unk_t func_800939B4();

#pragma push
asm unk_t func_80091A4C()
{ // clang-format off
    nofralloc
/* 80091A4C 0008E62C  7C 08 02 A6 */	mflr r0
/* 80091A50 0008E630  90 01 00 04 */	stw r0, 4(r1)
/* 80091A54 0008E634  94 21 FF F8 */	stwu r1, -8(r1)
/* 80091A58 0008E638  80 C3 00 2C */	lwz r6, 0x2c(r3)
/* 80091A5C 0008E63C  80 06 06 68 */	lwz r0, 0x668(r6)
/* 80091A60 0008E640  54 00 06 75 */	rlwinm. r0, r0, 0, 0x19, 0x1a
/* 80091A64 0008E644  41 82 00 24 */	beq lbl_80091A88
/* 80091A68 0008E648  80 8D AE B4 */	lwz r4, p_ftCommonData(r13)
/* 80091A6C 0008E64C  88 A6 06 72 */	lbz r5, 0x672(r6)
/* 80091A70 0008E650  80 04 02 A0 */	lwz r0, 0x2a0(r4)
/* 80091A74 0008E654  7C 05 00 00 */	cmpw r5, r0
/* 80091A78 0008E658  40 80 00 10 */	bge lbl_80091A88
/* 80091A7C 0008E65C  48 00 1F 39 */	bl func_800939B4
/* 80091A80 0008E660  38 60 00 01 */	li r3, 1
/* 80091A84 0008E664  48 00 00 44 */	b lbl_80091AC8
lbl_80091A88:
/* 80091A88 0008E668  80 06 06 5C */	lwz r0, 0x65c(r6)
/* 80091A8C 0008E66C  54 00 00 01 */	rlwinm. r0, r0, 0, 0, 0
/* 80091A90 0008E670  41 82 00 0C */	beq lbl_80091A9C
/* 80091A94 0008E674  38 00 00 01 */	li r0, 1
/* 80091A98 0008E678  48 00 00 08 */	b lbl_80091AA0
lbl_80091A9C:
/* 80091A9C 0008E67C  38 00 00 00 */	li r0, 0
lbl_80091AA0:
/* 80091AA0 0008E680  2C 00 00 00 */	cmpwi r0, 0
/* 80091AA4 0008E684  41 82 00 20 */	beq lbl_80091AC4
/* 80091AA8 0008E688  C0 26 19 98 */	lfs f1, 0x1998(r6)
/* 80091AAC 0008E68C  C0 02 8B 58 */	lfs f0, lbl_804D8538(r2)
/* 80091AB0 0008E690  FC 01 00 00 */	fcmpu cr0, f1, f0
/* 80091AB4 0008E694  41 82 00 10 */	beq lbl_80091AC4
/* 80091AB8 0008E698  48 00 08 FD */	bl func_800923B4
/* 80091ABC 0008E69C  38 60 00 01 */	li r3, 1
/* 80091AC0 0008E6A0  48 00 00 08 */	b lbl_80091AC8
lbl_80091AC4:
/* 80091AC4 0008E6A4  38 60 00 00 */	li r3, 0
lbl_80091AC8:
/* 80091AC8 0008E6A8  80 01 00 0C */	lwz r0, 0xc(r1)
/* 80091ACC 0008E6AC  38 21 00 08 */	addi r1, r1, 8
/* 80091AD0 0008E6B0  7C 08 03 A6 */	mtlr r0
/* 80091AD4 0008E6B4  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

#pragma push
asm unk_t func_80091AD8()
{ // clang-format off
    nofralloc
/* 80091AD8 0008E6B8  7C 08 02 A6 */	mflr r0
/* 80091ADC 0008E6BC  90 01 00 04 */	stw r0, 4(r1)
/* 80091AE0 0008E6C0  94 21 FF D8 */	stwu r1, -0x28(r1)
/* 80091AE4 0008E6C4  93 E1 00 24 */	stw r31, 0x24(r1)
/* 80091AE8 0008E6C8  93 C1 00 20 */	stw r30, 0x20(r1)
/* 80091AEC 0008E6CC  7C 9E 23 78 */	mr r30, r4
/* 80091AF0 0008E6D0  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 80091AF4 0008E6D4  80 1F 06 68 */	lwz r0, 0x668(r31)
/* 80091AF8 0008E6D8  54 00 06 75 */	rlwinm. r0, r0, 0, 0x19, 0x1a
/* 80091AFC 0008E6DC  41 82 00 24 */	beq lbl_80091B20
/* 80091B00 0008E6E0  80 8D AE B4 */	lwz r4, p_ftCommonData(r13)
/* 80091B04 0008E6E4  88 BF 06 72 */	lbz r5, 0x672(r31)
/* 80091B08 0008E6E8  80 04 02 A0 */	lwz r0, 0x2a0(r4)
/* 80091B0C 0008E6EC  7C 05 00 00 */	cmpw r5, r0
/* 80091B10 0008E6F0  40 80 00 10 */	bge lbl_80091B20
/* 80091B14 0008E6F4  48 00 1E A1 */	bl func_800939B4
/* 80091B18 0008E6F8  38 00 00 01 */	li r0, 1
/* 80091B1C 0008E6FC  48 00 00 44 */	b lbl_80091B60
lbl_80091B20:
/* 80091B20 0008E700  80 1F 06 5C */	lwz r0, 0x65c(r31)
/* 80091B24 0008E704  54 00 00 01 */	rlwinm. r0, r0, 0, 0, 0
/* 80091B28 0008E708  41 82 00 0C */	beq lbl_80091B34
/* 80091B2C 0008E70C  38 00 00 01 */	li r0, 1
/* 80091B30 0008E710  48 00 00 08 */	b lbl_80091B38
lbl_80091B34:
/* 80091B34 0008E714  38 00 00 00 */	li r0, 0
lbl_80091B38:
/* 80091B38 0008E718  2C 00 00 00 */	cmpwi r0, 0
/* 80091B3C 0008E71C  41 82 00 20 */	beq lbl_80091B5C
/* 80091B40 0008E720  C0 3F 19 98 */	lfs f1, 0x1998(r31)
/* 80091B44 0008E724  C0 02 8B 58 */	lfs f0, lbl_804D8538(r2)
/* 80091B48 0008E728  FC 01 00 00 */	fcmpu cr0, f1, f0
/* 80091B4C 0008E72C  41 82 00 10 */	beq lbl_80091B5C
/* 80091B50 0008E730  48 00 08 65 */	bl func_800923B4
/* 80091B54 0008E734  38 00 00 01 */	li r0, 1
/* 80091B58 0008E738  48 00 00 08 */	b lbl_80091B60
lbl_80091B5C:
/* 80091B5C 0008E73C  38 00 00 00 */	li r0, 0
lbl_80091B60:
/* 80091B60 0008E740  2C 00 00 00 */	cmpwi r0, 0
/* 80091B64 0008E744  41 82 00 10 */	beq lbl_80091B74
/* 80091B68 0008E748  93 DF 23 60 */	stw r30, 0x2360(r31)
/* 80091B6C 0008E74C  38 60 00 01 */	li r3, 1
/* 80091B70 0008E750  48 00 00 08 */	b lbl_80091B78
lbl_80091B74:
/* 80091B74 0008E754  38 60 00 00 */	li r3, 0
lbl_80091B78:
/* 80091B78 0008E758  80 01 00 2C */	lwz r0, 0x2c(r1)
/* 80091B7C 0008E75C  83 E1 00 24 */	lwz r31, 0x24(r1)
/* 80091B80 0008E760  83 C1 00 20 */	lwz r30, 0x20(r1)
/* 80091B84 0008E764  38 21 00 28 */	addi r1, r1, 0x28
/* 80091B88 0008E768  7C 08 03 A6 */	mtlr r0
/* 80091B8C 0008E76C  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

#pragma push
asm unk_t func_80091B90()
{ // clang-format off
    nofralloc
/* 80091B90 0008E770  80 63 00 2C */	lwz r3, 0x2c(r3)
/* 80091B94 0008E774  90 83 23 60 */	stw r4, 0x2360(r3)
/* 80091B98 0008E778  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

#pragma push
asm unk_t func_80091B9C()
{ // clang-format off
    nofralloc
/* 80091B9C 0008E77C  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 80091BA0 0008E780  80 8D AE B4 */	lwz r4, p_ftCommonData(r13)
/* 80091BA4 0008E784  80 63 00 2C */	lwz r3, 0x2c(r3)
/* 80091BA8 0008E788  C0 04 00 68 */	lfs f0, 0x68(r4)
/* 80091BAC 0008E78C  FC 00 00 1E */	fctiwz f0, f0
/* 80091BB0 0008E790  D8 01 00 18 */	stfd f0, 0x18(r1)
/* 80091BB4 0008E794  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 80091BB8 0008E798  90 03 23 64 */	stw r0, 0x2364(r3)
/* 80091BBC 0008E79C  38 21 00 20 */	addi r1, r1, 0x20
/* 80091BC0 0008E7A0  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

extern f32 const lbl_804D8548;
extern f64 const lbl_804D8558;
extern f64 const lbl_804D8560;
extern f32 const lbl_804D8568;
extern f32 const lbl_804D8550;
extern f32 const lbl_804D8554;
extern f32 const lbl_804D853C;
extern f32 const lbl_804D8540;
extern f32 const lbl_804D8544;
extern f32 const lbl_804D854C;
extern unk_t func_8000D008();
extern f32 const lbl_804D854C;

#pragma push
asm unk_t func_80091BC4()
{ // clang-format off
    nofralloc
/* 80091BC4 0008E7A4  7C 08 02 A6 */	mflr r0
/* 80091BC8 0008E7A8  90 01 00 04 */	stw r0, 4(r1)
/* 80091BCC 0008E7AC  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 80091BD0 0008E7B0  93 E1 00 14 */	stw r31, 0x14(r1)
/* 80091BD4 0008E7B4  7C 7F 1B 78 */	mr r31, r3
/* 80091BD8 0008E7B8  C0 43 06 20 */	lfs f2, 0x620(r3)
/* 80091BDC 0008E7BC  C0 03 00 2C */	lfs f0, 0x2c(r3)
/* 80091BE0 0008E7C0  C0 23 06 24 */	lfs f1, 0x624(r3)
/* 80091BE4 0008E7C4  EC 42 00 32 */	fmuls f2, f2, f0
/* 80091BE8 0008E7C8  4B F7 B4 21 */	bl func_8000D008
/* 80091BEC 0008E7CC  C0 02 8B 58 */	lfs f0, lbl_804D8538(r2)
/* 80091BF0 0008E7D0  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 80091BF4 0008E7D4  40 80 00 0C */	bge lbl_80091C00
/* 80091BF8 0008E7D8  C0 02 8B 5C */	lfs f0, lbl_804D853C(r2)
/* 80091BFC 0008E7DC  EC 21 00 2A */	fadds f1, f1, f0
lbl_80091C00:
/* 80091C00 0008E7E0  C0 42 8B 60 */	lfs f2, lbl_804D8540(r2)
/* 80091C04 0008E7E4  C0 02 8B 58 */	lfs f0, lbl_804D8538(r2)
/* 80091C08 0008E7E8  EC 22 00 72 */	fmuls f1, f2, f1
/* 80091C0C 0008E7EC  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 80091C10 0008E7F0  FC 60 08 90 */	fmr f3, f1
/* 80091C14 0008E7F4  40 80 00 08 */	bge lbl_80091C1C
/* 80091C18 0008E7F8  FC 60 00 90 */	fmr f3, f0
lbl_80091C1C:
/* 80091C1C 0008E7FC  C0 02 8B 64 */	lfs f0, lbl_804D8544(r2)
/* 80091C20 0008E800  FC 03 00 40 */	fcmpo cr0, f3, f0
/* 80091C24 0008E804  40 81 00 08 */	ble lbl_80091C2C
/* 80091C28 0008E808  FC 60 00 90 */	fmr f3, f0
lbl_80091C2C:
/* 80091C2C 0008E80C  C0 5F 23 48 */	lfs f2, 0x2348(r31)
/* 80091C30 0008E810  C0 22 8B 68 */	lfs f1, lbl_804D8548(r2)
/* 80091C34 0008E814  C0 02 8B 6C */	lfs f0, lbl_804D854C(r2)
/* 80091C38 0008E818  EC 42 08 28 */	fsubs f2, f2, f1
/* 80091C3C 0008E81C  EC 23 10 28 */	fsubs f1, f3, f2
/* 80091C40 0008E820  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 80091C44 0008E824  FC 60 08 90 */	fmr f3, f1
/* 80091C48 0008E828  40 81 00 10 */	ble lbl_80091C58
/* 80091C4C 0008E82C  C0 02 8B 70 */	lfs f0, lbl_804D8550(r2)
/* 80091C50 0008E830  EC 63 00 28 */	fsubs f3, f3, f0
/* 80091C54 0008E834  48 00 00 18 */	b lbl_80091C6C
lbl_80091C58:
/* 80091C58 0008E838  C0 02 8B 74 */	lfs f0, lbl_804D8554(r2)
/* 80091C5C 0008E83C  FC 03 00 40 */	fcmpo cr0, f3, f0
/* 80091C60 0008E840  40 80 00 0C */	bge lbl_80091C6C
/* 80091C64 0008E844  C0 02 8B 70 */	lfs f0, lbl_804D8550(r2)
/* 80091C68 0008E848  EC 63 00 2A */	fadds f3, f3, f0
lbl_80091C6C:
/* 80091C6C 0008E84C  80 6D AE B4 */	lwz r3, p_ftCommonData(r13)
/* 80091C70 0008E850  C0 22 8B 70 */	lfs f1, lbl_804D8550(r2)
/* 80091C74 0008E854  C0 03 04 4C */	lfs f0, 0x44c(r3)
/* 80091C78 0008E858  EC 03 10 3A */	fmadds f0, f3, f0, f2
/* 80091C7C 0008E85C  FC 00 08 40 */	fcmpo cr0, f0, f1
/* 80091C80 0008E860  FC 40 00 90 */	fmr f2, f0
/* 80091C84 0008E864  40 81 00 0C */	ble lbl_80091C90
/* 80091C88 0008E868  EC 42 08 28 */	fsubs f2, f2, f1
/* 80091C8C 0008E86C  48 00 00 14 */	b lbl_80091CA0
lbl_80091C90:
/* 80091C90 0008E870  C0 02 8B 58 */	lfs f0, lbl_804D8538(r2)
/* 80091C94 0008E874  FC 02 00 40 */	fcmpo cr0, f2, f0
/* 80091C98 0008E878  40 80 00 08 */	bge lbl_80091CA0
/* 80091C9C 0008E87C  EC 42 08 2A */	fadds f2, f2, f1
lbl_80091CA0:
/* 80091CA0 0008E880  C0 02 8B 68 */	lfs f0, lbl_804D8548(r2)
/* 80091CA4 0008E884  EC 00 10 2A */	fadds f0, f0, f2
/* 80091CA8 0008E888  D0 1F 23 48 */	stfs f0, 0x2348(r31)
/* 80091CAC 0008E88C  C0 1F 06 20 */	lfs f0, 0x620(r31)
/* 80091CB0 0008E890  C0 3F 06 24 */	lfs f1, 0x624(r31)
/* 80091CB4 0008E894  EC 40 00 32 */	fmuls f2, f0, f0
/* 80091CB8 0008E898  C0 02 8B 58 */	lfs f0, lbl_804D8538(r2)
/* 80091CBC 0008E89C  EC 21 00 72 */	fmuls f1, f1, f1
/* 80091CC0 0008E8A0  EC 82 08 2A */	fadds f4, f2, f1
/* 80091CC4 0008E8A4  FC 04 00 40 */	fcmpo cr0, f4, f0
/* 80091CC8 0008E8A8  40 81 00 50 */	ble lbl_80091D18
/* 80091CCC 0008E8AC  FC 20 20 34 */	frsqrte f1, f4
/* 80091CD0 0008E8B0  C8 62 8B 78 */	lfd f3, lbl_804D8558(r2)
/* 80091CD4 0008E8B4  C8 42 8B 80 */	lfd f2, lbl_804D8560(r2)
/* 80091CD8 0008E8B8  FC 01 00 72 */	fmul f0, f1, f1
/* 80091CDC 0008E8BC  FC 23 00 72 */	fmul f1, f3, f1
/* 80091CE0 0008E8C0  FC 04 10 3C */	fnmsub f0, f4, f0, f2
/* 80091CE4 0008E8C4  FC 21 00 32 */	fmul f1, f1, f0
/* 80091CE8 0008E8C8  FC 01 00 72 */	fmul f0, f1, f1
/* 80091CEC 0008E8CC  FC 23 00 72 */	fmul f1, f3, f1
/* 80091CF0 0008E8D0  FC 04 10 3C */	fnmsub f0, f4, f0, f2
/* 80091CF4 0008E8D4  FC 21 00 32 */	fmul f1, f1, f0
/* 80091CF8 0008E8D8  FC 01 00 72 */	fmul f0, f1, f1
/* 80091CFC 0008E8DC  FC 23 00 72 */	fmul f1, f3, f1
/* 80091D00 0008E8E0  FC 04 10 3C */	fnmsub f0, f4, f0, f2
/* 80091D04 0008E8E4  FC 01 00 32 */	fmul f0, f1, f0
/* 80091D08 0008E8E8  FC 04 00 32 */	fmul f0, f4, f0
/* 80091D0C 0008E8EC  FC 00 00 18 */	frsp f0, f0
/* 80091D10 0008E8F0  D0 01 00 0C */	stfs f0, 0xc(r1)
/* 80091D14 0008E8F4  C0 81 00 0C */	lfs f4, 0xc(r1)
lbl_80091D18:
/* 80091D18 0008E8F8  C0 02 8B 88 */	lfs f0, lbl_804D8568(r2)
/* 80091D1C 0008E8FC  FC 40 20 90 */	fmr f2, f4
/* 80091D20 0008E900  FC 04 00 40 */	fcmpo cr0, f4, f0
/* 80091D24 0008E904  40 81 00 08 */	ble lbl_80091D2C
/* 80091D28 0008E908  FC 40 00 90 */	fmr f2, f0
lbl_80091D2C:
/* 80091D2C 0008E90C  C0 3F 23 44 */	lfs f1, 0x2344(r31)
/* 80091D30 0008E910  80 6D AE B4 */	lwz r3, p_ftCommonData(r13)
/* 80091D34 0008E914  EC 02 08 28 */	fsubs f0, f2, f1
/* 80091D38 0008E918  C0 43 04 4C */	lfs f2, 0x44c(r3)
/* 80091D3C 0008E91C  EC 02 08 3A */	fmadds f0, f2, f0, f1
/* 80091D40 0008E920  D0 1F 23 44 */	stfs f0, 0x2344(r31)
/* 80091D44 0008E924  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 80091D48 0008E928  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 80091D4C 0008E92C  38 21 00 18 */	addi r1, r1, 0x18
/* 80091D50 0008E930  7C 08 03 A6 */	mtlr r0
/* 80091D54 0008E934  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

extern char* lbl_804D3AF8;
extern char* lbl_804D3B00;

#pragma push
asm unk_t func_80091D58()
{ // clang-format off
    nofralloc
/* 80091D58 0008E938  7C 08 02 A6 */	mflr r0
/* 80091D5C 0008E93C  90 01 00 04 */	stw r0, 4(r1)
/* 80091D60 0008E940  94 21 FF D0 */	stwu r1, -0x30(r1)
/* 80091D64 0008E944  93 E1 00 2C */	stw r31, 0x2c(r1)
/* 80091D68 0008E948  80 03 00 04 */	lwz r0, 4(r3)
/* 80091D6C 0008E94C  2C 00 00 0E */	cmpwi r0, 0xe
/* 80091D70 0008E950  40 82 00 0C */	bne lbl_80091D7C
/* 80091D74 0008E954  C0 03 01 A0 */	lfs f0, 0x1a0(r3)
/* 80091D78 0008E958  48 00 00 44 */	b lbl_80091DBC
lbl_80091D7C:
/* 80091D7C 0008E95C  80 8D AE B4 */	lwz r4, p_ftCommonData(r13)
/* 80091D80 0008E960  C0 23 19 98 */	lfs f1, 0x1998(r3)
/* 80091D84 0008E964  C0 04 02 60 */	lfs f0, 0x260(r4)
/* 80091D88 0008E968  C0 A4 02 D4 */	lfs f5, 0x2d4(r4)
/* 80091D8C 0008E96C  EC 61 00 24 */	fdivs f3, f1, f0
/* 80091D90 0008E970  C0 04 02 D8 */	lfs f0, 0x2d8(r4)
/* 80091D94 0008E974  C0 43 19 9C */	lfs f2, 0x199c(r3)
/* 80091D98 0008E978  C0 C4 02 64 */	lfs f6, 0x264(r4)
/* 80091D9C 0008E97C  C0 82 8B 88 */	lfs f4, lbl_804D8568(r2)
/* 80091DA0 0008E980  EC 20 28 28 */	fsubs f1, f0, f5
/* 80091DA4 0008E984  C0 03 01 A0 */	lfs f0, 0x1a0(r3)
/* 80091DA8 0008E988  EC 84 30 28 */	fsubs f4, f4, f6
/* 80091DAC 0008E98C  EC 22 28 7A */	fmadds f1, f2, f1, f5
/* 80091DB0 0008E990  EC 23 00 72 */	fmuls f1, f3, f1
/* 80091DB4 0008E994  EC 24 30 7A */	fmadds f1, f4, f1, f6
/* 80091DB8 0008E998  EC 01 00 32 */	fmuls f0, f1, f0
lbl_80091DBC:
/* 80091DBC 0008E99C  D0 01 00 20 */	stfs f0, 0x20(r1)
/* 80091DC0 0008E9A0  D0 01 00 1C */	stfs f0, 0x1c(r1)
/* 80091DC4 0008E9A4  D0 01 00 18 */	stfs f0, 0x18(r1)
/* 80091DC8 0008E9A8  80 83 01 0C */	lwz r4, 0x10c(r3)
/* 80091DCC 0008E9AC  80 A3 05 E8 */	lwz r5, 0x5e8(r3)
/* 80091DD0 0008E9B0  80 64 00 08 */	lwz r3, 8(r4)
/* 80091DD4 0008E9B4  88 03 00 11 */	lbz r0, 0x11(r3)
/* 80091DD8 0008E9B8  54 00 20 36 */	slwi r0, r0, 4
/* 80091DDC 0008E9BC  7F E5 00 2E */	lwzx r31, r5, r0
/* 80091DE0 0008E9C0  28 1F 00 00 */	cmplwi r31, 0
/* 80091DE4 0008E9C4  40 82 00 14 */	bne lbl_80091DF8
/* 80091DE8 0008E9C8  38 6D 84 58 */	addi r3, r13, lbl_804D3AF8
/* 80091DEC 0008E9CC  38 80 02 F8 */	li r4, 0x2f8
/* 80091DF0 0008E9D0  38 AD 84 60 */	addi r5, r13, lbl_804D3B00
/* 80091DF4 0008E9D4  48 2F 64 2D */	bl __assert
lbl_80091DF8:
/* 80091DF8 0008E9D8  80 61 00 18 */	lwz r3, 0x18(r1)
/* 80091DFC 0008E9DC  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 80091E00 0008E9E0  90 7F 00 2C */	stw r3, 0x2c(r31)
/* 80091E04 0008E9E4  90 1F 00 30 */	stw r0, 0x30(r31)
/* 80091E08 0008E9E8  80 01 00 20 */	lwz r0, 0x20(r1)
/* 80091E0C 0008E9EC  90 1F 00 34 */	stw r0, 0x34(r31)
/* 80091E10 0008E9F0  80 1F 00 14 */	lwz r0, 0x14(r31)
/* 80091E14 0008E9F4  54 00 01 8D */	rlwinm. r0, r0, 0, 6, 6
/* 80091E18 0008E9F8  40 82 00 4C */	bne lbl_80091E64
/* 80091E1C 0008E9FC  28 1F 00 00 */	cmplwi r31, 0
/* 80091E20 0008EA00  41 82 00 44 */	beq lbl_80091E64
/* 80091E24 0008EA04  40 82 00 14 */	bne lbl_80091E38
/* 80091E28 0008EA08  38 6D 84 58 */	addi r3, r13, lbl_804D3AF8
/* 80091E2C 0008EA0C  38 80 02 34 */	li r4, 0x234
/* 80091E30 0008EA10  38 AD 84 60 */	addi r5, r13, lbl_804D3B00
/* 80091E34 0008EA14  48 2F 63 ED */	bl __assert
lbl_80091E38:
/* 80091E38 0008EA18  80 9F 00 14 */	lwz r4, 0x14(r31)
/* 80091E3C 0008EA1C  38 60 00 00 */	li r3, 0
/* 80091E40 0008EA20  54 80 02 11 */	rlwinm. r0, r4, 0, 8, 8
/* 80091E44 0008EA24  40 82 00 10 */	bne lbl_80091E54
/* 80091E48 0008EA28  54 80 06 73 */	rlwinm. r0, r4, 0, 0x19, 0x19
/* 80091E4C 0008EA2C  41 82 00 08 */	beq lbl_80091E54
/* 80091E50 0008EA30  38 60 00 01 */	li r3, 1
lbl_80091E54:
/* 80091E54 0008EA34  2C 03 00 00 */	cmpwi r3, 0
/* 80091E58 0008EA38  40 82 00 0C */	bne lbl_80091E64
/* 80091E5C 0008EA3C  7F E3 FB 78 */	mr r3, r31
/* 80091E60 0008EA40  48 2E 14 89 */	bl HSD_JObjSetMtxDirtySub
lbl_80091E64:
/* 80091E64 0008EA44  80 01 00 34 */	lwz r0, 0x34(r1)
/* 80091E68 0008EA48  83 E1 00 2C */	lwz r31, 0x2c(r1)
/* 80091E6C 0008EA4C  38 21 00 30 */	addi r1, r1, 0x30
/* 80091E70 0008EA50  7C 08 03 A6 */	mtlr r0
/* 80091E74 0008EA54  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

extern f32 const lbl_804D856C;
extern f64 const lbl_804D8570;
extern unk_t func_8005F864();
extern unk_t func_8006FA58();
extern unk_t func_80070010();
extern unk_t func_8006FF74();
extern unk_t func_8006FE9C();
extern unk_t func_80070108();
extern unk_t func_8006FB88();
extern unk_t func_80070710();
extern unk_t func_8006F4C8();

#pragma push
asm unk_t func_80091E78()
{ // clang-format off
    nofralloc
/* 80091E78 0008EA58  7C 08 02 A6 */	mflr r0
/* 80091E7C 0008EA5C  90 01 00 04 */	stw r0, 4(r1)
/* 80091E80 0008EA60  94 21 FF A0 */	stwu r1, -0x60(r1)
/* 80091E84 0008EA64  DB E1 00 58 */	stfd f31, 0x58(r1)
/* 80091E88 0008EA68  FF E0 08 90 */	fmr f31, f1
/* 80091E8C 0008EA6C  93 E1 00 54 */	stw r31, 0x54(r1)
/* 80091E90 0008EA70  93 C1 00 50 */	stw r30, 0x50(r1)
/* 80091E94 0008EA74  7C 7E 1B 78 */	mr r30, r3
/* 80091E98 0008EA78  93 A1 00 4C */	stw r29, 0x4c(r1)
/* 80091E9C 0008EA7C  80 63 00 2C */	lwz r3, 0x2c(r3)
/* 80091EA0 0008EA80  88 03 22 18 */	lbz r0, 0x2218(r3)
/* 80091EA4 0008EA84  3B E3 00 00 */	addi r31, r3, 0
/* 80091EA8 0008EA88  54 00 E7 FF */	rlwinm. r0, r0, 0x1c, 0x1f, 0x1f
/* 80091EAC 0008EA8C  40 82 00 10 */	bne lbl_80091EBC
/* 80091EB0 0008EA90  88 1F 22 1B */	lbz r0, 0x221b(r31)
/* 80091EB4 0008EA94  54 00 CF FF */	rlwinm. r0, r0, 0x19, 0x1f, 0x1f
/* 80091EB8 0008EA98  41 82 02 80 */	beq lbl_80092138
lbl_80091EBC:
/* 80091EBC 0008EA9C  7F E3 FB 78 */	mr r3, r31
/* 80091EC0 0008EAA0  4B FF FD 05 */	bl func_80091BC4
/* 80091EC4 0008EAA4  C0 3F 23 44 */	lfs f1, 0x2344(r31)
/* 80091EC8 0008EAA8  C0 02 8B 58 */	lfs f0, lbl_804D8538(r2)
/* 80091ECC 0008EAAC  FC 01 00 00 */	fcmpu cr0, f1, f0
/* 80091ED0 0008EAB0  41 82 00 B0 */	beq lbl_80091F80
/* 80091ED4 0008EAB4  83 BF 08 AC */	lwz r29, 0x8ac(r31)
/* 80091ED8 0008EAB8  38 7F 00 00 */	addi r3, r31, 0
/* 80091EDC 0008EABC  38 80 00 26 */	li r4, 0x26
/* 80091EE0 0008EAC0  4B FF 3F 71 */	bl func_80085E50
/* 80091EE4 0008EAC4  38 A3 00 00 */	addi r5, r3, 0
/* 80091EE8 0008EAC8  38 7F 00 00 */	addi r3, r31, 0
/* 80091EEC 0008EACC  38 80 00 01 */	li r4, 1
/* 80091EF0 0008EAD0  4B FD D5 D9 */	bl func_8006F4C8
/* 80091EF4 0008EAD4  7F A3 EB 78 */	mr r3, r29
/* 80091EF8 0008EAD8  C0 3F 23 48 */	lfs f1, 0x2348(r31)
/* 80091EFC 0008EADC  4B FD E8 15 */	bl func_80070710
/* 80091F00 0008EAE0  80 BF 01 08 */	lwz r5, 0x108(r31)
/* 80091F04 0008EAE4  38 7F 00 00 */	addi r3, r31, 0
/* 80091F08 0008EAE8  38 80 00 01 */	li r4, 1
/* 80091F0C 0008EAEC  80 A5 00 08 */	lwz r5, 8(r5)
/* 80091F10 0008EAF0  4B FD DC 79 */	bl func_8006FB88
/* 80091F14 0008EAF4  7F A3 EB 78 */	mr r3, r29
/* 80091F18 0008EAF8  48 2D EA 11 */	bl HSD_JObjAnimAll
/* 80091F1C 0008EAFC  C0 5F 23 44 */	lfs f2, 0x2344(r31)
/* 80091F20 0008EB00  C0 02 8B 88 */	lfs f0, lbl_804D8568(r2)
/* 80091F24 0008EB04  FC 02 00 40 */	fcmpo cr0, f2, f0
/* 80091F28 0008EB08  40 80 00 24 */	bge lbl_80091F4C
/* 80091F2C 0008EB0C  80 9F 01 0C */	lwz r4, 0x10c(r31)
/* 80091F30 0008EB10  EC 20 10 28 */	fsubs f1, f0, f2
/* 80091F34 0008EB14  7F E3 FB 78 */	mr r3, r31
/* 80091F38 0008EB18  80 A4 00 20 */	lwz r5, 0x20(r4)
/* 80091F3C 0008EB1C  38 80 00 01 */	li r4, 1
/* 80091F40 0008EB20  80 A5 00 00 */	lwz r5, 0(r5)
/* 80091F44 0008EB24  80 A5 00 08 */	lwz r5, 8(r5)
/* 80091F48 0008EB28  4B FD E1 C1 */	bl func_80070108
lbl_80091F4C:
/* 80091F4C 0008EB2C  C0 02 8B 88 */	lfs f0, lbl_804D8568(r2)
/* 80091F50 0008EB30  FC 1F 00 40 */	fcmpo cr0, f31, f0
/* 80091F54 0008EB34  40 80 00 1C */	bge lbl_80091F70
/* 80091F58 0008EB38  FC 20 F8 90 */	fmr f1, f31
/* 80091F5C 0008EB3C  7F E3 FB 78 */	mr r3, r31
/* 80091F60 0008EB40  EC 40 F8 28 */	fsubs f2, f0, f31
/* 80091F64 0008EB44  38 80 00 01 */	li r4, 1
/* 80091F68 0008EB48  4B FD DF 35 */	bl func_8006FE9C
/* 80091F6C 0008EB4C  48 00 00 64 */	b lbl_80091FD0
lbl_80091F70:
/* 80091F70 0008EB50  38 7F 00 00 */	addi r3, r31, 0
/* 80091F74 0008EB54  38 80 00 01 */	li r4, 1
/* 80091F78 0008EB58  4B FD DF FD */	bl func_8006FF74
/* 80091F7C 0008EB5C  48 00 00 54 */	b lbl_80091FD0
lbl_80091F80:
/* 80091F80 0008EB60  C0 02 8B 88 */	lfs f0, lbl_804D8568(r2)
/* 80091F84 0008EB64  FC 1F 00 40 */	fcmpo cr0, f31, f0
/* 80091F88 0008EB68  40 80 00 2C */	bge lbl_80091FB4
/* 80091F8C 0008EB6C  80 9F 01 0C */	lwz r4, 0x10c(r31)
/* 80091F90 0008EB70  FC 20 F8 90 */	fmr f1, f31
/* 80091F94 0008EB74  EC 40 F8 28 */	fsubs f2, f0, f31
/* 80091F98 0008EB78  7F E3 FB 78 */	mr r3, r31
/* 80091F9C 0008EB7C  80 A4 00 20 */	lwz r5, 0x20(r4)
/* 80091FA0 0008EB80  38 80 00 01 */	li r4, 1
/* 80091FA4 0008EB84  80 A5 00 00 */	lwz r5, 0(r5)
/* 80091FA8 0008EB88  80 A5 00 08 */	lwz r5, 8(r5)
/* 80091FAC 0008EB8C  4B FD E0 65 */	bl func_80070010
/* 80091FB0 0008EB90  48 00 00 20 */	b lbl_80091FD0
lbl_80091FB4:
/* 80091FB4 0008EB94  80 BF 01 0C */	lwz r5, 0x10c(r31)
/* 80091FB8 0008EB98  38 7F 00 00 */	addi r3, r31, 0
/* 80091FBC 0008EB9C  38 80 00 01 */	li r4, 1
/* 80091FC0 0008EBA0  80 A5 00 20 */	lwz r5, 0x20(r5)
/* 80091FC4 0008EBA4  80 A5 00 00 */	lwz r5, 0(r5)
/* 80091FC8 0008EBA8  80 A5 00 08 */	lwz r5, 8(r5)
/* 80091FCC 0008EBAC  4B FD DA 8D */	bl func_8006FA58
lbl_80091FD0:
/* 80091FD0 0008EBB0  80 1F 00 04 */	lwz r0, 4(r31)
/* 80091FD4 0008EBB4  2C 00 00 0E */	cmpwi r0, 0xe
/* 80091FD8 0008EBB8  40 82 00 0C */	bne lbl_80091FE4
/* 80091FDC 0008EBBC  C0 1F 01 A0 */	lfs f0, 0x1a0(r31)
/* 80091FE0 0008EBC0  48 00 00 44 */	b lbl_80092024
lbl_80091FE4:
/* 80091FE4 0008EBC4  80 6D AE B4 */	lwz r3, p_ftCommonData(r13)
/* 80091FE8 0008EBC8  C0 3F 19 98 */	lfs f1, 0x1998(r31)
/* 80091FEC 0008EBCC  C0 03 02 60 */	lfs f0, 0x260(r3)
/* 80091FF0 0008EBD0  C0 A3 02 D4 */	lfs f5, 0x2d4(r3)
/* 80091FF4 0008EBD4  EC 61 00 24 */	fdivs f3, f1, f0
/* 80091FF8 0008EBD8  C0 03 02 D8 */	lfs f0, 0x2d8(r3)
/* 80091FFC 0008EBDC  C0 5F 19 9C */	lfs f2, 0x199c(r31)
/* 80092000 0008EBE0  C0 C3 02 64 */	lfs f6, 0x264(r3)
/* 80092004 0008EBE4  C0 82 8B 88 */	lfs f4, lbl_804D8568(r2)
/* 80092008 0008EBE8  EC 20 28 28 */	fsubs f1, f0, f5
/* 8009200C 0008EBEC  C0 1F 01 A0 */	lfs f0, 0x1a0(r31)
/* 80092010 0008EBF0  EC 84 30 28 */	fsubs f4, f4, f6
/* 80092014 0008EBF4  EC 22 28 7A */	fmadds f1, f2, f1, f5
/* 80092018 0008EBF8  EC 23 00 72 */	fmuls f1, f3, f1
/* 8009201C 0008EBFC  EC 24 30 7A */	fmadds f1, f4, f1, f6
/* 80092020 0008EC00  EC 01 00 32 */	fmuls f0, f1, f0
lbl_80092024:
/* 80092024 0008EC04  D0 01 00 2C */	stfs f0, 0x2c(r1)
/* 80092028 0008EC08  D0 01 00 28 */	stfs f0, 0x28(r1)
/* 8009202C 0008EC0C  D0 01 00 24 */	stfs f0, 0x24(r1)
/* 80092030 0008EC10  80 7F 01 0C */	lwz r3, 0x10c(r31)
/* 80092034 0008EC14  80 9F 05 E8 */	lwz r4, 0x5e8(r31)
/* 80092038 0008EC18  80 63 00 08 */	lwz r3, 8(r3)
/* 8009203C 0008EC1C  88 03 00 11 */	lbz r0, 0x11(r3)
/* 80092040 0008EC20  54 00 20 36 */	slwi r0, r0, 4
/* 80092044 0008EC24  7F E4 00 2E */	lwzx r31, r4, r0
/* 80092048 0008EC28  28 1F 00 00 */	cmplwi r31, 0
/* 8009204C 0008EC2C  40 82 00 14 */	bne lbl_80092060
/* 80092050 0008EC30  38 6D 84 58 */	addi r3, r13, lbl_804D3AF8
/* 80092054 0008EC34  38 80 02 F8 */	li r4, 0x2f8
/* 80092058 0008EC38  38 AD 84 60 */	addi r5, r13, lbl_804D3B00
/* 8009205C 0008EC3C  48 2F 61 C5 */	bl __assert
lbl_80092060:
/* 80092060 0008EC40  80 61 00 24 */	lwz r3, 0x24(r1)
/* 80092064 0008EC44  80 01 00 28 */	lwz r0, 0x28(r1)
/* 80092068 0008EC48  90 7F 00 2C */	stw r3, 0x2c(r31)
/* 8009206C 0008EC4C  90 1F 00 30 */	stw r0, 0x30(r31)
/* 80092070 0008EC50  80 01 00 2C */	lwz r0, 0x2c(r1)
/* 80092074 0008EC54  90 1F 00 34 */	stw r0, 0x34(r31)
/* 80092078 0008EC58  80 1F 00 14 */	lwz r0, 0x14(r31)
/* 8009207C 0008EC5C  54 00 01 8D */	rlwinm. r0, r0, 0, 6, 6
/* 80092080 0008EC60  40 82 00 4C */	bne lbl_800920CC
/* 80092084 0008EC64  28 1F 00 00 */	cmplwi r31, 0
/* 80092088 0008EC68  41 82 00 44 */	beq lbl_800920CC
/* 8009208C 0008EC6C  40 82 00 14 */	bne lbl_800920A0
/* 80092090 0008EC70  38 6D 84 58 */	addi r3, r13, lbl_804D3AF8
/* 80092094 0008EC74  38 80 02 34 */	li r4, 0x234
/* 80092098 0008EC78  38 AD 84 60 */	addi r5, r13, lbl_804D3B00
/* 8009209C 0008EC7C  48 2F 61 85 */	bl __assert
lbl_800920A0:
/* 800920A0 0008EC80  80 9F 00 14 */	lwz r4, 0x14(r31)
/* 800920A4 0008EC84  38 60 00 00 */	li r3, 0
/* 800920A8 0008EC88  54 80 02 11 */	rlwinm. r0, r4, 0, 8, 8
/* 800920AC 0008EC8C  40 82 00 10 */	bne lbl_800920BC
/* 800920B0 0008EC90  54 80 06 73 */	rlwinm. r0, r4, 0, 0x19, 0x19
/* 800920B4 0008EC94  41 82 00 08 */	beq lbl_800920BC
/* 800920B8 0008EC98  38 60 00 01 */	li r3, 1
lbl_800920BC:
/* 800920BC 0008EC9C  2C 03 00 00 */	cmpwi r3, 0
/* 800920C0 0008ECA0  40 82 00 0C */	bne lbl_800920CC
/* 800920C4 0008ECA4  7F E3 FB 78 */	mr r3, r31
/* 800920C8 0008ECA8  48 2E 12 21 */	bl HSD_JObjSetMtxDirtySub
lbl_800920CC:
/* 800920CC 0008ECAC  80 BE 00 2C */	lwz r5, 0x2c(r30)
/* 800920D0 0008ECB0  80 05 00 04 */	lwz r0, 4(r5)
/* 800920D4 0008ECB4  2C 00 00 0E */	cmpwi r0, 0xe
/* 800920D8 0008ECB8  41 82 00 60 */	beq lbl_80092138
/* 800920DC 0008ECBC  80 8D AE B4 */	lwz r4, p_ftCommonData(r13)
/* 800920E0 0008ECC0  3C 00 43 30 */	lis r0, 0x4330
/* 800920E4 0008ECC4  C0 02 8B 8C */	lfs f0, lbl_804D856C(r2)
/* 800920E8 0008ECC8  7F C3 F3 78 */	mr r3, r30
/* 800920EC 0008ECCC  C0 64 02 F4 */	lfs f3, 0x2f4(r4)
/* 800920F0 0008ECD0  C0 45 19 9C */	lfs f2, 0x199c(r5)
/* 800920F4 0008ECD4  EC 00 18 28 */	fsubs f0, f0, f3
/* 800920F8 0008ECD8  C8 22 8B 90 */	lfd f1, lbl_804D8570(r2)
/* 800920FC 0008ECDC  EC 02 00 32 */	fmuls f0, f2, f0
/* 80092100 0008ECE0  FC 00 00 1E */	fctiwz f0, f0
/* 80092104 0008ECE4  D8 01 00 40 */	stfd f0, 0x40(r1)
/* 80092108 0008ECE8  80 81 00 44 */	lwz r4, 0x44(r1)
/* 8009210C 0008ECEC  6C 84 80 00 */	xoris r4, r4, 0x8000
/* 80092110 0008ECF0  90 81 00 3C */	stw r4, 0x3c(r1)
/* 80092114 0008ECF4  90 01 00 38 */	stw r0, 0x38(r1)
/* 80092118 0008ECF8  C8 01 00 38 */	lfd f0, 0x38(r1)
/* 8009211C 0008ECFC  EC 00 08 28 */	fsubs f0, f0, f1
/* 80092120 0008ED00  EC 03 00 2A */	fadds f0, f3, f0
/* 80092124 0008ED04  FC 00 00 1E */	fctiwz f0, f0
/* 80092128 0008ED08  D8 01 00 30 */	stfd f0, 0x30(r1)
/* 8009212C 0008ED0C  80 01 00 34 */	lwz r0, 0x34(r1)
/* 80092130 0008ED10  54 04 06 3E */	clrlwi r4, r0, 0x18
/* 80092134 0008ED14  4B FC D7 31 */	bl func_8005F864
lbl_80092138:
/* 80092138 0008ED18  80 01 00 64 */	lwz r0, 0x64(r1)
/* 8009213C 0008ED1C  CB E1 00 58 */	lfd f31, 0x58(r1)
/* 80092140 0008ED20  83 E1 00 54 */	lwz r31, 0x54(r1)
/* 80092144 0008ED24  83 C1 00 50 */	lwz r30, 0x50(r1)
/* 80092148 0008ED28  83 A1 00 4C */	lwz r29, 0x4c(r1)
/* 8009214C 0008ED2C  38 21 00 60 */	addi r1, r1, 0x60
/* 80092150 0008ED30  7C 08 03 A6 */	mtlr r0
/* 80092154 0008ED34  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

#pragma push
asm unk_t func_80092158()
{ // clang-format off
    nofralloc
/* 80092158 0008ED38  7C 08 02 A6 */	mflr r0
/* 8009215C 0008ED3C  90 01 00 04 */	stw r0, 4(r1)
/* 80092160 0008ED40  94 21 FF D8 */	stwu r1, -0x28(r1)
/* 80092164 0008ED44  93 E1 00 24 */	stw r31, 0x24(r1)
/* 80092168 0008ED48  3B E5 00 00 */	addi r31, r5, 0
/* 8009216C 0008ED4C  93 C1 00 20 */	stw r30, 0x20(r1)
/* 80092170 0008ED50  3B C4 00 00 */	addi r30, r4, 0
/* 80092174 0008ED54  93 A1 00 1C */	stw r29, 0x1c(r1)
/* 80092178 0008ED58  7C 7D 1B 78 */	mr r29, r3
/* 8009217C 0008ED5C  80 63 00 2C */	lwz r3, 0x2c(r3)
/* 80092180 0008ED60  88 63 00 0C */	lbz r3, 0xc(r3)
/* 80092184 0008ED64  4B FA 43 B5 */	bl Player_GetUnk45
/* 80092188 0008ED68  80 0D AE 6C */	lwz r0, lbl_804D650C(r13)
/* 8009218C 0008ED6C  54 64 10 3A */	slwi r4, r3, 2
/* 80092190 0008ED70  38 7E 00 00 */	addi r3, r30, 0
/* 80092194 0008ED74  4C C6 31 82 */	crclr 6
/* 80092198 0008ED78  7C E0 22 14 */	add r7, r0, r4
/* 8009219C 0008ED7C  88 07 00 01 */	lbz r0, 1(r7)
/* 800921A0 0008ED80  7F A4 EB 78 */	mr r4, r29
/* 800921A4 0008ED84  88 C7 00 00 */	lbz r6, 0(r7)
/* 800921A8 0008ED88  38 BF 00 00 */	addi r5, r31, 0
/* 800921AC 0008ED8C  54 00 40 2E */	slwi r0, r0, 8
/* 800921B0 0008ED90  88 E7 00 02 */	lbz r7, 2(r7)
/* 800921B4 0008ED94  50 C0 82 1E */	rlwimi r0, r6, 0x10, 8, 0xf
/* 800921B8 0008ED98  7C E6 03 78 */	or r6, r7, r0
/* 800921BC 0008ED9C  4B FC DC 21 */	bl ef_Spawn
/* 800921C0 0008EDA0  80 01 00 2C */	lwz r0, 0x2c(r1)
/* 800921C4 0008EDA4  83 E1 00 24 */	lwz r31, 0x24(r1)
/* 800921C8 0008EDA8  83 C1 00 20 */	lwz r30, 0x20(r1)
/* 800921CC 0008EDAC  83 A1 00 1C */	lwz r29, 0x1c(r1)
/* 800921D0 0008EDB0  38 21 00 28 */	addi r1, r1, 0x28
/* 800921D4 0008EDB4  7C 08 03 A6 */	mtlr r0
/* 800921D8 0008EDB8  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

#pragma push
asm unk_t func_800921DC()
{ // clang-format off
    nofralloc
/* 800921DC 0008EDBC  7C 08 02 A6 */	mflr r0
/* 800921E0 0008EDC0  90 01 00 04 */	stw r0, 4(r1)
/* 800921E4 0008EDC4  94 21 FF C8 */	stwu r1, -0x38(r1)
/* 800921E8 0008EDC8  93 E1 00 34 */	stw r31, 0x34(r1)
/* 800921EC 0008EDCC  93 C1 00 30 */	stw r30, 0x30(r1)
/* 800921F0 0008EDD0  7C 7E 1B 78 */	mr r30, r3
/* 800921F4 0008EDD4  93 A1 00 2C */	stw r29, 0x2c(r1)
/* 800921F8 0008EDD8  80 63 00 2C */	lwz r3, 0x2c(r3)
/* 800921FC 0008EDDC  7C 7F 1B 78 */	mr r31, r3
/* 80092200 0008EDE0  88 63 00 0C */	lbz r3, 0xc(r3)
/* 80092204 0008EDE4  80 9F 01 0C */	lwz r4, 0x10c(r31)
/* 80092208 0008EDE8  80 BF 05 E8 */	lwz r5, 0x5e8(r31)
/* 8009220C 0008EDEC  80 84 00 08 */	lwz r4, 8(r4)
/* 80092210 0008EDF0  88 04 00 11 */	lbz r0, 0x11(r4)
/* 80092214 0008EDF4  54 00 20 36 */	slwi r0, r0, 4
/* 80092218 0008EDF8  7F A5 00 2E */	lwzx r29, r5, r0
/* 8009221C 0008EDFC  4B FA 43 1D */	bl Player_GetUnk45
/* 80092220 0008EE00  80 0D AE 6C */	lwz r0, lbl_804D650C(r13)
/* 80092224 0008EE04  54 63 10 3A */	slwi r3, r3, 2
/* 80092228 0008EE08  38 9E 00 00 */	addi r4, r30, 0
/* 8009222C 0008EE0C  4C C6 31 82 */	crclr 6
/* 80092230 0008EE10  7C E0 1A 14 */	add r7, r0, r3
/* 80092234 0008EE14  88 07 00 01 */	lbz r0, 1(r7)
/* 80092238 0008EE18  7F A5 EB 78 */	mr r5, r29
/* 8009223C 0008EE1C  88 C7 00 00 */	lbz r6, 0(r7)
/* 80092240 0008EE20  38 60 04 17 */	li r3, 0x417
/* 80092244 0008EE24  54 00 40 2E */	slwi r0, r0, 8
/* 80092248 0008EE28  88 E7 00 02 */	lbz r7, 2(r7)
/* 8009224C 0008EE2C  50 C0 82 1E */	rlwimi r0, r6, 0x10, 8, 0xf
/* 80092250 0008EE30  7C E6 03 78 */	or r6, r7, r0
/* 80092254 0008EE34  4B FC DB 89 */	bl ef_Spawn
/* 80092258 0008EE38  88 1F 22 19 */	lbz r0, 0x2219(r31)
/* 8009225C 0008EE3C  38 60 00 01 */	li r3, 1
/* 80092260 0008EE40  50 60 3E 30 */	rlwimi r0, r3, 7, 0x18, 0x18
/* 80092264 0008EE44  98 1F 22 19 */	stb r0, 0x2219(r31)
/* 80092268 0008EE48  38 00 00 00 */	li r0, 0
/* 8009226C 0008EE4C  90 1F 23 4C */	stw r0, 0x234c(r31)
/* 80092270 0008EE50  C0 42 8B 58 */	lfs f2, lbl_804D8538(r2)
/* 80092274 0008EE54  D0 5F 23 40 */	stfs f2, 0x2340(r31)
/* 80092278 0008EE58  80 6D AE B4 */	lwz r3, p_ftCommonData(r13)
/* 8009227C 0008EE5C  C0 03 02 68 */	lfs f0, 0x268(r3)
/* 80092280 0008EE60  D0 1F 23 50 */	stfs f0, 0x2350(r31)
/* 80092284 0008EE64  C0 02 8B 68 */	lfs f0, lbl_804D8548(r2)
/* 80092288 0008EE68  D0 1F 23 48 */	stfs f0, 0x2348(r31)
/* 8009228C 0008EE6C  D0 5F 23 44 */	stfs f2, 0x2344(r31)
/* 80092290 0008EE70  D0 5F 23 6C */	stfs f2, 0x236c(r31)
/* 80092294 0008EE74  80 6D AE B4 */	lwz r3, p_ftCommonData(r13)
/* 80092298 0008EE78  C0 3F 06 50 */	lfs f1, 0x650(r31)
/* 8009229C 0008EE7C  C0 63 00 10 */	lfs f3, 0x10(r3)
/* 800922A0 0008EE80  C0 02 8B 88 */	lfs f0, lbl_804D8568(r2)
/* 800922A4 0008EE84  EC 21 18 28 */	fsubs f1, f1, f3
/* 800922A8 0008EE88  EC 00 18 28 */	fsubs f0, f0, f3
/* 800922AC 0008EE8C  EC 01 00 24 */	fdivs f0, f1, f0
/* 800922B0 0008EE90  FC 00 10 40 */	fcmpo cr0, f0, f2
/* 800922B4 0008EE94  40 80 00 08 */	bge lbl_800922BC
/* 800922B8 0008EE98  C0 1F 23 6C */	lfs f0, 0x236c(r31)
lbl_800922BC:
/* 800922BC 0008EE9C  D0 1F 19 9C */	stfs f0, 0x199c(r31)
/* 800922C0 0008EEA0  38 00 00 00 */	li r0, 0
/* 800922C4 0008EEA4  90 1F 23 64 */	stw r0, 0x2364(r31)
/* 800922C8 0008EEA8  90 1F 23 60 */	stw r0, 0x2360(r31)
/* 800922CC 0008EEAC  C0 02 8B 58 */	lfs f0, lbl_804D8538(r2)
/* 800922D0 0008EEB0  D0 01 00 20 */	stfs f0, 0x20(r1)
/* 800922D4 0008EEB4  D0 01 00 1C */	stfs f0, 0x1c(r1)
/* 800922D8 0008EEB8  D0 01 00 18 */	stfs f0, 0x18(r1)
/* 800922DC 0008EEBC  80 7F 01 0C */	lwz r3, 0x10c(r31)
/* 800922E0 0008EEC0  80 9F 05 E8 */	lwz r4, 0x5e8(r31)
/* 800922E4 0008EEC4  80 63 00 08 */	lwz r3, 8(r3)
/* 800922E8 0008EEC8  88 03 00 11 */	lbz r0, 0x11(r3)
/* 800922EC 0008EECC  54 00 20 36 */	slwi r0, r0, 4
/* 800922F0 0008EED0  7F A4 00 2E */	lwzx r29, r4, r0
/* 800922F4 0008EED4  28 1D 00 00 */	cmplwi r29, 0
/* 800922F8 0008EED8  40 82 00 14 */	bne lbl_8009230C
/* 800922FC 0008EEDC  38 6D 84 58 */	addi r3, r13, lbl_804D3AF8
/* 80092300 0008EEE0  38 80 03 94 */	li r4, 0x394
/* 80092304 0008EEE4  38 AD 84 60 */	addi r5, r13, lbl_804D3B00
/* 80092308 0008EEE8  48 2F 5F 19 */	bl __assert
lbl_8009230C:
/* 8009230C 0008EEEC  80 61 00 18 */	lwz r3, 0x18(r1)
/* 80092310 0008EEF0  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 80092314 0008EEF4  90 7D 00 38 */	stw r3, 0x38(r29)
/* 80092318 0008EEF8  90 1D 00 3C */	stw r0, 0x3c(r29)
/* 8009231C 0008EEFC  80 01 00 20 */	lwz r0, 0x20(r1)
/* 80092320 0008EF00  90 1D 00 40 */	stw r0, 0x40(r29)
/* 80092324 0008EF04  80 1D 00 14 */	lwz r0, 0x14(r29)
/* 80092328 0008EF08  54 00 01 8D */	rlwinm. r0, r0, 0, 6, 6
/* 8009232C 0008EF0C  40 82 00 4C */	bne lbl_80092378
/* 80092330 0008EF10  28 1D 00 00 */	cmplwi r29, 0
/* 80092334 0008EF14  41 82 00 44 */	beq lbl_80092378
/* 80092338 0008EF18  40 82 00 14 */	bne lbl_8009234C
/* 8009233C 0008EF1C  38 6D 84 58 */	addi r3, r13, lbl_804D3AF8
/* 80092340 0008EF20  38 80 02 34 */	li r4, 0x234
/* 80092344 0008EF24  38 AD 84 60 */	addi r5, r13, lbl_804D3B00
/* 80092348 0008EF28  48 2F 5E D9 */	bl __assert
lbl_8009234C:
/* 8009234C 0008EF2C  80 9D 00 14 */	lwz r4, 0x14(r29)
/* 80092350 0008EF30  38 60 00 00 */	li r3, 0
/* 80092354 0008EF34  54 80 02 11 */	rlwinm. r0, r4, 0, 8, 8
/* 80092358 0008EF38  40 82 00 10 */	bne lbl_80092368
/* 8009235C 0008EF3C  54 80 06 73 */	rlwinm. r0, r4, 0, 0x19, 0x19
/* 80092360 0008EF40  41 82 00 08 */	beq lbl_80092368
/* 80092364 0008EF44  38 60 00 01 */	li r3, 1
lbl_80092368:
/* 80092368 0008EF48  2C 03 00 00 */	cmpwi r3, 0
/* 8009236C 0008EF4C  40 82 00 0C */	bne lbl_80092378
/* 80092370 0008EF50  7F A3 EB 78 */	mr r3, r29
/* 80092374 0008EF54  48 2E 0F 75 */	bl HSD_JObjSetMtxDirtySub
lbl_80092378:
/* 80092378 0008EF58  7F C3 F3 78 */	mr r3, r30
/* 8009237C 0008EF5C  C0 22 8B 58 */	lfs f1, lbl_804D8538(r2)
/* 80092380 0008EF60  4B FF FA F9 */	bl func_80091E78
/* 80092384 0008EF64  38 7F 00 00 */	addi r3, r31, 0
/* 80092388 0008EF68  38 80 00 6E */	li r4, 0x6e
/* 8009238C 0008EF6C  38 A0 00 7F */	li r5, 0x7f
/* 80092390 0008EF70  38 C0 00 40 */	li r6, 0x40
/* 80092394 0008EF74  4B FF 5D B5 */	bl func_80088148
/* 80092398 0008EF78  80 01 00 3C */	lwz r0, 0x3c(r1)
/* 8009239C 0008EF7C  83 E1 00 34 */	lwz r31, 0x34(r1)
/* 800923A0 0008EF80  83 C1 00 30 */	lwz r30, 0x30(r1)
/* 800923A4 0008EF84  83 A1 00 2C */	lwz r29, 0x2c(r1)
/* 800923A8 0008EF88  38 21 00 38 */	addi r1, r1, 0x38
/* 800923AC 0008EF8C  7C 08 03 A6 */	mtlr r0
/* 800923B0 0008EF90  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

extern unk_t func_800924C0();

#pragma push
asm unk_t func_800923B4()
{ // clang-format off
    nofralloc
/* 800923B4 0008EF94  7C 08 02 A6 */	mflr r0
/* 800923B8 0008EF98  90 01 00 04 */	stw r0, 4(r1)
/* 800923BC 0008EF9C  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 800923C0 0008EFA0  93 E1 00 14 */	stw r31, 0x14(r1)
/* 800923C4 0008EFA4  93 C1 00 10 */	stw r30, 0x10(r1)
/* 800923C8 0008EFA8  7C 7E 1B 78 */	mr r30, r3
/* 800923CC 0008EFAC  80 63 00 2C */	lwz r3, 0x2c(r3)
/* 800923D0 0008EFB0  80 03 00 04 */	lwz r0, 4(r3)
/* 800923D4 0008EFB4  3B E3 00 00 */	addi r31, r3, 0
/* 800923D8 0008EFB8  2C 00 00 12 */	cmpwi r0, 0x12
/* 800923DC 0008EFBC  41 82 00 20 */	beq lbl_800923FC
/* 800923E0 0008EFC0  40 80 00 50 */	bge lbl_80092430
/* 800923E4 0008EFC4  2C 00 00 0E */	cmpwi r0, 0xe
/* 800923E8 0008EFC8  41 82 00 08 */	beq lbl_800923F0
/* 800923EC 0008EFCC  48 00 00 44 */	b lbl_80092430
lbl_800923F0:
/* 800923F0 0008EFD0  7F C3 F3 78 */	mr r3, r30
/* 800923F4 0008EFD4  48 09 9A D9 */	bl func_8012BECC
/* 800923F8 0008EFD8  48 00 00 40 */	b lbl_80092438
lbl_800923FC:
/* 800923FC 0008EFDC  7F C3 F3 78 */	mr r3, r30
/* 80092400 0008EFE0  48 00 00 C1 */	bl func_800924C0
/* 80092404 0008EFE4  38 7E 00 00 */	addi r3, r30, 0
/* 80092408 0008EFE8  38 80 00 01 */	li r4, 1
/* 8009240C 0008EFEC  38 A0 00 01 */	li r5, 1
/* 80092410 0008EFF0  4B FE 26 FD */	bl func_80074B0C
/* 80092414 0008EFF4  3C 80 00 03 */	lis r4, 0x0002E6A3@ha
/* 80092418 0008EFF8  38 7F 00 00 */	addi r3, r31, 0
/* 8009241C 0008EFFC  38 84 E6 A3 */	addi r4, r4, 0x0002E6A3@l
/* 80092420 0008F000  38 A0 00 7F */	li r5, 0x7f
/* 80092424 0008F004  38 C0 00 40 */	li r6, 0x40
/* 80092428 0008F008  4B FF 5D 21 */	bl func_80088148
/* 8009242C 0008F00C  48 00 00 0C */	b lbl_80092438
lbl_80092430:
/* 80092430 0008F010  7F C3 F3 78 */	mr r3, r30
/* 80092434 0008F014  48 00 00 8D */	bl func_800924C0
lbl_80092438:
/* 80092438 0008F018  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 8009243C 0008F01C  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 80092440 0008F020  83 C1 00 10 */	lwz r30, 0x10(r1)
/* 80092444 0008F024  38 21 00 18 */	addi r1, r1, 0x18
/* 80092448 0008F028  7C 08 03 A6 */	mtlr r0
/* 8009244C 0008F02C  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

extern unk_t lbl_80092E50();

#pragma push
asm unk_t func_80092450()
{ // clang-format off
    nofralloc
/* 80092450 0008F030  7C 08 02 A6 */	mflr r0
/* 80092454 0008F034  3C 80 80 09 */	lis r4, lbl_80092E50@ha
/* 80092458 0008F038  90 01 00 04 */	stw r0, 4(r1)
/* 8009245C 0008F03C  38 A4 2E 50 */	addi r5, r4, lbl_80092E50@l
/* 80092460 0008F040  94 21 FF D0 */	stwu r1, -0x30(r1)
/* 80092464 0008F044  93 E1 00 2C */	stw r31, 0x2c(r1)
/* 80092468 0008F048  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 8009246C 0008F04C  C0 22 8B 88 */	lfs f1, lbl_804D8568(r2)
/* 80092470 0008F050  80 9F 01 0C */	lwz r4, 0x10c(r31)
/* 80092474 0008F054  C0 02 8B 58 */	lfs f0, lbl_804D8538(r2)
/* 80092478 0008F058  80 C4 00 08 */	lwz r6, 8(r4)
/* 8009247C 0008F05C  38 81 00 10 */	addi r4, r1, 0x10
/* 80092480 0008F060  88 06 00 11 */	lbz r0, 0x11(r6)
/* 80092484 0008F064  90 01 00 10 */	stw r0, 0x10(r1)
/* 80092488 0008F068  D0 21 00 20 */	stfs f1, 0x20(r1)
/* 8009248C 0008F06C  D0 01 00 1C */	stfs f0, 0x1c(r1)
/* 80092490 0008F070  D0 01 00 18 */	stfs f0, 0x18(r1)
/* 80092494 0008F074  D0 01 00 14 */	stfs f0, 0x14(r1)
/* 80092498 0008F078  4B FE 8D 21 */	bl func_8007B1B8
/* 8009249C 0008F07C  88 1F 22 1A */	lbz r0, 0x221a(r31)
/* 800924A0 0008F080  38 60 00 01 */	li r3, 1
/* 800924A4 0008F084  50 60 07 FE */	rlwimi r0, r3, 0, 0x1f, 0x1f
/* 800924A8 0008F088  98 1F 22 1A */	stb r0, 0x221a(r31)
/* 800924AC 0008F08C  80 01 00 34 */	lwz r0, 0x34(r1)
/* 800924B0 0008F090  83 E1 00 2C */	lwz r31, 0x2c(r1)
/* 800924B4 0008F094  38 21 00 30 */	addi r1, r1, 0x30
/* 800924B8 0008F098  7C 08 03 A6 */	mtlr r0
/* 800924BC 0008F09C  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

#pragma push
asm unk_t func_800924C0()
{ // clang-format off
    nofralloc
/* 800924C0 0008F0A0  7C 08 02 A6 */	mflr r0
/* 800924C4 0008F0A4  38 80 00 B2 */	li r4, 0xb2
/* 800924C8 0008F0A8  90 01 00 04 */	stw r0, 4(r1)
/* 800924CC 0008F0AC  3C A0 20 00 */	lis r5, 0x2000
/* 800924D0 0008F0B0  38 C0 00 00 */	li r6, 0
/* 800924D4 0008F0B4  94 21 FF D0 */	stwu r1, -0x30(r1)
/* 800924D8 0008F0B8  93 E1 00 2C */	stw r31, 0x2c(r1)
/* 800924DC 0008F0BC  93 C1 00 28 */	stw r30, 0x28(r1)
/* 800924E0 0008F0C0  7C 7E 1B 78 */	mr r30, r3
/* 800924E4 0008F0C4  C0 22 8B 58 */	lfs f1, lbl_804D8538(r2)
/* 800924E8 0008F0C8  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 800924EC 0008F0CC  FC 60 08 90 */	fmr f3, f1
/* 800924F0 0008F0D0  C0 42 8B 88 */	lfs f2, lbl_804D8568(r2)
/* 800924F4 0008F0D4  4B FD 6E B9 */	bl Fighter_ActionStateChange_800693AC
/* 800924F8 0008F0D8  7F C3 F3 78 */	mr r3, r30
/* 800924FC 0008F0DC  4B FD C6 A9 */	bl func_8006EBA4
/* 80092500 0008F0E0  88 1F 22 1C */	lbz r0, 0x221c(r31)
/* 80092504 0008F0E4  38 C0 00 00 */	li r6, 0
/* 80092508 0008F0E8  50 C0 26 F6 */	rlwimi r0, r6, 4, 0x1b, 0x1b
/* 8009250C 0008F0EC  98 1F 22 1C */	stb r0, 0x221c(r31)
/* 80092510 0008F0F0  3C 60 80 09 */	lis r3, lbl_80092E50@ha
/* 80092514 0008F0F4  38 A3 2E 50 */	addi r5, r3, lbl_80092E50@l
/* 80092518 0008F0F8  88 1F 22 1C */	lbz r0, 0x221c(r31)
/* 8009251C 0008F0FC  50 C0 36 72 */	rlwimi r0, r6, 6, 0x19, 0x19
/* 80092520 0008F100  38 7E 00 00 */	addi r3, r30, 0
/* 80092524 0008F104  98 1F 22 1C */	stb r0, 0x221c(r31)
/* 80092528 0008F108  38 81 00 14 */	addi r4, r1, 0x14
/* 8009252C 0008F10C  88 1F 22 1C */	lbz r0, 0x221c(r31)
/* 80092530 0008F110  50 C0 2E B4 */	rlwimi r0, r6, 5, 0x1a, 0x1a
/* 80092534 0008F114  98 1F 22 1C */	stb r0, 0x221c(r31)
/* 80092538 0008F118  90 DF 23 5C */	stw r6, 0x235c(r31)
/* 8009253C 0008F11C  C0 22 8B 58 */	lfs f1, lbl_804D8538(r2)
/* 80092540 0008F120  D0 3F 23 54 */	stfs f1, 0x2354(r31)
/* 80092544 0008F124  D0 3F 23 58 */	stfs f1, 0x2358(r31)
/* 80092548 0008F128  83 FE 00 2C */	lwz r31, 0x2c(r30)
/* 8009254C 0008F12C  C0 02 8B 88 */	lfs f0, lbl_804D8568(r2)
/* 80092550 0008F130  80 DF 01 0C */	lwz r6, 0x10c(r31)
/* 80092554 0008F134  80 C6 00 08 */	lwz r6, 8(r6)
/* 80092558 0008F138  88 06 00 11 */	lbz r0, 0x11(r6)
/* 8009255C 0008F13C  90 01 00 14 */	stw r0, 0x14(r1)
/* 80092560 0008F140  D0 01 00 24 */	stfs f0, 0x24(r1)
/* 80092564 0008F144  D0 21 00 20 */	stfs f1, 0x20(r1)
/* 80092568 0008F148  D0 21 00 1C */	stfs f1, 0x1c(r1)
/* 8009256C 0008F14C  D0 21 00 18 */	stfs f1, 0x18(r1)
/* 80092570 0008F150  4B FE 8C 49 */	bl func_8007B1B8
/* 80092574 0008F154  88 1F 22 1A */	lbz r0, 0x221a(r31)
/* 80092578 0008F158  38 60 00 01 */	li r3, 1
/* 8009257C 0008F15C  50 60 07 FE */	rlwimi r0, r3, 0, 0x1f, 0x1f
/* 80092580 0008F160  98 1F 22 1A */	stb r0, 0x221a(r31)
/* 80092584 0008F164  7F C3 F3 78 */	mr r3, r30
/* 80092588 0008F168  4B FF FC 55 */	bl func_800921DC
/* 8009258C 0008F16C  80 01 00 34 */	lwz r0, 0x34(r1)
/* 80092590 0008F170  83 E1 00 2C */	lwz r31, 0x2c(r1)
/* 80092594 0008F174  83 C1 00 28 */	lwz r30, 0x28(r1)
/* 80092598 0008F178  38 21 00 30 */	addi r1, r1, 0x30
/* 8009259C 0008F17C  7C 08 03 A6 */	mtlr r0
/* 800925A0 0008F180  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

extern unk_t func_8003E0E8();

#pragma push
asm unk_t func_800925A4()
{ // clang-format off
    nofralloc
/* 800925A4 0008F184  7C 08 02 A6 */	mflr r0
/* 800925A8 0008F188  90 01 00 04 */	stw r0, 4(r1)
/* 800925AC 0008F18C  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 800925B0 0008F190  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 800925B4 0008F194  93 C1 00 18 */	stw r30, 0x18(r1)
/* 800925B8 0008F198  7C 7E 1B 78 */	mr r30, r3
/* 800925BC 0008F19C  80 63 00 2C */	lwz r3, 0x2c(r3)
/* 800925C0 0008F1A0  88 03 22 1B */	lbz r0, 0x221b(r3)
/* 800925C4 0008F1A4  3B E3 00 00 */	addi r31, r3, 0
/* 800925C8 0008F1A8  54 00 CF FF */	rlwinm. r0, r0, 0x19, 0x1f, 0x1f
/* 800925CC 0008F1AC  41 82 00 F4 */	beq lbl_800926C0
/* 800925D0 0008F1B0  C0 1F 19 9C */	lfs f0, 0x199c(r31)
/* 800925D4 0008F1B4  D0 1F 23 6C */	stfs f0, 0x236c(r31)
/* 800925D8 0008F1B8  80 6D AE B4 */	lwz r3, p_ftCommonData(r13)
/* 800925DC 0008F1BC  C0 1F 06 50 */	lfs f0, 0x650(r31)
/* 800925E0 0008F1C0  C0 63 00 10 */	lfs f3, 0x10(r3)
/* 800925E4 0008F1C4  C0 22 8B 88 */	lfs f1, lbl_804D8568(r2)
/* 800925E8 0008F1C8  EC 40 18 28 */	fsubs f2, f0, f3
/* 800925EC 0008F1CC  C0 02 8B 58 */	lfs f0, lbl_804D8538(r2)
/* 800925F0 0008F1D0  EC 21 18 28 */	fsubs f1, f1, f3
/* 800925F4 0008F1D4  EC 22 08 24 */	fdivs f1, f2, f1
/* 800925F8 0008F1D8  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 800925FC 0008F1DC  40 80 00 08 */	bge lbl_80092604
/* 80092600 0008F1E0  C0 3F 23 6C */	lfs f1, 0x236c(r31)
lbl_80092604:
/* 80092604 0008F1E4  D0 3F 19 9C */	stfs f1, 0x199c(r31)
/* 80092608 0008F1E8  80 6D AE B4 */	lwz r3, p_ftCommonData(r13)
/* 8009260C 0008F1EC  C0 3F 19 9C */	lfs f1, 0x199c(r31)
/* 80092610 0008F1F0  C0 83 02 EC */	lfs f4, 0x2ec(r3)
/* 80092614 0008F1F4  C0 03 02 F0 */	lfs f0, 0x2f0(r3)
/* 80092618 0008F1F8  C0 43 02 78 */	lfs f2, 0x278(r3)
/* 8009261C 0008F1FC  EC 00 20 28 */	fsubs f0, f0, f4
/* 80092620 0008F200  C0 7F 19 98 */	lfs f3, 0x1998(r31)
/* 80092624 0008F204  EC 01 20 3A */	fmadds f0, f1, f0, f4
/* 80092628 0008F208  EC 02 00 32 */	fmuls f0, f2, f0
/* 8009262C 0008F20C  EC 03 00 28 */	fsubs f0, f3, f0
/* 80092630 0008F210  D0 1F 19 98 */	stfs f0, 0x1998(r31)
/* 80092634 0008F214  C0 1F 19 98 */	lfs f0, 0x1998(r31)
/* 80092638 0008F218  C0 42 8B 58 */	lfs f2, lbl_804D8538(r2)
/* 8009263C 0008F21C  FC 00 10 40 */	fcmpo cr0, f0, f2
/* 80092640 0008F220  40 80 00 58 */	bge lbl_80092698
/* 80092644 0008F224  D0 5F 19 98 */	stfs f2, 0x1998(r31)
/* 80092648 0008F228  38 60 00 00 */	li r3, 0
/* 8009264C 0008F22C  88 1F 22 1A */	lbz r0, 0x221a(r31)
/* 80092650 0008F230  50 60 07 FE */	rlwimi r0, r3, 0, 0x1f, 0x1f
/* 80092654 0008F234  98 1F 22 1A */	stb r0, 0x221a(r31)
/* 80092658 0008F238  88 1F 22 1B */	lbz r0, 0x221b(r31)
/* 8009265C 0008F23C  50 60 3E 30 */	rlwimi r0, r3, 7, 0x18, 0x18
/* 80092660 0008F240  98 1F 22 1B */	stb r0, 0x221b(r31)
/* 80092664 0008F244  88 9F 22 1F */	lbz r4, 0x221f(r31)
/* 80092668 0008F248  88 7F 00 0C */	lbz r3, 0xc(r31)
/* 8009266C 0008F24C  54 84 EF FE */	rlwinm r4, r4, 0x1d, 0x1f, 0x1f
/* 80092670 0008F250  4B FA BA 79 */	bl func_8003E0E8
/* 80092674 0008F254  7F C3 F3 78 */	mr r3, r30
/* 80092678 0008F258  48 00 64 A9 */	bl func_80098B20
/* 8009267C 0008F25C  38 7F 00 00 */	addi r3, r31, 0
/* 80092680 0008F260  38 80 00 81 */	li r4, 0x81
/* 80092684 0008F264  38 A0 00 7F */	li r5, 0x7f
/* 80092688 0008F268  38 C0 00 40 */	li r6, 0x40
/* 8009268C 0008F26C  4B FF 5A BD */	bl func_80088148
/* 80092690 0008F270  38 60 00 01 */	li r3, 1
/* 80092694 0008F274  48 00 00 30 */	b lbl_800926C4
lbl_80092698:
/* 80092698 0008F278  C0 3F 23 50 */	lfs f1, 0x2350(r31)
/* 8009269C 0008F27C  FC 01 10 40 */	fcmpo cr0, f1, f2
/* 800926A0 0008F280  40 81 00 20 */	ble lbl_800926C0
/* 800926A4 0008F284  C0 02 8B 88 */	lfs f0, lbl_804D8568(r2)
/* 800926A8 0008F288  EC 01 00 28 */	fsubs f0, f1, f0
/* 800926AC 0008F28C  D0 1F 23 50 */	stfs f0, 0x2350(r31)
/* 800926B0 0008F290  C0 1F 23 50 */	lfs f0, 0x2350(r31)
/* 800926B4 0008F294  FC 00 10 40 */	fcmpo cr0, f0, f2
/* 800926B8 0008F298  40 80 00 08 */	bge lbl_800926C0
/* 800926BC 0008F29C  D0 5F 23 50 */	stfs f2, 0x2350(r31)
lbl_800926C0:
/* 800926C0 0008F2A0  38 60 00 00 */	li r3, 0
lbl_800926C4:
/* 800926C4 0008F2A4  80 01 00 24 */	lwz r0, 0x24(r1)
/* 800926C8 0008F2A8  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 800926CC 0008F2AC  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 800926D0 0008F2B0  38 21 00 20 */	addi r1, r1, 0x20
/* 800926D4 0008F2B4  7C 08 03 A6 */	mtlr r0
/* 800926D8 0008F2B8  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

#pragma push
asm unk_t func_800926DC()
{ // clang-format off
    nofralloc
/* 800926DC 0008F2BC  7C 08 02 A6 */	mflr r0
/* 800926E0 0008F2C0  90 01 00 04 */	stw r0, 4(r1)
/* 800926E4 0008F2C4  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 800926E8 0008F2C8  93 E1 00 14 */	stw r31, 0x14(r1)
/* 800926EC 0008F2CC  93 C1 00 10 */	stw r30, 0x10(r1)
/* 800926F0 0008F2D0  7C 7E 1B 78 */	mr r30, r3
/* 800926F4 0008F2D4  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 800926F8 0008F2D8  C0 02 8B 88 */	lfs f0, lbl_804D8568(r2)
/* 800926FC 0008F2DC  C0 3F 23 40 */	lfs f1, 0x2340(r31)
/* 80092700 0008F2E0  EC 01 00 2A */	fadds f0, f1, f0
/* 80092704 0008F2E4  D0 1F 23 40 */	stfs f0, 0x2340(r31)
/* 80092708 0008F2E8  4B FF FE 9D */	bl func_800925A4
/* 8009270C 0008F2EC  2C 03 00 00 */	cmpwi r3, 0
/* 80092710 0008F2F0  40 82 00 30 */	bne lbl_80092740
/* 80092714 0008F2F4  C0 3F 23 40 */	lfs f1, 0x2340(r31)
/* 80092718 0008F2F8  C0 1F 02 E8 */	lfs f0, 0x2e8(r31)
/* 8009271C 0008F2FC  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 80092720 0008F300  4C 41 13 82 */	cror 2, 1, 2
/* 80092724 0008F304  40 82 00 10 */	bne lbl_80092734
/* 80092728 0008F308  7F C3 F3 78 */	mr r3, r30
/* 8009272C 0008F30C  48 00 01 A1 */	bl func_800928CC
/* 80092730 0008F310  48 00 00 10 */	b lbl_80092740
lbl_80092734:
/* 80092734 0008F314  7F C3 F3 78 */	mr r3, r30
/* 80092738 0008F318  EC 21 00 24 */	fdivs f1, f1, f0
/* 8009273C 0008F31C  4B FF F7 3D */	bl func_80091E78
lbl_80092740:
/* 80092740 0008F320  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 80092744 0008F324  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 80092748 0008F328  83 C1 00 10 */	lwz r30, 0x10(r1)
/* 8009274C 0008F32C  38 21 00 18 */	addi r1, r1, 0x18
/* 80092750 0008F330  7C 08 03 A6 */	mtlr r0
/* 80092754 0008F334  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

extern unk_t func_800CB024();
extern unk_t func_800D8B9C();
extern unk_t func_8009980C();

#pragma push
asm unk_t func_80092758()
{ // clang-format off
    nofralloc
/* 80092758 0008F338  7C 08 02 A6 */	mflr r0
/* 8009275C 0008F33C  90 01 00 04 */	stw r0, 4(r1)
/* 80092760 0008F340  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 80092764 0008F344  93 E1 00 14 */	stw r31, 0x14(r1)
/* 80092768 0008F348  93 C1 00 10 */	stw r30, 0x10(r1)
/* 8009276C 0008F34C  7C 7E 1B 78 */	mr r30, r3
/* 80092770 0008F350  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 80092774 0008F354  48 00 04 59 */	bl func_80092BCC
/* 80092778 0008F358  80 1F 23 4C */	lwz r0, 0x234c(r31)
/* 8009277C 0008F35C  2C 00 00 00 */	cmpwi r0, 0
/* 80092780 0008F360  41 82 00 14 */	beq lbl_80092794
/* 80092784 0008F364  C0 3F 23 50 */	lfs f1, 0x2350(r31)
/* 80092788 0008F368  C0 02 8B 58 */	lfs f0, lbl_804D8538(r2)
/* 8009278C 0008F36C  FC 01 00 00 */	fcmpu cr0, f1, f0
/* 80092790 0008F370  41 82 00 1C */	beq lbl_800927AC
lbl_80092794:
/* 80092794 0008F374  88 1F 22 1B */	lbz r0, 0x221b(r31)
/* 80092798 0008F378  54 00 CF FF */	rlwinm. r0, r0, 0x19, 0x1f, 0x1f
/* 8009279C 0008F37C  40 82 00 20 */	bne lbl_800927BC
/* 800927A0 0008F380  88 1F 22 18 */	lbz r0, 0x2218(r31)
/* 800927A4 0008F384  54 00 E7 FF */	rlwinm. r0, r0, 0x1c, 0x1f, 0x1f
/* 800927A8 0008F388  40 82 00 14 */	bne lbl_800927BC
lbl_800927AC:
/* 800927AC 0008F38C  7F C3 F3 78 */	mr r3, r30
/* 800927B0 0008F390  48 00 04 39 */	bl func_80092BE8
/* 800927B4 0008F394  38 00 00 01 */	li r0, 1
/* 800927B8 0008F398  48 00 00 1C */	b lbl_800927D4
lbl_800927BC:
/* 800927BC 0008F39C  80 7F 23 5C */	lwz r3, 0x235c(r31)
/* 800927C0 0008F3A0  2C 03 00 00 */	cmpwi r3, 0
/* 800927C4 0008F3A4  41 82 00 0C */	beq lbl_800927D0
/* 800927C8 0008F3A8  38 03 FF FF */	addi r0, r3, -1
/* 800927CC 0008F3AC  90 1F 23 5C */	stw r0, 0x235c(r31)
lbl_800927D0:
/* 800927D0 0008F3B0  38 00 00 00 */	li r0, 0
lbl_800927D4:
/* 800927D4 0008F3B4  2C 00 00 00 */	cmpwi r0, 0
/* 800927D8 0008F3B8  40 82 00 80 */	bne lbl_80092858
/* 800927DC 0008F3BC  7F C3 F3 78 */	mr r3, r30
/* 800927E0 0008F3C0  48 00 0E B5 */	bl func_80093694
/* 800927E4 0008F3C4  2C 03 00 00 */	cmpwi r3, 0
/* 800927E8 0008F3C8  40 82 00 70 */	bne lbl_80092858
/* 800927EC 0008F3CC  7F C3 F3 78 */	mr r3, r30
/* 800927F0 0008F3D0  48 00 29 6D */	bl func_8009515C
/* 800927F4 0008F3D4  2C 03 00 00 */	cmpwi r3, 0
/* 800927F8 0008F3D8  40 82 00 60 */	bne lbl_80092858
/* 800927FC 0008F3DC  7F C3 F3 78 */	mr r3, r30
/* 80092800 0008F3E0  48 00 70 0D */	bl func_8009980C
/* 80092804 0008F3E4  2C 03 00 00 */	cmpwi r3, 0
/* 80092808 0008F3E8  40 82 00 50 */	bne lbl_80092858
/* 8009280C 0008F3EC  7F C3 F3 78 */	mr r3, r30
/* 80092810 0008F3F0  48 00 69 6D */	bl func_8009917C
/* 80092814 0008F3F4  2C 03 00 00 */	cmpwi r3, 0
/* 80092818 0008F3F8  40 82 00 40 */	bne lbl_80092858
/* 8009281C 0008F3FC  7F C3 F3 78 */	mr r3, r30
/* 80092820 0008F400  48 04 63 7D */	bl func_800D8B9C
/* 80092824 0008F404  2C 03 00 00 */	cmpwi r3, 0
/* 80092828 0008F408  40 82 00 30 */	bne lbl_80092858
/* 8009282C 0008F40C  7F C3 F3 78 */	mr r3, r30
/* 80092830 0008F410  48 04 61 61 */	bl func_800D8990
/* 80092834 0008F414  2C 03 00 00 */	cmpwi r3, 0
/* 80092838 0008F418  40 82 00 20 */	bne lbl_80092858
/* 8009283C 0008F41C  7F C3 F3 78 */	mr r3, r30
/* 80092840 0008F420  48 03 87 E5 */	bl func_800CB024
/* 80092844 0008F424  2C 03 00 00 */	cmpwi r3, 0
/* 80092848 0008F428  40 82 00 10 */	bne lbl_80092858
/* 8009284C 0008F42C  7F C3 F3 78 */	mr r3, r30
/* 80092850 0008F430  48 00 78 31 */	bl func_8009A080
/* 80092854 0008F434  2C 03 00 00 */	cmpwi r3, 0
lbl_80092858:
/* 80092858 0008F438  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 8009285C 0008F43C  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 80092860 0008F440  83 C1 00 10 */	lwz r30, 0x10(r1)
/* 80092864 0008F444  38 21 00 18 */	addi r1, r1, 0x18
/* 80092868 0008F448  7C 08 03 A6 */	mtlr r0
/* 8009286C 0008F44C  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

#pragma push
asm unk_t func_80092870()
{ // clang-format off
    nofralloc
/* 80092870 0008F450  7C 08 02 A6 */	mflr r0
/* 80092874 0008F454  90 01 00 04 */	stw r0, 4(r1)
/* 80092878 0008F458  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 8009287C 0008F45C  93 E1 00 14 */	stw r31, 0x14(r1)
/* 80092880 0008F460  7C 7F 1B 78 */	mr r31, r3
/* 80092884 0008F464  4B FF 26 B9 */	bl func_80084F3C
/* 80092888 0008F468  7F E3 FB 78 */	mr r3, r31
/* 8009288C 0008F46C  4B FE 86 55 */	bl func_8007AEE0
/* 80092890 0008F470  7F E3 FB 78 */	mr r3, r31
/* 80092894 0008F474  4B FE 86 65 */	bl func_8007AEF8
/* 80092898 0008F478  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 8009289C 0008F47C  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 800928A0 0008F480  38 21 00 18 */	addi r1, r1, 0x18
/* 800928A4 0008F484  7C 08 03 A6 */	mtlr r0
/* 800928A8 0008F488  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

#pragma push
asm unk_t func_800928AC()
{ // clang-format off
    nofralloc
/* 800928AC 0008F48C  7C 08 02 A6 */	mflr r0
/* 800928B0 0008F490  90 01 00 04 */	stw r0, 4(r1)
/* 800928B4 0008F494  94 21 FF F8 */	stwu r1, -8(r1)
/* 800928B8 0008F498  4B FF 1C FD */	bl func_800845B4
/* 800928BC 0008F49C  80 01 00 0C */	lwz r0, 0xc(r1)
/* 800928C0 0008F4A0  38 21 00 08 */	addi r1, r1, 8
/* 800928C4 0008F4A4  7C 08 03 A6 */	mtlr r0
/* 800928C8 0008F4A8  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

extern unk_t func_80092908();

#pragma push
asm void func_800928CC(HSD_GObj* fighter_gobj)
{ // clang-format off
    nofralloc
/* 800928CC 0008F4AC  7C 08 02 A6 */	mflr r0
/* 800928D0 0008F4B0  90 01 00 04 */	stw r0, 4(r1)
/* 800928D4 0008F4B4  94 21 FF F8 */	stwu r1, -8(r1)
/* 800928D8 0008F4B8  80 83 00 2C */	lwz r4, 0x2c(r3)
/* 800928DC 0008F4BC  80 04 00 04 */	lwz r0, 4(r4)
/* 800928E0 0008F4C0  2C 00 00 0E */	cmpwi r0, 0xe
/* 800928E4 0008F4C4  41 82 00 08 */	beq lbl_800928EC
/* 800928E8 0008F4C8  48 00 00 0C */	b lbl_800928F4
lbl_800928EC:
/* 800928EC 0008F4CC  48 09 98 E9 */	bl func_8012C1D4
/* 800928F0 0008F4D0  48 00 00 08 */	b lbl_800928F8
lbl_800928F4:
/* 800928F4 0008F4D4  48 00 00 15 */	bl func_80092908
lbl_800928F8:
/* 800928F8 0008F4D8  80 01 00 0C */	lwz r0, 0xc(r1)
/* 800928FC 0008F4DC  38 21 00 08 */	addi r1, r1, 8
/* 80092900 0008F4E0  7C 08 03 A6 */	mtlr r0
/* 80092904 0008F4E4  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

#pragma push
asm unk_t func_80092908()
{ // clang-format off
    nofralloc
/* 80092908 0008F4E8  7C 08 02 A6 */	mflr r0
/* 8009290C 0008F4EC  38 80 00 B3 */	li r4, 0xb3
/* 80092910 0008F4F0  90 01 00 04 */	stw r0, 4(r1)
/* 80092914 0008F4F4  3C A0 20 00 */	lis r5, 0x2000
/* 80092918 0008F4F8  38 C0 00 00 */	li r6, 0
/* 8009291C 0008F4FC  94 21 FF C0 */	stwu r1, -0x40(r1)
/* 80092920 0008F500  93 E1 00 3C */	stw r31, 0x3c(r1)
/* 80092924 0008F504  93 C1 00 38 */	stw r30, 0x38(r1)
/* 80092928 0008F508  7C 7E 1B 78 */	mr r30, r3
/* 8009292C 0008F50C  93 A1 00 34 */	stw r29, 0x34(r1)
/* 80092930 0008F510  C0 22 8B 58 */	lfs f1, lbl_804D8538(r2)
/* 80092934 0008F514  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 80092938 0008F518  FC 60 08 90 */	fmr f3, f1
/* 8009293C 0008F51C  C0 42 8B 88 */	lfs f2, lbl_804D8568(r2)
/* 80092940 0008F520  4B FD 6A 6D */	bl Fighter_ActionStateChange_800693AC
/* 80092944 0008F524  80 7F 01 0C */	lwz r3, 0x10c(r31)
/* 80092948 0008F528  80 BE 00 2C */	lwz r5, 0x2c(r30)
/* 8009294C 0008F52C  80 63 00 08 */	lwz r3, 8(r3)
/* 80092950 0008F530  80 9F 05 E8 */	lwz r4, 0x5e8(r31)
/* 80092954 0008F534  88 03 00 11 */	lbz r0, 0x11(r3)
/* 80092958 0008F538  88 65 00 0C */	lbz r3, 0xc(r5)
/* 8009295C 0008F53C  54 00 20 36 */	slwi r0, r0, 4
/* 80092960 0008F540  7F A4 00 2E */	lwzx r29, r4, r0
/* 80092964 0008F544  4B FA 3B D5 */	bl Player_GetUnk45
/* 80092968 0008F548  80 0D AE 6C */	lwz r0, lbl_804D650C(r13)
/* 8009296C 0008F54C  54 63 10 3A */	slwi r3, r3, 2
/* 80092970 0008F550  38 9E 00 00 */	addi r4, r30, 0
/* 80092974 0008F554  4C C6 31 82 */	crclr 6
/* 80092978 0008F558  7C E0 1A 14 */	add r7, r0, r3
/* 8009297C 0008F55C  88 07 00 01 */	lbz r0, 1(r7)
/* 80092980 0008F560  7F A5 EB 78 */	mr r5, r29
/* 80092984 0008F564  88 C7 00 00 */	lbz r6, 0(r7)
/* 80092988 0008F568  38 60 04 18 */	li r3, 0x418
/* 8009298C 0008F56C  54 00 40 2E */	slwi r0, r0, 8
/* 80092990 0008F570  88 E7 00 02 */	lbz r7, 2(r7)
/* 80092994 0008F574  50 C0 82 1E */	rlwimi r0, r6, 0x10, 8, 0xf
/* 80092998 0008F578  7C E6 03 78 */	or r6, r7, r0
/* 8009299C 0008F57C  4B FC D4 41 */	bl ef_Spawn
/* 800929A0 0008F580  88 1F 22 19 */	lbz r0, 0x2219(r31)
/* 800929A4 0008F584  3B A0 00 01 */	li r29, 1
/* 800929A8 0008F588  53 A0 3E 30 */	rlwimi r0, r29, 7, 0x18, 0x18
/* 800929AC 0008F58C  98 1F 22 19 */	stb r0, 0x2219(r31)
/* 800929B0 0008F590  3C 60 80 09 */	lis r3, lbl_80092E50@ha
/* 800929B4 0008F594  38 A3 2E 50 */	addi r5, r3, lbl_80092E50@l
/* 800929B8 0008F598  83 FE 00 2C */	lwz r31, 0x2c(r30)
/* 800929BC 0008F59C  7F C3 F3 78 */	mr r3, r30
/* 800929C0 0008F5A0  C0 22 8B 88 */	lfs f1, lbl_804D8568(r2)
/* 800929C4 0008F5A4  38 81 00 18 */	addi r4, r1, 0x18
/* 800929C8 0008F5A8  80 DF 01 0C */	lwz r6, 0x10c(r31)
/* 800929CC 0008F5AC  C0 02 8B 58 */	lfs f0, lbl_804D8538(r2)
/* 800929D0 0008F5B0  80 C6 00 08 */	lwz r6, 8(r6)
/* 800929D4 0008F5B4  88 06 00 11 */	lbz r0, 0x11(r6)
/* 800929D8 0008F5B8  90 01 00 18 */	stw r0, 0x18(r1)
/* 800929DC 0008F5BC  D0 21 00 28 */	stfs f1, 0x28(r1)
/* 800929E0 0008F5C0  D0 01 00 24 */	stfs f0, 0x24(r1)
/* 800929E4 0008F5C4  D0 01 00 20 */	stfs f0, 0x20(r1)
/* 800929E8 0008F5C8  D0 01 00 1C */	stfs f0, 0x1c(r1)
/* 800929EC 0008F5CC  4B FE 87 CD */	bl func_8007B1B8
/* 800929F0 0008F5D0  88 1F 22 1A */	lbz r0, 0x221a(r31)
/* 800929F4 0008F5D4  53 A0 07 FE */	rlwimi r0, r29, 0, 0x1f, 0x1f
/* 800929F8 0008F5D8  38 7E 00 00 */	addi r3, r30, 0
/* 800929FC 0008F5DC  98 1F 22 1A */	stb r0, 0x221a(r31)
/* 80092A00 0008F5E0  C0 22 8B 88 */	lfs f1, lbl_804D8568(r2)
/* 80092A04 0008F5E4  4B FF F4 75 */	bl func_80091E78
/* 80092A08 0008F5E8  80 01 00 44 */	lwz r0, 0x44(r1)
/* 80092A0C 0008F5EC  83 E1 00 3C */	lwz r31, 0x3c(r1)
/* 80092A10 0008F5F0  83 C1 00 38 */	lwz r30, 0x38(r1)
/* 80092A14 0008F5F4  83 A1 00 34 */	lwz r29, 0x34(r1)
/* 80092A18 0008F5F8  38 21 00 40 */	addi r1, r1, 0x40
/* 80092A1C 0008F5FC  7C 08 03 A6 */	mtlr r0
/* 80092A20 0008F600  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

#pragma push
asm unk_t func_80092A24()
{ // clang-format off
    nofralloc
/* 80092A24 0008F604  7C 08 02 A6 */	mflr r0
/* 80092A28 0008F608  90 01 00 04 */	stw r0, 4(r1)
/* 80092A2C 0008F60C  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 80092A30 0008F610  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 80092A34 0008F614  7C 7F 1B 78 */	mr r31, r3
/* 80092A38 0008F618  80 83 00 2C */	lwz r4, 0x2c(r3)
/* 80092A3C 0008F61C  C0 02 8B 88 */	lfs f0, lbl_804D8568(r2)
/* 80092A40 0008F620  C0 24 23 40 */	lfs f1, 0x2340(r4)
/* 80092A44 0008F624  EC 01 00 2A */	fadds f0, f1, f0
/* 80092A48 0008F628  D0 04 23 40 */	stfs f0, 0x2340(r4)
/* 80092A4C 0008F62C  4B FF FB 59 */	bl func_800925A4
/* 80092A50 0008F630  2C 03 00 00 */	cmpwi r3, 0
/* 80092A54 0008F634  40 82 00 10 */	bne lbl_80092A64
/* 80092A58 0008F638  7F E3 FB 78 */	mr r3, r31
/* 80092A5C 0008F63C  C0 22 8B 88 */	lfs f1, lbl_804D8568(r2)
/* 80092A60 0008F640  4B FF F4 19 */	bl func_80091E78
lbl_80092A64:
/* 80092A64 0008F644  80 01 00 24 */	lwz r0, 0x24(r1)
/* 80092A68 0008F648  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 80092A6C 0008F64C  38 21 00 20 */	addi r1, r1, 0x20
/* 80092A70 0008F650  7C 08 03 A6 */	mtlr r0
/* 80092A74 0008F654  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

#pragma push
asm unk_t func_80092A78()
{ // clang-format off
    nofralloc
/* 80092A78 0008F658  7C 08 02 A6 */	mflr r0
/* 80092A7C 0008F65C  90 01 00 04 */	stw r0, 4(r1)
/* 80092A80 0008F660  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 80092A84 0008F664  93 E1 00 14 */	stw r31, 0x14(r1)
/* 80092A88 0008F668  93 C1 00 10 */	stw r30, 0x10(r1)
/* 80092A8C 0008F66C  7C 7E 1B 78 */	mr r30, r3
/* 80092A90 0008F670  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 80092A94 0008F674  48 00 01 39 */	bl func_80092BCC
/* 80092A98 0008F678  80 1F 23 4C */	lwz r0, 0x234c(r31)
/* 80092A9C 0008F67C  2C 00 00 00 */	cmpwi r0, 0
/* 80092AA0 0008F680  41 82 00 14 */	beq lbl_80092AB4
/* 80092AA4 0008F684  C0 3F 23 50 */	lfs f1, 0x2350(r31)
/* 80092AA8 0008F688  C0 02 8B 58 */	lfs f0, lbl_804D8538(r2)
/* 80092AAC 0008F68C  FC 01 00 00 */	fcmpu cr0, f1, f0
/* 80092AB0 0008F690  41 82 00 1C */	beq lbl_80092ACC
lbl_80092AB4:
/* 80092AB4 0008F694  88 1F 22 1B */	lbz r0, 0x221b(r31)
/* 80092AB8 0008F698  54 00 CF FF */	rlwinm. r0, r0, 0x19, 0x1f, 0x1f
/* 80092ABC 0008F69C  40 82 00 20 */	bne lbl_80092ADC
/* 80092AC0 0008F6A0  88 1F 22 18 */	lbz r0, 0x2218(r31)
/* 80092AC4 0008F6A4  54 00 E7 FF */	rlwinm. r0, r0, 0x1c, 0x1f, 0x1f
/* 80092AC8 0008F6A8  40 82 00 14 */	bne lbl_80092ADC
lbl_80092ACC:
/* 80092ACC 0008F6AC  7F C3 F3 78 */	mr r3, r30
/* 80092AD0 0008F6B0  48 00 01 19 */	bl func_80092BE8
/* 80092AD4 0008F6B4  38 00 00 01 */	li r0, 1
/* 80092AD8 0008F6B8  48 00 00 1C */	b lbl_80092AF4
lbl_80092ADC:
/* 80092ADC 0008F6BC  80 7F 23 5C */	lwz r3, 0x235c(r31)
/* 80092AE0 0008F6C0  2C 03 00 00 */	cmpwi r3, 0
/* 80092AE4 0008F6C4  41 82 00 0C */	beq lbl_80092AF0
/* 80092AE8 0008F6C8  38 03 FF FF */	addi r0, r3, -1
/* 80092AEC 0008F6CC  90 1F 23 5C */	stw r0, 0x235c(r31)
lbl_80092AF0:
/* 80092AF0 0008F6D0  38 00 00 00 */	li r0, 0
lbl_80092AF4:
/* 80092AF4 0008F6D4  2C 00 00 00 */	cmpwi r0, 0
/* 80092AF8 0008F6D8  40 82 00 60 */	bne lbl_80092B58
/* 80092AFC 0008F6DC  7F C3 F3 78 */	mr r3, r30
/* 80092B00 0008F6E0  48 00 26 5D */	bl func_8009515C
/* 80092B04 0008F6E4  2C 03 00 00 */	cmpwi r3, 0
/* 80092B08 0008F6E8  40 82 00 50 */	bne lbl_80092B58
/* 80092B0C 0008F6EC  7F C3 F3 78 */	mr r3, r30
/* 80092B10 0008F6F0  48 00 6C FD */	bl func_8009980C
/* 80092B14 0008F6F4  2C 03 00 00 */	cmpwi r3, 0
/* 80092B18 0008F6F8  40 82 00 40 */	bne lbl_80092B58
/* 80092B1C 0008F6FC  7F C3 F3 78 */	mr r3, r30
/* 80092B20 0008F700  48 00 66 5D */	bl func_8009917C
/* 80092B24 0008F704  2C 03 00 00 */	cmpwi r3, 0
/* 80092B28 0008F708  40 82 00 30 */	bne lbl_80092B58
/* 80092B2C 0008F70C  7F C3 F3 78 */	mr r3, r30
/* 80092B30 0008F710  48 04 5E 61 */	bl func_800D8990
/* 80092B34 0008F714  2C 03 00 00 */	cmpwi r3, 0
/* 80092B38 0008F718  40 82 00 20 */	bne lbl_80092B58
/* 80092B3C 0008F71C  7F C3 F3 78 */	mr r3, r30
/* 80092B40 0008F720  48 03 84 E5 */	bl func_800CB024
/* 80092B44 0008F724  2C 03 00 00 */	cmpwi r3, 0
/* 80092B48 0008F728  40 82 00 10 */	bne lbl_80092B58
/* 80092B4C 0008F72C  7F C3 F3 78 */	mr r3, r30
/* 80092B50 0008F730  48 00 75 31 */	bl func_8009A080
/* 80092B54 0008F734  2C 03 00 00 */	cmpwi r3, 0
lbl_80092B58:
/* 80092B58 0008F738  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 80092B5C 0008F73C  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 80092B60 0008F740  83 C1 00 10 */	lwz r30, 0x10(r1)
/* 80092B64 0008F744  38 21 00 18 */	addi r1, r1, 0x18
/* 80092B68 0008F748  7C 08 03 A6 */	mtlr r0
/* 80092B6C 0008F74C  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

#pragma push
asm unk_t func_80092B70()
{ // clang-format off
    nofralloc
/* 80092B70 0008F750  7C 08 02 A6 */	mflr r0
/* 80092B74 0008F754  90 01 00 04 */	stw r0, 4(r1)
/* 80092B78 0008F758  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 80092B7C 0008F75C  93 E1 00 14 */	stw r31, 0x14(r1)
/* 80092B80 0008F760  7C 7F 1B 78 */	mr r31, r3
/* 80092B84 0008F764  4B FF 23 B9 */	bl func_80084F3C
/* 80092B88 0008F768  7F E3 FB 78 */	mr r3, r31
/* 80092B8C 0008F76C  4B FE 83 55 */	bl func_8007AEE0
/* 80092B90 0008F770  7F E3 FB 78 */	mr r3, r31
/* 80092B94 0008F774  4B FE 83 65 */	bl func_8007AEF8
/* 80092B98 0008F778  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 80092B9C 0008F77C  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 80092BA0 0008F780  38 21 00 18 */	addi r1, r1, 0x18
/* 80092BA4 0008F784  7C 08 03 A6 */	mtlr r0
/* 80092BA8 0008F788  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

#pragma push
asm unk_t func_80092BAC()
{ // clang-format off
    nofralloc
/* 80092BAC 0008F78C  7C 08 02 A6 */	mflr r0
/* 80092BB0 0008F790  90 01 00 04 */	stw r0, 4(r1)
/* 80092BB4 0008F794  94 21 FF F8 */	stwu r1, -8(r1)
/* 80092BB8 0008F798  4B FF 19 FD */	bl func_800845B4
/* 80092BBC 0008F79C  80 01 00 0C */	lwz r0, 0xc(r1)
/* 80092BC0 0008F7A0  38 21 00 08 */	addi r1, r1, 8
/* 80092BC4 0008F7A4  7C 08 03 A6 */	mtlr r0
/* 80092BC8 0008F7A8  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

#pragma push
asm void func_80092BCC(HSD_GObj* fighter_gobj)
{ // clang-format off
    nofralloc
/* 80092BCC 0008F7AC  80 63 00 2C */	lwz r3, 0x2c(r3)
/* 80092BD0 0008F7B0  80 03 06 5C */	lwz r0, 0x65c(r3)
/* 80092BD4 0008F7B4  54 00 00 01 */	rlwinm. r0, r0, 0, 0, 0
/* 80092BD8 0008F7B8  4C 82 00 20 */	bnelr 
/* 80092BDC 0008F7BC  38 00 00 01 */	li r0, 1
/* 80092BE0 0008F7C0  90 03 23 4C */	stw r0, 0x234c(r3)
/* 80092BE4 0008F7C4  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

extern unk_t func_80092C54();
extern unk_t func_8003E114();

#pragma push
asm unk_t func_80092BE8()
{ // clang-format off
    nofralloc
/* 80092BE8 0008F7C8  7C 08 02 A6 */	mflr r0
/* 80092BEC 0008F7CC  90 01 00 04 */	stw r0, 4(r1)
/* 80092BF0 0008F7D0  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 80092BF4 0008F7D4  93 E1 00 14 */	stw r31, 0x14(r1)
/* 80092BF8 0008F7D8  93 C1 00 10 */	stw r30, 0x10(r1)
/* 80092BFC 0008F7DC  7C 7E 1B 78 */	mr r30, r3
/* 80092C00 0008F7E0  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 80092C04 0008F7E4  88 9F 22 1F */	lbz r4, 0x221f(r31)
/* 80092C08 0008F7E8  88 7F 00 0C */	lbz r3, 0xc(r31)
/* 80092C0C 0008F7EC  C0 3F 19 98 */	lfs f1, 0x1998(r31)
/* 80092C10 0008F7F0  54 84 EF FE */	rlwinm r4, r4, 0x1d, 0x1f, 0x1f
/* 80092C14 0008F7F4  4B FA B5 01 */	bl func_8003E114
/* 80092C18 0008F7F8  80 1F 00 04 */	lwz r0, 4(r31)
/* 80092C1C 0008F7FC  2C 00 00 0E */	cmpwi r0, 0xe
/* 80092C20 0008F800  41 82 00 08 */	beq lbl_80092C28
/* 80092C24 0008F804  48 00 00 10 */	b lbl_80092C34
lbl_80092C28:
/* 80092C28 0008F808  7F C3 F3 78 */	mr r3, r30
/* 80092C2C 0008F80C  48 09 98 71 */	bl func_8012C49C
/* 80092C30 0008F810  48 00 00 0C */	b lbl_80092C3C
lbl_80092C34:
/* 80092C34 0008F814  7F C3 F3 78 */	mr r3, r30
/* 80092C38 0008F818  48 00 00 1D */	bl func_80092C54
lbl_80092C3C:
/* 80092C3C 0008F81C  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 80092C40 0008F820  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 80092C44 0008F824  83 C1 00 10 */	lwz r30, 0x10(r1)
/* 80092C48 0008F828  38 21 00 18 */	addi r1, r1, 0x18
/* 80092C4C 0008F82C  7C 08 03 A6 */	mtlr r0
/* 80092C50 0008F830  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

#pragma push
asm unk_t func_80092C54()
{ // clang-format off
    nofralloc
/* 80092C54 0008F834  7C 08 02 A6 */	mflr r0
/* 80092C58 0008F838  38 80 00 B4 */	li r4, 0xb4
/* 80092C5C 0008F83C  90 01 00 04 */	stw r0, 4(r1)
/* 80092C60 0008F840  38 A0 00 00 */	li r5, 0
/* 80092C64 0008F844  38 C0 00 00 */	li r6, 0
/* 80092C68 0008F848  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 80092C6C 0008F84C  93 E1 00 14 */	stw r31, 0x14(r1)
/* 80092C70 0008F850  C0 22 8B 58 */	lfs f1, lbl_804D8538(r2)
/* 80092C74 0008F854  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 80092C78 0008F858  FC 60 08 90 */	fmr f3, f1
/* 80092C7C 0008F85C  C0 42 8B 88 */	lfs f2, lbl_804D8568(r2)
/* 80092C80 0008F860  4B FD 67 2D */	bl Fighter_ActionStateChange_800693AC
/* 80092C84 0008F864  38 7F 00 00 */	addi r3, r31, 0
/* 80092C88 0008F868  38 80 00 7F */	li r4, 0x7f
/* 80092C8C 0008F86C  38 A0 00 7F */	li r5, 0x7f
/* 80092C90 0008F870  38 C0 00 40 */	li r6, 0x40
/* 80092C94 0008F874  4B FF 54 B5 */	bl func_80088148
/* 80092C98 0008F878  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 80092C9C 0008F87C  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 80092CA0 0008F880  38 21 00 18 */	addi r1, r1, 0x18
/* 80092CA4 0008F884  7C 08 03 A6 */	mtlr r0
/* 80092CA8 0008F888  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

#pragma push
asm unk_t func_80092CAC()
{ // clang-format off
    nofralloc
/* 80092CAC 0008F88C  7C 08 02 A6 */	mflr r0
/* 80092CB0 0008F890  90 01 00 04 */	stw r0, 4(r1)
/* 80092CB4 0008F894  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 80092CB8 0008F898  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 80092CBC 0008F89C  7C 7F 1B 78 */	mr r31, r3
/* 80092CC0 0008F8A0  80 83 00 2C */	lwz r4, 0x2c(r3)
/* 80092CC4 0008F8A4  C0 02 8B 88 */	lfs f0, lbl_804D8568(r2)
/* 80092CC8 0008F8A8  C0 24 23 40 */	lfs f1, 0x2340(r4)
/* 80092CCC 0008F8AC  EC 01 00 2A */	fadds f0, f1, f0
/* 80092CD0 0008F8B0  D0 04 23 40 */	stfs f0, 0x2340(r4)
/* 80092CD4 0008F8B4  4B FD C5 65 */	bl ftAnim_IsFramesRemaining
/* 80092CD8 0008F8B8  2C 03 00 00 */	cmpwi r3, 0
/* 80092CDC 0008F8BC  40 82 00 0C */	bne lbl_80092CE8
/* 80092CE0 0008F8C0  7F E3 FB 78 */	mr r3, r31
/* 80092CE4 0008F8C4  4B FF 75 D9 */	bl func_8008A2BC
lbl_80092CE8:
/* 80092CE8 0008F8C8  80 01 00 24 */	lwz r0, 0x24(r1)
/* 80092CEC 0008F8CC  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 80092CF0 0008F8D0  38 21 00 20 */	addi r1, r1, 0x20
/* 80092CF4 0008F8D4  7C 08 03 A6 */	mtlr r0
/* 80092CF8 0008F8D8  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

#pragma push
asm unk_t func_80092CFC()
{ // clang-format off
    nofralloc
/* 80092CFC 0008F8DC  7C 08 02 A6 */	mflr r0
/* 80092D00 0008F8E0  90 01 00 04 */	stw r0, 4(r1)
/* 80092D04 0008F8E4  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 80092D08 0008F8E8  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 80092D0C 0008F8EC  7C 7F 1B 78 */	mr r31, r3
/* 80092D10 0008F8F0  80 63 00 2C */	lwz r3, 0x2c(r3)
/* 80092D14 0008F8F4  80 03 23 5C */	lwz r0, 0x235c(r3)
/* 80092D18 0008F8F8  2C 00 00 00 */	cmpwi r0, 0
/* 80092D1C 0008F8FC  41 82 00 C4 */	beq lbl_80092DE0
/* 80092D20 0008F900  7F E3 FB 78 */	mr r3, r31
/* 80092D24 0008F904  48 00 38 1D */	bl func_80096540
/* 80092D28 0008F908  2C 03 00 00 */	cmpwi r3, 0
/* 80092D2C 0008F90C  40 82 00 D0 */	bne lbl_80092DFC
/* 80092D30 0008F910  7F E3 FB 78 */	mr r3, r31
/* 80092D34 0008F914  48 04 3C 29 */	bl func_800D695C
/* 80092D38 0008F918  2C 03 00 00 */	cmpwi r3, 0
/* 80092D3C 0008F91C  40 82 00 C0 */	bne lbl_80092DFC
/* 80092D40 0008F920  7F E3 FB 78 */	mr r3, r31
/* 80092D44 0008F924  48 04 3A E1 */	bl func_800D6824
/* 80092D48 0008F928  2C 03 00 00 */	cmpwi r3, 0
/* 80092D4C 0008F92C  40 82 00 B0 */	bne lbl_80092DFC
/* 80092D50 0008F930  7F E3 FB 78 */	mr r3, r31
/* 80092D54 0008F934  48 04 3B 6D */	bl func_800D68C0
/* 80092D58 0008F938  2C 03 00 00 */	cmpwi r3, 0
/* 80092D5C 0008F93C  40 82 00 A0 */	bne lbl_80092DFC
/* 80092D60 0008F940  7F E3 FB 78 */	mr r3, r31
/* 80092D64 0008F944  48 04 5C 2D */	bl func_800D8990
/* 80092D68 0008F948  2C 03 00 00 */	cmpwi r3, 0
/* 80092D6C 0008F94C  40 82 00 90 */	bne lbl_80092DFC
/* 80092D70 0008F950  7F E3 FB 78 */	mr r3, r31
/* 80092D74 0008F954  4B FF 92 51 */	bl func_8008BFC4
/* 80092D78 0008F958  2C 03 00 00 */	cmpwi r3, 0
/* 80092D7C 0008F95C  40 82 00 80 */	bne lbl_80092DFC
/* 80092D80 0008F960  7F E3 FB 78 */	mr r3, r31
/* 80092D84 0008F964  4B FF 9A AD */	bl func_8008C830
/* 80092D88 0008F968  2C 03 00 00 */	cmpwi r3, 0
/* 80092D8C 0008F96C  40 82 00 70 */	bne lbl_80092DFC
/* 80092D90 0008F970  7F E3 FB 78 */	mr r3, r31
/* 80092D94 0008F974  4B FF 9D B1 */	bl func_8008CB44
/* 80092D98 0008F978  2C 03 00 00 */	cmpwi r3, 0
/* 80092D9C 0008F97C  40 82 00 60 */	bne lbl_80092DFC
/* 80092DA0 0008F980  7F E3 FB 78 */	mr r3, r31
/* 80092DA4 0008F984  4B FF 88 B5 */	bl func_8008B658
/* 80092DA8 0008F988  2C 03 00 00 */	cmpwi r3, 0
/* 80092DAC 0008F98C  40 82 00 50 */	bne lbl_80092DFC
/* 80092DB0 0008F990  7F E3 FB 78 */	mr r3, r31
/* 80092DB4 0008F994  4B FF 8B CD */	bl func_8008B980
/* 80092DB8 0008F998  2C 03 00 00 */	cmpwi r3, 0
/* 80092DBC 0008F99C  40 82 00 40 */	bne lbl_80092DFC
/* 80092DC0 0008F9A0  7F E3 FB 78 */	mr r3, r31
/* 80092DC4 0008F9A4  4B FF 8D 81 */	bl func_8008BB44
/* 80092DC8 0008F9A8  2C 03 00 00 */	cmpwi r3, 0
/* 80092DCC 0008F9AC  40 82 00 30 */	bne lbl_80092DFC
/* 80092DD0 0008F9B0  7F E3 FB 78 */	mr r3, r31
/* 80092DD4 0008F9B4  4B FF 7C 25 */	bl func_8008A9F8
/* 80092DD8 0008F9B8  2C 03 00 00 */	cmpwi r3, 0
/* 80092DDC 0008F9BC  40 82 00 20 */	bne lbl_80092DFC
lbl_80092DE0:
/* 80092DE0 0008F9C0  7F E3 FB 78 */	mr r3, r31
/* 80092DE4 0008F9C4  48 00 6A 29 */	bl func_8009980C
/* 80092DE8 0008F9C8  2C 03 00 00 */	cmpwi r3, 0
/* 80092DEC 0008F9CC  40 82 00 10 */	bne lbl_80092DFC
/* 80092DF0 0008F9D0  7F E3 FB 78 */	mr r3, r31
/* 80092DF4 0008F9D4  48 03 82 31 */	bl func_800CB024
/* 80092DF8 0008F9D8  2C 03 00 00 */	cmpwi r3, 0
lbl_80092DFC:
/* 80092DFC 0008F9DC  80 01 00 24 */	lwz r0, 0x24(r1)
/* 80092E00 0008F9E0  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 80092E04 0008F9E4  38 21 00 20 */	addi r1, r1, 0x20
/* 80092E08 0008F9E8  7C 08 03 A6 */	mtlr r0
/* 80092E0C 0008F9EC  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

#pragma push
asm unk_t func_80092E10()
{ // clang-format off
    nofralloc
/* 80092E10 0008F9F0  7C 08 02 A6 */	mflr r0
/* 80092E14 0008F9F4  90 01 00 04 */	stw r0, 4(r1)
/* 80092E18 0008F9F8  94 21 FF F8 */	stwu r1, -8(r1)
/* 80092E1C 0008F9FC  4B FF 21 21 */	bl func_80084F3C
/* 80092E20 0008FA00  80 01 00 0C */	lwz r0, 0xc(r1)
/* 80092E24 0008FA04  38 21 00 08 */	addi r1, r1, 8
/* 80092E28 0008FA08  7C 08 03 A6 */	mtlr r0
/* 80092E2C 0008FA0C  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

#pragma push
asm unk_t func_80092E30()
{ // clang-format off
    nofralloc
/* 80092E30 0008FA10  7C 08 02 A6 */	mflr r0
/* 80092E34 0008FA14  90 01 00 04 */	stw r0, 4(r1)
/* 80092E38 0008FA18  94 21 FF F8 */	stwu r1, -8(r1)
/* 80092E3C 0008FA1C  4B FF 17 79 */	bl func_800845B4
/* 80092E40 0008FA20  80 01 00 0C */	lwz r0, 0xc(r1)
/* 80092E44 0008FA24  38 21 00 08 */	addi r1, r1, 8
/* 80092E48 0008FA28  7C 08 03 A6 */	mtlr r0
/* 80092E4C 0008FA2C  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

extern unk_t func_800C36DC();
extern unk_t func_80092F2C();

#pragma push
asm unk_t lbl_80092E50()
{ // clang-format off
    nofralloc
/* 80092E50 0008FA30  7C 08 02 A6 */	mflr r0
/* 80092E54 0008FA34  90 01 00 04 */	stw r0, 4(r1)
/* 80092E58 0008FA38  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 80092E5C 0008FA3C  93 E1 00 14 */	stw r31, 0x14(r1)
/* 80092E60 0008FA40  93 C1 00 10 */	stw r30, 0x10(r1)
/* 80092E64 0008FA44  7C 7E 1B 78 */	mr r30, r3
/* 80092E68 0008FA48  80 63 00 2C */	lwz r3, 0x2c(r3)
/* 80092E6C 0008FA4C  80 03 19 B0 */	lwz r0, 0x19b0(r3)
/* 80092E70 0008FA50  28 00 00 0A */	cmplwi r0, 0xa
/* 80092E74 0008FA54  40 82 00 0C */	bne lbl_80092E80
/* 80092E78 0008FA58  3B E0 00 01 */	li r31, 1
/* 80092E7C 0008FA5C  48 00 00 08 */	b lbl_80092E84
lbl_80092E80:
/* 80092E80 0008FA60  3B E0 00 00 */	li r31, 0
lbl_80092E84:
/* 80092E84 0008FA64  80 03 00 04 */	lwz r0, 4(r3)
/* 80092E88 0008FA68  2C 00 00 0E */	cmpwi r0, 0xe
/* 80092E8C 0008FA6C  41 82 00 08 */	beq lbl_80092E94
/* 80092E90 0008FA70  48 00 00 14 */	b lbl_80092EA4
lbl_80092E94:
/* 80092E94 0008FA74  38 7E 00 00 */	addi r3, r30, 0
/* 80092E98 0008FA78  38 9F 00 00 */	addi r4, r31, 0
/* 80092E9C 0008FA7C  48 09 97 65 */	bl func_8012C600
/* 80092EA0 0008FA80  48 00 00 10 */	b lbl_80092EB0
lbl_80092EA4:
/* 80092EA4 0008FA84  38 7E 00 00 */	addi r3, r30, 0
/* 80092EA8 0008FA88  38 9F 00 00 */	addi r4, r31, 0
/* 80092EAC 0008FA8C  48 00 00 81 */	bl func_80092F2C
lbl_80092EB0:
/* 80092EB0 0008FA90  2C 1F 00 00 */	cmpwi r31, 0
/* 80092EB4 0008FA94  41 82 00 0C */	beq lbl_80092EC0
/* 80092EB8 0008FA98  7F C3 F3 78 */	mr r3, r30
/* 80092EBC 0008FA9C  48 03 08 21 */	bl func_800C36DC
lbl_80092EC0:
/* 80092EC0 0008FAA0  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 80092EC4 0008FAA4  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 80092EC8 0008FAA8  83 C1 00 10 */	lwz r30, 0x10(r1)
/* 80092ECC 0008FAAC  38 21 00 18 */	addi r1, r1, 0x18
/* 80092ED0 0008FAB0  7C 08 03 A6 */	mtlr r0
/* 80092ED4 0008FAB4  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

#pragma push
asm f32 func_80092ED8(s32, ftLinkAttributes*, f32)
{ // clang-format off
    nofralloc
/* 80092ED8 0008FAB8  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 80092EDC 0008FABC  6C 60 80 00 */	xoris r0, r3, 0x8000
/* 80092EE0 0008FAC0  80 8D AE B4 */	lwz r4, p_ftCommonData(r13)
/* 80092EE4 0008FAC4  90 01 00 14 */	stw r0, 0x14(r1)
/* 80092EE8 0008FAC8  3C 00 43 30 */	lis r0, 0x4330
/* 80092EEC 0008FACC  C0 A4 02 E4 */	lfs f5, 0x2e4(r4)
/* 80092EF0 0008FAD0  C0 04 02 E8 */	lfs f0, 0x2e8(r4)
/* 80092EF4 0008FAD4  90 01 00 10 */	stw r0, 0x10(r1)
/* 80092EF8 0008FAD8  EC 00 28 28 */	fsubs f0, f0, f5
/* 80092EFC 0008FADC  C8 82 8B 90 */	lfd f4, lbl_804D8570(r2)
/* 80092F00 0008FAE0  C8 61 00 10 */	lfd f3, 0x10(r1)
/* 80092F04 0008FAE4  C0 42 8B 88 */	lfs f2, lbl_804D8568(r2)
/* 80092F08 0008FAE8  EC 21 28 3A */	fmadds f1, f1, f0, f5
/* 80092F0C 0008FAEC  EC 63 20 28 */	fsubs f3, f3, f4
/* 80092F10 0008FAF0  C0 84 02 8C */	lfs f4, 0x28c(r4)
/* 80092F14 0008FAF4  C0 04 02 90 */	lfs f0, 0x290(r4)
/* 80092F18 0008FAF8  EC 22 08 28 */	fsubs f1, f2, f1
/* 80092F1C 0008FAFC  EC 23 00 72 */	fmuls f1, f3, f1
/* 80092F20 0008FB00  EC 24 00 7A */	fmadds f1, f4, f1, f0
/* 80092F24 0008FB04  38 21 00 18 */	addi r1, r1, 0x18
/* 80092F28 0008FB08  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

extern f32 const lbl_804D8578;

#pragma push
asm unk_t func_80092F2C()
{ // clang-format off
    nofralloc
/* 80092F2C 0008FB0C  7C 08 02 A6 */	mflr r0
/* 80092F30 0008FB10  38 A0 00 00 */	li r5, 0
/* 80092F34 0008FB14  90 01 00 04 */	stw r0, 4(r1)
/* 80092F38 0008FB18  38 C0 00 00 */	li r6, 0
/* 80092F3C 0008FB1C  94 21 FF 88 */	stwu r1, -0x78(r1)
/* 80092F40 0008FB20  DB E1 00 70 */	stfd f31, 0x70(r1)
/* 80092F44 0008FB24  93 E1 00 6C */	stw r31, 0x6c(r1)
/* 80092F48 0008FB28  93 C1 00 68 */	stw r30, 0x68(r1)
/* 80092F4C 0008FB2C  3B C4 00 00 */	addi r30, r4, 0
/* 80092F50 0008FB30  38 80 00 B5 */	li r4, 0xb5
/* 80092F54 0008FB34  93 A1 00 64 */	stw r29, 0x64(r1)
/* 80092F58 0008FB38  3B A3 00 00 */	addi r29, r3, 0
/* 80092F5C 0008FB3C  93 81 00 60 */	stw r28, 0x60(r1)
/* 80092F60 0008FB40  C0 22 8B 58 */	lfs f1, lbl_804D8538(r2)
/* 80092F64 0008FB44  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 80092F68 0008FB48  FC 60 08 90 */	fmr f3, f1
/* 80092F6C 0008FB4C  C0 42 8B 88 */	lfs f2, lbl_804D8568(r2)
/* 80092F70 0008FB50  4B FD 64 3D */	bl Fighter_ActionStateChange_800693AC
/* 80092F74 0008FB54  3C 60 80 09 */	lis r3, func_80093240@ha
/* 80092F78 0008FB58  38 03 32 40 */	addi r0, r3, func_80093240@l
/* 80092F7C 0008FB5C  90 1F 21 D0 */	stw r0, 0x21d0(r31)
/* 80092F80 0008FB60  38 00 00 FE */	li r0, 0xfe
/* 80092F84 0008FB64  3C 60 80 09 */	lis r3, func_800932DC@ha
/* 80092F88 0008FB68  98 1F 06 70 */	stb r0, 0x670(r31)
/* 80092F8C 0008FB6C  38 03 32 DC */	addi r0, r3, func_800932DC@l
/* 80092F90 0008FB70  90 1F 21 D8 */	stw r0, 0x21d8(r31)
/* 80092F94 0008FB74  88 1F 22 1C */	lbz r0, 0x221c(r31)
/* 80092F98 0008FB78  54 00 DF FF */	rlwinm. r0, r0, 0x1b, 0x1f, 0x1f
/* 80092F9C 0008FB7C  40 82 00 70 */	bne lbl_8009300C
/* 80092FA0 0008FB80  80 7F 01 0C */	lwz r3, 0x10c(r31)
/* 80092FA4 0008FB84  80 BD 00 2C */	lwz r5, 0x2c(r29)
/* 80092FA8 0008FB88  80 63 00 08 */	lwz r3, 8(r3)
/* 80092FAC 0008FB8C  80 9F 05 E8 */	lwz r4, 0x5e8(r31)
/* 80092FB0 0008FB90  88 03 00 11 */	lbz r0, 0x11(r3)
/* 80092FB4 0008FB94  88 65 00 0C */	lbz r3, 0xc(r5)
/* 80092FB8 0008FB98  54 00 20 36 */	slwi r0, r0, 4
/* 80092FBC 0008FB9C  7F 84 00 2E */	lwzx r28, r4, r0
/* 80092FC0 0008FBA0  4B FA 35 79 */	bl Player_GetUnk45
/* 80092FC4 0008FBA4  80 0D AE 6C */	lwz r0, lbl_804D650C(r13)
/* 80092FC8 0008FBA8  54 63 10 3A */	slwi r3, r3, 2
/* 80092FCC 0008FBAC  38 9D 00 00 */	addi r4, r29, 0
/* 80092FD0 0008FBB0  4C C6 31 82 */	crclr 6
/* 80092FD4 0008FBB4  7C E0 1A 14 */	add r7, r0, r3
/* 80092FD8 0008FBB8  88 07 00 01 */	lbz r0, 1(r7)
/* 80092FDC 0008FBBC  7F 85 E3 78 */	mr r5, r28
/* 80092FE0 0008FBC0  88 C7 00 00 */	lbz r6, 0(r7)
/* 80092FE4 0008FBC4  38 60 04 19 */	li r3, 0x419
/* 80092FE8 0008FBC8  54 00 40 2E */	slwi r0, r0, 8
/* 80092FEC 0008FBCC  88 E7 00 02 */	lbz r7, 2(r7)
/* 80092FF0 0008FBD0  50 C0 82 1E */	rlwimi r0, r6, 0x10, 8, 0xf
/* 80092FF4 0008FBD4  7C E6 03 78 */	or r6, r7, r0
/* 80092FF8 0008FBD8  4B FC CD E5 */	bl ef_Spawn
/* 80092FFC 0008FBDC  88 1F 22 19 */	lbz r0, 0x2219(r31)
/* 80093000 0008FBE0  38 60 00 01 */	li r3, 1
/* 80093004 0008FBE4  50 60 3E 30 */	rlwimi r0, r3, 7, 0x18, 0x18
/* 80093008 0008FBE8  98 1F 22 19 */	stb r0, 0x2219(r31)
lbl_8009300C:
/* 8009300C 0008FBEC  80 8D AE B4 */	lwz r4, p_ftCommonData(r13)
/* 80093010 0008FBF0  3C 00 43 30 */	lis r0, 0x4330
/* 80093014 0008FBF4  80 7F 19 A4 */	lwz r3, 0x19a4(r31)
/* 80093018 0008FBF8  C0 44 02 E4 */	lfs f2, 0x2e4(r4)
/* 8009301C 0008FBFC  C0 04 02 E8 */	lfs f0, 0x2e8(r4)
/* 80093020 0008FC00  6C 63 80 00 */	xoris r3, r3, 0x8000
/* 80093024 0008FC04  90 61 00 5C */	stw r3, 0x5c(r1)
/* 80093028 0008FC08  EC 00 10 28 */	fsubs f0, f0, f2
/* 8009302C 0008FC0C  C0 3F 19 9C */	lfs f1, 0x199c(r31)
/* 80093030 0008FC10  90 01 00 58 */	stw r0, 0x58(r1)
/* 80093034 0008FC14  C8 62 8B 90 */	lfd f3, lbl_804D8570(r2)
/* 80093038 0008FC18  EC 01 10 3A */	fmadds f0, f1, f0, f2
/* 8009303C 0008FC1C  C0 22 8B 88 */	lfs f1, lbl_804D8568(r2)
/* 80093040 0008FC20  C8 41 00 58 */	lfd f2, 0x58(r1)
/* 80093044 0008FC24  EC 21 00 28 */	fsubs f1, f1, f0
/* 80093048 0008FC28  C0 84 02 8C */	lfs f4, 0x28c(r4)
/* 8009304C 0008FC2C  EC 42 18 28 */	fsubs f2, f2, f3
/* 80093050 0008FC30  C0 04 02 90 */	lfs f0, 0x290(r4)
/* 80093054 0008FC34  80 7D 00 28 */	lwz r3, 0x28(r29)
/* 80093058 0008FC38  EC 22 00 72 */	fmuls f1, f2, f1
/* 8009305C 0008FC3C  EF E4 00 7A */	fmadds f31, f4, f1, f0
/* 80093060 0008FC40  4B F7 8D E1 */	bl func_8000BE40
/* 80093064 0008FC44  C0 02 8B 98 */	lfs f0, lbl_804D8578(r2)
/* 80093068 0008FC48  7F A3 EB 78 */	mr r3, r29
/* 8009306C 0008FC4C  EC 00 08 2A */	fadds f0, f0, f1
/* 80093070 0008FC50  EC 20 F8 24 */	fdivs f1, f0, f31
/* 80093074 0008FC54  4B FD C1 1D */	bl ftAnim_SetAnimRate
/* 80093078 0008FC58  2C 1E 00 00 */	cmpwi r30, 0
/* 8009307C 0008FC5C  40 82 00 54 */	bne lbl_800930D0
/* 80093080 0008FC60  80 6D AE B4 */	lwz r3, p_ftCommonData(r13)
/* 80093084 0008FC64  88 1F 22 1C */	lbz r0, 0x221c(r31)
/* 80093088 0008FC68  C0 03 02 94 */	lfs f0, 0x294(r3)
/* 8009308C 0008FC6C  54 00 DF FF */	rlwinm. r0, r0, 0x1b, 0x1f, 0x1f
/* 80093090 0008FC70  EC 5F 00 32 */	fmuls f2, f31, f0
/* 80093094 0008FC74  40 82 00 0C */	bne lbl_800930A0
/* 80093098 0008FC78  C0 03 02 BC */	lfs f0, 0x2bc(r3)
/* 8009309C 0008FC7C  EC 42 00 32 */	fmuls f2, f2, f0
lbl_800930A0:
/* 800930A0 0008FC80  C0 03 02 98 */	lfs f0, 0x298(r3)
/* 800930A4 0008FC84  FC 02 00 40 */	fcmpo cr0, f2, f0
/* 800930A8 0008FC88  40 81 00 08 */	ble lbl_800930B0
/* 800930AC 0008FC8C  FC 40 00 90 */	fmr f2, f0
lbl_800930B0:
/* 800930B0 0008FC90  C0 3F 19 AC */	lfs f1, 0x19ac(r31)
/* 800930B4 0008FC94  C0 02 8B 58 */	lfs f0, lbl_804D8538(r2)
/* 800930B8 0008FC98  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 800930BC 0008FC9C  40 80 00 0C */	bge lbl_800930C8
/* 800930C0 0008FCA0  FC 00 10 90 */	fmr f0, f2
/* 800930C4 0008FCA4  48 00 00 08 */	b lbl_800930CC
lbl_800930C8:
/* 800930C8 0008FCA8  FC 00 10 50 */	fneg f0, f2
lbl_800930CC:
/* 800930CC 0008FCAC  D0 1F 00 EC */	stfs f0, 0xec(r31)
lbl_800930D0:
/* 800930D0 0008FCB0  83 9D 00 2C */	lwz r28, 0x2c(r29)
/* 800930D4 0008FCB4  3C 60 80 09 */	lis r3, lbl_80092E50@ha
/* 800930D8 0008FCB8  38 A3 2E 50 */	addi r5, r3, lbl_80092E50@l
/* 800930DC 0008FCBC  C0 22 8B 88 */	lfs f1, lbl_804D8568(r2)
/* 800930E0 0008FCC0  80 9C 01 0C */	lwz r4, 0x10c(r28)
/* 800930E4 0008FCC4  C0 02 8B 58 */	lfs f0, lbl_804D8538(r2)
/* 800930E8 0008FCC8  7F A3 EB 78 */	mr r3, r29
/* 800930EC 0008FCCC  80 C4 00 08 */	lwz r6, 8(r4)
/* 800930F0 0008FCD0  38 81 00 38 */	addi r4, r1, 0x38
/* 800930F4 0008FCD4  88 06 00 11 */	lbz r0, 0x11(r6)
/* 800930F8 0008FCD8  90 01 00 38 */	stw r0, 0x38(r1)
/* 800930FC 0008FCDC  D0 21 00 48 */	stfs f1, 0x48(r1)
/* 80093100 0008FCE0  D0 01 00 44 */	stfs f0, 0x44(r1)
/* 80093104 0008FCE4  D0 01 00 40 */	stfs f0, 0x40(r1)
/* 80093108 0008FCE8  D0 01 00 3C */	stfs f0, 0x3c(r1)
/* 8009310C 0008FCEC  4B FE 80 AD */	bl func_8007B1B8
/* 80093110 0008FCF0  88 1C 22 1A */	lbz r0, 0x221a(r28)
/* 80093114 0008FCF4  38 60 00 01 */	li r3, 1
/* 80093118 0008FCF8  50 60 07 FE */	rlwimi r0, r3, 0, 0x1f, 0x1f
/* 8009311C 0008FCFC  98 1C 22 1A */	stb r0, 0x221a(r28)
/* 80093120 0008FD00  80 1F 00 04 */	lwz r0, 4(r31)
/* 80093124 0008FD04  2C 00 00 0E */	cmpwi r0, 0xe
/* 80093128 0008FD08  40 82 00 0C */	bne lbl_80093134
/* 8009312C 0008FD0C  C0 1F 01 A0 */	lfs f0, 0x1a0(r31)
/* 80093130 0008FD10  48 00 00 44 */	b lbl_80093174
lbl_80093134:
/* 80093134 0008FD14  80 6D AE B4 */	lwz r3, p_ftCommonData(r13)
/* 80093138 0008FD18  C0 3F 19 98 */	lfs f1, 0x1998(r31)
/* 8009313C 0008FD1C  C0 03 02 60 */	lfs f0, 0x260(r3)
/* 80093140 0008FD20  C0 A3 02 D4 */	lfs f5, 0x2d4(r3)
/* 80093144 0008FD24  EC 61 00 24 */	fdivs f3, f1, f0
/* 80093148 0008FD28  C0 03 02 D8 */	lfs f0, 0x2d8(r3)
/* 8009314C 0008FD2C  C0 5F 19 9C */	lfs f2, 0x199c(r31)
/* 80093150 0008FD30  C0 C3 02 64 */	lfs f6, 0x264(r3)
/* 80093154 0008FD34  C0 82 8B 88 */	lfs f4, lbl_804D8568(r2)
/* 80093158 0008FD38  EC 20 28 28 */	fsubs f1, f0, f5
/* 8009315C 0008FD3C  C0 1F 01 A0 */	lfs f0, 0x1a0(r31)
/* 80093160 0008FD40  EC 84 30 28 */	fsubs f4, f4, f6
/* 80093164 0008FD44  EC 22 28 7A */	fmadds f1, f2, f1, f5
/* 80093168 0008FD48  EC 23 00 72 */	fmuls f1, f3, f1
/* 8009316C 0008FD4C  EC 24 30 7A */	fmadds f1, f4, f1, f6
/* 80093170 0008FD50  EC 01 00 32 */	fmuls f0, f1, f0
lbl_80093174:
/* 80093174 0008FD54  D0 01 00 34 */	stfs f0, 0x34(r1)
/* 80093178 0008FD58  D0 01 00 30 */	stfs f0, 0x30(r1)
/* 8009317C 0008FD5C  D0 01 00 2C */	stfs f0, 0x2c(r1)
/* 80093180 0008FD60  80 7F 01 0C */	lwz r3, 0x10c(r31)
/* 80093184 0008FD64  80 9F 05 E8 */	lwz r4, 0x5e8(r31)
/* 80093188 0008FD68  80 63 00 08 */	lwz r3, 8(r3)
/* 8009318C 0008FD6C  88 03 00 11 */	lbz r0, 0x11(r3)
/* 80093190 0008FD70  54 00 20 36 */	slwi r0, r0, 4
/* 80093194 0008FD74  7F 84 00 2E */	lwzx r28, r4, r0
/* 80093198 0008FD78  28 1C 00 00 */	cmplwi r28, 0
/* 8009319C 0008FD7C  40 82 00 14 */	bne lbl_800931B0
/* 800931A0 0008FD80  38 6D 84 58 */	addi r3, r13, lbl_804D3AF8
/* 800931A4 0008FD84  38 80 02 F8 */	li r4, 0x2f8
/* 800931A8 0008FD88  38 AD 84 60 */	addi r5, r13, lbl_804D3B00
/* 800931AC 0008FD8C  48 2F 50 75 */	bl __assert
lbl_800931B0:
/* 800931B0 0008FD90  80 61 00 2C */	lwz r3, 0x2c(r1)
/* 800931B4 0008FD94  80 01 00 30 */	lwz r0, 0x30(r1)
/* 800931B8 0008FD98  90 7C 00 2C */	stw r3, 0x2c(r28)
/* 800931BC 0008FD9C  90 1C 00 30 */	stw r0, 0x30(r28)
/* 800931C0 0008FDA0  80 01 00 34 */	lwz r0, 0x34(r1)
/* 800931C4 0008FDA4  90 1C 00 34 */	stw r0, 0x34(r28)
/* 800931C8 0008FDA8  80 1C 00 14 */	lwz r0, 0x14(r28)
/* 800931CC 0008FDAC  54 00 01 8D */	rlwinm. r0, r0, 0, 6, 6
/* 800931D0 0008FDB0  40 82 00 4C */	bne lbl_8009321C
/* 800931D4 0008FDB4  28 1C 00 00 */	cmplwi r28, 0
/* 800931D8 0008FDB8  41 82 00 44 */	beq lbl_8009321C
/* 800931DC 0008FDBC  40 82 00 14 */	bne lbl_800931F0
/* 800931E0 0008FDC0  38 6D 84 58 */	addi r3, r13, lbl_804D3AF8
/* 800931E4 0008FDC4  38 80 02 34 */	li r4, 0x234
/* 800931E8 0008FDC8  38 AD 84 60 */	addi r5, r13, lbl_804D3B00
/* 800931EC 0008FDCC  48 2F 50 35 */	bl __assert
lbl_800931F0:
/* 800931F0 0008FDD0  80 9C 00 14 */	lwz r4, 0x14(r28)
/* 800931F4 0008FDD4  38 60 00 00 */	li r3, 0
/* 800931F8 0008FDD8  54 80 02 11 */	rlwinm. r0, r4, 0, 8, 8
/* 800931FC 0008FDDC  40 82 00 10 */	bne lbl_8009320C
/* 80093200 0008FDE0  54 80 06 73 */	rlwinm. r0, r4, 0, 0x19, 0x19
/* 80093204 0008FDE4  41 82 00 08 */	beq lbl_8009320C
/* 80093208 0008FDE8  38 60 00 01 */	li r3, 1
lbl_8009320C:
/* 8009320C 0008FDEC  2C 03 00 00 */	cmpwi r3, 0
/* 80093210 0008FDF0  40 82 00 0C */	bne lbl_8009321C
/* 80093214 0008FDF4  7F 83 E3 78 */	mr r3, r28
/* 80093218 0008FDF8  48 2E 00 D1 */	bl HSD_JObjSetMtxDirtySub
lbl_8009321C:
/* 8009321C 0008FDFC  80 01 00 7C */	lwz r0, 0x7c(r1)
/* 80093220 0008FE00  CB E1 00 70 */	lfd f31, 0x70(r1)
/* 80093224 0008FE04  83 E1 00 6C */	lwz r31, 0x6c(r1)
/* 80093228 0008FE08  83 C1 00 68 */	lwz r30, 0x68(r1)
/* 8009322C 0008FE0C  83 A1 00 64 */	lwz r29, 0x64(r1)
/* 80093230 0008FE10  83 81 00 60 */	lwz r28, 0x60(r1)
/* 80093234 0008FE14  38 21 00 78 */	addi r1, r1, 0x78
/* 80093238 0008FE18  7C 08 03 A6 */	mtlr r0
/* 8009323C 0008FE1C  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

#pragma push
asm unk_t func_80093240()
{ // clang-format off
    nofralloc
/* 80093240 0008FE20  80 83 00 2C */	lwz r4, 0x2c(r3)
/* 80093244 0008FE24  88 04 22 1A */	lbz r0, 0x221a(r4)
/* 80093248 0008FE28  54 00 DF FF */	rlwinm. r0, r0, 0x1b, 0x1f, 0x1f
/* 8009324C 0008FE2C  4D 82 00 20 */	beqlr 
/* 80093250 0008FE30  80 04 00 E0 */	lwz r0, 0xe0(r4)
/* 80093254 0008FE34  2C 00 00 00 */	cmpwi r0, 0
/* 80093258 0008FE38  4C 82 00 20 */	bnelr 
/* 8009325C 0008FE3C  C0 44 06 20 */	lfs f2, 0x620(r4)
/* 80093260 0008FE40  C0 02 8B 58 */	lfs f0, lbl_804D8538(r2)
/* 80093264 0008FE44  FC 02 00 40 */	fcmpo cr0, f2, f0
/* 80093268 0008FE48  40 80 00 0C */	bge lbl_80093274
/* 8009326C 0008FE4C  FC 20 10 50 */	fneg f1, f2
/* 80093270 0008FE50  48 00 00 08 */	b lbl_80093278
lbl_80093274:
/* 80093274 0008FE54  FC 20 10 90 */	fmr f1, f2
lbl_80093278:
/* 80093278 0008FE58  80 AD AE B4 */	lwz r5, p_ftCommonData(r13)
/* 8009327C 0008FE5C  C0 05 04 B0 */	lfs f0, 0x4b0(r5)
/* 80093280 0008FE60  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 80093284 0008FE64  4C 41 13 82 */	cror 2, 1, 2
/* 80093288 0008FE68  4C 82 00 20 */	bnelr 
/* 8009328C 0008FE6C  88 64 06 70 */	lbz r3, 0x670(r4)
/* 80093290 0008FE70  80 05 04 B4 */	lwz r0, 0x4b4(r5)
/* 80093294 0008FE74  7C 03 00 00 */	cmpw r3, r0
/* 80093298 0008FE78  4C 80 00 20 */	bgelr 
/* 8009329C 0008FE7C  C0 05 04 B8 */	lfs f0, 0x4b8(r5)
/* 800932A0 0008FE80  38 00 00 FE */	li r0, 0xfe
/* 800932A4 0008FE84  C0 65 04 C0 */	lfs f3, 0x4c0(r5)
/* 800932A8 0008FE88  EC 42 00 32 */	fmuls f2, f2, f0
/* 800932AC 0008FE8C  C0 24 08 48 */	lfs f1, 0x848(r4)
/* 800932B0 0008FE90  C0 04 00 B0 */	lfs f0, 0xb0(r4)
/* 800932B4 0008FE94  EC 43 00 B2 */	fmuls f2, f3, f2
/* 800932B8 0008FE98  EC 01 00 BA */	fmadds f0, f1, f2, f0
/* 800932BC 0008FE9C  D0 04 00 B0 */	stfs f0, 0xb0(r4)
/* 800932C0 0008FEA0  C0 24 08 44 */	lfs f1, 0x844(r4)
/* 800932C4 0008FEA4  C0 04 00 B4 */	lfs f0, 0xb4(r4)
/* 800932C8 0008FEA8  FC 20 08 50 */	fneg f1, f1
/* 800932CC 0008FEAC  EC 01 00 BA */	fmadds f0, f1, f2, f0
/* 800932D0 0008FEB0  D0 04 00 B4 */	stfs f0, 0xb4(r4)
/* 800932D4 0008FEB4  98 04 06 70 */	stb r0, 0x670(r4)
/* 800932D8 0008FEB8  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

#pragma push
asm unk_t func_800932DC()
{ // clang-format off
    nofralloc
/* 800932DC 0008FEBC  80 83 00 2C */	lwz r4, 0x2c(r3)
/* 800932E0 0008FEC0  80 04 00 E0 */	lwz r0, 0xe0(r4)
/* 800932E4 0008FEC4  2C 00 00 00 */	cmpwi r0, 0
/* 800932E8 0008FEC8  4C 82 00 20 */	bnelr 
/* 800932EC 0008FECC  C0 44 06 20 */	lfs f2, 0x620(r4)
/* 800932F0 0008FED0  C0 02 8B 58 */	lfs f0, lbl_804D8538(r2)
/* 800932F4 0008FED4  FC 02 00 40 */	fcmpo cr0, f2, f0
/* 800932F8 0008FED8  40 80 00 0C */	bge lbl_80093304
/* 800932FC 0008FEDC  FC 20 10 50 */	fneg f1, f2
/* 80093300 0008FEE0  48 00 00 08 */	b lbl_80093308
lbl_80093304:
/* 80093304 0008FEE4  FC 20 10 90 */	fmr f1, f2
lbl_80093308:
/* 80093308 0008FEE8  80 AD AE B4 */	lwz r5, p_ftCommonData(r13)
/* 8009330C 0008FEEC  C0 05 04 B0 */	lfs f0, 0x4b0(r5)
/* 80093310 0008FEF0  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 80093314 0008FEF4  4C 41 13 82 */	cror 2, 1, 2
/* 80093318 0008FEF8  4C 82 00 20 */	bnelr 
/* 8009331C 0008FEFC  C0 05 04 BC */	lfs f0, 0x4bc(r5)
/* 80093320 0008FF00  C0 65 04 C0 */	lfs f3, 0x4c0(r5)
/* 80093324 0008FF04  EC 42 00 32 */	fmuls f2, f2, f0
/* 80093328 0008FF08  C0 24 08 48 */	lfs f1, 0x848(r4)
/* 8009332C 0008FF0C  C0 04 00 B0 */	lfs f0, 0xb0(r4)
/* 80093330 0008FF10  EC 43 00 B2 */	fmuls f2, f3, f2
/* 80093334 0008FF14  EC 01 00 BA */	fmadds f0, f1, f2, f0
/* 80093338 0008FF18  D0 04 00 B0 */	stfs f0, 0xb0(r4)
/* 8009333C 0008FF1C  C0 24 08 44 */	lfs f1, 0x844(r4)
/* 80093340 0008FF20  C0 04 00 B4 */	lfs f0, 0xb4(r4)
/* 80093344 0008FF24  FC 20 08 50 */	fneg f1, f1
/* 80093348 0008FF28  EC 01 00 BA */	fmadds f0, f1, f2, f0
/* 8009334C 0008FF2C  D0 04 00 B4 */	stfs f0, 0xb4(r4)
/* 80093350 0008FF30  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

#pragma push
asm unk_t func_80093354()
{ // clang-format off
    nofralloc
/* 80093354 0008FF34  7C 08 02 A6 */	mflr r0
/* 80093358 0008FF38  90 01 00 04 */	stw r0, 4(r1)
/* 8009335C 0008FF3C  94 21 FF 98 */	stwu r1, -0x68(r1)
/* 80093360 0008FF40  93 E1 00 64 */	stw r31, 0x64(r1)
/* 80093364 0008FF44  93 C1 00 60 */	stw r30, 0x60(r1)
/* 80093368 0008FF48  7C 7E 1B 78 */	mr r30, r3
/* 8009336C 0008FF4C  93 A1 00 5C */	stw r29, 0x5c(r1)
/* 80093370 0008FF50  83 A3 00 2C */	lwz r29, 0x2c(r3)
/* 80093374 0008FF54  48 00 08 4D */	bl func_80093BC0
/* 80093378 0008FF58  7F C3 F3 78 */	mr r3, r30
/* 8009337C 0008FF5C  4B FD BE BD */	bl ftAnim_IsFramesRemaining
/* 80093380 0008FF60  2C 03 00 00 */	cmpwi r3, 0
/* 80093384 0008FF64  40 82 01 88 */	bne lbl_8009350C
/* 80093388 0008FF68  80 1D 23 4C */	lwz r0, 0x234c(r29)
/* 8009338C 0008FF6C  2C 00 00 00 */	cmpwi r0, 0
/* 80093390 0008FF70  41 82 00 74 */	beq lbl_80093404
/* 80093394 0008FF74  83 BE 00 2C */	lwz r29, 0x2c(r30)
/* 80093398 0008FF78  88 9D 22 1F */	lbz r4, 0x221f(r29)
/* 8009339C 0008FF7C  88 7D 00 0C */	lbz r3, 0xc(r29)
/* 800933A0 0008FF80  C0 3D 19 98 */	lfs f1, 0x1998(r29)
/* 800933A4 0008FF84  54 84 EF FE */	rlwinm r4, r4, 0x1d, 0x1f, 0x1f
/* 800933A8 0008FF88  4B FA AD 6D */	bl func_8003E114
/* 800933AC 0008FF8C  80 1D 00 04 */	lwz r0, 4(r29)
/* 800933B0 0008FF90  2C 00 00 0E */	cmpwi r0, 0xe
/* 800933B4 0008FF94  41 82 00 08 */	beq lbl_800933BC
/* 800933B8 0008FF98  48 00 00 10 */	b lbl_800933C8
lbl_800933BC:
/* 800933BC 0008FF9C  7F C3 F3 78 */	mr r3, r30
/* 800933C0 0008FFA0  48 09 90 DD */	bl func_8012C49C
/* 800933C4 0008FFA4  48 00 02 44 */	b lbl_80093608
lbl_800933C8:
/* 800933C8 0008FFA8  C0 22 8B 58 */	lfs f1, lbl_804D8538(r2)
/* 800933CC 0008FFAC  7F C3 F3 78 */	mr r3, r30
/* 800933D0 0008FFB0  83 BE 00 2C */	lwz r29, 0x2c(r30)
/* 800933D4 0008FFB4  38 80 00 B4 */	li r4, 0xb4
/* 800933D8 0008FFB8  FC 60 08 90 */	fmr f3, f1
/* 800933DC 0008FFBC  C0 42 8B 88 */	lfs f2, lbl_804D8568(r2)
/* 800933E0 0008FFC0  38 A0 00 00 */	li r5, 0
/* 800933E4 0008FFC4  38 C0 00 00 */	li r6, 0
/* 800933E8 0008FFC8  4B FD 5F C5 */	bl Fighter_ActionStateChange_800693AC
/* 800933EC 0008FFCC  38 7D 00 00 */	addi r3, r29, 0
/* 800933F0 0008FFD0  38 80 00 7F */	li r4, 0x7f
/* 800933F4 0008FFD4  38 A0 00 7F */	li r5, 0x7f
/* 800933F8 0008FFD8  38 C0 00 40 */	li r6, 0x40
/* 800933FC 0008FFDC  4B FF 4D 4D */	bl func_80088148
/* 80093400 0008FFE0  48 00 02 08 */	b lbl_80093608
lbl_80093404:
/* 80093404 0008FFE4  83 FE 00 2C */	lwz r31, 0x2c(r30)
/* 80093408 0008FFE8  80 1F 00 04 */	lwz r0, 4(r31)
/* 8009340C 0008FFEC  2C 00 00 0E */	cmpwi r0, 0xe
/* 80093410 0008FFF0  41 82 00 08 */	beq lbl_80093418
/* 80093414 0008FFF4  48 00 00 10 */	b lbl_80093424
lbl_80093418:
/* 80093418 0008FFF8  7F C3 F3 78 */	mr r3, r30
/* 8009341C 0008FFFC  48 09 8D B9 */	bl func_8012C1D4
/* 80093420 00090000  48 00 01 E8 */	b lbl_80093608
lbl_80093424:
/* 80093424 00090004  C0 22 8B 58 */	lfs f1, lbl_804D8538(r2)
/* 80093428 00090008  7F C3 F3 78 */	mr r3, r30
/* 8009342C 0009000C  C0 42 8B 88 */	lfs f2, lbl_804D8568(r2)
/* 80093430 00090010  38 80 00 B3 */	li r4, 0xb3
/* 80093434 00090014  FC 60 08 90 */	fmr f3, f1
/* 80093438 00090018  3C A0 20 00 */	lis r5, 0x2000
/* 8009343C 0009001C  38 C0 00 00 */	li r6, 0
/* 80093440 00090020  4B FD 5F 6D */	bl Fighter_ActionStateChange_800693AC
/* 80093444 00090024  80 7F 01 0C */	lwz r3, 0x10c(r31)
/* 80093448 00090028  80 BE 00 2C */	lwz r5, 0x2c(r30)
/* 8009344C 0009002C  80 63 00 08 */	lwz r3, 8(r3)
/* 80093450 00090030  80 9F 05 E8 */	lwz r4, 0x5e8(r31)
/* 80093454 00090034  88 03 00 11 */	lbz r0, 0x11(r3)
/* 80093458 00090038  88 65 00 0C */	lbz r3, 0xc(r5)
/* 8009345C 0009003C  54 00 20 36 */	slwi r0, r0, 4
/* 80093460 00090040  7F A4 00 2E */	lwzx r29, r4, r0
/* 80093464 00090044  4B FA 30 D5 */	bl Player_GetUnk45
/* 80093468 00090048  80 0D AE 6C */	lwz r0, lbl_804D650C(r13)
/* 8009346C 0009004C  54 63 10 3A */	slwi r3, r3, 2
/* 80093470 00090050  38 9E 00 00 */	addi r4, r30, 0
/* 80093474 00090054  4C C6 31 82 */	crclr 6
/* 80093478 00090058  7C E0 1A 14 */	add r7, r0, r3
/* 8009347C 0009005C  88 07 00 01 */	lbz r0, 1(r7)
/* 80093480 00090060  7F A5 EB 78 */	mr r5, r29
/* 80093484 00090064  88 C7 00 00 */	lbz r6, 0(r7)
/* 80093488 00090068  38 60 04 18 */	li r3, 0x418
/* 8009348C 0009006C  54 00 40 2E */	slwi r0, r0, 8
/* 80093490 00090070  88 E7 00 02 */	lbz r7, 2(r7)
/* 80093494 00090074  50 C0 82 1E */	rlwimi r0, r6, 0x10, 8, 0xf
/* 80093498 00090078  7C E6 03 78 */	or r6, r7, r0
/* 8009349C 0009007C  4B FC C9 41 */	bl ef_Spawn
/* 800934A0 00090080  88 1F 22 19 */	lbz r0, 0x2219(r31)
/* 800934A4 00090084  3B A0 00 01 */	li r29, 1
/* 800934A8 00090088  53 A0 3E 30 */	rlwimi r0, r29, 7, 0x18, 0x18
/* 800934AC 0009008C  98 1F 22 19 */	stb r0, 0x2219(r31)
/* 800934B0 00090090  3C 60 80 09 */	lis r3, lbl_80092E50@ha
/* 800934B4 00090094  38 A3 2E 50 */	addi r5, r3, lbl_80092E50@l
/* 800934B8 00090098  83 FE 00 2C */	lwz r31, 0x2c(r30)
/* 800934BC 0009009C  7F C3 F3 78 */	mr r3, r30
/* 800934C0 000900A0  C0 22 8B 88 */	lfs f1, lbl_804D8568(r2)
/* 800934C4 000900A4  38 81 00 30 */	addi r4, r1, 0x30
/* 800934C8 000900A8  80 DF 01 0C */	lwz r6, 0x10c(r31)
/* 800934CC 000900AC  C0 02 8B 58 */	lfs f0, lbl_804D8538(r2)
/* 800934D0 000900B0  80 C6 00 08 */	lwz r6, 8(r6)
/* 800934D4 000900B4  88 06 00 11 */	lbz r0, 0x11(r6)
/* 800934D8 000900B8  90 01 00 30 */	stw r0, 0x30(r1)
/* 800934DC 000900BC  D0 21 00 40 */	stfs f1, 0x40(r1)
/* 800934E0 000900C0  D0 01 00 3C */	stfs f0, 0x3c(r1)
/* 800934E4 000900C4  D0 01 00 38 */	stfs f0, 0x38(r1)
/* 800934E8 000900C8  D0 01 00 34 */	stfs f0, 0x34(r1)
/* 800934EC 000900CC  4B FE 7C CD */	bl func_8007B1B8
/* 800934F0 000900D0  88 1F 22 1A */	lbz r0, 0x221a(r31)
/* 800934F4 000900D4  53 A0 07 FE */	rlwimi r0, r29, 0, 0x1f, 0x1f
/* 800934F8 000900D8  38 7E 00 00 */	addi r3, r30, 0
/* 800934FC 000900DC  98 1F 22 1A */	stb r0, 0x221a(r31)
/* 80093500 000900E0  C0 22 8B 88 */	lfs f1, lbl_804D8568(r2)
/* 80093504 000900E4  4B FF E9 75 */	bl func_80091E78
/* 80093508 000900E8  48 00 01 00 */	b lbl_80093608
lbl_8009350C:
/* 8009350C 000900EC  80 1D 00 04 */	lwz r0, 4(r29)
/* 80093510 000900F0  2C 00 00 0E */	cmpwi r0, 0xe
/* 80093514 000900F4  40 82 00 0C */	bne lbl_80093520
/* 80093518 000900F8  C0 1D 01 A0 */	lfs f0, 0x1a0(r29)
/* 8009351C 000900FC  48 00 00 44 */	b lbl_80093560
lbl_80093520:
/* 80093520 00090100  80 6D AE B4 */	lwz r3, p_ftCommonData(r13)
/* 80093524 00090104  C0 3D 19 98 */	lfs f1, 0x1998(r29)
/* 80093528 00090108  C0 03 02 60 */	lfs f0, 0x260(r3)
/* 8009352C 0009010C  C0 A3 02 D4 */	lfs f5, 0x2d4(r3)
/* 80093530 00090110  EC 61 00 24 */	fdivs f3, f1, f0
/* 80093534 00090114  C0 03 02 D8 */	lfs f0, 0x2d8(r3)
/* 80093538 00090118  C0 5D 19 9C */	lfs f2, 0x199c(r29)
/* 8009353C 0009011C  C0 C3 02 64 */	lfs f6, 0x264(r3)
/* 80093540 00090120  C0 82 8B 88 */	lfs f4, lbl_804D8568(r2)
/* 80093544 00090124  EC 20 28 28 */	fsubs f1, f0, f5
/* 80093548 00090128  C0 1D 01 A0 */	lfs f0, 0x1a0(r29)
/* 8009354C 0009012C  EC 84 30 28 */	fsubs f4, f4, f6
/* 80093550 00090130  EC 22 28 7A */	fmadds f1, f2, f1, f5
/* 80093554 00090134  EC 23 00 72 */	fmuls f1, f3, f1
/* 80093558 00090138  EC 24 30 7A */	fmadds f1, f4, f1, f6
/* 8009355C 0009013C  EC 01 00 32 */	fmuls f0, f1, f0
lbl_80093560:
/* 80093560 00090140  D0 01 00 50 */	stfs f0, 0x50(r1)
/* 80093564 00090144  D0 01 00 4C */	stfs f0, 0x4c(r1)
/* 80093568 00090148  D0 01 00 48 */	stfs f0, 0x48(r1)
/* 8009356C 0009014C  80 7D 01 0C */	lwz r3, 0x10c(r29)
/* 80093570 00090150  80 9D 05 E8 */	lwz r4, 0x5e8(r29)
/* 80093574 00090154  80 63 00 08 */	lwz r3, 8(r3)
/* 80093578 00090158  88 03 00 11 */	lbz r0, 0x11(r3)
/* 8009357C 0009015C  54 00 20 36 */	slwi r0, r0, 4
/* 80093580 00090160  7F A4 00 2E */	lwzx r29, r4, r0
/* 80093584 00090164  28 1D 00 00 */	cmplwi r29, 0
/* 80093588 00090168  40 82 00 14 */	bne lbl_8009359C
/* 8009358C 0009016C  38 6D 84 58 */	addi r3, r13, lbl_804D3AF8
/* 80093590 00090170  38 80 02 F8 */	li r4, 0x2f8
/* 80093594 00090174  38 AD 84 60 */	addi r5, r13, lbl_804D3B00
/* 80093598 00090178  48 2F 4C 89 */	bl __assert
lbl_8009359C:
/* 8009359C 0009017C  80 61 00 48 */	lwz r3, 0x48(r1)
/* 800935A0 00090180  80 01 00 4C */	lwz r0, 0x4c(r1)
/* 800935A4 00090184  90 7D 00 2C */	stw r3, 0x2c(r29)
/* 800935A8 00090188  90 1D 00 30 */	stw r0, 0x30(r29)
/* 800935AC 0009018C  80 01 00 50 */	lwz r0, 0x50(r1)
/* 800935B0 00090190  90 1D 00 34 */	stw r0, 0x34(r29)
/* 800935B4 00090194  80 1D 00 14 */	lwz r0, 0x14(r29)
/* 800935B8 00090198  54 00 01 8D */	rlwinm. r0, r0, 0, 6, 6
/* 800935BC 0009019C  40 82 00 4C */	bne lbl_80093608
/* 800935C0 000901A0  28 1D 00 00 */	cmplwi r29, 0
/* 800935C4 000901A4  41 82 00 44 */	beq lbl_80093608
/* 800935C8 000901A8  40 82 00 14 */	bne lbl_800935DC
/* 800935CC 000901AC  38 6D 84 58 */	addi r3, r13, lbl_804D3AF8
/* 800935D0 000901B0  38 80 02 34 */	li r4, 0x234
/* 800935D4 000901B4  38 AD 84 60 */	addi r5, r13, lbl_804D3B00
/* 800935D8 000901B8  48 2F 4C 49 */	bl __assert
lbl_800935DC:
/* 800935DC 000901BC  80 9D 00 14 */	lwz r4, 0x14(r29)
/* 800935E0 000901C0  38 60 00 00 */	li r3, 0
/* 800935E4 000901C4  54 80 02 11 */	rlwinm. r0, r4, 0, 8, 8
/* 800935E8 000901C8  40 82 00 10 */	bne lbl_800935F8
/* 800935EC 000901CC  54 80 06 73 */	rlwinm. r0, r4, 0, 0x19, 0x19
/* 800935F0 000901D0  41 82 00 08 */	beq lbl_800935F8
/* 800935F4 000901D4  38 60 00 01 */	li r3, 1
lbl_800935F8:
/* 800935F8 000901D8  2C 03 00 00 */	cmpwi r3, 0
/* 800935FC 000901DC  40 82 00 0C */	bne lbl_80093608
/* 80093600 000901E0  7F A3 EB 78 */	mr r3, r29
/* 80093604 000901E4  48 2D FC E5 */	bl HSD_JObjSetMtxDirtySub
lbl_80093608:
/* 80093608 000901E8  80 01 00 6C */	lwz r0, 0x6c(r1)
/* 8009360C 000901EC  83 E1 00 64 */	lwz r31, 0x64(r1)
/* 80093610 000901F0  83 C1 00 60 */	lwz r30, 0x60(r1)
/* 80093614 000901F4  83 A1 00 5C */	lwz r29, 0x5c(r1)
/* 80093618 000901F8  38 21 00 68 */	addi r1, r1, 0x68
/* 8009361C 000901FC  7C 08 03 A6 */	mtlr r0
/* 80093620 00090200  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

void func_80093624(void)
{
    return;
}

#pragma push
asm unk_t func_80093628()
{ // clang-format off
    nofralloc
/* 80093628 00090208  7C 08 02 A6 */	mflr r0
/* 8009362C 0009020C  90 01 00 04 */	stw r0, 4(r1)
/* 80093630 00090210  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 80093634 00090214  93 E1 00 14 */	stw r31, 0x14(r1)
/* 80093638 00090218  7C 7F 1B 78 */	mr r31, r3
/* 8009363C 0009021C  4B FF 19 01 */	bl func_80084F3C
/* 80093640 00090220  7F E3 FB 78 */	mr r3, r31
/* 80093644 00090224  4B FE 78 9D */	bl func_8007AEE0
/* 80093648 00090228  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 8009364C 0009022C  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 80093650 00090230  38 21 00 18 */	addi r1, r1, 0x18
/* 80093654 00090234  7C 08 03 A6 */	mtlr r0
/* 80093658 00090238  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

#pragma push
asm unk_t func_8009365C()
{ // clang-format off
    nofralloc
/* 8009365C 0009023C  7C 08 02 A6 */	mflr r0
/* 80093660 00090240  90 01 00 04 */	stw r0, 4(r1)
/* 80093664 00090244  94 21 FF F8 */	stwu r1, -8(r1)
/* 80093668 00090248  80 83 00 2C */	lwz r4, 0x2c(r3)
/* 8009366C 0009024C  88 04 22 1A */	lbz r0, 0x221a(r4)
/* 80093670 00090250  54 00 DF FF */	rlwinm. r0, r0, 0x1b, 0x1f, 0x1f
/* 80093674 00090254  40 82 00 0C */	bne lbl_80093680
/* 80093678 00090258  4B FF 0F 3D */	bl func_800845B4
/* 8009367C 0009025C  48 00 00 08 */	b lbl_80093684
lbl_80093680:
/* 80093680 00090260  4B FF 0A 85 */	bl func_80084104
lbl_80093684:
/* 80093684 00090264  80 01 00 0C */	lwz r0, 0xc(r1)
/* 80093688 00090268  38 21 00 08 */	addi r1, r1, 8
/* 8009368C 0009026C  7C 08 03 A6 */	mtlr r0
/* 80093690 00090270  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

extern unk_t func_80093850();

#pragma push
asm BOOL func_80093694()
{ // clang-format off
    nofralloc
/* 80093694 00090274  7C 08 02 A6 */	mflr r0
/* 80093698 00090278  90 01 00 04 */	stw r0, 4(r1)
/* 8009369C 0009027C  3C 00 43 30 */	lis r0, 0x4330
/* 800936A0 00090280  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 800936A4 00090284  80 8D AE B4 */	lwz r4, p_ftCommonData(r13)
/* 800936A8 00090288  80 A3 00 2C */	lwz r5, 0x2c(r3)
/* 800936AC 0009028C  80 C4 02 A0 */	lwz r6, 0x2a0(r4)
/* 800936B0 00090290  C8 22 8B 90 */	lfd f1, lbl_804D8570(r2)
/* 800936B4 00090294  6C C4 80 00 */	xoris r4, r6, 0x8000
/* 800936B8 00090298  C0 45 23 40 */	lfs f2, 0x2340(r5)
/* 800936BC 0009029C  90 81 00 14 */	stw r4, 0x14(r1)
/* 800936C0 000902A0  90 01 00 10 */	stw r0, 0x10(r1)
/* 800936C4 000902A4  C8 01 00 10 */	lfd f0, 0x10(r1)
/* 800936C8 000902A8  EC 00 08 28 */	fsubs f0, f0, f1
/* 800936CC 000902AC  FC 02 00 40 */	fcmpo cr0, f2, f0
/* 800936D0 000902B0  40 80 00 28 */	bge lbl_800936F8
/* 800936D4 000902B4  80 05 06 68 */	lwz r0, 0x668(r5)
/* 800936D8 000902B8  54 00 06 75 */	rlwinm. r0, r0, 0, 0x19, 0x1a
/* 800936DC 000902BC  41 82 00 1C */	beq lbl_800936F8
/* 800936E0 000902C0  88 05 06 72 */	lbz r0, 0x672(r5)
/* 800936E4 000902C4  7C 00 30 00 */	cmpw r0, r6
/* 800936E8 000902C8  40 80 00 10 */	bge lbl_800936F8
/* 800936EC 000902CC  48 00 01 65 */	bl func_80093850
/* 800936F0 000902D0  38 60 00 01 */	li r3, 1
/* 800936F4 000902D4  48 00 00 08 */	b lbl_800936FC
lbl_800936F8:
/* 800936F8 000902D8  38 60 00 00 */	li r3, 0
lbl_800936FC:
/* 800936FC 000902DC  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 80093700 000902E0  38 21 00 18 */	addi r1, r1, 0x18
/* 80093704 000902E4  7C 08 03 A6 */	mtlr r0
/* 80093708 000902E8  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

#pragma push
asm unk_t func_8009370C()
{ // clang-format off
    nofralloc
/* 8009370C 000902EC  7C 08 02 A6 */	mflr r0
/* 80093710 000902F0  90 01 00 04 */	stw r0, 4(r1)
/* 80093714 000902F4  38 00 00 01 */	li r0, 1
/* 80093718 000902F8  94 21 FF C0 */	stwu r1, -0x40(r1)
/* 8009371C 000902FC  81 03 00 2C */	lwz r8, 0x2c(r3)
/* 80093720 00090300  C0 02 8B 58 */	lfs f0, lbl_804D8538(r2)
/* 80093724 00090304  80 A8 01 0C */	lwz r5, 0x10c(r8)
/* 80093728 00090308  80 ED AE B4 */	lwz r7, p_ftCommonData(r13)
/* 8009372C 0009030C  80 C5 00 08 */	lwz r6, 8(r5)
/* 80093730 00090310  38 A4 00 00 */	addi r5, r4, 0
/* 80093734 00090314  38 81 00 14 */	addi r4, r1, 0x14
/* 80093738 00090318  88 C6 00 11 */	lbz r6, 0x11(r6)
/* 8009373C 0009031C  90 C1 00 14 */	stw r6, 0x14(r1)
/* 80093740 00090320  C0 28 19 98 */	lfs f1, 0x1998(r8)
/* 80093744 00090324  FC 20 08 1E */	fctiwz f1, f1
/* 80093748 00090328  D8 21 00 38 */	stfd f1, 0x38(r1)
/* 8009374C 0009032C  80 C1 00 3C */	lwz r6, 0x3c(r1)
/* 80093750 00090330  90 C1 00 18 */	stw r6, 0x18(r1)
/* 80093754 00090334  D0 01 00 24 */	stfs f0, 0x24(r1)
/* 80093758 00090338  D0 01 00 20 */	stfs f0, 0x20(r1)
/* 8009375C 0009033C  D0 01 00 1C */	stfs f0, 0x1c(r1)
/* 80093760 00090340  C0 07 02 A8 */	lfs f0, 0x2a8(r7)
/* 80093764 00090344  D0 01 00 28 */	stfs f0, 0x28(r1)
/* 80093768 00090348  C0 07 02 AC */	lfs f0, 0x2ac(r7)
/* 8009376C 0009034C  D0 01 00 2C */	stfs f0, 0x2c(r1)
/* 80093770 00090350  C0 07 02 B0 */	lfs f0, 0x2b0(r7)
/* 80093774 00090354  D0 01 00 30 */	stfs f0, 0x30(r1)
/* 80093778 00090358  98 01 00 34 */	stb r0, 0x34(r1)
/* 8009377C 0009035C  4B FE 7A C1 */	bl ftColl_CreateReflectHit
/* 80093780 00090360  80 01 00 44 */	lwz r0, 0x44(r1)
/* 80093784 00090364  38 21 00 40 */	addi r1, r1, 0x40
/* 80093788 00090368  7C 08 03 A6 */	mtlr r0
/* 8009378C 0009036C  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

#pragma push
asm unk_t lbl_80093790()
{ // clang-format off
    nofralloc
/* 80093790 00090370  7C 08 02 A6 */	mflr r0
/* 80093794 00090374  90 01 00 04 */	stw r0, 4(r1)
/* 80093798 00090378  94 21 FF D8 */	stwu r1, -0x28(r1)
/* 8009379C 0009037C  93 E1 00 24 */	stw r31, 0x24(r1)
/* 800937A0 00090380  93 C1 00 20 */	stw r30, 0x20(r1)
/* 800937A4 00090384  93 A1 00 1C */	stw r29, 0x1c(r1)
/* 800937A8 00090388  7C 7D 1B 78 */	mr r29, r3
/* 800937AC 0009038C  83 C3 00 2C */	lwz r30, 0x2c(r3)
/* 800937B0 00090390  4B FE A3 75 */	bl func_8007DB24
/* 800937B4 00090394  80 7E 01 0C */	lwz r3, 0x10c(r30)
/* 800937B8 00090398  80 BD 00 2C */	lwz r5, 0x2c(r29)
/* 800937BC 0009039C  80 63 00 08 */	lwz r3, 8(r3)
/* 800937C0 000903A0  80 9E 05 E8 */	lwz r4, 0x5e8(r30)
/* 800937C4 000903A4  88 03 00 11 */	lbz r0, 0x11(r3)
/* 800937C8 000903A8  88 65 00 0C */	lbz r3, 0xc(r5)
/* 800937CC 000903AC  54 00 20 36 */	slwi r0, r0, 4
/* 800937D0 000903B0  7F E4 00 2E */	lwzx r31, r4, r0
/* 800937D4 000903B4  4B FA 2D 65 */	bl Player_GetUnk45
/* 800937D8 000903B8  80 0D AE 6C */	lwz r0, lbl_804D650C(r13)
/* 800937DC 000903BC  54 63 10 3A */	slwi r3, r3, 2
/* 800937E0 000903C0  38 9D 00 00 */	addi r4, r29, 0
/* 800937E4 000903C4  4C C6 31 82 */	crclr 6
/* 800937E8 000903C8  7C E0 1A 14 */	add r7, r0, r3
/* 800937EC 000903CC  88 07 00 01 */	lbz r0, 1(r7)
/* 800937F0 000903D0  7F E5 FB 78 */	mr r5, r31
/* 800937F4 000903D4  88 C7 00 00 */	lbz r6, 0(r7)
/* 800937F8 000903D8  38 60 04 1A */	li r3, 0x41a
/* 800937FC 000903DC  54 00 40 2E */	slwi r0, r0, 8
/* 80093800 000903E0  88 E7 00 02 */	lbz r7, 2(r7)
/* 80093804 000903E4  50 C0 82 1E */	rlwimi r0, r6, 0x10, 8, 0xf
/* 80093808 000903E8  7C E6 03 78 */	or r6, r7, r0
/* 8009380C 000903EC  4B FC C5 D1 */	bl ef_Spawn
/* 80093810 000903F0  88 1E 22 19 */	lbz r0, 0x2219(r30)
/* 80093814 000903F4  38 60 00 01 */	li r3, 1
/* 80093818 000903F8  50 60 3E 30 */	rlwimi r0, r3, 7, 0x18, 0x18
/* 8009381C 000903FC  98 1E 22 19 */	stb r0, 0x2219(r30)
/* 80093820 00090400  38 7E 00 00 */	addi r3, r30, 0
/* 80093824 00090404  38 80 00 80 */	li r4, 0x80
/* 80093828 00090408  38 A0 00 7F */	li r5, 0x7f
/* 8009382C 0009040C  38 C0 00 40 */	li r6, 0x40
/* 80093830 00090410  4B FF 49 19 */	bl func_80088148
/* 80093834 00090414  80 01 00 2C */	lwz r0, 0x2c(r1)
/* 80093838 00090418  83 E1 00 24 */	lwz r31, 0x24(r1)
/* 8009383C 0009041C  83 C1 00 20 */	lwz r30, 0x20(r1)
/* 80093840 00090420  83 A1 00 1C */	lwz r29, 0x1c(r1)
/* 80093844 00090424  38 21 00 28 */	addi r1, r1, 0x28
/* 80093848 00090428  7C 08 03 A6 */	mtlr r0
/* 8009384C 0009042C  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

extern unk_t func_8009388C();

#pragma push
asm unk_t func_80093850()
{ // clang-format off
    nofralloc
/* 80093850 00090430  7C 08 02 A6 */	mflr r0
/* 80093854 00090434  90 01 00 04 */	stw r0, 4(r1)
/* 80093858 00090438  94 21 FF F8 */	stwu r1, -8(r1)
/* 8009385C 0009043C  80 83 00 2C */	lwz r4, 0x2c(r3)
/* 80093860 00090440  80 04 00 04 */	lwz r0, 4(r4)
/* 80093864 00090444  2C 00 00 0E */	cmpwi r0, 0xe
/* 80093868 00090448  41 82 00 08 */	beq lbl_80093870
/* 8009386C 0009044C  48 00 00 0C */	b lbl_80093878
lbl_80093870:
/* 80093870 00090450  48 09 8F E1 */	bl func_8012C850
/* 80093874 00090454  48 00 00 08 */	b lbl_8009387C
lbl_80093878:
/* 80093878 00090458  48 00 00 15 */	bl func_8009388C
lbl_8009387C:
/* 8009387C 0009045C  80 01 00 0C */	lwz r0, 0xc(r1)
/* 80093880 00090460  38 21 00 08 */	addi r1, r1, 8
/* 80093884 00090464  7C 08 03 A6 */	mtlr r0
/* 80093888 00090468  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

#pragma push
asm unk_t func_8009388C()
{ // clang-format off
    nofralloc
/* 8009388C 0009046C  7C 08 02 A6 */	mflr r0
/* 80093890 00090470  3C 80 20 00 */	lis r4, 0x20000002@ha
/* 80093894 00090474  90 01 00 04 */	stw r0, 4(r1)
/* 80093898 00090478  38 A4 00 02 */	addi r5, r4, 0x20000002@l
/* 8009389C 0009047C  38 80 00 B6 */	li r4, 0xb6
/* 800938A0 00090480  94 21 FF B8 */	stwu r1, -0x48(r1)
/* 800938A4 00090484  38 C0 00 00 */	li r6, 0
/* 800938A8 00090488  93 E1 00 44 */	stw r31, 0x44(r1)
/* 800938AC 0009048C  93 C1 00 40 */	stw r30, 0x40(r1)
/* 800938B0 00090490  7C 7E 1B 78 */	mr r30, r3
/* 800938B4 00090494  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 800938B8 00090498  C0 42 8B 88 */	lfs f2, lbl_804D8568(r2)
/* 800938BC 0009049C  C0 62 8B 58 */	lfs f3, lbl_804D8538(r2)
/* 800938C0 000904A0  C0 3F 08 94 */	lfs f1, 0x894(r31)
/* 800938C4 000904A4  4B FD 5A E9 */	bl Fighter_ActionStateChange_800693AC
/* 800938C8 000904A8  38 00 00 FE */	li r0, 0xfe
/* 800938CC 000904AC  98 1F 06 72 */	stb r0, 0x672(r31)
/* 800938D0 000904B0  3C 60 80 09 */	lis r3, lbl_80093790@ha
/* 800938D4 000904B4  38 A3 37 90 */	addi r5, r3, lbl_80093790@l
/* 800938D8 000904B8  88 1F 22 1A */	lbz r0, 0x221a(r31)
/* 800938DC 000904BC  38 C0 00 00 */	li r6, 0
/* 800938E0 000904C0  50 C0 07 FE */	rlwimi r0, r6, 0, 0x1f, 0x1f
/* 800938E4 000904C4  98 1F 22 1A */	stb r0, 0x221a(r31)
/* 800938E8 000904C8  38 E0 00 01 */	li r7, 1
/* 800938EC 000904CC  38 7E 00 00 */	addi r3, r30, 0
/* 800938F0 000904D0  88 1F 22 1B */	lbz r0, 0x221b(r31)
/* 800938F4 000904D4  50 C0 3E 30 */	rlwimi r0, r6, 7, 0x18, 0x18
/* 800938F8 000904D8  38 81 00 14 */	addi r4, r1, 0x14
/* 800938FC 000904DC  98 1F 22 1B */	stb r0, 0x221b(r31)
/* 80093900 000904E0  88 1F 22 1C */	lbz r0, 0x221c(r31)
/* 80093904 000904E4  50 E0 26 F6 */	rlwimi r0, r7, 4, 0x1b, 0x1b
/* 80093908 000904E8  98 1F 22 1C */	stb r0, 0x221c(r31)
/* 8009390C 000904EC  88 1F 22 1C */	lbz r0, 0x221c(r31)
/* 80093910 000904F0  50 E0 36 72 */	rlwimi r0, r7, 6, 0x19, 0x19
/* 80093914 000904F4  98 1F 22 1C */	stb r0, 0x221c(r31)
/* 80093918 000904F8  88 1F 22 1C */	lbz r0, 0x221c(r31)
/* 8009391C 000904FC  50 E0 2E B4 */	rlwimi r0, r7, 5, 0x1a, 0x1a
/* 80093920 00090500  98 1F 22 1C */	stb r0, 0x221c(r31)
/* 80093924 00090504  90 DF 23 5C */	stw r6, 0x235c(r31)
/* 80093928 00090508  80 CD AE B4 */	lwz r6, p_ftCommonData(r13)
/* 8009392C 0009050C  C0 06 02 A4 */	lfs f0, 0x2a4(r6)
/* 80093930 00090510  D0 1F 23 54 */	stfs f0, 0x2354(r31)
/* 80093934 00090514  80 CD AE B4 */	lwz r6, p_ftCommonData(r13)
/* 80093938 00090518  C0 06 02 B4 */	lfs f0, 0x2b4(r6)
/* 8009393C 0009051C  D0 1F 23 58 */	stfs f0, 0x2358(r31)
/* 80093940 00090520  81 1E 00 2C */	lwz r8, 0x2c(r30)
/* 80093944 00090524  C0 02 8B 58 */	lfs f0, lbl_804D8538(r2)
/* 80093948 00090528  80 C8 01 0C */	lwz r6, 0x10c(r8)
/* 8009394C 0009052C  81 2D AE B4 */	lwz r9, p_ftCommonData(r13)
/* 80093950 00090530  80 C6 00 08 */	lwz r6, 8(r6)
/* 80093954 00090534  88 06 00 11 */	lbz r0, 0x11(r6)
/* 80093958 00090538  90 01 00 14 */	stw r0, 0x14(r1)
/* 8009395C 0009053C  C0 28 19 98 */	lfs f1, 0x1998(r8)
/* 80093960 00090540  FC 20 08 1E */	fctiwz f1, f1
/* 80093964 00090544  D8 21 00 38 */	stfd f1, 0x38(r1)
/* 80093968 00090548  80 01 00 3C */	lwz r0, 0x3c(r1)
/* 8009396C 0009054C  90 01 00 18 */	stw r0, 0x18(r1)
/* 80093970 00090550  D0 01 00 24 */	stfs f0, 0x24(r1)
/* 80093974 00090554  D0 01 00 20 */	stfs f0, 0x20(r1)
/* 80093978 00090558  D0 01 00 1C */	stfs f0, 0x1c(r1)
/* 8009397C 0009055C  C0 09 02 A8 */	lfs f0, 0x2a8(r9)
/* 80093980 00090560  D0 01 00 28 */	stfs f0, 0x28(r1)
/* 80093984 00090564  C0 09 02 AC */	lfs f0, 0x2ac(r9)
/* 80093988 00090568  D0 01 00 2C */	stfs f0, 0x2c(r1)
/* 8009398C 0009056C  C0 09 02 B0 */	lfs f0, 0x2b0(r9)
/* 80093990 00090570  D0 01 00 30 */	stfs f0, 0x30(r1)
/* 80093994 00090574  98 E1 00 34 */	stb r7, 0x34(r1)
/* 80093998 00090578  4B FE 78 A5 */	bl ftColl_CreateReflectHit
/* 8009399C 0009057C  80 01 00 4C */	lwz r0, 0x4c(r1)
/* 800939A0 00090580  83 E1 00 44 */	lwz r31, 0x44(r1)
/* 800939A4 00090584  83 C1 00 40 */	lwz r30, 0x40(r1)
/* 800939A8 00090588  38 21 00 48 */	addi r1, r1, 0x48
/* 800939AC 0009058C  7C 08 03 A6 */	mtlr r0
/* 800939B0 00090590  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

extern unk_t func_80093A50();
extern unk_t func_8012C914();

#pragma push
asm unk_t func_800939B4()
{ // clang-format off
    nofralloc
/* 800939B4 00090594  7C 08 02 A6 */	mflr r0
/* 800939B8 00090598  90 01 00 04 */	stw r0, 4(r1)
/* 800939BC 0009059C  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 800939C0 000905A0  93 E1 00 14 */	stw r31, 0x14(r1)
/* 800939C4 000905A4  93 C1 00 10 */	stw r30, 0x10(r1)
/* 800939C8 000905A8  7C 7E 1B 78 */	mr r30, r3
/* 800939CC 000905AC  80 63 00 2C */	lwz r3, 0x2c(r3)
/* 800939D0 000905B0  80 03 00 04 */	lwz r0, 4(r3)
/* 800939D4 000905B4  3B E3 00 00 */	addi r31, r3, 0
/* 800939D8 000905B8  2C 00 00 12 */	cmpwi r0, 0x12
/* 800939DC 000905BC  41 82 00 20 */	beq lbl_800939FC
/* 800939E0 000905C0  40 80 00 50 */	bge lbl_80093A30
/* 800939E4 000905C4  2C 00 00 0E */	cmpwi r0, 0xe
/* 800939E8 000905C8  41 82 00 08 */	beq lbl_800939F0
/* 800939EC 000905CC  48 00 00 44 */	b lbl_80093A30
lbl_800939F0:
/* 800939F0 000905D0  7F C3 F3 78 */	mr r3, r30
/* 800939F4 000905D4  48 09 8F 21 */	bl func_8012C914
/* 800939F8 000905D8  48 00 00 40 */	b lbl_80093A38
lbl_800939FC:
/* 800939FC 000905DC  7F C3 F3 78 */	mr r3, r30
/* 80093A00 000905E0  48 00 00 51 */	bl func_80093A50
/* 80093A04 000905E4  38 7E 00 00 */	addi r3, r30, 0
/* 80093A08 000905E8  38 80 00 01 */	li r4, 1
/* 80093A0C 000905EC  38 A0 00 01 */	li r5, 1
/* 80093A10 000905F0  4B FE 10 FD */	bl func_80074B0C
/* 80093A14 000905F4  3C 80 00 03 */	lis r4, 0x0002E6A3@ha
/* 80093A18 000905F8  38 7F 00 00 */	addi r3, r31, 0
/* 80093A1C 000905FC  38 84 E6 A3 */	addi r4, r4, 0x0002E6A3@l
/* 80093A20 00090600  38 A0 00 7F */	li r5, 0x7f
/* 80093A24 00090604  38 C0 00 40 */	li r6, 0x40
/* 80093A28 00090608  4B FF 47 21 */	bl func_80088148
/* 80093A2C 0009060C  48 00 00 0C */	b lbl_80093A38
lbl_80093A30:
/* 80093A30 00090610  7F C3 F3 78 */	mr r3, r30
/* 80093A34 00090614  48 00 00 1D */	bl func_80093A50
lbl_80093A38:
/* 80093A38 00090618  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 80093A3C 0009061C  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 80093A40 00090620  83 C1 00 10 */	lwz r30, 0x10(r1)
/* 80093A44 00090624  38 21 00 18 */	addi r1, r1, 0x18
/* 80093A48 00090628  7C 08 03 A6 */	mtlr r0
/* 80093A4C 0009062C  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop
