#include "mninfobonus.h"
#include "mnmain.h"
#include "inlines.h"

#include <gm/gm_16AE.h>
#include <gm/gm_16F1.h>
#include <baselib/gobj.h>
#include <baselib/jobj.h>
#include <baselib/sislib.h>
#include <baselib/controller.h>
#include <baselib/gobjplink.h>
#include <db/db.h>
#include <lb/lbaudio_ax.h>

#include "mninfobonus.static.h"

inline int mnInfoBonus_802528F8_inline(int j)
{
    if (*mnInfoBonus_804D6C80) return TRUE;
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

inline int mnInfoBonus_802528F8_wrapper(void)
{
    return mnInfoBonus_802528F8();
}

inline int mnInfoBonus_802529B4_inline0(int i)
{
    if (*mnInfoBonus_804D6C80 != 0) return 1;
    return gm_8016F120(i);
}

inline int mnInfoBonus_802529B4_inline1(int i)
{
    return ((u16) gm_8016F208(i) - 2) * 3;
}

void mnInfoBonus_802529B4(void)
{
    struct mnInfoBonus_804A09B0_t* o = &mnInfoBonus_804A09B0;
    int text_idx = 0;
    int bonus_offset = o->x0;
    int var_r28 = 5;
    int i;

    for (i = 0; ; i++) {
        int temp_1 = mnInfoBonus_803EFCE8[i];
        if (temp_1 == 0x100)
            break;
        if (bonus_offset != 0) {
            if (mnInfoBonus_802529B4_inline0(temp_1) != 0)
                --bonus_offset;
        } else if (var_r28 != 0) {
            if (mnInfoBonus_802529B4_inline0(temp_1) != 0) {
                HSD_SisLib_803A6368(o->x4[text_idx], mnInfoBonus_802529B4_inline1(temp_1) + 0x1BA);
                HSD_SisLib_803A6368(o->x18[text_idx], mnInfoBonus_802529B4_inline1(temp_1) + 0x1BB);
                HSD_SisLib_803A6368(o->x2C[text_idx], mnInfoBonus_802529B4_inline1(temp_1) + 0x1BC);
                ++text_idx;
                --var_r28;
            }
        }
   }
}

inline void mnInfoBonus_80252ADC_inline(HSD_Text* text)
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

void fn_80252C50(HSD_GObj* gobj)
{
    struct mnInfoBonus_804A09B0_t* o = &mnInfoBonus_804A09B0;
    int i;
    u64 temp_r3;
    u32 pad_0;

    if (mn_804D6BC8.x0 != 0) {
        --mn_804D6BC8.x0;
        mn_804D6BC8.x2 = 0;
        mn_804D6BC8.x4 = 0;
        return;
    }
    if (o->x44 != 0) {
        if (o->x44 == 1)
            mnInfoBonus_80252ADC();
        --o->x44;
        return;
    }

    // TODO some GC/Wii decomp members are suspicious of this block. Investigate further
    // Context: inadvertent hack to remove an extra `li r29,0` operation using i = 0
    i = 0;
    temp_r3 = Menu_GetAllEvents();
    if (((u64) temp_r3 & 0x20) != 0) {
        lbAudioAx_80024030(i);
        mn_804A04F0.x11 = i;
        mn_80229894(0x1C, 1U, 3);
        for (i = 0; i < 5; ++i) {
    // Weird code end
            HSD_SisLib_803A5CC4(o->x4[i]);
            HSD_SisLib_803A5CC4(o->x2C[i]);
            HSD_SisLib_803A5CC4(o->x18[i]);
        }
        HSD_SisLib_803A5CC4(o->x40);
        HSD_GObjPLink_80390228(o->x4C);
        o->x4C = NULL;
        return;
    }
    // TODO inline button getter
    if (g_debugLevel >= 3 && HSD_PadCopyStatus->button & 0x40 && HSD_PadCopyStatus->button & 0x20 && HSD_PadCopyStatus->button & 0x100) {
        o->x0 = 0;
        *mnInfoBonus_804D6C80 = 1;
        mnInfoBonus_802529B4();
    }
    if (((u64) temp_r3 & 1) != 0) {
        if (o->x0 > 0) {
            lbAudioAx_80024030(2);
            --o->x0;
            mnInfoBonus_802529B4();
        }
    } else if (((u64) temp_r3 & 2) != 0 && mnInfoBonus_802528F8_wrapper() /* TODO don't inline! */ > 5) {
        lbAudioAx_80024030(2);
        ++o->x0;
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

void fn_80252E4C(HSD_GObj* arg0)
{
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
    if (mnInfoBonus_802528F8_wrapper() > 5) {
        HSD_JObjClearFlags(fn_80252E4C_inline_GetJObjChild(temp_r30), 0x10U);
    } else {
        HSD_JObjSetFlags(fn_80252E4C_inline_GetJObjChild(temp_r30), 0x10U);
    }
    HSD_JObjReqAnimAll(temp_r30, (f32)o->x48);
    HSD_JObjAnimAll(temp_r30);
}
