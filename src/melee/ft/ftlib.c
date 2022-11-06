#include <melee/ft/ftlib.h>

#include <melee/ft/ft_unknown_006.h>
#include <melee/ft/ftdata.h>
#include <melee/gm/code_801601C4.h>
#include <melee/lb/lbunknown_001.h>
#include <melee/pl/player.h>
#include <sysdolphin/baselib/jobj.h>

extern s8 lbl_803C26FC[];

s32 func_800860C4(void)
{
    s32 ret = 0;
    HSD_GObj* cur;
    for (cur = lbl_804D782C->x20_fighters; cur != NULL; cur = cur->next) {
        ret++;
    }
    return ret;
}

BOOL func_800860E8(void)
{
    u32 unused[2];
    HSD_GObj* cur;
    for (cur = lbl_804D782C->x20_fighters; cur != NULL; cur = cur->next) {
        if (func_800872A4(cur) == 0x1B) {
            return TRUE;
        }
    }
    return FALSE;
}

BOOL func_80086140(void)
{
    u32 unused[2];
    HSD_GObj* cur;
    for (cur = lbl_804D782C->x20_fighters; cur != NULL; cur = cur->next) {
        if (func_800872A4(cur) == 0x1C) {
            return TRUE;
        }
    }
    return FALSE;
}

#include <melee/gm/code_801601C4.h>

HSD_GObj* func_80086198(HSD_GObj* gobj)
{
    Fighter* fp;
    HSD_GObj* cur;
    HSD_GObj* result;
    Fighter* fp2;
    s32 min_percent = 999;
    int unused[4];

    if (gobj != NULL) {
        fp = gobj->user_data;
    } else {
        fp = NULL;
    }

    result = NULL;
    for (cur = lbl_804D782C->x20_fighters; cur != NULL; cur = cur->next) {
        // skip if same player
        if (func_80086FD4(gobj, cur)) {
            continue;
        }
        fp2 = cur->user_data;
        if (fp2->x221F_flag.bits.b3) {
            continue;
        }
        // skip if same team
        if (func_8016B168() && fp != NULL &&
            fp2->x61B_team == fp->x61B_team) {
            continue;
        }

        if (fp2->dmg.x1830_percent < min_percent) {
            min_percent = fp2->dmg.x1830_percent;
            result = cur;
        }
    }
    return result;
}

// get closest opposing fp?
HSD_GObj* func_8008627C(Vec3* v, HSD_GObj* gobj)
{
    Vec3 cur_v;
    f32 dist;
    f32 dx;
    f32 dy;
    Fighter* cur_fp;
    Fighter* fp;
    HSD_GObj* cur;
    HSD_GObj* result;
    u32 unused[4];

    f32 min_dist = FLT_MAX;

    if (gobj != NULL) {
        fp = gobj->user_data;
    } else {
        fp = NULL;
    }

    result = NULL;
    for (cur = lbl_804D782C->x20_fighters; cur != NULL; cur = cur->next) {
        // skip if same player
        if (func_80086FD4(gobj, cur)) {
            continue;
        }
        cur_fp = cur->user_data;
        // skip if same team
        if (cur_fp->x221F_flag.bits.b3 ||
            func_8016B168() && fp != NULL && cur_fp->x61B_team == fp->x61B_team) {
            continue;
        }
        func_800866DC(cur, &cur_v);
        dx = v->x - cur_v.x;
        dy = v->y - cur_v.y;
        dist = (dx * dx) + (dy * dy);
        if (dist < min_dist) {
            min_dist = dist;
            result = cur;
        }
    }
    return result;
}

