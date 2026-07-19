#include "generator.h"

#include "particle.h"

#include <math.h>
#include <math_ppc.h>
#include <trigf.h>
#include <sysdolphin/baselib/cobj.h>
#include <sysdolphin/baselib/mtx.h>
#include <sysdolphin/baselib/psappsrt.h>
#include <sysdolphin/baselib/psstructs.h>
#include <sysdolphin/baselib/random.h>

/* 4D78DA */ extern u16 hsd_804D78DA;
/* 4D78E0 */ extern u16 hsd_804D78E0;
/* 4D78E2 */ extern u16 hsd_804D78E2[2];
/* 4D78E8 */ extern u32 hsd_804D78E8;
/* 4D78E8 */ extern u32 hsd_804D78EC;
/* 4D78F0 */ extern HSD_CObj* psCamera;
/* 4D78F4 */ extern u32 hsd_804D78F4;
/* 4D0D58 */ extern int psNumCmdList[65];
/* 4D0E5C */ extern u32* ptclref_804D0E5C[65];

/* 4D78F8 */ static u32 hsd_804D78F8;
/* 4D78FC */ static HSD_Generator* hsd_804D78FC;
/* 4D7900 */ static void (*hsd_804D7900)(HSD_Generator*);

/* 4D0F90 */ struct hsd_804D0F60_t hsd_804D0F90;

static u16 lbl_804D6368 = 0x100;

void hsd_8039D1E4(HSD_Generator* gen, void* userfunc)
{
    gen->userfunc = userfunc;
}

u16 hsd_8039D1EC(void)
{
    lbl_804D6368++;
    if (lbl_804D6368 < 256) {
        lbl_804D6368 = 256;
    }
    return lbl_804D6368;
}

void hsd_8039D214(HSD_Generator* gen)
{
    HSD_JObj* jobj;

    if (!(gen->type & 0x100)) {
        return;
    }

    if ((jobj = gen->jobj) == NULL) {
        return;
    }

    HSD_JObjSetupMatrix(jobj);

    if (gen->type & 0x200) {
        gen->pos.x = gen->jobj->mtx[0][3];
        gen->pos.y = gen->jobj->mtx[1][3];
        gen->pos.z = gen->jobj->mtx[2][3];
    }

    if (gen->type & 0x800) {
        if (gen->appsrt != NULL && gen->appsrt->gp == gen) {
            gen->appsrt->translate.x = gen->jobj->mtx[0][3];
            gen->appsrt->translate.y = gen->jobj->mtx[1][3];
            gen->appsrt->translate.z = gen->jobj->mtx[2][3];
        }
    }

    if (gen->type & 0x1000) {
        if (gen->appsrt != NULL && gen->appsrt->gp == gen) {
            HSD_MtxGetScale(gen->jobj->mtx, &gen->appsrt->scale);
        }
    }
}

void hsd_8039D354(u32 unused)
{
    HSD_ObjAllocInit(&hsd_804D0F90.alloc_data, 0x94, 4);
    hsd_804D78FC = NULL;
    hsd_804D78E0 = 0;
    hsd_804D78DA = 0;
    hsd_804D78F4 = 0;
    psCamera = NULL;
    hsd_804D78E8 = 0;
    hsd_804D78EC = 0;
    hsd_804D78F8 = 0;
    hsd_804D7900 = NULL;
}

HSD_Generator* hsd_8039D3AC(HSD_Generator* gen, HSD_Generator* prev)
{
    if (gen->type & 0x80) {
        hsd_8039D0A0(gen);
    }
    if (gen->numChild != 0) {
        gen->random = 0.0F;
        gen->genLife = 1;
        return gen;
    }
    if (gen->type & 0x100) {
        if (gen->jobj != NULL) {
            if (gen->type & 0x1800) {
                HSD_psAppSRT* srt = gen->appsrt;
                if (srt != NULL) {
                    if (srt->gp == gen) {
                        if (srt->usedCount != 1) {
                            gen->random = 0.0F;
                            gen->genLife = 1;
                            return gen;
                        }
                    }
                }
            }
        }
    }
    if (prev == NULL) {
        hsd_804D78FC = gen->next;
    } else {
        prev->next = gen->next;
    }
    if (gen->appsrt != NULL) {
        psRemoveGeneratorSRT(gen);
    }
    if (gen->jobj != NULL) {
        HSD_JObjUnref(gen->jobj);
        gen->jobj = NULL;
    }
    HSD_ObjFree(&hsd_804D0F90.alloc_data, gen);
    hsd_804D78E0--;
    return prev;
}

void hsd_8039D4DC(HSD_Generator* gen)
{
    HSD_Generator* cur;

    cur = hsd_804D78FC;
    hsd_804D78F8 = 0;
    while (cur != NULL) {
        if (cur == gen) {
            hsd_804D78F8 =
                (u32) hsd_8039D3AC(gen, (HSD_Generator*) hsd_804D78F8);
            if (hsd_804D78F8 != 0) {
                while (((HSD_Generator*) hsd_804D78F8)->next != NULL) {
                    hsd_804D78F8 = (u32) ((HSD_Generator*) hsd_804D78F8)->next;
                }
            } else if (hsd_804D78FC != NULL) {
                hsd_804D78F8 = (u32) hsd_804D78FC;
                while (((HSD_Generator*) hsd_804D78F8)->next != NULL) {
                    hsd_804D78F8 = (u32) ((HSD_Generator*) hsd_804D78F8)->next;
                }
            }
            return;
        }
        hsd_804D78F8 = (u32) cur;
        cur = cur->next;
    }
}

void hsd_8039D580(HSD_JObj* jobj)
{
    HSD_Generator* next;
    HSD_Generator* cur;

    if (jobj != NULL) {
        cur = hsd_804D78FC;
        while (cur != NULL) {
            next = cur->next;
            if (cur->jobj == jobj) {
                hsd_8039D4DC(cur);
            }
            cur = next;
        }
    }
}

