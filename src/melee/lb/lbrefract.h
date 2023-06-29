#ifndef _lbrefract_h_
#define _lbrefract_h_

#include <string.h>
#include <dolphin/gx/GXMisc.h>
#include <dolphin/os/OSCache.h>
#include <baselib/cobj.h>
#include <baselib/memory.h>
#include <baselib/pobj.h>
#include <baselib/tobj.h>

void lbRefract_800222A4(void);
void lbRefract_8002247C(HSD_CObj*);
void lbRefract_80022560(void);
void lbRefract_800225D4(void);
s32 lbRefract_PObjLoad(HSD_PObj* pobj, HSD_PObjDesc* desc);
void lbRefract_80022998(s32, s32);
void lbRefract_80022BB8(void);
void lbRefract_80022BD0(void);

#pragma region lbrefract_003

float atan2f(float y, float x);
float acosf(float);
float asinf(float);
float atanf(float);

#pragma endregion

// todo: locals to be removed

struct _RefractCallbackData;

typedef void (*RefractCallbackTypeA)(struct _RefractCallbackData*, s32, u32,
                                     s8, s8);
typedef void (*RefractCallbackTypeB)(struct _RefractCallbackData*, s32, u32,
                                     s8, s8, s8, s8);
typedef void (*RefractCallbackTypeC)(struct _RefractCallbackData*, s32, u32,
                                     s32*, s32*, s32*, s32*);
typedef struct _RefractCallbackData {
    s32 unk0;        // x00
    s32 unk1;        // x04
    s32 unk2;        // x08
    s32 unk3;        // x08
    s32 unk4;        // x10
    s32 unk5;        // x14
    void* callback0; // x1C
    void* callback1; // x20

} RefractCallbackData;

void lbRefract_80021CE8(void*, s32);

extern RefractCallbackTypeA lbRefract_80021F34;
extern RefractCallbackTypeA lbRefract_80021F70;

extern RefractCallbackTypeB lbRefract_80021FB4;

extern RefractCallbackTypeC lbRefract_80021FF8;
extern RefractCallbackTypeC lbRefract_8002206C;
extern RefractCallbackTypeC lbRefract_80022120;

s32 lbRefract_8002219C(RefractCallbackData*, s32, u32, u16, u16);

#endif
