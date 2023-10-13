#include <platform.h>
#include "ft/forward.h"
#include "ftCommon/forward.h"

#include "ftCo_DamageIce.h"

#include "ftCo_09CB.h"
#include "ftCo_DamageFall.h"
#include "ftCo_DownAttack.h"
#include "ftCo_DownBound.h"
#include "ftCo_FallSpecial.h"
#include "ftCo_PassiveStand.h"

#include "baselib/mtx.h"
#include "cm/camera.h"
#include "ef/efasync.h"
#include "ft/fighter.h"
#include "ft/ft_081B.h"
#include "ft/ft_0877.h"
#include "ft/ft_08A4.h"
#include "ft/ftcoll.h"
#include "ft/ftcommon.h"
#include "ft/ftparts.h"
#include "ft/types.h"
#include "ftKirby/ftKb_Init.h"
#include "lb/lb_00B0.h"
#include "lb/lbvector.h"

#include <common_structs.h>
#include <placeholder.h>
#include <baselib/debug.h>

static Vec3 const ftCo_803B74B0 = { 0 };
static Vec3 const ftCo_803B74BC = { 0 };

#ifdef MWERKS_GEKKO
/* static */ extern char* ftCo_804D3AE8; // = "jobj.h";
/* static */ extern char* ftCo_804D3AF0; // = "jobj";
#endif

void ftCo_80090984(ftCo_GObj* gobj)
{
    RETURN_IF(ftCo_80098928(gobj))
    RETURN_IF(ftCo_8009872C(gobj))
    ftCo_80097D40(gobj);
}

void ftCo_800909D0(Fighter* fp)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8] = { 0 };
#endif
    Vec3 offset;
    Vec3 pos;
    {
        /// @todo Unused stack.
#ifdef MUST_MATCH
        u8 _[4] = { 0 };
#endif
        float radius = fp->x34_scale.y * fp->co_attrs.bubble_ratio;
        lb_8000B1CC(fp->parts[FtPart_TopN].joint, NULL, &pos);
        lb_8000B1CC(fp->parts[ftParts_8007500C(fp, FtPart_XRotN)].joint, NULL,
                    &offset);
        lbVector_Sub(&offset, &pos);
        fp->mv.co.damageice.x8.top = radius + offset.y;
        fp->mv.co.damageice.x8.bottom = -radius + offset.y;
        fp->mv.co.damageice.x8.right.x = radius + offset.x;
        fp->mv.co.damageice.x8.right.y = 0;
        fp->mv.co.damageice.x8.left.x = -radius + offset.x;
        fp->mv.co.damageice.x8.left.y = 0;
        ftCommon_8007D5BC(fp);
        if (fp->ground_or_air == GA_Air) {
            ft_80082638(fp->gobj, &fp->mv.co.damageice.x8);
        } else {
            ft_80082888(fp->gobj, &fp->mv.co.damageice.x8);
        }
    }
}

static inline void inlineA0(ftCo_GObj* gobj, HSD_JObj* joint, float* param)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8] = { 0 };
#endif
    ftCo_Fighter* fp = gobj->user_data;
    efAsync_Spawn(gobj, &fp->x60C, 3, 1045, joint, param);
}

void ftCo_80090AC0(Fighter* fp)
{
    float param;
    HSD_JObj* joint = fp->parts[ftParts_8007500C(fp, FtPart_XRotN)].joint;
    float scl_y = fp->x34_scale.y * fp->co_attrs.bubble_ratio;
    param = scl_y / p_ftCommonData->x7A0;
    inlineA0(fp->gobj, joint, &param);
    fp->x2219_b0 = true;
}

void ftCo_80090B48(ftCo_GObj* gobj)
{
    ftCo_Fighter* fp = gobj->user_data;
    fp->x2227_flag.bits.b6 = false;
}

