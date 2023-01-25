glabel test
addiu $sp, $sp, -16

# Saving a function call result across a function call
jal foo
 nop
sw $v0, ($sp)
jal bar
 nop
lw $v0, ($sp)
la $v1, global
sw $v0, ($v1)

# Saving a load across a function call
lw $v0, ($v1)
sw $v0, ($sp)
jal bar
 nop
lw $v0, ($sp)
la $v1, global
sw $v0, ($v1)

addiu $sp, $sp, 16
jr $ra
 nop
