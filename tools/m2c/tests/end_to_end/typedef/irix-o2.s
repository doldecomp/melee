.set noat      # allow manual use of $at
.set noreorder # don't insert nops after branches


glabel func_00400090
/* 000090 00400090 8CAE0000 */  lw    $t6, ($a1)
/* 000094 00400094 03E00008 */  jr    $ra
/* 000098 00400098 01C41021 */   addu  $v0, $t6, $a0

glabel test
/* 00009C 0040009C 27BDFFE0 */  addiu $sp, $sp, -0x20
/* 0000A0 004000A0 AFBF0014 */  sw    $ra, 0x14($sp)
/* 0000A4 004000A4 AFA40020 */  sw    $a0, 0x20($sp)
/* 0000A8 004000A8 0C100024 */  jal   func_00400090
/* 0000AC 004000AC AFA50024 */   sw    $a1, 0x24($sp)
/* 0000B0 004000B0 AFA20018 */  sw    $v0, 0x18($sp)
/* 0000B4 004000B4 8FA40020 */  lw    $a0, 0x20($sp)
/* 0000B8 004000B8 0C100024 */  jal   func_00400090
/* 0000BC 004000BC 27A50020 */   addiu $a1, $sp, 0x20
/* 0000C0 004000C0 8FA50024 */  lw    $a1, 0x24($sp)
/* 0000C4 004000C4 AFA2001C */  sw    $v0, 0x1c($sp)
/* 0000C8 004000C8 0C100024 */  jal   func_00400090
/* 0000CC 004000CC 8CA40000 */   lw    $a0, ($a1)
/* 0000D0 004000D0 8FAE001C */  lw    $t6, 0x1c($sp)
/* 0000D4 004000D4 8FBF0014 */  lw    $ra, 0x14($sp)
/* 0000D8 004000D8 8FB80018 */  lw    $t8, 0x18($sp)
/* 0000DC 004000DC 004E7821 */  addu  $t7, $v0, $t6
/* 0000E0 004000E0 27BD0020 */  addiu $sp, $sp, 0x20
/* 0000E4 004000E4 03E00008 */  jr    $ra
/* 0000E8 004000E8 01F81021 */   addu  $v0, $t7, $t8

/* 0000EC 004000EC 00000000 */  nop
