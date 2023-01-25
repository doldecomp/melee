.section .rodata
foo:
.incbin "test.bin"

bar:
.incbin "test.bin", 4, 4

baz:
.incbin "README.md"

.section .text
glabel test
lui $a0, %hi(foo)
lw $a0, %lo(foo)($a0)
lui $a1, %hi(bar)
lw $a1, %lo(bar)($a1)
addu $v0, $a0, $a1
jr $ra
 nop
