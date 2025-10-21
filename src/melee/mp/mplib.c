#include "mplib.h"

#include "mpisland.h"

#include "mplib.static.h"

#include "placeholder.h"
#include "platform.h"
#include "stdbool.h"
#include "types.h"

#include "baselib/debug.h"

#include "baselib/forward.h"

#include "baselib/memory.h"
#include "db/db.h"
#include "dolphin/gx/GXGeometry.h"
#include "dolphin/gx/GXStruct.h"
#include "dolphin/gx/GXVert.h"
#include "dolphin/types.h"
#include "ft/ftlib.h"
#include "gr/grdynamicattr.h"
#include "gr/ground.h"
#include "it/inlines.h"
#include "it/it_26B1.h"
#include "it/itCharItems.h"

#include "lb/forward.h"
#include "mp/forward.h"

#include "mp/mpcoll.h"

#include <math.h>
#include <math_ppc.h>
#include <stddef.h>
#include <string.h>
#include <dolphin/mtx.h>
#include <baselib/jobj.h>
#include <sysdolphin/baselib/cobj.h>
#include <sysdolphin/baselib/gobj.h>
#include <sysdolphin/baselib/gobjproc.h>
#include <sysdolphin/baselib/lobj.h>
#include <sysdolphin/baselib/tev.h>
#include <sysdolphin/baselib/texp.h>
#include <melee/cm/camera.h>
#include <melee/cm/types.h>
#include <melee/gr/stage.h>
#include <melee/lb/types.h>

#define LINEID_CHECK(line, line_id)                                           \
    do {                                                                      \
        if ((line_id) == -1 || (line_id) >= mpLib_804D64B4->line_count)       \
            HSD_ASSERTREPORT(line, 0, "%s:%d:not found lineID=%d\n",          \
                             __FILE__, line, line_id);                        \
    } while (0)

static Vec2 mpLib_803BF718[2] = { { -1.0F, -400.0F }, { 1.0F, -400.0F } };
static mpLib_Line mpLib_803BF728 = { 0, 1, -1, -1, -1, -1, 1, 0 };
static CollInfo mpLib_803BF738 = {
    1, 0, 0, 0, 0, -9.0F, -408.0F, 9.0F, -392.0F, 2,
};
static mpCollData mpLib_803BF760 = {
    /*  +0 */ mpLib_803BF718,
    /*  +4 */ 2,
    /*  +8 */ &mpLib_803BF728,
    /*  +C */ 0x00000001,
    /* +10 */ 0,
    /* +12 */ 1,
    /* +14 */ 0,
    /* +16 */ 0,
    /* +18 */ 0,
    /* +1A */ 0,
    /* +1C */ 0,
    /* +1E */ 0,
    /* +20 */ 0,
    /* +22 */ 0,
    /* +24 */ &mpLib_803BF738,
    /* +28 */ 0x00000001,
    /* +2C */ 0x00000000,
};

mpCollData* mpLib_8004D164(void)
{
    return mpLib_804D64B4;
}

CollVtx* mpGetGroundCollVtx(void)
{
    return groundCollVtx;
}

CollLine* mpGetGroundCollLine(void)
{
    return groundCollLine;
}

CollJoint* mpGetGroundCollJoint(void)
{
    return groundCollJoint;
}

void mpPruneEmptyLines(mpCollData* coll_data)
{
    mpLib_Line* line;
    Vec2* verts = coll_data->verts;
    int i;

    if (stage_info.internal_stage_id == PURA) {
        return;
    }

    line = coll_data->lines;
    for (i = 0; i < coll_data->line_count; i++, line++) {
        Vec2* v0 = &verts[line->v0_idx];
        Vec2* v1 = &verts[line->v1_idx];
        mpLib_Line* other;
        int j;

        if (v0->x != v1->x || v0->y != v1->y) {
            continue;
        }

        other = coll_data->lines;
        for (j = 0; j < coll_data->line_count; j++, other++) {
            if (other->prev_id0 == i) {
                other->prev_id0 = line->prev_id0;
            }
            if (other->next_id0 == i) {
                other->next_id0 = line->next_id0;
            }
            if (other->prev_id1 == i) {
                other->prev_id1 = line->prev_id0;
            }
            if (other->next_id1 == i) {
                other->next_id1 = line->next_id0;
            }
        }

        line->is_empty |= LINE_FLAG_EMPTY;
        line->prev_id0 = -1;
        line->next_id0 = -1;
        line->prev_id1 = -1;
        line->next_id1 = -1;
    }
}

void mpLibLoad(mpCollData* coll_data)
{
    float f0;
    float f1;
    float f2;
    float f31;
    float* temp_r30;
    float* temp_r29;
    float* temp_r28;
    CollJoint* var_r27;
    CollJoint* var_r26;
    int start;
    int count;
    int i;

    var_r27 = NULL;
    groundCollVtx = HSD_MemAlloc(0xC000);
    HSD_ASSERT(412, groundCollVtx);
    groundCollLine = HSD_MemAlloc(0x3000);
    HSD_ASSERT(413, groundCollLine);
    groundCollJoint = HSD_MemAlloc(0x3400);
    HSD_ASSERT(414, groundCollJoint);
    grDynamicAttr_801CA0B4();
    if (coll_data == NULL) {
        coll_data = &mpLib_803BF760;
    }
    f31 = Ground_801C0498();
    temp_r29 = &mpLib_80458868[0].right;
    mpLib_80458868[0].right = F32_MAX;
    mpLib_80458868[0].top = F32_MAX;
    temp_r28 = &mpLib_80458868[0].left;
    mpLib_80458868[0].left = -F32_MAX;
    temp_r30 = &mpLib_80458868[0].bottom;
    mpLib_80458868[0].bottom = -F32_MAX;
    for (i = 0; i < coll_data->x28; i++) {
        var_r26 = &groundCollJoint[i];
        var_r26->coll_info = &coll_data->x24[i];
        var_r26->flags = 0x10000;
        var_r26->x10.x = f31 * coll_data->x24[i].x14;
        var_r26->x10.y = f31 * coll_data->x24[i].x18;
        var_r26->x18.x = f31 * coll_data->x24[i].x1C;
        var_r26->x18.y = f31 * coll_data->x24[i].x20;
        var_r26->x20 = NULL;
        var_r26->x28 = NULL;
        var_r26->x24 = NULL;
        var_r26->x30 = NULL;
        var_r26->x2C = NULL;
        var_r26->xE = true;
        if (var_r27 == NULL) {
            mpLib_804D64C4 = var_r26;
        } else {
            var_r27->next = var_r26;
        }
        var_r27 = var_r26;
    }
    var_r26->next = NULL;
    mpLib_804D64C8 = var_r26;
    mpPruneEmptyLines(coll_data);

    count = coll_data->floor_count;
    start = coll_data->floor_start;
    while (count-- > 0) {
        groundCollLine[start].flags =
            coll_data->lines[start].is_empty | 0x10000;
        groundCollLine[start].x0 = &coll_data->lines[start];
        start++;
    }

    count = coll_data->ceiling_count;
    start = coll_data->ceiling_start;
    while (count-- > 0) {
        groundCollLine[start].flags =
            coll_data->lines[start].is_empty | 0x10000;
        groundCollLine[start].x0 = &coll_data->lines[start];
        start++;
    }

    count = coll_data->right_wall_count;
    start = coll_data->right_wall_start;
    while (count-- > 0) {
        groundCollLine[start].flags =
            coll_data->lines[start].is_empty | 0x10000;
        groundCollLine[start].x0 = &coll_data->lines[start];
        start++;
    }

    count = coll_data->left_wall_count;
    start = coll_data->left_wall_start;
    while (count-- > 0) {
        groundCollLine[start].flags =
            coll_data->lines[start].is_empty | 0x10000;
        groundCollLine[start].x0 = &coll_data->lines[start];
        start++;
    }

    count = coll_data->dynamic_count;
    start = coll_data->dynamic_start;
    while (count-- > 0) {
        groundCollLine[start].flags =
            coll_data->lines[start].is_empty | 0x10000;
        groundCollLine[start].x0 = &coll_data->lines[start];
        start++;
    }

    i = 0;
    while (i < coll_data->vert_count) {
        f0 = coll_data->verts[i].x;
        f2 = f31 * f0;
        groundCollVtx[i].x0 = f0;
        groundCollVtx[i].pos.x = f2;
        groundCollVtx[i].x10 = f2;
        f0 = coll_data->verts[i].y;
        f1 = f31 * f0;
        groundCollVtx[i].x4 = f0;
        groundCollVtx[i].pos.y = f1;
        groundCollVtx[i].x14 = f1;
        if (mpLib_80458868[0].top < f1) {
            mpLib_80458868[0].top = f1;
        }
        if (*temp_r30 > f1) {
            *temp_r30 = f1;
        }
        if (*temp_r29 < f2) {
            *temp_r29 = f2;
        }
        if (*temp_r28 > f2) {
            *temp_r28 = f2;
        }
        i++;
    }
    mpLib_804D64B4 = coll_data;
    if (coll_data != NULL) {
        mpIsland_8005A728();
    } else {
        mpIsland_8005A6F8();
    }
    mpLib_80058AA0();
}

int mpLineGetNext(int line_id)
{
    s16 result = groundCollLine[line_id].x0->next_id1;

    if (result != -1) {
        u32 flags = groundCollLine[result].flags;

        if ((flags & 0x10000) && !(flags & 0x40000)) {
            CollVtx* v1 = &groundCollVtx[groundCollLine[line_id].x0->v1_idx];
            CollVtx* v0 = &groundCollVtx[groundCollLine[result].x0->v0_idx];

            if (SQ(v1->pos.x - v0->pos.x) + SQ(v1->pos.y - v0->pos.y) < 4.0) {
                return result;
            }
        }
    }

    return groundCollLine[line_id].x0->next_id0;
}

int mpLineGetPrev(int line_id)
{
    s16 result = groundCollLine[line_id].x0->prev_id1;

    if (result != -1) {
        u32 flags = groundCollLine[result].flags;

        if ((flags & 0x10000) && !(flags & 0x40000)) {
            CollVtx* v0 = &groundCollVtx[groundCollLine[line_id].x0->v0_idx];
            CollVtx* v1 = &groundCollVtx[groundCollLine[result].x0->v1_idx];

            if (SQ(v0->pos.x - v1->pos.x) + SQ(v0->pos.y - v1->pos.y) < 4.0) {
                return result;
            }
        }
    }

    return groundCollLine[line_id].x0->prev_id0;
}

// remap point p from line a to line b
static void mpRemap2d(float* x_out, float* y_out, float ax0, float ay0,
                      float ax1, float ay1, float bx0, float by0, float bx1,
                      float by1, float px, float py)
{
    double dx;
    double dy;
    double dist2;
    float f30;
    float f29;
    dx = ax1 - ax0;
    dy = ay1 - ay0;
    f30 = px - ax0;
    f29 = py - ay0;
    dist2 = (dy * dy) + (dx * dx);
    if (ABS(dist2) > 0.0001) {
        // how far along line a is point p
        double t = (dy * f29 + dx * f30) / dist2;
        if (t > 1.0) {
            t = 1.0;
        } else if (t < 0.0) {
            t = 0.0;
        }

        *x_out = px + (1.0 - t) * (bx0 - ax0) + t * (bx1 - ax1);
        *y_out = py + (1.0 - t) * (by0 - ay0) + t * (by1 - ay1);
    } else {
        *x_out = px + (bx0 - ax0) + (bx1 - ax0);
        *y_out = py + (by0 - ay0) + (by1 - ay0);
    }
}

int mpLib_8004DD90_Floor(int line_id, Vec3* vec, float* y_out, u32* flags_out,
                         Vec3* normal_out)
{
    int dir = 0;
    float x0, y0;
    float x1, y1;
    float x, y;

    LINEID_CHECK(774, line_id);

    while (true) {
        CollLine* line = &groundCollLine[line_id];

        x0 = groundCollVtx[line->x0->v0_idx].pos.x;
        x1 = groundCollVtx[line->x0->v1_idx].pos.x;
        x = vec->x;
        y = vec->y;
        if (x < x0) {
            if (dir != 1) {
                int new_id = mpLineGetPrev(line_id);
                if (new_id == -1 ||
                    !(groundCollLine[new_id].flags & CollLine_Floor))
                {
                    if (x - x0 < -0.1) {
                        return -1;
                    }
                    x = x0;
                    break;
                }
                line_id = new_id;
                dir = -1;
            } else {
                x = x0;
                break;
            }
        } else if (x > x1) {
            if (dir != -1) {
                int new_id = mpLineGetNext(line_id);
                if (new_id == -1 ||
                    !(groundCollLine[new_id].flags & CollLine_Floor))
                {
                    if (x - x1 > 0.1) {
                        return -1;
                    }
                    x = x1;
                    break;
                }

                line_id = new_id;
            } else {
                x = x1;
                break;
            }
        } else {
            break;
        }
    }

    if (flags_out != NULL) {
        *flags_out = groundCollLine[line_id].x0->flags;
    }

    y0 = groundCollVtx[groundCollLine[line_id].x0->v0_idx].pos.y;
    y1 = groundCollVtx[groundCollLine[line_id].x0->v1_idx].pos.y;
    if (y_out != NULL) {
        *y_out = (y1 - y0) * (x - x0) / (x1 - x0) + y0 - y + 0.0001;
    }

    if (normal_out != NULL) {
        normal_out->x = -(y1 - y0);
        normal_out->y = x1 - x0;
        normal_out->z = 0.0F;
        PSVECNormalize(normal_out, normal_out);
    }

    return line_id;
}

int mpLib_8004E090_Ceiling(int line_id, Vec3* vec, float* y_out,
                           u32* flags_out, Vec3* normal_out)
{
    int dir = 0;
    float x0, y0;
    float x1, y1;
    float x;

    LINEID_CHECK(893, line_id);

    x = vec->x;
    while (true) {
        CollLine* line_r4 = &groundCollLine[line_id];
        x0 = groundCollVtx[line_r4->x0->v0_idx].pos.x;
        x1 = groundCollVtx[line_r4->x0->v1_idx].pos.x;
        if (vec->x < x1) {
            if (dir != 1) {
                int new_id = mpLineGetNext(line_id);
                if (new_id == -1 ||
                    !(groundCollLine[new_id].flags & CollLine_Ceiling))
                {
                    if (vec->x - x1 < -0.1) {
                        return -1;
                    }

                    x = x1;
                    break;
                }
                line_id = new_id;
                dir = -1;
                continue;
            }
            x = x1;
        } else if (vec->x > x0) {
            if (dir != -1) {
                int new_id = mpLineGetPrev(line_id);
                if (new_id == -1 ||
                    !(groundCollLine[new_id].flags & CollLine_Ceiling))
                {
                    if (vec->x - x0 > 0.1) {
                        return -1;
                    }

                    x = x0;
                    break;
                }
                line_id = new_id;
                dir = 1;
                continue;
            }
            x = x0;
        }
        break;
    }

    if (flags_out != NULL) {
        *flags_out = groundCollLine[line_id].x0->flags;
    }

    y0 = groundCollVtx[groundCollLine[line_id].x0->v0_idx].pos.y;
    y1 = groundCollVtx[groundCollLine[line_id].x0->v1_idx].pos.y;

    if (y_out != NULL) {
        *y_out = (y1 - y0) * (x - x0) / (x1 - x0) + y0 - vec->y - 0.0001;
    }

    if (normal_out != NULL) {
        normal_out->x = -(y1 - y0);
        normal_out->y = x1 - x0;
        normal_out->z = 0.0F;
        PSVECNormalize(normal_out, normal_out);
    }

    return line_id;
}

int mpLib_8004E398_LeftWall(int line_id, Vec3* vec, float* x_out,
                            u32* flags_out, Vec3* normal_out)
{
    int dir = 0;
    float x0, y0;
    float x1, y1;
    float y;

    LINEID_CHECK(1014, line_id);

    y = vec->y;
    while (true) {
        CollLine* line_r4 = &groundCollLine[line_id];
        y0 = groundCollVtx[line_r4->x0->v0_idx].pos.y;
        y1 = groundCollVtx[line_r4->x0->v1_idx].pos.y;
        if (vec->y < y0) {
            if (dir != 1) {
                int new_id = mpLineGetPrev(line_id);
                if (new_id == -1 ||
                    !(groundCollLine[new_id].flags & CollLine_LeftWall))
                {
                    if (vec->y - y0 < -0.1) {
                        return -1;
                    }
                    y = y0;
                    break;
                }
                line_id = new_id;
                dir = -1;
                continue;
            }
        } else if (vec->y > y1) {
            if (dir != -1) {
                int new_id = mpLineGetNext(line_id);
                if (new_id == -1 ||
                    !(groundCollLine[new_id].flags & CollLine_LeftWall))
                {
                    if (vec->y - y1 > 0.1) {
                        return -1;
                    }
                    y = y1;
                    break;
                }
                line_id = new_id;
                dir = 1;
                continue;
            }
        }
        break;
    }

    if (flags_out != NULL) {
        *flags_out = groundCollLine[line_id].x0->flags;
    }

    x0 = groundCollVtx[groundCollLine[line_id].x0->v0_idx].pos.x;
    x1 = groundCollVtx[groundCollLine[line_id].x0->v1_idx].pos.x;

    if (x_out != NULL) {
        *x_out = x0 + (x1 - x0) * (y - y0) / (y1 - y0) - vec->x;
    }

    if (normal_out != NULL) {
        normal_out->x = -(y1 - y0);
        normal_out->y = x1 - x0;
        normal_out->z = 0.0F;
        PSVECNormalize(normal_out, normal_out);
    }

    return line_id;
}

int mpLib_8004E684_RightWall(int line_id, Vec3* vec, float* x_out,
                             u32* flags_out, Vec3* normal_out)
{
    int dir = 0;
    float x0, y0;
    float x1, y1;
    float y;

    LINEID_CHECK(1134, line_id);

    y = vec->y;
    while (true) {
        CollLine* line_r4 = &groundCollLine[line_id];
        y0 = groundCollVtx[line_r4->x0->v0_idx].pos.y;
        y1 = groundCollVtx[line_r4->x0->v1_idx].pos.y;
        if (vec->y > y0) {
            if (dir != -1) {
                int new_id_r8 = mpLineGetPrev(line_id);
                if (new_id_r8 == -1 ||
                    !(groundCollLine[new_id_r8].flags & CollLine_RightWall))
                {
                    if (vec->y - y0 > 0.1) {
                        return -1;
                    }
                    y = y0;
                    break;
                }
                line_id = new_id_r8;
                dir = 1;
                continue;
            }
            y = y0;
        } else if (vec->y < y1) {
            if (dir != 1) {
                int new_id_r9 = mpLineGetNext(line_id);
                if (new_id_r9 == -1 ||
                    !(groundCollLine[new_id_r9].flags & CollLine_RightWall))
                {
                    if (vec->y - y1 < -0.1) {
                        return -1;
                    }
                    y = y1;
                    break;
                }
                line_id = new_id_r9;
                dir = -1;
                continue;
            }
            y = y1;
        }
        break;
    }

    if (flags_out != NULL) {
        *flags_out = groundCollLine[line_id].x0->flags;
    }

    x0 = groundCollVtx[groundCollLine[line_id].x0->v0_idx].pos.x;
    x1 = groundCollVtx[groundCollLine[line_id].x0->v1_idx].pos.x;

    if (x_out != NULL) {
        *x_out = x0 + ((x1 - x0) * (y - y0)) / (y1 - y0) - vec->x;
    }

    if (normal_out != NULL) {
        normal_out->x = -(y1 - y0);
        normal_out->y = x1 - x0;
        normal_out->z = 0.0F;
        PSVECNormalize(normal_out, normal_out);
    }

    return line_id;
}

// direction dependent line intersection
bool mpLib_8004E97C(float ax0, float ay0, float ax1, float ay1, float bx0,
                    float by0, float bx1, float by1, float* int_x,
                    float* int_y)
{
    bool b1_below_a = false;
    bool b2_above_a = false;

    // b entirely left/right of a
    if (ax0 <= ax1) {
        if ((bx0 < ax0 && bx1 < ax0) || (ax1 < bx0 && ax1 < bx1)) {
            return false;
        }
    } else {
        if ((bx0 < ax1 && bx1 < ax1) || (ax0 < bx0 && ax0 < bx1)) {
            return false;
        }
    }

    // b entirely above/below a
    if (ay0 <= ay1) {
        if ((by0 < ay0 && by1 < ay0) || (ay1 < by0 && ay1 < by1)) {
            return false;
        }
    } else {
        if ((by0 < ay1 && by1 < ay1) || (ay0 < by0 && ay0 < by1)) {
            return false;
        }
    }

    {
        double ah = ay1 - ay0;
        double dx0 = bx0 - ax0;
        double aw = ax1 - ax0;
        double dy0 = by0 - ay0;
        double hs_b0_a = (aw * dy0) - (ah * dx0);
        double dy1;
        double dx1;
        double det;
        double hs_b1_a;
        double bh;
        double bw;

        if (hs_b0_a < 0.0) {
            if (hs_b0_a < -0.1) {
                return false;
            }
            b1_below_a = true;
        }

        dx1 = bx1 - ax1;
        dy1 = by1 - ay1;

        hs_b1_a = (aw * dy1) - (ah * dx1);
        if (hs_b1_a > 0.0) {
            if (hs_b1_a > 0.1) {
                return false;
            }
            b2_above_a = true;
        }

        // check if a and b are colinear
        if (hs_b0_a == 0.0 && hs_b1_a == 0.0) {
            return false;
        }

        det = (dx0 * dy1) - (dy0 * dx1);
        if (det < hs_b0_a) {
            if (det < hs_b1_a) {
                return false;
            }
        } else if (det > hs_b0_a) {
            if (det > hs_b1_a) {
                return false;
            }
        }

        bw = bx1 - bx0;
        bh = by1 - by0;
        if (!((bw == 0.0 && bh == 0.0) || (b1_below_a && b2_above_a) ||
              (hs_b0_a >= 0.0 && b2_above_a)))
        {
            double area = (bw * ah) - (bh * aw);

            if (ABS(area) > 0.0001F) {
                double t =
                    ((bw * dy0) - (bh * dx0)) / area; // barycentric weight
                if (t > 0.0) {
                    if (t < 1.0) {
                        *int_x = (aw * t) + ax0;
                        *int_y = (ah * t) + ay0;
                    } else {
                        *int_x = ax1;
                        *int_y = ay1;
                    }
                } else {
                    *int_x = ax0;
                    *int_y = ay0;
                }

                goto tlabel;
            }
        }
        return false;
    tlabel:
        return true;
    }
}

bool mpLib_8004EBF8(f32* arg0, f32* arg1, f32 arg8, f32 arg9, f32 argA,
                    f32 argB, f32 argC, f32 argD, f32 argE)
{
    f32 d2;
    f64 d1;
    f32 var_f3;
    f32 var_f8;
    f64 var_f5;

    var_f3 = argA;
    if (arg8 < var_f3) {
        if ((argB < arg8 && argD < arg8) || (var_f3 < argB && var_f3 < argD)) {
            return false;
        }
        if (argC - arg9 < -0.0001 || argE - arg9 > 0.0001) {
            return false;
        }
        var_f8 = arg8;
    } else {
        if ((argB < var_f3 && argD < var_f3) || (arg8 < argB && arg8 < argD)) {
            return false;
        }
        if (argE - arg9 < -0.0001 || argC - arg9 > 0.0001) {
            return false;
        }
        var_f8 = var_f3;
        var_f3 = arg8;
    }
    d1 = argE - argC;
    d2 = argD - argB;
    if (ABS(d1) < 0.0001) {
        return false;
    }
    var_f5 = d2 / d1 * (arg9 - argC) + argB;
    if (d2 / d1 * (arg9 - argC) + argB - var_f8 < 0.0) {
        if (d2 / d1 * (arg9 - argC) + argB - var_f8 < -0.1) {
            return false;
        }
        var_f5 = var_f8;
    }
    if (var_f5 - var_f3 > 0.0) {
        if (var_f5 - var_f3 > 0.1) {
            return false;
        }
        var_f5 = var_f3;
    }
    *arg0 = var_f5;
    *arg1 = arg9;
    return true;
}

void mpLib_8004ED5C(int line_id, float* x0_out, float* y0_out, float* x1_out,
                    float* y1_out)
{
    bool calculated_distance = false;
    mpLib_Line* line_r11 = groundCollLine[line_id].x0;

    float x0_f0 = groundCollVtx[line_r11->v0_idx].pos.x;
    float y0_f1 = groundCollVtx[line_r11->v0_idx].pos.y;
    float x1_f2 = groundCollVtx[line_r11->v1_idx].pos.x;
    float y1_f3 = groundCollVtx[line_r11->v1_idx].pos.y;
    float distance;

    if (mpLineGetPrev(line_id) != -1) {
        distance = sqrtf(SQ(x0_f0 - x1_f2) + SQ(y0_f1 - y1_f3));
        if (distance > 0.001F) {
            x0_f0 += (x0_f0 - x1_f2) / distance;
            y0_f1 += (y0_f1 - y1_f3) / distance;
        }
        calculated_distance = true;
    }

    if (mpLineGetNext(line_id) != -1) {
        if (!calculated_distance) {
            distance = sqrtf(SQ(x0_f0 - x1_f2) + SQ(y0_f1 - y1_f3));
        }
        if (distance > 0.001F) {
            x1_f2 += (x1_f2 - x0_f0) / distance;
            y1_f3 += (y1_f3 - y0_f1) / distance;
        }
    }

    *x0_out = x0_f0;
    *y0_out = y0_f1;
    *x1_out = x1_f2;
    *y1_out = y1_f3;
}

bool mpLib_8004F008_Floor(float ax, float ay, float bx, float by,
                          float y_offset, Vec3* vec_out, int* line_id_out,
                          u32* flags_out, Vec3* normal_out, int line_id,
                          int joint_id0, int joint_id1,
                          bool (*cb)(Fighter_GObj*, int), Fighter_GObj* gobj)
{
    float min_dist2_f30;
    CollJoint* r29;
    int i_r28;
    bool result_r27;
    bool temp_r3;

    result_r27 = false;
    min_dist2_f30 = F32_MAX;
    temp_r3 = mpLib_800588C8();
    if (!temp_r3) {
        mpLib_80058970(ax, ay, bx, by);
    }

    for (r29 = mpLib_804D64C4; r29 != NULL; r29 = r29->next) {
        CollLine* line_r26;
        int var_r25;
        int var_r24;
        CollInfo* temp_r4;
        if (r29->flags & 0x1000) {
            continue;
        }

        if (joint_id0 == r29 - groundCollJoint ||
            (joint_id1 != -1 && joint_id1 != r29 - groundCollJoint))
        {
            continue;
        }

        temp_r4 = r29->coll_info;
        i_r28 = 0;
        var_r25 = temp_r4->floor_count;
        var_r24 = temp_r4->dynamic_count;
        line_r26 = &groundCollLine[temp_r4->floor_start];
        for (; i_r28 < var_r25; i_r28 += 1, line_r26 += 1) {
            float px_sp54;
            float py_sp50;
            float x0_sp48;
            float y0_sp44;
            float x1_sp40;
            float y1_sp3C;
        block_8:
            if (cb != NULL && !cb(gobj, line_r26 - groundCollLine)) {
                continue;
            }

            if (line_id == line_r26 - groundCollLine) {
                continue;
            }

            if (!(line_r26->flags & CollLine_Floor) ||
                !(line_r26->flags & 0x10000) ||
                line_r26->flags & LINE_FLAG_EMPTY)
            {
                continue;
            }

            mpLib_8004ED5C((line_r26 - groundCollLine) / 8, &x0_sp48, &y0_sp44,
                           &x1_sp40, &y1_sp3C);
            y0_sp44 += y_offset;
            y1_sp3C += y_offset;
            if (ABS(y0_sp44 - y1_sp3C) > 0.0001) {
                if (mpLib_8004E97C(x0_sp48, y0_sp44, x1_sp40, y1_sp3C, ax, ay,
                                   bx, by, &px_sp54, &py_sp50))
                {
                    float dx = px_sp54 - ax;
                    float dy = py_sp50 - ay;
                    float dx2 = dx * dx;
                    float dy2 = dy * dy;
                    float dist2 = dx2 + dy2;
                    if (min_dist2_f30 > dist2) {
                        min_dist2_f30 = dist2;
                        if (vec_out != NULL) {
                            vec_out->x = px_sp54;
                            vec_out->y = py_sp50;
                            vec_out->z = 0.0F;
                        }
                        if (line_id_out != NULL) {
                            *line_id_out = line_r26 - groundCollLine;
                        }
                        if (flags_out != NULL) {
                            *flags_out = line_r26->x0->flags;
                        }
                        if (normal_out != NULL) {
                            normal_out->x = -(y1_sp3C - y0_sp44);
                            normal_out->y = x1_sp40 - x0_sp48;
                            normal_out->z = 0.0F;
                            PSVECNormalize(normal_out, normal_out);
                        }
                        result_r27 = true;
                    }
                }
            } else {
                if (ay >= by &&
                    mpLib_8004EBF8(&px_sp54, &py_sp50, x0_sp48, y0_sp44,
                                   x1_sp40, ax, ay, bx, by))
                {
                    float dx = px_sp54 - ax;
                    float dx2 = dx * dx;
                    float dy = py_sp50 - ay;
                    float dy2 = dy * dy;
                    float dist2 = dx2 + dy2;
                    if (min_dist2_f30 > dist2) {
                        min_dist2_f30 = dist2;
                        if (vec_out != NULL) {
                            vec_out->x = px_sp54;
                            vec_out->y = py_sp50;
                            vec_out->z = 0.0F;
                        }
                        if (line_id_out != NULL) {
                            *line_id_out = line_r26 - groundCollLine;
                        }
                        if (flags_out != NULL) {
                            *flags_out = line_r26->x0->flags;
                        }
                        if (normal_out != NULL) {
                            normal_out->x = 0.0F;
                            normal_out->y = 1.0F;
                            normal_out->z = 0.0F;
                        }
                        result_r27 = true;
                    }
                }
            }
        }

        if (var_r24 != 0) {
            var_r25 = var_r24;
            i_r28 = 0;
            var_r24 = 0;
            line_r26 = &groundCollLine[r29->coll_info->dynamic_start];
            goto block_8;
        }
    }

    if (!temp_r3) {
        mpLib_80058AA0();
    }

    return result_r27;
}

