.set noat      # allow manual use of $at
.set noreorder # don't insert nops after branches


glabel test
/* 000090 00400090 27BDFFE8 */  addiu $sp, $sp, -0x18
/* 000094 00400094 46006005 */  abs.s $f0, $f12
/* 000098 00400098 46000386 */  mov.s $f14, $f0
/* 00009C 0040009C 46007004 */  sqrt.s $f0, $f14
/* 0000A0 004000A0 46000121 */  cvt.d.s $f4, $f0
/* 0000A4 004000A4 F7A40010 */  sdc1  $f4, 0x10($sp)
/* 0000A8 004000A8 D7A00010 */  ldc1  $f0, 0x10($sp)
/* 0000AC 004000AC 46200005 */  abs.d $f0, $f0
/* 0000B0 004000B0 46200406 */  mov.d $f16, $f0
/* 0000B4 004000B4 46208004 */  sqrt.d $f0, $f16
/* 0000B8 004000B8 10000003 */  b     .L004000C8
/* 0000BC 004000BC 46200020 */   cvt.s.d $f0, $f0
/* 0000C0 004000C0 10000001 */  b     .L004000C8
/* 0000C4 004000C4 00000000 */   nop
.L004000C8:
/* 0000C8 004000C8 03E00008 */  jr    $ra
/* 0000CC 004000CC 27BD0018 */   addiu $sp, $sp, 0x18
