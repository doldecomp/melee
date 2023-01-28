.set noat      # allow manual use of $at
.set noreorder # don't insert nops after branches


glabel test
/* 000090 00400090 0085001A */  div   $zero, $a0, $a1
/* 000094 00400094 00001012 */  mflo  $v0
/* 000098 00400098 14A00002 */  bnez  $a1, .L004000A4
/* 00009C 0040009C 00000000 */   nop
/* 0000A0 004000A0 0007000D */  break 7
.L004000A4:
/* 0000A4 004000A4 2401FFFF */  addiu $at, $zero, -1
/* 0000A8 004000A8 14A10004 */  bne   $a1, $at, .L004000BC
/* 0000AC 004000AC 3C018000 */   lui   $at, 0x8000
/* 0000B0 004000B0 14810002 */  bne   $a0, $at, .L004000BC
/* 0000B4 004000B4 00000000 */   nop
/* 0000B8 004000B8 0006000D */  break 6
.L004000BC:
/* 0000BC 004000BC 03E00008 */  jr    $ra
/* 0000C0 004000C0 00000000 */   nop

/* 0000C4 004000C4 00000000 */  nop
/* 0000C8 004000C8 00000000 */  nop
/* 0000CC 004000CC 00000000 */  nop
