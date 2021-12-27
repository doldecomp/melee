#include "sysdolphin/baselib/class.h"

extern void func_803822C0();

HSD_ClassInfo hsdClass = { func_803822C0 };

extern char lbl_804D5FA8[8]; // "class.c\0";
extern char lbl_804D5FB0[2];

void ClassInfoInit(HSD_ClassInfo* info)
{
    if ((info->head.flags & 1) == 0) {
        (*info->head.info_init)();
    }
}

void hsdInitClassInfo(HSD_ClassInfo* class_info, HSD_ClassInfo* parent_info, char* base_class_library, char* type, s32 info_size, s32 class_size)
{
    class_info->head.flags = 1;
    class_info->head.library_name = base_class_library;
    class_info->head.class_name = type;
    class_info->head.obj_size = (s16)class_size;
    class_info->head.info_size = (s16)info_size;
    class_info->head.parent = parent_info;
    class_info->head.child = NULL;
    class_info->head.next = NULL;
    class_info->head.nb_exist = 0;
    class_info->head.nb_peak = 0;

    if (parent_info != NULL) {
        if ((parent_info->head.flags & 1) == 0) {
            (*parent_info->head.info_init)();
        }
        if (class_info->head.obj_size < parent_info->head.obj_size) {
            __assert(lbl_804D5FA8, 94, "class_info->head.obj_size >= parent_info->head.obj_size");
        }
        if (class_info->head.info_size < parent_info->head.info_size) {
            __assert(lbl_804D5FA8, 95, "class_info->head.info_size >= parent_info->head.info_size");
        }
        memcpy(&class_info->alloc, &parent_info->alloc, parent_info->head.info_size - 0x28);
        class_info->head.next = parent_info->head.child;
        parent_info->head.child = class_info;
    }
}

void OSReport_PrintSpaces(s32 count) {
    s32 i;

    for (i = 0; i < count; i++) {
        OSReport(lbl_804D5FB0);
    }
}

