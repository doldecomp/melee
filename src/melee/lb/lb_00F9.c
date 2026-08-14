#include "lb_00F9.h"

#include "math.h"
#include "platform.h"
#include "stddef.h"

#include <placeholder.h>

#include "baselib/forward.h"

#include "baselib/psstructs.h"
#include "baselib/tobj.h"

#include "lb/forward.h"

#include "lb/lbcollision.h"
#include "lb/lbspdisplay.h"
#include "lb/lbvector.h"
#include "lb/types.h"

#include <math_ppc.h>
#include <trigf.h>
#include <dolphin/mtx.h>
#include <baselib/cobj.h>
#include <baselib/displayfunc.h>
#include <baselib/dobj.h>
#include <baselib/gobj.h>
#include <baselib/gobjobject.h>
#include <baselib/jobj.h>
#include <baselib/lobj.h>
#include <baselib/memory.h>
#include <baselib/quatlib.h>
#include <melee/mp/mplib.h>

struct lb_Collider {
    /* 0x00 */ char pad_00[0x0C];
    /* 0x0C */ f32 radius;
    /* 0x10 */ char pad_10[0x08];
    /* 0x18 */ Vec3 position;
    /* 0x24 */ char pad_24[0x04];
};

struct CameraBlurData {
    /* 0x00 */ f32 x0;
    /* 0x04 */ f32 x4;
    /* 0x08 */ f32 x8;
    /* 0x0C */ f32 xC;
    /* 0x10 */ u8 x10;
    /* 0x11 */ u8 x11;
    /* 0x12 */ u8 x12;
    /* 0x13 */ char pad_13[0x18 - 0x13];
    /* 0x18 */ HSD_GObjEvent x18;
    /* 0x1C */ HSD_ImageDesc* x1C;
    /* 0x20 */ f32 x20;
};

const struct {
    Vec3 v0;
    Vec3 v1;
    Vec3 v2;
    f32 pad;
} lb_803B7280 = {
    { 0.0f, -1.0f, 0.0f },
    { 0.0f, -1.0f, 0.0f },
    { 0.0f, -1.0f, 0.0f },
    0.0f,
};

/* 4D63A0 */ static struct lb_804D63A0_t* lb_804D63A0;
/* 4D63A4 */ static struct DynamicsData* cur_data;
/* 4D63A8 */ static struct lb_804D63A8_t* lb_804D63A8;
/* 4D63AC */ static struct lb_80011A50_t* lb_804D63AC;
/* 4D63B0 */ static struct lb_80011A50_t* lb_804D63B0;
/* 4D63B4 */ static enum_t lb_804D63B4;
/* 4D63B8 */ static u8 lb_804D63B8;

static void order_data(void)
{
    (void) "active deffect:";
    (void) "[NULL]\n\n";
    (void) "free deffect:";
    (void) "[NULL]\n\n\n";
    (void) "translate";
}

static inline bool checkJObjFlags(HSD_JObj* jobj)
{
    return jobj->flags & (JOBJ_PTCL | JOBJ_SPLINE) ? false : true;
}

void lb_8000F9F8(HSD_JObj* jobj)
{
    if (HSD_JObjGetChild(jobj) != NULL) {
        lb_80011C18(HSD_JObjGetChild(jobj), JOBJ_UNK_B26);
    }
    if (checkJObjFlags(jobj) && HSD_JObjGetDObj(jobj) != NULL) {
        lb_80011B74(HSD_JObjGetDObj(jobj), JOBJ_UNK_B26);
    }
}

void lb_8000FA94(void)
{
    int i;

    for (i = 0; i < 0x140; i++) {
        lb_804D63A0->entries[i].desc.lb_unk0.jobj = NULL;
        lb_804D63A0->entries[i].next =
            (i < 0x13F) ? &lb_804D63A0->entries[i] + 1 : NULL;
    }

    cur_data = &lb_804D63A0->entries[0];

    for (i = 0; i < 8; i++) {
        lb_804D63A8->entries[i].x0 = 0;
        lb_804D63A8->entries[i].next =
            (i < 7) ? &lb_804D63A8->entries[i] + 1 : NULL;
    }

    lb_804D63AC = &lb_804D63A8->entries[0];
    lb_804D63B0 = NULL;
    lb_804D63B4 = 0;
}

void lb_8000FCDC(void)
{
    lb_804D63A0 = HSD_MemAlloc(sizeof(*lb_804D63A0));
    lb_804D63A8 = HSD_MemAlloc(sizeof(*lb_804D63A8));
    lb_8000FA94();
}

void lb_8000FD18(DynamicsDesc* desc)
{
    struct DynamicsData *temp, *cur, *next;

    for (cur = desc->data; cur != NULL; cur = next) {
        next = cur->next;
        temp = cur_data;
        cur_data = cur;
        cur->next = temp;
    }
    desc->data = NULL;
}

static inline struct DynamicsData* popDynamicsData(void)
{
    struct DynamicsData* entry = cur_data;
    if (entry == NULL) {
        return NULL;
    }
    cur_data = entry->next;
    entry->next = NULL;
    return entry;
}

