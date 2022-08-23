.set noat      # allow manual use of $at
.set noreorder # don't insert nops after branches

.rdata
glabel D_400100
.asciz /* "before */ "\"hello\"\n\x01" /* after" */ # more"
.asciz "world  /* comment */ #"

.late_rodata
glabel D_40010C
.float 1.2

glabel D_400110
.double 1.4e10

.text
glabel test
/* 0000B0 004000B0 3C010040 */  lui   $at, %hi(D_40010C)
/* 0000B4 004000B4 C424010C */  lwc1  $f4, %lo(D_40010C)($at)
/* 0000B8 004000B8 3C010041 */  lui   $at, %hi(D_410120)
/* 0000BC 004000BC 44803000 */  mtc1  $zero, $f6
/* 0000C0 004000C0 E4240120 */  swc1  $f4, %lo(D_410120)($at)
/* 0000C4 004000C4 3C01402A */  lui   $at, 0x402a
/* 0000C8 004000C8 44813800 */  mtc1  $at, $f7
/* 0000CC 004000CC 3C010041 */  lui   $at, %hi(D_410128)
/* 0000D0 004000D0 3C0E0040 */  lui   $t6, %hi(D_400100)
/* 0000D4 004000D4 F4260128 */  sdc1  $f6, %lo(D_410128)($at)
/* 0000D8 004000D8 3C010040 */  lui   $at, %hi(D_400110)
/* 0000DC 004000DC D4280110 */  ldc1  $f8, %lo(D_400110)($at)
/* 0000E0 004000E0 3C010041 */  lui   $at, %hi(D_410130)
/* 0000E4 004000E4 25CE0100 */  addiu $t6, $t6, %lo(D_400100)
/* 0000E8 004000E8 F4280130 */  sdc1  $f8, %lo(D_410130)($at)
/* 0000EC 004000EC 3C010041 */  lui   $at, %hi(D_410138)
/* 0000F0 004000F0 03E00008 */  jr    $ra
/* 0000F4 004000F4 AC2E0138 */   sw    $t6, %lo(D_410138)($at)

/* 0000F8 004000F8 00000000 */  nop
/* 0000FC 004000FC 00000000 */  nop
