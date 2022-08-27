.set noat      # allow manual use of $at
.set noreorder # don't insert nops after branches


glabel test
/* 0000B0 004000B0 3C030041 */  lui   $v1, %hi(D_4100E0)
/* 0000B4 004000B4 246300E0 */  addiu $v1, $v1, %lo(D_4100E0)
/* 0000B8 004000B8 24040001 */  addiu $a0, $zero, 1
/* 0000BC 004000BC 24020002 */  addiu $v0, $zero, 2
.L004000C0:
/* 0000C0 004000C0 8C6E0000 */  lw    $t6, ($v1)
/* 0000C4 004000C4 104E0003 */  beq   $v0, $t6, .L004000D4
/* 0000C8 004000C8 00000000 */   nop
/* 0000CC 004000CC 1000FFFC */  b     .L004000C0
/* 0000D0 004000D0 AC640000 */   sw    $a0, ($v1)
.L004000D4:
/* 0000D4 004000D4 03E00008 */  jr    $ra
/* 0000D8 004000D8 00000000 */   nop

/* 0000DC 004000DC 00000000 */  nop
