.set noat      # allow manual use of $at
.set noreorder # don't insert nops after branches

glabel test
    break
    break 2

    sync

    teq $zero, $a0
    tne $zero, $a0
    tlt $zero, $a0
    tltu $zero, $a0
    tge $zero, $a0
    tgeu $zero, $a0

    teqi $a0, 1
    tnei $a0, 2
    tlti $a0, 3
    tltiu $a0, 4
    tgei $a0, 5
    tgeiu $a0, 6

    badinstr $t0, $t0
    badinstr2 $t1, $t1
    badinstr3 $v0, $t2
    sllv $t1, $t1, $t1
    sw $t1, ($zero)
    addiu $v1, $v1, 2
    sw $v1, ($zero)
    jr $ra
     nop
