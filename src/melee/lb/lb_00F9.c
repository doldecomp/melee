#include "lb_00F9.static.h"

#include "math.h"
#include "math_ppc.h"
#include "stdarg.h"
#include "stddef.h"

#include "baselib/debug.h"
#include "baselib/displayfunc.h"
#include "baselib/psstructs.h"
#include "baselib/rumble.h"
#include "baselib/tobj.h"
#include "dolphin/gx/GXCull.h"
#include "dolphin/gx/GXGeometry.h"
#include "dolphin/gx/GXLighting.h"
#include "dolphin/gx/GXPixel.h"
#include "dolphin/gx/GXTev.h"
#include "dolphin/gx/GXTexture.h"
#include "dolphin/gx/GXTransform.h"
#include "dolphin/gx/GXVert.h"
#include "dolphin/pad.h"

#include "lb/forward.h"

#include "lb/lbarchive.h"
#include "lb/lbcollision.h"
#include "lb/lbcommand.h"
#include "lb/lbdvd.h"
#include "lb/lbvector.h"
#include "lb/types.h"

#include <baselib/cobj.h>
#include <baselib/dobj.h>
#include <baselib/gobj.h>
#include <baselib/gobjgxlink.h>
#include <baselib/gobjobject.h>
#include <baselib/gobjuserdata.h>
#include <baselib/jobj.h>
#include <baselib/lobj.h>
#include <baselib/memory.h>
#include <baselib/quatlib.h>
#include <baselib/state.h>
#include <baselib/tev.h>
#include <melee/mp/mplib.h>
#include <melee/sc/types.h>
#include <MSL/trigf.h>

typedef bool (*lb_803BA248_fn)(ColorOverlay*);

struct lb_Collider {
    /* 0x00 */ char pad_00[0x0C];
    /* 0x0C */ f32 radius;
    /* 0x10 */ char pad_10[0x08];
    /* 0x18 */ Vec3 position;
    /* 0x24 */ char pad_24[0x04];
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

lb_803BA248_fn lb_803BA248[] = {
    lb_80013BB0, lb_80013BB8, lb_80013BE4, lb_80013C18, lb_80013D68,
    lb_80013E3C, lb_80013F78, lb_80013FF0, lb_80014014, lb_800140F8,
    lb_80014234, NULL,        NULL,        NULL,        NULL,
    NULL,        NULL,        NULL,        NULL,        NULL,
    NULL,        NULL,
};

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
    struct DynamicsData* next;
    struct lb_80011A50_t* next2;

    for (i = 0; i < 0x140; i++) {
        lb_804D63A0->entries[i].desc.lb_unk0.jobj = NULL;
        if (i < 0x13F) {
            next = &lb_804D63A0->entries[i] + 1;
        } else {
            next = NULL;
        }
        lb_804D63A0->entries[i].next = next;
    }

    cur_data = &lb_804D63A0->entries[0];

    for (i = 0; i < 8; i++) {
        lb_804D63A8->entries[i].x0 = 0;
        if (i < 7) {
            next2 = &lb_804D63A8->entries[i] + 1;
        } else {
            next2 = NULL;
        }
        lb_804D63A8->entries[i].next = next2;
    }

    lb_804D63AC = &lb_804D63A8->entries[0];
    lb_804D63B0 = NULL;
    lb_804D63B4 = 0;
}

