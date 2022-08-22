.set noat      # allow manual use of $at
.set noreorder # don't insert nops after branches


glabel test
/* 000090 00400090 8C8E0000 */  lw    $t6, ($a0)
/* 000094 00400094 8C8F0004 */  lw    $t7, 4($a0)
/* 000098 00400098 8C990000 */  lw    $t9, ($a0)
/* 00009C 0040009C 00801025 */  move  $v0, $a0
/* 0000A0 004000A0 01CF1821 */  addu  $v1, $t6, $t7
/* 0000A4 004000A4 AC830004 */  sw    $v1, 4($a0)
/* 0000A8 004000A8 ACB90000 */  sw    $t9, ($a1)
/* 0000AC 004000AC 8C980004 */  lw    $t8, 4($a0)
/* 0000B0 004000B0 03E00008 */  jr    $ra
/* 0000B4 004000B4 ACB80004 */   sw    $t8, 4($a1)

/* 0000B8 004000B8 00000000 */  nop
/* 0000BC 004000BC 00000000 */  nop
