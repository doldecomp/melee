#include <sysdolphin/baselib/__baselib.h>
#include <sysdolphin/baselib/sobjlib.h>

#include <sysdolphin/baselib/gobjgxlink.h>
#include <sysdolphin/baselib/cobj.h>
#include <sysdolphin/baselib/gobj.h>
#include <sysdolphin/baselib/pobj.h>
#include <dolphin/gx/GXMisc.h>
#include <dolphin/gx/GXAttr.h>
#include <sysdolphin/baselib/tev.h>
#include <dolphin/gx/GX.h>
#include <dolphin/os/os.h>
#include <sysdolphin/baselib/state.h>
#include <sysdolphin/baselib/tev.h>
#include <sysdolphin/baselib/objalloc.h>
#include <sysdolphin/baselib/gobjobject.h>

extern Vec lbl_803B9658;
extern Vec lbl_803B9664;
extern unk_t lbl_8040C3A0;
extern const s32 lbl_804DEA80;
extern const s32 lbl_804DEA84;
extern const s32 lbl_804DEA88;
extern const s32 lbl_804DEA8C;
extern const s32 lbl_804DEA90;
extern s8 lbl_8040C3B0[10];
extern HSD_ObjAllocData lbl_804D10E0;
extern u8 lbl_804D7960;

void func_803A54EC(HSD_GObj *, s32);
void func_803A55DC(HSD_GObj *arg0, u16 arg1, s16 arg2, u32 arg3);
void func_803A4740(void *arg0);
void func_803A4A68(void *arg0);
void func_803A49E0(void *arg0);
void *func_803A477C(s32 arg0, void *arg1, s32 arg2, s32 arg3, s32 arg4, s8 arg5);
void func_803A44D4(s32 arg0, void *arg1, s32 arg2, f32 arg3, f32 arg4);
void func_803A4740(void *arg0);
void func_803A466C(unk_t);