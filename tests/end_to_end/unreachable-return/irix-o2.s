.set noat      # allow manual use of $at
.set noreorder # don't insert nops after branches


glabel test
/* 0000C0 004000C0 240E0001 */  addiu $t6, $zero, 1
/* 0000C4 004000C4 3C010041 */  lui   $at, %hi(D_4100F0)
/* 0000C8 004000C8 AC2E00F0 */  sw    $t6, %lo(D_4100F0)($at)
.L004000CC:
/* 0000CC 004000CC 1000FFFF */  b     .L004000CC
/* 0000D0 004000D0 00000000 */   nop
/* 0000D4 004000D4 00000000 */  nop
/* 0000D8 004000D8 00000000 */  nop
/* 0000DC 004000DC 00000000 */  nop
/* 0000E0 004000E0 03E00008 */  jr    $ra
/* 0000E4 004000E4 00000000 */   nop

/* 0000E8 004000E8 00000000 */  nop
/* 0000EC 004000EC 00000000 */  nop
