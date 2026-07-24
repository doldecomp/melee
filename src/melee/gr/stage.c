#include "gr/stage.h"

#include "gm/gm_unsplit.h"
#include "gr/ground.h"
#include "gr/types.h"
#include "lb/lbaudio_ax.h"
#include "lb/lbvector.h"
#include "mp/mplib.h"

#include <baselib/debug.h>
#include <baselib/random.h>

extern struct StageInfo stage_info;

/// One #stage_id_map entry: the #InternalStageId for an #ExternalStageId.
struct StageIdMapEntry {
    InternalStageId internal_id;
    s32 unk1;
    s32 unk2;
};
struct StageSelection {
    ExternalStageId external_id;
    struct StageIdMapEntry* entry;
};

struct StageSelection selected_stage = { ExternalStageID_IZUMI, NULL };
StageIdPair default_stage_pair = { IZUMI, ExternalStageID_IZUMI };

f32 Stage_GetCamBoundsLeftOffset(void)
{
    return stage_info.cam_info.cam_bounds.left +
           stage_info.cam_info.cam_x_offset;
}

f32 Stage_GetCamBoundsRightOffset(void)
{
    return stage_info.cam_info.cam_bounds.right +
           stage_info.cam_info.cam_x_offset;
}

f32 Stage_GetCamBoundsTopOffset(void)
{
    return stage_info.cam_info.cam_bounds.top +
           stage_info.cam_info.cam_y_offset;
}

f32 Stage_GetCamBoundsBottomOffset(void)
{
    return stage_info.cam_info.cam_bounds.bottom +
           stage_info.cam_info.cam_y_offset;
}

f32 Stage_GetCamPanAngleRadians(void)
{
    return 0.0174532923847F * stage_info.cam_info.cam_pan_degrees;
}

f32 Stage_GetCamMaxDepth(void)
{
    return stage_info.cam_info.cam_max_depth;
}

f32 Stage_GetCamZoomRate(void)
{
    return stage_info.cam_info.cam_zoom_rate;
}

f32 Stage_GetCamInfoX20(void)
{
    return stage_info.cam_info.x20;
}

f32 Stage_GetCamInfoX24(void)
{
    return stage_info.cam_info.x24;
}

f32 Stage_GetCamFixedZoom(void)
{
    return stage_info.cam_info.cam_fixed_zoom;
}

f32 Stage_GetCamTrackRatio(void)
{
    return stage_info.cam_info.cam_track_ratio;
}

f32 Stage_GetCamTrackSmooth(void)
{
    return stage_info.cam_info.cam_track_smooth;
}

f32 Stage_GetBlastZoneRightOffset(void)
{
    return stage_info.blast_zone.right + stage_info.cam_info.cam_x_offset;
}

f32 Stage_GetBlastZoneLeftOffset(void)
{
    return stage_info.blast_zone.left + stage_info.cam_info.cam_x_offset;
}

/// named stGetPlyDeadUp according to an assert in ftcamera.c
f32 Stage_GetBlastZoneTopOffset(void)
{
    return stage_info.blast_zone.top + stage_info.cam_info.cam_y_offset;
}

f32 Stage_GetBlastZoneBottomOffset(void)
{
    return stage_info.blast_zone.bottom + stage_info.cam_info.cam_y_offset;
}

f32 Stage_CalcUnkCamY(void)
{
    f32 cam_y_offset = stage_info.cam_info.cam_y_offset;
    f32 y_pos = stage_info.cam_info.cam_bounds.bottom + cam_y_offset +
                (stage_info.blast_zone.bottom + cam_y_offset);
    return 0.5F * y_pos;
}

f32 Stage_CalcUnkCamYBounds(void)
{
    f32 cam_offset = (stage_info.cam_info.cam_bounds.bottom +
                      stage_info.cam_info.cam_y_offset);
    f32 y_pos_product =
        0.5F *
        ((stage_info.cam_info.cam_bounds.bottom +
          stage_info.cam_info.cam_y_offset) +
         (stage_info.blast_zone.bottom + stage_info.cam_info.cam_y_offset));

    return 0.5F * (cam_offset + y_pos_product);
}

