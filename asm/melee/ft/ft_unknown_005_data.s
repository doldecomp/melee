.include "macros.inc"

.section .bss, "wa"
    .balign 8
.global gFtDataList
gFtDataList:
    .skip 0x84
.global lbl_8045993C
lbl_8045993C:
    .skip 0x30
.global lbl_8045996C
lbl_8045996C:
    .skip 0x84
lbl_804599F0:
    .skip 0x78


.section .data
    .balign 8
.global CostumeListsForeachCharacter
CostumeListsForeachCharacter:
    .4byte lbl_804599F0
    .4byte 0x05000000
    .4byte lbl_80459B28
    .4byte 0x04000000
    .4byte lbl_80459A98
    .4byte 0x06000000
    .4byte lbl_80459CA0
    .4byte 0x05000000
    .4byte lbl_80459C10
    .4byte 0x06000000
    .4byte lbl_8045A090
    .4byte 0x04000000
    .4byte lbl_803C82EC
    .4byte 0x05000000
    .4byte lbl_80459D18
    .4byte 0x05000000
    .4byte lbl_80459D90
    .4byte 0x04000000
    .4byte lbl_80459DF0
    .4byte 0x05000000
    .4byte lbl_80459E68
    .4byte 0x04000000
    .4byte lbl_80459EC8
    .4byte 0x04000000
    .4byte lbl_80459F28
    .4byte 0x04000000
    .4byte lbl_80459F88
    .4byte 0x05000000
    .4byte lbl_8045A000
    .4byte 0x06000000
    .4byte lbl_8045A1F8
    .4byte 0x05000000
    .4byte lbl_8045A2D0
    .4byte 0x04000000
    .4byte lbl_8045A270
    .4byte 0x04000000
    .4byte lbl_8045A0F0
    .4byte 0x05000000
    .4byte lbl_8045A168
    .4byte 0x05000000
    .4byte lbl_8045A330
    .4byte 0x05000000
    .4byte lbl_8045A3A8
    .4byte 0x05000000
    .4byte lbl_8045A420
    .4byte 0x04000000
    .4byte lbl_8045A480
    .4byte 0x04000000
    .4byte lbl_8045A4E0
    .4byte 0x04000000
    .4byte lbl_8045A540
    .4byte 0x05000000
    .4byte lbl_8045A5B8
    .4byte 0x05000000
    .4byte lbl_8045A690
    .4byte 0x01000000
    .4byte lbl_8045A6A8
    .4byte 0x01000000
    .4byte lbl_8045A630
    .4byte 0x01000000
    .4byte lbl_8045A648
    .4byte 0x01000000
    .4byte lbl_8045A660
    .4byte 0x01000000
    .4byte lbl_8045A678
    .4byte 0x01000000

.section .sdata
    .balign 8
.global lbl_804D3AA8
lbl_804D3AA8:
    .asciz "jobj.h"
    .balign 4
.global lbl_804D3AB0
lbl_804D3AB0:
    .asciz "jobj"
    .balign 4
