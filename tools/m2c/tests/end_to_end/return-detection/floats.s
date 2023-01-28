# prioritize f0 over v0 when v0 isn't read/is from function call
# modified from read-fncall.s
glabel test
addiu	$sp, $sp, -0x30
sw	$ra, 0x2C($sp)
sw	$s0, 0x28($sp)
# set f0 from function call
jal	bar
 nop
li	$v0, 4
li	$s0, 1
beqz $v0, .skip
nop
.again:
beqz	$s0, .skip
 nop
jal	bar
 nop
# set f0 manually without reading it
lui $at, 0x4000
mtc1 $at, $f0
nop
.skip:
slt	$at, $s0, $s0
bltz	$at, .again
 nop
lw	$ra, 0x2C($sp)
lw	$s0, 0x28($sp)
jr	$ra
addiu	$sp, $sp, 0x30
