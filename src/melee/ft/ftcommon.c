#include <melee/ft/ftcommon.h>

#include <dolphin/os/os.h>
#include <melee/ft/code_80081B38.h>
#include <melee/ft/ft_unknown_006.h>
#include <melee/it/item.h>
#include <sysdolphin/baselib/jobj.h>

#include <math.h>

const Vec3 lbl_803B74A0 = { 0, 0, 0 };

void func_8007C930(Fighter* fp, f32 result)
{
    f32 absvel = fabs_inline(fp->xEC_ground_vel);
    if (fabs_inline(result) > absvel) {
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
        phi_f1 = fabs_inline(fp->xEC_ground_vel);
        phi_f0 = fabs_inline(argA);
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

    if (fabs_inline(phi_f1) >= arg8) {
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

    ground_normal = &fp->x6F0_collData.x14C_ground.normal;
    temp_f1 = Stage_GetGroundFrictionMultiplier(fp);
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
    Vec3* ground_normal = &fp->x6F0_collData.x14C_ground.normal;
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

void func_8007CCA0(Fighter* fp, f32 arg1)
{
    if (fp->xF0_ground_kb_vel < 0) {
        fp->xF0_ground_kb_vel = fp->xF0_ground_kb_vel + arg1;
        if (fp->xF0_ground_kb_vel > 0) {
            fp->xF0_ground_kb_vel = 0;
        }
    } else {
        fp->xF0_ground_kb_vel = fp->xF0_ground_kb_vel - arg1;
        if (fp->xF0_ground_kb_vel < 0) {
            fp->xF0_ground_kb_vel = 0;
        }
    }
}

void func_8007CCE8(Fighter* fp)
{
    Vec3* ground_normal;
    if (fp->xE0_ground_or_air == GA_Ground && fp->xF0_ground_kb_vel == 0) {
        ground_normal = &fp->x6F0_collData.x14C_ground.normal;
        fp->xF0_ground_kb_vel = fp->x8c_kb_vel.x;
        if (fp->xF0_ground_kb_vel > p_ftCommonData->x164) {
            fp->xF0_ground_kb_vel = p_ftCommonData->x164;
        }
        if (fp->xF0_ground_kb_vel < -p_ftCommonData->x164) {
            fp->xF0_ground_kb_vel = -p_ftCommonData->x164;
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
#define assert_line(line, cond) \
    ((cond) ? ((void) 0) : __assert(lbl_803C0D58, line, #cond))

#pragma push
asm f32 func_8007CDA4(Fighter*)
{ // clang-format off
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
} // clang-format on
#pragma pop

#pragma push
asm f32 func_8007CDF8(Fighter*)
{ // clang-format off
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
} // clang-format on
#pragma pop

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
    f32 phi_f2 = fabs_inline(fp->x80_self_vel.x);
    if (fabs_inline(val) >= phi_f2) {
        val = -fp->x80_self_vel.x;
    } else if (fp->x80_self_vel.x > 0) {
        val = -val;
    }
    fp->x74_anim_vel.x = val;
}

void func_8007CEF4(Fighter* fp)
{
    f32 result = fp->x110_attr.x180_AerialFriction;
    f32 lhs = fabs_inline(result);
    f32 phi_f1 = fabs_inline(fp->x80_self_vel.x);
    if (fabs_inline(result) >= phi_f1) {
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
    phi_f1 = fabs_inline(temp_f3);
    if (fabs_inline(temp_f3) > attr->x17C_AerialDriftMax) {
        phi_f2 = p_ftCommonData->x1FC;
        phi_f1 = fabs_inline(temp_f3);
        phi_f0 = fabs_inline(p_ftCommonData->x1FC);
        if (phi_f0 >= phi_f1) {
            phi_f2 = -temp_f3;
        } else if (temp_f3 > 0) {
            phi_f2 = -p_ftCommonData->x1FC;
        }
        fp->x74_anim_vel.x = phi_f2;
        return TRUE;
    } else {
        phi_f2 = fp->x110_attr.x180_AerialFriction;
        phi_f1 = fabs_inline(temp_f3);
        phi_f0 = fabs_inline(fp->x110_attr.x180_AerialFriction);
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
    phi_f0 = fabs_inline(temp_f3);
    if (fabs_inline(temp_f3) > val) {
        phi_f2 = p_ftCommonData->x1FC;
        phi_f1 = fabs_inline(temp_f3);
        phi_f0_2 = fabs_inline(p_ftCommonData->x1FC);
        if (phi_f0_2 >= phi_f1) {
            phi_f2 = -temp_f3;
        } else if (temp_f3 > 0) {
            phi_f2 = -p_ftCommonData->x1FC;
        }
        fp->x74_anim_vel.x = phi_f2;
        return 1;
    } else {
        phi_f2 = fp->x110_attr.x180_AerialFriction;
        phi_f1_2 = fabs_inline(temp_f3);
        phi_f0_3 = fabs_inline(fp->x110_attr.x180_AerialFriction);
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
        phi_f1 = fabs_inline(fp->x80_self_vel.x);
        if (fabs_inline(argB) >= phi_f1) {
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

    if (fabs_inline(fp->input.x620_lstick_x) >= arg8) {
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

    if (fabs_inline(fp->input.x620_lstick_x) >= arg8) {
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

void ftComm_ClampFallSpeed(Fighter* fp, f32 val)
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
        fp->input.x624_lstick_y <= -p_ftCommonData->x88 && fp->x671_timer_lstick_tilt_y < p_ftCommonData->x8C) {

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
    fp->x6F0_collData.x130_flags &= 0xFFFFFFEF;
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
    fp->x6F0_collData.x130_flags |= 0x10;
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
    fp->x6F0_collData.x130_flags |= 0x10;
}

void func_8007D698(Fighter* fp)
{
    fp->x1968_jumpsUsed = fp->x110_attr.x168_MaxJumps;
}

void func_8007D6A4(Fighter* fp)
{
    f32 tmp;
    if (fp->x594_animCurrFlags1.bits.b0) {
        fp->x80_self_vel.x = fp->x6A4_transNOffset.z * fp->facing_direction;
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
    fp->x6F0_collData.x130_flags &= 0xFFFFFFEF;
    if (!func_80084A18(fp->x0_fighter)) {
        OSReport("fighter ground no under Id! %d %d\n", fp->xC_playerID, fp->x10_action_state_index);
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
    if (fp->x594_animCurrFlags1.bits.b0) {
        fp->x80_self_vel.x = fp->x6A4_transNOffset.z * fp->facing_direction;
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
    fp->x6F0_collData.x130_flags &= 0xFFFFFFEF;
    if (!func_80084A18(fp->x0_fighter)) {
        OSReport("fighter ground no under Id! %d %d\n", fp->xC_playerID, fp->x10_action_state_index);
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

#include <melee/lb/lbrefract.h>

f32 func_8007D964(Fighter* fp)
{
    return atan2f(fp->input.x624_lstick_y, fabs_inline(fp->input.x620_lstick_x));
}

f32 func_8007D99C(Fighter* fp)
{
    return atan2f(fp->input.x63C_lsubStick_y, fabs_inline(fp->input.x638_lsubStick_x));
}

f32 func_8007D9D4(Fighter* fp)
{
    return atan2f(fp->input.x624_lstick_y, fp->input.x620_lstick_x);
}

void func_8007D9FC(Fighter* fp)
{
    f32 phi_f0;
    if (fp->input.x620_lstick_x >= 0) {
        phi_f0 = +1;
    } else {
        phi_f0 = -1;
    }
    fp->facing_direction = phi_f0;
}

void func_8007DA24(Fighter* fp)
{
    f32 phi_f0;
    if (fabs_inline(fp->input.x620_lstick_x) > p_ftCommonData->x0) {
        if (fp->input.x620_lstick_x >= 0) {
            phi_f0 = +1;
        } else {
            phi_f0 = -1;
        }
        fp->facing_direction = phi_f0;
    }
}

f32 func_8007DA74(s32 arg0, u32 arg1, f32 arg8)
{
    s32 tmp = arg0 * p_ftCommonData->x198 + p_ftCommonData->x19C;
    f32 result = (s32) (tmp * arg8);
    if (arg1 - 0x27 <= 1) {
        result = (s32) (result * p_ftCommonData->x1A0);
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
    Vec2* x0;
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

    if (fp->input.x620_lstick_x < -p_ftCommonData->x308) {
        fp->x1A50 = -1;
    }
    if (fp->input.x620_lstick_x > p_ftCommonData->x308) {
        fp->x1A50 = 1;
    }
    if (fp->input.x624_lstick_y < -p_ftCommonData->x308) {
        fp->x1A51 = -1;
    }
    if (fp->input.x624_lstick_y > p_ftCommonData->x308) {
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

inline f32 fabsf(f32 x)
{
    if (x < 0) {
        return -x;
    } else {
        return x;
    }
}

void func_8007DD7C(HSD_GObj* gobj, Vec3* v)
{
    u8 unused2[4];
    Vec2* temp_r31;
    Vec3 sp24;
    Fighter* arg_ft;
    Fighter* cur_ft;
    f32 temp_f0;
    s32 arg_gnd;
    s32 cur_gnd;
    HSD_GObj* cur;
    BOOL phi_r28;
    Vec2* vtmp;
    u8 unused[0x14];

    arg_ft = gobj->user_data;
    phi_r28 = FALSE;
    for (cur = lbl_804D782C->x20_fighters; cur != NULL; cur = cur->next) {
        temp_r31 = &arg_ft->x2C4;
        if (cur != gobj && !func_80086FD4(cur, gobj)) {
            cur_ft = cur->user_data;
            if (cur_ft->x221F_flag.bits.b3 || cur_ft->xE0_ground_or_air != 0 ||
                cur_ft->x1A58_interactedFighter != NULL || cur_ft->x221F_flag.bits.b4) {
                continue;
            }
            arg_gnd = arg_ft->x6F0_collData.x14C_ground.index;
            cur_gnd = cur_ft->x6F0_collData.x14C_ground.index;
            if (arg_gnd == cur_gnd || cur_gnd == func_8004DB78(arg_gnd)
                                   || cur_gnd == func_8004DC04(arg_gnd)) {
                func_8007F8B4(cur_ft, &sp24);
                vtmp = &cur_ft->x2C4;
                temp_f0 = (temp_r31->x * arg_ft->facing_direction + v->x) -
                          (cur_ft->facing_direction * vtmp->x + sp24.x);
                if (fabsf(temp_f0) < temp_r31->y + vtmp->y) {
                    if (temp_f0) {
                        arg_ft->xF8_playerNudgeVel.x += temp_f0 < 0 ? -p_ftCommonData->x450 : p_ftCommonData->x450;
                    } else {
                        arg_ft->xF8_playerNudgeVel.x += phi_r28 ? -p_ftCommonData->x450 : p_ftCommonData->x450;
                    }
                    if (v->z - sp24.z) {
                        arg_ft->xF8_playerNudgeVel.y += v->z - sp24.z < 0 ? -p_ftCommonData->x454 : p_ftCommonData->x454;
                    } else if (temp_f0) {
                        arg_ft->xF8_playerNudgeVel.y += temp_f0 < 0 ? -p_ftCommonData->x454 : p_ftCommonData->x454;
                    } else {
                        arg_ft->xF8_playerNudgeVel.y += phi_r28 ? -p_ftCommonData->x454 : p_ftCommonData->x454;
                    }
                }
            }
        } else {
            phi_r28 = TRUE;
        }
    }
}

#include <melee/pl/player.h>

void func_8007DFD0(HSD_GObj* gobj, Vec3* arg1)
{
    u8 unused2[4];
    Vec3 sp1C;
    Vec2* temp_r31;
    HSD_GObj *new_var;
    s32 new_var2;
    Fighter* fp;
    Fighter* temp_r3;
    f32 temp_f1;
    s32 temp_r0;
    s32 temp_r30;
    Vec2* tmp;
    u8 unused[0xC];

    fp = gobj->user_data;
    temp_r31 = &fp->x2C4;
    new_var = Player_GetEntity(fp->xC_playerID);
    temp_r3 = new_var->user_data;
    if (!temp_r3->x221F_flag.bits.b3 && temp_r3->xE0_ground_or_air == 0) {
        temp_r0 = fp->x6F0_collData.x14C_ground.index;
        temp_r30 = (new_var2 = temp_r3->x6F0_collData.x14C_ground.index);
        if (temp_r0 == temp_r30 || temp_r30 == func_8004DB78(temp_r0)
                                || temp_r30 == func_8004DC04(temp_r0)) {
            func_8007F8B4(temp_r3, &sp1C);
            tmp = &temp_r3->x2C4;
            temp_f1 = (temp_r31->x * fp->facing_direction + arg1->x) -
                      (temp_r3->facing_direction * tmp->x + sp1C.x);
            if (fabsf(temp_f1) < temp_r31->y + tmp->y) {
                fp->xF8_playerNudgeVel.y -= p_ftCommonData->x45C;
            }
        }
    }
    func_8007DD7C(gobj, arg1);
}

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
            phi_f30 = p_ftCommonData->x454;
            phi_f31 = p_ftCommonData->x458;
        } else {
            phi_f30 = p_ftCommonData->x45C;
            phi_f31 = p_ftCommonData->x460;
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

HSD_GObj* func_8007E2A4(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    CollData* colldata = &fp->x6F0_collData;
    fp->x98_atk_shield_kb.x = colldata->x14C_ground.normal.y * fp->xF4_ground_attacker_shield_kb_vel;
    fp->x98_atk_shield_kb.y = -colldata->x14C_ground.normal.x * fp->xF4_ground_attacker_shield_kb_vel;
    return gobj;
}

void ftCommon_SetOnGrabCallbacks(Fighter* fp, s16 arg1,
                                 void (*cb0)(HSD_GObj*), void (*cb1)(HSD_GObj*), void (*cb2)(HSD_GObj*, HSD_GObj*))
{
    fp->x221E_flag.bits.b6 = 1;
    fp->x1A68 = arg1;
    fp->cb.x2190_callback_OnGrabFighter_Self = cb0;
    fp->cb.x2198_callback_OnGrabFighter_Victim = cb2;
    fp->cb.x2194_callback = cb1;
}

void func_8007E2F4(Fighter* fp, s16 val)
{
    fp->x1A6A = val;
}

inline void _func_8007E2FC_inline(HSD_GObj* gobj)
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

void func_8007E2FC(HSD_GObj* gobj)
{
    _func_8007E2FC_inline(gobj);
}

#include <melee/ft/ftparts.h>

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
    Vec* ground_normal = &fp->x6F0_collData.x14C_ground.normal;
    f32 tmp = -atan2f(ground_normal->x, ground_normal->y);
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

extern void (*ft_OnItemDropExt[])(HSD_GObj*, s32);
extern void (*ft_OnItemDrop[])(HSD_GObj*, s32); // OnItemDrop?
extern void (*ft_OnItemPickup[])(HSD_GObj*, s32);

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
    if (ft_OnItemDropExt[fp->x4_fighterKind] != NULL) {
        ft_OnItemDropExt[fp->x4_fighterKind](gobj, arg2);
    }
    func_8003EA08(fp->xC_playerID, fp->x221F_flag.bits.b4);
    fp->x1974_heldItem = NULL;
}

void func_8007E79C(HSD_GObj* gobj, s32 arg1)
{
    Fighter* fp = gobj->user_data;
    if (ft_OnItemDrop[fp->x4_fighterKind] != NULL) {
        ft_OnItemDrop[fp->x4_fighterKind](gobj, arg1);
    }
}

void func_8007E7E4(HSD_GObj* gobj, s32 arg1)
{
    Fighter* fp = gobj->user_data;
    if (ft_OnItemPickup[fp->x4_fighterKind] != NULL) {
        ft_OnItemPickup[fp->x4_fighterKind](gobj, arg1);
    }
}

void func_8007E82C(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    fp->x1984_heldItemSpec = NULL;
}

#include <melee/it/enums.h>

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

void func_8007E83C(HSD_GObj* gobj, s32 arg1, f32 div)
{
    f32 val;

    Fighter* fp = gobj->user_data;
    assert_line(0x4FC, ftGetParasolStatus(gobj) != FtParasol_None);
    if (div == 0) {
        val = fp->x89C_frameSpeedMul;
    } else if (itGetKind(fp->x1974_heldItem) == It_Kind_Parasol) {
        val = fp->x89C_frameSpeedMul * (func_8028B08C(fp->x1974_heldItem, parasol_table_2[arg1]) / div);
    } else {
        val = fp->x89C_frameSpeedMul * (func_802BDA40(fp->x1974_heldItem, parasol_table_4[arg1]) / div);
    }
    if (itGetKind(fp->x1974_heldItem) == It_Kind_Parasol) {
        parasol_table_1[arg1](fp->x1974_heldItem, val);
    } else {
        parasol_table_3[arg1](fp->x1974_heldItem, val);
    }
}

s32 ftGetParasolStatus(HSD_GObj* gobj)
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
        itGetKind(fp->x1974_heldItem) == It_Kind_Peach_Parasol) {
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
        phi_f30 = p_ftCommonData->x5C0;
        func_800866DC(fp->x0_fighter, &sp10);
    }
    temp_r31 = func_802E5F8C(fp->x0_fighter, &sp10, arg1, 1, phi_f31, phi_f30);
    if (fp->dmg.x18c4_source_ply != 6) {
        Player_SetUnk98(fp->dmg.x18c4_source_ply, temp_r31 + Player_GetUnk98(fp->dmg.x18c4_source_ply));
    }
}

#include <melee/lb/lbunknown_003.h>

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

    cur = lbl_804D782C->x20_fighters;
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

#include <melee/lb/lbunknown_003.h>

void func_8007ED2C(Fighter* fp)
{
    func_800145C0(fp->x618_player_id);
}

void func_8007ED50(Fighter* fp, s32 arg1)
{
    f32 tmp = arg1 * p_ftCommonData->x138 + p_ftCommonData->x13C;
    s32 val2 = tmp;
    if ((s32) tmp < 1) {
        return;
    }
    func_8007EBAC(fp, 5, val2);
}

void func_8007EE0C(Fighter* fp, s32 arg1)
{
    f32 tmp = arg1 * p_ftCommonData->xEC + p_ftCommonData->xF0;
    s32 val2 = tmp;
    if ((s32) tmp < 1) {
        return;
    }
    func_8007EBAC(fp, 10, val2);
}

void func_8007EEC8(Fighter* fp, s32 arg1, s32 arg2)
{
    if (fp->x1974_heldItem != NULL && fp->x1974_heldItem->classifier == 6
            && itGetKind(fp->x1974_heldItem) == It_Kind_Sword) {
        f32 multiplier = 1.0 / 256;
        f32 tmp = arg2 * multiplier;
        func_80284FC4(fp->x1974_heldItem, arg1, tmp);
    }
}

void func_8007EF5C(Fighter* fp, s32 arg1)
{
    if (fp->x1974_heldItem != NULL && fp->x1974_heldItem->classifier == 6
            && itGetKind(fp->x1974_heldItem) == It_Kind_Sword) {
        func_80285024(fp->x1974_heldItem, arg1);
    }
}

void func_8007EFC0(Fighter* fp, u32 val)
{
    fp->x209A = val;
}

void func_8007EFC8(HSD_GObj* gobj, void (*arg1)(HSD_GObj*))
{
    Fighter* src;
    HSD_GObj* dst_gobj;
    Fighter* dst;
    s32 tmp_bit;
    u32 unused[4];

    src = gobj->user_data;
    dst_gobj = Player_GetEntityAtIndex(src->xC_playerID, 1);
    dst = dst_gobj->user_data;
    Player_SwapTransformedStates(src->xC_playerID,
        src->x221F_flag.bits.b4, dst->x221F_flag.bits.b4);
    tmp_bit = src->x221F_flag.bits.b4;
    src->x221F_flag.bits.b4 = dst->x221F_flag.bits.b4;
    dst->x221F_flag.bits.b4 = tmp_bit;
    Fighter_UnkInitReset_80067C98(dst);
    _func_8007E2FC_inline(dst_gobj);
    dst->xB0_pos = src->xB0_pos;
    dst->xBC_prevPos = src->xBC_prevPos;
    dst->xC8_pos_delta = src->xC8_pos_delta;
    dst->facing_direction = src->facing_direction;
    dst->dmg.x1830_percent = src->dmg.x1830_percent;
    Player_SetHPByIndex(dst->xC_playerID,
        dst->x221F_flag.bits.b4, dst->dmg.x1830_percent);
    dst->dmg.x18F0 = src->dmg.x18F0;
    dst->x80_self_vel = src->x80_self_vel;
    dst->xE0_ground_or_air = src->xE0_ground_or_air;
    dst->xEC_ground_vel = src->xEC_ground_vel;
    dst->xF0_ground_kb_vel = src->xF0_ground_kb_vel;
    dst->xF4_ground_attacker_shield_kb_vel = src->xF4_ground_attacker_shield_kb_vel;
    dst->xF8_playerNudgeVel.x = src->xF8_playerNudgeVel.x;
    dst->xF8_playerNudgeVel.y = src->xF8_playerNudgeVel.y;
    dst->input = src->input;
    dst->x670_timer_lstick_tilt_x = src->x670_timer_lstick_tilt_x;
    dst->x671_timer_lstick_tilt_y = src->x671_timer_lstick_tilt_y;
    dst->x672_input_timer_counter = src->x672_input_timer_counter;
    dst->x673 = src->x673;
    dst->x674 = src->x674;
    dst->x675 = src->x675;
    dst->x679_x = src->x679_x;
    dst->x67A_y = src->x67A_y;
    dst->x67B = src->x67B;
    dst->x685 = src->x685;
    dst->x686 = src->x686;
    dst->x687 = src->x687;
    dst->x688 = src->x688;
    dst->x689 = src->x689;
    dst->x68A = src->x68A;
    dst->x68B = src->x68B;
    dst->x67C = src->x67C;
    dst->x67D = src->x67D;
    dst->x67E = src->x67E;
    dst->x681 = src->x681;
    dst->x682 = src->x682;
    dst->x67F = src->x67F;
    dst->x680 = src->x680;
    dst->x683 = src->x683;
    dst->x684 = src->x684;
    dst->dmg.x18c4_source_ply = src->dmg.x18c4_source_ply;
    dst->dmg.x18C8 = src->dmg.x18C8;
    dst->x221F_flag.bits.b5 = src->x221F_flag.bits.b5;
    dst->dmg.x18CC = src->dmg.x18CC;
    dst->dmg.x18D0 = src->dmg.x18D0;
    dst->dmg.x18d4 = src->dmg.x18d4;
    dst->dmg.x18ec_instancehitby = src->dmg.x18ec_instancehitby;
    dst->x21FC_flag.u8 = src->x21FC_flag.u8;
    dst->x2221_flag.bits.b7 = src->x2221_flag.bits.b7;
    dst->x2221_flag.bits.b6 = src->x2221_flag.bits.b6;
    dst->x2221_flag.bits.b4 = src->x2221_flag.bits.b4;
    dst->x2221_flag.bits.b5 = src->x2221_flag.bits.b5;
    dst->x2104 = src->x2104;
    dst->dmg.x1910 = src->dmg.x1910;
    dst->x1968_jumpsUsed = src->x1968_jumpsUsed;
    dst->x1969_walljumpUsed = src->x1969_walljumpUsed;
    dst->x1998_shieldHealth = src->x1998_shieldHealth;
    dst->x232C = src->x232C;
    dst->x2330 = src->x2330;
    dst->x2338 = src->x2338;
    dst->x2224_flag.bits.b2 = src->x2224_flag.bits.b2;
    if (src->x221D_flag.bits.b6) {
        func_8007B7FC(dst, src->x2004);
        func_800C0358(src, dst, 0x6B);
        func_800880D8(src);
    } else {
        func_800C0200(dst, 9);
    }
    if ((src->x198C = 2) && (src->x1990 != 0)) {
        func_8007B760(dst_gobj, src->x1990);
    }
    dst->x2220_flag.bits.b5 = src->x2220_flag.bits.b5;
    dst->x2220_flag.bits.b6 = src->x2220_flag.bits.b6;
    dst->x2008 = src->x2008;
    ftData_SetScale(dst_gobj, src->x34_scale.y);
    if (src->x2223_flag.bits.b7) {
        func_800C8348(dst_gobj, src->x2028, src->x202C);
        func_800C8540(gobj);
    }
    if (src->x2226_flag.bits.b4) {
        if (!src->x2226_flag.bits.b7) {
            func_800C88D4(dst_gobj, src->x2030, 0);
        }
        func_800C8A64(gobj);
    }
    dst->x221E_flag.bits.b4 = src->x221E_flag.bits.b4;
    if (src->x197C != NULL) {
        func_8026B9A8(src->x197C, dst_gobj, dst->x10C_ftData->x8->unk12);
        func_802950D4(src->x197C, 0);
        func_8007F948(dst_gobj, src->x197C, src->x2014);
        func_8007FA00(gobj);
    } else {
        dst->x197C = NULL;
    }
    if (src->x1980 != NULL) {
        func_8026B9A8(src->x1980, dst_gobj, dst->x10C_ftData->x8->unk12);
        func_8007FE84(dst_gobj, src->x1980, src->x2018, src->x2024);
        func_8007FDA0(gobj);
    } else {
        dst->x1980 = NULL;
    }
    func_800D105C(dst_gobj);
    func_80076064(dst);
    func_800849EC(src, dst);
    func_80081C88(dst_gobj, src->x34_scale.y);
    if (src->x1974_heldItem != NULL) {
        dst->x1974_heldItem = src->x1974_heldItem;
        dst->x221E_flag.bits.b3 = src->x221E_flag.bits.b3;
        func_80094818(dst_gobj, 1);
        func_8026B9A8(src->x1974_heldItem, dst_gobj, dst->x10C_ftData->x8->unk10);
    }
    func_80322314();
    func_800BFD04(gobj);
    arg1(dst_gobj);
}

extern void (*ft_OnItemInvisible[])(HSD_GObj*);
extern void (*ft_OnItemVisible[])(HSD_GObj*);
extern void (*ft_OnKnockbackEnter[])(HSD_GObj*);
extern void (*ft_OnKnockbackExit[])(HSD_GObj*);

void func_8007F578(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    if (fp->x1974_heldItem == NULL) {
        return;
    }
    if (ft_OnItemInvisible[fp->x4_fighterKind] != NULL) {
        ft_OnItemInvisible[fp->x4_fighterKind](gobj);
    }
}

void func_8007F5CC(HSD_GObj* gobj, s32 arg1)
{
    Fighter* fp;
    HSD_GObj* item;
    u32 unused[2];

    fp = gobj->user_data;
    item = fp->x1974_heldItem;
    if (item != NULL && fp->x221E_flag.bits.b3 != arg1) {
        if (arg1 == 0) {
            func_8007F578(gobj);
        } else if (item != NULL) {
            if (ft_OnItemVisible[fp->x4_fighterKind] != NULL) {
                ft_OnItemVisible[fp->x4_fighterKind](gobj);
            }
        }
    }
    fp->x221E_flag.bits.b3 = arg1;
}

f32 Fighter_GetModelScale(Fighter* fp)
{
    return fp->x34_scale.y * fp->x110_attr.x19C_ModelScaling;
}

void func_8007F6A4(Fighter* fp, HSD_JObj* jobj)
{
    Vec3 scale;
    f32 val = 1.0f / fp->x10C_ftData->x0->x8C;
    scale.z = val;
    scale.y = val;
    scale.x = val;
    HSD_JObjSetScale(jobj, &scale);
}

void func_8007F76C(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    fp->xEC_ground_vel = fp->facing_direction * fabs_inline(fp->xEC_ground_vel);
    fp->x80_self_vel.x = fp->facing_direction * fabs_inline(fp->x80_self_vel.x);
}

void func_8007F7B4(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    fp->xEC_ground_vel = -fp->facing_direction * fabs_inline(fp->xEC_ground_vel);
    fp->x80_self_vel.x = -fp->facing_direction * fabs_inline(fp->x80_self_vel.x);
}

void* func_8007F804(Fighter* fp)
{
    if (fp->x34_scale.z != 1) {
        return &fp->x44_mtx;
    }
    return NULL;
}

void func_8007F824(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    if (ft_OnKnockbackEnter[fp->x4_fighterKind] != NULL) {
        ft_OnKnockbackEnter[fp->x4_fighterKind](gobj);
    }
}

void func_8007F86C(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    if (ft_OnKnockbackExit[fp->x4_fighterKind] != NULL) {
        ft_OnKnockbackExit[fp->x4_fighterKind](gobj);
    }
}

void func_8007F8B4(Fighter* fp, Vec3* v)
{
    v->x = fp->xB0_pos.x + fp->xD4_unk_vel.x;
    v->y = fp->xB0_pos.y + fp->xD4_unk_vel.y;
    v->z = fp->xB0_pos.z + fp->xD4_unk_vel.z;
}

extern void (*lbl_803C1C28[])(HSD_GObj*);

void func_8007F8E8(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    if (fp->x197C == NULL || fp->x1980 == NULL) {
        if (lbl_803C1C28[fp->x4_fighterKind] != NULL) {
            lbl_803C1C28[fp->x4_fighterKind](gobj);
        }
    }
}

extern void (*lbl_803C1BA4[])(HSD_GObj*);

inline void _func_8007F948_inline(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    if (fp->x197C == NULL || fp->x1980 == NULL) {
        if (lbl_803C1BA4[fp->x4_fighterKind] != NULL) {
            lbl_803C1BA4[fp->x4_fighterKind](gobj);
        }
    }
}

void func_8007F948(HSD_GObj* gobj, HSD_GObj* arg1, s32 arg2)
{
    Fighter* fp = gobj->user_data;
    fp->x197C = arg1;
    fp->x2014 = arg2;
    _func_8007F948_inline(gobj);
}

void func_8007F9B4(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    fp->x197C = NULL;
    func_800D105C(gobj);
    func_80081C88(gobj, fp->x34_scale.y);
}

#include <melee/it/code_8027CF30.h>

void func_8007FA00(HSD_GObj* gobj)
{
    Fighter* fp;
    Vec3* vec;
    u32 unused[2];

    fp = gobj->user_data;
    vec = &fp->x110_attr.x224;
    func_80294EB0(fp->x197C, &vec[1], vec);
    func_80294E78(fp->x197C, fp->x34_scale.y * vec[2].x);
}

void func_8007FA58(HSD_GObj* gobj, HSD_GObj* arg1)
{
    Vec3 vec;
    Fighter* fp;
    Fighter* fp2;
    u32 unused[7];

    fp = fp2 = gobj->user_data;
    if (fp2->x197C != NULL) {
        fp->x2014 = func_8026B54C(arg1);
        func_80088148(fp, 0x117, 0x7F, 0x40);
        func_8007EBAC(fp, 0x10, 0);
        func_8026A8EC(arg1);
        return;
    }
    vec = lbl_803B74A0;
    func_8026BD0C(arg1);
    func_8026ABD8(arg1, &vec, 0);
    func_8026AB54(arg1, gobj, fp->x10C_ftData->x8->unk12);
    func_8007F948(gobj, arg1, func_8026B54C(arg1));
    func_800D105C(gobj);
    func_80081C88(gobj, fp->x34_scale.y);
    func_80088148(fp, 0x117, 0x7F, 0x40);
    func_8007EBAC(fp, 0x10, 0);
    func_8026BCF4(arg1);
    func_8007FA00(gobj);
}

void func_8007FC7C(HSD_GObj* gobj, f32 arg8)
{
    HSD_GObj* item_gobj;
    Fighter* fp;
    s32 sp20;
    u32 unused;

    fp = gobj->user_data;
    sp20 = arg8 * p_ftCommonData->x704;
    if (fp->x1980 != NULL) {
        fp->x2018 += sp20;
        if (fp->x2018 > p_ftCommonData->x700) {
            fp->x2018 = p_ftCommonData->x700;
        }
        sp20 = fp->x2024;
        fp->x2024 = sp20 + arg8;
        func_8007FDA0(gobj);
    } else {
        item_gobj = func_8029A748(gobj, &fp->xB0_pos, fp->x10C_ftData->x8->unk12,
                                  fp->facing_direction);
        if (item_gobj != NULL) {
            func_8007FE84(gobj, item_gobj, sp20, arg8);
            func_8007FDA0(gobj);
        }
    }
    func_80088148(fp, 0x11F, 0x7F, 0x40);
}

inline f32 fminf(f32 a, f32 b)
{
    f32 result = a;
    if (a > b) {
        result = b;
    }
    return result;
}

void func_8007FDA0(HSD_GObj* gobj)
{
    Vec3 sp20;
    Fighter* fp;
    f32 temp_f1;
    Vec3* temp_r30;
    f32 phi_f31;
    u32 unused[4];

    fp = gobj->user_data;
    temp_r30 = &fp->x110_attr.x240;
    phi_f31 = fminf(p_ftCommonData->x710 * fp->x2024 + p_ftCommonData->x708, p_ftCommonData->x70C);
    temp_f1 = 1.0f / phi_f31;
    sp20 = *temp_r30;
    sp20.x *= temp_f1;
    sp20.y *= temp_f1;
    sp20.z *= temp_f1;
    func_8029A8F4(fp->x1980, &sp20, temp_f1);
    func_8029A89C(fp->x1980, phi_f31 * temp_r30[1].x * fp->x34_scale.y);
}

void func_8007FE84(HSD_GObj* gobj, HSD_GObj* item_gobj, s32 arg2, f32 arg3)
{
    u32 unused[2];
    Fighter* fp = gobj->user_data;
    fp->x1980 = item_gobj;
    fp->x2018 = arg2;
    fp->x201C = p_ftCommonData->x6F8;
    fp->x2024 = arg3;
    fp->x2021 = 0;
    fp->x2020 = 0;
    func_8007EBAC(fp, 2, 0);
    _func_8007F948_inline(gobj);
}

void func_8007FF74(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    fp->x1980 = NULL;
    func_8007ECD4(fp, 2);
    func_80040460(fp->xC_playerID, fp->x221F_flag.bits.b4);
}

BOOL func_8007FFD8(Fighter* fp, f32 arg8)
{
    s32 phi_r31;
    s8 b0, b1;
    phi_r31 = FALSE;
    if ((fp->input.x668 & 0x80000F00) != 0) {
        fp->x2018 -= arg8;
        phi_r31 = TRUE;
    }
    b0 = fp->x2020;
    b1 = fp->x2021;
    if (fp->input.x620_lstick_x < -p_ftCommonData->x308) {
        fp->x2020 = -1;
    }
    if (fp->input.x620_lstick_x > p_ftCommonData->x308) {
        fp->x2020 = 1;
    }
    if (fp->input.x624_lstick_y < -p_ftCommonData->x308) {
        fp->x2021 = -1;
    }
    if (fp->input.x624_lstick_y > p_ftCommonData->x308) {
        fp->x2021 = 1;
    }
    if (b0 != fp->x2020 || b1 != fp->x2021) {
        fp->x2018 = fp->x2018 - arg8;
        phi_r31 = TRUE;
    }
    func_800402D0(fp->xC_playerID, fp->x221F_flag.bits.b4, phi_r31);
    return phi_r31;
}

BOOL func_80080144(Fighter* fp)
{
    int kind = fp->x4_fighterKind;
    if ((kind == FTKIND_POPO || kind == FTKIND_NANA) && fp->x619_costume_id >= 2) {
        return TRUE;
    }
    return FALSE;
}

// https://decomp.me/scratch/Jjkwx
void func_80080174(Fighter *fp)
{
    f32 phi_f2;
    f32 phi_f3;
    Vec3* v;
    u32 unused[4];

    if (fp->x197C != NULL) {
        func_80294E78(fp->x197C, fp->x34_scale.y * fp->x110_attr.x23C);
    }
    if (fp->x1980 != NULL) {
        v = &fp->x110_attr.x240;
        if ((phi_f2 = p_ftCommonData->x710 * fp->x2024 + p_ftCommonData->x708) > (phi_f3 = p_ftCommonData->x70C)) {
            phi_f2 = phi_f3;
        }
        func_8029A89C(fp->x1980, phi_f2 * v[1].x * fp->x34_scale.y);
    }
}

void func_8008021C(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    Vec2 shift;
    Vec2* result;
    u32 unused;

    fp->dmg.x18BC = 0;
    fp->dmg.x18B8 = 0;
    if (func_80090690(fp, &shift)) {
        fp->dmg.x18B8 += shift.x;
        fp->dmg.x18BC += shift.y;
    }
    if (fp->x2224_flag.bits.b5) {
        Vec2* temp_r3 = &lbl_804D652C->x0[fp->x1A52];
        shift.x = temp_r3->x;
        shift.y = temp_r3->y;
        result = &shift;
    } else {
        result = NULL;
    }
    if (result != NULL) {
        fp->dmg.x18B8 += shift.x;
        fp->dmg.x18BC += shift.y;
    }
    if (func_800DEEE8(fp, &shift)) {
        fp->dmg.x18B8 += shift.x;
        fp->dmg.x18BC += shift.y;
    }
}

void func_8008031C(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    if (fabs_inline(fp->input.x620_lstick_x) >= p_ftCommonData->x7B8 && fp->x679_x < p_ftCommonData->x7C0 ||
        fabs_inline(fp->input.x624_lstick_y) >= p_ftCommonData->x7B8 && fp->x67A_y < p_ftCommonData->x7C0) {
        Player_UpdateJoystickCountByIndex((s32) fp->xC_playerID, fp->x221F_flag.bits.b4);
        fp->x67A_y = 0xFE;
        fp->x679_x = 0xFE;
    }
    if (fabs_inline(fp->input.x650) >= p_ftCommonData->x7BC) {
        if (fp->x67B < p_ftCommonData->x7C0) {
            Player_UpdateJoystickCountByIndex((s32) fp->xC_playerID, fp->x221F_flag.bits.b4);
            fp->x67B = 0xFE;
        }
    }
}

void func_80080460(Fighter* fp)
{
    fp->x2225_flag.bits.b6 = TRUE;
}

void func_80080474(Fighter* fp)
{
    fp->x2225_flag.bits.b6 = fp->x2225_flag.bits.b5;
}

void func_80080484(Fighter* fp)
{
    if (fp->x2114_SmashAttr.x2138_smashSinceHitbox == -1) {
        fp->x2114_SmashAttr.x2138_smashSinceHitbox = 0;
    }
}

void func_800804A0(Fighter* fp, f32 arg8)
{
    f32 temp_f1;
    f32 phi_f31 = arg8;
    if ((temp_f1 = Stage_GetGroundFrictionMultiplier(fp)) < 1) {
        phi_f31 *= temp_f1;
    }
    fp->xE8_ground_accel_2 = phi_f31;
}

// DataOffset_PlayerScale_MultiplyBySomething, returns fp->x40*fp->x34
f32 func_800804EC(Fighter* fp)
{
    return fp->x40 * fp->x34_scale.x;
}

void func_800804FC(Fighter* fp)
{
    if (fp->xE0_ground_or_air == GA_Ground) {
        fp->dmg.x18c4_source_ply = 6;
        fp->dmg.x18C8 = -1;
    }
}
