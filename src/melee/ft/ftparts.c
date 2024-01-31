#include "ft/forward.h"

#include "ft/ftparts.h"

#include "ft/fighter.h"
#include "ft/types.h"
#include "lb/lbrefract.h"

#include <placeholder.h>
#include <dolphin/mtx.h>
#include <dolphin/os/OSError.h>
#include <baselib/class.h>
#include <baselib/debug.h>
#include <baselib/gobj.h>
#include <baselib/jobj.h>
#include <baselib/mtx.h>
#include <baselib/pobj.h>

#define MAX_FT_PARTS 140

#define JOBJ_NEXT(jobj) ((jobj) == NULL ? NULL : (jobj)->next)
#define JOBJ_PARENT(jobj) ((jobj) == NULL ? NULL : (jobj)->parent)
#define JOBJ_CHILD(jobj) ((jobj) == NULL ? NULL : (jobj)->child)

HSD_JObjInfo ftJObj = { ftParts_JObjInfoInit };
HSD_JObjInfo ftIntpJObj = { ftParts_IntpJObjInfoInit };
HSD_PObjInfo ftPObj = { ftParts_PObjInfoInit };

// .data
static char ftParts_803C09E0[] = "fighter_class_library";
static char ftParts_803C09F8[] = "ft_intp_jobj";
static char ftParts_803C0A08[] = "ftparts.c";

static char ftParts_803C0A14[] = "envelope";
static char ftParts_803C0A20[] = "envelope->jobj";
static char ftParts_803C0A30[] = "jp->envelopemtx";
static char ftParts_803C0A40[] =
    "fighter parts model dobj num over! player %d\n";
static char ftParts_803C0A70[] = "fighter dobj num over! player %d\n";

static char ftParts_803C0A94[] = "fighter parts num over! player %d\n";
static char ftParts_803C0AB8[] = "fighter parts num not match! player %d\n";

static char ftParts_803C0AE0[] = "fighter parts model num over!\n";
static char ftParts_803C0B00[] = "can't find tobj!\n";
static char ftParts_803C0B14[] = "fighter parts model dobj num over!\n";

static char ftParts_803C0B38[] = "cant set fighter rot x!\n";
static char ftParts_803C0B54[] = "!(jobj->flags & JOBJ_USE_QUATERNION)";
static char ftParts_803C0B7C[] = "cant set fighter rot y!\n";
static char ftParts_803C0B98[] = "cant set fighter rot z!\n";

static char ftParts_803C0BB4[] = "cant get fighter rot x!\n";
static char ftParts_803C0BD0[] = "cant get fighter rot y!\n";

static char ftParts_803C0BEC[] = "cant get fighter rot z!\n";

// .bss
struct {
    Mtx mtx;
    u8 has_z_scale : 1;
    char unk_31[7];
} ft_jobj_scale;

// .sdata
static char ftParts_804D3A30[] = "jobj.h";
static char ftParts_804D3A38[] = "jobj";
static char ftParts_804D3A40[] = "ft_jobj";

static char ftParts_804D3A48[] = "jp->mtx";

static char ftParts_804D3A50[] = "ft_pobj";
static char ftParts_804D3A58[] = "0";

static char ftParts_804D3A5C[] = "rotate";

/// @todo Remove when strings can be reused
static inline float _HSD_JObjGetScaleX(HSD_JObj* jobj)
{
    ((jobj) ? ((void) 0) : __assert(ftParts_804D3A30, 875, ftParts_804D3A38));
    return jobj->scale.x;
}

/// @todo Remove when strings can be reused
static inline float _HSD_JObjGetScaleY(HSD_JObj* jobj)
{
    ((jobj) ? ((void) 0) : __assert(ftParts_804D3A30, 888, ftParts_804D3A38));
    return jobj->scale.y;
}

/// @todo Remove when strings can be reused
static inline float _HSD_JObjGetScaleZ(HSD_JObj* jobj)
{
    ((jobj) ? ((void) 0) : __assert(ftParts_804D3A30, 901, ftParts_804D3A38));
    return jobj->scale.z;
}

