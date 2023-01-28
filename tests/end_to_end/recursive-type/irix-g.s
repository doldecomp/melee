.set noat      # allow manual use of $at
.set noreorder # don't insert nops after branches


glabel func_00400090
/* 000090 00400090 8CAE0000 */  lw    $t6, ($a1)
/* 000094 00400094 AC8E0000 */  sw    $t6, ($a0)
/* 000098 00400098 03E00008 */  jr    $ra
/* 00009C 0040009C 00000000 */   nop

/* 0000A0 004000A0 03E00008 */  jr    $ra
/* 0000A4 004000A4 00000000 */   nop

glabel test
/* 0000A8 004000A8 27BDFFE8 */  addiu $sp, $sp, -0x18
/* 0000AC 004000AC AFBF0014 */  sw    $ra, 0x14($sp)
/* 0000B0 004000B0 AFA40018 */  sw    $a0, 0x18($sp)
/* 0000B4 004000B4 AFA5001C */  sw    $a1, 0x1c($sp)
/* 0000B8 004000B8 27AE0018 */  addiu $t6, $sp, 0x18
/* 0000BC 004000BC AFAE0018 */  sw    $t6, 0x18($sp)
/* 0000C0 004000C0 27AF001C */  addiu $t7, $sp, 0x1c
/* 0000C4 004000C4 AFAF001C */  sw    $t7, 0x1c($sp)
/* 0000C8 004000C8 8FA40018 */  lw    $a0, 0x18($sp)
/* 0000CC 004000CC 0C100024 */  jal   func_00400090
/* 0000D0 004000D0 8FA5001C */   lw    $a1, 0x1c($sp)
/* 0000D4 004000D4 8FB8001C */  lw    $t8, 0x1c($sp)
/* 0000D8 004000D8 AFB80018 */  sw    $t8, 0x18($sp)
/* 0000DC 004000DC 8FA40018 */  lw    $a0, 0x18($sp)
/* 0000E0 004000E0 0C100024 */  jal   func_00400090
/* 0000E4 004000E4 8FA5001C */   lw    $a1, 0x1c($sp)
/* 0000E8 004000E8 10000001 */  b     .L004000F0
/* 0000EC 004000EC 00000000 */   nop
.L004000F0:
/* 0000F0 004000F0 8FBF0014 */  lw    $ra, 0x14($sp)
/* 0000F4 004000F4 27BD0018 */  addiu $sp, $sp, 0x18
/* 0000F8 004000F8 03E00008 */  jr    $ra
/* 0000FC 004000FC 00000000 */   nop
