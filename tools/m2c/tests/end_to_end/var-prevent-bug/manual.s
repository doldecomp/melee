glabel test
lui         $v0, %hi(gChar)
addiu       $v0, $v0, %lo(gChar)
sb          $zero, ($v0)
.loop:
addiu       $v0, $v0, 1
sb          $zero, -1($v0)
bnez         $zero, .loop
 nop
jr          $ra
 nop
