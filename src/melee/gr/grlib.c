#include "grlib.h"

#include "grbigblue.h"
#include "gricemt.h"
#include "ground.h"
#include "grrcruise.h"

#include <placeholder.h>

#include "baselib/forward.h"

#include "baselib/psappsrt.h"
#include "baselib/psstructs.h"
#include "cm/camera.h"
#include "ft/inlines.h"
#include "ft/types.h"
#include "gr/types.h"
#include "it/inlines.h"
#include "it/it_26B1.h"
#include "lb/lb_00F9.h"
#include "lb/types.h" // IWYU pragma: keep
#include "sc/types.h"

#include <math.h>
#include <baselib/gobjobject.h>
#include <baselib/gobjplink.h>
#include <baselib/gobjproc.h>
#include <baselib/particle.h>

/* 1C9BC8 */ static void grLib_801C9BC8(HSD_GObj*);
/* 1C9C40 */ static void grLib_801C9C40(HSD_GObj*);

extern StageInfo stage_info;
extern HSD_Generator* hsd_804D78FC;

static VecMtx grLib_8049EF58;
static Vec3 grLib_unusedvec1;
static Vec3 grLib_unusedvec2;

bool grLib_801C96E8(HSD_GObj* arg0)
{
    Ground* gp = arg0->user_data;
    return gp->x10_flags.b4;
}

HSD_Generator* grLib_801C96F8(s32 arg0, s32 arg1, Vec3* arg2)
{
    HSD_Generator* temp_r3;
    HSD_psAppSRT* phi_r30;
    f32 scale;

    temp_r3 = hsd_8039F05C(0, arg1, arg0);
    if (temp_r3 != NULL) {
        phi_r30 = temp_r3->appsrt;
        if (phi_r30 == NULL) {
            phi_r30 = psAddGeneratorAppSRT_begin(temp_r3, 1);
        } else {
            phi_r30->xA2 = 0;
        }
        if (phi_r30 == NULL) {
            hsd_8039D4DC(temp_r3);
            return NULL;
        }
        phi_r30->translate = *arg2;
        scale = Ground_801C0498();
        phi_r30->scale.x *= scale;
        phi_r30->scale.y *= scale;
        phi_r30->scale.z *= scale;
        temp_r3->pos.x = temp_r3->pos.y = temp_r3->pos.z = 0.0f;
    }
    return temp_r3;
}

void grLib_801C97DC(s32 arg0, s32 arg1, HSD_JObj* arg2)
{
    hsd_8039F6CC(0, arg1, arg0, arg2);
}

void grLib_801C9808(s32 arg0, s32 arg1, HSD_JObj* arg2)
{
    hsd_8039EFAC(0, arg1, arg0, arg2);
}

void grLib_801C9834(HSD_Generator* arg0)
{
    hsd_8039D4DC(arg0);
}

void grLib_801C9854(HSD_JObj* jobj)
{
    hsd_8039D5DC(jobj);
}

void grLib_801C9874(HSD_Generator* arg0)
{
    arg0->type |= 0x80;
    hsd_8039D4DC(arg0);
}

void grLib_801C98A0(HSD_JObj* jobj)
{
    HSD_Generator *cur, *next;

    if (jobj == NULL) {
        return;
    }

    for (cur = hsd_804D78FC; cur != NULL; cur = next) {
        next = cur->next;
        if (cur->jobj == jobj) {
            cur->type |= 0x80;
            hsd_8039D4DC(cur);
        }
    }
}

inline HSD_JObj* jobj_child(HSD_JObj* node)
{
    if (node == NULL) {
        return NULL;
    }
    return node->child;
}

inline HSD_JObj* jobj_next(HSD_JObj* node)
{
    if (node == NULL) {
        return NULL;
    }
    return node->next;
}

void grLib_801C9908(HSD_JObj* jobj)
{
    HSD_Generator* cur;
    HSD_Generator* next;

    if (jobj == NULL) {
        return;
    }

    for (cur = hsd_804D78FC; cur != NULL; cur = next) {
        next = cur->next;
        if (cur->jobj == jobj) {
            cur->type |= 0x80;
            hsd_8039D4DC(cur);
        }
    }

    if (jobj->flags & JOBJ_INSTANCE) {
        return;
    }

    for (jobj = jobj_child(jobj); jobj != NULL; jobj = jobj_next(jobj)) {
        grLib_801C9908(jobj);
    }
}

void grLib_801C99C0(s32 arg0, s32 arg1, HSD_JObj* arg2, s32 arg3)
{
    if (arg3 != 0) {
        hsd_8039EFAC(0, arg0, arg1, arg2);
    } else {
        hsd_8039F6CC(0, arg0, arg1, arg2);
    }
}

VecMtxPtr grLib_801C9A10(void)
{
    Ground_801C2D24(0, &grLib_8049EF58[0]);
    Ground_801C2D24(1, &grLib_8049EF58[1]);
    Ground_801C2D24(2, &grLib_8049EF58[2]);
    Ground_801C2D24(3, &grLib_8049EF58[3]);
    return grLib_8049EF58;
}

void grLib_801C9A70(enum_t arg0, Vec3* v)
{
    int i;
    switch (arg0) {
    case 0:
        i = 0;
        break;
    case 1:
        i = 1;
        break;
    case 2:
        i = 2;
        break;
    case 3:
        i = 3;
        break;
    default:
        HSD_ASSERT(290, 0);
#ifdef BUGFIX
        // Asserts 0 but the compiler doesn't know that.
        return;
#endif
    }
    *v = grLib_8049EF58[i];
}

