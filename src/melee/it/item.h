#ifndef GALE01_266F3C
#define GALE01_266F3C

#include <platform.h>

#include "it/forward.h"
#include <baselib/forward.h>

#include "ft/types.h"

#include <dolphin/mtx.h>
#include <baselib/objalloc.h>

struct ItemStateDesc;

/* 266F3C */ bool Item_80266F3C(void);
/* 266F70 */ void Item_80266F70(void);
/* 266FA8 */ void Item_80266FA8(void);
/* 266FCC */ void Item_80266FCC(void);
/* 267454 */ void Item_80267454(HSD_GObj* gobj);
/* 267978 */ void Item_80267978(HSD_GObj* gobj);
/* 2680CC */ void Item_802680CC(HSD_GObj* gobj);
/* 26849C */ void Item_8026849C(HSD_GObj* gobj);
/* 268B18 */ Item_GObj* Item_80268B18(SpawnItem* spawnItem);
/* 268B5C */ Item_GObj* Item_80268B5C(SpawnItem* spawnItem);
/* 268B9C */ void Item_80268B9C(SpawnItem* spawnItem);
/* 268D34 */ void Item_80268D34(HSD_GObj* gobj,
                                struct ItemStateDesc* itemStateDesc);
/* 268DD4 */ void Item_80268DD4(HSD_GObj* gobj, float);
/* 268E40 */ void Item_80268E40(Item* item_data,
                                struct ItemStateDesc* itemStateDesc);
/* 268E5C */ void Item_80268E5C(HSD_GObj* gobj, enum_t msid,
                                Item_StateChangeFlags flags);
/* 2693E4 */ void Item_802693E4(HSD_GObj* gobj);
/* 2694CC */ void Item_802694CC(HSD_GObj* gobj);
/* 2697D4 */ void Item_802697D4(HSD_GObj* gobj);
/* 269978 */ void Item_80269978(HSD_GObj* gobj);
/* 269CA0 */ void Item_80269CA0(Item* item_data, s32 damage);
/* 26A848 */ void Item_8026A848(HSD_GObj* gobj, HSD_GObj* fgobj);
/* 26A8EC */ void Item_8026A8EC(Item_GObj* gobj);
/* 26AB54 */ void Item_8026AB54(HSD_GObj* gobj, HSD_GObj* owner_gobj,
                                Fighter_Part part);
/* 26ABD8 */ void Item_8026ABD8(Item_GObj* gobj, Vec3* pos, float);
/* 26AC74 */ void Item_8026AC74(HSD_GObj* gobj, Vec3*, Vec3*, float);
/* 26AD20 */ void Item_8026AD20(HSD_GObj* gobj, Vec3*, Vec3*, float);
/* 26ADC0 */ void Item_8026ADC0(HSD_GObj* gobj);
/* 26AE10 */ void Item_OnUserDataRemove(void* user_data);
/* 26AE10 */ void lbl_8026AE10(void* user_data);
/* 26AE60 */ u32 Item_8026AE60(void);
/* 26AE84 */ void Item_8026AE84(Item* item_data, enum_t sfx, int pan,
                                int volume);
/* 26AF0C */ void Item_8026AF0C(Item* item_data, enum_t sfx, int pan,
                                int volume);
/* 26AFA0 */ void Item_8026AFA0(Item* item_data, enum_t sfx, int pan,
                                int volume);
/* 26B034 */ void Item_8026B034(Item* item_data);
/* 26B074 */ void Item_8026B074(Item* item_data);
/* 26B1A4 */ bool Item_IsGrabbable(Item_GObj* gobj);
/* 4A0C38 */ extern HSD_ObjAllocData item_link_alloc_data;
/* 4A0C64 */ extern HSD_ObjAllocUnk Item_804A0C64;
/* 4A0CCC */ extern HSD_ObjAllocUnk2 Item_804A0CCC;
/* 4A0E24 */ extern S32Vec3 Item_804A0E24;

#endif
