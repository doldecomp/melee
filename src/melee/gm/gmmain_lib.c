#include <melee/gm/gmmain_lib.h>
#include <melee/lb/lbtime.h>

void* func_8015CC34(void) {
    return &lbl_804D3EE0->x1850;
}

void* func_8015CC40(void) {
    return &lbl_804D3EE0->thing.x1868;
}

void* func_8015CC4C(void) {
    return &lbl_804D3EE0->thing.x2FF8;
}

struct gmm_x1CB0 *func_8015CC58(void) {
    return &lbl_804D3EE0->thing.x1CB0;
}

void* func_8015CC64(s32 arg0) {
    struct gmm_x1F2C *base = &lbl_804D3EE0->thing.x1F2C[0];
    return &base[arg0];
}

void* func_8015CC78(void) {
    return &lbl_804D3EE0->thing.x1CD4;
}

void* func_8015CC84(void) {
    return &lbl_804D3EE0->thing.x1CD2;
}

void* func_8015CC90(void) {
    return &lbl_804D3EE0->thing.x1CD0;
}

void* func_8015CC9C(s32 arg0) {
    struct gmm_x2FF8 *base = &lbl_804D3EE0->thing.x2FF8[0];
    struct gmm_x2FF8_inner *inner = &base[arg0/19].inner[0];
    return &inner[arg0 % 19];
}

void* func_8015CCE4(void) {
    return &lbl_804D3EE0->x44;
}

void* func_8015CCF0(void) {
    return &lbl_804D3EE0->thing.x1A48;
}

void* func_8015CCFC(void) {
    return &lbl_804D3EE0->thing.x1A4C;
}

void* func_8015CD08(void) {
    return &lbl_804D3EE0->thing.x1A30;
}

void* func_8015CD14(void) {
    return &lbl_804D3EE0->thing.x1A34;
}

void* func_8015CD20(void) {
    return &lbl_804D3EE0->thing.x1A38;
}

void* func_8015CD2C(void) {
    return &lbl_804D3EE0->thing.x1A18;
}

void* func_8015CD38(void) {
    return &lbl_804D3EE0->thing.x1A1C;
}

void* func_8015CD44(void) {
    return &lbl_804D3EE0->thing.x1A20;
}

void* func_8015CD50(void) {
    return &lbl_804D3EE0->thing.x1A24;
}

void* func_8015CD5C(void) {
    return &lbl_804D3EE0->thing.x1A28;
}

void* func_8015CD68(void) {
    return &lbl_804D3EE0->thing.x1A2C;
}

void* func_8015CD74(void) {
    return &lbl_804D3EE0->thing.x1A3C;
}

void* func_8015CD80(void) {
    return &lbl_804D3EE0->thing.x1A44;
}

void* func_8015CD8C(void) {
    return &lbl_804D3EE0->thing.x1A50;
}

void* func_8015CD98(void) {
    return &lbl_804D3EE0->thing.x1A54;
}

void* func_8015CDA4(void) {
    return &lbl_804D3EE0->thing.x1A58;
}

void* func_8015CDB0(void) {
    return &lbl_804D3EE0->thing.x1A5C;
}

void* func_8015CDBC(void) {
    return &lbl_804D3EE0->thing.x1A60;
}

void* func_8015CDC8(void) {
    return &lbl_804D3EE0->x51C;
}

void* func_8015CDD4(void) {
    return &lbl_804D3EE0->x522;
}

void* func_8015CDE0(void) {
    return &lbl_804D3EE0->x528;
}

void func_8015CDEC(void) {
    s32 i;
    for (i = 0; i < 6; ++i) {
        s8* ptr = func_8015CE44(i, 0x78);
        if (ptr != 0) {
            *ptr = 5;
        }
    }
}

s8* func_8015CE44(s32 arg0, s32 arg1) {
    if (arg1 == 0x78) {
        if (arg0 < 4) {
            return &lbl_804D3EE0->x588[arg0];
        }
        return 0;
    } else {
        struct gmm_x2FF8 *base = &lbl_804D3EE0->thing.x2FF8[0];
        struct gmm_x2FF8_inner *inner = &base[arg1/19].inner[0];
        return &inner[arg1%19].x1A2;
    }
}

void func_8015CEB4(s32 arg0) {
    lbl_804D3EE0->thing.x1A68 |= (1LL << arg0);
}

