#ifndef GALE01_041C78
#define GALE01_041C78

#include <platform.h>

#include "ft/forward.h"
#include "ftCommon/forward.h"
#include "mp/forward.h"
#include <baselib/forward.h>

#include <dolphin/mtx.h>

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
/* 042C58 */ void mpColl_80042C58(CollData*, ftCollisionBox*);
/* 042D24 */ void mpColl_80042D24(CollData* cd);
/* 042DB0 */ void mpColl_80042DB0(CollData* ecb, float time);
/* 043268 */ void mpColl_80043268(CollData*, s32, s32, float);
/* 043324 */ void mpColl_80043324(CollData*, s32, s32);
/* 043558 */ void mpColl_80043558(CollData*, s32);
/* 043670 */ void mpColl_80043670(CollData*);
/* 043680 */ void mpColl_80043680(CollData*, Vec3*);
/* 0436D8 */ void mpColl_800436D8(CollData*, int facing_dir);
/* 0436E4 */ void mpColl_800436E4(CollData*, float);
/* 043754 */ bool mpColl_80043754(mpColl_Callback, CollData*, u32);
/* 0439FC */ void mpColl_800439FC(CollData*);
/* 043ADC */ void mpColl_80043ADC(CollData*);
/* 043BBC */ bool mpColl_80043BBC(CollData*, s32*);
/* 043C6C */ void mpColl_80043C6C(CollData*, s32, s32);
/* 043E90 */ bool mpColl_80043E90(CollData*, s32*);
/* 043F40 */ void mpColl_80043F40(CollData*, s32, s32);
/* 044164 */ bool mpColl_80044164(CollData* cd, int* p_ledge_id);
/* 0443C4 */ bool mpColl_800443C4(CollData* cd, int* p_ledge_id);
/* 044628 */ bool mpColl_80044628(CollData*, bool (*)(Fighter_GObj*, int),
                                  void*, s32);
/* 044838 */ bool mpColl_80044838(CollData*, s32);
/* 044948 */ s32 mpColl_80044948(CollData*);
/* 044AD8 */ s32 mpColl_80044AD8(CollData*, s32);
/* 044C74 */ s32 mpColl_80044C74(CollData*);
/* 044E10 */ s32 mpColl_80044E10(CollData*);
/* 0454A4 */ s32 mpColl_800454A4(CollData*);
/* 045B74 */ s32 mpColl_80045B74(CollData*);
/* 046224 */ s32 mpColl_80046224(CollData*);
/* 046904 */ bool mpColl_80046904(CollData*, u32 flags);
/* 046F78 */ bool fn_80046F78(CollData*, u32);
/* 0471F8 */ bool mpColl_800471F8(CollData*);
/* 04730C */ bool mpColl_8004730C(CollData*, ftCollisionBox*);
/* 0473CC */ bool mpColl_800473CC(CollData*);
/* 0474E0 */ bool mpColl_800474E0(CollData*);
/* 0475F4 */ bool mpColl_800475F4(CollData*, ftCollisionBox*);
/* 0476B4 */ bool mpColl_800476B4(CollData*, bool (*)(Fighter_GObj*, enum_t), Fighter_GObj*);
/* 0477E0 */ bool mpColl_800477E0(CollData*);
/* 0478F4 */ bool mpColl_800478F4(CollData*);
/* 047A08 */ bool mpColl_80047A08(CollData*, ftCollisionBox*);
/* 047AC8 */ bool mpColl_80047AC8(CollData*, bool (*)(Fighter_GObj*, enum_t), Fighter_GObj*);
/* 047BF4 */ bool mpColl_80047BF4(CollData*, bool (*)(Fighter_GObj*, enum_t), Fighter_GObj*);
/* 047D20 */ bool mpColl_80047D20(CollData*, bool (*)(Fighter_GObj*, enum_t), Fighter_GObj*);
/* 047E14 */ bool mpColl_80047E14(CollData*, bool (*)(Fighter_GObj*, enum_t), Fighter_GObj*);
/* 047F40 */ bool mpColl_80047F40(CollData*, bool (*)(Fighter_GObj*, enum_t), Fighter_GObj*);
/* 04806C */ bool mpColl_8004806C(CollData*, bool (*)(Fighter_GObj*, enum_t), Fighter_GObj*);
/* 048160 */ bool mpColl_80048160(CollData*);
/* 048274 */ bool mpColl_80048274(CollData*);
/* 048388 */ bool mpColl_80048388(CollData*);
/* 048464 */ bool mpColl_80048464(CollData*);
/* 048578 */ bool mpColl_80048578(CollData*);
/* 048654 */ bool mpColl_80048654(CollData*);
/* 048768 */ bool mpColl_80048768(CollData*);
/* 048844 */ bool mpColl_80048844(CollData*, f32);
/* 0488F4 */ bool mpColl_800488F4(CollData*);
/* 048AB0 */ bool mpColl_80048AB0(CollData*);
/* 0491C8 */ bool mpColl_800491C8(CollData*);
/* 049778 */ bool mpColl_80049778(CollData*);
/* 049EAC */ bool mpColl_80049EAC(CollData*);
/* 04A45C */ bool mpColl_8004A45C(CollData*, int);
/* 04A678 */ bool mpColl_8004A678(CollData*, int);
/* 04A908 */ bool mpColl_8004A908(CollData*, int);
/* 04AB80 */ bool mpColl_8004AB80(CollData*);
/* 04ACE4 */ bool fn_8004ACE4(CollData*, int);
/* 04B108 */ bool mpColl_8004B108(CollData*);
/* 04B21C */ bool mpColl_8004B21C(CollData*, ftCollisionBox*);
/* 04B2DC */ bool mpColl_8004B2DC(CollData*);
/* 04B3F0 */ bool mpColl_8004B3F0(CollData*, ftCollisionBox*);
/* 04B4B0 */ bool mpColl_8004B4B0(CollData*);
/* 04B5C4 */ bool mpColl_8004B5C4(CollData*);
/* 04B6D8 */ bool mpColl_8004B6D8(CollData*);
/* 04B894 */ UNK_RET mpColl_8004B894(UNK_PARAMS);
/* 04BDD4 */ UNK_RET mpColl_8004BDD4(UNK_PARAMS);
/* 04C328 */ UNK_RET mpColl_8004C328(UNK_PARAMS);
/* 04C534 */ bool fn_8004C534(CollData*, u32);
/* 04C750 */ bool mpColl_8004C750(CollData*);
/* 04C864 */ void mpColl_8004C864(CollData*, s32, float, float);
/* 04C91C */ void mpColl_8004C91C(CollData*, s32, float, float);
/* 04CA6C */ float mpColl_8004CA6C(CollData*);
/* 04CAA0 */ bool mpColl_8004CAA0(CollData*, Vec3*);
/* 04CAE8 */ bool mpColl_8004CAE8(CollData*, Vec3*);
/* 04CB30 */ bool mpColl_8004CB30(CollData*, Vec3*);
/* 04CB78 */ bool mpColl_8004CB78(CollData*, Vec3*);
/* 04CBC0 */ bool mpColl_8004CBC0(CollData*);
/* 04CBE8 */ void mpColl_8004CBE8(CollData*);
/* 04CBF4 */ void mpColl_8004CBF4(CollData*);
/* 04CC00 */ void mpColl_8004CC00(CollData*, CollData*, int);
/* 04D024 */ bool mpColl_8004D024(Vec3*);
/* 0528CC */ s32 mpColl_800528CC(s32);
/* 052A98 */ s32 mpColl_80052A98(s32);
/* 4D64AC */ extern int mpColl_804D64AC;

#endif