void lb_8000FD48(HSD_JObj* jobj, DynamicsDesc* desc, size_t max_count)
{
    struct DynamicsData* prev;
    PAD_STACK(0x10);

    if (desc == NULL) {
        return;
    }

    if (jobj == NULL) {
        desc->data = NULL;
        return;
    }

    desc->count = 0;

    while ((s32) desc->count < (s32) max_count) {
        if ((s32) desc->count == 0) {
            desc->data = (prev = popDynamicsData());
        } else {
            prev->next = popDynamicsData();
            prev = prev->next;
        }

        if (prev == NULL) {
            return;
        }

        HSD_JObjSetMtxDirty(jobj);
        HSD_JObjSetupMatrix(jobj);

        prev->desc.lb_unk0.jobj = jobj;
        prev->desc.lb_unk0.rotate = jobj->rotate;
        prev->desc.lb_unk0.scale = jobj->scale;
        prev->desc.lb_unk0.translate = jobj->translate;
        prev->desc.lb_unk0.unk_2C.x = jobj->mtx[0][3];
        prev->desc.lb_unk0.unk_2C.y = jobj->mtx[1][3];
        prev->desc.lb_unk0.unk_2C.z = jobj->mtx[2][3];
        prev->desc.lb_unk0.unk_58 = prev->desc.lb_unk0.rotate;
        prev->desc.lb_unk0.unk_38.x = 1.0f;
        prev->desc.lb_unk0.unk_38.y = 0.0f;
        prev->desc.lb_unk0.unk_38.z = 0.0f;
        prev->desc.lb_unk0.unk_44 = 0.0f;
        prev->desc.lb_unk0.unk_8C = 0.0f;
        prev->desc.lb_unk0.unk_48 = 0.0f;
        prev->next = NULL;
        prev->unk_94 = 0;

        jobj = jobj->child;
        desc->count++;
    }

    prev = desc->data;
    {
        struct DynamicsData* next;

        while ((next = prev->next) != NULL) {
            f32 dx, dy, dz, dist_sq;

            dx = prev->desc.lb_unk0.unk_2C.x - next->desc.lb_unk0.unk_2C.x;
            dy = prev->desc.lb_unk0.unk_2C.y - next->desc.lb_unk0.unk_2C.y;
            dz = prev->desc.lb_unk0.unk_2C.z - next->desc.lb_unk0.unk_2C.z;
            if ((dist_sq = dz * dz + (dx * dx + dy * dy)) > 0.0f) {
                volatile float y;
                double guess = __frsqrte((double) dist_sq);
                guess = .5 * guess * (3.0 - guess * guess * dist_sq);
                guess = .5 * guess * (3.0 - guess * guess * dist_sq);
                guess = .5 * guess * (3.0 - guess * guess * dist_sq);
                y = (float) (dist_sq * guess);
                dist_sq = y;
            }
            prev->desc.lb_unk0.unk_48 = dist_sq;

            next = prev->next;
            {
                f32 tx, ty, tz;

                tx = ABS(next->desc.lb_unk0.translate.x);
                ty = ABS(next->desc.lb_unk0.translate.y);
                tz = ABS(next->desc.lb_unk0.translate.z);

                if (tz > ty) {
                    if (tz > tx) {
                        prev->desc.lb_unk0.unk_54 = -1;
                    } else {
                        prev->desc.lb_unk0.unk_54 = 0;
                    }
                } else if (ty > tx) {
                    prev->desc.lb_unk0.unk_54 = 1;
                } else {
                    prev->desc.lb_unk0.unk_54 = 0;
                }
            }

            prev = prev->next;
        }
    }
}

static inline struct lb_80011A50_t* inlineA0(void)
{
    struct lb_80011A50_t* ret = lb_804D63AC;
    if (ret == NULL) {
        return NULL;
    }
    {
        /// @todo inline appears in #lb_800115F4
        struct lb_80011A50_t* temp = lb_804D63B0;
        lb_804D63AC = ret->next;
        lb_804D63B0 = ret;
        ret->next = temp;
    }
    return ret;
}

static inline struct lb_80011A50_t* inlineA1(void)
{
    struct lb_80011A50_t* cur = lb_804D63B0;
    if (lb_804D63B0 == NULL) {
        return NULL;
    }
    {
        struct lb_80011A50_t* ret = cur;
        s32 max = cur->x1;
        while (cur != NULL) {
            if (max < (s32) cur->x1) {
                max = cur->x1;
                ret = cur;
            }
            cur = cur->next;
        }
        return ret;
    }
}

struct lb_80011A50_t* lb_800100B0(struct lb_80011A50_t* arg0, f32 arg1)
{
    struct lb_80011A50_t* ret = inlineA0();
    if (ret == NULL) {
        ret = inlineA1();
        if (ret == NULL) {
            return NULL;
        }
        if (ret->x1 < arg0->x1) {
            return NULL;
        }
    }
    ret->x0 = arg0->x0;
    ret->x1 = arg0->x1;
    ret->x4 = arg0->x4;
    ret->unk_scale = arg0->unk_scale;
    ret->x24 = arg0->x24;
    ret->unk_count0 = arg0->unk_count0;
    ret->unk_angle_float = arg0->unk_angle_float;
    ret->x10 = arg0->x10;
    ret->x14 = arg0->x14;
    ret->x18 = arg0->x18;
    ret->x1C = arg0->x1C;
    ret->unk_angle_int = 0;
    return ret;
}

