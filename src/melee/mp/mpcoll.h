#ifndef GALE01_041C78
#define GALE01_041C78

#include <platform.h>
#include <dolphin/mtx/forward.h>
#include <baselib/forward.h>

#include "ft/types.h"

/* 041C78 */ void mpColl_80041C78(void);
/* 041C8C */ void mpColl_80041C8C(CollData* cd);
/* 041DD0 */ void mpColl_80041DD0(CollData* cd, u32 flags);
/* 041EE4 */ void mpColl_80041EE4(CollData*);
/* 042078 */ void mpColl_80042078(CollData* cd, HSD_GObj* gobj, HSD_JObj*,
                                  HSD_JObj*, HSD_JObj*, HSD_JObj*, HSD_JObj*,
                                  HSD_JObj*, HSD_JObj*, float);
/* 04220C */ void mpColl_8004220C(CollData* cd, HSD_GObj* gobj, float, float,
                                  float, float);
/* 042374 */ void mpColl_80042374(CollData*, float, float, float);
/* 042384 */ void mpColl_80042384(CollData* cd);
/* 0424DC */ void mpColl_800424DC(CollData* cd, u32 flags);
/* 04293C */ void mpColl_8004293C(CollData* cd);
/* 042C58 */ void mpColl_80042C58(CollData*, ftECB*);
/* 042D24 */ void mpColl_80042D24(CollData* cd);
/* 042DB0 */ void mpColl_80042DB0(CollData* ecb, float time);
/* 043268 */ void mpColl_80043268(CollData*, s32, s32, float);
/* 043324 */ void mpColl_80043324(CollData*, s32, s32);
/* 043558 */ void mpColl_80043558(CollData*, s32);
/* 043670 */ void mpColl_80043670(CollData*);
/* 043680 */ void mpColl_80043680(CollData*, Vec3*);
/* 0436D8 */ void mpColl_800436D8(CollData*, int facing_dir);
/* 0436E4 */ void mpColl_800436E4(CollData*, float);
/* 043754 */ s32 mpColl_80043754(s32 (*)(void*, u32), CollData*, u32);
/* 0439FC */ void mpColl_800439FC(CollData*);
/* 043ADC */ void mpColl_80043ADC(CollData*);
/* 043BBC */ bool mpColl_80043BBC(CollData*, s32*);
/* 043C6C */ void mpColl_80043C6C(CollData*, s32, s32);
/* 044164 */ bool mpColl_80044164(CollData* cd, int* p_ledge_id);
/* 0443C4 */ bool mpColl_800443C4(CollData* cd, int* p_ledge_id);
/* 046904 */ s32 mpColl_80046904(void*, u32);
/* 0471F8 */ void mpColl_800471F8(CollData*);
/* 04730C */ void mpColl_8004730C(CollData*, float (*x)[6]);
/* 0473CC */ void mpColl_800473CC(CollData*);
/* 0474E0 */ void mpColl_800474E0(CollData*);
/* 0475F4 */ void mpColl_800475F4(CollData*);
/* 0476B4 */ void mpColl_800476B4(CollData*);
/* 0477E0 */ bool mpColl_800477E0(CollData*);
/* 0478F4 */ void mpColl_800478F4(CollData*);
/* 047A08 */ void mpColl_80047A08(CollData*);
/* 047AC8 */ void mpColl_80047AC8(CollData*);
/* 047BF4 */ void mpColl_80047BF4(CollData*);
/* 047D20 */ void mpColl_80047D20(CollData*);
/* 047E14 */ void mpColl_80047E14(CollData*);
/* 047F40 */ void mpColl_80047F40(CollData*);
/* 04806C */ void mpColl_8004806C(CollData*);
/* 048160 */ void mpColl_80048160(CollData*);
/* 048274 */ void mpColl_80048274(CollData*);
/* 048388 */ void mpColl_80048388(CollData*);
/* 048464 */ void mpColl_80048464(CollData*);
/* 048578 */ void mpColl_80048578(CollData*);
/* 048654 */ void mpColl_80048654(CollData*);
/* 048768 */ void mpColl_80048768(CollData*);
/* 04B108 */ void mpColl_8004B108(CollData*);
/* 04B21C */ void mpColl_8004B21C(CollData*);
/* 04B2DC */ void mpColl_8004B2DC(CollData*);
/* 04B3F0 */ void mpColl_8004B3F0(CollData*);
/* 04B5C4 */ void mpColl_8004B5C4(CollData*);
/* 04CA6C */ void mpColl_8004CA6C(CollData*);
/* 04CBC0 */ bool mpColl_8004CBC0(CollData*);
/* 04CBE8 */ void mpColl_8004CBE8(CollData*);
/* 04CBF4 */ void mpColl_8004CBF4(CollData*);
/* 04CC00 */ void mpColl_8004CC00(CollData*);
/* 4D64A0 */ extern s32 mpColl_804D64A0;
/* 4D64A4 */ extern s32 mpColl_804D64A4;
/* 4D64A8 */ extern s32 mpColl_804D64A8;
/* 4D64AC */ extern u32 mpColl_804D64AC;

#endif
