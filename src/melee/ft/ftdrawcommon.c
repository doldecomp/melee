#include <dolphin/mtx.h>
#include <dolphin/types.h>
#include <melee/ft/fighter.h>
#include <melee/ft/ftcommon.h>
#include <melee/ft/ftdata.h>
#include <melee/ft/ftdrawcommon.h>
#include <melee/ft/ftlib.h>
#include <sysdolphin/baselib/cobj.h>
#include <sysdolphin/baselib/debug.h>
#include <sysdolphin/baselib/jobj.h>
#include <sysdolphin/baselib/state.h>

static char lbl_803C0EB0[] = "translate";
static s32 lbl_804D3A88 = -128;
static s32 lbl_804D3A8C = 0x8080FF80;
static s32 lbl_804D3A90 = 0x80808080;

static char lbl_804D3A94[] = "jobj.h";
static char lbl_804D3A9C[] = "jobj";

extern f32 lbl_804D8368;
extern s32 lbl_804D836C[1];
extern s32 lbl_804D8370[2];

extern unk_t func_800750C8();
extern unk_t func_8009F7F8();
extern unk_t func_800C8AF0();
extern unk_t HSD_JObjDispAll();
extern unk_t func_8009F5AC();
extern unk_t func_80369808();
extern unk_t func_800310B8();
extern unk_t func_80031060();
extern unk_t func_800C2600();
extern unk_t func_8000A1A8();
extern unk_t func_8000A044();
extern unk_t func_8001E2F8();
extern unk_t func_80014770();
extern unk_t func_800B395C();
extern unk_t func_800117F4();
extern unk_t func_8000A460();
extern unk_t func_8000A78C();
extern unk_t func_8000AB2C();
extern unk_t func_8000A95C();
extern unk_t func_8000A244();
extern unk_t func_8000A584();
extern unk_t func_80009F54();

static inline mtx_thing(MtxPtr mtx, Vec* ptr, f32 val, f32 val2)
{
    mtx[0][3] = ptr->x + val;
    mtx[1][3] = ptr->y + val;
    mtx[2][3] = ptr->z + val2;
}

MtxPtr func_8008051C(HSD_GObj* arg1, MtxPtr arg2)
{
    u8 pad2[0x4];

    Vec sp54;

    u8 pad1[0xC];

    Mtx sp18;

    u8 pad0[0x8];

    f32 temp_f31;
    f32 temp_f0;

    MtxPtr temp_r31;

    temp_f31 = temp_f0 = 0.0F;
    sp54.z = temp_f31;
    sp54.y = temp_f31;
    sp54.x = temp_f31;
    if (func_80087074(arg1, &sp54)) {
        temp_r31 = HSD_CObjGetCurrent()->view_mtx;
        PSMTXIdentity(sp18);

        mtx_thing(sp18, &sp54, temp_f31, temp_f0);

        PSMTXConcat(temp_r31, sp18, arg2);
        return arg2;
    }
    return NULL;
}

#ifdef NON_MATCHING

// https://decomp.me/scratch/wbs6Q // 7183 (82.39%)
void func_800805C8(HSD_GObj* gobj, s32 arg1, s32 arg2)
{
    u8 padding2[0x4];

    Mtx sp78;
    Mtx sp48;

    u8 padding1[0xC];

    Vec sp30;

    u8 padding0[0x14];

    s32 spA8;
    s32 spAC;
    f32 temp_f0;
    f32 temp_f31;
    Vec* temp_r4;
    MtxPtr temp_r29;
    s32 fighter_2;
    u32 temp_r25;

    void* fighter0;

    itPickup* temp_r24;
    Fighter* fighter;
    Fighter* phi_r26;
    u32 phi_r25;

    u32 phi_r24;

    u32 phi_r30;
    MtxPtr phi_r29;

    fighter = gobj->user_data;
    phi_r30 = 0U;
    phi_r30 = 0U;
    if (fighter->x21FC_flag.bits.b6 != 0) {
        phi_r26 = fighter + 0x138 * 0;
        phi_r25 = 0U;
        do {
            if (func_80009F54(&phi_r26->x914, arg1, fighter->x34_scale.y) != 0) {
                phi_r30 = 1U;
            }
            temp_r25 = phi_r25 + 1;
            phi_r26 = phi_r26 + 0x138;
            phi_r25 = temp_r25;
            phi_r30 = phi_r30;
        } while (temp_r25 < 4U);
        if (fighter->x221D_flag.bits.b6 != 0) {
            phi_r26 = fighter + (0U * 0x4C);
            phi_r30 = phi_r30;
            while (phi_r25 < fighter->x119E_hurtboxNum) {
                if (func_8000A584(phi_r26->x11A0_fighterHurtbox, 1, arg1, func_8007F804(fighter), fighter->xB0_pos.z) != 0) {
                    phi_r30 = 1U;
                }
                phi_r25 += 1;
                phi_r26 = phi_r26 + 0x4C;
            }
        } else {
            fighter_2 = fighter->x1988;
            if ((fighter_2 == 0) && ((s32) fighter->x198C == 0)) {
                phi_r26 = fighter;
                phi_r30 = phi_r30;
                while (phi_r25 <  fighter->x119E_hurtboxNum) {
                    if (func_8000A244(phi_r26->x11A0_fighterHurtbox, arg1, func_8007F804(fighter), fighter->xB0_pos.z) != 0) {
                        phi_r30 = 1U;
                    }
                    phi_r25 += 1;
                    phi_r26 += 0x4C;
                }
            } else {
                if ((fighter->x198C == 2) || (fighter_2 == 2)) {
                    phi_r24 = 2;
                } else {
                    phi_r24 = 1;
                }
                phi_r26 = fighter;
                phi_r30 = phi_r30;
                while (phi_r25 < fighter->x119E_hurtboxNum) {
                    if (func_8000A584(phi_r26->x11A0_fighterHurtbox, phi_r24, arg1, func_8007F804(fighter), fighter->xB0_pos.z) != 0) {
                        phi_r30 = 1U;
                    }
                    phi_r25 += 1;
                    phi_r26 += 0x4C;
                }
            }
        }
        if ((fighter->x2218_flag.bits.b3 != 0) && (func_8000A95C(fighter + 0x19E4, arg1, func_8007F804(fighter), fighter->xB0_pos.z) != 0)) {
            phi_r30 = 1U;
        }
        if ((fighter->x2218_flag.bits.b6 != 0) && (func_8000AB2C(fighter + 0x1A08, arg1, func_8007F804(fighter), fighter->xB0_pos.z) != 0)) {
            phi_r30 = 1U;
        }
        if ((fighter->x221B_flag.bits.b0 != 0) && (func_8000A78C(fighter + 0x19C0, arg1, func_8007F804(fighter), fighter->xB0_pos.z) != 0)) {
            phi_r30 = 1U;
        }
    }
    phi_r30 = phi_r30;
    if (fighter->x21FC_flag.bits.b5 != 0) {
        phi_r25 = 0U;
        phi_r26 = fighter;
        phi_r25 = 0U;
        while (phi_r25 < (u8) fighter->x166C) {
            if (func_8000A460(&phi_r26->x1670, arg1) != 0) {
                phi_r30 = 1U;
            }
            phi_r25 += 1;
            phi_r26 += 0x28;
        }
        phi_r26 = fighter;
        while (phi_r25 < fighter->x3E0) {
            spAC = 0.0f; // lbl_804D836C; //change to actual label
            spA8 = 0.0f; // lbl_804D8370; //change to actual label
            if (func_800117F4(&phi_r26->x2F4, &spAC, &spA8, phi_r26->x3E0, arg1) != 0) {
                phi_r30 = 1U;
            }
            phi_r25 += 1;
            phi_r26 += 0x18;
        }
    }
    if ((fighter->x21FC_flag.bits.b3 != 0) && (func_800B395C(gobj, arg1) != 0)) {
        phi_r30 = 1U;
    }
    if ((fighter->x21FC_flag.bits.b4 != 0) && (fighter->x2223_flag.bits.b5 != 0) && (func_80014770(fighter + 0x1930, arg1) != 0)) {
        phi_r30 = 1U;
    }
    if (fighter->x21FC_flag.bits.b3 != 0) {
        temp_r24 = &fighter->x294_itPickup;
        if (fighter->xE0_ground_or_air == GA_Ground) {
            if (func_8001E2F8(&temp_r24->x0_ground_light_offset, &fighter->xB0_pos, &lbl_804D3A88, arg1, fighter->facing_direction) != 0) {
                phi_r30 = 1U;
            }
            if (func_8001E2F8(&temp_r24->x10_ground_heavy_offset, &fighter->xB0_pos, &lbl_804D3A90, arg1, fighter->facing_direction) != 0) {
                phi_r30 = 1U;
            }
        } else if (func_8001E2F8(&temp_r24->x20_air_light_offset, &fighter->xB0_pos, &lbl_804D3A8C, arg1, fighter->facing_direction) != 0) {
            phi_r30 = 1U;
        }
    }
    if ((fighter->x21FC_flag.bits.b2 != 0) && (fighter->x2227_flag.bits.b2 == 0) && (func_8000A044(&fighter->x1064_thrownHitbox, arg1, fighter->x34_scale.y) != 0)) {
        phi_r30 = 1U;
    }
    if ((fighter->x21FC_flag.bits.b0 != 0) && (fighter->x2229_b4 == 0)) {
        phi_r26 = fighter + (0U * 0x2C);
        phi_r25 = 0U;
        do {
            if (func_8000A1A8(&phi_r26->x1614, arg1, fighter->x34_scale.y) != 0) {
                phi_r30 = 1U;
            }
            temp_r25 = phi_r25 + 1;
            phi_r26 += 0x2C;
            phi_r25 = temp_r25;
        } while (temp_r25 < 2U);
    }
    if (phi_r30 != 0U) {
        HSD_StateInvalidate(-1);
    }
    if (fighter->x21FC_flag.bits.b7 != 0) {
        if ((fighter->x221E_flag.bits.b0 == 0) && (fighter->x221E_flag.bits.b5 == 0) && (arg2 != 0)) {
            func_800750C8(fighter, 1, 0);
            func_800750C8(fighter, 4, 0);
            if ((fighter->x2223_flag.bits.b7 != 0) || (fighter->x2226_flag.bits.b5 != 0) || (fighter->x2227_flag.bits.b3 != 0)) {
                func_800750C8(fighter, 0, 0);
                func_800750C8(fighter, 2, 1);
            } else {
                func_800750C8(fighter, 2, 0);
                func_800750C8(fighter, 0, 1);
            }
            func_8009F5AC(fighter);
            fighter->x2223_flag.bits.b2 = 0;
            temp_r4 = &sp30;
            fighter->x2227_flag.bits.b7 = 1;
            fighter->x2228_flag.bits.b0 = 0;
            temp_f31 = temp_f0 = 0.0f;
            sp30.z = temp_f31;
            sp30.y = temp_f31;
            sp30.x = temp_f31;
            phi_r29 = NULL;
            if (func_80087074(gobj, temp_r4) != 0) {
                temp_r29 = HSD_CObjGetCurrent()->view_mtx;

                PSMTXIdentity(sp48);

                mtx_thing(sp48, &sp30, temp_f31, temp_f0);

                PSMTXConcat(temp_r29, sp48, sp78);
                phi_r29 = sp78;
            }
            fighter0 = gobj->hsd_obj;
            HSD_JObjDispAll(fighter0, phi_r29, func_80390EB8(arg1), 0);
            if (lbl_803C20CC[fighter->x4_fighterKind] != NULL) {
                lbl_803C20CC[fighter->x4_fighterKind](gobj, arg1, (MtxPtr) phi_r29);
            }
            func_800C8AF0(fighter);
            func_8009F7F8(fighter);
        }
        if ((u32) fighter->x20A0_accessory != 0U) {
            HSD_JObjDispAll(fighter->x20A0_accessory, NULL, func_80390EB8(arg1), 0);
        }
        func_800C2600(gobj, arg1);
    }
}

