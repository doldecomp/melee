#include "ftlib.h"

#include "cm/camera.h"
#include "ef/efasync.h"
#include "ft/ft_081B.h"
#include "ft/ft_0877.h"
#include "ft/ftcommon.h"
#include "ft/ftdata.h"
#include "ft/ftparts.h"
#include "ft/inlines.h"
#include "ftGameWatch/ftgamewatch.h"
#include "ftKirby/ftkirby.h"
#include "gm/gm_1601.h"
#include "lb/lb_00B0.h"
#include "lb/lb_00F9.h"
#include "pl/pl_0371.h"
#include "pl/player.h"

#include <baselib/jobj.h>
#include <baselib/rumble.h>

extern struct {
    void* unk0;
    u8 unk4;
} CostumeListsForeachCharacter[];

extern s8 lbl_803C26FC[];

s32 ftLib_800860C4(void)
{
    s32 ret = 0;
    HSD_GObj* cur;
    for (cur = lbl_804D782C->x20_fighters; cur != NULL; cur = cur->next) {
        ret++;
    }
    return ret;
}

bool ftLib_800860E8(void)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    HSD_GObj* cur;
    for (cur = lbl_804D782C->x20_fighters; cur != NULL; cur = cur->next) {
        if (ftLib_800872A4(cur) == FTKIND_MASTERH) {
            return true;
        }
    }

    return false;
}

bool ftLib_80086140(void)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    HSD_GObj* cur;
    for (cur = lbl_804D782C->x20_fighters; cur != NULL; cur = cur->next) {
        if (ftLib_800872A4(cur) == FTKIND_CREZYH) {
            return true;
        }
    }

    return false;
}

HSD_GObj* ftLib_80086198(HSD_GObj* gobj)
{
    /// @todo Figure out how these are really declared
    Fighter* fp;
    HSD_GObj* cur;
    HSD_GObj* result;
    int min_percent = 999;

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    if (gobj != NULL) {
        fp = GET_FIGHTER(gobj);
    } else {
        fp = NULL;
    }

    result = NULL;
    for (cur = lbl_804D782C->x20_fighters; cur != NULL; cur = cur->next) {
        if (!ftLib_80086FD4(gobj, cur)) {
            // If not same player
            Fighter* cur_fp = GET_FIGHTER(cur);
            if (cur_fp->x221F_flag.bits.b3) {
                continue;
            }

            // Skip if same team
            if (gm_8016B168() && fp != NULL &&
                cur_fp->x61B_team == fp->x61B_team)
            {
                continue;
            }

            if (cur_fp->dmg.x1830_percent < min_percent) {
                min_percent = cur_fp->dmg.x1830_percent;
                result = cur;
            }
        }
    }

    return result;
}

// get closest opposing fp?
HSD_GObj* ftLib_8008627C(Vec3* v, HSD_GObj* gobj)
{
    Vec3 cur_v;
    f32 dist;
    f32 dx;
    f32 dy;
    Fighter* cur_fp;
    Fighter* fp;
    HSD_GObj* cur;
    HSD_GObj* result;

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[16];
#endif

    f32 min_dist = F32_MAX;

    if (gobj != NULL) {
        fp = gobj->user_data;
    } else {
        fp = NULL;
    }

    result = NULL;
    for (cur = lbl_804D782C->x20_fighters; cur != NULL; cur = cur->next) {
        // skip if same player
        if (ftLib_80086FD4(gobj, cur)) {
            continue;
        }

        cur_fp = cur->user_data;
        // skip if same team
        if (cur_fp->x221F_flag.bits.b3 || (gm_8016B168() && fp != NULL &&
                                           cur_fp->x61B_team == fp->x61B_team))
        {
            continue;
        }

        ftLib_800866DC(cur, &cur_v);
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
HSD_GObj* ftLib_80086368(Vec3* v, HSD_GObj* gobj, f32 facing_dir)
{
    Vec3 sp24;
    f32 dx, dy, diff;
    Fighter* cur_fp;
    Fighter* fp;
    HSD_GObj* cur;
    HSD_GObj* result;

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[16];
#endif

    f32 min_diff = F32_MAX;

    if (gobj != NULL) {
        fp = gobj->user_data;
    } else {
        fp = NULL;
    }

    result = NULL;
    for (cur = lbl_804D782C->x20_fighters; cur != NULL; cur = cur->next) {
        if (ftLib_80086FD4(gobj, cur)) {
            continue;
        }

        cur_fp = cur->user_data;
        if (cur_fp->x221F_flag.bits.b3 || (gm_8016B168() && fp != NULL &&
                                           cur_fp->x61B_team == fp->x61B_team))
        {
            continue;
        }
        ftLib_800866DC(cur, &sp24);

        if ((facing_dir == -1 && sp24.x > v->x) ||
            (facing_dir == +1 && sp24.x < v->x))
        {
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

f32 ftLib_800864A8(Vec3* v, HSD_GObj* gobj)
{
    Vec3 vec;
    Fighter* fp;
    HSD_GObj* cur;

    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[12];
#endif

    int result = 0;

    if (gobj != NULL) {
        fp = gobj->user_data;
    } else {
        fp = NULL;
    }

    for (cur = lbl_804D782C->x20_fighters; cur != NULL; cur = cur->next) {
        if (ftLib_80086FD4(gobj, cur)) {
            continue;
        }

        {
            Fighter* cur_fp = cur->user_data;
            if (cur_fp->x221F_flag.bits.b3 ||
                (gm_8016B168() && fp != NULL &&
                 cur_fp->x61B_team == fp->x61B_team))
            {
                continue;
            }

            ftLib_800866DC(cur, &vec);
            result += sgn(vec.x - v->x);
        }
    }

    if (result == 0) {
        result = HSD_Randi(2) != 0 ? +1 : -1;
    }

    if (result < 0) {
        return -1;
    } else {
        return +1;
    }
}

f32 ftLib_800865C0(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    return fp->facing_dir;
}

s32 ftLib_800865CC(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    return fp->xE0_ground_or_air;
}

void ftLib_800865D8(HSD_GObj* gobj, f32* x, f32* y)
{
    Fighter* fp = GET_FIGHTER(gobj);
    *x = fp->input.x620_lstick_x;
    *y = fp->input.x624_lstick_y;
}

void* ftLib_800865F0(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    return fp->x5E8_fighterBones[ftParts_8007500C(fp, 4)].x0_jobj;
}

void* ftLib_80086630(HSD_GObj* gobj, s32 i)
{
    Fighter* fp = GET_FIGHTER(gobj);
    return fp->x5E8_fighterBones[i].x0_jobj;
}

void ftLib_80086644(HSD_GObj* gobj, Vec3* pos)
{
    Fighter* fp = GET_FIGHTER(gobj);
    *pos = fp->xB0_pos;
}

void ftLib_80086664(HSD_GObj* gobj, Vec3* pos)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->xB0_pos = *pos;
}

void ftLib_80086684(HSD_GObj* gobj, Vec3* pos)
{
    Fighter* fp = GET_FIGHTER(gobj);
    *pos = fp->xBC_prevPos;
}

void ftLib_SetScale(HSD_GObj* gobj, f32 val)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->x34_scale.y = val;
    Fighter_UpdateModelScale(gobj);
    ftCommon_80080174(fp);
}

void ftLib_800866DC(HSD_GObj* gobj, Vec3* v)
{
    Fighter* fp = GET_FIGHTER(gobj);
    struct attr* r4 = &fp->x110_attr;
    s32 i = fp->x10C_ftData->x0->x16C_idx;
    lb_8000B1CC(ftLib_80086630(gobj, i), &r4->x280, v);
}

void ftLib_80086724(HSD_GObj* gobj, HSD_GObj* other)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->x1974_heldItem != NULL || fp->x1978 != NULL) {
        ftCommon_8007E6DC(gobj, other, 1);
    }
}

void ftLib_80086764(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->x1984_heldItemSpec != NULL) {
        ftCommon_8007E82C(gobj);
    }
}

HSD_GObj* ftLib_80086794(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    return fp->x1974_heldItem;
}

bool ftLib_800867A0(HSD_GObj* gobj, HSD_GObj* arg1)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->x1974_heldItem == arg1 || fp->x1978 == arg1) {
        return true;
    } else {
        return false;
    }
}

HSD_GObj* ftLib_800867CC(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    return fp->x1984_heldItemSpec;
}

bool ftLib_800867D8(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    return fp->x221D_flag.bits.b4;
}

void ftLib_800867E8(HSD_GObj* gobj)
{
    Fighter* fp = gobj->user_data;
    Fighter_ResetInputData_80068854(gobj);
    fp->x221D_flag.bits.b4 = true;
}

void ftLib_80086824(void)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[16];
#endif

    HSD_GObj* cur;
    for (cur = lbl_804D782C->x20_fighters; cur != NULL; cur = cur->next) {
        ftLib_800867E8(cur);
    }
}

void ftLib_8008688C(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->x221D_flag.bits.b4 = false;
}

void ftLib_800868A4(void)
{
    HSD_GObj* cur;
    for (cur = lbl_804D782C->x20_fighters; cur != NULL; cur = cur->next) {
        ftLib_8008688C(cur);
    }
}

bool ftLib_800868D4(HSD_GObj* gobj, HSD_GObj* arg1)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (fp->x1974_heldItem != arg1 && fp->x197C != arg1 && fp->x1980 != arg1) {
        return true;
    }

    if (fp->x221E_flag.bits.b0 || fp->x221E_flag.bits.b5 ||
        (!fp->x221E_flag.bits.b3 && fp->x1974_heldItem == arg1) ||
        (!fp->x221E_flag.bits.b4 && (fp->x197C == arg1 || fp->x1980 == arg1)))
    {
        return false;
    } else {
        return true;
    }
}

bool ftLib_80086960(HSD_GObj* arg)
{
    if (arg != NULL && arg->classifier == 4) {
        return true;
    } else {
        return false;
    }
}

CollData* ftLib_80086984(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    return Fighter_GetCollData(fp);
}

inline void vector_add(Vec3* dst, Vec3* src, f32 x, f32 y, f32 z)
{
    dst->x = src->x + x;
    dst->y = src->y + y;
    dst->z = src->z + z;
}

void ftLib_80086990(HSD_GObj* gobj, Vec3* v)
{
    Fighter* fp = GET_FIGHTER(gobj);
    f32 tmp = 0.5f * (fp->x6F0_collData.xA4_ecbCurrCorrect.top.y +
                      fp->x6F0_collData.xA4_ecbCurrCorrect.bottom.y);
    vector_add(v, &fp->xB0_pos, 0, tmp, 0);
}

f32 ftLib_800869D4(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    return ftCommon_GetModelScale(fp);
}

f32 ftLib_800869F8(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    return fp->x34_scale.x * fp->x110_attr.x19C_ModelScaling;
}

f32 ftLib_80086A0C(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    return fp->x34_scale.y;
}

bool ftLib_80086A18(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    bool result = false;

    switch (fp->action_id) {
    case ASID_GUARDON:
    case ASID_GUARD:
    case ASID_GUARDSETOFF:
        result = true;
    }

    return result;
}

void ftLib_80086A4C(HSD_GObj* gobj, f32 val)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->dmg.x1958 = val;
}

bool ftLib_80086A58(HSD_GObj* gobj, S32Vec2* x)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (!fp->x2229_b3 && !fp->x2220_flag.bits.b7) {
        *x = fp->x2188;
    }

    return false;
}

bool ftLib_80086A8C(HSD_GObj* gobj)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[8];
#endif

    struct {
        u8 x0_fill[0x28];
        void* unk28;
    }* temp_r3;

    Fighter* fp = GET_FIGHTER(gobj);
    if (!fp->x2229_b3 && !fp->x2220_flag.bits.b7) {
        temp_r3 = Camera_80030A50();
        if (temp_r3 != NULL) {
            void* temp_r30 = temp_r3->unk28;
            if (temp_r30 == HSD_CObjGetCurrent()) {
                if (Camera_80030CD8(fp->x890_cameraBox, &fp->x2188)) {
                    fp->x221F_flag.bits.b0 = false;
                    return true;
                }
                fp->x221F_flag.bits.b0 = true;
                if (Camera_80030CFC(fp->x890_cameraBox, 15)) {
                    return true;
                }
                return false;
            }
        }
    }

    fp->x221F_flag.bits.b0 = false;
    return true;
}

bool ftLib_80086B64(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    return fp->x221F_flag.bits.b0;
}

CameraBox* ftLib_80086B74(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    return fp->x890_cameraBox;
}

f32 ftLib_80086B80(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    return fp->x890_cameraBox->x48.z;
}

void ftLib_80086B90(HSD_GObj* gobj, Vec3* v)
{
    Fighter* fp = GET_FIGHTER(gobj);
    CameraBox* cam = fp->x890_cameraBox;
    *v = cam->x1C;
}

void ftLib_80086BB4(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    CameraBox* cam = fp->x890_cameraBox;
    Camera_80031154(&cam->x10);
}

u8 ftLib_80086BE0(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    return fp->xC_playerID;
}

void ftLib_80086BEC(HSD_GObj* gobj, Vec3* v)
{
    Fighter* fp = GET_FIGHTER(gobj);
    *v = fp->xC8_pos_delta;
}

enum_t ftLib_80086C0C(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    return fp->action_id;
}

inline void helper(HSD_GObj* gobj, s32 arg1, s32 arg2, s32 val)
{
    Fighter* fp = gobj->user_data;

    if (!Player_8003544C(fp->xC_playerID, fp->x221F_flag.bits.b4)) {
        return;
    }

    if (!fp->x221F_flag.bits.b3 && !fp->x2224_flag.bits.b2) {
        lb_80014574(fp->x618_player_id, val, arg1, arg2);
    }
}

void ftLib_80086C18(HSD_GObj* gobj, s32 arg1, s32 arg2)
{
    helper(gobj, arg1, arg2, 0);
}

void ftLib_80086C9C(s32 arg0, s32 arg1)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[16];
#endif

    HSD_GObj* cur;
    for (cur = lbl_804D782C->x20_fighters; cur != NULL; cur = cur->next) {
        ftLib_80086C18(cur, arg0, arg1);
    }
}

void ftLib_80086D40(HSD_GObj* arg0, s32 arg1, s32 arg2)
{
    helper(arg0, arg1, arg2, 1);
}

void ftLib_80086DC4(s32 arg0, s32 arg1)
{
    /// @todo Unused stack.
#ifdef MUST_MATCH
    u8 _[16];
#endif

    HSD_GObj* cur;
    for (cur = lbl_804D782C->x20_fighters; cur != NULL; cur = cur->next) {
        ftLib_80086D40(cur, arg0, arg1);
    }
}

void ftLib_80086E68(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (Player_8003544C(fp->xC_playerID, fp->x221F_flag.bits.b4)) {
        func_80378280(fp->x618_player_id, 1);
    }
}

s32 ftLib_80086EB4(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    return fp->x61B_team;
}

bool ftLib_80086EC0(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    return fp->x221C_flag.bits.b6;
}

bool ftLib_80086ED0(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->x221E_flag.bits.b0 || fp->x221E_flag.bits.b2 ||
        Player_GetMoreFlagsBit4(fp->xC_playerID) || fp->x2228_flag.bits.b2 ||
        fp->x2229_b3 || fp->x2220_flag.bits.b7)
    {
        return false;
    }

    return true;
}

bool ftLib_80086F4C(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (!fp->x221F_flag.bits.b2 && !fp->x221F_flag.bits.b1 && fp->x209A == 1) {
        return true;
    }

    return false;
}

f32 ftLib_80086F80(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->x221E_flag.bits.b0) {
        return fp->x10C_ftData->x0->xFC;
    }

    return fp->x110_attr.x20C_NametagHeight;
}

bool ftLib_80086FA8(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    switch (fp->action_id) {
    case ASID_SWORDSWING1:
    case ASID_SWORDSWING3:
    case ASID_SWORDSWING4:
    case ASID_SWORDSWINGDASH:
        return true;
    }

    return false;
}

bool ftLib_80086FD4(HSD_GObj* gobj0, HSD_GObj* gobj1)
{
    if (gobj0 != NULL && gobj1 != NULL) {
        if (gobj0 == gobj1) {
            return true;
        }

        {
            Fighter* fp0 = GET_FIGHTER(gobj0);
            Fighter* fp1 = GET_FIGHTER(gobj1);
            if (fp0->xC_playerID == fp1->xC_playerID) {
                return true;
            }
        }
    }

    return false;
}

bool ftLib_8008701C(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    return fp->x221F_flag.bits.b3;
}

void ftLib_8008702C(s32 arg0)
{
    ftData_80085560(arg0, 1);
}

void ftLib_80087050(s32 arg0)
{
    ftData_80085560(arg0, -1);
}

bool ftLib_80087074(HSD_GObj* gobj, Vec3* v)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->dmg.x18B8 || fp->dmg.x18BC) {
        v->x = fp->dmg.x18B8;
        v->y = fp->dmg.x18BC;
        v->z = 0.0f;
        return true;
    }
    return false;
}

bool ftLib_800870BC(HSD_GObj* gobj, void** val)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->x61A_controller_index) {
        *val = p_ftCommonData->x6D8[fp->x61A_controller_index];
        return true;
    }
    return false;
}

void ftLib_800870F0(HSD_GObj* gobj, s32 x)
{
    Fighter* fp = GET_FIGHTER(gobj);
    fp->dmg.x1830_percent = x;
}

s32 ftLib_80087120(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    s32 result = fp->dmg.x1830_percent;
    return result;
}

void ftLib_80087140(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (!fp->x221F_flag.bits.b3) {
        ft_800D4F24(gobj, 1);
        ftCommon_8007ED2C(fp);
        Fighter_UnkProcessDeath_80068354(gobj);
        ftCommon_8007D92C(gobj);
    }
}

void ftLib_800871A8(HSD_GObj* gobj, HSD_GObj* item_gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    HSD_ASSERT(1117, itGetKind(item_gobj) == It_Kind_MetalB);
    ft_800C8348(gobj, it_8026B560(item_gobj), it_8026B574(item_gobj));
    ft_800D105C(gobj);
    ft_80081C88(gobj, fp->x34_scale.y);
    ftCommon_8007EBAC(fp, 0xC, 0);
    Camera_80030E44(2, &fp->xB0_pos);
    ft_80088148(fp, 0x121, 0x7F, 0x40);
}

bool ftLib_80087284(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->action_id >= ASID_LIGHTTHROWF4) {
        return true;
    }

    return false;
}

FighterKind ftLib_800872A4(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    return fp->x4_fighterKind;
}

void* ftLib_800872B0(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    return &fp->x20A4;
}

bool ftLib_800872BC(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    return !fp->x221E_flag.bits.b1 && !fp->x2226_flag.bits.b4 &&
           !fp->x221F_flag.bits.b4;
}

s32 ftLib_80087300(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    return fp->dmg.x18c4_source_ply;
}

s32 ftLib_8008730C(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    return fp->x221F_flag.bits.b5;
}

s32 ftLib_8008731C(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    return fp->x221F_flag.bits.b3;
}

bool ftLib_8008732C(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->action_id >= ASID_DEADDOWN &&
        fp->action_id <= ASID_DEADUPFALLHITCAMERAICE)
    {
        return true;
    }

    return false;
}

bool ftLib_80087354(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->action_id >= ASID_DEADUP &&
        fp->action_id <= ASID_DEADUPFALLHITCAMERAICE)
    {
        return true;
    }

    return false;
}

bool ftLib_8008737C(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->action_id >= ASID_DEADUPSTAR &&
        fp->action_id <= ASID_DEADUPSTARICE)
    {
        return true;
    }

    return false;
}

bool ftLib_800873A4(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->action_id >= ASID_DEADUPFALL &&
        fp->action_id <= ASID_DEADUPFALLHITCAMERAICE)
    {
        return true;
    }

    return false;
}

