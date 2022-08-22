glabel test

li $t1, 1

b .label
sw $zero, ($zero)

b .label
sw $zero, ($zero)

sw $zero, ($zero)
.label:

b .label2
nop
.label2:

b .label3
sw $zero, ($t1)

b .label4
sw $zero, ($t1)
.label3:

nop
.label4:
jr $ra
nop
