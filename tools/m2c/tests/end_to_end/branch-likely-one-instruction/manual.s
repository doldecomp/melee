glabel test
lui   $v0, 0x800a
lw    $v0, -0x5a00($v0)
lui   $v1, 0x800b
lb    $v1, 0xf15($v1)
xori  $v0, $v0, 3
sltiu $a0, $v0, 1
addiu $v0, $zero, 5
beql  $v1, $v0, .L8004416C
 addiu $a0, $zero, 1
.L8004416C:
jr    $ra
 daddu $v0, $a0, $zero

