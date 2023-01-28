glabel test
lui   $s1, %hi(glob2)
addiu $s1, %lo(glob2)
lui   $s0, %hi(glob)
addiu $s0, %lo(glob)
sw    $s0, ($s1)
addiu $s2, $s0, 0xC
sw    $s2, ($s1)
lh    $v0, 0x100($s0)
jr $ra
 nop
