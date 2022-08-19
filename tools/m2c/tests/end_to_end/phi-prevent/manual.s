glabel test
addiu $t0, $a0, 1
beqz $a2, .skip
 move $v0, $t0
addiu $t0, $a0, 2
.skip:
jr $ra
 sw $t0, ($zero)
