.include "macros.inc"

.section .dtors, "wa"  # 0x803B7260 - 0x803B7280
    .balign 8
.global MSL_AbortExit_803B7260
MSL_AbortExit_803B7260:
    .4byte __destroy_global_chain
    .4byte __fini_cpp_exceptions
    .4byte __destroy_global_chain
    .4byte NULL