s32 func_8015CEFC(s32 arg0) {
    if (lbl_804D3EE0->thing.x1A68 & (1LL << arg0)) {
        return 1;
    } else {
        return 0;
    }
}

s32 func_8015CF5C(s32 arg0) {
    return lbl_804D3EE0->thing.x1A70[arg0];
}

void func_8015CF70(s32 arg0, s32 arg1) {
    lbl_804D3EE0->thing.x1A70[arg0] = arg1;
}

void func_8015CF84(void) {
    lbl_804D3EE0->thing.x1B3C = 1;
}

s32 func_8015CF94(void) {
    if (lbl_804D3EE0->thing.x1B3C) {
        return 1;
    }
    return 0;
}

s32 func_8015CFAC(void) {
    return 0;
}

s8* func_8015CFB4(u8 arg0) {
    struct gmm_x1F2C *base = &lbl_804D3EE0->thing.x1F2C[0];
    return &base[arg0].x78;
}

s32 func_8015CFCC(u8 arg0) {
    return (1 << arg0) & func_8015ED98()->xC;
}

void func_8015D00C(u8 arg0) {
    s32 unused[3];
    struct gmm_x1F2C *base = &lbl_804D3EE0->thing.x1F2C[0];
    base[arg0].x7A.bits.b0 = 1;
    func_8015ED98()->xC |= 1 << arg0;
}

s32* func_8015D06C(u8 arg0) {
    struct gmm_x1F2C *base = &lbl_804D3EE0->thing.x1F2C[0];
    return &base[arg0].x84;
}

#ifdef NON_MATCHING
// needs a @frank patch
s32* func_8015D084(s32 arg0) {
    return &func_8015EDBC()->xB0[arg0 & 0xFF];
}
#else
asm s32* func_8015D084(s32 arg0) {
    nofralloc
/* 8015D084 00159C64  7C 08 02 A6 */	mflr r0
/* 8015D088 00159C68  90 01 00 04 */	stw r0, 4(r1)
/* 8015D08C 00159C6C  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 8015D090 00159C70  93 E1 00 14 */	stw r31, 0x14(r1)
/* 8015D094 00159C74  7C 7F 1B 78 */	mr r31, r3
/* 8015D098 00159C78  48 00 1D 25 */	bl func_8015EDBC
/* 8015D09C 00159C7C  57 E4 15 BA */	rlwinm r4, r31, 2, 0x16, 0x1d
/* 8015D0A0 00159C80  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 8015D0A4 00159C84  38 03 00 00 */	addi r0, r3, 0
/* 8015D0A8 00159C88  38 64 00 B0 */	addi r3, r4, 0xb0
/* 8015D0AC 00159C8C  7C 60 1A 14 */	add r3, r0, r3
/* 8015D0B0 00159C90  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 8015D0B4 00159C94  38 21 00 18 */	addi r1, r1, 0x18
/* 8015D0B8 00159C98  7C 08 03 A6 */	mtlr r0
/* 8015D0BC 00159C9C  4E 80 00 20 */	blr
}
#pragma peephole on
#endif

s32* func_8015D0C0(u8 arg0) {
    struct gmm_x1F2C *base = &lbl_804D3EE0->thing.x1F2C[0];
    return &base[arg0].x88;
}

s32 func_8015D0D8(u8 arg0) {
    struct gmm_x1F2C *base = &lbl_804D3EE0->thing.x1F2C[0];
    return base[arg0].x7C.bits.b4;
}

s32 func_8015D0F4(u8 arg0) {
    s32 x10 = func_8015ED98()->x10;
    return x10 & (1 << arg0);
}

void func_8015D134(u8 arg0) {
    s32 unused[3];
    struct gmm_x1F2C *base = &lbl_804D3EE0->thing.x1F2C[0];
    base[arg0].x7C.bits.b4 = 1;
    func_8015ED98()->x10 |= 1 << arg0;
}

s8* func_8015D194(u8 arg0) {
    struct gmm_x1F2C *base = &lbl_804D3EE0->thing.x1F2C[0];
    return &base[arg0].x80;
}

s32 func_8015D1AC(u8 arg0) {
    struct gmm_x1F2C *base = &lbl_804D3EE0->thing.x1F2C[0];
    return base[arg0].x7C.bits.b789;
}

void func_8015D1C8(u8 arg0, s32 arg1) {
    struct gmm_x1F2C *base = &lbl_804D3EE0->thing.x1F2C[0];
    base[arg0].x7C.bits.b789 = arg1;
}

