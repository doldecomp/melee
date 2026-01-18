#include "grvenom.h"

#include <platform.h>

#include "gr/grcorneria.h"
#include "gr/stage.h"
#include "gr/grzakogenerator.h"
#include "gr/inlines.h"

#include <baselib/aobj.h>
#include <baselib/gobj.h>
#include <baselib/lobj.h>
#include "if/ifcoget.h"
#include "if/ifstatus.h"

/// #grVenom_8020362C

void grVenom_80203B14(bool arg) {}

/// #grVenom_80203B18

void grVenom_80203DD0(void)
{
    HSD_GObj* gobj;
    HSD_LObj* lobj;

    gobj = HSD_GObj_Entities->xC;
    while (gobj != NULL) {
        if (HSD_GObjGetClassifier(gobj) == 0xC) {
            lobj = GET_LOBJ(gobj);
            while (lobj != NULL) {
                HSD_ForeachAnim(lobj, LOBJ_TYPE, ALL_TYPE_MASK,
                                HSD_AObjSetFlags, AOBJ_ARG_AU, AOBJ_LOOP);
                lobj = HSD_LObjGetNext(lobj);
            }
            return;
        }
        gobj = HSD_GObjGetNext(gobj);
    }
}

void grVenom_80203E80(void)
{
    grZakoGenerator_801CAE04(0);
}

bool grVenom_80203EA4(void)
{
    return false;
}

/// #grVenom_80203EAC

void grVenom_80203F98(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    grAnime_801C8138(gobj, gp->map_id, 0);
}

bool grVenom_80203FC4(Ground_GObj* arg)
{
    return false;
}

void grVenom_80203FCC(Ground_GObj* arg) {}

void grVenom_80203FD0(Ground_GObj* arg) {}

/// #grVenom_80203FD4

bool grVenom_802040A4(Ground_GObj* arg)
{
    return false;
}

void grVenom_802040AC(Ground_GObj* arg) {}

void grVenom_802040B0(Ground_GObj* arg) {}

/// #fn_802040B4

/// #grVenom_802040F0

bool grVenom_8020427C(Ground_GObj* arg)
{
    return false;
}

/// #grVenom_80204284

void grVenom_80204424(Ground_GObj* arg) {}

/// #grVenom_80204428

bool grVenom_80204544(Ground_GObj* arg)
{
    return false;
}

/// #grVenom_8020454C

void grVenom_80204B84(Ground_GObj* arg) {}

/// #grVenom_80204B88

void grVenom_80204CE0(Ground_GObj* arg) {}

bool grVenom_80204CE4(Ground_GObj* arg)
{
    return false;
}

/// #grVenom_80204CEC

void grVenom_80204DB0(Ground_GObj* gobj)
{
    ifStatus_802F68F0();
    un_802FF620();
}

/// #grVenom_80204DD4

bool grVenom_80204EF4(Ground_GObj* arg)
{
    return false;
}

bool grVenom_80204EFC(Ground_GObj* arg)
{
    return Ground_801C2FE0(arg);
}

void grVenom_80204F1C(Ground_GObj* arg) {}

/// #grVenom_80204F20

bool grVenom_802052D8(Ground_GObj* arg)
{
    return false;
}

/// #grVenom_802052E0

/// #grVenom_802053B0

void grVenom_802056AC(Ground_GObj* arg) {}

/// #grVenom_802056B0

bool grVenom_80205750(Ground_GObj* arg)
{
    return false;
}

/// #grVenom_80205758

void grVenom_80205AD0(Ground_GObj* arg) {}

/// #grVenom_80205AD4

bool grVenom_80205DF0(Ground_GObj* arg)
{
    return false;
}

s32 grVenom_80205DF8(Vec3* pos)
{
    if (pos->x > Stage_GetBlastZoneRightOffset()) {
        return 1;
    }
    if (pos->x < Stage_GetBlastZoneLeftOffset()) {
        return 1;
    }
    if (pos->y > Stage_GetBlastZoneTopOffset()) {
        return 1;
    }
    if (pos->y < Stage_GetBlastZoneBottomOffset()) {
        return 1;
    }
    return 0;
}

/// #grVenom_80205E84

/// #grVenom_80205F30

void grVenom_80206870(Ground_GObj* arg) {}

/// #grVenom_80206874

bool grVenom_80206B68(Ground_GObj* arg)
{
    return false;
}

void grVenom_80206B70(Ground_GObj* arg)
{
    grVenom_80205F30(arg);
}

void grVenom_80206B90(Ground_GObj* arg) {}

void grVenom_80206B94(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    grCorneria_801E2550(gobj, &gp->gv.corneria);
}

bool grVenom_80206BBC(Ground_GObj* arg)
{
    return false;
}

void grVenom_80206BC4(Ground_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    grCorneria_801E277C(gobj, &gp->gv.corneria);
}

void grVenom_80206BEC(Ground_GObj* arg) {}

/// #grVenom_80206BF0

/// #grVenom_80206CB0

/// #grVenom_80206D10

DynamicsDesc* grVenom_80206D74(enum_t arg)
{
    return false;
}

/// #grVenom_80206D7C
