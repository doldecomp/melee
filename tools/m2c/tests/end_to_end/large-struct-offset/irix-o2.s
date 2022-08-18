.set noat      # allow manual use of $at
.set noreorder # don't insert nops after branches


glabel test
/* 0000B0 004000B0 3C0E0001 */  lui   $t6, 1
/* 0000B4 004000B4 01C47021 */  addu  $t6, $t6, $a0
/* 0000B8 004000B8 8DCE2348 */  lw    $t6, 0x2348($t6)
/* 0000BC 004000BC 3C010041 */  lui   $at, %hi(D_4100E0)
/* 0000C0 004000C0 AC2E00E0 */  sw    $t6, %lo(D_4100E0)($at)
/* 0000C4 004000C4 3C010001 */  lui   $at, 1
/* 0000C8 004000C8 34212348 */  ori   $at, $at, 0x2348
/* 0000CC 004000CC 03E00008 */  jr    $ra
/* 0000D0 004000D0 00811021 */   addu  $v0, $a0, $at

/* 0000D4 004000D4 00000000 */  nop
/* 0000D8 004000D8 00000000 */  nop
/* 0000DC 004000DC 00000000 */  nop
