#include <melee/ft/ft_unknown_006.h>

#include <melee/ft/fighter.h>
#include <melee/ft/ftcommon.h>

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