s32* func_8015D1E8(u8 arg0) {
    struct gmm_x1F2C *base = &lbl_804D3EE0->thing.x1F2C[0];
    return &base[arg0].x8C;
}

s32 func_8015D200(u8 arg0) {
    struct gmm_x1F2C *base = &lbl_804D3EE0->thing.x1F2C[0];
    return base[arg0].x7C.bits.b5;
}

s32 func_8015D21C(u8 arg0) {
    s32 x14 = func_8015ED98()->x14;
    return x14 & (1 << arg0);
}

void func_8015D25C(u8 arg0) {
    s32 unused[3];
    struct gmm_x1F2C *base = &lbl_804D3EE0->thing.x1F2C[0];
    base[arg0].x7C.bits.b5 = 1;
    func_8015ED98()->x14 |= 1 << arg0;
}

s8* func_8015D2BC(u8 arg0) {
    struct gmm_x1F2C *base = &lbl_804D3EE0->thing.x1F2C[0];
    return &base[arg0].x81;
}

s32 func_8015D2D4(u8 arg0) {
    struct gmm_x1F2C *base = &lbl_804D3EE0->thing.x1F2C[0];
    return base[arg0].x7C.bits.b10_to_12;
}

void func_8015D2F0(u8 arg0, s32 arg1) {
    struct gmm_x1F2C *base = &lbl_804D3EE0->thing.x1F2C[0];
    base[arg0].x7C.bits.b10_to_12 = arg1;
}

s32* func_8015D310(u8 arg0) {
    struct gmm_x1F2C *base = &lbl_804D3EE0->thing.x1F2C[0];
    return &base[arg0].x90;
}

s32 func_8015D328(u8 arg0) {
    struct gmm_x1F2C *base = &lbl_804D3EE0->thing.x1F2C[0];
    return base[arg0].x7C.bits.b6;
}

s32 func_8015D344(u8 arg0) {
    s32 x18 = func_8015ED98()->x18;
    return x18 & (1 << arg0);
}

void func_8015D384(u8 arg0) {
    s32 unused[3];
    struct gmm_x1F2C *base = &lbl_804D3EE0->thing.x1F2C[0];
    base[arg0].x7C.bits.b6 = 1;
    func_8015ED98()->x18 |= 1 << arg0;
}

s8* func_8015D3E4(u8 arg0) {
    struct gmm_x1F2C *base = &lbl_804D3EE0->thing.x1F2C[0];
    return &base[arg0].x82;
}

s32 func_8015D3FC(u8 arg0) {
    struct gmm_x1F2C *base = &lbl_804D3EE0->thing.x1F2C[0];
    return base[arg0].x7C.bits.b13_to_15;
}

void func_8015D418(u8 arg0, s32 arg1) {
    struct gmm_x1F2C *base = &lbl_804D3EE0->thing.x1F2C[0];
    base[arg0].x7C.bits.b13_to_15 = arg1;
}

s32* func_8015D438(u8 arg0) {
    struct gmm_x1F2C *base = &lbl_804D3EE0->thing.x1F2C[0];
    return &base[arg0].x94;
}

#ifdef NON_MATCHING
// needs a @frank patch
s32* func_8015D450(s32 arg0) {
    return &func_8015EDBC()->x4C[arg0 & 255];
}
#else
asm s32* func_8015D450(s32 arg0) {
    nofralloc
/* 8015D450 0015A030  7C 08 02 A6 */	mflr r0
/* 8015D454 0015A034  90 01 00 04 */	stw r0, 4(r1)
/* 8015D458 0015A038  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 8015D45C 0015A03C  93 E1 00 14 */	stw r31, 0x14(r1)
/* 8015D460 0015A040  7C 7F 1B 78 */	mr r31, r3
/* 8015D464 0015A044  48 00 19 59 */	bl func_8015EDBC
/* 8015D468 0015A048  57 E4 15 BA */	rlwinm r4, r31, 2, 0x16, 0x1d
/* 8015D46C 0015A04C  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 8015D470 0015A050  38 03 00 00 */	addi r0, r3, 0
/* 8015D474 0015A054  38 64 00 4C */	addi r3, r4, 0x4c
/* 8015D478 0015A058  7C 60 1A 14 */	add r3, r0, r3
/* 8015D47C 0015A05C  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 8015D480 0015A060  38 21 00 18 */	addi r1, r1, 0x18
/* 8015D484 0015A064  7C 08 03 A6 */	mtlr r0
/* 8015D488 0015A068  4E 80 00 20 */	blr 
}
#pragma peephole on
#endif

