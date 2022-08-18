.set noat      # allow manual use of $at
.set noreorder # don't insert nops after branches


glabel static_fn
/* 0000B8 004000B8 03E00008 */  jr    $ra
/* 0000BC 004000BC AFA40000 */   sw    $a0, ($sp)

glabel test
/* 0000C0 004000C0 3C030041 */  lui   $v1, %hi(extern_float)
/* 0000C4 004000C4 24630190 */  addiu $v1, $v1, %lo(extern_float)
/* 0000C8 004000C8 3C020041 */  lui   $v0, %hi(static_int)
/* 0000CC 004000CC 3C0143E4 */  lui   $at, 0x43e4
/* 0000D0 004000D0 44813000 */  mtc1  $at, $f6
/* 0000D4 004000D4 C4640000 */  lwc1  $f4, ($v1)
/* 0000D8 004000D8 24420194 */  addiu $v0, $v0, %lo(static_int)
/* 0000DC 004000DC 8C4E0000 */  lw    $t6, ($v0)
/* 0000E0 004000E0 46062202 */  mul.s $f8, $f4, $f6
/* 0000E4 004000E4 27BDFFE8 */  addiu $sp, $sp, -0x18
/* 0000E8 004000E8 000E78C0 */  sll   $t7, $t6, 3
/* 0000EC 004000EC 01EE7823 */  subu  $t7, $t7, $t6
/* 0000F0 004000F0 000F78C0 */  sll   $t7, $t7, 3
/* 0000F4 004000F4 01EE7821 */  addu  $t7, $t7, $t6
/* 0000F8 004000F8 AFBF0014 */  sw    $ra, 0x14($sp)
/* 0000FC 004000FC 000F78C0 */  sll   $t7, $t7, 3
/* 000100 00400100 3C040041 */  lui   $a0, %hi(static_A)
/* 000104 00400104 AC4F0000 */  sw    $t7, ($v0)
/* 000108 00400108 E4680000 */  swc1  $f8, ($v1)
/* 00010C 0040010C 0C10002E */  jal   static_fn
/* 000110 00400110 24840160 */   addiu $a0, $a0, %lo(static_A)
/* 000114 00400114 3C040041 */  lui   $a0, %hi(static_A_ptr)
/* 000118 00400118 0C10002C */  jal   extern_fn
/* 00011C 0040011C 8C840174 */   lw    $a0, %lo(static_A_ptr)($a0)
/* 000120 00400120 3C180040 */  lui   $t8, %hi(static_array)
/* 000124 00400124 3C190041 */  lui   $t9, %hi(static_ro_array)
/* 000128 00400128 8F390178 */  lw    $t9, %lo(static_ro_array)($t9)
/* 00012C 0040012C 8F180150 */  lw    $t8, %lo(static_array)($t8)
/* 000130 00400130 8FBF0014 */  lw    $ra, 0x14($sp)
/* 000134 00400134 3C020041 */  lui   $v0, %hi(static_int)
/* 000138 00400138 3C010041 */  lui   $at, %hi(static_bss_array)
/* 00013C 0040013C 8C420194 */  lw    $v0, %lo(static_int)($v0)
/* 000140 00400140 03194021 */  addu  $t0, $t8, $t9
/* 000144 00400144 AC280198 */  sw    $t0, %lo(static_bss_array)($at)
/* 000148 00400148 03E00008 */  jr    $ra
/* 00014C 0040014C 27BD0018 */   addiu $sp, $sp, 0x18

.rodata
glabel static_ro_array
.word 0x07, 0x08, -0x9

glabel unused_static_ro_array
.word 10, -11, 12

.data
glabel static_A
.byte 1
.space 3
.word 0x01, 0x02, 0x03, 0x04, 0x05
.float 1.0, 2.0, 3.0, 4.0
.float 5.0, 6.0, 7.0, 8.0
.float 9.0, 0.0, 1.0, 2.0
.float 1.5, 2.5, 3.5, 4.5
.float 5.5, 6.5, 7.5, 8.5
.float 9.5, 0.5, 1.5, 2.5
.word 0, static_int
.word static_bss_A

glabel static_A_ptr
.word static_A

glabel static_array
.word 2, 4, 6

glabel unused_static_array
.half -8, 10, 12

.bss
glabel static_int
.space 4

glabel static_bss_array
.space 12

glabel static_bss_A
.space 42
