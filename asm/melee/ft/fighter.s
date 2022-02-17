.include "macros.inc"

.section .text  # 0x800679B0 - 0x8006DBF0


.section .rodata

.global lbl_803B7488
lbl_803B7488:
	.float 0
    .float 0
    .float 0
.global lbl_803B7494
lbl_803B7494:
	.float 0
    .float 0
    .float 0


.section .data

.global lbl_803C05AC
lbl_803C05AC:
    .asciz "fighter procUpdate pos error.\tpos.x=%f\tpos.y=%f\n"
    .balign 4
    .asciz "fighter procMap pos error.\tpos.x=%f\tpos.y=%f\n"
    .balign 4
.global lbl_803C0610
lbl_803C0610:
    .asciz "ellegal flag fp->no_reaction_always\n"
    .balign 4


.section .bss, "wa"

.global lbl_80458FD0
lbl_80458FD0:
	.skip 0x2C
.global lbl_80458FFC
lbl_80458FFC:
	.skip 0x2C


.section .sdata

.global lbl_804D3A00
lbl_804D3A00:
    .asciz "jobj.h"
    .balign 4
.global lbl_804D3A08
lbl_804D3A08:
    .asciz "jobj"
    .balign 4
.global lbl_804D3A10
lbl_804D3A10:
    .asciz "0"
    .balign 4
    .4byte NULL


.section .sbss



.section .sdata2

.global lbl_804D8250
lbl_804D8250:
	.4byte 0x3F800000
.global lbl_804D8254
lbl_804D8254:
	.4byte 0x00000000
.global lbl_804D8258
lbl_804D8258:
	.4byte 0xBF800000
	.4byte 0x00000000
.global lbl_804D8260
lbl_804D8260:
	.4byte 0x43300000
	.4byte 0x80000000
.global lbl_804D8268
lbl_804D8268:
	.4byte 0x4108CCCD
	.4byte 0x00000000
.global lbl_804D8270
lbl_804D8270:
	.4byte 0x3FF921FB
	.4byte 0x54442D18
.global lbl_804D8278
lbl_804D8278:
	.4byte 0x43300000
	.4byte 0x00000000
.global lbl_804D8280
lbl_804D8280:
	.4byte 0x3FE00000
	.4byte 0x00000000
.global lbl_804D8288
lbl_804D8288:
	.4byte 0x40080000
	.4byte 0x00000000
.global lbl_804D8290
lbl_804D8290:
	.4byte 0x4479C000
	.4byte 0x00000000
