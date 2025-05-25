#ifndef GALE01_0860C4
#define GALE01_0860C4

#include <dolphin/mtx/forward.h>
#include <baselib/forward.h>

#include "ft/types.h"

/* 0860C4 */ s32 ftLib_800860C4(void);
/* 0860E8 */ bool ftLib_IsMasterHandPresent(void);
/* 086140 */ bool ftLib_IsCrazyHandPresent(void);
/* 086198 */ HSD_GObj* ftLib_80086198(HSD_GObj*);
/* 08627C */ HSD_GObj* ftLib_8008627C(Vec3* pos, HSD_GObj*);
/* 086368 */ HSD_GObj* ftLib_80086368(Vec3*, HSD_GObj*, float);
/* 0864A8 */ float ftLib_800864A8(Vec3*, HSD_GObj*);
/* 0865C0 */ float ftLib_800865C0(HSD_GObj*);
/* 0865CC */ s32 ftLib_800865CC(HSD_GObj*);
/* 0865D8 */ void ftLib_800865D8(HSD_GObj*, float*, float*);
/* 0865F0 */ void* ftLib_800865F0(HSD_GObj*);
/* 086630 */ void* ftLib_80086630(Fighter_GObj*, Fighter_Part part);
/* 086644 */ void ftLib_80086644(HSD_GObj*, Vec3*);
/* 086664 */ void ftLib_80086664(HSD_GObj*, Vec3*);
/* 086684 */ void ftLib_80086684(HSD_GObj*, Vec3*);
/* 0866A4 */ void ftLib_SetScale(HSD_GObj*, float);
/* 0866DC */ void ftLib_800866DC(HSD_GObj*, Vec3*);
/* 086724 */ void ftLib_80086724(HSD_GObj*, HSD_GObj*);
/* 086764 */ void ftLib_80086764(HSD_GObj*);
/* 086794 */ HSD_GObj* ftLib_80086794(HSD_GObj*);
/* 0867A0 */ bool ftLib_800867A0(HSD_GObj*, HSD_GObj*);
/* 0867CC */ HSD_GObj* ftLib_800867CC(HSD_GObj*);
/* 0867D8 */ bool ftLib_800867D8(HSD_GObj*);
/* 0867E8 */ void ftLib_800867E8(HSD_GObj*);
/* 086824 */ void ftLib_80086824(void);
/* 08688C */ void ftLib_8008688C(HSD_GObj*);
/* 0868A4 */ void ftLib_800868A4(void);
/* 0868D4 */ bool ftLib_800868D4(HSD_GObj*, HSD_GObj*);
/* 086960 */ bool ftLib_80086960(HSD_GObj* gobj);
/* 086984 */ CollData* ftLib_80086984(HSD_GObj*);
/* 086990 */ void ftLib_80086990(HSD_GObj*, Vec3*);
/* 0869D4 */ float ftLib_800869D4(HSD_GObj*);
/* 0869F8 */ float ftLib_800869F8(HSD_GObj*);
/* 086A0C */ float ftLib_80086A0C(HSD_GObj*);
/* 086A18 */ bool ftLib_80086A18(HSD_GObj*);
/* 086A4C */ void ftLib_80086A4C(HSD_GObj*, float);
/* 086A58 */ bool ftLib_80086A58(HSD_GObj*, S32Vec2*);
/* 086A8C */ bool ftLib_80086A8C(HSD_GObj*);
/* 086B64 */ bool ftLib_80086B64(HSD_GObj*);
/* 086B74 */ CameraBox* ftLib_80086B74(HSD_GObj*);
/* 086B80 */ float ftLib_80086B80(HSD_GObj*);
/* 086B90 */ void ftLib_80086B90(HSD_GObj*, Vec3* v);
/* 086BB4 */ void ftLib_80086BB4(HSD_GObj*);
/* 086BE0 */ u8 ftLib_80086BE0(HSD_GObj*);
/* 086BEC */ void ftLib_80086BEC(HSD_GObj*, Vec3*);
/* 086C0C */ enum_t ftLib_80086C0C(HSD_GObj*);
/* 086C18 */ void ftLib_80086C18(HSD_GObj*, s32, s32);
/* 086C9C */ void ftLib_80086C9C(s32, s32);
/* 086D40 */ void ftLib_80086D40(HSD_GObj*, s32, s32);
/* 086DC4 */ void ftLib_80086DC4(s32, s32);
/* 086E68 */ void ftLib_80086E68(HSD_GObj*);
/* 086EB4 */ s32 ftLib_80086EB4(HSD_GObj*);
/* 086EC0 */ bool ftLib_80086EC0(HSD_GObj*);
/* 086ED0 */ bool ftLib_80086ED0(HSD_GObj*);
/* 086F4C */ bool ftLib_80086F4C(HSD_GObj*);
/* 086F80 */ float ftLib_80086F80(HSD_GObj*);
/* 086FA8 */ bool ftLib_80086FA8(HSD_GObj*);
/* 086FD4 */ bool ftLib_80086FD4(HSD_GObj*, HSD_GObj*);
/* 08701C */ bool ftLib_8008701C(HSD_GObj*);
/* 08702C */ void ftLib_8008702C(s32);
/* 087050 */ void ftLib_80087050(s32);
/* 087074 */ bool ftLib_80087074(HSD_GObj*, Vec3*);
/* 0870BC */ bool ftLib_800870BC(HSD_GObj*, void**);
/* 0870F0 */ void ftLib_800870F0(HSD_GObj*, s32);
/* 087120 */ s32 ftLib_80087120(HSD_GObj*);
/* 087140 */ void ftLib_80087140(HSD_GObj*);
/* 0871A8 */ void ftLib_800871A8(Fighter_GObj*, Item_GObj*);
/* 087284 */ bool ftLib_80087284(HSD_GObj*);
/* 0872A4 */ FighterKind ftLib_800872A4(HSD_GObj*);
/* 0872B0 */ void* ftLib_800872B0(HSD_GObj*);
/* 0872BC */ bool ftLib_800872BC(HSD_GObj*);
/* 087300 */ s32 ftLib_80087300(HSD_GObj*);
/* 08730C */ s32 ftLib_8008730C(HSD_GObj*);
/* 08731C */ s32 ftLib_8008731C(HSD_GObj*);
/* 08732C */ bool ftLib_8008732C(HSD_GObj*);
/* 087354 */ bool ftLib_80087354(HSD_GObj*);
/* 08737C */ bool ftLib_8008737C(HSD_GObj*);
/* 0873A4 */ bool ftLib_800873A4(HSD_GObj*);
/* 0873CC */ bool ftLib_800873CC(HSD_GObj*);
/* 0873F4 */ bool ftLib_800873F4(HSD_GObj*);
/* 08741C */ HSD_GObj* ftLib_8008741C(u32);
/* 087454 */ float ftLib_80087454(HSD_GObj*);
/* 087460 */ u32 ftLib_80087460(HSD_GObj*);
/* 08746C */ s32 ftLib_8008746C(HSD_GObj*);
/* 0874BC */ s32 ftLib_800874BC(HSD_GObj*);
/* 0874CC */ void ftLib_800874CC(HSD_GObj*, void*, s32);
/* 087508 */ void ftLib_80087508(s8, u8);
/* 087574 */ void ftLib_80087574(s8);
/* 087610 */ void ftLib_80087610(u8);
/* 0876B4 */ void ftLib_800876B4(HSD_GObj*);
/* 0876D4 */ bool ftLib_800876D4(HSD_GObj*);
/* 0876F4 */ s32 ftLib_800876F4(HSD_GObj*);
/* 087700 */ s32 ftLib_80087700(HSD_GObj*);
/* 08770C */ void ftLib_8008770C(HSD_GObj*, void* dst);
/* 087744 */ void ftLib_80087744(HSD_GObj*, void* dst);
/* 08777C */ void ftLib_8008777C(HSD_GObj*);
/* 0877D4 */ bool ftLib_800877D4(HSD_GObj*);

#endif
