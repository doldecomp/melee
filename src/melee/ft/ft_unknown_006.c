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
