#ifndef _ftlib_h_
#define _ftlib_h_

#include <melee/ft/fighter.h>
#include <sysdolphin/baselib/gobj.h>

s32 func_800860C4(void);
bool func_800860E8(void);
bool func_80086140(void);
HSD_GObj* func_80086198(HSD_GObj*);
HSD_GObj* func_8008627C(Vec3*, HSD_GObj*);
HSD_GObj* func_80086368(Vec3*, HSD_GObj*, f32);
f32 func_800864A8(Vec3*, HSD_GObj*);
f32 func_800865C0(HSD_GObj*);
s32 func_800865CC(HSD_GObj*);
void func_800865D8(HSD_GObj*, f32*, f32*);
void* func_800865F0(HSD_GObj*);
void* func_80086630(HSD_GObj*, s32);
void func_80086644(HSD_GObj*, Vec3*);
void func_80086664(HSD_GObj*, Vec3*);
void func_80086684(HSD_GObj*, Vec3*);
void ftData_SetScale(HSD_GObj*, f32);
void func_800866DC(HSD_GObj*, Vec3*);
void func_80086724(HSD_GObj*, HSD_GObj*);
void func_80086764(HSD_GObj*);
HSD_GObj* func_80086794(HSD_GObj*);
bool func_800867A0(HSD_GObj*, HSD_GObj*);
HSD_GObj* func_800867CC(HSD_GObj*);
bool func_800867D8(HSD_GObj*);
void func_800867E8(HSD_GObj*);
void func_80086824(void);
void func_8008688C(HSD_GObj*);
void func_800868A4(void);
bool func_800868D4(HSD_GObj*, HSD_GObj*);

// Check if entity is a fighter
bool func_80086960(HSD_GObj*);

CollData* func_80086984(HSD_GObj*);
void func_80086990(HSD_GObj*, Vec3*);
f32 func_800869D4(HSD_GObj*);
f32 func_800869F8(HSD_GObj*);
f32 func_80086A0C(HSD_GObj*);
bool func_80086A18(HSD_GObj*);
void func_80086A4C(HSD_GObj*, f32);
bool func_80086A58(HSD_GObj*, S32Vec2*);
bool func_80086A8C(HSD_GObj*);
bool func_80086B64(HSD_GObj*);
CameraBox* func_80086B74(HSD_GObj*);
f32 func_80086B80(HSD_GObj*);
void func_80086B90(HSD_GObj*, Vec3* v);
void func_80086BB4(HSD_GObj*);
u8 func_80086BE0(HSD_GObj*);
void func_80086BEC(HSD_GObj*, Vec3*);
s32 func_80086C0C(HSD_GObj*);
void func_80086C18(HSD_GObj*, s32, s32);
void func_80086C9C(s32, s32);
void func_80086D40(HSD_GObj*, s32, s32);
void func_80086DC4(s32, s32);
void func_80086E68(HSD_GObj*);
s32 func_80086EB4(HSD_GObj*);
bool func_80086EC0(HSD_GObj*);
bool func_80086ED0(HSD_GObj*);
bool func_80086F4C(HSD_GObj*);
f32 func_80086F80(HSD_GObj*);
bool func_80086FA8(HSD_GObj*);
bool func_80086FD4(HSD_GObj*, HSD_GObj*);
bool func_8008701C(HSD_GObj*);
void func_8008702C(s32);
void func_80087050(s32);
bool func_80087074(HSD_GObj*, Vec3*);
bool func_800870BC(HSD_GObj*, void**);
void func_800870F0(HSD_GObj*, s32);
s32 func_80087120(HSD_GObj*);
void func_80087140(HSD_GObj*);
void func_800871A8(HSD_GObj*, HSD_GObj*);
bool func_80087284(HSD_GObj*);
FighterKind func_800872A4(HSD_GObj*);
void* func_800872B0(HSD_GObj*);
bool func_800872BC(HSD_GObj*);
s32 func_80087300(HSD_GObj*);
s32 func_8008730C(HSD_GObj*);
s32 func_8008731C(HSD_GObj*);
bool func_8008732C(HSD_GObj*);
bool func_80087354(HSD_GObj*);
bool func_8008737C(HSD_GObj*);
bool func_800873A4(HSD_GObj*);
bool func_800873CC(HSD_GObj*);
bool func_800873F4(HSD_GObj*);
HSD_GObj* func_8008741C(u32);
f32 func_80087454(HSD_GObj*);
u32 func_80087460(HSD_GObj*);
s32 func_8008746C(HSD_GObj*);
s32 func_800874BC(HSD_GObj*);
void func_800874CC(HSD_GObj*, s32, s32);
void func_80087508(s8, u8);
void func_80087574(s8);
void func_80087610(u8);
void func_800876B4(HSD_GObj*);
bool func_800876D4(HSD_GObj*);
s32 func_800876F4(HSD_GObj*);
s32 func_80087700(HSD_GObj*);
void func_8008770C(HSD_GObj*, void* dst);
void func_80087744(HSD_GObj*, void* dst);
void func_8008777C(HSD_GObj*);
bool func_800877D4(HSD_GObj*);

#endif
