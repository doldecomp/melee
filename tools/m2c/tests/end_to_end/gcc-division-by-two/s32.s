glabel test
move      $t9, $a0
srl       $v0, $t9, 0x1f
addu      $v0, $t9, $v0
sra       $v0, $v0, 1
jr        $ra
nop