s32 func_8015D48C(u8 arg0) {
    struct gmm_x1F2C *base = &lbl_804D3EE0->thing.x1F2C[0];
    return base[arg0].x7C.bits.b0;
}

s32 func_8015D4A8(u8 arg0) {
    s32 x1C = func_8015ED98()->x1C;
    return x1C & (1 << arg0);
}

void func_8015D4E8(u8 arg0, s32 arg1) {
    struct gmm_x1F2C *base = &lbl_804D3EE0->thing.x1F2C[0];
    base[arg0].x7C.bits.b0 = arg1;
}

s32 lbl_8015D508(void) {
    struct gmm_x1868 *base = &lbl_804D3EE0->thing;
    s32 i;
    for (i = 0; i < 25; ++i) {
        struct gmm_x1F2C* _x1F2C = base->x1F2C;
        if (_x1F2C[(u8)i].x7C.bits.b0 == 0) {
            return 0;
        }
    }
    return 1;
}

s32 func_8015D5DC(void) {
    s32 i;
    for (i = 0; i < 0x19; i++) {
        s32 j = func_8015EDB0()->x4;
        s32 k = 1 << (u8)i;
        if ((j & k) == 0) {
            return 0;
        }
    }
    return 1;
}

s32 func_8015D640(void) {
    s32 i;
    for (i = 0; i < 0x19; i++) {
        s32 j = func_8015EDBC()->x8;
        s32 k = 1 << (u8)i;
        if ((j & k) == 0) {
            return 0;
        }
    }
    return 1;
}

s32* func_8015D6A4(u8 arg0) {
    struct gmm_x1F2C *base = &lbl_804D3EE0->thing.x1F2C[0];
    return &base[arg0].x98;
}

s32 func_8015D6BC(u8 arg0) {
    struct gmm_x1F2C *base = &lbl_804D3EE0->thing.x1F2C[0];
    return base[arg0].x7C.bits.b1;
}

void func_8015D6D8(u8 arg0, s32 arg1) {
    struct gmm_x1F2C *base = &lbl_804D3EE0->thing.x1F2C[0];
    base[arg0].x7C.bits.b1 = arg1;
}

s32* func_8015D6F8(u8 arg0) {
    struct gmm_x1F2C *base = &lbl_804D3EE0->thing.x1F2C[0];
    return &base[arg0].x9C;
}

s32 func_8015D710(u8 arg0) {
    struct gmm_x1F2C *base = &lbl_804D3EE0->thing.x1F2C[0];
    return base[arg0].x7C.bits.b2;
}

void func_8015D72C(u8 arg0, s32 arg1) {
    struct gmm_x1F2C *base = &lbl_804D3EE0->thing.x1F2C[0];
    base[arg0].x7C.bits.b2 = arg1;
}

s16* func_8015D74C(u8 arg0) {
    struct gmm_x1F2C *base = &lbl_804D3EE0->thing.x1F2C[0];
    return &base[arg0].xA0;
}

s32 func_8015D764(u8 arg0) {
    struct gmm_x1F2C *base = &lbl_804D3EE0->thing.x1F2C[0];
    return base[arg0].x7C.bits.b3;
}

void func_8015D780(u8 arg0) {
    struct gmm_x1F2C *base = &lbl_804D3EE0->thing.x1F2C[0];
    base[arg0].x7C.bits.b3 = 1;
}

s16* func_8015D7A4(u8 arg0) {
    struct gmm_x1F2C *base = &lbl_804D3EE0->thing.x1F2C[0];
    return &base[arg0].xA2;
}

s32* func_8015D7BC(u8 arg0) {
    struct gmm_x1F2C *base = &lbl_804D3EE0->thing.x1F2C[0];
    return &base[arg0].xA4;
}

s32* func_8015D7D4(u8 arg0) {
    struct gmm_x1F2C *base = &lbl_804D3EE0->thing.x1F2C[0];
    return &base[arg0].xA8;
}

s16* func_8015D7EC(u8 arg0) {
    struct gmm_x1F2C *base = &lbl_804D3EE0->thing.x1F2C[0];
    return &base[arg0].x7E;
}

void* func_8015D804(s32 arg0) {
    struct gmm_x1868 *thing = &lbl_804D3EE0->thing;
    return &thing->x1B80[arg0];
}