ASM void ftCo_80090B60(ftCo_GObj* gobj)
#if !defined(MUST_MATCH) || defined(WIP)
{
    NOT_IMPLEMENTED;
}
#else /* clang-format off */
{ nofralloc
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
/* 80090B88 0008D768  48 00 69 85 */	bl ftCo_8009750C
/* 80090B8C 0008D76C  7F 83 E3 78 */	mr r3, r28
/* 80090B90 0008D770  48 04 C5 D9 */	bl ftCo_800DD168
/* 80090B94 0008D774  88 1D 22 27 */	lbz r0, 0x2227(r29)
/* 80090B98 0008D778  38 60 00 01 */	li r3, 1
/* 80090B9C 0008D77C  50 60 0F BC */	rlwimi r0, r3, 1, 0x1e, 0x1e
/* 80090BA0 0008D780  98 1D 22 27 */	stb r0, 0x2227(r29)
/* 80090BA4 0008D784  38 7C 00 00 */	addi r3, r28, 0
/* 80090BA8 0008D788  38 80 01 45 */	li r4, 0x145
/* 80090BAC 0008D78C  C0 22 8B 38 */	lfs f1, 0.0f
/* 80090BB0 0008D790  38 A0 00 40 */	li r5, 0x40
/* 80090BB4 0008D794  C0 42 8B 3C */	lfs f2, 1.0f
/* 80090BB8 0008D798  38 C0 00 00 */	li r6, 0
/* 80090BBC 0008D79C  FC 60 08 90 */	fmr f3, f1
/* 80090BC0 0008D7A0  4B FD 87 ED */	bl Fighter_ChangeMotionState
/* 80090BC4 0008D7A4  80 AD AE B4 */	lwz r5, p_ftCommonData
/* 80090BC8 0008D7A8  7F A3 EB 78 */	mr r3, r29
/* 80090BCC 0008D7AC  C0 3D 18 38 */	lfs f1, 0x1838(r29)
/* 80090BD0 0008D7B0  38 80 00 00 */	li r4, 0
/* 80090BD4 0008D7B4  C0 05 07 90 */	lfs f0, 0x790(r5)
/* 80090BD8 0008D7B8  EC 21 00 32 */	fmuls f1, f1, f0
/* 80090BDC 0008D7BC  4B FE CF F1 */	bl ftCommon_8007DBCC
/* 80090BE0 0008D7C0  38 7D 00 00 */	addi r3, r29, 0
/* 80090BE4 0008D7C4  38 80 00 02 */	li r4, 2
/* 80090BE8 0008D7C8  4B FE 44 25 */	bl ftParts_8007500C
/* 80090BEC 0008D7CC  80 9D 05 E8 */	lwz r4, 0x5e8(r29)
/* 80090BF0 0008D7D0  54 60 20 36 */	slwi r0, r3, 4
/* 80090BF4 0008D7D4  38 7D 00 00 */	addi r3, r29, 0
/* 80090BF8 0008D7D8  7F 84 00 2E */	lwzx r28, r4, r0
/* 80090BFC 0008D7DC  38 80 00 03 */	li r4, 3
/* 80090C00 0008D7E0  4B FE 44 0D */	bl ftParts_8007500C
/* 80090C04 0008D7E4  80 9D 05 E8 */	lwz r4, 0x5e8(r29)
/* 80090C08 0008D7E8  54 60 20 36 */	slwi r0, r3, 4
/* 80090C0C 0008D7EC  C0 02 8B 38 */	lfs f0, 0.0f
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
/* 80090C44 0008D824  38 6D 84 48 */	addi r3, r13, ftCo_804D3AE8
/* 80090C48 0008D828  38 80 02 BB */	li r4, 0x2bb
/* 80090C4C 0008D82C  38 AD 84 50 */	addi r5, r13, ftCo_804D3AF0
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
/* 80090C98 0008D878  48 2E 95 99 */	bl HSD_Mtx_8037A230
lbl_80090C9C:
/* 80090C9C 0008D87C  38 61 00 AC */	addi r3, r1, 0xac
/* 80090CA0 0008D880  38 81 01 1C */	addi r4, r1, 0x11c
/* 80090CA4 0008D884  48 2B 16 2D */	bl PSMTXTranspose
/* 80090CA8 0008D888  28 1C 00 00 */	cmplwi r28, 0
/* 80090CAC 0008D88C  40 82 00 14 */	bne lbl_80090CC0
/* 80090CB0 0008D890  38 6D 84 48 */	addi r3, r13, ftCo_804D3AE8
/* 80090CB4 0008D894  38 80 02 BB */	li r4, 0x2bb
/* 80090CB8 0008D898  38 AD 84 50 */	addi r5, r13, ftCo_804D3AF0
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
/* 80090D04 0008D8E4  48 2E 95 2D */	bl HSD_Mtx_8037A230
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
/* 80090D4C 0008D92C  38 6D 84 48 */	addi r3, r13, ftCo_804D3AE8
/* 80090D50 0008D930  38 80 04 5A */	li r4, 0x45a
/* 80090D54 0008D934  38 AD 84 50 */	addi r5, r13, ftCo_804D3AF0
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
/* 80090D80 0008D960  38 6D 84 48 */	addi r3, r13, ftCo_804D3AE8
/* 80090D84 0008D964  38 80 02 34 */	li r4, 0x234
/* 80090D88 0008D968  38 AD 84 50 */	addi r5, r13, ftCo_804D3AF0
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
/* 80090DC8 0008D9A8  38 6D 84 48 */	addi r3, r13, ftCo_804D3AE8
/* 80090DCC 0008D9AC  38 80 04 66 */	li r4, 0x466
/* 80090DD0 0008D9B0  38 AD 84 50 */	addi r5, r13, ftCo_804D3AF0
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
/* 80090DFC 0008D9DC  38 6D 84 48 */	addi r3, r13, ftCo_804D3AE8
/* 80090E00 0008D9E0  38 80 02 34 */	li r4, 0x234
/* 80090E04 0008D9E4  38 AD 84 50 */	addi r5, r13, ftCo_804D3AF0
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
/* 80090E40 0008DA20  48 00 D3 01 */	bl ftCo_8009E140
/* 80090E44 0008DA24  80 7D 00 00 */	lwz r3, 0(r29)
/* 80090E48 0008DA28  4B FE E9 DD */	bl ftCommon_8007F824
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
/* 80090E80 0008DA60  C0 02 8B 38 */	lfs f0, 0.0f
/* 80090E84 0008DA64  D0 1D 00 94 */	stfs f0, 0x94(r29)
/* 80090E88 0008DA68  D0 1D 00 90 */	stfs f0, 0x90(r29)
/* 80090E8C 0008DA6C  D0 1D 00 8C */	stfs f0, 0x8c(r29)
/* 80090E90 0008DA70  48 00 00 14 */	b lbl_80090EA4
lbl_80090E94:
/* 80090E94 0008DA74  C0 1D 00 F0 */	lfs f0, 0xf0(r29)
/* 80090E98 0008DA78  D0 1D 00 EC */	stfs f0, 0xec(r29)
/* 80090E9C 0008DA7C  C0 02 8B 38 */	lfs f0, 0.0f
/* 80090EA0 0008DA80  D0 1D 00 F0 */	stfs f0, 0xf0(r29)
lbl_80090EA4:
/* 80090EA4 0008DA84  38 7D 00 00 */	addi r3, r29, 0
/* 80090EA8 0008DA88  38 80 01 FF */	li r4, 0x1ff
/* 80090EAC 0008DA8C  4B FE D4 49 */	bl ftCommon_8007E2F4
/* 80090EB0 0008DA90  3B E0 00 00 */	li r31, 0
/* 80090EB4 0008DA94  9B FD 23 40 */	stb r31, 0x2340(r29)
/* 80090EB8 0008DA98  48 2E F6 71 */	bl HSD_Randf
/* 80090EBC 0008DA9C  80 8D AE B4 */	lwz r4, p_ftCommonData
/* 80090EC0 0008DAA0  7F A3 EB 78 */	mr r3, r29
/* 80090EC4 0008DAA4  C0 44 07 88 */	lfs f2, 0x788(r4)
/* 80090EC8 0008DAA8  C0 04 07 8C */	lfs f0, 0x78c(r4)
/* 80090ECC 0008DAAC  EC 00 10 28 */	fsubs f0, f0, f2
/* 80090ED0 0008DAB0  EC 00 10 7A */	fmadds f0, f0, f1, f2
/* 80090ED4 0008DAB4  D0 1D 23 44 */	stfs f0, 0x2344(r29)
/* 80090ED8 0008DAB8  4B FF FA F9 */	bl ftCo_800909D0
/* 80090EDC 0008DABC  38 7D 00 00 */	addi r3, r29, 0
/* 80090EE0 0008DAC0  38 80 00 02 */	li r4, 2
/* 80090EE4 0008DAC4  4B FE 41 29 */	bl ftParts_8007500C
/* 80090EE8 0008DAC8  C0 3D 00 38 */	lfs f1, 0x38(r29)
/* 80090EEC 0008DACC  54 60 20 36 */	slwi r0, r3, 4
/* 80090EF0 0008DAD0  C0 1D 02 5C */	lfs f0, 0x25c(r29)
/* 80090EF4 0008DAD4  3B DD 02 5C */	addi r30, r29, 0x25c
/* 80090EF8 0008DAD8  80 8D AE B4 */	lwz r4, p_ftCommonData
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
/* 80090F4C 0008DB2C  4B FE A1 75 */	bl ftColl_8007B0C0
/* 80090F50 0008DB30  3C 60 80 3B */	lis r3, ftCo_803B74B0@ha
/* 80090F54 0008DB34  38 C3 74 B0 */	addi r6, r3, ftCo_803B74B0@l
/* 80090F58 0008DB38  80 A6 00 00 */	lwz r5, 0(r6)
/* 80090F5C 0008DB3C  7F A3 EB 78 */	mr r3, r29
/* 80090F60 0008DB40  80 06 00 04 */	lwz r0, 4(r6)
/* 80090F64 0008DB44  38 80 00 02 */	li r4, 2
/* 80090F68 0008DB48  90 A1 00 28 */	stw r5, 0x28(r1)
/* 80090F6C 0008DB4C  90 01 00 2C */	stw r0, 0x2c(r1)
/* 80090F70 0008DB50  80 06 00 08 */	lwz r0, 8(r6)
/* 80090F74 0008DB54  90 01 00 30 */	stw r0, 0x30(r1)
/* 80090F78 0008DB58  4B FE 40 95 */	bl ftParts_8007500C
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
/* 80090FCC 0008DBAC  4B FE A5 E1 */	bl ftColl_8007B5AC
/* 80090FD0 0008DBB0  38 7D 00 00 */	addi r3, r29, 0
/* 80090FD4 0008DBB4  38 80 00 01 */	li r4, 1
/* 80090FD8 0008DBB8  38 A0 00 00 */	li r5, 0
/* 80090FDC 0008DBBC  4B FE DB D1 */	bl ftCommon_8007EBAC
/* 80090FE0 0008DBC0  3C 60 80 09 */	lis r3, ftCo_80091274@ha
/* 80090FE4 0008DBC4  38 03 12 74 */	addi r0, r3, ftCo_80091274@l
/* 80090FE8 0008DBC8  3C 60 80 09 */	lis r3, ftCo_80090B48@ha
/* 80090FEC 0008DBCC  90 1D 21 F0 */	stw r0, 0x21f0(r29)
/* 80090FF0 0008DBD0  38 03 0B 48 */	addi r0, r3, ftCo_80090B48@l
/* 80090FF4 0008DBD4  90 1D 21 DC */	stw r0, 0x21dc(r29)
/* 80090FF8 0008DBD8  38 7D 00 00 */	addi r3, r29, 0
/* 80090FFC 0008DBDC  38 80 01 22 */	li r4, 0x122
/* 80091000 0008DBE0  38 A0 00 7F */	li r5, 0x7f
/* 80091004 0008DBE4  38 C0 00 40 */	li r6, 0x40
/* 80091008 0008DBE8  4B FF 76 D1 */	bl ftCo_800886D8
/* 8009100C 0008DBEC  80 01 01 D4 */	lwz r0, 0x1d4(r1)
/* 80091010 0008DBF0  CB E1 01 C8 */	lfd f31, 0x1c8(r1)
/* 80091014 0008DBF4  83 E1 01 C4 */	lwz r31, 0x1c4(r1)
/* 80091018 0008DBF8  83 C1 01 C0 */	lwz r30, 0x1c0(r1)
/* 8009101C 0008DBFC  83 A1 01 BC */	lwz r29, 0x1bc(r1)
/* 80091020 0008DC00  83 81 01 B8 */	lwz r28, 0x1b8(r1)
/* 80091024 0008DC04  38 21 01 D0 */	addi r1, r1, 0x1d0
/* 80091028 0008DC08  7C 08 03 A6 */	mtlr r0
/* 8009102C 0008DC0C  4E 80 00 20 */	blr
}
#pragma peephole on
#endif /* clang-format on */

