glabel test
lui $v0, %hi(a + 4)
jr $ra
lw $v0, %lo(a + 4)($v0)