void Stage_UnkSetVec3TCam_Offset(Vec3* vec3)
{
    vec3->x = stage_info.cam_info.cam_x_offset;
    vec3->y = stage_info.cam_info.cam_y_offset;
    vec3->z = 0.0F;
}

f32 Stage_GetPauseCamZPosMin(void)
{
    return stage_info.cam_info.pausecam_zpos_min;
}

f32 Stage_GetPauseCamZPosInit(void)
{
    return stage_info.cam_info.pausecam_zpos_init;
}

f32 Stage_GetPauseCamZPosMax(void)
{
    return stage_info.cam_info.pausecam_zpos_max;
}

f32 Stage_GetCamAngleRadiansUp(void)
{
    return 0.0174532923847F * stage_info.cam_info.cam_angle_up;
}

f32 Stage_GetCamAngleRadiansDown(void)
{
    return 0.0174532923847F * stage_info.cam_info.cam_angle_down;
}

f32 Stage_GetCamAngleRadiansLeft(void)
{
    return 0.0174532923847F * stage_info.cam_info.cam_angle_left;
}

f32 Stage_GetCamAngleRadiansRight(void)
{
    return 0.0174532923847F * stage_info.cam_info.cam_angle_right;
}

void Stage_80224CAC(Vec3* arg0)
{
    Vec3 another_vec = { 0, 0, -100.0F };
    Vec3 rot_vec;

    *arg0 = stage_info.cam_info.fixed_cam_pos;

    rot_vec.x = 0.0174532923847F * stage_info.cam_info.fixed_cam_vert_angle;
    rot_vec.y = 0.0174532923847F * stage_info.cam_info.fixed_cam_horz_angle;
    rot_vec.z = 0.0F;

    lbVector_ApplyEulerRotation(&another_vec, &rot_vec);

    {
        Vec3 last_vec;
        f32 temp_f4 = (arg0->z / -another_vec.z);

        last_vec.x = (another_vec.x * temp_f4) + arg0->x;
        last_vec.y = (another_vec.y * temp_f4) + arg0->y;
        last_vec.z = 0.0F;
        *arg0 = last_vec;
    }
}

void Stage_SetVecToFixedCamPos(Vec3* arg0)
{
    *arg0 = stage_info.cam_info.fixed_cam_pos;
}

f32 Stage_GetCamFixedFov(void)
{
    return stage_info.cam_info.fixed_cam_fov;
}

bool Stage_80224DC8(s32 arg)
{
    return (arg == 0x3b || arg == 0x3f || arg == 0x42 || arg == 0x49 ||
            arg == 0x4c) != 0;
}

void Stage_80224E38(Vec3* arg0, s32 arg1)
{
    Ground_801C2D24(arg1 + 4, arg0);
}

void Stage_80224E64(enum_t arg0, Vec3* arg_vec)
{
    bool bool1;

    f32 counter_f;
    Vec3 internal_vec;

    if (arg0 == -1) {
        /// @todo Needs to be #HSD_ASSERT. Also remove fake zero-byte padding.
        __assert("stage.c", 360, "no!=St_Player_InitPos_None\0\0\0\0");
    }

    if (arg0 == 4) {
        bool1 = 0;
        for (counter_f = -10.0F; counter_f < 100.0f; counter_f += 10.0f) {
            s32 temp_ret =
                mpCheckMultiple(0.0F, 10.0F + counter_f, 0.0F, counter_f,
                                &internal_vec, 0, 0, 0, 1, -1, -1);
            if (temp_ret != 0) {
                bool1 = 1;
                break;
            }
        }

        if (bool1 == 0) {
            for (counter_f = -10.0F; counter_f > -100.0f; counter_f -= 10.0f) {
                s32 temp_ret =
                    mpCheckMultiple(0.0F, counter_f, 0.0F, counter_f - 10.0F,
                                    &internal_vec, 0, 0, 0, 1, -1, -1);

                if (temp_ret != 0) {
                    bool1 = 1;
                    break;
                }
            }
        }

        if (bool1) {
            *arg_vec = internal_vec;
            return;
        }
        arg_vec->z = 0.0F;
        arg_vec->y = 0.0F;
        arg_vec->x = 0.0F;
        return;
    }
    Ground_801C2D24(arg0, arg_vec);
}