void lb_8000FCDC(void)
{
    lb_804D63A0 = HSD_MemAlloc(0xBE00);
    lb_804D63A8 = HSD_MemAlloc(0x1C0);
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

void lb_8000FD48(HSD_JObj* jobj, DynamicsDesc* desc, size_t max_count)
{
    struct DynamicsData* prev;
    PAD_STACK(0x20);

    if (desc == NULL) {
        return;
    }

    if (jobj == NULL) {
        desc->data = NULL;
        return;
    }

    desc->count = 0;

    while ((s32) desc->count < (s32) max_count) {
        struct DynamicsData* entry;

        if ((s32) desc->count == 0) {
            entry = cur_data;
            if (entry == NULL) {
                entry = NULL;
            } else {
                cur_data = entry->next;
                entry->next = NULL;
            }
            prev = entry;
            desc->data = prev;
        } else {
            entry = cur_data;
            if (entry == NULL) {
                entry = NULL;
            } else {
                cur_data = entry->next;
                entry->next = NULL;
            }
            prev->next = entry;
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

    {
        struct DynamicsData* cur = desc->data;
        struct DynamicsData* next;

        while ((next = cur->next) != NULL) {
            f32 dx, dy, dz, dist_sq;

            dx = cur->desc.lb_unk0.unk_2C.x - next->desc.lb_unk0.unk_2C.x;
            dy = cur->desc.lb_unk0.unk_2C.y - next->desc.lb_unk0.unk_2C.y;
            dz = cur->desc.lb_unk0.unk_2C.z - next->desc.lb_unk0.unk_2C.z;
            dist_sq = dx * dx + dy * dy + dz * dz;
            if (dist_sq > 0.0f) {
                dist_sq = sqrtf(dist_sq);
            }
            cur->desc.lb_unk0.unk_48 = dist_sq;

            next = cur->next;
            {
                f32 tx, ty, tz;

                tx = next->desc.lb_unk0.translate.x;
                if (tx < 0.0f) {
                    tx = -tx;
                }
                ty = next->desc.lb_unk0.translate.y;
                if (ty < 0.0f) {
                    ty = -ty;
                }
                tz = next->desc.lb_unk0.translate.z;
                if (tz < 0.0f) {
                    tz = -tz;
                }

                if (tz > ty) {
                    if (tz > tx) {
                        cur->desc.lb_unk0.unk_54 = -1;
                    } else {
                        cur->desc.lb_unk0.unk_54 = 0;
                    }
                } else if (ty > tx) {
                    cur->desc.lb_unk0.unk_54 = 1;
                } else {
                    cur->desc.lb_unk0.unk_54 = 0;
                }
            }

            cur = cur->next;
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

void lb_800101C8(Vec3* arg0, Vec3* arg1)
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
    lbVector_Normalize(arg1);
}

float lb_800103B8(Vec3* a, Vec3* b)
{
    lb_800101C8(a, b);
}

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

void lb_8001044C(DynamicsDesc* desc, void* colliders_raw, int num_colliders,
                 float pos_y, bool use_floor_fn, Fighter_Part part,
                 int first_active, bool ground_check)
{
    Mtx parent_mtx, temp_mtx, bone_mtx, constrained_mtx, trans_mtx, scale_mtx;
    Vec3 natural_dir, current_dir, link_dir;
    Vec3 cross_vec, local_axis;
    Vec3 gnd_norm;
    Quaternion angle_quat, euler_quat, result_quat;
    Vec3 euler_angles;
    Vec3 collision_point;
    Vec3 floor_point, floor_normal;
    int line_id;
    u32 floor_flags;
    Vec3 floor_cross;
    Vec3 floor_point2, floor_normal2;
    int line_id2;
    u32 floor_flags2;
    Vec3 floor_cross2;
    s32 sp8;

    struct DynamicsData* cur;
    HSD_JObj* jobj;
    HSD_JObj* parent_jobj;
    struct lb_Collider* collider;
    s32 on_ground;
    s32 idx;

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
    idx = 0;

    if ((s32) part > 0) {
        s32 skip_count = 0;
        s32 rem8 = (s32) part - 8;
        if ((s32) part > 8) {
            s32 n = (u32) (rem8 + 7) >> 3;
            if (rem8 > 0) {
                do {
                    cur = cur->next->next->next->next->next->next->next->next;
                    idx += 8;
                    skip_count += 8;
                } while (--n);
            }
        }
        if (skip_count < (s32) part) {
            s32 rem = (s32) part - skip_count;
            do {
                cur = cur->next;
                skip_count++;
            } while (--rem);
        }
    }

    parent_jobj = cur->desc.lb_unk0.jobj->parent;
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
            Vec3 saved_dir = link_dir;

            /* Apply stiffness blend toward natural direction */
            if (cur->desc.lb_unk0.unk_4C * desc->pos.x < 1.0f) {
                f32 stiff_angle = lbVector_Angle(&link_dir, &current_dir);
                if (stiff_angle < 0.0f) {
                    stiff_angle = -stiff_angle;
                }
                if (stiff_angle != 0.0f) {
                    PSVECCrossProduct(&link_dir, &current_dir, &cross_vec);
                    lbVector_Normalize(&cross_vec);
                    lbVector_RotateAboutUnitAxis(
                        &link_dir, &cross_vec,
                        stiff_angle *
                            (f32) (1.0 - (f64) (cur->desc.lb_unk0.unk_4C *
                                                desc->pos.x)));
                }
            }

            /* Apply gravity influence */
            {
                Vec3 grav_dir = lb_803B7280.v0;
                f32 grav_angle = lbVector_Angle(&link_dir, &grav_dir);
                if (grav_angle != 0.0f) {
                    f32 grav_rot = cur->desc.lb_unk0.unk_8C * sinf(grav_angle);
                    if (grav_rot < 0.0f) {
                        grav_rot = -grav_rot;
                    }
                    PSVECCrossProduct(&link_dir, &grav_dir, &cross_vec);
                    lbVector_Normalize(&cross_vec);
                    lbVector_RotateAboutUnitAxis(&link_dir, &cross_vec,
                                                 grav_rot);
                }
            }

            /* Apply interaction force */
            force_mag = 0.0f;
            if (lb_804D63B0 != NULL && first_active <= idx) {
                struct DynamicsData* next_node = cur->next;
                Vec3 next_pos = next_node->desc.lb_unk0.unk_2C;
                Vec3 force_dir;
                force_mag = lb_800103B8(&next_pos, &force_dir);
                {
                    f32 force_angle = lbVector_Angle(&link_dir, &force_dir);
                    if (force_angle != 0.0f) {
                        f32 force_rot = (force_mag * sinf(force_angle)) /
                                        cur->desc.lb_unk0.unk_48;
                        if (force_rot < 0.0f) {
                            force_rot = -force_rot;
                        }
                        PSVECCrossProduct(&link_dir, &force_dir, &cross_vec);
                        lbVector_Normalize(&cross_vec);
                        lbVector_RotateAboutUnitAxis(&link_dir, &cross_vec,
                                                     force_rot);
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
                Vec3 clamp_dir = saved_dir;
                if (lbVector_Angle(&clamp_dir, &link_dir) >
                    cur->desc.lb_unk0.unk_88)
                {
                    PSVECCrossProduct(&clamp_dir, &link_dir, &cross_vec);
                    lbVector_Normalize(&cross_vec);
                    lbVector_RotateAboutUnitAxis(&clamp_dir, &cross_vec,
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
                    PSVECCrossProduct(&link_dir, &natural_dir, &cross_vec);
                    lbVector_Normalize(&cross_vec);
                    lbVector_RotateAboutUnitAxis(&link_dir, &cross_vec,
                                                 cur->desc.lb_unk0.unk_50);
                }
            }

            /* Apply max angle deviation */
            {
                f32 dev_angle = lbVector_Angle(&natural_dir, &link_dir);
                if (dev_angle > cur->desc.lb_unk0.unk_68) {
                    PSVECCrossProduct(&link_dir, &natural_dir, &cross_vec);
                    lbVector_Normalize(&cross_vec);
                    lbVector_RotateAboutUnitAxis(&link_dir, &cross_vec,
                                                 dev_angle -
                                                     cur->desc.lb_unk0.unk_68);
                }
            }

            /* Collider avoidance */
            if (num_colliders != 0) {
                lbVector_Normalize(&link_dir);
                collider = (struct lb_Collider*) colliders_raw;
                {
                    s32 ci;
                    for (ci = 0; ci < num_colliders; ci++) {
                        Vec3 coll_dir;
                        f32 bone_len = cur->desc.lb_unk0.unk_48;
                        Vec3 next_bone_pos;
                        next_bone_pos.x =
                            link_dir.x * bone_len + cur->desc.lb_unk0.unk_2C.x;
                        next_bone_pos.y =
                            link_dir.y * bone_len + cur->desc.lb_unk0.unk_2C.y;
                        next_bone_pos.z =
                            link_dir.z * bone_len + cur->desc.lb_unk0.unk_2C.z;

                        coll_dir.x =
                            collider->position.x - cur->desc.lb_unk0.unk_2C.x;
                        coll_dir.y =
                            collider->position.y - cur->desc.lb_unk0.unk_2C.y;
                        coll_dir.z =
                            collider->position.z - cur->desc.lb_unk0.unk_2C.z;

                        {
                            f32 coll_dist = coll_dir.z * coll_dir.z +
                                            (coll_dir.x * coll_dir.x +
                                             coll_dir.y * coll_dir.y);
                            if (coll_dist > 0.0f) {
                                coll_dist = sqrtf(coll_dist);
                            }

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
                                    f32 side_sq = coll_dist * coll_dist -
                                                  adj_radius * adj_radius;
                                    if (side_sq > 0.0f) {
                                        side_sq = sqrtf(side_sq);
                                    }
                                    {
                                        f32 avoidance_angle =
                                            atan2f(adj_radius, side_sq);
                                        avoidance_angle = ABS(avoidance_angle);
                                        avoidance_angle -= coll_angle;
                                        if (avoidance_angle > 0.0) {
                                            PSVECCrossProduct(&coll_dir,
                                                              &link_dir,
                                                              &cross_vec);
                                            lbVector_Normalize(&cross_vec);
                                            lbVector_RotateAboutUnitAxis(
                                                &link_dir, &cross_vec,
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
                    gnd_norm = lb_803B7280.v1;
                    lbVector_Normalize(&link_dir);
                    {
                        f32 bone_len = cur->desc.lb_unk0.unk_48;
                        f32 end_x =
                            link_dir.x * bone_len + cur->desc.lb_unk0.unk_2C.x;
                        f32 end_y =
                            link_dir.y * bone_len + cur->desc.lb_unk0.unk_2C.y;
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
                    gnd_norm = lb_803B7280.v2;
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
                            PSVECCrossProduct(&gnd_norm, &link_dir,
                                              &floor_cross2);
                            lbVector_Normalize(&floor_cross2);
                            lbVector_RotateAboutUnitAxis(
                                &gnd_norm, &floor_cross2, 1.5707964f);
                            on_ground = 1;
                            link_dir = gnd_norm;
                        } else {
                            f32 bone_len = cur->desc.lb_unk0.unk_48;
                            f32 end_x2 = link_dir.x * bone_len +
                                         cur->desc.lb_unk0.unk_2C.x;
                            f32 end_y2 = link_dir.y * bone_len +
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
                                f32 height_diff = cur->desc.lb_unk0.unk_2C.y -
                                                  floor_point2.y;
                                f32 horiz_sq;
                                if (height_diff < 0.0f) {
                                    height_diff = -height_diff;
                                }
                                horiz_sq = -(height_diff * height_diff -
                                             bone_len * bone_len);
                                if (horiz_sq > 0.0f) {
                                    horiz_sq = sqrtf(horiz_sq);
                                }
                                {
                                    f32 ground_angle =
                                        atan2f(horiz_sq, height_diff);
                                    if (ground_angle < 0.0f) {
                                        ground_angle = -ground_angle;
                                    }
                                    PSVECCrossProduct(&gnd_norm, &link_dir,
                                                      &floor_cross2);
                                    lbVector_Normalize(&floor_cross2);
                                    lbVector_RotateAboutUnitAxis(&gnd_norm,
                                                                 &floor_cross2,
                                                                 ground_angle);
                                    on_ground = 1;
                                    link_dir = gnd_norm;
                                }
                            } else {
                                on_ground = 0;
                            }
                        }
                    }
                }
            }

            /* Compute angular difference and rotation axis */
            angle_diff = lbVector_Angle(&current_dir, &link_dir);
            PSVECCrossProduct(&current_dir, &link_dir, &cross_vec);
            lbVector_Normalize(&cross_vec);

            /* Rotate current_dir by angle_diff */
            {
                Vec3 adj_dir = current_dir;
                lbVector_RotateAboutUnitAxis(&adj_dir, &cross_vec, angle_diff);
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
        if (!(angle_diff < 0.00001f && angle_diff > -0.00001f)) {
            PSMTXTranspose(parent_mtx, bone_mtx);
            PSMTXMultVec(bone_mtx, &cross_vec, &local_axis);
            if (local_axis.x >= 0.00001f || local_axis.x <= -0.00001f ||
                local_axis.y >= 0.00001f || local_axis.y <= -0.00001f ||
                local_axis.z >= 0.00001f || local_axis.z <= -0.00001f)
            {
                HSD_QuatLib_8037ECE0(&local_axis, &angle_quat, angle_diff);
                euler_angles.x = jobj->rotate.x;
                euler_angles.y = jobj->rotate.y;
                euler_angles.z = jobj->rotate.z;
                EulerToQuat(&euler_angles, &euler_quat);
                HSD_QuatLib_8037EC4C(&angle_quat, &euler_quat, &result_quat);
                PSMTXQuat(bone_mtx, &result_quat);
                HSD_QuatLib_8037EB28(bone_mtx, &euler_angles);
                HSD_JObjSetRotation(jobj, &euler_quat);
                if (!(jobj->flags & JOBJ_MTX_INDEP_SRT)) {
                    HSD_JObjSetMtxDirty(jobj);
                }
                HSD_JObjClearFlagsAll(jobj, 0x20000U);
            }
        }

        /* Dominant axis damping */
        {
            s32 axis = cur->desc.lb_unk0.unk_54;
            if (axis == -1) {
                f32 rot_z = HSD_JObjGetRotationZ(jobj);
                HSD_JObjSetRotationZ(jobj, 0.9f * rot_z);
            } else if (axis == 0) {
                f32 rot_x = HSD_JObjGetRotationX(jobj);
                HSD_JObjSetRotationX(jobj, 0.9f * rot_x);
            } else {
                f32 rot_y = HSD_JObjGetRotationY(jobj);
                HSD_JObjSetRotationY(jobj, 0.9f * rot_y);
            }
        }

        /* Update parent matrix for next iteration */
        PSMTXConcat(parent_mtx, trans_mtx, parent_mtx);
        lbVector_CreateEulerMatrix(temp_mtx, &jobj->rotate);
        PSMTXConcat(parent_mtx, temp_mtx, parent_mtx);
        PSMTXConcat(parent_mtx, scale_mtx, parent_mtx);

        jobj = jobj->child;
        idx += 1;
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

static inline double inlineB0(void)
{
    float ret = 0.0f;
    struct lb_80011A50_t* cur = lb_804D63B0;

    while (cur != NULL) {
        if (cur->x0 == 1) {
            ret += cur->unk_scale;
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
            struct lb_80011A50_t* var_r3 = lb_804D63B0;
            struct lb_80011A50_t* prev = cur;
            cur = cur->next;
            if (prev == var_r3) {
                lb_804D63B0 = cur;
            } else {
                while (var_r3->next != prev) {
                    var_r3 = var_r3->next;
                }
                var_r3->next = prev->next;
            }
            {
                /// @todo inline appears in #lb_800115F4
                struct lb_80011A50_t* temp = lb_804D63AC;
                lb_804D63AC = prev;
                prev->next = temp;
            }
        } else {
            cur = cur->next;
        }
    }
    return ret;
}

void lb_800115F4(void)
{
    if (inlineB0() > 0.1) {
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

HSD_LObj* lb_80011AC4(LightList** list)
{
    HSD_LObj* prev;
    HSD_LObj* curr;
    HSD_LObj* first;
    HSD_LightAnim** temp_r4;

    prev = NULL;
    while (*list != NULL) {
        curr = HSD_LObjLoadDesc((*list)->desc);
        temp_r4 = (*list)->anims;
        if (temp_r4 != NULL) {
            HSD_LObjAddAnimAll(curr, temp_r4[0]);
        }
        if (prev != NULL) {
            HSD_LObjSetNext(prev, curr);
        } else {
            first = curr;
        }
        prev = curr;
        list++;
    }
    return first;
}

void lb_80011B74(HSD_DObj* dobj, u32 flags)
{
    if (dobj->next != NULL) {
        lb_80011B74(dobj->next, flags);
    }
    dobj->mobj->rendermode |= flags;
}

#pragma inline_depth(2)
void lb_80011C18(HSD_JObj* jobj, u32 flags)
{
    HSD_JObj* cur;

    cur = jobj->child;
    if (cur != NULL) {
        if (cur->child != NULL) {
            lb_80011C18(cur->child, flags);
        }
        if (cur->next != NULL) {
            lb_80011C18(cur->next, flags);
        }
        if (checkJObjFlags(cur)) {
            if (cur->u.dobj != NULL) {
                lb_80011B74(cur->u.dobj, flags);
            }
        }
    }

    cur = jobj->next;
    if (cur != NULL) {
        if (cur->child != NULL) {
            lb_80011C18(cur->child, flags);
        }
        if (cur->next != NULL) {
            lb_80011C18(cur->next, flags);
        }
        if (checkJObjFlags(cur)) {
            if (cur->u.dobj != NULL) {
                lb_80011B74(cur->u.dobj, flags);
            }
        }
    }

    if (checkJObjFlags(jobj)) {
        HSD_DObj* dobj = jobj->u.dobj;
        if (dobj != NULL) {
            if (dobj->next != NULL) {
                lb_80011B74(dobj->next, flags);
            }
            dobj->mobj->rendermode |= flags;
        }
    }
}
#pragma inline_depth(8)
/**
 * @note: The number of HSD_JObjs that get passed into arg1 is the number of
 * variable arguments passed until -1 is passed.
 */
int lb_80011E24(HSD_JObj* root, HSD_JObj** result, ...)
{
    va_list ap;
    HSD_JObj** out;
    HSD_JObj* jobj;
    HSD_JObj* saved;
    HSD_JObj* next_node;
    int found;
    int prev;
    int cur;
    s32 target;

    out = result;
    found = 0;
    prev = -1;

    if (root == NULL || out == NULL) {
        return 0;
    }

    va_start(ap, result);
    for (;;) {
        target = va_arg(ap, s32);
        if (target == -1) {
            break;
        }
        if (prev > target || prev == -1) {
            jobj = root;
            cur = 0;
        } else {
            cur = prev;
        }

        while (jobj != NULL) {
            if (cur == target) {
                break;
            }
            saved = jobj;
            if (!(jobj->flags & JOBJ_INSTANCE) &&
                HSD_JObjGetChild(jobj) != NULL)
            {
                next_node = HSD_JObjGetChild(jobj);
            } else if (HSD_JObjGetNext(jobj) != NULL) {
                next_node = HSD_JObjGetNext(jobj);
            } else {
                while (true) {
                    if (HSD_JObjGetParent(saved) == NULL) {
                        next_node = NULL;
                        break;
                    }
                    if (HSD_JObjGetNext(HSD_JObjGetParent(saved)) != NULL) {
                        next_node = HSD_JObjGetNext(HSD_JObjGetParent(saved));
                        break;
                    }
                    saved = HSD_JObjGetParent(saved);
                }
            }
            jobj = next_node;
            cur++;
        }

        *out = jobj;
        prev = cur;
        out++;
        if (jobj != NULL) {
            found++;
        }
    }
    va_end(ap);

    return found;
}

int lb_8001204C(HSD_JObj* root, HSD_JObj** result, u16* indices, int count)
{
    HSD_JObj** out;
    u16* idx;
    HSD_JObj* jobj;
    HSD_JObj* saved;
    HSD_JObj* next_node;
    int found;
    int prev;
    int cur;
    int i;
    u16 target;

    out = result;
    idx = indices;
    found = 0;
    prev = -1;

    if (root == NULL || out == NULL || idx == NULL || count == 0) {
        return 0;
    }

    for (i = count; i > 0; i--) {
        target = *idx;
        if (prev > (s32) target || prev == -1) {
            jobj = root;
            cur = 0;
        } else {
            cur = prev;
        }

        while (jobj != NULL) {
            if (cur == (s32) target) {
                break;
            }
            saved = jobj;
            if (!(jobj->flags & JOBJ_INSTANCE) &&
                HSD_JObjGetChild(jobj) != NULL)
            {
                next_node = HSD_JObjGetChild(jobj);
            } else if (HSD_JObjGetNext(jobj) != NULL) {
                next_node = HSD_JObjGetNext(jobj);
            } else {
                while (true) {
                    if (HSD_JObjGetParent(saved) == NULL) {
                        next_node = NULL;
                        break;
                    }
                    if (HSD_JObjGetNext(HSD_JObjGetParent(saved)) != NULL) {
                        next_node = (saved = HSD_JObjGetNext(
                                         HSD_JObjGetParent(saved)));
                        break;
                    }
                    saved = HSD_JObjGetParent(saved);
                }
            }
            jobj = next_node;
            cur++;
        }

        *out = jobj;
        prev = cur;
        out++;
        if (jobj != NULL) {
            found++;
        }
        idx++;
    }

    return found;
}

static void* setImageFromPreloadedArchive(HSD_ImageDesc* image_desc,
                                          s16 entry_num)
{
    void* image_ptr = lbDvd_GetPreloadedArchive(entry_num);
    image_desc->image_ptr = image_ptr;
    return image_ptr;
}

HSD_ImageDesc* lb_800121FC(HSD_ImageDesc* image_desc, int width, int height,
                           GXTexFmt format, s16 entry_num)
{
    image_desc->width = width;
    image_desc->height = height;
    image_desc->mipmap = 0;
    image_desc->minLOD = 0.0f;
    image_desc->maxLOD = 0.0f;
    image_desc->format = format;
    HSD_ASSERT(41, !image_desc->image_ptr);
    {
        size_t buffer_size = GXGetTexBufferSize(
            image_desc->width, image_desc->height, image_desc->format, 0, 0);
        if (entry_num == 0 ||
            !setImageFromPreloadedArchive(image_desc, entry_num))
        {
            image_desc->image_ptr = HSD_MemAlloc((buffer_size + 0x1F) & ~0x1F);
        }
    }
    return image_desc;
}

void lb_800122C8(HSD_ImageDesc* image_desc, u16 origx, u16 origy, bool clear)
{
    HSD_ImageDescCopyFromEFB(image_desc, origx, origy, clear, true);
}

void lb_800122F0(HSD_ImageDesc* img, GXTexObj* tex, f32 factor)
{
    GXColor color0, color1, color2;
    f32 temp;
    f32 mul179;

    temp = 120.0f * factor;
    mul179 = 179.0f * factor;

    color0.r = (u8) (s8) (255.0f - mul179);
    color1.r = (u8) (s8) (150.0f * factor);
    color2.r = (u8) (s8) (29.0f * factor);

    color0.g = (u8) (s8) (68.4f * factor);
    color1.g = (u8) (s8) (255.0f - temp);
    color2.g = (u8) (s8) (26.099998f * factor);

    color0.b = (u8) (s8) (60.8f * factor);
    color1.b = (u8) (s8) temp;
    color2.b = (u8) (s8) - ((231.8f * factor) - 255.0f);

    color0.a = 0;
    color1.a = 0;

    GXInitTexObj(tex, img->image_ptr, img->width, img->height, img->format,
                 GX_CLAMP, GX_CLAMP, (u8) img->mipmap);
    GXClearVtxDesc();
    GXSetCullMode(GX_CULL_BACK);
    GXSetNumTexGens(1);
    GXSetZMode(0, GX_ALWAYS, 0);
    GXLoadTexObj(tex, GX_TEXMAP0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_TEX_S, GX_RGBA6, 0);
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_RGBA6, 0);
    GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);

    if (factor != 0.0f) {
        GXSetNumTevStages(3);
        GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
        GXSetTevOrder(GX_TEVSTAGE1, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
        GXSetTevOrder(GX_TEVSTAGE2, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
        GXSetTevKColor(GX_KCOLOR0, color0);
        GXSetTevKColor(GX_KCOLOR1, color1);
        GXSetTevKColor(GX_KCOLOR2, color2);
        GXSetTevKColorSel(GX_TEVSTAGE0, GX_TEV_KCSEL_K0);
        GXSetTevKColorSel(GX_TEVSTAGE1, GX_TEV_KCSEL_K1);
        GXSetTevKColorSel(GX_TEVSTAGE2, GX_TEV_KCSEL_K2);
        GXSetTevSwapMode(GX_TEVSTAGE0, GX_TEV_SWAP1, GX_TEV_SWAP1);
        GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_TEXC, GX_CC_KONST,
                        GX_CC_ZERO);
        GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 1,
                        GX_TEVPREV);
        GXSetTevSwapMode(GX_TEVSTAGE1, GX_TEV_SWAP2, GX_TEV_SWAP2);
        GXSetTevColorIn(GX_TEVSTAGE1, GX_CC_ZERO, GX_CC_TEXC, GX_CC_KONST,
                        GX_CC_CPREV);
        GXSetTevColorOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 1,
                        GX_TEVPREV);
        GXSetTevSwapMode(GX_TEVSTAGE2, GX_TEV_SWAP3, GX_TEV_SWAP3);
        GXSetTevColorIn(GX_TEVSTAGE2, GX_CC_ZERO, GX_CC_TEXC, GX_CC_KONST,
                        GX_CC_CPREV);
        GXSetTevColorOp(GX_TEVSTAGE2, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 1,
                        GX_TEVPREV);
        GXSetTevAlphaIn(GX_TEVSTAGE1, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO,
                        GX_CA_APREV);
        GXSetTevAlphaOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 1,
                        GX_TEVPREV);
        GXSetTevAlphaIn(GX_TEVSTAGE2, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO,
                        GX_CA_APREV);
        GXSetTevAlphaOp(GX_TEVSTAGE2, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 1,
                        GX_TEVPREV);
    } else {
        GXSetNumTevStages(1);
        GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
        GXSetTevSwapMode(GX_TEVSTAGE0, GX_TEV_SWAP0, GX_TEV_SWAP0);
        GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO,
                        GX_CC_TEXC);
        GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 1,
                        GX_TEVPREV);
    }

    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA,
                   GX_LO_CLEAR);
    GXSetColorUpdate(1);
    GXSetAlphaCompare(GX_GEQUAL, 0, GX_AOP_OR, GX_GEQUAL, 0);
}

void lb_8001271C(GXTexObj* arg0, float x0, float arg2, float tex_width,
                 float tex_height, float scale_x, float scale_y)
{
    f32 t;
    f32 new_var;
    f32 s;
    f32 new_var2;
    f32 w, h, y0, x1, y_sum, y1;
    PAD_STACK(8);

    t = tex_width / GXGetTexObjWidth(arg0);
    s = tex_height / GXGetTexObjHeight(arg0);

    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    w = tex_width * scale_x;
    h = tex_height * scale_y;
    y0 = -arg2;
    GXPosition2f32(x0, y0);
    x1 = x0 + w;
    new_var = arg2;
    y_sum = new_var + h;
    GXTexCoord2f32(0.0f, new_var2 = 0.0f);
    GXPosition2f32(x1, y0);
    if ((!x1) && (!x1)) {
    }
    GXTexCoord2f32(s, 0.0f);
    y1 = -y_sum;
    GXPosition2f32(x1, y1);
    GXTexCoord2f32(s, t);
    GXPosition2f32(x0, y1);
    y1 = new_var2;
    GXTexCoord2f32(y1, t);
    GXEnd();
}

void lb_8001285C(HSD_ImageDesc* image_desc, GXTexObj* tex_obj)
{
    PAD_STACK(4);
    GXInitTexObj(tex_obj, image_desc->image_ptr, image_desc->width,
                 image_desc->height, image_desc->format, GX_CLAMP, GX_CLAMP,
                 image_desc->mipmap);
    GXGetTexObjFmt(tex_obj);
    GXClearVtxDesc();
    GXSetCullMode(GX_CULL_BACK);
    GXSetNumTexGens(1);
    GXSetNumTevStages(1);
    GXSetZMode(0, GX_ALWAYS, 0);
    GXLoadTexObj(tex_obj, GX_TEXMAP0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_TEX_S, GX_RGBA6, 0);
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_RGBA6, 0);
    GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ONE,
                    GX_CC_TEXC);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 1,
                    GX_TEVPREV);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA,
                   GX_LO_CLEAR);
}

void lb_80012994(HSD_ImageDesc* img, u8 alpha, u8 blur_size, f32 x, f32 y,
                 f32 scale_x, f32 scale_y, f32 color_factor)
{
    GXTexObj tex;
    GXColor color;
    u16 w = img->width;
    u16 h = img->height;
    f32 off1 = (f32) blur_size * 0.015625f;
    f32 off2 = 2.0f * off1;
    f32 x_p1, x_m1, y_p1, y_m1;
    f32 x_p2, x_m2, y_p2, y_m2;

    lb_800122F0(img, &tex, color_factor);
    PAD_STACK(88);

    color.a = alpha;
    GXSetTevColor(GX_TEVREG0, color);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_TEXA, GX_CA_ZERO, GX_CA_A0,
                    GX_CA_ZERO);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 1,
                    GX_TEVPREV);
    lb_8001271C(&tex, x, y, (f32) w, (f32) h, scale_x, scale_y);

    color.a = 0x7F;
    GXSetTevColor(GX_TEVREG0, color);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_TEXA, GX_CA_ZERO, GX_CA_A0,
                    GX_CA_ZERO);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 1,
                    GX_TEVPREV);
    x_p1 = x + off1;
    lb_8001271C(&tex, x_p1, y, (f32) w, (f32) h, scale_x, scale_y);

    color.a = 0xA9;
    GXSetTevColor(GX_TEVREG0, color);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_TEXA, GX_CA_ZERO, GX_CA_A0,
                    GX_CA_ZERO);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 1,
                    GX_TEVPREV);
    x_m1 = x - off1;
    lb_8001271C(&tex, x_m1, y, (f32) w, (f32) h, scale_x, scale_y);

    color.a = 0xBF;
    GXSetTevColor(GX_TEVREG0, color);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_TEXA, GX_CA_ZERO, GX_CA_A0,
                    GX_CA_ZERO);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 1,
                    GX_TEVPREV);
    y_p1 = y + off1;
    lb_8001271C(&tex, x, y_p1, (f32) w, (f32) h, scale_x, scale_y);

    color.a = 0xCC;
    GXSetTevColor(GX_TEVREG0, color);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_TEXA, GX_CA_ZERO, GX_CA_A0,
                    GX_CA_ZERO);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 1,
                    GX_TEVPREV);
    y_m1 = y - off1;
    lb_8001271C(&tex, x, y_m1, (f32) w, (f32) h, scale_x, scale_y);

    color.a = 0xD4;
    GXSetTevColor(GX_TEVREG0, color);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_TEXA, GX_CA_ZERO, GX_CA_A0,
                    GX_CA_ZERO);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 1,
                    GX_TEVPREV);
    lb_8001271C(&tex, x_p1, y_p1, (f32) w, (f32) h, scale_x, scale_y);

    color.a = 0xDA;
    GXSetTevColor(GX_TEVREG0, color);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_TEXA, GX_CA_ZERO, GX_CA_A0,
                    GX_CA_ZERO);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 1,
                    GX_TEVPREV);
    lb_8001271C(&tex, x_m1, y_m1, (f32) w, (f32) h, scale_x, scale_y);

    color.a = 0xDF;
    GXSetTevColor(GX_TEVREG0, color);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_TEXA, GX_CA_ZERO, GX_CA_A0,
                    GX_CA_ZERO);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 1,
                    GX_TEVPREV);
    lb_8001271C(&tex, x_p1, y_m1, (f32) w, (f32) h, scale_x, scale_y);

    color.a = 0xE2;
    GXSetTevColor(GX_TEVREG0, color);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_TEXA, GX_CA_ZERO, GX_CA_A0,
                    GX_CA_ZERO);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 1,
                    GX_TEVPREV);
    lb_8001271C(&tex, x_m1, y_p1, (f32) w, (f32) h, scale_x, scale_y);

    color.a = 0xE5;
    GXSetTevColor(GX_TEVREG0, color);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_TEXA, GX_CA_ZERO, GX_CA_A0,
                    GX_CA_ZERO);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 1,
                    GX_TEVPREV);
    x_p2 = x + off2;
    lb_8001271C(&tex, x_p2, y, (f32) w, (f32) h, scale_x, scale_y);

    color.a = 0xE7;
    GXSetTevColor(GX_TEVREG0, color);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_TEXA, GX_CA_ZERO, GX_CA_A0,
                    GX_CA_ZERO);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 1,
                    GX_TEVPREV);
    x_m2 = x - off2;
    lb_8001271C(&tex, x_m2, y, (f32) w, (f32) h, scale_x, scale_y);

    color.a = 0xE9;
    GXSetTevColor(GX_TEVREG0, color);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_TEXA, GX_CA_ZERO, GX_CA_A0,
                    GX_CA_ZERO);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 1,
                    GX_TEVPREV);
    lb_8001271C(&tex, x_p2, y_p1, (f32) w, (f32) h, scale_x, scale_y);

    color.a = 0xEB;
    GXSetTevColor(GX_TEVREG0, color);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_TEXA, GX_CA_ZERO, GX_CA_A0,
                    GX_CA_ZERO);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 1,
                    GX_TEVPREV);
    lb_8001271C(&tex, x_m2, y_p1, (f32) w, (f32) h, scale_x, scale_y);

    color.a = 0xEC;
    GXSetTevColor(GX_TEVREG0, color);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_TEXA, GX_CA_ZERO, GX_CA_A0,
                    GX_CA_ZERO);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 1,
                    GX_TEVPREV);
    lb_8001271C(&tex, x_p2, y_m1, (f32) w, (f32) h, scale_x, scale_y);

    color.a = 0xEE;
    GXSetTevColor(GX_TEVREG0, color);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_TEXA, GX_CA_ZERO, GX_CA_A0,
                    GX_CA_ZERO);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 1,
                    GX_TEVPREV);
    lb_8001271C(&tex, x_m2, y_m1, (f32) w, (f32) h, scale_x, scale_y);

    color.a = 0xEF;
    GXSetTevColor(GX_TEVREG0, color);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_TEXA, GX_CA_ZERO, GX_CA_A0,
                    GX_CA_ZERO);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 1,
                    GX_TEVPREV);
    y_p2 = y + off2;
    lb_8001271C(&tex, x, y_p2, (f32) w, (f32) h, scale_x, scale_y);

    color.a = 0xF0;
    GXSetTevColor(GX_TEVREG0, color);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_TEXA, GX_CA_ZERO, GX_CA_A0,
                    GX_CA_ZERO);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 1,
                    GX_TEVPREV);
    y_m2 = y - off2;
    lb_8001271C(&tex, x, y_m2, (f32) w, (f32) h, scale_x, scale_y);

    color.a = 0xF0;
    GXSetTevColor(GX_TEVREG0, color);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_TEXA, GX_CA_ZERO, GX_CA_A0,
                    GX_CA_ZERO);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 1,
                    GX_TEVPREV);
    lb_8001271C(&tex, x_p1, y_p2, (f32) w, (f32) h, scale_x, scale_y);

    color.a = 0xF1;
    GXSetTevColor(GX_TEVREG0, color);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_TEXA, GX_CA_ZERO, GX_CA_A0,
                    GX_CA_ZERO);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 1,
                    GX_TEVPREV);
    lb_8001271C(&tex, x_p1, y_m2, (f32) w, (f32) h, scale_x, scale_y);

    color.a = 0xF2;
    GXSetTevColor(GX_TEVREG0, color);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_TEXA, GX_CA_ZERO, GX_CA_A0,
                    GX_CA_ZERO);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 1,
                    GX_TEVPREV);
    lb_8001271C(&tex, x_m1, y_p2, (f32) w, (f32) h, scale_x, scale_y);

    color.a = 0xF2;
    GXSetTevColor(GX_TEVREG0, color);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_TEXA, GX_CA_ZERO, GX_CA_A0,
                    GX_CA_ZERO);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 1,
                    GX_TEVPREV);
    lb_8001271C(&tex, x_m1, y_m2, (f32) w, (f32) h, scale_x, scale_y);

    HSD_StateInvalidate(2);
}
static struct {
    u8 pad_0[0x28];
    HSD_Chan chan0;
    HSD_Chan chan1;
} lb_803BA1C0;

