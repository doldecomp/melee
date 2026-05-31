.include "macros.inc"

.section .init, "ax"

.macro trk_redirect vector
    mtspr   SPRG1, r2
    mtspr   SPRG2, r3
    mtspr   SPRG3, r4
    mfspr   r2, SRR0
    mfspr   r4, SRR1
    mfmsr   r3
    ori     r3, r3, 0x30
    mtspr   SRR1, r3
    lis     r3, TRKInterruptHandler@h
    ori     r3, r3, TRKInterruptHandler@l
    mtspr   SRR0, r3
    li      r3, \vector
    rfi
.endm

.macro trk_tlb_redirect vector
    mtspr   SPRG1, r2
    mfcr    r2
    mtspr   SPRG2, r2
    mfmsr   r2
    andis.  r2, r2, 2
    beq     .L_restore_cr_\@
    mfmsr   r2
    xoris   r2, r2, 2
    sync    0
    mtmsr   r2
    sync    0
    mtspr   SPRG1, r2
.L_restore_cr_\@:
    mfspr   r2, SPRG2
    mtcrf   0xFF, r2
    mfspr   r2, SPRG1
    trk_redirect \vector
.endm

.balign 4

.global gTRKInterruptVectorTable
gTRKInterruptVectorTable:
    .asciz "Metrowerks Target Resident Kernel for PowerPC"
    .balign 4
    .skip 208

# 0x0100: System Reset Exception
    b       __TRK_reset
    .skip 252

# 0x0200: Machine Check Exception
    mtspr   SPRG1, r2
    mfspr   r2, SRR0
    icbi    0, r2
    mfdar   r2
    dcbi    0, r2
    mfspr   r2, SPRG1
    trk_redirect 0x200
    .skip 180

# 0x0300: DSI Exception
    trk_redirect 0x300
    .skip 204

# 0x0400: ISI Exception
    trk_redirect 0x400
    .skip 204

# 0x0500: External Interrupt Exception
    trk_redirect 0x500
    .skip 204

# 0x0600: Alignment Exception
    trk_redirect 0x600
    .skip 204

# 0x0700: Program Exception
    trk_redirect 0x700
    .skip 204

# 0x0800: FPU Unavailable Exception
    trk_redirect 0x800
    .skip 204

# 0x0900: Decrementer Interrupt Exception
    trk_redirect 0x900
    .skip 716

# 0x0C00: System Call Exception
    trk_redirect 0xC00
    .skip 204

# 0x0D00: Trace Exception
    trk_redirect 0xD00
    .skip 204

# 0x0E00: FP Assist Exception
    trk_redirect 0xE00
    .skip 204

# 0x0F00: Performance Monitor / 0x0F20: AltiVec Unavailable
    b       .L_perf_monitor
    .skip 28
# 0x0F20: AltiVec Unavailable
    trk_redirect 0xF20
.L_perf_monitor:
    trk_redirect 0xF00
    .skip 120

# 0x1000: PPC603E Instruction TLB Miss
    trk_tlb_redirect 0x1000
    .skip 144

# 0x1100: PPC603E Data Load TLB Miss
    trk_tlb_redirect 0x1100
    .skip 144

# 0x1200: PPC603E Data Store TLB Miss
    trk_tlb_redirect 0x1200
    .skip 144

# 0x1300: Instruction Address Breakpoint Exception
    trk_redirect 0x1300
    .skip 204

# 0x1400: System Management Interrupt
    trk_redirect 0x1400
    .skip 460

# 0x1600: Denorm Detect / Java Mode Exception
    trk_redirect 0x1600
    .skip 204

# 0x1700: Thermal Management Interrupt
    trk_redirect 0x1700
    .skip 1228

# 0x1C00: Data Breakpoint Exception
    trk_redirect 0x1C00
    .skip 204

# 0x1D00: Instruction Breakpoint Exception
    trk_redirect 0x1D00
    .skip 204

# 0x1E00: Peripheral Breakpoint Exception
    trk_redirect 0x1E00
    .skip 204

# 0x1F00: Non-Maskable Development Port Exception
    trk_redirect 0x1F00

.global gTRKInterruptVectorTableEnd
gTRKInterruptVectorTableEnd:
