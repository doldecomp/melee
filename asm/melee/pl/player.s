.include "macros.inc"

.section .text  # 0x80005940 - 0x803B7240

.section .data

.global lbl_803BCDC0
lbl_803BCDC0:
    .asciz "PdPm.dat"
    .balign 4
.global lbl_803BCDCC
lbl_803BCDCC:
    .asciz "plLoadCommonData"
    .balign 4
.global lbl_803BCDE0
lbl_803BCDE0:
    .4byte 0x02FF0003
    .4byte 0xFF0001FF
    .4byte 0x0018FF00
    .4byte 0x04FF0005
    .4byte 0xFF0006FF
    .4byte 0x0011FF00
    .4byte 0x00FF0012
    .4byte 0xFF0010FF
    .4byte 0x0008FF00
    .4byte 0x09FF000C
    .4byte 0xFF000A0B
    .4byte 0x000FFF00
    .4byte 0x0DFF000E
    .4byte 0xFF001307
    .4byte 0x01071301
    .4byte 0x16FF0014
    .4byte 0xFF0015FF
    .4byte 0x001AFF00
    .4byte 0x17FF0019
    .4byte 0xFF001BFF
    .4byte 0x001DFF00
    .4byte 0x1EFF001F
    .4byte 0xFF001CFF
    .4byte 0x0020FF00
    .4byte 0x0AFF0000
.global lbl_803BCE44
lbl_803BCE44:
    .asciz "cant get player struct! %d\n"
    .balign 4
.global lbl_803BCE60
lbl_803BCE60:
    .asciz "player.c"
    .balign 4
    .4byte NULL


.section .bss, "wa"

.global player_slots
player_slots:
	.skip 0x5760
.global lbl_804587E0
lbl_804587E0:
	.skip 0x30


.section .sdata

.global lbl_804D3940
lbl_804D3940:
    .asciz "0"
    .balign 4
    .4byte NULL


.section .sdata2

.global lbl_804D7F10
lbl_804D7F10:
	.4byte 0x00000000
.global lbl_804D7F14
lbl_804D7F14:
	.4byte 0x3F800000