void grLib_801C9B20(HSD_JObj* arg0, DynamicsDesc* arg1, DynamicsDesc* arg2)
{
    lb_8000FD48(arg0, arg2, arg1->count);
    lb_80011710(arg1, arg2);
}

void grLib_801C9B6C(void* arg0)
{
    lb_8000FD18(arg0);
}

void grLib_801C9B8C(void* arg0)
{
    lb_8001044C(arg0, 0, 0, 0.0f, 0, 0, 0, 0);
}

static void grLib_801C9BC8(HSD_GObj* gobj)
{
    HSD_JObj* jobj = gobj->hsd_obj;
    HSD_JObjAnimAll(jobj);
    Camera_8002A278(HSD_JObjGetTranslationX(jobj),
                    HSD_JObjGetTranslationY(jobj));
}

static void grLib_801C9C40(HSD_GObj* gobj)
{
    HSD_JObj* jobj = gobj->hsd_obj;
    HSD_AObj* aobj = jobj->aobj;

    HSD_JObjAnimAll(jobj);
    Camera_8002A278(HSD_JObjGetTranslationX(jobj),
                    HSD_JObjGetTranslationY(jobj));

    if (aobj == NULL || aobj->flags & 0x40000000) {
        HSD_GObjPLink_80390228(gobj);
    }
}

HSD_GObj* grLib_801C9CEC(s32 idx1)
{
    u8 tmp;
    HSD_GObj* gobj;
    HSD_JObj* jobj;
    s32 idx0;

    if (idx1 == 1) {
        idx0 = 0;
    } else if (idx1 == 2) {
        idx0 = 1;
    } else if (idx1 == 3) {
        idx0 = 2;
    } else if (idx1 == 4) {
        idx0 = 3;
    } else {
        return NULL;
    }

    if (stage_info.quake_model_set == NULL) {
        return NULL;
    }
    tmp = idx1;
    gobj = GObj_Create(HSD_GOBJ_CLASS_STAGE, 18, tmp);
    jobj = HSD_JObjLoadJoint(stage_info.quake_model_set->joint);

    HSD_GObjObject_80390A70(gobj, HSD_GObj_804D7849, jobj);
    if (idx1 == 1) {
        HSD_GObjProc_8038FD54(gobj, grLib_801C9BC8, 1);
    } else {
        HSD_GObjProc_8038FD54(gobj, grLib_801C9C40, 1);
    }

    HSD_JObjAddAnimAll(jobj, stage_info.quake_model_set->anims[idx0], NULL,
                       NULL);
    HSD_JObjReqAnimAll(jobj, 0);
    if (idx1 == 1) {
        HSD_ForeachAnim(jobj, 6, 0x20, HSD_AObjSetFlags, 3, 0x20000000);
    }
    return gobj;
}

int grLib_801C9E40(void)
{
    return stage_info.x708;
}

void grLib_801C9E50(s16 val)
{
    stage_info.x708 = val;
}

bool grLib_801C9E60(Vec3* v)
{
    InternalStageId id = stage_info.internal_stage_id;

    if (id == RCRUISE) {
        grRCruise_80201918(v);
        return true;
    }

    if (id == BIGBLUE) {
        grBigBlue_801EF7D8(v);
        return true;
    }

    if (id == ICEMTN) {
        grIceMt_801FA728(v);
        return true;
    }

    v->z = 0.0F;
    v->y = 0.0F;
    v->x = 0.0F;

    return false;
}

static inline bool PointInsideColl(CollData* cd, Vec3* point, float offset)
{
    f32 top, bottom;
    f32 left, right;
    f32 width, height;
    f32 topn;
    f32 x, y;
    f32 comp;

    top = cd->ecb.top.y;
    bottom = cd->ecb.bottom.y;
    topn = cd->cur_pos.y;
    height = top - bottom;
    comp = 0.5f * height + offset;
    y = 0.5f * (top + bottom) + topn - point->y;
    if (ABS(y) > comp) {
        return false;
    }

    right = cd->ecb.right.x;
    left = cd->ecb.left.x;
    topn = cd->cur_pos.x;
    width = right - left;
    comp = 0.5f * width + offset;
    x = 0.5f * (left + right) + topn - point->x;
    if (ABS(x) > comp) {
        return false;
    }

    return true;
}

bool grLib_801C9EE8(Vec3* point, float offset)
{
    Fighter* fp;
    Item* ip;
    Fighter_GObj* cur_fighter;
    Fighter_GObj* fighters;
    Item_GObj* cur_item;
    Item_GObj* items;

    fighters = HSD_GObj_Entities->fighters;
    for (cur_fighter = fighters; cur_fighter != NULL;
         cur_fighter = cur_fighter->next)
    {
        fp = GET_FIGHTER(cur_fighter);
        if (PointInsideColl(&fp->coll_data, point, offset)) {
            return true;
        }
    }

    items = HSD_GObj_Entities->items;
    for (cur_item = items; cur_item != NULL; cur_item = cur_item->next) {
        if (itGetKind(cur_item) != Pokemon_Random) {
            ip = GET_ITEM(cur_item);
            if (PointInsideColl(&ip->x378_itemColl, point, offset)) {
                return true;
            }
        }
    }
    return false;
}
