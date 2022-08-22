.set noat      # allow manual use of $at
.set noreorder # don't insert nops after branches


glabel test
/* 000090 00400090 8C820000 */  lw    $v0, ($a0)
/* 000094 00400094 04410003 */  bgez  $v0, .L004000A4
/* 000098 00400098 00027043 */   sra   $t6, $v0, 1
/* 00009C 0040009C 24410001 */  addiu $at, $v0, 1
/* 0000A0 004000A0 00017043 */  sra   $t6, $at, 1
.L004000A4:
/* 0000A4 004000A4 03E00008 */  jr    $ra
/* 0000A8 004000A8 AC8E0000 */   sw    $t6, ($a0)

/* 0000AC 004000AC 00000000 */  nop
