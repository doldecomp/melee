.include "macros.inc"

.section .sbss
    .balign 4
.global DVDInitialized
DVDInitialized:
    .skip 0x4
.global LastState
LastState:
    .skip 0x4
