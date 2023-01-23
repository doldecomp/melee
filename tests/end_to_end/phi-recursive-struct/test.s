glabel test
addiu $sp, $sp, -0x78
sw    $ra, 0x24($sp)
sw    $s6, 0x20($sp)
sw    $s1, 0x1c($sp)
sw    $s0, 0x18($sp)
move  $s1, $zero
lui   $s0, %hi(glob)
addiu $s0, %lo(glob)
.loop:
lh    $t6, ($zero)
bnez  $t6, .skip
 nop
lh    $a0, 0x2004($s0)
jal   foo
 nop
.skip:
addiu $s1, $s1, 1
slti   $at, $s1, 5
addiu $s0, $s0, 0xc
bnez  $at, .loop
 nop
lw    $ra, 0x24($sp)
lw    $s0, 0x18($sp)
lw    $s1, 0x1c($sp)
lw    $s6, 0x20($sp)
jr    $ra
 addiu $sp, $sp, 0x78
