#include "grpushon.h"

#include <platform.h>

#include "gr/ground.h"
#include "gr/grzakogenerator.h"
#include "lb/types.h"

#include <baselib/random.h>

struct grPushOn_Entry {
    s32 x0;
    s16 x4;
    s16 x6;
};

static struct {
    char pad[0x18];
    bool x18;
    struct grPushOn_Entry x1c[0x21];
}* grPushOn_804D6AB8;

void grPushOn_802182C4(bool arg) {}

/// #grPushOn_802182C8

/// #grPushOn_80218330

void grPushOn_80218378(void)
{
    bool val;
    grZakoGenerator_801CAE04(NULL);
    val = grPushOn_804D6AB8->x18;
    if (val) {
        val = HSD_Randi(grPushOn_804D6AB8->x18);
    } else {
        val = false;
    }
    if (!val) {
        grZakoGenerator_801CAEB0(Ground_801C5840(), Ground_801C5940());
    }
}

bool grPushOn_802183DC(void)
{
    return false;
}

/// #grPushOn_802183E4

/// #grPushOn_802184CC

bool grPushOn_80218590(Ground_GObj* arg)
{
    return false;
}

void grPushOn_80218598(Ground_GObj* arg) {}

void grPushOn_8021859C(Ground_GObj* arg) {}

/// #grPushOn_802185A0

bool grPushOn_80218670(Ground_GObj* arg)
{
    return false;
}

/// #fn_80218678

/// #grPushOn_802186C8

void grPushOn_802187A4(Ground_GObj* arg) {}

/// #grPushOn_802187A8

bool grPushOn_80218880(Ground_GObj* arg)
{
    return false;
}

/// #grPushOn_80218888

void grPushOn_80218ED0(Ground_GObj* arg) {}

/// #grPushOn_80218ED4

/// #grPushOn_80218FC0

/// Ground collision callback for pushon stage elements.
/// Activates push behavior when collision flags indicate contact (b1234 == 1).
void fn_802190A0(Ground* gp, s32 joint_id, CollData* coll, s32 unk,
                 mpLib_GroundEnum ground_enum)
{
    if (((*(u8*) &coll->x34_flags >> 3U) & 0xF) == 1 &&
        (ground_enum - 1) <= 1U)
    {
        gp->u.map.xC4_b0 = true;
    }
}

/// #grPushOn_802190D0

void grPushOn_80219204(int arg0, int* out1, int* out2)
{
    int idx = arg0 - 0x99;
    *out1 = grPushOn_804D6AB8->x1c[idx].x0;
    *out2 = grPushOn_804D6AB8->x1c[idx].x4;
}

/// #grPushOn_80219230

/// #fn_802192A4

/// #grPushOn_80219458

bool grPushOn_80219528(Vec3* arg, int arg0, HSD_JObj* jobj)
{
    return true;
}
