.include "macros.inc"

.section .text  # 0x80005940 - 0x803B7240

.global EXI2_Init
EXI2_Init:
/* 8032AFB4 00327B94  4E 80 00 20 */	blr 

.global EXI2_EnableInterrupts
EXI2_EnableInterrupts:
/* 8032AFB8 00327B98  4E 80 00 20 */	blr 

.global EXI2_Poll
EXI2_Poll:
/* 8032AFBC 00327B9C  38 60 00 00 */	li r3, 0
/* 8032AFC0 00327BA0  4E 80 00 20 */	blr 

.global EXI2_ReadN
EXI2_ReadN:
/* 8032AFC4 00327BA4  38 60 00 00 */	li r3, 0
/* 8032AFC8 00327BA8  4E 80 00 20 */	blr 

.global EXI2_WriteN
EXI2_WriteN:
/* 8032AFCC 00327BAC  38 60 00 00 */	li r3, 0
/* 8032AFD0 00327BB0  4E 80 00 20 */	blr 

.global EXI2_Reserve
EXI2_Reserve:
/* 8032AFD4 00327BB4  4E 80 00 20 */	blr 

.global EXI2_Unreserve
EXI2_Unreserve:
/* 8032AFD8 00327BB8  4E 80 00 20 */	blr 

.global AMC_IsStub
AMC_IsStub:
/* 8032AFDC 00327BBC  38 60 00 01 */	li r3, 1
/* 8032AFE0 00327BC0  4E 80 00 20 */	blr 
