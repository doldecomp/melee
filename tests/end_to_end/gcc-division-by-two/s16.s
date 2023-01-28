glabel test
move      $v0, $a0
sll       $v0, $v0, 0x10
sra       $v1, $v0, 0x10
srl       $v0, $v0, 0x1f
addu      $v1, $v1, $v0
sra       $v1, $v1, 1
jr        $ra
move      $v0, $v1
