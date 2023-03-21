#ifndef MELEE_FT_CHARA_FTPEACH_FTPEACH_H
#define MELEE_FT_CHARA_FTPEACH_FTPEACH_H

#include <sysdolphin/baselib/gobj.h>
#include <melee/ft/fighter.h>

typedef struct _ftPeachAttributes {
    f32 unk0;
    f32 unk4;
    u8 padding[0xB8];
} ftPeachAttributes;

extern ActionState as_table_peach[];
extern char ftPeach_str_PlPe_dat[];
extern char ftPeach_str_ftDataPeach[];
extern Fighter_CostumeStrings ftPeach_str_arr_Costumes[];
extern char str_PlPeAJ_dat[];
extern Fighter_DemoStrings ftPeach_str_arr_ftDemo;

void ftPeach_OnDeath(HSD_GObj* gobj);
s32 ftPeach_8011BA20(Fighter* fp);
void ftPeach_OnKnockbackEnter(HSD_GObj* gobj);
void ftPeach_OnKnockbackExit(HSD_GObj* gobj);
void ftPeach_OnLoad(HSD_GObj* gobj);
void ftPeach_8011B704(HSD_GObj* gobj);
void ftPeach_OnItemPickup(HSD_GObj* gobj, bool bool);
void ftPeach_OnItemInvisible(HSD_GObj* gobj);
void ftPeach_OnItemVisible(HSD_GObj* gobj);
void ftPeach_OnItemDrop(HSD_GObj* gobj, bool bool1);
void ftPeach_LoadSpecialAttrs(HSD_GObj* gobj);
void ftPeach_8011B93C(HSD_GObj* gobj);
void ftPeach_8011BC38(HSD_GObj*);
void ftPeach_8011BC8C(HSD_GObj*);
void ftPeach_8011BD18(HSD_GObj*);
void ftPeach_8011BD3C(HSD_GObj*);
void ftPeach_8011BDF0(HSD_GObj*);
void ftPeach_8011BE2C(HSD_GObj*);
void ftPeach_8011BE30(HSD_GObj*);
void ftPeach_8011BE50(HSD_GObj*);
void ftPeach_8011BDF0(HSD_GObj*);
void ftPeach_8011BE2C(HSD_GObj*);
void ftPeach_8011BE30(HSD_GObj*);
void ftPeach_8011BE50(HSD_GObj*);
void ftPeach_8011BF88(HSD_GObj*);
void ftPeach_8011C044(HSD_GObj*);
void ftPeach_8011C160(HSD_GObj*);
void ftPeach_8011C198(HSD_GObj*);
void ftPeach_8011BF88(HSD_GObj*);
void ftPeach_8011C044(HSD_GObj*);
void ftPeach_8011C160(HSD_GObj*);
void ftPeach_8011C198(HSD_GObj*);
void ftPeach_8011BF88(HSD_GObj*);
void ftPeach_8011C044(HSD_GObj*);
void ftPeach_8011C160(HSD_GObj*);
void ftPeach_8011C198(HSD_GObj*);
void ftPeach_8011BF88(HSD_GObj*);
void ftPeach_8011C044(HSD_GObj*);
void ftPeach_8011C160(HSD_GObj*);
void ftPeach_8011C198(HSD_GObj*);
void ftPeach_8011BF88(HSD_GObj*);
void ftPeach_8011C044(HSD_GObj*);
void ftPeach_8011C160(HSD_GObj*);
void ftPeach_8011C198(HSD_GObj*);
void ftPeach_8011C248(HSD_GObj*);
void ftPeach_8011C284(HSD_GObj*);
void ftPeach_8011C2B4(HSD_GObj*);
void ftPeach_8011C2D4(HSD_GObj*);
void ftPeach_8011C248(HSD_GObj*);
void ftPeach_8011C284(HSD_GObj*);
void ftPeach_8011C2B4(HSD_GObj*);
void ftPeach_8011C2D4(HSD_GObj*);
void ftPeach_8011C248(HSD_GObj*);
void ftPeach_8011C284(HSD_GObj*);
void ftPeach_8011C2B4(HSD_GObj*);
void ftPeach_8011C2D4(HSD_GObj*);
void ftPeach_8011D2EC(HSD_GObj*);
void ftPeach_8011D394(HSD_GObj*);
void ftPeach_8011D3D4(HSD_GObj*);
void ftPeach_8011D340(HSD_GObj*);
void ftPeach_8011D3B4(HSD_GObj*);
void ftPeach_8011D3FC(HSD_GObj*);
void ftPeach_8011C4F0(HSD_GObj*);
void ftPeach_8011C5E8(HSD_GObj*);
void ftPeach_8011C5F0(HSD_GObj*);
void ftPeach_8011C664(HSD_GObj*);
void ftPeach_8011CA84(HSD_GObj*);
void ftPeach_8011CAFC(HSD_GObj*);
void ftPeach_8011CB04(HSD_GObj*);
void ftPeach_8011CB44(HSD_GObj*);
void ftPeach_8011C588(HSD_GObj*);
void ftPeach_8011C5EC(HSD_GObj*);
void ftPeach_8011C644(HSD_GObj*);
void ftPeach_8011C6FC(HSD_GObj*);
void ftPeach_8011CAC0(HSD_GObj*);
void ftPeach_8011CB00(HSD_GObj*);
void ftPeach_8011CB24(HSD_GObj*);
void ftPeach_8011CB80(HSD_GObj*);
void ftPeach_8011CAC0(HSD_GObj*);
void ftPeach_8011CB00(HSD_GObj*);
void ftPeach_8011CB24(HSD_GObj*);
void ftPeach_8011CB80(HSD_GObj*);
void ftPeach_8011C878(HSD_GObj*);
void ftPeach_8011C8C8(HSD_GObj*);
void ftPeach_8011C8CC(HSD_GObj*);
void ftPeach_8011C93C(HSD_GObj*);
void ftPeach_8011D8D0(HSD_GObj*);
void ftPeach_8011DA30(HSD_GObj*);
void ftPeach_8011DCC0(HSD_GObj*);
void ftPeach_8011DDBC(HSD_GObj*);
void ftPeach_8011DE9C(HSD_GObj*);
void ftPeach_8011DF5C(HSD_GObj*);
void ftPeach_8011DF64(HSD_GObj*);
void ftPeach_8011E094(HSD_GObj*);
void ftPeach_8011D980(HSD_GObj*);
void ftPeach_8011DB78(HSD_GObj*);
void ftPeach_8011DCF8(HSD_GObj*);
void ftPeach_8011DE2C(HSD_GObj*);
void ftPeach_8011DEFC(HSD_GObj*);
void ftPeach_8011DF60(HSD_GObj*);
void ftPeach_8011DFD0(HSD_GObj*);
void ftPeach_8011E104(HSD_GObj*);
void ftPeach_8011E4F8(HSD_GObj*);
void ftPeach_8011E670(HSD_GObj*);
void ftPeach_8011E678(HSD_GObj*);
void ftPeach_8011E75C(HSD_GObj*);
void ftPeach_8011E9A0(HSD_GObj*);
void ftPeach_8011EA68(HSD_GObj*);
void ftPeach_8011EA70(HSD_GObj*);
void ftPeach_8011EAE0(HSD_GObj*);
void ftPeach_8011E5B4(HSD_GObj*);
void ftPeach_8011E674(HSD_GObj*);
void ftPeach_8011E6AC(HSD_GObj*);
void ftPeach_8011E798(HSD_GObj*);
void ftPeach_8011EA04(HSD_GObj*);
void ftPeach_8011EA6C(HSD_GObj*);
void ftPeach_8011EA90(HSD_GObj*);
void ftPeach_8011EB1C(HSD_GObj*);
void ftPeach_SpecialS_StartAction(HSD_GObj*);
void ftPeach_SpecialAirHi_StartAction(HSD_GObj*);
void ftPeach_SpecialAirLw_StartAction(HSD_GObj*);
void ftPeach_SpecialAirS_StartAction(HSD_GObj*);
void ftPeach_SpecialAirN_StartAction(HSD_GObj*);
void ftPeach_SpecialN_StartAction(HSD_GObj*);
void ftPeach_SpecialLw_StartAction(HSD_GObj*);
void ftPeach_SpecialHi_StartAction(HSD_GObj*);

#endif
