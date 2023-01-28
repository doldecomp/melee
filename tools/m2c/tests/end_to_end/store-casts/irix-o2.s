.set noat      # allow manual use of $at
.set noreorder # don't insert nops after branches


glabel test
/* 000090 00400090 AFA60008 */  sw    $a2, 8($sp)
/* 000094 00400094 24180002 */  addiu $t8, $zero, 2
/* 000098 00400098 00C5C821 */  addu  $t9, $a2, $a1
/* 00009C 0040009C A4980008 */  sh    $t8, 8($a0)
/* 0000A0 004000A0 A485000A */  sh    $a1, 0xa($a0)
/* 0000A4 004000A4 A486000C */  sh    $a2, 0xc($a0)
/* 0000A8 004000A8 03E00008 */  jr    $ra
/* 0000AC 004000AC A499000E */   sh    $t9, 0xe($a0)