bool mpLib_8004F400_Floor(float ax, float ay, float bx, float by,
                          float y_offset, Vec3* vec_out, int* line_id_out,
                          u32* flags_out, Vec3* normal_out, int line_id,
                          int joint_id0, int joint_id1,
                          bool (*cb)(Fighter_GObj*, int), Fighter_GObj* gobj)
{
    float min_dist2 = F32_MAX;
    float old_x = ax;
    float old_y = ay;
    CollJoint* joint;
    int i;
    bool result = false;
    bool r3;
    PAD_STACK(8);

    r3 = mpLib_800588C8();
    if (!r3) {
        mpLib_80058970(ax, ay, bx, by);
    }

    for (joint = mpLib_804D64C4; joint != NULL; joint = joint->next) {
        CollLine* line;
        int count;
        int count2;
        if (joint->flags & 0x1000) {
            continue;
        }

        if (joint_id0 == joint - groundCollJoint ||
            (joint_id1 != -1 && joint_id1 != joint - groundCollJoint))
        {
            continue;
        }

        count = joint->coll_info->floor_count;
        count2 = joint->coll_info->dynamic_count;
        line = &groundCollLine[joint->coll_info->floor_start];
        for (i = 0; i < count; i++, line++) {
        block_8:
            if (cb != NULL && !cb(gobj, line - groundCollLine)) {
                continue;
            }

            if (line_id == line - groundCollLine) {
                continue;
            }

            if (!(line->flags & CollLine_Floor) || !(line->flags & 0x10000) ||
                line->flags & LINE_FLAG_EMPTY)
            {
                continue;
            }

            {
                CollVtx* v0_r5 = &groundCollVtx[line->x0->v0_idx];
                CollVtx* v1_r6 = &groundCollVtx[line->x0->v1_idx];
                float v0x = v0_r5->pos.x;
                float v0y = y_offset + v0_r5->pos.y;
                float v1x = v1_r6->pos.x;
                float v1y = y_offset + v1_r6->pos.y;
                float x_f23;
                float y_f22;
                float dx2;
                float dy2;
                float dist2;
                float int_x_sp4C;
                float int_y_sp48;
                PAD_STACK(4);

                if (joint->flags & 0x700) {
                    mpRemap2d(&ax, &ay, v0_r5->x10, v0_r5->x14, v1_r6->x10,
                              v1_r6->x14, v0x, v0y, v1x, v1y, old_x, old_y);
                } else {
                    ax = old_x;
                    ay = old_y;
                }

                x_f23 = bx - ax;
                y_f22 = by - ay;

                if (ABS(v0y - v1y) > 0.0001) {
                    if (mpLib_8004E97C(v0x, v0y, v1x, v1y, ax, ay, bx, by,
                                       &int_x_sp4C, &int_y_sp48))
                    {
                        dx2 = SQ(int_x_sp4C - old_x);
                        dy2 = SQ(int_y_sp48 - old_y);
                        dist2 = dx2 + dy2;

                        if (x_f23 * (int_x_sp4C - old_x) +
                                y_f22 * (int_y_sp48 - old_y) <
                            0.0F)
                        {
                            dist2 = -dist2;
                        }
                        if (min_dist2 > dist2) {
                            min_dist2 = dist2;
                            if (vec_out) {
                                vec_out->x = int_x_sp4C;
                                vec_out->y = int_y_sp48;
                                vec_out->z = 0.0F;
                            }
                            if (line_id_out) {
                                *line_id_out = line - groundCollLine;
                            }
                            if (flags_out) {
                                *flags_out = line->x0->flags;
                            }
                            if (normal_out) {
                                normal_out->x = -(v1y - v0y);
                                normal_out->y = v1x - v0x;
                                normal_out->z = 0.0F;
                                PSVECNormalize(normal_out, normal_out);
                            }
                            result = true;
                        }
                    }
                } else if (ay >= by &&
                           mpLib_8004EBF8(&int_x_sp4C, &int_y_sp48, v0x, v0y,
                                          v1x, ax, ay, bx, by))
                {
                    dx2 = SQ(int_x_sp4C - old_x);
                    dy2 = SQ(int_y_sp48 - old_y);
                    dist2 = dx2 + dy2;

                    if (x_f23 * (int_x_sp4C - old_x) +
                            y_f22 * (int_y_sp48 - old_y) <
                        0.0F)
                    {
                        dist2 = -dist2;
                    }

                    if (min_dist2 > dist2) {
                        min_dist2 = dist2;
                        if (vec_out) {
                            vec_out->x = int_x_sp4C;
                            vec_out->y = int_y_sp48;
                            vec_out->z = 0.0F;
                        }
                        if (line_id_out) {
                            *line_id_out = line - groundCollLine;
                        }
                        if (flags_out) {
                            *flags_out = line->x0->flags;
                        }
                        if (normal_out) {
                            normal_out->x = 0.0F;
                            normal_out->y = 1.0F;
                            normal_out->z = 0.0F;
                        }
                        result = true;
                    }
                }
            }
        }

        if (count2 != 0) {
            count = count2;
            i = 0;
            count2 = 0;
            line = &groundCollLine[joint->coll_info->dynamic_start];
            goto block_8;
        }
    }

    if (!r3) {
        mpLib_80058AA0();
    }

    return result;
}

bool mpLib_8004F8A4_Ceiling(float ax, float ay, float bx, float by,
                            Vec3* vec_out, int* line_id_out, u32* flags_out,
                            Vec3* normal_out, int joint_id0, int joint_id1)
{
    float min_dist2 = F32_MAX;
    CollJoint* r29;
    int i_r28;
    bool result = false;
    bool temp_r3;
    PAD_STACK(8);

    temp_r3 = mpLib_800588C8();
    if (!temp_r3) {
        mpLib_80058970(ax, ay, bx, by);
    }

    for (r29 = mpLib_804D64C4; r29 != NULL; r29 = r29->next) {
        CollLine* line_r26;
        int var_r25;
        int var_r24;
        CollInfo* coll_info;
        if (r29->flags & 0x1000) {
            continue;
        }

        if (joint_id0 == r29 - groundCollJoint ||
            (joint_id1 != -1 && joint_id1 != r29 - groundCollJoint))
        {
            continue;
        }

        coll_info = r29->coll_info;
        i_r28 = 0;
        var_r25 = coll_info->ceiling_count;
        var_r24 = coll_info->dynamic_count;
        line_r26 = &groundCollLine[coll_info->ceiling_start];
        for (; i_r28 < var_r25; i_r28 += 1, line_r26 += 1) {
            float int_x;
            float int_y;
            u8 pad[4];
            float x0;
            float y0;
            float x1;
            float y1;
            float dist2;

        block_8:
            if (!(line_r26->flags & CollLine_Ceiling) ||
                !(line_r26->flags & 0x10000) ||
                line_r26->flags & LINE_FLAG_EMPTY)
            {
                continue;
            }

            mpLib_8004ED5C(line_r26 - groundCollLine, &x0, &y0, &x1, &y1);
            if (ABS(y0 - y1) > 0.0001) {
                if (mpLib_8004E97C(x0, y0, x1, y1, ax, ay, bx, by, &int_x,
                                   &int_y))
                {
                    dist2 = SQ(int_x - ax) + SQ(int_y - ay);
                    if (min_dist2 > dist2) {
                        min_dist2 = dist2;

                        if (vec_out != NULL) {
                            vec_out->x = int_x;
                            vec_out->y = int_y;
                            vec_out->z = 0.0F;
                        }

                        if (line_id_out != NULL) {
                            *line_id_out = line_r26 - groundCollLine;
                        }

                        if (flags_out != NULL) {
                            *flags_out = line_r26->x0->flags;
                        }

                        if (normal_out != NULL) {
                            normal_out->x = -(y1 - y0);
                            normal_out->y = x1 - x0;
                            normal_out->z = 0.0F;
                            PSVECNormalize(normal_out, normal_out);
                        }

                        result = true;
                    }
                }
            } else {
                if (ay <= by &&
                    mpLib_8004EBF8(&int_x, &int_y, x0, y0, x1, ax, ay, bx, by))
                {
                    dist2 = SQ(int_x - ax) + SQ(int_y - ay);
                    if (min_dist2 > dist2) {
                        min_dist2 = dist2;

                        if (vec_out != NULL) {
                            vec_out->x = int_x;
                            vec_out->y = int_y;
                            vec_out->z = 0.0F;
                        }

                        if (line_id_out != NULL) {
                            *line_id_out = line_r26 - groundCollLine;
                        }

                        if (flags_out != NULL) {
                            *flags_out = line_r26->x0->flags;
                        }

                        if (normal_out != NULL) {
                            normal_out->x = 0.0F;
                            normal_out->y = -1.0F;
                            normal_out->z = 0.0F;
                        }

                        result = true;
                    }
                }
            }
        }

        if (var_r24 != 0) {
            var_r25 = var_r24;
            i_r28 = 0;
            var_r24 = 0;
            line_r26 = &groundCollLine[r29->coll_info->dynamic_start];
            goto block_8;
        }
    }

    if (!temp_r3) {
        mpLib_80058AA0();
    }

    return result;
}

bool mpLib_8004FC2C_Ceiling(float ax, float ay, float bx, float by,
                            Vec3* vec_out, int* line_id_out, u32* flags_out,
                            Vec3* normal_out, int joint_id0, int joint_id1)
{
    float min_f30 = F32_MAX;
    float f29 = ax;
    float f28 = ay;
    CollJoint* joint;
    int r28;
    int r27 = false;
    int r3 = mpLib_800588C8();

    if (!r3) {
        mpLib_80058970(ax, ay, bx, by);
    }

    for (joint = mpLib_804D64C4; joint != NULL; joint = joint->next) {
        CollLine* r26;
        int r25;
        int r24;
        if (joint->flags & 0x1000) {
            continue;
        }

        if (joint_id0 == (joint - groundCollJoint) ||
            !(joint_id1 == -1 || joint_id1 == (joint - groundCollJoint)))
        {
            continue;
        }

        r25 = joint->coll_info->ceiling_count;
        r24 = joint->coll_info->dynamic_count;
        r26 = &groundCollLine[joint->coll_info->ceiling_start];
        for (r28 = 0; r28 < r25; r28++, r26++) {
        block_8:
            if (r26->flags & CollLine_Ceiling && r26->flags & 0x10000 &&
                !(r26->flags & LINE_FLAG_EMPTY))
            {
                float dx2;
                float dy2;
                float dist2;
                float x_f23;
                float y_f22;
                float sp58;
                float sp54;
                u8 _[12];
                float sp44;
                float sp40;
                float sp3C;
                float sp38;
                mpLib_8004ED5C(r26 - groundCollLine, &sp44, &sp40, &sp3C,
                               &sp38);

                if (joint->flags & 0x700) {
                    mpLib_Line* line_r3 = r26->x0;
                    CollVtx* v1_r6 = &groundCollVtx[line_r3->v1_idx];
                    CollVtx* v0_r5 = &groundCollVtx[line_r3->v0_idx];
                    mpRemap2d(&ax, &ay, v0_r5->x10, v0_r5->x14, v1_r6->x10,
                              v1_r6->x14, sp44, sp40, sp3C, sp38, f29, f28);
                } else {
                    ax = f29;
                    ay = f28;
                }

                x_f23 = bx - ax;
                y_f22 = by - ay;
                if (ABS(sp40 - sp38) > 0.0001) {
                    if (mpLib_8004E97C(sp44, sp40, sp3C, sp38, ax, ay, bx, by,
                                       &sp58, &sp54))
                    {
                        dx2 = SQ(sp58 - f29);
                        dy2 = SQ(sp54 - f28);
                        dist2 = dx2 + dy2;
                        if ((x_f23 * (sp58 - f29)) + (y_f22 * (sp54 - f28)) <
                            0.0F)
                        {
                            dist2 = -dist2;
                        }
                        if (min_f30 > dist2) {
                            min_f30 = dist2;

                            if (vec_out != NULL) {
                                vec_out->x = sp58;
                                vec_out->y = sp54;
                                vec_out->z = 0.0F;
                            }

                            if (line_id_out != NULL) {
                                *line_id_out = r26 - groundCollLine;
                            }

                            if (flags_out != NULL) {
                                *flags_out = r26->x0->flags;
                            }

                            if (normal_out != NULL) {
                                normal_out->x = -(sp38 - sp40);
                                normal_out->y = sp3C - sp44;
                                normal_out->z = 0.0F;
                                PSVECNormalize(normal_out, normal_out);
                            }

                            r27 = true;
                        }
                    }
                } else {
                    if (ay <= by && mpLib_8004EBF8(&sp58, &sp54, sp44, sp40,
                                                   sp3C, ax, ay, bx, by))
                    {
                        dx2 = SQ(sp58 - f29);
                        dy2 = SQ(sp54 - f28);
                        dist2 = dx2 + dy2;
                        if ((x_f23 * (sp58 - f29)) + (y_f22 * (sp54 - f28)) <
                            0.0F)
                        {
                            dist2 = -dist2;
                        }
                        if (min_f30 > dist2) {
                            min_f30 = dist2;

                            if (vec_out != NULL) {
                                vec_out->x = sp58;
                                vec_out->y = sp54;
                                vec_out->z = 0.0F;
                            }

                            if (line_id_out != NULL) {
                                *line_id_out = r26 - groundCollLine;
                            }

                            if (flags_out != NULL) {
                                *flags_out = r26->x0->flags;
                            }

                            if (normal_out != NULL) {
                                normal_out->x = 0.0F;
                                normal_out->y = -1.0F;
                                normal_out->z = 0.0F;
                            }

                            r27 = true;
                        }
                    }
                }
            }
        }

        if (r24 != 0) {
            r25 = r24;
            r28 = 0;
            r24 = 0;
            r26 = &groundCollLine[joint->coll_info->dynamic_start];
            goto block_8;
        }
    }

    if (!r3) {
        mpLib_80058AA0();
    }

    return r27;
}

bool mpLib_80050068(float* r3, float* r4, float f1, float f2, float f3,
                    float f4, float f5, float f6, float f7)
{
    double d2;
    double d4;
    double d5;
    double d7;
    float min;
    float max;
    if (f2 < f3) {
        if ((f5 < f2 && f7 < f2) || (f3 < f5 && f3 < f7)) {
            return false;
        }
        if (f6 - f1 < -0.0001 || f4 - f1 > 0.0001) {
            return false;
        }
        min = f2;
        max = f3;
    } else {
        if ((f5 < f3 && f7 < f3) || (f2 < f5 && f2 < f7)) {
            return false;
        }
        if (f4 - f1 < -0.0001 || f6 - f1 > 0.0001) {
            return false;
        }
        min = f3;
        max = f2;
    }
    d7 = f7 - f5;
    d2 = f6 - f4;
    if (ABS(d2) < 0.0001) {
        return false;
    }
    d2 = (d7 / d2 * (f1 - f4)) + f5;
    d4 = d2;
    d5 = d2;
    d4 = d4 - min;
    if (d4 < 0.0) {
        if (d4 < -0.1) {
            return false;
        }
        d5 = min;
    }
    d4 = d5 - max;
    if (d4 > 0.0) {
        if (d4 > 0.1) {
            return false;
        }
        d5 = max;
    }
    *r3 = f1;
    *r4 = d5;
    return true;
}

bool mpLib_800501CC_LeftWall(float ax, float ay, float bx, float by,
                             Vec3* vec_out, int* line_id_out, u32* flags_out,
                             Vec3* normal_out, int joint_id0, int joint_id1)
{
    float min;
    CollJoint* joint;
    int r28;
    int result;
    CollLine* p26;
    int r25;
    int r24;
    CollInfo* coll_info;
    int r3;
    PAD_STACK(4);

    result = false;
    min = F32_MAX;
    r3 = mpLib_800588C8();

    if (!r3) {
        mpLib_80058970(ax, ay, bx, by);
    }

    for (joint = mpLib_804D64C4; joint != NULL; joint = joint->next) {
        if (joint->flags & 0x1000) {
            continue;
        }

        if (joint_id0 == (joint - groundCollJoint) ||
            !(joint_id1 == -1 || joint_id1 == (joint - groundCollJoint)))
        {
            continue;
        }

        coll_info = joint->coll_info;

        r25 = coll_info->left_wall_count;
        r24 = coll_info->dynamic_count;
        p26 = &groundCollLine[coll_info->left_wall_start];

        for (r28 = 0; r28 < r25; r28++, p26++) {
        block_8:
            if (p26->flags & CollLine_LeftWall && p26->flags & 0x10000 &&
                !(p26->flags & LINE_FLAG_EMPTY))
            {
                mpLib_Line* line = p26->x0;
                CollVtx* v0 = &groundCollVtx[line->v0_idx];
                CollVtx* v1 = &groundCollVtx[line->v1_idx];
                float x0 = v0->pos.x;
                float y0 = v0->pos.y;
                float x1 = v1->pos.x;
                float y1 = v1->pos.y;
                float dx2;
                float dy2;
                float dist2;
                float x;
                float y;
                if (ABS(x0 - x1) > 0.0001) {
                    if (mpLib_8004E97C(x0, y0, x1, y1, ax, ay, bx, by, &x, &y))
                    {
                        dx2 = SQ(x - ax);
                        dy2 = SQ(y - ay);
                        dist2 = dx2 + dy2;
                        if (min > dist2) {
                            min = dist2;
                            if (vec_out != NULL) {
                                vec_out->x = x;
                                vec_out->y = y;
                                vec_out->z = 0.0F;
                            }
                            if (line_id_out != NULL) {
                                *line_id_out = p26 - groundCollLine;
                            }
                            if (flags_out != NULL) {
                                *flags_out = p26->x0->flags;
                            }
                            if (normal_out != NULL) {
                                normal_out->x = -(y1 - y0);
                                normal_out->y = x1 - x0;
                                normal_out->z = 0.0F;
                                PSVECNormalize(normal_out, normal_out);
                            }
                            result = true;
                        }
                    }
                } else {
                    if ((ax <= bx) &&
                        mpLib_80050068(&x, &y, x0, y0, y1, ax, ay, bx, by))
                    {
                        dx2 = SQ(x - ax);
                        dy2 = SQ(y - ay);
                        dist2 = dx2 + dy2;
                        if (min > dist2) {
                            min = dist2;
                            if (vec_out != NULL) {
                                vec_out->x = x;
                                vec_out->y = y;
                                vec_out->z = 0.0F;
                            }
                            if (line_id_out != NULL) {
                                *line_id_out = p26 - groundCollLine;
                            }
                            if (flags_out != NULL) {
                                *flags_out = p26->x0->flags;
                            }
                            if (normal_out != NULL) {
                                normal_out->x = -1.0F;
                                normal_out->y = 0.0F;
                                normal_out->z = 0.0F;
                            }
                            result = true;
                        }
                    }
                }
            }
        }

        if (r24 != 0) {
            r25 = r24;
            r28 = 0;
            r24 = 0;
            p26 = &groundCollLine[joint->coll_info->dynamic_start];
            goto block_8;
        }
    }
    if (!r3) {
        mpLib_80058AA0();
    }

    return result;
}

bool mpLib_8005057C_LeftWall(Vec3* vec_out, int* line_id_out, u32* flags_out,
                             Vec3* normal_out, int joint_id0, int joint_id1,
                             float f1, float f2, float f3, float f4)
{
    float min_f30;
    float f29 = f1;
    float f28 = f2;
    CollJoint* joint;
    int r28;
    int r27;
    CollLine* r26;
    int r25;
    int r24;
    CollInfo* ci_r4;
    int r3;
    u8 _[8];

    r27 = false;
    min_f30 = F32_MAX;

    r3 = mpLib_800588C8();
    if (!r3) {
        mpLib_80058970(f1, f2, f3, f4);
    }

    for (joint = mpLib_804D64C4; joint != NULL; joint = joint->next) {
        if (joint->flags & 0x1000) {
            continue;
        }

        if (joint_id0 == (joint - groundCollJoint) ||
            !(joint_id1 == -1 || joint_id1 == (joint - groundCollJoint)))
        {
            continue;
        }

        ci_r4 = joint->coll_info;
        r25 = ci_r4->left_wall_count;
        r24 = ci_r4->dynamic_count;
        r26 = &groundCollLine[ci_r4->left_wall_start];
        for (r28 = 0; r28 < r25; r28++, r26++) {
        block_8:
            if (r26->flags & CollLine_LeftWall && r26->flags & 0x10000 &&
                !(r26->flags & LINE_FLAG_EMPTY))
            {
                mpLib_Line* line_r3 = r26->x0;
                CollVtx* v0_r5 = &groundCollVtx[line_r3->v0_idx];
                CollVtx* v1_r6 = &groundCollVtx[line_r3->v1_idx];
                float x0_f27 = v0_r5->pos.x;
                float y0_f26 = v0_r5->pos.y;
                float x1_f25 = v1_r6->pos.x;
                float y1_f24 = v1_r6->pos.y;
                float x_f23;
                float y_f22;
                float dx2;
                float dy2;
                float dist2;
                float int_x_sp3C;
                float int_y_sp38;

                if (joint->flags & 0x700) {
                    mpRemap2d(&f1, &f2, v0_r5->x10, v0_r5->x14, v1_r6->x10,
                              v1_r6->x14, x0_f27, y0_f26, x1_f25, y1_f24, f29,
                              f28);
                } else {
                    f1 = f29;
                    f2 = f28;
                }

                x_f23 = f3 - f1;
                y_f22 = f4 - f2;
                if (ABS(x0_f27 - x1_f25) > 0.0001) {
                    if (mpLib_8004E97C(x0_f27, y0_f26, x1_f25, y1_f24, f1, f2,
                                       f3, f4, &int_x_sp3C, &int_y_sp38))
                    {
                        dx2 = SQ(int_x_sp3C - f29);
                        dy2 = SQ(int_y_sp38 - f28);
                        dist2 = dx2 + dy2;
                        if ((x_f23 * (int_x_sp3C - f29)) +
                                (y_f22 * (int_y_sp38 - f28)) <
                            0.0F)
                        {
                            dist2 = -dist2;
                        }
                        if (min_f30 > dist2) {
                            min_f30 = dist2;

                            if (vec_out != NULL) {
                                vec_out->x = int_x_sp3C;
                                vec_out->y = int_y_sp38;
                                vec_out->z = 0.0F;
                            }

                            if (line_id_out != NULL) {
                                *line_id_out = r26 - groundCollLine;
                            }

                            if (flags_out != NULL) {
                                *flags_out = r26->x0->flags;
                            }

                            if (normal_out != NULL) {
                                normal_out->x = -(y1_f24 - y0_f26);
                                normal_out->y = x1_f25 - x0_f27;
                                normal_out->z = 0.0F;
                                PSVECNormalize(normal_out, normal_out);
                            }

                            r27 = true;
                        }
                    }
                } else {
                    if (f1 <= f3 &&
                        mpLib_80050068(&int_x_sp3C, &int_y_sp38, x0_f27,
                                       y0_f26, y1_f24, f1, f2, f3, f4))
                    {
                        dx2 = SQ(int_x_sp3C - f29);
                        dy2 = SQ(int_y_sp38 - f28);
                        dist2 = dx2 + dy2;
                        if ((x_f23 * (int_x_sp3C - f29)) +
                                (y_f22 * (int_y_sp38 - f28)) <
                            0.0F)
                        {
                            dist2 = -dist2;
                        }
                        if (min_f30 > dist2) {
                            min_f30 = dist2;

                            if (vec_out != NULL) {
                                vec_out->x = int_x_sp3C;
                                vec_out->y = int_y_sp38;
                                vec_out->z = 0.0F;
                            }

                            if (line_id_out != NULL) {
                                *line_id_out = r26 - groundCollLine;
                            }

                            if (flags_out != NULL) {
                                *flags_out = r26->x0->flags;
                            }

                            if (normal_out != NULL) {
                                normal_out->x = -1.0F;
                                normal_out->y = 0.0F;
                                normal_out->z = 0.0F;
                            }

                            r27 = true;
                        }
                    }
                }
            }
        }

        if (r24 != 0) {
            r25 = r24;
            r28 = 0;
            r24 = 0;
            r26 = &groundCollLine[joint->coll_info->dynamic_start];
            goto block_8;
        }
    }

    if (!r3) {
        mpLib_80058AA0();
    }

    return r27;
}

bool mpLib_800509B8_RightWall(float ax, float ay, float bx, float by,
                              Vec3* vec_out, int* line_id_out, u32* flags_out,
                              Vec3* normal_out, int joint_id0, int joint_id1)
{
    float min;
    CollJoint* joint;
    int r28;
    int result;
    CollLine* p26;
    int r25;
    int r24;
    CollInfo* coll_info;
    int r3;
    PAD_STACK(4);

    result = false;
    min = F32_MAX;
    r3 = mpLib_800588C8();

    if (!r3) {
        mpLib_80058970(ax, ay, bx, by);
    }

    for (joint = mpLib_804D64C4; joint != NULL; joint = joint->next) {
        if (joint->flags & 0x1000) {
            continue;
        }

        if (joint_id0 == (joint - groundCollJoint) ||
            !(joint_id1 == -1 || joint_id1 == (joint - groundCollJoint)))
        {
            continue;
        }

        coll_info = joint->coll_info;

        r25 = coll_info->right_wall_count;
        r24 = coll_info->dynamic_count;
        p26 = &groundCollLine[coll_info->right_wall_start];

        for (r28 = 0; r28 < r25; r28++, p26++) {
        block_8:
            if (p26->flags & CollLine_RightWall && p26->flags & 0x10000 &&
                !(p26->flags & LINE_FLAG_EMPTY))
            {
                mpLib_Line* line = p26->x0;
                CollVtx* v0 = &groundCollVtx[line->v0_idx];
                CollVtx* v1 = &groundCollVtx[line->v1_idx];
                float x0 = v0->pos.x;
                float y0 = v0->pos.y;
                float x1 = v1->pos.x;
                float y1 = v1->pos.y;
                float dx2;
                float dy2;
                float dist2;
                float x;
                float y;
                if (ABS(x0 - x1) > 0.0001) {
                    if (mpLib_8004E97C(x0, y0, x1, y1, ax, ay, bx, by, &x, &y))
                    {
                        dx2 = SQ(x - ax);
                        dy2 = SQ(y - ay);
                        dist2 = dx2 + dy2;
                        if (min > dist2) {
                            min = dist2;
                            if (vec_out != NULL) {
                                vec_out->x = x;
                                vec_out->y = y;
                                vec_out->z = 0.0F;
                            }
                            if (line_id_out != NULL) {
                                *line_id_out = p26 - groundCollLine;
                            }
                            if (flags_out != NULL) {
                                *flags_out = p26->x0->flags;
                            }
                            if (normal_out != NULL) {
                                normal_out->x = -(y1 - y0);
                                normal_out->y = x1 - x0;
                                normal_out->z = 0.0F;
                                PSVECNormalize(normal_out, normal_out);
                            }
                            result = true;
                        }
                    }
                } else {
                    if (ax >= bx &&
                        mpLib_80050068(&x, &y, x0, y0, y1, ax, ay, bx, by))
                    {
                        dx2 = SQ(x - ax);
                        dy2 = SQ(y - ay);
                        dist2 = dx2 + dy2;
                        if (min > dist2) {
                            min = dist2;
                            if (vec_out != NULL) {
                                vec_out->x = x;
                                vec_out->y = y;
                                vec_out->z = 0.0F;
                            }
                            if (line_id_out != NULL) {
                                *line_id_out = p26 - groundCollLine;
                            }
                            if (flags_out != NULL) {
                                *flags_out = p26->x0->flags;
                            }
                            if (normal_out != NULL) {
                                normal_out->x = 1.0F;
                                normal_out->y = 0.0F;
                                normal_out->z = 0.0F;
                            }
                            result = true;
                        }
                    }
                }
            }
        }

        if (r24 != 0) {
            r25 = r24;
            r28 = 0;
            r24 = 0;
            p26 = &groundCollLine[joint->coll_info->dynamic_start];
            goto block_8;
        }
    }
    if (!r3) {
        mpLib_80058AA0();
    }

    return result;
}

bool mpLib_80050D68_RightWall(Vec3* vec_out, int* line_id_out, u32* flags_out,
                              Vec3* normal_out, int joint_id0, int joint_id1,
                              float f1, float f2, float f3, float f4)
{
    float min_f30;
    float f29 = f1;
    float f28 = f2;
    CollJoint* joint;
    int r28;
    int r27;
    CollLine* r26;
    int r25;
    int r24;
    CollInfo* ci_r4;
    int r3;
    u8 _[8];

    r27 = false;
    min_f30 = F32_MAX;

    r3 = mpLib_800588C8();
    if (!r3) {
        mpLib_80058970(f1, f2, f3, f4);
    }

    for (joint = mpLib_804D64C4; joint != NULL; joint = joint->next) {
        if (joint->flags & 0x1000) {
            continue;
        }

        if (joint_id0 == (joint - groundCollJoint) ||
            !(joint_id1 == -1 || joint_id1 == (joint - groundCollJoint)))
        {
            continue;
        }

        ci_r4 = joint->coll_info;
        r25 = ci_r4->right_wall_count;
        r24 = ci_r4->dynamic_count;
        r26 = &groundCollLine[ci_r4->right_wall_start];
        for (r28 = 0; r28 < r25; r28++, r26++) {
        block_8:
            if (r26->flags & CollLine_RightWall && r26->flags & 0x10000 &&
                !(r26->flags & LINE_FLAG_EMPTY))
            {
                mpLib_Line* line_r3 = r26->x0;
                CollVtx* v0_r5 = &groundCollVtx[line_r3->v0_idx];
                CollVtx* v1_r6 = &groundCollVtx[line_r3->v1_idx];
                float x0_f27 = v0_r5->pos.x;
                float y0_f26 = v0_r5->pos.y;
                float x1_f25 = v1_r6->pos.x;
                float y1_f24 = v1_r6->pos.y;
                float x_f23;
                float y_f22;
                float dx2;
                float dy2;
                float dist2;
                float int_x_sp3C;
                float int_y_sp38;

                if (joint->flags & 0x700) {
                    mpRemap2d(&f1, &f2, v0_r5->x10, v0_r5->x14, v1_r6->x10,
                              v1_r6->x14, x0_f27, y0_f26, x1_f25, y1_f24, f29,
                              f28);
                } else {
                    f1 = f29;
                    f2 = f28;
                }

                x_f23 = f3 - f1;
                y_f22 = f4 - f2;
                if (ABS(x0_f27 - x1_f25) > 0.0001) {
                    if (mpLib_8004E97C(x0_f27, y0_f26, x1_f25, y1_f24, f1, f2,
                                       f3, f4, &int_x_sp3C, &int_y_sp38))
                    {
                        dx2 = SQ(int_x_sp3C - f29);
                        dy2 = SQ(int_y_sp38 - f28);
                        dist2 = dx2 + dy2;
                        if ((x_f23 * (int_x_sp3C - f29)) +
                                (y_f22 * (int_y_sp38 - f28)) <
                            0.0F)
                        {
                            dist2 = -dist2;
                        }
                        if (min_f30 > dist2) {
                            min_f30 = dist2;

                            if (vec_out != NULL) {
                                vec_out->x = int_x_sp3C;
                                vec_out->y = int_y_sp38;
                                vec_out->z = 0.0F;
                            }

                            if (line_id_out != NULL) {
                                *line_id_out = r26 - groundCollLine;
                            }

                            if (flags_out != NULL) {
                                *flags_out = r26->x0->flags;
                            }

                            if (normal_out != NULL) {
                                normal_out->x = -(y1_f24 - y0_f26);
                                normal_out->y = x1_f25 - x0_f27;
                                normal_out->z = 0.0F;
                                PSVECNormalize(normal_out, normal_out);
                            }

                            r27 = true;
                        }
                    }
                } else {
                    if (f1 <= f3 &&
                        mpLib_80050068(&int_x_sp3C, &int_y_sp38, x0_f27,
                                       y0_f26, y1_f24, f1, f2, f3, f4))
                    {
                        dx2 = SQ(int_x_sp3C - f29);
                        dy2 = SQ(int_y_sp38 - f28);
                        dist2 = dx2 + dy2;
                        if ((x_f23 * (int_x_sp3C - f29)) +
                                (y_f22 * (int_y_sp38 - f28)) <
                            0.0F)
                        {
                            dist2 = -dist2;
                        }
                        if (min_f30 > dist2) {
                            min_f30 = dist2;

                            if (vec_out != NULL) {
                                vec_out->x = int_x_sp3C;
                                vec_out->y = int_y_sp38;
                                vec_out->z = 0.0F;
                            }

                            if (line_id_out != NULL) {
                                *line_id_out = r26 - groundCollLine;
                            }

                            if (flags_out != NULL) {
                                *flags_out = r26->x0->flags;
                            }

                            if (normal_out != NULL) {
                                normal_out->x = 1.0F;
                                normal_out->y = 0.0F;
                                normal_out->z = 0.0F;
                            }

                            r27 = true;
                        }
                    }
                }
            }
        }

        if (r24 != 0) {
            r25 = r24;
            r28 = 0;
            r24 = 0;
            r26 = &groundCollLine[joint->coll_info->dynamic_start];
            goto block_8;
        }
    }

    if (!r3) {
        mpLib_80058AA0();
    }

    return r27;
}

