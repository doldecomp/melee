#ifndef GALE01_391580
#define GALE01_391580

#include <platform.h>

#include "baselib/forward.h"

#include "baselib/jobj.h"

#include <baselib/psstructs.h>

/* 3983A4 */ void hsd_803983A4(HSD_Generator*);
/* 3984F4 */ void psInitDataBankLoad(int bank, const int* cmdBank,
                                     const int* texBank, const u32* ref,
                                     const int* formBank);
/* 398614 */ void psInitDataBankLocate(HSD_Archive* cmdBank,
                                       HSD_Archive* texBank, int* formBank);
/* 3989A0 */ void psInitDataBankRelocate(int* cmdBank, int* texBank,
                                         int* formBank, int* newCmdBank,
                                         int* newTexBank, int* newFormBank);
/* 398A08 */ void hsd_80398A08(u32);
/* 398C04 */ HSD_Particle*
psGenerateParticle0(HSD_Particle** head, int linkNo, int bank, u32 kind,
                    u16 texGroup, u8* list, int life, int palflag, f32 x,
                    f32 y, f32 z, f32 vx, f32 vy, f32 vz, f32 size, f32 grav,
                    f32 fric, HSD_Generator* gp, int flgInterpret);
/* 398F0C */ void hsd_80398F0C(s32, s32, s32, u16, s32, s32, s32, s32, f32,
                               f32, f32, f32, f32, f32, f32, f32, f32);
/* 398F8C */ void hsd_80398F8C(HSD_Particle*, f32);
/* 3991D8 */ s32 hsd_803991D8(HSD_Generator*, HSD_JObj*, f32, f32);
/* 39930C */ void* hsd_8039930C(void*, void*);
/* 39CEAC */ void hsd_8039CEAC(u32);
/* 39CF4C */ void hsd_8039CF4C(s32, HSD_JObj*);
/* 39D048 */ void hsd_8039D048(void* particle);
/* 4D0908 */ extern HSD_Particle* hsd_804D0908[16];
/* 4D0B50 */ extern HSD_PSTexGroup** psTexGroupArray[65];
/* 4D0D58 */ extern int psNumCmdList[65];
/* 4D0E5C */ extern u32* ptclref_804D0E5C[65];
/* 4D78D8 */ extern u16 hsd_804D78D8;
/* 4D78DE */ extern u16 hsd_804D78DE;

#endif
