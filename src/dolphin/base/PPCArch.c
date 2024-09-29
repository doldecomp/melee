#include <placeholder.h>

#include <dolphin/base/PPCArch.h>

#ifdef MWERKS_GEKKO
asm u32 PPCMfmsr(void){ // clang-format off
    nofralloc
    mfmsr r3
    blr
} // clang-format on

#else
u32 PPCMfmsr(void)
{
    NOT_IMPLEMENTED;
}
#endif

#ifdef MWERKS_GEKKO
asm void PPCMtmsr(u32)
{ // clang-format off
    nofralloc
    mtmsr r3
    blr
} // clang-format on

#else
void PPCMtmsr(u32 arg0)
{
    NOT_IMPLEMENTED;
}
#endif

#ifdef MWERKS_GEKKO
asm u32 PPCMfhid0(void){ // clang-format off
    nofralloc
    mfspr r3, 0x3f0
    blr
} // clang-format on

#else
u32 PPCMfhid0(void)
{
    NOT_IMPLEMENTED;
}
#endif

#ifdef MWERKS_GEKKO
asm u32 PPCMfl2cr(void){ // clang-format off
    nofralloc
    mfspr r3, 0x3f9
    blr
} // clang-format on

#else
u32 PPCMfl2cr(void)
{
    NOT_IMPLEMENTED;
}
#endif

#ifdef MWERKS_GEKKO
asm void PPCMtl2cr(u32)
{ // clang-format off
    nofralloc
    mtspr 0x3f9, r3
    blr
} // clang-format on

#else
void PPCMtl2cr(u32 arg0)
{
    NOT_IMPLEMENTED;
}
#endif

#ifdef MWERKS_GEKKO
asm void PPCMtdec(u32)
{ // clang-format off
    nofralloc
    mtspr 0x16, r3
    blr
} // clang-format on

#else
void PPCMtdec(u32 arg0)
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
asm u32 PPCMfhid2(void){ // clang-format off
    nofralloc
    mfspr r3, 0x398
    blr
} // clang-format on

#else
u32 PPCMfhid2(void)
{
    NOT_IMPLEMENTED;
}
#endif

#ifdef MWERKS_GEKKO
asm void PPCMthid2(u32)
{ // clang-format off
    nofralloc
    mtspr 0x398, r3
    blr
} // clang-format on

#else
void PPCMthid2(u32 arg0)
{
    NOT_IMPLEMENTED;
}
#endif

#ifdef MWERKS_GEKKO
asm void PPCMtwpar(u32)
{ // clang-format off
    nofralloc
    mtspr 0x399, r3
    blr
} // clang-format on
#else

void PPCMtwpar(u32 arg0)
{
    NOT_IMPLEMENTED;
}
#endif
