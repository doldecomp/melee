.include "macros.inc"

.section .text  # 0x800679B0 - 0x8006DBF0 

.section .rodata
    .balign 8
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
    .balign 8
.global lbl_803C0530
lbl_803C0530:
    .asciz "PlCo.dat"
    .balign 4

.global lbl_803C053C
lbl_803C053C:
    .asciz "ftLoadCommonData"
    .balign 4
.global lbl_803C0550
lbl_803C0550:
    .asciz "translate"
    .balign 4
.global lbl_803C055C
lbl_803C055C:
    .asciz "fighter sub color num over!\n"
    .balign 4
.global lbl_803C057C
lbl_803C057C:
    .asciz "fighter.c"
    .balign 4
.global lbl_803C0588
lbl_803C0588:
    .asciz "ellegal flag fp->no_normal_motion\n"
    .balign 4
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
    .balign 8
.global lbl_80458FD0
lbl_80458FD0:
	.skip 0x2C
.global lbl_80458FFC
lbl_80458FFC:
	.skip 0x2C


.section .sdata
    .balign 8
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


.section .sbss
    .balign 8
.global lbl_804D64F8
lbl_804D64F8:
	.skip 0x4
.global lbl_804D64FC
lbl_804D64FC:
	.skip 0x4
.global lbl_804D6500
lbl_804D6500:
	.skip 0x4
.global lbl_804D6504
lbl_804D6504:
	.skip 0x4
.global lbl_804D6508
lbl_804D6508:
	.skip 0x4
.global lbl_804D650C
lbl_804D650C:
	.skip 0x4
.global lbl_804D6510
lbl_804D6510:
	.skip 0x4
.global lbl_804D6514
lbl_804D6514:
	.skip 0x4
.global lbl_804D6518
lbl_804D6518:
	.skip 0x4
.global lbl_804D651C
lbl_804D651C:
	.skip 0x4
.global lbl_804D6520
lbl_804D6520:
	.skip 0x4
.global lbl_804D6524
lbl_804D6524:
	.skip 0x4
.global lbl_804D6528
lbl_804D6528:
	.skip 0x4
.global lbl_804D652C
lbl_804D652C:
	.skip 0x4
.global lbl_804D6530
lbl_804D6530:
	.skip 0x4
.global lbl_804D6534
lbl_804D6534:
	.skip 0x4
.global lbl_804D6538
lbl_804D6538:
	.skip 0x4
.global lbl_804D653C
lbl_804D653C:
	.skip 0x4
.global lbl_804D6540
lbl_804D6540:
	.skip 0x4
.global lbl_804D6544
lbl_804D6544:
	.skip 0x4
.global lbl_804D6548
lbl_804D6548:
	.skip 0x4
.global lbl_804D654C
lbl_804D654C:
	.skip 0x4
.global lbl_804D6550
lbl_804D6550:
	.skip 0x4
.global lbl_804D6554
lbl_804D6554:
	.skip 0x4


.section .sdata2
    .balign 8
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
