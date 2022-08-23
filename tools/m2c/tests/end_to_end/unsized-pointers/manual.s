glabel test
    lw      $v1, 4($a0)
    addiu    $v0, $v1, 1
    lw      $v1, 4($a1)
    addu    $v0, $v0, $v1
    addiu    $v1, $a1, 1
    addu    $v0, $v0, $v1
    jr      $ra
     nop
