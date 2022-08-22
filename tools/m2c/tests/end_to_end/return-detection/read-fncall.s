# regression test: this function should be deduced as void, but wasn't in an
# early version of PR 131.
glabel test
addiu	$sp, $sp, -0x30
sw	$ra, 0x2C($sp)
sw	$s0, 0x28($sp)
jal	bar
 nop
# v0 is set but read here...
li	$v0, 4
li	$s0, 1
beqz $v0, .skip
nop
.again:
beqz	$s0, .skip
 nop
# ... and set by function call here
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