#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-but-set-variable"
#endif

ASM void ftCo_80091030(Fighter_GObj* gobj)
#if !defined(MUST_MATCH) || defined(WIP)
{
    float param;
    struct UNK_SAMUS_S2 sp2C;
    Vec3 sp20;
    HSD_JObj* temp_r7;
    float temp_f1;
    float temp_f2;
    Fighter* fp = gobj->user_data;
    ftCommon_8007DB58(gobj);
    ftCo_8009750C(gobj);
    ftCo_800DD168(gobj);
    fp->x2227_flag.bits.b6 = true;
    Fighter_ChangeMotionState(gobj, ftCo_MS_DamageIce,
                              Ft_MF_KeepGfx | Ft_MF_Unk06, 0, 1, 0, NULL);
    ftCo_8009E140(fp, 0);
    ftCommon_8007F824(fp->gobj);
    fp->x2222_b3 = true;
    if (fp->ground_or_air == GA_Air) {
        fp->self_vel = fp->x8c_kb_vel;
        fp->x8c_kb_vel.x = fp->x8c_kb_vel.y = fp->x8c_kb_vel.z = 0;
    } else {
        fp->gr_vel = fp->xF0_ground_kb_vel;
        fp->xF0_ground_kb_vel = 0;
    }
    ftCommon_8007E2F4(fp, 0x1FF);
    fp->mv.co.damageice.x0 = 0;
    temp_f2 = p_ftCommonData->x788;
    fp->mv.ca.specialhi.vel.x =
        (p_ftCommonData->x78C - temp_f2) * HSD_Randf() + temp_f2;
    ftCo_800909D0(fp);
    temp_f1 = fp->x34_scale.y * fp->co_attrs.bubble_ratio;
    temp_r7 = fp->parts[ftParts_8007500C(fp, FtPart_XRotN)].joint;
    {
        param = temp_f1 / p_ftCommonData->x7A0;
        {
            HSD_GObj* temp_r3 = fp->gobj;
            efAsync_Spawn(temp_r3, &GET_FIGHTER(temp_r3)->x60C, 3, 1045,
                          temp_r7, &param);
            fp->x2219_b7 = true;
            ftColl_8007B0C0(fp->gobj, Intangible);
            {
                float temp_r0;
                sp20.x = ftCo_803B74B0.x;
                sp20.y = ftCo_803B74B0.y;
                temp_r0 = ftCo_803B74B0.z;
                sp20.z = temp_r0;
                sp2C.parts[0] = ftParts_8007500C(fp, FtPart_XRotN);
                sp2C.parts[1] = FtPart_TransN;
                sp2C.parts[2] = FtPart_TopN;
                sp2C.vec2.x = sp20.x;
                sp2C.vec2.y = sp20.y;
                sp2C.vec2.z = temp_r0;
                sp2C.vec1.x = sp2C.vec2.x;
                sp2C.vec1.y = sp2C.vec2.y;
                sp2C.vec1.z = temp_r0;
                sp2C.single_float = fp->co_attrs.bubble_ratio;
                ftColl_8007B5AC(fp, fp->x11A0_fighterHurtbox, &sp2C);
                ftCommon_8007EBAC(fp, 1, 0);
                fp->x21F0 = ftCo_80091274;
                fp->take_dmg_cb = ftCo_80090B48;
            }
        }
    }
}
#else /* clang-format off */
{ nofralloc
/* 80091030 0008DC10  7C 08 02 A6 */	mflr r0
/* 80091034 0008DC14  90 01 00 04 */	stw r0, 4(r1)
/* 80091038 0008DC18  94 21 FF 90 */	stwu r1, -0x70(r1)
/* 8009103C 0008DC1C  93 E1 00 6C */	stw r31, 0x6c(r1)
/* 80091040 0008DC20  93 C1 00 68 */	stw r30, 0x68(r1)
/* 80091044 0008DC24  7C 7E 1B 78 */	mr r30, r3
/* 80091048 0008DC28  93 A1 00 64 */	stw r29, 0x64(r1)
/* 8009104C 0008DC2C  93 81 00 60 */	stw r28, 0x60(r1)
/* 80091050 0008DC30  83 A3 00 2C */	lwz r29, 0x2c(r3)
/* 80091054 0008DC34  4B FE CB 05 */	bl ftCommon_8007DB58
/* 80091058 0008DC38  7F C3 F3 78 */	mr r3, r30
/* 8009105C 0008DC3C  48 00 64 B1 */	bl ftCo_8009750C
/* 80091060 0008DC40  7F C3 F3 78 */	mr r3, r30
/* 80091064 0008DC44  48 04 C1 05 */	bl ftCo_800DD168
/* 80091068 0008DC48  88 1D 22 27 */	lbz r0, 0x2227(r29)
/* 8009106C 0008DC4C  3B 80 00 01 */	li r28, 1
/* 80091070 0008DC50  53 80 0F BC */	rlwimi r0, r28, 1, 0x1e, 0x1e
/* 80091074 0008DC54  98 1D 22 27 */	stb r0, 0x2227(r29)
/* 80091078 0008DC58  38 7E 00 00 */	addi r3, r30, 0
/* 8009107C 0008DC5C  38 80 01 45 */	li r4, 0x145
/* 80091080 0008DC60  C0 22 8B 38 */	lfs f1, 0.0f
/* 80091084 0008DC64  38 A0 00 42 */	li r5, 0x42
/* 80091088 0008DC68  C0 42 8B 3C */	lfs f2, 1.0f
/* 8009108C 0008DC6C  38 C0 00 00 */	li r6, 0
/* 80091090 0008DC70  FC 60 08 90 */	fmr f3, f1
/* 80091094 0008DC74  4B FD 83 19 */	bl Fighter_ChangeMotionState
/* 80091098 0008DC78  38 7D 00 00 */	addi r3, r29, 0
/* 8009109C 0008DC7C  38 80 00 00 */	li r4, 0
/* 800910A0 0008DC80  48 00 D0 A1 */	bl ftCo_8009E140
/* 800910A4 0008DC84  80 7D 00 00 */	lwz r3, 0(r29)
/* 800910A8 0008DC88  4B FE E7 7D */	bl ftCommon_8007F824
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
/* 800910DC 0008DCBC  C0 02 8B 38 */	lfs f0, 0.0f
/* 800910E0 0008DCC0  D0 1D 00 94 */	stfs f0, 0x94(r29)
/* 800910E4 0008DCC4  D0 1D 00 90 */	stfs f0, 0x90(r29)
/* 800910E8 0008DCC8  D0 1D 00 8C */	stfs f0, 0x8c(r29)
/* 800910EC 0008DCCC  48 00 00 14 */	b lbl_80091100
lbl_800910F0:
/* 800910F0 0008DCD0  C0 1D 00 F0 */	lfs f0, 0xf0(r29)
/* 800910F4 0008DCD4  D0 1D 00 EC */	stfs f0, 0xec(r29)
/* 800910F8 0008DCD8  C0 02 8B 38 */	lfs f0, 0.0f
/* 800910FC 0008DCDC  D0 1D 00 F0 */	stfs f0, 0xf0(r29)
lbl_80091100:
/* 80091100 0008DCE0  38 7D 00 00 */	addi r3, r29, 0
/* 80091104 0008DCE4  38 80 01 FF */	li r4, 0x1ff
/* 80091108 0008DCE8  4B FE D1 ED */	bl ftCommon_8007E2F4
/* 8009110C 0008DCEC  3B E0 00 00 */	li r31, 0
/* 80091110 0008DCF0  9B FD 23 40 */	stb r31, 0x2340(r29)
/* 80091114 0008DCF4  48 2E F4 15 */	bl HSD_Randf
/* 80091118 0008DCF8  80 8D AE B4 */	lwz r4, p_ftCommonData
/* 8009111C 0008DCFC  7F A3 EB 78 */	mr r3, r29
/* 80091120 0008DD00  C0 44 07 88 */	lfs f2, 0x788(r4)
/* 80091124 0008DD04  C0 04 07 8C */	lfs f0, 0x78c(r4)
/* 80091128 0008DD08  EC 00 10 28 */	fsubs f0, f0, f2
/* 8009112C 0008DD0C  EC 00 10 7A */	fmadds f0, f0, f1, f2
/* 80091130 0008DD10  D0 1D 23 44 */	stfs f0, 0x2344(r29)
/* 80091134 0008DD14  4B FF F8 9D */	bl ftCo_800909D0
/* 80091138 0008DD18  38 7D 00 00 */	addi r3, r29, 0
/* 8009113C 0008DD1C  38 80 00 02 */	li r4, 2
/* 80091140 0008DD20  4B FE 3E CD */	bl ftParts_8007500C
/* 80091144 0008DD24  C0 3D 00 38 */	lfs f1, 0x38(r29)
/* 80091148 0008DD28  54 60 20 36 */	slwi r0, r3, 4
/* 8009114C 0008DD2C  C0 1D 02 5C */	lfs f0, 0x25c(r29)
/* 80091150 0008DD30  3B DD 02 5C */	addi r30, r29, 0x25c
/* 80091154 0008DD34  80 8D AE B4 */	lwz r4, p_ftCommonData
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
/* 800911A8 0008DD88  4B FE 9F 19 */	bl ftColl_8007B0C0
/* 800911AC 0008DD8C  3C 60 80 3B */	lis r3, ftCo_803B74B0@ha
/* 800911B0 0008DD90  38 C3 74 B0 */	addi r6, r3, ftCo_803B74B0@l
/* 800911B4 0008DD94  80 A6 00 00 */	lwz r5, 0(r6)
/* 800911B8 0008DD98  7F A3 EB 78 */	mr r3, r29
/* 800911BC 0008DD9C  80 06 00 04 */	lwz r0, 4(r6)
/* 800911C0 0008DDA0  38 80 00 02 */	li r4, 2
/* 800911C4 0008DDA4  90 A1 00 20 */	stw r5, 0x20(r1)
/* 800911C8 0008DDA8  90 01 00 24 */	stw r0, 0x24(r1)
/* 800911CC 0008DDAC  80 06 00 08 */	lwz r0, 8(r6)
/* 800911D0 0008DDB0  90 01 00 28 */	stw r0, 0x28(r1)
/* 800911D4 0008DDB4  4B FE 3E 39 */	bl ftParts_8007500C
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
/* 80091228 0008DE08  4B FE A3 85 */	bl ftColl_8007B5AC
/* 8009122C 0008DE0C  38 7D 00 00 */	addi r3, r29, 0
/* 80091230 0008DE10  38 80 00 01 */	li r4, 1
/* 80091234 0008DE14  38 A0 00 00 */	li r5, 0
/* 80091238 0008DE18  4B FE D9 75 */	bl ftCommon_8007EBAC
/* 8009123C 0008DE1C  3C 60 80 09 */	lis r3, ftCo_80091274@ha
/* 80091240 0008DE20  38 03 12 74 */	addi r0, r3, ftCo_80091274@l
/* 80091244 0008DE24  3C 60 80 09 */	lis r3, ftCo_80090B48@ha
/* 80091248 0008DE28  90 1D 21 F0 */	stw r0, 0x21f0(r29)
/* 8009124C 0008DE2C  38 03 0B 48 */	addi r0, r3, ftCo_80090B48@l
/* 80091250 0008DE30  90 1D 21 DC */	stw r0, 0x21dc(r29)
/* 80091254 0008DE34  80 01 00 74 */	lwz r0, 0x74(r1)
/* 80091258 0008DE38  83 E1 00 6C */	lwz r31, 0x6c(r1)
/* 8009125C 0008DE3C  83 C1 00 68 */	lwz r30, 0x68(r1)
/* 80091260 0008DE40  83 A1 00 64 */	lwz r29, 0x64(r1)
/* 80091264 0008DE44  83 81 00 60 */	lwz r28, 0x60(r1)
/* 80091268 0008DE48  38 21 00 70 */	addi r1, r1, 0x70
/* 8009126C 0008DE4C  7C 08 03 A6 */	mtlr r0
/* 80091270 0008DE50  4E 80 00 20 */	blr
} /* clang-format on */
#endif

