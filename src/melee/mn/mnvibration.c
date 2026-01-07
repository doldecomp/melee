#include "mnvibration.h"
#include <melee/mn/mnmain.h>
#include <melee/lb/lbarchive.h>
#include <sysdolphin/baselib/gobj.h>
#include <sysdolphin/baselib/gobjproc.h>

// --- Externs ---
extern long HSD_GObj_804D783C;

// --- Local Helper Structs ---
typedef struct MnVibrationAssets {
    void* SCl_Top_joint;            // 0x00
    u8 pad4[0xC];
    void* Title_Top_joint;          // 0x10
    void* Title_Top_animjoint;      // 0x14
    void* Title_Top_matanim_joint;  // 0x18
    void* Title_Top_shapeanim_joint;// 0x1C
    void* Option_Top_joint;         // 0x20
    void* Option_Top_animjoint;     // 0x24
    void* Option_Top_matanim_joint; // 0x28
    void* Option_Top_shapeanim_joint;// 0x2C
    void* Panel_Top_joint;          // 0x30
    void* Panel_Top_animjoint;      // 0x34
    void* Panel_Top_matanim_joint;  // 0x38
    void* Panel_Top_shapeanim_joint;// 0x3C
} MnVibrationAssets;

MnVibrationAssets mnVibration_804A0868;

// --- Function Implementation ---

void mnVibration_80249174(int arg0) {
    HSD_GObj* gobj;
    u8* gobj_flags_ptr;

    mn_804D6BC8.cooldown = 5;
    mn_804A04F0.prev_menu = mn_804A04F0.cur_menu;
    mn_804A04F0.cur_menu = 19;
    mn_804A04F0.hovered_selection = 0;

    // Correct Order: Title -> SCl -> Option -> Panel
    lbArchive_LoadSections(mn_804D6BB8,
        &mnVibration_804A0868.Title_Top_joint, "MnVibTitle_Top_joint",
        &mnVibration_804A0868.Title_Top_animjoint, "MnVibTitle_Top_animjoint",
        &mnVibration_804A0868.Title_Top_matanim_joint, "MnVibTitle_Top_matanim_joint",
        &mnVibration_804A0868.Title_Top_shapeanim_joint, "MnVibTitle_Top_shapeanim_joint",

        &mnVibration_804A0868.SCl_Top_joint, "MnVibSCl_Top_joint",

        &mnVibration_804A0868.Option_Top_joint, "MnVibOption_Top_joint",
        &mnVibration_804A0868.Option_Top_animjoint, "MnVibOption_Top_animjoint",
        &mnVibration_804A0868.Option_Top_matanim_joint, "MnVibOption_Top_matanim_joint",
        &mnVibration_804A0868.Option_Top_shapeanim_joint, "MnVibOption_Top_shapeanim_joint",

        &mnVibration_804A0868.Panel_Top_joint, "MnVibPanel_Top_joint",
        &mnVibration_804A0868.Panel_Top_animjoint, "MnVibPanel_Top_animjoint",
        &mnVibration_804A0868.Panel_Top_matanim_joint, "MnVibPanel_Top_matanim_joint",
        &mnVibration_804A0868.Panel_Top_shapeanim_joint, "MnVibPanel_Top_shapeanim_joint",

        NULL);

    // Cast to function pointer taking an int to bypass header mismatch
    ((void (*)(int))mnVibration_80248ED4)(arg0);

    gobj = GObj_Create(0, 1, 0x80);
    HSD_GObjProc_8038FD54(gobj, (void (*)(HSD_GObj*))fn_80247510, 0);

    gobj_flags_ptr = (u8*)gobj + 0xD;
    *gobj_flags_ptr = (*gobj_flags_ptr & 0xCF) | ((HSD_GObj_804D783C << 4) & 0x30);
}
