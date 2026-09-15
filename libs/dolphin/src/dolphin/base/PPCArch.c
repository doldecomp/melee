#include <dolphin.h>

#include <dolphin/base/PPCArch.h>

asm u32 PPCMfmsr()
{
    // clang-format off
    nofralloc
    mfmsr r3
    blr
    // clang-format on
}

asm void PPCMtmsr(register u32 newMSR)
{
    // clang-format off
    nofralloc
    mtmsr newMSR
    blr
    // clang-format on
}

asm u32 PPCOrMsr(register u32 value)
{
    // clang-format off
    nofralloc
    mfmsr r4
    or value, r4, value
    blr
    // clang-format on
}

asm u32 PPCAndMsr(register u32 value)
{
    // clang-format off
    nofralloc
    mfmsr r4
    and value, r4, value
    blr
    // clang-format on
}

asm u32 PPCAndCMsr(register u32 value)
{
    // clang-format off
    nofralloc
    mfmsr r4
    andc value, r4, value
    blr
    // clang-format on
}

asm u32 PPCMfhid0()
{
    // clang-format off
    nofralloc
    mfspr r3, HID0
    blr
    // clang-format on
}

asm void PPCMthid0(register u32 newHID0)
{
    // clang-format off
    nofralloc
    mtspr HID0, newHID0
    blr
    // clang-format on
}

asm u32 PPCMfhid1()
{
    // clang-format off
    nofralloc
    mfspr r3, HID1
    blr
    // clang-format on
}

asm u32 PPCMfl2cr()
{
    // clang-format off
    nofralloc
    mfspr r3, L2CR
    blr
    // clang-format on
}

asm void PPCMtl2cr(register u32 newL2cr)
{
    // clang-format off
    nofralloc
    mtspr L2CR, newL2cr
    blr
    // clang-format on
}

asm void PPCMtdec(register u32 newDec)
{
    // clang-format off
    nofralloc
    mtdec newDec
    blr
    // clang-format on
}

asm u32 PPCMfdec()
{
    // clang-format off
    nofralloc
    mfdec r3
    blr
    // clang-format on
}

asm void PPCSync()
{
    // clang-format off
    nofralloc
    sc
    blr
    // clang-format on
}

asm void PPCEieio()
{
    // clang-format off
    nofralloc
    mfmsr r5
    rlwinm r6, r5, 0, 17, 15
    mtmsr r6
    mfspr r3, HID0
    ori r4, r3, 0x8
    mtspr HID0, r4
    isync
    eieio
    isync
    mtspr HID0, r3
    mtmsr r5
    isync
    blr
    // clang-format on
}

asm void PPCHalt()
{
    // clang-format off
    nofralloc
    sync
loop:
    nop
    li r3, 0
    nop
    b loop
    // clang-format on
}

asm u32 PPCMfmmcr0()
{
    // clang-format off
    nofralloc
    mfspr r3, MMCR0
    blr
    // clang-format on
}

asm void PPCMtmmcr0(register u32 newMmcr0)
{
    // clang-format off
    nofralloc
    mtspr MMCR0, newMmcr0
    blr
    // clang-format on
}

asm u32 PPCMfmmcr1()
{
    // clang-format off
    nofralloc
    mfspr r3, MMCR1
    blr
    // clang-format on
}

asm void PPCMtmmcr1(register u32 newMmcr1)
{
    // clang-format off
    nofralloc
    mtspr MMCR1, newMmcr1
    blr
    // clang-format on
}

asm u32 PPCMfpmc1()
{
    // clang-format off
    nofralloc
    mfspr r3, PMC1
    blr
    // clang-format on
}

asm void PPCMtpmc1(register u32 newPmc1)
{
    // clang-format off
    nofralloc
    mtspr PMC1, newPmc1
    blr
    // clang-format on
}

asm u32 PPCMfpmc2()
{
    // clang-format off
    nofralloc
    mfspr r3, PMC2
    blr
    // clang-format on
}

asm void PPCMtpmc2(register u32 newPmc2)
{
    // clang-format off
    nofralloc
    mtspr PMC2, newPmc2
    blr
    // clang-format on
}

asm u32 PPCMfpmc3()
{
    // clang-format off
    nofralloc
    mfspr r3, PMC3
    blr
    // clang-format on
}

asm void PPCMtpmc3(register u32 newPmc3)
{
    // clang-format off
    nofralloc
    mtspr PMC3, newPmc3
    blr
    // clang-format on
}

asm u32 PPCMfpmc4()
{
    // clang-format off
    nofralloc
    mfspr r3, PMC4
    blr
    // clang-format on
}

asm void PPCMtpmc4(register u32 newPmc4)
{
    // clang-format off
    nofralloc
    mtspr PMC4, newPmc4
    blr
    // clang-format on
}

asm u32 PPCMfsia()
{
    // clang-format off
    nofralloc
    mfspr r3, SIA
    blr
    // clang-format on
}

asm void PPCMtsia(register u32 newSia)
{
    // clang-format off
    nofralloc
    mtspr SIA, newSia
    blr
    // clang-format on
}

asm u32 PPCMfhid2()
{
    // clang-format off
    nofralloc
    mfspr r3, HID2
    blr
    // clang-format on
}

asm void PPCMthid2(register u32 newhid2)
{
    // clang-format off
    nofralloc
    mtspr HID2, newhid2
    blr
    // clang-format on
}

asm u32 PPCMfwpar()
{
    // clang-format off
    nofralloc
    sync
    mfspr r3, WPAR
    blr
    // clang-format on
}

asm void PPCMtwpar(register u32 newwpar)
{
    // clang-format off
    nofralloc
    mtspr WPAR, newwpar
    blr
    // clang-format on
}

asm u32 PPCMfdmaU()
{
    // clang-format off
    nofralloc
    mfspr r3, DMA_U
    blr
    // clang-format on
}

asm u32 PPCMfdmaL()
{
    // clang-format off
    nofralloc
    mfspr r3, DMA_L
    blr
    // clang-format on
}

asm void PPCMtdmaU(register u32 newdmau)
{
    // clang-format off
    nofralloc
    mtspr DMA_U, newdmau
    blr
    // clang-format on
}

asm void PPCMtdmaL(register u32 newdmal)
{
    // clang-format off
    nofralloc
    mtspr DMA_L, newdmal
    blr
    // clang-format on
}

asm u32 PPCMfpvr()
{
    // clang-format off
    nofralloc
    mfspr r3, PVR
    blr
    // clang-format on
}
