#ifndef _ftcoll_h_
#define _ftcoll_h_

#include <dolphin/mtx/types.h>
#include <Runtime/platform.h>
#include <sysdolphin/baselib/gobjproc.h>

#include <melee/ft/fighter.h>

void func_800763C0(HSD_GObj* attacker, HSD_GObj* victim,
                   s32 attackID); // Combo Count Logic //
void func_80076444(HSD_GObj* attacker,
                   HSD_GObj* victim); // Combo Count Logic + Get Attack ID //
void func_8007646C(HSD_GObj* attackItem,
                   HSD_GObj* victim); // Combo Count Logic w/ Item Owner //
void func_800764DC(HSD_GObj* fighter_gobj); // Check to end combo for victim //
void func_80076528(
    HSD_GObj* fighter_gobj);          // Combo count something + adjust TopN //
void func_800765AC(HSD_GObj* victim); // Clear victim pointer from attacker upon
                                      // freeing memory? //
void func_800765E0(void); // Reset hitbox and phantom collision count? //
f32 func_800765F0(Fighter* fp, HSD_GObj* victim,
                  f32 unk_floatvar); // Unk knockback related ? //
bool func_8007B868(HSD_GObj* fighter_gobj);

void func_80076528(HSD_GObj*);
void func_800765E0(void);
void func_80078754(HSD_GObj*, HSD_GObj*, bool);
void func_80078A2C(HSD_GObj*);
void func_80078C70(HSD_GObj*);
void func_8007925C(HSD_GObj*);
void func_8007AB48(HSD_GObj*);
void func_8007AB80(HSD_GObj*);
void func_8007ABD0(struct _Hitbox*, u32 damageAmount, HSD_GObj*);
void func_8007AE80(HSD_GObj*);
void func_8007AEE0(HSD_GObj*);
void func_8007AF28(HSD_GObj* fighter_gobj);
void func_8007AFF8(HSD_GObj*);
void func_8007B0C0(HSD_GObj*, s32);
void func_8007B1B8(HSD_GObj*, f32*, void (*)(HSD_GObj*));
void func_8007B320(HSD_GObj*);
void func_8007B4E0(HSD_GObj*);
void func_8007B62C(HSD_GObj*, bool);
void func_8007B6EC(HSD_GObj*);
void func_8007B760(HSD_GObj*, s32);
void func_8007B8CC(Fighter*, HSD_GObj*);
void func_8007B8E8(HSD_GObj*);
void func_getWindOffsetVec_8007B924(HSD_GObj*, Vec3* out_wind);
void func_8007BA0C(HSD_GObj*);
void func_8007BAC0(HSD_GObj*);
f32 func_8007BBCC(HSD_GObj*);
void func_8007BC90(HSD_GObj*);
void func_8007BE3C(HSD_GObj*);

///  Update hitbox positions
void func_8007B8A8(Hitbox*, Vec3*);

/// Enable Reflect Bubble Update
void func_8007AEF8(HSD_GObj*);

void ftColl_CreateReflectHit(HSD_GObj*, ReflectDesc*, HSD_GObjEvent on_reflect);
void ftColl_CreateAbsorbHit(HSD_GObj*, AbsorbDesc*);
void func_8007AF10(HSD_GObj*);
void func_8007B5AC(void* arg0, void* arg1, void* arg2);
void func_8007B7FC(Fighter*, s32);
void func_800763C0(HSD_GObj* attacker, HSD_GObj* victim, s32 attackID);
void func_80076640(void);
void func_80076764(void);
void func_80076808(void);
void func_800768A0(void);
void func_8007699C(void);
void func_800784B4(void);
void func_80076CBC(void);
void func_80076ED8(void);
void func_8007891C(void);
void func_80078488(void);
void func_80077970(void);
void func_80077C60(void);
void func_80078998(void);
void func_80078384(void);

#endif
