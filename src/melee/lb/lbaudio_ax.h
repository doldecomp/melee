#ifndef MELEE_LB_LBAUDIO_AX_H
#define MELEE_LB_LBAUDIO_AX_H

#include <platform.h>

#include <baselib/gobj.h>

/// @todo Create an @c enum for SFX IDs.
#define SFX_NONE -1

void lbAudioAx_800236B8(s32);
u32 lbAudioAx_800237A8(enum_t sfx_id, u8 sfx_vol, u8 sfx_pan);
void lbAudioAx_80023F28(s32);
void lbAudioAx_8002438C(s32);
void lbAudioAx_80024B1C(s32, s32);
void lbAudioAx_80024B58(s32, s32);
s32 lbAudioAx_80023220(s32);
s32 lbAudioAx_800230C8(s32, int*, int*);
s32 lbAudioAx_80023130(void);
s32 lbAudioAx_800233EC(s32);
void lbAudioAx_80024DC4(void);
void lbAudioAx_80024FDC(void);
void lbAudioAx_80024FF4(void);
void lbAudioAx_8002500C(s32);
void lbAudioAx_80025038(s32);
void lbAudioAx_8002838C(void);
bool lbAudioAx_80023710(s32);
void lbAudioAx_80023870(unk_t, s32, s32, s32);
s32 lbAudioAx_8002305C(s32, s32);
void lbAudioAx_80026510(HSD_GObj*);
enum_t lbAudioAx_800265C4(HSD_GObj*, enum_t sfx);
int lbAudioAx_80024184(int, int, int, int);
void lbAudioAx_80024B94(int, int);
/* 0264E4 */ bool lbAudioAx_800264E4(void);
/* 0263E8 */ void lbAudioAx_800263E8(HSD_GObj*, int, int, int, float);

#endif
