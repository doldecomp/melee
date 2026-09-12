#ifndef GALE01_266F3C
#define GALE01_266F3C
#include <Runtime/platform.h>

#include <melee/it/forward.h>
#include <sysdolphin/baselib/forward.h>

#include <dolphin/mtx.h>
#include <melee/ft/types.h>
#include <sysdolphin/baselib/objalloc.h>

struct ItemStateDesc;

/// Checks if items are enabled
/* 266F3C */ bool Item_80266F3C(void);

/// Check to load ItCo.dat/usd
/* 266F70 */ void Item_80266F70(void);

/// ItCo prefunction with 0
/* 266FA8 */ void Item_80266FA8(void);

/// Init item struct?
/* 266FCC */ void Item_80266FCC(void);

/// Remove Camera Box
/* 267454 */ void Item_80267454(HSD_GObj* gobj);

/// Store Item Pointers
/* 267978 */ void Item_80267978(HSD_GObj* gobj);

/// Setup Item JObj
/* 2680CC */ void Item_802680CC(HSD_GObj* gobj);

/// Set item model scale
/* 26849C */ void Item_8026849C(HSD_GObj* gobj);

/// Item spawn prefunction - spawn airborne
/* 268B18 */ Item_GObj* Item_80268B18(SpawnItem* spawnItem);

/// Item spawn prefunction - spawn grounded
/* 268B5C */ Item_GObj* Item_80268B5C(SpawnItem* spawnItem);

/// Item spawn prefunction - spawn grounded and toggle unknown true
/* 268B9C */ void Item_80268B9C(SpawnItem* spawnItem);

/// Unk Item AObj-related function
/* 268D34 */ void Item_80268D34(HSD_GObj* gobj,
                                struct ItemStateDesc* itemStateDesc);

/// Advance item animation?
/* 268DD4 */ void Item_80268DD4(HSD_GObj* gobj, float);

/// Copy item script
/* 268E40 */ void Item_80268E40(Item* item_data,
                                struct ItemStateDesc* itemStateDesc);

/// Item State Change
/* 268E5C */ void Item_80268E5C(HSD_GObj* gobj, enum_t msid,
                                Item_StateChangeFlags flags);

/* 2693E4 */ void Item_802693E4(HSD_GObj* gobj);

/// Advance item animation + script?
/* 2694CC */ void Item_802694CC(HSD_GObj* gobj);

/// Item Think - Physics
/* 2697D4 */ void Item_802697D4(HSD_GObj* gobj);

/// Item Think - Collision
/* 269978 */ void Item_80269978(HSD_GObj* gobj);

/// Set damage taken
/* 269CA0 */ void Item_80269CA0(Item* item_data, s32 damage);

/// Remove Item from Player
/* 26A848 */ void Item_8026A848(HSD_GObj* gobj, HSD_GObj* fgobj);

/// Destroy Item
/* 26A8EC */ void Item_8026A8EC(Item_GObj* gobj);

/// Make Item Held
/* 26AB54 */ void Item_8026AB54(HSD_GObj* gobj, HSD_GObj* owner_gobj,
                                Fighter_Part part);

/// Drop Item
/* 26ABD8 */ void Item_8026ABD8(Item_GObj* gobj, Vec3* pos, float);

/// This is actually another Item Drop function
/* 26AC74 */ void Item_8026AC74(HSD_GObj* gobj, Vec3*, Vec3*, float);

/// Throw Item
/* 26AD20 */ void Item_8026AD20(HSD_GObj* gobj, Vec3*, Vec3*, float, bool);

/// Make Item Airborne
/* 26ADC0 */ void Item_8026ADC0(HSD_GObj* gobj);

/* 26AE10 */ void Item_OnUserDataRemove(void* user_data);

/// Clear Item Struct ?
/* 26AE10 */ void lbl_8026AE10(void* user_data);

/* 26AE60 */ u32 Item_8026AE60(void);

/// Play Item SFX
/* 26AE84 */ void Item_8026AE84(Item* item_data, enum_t sfx, u8 pan,
                                u8 volume);

/// Play Item SFX 2
/* 26AF0C */ void Item_8026AF0C(Item* item_data, enum_t sfx, u8 pan,
                                u8 volume);

/// Play Item SFX 3
/* 26AFA0 */ void Item_8026AFA0(Item* item_data, enum_t sfx, u8 pan,
                                u8 volume);

/// Stop Item SFX
/* 26B034 */ void Item_8026B034(Item* item_data);

/// Stop Item SFX 2
/* 26B074 */ void Item_8026B074(Item* item_data);

/// Check if item is grabbable
/* 26B1A4 */ bool Item_IsGrabbable(Item_GObj* gobj);

/* 4A0C38 */ extern HSD_ObjAllocData item_link_alloc_data;
/* 4A0C64 */ extern HSD_ObjAllocUnk Item_804A0C64;
/* 4A0CCC */ extern Item_FtTrack Item_804A0CCC;
/* 4A0E24 */ extern S32Vec3 Item_804A0E24;

#endif
