# regression test: an early version of PR 131 did not handle circular phi
# dependencies correctly.
glabel test
addiu	$sp, $sp, -0x30
sw	$ra, 0x2C($sp)
sw	$s0, 0x28($sp)
jal	bar
 nop
li	$v0, 4
li	$s0, 1
.again:
beqz	$s0, .skip
 nop
jal	bar
 nop
li	$v0, 5
.skip:
slt	$at, $s0, $v0
bltz	$at, .again
 nop
lw	$ra, 0x2C($sp)
lw	$s0, 0x28($sp)
jr	$ra
addiu	$sp, $sp, 0x30