void fn_80013614(HSD_GObj* gobj)
{
    struct CameraBlurData* data = gobj->user_data;
    Mtx view_mtx;
    Mtx view_mtx2;
    GXTexObj tex_obj;
    GXColor color;
    PAD_STACK(16);

    if (data->x18 != NULL) {
        data->x18(gobj);
    }

    if (data->x12 == 1) {
        HSD_CObj* cobj = (HSD_CObj*) gobj->hsd_obj;
        f32 alpha = data->x20;
        u8 x11 = data->x11;
        u8 x10 = data->x10;
        f32 xC = data->xC;
        f32 x8 = data->x8;
        f32 x4 = data->x4;
        f32 x0 = data->x0;
        HSD_ImageDesc* image = data->x1C;

        HSD_CObjSetCurrent(cobj);
        HSD_StateSetZMode(0, 7, 0);
        GXSetCurrentMtx(0);
        HSD_CObjGetViewingMtx(HSD_CObjGetCurrent(), view_mtx);
        GXLoadPosMtxImm(view_mtx, 0);
        GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, 0x3C, 0,
                          0x7D);
        HSD_SetupChannel(&lb_803BA1C0.chan0);
        HSD_SetupChannel(&lb_803BA1C0.chan1);
        HSD_StateSetNumChans(1);

        if (alpha != 0.0f) {
            GXSetScissor(0, 0x6E, 0x280, 0x122);
        }

        lb_80012994(image, x10, x11, x0, x4, x8, xC, alpha);
    } else {
        HSD_CObj* cobj = (HSD_CObj*) gobj->hsd_obj;
        u8 x10 = data->x10;
        f32 xC = data->xC;
        f32 x8 = data->x8;
        f32 x4 = data->x4;
        f32 x0 = data->x0;
        HSD_ImageDesc* image = data->x1C;
        u16 width;
        u16 height;

        HSD_CObjSetCurrent(cobj);
        HSD_StateSetZMode(0, 7, 0);
        GXSetCurrentMtx(0);
        HSD_CObjGetViewingMtx(HSD_CObjGetCurrent(), view_mtx2);
        GXLoadPosMtxImm(view_mtx2, 0);
        GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, 0x3C, 0,
                          0x7D);
        HSD_SetupChannel(&lb_803BA1C0.chan0);
        HSD_SetupChannel(&lb_803BA1C0.chan1);
        HSD_StateSetNumChans(1);

        width = image->width;
        height = image->height;
        lb_8001285C(image, &tex_obj);

        color.a = x10;
        GXSetTevColor(GX_TEVREG0, color);
        GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_TEXA, GX_CA_ZERO, GX_CA_A0,
                        GX_CA_ZERO);
        GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 1,
                        GX_TEVPREV);
        lb_8001271C(&tex_obj, x0, x4, (f32) width, (f32) height, x8, xC);
        HSD_StateInvalidate(2);
    }
}