// get closest opposing fp, on given side (left/right)
HSD_GObj* func_80086368(Vec3* v, HSD_GObj* gobj, f32 arg8)
{
    Vec3 sp24;
    f32 dx, dy, diff;
    Fighter* cur_fp;
    Fighter* fp;
    HSD_GObj* cur;
    HSD_GObj* result;
    u32 unused[4];

    f32 min_diff = FLT_MAX;

    if (gobj != NULL) {
        fp = gobj->user_data;
    } else {
        fp = NULL;
    }

    result = NULL;
    for (cur = lbl_804D782C->x20_fighters; cur != NULL; cur = cur->next) {
        if (func_80086FD4(gobj, cur)) {
            continue;
        }
        cur_fp = cur->user_data;
        if (cur_fp->x221F_flag.bits.b3 ||
            func_8016B168() && fp != NULL && cur_fp->x61B_team == fp->x61B_team) {
            continue;
        }
        func_800866DC(cur, &sp24);
        if (arg8 == -1.0f && sp24.x > v->x ||
            arg8 == +1.0f && sp24.x < v->x) {
            continue;
        }

        dx = v->x - sp24.x;
        dy = v->y - sp24.y;
        diff = dx * dx + dy * dy;
        if (diff < min_diff) {
            min_diff = diff;
            result = cur;
        }
    }
    return result;
}

inline s32 sgn(f32 x)
{
    if (x < 0.0f) {
        return -1;
    } else {
        return +1;
    }
}

#include <sysdolphin/baselib/random.h>

f32 func_800864A8(Vec3* v, HSD_GObj* gobj)
{
    Vec3 sp20;
    Fighter* cur_fp;
    Fighter* fp;
    HSD_GObj* cur;
    s32 phi_r0;
    u32 unused[3];

    s32 result = 0;

    if (gobj != NULL) {
        fp = gobj->user_data;
    } else {
        fp = NULL;
    }

    for (cur = lbl_804D782C->x20_fighters; cur != NULL; cur = cur->next) {
        if (func_80086FD4(gobj, cur)) {
            continue;
        }
        cur_fp = cur->user_data;
        if (cur_fp->x221F_flag.bits.b3 ||
            func_8016B168() && fp != NULL && cur_fp->x61B_team == fp->x61B_team) {
            continue;
        }
        func_800866DC(cur, &sp20);
        result += sgn(sp20.x - v->x);
    }
    if (result == 0) {
        if (HSD_Randi(2) != 0) {
            phi_r0 = +1;
        } else {
            phi_r0 = -1;
        }
        result = phi_r0;
    }
    if (result < 0) {
        return -1.0f;
    } else {
        return +1.0f;
    }
}

f32 func_800865C0(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    return fp->facing_direction;
}

s32 func_800865CC(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    return fp->xE0_ground_or_air;
}

void func_800865D8(HSD_GObj* gobj, f32* x, f32* y)
{
    Fighter* fp = gobj->user_data;
    *x = fp->input.x620_lstick_x;
    *y = fp->input.x624_lstick_y;
}

#include <melee/ft/ftparts.h>

void* func_800865F0(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    return fp->x5E8_fighterBones[func_8007500C(fp, 4)].x0_jobj;
}

void* func_80086630(HSD_GObj* gobj, s32 i)
{
    Fighter* fp = gobj->user_data;
    return fp->x5E8_fighterBones[i].x0_jobj;
}

void func_80086644(HSD_GObj* gobj, Vec3* pos)
{
    Fighter* fp = gobj->user_data;
    *pos = fp->xB0_pos;
}

void func_80086664(HSD_GObj* gobj, Vec3* pos)
{
    Fighter* fp = gobj->user_data;
    fp->xB0_pos = *pos;
}

void func_80086684(HSD_GObj* gobj, Vec3* pos)
{
    Fighter* fp = gobj->user_data;
    *pos = fp->xBC_prevPos;
}

void ftData_SetScale(HSD_GObj* gobj, f32 val)
{
    u32 unused[2];
    Fighter* fp = gobj->user_data;
    fp->x34_scale.y = val;
    Fighter_UpdateModelScale(gobj);
    func_80080174(fp);
}

void func_800866DC(HSD_GObj* gobj, Vec3* v)
{
    Fighter* fp = gobj->user_data;
    struct attr* r4 = &fp->x110_attr;
    s32 i = fp->x10C_ftData->x0->x16C_idx;
    func_8000B1CC(func_80086630(gobj, i), &r4->x280, v);
}

void func_80086724(HSD_GObj* gobj, HSD_GObj* other)
{
    Fighter* fp = gobj->user_data;
    if (fp->x1974_heldItem != NULL || fp->x1978 != NULL) {
        func_8007E6DC(gobj, other, 1);
    }
}

void func_80086764(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    if (fp->x1984_heldItemSpec != NULL) {
        func_8007E82C(gobj);
    }
}

HSD_GObj* func_80086794(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    return fp->x1974_heldItem;
}

BOOL func_800867A0(HSD_GObj* gobj, HSD_GObj* arg1)
{
    Fighter* fp = gobj->user_data;
    if (fp->x1974_heldItem == arg1 || fp->x1978 == arg1) {
        return TRUE;
    } else {
        return FALSE;
    }
}

HSD_GObj* func_800867CC(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    return fp->x1984_heldItemSpec;
}

BOOL func_800867D8(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    return fp->x221D_flag.bits.b4;
}

void func_800867E8(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    Fighter_ResetInputData_80068854(gobj);
    fp->x221D_flag.bits.b4 = 1;
}

void func_80086824(void)
{
    u32 unused[4];
    HSD_GObj* cur;
    for (cur = lbl_804D782C->x20_fighters; cur != NULL; cur = cur->next) {
        func_800867E8(cur);
    }
}

void func_8008688C(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    fp->x221D_flag.bits.b4 = 0;
}

void func_800868A4(void)
{
    HSD_GObj* cur;
    for (cur = lbl_804D782C->x20_fighters; cur != NULL; cur = cur->next) {
        func_8008688C(cur);
    }
}

BOOL func_800868D4(HSD_GObj* gobj, HSD_GObj* arg1) {
    Fighter* fp = gobj->user_data;
    if ((fp->x1974_heldItem != arg1) && (fp->x197C != arg1) && (fp->x1980 != arg1)) {
        return 1;
    }
    if (fp->x221E_flag.bits.b0 || fp->x221E_flag.bits.b5 ||
        !fp->x221E_flag.bits.b3 && fp->x1974_heldItem == arg1 ||
        (!fp->x221E_flag.bits.b4 && (fp->x197C == arg1 || fp->x1980 == arg1))) {
        return 0;
    } else {
        return 1;
    }
}

BOOL func_80086960(HSD_GObj* arg)
{
    if (arg != NULL && arg->classifier == 4) {
        return TRUE;
    } else {
        return FALSE;
    }
}

CollData* func_80086984(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    return &fp->x6F0_collData;
}

inline void vector_add(Vec* dst, Vec* src, f32 x, f32 y, f32 z)
{
    dst->x = src->x + x;
    dst->y = src->y + y;
    dst->z = src->z + z;
}

void func_80086990(HSD_GObj* gobj, Vec3* v)
{
    Fighter* fp = gobj->user_data;
    f32 tmp = 0.5f * (fp->x6F0_collData.xA4_ecbCurrCorrect.top.y + fp->x6F0_collData.xA4_ecbCurrCorrect.bottom.y);
    vector_add(v, &fp->xB0_pos, 0.0f, tmp, 0.0f);
}

f32 func_800869D4(HSD_GObj* gobj)
{
    return Fighter_GetModelScale(gobj->user_data);
}

f32 func_800869F8(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    return fp->x34_scale.x * fp->x110_attr.x19C_ModelScaling;
}

f32 func_80086A0C(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    return fp->x34_scale.y;
}

BOOL func_80086A18(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    BOOL result = FALSE;
    switch (fp->x10_action_state_index) {
        case 0xB2:
        case 0xB3:
        case 0xB5:
            result = TRUE;
    }
    return result;
}

void func_80086A4C(HSD_GObj* gobj, f32 val)
{
    Fighter* fp = gobj->user_data;
    fp->dmg.x1958 = val;
}

BOOL func_80086A58(HSD_GObj* gobj, S32Pair* x)
{
    Fighter* fp = gobj->user_data;
    if (!fp->x2229_b3 && !fp->x2220_flag.bits.b7) {
        *x = fp->x2188;
    }
    return FALSE;
}

#include <melee/cm/camera.h>

BOOL func_80086A8C(HSD_GObj* gobj)
{
    u32 unused[2];
    struct {
        u8 x0_fill[0x28];
        void* unk28;
    }* temp_r3;

    Fighter* fp = gobj->user_data;
    if (!fp->x2229_b3 && !fp->x2220_flag.bits.b7) {
        temp_r3 = func_80030A50();
        if (temp_r3 != NULL) {
            void* temp_r30 = temp_r3->unk28;
            if (temp_r30 == HSD_CObjGetCurrent()) {
                if (func_80030CD8(fp->x890_cameraBox, &fp->x2188)) {
                    fp->x221F_flag.bits.b0 = 0;
                    return TRUE;
                }
                fp->x221F_flag.bits.b0 = 1;
                if (func_80030CFC(fp->x890_cameraBox, 15)) {
                    return TRUE;
                }
                return FALSE;
            }
        }
    }
    fp->x221F_flag.bits.b0 = 0;
    return TRUE;
}

BOOL func_80086B64(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    return fp->x221F_flag.bits.b0;
}

#include <melee/cm/camera.h>

CameraBox* func_80086B74(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    return fp->x890_cameraBox;
}

f32 func_80086B80(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    return fp->x890_cameraBox->x48.z;
}

void func_80086B90(HSD_GObj* gobj, Vec3* v)
{
    Fighter* fp = gobj->user_data;
    CameraBox* cam = fp->x890_cameraBox;
    *v = cam->x1C;
}

void func_80086BB4(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    CameraBox* cam = fp->x890_cameraBox;
    func_80031154(&cam->x10);
}

u8 func_80086BE0(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    return fp->xC_playerID;
}

void func_80086BEC(HSD_GObj* gobj, Vec3* v)
{
    Fighter* fp = gobj->user_data;
    *v = fp->xC8_pos_delta;
}

s32 func_80086C0C(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    return fp->x10_action_state_index;
}

#include <melee/lb/lbunknown_003.h>

inline void helper(HSD_GObj* gobj, s32 arg1, s32 arg2, s32 val)
{
    Fighter* fp = gobj->user_data;
    if (!Player_8003544C(fp->xC_playerID, fp->x221F_flag.bits.b4)) {
        return;
    }
    if (!fp->x221F_flag.bits.b3 && !fp->x2224_flag.bits.b2) {
        func_80014574(fp->x618_player_id, val, arg1, arg2);
    }
}

void func_80086C18(HSD_GObj* gobj, s32 arg1, s32 arg2)
{
    helper(gobj, arg1, arg2, 0);
}

void func_80086C9C(s32 arg0, s32 arg1)
{
    HSD_GObj* cur;
    u32 unused[4];
    for (cur = lbl_804D782C->x20_fighters; cur != NULL; cur = cur->next) {
        func_80086C18(cur, arg0, arg1);
    }
}

void func_80086D40(HSD_GObj* arg0, s32 arg1, s32 arg2)
{
    helper(arg0, arg1, arg2, 1);
}

void func_80086DC4(s32 arg0, s32 arg1)
{
    HSD_GObj* cur;
    u32 unused[4];
    for (cur = lbl_804D782C->x20_fighters; cur != NULL; cur = cur->next) {
        func_80086D40(cur, arg0, arg1);
    }
}

void func_80086E68(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    if (Player_8003544C(fp->xC_playerID, fp->x221F_flag.bits.b4)) {
        func_80378280(fp->x618_player_id, 1);
    }
}

s32 func_80086EB4(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    return fp->x61B_team;
}

BOOL func_80086EC0(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    return fp->x221C_flag.bits.b6;
}

BOOL func_80086ED0(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    if (fp->x221E_flag.bits.b0 || fp->x221E_flag.bits.b2 || Player_GetMoreFlagsBit4(fp->xC_playerID) ||
        fp->x2228_flag.bits.b2 || fp->x2229_b3 || fp->x2220_flag.bits.b7) {
        return FALSE;
    }
    return TRUE;
}

BOOL func_80086F4C(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    if (!fp->x221F_flag.bits.b2 && !fp->x221F_flag.bits.b1 && fp->x209A == 1) {
        return TRUE;
    } else {
        return FALSE;
    }
}

f32 func_80086F80(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    if (fp->x221E_flag.bits.b0) {
        return fp->x10C_ftData->x0->xFC;
    }
    return fp->x110_attr.x20C_NametagHeight;
}

BOOL func_80086FA8(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    switch (fp->x10_action_state_index) {
        case 0x78:
        case 0x79:
        case 0x7A:
        case 0x7B:
            return TRUE;
    }
    return FALSE;
}

BOOL func_80086FD4(HSD_GObj* gobj1, HSD_GObj* gobj2)
{
    Fighter* fp1;
    Fighter* fp2;
    if (gobj1 != NULL && gobj2 != NULL) {
        if (gobj1 == gobj2) {
            return TRUE;
        }
        fp1 = gobj1->user_data;
        fp2 = gobj2->user_data;
        if (fp1->xC_playerID == fp2->xC_playerID) {
            return TRUE;
        }
    }
    return FALSE;
}

BOOL func_8008701C(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    return fp->x221F_flag.bits.b3;
}

void func_8008702C(s32 arg0)
{
    func_80085560(arg0, 1);
}

void func_80087050(s32 arg0)
{
    func_80085560(arg0, -1);
}

BOOL func_80087074(HSD_GObj* gobj, Vec3* v)
{
    Fighter* fp = gobj->user_data;
    if (fp->dmg.x18B8 || fp->dmg.x18BC) {
        v->x = fp->dmg.x18B8;
        v->y = fp->dmg.x18BC;
        v->z = 0.0f;
        return TRUE;
    }
    return FALSE;
}

BOOL func_800870BC(HSD_GObj* gobj, void** val)
{
    Fighter* fp = gobj->user_data;
    if (fp->x61A_controller_index) {
        *val = p_ftCommonData->x6D8[fp->x61A_controller_index];
        return TRUE;
    }
    return FALSE;
}

void func_800870F0(HSD_GObj* gobj, s32 x)
{
    Fighter* fp = gobj->user_data;
    fp->dmg.x1830_percent = x;
}

s32 func_80087120(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    s32 result = fp->dmg.x1830_percent;
    return result;
}

void func_80087140(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    if (!fp->x221F_flag.bits.b3) {
        func_800D4F24(gobj, 1);
        func_8007ED2C(fp);
        Fighter_UnkProcessDeath_80068354(gobj);
        func_8007D92C(gobj);
    }
}

/**
 * @require It_Kind
*/
#include <melee/it/enums.h>

#include <melee/it/item.h>
#include <melee/it/item2.h>

void func_800871A8(HSD_GObj* fighter_gobj, HSD_GObj* item_gobj)
{
    Fighter* fp = fighter_gobj->user_data;
    u32 unused[2];
    assert_line(1117, itGetKind(item_gobj) == It_Kind_MetalB);
    func_800C8348(fighter_gobj, func_8026B560(item_gobj), func_8026B574(item_gobj));
    func_800D105C(fighter_gobj);
    func_80081C88(fighter_gobj, fp->x34_scale.y);
    func_8007EBAC(fp, 0xC, 0);
    func_80030E44(2, &fp->xB0_pos);
    func_80088148(fp, 0x121, 0x7F, 0x40);
}

BOOL func_80087284(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    if (fp->x10_action_state_index >= 0x6C) {
        return TRUE;
    } else {
        return FALSE;
    }
}

s32 func_800872A4(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    return fp->x4_fighterKind;
}

void* func_800872B0(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    return &fp->x20A4;
}

BOOL func_800872BC(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    return !fp->x221E_flag.bits.b1 && !fp->x2226_flag.bits.b4 && !fp->x221F_flag.bits.b4;
}

s32 func_80087300(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    return fp->dmg.x18c4_source_ply;
}

s32 func_8008730C(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    return fp->x221F_flag.bits.b5;
}

s32 func_8008731C(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    return fp->x221F_flag.bits.b3;
}

BOOL func_8008732C(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    if (fp->x10_action_state_index >= 0 && fp->x10_action_state_index <= 10) {
        return TRUE;
    }
    return FALSE;
}

BOOL func_80087354(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    if (fp->x10_action_state_index >= 3 && fp->x10_action_state_index <= 10) {
        return TRUE;
    }
    return FALSE;
}

BOOL func_8008737C(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    if (fp->x10_action_state_index >= 4 && fp->x10_action_state_index <= 5) {
        return TRUE;
    }
    return FALSE;
}