void hsd_8039D5DC(HSD_JObj* jobj)
{
    HSD_Generator* next;
    HSD_Generator* gen;

    if (jobj == NULL) {
        return;
    }
    gen = hsd_804D78FC;
    while (gen != NULL) {
        next = gen->next;
        if (gen->jobj == jobj) {
            hsd_8039D4DC(gen);
        }
        gen = next;
    }
    if (jobj->flags & 0x1000) {
        return;
    }
    jobj = jobj == NULL ? NULL : jobj->child;
    while (jobj != NULL) {
        hsd_8039D5DC(jobj);
        jobj = jobj == NULL ? NULL : jobj->next;
    }
}

void hsd_8039D688(HSD_JObj* jobj, f32** unused1, s32 unused2)
{
    HSD_Generator* next;
    HSD_Generator* gen;

    gen = hsd_804D78FC;
    hsd_804D78F8 = 0;
    while (gen != NULL) {
        next = gen->next;
        if (gen->jobj == jobj) {
            if (gen->appsrt != NULL) {
                u16 type = gen->type;
                if (type & 0x100) {
                    gen->type = type | 0x80;
                }
            }
            hsd_804D78F8 =
                (u32) hsd_8039D3AC(gen, (HSD_Generator*) hsd_804D78F8);
        } else {
            hsd_804D78F8 = (u32) gen;
        }
        gen = next;
    }
}

void hsd_8039D71C(HSD_Generator* gen)
{
    HSD_JObj* jobj;
    Mtx mtx;
    Vec3 col;
    f32 col0_x, col0_y, col0_z;
    f32 col1_x, col1_y, col1_z;
    PAD_STACK(12);

    if (!(gen->type & 0x100)) {
        return;
    }

    if ((jobj = gen->jobj) == NULL) {
        return;
    }

    HSD_JObjSetupMatrix(jobj);

    if (gen->type & 0x200) {
        gen->pos.x = gen->jobj->mtx[0][3];
        gen->pos.y = gen->jobj->mtx[1][3];
        gen->pos.z = gen->jobj->mtx[2][3];
    }

    if (gen->type & 0x800) {
        if (gen->appsrt != NULL && gen->appsrt->gp == gen) {
            gen->appsrt->translate.x = gen->jobj->mtx[0][3];
            gen->appsrt->translate.y = gen->jobj->mtx[1][3];
            gen->appsrt->translate.z = gen->jobj->mtx[2][3];
        }
    }

    if (gen->type & 0x1000) {
        if (gen->appsrt != NULL && gen->appsrt->gp == gen) {
            HSD_MtxGetScale(gen->jobj->mtx, &gen->appsrt->scale);
        }
    }

    col.x = jobj->mtx[0][0];
    col.y = jobj->mtx[1][0];
    col.z = jobj->mtx[2][0];
    PSVECNormalize(&col, &col);
    col0_x = col.x;
    col0_y = col.y;
    col0_z = col.z;

    col.x = jobj->mtx[0][1];
    col.y = jobj->mtx[1][1];
    col.z = jobj->mtx[2][1];
    PSVECNormalize(&col, &col);
    col1_x = col.x;
    col1_y = col.y;
    col1_z = col.z;

    col.x = jobj->mtx[0][2];
    col.y = jobj->mtx[1][2];
    col.z = jobj->mtx[2][2];
    PSVECNormalize(&col, &col);

    {
        f32 cx = col.x;
        f32 cy = col.y;
        f32 cz = col.z;
        f32 vx = gen->vel.x;
        f32 vy = gen->vel.y;
        f32 vz = gen->vel.z;
        gen->vel.x = col0_x * vx + col1_x * vy + cx * vz;
        gen->vel.y = col0_y * vx + col1_y * vy + cy * vz;
        gen->vel.z = col0_z * vx + col1_z * vy + cz * vz;
    }

    if ((gen->type & 0xF) == 1) {
        f32 ax = gen->aux.line.x2;
        f32 ay = gen->aux.line.y2;
        f32 az = gen->aux.line.z2;
        gen->aux.line.x2 =
            jobj->mtx[0][0] * ax + jobj->mtx[0][1] * ay + jobj->mtx[0][2] * az;
        gen->aux.line.y2 =
            jobj->mtx[1][0] * ax + jobj->mtx[1][1] * ay + jobj->mtx[1][2] * az;
        gen->aux.line.z2 =
            jobj->mtx[2][0] * ax + jobj->mtx[2][1] * ay + jobj->mtx[2][2] * az;
    }
}

HSD_Generator* hsd_8039D9C8(void)
{
    HSD_Generator* gen;
    PAD_STACK(8);

    gen = HSD_ObjAlloc(&hsd_804D0F90.alloc_data);
    if (gen != NULL) {
        memset(gen, 0, 0x94);
    }
    if (gen == NULL) {
        return NULL;
    }

    hsd_804D78E0++;
    if (hsd_804D78E0 > hsd_804D78DA) {
        hsd_804D78DA = hsd_804D78E0;
    }

    if ((HSD_Generator*) hsd_804D78F8 == NULL ||
        ((HSD_Generator*) hsd_804D78F8)->next == NULL)
    {
        if (hsd_804D78FC == NULL) {
            gen->next = NULL;
            hsd_804D78FC = gen;
        } else {
            gen->next = hsd_804D78FC->next;
            hsd_804D78FC->next = gen;
        }
    } else {
        gen->next = ((HSD_Generator*) hsd_804D78F8)->next->next;
        ((HSD_Generator*) hsd_804D78F8)->next->next = gen;
    }

    lbl_804D6368++;
    if (lbl_804D6368 < 0x100) {
        lbl_804D6368 = 0x100;
    }
    gen->idnum = lbl_804D6368;
    gen->appsrt = NULL;
    gen->userfunc = NULL;
    return gen;
}

