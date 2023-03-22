.include "macros.inc"

.section .text

.global grZakoGenerator_801CA394
grZakoGenerator_801CA394:
/* 801CA394 001C6F74  7C 08 02 A6 */    mflr r0
/* 801CA398 001C6F78  90 01 00 04 */    stw r0, 4(r1)
/* 801CA39C 001C6F7C  94 21 FF D0 */    stwu r1, -0x30(r1)
/* 801CA3A0 001C6F80  DB E1 00 28 */    stfd f31, 0x28(r1)
/* 801CA3A4 001C6F84  FF E0 08 90 */    fmr f31, f1
/* 801CA3A8 001C6F88  93 E1 00 24 */    stw r31, 0x24(r1)
/* 801CA3AC 001C6F8C  93 C1 00 20 */    stw r30, 0x20(r1)
/* 801CA3B0 001C6F90  3B C5 00 00 */    addi r30, r5, 0
/* 801CA3B4 001C6F94  93 A1 00 1C */    stw r29, 0x1c(r1)
/* 801CA3B8 001C6F98  3B A4 00 00 */    addi r29, r4, 0
/* 801CA3BC 001C6F9C  93 81 00 18 */    stw r28, 0x18(r1)
/* 801CA3C0 001C6FA0  3B 83 00 00 */    addi r28, r3, 0
/* 801CA3C4 001C6FA4  38 60 00 1C */    li r3, 0x1c
/* 801CA3C8 001C6FA8  48 1B 4E 1D */    bl HSD_MemAlloc
/* 801CA3CC 001C6FAC  7C 7F 1B 79 */    or. r31, r3, r3
/* 801CA3D0 001C6FB0  41 82 00 44 */    beq grZakoGenerator_801CA414
/* 801CA3D4 001C6FB4  1C 7D 00 18 */    mulli r3, r29, 0x18
/* 801CA3D8 001C6FB8  48 1B 4E 0D */    bl HSD_MemAlloc
/* 801CA3DC 001C6FBC  28 03 00 00 */    cmplwi r3, 0
/* 801CA3E0 001C6FC0  90 7F 00 04 */    stw r3, 4(r31)
/* 801CA3E4 001C6FC4  41 82 00 24 */    beq grZakoGenerator_801CA408
/* 801CA3E8 001C6FC8  93 9F 00 00 */    stw r28, 0(r31)
/* 801CA3EC 001C6FCC  38 00 00 00 */    li r0, 0
/* 801CA3F0 001C6FD0  93 BF 00 08 */    stw r29, 8(r31)
/* 801CA3F4 001C6FD4  93 DF 00 0C */    stw r30, 0xc(r31)
/* 801CA3F8 001C6FD8  D3 FF 00 10 */    stfs f31, 0x10(r31)
/* 801CA3FC 001C6FDC  90 1F 00 14 */    stw r0, 0x14(r31)
/* 801CA400 001C6FE0  90 1F 00 18 */    stw r0, 0x18(r31)
/* 801CA404 001C6FE4  48 00 00 10 */    b grZakoGenerator_801CA414
grZakoGenerator_801CA408:
/* 801CA408 001C6FE8  7F E3 FB 78 */    mr r3, r31
/* 801CA40C 001C6FEC  48 1B 4D A5 */    bl HSD_Free
/* 801CA410 001C6FF0  3B E0 00 00 */    li r31, 0
grZakoGenerator_801CA414:
/* 801CA414 001C6FF4  7F E3 FB 78 */    mr r3, r31
/* 801CA418 001C6FF8  80 01 00 34 */    lwz r0, 0x34(r1)
/* 801CA41C 001C6FFC  CB E1 00 28 */    lfd f31, 0x28(r1)
/* 801CA420 001C7000  83 E1 00 24 */    lwz r31, 0x24(r1)
/* 801CA424 001C7004  83 C1 00 20 */    lwz r30, 0x20(r1)
/* 801CA428 001C7008  83 A1 00 1C */    lwz r29, 0x1c(r1)
/* 801CA42C 001C700C  83 81 00 18 */    lwz r28, 0x18(r1)
/* 801CA430 001C7010  38 21 00 30 */    addi r1, r1, 0x30
/* 801CA434 001C7014  7C 08 03 A6 */    mtlr r0
/* 801CA438 001C7018  4E 80 00 20 */    blr

