.set noat      # allow manual use of $at
.set noreorder # don't insert nops after branches


glabel test
/* 0000B0 004000B0 3C0F0041 */  lui   $t7, %hi(D_4102E0)
/* 0000B4 004000B4 25EF02E0 */  addiu $t7, $t7, %lo(D_4102E0)
/* 0000B8 004000B8 3C0E0041 */  lui   $t6, %hi(D_410150)
/* 0000BC 004000BC 25CE0150 */  addiu $t6, $t6, %lo(D_410150)
/* 0000C0 004000C0 25E8018C */  addiu $t0, $t7, 0x18c
.L004000C4:
/* 0000C4 004000C4 8DE10000 */  lw    $at, ($t7)
/* 0000C8 004000C8 25EF000C */  addiu $t7, $t7, 0xc
/* 0000CC 004000CC 25CE000C */  addiu $t6, $t6, 0xc
/* 0000D0 004000D0 ADC1FFF4 */  sw    $at, -0xc($t6)
/* 0000D4 004000D4 8DE1FFF8 */  lw    $at, -8($t7)
/* 0000D8 004000D8 ADC1FFF8 */  sw    $at, -8($t6)
/* 0000DC 004000DC 8DE1FFFC */  lw    $at, -4($t7)
/* 0000E0 004000E0 15E8FFF8 */  bne   $t7, $t0, .L004000C4
/* 0000E4 004000E4 ADC1FFFC */   sw    $at, -4($t6)
/* 0000E8 004000E8 8DE10000 */  lw    $at, ($t7)
/* 0000EC 004000EC 00A06025 */  move  $t4, $a1
/* 0000F0 004000F0 00806825 */  move  $t5, $a0
/* 0000F4 004000F4 24AB0060 */  addiu $t3, $a1, 0x60
/* 0000F8 004000F8 ADC10000 */  sw    $at, ($t6)
.L004000FC:
/* 0000FC 004000FC 89810000 */  lwl   $at, ($t4)
/* 000100 00400100 99810003 */  lwr   $at, 3($t4)
/* 000104 00400104 258C000C */  addiu $t4, $t4, 0xc
/* 000108 00400108 25AD000C */  addiu $t5, $t5, 0xc
/* 00010C 0040010C A9A1FFF4 */  swl   $at, -0xc($t5)
/* 000110 00400110 B9A1FFF7 */  swr   $at, -9($t5)
/* 000114 00400114 8981FFF8 */  lwl   $at, -8($t4)
/* 000118 00400118 9981FFFB */  lwr   $at, -5($t4)
/* 00011C 0040011C A9A1FFF8 */  swl   $at, -8($t5)
/* 000120 00400120 B9A1FFFB */  swr   $at, -5($t5)
/* 000124 00400124 8981FFFC */  lwl   $at, -4($t4)
/* 000128 00400128 9981FFFF */  lwr   $at, -1($t4)
/* 00012C 0040012C A9A1FFFC */  swl   $at, -4($t5)
/* 000130 00400130 158BFFF2 */  bne   $t4, $t3, .L004000FC
/* 000134 00400134 B9A1FFFF */   swr   $at, -1($t5)
/* 000138 00400138 89810000 */  lwl   $at, ($t4)
/* 00013C 0040013C 99810003 */  lwr   $at, 3($t4)
/* 000140 00400140 A9A10000 */  swl   $at, ($t5)
/* 000144 00400144 03E00008 */  jr    $ra
/* 000148 00400148 B9A10003 */   swr   $at, 3($t5)

/* 00014C 0040014C 00000000 */  nop