bool Stage_80224FDC(Vec3* arg0)
{
    s32 rand_output;
    s32 counter = 0x15;
    s32 counter2;

    while (counter != 0) {
        if (Ground_801C2D24(HSD_Randi(counter) + 0x7F, arg0)) {
            return true;
        }
        counter += -1;
    }

    counter2 = 4;
    while (counter2 != 0) {
        rand_output = HSD_Randi(counter2);
        counter2 = Ground_801C2D24(rand_output, arg0);

        if (counter2 != 0) {
            return true;
        }
        counter2 = rand_output;
    }

    return false;
}

s32 Stage_80225074(s32 arg0)
{
    s32 r31;
    s32 spC;
    bool tmp;

    if (gm_8016B238() != 0) {
        if (stage_info.unk8C.b0 || arg0 == 2) {
            r31 = 0x12;
        } else {
            r31 = 0x11;
        }
    } else if (gm_8016B3A0() != 0) {
        if (arg0 == 2) {
            r31 = 0x22;
        } else if (arg0 == 1) {
            r31 = 0x64;
        } else {
            r31 = 0x24;
        }
    } else if (arg0 == 0) {
        r31 = 4;
    } else if (arg0 == 3) {
        r31 = 1;
    } else if (arg0 == 2) {
        r31 = 2;
    } else if (arg0 == 1) {
        r31 = 0x44;
    } else {
        HSD_ASSERT(526, 0);
    }

    tmp = Ground_801C28AC(selected_stage.external_id, r31, &spC);
    lbAudioAx_80023F28(spC);
    Ground_801C5A84(spC);
    Ground_801C5AA4(tmp);
    return arg0;
}

ExternalStageId Stage_80225194(void)
{
    return selected_stage.external_id;
}

