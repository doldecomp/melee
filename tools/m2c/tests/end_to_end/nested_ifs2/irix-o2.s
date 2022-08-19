.set noat      # allow manual use of $at
.set noreorder # don't insert nops after branches


glabel test
/* 000090 00400090 27BDFFE8 */  addiu $sp, $sp, -0x18
/* 000094 00400094 24010007 */  addiu $at, $zero, 7
/* 000098 00400098 AFBF0014 */  sw    $ra, 0x14($sp)
/* 00009C 0040009C 1481000E */  bne   $a0, $at, .L004000D8
/* 0000A0 004000A0 00802825 */   move  $a1, $a0
/* 0000A4 004000A4 24040001 */  addiu $a0, $zero, 1
/* 0000A8 004000A8 0C10003C */  jal   func_004000F0
/* 0000AC 004000AC AFA50018 */   sw    $a1, 0x18($sp)
/* 0000B0 004000B0 8FA50018 */  lw    $a1, 0x18($sp)
/* 0000B4 004000B4 24010008 */  addiu $at, $zero, 8
/* 0000B8 004000B8 14A10003 */  bne   $a1, $at, .L004000C8
/* 0000BC 004000BC 00000000 */   nop
/* 0000C0 004000C0 0C10003C */  jal   func_004000F0
/* 0000C4 004000C4 24040002 */   addiu $a0, $zero, 2
.L004000C8:
/* 0000C8 004000C8 0C10003C */  jal   func_004000F0
/* 0000CC 004000CC 24040003 */   addiu $a0, $zero, 3
/* 0000D0 004000D0 10000004 */  b     .L004000E4
/* 0000D4 004000D4 8FBF0014 */   lw    $ra, 0x14($sp)
.L004000D8:
/* 0000D8 004000D8 0C10003C */  jal   func_004000F0
/* 0000DC 004000DC 24040004 */   addiu $a0, $zero, 4
/* 0000E0 004000E0 8FBF0014 */  lw    $ra, 0x14($sp)
.L004000E4:
/* 0000E4 004000E4 27BD0018 */  addiu $sp, $sp, 0x18
/* 0000E8 004000E8 03E00008 */  jr    $ra
/* 0000EC 004000EC 00000000 */   nop

glabel func_004000F0
/* 0000F0 004000F0 03E00008 */  jr    $ra
/* 0000F4 004000F4 AFA40000 */   sw    $a0, ($sp)

/* 0000F8 004000F8 00000000 */  nop
/* 0000FC 004000FC 00000000 */  nop
