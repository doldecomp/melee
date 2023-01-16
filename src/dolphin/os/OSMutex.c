#include <dolphin/os/OSMutex.h>

#include <placeholder.h>

void __OSUnlockAllMutex(OSThread* thread)
{
    while (thread->mutexQueue.head != NULL) {
        OSMutex* head = thread->mutexQueue.head;
        OSMutex* next = head->link.next;

        if (next == NULL)
            thread->mutexQueue.tail = NULL;
        else
            next->link.prev = NULL;
        thread->mutexQueue.head = next;
        head->lock = 0;
        head->thread = NULL;
        OSWakeupThread(&head->queue);
    }
}

#ifdef MWERKS_GEKKO

#pragma push
asm void __OSCheckMutex(void)
{ // clang-format off
    nofralloc
/* 80347F4C 00344B2C  80 83 00 00 */	lwz r4, 0(r3)
/* 80347F50 00344B30  38 E0 00 00 */	li r7, 0
/* 80347F54 00344B34  28 04 00 00 */	cmplwi r4, 0
/* 80347F58 00344B38  41 82 00 18 */	beq lbl_80347F70
/* 80347F5C 00344B3C  80 04 02 E4 */	lwz r0, 0x2e4(r4)
/* 80347F60 00344B40  28 00 00 00 */	cmplwi r0, 0
/* 80347F64 00344B44  41 82 00 0C */	beq lbl_80347F70
/* 80347F68 00344B48  38 60 00 00 */	li r3, 0
/* 80347F6C 00344B4C  4E 80 00 20 */	blr
lbl_80347F70:
/* 80347F70 00344B50  80 A3 00 04 */	lwz r5, 4(r3)
/* 80347F74 00344B54  28 05 00 00 */	cmplwi r5, 0
/* 80347F78 00344B58  41 82 00 18 */	beq lbl_80347F90
/* 80347F7C 00344B5C  80 05 02 E0 */	lwz r0, 0x2e0(r5)
/* 80347F80 00344B60  28 00 00 00 */	cmplwi r0, 0
/* 80347F84 00344B64  41 82 00 0C */	beq lbl_80347F90
/* 80347F88 00344B68  38 60 00 00 */	li r3, 0
/* 80347F8C 00344B6C  4E 80 00 20 */	blr
lbl_80347F90:
/* 80347F90 00344B70  7C 86 23 78 */	mr r6, r4
/* 80347F94 00344B74  48 00 00 74 */	b lbl_80348008
lbl_80347F98:
/* 80347F98 00344B78  80 86 02 E0 */	lwz r4, 0x2e0(r6)
/* 80347F9C 00344B7C  28 04 00 00 */	cmplwi r4, 0
/* 80347FA0 00344B80  41 82 00 18 */	beq lbl_80347FB8
/* 80347FA4 00344B84  80 04 02 E4 */	lwz r0, 0x2e4(r4)
/* 80347FA8 00344B88  7C 06 00 40 */	cmplw r6, r0
/* 80347FAC 00344B8C  41 82 00 0C */	beq lbl_80347FB8
/* 80347FB0 00344B90  38 60 00 00 */	li r3, 0
/* 80347FB4 00344B94  4E 80 00 20 */	blr
lbl_80347FB8:
/* 80347FB8 00344B98  80 A6 02 E4 */	lwz r5, 0x2e4(r6)
/* 80347FBC 00344B9C  28 05 00 00 */	cmplwi r5, 0
/* 80347FC0 00344BA0  41 82 00 18 */	beq lbl_80347FD8
/* 80347FC4 00344BA4  80 05 02 E0 */	lwz r0, 0x2e0(r5)
/* 80347FC8 00344BA8  7C 06 00 40 */	cmplw r6, r0
/* 80347FCC 00344BAC  41 82 00 0C */	beq lbl_80347FD8
/* 80347FD0 00344BB0  38 60 00 00 */	li r3, 0
/* 80347FD4 00344BB4  4E 80 00 20 */	blr
lbl_80347FD8:
/* 80347FD8 00344BB8  A0 06 02 C8 */	lhz r0, 0x2c8(r6)
/* 80347FDC 00344BBC  28 00 00 04 */	cmplwi r0, 4
/* 80347FE0 00344BC0  41 82 00 0C */	beq lbl_80347FEC
/* 80347FE4 00344BC4  38 60 00 00 */	li r3, 0
/* 80347FE8 00344BC8  4E 80 00 20 */	blr
lbl_80347FEC:
/* 80347FEC 00344BCC  80 06 02 D0 */	lwz r0, 0x2d0(r6)
/* 80347FF0 00344BD0  7C 00 38 00 */	cmpw r0, r7
/* 80347FF4 00344BD4  40 80 00 0C */	bge lbl_80348000
/* 80347FF8 00344BD8  38 60 00 00 */	li r3, 0
/* 80347FFC 00344BDC  4E 80 00 20 */	blr
lbl_80348000:
/* 80348000 00344BE0  7C 07 03 78 */	mr r7, r0
/* 80348004 00344BE4  38 C4 00 00 */	addi r6, r4, 0
lbl_80348008:
/* 80348008 00344BE8  28 06 00 00 */	cmplwi r6, 0
/* 8034800C 00344BEC  40 82 FF 8C */	bne lbl_80347F98
/* 80348010 00344BF0  80 03 00 08 */	lwz r0, 8(r3)
/* 80348014 00344BF4  28 00 00 00 */	cmplwi r0, 0
/* 80348018 00344BF8  41 82 00 18 */	beq lbl_80348030
/* 8034801C 00344BFC  80 03 00 0C */	lwz r0, 0xc(r3)
/* 80348020 00344C00  2C 00 00 00 */	cmpwi r0, 0
/* 80348024 00344C04  41 81 00 20 */	bgt lbl_80348044
/* 80348028 00344C08  38 60 00 00 */	li r3, 0
/* 8034802C 00344C0C  4E 80 00 20 */	blr
lbl_80348030:
/* 80348030 00344C10  80 03 00 0C */	lwz r0, 0xc(r3)
/* 80348034 00344C14  2C 00 00 00 */	cmpwi r0, 0
/* 80348038 00344C18  41 82 00 0C */	beq lbl_80348044
/* 8034803C 00344C1C  38 60 00 00 */	li r3, 0
/* 80348040 00344C20  4E 80 00 20 */	blr
lbl_80348044:
/* 80348044 00344C24  38 60 00 01 */	li r3, 1
/* 80348048 00344C28  4E 80 00 20 */	blr
} // clang-format on
#pragma pop

