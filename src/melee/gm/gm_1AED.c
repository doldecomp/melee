#include "gm_1AED.h"

#include <melee/db/db_2253.h>
#include <melee/gm/gm_1A36.h>
#include <melee/gm/gmmain_lib.h>
#include <melee/gm/types.h>
#include <melee/lb/lb_00B0.h>
#include <melee/lb/lbaudio_ax.h>
#include <melee/lb/lbcardgame.h>
#include <melee/lb/lblanguage.h>
#include <sysdolphin/baselib/controller.h>

static u8 gm_804D6870;
static u16 gm_804D6872;

static int gm_803DD550_jp[] = {
    1, 1, 1, 1, 2, 2, 3, 1, 3, 2, 4, 1, 4, 4, 5, 1, 2, 4, 2, 3, 2, 2, 2,
};
static int gm_803DD550_us[] = {
    1, 1, 1, 1, 3, 3, 3, 3, 3, 3, 5, 2, 5, 2, 3, 2, 2, 4, 2, 3, 2, 1, 2,
};

static struct gm_80480DA8_t gm_80480DA8;

void gm_801AEE6C(int arg0, int arg1, int arg2)
{
    float scale = 1.12F;
    switch (arg0) {
    case 0:
        gm_801AE848(0);
        gm_801ADE1C(0, arg1, 0.0F, 0.0F);
        gm_801AE44C(0, scale * (arg2 - 2));
        gm_801AE544(0, -2.0F);
        gm_80480DA8.unk10 = 0;
        return;
    case 1:
        gm_801AE848(0);
        gm_801ADE1C(0, arg1, 0.0F, 0.0F);
        gm_801AE44C(0, scale * (arg2 - 2));
        gm_801AE050(0, 0, 3, -3.5F, -scale * (arg2 - 2));
        gm_801AE050(0, 1, 4, 3.5F, -scale * (arg2 - 2));
        gm_80480DA8.unk1C = 0U;
        gm_801AE640(0, gm_80480DA8.unk1C);
        gm_801AE74C(0, !gm_80480DA8.unk1C);
        gm_80480DA8.unk10 = 1;
        return;
    case 2:
        gm_801AE848(0);
        gm_801ADE1C(0, arg1, 0.0F, 0.0F);
        gm_801AE44C(0, scale * (arg2 - 2));
        gm_801AE050(0, 0, 2, -3.5F, -scale * (arg2 - 2));
        gm_801AE050(0, 1, 5, 3.5F, -scale * (arg2 - 2));
        gm_80480DA8.unk1C = 0U;
        gm_801AE640(0, gm_80480DA8.unk1C);
        gm_801AE74C(0, !gm_80480DA8.unk1C);
        gm_80480DA8.unk10 = 1;
        return;
    }
}

static inline bool gm_801AF0D4_inline(void)
{
    if (lb_8001C404(gm_80480DA8.unk0.unk4)) {
        if (gm_80480DA8.unk18 == 1) {
            gm_80480DA8.unk18 = 0;
            gm_80480DA8.unk14 = 1;
            return true;
        }
    } else if (gm_80480DA8.unk18 == 0) {
        gm_80480DA8.unk18 = 1;
        gm_80480DA8.unk14 = 1;
        return true;
    }
    return false;
}

int gm_801AF0D4(void)
{
    int saved_unk1C = gm_80480DA8.unk1C;

    if (gm_801AF0D4_inline()) {
        return 1;
    }

    if (gm_801AEDC8() & 0x40001 ? 1 : 0) {
        if (gm_80480DA8.unk1C != 0) {
            if (gm_80480DA8.unk10 != 0) {
                lbAudioAx_80024030(2);
            }
            gm_80480DA8.unk1C = 0;
        }
    } else if ((gm_801AEDC8() & 0x80002 ? 1 : 0)) {
        if (gm_80480DA8.unk1C < 1) {
            if (gm_80480DA8.unk10 != 0) {
                lbAudioAx_80024030(2);
            }
            gm_80480DA8.unk1C = 1;
        }
    }
    if (saved_unk1C != gm_80480DA8.unk1C) {
        gm_801AE640(0, gm_80480DA8.unk1C);
        gm_801AE74C(0, !gm_80480DA8.unk1C);
    }
    return 0;
}

static inline u8 set_gm_804D6870_inline(void)
{
    if ((HSD_PadCopyStatus->button & 0x40) &&
        (HSD_PadCopyStatus->button & 0x20) &&
        (HSD_PadCopyStatus->button & 0x100)) {
        gm_804D6870 = 1;
    }
    return gm_804D6870;
}

static inline bool gm_801AEDC8_flag_check(void)
{
    if (gm_801AEDC8() & 0x1100) {
        lbAudioAx_80024030(1);
        return true;
    }
    return false;
}

static inline int get_lang_val(int idx)
{
    int i;
    if (lbLang_IsSavedLanguageUS()) {
        i = idx - 2;
        return gm_803DD550_us[i];
    } else {
        i = idx - 2;
        return gm_803DD550_jp[i];
    }
}

