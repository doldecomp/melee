#include "lbcommand.h"

extern const f64 lbl_804D79E0;

void (*lbl_803B9840[16])(CommandInfo*) = {
                            Command_00, Command_04, Command_08, Command_0C, Command_10_ExecuteLoop, 
                            Command_10_Goto, Command_80005AC4, Command_80005AE4, Command_80005B00, Command_80005B18, 
                            NULL, NULL, NULL, NULL, NULL, NULL
                         };

// Reset
void Command_00(CommandInfo* info)
{
    info->data_position = 0;
}

//Set Timer
void Command_04(CommandInfo* info)
{
    info->timer += *info->data_position & 0x3ffffff;
    info->data_position += 1;
}

//Adjust Timer
void Command_08(CommandInfo* info)
{
    info->timer = (*info->data_position & 0x3ffffff) - info->frame_count;
    info->data_position += 1;
}

//Set Loop
void Command_0C(CommandInfo* info)
{
    info->event_return[info->loop_count++] = info->data_position + 1;
    info->event_return[info->loop_count++] = (u32*)(*info->data_position & 0x3ffffff);
    info->data_position += 1;
}

//Execute Loop
asm void Command_10_ExecuteLoop(CommandInfo* info)
{
    nofralloc
/* 80005A30 00002610  80 03 00 0C */	lwz r0, 0xc(r3)
/* 80005A34 00002614  54 00 10 3A */	slwi r0, r0, 2
/* 80005A38 00002618  7C A3 02 14 */	add r5, r3, r0
/* 80005A3C 0000261C  80 85 00 0C */	lwz r4, 0xc(r5)
/* 80005A40 00002620  38 04 FF FF */	addi r0, r4, -1
/* 80005A44 00002624  90 05 00 0C */	stw r0, 0xc(r5)
/* 80005A48 00002628  80 03 00 0C */	lwz r0, 0xc(r3)
/* 80005A4C 0000262C  54 00 10 3A */	slwi r0, r0, 2
/* 80005A50 00002630  7C 83 02 14 */	add r4, r3, r0
/* 80005A54 00002634  80 04 00 0C */	lwz r0, 0xc(r4)
/* 80005A58 00002638  2C 00 00 00 */	cmpwi r0, 0
/* 80005A5C 0000263C  41 82 00 10 */	beq lbl_80005A6C
/* 80005A60 00002640  80 04 00 08 */	lwz r0, 8(r4)
/* 80005A64 00002644  90 03 00 08 */	stw r0, 8(r3)
/* 80005A68 00002648  4E 80 00 20 */	blr 
lbl_80005A6C:
/* 80005A6C 0000264C  80 83 00 08 */	lwz r4, 8(r3)
/* 80005A70 00002650  38 04 00 04 */	addi r0, r4, 4
/* 80005A74 00002654  90 03 00 08 */	stw r0, 8(r3)
/* 80005A78 00002658  80 83 00 0C */	lwz r4, 0xc(r3)
/* 80005A7C 0000265C  38 04 FF FE */	addi r0, r4, -2
/* 80005A80 00002660  90 03 00 0C */	stw r0, 0xc(r3)
/* 80005A84 00002664  4E 80 00 20 */	blr 
}

void Command_10_Goto(CommandInfo* info) {
    info->data_position = info->data_position + 1;
    info->event_return[info->loop_count++] = info->data_position + 1;
    info->data_position = (u32*)(*info->data_position);
}

void Command_80005AC4(CommandInfo* info) {
    info->data_position = info->event_return[info->loop_count -= 1];
}

void Command_80005AE4(CommandInfo* info) {
    info->data_position += 1;
    info->data_position = (u32*)*info->data_position;
}

void Command_80005B00(CommandInfo* info) {
    info->data_position += 1;
    info->timer = FLT_MAX;
}

asm void Command_80005B18(CommandInfo* info) {
    nofralloc
/* 80005B18 000026F8  7C 08 02 A6 */	mflr r0
/* 80005B1C 000026FC  90 01 00 04 */	stw r0, 4(r1)
/* 80005B20 00002700  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 80005B24 00002704  93 E1 00 14 */	stw r31, 0x14(r1)
/* 80005B28 00002708  7C 7F 1B 78 */	mr r31, r3
/* 80005B2C 0000270C  80 83 00 08 */	lwz r4, 8(r3)
/* 80005B30 00002710  A0 64 00 00 */	lhz r3, 0(r4)
/* 80005B34 00002714  80 84 00 00 */	lwz r4, 0(r4)
/* 80005B38 00002718  54 63 F6 3E */	rlwinm r3, r3, 0x1e, 0x18, 0x1f
/* 80005B3C 0000271C  54 84 03 BE */	clrlwi r4, r4, 0xe
/* 80005B40 00002720  48 01 C1 09 */	bl func_80021C48
/* 80005B44 00002724  80 7F 00 08 */	lwz r3, 8(r31)
/* 80005B48 00002728  38 03 00 04 */	addi r0, r3, 4
/* 80005B4C 0000272C  90 1F 00 08 */	stw r0, 8(r31)
/* 80005B50 00002730  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 80005B54 00002734  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 80005B58 00002738  38 21 00 18 */	addi r1, r1, 0x18
/* 80005B5C 0000273C  7C 08 03 A6 */	mtlr r0
/* 80005B60 00002740  4E 80 00 20 */	blr 
}

#pragma push
#pragma peephole on
BOOL Command_80005B64(CommandInfo* info, u32 command) {
    if (command < 10) {
        lbl_803B9840[command](info);
        return TRUE;
    }
    return FALSE;
}
#pragma pop
