glabel test
beqz $a0, .a
 nop
jal fun
 nop
lui $v0, 1
b .b
 nop
.a:
lui $v0, 1
.b:
ori $v0, $v0, 2
jr $ra
 nop