#if defined(__clang__)
#pragma clang diagnostic pop
#endif

ASM void ftCo_80091274(ftCo_GObj* gobj)
#if !defined(MUST_MATCH) || defined(WIP)
{
    ftCo_Fighter* fp = gobj->user_data;
    fp->x1A4C =
        -(fp->dmg.x1838_percentTemp * p_ftCommonData->x79C - fp->x1A4C);
    if (fp->dmg.x1860 == 1) {
        fp->x1A4C = 0;
    }
}
#else /* clang-format off */
{ nofralloc
/* 80091274 0008DE54  80 83 00 2C */	lwz r4, 0x2c(r3)
/* 80091278 0008DE58  80 6D AE B4 */	lwz r3, p_ftCommonData
/* 8009127C 0008DE5C  C0 44 18 38 */	lfs f2, 0x1838(r4)
/* 80091280 0008DE60  C0 23 07 9C */	lfs f1, 0x79c(r3)
/* 80091284 0008DE64  C0 04 1A 4C */	lfs f0, 0x1a4c(r4)
/* 80091288 0008DE68  EC 02 00 7C */	fnmsubs f0, f2, f1, f0
/* 8009128C 0008DE6C  D0 04 1A 4C */	stfs f0, 0x1a4c(r4)
/* 80091290 0008DE70  80 04 18 60 */	lwz r0, 0x1860(r4)
/* 80091294 0008DE74  28 00 00 01 */	cmplwi r0, 1
/* 80091298 0008DE78  4C 82 00 20 */	bnelr
/* 8009129C 0008DE7C  C0 02 8B 38 */	lfs f0, 0.0f
/* 800912A0 0008DE80  D0 04 1A 4C */	stfs f0, 0x1a4c(r4)
/* 800912A4 0008DE84  4E 80 00 20 */	blr
}
#pragma peephole on
#endif /* clang-format on */

