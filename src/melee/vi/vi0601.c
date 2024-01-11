#include "vi/vi0601.h"

#include "vi/vi.h"

#include <sysdolphin/baselib/jobj.h>

void un_8031E6CC(void)
{
    un_8031CAAC();
}

void un_8031E6EC(HSD_GObj* gobj)
{
    HSD_JObjAnimAll((HSD_JObj*) gobj->hsd_obj);
}
