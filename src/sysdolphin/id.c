#include "id.h"

extern HSD_ObjAllocData lbl_804C23C0; // hsd_iddata

extern struct _HSD_IDTable lbl_804C23EC; // default_table

extern char* lbl_804D5EE8; // "id.c"
extern char* lbl_804D5EF0;

HSD_ObjAllocData* HSD_IDGetAllocData(void)
{
    return &lbl_804C23C0;
}

void HSD_IDInitAllocData(void)
{
    HSD_ObjAllocInit(&lbl_804C23C0, sizeof(IDEntry), 4);
}

void HSD_IDSetup(void)
{
    memset(&lbl_804C23EC, 0, 0x194); // The partial memset doesn't quite make sense, but it matches
}

#ifdef NON_MATCHING
void HSD_IDInsertToTable(HSD_IDTable* table, u32 id, void* data)
{
    IDEntry* entry;
    u32 hash_key;

    if (table == NULL) {
        table = &lbl_804C23EC;
    }

    hash_key = hash(id);
    entry = &table->table[hash_key];

    while (entry != NULL && entry->id != id) {
        entry = entry->next;
    }

    if (entry == NULL) {
        entry = HSD_ObjAlloc(&lbl_804C23C0);
        if (entry == NULL) {
            __assert(lbl_804D5EE8, 67, lbl_804D5EF0);
        }
        entry->id = id;
        entry->data = data;
        entry->next = &table->table[hash_key];
        table->table[hash_key].next = entry;
    } else {
        entry->id = id;
        entry->data = data;
    }
}
#else
asm void HSD_IDInsertToTable(HSD_IDTable* table, u32 id, void* data)
{
    nofralloc
/* 8037CDEC 003799CC  7C 08 02 A6 */	mflr r0
/* 8037CDF0 003799D0  28 03 00 00 */	cmplwi r3, 0
/* 8037CDF4 003799D4  90 01 00 04 */	stw r0, 4(r1)
/* 8037CDF8 003799D8  94 21 FF C8 */	stwu r1, -0x38(r1)
/* 8037CDFC 003799DC  93 E1 00 34 */	stw r31, 0x34(r1)
/* 8037CE00 003799E0  3B E5 00 00 */	addi r31, r5, 0
/* 8037CE04 003799E4  93 C1 00 30 */	stw r30, 0x30(r1)
/* 8037CE08 003799E8  3B C4 00 00 */	addi r30, r4, 0
/* 8037CE0C 003799EC  93 A1 00 2C */	stw r29, 0x2c(r1)
/* 8037CE10 003799F0  93 81 00 28 */	stw r28, 0x28(r1)
/* 8037CE14 003799F4  40 82 00 0C */	bne lbl_8037CE20
/* 8037CE18 003799F8  3C 60 80 4C */	lis r3, lbl_804C23EC@ha
/* 8037CE1C 003799FC  38 63 23 EC */	addi r3, r3, lbl_804C23EC@l
lbl_8037CE20:
/* 8037CE20 00379A00  3C 80 44 70 */	lis r4, 0x4470
/* 8037CE24 00379A04  38 04 86 57 */	addi r0, r4, -0x79A9
/* 8037CE28 00379A08  7C 80 F0 16 */	mulhwu r4, r0, r30
/* 8037CE2C 00379A0C  7C 04 F0 50 */	subf r0, r4, r30
/* 8037CE30 00379A10  54 00 F8 7E */	srwi r0, r0, 1
/* 8037CE34 00379A14  7C 00 22 14 */	add r0, r0, r4
/* 8037CE38 00379A18  54 00 D1 BE */	srwi r0, r0, 6
/* 8037CE3C 00379A1C  1C 00 00 65 */	mulli r0, r0, 0x65
/* 8037CE40 00379A20  7C 00 F0 50 */	subf r0, r0, r30
/* 8037CE44 00379A24  54 00 10 3A */	slwi r0, r0, 2
/* 8037CE48 00379A28  7F 83 02 14 */	add r28, r3, r0
/* 8037CE4C 00379A2C  80 7C 00 00 */	lwz r3, 0(r28)
/* 8037CE50 00379A30  48 00 00 14 */	b lbl_8037CE64
lbl_8037CE54:
/* 8037CE54 00379A34  80 03 00 04 */	lwz r0, 4(r3)
/* 8037CE58 00379A38  7C 00 F0 40 */	cmplw r0, r30
/* 8037CE5C 00379A3C  41 82 00 10 */	beq lbl_8037CE6C
/* 8037CE60 00379A40  80 63 00 00 */	lwz r3, 0(r3)
lbl_8037CE64:
/* 8037CE64 00379A44  28 03 00 00 */	cmplwi r3, 0
/* 8037CE68 00379A48  40 82 FF EC */	bne lbl_8037CE54
lbl_8037CE6C:
/* 8037CE6C 00379A4C  28 03 00 00 */	cmplwi r3, 0
/* 8037CE70 00379A50  41 82 00 10 */	beq lbl_8037CE80
/* 8037CE74 00379A54  93 C3 00 04 */	stw r30, 4(r3)
/* 8037CE78 00379A58  93 E3 00 08 */	stw r31, 8(r3)
/* 8037CE7C 00379A5C  48 00 00 4C */	b lbl_8037CEC8
lbl_8037CE80:
/* 8037CE80 00379A60  3C 60 80 4C */	lis r3, lbl_804C23C0@ha
/* 8037CE84 00379A64  38 63 23 C0 */	addi r3, r3, lbl_804C23C0@l
/* 8037CE88 00379A68  4B FF DD 41 */	bl HSD_ObjAlloc
/* 8037CE8C 00379A6C  7C 7D 1B 79 */	or. r29, r3, r3
/* 8037CE90 00379A70  40 82 00 14 */	bne lbl_8037CEA4
/* 8037CE94 00379A74  38 6D A8 48 */	addi r3, r13, lbl_804D5EE8
/* 8037CE98 00379A78  38 80 00 43 */	li r4, 0x43
/* 8037CE9C 00379A7C  38 AD A8 50 */	addi r5, r13, lbl_804D5EF0
/* 8037CEA0 00379A80  48 00 B3 81 */	bl __assert
lbl_8037CEA4:
/* 8037CEA4 00379A84  38 7D 00 00 */	addi r3, r29, 0
/* 8037CEA8 00379A88  38 80 00 00 */	li r4, 0
/* 8037CEAC 00379A8C  38 A0 00 0C */	li r5, 0xc
/* 8037CEB0 00379A90  4B C8 62 51 */	bl memset
/* 8037CEB4 00379A94  93 DD 00 04 */	stw r30, 4(r29)
/* 8037CEB8 00379A98  93 FD 00 08 */	stw r31, 8(r29)
/* 8037CEBC 00379A9C  80 1C 00 00 */	lwz r0, 0(r28)
/* 8037CEC0 00379AA0  90 1D 00 00 */	stw r0, 0(r29)
/* 8037CEC4 00379AA4  93 BC 00 00 */	stw r29, 0(r28)
lbl_8037CEC8:
/* 8037CEC8 00379AA8  80 01 00 3C */	lwz r0, 0x3c(r1)
/* 8037CECC 00379AAC  83 E1 00 34 */	lwz r31, 0x34(r1)
/* 8037CED0 00379AB0  83 C1 00 30 */	lwz r30, 0x30(r1)
/* 8037CED4 00379AB4  83 A1 00 2C */	lwz r29, 0x2c(r1)
/* 8037CED8 00379AB8  83 81 00 28 */	lwz r28, 0x28(r1)
/* 8037CEDC 00379ABC  38 21 00 38 */	addi r1, r1, 0x38
/* 8037CEE0 00379AC0  7C 08 03 A6 */	mtlr r0
/* 8037CEE4 00379AC4  4E 80 00 20 */	blr 
}
#endif