s32 func_8015D818(u32 arg0) {
    s32 unused[10];
    if (func_8015D94C(arg0) == 0) {
        struct gmm_x1868 *base = &lbl_804D3EE0->thing;
        u32 *q = &base->x1B80[arg0];
        *q = func_8000AFBC();
        func_8015D888(arg0);
        func_8015D8FC(arg0);
        return 1;
    }
    return 0;
}

void func_8015D888(u32 arg0) {
    u32 *thing = &lbl_804D3EE0->thing.x1B40[0];
    thing[arg0 / 32] |= (1 << (arg0 % 32));
}

void func_8015D8B0(u32 arg0) {
    u32 *thing = &lbl_804D3EE0->thing.x1B40[0];
    thing[arg0 / 32] &= ~(1 << (arg0 % 32));
}

s32 func_8015D8D8(u32 arg0) {
    u32 *thing = &lbl_804D3EE0->thing.x1B40[0];
    return thing[arg0 / 32] & (1 << (arg0 % 32));
}

void func_8015D8FC(u32 arg0) {
    u32 *thing = &lbl_804D3EE0->thing.x1B4C[0];
    thing[arg0 / 32] |= (1 << (arg0 % 32));
}

void func_8015D924(u32 arg0) {
    u32 *thing = &lbl_804D3EE0->thing.x1B4C[0];
    thing[arg0 / 32] &= ~(1 << (arg0 % 32));
}

s32 func_8015D94C(u32 arg0) {
    u32 *thing = &lbl_804D3EE0->thing.x1B4C[0];
    u32 flag = thing[arg0 / 32];
    return flag & (1 << (arg0 % 32));
}

s32* func_8015D970(s32 arg0) {
    s32 *base = &lbl_804D3EE0->x6C[0];
    return &base[arg0];
}

s32 func_8015DA90(u32 arg0);
void func_8015D9F4(u32 arg0);
void func_8015DA40(u32 arg0);
#ifdef NON_MATCHING
// https://decomp.me/scratch/CJy8X
// register swap
s32 func_8015D984(s32 arg0) {
    s32 unused[4];
    if (func_8015DA90(arg0) == 0) {
        s32 *base = &lbl_804D3EE0->x6C[0];
        s32 *qwe = &base[arg0];
        *qwe = func_8000AFBC();

        func_8015D9F4(arg0);
        func_8015DA40(arg0);
        return 1;
    }
    return 0;
}
#else
asm s32 func_8015D984(s32 arg0) {
    nofralloc
/* 8015D984 0015A564  7C 08 02 A6 */	mflr r0
/* 8015D988 0015A568  90 01 00 04 */	stw r0, 4(r1)
/* 8015D98C 0015A56C  94 21 FF D8 */	stwu r1, -0x28(r1)
/* 8015D990 0015A570  93 E1 00 24 */	stw r31, 0x24(r1)
/* 8015D994 0015A574  93 C1 00 20 */	stw r30, 0x20(r1)
/* 8015D998 0015A578  7C 7E 1B 78 */	mr r30, r3
/* 8015D99C 0015A57C  48 00 00 F5 */	bl func_8015DA90
/* 8015D9A0 0015A580  2C 03 00 00 */	cmpwi r3, 0
/* 8015D9A4 0015A584  40 82 00 34 */	bne lbl_8015D9D8
/* 8015D9A8 0015A588  80 6D 88 40 */	lwz r3, lbl_804D3EE0
/* 8015D9AC 0015A58C  57 C0 10 3A */	slwi r0, r30, 2
/* 8015D9B0 0015A590  7C 63 02 14 */	add r3, r3, r0
/* 8015D9B4 0015A594  3B E3 00 6C */	addi r31, r3, 0x6c
/* 8015D9B8 0015A598  4B EA D6 05 */	bl func_8000AFBC
/* 8015D9BC 0015A59C  90 7F 00 00 */	stw r3, 0(r31)
/* 8015D9C0 0015A5A0  7F C3 F3 78 */	mr r3, r30
/* 8015D9C4 0015A5A4  48 00 00 31 */	bl func_8015D9F4
/* 8015D9C8 0015A5A8  7F C3 F3 78 */	mr r3, r30
/* 8015D9CC 0015A5AC  48 00 00 75 */	bl func_8015DA40
/* 8015D9D0 0015A5B0  38 60 00 01 */	li r3, 1
/* 8015D9D4 0015A5B4  48 00 00 08 */	b lbl_8015D9DC
lbl_8015D9D8:
/* 8015D9D8 0015A5B8  38 60 00 00 */	li r3, 0
lbl_8015D9DC:
/* 8015D9DC 0015A5BC  80 01 00 2C */	lwz r0, 0x2c(r1)
/* 8015D9E0 0015A5C0  83 E1 00 24 */	lwz r31, 0x24(r1)
/* 8015D9E4 0015A5C4  83 C1 00 20 */	lwz r30, 0x20(r1)
/* 8015D9E8 0015A5C8  38 21 00 28 */	addi r1, r1, 0x28
/* 8015D9EC 0015A5CC  7C 08 03 A6 */	mtlr r0
/* 8015D9F0 0015A5D0  4E 80 00 20 */	blr
}
#pragma peephole on
#endif