// @TODO: Currently 97.23% match - register allocation, shape/velocity
// switch case logic, Newton-Raphson sqrt inlining, trig matrix layout
f32 hsd_8039DAD4(HSD_Generator* gen)
{
    Mtx rot_mtx;
    Vec3 vel_out;
    Vec3 tmpvec;
    Vec3 emit_pos;
    Vec3 vel_copy;
    Mtx jobj_mtx;
    Vec3 look_dir;
    Vec3 cam_up;
    Vec3 cross1;
    Vec3 vel_norm;
    Mtx trig_mtx;
    f64 eps;
    f32 vel_mag_sq;
    f32 angle1;
    f32 sin_az;
    f32 cos_az;
    f32 sin_el;
    f32 angle_step;
    f32 cur_angle;
    f32 radius;
    f32 cone_angle;
    f32 elevation;
    f32 tmp;
    f32 angle3;
    PAD_STACK(8);

    angle1 = angle3 = 0.0F;
    if (gen->count < 1.0F) {
        return gen->count;
    }

    vel_mag_sq = angle3;

    /* Copy velocity */
    vel_copy.x = gen->vel.x;
    vel_copy.y = gen->vel.y;
    vel_copy.z = gen->vel.z;

    /* Compute velocity magnitude */
    vel_mag_sq = vel_copy.z * vel_copy.z;
    vel_mag_sq += vel_copy.x * vel_copy.x + vel_copy.y * vel_copy.y;
    if (vel_mag_sq > 0.0F) {
        f64 e = __frsqrte(vel_mag_sq);
        e = 0.5 * e * -(vel_mag_sq * (e * e) - 3.0);
        e = 0.5 * e * -(vel_mag_sq * (e * e) - 3.0);
        e = 0.5 * e * -(vel_mag_sq * (e * e) - 3.0);
        tmp = (f32) (vel_mag_sq * e);
        vel_mag_sq = tmp;
    }

    /* Initialize rotation matrix */
    PSMTXIdentity(rot_mtx);

    /* JObj-based rotation: type & 0x100 and jobj!=NULL and type & 0x400
       and !(kind & 0x3C000) */
    if ((gen->type & 0x100) && gen->jobj != NULL && (gen->type & 0x400) &&
        !(gen->kind & 0x30000))
    {
        PSMTXCopy((void*) ((u8*) gen->jobj + 0x44), jobj_mtx);

        /* Extract and normalize each column of the 3x3 rotation */
        tmpvec.x = jobj_mtx[0][0];
        tmpvec.y = jobj_mtx[1][0];
        tmpvec.z = jobj_mtx[2][0];
        PSVECNormalize(&tmpvec, &tmpvec);
        rot_mtx[0][0] = tmpvec.x;
        rot_mtx[1][0] = tmpvec.y;
        rot_mtx[2][0] = tmpvec.z;

        tmpvec.x = jobj_mtx[0][1];
        tmpvec.y = jobj_mtx[1][1];
        tmpvec.z = jobj_mtx[2][1];
        PSVECNormalize(&tmpvec, &tmpvec);
        rot_mtx[0][1] = tmpvec.x;
        rot_mtx[1][1] = tmpvec.y;
        rot_mtx[2][1] = tmpvec.z;

        tmpvec.x = jobj_mtx[0][2];
        tmpvec.y = jobj_mtx[1][2];
        tmpvec.z = jobj_mtx[2][2];
        PSVECNormalize(&tmpvec, &tmpvec);
        rot_mtx[0][2] = tmpvec.x;
        rot_mtx[1][2] = tmpvec.y;
        rot_mtx[2][2] = tmpvec.z;

        rot_mtx[0][3] = 0.0F;
        rot_mtx[1][3] = 0.0F;
        rot_mtx[2][3] = 0.0F;
    }

    /* Billboard orientation: kind & 0x10000 */
    if (gen->kind & 0x10000) {
        HSD_ASSERT(677, psCamera);
        {
            HSD_CObj* cobj = psCamera;
            void* view = *(void**) ((u8*) cobj + 0x24);
            look_dir.x = *(f32*) ((u8*) view + 0x0C) - gen->pos.x;
            view = *(void**) ((u8*) cobj + 0x24);
            look_dir.y = *(f32*) ((u8*) view + 0x10) - gen->pos.y;
            view = *(void**) ((u8*) cobj + 0x24);
            look_dir.z = *(f32*) ((u8*) view + 0x14) - gen->pos.z;
        }
        PSVECNormalize(&look_dir, &look_dir);
        HSD_CObjGetUpVector(psCamera, &cam_up);
        PSVECNormalize(&cam_up, &cam_up);
        PSVECCrossProduct(&cam_up, &look_dir, &cross1);
        PSVECCrossProduct(&look_dir, &cross1, &cam_up);

        rot_mtx[0][0] = cross1.x;
        rot_mtx[1][0] = cross1.y;
        rot_mtx[2][0] = cross1.z;
        rot_mtx[0][1] = cam_up.x;
        rot_mtx[1][1] = cam_up.y;
        rot_mtx[2][1] = cam_up.z;
        rot_mtx[0][2] = look_dir.x;
        rot_mtx[1][2] = look_dir.y;
        rot_mtx[2][2] = look_dir.z;
    }

    /* Velocity-based rotation */
    if ((gen->type & 0xF) != 1 && vel_mag_sq > 0.0F) {
        vel_norm.x = gen->vel.x;
        vel_norm.y = gen->vel.y;
        vel_norm.z = gen->vel.z;
        PSVECNormalize(&vel_norm, &vel_norm);

        tmp = vel_norm.z;
        *(s32*) &tmp &= 0x7FFFFFFF;
        if (tmp < 1.1754944e-38F) {
            if (vel_norm.y >= 0.0F) {
                sin_az = 1.5707964F;
            } else {
                sin_az = -1.5707964F;
            }
        } else {
            sin_az = atan2f(vel_norm.y, vel_norm.z);
        }
        cos_az = sinf(sin_az);
        sin_az = cosf(sin_az);

        {
            f32 projected_z = vel_norm.z * sin_az;
            projected_z += vel_norm.y * cos_az;
            tmp = projected_z;
            *(s32*) &tmp &= 0x7FFFFFFF;
            if (tmp < 1.1754944e-38F) {
                if (vel_norm.x >= 0.0F) {
                    elevation = 1.5707964F;
                } else {
                    elevation = -1.5707964F;
                }
            } else {
                elevation = atan2f(vel_norm.x, projected_z);
            }
        }
        sin_el = sinf(elevation);
        {
            f32 cos_el = cosf(elevation);
            f32 neg_cos_az = -cos_az;
            f32 neg_sin_az_s = -sin_az;

            trig_mtx[0][0] = cos_el;
            trig_mtx[0][1] = 0.0F;
            trig_mtx[0][2] = sin_el;
            trig_mtx[0][3] = 0.0F;
            trig_mtx[1][0] = neg_cos_az * sin_el;
            trig_mtx[1][1] = sin_az;
            trig_mtx[1][2] = cos_az * cos_el;
            trig_mtx[1][3] = 0.0F;
            trig_mtx[2][0] = neg_sin_az_s * sin_el;
            trig_mtx[2][1] = neg_cos_az;
            trig_mtx[2][2] = sin_az * cos_el;
            trig_mtx[2][3] = 0.0F;
        }
        PSMTXConcat(rot_mtx, trig_mtx, rot_mtx);
    }

    /* Type 2: extract Euler angles from rotation matrix */
    if ((gen->type & 0xF) == 2) {
        tmp = rot_mtx[2][2];
        *(s32*) &tmp &= 0x7FFFFFFF;
        if (tmp < 1.1754944e-38F) {
            if (rot_mtx[1][2] >= 0.0F) {
                angle1 = 1.5707964F;
            } else {
                angle1 = -1.5707964F;
            }
        } else {
            angle1 = atan2f(rot_mtx[1][2], rot_mtx[2][2]);
        }
        {
            f32 comb = rot_mtx[2][2] * cosf(angle1);
            comb += rot_mtx[1][2] * sinf(angle1);
            tmp = comb;
            *(s32*) &tmp &= 0x7FFFFFFF;
            if (tmp < 1.1754944e-38F) {
                if (rot_mtx[0][2] >= 0.0F) {
                    angle3 = 1.5707964F;
                } else {
                    angle3 = -1.5707964F;
                }
            } else {
                angle3 = atan2f(rot_mtx[0][2], comb);
            }
        }
    }

    /* Angle step computation (pre-loop) */
    if (gen->angle < 0.0F) {
        switch (gen->type & 0xF) {
        case 0:
        case 3:
        case 4: {
            f32 min_a = gen->aux.disc.minAngle;
            f32 rnd = HSD_Randf();
            f32 range = gen->aux.disc.maxAngle - min_a;
            angle_step = range / (f32) (s32) gen->count;
            cur_angle = angle_step * rnd + min_a;
            break;
        }
        case 6:
        case 7: {
            f32 min_a = gen->aux.cone.minAngle;
            f32 rnd = HSD_Randf();
            f32 range = gen->aux.cone.maxAngle - min_a;
            angle_step = range / (f32) (s32) gen->count;
            cur_angle = angle_step * rnd + min_a;
            break;
        }
        default: {
            f32 rnd = HSD_Randf();
            cur_angle = (f32) (2.0 * (M_PI * (f64) rnd));
            angle_step = (f32) ((2.0 * M_PI) / (f64) (s32) gen->count);
            break;
        }
        }
    }

    /* Main particle emission loop */
    eps = 0.001F;
    while (gen->count >= 1.0F) {
        switch (gen->type & 0xF) {
        case 0: /* point, disc, cone, sphere, etc. */
        case 3:
        case 4:
        case 6:
        case 7: {
            /* Compute radius */
            if (gen->radius < 0.0F) {
                sin_az = -gen->radius;
                radius = 0.0F;
            } else {
                radius = HSD_Randf();
                if ((gen->type & 0xF) == 3 || (gen->type & 0xF) == 4) {
                    radius = sqrtf(radius);
                }
                sin_az = radius * gen->radius;
            }

            /* Compute emission angle per shape */
            switch (gen->type & 0xF) {
            case 6:
                if (gen->angle < 0.0F) {
                    emit_pos.z = sin_az;
                    cur_angle += angle_step;
                    tmp = sin_az;
                    *(s32*) &tmp &= 0x7FFFFFFF;
                    if (tmp < 1.1754944e-38F) {
                        if (gen->aux.cone.height >= 0.0F) {
                            cone_angle = -gen->angle;
                        } else {
                            cone_angle = (f32) (M_PI - gen->angle);
                        }
                    } else {
                        cone_angle = (f32) (M_PI - atan2f(gen->aux.cone.height,
                                                          sin_az)) -
                                     gen->angle;
                    }
                } else {
                    cur_angle = gen->aux.cone.minAngle;
                    {
                        f32 rnd = HSD_Randf();
                        f32 range = gen->aux.cone.maxAngle - cur_angle;
                        cone_angle = radius * gen->angle;
                        cur_angle = range * rnd + cur_angle;
                    }
                    emit_pos.z = sin_az;
                    tmp = sin_az;
                    *(s32*) &tmp &= 0x7FFFFFFF;
                    if (tmp < 1.1754944e-38F) {
                        if (gen->aux.cone.height >= 0.0F) {
                            cone_angle = gen->angle;
                        } else {
                            cone_angle = (f32) (M_PI + gen->angle);
                        }
                    } else {
                        cone_angle = gen->angle +
                                     (f32) (M_PI - atan2f(gen->aux.cone.height,
                                                          sin_az));
                    }
                }
                break;
            case 7:
                if (gen->angle < 0.0F) {
                    cone_angle = (f32) (M_PI - gen->angle);
                    cur_angle += angle_step;
                } else {
                    cur_angle = gen->aux.disc.minAngle;
                    {
                        f32 rnd = HSD_Randf();
                        f32 range = gen->aux.disc.maxAngle - cur_angle;
                        cone_angle = (f32) (M_PI + gen->angle);
                        cur_angle = range * rnd + cur_angle;
                    }
                }
                break;
            default:
                if (gen->angle < 0.0F) {
                    cone_angle = -gen->angle;
                    cur_angle += angle_step;
                    cone_angle = radius * cone_angle;
                } else {
                    cur_angle = gen->aux.disc.minAngle;
                    {
                        f32 rnd = HSD_Randf();
                        f32 range = gen->aux.disc.maxAngle - cur_angle;
                        cone_angle = radius * gen->angle;
                        cur_angle = range * rnd + cur_angle;
                    }
                }
                break;
            }

            /* Compute emission position and velocity from angle */
            emit_pos.x = sin_az * cosf(cur_angle);
            emit_pos.y = sin_az * sinf(cur_angle);

            /* Shape 6,7: z from random, scale by height */
            if ((gen->type & 0xF) == 6 || (gen->type & 0xF) == 7) {
                emit_pos.z = HSD_Randf();
                if ((gen->type & 0xF) == 6) {
                    emit_pos.x *= (1.0F - emit_pos.z);
                    emit_pos.y *= (1.0F - emit_pos.z);
                }
                emit_pos.z *= gen->aux.cone.height;
            } else {
                emit_pos.z = 0.0F;
            }

            /* Compute velocity direction from cone angle */
            {
                f32 sin_ca = vel_mag_sq * sinf(cone_angle);
                vel_out.x = sin_ca * cosf(cur_angle);
                vel_out.y = sin_ca * sinf(cur_angle);
                vel_out.z = vel_mag_sq * cosf(cone_angle);
            }

            /* Shape 3: scale velocity by radius factor */
            if ((gen->type & 0xF) == 3) {
                vel_out.x *= radius;
                vel_out.y *= radius;
                vel_out.z *= radius;
            }

            /* Apply rotation matrix to emission position */
            PSMTXMultVec(rot_mtx, &emit_pos, &emit_pos);
            emit_pos.x += gen->pos.x;
            emit_pos.y += gen->pos.y;
            emit_pos.z += gen->pos.z;

            /* Apply rotation matrix to velocity */
            PSMTXMultVec(rot_mtx, &vel_out, &vel_out);

            /* Spawn particle */
            hsd_80398F0C(gen->linkNo, gen->bank, gen->kind, gen->texGroup,
                         (s32) gen->cmdList, gen->life, 0, (s32) gen,
                         emit_pos.x, emit_pos.y, emit_pos.z, vel_out.x,
                         vel_out.y, vel_out.z, gen->size, gen->grav,
                         gen->fric);
            break;
        }

        case 1: /* line */
        {
            f32 rnd = HSD_Randf();
            emit_pos.x = rnd * gen->aux.line.x2;
            emit_pos.y = rnd * gen->aux.line.y2;
            emit_pos.z = rnd * gen->aux.line.z2;

            PSMTXMultVec(rot_mtx, &emit_pos, &emit_pos);
            emit_pos.x += gen->pos.x;
            emit_pos.y += gen->pos.y;
            emit_pos.z += gen->pos.z;

            PSMTXMultVec(rot_mtx, &vel_copy, &vel_out);

            hsd_80398F0C(gen->linkNo, gen->bank, gen->kind, gen->texGroup,
                         (s32) gen->cmdList, gen->life, 0, (s32) gen,
                         emit_pos.x, emit_pos.y, emit_pos.z, vel_out.x,
                         vel_out.y, vel_out.z, gen->size, gen->grav,
                         gen->fric);
            break;
        }

        case 2: /* tornado */
        {
            if (gen->radius < 0.0F) {
                sin_az = 0.0F;
            } else {
                sin_az = HSD_Randf();
            }
            if (gen->angle < 0.0F) {
                cur_angle += angle_step;
            } else {
                f32 rnd = HSD_Randf();
                cur_angle = (f32) (2.0 * (M_PI * (f64) rnd));
            }
            gen->aux.line.x2 = vel_mag_sq;
            hsd_80398F0C(gen->linkNo, gen->bank, gen->kind | 4, gen->texGroup,
                         (s32) gen->cmdList, gen->life, 0, (s32) gen, 0.0F,
                         0.0F, 0.0F, cur_angle, sin_az, 0.0F, gen->size,
                         angle1, angle3);
            break;
        }

        case 5: /* rect */
        {
            Vec3 vel_temp;
            emit_pos.x = HSD_Randf();
            emit_pos.y = HSD_Randf();
            emit_pos.z = HSD_Randf();

            switch (gen->aux.rect.flag) {
            case 0: /* default: no modification */
                break;
            case 1: /* +x */
                emit_pos.x = emit_pos.x > 0.5F ? 1.0F : 0.0F;
                break;
            case 2: /* +y */
                emit_pos.y = emit_pos.y > 0.5F ? 1.0F : 0.0F;
                break;
            case 3: /* xy split */
            {
                f32 rnd = HSD_Randf();
                f32 a2 = gen->aux.rect.x;
                f32 b2 = gen->aux.rect.y;
                if (rnd > a2 / (a2 + b2)) {
                    emit_pos.y = emit_pos.y > 0.5F ? 1.0F : 0.0F;
                } else {
                    emit_pos.x = emit_pos.x > 0.5F ? 1.0F : 0.0F;
                }
                break;
            }
            case 4: /* +z */
                emit_pos.z = emit_pos.z > 0.5F ? 1.0F : 0.0F;
                break;
            case 5: /* xz split */
            {
                f32 rnd = HSD_Randf();
                f32 a2 = gen->aux.rect.x;
                f32 b2 = gen->aux.rect.z;
                if (rnd > a2 / (a2 + b2)) {
                    emit_pos.z = emit_pos.z > 0.5F ? 1.0F : 0.0F;
                } else {
                    emit_pos.x = emit_pos.x > 0.5F ? 1.0F : 0.0F;
                }
                break;
            }
            case 6: /* yz split */
            {
                f32 rnd = HSD_Randf();
                f32 a2 = gen->aux.rect.y;
                f32 b2 = gen->aux.rect.z;
                if (rnd > a2 / (a2 + b2)) {
                    emit_pos.z = emit_pos.z > 0.5F ? 1.0F : 0.0F;
                } else {
                    emit_pos.y = emit_pos.y > 0.5F ? 1.0F : 0.0F;
                }
                break;
            }
            case 7: /* 3-way split */
            {
                f32 rnd = HSD_Randf();
                f32 a2 = gen->aux.rect.z;
                f32 b2 = gen->aux.rect.y;
                f32 c2 = gen->aux.rect.x;
                f32 ab = b2 * a2;
                f32 ca = c2 * b2;
                f32 total = c2 * (b2 + a2) + ab;
                f32 r0 = 1.0F / total;
                f32 t1 = r0 * ca;
                if (rnd < t1) {
                    emit_pos.z = emit_pos.z > 0.5F ? 1.0F : 0.0F;
                } else {
                    f32 t2 = 1.0F - r0 * c2 * a2;
                    if (rnd > t2) {
                        emit_pos.y = emit_pos.y > 0.5F ? 1.0F : 0.0F;
                    } else {
                        emit_pos.x = emit_pos.x > 0.5F ? 1.0F : 0.0F;
                    }
                }
                break;
            }
            default:
                break;
            }

            /* Common rect post-processing */
            emit_pos.x -= 0.5F;
            emit_pos.y -= 0.5F;
            emit_pos.z -= 0.5F;

            /* Multiply by rect's 3x3 matrix */
            vel_temp.x = gen->aux.rect.yx * emit_pos.y +
                         gen->aux.rect.xx * emit_pos.x +
                         gen->aux.rect.zx * emit_pos.z;
            vel_temp.y = gen->aux.rect.yy * emit_pos.y +
                         gen->aux.rect.xy * emit_pos.x +
                         gen->aux.rect.zy * emit_pos.z;
            vel_temp.z = gen->aux.rect.yz * emit_pos.y +
                         gen->aux.rect.xz * emit_pos.x +
                         gen->aux.rect.zz * emit_pos.z;

            PSMTXMultVec(rot_mtx, &vel_temp, &emit_pos);
            emit_pos.x += gen->pos.x;
            emit_pos.y += gen->pos.y;
            emit_pos.z += gen->pos.z;

            /* Compute velocity from rect axes */
            {
                f32 mag = gen->aux.rect.zx * gen->aux.rect.zx +
                          gen->aux.rect.zy * gen->aux.rect.zy +
                          gen->aux.rect.zz * gen->aux.rect.zz;
                mag = sqrtf(mag);
                {
                    f32 scale = vel_mag_sq / mag;
                    vel_out.x = gen->aux.rect.zx * scale;
                    vel_out.y = gen->aux.rect.zy * scale;
                    vel_out.z = gen->aux.rect.zz * scale;
                }
            }

            PSMTXMultVec(rot_mtx, &vel_out, &vel_out);

            hsd_80398F0C(gen->linkNo, gen->bank, gen->kind, gen->texGroup,
                         (s32) gen->cmdList, gen->life, 0, (s32) gen,
                         emit_pos.x, emit_pos.y, emit_pos.z, vel_out.x,
                         vel_out.y, vel_out.z, gen->size, gen->grav,
                         gen->fric);
            break;
        }

        case 8: /* sphere emission */
        {
            f32 r0 = gen->aux.cone.height;
            if (r0 == 0.0F || __fabs(r0 - M_PI) < eps) {
                f32 rnd = sqrtf(HSD_Randf());
                radius = (f32) (M_PI * rnd);
                {
                    f32 rnd2 = HSD_Randf();
                    if (rnd2 < 0.5F) {
                        radius = (f32) (M_PI - radius);
                    }
                }
            } else {
                f32 rnd = sqrtf(HSD_Randf());
                radius = gen->aux.cone.height * rnd;
            }
            {
                f32 rnd = HSD_Randf();
                f32 az_angle;
                f32 r2 = gen->radius;
                az_angle = (f32) (2.0 * (M_PI * (f64) rnd));
                cone_angle = az_angle;

                if (r2 < 0.0F) {
                    sin_az = -r2;
                } else {
                    rnd = sqrtf(HSD_Randf());
                    sin_az = r2 * rnd;
                }
            }
            {
                f32 cos_r;
                f32 sin_r;
                cos_r = cosf(cone_angle);
                cos_az = sinf(radius);
                vel_out.x = cos_az * cos_r;
                sin_el = sinf(cone_angle);
                sin_r = sinf(radius);
                vel_out.y = sin_el * sin_r;
                vel_out.z = cosf(radius);
            }

            PSMTXMultVec(rot_mtx, &vel_out, &emit_pos);

            /* Scale position by aux.rect.x */
            vel_out.x = emit_pos.x * gen->aux.rect.x;
            vel_out.y = emit_pos.y * gen->aux.rect.x;
            vel_out.z = emit_pos.z * gen->aux.rect.x;

            /* Scale velocity if needed */
            if (gen->radius >= 0.0F && gen->aux.rect.x < 0.0F) {
                f32 scale = sin_az / gen->radius;
                vel_out.x *= scale;
                vel_out.y *= scale;
                vel_out.z *= scale;
            }

            emit_pos.x = sin_az * emit_pos.x + gen->pos.x;
            emit_pos.y = sin_az * emit_pos.y + gen->pos.y;
            emit_pos.z = sin_az * emit_pos.z + gen->pos.z;

            hsd_80398F0C(gen->linkNo, gen->bank, gen->kind, gen->texGroup,
                         (s32) gen->cmdList, gen->life, 0, (s32) gen,
                         emit_pos.x, emit_pos.y, emit_pos.z, vel_out.x,
                         vel_out.y, vel_out.z, gen->size, gen->grav,
                         gen->fric);
            break;
        }

        default: /* shape > 8 */
            if ((void (*)(HSD_Generator*, Mtx)) hsd_804D78E8 != NULL) {
                ((void (*)(HSD_Generator*, Mtx)) hsd_804D78E8)(gen, rot_mtx);
            }
            break;
        }

        gen->count -= 1.0F;
    }

    return gen->count;
}

