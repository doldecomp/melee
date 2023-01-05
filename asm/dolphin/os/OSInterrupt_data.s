.include "macros.inc"

.section .data
    .balign 8
.global lbl_80402318
lbl_80402318:
    .4byte 0x00000100
    .4byte 0x00000040
    .4byte 0xF8000000
    .4byte 0x00000200
    .4byte 0x00000080
    .4byte 0x00003000
    .4byte 0x00000020
    .4byte 0x03FF8C00
    .4byte 0x04000000
    .4byte 0x00004000
    .4byte 0xFFFFFFFF
    .4byte NULL


.section .sbss
    .4byte NULL
.global InterruptHandlerTable
InterruptHandlerTable:
    .skip 0x4
.global __OSLastInterruptSrr0
__OSLastInterruptSrr0:
    .skip 0x4
.global __OSLastInterrupt
__OSLastInterrupt:
    .skip 0x8
.global __OSLastInterruptTime
__OSLastInterruptTime:
    .skip 0x4
.global lbl_804D738C
lbl_804D738C:
    .skip 0x4
