#ifndef _ftkoopa_h_
#define _ftkoopa_h_

#include <sysdolphin/baselib/gobj.h>
#include <melee/ft/fighter.h>

typedef struct _ftKoopaAttributes {
    f32 x0;
    u32 x4;
    f32 x8;
    f32 xC;
    f32 x10;
    f32 x14;
    f32 x18;
    f32 x1C;
    u32 x20;
    f32 x24;
    f32 x28;
    u32 x2C;
    f32 x30;
    f32 x34;
    f32 x38;
    f32 x3C;
    f32 x40;
    f32 x44;
    f32 x48;
    f32 x4C;
    u32 unk50;
    f32 x54;
    f32 x58;
    f32 x5C;
    f32 x60;
    f32 x64;
    f32 x68;
    f32 x6C;
    f32 x70;
    f32 x74;
    f32 x78;
    f32 x7C;
    f32 x80;
    f32 x84;
    f32 x88;
    f32 x8C;
    f32 x90;
    f32 x94;
    f32 x98;
    f32 x9C;
} ftKoopaAttributes;

typedef struct _ftKoopaVars {
    f32 x0;
    f32 x4;
} ftKoopaVars;

extern ActionState as_table_koopa[];
extern char lbl_803CF0A0[];
extern char lbl_803CF0AC[];
extern Fighter_CostumeStrings lbl_803CF26C[];
extern char lbl_803CF1E0[];
extern Fighter_DemoStrings lbl_803CF25C;

