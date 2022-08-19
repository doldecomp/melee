.set noat      # allow manual use of $at
.set noreorder # don't insert nops after branches


glabel func_004000B0
/* 0000B0 004000B0 03E00008 */  jr    $ra
/* 0000B4 004000B4 00000000 */   nop

glabel test
/* 0000B8 004000B8 27BDFFE8 */  addiu $sp, $sp, -0x18
/* 0000BC 004000BC AFBF0014 */  sw    $ra, 0x14($sp)
/* 0000C0 004000C0 0C10002C */  jal   func_004000B0
/* 0000C4 004000C4 00000000 */   nop
/* 0000C8 004000C8 8FBF0014 */  lw    $ra, 0x14($sp)
/* 0000CC 004000CC 240E0004 */  addiu $t6, $zero, 4
/* 0000D0 004000D0 3C010041 */  lui   $at, %hi(D_4100E0)
/* 0000D4 004000D4 AC2E00E0 */  sw    $t6, %lo(D_4100E0)($at)
/* 0000D8 004000D8 03E00008 */  jr    $ra
/* 0000DC 004000DC 27BD0018 */   addiu $sp, $sp, 0x18
