#ifndef MELEE_EF_EFLIB_H
#define MELEE_EF_EFLIB_H

#include "ef/forward.h"
#include <baselib/forward.h>

#include <dolphin/mtx.h>

typedef struct EF_ParamEntry {
    /* 0x0 */ void* gobj;
    /* 0x4 */ u16 gfx_id;
    /* 0x6 */ u16 alpha;
} EF_ParamEntry; /* size = 0x8 */
STATIC_ASSERT(sizeof(EF_ParamEntry) == 0x8);

/* 05B4B8 */ void efLib_Init(void);
/* 05B704 */ void efLib_SetFlags(HSD_GObj* gobj, s32 expires);
/* 05B780 */ void efLib_Destroy(HSD_GObj* gobj);
/* 05B880 */ void efLib_DestroyAll(HSD_GObj* gobj);
/* 05BA40 */ void efLib_PauseAll(HSD_GObj* gobj);
/* 05BAC4 */ void efLib_ResumeAll(HSD_GObj* gobj);
/* 05BB40 */ void efLib_remove_user_data(void* user_data);
/* 05BBB4 */ void efLib_RemoveLast(void);
/* 05BC50 */ void efLib_Update(HSD_GObj* gobj);

// Create effects

/* 05BE88 */ EF_Effect* efLib_Create(int gfx_id, HSD_GObj* parent_gobj);
/* 05C1B4 */ EF_Effect* efLib_Create_Attach(u32 gfx_id, HSD_GObj* gobj,
                                            HSD_JObj* jobj);
/* 05C2BC */ EF_Effect* efLib_Create_AttachChild(u32 gfx_id, HSD_GObj* gobj,
                                                 HSD_JObj* jobj);
/* 05C3DC */ EF_Effect* efLib_Create_Attach_Scale(u32 gfx_id, HSD_GObj* gobj,
                                                  HSD_JObj* jobj);
/* 05C5C4 */ EF_Effect*
efLib_Create_AttachChild_Scale(u32 gfx_id, HSD_GObj* gobj, HSD_JObj* jobj);
/* 05C6F4 */ EF_Effect* efLib_Create_Attach_Scale_FacingDir(u32 gfx_id,
                                                            HSD_GObj* gobj,
                                                            HSD_JObj* jobj);
/* 05C814 */ EF_Effect* efLib_Create_Attach_Pos(u32 gfx_id, HSD_GObj* gobj,
                                          Vec3* position);

// Particle processing callbacks

/* 05C9A4 */ void efLib_particles_proc_main(HSD_GObj* gobj);
/* 05C9D0 */ void efLib_particles_proc_aux(HSD_GObj* gobj);

// Create generators

/* 05C9FC */ HSD_Generator* efLib_CreateGenerator(s32 gfx_id, Vec3* pos);
/* 05CAB0 */ HSD_Generator* efLib_CreateGenerator_AddAppSRT(s32 gfx_id);
/* 05CB34 */ HSD_Generator*
efLib_CreateGenerator_Translate_FacingDir(s32 gfx_id, Vec3* translation,
                                          f32 direction);
/* 05CC2C */ HSD_Generator* efLib_CreateGenerator_Attach(s32 gfx_id,
                                                         HSD_JObj* jobj);
/* 05CC84 */ HSD_Generator*
efLib_CreateGenerator_Attach_AddAppSRT(s32 gfx_id, HSD_JObj* jobj);
/* 05CD2C */ HSD_Generator*
efLib_CreateGenerator_Attach_Scale(s32 gfx_id, va_list vlist, HSD_GObj* gobj);
/* 05CE48 */ HSD_Generator*
efLib_CreateGenerator_AppSRT_SetScale(s32 gfx_id, va_list vlist);
/* 05CF40 */ HSD_Generator*
efLib_CreateGenerator_AppSRT_SetFacingDir(s32 gfx_id, va_list vlist);
/* 05D044 */ HSD_Generator*
efLib_CreateGenerator_AppSRT_SetFacingDirScale(s32 gfx_id, va_list vlist);

// Called by particles library

/* 05D174 */ void efLib_SpawnParticleEffect(int bank, s32 gfx_id,
                                            HSD_JObj* jobj, bool flag);

// Particle-related callbacks

/* 05DB20 */ void efLib_Cb_SPtcl(s32 linkNo, s32 bank, s32 gfx_id,
                                 HSD_JObj* jobj);
/* 05DB70 */ void efLib_Cb_DPtcl(int linkNo, int bank, int gfx_id,
                                 HSD_JObj* jobj);
/* 05DBC0 */ void efLib_Cb_ParticleRender(HSD_Particle* particle);
/* 05DCD0 */ void efLib_Cb_PtclAppSRTHook(HSD_Particle* particle);

// Effect callbacks

/* 05DDB8 */ void efLib_Cb_SetOffsetY_FromParamY(EF_Effect* effect);
/* 05DE94 */ void efLib_Cb_SetScale_FromParamX(EF_Effect* effect);
/* 05E090 */ void efLib_Cb_SetRotYAndTransition(EF_Effect* effect);
/* 05E1D8 */ void efLib_Cb_SetJObjOffsetZ(EF_Effect* effect);
/* 05E2B4 */ void efLib_Cb_SetRotY_FromFighterDir(EF_Effect* effect);
/* 05E3A0 */ void efLib_Cb_SetRotYZ_FromFighter(EF_Effect* effect);
/* 05E648 */ void efLib_Cb_Fall_FromParamY(EF_Effect* effect);
/* 05E950 */ void efLib_Cb_SetOffset_FromParams(EF_Effect* effect);
/* 05EB70 */ void efLib_Cb_LifetimeEndSpawn(EF_Effect* effect);
/* 05EBC8 */ void efLib_Cb_SetScaleRotY_FromFighter(EF_Effect* effect);
/* 05EDDC */ void efLib_Cb_SetRotYZ_FromParamZ_FighterDir(EF_Effect* effect);
/* 05F08C */ void efLib_Cb_ftMr_SpecialLw(EF_Effect* effect);
/* 05F270 */ void efLib_Cb_ftLg_SpecialLw(EF_Effect* effect);
/* 05F454 */ void efLib_Cb_ftKp_SpecialHi(EF_Effect* effect);
/* 05F748 */ void efLib_Cb_ftCo_Bury(EF_Effect* effect);

// Property setting

/* 05F774 */ void efLib_SetTevKonstColor(HSD_JObj* jobj, s32 count, u32 konst,
                                         u32 tev0);
/* 05F864 */ void efLib_SetParamAlpha(HSD_GObj* gobj, u8 alpha, f32 unused1,
                                      f32 unused2);
/* 05F990 */ void efLib_SetParamGfxId(HSD_GObj* gobj, s32 gfx_id);

// More effect callbacks (?)

/* 05FAB8 */ void efLib_Cb_ApplyStoredAlpha(EF_Effect* effect);
/* 05FBE4 */ void efLib_Cb_AccumOffset_FromParams(EF_Effect* effect);

// Misplaced generator creation

/* 05FCD8 */ EF_Effect* efLib_CreateGenerator_AppSRT_SetPos(int gfx_id,
                                                            HSD_GObj* gobj,
                                                            HSD_JObj* jobj,
                                                            Vec3* vec);

extern EF_ParamEntry efLib_AnimQueue[0x10];
extern EF_ParamEntry efLib_ParamTable[0x8];

#endif
