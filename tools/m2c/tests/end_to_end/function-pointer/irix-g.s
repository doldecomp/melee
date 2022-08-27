.set noat      # allow manual use of $at
.set noreorder # don't insert nops after branches


glabel test
/* 000090 00400090 27BDFFE8 */  addiu $sp, $sp, -0x18
/* 000094 00400094 AFBF0014 */  sw    $ra, 0x14($sp)
/* 000098 00400098 AFA40018 */  sw    $a0, 0x18($sp)
/* 00009C 0040009C AFA5001C */  sw    $a1, 0x1c($sp)
/* 0000A0 004000A0 8FB90018 */  lw    $t9, 0x18($sp)
/* 0000A4 004000A4 8FA4001C */  lw    $a0, 0x1c($sp)
/* 0000A8 004000A8 0320F809 */  jalr  $t9
/* 0000AC 004000AC 00000000 */  nop
/* 0000B0 004000B0 10000003 */  b     .L004000C0
/* 0000B4 004000B4 24420001 */   addiu $v0, $v0, 1
/* 0000B8 004000B8 10000001 */  b     .L004000C0
/* 0000BC 004000BC 00000000 */   nop
.L004000C0:
/* 0000C0 004000C0 8FBF0014 */  lw    $ra, 0x14($sp)
/* 0000C4 004000C4 27BD0018 */  addiu $sp, $sp, 0x18
/* 0000C8 004000C8 03E00008 */  jr    $ra
/* 0000CC 004000CC 00000000 */   nop
