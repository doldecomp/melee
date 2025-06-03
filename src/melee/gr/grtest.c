#include <platform.h>

#include "baselib/forward.h"

#include "baselib/gobj.h"
#include "gr/granime.h"
#include "gr/grzakogenerator.h"
#include "gr/inlines.h"

void grTest_80206E2C(void) {}

/// #grTest_80206E30

void grTest_80207014(void) {}

void grTest_80207018(void)
{
    grZakoGenerator_801CAE04(false);
}

bool grTest_8020703C(void)
{
    return false;
}

/// #grTest_80207044

void grTest_80207130(HSD_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    grAnime_801C8138(gobj, gp->map_id, 0);
}

bool grTest_8020715C(void)
{
    return false;
}

void grTest_80207164(void) {}

void grTest_80207168(void) {}

void grTest_8020716C(HSD_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    HSD_JObj* jobj = GET_JOBJ(gobj);

    Ground_801C2ED0(jobj, gp->map_id);
    grAnime_801C8138(gobj, gp->map_id, 0);
}

bool grTest_802071BC(void)
{
    return false;
}

/// #grTest_802071C4

void grTest_802073AC(void) {}

void grTest_802073B0(HSD_GObj* gobj)
{
    Ground_801C2FE0(gobj);
}

void grTest_802073D0(HSD_GObj* gobj)
{
    Ground* gp = GET_GROUND(gobj);
    grAnime_801C8138(gobj, gp->map_id, 0);
}

bool grTest_802073FC(void)
{
    return false;
}

void grTest_80207404(void) {}

void grTest_80207408(void) {}

bool grTest_8020740C(void)
{
    return false;
}

bool grTest_80207414(void)
{
    return true;
}
