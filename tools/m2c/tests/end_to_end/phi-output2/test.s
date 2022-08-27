glabel test
  li          $a3, 0
.loop:
  addiu       $a2, $a3, 1
  lw          $v0, 4($a2)
  lw          $a3, ($zero)
  beqz        $a0, .skip
   nop
  lw          v0, 4(a2)
.skip:
  bnez        $a0, .loop
   nop
  jr $ra
   nop