void fn_800138AC(void* ptr)
{
    HSD_Free(ptr);
}

void lb_800138CC(HSD_GObj* gobj, HSD_GObjEvent arg1)
{
    struct lb_800138D8_t* data = HSD_GObjGetUserData(gobj);
    data->x18 = arg1;
}

void lb_800138D8(HSD_GObj* gobj, s8 arg1)
{
    struct lb_800138D8_t* data = HSD_GObjGetUserData(gobj);
    data->x12 = 1;
    data->x11 = arg1;
}

static Vec3 lb_803B72A8 = { 0.0F, 0.0F, 1.0F };
static Vec3 lb_803B72B4 = { 0.0F, 0.0F, 0.0F };

void lb_800138EC(s32 arg0, GObj_RenderFunc render_func, u32 arg2, s8 arg3,
                 f32 x, f32 y, f32 w, f32 h)
{
    HSD_GObj* gobj;
    HSD_CObj* cobj;
    struct lb_800138D8_t* data;
    HSD_RectS16 viewport;
    Scissor scissor;
    Vec3 eye;
    Vec3 interest;
    f32 zero = 0.0F;
    f32 roll;
    f32 far = -480.0F;
    f32 ortho_top = zero;
    f32 ortho_bot = 2.0F;
    f32 ortho_left = zero;
    f32 ortho_right = 640.0F;

    eye = lb_803B72A8;
    roll = zero;
    interest = lb_803B72B4;

    gobj = GObj_Create(14, 15, 0);
    cobj = HSD_CObjAlloc();

    viewport.xmin = 0;
    scissor.left = 0;
    viewport.xmax = 640;
    scissor.right = 640;
    viewport.ymin = 0;
    scissor.top = 0;
    viewport.ymax = 480;
    scissor.bottom = 480;

    HSD_CObjSetProjectionType(cobj, 3);
    HSD_CObjSetViewport(cobj, &viewport);
    HSD_CObjSetScissor(cobj, &scissor);
    HSD_CObjSetEyePosition(cobj, &eye);
    HSD_CObjSetInterest(cobj, &interest);
    HSD_CObjSetRoll(cobj, roll);
    HSD_CObjSetNear(cobj, zero);
    HSD_CObjSetFar(cobj, far);
    HSD_CObjSetOrtho(cobj, ortho_top, ortho_bot, ortho_left, ortho_right);
    HSD_GObjObject_80390A70(gobj, HSD_GObj_804D784B, cobj);

    data = HSD_MemAlloc(sizeof(struct lb_800138D8_t));
    data->x0 = x;
    data->x4 = y;
    data->x8 = w;
    data->xC = h;
    data->x10 = arg3;
    data->x12 = 0;
    data->x1C = arg0;
    data->x18 = 0;
    GObj_InitUserData(gobj, 0, fn_800138AC, data);

    if (render_func == NULL) {
        GObj_SetupGXLinkMax(gobj, (GObj_RenderFunc) fn_80013614, arg2);
    } else {
        GObj_SetupGXLinkMax(gobj, render_func, arg2);
    }
}

