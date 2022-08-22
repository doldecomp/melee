.set noat      # allow manual use of $at
.set noreorder # don't insert nops after branches


glabel test
/* 000090 00400090 1880000A */  blez  $a0, .L004000BC
/* 000094 00400094 00001825 */   move  $v1, $zero
/* 000098 00400098 24020005 */  addiu $v0, $zero, 5
.L0040009C:
/* 00009C 0040009C 14620003 */  bne   $v1, $v0, .L004000AC
/* 0000A0 004000A0 00037040 */   sll   $t6, $v1, 1
/* 0000A4 004000A4 10000002 */  b     .L004000B0
/* 0000A8 004000A8 01C01825 */   move  $v1, $t6
.L004000AC:
/* 0000AC 004000AC 24630004 */  addiu $v1, $v1, 4
.L004000B0:
/* 0000B0 004000B0 0064082A */  slt   $at, $v1, $a0
/* 0000B4 004000B4 1420FFF9 */  bnez  $at, .L0040009C
/* 0000B8 004000B8 00000000 */   nop
.L004000BC:
/* 0000BC 004000BC 03E00008 */  jr    $ra
/* 0000C0 004000C0 00601025 */   move  $v0, $v1

/* 0000C4 004000C4 00000000 */  nop
/* 0000C8 004000C8 00000000 */  nop
/* 0000CC 004000CC 00000000 */  nop
