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

/* 004DB670 */ extern const s32 lbl_804DEA90;
/* 004DB66C */ extern const s32 lbl_804DEA8C;
/* 004DB668 */ extern const s32 lbl_804DEA88;
/* 004DB664 */ extern const s32 lbl_804DEA84;
/* 004DB660 */ extern const s32 lbl_804DEA80;
/* 004D4540 */ extern u8 lbl_804D7960;
/* 004CDCC0 */ extern HSD_ObjAllocData lbl_804D10E0;
/* 00408F90 */ extern s8 lbl_8040C3B0[10];
/* 00408F80 */ extern unk_t lbl_8040C3A0;
/* 003B6244 */ extern Vec lbl_803B9664;
/* 003B6238 */ extern Vec lbl_803B9658;
/* 003A21BC */ extern void func_803A55DC(HSD_GObj *, u16, s16, u32);
/* 003A20CC */ extern void func_803A54EC(HSD_GObj *, s32);
/* 003A1648 */ extern void func_803A4A68(unk_t);
/* 003A15C0 */ extern void func_803A49E0(unk_t);
/* 003A135C */ extern unk_t func_803A477C(s32, unk_t, s32, s32, s32, s8);
/* 003A1320 */ extern void func_803A4740(unk_t);
/* 003A1320 */ extern void func_803A4740(unk_t);
/* 003A124C */ extern void func_803A466C(unk_t);
/* 003A10B4 */ extern void func_803A44D4(s32, unk_t, s32, f32, f32);