.global grZakoGenerator_801CA43C
grZakoGenerator_801CA43C:
/* 801CA43C 001C701C  7C 08 02 A6 */    mflr r0
/* 801CA440 001C7020  90 01 00 04 */    stw r0, 4(r1)
/* 801CA444 001C7024  94 21 FF A8 */    stwu r1, -0x58(r1)
/* 801CA448 001C7028  DB E1 00 50 */    stfd f31, 0x50(r1)
/* 801CA44C 001C702C  DB C1 00 48 */    stfd f30, 0x48(r1)
/* 801CA450 001C7030  DB A1 00 40 */    stfd f29, 0x40(r1)
/* 801CA454 001C7034  FF A0 08 90 */    fmr f29, f1
/* 801CA458 001C7038  BF 41 00 28 */    stmw r26, 0x28(r1)
/* 801CA45C 001C703C  7C 7A 1B 79 */    or. r26, r3, r3
/* 801CA460 001C7040  3B 64 00 00 */    addi r27, r4, 0
/* 801CA464 001C7044  3B A0 00 00 */    li r29, 0
/* 801CA468 001C7048  41 82 00 0C */    beq grZakoGenerator_801CA474
/* 801CA46C 001C704C  28 1B 00 00 */    cmplwi r27, 0
/* 801CA470 001C7050  40 82 00 0C */    bne grZakoGenerator_801CA47C
grZakoGenerator_801CA474:
/* 801CA474 001C7054  38 60 00 00 */    li r3, 0
/* 801CA478 001C7058  48 00 01 E4 */    b grZakoGenerator_801CA65C
grZakoGenerator_801CA47C:
/* 801CA47C 001C705C  83 FA 00 00 */    lwz r31, 0(r26)
/* 801CA480 001C7060  3B C0 00 00 */    li r30, 0
/* 801CA484 001C7064  83 9A 00 04 */    lwz r28, 4(r26)
/* 801CA488 001C7068  48 00 00 30 */    b grZakoGenerator_801CA4B8
grZakoGenerator_801CA48C:
/* 801CA48C 001C706C  38 7B 00 00 */    addi r3, r27, 0
/* 801CA490 001C7070  38 9F 00 00 */    addi r4, r31, 0
/* 801CA494 001C7074  38 BC 00 00 */    addi r5, r28, 0
/* 801CA498 001C7078  4B E4 0D 35 */    bl lb_8000B1CC
/* 801CA49C 001C707C  38 7B 00 00 */    addi r3, r27, 0
/* 801CA4A0 001C7080  38 9F 00 0C */    addi r4, r31, 0xc
/* 801CA4A4 001C7084  38 BC 00 0C */    addi r5, r28, 0xc
/* 801CA4A8 001C7088  4B E4 0D 25 */    bl lb_8000B1CC
/* 801CA4AC 001C708C  3B DE 00 01 */    addi r30, r30, 1
/* 801CA4B0 001C7090  3B FF 00 18 */    addi r31, r31, 0x18
/* 801CA4B4 001C7094  3B 9C 00 18 */    addi r28, r28, 0x18
grZakoGenerator_801CA4B8:
/* 801CA4B8 001C7098  80 1A 00 08 */    lwz r0, 8(r26)
/* 801CA4BC 001C709C  7C 1E 00 00 */    cmpw r30, r0
/* 801CA4C0 001C70A0  41 80 FF CC */    blt grZakoGenerator_801CA48C
/* 801CA4C4 001C70A4  83 FA 00 04 */    lwz r31, 4(r26)
/* 801CA4C8 001C70A8  3B C0 00 00 */    li r30, 0
/* 801CA4CC 001C70AC  C3 C2 B3 C8 */    lfs f30, lbl_804DADA8@sda21(r2)
/* 801CA4D0 001C70B0  C3 E2 B3 CC */    lfs f31, lbl_804DADAC@sda21(r2)
/* 801CA4D4 001C70B4  48 00 01 78 */    b grZakoGenerator_801CA64C
grZakoGenerator_801CA4D8:
/* 801CA4D8 001C70B8  C0 3F 00 04 */    lfs f1, 4(r31)
/* 801CA4DC 001C70BC  FC 01 E8 40 */    fcmpo cr0, f1, f29
/* 801CA4E0 001C70C0  40 81 00 10 */    ble grZakoGenerator_801CA4F0
/* 801CA4E4 001C70C4  C0 1F 00 10 */    lfs f0, 0x10(r31)
/* 801CA4E8 001C70C8  FC 00 E8 40 */    fcmpo cr0, f0, f29
/* 801CA4EC 001C70CC  41 81 01 34 */    bgt grZakoGenerator_801CA620
grZakoGenerator_801CA4F0:
/* 801CA4F0 001C70D0  FC 01 E8 40 */    fcmpo cr0, f1, f29
/* 801CA4F4 001C70D4  40 80 00 10 */    bge grZakoGenerator_801CA504
/* 801CA4F8 001C70D8  C0 1F 00 10 */    lfs f0, 0x10(r31)
/* 801CA4FC 001C70DC  FC 00 E8 40 */    fcmpo cr0, f0, f29
/* 801CA500 001C70E0  41 80 01 20 */    blt grZakoGenerator_801CA620
grZakoGenerator_801CA504:
/* 801CA504 001C70E4  C0 1A 00 10 */    lfs f0, 0x10(r26)
/* 801CA508 001C70E8  FC 00 F0 40 */    fcmpo cr0, f0, f30
/* 801CA50C 001C70EC  41 80 00 14 */    blt grZakoGenerator_801CA520
/* 801CA510 001C70F0  48 1B 60 19 */    bl HSD_Randf
/* 801CA514 001C70F4  C0 1A 00 10 */    lfs f0, 0x10(r26)
/* 801CA518 001C70F8  FC 01 00 40 */    fcmpo cr0, f1, f0
/* 801CA51C 001C70FC  40 80 01 28 */    bge grZakoGenerator_801CA644
grZakoGenerator_801CA520:
/* 801CA520 001C7100  C0 1F 00 10 */    lfs f0, 0x10(r31)
/* 801CA524 001C7104  C0 3F 00 04 */    lfs f1, 4(r31)
/* 801CA528 001C7108  EC 00 08 28 */    fsubs f0, f0, f1
/* 801CA52C 001C710C  FC 00 F0 40 */    fcmpo cr0, f0, f30
/* 801CA530 001C7110  FC 60 00 90 */    fmr f3, f0
/* 801CA534 001C7114  40 80 00 0C */    bge grZakoGenerator_801CA540
/* 801CA538 001C7118  FC 00 18 50 */    fneg f0, f3
/* 801CA53C 001C711C  48 00 00 08 */    b grZakoGenerator_801CA544
grZakoGenerator_801CA540:
/* 801CA540 001C7120  FC 00 18 90 */    fmr f0, f3
grZakoGenerator_801CA544:
/* 801CA544 001C7124  FC 00 F8 40 */    fcmpo cr0, f0, f31
/* 801CA548 001C7128  40 81 00 3C */    ble grZakoGenerator_801CA584
/* 801CA54C 001C712C  EC 3D 08 28 */    fsubs f1, f29, f1
/* 801CA550 001C7130  C0 5F 00 00 */    lfs f2, 0(r31)
/* 801CA554 001C7134  C0 1F 00 0C */    lfs f0, 0xc(r31)
/* 801CA558 001C7138  EC 61 18 24 */    fdivs f3, f1, f3
/* 801CA55C 001C713C  EC 00 10 28 */    fsubs f0, f0, f2
/* 801CA560 001C7140  EC 03 10 3A */    fmadds f0, f3, f0, f2
/* 801CA564 001C7144  D0 01 00 18 */    stfs f0, 0x18(r1)
/* 801CA568 001C7148  D3 A1 00 1C */    stfs f29, 0x1c(r1)
/* 801CA56C 001C714C  C0 3F 00 08 */    lfs f1, 8(r31)
/* 801CA570 001C7150  C0 1F 00 14 */    lfs f0, 0x14(r31)
/* 801CA574 001C7154  EC 00 08 28 */    fsubs f0, f0, f1
/* 801CA578 001C7158  EC 03 08 3A */    fmadds f0, f3, f0, f1
/* 801CA57C 001C715C  D0 01 00 20 */    stfs f0, 0x20(r1)
/* 801CA580 001C7160  48 00 00 34 */    b grZakoGenerator_801CA5B4
grZakoGenerator_801CA584:
/* 801CA584 001C7164  48 1B 5F A5 */    bl HSD_Randf
/* 801CA588 001C7168  C0 5F 00 00 */    lfs f2, 0(r31)
/* 801CA58C 001C716C  C0 1F 00 0C */    lfs f0, 0xc(r31)
/* 801CA590 001C7170  EC 00 10 28 */    fsubs f0, f0, f2
/* 801CA594 001C7174  EC 01 10 3A */    fmadds f0, f1, f0, f2
/* 801CA598 001C7178  D0 01 00 18 */    stfs f0, 0x18(r1)
/* 801CA59C 001C717C  D3 A1 00 1C */    stfs f29, 0x1c(r1)
/* 801CA5A0 001C7180  C0 5F 00 08 */    lfs f2, 8(r31)
/* 801CA5A4 001C7184  C0 1F 00 14 */    lfs f0, 0x14(r31)
/* 801CA5A8 001C7188  EC 00 10 28 */    fsubs f0, f0, f2
/* 801CA5AC 001C718C  EC 01 10 3A */    fmadds f0, f1, f0, f2
/* 801CA5B0 001C7190  D0 01 00 20 */    stfs f0, 0x20(r1)
grZakoGenerator_801CA5B4:
/* 801CA5B4 001C7194  C0 1A 00 10 */    lfs f0, 0x10(r26)
/* 801CA5B8 001C7198  FC 00 F0 40 */    fcmpo cr0, f0, f30
/* 801CA5BC 001C719C  40 80 00 48 */    bge grZakoGenerator_801CA604
/* 801CA5C0 001C71A0  80 7A 00 14 */    lwz r3, 0x14(r26)
/* 801CA5C4 001C71A4  28 03 00 00 */    cmplwi r3, 0
/* 801CA5C8 001C71A8  40 82 00 20 */    bne grZakoGenerator_801CA5E8
/* 801CA5CC 001C71AC  81 9A 00 0C */    lwz r12, 0xc(r26)
/* 801CA5D0 001C71B0  38 9E 00 00 */    addi r4, r30, 0
/* 801CA5D4 001C71B4  38 61 00 18 */    addi r3, r1, 0x18
/* 801CA5D8 001C71B8  7D 88 03 A6 */    mtlr r12
/* 801CA5DC 001C71BC  4E 80 00 21 */    blrl
/* 801CA5E0 001C71C0  90 7A 00 14 */    stw r3, 0x14(r26)
/* 801CA5E4 001C71C4  48 00 00 34 */    b grZakoGenerator_801CA618
grZakoGenerator_801CA5E8:
/* 801CA5E8 001C71C8  C0 01 00 18 */    lfs f0, 0x18(r1)
/* 801CA5EC 001C71CC  D0 03 00 24 */    stfs f0, 0x24(r3)
/* 801CA5F0 001C71D0  C0 01 00 1C */    lfs f0, 0x1c(r1)
/* 801CA5F4 001C71D4  D0 03 00 28 */    stfs f0, 0x28(r3)
/* 801CA5F8 001C71D8  C0 01 00 20 */    lfs f0, 0x20(r1)
/* 801CA5FC 001C71DC  D0 03 00 2C */    stfs f0, 0x2c(r3)
/* 801CA600 001C71E0  48 00 00 18 */    b grZakoGenerator_801CA618
grZakoGenerator_801CA604:
/* 801CA604 001C71E4  81 9A 00 0C */    lwz r12, 0xc(r26)
/* 801CA608 001C71E8  38 9E 00 00 */    addi r4, r30, 0
/* 801CA60C 001C71EC  38 61 00 18 */    addi r3, r1, 0x18
/* 801CA610 001C71F0  7D 88 03 A6 */    mtlr r12
/* 801CA614 001C71F4  4E 80 00 21 */    blrl
grZakoGenerator_801CA618:
/* 801CA618 001C71F8  3B BD 00 01 */    addi r29, r29, 1
/* 801CA61C 001C71FC  48 00 00 28 */    b grZakoGenerator_801CA644
grZakoGenerator_801CA620:
/* 801CA620 001C7200  C0 1A 00 10 */    lfs f0, 0x10(r26)
/* 801CA624 001C7204  FC 00 F0 40 */    fcmpo cr0, f0, f30
/* 801CA628 001C7208  40 80 00 1C */    bge grZakoGenerator_801CA644
/* 801CA62C 001C720C  80 7A 00 14 */    lwz r3, 0x14(r26)
/* 801CA630 001C7210  28 03 00 00 */    cmplwi r3, 0
/* 801CA634 001C7214  41 82 00 10 */    beq grZakoGenerator_801CA644
/* 801CA638 001C7218  4B FF F2 3D */    bl grLib_801C9874
/* 801CA63C 001C721C  38 00 00 00 */    li r0, 0
/* 801CA640 001C7220  90 1A 00 14 */    stw r0, 0x14(r26)
grZakoGenerator_801CA644:
/* 801CA644 001C7224  3B DE 00 01 */    addi r30, r30, 1
/* 801CA648 001C7228  3B FF 00 18 */    addi r31, r31, 0x18
grZakoGenerator_801CA64C:
/* 801CA64C 001C722C  80 1A 00 08 */    lwz r0, 8(r26)
/* 801CA650 001C7230  7C 1E 00 00 */    cmpw r30, r0
/* 801CA654 001C7234  41 80 FE 84 */    blt grZakoGenerator_801CA4D8
/* 801CA658 001C7238  7F A3 EB 78 */    mr r3, r29
grZakoGenerator_801CA65C:
/* 801CA65C 001C723C  BB 41 00 28 */    lmw r26, 0x28(r1)
/* 801CA660 001C7240  80 01 00 5C */    lwz r0, 0x5c(r1)
/* 801CA664 001C7244  CB E1 00 50 */    lfd f31, 0x50(r1)
/* 801CA668 001C7248  CB C1 00 48 */    lfd f30, 0x48(r1)
/* 801CA66C 001C724C  CB A1 00 40 */    lfd f29, 0x40(r1)
/* 801CA670 001C7250  38 21 00 58 */    addi r1, r1, 0x58
/* 801CA674 001C7254  7C 08 03 A6 */    mtlr r0
/* 801CA678 001C7258  4E 80 00 20 */    blr

