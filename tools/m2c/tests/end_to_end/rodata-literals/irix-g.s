.set noat      # allow manual use of $at
.set noreorder # don't insert nops after branches

.rdata
glabel D_400110
.ascii "\x22hello\x22\n\1\0world  /* comment */ #\0"

.late_rodata
glabel D_40011C
.byte 0x3f, 0x99, 0x99, 0x9a

glabel D_400120
.byte 0x42, 0xa, 0x13, 0xb8, 0x60, 0x0, 0x0, 0x0

.text
glabel test
/* 0000B0 004000B0 3C010040 */  lui   $at, %hi(D_40011C)
/* 0000B4 004000B4 C424011C */  lwc1  $f4, %lo(D_40011C)($at)
/* 0000B8 004000B8 3C010041 */  lui   $at, %hi(D_410130)
/* 0000BC 004000BC E4240130 */  swc1  $f4, %lo(D_410130)($at)
/* 0000C0 004000C0 3C01402A */  lui   $at, 0x402a
/* 0000C4 004000C4 44813800 */  mtc1  $at, $f7
/* 0000C8 004000C8 44803000 */  mtc1  $zero, $f6
/* 0000CC 004000CC 3C010041 */  lui   $at, %hi(D_410138)
/* 0000D0 004000D0 F4260138 */  sdc1  $f6, %lo(D_410138)($at)
/* 0000D4 004000D4 3C010040 */  lui   $at, %hi(D_400120)
/* 0000D8 004000D8 D4280120 */  ldc1  $f8, %lo(D_400120)($at)
/* 0000DC 004000DC 3C010041 */  lui   $at, %hi(D_410140)
/* 0000E0 004000E0 F4280140 */  sdc1  $f8, %lo(D_410140)($at)
/* 0000E4 004000E4 3C0E0040 */  lui   $t6, %hi(D_400110)
/* 0000E8 004000E8 25CE0110 */  addiu $t6, $t6, %lo(D_400110)
/* 0000EC 004000EC 3C010041 */  lui   $at, %hi(D_410148)
/* 0000F0 004000F0 AC2E0148 */  sw    $t6, %lo(D_410148)($at)
/* 0000F4 004000F4 03E00008 */  jr    $ra
/* 0000F8 004000F8 00000000 */   nop

/* 0000FC 004000FC 03E00008 */  jr    $ra
/* 000100 00400100 00000000 */   nop

/* 000104 00400104 00000000 */  nop
/* 000108 00400108 00000000 */  nop
/* 00010C 0040010C 00000000 */  nop
