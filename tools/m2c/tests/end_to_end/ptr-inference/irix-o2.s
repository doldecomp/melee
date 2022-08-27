.set noat      # allow manual use of $at
.set noreorder # don't insert nops after branches


glabel foo
/* 000090 00400090 AFA40000 */  sw    $a0, ($sp)
/* 000094 00400094 03E00008 */  jr    $ra
/* 000098 00400098 AFA50004 */   sw    $a1, 4($sp)

glabel test
/* 00009C 0040009C 27BDFFE0 */  addiu $sp, $sp, -0x20
/* 0000A0 004000A0 AFBF0014 */  sw    $ra, 0x14($sp)
/* 0000A4 004000A4 27A4001C */  addiu $a0, $sp, 0x1c
/* 0000A8 004000A8 0C100024 */  jal   foo
/* 0000AC 004000AC 27A50018 */   addiu $a1, $sp, 0x18
/* 0000B0 004000B0 8FBF0014 */  lw    $ra, 0x14($sp)
/* 0000B4 004000B4 27BD0020 */  addiu $sp, $sp, 0x20
/* 0000B8 004000B8 03E00008 */  jr    $ra
/* 0000BC 004000BC 00000000 */   nop
