.include "macros.inc"

.section .sbss

.global ResetCallback
ResetCallback:
	.skip 0x4
.global Down
Down:
	.skip 0x4
.global OSResetSW_LastState
OSResetSW_LastState:
	.skip 0x8
.global HoldUp
HoldUp:
	.skip 0x8
.global HoldDown
HoldDown:
	.skip 0x8
