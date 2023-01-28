.set noat      # allow manual use of $at
.set noreorder # don't insert nops after branches


glabel test
/* 000090 00400090 27BDFFF8 */  addiu $sp, $sp, -8
/* 000094 00400094 AFA00004 */  sw    $zero, 4($sp)
/* 000098 00400098 10800003 */  beqz  $a0, .L004000A8
/* 00009C 0040009C 00000000 */   nop
/* 0000A0 004000A0 240E0001 */  addiu $t6, $zero, 1
/* 0000A4 004000A4 AFAE0004 */  sw    $t6, 4($sp)
.L004000A8:
/* 0000A8 004000A8 10000003 */  b     .L004000B8
/* 0000AC 004000AC 8FA20004 */   lw    $v0, 4($sp)
/* 0000B0 004000B0 10000001 */  b     .L004000B8
/* 0000B4 004000B4 00000000 */   nop
.L004000B8:
/* 0000B8 004000B8 03E00008 */  jr    $ra
/* 0000BC 004000BC 27BD0008 */   addiu $sp, $sp, 8
