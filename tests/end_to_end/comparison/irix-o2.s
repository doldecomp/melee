.set noat      # allow manual use of $at
.set noreorder # don't insert nops after branches


glabel test
/* 0000B0 004000B0 3C020041 */  lui   $v0, %hi(D_410100)
/* 0000B4 004000B4 00857026 */  xor   $t6, $a0, $a1
/* 0000B8 004000B8 24420100 */  addiu $v0, $v0, %lo(D_410100)
/* 0000BC 004000BC 2DCE0001 */  sltiu $t6, $t6, 1
/* 0000C0 004000C0 00867826 */  xor   $t7, $a0, $a2
/* 0000C4 004000C4 AC4E0000 */  sw    $t6, ($v0)
/* 0000C8 004000C8 000F782B */  sltu  $t7, $zero, $t7
/* 0000CC 004000CC AC4F0000 */  sw    $t7, ($v0)
/* 0000D0 004000D0 0085C02A */  slt   $t8, $a0, $a1
/* 0000D4 004000D4 00A4C82A */  slt   $t9, $a1, $a0
/* 0000D8 004000D8 AC580000 */  sw    $t8, ($v0)
/* 0000DC 004000DC 3B390001 */  xori  $t9, $t9, 1
/* 0000E0 004000E0 AC590000 */  sw    $t9, ($v0)
/* 0000E4 004000E4 2C880001 */  sltiu $t0, $a0, 1
/* 0000E8 004000E8 AC480000 */  sw    $t0, ($v0)
/* 0000EC 004000EC 0005482B */  sltu  $t1, $zero, $a1
/* 0000F0 004000F0 03E00008 */  jr    $ra
/* 0000F4 004000F4 AC490000 */   sw    $t1, ($v0)

/* 0000F8 004000F8 00000000 */  nop
/* 0000FC 004000FC 00000000 */  nop
