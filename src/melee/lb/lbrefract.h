#ifndef _lbrefract_h_
#define _lbrefract_h_

#include <string.h>
#include <sysdolphin/baselib/memory.h>
#include <sysdolphin/baselib/cobj.h>
#include <sysdolphin/baselib/pobj.h>
#include <sysdolphin/baselib/tobj.h>
#include <dolphin/gx/GXMisc.h>
#include <dolphin/os/OSCache.h>

void func_800222A4();
void func_8002247C(HSD_CObj *);
void func_80022560();
void func_800225D4();
s32 func_800226A8(HSD_PObj *);
void func_80022998(s32, s32);
void func_80022BB8();
void func_80022BD0();
f32 atan2f(f32 y, f32 x);
f32 func_80022D1C(f32);
f32 func_80022DBC(f32);
f32 func_80022E68(f32);

// todo: locals to be removed

struct _RefractCallbackData;

typedef void (*RefractCallbackTypeA)(struct _RefractCallbackData *, s32, u32, s8, s8);
typedef void (*RefractCallbackTypeB)(struct _RefractCallbackData *, s32, u32, s8, s8, s8, s8);
typedef void (*RefractCallbackTypeC)(struct _RefractCallbackData *, s32, u32, s32 *, s32 *, s32 *, s32 *);
typedef struct _RefractCallbackData
{
    s32 unk0;        // x00
    s32 unk1;        // x04
    s32 unk2;        // x08
    s32 unk3;        // x08
    s32 unk4;        // x10
    s32 unk5;        // x14
    void *callback0; // x1C
    void *callback1; // x20

} RefractCallbackData;

void local_80021CE8(void *, s32);

extern RefractCallbackTypeA callback_80021F34;
extern RefractCallbackTypeA callback_80021F70;

extern RefractCallbackTypeB callback_80021FB4;
extern RefractCallbackTypeB callback_80021FB4;

extern RefractCallbackTypeC callback_80021FF8;
extern RefractCallbackTypeC callback_8002206C;
extern RefractCallbackTypeC callback_80022120;

s32 local_8002219C(RefractCallbackData *, s32, u32, u16, u16);

#endif
