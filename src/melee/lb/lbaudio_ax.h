#ifndef GALE01_02305C
#define GALE01_02305C

#include <platform.h>

#include <baselib/forward.h>
#include <melee/ft/forward.h>
#include <melee/gr/forward.h>

#include <baselib/gobj.h>

/// @todo Create an @c enum for SFX IDs.
#define SFX_NONE -1

enum {
    AUDIO_MODE_UNK0,
    AUDIO_MODE_UNK1,
};

int lbAudioAx_8002305C(int, int);
int lbAudioAx_80023090(int);
int lbAudioAx_800230C8(int, int*, int*);
int lbAudioAx_80023130(int);
int lbAudioAx_80023220(int);
int lbAudioAx_800233EC(int);
int lbAudioAx_80023694(void);
int lbAudioAx_800236B8(int);
int lbAudioAx_800236DC(void);
bool lbAudioAx_80023710(int);
bool lbAudioAx_80023730(void);
int lbAudioAx_800237A8(enum_t sfx_id, int sfx_vol, int sfx_pan);
int lbAudioAx_80023870(int, int, int, int);
void lbAudioAx_8002392C(void);
int lbAudioAx_80023968(int);
int lbAudioAx_80023A44(int, int);
int lbAudioAx_80023B24(int);
int lbAudioAx_80023F28(int);
void lbAudioAx_80024030(int);
int lbAudioAx_800240B4(int);
int lbAudioAx_8002411C(int);
int lbAudioAx_80024184(int, int, int, int);
int lbAudioAx_80024304(int);
int lbAudioAx_8002438C(int);
int lbAudioAx_800243F4(int);
void lbAudioAx_800245D4(int);
int lbAudioAx_800245F4(int);
void lbAudioAx_80024614(int);
void lbAudioAx_80024634(int);
void lbAudioAx_80024B1C(int, int);
void lbAudioAx_80024B58(int, int);
int lbAudioAx_80024B94(int arg0, int arg1);
bool lbAudioAx_80024BD0(void);
bool lbAudioAx_80024C08(enum_t);
void lbAudioAx_80024C84(void);
void lbAudioAx_80024D50(void);
void lbAudioAx_80024D78(int);
void lbAudioAx_80024DC4(int);
void lbAudioAx_80024E50(bool pause);
void lbAudioAx_80024E84(bool);
void lbAudioAx_80024F08(void);
void lbAudioAx_80024F6C(void);
void lbAudioAx_80024FDC(void);
void lbAudioAx_80024FF4(void);
void lbAudioAx_8002500C(int);
void lbAudioAx_80025038(int);
void lbAudioAx_80025064(bool, bool);
void lbAudioAx_80025098(bool debug);
HSD_GObj* lbAudioAx_800263E8(float, HSD_GObj*, int, int, int, int, int, int,
                             int, int, int);
int lbAudioAx_800264E4(HSD_GObj* data);
bool lbAudioAx_80026510(HSD_GObj*);
bool lbAudioAx_800265C4(HSD_GObj*, int sfx);
u64 lbAudioAx_80026E84(CharacterKind);
u64 lbAudioAx_80026EBC(StKind);
void lbAudioAx_80026F2C(u32);
void lbAudioAx_8002702C(u32 flags, u64 mask);
void lbAudioAx_80027168(void);
void lbAudioAx_80027648(void);
void lbAudioAx_8002785C(void);
void lbAudioAx_80027AB0(int);
void lbAudioAx_80027DBC(void);
void lbAudioAx_80027DF8(void);
void lbAudioAx_8002835C(void);
void lbAudioAx_8002838C(void);
void lbAudioAx_80028690(void);
int lbAudioAx_80028B2C(void);
int lbAudioAx_80028B4C(void);
void lbAudioAx_80028B6C(void);
void lbAudioAx_80028B90(void);

#endif
