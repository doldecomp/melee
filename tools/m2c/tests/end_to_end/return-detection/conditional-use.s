# a conditional use should still count as a use
glabel test
addiu	$sp, $sp, -0x30
sw	$ra, 0x2C($sp)
li	$v0, 4
li	$v1, 1
beqz $v1, .skip
 nop
beqz $v1, .skip
 nop
move $a0, $v0
jal foo
 nop
.skip:
lw	$ra, 0x2C($sp)
jr	$ra
addiu	$sp, $sp, 0x30
