#include <platform.h>
#include "ft/forward.h"

#include "ftCo_EscapeAir.h"

#include "ftCo_FallSpecial.h"
#include "ftCo_ItemThrow.h"

#include "ft/fighter.h"
#include "ft/ft_081B.h"
#include "ft/ft_0877.h"
#include "ft/ft_08A4.h"
#include "ft/ftcommon.h"

#include <placeholder.h>
#include <MSL/trigf.h>

typedef enum cmd_var_idx {
    cmd_skip_decay,
} cmd_var_idx;

bool ftCo_80099A58(Fighter_GObj* gobj)
{
    ftCo_Fighter* fp = gobj->user_data;
    if (fp->input.x668 & (HSD_PAD_R | HSD_PAD_L)) {
        ftCo_80099A9C(gobj, p_ftCommonData->x334);
        return true;
    }
    return false;
}

static inline void inlineA0(ftCo_Fighter* fp)
{
    fp->mv.co.escapeair.self_vel = fp->self_vel;
    if (ABS(fp->input.lstick.x) < p_ftCommonData->escapeair_deadzone.x) {
        if (ABS(fp->input.lstick.y) < p_ftCommonData->escapeair_deadzone.y) {
            fp->self_vel.y = 0;
            fp->self_vel.x = 0;
            return;
        }
    }
    {
        float angle = ftCommon_8007D9D4(fp);
        fp->self_vel.x = p_ftCommonData->escapeair_force * cosf(angle);
        fp->self_vel.y = p_ftCommonData->escapeair_force * sinf(angle);
    }
}

void ftCo_80099A9C(Fighter_GObj* gobj, int timer)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8] = { 0 };
#endif
    ftCo_Fighter* fp = gobj->user_data;
    ftCo_800D705C(gobj);
    inlineA0(fp);
    fp->cmd_vars[cmd_skip_decay] = false;
    fp->mv.co.escapeair.timer = timer;
    Fighter_ChangeMotionState(gobj, ftCo_MS_EscapeAir, Ft_MF_None, NULL, 0, 1,
                              0);
    ftAnim_8006EBA4(gobj);
    ftCommon_8007EBAC(fp, 23, 0);
}

void ftCo_EscapeAir_Anim(Fighter_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8] = { 0 };
#endif
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ft_80096900(gobj, 1, 1, false, p_ftCommonData->x340,
                    p_ftCommonData->x344);
    }
}

