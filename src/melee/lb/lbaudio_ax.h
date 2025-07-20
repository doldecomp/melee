#ifndef GALE01_02305C
#define GALE01_02305C

#include <platform.h>

#include <baselib/forward.h>

#include <baselib/gobj.h>

/// @todo Create an @c enum for SFX IDs.
#define SFX_NONE -1

/* 02305C */ s32 lbAudioAx_8002305C(s32, s32);
/* 023090 */ UNK_RET lbAudioAx_80023090(UNK_PARAMS);
/* 0230C8 */ s32 lbAudioAx_800230C8(s32, int*, int*);
/* 023130 */ s32 lbAudioAx_80023130(void);
/* 023220 */ s32 lbAudioAx_80023220(s32);
/* 023254 */ UNK_RET fn_80023254(UNK_PARAMS);
/* 0233EC */ s32 lbAudioAx_800233EC(s32);
/* 023694 */ s32 lbAudioAx_80023694(void);
/* 0236B8 */ int lbAudioAx_800236B8(int);
/* 0236DC */ void lbAudioAx_800236DC(void);
/* 023710 */ bool lbAudioAx_80023710(s32);
/* 023730 */ UNK_RET lbAudioAx_80023730(UNK_PARAMS);
/* 023750 */ UNK_RET fn_80023750(UNK_PARAMS);
/* 0237A8 */ u32 lbAudioAx_800237A8(enum_t sfx_id, u8 sfx_vol, u8 sfx_pan);
/* 023870 */ int lbAudioAx_80023870(int, int, int, int);
/* 02392C */ UNK_RET lbAudioAx_8002392C(UNK_PARAMS);
/* 023968 */ s32 lbAudioAx_80023968(s32);
/* 023A44 */ s32 lbAudioAx_80023A44(u8, u16);
/* 023B24 */ f32 lbAudioAx_80023B24(s32);
/* 023ED4 */ UNK_RET fn_80023ED4(UNK_PARAMS);
/* 023F28 */ void lbAudioAx_80023F28(s32);
/* 024030 */ void lbAudioAx_80024030(s32);
/* 0240B4 */ UNK_RET lbAudioAx_800240B4(UNK_PARAMS);
/* 02411C */ UNK_RET lbAudioAx_8002411C(UNK_PARAMS);
/* 024184 */ int lbAudioAx_80024184(int, int, int, int);
/* 024304 */ UNK_RET lbAudioAx_80024304(UNK_PARAMS);
/* 02438C */ void lbAudioAx_8002438C(s32);
/* 0243F4 */ UNK_RET lbAudioAx_800243F4(UNK_PARAMS);
/* 0244F4 */ UNK_RET fn_800244F4(UNK_PARAMS);
/* 0245D4 */ void lbAudioAx_800245D4(u8);
/* 0245F4 */ s32 lbAudioAx_800245F4(u8); /// i dont believe this actually returns anything
/* 024614 */ void lbAudioAx_80024614(u8);
/* 024634 */ void lbAudioAx_80024634(u8);
/* 024654 */ UNK_RET fn_80024654(UNK_PARAMS);
/* 024B1C */ void lbAudioAx_80024B1C(s32, s32);
/* 024B58 */ void lbAudioAx_80024B58(s32, s32);
/* 024B94 */ int lbAudioAx_80024B94(int arg0, int arg1);
/* 024BD0 */ int lbAudioAx_80024BD0(void);
/* 024C08 */ void lbAudioAx_80024C08(int);
/* 024C84 */ UNK_RET lbAudioAx_80024C84(UNK_PARAMS);
/* 024D50 */ UNK_RET lbAudioAx_80024D50(UNK_PARAMS);
/* 024D78 */ UNK_RET lbAudioAx_80024D78(UNK_PARAMS);
/* 024DC4 */ void lbAudioAx_80024DC4(s32);
/* 024E50 */ void lbAudioAx_80024E50(s32);
/* 024E84 */ void lbAudioAx_80024E84(int);
/* 024F08 */ UNK_RET lbAudioAx_80024F08(UNK_PARAMS);
/* 024F6C */ UNK_RET lbAudioAx_80024F6C(UNK_PARAMS);
/* 024FDC */ void lbAudioAx_80024FDC(void);
/* 024FF4 */ void lbAudioAx_80024FF4(void);
/* 02500C */ void lbAudioAx_8002500C(s32);
/* 025038 */ void lbAudioAx_80025038(s32);
/* 025064 */ void lbAudioAx_80025064(int, int);
/* 025098 */ void lbAudioAx_80025098(s32 arg0);
/* 0250A0 */ UNK_RET fn_800250A0(UNK_PARAMS);
/* 0251EC */ UNK_RET fn_800251EC(UNK_PARAMS);
/* 0253D8 */ UNK_RET fn_800253D8(UNK_PARAMS);
/* 0256BC */ UNK_RET fn_800256BC(UNK_PARAMS);
/* 0259A0 */ UNK_RET fn_800259A0(UNK_PARAMS);
/* 0259EC */ UNK_RET fn_800259EC(UNK_PARAMS);
/* 025A98 */ UNK_RET fn_80025A98(UNK_PARAMS);
/* 025B44 */ UNK_RET fn_80025B44(UNK_PARAMS);
/* 025CBC */ UNK_RET fn_80025CBC(UNK_PARAMS);
/* 025E38 */ UNK_RET fn_80025E38(UNK_PARAMS);
/* 025FAC */ UNK_RET fn_80025FAC(UNK_PARAMS);
/* 0262A0 */ UNK_RET fn_800262A0(UNK_PARAMS);
/* 0263B4 */ UNK_RET fn_800263B4(UNK_PARAMS);
/* 0263E8 */ void lbAudioAx_800263E8(HSD_GObj*, int, int, int, float);
/* 0264E4 */ bool lbAudioAx_800264E4(void);
/* 026510 */ void lbAudioAx_80026510(HSD_GObj*);
/* 0265C4 */ enum_t lbAudioAx_800265C4(HSD_GObj*, enum_t sfx);
/* 026650 */ UNK_RET fn_80026650(UNK_PARAMS);
/* 0267B0 */ UNK_RET fn_800267B0(UNK_PARAMS);
/* 0268B4 */ UNK_RET fn_800268B4(UNK_PARAMS);
/* 0269AC */ UNK_RET fn_800269AC(UNK_PARAMS);
/* 026C04 */ UNK_RET fn_80026C04(UNK_PARAMS);
/* 026E58 */ UNK_RET fn_80026E58(UNK_PARAMS);
/* 026E84 */ u64 lbAudioAx_80026E84(int);
/* 026EBC */ u64 lbAudioAx_80026EBC(u32);
/* 026F2C */ u64 lbAudioAx_80026F2C(s32);
/* 02702C */ void lbAudioAx_8002702C(s32, u64);
/* 027168 */ void lbAudioAx_80027168(void);
/* 027488 */ UNK_RET fn_80027488(UNK_PARAMS);
/* 027648 */ void lbAudioAx_80027648(void);
/* 02785C */ UNK_RET lbAudioAx_8002785C(UNK_PARAMS);
/* 027AB0 */ void lbAudioAx_80027AB0(int);
/* 027DBC */ void lbAudioAx_80027DBC(void);
/* 027DF8 */ UNK_RET lbAudioAx_80027DF8(UNK_PARAMS);
/* 02835C */ UNK_RET lbAudioAx_8002835C(UNK_PARAMS);
/* 02838C */ void lbAudioAx_8002838C(void);
/* 028690 */ UNK_RET lbAudioAx_80028690(UNK_PARAMS);
/* 028B2C */ int lbAudioAx_80028B2C(void);
/* 028B4C */ int lbAudioAx_80028B4C(void);
/* 028B6C */ UNK_RET lbAudioAx_80028B6C(UNK_PARAMS);
/* 028B90 */ UNK_RET lbAudioAx_80028B90(UNK_PARAMS);

#endif
