#ifndef _ftcoll_h_
#define _ftcoll_h_

#include <platform.h>
#include "ftCommon/forward.h"
#include "lb/forward.h"

#include "ft/fighter.h"

#include <common_structs.h>
#include <dolphin/mtx/types.h>
#include <baselib/gobjproc.h>

void ftColl_800763C0(HSD_GObj* attacker, HSD_GObj* victim,
                     s32 attackID); // Combo Count Logic
void ftColl_80076444(HSD_GObj* attacker,
                     HSD_GObj* victim); // Combo Count Logic + Get Attack ID
void ftColl_8007646C(HSD_GObj* attackItem,
                     HSD_GObj* victim); // Combo Count Logic w/ Item Owner
void ftColl_800764DC(HSD_GObj* gobj);   // Check to end combo for victim
void ftColl_80076528(
    HSD_GObj* gobj); // Combo count something + adjust FtPart_TopN
void ftColl_800765AC(HSD_GObj* victim); // Clear victim pointer from attacker
                                        // upon freeing memory?
void ftColl_800765E0(void); // Reset hitbox and phantom collision count?
f32 ftColl_800765F0(Fighter* fp, HSD_GObj* victim,
                    f32 unk_floatvar); // Unk knockback related ?
bool ftColl_8007B868(HSD_GObj* gobj);

void ftColl_80076528(HSD_GObj*);
void ftColl_800765E0(void);
void ftColl_80078754(HSD_GObj*, HSD_GObj*, bool);
void ftColl_80078A2C(HSD_GObj*);
void ftColl_80078C70(HSD_GObj*);
void ftColl_8007925C(HSD_GObj*);
void ftColl_8007AB48(HSD_GObj*);
void ftColl_8007AB80(HSD_GObj*);
void ftColl_8007ABD0(HitCapsule*, u32 damageAmount, HSD_GObj*);
void ftColl_8007AE80(HSD_GObj*);
void ftColl_8007AEE0(HSD_GObj*);
void ftColl_8007AF28(HSD_GObj* gobj);
void ftColl_8007AFF8(HSD_GObj*);
void ftColl_8007B0C0(HSD_GObj*, int);
void ftColl_8007B1B8(HSD_GObj*, AbsorbDesc*, HSD_GObjEvent);
void ftColl_8007B320(HSD_GObj*);
void ftColl_8007B4E0(HSD_GObj*);
void ftColl_8007B62C(HSD_GObj*, bool);
void ftColl_8007B6EC(HSD_GObj*);
void ftColl_8007B760(HSD_GObj*, s32);
void ftColl_8007B8CC(Fighter*, HSD_GObj*);
void ftColl_8007B8E8(HSD_GObj*);
void ftColl_GetWindOffsetVec(HSD_GObj*, Vec3* out_wind);
void ftColl_8007BA0C(HSD_GObj*);
void ftColl_8007BAC0(HSD_GObj*);
f32 ftColl_8007BBCC(HSD_GObj*);
void ftColl_8007BC90(HSD_GObj*);
void ftColl_8007BE3C(HSD_GObj*);

///  Update hitbox positions
void ftColl_8007B8A8(HitCapsule*, Vec3*);

/// Enable Reflect Bubble Update
void ftColl_8007AEF8(HSD_GObj*);

void ftColl_CreateReflectHit(HSD_GObj*, ReflectDesc*,
                             HSD_GObjEvent on_reflect);
void ftColl_CreateAbsorbHit(HSD_GObj*, AbsorbDesc*);
void ftColl_8007AF10(HSD_GObj*);
void ftColl_8007B5AC(void* arg0, HurtCapsule* arg1, void* arg2);
void ftColl_8007B7FC(Fighter*, s32);
void ftColl_800763C0(HSD_GObj* attacker, HSD_GObj* victim, s32 attackID);
void ftColl_80076640(void);
void ftColl_80076764(int arg0, int arg1, int arg2, UNK_T arg3,
                     ftCo_Fighter* arg4, int arg5);
void ftColl_80076808(Fighter* attacker, HitCapsule*, int, Fighter* victim,
                     int);
void ftColl_800768A0(void);
bool ftColl_8007699C(Fighter*, HitCapsule*, Fighter*, HitCapsule*);
void ftColl_800784B4(void);
bool ftColl_80076CBC(Fighter*, HitCapsule*, Fighter*);
bool ftColl_80076ED8(Fighter*, HitCapsule*, Fighter*, HurtCapsule*);
UNK_RET ftColl_8007891C(UNK_PARAMS);
UNK_RET ftColl_80078488(UNK_PARAMS);
UNK_RET ftColl_80077970(UNK_PARAMS);
UNK_RET ftColl_80077C60(UNK_PARAMS);
UNK_RET ftColl_80078998(UNK_PARAMS);
UNK_RET ftColl_80078384(UNK_PARAMS);
UNK_RET ftColl_80078538(UNK_PARAMS);
UNK_RET ftColl_8007861C(UNK_PARAMS);
UNK_RET ftColl_800787B4(UNK_PARAMS);
UNK_RET ftColl_800788D4(UNK_PARAMS);
UNK_RET ftColl_80079AB0(UNK_PARAMS);
UNK_RET ftColl_80079C70(UNK_PARAMS);
UNK_RET ftColl_80079EA8(UNK_PARAMS);
UNK_RET ftColl_8007A06C(UNK_PARAMS);
bool ftColl_8007AC68(int kb_angle);
UNK_RET ftColl_8007AC9C(UNK_PARAMS);
UNK_RET ftColl_8007AD18(UNK_PARAMS);
UNK_RET ftColl_8007AF60(UNK_PARAMS);
UNK_RET ftColl_8007AFC8(UNK_PARAMS);
void ftColl_8007B064(ftCo_GObj* gobj, enum_t arg1);
UNK_RET ftColl_8007B128(UNK_PARAMS);
UNK_RET ftColl_80077464(UNK_PARAMS);
/* 07B6A0 */ void ftColl_8007B6A0(ftCo_GObj* gobj);
/* 07B7A4 */ void ftColl_8007B7A4(ftCo_GObj* gobj, int);

#endif
