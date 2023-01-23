.set noat      # allow manual use of $at
.set noreorder # don't insert nops after branches


glabel test
/* 000090 00400090 46006005 */  abs.s $f0, $f12
/* 000094 00400094 46000004 */  sqrt.s $f0, $f0
/* 000098 00400098 46000021 */  cvt.d.s $f0, $f0
/* 00009C 0040009C 46200005 */  abs.d $f0, $f0
/* 0000A0 004000A0 46200004 */  sqrt.d $f0, $f0
/* 0000A4 004000A4 03E00008 */  jr    $ra
/* 0000A8 004000A8 46200020 */   cvt.s.d $f0, $f0

/* 0000AC 004000AC 00000000 */  nop
