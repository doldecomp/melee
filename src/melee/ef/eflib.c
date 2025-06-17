#include <placeholder.h>

#include "baselib/forward.h"
#include "ef/forward.h"

#include "eflib.h"

#include "types.h"

#include "baselib/gobj.h"
#include "baselib/gobjgxlink.h"
#include "baselib/gobjobject.h"
#include "baselib/gobjplink.h"
#include "baselib/gobjproc.h"
#include "baselib/gobjuserdata.h"
#include "lb/lb_00F9.h"

#include <runtime.h>
#include <baselib/jobj.h>
#include <baselib/particle.h>
#include <baselib/psappsrt.h>

/// #efLib_8005B4B8

/// #efLib_8005B704

/// #efLib_8005B780

/// #efLib_DestroyAll

/// #efLib_PauseAll

/// #efLib_ResumeAll

/// #Effect_RemoveUserData

/// #efLib_8005BBB4

/// #fn_8005BC50

extern M2C_UNK efAsync_803C025C;
extern u32 efLib_804D64E8;
extern u32 efLib_804D64EC;
extern s32 efLib_804D64F0;
static s8 efLib_803BF7A0[0x18] = "Duplicate Free %08X\n";
HSD_ObjAllocData Effect_AllocData;
static HSD_JObj** efLib_80458EE0;
static s8 efLib_804D39A0[8] = "eflib.c";
static s8 efLib_804D39A8 = 0x30;

Effect* efLib_8005BE88(int arg0, HSD_GObj* parent_gobj)
{
    Effect* ep;
    EffectDesc* desc;

    // desc = (void*) M2C_FIELD((&efAsync_803C025C + ((arg0 / 1000) * 0xC)),
    // s32*,
    //                          8) +
    //        ((arg0 % 1000) * 0x14);
    desc = NULL;

    if (efLib_804D64E8 == 0) {
        if (efLib_804D64EC >= 64) {
            efLib_8005BBB4();
        }
        efLib_804D64EC += 1;
    }
    {
        Effect* ep1 = HSD_ObjAlloc(&Effect_AllocData);
        {
            Effect* ep2 = ep1;
            if (ep2 == NULL) {
                ep = NULL;
            } else {
                ep2->x0 = NULL;
                ep = ep2;
                ep2->gobj = NULL;
                ep2->xC = 0;
                ep2->x10 = 0;
                ep2->x28 = 0;
                ep2->x26 = 0;
                ep2->x27 = 0;
                ep2->x29 = efLib_804D64E8;
            }
        }
        if (ep == NULL) {
            return NULL;
        }
        if (parent_gobj == NULL && ep->x29) {
            OSReport("error no parent gobj!\n", ep1, ep1);
            __assert("eflib.c", 177, "0");
        }
    }
    {
        HSD_GObj* ret_gobj;
        { ///@ todo Inline that returns @c ret_gobj?
            u8 p_link;
            if (arg0 >= 27 || arg0 < 25) {
                p_link = 11;
            } else {
                p_link = 12;
            }
            ep->parent_gobj = parent_gobj;
            ret_gobj = GObj_Create(HSD_GOBJ_CLASS_EFFECT, p_link, 0);
        }
        {
            HSD_GObj* gobj = ret_gobj;
            ep->gobj = gobj;
            if (gobj == NULL) {
                if (ep->gobj != NULL) {
                    if (M2C_FIELD(ep, u8*, 41) == 0) {
                        efLib_804D64EC -= 1;
                    }
                    HSD_ObjFree(&Effect_AllocData, ep);
                } else {
                    OSReport("Duplicate Free %08X\n", ep, ret_gobj);
                    __assert("eflib.c", 0x35, "0");
                }
                return NULL;
            }
        }
    }
    GObj_SetupGXLink(ep->gobj, HSD_GObj_JObjCallback, 7, 1);
    GObj_InitUserData(ep->gobj, 8, Effect_RemoveUserData, ep);
    {
        HSD_JObj* jobj = HSD_JObjLoadJoint(desc->model_desc.joint);
        if (jobj == NULL) {
            HSD_GObjPLink_80390228(ep->gobj);
            return NULL;
        }
        HSD_GObjObject_80390A70(ep->gobj, HSD_GObj_804D7849, jobj);
        if (((10.0f * M2C_FIELD(desc, f32*, 0)) / /* % */ 10) != 0) {
            lb_80011C18(jobj, 0x08000000);
        }
        ep->x24 = desc->x0;
        if (ep->x24 != 0) {
            ++ep->x24;
        }
        {
            HSD_ShapeAnimJoint* sjoint = desc->model_desc.shapeanim_joint;
            HSD_AnimJoint* ajoint = desc->model_desc.animjoint;
            intptr_t temp_r3_5 = -((intptr_t) sjoint);
            HSD_MatAnimJoint* mjoint = desc->model_desc.matanim_joint;
            intptr_t temp_r3_6 = -((intptr_t) ajoint);
            if ((((temp_r3_5 - (temp_r3_5 - 1)) - !M2C_CARRY) |
                 (((temp_r3_6 - (temp_r3_6 - 1)) - !M2C_CARRY) | !!mjoint)) !=
                0)
            {
                HSD_JObjAddAnimAll(jobj, ajoint, mjoint, sjoint);
                HSD_JObjReqAnimAll(jobj, 0.0f);
                {
                    s32 temp_r5_2 = efLib_804D64F0;
                    s32 temp_r4_2 = temp_r5_2 + 1;
                    s32 temp_r3_7 = temp_r5_2 * 4;
                    efLib_804D64F0 = temp_r4_2;
                    efLib_80458EE0[temp_r3_7] = jobj;
                    if (efLib_804D64F0 >= 32) {
                        OSReport("Over Anime Call\n", temp_r4_2, temp_r5_2);
                        __assert("eflib.c", 224, "0");
                    }
                }
            }
        }
    }
    HSD_GObjProc_8038FD54(ep->gobj, fn_8005BC50, 15);
    return ep;
}

