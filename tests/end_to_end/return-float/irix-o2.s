.set noat      # allow manual use of $at
.set noreorder # don't insert nops after branches


glabel test
/* 000090 00400090 44802000 */  mtc1  $zero, $f4
/* 000094 00400094 3C014170 */  lui   $at, 0x4170
/* 000098 00400098 46046032 */  c.eq.s $f12, $f4
/* 00009C 0040009C 00000000 */  nop
/* 0000A0 004000A0 45030005 */  bc1tl .L004000B8
/* 0000A4 004000A4 46006086 */   mov.s $f2, $f12
/* 0000A8 004000A8 44811000 */  mtc1  $at, $f2
/* 0000AC 004000AC 03E00008 */  jr    $ra
/* 0000B0 004000B0 46001006 */   mov.s $f0, $f2

/* 0000B4 004000B4 46006086 */  mov.s $f2, $f12
.L004000B8:
/* 0000B8 004000B8 03E00008 */  jr    $ra
/* 0000BC 004000BC 46001006 */   mov.s $f0, $f2