HSD_CObj* lb_80013B14(HSD_CameraDescPerspective* desc)
{
    HSD_CObj* cobj = HSD_CObjLoadDesc((HSD_CObjDesc*) desc);
    Scissor scissor;

    if (HSD_CObjGetProjectionType(cobj) == 1 &&
        HSD_CObjGetAspect(cobj) == 1.18F)
    {
        HSD_CObjSetAspect(cobj, 1.2173333F);
    }
    HSD_CObjGetScissor(cobj, &scissor);
    if (scissor.right > 0x280) {
        scissor.right = 0x280;
    }
    if (scissor.bottom > 0x1E0) {
        scissor.bottom = 0x1E0;
    }
    HSD_CObjSetScissor(cobj, &scissor);
    return cobj;
}

bool lb_80013BB0(ColorOverlay* arg)
{
    return true;
}

bool lb_80013BB8(ColorOverlay* arg0)
{
    arg0->x0_timer += arg0->x8_ptr1->unk.timer;
    ++arg0->x8_ptr1;
    return false;
}

bool lb_80013BE4(ColorOverlay* arg0)
{
    arg0->x7C_color_enable = arg0->x7C_flag2 = false;
    ++arg0->x8_ptr1;
    return false;
}

bool lb_80013C18(ColorOverlay* arg0)
{
    arg0->x7C_light_enable = arg0->x8_ptr1->light_rot2.light_enable;
    arg0->x74_light_rot_x = arg0->x8_ptr1->light_rot2.x;
    arg0->x78_light_rot_yz = arg0->x8_ptr1->light_rot2.yz;
    ++arg0->x8_ptr1;
    arg0->x50_light_color.r = arg0->x8_ptr1->light_color.r;
    arg0->x50_light_color.g = arg0->x8_ptr1->light_color.g;
    arg0->x50_light_color.b = arg0->x8_ptr1->light_color.b;
    arg0->x50_light_color.a = arg0->x8_ptr1->light_color.a;
    arg0->x54_light_red = arg0->x50_light_color.r;
    arg0->x58_light_green = arg0->x50_light_color.g;
    arg0->x5C_light_blue = arg0->x50_light_color.b;
    arg0->x60_light_alpha = arg0->x50_light_color.a;
    arg0->x70_lightblend_alpha = 0.0f;
    arg0->x6C_lightblend_blue = 0.0f;
    arg0->x68_lightblend_green = 0.0f;
    arg0->x64_lightblend_red = 0.0f;
    ++arg0->x8_ptr1;
    arg0->x7C_flag2 = true;
    return false;
}

