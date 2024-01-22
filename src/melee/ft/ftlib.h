#ifndef _ftlib_h_
#define _ftlib_h_

#include "ft/fighter.h"

#include <baselib/gobj.h>

s32 ftLib_800860C4(void);
bool ftLib_800860E8(void);
bool ftLib_80086140(void);
HSD_GObj* ftLib_80086198(HSD_GObj*);
HSD_GObj* ftLib_8008627C(Vec3* pos, HSD_GObj*);
HSD_GObj* ftLib_80086368(Vec3*, HSD_GObj*, f32);
f32 ftLib_800864A8(Vec3*, HSD_GObj*);
f32 ftLib_800865C0(HSD_GObj*);
s32 ftLib_800865CC(HSD_GObj*);
void ftLib_800865D8(HSD_GObj*, f32*, f32*);
void* ftLib_800865F0(HSD_GObj*);
void* ftLib_80086630(Fighter_GObj*, Fighter_Part part);
void ftLib_80086644(HSD_GObj*, Vec3*);
void ftLib_80086664(HSD_GObj*, Vec3*);
void ftLib_80086684(HSD_GObj*, Vec3*);
void ftLib_SetScale(HSD_GObj*, f32);
void ftLib_800866DC(HSD_GObj*, Vec3*);
void ftLib_80086724(HSD_GObj*, HSD_GObj*);
void ftLib_80086764(HSD_GObj*);
HSD_GObj* ftLib_80086794(HSD_GObj*);
bool ftLib_800867A0(HSD_GObj*, HSD_GObj*);
HSD_GObj* ftLib_800867CC(HSD_GObj*);
bool ftLib_800867D8(HSD_GObj*);
void ftLib_800867E8(HSD_GObj*);
void ftLib_80086824(void);
void ftLib_8008688C(HSD_GObj*);
void ftLib_800868A4(void);
bool ftLib_800868D4(HSD_GObj*, HSD_GObj*);

/// @returns @c true if @p gobj is a #Fighter, otherwise @c false.
bool ftLib_80086960(HSD_GObj* gobj);

CollData* ftLib_80086984(HSD_GObj*);
void ftLib_80086990(HSD_GObj*, Vec3*);
f32 ftLib_800869D4(HSD_GObj*);
f32 ftLib_800869F8(HSD_GObj*);
f32 ftLib_80086A0C(HSD_GObj*);
bool ftLib_80086A18(HSD_GObj*);
void ftLib_80086A4C(HSD_GObj*, f32);
bool ftLib_80086A58(HSD_GObj*, S32Vec2*);
bool ftLib_80086A8C(HSD_GObj*);
bool ftLib_80086B64(HSD_GObj*);
CameraBox* ftLib_80086B74(HSD_GObj*);
f32 ftLib_80086B80(HSD_GObj*);
void ftLib_80086B90(HSD_GObj*, Vec3* v);
void ftLib_80086BB4(HSD_GObj*);
u8 ftLib_80086BE0(HSD_GObj*);
void ftLib_80086BEC(HSD_GObj*, Vec3*);

/// @returns A fighter action state ID.
enum_t ftLib_80086C0C(HSD_GObj*);

void ftLib_80086C18(HSD_GObj*, s32, s32);
void ftLib_80086C9C(s32, s32);
void ftLib_80086D40(HSD_GObj*, s32, s32);
void ftLib_80086DC4(s32, s32);
void ftLib_80086E68(HSD_GObj*);
s32 ftLib_80086EB4(HSD_GObj*);
bool ftLib_80086EC0(HSD_GObj*);
bool ftLib_80086ED0(HSD_GObj*);
bool ftLib_80086F4C(HSD_GObj*);
f32 ftLib_80086F80(HSD_GObj*);
bool ftLib_80086FA8(HSD_GObj*);
bool ftLib_80086FD4(HSD_GObj*, HSD_GObj*);
bool ftLib_8008701C(HSD_GObj*);
void ftLib_8008702C(s32);
void ftLib_80087050(s32);
bool ftLib_80087074(HSD_GObj*, Vec3*);
bool ftLib_800870BC(HSD_GObj*, void**);
void ftLib_800870F0(HSD_GObj*, s32);
s32 ftLib_80087120(HSD_GObj*);
void ftLib_80087140(HSD_GObj*);
void ftLib_800871A8(HSD_GObj*, HSD_GObj*);
bool ftLib_80087284(HSD_GObj*);
FighterKind ftLib_800872A4(HSD_GObj*);
void* ftLib_800872B0(HSD_GObj*);
bool ftLib_800872BC(HSD_GObj*);
s32 ftLib_80087300(HSD_GObj*);
s32 ftLib_8008730C(HSD_GObj*);
s32 ftLib_8008731C(HSD_GObj*);
bool ftLib_8008732C(HSD_GObj*);
bool ftLib_80087354(HSD_GObj*);
bool ftLib_8008737C(HSD_GObj*);
bool ftLib_800873A4(HSD_GObj*);
bool ftLib_800873CC(HSD_GObj*);
bool ftLib_800873F4(HSD_GObj*);
HSD_GObj* ftLib_8008741C(u32);
f32 ftLib_80087454(HSD_GObj*);
u32 ftLib_80087460(HSD_GObj*);
s32 ftLib_8008746C(HSD_GObj*);
s32 ftLib_800874BC(HSD_GObj*);
void ftLib_800874CC(HSD_GObj*, s32, s32);
void ftLib_80087508(s8, u8);
void ftLib_80087574(s8);
void ftLib_80087610(u8);
void ftLib_800876B4(HSD_GObj*);
bool ftLib_800876D4(HSD_GObj*);
s32 ftLib_800876F4(HSD_GObj*);
s32 ftLib_80087700(HSD_GObj*);
void ftLib_8008770C(HSD_GObj*, void* dst);
void ftLib_80087744(HSD_GObj*, void* dst);
void ftLib_8008777C(HSD_GObj*);
bool ftLib_800877D4(HSD_GObj*);

#endif
