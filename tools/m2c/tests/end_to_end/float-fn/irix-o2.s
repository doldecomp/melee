.set noat      # allow manual use of $at
.set noreorder # don't insert nops after branches


glabel test
/* 000090 00400090 27BDFFE8 */  addiu $sp, $sp, -0x18
/* 000094 00400094 AFBF0014 */  sw    $ra, 0x14($sp)
/* 000098 00400098 0C10002F */  jal   func_004000BC
/* 00009C 0040009C 00000000 */   nop
/* 0000A0 004000A0 0C100031 */  jal   func_004000C4
/* 0000A4 004000A4 46000321 */   cvt.d.s $f12, $f0
/* 0000A8 004000A8 8FBF0014 */  lw    $ra, 0x14($sp)
/* 0000AC 004000AC 27BD0018 */  addiu $sp, $sp, 0x18
/* 0000B0 004000B0 46200020 */  cvt.s.d $f0, $f0
/* 0000B4 004000B4 03E00008 */  jr    $ra
/* 0000B8 004000B8 00000000 */   nop

glabel func_004000BC
/* 0000BC 004000BC 03E00008 */  jr    $ra
/* 0000C0 004000C0 46006006 */   mov.s $f0, $f12

glabel func_004000C4
/* 0000C4 004000C4 03E00008 */  jr    $ra
/* 0000C8 004000C8 46206006 */   mov.d $f0, $f12

/* 0000CC 004000CC 00000000 */  nop