float lb_800101C8(Vec3* arg0, Vec3* arg1)
{
    struct lb_80011A50_t* var_r30 = lb_804D63B0;
    arg1->x = 0.0f;
    arg1->y = 0.0f;
    arg1->z = 0.0f;
    for (; var_r30 != NULL; var_r30 = var_r30->next) {
        float scale0 =
            0.5 * var_r30->unk_scale *
            (1.0 + cosf(var_r30->unk_angle_int * var_r30->unk_angle_float));
        if (var_r30->x0 == 1) {
            if (arg0->x > var_r30->x10 && arg0->x < var_r30->x18) {
                if (arg0->y < var_r30->x14 && arg0->y > var_r30->x1C) {
                    arg1->x += var_r30->x4.x * scale0;
                    arg1->y += var_r30->x4.y * scale0;
                    arg1->z += var_r30->x4.z * scale0;
                }
            }
        } else {
            Vec3 delta;
            delta.x = arg0->x - var_r30->x4.x;
            delta.y = arg0->y - var_r30->x4.y;
            delta.z = arg0->z - var_r30->x4.z;
            {
                f32 scale1;
                f32 var_f0 = 0.05 * lbVector_Normalize(&delta);
                if (var_f0 < 1.0) {
                    var_f0 = 1.0f;
                }
                scale1 = 1.0 / (var_f0 * var_f0);
                arg1->x += scale1 * (delta.x * scale0);
                arg1->y += scale1 * (delta.y * scale0);
                arg1->z += scale1 * (delta.z * scale0);
            }
        }
    }
    return lbVector_Normalize(arg1);
}

float lb_800103B8(Vec3* a, Vec3* b)
{
    return lb_800101C8(a, b);
}

#pragma push
#pragma dont_inline on
bool lb_800103D8(Vec3* vec, float x0, float x1, float x2, float x3,
                 float offset)
{
    float dist0 = x1 - offset;
    float dist1 = x3 - offset;
    if (dist0 == dist1) {
        if (dist0 > 1e-10f) {
            return true;
        }
        return false;
    }
    if ((double) dist0 > 0.0 && (double) dist1 < 0.0) {
        vec->x = -dist1 / (dist0 - dist1) * (x0 - x2) + x2;
        vec->y = offset;
        vec->z = 0.0f;
        return true;
    }
    return false;
}
#pragma pop

static inline bool approximatelyZeroVec3(Vec3 vec)
{
    bool result;

    if (vec.x >= 0.00001f || vec.x <= -0.00001f || vec.y >= 0.00001f ||
        vec.y <= -0.00001f || vec.z >= 0.00001f || vec.z <= -0.00001f)
    {
        result = false;
    } else {
        result = true;
    }
    return result;
}

static inline float absf(float x)
{
    if (x < 0.0f) {
        x = -x;
    }
    return x;
}

static inline float groundHeight(struct DynamicsData* data, Vec3* floor_point)
{
    return absf(data->desc.lb_unk0.unk_2C.y - floor_point->y);
}

