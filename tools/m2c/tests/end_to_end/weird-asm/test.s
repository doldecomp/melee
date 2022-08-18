.set noat # allow use of $at
.set noreorder # don't insert nops after branches
.set gp=64 # allow use of 64bit registers
.macro glabel label
    .global \label
    \label:
.endm

glabel
loc_whatever:
nop

test:
addiu $sp, $sp, -0x34
sw $s0, 0X20+16($sp)
beq $zero, $zero, .label
loc_whatever:
lui $v0, (0x12345678 >> (8 + 0x4 * 2))
.label: addiu $v0, 0xFFFF # subtract 1
addiu $sp, $sp, 0x34

func_other:
jr $ra
sw $zero, ($zero)

yet_another_func:
jr $ra
sw $zero, ($zero)
