#include "sysdolphin/baselib/id.h"

HSD_ObjAllocData hsd_iddata;

HSD_IDTable default_table;

static char lbl_804D5EE8[5] = "id.c\0"; // "id.c"
static char lbl_804D5EF0[6] = "entry\0";

HSD_ObjAllocData* HSD_IDGetAllocData(void)
{
    return &hsd_iddata;
}

void HSD_IDInitAllocData(void)
{
    HSD_ObjAllocInit(&hsd_iddata, sizeof(IDEntry), 4);
}

void HSD_IDSetup(void)
{
    memset(&default_table, 0, sizeof(HSD_IDTable));
}

#ifdef NON_MATCHING
void HSD_IDInsertToTable(HSD_IDTable* table, u32 id, void* data)
{
    IDEntry* entry;
    u32 hash_key;

    if (table == NULL) {
        table = &default_table;
    }

    hash_key = hash(id);
    entry = table->table[hash_key];

    while (entry != NULL && entry->id != id) {
        entry = entry->next;
    }

    if (entry == NULL) {
        entry = HSD_ObjAlloc(&hsd_iddata);
        if (entry == NULL) {
            __assert(lbl_804D5EE8, 67, lbl_804D5EF0);
        }
        entry->id = id;
        entry->data = data;
        entry->next = table->table[hash_key];
        table->table[hash_key]->next = entry;
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
/* 8037CE18 003799F8  3C 60 80 4C */	lis r3, default_table@ha
/* 8037CE1C 003799FC  38 63 23 EC */	addi r3, r3, default_table@l
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
/* 8037CE80 00379A60  3C 60 80 4C */	lis r3, hsd_iddata@ha
/* 8037CE84 00379A64  38 63 23 C0 */	addi r3, r3, hsd_iddata@l
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

#pragma push
#pragma peephole on
inline void IDEntryFree(IDEntry* entry) {
    HSD_ObjFree(&hsd_iddata, entry);
}

void HSD_IDRemoveByIDFromTable(HSD_IDTable* table, u32 id) {
    IDEntry* entry;
    IDEntry* prev;

    if (table == NULL) {
        table = &default_table;
    }

    prev = NULL;
    for (entry = table->table[hash(id)]; entry != NULL; entry = entry->next) {
        if (entry->id == id) {
            if (prev != NULL) {
                prev->next = entry->next;
            } else {
                table->table[hash(id)] = entry->next;
            }
            IDEntryFree(entry);
            return;
        }
        prev = entry;
    }
}

void* HSD_IDGetDataFromTable(HSD_IDTable* table, u32 id, s32* success)
{
    IDEntry* entry;

    if (table == NULL) {
        table = &default_table;
    }

    entry = table->table[hash(id)];
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
    memset(&default_table, 0, sizeof(HSD_IDTable));
}
#pragma pop