.global grZakoGenerator_801CA67C
grZakoGenerator_801CA67C:
/* 801CA67C 001C725C  7C 08 02 A6 */    mflr r0
/* 801CA680 001C7260  38 60 03 CC */    li r3, 0x3cc
/* 801CA684 001C7264  90 01 00 04 */    stw r0, 4(r1)
/* 801CA688 001C7268  94 21 FF E0 */    stwu r1, -0x20(r1)
/* 801CA68C 001C726C  93 E1 00 1C */    stw r31, 0x1c(r1)
/* 801CA690 001C7270  48 1B 4B 55 */    bl HSD_MemAlloc
/* 801CA694 001C7274  7C 7F 1B 79 */    or. r31, r3, r3
/* 801CA698 001C7278  40 82 00 18 */    bne grZakoGenerator_801CA6B0
/* 801CA69C 001C727C  3C 60 80 3E */    lis r3, lbl_803E0BA8@ha
/* 801CA6A0 001C7280  38 63 0B A8 */    addi r3, r3, lbl_803E0BA8@l
/* 801CA6A4 001C7284  38 80 00 52 */    li r4, 0x52
/* 801CA6A8 001C7288  38 AD 8E F0 */    addi r5, r13, lbl_804D4590@sda21
/* 801CA6AC 001C728C  48 1B DB 75 */    bl __assert
grZakoGenerator_801CA6B0:
/* 801CA6B0 001C7290  38 00 00 05 */    li r0, 5
/* 801CA6B4 001C7294  7C 09 03 A6 */    mtctr r0
/* 801CA6B8 001C7298  39 7F 00 00 */    addi r11, r31, 0
/* 801CA6BC 001C729C  39 80 00 00 */    li r12, 0
grZakoGenerator_801CA6C0:
/* 801CA6C0 001C72A0  39 4C 00 20 */    addi r10, r12, 0x20
/* 801CA6C4 001C72A4  B1 4B 00 00 */    sth r10, 0(r11)
/* 801CA6C8 001C72A8  39 20 00 00 */    li r9, 0
/* 801CA6CC 001C72AC  39 0C 00 21 */    addi r8, r12, 0x21
/* 801CA6D0 001C72B0  B1 2B 00 02 */    sth r9, 2(r11)
/* 801CA6D4 001C72B4  38 EC 00 22 */    addi r7, r12, 0x22
/* 801CA6D8 001C72B8  38 CC 00 23 */    addi r6, r12, 0x23
/* 801CA6DC 001C72BC  91 2B 00 04 */    stw r9, 4(r11)
/* 801CA6E0 001C72C0  38 AC 00 24 */    addi r5, r12, 0x24
/* 801CA6E4 001C72C4  38 8C 00 25 */    addi r4, r12, 0x25
/* 801CA6E8 001C72C8  B1 0B 00 0C */    sth r8, 0xc(r11)
/* 801CA6EC 001C72CC  38 6C 00 26 */    addi r3, r12, 0x26
/* 801CA6F0 001C72D0  38 0C 00 27 */    addi r0, r12, 0x27
/* 801CA6F4 001C72D4  B1 2B 00 0E */    sth r9, 0xe(r11)
/* 801CA6F8 001C72D8  39 4C 00 28 */    addi r10, r12, 0x28
/* 801CA6FC 001C72DC  39 0C 00 29 */    addi r8, r12, 0x29
/* 801CA700 001C72E0  91 2B 00 10 */    stw r9, 0x10(r11)
/* 801CA704 001C72E4  B0 EB 00 18 */    sth r7, 0x18(r11)
/* 801CA708 001C72E8  38 EC 00 2A */    addi r7, r12, 0x2a
/* 801CA70C 001C72EC  B1 2B 00 1A */    sth r9, 0x1a(r11)
/* 801CA710 001C72F0  91 2B 00 1C */    stw r9, 0x1c(r11)
/* 801CA714 001C72F4  B0 CB 00 24 */    sth r6, 0x24(r11)
/* 801CA718 001C72F8  38 CC 00 2B */    addi r6, r12, 0x2b
/* 801CA71C 001C72FC  B1 2B 00 26 */    sth r9, 0x26(r11)
/* 801CA720 001C7300  91 2B 00 28 */    stw r9, 0x28(r11)
/* 801CA724 001C7304  B0 AB 00 30 */    sth r5, 0x30(r11)
/* 801CA728 001C7308  38 AC 00 2C */    addi r5, r12, 0x2c
/* 801CA72C 001C730C  B1 2B 00 32 */    sth r9, 0x32(r11)
/* 801CA730 001C7310  91 2B 00 34 */    stw r9, 0x34(r11)
/* 801CA734 001C7314  B0 8B 00 3C */    sth r4, 0x3c(r11)
/* 801CA738 001C7318  38 8C 00 2D */    addi r4, r12, 0x2d
/* 801CA73C 001C731C  B1 2B 00 3E */    sth r9, 0x3e(r11)
/* 801CA740 001C7320  91 2B 00 40 */    stw r9, 0x40(r11)
/* 801CA744 001C7324  B0 6B 00 48 */    sth r3, 0x48(r11)
/* 801CA748 001C7328  38 6C 00 2E */    addi r3, r12, 0x2e
/* 801CA74C 001C732C  B1 2B 00 4A */    sth r9, 0x4a(r11)
/* 801CA750 001C7330  91 2B 00 4C */    stw r9, 0x4c(r11)
/* 801CA754 001C7334  B0 0B 00 54 */    sth r0, 0x54(r11)
/* 801CA758 001C7338  38 0C 00 2F */    addi r0, r12, 0x2f
/* 801CA75C 001C733C  39 8C 00 10 */    addi r12, r12, 0x10
/* 801CA760 001C7340  B1 2B 00 56 */    sth r9, 0x56(r11)
/* 801CA764 001C7344  91 2B 00 58 */    stw r9, 0x58(r11)
/* 801CA768 001C7348  B1 4B 00 60 */    sth r10, 0x60(r11)
/* 801CA76C 001C734C  B1 2B 00 62 */    sth r9, 0x62(r11)
/* 801CA770 001C7350  91 2B 00 64 */    stw r9, 0x64(r11)
/* 801CA774 001C7354  B1 0B 00 6C */    sth r8, 0x6c(r11)
/* 801CA778 001C7358  B1 2B 00 6E */    sth r9, 0x6e(r11)
/* 801CA77C 001C735C  91 2B 00 70 */    stw r9, 0x70(r11)
/* 801CA780 001C7360  B0 EB 00 78 */    sth r7, 0x78(r11)
/* 801CA784 001C7364  B1 2B 00 7A */    sth r9, 0x7a(r11)
/* 801CA788 001C7368  91 2B 00 7C */    stw r9, 0x7c(r11)
/* 801CA78C 001C736C  B0 CB 00 84 */    sth r6, 0x84(r11)
/* 801CA790 001C7370  B1 2B 00 86 */    sth r9, 0x86(r11)
/* 801CA794 001C7374  91 2B 00 88 */    stw r9, 0x88(r11)
/* 801CA798 001C7378  B0 AB 00 90 */    sth r5, 0x90(r11)
/* 801CA79C 001C737C  B1 2B 00 92 */    sth r9, 0x92(r11)
/* 801CA7A0 001C7380  91 2B 00 94 */    stw r9, 0x94(r11)
/* 801CA7A4 001C7384  B0 8B 00 9C */    sth r4, 0x9c(r11)
/* 801CA7A8 001C7388  B1 2B 00 9E */    sth r9, 0x9e(r11)
/* 801CA7AC 001C738C  91 2B 00 A0 */    stw r9, 0xa0(r11)
/* 801CA7B0 001C7390  B0 6B 00 A8 */    sth r3, 0xa8(r11)
/* 801CA7B4 001C7394  B1 2B 00 AA */    sth r9, 0xaa(r11)
/* 801CA7B8 001C7398  91 2B 00 AC */    stw r9, 0xac(r11)
/* 801CA7BC 001C739C  B0 0B 00 B4 */    sth r0, 0xb4(r11)
/* 801CA7C0 001C73A0  B1 2B 00 B6 */    sth r9, 0xb6(r11)
/* 801CA7C4 001C73A4  91 2B 00 B8 */    stw r9, 0xb8(r11)
/* 801CA7C8 001C73A8  39 6B 00 C0 */    addi r11, r11, 0xc0
/* 801CA7CC 001C73AC  42 00 FE F4 */    bdnz grZakoGenerator_801CA6C0
/* 801CA7D0 001C73B0  1C 0C 00 0C */    mulli r0, r12, 0xc
/* 801CA7D4 001C73B4  2C 0C 00 51 */    cmpwi r12, 0x51
/* 801CA7D8 001C73B8  7C BF 02 14 */    add r5, r31, r0
/* 801CA7DC 001C73BC  20 6C 00 51 */    subfic r3, r12, 0x51
/* 801CA7E0 001C73C0  38 80 FF FF */    li r4, -1
/* 801CA7E4 001C73C4  40 80 00 98 */    bge grZakoGenerator_801CA87C
/* 801CA7E8 001C73C8  54 60 E8 FF */    rlwinm. r0, r3, 0x1d, 3, 0x1f
/* 801CA7EC 001C73CC  7C 09 03 A6 */    mtctr r0
/* 801CA7F0 001C73D0  41 82 00 74 */    beq grZakoGenerator_801CA864
grZakoGenerator_801CA7F4:
/* 801CA7F4 001C73D4  B0 85 00 00 */    sth r4, 0(r5)
/* 801CA7F8 001C73D8  B1 25 00 02 */    sth r9, 2(r5)
/* 801CA7FC 001C73DC  91 25 00 04 */    stw r9, 4(r5)
/* 801CA800 001C73E0  B0 85 00 0C */    sth r4, 0xc(r5)
/* 801CA804 001C73E4  B1 25 00 0E */    sth r9, 0xe(r5)
/* 801CA808 001C73E8  91 25 00 10 */    stw r9, 0x10(r5)
/* 801CA80C 001C73EC  B0 85 00 18 */    sth r4, 0x18(r5)
/* 801CA810 001C73F0  B1 25 00 1A */    sth r9, 0x1a(r5)
/* 801CA814 001C73F4  91 25 00 1C */    stw r9, 0x1c(r5)
/* 801CA818 001C73F8  B0 85 00 24 */    sth r4, 0x24(r5)
/* 801CA81C 001C73FC  B1 25 00 26 */    sth r9, 0x26(r5)
/* 801CA820 001C7400  91 25 00 28 */    stw r9, 0x28(r5)
/* 801CA824 001C7404  B0 85 00 30 */    sth r4, 0x30(r5)
/* 801CA828 001C7408  B1 25 00 32 */    sth r9, 0x32(r5)
/* 801CA82C 001C740C  91 25 00 34 */    stw r9, 0x34(r5)
/* 801CA830 001C7410  B0 85 00 3C */    sth r4, 0x3c(r5)
/* 801CA834 001C7414  B1 25 00 3E */    sth r9, 0x3e(r5)
/* 801CA838 001C7418  91 25 00 40 */    stw r9, 0x40(r5)
/* 801CA83C 001C741C  B0 85 00 48 */    sth r4, 0x48(r5)
/* 801CA840 001C7420  B1 25 00 4A */    sth r9, 0x4a(r5)
/* 801CA844 001C7424  91 25 00 4C */    stw r9, 0x4c(r5)
/* 801CA848 001C7428  B0 85 00 54 */    sth r4, 0x54(r5)
/* 801CA84C 001C742C  B1 25 00 56 */    sth r9, 0x56(r5)
/* 801CA850 001C7430  91 25 00 58 */    stw r9, 0x58(r5)
/* 801CA854 001C7434  38 A5 00 60 */    addi r5, r5, 0x60
/* 801CA858 001C7438  42 00 FF 9C */    bdnz grZakoGenerator_801CA7F4
/* 801CA85C 001C743C  70 63 00 07 */    andi. r3, r3, 7
/* 801CA860 001C7440  41 82 00 1C */    beq grZakoGenerator_801CA87C
grZakoGenerator_801CA864:
/* 801CA864 001C7444  7C 69 03 A6 */    mtctr r3
grZakoGenerator_801CA868:
/* 801CA868 001C7448  B0 85 00 00 */    sth r4, 0(r5)
/* 801CA86C 001C744C  B1 25 00 02 */    sth r9, 2(r5)
/* 801CA870 001C7450  91 25 00 04 */    stw r9, 4(r5)
/* 801CA874 001C7454  38 A5 00 0C */    addi r5, r5, 0xc
/* 801CA878 001C7458  42 00 FF F0 */    bdnz grZakoGenerator_801CA868
grZakoGenerator_801CA87C:
/* 801CA87C 001C745C  3C 60 80 4A */    lis r3, lbl_8049F030@ha
/* 801CA880 001C7460  38 83 F0 30 */    addi r4, r3, lbl_8049F030@l
/* 801CA884 001C7464  88 04 00 0A */    lbz r0, 0xa(r4)
/* 801CA888 001C7468  38 60 00 01 */    li r3, 1
/* 801CA88C 001C746C  50 60 3E 30 */    rlwimi r0, r3, 7, 0x18, 0x18
/* 801CA890 001C7470  98 04 00 0A */    stb r0, 0xa(r4)
/* 801CA894 001C7474  38 00 00 00 */    li r0, 0
/* 801CA898 001C7478  38 7F 00 00 */    addi r3, r31, 0
/* 801CA89C 001C747C  B0 04 00 08 */    sth r0, 8(r4)
/* 801CA8A0 001C7480  80 01 00 24 */    lwz r0, 0x24(r1)
/* 801CA8A4 001C7484  83 E1 00 1C */    lwz r31, 0x1c(r1)
/* 801CA8A8 001C7488  38 21 00 20 */    addi r1, r1, 0x20
/* 801CA8AC 001C748C  7C 08 03 A6 */    mtlr r0
/* 801CA8B0 001C7490  4E 80 00 20 */    blr

