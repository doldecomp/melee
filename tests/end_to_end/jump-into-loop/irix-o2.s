.set noat      # allow manual use of $at
.set noreorder # don't insert nops after branches


glabel test
/* 000090 00400090 27BDFFE0 */  addiu $sp, $sp, -0x20
/* 000094 00400094 AFB00018 */  sw    $s0, 0x18($sp)
/* 000098 00400098 00808025 */  move  $s0, $a0
/* 00009C 0040009C 10000004 */  b     .L004000B0
/* 0000A0 004000A0 AFBF001C */   sw    $ra, 0x1c($sp)
.L004000A4:
/* 0000A4 004000A4 0C100037 */  jal   func_004000DC
/* 0000A8 004000A8 02002025 */   move  $a0, $s0
/* 0000AC 004000AC 26100001 */  addiu $s0, $s0, 1
.L004000B0:
/* 0000B0 004000B0 0C100037 */  jal   func_004000DC
/* 0000B4 004000B4 02002025 */   move  $a0, $s0
/* 0000B8 004000B8 00107040 */  sll   $t6, $s0, 1
/* 0000BC 004000BC 29C10004 */  slti  $at, $t6, 4
/* 0000C0 004000C0 1420FFF8 */  bnez  $at, .L004000A4
/* 0000C4 004000C4 01C08025 */   move  $s0, $t6
/* 0000C8 004000C8 8FBF001C */  lw    $ra, 0x1c($sp)
/* 0000CC 004000CC 8FB00018 */  lw    $s0, 0x18($sp)
/* 0000D0 004000D0 27BD0020 */  addiu $sp, $sp, 0x20
/* 0000D4 004000D4 03E00008 */  jr    $ra
/* 0000D8 004000D8 01C01025 */   move  $v0, $t6

glabel func_004000DC
/* 0000DC 004000DC 03E00008 */  jr    $ra
/* 0000E0 004000E0 AFA40000 */   sw    $a0, ($sp)

/* 0000E4 004000E4 00000000 */  nop
/* 0000E8 004000E8 00000000 */  nop
/* 0000EC 004000EC 00000000 */  nop
