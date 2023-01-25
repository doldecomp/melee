glabel test

li $t2, 0
sltiu       $at, $a0, 2
beqz        $at, .skip
 lw         $at, %got(jtbl_1)($gp)
sll         $a0, $a0, 2
addu        $at, $at, $a0
lw          $a0, %lo(jtbl_1)($at)
addu        $a0, $a0, $gp
jr          $a0
 nop

.case0:
b .skip
 li $t2, 1

.case1:
b .skip
 li $t2, 2

.skip:

lw    $t1, %got(local_sym)($gp)
addiu $t1, $t1, %lo(local_sym)
sw    $t2, 8($t1)

lw    $t1, %got(global_sym)($gp)
sw    $zero, 8($t1)

lw    $t9, %got(func)($gp)
jalr  $t9
 nop

jr $ra
 nop

.section .rodata
jtbl_1:
.word .case0
.word .case1
