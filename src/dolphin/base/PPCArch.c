#include <placeholder.h>

#ifdef MWERKS_GEKKO

asm void PPCMfmsr(void)
{ // clang-format off
    nofralloc
    mfmsr r3
    blr
} // clang-format on

#else

void PPCMfmsr(void)
{
    NOT_IMPLEMENTED;
}

#endif

#ifdef MWERKS_GEKKO

asm void PPCMtmsr(void)
{ // clang-format off
    nofralloc
    mtmsr r3
    blr
} // clang-format on

#else

void PPCMtmsr(void)
{
    NOT_IMPLEMENTED;
}

#endif

#ifdef MWERKS_GEKKO

asm void PPCMfhid0(void)
{ // clang-format off
    nofralloc
    mfspr r3, 0x3f0
    blr
} // clang-format on

#else

void PPCMfhid0(void)
{
    NOT_IMPLEMENTED;
}

#endif

#ifdef MWERKS_GEKKO

asm void PPCMfl2cr(void)
{ // clang-format off
    nofralloc
    mfspr r3, 0x3f9
    blr
} // clang-format on

#else

void PPCMfl2cr(void)
{
    NOT_IMPLEMENTED;
}

#endif

#ifdef MWERKS_GEKKO

asm void PPCMtl2cr(void)
{ // clang-format off
    nofralloc
    mtspr 0x3f9, r3
    blr
} // clang-format on

#else

void PPCMtl2cr(void)
{
    NOT_IMPLEMENTED;
}

#endif

#ifdef MWERKS_GEKKO

asm void PPCMtdec(void)
{ // clang-format off
    nofralloc
    mtspr 0x16, r3
    blr
} // clang-format on

#else

void PPCMtdec(void)
{
    NOT_IMPLEMENTED;
}

#endif

#ifdef MWERKS_GEKKO

asm void PPCSync(void)
{ // clang-format off
    nofralloc
    sc
    blr
} // clang-format on

#else

void PPCSync(void)
{
    NOT_IMPLEMENTED;
}

#endif

#ifdef MWERKS_GEKKO

asm void PPCHalt(void)
{ // clang-format off
    nofralloc
    sync
halt_loop:
    nop
    li r3, 0
    nop
    b halt_loop
} // clang-format on

#else

void PPCHalt(void)
{
    NOT_IMPLEMENTED;
}

#endif

#ifdef MWERKS_GEKKO

asm void PPCMfhid2(void)
{ // clang-format off
    nofralloc
    mfspr r3, 0x398
    blr
} // clang-format on

#else

void PPCMfhid2(void)
{
    NOT_IMPLEMENTED;
}

#endif

#ifdef MWERKS_GEKKO

asm void PPCMthid2(void)
{ // clang-format off
    nofralloc
    mtspr 0x398, r3
    blr
} // clang-format on

#else

void PPCMthid2(void)
{
    NOT_IMPLEMENTED;
}

#endif

#ifdef MWERKS_GEKKO

asm void PPCMtwpar(void)
{ // clang-format off
    nofralloc
    mtspr 0x399, r3
    blr
} // clang-format on

#else

void PPCMtwpar(void)
{
    NOT_IMPLEMENTED;
}

#endif