bool lb_80013D68(ColorOverlay* arg0)
{
    ++arg0->x8_ptr1;
    arg0->x50_light_color.r = arg0->x8_ptr1->light_color.r;
    arg0->x50_light_color.g = arg0->x8_ptr1->light_color.g;
    arg0->x50_light_color.b = arg0->x8_ptr1->light_color.b;
    arg0->x50_light_color.a = arg0->x8_ptr1->light_color.a;
    arg0->x54_light_red = arg0->x50_light_color.r;
    arg0->x58_light_green = arg0->x50_light_color.g;
    arg0->x5C_light_blue = arg0->x50_light_color.b;
    arg0->x60_light_alpha = arg0->x50_light_color.a;
    arg0->x70_lightblend_alpha = 0.0f;
    arg0->x6C_lightblend_blue = 0.0f;
    arg0->x68_lightblend_green = 0.0f;
    arg0->x64_lightblend_red = 0.0f;
    ++arg0->x8_ptr1;
    return false;
}

bool lb_80013E3C(ColorOverlay* arg0)
{
    float f = arg0->x8_ptr1++->unk.timer;
    arg0->x64_lightblend_red =
        ((0.5f + arg0->x8_ptr1->light_color.r) - arg0->x50_light_color.r) / f;
    arg0->x68_lightblend_green =
        ((0.5f + arg0->x8_ptr1->light_color.g) - arg0->x50_light_color.g) / f;
    arg0->x6C_lightblend_blue =
        ((0.5f + arg0->x8_ptr1->light_color.b) - arg0->x50_light_color.b) / f;
    arg0->x70_lightblend_alpha =
        ((0.5f + arg0->x8_ptr1->light_color.a) - arg0->x50_light_color.a) / f;
    ++arg0->x8_ptr1;
    return false;
}

