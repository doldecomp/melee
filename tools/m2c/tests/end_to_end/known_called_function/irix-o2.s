.set noat      # allow manual use of $at
.set noreorder # don't insert nops after branches


glabel foo
/* 0000A0 004000A0 AFA50004 */  sw    $a1, 4($sp)
/* 0000A4 004000A4 AFA60008 */  sw    $a2, 8($sp)
/* 0000A8 004000A8 03E00008 */  jr    $ra
/* 0000AC 004000AC 00801025 */   move  $v0, $a0

glabel test
/* 0000B0 004000B0 27BDFFD8 */  addiu $sp, $sp, -0x28
/* 0000B4 004000B4 AFB20020 */  sw    $s2, 0x20($sp)
/* 0000B8 004000B8 AFB1001C */  sw    $s1, 0x1c($sp)
/* 0000BC 004000BC AFB00018 */  sw    $s0, 0x18($sp)
/* 0000C0 004000C0 00A08825 */  move  $s1, $a1
/* 0000C4 004000C4 AFBF0024 */  sw    $ra, 0x24($sp)
/* 0000C8 004000C8 AFA40028 */  sw    $a0, 0x28($sp)
/* 0000CC 004000CC AFA60030 */  sw    $a2, 0x30($sp)
/* 0000D0 004000D0 AFA70034 */  sw    $a3, 0x34($sp)
/* 0000D4 004000D4 00008025 */  move  $s0, $zero
/* 0000D8 004000D8 8FB2003C */  lw    $s2, 0x3c($sp)
.L004000DC:
/* 0000DC 004000DC 02002025 */  move  $a0, $s0
/* 0000E0 004000E0 02202825 */  move  $a1, $s1
/* 0000E4 004000E4 0C100028 */  jal   foo
/* 0000E8 004000E8 02403025 */   move  $a2, $s2
/* 0000EC 004000EC 1000FFFB */  b     .L004000DC
/* 0000F0 004000F0 00408025 */   move  $s0, $v0
/* 0000F4 004000F4 00000000 */  nop
/* 0000F8 004000F8 00000000 */  nop
/* 0000FC 004000FC 00000000 */  nop
/* 000100 00400100 8FBF0024 */  lw    $ra, 0x24($sp)
/* 000104 00400104 8FB00018 */  lw    $s0, 0x18($sp)
/* 000108 00400108 8FB1001C */  lw    $s1, 0x1c($sp)
/* 00010C 0040010C 8FB20020 */  lw    $s2, 0x20($sp)
/* 000110 00400110 03E00008 */  jr    $ra
/* 000114 00400114 27BD0028 */   addiu $sp, $sp, 0x28

/* 000118 00400118 00000000 */  nop
/* 00011C 0040011C 00000000 */  nop
