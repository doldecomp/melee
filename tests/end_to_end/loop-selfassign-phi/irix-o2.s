.set noat      # allow manual use of $at
.set noreorder # don't insert nops after branches


glabel test
/* 0000A0 004000A0 27BDFFE0 */  addiu $sp, $sp, -0x20
/* 0000A4 004000A4 AFB00018 */  sw    $s0, 0x18($sp)
/* 0000A8 004000A8 00808025 */  move  $s0, $a0
/* 0000AC 004000AC AFBF001C */  sw    $ra, 0x1c($sp)
.L004000B0:
/* 0000B0 004000B0 2A010003 */  slti  $at, $s0, 3
.L004000B4:
/* 0000B4 004000B4 5420FFFF */  bnezl $at, .L004000B4
/* 0000B8 004000B8 2A010003 */   slti  $at, $s0, 3
/* 0000BC 004000BC 0C10003D */  jal   func_004000F4
/* 0000C0 004000C0 02002025 */   move  $a0, $s0
/* 0000C4 004000C4 1000FFFA */  b     .L004000B0
/* 0000C8 004000C8 00408025 */   move  $s0, $v0
/* 0000CC 004000CC 00000000 */  nop
/* 0000D0 004000D0 00000000 */  nop
/* 0000D4 004000D4 00000000 */  nop
/* 0000D8 004000D8 00000000 */  nop
/* 0000DC 004000DC 00000000 */  nop
/* 0000E0 004000E0 8FBF001C */  lw    $ra, 0x1c($sp)
/* 0000E4 004000E4 8FB00018 */  lw    $s0, 0x18($sp)
/* 0000E8 004000E8 27BD0020 */  addiu $sp, $sp, 0x20
/* 0000EC 004000EC 03E00008 */  jr    $ra
/* 0000F0 004000F0 00000000 */   nop

glabel func_004000F4
/* 0000F4 004000F4 03E00008 */  jr    $ra
/* 0000F8 004000F8 00801025 */   move  $v0, $a0

/* 0000FC 004000FC 00000000 */  nop
