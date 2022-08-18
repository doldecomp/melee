.set noat      # allow manual use of $at
.set noreorder # don't insert nops after branches


glabel test
/* 000090 00400090 27BDFFF0 */  addiu $sp, $sp, -0x10
/* 000094 00400094 3C013F00 */  lui   $at, 0x3f00
/* 000098 00400098 44813000 */  mtc1  $at, $f6
/* 00009C 0040009C E7AC0004 */  swc1  $f12, 4($sp)
/* 0000A0 004000A0 8FAE0004 */  lw    $t6, 4($sp)
/* 0000A4 004000A4 46066202 */  mul.s $f8, $f12, $f6
/* 0000A8 004000A8 3C185F37 */  lui   $t8, 0x5f37
/* 0000AC 004000AC 371859DF */  ori   $t8, $t8, 0x59df
/* 0000B0 004000B0 000E7843 */  sra   $t7, $t6, 1
/* 0000B4 004000B4 030FC823 */  subu  $t9, $t8, $t7
/* 0000B8 004000B8 AFAE000C */  sw    $t6, 0xc($sp)
/* 0000BC 004000BC AFB9000C */  sw    $t9, 0xc($sp)
/* 0000C0 004000C0 C7A4000C */  lwc1  $f4, 0xc($sp)
/* 0000C4 004000C4 3C013FC0 */  lui   $at, 0x3fc0
/* 0000C8 004000C8 44819000 */  mtc1  $at, $f18
/* 0000CC 004000CC 46044282 */  mul.s $f10, $f8, $f4
/* 0000D0 004000D0 E7A40004 */  swc1  $f4, 4($sp)
/* 0000D4 004000D4 46045402 */  mul.s $f16, $f10, $f4
/* 0000D8 004000D8 46109181 */  sub.s $f6, $f18, $f16
/* 0000DC 004000DC 46043002 */  mul.s $f0, $f6, $f4
/* 0000E0 004000E0 E7A00004 */  swc1  $f0, 4($sp)
/* 0000E4 004000E4 03E00008 */  jr    $ra
/* 0000E8 004000E8 27BD0010 */   addiu $sp, $sp, 0x10

/* 0000EC 004000EC 00000000 */  nop