void ftParts_JObjMakePositionMtx(HSD_JObj* jobj, Mtx mtx, Mtx rmtx)
{
    Fighter* fighter = (Fighter*) HSD_GObj_804D7814->user_data;

    hsdJObj.make_pmtx(jobj, mtx, rmtx);

    if (fighter->x34_scale.z != 1.0F) {
        Mtx temp_mtx;
        float scale_z = _HSD_JObjGetScaleZ(jobj);
        float scale_y = _HSD_JObjGetScaleY(jobj);
        float scale_x = _HSD_JObjGetScaleX(jobj);
        PSMTXScale(temp_mtx, 1.0F / scale_x, 1.0F / scale_y, 1.0F / scale_z);
        PSMTXConcat(rmtx, temp_mtx, ft_jobj_scale.mtx);
        HSD_MtxInverse(rmtx, temp_mtx);
        PSMTXConcat(ft_jobj_scale.mtx, temp_mtx, ft_jobj_scale.mtx);
        ft_jobj_scale.has_z_scale = true;
    } else {
        ft_jobj_scale.has_z_scale = false;
    }
}

void ftParts_JObjInfoInit(void)
{
    hsdInitClassInfo(HSD_CLASS_INFO(&ftJObj), HSD_CLASS_INFO(&hsdJObj),
                     ftParts_803C09E0, ftParts_804D3A40, sizeof(HSD_JObjInfo),
                     sizeof(HSD_JObj));
    HSD_JOBJ_INFO(&ftJObj)->make_pmtx = ftParts_JObjMakePositionMtx;
}

void ftParts_80073758(HSD_JObj* arg0)
{
    NOT_IMPLEMENTED;
}

s32 ftParts_IntpJObjLoad(HSD_JObj* jobj, HSD_Joint* joint, HSD_JObj* parent)
{
    NOT_IMPLEMENTED;
}

void ftParts_IntpJObjInfoInit(void)
{
    hsdInitClassInfo(HSD_CLASS_INFO(&ftIntpJObj), HSD_CLASS_INFO(&hsdJObj),
                     ftParts_803C09E0, ftParts_803C09F8, sizeof(HSD_JObjInfo),
                     sizeof(HSD_JObj));
    HSD_JOBJ_INFO(&ftIntpJObj)->load = ftParts_IntpJObjLoad;
}

void ftParts_80073830(void)
{
    NOT_IMPLEMENTED;
}

void ftParts_800739B8(void)
{
    NOT_IMPLEMENTED;
}

void ftParts_80073CA8(void)
{
    NOT_IMPLEMENTED;
}

void ftParts_PObjInfoInit(void)
{
    hsdInitClassInfo(HSD_CLASS_INFO(&ftPObj), HSD_CLASS_INFO(&hsdPObj),
                     ftParts_803C09E0, ftParts_804D3A50, sizeof(HSD_PObjInfo),
                     sizeof(HSD_PObj));
    HSD_POBJ_INFO(&ftPObj)->load = lbRefract_PObjLoad;
    HSD_POBJ_INFO(&ftPObj)->setup_mtx = ftParts_PObjSetupMtx;
}

void ftParts_80074148(void)
{
    NOT_IMPLEMENTED;
}

void ftParts_80074170(void)
{
    NOT_IMPLEMENTED;
}

void ftParts_SetupParts(HSD_GObj* fighter_obj)
{
    HSD_JObj* jobj = fighter_obj->hsd_obj;
    Fighter* fighter = (Fighter*) fighter_obj->user_data;
    u32 part = 0;
    u32 tree_depth = 0;
    u32 dobj_count = 0;

    if (ftPartsTable[fighter->kind]->parts_num > MAX_FT_PARTS) {
        OSReport(ftParts_803C0A94, fighter->player_id);
        __assert(ftParts_803C0A08, 503, ftParts_804D3A58);
    }

    while (jobj != NULL) {
        if (ftParts_8007506C(fighter->kind, part) != 0) {
            fighter->parts[part].joint = NULL;
            part++;
            continue;
        }

        ftParts_80074194(fighter, &fighter->parts[part], jobj, &dobj_count,
                         tree_depth);
        part++;

        if (!(HSD_JObjGetFlags(jobj) & JOBJ_INSTANCE) &&
            JOBJ_CHILD(jobj) != NULL)
        {
            // Descend the left side of the tree
            jobj = JOBJ_CHILD(jobj);
            tree_depth++;
            continue;
        }

        if (JOBJ_NEXT(jobj) != NULL) {
            // Visit bottom nodes from left to right
            jobj = JOBJ_NEXT(jobj);
            continue;
        }

        while (true) {
            if (JOBJ_PARENT(jobj) == NULL) {
                // Finished
                jobj = NULL;
                break;
            } else {
                // Go back up the tree until we can continue to the right
                HSD_JObj* parent = JOBJ_PARENT(jobj);
                HSD_JObj* parent_next = JOBJ_NEXT(parent);

                if (parent_next != NULL) {
                    jobj = JOBJ_PARENT(jobj);
                    jobj = JOBJ_NEXT(jobj);
                    tree_depth--;
                    break;
                }

                jobj = JOBJ_PARENT(jobj);
                tree_depth--;
            }
        }
    }

    fighter->dobj_list.count = dobj_count;

    if (part != ftPartsTable[fighter->kind]->parts_num) {
        OSReport(ftParts_803C0AB8, fighter->player_id);
        __assert(ftParts_803C0A08, 546, ftParts_804D3A58);
    }
}

