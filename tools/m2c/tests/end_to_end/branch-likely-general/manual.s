glabel test
beqzl $a0, .label
sw $zero, ($zero)
li $t1, 1
sw $t1, ($zero)
.label:
li $t2, 2
sw $t2, ($zero)
jr $ra
nop
