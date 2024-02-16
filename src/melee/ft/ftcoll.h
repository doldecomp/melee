#ifndef GALE01_0763C0
#define GALE01_0763C0

#include <platform.h>
#include "ft/forward.h"
#include "ftCommon/forward.h"
#include "lb/forward.h"
#include <baselib/forward.h>

#include <placeholder.h>

/* 0763C0 */ void ftColl_800763C0(Fighter_GObj* attacker, Fighter_GObj* victim,
                                  enum_t attackID);
/* 076444 */ void ftColl_80076444(Fighter_GObj* attacker,
                                  Fighter_GObj* victim);
/* 07646C */ void ftColl_8007646C(Fighter_GObj* attackItem,
                                  Fighter_GObj* victim);
/* 0764DC */ void ftColl_800764DC(Fighter_GObj* gobj);
/* 076528 */ void ftColl_80076528(Fighter_GObj* gobj);
/* 0765AC */ void ftColl_800765AC(Fighter_GObj* victim);
/* 0765E0 */ void ftColl_800765E0(void);
/* 0765F0 */ float ftColl_800765F0(Fighter* fp, Fighter_GObj* victim,
                                   float unk_floatvar);
/* 076640 */ bool ftColl_80076640(Fighter*, float*);
/* 076764 */ void ftColl_80076764(int arg0, enum_t arg1, enum_t arg2,
                                  UNK_T arg3, ftCo_Fighter* arg4,
                                  HurtCapsule* arg5);
/* 076808 */ void ftColl_80076808(Fighter* attacker, HitCapsule*, int,
                                  Fighter* victim, int);
/* 0768A0 */ void ftColl_800768A0(void);
/* 07699C */ bool ftColl_8007699C(Fighter*, HitCapsule*, Fighter*,
                                  HitCapsule*);
/* 076CBC */ bool ftColl_80076CBC(Fighter*, HitCapsule*, Fighter*);
/* 076ED8 */ bool ftColl_80076ED8(Fighter*, HitCapsule*, Fighter*,
                                  HurtCapsule*);
/* 077464 */ UNK_RET ftColl_80077464(UNK_PARAMS);
/* 077970 */ UNK_RET ftColl_80077970(UNK_PARAMS);
/* 077C60 */ UNK_RET ftColl_80077C60(UNK_PARAMS);
/* 078384 */ void ftColl_80078384(Fighter*, HurtCapsule*, HitCapsule*);
/* 078488 */ UNK_RET ftColl_80078488(UNK_PARAMS);
/* 0784B4 */ void ftColl_800784B4(void);
/* 078538 */ UNK_RET ftColl_80078538(UNK_PARAMS);
/* 07861C */ UNK_RET ftColl_8007861C(bool arg0, Fighter_GObj* gobj, int arg2,
                                     int arg3, int arg4, u32 arg5, int arg6,
                                     UNK_T arg7, int arg8);
/* 078710 */ void ftColl_80078710(Fighter_GObj* gobj);
/* 078754 */ void ftColl_80078754(Fighter_GObj*, Fighter_GObj*, bool);
/* 0787B4 */ UNK_RET ftColl_800787B4(UNK_PARAMS);
/* 0788D4 */ void ftColl_800788D4(Fighter_GObj* gobj);
/* 07891C */ UNK_RET ftColl_8007891C(UNK_PARAMS);
/* 078998 */ UNK_RET ftColl_80078998(UNK_PARAMS);
/* 078A2C */ void ftColl_80078A2C(Fighter_GObj*);
/* 078C70 */ void ftColl_80078C70(Fighter_GObj*);
/* 07925C */ void ftColl_8007925C(Fighter_GObj*);
/* 079AB0 */ UNK_RET ftColl_80079AB0(UNK_PARAMS);
/* 079C70 */ float ftColl_80079C70(Fighter*, Fighter*, void*, int);
/* 079EA8 */ float ftColl_80079EA8(Fighter*, HitCapsule*, int);
/* 07A06C */ UNK_RET ftColl_8007A06C(UNK_PARAMS);
/* 07AB48 */ void ftColl_8007AB48(Fighter_GObj*);
/* 07AB80 */ void ftColl_8007AB80(Fighter_GObj*);
/* 07ABD0 */ void ftColl_8007ABD0(HitCapsule*, u32 damageAmount,
                                  Fighter_GObj*);
