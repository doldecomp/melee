#include "mninfo.h"

#include "placeholder.h"

#include <sysdolphin/baselib/gobj.h>
#include <sysdolphin/baselib/gobjplink.h>
#include <sysdolphin/baselib/jobj.h>
#include <sysdolphin/baselib/sislib.h>
#include <melee/gm/gmmain_lib.h>
#include <melee/lb/lb_00F9.h>
#include <melee/lb/lblanguage.h>
#include <melee/mn/mnmain.h>
#include <melee/un/un_2FC9.h>

s32 mnInfo_80251A08(s32 arg0)
{
    switch (arg0) { /* irregular */
    case 0x3E:
        return 0;
    case 0x34:
        if (lbLang_IsSettingUS() != 0) {
            return 0;
        }
        return gmMainLib_8015D94C(arg0);
    case 0x35:
        if (lbLang_IsSettingJP() != 0) {
            return 0;
        }
        return gmMainLib_8015D94C(arg0);
    default:
        return gmMainLib_8015D94C(arg0);
    }
}

#pragma push
#pragma dont_inline on
s32 mnInfo_80251AA4(void)
{
    s32 i;
    s32 var_r30 = 0;

    for (i = 0; i < 0x42; i++) {
        if (mnInfo_80251A08(i) != 0) {
            var_r30++;
        }
    }
    return var_r30;
}
#pragma pop

/// #mnInfo_80251AFC

/// #mnInfo_80251D58

void mnInfo_80251F04(HSD_GObj* gobj, u32 idx, u32 arg2)
{
    MnInfoData* data;
    HSD_Text* text;
    s16 sp16;

    data = gobj->user_data;
    if (data->right_column[idx] != NULL) {
        HSD_SisLib_803A5CC4(data->right_column[idx]);
    }
    text = HSD_SisLib_803A5ACC(0, 0, -5.0f, (3.45f * idx) + -5.9f, 17.0f,
                               514.2857f, 142.85715f);
    data->right_column[idx] = text;
    text->font_size.x = 0.035f;
    text->font_size.y = 0.035f;
    text->default_fitting = 1;
    un_802FE3F8((s32) arg2, 0x4BD, &sp16, NULL);
    HSD_SisLib_803A6368(text, (s32) (u16) sp16);
}

/// #fn_80251FE4

static Vec3 mnInfo_803EFC08[0x12] = {
    { 0.0f, 199.0f, 0.0f },
    { 1.8e-42f, 1.802e-42f, 1.803e-42f },
    { 1.805e-42f, 2.1092525e-16f, 1.379729e31f },
    { 0.0f, 2.109659e-16f, 1.4748028e31f },
    { 0.0f, 225.43028f, 5.083402e31f },
    { 5.085142e31f, 7.153577e22f, 2.817505e20f },
    { 6.162976e-33f, 4.6115556e27f, 2.8237532e23f },
    { 0.0f, 3.0854143e32f, 1.6456562e19f },
    { 1.4757395e20f, 2.405757e8f, 2.6912729e20f },
    { 7.3738955e28f, 1.5307577e19f, 1.6892836e19f },
    { 1.8878586e28f, 2.405757e8f, 2.6912729e20f },
    { 7.3738955e28f, 1.5307577e19f, 1.6244036e19f },
    { 4.5346362e27f, 1.8878586e28f, 2.405757e8f },
    { 2.6912729e20f, 7.3738955e28f, 1.5307577e19f },
    { 1.710508e19f, 2.7487011e20f, 1.6892836e19f },
    { 1.8878586e28f, 2.405757e8f, 2.6912729e20f },
    { 7.3738955e28f, 1.5307577e19f, 1.7539375e19f },
    { 2.8395941e29f, 1.7935375e25f, 7.2243537e28f },
};

#pragma push
#pragma dont_inline on
void mnInfo_802522B8(HSD_GObj* gobj)
{
    s32 count;
    s32 i;
    MnInfoData* data;
    HSD_JObj* jobj;
    HSD_JObj* child;
    PAD_STACK(12);

    jobj = gobj->hsd_obj;
    data = gobj->user_data;
    lb_80011E24(jobj, &child, 2, -1);
    if (data->scroll_idx != 0) {
        HSD_JObjClearFlagsAll(child, JOBJ_HIDDEN);
    } else {
        HSD_JObjSetFlagsAll(child, JOBJ_HIDDEN);
    }
    lb_80011E24(jobj, &child, 1, -1);

    count = 0;
    for (i = 0; i < 0x42; i++) {
        if (mnInfo_80251A08(i) != 0) {
            count++;
        }
    }

    if ((data->scroll_idx + 4) < count) {
        HSD_JObjClearFlagsAll(child, JOBJ_HIDDEN);
    } else {
        HSD_JObjSetFlagsAll(child, JOBJ_HIDDEN);
    }
    mn_8022ED6C(jobj, mnInfo_803EFC08);
}
#pragma pop

void fn_802523B8(HSD_GObj* gobj)
{
    HSD_GObjPLink_80390228(gobj);
}

/// #fn_802523D8

/// #fn_80252548

void mnInfo_80252720(MnInfoData* data)
{
    data->scroll_idx = 0;
    data->anim_timer = 10;
    data->description = NULL;
    data->left_column[0] = NULL;
    data->right_column[0] = NULL;
    data->left_column[1] = NULL;
    data->right_column[1] = NULL;
    data->left_column[2] = NULL;
    data->right_column[2] = NULL;
    data->left_column[3] = NULL;
    data->right_column[3] = NULL;
}

/// #mnInfo_80252758
