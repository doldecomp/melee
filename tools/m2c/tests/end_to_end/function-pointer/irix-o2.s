.set noat      # allow manual use of $at
.set noreorder # don't insert nops after branches


glabel test
/* 000090 00400090 27BDFFE8 */  addiu $sp, $sp, -0x18
/* 000094 00400094 AFBF0014 */  sw    $ra, 0x14($sp)
/* 000098 00400098 00803025 */  move  $a2, $a0
/* 00009C 0040009C 00C0F809 */  jalr  $a2
/* 0000A0 004000A0 00A02025 */  move  $a0, $a1
/* 0000A4 004000A4 8FBF0014 */  lw    $ra, 0x14($sp)
/* 0000A8 004000A8 27BD0018 */  addiu $sp, $sp, 0x18
/* 0000AC 004000AC 24420001 */  addiu $v0, $v0, 1
/* 0000B0 004000B0 03E00008 */  jr    $ra
/* 0000B4 004000B4 00000000 */   nop

/* 0000B8 004000B8 00000000 */  nop
/* 0000BC 004000BC 00000000 */  nop
