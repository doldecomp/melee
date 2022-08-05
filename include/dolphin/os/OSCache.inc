.section .data
    .balign 8
lbl_80401BF0:
    .asciz ">>> L2 INVALIDATE : SHOULD NEVER HAPPEN\n"
    .balign 4
    .asciz "Machine check received\n"
    .balign 4
    .asciz "HID2 = 0x%x   SRR1 = 0x%x\n"
    .balign 4
    .asciz "Machine check was not DMA/locked cache related\n"
    .balign 4
    .asciz "DMAErrorHandler(): An error occurred while processing DMA.\n"
    .balign 4
    .asciz "The following errors have been detected and cleared :\n"
    .balign 4
    .asciz "\t- Requested a locked cache tag that was already in the cache\n"
    .balign 4
    .asciz "\t- DMA attempted to access normal cache\n"
    .balign 4
    .asciz "\t- DMA missed in data cache\n"
    .balign 4
    .asciz "\t- DMA queue overflowed\n"
    .balign 4
    .asciz "L1 i-caches initialized\n"
    .balign 4
    .asciz "L1 d-caches initialized\n"
    .balign 4
    .asciz "L2 cache initialized\n"
    .balign 4
    .asciz "Locked cache machine check handler installed\n"
    .balign 4
    .4byte NULL
