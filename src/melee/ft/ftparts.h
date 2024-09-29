#ifndef GALE01_0735BC
#define GALE01_0735BC

#include <platform.h>

#include "ft/forward.h"
#include "ftCommon/forward.h"
#include <dolphin/mtx/forward.h>
#include <baselib/forward.h>

/* 0735BC */ void ftParts_JObjMakePositionMtx(HSD_JObj* jobj, Mtx mtx,
                                              Mtx rmtx);
/* 073700 */ void ftParts_JObjInfoInit(void);
/* 073758 */ void ftParts_80073758(HSD_JObj*);
/* 073780 */ s32 ftParts_IntpJObjLoad(HSD_JObj* jobj, HSD_Joint* joint,
                                      HSD_JObj* parent);
/* 0737D8 */ void ftParts_IntpJObjInfoInit(void);
/* 073830 */ void ftParts_80073830(void);
/* 0739B8 */ void ftParts_800739B8(void);
/* 073CA8 */ void ftParts_80073CA8(void);
/* 074048 */ void ftParts_PObjSetupMtx(HSD_PObj* pobj, Mtx vmtx, Mtx pmtx,
                                       u32 rendermode);
/* 0740E4 */ void ftParts_PObjInfoInit(void);
/* 074148 */ void ftParts_80074148(void);
/* 074170 */ void ftParts_80074170(void);
/* 074194 */ void ftParts_80074194(Fighter* fighter, FighterBone* bone,
                                   HSD_JObj* jobj, u32* dobj_index,
                                   u32 tree_depth);
/* 0743E0 */ void ftParts_SetupParts(HSD_GObj* fighter_obj);
/* 0743E0 */ void func_800743E0(void);
/* 07462C */ void ftParts_8007462C(void);
/* 07482C */ void ftParts_8007482C(void);
/* 07487C */ void ftParts_8007487C(UNK_T item, UNK_T, u8 costume_id, UNK_T,
                                   UNK_T);
/* 0749CC */ void ftParts_800749CC(HSD_GObj*);
/* 074A4C */ void ftParts_80074A4C(HSD_GObj*, enum_t, enum_t);
/* 074A74 */ s32 ftParts_80074A74(HSD_GObj*, s32);
/* 074A8C */ void ftParts_80074A8C(HSD_GObj*);
/* 074ACC */ void ftParts_80074ACC(ftCo_GObj* gobj);
/* 074B0C */ void ftParts_80074B0C(HSD_GObj*, int, int);
/* 074B6C */ void ftParts_80074B6C(void);
/* 074CA0 */ void ftParts_80074CA0(u32*, s32, u32*);
/* 074D7C */ void ftParts_80074D7C(u32*, s32, u32*);
/* 074E58 */ void ftParts_80074E58(Fighter*);
/* 07500C */ Fighter_Part ftParts_8007500C(Fighter*, Fighter_Part);
/* 075028 */ u8 ftParts_80075028(size_t to_table_idx, size_t from_table_idx,
                                 size_t joint_idx);
/* 07506C */ u32 ftParts_8007506C(s32 ftkind, u32 part);
/* 0750C8 */ void ftParts_800750C8(Fighter*, enum_t, bool);
/* 075240 */ void ftParts_80075240(void);
/* 075304 */ void ftParts_80075304(void);
/* 0753D4 */ void ftParts_800753D4(Fighter*, s32, UNK_T);
/* 0755E8 */ void ftParts_800755E8(Fighter*, u8*);
/* 075650 */ void ftParts_80075650(HSD_GObj* gobj, HSD_JObj*, u32*);
/* 07584C */ void ftParts_JObjSetRotation(HSD_JObj*, Quaternion*);
/* 07592C */ void ftParts_8007592C(Fighter*, s32, float);
/* 075AF0 */ void ftParts_80075AF0(Fighter*, s32, float);
/* 075CB4 */ void ftParts_80075CB4(Fighter*, s32, float);
/* 075E78 */ float ftParts_80075E78(Fighter*, bool);
/* 075F48 */ float ftParts_80075F48(Fighter*, s32);

#endif
