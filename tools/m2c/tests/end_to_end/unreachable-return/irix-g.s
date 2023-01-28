.set noat      # allow manual use of $at
.set noreorder # don't insert nops after branches


glabel test
.L004000B0:
/* 0000B0 004000B0 240E0001 */  addiu $t6, $zero, 1
/* 0000B4 004000B4 3C010041 */  lui   $at, %hi(D_4100E0)
/* 0000B8 004000B8 AC2E00E0 */  sw    $t6, %lo(D_4100E0)($at)
/* 0000BC 004000BC 1000FFFC */  b     .L004000B0
/* 0000C0 004000C0 00000000 */   nop
/* 0000C4 004000C4 03E00008 */  jr    $ra
/* 0000C8 004000C8 00000000 */   nop

/* 0000CC 004000CC 03E00008 */  jr    $ra
/* 0000D0 004000D0 00000000 */   nop

/* 0000D4 004000D4 00000000 */  nop
/* 0000D8 004000D8 00000000 */  nop
/* 0000DC 004000DC 00000000 */  nop
