#ifndef _code_8000B074_h_
#define  _code_8000B074_h_

#include <dolphin/mtx/mtxtypes.h>

typedef Vec Vec3;

BOOL func_8000B074(struct _HSD_JObj*);
BOOL func_8000B09C(struct _HSD_JObj*);
BOOL func_8000B134(struct _HSD_JObj*);
void func_8000B1CC(struct _HSD_JObj*, Vec3*, Vec3*);
void func_8000B4FC(struct _HSD_JObj*, struct _HSD_Joint*);
void func_8000B5DC(struct _HSD_JObj*, struct _HSD_Joint*);
void func_8000B6A4(struct _HSD_JObj*, struct _HSD_Joint*);
void func_8000B760(struct _HSD_JObj*, struct _HSD_Joint*);
void func_8000B804(struct _HSD_JObj*, struct _HSD_Joint*);
static void lbl_8000B9D8(struct _HSD_JObj*, f32**, s32);
void func_8000BA0C(struct _HSD_JObj*, f32);
void func_8000BA44(struct _HSD_DObj*, f32);
void func_8000BB24(struct _HSD_DObj*, f32);
static struct _HSD_JObj* lbFindJObjWithAObj(struct _HSD_JObj*);
f32 func_8000BD28(struct _HSD_JObj*);
f32 func_8000BDB4(struct _HSD_JObj*);
f32 func_8000BE40(struct _HSD_JObj*);
static struct _HSD_AnimJoint* func_8000BECC(struct _HSD_AnimJoint* animjoint);
f32 func_8000BFF0(struct _HSD_AnimJoint* animjoint);
void func_8000C07C(struct _HSD_JObj*, s32 i, struct _HSD_AnimJoint**,
                   struct _HSD_MatAnimJoint**, struct _HSD_ShapeAnimJoint**);
void func_8000C0E8(struct _HSD_JObj*, s32 i, struct _UnkAnimContainer*);
void func_8000C160(void* mem, int size);
void func_8000C1C0(struct _HSD_JObj*, struct _HSD_JObj* constraint);
void func_8000C228(struct _HSD_JObj*, struct _HSD_JObj* constraint);
void func_8000C290(struct _HSD_JObj*, struct _HSD_JObj* constraint);
void func_8000C2F8(struct _HSD_JObj*, struct _HSD_JObj* constraint);
void func_8000C390(struct _HSD_JObj*);
void func_8000C420(struct _HSD_JObj*, u32 flags, f32 limit);
void func_8000C490(struct _HSD_JObj*, struct _HSD_JObj*, struct _HSD_JObj*, f32, f32);
void func_8000C7BC(struct _HSD_JObj* src, struct _HSD_JObj* dst);
void func_8000C868(struct _HSD_Joint*, struct _HSD_JObj*, struct _HSD_JObj*, f32, f32);
static s32 lbGetFreeColorRegImpl(s32 i0, struct _HSD_TevDesc*,
                                 union _HSD_TExp*, union _HSD_TExp*);
s32 func_8000CC5C(s32 i0, struct _HSD_MObj*, union _HSD_TExp*);
s32 func_8000CC8C(s32 i);
s32 func_8000CCA4(s32 i);
static s32 lbGetFreeAlphaRegImpl(s32 i0, struct _HSD_TevDesc* cur,
                                 union _HSD_TExp*, union _HSD_TExp*);
s32 func_8000CD60(s32 i0, struct _HSD_MObj*, union _HSD_TExp*);
s32 func_8000CD90(s32 i);
s32 func_8000CDA8(s32 i);
struct _HSD_LObj* func_8000CDC0(struct _HSD_LObj*);
void func_8000CE30(struct _HSD_DObj*, struct _HSD_DObj*);
void func_8000CE40(struct _HSD_JObj*, struct _HSD_DObj*);

#endif