BOOL func_800873A4(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    if (fp->x10_action_state_index >= 6 && fp->x10_action_state_index <= 10) {
        return TRUE;
    }
    return FALSE;
}

BOOL func_800873CC(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    if (fp->x10_action_state_index >= 12 && fp->x10_action_state_index <= 13) {
        return TRUE;
    }
    return FALSE;
}

BOOL func_800873F4(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    if (fp->x10_action_state_index >= 0x142 && fp->x10_action_state_index <= 0x144) {
        return TRUE;
    }
    return FALSE;
}

HSD_GObj* func_8008741C(u32 i)
{
    HSD_GObj* cur;
    for (cur = lbl_804D782C->x20_fighters; cur != NULL; cur = cur->next) {
        Fighter* fp = cur->user_data;
        if (fp->x8_spawnNum == i) {
            return cur;
        }
    }
    return NULL;
}

f32 func_80087454(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    return fp->dmg.x18A4_knockbackMagnitude;
}

u32 func_80087460(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    return fp->x8_spawnNum;
}

s32 func_8008746C(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;

    if (func_80080144(fp)) {
        return 0x1FBD1;
    }
    return fp->x10C_ftData->x4C_collisionData->x34;
}

s32 func_800874BC(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    return fp->x221F_flag.bits.b4;
}

void func_800874CC(HSD_GObj* gobj, s32 arg1, s32 arg2)
{
    Fighter* fp = gobj->user_data;
    func_8003E4A4(fp->xC_playerID, fp->x221F_flag.bits.b4, arg1, arg2);
}

#include <melee/ef/efasync.h>
#include <melee/ft/ftdata.h>

void func_80087508(s8 arg0, u8 arg1)
{
    func_8008572C(arg0);
    func_8006737C(lbl_803C26FC[arg0]);
    func_80085820(arg0, arg1);
    func_80085A14(arg0);
    func_800857E0(arg0);
}

void func_80087574(s8 arg)
{
    u8 i;
    func_8008572C(arg);
    func_8006737C(lbl_803C26FC[arg]);
    for (i = 0; i < CostumeListsForeachCharacter[arg].numCostumes; i++) {
        func_80085820(arg, i);
    }
    func_80085A14(arg);
    func_800857E0(arg);
}

void func_80087610(u8 arg0)
{
    u8 i;
    for (i = 0; i <= 25; i++) {
        if (func_80164840(i)) {
            func_800EED50(Player_800325C8(i, 0), arg0);
            if ((u8) (i - 18) <= 1) {
                func_800EED50(Player_800325C8(i, 1), arg0);
            }
        }
    }
}

#include <melee/ft/ftanim.h>

void func_800876B4(HSD_GObj* gobj)
{
    ftAnim_IsFramesRemaining(gobj);
}

BOOL func_800876D4(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    if (fp->x2114_SmashAttr.x2114_state == 2) {
        return TRUE;
    } else {
        return FALSE;
    }
}

s32 func_800876F4(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    return fp->dmg.x18CC;
}

s32 func_80087700(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    return fp->dmg.x18D0;
}

void func_8008770C(HSD_GObj* gobj, void* dst)
{
    Fighter* fp = gobj->user_data;
    if (fp->x4_fighterKind == FTKIND_GAMEWATCH) {
        ftGameWatch_8014A7F4(gobj, dst);
    } else {
        func_800EEB00(gobj, dst);
    }
}

void func_80087744(HSD_GObj* gobj, void* dst)
{
    Fighter* fp = gobj->user_data;
    if (fp->x4_fighterKind == FTKIND_GAMEWATCH) {
        ftGameWatch_8014A814(gobj, dst);
    } else {
        func_800EEB1C(gobj, dst);
    }
}

void func_8008777C(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    CollData* cd;
    u32 unused[2];

    if (fp->xE0_ground_or_air != GA_Ground) {
        __assert("ftlib.c", 1517, "fp->ground_or_air == GA_Ground");
    }
    cd = &fp->x6F0_collData;
    atan2f(-cd->x14C_ground.normal.x, cd->x14C_ground.normal.y);
}

BOOL func_800877D4(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    if (fp->xF8_playerNudgeVel.x != 0) {
        return TRUE;
    } else {
        return FALSE;
    }
}
