.include "macros.inc"

.section .text  # 0x800763C0 - 0x800DF934

.section .data
    .balign 8
.global lbl_803C0C40
lbl_803C0C40:
    .int 141
    .int 142
    .int 143
.global lbl_803C0C4C
lbl_803C0C4C:
    .int 107
    .int 108
    .int 109
.global lbl_803C0C58
lbl_803C0C58:
    .asciz "attack power over 500!! %f\n"
    .balign 4
.global lbl_803C0C74
lbl_803C0C74:
    .asciz "ftcoll.c"
    .balign 4
.global lbl_803C0C80
lbl_803C0C80:
    .asciz "damage log over %d!!\n"
    .balign 4
    .asciz "tip log over %d!!\n"
    .balign 4
.global lbl_803C0CAC
lbl_803C0CAC:
    .4byte 0x000003E8
    .4byte 0x000003EA
    .4byte 0x000003E9
    .4byte 0x000003EC
    .4byte 0x00000479
    .4byte 0x000003ED
    .int -1
    .int -1
    .int -1
    .4byte 0x000003E8
    .4byte 0x000003E8
    .int -1
    .int -1
    .4byte 0x00000416
    .int -1
    .int -1
    .float 0.0
.global lbl_803C0CF0
lbl_803C0CF0:
    .asciz "in ftCollisionSetHitStatus illegal parts!\n"
    .balign 4
    .asciz "fighter hit num over!\n"
    .balign 4
    .asciz "fighter dynamics hit num over!\n"
    .balign 4

.section .bss
    .balign 8
.global lbl_80459278
lbl_80459278:
	.skip 0x320
.global lbl_80459598
lbl_80459598:
	.skip 0x320

.section .sdata
    .balign 8
.global lbl_804D3A68
lbl_804D3A68:
    .asciz "0"
    .balign 4

.section .sbss
    .balign 8
.global lbl_804D6558
lbl_804D6558:
	.skip 0x4
.global lbl_804D655C
lbl_804D655C:
	.skip 0x4
.global lbl_804D6560
lbl_804D6560:
	.skip 0x4

.section .sdata2
    .balign 8
.global lbl_804D82E8
lbl_804D82E8:
	.float 0.5
.global lbl_804D82EC
lbl_804D82EC:
	.float 1.0
.global lbl_804D82F0
lbl_804D82F0:
	.double -0.0078125
.global lbl_804D82F8
lbl_804D82F8:
	.double 4503601774854144.0
.global lbl_804D8300
lbl_804D8300:
	.float 0.01745329238474369
	.float 0.0
.global lbl_804D8308
lbl_804D8308:
	.double 4503599627370496.0
.global lbl_804D8310
lbl_804D8310:
	.4byte 0x7F7FFFFF
.global lbl_804D8314
lbl_804D8314:
	.float 0.009999999776482582
.global lbl_804D8318
lbl_804D8318:
	.float 9.999999747378752e-06
.global lbl_804D831C
lbl_804D831C:
	.float 57.295780181884766
