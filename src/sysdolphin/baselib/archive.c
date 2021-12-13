#include <string.h>

#include "sysdolphin/baselib/archive.h"

extern char* lbl_804074A8;

inline void Locate(HSD_Archive* archive)
{
    int i;
    u32* ptr;

    for (i = 0; i < archive->header.nb_reloc; i++) {
        ptr = (u32*)(archive->data + archive->reloc_info[i].offset);
        *ptr += (u32)archive->data;
    }
}


// Non-matching because we can't extern the string due to section
#ifdef NON_MATCHING
s32 HSD_ArchiveParse(HSD_Archive* archive, u8* src, u32 file_size)
{
    u32 offset;
    
    if (archive == NULL) {
        return -1;
    }

    memset(archive, 0, sizeof(HSD_Archive));
    archive->flags |= 1;
    memcpy(archive, src, sizeof(HSD_ArchiveHeader));

    if (archive->header.file_size != file_size) {
        OSReport("HSD_ArchiveParse: byte-order mismatch! Please check data format %x %x\n", archive->header.file_size, file_size);
        return -1;
    }

    offset = sizeof(HSD_ArchiveHeader);
    if (archive->header.data_size != 0) { // Body Size
        archive->data = src + 0x20;
        offset = archive->header.data_size + 0x20;
    }
    if (archive->header.nb_reloc != 0) { // Relocation Size
        archive->reloc_info = (HSD_ArchiveRelocationInfo*)((s32)src + offset);
        offset = offset + archive->header.nb_reloc * 4;
    }
    if (archive->header.nb_public != 0) { // Root Size
        archive->public_info = (HSD_ArchivePublicInfo*)((s32)src + offset);
        offset = offset + archive->header.nb_public * 8;
    }
    if (archive->header.nb_extern != 0) { // XRef Size
        archive->extern_info = (HSD_ArchiveExternInfo*)((s32)src + offset);
        offset = offset + archive->header.nb_extern * 8;
    }
    if (offset < archive->header.file_size) { // File Size
        archive->symbols = (char*)((s32)src + offset);
    }

    archive->top_ptr = (void*)src;
    Locate(archive);

    return 0;
}
#else
asm s32 HSD_ArchiveParse(HSD_Archive* archive, u8* src, u32 file_size)
{
    nofralloc
/* 803801E4 0037CDC4  7C 08 02 A6 */	mflr r0
/* 803801E8 0037CDC8  90 01 00 04 */	stw r0, 4(r1)
/* 803801EC 0037CDCC  94 21 FF D8 */	stwu r1, -0x28(r1)
/* 803801F0 0037CDD0  93 E1 00 24 */	stw r31, 0x24(r1)
/* 803801F4 0037CDD4  3B E4 00 00 */	addi r31, r4, 0
/* 803801F8 0037CDD8  93 C1 00 20 */	stw r30, 0x20(r1)
/* 803801FC 0037CDDC  7C 7E 1B 79 */	or. r30, r3, r3
/* 80380200 0037CDE0  93 A1 00 1C */	stw r29, 0x1c(r1)
/* 80380204 0037CDE4  3B A5 00 00 */	addi r29, r5, 0
/* 80380208 0037CDE8  40 82 00 0C */	bne lbl_80380214
/* 8038020C 0037CDEC  38 60 FF FF */	li r3, -1
/* 80380210 0037CDF0  48 00 01 2C */	b lbl_8038033C
lbl_80380214:
/* 80380214 0037CDF4  38 7E 00 00 */	addi r3, r30, 0
/* 80380218 0037CDF8  38 80 00 00 */	li r4, 0
/* 8038021C 0037CDFC  38 A0 00 44 */	li r5, 0x44
/* 80380220 0037CE00  4B C8 2E E1 */	bl memset
/* 80380224 0037CE04  80 1E 00 3C */	lwz r0, 0x3c(r30)
/* 80380228 0037CE08  38 7E 00 00 */	addi r3, r30, 0
/* 8038022C 0037CE0C  38 9F 00 00 */	addi r4, r31, 0
/* 80380230 0037CE10  60 00 00 01 */	ori r0, r0, 1
/* 80380234 0037CE14  90 1E 00 3C */	stw r0, 0x3c(r30)
/* 80380238 0037CE18  38 A0 00 20 */	li r5, 0x20
/* 8038023C 0037CE1C  4B C8 2F B9 */	bl memcpy
/* 80380240 0037CE20  80 9E 00 00 */	lwz r4, 0(r30)
/* 80380244 0037CE24  7C 04 E8 40 */	cmplw r4, r29
/* 80380248 0037CE28  41 82 00 20 */	beq lbl_80380268
/* 8038024C 0037CE2C  3C 60 80 40 */	lis r3, lbl_804074A8@ha
/* 80380250 0037CE30  4C C6 31 82 */	crclr 6
/* 80380254 0037CE34  38 63 74 A8 */	addi r3, r3, lbl_804074A8@l
/* 80380258 0037CE38  38 BD 00 00 */	addi r5, r29, 0
/* 8038025C 0037CE3C  4B FC 54 4D */	bl OSReport
/* 80380260 0037CE40  38 60 FF FF */	li r3, -1
/* 80380264 0037CE44  48 00 00 D8 */	b lbl_8038033C
lbl_80380268:
/* 80380268 0037CE48  80 1E 00 04 */	lwz r0, 4(r30)
/* 8038026C 0037CE4C  38 60 00 20 */	li r3, 0x20
/* 80380270 0037CE50  28 00 00 00 */	cmplwi r0, 0
/* 80380274 0037CE54  41 82 00 14 */	beq lbl_80380288
/* 80380278 0037CE58  38 1F 00 20 */	addi r0, r31, 0x20
/* 8038027C 0037CE5C  90 1E 00 20 */	stw r0, 0x20(r30)
/* 80380280 0037CE60  80 7E 00 04 */	lwz r3, 4(r30)
/* 80380284 0037CE64  38 63 00 20 */	addi r3, r3, 0x20
lbl_80380288:
/* 80380288 0037CE68  80 1E 00 08 */	lwz r0, 8(r30)
/* 8038028C 0037CE6C  28 00 00 00 */	cmplwi r0, 0
/* 80380290 0037CE70  41 82 00 18 */	beq lbl_803802A8
/* 80380294 0037CE74  7C 1F 1A 14 */	add r0, r31, r3
/* 80380298 0037CE78  90 1E 00 24 */	stw r0, 0x24(r30)
/* 8038029C 0037CE7C  80 1E 00 08 */	lwz r0, 8(r30)
/* 803802A0 0037CE80  54 00 10 3A */	slwi r0, r0, 2
/* 803802A4 0037CE84  7C 63 02 14 */	add r3, r3, r0
lbl_803802A8:
/* 803802A8 0037CE88  80 1E 00 0C */	lwz r0, 0xc(r30)
/* 803802AC 0037CE8C  28 00 00 00 */	cmplwi r0, 0
/* 803802B0 0037CE90  41 82 00 18 */	beq lbl_803802C8
/* 803802B4 0037CE94  7C 1F 1A 14 */	add r0, r31, r3
/* 803802B8 0037CE98  90 1E 00 28 */	stw r0, 0x28(r30)
/* 803802BC 0037CE9C  80 1E 00 0C */	lwz r0, 0xc(r30)
/* 803802C0 0037CEA0  54 00 18 38 */	slwi r0, r0, 3
/* 803802C4 0037CEA4  7C 63 02 14 */	add r3, r3, r0
lbl_803802C8:
/* 803802C8 0037CEA8  80 1E 00 10 */	lwz r0, 0x10(r30)
/* 803802CC 0037CEAC  28 00 00 00 */	cmplwi r0, 0
/* 803802D0 0037CEB0  41 82 00 18 */	beq lbl_803802E8
/* 803802D4 0037CEB4  7C 1F 1A 14 */	add r0, r31, r3
/* 803802D8 0037CEB8  90 1E 00 2C */	stw r0, 0x2c(r30)
/* 803802DC 0037CEBC  80 1E 00 10 */	lwz r0, 0x10(r30)
/* 803802E0 0037CEC0  54 00 18 38 */	slwi r0, r0, 3
/* 803802E4 0037CEC4  7C 63 02 14 */	add r3, r3, r0
lbl_803802E8:
/* 803802E8 0037CEC8  80 1E 00 00 */	lwz r0, 0(r30)
/* 803802EC 0037CECC  7C 03 00 40 */	cmplw r3, r0
/* 803802F0 0037CED0  40 80 00 0C */	bge lbl_803802FC
/* 803802F4 0037CED4  7C 1F 1A 14 */	add r0, r31, r3
/* 803802F8 0037CED8  90 1E 00 30 */	stw r0, 0x30(r30)
lbl_803802FC:
/* 803802FC 0037CEDC  38 80 00 00 */	li r4, 0
/* 80380300 0037CEE0  93 FE 00 40 */	stw r31, 0x40(r30)
/* 80380304 0037CEE4  7C 85 23 78 */	mr r5, r4
/* 80380308 0037CEE8  48 00 00 24 */	b lbl_8038032C
lbl_8038030C:
/* 8038030C 0037CEEC  80 7E 00 24 */	lwz r3, 0x24(r30)
/* 80380310 0037CEF0  38 84 00 01 */	addi r4, r4, 1
/* 80380314 0037CEF4  80 DE 00 20 */	lwz r6, 0x20(r30)
/* 80380318 0037CEF8  7C 63 28 2E */	lwzx r3, r3, r5
/* 8038031C 0037CEFC  38 A5 00 04 */	addi r5, r5, 4
/* 80380320 0037CF00  7C 06 18 2E */	lwzx r0, r6, r3
/* 80380324 0037CF04  7C 00 32 14 */	add r0, r0, r6
/* 80380328 0037CF08  7C 06 19 2E */	stwx r0, r6, r3
lbl_8038032C:
/* 8038032C 0037CF0C  80 1E 00 08 */	lwz r0, 8(r30)
/* 80380330 0037CF10  7C 04 00 40 */	cmplw r4, r0
/* 80380334 0037CF14  41 80 FF D8 */	blt lbl_8038030C
/* 80380338 0037CF18  38 60 00 00 */	li r3, 0
lbl_8038033C:
/* 8038033C 0037CF1C  80 01 00 2C */	lwz r0, 0x2c(r1)
/* 80380340 0037CF20  83 E1 00 24 */	lwz r31, 0x24(r1)
/* 80380344 0037CF24  83 C1 00 20 */	lwz r30, 0x20(r1)
/* 80380348 0037CF28  83 A1 00 1C */	lwz r29, 0x1c(r1)
/* 8038034C 0037CF2C  38 21 00 28 */	addi r1, r1, 0x28
/* 80380350 0037CF30  7C 08 03 A6 */	mtlr r0
/* 80380354 0037CF34  4E 80 00 20 */	blr 
}
#endif