asm void HSD_IDRemoveByIDFromTable(HSD_IDTable* table, u32 id)
{
    nofralloc
/* 8037CEE8 00379AC8  7C 08 02 A6 */	mflr r0
/* 8037CEEC 00379ACC  28 03 00 00 */	cmplwi r3, 0
/* 8037CEF0 00379AD0  90 01 00 04 */	stw r0, 4(r1)
/* 8037CEF4 00379AD4  94 21 FF F8 */	stwu r1, -8(r1)
/* 8037CEF8 00379AD8  40 82 00 0C */	bne lbl_8037CF04
/* 8037CEFC 00379ADC  3C 60 80 4C */	lis r3, lbl_804C23EC@ha
/* 8037CF00 00379AE0  38 63 23 EC */	addi r3, r3, lbl_804C23EC@l
lbl_8037CF04:
/* 8037CF04 00379AE4  3C A0 44 70 */	lis r5, 0x4470
/* 8037CF08 00379AE8  38 05 86 57 */	addi r0, r5, -0x79A9
/* 8037CF0C 00379AEC  7C A0 20 16 */	mulhwu r5, r0, r4
/* 8037CF10 00379AF0  7C 05 20 50 */	subf r0, r5, r4
/* 8037CF14 00379AF4  54 00 F8 7E */	srwi r0, r0, 1
/* 8037CF18 00379AF8  7C 00 2A 14 */	add r0, r0, r5
/* 8037CF1C 00379AFC  54 00 D1 BE */	srwi r0, r0, 6
/* 8037CF20 00379B00  1C 00 00 65 */	mulli r0, r0, 0x65
/* 8037CF24 00379B04  7C 00 20 50 */	subf r0, r0, r4
/* 8037CF28 00379B08  54 00 10 3A */	slwi r0, r0, 2
/* 8037CF2C 00379B0C  7C 63 02 14 */	add r3, r3, r0
/* 8037CF30 00379B10  80 A3 00 00 */	lwz r5, 0(r3)
/* 8037CF34 00379B14  38 C0 00 00 */	li r6, 0
/* 8037CF38 00379B18  48 00 00 48 */	b lbl_8037CF80
lbl_8037CF3C:
/* 8037CF3C 00379B1C  80 05 00 04 */	lwz r0, 4(r5)
/* 8037CF40 00379B20  7C 00 20 40 */	cmplw r0, r4
/* 8037CF44 00379B24  40 82 00 34 */	bne lbl_8037CF78
/* 8037CF48 00379B28  28 06 00 00 */	cmplwi r6, 0
/* 8037CF4C 00379B2C  41 82 00 10 */	beq lbl_8037CF5C
/* 8037CF50 00379B30  80 05 00 00 */	lwz r0, 0(r5)
/* 8037CF54 00379B34  90 06 00 00 */	stw r0, 0(r6)
/* 8037CF58 00379B38  48 00 00 0C */	b lbl_8037CF64
lbl_8037CF5C:
/* 8037CF5C 00379B3C  80 05 00 00 */	lwz r0, 0(r5)
/* 8037CF60 00379B40  90 03 00 00 */	stw r0, 0(r3)
lbl_8037CF64:
/* 8037CF64 00379B44  3C 60 80 4C */	lis r3, lbl_804C23C0@ha
/* 8037CF68 00379B48  38 63 23 C0 */	addi r3, r3, lbl_804C23C0@l
/* 8037CF6C 00379B4C  38 85 00 00 */	addi r4, r5, 0
/* 8037CF70 00379B50  4B FF DD B1 */	bl HSD_ObjFree
/* 8037CF74 00379B54  48 00 00 14 */	b lbl_8037CF88
lbl_8037CF78:
/* 8037CF78 00379B58  7C A6 2B 78 */	mr r6, r5
/* 8037CF7C 00379B5C  80 A5 00 00 */	lwz r5, 0(r5)
lbl_8037CF80:
/* 8037CF80 00379B60  28 05 00 00 */	cmplwi r5, 0
/* 8037CF84 00379B64  40 82 FF B8 */	bne lbl_8037CF3C
lbl_8037CF88:
/* 8037CF88 00379B68  80 01 00 0C */	lwz r0, 0xc(r1)
/* 8037CF8C 00379B6C  38 21 00 08 */	addi r1, r1, 8
/* 8037CF90 00379B70  7C 08 03 A6 */	mtlr r0
/* 8037CF94 00379B74  4E 80 00 20 */	blr 
}

#pragma push
#pragma peephole on
void* HSD_IDGetDataFromTable(HSD_IDTable* table, u32 id, s32* success)
{
    IDEntry* entry;

    if (table == NULL) {
        table = &lbl_804C23EC;
    }

    entry = (&table->table[0].next)[hash(id)];
    while (entry != NULL) {
        if (entry->id == id) {
            if (success != NULL) {
                *success = 1;
            }
            return entry->data;
        }
        entry = entry->next;
    }

    if (success != NULL) {
        *success = 0;
    }
    return NULL;
}

void _HSD_IDForgetMemory(void)
{
    memset(&lbl_804C23EC, 0, 0x194);
}
#pragma pop
