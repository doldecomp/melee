.set noat      # allow manual use of $at
.set noreorder # don't insert nops after branches


glabel test
/* 000090 00400090 8C820000 */  lw    $v0, ($a0)
/* 000094 00400094 04410002 */  bgez  $v0, .L004000A0
/* 000098 00400098 00400821 */   move  $at, $v0
/* 00009C 0040009C 24410001 */  addiu $at, $v0, 1
.L004000A0:
/* 0000A0 004000A0 00011043 */  sra   $v0, $at, 1
/* 0000A4 004000A4 03E00008 */  jr    $ra
/* 0000A8 004000A8 AC820000 */   sw    $v0, ($a0)

/* 0000AC 004000AC 00000000 */  nop