#else

void __OSCheckMutex(void)
{
    NOT_IMPLEMENTED;
}

#endif

#ifdef MWERKS_GEKKO

#pragma push
asm void __OSCheckDeadLock(void)
{ // clang-format off
    nofralloc
/* 8034804C 00344C2C  80 83 02 F0 */	lwz r4, 0x2f0(r3)
/* 80348050 00344C30  48 00 00 18 */	b lbl_80348068
lbl_80348054:
/* 80348054 00344C34  7C 04 18 40 */	cmplw r4, r3
/* 80348058 00344C38  40 82 00 0C */	bne lbl_80348064
/* 8034805C 00344C3C  38 60 00 01 */	li r3, 1
/* 80348060 00344C40  4E 80 00 20 */	blr
lbl_80348064:
/* 80348064 00344C44  80 84 02 F0 */	lwz r4, 0x2f0(r4)
lbl_80348068:
/* 80348068 00344C48  28 04 00 00 */	cmplwi r4, 0
/* 8034806C 00344C4C  41 82 00 10 */	beq lbl_8034807C
/* 80348070 00344C50  80 84 00 08 */	lwz r4, 8(r4)
/* 80348074 00344C54  28 04 00 00 */	cmplwi r4, 0
/* 80348078 00344C58  40 82 FF DC */	bne lbl_80348054
lbl_8034807C:
/* 8034807C 00344C5C  38 60 00 00 */	li r3, 0
/* 80348080 00344C60  4E 80 00 20 */	blr
} // clang-format on
#pragma pop

#else

void __OSCheckDeadLock(void)
{
    NOT_IMPLEMENTED;
}

#endif

#ifdef MWERKS_GEKKO

#pragma push
asm void __OSCheckMutexes(void)
{ // clang-format off
    nofralloc
/* 80348084 00344C64  7C 08 02 A6 */	mflr r0
/* 80348088 00344C68  90 01 00 04 */	stw r0, 4(r1)
/* 8034808C 00344C6C  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 80348090 00344C70  93 E1 00 14 */	stw r31, 0x14(r1)
/* 80348094 00344C74  93 C1 00 10 */	stw r30, 0x10(r1)
/* 80348098 00344C78  7C 7E 1B 78 */	mr r30, r3
/* 8034809C 00344C7C  83 E3 02 F4 */	lwz r31, 0x2f4(r3)
/* 803480A0 00344C80  48 00 00 34 */	b lbl_803480D4
lbl_803480A4:
/* 803480A4 00344C84  80 1F 00 08 */	lwz r0, 8(r31)
/* 803480A8 00344C88  7C 00 F0 40 */	cmplw r0, r30
/* 803480AC 00344C8C  41 82 00 0C */	beq lbl_803480B8
/* 803480B0 00344C90  38 60 00 00 */	li r3, 0
/* 803480B4 00344C94  48 00 00 2C */	b lbl_803480E0
lbl_803480B8:
/* 803480B8 00344C98  7F E3 FB 78 */	mr r3, r31
/* 803480BC 00344C9C  4B FF FE 91 */	bl __OSCheckMutex
/* 803480C0 00344CA0  2C 03 00 00 */	cmpwi r3, 0
/* 803480C4 00344CA4  40 82 00 0C */	bne lbl_803480D0
/* 803480C8 00344CA8  38 60 00 00 */	li r3, 0
/* 803480CC 00344CAC  48 00 00 14 */	b lbl_803480E0
lbl_803480D0:
/* 803480D0 00344CB0  83 FF 00 10 */	lwz r31, 0x10(r31)
lbl_803480D4:
/* 803480D4 00344CB4  28 1F 00 00 */	cmplwi r31, 0
/* 803480D8 00344CB8  40 82 FF CC */	bne lbl_803480A4
/* 803480DC 00344CBC  38 60 00 01 */	li r3, 1
lbl_803480E0:
/* 803480E0 00344CC0  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 803480E4 00344CC4  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 803480E8 00344CC8  83 C1 00 10 */	lwz r30, 0x10(r1)
/* 803480EC 00344CCC  7C 08 03 A6 */	mtlr r0
/* 803480F0 00344CD0  38 21 00 18 */	addi r1, r1, 0x18
/* 803480F4 00344CD4  4E 80 00 20 */	blr
} // clang-format on
#pragma pop

#else

void __OSCheckMutexes(void)
{
    NOT_IMPLEMENTED;
}

#endif
