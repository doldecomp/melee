#include "gmscmemcard.h"

#include "gm_unsplit.h"
#include "gmmain_lib.h"
#include <melee/db/db.h>
#include <melee/lb/lb_00B0.h>
#include <melee/lb/lbcardgame.h>
#include <melee/lb/lbcardnew.h>
#include <melee/lb/lblanguage.h>
#include <melee/mn/inlines.h>
#include <sysdolphin/baselib/controller.h>

typedef struct {
    bool unk0;
    u8 mode_id;
} exitData;

struct enterData_x0_t {
    int unk0; ///< ::LbLanguage?
    u8 chan;  ///< memcard channel
    u8 mode_id;
};

typedef enum {
    tickDecision_0,
    tickDecision_1,
    tickDecision_2,
    tickDecision_3,
    tickDecision_4,
    tickDecision_5,
    tickDecision_6,
    tickDecision_7,
    tickDecision_8,
    tickDecision_9,
    tickDecision_10,
    tickDecision_11,
    tickDecision_12,
    tickDecision_13,
    tickDecision_14,
    tickDecision_15,
    tickDecision_16,
    tickDecision_17,
    tickDecision_18,
    tickDecision_19,
    tickDecision_20,
} tickDecision;

typedef struct {
    struct enterData_x0_t unk0;
    exitData unk8;
    int unk10;
    tickDecision decision;
    bool unk18;
    u8 unk1C;
} enterData;

/* 1AEE6C */ static void gm_801AEE6C(int, int, int);
/* 1AF0D4 */ static bool gm_801AF0D4(void);
/* 1AF250 */ static void gm_801AF250(void);

static u8 gm_804D6870;
static u16 gm_804D6872;

static int gm_803DD550_jp[] = {
    1, 1, 1, 1, 2, 2, 3, 1, 3, 2, 4, 1, 4, 4, 5, 1, 2, 4, 2, 3, 2, 2, 2,
};
static int gm_803DD550_us[] = {
    1, 1, 1, 1, 3, 3, 3, 3, 3, 3, 5, 2, 5, 2, 3, 2, 2, 4, 2, 3, 2, 1, 2,
};

static enterData enter_data;

void gm_801AEE6C(int arg0, int arg1, int arg2)
{
    float scale = 1.12F;
    switch (arg0) {
    case 0:
        gm_801AE848(0);
        gm_801ADE1C(0, arg1, 0.0F, 0.0F);
        gm_801AE44C(0, scale * (arg2 - 2));
        gm_801AE544(0, -2.0F);
        enter_data.unk10 = 0;
        return;
    case 1:
        gm_801AE848(0);
        gm_801ADE1C(0, arg1, 0.0F, 0.0F);
        gm_801AE44C(0, scale * (arg2 - 2));
        gm_801AE050(0, 0, 3, -3.5F, -scale * (arg2 - 2));
        gm_801AE050(0, 1, 4, 3.5F, -scale * (arg2 - 2));
        enter_data.unk1C = 0U;
        gm_801AE640(0, enter_data.unk1C);
        gm_801AE74C(0, !enter_data.unk1C);
        enter_data.unk10 = 1;
        return;
    case 2:
        gm_801AE848(0);
        gm_801ADE1C(0, arg1, 0.0F, 0.0F);
        gm_801AE44C(0, scale * (arg2 - 2));
        gm_801AE050(0, 0, 2, -3.5F, -scale * (arg2 - 2));
        gm_801AE050(0, 1, 5, 3.5F, -scale * (arg2 - 2));
        enter_data.unk1C = 0U;
        gm_801AE640(0, enter_data.unk1C);
        gm_801AE74C(0, !enter_data.unk1C);
        enter_data.unk10 = 1;
        return;
    }
}

static inline bool gm_801AF0D4_inline(void)
{
    if (lbCardNew_ProbeEx(enter_data.unk0.chan)) {
        if (enter_data.unk18 == 1) {
            enter_data.unk18 = 0;
            enter_data.decision = 1;
            return true;
        }
    } else if (enter_data.unk18 == 0) {
        enter_data.unk18 = 1;
        enter_data.decision = 1;
        return true;
    }
    return false;
}

bool gm_801AF0D4(void)
{
    int saved_unk1C = enter_data.unk1C;

    if (gm_801AF0D4_inline()) {
        return true;
    }

    if (gm_801AEDC8() & 0x40001 ? 1 : 0) {
        if (enter_data.unk1C != 0) {
            if (enter_data.unk10 != 0) {
                sfxMove();
            }
            enter_data.unk1C = 0;
        }
    } else if ((gm_801AEDC8() & 0x80002 ? 1 : 0)) {
        if (enter_data.unk1C < 1) {
            if (enter_data.unk10 != 0) {
                sfxMove();
            }
            enter_data.unk1C = 1;
        }
    }
    if (saved_unk1C != enter_data.unk1C) {
        gm_801AE640(0, enter_data.unk1C);
        gm_801AE74C(0, !enter_data.unk1C);
    }
    return false;
}