bool mpLib_800511A4_RightWall(float ax, float ay, float bx, float by, float cx,
                              float cy, float dx, float dy, int* line_id_out,
                              int joint_id0, int joint_id1)
{
    float min_dist2;
    CollJoint* joint;
    int i;
    int result;
    int r3;
    PAD_STACK(8);

    result = false;
    min_dist2 = F32_MAX;
    r3 = mpLib_800588C8();

    if (!r3) {
        mpLib_800589D0(ax, ay, bx, by, cx, cy, dx, dy);
    }

    for (joint = mpLib_804D64C4; joint != NULL; joint = joint->next) {
        CollLine* line;
        int count;
        int dynamic_count;
        CollInfo* coll_info;

        if (joint->flags & 0x1000) {
            continue;
        }

        if (joint_id0 == (joint - groundCollJoint) ||
            !(joint_id1 == -1 || joint_id1 == (joint - groundCollJoint)))
        {
            continue;
        }

        coll_info = joint->coll_info;

        count = coll_info->right_wall_count;
        dynamic_count = coll_info->dynamic_count;
        line = &groundCollLine[coll_info->right_wall_start];
        for (i = 0; i < count; i++, line++) {
        block_8:
            if (line->flags & CollLine_RightWall && line->flags & 0x10000 &&
                !(line->flags & LINE_FLAG_EMPTY))
            {
                CollVtx* vtx;
                float int_x;
                float int_y;
                float x;
                float y;
                float x0;
                float y0;
                float x1;
                float y1;
                float vdx;
                float vdy;
                float dist2;

                {
                    vtx = &groundCollVtx[line->x0->v0_idx];
                    x0 = vtx->pos.x;
                    y0 = vtx->pos.y;
                    x1 = vtx->x10;
                    y1 = vtx->x14;
                    mpRemap2d(&x, &y, ax, ay, bx, by, cx, cy, dx, dy, x1, y1);

                    vdx = x0 - x;
                    vdy = y0 - y;

                    if (SQ(vdx) + SQ(vdy) > 0.001F) {
                        if (mpLib_8004E97C(cx, cy, dx, dy, x, y, x0, y0,
                                           &int_x, &int_y))
                        {
                            dist2 = SQ(int_x - x1) + SQ(int_y - y1);
                            if ((vdx * (int_x - x1)) + (vdy * (int_y - y1)) <
                                0.0F)
                            {
                                dist2 = -dist2;
                            }
                            if (min_dist2 > dist2) {
                                min_dist2 = dist2;
                                if (line_id_out != NULL) {
                                    *line_id_out = line - groundCollLine;
                                }
                                result = true;
                            }
                        }
                    }
                }

                {
                    vtx = &groundCollVtx[line->x0->v1_idx];
                    x0 = vtx->pos.x;
                    y0 = vtx->pos.y;
                    x1 = vtx->x10;
                    y1 = vtx->x14;
                    mpRemap2d(&x, &y, ax, ay, bx, by, cx, cy, dx, dy, x1, y1);

                    vdx = x0 - x;
                    vdy = y0 - y;

                    if (SQ(vdx) + SQ(vdy) > 0.001F) {
                        if (mpLib_8004E97C(cx, cy, dx, dy, x, y, x0, y0,
                                           &int_x, &int_y))
                        {
                            dist2 = SQ(int_x - x1) + SQ(int_y - y1);
                            if ((vdx * (int_x - x1)) + (vdy * (int_y - y1)) <
                                0.0F)
                            {
                                dist2 = -dist2;
                            }
                            if (min_dist2 > dist2) {
                                min_dist2 = dist2;
                                if (line_id_out != NULL) {
                                    *line_id_out = line - groundCollLine;
                                }
                                result = true;
                            }
                        }
                    }
                }
            }
        }

        if (dynamic_count != 0) {
            count = dynamic_count;
            i = 0;
            dynamic_count = 0;
            line = &groundCollLine[joint->coll_info->dynamic_start];
            goto block_8;
        }
    }

    if (!r3) {
        mpLib_80058AA0();
    }

    return result;
}

bool mpLib_800515A0_LeftWall(float ax, float ay, float bx, float by, float cx,
                             float cy, float dx, float dy, int* line_id_out,
                             int joint_id0, int joint_id1)
{
    float min_dist2;
    CollJoint* joint;
    int i;
    int result;
    int r3;
    PAD_STACK(8);

    result = false;
    min_dist2 = F32_MAX;
    r3 = mpLib_800588C8();

    if (!r3) {
        mpLib_800589D0(ax, ay, bx, by, cx, cy, dx, dy);
    }

    for (joint = mpLib_804D64C4; joint != NULL; joint = joint->next) {
        CollLine* line;
        int count;
        int dynamic_count;
        CollInfo* coll_info;

        if (joint->flags & 0x1000) {
            continue;
        }

        if (joint_id0 == (joint - groundCollJoint) ||
            !(joint_id1 == -1 || joint_id1 == (joint - groundCollJoint)))
        {
            continue;
        }

        coll_info = joint->coll_info;

        count = coll_info->left_wall_count;
        dynamic_count = coll_info->dynamic_count;
        line = &groundCollLine[coll_info->left_wall_start];
        for (i = 0; i < count; i++, line++) {
        block_8:
            if (line->flags & CollLine_LeftWall && line->flags & 0x10000 &&
                !(line->flags & LINE_FLAG_EMPTY))
            {
                CollVtx* vtx;
                float int_x;
                float int_y;
                float x;
                float y;
                float x0;
                float y0;
                float x1;
                float y1;
                float vdx;
                float vdy;
                float dist2;

                {
                    vtx = &groundCollVtx[line->x0->v0_idx];
                    x0 = vtx->pos.x;
                    y0 = vtx->pos.y;
                    x1 = vtx->x10;
                    y1 = vtx->x14;
                    mpRemap2d(&x, &y, ax, ay, bx, by, cx, cy, dx, dy, x1, y1);

                    vdx = x0 - x;
                    vdy = y0 - y;

                    if (SQ(vdx) + SQ(vdy) > 0.001F) {
                        if (mpLib_8004E97C(cx, cy, dx, dy, x, y, x0, y0,
                                           &int_x, &int_y))
                        {
                            dist2 = SQ(int_x - x1) + SQ(int_y - y1);
                            if ((vdx * (int_x - x1)) + (vdy * (int_y - y1)) <
                                0.0F)
                            {
                                dist2 = -dist2;
                            }
                            if (min_dist2 > dist2) {
                                min_dist2 = dist2;
                                if (line_id_out != NULL) {
                                    *line_id_out = line - groundCollLine;
                                }
                                result = true;
                            }
                        }
                    }
                }

                {
                    vtx = &groundCollVtx[line->x0->v1_idx];
                    x0 = vtx->pos.x;
                    y0 = vtx->pos.y;
                    x1 = vtx->x10;
                    y1 = vtx->x14;
                    mpRemap2d(&x, &y, ax, ay, bx, by, cx, cy, dx, dy, x1, y1);

                    vdx = x0 - x;
                    vdy = y0 - y;

                    if (SQ(vdx) + SQ(vdy) > 0.001F) {
                        if (mpLib_8004E97C(cx, cy, dx, dy, x, y, x0, y0,
                                           &int_x, &int_y))
                        {
                            dist2 = SQ(int_x - x1) + SQ(int_y - y1);
                            if ((vdx * (int_x - x1)) + (vdy * (int_y - y1)) <
                                0.0F)
                            {
                                dist2 = -dist2;
                            }
                            if (min_dist2 > dist2) {
                                min_dist2 = dist2;
                                if (line_id_out != NULL) {
                                    *line_id_out = line - groundCollLine;
                                }
                                result = true;
                            }
                        }
                    }
                }
            }
        }

        if (dynamic_count != 0) {
            count = dynamic_count;
            i = 0;
            dynamic_count = 0;
            line = &groundCollLine[joint->coll_info->dynamic_start];
            goto block_8;
        }
    }

    if (!r3) {
        mpLib_80058AA0();
    }

    return result;
}

int mpLib_8005199C_Floor(Vec3* vec, int arg1, int arg2)
{
    int line_id_r30 = -1;
    float x_f31 = vec->x;
    float y_f30 = vec->y;
    bool r3_1 = mpLib_800588C8();
    CollJoint* r3;
    PAD_STACK(16);

    if (!r3_1) {
        mpLib_80058970(x_f31, y_f30, x_f31, y_f30 - 30000.0F);
    }

    for (r3 = mpLib_804D64C4; r3 != NULL; r3 = r3->next) {
        if (r3->flags & 0x1000 || arg1 == r3 - groundCollJoint) {
            continue;
        }

        if (arg2 == -1 || arg2 == r3 - groundCollJoint) {
            CollInfo* r9 = r3->coll_info;
            int r10 = 0;
            CollLine* line_r11 = &groundCollLine[r9->floor_start];
            int r12 = r9->floor_count;
            int r27;
            r27 = r9->dynamic_count;
            goto loop_condition;
            while (true) {
                if ((line_r11->flags & CollLine_Floor) &&
                    (line_r11->flags & 0x10000) &&
                    !(line_r11->flags & LINE_FLAG_EMPTY))
                {
                    CollVtx* v1_r4 = &groundCollVtx[line_r11->x0->v1_idx];
                    CollVtx* v0_r5 = &groundCollVtx[line_r11->x0->v0_idx];
                    float x0_f4 = v0_r5->pos.x;
                    float x1_f0 = v1_r4->pos.x;
                    float y0_f6 = v0_r5->pos.y;
                    float y1_f1 = v1_r4->pos.y;

                    if (x_f31 >= v0_r5->pos.x && x_f31 <= x1_f0) {
                        if (y_f30 >= y0_f6 && y_f30 >= y1_f1) {
                            line_id_r30 = (line_r11 - groundCollLine);
                            goto end;
                        }
                        if (ABS(x1_f0 - v0_r5->pos.x) > 0.0001 &&
                            y_f30 >= (y1_f1 - y0_f6) / (x1_f0 - v0_r5->pos.x) *
                                             (x_f31 - v0_r5->pos.x) +
                                         y0_f6)
                        {
                            line_id_r30 = (line_r11 - groundCollLine);
                            goto end;
                        }
                    }
                }

                r10 += 1;
                line_r11 += 1;

            loop_condition:
                if (r10 >= r12) {
                    if (r27 != 0) {
                        r12 = r27;
                        r10 = 0;
                        line_r11 = &groundCollLine[r9->dynamic_start];
                        r27 = 0;
                    } else {
                        break;
                    }
                }
            }
        }
    }

end:
    if (!r3_1) {
        mpLib_80058AA0();
    }

    return line_id_r30;
}

