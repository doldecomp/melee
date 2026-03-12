#ifndef MELEE_EF_EFLIB_H
#define MELEE_EF_EFLIB_H

#include "ef/forward.h"
#include <baselib/forward.h>

#include <dolphin/mtx.h>

typedef struct _struct_efLib_80458EE0 {
    /* 0x0 */ void* x0_gobj;
    /* 0x4 */ u16 x4_unk;
    /* 0x6 */ u16 x6_unk;
} _struct_efLib_80458EE0; /* size = 0x8 */
STATIC_ASSERT(sizeof(_struct_efLib_80458EE0) == 0x8);

/* 05B4B8 */ void efLib_8005B4B8(void);
/* 05B704 */ void efLib_8005B704(HSD_GObj*, s32);
/* 05B780 */ void efLib_8005B780(HSD_GObj*);
/* 05B880 */ void efLib_DestroyAll(HSD_GObj* gobj);
/* 05BA40 */ void efLib_PauseAll(HSD_GObj* gobj);
/* 05BAC4 */ void efLib_ResumeAll(HSD_GObj* gobj);
/* 05BB40 */ void efLib_RemoveUserData(void* user_data);
/* 05BBB4 */ void efLib_8005BBB4();
/* 05BC50 */ void fn_8005BC50(HSD_GObj* gobj);
/* 05BE88 */ Effect* efLib_8005BE88(int, HSD_GObj* parent_gobj);
/* 05C1B4 */ Effect* efLib_8005C1B4(u32 arg0, HSD_GObj* arg_gobj,
                                    HSD_JObj* arg_jobj);
/* 05C2BC */ Effect* efLib_8005C2BC(u32 arg0, HSD_GObj* arg_gobj,
                                    HSD_JObj* arg_jobj);
/* 05C3DC */ Effect* efLib_8005C3DC(u32, HSD_GObj*, HSD_JObj*);
/* 05C5C4 */ Effect* efLib_8005C5C4(u32, HSD_GObj*, HSD_JObj*);
/* 05C6F4 */ Effect* efLib_8005C6F4(u32, HSD_GObj*, HSD_JObj*);
/* 05C814 */ Effect* efLib_8005C814(u32 arg0, HSD_GObj* arg_gobj,
                                    Vec3* arg_vec3);
/* 05C9A4 */ void efLib_8005C9A4(HSD_GObj*);
/* 05C9D0 */ void fn_8005C9D0(HSD_GObj*);
/// /* 05C9FC */ Effect* efLib_8005C9FC();
/* 05C9FC */ HSD_Generator* efLib_8005C9FC(s32, Vec3*);
/// /* 05C9FC */ Effect* efLib_8005C9FC(u32, Vec3*, f32, Vec3*, ...);
/* 05CAB0 */ HSD_Generator* efLib_8005CAB0(s32);
/* 05CB34 */ HSD_Generator* efLib_8005CB34(s32 arg0, Vec3* arg_vec3, f32 arg2);
/* 05CC2C */ HSD_Generator* efLib_8005CC2C(s32, HSD_JObj*);
/// /* 05CC84 */ HSD_Generator* efLib_8005CC84(u32,  HSD_JObj*, ...);
/* 05CC84 */ HSD_Generator* efLib_8005CC84(s32, HSD_JObj*);
/* 05CD2C */ HSD_Generator* efLib_8005CD2C(s32, va_list, HSD_GObj*);
/* 05CE48 */ HSD_Generator* efLib_8005CE48(s32, va_list);
/* 05CF40 */ HSD_Generator* efLib_8005CF40(s32, va_list);
/* 05D044 */ HSD_Generator* efLib_8005D044(s32, va_list);
/* 05D174 */ void efLib_8005D174(int, s32, HSD_JObj*, bool);
/* 05DB20 */ void fn_8005DB20(s32, s32, s32, HSD_JObj*);
/* 05DB70 */ void fn_8005DB70(int arg0, int lo, int hi, HSD_JObj* jobj);
/* 05DBC0 */ void efLib_8005DBC0(HSD_Particle*);
/* 05DCD0 */ void fn_8005DCD0(HSD_Particle* particle);
/* 05DDB8 */ void efLib_8005DDB8(Effect*);
/* 05DE94 */ void efLib_8005DE94(Effect*);
/* 05E090 */ void efLib_8005E090(Effect* effect);
/* 05E1D8 */ void efLib_8005E1D8(Effect*);
/* 05E2B4 */ void efLib_8005E2B4(Effect* effect);
/* 05E3A0 */ void efLib_8005E3A0(Effect*);
/* 05E648 */ void efLib_8005E648(Effect*);
/* 05E950 */ void efLib_8005E950(Effect*);
/* 05EB70 */ void efLib_8005EB70(Effect*);
/* 05EBC8 */ void efLib_8005EBC8(Effect*);
/* 05EDDC */ void efLib_8005EDDC(Effect*);
/* 05F08C */ void efLib_8005F08C(Effect*);
/* 05F270 */ void efLib_8005F270(Effect*);
/* 05F454 */ void efLib_8005F454(Effect* arg_effect);
/* 05F748 */ void efLib_8005F748(Effect*);
/* 05F774 */ void efLib_8005F774(HSD_JObj* arg_jobj, s32 arg1, u32 arg2, u32 arg3);
/* 05F864 */ void efLib_8005F864(HSD_GObj* gobj, u8 arg1, f32 arg2, f32 arg3);
/* 05F990 */ void efLib_8005F990(HSD_GObj* gobj, u16 arg1);
/* 05FAB8 */ void efLib_8005FAB8(Effect* effect);
/* 05FBE4 */ void fn_8005FBE4(Effect* effect);
/* 05FCD8 */ Effect* efLib_8005FCD8(int arg0, HSD_GObj* gobj, HSD_JObj* jobj, Vec3* vec);

extern _struct_efLib_80458EE0 efLib_80458EE0[0x10];
extern _struct_efLib_80458EE0 efLib_80458F60[0x8];

#endif
