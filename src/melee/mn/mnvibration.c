#include "mnvibration.h"

#include "ft/ft_0C31.h"
#include "gm/gm_1A36.h"
#include "gm/gmmain_lib.h"
#include "lb/lb_00B0.h"
#include "lb/lb_00F9.h"
#include "lb/lbarchive.h"
#include "lb/lbaudio_ax.h"
#include "mn/inlines.h"
#include "mn/mnmain.h"
#include "mn/mnname.h"
#include "mn/types.h"

#include <dolphin/os.h>
#include <baselib/controller.h>
#include <baselib/gobj.h>
#include <baselib/gobjgxlink.h>
#include <baselib/gobjobject.h>
#include <baselib/gobjplink.h>
#include <baselib/gobjproc.h>
#include <baselib/gobjuserdata.h>
#include <baselib/jobj.h>
#include <baselib/memory.h>
#include <baselib/sislib.h>

// --- Externs ---
extern long HSD_GObj_804D783C;
void lb_8001CE00(void);

// Local inline JObj functions using ftCo_800C6AFC pattern
static inline f32 mnVibration_JObjGetTranslationX(HSD_JObj* jobj)
{
    ((jobj) ? ((void) 0)
            : __assert(mnVibration_804D4FF4, 0x3E1, mnVibration_804D4FFC));
    return jobj->translate.x;
}

static inline f32 mnVibration_JObjGetTranslationY(HSD_JObj* jobj)
{
    ((jobj) ? ((void) 0)
            : __assert(mnVibration_804D4FF4, 0x3EE, mnVibration_804D4FFC));
    return jobj->translate.y;
}

static inline f32 mnVibration_JObjGetTranslationZ(HSD_JObj* jobj)
{
    ((jobj) ? ((void) 0)
            : __assert(mnVibration_804D4FF4, 0x3FB, mnVibration_804D4FFC));
    return jobj->translate.z;
}

static inline void mnVibration_JObjSetTranslateX(HSD_JObj* jobj, f32 x)
{
    HSD_JObj* temp = jobj;
    ((jobj) ? ((void) 0)
            : __assert(mnVibration_804D4FF4, 0x3A4, mnVibration_804D4FFC));
    jobj->translate.x = x;
    if (!(jobj->flags & JOBJ_MTX_INDEP_SRT)) {
        ftCo_800C6AFC(temp);
    }
}

static inline void mnVibration_JObjSetTranslateY(HSD_JObj* jobj, f32 y)
{
    HSD_JObj* temp = jobj;
    ((jobj) ? ((void) 0)
            : __assert(mnVibration_804D4FF4, 0x3B3, mnVibration_804D4FFC));
    jobj->translate.y = y;
    if (!(jobj->flags & JOBJ_MTX_INDEP_SRT)) {
        ftCo_800C6AFC(temp);
    }
}

static inline void mnVibration_JObjSetTranslateZ(HSD_JObj* jobj, f32 z)
{
    HSD_JObj* temp = jobj;
    ((jobj) ? ((void) 0)
            : __assert(mnVibration_804D4FF4, 0x3C2, mnVibration_804D4FFC));
    jobj->translate.z = z;
    if (!(jobj->flags & JOBJ_MTX_INDEP_SRT)) {
        ftCo_800C6AFC(temp);
    }
}

// --- Static data ---
static u16 mnVibration_804D4FE8[4] = { 0x16, 0x15, 0x14, 0x13 };
static s32 mnVibration_804D4FF0;

// --- Globals ---
HSD_GObj* mnVibration_804D6C28;

// --- Local Helper Structs ---
typedef struct MnVibrationAssets {
    void* SCl_Top_joint; // 0x00
    u8 pad4[0xC];
    void* Title_Top_joint;            // 0x10
    void* Title_Top_animjoint;        // 0x14
    void* Title_Top_matanim_joint;    // 0x18
    void* Title_Top_shapeanim_joint;  // 0x1C
    void* Option_Top_joint;           // 0x20
    void* Option_Top_animjoint;       // 0x24
    void* Option_Top_matanim_joint;   // 0x28
    void* Option_Top_shapeanim_joint; // 0x2C
    void* Panel_Top_joint;            // 0x30
    void* Panel_Top_animjoint;        // 0x34
    void* Panel_Top_matanim_joint;    // 0x38
    void* Panel_Top_shapeanim_joint;  // 0x3C
} MnVibrationAssets;

typedef struct MnVibrationJointAssets {
    void* joint;     // 0x00
    void* animjoint; // 0x04
    void* matanim;   // 0x08
    void* shapeanim; // 0x0C
} MnVibrationJointAssets;