#ifdef NON_MATCHING
HSD_MemoryEntry* GetMemoryEntry(s32 idx)
{
    HSD_MemoryEntry** new_list;
    HSD_MemoryEntry** old_list;
    HSD_MemoryEntry* entry;
    s32 i;
    BOOL found;

    if (idx < 0) {
        __assert(__FILE__, 171, "idx >= 0");
    }

    if (idx >= nb_memory_list) {
        if (nb_memory_list == 0) { //In this case, it's uninitialized and allocs the array
            s32 new_nb;
            for (new_nb = 32; idx >= new_nb; new_nb *= 2) {
            }
            memory_list = (HSD_MemoryEntry**)HSD_MemAlloc(new_nb * 4);
            if (memory_list == NULL) {
                return NULL;
            }
            memset(memory_list, 0, new_nb*4);
            nb_memory_list = new_nb;
        } else { //Resizes the array
            s32 new_nb, old_nb;

            new_nb = nb_memory_list * 2;
            while (idx >= new_nb){
                new_nb *= 2;
            }
            
            new_list = (HSD_MemoryEntry**)HSD_MemAlloc(4 * new_nb);
            if (new_list == NULL)
                return NULL;
            
            memcpy(new_list, memory_list, 4 * nb_memory_list);
            memset(&new_list[nb_memory_list], 0, 4 * (new_nb - nb_memory_list)); //You start *after* existing ptrs and make sure memory is zero'd

            old_nb = nb_memory_list;
            old_list = memory_list;
            memory_list = new_list;
            nb_memory_list = new_nb;
            old_nb = (old_nb * 4) & ~0x1F;
            
            hsdFreeMemPiece(old_list, old_nb);
            memory_list[(((new_nb + 31) >> 5) & 0x7FFFFFF) - 1]->nb_alloc += 1;
        }
    }

    if (memory_list[idx] == NULL) {
        entry = (HSD_MemoryEntry*)HSD_MemAlloc(sizeof(HSD_MemoryEntry));
        if (entry == NULL) {
            return NULL;
        }
        memset(entry, 0, sizeof(HSD_MemoryEntry));
        entry->total_bits = (idx + 1) * 32;
        memory_list[idx] = entry;
            
        found = FALSE;
        for (i = idx - 1; i >= 0; --i) {
            if (memory_list[i] != NULL) {
                found = TRUE;
                entry->next = memory_list[i]->next;
                memory_list[i]->next = entry;
                break;
            }
        }
        if (found == FALSE) {
            for (i = idx + 1; i < nb_memory_list; i++) {
                if (memory_list[i] != NULL) {
                    entry->next = memory_list[i];
                    break;
                }
            }
        }
    }
    return memory_list[idx];
}
#else
asm HSD_MemoryEntry* GetMemoryEntry(s32 idx)
{
    nofralloc
/* 80381D58 0037E938  7C 08 02 A6 */	mflr r0
/* 80381D5C 0037E93C  90 01 00 04 */	stw r0, 4(r1)
/* 80381D60 0037E940  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 80381D64 0037E944  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 80381D68 0037E948  93 C1 00 18 */	stw r30, 0x18(r1)
/* 80381D6C 0037E94C  93 A1 00 14 */	stw r29, 0x14(r1)
/* 80381D70 0037E950  7C 7D 1B 79 */	or. r29, r3, r3
/* 80381D74 0037E954  40 80 00 18 */	bge lbl_80381D8C
/* 80381D78 0037E958  3C 60 80 40 */	lis r3, lbl_80407698@ha
/* 80381D7C 0037E95C  38 A3 76 98 */	addi r5, r3, lbl_80407698@l
/* 80381D80 0037E960  38 6D A9 08 */	addi r3, r13, lbl_804D5FA8@sda21
/* 80381D84 0037E964  38 80 00 AB */	li r4, 0xab
/* 80381D88 0037E968  48 00 64 99 */	bl __assert
lbl_80381D8C:
/* 80381D8C 0037E96C  80 0D C0 64 */	lwz r0, lbl_804D7704@sda21(r13)
/* 80381D90 0037E970  7C 1D 00 00 */	cmpw r29, r0
/* 80381D94 0037E974  41 80 00 F0 */	blt lbl_80381E84
/* 80381D98 0037E978  2C 00 00 00 */	cmpwi r0, 0
/* 80381D9C 0037E97C  40 82 00 50 */	bne lbl_80381DEC
/* 80381DA0 0037E980  3B E0 00 20 */	li r31, 0x20
/* 80381DA4 0037E984  48 00 00 08 */	b lbl_80381DAC
lbl_80381DA8:
/* 80381DA8 0037E988  57 FF 08 3C */	slwi r31, r31, 1
lbl_80381DAC:
/* 80381DAC 0037E98C  7C 1D F8 00 */	cmpw r29, r31
/* 80381DB0 0037E990  40 80 FF F8 */	bge lbl_80381DA8
/* 80381DB4 0037E994  57 FE 10 3A */	slwi r30, r31, 2
/* 80381DB8 0037E998  38 7E 00 00 */	addi r3, r30, 0
/* 80381DBC 0037E99C  4B FF D4 29 */	bl HSD_MemAlloc
/* 80381DC0 0037E9A0  90 6D C0 60 */	stw r3, lbl_804D7700@sda21(r13)
/* 80381DC4 0037E9A4  80 6D C0 60 */	lwz r3, lbl_804D7700@sda21(r13)
/* 80381DC8 0037E9A8  28 03 00 00 */	cmplwi r3, 0
/* 80381DCC 0037E9AC  40 82 00 0C */	bne lbl_80381DD8
/* 80381DD0 0037E9B0  38 60 00 00 */	li r3, 0
/* 80381DD4 0037E9B4  48 00 01 B8 */	b lbl_80381F8C
lbl_80381DD8:
/* 80381DD8 0037E9B8  38 BE 00 00 */	addi r5, r30, 0
/* 80381DDC 0037E9BC  38 80 00 00 */	li r4, 0
/* 80381DE0 0037E9C0  4B C8 13 21 */	bl memset
/* 80381DE4 0037E9C4  93 ED C0 64 */	stw r31, lbl_804D7704@sda21(r13)
/* 80381DE8 0037E9C8  48 00 00 9C */	b lbl_80381E84
lbl_80381DEC:
/* 80381DEC 0037E9CC  54 1F 08 3C */	slwi r31, r0, 1
/* 80381DF0 0037E9D0  48 00 00 08 */	b lbl_80381DF8
lbl_80381DF4:
/* 80381DF4 0037E9D4  57 FF 08 3C */	slwi r31, r31, 1
lbl_80381DF8:
/* 80381DF8 0037E9D8  7C 1D F8 00 */	cmpw r29, r31
/* 80381DFC 0037E9DC  40 80 FF F8 */	bge lbl_80381DF4
/* 80381E00 0037E9E0  57 E3 10 3A */	slwi r3, r31, 2
/* 80381E04 0037E9E4  4B FF D3 E1 */	bl HSD_MemAlloc
/* 80381E08 0037E9E8  7C 7E 1B 79 */	or. r30, r3, r3
/* 80381E0C 0037E9EC  40 82 00 0C */	bne lbl_80381E18
/* 80381E10 0037E9F0  38 60 00 00 */	li r3, 0
/* 80381E14 0037E9F4  48 00 01 78 */	b lbl_80381F8C
lbl_80381E18:
/* 80381E18 0037E9F8  80 0D C0 64 */	lwz r0, lbl_804D7704@sda21(r13)
/* 80381E1C 0037E9FC  7F C3 F3 78 */	mr r3, r30
/* 80381E20 0037EA00  80 8D C0 60 */	lwz r4, lbl_804D7700@sda21(r13)
/* 80381E24 0037EA04  54 05 10 3A */	slwi r5, r0, 2
/* 80381E28 0037EA08  4B C8 13 CD */	bl memcpy
/* 80381E2C 0037EA0C  80 0D C0 64 */	lwz r0, lbl_804D7704@sda21(r13)
/* 80381E30 0037EA10  38 80 00 00 */	li r4, 0
/* 80381E34 0037EA14  54 03 10 3A */	slwi r3, r0, 2
/* 80381E38 0037EA18  7C 00 F8 50 */	subf r0, r0, r31
/* 80381E3C 0037EA1C  7C 7E 1A 14 */	add r3, r30, r3
/* 80381E40 0037EA20  54 05 10 3A */	slwi r5, r0, 2
/* 80381E44 0037EA24  4B C8 12 BD */	bl memset
/* 80381E48 0037EA28  80 0D C0 64 */	lwz r0, lbl_804D7704@sda21(r13)
/* 80381E4C 0037EA2C  80 6D C0 60 */	lwz r3, lbl_804D7700@sda21(r13)
/* 80381E50 0037EA30  93 ED C0 64 */	stw r31, lbl_804D7704@sda21(r13)
/* 80381E54 0037EA34  54 1F 10 34 */	rlwinm r31, r0, 2, 0, 0x1a
/* 80381E58 0037EA38  7F E4 FB 78 */	mr r4, r31
/* 80381E5C 0037EA3C  93 CD C0 60 */	stw r30, lbl_804D7700@sda21(r13)
/* 80381E60 0037EA40  48 00 03 0D */	bl hsdFreeMemPiece
/* 80381E64 0037EA44  38 1F 00 1F */	addi r0, r31, 0x1f
/* 80381E68 0037EA48  80 6D C0 60 */	lwz r3, lbl_804D7700@sda21(r13)
/* 80381E6C 0037EA4C  54 00 E8 FA */	rlwinm r0, r0, 0x1d, 3, 0x1d
/* 80381E70 0037EA50  7C 63 02 14 */	add r3, r3, r0
/* 80381E74 0037EA54  80 83 FF FC */	lwz r4, -4(r3)
/* 80381E78 0037EA58  80 64 00 04 */	lwz r3, 4(r4)
/* 80381E7C 0037EA5C  38 03 00 01 */	addi r0, r3, 1
/* 80381E80 0037EA60  90 04 00 04 */	stw r0, 4(r4)
lbl_80381E84:
/* 80381E84 0037EA64  80 6D C0 60 */	lwz r3, lbl_804D7700@sda21(r13)
/* 80381E88 0037EA68  57 BF 10 3A */	slwi r31, r29, 2
/* 80381E8C 0037EA6C  7C 03 F8 2E */	lwzx r0, r3, r31
/* 80381E90 0037EA70  28 00 00 00 */	cmplwi r0, 0
/* 80381E94 0037EA74  40 82 00 F0 */	bne lbl_80381F84
/* 80381E98 0037EA78  38 60 00 14 */	li r3, 0x14
/* 80381E9C 0037EA7C  4B FF D3 49 */	bl HSD_MemAlloc
/* 80381EA0 0037EA80  7C 7E 1B 79 */	or. r30, r3, r3
/* 80381EA4 0037EA84  40 82 00 0C */	bne lbl_80381EB0
/* 80381EA8 0037EA88  38 60 00 00 */	li r3, 0
/* 80381EAC 0037EA8C  48 00 00 E0 */	b lbl_80381F8C
lbl_80381EB0:
/* 80381EB0 0037EA90  38 7E 00 00 */	addi r3, r30, 0
/* 80381EB4 0037EA94  38 80 00 00 */	li r4, 0
/* 80381EB8 0037EA98  38 A0 00 14 */	li r5, 0x14
/* 80381EBC 0037EA9C  4B C8 12 45 */	bl memset
/* 80381EC0 0037EAA0  38 1D 00 01 */	addi r0, r29, 1
/* 80381EC4 0037EAA4  54 00 28 34 */	slwi r0, r0, 5
/* 80381EC8 0037EAA8  90 1E 00 00 */	stw r0, 0(r30)
/* 80381ECC 0037EAAC  34 BD FF FF */	addic. r5, r29, -1
/* 80381ED0 0037EAB0  38 C0 00 00 */	li r6, 0
/* 80381ED4 0037EAB4  80 6D C0 60 */	lwz r3, lbl_804D7700@sda21(r13)
/* 80381ED8 0037EAB8  38 05 00 01 */	addi r0, r5, 1
/* 80381EDC 0037EABC  7F C3 F9 2E */	stwx r30, r3, r31
/* 80381EE0 0037EAC0  7C 09 03 A6 */	mtctr r0
/* 80381EE4 0037EAC4  54 A0 10 3A */	slwi r0, r5, 2
/* 80381EE8 0037EAC8  80 8D C0 60 */	lwz r4, lbl_804D7700@sda21(r13)
/* 80381EEC 0037EACC  7C 64 02 14 */	add r3, r4, r0
/* 80381EF0 0037EAD0  41 80 00 40 */	blt lbl_80381F30
lbl_80381EF4:
/* 80381EF4 0037EAD4  80 03 00 00 */	lwz r0, 0(r3)
/* 80381EF8 0037EAD8  28 00 00 00 */	cmplwi r0, 0
/* 80381EFC 0037EADC  41 82 00 28 */	beq lbl_80381F24
/* 80381F00 0037EAE0  54 A5 10 3A */	slwi r5, r5, 2
/* 80381F04 0037EAE4  7C 64 28 2E */	lwzx r3, r4, r5
/* 80381F08 0037EAE8  38 C0 00 01 */	li r6, 1
/* 80381F0C 0037EAEC  80 03 00 10 */	lwz r0, 0x10(r3)
/* 80381F10 0037EAF0  90 1E 00 10 */	stw r0, 0x10(r30)
/* 80381F14 0037EAF4  80 6D C0 60 */	lwz r3, lbl_804D7700@sda21(r13)
/* 80381F18 0037EAF8  7C 63 28 2E */	lwzx r3, r3, r5
/* 80381F1C 0037EAFC  93 C3 00 10 */	stw r30, 0x10(r3)
/* 80381F20 0037EB00  48 00 00 10 */	b lbl_80381F30
lbl_80381F24:
/* 80381F24 0037EB04  38 63 FF FC */	addi r3, r3, -4
/* 80381F28 0037EB08  38 A5 FF FF */	addi r5, r5, -1
/* 80381F2C 0037EB0C  42 00 FF C8 */	bdnz lbl_80381EF4
lbl_80381F30:
/* 80381F30 0037EB10  2C 06 00 00 */	cmpwi r6, 0
/* 80381F34 0037EB14  40 82 00 50 */	bne lbl_80381F84
/* 80381F38 0037EB18  80 8D C0 64 */	lwz r4, lbl_804D7704@sda21(r13)
/* 80381F3C 0037EB1C  38 DD 00 01 */	addi r6, r29, 1
/* 80381F40 0037EB20  80 AD C0 60 */	lwz r5, lbl_804D7700@sda21(r13)
/* 80381F44 0037EB24  54 C3 10 3A */	slwi r3, r6, 2
/* 80381F48 0037EB28  7C 06 20 50 */	subf r0, r6, r4
/* 80381F4C 0037EB2C  7C 06 20 00 */	cmpw r6, r4
/* 80381F50 0037EB30  7C 09 03 A6 */	mtctr r0
/* 80381F54 0037EB34  7C 65 1A 14 */	add r3, r5, r3
/* 80381F58 0037EB38  40 80 00 2C */	bge lbl_80381F84
lbl_80381F5C:
/* 80381F5C 0037EB3C  80 03 00 00 */	lwz r0, 0(r3)
/* 80381F60 0037EB40  28 00 00 00 */	cmplwi r0, 0
/* 80381F64 0037EB44  41 82 00 14 */	beq lbl_80381F78
/* 80381F68 0037EB48  54 C0 10 3A */	slwi r0, r6, 2
/* 80381F6C 0037EB4C  7C 05 00 2E */	lwzx r0, r5, r0
/* 80381F70 0037EB50  90 1E 00 10 */	stw r0, 0x10(r30)
/* 80381F74 0037EB54  48 00 00 10 */	b lbl_80381F84
lbl_80381F78:
/* 80381F78 0037EB58  38 63 00 04 */	addi r3, r3, 4
/* 80381F7C 0037EB5C  38 C6 00 01 */	addi r6, r6, 1
/* 80381F80 0037EB60  42 00 FF DC */	bdnz lbl_80381F5C
lbl_80381F84:
/* 80381F84 0037EB64  80 6D C0 60 */	lwz r3, lbl_804D7700@sda21(r13)
/* 80381F88 0037EB68  7C 63 F8 2E */	lwzx r3, r3, r31
lbl_80381F8C:
/* 80381F8C 0037EB6C  80 01 00 24 */	lwz r0, 0x24(r1)
/* 80381F90 0037EB70  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 80381F94 0037EB74  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 80381F98 0037EB78  83 A1 00 14 */	lwz r29, 0x14(r1)
/* 80381F9C 0037EB7C  38 21 00 20 */	addi r1, r1, 0x20
/* 80381FA0 0037EB80  7C 08 03 A6 */	mtlr r0
/* 80381FA4 0037EB84  4E 80 00 20 */	blr 
}
#endif
