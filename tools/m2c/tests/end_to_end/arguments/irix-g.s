.set noat      # allow manual use of $at
.set noreorder # don't insert nops after branches


glabel test
/* 0000B0 004000B0 AFA60008 */  sw    $a2, 8($sp)
/* 0000B4 004000B4 C7A40008 */  lwc1  $f4, 8($sp)
/* 0000B8 004000B8 C7A80010 */  lwc1  $f8, 0x10($sp)
/* 0000BC 004000BC 3C010041 */  lui   $at, %hi(D_4100F4)
/* 0000C0 004000C0 46046180 */  add.s $f6, $f12, $f4
/* 0000C4 004000C4 46083280 */  add.s $f10, $f6, $f8
/* 0000C8 004000C8 E42A00F4 */  swc1  $f10, %lo(D_4100F4)($at)
/* 0000CC 004000CC 8FAF0014 */  lw    $t7, 0x14($sp)
/* 0000D0 004000D0 00A77021 */  addu  $t6, $a1, $a3
/* 0000D4 004000D4 3C010041 */  lui   $at, %hi(D_4100F0)
/* 0000D8 004000D8 01CFC021 */  addu  $t8, $t6, $t7
/* 0000DC 004000DC AC3800F0 */  sw    $t8, %lo(D_4100F0)($at)
/* 0000E0 004000E0 10000001 */  b     .L004000E8
/* 0000E4 004000E4 00000000 */   nop
.L004000E8:
/* 0000E8 004000E8 03E00008 */  jr    $ra
/* 0000EC 004000EC 00000000 */   nop