static inline u8 set_gm_804D6870_inline(void)
{
    if ((HSD_PadCopyStatus->button & HSD_PAD_L) &&
        (HSD_PadCopyStatus->button & HSD_PAD_R) &&
        (HSD_PadCopyStatus->button & HSD_PAD_A))
    {
        gm_804D6870 = 1;
    }
    return gm_804D6870;
}

static inline bool gm_801AEDC8_flag_check(void)
{
    if (gm_801AEDC8() & (HSD_PAD_START | HSD_PAD_A)) {
        sfxForward();
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
    if (enter_data.unk0.unk0 == 1) {
        gm_801AEE6C(2, 23, get_lang_val(23));
        enter_data.decision = 18;
    } else {
        gm_801AEE6C(2, 24, get_lang_val(24));
        enter_data.decision = 19;
    }
}

void gm_801AF250(void)
{
    u32 temp_r3 = lb_8001C87C();
    enter_data.unk18 = 1;
    switch (temp_r3) {
    case 1:
    case 2:
        if (enter_data.unk0.unk0 == 0) {
            gm_801AEE6C(1, 7, get_lang_val(6));
        } else {
            gm_801AEE6C(1, 6, get_lang_val(6));
            enter_data.unk1C = 1;
            gm_801AE640(0, enter_data.unk1C);
            gm_801AE74C(0, !enter_data.unk1C);
        }
        enter_data.decision = 2;
        return;
    case 3:
        gm_801AEE6C(1, 8, get_lang_val(8));
        enter_data.decision = 3;
        enter_data.unk1C = 1;
        gm_801AE640(0, enter_data.unk1C);
        gm_801AE74C(0, !enter_data.unk1C);
        return;
    case 4:
        gm_801AEE6C(1, 0xA, get_lang_val(0xA));
        enter_data.decision = 5;
        return;
    case 5:
        gm_801AEE6C(0, 0xE, get_lang_val(0xE));
        enter_data.decision = 9;
        return;
    case 6:
        gm_801AEE6C(0, 0xF, get_lang_val(0xF));
        enter_data.decision = 0xA;
        return;
    case 9:
        gm_801AEE6C(1, 0x10, get_lang_val(0x10));
        enter_data.decision = 0xB;
        enter_data.unk1C = 1U;
        gm_801AE640(0, enter_data.unk1C);
        gm_801AE74C(0, !enter_data.unk1C);
        return;
    case 10:
    case 11:
    case 13:
        gm_801AEE6C(0, 0x13, get_lang_val(0x13));
        enter_data.decision = 0xE;
        return;
    case 12:
        gm_801AEE6C(0, 0x14, get_lang_val(0x14));
        enter_data.decision = 0xF;
        return;
    case 14:
        gm_801AEE6C(0, 0x15, get_lang_val(0x15));
        enter_data.decision = 0x10;
        return;
    case 15:
        gm_801AEE6C(0, 0x16, get_lang_val(0x16));
        enter_data.unk18 = 0;
        enter_data.decision = 0x11;
        return;
    case 0:
    case 7:
    case 8:
    default:
        gm_801A4B60();
    }
}

void gm_Scene_MemCard_OnFrame(void)
{
    int temp_r29;
    u8 _[0x14];

    if (DbLevel >= DbLKind_DebugRom && set_gm_804D6870_inline() != 0) {
        if (HSD_PadCopyStatus->trigger & HSD_PAD_L) {
            if (gm_804D6872 > 6) {
                gm_804D6872 -= 1;
                gm_801AEE6C(0, gm_804D6872, get_lang_val(gm_804D6872));
            }
        } else if ((HSD_PadCopyStatus->trigger & HSD_PAD_R)) {
            if (gm_804D6872 < 0x18) {
                gm_804D6872 += 1;
                gm_801AEE6C(0, gm_804D6872, get_lang_val(gm_804D6872));
            }
        }
        if ((HSD_PadCopyStatus->button & HSD_PAD_L) &&
            (HSD_PadCopyStatus->button & HSD_PAD_R) &&
            (HSD_PadCopyStatus->button & HSD_PAD_B))
        {
            gm_801A4B60();
        }
        return;
    }

    switch (enter_data.decision) {
    case 0:
        temp_r29 = lb_8001CBBC();
        gmMainLib_8015FA34(temp_r29);
        if (temp_r29 == 0 || temp_r29 == 2) {
            enter_data.unk8.unk0 = 1;
            enter_data.decision = 0x14;
        } else {
            enter_data.decision = 1;
        }
        break;
    case 1:
        gm_801AF250();
        break;
    case 2:
        if (!gm_801AF0D4() && gm_801AEDC8_flag_check()) {
            if (enter_data.unk1C == 0) {
                if (enter_data.unk0.unk0 == 0) {
                    enter_data.decision = 0;
                    lbCardGame_SetCardStatus(LbCardStatus_0);
                } else {
                    enter_data.unk8.unk0 = 1;
                    enter_data.decision = 20;
                    lbCardGame_SetCardStatus(LbCardStatus_0);
                    lbCardGame_SaveChanges();
                }
            } else {
                unk_inline();
            }
        }
        break;
    case 3:
        if (!gm_801AF0D4() && gm_801AEDC8_flag_check()) {
            if (enter_data.unk1C == 0) {
                gm_801AEE6C(0, 9, get_lang_val(9));
                enter_data.decision = 4;
            } else {
                unk_inline();
            }
        }
        break;
    case 4:
        if (!gm_801AF0D4()) {
            if (!lb_8001CC4C()) {
                gm_801AEE6C(0, 0xB, get_lang_val(0xB));
                enter_data.decision = 6;
            } else {
                gm_801AEE6C(0, 0xD, get_lang_val(0xD));
                enter_data.decision = 8;
            }
        }
        break;
    case 5:
        if (!gm_801AF0D4() && gm_801AEDC8_flag_check()) {
            if (enter_data.unk1C == 0) {
                gm_801AEE6C(0, 0xB, get_lang_val(0xB));
                enter_data.decision = 6;
            } else {
                unk_inline();
            }
        }
        break;
    case 6:
        if (!gm_801AF0D4()) {
            if (!lb_8001C8BC()) {
                gm_801AEE6C(0, 0xC, get_lang_val(0xC));
                enter_data.decision = 7;
            } else {
                gm_801AEE6C(0, 0xD, get_lang_val(0xD));
                enter_data.decision = 8;
            }
        }
        break;
    case 7:
        if (!gm_801AF0D4() && gm_801AEDC8_flag_check()) {
            enter_data.unk8.unk0 = 1;
            enter_data.decision = 0x14;
            lbCardGame_SetCardStatus(0);
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
            if (enter_data.unk1C == 0) {
                if (lb_8001B8C8(enter_data.unk0.chan) == 0) {
                    gm_801AEE6C(0, 0x11, get_lang_val(0x11));
                    enter_data.decision = 0xC;
                } else {
                    gm_801AEE6C(0, 0x12, get_lang_val(0x12));
                    enter_data.decision = 0xD;
                }
            } else {
                unk_inline();
            }
        }
        break;
    case 12:
        if (!gm_801AF0D4() && gm_801AEDC8_flag_check()) {
            enter_data.decision = 1;
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
            if (enter_data.unk1C == 0) {
                enter_data.unk8.unk0 = 0;
                enter_data.decision = tickDecision_20;
                lbCardGame_SetCardStatus(LbCardStatus_4);
            } else {
                enter_data.decision = 1;
            }
        }
        break;
    case 19:
        if (!gm_801AF0D4() && gm_801AEDC8_flag_check()) {
            if (enter_data.unk1C == 0) {
                enter_data.unk8.unk0 = 0;
                enter_data.decision = tickDecision_20;
                lbCardGame_SetCardStatus(LbCardStatus_4);
            } else {
                enter_data.decision = tickDecision_1;
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

static inline bool checkUnk0(void)
{
    if (enter_data.unk0.unk0 == 0) {
        return tickDecision_0;
    }
    return tickDecision_1;
}

void gm_Scene_MemCard_OnEnter(void* user_data)
{
    enterData* data = user_data;

    memzero(&enter_data, sizeof(enter_data));
    if (data != NULL) {
        enter_data.unk0 = data->unk0;
    }
    enter_data.decision = checkUnk0();
    enter_data.unk8.mode_id = enter_data.unk0.mode_id;
    lbCardNew_AllocWorkArea();
    lbCardGame_LoadArchive(0);
    gm_801ADDD8();
    gm_804D6870 = 0;
    gm_804D6872 = 6;
}

void gm_Scene_MemCard_OnExit(void* user_data)
{
    exitData* data = user_data;
    if (data != NULL) {
        *data = enter_data.unk8;
    }
    gm_801AE848(0);
}
