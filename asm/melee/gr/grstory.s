.include "macros.inc"

.section .text  # 0x80005940 - 0x803B7240
.set lbl_804DB274, 0x804DB274
.set lbl_804DB278, 0x804DB278
.set _SDA2_BASE_, 0x804DF9E0

.section .data
    .balign 8
.global lbl_803E26F0
lbl_803E26F0:
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
    .4byte NULL
	.4byte lbl_801E31C0
	.4byte lbl_801E3224
	.4byte lbl_801E322C
	.4byte lbl_801E3230
    .4byte NULL
	.4byte lbl_801E3370
	.4byte lbl_801E33D8
	.4byte lbl_801E33E0
	.4byte lbl_801E3414
    .4byte NULL
	.4byte lbl_801E3234
	.4byte lbl_801E332C
	.4byte lbl_801E3334
	.4byte lbl_801E336C
    .4byte 0xC0000000
.global lbl_803E2740
lbl_803E2740:
    .asciz "/GrSt.dat"
    .balign 4
.global lbl_803E274C
lbl_803E274C:
    .4byte 0x0000000A
    .4byte lbl_803E26F0
    .4byte lbl_803E2740
	.4byte func_801E3030
	.4byte func_801E302C
	.4byte lbl_801E30A8
	.4byte lbl_801E30AC
	.4byte lbl_801E30D0
	.4byte lbl_801E36D0
	.4byte lbl_801E36D8
    .4byte 0x00000001
    .4byte NULL
    .4byte NULL
    .asciz "%s:%d: couldn t get gobj(id=%d)\n"
    .balign 4
    .ascii "grstory.c"
    .balign 4
    .4byte 0xC3920000
    .4byte 0x42D20000
    .4byte 0xC3920000
    .4byte 0x42960000
    .4byte 0xC3920000
    .4byte 0x42480000
    .4byte 0x43980000
    .4byte 0x42DC0000
    .4byte 0x43980000
    .4byte 0x42B40000
    .4byte NULL
    .4byte NULL
