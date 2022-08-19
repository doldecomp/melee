.set noat      # allow manual use of $at
.set noreorder # don't insert nops after branches


glabel test
/* 000090 00400090 27BDFFF8 */  addiu $sp, $sp, -8
/* 000094 00400094 18A00009 */  blez  $a1, .L004000BC
/* 000098 00400098 AFA00004 */   sw    $zero, 4($sp)
.L0040009C:
/* 00009C 0040009C 8FAE0004 */  lw    $t6, 4($sp)
/* 0000A0 004000A0 008E7821 */  addu  $t7, $a0, $t6
/* 0000A4 004000A4 A1E00000 */  sb    $zero, ($t7)
/* 0000A8 004000A8 8FB80004 */  lw    $t8, 4($sp)
/* 0000AC 004000AC 27190001 */  addiu $t9, $t8, 1
/* 0000B0 004000B0 0325082A */  slt   $at, $t9, $a1
/* 0000B4 004000B4 1420FFF9 */  bnez  $at, .L0040009C
/* 0000B8 004000B8 AFB90004 */   sw    $t9, 4($sp)
.L004000BC:
/* 0000BC 004000BC 10000001 */  b     .L004000C4
/* 0000C0 004000C0 00000000 */   nop
.L004000C4:
/* 0000C4 004000C4 03E00008 */  jr    $ra
/* 0000C8 004000C8 27BD0008 */   addiu $sp, $sp, 8

/* 0000CC 004000CC 00000000 */  nop
