.set noat      # allow manual use of $at
.set noreorder # don't insert nops after branches


glabel test
/* 000090 00400090 00851025 */  or    $v0, $a0, $a1
/* 000094 00400094 03E00008 */  jr    $ra
/* 000098 00400098 00401027 */   not   $v0, $v0

/* 00009C 0040009C 03E00008 */  jr    $ra
/* 0000A0 004000A0 00000000 */   nop

/* 0000A4 004000A4 03E00008 */  jr    $ra
/* 0000A8 004000A8 00000000 */   nop

/* 0000AC 004000AC 00000000 */  nop