void hsd_8039EE24(u32 mask)
{
    HSD_Generator* gp;
    HSD_Generator* gen;

    while (hsd_804D78F4 != 0) {
        gp = (HSD_Generator*) ((HSD_SList*) hsd_804D78F4)->data;
        hsd_8039D71C(gp);
        hsd_804D78F4 = (u32) HSD_SListRemove((HSD_SList*) hsd_804D78F4);
        if (gp->jobj != NULL) {
            HSD_JObjUnref(gp->jobj);
            gp->jobj = NULL;
        }
    }

    gen = hsd_804D78FC;
    hsd_804D78F8 = 0;

    while (gen != NULL) {
        if (mask & (1 << (gen->linkNo + 16))) {
            hsd_804D78F8 = (u32) gen;
            gen = gen->next;
            continue;
        }
        if (gen->kind & 0x800) {
            hsd_804D78F8 = (u32) gen;
            gen = gen->next;
            continue;
        }
        hsd_8039D214(gen);
        if (gen->random < 0.0F) {
            gen->count -= gen->random;
        } else {
            gen->count += gen->random * HSD_Randf();
        }
        if (gen->count >= 1.0F) {
            gen->count = hsd_8039DAD4(gen);
        }
        if (gen->genLife != 0) {
            u16 life = gen->genLife - 1;
            gen->genLife = life;
            if (life == 0) {
                hsd_804D78F8 =
                    (u32) hsd_8039D3AC(gen, (HSD_Generator*) hsd_804D78F8);
                if (hsd_804D78F8 != 0) {
                    gen = ((HSD_Generator*) hsd_804D78F8)->next;
                } else {
                    gen = hsd_804D78FC;
                }
                continue;
            }
        }
        hsd_804D78F8 = (u32) gen;
        gen = gen->next;
    }
}

