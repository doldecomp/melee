#ifndef GALE01_041C78
#define GALE01_041C78

#include <platform.h>

#include "ft/forward.h"
#include "ftCommon/forward.h"
#include "mp/forward.h"
#include <baselib/forward.h>

#include <dolphin/mtx.h>

/* 041C78 */ void mpColl_80041C78(void);
/* 041C8C */ void mpCollPrev(CollData* cd);
/* 041DD0 */ void mpCollCheckBounding(CollData* cd, u32 flags);
/* 041EE4 */ void mpColl_80041EE4(CollData*);
/* 042078 */ void mpColl_SetECBSource_JObj(CollData* cd, HSD_GObj* gobj,
                                           HSD_JObj*, HSD_JObj*, HSD_JObj*,
                                           HSD_JObj*, HSD_JObj*, HSD_JObj*,
                                           HSD_JObj*, float);
/* 04220C */ void mpColl_SetECBSource_Fixed(CollData* cd, HSD_GObj* gobj,
                                            float, float, float, float);
/* 042374 */ void mpColl_SetLedgeSnap(CollData*, float, float, float);
/* 042384 */ void mpColl_80042384(CollData* cd);
/* 0424DC */ void mpColl_LoadECB_JObj(CollData*, u32 flags);
/* 04293C */ void mpColl_LoadECB_Fixed(CollData*);
/* 042C58 */ void mpColl_80042C58(CollData*, ftCollisionBox*);
/* 042D24 */ void mpColl_LoadECB(CollData*);
/* 042DB0 */ void mpCollInterpolateECB(CollData*, float time);
/* 043268 */ void mpColl_80043268(CollData*, int line_id, bool, float);
/* 043324 */ void mpCollEnd(CollData*, bool, bool);
/* 043558 */ void mpColl_80043558(CollData*, int line_id);
/* 043670 */ void mpColl_80043670(CollData*);
/* 043680 */ void mpColl_80043680(CollData*, Vec3*);
/* 0436D8 */ void mpCollSetFacingDir(CollData*, int facing_dir);
/* 0436E4 */ void mpColl_800436E4(CollData*, float);
/* 043754 */ bool mpColl_80043754(mpColl_Callback, CollData*, u32);
/* 0439FC */ void mpColl_800439FC(CollData*);
/* 043ADC */ void mpColl_80043ADC(CollData*);
/* 043BBC */ bool mpColl_80043BBC(CollData*, int* line_id_out);
/* 043C6C */ void mpColl_80043C6C(CollData*, int, bool);
/* 043E90 */ bool mpColl_80043E90(CollData*, int* line_id_out);
/* 043F40 */ void mpColl_80043F40(CollData*, int, bool);
/* 044164 */ bool mpColl_80044164(CollData* cd, int* p_ledge_id);
/* 0443C4 */ bool mpColl_800443C4(CollData* cd, int* p_ledge_id);
/* 044628 */ bool mpColl_80044628_Floor(CollData*,
                                        bool (*)(Fighter_GObj*, int),
                                        Fighter_GObj*, int);
/* 044838 */ bool mpColl_80044838_Floor(CollData* coll, bool ignore_bottom);
/* 044948 */ bool mpColl_80044948_Floor(CollData* coll);
/* 044AD8 */ bool mpColl_80044AD8_Ceiling(CollData*, int);
/* 044C74 */ bool mpColl_80044C74_Ceiling(CollData*);
/* 044E10 */ bool mpColl_80044E10_RightWall(CollData*);
/* 0454A4 */ bool mpColl_800454A4_RightWall(CollData*);
/* 045B74 */ bool mpColl_80045B74_LeftWall(CollData*);
/* 046224 */ bool mpColl_80046224_LeftWall(CollData*);
/* 046904 */ bool mpColl_80046904(CollData*, u32 flags);
/* 046F78 */ bool mpColl_80046F78(CollData*, u32);
/* 0471F8 */ bool mpColl_800471F8(CollData*);
/* 04730C */ bool mpColl_8004730C(CollData*, ftCollisionBox*);
/* 0473CC */ bool mpColl_800473CC(CollData*);
/* 0474E0 */ bool mpColl_800474E0(CollData*);
/* 0475F4 */ bool mpColl_800475F4(CollData*, ftCollisionBox*);
/* 0476B4 */ bool mpColl_800476B4(CollData*, bool (*)(Fighter_GObj*, enum_t),
                                  Fighter_GObj*);
