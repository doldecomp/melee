.set noat      # allow manual use of $at
.set noreorder # don't insert nops after branches


glabel test
/* 0000B0 004000B0 4600610D */  trunc.w.s $f4, $f12
/* 0000B4 004000B4 44853000 */  mtc1  $a1, $f6
/* 0000B8 004000B8 3C010041 */  lui   $at, %hi(D_410140)
/* 0000BC 004000BC 44867000 */  mtc1  $a2, $f14
/* 0000C0 004000C0 46803220 */  cvt.s.w $f8, $f6
/* 0000C4 004000C4 440F2000 */  mfc1  $t7, $f4
/* 0000C8 004000C8 44808000 */  mtc1  $zero, $f16
/* 0000CC 004000CC 24E70003 */  addiu $a3, $a3, 3
/* 0000D0 004000D0 AC2F0140 */  sw    $t7, %lo(D_410140)($at)
/* 0000D4 004000D4 3C010041 */  lui   $at, %hi(D_410144)
/* 0000D8 004000D8 E4280144 */  swc1  $f8, %lo(D_410144)($at)
/* 0000DC 004000DC 3C014014 */  lui   $at, 0x4014
/* 0000E0 004000E0 44818800 */  mtc1  $at, $f17
/* 0000E4 004000E4 460072A1 */  cvt.d.s $f10, $f14
/* 0000E8 004000E8 3C010040 */  lui   $at, %hi(D_400130)
/* 0000EC 004000EC 46305480 */  add.d $f18, $f10, $f16
/* 0000F0 004000F0 D4280130 */  ldc1  $f8, %lo(D_400130)($at)
/* 0000F4 004000F4 44878000 */  mtc1  $a3, $f16
/* 0000F8 004000F8 3C014F80 */  lui   $at, 0x4f80
/* 0000FC 004000FC 462093A0 */  cvt.s.d $f14, $f18
/* 000100 00400100 468084A0 */  cvt.s.w $f18, $f16
/* 000104 00400104 46007121 */  cvt.d.s $f4, $f14
/* 000108 00400108 462023A0 */  cvt.s.d $f14, $f4
/* 00010C 0040010C 460071A1 */  cvt.d.s $f6, $f14
/* 000110 00400110 46283280 */  add.d $f10, $f6, $f8
/* 000114 00400114 04E10004 */  bgez  $a3, .L00400128
/* 000118 00400118 462053A0 */   cvt.s.d $f14, $f10
/* 00011C 0040011C 44812000 */  mtc1  $at, $f4
/* 000120 00400120 00000000 */  nop
/* 000124 00400124 46049480 */  add.s $f18, $f18, $f4
.L00400128:
/* 000128 00400128 03E00008 */  jr    $ra
/* 00012C 0040012C 460E9000 */   add.s $f0, $f18, $f14