HSD_Generator* hsd_8039EFAC(s32 linkNo, s32 bank, s32 gfx_id, HSD_JObj* jobj)
{
    HSD_Generator* gen;

    gen = hsd_8039F05C(linkNo, bank, gfx_id);
    if (gen == NULL) {
        return NULL;
    }
    if (gen != NULL) {
        gen->jobj = jobj;
        if (jobj != NULL) {
            ref_INC(jobj);
        }
    }
    gen->type |= (gen->kind & 0x20000) ? 0x500 : 0x700;
    return gen;
}

// @TODO: Currently 96.66% match - command-array register swap and stack
// frame differences remain
HSD_Generator* hsd_8039F05C(s32 linkNo, s32 bank, s32 idx)
{
    HSD_PSCmdList*** cmdListArr;
    HSD_PSTexGroup* tg;
    HSD_Generator* gen;
    s32 ofs;
    f32 mag;
    f32 f0, f1, f3;
    u32 shape;

    if (bank >= 0x41) {
        return NULL;
    }
    if (linkNo >= 8) {
        return NULL;
    }
    if (idx >= psNumCmdList[bank]) {
        return NULL;
    }

    cmdListArr = (HSD_PSCmdList***) &ptclref_804D0E5C[bank];
    ofs = idx * 4;
    if ((*cmdListArr)[idx] == NULL) {
        return NULL;
    }

    gen = hsd_8039D9C8();
    if (gen != NULL) {
        gen->type = (*cmdListArr)[idx]->type;
        gen->bank = bank;
        gen->linkNo = linkNo;
        gen->kind = (*cmdListArr)[idx]->kind;
        gen->texGroup = (*cmdListArr)[idx]->texGroup;
        gen->life = (*cmdListArr)[idx]->life;
        gen->genLife = (*cmdListArr)[idx]->genLife;
        gen->pos.z = 0.0F;
        gen->pos.y = 0.0F;
        gen->pos.x = 0.0F;
        gen->vel.x = (*cmdListArr)[idx]->vx;
        gen->vel.y = (*cmdListArr)[idx]->vy;
        gen->vel.z = (*cmdListArr)[idx]->vz;
        gen->grav = (*cmdListArr)[idx]->grav;
        gen->fric = (*cmdListArr)[idx]->fric;
        gen->size = (*cmdListArr)[idx]->size;
        gen->cmdList = (*cmdListArr)[idx]->cmdList;
        gen->radius = (*cmdListArr)[idx]->radius;
        gen->angle = (*cmdListArr)[idx]->angle;
        gen->random = (*cmdListArr)[idx]->random;

        if (gen->kind & 0x100) {
            f1 = gen->random;
            if (f1 < 0.0F) {
                f3 = 1.0F;
                if ((1.0F + f1) > 1.1920929e-7F) {
                } else {
                    f3 = 0.0F;
                }
                gen->count = f3;
            } else {
                gen->count = 0.9999999F;
            }
        } else if (gen->random < 0.0F) {
            gen->count = 0.0F;
        } else {
            gen->count = HSD_Randf();
        }

        tg = ((HSD_PSTexGroup***) ((uintptr_t) cmdListArr - bank * 4 -
                                   0x30C))[bank][gen->texGroup];
        if (tg != NULL && tg->palflag != 0) {
            gen->kind |= 0x10;
        }

        gen->jobj = NULL;
        gen->numChild = 0;

        shape = gen->type & 0xF;
        switch (shape) {
        case 0:
        case 3:
        case 4: {
            HSD_PSCmdList* c = (*cmdListArr)[idx];
            f32 p1 = c->param1;
            if (p1 == 0.0F && c->param2 == 0.0F) {
                gen->aux.disc.minAngle = 0.0F;
                gen->aux.disc.maxAngle = 6.2831855F;
            } else {
                gen->aux.disc.minAngle = p1;
                gen->aux.disc.maxAngle = (*cmdListArr)[idx]->param2;
            }
            break;
        }
        case 1:
            gen->aux.line.x2 = (*cmdListArr)[idx]->param1;
            gen->aux.line.y2 = (*cmdListArr)[idx]->param2;
            gen->aux.line.z2 = (*cmdListArr)[idx]->param3;
            break;
        case 6:
        case 7: {
            HSD_PSCmdList* c = (*cmdListArr)[idx];
            f32 p1 = c->param1;
            if (p1 == 0.0F && c->param2 == 0.0F) {
                gen->aux.cone.minAngle = 0.0F;
                gen->aux.cone.maxAngle = 6.2831855F;
            } else {
                gen->aux.cone.minAngle = p1;
                gen->aux.cone.maxAngle = (*cmdListArr)[idx]->param2;
            }
            gen->aux.cone.height = (*cmdListArr)[idx]->param3;
            break;
        }
        case 5: {
            f0 = (*cmdListArr)[idx]->param1;
            gen->aux.rect.x = f0;
            gen->aux.rect.xx = f0;
            f0 = (*cmdListArr)[idx]->param2;
            gen->aux.rect.y = f0;
            gen->aux.rect.zx = f0;
            f0 = (*cmdListArr)[idx]->param3;
            gen->aux.rect.z = f0;
            gen->aux.rect.zy = f0;
            gen->aux.rect.zz = 0.0F;
            gen->aux.rect.yz = 0.0F;
            gen->aux.rect.yy = 0.0F;
            gen->aux.rect.xy = 0.0F;
            gen->aux.rect.xz = 0.0F;
            gen->aux.rect.yx = 0.0F;
            gen->aux.rect.flag = 0;
            if ((*cmdListArr)[idx]->param1 < 0.0F) {
                gen->aux.rect.flag |= 1;
            }
            if ((*cmdListArr)[idx]->param2 < 0.0F) {
                gen->aux.rect.flag |= 2;
            }
            if ((*cmdListArr)[idx]->param3 < 0.0F) {
                gen->aux.rect.flag |= 4;
            }
            break;
        }
        case 8: {
            f32 vx = gen->vel.x;
            f32 vy = gen->vel.y;
            f32 vz = gen->vel.z;
            f32 vx_sq = vx * vx;
            f32 vy_sq = vy * vy;
            f32 vz_sq = vz * vz;
            mag = vx_sq + vy_sq;
            mag += vz_sq;
            gen->aux.sphere.speed = sqrtf(mag);

            f0 = gen->vel.x;
            f1 = gen->vel.z;
            vx_sq = f0 * f0;
            vz_sq = f1 * f1;
            mag = vx_sq + vz_sq;
            mag = sqrtf(mag);

            if (mag < 1.1754944e-38F) {
                if (gen->vel.y >= 0.0F) {
                    gen->aux.sphere.latMid = 1.5707964F;
                } else {
                    gen->aux.sphere.latMid = -1.5707964F;
                }
            } else {
                gen->aux.sphere.latMid = atan2f(gen->vel.y, mag);
            }

            if (fabsf_bitwise(gen->vel.x) < 1.1754944e-38F) {
                if (gen->vel.z >= 0.0F) {
                    gen->aux.sphere.lonMid = 1.5707964F;
                } else {
                    gen->aux.sphere.lonMid = -1.5707964F;
                }
            } else {
                gen->aux.sphere.lonMid = atan2f(gen->vel.z, gen->vel.x);
            }
            gen->aux.sphere.latRange = (*cmdListArr)[idx]->param1;
            f1 = gen->aux.sphere.latRange;
            if (f1 < 0.0F) {
                gen->aux.sphere.latRange = -f1;
                gen->aux.sphere.speed = -gen->aux.sphere.speed;
            }
            gen->aux.sphere.lonRange = (*cmdListArr)[idx]->param2;
            break;
        }
        default:
            if ((void (*)(HSD_Generator*)) hsd_804D78EC != NULL) {
                ((void (*)(HSD_Generator*)) hsd_804D78EC)(gen);
            }
            break;
        }

        if (gen->kind & 0x20000) {
            gen->type |= 0x800;
            psAddGeneratorAppSRT_begin(gen, 0);
            if (gen->appsrt != NULL) {
                gen->appsrt->xA2 = 1;
                gen->appsrt->gp = gen;
            }
        }

        if (hsd_804D7900 != NULL) {
            hsd_804D7900(gen);
        }
    }
    return gen;
}

HSD_Generator* hsd_8039F6CC(s32 linkNo, s32 bank, s32 gfx_id, HSD_JObj* jobj)
{
    HSD_Generator* gen;

    gen = hsd_8039F05C(linkNo, bank, gfx_id);
    if (gen == NULL) {
        return NULL;
    }
    if (gen != NULL) {
        gen->jobj = jobj;
        if (jobj != NULL) {
            ref_INC(jobj);
        }
    }
    gen->type |= (gen->kind & 0x20000) ? 0x500 : 0x700;
    hsd_804D78F4 =
        (u32) HSD_SListAllocAndAppend((HSD_SList*) hsd_804D78F4, gen);
    return gen;
}
