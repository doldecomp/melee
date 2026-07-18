#ifndef GALE01_391580
#define GALE01_391580

#include <placeholder.h>
#include <platform.h>

#include "baselib/forward.h"

#include <sysdolphin/baselib/generator.h>

#include "baselib/jobj.h"

/* 3983A4 */ void hsd_803983A4(HSD_Generator*);
/* 3984F4 */ void psInitDataBankLoad(int bank, int* cmdBank, int* texBank,
                                     u32* ref, int* formBank);
/* 398614 */ void psInitDataBankLocate(HSD_Archive* cmdBank,
                                       HSD_Archive* texBank, int* formBank);
/* 3989A0 */ void psInitDataBankRelocate(int* cmdBank, int* texBank,
                                         int* formBank, int* newCmdBank,
                                         int* newTexBank, int* newFormBank);
/* 398A08 */ void hsd_80398A08(u32);
/* 398C04 */ HSD_Particle* hsd_80398C04(HSD_Particle**, int, int, u32, u16,
                                        u8*, int, int, f32, f32, f32, f32, f32,
                                        f32, f32, f32, f32, HSD_Generator*,
                                        int);
/* 398F0C */ void hsd_80398F0C(s32, s32, s32, u16, s32, s32, s32, s32, f32,
                               f32, f32, f32, f32, f32, f32, f32, f32);
/* 398F8C */ void hsd_80398F8C(HSD_Particle*, f32);
/* 3991D8 */ s32 hsd_803991D8(HSD_Generator*, HSD_JObj*, f32, f32);
/* 39930C */ void* hsd_8039930C(void*, void*);
/* 39CEAC */ void hsd_8039CEAC(u32);
/* 39CF4C */ void hsd_8039CF4C(s32, HSD_JObj*);
/* 39D048 */ void hsd_8039D048(void* particle);

#endif
