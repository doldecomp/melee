.set noat      # allow manual use of $at
.set noreorder # don't insert nops after branches


glabel test
/* 000090 00400090 00063400 */  sll   $a2, $a2, 0x10
/* 000094 00400094 00063403 */  sra   $a2, $a2, 0x10
/* 000098 00400098 240E0002 */  addiu $t6, $zero, 2
/* 00009C 0040009C A48E0008 */  sh    $t6, 8($a0)
/* 0000A0 004000A0 A485000A */  sh    $a1, 0xa($a0)
/* 0000A4 004000A4 A486000C */  sh    $a2, 0xc($a0)
/* 0000A8 004000A8 00C57821 */  addu  $t7, $a2, $a1
/* 0000AC 004000AC A48F000E */  sh    $t7, 0xe($a0)
/* 0000B0 004000B0 03E00008 */  jr    $ra
/* 0000B4 004000B4 00000000 */   nop

/* 0000B8 004000B8 03E00008 */  jr    $ra
/* 0000BC 004000BC 00000000 */   nop
