#ifndef _DOLPHIN_PPCARCH_H_
#define _DOLPHIN_PPCARCH_H_

// GEKKO registers
#define GQR0 0x390
#define GQR1 0x391
#define GQR2 0x392
#define GQR3 0x393
#define GQR4 0x394
#define GQR5 0x395
#define GQR6 0x396
#define GQR7 0x397

void PPCHalt(void);
s32 PPCMfhid2();
void PPCMthid2(s32);

#endif