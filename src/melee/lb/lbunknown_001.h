#ifndef _code_8000B074_h_
#define _code_8000B074_h_

#include <dolphin/mtx/types.h>
#include <sysdolphin/baselib/jobj.h>
#include <melee/sc/scene.h>

bool func_8000B074(HSD_JObj*);
bool func_8000B09C(HSD_JObj*);
bool func_8000B134(HSD_JObj*);
void func_8000B1CC(HSD_JObj*, Vec3*, Vec3*);
void func_8000B4FC(HSD_JObj*, HSD_Joint*);
void func_8000B5DC(HSD_JObj*, HSD_Joint*);
void func_8000B6A4(HSD_JObj*, HSD_Joint*);
void func_8000B760(HSD_JObj*, HSD_Joint*);
void func_8000B804(HSD_JObj*, HSD_Joint*);
static void lbl_8000B9D8(HSD_JObj*, f32**, s32);
void func_8000BA0C(HSD_JObj*, f32);
void func_8000BA44(HSD_DObj*, f32);
void func_8000BB24(HSD_DObj*, f32);
static HSD_JObj* lbFindJObjWithAObj(HSD_JObj*);
f32 func_8000BD28(HSD_JObj*);
f32 func_8000BDB4(HSD_JObj*);
f32 func_8000BE40(HSD_JObj*);
static HSD_AnimJoint* func_8000BECC(HSD_AnimJoint* animjoint);
f32 func_8000BFF0(HSD_AnimJoint* animjoint);
void func_8000C07C(HSD_JObj*, s32 i, HSD_AnimJoint**, HSD_MatAnimJoint**,
                   HSD_ShapeAnimJoint**);
void func_8000C0E8(HSD_JObj* jobj, s32 i, DynamicModelDesc* arg2);
void func_8000C160(void* mem, int size);
void func_8000C1C0(HSD_JObj*, HSD_JObj* constraint);
void func_8000C228(HSD_JObj*, HSD_JObj* constraint);
void func_8000C290(HSD_JObj*, HSD_JObj* constraint);
void func_8000C2F8(HSD_JObj*, HSD_JObj* constraint);
void func_8000C390(HSD_JObj*);
void func_8000C420(HSD_JObj*, u32 flags, f32 limit);
void func_8000C490(HSD_JObj*, HSD_JObj*, HSD_JObj*, f32, f32);
void func_8000C7BC(HSD_JObj* src, HSD_JObj* dst);
void func_8000C868(HSD_Joint*, HSD_JObj*, HSD_JObj*, f32, f32);
static s32 lbGetFreeColorRegImpl(s32 i0, HSD_TevDesc*, HSD_TExp*, HSD_TExp*);
s32 func_8000CC5C(s32 i0, HSD_MObj*, HSD_TExp*);
s32 func_8000CC8C(s32 i);
s32 func_8000CCA4(s32 i);
static s32 lbGetFreeAlphaRegImpl(s32 i0, HSD_TevDesc* cur, HSD_TExp*,
                                 HSD_TExp*);
s32 func_8000CD60(s32 i0, HSD_MObj*, HSD_TExp*);
s32 func_8000CD90(s32 i);
s32 func_8000CDA8(s32 i);
HSD_LObj* func_8000CDC0(HSD_LObj*);
void func_8000CE30(HSD_DObj*, HSD_DObj*);
void func_8000CE40(HSD_JObj*, HSD_DObj*);

f32 func_8000BDB4(HSD_JObj*);
void func_8000C1C0(HSD_JObj*, HSD_JObj*);
void func_8000C228(HSD_JObj*, HSD_JObj*);
void func_8000C420(HSD_JObj*, u32, f32);

#endif
