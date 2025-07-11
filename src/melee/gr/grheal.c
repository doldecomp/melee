#include <platform.h>
#include "gr/forward.h"
#include "gr/grheal.h"
#include "placeholder.h"
#include "baselib/gobj.h"
#include "baselib/jobj.h"
#include "dolphin/types.h"
#include "gr/granime.h"
#include "gr/ground.h"
#include "gr/grzakogenerator.h"
#include "gr/stage.h"
#include "lb/lb_00F9.h"

void grHeal_8021EF38(void) {}
struct {
    int x0;
    int x4;
}* yaku;

extern struct yaku *grHeal_804D6AF0;
void grHeal_8021EF3C(void)
{
    grHeal_804D6AF0 = Ground_801C49F8();
    stage_info.unk8C.b4 = false;
    stage_info.unk8C.b5 = true;

    grHeal_8021EFEC(0);
    grHeal_8021EFEC(1);
    grHeal_8021EFEC(3);
    Ground_801C39C0();
    Ground_801C3BB4();
    Ground_801C3980(2.0F * Stage_GetBlastZoneTopOffset());
}

void grHeal_8021EFBC(void) {}

void grHeal_8021EFC0(void)
{
    grZakoGenerator_801CAE04(0);
}

bool grHeal_8021EFE4(void)
{
    return false;
}

/// #grHeal_8021EFEC

/// #grHeal_8021F0D8

bool grHeal_8021F170(void)
{
    return false;
}

void grHeal_8021F178(void) {}

void grHeal_8021F17C(void) {}

/// #grHeal_8021F180

bool grHeal_8021F41C(void)
{
    return false;
}

s32 fn_8021F424(void)
{
    Ground_GObj* ground;
    Ground* gp;

    ground = Ground_801C2BA4(1);
    if (ground != NULL) {
        gp = ground->user_data;
        if ((gp != NULL) && (gp->gv.unk.xC4 != 0)) {
            return 1;
        }
    }
    return 0;
}

void grHeal_8021F474(Ground_GObj* ground)
{
    Ground* gp;

    gp = ground->user_data;
    Ground_801C3D44(fn_8021F424, 10.0f, 20.0f);
    lb_800115F4();
    gp->gv.flatzone2.xC4 = 0;
}

void grHeal_8021F4BC(void) {}

void fn_8021F4C0(Ground* gp, void* arg2, s32 arg4, s32 arg5, s32 arg6)
{
    if ((((*(u8*)((u8*)arg4 + 0x34) >> 3U) & 0xF) == 1)
            && ((arg6 - 1) <= 1U)) 
        {
            gp->gv.unk.xC4 = 1;
        }
}

static char grHeal_803E851C[0x2C] = {
    0x67,
    0x72,
    0x68,
    0x65,
    0x61,
    0x6C,
    0x2E,
    0x63,
    0,
    0,
    0,
    0,
    0x2A,
    0x2A,
    0x2A,
    0x20,
    0x4E,
    0x6F,
    0x74,
    0x20,
    0x66,
    0x6F,
    0x75,
    0x6E,
    0x64,
    0x20,
    0x4E,
    0x65,
    0x78,
    0x74,
    0x20,
    0x50,
    0x6C,
    0x61,
    0x79,
    0x65,
    0x72,
    0x21,
    0x28,
    0x25,
    0x64,
    0x29,
    0xA,
    0,
};
static char grHeal_804D49E0[5] = "gobj";

void grHeal_8021F4E8(s32 arg0, HSD_JObj* parent_jobj)
{
    Ground_GObj* ground;
    HSD_JObj* jobj;
    HSD_JObj* child;

    ground = grHeal_8021EFEC(4U);
    if (ground == NULL) {
        __assert(grHeal_803E851C, 0x1B8U, "gobj");
    }
    grAnime_801C8138(ground, 4, 0);
    grAnime_801C7FF8(ground, 0, 7, 0, (f32) arg0, 0.0f);
    jobj = GET_JOBJ(ground);
    if (jobj == NULL) {
        child = NULL;
    } else {
        child = jobj->child;
    }
    HSD_JObjReparent(child, parent_jobj);
    HSD_JObjClearFlagsAll(child, 0x10U);
    Ground_801C4A08(ground);
}

void grHeal_8021F5C8(void) {}

bool grHeal_8021F5CC(void)
{
    return false;
}

void grHeal_8021F5D4(void) {}

void grHeal_8021F5D8(void) {}

void grHeal_8021F5DC(Ground_GObj* ground)
{
    Ground* gp;

    gp = ground->user_data;
    gp->x10_flags.b2 = false;
    grAnime_801C8138(ground, gp->map_id, 0);
}

bool grHeal_8021F618(void)
{
    return false;
}

void grHeal_8021F620(void) {}

void grHeal_8021F624(void) {}

void grHeal_8021F628(s32 arg0, HSD_JObj* jobj_parent)
{
    Ground_GObj* ground;
    HSD_JObj* jobj;
    HSD_JObj* child;

    ground = grHeal_8021EFEC(2U);
    if (ground == NULL) {
        __assert(grHeal_803E851C, 0x201U, "gobj");
    }
    grAnime_801C8138(ground, 2, 0);
    grAnime_801C7FF8(ground, 0, 7, 0, (f32) arg0, 0.0f);
    jobj = GET_JOBJ(ground);
    if (jobj == NULL) {
        child = NULL;
    } else {
        child = jobj->child;
    }
    HSD_JObjReparent(child, jobj_parent);
    Ground_801C4A08(ground);
}

void grHeal_8021F6F8(void) {}

bool grHeal_8021F6FC(void)
{
    return false;
}

void grHeal_8021F704(void) {}

void grHeal_8021F708(void) {}

static s32 grHeal_803E83B8[0x27] = {
    0x1D001E,
    0x1F0020,
    0x210022,
    0x230024,
    0x250026,
    0x270028,
    0x29002A,
    0x2B002C,
    0x2D002E,
    0x2F0030,
    0x310032,
    0x330034,
    0x350036,
    0,
    0x15,
    1,
    0x16,
    0x14,
    2,
    0x19,
    3,
    0xE,
    4,
    5,
    7,
    6,
    8,
    9,
    0xA,
    0xB,
    0x18,
    0xC,
    0xD,
    0xF,
    0x10,
    0x11,
    0x12,
    0x17,
    -1,
};

u32 grHeal_8021F70C(u32 character_id)
{
    s32 temp_r0;
    s32* var_r4;
    u32 var_r3;
    int i;

    var_r3 = character_id;
    // i = 0;
    if (var_r3 == 0x13) {
        var_r3 = 0x12;
    }
//     var_r4 = &grHeal_803E851C[0xD];
// loop_5:
//     temp_r0 = *var_r4;
//     if (temp_r0 != -1) {
//         if ((s32) var_r3 != temp_r0) {
//             var_r4 += 4;
//             var_r6 += 1;
//             goto loop_5;
//         }
//     }

    for (i = 0; i < 0x27; i++) {

    }
    if (grHeal_803E83B8[i] == -1) {
        OSReport("*** Not found Next Player!(%d)\n", i);
        i = 0;
    }
    return i;
}

/// #grHeal_8021F79C

bool grHeal_8021F830(void)
{
    return false;
}

bool grHeal_8021F838(void)
{
    return true;
}