/// @todo Only the placement of one @c li differs.
void lb_8001044C(DynamicsDesc* desc, void* colliders_raw, int num_colliders,
                 float pos_y, bool use_floor_fn, Fighter_Part part,
                 int first_active, bool ground_check)
{
    HSD_JObj* parent_jobj;
    Mtx parent_mtx, temp_mtx;
    Vec3 natural_dir, current_dir, link_dir;
    Vec3 adj_dir, saved_dir, rotation_axis;
    Mtx bone_mtx, constrained_mtx, trans_mtx, scale_mtx;
    u8 _padA[4];
    Vec3 local_axis;
    Vec3 euler_angles;
    Quaternion angle_quat, euler_quat, result_quat;
    Vec3 stiffness_axis;
    Vec3 grav_dir, gravity_axis;
    Vec3 next_pos, force_dir, force_axis;
    Vec3 clamp_dir, clamp_axis;
    Vec3 convergence_axis, deviation_axis;
    Vec3 next_bone_pos, coll_dir;
    Vec3 collision_point;
    Vec3 avoidance_axis;
    u8 _padB[16];
    s32 sp8;

    struct DynamicsData* cur;
    HSD_JObj* jobj;
    struct lb_Collider* collider;
    s32 on_ground;
    s32 loop_index = 0;

    if ((u8) lb_804D63B8 != 0) {
        return;
    }
    if (desc == NULL) {
        return;
    }

    cur = desc->data;
    if (cur == NULL) {
        return;
    }
    if (part > 0xFF) {
        return;
    }

    on_ground = 0;
    {
        s32 i;
        for (i = 0; i < (s32) part; i++) {
            cur = cur->next;
            loop_index++;
        }
    }

    parent_jobj = cur->desc.lb_unk0.jobj->parent;
    (void) parent_jobj;
    if (parent_jobj != NULL) {
        HSD_JObjSetMtxDirty(parent_jobj);
        HSD_JObjSetupMatrix(parent_jobj);
        PSMTXCopy(parent_jobj->mtx, parent_mtx);
    } else {
        PSMTXIdentity(parent_mtx);
    }

    jobj = cur->desc.lb_unk0.jobj;

    while (cur->next != NULL) {
        f32 angle_diff;
        f32 force_mag;

        /* Build translation matrix and concat */
        PSMTXTrans(trans_mtx, jobj->translate.x, jobj->translate.y,
                   jobj->translate.z);
        PSMTXConcat(parent_mtx, trans_mtx, bone_mtx);

        /* Build rotation from saved rotation (offset 0x58) */
        lbVector_CreateEulerMatrix(temp_mtx, &cur->desc.lb_unk0.unk_58);
        PSMTXConcat(bone_mtx, temp_mtx, constrained_mtx);

        /* Build rotation from jobj euler rotation */
        lbVector_CreateEulerMatrix(temp_mtx, &jobj->rotate);
        PSMTXConcat(bone_mtx, temp_mtx, bone_mtx);

        /* Build scale matrix and concat */
        PSMTXScale(scale_mtx, jobj->scale.x, jobj->scale.y, jobj->scale.z);
        PSMTXConcat(bone_mtx, scale_mtx, bone_mtx);
        PSMTXConcat(constrained_mtx, scale_mtx, constrained_mtx);

        /* Store world position */
        cur->desc.lb_unk0.unk_2C.x = bone_mtx[0][3];
        cur->desc.lb_unk0.unk_2C.y = bone_mtx[1][3];
        cur->desc.lb_unk0.unk_2C.z = bone_mtx[2][3];

        /* Compute natural bone direction */
        PSMTXMultVec(constrained_mtx, &jobj->child->translate, &natural_dir);
        natural_dir.x -= cur->desc.lb_unk0.unk_2C.x;
        natural_dir.y -= cur->desc.lb_unk0.unk_2C.y;
        natural_dir.z -= cur->desc.lb_unk0.unk_2C.z;

        /* Compute current bone direction */
        PSMTXMultVec(bone_mtx, &jobj->child->translate, &current_dir);
        current_dir.x -= cur->desc.lb_unk0.unk_2C.x;
        current_dir.y -= cur->desc.lb_unk0.unk_2C.y;
        current_dir.z -= cur->desc.lb_unk0.unk_2C.z;

        /* Compute link direction (next world pos - current world pos) */
        link_dir.x =
            cur->next->desc.lb_unk0.unk_2C.x - cur->desc.lb_unk0.unk_2C.x;
        link_dir.y =
            cur->next->desc.lb_unk0.unk_2C.y - cur->desc.lb_unk0.unk_2C.y;
        link_dir.z =
            cur->next->desc.lb_unk0.unk_2C.z - cur->desc.lb_unk0.unk_2C.z;

        lbVector_Normalize(&natural_dir);
        lbVector_Normalize(&current_dir);
        lbVector_Normalize(&link_dir);

        /* Save link direction */
        {
            saved_dir = link_dir;

            /* Apply stiffness blend toward natural direction */
            if (cur->desc.lb_unk0.unk_4C * desc->pos.x < 1.0) {
                f32 stiff_angle = ABS(lbVector_Angle(&link_dir, &current_dir));
                if (stiff_angle != 0.0f) {
                    PSVECCrossProduct(&link_dir, &current_dir,
                                      &stiffness_axis);
                    lbVector_Normalize(&stiffness_axis);
                    lbVector_RotateAboutUnitAxis(
                        &link_dir, &stiffness_axis,
                        stiff_angle *
                            (f32) (1.0 - (f64) (cur->desc.lb_unk0.unk_4C *
                                                desc->pos.x)));
                }
            }

            /* Apply gravity influence */
            {
                f32 grav_angle;
                grav_dir = lb_803B7280.v0;
                grav_angle = lbVector_Angle(&link_dir, &grav_dir);
                if (grav_angle != 0.0f) {
                    f32 grav_rot = cur->desc.lb_unk0.unk_8C * sinf(grav_angle);
                    if (grav_rot < 0.0f) {
                        grav_rot = -grav_rot;
                    }
                    {
                        PSVECCrossProduct(&link_dir, &grav_dir, &gravity_axis);
                        lbVector_Normalize(&gravity_axis);
                        lbVector_RotateAboutUnitAxis(&link_dir, &gravity_axis,
                                                     grav_rot);
                    }
                }
            }

            /* Apply interaction force */
            force_mag = 0.0f;
            if (lb_804D63B0 != NULL && first_active <= loop_index) {
                struct DynamicsData* next_node = cur->next;
                next_pos = next_node->desc.lb_unk0.unk_2C;
                force_mag = lb_800101C8(&next_pos, &force_dir);
                {
                    f32 force_angle = lbVector_Angle(&link_dir, &force_dir);
                    if (force_angle != 0.0f) {
                        f32 force_rot = (force_mag * sinf(force_angle)) /
                                        cur->desc.lb_unk0.unk_48;
                        if (force_rot < 0.0f) {
                            force_rot = -force_rot;
                        }
                        {
                            PSVECCrossProduct(&link_dir, &force_dir,
                                              &force_axis);
                            lbVector_Normalize(&force_axis);
                            lbVector_RotateAboutUnitAxis(
                                &link_dir, &force_axis, force_rot);
                        }
                    }
                }
            }

            /* Apply angular velocity rotation */
            if (0.0 != cur->desc.lb_unk0.unk_44) {
                lbVector_RotateAboutUnitAxis(&link_dir,
                                             &cur->desc.lb_unk0.unk_38,
                                             cur->desc.lb_unk0.unk_44);
            }

            /* Apply max angle constraint */
            if (force_mag <
                cur->desc.lb_unk0.unk_8C * cur->desc.lb_unk0.unk_48)
            {
                clamp_dir = saved_dir;
                if (lbVector_Angle(&clamp_dir, &link_dir) >
                    cur->desc.lb_unk0.unk_88)
                {
                    PSVECCrossProduct(&clamp_dir, &link_dir, &clamp_axis);
                    lbVector_Normalize(&clamp_axis);
                    lbVector_RotateAboutUnitAxis(&clamp_dir, &clamp_axis,
                                                 cur->desc.lb_unk0.unk_88);
                    link_dir = clamp_dir;
                }
            }

            /* Apply convergence limit */
            if (cur->desc.lb_unk0.unk_50 > 0.0) {
                if (lbVector_Angle(&natural_dir, &link_dir) <
                    cur->desc.lb_unk0.unk_50)
                {
                    link_dir = natural_dir;
                } else {
                    PSVECCrossProduct(&link_dir, &natural_dir,
                                      &convergence_axis);
                    lbVector_Normalize(&convergence_axis);
                    lbVector_RotateAboutUnitAxis(&link_dir, &convergence_axis,
                                                 cur->desc.lb_unk0.unk_50);
                }
            }

            /* Apply max angle deviation */
            {
                f32 dev_angle = lbVector_Angle(&natural_dir, &link_dir);
                if (dev_angle > cur->desc.lb_unk0.unk_68) {
                    PSVECCrossProduct(&link_dir, &natural_dir,
                                      &deviation_axis);
                    lbVector_Normalize(&deviation_axis);
                    lbVector_RotateAboutUnitAxis(&link_dir, &deviation_axis,
                                                 dev_angle -
                                                     cur->desc.lb_unk0.unk_68);
                }
            }

            /* Collider avoidance */
            if (num_colliders != 0) {
                lbVector_Normalize(&link_dir);
                collider = colliders_raw;
                {
                    s32 ci;
                    for (ci = 0; ci < num_colliders; ci++) {
                        next_bone_pos.x =
                            link_dir.x * cur->desc.lb_unk0.unk_48 +
                            cur->desc.lb_unk0.unk_2C.x;
                        next_bone_pos.y =
                            link_dir.y * cur->desc.lb_unk0.unk_48 +
                            cur->desc.lb_unk0.unk_2C.y;
                        next_bone_pos.z =
                            link_dir.z * cur->desc.lb_unk0.unk_48 +
                            cur->desc.lb_unk0.unk_2C.z;

                        coll_dir.x =
                            collider->position.x - cur->desc.lb_unk0.unk_2C.x;
                        coll_dir.y =
                            collider->position.y - cur->desc.lb_unk0.unk_2C.y;
                        coll_dir.z =
                            collider->position.z - cur->desc.lb_unk0.unk_2C.z;

                        {
                            f32 coll_dist = sqrtf(coll_dir.z * coll_dir.z +
                                                  (coll_dir.x * coll_dir.x +
                                                   coll_dir.y * coll_dir.y));

                            if (coll_dist > collider->radius &&
                                lbColl_80005C44(
                                    &cur->desc.lb_unk0.unk_2C, &next_bone_pos,
                                    &collider->position, &collision_point,
                                    0.1f, collider->radius) != 0)
                            {
                                f32 coll_angle =
                                    lbVector_Angle(&coll_dir, &link_dir);
                                if (0.0 != coll_angle) {
                                    f32 adj_radius =
                                        (f32) (0.1 + (f64) collider->radius);
                                    f32 side_sq =
                                        sqrtf(coll_dist * coll_dist -
                                              adj_radius * adj_radius);
                                    {
                                        f32 avoidance_angle =
                                            atan2f(adj_radius, side_sq);
                                        if (avoidance_angle < 0.0f) {
                                            avoidance_angle = -avoidance_angle;
                                        }
                                        avoidance_angle -= coll_angle;
                                        if (avoidance_angle > 0.0) {
                                            PSVECCrossProduct(&coll_dir,
                                                              &link_dir,
                                                              &avoidance_axis);
                                            lbVector_Normalize(
                                                &avoidance_axis);
                                            lbVector_RotateAboutUnitAxis(
                                                &link_dir, &avoidance_axis,
                                                avoidance_angle);
                                        }
                                    }
                                }
                            }
                        }
                        collider++;
                    }
                }
            }

            /* Ground collision */
            if (ground_check != 0) {
                if (on_ground != 0) {
                    Vec3 floor_point, floor_normal;
                    UNUSED Vec3 unused;
                    int line_id;
                    u32 floor_flags;
                    Vec3 floor_cross;
                    Vec3 gnd_norm;
                    UNUSED Vec3 unused_b;

                    gnd_norm = lb_803B7280.v1;
                    lbVector_Normalize(&link_dir);
                    {
                        f32 end_x = link_dir.x * cur->desc.lb_unk0.unk_48 +
                                    cur->desc.lb_unk0.unk_2C.x;
                        f32 end_y = link_dir.y * cur->desc.lb_unk0.unk_48 +
                                    cur->desc.lb_unk0.unk_2C.y;
                        s32 floor_hit;
                        if (use_floor_fn != 0) {
                            floor_hit = lb_800103D8(
                                &floor_point, end_x, (f32) (1.0 + (f64) end_y),
                                end_x, (f32) ((f64) end_y - 1.0), pos_y);
                        } else {
                            sp8 = 0;
                            floor_hit = mpCheckFloor(
                                end_x, (f32) (1.0 + (f64) end_y), end_x,
                                (f32) ((f64) end_y - 1.0), 0.1f, &floor_point,
                                &line_id, &floor_flags, &floor_normal, -1, -1,
                                -1, NULL, NULL);
                        }
                        PSVECCrossProduct(&gnd_norm, &link_dir, &floor_cross);
                        lbVector_Normalize(&floor_cross);
                        lbVector_RotateAboutUnitAxis(&gnd_norm, &floor_cross,
                                                     1.5707964f);
                        link_dir = gnd_norm;
                        if (floor_hit != 0) {
                            on_ground = 1;
                        } else {
                            on_ground = 0;
                        }
                    }
                } else {
                    Vec3 floor_point2, floor_normal2;
                    UNUSED Vec3 unused2;
                    int line_id2;
                    u32 floor_flags2;
                    Vec3 floor_cross2;
                    Vec3 gnd_norm2;

                    gnd_norm2 = lb_803B7280.v2;
                    lbVector_Normalize(&link_dir);
                    {
                        s32 floor_hit2;
                        if (use_floor_fn != 0) {
                            floor_hit2 = lb_800103D8(
                                &floor_point2, cur->desc.lb_unk0.unk_2C.x,
                                (f32) (1.0 + (f64) cur->desc.lb_unk0.unk_2C.y),
                                cur->desc.lb_unk0.unk_2C.x,
                                cur->desc.lb_unk0.unk_2C.y, pos_y);
                        } else {
                            sp8 = 0;
                            floor_hit2 = mpCheckFloor(
                                cur->desc.lb_unk0.unk_2C.x,
                                (f32) (1.0 + (f64) cur->desc.lb_unk0.unk_2C.y),
                                cur->desc.lb_unk0.unk_2C.x,
                                cur->desc.lb_unk0.unk_2C.y, 0.1f,
                                &floor_point2, &line_id2, &floor_flags2,
                                &floor_normal2, -1, -1, -1, NULL, NULL);
                        }
                        if (floor_hit2 != 0) {
                            PSVECCrossProduct(&gnd_norm2, &link_dir,
                                              &floor_cross2);
                            lbVector_Normalize(&floor_cross2);
                            lbVector_RotateAboutUnitAxis(
                                &gnd_norm2, &floor_cross2, 1.5707964f);
                            on_ground = 1;
                            link_dir = gnd_norm2;
                        } else {
                            f32 end_x2 =
                                link_dir.x * cur->desc.lb_unk0.unk_48 +
                                cur->desc.lb_unk0.unk_2C.x;
                            f32 end_y2 =
                                link_dir.y * cur->desc.lb_unk0.unk_48 +
                                cur->desc.lb_unk0.unk_2C.y;
                            s32 floor_hit3;
                            if (use_floor_fn != 0) {
                                floor_hit3 = lb_800103D8(
                                    &floor_point2, cur->desc.lb_unk0.unk_2C.x,
                                    cur->desc.lb_unk0.unk_2C.y, end_x2, end_y2,
                                    pos_y);
                            } else {
                                sp8 = 0;
                                floor_hit3 = mpCheckFloor(
                                    cur->desc.lb_unk0.unk_2C.x,
                                    cur->desc.lb_unk0.unk_2C.y, end_x2, end_y2,
                                    0.1f, &floor_point2, &line_id2,
                                    &floor_flags2, &floor_normal2, -1, -1, -1,
                                    NULL, NULL);
                            }
                            if (floor_hit3 != 0) {
                                f32 height_diff =
                                    groundHeight(cur, &floor_point2);
                                f32 horiz_dist =
                                    sqrtf(-(height_diff * height_diff -
                                            cur->desc.lb_unk0.unk_48 *
                                                cur->desc.lb_unk0.unk_48));
                                f32 ground_angle =
                                    ABS(atan2f(horiz_dist, height_diff));
                                PSVECCrossProduct(&gnd_norm2, &link_dir,
                                                  &floor_cross2);
                                lbVector_Normalize(&floor_cross2);
                                lbVector_RotateAboutUnitAxis(
                                    &gnd_norm2, &floor_cross2, ground_angle);
                                on_ground = 1;
                                link_dir = gnd_norm2;
                            } else {
                                on_ground = 0;
                            }
                        }
                    }
                }
            }

            /* Compute angular difference and rotation axis */
            angle_diff = lbVector_Angle(&current_dir, &link_dir);
            PSVECCrossProduct(&current_dir, &link_dir, &rotation_axis);
            lbVector_Normalize(&rotation_axis);

            /* Rotate current_dir by angle_diff */
            {
                adj_dir = current_dir;
                lbVector_RotateAboutUnitAxis(&adj_dir, &rotation_axis,
                                             angle_diff);
                link_dir = adj_dir;
            }

            /* Store angular velocity */
            if (on_ground != 0) {
                cur->desc.lb_unk0.unk_44 = 0.0f;
            } else {
                cur->desc.lb_unk0.unk_44 =
                    lbVector_Angle(&saved_dir, &link_dir);
            }

            /* Dampen angular velocity */
            {
                f32 ang_vel = cur->desc.lb_unk0.unk_44;
                if (ang_vel < 0.0f) {
                    ang_vel = -ang_vel;
                }
                if (ang_vel > 0.0) {
                    PSVECCrossProduct(&saved_dir, &link_dir,
                                      &cur->desc.lb_unk0.unk_38);
                    lbVector_Normalize(&cur->desc.lb_unk0.unk_38);
                }
            }

            /* Apply damping to angular velocity */
            {
                f32 ang_vel2 = cur->desc.lb_unk0.unk_44;
                if (0.0 != ang_vel2) {
                    f32 damping = cur->desc.lb_unk0.unk_84;
                    if (ang_vel2 > damping) {
                        cur->desc.lb_unk0.unk_44 = ang_vel2 - damping;
                    } else if (ang_vel2 < -damping) {
                        cur->desc.lb_unk0.unk_44 = ang_vel2 + damping;
                    } else {
                        cur->desc.lb_unk0.unk_44 = 0.0f;
                    }
                }
            }
        }

        /* Update JObj rotation via quaternion if angle is significant */
        if (!approximatelyZero(angle_diff)) {
            PSMTXTranspose(parent_mtx, bone_mtx);
            PSMTXMultVec(bone_mtx, &rotation_axis, &local_axis);
            if (!approximatelyZeroVec3(local_axis)) {
                Quaternion rotation;
                HSD_QuatLib_8037ECE0(&local_axis, &angle_quat, angle_diff);
                euler_angles.x = jobj->rotate.x;
                euler_angles.y = jobj->rotate.y;
                euler_angles.z = jobj->rotate.z;
                EulerToQuat(&euler_angles, &euler_quat);
                HSD_QuatLib_8037EC4C(&angle_quat, &euler_quat, &result_quat);
                PSMTXQuat(bone_mtx, &result_quat);
                HSD_QuatLib_8037EB28(bone_mtx, (Vec3*) &rotation);
                HSD_JObjSetRotation(jobj, &rotation);
                HSD_JObjClearFlagsAll(jobj, 0x20000U);
            }
        }

        /* Dominant axis damping */
        {
            s32 axis = cur->desc.lb_unk0.unk_54;
            if (axis == -1) {
                f32 rot_z = HSD_JObjGetRotationZ(jobj);
                rot_z = rot_z * 0.9f;
                HSD_JObjSetRotationZ(jobj, rot_z);
            } else if (axis == 0) {
                f32 rot_x = HSD_JObjGetRotationX(jobj);
                rot_x = rot_x * 0.9f;
                HSD_JObjSetRotationX(jobj, rot_x);
            } else {
                f32 rot_y = HSD_JObjGetRotationY(jobj);
                rot_y = rot_y * 0.9f;
                HSD_JObjSetRotationY(jobj, rot_y);
            }
        }

        /* Update parent matrix for next iteration */
        PSMTXConcat(parent_mtx, trans_mtx, parent_mtx);
        lbVector_CreateEulerMatrix(temp_mtx, &jobj->rotate);
        PSMTXConcat(parent_mtx, temp_mtx, parent_mtx);
        PSMTXConcat(parent_mtx, scale_mtx, parent_mtx);

        jobj = jobj->child;
        loop_index += 1;
        cur = cur->next;
    }

    /* Tail node: compute final world position */
    PSMTXTrans(temp_mtx, jobj->translate.x, jobj->translate.y,
               jobj->translate.z);
    PSMTXConcat(parent_mtx, temp_mtx, parent_mtx);
    lbVector_CreateEulerMatrix(temp_mtx, &jobj->rotate);
    PSMTXConcat(parent_mtx, temp_mtx, parent_mtx);
    PSMTXScale(temp_mtx, jobj->scale.x, jobj->scale.y, jobj->scale.z);
    PSMTXConcat(parent_mtx, temp_mtx, parent_mtx);
    cur->desc.lb_unk0.unk_2C.x = parent_mtx[0][3];
    cur->desc.lb_unk0.unk_2C.y = parent_mtx[1][3];
    cur->desc.lb_unk0.unk_2C.z = parent_mtx[2][3];
}

