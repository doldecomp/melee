.set noat      # allow manual use of $at
.set noreorder # don't insert nops after branches


glabel test
/* 000090 00400090 3C0EFFFA */  lui   $t6, 0xfffa
/* 000094 00400094 03A07825 */  move  $t7, $sp
/* 000098 00400098 27BDFFE8 */  addiu $sp, $sp, -0x18
/* 00009C 0040009C 35CE5A5A */  ori   $t6, $t6, 0x5a5a
.L004000A0:
/* 0000A0 004000A0 25EFFFF8 */  addiu $t7, $t7, -8
/* 0000A4 004000A4 ADEE0000 */  sw    $t6, ($t7)
/* 0000A8 004000A8 15FDFFFD */  bne   $t7, $sp, .L004000A0
/* 0000AC 004000AC ADEE0004 */   sw    $t6, 4($t7)
/* 0000B0 004000B0 AFBF0014 */  sw    $ra, 0x14($sp)
/* 0000B4 004000B4 AFA40018 */  sw    $a0, 0x18($sp)
/* 0000B8 004000B8 0C100037 */  jal   func_004000DC
/* 0000BC 004000BC 24840001 */   addiu $a0, $a0, 1
/* 0000C0 004000C0 8FA40018 */  lw    $a0, 0x18($sp)
/* 0000C4 004000C4 0C100037 */  jal   func_004000DC
/* 0000C8 004000C8 24840002 */   addiu $a0, $a0, 2
/* 0000CC 004000CC 8FBF0014 */  lw    $ra, 0x14($sp)
/* 0000D0 004000D0 27BD0018 */  addiu $sp, $sp, 0x18
/* 0000D4 004000D4 03E00008 */  jr    $ra
/* 0000D8 004000D8 00000000 */   nop

glabel func_004000DC
/* 0000DC 004000DC 03E00008 */  jr    $ra
/* 0000E0 004000E0 AFA40000 */   sw    $a0, ($sp)

/* 0000E4 004000E4 00000000 */  nop
/* 0000E8 004000E8 00000000 */  nop
/* 0000EC 004000EC 00000000 */  nop
