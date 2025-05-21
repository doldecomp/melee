#include "vi/vi0601.h"

#include "vi/vi.h"

#include <baselib/gobj.h>
#include <baselib/jobj.h>

void un_8031E6CC(void)
{
    vi_8031CAAC();
}

void un_8031E6EC(HSD_GObj* gobj)
{
    HSD_JObjAnimAll(GET_JOBJ(gobj));
}