.global grZakoGenerator_801CA8B4
grZakoGenerator_801CA8B4:
/* 801CA8B4 001C7494  7C 08 02 A6 */    mflr r0
/* 801CA8B8 001C7498  3C 80 80 4A */    lis r4, lbl_8049F030@ha
/* 801CA8BC 001C749C  90 01 00 04 */    stw r0, 4(r1)
/* 801CA8C0 001C74A0  94 21 FF 80 */    stwu r1, -0x80(r1)
/* 801CA8C4 001C74A4  DB E1 00 78 */    stfd f31, 0x78(r1)
/* 801CA8C8 001C74A8  DB C1 00 70 */    stfd f30, 0x70(r1)
/* 801CA8CC 001C74AC  DB A1 00 68 */    stfd f29, 0x68(r1)
/* 801CA8D0 001C74B0  DB 81 00 60 */    stfd f28, 0x60(r1)
/* 801CA8D4 001C74B4  DB 61 00 58 */    stfd f27, 0x58(r1)
/* 801CA8D8 001C74B8  DB 41 00 50 */    stfd f26, 0x50(r1)
/* 801CA8DC 001C74BC  DB 21 00 48 */    stfd f25, 0x48(r1)
/* 801CA8E0 001C74C0  DB 01 00 40 */    stfd f24, 0x40(r1)
/* 801CA8E4 001C74C4  BF 01 00 20 */    stmw r24, 0x20(r1)
/* 801CA8E8 001C74C8  3B 64 F0 30 */    addi r27, r4, lbl_8049F030@l
/* 801CA8EC 001C74CC  3B FB 00 04 */    addi r31, r27, 4
/* 801CA8F0 001C74D0  3B 23 00 00 */    addi r25, r3, 0
/* 801CA8F4 001C74D4  80 1B 00 04 */    lwz r0, 4(r27)
/* 801CA8F8 001C74D8  28 00 00 00 */    cmplwi r0, 0
/* 801CA8FC 001C74DC  41 82 02 E4 */    beq grZakoGenerator_801CABE0
/* 801CA900 001C74E0  88 1B 00 0A */    lbz r0, 0xa(r27)
/* 801CA904 001C74E4  54 00 CF FF */    rlwinm. r0, r0, 0x19, 0x1f, 0x1f
/* 801CA908 001C74E8  41 82 02 D8 */    beq grZakoGenerator_801CABE0
/* 801CA90C 001C74EC  48 05 A2 2D */    bl Stage_GetBlastZoneRightOffset
/* 801CA910 001C74F0  FF 80 08 90 */    fmr f28, f1
/* 801CA914 001C74F4  48 05 A2 3D */    bl Stage_GetBlastZoneLeftOffset
/* 801CA918 001C74F8  FF A0 08 90 */    fmr f29, f1
/* 801CA91C 001C74FC  48 05 A2 4D */    bl Stage_GetBlastZoneTopOffset
/* 801CA920 001C7500  FF C0 08 90 */    fmr f30, f1
/* 801CA924 001C7504  48 05 A2 5D */    bl Stage_GetBlastZoneBottomOffset
/* 801CA928 001C7508  FF E0 08 90 */    fmr f31, f1
/* 801CA92C 001C750C  48 05 A1 3D */    bl Stage_GetCamBoundsRightOffset
/* 801CA930 001C7510  EC 3C 08 2A */    fadds f1, f28, f1
/* 801CA934 001C7514  C0 02 B3 D0 */    lfs f0, lbl_804DADB0@sda21(r2)
/* 801CA938 001C7518  EF 60 00 72 */    fmuls f27, f0, f1
/* 801CA93C 001C751C  48 05 A1 19 */    bl Stage_GetCamBoundsLeftOffset
/* 801CA940 001C7520  EC 3D 08 2A */    fadds f1, f29, f1
/* 801CA944 001C7524  C0 02 B3 D0 */    lfs f0, lbl_804DADB0@sda21(r2)
/* 801CA948 001C7528  EF 40 00 72 */    fmuls f26, f0, f1
/* 801CA94C 001C752C  48 05 A1 35 */    bl Stage_GetCamBoundsTopOffset
/* 801CA950 001C7530  EC 3E 08 2A */    fadds f1, f30, f1
/* 801CA954 001C7534  C0 02 B3 D0 */    lfs f0, lbl_804DADB0@sda21(r2)
/* 801CA958 001C7538  EF 20 00 72 */    fmuls f25, f0, f1
/* 801CA95C 001C753C  48 05 A1 3D */    bl Stage_GetCamBoundsBottomOffset
/* 801CA960 001C7540  EC 3F 08 2A */    fadds f1, f31, f1
/* 801CA964 001C7544  C0 02 B3 D0 */    lfs f0, lbl_804DADB0@sda21(r2)
/* 801CA968 001C7548  3B 1B 00 08 */    addi r24, r27, 8
/* 801CA96C 001C754C  AB 5B 00 08 */    lha r26, 8(r27)
/* 801CA970 001C7550  3B 80 00 FF */    li r28, 0xff
/* 801CA974 001C7554  EF 00 00 72 */    fmuls f24, f0, f1
/* 801CA978 001C7558  7F 5D D3 78 */    mr r29, r26
grZakoGenerator_801CA97C:
/* 801CA97C 001C755C  1F DD 00 0C */    mulli r30, r29, 0xc
/* 801CA980 001C7560  80 1F 00 00 */    lwz r0, 0(r31)
/* 801CA984 001C7564  7C 80 F2 14 */    add r4, r0, r30
/* 801CA988 001C7568  A8 64 00 00 */    lha r3, 0(r4)
/* 801CA98C 001C756C  2C 03 FF FF */    cmpwi r3, -1
/* 801CA990 001C7570  41 82 02 28 */    beq grZakoGenerator_801CABB8
/* 801CA994 001C7574  80 04 00 04 */    lwz r0, 4(r4)
/* 801CA998 001C7578  28 00 00 00 */    cmplwi r0, 0
/* 801CA99C 001C757C  40 82 02 1C */    bne grZakoGenerator_801CABB8
/* 801CA9A0 001C7580  38 A4 00 02 */    addi r5, r4, 2
/* 801CA9A4 001C7584  A8 84 00 02 */    lha r4, 2(r4)
/* 801CA9A8 001C7588  2C 04 FF FF */    cmpwi r4, -1
/* 801CA9AC 001C758C  41 82 02 0C */    beq grZakoGenerator_801CABB8
/* 801CA9B0 001C7590  7C 80 07 35 */    extsh. r0, r4
/* 801CA9B4 001C7594  40 81 00 10 */    ble grZakoGenerator_801CA9C4
/* 801CA9B8 001C7598  38 04 FF FF */    addi r0, r4, -1
/* 801CA9BC 001C759C  B0 05 00 00 */    sth r0, 0(r5)
/* 801CA9C0 001C75A0  48 00 01 F8 */    b grZakoGenerator_801CABB8
grZakoGenerator_801CA9C4:
/* 801CA9C4 001C75A4  38 81 00 10 */    addi r4, r1, 0x10
/* 801CA9C8 001C75A8  4B FF 83 5D */    bl Ground_801C2D24
/* 801CA9CC 001C75AC  2C 03 00 00 */    cmpwi r3, 0
/* 801CA9D0 001C75B0  41 82 01 E8 */    beq grZakoGenerator_801CABB8
/* 801CA9D4 001C75B4  C0 01 00 10 */    lfs f0, 0x10(r1)
/* 801CA9D8 001C75B8  FC 1D 00 40 */    fcmpo cr0, f29, f0
/* 801CA9DC 001C75BC  40 80 01 DC */    bge grZakoGenerator_801CABB8
/* 801CA9E0 001C75C0  FC 00 E0 40 */    fcmpo cr0, f0, f28
/* 801CA9E4 001C75C4  40 80 01 D4 */    bge grZakoGenerator_801CABB8
/* 801CA9E8 001C75C8  C0 21 00 14 */    lfs f1, 0x14(r1)
/* 801CA9EC 001C75CC  FC 1F 08 40 */    fcmpo cr0, f31, f1
/* 801CA9F0 001C75D0  40 80 01 C8 */    bge grZakoGenerator_801CABB8
/* 801CA9F4 001C75D4  FC 01 F0 40 */    fcmpo cr0, f1, f30
/* 801CA9F8 001C75D8  40 80 01 C0 */    bge grZakoGenerator_801CABB8
/* 801CA9FC 001C75DC  2C 19 00 00 */    cmpwi r25, 0
/* 801CAA00 001C75E0  40 82 00 24 */    bne grZakoGenerator_801CAA24
/* 801CAA04 001C75E4  FC 1A 00 40 */    fcmpo cr0, f26, f0
/* 801CAA08 001C75E8  40 80 00 1C */    bge grZakoGenerator_801CAA24
/* 801CAA0C 001C75EC  FC 00 D8 40 */    fcmpo cr0, f0, f27
/* 801CAA10 001C75F0  40 80 00 14 */    bge grZakoGenerator_801CAA24
/* 801CAA14 001C75F4  FC 18 08 40 */    fcmpo cr0, f24, f1
/* 801CAA18 001C75F8  40 80 00 0C */    bge grZakoGenerator_801CAA24
/* 801CAA1C 001C75FC  FC 01 C8 40 */    fcmpo cr0, f1, f25
/* 801CAA20 001C7600  41 80 01 98 */    blt grZakoGenerator_801CABB8
grZakoGenerator_801CAA24:
/* 801CAA24 001C7604  80 1F 00 00 */    lwz r0, 0(r31)
/* 801CAA28 001C7608  38 60 00 00 */    li r3, 0
/* 801CAA2C 001C760C  7C A0 F2 14 */    add r5, r0, r30
/* 801CAA30 001C7610  A8 85 00 00 */    lha r4, 0(r5)
/* 801CAA34 001C7614  2C 04 00 DC */    cmpwi r4, 0xdc
/* 801CAA38 001C7618  41 80 00 34 */    blt grZakoGenerator_801CAA6C
/* 801CAA3C 001C761C  2C 04 00 FB */    cmpwi r4, 0xfb
/* 801CAA40 001C7620  41 81 00 2C */    bgt grZakoGenerator_801CAA6C
/* 801CAA44 001C7624  80 65 00 08 */    lwz r3, 8(r5)
/* 801CAA48 001C7628  2C 03 FF FF */    cmpwi r3, -1
/* 801CAA4C 001C762C  41 82 01 6C */    beq grZakoGenerator_801CABB8
/* 801CAA50 001C7630  4B FF AE 91 */    bl Ground_801C58E0
/* 801CAA54 001C7634  28 03 00 00 */    cmplwi r3, 0
/* 801CAA58 001C7638  41 82 01 60 */    beq grZakoGenerator_801CABB8
/* 801CAA5C 001C763C  80 9F 00 00 */    lwz r4, 0(r31)
/* 801CAA60 001C7640  38 1E 00 04 */    addi r0, r30, 4
/* 801CAA64 001C7644  7C 64 01 2E */    stwx r3, r4, r0
/* 801CAA68 001C7648  48 00 01 50 */    b grZakoGenerator_801CABB8
grZakoGenerator_801CAA6C:
/* 801CAA6C 001C764C  80 BB 00 00 */    lwz r5, 0(r27)
/* 801CAA70 001C7650  28 05 00 00 */    cmplwi r5, 0
/* 801CAA74 001C7654  41 82 01 44 */    beq grZakoGenerator_801CABB8
/* 801CAA78 001C7658  38 04 FF E0 */    addi r0, r4, -32
/* 801CAA7C 001C765C  54 04 10 3A */    slwi r4, r0, 2
/* 801CAA80 001C7660  7C 05 22 2E */    lhzx r0, r5, r4
/* 801CAA84 001C7664  2C 00 00 D3 */    cmpwi r0, 0xd3
/* 801CAA88 001C7668  41 82 00 B0 */    beq grZakoGenerator_801CAB38
/* 801CAA8C 001C766C  40 80 00 2C */    bge grZakoGenerator_801CAAB8
/* 801CAA90 001C7670  2C 00 00 2D */    cmpwi r0, 0x2d
/* 801CAA94 001C7674  41 82 00 6C */    beq grZakoGenerator_801CAB00
/* 801CAA98 001C7678  40 80 00 14 */    bge grZakoGenerator_801CAAAC
/* 801CAA9C 001C767C  2C 00 00 2B */    cmpwi r0, 0x2b
/* 801CAAA0 001C7680  41 82 00 34 */    beq grZakoGenerator_801CAAD4
/* 801CAAA4 001C7684  40 80 00 4C */    bge grZakoGenerator_801CAAF0
/* 801CAAA8 001C7688  48 00 00 F4 */    b grZakoGenerator_801CAB9C
grZakoGenerator_801CAAAC:
/* 801CAAAC 001C768C  2C 00 00 2F */    cmpwi r0, 0x2f
/* 801CAAB0 001C7690  40 80 00 EC */    bge grZakoGenerator_801CAB9C
/* 801CAAB4 001C7694  48 00 00 68 */    b grZakoGenerator_801CAB1C
grZakoGenerator_801CAAB8:
/* 801CAAB8 001C7698  2C 00 00 D9 */    cmpwi r0, 0xd9
/* 801CAABC 001C769C  41 82 00 C8 */    beq grZakoGenerator_801CAB84
/* 801CAAC0 001C76A0  40 80 00 DC */    bge grZakoGenerator_801CAB9C
/* 801CAAC4 001C76A4  2C 00 00 D5 */    cmpwi r0, 0xd5
/* 801CAAC8 001C76A8  41 82 00 A4 */    beq grZakoGenerator_801CAB6C
/* 801CAACC 001C76AC  40 80 00 D0 */    bge grZakoGenerator_801CAB9C
/* 801CAAD0 001C76B0  48 00 00 84 */    b grZakoGenerator_801CAB54
grZakoGenerator_801CAAD4:
/* 801CAAD4 001C76B4  38 81 00 10 */    addi r4, r1, 0x10
/* 801CAAD8 001C76B8  38 60 00 2B */    li r3, 0x2b
/* 801CAADC 001C76BC  38 A0 00 00 */    li r5, 0
/* 801CAAE0 001C76C0  38 C0 00 00 */    li r6, 0
/* 801CAAE4 001C76C4  38 E0 00 01 */    li r7, 1
/* 801CAAE8 001C76C8  48 0B 0A C9 */    bl func_8027B5B0
/* 801CAAEC 001C76CC  48 00 00 B0 */    b grZakoGenerator_801CAB9C
grZakoGenerator_801CAAF0:
/* 801CAAF0 001C76D0  38 61 00 10 */    addi r3, r1, 0x10
/* 801CAAF4 001C76D4  38 80 FF FF */    li r4, -1
/* 801CAAF8 001C76D8  48 11 FF 05 */    bl func_802EA9FC
/* 801CAAFC 001C76DC  48 00 00 A0 */    b grZakoGenerator_801CAB9C
grZakoGenerator_801CAB00:
/* 801CAB00 001C76E0  38 81 00 10 */    addi r4, r1, 0x10
/* 801CAB04 001C76E4  38 60 00 2D */    li r3, 0x2d
/* 801CAB08 001C76E8  38 A0 00 00 */    li r5, 0
/* 801CAB0C 001C76EC  38 C0 00 00 */    li r6, 0
/* 801CAB10 001C76F0  38 E0 00 01 */    li r7, 1
/* 801CAB14 001C76F4  48 0B 0A 9D */    bl func_8027B5B0
/* 801CAB18 001C76F8  48 00 00 84 */    b grZakoGenerator_801CAB9C
grZakoGenerator_801CAB1C:
/* 801CAB1C 001C76FC  38 81 00 10 */    addi r4, r1, 0x10
/* 801CAB20 001C7700  38 60 00 2E */    li r3, 0x2e
/* 801CAB24 001C7704  38 A0 00 00 */    li r5, 0
/* 801CAB28 001C7708  38 C0 00 00 */    li r6, 0
/* 801CAB2C 001C770C  38 E0 00 01 */    li r7, 1
/* 801CAB30 001C7710  48 0B 0A 81 */    bl func_8027B5B0
/* 801CAB34 001C7714  48 00 00 68 */    b grZakoGenerator_801CAB9C
grZakoGenerator_801CAB38:
/* 801CAB38 001C7718  38 04 00 02 */    addi r0, r4, 2
/* 801CAB3C 001C771C  7C 65 00 AE */    lbzx r3, r5, r0
/* 801CAB40 001C7720  38 81 00 10 */    addi r4, r1, 0x10
/* 801CAB44 001C7724  38 A0 00 00 */    li r5, 0
/* 801CAB48 001C7728  38 C0 FF FF */    li r6, -1
/* 801CAB4C 001C772C  48 11 2C A5 */    bl func_802DD7F0
/* 801CAB50 001C7730  48 00 00 4C */    b grZakoGenerator_801CAB9C
grZakoGenerator_801CAB54:
/* 801CAB54 001C7734  38 04 00 02 */    addi r0, r4, 2
/* 801CAB58 001C7738  7C 65 00 AE */    lbzx r3, r5, r0
/* 801CAB5C 001C773C  38 81 00 10 */    addi r4, r1, 0x10
/* 801CAB60 001C7740  38 A0 FF FF */    li r5, -1
/* 801CAB64 001C7744  48 11 6B 95 */    bl func_802E16F8
/* 801CAB68 001C7748  48 00 00 34 */    b grZakoGenerator_801CAB9C
grZakoGenerator_801CAB6C:
/* 801CAB6C 001C774C  38 04 00 02 */    addi r0, r4, 2
/* 801CAB70 001C7750  7C 65 00 AE */    lbzx r3, r5, r0
/* 801CAB74 001C7754  38 81 00 10 */    addi r4, r1, 0x10
/* 801CAB78 001C7758  38 A0 FF FF */    li r5, -1
/* 801CAB7C 001C775C  48 11 19 41 */    bl func_802DC4BC
/* 801CAB80 001C7760  48 00 00 1C */    b grZakoGenerator_801CAB9C
grZakoGenerator_801CAB84:
/* 801CAB84 001C7764  38 81 00 10 */    addi r4, r1, 0x10
/* 801CAB88 001C7768  38 60 00 D9 */    li r3, 0xd9
/* 801CAB8C 001C776C  38 A0 00 00 */    li r5, 0
/* 801CAB90 001C7770  38 C0 00 00 */    li r6, 0
/* 801CAB94 001C7774  38 E0 00 01 */    li r7, 1
/* 801CAB98 001C7778  48 0B 0A 19 */    bl func_8027B5B0
grZakoGenerator_801CAB9C:
/* 801CAB9C 001C777C  28 03 00 00 */    cmplwi r3, 0
/* 801CABA0 001C7780  41 82 00 18 */    beq grZakoGenerator_801CABB8
/* 801CABA4 001C7784  80 A3 00 2C */    lwz r5, 0x2c(r3)
/* 801CABA8 001C7788  38 1E 00 04 */    addi r0, r30, 4
/* 801CABAC 001C778C  80 9F 00 00 */    lwz r4, 0(r31)
/* 801CABB0 001C7790  7C 64 01 2E */    stwx r3, r4, r0
/* 801CABB4 001C7794  93 A5 0D D8 */    stw r29, 0xdd8(r5)
grZakoGenerator_801CABB8:
/* 801CABB8 001C7798  3B BD 00 01 */    addi r29, r29, 1
/* 801CABBC 001C779C  2C 1D 00 51 */    cmpwi r29, 0x51
/* 801CABC0 001C77A0  41 80 00 08 */    blt grZakoGenerator_801CABC8
/* 801CABC4 001C77A4  3B A0 00 00 */    li r29, 0
grZakoGenerator_801CABC8:
/* 801CABC8 001C77A8  7C 1D D0 00 */    cmpw r29, r26
/* 801CABCC 001C77AC  41 82 00 0C */    beq grZakoGenerator_801CABD8
/* 801CABD0 001C77B0  37 9C FF FF */    addic. r28, r28, -1
/* 801CABD4 001C77B4  41 81 FD A8 */    bgt grZakoGenerator_801CA97C
grZakoGenerator_801CABD8:
/* 801CABD8 001C77B8  7F A0 07 34 */    extsh r0, r29
/* 801CABDC 001C77BC  B0 18 00 00 */    sth r0, 0(r24)
grZakoGenerator_801CABE0:
/* 801CABE0 001C77C0  BB 01 00 20 */    lmw r24, 0x20(r1)
/* 801CABE4 001C77C4  80 01 00 84 */    lwz r0, 0x84(r1)
/* 801CABE8 001C77C8  CB E1 00 78 */    lfd f31, 0x78(r1)
/* 801CABEC 001C77CC  CB C1 00 70 */    lfd f30, 0x70(r1)
/* 801CABF0 001C77D0  CB A1 00 68 */    lfd f29, 0x68(r1)
/* 801CABF4 001C77D4  CB 81 00 60 */    lfd f28, 0x60(r1)
/* 801CABF8 001C77D8  CB 61 00 58 */    lfd f27, 0x58(r1)
/* 801CABFC 001C77DC  CB 41 00 50 */    lfd f26, 0x50(r1)
/* 801CAC00 001C77E0  CB 21 00 48 */    lfd f25, 0x48(r1)
/* 801CAC04 001C77E4  CB 01 00 40 */    lfd f24, 0x40(r1)
/* 801CAC08 001C77E8  38 21 00 80 */    addi r1, r1, 0x80
/* 801CAC0C 001C77EC  7C 08 03 A6 */    mtlr r0
/* 801CAC10 001C77F0  4E 80 00 20 */    blr