void lb_800115F4(void)
{
    float total_scale = 0.0f;
    struct lb_80011A50_t* cur = lb_804D63B0;
    struct lb_80011A50_t* head;
    struct lb_80011A50_t* prev;

    while (cur != NULL) {
        if (cur->x0 == 1) {
            total_scale += cur->unk_scale;
        }
        cur->unk_scale -= cur->x24;
        if (cur->unk_scale < 0.0) {
            cur->unk_scale = 0.0;
        }
        if (cur->unk_count0 > 0) {
            --cur->unk_count0;
        }
        ++cur->unk_angle_int;
        if (cur->unk_count0 == 0) {
            prev = cur;
            cur = cur->next;
            if (prev == (head = lb_804D63B0)) {
                lb_804D63B0 = cur;
            } else {
                while (head->next != prev) {
                    head = head->next;
                }
                head->next = prev->next;
            }
            {
                struct lb_80011A50_t* temp = lb_804D63AC;
                lb_804D63AC = prev;
                prev->next = temp;
            }
        } else {
            cur = cur->next;
        }
    }

    if (total_scale > 0.1) {
        if (lb_804D63B4 > 0) {
            lb_804D63B4 = 2;
            return;
        }
        lb_804D63B4 = 1;
        return;
    }
    if (lb_804D63B4 > 0) {
        lb_804D63B4 = -1;
        return;
    }
    lb_804D63B4 = 0;
}

void lb_80011710(DynamicsDesc* arg0, DynamicsDesc* arg1)
{
    struct lb_00F9_UnkDesc1Inner* data0;
    struct DynamicsData* data1;
    int i;

    arg1->pos.x = arg0->pos.x;
    arg1->pos.y = arg0->pos.y;
    arg1->pos.z = arg0->pos.z;
    data1 = arg1->data;
    data0 = &arg0->data->desc.lb_unk1.array[0];
    for (data1 = arg1->data, i = 0; i < (int) arg0->count;
         data1 = data1->next, i++)
    {
        s32 tmp0, tmp1;
        data1->desc.lb_unk0.unk_4C = data0[i].unk_0;
        data1->desc.lb_unk0.unk_50 = data0[i].unk_4;
        data1->desc.lb_unk0.unk_58 = data0[i].unk_8;
        data1->desc.lb_unk0.unk_68 = data0[i].unk_18;
        data1->desc.lb_unk0.unk_6C = data0[i].unk_1C;
        data1->desc.lb_unk0.unk_78 = data0[i].unk_28;
        data1->desc.lb_unk0.unk_84 = data0[i].unk_34;
        data1->desc.lb_unk0.unk_88 = data0[i].unk_38;
        if (data1->desc.lb_unk0.unk_48 != 0.0) {
            data1->desc.lb_unk0.unk_8C =
                arg0->pos.z / data1->desc.lb_unk0.unk_48;
        } else {
            data1->desc.lb_unk0.unk_8C = 0.0f;
        }
    }
}

bool lb_800117F4(DynamicsDesc* arg0, GXColor* arg1, GXColor* arg2, int arg3,
                 u32 arg4)
{
    Mtx view_mtx;
    struct DynamicsData* cur;
    int i;
    PAD_STACK(8 * 4);

    if (arg1->a < 0xFF) {
        if (arg4 != 2) {
            return false;
        }
    } else if (arg4 != 0) {
        return false;
    }
    HSD_StateInitDirect(0, 2);
    HSD_CObjGetViewingMtx(HSD_CObjGetCurrent(), &view_mtx[0]);
    GXLoadPosMtxImm(&view_mtx[0], 0);
    GXSetLineWidth(12, GX_TO_ONE);
    GXBegin(GX_LINESTRIP, GX_VTXFMT0, arg0->count);
    for (cur = arg0->data, i = 0; cur != NULL; cur = cur->next, i++) {
        HSD_JObjSetMtxDirtyInline(cur->desc.lb_unk0.jobj);
        HSD_JObjSetupMatrix(cur->desc.lb_unk0.jobj);
        {
            float x = cur->desc.lb_unk0.jobj->mtx[0][3];
            float y = cur->desc.lb_unk0.jobj->mtx[1][3];
            float z = cur->desc.lb_unk0.jobj->mtx[2][3];
            if (i < arg3) {
                GXPosition3f32(x, y, z);
                GXColor4u8(arg1->r / 2, arg1->g / 2, arg1->b / 2, arg1->a);
            } else {
                GXPosition3f32(x, y, z);
                GXColor4u8(arg1->r, arg1->g, arg1->b, arg1->a);
            }
        }
    }
    return true;
}

void lb_800119DC(Vec3* arg0, int arg1, float arg2, float arg3, float arg4)
{
    struct lb_80011A50_t sp1C;
    sp1C.x0 = 2;
    sp1C.x1 = 0x64;
    sp1C.x4 = *arg0;
    sp1C.unk_scale = arg2;
    sp1C.x24 = arg3;
    sp1C.unk_count0 = arg1;
    sp1C.unk_angle_float = arg4;
    sp1C.x10 = -10000.0f;
    sp1C.x14 = 10000.0f;
    sp1C.x18 = 10000.0f;
    sp1C.x1C = -10000.0f;
    lb_800100B0(&sp1C, arg2);
}

struct lb_80011A50_t* lb_80011A50(Vec3* arg0, int arg1, float arg2, float arg3,
                                  float arg4, float arg5, float arg6,
                                  float arg7, float arg8)
{
    struct lb_80011A50_t x2C;
    x2C.x0 = 1;
    x2C.x1 = 0;
    x2C.x4 = *arg0;
    x2C.unk_scale = arg2;
    x2C.x24 = arg3;
    x2C.unk_count0 = arg1;
    x2C.unk_angle_float = arg4;
    x2C.x10 = arg5;
    x2C.x14 = arg6;
    x2C.x18 = arg7;
    x2C.x1C = arg8;
    return lb_800100B0(&x2C, arg2);
}

enum_t lb_80011ABC(void)
{
    return lb_804D63B4;
}