/// Indexed by #ExternalStageId.
struct StageIdMapEntry stage_id_map[] = {
    { InternalStageID_Unk00, 0, 0 },
    { TEST, 0, 0 },
    { IZUMI, 0, 0 },
    { PSTADIUM, 0, 0 },
    { CASTLE, 0, 0 },
    { KONGO, 0, 0 },
    { ZEBES, 0, 0 },
    { CORNERIA, 0, 0 },
    { STORY, 0, 0 },
    { ONETT, 0, 0 },
    { MUTECITY, 0, 0 },
    { RCRUISE, 0, 0 },
    { GARDEN, 0, 0 },
    { GREATBAY, 0, 0 },
    { SHRINE, 0, 0 },
    { KRAID, 0, 0 },
    { YORSTER, 0, 0 },
    { GREENS, 0, 0 },
    { FOURSIDE, 0, 0 },
    { INISHIE1, 0, 0 },
    { INISHIE2, 0, 0 },
    { InternalStageID_Unk26, 0, 0 },
    { VENOM, 0, 0 },
    { PURA, 0, 0 },
    { BIGBLUE, 0, 0 },
    { ICEMTN, 0, 0 },
    { ICEMTN, 0, 0 },
    { FLATZONE, 0, 0 },
    { OLDPUPUPU, 0, 0 },
    { OLDYOSHI, 0, 0 },
    { OLDKONGO, 0, 0 },
    { BATTLE, 0, 0 },
    { LAST, 0, 0 },
    { TMARIO, 0, 0 },
    { TCAPTAIN, 0, 0 },
    { TCLINK, 0, 0 },
    { TDONKEY, 0, 0 },
    { TDRMARIO, 0, 0 },
    { TFALCO, 0, 0 },
    { TFOX, 0, 0 },
    { TICECLIMBER, 0, 0 },
    { TKIRBY, 0, 0 },
    { TKOOPA, 0, 0 },
    { TLINK, 0, 0 },
    { TLUIGI, 0, 0 },
    { TMARS, 0, 0 },
    { TMEWTWO, 0, 0 },
    { TNESS, 0, 0 },
    { TPEACH, 0, 0 },
    { TPICHU, 0, 0 },
    { TPIKACHU, 0, 0 },
    { TPURIN, 0, 0 },
    { TSAMUS, 0, 0 },
    { TSEAK, 0, 0 },
    { TYOSHI, 0, 0 },
    { TZELDA, 0, 0 },
    { TGAMEWATCH, 0, 0 },
    { TEMBLEM, 0, 0 },
    { TGANON, 0, 0 },
    { KINOKOROUTE, 0, 0 },
    { CASTLE, 0, 0 },
    { KONGO, 0, 0 },
    { GARDEN, 0, 0 },
    { SHRINEROUTE, 0, 0 },
    { SHRINE, 0, 0 },
    { ZEBES, 0, 0 },
    { ZEBESROUTE, 0, 0 },
    { GREENS, 0, 0 },
    { GREENS, 0, 0 },
    { GREENS, 0, 0 },
    { CORNERIA, 0, 0 },
    { CORNERIA, 0, 0 },
    { PSTADIUM, 0, 0 },
    { BIGBLUEROUTE, 0, 0 },
    { MUTECITY, 0, 0 },
    { ONETT, 0, 0 },
    { ICEMTN, 0, 0 },
    { ICEMTN, 0, 0 },
    { BATTLE, 0, 0 },
    { BATTLE, 0, 0 },
    { LAST, 0, 0 },
    { LAST, 0, 0 },
    { PUSHON, 0, 0 },
    { FIGUREGET, 0, 0 },
    { HOMERUN, 0, 0 },
    { HEAL, 0, 0 },
    { CASTLE, 0, 0 },
    { RCRUISE, 0, 0 },
    { KONGO, 0, 0 },
    { GARDEN, 0, 0 },
    { GREATBAY, 0, 0 },
    { SHRINE, 0, 0 },
    { ZEBES, 0, 0 },
    { KRAID, 0, 0 },
    { STORY, 0, 0 },
    { YORSTER, 0, 0 },
    { IZUMI, 0, 0 },
    { GREENS, 0, 0 },
    { CORNERIA, 0, 0 },
    { VENOM, 0, 0 },
    { PSTADIUM, 0, 0 },
    { INISHIE1, 0, 0 },
    { INISHIE2, 0, 0 },
    { MUTECITY, 0, 0 },
    { BIGBLUE, 0, 0 },
    { ONETT, 0, 0 },
    { FOURSIDE, 0, 0 },
    { PSTADIUM, 0, 0 },
    { CASTLE, 0, 0 },
    { BATTLE, 0, 0 },
    { CASTLE, 0, 0 },
    { INISHIE2, 0, 0 },
    { SHRINE, 0, 0 },
    { GREATBAY, 0, 0 },
    { LAST, 0, 0 },
    { PSTADIUM, 0, 0 },
    { ICEMTN, 0, 0 },
    { ICEMTN, 0, 0 },
    { INISHIE1, 0, 0 },
    { GREATBAY, 0, 0 },
    { SHRINE, 0, 0 },
    { CORNERIA, 0, 0 },
    { VENOM, 0, 0 },
    { GREATBAY, 0, 0 },
    { PSTADIUM, 0, 0 },
    { BATTLE, 0, 0 },
    { INISHIE2, 0, 0 },
    { KONGO, 0, 0 },
    { SHRINE, 0, 0 },
    { GREATBAY, 0, 0 },
    { INISHIE1, 0, 0 },
    { GREATBAY, 0, 0 },
    { BIGBLUE, 0, 0 },
    { ZEBES, 0, 0 },
    { STORY, 0, 0 },
    { YORSTER, 0, 0 },
    { GREENS, 0, 0 },
    { IZUMI, 0, 0 },
    { GREENS, 0, 0 },
    { ICEMTN, 0, 0 },
    { CORNERIA, 0, 0 },
    { MUTECITY, 0, 0 },
    { PSTADIUM, 0, 0 },
    { PSTADIUM, 0, 0 },
    { INISHIE1, 0, 0 },
    { ONETT, 0, 0 },
    { FOURSIDE, 0, 0 },
    { BIGBLUE, 0, 0 },
    { BATTLE, 0, 0 },
    { BATTLE, 0, 0 },
    { BATTLE, 0, 0 },
    { SHRINE, 0, 0 },
    { GREATBAY, 0, 0 },
    { SHRINE, 0, 0 },
    { GREATBAY, 0, 0 },
    { CASTLE, 0, 0 },
    { KONGO, 0, 0 },
    { GREATBAY, 0, 0 },
    { STORY, 0, 0 },
    { INISHIE2, 0, 0 },
    { MUTECITY, 0, 0 },
    { PSTADIUM, 0, 0 },
    { IZUMI, 0, 0 },
    { INISHIE1, 0, 0 },
    { SHRINE, 0, 0 },
    { RCRUISE, 0, 0 },
    { GARDEN, 0, 0 },
    { IZUMI, 0, 0 },
    { INISHIE2, 0, 0 },
    { ONETT, 0, 0 },
    { PSTADIUM, 0, 0 },
    { ICEMTN, 0, 0 },
    { PSTADIUM, 0, 0 },
    { FLATZONE, 0, 0 },
    { MUTECITY, 0, 0 },
    { BATTLE, 0, 0 },
    { LAST, 0, 0 },
    { RCRUISE, 0, 0 },
    { KONGO, 0, 0 },
    { GREATBAY, 0, 0 },
    { ZEBES, 0, 0 },
    { STORY, 0, 0 },
    { GREENS, 0, 0 },
    { CORNERIA, 0, 0 },
    { PSTADIUM, 0, 0 },
    { INISHIE1, 0, 0 },
    { MUTECITY, 0, 0 },
    { ONETT, 0, 0 },
    { PURA, 0, 0 },
    { ICEMTN, 0, 0 },
    { CASTLE, 0, 0 },
    { SHRINE, 0, 0 },
    { IZUMI, 0, 0 },
    { BATTLE, 0, 0 },
    { YORSTER, 0, 0 },
    { INISHIE2, 0, 0 },
    { GARDEN, 0, 0 },
    { VENOM, 0, 0 },
    { FOURSIDE, 0, 0 },
    { LAST, 0, 0 },
    { FLATZONE, 0, 0 },
    { KRAID, 0, 0 },
    { BATTLE, 0, 0 },
    { SHRINE, 0, 0 },
    { CASTLE, 0, 0 },
    { STORY, 0, 0 },
    { ONETT, 0, 0 },
    { IZUMI, 0, 0 },
    { PSTADIUM, 0, 0 },
    { ZEBES, 0, 0 },
    { GREATBAY, 0, 0 },
    { YORSTER, 0, 0 },
    { ICEMTN, 0, 0 },
    { MUTECITY, 0, 0 },
    { RCRUISE, 0, 0 },
    { FIGURE1, 0, 0 },
    { BATTLE, 0, 0 },
    { CORNERIA, 0, 0 },
    { GARDEN, 0, 0 },
    { KONGO, 0, 0 },
    { LAST, 0, 0 },
    { ZEBES, 0, 0 },
    { CASTLE, 0, 0 },
    { INISHIE2, 0, 0 },
    { KRAID, 0, 0 },
    { YORSTER, 0, 0 },
    { FOURSIDE, 0, 0 },
    { FIGURE2, 0, 0 },
    { VENOM, 0, 0 },
    { GREENS, 0, 0 },
    { SHRINE, 0, 0 },
    { IZUMI, 0, 0 },
    { INISHIE1, 0, 0 },
    { CORNERIA, 0, 0 },
    { BIGBLUEROUTE, 0, 0 },
    { GREATBAY, 0, 0 },
    { OLDPUPUPU, 0, 0 },
    { FOURSIDE, 0, 0 },
    { IZUMI, 0, 0 },
    { INISHIE2, 0, 0 },
    { PSTADIUM, 0, 0 },
    { SHRINE, 0, 0 },
    { SHRINE, 0, 0 },
    { PURA, 0, 0 },
    { BIGBLUE, 0, 0 },
    { BATTLE, 0, 0 },
    { FLATZONE, 0, 0 },
    { SHRINE, 0, 0 },
    { FIGURE3, 0, 0 },
    { STORY, 0, 0 },
    { INISHIE1, 0, 0 },
    { LAST, 0, 0 },
    { LAST, 0, 0 },
    { GARDEN, 0, 0 },
    { STORY, 0, 0 },
    { CASTLE, 0, 0 },
    { RCRUISE, 0, 0 },
    { GREATBAY, 0, 0 },
    { SHRINE, 0, 0 },
    { MUTECITY, 0, 0 },
    { CORNERIA, 0, 0 },
    { PSTADIUM, 0, 0 },
    { ONETT, 0, 0 },
    { ICEMTN, 0, 0 },
    { INISHIE2, 0, 0 },
    { PURA, 0, 0 },
    { LAST, 0, 0 },
    { FLATZONE, 0, 0 },
    { VENOM, 0, 0 },
    { PSTADIUM, 0, 0 },
    { GREATBAY, 0, 0 },
    { SHRINE, 0, 0 },
    { LAST, 0, 0 },
    { BATTLE, 0, 0 },
    { PSTADIUM, 0, 0 },
    { LAST, 0, 0 },
    { INISHIE2, 0, 0 },
    { IZUMI, 0, 0 },
    { FLATZONE, 0, 0 },
    { CASTLE, 0, 0 },
    { LAST, 0, 0 },
    { GREATBAY, 0, 0 },
    { BATTLE, 0, 0 },
    { PSTADIUM, 0, 0 },
    { SHRINE, 0, 0 },
    { BATTLE, 0, 0 },
};