/* 0477E0 */ bool mpColl_800477E0(CollData*);
/* 0478F4 */ bool mpColl_800478F4(CollData*);
/* 047A08 */ bool mpColl_80047A08(CollData*, ftCollisionBox*);
/* 047AC8 */ bool mpColl_80047AC8(CollData*, bool (*)(Fighter_GObj*, enum_t),
                                  Fighter_GObj*);
/* 047BF4 */ bool mpColl_80047BF4(CollData*, bool (*)(Fighter_GObj*, enum_t),
                                  Fighter_GObj*);
/* 047D20 */ bool mpColl_80047D20(CollData*, bool (*)(Fighter_GObj*, enum_t),
                                  Fighter_GObj*);
/* 047E14 */ bool mpColl_80047E14(CollData*, bool (*)(Fighter_GObj*, enum_t),
                                  Fighter_GObj*);
/* 047F40 */ bool mpColl_80047F40(CollData*, bool (*)(Fighter_GObj*, enum_t),
                                  Fighter_GObj*);
/* 04806C */ bool mpColl_8004806C(CollData*, bool (*)(Fighter_GObj*, enum_t),
                                  Fighter_GObj*);
/* 048160 */ bool mpColl_80048160(CollData*);
/* 048274 */ bool mpColl_80048274(CollData*);
/* 048388 */ bool mpColl_80048388(CollData*);
/* 048464 */ bool mpColl_80048464(CollData*);
/* 048578 */ bool mpColl_80048578(CollData*);
/* 048654 */ bool mpColl_80048654(CollData*);
/* 048768 */ bool mpColl_80048768(CollData*);
/* 048844 */ bool mpColl_80048844(CollData*, f32);
/* 0488F4 */ bool mpColl_800488F4(CollData*);
/* 048AB0 */ bool mpColl_80048AB0_RightWall(CollData*);
/* 0491C8 */ bool mpColl_800491C8_RightWall(CollData*);
/* 049778 */ bool mpColl_80049778_LeftWall(CollData*);
/* 049EAC */ bool mpColl_80049EAC_LeftWall(CollData*);
/* 04A45C */ bool mpColl_8004A45C_Floor(CollData*, int line_id);
/* 04A678 */ bool mpColl_8004A678_Floor(CollData*, int line_id);
/* 04A908 */ bool mpColl_8004A908_Floor(CollData*, int line_id);
/* 04AB80 */ bool mpColl_8004AB80(CollData*);
/* 04ACE4 */ bool mpColl_8004ACE4(CollData*, int);
/* 04B108 */ bool mpColl_8004B108(CollData*);
/* 04B21C */ bool mpColl_8004B21C(CollData*, ftCollisionBox*);
/* 04B2DC */ bool mpColl_8004B2DC(CollData*);
/* 04B3F0 */ bool mpColl_8004B3F0(CollData*, ftCollisionBox*);
/* 04B4B0 */ bool mpColl_8004B4B0(CollData*);
/* 04B5C4 */ bool mpColl_8004B5C4(CollData*);
/* 04B6D8 */ bool mpColl_8004B6D8(CollData*);
/* 04B894 */ bool mpColl_8004B894_RightWall(CollData*);
/* 04BDD4 */ bool mpColl_8004BDD4_LeftWall(CollData*);
/* 04C328 */ bool mpColl_8004C328_Ceiling(CollData*, int line_id);
/* 04C534 */ bool mpColl_8004C534(CollData*, u32);
/* 04C750 */ bool mpColl_8004C750(CollData*);
/* 04C864 */ void mpCollSqueezeHorizontal(CollData*, bool airborne, float left,
                                          float right);
/* 04C91C */ void mpCollSqueezeVertical(CollData*, bool airborne, float top,
                                        float bottom);
/* 04CA6C */ float mpColl_8004CA6C(CollData*);
/* 04CAA0 */ bool mpCollGetSpeedCeiling(CollData*, Vec3* speed);
/* 04CAE8 */ bool mpCollGetSpeedLeftWall(CollData*, Vec3* speed);
/* 04CB30 */ bool mpCollGetSpeedRightWall(CollData*, Vec3* speed);
/* 04CB78 */ bool mpCollGetSpeedFloor(CollData*, Vec3* speed);
/* 04CBC0 */ bool mpColl_IsOnPlatform(CollData*);
/* 04CBE8 */ void mpUpdateFloorSkip(CollData*);
/* 04CBF4 */ void mpClearFloorSkip(CollData*);
/* 04CC00 */ void mpCopyCollData(CollData* src, CollData* dst, int);
/* 04D024 */ bool mpColl_8004D024(Vec3*);
/* 4D64AC */ extern int mpColl_804D64AC;

#endif
