#include "lbcommand.h"

extern const f64 lbl_804D79E0;

void (*lbl_803B9840[16])(CommandInfo*) = {
                            Command_00, Command_01, Command_02, Command_03, Command_04, 
                            Command_05, Command_06, Command_07, Command_08, Command_09, 
                            NULL, NULL, NULL, NULL, NULL, NULL
                         };

// Reset
void Command_00(CommandInfo* info)
{
    info->data_position = 0;
}

// SynchronousTimer
void Command_01(CommandInfo* info)
{
    info->timer += *info->data_position & 0x3ffffff;
    info->data_position += 1;
}

// AsynchronousTimer
void Command_02(CommandInfo* info)
{
    info->timer = (*info->data_position & 0x3ffffff) - info->frame_count;
    info->data_position += 1;
}

// SetLoop
void Command_03(CommandInfo* info)
{
    info->event_return[info->loop_count++] = info->data_position + 1;
    info->event_return[info->loop_count++] = (u32*)(*info->data_position & 0x3ffffff);
    info->data_position += 1;
}

// Execute Loop
asm void Command_04(CommandInfo* info)
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

// Subroutine
void Command_05(CommandInfo* info) {
    info->data_position = info->data_position + 1;
    info->event_return[info->loop_count++] = info->data_position + 1;
    info->data_position = (u32*)(*info->data_position);
}

// Return
void Command_06(CommandInfo* info) {
    info->data_position = info->event_return[info->loop_count -= 1];
}

// GoTo
void Command_07(CommandInfo* info) {
    info->data_position += 1;
    info->data_position = (u32*)*info->data_position;
}

// SetTimerAnimation
void Command_08(CommandInfo* info) {
    info->data_position += 1;
    info->timer = FLT_MAX;
}

#pragma push
#pragma peephole on
void Command_09(CommandInfo* info) {
    Command_09_Struct* cmd = (Command_09_Struct*)info->data_position;
    func_80021C48(cmd->param_1, cmd->param_2);
    info->data_position += 1;
}

BOOL Command_Execute(CommandInfo* info, u32 command) {
    if (command < 10) {
        lbl_803B9840[command](info);
        return TRUE;
    }
    return FALSE;
}
#pragma pop
