.include "macros.inc"

.section .text  # 0x80005940 - 0x803B7240



.section .sbss
    .balign 8

.global __piReg
__piReg:
	.skip 0x4

.global __cpReg
__cpReg:
	.skip 0x4

.global __peReg
__peReg:
	.skip 0x4

.global lbl_804D72FC
lbl_804D72FC:
	.skip 0x4

.global CPUFifo
CPUFifo:
	.skip 0x4

.global GPFifo
GPFifo:
	.skip 0x4

.global __GXCurrentThread
__GXCurrentThread:
	.skip 0x4

.global CPGPLinked
CPGPLinked:
	.skip 0x4

.global GXOverflowSuspendInProgress
GXOverflowSuspendInProgress:
	.skip 0x4

.global BreakPointCB
BreakPointCB:
	.skip 0x4

.global __GXOverflowCount
__GXOverflowCount:
	.skip 0x4