/// #efLib_8005C1B4

/// #efLib_8005C2BC

/// #efLib_8005C3DC

/// #efLib_8005C5C4

/// #efLib_8005C6F4

/// #efLib_8005C814

/// #fn_8005C904

/// #efLib_8005C9A4

/// #fn_8005C9D0

/// #efLib_8005C9FC

/// #efLib_8005CAB0

/// #efLib_8005CB34

void efLib_8005CC2C(int arg0, HSD_JObj* arg1)
{
    UnkGeneratorStruct* particle = hsd_8039EFAC(0, arg0 / 1000, arg0, arg1);
    if (particle != NULL) {
        particle->x16_flags &= ~PSAPPSRT_UNK_B10;
    }
}

/// #efLib_8005CC84

/// #efLib_8005CD2C

/// #efLib_8005CE48

/// #efLib_8005CF40

/// #efLib_8005D044

/// #efLib_8005D174

/// #fn_8005DB20

/// #fn_8005DB70

/// #efLib_8005DBC0

/// #fn_8005DCD0

/// #efLib_8005DDB8

/// #efLib_8005DE94

/// #efLib_8005E090

/// #efLib_8005E1D8

/// #efLib_8005E2B4

/// #efLib_8005E3A0

/// #efLib_8005E648

/// #efLib_8005E950

/// #efLib_8005EB70

/// #efLib_8005EBC8

/// #efLib_8005EDDC

/// #efLib_8005F08C

/// #efLib_8005F270

/// #efLib_8005F454

/// #efLib_8005F748

/// #efLib_8005F774

/// #efLib_8005F864

/// #efLib_8005F990

/// #efLib_8005FAB8

/// #fn_8005FBE4

Effect* efLib_8005FCD8(int arg0, HSD_GObj* gobj, ef_UnkStruct1* arg2)
{
    UnkGeneratorMember* var_r3;
    UnkGeneratorStruct* temp_r3_2;
    Effect* ep = efLib_8005BE88(0, gobj);
    if (ep != NULL) {
        ep->x10 = fn_8005FBE4;
        ep->xC = gobj;
        ep->x18 = arg2->x0;
        ep->x14 = arg2->x4;
        ep->x18 = arg2->x8;
        temp_r3_2 = hsd_8039EFAC(0, arg0 / 1000, arg0, ep->x0->x0);
        if (temp_r3_2 != NULL) {
            var_r3 = temp_r3_2->x54;
            if (var_r3 == NULL) {
                var_r3 = psAddGeneratorAppSRT_begin(temp_r3_2, 0);
            }
            if (var_r3 != NULL) {
                var_r3->x4 = temp_r3_2;
                temp_r3_2->x16_flags &= ~PSAPPSRT_UNK_B09;
                temp_r3_2->x16_flags |= PSAPPSRT_UNK_B11;
            } else {
                hsd_8039D4DC(temp_r3_2);
            }
        }
    }
    return ep;
}
