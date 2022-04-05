#include "ftcommon.h"

#include <melee/it/id.h>

extern struct {
    u8 x0_pad[0x20];
    HSD_GObj* unk20;
}* lbl_804D782C;

inline f32 fabsf(f32 x)
{
    if (x < 0) {
        return -x;
    } else {
        return x;
    }
}

void func_8007C930(Fighter* fp, f32 result)
{
    f32 absvel = fabsf(fp->xEC_ground_vel);
    if (fabsf(result) > absvel) {
        result = -fp->xEC_ground_vel;
    } else if (fp->xEC_ground_vel > 0) {
        result = -result;
    }
    fp->xE4_ground_accel_1 = result;
}

void func_8007C98C(Fighter* fp, f32 arg8, f32 arg9, f32 argA)
{
    f32 temp_f1;
    f32 phi_f0;
    f32 phi_f1;
    f32 phi_f3;
    f32 phi_f1_2;
    f32 result;

    phi_f3 = argA;
    result = arg8;
    if (!arg9) {
        phi_f1 = fabsf(fp->xEC_ground_vel);
        phi_f0 = fabsf(argA);
        if (phi_f0 > phi_f1) {
            phi_f3 = -fp->xEC_ground_vel;
        } else if (fp->xEC_ground_vel > 0) {
            phi_f3 = -argA;
        }
        fp->xE4_ground_accel_1 = phi_f3;
        return;
    }
    if (!(fp->xEC_ground_vel * arg8 < 0)) {
        if (arg8 > 0) {
            if (fp->xEC_ground_vel + arg8 > arg9) {
                temp_f1 = -argA;
                phi_f1_2 = temp_f1;
                if (fp->xEC_ground_vel + temp_f1 < arg9) {
                    phi_f1_2 = arg9 - fp->xEC_ground_vel;
                }
                result = phi_f1_2;
                if (fp->xEC_ground_vel + phi_f1_2 > fp->x110_attr.x144_GroundedMaxHorizontalVelocity) {
                    result = fp->x110_attr.x144_GroundedMaxHorizontalVelocity - fp->xEC_ground_vel;
                }
            }
        } else if (fp->xEC_ground_vel + arg8 < arg9) {
            result = argA;
            if (fp->xEC_ground_vel + argA > arg9) {
                result = arg9 - fp->xEC_ground_vel;
            }
            if (fp->xEC_ground_vel + result < -fp->x110_attr.x144_GroundedMaxHorizontalVelocity) {
                result = -fp->x110_attr.x144_GroundedMaxHorizontalVelocity - fp->xEC_ground_vel;
            }
        }
    }
    fp->xE4_ground_accel_1 = result;
}

void func_8007CA80(Fighter* fp, f32 result, f32 arg9)
{
    if (!arg9) {
        result = -fp->xEC_ground_vel;
    } else if (!(fp->xEC_ground_vel * result < 0)) {
        if (result > 0) {
            if (fp->xEC_ground_vel + result > arg9) {
                result = arg9 - fp->xEC_ground_vel;
            }
        } else if (fp->xEC_ground_vel + result < arg9) {
            result = arg9 - fp->xEC_ground_vel;
        }
    }
    fp->xE4_ground_accel_1 = result;
}

void func_8007CADC(Fighter* fp, f32 arg8, f32 arg9, f32 argA)
{
    f32 phi_f1 = fp->input.x620_lstick_x;
    f32 phi_f2;
    f32 phi_f4;

    if (fabsf(phi_f1) >= arg8) {
        phi_f2 = phi_f1 * arg9;
        phi_f4 = phi_f1 * argA;
    } else {
        phi_f4 = 0;
        phi_f2 = 0;
    }
    func_8007CA80(fp, phi_f2, phi_f4);
}

void func_8007CB74(HSD_GObj* gobj)
{
    f32 temp_f1;
    Vec3* ground_normal;
    Fighter* fp = gobj->user_data;
    u32 unused[2];

    ground_normal = &fp->x6F0_collData.x154_groundNormal;
    temp_f1 = func_80084A40(fp);
    if (temp_f1 < 1) {
        fp->xE4_ground_accel_1 *= temp_f1;
    }
    fp->x74_anim_vel.x = +ground_normal->y * fp->xE4_ground_accel_1;
    fp->x74_anim_vel.y = -ground_normal->x * fp->xE4_ground_accel_1;
    fp->x74_anim_vel.z = 0;
    fp->x80_self_vel.x = +ground_normal->y * fp->xEC_ground_vel;
    fp->x80_self_vel.y = -ground_normal->x * fp->xEC_ground_vel;
    fp->x80_self_vel.z = 0;
}

HSD_GObj* func_8007CC1C(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    Vec3* ground_normal = &fp->x6F0_collData.x154_groundNormal;
    fp->x74_anim_vel.x = +ground_normal->y * fp->xE4_ground_accel_1;
    fp->x74_anim_vel.y = -ground_normal->x * fp->xE4_ground_accel_1;
    fp->x74_anim_vel.z = 0;
    fp->x80_self_vel.x = +ground_normal->y * fp->xEC_ground_vel;
    fp->x80_self_vel.y = -ground_normal->x * fp->xEC_ground_vel;
    fp->x80_self_vel.z = 0;
    return gobj;
}

void func_8007CC78(Fighter* fp, f32 max)
{
    if (fp->xEC_ground_vel < -max) {
        fp->xEC_ground_vel = -max;
    } else if (fp->xEC_ground_vel > max) {
        fp->xEC_ground_vel = +max;
    }
}

void func_8007CCA0(Fighter* arg0, f32 arg1)
{
    if (arg0->xF0_ground_kb_vel < 0) {
        arg0->xF0_ground_kb_vel = arg0->xF0_ground_kb_vel + arg1;
        if (arg0->xF0_ground_kb_vel > 0) {
            arg0->xF0_ground_kb_vel = 0;
        }
    } else {
        arg0->xF0_ground_kb_vel = arg0->xF0_ground_kb_vel - arg1;
        if (arg0->xF0_ground_kb_vel < 0) {
            arg0->xF0_ground_kb_vel = 0;
        }
    }
}

void func_8007CCE8(Fighter* fp)
{
    Vec3* ground_normal;
    if (fp->xE0_ground_or_air == GA_Ground && fp->xF0_ground_kb_vel == 0) {
        ground_normal = &fp->x6F0_collData.x154_groundNormal;
        fp->xF0_ground_kb_vel = fp->x8c_kb_vel.x;
        if (fp->xF0_ground_kb_vel > lbl_804D6554->x164) {
            fp->xF0_ground_kb_vel = lbl_804D6554->x164;
        }
        if (fp->xF0_ground_kb_vel < -lbl_804D6554->x164) {
            fp->xF0_ground_kb_vel = -lbl_804D6554->x164;
        }
        fp->x8c_kb_vel.x = +ground_normal->y * fp->xF0_ground_kb_vel;
        fp->x8c_kb_vel.y = -ground_normal->x * fp->xF0_ground_kb_vel;
    }
}

f32 func_8007CD6C(f32 value, f32 decrement)
{
    f32 result = value;
    if (value > 0) {
        result = value - decrement;
        if (result < 0) {
            return 0;
        }
    } else if (value < 0) {
        result = value + decrement;
        if (result > 0) {
            return 0;
        }
    }
    return result;
}

// These do not match due to unpatched epilogue scheduling
#ifndef NON_MATCHING
char lbl_803C0D58[] = "ftcommon.c";
char lbl_803C0D64[] = "fp->kind == Ft_Kind_Sandbag";

