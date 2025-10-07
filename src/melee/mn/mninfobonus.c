#include "mninfobonus.h"

#include <gm/gm_16AE.h>
#include <baselib/gobj.h>
#include <baselib/jobj.h>
#include <baselib/sislib.h>

#include "mninfobonus.static.h"

int inline mnInfoBonus_802528F8_inline(int j)
{
    if (*mnInfoBonus_804D6C80)
    {
        return TRUE;
    }
    return gm_8016F120(j);
}

int mnInfoBonus_802528F8(void) {
    int unused;
    int var_r30 = 0;
    int var_r29 = mnInfoBonus_804A09B0.x0;
    int i;
    for (i = 0;;i++) {
        int j = mnInfoBonus_803EFCE8[i];
        if (j == 0x100) {
            break;
        }

        if (var_r29 != 0) {
            if (mnInfoBonus_802528F8_inline(j)) {
                var_r29--;
            }
        } else {
            if (mnInfoBonus_802528F8_inline(j)) {
                var_r30++;
            }
        }
    }
    return var_r30;
}

void inline mnInfoBonus_80252ADC_inline(HSD_Text* text)
{
    text->x34.x = 0.034F;
    text->x34.y = 0.034F;
}

void mnInfoBonus_80252ADC(void)
{
    struct mnInfoBonus_804A09B0_t* o = &mnInfoBonus_804A09B0;
    int i = 0;
    u64 pad_0 = 0;
    for ( ; i < 5; ++i) {
        o->x4[i] = HSD_SisLib_803A5ACC(0, 1, -14.F, -6.35F + 2.77F * (float) i, 17.F, 8.9F, 1.25F);
        mnInfoBonus_80252ADC_inline(o->x4[i]);
        o->x4[i]->x4A = 2;
        
        o->x2C[i] = HSD_SisLib_803A5ACC(0, 1, -14.F, -5.F + 2.77F * (float) i, 17.F, 8.9F, 1.25F);
        mnInfoBonus_80252ADC_inline(o->x2C[i]);
        o->x2C[i]->x4A = 2;
        
        o->x18[i] = HSD_SisLib_803A5ACC(0, 1, -4.7500005F, -6.25F + 2.77F * (float) i, 17.F, 18.5F, 2.5F);
        mnInfoBonus_80252ADC_inline(o->x18[i]);
        if (i == 4)
            mnInfoBonus_802529B4();
    }
}

inline HSD_JObj* fn_80252E4C_inline_GetJObjNext(HSD_JObj* jobj)
{
    if (jobj == NULL) return NULL;
    return jobj->next;
}

inline HSD_JObj* fn_80252E4C_inline_GetJObjChild(HSD_JObj* jobj)
{
    if (jobj == NULL) return NULL;
    return jobj->child;
}

void fn_80252E4C(HSD_GObj* arg0) {
    HSD_JObj* temp_r30 = GET_JOBJ(arg0);
    struct mnInfoBonus_804A09B0_t* o = &mnInfoBonus_804A09B0;
    // definitely an int instead of u32
    if (o->x48 < 0xC8) {
        o->x48++;
    } else {
        o->x48 = 0;
    }
    if (o->x0 > 0) {
        HSD_JObjClearFlags(fn_80252E4C_inline_GetJObjNext(fn_80252E4C_inline_GetJObjChild(temp_r30)), 0x10);
    } else {
        HSD_JObjSetFlags(fn_80252E4C_inline_GetJObjNext(fn_80252E4C_inline_GetJObjChild(temp_r30)), 0x10);
    }
    if (mnInfoBonus_802528F8() /* TODO don't inline! */ > 5) {
        HSD_JObjClearFlags(fn_80252E4C_inline_GetJObjChild(temp_r30), 0x10U);
    } else {
        HSD_JObjSetFlags(fn_80252E4C_inline_GetJObjChild(temp_r30), 0x10U);
    }
    HSD_JObjReqAnimAll(temp_r30, (f32)o->x48);
    HSD_JObjAnimAll(temp_r30);
}