.global grZakoGenerator_801CAC14
grZakoGenerator_801CAC14:
/* 801CAC14 001C77F4  7C 08 02 A6 */    mflr r0
/* 801CAC18 001C77F8  90 01 00 04 */    stw r0, 4(r1)
/* 801CAC1C 001C77FC  94 21 FF E8 */    stwu r1, -0x18(r1)
/* 801CAC20 001C7800  93 E1 00 14 */    stw r31, 0x14(r1)
/* 801CAC24 001C7804  93 C1 00 10 */    stw r30, 0x10(r1)
/* 801CAC28 001C7808  7C 7E 1B 78 */    mr r30, r3
/* 801CAC2C 001C780C  83 E3 00 2C */    lwz r31, 0x2c(r3)
/* 801CAC30 001C7810  48 0A 06 D1 */    bl itGetKind
/* 801CAC34 001C7814  2C 03 00 9F */    cmpwi r3, 0x9f
/* 801CAC38 001C7818  40 82 00 2C */    bne grZakoGenerator_801CAC64
/* 801CAC3C 001C781C  3C 60 80 4A */    lis r3, lbl_8049F030@ha
/* 801CAC40 001C7820  38 63 F0 30 */    addi r3, r3, lbl_8049F030@l
/* 801CAC44 001C7824  80 63 00 04 */    lwz r3, 4(r3)
/* 801CAC48 001C7828  38 00 00 00 */    li r0, 0
/* 801CAC4C 001C782C  38 83 03 C4 */    addi r4, r3, 0x3c4
/* 801CAC50 001C7830  80 63 03 C4 */    lwz r3, 0x3c4(r3)
/* 801CAC54 001C7834  7C 03 F0 40 */    cmplw r3, r30
/* 801CAC58 001C7838  40 82 00 48 */    bne grZakoGenerator_801CACA0
/* 801CAC5C 001C783C  90 04 00 00 */    stw r0, 0(r4)
/* 801CAC60 001C7840  48 00 00 40 */    b grZakoGenerator_801CACA0
grZakoGenerator_801CAC64:
/* 801CAC64 001C7844  80 1F 0D D8 */    lwz r0, 0xdd8(r31)
/* 801CAC68 001C7848  2C 00 FF FF */    cmpwi r0, -1
/* 801CAC6C 001C784C  41 82 00 34 */    beq grZakoGenerator_801CACA0
/* 801CAC70 001C7850  3C 60 80 4A */    lis r3, lbl_8049F030@ha
/* 801CAC74 001C7854  38 63 F0 30 */    addi r3, r3, lbl_8049F030@l
/* 801CAC78 001C7858  38 C3 00 04 */    addi r6, r3, 4
/* 801CAC7C 001C785C  1C A0 00 0C */    mulli r5, r0, 0xc
/* 801CAC80 001C7860  80 03 00 04 */    lwz r0, 4(r3)
/* 801CAC84 001C7864  7C 60 2A 14 */    add r3, r0, r5
/* 801CAC88 001C7868  38 00 00 00 */    li r0, 0
/* 801CAC8C 001C786C  90 03 00 04 */    stw r0, 4(r3)
/* 801CAC90 001C7870  38 80 00 02 */    li r4, 2
/* 801CAC94 001C7874  80 06 00 00 */    lwz r0, 0(r6)
/* 801CAC98 001C7878  7C 60 2A 14 */    add r3, r0, r5
/* 801CAC9C 001C787C  B0 83 00 02 */    sth r4, 2(r3)
grZakoGenerator_801CACA0:
/* 801CACA0 001C7880  80 01 00 1C */    lwz r0, 0x1c(r1)
/* 801CACA4 001C7884  83 E1 00 14 */    lwz r31, 0x14(r1)
/* 801CACA8 001C7888  83 C1 00 10 */    lwz r30, 0x10(r1)
/* 801CACAC 001C788C  38 21 00 18 */    addi r1, r1, 0x18
/* 801CACB0 001C7890  7C 08 03 A6 */    mtlr r0
/* 801CACB4 001C7894  4E 80 00 20 */    blr

