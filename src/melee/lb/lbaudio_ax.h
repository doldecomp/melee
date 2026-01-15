#ifndef GALE01_02305C
#define GALE01_02305C

#include <platform.h>

#include <baselib/forward.h>
#include <melee/ft/forward.h>
#include <melee/gr/forward.h>

#include <baselib/gobj.h>

/// @todo Create an @c enum for SFX IDs.
#define SFX_NONE -1

/* 02305C */ int lbAudioAx_8002305C(int, int);
/* 023090 */ int lbAudioAx_80023090(int);
/* 0230C8 */ int lbAudioAx_800230C8(int, int*, int*);
/* 023130 */ int lbAudioAx_80023130(int);
/* 023220 */ int lbAudioAx_80023220(int);
/* 023254 */ void fn_80023254(s32 arg0);
/* 0233EC */ s32 lbAudioAx_800233EC(s32);
/* 023694 */ int lbAudioAx_80023694(void);
/* 0236B8 */ int lbAudioAx_800236B8(int);
/* 0236DC */ int lbAudioAx_800236DC(void);
/* 023710 */ bool lbAudioAx_80023710(int);
/* 023730 */ bool lbAudioAx_80023730(void);
/* 023750 */ int fn_80023750(int, int, int, int, int);
/* 0237A8 */ int lbAudioAx_800237A8(enum_t sfx_id, int sfx_vol, int sfx_pan);
/* 023870 */ int lbAudioAx_80023870(int, int, int, int);
/* 02392C */ void lbAudioAx_8002392C(void);
/* 023968 */ int lbAudioAx_80023968(int);
/* 023A44 */ int lbAudioAx_80023A44(int, int);
/* 023B24 */ f32 lbAudioAx_80023B24(s32);
/* 023ED4 */ bool fn_80023ED4(const char* arg0, int arg1, int arg2);
/* 023F28 */ bool lbAudioAx_80023F28(s32);
/* 024030 */ void lbAudioAx_80024030(s32);
/* 0240B4 */ int lbAudioAx_800240B4(int);
/* 02411C */ int lbAudioAx_8002411C(int);
/* 024184 */ int lbAudioAx_80024184(int, int, int, int);
/* 024304 */ int lbAudioAx_80024304(int);
/* 02438C */ int lbAudioAx_8002438C(int);
/* 0243F4 */ UNK_RET lbAudioAx_800243F4(int);
/* 0244F4 */ UNK_RET fn_800244F4(UNK_PARAMS);
/* 0245D4 */ void lbAudioAx_800245D4(int);
/* 0245F4 */ int lbAudioAx_800245F4(int);
/* 024614 */ void lbAudioAx_80024614(int);
/* 024634 */ void lbAudioAx_80024634(int);
/* 024654 */ void fn_80024654(int);
/* 024B1C */ void lbAudioAx_80024B1C(int, int);
/* 024B58 */ void lbAudioAx_80024B58(int, int);
/* 024B94 */ int lbAudioAx_80024B94(int arg0, int arg1);
/* 024BD0 */ bool lbAudioAx_80024BD0(void);
/* 024C08 */ int lbAudioAx_80024C08(int);
/* 024C84 */ void lbAudioAx_80024C84(void);
/* 024D50 */ void lbAudioAx_80024D50(void);
/* 024D78 */ void lbAudioAx_80024D78(int);
/* 024DC4 */ void lbAudioAx_80024DC4(int);
/* 024E50 */ void lbAudioAx_80024E50(bool);
/* 024E84 */ void lbAudioAx_80024E84(bool);
/* 024F08 */ void lbAudioAx_80024F08(void);
/* 024F6C */ void lbAudioAx_80024F6C(void);
/* 024FDC */ void lbAudioAx_80024FDC(void);
/* 024FF4 */ void lbAudioAx_80024FF4(void);
/* 02500C */ void lbAudioAx_8002500C(int);
/* 025038 */ void lbAudioAx_80025038(int);
/* 025064 */ void lbAudioAx_80025064(bool, bool);
/* 025098 */ void lbAudioAx_80025098(s32 arg0);
/* 0250A0 */ int fn_800250A0(int, int, int, int);
/* 0251EC */ bool fn_800251EC(HSD_GObj* gobj);
/* 0253D8 */ bool fn_800253D8(HSD_GObj* gobj);
/* 0256BC */ bool fn_800256BC(HSD_GObj* gobj);
/* 0259A0 */ bool fn_800259A0(HSD_GObj* gobj);
/* 0259EC */ bool fn_800259EC(HSD_GObj* gobj);
/* 025A98 */ bool fn_80025A98(HSD_GObj* gobj);
/* 025B44 */ bool fn_80025B44(HSD_GObj* gobj);
/* 025CBC */ bool fn_80025CBC(HSD_GObj* gobj);
/* 025E38 */ bool fn_80025E38(HSD_GObj* gobj);
/* 025FAC */ void fn_80025FAC(HSD_GObj* gobj, void* userdata, void* params);
/* 0262A0 */ void fn_800262A0(HSD_GObj* gobj);
/* 0263B4 */ void lbAudioAx_ObjFree(void* obj);
/* 0263E8 */ HSD_GObj* lbAudioAx_800263E8(float, HSD_GObj*, int, int, int, int,
                                          int, int, int, int, int);
/* 0264E4 */ bool lbAudioAx_800264E4(void* data);
/* 026510 */ bool lbAudioAx_80026510(HSD_GObj*);
/* 0265C4 */ bool lbAudioAx_800265C4(HSD_GObj*, int sfx);
/* 026650 */ UNK_RET fn_80026650(UNK_PARAMS);
/* 0267B0 */ void fn_800267B0(void);
/* 0268B4 */ void fn_800268B4(void);
/* 0269AC */ UNK_RET fn_800269AC(UNK_PARAMS);
/* 026C04 */ UNK_RET fn_80026C04(UNK_PARAMS);
/* 026E58 */ bool fn_80026E58(int);
/* 026E84 */ u64 lbAudioAx_80026E84(CharacterKind);
/* 026EBC */ u64 lbAudioAx_80026EBC(InternalStageId);
/* 026F2C */ u64 lbAudioAx_80026F2C(s32);
/* 02702C */ void lbAudioAx_8002702C(s32, u64);
/* 027168 */ void lbAudioAx_80027168(void);
/* 027488 */ UNK_RET fn_80027488(UNK_PARAMS);
/* 027648 */ void lbAudioAx_80027648(void);
/* 02785C */ UNK_RET lbAudioAx_8002785C(UNK_PARAMS);
/* 027AB0 */ void lbAudioAx_80027AB0(int);
/* 027DBC */ void lbAudioAx_80027DBC(void);
/* 027DF8 */ UNK_RET lbAudioAx_80027DF8(UNK_PARAMS);
/* 02835C */ void lbAudioAx_8002835C(void);
/* 02838C */ void lbAudioAx_8002838C(void);
/* 028690 */ UNK_RET lbAudioAx_80028690(UNK_PARAMS);
/* 028B2C */ int lbAudioAx_80028B2C(void);
/* 028B4C */ int lbAudioAx_80028B4C(void);
/* 028B6C */ void lbAudioAx_80028B6C(void);
/* 028B90 */ void lbAudioAx_80028B90(void);

#endif
