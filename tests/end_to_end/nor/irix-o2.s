.set noat      # allow manual use of $at
.set noreorder # don't insert nops after branches


glabel test
/* 000090 00400090 03E00008 */  jr    $ra
/* 000094 00400094 00851027 */   nor   $v0, $a0, $a1

/* 000098 00400098 00000000 */  nop
/* 00009C 0040009C 00000000 */  nop
