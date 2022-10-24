.include "macros.inc"

.section .text  # 0x800763C0 - 0x800DF934

.section .data
    .balign 8
.global lbl_803C0C40
lbl_803C0C40:
    .4byte 0x0000008D
    .4byte 0x0000008E
    .4byte 0x0000008F
.global lbl_803C0C4C
lbl_803C0C4C:
    .4byte 0x0000006B
    .4byte 0x0000006C
    .4byte 0x0000006D
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
    .4byte 0xFFFFFFFF
    .4byte 0xFFFFFFFF
    .4byte 0xFFFFFFFF
    .4byte 0x000003E8
    .4byte 0x000003E8
    .4byte 0xFFFFFFFF
    .4byte 0xFFFFFFFF
    .4byte 0x00000416
    .4byte 0xFFFFFFFF
    .4byte 0xFFFFFFFF
    .4byte NULL
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
.global lbl_804D82E0
lbl_804D82E0:
	.4byte 0x00000000
.global lbl_804D82E4
lbl_804D82E4:
	.4byte 0x43FA0000
.global lbl_804D82E8
lbl_804D82E8:
	.4byte 0x3F000000
.global lbl_804D82EC
lbl_804D82EC:
	.4byte 0x3F800000
.global lbl_804D82F0
lbl_804D82F0:
	.4byte 0xBF800000
	.4byte 0x00000000
.global lbl_804D82F8
lbl_804D82F8:
	.4byte 0x43300000
	.4byte 0x80000000
.global lbl_804D8300
lbl_804D8300:
	.4byte 0x3C8EFA35
	.4byte 0x00000000
.global lbl_804D8308
lbl_804D8308:
	.4byte 0x43300000
	.4byte 0x00000000
.global lbl_804D8310
lbl_804D8310:
	.4byte 0x7F7FFFFF
.global lbl_804D8314
lbl_804D8314:
	.4byte 0x3C23D70A
.global lbl_804D8318
lbl_804D8318:
	.4byte 0x3727C5AC
.global lbl_804D831C
lbl_804D831C:
	.4byte 0x42652EE1
