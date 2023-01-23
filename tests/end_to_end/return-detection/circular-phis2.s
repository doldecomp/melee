# same thing as circular-phis.s but with function returns instead of manual sets
glabel test
addiu	$sp, $sp, -0x30
sw	$ra, 0x2C($sp)
sw	$s0, 0x28($sp)
jal	bar
 nop
li	$s0, 1
.again:
beqz	$s0, .skip
 nop
jal	bar
 nop
.skip:
slt	$at, $s0, $s0
bltz	$at, .again
 nop
lw	$ra, 0x2C($sp)
lw	$s0, 0x28($sp)
jr	$ra
addiu	$sp, $sp, 0x30
