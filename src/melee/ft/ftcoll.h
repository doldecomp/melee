#ifndef _ftcoll_h_
#define _ftcoll_h_

#include <dolphin/types.h>
#include <dolphin/mtx/mtxtypes.h>

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
BOOL func_8007B868(HSD_GObj* fighter_gobj);

void func_800764DC();
void func_80076528(struct _HSD_GObj*);
void func_800765AC();
void func_800765E0();
void func_80078754();
void func_80078A2C();
void func_80078C70();
void func_8007925C();
void func_8007AB48();
void func_8007AB80();
void func_8007ABD0(struct _Hitbox*, u32 damageAmount, struct _HSD_GObj*);
void func_8007AE80();
void func_8007AEE0(struct _HSD_GObj*);
void func_8007AF28(struct _HSD_GObj* fighter_gobj);
void func_8007AFF8(struct _HSD_GObj*);
void func_8007B0C0(struct _HSD_GObj*, s32);
void func_8007B1B8(struct _HSD_GObj*, f32*, void (*)(struct _HSD_GObj*));
void func_8007B320();
void func_8007B4E0();
void func_8007B62C();
void func_8007B6EC();
void func_8007B760();
void func_8007B8CC();
void func_8007B8E8();
void func_getWindOffsetVec_8007B924(struct _HSD_GObj*, Vec* out_wind);
void func_8007BA0C();
void func_8007BAC0();
f32 func_8007BBCC(struct _HSD_GObj*);
void func_8007BC90();
void func_8007BE3C(struct _HSD_GObj*);

#endif
