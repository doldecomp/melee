.include "macros.inc"


.section .data
    .balign 8
.global ftCo_803C6BA0
ftCo_803C6BA0:
    .asciz "!(jobj->flags & JOBJ_USE_QUATERNION)"
    .balign 4
.global ftCo_803C6BC8
ftCo_803C6BC8:
    .asciz "translate"
    .balign 4
    .4byte NULL


.section .sdata
    .balign 8
.global ftCo_804D3C20
ftCo_804D3C20:
    .asciz "jobj.h"
    .balign 4
.global ftCo_804D3C28
ftCo_804D3C28:
    .asciz "jobj"
    .balign 4


.section .sdata2
    .balign 8
.global ftCo_804D8C28
ftCo_804D8C28:
    .8byte U32_TO_F32
.global ftCo_804D8C30
ftCo_804D8C30:
    .8byte S32_TO_F32
.global ftCo_804D8C38
ftCo_804D8C38:
    .float 0
.global ftCo_804D8C3C
ftCo_804D8C3C:
    .float 1
