#ifndef MELEE_LB_LBAUDIO_AX_H
#define MELEE_LB_LBAUDIO_AX_H

#include <platform.h>
#include <baselib/forward.h>

#include <baselib/gobj.h>

/// @todo Create an @c enum for SFX IDs.
#define SFX_NONE -1

/* 02305C */ s32 lbAudioAx_8002305C(s32, s32);
/* 0230C8 */ s32 lbAudioAx_800230C8(s32, int*, int*);
/* 023130 */ s32 lbAudioAx_80023130(void);
/* 023220 */ s32 lbAudioAx_80023220(s32);
/* 0233EC */ s32 lbAudioAx_800233EC(s32);
/* 0236B8 */ void lbAudioAx_800236B8(s32);
/* 023710 */ bool lbAudioAx_80023710(s32);
/* 0237A8 */ u32 lbAudioAx_800237A8(enum_t sfx_id, u8 sfx_vol, u8 sfx_pan);
/* 023870 */ int lbAudioAx_80023870(int, int, int, int);
/* 023F28 */ void lbAudioAx_80023F28(s32);
/* 024030 */ void lbAudioAx_80024030(s32);
/* 024184 */ int lbAudioAx_80024184(int, int, int, int);
/* 02438C */ void lbAudioAx_8002438C(s32);
/* 024B1C */ void lbAudioAx_80024B1C(s32, s32);
/* 024B58 */ void lbAudioAx_80024B58(s32, s32);
/* 024B94 */ void lbAudioAx_80024B94(int, int);
/* 024DC4 */ void lbAudioAx_80024DC4(void);
/* 024FDC */ void lbAudioAx_80024FDC(void);
/* 024FF4 */ void lbAudioAx_80024FF4(void);
/* 02500C */ void lbAudioAx_8002500C(s32);
/* 025038 */ void lbAudioAx_80025038(s32);
/* 0263E8 */ void lbAudioAx_800263E8(HSD_GObj*, int, int, int, float);
/* 0264E4 */ bool lbAudioAx_800264E4(void);
/* 026510 */ void lbAudioAx_80026510(HSD_GObj*);
/* 0265C4 */ enum_t lbAudioAx_800265C4(HSD_GObj*, enum_t sfx);
/* 027DBC */ void lbAudioAx_80027DBC(void);
/* 02838C */ void lbAudioAx_8002838C(void);
/* 026F2C */ void lbAudioAx_80026F2C(s32);

#endif