.global grZakoGenerator_801CACB8
grZakoGenerator_801CACB8:
/* 801CACB8 001C7898  7C 08 02 A6 */    mflr r0
/* 801CACBC 001C789C  3C 80 80 4A */    lis r4, lbl_8049F030@ha
/* 801CACC0 001C78A0  90 01 00 04 */    stw r0, 4(r1)
/* 801CACC4 001C78A4  94 21 FF E0 */    stwu r1, -0x20(r1)
/* 801CACC8 001C78A8  93 E1 00 1C */    stw r31, 0x1c(r1)
/* 801CACCC 001C78AC  93 C1 00 18 */    stw r30, 0x18(r1)
/* 801CACD0 001C78B0  93 A1 00 14 */    stw r29, 0x14(r1)
/* 801CACD4 001C78B4  3B A4 F0 30 */    addi r29, r4, lbl_8049F030@l
/* 801CACD8 001C78B8  93 81 00 10 */    stw r28, 0x10(r1)
/* 801CACDC 001C78BC  3B 83 00 00 */    addi r28, r3, 0
/* 801CACE0 001C78C0  83 E3 00 2C */    lwz r31, 0x2c(r3)
/* 801CACE4 001C78C4  48 0A 06 1D */    bl itGetKind
/* 801CACE8 001C78C8  3B C3 00 00 */    addi r30, r3, 0
/* 801CACEC 001C78CC  38 7C 00 00 */    addi r3, r28, 0
/* 801CACF0 001C78D0  48 0B 21 29 */    bl func_8027CE18
/* 801CACF4 001C78D4  2C 1E 00 9F */    cmpwi r30, 0x9f
/* 801CACF8 001C78D8  40 82 00 34 */    bne grZakoGenerator_801CAD2C
/* 801CACFC 001C78DC  38 DD 00 04 */    addi r6, r29, 4
/* 801CAD00 001C78E0  80 9D 00 04 */    lwz r4, 4(r29)
/* 801CAD04 001C78E4  38 60 FF FF */    li r3, -1
/* 801CAD08 001C78E8  38 00 00 00 */    li r0, 0
/* 801CAD0C 001C78EC  38 A4 03 C0 */    addi r5, r4, 0x3c0
/* 801CAD10 001C78F0  80 84 03 C4 */    lwz r4, 0x3c4(r4)
/* 801CAD14 001C78F4  7C 04 E0 40 */    cmplw r4, r28
/* 801CAD18 001C78F8  40 82 00 84 */    bne grZakoGenerator_801CAD9C
/* 801CAD1C 001C78FC  B0 65 00 00 */    sth r3, 0(r5)
/* 801CAD20 001C7900  80 66 00 00 */    lwz r3, 0(r6)
/* 801CAD24 001C7904  90 03 03 C4 */    stw r0, 0x3c4(r3)
/* 801CAD28 001C7908  48 00 00 74 */    b grZakoGenerator_801CAD9C
grZakoGenerator_801CAD2C:
/* 801CAD2C 001C790C  80 1F 0D D8 */    lwz r0, 0xdd8(r31)
/* 801CAD30 001C7910  2C 00 FF FF */    cmpwi r0, -1
/* 801CAD34 001C7914  41 82 00 68 */    beq grZakoGenerator_801CAD9C
/* 801CAD38 001C7918  38 DD 00 04 */    addi r6, r29, 4
/* 801CAD3C 001C791C  1C A0 00 0C */    mulli r5, r0, 0xc
/* 801CAD40 001C7920  80 7D 00 04 */    lwz r3, 4(r29)
/* 801CAD44 001C7924  7C 83 2A AE */    lhax r4, r3, r5
/* 801CAD48 001C7928  7C 63 2A 14 */    add r3, r3, r5
/* 801CAD4C 001C792C  38 00 00 00 */    li r0, 0
/* 801CAD50 001C7930  90 03 00 04 */    stw r0, 4(r3)
/* 801CAD54 001C7934  38 04 FF E0 */    addi r0, r4, -32
/* 801CAD58 001C7938  54 00 10 3A */    slwi r0, r0, 2
/* 801CAD5C 001C793C  80 7D 00 00 */    lwz r3, 0(r29)
/* 801CAD60 001C7940  7C 63 02 14 */    add r3, r3, r0
/* 801CAD64 001C7944  88 03 00 03 */    lbz r0, 3(r3)
/* 801CAD68 001C7948  28 00 00 01 */    cmplwi r0, 1
/* 801CAD6C 001C794C  40 82 00 18 */    bne grZakoGenerator_801CAD84
/* 801CAD70 001C7950  80 06 00 00 */    lwz r0, 0(r6)
/* 801CAD74 001C7954  38 80 07 08 */    li r4, 0x708
/* 801CAD78 001C7958  7C 60 2A 14 */    add r3, r0, r5
/* 801CAD7C 001C795C  B0 83 00 02 */    sth r4, 2(r3)
/* 801CAD80 001C7960  48 00 00 14 */    b grZakoGenerator_801CAD94
grZakoGenerator_801CAD84:
/* 801CAD84 001C7964  80 06 00 00 */    lwz r0, 0(r6)
/* 801CAD88 001C7968  38 80 FF FF */    li r4, -1
/* 801CAD8C 001C796C  7C 60 2A 14 */    add r3, r0, r5
/* 801CAD90 001C7970  B0 83 00 02 */    sth r4, 2(r3)
grZakoGenerator_801CAD94:
/* 801CAD94 001C7974  38 00 FF FF */    li r0, -1
/* 801CAD98 001C7978  90 1F 0D D8 */    stw r0, 0xdd8(r31)
grZakoGenerator_801CAD9C:
/* 801CAD9C 001C797C  80 01 00 24 */    lwz r0, 0x24(r1)
/* 801CADA0 001C7980  83 E1 00 1C */    lwz r31, 0x1c(r1)
/* 801CADA4 001C7984  83 C1 00 18 */    lwz r30, 0x18(r1)
/* 801CADA8 001C7988  83 A1 00 14 */    lwz r29, 0x14(r1)
/* 801CADAC 001C798C  83 81 00 10 */    lwz r28, 0x10(r1)
/* 801CADB0 001C7990  38 21 00 20 */    addi r1, r1, 0x20
/* 801CADB4 001C7994  7C 08 03 A6 */    mtlr r0
/* 801CADB8 001C7998  4E 80 00 20 */    blr
grZakoGenerator_801CADBC:
/* 801CADBC 001C799C  7C 08 02 A6 */    mflr r0
/* 801CADC0 001C79A0  38 60 00 00 */    li r3, 0
/* 801CADC4 001C79A4  90 01 00 04 */    stw r0, 4(r1)
/* 801CADC8 001C79A8  94 21 FF F8 */    stwu r1, -8(r1)
/* 801CADCC 001C79AC  4B FF FA E9 */    bl grZakoGenerator_801CA8B4
/* 801CADD0 001C79B0  80 01 00 0C */    lwz r0, 0xc(r1)
/* 801CADD4 001C79B4  38 21 00 08 */    addi r1, r1, 8
/* 801CADD8 001C79B8  7C 08 03 A6 */    mtlr r0
/* 801CADDC 001C79BC  4E 80 00 20 */    blr

