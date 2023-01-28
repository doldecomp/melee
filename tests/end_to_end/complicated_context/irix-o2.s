.set noat      # allow manual use of $at
.set noreorder # don't insert nops after branches

glabel func_decl
/* 0000B0 004000B0 3C010041 */  lui   $at, %hi(globali)
/* 0000B4 004000B4 03E00008 */  jr    $ra
/* 0000B8 004000B8 AC200110 */   sw    $zero, %lo(globali)($at)

glabel test
/* 0000BC 004000BC 27BDFFF8 */  addiu $sp, $sp, -8
/* 0000C0 004000C0 30AE00FF */  andi  $t6, $a1, 0xff
/* 0000C4 004000C4 AFA5000C */  sw    $a1, 0xc($sp)
/* 0000C8 004000C8 AFA60010 */  sw    $a2, 0x10($sp)
/* 0000CC 004000CC 11C00009 */  beqz  $t6, .L004000F4
/* 0000D0 004000D0 AFA70014 */   sw    $a3, 0x14($sp)
/* 0000D4 004000D4 C4840004 */  lwc1  $f4, 4($a0)
/* 0000D8 004000D8 3C010041 */  lui   $at, %hi(globalf)
/* 0000DC 004000DC E4240114 */  swc1  $f4, %lo(globalf)($at)
/* 0000E0 004000E0 8C8F0000 */  lw    $t7, ($a0)
/* 0000E4 004000E4 3C010041 */  lui   $at, %hi(globali)
/* 0000E8 004000E8 AC2F0110 */  sw    $t7, %lo(globali)($at)
/* 0000EC 004000EC 10000005 */  b     .L00400104
/* 0000F0 004000F0 A08E0010 */   sb    $t6, 0x10($a0)
.L004000F4:
/* 0000F4 004000F4 44803800 */  mtc1  $zero, $f7
/* 0000F8 004000F8 44803000 */  mtc1  $zero, $f6
/* 0000FC 004000FC AC800008 */  sw    $zero, 8($a0)
/* 000100 00400100 F4860010 */  sdc1  $f6, 0x10($a0)
.L00400104:
/* 000104 00400104 84820002 */  lh    $v0, 2($a0)
/* 000108 00400108 03E00008 */  jr    $ra
/* 00010C 0040010C 27BD0008 */   addiu $sp, $sp, 8
