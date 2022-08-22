.set noat      # allow manual use of $at
.set noreorder # don't insert nops after branches


glabel test
/* 0000B0 004000B0 27BDFFE8 */  addiu $sp, $sp, -0x18
/* 0000B4 004000B4 AFBF0014 */  sw    $ra, 0x14($sp)
/* 0000B8 004000B8 0C100039 */  jal   func_004000E4
/* 0000BC 004000BC 00000000 */   nop
/* 0000C0 004000C0 240E0001 */  addiu $t6, $zero, 1
/* 0000C4 004000C4 3C010041 */  lui   $at, %hi(D_410100)
/* 0000C8 004000C8 AC2E0100 */  sw    $t6, %lo(D_410100)($at)
/* 0000CC 004000CC 0C10003B */  jal   func_004000EC
/* 0000D0 004000D0 00402025 */   move  $a0, $v0
/* 0000D4 004000D4 8FBF0014 */  lw    $ra, 0x14($sp)
/* 0000D8 004000D8 27BD0018 */  addiu $sp, $sp, 0x18
/* 0000DC 004000DC 03E00008 */  jr    $ra
/* 0000E0 004000E0 00000000 */   nop

glabel func_004000E4
/* 0000E4 004000E4 03E00008 */  jr    $ra
/* 0000E8 004000E8 24020001 */   addiu $v0, $zero, 1

glabel func_004000EC
/* 0000EC 004000EC 03E00008 */  jr    $ra
/* 0000F0 004000F0 AFA40000 */   sw    $a0, ($sp)

/* 0000F4 004000F4 00000000 */  nop
/* 0000F8 004000F8 00000000 */  nop
/* 0000FC 004000FC 00000000 */  nop