typedef struct MnVibrationData {
    /* 0x00 */ u8 x0[6];         // Controller scroll states
    /* 0x06 */ u8 x6[4];         // Controller connected flags
    /* 0x0A */ u8 scroll_offset; // Scroll offset for name list
    /* 0x0B */ u8 pad_0B;
    /* 0x0C */ HSD_JObj* jobjs[25]; // JObj references (0xC to 0x70)
    /* 0x70 */ HSD_Text* texts[8];  // Text handles for name display
    /* 0x90 */ HSD_Text* title_text;
    /* 0x94 */ HSD_GObj* cursor_gobj;
} MnVibrationData;

MnVibrationAssets mnVibration_804A0868;
MnVibrationJointAssets mnVibration_804A0878;
MnVibrationJointAssets mnVibration_804A0888;
MnVibrationJointAssets mnVibration_804A0898;

// --- Function Implementation ---

HSD_JObj* mnVibration_802474C4(s32 count)
{
    HSD_JObj* temp_r4;
    HSD_JObj* var_r4;
    MnVibrationData* data;

    data = mnVibration_804D6C28->user_data;
    temp_r4 = data->jobjs[17];
    if (temp_r4 == NULL) {
        var_r4 = NULL;
    } else {
        var_r4 = temp_r4->child;
    }
    for (; count > 0; count--) {
        if (var_r4 == NULL) {
            var_r4 = NULL;
        } else {
            var_r4 = var_r4->next;
        }
    }
    return var_r4;
}

void fn_80247510(HSD_GObj* gobj)
{
    MnVibrationData* data = mnVibration_804D6C28->user_data;
    u8 var_ctr;
    s32 i;
    u64 inputs;
    u64 inputs_repeat;
    HSD_JObj* cursor_jobj;
    HSD_JObj* panel_jobj;
    u8 cursor_row;
    u8 scroll_offset;
    s32 name_count;
    s32 name_idx;
    u8 rumble_setting;
    HSD_JObj* jobj;

    if (mn_804D6BC8.cooldown != 0) {
        Menu_DecrementAnimTimer();
        return;
    }

    Menu_GetAllInputs();

    // Handle B button - exit menu
    inputs = gm_801A36A0(4);
    if (inputs & 2) {
        MnVibrationData* exit_data;
        lbAudioAx_80024030(0);
        mn_804A04F0.entering_menu = 0;
        mn_80229894(4, 0, 3);
        // Clean up text objects - reload data pointer
        exit_data = mnVibration_804D6C28->user_data;
        for (i = 0; i < 8; i++) {
            HSD_SisLib_803A5CC4(exit_data->texts[i]);
        }
        if (exit_data->title_text != NULL) {
            HSD_SisLib_803A5CC4(exit_data->title_text);
        }
        HSD_GObjPLink_80390228(mnVibration_804D6C28);
        HSD_PadRumbleRemoveAll();
        lb_8001CE00();
        return;
    }

    // Check animation timer
    if (data->x0[0] < ((AnimLoopSettings*) &mnVibration_803EECE0)->end_frame) {
        data->x0[0]++;
        return;
    }

    // Check A button per controller for rumble toggle
    for (i = 0; i < 4; i++) {
        if (data->x0[i + 2] == 0) {
            inputs = gm_801A36A0(i);
            if (inputs & 1) {
                HSD_JObj* temp_jobj;
                lbAudioAx_80024030(1);
                if (GetRumbleSettingOfPort(i) != 0) {
                    gmMainLib_8015ED4C(i, 0);
                    rumble_setting = GetRumbleSettingOfPort(i);
                    temp_jobj =
                        ((MnVibrationData*) mnVibration_804D6C28->user_data)
                            ->jobjs[23];
                    if (temp_jobj == NULL) {
                        jobj = NULL;
                    } else {
                        jobj = temp_jobj->child;
                    }
                    var_ctr = i;
                    if ((s32) i > 0) {
                        do {
                            if (jobj == NULL) {
                                jobj = NULL;
                            } else {
                                jobj = jobj->next;
                            }
                            var_ctr -= 1;
                        } while (var_ctr != 0);
                    }
                    lb_80011E24(jobj, &panel_jobj, 2, -1,
                                (f32) rumble_setting);
                    HSD_JObjReqAnimAll(panel_jobj, (f32) rumble_setting);
                    HSD_JObjAnimAll(panel_jobj);
                    HSD_PadRumbleRemoveAll();
                    HSD_PadRumbleOffN(i);
                    return;
                } else {
                    gmMainLib_8015ED4C(i, 1);
                    rumble_setting = GetRumbleSettingOfPort(i);
                    temp_jobj =
                        ((MnVibrationData*) mnVibration_804D6C28->user_data)
                            ->jobjs[23];
                    if (temp_jobj == NULL) {
                        jobj = NULL;
                    } else {
                        jobj = temp_jobj->child;
                    }
                    var_ctr = i;
                    if ((s32) i > 0) {
                        do {
                            if (jobj == NULL) {
                                jobj = NULL;
                            } else {
                                jobj = jobj->next;
                            }
                            var_ctr -= 1;
                        } while (var_ctr != 0);
                    }
                    lb_80011E24(jobj, &panel_jobj, 2, -1,
                                (f32) rumble_setting);
                    HSD_JObjReqAnimAll(panel_jobj, (f32) rumble_setting);
                    HSD_JObjAnimAll(panel_jobj);
                    HSD_PadRumbleAdd(i, 0, 14, 0, &mnVibration_804D4FF0);
                    return;
                }
            }
        }
    }

    // Handle name list navigation if names exist
    if (GetNameCount() == 0) {
        return;
    }

    // Check for up/down navigation
    for (i = 0; i < 4; i++) {
        inputs = gm_801A36A0(i);
        if ((inputs & 0x40) && data->x0[i + 2] == 1) {
            lbAudioAx_80024030(2);
            data->x0[i + 2] = 0;
            panel_jobj = data->jobjs[mnVibration_804D4FE8[i]];
            HSD_JObjReqAnimAll(panel_jobj, (f32) data->x0[i + 2]);
            HSD_JObjAnimAll(panel_jobj);
        } else if (inputs & 0x80) {
            if (data->x0[i + 2] == 0) {
                lbAudioAx_80024030(2);
                data->x0[i + 2] = 1;
                panel_jobj = data->jobjs[mnVibration_804D4FE8[i]];
                HSD_JObjReqAnimAll(panel_jobj, (f32) data->x0[i + 2]);
                HSD_JObjAnimAll(panel_jobj);
            }
        }
    }

    // Collect repeated inputs from all controllers with L held
    inputs_repeat = 0;
    for (i = 0; i < 4; i++) {
        if (data->x0[i + 2] == 1) {
            inputs_repeat |= gm_801A36C0(i);
        }
    }

    // Handle A button to toggle rumble setting for selected name
    if (inputs_repeat & 1) {
        lbAudioAx_80024030(1);
        cursor_row = data->x0[1];
        scroll_offset = data->scroll_offset;
        name_count = GetNameCount();
        if (name_count < 8 && cursor_row >= name_count) {
            name_idx = 0xFF;
        } else {
            name_idx = scroll_offset + cursor_row;
            if (name_count <= name_idx) {
                name_idx = 0xFF;
            }
        }
        if (GetPersistentNameData(name_idx)->x1A1 == 1) {
            GetPersistentNameData(name_idx)->x1A1 = 0;
        } else {
            GetPersistentNameData(name_idx)->x1A1 = 1;
        }
        rumble_setting = GetPersistentNameData(name_idx)->x1A1;
        jobj = mnVibration_802474C4(data->x0[1]);
        HSD_JObjReqAnimAll(jobj, (f32) rumble_setting);
        HSD_JObjAnimAll(jobj);
        return;
    }

    // Handle up navigation
    if (inputs_repeat & 0x10) {
        cursor_row = data->x0[1];
        if (cursor_row != 0) {
            scroll_offset = data->scroll_offset;
            name_count = GetNameCount();
            if (name_count < 8 && cursor_row - 1 >= name_count) {
                name_idx = 0xFF;
            } else {
                name_idx = scroll_offset + cursor_row - 1;
                if (name_count <= name_idx) {
                    name_idx = 0xFF;
                }
            }
            if (name_idx != 0xFF) {
                lbAudioAx_80024030(2);
                data->x0[1]--;
                cursor_jobj = data->cursor_gobj->hsd_obj;
                HSD_JObjSetTranslateX(
                    cursor_jobj, HSD_JObjGetTranslationX(data->jobjs[17]));
                HSD_JObjSetTranslateY(
                    cursor_jobj, (HSD_JObjGetTranslationY(data->jobjs[18]) -
                                  HSD_JObjGetTranslationY(data->jobjs[17])) *
                                         (f32) data->x0[1] +
                                     HSD_JObjGetTranslationY(data->jobjs[17]));
                HSD_JObjSetTranslateZ(
                    cursor_jobj, HSD_JObjGetTranslationZ(data->jobjs[17]));
            }
        } else if (GetNameCount() > 8 && data->scroll_offset != 0) {
            lbAudioAx_80024030(2);
            data->scroll_offset--;
            mnVibration_80248644(mnVibration_804D6C28);
        }
    }

    // Handle down navigation
    if (inputs_repeat & 0x20) {
        cursor_row = data->x0[1];
        if (cursor_row < 7) {
            scroll_offset = data->scroll_offset;
            name_count = GetNameCount();
            if (name_count < 8 && cursor_row + 1 >= name_count) {
                name_idx = 0xFF;
            } else {
                name_idx = scroll_offset + cursor_row + 1;
                if (name_count <= name_idx) {
                    name_idx = 0xFF;
                }
            }
            if (name_idx != 0xFF) {
                lbAudioAx_80024030(2);
                data->x0[1]++;
                cursor_jobj = data->cursor_gobj->hsd_obj;
                HSD_JObjSetTranslateX(
                    cursor_jobj, HSD_JObjGetTranslationX(data->jobjs[17]));
                HSD_JObjSetTranslateY(
                    cursor_jobj, (HSD_JObjGetTranslationY(data->jobjs[18]) -
                                  HSD_JObjGetTranslationY(data->jobjs[17])) *
                                         (f32) data->x0[1] +
                                     HSD_JObjGetTranslationY(data->jobjs[17]));
                HSD_JObjSetTranslateZ(
                    cursor_jobj, HSD_JObjGetTranslationZ(data->jobjs[17]));
            }
        } else if (GetNameCount() > 8) {
            scroll_offset = data->scroll_offset;
            name_count = GetNameCount();
            if (name_count < 8 && 8 <= name_count) {
                name_idx = 0xFF;
            } else {
                name_idx = scroll_offset + 8;
                if (name_count <= name_idx) {
                    name_idx = 0xFF;
                }
            }
            if (name_idx != 0xFF) {
                lbAudioAx_80024030(2);
                data->scroll_offset++;
                if (data->scroll_offset >= GetNameCount()) {
                    data->scroll_offset = 0;
                }
                mnVibration_80248644(mnVibration_804D6C28);
            }
        }
    }
}

void fn_80248084(HSD_GObj* gobj)
{
    if (mn_804A04F0.cur_menu != 0x13) {
        HSD_GObjPLink_80390228(gobj);
    }
}

void mnVibration_802480B4(HSD_JObj* arg0, u8 arg1, u8 arg2)
{
    HSD_JObj* sp14;
    HSD_JObj* sp10;
    u8 temp_ret;
    MnVibrationFloatData* floats = &mnVibration_803EECE0;

    lb_80011E24(arg0, &sp14, 1, -1);
    if (arg2 != 0) {
        HSD_JObjReqAnimAll(sp14, (f32) arg1);
        HSD_JObjAnimAll(sp14);
        if (GetRumbleSettingOfPort((s32) arg1) != 0) {
            HSD_JObjReqAnimAll(sp14, floats->x1C);
        } else {
            HSD_JObjReqAnimAll(sp14, floats->x18);
        }
        mn_8022F3D8(sp14, 0xFF, MOBJ_MASK);
        HSD_JObjAnimAll(sp14);
    } else {
        HSD_JObjReqAnimAll(sp14, mnVibration_804DC020);
        HSD_JObjAnimAll(sp14);
        HSD_JObjReqAnimAll(sp14, floats->x1C);
        mn_8022F3D8(sp14, 0xFF, MOBJ_MASK);
        HSD_JObjAnimAll(sp14);
    }
    lb_80011E24(arg0, &sp14, 3, -1);
    if (arg2 != 0) {
        HSD_JObjReqAnimAll(sp14, (f32) (arg1 + 1));
    } else {
        HSD_JObjReqAnimAll(sp14, mnVibration_804DC020);
    }
    HSD_JObjAnimAll(sp14);
    if (arg2 != 0) {
        temp_ret = GetRumbleSettingOfPort((s32) arg1);
        lb_80011E24(arg0, &sp10, 2, -1);
        HSD_JObjReqAnimAll(sp10, (f32) temp_ret);
        HSD_JObjAnimAll(sp10);
        return;
    }
    lb_80011E24(arg0, &sp14, 2, -1);
    HSD_JObjReqAnimAll(sp14, mnVibration_804DC020);
    HSD_JObjAnimAll(sp14);
}

void mnVibration_8024829C(HSD_GObj* arg0)
{
    MnVibrationData* data;
    MnVibrationJointAssets* assets = &mnVibration_804A0878;
    HSD_JObj* jobj0;
    HSD_JObj* jobj1;
    f32 base_x;
    f32 spacing;
    HSD_JObj* new_jobj;
    s32 i;
    s32 connected;

    data = arg0->user_data;
    jobj0 = data->jobjs[23];
    base_x = HSD_JObjGetTranslationX(jobj0);
    jobj1 = data->jobjs[24];
    spacing = HSD_JObjGetTranslationX(jobj1) - base_x;
    i = 0;
    do {
        new_jobj = HSD_JObjLoadJoint(assets->joint);
        HSD_JObjAddAnimAll(new_jobj, assets->animjoint, assets->matanim,
                           assets->shapeanim);
        HSD_JObjReqAnimAll(new_jobj, 0.0f);
        HSD_JObjAnimAll(new_jobj);
        HSD_JObjSetTranslateX(new_jobj, spacing * (f32) i);
        if ((s8) (u8) HSD_PadCopyStatus[(u8) i].err != 0) {
            connected = 0;
        } else {
            connected = 1;
        }
        mnVibration_802480B4(new_jobj, (u8) i, (u8) connected);
        HSD_JObjSetFlagsAll(new_jobj, 0x10);
        HSD_JObjAddChild(data->jobjs[23], new_jobj);
        i += 1;
    } while (i < 4);
}

