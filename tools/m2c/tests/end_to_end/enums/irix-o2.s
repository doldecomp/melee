.set noat      # allow manual use of $at
.set noreorder # don't insert nops after branches


glabel test
/* 000090 00400090 10800009 */  beqz  $a0, .L004000B8
/* 000094 00400094 3C020040 */   lui   $v0, %hi(array)
/* 000098 00400098 24010002 */  addiu $at, $zero, 2
/* 00009C 0040009C 10810008 */  beq   $a0, $at, .L004000C0
/* 0000A0 004000A0 3C020040 */   lui   $v0, %hi(array)
/* 0000A4 004000A4 24010004 */  addiu $at, $zero, 3
/* 0000A8 004000A8 10810007 */  beq   $a0, $at, .L004000C8
/* 0000AC 004000AC 3C020040 */   lui   $v0, %hi(array)
/* 0000B0 004000B0 10000007 */  b     .L004000D0
/* 0000B4 004000B4 00001025 */   move  $v0, $zero
.L004000B8:
/* 0000B8 004000B8 03E00008 */  jr    $ra
/* 0000BC 004000BC 8C4200E0 */   lw    $v0, %lo(array)($v0)

.L004000C0:
/* 0000C0 004000C0 03E00008 */  jr    $ra
/* 0000C4 004000C4 8C4200E4 */   lw    $v0, %lo(array+4)($v0)

.L004000C8:
/* 0000C8 004000C8 03E00008 */  jr    $ra
/* 0000CC 004000CC 8C4200E8 */   lw    $v0, %lo(array+8)($v0)

.L004000D0:
/* 0000D0 004000D0 03E00008 */  jr    $ra
/* 0000D4 004000D4 00000000 */   nop

/* 0000D8 004000D8 00000000 */  nop
/* 0000DC 004000DC 00000000 */  nop

.section .rodata
.global array
array:
	.word 0x00000003
	.word 0x00000002
	.word 0x00000002
	.word 0x00000000
