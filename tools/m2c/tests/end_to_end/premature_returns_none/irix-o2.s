.set noat      # allow manual use of $at
.set noreorder # don't insert nops after branches


glabel test
/* 000090 00400090 10800002 */  beqz  $a0, .L0040009C
/* 000094 00400094 00001825 */   move  $v1, $zero
/* 000098 00400098 24030001 */  addiu $v1, $zero, 1
.L0040009C:
/* 00009C 0040009C 03E00008 */  jr    $ra
/* 0000A0 004000A0 00601025 */   move  $v0, $v1

/* 0000A4 004000A4 00000000 */  nop
/* 0000A8 004000A8 00000000 */  nop
/* 0000AC 004000AC 00000000 */  nop
