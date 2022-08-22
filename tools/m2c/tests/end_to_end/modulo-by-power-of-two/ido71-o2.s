.set noat      # allow manual use of $at
.set noreorder # don't insert nops after branches


glabel test
/* 000090 00400090 8C820000 */  lw    $v0, ($a0)
/* 000094 00400094 04410004 */  bgez  $v0, .L004000A8
/* 000098 00400098 30420001 */   andi  $v0, $v0, 1
/* 00009C 0040009C 10400002 */  beqz  $v0, .L004000A8
/* 0000A0 004000A0 00000000 */   nop
/* 0000A4 004000A4 2442FFFE */  addiu $v0, $v0, -2
.L004000A8:
/* 0000A8 004000A8 03E00008 */  jr    $ra
/* 0000AC 004000AC AC820000 */   sw    $v0, ($a0)
