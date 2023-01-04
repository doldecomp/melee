#ifndef MELEE_FT_FTBOSSLIB_H
#define MELEE_FT_FTBOSSLIB_H

#include <melee/ft/fighter.h>

HSD_GObj* func_8015C3E8(s32); // func_8015C3E8(FighterKind)
s32 func_8015C44C(s32);       // func_8015C44C(FighterKind)

void func_8015BD20(struct _HSD_GObj*);
void func_8015BD24(s32, f32*, f32, s32, s32, s32);
void func_8015BDB4(struct _HSD_GObj*);
void func_8015BE40(struct _HSD_GObj* gobj, Vec*, f32*, f32, f32);
void func_8015BF74(struct _HSD_GObj*, f32);
void func_8015C010(struct _HSD_GObj*, f32);
void func_8015C09C(struct _HSD_GObj*, f32);
void func_8015C190(struct _HSD_GObj*);
void func_8015C208(struct _HSD_GObj*, Vec*);
struct _HSD_GObj* func_8015C244(struct _HSD_GObj*, Vec*);
BOOL func_8015C31C(void);
BOOL func_8015C3A0(void);
struct _HSD_GObj* func_8015C3E8(s32);
s32 func_8015C44C(s32);
s32 func_8015C4C4(void);
void func_8015C5F8(struct _HSD_GObj*);

#endif