void ftParts_8007462C(void)
{
    NOT_IMPLEMENTED;
}

void ftParts_8007482C(void)
{
    NOT_IMPLEMENTED;
}

void ftParts_8007487C(unk_t item, u32* arg1, u8 costume_id, u32* arg3,
                      u32* arg4)
{
    NOT_IMPLEMENTED;
}

void ftParts_800749CC(HSD_GObj* arg0)
{
    NOT_IMPLEMENTED;
}

void ftParts_80074A4C(HSD_GObj* arg0, enum_t arg1, enum_t arg2)
{
    NOT_IMPLEMENTED;
}

s32 ftParts_80074A74(HSD_GObj* arg0, s32 arg1)
{
    NOT_IMPLEMENTED;
}

void ftParts_80074A8C(HSD_GObj* arg0)
{
    NOT_IMPLEMENTED;
}

void ftParts_80074ACC(ftCo_GObj* gobj)
{
    NOT_IMPLEMENTED;
}

void ftParts_80074B0C(HSD_GObj* gobj, int arg1, int arg2)
{
    NOT_IMPLEMENTED;
}

void ftParts_80074B6C(void)
{
    NOT_IMPLEMENTED;
}

void ftParts_80074CA0(u32* arg0, s32 arg1, u32* arg2)
{
    NOT_IMPLEMENTED;
}

void ftParts_80074D7C(u32* arg0, s32 arg1, u32* arg2)
{
    NOT_IMPLEMENTED;
}

void ftParts_80074E58(Fighter* fp)
{
    NOT_IMPLEMENTED;
}

Fighter_Part ftParts_8007500C(Fighter* fp, Fighter_Part part)
{
    NOT_IMPLEMENTED;
}

void ftParts_80075028(void)
{
    NOT_IMPLEMENTED;
}

u32 ftParts_8007506C(s32 ftkind, u32 part)
{
    NOT_IMPLEMENTED;
}

void ftParts_800750C8(void)
{
    NOT_IMPLEMENTED;
}

void ftParts_80075240(void)
{
    NOT_IMPLEMENTED;
}

void ftParts_80075304(void)
{
    NOT_IMPLEMENTED;
}

void ftParts_800753D4(Fighter* arg0, s32 arg1, unk_t arg2)
{
    NOT_IMPLEMENTED;
}

void ftParts_800755E8(void)
{
    NOT_IMPLEMENTED;
}

void ftParts_80075650(HSD_GObj* gobj, HSD_JObj* arg1, u32* arg2)
{
    NOT_IMPLEMENTED;
}

void ftParts_JObjSetRotation(HSD_JObj* jobj, Quaternion* quat)
{
    NOT_IMPLEMENTED;
}

void ftParts_8007592C(Fighter* arg0, s32 arg1, float arg2)
{
    NOT_IMPLEMENTED;
}

void ftParts_80075AF0(Fighter* arg0, s32 arg1, float arg2)
{
    NOT_IMPLEMENTED;
}

void ftParts_80075CB4(Fighter* arg0, s32 arg1, float arg2)
{
    NOT_IMPLEMENTED;
}

float ftParts_80075E78(Fighter* arg0, bool arg1)
{
    NOT_IMPLEMENTED;
}

float ftParts_80075F48(Fighter* arg0, s32 arg1)
{
    NOT_IMPLEMENTED;
}