#else

#pragma push
asm unk_t func_800805C8()
{ // clang-format off
    nofralloc
/* 800805C8 0007D1A8  7C 08 02 A6 */	mflr r0
/* 800805CC 0007D1AC  90 01 00 04 */	stw r0, 4(r1)
/* 800805D0 0007D1B0  94 21 FF 28 */	stwu r1, -0xd8(r1)
/* 800805D4 0007D1B4  DB E1 00 D0 */	stfd f31, 0xd0(r1)
/* 800805D8 0007D1B8  BF 01 00 B0 */	stmw r24, 0xb0(r1)
/* 800805DC 0007D1BC  7C 7B 1B 78 */	mr r27, r3
/* 800805E0 0007D1C0  3B 84 00 00 */	addi r28, r4, 0
/* 800805E4 0007D1C4  3B A5 00 00 */	addi r29, r5, 0
/* 800805E8 0007D1C8  3B C0 00 00 */	li r30, 0
/* 800805EC 0007D1CC  80 63 00 2C */	lwz r3, 0x2c(r3)
/* 800805F0 0007D1D0  88 03 21 FC */	lbz r0, 0x21fc(r3)
/* 800805F4 0007D1D4  3B E3 00 00 */	addi r31, r3, 0
/* 800805F8 0007D1D8  54 00 FF FF */	rlwinm. r0, r0, 0x1f, 0x1f, 0x1f
/* 800805FC 0007D1DC  41 82 02 10 */	beq lbl_8008080C
/* 80080600 0007D1E0  3B 20 00 00 */	li r25, 0
/* 80080604 0007D1E4  1C 19 01 38 */	mulli r0, r25, 0x138
/* 80080608 0007D1E8  7F 5F 02 14 */	add r26, r31, r0
lbl_8008060C:
/* 8008060C 0007D1EC  C0 3F 00 38 */	lfs f1, 0x38(r31)
/* 80080610 0007D1F0  38 9C 00 00 */	addi r4, r28, 0
/* 80080614 0007D1F4  38 7A 09 14 */	addi r3, r26, 0x914
/* 80080618 0007D1F8  4B F8 99 3D */	bl func_80009F54
/* 8008061C 0007D1FC  2C 03 00 00 */	cmpwi r3, 0
/* 80080620 0007D200  41 82 00 08 */	beq lbl_80080628
/* 80080624 0007D204  3B C0 00 01 */	li r30, 1
lbl_80080628:
/* 80080628 0007D208  3B 39 00 01 */	addi r25, r25, 1
/* 8008062C 0007D20C  28 19 00 04 */	cmplwi r25, 4
/* 80080630 0007D210  3B 5A 01 38 */	addi r26, r26, 0x138
/* 80080634 0007D214  41 80 FF D8 */	blt lbl_8008060C
/* 80080638 0007D218  88 1F 22 1D */	lbz r0, 0x221d(r31)
/* 8008063C 0007D21C  54 00 FF FF */	rlwinm. r0, r0, 0x1f, 0x1f, 0x1f
/* 80080640 0007D220  41 82 00 58 */	beq lbl_80080698
/* 80080644 0007D224  3B 20 00 00 */	li r25, 0
/* 80080648 0007D228  1C 19 00 4C */	mulli r0, r25, 0x4c
/* 8008064C 0007D22C  7F 5F 02 14 */	add r26, r31, r0
/* 80080650 0007D230  48 00 00 38 */	b lbl_80080688
lbl_80080654:
/* 80080654 0007D234  7F E3 FB 78 */	mr r3, r31
/* 80080658 0007D238  4B FF F1 AD */	bl func_8007F804
/* 8008065C 0007D23C  C0 3F 00 B8 */	lfs f1, 0xb8(r31)
/* 80080660 0007D240  38 C3 00 00 */	addi r6, r3, 0
/* 80080664 0007D244  38 BC 00 00 */	addi r5, r28, 0
/* 80080668 0007D248  38 7A 11 A0 */	addi r3, r26, 0x11a0
/* 8008066C 0007D24C  38 80 00 01 */	li r4, 1
/* 80080670 0007D250  4B F8 9F 15 */	bl func_8000A584
/* 80080674 0007D254  2C 03 00 00 */	cmpwi r3, 0
/* 80080678 0007D258  41 82 00 08 */	beq lbl_80080680
/* 8008067C 0007D25C  3B C0 00 01 */	li r30, 1
lbl_80080680:
/* 80080680 0007D260  3B 5A 00 4C */	addi r26, r26, 0x4c
/* 80080684 0007D264  3B 39 00 01 */	addi r25, r25, 1
lbl_80080688:
/* 80080688 0007D268  88 1F 11 9E */	lbz r0, 0x119e(r31)
/* 8008068C 0007D26C  7C 19 00 40 */	cmplw r25, r0
/* 80080690 0007D270  41 80 FF C4 */	blt lbl_80080654
/* 80080694 0007D274  48 00 00 DC */	b lbl_80080770
lbl_80080698:
/* 80080698 0007D278  80 7F 19 88 */	lwz r3, 0x1988(r31)
/* 8008069C 0007D27C  2C 03 00 00 */	cmpwi r3, 0
/* 800806A0 0007D280  40 82 00 60 */	bne lbl_80080700
/* 800806A4 0007D284  80 1F 19 8C */	lwz r0, 0x198c(r31)
/* 800806A8 0007D288  2C 00 00 00 */	cmpwi r0, 0
/* 800806AC 0007D28C  40 82 00 54 */	bne lbl_80080700
/* 800806B0 0007D290  3B 20 00 00 */	li r25, 0
/* 800806B4 0007D294  1C 19 00 4C */	mulli r0, r25, 0x4c
/* 800806B8 0007D298  7F 5F 02 14 */	add r26, r31, r0
/* 800806BC 0007D29C  48 00 00 34 */	b lbl_800806F0
lbl_800806C0:
/* 800806C0 0007D2A0  7F E3 FB 78 */	mr r3, r31
/* 800806C4 0007D2A4  4B FF F1 41 */	bl func_8007F804
/* 800806C8 0007D2A8  C0 3F 00 B8 */	lfs f1, 0xb8(r31)
/* 800806CC 0007D2AC  38 A3 00 00 */	addi r5, r3, 0
/* 800806D0 0007D2B0  38 9C 00 00 */	addi r4, r28, 0
/* 800806D4 0007D2B4  38 7A 11 A0 */	addi r3, r26, 0x11a0
/* 800806D8 0007D2B8  4B F8 9B 6D */	bl func_8000A244
/* 800806DC 0007D2BC  2C 03 00 00 */	cmpwi r3, 0
/* 800806E0 0007D2C0  41 82 00 08 */	beq lbl_800806E8
/* 800806E4 0007D2C4  3B C0 00 01 */	li r30, 1
lbl_800806E8:
/* 800806E8 0007D2C8  3B 5A 00 4C */	addi r26, r26, 0x4c
/* 800806EC 0007D2CC  3B 39 00 01 */	addi r25, r25, 1
lbl_800806F0:
/* 800806F0 0007D2D0  88 1F 11 9E */	lbz r0, 0x119e(r31)
/* 800806F4 0007D2D4  7C 19 00 40 */	cmplw r25, r0
/* 800806F8 0007D2D8  41 80 FF C8 */	blt lbl_800806C0
/* 800806FC 0007D2DC  48 00 00 74 */	b lbl_80080770
lbl_80080700:
/* 80080700 0007D2E0  80 1F 19 8C */	lwz r0, 0x198c(r31)
/* 80080704 0007D2E4  2C 00 00 02 */	cmpwi r0, 2
/* 80080708 0007D2E8  41 82 00 0C */	beq lbl_80080714
/* 8008070C 0007D2EC  2C 03 00 02 */	cmpwi r3, 2
/* 80080710 0007D2F0  40 82 00 0C */	bne lbl_8008071C
lbl_80080714:
/* 80080714 0007D2F4  3B 00 00 02 */	li r24, 2
/* 80080718 0007D2F8  48 00 00 08 */	b lbl_80080720
lbl_8008071C:
/* 8008071C 0007D2FC  3B 00 00 01 */	li r24, 1
lbl_80080720:
/* 80080720 0007D300  3B 20 00 00 */	li r25, 0
/* 80080724 0007D304  1C 19 00 4C */	mulli r0, r25, 0x4c
/* 80080728 0007D308  7F 5F 02 14 */	add r26, r31, r0
/* 8008072C 0007D30C  48 00 00 38 */	b lbl_80080764
lbl_80080730:
/* 80080730 0007D310  7F E3 FB 78 */	mr r3, r31
/* 80080734 0007D314  4B FF F0 D1 */	bl func_8007F804
/* 80080738 0007D318  C0 3F 00 B8 */	lfs f1, 0xb8(r31)
/* 8008073C 0007D31C  38 C3 00 00 */	addi r6, r3, 0
/* 80080740 0007D320  38 98 00 00 */	addi r4, r24, 0
/* 80080744 0007D324  38 BC 00 00 */	addi r5, r28, 0
/* 80080748 0007D328  38 7A 11 A0 */	addi r3, r26, 0x11a0
/* 8008074C 0007D32C  4B F8 9E 39 */	bl func_8000A584
/* 80080750 0007D330  2C 03 00 00 */	cmpwi r3, 0
/* 80080754 0007D334  41 82 00 08 */	beq lbl_8008075C
/* 80080758 0007D338  3B C0 00 01 */	li r30, 1
lbl_8008075C:
/* 8008075C 0007D33C  3B 5A 00 4C */	addi r26, r26, 0x4c
/* 80080760 0007D340  3B 39 00 01 */	addi r25, r25, 1
lbl_80080764:
/* 80080764 0007D344  88 1F 11 9E */	lbz r0, 0x119e(r31)
/* 80080768 0007D348  7C 19 00 40 */	cmplw r25, r0
/* 8008076C 0007D34C  41 80 FF C4 */	blt lbl_80080730
lbl_80080770:
/* 80080770 0007D350  88 1F 22 18 */	lbz r0, 0x2218(r31)
/* 80080774 0007D354  54 00 E7 FF */	rlwinm. r0, r0, 0x1c, 0x1f, 0x1f
/* 80080778 0007D358  41 82 00 2C */	beq lbl_800807A4
/* 8008077C 0007D35C  7F E3 FB 78 */	mr r3, r31
/* 80080780 0007D360  4B FF F0 85 */	bl func_8007F804
/* 80080784 0007D364  C0 3F 00 B8 */	lfs f1, 0xb8(r31)
/* 80080788 0007D368  38 A3 00 00 */	addi r5, r3, 0
/* 8008078C 0007D36C  38 9C 00 00 */	addi r4, r28, 0
/* 80080790 0007D370  38 7F 19 E4 */	addi r3, r31, 0x19e4
/* 80080794 0007D374  4B F8 A1 C9 */	bl func_8000A95C
/* 80080798 0007D378  2C 03 00 00 */	cmpwi r3, 0
/* 8008079C 0007D37C  41 82 00 08 */	beq lbl_800807A4
/* 800807A0 0007D380  3B C0 00 01 */	li r30, 1
lbl_800807A4:
/* 800807A4 0007D384  88 1F 22 18 */	lbz r0, 0x2218(r31)
/* 800807A8 0007D388  54 00 FF FF */	rlwinm. r0, r0, 0x1f, 0x1f, 0x1f
/* 800807AC 0007D38C  41 82 00 2C */	beq lbl_800807D8
/* 800807B0 0007D390  7F E3 FB 78 */	mr r3, r31
/* 800807B4 0007D394  4B FF F0 51 */	bl func_8007F804
/* 800807B8 0007D398  C0 3F 00 B8 */	lfs f1, 0xb8(r31)
/* 800807BC 0007D39C  38 A3 00 00 */	addi r5, r3, 0
/* 800807C0 0007D3A0  38 9C 00 00 */	addi r4, r28, 0
/* 800807C4 0007D3A4  38 7F 1A 08 */	addi r3, r31, 0x1a08
/* 800807C8 0007D3A8  4B F8 A3 65 */	bl func_8000AB2C
/* 800807CC 0007D3AC  2C 03 00 00 */	cmpwi r3, 0
/* 800807D0 0007D3B0  41 82 00 08 */	beq lbl_800807D8
/* 800807D4 0007D3B4  3B C0 00 01 */	li r30, 1
lbl_800807D8:
/* 800807D8 0007D3B8  88 1F 22 1B */	lbz r0, 0x221b(r31)
/* 800807DC 0007D3BC  54 00 CF FF */	rlwinm. r0, r0, 0x19, 0x1f, 0x1f
/* 800807E0 0007D3C0  41 82 00 2C */	beq lbl_8008080C
/* 800807E4 0007D3C4  7F E3 FB 78 */	mr r3, r31
/* 800807E8 0007D3C8  4B FF F0 1D */	bl func_8007F804
/* 800807EC 0007D3CC  C0 3F 00 B8 */	lfs f1, 0xb8(r31)
/* 800807F0 0007D3D0  38 A3 00 00 */	addi r5, r3, 0
/* 800807F4 0007D3D4  38 9C 00 00 */	addi r4, r28, 0
/* 800807F8 0007D3D8  38 7F 19 C0 */	addi r3, r31, 0x19c0
/* 800807FC 0007D3DC  4B F8 9F 91 */	bl func_8000A78C
/* 80080800 0007D3E0  2C 03 00 00 */	cmpwi r3, 0
/* 80080804 0007D3E4  41 82 00 08 */	beq lbl_8008080C
/* 80080808 0007D3E8  3B C0 00 01 */	li r30, 1
lbl_8008080C:
/* 8008080C 0007D3EC  88 1F 21 FC */	lbz r0, 0x21fc(r31)
/* 80080810 0007D3F0  54 00 F7 FF */	rlwinm. r0, r0, 0x1e, 0x1f, 0x1f
/* 80080814 0007D3F4  41 82 00 98 */	beq lbl_800808AC
/* 80080818 0007D3F8  3B 20 00 00 */	li r25, 0
/* 8008081C 0007D3FC  1C 19 00 28 */	mulli r0, r25, 0x28
/* 80080820 0007D400  7F 5F 02 14 */	add r26, r31, r0
/* 80080824 0007D404  48 00 00 24 */	b lbl_80080848
lbl_80080828:
/* 80080828 0007D408  38 7A 16 70 */	addi r3, r26, 0x1670
/* 8008082C 0007D40C  38 9C 00 00 */	addi r4, r28, 0
/* 80080830 0007D410  4B F8 9C 31 */	bl func_8000A460
/* 80080834 0007D414  2C 03 00 00 */	cmpwi r3, 0
/* 80080838 0007D418  41 82 00 08 */	beq lbl_80080840
/* 8008083C 0007D41C  3B C0 00 01 */	li r30, 1
lbl_80080840:
/* 80080840 0007D420  3B 5A 00 28 */	addi r26, r26, 0x28
/* 80080844 0007D424  3B 39 00 01 */	addi r25, r25, 1
lbl_80080848:
/* 80080848 0007D428  88 1F 16 6C */	lbz r0, 0x166c(r31)
/* 8008084C 0007D42C  7C 19 00 40 */	cmplw r25, r0
/* 80080850 0007D430  41 80 FF D8 */	blt lbl_80080828
/* 80080854 0007D434  3B 20 00 00 */	li r25, 0
/* 80080858 0007D438  1C 19 00 18 */	mulli r0, r25, 0x18
/* 8008085C 0007D43C  7F 5F 02 14 */	add r26, r31, r0
/* 80080860 0007D440  48 00 00 40 */	b lbl_800808A0
lbl_80080864:
/* 80080864 0007D444  80 82 89 8C */	lwz r4, lbl_804D836C(r2)
/* 80080868 0007D448  7F 87 E3 78 */	mr r7, r28
/* 8008086C 0007D44C  80 02 89 90 */	lwz r0, lbl_804D8370(r2)
/* 80080870 0007D450  38 7A 02 F4 */	addi r3, r26, 0x2f4
/* 80080874 0007D454  90 81 00 AC */	stw r4, 0xac(r1)
/* 80080878 0007D458  38 81 00 AC */	addi r4, r1, 0xac
/* 8008087C 0007D45C  90 01 00 A8 */	stw r0, 0xa8(r1)
/* 80080880 0007D460  38 A1 00 A8 */	addi r5, r1, 0xa8
/* 80080884 0007D464  80 DA 02 F0 */	lwz r6, 0x2f0(r26)
/* 80080888 0007D468  4B F9 0F 6D */	bl func_800117F4
/* 8008088C 0007D46C  2C 03 00 00 */	cmpwi r3, 0
/* 80080890 0007D470  41 82 00 08 */	beq lbl_80080898
/* 80080894 0007D474  3B C0 00 01 */	li r30, 1
lbl_80080898:
/* 80080898 0007D478  3B 5A 00 18 */	addi r26, r26, 0x18
/* 8008089C 0007D47C  3B 39 00 01 */	addi r25, r25, 1
lbl_800808A0:
/* 800808A0 0007D480  80 1F 03 E0 */	lwz r0, 0x3e0(r31)
/* 800808A4 0007D484  7C 19 00 40 */	cmplw r25, r0
/* 800808A8 0007D488  41 80 FF BC */	blt lbl_80080864
lbl_800808AC:
/* 800808AC 0007D48C  88 1F 21 FC */	lbz r0, 0x21fc(r31)
/* 800808B0 0007D490  54 00 E7 FF */	rlwinm. r0, r0, 0x1c, 0x1f, 0x1f
/* 800808B4 0007D494  41 82 00 1C */	beq lbl_800808D0
/* 800808B8 0007D498  38 7B 00 00 */	addi r3, r27, 0
/* 800808BC 0007D49C  38 9C 00 00 */	addi r4, r28, 0
/* 800808C0 0007D4A0  48 03 30 9D */	bl func_800B395C
/* 800808C4 0007D4A4  2C 03 00 00 */	cmpwi r3, 0
/* 800808C8 0007D4A8  41 82 00 08 */	beq lbl_800808D0
/* 800808CC 0007D4AC  3B C0 00 01 */	li r30, 1
lbl_800808D0:
/* 800808D0 0007D4B0  88 1F 21 FC */	lbz r0, 0x21fc(r31)
/* 800808D4 0007D4B4  54 00 EF FF */	rlwinm. r0, r0, 0x1d, 0x1f, 0x1f
/* 800808D8 0007D4B8  41 82 00 28 */	beq lbl_80080900
/* 800808DC 0007D4BC  88 1F 22 23 */	lbz r0, 0x2223(r31)
/* 800808E0 0007D4C0  54 00 F7 FF */	rlwinm. r0, r0, 0x1e, 0x1f, 0x1f
/* 800808E4 0007D4C4  41 82 00 1C */	beq lbl_80080900
/* 800808E8 0007D4C8  38 7F 19 30 */	addi r3, r31, 0x1930
/* 800808EC 0007D4CC  38 9C 00 00 */	addi r4, r28, 0
/* 800808F0 0007D4D0  4B F9 3E 81 */	bl func_80014770
/* 800808F4 0007D4D4  2C 03 00 00 */	cmpwi r3, 0
/* 800808F8 0007D4D8  41 82 00 08 */	beq lbl_80080900
/* 800808FC 0007D4DC  3B C0 00 01 */	li r30, 1
lbl_80080900:
/* 80080900 0007D4E0  88 1F 21 FC */	lbz r0, 0x21fc(r31)
/* 80080904 0007D4E4  54 00 DF FF */	rlwinm. r0, r0, 0x1b, 0x1f, 0x1f
/* 80080908 0007D4E8  41 82 00 84 */	beq lbl_8008098C
/* 8008090C 0007D4EC  80 1F 00 E0 */	lwz r0, 0xe0(r31)
/* 80080910 0007D4F0  3B 1F 02 94 */	addi r24, r31, 0x294
/* 80080914 0007D4F4  2C 00 00 00 */	cmpwi r0, 0
/* 80080918 0007D4F8  40 82 00 50 */	bne lbl_80080968
/* 8008091C 0007D4FC  C0 3F 00 2C */	lfs f1, 0x2c(r31)
/* 80080920 0007D500  38 78 00 00 */	addi r3, r24, 0
/* 80080924 0007D504  38 DC 00 00 */	addi r6, r28, 0
/* 80080928 0007D508  38 9F 00 B0 */	addi r4, r31, 0xb0
/* 8008092C 0007D50C  38 AD 83 E8 */	addi r5, r13, lbl_804D3A88
/* 80080930 0007D510  4B F9 D9 C9 */	bl func_8001E2F8
/* 80080934 0007D514  2C 03 00 00 */	cmpwi r3, 0
/* 80080938 0007D518  41 82 00 08 */	beq lbl_80080940
/* 8008093C 0007D51C  3B C0 00 01 */	li r30, 1
lbl_80080940:
/* 80080940 0007D520  C0 3F 00 2C */	lfs f1, 0x2c(r31)
/* 80080944 0007D524  38 DC 00 00 */	addi r6, r28, 0
/* 80080948 0007D528  38 78 00 10 */	addi r3, r24, 0x10
/* 8008094C 0007D52C  38 9F 00 B0 */	addi r4, r31, 0xb0
/* 80080950 0007D530  38 AD 83 F0 */	addi r5, r13, lbl_804D3A90
/* 80080954 0007D534  4B F9 D9 A5 */	bl func_8001E2F8
/* 80080958 0007D538  2C 03 00 00 */	cmpwi r3, 0
/* 8008095C 0007D53C  41 82 00 30 */	beq lbl_8008098C
/* 80080960 0007D540  3B C0 00 01 */	li r30, 1
/* 80080964 0007D544  48 00 00 28 */	b lbl_8008098C
lbl_80080968:
/* 80080968 0007D548  C0 3F 00 2C */	lfs f1, 0x2c(r31)
/* 8008096C 0007D54C  38 DC 00 00 */	addi r6, r28, 0
/* 80080970 0007D550  38 78 00 20 */	addi r3, r24, 0x20
/* 80080974 0007D554  38 9F 00 B0 */	addi r4, r31, 0xb0
/* 80080978 0007D558  38 AD 83 EC */	addi r5, r13, lbl_804D3A8C
/* 8008097C 0007D55C  4B F9 D9 7D */	bl func_8001E2F8
/* 80080980 0007D560  2C 03 00 00 */	cmpwi r3, 0
/* 80080984 0007D564  41 82 00 08 */	beq lbl_8008098C
/* 80080988 0007D568  3B C0 00 01 */	li r30, 1
lbl_8008098C:
/* 8008098C 0007D56C  88 1F 21 FC */	lbz r0, 0x21fc(r31)
/* 80080990 0007D570  54 00 D7 FF */	rlwinm. r0, r0, 0x1a, 0x1f, 0x1f
/* 80080994 0007D574  41 82 00 2C */	beq lbl_800809C0
/* 80080998 0007D578  88 1F 22 27 */	lbz r0, 0x2227(r31)
/* 8008099C 0007D57C  54 00 DF FF */	rlwinm. r0, r0, 0x1b, 0x1f, 0x1f
/* 800809A0 0007D580  40 82 00 20 */	bne lbl_800809C0
/* 800809A4 0007D584  C0 3F 00 38 */	lfs f1, 0x38(r31)
/* 800809A8 0007D588  38 9C 00 00 */	addi r4, r28, 0
/* 800809AC 0007D58C  38 7F 10 64 */	addi r3, r31, 0x1064
/* 800809B0 0007D590  4B F8 96 95 */	bl func_8000A044
/* 800809B4 0007D594  2C 03 00 00 */	cmpwi r3, 0
/* 800809B8 0007D598  41 82 00 08 */	beq lbl_800809C0
/* 800809BC 0007D59C  3B C0 00 01 */	li r30, 1
lbl_800809C0:
/* 800809C0 0007D5A0  88 1F 21 FC */	lbz r0, 0x21fc(r31)
/* 800809C4 0007D5A4  54 00 CF FF */	rlwinm. r0, r0, 0x19, 0x1f, 0x1f
/* 800809C8 0007D5A8  41 82 00 48 */	beq lbl_80080A10
/* 800809CC 0007D5AC  88 1F 22 29 */	lbz r0, 0x2229(r31)
/* 800809D0 0007D5B0  54 00 EF FF */	rlwinm. r0, r0, 0x1d, 0x1f, 0x1f
/* 800809D4 0007D5B4  40 82 00 3C */	bne lbl_80080A10
/* 800809D8 0007D5B8  3B 20 00 00 */	li r25, 0
/* 800809DC 0007D5BC  1C 19 00 2C */	mulli r0, r25, 0x2c
/* 800809E0 0007D5C0  7F 5F 02 14 */	add r26, r31, r0
lbl_800809E4:
/* 800809E4 0007D5C4  C0 3F 00 38 */	lfs f1, 0x38(r31)
/* 800809E8 0007D5C8  38 9C 00 00 */	addi r4, r28, 0
/* 800809EC 0007D5CC  38 7A 16 14 */	addi r3, r26, 0x1614
/* 800809F0 0007D5D0  4B F8 97 B9 */	bl func_8000A1A8
/* 800809F4 0007D5D4  2C 03 00 00 */	cmpwi r3, 0
/* 800809F8 0007D5D8  41 82 00 08 */	beq lbl_80080A00
/* 800809FC 0007D5DC  3B C0 00 01 */	li r30, 1
lbl_80080A00:
/* 80080A00 0007D5E0  3B 39 00 01 */	addi r25, r25, 1
/* 80080A04 0007D5E4  28 19 00 02 */	cmplwi r25, 2
/* 80080A08 0007D5E8  3B 5A 00 2C */	addi r26, r26, 0x2c
/* 80080A0C 0007D5EC  41 80 FF D8 */	blt lbl_800809E4
lbl_80080A10:
/* 80080A10 0007D5F0  28 1E 00 00 */	cmplwi r30, 0
/* 80080A14 0007D5F4  41 82 00 0C */	beq lbl_80080A20
/* 80080A18 0007D5F8  38 60 FF FF */	li r3, -1
/* 80080A1C 0007D5FC  48 2E 15 A9 */	bl HSD_StateInvalidate
lbl_80080A20:
/* 80080A20 0007D600  88 1F 21 FC */	lbz r0, 0x21fc(r31)
/* 80080A24 0007D604  54 00 07 FF */	clrlwi. r0, r0, 0x1f
/* 80080A28 0007D608  41 82 01 E8 */	beq lbl_80080C10
/* 80080A2C 0007D60C  88 7F 22 1E */	lbz r3, 0x221e(r31)
/* 80080A30 0007D610  54 60 CF FF */	rlwinm. r0, r3, 0x19, 0x1f, 0x1f
/* 80080A34 0007D614  40 82 01 A8 */	bne lbl_80080BDC
/* 80080A38 0007D618  54 60 F7 FF */	rlwinm. r0, r3, 0x1e, 0x1f, 0x1f
/* 80080A3C 0007D61C  40 82 01 A0 */	bne lbl_80080BDC
/* 80080A40 0007D620  2C 1D 00 00 */	cmpwi r29, 0
/* 80080A44 0007D624  41 82 01 98 */	beq lbl_80080BDC
/* 80080A48 0007D628  38 7F 00 00 */	addi r3, r31, 0
/* 80080A4C 0007D62C  38 80 00 01 */	li r4, 1
/* 80080A50 0007D630  38 A0 00 00 */	li r5, 0
/* 80080A54 0007D634  4B FF 46 75 */	bl func_800750C8
/* 80080A58 0007D638  38 7F 00 00 */	addi r3, r31, 0
/* 80080A5C 0007D63C  38 80 00 04 */	li r4, 4
/* 80080A60 0007D640  38 A0 00 00 */	li r5, 0
/* 80080A64 0007D644  4B FF 46 65 */	bl func_800750C8
/* 80080A68 0007D648  88 1F 22 23 */	lbz r0, 0x2223(r31)
/* 80080A6C 0007D64C  54 00 07 FF */	clrlwi. r0, r0, 0x1f
/* 80080A70 0007D650  40 82 00 1C */	bne lbl_80080A8C
/* 80080A74 0007D654  88 1F 22 26 */	lbz r0, 0x2226(r31)
/* 80080A78 0007D658  54 00 F7 FF */	rlwinm. r0, r0, 0x1e, 0x1f, 0x1f
/* 80080A7C 0007D65C  40 82 00 10 */	bne lbl_80080A8C
/* 80080A80 0007D660  88 1F 22 27 */	lbz r0, 0x2227(r31)
/* 80080A84 0007D664  54 00 E7 FF */	rlwinm. r0, r0, 0x1c, 0x1f, 0x1f
/* 80080A88 0007D668  41 82 00 28 */	beq lbl_80080AB0
lbl_80080A8C:
/* 80080A8C 0007D66C  38 7F 00 00 */	addi r3, r31, 0
/* 80080A90 0007D670  38 80 00 00 */	li r4, 0
/* 80080A94 0007D674  38 A0 00 00 */	li r5, 0
/* 80080A98 0007D678  4B FF 46 31 */	bl func_800750C8
/* 80080A9C 0007D67C  38 7F 00 00 */	addi r3, r31, 0
/* 80080AA0 0007D680  38 80 00 02 */	li r4, 2
/* 80080AA4 0007D684  38 A0 00 01 */	li r5, 1
/* 80080AA8 0007D688  4B FF 46 21 */	bl func_800750C8
/* 80080AAC 0007D68C  48 00 00 24 */	b lbl_80080AD0
lbl_80080AB0:
/* 80080AB0 0007D690  38 7F 00 00 */	addi r3, r31, 0
/* 80080AB4 0007D694  38 80 00 02 */	li r4, 2
/* 80080AB8 0007D698  38 A0 00 00 */	li r5, 0
/* 80080ABC 0007D69C  4B FF 46 0D */	bl func_800750C8
/* 80080AC0 0007D6A0  38 7F 00 00 */	addi r3, r31, 0
/* 80080AC4 0007D6A4  38 80 00 00 */	li r4, 0
/* 80080AC8 0007D6A8  38 A0 00 01 */	li r5, 1
/* 80080ACC 0007D6AC  4B FF 45 FD */	bl func_800750C8
lbl_80080AD0:
/* 80080AD0 0007D6B0  7F E3 FB 78 */	mr r3, r31
/* 80080AD4 0007D6B4  48 01 EA D9 */	bl func_8009F5AC
/* 80080AD8 0007D6B8  88 1F 22 23 */	lbz r0, 0x2223(r31)
/* 80080ADC 0007D6BC  3B A0 00 00 */	li r29, 0
/* 80080AE0 0007D6C0  53 A0 2E B4 */	rlwimi r0, r29, 5, 0x1a, 0x1a
/* 80080AE4 0007D6C4  98 1F 22 23 */	stb r0, 0x2223(r31)
/* 80080AE8 0007D6C8  38 80 00 01 */	li r4, 1
/* 80080AEC 0007D6CC  38 7B 00 00 */	addi r3, r27, 0
/* 80080AF0 0007D6D0  88 1F 22 27 */	lbz r0, 0x2227(r31)
/* 80080AF4 0007D6D4  50 80 07 FE */	rlwimi r0, r4, 0, 0x1f, 0x1f
/* 80080AF8 0007D6D8  38 81 00 30 */	addi r4, r1, 0x30
/* 80080AFC 0007D6DC  98 1F 22 27 */	stb r0, 0x2227(r31)
/* 80080B00 0007D6E0  88 1F 22 28 */	lbz r0, 0x2228(r31)
/* 80080B04 0007D6E4  53 A0 3E 30 */	rlwimi r0, r29, 7, 0x18, 0x18
/* 80080B08 0007D6E8  98 1F 22 28 */	stb r0, 0x2228(r31)
/* 80080B0C 0007D6EC  C3 E2 89 88 */	lfs f31, lbl_804D8368(r2)
/* 80080B10 0007D6F0  D3 E1 00 38 */	stfs f31, 0x38(r1)
/* 80080B14 0007D6F4  D3 E1 00 34 */	stfs f31, 0x34(r1)
/* 80080B18 0007D6F8  D3 E1 00 30 */	stfs f31, 0x30(r1)
/* 80080B1C 0007D6FC  48 00 65 59 */	bl func_80087074
/* 80080B20 0007D700  2C 03 00 00 */	cmpwi r3, 0
/* 80080B24 0007D704  41 82 00 50 */	beq lbl_80080B74
/* 80080B28 0007D708  48 2E 97 61 */	bl HSD_CObjGetCurrent
/* 80080B2C 0007D70C  3B A3 00 54 */	addi r29, r3, 0x54
/* 80080B30 0007D710  38 61 00 48 */	addi r3, r1, 0x48
/* 80080B34 0007D714  48 2C 16 71 */	bl PSMTXIdentity
/* 80080B38 0007D718  C0 21 00 30 */	lfs f1, 0x30(r1)
/* 80080B3C 0007D71C  7F A3 EB 78 */	mr r3, r29
/* 80080B40 0007D720  C0 02 89 88 */	lfs f0, lbl_804D8368(r2)
/* 80080B44 0007D724  38 81 00 48 */	addi r4, r1, 0x48
/* 80080B48 0007D728  EC 21 F8 2A */	fadds f1, f1, f31
/* 80080B4C 0007D72C  38 A1 00 78 */	addi r5, r1, 0x78
/* 80080B50 0007D730  D0 21 00 54 */	stfs f1, 0x54(r1)
/* 80080B54 0007D734  C0 21 00 34 */	lfs f1, 0x34(r1)
/* 80080B58 0007D738  EC 21 F8 2A */	fadds f1, f1, f31
/* 80080B5C 0007D73C  D0 21 00 64 */	stfs f1, 0x64(r1)
/* 80080B60 0007D740  C0 21 00 38 */	lfs f1, 0x38(r1)
/* 80080B64 0007D744  EC 01 00 2A */	fadds f0, f1, f0
/* 80080B68 0007D748  D0 01 00 74 */	stfs f0, 0x74(r1)
/* 80080B6C 0007D74C  48 2C 16 99 */	bl PSMTXConcat
/* 80080B70 0007D750  3B A1 00 78 */	addi r29, r1, 0x78
lbl_80080B74:
/* 80080B74 0007D754  83 DB 00 28 */	lwz r30, 0x28(r27)
/* 80080B78 0007D758  3B 1D 00 00 */	addi r24, r29, 0
/* 80080B7C 0007D75C  38 7C 00 00 */	addi r3, r28, 0
/* 80080B80 0007D760  48 31 03 39 */	bl func_80390EB8
/* 80080B84 0007D764  38 A3 00 00 */	addi r5, r3, 0
/* 80080B88 0007D768  38 7E 00 00 */	addi r3, r30, 0
/* 80080B8C 0007D76C  38 98 00 00 */	addi r4, r24, 0
/* 80080B90 0007D770  38 C0 00 00 */	li r6, 0
/* 80080B94 0007D774  48 2E FE 49 */	bl HSD_JObjDispAll
/* 80080B98 0007D778  80 9F 00 04 */	lwz r4, 4(r31)
/* 80080B9C 0007D77C  3C 60 80 3C */	lis r3, lbl_803C20CC@ha
/* 80080BA0 0007D780  38 03 20 CC */	addi r0, r3, lbl_803C20CC@l
/* 80080BA4 0007D784  54 83 10 3A */	slwi r3, r4, 2
/* 80080BA8 0007D788  7C 60 1A 14 */	add r3, r0, r3
/* 80080BAC 0007D78C  81 83 00 00 */	lwz r12, 0(r3)
/* 80080BB0 0007D790  28 0C 00 00 */	cmplwi r12, 0
/* 80080BB4 0007D794  41 82 00 18 */	beq lbl_80080BCC
/* 80080BB8 0007D798  7D 88 03 A6 */	mtlr r12
/* 80080BBC 0007D79C  38 7B 00 00 */	addi r3, r27, 0
/* 80080BC0 0007D7A0  38 9C 00 00 */	addi r4, r28, 0
/* 80080BC4 0007D7A4  38 B8 00 00 */	addi r5, r24, 0
/* 80080BC8 0007D7A8  4E 80 00 21 */	blrl 
lbl_80080BCC:
/* 80080BCC 0007D7AC  7F E3 FB 78 */	mr r3, r31
/* 80080BD0 0007D7B0  48 04 7F 21 */	bl func_800C8AF0
/* 80080BD4 0007D7B4  7F E3 FB 78 */	mr r3, r31
/* 80080BD8 0007D7B8  48 01 EC 21 */	bl func_8009F7F8
lbl_80080BDC:
/* 80080BDC 0007D7BC  80 1F 20 A0 */	lwz r0, 0x20a0(r31)
/* 80080BE0 0007D7C0  28 00 00 00 */	cmplwi r0, 0
/* 80080BE4 0007D7C4  41 82 00 20 */	beq lbl_80080C04
/* 80080BE8 0007D7C8  7F 83 E3 78 */	mr r3, r28
/* 80080BEC 0007D7CC  48 31 02 CD */	bl func_80390EB8
/* 80080BF0 0007D7D0  7C 65 1B 78 */	mr r5, r3
/* 80080BF4 0007D7D4  80 7F 20 A0 */	lwz r3, 0x20a0(r31)
/* 80080BF8 0007D7D8  38 80 00 00 */	li r4, 0
/* 80080BFC 0007D7DC  38 C0 00 00 */	li r6, 0
/* 80080C00 0007D7E0  48 2E FD DD */	bl HSD_JObjDispAll
lbl_80080C04:
/* 80080C04 0007D7E4  38 7B 00 00 */	addi r3, r27, 0
/* 80080C08 0007D7E8  38 9C 00 00 */	addi r4, r28, 0
/* 80080C0C 0007D7EC  48 04 19 F5 */	bl func_800C2600
lbl_80080C10:
/* 80080C10 0007D7F0  BB 01 00 B0 */	lmw r24, 0xb0(r1)
/* 80080C14 0007D7F4  80 01 00 DC */	lwz r0, 0xdc(r1)
/* 80080C18 0007D7F8  CB E1 00 D0 */	lfd f31, 0xd0(r1)
/* 80080C1C 0007D7FC  38 21 00 D8 */	addi r1, r1, 0xd8
/* 80080C20 0007D800  7C 08 03 A6 */	mtlr r0
/* 80080C24 0007D804  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

#endif

#ifdef NON_MATCHING

// https://decomp.me/scratch/sjQ3z // 155 (98.75%) @permuter
void func_80080C28(HSD_GObj* gobj, s32 arg1)
{
    MtxPtr temp_r28;
    f32 temp_f31;
    f32 temp_f0;

    Mtx sp70;
    Mtx sp40;

    u8 pad0[0xC];

    Vec sp30;

    Fighter* fighter;

    MtxPtr phi_r28;
    void* temp_r27;

    u8 pad1[0x18];

    fighter = gobj->user_data;
    if (fighter->x21FC_flag.bits.b7 != 0) {
        if ((fighter->x221E_flag.bits.b0 == 0) && (fighter->x221E_flag.bits.b5 == 0) && (fighter->x2226_flag.bits.b5 == 0)) {
            func_8009F5AC(fighter);
            if (fighter->x5BC != 0U) {
                func_800750C8(fighter, 0, 0);
                func_800750C8(fighter, 2, 0);
                func_800750C8(fighter, 4, 0);
                func_800750C8(fighter, 1, 1);
            }

            phi_r28 = NULL;

            fighter->x2223_flag.bits.b2 = 0;
            fighter->x2223_flag.bits.b3 = 0;
            fighter->x2227_flag.bits.b7 = 0;
            fighter->x2228_flag.bits.b0 = 1;

            temp_f31 = temp_f0 = 0.0f;
            sp30.z = temp_f31;
            sp30.y = temp_f31;
            sp30.x = temp_f31;

            if (func_80087074(gobj, &sp30) != 0) {
                temp_r28 = HSD_CObjGetCurrent()->view_mtx;
                PSMTXIdentity(sp40);

                mtx_thing(sp40, &sp30, temp_f31, temp_f0);

                PSMTXConcat(temp_r28, sp40, sp70);
                phi_r28 = sp70;
            }

            temp_r27 = gobj->hsd_obj;
            HSD_JObjDispAll(temp_r27, (MtxPtr) phi_r28, func_80390EB8(arg1), 0);
            if (lbl_803C20CC[fighter->x4_fighterKind] != NULL) {
                lbl_803C20CC[fighter->x4_fighterKind](gobj, arg1, (MtxPtr) phi_r28);
            }
            func_800C8AF0(fighter);
            func_8009F7F8(fighter);
        }
        if (fighter->x20A0_accessory != NULL) {
            HSD_JObjDispAll(fighter->x20A0_accessory, NULL, func_80390EB8(arg1), 0);
        }
    }
}

#else

#pragma push
asm unk_t func_80080C28()
{ // clang-format off
    nofralloc
/* 80080C28 0007D808  7C 08 02 A6 */	mflr r0
/* 80080C2C 0007D80C  90 01 00 04 */	stw r0, 4(r1)
/* 80080C30 0007D810  94 21 FF 40 */	stwu r1, -0xc0(r1)
/* 80080C34 0007D814  DB E1 00 B8 */	stfd f31, 0xb8(r1)
/* 80080C38 0007D818  BF 61 00 A4 */	stmw r27, 0xa4(r1)
/* 80080C3C 0007D81C  7C 7D 1B 78 */	mr r29, r3
/* 80080C40 0007D820  7C 9E 23 78 */	mr r30, r4
/* 80080C44 0007D824  80 63 00 2C */	lwz r3, 0x2c(r3)
/* 80080C48 0007D828  88 03 21 FC */	lbz r0, 0x21fc(r3)
/* 80080C4C 0007D82C  3B E3 00 00 */	addi r31, r3, 0
/* 80080C50 0007D830  54 00 07 FF */	clrlwi. r0, r0, 0x1f
/* 80080C54 0007D834  41 82 01 AC */	beq lbl_80080E00
/* 80080C58 0007D838  88 7F 22 1E */	lbz r3, 0x221e(r31)
/* 80080C5C 0007D83C  54 60 CF FF */	rlwinm. r0, r3, 0x19, 0x1f, 0x1f
/* 80080C60 0007D840  40 82 01 78 */	bne lbl_80080DD8
/* 80080C64 0007D844  54 60 F7 FF */	rlwinm. r0, r3, 0x1e, 0x1f, 0x1f
/* 80080C68 0007D848  40 82 01 70 */	bne lbl_80080DD8
/* 80080C6C 0007D84C  88 1F 22 26 */	lbz r0, 0x2226(r31)
/* 80080C70 0007D850  54 00 F7 FF */	rlwinm. r0, r0, 0x1e, 0x1f, 0x1f
/* 80080C74 0007D854  40 82 01 64 */	bne lbl_80080DD8
/* 80080C78 0007D858  7F E3 FB 78 */	mr r3, r31
/* 80080C7C 0007D85C  48 01 E9 31 */	bl func_8009F5AC
/* 80080C80 0007D860  80 1F 05 BC */	lwz r0, 0x5bc(r31)
/* 80080C84 0007D864  28 00 00 00 */	cmplwi r0, 0
/* 80080C88 0007D868  41 82 00 44 */	beq lbl_80080CCC
/* 80080C8C 0007D86C  38 7F 00 00 */	addi r3, r31, 0
/* 80080C90 0007D870  38 80 00 00 */	li r4, 0
/* 80080C94 0007D874  38 A0 00 00 */	li r5, 0
/* 80080C98 0007D878  4B FF 44 31 */	bl func_800750C8
/* 80080C9C 0007D87C  38 7F 00 00 */	addi r3, r31, 0
/* 80080CA0 0007D880  38 80 00 02 */	li r4, 2
/* 80080CA4 0007D884  38 A0 00 00 */	li r5, 0
/* 80080CA8 0007D888  4B FF 44 21 */	bl func_800750C8
/* 80080CAC 0007D88C  38 7F 00 00 */	addi r3, r31, 0
/* 80080CB0 0007D890  38 80 00 04 */	li r4, 4
/* 80080CB4 0007D894  38 A0 00 00 */	li r5, 0
/* 80080CB8 0007D898  4B FF 44 11 */	bl func_800750C8
/* 80080CBC 0007D89C  38 7F 00 00 */	addi r3, r31, 0
/* 80080CC0 0007D8A0  38 80 00 01 */	li r4, 1
/* 80080CC4 0007D8A4  38 A0 00 01 */	li r5, 1
/* 80080CC8 0007D8A8  4B FF 44 01 */	bl func_800750C8
lbl_80080CCC:
/* 80080CCC 0007D8AC  88 1F 22 23 */	lbz r0, 0x2223(r31)
/* 80080CD0 0007D8B0  3B 80 00 00 */	li r28, 0
/* 80080CD4 0007D8B4  53 80 2E B4 */	rlwimi r0, r28, 5, 0x1a, 0x1a
/* 80080CD8 0007D8B8  98 1F 22 23 */	stb r0, 0x2223(r31)
/* 80080CDC 0007D8BC  38 A0 00 01 */	li r5, 1
/* 80080CE0 0007D8C0  38 7D 00 00 */	addi r3, r29, 0
/* 80080CE4 0007D8C4  88 1F 22 23 */	lbz r0, 0x2223(r31)
/* 80080CE8 0007D8C8  53 80 26 F6 */	rlwimi r0, r28, 4, 0x1b, 0x1b
/* 80080CEC 0007D8CC  38 81 00 28 */	addi r4, r1, 0x28
/* 80080CF0 0007D8D0  98 1F 22 23 */	stb r0, 0x2223(r31)
/* 80080CF4 0007D8D4  88 1F 22 27 */	lbz r0, 0x2227(r31)
/* 80080CF8 0007D8D8  53 80 07 FE */	rlwimi r0, r28, 0, 0x1f, 0x1f
/* 80080CFC 0007D8DC  98 1F 22 27 */	stb r0, 0x2227(r31)
/* 80080D00 0007D8E0  88 1F 22 28 */	lbz r0, 0x2228(r31)
/* 80080D04 0007D8E4  50 A0 3E 30 */	rlwimi r0, r5, 7, 0x18, 0x18
/* 80080D08 0007D8E8  98 1F 22 28 */	stb r0, 0x2228(r31)
/* 80080D0C 0007D8EC  C3 E2 89 88 */	lfs f31, lbl_804D8368(r2)
/* 80080D10 0007D8F0  D3 E1 00 30 */	stfs f31, 0x30(r1)
/* 80080D14 0007D8F4  D3 E1 00 2C */	stfs f31, 0x2c(r1)
/* 80080D18 0007D8F8  D3 E1 00 28 */	stfs f31, 0x28(r1)
/* 80080D1C 0007D8FC  48 00 63 59 */	bl func_80087074
/* 80080D20 0007D900  2C 03 00 00 */	cmpwi r3, 0
/* 80080D24 0007D904  41 82 00 50 */	beq lbl_80080D74
/* 80080D28 0007D908  48 2E 95 61 */	bl HSD_CObjGetCurrent
/* 80080D2C 0007D90C  3B 83 00 54 */	addi r28, r3, 0x54
/* 80080D30 0007D910  38 61 00 40 */	addi r3, r1, 0x40
/* 80080D34 0007D914  48 2C 14 71 */	bl PSMTXIdentity
/* 80080D38 0007D918  C0 21 00 28 */	lfs f1, 0x28(r1)
/* 80080D3C 0007D91C  7F 83 E3 78 */	mr r3, r28
/* 80080D40 0007D920  C0 02 89 88 */	lfs f0, lbl_804D8368(r2)
/* 80080D44 0007D924  38 81 00 40 */	addi r4, r1, 0x40
/* 80080D48 0007D928  EC 21 F8 2A */	fadds f1, f1, f31
/* 80080D4C 0007D92C  38 A1 00 70 */	addi r5, r1, 0x70
/* 80080D50 0007D930  D0 21 00 4C */	stfs f1, 0x4c(r1)
/* 80080D54 0007D934  C0 21 00 2C */	lfs f1, 0x2c(r1)
/* 80080D58 0007D938  EC 21 F8 2A */	fadds f1, f1, f31
/* 80080D5C 0007D93C  D0 21 00 5C */	stfs f1, 0x5c(r1)
/* 80080D60 0007D940  C0 21 00 30 */	lfs f1, 0x30(r1)
/* 80080D64 0007D944  EC 01 00 2A */	fadds f0, f1, f0
/* 80080D68 0007D948  D0 01 00 6C */	stfs f0, 0x6c(r1)
/* 80080D6C 0007D94C  48 2C 14 99 */	bl PSMTXConcat
/* 80080D70 0007D950  3B 81 00 70 */	addi r28, r1, 0x70
lbl_80080D74:
/* 80080D74 0007D954  83 7D 00 28 */	lwz r27, 0x28(r29)
/* 80080D78 0007D958  7F C3 F3 78 */	mr r3, r30
/* 80080D7C 0007D95C  48 31 01 3D */	bl func_80390EB8
/* 80080D80 0007D960  38 A3 00 00 */	addi r5, r3, 0
/* 80080D84 0007D964  38 7B 00 00 */	addi r3, r27, 0
/* 80080D88 0007D968  38 9C 00 00 */	addi r4, r28, 0
/* 80080D8C 0007D96C  38 C0 00 00 */	li r6, 0
/* 80080D90 0007D970  48 2E FC 4D */	bl HSD_JObjDispAll
/* 80080D94 0007D974  80 9F 00 04 */	lwz r4, 4(r31)
/* 80080D98 0007D978  3C 60 80 3C */	lis r3, lbl_803C20CC@ha
/* 80080D9C 0007D97C  38 03 20 CC */	addi r0, r3, lbl_803C20CC@l
/* 80080DA0 0007D980  54 83 10 3A */	slwi r3, r4, 2
/* 80080DA4 0007D984  7C 60 1A 14 */	add r3, r0, r3
/* 80080DA8 0007D988  81 83 00 00 */	lwz r12, 0(r3)
/* 80080DAC 0007D98C  28 0C 00 00 */	cmplwi r12, 0
/* 80080DB0 0007D990  41 82 00 18 */	beq lbl_80080DC8
/* 80080DB4 0007D994  7D 88 03 A6 */	mtlr r12
/* 80080DB8 0007D998  38 7D 00 00 */	addi r3, r29, 0
/* 80080DBC 0007D99C  38 9E 00 00 */	addi r4, r30, 0
/* 80080DC0 0007D9A0  38 BC 00 00 */	addi r5, r28, 0
/* 80080DC4 0007D9A4  4E 80 00 21 */	blrl 
lbl_80080DC8:
/* 80080DC8 0007D9A8  7F E3 FB 78 */	mr r3, r31
/* 80080DCC 0007D9AC  48 04 7D 25 */	bl func_800C8AF0
/* 80080DD0 0007D9B0  7F E3 FB 78 */	mr r3, r31
/* 80080DD4 0007D9B4  48 01 EA 25 */	bl func_8009F7F8
lbl_80080DD8:
/* 80080DD8 0007D9B8  80 1F 20 A0 */	lwz r0, 0x20a0(r31)
/* 80080DDC 0007D9BC  28 00 00 00 */	cmplwi r0, 0
/* 80080DE0 0007D9C0  41 82 00 20 */	beq lbl_80080E00
/* 80080DE4 0007D9C4  7F C3 F3 78 */	mr r3, r30
/* 80080DE8 0007D9C8  48 31 00 D1 */	bl func_80390EB8
/* 80080DEC 0007D9CC  7C 65 1B 78 */	mr r5, r3
/* 80080DF0 0007D9D0  80 7F 20 A0 */	lwz r3, 0x20a0(r31)
/* 80080DF4 0007D9D4  38 80 00 00 */	li r4, 0
/* 80080DF8 0007D9D8  38 C0 00 00 */	li r6, 0
/* 80080DFC 0007D9DC  48 2E FB E1 */	bl HSD_JObjDispAll
lbl_80080E00:
/* 80080E00 0007D9E0  BB 61 00 A4 */	lmw r27, 0xa4(r1)
/* 80080E04 0007D9E4  80 01 00 C4 */	lwz r0, 0xc4(r1)
/* 80080E08 0007D9E8  CB E1 00 B8 */	lfd f31, 0xb8(r1)
/* 80080E0C 0007D9EC  38 21 00 C0 */	addi r1, r1, 0xc0
/* 80080E10 0007D9F0  7C 08 03 A6 */	mtlr r0
/* 80080E14 0007D9F4  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

#endif

#pragma push
asm void func_80080E18(HSD_GObj*, s32)
{ // clang-format off
    nofralloc
/* 80080E18 0007D9F8  7C 08 02 A6 */	mflr r0
/* 80080E1C 0007D9FC  90 01 00 04 */	stw r0, 4(r1)
/* 80080E20 0007DA00  94 21 FF 60 */	stwu r1, -0xa0(r1)
/* 80080E24 0007DA04  BF 61 00 8C */	stmw r27, 0x8c(r1)
/* 80080E28 0007DA08  7C 7C 1B 78 */	mr r28, r3
/* 80080E2C 0007DA0C  7C 9D 23 78 */	mr r29, r4
/* 80080E30 0007DA10  83 C3 00 2C */	lwz r30, 0x2c(r3)
/* 80080E34 0007DA14  88 1E 22 1F */	lbz r0, 0x221f(r30)
/* 80080E38 0007DA18  54 00 E7 FF */	rlwinm. r0, r0, 0x1c, 0x1f, 0x1f
/* 80080E3C 0007DA1C  40 82 02 C8 */	bne lbl_80081104
/* 80080E40 0007DA20  7F 83 E3 78 */	mr r3, r28
/* 80080E44 0007DA24  48 00 5C 49 */	bl func_80086A8C
/* 80080E48 0007DA28  2C 03 00 00 */	cmpwi r3, 0
/* 80080E4C 0007DA2C  41 82 02 B8 */	beq lbl_80081104
/* 80080E50 0007DA30  4B FB 02 11 */	bl func_80031060
/* 80080E54 0007DA34  2C 03 00 01 */	cmpwi r3, 1
/* 80080E58 0007DA38  41 82 00 14 */	beq lbl_80080E6C
/* 80080E5C 0007DA3C  40 80 02 A8 */	bge lbl_80081104
/* 80080E60 0007DA40  2C 03 00 00 */	cmpwi r3, 0
/* 80080E64 0007DA44  40 80 02 70 */	bge lbl_800810D4
/* 80080E68 0007DA48  48 00 02 9C */	b lbl_80081104
lbl_80080E6C:
/* 80080E6C 0007DA4C  88 1E 22 20 */	lbz r0, 0x2220(r30)
/* 80080E70 0007DA50  54 00 07 FF */	clrlwi. r0, r0, 0x1f
/* 80080E74 0007DA54  41 82 00 C4 */	beq lbl_80080F38
/* 80080E78 0007DA58  83 7C 00 2C */	lwz r27, 0x2c(r28)
/* 80080E7C 0007DA5C  83 FC 00 28 */	lwz r31, 0x28(r28)
/* 80080E80 0007DA60  4B FB 02 39 */	bl func_800310B8
/* 80080E84 0007DA64  48 2E 89 85 */	bl func_80369808
/* 80080E88 0007DA68  38 9E 23 50 */	addi r4, r30, 0x2350
/* 80080E8C 0007DA6C  38 BB 00 B0 */	addi r5, r27, 0xb0
/* 80080E90 0007DA70  48 2C 1C 19 */	bl PSMTXMUltiVec
/* 80080E94 0007DA74  28 1F 00 00 */	cmplwi r31, 0
/* 80080E98 0007DA78  3B 7B 00 B0 */	addi r27, r27, 0xb0
/* 80080E9C 0007DA7C  40 82 00 14 */	bne lbl_80080EB0
/* 80080EA0 0007DA80  38 6D 83 F4 */	addi r3, r13, lbl_804D3A94
/* 80080EA4 0007DA84  38 80 03 94 */	li r4, 0x394
/* 80080EA8 0007DA88  38 AD 83 FC */	addi r5, r13, lbl_804D3A9C
/* 80080EAC 0007DA8C  48 30 73 75 */	bl __assert
lbl_80080EB0:
/* 80080EB0 0007DA90  28 1B 00 00 */	cmplwi r27, 0
/* 80080EB4 0007DA94  40 82 00 18 */	bne lbl_80080ECC
/* 80080EB8 0007DA98  3C 60 80 3C */	lis r3, lbl_803C0EB0@ha
/* 80080EBC 0007DA9C  38 A3 0E B0 */	addi r5, r3, lbl_803C0EB0@l
/* 80080EC0 0007DAA0  38 6D 83 F4 */	addi r3, r13, lbl_804D3A94
/* 80080EC4 0007DAA4  38 80 03 95 */	li r4, 0x395
/* 80080EC8 0007DAA8  48 30 73 59 */	bl __assert
lbl_80080ECC:
/* 80080ECC 0007DAAC  80 7B 00 00 */	lwz r3, 0(r27)
/* 80080ED0 0007DAB0  80 1B 00 04 */	lwz r0, 4(r27)
/* 80080ED4 0007DAB4  90 7F 00 38 */	stw r3, 0x38(r31)
/* 80080ED8 0007DAB8  90 1F 00 3C */	stw r0, 0x3c(r31)
/* 80080EDC 0007DABC  80 1B 00 08 */	lwz r0, 8(r27)
/* 80080EE0 0007DAC0  90 1F 00 40 */	stw r0, 0x40(r31)
/* 80080EE4 0007DAC4  80 1F 00 14 */	lwz r0, 0x14(r31)
/* 80080EE8 0007DAC8  54 00 01 8D */	rlwinm. r0, r0, 0, 6, 6
/* 80080EEC 0007DACC  40 82 00 4C */	bne lbl_80080F38
/* 80080EF0 0007DAD0  28 1F 00 00 */	cmplwi r31, 0
/* 80080EF4 0007DAD4  41 82 00 44 */	beq lbl_80080F38
/* 80080EF8 0007DAD8  40 82 00 14 */	bne lbl_80080F0C
/* 80080EFC 0007DADC  38 6D 83 F4 */	addi r3, r13, lbl_804D3A94
/* 80080F00 0007DAE0  38 80 02 34 */	li r4, 0x234
/* 80080F04 0007DAE4  38 AD 83 FC */	addi r5, r13, lbl_804D3A9C
/* 80080F08 0007DAE8  48 30 73 19 */	bl __assert
lbl_80080F0C:
/* 80080F0C 0007DAEC  80 9F 00 14 */	lwz r4, 0x14(r31)
/* 80080F10 0007DAF0  38 60 00 00 */	li r3, 0
/* 80080F14 0007DAF4  54 80 02 11 */	rlwinm. r0, r4, 0, 8, 8
/* 80080F18 0007DAF8  40 82 00 10 */	bne lbl_80080F28
/* 80080F1C 0007DAFC  54 80 06 73 */	rlwinm. r0, r4, 0, 0x19, 0x19
/* 80080F20 0007DB00  41 82 00 08 */	beq lbl_80080F28
/* 80080F24 0007DB04  38 60 00 01 */	li r3, 1
lbl_80080F28:
/* 80080F28 0007DB08  2C 03 00 00 */	cmpwi r3, 0
/* 80080F2C 0007DB0C  40 82 00 0C */	bne lbl_80080F38
/* 80080F30 0007DB10  7F E3 FB 78 */	mr r3, r31
/* 80080F34 0007DB14  48 2F 23 B5 */	bl HSD_JObjSetMtxDirtySub
lbl_80080F38:
/* 80080F38 0007DB18  80 1E 05 C8 */	lwz r0, 0x5c8(r30)
/* 80080F3C 0007DB1C  28 00 00 00 */	cmplwi r0, 0
/* 80080F40 0007DB20  41 82 01 C4 */	beq lbl_80081104
/* 80080F44 0007DB24  83 7C 00 2C */	lwz r27, 0x2c(r28)
/* 80080F48 0007DB28  88 1B 21 FC */	lbz r0, 0x21fc(r27)
/* 80080F4C 0007DB2C  54 00 07 FF */	clrlwi. r0, r0, 0x1f
/* 80080F50 0007DB30  41 82 00 B4 */	beq lbl_80081004
/* 80080F54 0007DB34  88 7B 22 1E */	lbz r3, 0x221e(r27)
/* 80080F58 0007DB38  54 60 CF FF */	rlwinm. r0, r3, 0x19, 0x1f, 0x1f
/* 80080F5C 0007DB3C  40 82 00 A8 */	bne lbl_80081004
/* 80080F60 0007DB40  54 60 F7 FF */	rlwinm. r0, r3, 0x1e, 0x1f, 0x1f
/* 80080F64 0007DB44  40 82 00 A0 */	bne lbl_80081004
/* 80080F68 0007DB48  88 1B 22 26 */	lbz r0, 0x2226(r27)
/* 80080F6C 0007DB4C  54 00 F7 FF */	rlwinm. r0, r0, 0x1e, 0x1f, 0x1f
/* 80080F70 0007DB50  40 82 00 94 */	bne lbl_80081004
/* 80080F74 0007DB54  38 7B 00 00 */	addi r3, r27, 0
/* 80080F78 0007DB58  38 80 00 00 */	li r4, 0
/* 80080F7C 0007DB5C  38 A0 00 00 */	li r5, 0
/* 80080F80 0007DB60  4B FF 41 49 */	bl func_800750C8
/* 80080F84 0007DB64  38 7B 00 00 */	addi r3, r27, 0
/* 80080F88 0007DB68  38 80 00 01 */	li r4, 1
/* 80080F8C 0007DB6C  38 A0 00 00 */	li r5, 0
/* 80080F90 0007DB70  4B FF 41 39 */	bl func_800750C8
/* 80080F94 0007DB74  38 7B 00 00 */	addi r3, r27, 0
/* 80080F98 0007DB78  38 80 00 02 */	li r4, 2
/* 80080F9C 0007DB7C  38 A0 00 00 */	li r5, 0
/* 80080FA0 0007DB80  4B FF 41 29 */	bl func_800750C8
/* 80080FA4 0007DB84  38 7B 00 00 */	addi r3, r27, 0
/* 80080FA8 0007DB88  38 80 00 04 */	li r4, 4
/* 80080FAC 0007DB8C  38 A0 00 01 */	li r5, 1
/* 80080FB0 0007DB90  4B FF 41 19 */	bl func_800750C8
/* 80080FB4 0007DB94  88 1B 22 23 */	lbz r0, 0x2223(r27)
/* 80080FB8 0007DB98  38 60 00 01 */	li r3, 1
/* 80080FBC 0007DB9C  50 60 2E B4 */	rlwimi r0, r3, 5, 0x1a, 0x1a
/* 80080FC0 0007DBA0  98 1B 22 23 */	stb r0, 0x2223(r27)
/* 80080FC4 0007DBA4  38 80 00 00 */	li r4, 0
/* 80080FC8 0007DBA8  38 7D 00 00 */	addi r3, r29, 0
/* 80080FCC 0007DBAC  88 1B 22 23 */	lbz r0, 0x2223(r27)
/* 80080FD0 0007DBB0  50 80 26 F6 */	rlwimi r0, r4, 4, 0x1b, 0x1b
/* 80080FD4 0007DBB4  98 1B 22 23 */	stb r0, 0x2223(r27)
/* 80080FD8 0007DBB8  83 7C 00 28 */	lwz r27, 0x28(r28)
/* 80080FDC 0007DBBC  48 30 FE DD */	bl func_80390EB8
/* 80080FE0 0007DBC0  3B C3 00 00 */	addi r30, r3, 0
/* 80080FE4 0007DBC4  38 7C 00 00 */	addi r3, r28, 0
/* 80080FE8 0007DBC8  38 81 00 54 */	addi r4, r1, 0x54
/* 80080FEC 0007DBCC  4B FF F5 31 */	bl func_8008051C
/* 80080FF0 0007DBD0  38 83 00 00 */	addi r4, r3, 0
/* 80080FF4 0007DBD4  38 7B 00 00 */	addi r3, r27, 0
/* 80080FF8 0007DBD8  38 BE 00 00 */	addi r5, r30, 0
/* 80080FFC 0007DBDC  38 C0 00 00 */	li r6, 0
/* 80081000 0007DBE0  48 2E F9 DD */	bl HSD_JObjDispAll
lbl_80081004:
/* 80081004 0007DBE4  38 7C 00 00 */	addi r3, r28, 0
/* 80081008 0007DBE8  38 9D 00 00 */	addi r4, r29, 0
/* 8008100C 0007DBEC  38 A0 00 01 */	li r5, 1
/* 80081010 0007DBF0  4B FF F5 B9 */	bl func_800805C8
/* 80081014 0007DBF4  83 7C 00 2C */	lwz r27, 0x2c(r28)
/* 80081018 0007DBF8  88 1B 21 FC */	lbz r0, 0x21fc(r27)
/* 8008101C 0007DBFC  54 00 07 FF */	clrlwi. r0, r0, 0x1f
/* 80081020 0007DC00  41 82 00 E4 */	beq lbl_80081104
/* 80081024 0007DC04  88 7B 22 1E */	lbz r3, 0x221e(r27)
/* 80081028 0007DC08  54 60 CF FF */	rlwinm. r0, r3, 0x19, 0x1f, 0x1f
/* 8008102C 0007DC0C  40 82 00 D8 */	bne lbl_80081104
/* 80081030 0007DC10  54 60 F7 FF */	rlwinm. r0, r3, 0x1e, 0x1f, 0x1f
/* 80081034 0007DC14  40 82 00 D0 */	bne lbl_80081104
/* 80081038 0007DC18  88 1B 22 26 */	lbz r0, 0x2226(r27)
/* 8008103C 0007DC1C  54 00 F7 FF */	rlwinm. r0, r0, 0x1e, 0x1f, 0x1f
/* 80081040 0007DC20  40 82 00 C4 */	bne lbl_80081104
/* 80081044 0007DC24  38 7B 00 00 */	addi r3, r27, 0
/* 80081048 0007DC28  38 80 00 00 */	li r4, 0
/* 8008104C 0007DC2C  38 A0 00 00 */	li r5, 0
/* 80081050 0007DC30  4B FF 40 79 */	bl func_800750C8
/* 80081054 0007DC34  38 7B 00 00 */	addi r3, r27, 0
/* 80081058 0007DC38  38 80 00 01 */	li r4, 1
/* 8008105C 0007DC3C  38 A0 00 00 */	li r5, 0
/* 80081060 0007DC40  4B FF 40 69 */	bl func_800750C8
/* 80081064 0007DC44  38 7B 00 00 */	addi r3, r27, 0
/* 80081068 0007DC48  38 80 00 02 */	li r4, 2
/* 8008106C 0007DC4C  38 A0 00 00 */	li r5, 0
/* 80081070 0007DC50  4B FF 40 59 */	bl func_800750C8
/* 80081074 0007DC54  38 7B 00 00 */	addi r3, r27, 0
/* 80081078 0007DC58  38 80 00 04 */	li r4, 4
/* 8008107C 0007DC5C  38 A0 00 01 */	li r5, 1
/* 80081080 0007DC60  4B FF 40 49 */	bl func_800750C8
/* 80081084 0007DC64  88 1B 22 23 */	lbz r0, 0x2223(r27)
/* 80081088 0007DC68  38 80 00 01 */	li r4, 1
/* 8008108C 0007DC6C  50 80 2E B4 */	rlwimi r0, r4, 5, 0x1a, 0x1a
/* 80081090 0007DC70  98 1B 22 23 */	stb r0, 0x2223(r27)
/* 80081094 0007DC74  7F A3 EB 78 */	mr r3, r29
/* 80081098 0007DC78  88 1B 22 23 */	lbz r0, 0x2223(r27)
/* 8008109C 0007DC7C  50 80 26 F6 */	rlwimi r0, r4, 4, 0x1b, 0x1b
/* 800810A0 0007DC80  98 1B 22 23 */	stb r0, 0x2223(r27)
/* 800810A4 0007DC84  83 7C 00 28 */	lwz r27, 0x28(r28)
/* 800810A8 0007DC88  48 30 FE 11 */	bl func_80390EB8
/* 800810AC 0007DC8C  3B A3 00 00 */	addi r29, r3, 0
/* 800810B0 0007DC90  38 7C 00 00 */	addi r3, r28, 0
/* 800810B4 0007DC94  38 81 00 24 */	addi r4, r1, 0x24
/* 800810B8 0007DC98  4B FF F4 65 */	bl func_8008051C
/* 800810BC 0007DC9C  38 83 00 00 */	addi r4, r3, 0
/* 800810C0 0007DCA0  38 7B 00 00 */	addi r3, r27, 0
/* 800810C4 0007DCA4  38 BD 00 00 */	addi r5, r29, 0
/* 800810C8 0007DCA8  38 C0 00 00 */	li r6, 0
/* 800810CC 0007DCAC  48 2E F9 11 */	bl HSD_JObjDispAll
/* 800810D0 0007DCB0  48 00 00 34 */	b lbl_80081104
lbl_800810D4:
/* 800810D4 0007DCB4  88 1E 22 23 */	lbz r0, 0x2223(r30)
/* 800810D8 0007DCB8  38 A0 00 00 */	li r5, 0
/* 800810DC 0007DCBC  50 A0 26 F6 */	rlwimi r0, r5, 4, 0x1b, 0x1b
/* 800810E0 0007DCC0  98 1E 22 23 */	stb r0, 0x2223(r30)
/* 800810E4 0007DCC4  80 1E 05 C8 */	lwz r0, 0x5c8(r30)
/* 800810E8 0007DCC8  28 00 00 00 */	cmplwi r0, 0
/* 800810EC 0007DCCC  41 82 00 08 */	beq lbl_800810F4
/* 800810F0 0007DCD0  48 00 00 08 */	b lbl_800810F8
lbl_800810F4:
/* 800810F4 0007DCD4  38 A0 00 01 */	li r5, 1
lbl_800810F8:
/* 800810F8 0007DCD8  38 7C 00 00 */	addi r3, r28, 0
/* 800810FC 0007DCDC  38 9D 00 00 */	addi r4, r29, 0
/* 80081100 0007DCE0  4B FF F4 C9 */	bl func_800805C8
lbl_80081104:
/* 80081104 0007DCE4  BB 61 00 8C */	lmw r27, 0x8c(r1)
/* 80081108 0007DCE8  80 01 00 A4 */	lwz r0, 0xa4(r1)
/* 8008110C 0007DCEC  38 21 00 A0 */	addi r1, r1, 0xa0
/* 80081110 0007DCF0  7C 08 03 A6 */	mtlr r0
/* 80081114 0007DCF4  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

#pragma push
asm unk_t func_80081118()
{ // clang-format off
    nofralloc
/* 80081118 0007DCF8  80 8D C1 8C */	lwz r4, lbl_804D782C(r13)
/* 8008111C 0007DCFC  3C 60 80 08 */	lis r3, func_80080E18@ha
/* 80081120 0007DD00  38 03 0E 18 */	addi r0, r3, func_80080E18@l
/* 80081124 0007DD04  80 64 00 20 */	lwz r3, 0x20(r4)
/* 80081128 0007DD08  48 00 00 0C */	b lbl_80081134
lbl_8008112C:
/* 8008112C 0007DD0C  90 03 00 1C */	stw r0, 0x1c(r3)
/* 80081130 0007DD10  80 63 00 08 */	lwz r3, 8(r3)
lbl_80081134:
/* 80081134 0007DD14  28 03 00 00 */	cmplwi r3, 0
/* 80081138 0007DD18  40 82 FF F4 */	bne lbl_8008112C
/* 8008113C 0007DD1C  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

#pragma push
asm unk_t func_80081140()
{ // clang-format off
    nofralloc
/* 80081140 0007DD20  80 8D C1 8C */	lwz r4, lbl_804D782C(r13)
/* 80081144 0007DD24  3C 60 80 08 */	lis r3, func_80080C28@ha
/* 80081148 0007DD28  38 03 0C 28 */	addi r0, r3, func_80080C28@l
/* 8008114C 0007DD2C  80 64 00 20 */	lwz r3, 0x20(r4)
/* 80081150 0007DD30  48 00 00 0C */	b lbl_8008115C
lbl_80081154:
/* 80081154 0007DD34  90 03 00 1C */	stw r0, 0x1c(r3)
/* 80081158 0007DD38  80 63 00 08 */	lwz r3, 8(r3)
lbl_8008115C:
/* 8008115C 0007DD3C  28 03 00 00 */	cmplwi r3, 0
/* 80081160 0007DD40  40 82 FF F4 */	bne lbl_80081154
/* 80081164 0007DD44  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

#pragma push
asm unk_t func_80081168()
{ // clang-format off
    nofralloc
/* 80081168 0007DD48  7C 08 02 A6 */	mflr r0
/* 8008116C 0007DD4C  90 01 00 04 */	stw r0, 4(r1)
/* 80081170 0007DD50  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 80081174 0007DD54  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 80081178 0007DD58  93 C1 00 18 */	stw r30, 0x18(r1)
/* 8008117C 0007DD5C  80 6D C1 8C */	lwz r3, lbl_804D782C(r13)
/* 80081180 0007DD60  83 E3 00 20 */	lwz r31, 0x20(r3)
/* 80081184 0007DD64  48 00 00 5C */	b lbl_800811E0
lbl_80081188:
/* 80081188 0007DD68  80 7F 00 2C */	lwz r3, 0x2c(r31)
/* 8008118C 0007DD6C  80 03 05 BC */	lwz r0, 0x5bc(r3)
/* 80081190 0007DD70  3B C3 00 00 */	addi r30, r3, 0
/* 80081194 0007DD74  28 00 00 00 */	cmplwi r0, 0
/* 80081198 0007DD78  41 82 00 44 */	beq lbl_800811DC
/* 8008119C 0007DD7C  38 7E 00 00 */	addi r3, r30, 0
/* 800811A0 0007DD80  38 80 00 01 */	li r4, 1
/* 800811A4 0007DD84  38 A0 00 00 */	li r5, 0
/* 800811A8 0007DD88  4B FF 3F 21 */	bl func_800750C8
/* 800811AC 0007DD8C  38 7E 00 00 */	addi r3, r30, 0
/* 800811B0 0007DD90  38 80 00 02 */	li r4, 2
/* 800811B4 0007DD94  38 A0 00 00 */	li r5, 0
/* 800811B8 0007DD98  4B FF 3F 11 */	bl func_800750C8
/* 800811BC 0007DD9C  38 7E 00 00 */	addi r3, r30, 0
/* 800811C0 0007DDA0  38 80 00 04 */	li r4, 4
/* 800811C4 0007DDA4  38 A0 00 00 */	li r5, 0
/* 800811C8 0007DDA8  4B FF 3F 01 */	bl func_800750C8
/* 800811CC 0007DDAC  38 7E 00 00 */	addi r3, r30, 0
/* 800811D0 0007DDB0  38 80 00 00 */	li r4, 0
/* 800811D4 0007DDB4  38 A0 00 01 */	li r5, 1
/* 800811D8 0007DDB8  4B FF 3E F1 */	bl func_800750C8
lbl_800811DC:
/* 800811DC 0007DDBC  83 FF 00 08 */	lwz r31, 8(r31)
lbl_800811E0:
/* 800811E0 0007DDC0  28 1F 00 00 */	cmplwi r31, 0
/* 800811E4 0007DDC4  40 82 FF A4 */	bne lbl_80081188
/* 800811E8 0007DDC8  80 01 00 24 */	lwz r0, 0x24(r1)
/* 800811EC 0007DDCC  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 800811F0 0007DDD0  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 800811F4 0007DDD4  38 21 00 20 */	addi r1, r1, 0x20
/* 800811F8 0007DDD8  7C 08 03 A6 */	mtlr r0
/* 800811FC 0007DDDC  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

#pragma push
asm unk_t func_80081200()
{ // clang-format off
    nofralloc
/* 80081200 0007DDE0  7C 08 02 A6 */	mflr r0
/* 80081204 0007DDE4  90 01 00 04 */	stw r0, 4(r1)
/* 80081208 0007DDE8  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 8008120C 0007DDEC  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 80081210 0007DDF0  93 C1 00 18 */	stw r30, 0x18(r1)
/* 80081214 0007DDF4  80 6D C1 8C */	lwz r3, lbl_804D782C(r13)
/* 80081218 0007DDF8  83 E3 00 20 */	lwz r31, 0x20(r3)
/* 8008121C 0007DDFC  48 00 00 5C */	b lbl_80081278
lbl_80081220:
/* 80081220 0007DE00  80 7F 00 2C */	lwz r3, 0x2c(r31)
/* 80081224 0007DE04  80 03 05 BC */	lwz r0, 0x5bc(r3)
/* 80081228 0007DE08  3B C3 00 00 */	addi r30, r3, 0
/* 8008122C 0007DE0C  28 00 00 00 */	cmplwi r0, 0
/* 80081230 0007DE10  41 82 00 44 */	beq lbl_80081274
/* 80081234 0007DE14  38 7E 00 00 */	addi r3, r30, 0
/* 80081238 0007DE18  38 80 00 00 */	li r4, 0
/* 8008123C 0007DE1C  38 A0 00 00 */	li r5, 0
/* 80081240 0007DE20  4B FF 3E 89 */	bl func_800750C8
/* 80081244 0007DE24  38 7E 00 00 */	addi r3, r30, 0
/* 80081248 0007DE28  38 80 00 02 */	li r4, 2
/* 8008124C 0007DE2C  38 A0 00 00 */	li r5, 0
/* 80081250 0007DE30  4B FF 3E 79 */	bl func_800750C8
/* 80081254 0007DE34  38 7E 00 00 */	addi r3, r30, 0
/* 80081258 0007DE38  38 80 00 04 */	li r4, 4
/* 8008125C 0007DE3C  38 A0 00 00 */	li r5, 0
/* 80081260 0007DE40  4B FF 3E 69 */	bl func_800750C8
/* 80081264 0007DE44  38 7E 00 00 */	addi r3, r30, 0
/* 80081268 0007DE48  38 80 00 01 */	li r4, 1
/* 8008126C 0007DE4C  38 A0 00 01 */	li r5, 1
/* 80081270 0007DE50  4B FF 3E 59 */	bl func_800750C8
lbl_80081274:
/* 80081274 0007DE54  83 FF 00 08 */	lwz r31, 8(r31)
lbl_80081278:
/* 80081278 0007DE58  28 1F 00 00 */	cmplwi r31, 0
/* 8008127C 0007DE5C  40 82 FF A4 */	bne lbl_80081220
/* 80081280 0007DE60  80 01 00 24 */	lwz r0, 0x24(r1)
/* 80081284 0007DE64  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 80081288 0007DE68  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 8008128C 0007DE6C  38 21 00 20 */	addi r1, r1, 0x20
/* 80081290 0007DE70  7C 08 03 A6 */	mtlr r0
/* 80081294 0007DE74  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop
