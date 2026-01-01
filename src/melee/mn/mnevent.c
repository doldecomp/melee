#include "mnevent.h"

#include <platform.h>
#include <sysdolphin/baselib/jobj.h>

extern f32 mnEvent_804DC150;
extern double mnEvent_804DC158;

u8 gm_80164024(u8);
void lb_80011E24(void*, ...);

void mnEvent_8024D0CC(HSD_GObj* gobj, s32 event_id) {
    HSD_JObj* jobj;
    HSD_JObj* child;
    s32 dummy;
    f32 frame;

    jobj = *(HSD_JObj**)((u8*)gobj + 0x28);
    if (event_id == 0x21) {
        frame = mnEvent_804DC150;
    } else {
        u8 result = gm_80164024((u8)event_id);
        frame = (f32)result;
    }
    lb_80011E24(jobj, &child, 4, -1);
    HSD_JObjReqAnimAll(child, frame);
    HSD_JObjAnimAll(child);
}
