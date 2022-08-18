.set noat      # allow manual use of $at
.set noreorder # don't insert nops after branches


glabel test
/* 0000B0 004000B0 27BDFFF8 */  addiu $sp, $sp, -8
/* 0000B4 004000B4 3C0E0041 */  lui   $t6, %hi(D_4100F0)
/* 0000B8 004000B8 8DCE00F0 */  lw    $t6, %lo(D_4100F0)($t6)
/* 0000BC 004000BC 3C010041 */  lui   $at, %hi(D_4100F0)
/* 0000C0 004000C0 29C40001 */  slti  $a0, $t6, 1
/* 0000C4 004000C4 25CFFFFF */  addiu $t7, $t6, -1
/* 0000C8 004000C8 10800003 */  beqz  $a0, .L004000D8
/* 0000CC 004000CC AC2F00F0 */   sw    $t7, %lo(D_4100F0)($at)
/* 0000D0 004000D0 10000005 */  b     .L004000E8
/* 0000D4 004000D4 24020004 */   addiu $v0, $zero, 4
.L004000D8:
/* 0000D8 004000D8 10000003 */  b     .L004000E8
/* 0000DC 004000DC 24020006 */   addiu $v0, $zero, 6
/* 0000E0 004000E0 10000001 */  b     .L004000E8
/* 0000E4 004000E4 00000000 */   nop
.L004000E8:
/* 0000E8 004000E8 03E00008 */  jr    $ra
/* 0000EC 004000EC 27BD0008 */   addiu $sp, $sp, 8
