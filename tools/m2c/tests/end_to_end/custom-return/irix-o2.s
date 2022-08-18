.set noat      # allow manual use of $at
.set noreorder # don't insert nops after branches


glabel test
/* 0000B0 004000B0 27BDFFE8 */  addiu $sp, $sp, -0x18
/* 0000B4 004000B4 AFBF0014 */  sw    $ra, 0x14($sp)
/* 0000B8 004000B8 0C100043 */  jal   func_0040010C
/* 0000BC 004000BC 24040001 */   addiu $a0, $zero, 1
/* 0000C0 004000C0 10400003 */  beqz  $v0, .L004000D0
/* 0000C4 004000C4 3043FFFF */   andi  $v1, $v0, 0xffff
/* 0000C8 004000C8 1000000C */  b     .L004000FC
/* 0000CC 004000CC 00601025 */   move  $v0, $v1
.L004000D0:
/* 0000D0 004000D0 3C0E0041 */  lui   $t6, %hi(D_410120)
/* 0000D4 004000D4 8DCE0120 */  lw    $t6, %lo(D_410120)($t6)
/* 0000D8 004000D8 2401007B */  addiu $at, $zero, 0x7b
/* 0000DC 004000DC 11C10005 */  beq   $t6, $at, .L004000F4
/* 0000E0 004000E0 00000000 */   nop
/* 0000E4 004000E4 0C100043 */  jal   func_0040010C
/* 0000E8 004000E8 24040002 */   addiu $a0, $zero, 2
/* 0000EC 004000EC 10000004 */  b     .L00400100
/* 0000F0 004000F0 8FBF0014 */   lw    $ra, 0x14($sp)
.L004000F4:
/* 0000F4 004000F4 0C100043 */  jal   func_0040010C
/* 0000F8 004000F8 24040003 */   addiu $a0, $zero, 3
.L004000FC:
/* 0000FC 004000FC 8FBF0014 */  lw    $ra, 0x14($sp)
.L00400100:
/* 000100 00400100 27BD0018 */  addiu $sp, $sp, 0x18
/* 000104 00400104 03E00008 */  jr    $ra
/* 000108 00400108 00000000 */   nop

glabel func_0040010C
/* 00010C 0040010C AFA40000 */  sw    $a0, ($sp)
/* 000110 00400110 03E00008 */  jr    $ra
/* 000114 00400114 24020001 */   addiu $v0, $zero, 1

/* 000118 00400118 00000000 */  nop
/* 00011C 0040011C 00000000 */  nop