bool lb_80013F78(ColorOverlay* arg0)
{
    arg0->x74_light_rot_x = arg0->x8_ptr1->light_rot1.x;
    arg0->x78_light_rot_yz = arg0->x8_ptr1->light_rot1.yz;
    ++arg0->x8_ptr1;
    return false;
}

bool lb_80013FF0(ColorOverlay* arg0)
{
    arg0->x7C_flag2 = false;
    ++arg0->x8_ptr1;
    return false;
}

bool lb_80014014(ColorOverlay* arg0)
{
    arg0->x7C_color_enable = true;
    ++arg0->x8_ptr1;
    arg0->x2C_hex.r = arg0->x8_ptr1->light_color.r;
    arg0->x2C_hex.g = arg0->x8_ptr1->light_color.g;
    arg0->x2C_hex.b = arg0->x8_ptr1->light_color.b;
    arg0->x2C_hex.a = arg0->x8_ptr1->light_color.a;
    arg0->x30_color_red = arg0->x2C_hex.r;
    arg0->x34_color_green = arg0->x2C_hex.g;
    arg0->x38_color_blue = arg0->x2C_hex.b;
    arg0->x3C_color_alpha = arg0->x2C_hex.a;
    arg0->x4C_colorblend_alpha = 0.0f;
    arg0->x48_colorblend_blue = 0.0f;
    arg0->x44_colorblend_green = 0.0f;
    arg0->x40_colorblend_red = 0.0f;
    ++arg0->x8_ptr1;
    return false;
}

bool lb_800140F8(ColorOverlay* arg0)
{
    float f = arg0->x8_ptr1++->unk.timer;
    arg0->x40_colorblend_red =
        ((0.5f + arg0->x8_ptr1->light_color.r) - arg0->x2C_hex.r) / f;
    arg0->x44_colorblend_green =
        ((0.5f + arg0->x8_ptr1->light_color.g) - arg0->x2C_hex.g) / f;
    arg0->x48_colorblend_blue =
        ((0.5f + arg0->x8_ptr1->light_color.b) - arg0->x2C_hex.b) / f;
    arg0->x4C_colorblend_alpha =
        ((0.5f + arg0->x8_ptr1->light_color.a) - arg0->x2C_hex.a) / f;
    ++arg0->x8_ptr1;
    return false;
}

bool lb_80014234(ColorOverlay* arg0)
{
    arg0->x7C_color_enable = false;
    ++arg0->x8_ptr1;
    return false;
}

