glabel test
  addiu $sp, $sp, -0x110
  jal   foo
   nop
  move  $t1, $v0
  lbu   $t0, ($zero)
  bnez  $t0, .L0043D650
   nop
  sw    $t1, 0x10c($sp)
  lw    $t1, 0x10c($sp)
.L0043D650:
  sb    $zero, 3($t1)
  sb    $zero, 4($t1)
  jr    $ra
   addiu $sp, $sp, 0x110
