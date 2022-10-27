#include <melee/ft/ft_unknown_006.h>

#include <melee/ft/chara/ftCLink/ftclink.h>
#include <melee/ft/chara/ftFox/ftfox.h>
#include <melee/ft/chara/ftGameWatch/ftgamewatch.h>
#include <melee/ft/fighter.h>
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
asm void func_80088C5C(Fighter* fp)
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
extern BOOL func_80099794(HSD_GObj* fighter_gobj);
extern BOOL func_8008BB44(HSD_GObj* fighter_gobj);
extern BOOL func_8008B980(HSD_GObj* fighter_gobj);
extern BOOL func_8008CB44(HSD_GObj* fighter_gobj);
extern BOOL func_8008C830(HSD_GObj* fighter_gobj);
extern BOOL func_8008BFC4(HSD_GObj* fighter_gobj);
extern BOOL func_800D8990(HSD_GObj* fighter_gobj);
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
