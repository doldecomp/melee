.set noat      # allow manual use of $at
.set noreorder # don't insert nops after branches


glabel test
/* 0000B0 004000B0 3C020041 */  lui   $v0, %hi(D_4100E0)
/* 0000B4 004000B4 3C030041 */  lui   $v1, %hi(D_4100E8)
/* 0000B8 004000B8 246300E8 */  addiu $v1, $v1, %lo(D_4100E8)
/* 0000BC 004000BC 244200E0 */  addiu $v0, $v0, %lo(D_4100E0)
/* 0000C0 004000C0 C4400000 */  lwc1  $f0, ($v0)
/* 0000C4 004000C4 D4620000 */  ldc1  $f2, ($v1)
/* 0000C8 004000C8 46000100 */  add.s $f4, $f0, $f0
/* 0000CC 004000CC 46221180 */  add.d $f6, $f2, $f2
/* 0000D0 004000D0 E4440000 */  swc1  $f4, ($v0)
/* 0000D4 004000D4 03E00008 */  jr    $ra
/* 0000D8 004000D8 F4660000 */   sdc1  $f6, ($v1)

/* 0000DC 004000DC 00000000 */  nop
