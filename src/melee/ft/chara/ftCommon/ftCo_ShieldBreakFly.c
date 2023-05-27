#include <platform.h>

#include "ftCo_ShieldBreakFly.h"

#include "ef/efasync.h"
#include "ft/ft_081B.h"
#include "ft/ft_0877.h"
#include "ft/ft_08A4.h"
#include "ft/ftcoll.h"
#include "ft/ftcommon.h"
#include "ftCommon/inlines.h"

#include <placeholder.h>

float const ftCo_804D8650 = 0;
float const ftCo_804D8654 = 1;

#if defined(MUST_MATCH) && !defined(WIP)
#pragma push
asm void ft_80098B20(ftCo_GObj*)
{
    // clang-format off
    nofralloc
/* 80098B20 00095700  7C 08 02 A6 */	mflr r0
/* 80098B24 00095704  90 01 00 04 */	stw r0, 4(r1)
/* 80098B28 00095708  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 80098B2C 0009570C  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 80098B30 00095710  93 C1 00 18 */	stw r30, 0x18(r1)
/* 80098B34 00095714  7C 7E 1B 78 */	mr r30, r3
/* 80098B38 00095718  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 80098B3C 0009571C  7F E3 FB 78 */	mr r3, r31
/* 80098B40 00095720  4B FE 4A 95 */	bl ftCommon_8007D5D4
/* 80098B44 00095724  C0 22 8C 70 */	lfs f1, ftCo_804D8650
/* 80098B48 00095728  7F C3 F3 78 */	mr r3, r30
/* 80098B4C 0009572C  C0 42 8C 74 */	lfs f2, ftCo_804D8654
/* 80098B50 00095730  38 80 00 CD */	li r4, 0xcd
/* 80098B54 00095734  FC 60 08 90 */	fmr f3, f1
/* 80098B58 00095738  38 A0 00 40 */	li r5, 0x40
/* 80098B5C 0009573C  38 C0 00 00 */	li r6, 0
/* 80098B60 00095740  4B FD 08 4D */	bl Fighter_ChangeMotionState
/* 80098B64 00095744  7F C3 F3 78 */	mr r3, r30
/* 80098B68 00095748  4B FD 60 3D */	bl ftAnim_8006EBA4
/* 80098B6C 0009574C  C0 02 8C 70 */	lfs f0, ftCo_804D8650
/* 80098B70 00095750  D0 1F 00 80 */	stfs f0, 0x80(r31)
/* 80098B74 00095754  C0 1F 01 A4 */	lfs f0, 0x1a4(r31)
/* 80098B78 00095758  D0 1F 00 84 */	stfs f0, 0x84(r31)
/* 80098B7C 0009575C  80 1F 00 04 */	lwz r0, 4(r31)
/* 80098B80 00095760  2C 00 00 0F */	cmpwi r0, 0xf
/* 80098B84 00095764  40 82 00 14 */	bne lbl_80098B98
/* 80098B88 00095768  88 1F 22 22 */	lbz r0, 0x2222(r31)
/* 80098B8C 0009576C  38 60 00 01 */	li r3, 1
/* 80098B90 00095770  50 60 26 F6 */	rlwimi r0, r3, 4, 0x1b, 0x1b
/* 80098B94 00095774  98 1F 22 22 */	stb r0, 0x2222(r31)
lbl_80098B98:
/* 80098B98 00095778  80 9F 01 0C */	lwz r4, 0x10c(r31)
/* 80098B9C 0009577C  7F C3 F3 78 */	mr r3, r30
/* 80098BA0 00095780  80 FF 05 E8 */	lwz r7, 0x5e8(r31)
/* 80098BA4 00095784  4C C6 31 82 */	crclr 6
/* 80098BA8 00095788  80 A4 00 08 */	lwz r5, 8(r4)
/* 80098BAC 0009578C  80 DE 00 2C */	lwz r6, 0x2c(r30)
/* 80098BB0 00095790  88 05 00 11 */	lbz r0, 0x11(r5)
/* 80098BB4 00095794  38 A0 00 00 */	li r5, 0
/* 80098BB8 00095798  38 86 06 0C */	addi r4, r6, 0x60c
/* 80098BBC 0009579C  54 00 20 36 */	slwi r0, r0, 4
/* 80098BC0 000957A0  7C E7 00 2E */	lwzx r7, r7, r0
/* 80098BC4 000957A4  38 C0 04 1B */	li r6, 0x41b
/* 80098BC8 000957A8  4B FC EB 29 */	bl efAsync_Spawn
/* 80098BCC 000957AC  38 7F 00 00 */	addi r3, r31, 0
/* 80098BD0 000957B0  38 80 00 82 */	li r4, 0x82
/* 80098BD4 000957B4  38 A0 00 7F */	li r5, 0x7f
/* 80098BD8 000957B8  38 C0 00 40 */	li r6, 0x40
/* 80098BDC 000957BC  4B FE F5 6D */	bl ft_80088148
/* 80098BE0 000957C0  38 7F 00 00 */	addi r3, r31, 0
/* 80098BE4 000957C4  38 80 00 18 */	li r4, 0x18
/* 80098BE8 000957C8  38 A0 00 00 */	li r5, 0
/* 80098BEC 000957CC  4B FE 5F C1 */	bl ftCommon_8007EBAC
/* 80098BF0 000957D0  38 7E 00 00 */	addi r3, r30, 0
/* 80098BF4 000957D4  38 80 00 02 */	li r4, 2
/* 80098BF8 000957D8  4B FE 2A 35 */	bl ftColl_8007B62C
/* 80098BFC 000957DC  80 01 00 24 */	lwz r0, 0x24(r1)
/* 80098C00 000957E0  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 80098C04 000957E4  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 80098C08 000957E8  38 21 00 20 */	addi r1, r1, 0x20
/* 80098C0C 000957EC  7C 08 03 A6 */	mtlr r0
/* 80098C10 000957F0  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#else

void ft_80098B20(Fighter_GObj* gobj)
{
    ftCo_Fighter* fp = gobj->user_data;
    ftCommon_8007D5D4(fp);
    Fighter_ChangeMotionState(gobj, 205, 64, NULL, 0, 1, 0);
    ftAnim_8006EBA4(gobj);
    fp->self_vel.x = 0;
    fp->self_vel.y = fp->co_attrs.shield_break_initial_velocity;
    if (fp->kind == FTKIND_PURIN) {
        fp->x2222_b3 = true;
    }
    ftCo_SpawnEf(gobj, fp->parts[fp->ft_data->x8->unk11].joint, 0, 1051);
    ft_80088148(fp, 130, 127, 64);
    ftCommon_8007EBAC(fp, 24, 0U);
    ftColl_8007B62C(gobj, 2);
}
#endif

void ftCo_ShieldBreakFly_Anim(Fighter_GObj* gobj)
{
    if (!ftAnim_IsFramesRemaining(gobj)) {
        ftCo_80098D90(gobj);
    }
}

void ftCo_ShieldBreakFly_IASA(HSD_GObj* gobj) {}

void ftCo_ShieldBreakFly_Phys(Fighter_GObj* gobj)
{
    ft_80084EEC(gobj);
}

void ftCo_ShieldBreakFly_Coll(Fighter_GObj* gobj)
{
    ft_80082C74(gobj, ftCo_80098E3C);
}

#if defined(MUST_MATCH) && !defined(WIP)
#pragma push
asm void ft_80098C9C(ftCo_GObj*)
{ // clang-format off
    nofralloc
/* 80098C9C 0009587C  7C 08 02 A6 */	mflr r0
/* 80098CA0 00095880  90 01 00 04 */	stw r0, 4(r1)
/* 80098CA4 00095884  94 21 FF D8 */	stwu r1, -0x28(r1)
/* 80098CA8 00095888  93 E1 00 24 */	stw r31, 0x24(r1)
/* 80098CAC 0009588C  93 C1 00 20 */	stw r30, 0x20(r1)
/* 80098CB0 00095890  7C 7E 1B 78 */	mr r30, r3
/* 80098CB4 00095894  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 80098CB8 00095898  7F E3 FB 78 */	mr r3, r31
/* 80098CBC 0009589C  4B FE 49 19 */	bl ftCommon_8007D5D4
/* 80098CC0 000958A0  C0 22 8C 70 */	lfs f1, ftCo_804D8650
/* 80098CC4 000958A4  7F C3 F3 78 */	mr r3, r30
/* 80098CC8 000958A8  C0 42 8C 74 */	lfs f2, ftCo_804D8654
/* 80098CCC 000958AC  38 80 00 CD */	li r4, 0xcd
/* 80098CD0 000958B0  FC 60 08 90 */	fmr f3, f1
/* 80098CD4 000958B4  38 A0 00 40 */	li r5, 0x40
/* 80098CD8 000958B8  38 C0 00 00 */	li r6, 0
/* 80098CDC 000958BC  4B FD 06 D1 */	bl Fighter_ChangeMotionState
/* 80098CE0 000958C0  7F C3 F3 78 */	mr r3, r30
/* 80098CE4 000958C4  4B FD 5E C1 */	bl ftAnim_8006EBA4
/* 80098CE8 000958C8  C0 02 8C 70 */	lfs f0, ftCo_804D8650
/* 80098CEC 000958CC  D0 1F 00 80 */	stfs f0, 0x80(r31)
/* 80098CF0 000958D0  C0 1F 01 A4 */	lfs f0, 0x1a4(r31)
/* 80098CF4 000958D4  D0 1F 00 84 */	stfs f0, 0x84(r31)
/* 80098CF8 000958D8  80 1F 00 04 */	lwz r0, 4(r31)
/* 80098CFC 000958DC  2C 00 00 0F */	cmpwi r0, 0xf
/* 80098D00 000958E0  40 82 00 14 */	bne lbl_80098D14
/* 80098D04 000958E4  88 1F 22 22 */	lbz r0, 0x2222(r31)
/* 80098D08 000958E8  38 60 00 01 */	li r3, 1
/* 80098D0C 000958EC  50 60 26 F6 */	rlwimi r0, r3, 4, 0x1b, 0x1b
/* 80098D10 000958F0  98 1F 22 22 */	stb r0, 0x2222(r31)
lbl_80098D14:
/* 80098D14 000958F4  80 9F 01 0C */	lwz r4, 0x10c(r31)
/* 80098D18 000958F8  7F C3 F3 78 */	mr r3, r30
/* 80098D1C 000958FC  80 FF 05 E8 */	lwz r7, 0x5e8(r31)
/* 80098D20 00095900  4C C6 31 82 */	crclr 6
/* 80098D24 00095904  80 A4 00 08 */	lwz r5, 8(r4)
/* 80098D28 00095908  80 DE 00 2C */	lwz r6, 0x2c(r30)
/* 80098D2C 0009590C  88 05 00 11 */	lbz r0, 0x11(r5)
/* 80098D30 00095910  38 A0 00 00 */	li r5, 0
/* 80098D34 00095914  38 86 06 0C */	addi r4, r6, 0x60c
/* 80098D38 00095918  54 00 20 36 */	slwi r0, r0, 4
/* 80098D3C 0009591C  7C E7 00 2E */	lwzx r7, r7, r0
/* 80098D40 00095920  38 C0 04 1B */	li r6, 0x41b
/* 80098D44 00095924  4B FC E9 AD */	bl efAsync_Spawn
/* 80098D48 00095928  38 7F 00 00 */	addi r3, r31, 0
/* 80098D4C 0009592C  38 80 00 82 */	li r4, 0x82
/* 80098D50 00095930  38 A0 00 7F */	li r5, 0x7f
/* 80098D54 00095934  38 C0 00 40 */	li r6, 0x40
/* 80098D58 00095938  4B FE F3 F1 */	bl ft_80088148
/* 80098D5C 0009593C  38 7F 00 00 */	addi r3, r31, 0
/* 80098D60 00095940  38 80 00 18 */	li r4, 0x18
/* 80098D64 00095944  38 A0 00 00 */	li r5, 0
/* 80098D68 00095948  4B FE 5E 45 */	bl ftCommon_8007EBAC
/* 80098D6C 0009594C  38 7E 00 00 */	addi r3, r30, 0
/* 80098D70 00095950  38 80 00 02 */	li r4, 2
/* 80098D74 00095954  4B FE 28 B9 */	bl ftColl_8007B62C
/* 80098D78 00095958  80 01 00 2C */	lwz r0, 0x2c(r1)
/* 80098D7C 0009595C  83 E1 00 24 */	lwz r31, 0x24(r1)
/* 80098D80 00095960  83 C1 00 20 */	lwz r30, 0x20(r1)
/* 80098D84 00095964  38 21 00 28 */	addi r1, r1, 0x28
/* 80098D88 00095968  7C 08 03 A6 */	mtlr r0
/* 80098D8C 0009596C  4E 80 00 20 */	blr
} // clang-format on
#pragma pop
#else

void ft_80098C9C(Fighter_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8] = { 0 };
#endif
    ft_80098B20(gobj);
}
#endif
