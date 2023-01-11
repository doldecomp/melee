#ifndef DOLPHIN_BASE_PPCARCH_H
#define DOLPHIN_BASE_PPCARCH_H

#include <Runtime/platform.h>

// GEKKO registers
#define GQR0 0x390
#define GQR1 0x391
#define GQR2 0x392
#define GQR3 0x393
#define GQR4 0x394
#define GQR5 0x395
#define GQR6 0x396
#define GQR7 0x397

u32 PPCMfmsr(void);
void PPCMtmsr(u32);
u32 PPCMfhid0(void);
void PPCMthid0(u32);
u32 PPCMfl2cr(void);
void PPCMtl2cr(u32);
void PPCMtdec(u32);
void PPCSync(void);
void PPCHalt(void);
u32 PPCMfhid2(void);
void PPCMthid2(u32);
void PPCMtwpar(u32);
void PPCDisableSpeculation(void);
void PPCSetFpNonIEEEMode(void);

#endif
