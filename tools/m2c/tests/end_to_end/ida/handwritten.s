glabel test

la $v0, symbol
lw $v0, ($v0)

la $v1, symbol + 8
lw $v1, 4($v1)

# same as addition
la $v0, 4($v0)

lw $a0, symbol

lw $a1, symbol+4

sw $a1, symbol

addu $v0, $v1
addu $v0, $a1

jr $ra
nop
