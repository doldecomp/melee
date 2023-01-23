glabel test
beqz $a0, .yes
 nop
b .no
 li	$v0, 0
.yes:
li $v0, 1
.no:
jr $ra
 nop