int mpLib_80051BA8_Floor(Vec3* out_vec, int line_id, int joint_id0,
                         int joint_id1, int dir, float left, float bottom,
                         float right, float top)
{
    float min;
    float out_x;
    float out_y;

    int ledge_id = -1;

    bool temp;
    int new_id;
    CollJoint* joint;

    if (dir > 0) {
        min = +F32_MAX;
    } else if (dir < 0) {
        min = -F32_MAX;
    } else {
        HSD_ASSERT(3821, 0);
    }

    temp = mpLib_800588C8();
    if (!temp) {
        mpLib_800588D0(left, bottom, right, top);
    }

    for (joint = mpLib_804D64C4; joint != NULL; joint = joint->next) {
        if (joint->flags & 0x1000) {
            continue;
        }

        if (joint_id0 == joint - groundCollJoint) {
            continue;
        }

        if (joint_id1 == -1 || joint_id1 == joint - groundCollJoint) {
            int i;
            CollLine* line = &groundCollLine[joint->coll_info->floor_start];
            int count = joint->coll_info->floor_count;
            int dynamic_cout = joint->coll_info->dynamic_count;
            for (i = 0; i < count; i++, line++) {
            reset:
                new_id = line - groundCollLine;
                if (line_id == new_id) {
                    continue;
                }

                if (line->flags & CollLine_Floor && line->flags & 0x10000 &&
                    !(line->flags & LINE_FLAG_EMPTY))
                {
                    mpLib_Line* inner = line->x0;
                    if (inner->flags & LINE_FLAG_LEDGE) {
                        float x0 = groundCollVtx[inner->v0_idx].pos.x;
                        float y0 = groundCollVtx[inner->v0_idx].pos.y;
                        float x1 = groundCollVtx[inner->v1_idx].pos.x;
                        float y1 = groundCollVtx[inner->v1_idx].pos.y;
                        float line_left;
                        float line_bottom;
                        float line_right;
                        float line_top;
                        float dist_h;

                        if (x0 > x1) {
                            line_right = x0;
                            line_left = x1;
                        } else {
                            line_left = x0;
                            line_right = x1;
                        }

                        if (y0 > y1) {
                            line_top = y0;
                            line_bottom = y1;
                        } else {
                            line_bottom = y0;
                            line_top = y1;
                        }
                        // distance between midpoints of two right/left
                        // pairs
                        dist_h =
                            ABS((line_right + line_left) - (right + left));
                        if (dist_h < (line_right - line_left) + (right - left))
                        {
                            float dist_v =
                                ABS((line_top + line_bottom) - (top + bottom));
                            if (dist_v <
                                (line_top - line_bottom) + (top - bottom))
                            {
                                // we interesect in both axes
                                if (dir > 0) {
                                    if (min > x0) {
                                        min = x0;
                                        ledge_id = new_id;
                                        if (out_vec != NULL) {
                                            out_x = x0;
                                            out_y = y0;
                                        }
                                    }
                                } else if (dir < 0) {
                                    if (min < x1) {
                                        min = x1;
                                        ledge_id = new_id;
                                        if (out_vec != NULL) {
                                            out_x = x1;
                                            out_y = y1;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }

            if (dynamic_cout != 0) {
                count = dynamic_cout;
                i = 0;
                line = &groundCollLine[joint->coll_info->dynamic_start];
                dynamic_cout = 0;
                goto reset;
            }
        }
    }

    if (!temp) {
        mpLib_80058AA0();
    }

    if (ledge_id != -1 && out_vec != NULL) {
        if (out_x > right) {
            out_x = right;
        } else if (out_x < left) {
            out_x = left;
        }
        out_vec->x = out_x;
        out_vec->y = out_y;
        out_vec->z = 0.0F;
    }

    return ledge_id;
}

bool mpLib_80051EC8(Vec3* pos_out, int* line_id_out, u32* flags_out,
                    Vec3* normal_out, u32 arg4, int joint_id0, int joint_id1,
                    float x1, float y1, float x2, float y2)
{
    f32 dx;
    f32 dy;

    f32 min_sq_dist_f31;
    bool temp_r3;

    s32 var_r30;
    s32 var_r29;

    Vec3 pos_sp68;
    Vec3 normal_sp5C;
    Vec3 pos_sp50;
    Vec3 normal_sp44;
    int line_id_sp40;
    u32 flags_sp3C;

    min_sq_dist_f31 = F32_MAX;
    temp_r3 = mpLib_800588C8();
    if (!temp_r3) {
        mpLib_80058970(x1, y1, x2, y2);
    }
    if (arg4 & 0x10) {
        if (arg4 & 1) {
            if (mpLib_8004F400_Floor(x1, y1, x2, y2, 0.0F, &pos_sp68,
                                     &line_id_sp40, &flags_sp3C, &normal_sp5C,
                                     -1, joint_id0, joint_id1, NULL, NULL))
            {
                dx = SQ(pos_sp68.x - x1);
                dy = SQ(pos_sp68.y - y1);
                pos_sp50 = pos_sp68;
                normal_sp44 = normal_sp5C;
                min_sq_dist_f31 = dx + dy;
                var_r30 = line_id_sp40;
                var_r29 = flags_sp3C;
            }
        }
        if ((arg4 & 2) &&
            (mpLib_8004FC2C_Ceiling(x1, y1, x2, y2, &pos_sp68, &line_id_sp40,
                                    &flags_sp3C, &normal_sp5C, joint_id0,
                                    joint_id1)))
        {
            dx = SQ(pos_sp68.x - x1);
            dy = SQ(pos_sp68.y - y1);
            if (min_sq_dist_f31 > dx + dy) {
                min_sq_dist_f31 = dx + dy;
                pos_sp50 = pos_sp68;
                normal_sp44 = normal_sp5C;
                var_r30 = line_id_sp40;
                var_r29 = flags_sp3C;
            }
        }
        if ((arg4 & 4) &&
            (mpLib_8005057C_LeftWall(&pos_sp68, &line_id_sp40, &flags_sp3C,
                                     &normal_sp5C, joint_id0, joint_id1, x1,
                                     y1, x2, y2)))
        {
            dx = SQ(pos_sp68.x - x1);
            dy = SQ(pos_sp68.y - y1);
            if (min_sq_dist_f31 > dx + dy) {
                min_sq_dist_f31 = dx + dy;
                pos_sp50 = pos_sp68;
                normal_sp44 = normal_sp5C;
                var_r30 = line_id_sp40;
                var_r29 = flags_sp3C;
            }
        }
        if ((arg4 & 8) &&
            (mpLib_80050D68_RightWall(&pos_sp68, &line_id_sp40, &flags_sp3C,
                                      &normal_sp5C, joint_id0, joint_id1, x1,
                                      y1, x2, y2)))
        {
            dx = SQ(pos_sp68.x - x1);
            dy = SQ(pos_sp68.y - y1);
            if (min_sq_dist_f31 > dx + dy) {
                min_sq_dist_f31 = dx + dy;
                pos_sp50 = pos_sp68;
                normal_sp44 = normal_sp5C;
                var_r30 = line_id_sp40;
                var_r29 = flags_sp3C;
            }
        }
    } else {
        if (arg4 & 1) {
            if (mpLib_8004F008_Floor(x1, y1, x2, y2, 0.0F, &pos_sp68,
                                     &line_id_sp40, &flags_sp3C, &normal_sp5C,
                                     -1, joint_id0, joint_id1, NULL, NULL))
            {
                dx = SQ(pos_sp68.x - x1);
                dy = SQ(pos_sp68.y - y1);
                pos_sp50 = pos_sp68;
                normal_sp44 = normal_sp5C;
                min_sq_dist_f31 = dx + dy;
                var_r30 = line_id_sp40;
                var_r29 = flags_sp3C;
            }
        }
        if ((arg4 & 2) &&
            (mpLib_8004F8A4_Ceiling(x1, y1, x2, y2, &pos_sp68, &line_id_sp40,
                                    &flags_sp3C, &normal_sp5C, joint_id0,
                                    joint_id1)))
        {
            dx = SQ(pos_sp68.x - x1);
            dy = SQ(pos_sp68.y - y1);
            if (min_sq_dist_f31 > dx + dy) {
                min_sq_dist_f31 = dx + dy;
                pos_sp50 = pos_sp68;
                normal_sp44 = normal_sp5C;
                var_r30 = line_id_sp40;
                var_r29 = flags_sp3C;
            }
        }
        if ((arg4 & 4) &&
            (mpLib_800501CC_LeftWall(x1, y1, x2, y2, &pos_sp68, &line_id_sp40,
                                     &flags_sp3C, &normal_sp5C, joint_id0,
                                     joint_id1)))
        {
            dx = SQ(pos_sp68.x - x1);
            dy = SQ(pos_sp68.y - y1);
            if (min_sq_dist_f31 > dx + dy) {
                min_sq_dist_f31 = dx + dy;
                pos_sp50 = pos_sp68;
                normal_sp44 = normal_sp5C;
                var_r30 = line_id_sp40;
                var_r29 = flags_sp3C;
            }
        }
        if ((arg4 & 8) &&
            (mpLib_800509B8_RightWall(x1, y1, x2, y2, &pos_sp68, &line_id_sp40,
                                      &flags_sp3C, &normal_sp5C, joint_id0,
                                      joint_id1)))
        {
            dx = SQ(pos_sp68.x - x1);
            dy = SQ(pos_sp68.y - y1);
            if (min_sq_dist_f31 > dx + dy) {
                min_sq_dist_f31 = dx + dy;
                pos_sp50 = pos_sp68;
                normal_sp44 = normal_sp5C;
                var_r30 = line_id_sp40;
                var_r29 = flags_sp3C;
            }
        }
    }
    if (!temp_r3) {
        mpLib_80058AA0();
    }
    if (min_sq_dist_f31 < F32_MAX) {
        if (pos_out != NULL) {
            *pos_out = pos_sp50;
        }
        if (line_id_out != NULL) {
            *line_id_out = var_r30;
        }
        if (flags_out != NULL) {
            *flags_out = var_r29;
        }
        if (normal_out != NULL) {
            *normal_out = normal_sp44;
        }
        return true;
    }
    return false;
}

bool mpLib_800524DC(Vec3* pos_out, int* line_id_out, u32* flags_out,
                    Vec3* normal_out, int joint_id0, int joint_id1, float x0,
                    float y0, float x1, float y1)
{
    return mpLib_80051EC8(pos_out, line_id_out, flags_out, normal_out, 0x1F,
                          joint_id0, joint_id1, x0, y0, x1, y1);
}

bool mpLib_80052508(Vec3* pos_out, int* line_id_out, u32* flags_out,
                    Vec3* normal_out, int joint_id0, int joint_id1, float x0,
                    float y0, float x1, float y1)
{
    return mpLib_80051EC8(pos_out, line_id_out, flags_out, normal_out, 0xF,
                          joint_id0, joint_id1, x0, y0, x1, y1);
}

int mpLib_80052534_Floor(int line_id)
{
    int new_id;
    bool valid_id;

    LINEID_CHECK(4139, line_id);

    new_id = mpLineGetNext(line_id);
    while (new_id != -1 && new_id != line_id &&
           !(groundCollLine[new_id].flags & CollLine_Floor))
    {
        new_id = mpLineGetNext(new_id);
    }

    valid_id = false;
    if ((new_id != -1) && (new_id != line_id)) {
        valid_id = true;
    }

    if (valid_id) {
        return new_id;
    }

    return -1;
}

int mpLib_80052700_Floor(int line_id)
{
    int new_id;
    bool valid_id;
    LINEID_CHECK(4148, line_id);
    new_id = mpLineGetPrev(line_id);
    while (new_id != -1 && new_id != line_id &&
           groundCollLine[new_id].flags & CollLine_Floor)
    {
        new_id = mpLineGetPrev(new_id);
    }

    valid_id = false;
    if ((new_id != -1) && (new_id != line_id)) {
        valid_id = true;
    }

    if (valid_id) {
        return new_id;
    }
    return -1;
}

int mpLib_800528CC_Ceiling(int line_id)
{
    int new_id;
    bool valid_id;
    LINEID_CHECK(4157, line_id);
    new_id = mpLineGetPrev(line_id);
    while (new_id != -1 && new_id != line_id &&
           groundCollLine[new_id].flags & CollLine_Ceiling)
    {
        new_id = mpLineGetPrev(new_id);
    }

    valid_id = false;
    if (new_id != -1 && new_id != line_id) {
        valid_id = true;
    }

    if (valid_id) {
        return new_id;
    }

    return -1;
}

int mpLib_80052A98_Ceiling(int line_id)
{
    int new_id;
    bool valid_id;
    LINEID_CHECK(4166, line_id);
    new_id = mpLineGetNext(line_id);
    while (new_id != -1 && new_id != line_id &&
           groundCollLine[new_id].flags & CollLine_Ceiling)
    {
        new_id = mpLineGetNext(new_id);
    }
    valid_id = false;
    if (new_id != -1 && new_id != line_id) {
        valid_id = true;
    }
    if (valid_id) {
        return new_id;
    }
    return -1;
}

int mpLib_80052C64_LeftWall(int line_id)
{
    int new_id;
    bool valid_id;
    LINEID_CHECK(4175, line_id);
    new_id = mpLineGetNext(line_id);
    while (new_id != -1 && new_id != line_id &&
           groundCollLine[new_id].flags & CollLine_LeftWall)
    {
        new_id = mpLineGetNext(new_id);
    }
    valid_id = false;
    if (new_id != -1 && new_id != line_id) {
        valid_id = true;
    }
    if (valid_id) {
        return new_id;
    }
    return -1;
}

int mpLib_80052E30_LeftWall(int line_id)
{
    int new_id;
    bool valid_id;
    LINEID_CHECK(4184, line_id);
    new_id = mpLineGetPrev(line_id);
    while (new_id != -1 && new_id != line_id &&
           groundCollLine[new_id].flags & CollLine_LeftWall)
    {
        new_id = mpLineGetPrev(new_id);
    }
    valid_id = false;
    if (new_id != -1 && new_id != line_id) {
        valid_id = true;
    }
    if (valid_id) {
        return new_id;
    }
    return -1;
}

int mpLib_80052FFC_RightWall(int line_id)
{
    int new_id;
    bool valid_id;
    LINEID_CHECK(4193, line_id);
    new_id = mpLineGetPrev(line_id);
    while (new_id != -1 && new_id != line_id &&
           groundCollLine[new_id].flags & CollLine_RightWall)
    {
        new_id = mpLineGetPrev(new_id);
    }
    valid_id = false;
    if (new_id != -1 && new_id != line_id) {
        valid_id = true;
    }
    if (valid_id) {
        return new_id;
    }
    return -1;
}

int mpLib_800531C8_RightWall(int line_id)
{
    int new_id;
    bool valid_id;
    LINEID_CHECK(4202, line_id);
    new_id = mpLineGetNext(line_id);
    while (new_id != -1 && new_id != line_id &&
           groundCollLine[new_id].flags & CollLine_RightWall)
    {
        new_id = mpLineGetNext(new_id);
    }
    valid_id = false;
    if (new_id != -1 && new_id != line_id) {
        valid_id = true;
    }
    if (valid_id) {
        return new_id;
    }
    return -1;
}

int mpLib_80053394_Floor(int line_id)
{
    int new_id;
    LINEID_CHECK(4252, line_id);
    new_id = groundCollLine[line_id].x0->next_id0;
    while (new_id != -1 && groundCollLine[new_id].flags & CollLine_Floor) {
        new_id = groundCollLine[new_id].x0->next_id0;
    }
    if (new_id != -1) {
        return new_id;
    }
    return -1;
}

int mpLib_80053448_Floor(int line_id)
{
    int new_id;
    LINEID_CHECK(4261, line_id);
    new_id = groundCollLine[line_id].x0->prev_id0;
    while (new_id != -1 && groundCollLine[new_id].flags & CollLine_Floor) {
        new_id = groundCollLine[new_id].x0->prev_id0;
    }
    if (new_id != -1) {
        return new_id;
    }
    return -1;
}

int mpLib_800534FC_Floor(int line_id)
{
    int new_id;
    LINEID_CHECK(4272, line_id);
    new_id = mpLineGetNext(line_id);
    while (new_id != -1) {
        if (!(groundCollLine[new_id].flags & CollLine_Floor)) {
            new_id = -1;
        } else if (new_id != groundCollLine[line_id].x0->next_id1) {
            new_id = mpLineGetNext(new_id);
            continue;
        }
        break;
    }
    if (new_id != -1) {
        return new_id;
    }
    return -1;
}

int mpLib_800536CC_Floor(int line_id)
{
    int new_id;
    LINEID_CHECK(4293, line_id);
    new_id = mpLineGetPrev(line_id);
    while (new_id != -1) {
        if (!(groundCollLine[new_id].flags & CollLine_Floor)) {
            new_id = -1;
        } else if (new_id != groundCollLine[line_id].x0->prev_id1) {
            new_id = mpLineGetPrev(new_id);
            continue;
        }
        break;
    }
    if (new_id != -1) {
        return new_id;
    }
    return -1;
}

int mpLib_8005389C_Ceiling(int line_id)
{
    int new_id;
    LINEID_CHECK(4314, line_id);
    new_id = groundCollLine[line_id].x0->prev_id0;
    while (new_id != -1 && (groundCollLine[new_id].flags & CollLine_Ceiling)) {
        new_id = groundCollLine[new_id].x0->prev_id0;
    }
    if (new_id != -1) {
        return new_id;
    }
    return -1;
}

int mpLib_80053950_Ceiling(int line_id)
{
    int new_id;
    LINEID_CHECK(4323, line_id);
    new_id = groundCollLine[line_id].x0->next_id0;
    while (new_id != -1 && (groundCollLine[new_id].flags & CollLine_Ceiling)) {
        new_id = groundCollLine[new_id].x0->next_id0;
    }
    if (new_id != -1) {
        return new_id;
    }
    return -1;
}

int mpLib_80053A04_Ceiling(int line_id)
{
    int new_id;
    LINEID_CHECK(4334, line_id);
    new_id = mpLineGetPrev(line_id);
    while (new_id != -1) {
        if (!(groundCollLine[new_id].flags & CollLine_Ceiling)) {
            new_id = -1;
        } else if (new_id != groundCollLine[line_id].x0->prev_id1) {
            line_id = new_id;
            new_id = mpLineGetPrev(new_id);
            continue;
        }
        break;
    }
    if (new_id != -1) {
        return new_id;
    }
    return -1;
}

int mpLib_80053BD4_Ceiling(int line_id)
{
    int new_id;
    LINEID_CHECK(4355, line_id);
    new_id = mpLineGetNext(line_id);
    while (new_id != -1) {
        if (!(groundCollLine[new_id].flags & CollLine_Ceiling)) {
            new_id = -1;
        } else if (new_id != groundCollLine[line_id].x0->next_id1) {
            line_id = new_id;
            new_id = mpLineGetNext(new_id);
            continue;
        }
        break;
    }
    if (new_id != -1) {
        return new_id;
    }
    return -1;
}

void mpLib_80053DA4_Floor(int line_id, Vec3* pos_out)
{
    int r29 = line_id;
    int r5;
    CollVtx* temp_r3;

    LINEID_CHECK(4428, r29);

    goto skip;
loop:
    r29 = r5;
skip:
    r5 = groundCollLine[r29].x0->next_id0;
    if (r5 != -1 && (groundCollLine[r5].flags & CollLine_Floor)) {
        goto loop;
    }

    LINEID_CHECK(4433, r29);

    temp_r3 = &groundCollVtx[groundCollLine[r29].x0->v1_idx];
    pos_out->x = temp_r3->pos.x;
    pos_out->y = temp_r3->pos.y;
    pos_out->z = 0.0F;
}

void mpLib_80053ECC_Floor(int line_id, Vec* vec)
{
    CollVtx* temp_r3;

    LINEID_CHECK(4448, line_id);

    while (true) {
        int new_id = groundCollLine[line_id].x0->prev_id0;
        if ((new_id != -1) && (groundCollLine[new_id].flags & CollLine_Floor))
        {
            line_id = new_id;
        } else {
            break;
        }
    }

    LINEID_CHECK(4453, line_id);

    temp_r3 = &groundCollVtx[groundCollLine[line_id].x0->v0_idx];
    vec->x = temp_r3->pos.x;
    vec->y = temp_r3->pos.y;
    vec->z = 0.0F;
}

void mpLib_80053FF4(int line_id, Vec3* pos_out)
{
    CollVtx* vtx;
    int new_id;
    u32 flags_r3;

    LINEID_CHECK(4465, line_id);

    new_id = line_id;
    flags_r3 = groundCollLine[line_id].flags & LINE_FLAG_KIND;
    while (true) {
        new_id = mpLineGetNext(new_id);

        if (new_id == -1 ||
            flags_r3 != (groundCollLine[new_id].flags & LINE_FLAG_KIND))
        {
            break;
        }
    }

    vtx = &groundCollVtx[groundCollLine[new_id].x0->v1_idx];
    pos_out->x = vtx->pos.x;
    pos_out->y = vtx->pos.y;
    pos_out->z = 0.0F;
}

void mpLib_80054158(int line_id, Vec3* arg1)
{
    CollVtx* vtx;
    int new_id;
    mpLib_Line* temp_r8;

    LINEID_CHECK(4474, line_id);

    new_id = line_id;
    while (true) {
        temp_r8 = groundCollLine[new_id].x0;
        new_id = mpLineGetPrev(new_id);

        if (new_id == -1 ||
            (groundCollLine[line_id].flags & LINE_FLAG_KIND) !=
                (groundCollLine[new_id].flags & LINE_FLAG_KIND))
        {
            break;
        }
    }

    vtx = &groundCollVtx[temp_r8->v0_idx];
    arg1->x = vtx->pos.x;
    arg1->y = vtx->pos.y;
    arg1->z = 0.0F;
}

void mpLib_800542BC(int line_id, Vec3* out)
{
    CollVtx* temp_r3;
    int new_id;

    LINEID_CHECK(4483, line_id);
    new_id = line_id;
    do {
        new_id = mpLineGetPrev(new_id);
    } while (new_id != -1 &&
             (groundCollLine[line_id].flags & LINE_FLAG_KIND) ==
                 (groundCollLine[new_id].flags & LINE_FLAG_KIND));
    temp_r3 = &groundCollVtx[groundCollLine[new_id].x0->v0_idx];
    out->x = temp_r3->pos.x;
    out->y = temp_r3->pos.y;
    out->z = 0.0F;
}

void mpLib_80054420(int line_id, Vec3* out)
{
    CollVtx* temp_r3;
    int new_id;

    LINEID_CHECK(4492, line_id);
    new_id = line_id;
    do {
        new_id = mpLineGetNext(new_id);
    } while (new_id != -1 &&
             (groundCollLine[line_id].flags & LINE_FLAG_KIND) ==
                 (groundCollLine[new_id].flags & LINE_FLAG_KIND));
    temp_r3 = &groundCollVtx[groundCollLine[new_id].x0->v0_idx];
    out->x = temp_r3->pos.x;
    out->y = temp_r3->pos.y;
    out->z = 0.0F;
}

CollVtx* mpLib_80054584(int line_id, Vec3* out)
{
    CollVtx* v1;
    s32 new_id;

    LINEID_CHECK(4501, line_id);
    new_id = line_id;

    do {
        new_id = mpLineGetNext(new_id);
    } while (new_id != -1 &&
             (groundCollLine[line_id].flags & LINE_FLAG_KIND) !=
                 (groundCollLine[new_id].flags & LINE_FLAG_KIND));
    v1 = &groundCollVtx[groundCollLine[new_id].x0->v1_idx];
    out->x = v1->pos.x;
    out->y = v1->pos.y;
    out->z = 0.0F;
    return v1;
}

void mpLib_800546E8(int line_id, Vec3* out)
{
    int new_id;
    CollVtx* v0;

    LINEID_CHECK(4510, line_id);
    new_id = line_id;
    do {
        new_id = mpLineGetPrev(new_id);
    } while (new_id != -1 &&
             (groundCollLine[line_id].flags & LINE_FLAG_KIND) !=
                 (groundCollLine[new_id].flags & LINE_FLAG_KIND));
    v0 = &groundCollVtx[groundCollLine[new_id].x0->v0_idx];
    out->x = v0->pos.x;
    out->y = v0->pos.y;
    out->z = 0.0F;
}

void mpLib_8005484C(int line_id, Vec3* arg1)
{
    int new_id;
    CollVtx* v0;

    LINEID_CHECK(4519, line_id);
    new_id = line_id;
    do {
        new_id = mpLineGetPrev(new_id);
    } while (new_id != -1 &&
             (groundCollLine[line_id].flags & LINE_FLAG_KIND) !=
                 (groundCollLine[new_id].flags & LINE_FLAG_KIND));
    v0 = &groundCollVtx[groundCollLine[new_id].x0->v0_idx];
    arg1->x = v0->pos.x;
    arg1->y = v0->pos.y;
    arg1->z = 0.0F;
}

void mpLib_800549B0(int line_id, Vec3* arg1)
{
    int new_id;
    CollVtx* v0;

    LINEID_CHECK(4519, line_id);
    new_id = line_id;
    do {
        new_id = mpLineGetPrev(new_id);
    } while (new_id != -1 &&
             (groundCollLine[line_id].flags & LINE_FLAG_KIND) !=
                 (groundCollLine[new_id].flags & LINE_FLAG_KIND));
    v0 = &groundCollVtx[groundCollLine[new_id].x0->v0_idx];
    arg1->x = v0->pos.x;
    arg1->y = v0->pos.y;
    arg1->z = 0.0F;
}

void mpLineGetV1Pos(int line_id, Vec3* pos_out)
{
    CollVtx* v1;

    LINEID_CHECK(4540, line_id);
    v1 = &groundCollVtx[groundCollLine[line_id].x0->v1_idx];
    pos_out->x = v1->pos.x;
    pos_out->y = v1->pos.y;
    pos_out->z = 0.0F;
}

void mpLineGetV0Pos(int line_id, Vec3* pos_out)
{
    CollVtx* v0;

    LINEID_CHECK(4555, line_id);
    v0 = &groundCollVtx[groundCollLine[line_id].x0->v0_idx];
    pos_out->x = v0->pos.x;
    pos_out->y = v0->pos.y;
    pos_out->z = 0.0F;
}

enum_t mpLineGetKind(int line_id)
{
    LINEID_CHECK(4573, line_id);
    return groundCollLine[line_id].flags & LINE_FLAG_KIND;
}

u32 mpLineGetFlags(int line_id)
{
    LINEID_CHECK(4583, line_id);
    return groundCollLine[line_id].x0->flags;
}

void mpLib_80054D68(int line_id, u32 flags)
{
    LINEID_CHECK(4595, line_id);
    {
        mpLib_Line* line = groundCollLine[line_id].x0;
        u16* old_flags = &line->flags;
        *old_flags = (*old_flags & ~0xFF) | flags;
    }
}

Vec3* mpLineGetNormal(int line_id, Vec3* normal_out)
{
    mpLib_Line* line;
    PAD_STACK(4);

    LINEID_CHECK(4609, line_id);
    line = groundCollLine[line_id].x0;
    {
        float y0 = groundCollVtx[line->v0_idx].pos.y;
        float y1 = groundCollVtx[line->v1_idx].pos.y;
        float x0 = groundCollVtx[line->v0_idx].pos.x;
        float x1 = groundCollVtx[line->v1_idx].pos.x;
        normal_out->x = -(y1 - y0);
        normal_out->y = +(x1 - x0);
        normal_out->z = 0.0F;
        PSVECNormalize(normal_out, normal_out);
    }
    return normal_out;
}

bool mpLib_80054ED8(int line_id)
{
    if (line_id == -1) {
        return false;
    }
    if (line_id < 0 || line_id >= mpLib_804D64B4->line_count) {
        OSReport("%s:%d:not found lineID=%d\n", __FILE__, 4636, line_id);
        while (true) {
        };
    }
    if (!(groundCollLine[line_id].flags & 0x10000) ||
        (groundCollLine[line_id].flags & 0x40000))
    {
        return false;
    }
    return true;
}

bool mpLib_80054F68(int line_id, int line_id2)
{
    int var_r6 = line_id;
    int var_r9;

    LINEID_CHECK(4656, line_id);
    LINEID_CHECK(4657, line_id2);
    if (line_id == line_id2) {
        return true;
    }
    var_r9 = mpLineGetNext(line_id);
loop_23:
    if (var_r9 == -1 || !(groundCollLine[line_id].flags ==
                          (groundCollLine[var_r9].flags & LINE_FLAG_KIND)))
    {
        var_r6 = mpLineGetPrev(line_id);
        while (true) {
            if (var_r6 == -1 ||
                !(groundCollLine[line_id].flags ==
                  (groundCollLine[var_r6].flags & LINE_FLAG_KIND)))
            {
                return false;
            }
            if (var_r6 == line_id2) {
                return true;
            }
            var_r6 = mpLineGetPrev(var_r6);
        }
    }
    if (var_r9 == line_id2) {
        return true;
    }
    var_r9 = mpLineGetNext(var_r6);
    goto loop_23;
}

static inline HSD_JObj* jobj_child(HSD_JObj* jobj)
{
    if (jobj == NULL) {
        return NULL;
    }

    return jobj->child;
}

static inline HSD_JObj* jobj_next(HSD_JObj* jobj)
{
    if (jobj == NULL) {
        return NULL;
    }

    return jobj->next;
}

static inline HSD_JObj* jobj_parent(HSD_JObj* jobj)
{
    if (jobj == NULL) {
        return NULL;
    }

    return jobj->parent;
}

// what even is this lol
void mpLib_800552B0(int joint_id, HSD_JObj* jobj, int z)
{
    s32 i;
    HSD_JObj* r7;

    for (r7 = jobj_child(jobj), i = 0; r7 != NULL && i != z; i++) {
        if (!(r7->flags & 0x1000)) {
            if (jobj_child(r7) != NULL) {
                r7 = jobj_child(r7);
                continue;
            }
        }

        if (jobj_next(r7) != NULL) {
            r7 = jobj_next(r7);
            continue;
        }

        while (true) {
            if (jobj_parent(r7) == NULL) {
                r7 = NULL;
            } else {
                if (jobj_next(jobj_parent(r7)) != NULL) {
                    r7 = jobj_next(jobj_parent(r7));
                } else {
                    r7 = jobj_parent(r7);
                    continue;
                }
            }
            break;
        }
    }

    if (r7 != NULL) {
        CollJoint* joint = &groundCollJoint[joint_id];
        joint->x20 = r7;
    }
}

void mpLib_8005541C(int joint_id)
{
    CollJoint* joint;
    CollLine* line;
    int count;

    joint = &groundCollJoint[joint_id];
    joint->flags |= 0x40000;

    count = joint->coll_info->floor_count;
    line = &groundCollLine[joint->coll_info->floor_start];
    while (count-- > 0) {
        line->flags |= 0x40000;
        line++;
    }

    count = joint->coll_info->ceiling_count;
    line = &groundCollLine[joint->coll_info->ceiling_start];
    while (count-- > 0) {
        line->flags |= 0x40000;
        line++;
    }

    count = joint->coll_info->left_wall_count;
    line = &groundCollLine[joint->coll_info->left_wall_start];
    while (count-- > 0) {
        line->flags |= 0x40000;
        line++;
    }

    count = joint->coll_info->right_wall_count;
    line = &groundCollLine[joint->coll_info->right_wall_start];
    while (count-- > 0) {
        line->flags |= 0x40000;
        line++;
    }

    count = joint->coll_info->dynamic_count;
    line = &groundCollLine[joint->coll_info->dynamic_start];
    while (count-- > 0) {
        line->flags |= 0x40000;
        line++;
    }
}

void mpLib_800557D0(int joint_id)
{
    CollJoint* joint;
    CollLine* line;
    CollVtx* vtx;
    int count;
    int i;

    joint = &groundCollJoint[joint_id];
    joint->flags &= ~0x40000;

    count = joint->coll_info->floor_count;
    line = &groundCollLine[joint->coll_info->floor_start];
    while (count-- > 0) {
        line->flags &= ~0x40000;
        line++;
    }

    count = joint->coll_info->ceiling_count;
    line = &groundCollLine[joint->coll_info->ceiling_start];
    while (count-- > 0) {
        line->flags &= ~0x40000;
        line++;
    }

    count = joint->coll_info->left_wall_count;
    line = &groundCollLine[joint->coll_info->left_wall_start];
    while (count-- > 0) {
        line->flags &= ~0x40000;
        line++;
    }

    count = joint->coll_info->right_wall_count;
    line = &groundCollLine[joint->coll_info->right_wall_start];
    while (count-- > 0) {
        line->flags &= ~0x40000;
        line++;
    }

    count = joint->coll_info->dynamic_count;
    line = &groundCollLine[joint->coll_info->dynamic_start];
    while (count-- > 0) {
        line->flags &= ~0x40000;
        line++;
    }

    count = joint->coll_info->vtx_count;
    vtx = &groundCollVtx[joint->coll_info->vtx_start];
    while (count-- > 0) {
        vtx->x10 = vtx->pos.x;
        vtx->x14 = vtx->pos.y;
        vtx++;
    }
}

void mpUpdateDynamics(int joint_id)
{
    const double TAN30 = 0.577350295784245;
    const double TAN60 = 1.7320508368950045;
    CollJoint* joint = &groundCollJoint[joint_id];
    CollLine* line;
    int i;
    s16 count = joint->coll_info->dynamic_count;
    u32 kind;

    line = &groundCollLine[joint->coll_info->dynamic_start];

    for (i = 0; i < count; i++, line++) {
        mpLib_Line* temp = line->x0;
        CollVtx* v1 = &groundCollVtx[temp->v1_idx];
        CollVtx* v0 = &groundCollVtx[temp->v0_idx];
        float dx = v1->pos.x - v0->pos.x;
        float dy = v1->pos.y - v0->pos.y;
        if (dx > 0.0F) {
            if (dy / dx > TAN60) {
                kind = CollLine_LeftWall;
            } else if (dy / dx < -TAN60) {
                kind = CollLine_RightWall;
            } else {
                kind = CollLine_Floor;
            }
        } else if (dx < 0.0F) {
            if (dy / dx > TAN30) {
                kind = CollLine_RightWall;
            } else if (dy / dx < -TAN30) {
                kind = CollLine_LeftWall;
            } else {
                kind = CollLine_Ceiling;
            }
        } else if (dy > 0.0F) {
            kind = CollLine_LeftWall;
        } else if (dy < 0.0F) {
            kind = CollLine_RightWall;
        } else {
            HSD_ASSERT(4884, 0);
        }
        line->flags = (line->flags & ~LINE_FLAG_KIND) | kind;
        if ((joint->flags & 0x10000) && (line->x0->flags & 0x400)) {
            if (kind & CollLine_Floor) {
                line->flags |= 0x10000 | LINE_FLAG_PLATFORM;
                line->x0->flags |= LINE_FLAG_PLATFORM;
            } else {
                line->flags &= ~0x10000;
            }
        }
    }
}

void mpLib_80055E24(int joint_id)
{
    bool var_r6;
    CollJoint* joint = &groundCollJoint[joint_id];

    mpUpdateDynamics(joint_id);
    var_r6 = false;
    if (!(joint->flags & 0x40800) && (joint->flags & 0x10000)) {
        var_r6 = true;
    }
    mpIsland_8005B334(joint_id, joint->coll_info->vtx_start,
                      joint->coll_info->vtx_count, var_r6);
}

void mpLib_80055E9C(int joint_id)
{
    float f31;
    float f30;
    float f0;
    float f1;
    float f2;
    float f3;
    u8 _[4];
    float m1_3;
    float m0_3;
    float m0_0;
    CollJoint* joint;
    HSD_JObj* jobj;
    int vtx_count;
    CollVtx* v_r26;
    int var_r25;
    CollVtx* v_r4;
    bool var_r6;
    MtxPtr mtx;
    int i;
    Vec3 sp28;
    PAD_STACK(0x14);

    mpColl_804D64AC += 1;
    joint = &groundCollJoint[joint_id];
    vtx_count = joint->coll_info->vtx_count;
    v_r4 = &groundCollVtx[joint->coll_info->vtx_start];
    for (i = 0; i < vtx_count; i++, v_r4++) {
        v_r4->x10 = v_r4->pos.x;
        v_r4->x14 = v_r4->pos.y;
    }
    jobj = joint->x20;
    if (jobj == NULL) {
        return;
    }

    if (HSD_JObjGetFlags(jobj) & 0x10) {
        if (!(joint->flags & 0x40000)) {
            mpLib_8005541C(joint_id);
            var_r6 = false;
            if (!(joint->flags & 0x40800) && (joint->flags & 0x10000)) {
                var_r6 = true;
            }
            mpIsland_8005B334(joint_id, joint->coll_info->vtx_start,
                              joint->coll_info->vtx_count, var_r6);
        }
        return;
    }

    joint->xE = true;
    var_r25 = 0;
    HSD_JObjSetupMatrix(jobj);
    mtx = HSD_JObjGetMtxPtr(jobj);
    m0_0 = mtx[0][0];
    if (m0_0 == mtx[1][1] && m0_0 == mtx[2][2]) {
        m0_3 = mtx[0][3];
        m1_3 = mtx[1][3];
        v_r4 = &groundCollVtx[joint->coll_info->vtx_start];
        for (i = 0; i < vtx_count; i++, v_r4++) {
            v_r4->pos.x = v_r4->x0 * m0_0 + m0_3;
            v_r4->pos.y = v_r4->x4 * m0_0 + m1_3;
        }
        joint->x10.x = (joint->coll_info->x14 * m0_0 + m0_3) - 30.0F;
        joint->x10.y = (joint->coll_info->x18 * m0_0 + m1_3) - 30.0F;
        joint->x18.x = 30.0F + (joint->coll_info->x1C * m0_0 + m0_3);
        joint->x18.y = 30.0F + (joint->coll_info->x20 * m0_0 + m1_3);
        joint->flags |= 0x100;
        goto after0;
    }

    i = 0;
    v_r26 = &groundCollVtx[joint->coll_info->vtx_start];

    while (i < vtx_count) {
        sp28.x = v_r26->x0;
        sp28.y = v_r26->x4;
        sp28.z = 0.0F;
        PSMTXMultVec(jobj->mtx, &sp28, &sp28);
        v_r26->pos.x = sp28.x;
        v_r26->pos.y = sp28.y;
        if (mpLib_804D64CC == 0 || v_r26->pos.x != v_r26->x10 ||
            v_r26->pos.y != v_r26->x14 || (++var_r25 <= 1))
        {
            i += 1;
            v_r26 += 1;
        } else {
            goto after1;
        }
    }
    {
        mtx = HSD_JObjGetMtxPtr(jobj);
        if (mtx[0][1] != 0.0F || mtx[0][2] != 0.0F || mtx[1][0] != 0.0F ||
            mtx[1][2] != 0.0F || mtx[2][0] != 0.0F || mtx[2][1] != 0.0F)
        {
            joint->flags |= 0x200;
        }
        joint->flags |= 0x100;
        if (!(joint->flags & 0x400)) {
            sp28.x = joint->coll_info->x14;
            sp28.y = joint->coll_info->x18;
            sp28.z = 0.0F;
            PSMTXMultVec(jobj->mtx, &sp28, &sp28);
            joint->x10.x = sp28.x;
            joint->x10.y = sp28.y;
            sp28.x = joint->coll_info->x1C;
            sp28.y = joint->coll_info->x20;
            sp28.z = 0.0F;
            PSMTXMultVec(jobj->mtx, &sp28, &sp28);
            joint->x18.x = sp28.x;
            joint->x18.y = sp28.y;
            if (joint->flags & 0x200) {
                sp28.x = joint->coll_info->x1C;
                sp28.y = joint->coll_info->x18;
                sp28.z = 0.0F;
                PSMTXMultVec(jobj->mtx, &sp28, &sp28);
                f30 = sp28.x;
                f31 = sp28.y;
                sp28.x = joint->coll_info->x14;
                sp28.y = joint->coll_info->x20;
                sp28.z = 0.0F;
                PSMTXMultVec(jobj->mtx, &sp28, &sp28);
                f1 = joint->x10.x;
                f0 = joint->x18.x;
                f2 = sp28.x;
                f3 = sp28.y;
                if (f1 > f0) {
                    joint->x10.x = f0;
                }
                if (joint->x10.x > f30) {
                    joint->x10.x = f30;
                }
                if (joint->x10.x > f2) {
                    joint->x10.x = f2;
                }
                if (joint->x18.x < f1) {
                    joint->x18.x = f1;
                }
                if (joint->x18.x < f30) {
                    joint->x18.x = f30;
                }
                if (joint->x18.x < f2) {
                    joint->x18.x = f2;
                }
                f1 = joint->x10.y;
                f0 = joint->x18.y;
                if (f1 > f0) {
                    joint->x10.y = f0;
                }
                if (joint->x10.y > f31) {
                    joint->x10.y = f31;
                }
                if (joint->x10.y > f3) {
                    joint->x10.y = f3;
                }
                if (joint->x18.y < f1) {
                    joint->x18.y = f1;
                }
                if (joint->x18.y < f31) {
                    joint->x18.y = f31;
                }
                if (joint->x18.y < f3) {
                    joint->x18.y = f3;
                }
            }
            joint->x10.x -= 30.0F;
            joint->x18.x += 30.0F;
            joint->x10.y -= 30.0F;
            joint->x18.y += 30.0F;
        }
    }

after0:
    mpUpdateDynamics(joint_id);

after1:
    if (joint->flags & 0x40000) {
        mpLib_800557D0(joint_id);
    }
    var_r6 = false;
    if (!(joint->flags & (0x40000 | 0x800)) && (joint->flags & 0x10000)) {
        var_r6 = true;
    }
    mpIsland_8005B334(joint_id, joint->coll_info->vtx_start,
                      joint->coll_info->vtx_count, var_r6);
}

void mpLib_800565DC(int joint_id)
{
    CollJoint* joint = &groundCollJoint[joint_id];
    CollVtx* vtx = &groundCollVtx[joint->coll_info->vtx_start];
    int count = joint->coll_info->vtx_count;

    int i;
    for (i = 0; i < count; i++) {
        if (joint->x10.x > vtx->pos.x - 30.0F) {
            joint->x10.x = vtx->pos.x - 30.0F;
        }
        if (joint->x18.x < vtx->pos.x + 30.0F) {
            joint->x18.x = vtx->pos.x + 30.0F;
        }
        if (joint->x10.y > vtx->pos.y - 30.0F) {
            joint->x10.y = vtx->pos.y - 30.0F;
        }
        if (joint->x18.y < vtx->pos.y + 30.0F) {
            joint->x18.y = vtx->pos.y + 30.0F;
        }
        vtx += 1;
    }
}

void mpLib_8005667C(int joint_id)
{
    bool var_r6 = false;
    CollJoint* joint = &groundCollJoint[joint_id];

    if (!(joint->flags & 0x40800) && (joint->flags & 0x10000)) {
        var_r6 = true;
    }
    mpIsland_8005B334(joint_id, joint->coll_info->vtx_start,
                      joint->coll_info->vtx_count, var_r6);
}

void mpVtxGetPos(int vtx_id, float* x_out, float* y_out)
{
    CollVtx* vtx = &groundCollVtx[vtx_id];
    *x_out = vtx->pos.x;
    *y_out = vtx->pos.y;
}

void mpVtxSetPos(int vtx_id, float x, float y)
{
    CollVtx* vtx = &groundCollVtx[vtx_id];
    vtx->pos.x = x;
    vtx->pos.y = y;
}

void mpLineSetPos(int line_id, float x0, float y0, float x1, float y1)
{
    CollLine* line = &groundCollLine[line_id];
    mpVtxSetPos(line->x0->v0_idx, x0, y0);
    mpVtxSetPos(line->x0->v1_idx, x1, y1);
}

void mpLib_80056758(int line_id, float x0, float y0, float x1, float y1)
{
    CollLine* line = &groundCollLine[line_id];

    CollVtx* vtx = &groundCollVtx[line->x0->v0_idx];
    vtx->pos.x = vtx->x0 + x0;
    vtx->pos.y = vtx->x4 + y0;

    vtx = &groundCollVtx[line->x0->v1_idx];
    vtx->pos.x = vtx->x0 + x1;
    vtx->pos.y = vtx->x4 + y1;
}

bool mpGetSpeed(int line_id, Vec3* pos, Vec3* speed)
{
    float new_x;
    float new_y;
    CollVtx* v0_r5;
    CollVtx* v1_r6;

    if (!mpLib_80054ED8(line_id)) {
        return false;
    }

    v0_r5 = &groundCollVtx[groundCollLine[line_id].x0->v0_idx];
    v1_r6 = &groundCollVtx[groundCollLine[line_id].x0->v1_idx];
    mpRemap2d(&new_x, &new_y, v0_r5->x10, v0_r5->x14, v1_r6->x10, v1_r6->x14,
              v0_r5->pos.x, v0_r5->pos.y, v1_r6->pos.x, v1_r6->pos.y, pos->x,
              pos->y);
    speed->x = new_x - pos->x;
    speed->y = new_y - pos->y;
    speed->z = 0.0F;
    if (g_debugLevel >= 3) {
        if (ABS(speed->x) > 10000.0F || ABS(speed->y) > 10000.0F) {
            OSReport("%s:%d: Error: mpGetSpeed() x=%f y=%f\n", __FILE__, 5333,
                     speed->x, speed->y);
            HSD_ASSERT(5334,
             !(ABS(speed->x)>10000.0F||ABS(speed->y)>10000.0F));
            HSD_ASSERT(5335, 0);
        }
    }
    return true;
}

struct mpLib_803BF248_t_x4 {
    float x0;
    int x4[4];
    int x14[3];
    int x20[4];
    int x30[3];
    int x3C[4];
    int x4C[3];
};

struct mpLib_803BF248_t {
    InternalStageId id;
    struct mpLib_803BF248_t_x4* (*x4)[20];
};
static struct mpLib_803BF248_t_x4 mpLib_803BD3D8 = {
    1.0F,         { -1, -1, -1, -1 }, { 0, -1, 0 }, { -1, -1, -1, -1 },
    { 0, -1, 0 }, { -1, -1, -1, -1 }, { 0, -1, 0 },
};
static struct mpLib_803BF248_t_x4 mpLib_803BD430 = {
    1.0F,         { 0x161, 0x161, 0x161, 0x161 },
    { 1, -1, 0 }, { -1, -1, -1, -1 },
    { 0, -1, 0 }, { 0x036, 0x037, 0x038, 0x039 },
    { 1, -1, 0 },
};
static struct mpLib_803BF248_t_x4 mpLib_803BD488 = {
    1.5F,         { 0x152, 0x152, 0x152, 0x152 },
    { 1, -1, 0 }, { -1, -1, -1, -1 },
    { 0, -1, 0 }, { 0x01D, 0x01E, 0x01F, 0x020 },
    { 1, -1, 0 },
};
static struct mpLib_803BF248_t_x4 mpLib_803BD4E0 = {
    1.0F,         { 0x155, 0x155, 0x155, 0x155 },
    { 1, -1, 0 }, { -1, -1, -1, -1 },
    { 0, -1, 0 }, { 0x022, 0x023, 0x024, 0x025 },
    { 1, -1, 0 },
};
static struct mpLib_803BF248_t_x4 mpLib_803BD538 = {
    1.0F,         { 0x16D, 0x16D, 0x16D, 0x16D },
    { 1, -1, 0 }, { -1, -1, -1, -1 },
    { 0, -1, 0 }, { 0x00E, 0x00F, 0x010, 0x011 },
    { 0, -1, 0 },
};
static struct mpLib_803BF248_t_x4 mpLib_803BD590 = {
    1.0F,         { 0x15B, 0x15B, 0x15B, 0x15B },
    { 1, -1, 0 }, { 0x04B, 0x04B, 0x04C, 0x04C },
    { 1, -1, 0 }, { 0x02C, 0x02D, 0x02E, 0x02F },
    { 1, -1, 1 },
};
static struct mpLib_803BF248_t_x4 mpLib_803BD5E8 = {
    1.0F,         { 0x158, 0x158, 0x158, 0x158 },
    { 1, -1, 0 }, { -1, -1, -1, -1 },
    { 0, -1, 0 }, { 0x027, 0x028, 0x029, 0x02A },
    { 1, -1, 0 },
};
static struct mpLib_803BF248_t_x4 mpLib_803BD640 = {
    1.0F,         { 0x16A, 0x16A, 0x16A, 0x16A },
    { 1, -1, 0 }, { -1, -1, -1, -1 },
    { 0, -1, 0 }, { 0x03B, 0x03C, 0x03D, 0x03E },
    { 1, -1, 0 },
};
static struct mpLib_803BF248_t_x4 mpLib_803BD698 = {
    1.0F,         { 0x15E, 0x15E, 0x15E, 0x15E },
    { 0, -1, 0 }, { -1, -1, -1, -1 },
    { 0, -1, 0 }, { 0x031, 0x032, 0x033, 0x034 },
    { 0, -1, 0 },
};
static struct mpLib_803BF248_t_x4 mpLib_803BD6F0 = {
    1.0F,         { -1, -1, -1, -1 }, { 0, -1, 0 }, { -1, -1, -1, -1 },
    { 0, -1, 0 }, { -1, -1, -1, -1 }, { 0, -1, 0 },
};
static struct mpLib_803BF248_t_x4 mpLib_803BD748 = {
    1.0F,         { 0x14F, 0x14F, 0x14F, 0x14F },
    { 1, -1, 0 }, { 0x20E, 0x20E, 0x20E, 0x20E },
    { 0, -1, 0 }, { 0x018, 0x019, 0x01A, 0x01B },
    { 1, -1, 0 },
};
static struct mpLib_803BF248_t_x4 mpLib_803BD7A0 = {
    1.0F,
    { 0x14F, 0x14F, 0x14F, 0x14F },
    { 1, 0x00007537, 0 },
    { 0x20E, 0x20E, 0x20E, 0x20E },
    { 0, 0x00007538, 0 },
    { 0x018, 0x019, 0x01A, 0x01B },
    { 1, 0x0000753B, 0 },
};
static struct mpLib_803BF248_t_x4 mpLib_803BD7F8 = {
    1.0F,
    { 0x14F, 0x14F, 0x14F, 0x14F },
    { 1, 0x00007539, 0 },
    { 0x20E, 0x20E, 0x20E, 0x20E },
    { 0, 0x00007533, 0 },
    { 0x018, 0x019, 0x01A, 0x01B },
    { 1, 0x0000753A, 0 },
};
static struct mpLib_803BF248_t_x4 mpLib_803BD850 = {
    1.0F,
    { 0x14F, 0x14F, 0x14F, 0x14F },
    { 1, 0x0000754A, 0 },
    { 0x20E, 0x20E, 0x20E, 0x20E },
    { 0, 0x00007539, 0 },
    { 0x018, 0x019, 0x01A, 0x01B },
    { 1, -1, 0 },
};
static struct mpLib_803BF248_t_x4 mpLib_803BD8A8 = {
    1.0F,         { -1, -1, -1, -1 }, { 0, -1, 0 }, { -1, -1, -1, -1 },
    { 0, -1, 0 }, { -1, -1, -1, -1 }, { 0, -1, 0 },
};
static struct mpLib_803BF248_t_x4 mpLib_803BD900 = {
    0.1F,         { -1, -1, -1, -1 }, { 0, -1, 0 }, { -1, -1, -1, -1 },
    { 0, -1, 0 }, { -1, -1, -1, -1 }, { 0, -1, 0 },
};
static struct mpLib_803BF248_t_x4 mpLib_803BD958 = {
    0.9F,         { -1, -1, -1, -1 }, { 0, -1, 0 }, { -1, -1, -1, -1 },
    { 0, -1, 0 }, { -1, -1, -1, -1 }, { 0, -1, 0 },
};
static struct mpLib_803BF248_t_x4 mpLib_803BD9B0 = {
    1.0F,         { 0x14C, 0x14C, 0x14C, 0x14C },
    { 1, -1, 0 }, { -1, -1, -1, -1 },
    { 0, -1, 0 }, { 0x013, 0x014, 0x015, 0x016 },
    { 1, -1, 0 },
};
static struct mpLib_803BF248_t_x4 mpLib_803BDA08 = {
    1.0F,
    { 0x14C, 0x14C, 0x14C, 0x14C },
    { 1, 0x00007531, 0 },
    { -1, -1, -1, -1 },
    { 0, 0x00007532, 0 },
    { 0x013, 0x014, 0x015, 0x016 },
    { 1, 0x00007533, 0 },
};
static struct mpLib_803BF248_t_x4 mpLib_803BDA60 = {
    0.2F,         { 0x164, 0x164, 0x164, 0x164 },
    { 1, -1, 0 }, { -1, -1, -1, -1 },
    { 0, -1, 0 }, { 0x036, 0x037, 0x038, 0x039 },
    { 1, -1, 0 },
};
static struct mpLib_803BF248_t_x4 mpLib_803BDAB8 = {
    1.0F,         { 0x170, 0x170, 0x170, 0x170 },
    { 0, -1, 0 }, { -1, -1, -1, -1 },
    { 0, -1, 0 }, { 0x040, 0x041, 0x042, 0x043 },
    { 0, -1, 0 },
};
static struct mpLib_803BF248_t_x4 mpLib_803BDB10 = {
    0.1F,         { 0x15E, 0x15E, 0x15E, 0x15E },
    { 1, -1, 0 }, { -1, -1, -1, -1 },
    { 0, -1, 0 }, { 0x031, 0x032, 0x033, 0x034 },
    { 1, -1, 0 },
};
static struct mpLib_803BF248_t_x4 mpLib_803BDB68 = {
    1.0F,         { 0x167, 0x167, 0x167, 0x167 },
    { 1, -1, 0 }, { -1, -1, -1, -1 },
    { 0, -1, 0 }, { 0x03B, 0x03C, 0x03D, 0x03E },
    { 1, -1, 0 },
};
static struct mpLib_803BF248_t_x4 mpLib_803BDBC0 = {
    1.0F,         { -1, -1, -1, -1 }, { 0, -1, 0 }, { -1, -1, -1, -1 },
    { 0, -1, 0 }, { -1, -1, -1, -1 }, { 0, -1, 0 },
};
static struct mpLib_803BF248_t_x4* mpLib_803BDC18[20] = {
    &mpLib_803BD3D8, &mpLib_803BD430, &mpLib_803BD488, &mpLib_803BD4E0,
    &mpLib_803BD538, &mpLib_803BD590, &mpLib_803BD5E8, &mpLib_803BD640,
    &mpLib_803BD698, &mpLib_803BD6F0, &mpLib_803BD748, &mpLib_803BD8A8,
    &mpLib_803BD900, &mpLib_803BD958, &mpLib_803BD9B0, &mpLib_803BDA60,
    &mpLib_803BDAB8, &mpLib_803BDB10, &mpLib_803BDB68, &mpLib_803BDBC0,
};
static struct mpLib_803BF248_t_x4* mpLib_803BDC68[20] = {
    &mpLib_803BD3D8, &mpLib_803BD430, &mpLib_803BD488, &mpLib_803BD4E0,
    &mpLib_803BD538, &mpLib_803BD590, &mpLib_803BD5E8, &mpLib_803BD640,
    &mpLib_803BD698, &mpLib_803BD6F0, &mpLib_803BD748, &mpLib_803BD8A8,
    &mpLib_803BD900, &mpLib_803BD958, &mpLib_803BD9B0, &mpLib_803BDA60,
    &mpLib_803BDAB8, &mpLib_803BDB10, &mpLib_803BDB68, &mpLib_803BDBC0,
};
static struct mpLib_803BF248_t_x4* mpLib_803BDCB8[20] = {
    &mpLib_803BD3D8, &mpLib_803BD430, &mpLib_803BD488, &mpLib_803BD4E0,
    &mpLib_803BD538, &mpLib_803BD590, &mpLib_803BD5E8, &mpLib_803BD640,
    &mpLib_803BD698, &mpLib_803BD6F0, &mpLib_803BD748, &mpLib_803BD8A8,
    &mpLib_803BD900, &mpLib_803BD958, &mpLib_803BD9B0, &mpLib_803BDA60,
    &mpLib_803BDAB8, &mpLib_803BDB10, &mpLib_803BDB68,
};
static struct mpLib_803BF248_t_x4* mpLib_803BDD08[20] = {
    &mpLib_803BD3D8, &mpLib_803BD430, &mpLib_803BD488, &mpLib_803BD4E0,
    &mpLib_803BD538, &mpLib_803BD590, &mpLib_803BD5E8, &mpLib_803BD640,
    &mpLib_803BD698, &mpLib_803BD6F0, &mpLib_803BD748, &mpLib_803BD8A8,
    &mpLib_803BD900, &mpLib_803BD958, &mpLib_803BD9B0, &mpLib_803BDA60,
    &mpLib_803BDAB8, &mpLib_803BDB10, &mpLib_803BDB68, &mpLib_803BDBC0,
};
static struct mpLib_803BF248_t_x4* mpLib_803BDD58[20] = {
    &mpLib_803BD3D8, &mpLib_803BD430, &mpLib_803BD488, &mpLib_803BD4E0,
    &mpLib_803BD538, &mpLib_803BD590, &mpLib_803BD5E8, &mpLib_803BD640,
    &mpLib_803BD698, &mpLib_803BD6F0, &mpLib_803BD748, &mpLib_803BD8A8,
    &mpLib_803BD900, &mpLib_803BD958, &mpLib_803BD9B0, &mpLib_803BDA60,
    &mpLib_803BDAB8, &mpLib_803BDB10, &mpLib_803BDB68, &mpLib_803BDBC0,
};
static struct mpLib_803BF248_t_x4* mpLib_803BDDA8[20] = {
    &mpLib_803BD3D8, &mpLib_803BD430, &mpLib_803BD488, &mpLib_803BD4E0,
    &mpLib_803BD538, &mpLib_803BD590, &mpLib_803BD5E8, &mpLib_803BD640,
    &mpLib_803BD698, &mpLib_803BD6F0, &mpLib_803BD748, &mpLib_803BD8A8,
    &mpLib_803BD900, &mpLib_803BD958, &mpLib_803BD9B0, &mpLib_803BDA60,
    &mpLib_803BDAB8, &mpLib_803BDB10, &mpLib_803BDB68, &mpLib_803BDBC0,
};
static struct mpLib_803BF248_t_x4* mpLib_803BDDF8[20] = {
    &mpLib_803BD3D8, &mpLib_803BD430, &mpLib_803BD488, &mpLib_803BD4E0,
    &mpLib_803BD538, &mpLib_803BD590, &mpLib_803BD5E8, &mpLib_803BD640,
    &mpLib_803BD698, &mpLib_803BD6F0, &mpLib_803BD748, &mpLib_803BD8A8,
    &mpLib_803BD900, &mpLib_803BD958, &mpLib_803BD9B0, &mpLib_803BDA60,
    &mpLib_803BDAB8, &mpLib_803BDB10, &mpLib_803BDB68, &mpLib_803BDBC0,
};
static struct mpLib_803BF248_t_x4* mpLib_803BDE48[20] = {
    &mpLib_803BD3D8, &mpLib_803BD430, &mpLib_803BD488, &mpLib_803BD4E0,
    &mpLib_803BD538, &mpLib_803BD590, &mpLib_803BD5E8, &mpLib_803BD640,
    &mpLib_803BD698, &mpLib_803BD6F0, &mpLib_803BD748, &mpLib_803BD8A8,
    &mpLib_803BD900, &mpLib_803BD958, &mpLib_803BD9B0, &mpLib_803BDA60,
    &mpLib_803BDAB8, &mpLib_803BDB10, &mpLib_803BDB68, &mpLib_803BDBC0,
};
static struct mpLib_803BF248_t_x4* mpLib_803BDE98[20] = {
    &mpLib_803BD3D8, &mpLib_803BD430, &mpLib_803BD488, &mpLib_803BD4E0,
    &mpLib_803BD538, &mpLib_803BD590, &mpLib_803BD5E8, &mpLib_803BD640,
    &mpLib_803BD698, &mpLib_803BD6F0, &mpLib_803BD748, &mpLib_803BD8A8,
    &mpLib_803BD900, &mpLib_803BD958, &mpLib_803BD9B0, &mpLib_803BDA60,
    &mpLib_803BDAB8, &mpLib_803BDB10, &mpLib_803BDB68, &mpLib_803BDBC0,
};
static struct mpLib_803BF248_t_x4* mpLib_803BDEE8[20] = {
    &mpLib_803BD3D8, &mpLib_803BD430, &mpLib_803BD488, &mpLib_803BD4E0,
    &mpLib_803BD538, &mpLib_803BD590, &mpLib_803BD5E8, &mpLib_803BD640,
    &mpLib_803BD698, &mpLib_803BD6F0, &mpLib_803BD748, &mpLib_803BD8A8,
    &mpLib_803BD900, &mpLib_803BD958, &mpLib_803BD9B0, &mpLib_803BDA60,
    &mpLib_803BDAB8, &mpLib_803BDB10, &mpLib_803BDB68, &mpLib_803BDBC0,
};
static struct mpLib_803BF248_t_x4* mpLib_803BDF38[20] = {
    &mpLib_803BD3D8, &mpLib_803BD430, &mpLib_803BD488, &mpLib_803BD4E0,
    &mpLib_803BD538, &mpLib_803BD590, &mpLib_803BD5E8, &mpLib_803BD640,
    &mpLib_803BD698, &mpLib_803BD6F0, &mpLib_803BD748, &mpLib_803BD8A8,
    &mpLib_803BD900, &mpLib_803BD958, &mpLib_803BD9B0, &mpLib_803BDA60,
    &mpLib_803BDAB8, &mpLib_803BDB10, &mpLib_803BDB68, &mpLib_803BDBC0,
};
static struct mpLib_803BF248_t_x4* mpLib_803BDF88[20] = {
    &mpLib_803BD3D8, &mpLib_803BD430, &mpLib_803BD488, &mpLib_803BD4E0,
    &mpLib_803BD538, &mpLib_803BD590, &mpLib_803BD5E8, &mpLib_803BD640,
    &mpLib_803BD698, &mpLib_803BD6F0, &mpLib_803BD748, &mpLib_803BD8A8,
    &mpLib_803BD900, &mpLib_803BD958, &mpLib_803BD9B0, &mpLib_803BDA60,
    &mpLib_803BDAB8, &mpLib_803BDB10, &mpLib_803BDB68, &mpLib_803BDBC0,
};
static struct mpLib_803BF248_t_x4* mpLib_803BDFD8[20] = {
    &mpLib_803BD3D8, &mpLib_803BD430, &mpLib_803BD488, &mpLib_803BD4E0,
    &mpLib_803BD538, &mpLib_803BD590, &mpLib_803BD5E8, &mpLib_803BD640,
    &mpLib_803BD698, &mpLib_803BD6F0, &mpLib_803BD7A0, &mpLib_803BD8A8,
    &mpLib_803BD900, &mpLib_803BD958, &mpLib_803BD9B0, &mpLib_803BDA60,
    &mpLib_803BDAB8, &mpLib_803BDB10, &mpLib_803BDB68, &mpLib_803BDBC0,
};
static struct mpLib_803BF248_t_x4* mpLib_803BE028[20] = {
    &mpLib_803BD3D8, &mpLib_803BD430, &mpLib_803BD488, &mpLib_803BD4E0,
    &mpLib_803BD538, &mpLib_803BD590, &mpLib_803BD5E8, &mpLib_803BD640,
    &mpLib_803BD698, &mpLib_803BD6F0, &mpLib_803BD748, &mpLib_803BD8A8,
    &mpLib_803BD900, &mpLib_803BD958, &mpLib_803BD9B0, &mpLib_803BDA60,
    &mpLib_803BDAB8, &mpLib_803BDB10, &mpLib_803BDB68, &mpLib_803BDBC0,
};
static struct mpLib_803BF248_t_x4* mpLib_803BE078[20] = {
    &mpLib_803BD3D8, &mpLib_803BD430, &mpLib_803BD488, &mpLib_803BD4E0,
    &mpLib_803BD538, &mpLib_803BD590, &mpLib_803BD5E8, &mpLib_803BD640,
    &mpLib_803BD698, &mpLib_803BD6F0, &mpLib_803BD748, &mpLib_803BD8A8,
    &mpLib_803BD900, &mpLib_803BD958, &mpLib_803BD9B0, &mpLib_803BDA60,
    &mpLib_803BDAB8, &mpLib_803BDB10, &mpLib_803BDB68, &mpLib_803BDBC0,
};
static struct mpLib_803BF248_t_x4* mpLib_803BE0C8[20] = {
    &mpLib_803BD3D8, &mpLib_803BD430, &mpLib_803BD488, &mpLib_803BD4E0,
    &mpLib_803BD538, &mpLib_803BD590, &mpLib_803BD5E8, &mpLib_803BD640,
    &mpLib_803BD698, &mpLib_803BD6F0, &mpLib_803BD748, &mpLib_803BD8A8,
    &mpLib_803BD900, &mpLib_803BD958, &mpLib_803BD9B0, &mpLib_803BDA60,
    &mpLib_803BDAB8, &mpLib_803BDB10, &mpLib_803BDB68, &mpLib_803BDBC0,
};
static struct mpLib_803BF248_t_x4* mpLib_803BE118[20] = {
    &mpLib_803BD3D8, &mpLib_803BD430, &mpLib_803BD488, &mpLib_803BD4E0,
    &mpLib_803BD538, &mpLib_803BD590, &mpLib_803BD5E8, &mpLib_803BD640,
    &mpLib_803BD698, &mpLib_803BD6F0, &mpLib_803BD850, &mpLib_803BD8A8,
    &mpLib_803BD900, &mpLib_803BD958, &mpLib_803BD9B0, &mpLib_803BDA60,
    &mpLib_803BDAB8, &mpLib_803BDB10, &mpLib_803BDB68, &mpLib_803BDBC0,
};
static struct mpLib_803BF248_t_x4* mpLib_803BE168[20] = {
    &mpLib_803BD3D8, &mpLib_803BD430, &mpLib_803BD488, &mpLib_803BD4E0,
    &mpLib_803BD538, &mpLib_803BD590, &mpLib_803BD5E8, &mpLib_803BD640,
    &mpLib_803BD698, &mpLib_803BD6F0, &mpLib_803BD748, &mpLib_803BD8A8,
    &mpLib_803BD900, &mpLib_803BD958, &mpLib_803BD9B0, &mpLib_803BDA60,
    &mpLib_803BDAB8, &mpLib_803BDB10, &mpLib_803BDB68, &mpLib_803BDBC0,
};
static struct mpLib_803BF248_t_x4* mpLib_803BE1B8[20] = {
    &mpLib_803BD3D8, &mpLib_803BD430, &mpLib_803BD488, &mpLib_803BD4E0,
    &mpLib_803BD538, &mpLib_803BD590, &mpLib_803BD5E8, &mpLib_803BD640,
    &mpLib_803BD698, &mpLib_803BD6F0, &mpLib_803BD748, &mpLib_803BD8A8,
    &mpLib_803BD900, &mpLib_803BD958, &mpLib_803BD9B0, &mpLib_803BDA60,
    &mpLib_803BDAB8, &mpLib_803BDB10, &mpLib_803BDB68, &mpLib_803BDBC0,
};
static struct mpLib_803BF248_t_x4* mpLib_803BE208[20] = {
    &mpLib_803BD3D8, &mpLib_803BD430, &mpLib_803BD488, &mpLib_803BD4E0,
    &mpLib_803BD538, &mpLib_803BD590, &mpLib_803BD5E8, &mpLib_803BD640,
    &mpLib_803BD698, &mpLib_803BD6F0, &mpLib_803BD748, &mpLib_803BD8A8,
    &mpLib_803BD900, &mpLib_803BD958, &mpLib_803BD9B0, &mpLib_803BDA60,
    &mpLib_803BDAB8, &mpLib_803BDB10, &mpLib_803BDB68, &mpLib_803BDBC0,
};
static struct mpLib_803BF248_t_x4* mpLib_803BE258[20] = {
    &mpLib_803BD3D8, &mpLib_803BD430, &mpLib_803BD488, &mpLib_803BD4E0,
    &mpLib_803BD538, &mpLib_803BD590, &mpLib_803BD5E8, &mpLib_803BD640,
    &mpLib_803BD698, &mpLib_803BD6F0, &mpLib_803BD748, &mpLib_803BD8A8,
    &mpLib_803BD900, &mpLib_803BD958, &mpLib_803BD9B0, &mpLib_803BDA60,
    &mpLib_803BDAB8, &mpLib_803BDB10, &mpLib_803BDB68, &mpLib_803BDBC0,
};
static struct mpLib_803BF248_t_x4* mpLib_803BE2A8[20] = {
    &mpLib_803BD3D8, &mpLib_803BD430, &mpLib_803BD488, &mpLib_803BD4E0,
    &mpLib_803BD538, &mpLib_803BD590, &mpLib_803BD5E8, &mpLib_803BD640,
    &mpLib_803BD698, &mpLib_803BD6F0, &mpLib_803BD748, &mpLib_803BD8A8,
    &mpLib_803BD900, &mpLib_803BD958, &mpLib_803BD9B0, &mpLib_803BDA60,
    &mpLib_803BDAB8, &mpLib_803BDB10, &mpLib_803BDB68, &mpLib_803BDBC0,
};
static struct mpLib_803BF248_t_x4* mpLib_803BE2F8[20] = {
    &mpLib_803BD3D8, &mpLib_803BD430, &mpLib_803BD488, &mpLib_803BD4E0,
    &mpLib_803BD538, &mpLib_803BD590, &mpLib_803BD5E8, &mpLib_803BD640,
    &mpLib_803BD698, &mpLib_803BD6F0, &mpLib_803BD748, &mpLib_803BD8A8,
    &mpLib_803BD900, &mpLib_803BD958, &mpLib_803BDA08, &mpLib_803BDA60,
    &mpLib_803BDAB8, &mpLib_803BDB10, &mpLib_803BDB68, &mpLib_803BDBC0,
};
static struct mpLib_803BF248_t_x4* mpLib_803BE348[20] = {
    &mpLib_803BD3D8, &mpLib_803BD430, &mpLib_803BD488, &mpLib_803BD4E0,
    &mpLib_803BD538, &mpLib_803BD590, &mpLib_803BD5E8, &mpLib_803BD640,
    &mpLib_803BD698, &mpLib_803BD6F0, &mpLib_803BD748, &mpLib_803BD8A8,
    &mpLib_803BD900, &mpLib_803BD958, &mpLib_803BD9B0, &mpLib_803BDA60,
    &mpLib_803BDAB8, &mpLib_803BDB10, &mpLib_803BDB68, &mpLib_803BDBC0,
};
static struct mpLib_803BF248_t_x4* mpLib_803BE398[20] = {
    &mpLib_803BD3D8, &mpLib_803BD430, &mpLib_803BD488, &mpLib_803BD4E0,
    &mpLib_803BD538, &mpLib_803BD590, &mpLib_803BD5E8, &mpLib_803BD640,
    &mpLib_803BD698, &mpLib_803BD6F0, &mpLib_803BD748, &mpLib_803BD8A8,
    &mpLib_803BD900, &mpLib_803BD958, &mpLib_803BD9B0, &mpLib_803BDA60,
    &mpLib_803BDAB8, &mpLib_803BDB10, &mpLib_803BDB68, &mpLib_803BDBC0,
};
static struct mpLib_803BF248_t_x4* mpLib_803BE3E8[20] = {
    &mpLib_803BD3D8, &mpLib_803BD430, &mpLib_803BD488, &mpLib_803BD4E0,
    &mpLib_803BD538, &mpLib_803BD590, &mpLib_803BD5E8, &mpLib_803BD640,
    &mpLib_803BD698, &mpLib_803BD6F0, &mpLib_803BD748, &mpLib_803BD8A8,
    &mpLib_803BD900, &mpLib_803BD958, &mpLib_803BD9B0, &mpLib_803BDA60,
    &mpLib_803BDAB8, &mpLib_803BDB10, &mpLib_803BDB68, &mpLib_803BDBC0,
};
static struct mpLib_803BF248_t_x4* mpLib_803BE438[20] = {
    &mpLib_803BD3D8, &mpLib_803BD430, &mpLib_803BD488, &mpLib_803BD4E0,
    &mpLib_803BD538, &mpLib_803BD590, &mpLib_803BD5E8, &mpLib_803BD640,
    &mpLib_803BD698, &mpLib_803BD6F0, &mpLib_803BD748, &mpLib_803BD8A8,
    &mpLib_803BD900, &mpLib_803BD958, &mpLib_803BD9B0, &mpLib_803BDA60,
    &mpLib_803BDAB8, &mpLib_803BDB10, &mpLib_803BDB68, &mpLib_803BDBC0,
};
static struct mpLib_803BF248_t_x4* mpLib_803BE488[20] = {
    &mpLib_803BD3D8, &mpLib_803BD430, &mpLib_803BD488, &mpLib_803BD4E0,
    &mpLib_803BD538, &mpLib_803BD590, &mpLib_803BD5E8, &mpLib_803BD640,
    &mpLib_803BD698, &mpLib_803BD6F0, &mpLib_803BD748, &mpLib_803BD8A8,
    &mpLib_803BD900, &mpLib_803BD958, &mpLib_803BD9B0, &mpLib_803BDA60,
    &mpLib_803BDAB8, &mpLib_803BDB10, &mpLib_803BDB68, &mpLib_803BDBC0,
};
static struct mpLib_803BF248_t_x4* mpLib_803BE4D8[20] = {
    &mpLib_803BD3D8, &mpLib_803BD430, &mpLib_803BD488, &mpLib_803BD4E0,
    &mpLib_803BD538, &mpLib_803BD590, &mpLib_803BD5E8, &mpLib_803BD640,
    &mpLib_803BD698, &mpLib_803BD6F0, &mpLib_803BD748, &mpLib_803BD8A8,
    &mpLib_803BD900, &mpLib_803BD958, &mpLib_803BD9B0, &mpLib_803BDA60,
    &mpLib_803BDAB8, &mpLib_803BDB10, &mpLib_803BDB68, &mpLib_803BDBC0,
};
static struct mpLib_803BF248_t_x4* mpLib_803BE528[20] = {
    &mpLib_803BD3D8, &mpLib_803BD430, &mpLib_803BD488, &mpLib_803BD4E0,
    &mpLib_803BD538, &mpLib_803BD590, &mpLib_803BD5E8, &mpLib_803BD640,
    &mpLib_803BD698, &mpLib_803BD6F0, &mpLib_803BD748, &mpLib_803BD8A8,
    &mpLib_803BD900, &mpLib_803BD958, &mpLib_803BD9B0, &mpLib_803BDA60,
    &mpLib_803BDAB8, &mpLib_803BDB10, &mpLib_803BDB68, &mpLib_803BDBC0,
};
static struct mpLib_803BF248_t_x4* mpLib_803BE578[20] = {
    &mpLib_803BD3D8, &mpLib_803BD430, &mpLib_803BD488, &mpLib_803BD4E0,
    &mpLib_803BD538, &mpLib_803BD590, &mpLib_803BD5E8, &mpLib_803BD640,
    &mpLib_803BD698, &mpLib_803BD6F0, &mpLib_803BD748, &mpLib_803BD8A8,
    &mpLib_803BD900, &mpLib_803BD958, &mpLib_803BD9B0, &mpLib_803BDA60,
    &mpLib_803BDAB8, &mpLib_803BDB10, &mpLib_803BDB68, &mpLib_803BDBC0,
};
static struct mpLib_803BF248_t_x4* mpLib_803BE5C8[20] = {
    &mpLib_803BD3D8, &mpLib_803BD430, &mpLib_803BD488, &mpLib_803BD4E0,
    &mpLib_803BD538, &mpLib_803BD590, &mpLib_803BD5E8, &mpLib_803BD640,
    &mpLib_803BD698, &mpLib_803BD6F0, &mpLib_803BD748, &mpLib_803BD8A8,
    &mpLib_803BD900, &mpLib_803BD958, &mpLib_803BD9B0, &mpLib_803BDA60,
    &mpLib_803BDAB8, &mpLib_803BDB10, &mpLib_803BDB68, &mpLib_803BDBC0,
};
static struct mpLib_803BF248_t_x4* mpLib_803BE618[20] = {
    &mpLib_803BD3D8, &mpLib_803BD430, &mpLib_803BD488, &mpLib_803BD4E0,
    &mpLib_803BD538, &mpLib_803BD590, &mpLib_803BD5E8, &mpLib_803BD640,
    &mpLib_803BD698, &mpLib_803BD6F0, &mpLib_803BD7F8, &mpLib_803BD8A8,
    &mpLib_803BD900, &mpLib_803BD958, &mpLib_803BD9B0, &mpLib_803BDA60,
    &mpLib_803BDAB8, &mpLib_803BDB10, &mpLib_803BDB68, &mpLib_803BDBC0,
};
static struct mpLib_803BF248_t_x4* mpLib_803BE668[20] = {
    &mpLib_803BD3D8, &mpLib_803BD430, &mpLib_803BD488, &mpLib_803BD4E0,
    &mpLib_803BD538, &mpLib_803BD590, &mpLib_803BD5E8, &mpLib_803BD640,
    &mpLib_803BD698, &mpLib_803BD6F0, &mpLib_803BD748, &mpLib_803BD8A8,
    &mpLib_803BD900, &mpLib_803BD958, &mpLib_803BD9B0, &mpLib_803BDA60,
    &mpLib_803BDAB8, &mpLib_803BDB10, &mpLib_803BDB68, &mpLib_803BDBC0,
};
static struct mpLib_803BF248_t_x4* mpLib_803BE6B8[20] = {
    &mpLib_803BD3D8, &mpLib_803BD430, &mpLib_803BD488, &mpLib_803BD4E0,
    &mpLib_803BD538, &mpLib_803BD590, &mpLib_803BD5E8, &mpLib_803BD640,
    &mpLib_803BD698, &mpLib_803BD6F0, &mpLib_803BD748, &mpLib_803BD8A8,
    &mpLib_803BD900, &mpLib_803BD958, &mpLib_803BD9B0, &mpLib_803BDA60,
    &mpLib_803BDAB8, &mpLib_803BDB10, &mpLib_803BDB68, &mpLib_803BDBC0,
};
static struct mpLib_803BF248_t_x4* mpLib_803BE708[20] = {
    &mpLib_803BD3D8, &mpLib_803BD430, &mpLib_803BD488, &mpLib_803BD4E0,
    &mpLib_803BD538, &mpLib_803BD590, &mpLib_803BD5E8, &mpLib_803BD640,
    &mpLib_803BD698, &mpLib_803BD6F0, &mpLib_803BD748, &mpLib_803BD8A8,
    &mpLib_803BD900, &mpLib_803BD958, &mpLib_803BD9B0, &mpLib_803BDA60,
    &mpLib_803BDAB8, &mpLib_803BDB10, &mpLib_803BDB68, &mpLib_803BDBC0,
};
static struct mpLib_803BF248_t_x4* mpLib_803BE758[20] = {
    &mpLib_803BD3D8, &mpLib_803BD430, &mpLib_803BD488, &mpLib_803BD4E0,
    &mpLib_803BD538, &mpLib_803BD590, &mpLib_803BD5E8, &mpLib_803BD640,
    &mpLib_803BD698, &mpLib_803BD6F0, &mpLib_803BD748, &mpLib_803BD8A8,
    &mpLib_803BD900, &mpLib_803BD958, &mpLib_803BD9B0, &mpLib_803BDA60,
    &mpLib_803BDAB8, &mpLib_803BDB10, &mpLib_803BDB68, &mpLib_803BDBC0,
};
static struct mpLib_803BF248_t_x4* mpLib_803BE7A8[20] = {
    &mpLib_803BD3D8, &mpLib_803BD430, &mpLib_803BD488, &mpLib_803BD4E0,
    &mpLib_803BD538, &mpLib_803BD590, &mpLib_803BD5E8, &mpLib_803BD640,
    &mpLib_803BD698, &mpLib_803BD6F0, &mpLib_803BD748, &mpLib_803BD8A8,
    &mpLib_803BD900, &mpLib_803BD958, &mpLib_803BD9B0, &mpLib_803BDA60,
    &mpLib_803BDAB8, &mpLib_803BDB10, &mpLib_803BDB68, &mpLib_803BDBC0,
};
static struct mpLib_803BF248_t_x4* mpLib_803BE7F8[20] = {
    &mpLib_803BD3D8, &mpLib_803BD430, &mpLib_803BD488, &mpLib_803BD4E0,
    &mpLib_803BD538, &mpLib_803BD590, &mpLib_803BD5E8, &mpLib_803BD640,
    &mpLib_803BD698, &mpLib_803BD6F0, &mpLib_803BD748, &mpLib_803BD8A8,
    &mpLib_803BD900, &mpLib_803BD958, &mpLib_803BD9B0, &mpLib_803BDA60,
    &mpLib_803BDAB8, &mpLib_803BDB10, &mpLib_803BDB68, &mpLib_803BDBC0,
};
static struct mpLib_803BF248_t_x4* mpLib_803BE848[20] = {
    &mpLib_803BD3D8, &mpLib_803BD430, &mpLib_803BD488, &mpLib_803BD4E0,
    &mpLib_803BD538, &mpLib_803BD590, &mpLib_803BD5E8, &mpLib_803BD640,
    &mpLib_803BD698, &mpLib_803BD6F0, &mpLib_803BD748, &mpLib_803BD8A8,
    &mpLib_803BD900, &mpLib_803BD958, &mpLib_803BD9B0, &mpLib_803BDA60,
    &mpLib_803BDAB8, &mpLib_803BDB10, &mpLib_803BDB68, &mpLib_803BDBC0,
};
static struct mpLib_803BF248_t_x4* mpLib_803BE898[20] = {
    &mpLib_803BD3D8, &mpLib_803BD430, &mpLib_803BD488, &mpLib_803BD4E0,
    &mpLib_803BD538, &mpLib_803BD590, &mpLib_803BD5E8, &mpLib_803BD640,
    &mpLib_803BD698, &mpLib_803BD6F0, &mpLib_803BD748, &mpLib_803BD8A8,
    &mpLib_803BD900, &mpLib_803BD958, &mpLib_803BD9B0, &mpLib_803BDA60,
    &mpLib_803BDAB8, &mpLib_803BDB10, &mpLib_803BDB68, &mpLib_803BDBC0,
};
static struct mpLib_803BF248_t_x4* mpLib_803BE8E8[20] = {
    &mpLib_803BD3D8, &mpLib_803BD430, &mpLib_803BD488, &mpLib_803BD4E0,
    &mpLib_803BD538, &mpLib_803BD590, &mpLib_803BD5E8, &mpLib_803BD640,
    &mpLib_803BD698, &mpLib_803BD6F0, &mpLib_803BD748, &mpLib_803BD8A8,
    &mpLib_803BD900, &mpLib_803BD958, &mpLib_803BD9B0, &mpLib_803BDA60,
    &mpLib_803BDAB8, &mpLib_803BDB10, &mpLib_803BDB68, &mpLib_803BDBC0,
};
static struct mpLib_803BF248_t_x4* mpLib_803BE938[20] = {
    &mpLib_803BD3D8, &mpLib_803BD430, &mpLib_803BD488, &mpLib_803BD4E0,
    &mpLib_803BD538, &mpLib_803BD590, &mpLib_803BD5E8, &mpLib_803BD640,
    &mpLib_803BD698, &mpLib_803BD6F0, &mpLib_803BD748, &mpLib_803BD8A8,
    &mpLib_803BD900, &mpLib_803BD958, &mpLib_803BD9B0, &mpLib_803BDA60,
    &mpLib_803BDAB8, &mpLib_803BDB10, &mpLib_803BDB68, &mpLib_803BDBC0,
};
static struct mpLib_803BF248_t_x4* mpLib_803BE988[20] = {
    &mpLib_803BD3D8, &mpLib_803BD430, &mpLib_803BD488, &mpLib_803BD4E0,
    &mpLib_803BD538, &mpLib_803BD590, &mpLib_803BD5E8, &mpLib_803BD640,
    &mpLib_803BD698, &mpLib_803BD6F0, &mpLib_803BD748, &mpLib_803BD8A8,
    &mpLib_803BD900, &mpLib_803BD958, &mpLib_803BD9B0, &mpLib_803BDA60,
    &mpLib_803BDAB8, &mpLib_803BDB10, &mpLib_803BDB68, &mpLib_803BDBC0,
};
static struct mpLib_803BF248_t_x4* mpLib_803BE9D8[20] = {
    &mpLib_803BD3D8, &mpLib_803BD430, &mpLib_803BD488, &mpLib_803BD4E0,
    &mpLib_803BD538, &mpLib_803BD590, &mpLib_803BD5E8, &mpLib_803BD640,
    &mpLib_803BD698, &mpLib_803BD6F0, &mpLib_803BD748, &mpLib_803BD8A8,
    &mpLib_803BD900, &mpLib_803BD958, &mpLib_803BD9B0, &mpLib_803BDA60,
    &mpLib_803BDAB8, &mpLib_803BDB10, &mpLib_803BDB68, &mpLib_803BDBC0,
};
static struct mpLib_803BF248_t_x4* mpLib_803BEA28[20] = {
    &mpLib_803BD3D8, &mpLib_803BD430, &mpLib_803BD488, &mpLib_803BD4E0,
    &mpLib_803BD538, &mpLib_803BD590, &mpLib_803BD5E8, &mpLib_803BD640,
    &mpLib_803BD698, &mpLib_803BD6F0, &mpLib_803BD748, &mpLib_803BD8A8,
    &mpLib_803BD900, &mpLib_803BD958, &mpLib_803BD9B0, &mpLib_803BDA60,
    &mpLib_803BDAB8, &mpLib_803BDB10, &mpLib_803BDB68, &mpLib_803BDBC0,
};
static struct mpLib_803BF248_t_x4* mpLib_803BEA78[20] = {
    &mpLib_803BD3D8, &mpLib_803BD430, &mpLib_803BD488, &mpLib_803BD4E0,
    &mpLib_803BD538, &mpLib_803BD590, &mpLib_803BD5E8, &mpLib_803BD640,
    &mpLib_803BD698, &mpLib_803BD6F0, &mpLib_803BD748, &mpLib_803BD8A8,
    &mpLib_803BD900, &mpLib_803BD958, &mpLib_803BD9B0, &mpLib_803BDA60,
    &mpLib_803BDAB8, &mpLib_803BDB10, &mpLib_803BDB68, &mpLib_803BDBC0,
};
static struct mpLib_803BF248_t_x4* mpLib_803BEAC8[20] = {
    &mpLib_803BD3D8, &mpLib_803BD430, &mpLib_803BD488, &mpLib_803BD4E0,
    &mpLib_803BD538, &mpLib_803BD590, &mpLib_803BD5E8, &mpLib_803BD640,
    &mpLib_803BD698, &mpLib_803BD6F0, &mpLib_803BD748, &mpLib_803BD8A8,
    &mpLib_803BD900, &mpLib_803BD958, &mpLib_803BD9B0, &mpLib_803BDA60,
    &mpLib_803BDAB8, &mpLib_803BDB10, &mpLib_803BDB68, &mpLib_803BDBC0,
};
static struct mpLib_803BF248_t_x4* mpLib_803BEB18[20] = {
    &mpLib_803BD3D8, &mpLib_803BD430, &mpLib_803BD488, &mpLib_803BD4E0,
    &mpLib_803BD538, &mpLib_803BD590, &mpLib_803BD5E8, &mpLib_803BD640,
    &mpLib_803BD698, &mpLib_803BD6F0, &mpLib_803BD748, &mpLib_803BD8A8,
    &mpLib_803BD900, &mpLib_803BD958, &mpLib_803BD9B0, &mpLib_803BDA60,
    &mpLib_803BDAB8, &mpLib_803BDB10, &mpLib_803BDB68, &mpLib_803BDBC0,
};
static struct mpLib_803BF248_t_x4* mpLib_803BEB68[20] = {
    &mpLib_803BD3D8, &mpLib_803BD430, &mpLib_803BD488, &mpLib_803BD4E0,
    &mpLib_803BD538, &mpLib_803BD590, &mpLib_803BD5E8, &mpLib_803BD640,
    &mpLib_803BD698, &mpLib_803BD6F0, &mpLib_803BD748, &mpLib_803BD8A8,
    &mpLib_803BD900, &mpLib_803BD958, &mpLib_803BD9B0, &mpLib_803BDA60,
    &mpLib_803BDAB8, &mpLib_803BDB10, &mpLib_803BDB68, &mpLib_803BDBC0,
};
static struct mpLib_803BF248_t_x4* mpLib_803BEBB8[20] = {
    &mpLib_803BD3D8, &mpLib_803BD430, &mpLib_803BD488, &mpLib_803BD4E0,
    &mpLib_803BD538, &mpLib_803BD590, &mpLib_803BD5E8, &mpLib_803BD640,
    &mpLib_803BD698, &mpLib_803BD6F0, &mpLib_803BD748, &mpLib_803BD8A8,
    &mpLib_803BD900, &mpLib_803BD958, &mpLib_803BD9B0, &mpLib_803BDA60,
    &mpLib_803BDAB8, &mpLib_803BDB10, &mpLib_803BDB68, &mpLib_803BDBC0,
};
static struct mpLib_803BF248_t_x4* mpLib_803BEC08[20] = {
    &mpLib_803BD3D8, &mpLib_803BD430, &mpLib_803BD488, &mpLib_803BD4E0,
    &mpLib_803BD538, &mpLib_803BD590, &mpLib_803BD5E8, &mpLib_803BD640,
    &mpLib_803BD698, &mpLib_803BD6F0, &mpLib_803BD748, &mpLib_803BD8A8,
    &mpLib_803BD900, &mpLib_803BD958, &mpLib_803BD9B0, &mpLib_803BDA60,
    &mpLib_803BDAB8, &mpLib_803BDB10, &mpLib_803BDB68, &mpLib_803BDBC0,
};
static struct mpLib_803BF248_t_x4* mpLib_803BEC58[20] = {
    &mpLib_803BD3D8, &mpLib_803BD430, &mpLib_803BD488, &mpLib_803BD4E0,
    &mpLib_803BD538, &mpLib_803BD590, &mpLib_803BD5E8, &mpLib_803BD640,
    &mpLib_803BD698, &mpLib_803BD6F0, &mpLib_803BD748, &mpLib_803BD8A8,
    &mpLib_803BD900, &mpLib_803BD958, &mpLib_803BD9B0, &mpLib_803BDA60,
    &mpLib_803BDAB8, &mpLib_803BDB10, &mpLib_803BDB68, &mpLib_803BDBC0,
};
static struct mpLib_803BF248_t_x4* mpLib_803BECA8[20] = {
    &mpLib_803BD3D8, &mpLib_803BD430, &mpLib_803BD488, &mpLib_803BD4E0,
    &mpLib_803BD538, &mpLib_803BD590, &mpLib_803BD5E8, &mpLib_803BD640,
    &mpLib_803BD698, &mpLib_803BD6F0, &mpLib_803BD748, &mpLib_803BD8A8,
    &mpLib_803BD900, &mpLib_803BD958, &mpLib_803BD9B0, &mpLib_803BDA60,
    &mpLib_803BDAB8, &mpLib_803BDB10, &mpLib_803BDB68, &mpLib_803BDBC0,
};
static struct mpLib_803BF248_t_x4* mpLib_803BECF8[20] = {
    &mpLib_803BD3D8, &mpLib_803BD430, &mpLib_803BD488, &mpLib_803BD4E0,
    &mpLib_803BD538, &mpLib_803BD590, &mpLib_803BD5E8, &mpLib_803BD640,
    &mpLib_803BD698, &mpLib_803BD6F0, &mpLib_803BD748, &mpLib_803BD8A8,
    &mpLib_803BD900, &mpLib_803BD958, &mpLib_803BD9B0, &mpLib_803BDA60,
    &mpLib_803BDAB8, &mpLib_803BDB10, &mpLib_803BDB68, &mpLib_803BDBC0,
};
static struct mpLib_803BF248_t_x4* mpLib_803BED48[20] = {
    &mpLib_803BD3D8, &mpLib_803BD430, &mpLib_803BD488, &mpLib_803BD4E0,
    &mpLib_803BD538, &mpLib_803BD590, &mpLib_803BD5E8, &mpLib_803BD640,
    &mpLib_803BD698, &mpLib_803BD6F0, &mpLib_803BD748, &mpLib_803BD8A8,
    &mpLib_803BD900, &mpLib_803BD958, &mpLib_803BD9B0, &mpLib_803BDA60,
    &mpLib_803BDAB8, &mpLib_803BDB10, &mpLib_803BDB68, &mpLib_803BDBC0,
};
static struct mpLib_803BF248_t_x4* mpLib_803BED98[20] = {
    &mpLib_803BD3D8, &mpLib_803BD430, &mpLib_803BD488, &mpLib_803BD4E0,
    &mpLib_803BD538, &mpLib_803BD590, &mpLib_803BD5E8, &mpLib_803BD640,
    &mpLib_803BD698, &mpLib_803BD6F0, &mpLib_803BD748, &mpLib_803BD8A8,
    &mpLib_803BD900, &mpLib_803BD958, &mpLib_803BD9B0, &mpLib_803BDA60,
    &mpLib_803BDAB8, &mpLib_803BDB10, &mpLib_803BDB68, &mpLib_803BDBC0,
};
static struct mpLib_803BF248_t_x4* mpLib_803BEDE8[20] = {
    &mpLib_803BD3D8, &mpLib_803BD430, &mpLib_803BD488, &mpLib_803BD4E0,
    &mpLib_803BD538, &mpLib_803BD590, &mpLib_803BD5E8, &mpLib_803BD640,
    &mpLib_803BD698, &mpLib_803BD6F0, &mpLib_803BD748, &mpLib_803BD8A8,
    &mpLib_803BD900, &mpLib_803BD958, &mpLib_803BD9B0, &mpLib_803BDA60,
    &mpLib_803BDAB8, &mpLib_803BDB10, &mpLib_803BDB68, &mpLib_803BDBC0,
};
static struct mpLib_803BF248_t_x4* mpLib_803BEE38[20] = {
    &mpLib_803BD3D8, &mpLib_803BD430, &mpLib_803BD488, &mpLib_803BD4E0,
    &mpLib_803BD538, &mpLib_803BD590, &mpLib_803BD5E8, &mpLib_803BD640,
    &mpLib_803BD698, &mpLib_803BD6F0, &mpLib_803BD748, &mpLib_803BD8A8,
    &mpLib_803BD900, &mpLib_803BD958, &mpLib_803BD9B0, &mpLib_803BDA60,
    &mpLib_803BDAB8, &mpLib_803BDB10, &mpLib_803BDB68, &mpLib_803BDBC0,
};
static struct mpLib_803BF248_t_x4* mpLib_803BEE88[20] = {
    &mpLib_803BD3D8, &mpLib_803BD430, &mpLib_803BD488, &mpLib_803BD4E0,
    &mpLib_803BD538, &mpLib_803BD590, &mpLib_803BD5E8, &mpLib_803BD640,
    &mpLib_803BD698, &mpLib_803BD6F0, &mpLib_803BD748, &mpLib_803BD8A8,
    &mpLib_803BD900, &mpLib_803BD958, &mpLib_803BD9B0, &mpLib_803BDA60,
    &mpLib_803BDAB8, &mpLib_803BDB10, &mpLib_803BDB68, &mpLib_803BDBC0,
};
static struct mpLib_803BF248_t_x4* mpLib_803BEED8[20] = {
    &mpLib_803BD3D8, &mpLib_803BD430, &mpLib_803BD488, &mpLib_803BD4E0,
    &mpLib_803BD538, &mpLib_803BD590, &mpLib_803BD5E8, &mpLib_803BD640,
    &mpLib_803BD698, &mpLib_803BD6F0, &mpLib_803BD748, &mpLib_803BD8A8,
    &mpLib_803BD900, &mpLib_803BD958, &mpLib_803BD9B0, &mpLib_803BDA60,
    &mpLib_803BDAB8, &mpLib_803BDB10, &mpLib_803BDB68, &mpLib_803BDBC0,
};
static struct mpLib_803BF248_t_x4* mpLib_803BEF28[20] = {
    &mpLib_803BD3D8, &mpLib_803BD430, &mpLib_803BD488, &mpLib_803BD4E0,
    &mpLib_803BD538, &mpLib_803BD590, &mpLib_803BD5E8, &mpLib_803BD640,
    &mpLib_803BD698, &mpLib_803BD6F0, &mpLib_803BD748, &mpLib_803BD8A8,
    &mpLib_803BD900, &mpLib_803BD958, &mpLib_803BD9B0, &mpLib_803BDA60,
    &mpLib_803BDAB8, &mpLib_803BDB10, &mpLib_803BDB68, &mpLib_803BDBC0,
};
static struct mpLib_803BF248_t_x4* mpLib_803BEF78[20] = {
    &mpLib_803BD3D8, &mpLib_803BD430, &mpLib_803BD488, &mpLib_803BD4E0,
    &mpLib_803BD538, &mpLib_803BD590, &mpLib_803BD5E8, &mpLib_803BD640,
    &mpLib_803BD698, &mpLib_803BD6F0, &mpLib_803BD748, &mpLib_803BD8A8,
    &mpLib_803BD900, &mpLib_803BD958, &mpLib_803BD9B0, &mpLib_803BDA60,
    &mpLib_803BDAB8, &mpLib_803BDB10, &mpLib_803BDB68, &mpLib_803BDBC0,
};
static struct mpLib_803BF248_t_x4* mpLib_803BEFC8[20] = {
    &mpLib_803BD3D8, &mpLib_803BD430, &mpLib_803BD488, &mpLib_803BD4E0,
    &mpLib_803BD538, &mpLib_803BD590, &mpLib_803BD5E8, &mpLib_803BD640,
    &mpLib_803BD698, &mpLib_803BD6F0, &mpLib_803BD748, &mpLib_803BD8A8,
    &mpLib_803BD900, &mpLib_803BD958, &mpLib_803BD9B0, &mpLib_803BDA60,
    &mpLib_803BDAB8, &mpLib_803BDB10, &mpLib_803BDB68, &mpLib_803BDBC0,
};
static struct mpLib_803BF248_t_x4* mpLib_803BF018[20] = {
    &mpLib_803BD3D8, &mpLib_803BD430, &mpLib_803BD488, &mpLib_803BD4E0,
    &mpLib_803BD538, &mpLib_803BD590, &mpLib_803BD5E8, &mpLib_803BD640,
    &mpLib_803BD698, &mpLib_803BD6F0, &mpLib_803BD748, &mpLib_803BD8A8,
    &mpLib_803BD900, &mpLib_803BD958, &mpLib_803BD9B0, &mpLib_803BDA60,
    &mpLib_803BDAB8, &mpLib_803BDB10, &mpLib_803BDB68, &mpLib_803BDBC0,
};
static struct mpLib_803BF248_t_x4* mpLib_803BF068[20] = {
    &mpLib_803BD3D8, &mpLib_803BD430, &mpLib_803BD488, &mpLib_803BD4E0,
    &mpLib_803BD538, &mpLib_803BD590, &mpLib_803BD5E8, &mpLib_803BD640,
    &mpLib_803BD698, &mpLib_803BD6F0, &mpLib_803BD748, &mpLib_803BD8A8,
    &mpLib_803BD900, &mpLib_803BD958, &mpLib_803BD9B0, &mpLib_803BDA60,
    &mpLib_803BDAB8, &mpLib_803BDB10, &mpLib_803BDB68, &mpLib_803BDBC0,
};
static struct mpLib_803BF248_t_x4* mpLib_803BF0B8[20] = {
    &mpLib_803BD3D8, &mpLib_803BD430, &mpLib_803BD488, &mpLib_803BD4E0,
    &mpLib_803BD538, &mpLib_803BD590, &mpLib_803BD5E8, &mpLib_803BD640,
    &mpLib_803BD698, &mpLib_803BD6F0, &mpLib_803BD748, &mpLib_803BD8A8,
    &mpLib_803BD900, &mpLib_803BD958, &mpLib_803BD9B0, &mpLib_803BDA60,
    &mpLib_803BDAB8, &mpLib_803BDB10, &mpLib_803BDB68, &mpLib_803BDBC0,
};
static struct mpLib_803BF248_t_x4* mpLib_803BF108[20] = {
    &mpLib_803BD3D8, &mpLib_803BD430, &mpLib_803BD488, &mpLib_803BD4E0,
    &mpLib_803BD538, &mpLib_803BD590, &mpLib_803BD5E8, &mpLib_803BD640,
    &mpLib_803BD698, &mpLib_803BD6F0, &mpLib_803BD748, &mpLib_803BD8A8,
    &mpLib_803BD900, &mpLib_803BD958, &mpLib_803BD9B0, &mpLib_803BDA60,
    &mpLib_803BDAB8, &mpLib_803BDB10, &mpLib_803BDB68, &mpLib_803BDBC0,
};
static struct mpLib_803BF248_t_x4* mpLib_803BF158[20] = {
    &mpLib_803BD3D8, &mpLib_803BD430, &mpLib_803BD488, &mpLib_803BD4E0,
    &mpLib_803BD538, &mpLib_803BD590, &mpLib_803BD5E8, &mpLib_803BD640,
    &mpLib_803BD698, &mpLib_803BD6F0, &mpLib_803BD748, &mpLib_803BD8A8,
    &mpLib_803BD900, &mpLib_803BD958, &mpLib_803BD9B0, &mpLib_803BDA60,
    &mpLib_803BDAB8, &mpLib_803BDB10, &mpLib_803BDB68, &mpLib_803BDBC0,
};
static struct mpLib_803BF248_t_x4* mpLib_803BF1A8[20] = {
    &mpLib_803BD3D8, &mpLib_803BD430, &mpLib_803BD488, &mpLib_803BD4E0,
    &mpLib_803BD538, &mpLib_803BD590, &mpLib_803BD5E8, &mpLib_803BD640,
    &mpLib_803BD698, &mpLib_803BD6F0, &mpLib_803BD748, &mpLib_803BD8A8,
    &mpLib_803BD900, &mpLib_803BD958, &mpLib_803BD9B0, &mpLib_803BDA60,
    &mpLib_803BDAB8, &mpLib_803BDB10, &mpLib_803BDB68, &mpLib_803BDBC0,
};
static struct mpLib_803BF248_t_x4* mpLib_803BF1F8[20] = {
    &mpLib_803BD3D8, &mpLib_803BD430, &mpLib_803BD488, &mpLib_803BD4E0,
    &mpLib_803BD538, &mpLib_803BD590, &mpLib_803BD5E8, &mpLib_803BD640,
    &mpLib_803BD698, &mpLib_803BD6F0, &mpLib_803BD748, &mpLib_803BD8A8,
    &mpLib_803BD900, &mpLib_803BD958, &mpLib_803BD9B0, &mpLib_803BDA60,
    &mpLib_803BDAB8, &mpLib_803BDB10, &mpLib_803BDB68, &mpLib_803BDBC0,
};

// clang-format off
static struct mpLib_803BF248_t mpLib_803BF248[0x47] = {
    { InternalStageID_Unk00,    &mpLib_803BDC18 },
    { InternalStageID_Unk01,    &mpLib_803BDC68 },
    { CASTLE,                   &mpLib_803BDCB8 },
    { RCRUISE,                  &mpLib_803BDD08 },
    { KONGO,                    &mpLib_803BDD58 },
    { GARDEN,                   &mpLib_803BDDA8 },
    { GREATBAY,                 &mpLib_803BDDF8 },
    { SHRINE,                   &mpLib_803BDE48 },
    { ZEBES,                    &mpLib_803BDE98 },
    { KRAID,                    &mpLib_803BDEE8 },
    { STORY,                    &mpLib_803BDF38 },
    { YORSTER,                  &mpLib_803BDF88 },
    { IZUMI,                    &mpLib_803BDFD8 },
    { GREENS,                   &mpLib_803BE028 },
    { CORNERIA,                 &mpLib_803BE078 },
    { VENOM,                    &mpLib_803BE0C8 },
    { PSTADIUM,                 &mpLib_803BE118 },
    { PURA,                     &mpLib_803BE168 },
    { MUTECITY,                 &mpLib_803BE1B8 },
    { BIGBLUE,                  &mpLib_803BE208 },
    { ONETT,                    &mpLib_803BE258 },
    { FOURSIDE,                 &mpLib_803BE2A8 },
    { ICEMTN,                   &mpLib_803BE2F8 },
    { InternalStageID_Unk23,    &mpLib_803BE348 },
    { INISHIE1,                 &mpLib_803BE398 },
    { INISHIE2,                 &mpLib_803BE3E8 },
    { InternalStageID_Unk26,    &mpLib_803BE438 },
    { FLATZONE,                 &mpLib_803BE488 },
    { OLDPUPUPU,                &mpLib_803BE4D8 },
    { OLDYOSHI,                 &mpLib_803BE528 },
    { OLDKONGO,                 &mpLib_803BE578 },
    { SHRINEROUTE,              &mpLib_803BE5C8 },
    { STAGEKIND_UNK32,          &mpLib_803BE618 },
    { STAGEKIND_UNK33,          &mpLib_803BE668 },
    { STAGEKIND_UNK34,          &mpLib_803BE6B8 },
    { STAGEKIND_UNK35,          &mpLib_803BE708 },
    { STAGEKIND_UNK36,          &mpLib_803BE758 },
    { STAGEKIND_UNK37,          &mpLib_803BE7A8 },
    { STAGEKIND_UNK38,          &mpLib_803BE7F8 },
    { STAGEKIND_UNK39,          &mpLib_803BE848 },
    { 0x28,                     &mpLib_803BE898 },
    { 0x29,                     &mpLib_803BE8E8 },
    { 0x2A,                     &mpLib_803BE938 },
    { 0x2B,                     &mpLib_803BE988 },
    { 0x2C,                     &mpLib_803BE9D8 },
    { 0x2D,                     &mpLib_803BEA28 },
    { 0x2E,                     &mpLib_803BEA78 },
    { 0x2F,                     &mpLib_803BEAC8 },
    { 0x30,                     &mpLib_803BEB18 },
    { 0x31,                     &mpLib_803BEB68 },
    { 0x32,                     &mpLib_803BEBB8 },
    { 0x33,                     &mpLib_803BEC08 },
    { 0x34,                     &mpLib_803BEC58 },
    { 0x35,                     &mpLib_803BECA8 },
    { 0x36,                     &mpLib_803BECF8 },
    { 0x37,                     &mpLib_803BED48 },
    { 0x38,                     &mpLib_803BED98 },
    { 0x39,                     &mpLib_803BEDE8 },
    { 0x3A,                     &mpLib_803BEE38 },
    { 0x3B,                     &mpLib_803BEE88 },
    { 0x3C,                     &mpLib_803BEED8 },
    { 0x3D,                     &mpLib_803BEF28 },
    { 0x3E,                     &mpLib_803BEF78 },
    { 0x3F,                     &mpLib_803BEFC8 },
    { 0x40,                     &mpLib_803BF018 },
    { 0x41,                     &mpLib_803BF068 },
    { 0x42,                     &mpLib_803BF0B8 },
    { HOMERUN,                  &mpLib_803BF108 },
    { 0x44,                     &mpLib_803BF158 },
    { 0x45,                     &mpLib_803BF1A8 },
    { 0x46,                     &mpLib_803BF1F8 },
};
// clang-format on

float mpLib_800569EC(u32 unk)
{
    return (*mpLib_803BF248[stage_info.internal_stage_id].x4)[(u8) unk]->x0;
}

int* mpLib_80056A1C(int arg0, int* arg1)
{
    struct mpLib_803BF248_t_x4* temp =
        (*mpLib_803BF248[stage_info.internal_stage_id].x4)[(u8) arg0];
    *arg1 = temp->x14[0];
    return temp->x4;
}

int mpLib_80056A54(int arg0, int* arg1)
{
    struct mpLib_803BF248_t_x4* temp =
        (*mpLib_803BF248[stage_info.internal_stage_id].x4)[(u8) arg0];
    *arg1 = temp->x14[2];
    return temp->x14[1];
}

int* mpLib_80056A8C(int arg0, int* arg1)
{
    struct mpLib_803BF248_t_x4* temp =
        (*mpLib_803BF248[stage_info.internal_stage_id].x4)[(u8) arg0];
    *arg1 = temp->x30[0];
    return temp->x20;
}

int mpLib_80056AC4(int arg0, int* arg1)
{
    struct mpLib_803BF248_t_x4* temp =
        (*mpLib_803BF248[stage_info.internal_stage_id].x4)[(u8) arg0];
    *arg1 = temp->x30[2];
    return temp->x30[1];
}

int* mpLib_80056AFC(int arg0, int* arg1)
{
    struct mpLib_803BF248_t_x4* temp =
        (*mpLib_803BF248[stage_info.internal_stage_id].x4)[(u8) arg0];
    *arg1 = temp->x4C[0];
    return temp->x3C;
}

int mpLib_80056B34(int arg0, int* arg1)
{
    struct mpLib_803BF248_t_x4* temp =
        (*mpLib_803BF248[stage_info.internal_stage_id].x4)[(u8) arg0];
    *arg1 = temp->x4C[2];
    return temp->x4C[1];
}

int mpJointFromLine(int line_id)
{
    if (line_id != -1) {
        int i;
        int v0_idx;
        CollJoint* joint;
        int count;
        LINEID_CHECK(5459, line_id);
        v0_idx = groundCollLine[line_id].x0->v0_idx;
        count = mpLib_804D64B4->x28;
        joint = groundCollJoint;
        for (i = 0; i < count; i++) {
            if (joint->coll_info->vtx_start <= v0_idx &&
                v0_idx <
                    joint->coll_info->vtx_start + joint->coll_info->vtx_count)
            {
                return joint - groundCollJoint;
            }
            joint++;
        }
    }

    return -1;
}

bool mpLib_80056C54(int line_id, Vec3* pos, int* line_id_out, Vec3* vec_out,
                    u32* flags_out, Vec3* normal_out, f32 var_f25, f32 arg7,
                    f32 arg8, f32 arg9)
{
    float sp64;
    Vec3 sp58;
    Vec3 sp4C;
    float dist_f28;
    float total_dist_f27;
    float x_f2;
    float y_f0;
    int result_r30;
    int new_id_r5;
    u32 flags_r0;

    result_r30 = true;
    if (!mpLib_80054ED8(line_id)) {
        return false;
    }

    if (mpLib_8004DD90_Floor(line_id, pos, &sp64, NULL, NULL) == -1) {
        return false;
    }
    sp58 = *pos;
    sp58.y += sp64;
    if (var_f25 > 0.0F) {
        while (true) {
            mpLineGetV1Pos(line_id, &sp4C);
            x_f2 = SQ(sp58.x - sp4C.x);
            y_f0 = SQ(sp58.y - sp4C.y);
            dist_f28 = sqrtf(x_f2 + y_f0);
            flags_r0 = mpLineGetKind(line_id);
            if (flags_r0 & 0xC) {
                total_dist_f27 += dist_f28;
                if (total_dist_f27 > arg7) {
                    result_r30 = false;
                } else {
                    goto block_30;
                }
            } else if (flags_r0 & 2) {
                result_r30 = false;
            } else {
                total_dist_f27 = 0.0F;
            block_30:
                if (!(dist_f28 > var_f25)) {
                    new_id_r5 = mpLineGetNext(line_id);
                    if (new_id_r5 == -1) {
                        result_r30 = false;
                    } else {
                        var_f25 -= dist_f28;
                        line_id = new_id_r5;
                        sp58 = sp4C;
                        continue;
                    }
                }
            }

            break;
        }
    } else {
        var_f25 = -var_f25;
        while (true) {
            mpLineGetV0Pos(line_id, &sp4C);
            x_f2 = SQ(sp58.x - sp4C.x);
            y_f0 = SQ(sp58.y - sp4C.y);
            dist_f28 = sqrtf(x_f2 + y_f0);
            flags_r0 = mpLineGetKind(line_id);
            if (flags_r0 & 0xC) {
                total_dist_f27 += dist_f28;
                if (total_dist_f27 > arg7) {
                    result_r30 = false;
                } else {
                    goto block_55;
                }
            } else if (flags_r0 & 2) {
                result_r30 = false;
            } else {
                total_dist_f27 = 0.0F;
            block_55:
                if (!(dist_f28 > var_f25)) {
                    new_id_r5 = mpLineGetPrev(line_id);
                    if (new_id_r5 == -1) {
                        result_r30 = false;
                    } else {
                        var_f25 -= dist_f28;
                        line_id = new_id_r5;
                        sp58 = sp4C;
                        continue;
                    }
                }
            }
            break;
        }
    }
    if (line_id != -1) {
        if (!(mpLineGetKind(line_id) & 1)) {
            line_id = -1;
        }
    }
    if (line_id_out != NULL) {
        *line_id_out = line_id;
    }
    if (line_id != -1) {
        if (flags_out != NULL) {
            *flags_out = mpLineGetFlags(line_id);
        }
        if (normal_out != NULL) {
            mpLineGetNormal(line_id, normal_out);
        }
    }
    if (vec_out != NULL) {
        if (result_r30) {
            if (dist_f28 < 0.0001) {
                *vec_out = sp58;
            } else {
                float temp_f2_5 = var_f25 / dist_f28;
                vec_out->x = (temp_f2_5 * (sp4C.x - sp58.x)) + sp58.x;
                vec_out->y = (temp_f2_5 * (sp4C.y - sp58.y)) + sp58.y;
                vec_out->z = (temp_f2_5 * (sp4C.z - sp58.z)) + sp58.z;
            }
        } else {
            *vec_out = sp4C;
        }
    }
    return result_r30;
}

void mpLib_80057424(int joint_id)
{
    CollJoint* joint = &groundCollJoint[joint_id];
    CollInfo* coll_info = joint->coll_info;
    u32 count = coll_info->vtx_count;
    s16 start = coll_info->vtx_start;
    int new_var;
    CollVtx* vtx = &groundCollVtx[start];
    for (joint_id = 0; joint_id < (new_var = count); joint_id++) {
        vtx->x10 = vtx->pos.x;
        vtx->x14 = vtx->pos.y;
        vtx++;
    }
}

void mpLib_80057528(int line_id)
{
    int joint_id = mpJointFromLine(line_id);
    if (joint_id != -1) {
        CollLine* line = &groundCollLine[line_id];
        CollJoint* joint = &groundCollJoint[joint_id];
        line->flags |= 0x10000;
        mpIsland_8005B334(joint_id, joint->coll_info->vtx_start,
                          joint->coll_info->vtx_count,
                          !(joint->flags & 0x800));
        joint->xE = true;
    }
}

void mpLib_800575B0(int line_id)
{
    int joint_id = mpJointFromLine(line_id);
    if (joint_id != -1) {
        CollLine* line = &groundCollLine[line_id];
        CollJoint* joint = &groundCollJoint[joint_id];
        line->flags &= ~0x10000;
        mpIsland_8005B334(joint_id, joint->coll_info->vtx_start,
                          joint->coll_info->vtx_count,
                          !(joint->flags & 0x800));
        joint->xE = true;
    }
}

void mpLib_80057638(int joint_id)
{
    CollJoint* joint;
    CollInfo* coll_info;
    int count_r7;
    CollLine* line_r6;

    joint = &groundCollJoint[joint_id];
    if (joint->flags & 0x10000) {
        return;
    }

    joint->flags |= 0x10000;
    if (mpLib_804D64C4 == NULL) {
        mpLib_804D64C4 = joint;
    } else {
        mpLib_804D64C8->next = joint;
    }
    mpLib_804D64C8 = joint;
    joint->next = NULL;

    coll_info = joint->coll_info;
    count_r7 = coll_info->floor_count;
    line_r6 = &groundCollLine[coll_info->floor_start];
    while (count_r7-- > 0) {
        line_r6->flags |= 0x10000;
        line_r6++;
    }

    coll_info = joint->coll_info;
    count_r7 = coll_info->ceiling_count;
    line_r6 = &groundCollLine[coll_info->ceiling_start];
    while (count_r7-- > 0) {
        line_r6->flags |= 0x10000;
        line_r6++;
    }

    coll_info = joint->coll_info;
    count_r7 = coll_info->left_wall_count;
    line_r6 = &groundCollLine[coll_info->left_wall_start];
    while (count_r7-- > 0) {
        line_r6->flags |= 0x10000;
        line_r6++;
    }

    coll_info = joint->coll_info;
    count_r7 = coll_info->right_wall_count;
    line_r6 = &groundCollLine[coll_info->right_wall_start];
    while (count_r7-- > 0) {
        line_r6->flags |= 0x10000;
        line_r6++;
    }

    coll_info = joint->coll_info;
    count_r7 = coll_info->dynamic_count;
    line_r6 = &groundCollLine[coll_info->dynamic_start];
    while (count_r7-- > 0) {
        line_r6->flags |= 0x10000;
        line_r6++;
    }

    mpLib_80057424(joint_id);
    coll_info = joint->coll_info;
    mpIsland_8005B334(joint_id, coll_info->vtx_start, coll_info->vtx_count,
                      !(joint->flags & 0x800));
    joint->xE = true;
}

void mpLib_80057B4C(CollJoint* arg0)
{
    CollJoint* cur;

    if (arg0 == mpLib_804D64C4) {
        if (arg0 == mpLib_804D64C8) {
            mpLib_804D64C8 = NULL;
            mpLib_804D64C4 = NULL;
        } else {
            mpLib_804D64C4 = mpLib_804D64C4->next;
        }
        return;
    }

    for (cur = mpLib_804D64C4; cur != NULL; cur = cur->next) {
        if (cur->next == arg0) {
            if (arg0 == mpLib_804D64C8) {
                mpLib_804D64C8 = cur;
            }
            cur->next = cur->next->next;
            return;
        }
    }
}

void mpLib_80057BC0(int joint_id)
{
    CollJoint* joint;
    CollInfo* coll_info;
    int count;
    int start;
    CollLine* line_r6;

    joint = &groundCollJoint[joint_id];
    if (!(joint->flags & 0x10000)) {
        return;
    }

    joint->flags &= ~0x10000;
    mpLib_80057B4C(joint);

    coll_info = joint->coll_info;
    count = coll_info->floor_count;
    line_r6 = &groundCollLine[coll_info->floor_start];
    while (count-- > 0) {
        line_r6->flags &= ~0x10000;
        line_r6++;
    }

    coll_info = joint->coll_info;
    count = coll_info->ceiling_count;
    line_r6 = &groundCollLine[coll_info->ceiling_start];
    while (count-- > 0) {
        line_r6->flags &= ~0x10000;
        line_r6++;
    }

    coll_info = joint->coll_info;
    count = coll_info->left_wall_count;
    line_r6 = &groundCollLine[coll_info->left_wall_start];
    while (count-- > 0) {
        line_r6->flags &= ~0x10000;
        line_r6++;
    }

    coll_info = joint->coll_info;
    count = coll_info->right_wall_count;
    line_r6 = &groundCollLine[coll_info->right_wall_start];
    while (count-- > 0) {
        line_r6->flags &= ~0x10000;
        line_r6++;
    }

    coll_info = joint->coll_info;
    count = coll_info->dynamic_count;
    line_r6 = &groundCollLine[coll_info->dynamic_start];
    while (count-- > 0) {
        line_r6->flags &= ~0x10000;
        line_r6++;
    }
    coll_info = joint->coll_info;
    mpIsland_8005B334(joint_id, coll_info->vtx_start, coll_info->vtx_count,
                      false);
    joint->xE = true;
}

void mpLib_80057FDC(int joint_id)
{
    CollInfo* coll_info;
    bool var_r6 = false;
    CollJoint* joint = &groundCollJoint[joint_id];

    joint->flags &= ~0x800;
    if (!(joint->flags & 0x40800) && (joint->flags & 0x10000)) {
        var_r6 = true;
    }
    coll_info = joint->coll_info;
    mpIsland_8005B334(joint_id, coll_info->vtx_start, coll_info->vtx_count,
                      var_r6);
}

void mpLib_80058044(int joint_id)
{
    CollInfo* temp_r5;
    bool var_r6 = false;
    CollJoint* temp_r7 = &groundCollJoint[joint_id];

    temp_r7->flags |= 0x800;
    if (!(temp_r7->flags & 0x40800) && (temp_r7->flags & 0x10000)) {
        var_r6 = true;
    }
    temp_r5 = temp_r7->coll_info;
    mpIsland_8005B334(joint_id, temp_r5->vtx_start, temp_r5->vtx_count,
                      var_r6);
}

void mpLib_800580AC(int joint_id)
{
    CollJoint* joint = &groundCollJoint[joint_id];
    joint->flags |= 0x400;
}

void mpJointSetCb1(int joint_id, Ground* arg1, mpLib_Callback cb)
{
    CollJoint* joint = &groundCollJoint[joint_id];
    joint->x24 = cb;
    joint->x28 = arg1;
}

void mpJointClearCb1(int joint_id)
{
    CollJoint* joint = &groundCollJoint[joint_id];
    joint->x24 = NULL;
    joint->x28 = NULL;
}

void mpJointGetCb1(int joint_id, mpLib_Callback* arg1, Ground** arg2)
{
    CollJoint* joint = &groundCollJoint[joint_id];
    *arg1 = joint->x24;
    *arg2 = joint->x28;
}

void mpLib_8005811C(CollData* coll, int ledge_id)
{
    if (ledge_id != -1) {
        int joint_id = mpJointFromLine(ledge_id);
        if (joint_id != -1) {
            mpLib_Callback cb = groundCollJoint[joint_id].x24;
            Ground* gp = groundCollJoint[joint_id].x28;
            if (cb != NULL) {
                cb(gp, joint_id, coll, coll->x50, 3, 0.0F);
            }
        }
    }
}

void mpJointSetCb2(int joint_id, Ground* arg1, mpLib_Callback arg2)
{
    CollJoint* joint = &groundCollJoint[joint_id];
    joint->x2C = arg2;
    joint->x30 = arg1;
}

void mpJointGetCb2(int joint_id, mpLib_Callback* cb, Ground** gr)
{
    CollJoint* joint = &groundCollJoint[joint_id];
    *cb = joint->x2C;
    *gr = joint->x30;
}

void mpLib_800581DC(int joint_id0, int joint_id1)
{
    struct pair {
        s16 start;
        s16 count;
    };
    CollJoint* j0_r9;
    CollJoint* j1_r10;
    int i;
    CollInfo* cd0;
    int vcount0;
    CollVtx* v0_r29;
    int vstart0;

    j0_r9 = &groundCollJoint[joint_id0];
    j1_r10 = &groundCollJoint[joint_id1];
    for (i = 0; i < 5; i++) {
        int j;
        int idx;
        struct pair* pair; /* r4 */
        int count;         /* r0 */
        int temp;          /* r0 */
        int start;         /* r8 */
        CollLine* lines;   /* r5 */

        pair = (struct pair*) j0_r9->coll_info + i;
        count = pair->count;
        start = pair->start;
        idx = start;
        lines = &groundCollLine[start];
        for (j = 0; j < count; j++, idx++) {
            temp = lines[j].x0->prev_id1;
            if (temp != -1) {
                temp = groundCollLine[temp].x0->next_id1;
                if (temp != -1 && idx != temp) {
                    lines[j].x0->prev_id1 = -1;
                }
            }
            temp = lines[j].x0->next_id1;
            if (temp != -1) {
                temp = groundCollLine[temp].x0->prev_id1;
                if (temp != -1 && idx != temp) {
                    lines[j].x0->next_id1 = -1;
                }
            }
        }

        pair = (struct pair*) j1_r10->coll_info + i;
        count = pair->count;
        start = pair->start;
        idx = start;
        lines = &groundCollLine[start];
        for (j = 0; j < count; j++, idx++) {
            temp = lines->x0->prev_id1;
            if (temp != -1) {
                temp = groundCollLine[temp].x0->next_id1;
                if (temp != -1 && idx != temp) {
                    lines->x0->prev_id1 = -1;
                }
            }
            temp = lines->x0->next_id1;
            if (temp != -1) {
                temp = groundCollLine[temp].x0->prev_id1;
                if (temp != -1 && idx != temp) {
                    lines->x0->next_id1 = -1;
                }
            }
            lines++;
        }
    }

    cd0 = j0_r9->coll_info;   /*  r3 */
    vstart0 = cd0->vtx_start; /*  r4 */
    vcount0 = cd0->vtx_count; /* r31 */

    v0_r29 = &groundCollVtx[vstart0];
    // for every pair of verts
    for (i = 0; i < vcount0; i++) {
        int v;       /* r28 */
        int vcount1; /* r27 */
        int vid_r26; /* r26 */
        int vid;
        int vstart1_r4;
        vstart1_r4 = j1_r10->coll_info->vtx_start;
        vcount1 = j1_r10->coll_info->vtx_count;
        vid = vstart1_r4;
        vid_r26 = vstart1_r4;
        for (v = 0; v < vcount1; v++, vid++, vid_r26++) {
            int var_r25;

            // ensure they are nearby
            if (!(ABS(v0_r29[i].pos.x - groundCollVtx[vid].pos.x) < 2.0) ||
                !(ABS(v0_r29[i].pos.y - groundCollVtx[vid].pos.y) < 2.0))
            {
                continue;
            }

            // find every line with the first vert
            for (var_r25 = 0; var_r25 < 5; var_r25++) {
                int i_r23;
                int lstart_r24;
                int lcount_r22;
                CollLine* lines; /* r5 */
                lstart_r24 = ((struct pair*) j0_r9->coll_info)[var_r25].start;
                lcount_r22 = ((struct pair*) j0_r9->coll_info)[var_r25].count;
                lines = &groundCollLine[lstart_r24];
                for (i_r23 = 0; i_r23 < lcount_r22; i_r23++) {
                    int j;
                    s16 lstart_r20;
                    s16 lcount_r17;
                    CollLine* iter_r3;
                    if (vstart0 + i == lines[i_r23].x0->v0_idx) {
                        // if the first vert is that line's v0
                        // find every line with the second vert as v1
                        for (j = 0; j < 5; j++) {
                            int k;
                            lstart_r20 =
                                ((struct pair*) j1_r10->coll_info)[j].start;
                            lcount_r17 =
                                ((struct pair*) j1_r10->coll_info)[j].count;
                            iter_r3 = &groundCollLine[lstart_r20];
                            for (k = 0; k < lcount_r17; k++) {
                                if (vid_r26 == iter_r3->x0->v1_idx) {
                                    lines[i_r23].x0->prev_id1 = lstart_r20 + k;
                                    iter_r3->x0->next_id1 = lstart_r24;
                                }
                                iter_r3++;
                            }
                        }
                    } else if (vstart0 + i == lines[i_r23].x0->v1_idx) {
                        // else if the first vert is that line's v1
                        // find every line with the second vert as v0
                        for (j = 0; j < 5; j++) {
                            int k;
                            lcount_r17 =
                                ((struct pair*) j1_r10->coll_info)[j].count;
                            lstart_r20 =
                                ((struct pair*) j1_r10->coll_info)[j].start;
                            iter_r3 = &groundCollLine[lstart_r20];
                            for (k = 0; k < lcount_r17; k++) {
                                if (vid_r26 == iter_r3->x0->v0_idx) {
                                    lines[i_r23].x0->next_id1 = lstart_r20 + k;
                                    iter_r3->x0->prev_id1 = lstart_r24;
                                }
                                iter_r3++;
                            }
                        }
                    }
                    lstart_r24++;
                }
            }
        }
    }
}

void mpLib_80058560(void)
{
    mpCollData* temp_r29 = mpLib_804D64B4;
    int i;
    int j;
    CollJoint* cur_i;
    CollJoint* cur_j;

    for (i = 0; i < temp_r29->x28 - 1; i++) {
        for (j = i + 1; j < temp_r29->x28; j++) {
            cur_i = &groundCollJoint[i];
            cur_j = &groundCollJoint[j];
            if ((cur_i->flags & 0x10000) && !(cur_i->flags & 0x40000) &&
                (cur_j->flags & 0x10000) && !(cur_j->flags & 0x40000))
            {
                mpLib_800581DC(i, j);
            }
        }
    }
}

void mpLib_80058614_Floor(void)
{
    // CollLine* var_r31;
    CollJoint* joint_r7;
    int count_r8;
    int count_r5 = 0;
    int i;
    CollLine* line_r31;
    int count_r30;
    int count_r29;
    int j;

    joint_r7 = groundCollJoint;
    count_r8 = mpLib_804D64B4->x28;
    for (i = 0; i < count_r8; i++) {
        if (joint_r7[i].xE) {
            break;
        }

        count_r5++;
    }

    if (count_r5 == count_r8) {
        return;
    }

    mpLib_80458868[1].right = -F32_MAX;
    mpLib_80458868[1].top = -F32_MAX;
    mpLib_80458868[1].left = F32_MAX;
    mpLib_80458868[1].bottom = F32_MAX;

    for (i = 0; i < count_r8; i++, joint_r7++) {
        joint_r7->xE = false;
        if (!(joint_r7->flags & 0x10000) || (joint_r7->flags & 0x40000)) {
            continue;
        }

        {
            CollInfo* coll_info = joint_r7->coll_info;
            line_r31 = &groundCollLine[coll_info->floor_start];
            count_r30 = coll_info->floor_count;
            count_r29 = coll_info->dynamic_count;

            for (j = 0; j < count_r30; j++, line_r31++) {
                CollVtx* v0;
                CollVtx* v1;
                float x0;
                float y0;
                float x1;
                float y1;
            block_8:

                if (!(line_r31->flags & CollLine_Floor) ||
                    !(line_r31->flags & 0x10000))
                {
                    continue;
                }

                v0 = &groundCollVtx[line_r31->x0->v0_idx];
                v1 = &groundCollVtx[line_r31->x0->v1_idx];
                x0 = v0->pos.x;
                y0 = v0->pos.y;
                x1 = v1->pos.x;
                y1 = v1->pos.y;

                if (mpLib_80458868[1].top < y0) {
                    mpLib_80458868[1].top = y0;
                }
                if (mpLib_80458868[1].bottom > y0) {
                    mpLib_80458868[1].bottom = y0;
                }
                if (mpLib_80458868[1].right < x0) {
                    mpLib_80458868[1].right = x0;
                }
                if (mpLib_80458868[1].left > x0) {
                    mpLib_80458868[1].left = x0;
                }
                if (mpLib_80458868[1].top < y1) {
                    mpLib_80458868[1].top = y1;
                }
                if (mpLib_80458868[1].bottom > y1) {
                    mpLib_80458868[1].bottom = y1;
                }
                if (mpLib_80458868[1].right < x1) {
                    mpLib_80458868[1].right = x1;
                }
                if (mpLib_80458868[1].left > x1) {
                    mpLib_80458868[1].left = x1;
                }
            }
            if (count_r29 != 0) {
                count_r30 = count_r29;
                j = 0;
                count_r29 = 0;
                line_r31 = &groundCollLine[joint_r7->coll_info->dynamic_start];
                goto block_8;
            }
        }
    }
}

void fn_800587FC(HSD_GObj* gobj)
{
    mpLib_80058614_Floor();
    grDynamicAttr_801CA224();
}

void mpLib_80058820(void)
{
    HSD_GObj* gobj = GObj_Create(1, 6, 0);
    HSD_ASSERT(6314, gobj);
    HSD_GObjProc_8038FD54(gobj, fn_800587FC, 4);
    mpLib_80458868[0].right = +10000.0F;
    mpLib_80458868[0].top = +10000.0F;
    mpLib_80458868[0].left = -10000.0F;
    mpLib_80458868[0].bottom = -10000.0F;
    mpLib_80458868[1] = mpLib_80458868[0];
}

bool mpLib_800588C8(void)
{
    return mpLib_804D64B0;
}

void mpLib_800588D0(float left, float bottom, float right, float top)
{
    CollJoint* curr = mpLib_804D64C4;

    while (curr != NULL) {
        if (curr->flags & 0x10000 && !(curr->flags & 0x40000)) {
            if (curr->flags & 0x400) {
                curr->flags &= ~0x1000;
            } else if (left > curr->x18.x || right < curr->x10.x ||
                       bottom > curr->x18.y || top < curr->x10.y)
            {
                curr->flags |= 0x1000;
            } else {
                curr->flags &= ~0x1000;
            }
        } else {
            curr->flags |= 0x1000;
        }

        curr = curr->next;
    }

    mpLib_804D64B0 = true;
}

void mpLib_80058970(float x1, float y1, float x2, float y2)
{
    float right;
    float left;
    float bottom;
    float top;

    if (x1 > x2) {
        left = x2;
        right = x1;
    } else {
        right = x2;
        left = x1;
    }
    if (y1 > y2) {
        bottom = y2;
        top = y1;
    } else {
        top = y2;
        bottom = y1;
    }
    mpLib_800588D0(left, bottom, right, top);
}

void mpLib_800589D0(float x0, float y0, float x1, float y1, float x2, float y2,
                    float x3, float y3)
{
    float right;
    float left;
    float bottom;
    float top;

    left = x1;
    bottom = y1;
    if (x0 > left) {
        right = x0;
    } else {
        right = left;
        left = x0;
    }
    if (y0 > bottom) {
        top = y0;
    } else {
        top = bottom;
        bottom = y0;
    }
    if (right < x2) {
        right = x2;
    } else if (left > x2) {
        left = x2;
    }
    if (top < y2) {
        top = y2;
    } else if (bottom > y2) {
        bottom = y2;
    }
    if (right < x3) {
        right = x3;
    } else if (left > x3) {
        left = x3;
    }
    if (top < y3) {
        top = y3;
    } else if (bottom > y3) {
        bottom = y3;
    }
    mpLib_800588D0(left, bottom, right, top);
}

void mpLib_80058AA0(void)
{
    CollJoint* curr = mpLib_804D64C4;

    while (curr != NULL) {
        curr->flags &= ~0x1000;
        curr = curr->next;
    }

    mpLib_804D64B0 = false;
}

static HSD_Chan mpLib_803BF540 = {
    NULL,
    GX_COLOR0A0,
    0,
    { 0, 0, 0, 0 },
    { 0xFF, 0xA0, 0x30, 0xFF },
    0,
    GX_SRC_REG,
    GX_SRC_REG,
    GX_LIGHT_NULL,
    GX_DF_CLAMP,
    GX_AF_NONE,
    NULL,
};

void mpLib_SetupDraw(GXColor color)
{
    HSD_TevDesc spC;
    HSD_StateInitTev();
    spC.flags = 0;
    spC.stage = HSD_StateAssignTev();
    spC.coord = 0xFF;
    spC.map = 0xFF;
    spC.color = 4;
    spC.u.tevop.tevmode = 4;
    HSD_SetupTevStage(&spC);
    HSD_SetupPEMode(1, NULL);
    HSD_SetTevRegAll();
    HSD_StateSetNumTevStages();
    HSD_StateSetNumTexGens();
    HSD_StateSetNumChans(1);
    mpLib_803BF540.mat_color = color;
    HSD_SetupChannel(&mpLib_803BF540);
}

void mpLib_DrawEcbs(CollData* cd)
{
    GXColor spE0 = { 0xFF, 0xA0, 0x30, 0xFF };
    GXColor spDC = { 0x80, 0x50, 0x18, 0xFF };
    GXColor spD8 = { 0xFF, 0x5A, 0x20, 0xFF };
    GXColor spD4 = { 0x80, 0x2D, 0x10, 0xFF };
    GXColor spD0 = { 0x20, 0x20, 0xFF, 0xFF };
    GXColor spCC = { 0x10, 0x10, 0x80, 0xFF };
    GXColor spC8 = { 0xFF, 0xFF, 0xFF, 0x80 };
    GXColor spC4 = { 0xFF, 0xFF, 0xFF, 0x80 };

    mpLib_SetupDraw(spE0);
    GXBegin(GX_QUADS, GX_VTXFMT0, 4);

    GXPosition3f32(cd->cur_pos.x + cd->xA4_ecbCurrCorrect.top.x,
                   cd->cur_pos.y + cd->xA4_ecbCurrCorrect.top.y,
                   cd->cur_pos.z);
    GXPosition3f32(cd->cur_pos.x + cd->xA4_ecbCurrCorrect.right.x,
                   cd->cur_pos.y + cd->xA4_ecbCurrCorrect.right.y,
                   cd->cur_pos.z);
    GXPosition3f32(cd->cur_pos.x + cd->xA4_ecbCurrCorrect.bottom.x,
                   cd->cur_pos.y + cd->xA4_ecbCurrCorrect.bottom.y,
                   cd->cur_pos.z);
    GXPosition3f32(cd->cur_pos.x + cd->xA4_ecbCurrCorrect.left.x,
                   cd->cur_pos.y + cd->xA4_ecbCurrCorrect.left.y,
                   cd->cur_pos.z);

    GXEnd();

    mpLib_SetupDraw(spDC);
    GXBegin(GX_LINES, GX_VTXFMT0, 4);

    GXPosition3f32(cd->cur_pos.x - 1.0F, cd->cur_pos.y, cd->cur_pos.z);
    GXPosition3f32(1.0F + cd->cur_pos.x, cd->cur_pos.y, cd->cur_pos.z);
    GXPosition3f32(cd->cur_pos.x, cd->cur_pos.y - 1.0F, cd->cur_pos.z);
    GXPosition3f32(cd->cur_pos.x, 1.0F + cd->cur_pos.y, cd->cur_pos.z);

    GXEnd();

    mpLib_SetupDraw(spD8);
    GXBegin(GX_QUADS, GX_VTXFMT0, 4);

    GXPosition3f32(cd->cur_pos_correct.x + cd->xC4_ecb.top.x,
                   cd->cur_pos_correct.y + cd->xC4_ecb.top.y,
                   cd->cur_pos_correct.z - 0.5F);
    GXPosition3f32(cd->cur_pos_correct.x + cd->xC4_ecb.right.x,
                   cd->cur_pos_correct.y + cd->xC4_ecb.right.y,
                   cd->cur_pos_correct.z - 0.5F);
    GXPosition3f32(cd->cur_pos_correct.x + cd->xC4_ecb.bottom.x,
                   cd->cur_pos_correct.y + cd->xC4_ecb.bottom.y,
                   cd->cur_pos_correct.z - 0.5F);
    GXPosition3f32(cd->cur_pos_correct.x + cd->xC4_ecb.left.x,
                   cd->cur_pos_correct.y + cd->xC4_ecb.left.y,
                   cd->cur_pos_correct.z - 0.5F);

    GXEnd();

    mpLib_SetupDraw(spD4);
    GXBegin(GX_LINES, GX_VTXFMT0, 4);

    GXPosition3f32(cd->cur_pos_correct.x - 1.0F, cd->cur_pos_correct.y,
                   cd->cur_pos_correct.z - 0.5F);
    GXPosition3f32(1.0F + cd->cur_pos_correct.x, cd->cur_pos_correct.y,
                   cd->cur_pos_correct.z - 0.5F);
    GXPosition3f32(cd->cur_pos_correct.x, cd->cur_pos_correct.y - 1.0F,
                   cd->cur_pos_correct.z - 0.5F);
    GXPosition3f32(cd->cur_pos_correct.x, 1.0F + cd->cur_pos_correct.y,
                   cd->cur_pos_correct.z - 0.5F);

    GXEnd();

    mpLib_SetupDraw(spD0);
    GXBegin(GX_QUADS, GX_VTXFMT0, 4);

    GXPosition3f32(cd->prev_pos.x + cd->xE4_ecb.top.x,
                   cd->prev_pos.y + cd->xE4_ecb.top.y, cd->prev_pos.z - 1.0F);
    GXPosition3f32(cd->prev_pos.x + cd->xE4_ecb.right.x,
                   cd->prev_pos.y + cd->xE4_ecb.right.y,
                   cd->prev_pos.z - 1.0F);
    GXPosition3f32(cd->prev_pos.x + cd->xE4_ecb.bottom.x,
                   cd->prev_pos.y + cd->xE4_ecb.bottom.y,
                   cd->prev_pos.z - 1.0F);
    GXPosition3f32(cd->prev_pos.x + cd->xE4_ecb.left.x,
                   cd->prev_pos.y + cd->xE4_ecb.left.y, cd->prev_pos.z - 1.0F);

    GXEnd();

    mpLib_SetupDraw(spCC);
    GXBegin(GX_LINES, GX_VTXFMT0, 4);

    GXPosition3f32(cd->prev_pos.x - 1.0F, cd->prev_pos.y,
                   cd->prev_pos.z - 1.0F);
    GXPosition3f32(1.0F + cd->prev_pos.x, cd->prev_pos.y,
                   cd->prev_pos.z - 1.0F);
    GXPosition3f32(cd->prev_pos.x, cd->prev_pos.y - 1.0F,
                   cd->prev_pos.z - 1.0F);
    GXPosition3f32(cd->prev_pos.x, 1.0F + cd->prev_pos.y,
                   cd->prev_pos.z - 1.0F);

    GXEnd();

    mpLib_SetupDraw(spC8);
    GXBegin(GX_LINESTRIP, GX_VTXFMT0, 5);
    if (cd->x34_flags.b6) {
        GXPosition3f32(cd->x28_vec.x + cd->x64_ecb.top.x,
                       cd->x28_vec.y + cd->x64_ecb.top.y,
                       0.5F + cd->x28_vec.z);
        GXPosition3f32(cd->x28_vec.x + cd->x64_ecb.right.x,
                       cd->x28_vec.y + cd->x64_ecb.right.y,
                       0.5F + cd->x28_vec.z);
        GXPosition3f32(cd->x28_vec.x + cd->x64_ecb.bottom.x,
                       cd->x28_vec.y + cd->x64_ecb.bottom.y,
                       0.5F + cd->x28_vec.z);
        GXPosition3f32(cd->x28_vec.x + cd->x64_ecb.left.x,
                       cd->x28_vec.y + cd->x64_ecb.left.y,
                       0.5F + cd->x28_vec.z);
        GXPosition3f32(cd->x28_vec.x + cd->x64_ecb.top.x,
                       cd->x28_vec.y + cd->x64_ecb.top.y,
                       0.5F + cd->x28_vec.z);
    } else {
        GXPosition3f32(cd->x28_vec.x + cd->xA4_ecbCurrCorrect.top.x,
                       cd->x28_vec.y + cd->xA4_ecbCurrCorrect.top.y,
                       0.5F + cd->x28_vec.z);
        GXPosition3f32(cd->x28_vec.x + cd->xA4_ecbCurrCorrect.right.x,
                       cd->x28_vec.y + cd->xA4_ecbCurrCorrect.right.y,
                       0.5F + cd->x28_vec.z);
        GXPosition3f32(cd->x28_vec.x + cd->xA4_ecbCurrCorrect.bottom.x,
                       cd->x28_vec.y + cd->xA4_ecbCurrCorrect.bottom.y,
                       0.5F + cd->x28_vec.z);
        GXPosition3f32(cd->x28_vec.x + cd->xA4_ecbCurrCorrect.left.x,
                       cd->x28_vec.y + cd->xA4_ecbCurrCorrect.left.y,
                       0.5F + cd->x28_vec.z);
        GXPosition3f32(cd->x28_vec.x + cd->xA4_ecbCurrCorrect.top.x,
                       cd->x28_vec.y + cd->xA4_ecbCurrCorrect.top.y,
                       0.5F + cd->x28_vec.z);
    }
    GXEnd();

    mpLib_SetupDraw(spC4);
    GXBegin(GX_LINES, GX_VTXFMT0, 4U);

    GXPosition3f32(cd->x28_vec.x - 1.0F, cd->x28_vec.y, 0.5 + cd->x28_vec.z);
    GXPosition3f32(1.0F + cd->x28_vec.x, cd->x28_vec.y, 0.5 + cd->x28_vec.z);
    GXPosition3f32(cd->x28_vec.x, cd->x28_vec.y - 1.0F, 0.5 + cd->x28_vec.z);
    GXPosition3f32(cd->x28_vec.x, 1.0F + cd->x28_vec.y, 0.5 + cd->x28_vec.z);

    GXEnd();
}

void mpLib_DrawSnapping(void)
{
    GXColor sp110 = { 0xFF, 0x37, 0x37, 0x80 };
    GXColor sp10C = { 0x37, 0x37, 0xFF, 0x80 };
    HSD_GObj* item_r28;
    HSD_GObj* ft_r27;
    bool var_r31;

    var_r31 = false;
    ft_r27 = HSD_GObj_Entities->fighters;
    if (ft_r27 != NULL) {
        Mtx spDC;
        PAD_STACK(0x30);
        HSD_StateSetCullMode(0);
        GXClearVtxDesc();
        GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_TEX_ST, GX_RGBA6, 0U);
        HSD_CObjGetViewingMtx(HSD_CObjGetCurrent(), spDC);
        GXSetCurrentMtx(0U);
        GXLoadPosMtxImm(spDC, 0);
        var_r31 = true;
        for (; ft_r27 != NULL; ft_r27 = ft_r27->next) {
            CollData* cd = ftLib_80086984(ft_r27);

            if (!cd->x35_flags.b0 || cd->x38 != mpColl_804D64AC) {
                continue;
            }

            mpLib_DrawEcbs(cd);

            if (cd->ledge_snap_x != 0.0 || cd->ledge_snap_y != 0.0) {
                float inner_x = cd->cur_pos.x + cd->xA4_ecbCurrCorrect.right.x;
                float pos_y = cd->cur_pos.y;
                float f30 = 0.5F * cd->ledge_snap_height;

                mpLib_SetupDraw(sp10C);
                GXBegin(GX_LINESTRIP, GX_VTXFMT0, 5);
                GXPosition3f32(inner_x + cd->ledge_snap_x,
                               f30 + (pos_y + cd->ledge_snap_y),
                               cd->cur_pos.z);
                GXPosition3f32(inner_x + cd->ledge_snap_x,
                               (pos_y + cd->ledge_snap_y) - f30,
                               cd->cur_pos.z);
                GXPosition3f32(cd->cur_pos.x, (pos_y + cd->ledge_snap_y) - f30,
                               cd->cur_pos.z);
                GXPosition3f32(cd->cur_pos.x, f30 + (pos_y + cd->ledge_snap_y),
                               cd->cur_pos.z);
                GXPosition3f32(inner_x + cd->ledge_snap_x,
                               f30 + (pos_y + cd->ledge_snap_y),
                               cd->cur_pos.z);
                GXEnd();

                pos_y = cd->cur_pos.y;
                inner_x = cd->cur_pos.x + cd->xA4_ecbCurrCorrect.left.x;
                mpLib_SetupDraw(sp110);
                GXBegin(GX_LINESTRIP, GX_VTXFMT0, 5);

                GXPosition3f32(inner_x - cd->ledge_snap_x,
                               f30 + (pos_y + cd->ledge_snap_y),
                               cd->cur_pos.z);
                GXPosition3f32(inner_x - cd->ledge_snap_x,
                               (pos_y + cd->ledge_snap_y) - f30,
                               cd->cur_pos.z);
                GXPosition3f32(cd->cur_pos.x, (pos_y + cd->ledge_snap_y) - f30,
                               cd->cur_pos.z);
                GXPosition3f32(cd->cur_pos.x, f30 + (pos_y + cd->ledge_snap_y),
                               cd->cur_pos.z);
                GXPosition3f32(inner_x - cd->ledge_snap_x,
                               f30 + (pos_y + cd->ledge_snap_y),
                               cd->cur_pos.z);

                GXEnd();
            }
        }
    }

    item_r28 = HSD_GObj_Entities->items;
    if (item_r28 != NULL) {
        if (!var_r31) {
            Mtx sp7C;
            PAD_STACK(0x40);
            GXSetCullMode(GX_CULL_NONE);
            GXClearVtxDesc();
            GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
            GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_TEX_ST, GX_RGBA6, 0);
            HSD_CObjGetViewingMtx(HSD_CObjGetCurrent(), sp7C);
            GXSetCurrentMtx(0);
            GXLoadPosMtxImm(sp7C, 0);
        }

        for (; item_r28 != NULL; item_r28 = item_r28->next) {
            CollData* cd = &GET_ITEM(item_r28)->x378_itemColl;
            if (!cd->x35_flags.b0) {
                continue;
            }

            if (cd->x38 == mpColl_804D64AC) {
                mpLib_DrawEcbs(cd);
            }

            if (itGetKind(item_r28) == It_Kind_Link_HShot) {
                mpLib_DrawEcbs(
                    &GET_ITEM(item_r28)
                         ->xDD4_itemVar.linkhookshot.x0->x30_collData);
            }
        }
    }
}

void mpLib_DrawMatchingLines(int value, int flag, GXColor color)
{
    CollLine* line_r31;
    int count_r28;
    int total_r27;
    CollLine* line_r6;
    int i;

    count_r28 = 0;
    total_r27 = mpLib_804D64B4->line_count;
    line_r6 = groundCollLine;
    for (i = 0; i < total_r27; i++) {
        if (line_r6->flags & 0x10000 && !(line_r6->flags & 0x40000) &&
            value == (line_r6->x0->flags & flag))
        {
            count_r28 += 1;
        }
        line_r6 += 1;
    }

    if (count_r28 == 0) {
        return;
    }

    line_r31 = groundCollLine;
    mpLib_SetupDraw(color);
    GXBegin(GX_QUADS, GX_VTXFMT0, count_r28 * 4);
    for (i = 0; i < total_r27; i++) {
        if (line_r31->flags & 0x10000 && !(line_r31->flags & 0x40000)) {
            if (value == (line_r31->x0->flags & flag)) {
                PAD_STACK(8);
                GXPosition3f32(groundCollVtx[line_r31->x0->v0_idx].pos.x,
                               groundCollVtx[line_r31->x0->v0_idx].pos.y,
                               25.0F);
                GXPosition3f32(groundCollVtx[line_r31->x0->v1_idx].pos.x,
                               groundCollVtx[line_r31->x0->v1_idx].pos.y,
                               25.0F);
                GXPosition3f32(groundCollVtx[line_r31->x0->v1_idx].pos.x,
                               groundCollVtx[line_r31->x0->v1_idx].pos.y,
                               -25.0F);
                GXPosition3f32(groundCollVtx[line_r31->x0->v0_idx].pos.x,
                               groundCollVtx[line_r31->x0->v0_idx].pos.y,
                               -25.0F);
            }
        }
        line_r31 += 1;
    }
    GXEnd();
}

static const GXColor mpLib_FloorColor = { 0xC0, 0xC0, 0xC0, 0xFF };
static const GXColor mpLib_CeilingColor = { 0xC0, 0x80, 0x80, 0xFF };
static const GXColor mpLib_RightWallColor = { 0x80, 0xC0, 0x80, 0xFF };
static const GXColor mpLib_LeftWallColor = { 0x80, 0x80, 0xC0, 0xFF };
static const GXColor mpLib_DynamicFloorColor = { 0x60, 0x60, 0x60, 0xFF };
static const GXColor mpLib_DynamicCeilingColor = { 0x60, 0x40, 0x40, 0xFF };
static const GXColor mpLib_DynamicRightWallColor = { 0x40, 0x60, 0x40, 0xFF };
static const GXColor mpLib_DynamicLeftWallColor = { 0x40, 0x40, 0x60, 0xFF };

void mpLib_80059554(void)
{
    CollLine* line_r7;
    CollLine* line_r4;
    CollVtx* v0_r6;
    CollVtx* v1_r4;
    s16 count_r30;
    int total_r29;
    mpCollData* coll_data_r31;
    int i;
    GXColor spB4;
    GXColor spB0;
    GXColor spAC;
    GXColor spA8;

    coll_data_r31 = mpLib_804D64B4;

    total_r29 = 0;
    count_r30 = coll_data_r31->floor_count;
    line_r4 = &groundCollLine[coll_data_r31->floor_start];

    for (i = 0; i < count_r30; i++) {
        if (line_r4->flags & 0x10000 && !(line_r4->flags & 0x40000)) {
            total_r29 += 1;
        }
        line_r4++;
    }

    if (total_r29 != 0) {
        mpLib_SetupDraw(mpLib_FloorColor);
        GXBegin(GX_QUADS, GX_VTXFMT0, (total_r29 * 4) & 0xFFFC);
        line_r7 = &groundCollLine[coll_data_r31->floor_start];

        for (i = 0; i < count_r30; i++) {
            if (line_r7->flags & 0x10000 && !(line_r7->flags & 0x40000)) {
                GXPosition3f32(groundCollVtx[line_r7->x0->v0_idx].pos.x,
                               groundCollVtx[line_r7->x0->v0_idx].pos.y,
                               25.0F);
                GXPosition3f32(groundCollVtx[line_r7->x0->v1_idx].pos.x,
                               groundCollVtx[line_r7->x0->v1_idx].pos.y,
                               25.0F);
                GXPosition3f32(groundCollVtx[line_r7->x0->v1_idx].pos.x,
                               groundCollVtx[line_r7->x0->v1_idx].pos.y,
                               -25.0F);
                GXPosition3f32(groundCollVtx[line_r7->x0->v0_idx].pos.x,
                               groundCollVtx[line_r7->x0->v0_idx].pos.y,
                               -25.0F);
            }
            line_r7++;
        }
        GXEnd();
    }

    total_r29 = 0;
    count_r30 = coll_data_r31->ceiling_count;
    line_r4 = &groundCollLine[coll_data_r31->ceiling_start];

    for (i = 0; i < count_r30; i++) {
        if (line_r4->flags & 0x10000 && !(line_r4->flags & 0x40000)) {
            total_r29 += 1;
        }
        line_r4 += 1;
    }

    if (total_r29 != 0) {
        mpLib_SetupDraw(mpLib_CeilingColor);
        GXBegin(GX_QUADS, GX_VTXFMT0, (total_r29 * 4) & 0xFFFC);
        line_r7 = &groundCollLine[coll_data_r31->ceiling_start];

        for (i = 0; i < count_r30; i++) {
            if (line_r7->flags & 0x10000 && !(line_r7->flags & 0x40000)) {
                GXPosition3f32(groundCollVtx[line_r7->x0->v0_idx].pos.x,
                               groundCollVtx[line_r7->x0->v0_idx].pos.y,
                               25.0F);
                GXPosition3f32(groundCollVtx[line_r7->x0->v1_idx].pos.x,
                               groundCollVtx[line_r7->x0->v1_idx].pos.y,
                               25.0F);
                GXPosition3f32(groundCollVtx[line_r7->x0->v1_idx].pos.x,
                               groundCollVtx[line_r7->x0->v1_idx].pos.y,
                               -25.0F);
                GXPosition3f32(groundCollVtx[line_r7->x0->v0_idx].pos.x,
                               groundCollVtx[line_r7->x0->v0_idx].pos.y,
                               -25.0F);
            }
            line_r7++;
        }
        GXEnd();
    }

    total_r29 = 0;
    count_r30 = coll_data_r31->right_wall_count;
    line_r4 = &groundCollLine[coll_data_r31->right_wall_start];

    for (i = 0; i < count_r30; i++) {
        if (line_r4->flags & 0x10000 && !(line_r4->flags & 0x40000)) {
            total_r29 += 1;
        }
        line_r4 += 1;
    }

    if (total_r29 != 0) {
        mpLib_SetupDraw(mpLib_RightWallColor);
        GXBegin(GX_QUADS, GX_VTXFMT0, (total_r29 * 4) & 0xFFFC);
        line_r7 = &groundCollLine[coll_data_r31->right_wall_start];

        for (i = 0; i < count_r30; i++) {
            if (line_r7->flags & 0x10000 && !(line_r7->flags & 0x40000)) {
                GXPosition3f32(groundCollVtx[line_r7->x0->v0_idx].pos.x,
                               groundCollVtx[line_r7->x0->v0_idx].pos.y,
                               25.0F);
                GXPosition3f32(groundCollVtx[line_r7->x0->v1_idx].pos.x,
                               groundCollVtx[line_r7->x0->v1_idx].pos.y,
                               25.0F);
                GXPosition3f32(groundCollVtx[line_r7->x0->v1_idx].pos.x,
                               groundCollVtx[line_r7->x0->v1_idx].pos.y,
                               -25.0F);
                GXPosition3f32(groundCollVtx[line_r7->x0->v0_idx].pos.x,
                               groundCollVtx[line_r7->x0->v0_idx].pos.y,
                               -25.0F);
            }
            line_r7++;
        }
        GXEnd();
    }

    total_r29 = 0;
    count_r30 = coll_data_r31->left_wall_count;
    line_r4 = &groundCollLine[coll_data_r31->left_wall_start];

    for (i = 0; i < count_r30; i++) {
        if (line_r4->flags & 0x10000 && !(line_r4->flags & 0x40000)) {
            total_r29 += 1;
        }
        line_r4 += 1;
    }

    if (total_r29 != 0) {
        mpLib_SetupDraw(mpLib_LeftWallColor);
        GXBegin(GX_QUADS, GX_VTXFMT0, (total_r29 * 4) & 0xFFFC);
        line_r7 = &groundCollLine[coll_data_r31->left_wall_start];

        for (i = 0; i < count_r30; i++) {
            if (line_r7->flags & 0x10000 && !(line_r7->flags & 0x40000)) {
                GXPosition3f32(groundCollVtx[line_r7->x0->v0_idx].pos.x,
                               groundCollVtx[line_r7->x0->v0_idx].pos.y,
                               25.0F);
                GXPosition3f32(groundCollVtx[line_r7->x0->v1_idx].pos.x,
                               groundCollVtx[line_r7->x0->v1_idx].pos.y,
                               25.0F);
                GXPosition3f32(groundCollVtx[line_r7->x0->v1_idx].pos.x,
                               groundCollVtx[line_r7->x0->v1_idx].pos.y,
                               -25.0F);
                GXPosition3f32(groundCollVtx[line_r7->x0->v0_idx].pos.x,
                               groundCollVtx[line_r7->x0->v0_idx].pos.y,
                               -25.0F);
            }
            line_r7++;
        }
        GXEnd();
    }

    count_r30 = coll_data_r31->dynamic_count;
    line_r4 = &groundCollLine[coll_data_r31->dynamic_start];
    total_r29 = 0;
    spB4 = mpLib_DynamicFloorColor;
    spB0 = mpLib_DynamicCeilingColor;
    spAC = mpLib_DynamicRightWallColor;
    spA8 = mpLib_DynamicLeftWallColor;

    for (i = 0; i < count_r30; i++) {
        if (line_r4->flags & 0x10000 && line_r4->flags & CollLine_Floor &&
            !(line_r4->flags & 0x40000))
        {
            total_r29 += 1;
        }
        line_r4 += 1;
    }

    if (total_r29 != 0) {
        mpLib_SetupDraw(spB4);
        GXBegin(GX_QUADS, GX_VTXFMT0, (total_r29 * 4) & 0xFFFC);
        line_r7 = &groundCollLine[coll_data_r31->dynamic_start];

        for (i = 0; i < count_r30; i++) {
            if (line_r7->flags & 0x10000 && line_r7->flags & CollLine_Floor &&
                !(line_r7->flags & 0x40000))
            {
                GXPosition3f32(groundCollVtx[line_r7->x0->v0_idx].pos.x,
                               groundCollVtx[line_r7->x0->v0_idx].pos.y,
                               25.0F);
                GXPosition3f32(groundCollVtx[line_r7->x0->v1_idx].pos.x,
                               groundCollVtx[line_r7->x0->v1_idx].pos.y,
                               25.0F);
                GXPosition3f32(groundCollVtx[line_r7->x0->v1_idx].pos.x,
                               groundCollVtx[line_r7->x0->v1_idx].pos.y,
                               -25.0F);
                GXPosition3f32(groundCollVtx[line_r7->x0->v0_idx].pos.x,
                               groundCollVtx[line_r7->x0->v0_idx].pos.y,
                               -25.0F);
            }
            line_r7++;
        }
        GXEnd();
    }
    line_r4 = &groundCollLine[coll_data_r31->dynamic_start];
    total_r29 = 0;

    for (i = 0; i < count_r30; i++) {
        if (line_r4->flags & 0x10000 && line_r4->flags & CollLine_Ceiling &&
            !(line_r4->flags & 0x40000))
        {
            total_r29 += 1;
        }
        line_r4 += 1;
    }

    if (total_r29 != 0) {
        mpLib_SetupDraw(spB0);
        GXBegin(GX_QUADS, GX_VTXFMT0, (total_r29 * 4) & 0xFFFC);
        line_r7 = &groundCollLine[coll_data_r31->dynamic_start];

        for (i = 0; i < count_r30; i++) {
            if (line_r7->flags & 0x10000 &&
                line_r7->flags & CollLine_Ceiling &&
                !(line_r7->flags & 0x40000))
            {
                GXPosition3f32(groundCollVtx[line_r7->x0->v0_idx].pos.x,
                               groundCollVtx[line_r7->x0->v0_idx].pos.y,
                               25.0F);
                GXPosition3f32(groundCollVtx[line_r7->x0->v1_idx].pos.x,
                               groundCollVtx[line_r7->x0->v1_idx].pos.y,
                               25.0F);
                GXPosition3f32(groundCollVtx[line_r7->x0->v1_idx].pos.x,
                               groundCollVtx[line_r7->x0->v1_idx].pos.y,
                               -25.0F);
                GXPosition3f32(groundCollVtx[line_r7->x0->v0_idx].pos.x,
                               groundCollVtx[line_r7->x0->v0_idx].pos.y,
                               -25.0F);
            }
            line_r7++;
        }
        GXEnd();
    }
    line_r4 = &groundCollLine[coll_data_r31->dynamic_start];
    total_r29 = 0;

    for (i = 0; i < count_r30; i++) {
        if (line_r4->flags & 0x10000 && line_r4->flags & CollLine_RightWall &&
            !(line_r4->flags & 0x40000))
        {
            total_r29 += 1;
        }
        line_r4 += 1;
    }
    if (total_r29 != 0) {
        mpLib_SetupDraw(spAC);
        GXBegin(GX_QUADS, GX_VTXFMT0, (total_r29 * 4) & 0xFFFC);
        line_r7 = &groundCollLine[coll_data_r31->dynamic_start];

        for (i = 0; i < count_r30; i++) {
            if (line_r7->flags & 0x10000 &&
                line_r7->flags & CollLine_RightWall &&
                !(line_r7->flags & 0x40000))
            {
                GXPosition3f32(groundCollVtx[line_r7->x0->v0_idx].pos.x,
                               groundCollVtx[line_r7->x0->v0_idx].pos.y,
                               25.0F);
                GXPosition3f32(groundCollVtx[line_r7->x0->v1_idx].pos.x,
                               groundCollVtx[line_r7->x0->v1_idx].pos.y,
                               25.0F);
                GXPosition3f32(groundCollVtx[line_r7->x0->v1_idx].pos.x,
                               groundCollVtx[line_r7->x0->v1_idx].pos.y,
                               -25.0F);
                GXPosition3f32(groundCollVtx[line_r7->x0->v0_idx].pos.x,
                               groundCollVtx[line_r7->x0->v0_idx].pos.y,
                               -25.0F);
            }
            line_r7++;
        }
        GXEnd();
    }
    line_r4 = &groundCollLine[coll_data_r31->dynamic_start];
    total_r29 = 0;

    for (i = 0; i < count_r30; i++) {
        if (line_r4->flags & 0x10000 && line_r4->flags & CollLine_LeftWall &&
            !(line_r4->flags & 0x40000))
        {
            total_r29 += 1;
        }
        line_r4 += 1;
    }
    if (total_r29 != 0) {
        mpLib_SetupDraw(spA8);
        GXBegin(GX_QUADS, GX_VTXFMT0, (total_r29 * 4) & 0xFFFC);
        line_r7 = &groundCollLine[coll_data_r31->dynamic_start];

        for (i = 0; i < count_r30; i++) {
            if (line_r7->flags & 0x10000 &&
                line_r7->flags & CollLine_LeftWall &&
                !(line_r7->flags & 0x40000))
            {
                GXPosition3f32(groundCollVtx[line_r7->x0->v0_idx].pos.x,
                               groundCollVtx[line_r7->x0->v0_idx].pos.y,
                               25.0F);
                GXPosition3f32(groundCollVtx[line_r7->x0->v1_idx].pos.x,
                               groundCollVtx[line_r7->x0->v1_idx].pos.y,
                               25.0F);
                GXPosition3f32(groundCollVtx[line_r7->x0->v1_idx].pos.x,
                               groundCollVtx[line_r7->x0->v1_idx].pos.y,
                               -25.0F);
                GXPosition3f32(groundCollVtx[line_r7->x0->v0_idx].pos.x,
                               groundCollVtx[line_r7->x0->v0_idx].pos.y,
                               -25.0F);
            }
            line_r7++;
        }
        GXEnd();
    }
}

static const GXColor mpLib_804D80F0 = { 0xFF, 0x40, 0x40, 0xFF };
static const GXColor mpLib_804D80F4 = { 0x40, 0x40, 0xFF, 0xFF };
static const GXColor mpLib_804D80F8 = { 0xFF, 0x40, 0xFF, 0xFF };
static const GXColor mpLib_804D80FC = { 0x80, 0x80, 0x80, 0xFF };
static const GXColor mpLib_804D8100 = { 0x80, 0x80, 0x80, 0xFF };

void mpLib_80059E60(void)
{
    Mtx sp104;
    PAD_STACK(0x3C);

    HSD_LObjSetupInit(HSD_CObjGetCurrent());
    GXSetCullMode(GX_CULL_NONE);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_TEX_ST, GX_RGBA6, 0U);
    HSD_CObjGetViewingMtx(HSD_CObjGetCurrent(), sp104);
    GXSetCurrentMtx(0U);
    GXLoadPosMtxImm(sp104, 0U);
    if (Camera_80030B50()) {
        // terrain draw
        mpIsland_Palette sp28;
        mpIsland_PaletteEntry* var_r30;
        PAD_STACK(0x8);
        sp28 = mpIsland_TerrainPalette;

        var_r30 = sp28.x0;

        while (var_r30->kind != -1) {
            mpLib_DrawMatchingLines(var_r30->kind, 0xFF, var_r30->color);
            var_r30++;
        }

        mpLib_DrawMatchingLines(mp_Terrain_Basic, 0xFF, mpLib_804D8100);
    } else if (Camera_80030B7C()) {
        // platform/ledge draw
        mpLib_DrawMatchingLines(LINE_FLAG_LEDGE, LINE_FLAG_LEDGE,
                                mpLib_804D80F0);
        mpLib_DrawMatchingLines(LINE_FLAG_PLATFORM, LINE_FLAG_PLATFORM,
                                mpLib_804D80F4);
        mpLib_DrawMatchingLines(LINE_FLAG_LEDGE | LINE_FLAG_PLATFORM,
                                LINE_FLAG_LEDGE | LINE_FLAG_PLATFORM,
                                mpLib_804D80F8);
        mpLib_DrawMatchingLines(0, LINE_FLAG_LEDGE | LINE_FLAG_PLATFORM,
                                mpLib_804D80FC);
    } else {
        mpLib_80059554();
    }
}

void mpLib_DrawCrosses(s16* idx, int len, GXColor arg2)
{
    Vec3 sp34;
    s16* var_r31;
    Vec3* var_r30;
    Vec3* temp_r29;
    int i;
    int j;
    Vec3* vtx;
    int var_r28;
    int len_r27;

    var_r28 = 0;
    vtx = mpLib_80458888;
    var_r30 = vtx;
    j = 0;
    var_r31 = idx;
    len_r27 = 0;
    for (var_r28 = 0; var_r28 < len && len_r27 < 0x80; var_r28++) {
        if (Ground_801C2D24(*var_r31, &sp34)) {
            len_r27 += 1;
            *var_r30 = sp34;
            var_r30++;
        }
        var_r31 += 1;
    }

    if (!len_r27) {
        return;
    }

    mpLib_SetupDraw(arg2);
    GXBegin(GX_LINES, GX_VTXFMT0, len_r27 * 6);
    for (i = 0; i < len_r27; i++) {
        GXPosition3f32(vtx->x - 3.0F, vtx->y, vtx->z);
        GXPosition3f32(3.0F + vtx->x, vtx->y, vtx->z);
        GXPosition3f32(vtx->x, vtx->y - 3.0F, vtx->z);
        GXPosition3f32(vtx->x, 3.0F + vtx->y, vtx->z);
        GXPosition3f32(vtx->x, vtx->y, vtx->z - 3.0F);
        GXPosition3f32(vtx->x, vtx->y, 3.0F + vtx->z);
        vtx++;
    }
}

static s16 mpLib_ItemSpawnVtxIds[0x15] = {
    0x7F, 0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89,
    0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F, 0x90, 0x91, 0x92, 0x93,
};

static s16 mpLib_EnemySpawnVtxIds[0x50] = {
    0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2A, 0x2B,
    0x2C, 0x2D, 0x2E, 0x2F, 0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37,
    0x38, 0x39, 0x3A, 0x3B, 0x3C, 0x3D, 0x3E, 0x3F, 0x40, 0x41, 0x42, 0x43,
    0x44, 0x45, 0x46, 0x47, 0x48, 0x49, 0x4A, 0x4B, 0x4C, 0x4D, 0x4E, 0x4F,
    0x50, 0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58, 0x59, 0x5A, 0x5B,
    0x5C, 0x5D, 0x5E, 0x5F, 0x60, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67,
    0x68, 0x69, 0x6A, 0x6B, 0x6C, 0x6D, 0x6E, 0x6F,
};

static s16 mpLib_TrophySpawnVtxIds[0x19] = {
    0xDC, 0xDD, 0xDE, 0xDF, 0xE0, 0xE1, 0xE2, 0xE3, 0xE4,
    0xE5, 0xE6, 0xE7, 0xE8, 0xE9, 0xEA, 0xEB, 0xEC, 0xED,
    0xEE, 0xEF, 0xF0, 0xF1, 0xF2, 0xF3, 0xF4,
};

static s16 mpLib_ExitVtxIds[0x2E] = {
    0x99, 0x9A, 0x9B, 0x9C, 0x9D, 0x9E, 0x9F, 0xA0, 0xA1, 0xA2, 0xA3, 0xA4,
    0xA5, 0xA6, 0xA7, 0xA8, 0xA9, 0xAA, 0xAB, 0xAC, 0xAD, 0xAE, 0xAF, 0xB0,
    0xB1, 0xB2, 0xB3, 0xB4, 0xB5, 0xB6, 0xB7, 0xB8, 0xB9, 0xBA, 0xBB, 0xBC,
    0xBD, 0xBE, 0xBF, 0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6
};

static s16 mpLib_SpawnVtxIds[4] = { 0, 1, 2, 3 };
static s16 mpLib_RespawnVtxIds[4] = { 4, 5, 6, 7 };

static const GXColor mpLib_804D8128 = { 0x7D, 0x7D, 0xFF, 0xFF };
static const GXColor mpLib_804D812C = { 0x7D, 0xFF, 0x80, 0xFF };
static const GXColor mpLib_804D8130 = { 0xFF, 0xFF, 0x80, 0xFF };
static const GXColor mpLib_804D8134 = { 0xFF, 0x40, 0x40, 0xFF };
static const GXColor mpLib_804D8138 = { 0xFF, 0x40, 0xC0, 0xFF };
static const GXColor mpLib_804D813C = { 0xFF, 0xFF, 0xFF, 0xFF };

void mpLib_DrawSpecialPoints(void)
{
    PAD_STACK(40);
    mpLib_DrawCrosses(mpLib_SpawnVtxIds, 0x04, mpLib_804D8128);
    mpLib_DrawCrosses(mpLib_RespawnVtxIds, 0x04, mpLib_804D812C);
    mpLib_DrawCrosses(mpLib_ItemSpawnVtxIds, 0x15, mpLib_804D8130);
    mpLib_DrawCrosses(mpLib_EnemySpawnVtxIds, 0x50, mpLib_804D8134);
    mpLib_DrawCrosses(mpLib_TrophySpawnVtxIds, 0x19, mpLib_804D8138);
    mpLib_DrawCrosses(mpLib_ExitVtxIds, 0x2E, mpLib_804D813C);
}

void mpLib_8005A2DC(void)
{
    mpLib_DrawSnapping();
    mpLib_80059E60();
    if (mpLib_804D64D0 == 0) {
        mpLib_804D64D0 = 1;
        OSReport("map coll under=%d upper=%d left=%d right=%d bbox=%d\n",
                 mpLib_804D64D4, mpLib_804D64D8, mpLib_804D64DC,
                 mpLib_804D64E0, mpLib_804D64E4);
    }
    HSD_StateInvalidate(-1);
}

static const GXColor mpLib_804D8140 = { 0xFF, 0xFF, 0xC0, 0xFF };
static const GXColor mpLib_804D8144 = { 0xFF, 0xFF, 0xFF, 0x80 };
static const GXColor mpLib_804D8148 = { 0x80, 0xC0, 0xC0, 0xFF };
static const GXColor mpLib_804D814C = { 0xC0, 0xFF, 0xFF, 0x80 };
static const GXColor mpLib_804D8150 = { 0x40, 0x40, 0xFF, 0x00 };

// blast zones, camera bounds, etc
void mpLib_DrawZones(void)
{
    u8 _3[0x4];
    Mtx sp7C;
    u8 _2[0x38];
    GXColor sp40;
    u8 _5[0x8];
    GXColor sp34;
    GXColor sp20;
    CameraBox* var_r30;

    f32 left;
    f32 right;
    f32 bottom;
    f32 top;

    HSD_LObjSetupInit(HSD_CObjGetCurrent());
    GXSetCullMode(GX_CULL_NONE);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_TEX_ST, GX_RGBA6, 0);
    HSD_CObjGetViewingMtx(HSD_CObjGetCurrent(), sp7C);
    GXSetCurrentMtx(0);
    GXLoadPosMtxImm(sp7C, 0);

    left = Stage_GetBlastZoneLeftOffset();
    right = Stage_GetBlastZoneRightOffset();
    bottom = Stage_GetBlastZoneBottomOffset();
    top = Stage_GetBlastZoneTopOffset();

    sp40 = mpLib_804D8144;
    mpLib_SetupDraw(mpLib_804D8140);
    GXSetZMode(1, GX_LEQUAL, 0);
    GXSetLineWidth(0x10, GX_TO_ZERO);

    GXBegin(GX_LINESTRIP, GX_VTXFMT0, 5);

    GXPosition3f32(left, bottom, 0.0F);
    GXPosition3f32(right, bottom, 0.0F);
    GXPosition3f32(right, top, 0.0F);
    GXPosition3f32(left, top, 0.0F);
    GXPosition3f32(left, bottom, 0.0F);

    GXEnd();

    mpLib_SetupDraw(sp40);
    GXSetZMode(1, GX_GREATER, 0);
    GXSetLineWidth(0x10, GX_TO_ZERO);

    GXBegin(GX_LINESTRIP, GX_VTXFMT0, 5);

    GXPosition3f32(left, bottom, 0.0F);
    GXPosition3f32(right, bottom, 0.0F);
    GXPosition3f32(right, top, 0.0F);
    GXPosition3f32(left, top, 0.0F);
    GXPosition3f32(left, bottom, 0.0F);

    GXEnd();

    left = Stage_GetCamBoundsLeftOffset();
    right = Stage_GetCamBoundsRightOffset();
    bottom = Stage_GetCamBoundsBottomOffset();
    top = Stage_GetCamBoundsTopOffset();

    sp34 = mpLib_804D814C;
    mpLib_SetupDraw(mpLib_804D8148);

    GXSetZMode(1, GX_LEQUAL, 0);
    GXSetLineWidth(0x10, GX_TO_ZERO);
    GXBegin(GX_LINESTRIP, GX_VTXFMT0, 5);

    sp20 = sp34;

    GXPosition3f32(left, bottom, 0.0F);
    GXPosition3f32(right, bottom, 0.0F);
    GXPosition3f32(right, top, 0.0F);
    GXPosition3f32(left, top, 0.0F);
    GXPosition3f32(left, bottom, 0.0F);

    GXEnd();

    mpLib_SetupDraw(sp20);

    GXSetZMode(1, GX_GREATER, 0);
    GXSetLineWidth(0x10, GX_TO_ZERO);
    GXBegin(GX_LINESTRIP, GX_VTXFMT0, 5);

    GXPosition3f32(left, bottom, 0.0F);
    GXPosition3f32(right, bottom, 0.0F);
    GXPosition3f32(right, top, 0.0F);
    GXPosition3f32(left, top, 0.0F);
    GXPosition3f32(left, bottom, 0.0F);

    GXEnd();

    mpLib_SetupDraw(mpLib_804D8150);

    GXSetZMode(0, GX_LEQUAL, 0);
    GXSetLineWidth(0x10, GX_TO_ZERO);

    var_r30 = cm_804D6468;
    while (var_r30 != NULL) {
        if (Camera_8002928C(var_r30)) {
            GXBegin(GX_LINESTRIP, GX_VTXFMT0, 5);

            GXPosition3f32(var_r30->x10.x + var_r30->x2C.x,
                           var_r30->x10.y + var_r30->x34.x, 0.0F);
            GXPosition3f32(var_r30->x10.x + var_r30->x2C.y,
                           var_r30->x10.y + var_r30->x34.x, 0.0F);
            GXPosition3f32(var_r30->x10.x + var_r30->x2C.y,
                           var_r30->x10.y + var_r30->x34.y, 0.0F);
            GXPosition3f32(var_r30->x10.x + var_r30->x2C.x,
                           var_r30->x10.y + var_r30->x34.y, 0.0F);
            GXPosition3f32(var_r30->x10.x + var_r30->x2C.x,
                           var_r30->x10.y + var_r30->x34.x, 0.0F);

            GXEnd();
        }
        var_r30 = var_r30->prev;
    }
    HSD_StateInvalidate(-1);
}