bool ftLib_800873CC(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->action_id >= ASID_REBIRTH && fp->action_id <= ASID_REBIRTHWAIT) {
        return true;
    }

    return false;
}

bool ftLib_800873F4(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->action_id >= ASID_ENTRY && fp->action_id <= ASID_ENTRYEND) {
        return true;
    }

    return false;
}

HSD_GObj* ftLib_8008741C(u32 i)
{
    HSD_GObj* cur;
    for (cur = lbl_804D782C->x20_fighters; cur != NULL; cur = cur->next) {
        Fighter* fp = GET_FIGHTER(cur);

        /// @todo Is @c i really #u32?
        if ((unsigned) fp->x8_spawnNum == i) {
            return cur;
        }
    }
    return NULL;
}

f32 ftLib_80087454(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    return fp->dmg.x18A4_knockbackMagnitude;
}

u32 ftLib_80087460(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    return fp->x8_spawnNum;
}

s32 ftLib_8008746C(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (ftCommon_80080144(fp)) {
        return 0x1FBD1;
    }

    return fp->x10C_ftData->x4C_collisionData->x34;
}

s32 ftLib_800874BC(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    return fp->x221F_flag.bits.b4;
}

void ftLib_800874CC(HSD_GObj* gobj, s32 arg1, s32 arg2)
{
    Fighter* fp = GET_FIGHTER(gobj);
    pl_8003E4A4(fp->xC_playerID, fp->x221F_flag.bits.b4, arg1, arg2);
}

void ftLib_80087508(s8 arg0, u8 arg1)
{
    ftData_8008572C(arg0);
    efAsync_8006737C(lbl_803C26FC[arg0]);
    ftData_80085820(arg0, arg1);
    ftData_80085A14(arg0);
    ftData_800857E0(arg0);
}

void ftLib_80087574(s8 arg)
{
    u8 i;
    ftData_8008572C(arg);
    efAsync_8006737C(lbl_803C26FC[arg]);

    for (i = 0; i < CostumeListsForeachCharacter[arg].unk4; i++) {
        ftData_80085820(arg, i);
    }

    ftData_80085A14(arg);
    ftData_800857E0(arg);
}

void ftLib_80087610(u8 arg0)
{
    u8 i;
    for (i = 0; i <= 25; i++) {
        if (gm_80164840(i)) {
            ftKirby_800EED50(Player_800325C8(i, 0), arg0);
            if ((u8) (i - 18) <= 1) {
                ftKirby_800EED50(Player_800325C8(i, 1), arg0);
            }
        }
    }
}

void ftLib_800876B4(HSD_GObj* gobj)
{
    ftAnim_IsFramesRemaining(gobj);
}

bool ftLib_800876D4(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->x2114_SmashAttr.x2114_state == 2) {
        return true;
    } else {
        return false;
    }
}

s32 ftLib_800876F4(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    return fp->dmg.x18CC;
}

s32 ftLib_80087700(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    return fp->dmg.x18D0;
}

void ftLib_8008770C(HSD_GObj* gobj, void* dst)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->x4_fighterKind == FTKIND_GAMEWATCH) {
        ftGameWatch_8014A7F4(gobj, dst);
    } else {
        ftKirby_800EEB00(gobj, dst);
    }
}

void ftLib_80087744(HSD_GObj* gobj, void* dst)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->x4_fighterKind == FTKIND_GAMEWATCH) {
        ftGameWatch_8014A814(gobj, dst);
    } else {
        ftKirby_800EEB1C(gobj, dst);
    }
}

void ftLib_8008777C(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);

    if (fp->xE0_ground_or_air != GA_Ground) {
        __assert("ftlib.c", 1517, "fp->ground_or_air == GA_Ground");
    }

    {
        CollData* cd = Fighter_GetCollData(fp);
        atan2f(-cd->x14C_ground.normal.x, cd->x14C_ground.normal.y);
    }
}

bool ftLib_800877D4(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    if (fp->xF8_playerNudgeVel.x != 0) {
        return true;
    } else {
        return false;
    }
}
