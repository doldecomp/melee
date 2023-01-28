.set noat      # allow manual use of $at
.set noreorder # don't insert nops after branches


glabel test
/* 000090 00400090 27AE0004 */  addiu $t6, $sp, 4
/* 000094 00400094 27AF0000 */  addiu $t7, $sp, 0
/* 000098 00400098 01CF1023 */  subu  $v0, $t6, $t7
/* 00009C 0040009C AFA40000 */  sw    $a0, ($sp)
/* 0000A0 004000A0 AFA50004 */  sw    $a1, 4($sp)
/* 0000A4 004000A4 03E00008 */  jr    $ra
/* 0000A8 004000A8 00021083 */   sra   $v0, $v0, 2

/* 0000AC 004000AC 00000000 */  nop
