.set noat      # allow manual use of $at
.set noreorder # don't insert nops after branches


glabel test
/* 0000B0 004000B0 3C040041 */  lui   $a0, %hi(D_4100E0)
/* 0000B4 004000B4 248400E0 */  addiu $a0, $a0, %lo(D_4100E0)
/* 0000B8 004000B8 8C830000 */  lw    $v1, ($a0)
/* 0000BC 004000BC 24020006 */  addiu $v0, $zero, 6
/* 0000C0 004000C0 246EFFFF */  addiu $t6, $v1, -1
/* 0000C4 004000C4 1C600003 */  bgtz  $v1, .L004000D4
/* 0000C8 004000C8 AC8E0000 */   sw    $t6, ($a0)
/* 0000CC 004000CC 03E00008 */  jr    $ra
/* 0000D0 004000D0 24020004 */   addiu $v0, $zero, 4

.L004000D4:
/* 0000D4 004000D4 03E00008 */  jr    $ra
/* 0000D8 004000D8 00000000 */   nop

/* 0000DC 004000DC 00000000 */  nop
