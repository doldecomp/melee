glabel test
li      $a1,1
slt     $a0,$zero,$a2
movz    $a2,$a1,$a0
li      $v0,5
slti    $v1,$a2,6
jr      $ra
movn    $v0,$a2,$v1