bool lb_80014258(HSD_GObj* gobj, void* arg1, FtCmd2 cmd)
{
    ColorOverlay* co = arg1;

    if (co->x8_ptr1 != NULL) {
        s32 timer = co->x0_timer;
        if (timer != 0) {
            co->x0_timer = timer - 1;
        }
    }

    while (co->x8_ptr1 != NULL && co->x0_timer == 0) {
        u32 opcode = co->x8_ptr1->unk.unk;
        if (!Command_Execute((CommandInfo*) co, opcode)) {
            if (opcode < 0x15U) {
                u32 idx = opcode - 0xA;
                if (lb_803BA248[idx](co)) {
                    return true;
                }
            } else {
                cmd(gobj, (CommandInfo*) co, (int) opcode);
            }
        }
    }

    if (co->x7C_color_enable) {
        co->x30_color_red += co->x40_colorblend_red;
        co->x34_color_green += co->x44_colorblend_green;
        co->x38_color_blue += co->x48_colorblend_blue;
        co->x3C_color_alpha += co->x4C_colorblend_alpha;
        co->x2C_hex.r = (u8) co->x30_color_red;
        co->x2C_hex.g = (u8) co->x34_color_green;
        co->x2C_hex.b = (u8) co->x38_color_blue;
        co->x2C_hex.a = (u8) co->x3C_color_alpha;
    }
    if (co->x7C_flag2) {
        co->x54_light_red += co->x64_lightblend_red;
        co->x58_light_green += co->x68_lightblend_green;
        co->x5C_light_blue += co->x6C_lightblend_blue;
        co->x60_light_alpha += co->x70_lightblend_alpha;
        co->x50_light_color.r = (u8) co->x54_light_red;
        co->x50_light_color.g = (u8) co->x58_light_green;
        co->x50_light_color.b = (u8) co->x5C_light_blue;
        co->x50_light_color.a = (u8) co->x60_light_alpha;
    }
    {
        s32 fc = co->x4_pri;
        if (fc != 0) {
            co->x4_pri = fc - 1;
            if (co->x4_pri == 0) {
                return true;
            }
        }
    }
    return false;
}

void lb_80014498(ColorOverlay* arg0)
{
    arg0->x8_ptr1 = NULL;
    arg0->x4_pri = 0;
    arg0->x28_colanim.ptr = NULL;
    arg0->x7C_color_enable = arg0->x7C_flag2 = false;
}

bool lb_800144C8(ColorOverlay* arg0, Fighter_804D653C_t* arg1, int arg2,
                 int arg3)
{
    if (arg1[arg0->x28_colanim.i].unk4 <= arg1[arg2].unk4) {
        arg0->x28_colanim.i = arg2;
        arg0->x4_pri = arg3;
        arg0->x8_ptr1 = arg1[arg2].unk;
        arg0->x0_timer = 0;
        arg0->xC_loop = 0;
        arg0->x7C_color_enable = arg0->x7C_flag2 = false;
        return true;
    }
    return false;
}

void lb_80014534(void)
{
    lbArchive_80017040(NULL, "LbRb.dat", &lb_804D63C0, "lbRumbleData", 0);
}

void lb_80014574(u8 arg0, int arg1, int arg2, int arg3)
{
    HSD_PadRumbleAdd(arg0, arg1, arg3 != 0 ? arg3 : -2, lb_804D63C0[arg2].unk4,
                     lb_804D63C0[arg2].unk);
}

void lb_800145C0(u8 slot)
{
    HSD_PadRumbleRemove(slot);
    HSD_PadRumbleOn(slot);
}

void lb_800145F4(void)
{
    int i;
    for (i = 0; i < PAD_MAX_CONTROLLERS; i++) {
        lb_800145C0(i);
    }
}

static inline float inlineC0(Vec3* a, Vec3* b, Vec3* c)
{
    if (ABS(b->z - a->z) < 0.01f) {
        return 1.0f;
    } else {
        return (c->z - a->z) / (b->z - a->z);
    }
}

bool lb_80014638(struct lb_80014638_arg0_t* arg0,
                 struct lb_80014638_arg1_t* arg1)
{
    Vec3 sp30, sp24, sp18;
    PAD_STACK(4);

    sp30 = arg0->x0;
    sp24 = arg0->xC;
    sp18 = arg1->x8;
    sp30.x = sp30.x + arg1->unk_x;
    sp30.y += arg1->unk_x;
    sp30.z += arg1->unk_y;
    if (sp30.z < sp24.z) {
        return false;
    }
    if (sp30.z < sp18.z || sp24.z > sp18.z) {
        return false;
    }
    {
        float z = inlineC0(&sp30, &sp24, &sp18);
        if (z * (sp24.x - sp30.x) + sp30.x > sp18.y) {
            return false;
        }
        if (z * (sp24.y - sp30.y) + sp30.y < sp18.x) {
            return false;
        }
    }
    return true;
}

bool lb_80014770(Vec3* arg0, int arg1)
{
    if ((u32) arg1 == 2U) {
        Vec3* near_pt;
        Vec3* far_pt;
        GXColor* near_clr;
        GXColor* far_clr;

        GXSetColorUpdate(GX_TRUE);
        GXSetAlphaUpdate(GX_FALSE);
        GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA,
                       GX_LO_NOOP);
        GXSetAlphaCompare(GX_GREATER, 0, GX_AOP_AND, GX_GREATER, 0);
        GXSetZMode(GX_TRUE, GX_LEQUAL, GX_FALSE);
        GXSetZCompLoc(GX_FALSE);
        GXSetNumTexGens(0);
        GXSetTevClampMode(GX_TEVSTAGE0, 0);
        GXSetNumTevStages(1);
        GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL,
                      GX_COLOR0A0);
        GXSetTevOp(GX_TEVSTAGE0, GX_PASSCLR);
        GXSetNumChans(1);
        GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_REG, GX_SRC_VTX, 0,
                      GX_DF_NONE, GX_AF_NONE);
        GXSetCullMode(GX_CULL_NONE);
        GXClearVtxDesc();
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
        GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
        GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
        {
            MtxPtr mtx = HSD_CObjGetCurrent()->view_mtx;
            GXLoadPosMtxImm(mtx, 0);
        }
        GXSetCurrentMtx(0);
        GXBegin(GX_TRIANGLESTRIP, GX_VTXFMT0, 5);

        if (arg0[1].z > arg0[0].z) {
            near_pt = &arg0[1];
            far_pt = &arg0[0];
            near_clr = &lb_804D3768;
            far_clr = &lb_804D376C;
        } else {
            near_pt = &arg0[0];
            far_pt = &arg0[1];
            near_clr = &lb_804D376C;
            far_clr = &lb_804D3768;
        }

        GXPosition3f32(near_pt->y, near_pt->z, 0.0f);
        GXColor4u8(near_clr->r, near_clr->g, near_clr->b, near_clr->a);

        GXPosition3f32(near_pt->x, near_pt->z, 0.0f);
        GXColor4u8(near_clr->r, near_clr->g, near_clr->b, near_clr->a);

        GXPosition3f32(far_pt->y, far_pt->z, 0.0f);
        GXColor4u8(far_clr->r, far_clr->g, far_clr->b, far_clr->a);

        GXPosition3f32(near_pt->x, near_pt->z, 0.0f);
        GXColor4u8(near_clr->r, near_clr->g, near_clr->b, near_clr->a);

        GXPosition3f32(far_pt->x, far_pt->z, 0.0f);
        GXColor4u8(far_clr->r, far_clr->g, far_clr->b, far_clr->a);

        GXEnd();
        PAD_STACK(8);
        return true;
    }
    return false;
}

bool lb_800149E0(Mtx arg0, u32 arg1)
{
    PAD_STACK(16);
    if (arg1 == 0) {
        HSD_StateInitDirect(0, 2);
        {
            MtxPtr mtx = HSD_CObjGetCurrent()->view_mtx;
            GXLoadPosMtxImm(mtx, 0);
            GXSetLineWidth(12, GX_TO_ONE);
            GXBegin(GX_LINESTRIP, GX_VTXFMT0, 2);
            {
                float y = arg0[1][0];
                GXPosition3f32(arg0[0][2], y, 0.0f);
                GXColor4u8(yellow.r, yellow.g, yellow.b, yellow.a);

                GXPosition3f32(arg0[0][3], y, 0.0f);
                GXColor4u8(yellow.r, yellow.g, yellow.b, yellow.a);
            }
            GXEnd();
        }
        return true;
    }
    return false;
}