/* 07AC68 */ bool ftColl_8007AC68(int kb_angle);
/* 07AC9C */ void ftColl_8007AC9C(HitCapsule*, int, Fighter_GObj*);
/* 07AD18 */ void ftColl_8007AD18(ftCo_Fighter* fp, HitCapsule*);
/* 07AE80 */ void ftColl_8007AE80(Fighter_GObj*);
/* 07AEE0 */ void ftColl_8007AEE0(Fighter_GObj*);
/* 07AEF8 */ void ftColl_8007AEF8(Fighter_GObj*);
/* 07AF10 */ void ftColl_8007AF10(Fighter_GObj*);
/* 07AF28 */ void ftColl_8007AF28(Fighter_GObj* gobj);
/* 07AF60 */ UNK_RET ftColl_8007AF60(UNK_PARAMS);
/* 07AFC8 */ void ftColl_8007AFC8(Fighter_GObj* gobj, int);
/* 07AFF8 */ void ftColl_8007AFF8(Fighter_GObj*);
/* 07B064 */ void ftColl_8007B064(Fighter_GObj* gobj, enum_t arg1);
/* 07B0C0 */ void ftColl_8007B0C0(Fighter_GObj*, Tangibility);
/* 07B128 */ void ftColl_8007B128(s8, int);
/* 07B1B8 */ void ftColl_8007B1B8(Fighter_GObj* gobj, ShieldDesc* shield,
                                  HSD_GObjEvent cb);
/* 07B23C */ void ftColl_CreateReflectHit(Fighter_GObj*, ReflectDesc*,
                                          HSD_GObjEvent on_reflect);
/* 07B2C4 */ void ftColl_CreateAbsorbHit(Fighter_GObj*, AbsorbDesc*);
/* 07B320 */ void ftColl_8007B320(Fighter_GObj*);
/* 07B4E0 */ void ftColl_8007B4E0(Fighter_GObj*);
/* 07B5AC */ void ftColl_8007B5AC(ftCo_Fighter* fp, HurtCapsule* arg1,
                                  struct UNK_SAMUS_S2* arg2);
/* 07B62C */ void ftColl_8007B62C(Fighter_GObj*, bool);
/* 07B6A0 */ void ftColl_8007B6A0(Fighter_GObj* gobj);
/* 07B6EC */ void ftColl_8007B6EC(Fighter_GObj*);
/* 07B760 */ void ftColl_8007B760(Fighter_GObj*, int);
/* 07B7A4 */ void ftColl_8007B7A4(Fighter_GObj* gobj, int);
/* 07B7FC */ void ftColl_8007B7FC(Fighter*, int);
/* 07B868 */ bool ftColl_8007B868(Fighter_GObj* gobj);
/* 07B8A8 */ void ftColl_8007B8A8(HitCapsule*, Vec3*);
/* 07B8CC */ void ftColl_8007B8CC(Fighter*, Fighter_GObj*);
/* 07B8E8 */ void ftColl_8007B8E8(Fighter_GObj*);
/* 07B924 */ void ftColl_GetWindOffsetVec(Fighter_GObj*, Vec3* out_wind);
/* 07BA0C */ void ftColl_8007BA0C(Fighter_GObj*);
/* 07BAC0 */ void ftColl_8007BAC0(Fighter_GObj*);
/* 07BBCC */ float ftColl_8007BBCC(Fighter_GObj*);
/* 07BC90 */ void ftColl_8007BC90(Fighter_GObj*);
/* 07BE3C */ void ftColl_8007BE3C(Fighter_GObj*);

#endif