// Not sure why this is needed
// Maybe __FILE__ is allocated separate from ordinary string literals?
#undef assert_line
#define assert_line(line, cond)                                                \
    ((cond) ? ((void) 0) : __assert(lbl_803C0D58, line, #cond))

asm f32 func_8007CDA4(Fighter*)
{
    nofralloc
/* 8007CDA4 00079984  7C 08 02 A6 */   mflr r0
/* 8007CDA8 00079988  90 01 00 04 */   stw r0, 4(r1)
/* 8007CDAC 0007998C  94 21 FF E8 */   stwu r1, -0x18(r1)
/* 8007CDB0 00079990  93 E1 00 14 */   stw r31, 0x14(r1)
/* 8007CDB4 00079994  7C 7F 1B 78 */   mr r31, r3
/* 8007CDB8 00079998  80 03 00 04 */   lwz r0, 4(r3)
/* 8007CDBC 0007999C  2C 00 00 20 */   cmpwi r0, 0x20
/* 8007CDC0 000799A0  41 82 00 1C */   beq lbl_8007CDDC
/* 8007CDC4 000799A4  3C 60 80 3C */   lis r3, lbl_803C0D58@ha
/* 8007CDC8 000799A8  3C 80 80 3C */   lis r4, lbl_803C0D64@ha
/* 8007CDCC 000799AC  38 A4 0D 64 */   addi r5, r4, lbl_803C0D64@l
/* 8007CDD0 000799B0  38 63 0D 58 */   addi r3, r3, lbl_803C0D58@l
/* 8007CDD4 000799B4  38 80 01 2B */   li r4, 0x12b
/* 8007CDD8 000799B8  48 30 B4 49 */   bl __assert
lbl_8007CDDC:
/* 8007CDDC 000799BC  80 7F 02 D4 */   lwz r3, 0x2d4(r31)
/* 8007CDE0 000799C0  80 01 00 1C */   lwz r0, 0x1c(r1)
/* 8007CDE4 000799C4  C0 23 00 00 */   lfs f1, 0(r3)
/* 8007CDE8 000799C8  83 E1 00 14 */   lwz r31, 0x14(r1)
/* 8007CDEC 000799CC  38 21 00 18 */   addi r1, r1, 0x18
/* 8007CDF0 000799D0  7C 08 03 A6 */   mtlr r0
/* 8007CDF4 000799D4  4E 80 00 20 */   blr 
}

asm f32 func_8007CDF8(Fighter*)
{
    nofralloc
/* 8007CDF8 000799D8  7C 08 02 A6 */	mflr r0
/* 8007CDFC 000799DC  90 01 00 04 */	stw r0, 4(r1)
/* 8007CE00 000799E0  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 8007CE04 000799E4  93 E1 00 14 */	stw r31, 0x14(r1)
/* 8007CE08 000799E8  7C 7F 1B 78 */	mr r31, r3
/* 8007CE0C 000799EC  80 03 00 04 */	lwz r0, 4(r3)
/* 8007CE10 000799F0  2C 00 00 20 */	cmpwi r0, 0x20
/* 8007CE14 000799F4  41 82 00 1C */	beq lbl_8007CE30
/* 8007CE18 000799F8  3C 60 80 3C */	lis r3, lbl_803C0D58@ha
/* 8007CE1C 000799FC  3C 80 80 3C */	lis r4, lbl_803C0D64@ha
/* 8007CE20 00079A00  38 A4 0D 64 */	addi r5, r4, lbl_803C0D64@l
/* 8007CE24 00079A04  38 63 0D 58 */	addi r3, r3, lbl_803C0D58@l
/* 8007CE28 00079A08  38 80 01 34 */	li r4, 0x134
/* 8007CE2C 00079A0C  48 30 B3 F5 */	bl __assert
lbl_8007CE30:
/* 8007CE30 00079A10  80 7F 02 D4 */	lwz r3, 0x2d4(r31)
/* 8007CE34 00079A14  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 8007CE38 00079A18  C0 23 00 04 */	lfs f1, 4(r3)
/* 8007CE3C 00079A1C  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 8007CE40 00079A20  38 21 00 18 */	addi r1, r1, 0x18
/* 8007CE44 00079A24  7C 08 03 A6 */	mtlr r0
/* 8007CE48 00079A28  4E 80 00 20 */	blr 
}
#pragma peephole on
#else

// to match assert statement
#define kind x4_fighterKind

static const int Ft_Kind_Sandbag = 0x20;
f32 func_8007CDA4(Fighter* fp)
{
    assert_line(299, fp->kind == Ft_Kind_Sandbag);
    return ((f32*) fp->x2D4_specialAttributes)[0];
}

f32 func_8007CDF8(Fighter* fp)
{
    assert_line(308, fp->kind == Ft_Kind_Sandbag);
    return ((f32*) fp->x2D4_specialAttributes)[1];
}
#endif

void func_8007CE4C(Fighter* fp, f32 val)
{
    if (fp->xF4_ground_attacker_shield_kb_vel < 0) {
        fp->xF4_ground_attacker_shield_kb_vel += val;
        if (fp->xF4_ground_attacker_shield_kb_vel > 0) {
            fp->xF4_ground_attacker_shield_kb_vel = 0;
        }
    } else {
        fp->xF4_ground_attacker_shield_kb_vel -= val;
        if (fp->xF4_ground_attacker_shield_kb_vel < 0) {
            fp->xF4_ground_attacker_shield_kb_vel = 0;
        }
    }
}

void func_8007CE94(Fighter* fp, f32 val)
{
    f32 phi_f2 = fabsf(fp->x80_self_vel.x);
    if (fabsf(val) >= phi_f2) {
        val = -fp->x80_self_vel.x;
    } else if (fp->x80_self_vel.x > 0) {
        val = -val;
    }
    fp->x74_anim_vel.x = val;
}

void func_8007CEF4(Fighter* fp)
{
    f32 result = fp->x110_attr.x180_AerialFriction;
    f32 lhs = fabsf(result);
    f32 phi_f1 = fabsf(fp->x80_self_vel.x);
    if (fabsf(result) >= phi_f1) {
        result = -fp->x80_self_vel.x;
    } else if (fp->x80_self_vel.x > 0) {
        result = -fp->x110_attr.x180_AerialFriction;
    }
    fp->x74_anim_vel.x = result;
}

BOOL func_8007CF58(Fighter* fp)
{
    f32 temp_f3;
    f32 phi_f1;
    f32 phi_f0;
    f32 phi_f2;
    struct attr* attr = &fp->x110_attr;

    temp_f3 = fp->x80_self_vel.x;
    phi_f1 = fabsf(temp_f3);
    if (fabsf(temp_f3) > attr->x17C_AerialDriftMax) {
        phi_f2 = lbl_804D6554->x1FC;
        phi_f1 = fabsf(temp_f3);
        phi_f0 = fabsf(lbl_804D6554->x1FC);
        if (phi_f0 >= phi_f1) {
            phi_f2 = -temp_f3;
        } else if (temp_f3 > 0) {
            phi_f2 = -lbl_804D6554->x1FC;
        }
        fp->x74_anim_vel.x = phi_f2;
        return TRUE;
    } else {
        phi_f2 = fp->x110_attr.x180_AerialFriction;
        phi_f1 = fabsf(temp_f3);
        phi_f0 = fabsf(fp->x110_attr.x180_AerialFriction);
        if (phi_f0 >= phi_f1) {
            phi_f2 = -temp_f3;
        } else if (temp_f3 > 0) {
            phi_f2 = -fp->x110_attr.x180_AerialFriction;
        }
        fp->x74_anim_vel.x = phi_f2;
        return FALSE;
    }
}

BOOL func_8007D050(Fighter* fp, f32 val)
{
    f32 temp_f2;
    f32 temp_f3;
    f32 phi_f0;
    f32 phi_f0_2;
    f32 phi_f1;
    f32 phi_f2;
    f32 phi_f0_3;
    f32 phi_f1_2;

    temp_f3 = fp->x80_self_vel.x;
    phi_f0 = fabsf(temp_f3);
    if (fabsf(temp_f3) > val) {
        phi_f2 = lbl_804D6554->x1FC;
        phi_f1 = fabsf(temp_f3);
        phi_f0_2 = fabsf(lbl_804D6554->x1FC);
        if (phi_f0_2 >= phi_f1) {
            phi_f2 = -temp_f3;
        } else if (temp_f3 > 0) {
            phi_f2 = -lbl_804D6554->x1FC;
        }
        fp->x74_anim_vel.x = phi_f2;
        return 1;
    } else {
        phi_f2 = fp->x110_attr.x180_AerialFriction;
        phi_f1_2 = fabsf(temp_f3);
        phi_f0_3 = fabsf(fp->x110_attr.x180_AerialFriction);
        if (phi_f0_3 >= phi_f1_2) {
            phi_f2 = -temp_f3;
        } else if (temp_f3 > 0) {
            phi_f2 = -fp->x110_attr.x180_AerialFriction;
        }
        fp->x74_anim_vel.x = phi_f2;
        return 0;
    }
}

void func_8007D140(Fighter* fp, f32 arg8, f32 arg9, f32 argA)
{
    func_8007D174(fp, fp->x80_self_vel.x, arg8, arg9, argA);
}

void func_8007D174(Fighter* fp, f32 arg8, f32 arg9, f32 argA, f32 argB)
{
    f32 phi_f1;
    f32 phi_f2;

    phi_f2 = argB;
    if (!argA) {
        phi_f1 = fabsf(fp->x80_self_vel.x);
        if (fabsf(argB) >= phi_f1) {
            phi_f2 = -fp->x80_self_vel.x;
        } else if (fp->x80_self_vel.x > 0) {
            phi_f2 = -argB;
        }
        fp->x74_anim_vel.x = phi_f2;
        return;
    }

    phi_f2 = arg9;
    if (!(arg8 * arg9 < 0)) {
        if (arg9 > 0) {
            if (arg8 + arg9 > argA) {
                phi_f2 = -argB;
                if (arg8 + phi_f2 < argA) {
                    phi_f2 = argA - arg8;
                }
                if (arg8 + phi_f2 > fp->x110_attr.x188_HorizontalAirMobilityConstant) {
                    phi_f2 = fp->x110_attr.x188_HorizontalAirMobilityConstant - arg8;
                }
            }
        } else if (arg8 + arg9 < argA) {
            phi_f2 = argB;
            if (arg8 + argB > argA) {
                phi_f2 = argA - arg8;
            }
            if (arg8 + phi_f2 < -fp->x110_attr.x188_HorizontalAirMobilityConstant) {
                phi_f2 = -fp->x110_attr.x188_HorizontalAirMobilityConstant - arg8;
            }
        }
    }
    fp->x74_anim_vel.x = phi_f2;
}

void func_8007D268(Fighter* fp)
{
    func_8007D28C(fp, fp->x80_self_vel.x);
}

void func_8007D28C(Fighter* fp, f32 arg8)
{
    f32 tmp;
    f32 phi_f3;
    f32 f5;
    struct attr* temp_r4;

    f5 = fp->input.x620_lstick_x;
    temp_r4 = &fp->x110_attr;
    tmp = f5 * fp->x110_attr.x174_AerialDriftStickMult;

    if (f5 > 0) {
        phi_f3 = +temp_r4->x178_AerialDriftBase;
    } else {
        phi_f3 = -temp_r4->x178_AerialDriftBase;
    }
    func_8007D174(fp, arg8, tmp + phi_f3,
        f5 * temp_r4->x17C_AerialDriftMax, temp_r4->x180_AerialFriction);
}

void func_8007D2E8(Fighter* fp, f32 arg8, f32 arg9)
{
    f32 result = arg8;
    if (!arg9) {
        result = -fp->x80_self_vel.x;
    } else if (!((fp->x80_self_vel.x * arg8) < 0)) {
        if (arg8 > 0) {
            if (fp->x80_self_vel.x + arg8 > arg9) {
                result = arg9 - fp->x80_self_vel.x;
            }
        } else {
            if (fp->x80_self_vel.x + arg8 < arg9) {
                result = arg9 - fp->x80_self_vel.x;
            }
        }
    }
    fp->x74_anim_vel.x = result;
}

void func_8007D344(Fighter* fp, f32 arg8, f32 arg9, f32 argA)
{
    f32 argx, argy;
    f32 friction;

    if (fabsf(fp->input.x620_lstick_x) >= arg8) {
        argx = fp->input.x620_lstick_x * arg9;
        argy = fp->input.x620_lstick_x * argA;
    } else {
        argy = 0;
        argx = 0;
    }
    friction = fp->x110_attr.x180_AerialFriction;
    func_8007D174(fp, fp->x80_self_vel.x, argx, argy, friction);
}

void func_8007D3A8(Fighter* fp, f32 arg8, f32 arg9, f32 argA)
{
    f32 phi_f2;
    f32 phi_f4;

    if (fabsf(fp->input.x620_lstick_x) >= arg8) {
        phi_f2 = fp->input.x620_lstick_x * arg9;
        phi_f4 = fp->input.x620_lstick_x * argA;
    } else {
        phi_f4 = 0;
        phi_f2 = 0;
    }

    func_8007D2E8(fp, phi_f2, phi_f4);
}

void func_8007D440(Fighter* fp, f32 val)
{
    f32 temp_f0 = fp->x80_self_vel.x;
    if (temp_f0 < -val) {
        fp->x80_self_vel.x = -val;
    } else if (temp_f0 > val) {
        fp->x80_self_vel.x = +val;
    }
}

void func_8007D468(Fighter* fp)
{
    if (fp->x80_self_vel.x < -fp->x110_attr.x17C_AerialDriftMax) {
        fp->x80_self_vel.x = -fp->x110_attr.x17C_AerialDriftMax;
    } else if (fp->x80_self_vel.x > fp->x110_attr.x17C_AerialDriftMax) {
        fp->x80_self_vel.x = fp->x110_attr.x17C_AerialDriftMax;
    }
}

void func_8007D494(Fighter* fp, f32 arg8, f32 arg9)
{
    fp->x80_self_vel.y -= arg8;
    if (fp->x80_self_vel.y < -arg9) {
        fp->x80_self_vel.y = -arg9;
    }
}

void func_8007D4B8(Fighter* fp)
{
    f32 tmp = -fp->x110_attr.x170_TerminalVelocity;
    fp->x80_self_vel.y -= fp->x110_attr.x16C_Gravity;
    if (fp->x80_self_vel.y < tmp) {
        fp->x80_self_vel.y = tmp;
    }
}

void func_8007D4E4(Fighter* fp)
{
    fp->x80_self_vel.y = -fp->x110_attr.x184_FastfallVelocity;
}

void ftComm_ClampFalllSpeed(Fighter* fp, f32 val)
{
    if (fp->x80_self_vel.y > val) {
        fp->x80_self_vel.y = val;
    }
}

void func_8007D508(Fighter* fp, f32 arg8, f32 arg9)
{
    fp->x80_self_vel.y += arg8;
    if (fp->x80_self_vel.y > arg9) {
        fp->x80_self_vel.y = arg9;
    }
}

BOOL func_8007D528(Fighter* fp)
{
    if (!fp->x221A_flag.bits.b4 && fp->x80_self_vel.y < 0 &&
        fp->input.x624_lstick_y <= -lbl_804D6554->x88 && fp->x671_timer_lstick_tilt_y < lbl_804D6554->x8C) {

        fp->x221A_flag.bits.b4 = 1;
        fp->x671_timer_lstick_tilt_y = 0xFE;
        func_80088148(fp, 0x96, 0x7F, 0x40);
        return TRUE;
    }
    return FALSE;
}

void func_8007D5BC(Fighter* fp)
{
    fp->x6F0_collData.x19C = 0;
    fp->x6F0_collData.x130 &= 0xFFFFFFEF;
}

void func_8007D5D4(Fighter* fp)
{
    fp->xE0_ground_or_air = GA_Air;
    fp->xEC_ground_vel = 0;
    fp->x98_atk_shield_kb.z = 0;
    fp->xB0_pos.z = 0;
    fp->x74_anim_vel.y = 0;
    fp->x1968_jumpsUsed = 1;
    fp->x6F0_collData.x19C = 0xA;
    fp->x6F0_collData.x130 |= 0x10;
}

void func_8007D60C(Fighter* fp)
{
    struct attr* attr = &fp->x110_attr;
    if (fp->x2227_flag.bits.b0 && fp->x1968_jumpsUsed <= 1) {
        func_8003FC44(fp->xC_playerID, fp->x221F_flag.bits.b4);
    }
    fp->xE0_ground_or_air = GA_Air;
    fp->xEC_ground_vel = 0;
    fp->x74_anim_vel.y = 0;
    fp->x1968_jumpsUsed = attr->x168_MaxJumps;
    fp->x6F0_collData.x19C = 5;
    fp->x6F0_collData.x130 |= 0x10;
}

void func_8007D698(Fighter* fp)
{
    fp->x1968_jumpsUsed = fp->x110_attr.x168_MaxJumps;
}

void func_8007D6A4(Fighter* fp)
{
    f32 tmp;
    if ((fp->x594_animCurrFlags1 >> 7U) & 1) {
        fp->x80_self_vel.x = fp->x6A4_transNOffset.z * fp->x2C_facing_direction;
    }
    tmp = fp->x110_attr.x144_GroundedMaxHorizontalVelocity;
    if (fp->xEC_ground_vel < -tmp) {
        fp->xEC_ground_vel = -tmp;
    } else if (fp->xEC_ground_vel > tmp) {
        fp->xEC_ground_vel = tmp;
    }
    fp->xE0_ground_or_air = GA_Ground;
    fp->xEC_ground_vel = fp->x80_self_vel.x;
    fp->x1968_jumpsUsed = 0;
    fp->x1969_walljumpUsed = 0;
    fp->x2227_flag.bits.b0 = 0;
    fp->x6F0_collData.x19C = 0;
    fp->x6F0_collData.x130 &= 0xFFFFFFEF;
    if (!func_80084A18(fp->x0_fighter)) {
        OSReport("fighter ground no under Id! %d %d\n", fp->xC_playerID, fp->x10);
        assert_line(686, 0);
    }
}

void func_8007D780(Fighter* fp)
{
    if (fp->xE0_ground_or_air != GA_Air) {
        return;
    }

    if (func_803224DC(fp->x8_spawnNum, fp->xB0_pos.x, fp->dmg.x18A4_knockbackMagnitude)) {
        fp->dmg.x18A4_knockbackMagnitude = 0;
    }
    if (fp->x2227_flag.bits.b0 && fp->x1968_jumpsUsed <= 1) {
        func_8003FC44(fp->xC_playerID, fp->x221F_flag.bits.b4);
    }
}

void func_8007D7FC(Fighter* fp)
{
    f32 fmp;
    if (fp->xE0_ground_or_air == GA_Air) {
        if (func_803224DC(fp->x8_spawnNum, fp->xB0_pos.x, fp->dmg.x18A4_knockbackMagnitude)) {
            fp->dmg.x18A4_knockbackMagnitude = 0;
        }
        if (fp->x2227_flag.bits.b0 && fp->x1968_jumpsUsed <= 1) {
            func_8003FC44(fp->xC_playerID, fp->x221F_flag.bits.b4);
        }
    }
    if ((fp->x594_animCurrFlags1 >> 7U) & 1) {
        fp->x80_self_vel.x = fp->x6A4_transNOffset.z * fp->x2C_facing_direction;
    }
    fmp = fp->x110_attr.x144_GroundedMaxHorizontalVelocity;
    if (fp->xEC_ground_vel < -fmp) {
        fp->xEC_ground_vel = -fmp;
    } else if (fp->xEC_ground_vel > fmp) {
        fp->xEC_ground_vel = fmp;
    }
    fp->xE0_ground_or_air = GA_Ground;
    fp->xEC_ground_vel = fp->x80_self_vel.x;
    fp->x1968_jumpsUsed = 0;
    fp->x1969_walljumpUsed = 0;
    fp->x2227_flag.bits.b0 = 0;
    fp->x6F0_collData.x19C = 0;
    fp->x6F0_collData.x130 &= 0xFFFFFFEF;
    if (!func_80084A18(fp->x0_fighter)) {
        OSReport("fighter ground no under Id! %d %d\n", fp->xC_playerID, fp->x10);
        assert_line(0x2AE, 0);
    }
}

void func_8007D92C(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    if (fp->xE0_ground_or_air == 1) {
        func_800CC730(gobj);
    } else {
        func_8008A2BC(gobj);
    }
}

f32 func_8007D964(Fighter* fp)
{
    return func_80022C30(fp->input.x624_lstick_y, fabsf(fp->input.x620_lstick_x));
}

f32 func_8007D99C(Fighter* fp)
{
    return func_80022C30(fp->input.x63C, fabsf(fp->input.x638));
}

f32 func_8007D9D4(Fighter* fp)
{
    return func_80022C30(fp->input.x624_lstick_y, fp->input.x620_lstick_x);
}

void func_8007D9FC(Fighter* fp)
{
    f32 phi_f0;
    if (fp->input.x620_lstick_x >= 0) {
        phi_f0 = +1;
    } else {
        phi_f0 = -1;
    }
    fp->x2C_facing_direction = phi_f0;
}

void func_8007DA24(Fighter* fp)
{
    f32 phi_f0;
    if (fabsf(fp->input.x620_lstick_x) > lbl_804D6554->x0) {
        if (fp->input.x620_lstick_x >= 0) {
            phi_f0 = +1;
        } else {
            phi_f0 = -1;
        }
        fp->x2C_facing_direction = phi_f0;
    }
}

f32 func_8007DA74(s32 arg0, u32 arg1, f32 arg8)
{
    s32 tmp = arg0 * lbl_804D6554->x198 + lbl_804D6554->x19C;
    f32 result = (s32) (tmp * arg8);
    if (arg1 - 0x27 <= 1) {
        result = (s32) (result * lbl_804D6554->x1A0);
    }
    return result;
}

void func_8007DB24(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    fp->x2219_flag.bits.b0 = 0;
    efLib_DestroyAll(gobj, fp);
}

void func_8007DB58(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    func_80088770(fp);
    func_800887CC(fp);
    if (fp->cb.x21DC_callback_OnTakeDamage != NULL) {
        fp->cb.x21DC_callback_OnTakeDamage(gobj);
    }
    if (fp->cb.x21E0_callback_OnDeath != NULL) {
        fp->cb.x21E0_callback_OnDeath(gobj);
    }
}

extern struct {
    s32 x0;
    s32 x4;
}* lbl_804D652C;

void func_8007DBCC(Fighter* fp, BOOL arg1, f32 arg8)
{
    fp->x1A4C = arg8;
    fp->x1A51 = 0;
    fp->x1A50 = 0;
    fp->x2224_flag.bits.b6 = arg1;
    if (fp->x2224_flag.bits.b6) {
        fp->x1A52 = 0;
        fp->x1A53 = lbl_804D652C->x4;
    }
}

s32 func_8007DC08(Fighter* fp, f32 arg8)
{
    s32 phi_r31;
    s8 r5;
    s8 r6;

    phi_r31 = 0;
    if (fp->input.x668 & 0x80000F00) {
        fp->x1A4C -= arg8;
        phi_r31 = 1;
    }
    r5 = fp->x1A50;
    r6 = fp->x1A51;

    if (fp->input.x620_lstick_x < -lbl_804D6554->x308) {
        fp->x1A50 = -1;
    }
    if (fp->input.x620_lstick_x > lbl_804D6554->x308) {
        fp->x1A50 = 1;
    }
    if (fp->input.x624_lstick_y < -lbl_804D6554->x308) {
        fp->x1A51 = -1;
    }
    if (fp->input.x624_lstick_y > lbl_804D6554->x308) {
        fp->x1A51 = 1;
    }
    if (r5 != fp->x1A50 || r6 != fp->x1A51) {
        fp->x1A4C -= arg8;
        phi_r31 = 1;
    }
    if (phi_r31 != 0 && fp->x2224_flag.bits.b6) {
        fp->x2224_flag.bits.b5 = 1;
        fp->x1A52 += 1;
        if (fp->x1A52 >= fp->x1A53) {
            fp->x1A52 = 0;
        }
    } else {
        fp->x2224_flag.bits.b5 = 0;
    }
    func_800402D0(fp->xC_playerID, fp->x221F_flag.bits.b4, phi_r31);
    return phi_r31;
}

#define _SDA2_BASE_ 0x804DF9E0
#define lbl_804D8330 0x804D8330
extern void func_8007F8B4();
extern void func_8004DC04();
extern void func_8004DB78();
extern void func_80086FD4();
/* https://decomp.me/scratch/il3yA */
asm void func_8007DD7C()
{
    nofralloc
/* 8007DD7C 0007A95C  7C 08 02 A6 */	mflr r0
/* 8007DD80 0007A960  90 01 00 04 */	stw r0, 4(r1)
/* 8007DD84 0007A964  94 21 FF 98 */	stwu r1, -0x68(r1)
/* 8007DD88 0007A968  DB E1 00 60 */	stfd f31, 0x60(r1)
/* 8007DD8C 0007A96C  BE E1 00 3C */	stmw r23, 0x3c(r1)
/* 8007DD90 0007A970  7C 7A 1B 78 */	mr r26, r3
/* 8007DD94 0007A974  7C 9B 23 78 */	mr r27, r4
/* 8007DD98 0007A978  3B 80 00 00 */	li r28, 0
/* 8007DD9C 0007A97C  80 6D C1 8C */	lwz r3, lbl_804D782C
/* 8007DDA0 0007A980  83 DA 00 2C */	lwz r30, 0x2c(r26)
/* 8007DDA4 0007A984  83 A3 00 20 */	lwz r29, 0x20(r3)
/* 8007DDA8 0007A988  C3 E2 89 50 */	lfs f31, lbl_804D8330-_SDA2_BASE_(r2)
/* 8007DDAC 0007A98C  3B FE 02 C4 */	addi r31, r30, 0x2c4
/* 8007DDB0 0007A990  48 00 02 00 */	b lbl_8007DFB0
lbl_8007DDB4:
/* 8007DDB4 0007A994  7C 1D D0 40 */	cmplw r29, r26
/* 8007DDB8 0007A998  41 82 01 F0 */	beq lbl_8007DFA8
/* 8007DDBC 0007A99C  38 7D 00 00 */	addi r3, r29, 0
/* 8007DDC0 0007A9A0  38 9A 00 00 */	addi r4, r26, 0
/* 8007DDC4 0007A9A4  48 00 92 11 */	bl func_80086FD4
/* 8007DDC8 0007A9A8  2C 03 00 00 */	cmpwi r3, 0
/* 8007DDCC 0007A9AC  40 82 01 DC */	bne lbl_8007DFA8
/* 8007DDD0 0007A9B0  80 9D 00 2C */	lwz r4, 0x2c(r29)
/* 8007DDD4 0007A9B4  88 64 22 1F */	lbz r3, 0x221f(r4)
/* 8007DDD8 0007A9B8  3B 04 00 00 */	addi r24, r4, 0
/* 8007DDDC 0007A9BC  54 60 E7 FF */	rlwinm. r0, r3, 0x1c, 0x1f, 0x1f
/* 8007DDE0 0007A9C0  40 82 01 CC */	bne lbl_8007DFAC
/* 8007DDE4 0007A9C4  80 18 00 E0 */	lwz r0, 0xe0(r24)
/* 8007DDE8 0007A9C8  2C 00 00 00 */	cmpwi r0, 0
/* 8007DDEC 0007A9CC  40 82 01 C0 */	bne lbl_8007DFAC
/* 8007DDF0 0007A9D0  80 18 1A 58 */	lwz r0, 0x1a58(r24)
/* 8007DDF4 0007A9D4  28 00 00 00 */	cmplwi r0, 0
/* 8007DDF8 0007A9D8  40 82 01 B4 */	bne lbl_8007DFAC
/* 8007DDFC 0007A9DC  54 60 EF FF */	rlwinm. r0, r3, 0x1d, 0x1f, 0x1f
/* 8007DE00 0007A9E0  40 82 01 AC */	bne lbl_8007DFAC
/* 8007DE04 0007A9E4  80 1E 08 3C */	lwz r0, 0x83c(r30)
/* 8007DE08 0007A9E8  83 38 08 3C */	lwz r25, 0x83c(r24)
/* 8007DE0C 0007A9EC  7C 17 03 78 */	mr r23, r0
/* 8007DE10 0007A9F0  7C 00 C8 00 */	cmpw r0, r25
/* 8007DE14 0007A9F4  41 82 00 24 */	beq lbl_8007DE38
/* 8007DE18 0007A9F8  7E E3 BB 78 */	mr r3, r23
/* 8007DE1C 0007A9FC  4B FC FD 5D */	bl func_8004DB78
/* 8007DE20 0007AA00  7C 19 18 00 */	cmpw r25, r3
/* 8007DE24 0007AA04  41 82 00 14 */	beq lbl_8007DE38
/* 8007DE28 0007AA08  7E E3 BB 78 */	mr r3, r23
/* 8007DE2C 0007AA0C  4B FC FD D9 */	bl func_8004DC04
/* 8007DE30 0007AA10  7C 19 18 00 */	cmpw r25, r3
/* 8007DE34 0007AA14  40 82 01 78 */	bne lbl_8007DFAC
lbl_8007DE38:
/* 8007DE38 0007AA18  38 78 00 00 */	addi r3, r24, 0
/* 8007DE3C 0007AA1C  38 81 00 24 */	addi r4, r1, 0x24
/* 8007DE40 0007AA20  48 00 1A 75 */	bl func_8007F8B4
/* 8007DE44 0007AA24  C0 9F 00 00 */	lfs f4, 0(r31)
/* 8007DE48 0007AA28  38 78 02 C4 */	addi r3, r24, 0x2c4
/* 8007DE4C 0007AA2C  C0 7E 00 2C */	lfs f3, 0x2c(r30)
/* 8007DE50 0007AA30  C0 1B 00 00 */	lfs f0, 0(r27)
/* 8007DE54 0007AA34  C0 58 00 2C */	lfs f2, 0x2c(r24)
/* 8007DE58 0007AA38  C0 38 02 C4 */	lfs f1, 0x2c4(r24)
/* 8007DE5C 0007AA3C  EC 64 00 FA */	fmadds f3, f4, f3, f0
/* 8007DE60 0007AA40  C0 01 00 24 */	lfs f0, 0x24(r1)
/* 8007DE64 0007AA44  EC 02 00 7A */	fmadds f0, f2, f1, f0
/* 8007DE68 0007AA48  EC 03 00 28 */	fsubs f0, f3, f0
/* 8007DE6C 0007AA4C  FC 00 F8 40 */	fcmpo cr0, f0, f31
/* 8007DE70 0007AA50  FC 60 00 90 */	fmr f3, f0
/* 8007DE74 0007AA54  40 80 00 0C */	bge lbl_8007DE80
/* 8007DE78 0007AA58  FC 40 18 50 */	fneg f2, f3
/* 8007DE7C 0007AA5C  48 00 00 08 */	b lbl_8007DE84
lbl_8007DE80:
/* 8007DE80 0007AA60  FC 40 18 90 */	fmr f2, f3
lbl_8007DE84:
/* 8007DE84 0007AA64  C0 3F 00 04 */	lfs f1, 4(r31)
/* 8007DE88 0007AA68  C0 03 00 04 */	lfs f0, 4(r3)
/* 8007DE8C 0007AA6C  EC 01 00 2A */	fadds f0, f1, f0
/* 8007DE90 0007AA70  FC 02 00 40 */	fcmpo cr0, f2, f0
/* 8007DE94 0007AA74  40 80 01 18 */	bge lbl_8007DFAC
/* 8007DE98 0007AA78  FC 03 F8 00 */	fcmpu cr0, f3, f31
/* 8007DE9C 0007AA7C  41 82 00 34 */	beq lbl_8007DED0
/* 8007DEA0 0007AA80  FC 03 F8 40 */	fcmpo cr0, f3, f31
/* 8007DEA4 0007AA84  40 80 00 14 */	bge lbl_8007DEB8
/* 8007DEA8 0007AA88  80 6D AE B4 */	lwz r3, lbl_804D6554
/* 8007DEAC 0007AA8C  C0 03 04 50 */	lfs f0, 0x450(r3)
/* 8007DEB0 0007AA90  FC 20 00 50 */	fneg f1, f0
/* 8007DEB4 0007AA94  48 00 00 0C */	b lbl_8007DEC0
lbl_8007DEB8:
/* 8007DEB8 0007AA98  80 6D AE B4 */	lwz r3, lbl_804D6554
/* 8007DEBC 0007AA9C  C0 23 04 50 */	lfs f1, 0x450(r3)
lbl_8007DEC0:
/* 8007DEC0 0007AAA0  C0 1E 00 F8 */	lfs f0, 0xf8(r30)
/* 8007DEC4 0007AAA4  EC 00 08 2A */	fadds f0, f0, f1
/* 8007DEC8 0007AAA8  D0 1E 00 F8 */	stfs f0, 0xf8(r30)
/* 8007DECC 0007AAAC  48 00 00 30 */	b lbl_8007DEFC
lbl_8007DED0:
/* 8007DED0 0007AAB0  2C 1C 00 00 */	cmpwi r28, 0
/* 8007DED4 0007AAB4  41 82 00 14 */	beq lbl_8007DEE8
/* 8007DED8 0007AAB8  80 6D AE B4 */	lwz r3, lbl_804D6554
/* 8007DEDC 0007AABC  C0 03 04 50 */	lfs f0, 0x450(r3)
/* 8007DEE0 0007AAC0  FC 20 00 50 */	fneg f1, f0
/* 8007DEE4 0007AAC4  48 00 00 0C */	b lbl_8007DEF0
lbl_8007DEE8:
/* 8007DEE8 0007AAC8  80 6D AE B4 */	lwz r3, lbl_804D6554
/* 8007DEEC 0007AACC  C0 23 04 50 */	lfs f1, 0x450(r3)
lbl_8007DEF0:
/* 8007DEF0 0007AAD0  C0 1E 00 F8 */	lfs f0, 0xf8(r30)
/* 8007DEF4 0007AAD4  EC 00 08 2A */	fadds f0, f0, f1
/* 8007DEF8 0007AAD8  D0 1E 00 F8 */	stfs f0, 0xf8(r30)
lbl_8007DEFC:
/* 8007DEFC 0007AADC  C0 3B 00 08 */	lfs f1, 8(r27)
/* 8007DF00 0007AAE0  C0 01 00 2C */	lfs f0, 0x2c(r1)
/* 8007DF04 0007AAE4  EC 01 00 28 */	fsubs f0, f1, f0
/* 8007DF08 0007AAE8  FC 00 F8 00 */	fcmpu cr0, f0, f31
/* 8007DF0C 0007AAEC  41 82 00 34 */	beq lbl_8007DF40
/* 8007DF10 0007AAF0  FC 00 F8 40 */	fcmpo cr0, f0, f31
/* 8007DF14 0007AAF4  40 80 00 14 */	bge lbl_8007DF28
/* 8007DF18 0007AAF8  80 6D AE B4 */	lwz r3, lbl_804D6554
/* 8007DF1C 0007AAFC  C0 03 04 54 */	lfs f0, 0x454(r3)
/* 8007DF20 0007AB00  FC 20 00 50 */	fneg f1, f0
/* 8007DF24 0007AB04  48 00 00 0C */	b lbl_8007DF30
lbl_8007DF28:
/* 8007DF28 0007AB08  80 6D AE B4 */	lwz r3, lbl_804D6554
/* 8007DF2C 0007AB0C  C0 23 04 54 */	lfs f1, 0x454(r3)
lbl_8007DF30:
/* 8007DF30 0007AB10  C0 1E 00 FC */	lfs f0, 0xfc(r30)
/* 8007DF34 0007AB14  EC 00 08 2A */	fadds f0, f0, f1
/* 8007DF38 0007AB18  D0 1E 00 FC */	stfs f0, 0xfc(r30)
/* 8007DF3C 0007AB1C  48 00 00 70 */	b lbl_8007DFAC
lbl_8007DF40:
/* 8007DF40 0007AB20  FC 03 F8 00 */	fcmpu cr0, f3, f31
/* 8007DF44 0007AB24  41 82 00 34 */	beq lbl_8007DF78
/* 8007DF48 0007AB28  FC 03 F8 40 */	fcmpo cr0, f3, f31
/* 8007DF4C 0007AB2C  40 80 00 14 */	bge lbl_8007DF60
/* 8007DF50 0007AB30  80 6D AE B4 */	lwz r3, lbl_804D6554
/* 8007DF54 0007AB34  C0 03 04 54 */	lfs f0, 0x454(r3)
/* 8007DF58 0007AB38  FC 20 00 50 */	fneg f1, f0
/* 8007DF5C 0007AB3C  48 00 00 0C */	b lbl_8007DF68
lbl_8007DF60:
/* 8007DF60 0007AB40  80 6D AE B4 */	lwz r3, lbl_804D6554
/* 8007DF64 0007AB44  C0 23 04 54 */	lfs f1, 0x454(r3)
lbl_8007DF68:
/* 8007DF68 0007AB48  C0 1E 00 FC */	lfs f0, 0xfc(r30)
/* 8007DF6C 0007AB4C  EC 00 08 2A */	fadds f0, f0, f1
/* 8007DF70 0007AB50  D0 1E 00 FC */	stfs f0, 0xfc(r30)
/* 8007DF74 0007AB54  48 00 00 38 */	b lbl_8007DFAC
lbl_8007DF78:
/* 8007DF78 0007AB58  2C 1C 00 00 */	cmpwi r28, 0
/* 8007DF7C 0007AB5C  41 82 00 14 */	beq lbl_8007DF90
/* 8007DF80 0007AB60  80 6D AE B4 */	lwz r3, lbl_804D6554
/* 8007DF84 0007AB64  C0 03 04 54 */	lfs f0, 0x454(r3)
/* 8007DF88 0007AB68  FC 20 00 50 */	fneg f1, f0
/* 8007DF8C 0007AB6C  48 00 00 0C */	b lbl_8007DF98
lbl_8007DF90:
/* 8007DF90 0007AB70  80 6D AE B4 */	lwz r3, lbl_804D6554
/* 8007DF94 0007AB74  C0 23 04 54 */	lfs f1, 0x454(r3)
lbl_8007DF98:
/* 8007DF98 0007AB78  C0 1E 00 FC */	lfs f0, 0xfc(r30)
/* 8007DF9C 0007AB7C  EC 00 08 2A */	fadds f0, f0, f1
/* 8007DFA0 0007AB80  D0 1E 00 FC */	stfs f0, 0xfc(r30)
/* 8007DFA4 0007AB84  48 00 00 08 */	b lbl_8007DFAC
lbl_8007DFA8:
/* 8007DFA8 0007AB88  3B 80 00 01 */	li r28, 1
lbl_8007DFAC:
/* 8007DFAC 0007AB8C  83 BD 00 08 */	lwz r29, 8(r29)
lbl_8007DFB0:
/* 8007DFB0 0007AB90  28 1D 00 00 */	cmplwi r29, 0
/* 8007DFB4 0007AB94  40 82 FE 00 */	bne lbl_8007DDB4
/* 8007DFB8 0007AB98  BA E1 00 3C */	lmw r23, 0x3c(r1)
/* 8007DFBC 0007AB9C  80 01 00 6C */	lwz r0, 0x6c(r1)
/* 8007DFC0 0007ABA0  CB E1 00 60 */	lfd f31, 0x60(r1)
/* 8007DFC4 0007ABA4  38 21 00 68 */	addi r1, r1, 0x68
/* 8007DFC8 0007ABA8  7C 08 03 A6 */	mtlr r0
/* 8007DFCC 0007ABAC  4E 80 00 20 */	blr 
}
#pragma peephole on

asm void func_8007DFD0()
{
    nofralloc
/* 8007DFD0 0007ABB0  7C 08 02 A6 */	mflr r0
/* 8007DFD4 0007ABB4  90 01 00 04 */	stw r0, 4(r1)
/* 8007DFD8 0007ABB8  94 21 FF B0 */	stwu r1, -0x50(r1)
/* 8007DFDC 0007ABBC  BF 21 00 34 */	stmw r25, 0x34(r1)
/* 8007DFE0 0007ABC0  7C 79 1B 78 */	mr r25, r3
/* 8007DFE4 0007ABC4  7C 9A 23 78 */	mr r26, r4
/* 8007DFE8 0007ABC8  83 A3 00 2C */	lwz r29, 0x2c(r3)
/* 8007DFEC 0007ABCC  88 7D 00 0C */	lbz r3, 0xc(r29)
/* 8007DFF0 0007ABD0  3B FD 02 C4 */	addi r31, r29, 0x2c4
/* 8007DFF4 0007ABD4  4B FB 61 1D */	bl Player_GetEntity
/* 8007DFF8 0007ABD8  80 63 00 2C */	lwz r3, 0x2c(r3)
/* 8007DFFC 0007ABDC  88 03 22 1F */	lbz r0, 0x221f(r3)
/* 8007E000 0007ABE0  3B 83 00 00 */	addi r28, r3, 0
/* 8007E004 0007ABE4  54 00 E7 FF */	rlwinm. r0, r0, 0x1c, 0x1f, 0x1f
/* 8007E008 0007ABE8  40 82 00 BC */	bne lbl_8007E0C4
/* 8007E00C 0007ABEC  80 1C 00 E0 */	lwz r0, 0xe0(r28)
/* 8007E010 0007ABF0  2C 00 00 00 */	cmpwi r0, 0
/* 8007E014 0007ABF4  40 82 00 B0 */	bne lbl_8007E0C4
/* 8007E018 0007ABF8  80 1D 08 3C */	lwz r0, 0x83c(r29)
/* 8007E01C 0007ABFC  83 DC 08 3C */	lwz r30, 0x83c(r28)
/* 8007E020 0007AC00  7C 1B 03 78 */	mr r27, r0
/* 8007E024 0007AC04  7C 00 F0 00 */	cmpw r0, r30
/* 8007E028 0007AC08  41 82 00 24 */	beq lbl_8007E04C
/* 8007E02C 0007AC0C  7F 63 DB 78 */	mr r3, r27
/* 8007E030 0007AC10  4B FC FB 49 */	bl func_8004DB78
/* 8007E034 0007AC14  7C 1E 18 00 */	cmpw r30, r3
/* 8007E038 0007AC18  41 82 00 14 */	beq lbl_8007E04C
/* 8007E03C 0007AC1C  7F 63 DB 78 */	mr r3, r27
/* 8007E040 0007AC20  4B FC FB C5 */	bl func_8004DC04
/* 8007E044 0007AC24  7C 1E 18 00 */	cmpw r30, r3
/* 8007E048 0007AC28  40 82 00 7C */	bne lbl_8007E0C4
lbl_8007E04C:
/* 8007E04C 0007AC2C  38 7C 00 00 */	addi r3, r28, 0
/* 8007E050 0007AC30  38 81 00 1C */	addi r4, r1, 0x1c
/* 8007E054 0007AC34  48 00 18 61 */	bl func_8007F8B4
/* 8007E058 0007AC38  C0 9F 00 00 */	lfs f4, 0(r31)
/* 8007E05C 0007AC3C  38 7C 02 C4 */	addi r3, r28, 0x2c4
/* 8007E060 0007AC40  C0 3D 00 2C */	lfs f1, 0x2c(r29)
/* 8007E064 0007AC44  C0 1A 00 00 */	lfs f0, 0(r26)
/* 8007E068 0007AC48  C0 7C 00 2C */	lfs f3, 0x2c(r28)
/* 8007E06C 0007AC4C  C0 5C 02 C4 */	lfs f2, 0x2c4(r28)
/* 8007E070 0007AC50  EC 84 00 7A */	fmadds f4, f4, f1, f0
/* 8007E074 0007AC54  C0 21 00 1C */	lfs f1, 0x1c(r1)
/* 8007E078 0007AC58  C0 02 89 50 */	lfs f0, 0.0f
/* 8007E07C 0007AC5C  EC 23 08 BA */	fmadds f1, f3, f2, f1
/* 8007E080 0007AC60  EC 24 08 28 */	fsubs f1, f4, f1
/* 8007E084 0007AC64  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 8007E088 0007AC68  FC 00 08 90 */	fmr f0, f1
/* 8007E08C 0007AC6C  40 80 00 0C */	bge lbl_8007E098
/* 8007E090 0007AC70  FC 40 00 50 */	fneg f2, f0
/* 8007E094 0007AC74  48 00 00 08 */	b lbl_8007E09C
lbl_8007E098:
/* 8007E098 0007AC78  FC 40 00 90 */	fmr f2, f0
lbl_8007E09C:
/* 8007E09C 0007AC7C  C0 3F 00 04 */	lfs f1, 4(r31)
/* 8007E0A0 0007AC80  C0 03 00 04 */	lfs f0, 4(r3)
/* 8007E0A4 0007AC84  EC 01 00 2A */	fadds f0, f1, f0
/* 8007E0A8 0007AC88  FC 02 00 40 */	fcmpo cr0, f2, f0
/* 8007E0AC 0007AC8C  40 80 00 18 */	bge lbl_8007E0C4
/* 8007E0B0 0007AC90  80 6D AE B4 */	lwz r3, lbl_804D6554
/* 8007E0B4 0007AC94  C0 3D 00 FC */	lfs f1, 0xfc(r29)
/* 8007E0B8 0007AC98  C0 03 04 5C */	lfs f0, 0x45c(r3)
/* 8007E0BC 0007AC9C  EC 01 00 28 */	fsubs f0, f1, f0
/* 8007E0C0 0007ACA0  D0 1D 00 FC */	stfs f0, 0xfc(r29)
lbl_8007E0C4:
/* 8007E0C4 0007ACA4  38 79 00 00 */	addi r3, r25, 0
/* 8007E0C8 0007ACA8  38 9A 00 00 */	addi r4, r26, 0
/* 8007E0CC 0007ACAC  4B FF FC B1 */	bl func_8007DD7C
/* 8007E0D0 0007ACB0  BB 21 00 34 */	lmw r25, 0x34(r1)
/* 8007E0D4 0007ACB4  80 01 00 54 */	lwz r0, 0x54(r1)
/* 8007E0D8 0007ACB8  38 21 00 50 */	addi r1, r1, 0x50
/* 8007E0DC 0007ACBC  7C 08 03 A6 */	mtlr r0
/* 8007E0E0 0007ACC0  4E 80 00 20 */	blr 
}
#pragma peephole on
void func_8007DD7C(HSD_GObj*, Vec3*);               /* extern */
void func_8007DFD0(HSD_GObj*, Vec3*);               /* extern */

void func_8007E0E4(HSD_GObj* gobj)
{
    Vec3 sp10;
    Fighter* fp;
    u8 temp_r3;
    f32 phi_f0;
    f32 phi_f31;
    f32 phi_f30;

    fp = gobj->user_data;
    fp->xF8_playerNudgeVel.y = 0;
    fp->xF8_playerNudgeVel.x = 0;
    if (!fp->x2219_flag.bits.b1 && !fp->x2219_flag.bits.b5 &&
        fp->xE0_ground_or_air == 0) {

        if (!fp->x221F_flag.bits.b4) {
            phi_f30 = lbl_804D6554->x454;
            phi_f31 = lbl_804D6554->x458;
        } else {
            phi_f30 = lbl_804D6554->x45C;
            phi_f31 = lbl_804D6554->x460;
        }
        func_8007F8B4(fp, &sp10);
        if (!fp->x221D_flag.bits.b5) {
            if (!fp->x221F_flag.bits.b4) {
                func_8007DD7C(gobj, &sp10);
            } else {
                func_8007DFD0(gobj, &sp10);
            }
        }
        if (!fp->xF8_playerNudgeVel.y && sp10.z) {
            if (sp10.z < 0) {
                phi_f0 = phi_f30;
            } else {
                phi_f0 = -phi_f30;
            }
            fp->xF8_playerNudgeVel.y = phi_f0;
        }
        if ((fp->xF8_playerNudgeVel.y > 0 && sp10.z < 0 && sp10.z + fp->xF8_playerNudgeVel.y >= 0) ||
            (fp->xF8_playerNudgeVel.y < 0 && sp10.z > 0 && sp10.z + fp->xF8_playerNudgeVel.y <= 0)) {

            fp->xF8_playerNudgeVel.y = -sp10.z;
            sp10.z = 0;
        }
        if (sp10.z + fp->xF8_playerNudgeVel.y > phi_f31) {
            fp->xF8_playerNudgeVel.y = phi_f31 - sp10.z;
        } else if (sp10.z + fp->xF8_playerNudgeVel.y < -phi_f31) {
            fp->xF8_playerNudgeVel.y = -phi_f31 - sp10.z;
        }
        if (fp->x221F_flag.bits.b4 == 1) {
            fp->xF8_playerNudgeVel.x = 0;
        }
    }
}

asm void func_8007E2A4()
{
    nofralloc
/* 8007E2A4 0007AE84  80 83 00 2C */	lwz r4, 0x2c(r3)
/* 8007E2A8 0007AE88  C0 04 00 F4 */	lfs f0, 0xf4(r4)
/* 8007E2AC 0007AE8C  C0 24 08 48 */	lfs f1, 0x848(r4)
/* 8007E2B0 0007AE90  EC 01 00 32 */	fmuls f0, f1, f0
/* 8007E2B4 0007AE94  D0 04 00 98 */	stfs f0, 0x98(r4)
/* 8007E2B8 0007AE98  C0 24 08 44 */	lfs f1, 0x844(r4)
/* 8007E2BC 0007AE9C  C0 04 00 F4 */	lfs f0, 0xf4(r4)
/* 8007E2C0 0007AEA0  FC 20 08 50 */	fneg f1, f1
/* 8007E2C4 0007AEA4  EC 01 00 32 */	fmuls f0, f1, f0
/* 8007E2C8 0007AEA8  D0 04 00 9C */	stfs f0, 0x9c(r4)
/* 8007E2CC 0007AEAC  4E 80 00 20 */	blr 
}
#pragma peephole on

void func_8007E2D0(Fighter* fp, s16 arg1,
    void (*cb0)(HSD_GObj*), void (*cb1)(HSD_GObj*), void (*cb2)(HSD_GObj*))
{
    fp->x221E_flag.bits.b6 = 1;
    fp->x1A68 = arg1;
    fp->cb.x2190_callback_OnGrabFighter_Self = cb0;
    fp->cb.x2198_callback_OnGrabFighter_Victim = cb2;
    fp->cb.x2194_callback_x2194 = cb1;
}

void func_8007E2F4(Fighter* fp, s16 val)
{
    fp->x1A6A = val;
}

void func_8007E2FC(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    fp->xE4_ground_accel_1 = 0;
    fp->xE8_ground_accel_2 = 0;
    fp->x74_anim_vel.z = 0;
    fp->x74_anim_vel.y = 0;
    fp->x74_anim_vel.x = 0;
    fp->xEC_ground_vel = 0;
    fp->x80_self_vel.z = 0;
    fp->x80_self_vel.y = 0;
    fp->x80_self_vel.x = 0;
    fp->xF0_ground_kb_vel = 0;
    fp->x8c_kb_vel.z = 0;
    fp->x8c_kb_vel.y = 0;
    fp->x8c_kb_vel.x = 0;
    fp->xF4_ground_attacker_shield_kb_vel = 0;
    fp->x98_atk_shield_kb.z = 0;
    fp->x98_atk_shield_kb.y = 0;
    fp->x98_atk_shield_kb.x = 0;
    fp->xD4_unk_vel.z = 0;
    fp->xD4_unk_vel.y = 0;
    fp->xD4_unk_vel.x = 0;
}

void func_8007E358(HSD_GObj* gobj)
{
    HSD_JObj* jobj;
    Fighter* fp = gobj->user_data;
    jobj = fp->x5E8_fighterBones[func_8007500C(fp, 4)].x0_jobj;
    HSD_JObjGetTranslation(jobj, &fp->x1A7C);
}

void func_8007E3EC(HSD_GObj* gobj)
{
    Fighter* fp;
    HSD_JObj* jobj;
    Vec3 sp10;
    u32 unused[1];

    fp = gobj->user_data;
    jobj = fp->x5E8_fighterBones[func_8007500C(fp, 4)].x0_jobj;
    if (HSD_JObjMtxIsDirty(jobj)) {
        HSD_JObjGetTranslation(jobj, &sp10);
        sp10.x -= fp->x1A7C.x;
        sp10.y -= fp->x1A7C.y;
        sp10.z -= fp->x1A7C.z;
        fp->x1A7C.x += sp10.x * fp->x1A6C;
        fp->x1A7C.y += sp10.y * fp->x1A6C;
        fp->x1A7C.z += sp10.z * fp->x1A6C;
        HSD_JObjSetTranslate(jobj, &fp->x1A7C);
    }
}

// to match assert statement
#define ground_or_air xE0_ground_or_air

void func_8007E5AC(Fighter* fp)
{
    Vec* ground_normal = &fp->x6F0_collData.x154_groundNormal;
    f32 tmp = -func_80022C30(ground_normal->x, ground_normal->y);
    assert_line(1146, fp->ground_or_air == GA_Ground);
    func_80075CB4(fp, 0, tmp);
}

void func_8007E620(Fighter* fp, HSD_Joint* joint)
{
    if (fp->x20A0_accessory != NULL) {
        OSReport("fighter accessory already exsist!\n");
        assert_line(0x486, 0);
    }
    fp->x20A0_accessory = HSD_JObjLoadJoint(joint);
}

void func_8007E690(Fighter* fp, HSD_AnimJoint* arg1)
{
    if (fp->x20A0_accessory != NULL) {
        HSD_JObjAddAnimAll(fp->x20A0_accessory, arg1, NULL, NULL);
        HSD_JObjReqAnimAll(fp->x20A0_accessory, 0);
    }
}

extern void (*ft_OnItemRelease[])(HSD_GObj*, s32);
extern void (*lbl_803C1B20[])(HSD_GObj*, s32); // OnItemDrop?
extern void (*ft_OnItemCatch[])(HSD_GObj*, s32);

void func_8007E6DC(HSD_GObj* gobj, HSD_GObj* item_gobj, s32 arg2)
{
    Fighter* fp = gobj->user_data;
    if ((fp->x1978 != NULL) && (fp->x1978 == item_gobj)) {
        fp->x1978 = NULL;
        return;
    }
    if (func_800C5240(gobj)) {
        func_800C5500(gobj);
    }
    if (ft_OnItemRelease[fp->x4_fighterKind] != NULL) {
        ft_OnItemRelease[fp->x4_fighterKind](gobj, arg2);
    }
    func_8003EA08(fp->xC_playerID, fp->x221F_flag.bits.b4);
    fp->x1974_heldItem = NULL;
}

void func_8007E79C(HSD_GObj* gobj, s32 arg1)
{
    Fighter* fp = gobj->user_data;
    if (lbl_803C1B20[fp->x4_fighterKind] != NULL) {
        lbl_803C1B20[fp->x4_fighterKind](gobj, arg1);
    }
}

void func_8007E7E4(HSD_GObj* gobj, s32 arg1)
{
    Fighter* fp = gobj->user_data;
    if (ft_OnItemCatch[fp->x4_fighterKind] != NULL) {
        ft_OnItemCatch[fp->x4_fighterKind](gobj, arg1);
    }
}

void func_8007E82C(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    fp->x1984_heldItemSpec = NULL;
}

void func_8028B718(HSD_GObj*, f32);
void func_8028B780(HSD_GObj*, f32);
void func_8028B7E8(HSD_GObj*, f32);
void func_8028B850(HSD_GObj*, f32);
void func_8028B648(HSD_GObj*, f32);
void func_8028B6B0(HSD_GObj*, f32);
void func_8028B618(HSD_GObj*, f32);
void func_802BDD40(HSD_GObj*, f32);
void func_802BDDB4(HSD_GObj*, f32);
static void (*parasol_table_1[7])(HSD_GObj*, f32) = {
    func_8028B718,
    func_8028B780,
    func_8028B7E8,
    func_8028B850,
    func_8028B648,
    func_8028B6B0,
    func_8028B618,
};
static s32 parasol_table_2[7] = { 7, 8, 9, 10, 5, 6, 4, };
static void (*parasol_table_3[7])(HSD_GObj*, f32) = {
    NULL,
    NULL,
    NULL,
    NULL,
    func_802BDD40,
    NULL,
    func_802BDDB4,
};
static s32 parasol_table_4[7] = { -1, -1, -1, -1, 1, -1, 2, };

s32 func_8028B08C(void*, s32);
s32 func_802BDA40(void*, s32);

static const int FtParasol_None = -1;
#define ftGetParasolStatus func_8007E994

void func_8007E83C(HSD_GObj* gobj, s32 arg1, f32 div)
{
    f32 val;

    Fighter* fp = gobj->user_data;
    assert_line(0x4FC, ftGetParasolStatus(gobj) != FtParasol_None);
    if (div == 0) {
        val = fp->x89C;
    } else if (itGetKind(fp->x1974_heldItem) == It_Kind_Parasol) {
        val = fp->x89C * (func_8028B08C(fp->x1974_heldItem, parasol_table_2[arg1]) / div);
    } else {
        val = fp->x89C * (func_802BDA40(fp->x1974_heldItem, parasol_table_4[arg1]) / div);
    }
    if (itGetKind(fp->x1974_heldItem) == It_Kind_Parasol) {
        parasol_table_1[arg1](fp->x1974_heldItem, val);
    } else {
        parasol_table_3[arg1](fp->x1974_heldItem, val);
    }
}

s32 func_8007E994(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    if (fp->x1974_heldItem != NULL &&
        itGetKind(fp->x1974_heldItem) == It_Kind_Parasol) {
        switch (func_8026B7A4(fp->x1974_heldItem)) {
            case 7:
                return 0;
            case 8:
                return 1;
            case 9:
                return 2;
            case 10:
                return 3;
            case 5:
                return 4;
            case 6:
                return 5;
            case 4:
                return 6;
        }
    }
    if (fp->x1974_heldItem != NULL &&
        itGetKind(fp->x1974_heldItem) == It_Kind_PeachParasol) {
        switch (func_8026B7A4(fp->x1974_heldItem)) {
            case 1:
                return 4;
            case 0:
            case 2:
                return 6;
        }
    }
    return FtParasol_None;
}

#define M_PI 3.141592653589793

void func_8007EA90(Fighter* fp, s32 arg1)
{
    s32 temp_r31;
    f32 phi_f31;
    f32 phi_f30;
    Vec3 sp10;

    if (func_8016B0B4() == 0) {
        return;
    }
    if (fp->dmg.x1850_forceApplied) {
        phi_f30 = fp->dmg.x1850_forceApplied;
        phi_f31 = func_8008D7F0(fp);
        if (fp->dmg.x1844_direction > 0) {
            if (phi_f31 > M_PI) {
                phi_f31 = M_PI*3 - phi_f31;
            } else {
                phi_f31 = M_PI - phi_f31;
            }
        }
        sp10.x = fp->dmg.x1854_collpos.x;
        sp10.y = fp->dmg.x1854_collpos.y;
        sp10.z = 0;
    } else {
        phi_f31 = M_PI/2;
        phi_f30 = lbl_804D6554->x5C0;
        func_800866DC(fp->x0_fighter, &sp10);
    }
    temp_r31 = func_802E5F8C(fp->x0_fighter, &sp10, arg1, 1, phi_f31, phi_f30);
    if (fp->dmg.x18c4_source_ply != 6) {
        Player_SetUnk98(fp->dmg.x18c4_source_ply, temp_r31 + Player_GetUnk98(fp->dmg.x18c4_source_ply));
    }
}

void func_8007EBAC(Fighter* fp, u32 arg1, u32 arg2)
{
    if (Player_8003544C(fp->xC_playerID, fp->x221F_flag.bits.b4) &&
            !fp->x221F_flag.bits.b3 && !fp->x2224_flag.bits.b2) {
        func_80014574(fp->x618_player_id, arg1 + 2, arg1, arg2);
    }
}

void func_8007EC30(u32 arg0, u32 arg1)
{
    Fighter* fp;
    HSD_GObj* cur;
    u32 unused[4];

    cur = lbl_804D782C->unk20;
    while (cur != NULL) {
        fp = cur->user_data;
        func_8007EBAC(fp, arg0, arg1);
        cur = cur->next;
    }
}

void func_8007ECD4(Fighter* fp, s32 arg1)
{
    if (Player_8003544C(fp->xC_playerID, fp->x221F_flag.bits.b4)) {
        func_80378280(fp->x618_player_id, arg1 + 2);
    }
}

void func_8007ED2C(Fighter* fp)
{
    func_800145C0(fp->x618_player_id);
}

void func_8007ED50(Fighter* fp, s32 arg1)
{
    f32 tmp = arg1 * lbl_804D6554->x138 + lbl_804D6554->x13C;
    s32 val2 = tmp;
    if ((s32) tmp < 1) {
        return;
    }
    func_8007EBAC(fp, 5, val2);
}

void func_8007EE0C(Fighter* fp, s32 arg1)
{
    f32 tmp = arg1 * lbl_804D6554->xEC + lbl_804D6554->xF0;
    s32 val2 = tmp;
    if ((s32) tmp < 1) {
        return;
    }
    func_8007EBAC(fp, 10, val2);
}

void func_8007EEC8(Fighter* fp, s32 arg1, s32 arg2)
{
    if (fp->x1974_heldItem != NULL && fp->x1974_heldItem->classifier == 6
            && itGetKind(fp->x1974_heldItem) == It_Kind_BeamSword) {
        f32 multiplier = 1.0 / 256;
        f32 tmp = arg2 * multiplier;
        func_80284FC4(fp->x1974_heldItem, arg1, tmp);
    }
}

void func_8007EF5C(Fighter* fp, s32 arg1)
{
    if (fp->x1974_heldItem != NULL && fp->x1974_heldItem->classifier == 6
            && itGetKind(fp->x1974_heldItem) == It_Kind_BeamSword) {
        func_80285024(fp->x1974_heldItem, arg1);
    }
}

void func_8007EFC0(Fighter* fp, u32 val)
{
    fp->x209A = val;
}