#pragma push
#pragma peephole on
void* HSD_ArchiveGetPublicAddress(HSD_Archive* archive, char* symbols) {
    int i;
    
    for (i = 0; i < archive->header.nb_public; i++) {
        if (strcmp(archive->symbols + archive->public_info[i].symbol, symbols) == 0) // If both strings are equal, we've found the node
            return archive->data + archive->public_info[i].offset;;
    }

    return NULL;
}

char* HSD_ArchiveGetExtern(HSD_Archive* archive, s32 offset)
{
    if (offset < 0 || archive->header.nb_extern <= offset) {
        return NULL;
    }
    return archive->symbols + archive->extern_info[offset].symbol;
}
#pragma pop

#ifdef NON_MATCHING
void HSD_ArchiveLocateExtern(HSD_Archive* archive, char* symbols, void* addr)
{
    u32 offset;
    int i;
    
    offset = -1;
    for (i = 0; i < archive->header.nb_extern; i++){
        if (strcmp(symbols, archive->symbols + archive->extern_info[i].symbol) == 0) {
            offset = archive->extern_info[i].offset;
            break;
        }
    }

    if (offset == -1){
        return;
    }

    while (offset != -1 && offset < archive->header.data_size) {
        u32 next = *(u32*)((u32*)archive->data)[offset];
        offset = next;
        *(u32*)archive->data = (u32)addr;
    }
}
#else
asm void HSD_ArchiveLocateExtern(HSD_Archive* archive, char* symbols, void* addr)
{
    nofralloc
/* 80380434 0037D014  7C 08 02 A6 */	mflr r0
/* 80380438 0037D018  90 01 00 04 */	stw r0, 4(r1)
/* 8038043C 0037D01C  94 21 FF D0 */	stwu r1, -0x30(r1)
/* 80380440 0037D020  BF 41 00 18 */	stmw r26, 0x18(r1)
/* 80380444 0037D024  3B 80 00 00 */	li r28, 0
/* 80380448 0037D028  3B E3 00 00 */	addi r31, r3, 0
/* 8038044C 0037D02C  3B 44 00 00 */	addi r26, r4, 0
/* 80380450 0037D030  3B 65 00 00 */	addi r27, r5, 0
/* 80380454 0037D034  57 9E 18 38 */	slwi r30, r28, 3
/* 80380458 0037D038  3B A0 FF FF */	li r29, -1
/* 8038045C 0037D03C  48 00 00 40 */	b lbl_8038049C
lbl_80380460:
/* 80380460 0037D040  80 9F 00 2C */	lwz r4, 0x2c(r31)
/* 80380464 0037D044  38 1E 00 04 */	addi r0, r30, 4
/* 80380468 0037D048  80 BF 00 30 */	lwz r5, 0x30(r31)
/* 8038046C 0037D04C  7F 43 D3 78 */	mr r3, r26
/* 80380470 0037D050  7C 04 00 2E */	lwzx r0, r4, r0
/* 80380474 0037D054  7C 85 02 14 */	add r4, r5, r0
/* 80380478 0037D058  4B FA 54 71 */	bl strcmp
/* 8038047C 0037D05C  2C 03 00 00 */	cmpwi r3, 0
/* 80380480 0037D060  40 82 00 14 */	bne lbl_80380494
/* 80380484 0037D064  80 7F 00 2C */	lwz r3, 0x2c(r31)
/* 80380488 0037D068  57 80 18 38 */	slwi r0, r28, 3
/* 8038048C 0037D06C  7F A3 00 2E */	lwzx r29, r3, r0
/* 80380490 0037D070  48 00 00 18 */	b lbl_803804A8
lbl_80380494:
/* 80380494 0037D074  3B DE 00 08 */	addi r30, r30, 8
/* 80380498 0037D078  3B 9C 00 01 */	addi r28, r28, 1
lbl_8038049C:
/* 8038049C 0037D07C  80 1F 00 10 */	lwz r0, 0x10(r31)
/* 803804A0 0037D080  7C 1C 00 40 */	cmplw r28, r0
/* 803804A4 0037D084  41 80 FF BC */	blt lbl_80380460
lbl_803804A8:
/* 803804A8 0037D088  3C 1D 00 01 */	addis r0, r29, 1
/* 803804AC 0037D08C  28 00 FF FF */	cmplwi r0, 0xffff
/* 803804B0 0037D090  40 82 00 1C */	bne lbl_803804CC
/* 803804B4 0037D094  48 00 00 30 */	b lbl_803804E4
/* 803804B8 0037D098  48 00 00 14 */	b lbl_803804CC
lbl_803804BC:
/* 803804BC 0037D09C  80 1F 00 20 */	lwz r0, 0x20(r31)
/* 803804C0 0037D0A0  7C 60 EA 14 */	add r3, r0, r29
/* 803804C4 0037D0A4  83 A3 00 00 */	lwz r29, 0(r3)
/* 803804C8 0037D0A8  93 63 00 00 */	stw r27, 0(r3)
lbl_803804CC:
/* 803804CC 0037D0AC  3C 1D 00 01 */	addis r0, r29, 1
/* 803804D0 0037D0B0  28 00 FF FF */	cmplwi r0, 0xffff
/* 803804D4 0037D0B4  41 82 00 10 */	beq lbl_803804E4
/* 803804D8 0037D0B8  80 1F 00 04 */	lwz r0, 4(r31)
/* 803804DC 0037D0BC  7C 1D 00 40 */	cmplw r29, r0
/* 803804E0 0037D0C0  41 80 FF DC */	blt lbl_803804BC
lbl_803804E4:
/* 803804E4 0037D0C4  BB 41 00 18 */	lmw r26, 0x18(r1)
/* 803804E8 0037D0C8  80 01 00 34 */	lwz r0, 0x34(r1)
/* 803804EC 0037D0CC  38 21 00 30 */	addi r1, r1, 0x30
/* 803804F0 0037D0D0  7C 08 03 A6 */	mtlr r0
/* 803804F4 0037D0D4  4E 80 00 20 */	blr 
}
#endif
