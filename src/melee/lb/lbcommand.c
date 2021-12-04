#include "lbcommand.h"

extern const f64 lbl_804D79E0;

void* lbl_803B9840[16] = {
                            Command_00, Command_04, Command_08, Command_0C, Command_10_ExecuteLoop, 
                            Command_10_Goto, Command_14, func_80005AE4, func_80005B00, func_80005B18, 
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
#ifdef NON_MATCHING
void Command_0C(CommandInfo* info)
{
    u32 loop;
    u32* data_ptr;

    loop = info->loop_count;
    data_ptr = info->data_position;
    info->loop_count += 1;
    data_ptr += loop;
    info->event_return = data_ptr;
    
    loop = info->loop_count;
    data_ptr = info->data_position;
    info->loop_count += 1;
    data_ptr += loop;
    info->event_return = (u32*)(*data_ptr & 0x3ffffff);

    info->data_position += 1;
}
#else
asm void Command_0C(CommandInfo* info)
{
    nofralloc
/* 800059DC 000025BC  80 A3 00 0C */	lwz r5, 0xc(r3)
/* 800059E0 000025C0  80 C3 00 08 */	lwz r6, 8(r3)
/* 800059E4 000025C4  38 85 00 01 */	addi r4, r5, 1
/* 800059E8 000025C8  54 A0 10 3A */	slwi r0, r5, 2
/* 800059EC 000025CC  90 83 00 0C */	stw r4, 0xc(r3)
/* 800059F0 000025D0  38 A6 00 04 */	addi r5, r6, 4
/* 800059F4 000025D4  7C 83 02 14 */	add r4, r3, r0
/* 800059F8 000025D8  90 A4 00 10 */	stw r5, 0x10(r4)
/* 800059FC 000025DC  80 83 00 0C */	lwz r4, 0xc(r3)
/* 80005A00 000025E0  80 C3 00 08 */	lwz r6, 8(r3)
/* 80005A04 000025E4  38 A4 00 01 */	addi r5, r4, 1
/* 80005A08 000025E8  80 C6 00 00 */	lwz r6, 0(r6)
/* 80005A0C 000025EC  54 80 10 3A */	slwi r0, r4, 2
/* 80005A10 000025F0  7C 83 02 14 */	add r4, r3, r0
/* 80005A14 000025F4  90 A3 00 0C */	stw r5, 0xc(r3)
/* 80005A18 000025F8  54 C0 01 BE */	clrlwi r0, r6, 6
/* 80005A1C 000025FC  90 04 00 10 */	stw r0, 0x10(r4)
/* 80005A20 00002600  80 83 00 08 */	lwz r4, 8(r3)
/* 80005A24 00002604  38 04 00 04 */	addi r0, r4, 4
/* 80005A28 00002608  90 03 00 08 */	stw r0, 8(r3)
/* 80005A2C 0000260C  4E 80 00 20 */	blr 
}
#endif

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

#ifdef NON_MATCHING
void Command_10_Goto(CommandInfo* info) {
    u32 i; 

    info->data_position = info->data_position + 1;
    i = info->loop_count;
    info->loop_count += 1;
    info->event_return = info->data_position + i;
    info->data_position = info->data_position + 1;
}
#else
asm void Command_10_Goto(CommandInfo* info) {
    nofralloc
/* 80005A88 00002668  80 83 00 08 */	lwz r4, 8(r3)
/* 80005A8C 0000266C  38 04 00 04 */	addi r0, r4, 4
/* 80005A90 00002670  90 03 00 08 */	stw r0, 8(r3)
/* 80005A94 00002674  80 A3 00 0C */	lwz r5, 0xc(r3)
/* 80005A98 00002678  80 C3 00 08 */	lwz r6, 8(r3)
/* 80005A9C 0000267C  38 85 00 01 */	addi r4, r5, 1
/* 80005AA0 00002680  54 A0 10 3A */	slwi r0, r5, 2
/* 80005AA4 00002684  90 83 00 0C */	stw r4, 0xc(r3)
/* 80005AA8 00002688  38 A6 00 04 */	addi r5, r6, 4
/* 80005AAC 0000268C  7C 83 02 14 */	add r4, r3, r0
/* 80005AB0 00002690  90 A4 00 10 */	stw r5, 0x10(r4)
/* 80005AB4 00002694  80 83 00 08 */	lwz r4, 8(r3)
/* 80005AB8 00002698  80 04 00 00 */	lwz r0, 0(r4)
/* 80005ABC 0000269C  90 03 00 08 */	stw r0, 8(r3)
/* 80005AC0 000026A0  4E 80 00 20 */	blr 
}
#endif

#ifdef NON_MATCHING
void Command_80005AC4(CommandInfo* info) {
    u32 i;
    CommandInfo* pos;

    i = info->loop_count;
    i -= 1;
    pos = (CommandInfo*)(info->data_position + i);
    info->loop_count = i;
    info->data_position = pos->event_return;
}
#else
asm void Command_80005AC4(CommandInfo* info) {
    nofralloc
/* 80005AC4 000026A4  80 83 00 0C */	lwz r4, 0xc(r3)
/* 80005AC8 000026A8  38 84 FF FF */	addi r4, r4, -1
/* 80005ACC 000026AC  54 80 10 3A */	slwi r0, r4, 2
/* 80005AD0 000026B0  90 83 00 0C */	stw r4, 0xc(r3)
/* 80005AD4 000026B4  7C 83 02 14 */	add r4, r3, r0
/* 80005AD8 000026B8  80 04 00 10 */	lwz r0, 0x10(r4)
/* 80005ADC 000026BC  90 03 00 08 */	stw r0, 8(r3)
/* 80005AE0 000026C0  4E 80 00 20 */	blr 
}
#endif
