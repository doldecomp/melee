.set noat      # allow manual use of $at
.set noreorder # don't insert nops after branches


glabel func_00400090
/* 000090 00400090 03E00008 */  jr    $ra
/* 000094 00400094 24820001 */   addiu $v0, $a0, 1

glabel test
/* 000098 00400098 27BDFFD0 */  addiu $sp, $sp, -0x30
/* 00009C 0040009C 00854021 */  addu  $t0, $a0, $a1
/* 0000A0 004000A0 00A67821 */  addu  $t7, $a1, $a2
/* 0000A4 004000A4 AFBF0014 */  sw    $ra, 0x14($sp)
/* 0000A8 004000A8 AFA40030 */  sw    $a0, 0x30($sp)
/* 0000AC 004000AC AFA7003C */  sw    $a3, 0x3c($sp)
/* 0000B0 004000B0 AFA8002C */  sw    $t0, 0x2c($sp)
/* 0000B4 004000B4 AFAF001C */  sw    $t7, 0x1c($sp)
/* 0000B8 004000B8 1500000E */  bnez  $t0, .L004000F4
/* 0000BC 004000BC 01E04825 */   move  $t1, $t7
/* 0000C0 004000C0 15E0000C */  bnez  $t7, .L004000F4
/* 0000C4 004000C4 01E02025 */   move  $a0, $t7
/* 0000C8 004000C8 AFA60038 */  sw    $a2, 0x38($sp)
/* 0000CC 004000CC 0C100024 */  jal   func_00400090
/* 0000D0 004000D0 AFA80020 */   sw    $t0, 0x20($sp)
/* 0000D4 004000D4 8FA60038 */  lw    $a2, 0x38($sp)
/* 0000D8 004000D8 8FA80020 */  lw    $t0, 0x20($sp)
/* 0000DC 004000DC 14400005 */  bnez  $v0, .L004000F4
/* 0000E0 004000E0 00404825 */   move  $t1, $v0
/* 0000E4 004000E4 8FB9003C */  lw    $t9, 0x3c($sp)
/* 0000E8 004000E8 8FAA0030 */  lw    $t2, 0x30($sp)
/* 0000EC 004000EC 13200003 */  beqz  $t9, .L004000FC
/* 0000F0 004000F0 00000000 */   nop
.L004000F4:
/* 0000F4 004000F4 10000005 */  b     .L0040010C
/* 0000F8 004000F8 24030001 */   addiu $v1, $zero, 1
.L004000FC:
/* 0000FC 004000FC 11400003 */  beqz  $t2, .L0040010C
/* 000100 00400100 2403FFFE */   addiu $v1, $zero, -2
/* 000104 00400104 10000001 */  b     .L0040010C
/* 000108 00400108 2403FFFF */   addiu $v1, $zero, -1
.L0040010C:
/* 00010C 0040010C 11000015 */  beqz  $t0, .L00400164
/* 000110 00400110 00661821 */   addu  $v1, $v1, $a2
/* 000114 00400114 11200013 */  beqz  $t1, .L00400164
/* 000118 00400118 01092021 */   addu  $a0, $t0, $t1
/* 00011C 0040011C AFA4002C */  sw    $a0, 0x2c($sp)
/* 000120 00400120 0C100024 */  jal   func_00400090
/* 000124 00400124 AFA30024 */   sw    $v1, 0x24($sp)
/* 000128 00400128 8FA30024 */  lw    $v1, 0x24($sp)
/* 00012C 0040012C 1040000D */  beqz  $v0, .L00400164
/* 000130 00400130 00404825 */   move  $t1, $v0
/* 000134 00400134 8FAC003C */  lw    $t4, 0x3c($sp)
/* 000138 00400138 28610005 */  slti  $at, $v1, 5
/* 00013C 0040013C 5180000A */  beql  $t4, $zero, .L00400168
/* 000140 00400140 8FAE002C */   lw    $t6, 0x2c($sp)
/* 000144 00400144 50200007 */  beql  $at, $zero, .L00400164
/* 000148 00400148 24630005 */   addiu $v1, $v1, 5
.L0040014C:
/* 00014C 0040014C 24630001 */  addiu $v1, $v1, 1
/* 000150 00400150 00036840 */  sll   $t5, $v1, 1
/* 000154 00400154 29A10005 */  slti  $at, $t5, 5
/* 000158 00400158 1420FFFC */  bnez  $at, .L0040014C
/* 00015C 0040015C 01A01825 */   move  $v1, $t5
/* 000160 00400160 24630005 */  addiu $v1, $v1, 5
.L00400164:
/* 000164 00400164 8FAE002C */  lw    $t6, 0x2c($sp)
.L00400168:
/* 000168 00400168 51C00016 */  beql  $t6, $zero, .L004001C4
/* 00016C 0040016C 24630006 */   addiu $v1, $v1, 6
/* 000170 00400170 11200013 */  beqz  $t1, .L004001C0
/* 000174 00400174 01C92021 */   addu  $a0, $t6, $t1
/* 000178 00400178 AFA4002C */  sw    $a0, 0x2c($sp)
/* 00017C 0040017C 0C100024 */  jal   func_00400090
/* 000180 00400180 AFA30024 */   sw    $v1, 0x24($sp)
/* 000184 00400184 1040000E */  beqz  $v0, .L004001C0
/* 000188 00400188 8FA30024 */   lw    $v1, 0x24($sp)
/* 00018C 0040018C 8FB8003C */  lw    $t8, 0x3c($sp)
/* 000190 00400190 28610005 */  slti  $at, $v1, 5
/* 000194 00400194 5300000B */  beql  $t8, $zero, .L004001C4
/* 000198 00400198 24630006 */   addiu $v1, $v1, 6
/* 00019C 0040019C 10200006 */  beqz  $at, .L004001B8
/* 0001A0 004001A0 00000000 */   nop
.L004001A4:
/* 0001A4 004001A4 24630001 */  addiu $v1, $v1, 1
/* 0001A8 004001A8 0003C840 */  sll   $t9, $v1, 1
/* 0001AC 004001AC 2B210005 */  slti  $at, $t9, 5
/* 0001B0 004001B0 1420FFFC */  bnez  $at, .L004001A4
/* 0001B4 004001B4 03201825 */   move  $v1, $t9
.L004001B8:
/* 0001B8 004001B8 10000002 */  b     .L004001C4
/* 0001BC 004001BC 24630005 */   addiu $v1, $v1, 5
.L004001C0:
/* 0001C0 004001C0 24630006 */  addiu $v1, $v1, 6
.L004001C4:
/* 0001C4 004001C4 8FBF0014 */  lw    $ra, 0x14($sp)
/* 0001C8 004001C8 27BD0030 */  addiu $sp, $sp, 0x30
/* 0001CC 004001CC 00601025 */  move  $v0, $v1
/* 0001D0 004001D0 03E00008 */  jr    $ra
/* 0001D4 004001D4 00000000 */   nop

/* 0001D8 004001D8 00000000 */  nop
/* 0001DC 004001DC 00000000 */  nop