.global grZakoGenerator_801CADE0
grZakoGenerator_801CADE0:
/* 801CADE0 001C79C0  7C 08 02 A6 */    mflr r0
/* 801CADE4 001C79C4  38 60 00 01 */    li r3, 1
/* 801CADE8 001C79C8  90 01 00 04 */    stw r0, 4(r1)
/* 801CADEC 001C79CC  94 21 FF F8 */    stwu r1, -8(r1)
/* 801CADF0 001C79D0  4B FF FA C5 */    bl grZakoGenerator_801CA8B4
/* 801CADF4 001C79D4  80 01 00 0C */    lwz r0, 0xc(r1)
/* 801CADF8 001C79D8  38 21 00 08 */    addi r1, r1, 8
/* 801CADFC 001C79DC  7C 08 03 A6 */    mtlr r0
/* 801CAE00 001C79E0  4E 80 00 20 */    blr

.global grZakoGenerator_801CAE04
grZakoGenerator_801CAE04:
/* 801CAE04 001C79E4  7C 08 02 A6 */    mflr r0
/* 801CAE08 001C79E8  90 01 00 04 */    stw r0, 4(r1)
/* 801CAE0C 001C79EC  94 21 FF E0 */    stwu r1, -0x20(r1)
/* 801CAE10 001C79F0  93 E1 00 1C */    stw r31, 0x1c(r1)
/* 801CAE14 001C79F4  93 C1 00 18 */    stw r30, 0x18(r1)
/* 801CAE18 001C79F8  93 A1 00 14 */    stw r29, 0x14(r1)
/* 801CAE1C 001C79FC  7C 7D 1B 78 */    mr r29, r3
/* 801CAE20 001C7A00  4B FF F8 5D */    bl grZakoGenerator_801CA67C
/* 801CAE24 001C7A04  3B C3 00 00 */    addi r30, r3, 0
/* 801CAE28 001C7A08  38 60 00 02 */    li r3, 2
/* 801CAE2C 001C7A0C  38 80 00 04 */    li r4, 4
/* 801CAE30 001C7A10  38 A0 00 00 */    li r5, 0
/* 801CAE34 001C7A14  48 1C 53 BD */    bl GObj_Create
/* 801CAE38 001C7A18  7C 7F 1B 79 */    or. r31, r3, r3
/* 801CAE3C 001C7A1C  40 82 00 30 */    bne grZakoGenerator_801CAE6C
/* 801CAE40 001C7A20  3C 60 80 3E */    lis r3, lbl_803E0BBC@ha
/* 801CAE44 001C7A24  4C C6 31 82 */    crclr 6
/* 801CAE48 001C7A28  3C 80 80 3E */    lis r4, lbl_803E0BA8@ha
/* 801CAE4C 001C7A2C  38 63 0B BC */    addi r3, r3, lbl_803E0BBC@l
/* 801CAE50 001C7A30  38 84 0B A8 */    addi r4, r4, lbl_803E0BA8@l
/* 801CAE54 001C7A34  38 A0 01 66 */    li r5, 0x166
/* 801CAE58 001C7A38  48 17 A8 51 */    bl OSReport
/* 801CAE5C 001C7A3C  7F C3 F3 78 */    mr r3, r30
/* 801CAE60 001C7A40  48 1B 43 51 */    bl HSD_Free
/* 801CAE64 001C7A44  38 60 00 00 */    li r3, 0
/* 801CAE68 001C7A48  48 00 00 2C */    b grZakoGenerator_801CAE94
grZakoGenerator_801CAE6C:
/* 801CAE6C 001C7A4C  3C 60 80 1D */    lis r3, grZakoGenerator_801CADBC@ha
/* 801CAE70 001C7A50  38 83 AD BC */    addi r4, r3, grZakoGenerator_801CADBC@l
/* 801CAE74 001C7A54  38 7F 00 00 */    addi r3, r31, 0
/* 801CAE78 001C7A58  38 A0 00 00 */    li r5, 0
/* 801CAE7C 001C7A5C  48 1C 4E D9 */    bl func_8038FD54
/* 801CAE80 001C7A60  3C 60 80 4A */    lis r3, lbl_8049F030@ha
/* 801CAE84 001C7A64  38 83 F0 30 */    addi r4, r3, lbl_8049F030@l
/* 801CAE88 001C7A68  93 A4 00 00 */    stw r29, 0(r4)
/* 801CAE8C 001C7A6C  7F E3 FB 78 */    mr r3, r31
/* 801CAE90 001C7A70  93 C4 00 04 */    stw r30, 4(r4)
grZakoGenerator_801CAE94:
/* 801CAE94 001C7A74  80 01 00 24 */    lwz r0, 0x24(r1)
/* 801CAE98 001C7A78  83 E1 00 1C */    lwz r31, 0x1c(r1)
/* 801CAE9C 001C7A7C  83 C1 00 18 */    lwz r30, 0x18(r1)
/* 801CAEA0 001C7A80  83 A1 00 14 */    lwz r29, 0x14(r1)
/* 801CAEA4 001C7A84  38 21 00 20 */    addi r1, r1, 0x20
/* 801CAEA8 001C7A88  7C 08 03 A6 */    mtlr r0
/* 801CAEAC 001C7A8C  4E 80 00 20 */    blr

