.include "macros.inc"

.ifdef MUST_MATCH

.section .data

.global lbl_80401FF8
.set lbl_80401FF8, report_messages - 0x5C
report_messages:
    .asciz "Non-recoverable Exception %d"
    .balign 4
    .asciz "Unhandled Exception %d"
    .balign 4
    .asciz "\nDSISR = 0x%08x                   DAR  = 0x%08x\n"
    .balign 4
    .asciz "TB = 0x%016llx\n"
    .balign 4
    .asciz "\nInstruction at 0x%x (read from SRR0) attempted to access invalid address 0x%x (read from DAR)\n"
    .balign 4
    .asciz "\nAttempted to fetch instruction from invalid address 0x%x (read from SRR0)\n"
    .balign 4
    .asciz "\nInstruction at 0x%x (read from SRR0) attempted to access unaligned address 0x%x (read from DAR)\n"
    .balign 4
    .asciz "\nProgram exception : Possible illegal instruction/operation at or around 0x%x (read from SRR0)\n"
    .balign 4
    .asciz "AI DMA Address =   0x%04x%04x\n"
    .balign 4
    .asciz "ARAM DMA Address = 0x%04x%04x\n"
    .balign 4
    .asciz "DI DMA Address =   0x%08x\n"
    .balign 4
    .asciz "\nLast interrupt (%d): SRR0 = 0x%08x  TB = 0x%016llx\n"
    .balign 4
.global jtbl_804022D4
jtbl_804022D4:
    .4byte lbl_80345A3C
    .4byte lbl_80345A3C
    .4byte lbl_80345994
    .4byte lbl_803459AC
    .4byte lbl_80345A3C
    .4byte lbl_803459C0
    .4byte lbl_803459D8
    .4byte lbl_80345A3C
    .4byte lbl_80345A3C
    .4byte lbl_80345A3C
    .4byte lbl_80345A3C
    .4byte lbl_80345A3C
    .4byte lbl_80345A3C
    .4byte lbl_80345A3C
    .4byte lbl_80345A3C
    .4byte lbl_803459F0

.section .sdata
    .balign 8
.global lbl_804D5C18
lbl_804D5C18:
    .4byte 0x0A000000
    .4byte 0x00000000

.endif
