.set noat      # allow manual use of $at
.set noreorder # don't insert nops after branches

glabel test
li $t0, 1
li $t1, 2
beq $a0, $t0, .skip
nop
beq $a1, $t1, .skip
nop
.skip:
beq $a0, $t0, .skip2
nop
.skip2:
jr $ra
nop
