.set noat      # allow manual use of $at
.set noreorder # don't insert nops after branches


glabel test
/* 000090 00400090 14800003 */  bnez  $a0, .L004000A0
/* 000094 00400094 00000000 */   nop
/* 000098 00400098 50A00008 */  beql  $a1, $zero, .L004000BC
/* 00009C 0040009C 00C71021 */   addu  $v0, $a2, $a3
.L004000A0:
/* 0000A0 004000A0 14C00003 */  bnez  $a2, .L004000B0
/* 0000A4 004000A4 00000000 */   nop
/* 0000A8 004000A8 50E00004 */  beql  $a3, $zero, .L004000BC
/* 0000AC 004000AC 00C71021 */   addu  $v0, $a2, $a3
.L004000B0:
/* 0000B0 004000B0 03E00008 */  jr    $ra
/* 0000B4 004000B4 00851021 */   addu  $v0, $a0, $a1

/* 0000B8 004000B8 00C71021 */  addu  $v0, $a2, $a3
.L004000BC:
/* 0000BC 004000BC 03E00008 */  jr    $ra
/* 0000C0 004000C0 00000000 */   nop

/* 0000C4 004000C4 00000000 */  nop
/* 0000C8 004000C8 00000000 */  nop
/* 0000CC 004000CC 00000000 */  nop
