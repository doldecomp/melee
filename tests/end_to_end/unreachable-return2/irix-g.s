.set noat      # allow manual use of $at
.set noreorder # don't insert nops after branches


glabel test
.L004000B0:
/* 0000B0 004000B0 3C0E0041 */  lui   $t6, %hi(D_4100F0)
/* 0000B4 004000B4 8DCE00F0 */  lw    $t6, %lo(D_4100F0)($t6)
/* 0000B8 004000B8 24010002 */  addiu $at, $zero, 2
/* 0000BC 004000BC 15C10003 */  bne   $t6, $at, .L004000CC
/* 0000C0 004000C0 00000000 */   nop
/* 0000C4 004000C4 10000006 */  b     .L004000E0
/* 0000C8 004000C8 00000000 */   nop
.L004000CC:
/* 0000CC 004000CC 240F0001 */  addiu $t7, $zero, 1
/* 0000D0 004000D0 3C010041 */  lui   $at, %hi(D_4100F0)
/* 0000D4 004000D4 AC2F00F0 */  sw    $t7, %lo(D_4100F0)($at)
/* 0000D8 004000D8 1000FFF5 */  b     .L004000B0
/* 0000DC 004000DC 00000000 */   nop
.L004000E0:
/* 0000E0 004000E0 03E00008 */  jr    $ra
/* 0000E4 004000E4 00000000 */   nop

/* 0000E8 004000E8 03E00008 */  jr    $ra
/* 0000EC 004000EC 00000000 */   nop
