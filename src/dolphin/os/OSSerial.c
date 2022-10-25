#include <dolphin/types.h>

extern unk_t lbl_80402358;

#pragma push
asm unk_t SIBusy()
{ // clang-format off
    nofralloc
/* 803494BC 0034609C  3C 60 80 40 */	lis r3, lbl_80402358@ha
/* 803494C0 003460A0  80 03 23 58 */	lwz r0, lbl_80402358@l(r3)
/* 803494C4 003460A4  2C 00 FF FF */	cmpwi r0, -1
/* 803494C8 003460A8  41 82 00 0C */	beq lbl_803494D4
/* 803494CC 003460AC  38 60 00 01 */	li r3, 1
/* 803494D0 003460B0  4E 80 00 20 */	blr 
lbl_803494D4:
/* 803494D4 003460B4  38 60 00 00 */	li r3, 0
/* 803494D8 003460B8  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop

extern unk_t Packet;

#pragma push
asm unk_t SIIsChanBusy()
{ // clang-format off
    nofralloc
/* 803494DC 003460BC  3C 80 80 4A */	lis r4, Packet@ha
/* 803494E0 003460C0  54 65 28 34 */	slwi r5, r3, 5
/* 803494E4 003460C4  38 04 7D B8 */	addi r0, r4, Packet@l
/* 803494E8 003460C8  7C 80 2A 14 */	add r4, r0, r5
/* 803494EC 003460CC  80 04 00 00 */	lwz r0, 0(r4)
/* 803494F0 003460D0  38 A0 00 01 */	li r5, 1
/* 803494F4 003460D4  2C 00 FF FF */	cmpwi r0, -1
/* 803494F8 003460D8  40 82 00 18 */	bne lbl_80349510
/* 803494FC 003460DC  3C 80 80 40 */	lis r4, lbl_80402358@ha
/* 80349500 003460E0  80 04 23 58 */	lwz r0, lbl_80402358@l(r4)
/* 80349504 003460E4  7C 00 18 00 */	cmpw r0, r3
/* 80349508 003460E8  41 82 00 08 */	beq lbl_80349510
/* 8034950C 003460EC  38 A0 00 00 */	li r5, 0
lbl_80349510:
/* 80349510 003460F0  7C A3 2B 78 */	mr r3, r5
/* 80349514 003460F4  4E 80 00 20 */	blr 
} // clang-format on
#pragma pop
