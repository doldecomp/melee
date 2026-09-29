#include "mninfobonus.h"

#include <melee/sc/forward.h>
#include <sysdolphin/baselib/forward.h>

#include "inlines.h"
#include "mnmain.h"
#include <melee/db/db.h>
#include <melee/gm/gm_16F1.h>
#include <melee/gm/gmvs.h>
#include <melee/lb/lb_00B0.h>
#include <melee/lb/lbarchive.h>
#include <melee/lb/lbaudio_ax.h>
#include <melee/sc/types.h>
#include <sysdolphin/baselib/archive.h>
#include <sysdolphin/baselib/controller.h>
#include <sysdolphin/baselib/gobj.h>
#include <sysdolphin/baselib/gobjgxlink.h>
#include <sysdolphin/baselib/gobjobject.h>
#include <sysdolphin/baselib/gobjplink.h>
#include <sysdolphin/baselib/gobjproc.h>
#include <sysdolphin/baselib/jobj.h>
#include <sysdolphin/baselib/sislib.h>

static int mnInfoBonus_803EFCE8[0x101] = {
    0x00000000, 0x00000001, 0x00000002, 0x00000003, 0x00000004, 0x00000005,
    0x00000006, 0x00000007, 0x00000008, 0x00000009, 0x0000000A, 0x0000000B,
    0x0000000C, 0x0000000D, 0x0000000E, 0x0000000F, 0x00000010, 0x00000011,
    0x00000012, 0x00000013, 0x00000014, 0x00000015, 0x00000016, 0x00000017,
    0x00000018, 0x00000019, 0x0000001A, 0x0000001B, 0x0000001C, 0x0000001D,
    0x0000001E, 0x0000001F, 0x00000020, 0x00000021, 0x00000022, 0x00000023,
    0x00000024, 0x00000025, 0x00000026, 0x00000027, 0x00000028, 0x00000029,
    0x0000002A, 0x0000002B, 0x0000002C, 0x0000002D, 0x0000002E, 0x0000002F,
    0x00000030, 0x00000031, 0x00000032, 0x00000033, 0x00000034, 0x00000035,
    0x00000036, 0x00000037, 0x00000038, 0x00000039, 0x0000003A, 0x0000003B,
    0x0000003C, 0x0000003D, 0x0000003E, 0x0000003F, 0x00000040, 0x00000041,
    0x00000042, 0x00000043, 0x00000044, 0x00000045, 0x00000046, 0x00000047,
    0x00000048, 0x00000049, 0x0000004A, 0x0000004B, 0x0000004C, 0x0000004D,
    0x000000F9, 0x0000004E, 0x0000004F, 0x00000050, 0x00000051, 0x00000052,
    0x00000053, 0x00000054, 0x00000055, 0x00000056, 0x00000057, 0x00000058,
    0x00000059, 0x0000005A, 0x0000005B, 0x0000005C, 0x0000005D, 0x0000005E,
    0x0000005F, 0x00000060, 0x000000FA, 0x00000061, 0x00000062, 0x00000063,
    0x00000064, 0x00000065, 0x000000FB, 0x00000066, 0x00000067, 0x00000068,
    0x00000069, 0x0000006A, 0x0000006B, 0x0000006C, 0x000000FC, 0x0000006D,
    0x000000FD, 0x0000006E, 0x0000006F, 0x00000070, 0x00000071, 0x00000072,
    0x00000073, 0x00000074, 0x00000075, 0x00000076, 0x00000077, 0x00000078,
    0x00000079, 0x0000007A, 0x0000007B, 0x0000007C, 0x0000007D, 0x0000007E,
    0x0000007F, 0x00000080, 0x00000081, 0x00000082, 0x00000083, 0x00000084,
    0x00000085, 0x00000086, 0x00000087, 0x00000088, 0x00000089, 0x0000008A,
    0x0000008B, 0x0000008C, 0x0000008D, 0x0000008E, 0x0000008F, 0x00000090,
    0x00000091, 0x00000092, 0x00000093, 0x00000094, 0x00000095, 0x00000096,
    0x00000097, 0x00000098, 0x00000099, 0x0000009A, 0x0000009B, 0x0000009C,
    0x0000009D, 0x000000FE, 0x000000FF, 0x0000009E, 0x0000009F, 0x000000A0,
    0x000000A1, 0x000000A2, 0x000000A3, 0x000000A4, 0x000000A5, 0x000000A6,
    0x000000A7, 0x000000A8, 0x000000A9, 0x000000AA, 0x000000AB, 0x000000AC,
    0x000000AD, 0x000000AE, 0x000000AF, 0x000000B0, 0x000000B1, 0x000000B2,
    0x000000B3, 0x000000B4, 0x000000B5, 0x000000B6, 0x000000B7, 0x000000B8,
    0x000000B9, 0x000000BA, 0x000000BB, 0x000000BC, 0x000000BD, 0x000000BE,
    0x000000BF, 0x000000C0, 0x000000C1, 0x000000C2, 0x000000C3, 0x000000C4,
    0x000000C5, 0x000000C6, 0x000000C7, 0x000000C8, 0x000000C9, 0x000000CA,
    0x000000CB, 0x000000CC, 0x000000CD, 0x000000CE, 0x000000CF, 0x000000D0,
    0x000000D1, 0x000000D2, 0x000000D3, 0x000000D4, 0x000000D5, 0x000000D6,
    0x000000D7, 0x000000D8, 0x000000D9, 0x000000DA, 0x000000DB, 0x000000DC,
    0x000000DD, 0x000000DE, 0x000000DF, 0x000000E0, 0x000000E1, 0x000000E2,
    0x000000E3, 0x000000E4, 0x000000E5, 0x000000F6, 0x000000F7, 0x000000F8,
    0x000000E6, 0x000000E7, 0x000000E8, 0x000000E9, 0x000000EA, 0x000000EB,
    0x000000EC, 0x000000ED, 0x000000EE, 0x000000EF, 0x000000F0, 0x000000F1,
    0x000000F2, 0x000000F3, 0x000000F4, 0x000000F5, 0x00000100
};

