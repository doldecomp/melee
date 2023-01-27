glabel test
addiu   $sp,$sp,-0x18
sqrt.s  $f0,$f12
c.eq.s  $f0,$f0
nop
bc1t    .label_20
sw      $ra,0x10($sp)
jal     sqrtf
nop
.label_20
lw $ra, 0x10($sp)
trunc.w.s $f2, $f0
mfc1 $v0, $f2
jr      $ra
addiu   $sp,$sp,0x18
nop