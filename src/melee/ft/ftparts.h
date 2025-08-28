#ifndef GALE01_0735BC
#define GALE01_0735BC

#include <platform.h>

#include "ft/forward.h"
#include "ftCommon/forward.h"
#include <baselib/forward.h>

#include <dolphin/mtx.h>

struct Fighter_804D6540_x0_t;

/* 0735BC */ void ftParts_JObjMakePositionMtx(HSD_JObj*, Mtx mtx, Mtx rmtx);
/* 073700 */ void ftParts_JObjInfoInit(void);
/* 073758 */ void ftParts_80073758(HSD_JObj*);
/* 073780 */ s32 ftParts_IntpJObjLoad(HSD_JObj*, HSD_Joint*, HSD_JObj* parent);
/* 0737D8 */ void ftParts_IntpJObjInfoInit(void);
/* 073830 */ void ftParts_80073830(HSD_PObj*, Mtx vmtx, Mtx pmtx,
                                   u32 rendermode);
/* 0739B8 */ void ftParts_800739B8(HSD_PObj*, Mtx vmtx, Mtx pmtx,
                                   u32 rendermode);
/* 073CA8 */ void ftParts_80073CA8(HSD_PObj*, Mtx vmtx, Mtx pmtx,
                                   u32 rendermode);
/* 074048 */ void ftParts_PObjSetupMtx(HSD_PObj*, Mtx vmtx, Mtx pmtx,
                                       u32 rendermode);
/* 0740E4 */ void ftParts_PObjInfoInit(void);
/* 074148 */ void ftParts_80074148(void);
/* 074170 */ void ftParts_80074170(void);
/* 074194 */ void ftParts_80074194(Fighter*, FighterBone* bone, HSD_JObj*,
                                   int* dobj_index, u32 tree_depth);
/* 0743E0 */ void ftParts_SetupParts(Fighter_GObj* fighter_obj);
/* 0743E0 */ void func_800743E0(void);
/* 07462C */ void ftParts_8007462C(Fighter_GObj*);
/* 07482C */ HSD_JObj* ftParts_8007482C(HSD_Joint*);
/* 07487C */ void ftParts_8007487C(UNK_T item, UNK_T, u8 costume_id, u32*,
                                   u32*);
/* 0749CC */ void ftParts_800749CC(Fighter_GObj*);
/* 074A4C */ void ftParts_80074A4C(Fighter_GObj*, int idx, int val);
/* 074A74 */ int ftParts_80074A74(Fighter_GObj*, int idx);
/* 074A8C */ void ftParts_80074A8C(Fighter_GObj*);
/* 074ACC */ void ftParts_80074ACC(Fighter_GObj*);
/* 074B0C */ void ftParts_80074B0C(Fighter_GObj*, int idx, int val);
/* 074B6C */ void ftParts_80074B6C(Fighter*, u32*, int, u32*);
/* 074CA0 */ void ftParts_80074CA0(UNK_T, s32, UNK_T);
/* 074D7C */ void ftParts_80074D7C(u32*, s32, u32*);
/* 074E58 */ void ftParts_80074E58(Fighter*);
/* 07500C */ Fighter_Part ftParts_GetBoneIndex(Fighter*, Fighter_Part);
/* 075028 */ int ftParts_80075028(size_t to_table_idx, size_t from_table_idx,
                                  size_t joint_idx);
/* 07506C */ u32 ftParts_8007506C(FighterKind ftkind, int part);
/* 0750C8 */ void ftParts_800750C8(Fighter*, enum_t, bool);
/* 075240 */ HSD_TObj*
ftParts_80075240(DObjList*, int n); ///< finds the n-th TObj in a DObjList
/* 075304 */ void ftParts_80075304(u8, HSD_JObj*, HSD_JObj*);
/* 0753D4 */ void ftParts_800753D4(Fighter*, struct Fighter_804D6540_x0_t*,
                                   HSD_Joint*);
/* 0755E8 */ void ftParts_800755E8(Fighter*, u8*);
/* 075650 */ void ftParts_80075650(Fighter_GObj*, HSD_JObj*, struct DObjList*);
/* 07584C */ void ftParts_JObjSetRotation(HSD_JObj*, Quaternion*);
/* 07592C */ void ftParts_8007592C(Fighter*, int part_idx, f32 rotate_x);
/* 075AF0 */ void ftParts_80075AF0(Fighter*, int part_idx, f32 rotate_y);
/* 075CB4 */ void ftParts_80075CB4(Fighter*, int part_idx, f32 rotate_z);
/* 075E78 */ float ftParts_80075E78(Fighter*, int part_idx);
/* 075F48 */ float ftParts_80075F48(Fighter*, int part_idx);

#endif