.global grZakoGenerator_801CAEB0
grZakoGenerator_801CAEB0:
/* 801CAEB0 001C7A90  3C A0 80 4A */    lis r5, lbl_8049F030@ha
/* 801CAEB4 001C7A94  38 A5 F0 30 */    addi r5, r5, lbl_8049F030@l
/* 801CAEB8 001C7A98  38 E5 00 04 */    addi r7, r5, 4
/* 801CAEBC 001C7A9C  80 A5 00 04 */    lwz r5, 4(r5)
/* 801CAEC0 001C7AA0  7C 84 07 34 */    extsh r4, r4
/* 801CAEC4 001C7AA4  38 00 00 00 */    li r0, 0
/* 801CAEC8 001C7AA8  38 C5 03 C0 */    addi r6, r5, 0x3c0
/* 801CAECC 001C7AAC  A8 A5 03 C0 */    lha r5, 0x3c0(r5)
/* 801CAED0 001C7AB0  2C 05 FF FF */    cmpwi r5, -1
/* 801CAED4 001C7AB4  4C 82 00 20 */    bnelr
/* 801CAED8 001C7AB8  B0 86 00 00 */    sth r4, 0(r6)
/* 801CAEDC 001C7ABC  80 87 00 00 */    lwz r4, 0(r7)
/* 801CAEE0 001C7AC0  90 64 03 C8 */    stw r3, 0x3c8(r4)
/* 801CAEE4 001C7AC4  80 67 00 00 */    lwz r3, 0(r7)
/* 801CAEE8 001C7AC8  90 03 03 C4 */    stw r0, 0x3c4(r3)
/* 801CAEEC 001C7ACC  4E 80 00 20 */    blr

.global grZakoGenerator_801CAEF0
grZakoGenerator_801CAEF0:
/* 801CAEF0 001C7AD0  3C 80 80 4A */    lis r4, lbl_8049F030@ha
/* 801CAEF4 001C7AD4  38 84 F0 30 */    addi r4, r4, lbl_8049F030@l
/* 801CAEF8 001C7AD8  88 04 00 0A */    lbz r0, 0xa(r4)
/* 801CAEFC 001C7ADC  50 60 3E 30 */    rlwimi r0, r3, 7, 0x18, 0x18
/* 801CAF00 001C7AE0  98 04 00 0A */    stb r0, 0xa(r4)
/* 801CAF04 001C7AE4  4E 80 00 20 */    blr

.global grZakoGenerator_801CAF08
grZakoGenerator_801CAF08:
/* 801CAF08 001C7AE8  7C 08 02 A6 */    mflr r0
/* 801CAF0C 001C7AEC  3C 60 80 4A */    lis r3, lbl_8049F030@ha
/* 801CAF10 001C7AF0  90 01 00 04 */    stw r0, 4(r1)
/* 801CAF14 001C7AF4  38 63 F0 30 */    addi r3, r3, lbl_8049F030@l
/* 801CAF18 001C7AF8  38 80 00 00 */    li r4, 0
/* 801CAF1C 001C7AFC  94 21 FF E8 */    stwu r1, -0x18(r1)
/* 801CAF20 001C7B00  93 E1 00 14 */    stw r31, 0x14(r1)
/* 801CAF24 001C7B04  93 C1 00 10 */    stw r30, 0x10(r1)
/* 801CAF28 001C7B08  88 03 00 0A */    lbz r0, 0xa(r3)
/* 801CAF2C 001C7B0C  50 80 3E 30 */    rlwimi r0, r4, 7, 0x18, 0x18
/* 801CAF30 001C7B10  98 03 00 0A */    stb r0, 0xa(r3)
/* 801CAF34 001C7B14  80 6D C1 8C */    lwz r3, lbl_804D782C@sda21(r13)
/* 801CAF38 001C7B18  83 C3 00 24 */    lwz r30, 0x24(r3)
/* 801CAF3C 001C7B1C  48 00 00 60 */    b grZakoGenerator_801CAF9C
grZakoGenerator_801CAF40:
/* 801CAF40 001C7B20  83 FE 00 08 */    lwz r31, 8(r30)
/* 801CAF44 001C7B24  7F C3 F3 78 */    mr r3, r30
/* 801CAF48 001C7B28  48 0A 03 B9 */    bl itGetKind
/* 801CAF4C 001C7B2C  2C 03 00 2B */    cmpwi r3, 0x2b
/* 801CAF50 001C7B30  41 80 00 0C */    blt grZakoGenerator_801CAF5C
/* 801CAF54 001C7B34  2C 03 00 30 */    cmpwi r3, 0x30
/* 801CAF58 001C7B38  41 80 00 14 */    blt grZakoGenerator_801CAF6C
grZakoGenerator_801CAF5C:
/* 801CAF5C 001C7B3C  2C 03 00 D0 */    cmpwi r3, 0xd0
/* 801CAF60 001C7B40  41 80 00 28 */    blt grZakoGenerator_801CAF88
/* 801CAF64 001C7B44  2C 03 00 E8 */    cmpwi r3, 0xe8
/* 801CAF68 001C7B48  40 80 00 20 */    bge grZakoGenerator_801CAF88
grZakoGenerator_801CAF6C:
/* 801CAF6C 001C7B4C  7F C3 F3 78 */    mr r3, r30
/* 801CAF70 001C7B50  48 0A 12 79 */    bl func_8026C1E8
/* 801CAF74 001C7B54  2C 03 00 00 */    cmpwi r3, 0
/* 801CAF78 001C7B58  41 82 00 20 */    beq grZakoGenerator_801CAF98
/* 801CAF7C 001C7B5C  7F C3 F3 78 */    mr r3, r30
/* 801CAF80 001C7B60  48 09 F9 6D */    bl func_8026A8EC
/* 801CAF84 001C7B64  48 00 00 14 */    b grZakoGenerator_801CAF98
grZakoGenerator_801CAF88:
/* 801CAF88 001C7B68  2C 03 00 9F */    cmpwi r3, 0x9f
/* 801CAF8C 001C7B6C  40 82 00 0C */    bne grZakoGenerator_801CAF98
/* 801CAF90 001C7B70  7F C3 F3 78 */    mr r3, r30
/* 801CAF94 001C7B74  48 09 F9 59 */    bl func_8026A8EC
grZakoGenerator_801CAF98:
/* 801CAF98 001C7B78  7F FE FB 78 */    mr r30, r31
grZakoGenerator_801CAF9C:
/* 801CAF9C 001C7B7C  28 1E 00 00 */    cmplwi r30, 0
/* 801CAFA0 001C7B80  40 82 FF A0 */    bne grZakoGenerator_801CAF40
/* 801CAFA4 001C7B84  80 01 00 1C */    lwz r0, 0x1c(r1)
/* 801CAFA8 001C7B88  83 E1 00 14 */    lwz r31, 0x14(r1)
/* 801CAFAC 001C7B8C  83 C1 00 10 */    lwz r30, 0x10(r1)
/* 801CAFB0 001C7B90  38 21 00 18 */    addi r1, r1, 0x18
/* 801CAFB4 001C7B94  7C 08 03 A6 */    mtlr r0
/* 801CAFB8 001C7B98  4E 80 00 20 */    blr


.section .bss
    .balign 8
lbl_8049F030:
    .skip 0x10


.section .data
    .balign 8
lbl_803E0BA8:
    .asciz "grzakogenerator.c"
    .balign 4
lbl_803E0BBC:
    .asciz "%s:%d: couldn t get gobj!\n"


.section .sdata
    .balign 8
lbl_804D4590:
    .asciz "pointp"


.section .sdata2
    .balign 8
lbl_804DADA8:
    .float 0
lbl_804DADAC:
    .float 0.0001
lbl_804DADB0:
    .float 0.5
