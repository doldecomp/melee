.include "macros.inc"

.section .ctors, "wa"  # 0x803B7240 - 0x803B7260

.global lbl_803B7240
lbl_803B7240:
	.4byte __init_cpp_exceptions
    .4byte func_80326578
    .4byte NULL