void func_8015D9F4(u32 arg0) {
    s32 *base = &lbl_804D3EE0->x44;
    base[arg0 / 32] |= (1 << (arg0 % 32));
}

s32 func_8015DA1C(u32 arg0) {
    s32 *base = &lbl_804D3EE0->x44;
    return (1 << (arg0 % 32)) & base[arg0 / 32];
}

void func_8015DA40(u32 arg0) {
    u32 *base = &lbl_804D3EE0->thing.x1B58[0];
    base[arg0 / 32] |= (1 << (arg0 % 32));
}

void func_8015DA68(u32 arg0) {
    u32 *base = &lbl_804D3EE0->thing.x1B58[0];
    base[arg0 / 32] &= ~(1 << (arg0 % 32));
}

s32 func_8015DA90(u32 arg0) {
    u32 *base = &lbl_804D3EE0->thing.x1B58[0];
    u32 *qwe = &base[arg0 / 32];
    return *qwe & (1 << (arg0 % 32));
}

void func_8015DAB4(u32 arg0) {
    u32 *base = &lbl_804D3EE0->thing.x1C88[0];
    base[arg0 / 32] |= (1 << (arg0 % 32));
}

s32 func_8015DADC(u32 arg0) {
    u32 *base = &lbl_804D3EE0->thing.x1C88[0];
    return (1 << (arg0 % 32)) & base[arg0 / 32];
}

u8 func_8015DB00(void) {
    return lbl_804D3EE0->x1;
}

void func_8015DB0C(u8 arg0) {
    lbl_804D3EE0->x1 = arg0;
}

void func_8015DB18(void) {
    lbl_804D3EE0->x1 += 1;
}

#ifdef NON_MATCHING
// regswap and extra useless addi
// https://decomp.me/scratch/emRDP
void func_8015DB2C(u8 arg0, s32 arg2) {
    u8 *base = &lbl_804D3EE0->x39[arg0];
    *base = func_8000AF74(*base, 1);
}
#else
asm void func_8015DB2C(u8 arg0, s32 arg2) {
    nofralloc
/* 8015DB2C 0015A70C  7C 08 02 A6 */	mflr r0
/* 8015DB30 0015A710  54 63 06 3E */	clrlwi r3, r3, 0x18
/* 8015DB34 0015A714  90 01 00 04 */	stw r0, 4(r1)
/* 8015DB38 0015A718  38 80 00 01 */	li r4, 1
/* 8015DB3C 0015A71C  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 8015DB40 0015A720  93 E1 00 14 */	stw r31, 0x14(r1)
/* 8015DB44 0015A724  80 0D 88 40 */	lwz r0, lbl_804D3EE0(r13)
/* 8015DB48 0015A728  7F E0 1A 14 */	add r31, r0, r3
/* 8015DB4C 0015A72C  88 7F 00 39 */	lbz r3, 0x39(r31)
/* 8015DB50 0015A730  4B EA D4 25 */	bl func_8000AF74
/* 8015DB54 0015A734  98 7F 00 39 */	stb r3, 0x39(r31)
/* 8015DB58 0015A738  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 8015DB5C 0015A73C  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 8015DB60 0015A740  38 21 00 18 */	addi r1, r1, 0x18
/* 8015DB64 0015A744  7C 08 03 A6 */	mtlr r0
/* 8015DB68 0015A748  4E 80 00 20 */	blr
}
#pragma peephole on
#endif

u8 func_8015DB6C(u8 arg0) {
    return lbl_804D3EE0->x39[arg0];
}

void func_8015DB80(void) {
    int i;
    for (i = 0; i < 11; i++) {
        lbl_804D3EE0->x39[(u8)i] = 0;
    }
}
