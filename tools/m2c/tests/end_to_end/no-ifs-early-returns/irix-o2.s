.set noat      # allow manual use of $at
.set noreorder # don't insert nops after branches


glabel test
/* 000090 00400090 8C830000 */  lw    $v1, ($a0)
/* 000094 00400094 24010008 */  addiu $at, $zero, 8
/* 000098 00400098 10610006 */  beq   $v1, $at, .L004000B4
/* 00009C 0040009C 00601025 */   move  $v0, $v1
/* 0000A0 004000A0 2401000F */  addiu $at, $zero, 0xf
/* 0000A4 004000A4 50410009 */  beql  $v0, $at, .L004000CC
/* 0000A8 004000A8 8CB80000 */   lw    $t8, ($a1)
/* 0000AC 004000AC 03E00008 */  jr    $ra
/* 0000B0 004000B0 00001025 */   move  $v0, $zero

.L004000B4:
/* 0000B4 004000B4 8CAE0000 */  lw    $t6, ($a1)
/* 0000B8 004000B8 00001025 */  move  $v0, $zero
/* 0000BC 004000BC 01C37821 */  addu  $t7, $t6, $v1
/* 0000C0 004000C0 03E00008 */  jr    $ra
/* 0000C4 004000C4 ACAF0000 */   sw    $t7, ($a1)

/* 0000C8 004000C8 8CB80000 */  lw    $t8, ($a1)
.L004000CC:
/* 0000CC 004000CC 0303C823 */  subu  $t9, $t8, $v1
/* 0000D0 004000D0 ACB90000 */  sw    $t9, ($a1)
/* 0000D4 004000D4 03E00008 */  jr    $ra
/* 0000D8 004000D8 00001025 */   move  $v0, $zero

/* 0000DC 004000DC 00000000 */  nop