void mnVibration_80248444(HSD_GObj* arg0, u8 arg1, u8 arg2)
{
    Point3d sp20;
    MnVibrationData* data;
    MnVibrationJointAssets* assets;
    HSD_JObj* jobj17;
    HSD_JObj* jobj18;
    HSD_Text* text;
    u8 name_flag;
    HSD_JObj* new_jobj;
    f32 spacing;
    PAD_STACK(8);

    assets = &mnVibration_804A0888;
    data = arg0->user_data;
    name_flag = GetPersistentNameData((s32) arg1)->x1A1;
    jobj17 = data->jobjs[17];
    spacing = HSD_JObjGetTranslationY(jobj17);
    jobj18 = data->jobjs[18];
    spacing = HSD_JObjGetTranslationY(jobj18) - spacing;
    lb_8000B1CC(data->jobjs[17], &mnVibration_803EED04, &sp20);
    text = HSD_SisLib_803A6754(0, 1);
    data->texts[arg2] = text;
    text->pos_x = sp20.x;
    text->pos_y = -(spacing * (f32) arg2 + sp20.y);
    text->pos_z = sp20.z;
    text->font_size.x = 0.03f;
    text->font_size.y = 0.03f;
    HSD_SisLib_803A6B98(text, 0.0f, 0.0f, GetNameText(arg1));
    new_jobj = HSD_JObjLoadJoint(assets->joint);
    HSD_JObjAddAnimAll(new_jobj, assets->animjoint, assets->matanim,
                       assets->shapeanim);
    HSD_JObjReqAnimAll(new_jobj, (f32) name_flag);
    HSD_JObjAnimAll(new_jobj);
    HSD_JObjSetTranslateY(new_jobj, spacing * (f32) arg2);
    HSD_JObjAddChild(data->jobjs[17], new_jobj);
}

s32 mnVibration_80248644(HSD_GObj* arg0)
{
    s32 i;
    MnVibrationData* data;
    HSD_Text** ptr1;
    HSD_Text** ptr2;
    s32 zero;
    HSD_JObj* jobj17;
    HSD_JObj* child;
    s32 j;
    u8 scroll_offset;
    s32 name_idx;
    s32 count;

    i = 0;
    zero = 0;
    data = arg0->user_data;
    ptr2 = data->texts;
    ptr1 = data->texts + i;
    do {
        if (*ptr2 != NULL) {
            HSD_SisLib_803A5CC4(*ptr1);
            *ptr2 = NULL;
        }
        i += 1;
        ptr2++;
        ptr1++;
    } while (i < 8);
    jobj17 = data->jobjs[17];
    if (jobj17 == NULL) {
        child = NULL;
    } else {
        child = jobj17->child;
    }
    if (child != NULL) {
        if (jobj17 == NULL) {
            jobj17 = NULL;
        } else {
            jobj17 = jobj17->child;
        }
        HSD_JObjRemoveAll(jobj17);
    }
    j = 0;
    do {
        scroll_offset = data->scroll_offset;
        count = GetNameCount();
        if ((count < 8) && (j >= count)) {
            name_idx = 0xFF;
        } else {
            name_idx = scroll_offset + j;
            if (count <= name_idx) {
                name_idx = 0xFF;
            } else {
                name_idx = (u8) name_idx;
            }
        }
        if ((u8) name_idx != 0xFF) {
            mnVibration_80248444(arg0, (u8) name_idx, (u8) j);
        }
        j += 1;
    } while (j < 8);
    return count;
}

static AnimLoopSettings mnVibration_803EECEC = { 50.0f, 70.0f, -0.1f };

void fn_80248748(HSD_GObj* gobj)
{
    MnVibrationData* data = gobj->user_data;
    f32 frame;
    PAD_STACK(8);

    frame = mn_8022ED6C(data->jobjs[1], &mnVibration_803EECEC);
    if (frame >= mnVibration_803EECEC.end_frame) {
        HSD_GObjPLink_80390228(gobj);
    }
}

static f32 mnVibration_803EECF8[3] = { 0.0f, 14.0f, -0.1f };

