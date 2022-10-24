#ifndef _ftcoll_h_
#define _ftcoll_h_

#include <dolphin/types.h>
#include <dolphin/mtx/mtxtypes.h>

#include <melee/ft/fighter.h>

void func_800763C0(HSD_GObj* attacker, HSD_GObj* victim, s32 attackID); // Combo Count Logic //
void func_80076444(HSD_GObj* attacker, HSD_GObj* victim); // Combo Count Logic + Get Attack ID //
void func_8007646C(HSD_GObj* attackItem, HSD_GObj* victim); // Combo Count Logic w/ Item Owner //
void func_800764DC(HSD_GObj* fighter_gobj); // Check to end combo for victim //
void func_80076528(HSD_GObj* fighter_gobj); // Combo count something + adjust TopN //
void func_800765AC(HSD_GObj* victim); // Clear victim pointer from attacker upon freeing memory? //
void func_800765E0(void); // Reset hitbox and phantom collision count? //
f32 func_800765F0(Fighter* fp, HSD_GObj* victim, f32 unk_floatvar); // Unk knockback related ? //
BOOL func_8007B868(HSD_GObj* fighter_gobj);
void func_8007ABD0(Hitbox*, u32 damageAmount, HSD_GObj*);
void func_8007AEE0(HSD_GObj*);
void func_8007AF28(HSD_GObj* fighter_gobj);
void func_8007AFF8(HSD_GObj *);
void func_8007B0C0(HSD_GObj*, s32);
void func_8007B1B8(HSD_GObj*, f32*, void (*)(HSD_GObj*));
void func_8007B4E0(HSD_GObj*);
void func_8007B5AC(Fighter*, ftHurt*, s32*);
void func_8007B6EC(HSD_GObj* fighter_gobj);
void func_8007B760(HSD_GObj* fighter_gobj, s32);
void func_8007B7A4(HSD_GObj* fighter_gobj, s32);
void func_8007B8CC(Fighter*, HSD_GObj*);
void func_8007B8E8(HSD_GObj* fighter_obj);

#endif 