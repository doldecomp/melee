glabel test
beqz $a1, .skip
.loop:
 addiu $a0, $a0, -1
bnez $a0, .loop
 nop
.skip:
jr $ra
 move $v0, $a0