struct mnInfoBonus_804A09B0_t {
    /*  +0 */ int x0;
    /*  +4 */ HSD_Text* x4[0x5];
    /* +18 */ HSD_Text* x18[0x5];
    /* +2C */ HSD_Text* x2C[0x5];
    /* +40 */ HSD_Text* x40;
    /* +44 */ int x44;
    /* +48 */ int x48;
    /* +4C */ HSD_GObj* x4C;
    /* +50 */ StaticModelDesc x50;
} mnInfoBonus_804A09B0;

static u8 mnInfoBonus_804D6C80[0x8];

static inline int mnInfoBonus_802528F8_inline(int j)
{
    if (*mnInfoBonus_804D6C80) {
        return true;
    }
    return gm_8016F120(j);
}

static inline void textSize(HSD_Text* text)
{
    text->font_size.x = 0.0521F;
    text->font_size.y = 0.0521F;
}

static void textSetup(struct mnInfoBonus_804A09B0_t* o)
{
    o->x40 =
        HSD_SisLib_803A5ACC(0, 1, -9.5F, 9.1F, 17.F, 364.68332F, 38.38772F);
    textSize(o->x40);
    HSD_SisLib_803A6368(o->x40, 0xA5);
}

int mnInfoBonus_802528F8(void)
{
    int unused;
    int var_r30 = 0;
    int var_r29 = mnInfoBonus_804A09B0.x0;
    int i;
    for (i = 0;; i++) {
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

static inline int mnInfoBonus_802528F8_wrapper(void)
{
    return mnInfoBonus_802528F8();
}

static inline int mnInfoBonus_802529B4_inline0(int i)
{
    if (*mnInfoBonus_804D6C80 != 0) {
        return 1;
    }
    return gm_8016F120(i);
}

static inline int mnInfoBonus_802529B4_inline1(int i)
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

    for (i = 0;; i++) {
        int temp_1 = mnInfoBonus_803EFCE8[i];
        if (temp_1 == 0x100) {
            break;
        }
        if (bonus_offset != 0) {
            if (mnInfoBonus_802529B4_inline0(temp_1) != 0) {
                --bonus_offset;
            }
        } else if (var_r28 != 0) {
            if (mnInfoBonus_802529B4_inline0(temp_1) != 0) {
                HSD_SisLib_803A6368(o->x4[text_idx],
                                    mnInfoBonus_802529B4_inline1(temp_1) +
                                        0x1BA);
                HSD_SisLib_803A6368(o->x18[text_idx],
                                    mnInfoBonus_802529B4_inline1(temp_1) +
                                        0x1BB);
                HSD_SisLib_803A6368(o->x2C[text_idx],
                                    mnInfoBonus_802529B4_inline1(temp_1) +
                                        0x1BC);
                ++text_idx;
                --var_r28;
            }
        }
    }
}

static inline void mnInfoBonus_80252ADC_inline(HSD_Text* text)
{
    text->x34.x = 0.034F;
    text->x34.y = 0.034F;
}

void mnInfoBonus_80252ADC(void)
{
    struct mnInfoBonus_804A09B0_t* o = &mnInfoBonus_804A09B0;
    int i = 0;
    u64 pad_0 = 0;
    for (; i < 5; ++i) {
        o->x4[i] = HSD_SisLib_803A5ACC(0, 1, -14.F, -6.35F + 2.77F * (float) i,
                                       17.F, 8.9F, 1.25F);
        mnInfoBonus_80252ADC_inline(o->x4[i]);
        o->x4[i]->default_alignment = 2;

        o->x2C[i] = HSD_SisLib_803A5ACC(0, 1, -14.F, -5.F + 2.77F * (float) i,
                                        17.F, 8.9F, 1.25F);
        mnInfoBonus_80252ADC_inline(o->x2C[i]);
        o->x2C[i]->default_alignment = 2;

        o->x18[i] = HSD_SisLib_803A5ACC(
            0, 1, -4.7500005F, -6.25F + 2.77F * (float) i, 17.F, 18.5F, 2.5F);
        mnInfoBonus_80252ADC_inline(o->x18[i]);
        if (i == 4) {
            mnInfoBonus_802529B4();
        }
    }
}

void fn_80252C50(HSD_GObj* gobj)
{
    struct mnInfoBonus_804A09B0_t* o = &mnInfoBonus_804A09B0;
    int i;
    u64 temp_r3;
    u32 pad_0;

    if (mn_804D6BC8.cooldown != 0) {
        --mn_804D6BC8.cooldown;
        mn_804D6BC8.x2 = 0;
        mn_804D6BC8.x4 = 0;
        return;
    }
    if (o->x44 != 0) {
        if (o->x44 == 1) {
            mnInfoBonus_80252ADC();
        }
        --o->x44;
        return;
    } ///< @todo some GC/Wii decomp members are suspicious of this block.
    // Investigate further Context: inadvertent hack to remove an extra `li
    // r29,0` operation using i = 0
    i = 0;
    temp_r3 = Menu_GetAllInputs();
    if ((temp_r3 & 0x20) != 0) {
        lbAudioAx_80024030(i);
        mn_804A04F0.entering_menu = i;
        mn_80229894(0x1C, 1U, 3);
        for (i = 0; i < 5; ++i) {
            // Weird code end
            HSD_SisLib_803A5CC4(o->x4[i]);
            HSD_SisLib_803A5CC4(o->x2C[i]);
            HSD_SisLib_803A5CC4(o->x18[i]);
        }
        HSD_SisLib_803A5CC4(o->x40);
        HSD_GObjFree(o->x4C);
        o->x4C = NULL;
        return;
    } ///< @todo inline button getter
    if (DbLevel >= DbLKind_DebugRom && HSD_PadCopyStatus->button & HSD_PAD_L &&
        HSD_PadCopyStatus->button & HSD_PAD_R &&
        HSD_PadCopyStatus->button & HSD_PAD_A)
    {
        o->x0 = 0;
        *mnInfoBonus_804D6C80 = 1;
        mnInfoBonus_802529B4();
    }
    if ((temp_r3 & 1) != 0) {
        if (o->x0 > 0) {
            sfxMove();
            --o->x0;
            mnInfoBonus_802529B4();
        }
    } else if ((temp_r3 & 2) != 0 &&
               mnInfoBonus_802528F8_wrapper() /* @todo don't inline! */ > 5)
    {
        sfxMove();
        ++o->x0;
        mnInfoBonus_802529B4();
    }
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
        HSD_JObjClearFlags(HSD_JObjGetNext(HSD_JObjGetChild(temp_r30)),
                           JOBJ_HIDDEN);
    } else {
        HSD_JObjSetFlags(HSD_JObjGetNext(HSD_JObjGetChild(temp_r30)),
                         JOBJ_HIDDEN);
    }
    if (mnInfoBonus_802528F8_wrapper() > 5) {
        HSD_JObjClearFlags(HSD_JObjGetChild(temp_r30), JOBJ_HIDDEN);
    } else {
        HSD_JObjSetFlags(HSD_JObjGetChild(temp_r30), JOBJ_HIDDEN);
    }
    HSD_JObjReqAnimAll(temp_r30, (f32) o->x48);
    HSD_JObjAnimAll(temp_r30);
}

