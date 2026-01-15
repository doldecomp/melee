#include "mnvibration.h"

#include "mnmain.h"

#include <sysdolphin/baselib/gobj.h>
#include <sysdolphin/baselib/gobjplink.h>
#include <sysdolphin/baselib/gobjproc.h>
#include <melee/lb/lbarchive.h>

typedef struct MnVibrationAssets {
    void* SCl_Top_joint;
    u8 pad4[0xC];
    void* Title_Top_joint;
    void* Title_Top_animjoint;
    void* Title_Top_matanim_joint;
    void* Title_Top_shapeanim_joint;
    void* Option_Top_joint;
    void* Option_Top_animjoint;
    void* Option_Top_matanim_joint;
    void* Option_Top_shapeanim_joint;
    void* Panel_Top_joint;
    void* Panel_Top_animjoint;
    void* Panel_Top_matanim_joint;
    void* Panel_Top_shapeanim_joint;
} MnVibrationAssets;

MnVibrationAssets mnVibration_804A0868;

void* mnVibration_802474C4(s32 arg0)
{
    VibNode* node;
    if (mnVibration_804D6C28->x2C == NULL) {
        node = NULL;
    } else {
        node = mnVibration_804D6C28->x2C->x50;
    }
    if (node == NULL) {
        node = NULL;
    } else {
        node = node->x10;
    }
    for (; arg0 > 0; arg0--) {
        if (node == NULL) {
            node = NULL;
        } else {
            node = node->x8;
        }
    }
    return node;
}
/// #fn_80247510

void fn_80248084(HSD_GObj* gobj)
{
    if (mn_804A04F0.cur_menu != 0x13) {
        HSD_GObjPLink_80390228(gobj);
    }
}

/// #mnVibration_802480B4

/// #mnVibration_8024829C

/// #mnVibration_80248444

/// #mnVibration_80248644

void fn_80248748(HSD_GObj* gobj)
{
    f32* table = mnVibration_803EECEC;
    void* data = gobj->user_data;
    void* jobj = ((VibJObjData*) data)->x10;
    f32 result = mn_8022ED6C(jobj, (AnimLoopSettings*) table);
    if (result >= table[1]) {
        HSD_GObjPLink_80390228(gobj);
    }
}
/// #fn_802487A8

/// #fn_80248A78

/// #mnVibration_80248ED4

void mnVibration_80249174(int arg0)
{
    HSD_GObj* gobj;
    u8* gobj_flags_ptr;

    mn_804D6BC8.cooldown = 5;
    mn_804A04F0.prev_menu = mn_804A04F0.cur_menu;
    mn_804A04F0.cur_menu = 19;
    mn_804A04F0.hovered_selection = 0;

    lbArchive_LoadSections(
        mn_804D6BB8, &mnVibration_804A0868.Title_Top_joint,
        "MnVibTitle_Top_joint", &mnVibration_804A0868.Title_Top_animjoint,
        "MnVibTitle_Top_animjoint",
        &mnVibration_804A0868.Title_Top_matanim_joint,
        "MnVibTitle_Top_matanim_joint",
        &mnVibration_804A0868.Title_Top_shapeanim_joint,
        "MnVibTitle_Top_shapeanim_joint",

        &mnVibration_804A0868.SCl_Top_joint, "MnVibSCl_Top_joint",

        &mnVibration_804A0868.Option_Top_joint, "MnVibOption_Top_joint",
        &mnVibration_804A0868.Option_Top_animjoint,
        "MnVibOption_Top_animjoint",
        &mnVibration_804A0868.Option_Top_matanim_joint,
        "MnVibOption_Top_matanim_joint",
        &mnVibration_804A0868.Option_Top_shapeanim_joint,
        "MnVibOption_Top_shapeanim_joint",

        &mnVibration_804A0868.Panel_Top_joint, "MnVibPanel_Top_joint",
        &mnVibration_804A0868.Panel_Top_animjoint, "MnVibPanel_Top_animjoint",
        &mnVibration_804A0868.Panel_Top_matanim_joint,
        "MnVibPanel_Top_matanim_joint",
        &mnVibration_804A0868.Panel_Top_shapeanim_joint,
        "MnVibPanel_Top_shapeanim_joint",

        NULL);

    ((void (*)(int)) mnVibration_80248ED4)(arg0);

    gobj = GObj_Create(0, 1, 0x80);
    HSD_GObjProc_8038FD54(gobj, (void (*)(HSD_GObj*)) fn_80247510, 0);

    gobj_flags_ptr = (u8*) gobj + 0xD;
    *gobj_flags_ptr =
        (*gobj_flags_ptr & 0xCF) | ((HSD_GObj_804D783C << 4) & 0x30);
}
