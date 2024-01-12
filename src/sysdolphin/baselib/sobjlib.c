#include <dolphin/gx/GXAttr.h>
#include <dolphin/gx/GXMisc.h>
#include <dolphin/os.h>
#include <baselib/__baselib.h>
#include <baselib/cobj.h>
#include <baselib/gobj.h>
#include <baselib/gobjgxlink.h>
#include <baselib/gobjobject.h>
#include <baselib/objalloc.h>
#include <baselib/pobj.h>
#include <baselib/sobjlib.h>
#include <baselib/state.h>
#include <baselib/tev.h>

/* 004DB670 */ extern const s32 HSD_SObjLib_804DEA90;
/* 004DB66C */ extern const s32 HSD_SObjLib_804DEA8C;
/* 004DB668 */ extern const s32 HSD_SObjLib_804DEA88;
/* 004DB664 */ extern const s32 HSD_SObjLib_804DEA84;
/* 004DB660 */ extern const s32 HSD_SObjLib_804DEA80;
/* 004D4540 */ extern u8 HSD_SObjLib_804D7960;
/* 004CDCC0 */ extern HSD_ObjAllocData HSD_SObjLib_804D10E0;
/* 00408F90 */ extern s8 HSD_SObjLib_8040C3B0[10];
/* 00408F80 */ extern unk_t HSD_SObjLib_8040C3A0;
/* 003B6244 */ extern Vec3 HSD_SObjLib_803B9664;
/* 003B6238 */ extern Vec3 HSD_SObjLib_803B9658;
/* 003A21BC */ extern void HSD_SObjLib_803A55DC(HSD_GObj*, u16, s16, u32);
/* 003A20CC */ extern void HSD_SObjLib_803A54EC(HSD_GObj*, s32);
/* 003A1648 */ extern void HSD_SObjLib_803A4A68(unk_t);
/* 003A15C0 */ extern void HSD_SObjLib_803A49E0(unk_t);
/* 003A135C */ extern unk_t HSD_SObjLib_803A477C(s32, unk_t, s32, s32, s32,
                                                 s8);
/* 003A1320 */ extern void HSD_SObjLib_803A4740(unk_t);
/* 003A1320 */ extern void HSD_SObjLib_803A4740(unk_t);
/* 003A124C */ extern void HSD_SObjLib_803A466C(unk_t);
/* 003A10B4 */ extern void HSD_SObjLib_803A44D4(s32, unk_t, s32, f32, f32);