ASM void ftCo_DamageIce_Anim(ftCo_GObj* gobj)
#if !defined(MUST_MATCH) || defined(WIP)
{
    HSD_JObj* jobj;
    ftCo_Fighter* fp = gobj->user_data;
    if (fp->ground_or_air == GA_Air) {
        float rot_x = fp->mv.co.damageice.x4;
        jobj = fp->parts[ftParts_8007500C(fp, FtPart_XRotN)].joint;
        HSD_ASSERT2("jobj.h", 1029, "jobj", jobj);
        jobj->rotate.x += rot_x;
        if (!(jobj->flags & JOBJ_MTX_INDEP_SRT)) {
            HSD_JObjSetMtxDirty(jobj);
        }
    }
    if (!fp->x2224_b2) {
        fp->x1A4C -= p_ftCommonData->x794;
    }
    ftCommon_8007DC08(fp, p_ftCommonData->x798);
    if (fp->x1A4C <= 0) {
        ftCo_80091854(gobj);
    }
}
#else /* clang-format off */
{ nofralloc
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
/* 800912E8 0008DEC8  4B FE 3D 25 */	bl ftParts_8007500C
/* 800912EC 0008DECC  80 9E 05 E8 */	lwz r4, 0x5e8(r30)
/* 800912F0 0008DED0  54 60 20 36 */	slwi r0, r3, 4
/* 800912F4 0008DED4  7F E4 00 2E */	lwzx r31, r4, r0
/* 800912F8 0008DED8  28 1F 00 00 */	cmplwi r31, 0
/* 800912FC 0008DEDC  40 82 00 14 */	bne lbl_80091310
/* 80091300 0008DEE0  38 6D 84 48 */	addi r3, r13, ftCo_804D3AE8
/* 80091304 0008DEE4  38 80 04 05 */	li r4, 0x405
/* 80091308 0008DEE8  38 AD 84 50 */	addi r5, r13, ftCo_804D3AF0
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
/* 80091334 0008DF14  38 6D 84 48 */	addi r3, r13, ftCo_804D3AE8
/* 80091338 0008DF18  38 80 02 34 */	li r4, 0x234
/* 8009133C 0008DF1C  38 AD 84 50 */	addi r5, r13, ftCo_804D3AF0
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
/* 8009137C 0008DF5C  80 6D AE B4 */	lwz r3, p_ftCommonData
/* 80091380 0008DF60  C0 3E 1A 4C */	lfs f1, 0x1a4c(r30)
/* 80091384 0008DF64  C0 03 07 94 */	lfs f0, 0x794(r3)
/* 80091388 0008DF68  EC 01 00 28 */	fsubs f0, f1, f0
/* 8009138C 0008DF6C  D0 1E 1A 4C */	stfs f0, 0x1a4c(r30)
lbl_80091390:
/* 80091390 0008DF70  80 8D AE B4 */	lwz r4, p_ftCommonData
/* 80091394 0008DF74  7F C3 F3 78 */	mr r3, r30
/* 80091398 0008DF78  C0 24 07 98 */	lfs f1, 0x798(r4)
/* 8009139C 0008DF7C  4B FE C8 6D */	bl ftCommon_8007DC08
/* 800913A0 0008DF80  C0 3E 1A 4C */	lfs f1, 0x1a4c(r30)
/* 800913A4 0008DF84  C0 02 8B 38 */	lfs f0, 0.0f
/* 800913A8 0008DF88  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 800913AC 0008DF8C  4C 40 13 82 */	cror 2, 0, 2
/* 800913B0 0008DF90  40 82 00 0C */	bne lbl_800913BC
/* 800913B4 0008DF94  7F A3 EB 78 */	mr r3, r29
/* 800913B8 0008DF98  48 00 04 9D */	bl ftCo_80091854
lbl_800913BC:
/* 800913BC 0008DF9C  80 01 00 2C */	lwz r0, 0x2c(r1)
/* 800913C0 0008DFA0  CB E1 00 20 */	lfd f31, 0x20(r1)
/* 800913C4 0008DFA4  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 800913C8 0008DFA8  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 800913CC 0008DFAC  83 A1 00 14 */	lwz r29, 0x14(r1)
/* 800913D0 0008DFB0  38 21 00 28 */	addi r1, r1, 0x28
/* 800913D4 0008DFB4  7C 08 03 A6 */	mtlr r0
/* 800913D8 0008DFB8  4E 80 00 20 */	blr
}
#pragma peephole on
#endif /* clang-format on */

