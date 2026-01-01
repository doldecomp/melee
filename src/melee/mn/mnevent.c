#include "mnevent.h"

#include <platform.h>
#include <sysdolphin/baselib/jobj.h>
#include <sysdolphin/baselib/sislib.h>

extern f32 mnEvent_804DC150;
extern double mnEvent_804DC158;
extern f32 mnEvent_804DC194;
extern f32 mnEvent_804DC198;
extern f32 mnEvent_804DC16C;
extern f32 mnEvent_804DC174;
extern f32 mnEvent_804DC178;
extern f32 mnEvent_804DC19C;

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

void mnEvent_8024D7E0(HSD_GObj* gobj, s32 idx) {
    u8* data;
    HSD_Text* text;
    s32 text_id;
    s32 dummy;

    data = *(u8**)((u8*)gobj + 0x2C);
    if ((text = *(HSD_Text**)(data + 0x78)) != NULL) {
        HSD_SisLib_803A5CC4(text);
    }
    text_id = idx * 2 + 0x155;
    text = HSD_SisLib_803A5ACC(0, 1, mnEvent_804DC194, mnEvent_804DC198, 
                               mnEvent_804DC16C, mnEvent_804DC174, mnEvent_804DC178);
    *(HSD_Text**)(data + 0x78) = text;
    {
        f32 val = mnEvent_804DC19C;
        text->font_size.x = val;
        text->font_size.y = val;
    }
    HSD_SisLib_803A6368(text, text_id);
}
