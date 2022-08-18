.set noat      # allow manual use of $at
.set noreorder # don't insert nops after branches


glabel test
/* 000090 00400090 27BDFFE8 */  addiu $sp, $sp, -0x18
/* 000094 00400094 AFBF0014 */  sw    $ra, 0x14($sp)
/* 000098 00400098 AFA40018 */  sw    $a0, 0x18($sp)
/* 00009C 0040009C 8FAE0018 */  lw    $t6, 0x18($sp)
/* 0000A0 004000A0 24010007 */  addiu $at, $zero, 7
/* 0000A4 004000A4 15C1000D */  bne   $t6, $at, .L004000DC
/* 0000A8 004000A8 00000000 */   nop
/* 0000AC 004000AC 0C100047 */  jal   func_0040011C
/* 0000B0 004000B0 24040001 */   addiu $a0, $zero, 1
/* 0000B4 004000B4 8FAF0018 */  lw    $t7, 0x18($sp)
/* 0000B8 004000B8 24010008 */  addiu $at, $zero, 8
/* 0000BC 004000BC 15E10003 */  bne   $t7, $at, .L004000CC
/* 0000C0 004000C0 00000000 */   nop
/* 0000C4 004000C4 0C100047 */  jal   func_0040011C
/* 0000C8 004000C8 24040002 */   addiu $a0, $zero, 2
.L004000CC:
/* 0000CC 004000CC 0C100047 */  jal   func_0040011C
/* 0000D0 004000D0 24040003 */   addiu $a0, $zero, 3
/* 0000D4 004000D4 1000000B */  b     .L00400104
/* 0000D8 004000D8 00000000 */   nop
.L004000DC:
/* 0000DC 004000DC 0C100047 */  jal   func_0040011C
/* 0000E0 004000E0 24040004 */   addiu $a0, $zero, 4
/* 0000E4 004000E4 8FB80018 */  lw    $t8, 0x18($sp)
/* 0000E8 004000E8 24010009 */  addiu $at, $zero, 9
/* 0000EC 004000EC 17010003 */  bne   $t8, $at, .L004000FC
/* 0000F0 004000F0 00000000 */   nop
/* 0000F4 004000F4 0C100047 */  jal   func_0040011C
/* 0000F8 004000F8 24040005 */   addiu $a0, $zero, 5
.L004000FC:
/* 0000FC 004000FC 0C100047 */  jal   func_0040011C
/* 000100 00400100 24040006 */   addiu $a0, $zero, 6
.L00400104:
/* 000104 00400104 10000001 */  b     .L0040010C
/* 000108 00400108 00000000 */   nop
.L0040010C:
/* 00010C 0040010C 8FBF0014 */  lw    $ra, 0x14($sp)
/* 000110 00400110 27BD0018 */  addiu $sp, $sp, 0x18
/* 000114 00400114 03E00008 */  jr    $ra
/* 000118 00400118 00000000 */   nop

glabel func_0040011C
/* 00011C 0040011C AFA40000 */  sw    $a0, ($sp)
/* 000120 00400120 10000001 */  b     .L00400128
/* 000124 00400124 00000000 */   nop
.L00400128:
/* 000128 00400128 03E00008 */  jr    $ra
/* 00012C 0040012C 00000000 */   nop
