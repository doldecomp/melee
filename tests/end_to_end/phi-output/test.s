glabel  test
  li       $t1, 0
  .loop:
  beq      $a0, $zero, .alt2
   nop
  move     $at, $a1
  lw       $t2, 1($at)
  b        .done
   nop
  .alt2:
  lw       $t2, 1($a1)
  .done:
  addu     $t1, $t1, $t2
  li       $a1, 0
  bnez     $t1, .loop
   nop
  jr       $ra
   nop