void ftKoopa_SpecialS_StartAction(HSD_GObj* gobj);
void func_8013302C(HSD_GObj* gobj);
void func_801330E4(HSD_GObj* gobj);
void func_80132A64(HSD_GObj* gobj);
void ftKoopa_OnLoadForGKoopa(Fighter* fp);
void ftKoopa_LoadSpecialAttrs(HSD_GObj* gobj);
f32 func_80132DC0(HSD_GObj* gobj);
f32 func_80132DD0(HSD_GObj* gobj);
f32 func_80132DE0(HSD_GObj* gobj);
f32 func_80132DF0(HSD_GObj* gobj);
f32 func_80132E00(HSD_GObj* gobj);
f32 func_80132E10(HSD_GObj* gobj);
f32 func_80132E20(HSD_GObj* gobj);
void ftKoopa_OnDeath(HSD_GObj* gobj);
void func_80132E30(HSD_GObj* gobj);
void ftKoopa_SpecialAirS_StartAction(HSD_GObj* gobj);
void func_8013319C(HSD_GObj* gobj);
void func_8013322C(HSD_GObj* gobj);
void func_801332C4(HSD_GObj* gobj);
void func_80133324(HSD_GObj* gobj);
void func_80133398(HSD_GObj* gobj);
void func_801333F8(HSD_GObj* gobj);
void func_80133484(HSD_GObj* gobj);
void func_801334E4(HSD_GObj* gobj);
void func_8013359C(HSD_GObj* gobj);
void func_80133654(HSD_GObj* gobj);
void func_80133690(HSD_GObj* gobj);
void func_801336CC(HSD_GObj* gobj);
void ftKoopa_OnLoad(HSD_GObj* gobj);
void func_80132B38(void);
void ftKoopa_OnItemPickup(HSD_GObj* gobj, bool bool);
void ftKoopa_OnItemInvisible(HSD_GObj* gobj);
void ftKoopa_OnItemVisible(HSD_GObj* gobj);
void ftKoopa_OnItemDrop(HSD_GObj* gobj, bool bool1);
void ftKoopa_OnKnockbackEnter(HSD_GObj* gobj);
void ftKoopa_OnKnockbackExit(HSD_GObj* gobj);
void lbl_80134F48(HSD_GObj*);
void lbl_801351B0(HSD_GObj*);
void lbl_80135438(HSD_GObj*);
void lbl_801354F8(HSD_GObj*);
void lbl_80134F9C(HSD_GObj*);
void lbl_801351B4(HSD_GObj*);
void lbl_80135458(HSD_GObj*);
void lbl_80135564(HSD_GObj*);
void lbl_80135040(HSD_GObj*);
void lbl_801352F0(HSD_GObj*);
void lbl_80135478(HSD_GObj*);
void lbl_801355D0(HSD_GObj*);
void lbl_8013507C(HSD_GObj*);
void lbl_801352F4(HSD_GObj*);
void lbl_80135498(HSD_GObj*);
void lbl_8013563C(HSD_GObj*);
void lbl_801350D0(HSD_GObj*);
void lbl_801352F8(HSD_GObj*);
void lbl_801354B8(HSD_GObj*);
void lbl_801356A8(HSD_GObj*);
void lbl_80135174(HSD_GObj*);
void lbl_80135434(HSD_GObj*);
void lbl_801354D8(HSD_GObj*);
void lbl_80135714(HSD_GObj*);
void func_80133654(HSD_GObj*);
void lbl_80134224(HSD_GObj*);
void lbl_80134388(HSD_GObj*);
void func_801336CC(HSD_GObj*);
void lbl_80133BF4(HSD_GObj*);
void lbl_80134288(HSD_GObj*);
void lbl_801343D8(HSD_GObj*);
void func_801336CC(HSD_GObj*);
void lbl_80133BF4(HSD_GObj*);
void lbl_80134288(HSD_GObj*);
void lbl_801343D8(HSD_GObj*);
void lbl_801339AC(HSD_GObj*);
void lbl_80133E4C(HSD_GObj*);
void lbl_801342C8(HSD_GObj*);
void lbl_80134428(HSD_GObj*);
void lbl_801339B4(HSD_GObj*);
void lbl_80134308(HSD_GObj*);
void lbl_80134478(HSD_GObj*);
void lbl_80133A90(HSD_GObj*);
void lbl_80134328(HSD_GObj*);
void lbl_801344A0(HSD_GObj*);
void func_80133690(HSD_GObj*);
void lbl_80134244(HSD_GObj*);
void lbl_801343B0(HSD_GObj*);
void lbl_8013383C(HSD_GObj*);
void lbl_80133D20(HSD_GObj*);
void lbl_801342A8(HSD_GObj*);
void lbl_80134400(HSD_GObj*);
void lbl_8013383C(HSD_GObj*);
void lbl_80133D20(HSD_GObj*);
void lbl_801342A8(HSD_GObj*);
void lbl_80134400(HSD_GObj*);
void lbl_801339B0(HSD_GObj*);
void lbl_80134038(HSD_GObj*);
void lbl_801342E8(HSD_GObj*);
void lbl_80134450(HSD_GObj*);
void lbl_80133AD4(HSD_GObj*);
void lbl_80134348(HSD_GObj*);
void lbl_801344C8(HSD_GObj*);
void lbl_80133BB0(HSD_GObj*);
void lbl_80134368(HSD_GObj*);
void lbl_801344F0(HSD_GObj*);
void func_80135C08(HSD_GObj*);
void lbl_80135D78(HSD_GObj*);
void lbl_80135D80(HSD_GObj*);
void lbl_80135E4C(HSD_GObj*);
void lbl_80135C60(HSD_GObj*);
void lbl_80135D7C(HSD_GObj*);
void lbl_80135DE0(HSD_GObj*);
void lbl_80135F6C(HSD_GObj*);
void lbl_8013474C(HSD_GObj*);
void lbl_801347C4(HSD_GObj*);
void lbl_801348A0(HSD_GObj*);
void lbl_80134788(HSD_GObj*);
void lbl_80134804(HSD_GObj*);
void func_801348C0(HSD_GObj*);
void lbl_801349C4(HSD_GObj*);
void lbl_80134A00(HSD_GObj*);
void lbl_80134A20(HSD_GObj*);
void ftKoopa_SpecialAirHi_StartAction(HSD_GObj*);
void ftKoopa_SpecialAirLw_StartAction(HSD_GObj*);
void ftKoopa_SpecialAirN_StartAction(HSD_GObj*);
void ftKoopa_SpecialN_StartAction(HSD_GObj*);
void ftKoopa_SpecialLw_StartAction(HSD_GObj*);
void ftKoopa_SpecialHi_StartAction(HSD_GObj*);

#endif
