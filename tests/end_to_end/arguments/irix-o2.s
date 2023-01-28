.set noat      # allow manual use of $at
.set noreorder # don't insert nops after branches


glabel test
/* 0000B0 004000B0 44867000 */  mtc1  $a2, $f14
/* 0000B4 004000B4 C7A60010 */  lwc1  $f6, 0x10($sp)
/* 0000B8 004000B8 8FAF0014 */  lw    $t7, 0x14($sp)
/* 0000BC 004000BC 460E6100 */  add.s $f4, $f12, $f14
/* 0000C0 004000C0 3C010041 */  lui   $at, %hi(D_4100E4)
/* 0000C4 004000C4 00A77021 */  addu  $t6, $a1, $a3
/* 0000C8 004000C8 01CFC021 */  addu  $t8, $t6, $t7
/* 0000CC 004000CC 46062200 */  add.s $f8, $f4, $f6
/* 0000D0 004000D0 E42800E4 */  swc1  $f8, %lo(D_4100E4)($at)
/* 0000D4 004000D4 3C010041 */  lui   $at, %hi(D_4100E0)
/* 0000D8 004000D8 03E00008 */  jr    $ra
/* 0000DC 004000DC AC3800E0 */   sw    $t8, %lo(D_4100E0)($at)
