glabel test
addiu   $sp,$sp,-0x18
sqrt.s  $f2,$f12
c.eq.s  $f2,$f2
nop
bc1t    .label_24
sw      $ra,0x10($sp)
jal     sqrtf
nop
mov.s   $f2,$f0
.label_24
lui     $at,0x3f00
mtc1    $at,$f0
nop
mul.s   $f0,$f2,$f0
nop
lw      $ra,0x10($sp)
jr      $ra
addiu   $sp,$sp,0x18
nop