static inline void unk_inline(void)
{
    if (gm_80480DA8.unk0.unk0 == 1) {
        gm_801AEE6C(2, 0x17, get_lang_val(0x17));
        gm_80480DA8.unk14 = 0x12;
    } else {
        gm_801AEE6C(2, 0x18, get_lang_val(0x18));
        gm_80480DA8.unk14 = 0x13;
    }
}

void gm_801AF250(void)
{
    u32 temp_r3 = lb_8001C87C();
    gm_80480DA8.unk18 = 1;
    switch (temp_r3) {
    case 1:
    case 2:
        if (gm_80480DA8.unk0.unk0 == 0) {
            gm_801AEE6C(1, 7, get_lang_val(6));
        } else {
            gm_801AEE6C(1, 6, get_lang_val(6));
            gm_80480DA8.unk1C = 1;
            gm_801AE640(0, gm_80480DA8.unk1C);
            gm_801AE74C(0, !gm_80480DA8.unk1C);
        }
        gm_80480DA8.unk14 = 2;
        return;
    case 3:
        gm_801AEE6C(1, 8, get_lang_val(8));
        gm_80480DA8.unk14 = 3;
        gm_80480DA8.unk1C = 1;
        gm_801AE640(0, gm_80480DA8.unk1C);
        gm_801AE74C(0, !gm_80480DA8.unk1C);
        return;
    case 4:
        gm_801AEE6C(1, 0xA, get_lang_val(0xA));
        gm_80480DA8.unk14 = 5;
        return;
    case 5:
        gm_801AEE6C(0, 0xE, get_lang_val(0xE));
        gm_80480DA8.unk14 = 9;
        return;
    case 6:
        gm_801AEE6C(0, 0xF, get_lang_val(0xF));
        gm_80480DA8.unk14 = 0xA;
        return;
    case 9:
        gm_801AEE6C(1, 0x10, get_lang_val(0x10));
        gm_80480DA8.unk14 = 0xB;
        gm_80480DA8.unk1C = 1U;
        gm_801AE640(0, gm_80480DA8.unk1C);
        gm_801AE74C(0, !gm_80480DA8.unk1C);
        return;
    case 10:
    case 11:
    case 13:
        gm_801AEE6C(0, 0x13, get_lang_val(0x13));
        gm_80480DA8.unk14 = 0xE;
        return;
    case 12:
        gm_801AEE6C(0, 0x14, get_lang_val(0x14));
        gm_80480DA8.unk14 = 0xF;
        return;
    case 14:
        gm_801AEE6C(0, 0x15, get_lang_val(0x15));
        gm_80480DA8.unk14 = 0x10;
        return;
    case 15:
        gm_801AEE6C(0, 0x16, get_lang_val(0x16));
        gm_80480DA8.unk18 = 0;
        gm_80480DA8.unk14 = 0x11;
        return;
    case 0:
    case 7:
    case 8:
    default:
        gm_801A4B60();
    }
}

