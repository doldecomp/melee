#include "lb_00F9.static.h"

#include "baselib/rumble.h"
#include "baselib/tobj.h"
#include "dolphin/pad.h"
#include "lb/lbarchive.h"
#include "lb/types.h"

#include <baselib/cobj.h>
#include <baselib/gobj.h>
#include <baselib/jobj.h>
#include <baselib/lobj.h>
#include <baselib/memory.h>
#include <melee/sc/types.h>

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

/// #lb_800100B0

/// #lb_800101C8

void lb_800103B8(void)
{
    lb_800101C8();
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

/// #lb_800115F4

/// #lb_80011710

/// #lb_800117F4

void lb_800119DC(Point3d* arg0, int arg1, float arg2, float arg3, float arg4)
{
    PAD_STACK(8);
    {
        struct lb_80011A50_t sp1C;
        sp1C.x0 = 2;
        sp1C.x1 = 0x64;
        sp1C.x4 = *arg0;
        sp1C.x20 = arg2;
        sp1C.x24 = arg3;
        sp1C.x28 = arg1;
        sp1C.x2C = arg4;
        sp1C.x10 = -10000.0f;
        sp1C.x14 = 10000.0f;
        sp1C.x18 = 10000.0f;
        sp1C.x1C = -10000.0f;
        lb_800100B0(&sp1C, arg2);
    }
}

void lb_80011A50(Vec3* arg0, int arg1, float arg2, float arg3, float arg4,
                 float arg5, float arg6, float arg7, float arg8)
{
    PAD_STACK(8);
    {
        struct lb_80011A50_t x2C;
        x2C.x0 = 1;
        x2C.x1 = 0;
        x2C.x4 = *arg0;
        x2C.x20 = arg2;
        x2C.x24 = arg3;
        x2C.x28 = arg1;
        x2C.x2C = arg4;
        x2C.x10 = arg5;
        x2C.x14 = arg6;
        x2C.x18 = arg7;
        x2C.x1C = arg8;
        lb_800100B0(&x2C, arg2);
    }
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

/// #lb_80011B74

/// #lb_80011C18

/**
 * @note: The number of HSD_JObjs that get passed into arg1 is the number of
 * variable arguments passed until -1 is passed.
 */
/// #lb_80011E24

/// #lb_8001204C

/// #lb_800121FC

void lb_800122C8(HSD_ImageDesc* arg0, u16 arg1, u16 arg2, int arg3)
{
    HSD_ImageDescCopyFromEFB(arg0, arg1, arg2, arg3, 1);
}

/// #lb_800122F0

/// #lb_8001271C

/// #lb_8001285C

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

bool lb_80013BB0(void)
{
    return true;
}

int lb_80013BB8(struct lb_80013FF0_t* arg0)
{
    arg0->x0 += *arg0->unk_8 & 0x03FFFFFF;
    ++arg0->unk_8;
    return 0;
}

int lb_80013BE4(ColorOverlay* arg0)
{
    arg0->x7C_color_enable = arg0->x7C_flag2 = false;
    ++arg0->x8_ptr1;
    return 0;
}

/// #lb_80013C18

/// #lb_80013D68

/// #lb_80013E3C

int lb_80013F78(ColorOverlay* arg0)
{
    s16 temp_r0;

    arg0->x74_light_rot_x =
        ((M2C_FIELD(arg0->x8_ptr1, s32*, 0) << 6) & 0xFFFC0000) >> 0x13;
    temp_r0 = M2C_FIELD(arg0->x8_ptr1, s16*, 2);
    arg0->x78_light_rot_yz =
        ((temp_r0 << 0x13) | ((temp_r0 >> 0xD) & 0x40000)) >> 0x13;
    ++arg0->x8_ptr1;
    return 0;
}

int lb_80013FF0(struct lb_80013FF0_t* arg0)
{
    arg0->x7C_1 = false;
    ++arg0->unk_8;
    return 0;
}

/// #lb_80014014

/// #lb_800140F8

int lb_80014234(struct lb_80013FF0_t* arg0)
{
    arg0->x7C_0 = false;
    ++arg0->unk_8;
    return 0;
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

/// #lb_80014638

/// #lb_80014770

/// #lb_800149E0
