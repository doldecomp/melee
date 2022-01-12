.include "macros.inc"

.section .ctors, "wa"  # 0x803B7240 - 0x803B7260

.global lbl_803B7240
lbl_803B7240:
	.4byte __init_cpp_exceptions
    .4byte __sinit_trigf_c
    .4byte NULL