void gm_801AF568(void)
{
    int temp_r29;
    u8 _[0x14];

    if (g_debugLevel >= 3 && set_gm_804D6870_inline() != 0) {
        if (HSD_PadCopyStatus->trigger & 0x40) {
            if (gm_804D6872 > 6) {
                gm_804D6872 -= 1;
                gm_801AEE6C(0, gm_804D6872, get_lang_val(gm_804D6872));
            }
        } else if ((HSD_PadCopyStatus->trigger & 0x20)) {
            if (gm_804D6872 < 0x18) {
                gm_804D6872 += 1;
                gm_801AEE6C(0, gm_804D6872, get_lang_val(gm_804D6872));
            }
        }
        if ((HSD_PadCopyStatus->button & 0x40) &&
            (HSD_PadCopyStatus->button & 0x20) &&
            (HSD_PadCopyStatus->button & 0x200)) {
            gm_801A4B60();
        }
        return;
    }

    switch (gm_80480DA8.unk14) {
    case 0:
        temp_r29 = lb_8001CBBC();
        gmMainLib_8015FA34();
        if (temp_r29 == 0 || temp_r29 == 2) {
            gm_80480DA8.unk8.unk0 = 1;
            gm_80480DA8.unk14 = 0x14;
        } else {
            gm_80480DA8.unk14 = 1;
        }
        break;
    case 1:
        gm_801AF250();
        break;
    case 2:
        if (!gm_801AF0D4() && gm_801AEDC8_flag_check()) {
            if (gm_80480DA8.unk1C == 0) {
                if (gm_80480DA8.unk0.unk0 == 0) {
                    gm_80480DA8.unk14 = 0;
                    lb_8001CBAC(0);
                } else {
                    gm_80480DA8.unk8.unk0 = 1;
                    gm_80480DA8.unk14 = 0x14;
                    lb_8001CBAC(0);
                    lb_8001CE00();
                }
            } else {
                unk_inline();
            }
        }
        break;
    case 3:
        if (!gm_801AF0D4() && gm_801AEDC8_flag_check()) {
            if (gm_80480DA8.unk1C == 0) {
                gm_801AEE6C(0, 9, get_lang_val(9));
                gm_80480DA8.unk14 = 4;
            } else {
                unk_inline();
            }
        }
        break;
    case 4:
        if (!gm_801AF0D4()) {
            if (!lb_8001CC4C()) {
                gm_801AEE6C(0, 0xB, get_lang_val(0xB));
                gm_80480DA8.unk14 = 6;
            } else {
                gm_801AEE6C(0, 0xD, get_lang_val(0xD));
                gm_80480DA8.unk14 = 8;
            }
        }
        break;
    case 5:
        if (!gm_801AF0D4() && gm_801AEDC8_flag_check()) {
            if (gm_80480DA8.unk1C == 0) {
                gm_801AEE6C(0, 0xB, get_lang_val(0xB));
                gm_80480DA8.unk14 = 6;
            } else {
                unk_inline();
            }
        }
        break;
    case 6:
        if (!gm_801AF0D4()) {
            if (!lb_8001C8BC()) {
                gm_801AEE6C(0, 0xC, get_lang_val(0xC));
                gm_80480DA8.unk14 = 7;
            } else {
                gm_801AEE6C(0, 0xD, get_lang_val(0xD));
                gm_80480DA8.unk14 = 8;
            }
        }
        break;
    case 7:
        if (!gm_801AF0D4() && gm_801AEDC8_flag_check()) {
            gm_80480DA8.unk8.unk0 = 1;
            gm_80480DA8.unk14 = 0x14;
            lb_8001CBAC(0);
        }
        break;
    case 8:
        if (!gm_801AF0D4() && gm_801AEDC8_flag_check()) {
            unk_inline();
        }
        break;
    case 9:
        if (!gm_801AF0D4() && gm_801AEDC8_flag_check()) {
            unk_inline();
        }
        break;
    case 10:
        if (!gm_801AF0D4() && gm_801AEDC8_flag_check()) {
            unk_inline();
        }
        break;
    case 11:
        if (!gm_801AF0D4() && gm_801AEDC8_flag_check()) {
            if (gm_80480DA8.unk1C == 0) {
                if (lb_8001B8C8(gm_80480DA8.unk0.unk4) == 0) {
                    gm_801AEE6C(0, 0x11, get_lang_val(0x11));
                    gm_80480DA8.unk14 = 0xC;
                } else {
                    gm_801AEE6C(0, 0x12, get_lang_val(0x12));
                    gm_80480DA8.unk14 = 0xD;
                }
            } else {
                unk_inline();
            }
        }
        break;
    case 12:
        if (!gm_801AF0D4() && gm_801AEDC8_flag_check()) {
            gm_80480DA8.unk14 = 1;
        }
        break;
    case 13:
        if (!gm_801AF0D4() && gm_801AEDC8_flag_check()) {
            unk_inline();
        }
        break;
    case 14:
        if (!gm_801AF0D4() && gm_801AEDC8_flag_check()) {
            unk_inline();
        }
        break;
    case 15:
        if (!gm_801AF0D4() && gm_801AEDC8_flag_check()) {
            unk_inline();
        }
        break;
    case 16:
        if (!gm_801AF0D4() && gm_801AEDC8_flag_check()) {
            unk_inline();
        }
        break;
    case 17:
        if (!gm_801AF0D4() && gm_801AEDC8_flag_check()) {
            unk_inline();
        }
        break;
    case 18:
        if (!gm_801AF0D4() && gm_801AEDC8_flag_check()) {
            if (gm_80480DA8.unk1C == 0) {
                gm_80480DA8.unk8.unk0 = 0;
                gm_80480DA8.unk14 = 0x14;
                lb_8001CBAC(4);
            } else {
                gm_80480DA8.unk14 = 1;
            }
        }
        break;
    case 19:
        if (!gm_801AF0D4() && gm_801AEDC8_flag_check()) {
            if (gm_80480DA8.unk1C == 0) {
                gm_80480DA8.unk8.unk0 = 0;
                gm_80480DA8.unk14 = 0x14;
                lb_8001CBAC(4);
            } else {
                gm_80480DA8.unk14 = 1;
            }
        }
        break;
    case 20:
        gm_801A4B60();
        break;
    default:
        gm_801A4B60();
        break;
    }
}

void gm_801B0264(struct gm_80480DA8_t* arg0)
{
    s32 var_r0;

    memzero(&gm_80480DA8, sizeof(gm_80480DA8));
    if (arg0 != 0U) {
        gm_80480DA8.unk0 = arg0->unk0;
    }
    if (gm_80480DA8.unk0.unk0 == 0) {
        var_r0 = 0;
    } else {
        var_r0 = 1;
    }
    gm_80480DA8.unk14 = var_r0;
    gm_80480DA8.unk8.unk4 = gm_80480DA8.unk0.unk5;
    lb_8001C550();
    lb_8001D164(0);
    gm_801ADDD8();
    gm_804D6870 = 0;
    gm_804D6872 = 6;
}

void gm_801B0304(struct gm_80480DA8_8_t* arg0)
{
    if (arg0 != NULL) {
        *arg0 = gm_80480DA8.unk8;
    }
    gm_801AE848(0);
}
