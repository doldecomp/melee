.set noat      # allow manual use of $at
.set noreorder # don't insert nops after branches


glabel test
/* 0000B0 004000B0 3C040041 */  lui   $a0, %hi(glob)
/* 0000B4 004000B4 3C020040 */  lui   $v0, %hi(foo)
/* 0000B8 004000B8 24840100 */  addiu $a0, $a0, %lo(glob)
/* 0000BC 004000BC 244200E4 */  addiu $v0, $v0, %lo(foo)
/* 0000C0 004000C0 3C030040 */  lui   $v1, %hi(bar)
/* 0000C4 004000C4 3C050041 */  lui   $a1, %hi(glob2)
/* 0000C8 004000C8 AC820000 */  sw    $v0, ($a0)
/* 0000CC 004000CC 246300F0 */  addiu $v1, $v1, %lo(bar)
/* 0000D0 004000D0 24A50104 */  addiu $a1, $a1, %lo(glob2)
/* 0000D4 004000D4 AC830000 */  sw    $v1, ($a0)
/* 0000D8 004000D8 ACA20000 */  sw    $v0, ($a1)
/* 0000DC 004000DC 03E00008 */  jr    $ra
/* 0000E0 004000E0 ACA30000 */   sw    $v1, ($a1)

/* 0000E4 004000E4 E7AC0000 */  swc1  $f12, ($sp)
/* 0000E8 004000E8 03E00008 */  jr    $ra
/* 0000EC 004000EC 24020001 */   addiu $v0, $zero, 1

/* 0000F0 004000F0 E7AC0000 */  swc1  $f12, ($sp)
/* 0000F4 004000F4 03E00008 */  jr    $ra
/* 0000F8 004000F8 24020002 */   addiu $v0, $zero, 2

/* 0000FC 004000FC 00000000 */  nop
