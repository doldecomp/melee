.set noat      # allow manual use of $at
.set noreorder # don't insert nops after branches


glabel func_00400090
/* 000090 00400090 8CAE0000 */  lw    $t6, ($a1)
/* 000094 00400094 03E00008 */  jr    $ra
/* 000098 00400098 AC8E0000 */   sw    $t6, ($a0)

glabel test
/* 00009C 0040009C 27BDFFE8 */  addiu $sp, $sp, -0x18
/* 0000A0 004000A0 AFA40018 */  sw    $a0, 0x18($sp)
/* 0000A4 004000A4 AFA5001C */  sw    $a1, 0x1c($sp)
/* 0000A8 004000A8 27A5001C */  addiu $a1, $sp, 0x1c
/* 0000AC 004000AC 27A40018 */  addiu $a0, $sp, 0x18
/* 0000B0 004000B0 AFBF0014 */  sw    $ra, 0x14($sp)
/* 0000B4 004000B4 AFA40018 */  sw    $a0, 0x18($sp)
/* 0000B8 004000B8 0C100024 */  jal   func_00400090
/* 0000BC 004000BC AFA5001C */   sw    $a1, 0x1c($sp)
/* 0000C0 004000C0 8FA5001C */  lw    $a1, 0x1c($sp)
/* 0000C4 004000C4 AFA50018 */  sw    $a1, 0x18($sp)
/* 0000C8 004000C8 0C100024 */  jal   func_00400090
/* 0000CC 004000CC 00A02025 */   move  $a0, $a1
/* 0000D0 004000D0 8FBF0014 */  lw    $ra, 0x14($sp)
/* 0000D4 004000D4 27BD0018 */  addiu $sp, $sp, 0x18
/* 0000D8 004000D8 03E00008 */  jr    $ra
/* 0000DC 004000DC 00000000 */   nop