void ftCo_DamageIce_IASA(ftCo_GObj* gobj) {}

void ftCo_DamageIce_Phys(ftCo_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8] = { 0 };
#endif
    ftCo_Fighter* fp = gobj->user_data;
    ftCo_DatAttrs* co = &fp->co_attrs;
    if (fp->ground_or_air == GA_Air) {
        ftCommon_8007CEF4(fp);
        ftCommon_8007D494(fp, co->grav * p_ftCommonData->x77C,
                          co->terminal_vel);
    } else {
        ft_80084F3C(gobj);
    }
}

void ftCo_DamageIce_Coll(ftCo_GObj* gobj)
{
    ftCo_Fighter* fp = gobj->user_data;
    if (fp->ground_or_air == GA_Air) {
        ftCo_800914A4(gobj);
    } else if (!ft_80082888(gobj, &fp->mv.co.damageice.x8)) {
        ftCommon_8007D5D4(fp);
    }
}

ASM void ftCo_800914A4(ftCo_GObj* gobj)
#if !defined(MUST_MATCH) || defined(WIP)
{
    NOT_IMPLEMENTED;
}
#else /* clang-format off */
{ nofralloc
/* 800914A4 0008E084  7C 08 02 A6 */	mflr r0
/* 800914A8 0008E088  90 01 00 04 */	stw r0, 4(r1)
/* 800914AC 0008E08C  94 21 FF C8 */	stwu r1, -0x38(r1)
/* 800914B0 0008E090  93 E1 00 34 */	stw r31, 0x34(r1)
/* 800914B4 0008E094  93 C1 00 30 */	stw r30, 0x30(r1)
/* 800914B8 0008E098  93 A1 00 2C */	stw r29, 0x2c(r1)
/* 800914BC 0008E09C  7C 7D 1B 78 */	mr r29, r3
/* 800914C0 0008E0A0  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 800914C4 0008E0A4  C0 02 8B 40 */	lfs f0, 3.0f
/* 800914C8 0008E0A8  C0 3F 08 94 */	lfs f1, 0x894(r31)
/* 800914CC 0008E0AC  3B DF 06 F0 */	addi r30, r31, 0x6f0
/* 800914D0 0008E0B0  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 800914D4 0008E0B4  4C 40 13 82 */	cror 2, 0, 2
/* 800914D8 0008E0B8  40 82 00 14 */	bne lbl_800914EC
/* 800914DC 0008E0BC  38 7D 00 00 */	addi r3, r29, 0
/* 800914E0 0008E0C0  38 9F 23 48 */	addi r4, r31, 0x2348
/* 800914E4 0008E0C4  4B FF 11 55 */	bl ft_80082638
/* 800914E8 0008E0C8  48 00 00 10 */	b lbl_800914F8
lbl_800914EC:
/* 800914EC 0008E0CC  38 7D 00 00 */	addi r3, r29, 0
/* 800914F0 0008E0D0  38 9F 23 48 */	addi r4, r31, 0x2348
/* 800914F4 0008E0D4  4B FF 0F AD */	bl ft_800824A0
lbl_800914F8:
/* 800914F8 0008E0D8  80 9E 01 34 */	lwz r4, 0x134(r30)
/* 800914FC 0008E0DC  54 80 05 29 */	rlwinm. r0, r4, 0, 0x14, 0x14
/* 80091500 0008E0E0  41 82 00 50 */	beq lbl_80091550
/* 80091504 0008E0E4  88 1F 23 40 */	lbz r0, 0x2340(r31)
/* 80091508 0008E0E8  28 00 00 01 */	cmplwi r0, 1
/* 8009150C 0008E0EC  41 82 00 44 */	beq lbl_80091550
/* 80091510 0008E0F0  C0 3E 00 BC */	lfs f1, 0xbc(r30)
/* 80091514 0008E0F4  7F A3 EB 78 */	mr r3, r29
/* 80091518 0008E0F8  C0 02 8B 38 */	lfs f0, 0.0f
/* 8009151C 0008E0FC  38 81 00 1C */	addi r4, r1, 0x1c
/* 80091520 0008E100  D0 21 00 1C */	stfs f1, 0x1c(r1)
/* 80091524 0008E104  C0 3E 00 C0 */	lfs f1, 0xc0(r30)
/* 80091528 0008E108  D0 21 00 20 */	stfs f1, 0x20(r1)
/* 8009152C 0008E10C  D0 01 00 24 */	stfs f0, 0x24(r1)
/* 80091530 0008E110  48 06 09 ED */	bl ftKb_SpecialN_800F1F1C
/* 80091534 0008E114  38 9E 01 7C */	addi r4, r30, 0x17c
/* 80091538 0008E118  38 7D 00 00 */	addi r3, r29, 0
/* 8009153C 0008E11C  38 A1 00 1C */	addi r5, r1, 0x1c
/* 80091540 0008E120  48 00 00 E1 */	bl ftCo_80091620
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
/* 8009156C 0008E14C  C0 02 8B 38 */	lfs f0, 0.0f
/* 80091570 0008E150  38 81 00 1C */	addi r4, r1, 0x1c
/* 80091574 0008E154  D0 21 00 1C */	stfs f1, 0x1c(r1)
/* 80091578 0008E158  C0 3E 00 B8 */	lfs f1, 0xb8(r30)
/* 8009157C 0008E15C  D0 21 00 20 */	stfs f1, 0x20(r1)
/* 80091580 0008E160  D0 01 00 24 */	stfs f0, 0x24(r1)
/* 80091584 0008E164  48 06 09 99 */	bl ftKb_SpecialN_800F1F1C
/* 80091588 0008E168  38 9E 01 68 */	addi r4, r30, 0x168
/* 8009158C 0008E16C  38 7D 00 00 */	addi r3, r29, 0
/* 80091590 0008E170  38 A1 00 1C */	addi r5, r1, 0x1c
/* 80091594 0008E174  48 00 00 8D */	bl ftCo_80091620
/* 80091598 0008E178  38 00 00 02 */	li r0, 2
/* 8009159C 0008E17C  98 1F 23 40 */	stb r0, 0x2340(r31)
/* 800915A0 0008E180  48 00 00 64 */	b lbl_80091604
lbl_800915A4:
/* 800915A4 0008E184  54 80 04 63 */	rlwinm. r0, r4, 0, 0x11, 0x11
/* 800915A8 0008E188  41 82 00 4C */	beq lbl_800915F4
/* 800915AC 0008E18C  88 1F 23 40 */	lbz r0, 0x2340(r31)
/* 800915B0 0008E190  28 00 00 03 */	cmplwi r0, 3
/* 800915B4 0008E194  41 82 00 40 */	beq lbl_800915F4
/* 800915B8 0008E198  C0 22 8B 38 */	lfs f1, 0.0f
/* 800915BC 0008E19C  38 7D 00 00 */	addi r3, r29, 0
/* 800915C0 0008E1A0  38 81 00 1C */	addi r4, r1, 0x1c
/* 800915C4 0008E1A4  D0 21 00 1C */	stfs f1, 0x1c(r1)
/* 800915C8 0008E1A8  C0 1E 00 A8 */	lfs f0, 0xa8(r30)
/* 800915CC 0008E1AC  D0 01 00 20 */	stfs f0, 0x20(r1)
/* 800915D0 0008E1B0  D0 21 00 24 */	stfs f1, 0x24(r1)
/* 800915D4 0008E1B4  48 06 09 49 */	bl ftKb_SpecialN_800F1F1C
/* 800915D8 0008E1B8  38 9E 01 90 */	addi r4, r30, 0x190
/* 800915DC 0008E1BC  38 7D 00 00 */	addi r3, r29, 0
/* 800915E0 0008E1C0  38 A1 00 1C */	addi r5, r1, 0x1c
/* 800915E4 0008E1C4  48 00 00 3D */	bl ftCo_80091620
/* 800915E8 0008E1C8  38 00 00 03 */	li r0, 3
/* 800915EC 0008E1CC  98 1F 23 40 */	stb r0, 0x2340(r31)
/* 800915F0 0008E1D0  48 00 00 14 */	b lbl_80091604
lbl_800915F4:
/* 800915F4 0008E1D4  2C 03 00 00 */	cmpwi r3, 0
/* 800915F8 0008E1D8  41 82 00 0C */	beq lbl_80091604
/* 800915FC 0008E1DC  7F E3 FB 78 */	mr r3, r31
/* 80091600 0008E1E0  4B FE C1 FD */	bl ftCommon_8007D7FC
lbl_80091604:
/* 80091604 0008E1E4  80 01 00 3C */	lwz r0, 0x3c(r1)
/* 80091608 0008E1E8  83 E1 00 34 */	lwz r31, 0x34(r1)
/* 8009160C 0008E1EC  83 C1 00 30 */	lwz r30, 0x30(r1)
/* 80091610 0008E1F0  83 A1 00 2C */	lwz r29, 0x2c(r1)
/* 80091614 0008E1F4  38 21 00 38 */	addi r1, r1, 0x38
/* 80091618 0008E1F8  7C 08 03 A6 */	mtlr r0
/* 8009161C 0008E1FC  4E 80 00 20 */	blr
}
#pragma peephole on
#endif /* clang-format on */

