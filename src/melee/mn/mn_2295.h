#ifndef GALE01_2295AC
#define GALE01_2295AC

#include <platform.h>

#include "dolphin/mtx/types.h"

#include <baselib/object.h>

u8 mn_802295AC(void); //< Test for some sort of analogue movement and return
                      // the port that inputted it.
u32 mn_80229624(u32); //< Return a MenuEvent bitfield of controller input.
void mn_8022EA08(char*,
                 u32); //< Fill arg0 with the string representation of arg1.

s32 mn_8022EB24(s32, s32); //< Shift arg0 left in base 10 by arg1 digits and
                           // return the ones digit>

void mn_8022F3D8(void*, u8, HSD_TypeMask);
void mn_8022ED6C(HSD_JObj*, Vec3*);

void mn_80229894(s32, s32, s32);

s32 mn_8022EB78(s32); //< Return how many digits are in a number.

float mn_8022EC18(HSD_JObj*, float*, int);
void mn_80229860(s8);
f32 mn_8022F298(HSD_JObj*);

typedef struct _mn_unk1 {
    u8 x0;
    u8 x1;
    s16 x2;
    s32 x4;
    u64 x8;
    u8 x10;
    u8 x11;
} mn_unk1;

typedef struct _mn_unk2 {
    u16 x0;
    u16 x2;
    s32 x4;
} mn_unk2;

extern HSD_Archive* mn_804D6BB8;
extern mn_unk1 mn_804A04F0;
extern mn_unk2 mn_804D6BC8;

#endif