void fn_802487A8(HSD_GObj* gobj)
{
    HSD_JObj* sp44;
    HSD_JObj* temp_r27;
    HSD_JObj* var_r3_2;
    s32 var_r24;
    u16* var_r25;
    u8 var_r23;
    u8 var_r3;
    u8* temp_r31;
    void* var_r26;
    void* var_r3_3;
    PAD_STACK(56);

    temp_r31 = gobj->user_data;
    if ((u8) mn_804A04F0.cur_menu != 0x13) {
        HSD_GObjProc* proc;
        HSD_GObjProc_8038FE24(HSD_GObj_804D7838);
        proc = HSD_GObjProc_8038FD54(gobj, fn_80248748, 0);
        proc->flags_3 = HSD_GObj_804D783C;
        return;
    }
    var_r24 = 0;
    do {
        void* temp_jobj;
        temp_jobj = ((MnVibrationData*) gobj->user_data)->jobjs[23];
        if (temp_jobj == NULL) {
            var_r3_2 = NULL;
        } else {
            var_r3_2 = ((HSD_JObj*) temp_jobj)->child;
        }
        {
            s32 i;
            for (i = 0; i < var_r24; i++) {
                if (var_r3_2 == NULL) {
                    var_r3_2 = NULL;
                } else {
                    var_r3_2 = var_r3_2->next;
                }
            }
        }
        lb_80011E24(var_r3_2, &sp44, 1, -1);
        if (GetRumbleSettingOfPort(var_r24) != 0) {
            mn_8022EC18(sp44, mnVibration_803EECF8, MOBJ_MASK);
        } else {
            HSD_JObjReqAnimAll(sp44, 0.0f);
            mn_8022F3D8(sp44, 0xFF, MOBJ_MASK);
            HSD_JObjAnimAll(sp44);
        }
        var_r24 += 1;
    } while (var_r24 < 4);
    var_r23 = 0;
    var_r25 = mnVibration_804D4FE8;
    do {
        // Force mulli pattern with explicit offset computation
        var_r3 = *((u8*)((u8*)HSD_PadCopyStatus + (u8)var_r23 * 0x44) + 0x41);
        if ((((s8) var_r3 != 0) && (temp_r31[var_r23 + 6] != 0)) ||
            (((s8) var_r3 == 0) && (temp_r31[var_r23 + 6] == 0)))
        {
            if ((s8) var_r3 != 0) {
                HSD_JObjSetFlagsAll(
                    ((MnVibrationData*) temp_r31)->jobjs[*var_r25], 0x10);
                {
                    void* temp_jobj2;
                    temp_jobj2 =
                        ((MnVibrationData*) gobj->user_data)->jobjs[23];
                    if (temp_jobj2 == NULL) {
                        var_r3_3 = NULL;
                    } else {
                        var_r3_3 = ((HSD_JObj*) temp_jobj2)->child;
                    }
                }
                {
                    s32 i;
                    for (i = 0; i < var_r23; i++) {
                        if (var_r3_3 == NULL) {
                            var_r3_3 = NULL;
                        } else {
                            var_r3_3 = ((HSD_JObj*) var_r3_3)->next;
                        }
                    }
                }
                mnVibration_802480B4((HSD_JObj*) var_r3_3, var_r23, 0);
                temp_r31[var_r23 + 6] = 0;
            } else {
                HSD_JObjClearFlagsAll(
                    ((MnVibrationData*) temp_r31)->jobjs[*var_r25], 0x10);
                var_r26 = NULL;
                temp_r31[var_r23 + 2] = 0;
                temp_r27 = ((MnVibrationData*) mnVibration_804D6C28->user_data)
                               ->jobjs[mnVibration_804D4FE8[var_r23]];
                HSD_JObjReqAnimAll(temp_r27, (f32) temp_r31[var_r23 + 2]);
                HSD_JObjAnimAll(temp_r27);
                {
                    HSD_JObj* temp_jobj3;
                    temp_jobj3 =
                        ((MnVibrationData*) gobj->user_data)->jobjs[23];
                    if (temp_jobj3 != NULL) {
                        var_r26 = temp_jobj3->child;
                    }
                }
                {
                    s32 i;
                    for (i = 0; i < var_r23; i++) {
                        if (var_r26 == NULL) {
                            var_r26 = NULL;
                        } else {
                            var_r26 = ((HSD_JObj*) var_r26)->next;
                        }
                    }
                }
                mnVibration_802480B4((HSD_JObj*) var_r26, var_r23, 1);
                temp_r31[var_r23 + 6] = 1;
            }
        }
        var_r23 += 1;
        var_r25 += 1;
    } while ((s32) var_r23 < 4);
}