ASM void ftCo_EscapeAir_IASA(ftCo_GObj* gobj)
#if !defined(MUST_MATCH) || defined(WIP)
{
    ftCo_Fighter* fp = gobj->user_data;
    if (fp->mv.co.escapeair.timer != 0) {
        Vec3 self_vel = fp->mv.co.escapeair.self_vel;
        bool b;
        if (ft_80095328(gobj, &b)) {
            if (!b) {
                return;
            }
            fp->self_vel = self_vel;
            return;
        }
        ftCo_800D705C(gobj);
        --fp->mv.co.escapeair.timer;
    }
    if (ftCo_800C3B10(gobj)) {
        fp->self_vel.x *= 0.1f;
    }
}
#else // clang-format off
{ nofralloc
/* 80099C24 00096804  7C 08 02 A6 */	mflr r0
/* 80099C28 00096808  90 01 00 04 */	stw r0, 4(r1)
/* 80099C2C 0009680C  94 21 FF D8 */	stwu r1, -0x28(r1)
/* 80099C30 00096810  93 E1 00 24 */	stw r31, 0x24(r1)
/* 80099C34 00096814  93 C1 00 20 */	stw r30, 0x20(r1)
/* 80099C38 00096818  7C 7E 1B 78 */	mr r30, r3
/* 80099C3C 0009681C  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 80099C40 00096820  80 1F 23 40 */	lwz r0, 0x2340(r31)
/* 80099C44 00096824  2C 00 00 00 */	cmpwi r0, 0
/* 80099C48 00096828  41 82 00 6C */	beq lbl_80099CB4
/* 80099C4C 0009682C  80 BF 23 44 */	lwz r5, 0x2344(r31)
/* 80099C50 00096830  7F C3 F3 78 */	mr r3, r30
/* 80099C54 00096834  80 1F 23 48 */	lwz r0, 0x2348(r31)
/* 80099C58 00096838  38 81 00 1C */	addi r4, r1, 0x1c
/* 80099C5C 0009683C  90 A1 00 10 */	stw r5, 0x10(r1)
/* 80099C60 00096840  90 01 00 14 */	stw r0, 0x14(r1)
/* 80099C64 00096844  80 1F 23 4C */	lwz r0, 0x234c(r31)
/* 80099C68 00096848  90 01 00 18 */	stw r0, 0x18(r1)
/* 80099C6C 0009684C  4B FF B6 BD */	bl ft_80095328
/* 80099C70 00096850  2C 03 00 00 */	cmpwi r3, 0
/* 80099C74 00096854  41 82 00 2C */	beq lbl_80099CA0
/* 80099C78 00096858  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 80099C7C 0009685C  2C 00 00 00 */	cmpwi r0, 0
/* 80099C80 00096860  41 82 00 54 */	beq lbl_80099CD4
/* 80099C84 00096864  80 61 00 10 */	lwz r3, 0x10(r1)
/* 80099C88 00096868  80 01 00 14 */	lwz r0, 0x14(r1)
/* 80099C8C 0009686C  90 7F 00 80 */	stw r3, 0x80(r31)
/* 80099C90 00096870  90 1F 00 84 */	stw r0, 0x84(r31)
/* 80099C94 00096874  80 01 00 18 */	lwz r0, 0x18(r1)
/* 80099C98 00096878  90 1F 00 88 */	stw r0, 0x88(r31)
/* 80099C9C 0009687C  48 00 00 38 */	b lbl_80099CD4
lbl_80099CA0:
/* 80099CA0 00096880  7F C3 F3 78 */	mr r3, r30
/* 80099CA4 00096884  48 03 D3 B9 */	bl ftCo_800D705C
/* 80099CA8 00096888  80 7F 23 40 */	lwz r3, 0x2340(r31)
/* 80099CAC 0009688C  38 03 FF FF */	addi r0, r3, -1
/* 80099CB0 00096890  90 1F 23 40 */	stw r0, 0x2340(r31)
lbl_80099CB4:
/* 80099CB4 00096894  7F C3 F3 78 */	mr r3, r30
/* 80099CB8 00096898  48 02 9E 59 */	bl ftCo_800C3B10
/* 80099CBC 0009689C  2C 03 00 00 */	cmpwi r3, 0
/* 80099CC0 000968A0  41 82 00 14 */	beq lbl_80099CD4
/* 80099CC4 000968A4  C0 3F 00 80 */	lfs f1, 0x80(r31)
/* 80099CC8 000968A8  C0 02 8C A8 */	lfs f0, 0.1f
/* 80099CCC 000968AC  EC 01 00 32 */	fmuls f0, f1, f0
/* 80099CD0 000968B0  D0 1F 00 80 */	stfs f0, 0x80(r31)
lbl_80099CD4:
/* 80099CD4 000968B4  80 01 00 2C */	lwz r0, 0x2c(r1)
/* 80099CD8 000968B8  83 E1 00 24 */	lwz r31, 0x24(r1)
/* 80099CDC 000968BC  83 C1 00 20 */	lwz r30, 0x20(r1)
/* 80099CE0 000968C0  38 21 00 28 */	addi r1, r1, 0x28
/* 80099CE4 000968C4  7C 08 03 A6 */	mtlr r0
/* 80099CE8 000968C8  4E 80 00 20 */	blr
}
#pragma peephole on
#endif // clang-format on

void ftCo_EscapeAir_Phys(ftCo_GObj* gobj)
{
    ftCo_Fighter* fp = gobj->user_data;
    if (!fp->cmd_vars[cmd_skip_decay]) {
        fp->self_vel.x *= p_ftCommonData->escapeair_decay;
        fp->self_vel.y *= p_ftCommonData->escapeair_decay;
    } else {
        ft_80084DB0(gobj);
    }
}

void ftCo_EscapeAir_Coll(Fighter_GObj* gobj)
{
    ft_80082C74(gobj, ftCo_80099D70);
}

void ftCo_80099D70(ftCo_GObj* gobj, float lag)
{
    ft_800D5CB0(gobj, 0, p_ftCommonData->x344);
}