ASM UNK_RET ftCo_80091620(UNK_PARAMS)
#if !defined(MUST_MATCH) || defined(WIP)
{
    NOT_IMPLEMENTED;
}
#else /* clang-format off */
{ nofralloc
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
/* 800916B8 0008E298  4B F9 F7 8D */	bl Camera_80030E44
/* 800916BC 0008E29C  38 7F 00 00 */	addi r3, r31, 0
/* 800916C0 0008E2A0  38 80 00 07 */	li r4, 7
/* 800916C4 0008E2A4  38 A0 00 00 */	li r5, 0
/* 800916C8 0008E2A8  4B FE D4 E5 */	bl ftCommon_8007EBAC
/* 800916CC 0008E2AC  38 7F 00 00 */	addi r3, r31, 0
/* 800916D0 0008E2B0  38 80 01 23 */	li r4, 0x123
/* 800916D4 0008E2B4  38 A0 00 7F */	li r5, 0x7f
/* 800916D8 0008E2B8  38 C0 00 40 */	li r6, 0x40
/* 800916DC 0008E2BC  4B FF 6A 6D */	bl ft_80088148
/* 800916E0 0008E2C0  C0 3F 00 80 */	lfs f1, 0x80(r31)
/* 800916E4 0008E2C4  C0 1F 00 84 */	lfs f0, 0x84(r31)
/* 800916E8 0008E2C8  EC 41 00 72 */	fmuls f2, f1, f1
/* 800916EC 0008E2CC  C0 7F 00 88 */	lfs f3, 0x88(r31)
/* 800916F0 0008E2D0  EC 20 00 32 */	fmuls f1, f0, f0
/* 800916F4 0008E2D4  C0 02 8B 38 */	lfs f0, 0.0f
/* 800916F8 0008E2D8  EC 63 00 F2 */	fmuls f3, f3, f3
/* 800916FC 0008E2DC  EC 22 08 2A */	fadds f1, f2, f1
/* 80091700 0008E2E0  EC 83 08 2A */	fadds f4, f3, f1
/* 80091704 0008E2E4  FC 04 00 40 */	fcmpo cr0, f4, f0
/* 80091708 0008E2E8  40 81 00 50 */	ble lbl_80091758
/* 8009170C 0008E2EC  FC 20 20 34 */	frsqrte f1, f4
/* 80091710 0008E2F0  C8 62 8B 48 */	lfd f3, 0.5
/* 80091714 0008E2F4  C8 42 8B 50 */	lfd f2, 3.0
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
/* 80091758 0008E338  80 6D AE B4 */	lwz r3, p_ftCommonData
/* 8009175C 0008E33C  C0 03 07 80 */	lfs f0, 0x780(r3)
/* 80091760 0008E340  FC 04 00 40 */	fcmpo cr0, f4, f0
/* 80091764 0008E344  40 81 00 4C */	ble lbl_800917B0
/* 80091768 0008E348  38 7F 00 00 */	addi r3, r31, 0
/* 8009176C 0008E34C  38 80 01 23 */	li r4, 0x123
/* 80091770 0008E350  38 A0 00 7F */	li r5, 0x7f
/* 80091774 0008E354  38 C0 00 40 */	li r6, 0x40
/* 80091778 0008E358  4B FF 69 D1 */	bl ft_80088148
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
/* 800917A8 0008E388  4B FF EF D9 */	bl ftCo_80090780
/* 800917AC 0008E38C  48 00 00 94 */	b lbl_80091840
lbl_800917B0:
/* 800917B0 0008E390  38 7F 00 80 */	addi r3, r31, 0x80
/* 800917B4 0008E394  38 9C 00 00 */	addi r4, r28, 0
/* 800917B8 0008E398  4B F7 C4 B5 */	bl lbVector_Mirror
/* 800917BC 0008E39C  80 6D AE B4 */	lwz r3, p_ftCommonData
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
/* 8009182C 0008E40C  4B FF 04 E1 */	bl ft_80081D0C
/* 80091830 0008E410  2C 03 00 00 */	cmpwi r3, 0
/* 80091834 0008E414  41 82 00 0C */	beq lbl_80091840
/* 80091838 0008E418  7F E3 FB 78 */	mr r3, r31
/* 8009183C 0008E41C  4B FE BF C1 */	bl ftCommon_8007D7FC
lbl_80091840:
/* 80091840 0008E420  BB 61 00 4C */	lmw r27, 0x4c(r1)
/* 80091844 0008E424  80 01 00 64 */	lwz r0, 0x64(r1)
/* 80091848 0008E428  38 21 00 60 */	addi r1, r1, 0x60
/* 8009184C 0008E42C  7C 08 03 A6 */	mtlr r0
/* 80091850 0008E430  4E 80 00 20 */	blr
}
#pragma peephole on
#endif /* clang-format on */
#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-but-set-variable"
#endif