void fn_80248A78(HSD_GObj* arg0)
{
    MnVibrationData* temp_r30;
    f32 frame;
    HSD_JObj* jobj;
    HSD_JObj* jobj2;
    HSD_JObj* jobj3;
    HSD_JObj* jobj4;
    HSD_GObj* cursor_gobj;
    HSD_JObj* cursor_jobj;
    HSD_JObj* jobj17;
    HSD_JObj* jobj18;
    f32 base_y;
    f32 spacing;
    f32 temp_x;
    f32 temp_y;
    f32 temp_z;
    u8 cursor_row;
    PAD_STACK(64);

    temp_r30 = arg0->user_data;
    frame = mn_8022ED6C(temp_r30->jobjs[1],
                        (AnimLoopSettings*) &mnVibration_803EECE0);
    if (frame == 10.0f) {
        jobj = ((MnVibrationData*) arg0->user_data)->jobjs[23];
        if (jobj == NULL) {
            jobj = NULL;
        } else {
            jobj = jobj->child;
        }
        {
            s32 i = 0;
            while (i < 0) {
                if (jobj == NULL) {
                    jobj = NULL;
                } else {
                    jobj = jobj->next;
                }
                i++;
            }
        }
        HSD_JObjClearFlagsAll(jobj, 0x10U);
        if ((u8) temp_r30->x6[0] != 0) {
            HSD_JObjClearFlagsAll(temp_r30->jobjs[22], 0x10U);
        }
    } else if (frame == 11.0f) {
        jobj = ((MnVibrationData*) arg0->user_data)->jobjs[23];
        if (jobj == NULL) {
            jobj = NULL;
        } else {
            jobj = jobj->child;
        }
        if (jobj == NULL) {
            jobj = NULL;
        } else {
            jobj = jobj->next;
        }
        HSD_JObjClearFlagsAll(jobj, 0x10U);
        if ((u8) temp_r30->x6[1] != 0) {
            HSD_JObjClearFlagsAll(temp_r30->jobjs[21], 0x10U);
        }
    } else if (frame == 12.0f) {
        jobj = ((MnVibrationData*) arg0->user_data)->jobjs[23];
        if (jobj == NULL) {
            jobj2 = NULL;
        } else {
            jobj2 = jobj->child;
        }
        if (jobj2 == NULL) {
            jobj3 = NULL;
        } else {
            jobj3 = jobj2->next;
        }
        if (jobj3 == NULL) {
            jobj4 = NULL;
        } else {
            jobj4 = jobj3->next;
        }
        HSD_JObjClearFlagsAll(jobj4, 0x10U);
        if ((u8) temp_r30->x6[2] != 0) {
            HSD_JObjClearFlagsAll(temp_r30->jobjs[20], 0x10U);
        }
    } else if (frame == 13.0f) {
        jobj = ((MnVibrationData*) arg0->user_data)->jobjs[23];
        if (jobj == NULL) {
            jobj2 = NULL;
        } else {
            jobj2 = jobj->child;
        }
        if (jobj2 == NULL) {
            jobj3 = NULL;
        } else {
            jobj3 = jobj2->next;
        }
        if (jobj3 == NULL) {
            jobj4 = NULL;
        } else {
            jobj4 = jobj3->next;
        }
        if (jobj4 == NULL) {
            jobj = NULL;
        } else {
            jobj = jobj4->next;
        }
        HSD_JObjClearFlagsAll(jobj, 0x10U);
        if ((u8) temp_r30->x6[3] != 0) {
            HSD_JObjClearFlagsAll(temp_r30->jobjs[19], 0x10U);
        }
    } else if (frame == 14.0f) {
        if (GetNameCount() != 0) {
            MnVibrationData* data2;
            MnVibrationData* data3;
            MnVibrationAssets* assets;
            HSD_JObj* loaded_joint;
            mnVibration_80248644(arg0);
            assets = &mnVibration_804A0868;
            data2 = arg0->user_data;
            cursor_gobj = GObj_Create(6U, 7U, 0x80U);
            data2->cursor_gobj = cursor_gobj;
            loaded_joint = HSD_JObjLoadJoint(assets->SCl_Top_joint);
            HSD_GObjObject_80390A70(
                (HSD_GObj*) ((u8*) cursor_gobj + 0), HSD_GObj_804D7849,
                (HSD_JObj*) ((u8*) loaded_joint + 0));
            GObj_SetupGXLink(cursor_gobj, HSD_GObj_JObjCallback, 4U, 0x80U);
            HSD_GObjProc_8038FD54(cursor_gobj, fn_80248084, 0U);
            data3 = arg0->user_data;
            cursor_jobj = cursor_gobj->hsd_obj;
            jobj17 = data3->jobjs[17];
            cursor_row = data2->x0[1];
            base_y = mnVibration_JObjGetTranslationY(jobj17);
            jobj18 = data3->jobjs[18];
            jobj17 = data3->jobjs[17];
            spacing = mnVibration_JObjGetTranslationY(jobj18) - base_y;
            temp_x = mnVibration_JObjGetTranslationX(jobj17);
            mnVibration_JObjSetTranslateX(cursor_jobj, temp_x);
            jobj17 = data3->jobjs[17];
            temp_y = (spacing * (f32) cursor_row) +
                     mnVibration_JObjGetTranslationY(jobj17);
            mnVibration_JObjSetTranslateY(cursor_jobj, temp_y);
            jobj17 = data3->jobjs[17];
            temp_z = mnVibration_JObjGetTranslationZ(jobj17);
            mnVibration_JObjSetTranslateZ(cursor_jobj, temp_z);
        }
    }

    if (frame >= ((AnimLoopSettings*) &mnVibration_803EECE0)->end_frame) {
        HSD_GObjProc* proc;
        HSD_GObjProc_8038FE24(HSD_GObj_804D7838);
        proc = HSD_GObjProc_8038FD54(arg0, fn_802487A8, 0);
        proc->flags_3 = HSD_GObj_804D783C;
    }
}

