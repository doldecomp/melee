.set noat      # allow manual use of $at
.set noreorder # don't insert nops after branches


glabel test
/* 000090 00400090 27BDFFF8 */  addiu $sp, $sp, -8
/* 000094 00400094 AFA40008 */  sw    $a0, 8($sp)
/* 000098 00400098 AFA5000C */  sw    $a1, 0xc($sp)
/* 00009C 0040009C AFA00004 */  sw    $zero, 4($sp)
/* 0000A0 004000A0 27AE000C */  addiu $t6, $sp, 0xc
/* 0000A4 004000A4 27AF0008 */  addiu $t7, $sp, 8
/* 0000A8 004000A8 01CF1023 */  subu  $v0, $t6, $t7
/* 0000AC 004000AC 10000003 */  b     .L004000BC
/* 0000B0 004000B0 00021083 */   sra   $v0, $v0, 2
/* 0000B4 004000B4 10000001 */  b     .L004000BC
/* 0000B8 004000B8 00000000 */   nop
.L004000BC:
/* 0000BC 004000BC 03E00008 */  jr    $ra
/* 0000C0 004000C0 27BD0008 */   addiu $sp, $sp, 8

/* 0000C4 004000C4 00000000 */  nop
/* 0000C8 004000C8 00000000 */  nop
/* 0000CC 004000CC 00000000 */  nop