static inline void mnInfoBonus_inline_SetGObjFlag(HSD_GObjProc* gobjproc)
{
    gobjproc->flags_3 = HSD_GObj_804D783C;
}

static inline void
mnInfoBonus_80252F8C_inline0(struct mnInfoBonus_804A09B0_t* o)
{
    HSD_GObj* gobj;
    HSD_JObj* jobj;
    StaticModelDesc* model_desc;

    model_desc = &o->x50;
    gobj = GObj_Create(6, 7, 0x80);
    o->x4C = gobj;
    jobj = HSD_JObjLoadJoint(model_desc->joint);

    HSD_GObjObject_80390A70(gobj, HSD_GObj_JObjKind, jobj);
    GObj_SetupGXLink(gobj, HSD_GObj_JObjCallback, 4, 0x80);
    HSD_JObjAddAnimAll(jobj, model_desc->animjoint, model_desc->matanim_joint,
                       model_desc->shapeanim_joint);
    HSD_JObjReqAnimAll(jobj, 0.F);
    HSD_JObjAnimAll(jobj);

    HSD_JObjSetFlags(HSD_JObjGetNext(HSD_JObjGetChild(jobj)), JOBJ_HIDDEN);
    HSD_JObjSetFlags(HSD_JObjGetChild(jobj), JOBJ_HIDDEN);
    mnInfoBonus_inline_SetGObjFlag(HSD_GObj_SetupProc(gobj, fn_80252E4C, 0));
}

void mnInfoBonus_80252F8C(void)
{
    struct mnInfoBonus_804A09B0_t* o = &mnInfoBonus_804A09B0;
    HSD_Archive* archive;
    u8 pad0[0x8];

    mn_804D6BC8.cooldown = 5;
    mn_804A04F0.prev_menu = mn_804A04F0.cur_menu;
    mn_804A04F0.cur_menu = 0x1F;
    mn_804A04F0.hovered_selection = 0;
    memzero(o, sizeof(*o));

    o->x44 = 8;
    *mnInfoBonus_804D6C80 = 0;
    archive = mn_804D6BB8;
    lbArchive_LoadSections(
        archive, (void**) &o->x50.joint, "MenMainConBo_Top_joint",
        &o->x50.animjoint, "MenMainConBo_Top_animjoint", &o->x50.matanim_joint,
        "MenMainConBo_Top_matanim_joint", &o->x50.shapeanim_joint,
        "MenMainConBo_Top_shapeanim_joint", 0);
    mnInfoBonus_inline_SetGObjFlag(
        HSD_GObj_SetupProc(GObj_Create(0U, 1U, 0x80U), fn_80252C50, 0U));

    mnInfoBonus_80252F8C_inline0(o);

    textSetup(o);
}