void mnVibration_80248ED4(s32 arg0)
{
    MnVibrationJointAssets* assets;
    HSD_GObj* gobj;
    HSD_JObj* jobj;
    HSD_Text* text;
    s32 i;
    MnVibrationData* data;
    PAD_STACK(32);

    (void) arg0;
    assets = &mnVibration_804A0898;
    gobj = GObj_Create(6, 7, 0x80);
    mnVibration_804D6C28 = gobj;
    jobj = HSD_JObjLoadJoint(assets->joint);
    HSD_GObjObject_80390A70(gobj, HSD_GObj_804D7849, jobj);
    GObj_SetupGXLink(gobj, HSD_GObj_JObjCallback, 4, 0x80);
    HSD_JObjAddAnimAll(jobj, assets->animjoint, assets->matanim,
                       assets->shapeanim);
    HSD_JObjReqAnimAll(jobj, 0.0f);
    data = HSD_MemAlloc(sizeof(MnVibrationData));
    if (data == NULL) {
        OSReport("couldn't allocate\n");
        __assert("mnvibration.c", 0x3A7, "data");
    }
    data->x0[0] = 0;
    data->x0[1] = 0;
    data->x0[2] = 0;
    data->x6[0] = (HSD_PadCopyStatus[0].err != 0) ? 0 : 1;
    data->x0[3] = 0;
    data->x6[1] = (HSD_PadCopyStatus[1].err != 0) ? 0 : 1;
    data->x0[4] = 0;
    data->x6[2] = (HSD_PadCopyStatus[2].err != 0) ? 0 : 1;
    data->x0[5] = 0;
    data->x6[3] = (HSD_PadCopyStatus[3].err != 0) ? 0 : 1;
    data->scroll_offset = 0;
    data->texts[0] = NULL;
    data->texts[1] = NULL;
    data->texts[2] = NULL;
    data->texts[3] = NULL;
    data->texts[4] = NULL;
    data->texts[5] = NULL;
    data->texts[6] = NULL;
    data->texts[7] = NULL;
    GObj_InitUserData(gobj, 0, HSD_Free, data);
    i = 0;
    do {
        lb_80011E24(jobj, &data->jobjs[i], i, -1);
        i += 1;
    } while (i < 0x19);
    HSD_JObjSetFlagsAll(data->jobjs[22], 0x10);
    HSD_JObjSetFlagsAll(data->jobjs[21], 0x10);
    HSD_JObjSetFlagsAll(data->jobjs[20], 0x10);
    HSD_JObjSetFlagsAll(data->jobjs[19], 0x10);
    HSD_GObjProc_8038FD54(gobj, (void (*)(HSD_GObj*)) fn_80248A78, 0);
    mnVibration_8024829C(gobj);
    text = data->title_text;
    if (text != NULL) {
        HSD_SisLib_803A5CC4(text);
    }
    text =
        HSD_SisLib_803A5ACC(0, 1, -9.5f, 9.1f, 17.0f, 364.68332f, 38.38772f);
    data->title_text = text;
    text->font_size.x = 0.0521f;
    text->font_size.y = 0.0521f;
    HSD_SisLib_803A6368(text, 0xA7);
}

void mnVibration_80249174(int arg0)
{
    int saved_arg = arg0;
    HSD_GObj* gobj;
    u8* gobj_flags_ptr;
    PAD_STACK(8);

    mn_804D6BC8.cooldown = 5;
    mn_804A04F0.prev_menu = mn_804A04F0.cur_menu;
    mn_804A04F0.cur_menu = 19;
    mn_804A04F0.hovered_selection = 0;

    // Correct Order: Title -> SCl -> Option -> Panel
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

    mnVibration_80248ED4(saved_arg);

    gobj = GObj_Create(0, 1, 0x80);
    HSD_GObjProc_8038FD54(gobj, (void (*)(HSD_GObj*)) fn_80247510, 0);

    gobj_flags_ptr = (u8*) gobj + 0xD;
    *gobj_flags_ptr =
        (*gobj_flags_ptr & 0xCF) | ((HSD_GObj_804D783C << 4) & 0x30);
}
