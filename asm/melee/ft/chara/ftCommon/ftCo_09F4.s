.include "macros.inc"

.section .sbss
    .balign 8
.global ftCo_804D6568
ftCo_804D6568:
    .skip 0x4
.global ftCo_804D656C
ftCo_804D656C:
    .skip 0x4

.section .sdata
    .balign 8
.L_804D3B48:
    .4byte ftDynamics_803C5794
    .4byte NULL
.global ftCo_804D3B50
ftCo_804D3B50:
    .4byte .L_804D3B48
    .4byte NULL
.global ftCo_804D3B58
ftCo_804D3B58:
    .asciz "jobj.h"
    .balign 4
.global ftCo_804D3B60
ftCo_804D3B60:
    .asciz "jobj"
