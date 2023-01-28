.set noat      # allow manual use of $at
.set noreorder # don't insert nops after branches

.rdata
glabel jtbl_4001D0
.word .case3
.word .case102
.word .case103
.word .case103
.word .case103
.word .case103
.word .case107

glabel jtbl_4001EC
.word .case1
.word .case2
.word .case3
.word .default
.word .default
.word .case6
.word .case6

.text
glabel test
/* 0000B0 004000B0 28810033 */  slti  $at, $a0, 0x33
/* 0000B4 004000B4 14200010 */  bnez  $at, .L004000F8 # if x < 51, goto block 2
/* 0000B8 004000B8 2881006C */   slti  $at, $a0, 0x6c
/* 0000BC 004000BC 14200006 */  bnez  $at, .L004000D8 # if x < 108, goto block 1
/* 0000C0 004000C0 248EFF9B */   addiu $t6, $a0, -0x65
/* 0000C4 004000C4 240100C8 */  addiu $at, $zero, 0xc8
/* 0000C8 004000C8 50810028 */  beql  $a0, $at, .L0040016C # if x == 200, goto case
/* 0000CC 004000CC 24980001 */   addiu $t8, $a0, 1
/* 0000D0 004000D0 10000035 */  b     .default
/* 0000D4 004000D4 00000000 */   nop
.L004000D8: # block 1
/* 0000D8 004000D8 2DC10007 */  sltiu $at, $t6, 7
/* 0000DC 004000DC 10200032 */  beqz  $at, .default # if x < 101, goto default
/* 0000E0 004000E0 000E7080 */   sll   $t6, $t6, 2
/* 0000E4 004000E4 3C010040 */  lui   $at, %hi(jtbl_4001D0)
/* 0000E8 004000E8 002E0821 */  addu  $at, $at, $t6
/* 0000EC 004000EC 8C2E01D0 */  lw    $t6, %lo(jtbl_4001D0)($at)
/* 0000F0 004000F0 01C00008 */  jr    $t6
/* 0000F4 004000F4 00000000 */   nop
.L004000F8: # block 2
/* 0000F8 004000F8 28810008 */  slti  $at, $a0, 8
/* 0000FC 004000FC 14200005 */  bnez  $at, .L00400114 # if x < 8, goto block 3
/* 000100 00400100 24010032 */   addiu $at, $zero, 0x32
/* 000104 00400104 1081001F */  beq   $a0, $at, .case50 # if x == 50, goto case
/* 000108 00400108 00000000 */   nop
/* 00010C 0040010C 10000026 */  b     .default
/* 000110 00400110 00000000 */   nop
.L00400114: # block 3
/* 000114 00400114 2881FFCF */  slti  $at, $a0, -0x31
/* 000118 00400118 14200009 */  bnez  $at, .L00400140 # if x < -49, goto block 4
/* 00011C 0040011C 248FFFFF */   addiu $t7, $a0, -1
/* 000120 00400120 2DE10007 */  sltiu $at, $t7, 7
/* 000124 00400124 10200020 */  beqz  $at, .default # if x < 1, goto default
/* 000128 00400128 000F7880 */   sll   $t7, $t7, 2
/* 00012C 0040012C 3C010040 */  lui   $at, %hi(jtbl_4001EC)
/* 000130 00400130 002F0821 */  addu  $at, $at, $t7
/* 000134 00400134 8C2F01EC */  lw    $t7, %lo(jtbl_4001EC)($at)
/* 000138 00400138 01E00008 */  jr    $t7
/* 00013C 0040013C 00000000 */   nop
.L00400140: # block 4
/* 000140 00400140 2401FFCE */  addiu $at, $zero, -0x32
/* 000144 00400144 1081000D */  beq   $a0, $at, .casem50 # if x == -50, goto case
/* 000148 00400148 00000000 */   nop
/* 00014C 0040014C 10000016 */  b     .default
/* 000150 00400150 00000000 */   nop
.case1:
/* 000154 00400154 00840019 */  multu $a0, $a0
/* 000158 00400158 00001012 */  mflo  $v0
/* 00015C 0040015C 03E00008 */  jr    $ra
/* 000160 00400160 00000000 */   nop

.case2:
/* 000164 00400164 2484FFFF */  addiu $a0, $a0, -1
.case3:
/* 000168 00400168 24980001 */  addiu $t8, $a0, 1
.L0040016C:
/* 00016C 0040016C 03E00008 */  jr    $ra
/* 000170 00400170 03041026 */   xor   $v0, $t8, $a0
.case107:
/* 000174 00400174 10000011 */  b     .L004001BC
/* 000178 00400178 24840001 */   addiu $a0, $a0, 1
.casem50:
/* 00017C 0040017C 1000000F */  b     .L004001BC
/* 000180 00400180 2484FFFF */   addiu $a0, $a0, -1
.case50:
/* 000184 00400184 1000000D */  b     .L004001BC
/* 000188 00400188 24840001 */   addiu $a0, $a0, 1
.case6:
/* 00018C 0040018C 0004C840 */  sll   $t9, $a0, 1
/* 000190 00400190 03202025 */  move  $a0, $t9
.case102:
/* 000194 00400194 3C080041 */  lui   $t0, %hi(D_410210)
/* 000198 00400198 8D080210 */  lw    $t0, %lo(D_410210)($t0)
/* 00019C 0040019C 15000007 */  bnez  $t0, .L004001BC
/* 0001A0 004001A0 00000000 */   nop
.case103:
/* 0001A4 004001A4 2484FFFF */  addiu $a0, $a0, -1
.default:
/* 0001A8 004001A8 04810003 */  bgez  $a0, .L004001B8
/* 0001AC 004001AC 00044843 */   sra   $t1, $a0, 1
/* 0001B0 004001B0 24810001 */  addiu $at, $a0, 1
/* 0001B4 004001B4 00014843 */  sra   $t1, $at, 1
.L004001B8:
/* 0001B8 004001B8 01202025 */  move  $a0, $t1
.L004001BC:
/* 0001BC 004001BC 3C010041 */  lui   $at, %hi(D_410210)
/* 0001C0 004001C0 AC240210 */  sw    $a0, %lo(D_410210)($at)
/* 0001C4 004001C4 24020002 */  addiu $v0, $zero, 2
/* 0001C8 004001C8 03E00008 */  jr    $ra
/* 0001CC 004001CC 00000000 */   nop
