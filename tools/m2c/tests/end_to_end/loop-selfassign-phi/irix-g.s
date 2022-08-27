.set noat      # allow manual use of $at
.set noreorder # don't insert nops after branches


glabel test
/* 000090 00400090 27BDFFE8 */  addiu $sp, $sp, -0x18
/* 000094 00400094 AFBF0014 */  sw    $ra, 0x14($sp)
/* 000098 00400098 AFA40018 */  sw    $a0, 0x18($sp)
.L0040009C:
/* 00009C 0040009C 8FAE0018 */  lw    $t6, 0x18($sp)
/* 0000A0 004000A0 29C10003 */  slti  $at, $t6, 3
/* 0000A4 004000A4 14200004 */  bnez  $at, .L004000B8
/* 0000A8 004000A8 00000000 */   nop
/* 0000AC 004000AC 0C100036 */  jal   func_004000D8
/* 0000B0 004000B0 8FA40018 */   lw    $a0, 0x18($sp)
/* 0000B4 004000B4 AFA20018 */  sw    $v0, 0x18($sp)
.L004000B8:
/* 0000B8 004000B8 1000FFF8 */  b     .L0040009C
/* 0000BC 004000BC 00000000 */   nop
/* 0000C0 004000C0 10000001 */  b     .L004000C8
/* 0000C4 004000C4 00000000 */   nop
.L004000C8:
/* 0000C8 004000C8 8FBF0014 */  lw    $ra, 0x14($sp)
/* 0000CC 004000CC 27BD0018 */  addiu $sp, $sp, 0x18
/* 0000D0 004000D0 03E00008 */  jr    $ra
/* 0000D4 004000D4 00000000 */   nop

glabel func_004000D8
/* 0000D8 004000D8 03E00008 */  jr    $ra
/* 0000DC 004000DC 00801025 */   move  $v0, $a0

/* 0000E0 004000E0 03E00008 */  jr    $ra
/* 0000E4 004000E4 00000000 */   nop

/* 0000E8 004000E8 03E00008 */  jr    $ra
/* 0000EC 004000EC 00000000 */   nop