ASM void ftCo_80091854(HSD_GObj* gobj)
#if !defined(MUST_MATCH) || defined(WIP)
{
    Vec3 vec;
    f32 sp24;
    ftCo_Fighter* fp = gobj->user_data;
    if (ftCo_800C5240(gobj)) {
        ftCo_800C5A98(gobj);
    } else {
        ftCommon_8007D5D4(fp);
        fp->x2227_flag.bits.b5 = false;
        Fighter_ChangeMotionState(gobj, 0x146, 0x40U, 0, 0, 0, NULL);
        ft_80088148(fp, 0x123, 0x7F, 0x40);
        {
            HSD_JObj* jobj =
                fp->parts[ftParts_8007500C(fp, FtPart_XRotN)].joint;
            vec.x = ftCo_803B74BC.x;
            vec.y = ftCo_803B74BC.y;
            vec.z = (s32) ftCo_803B74BC.z;
            {
                f32 temp_f2 = M2C_FIELD(fp, f32*, 0x38);
                f32 temp_f1 = temp_f2 * fp->co_attrs.bubble_ratio;
                sp24 = temp_f1 / p_ftCommonData->x7A0;
                efAsync_Spawn(gobj, GET_FIGHTER(gobj)->x60C, 5, 1091, jobj);
            }
            fp->self_vel.x = fp->input.lstick.x * fp->co_attrs.x144;
            fp->self_vel.y = fp->co_attrs.x140;
            fp->mv.co.damageicejump.x0 = p_ftCommonData->x7A4;
        }
    }
}
#else /* clang-format off */
{ nofralloc
/* 80091854 0008E434  7C 08 02 A6 */	mflr r0
/* 80091858 0008E438  90 01 00 04 */	stw r0, 4(r1)
/* 8009185C 0008E43C  94 21 FF C0 */	stwu r1, -0x40(r1)
/* 80091860 0008E440  93 E1 00 3C */	stw r31, 0x3c(r1)
/* 80091864 0008E444  93 C1 00 38 */	stw r30, 0x38(r1)
/* 80091868 0008E448  7C 7E 1B 78 */	mr r30, r3
/* 8009186C 0008E44C  83 E3 00 2C */	lwz r31, 0x2c(r3)
/* 80091870 0008E450  48 03 39 D1 */	bl ftCo_800C5240
/* 80091874 0008E454  2C 03 00 00 */	cmpwi r3, 0
/* 80091878 0008E458  41 82 00 10 */	beq lbl_80091888
/* 8009187C 0008E45C  7F C3 F3 78 */	mr r3, r30
/* 80091880 0008E460  48 03 42 19 */	bl ftCo_800C5A98
/* 80091884 0008E464  48 00 00 EC */	b lbl_80091970
lbl_80091888:
/* 80091888 0008E468  7F E3 FB 78 */	mr r3, r31
/* 8009188C 0008E46C  4B FE BD 49 */	bl ftCommon_8007D5D4
/* 80091890 0008E470  88 1F 22 27 */	lbz r0, 0x2227(r31)
/* 80091894 0008E474  38 60 00 00 */	li r3, 0
/* 80091898 0008E478  50 60 0F BC */	rlwimi r0, r3, 1, 0x1e, 0x1e
/* 8009189C 0008E47C  98 1F 22 27 */	stb r0, 0x2227(r31)
/* 800918A0 0008E480  38 7E 00 00 */	addi r3, r30, 0
/* 800918A4 0008E484  38 80 01 46 */	li r4, 0x146
/* 800918A8 0008E488  C0 22 8B 38 */	lfs f1, 0.0f
/* 800918AC 0008E48C  38 A0 00 40 */	li r5, 0x40
/* 800918B0 0008E490  38 C0 00 00 */	li r6, 0
/* 800918B4 0008E494  FC 40 08 90 */	fmr f2, f1
/* 800918B8 0008E498  FC 60 08 90 */	fmr f3, f1
/* 800918BC 0008E49C  4B FD 7A F1 */	bl Fighter_ChangeMotionState
/* 800918C0 0008E4A0  38 7F 00 00 */	addi r3, r31, 0
/* 800918C4 0008E4A4  38 80 01 23 */	li r4, 0x123
/* 800918C8 0008E4A8  38 A0 00 7F */	li r5, 0x7f
/* 800918CC 0008E4AC  38 C0 00 40 */	li r6, 0x40
/* 800918D0 0008E4B0  4B FF 68 79 */	bl ft_80088148
/* 800918D4 0008E4B4  38 7F 00 00 */	addi r3, r31, 0
/* 800918D8 0008E4B8  38 80 00 02 */	li r4, 2
/* 800918DC 0008E4BC  4B FE 37 31 */	bl ftParts_8007500C
/* 800918E0 0008E4C0  3C A0 80 3B */	lis r5, ftCo_803B74BC@ha
/* 800918E4 0008E4C4  80 DF 05 E8 */	lwz r6, 0x5e8(r31)
/* 800918E8 0008E4C8  54 60 20 36 */	slwi r0, r3, 4
/* 800918EC 0008E4CC  80 8D AE B4 */	lwz r4, p_ftCommonData
/* 800918F0 0008E4D0  39 45 74 BC */	addi r10, r5, ftCo_803B74BC@l
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
/* 80091964 0008E544  80 6D AE B4 */	lwz r3, p_ftCommonData
/* 80091968 0008E548  C0 03 07 A4 */	lfs f0, 0x7a4(r3)
/* 8009196C 0008E54C  D0 1F 23 40 */	stfs f0, 0x2340(r31)
lbl_80091970:
/* 80091970 0008E550  80 01 00 44 */	lwz r0, 0x44(r1)
/* 80091974 0008E554  83 E1 00 3C */	lwz r31, 0x3c(r1)
/* 80091978 0008E558  83 C1 00 38 */	lwz r30, 0x38(r1)
/* 8009197C 0008E55C  38 21 00 40 */	addi r1, r1, 0x40
/* 80091980 0008E560  7C 08 03 A6 */	mtlr r0
/* 80091984 0008E564  4E 80 00 20 */	blr
}
#pragma peephole on
#endif /* clang-format on */
#if defined(__clang__)
#pragma clang diagnostic pop
#endif

void ftCo_DamageIceJump_Anim(HSD_GObj* gobj)
{
    ftCo_Fighter* fp = gobj->user_data;
    if (fp->mv.co.damageicejump.x0 > 0) {
        fp->mv.co.damageicejump.x0 -= 1;
        if (fp->mv.co.damageicejump.x0 <= 0) {
            ftCo_800CC730(gobj);
        }
    }
}

void ftCo_DamageIceJump_IASA(ftCo_GObj* gobj) {}

void ftCo_DamageIceJump_Phys(ftCo_GObj* gobj)
{
    ft_80084EEC(gobj);
}

void ftCo_DamageIceJump_Coll(ftCo_GObj* gobj)
{
    ft_800831CC(gobj, ftCo_80096CC8, ft_80082B1C);
}
