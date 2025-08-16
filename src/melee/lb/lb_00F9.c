#include "lb_00F9.static.h"

#include "math.h"
#include "stddef.h"

#include "baselib/debug.h"
#include "baselib/displayfunc.h"
#include "baselib/rumble.h"
#include "baselib/tobj.h"
#include "dolphin/gx/GXGeometry.h"
#include "dolphin/gx/GXVert.h"
#include "dolphin/pad.h"

#include "lb/forward.h"

#include "lb/lbarchive.h"
#include "lb/lbdvd.h"
#include "lb/lbvector.h"
#include "lb/types.h"

#include <baselib/cobj.h>
#include <baselib/dobj.h>
#include <baselib/gobj.h>
#include <baselib/jobj.h>
#include <baselib/lobj.h>
#include <baselib/memory.h>
#include <melee/sc/types.h>

typedef bool (*lb_803BA248_fn)(ColorOverlay*);

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

/// #lb_8000FA94

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

/// #lb_8000FD48

static inline struct lb_80011A50_t* inlineA0()
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

static inline struct lb_80011A50_t* inlineA1()
{
    struct lb_80011A50_t* cur = lb_804D63B0;
    if (lb_804D63B0 == NULL) {
        return NULL;
    }
    {
        struct lb_80011A50_t* ret = cur;
        int max = cur->x1;
        while (cur != NULL) {
            if (max < cur->x1) {
                max = cur->x1;
                ret = cur;
            }
            cur = cur->next;
        }
        return cur;
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

void lb_800103B8(Vec3* a, Vec3* b)
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

/// #lb_8001044C

static inline double inlineB0()
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
    int i;
    struct lb_00F9_UnkDesc1Inner* data0;
    struct DynamicsData* data1;

    arg1->pos.x = arg0->pos.x;
    arg1->pos.y = arg0->pos.y;
    arg1->pos.z = arg0->pos.z;
    data1 = arg1->data;
    data0 = &arg0->data->desc.lb_unk1.array[0];
    for (data1 = arg1->data, i = 0; i < arg0->count; data1 = data1->next, i++)
    {
        data1->desc.lb_unk0.unk_10 = data0[i].unk_0;
        data1->desc.lb_unk0.unk_14 = data0[i].unk_4;
        data1->desc.lb_unk0.unk_1C = data0[i].unk_8;
        data1->desc.lb_unk0.unk_20 = data0[i].unk_C;
        data1->desc.lb_unk0.unk_24 = data0[i].unk_10;
        data1->desc.lb_unk0.unk_28 = data0[i].unk_14;
        data1->desc.lb_unk0.unk_2C = data0[i].unk_18;
        data1->desc.lb_unk0.unk_30 = data0[i].unk_1C;
        data1->desc.lb_unk0.unk_34 = data0[i].unk_20;
        data1->desc.lb_unk0.unk_38 = data0[i].unk_24;
        data1->desc.lb_unk0.unk_78 = data0[i].unk_28;
        data1->desc.lb_unk0.unk_7C = data0[i].unk_2C;
        data1->desc.lb_unk0.unk_80 = data0[i].unk_30;
        data1->desc.lb_unk0.unk_84 = data0[i].unk_34;
        data1->desc.lb_unk0.unk_88 = data0[i].unk_38;
        if (data1->desc.lb_unk0.unk_C != 0.0f) {
            data1->desc.lb_unk0.unk_8C =
                arg0->pos.z / data1->desc.lb_unk0.unk_C;
        } else {
            data1->desc.lb_unk0.unk_8C = 0.0f;
        }
    }
}

bool lb_800117F4(DynamicsDesc* arg0, GXColor* arg1, UNK_T arg2, int arg3,
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
        goto block_5;
    }
    if (arg4 != 0) {
        return false;
    }
block_5:
    HSD_StateInitDirect(0, 2);
    HSD_CObjGetViewingMtx(HSD_CObjGetCurrent(), &view_mtx[0]);
    GXLoadPosMtxImm(&view_mtx[0], 0);
    GXSetLineWidth(12, GX_TO_ONE);
    GXBegin(GX_LINESTRIP, GX_VTXFMT0, arg0->count);
    for (cur = arg0->data, i = 0; cur != NULL; cur = cur->next, i++) {
        HSD_JObjSetMtxDirtyInline(cur->desc.ft_unk.jobj);
        HSD_JObjSetupMatrix(cur->desc.ft_unk.jobj);
        {
            float x = cur->desc.ft_unk.jobj->mtx[0][3];
            float y = cur->desc.ft_unk.jobj->mtx[1][3];
            float z = cur->desc.ft_unk.jobj->mtx[2][3];
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

void lb_800119DC(Point3d* arg0, int arg1, float arg2, float arg3, float arg4)
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

void lb_80011A50(Vec3* arg0, int arg1, float arg2, float arg3, float arg4,
                 float arg5, float arg6, float arg7, float arg8)
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
    lb_800100B0(&x2C, arg2);
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
            if (prev == NULL) {
                __assert("lobj.h", 0x136, "lobj");
            }
            prev->next = curr;
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

/// #lb_80011C18

/**
 * @note: The number of HSD_JObjs that get passed into arg1 is the number of
 * variable arguments passed until -1 is passed.
 */
/// #lb_80011E24

/// #lb_8001204C
#if 0
int lb_8001204C(HSD_JObj* arg0, HSD_JObj** arg1, ...)
{
    HSD_JObj* var_ctr;
    HSD_JObj* var_r0_2;
    HSD_JObj* var_r0_3;
    HSD_JObj* var_r0_4;
    HSD_JObj* var_r0_5;
    HSD_JObj* var_r0_6;
    u16* var_r5;
    HSD_JObj* var_r6;
    HSD_JObj* var_r6_3;
    HSD_JObj* var_r8;
    HSD_JObj** var_r4;
    s32 n;
    int count;
    u16 temp_r7;

    var_r4 = arg1;
    var_r5 = (u16*) arg1[1];
    var_r6 = arg1[1];
    count = 0;
    n = -1;
    if (arg0 == NULL) {
        goto block_4;
    }
    if (var_r4 == NULL) {
        goto block_4;
    }
    if (var_r5 == NULL) {
        goto block_4;
    }
    if (var_r6 != 0) {
        goto block_5;
    }
block_4:
    return 0;
block_5:
    var_ctr = var_r6;
    if ((int) var_r6 <= 0) {
        goto block_52;
    }
loop_6:
    temp_r7 = *var_r5;
    if (n > temp_r7) {
        goto block_8;
    }
    if (n != -1) {
        goto block_9;
    }
block_8: {
    s32 var_r10;
    var_r6 = arg0;
    var_r10 = 0;
    goto loop_48;
block_9:
    var_r10 = n;
    goto loop_48;
block_10:
    if (var_r10 == temp_r7) {
        goto block_49;
    }
    var_r8 = var_r6;
    {
        if (var_r6->flags & 0x1000) {
            goto if_19;
        }
        if (var_r6 != NULL) {
            goto if_14;
        }
        var_r0_2 = NULL;
        goto else_15;
    if_14:
        var_r0_2 = var_r6->child;
    else_15:
        if (var_r0_2 == NULL) {
            goto if_19;
        }
        if (var_r6 != NULL) {
            goto if_18;
        }
        var_r0_3 = NULL;
        goto end_for_47;
    if_18:
        var_r0_3 = var_r6->child;
        goto end_for_47;
    }
if_19:
    if (var_r6 != NULL) {
        goto block_21;
    }
    var_r0_4 = NULL;
    goto block_22;
block_21:
    var_r0_4 = var_r6->next;
block_22:
    if (var_r0_4 == NULL) {
        goto loop_26;
    }
    if (var_r6 != NULL) {
        goto block_25;
    }
    var_r0_3 = NULL;
    goto end_for_47;
block_25:
    var_r0_3 = var_r6->next;
    goto end_for_47;
loop_26:
    if (var_r8 != NULL) {
        goto block_28;
    }
    var_r0_5 = NULL;
    goto block_29;
block_28:
    var_r0_5 = var_r8->parent;
block_29:
    if (var_r0_5 != NULL) {
        goto block_31;
    }
    var_r0_3 = NULL;
    goto end_for_47;
block_31:
    if (var_r8 != NULL) {
        goto block_33;
    }
    {
        HSD_JObj* var_r6_2;
        var_r6_2 = NULL;
        goto block_34;
    block_33:
        var_r6_2 = var_r8->parent;
    block_34:
        if (var_r6_2 != NULL) {
            goto block_36;
        }
        var_r0_6 = NULL;
        goto block_37;
    block_36:
        var_r0_6 = var_r6_2->next;
    }
block_37:
    if (var_r0_6 == NULL) {
        goto block_44;
    }
    if (var_r8 != NULL) {
        goto block_40;
    }
    var_r6_3 = NULL;
    goto block_41;
block_40:
    var_r6_3 = var_r8->parent;
block_41:
    if (var_r6_3 != NULL) {
        goto block_43;
    }
    var_r0_3 = NULL;
    goto end_for_47;
block_43:
    var_r0_3 = var_r6_3->next;
    goto end_for_47;
block_44:
    if (var_r8 != NULL) {
        goto block_46;
    }
    var_r8 = NULL;
    goto loop_26;
block_46:
    var_r8 = var_r8->parent;
    goto loop_26;
end_for_47:
    var_r6 = var_r0_3;
    var_r10 += 1;
loop_48:
    if (var_r6 != NULL) {
        goto block_10;
    }
block_49:
    *var_r4 = var_r6;
    n = var_r10;
    var_r4 += 1;
    if (var_r6 == NULL) {
        goto block_51;
    }
    count += 1;
}
block_51:
    var_r5 += 2;
    var_ctr -= 1;
    if (var_ctr != NULL) {
        goto loop_6;
    }
block_52:
    return count;
}
#endif

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

/// #lb_800122F0

void lb_8001271C(GXTexObj* arg0, float x0, float arg2, float tex_width,
                 float tex_height, float scale_x, float scale_y)
{
#define SOLUTION 0
#if SOLUTION == 0
    f32 s, t;
    PAD_STACK(16);

    t = tex_width / GXGetTexObjWidth(arg0);
    s = tex_height / GXGetTexObjHeight(arg0);

    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    {
        GXPosition2f32(x0, -arg2);
        GXTexCoord2f32(0.0f, 0.0f);
    }
    {
        GXPosition2f32(x0 + tex_width * scale_x, -arg2);
        GXTexCoord2f32(s, 0.0f);
    }
    {
        GXPosition2f32(x0 + tex_width * scale_x,
                       -(arg2 + tex_height * scale_y));
        GXTexCoord2f32(s, t);
    }
    {
        GXPosition2f32(x0, -(arg2 + tex_height * scale_y));
        GXTexCoord2f32(0.0f, t);
    }
    GXEnd();

#elif SOLUTION == 1
    f32 y2;
    f32 x1;
    f32 s1;
    f32 t2;
    f32 y0;
    PAD_STACK(16);

    t2 = tex_width / GXGetTexObjWidth(arg0);
    s1 = tex_height / GXGetTexObjHeight(arg0);
    GXBegin(GX_QUADS, GX_VTXFMT0, 4);

    {
        y0 = -arg2;
        GXPosition2f32(x0, y0);
        x1 = x0 + (tex_width * scale_x);
        GXTexCoord2f32(0.0f, 0.0f);
        y2 = -(arg2 + (tex_height * scale_y));
    }
    {
        GXPosition2f32(x1, y0);
        GXTexCoord2f32(s1, 0.0f);
    }
    {
        GXPosition2f32(x1, y2);
        GXTexCoord2f32(s1, t2);
    }
    {
        GXPosition2f32(x0, y2);
        GXTexCoord2f32(0.0f, t2);
    }
    GXEnd();
#endif
#undef SOLUTION
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

/// #lb_80012994

/// #fn_80013614

void fn_800138AC(void* ptr)
{
    HSD_Free(ptr);
}

void lb_800138CC(HSD_GObj* gobj, int arg1)
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

/// #lb_800138EC

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

/// #lb_80014258

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

/// #lb_80014770

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