InternalStageId Stage_8022519C(ExternalStageId external_id)
{
    return stage_id_map[external_id].internal_id;
}

void Stage_802251B4(ExternalStageId external_id)
{
    Ground_801C06B8(stage_id_map[external_id].internal_id);
}

void Stage_802251E8(ExternalStageId external_id, s32* _)
{
    StageIdPair local_data;

    selected_stage.external_id = external_id;
    selected_stage.entry = &stage_id_map[external_id];

    local_data = default_stage_pair;

    local_data.internal_id = selected_stage.entry->internal_id;
    local_data.external_id = selected_stage.external_id;

    Ground_801C0754(&local_data);
}

void Stage_8022524C(void)
{
    StageIdPair local_data;

    local_data = default_stage_pair;

    local_data.internal_id = selected_stage.entry->internal_id;
    local_data.external_id = selected_stage.external_id;

    Ground_801C0800(&local_data);
}

void Stage_80225298(void)
{
    StageIdPair local_data;

    local_data = default_stage_pair;

    local_data.internal_id = selected_stage.entry->internal_id;
    local_data.external_id = selected_stage.external_id;

    Ground_801C0F78(&local_data);
}

void Stage_802252E4(ExternalStageId external_id, HSD_GObj* _)
{
    StageIdPair local_data;

    local_data = default_stage_pair;

    local_data.internal_id = selected_stage.entry->internal_id;
    local_data.external_id = external_id;

    Ground_801C0FB8(&local_data);
}

void Stage_8022532C(ExternalStageId external_id, s32 arg1)
{
    StageIdPair local_data;

    local_data = default_stage_pair;

    local_data.internal_id = selected_stage.entry->internal_id;
    local_data.external_id = external_id;

    Ground_DemoInit(&local_data, arg1);
}
