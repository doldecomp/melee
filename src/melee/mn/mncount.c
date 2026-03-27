#include "placeholder.h"

#include <baselib/gobj.h>
#include <sysdolphin/baselib/debug.h>
#include <sysdolphin/baselib/gobj.h>
#include <sysdolphin/baselib/gobjgxlink.h>
#include <sysdolphin/baselib/gobjobject.h>
#include <sysdolphin/baselib/gobjplink.h>
#include <sysdolphin/baselib/gobjproc.h>
#include <sysdolphin/baselib/gobjuserdata.h>
#include <sysdolphin/baselib/jobj.h>
#include <sysdolphin/baselib/memory.h>
#include <sysdolphin/baselib/sislib.h>
#include <melee/gm/gm_1601.h>
#include <melee/gm/gmmain_lib.h>
#include <melee/gm/types.h>
#include <melee/if/textlib.h>
#include <melee/lb/lb_00F9.h>
#include <melee/lb/lbarchive.h>
#include <melee/lb/lbaudio_ax.h>
#include <melee/mn/inlines.h>
#include <melee/mn/mncount.h>
#include <melee/mn/mndiagram.h>
#include <melee/mn/mnmain.h>
#include <melee/mn/mnname.h>
#include <melee/mn/types.h>
#include <melee/sc/types.h>

// DATA / MELEE RECORDS / MISC RECORDS
#define NUM_STAGES 29
#define NUM_CHARACTERS 25
#define MAX_SCROLL 20

static AnimLoopSettings mnCount_803EFAA0 = { 0.0f, 199.0f, 0.0f };
static StaticModelDesc model_desc;
static HSD_GObj* menu_gobj;
static HSD_JObj* menu_jobj;
static u16 mnCount_sis_idx[30] = {
    0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF, 0xD0, 0xD1, 0xD2,
    0xD3, 0xD4, 0xD5, 0xD6, 0xD7, 0xD8, 0xD9, 0xDA, 0xDB, 0xDC,
    0xDD, 0xDE, 0xDF, 0xE0, 0xE1, 0xE2, 0xE3, 0xE4, 0xE5, 0xE6,
};
extern GXColor mn_804D4B64;

static inline bool inline_is_row_time(int row)
{
    switch (row) {
    case POWER_TIME:
    case PLAY_TIME:
    case SINGLEPLAYER_TIME:
    case VS_PLAY_TIME:
    case COMBINED_VS_PLAY_TIME:
        return true;
    default:
        return false;
    }
}

static inline bool inline_is_row_char(int row)
{
    switch (row) {
    case LONGEST_TIME:
    case SECOND_LONGEST_TIME:
    case SHORTEST_TIME:
    case SMASH_CHAMP:
    case SMASH_SAP:
    case SLUG_MEISTER:
    case PUNCHING_BAG:
    case KO_KINGPIN:
    case NO_DEFENSE_NELLY:
    case DISASTER_MASTER:
        return true;
    default:
        return false;
    }
}

static inline void inline_update_entries(HSD_GObj* gobj)
{
    MnCountData* userdata = GET_MNCOUNT(gobj);
    int i;
    for (i = 0; i < MNCOUNT_VISIBLE_ROWS; i++) {
        mnCount_CreateRow(gobj, i, userdata->scroll_pos + i);
    }
}

static inline void inline_free_text(HSD_GObj* gobj)
{
    MnCountData* userdata = GET_MNCOUNT(gobj);
    int i;

    for (i = 0; i < MNCOUNT_VISIBLE_ROWS; i++) {
        if (userdata->labels[i] != NULL) {
            HSD_SisLib_803A5CC4(userdata->labels[i]);
            userdata->labels[i] = NULL;
        }
        if (userdata->values[i] != NULL) {
            HSD_SisLib_803A5CC4(userdata->values[i]);
            userdata->values[i] = NULL;
        }
    }

    HSD_SisLib_803A5CC4(userdata->title);
}

static inline void mnCount_8025186C_inline(HSD_GObj* gobj)
{
    MnCountData* userdata = GET_MNCOUNT(gobj);
    HSD_Text* text;
    if (userdata->title != NULL) {
        HSD_SisLib_803A5CC4(userdata->title);
    }
    text =
        HSD_SisLib_803A5ACC(0, 1, -9.5f, 9.1f, 17.0f, 364.68332f, 38.38772f);
    userdata->title = text;
    text->font_size.x = 0.0521f;
    text->font_size.y = 0.0521f;
    HSD_SisLib_803A6368(text, 166);
}

static inline bool mnCount_8025035C_inline(void)
{
    s32 i;
    for (i = 0; i < 25; i++) {
        if (GetPersistentFighterData(i)->play_time != 0) {
            return false;
        }
    }
    return true;
}

u32 mnCount_GetMatchTime(s32 arg0)
{
    return GetPersistentFighterData(arg0)->play_time;
}

u32 mnCount_GetKOKingpin(s32 arg0)
{
    return mnDiagram_GetFighterTotalKOs(arg0);
}

u32 mnCount_GetNoDefenseNelly(s32 arg0)
{
    return mnDiagram_GetFighterTotalFalls(arg0);
}

u32 mnCount_GetDisasterMaster(s32 arg0)
{
    return GetPersistentFighterData(arg0)->sd_count;
}

int mnCount_8025035C(s32 skip_count, u32 (*get_val_func)(s32))
{
    PAD_STACK(4);
    {
        int i;
        int j;
        int best_idx;
        CountEntry sp18[25];
        CountEntry temp;
        ssize_t const arr_size = ARRAY_SIZE(sp18);

        if (mnCount_8025035C_inline()) {
            return arr_size;
        }

        for (i = 0; i < arr_size; i++) {
            sp18[i].id = i;
            sp18[i].val = get_val_func(i);
        }

        for (i = 0; i < arr_size; i++) {
            best_idx = i;

            for (j = i + 1; j < arr_size; j++) {
                if (sp18[best_idx].val < sp18[j].val) {
                    best_idx = j;
                }
            }

            if (best_idx != i) {
                temp = sp18[best_idx];
                for (j = best_idx; j > i; j--) {
                    sp18[j] = sp18[j - 1];
                }
                sp18[i] = temp;
            }
        }

        for (i = 0; i < arr_size; i++) {
            if (gm_80164840(gm_8016400C(sp18[i].id)) == 0) {
                continue;
            }

            if (skip_count != 0) {
                skip_count--;
                j = i + 1;
                while (j < arr_size) {
                    if (gm_80164840(gm_8016400C(sp18[j].id)) != 0 &&
                        get_val_func(sp18[i].id) == get_val_func(sp18[j].id))
                    {
                        i++;
                        if (skip_count != 0) {
                            skip_count--;
                        } else {
                            return arr_size;
                        }
                    }
                    j++;
                }
            } else {
                for (j = i + 1; j < arr_size; j++) {
                    if (gm_80164840(gm_8016400C(sp18[j].id)) == 0) {
                        continue;
                    }

                    if (get_val_func(sp18[i].id) == get_val_func(sp18[j].id)) {
                        return arr_size;
                    }
                }
                return sp18[i].id;
            }
        }

        return arr_size;
    }
}

u32 mnCount_GetSmashChamp(s32 arg0)
{
    return GetPersistentFighterData(arg0)->victories;
}

u32 mnCount_GetSmashSap(s32 arg0)
{
    return GetPersistentFighterData(arg0)->losses;
}

u32 mnCount_GetSlugMeister(s32 arg0)
{
    return GetPersistentFighterData(arg0)->damage_dealt;
}

u32 mnCount_GetPunchingBag(s32 arg0)
{
    return GetPersistentFighterData(arg0)->damage_taken;
}

#define GET_KOS(i) mnCount_GetKOKingpin(entries[i].id)
#define GET_FALLS(i) mnCount_GetNoDefenseNelly(entries[i].id)
s32 mnCount_8025072C(CountEntry* entries, s32 start_idx, bool mode)
{
    int idx, best_idx;
    bool tie = false;
    best_idx = start_idx;
    for (idx = start_idx + 1; idx < NUM_CHARACTERS; idx++) {
        if (entries[start_idx].val == entries[idx].val) {
            if (mode) {
                if (GET_KOS(best_idx) > GET_KOS(idx)) {
                    best_idx = idx;
                }
            } else {
                if (GET_KOS(best_idx) < GET_KOS(idx)) {
                    best_idx = idx;
                }
            }
            if (GET_KOS(best_idx) == GET_KOS(idx)) {
                tie = true;
                break;
            }
        }
    }
    if (!tie) {
        return entries[best_idx].id;
    }
    tie = false;
    for (idx = start_idx + 1; idx < NUM_CHARACTERS; idx++) {
        if (idx == best_idx) {
            continue;
        }
        if (entries[start_idx].val == entries[idx].val) {
            if (GET_KOS(start_idx) == GET_KOS(idx)) {
                if (GET_FALLS(best_idx) == GET_FALLS(idx)) {
                    tie = true;
                    break;
                }
                if (mode) {
                    if (GET_FALLS(best_idx) < GET_FALLS(idx)) {
                        best_idx = idx;
                    }
                } else {
                    if (GET_FALLS(best_idx) > GET_FALLS(idx)) {
                        best_idx = idx;
                    }
                }
            }
        }
    }
    if (tie) {
        return NUM_CHARACTERS;
    } else {
        return entries[best_idx].id;
    }
}
#undef GET_KOS
#undef GET_FALLS

static inline bool mnCount_8025092C_inline(void)
{
    int i;
    for (i = 0; i < NUM_CHARACTERS; i++) {
        if (mnCount_GetMatchTime(i) != 0) {
            return false;
        }
    }
    return true;
}

s32 mnCount_8025092C(s32 rank, u32 (*getVal)(s32), bool mode)
{
    CountEntry entries[NUM_CHARACTERS];
    int i, j, min;
    if (mnCount_8025092C_inline()) {
        return NUM_CHARACTERS;
    }
    for (i = 0; i < NUM_CHARACTERS; i++) {
        entries[i].id = i;
        entries[i].val = getVal(i);
    }
    for (i = 0; i < NUM_CHARACTERS; i++) {
        min = i;
        for (j = i + 1; j < NUM_CHARACTERS; j++) {
            if (entries[j].val < entries[min].val) {
                min = j;
            }
        }
        if (min != i) {
            CountEntry tmp = entries[min];
            for (j = min; j > i; j--) {
                entries[j] = entries[j - 1];
            }
            entries[i] = tmp;
        }
    }
    for (i = 0; i < NUM_CHARACTERS; i++) {
        if (!gm_80164840(gm_8016400C(entries[i].id))) {
            continue;
        }
        if (rank != 0) {
            rank--;
            for (j = i + 1; j < NUM_CHARACTERS; j++) {
                if (!gm_80164840(gm_8016400C(entries[j].id))) {
                    continue;
                }
                if (getVal(entries[i].id) == getVal(entries[j].id)) {
                    i++;
                    if (rank != 0) {
                        rank--;
                    } else {
                        return NUM_CHARACTERS;
                    }
                }
            }
        } else {
            for (j = i + 1; j < NUM_CHARACTERS; j++) {
                if (!gm_80164840(gm_8016400C(entries[j].id))) {
                    continue;
                }
                if (getVal(entries[i].id) == getVal(entries[j].id)) {
                    return mnCount_8025072C(entries, i, mode);
                }
            }
            return entries[i].id;
        }
    }
    return NUM_CHARACTERS;
}

int mnCount_GetRowValue_Character(mnCount_row row)
{
    int c;
    int i;
    switch (row) {
    case LONGEST_TIME:
        return mnCount_8025035C(0, mnCount_GetMatchTime);
    case SECOND_LONGEST_TIME:
        return mnCount_8025035C(1, mnCount_GetMatchTime);
    case SHORTEST_TIME:
        c = 0;
        for (i = 0; i < NUM_CHARACTERS; i++) {
            if (gm_80164840(gm_8016400C(i))) {
                c += 1;
            }
        }
        if (c < 3) {
            return NUM_CHARACTERS;
        }
        return mnCount_8025035C(c - 1, mnCount_GetMatchTime);
    case SMASH_CHAMP:
        return mnCount_8025092C(0, mnCount_GetSmashChamp, 0);
    case SMASH_SAP:
        return mnCount_8025092C(0, mnCount_GetSmashSap, 1);
    case SLUG_MEISTER:
        return mnCount_8025092C(0, mnCount_GetSlugMeister, 0);
    case PUNCHING_BAG:
        return mnCount_8025092C(0, mnCount_GetPunchingBag, 1);
    case KO_KINGPIN:
        return mnCount_8025035C(0, mnCount_GetKOKingpin);
    case NO_DEFENSE_NELLY:
        return mnCount_8025035C(0, mnCount_GetNoDefenseNelly);
    case DISASTER_MASTER:
        return mnCount_8025035C(0, mnCount_GetDisasterMaster);
    default:
        return NUM_CHARACTERS;
    }
}

unsigned int mnCount_GetRowValue_Number(int row)
{
    unsigned int ret;
    switch (row) {
    case POWER_COUNT:
        ret = *(unsigned int*) gmMainLib_GetPowerCount();
        break;
    case POWER_TIME:
        ret = *gm_GetPowerTime();
        break;
    case PLAY_TIME:
        ret = gm_GetPlayTime();
        break;
    case SINGLEPLAYER_TIME:
        ret = *(unsigned int*) gmMainLib_GetSingleplayerTime();
        break;
    case VS_PLAY_TIME:
        ret = *(unsigned int*) gmMainLib_GetVsPlayTime();
        break;
    case COMBINED_VS_PLAY_TIME:
        ret = *(unsigned int*) gmMainLib_GetCombinedVSPlayTime();
        break;
    case VS_PLAY_MATCH_TOTAL:
        ret = gm_GetVsPlayMatchTotal();
        break;
    case TIME_MATCH_TOTAL:
        ret = *(unsigned int*) gmMainLib_GetTimeMatchTotal();
        break;
    case STOCK_MATCH_TOTAL:
        ret = *(unsigned int*) gmMainLib_GetStockMatchTotal();
        break;
    case COIN_MATCH_TOTAL:
        ret = *(unsigned int*) gmMainLib_GetCoinMatchTotal();
        break;
    case BONUS_MATCH_TOTAL:
        ret = *(unsigned int*) gmMainLib_GetBonusMatchTotal();
        break;
    case VS_PLAY_CONTESTANTS:
        ret = *(unsigned int*) gmMainLib_GetVsPlayContestants();
        break;
    case MATCH_RESET_COUNTER:
        ret = *(unsigned int*) gmMainLib_GetMatchResetCounter();
        break;
    case TOTAL_DAMAGE:
        ret = *(unsigned int*) gmMainLib_GetTotalDamage();
        break;
    case KO_TOTAL:
        ret = *gmMainLib_GetKOTotal();
        break;
    case SELFDESTRUCT_TOTAL:
        ret = *(unsigned int*) gmMainLib_GetSelfDestructTotal();
        break;
    case AVAILABLE_CHARACTERS: {
        int i, c;
        c = 0;
        for (i = 0; i < NUM_CHARACTERS; i++) {
            if (gm_80164840(gm_8016400C(i))) {
                c++;
            }
        }
        ret = c;
    } break;
    case AVAILABLE_MAPS: {
        int i, c;
        c = 0;
        for (i = 0; i < NUM_STAGES; i++) {
            if (gm_80164430(gm_801641CC(i))) {
                c++;
            }
        }
        ret = c;
    } break;
    case TROPHY_TOTAL:
        ret = un_GetTrophyTotal();
        break;
    case NAME_TOTAL:
        ret = GetNameCount();
        break;
    default:
        if (inline_is_row_time(row)) {
            ret = 359940; // if in seconds, 99h 59m
        } else {
            ret = 9999;
        }
        break;
    }

    if (inline_is_row_time(row)) {
        if (ret > 3599999940u) {
            ret = 3599999940u; // if in seconds, 999999h 59m
        }
    } else if (ret > 999999999) {
        ret = 999999999;
    }
    return ret;
}

void mnCount_CreateRow(HSD_GObj* gobj, int visible_row, mnCount_row data_row)
{
    MnCountData* userdata = GET_MNCOUNT(gobj);
    HSD_Text* text;
    unsigned int row_value;
    int row_value_2;
    float y;
    char buf1[8];
    char buf2[8];
    static GXColor text_color = { 0xAA, 0xAA, 0xAA, 0xFF };
    if (userdata->labels[visible_row] != NULL) {
        HSD_SisLib_803A5CC4(userdata->labels[visible_row]);
        userdata->labels[visible_row] = NULL;
    }
    y = (1.4f * visible_row) + -6.4f;
    text = HSD_SisLib_803A5ACC(0, 1, -13.0f, y, 17.0f, 500.0f, 38.38772f);
    userdata->labels[visible_row] = text;
    text->font_size.x = 0.03f;
    text->font_size.y = 0.03f;
    text->text_color = text_color;
    HSD_SisLib_803A6368(text, mnCount_sis_idx[data_row]);
    if (userdata->values[visible_row] != NULL) {
        HSD_SisLib_803A5CC4(userdata->values[visible_row]);
        userdata->values[visible_row] = NULL;
    }
    text = HSD_SisLib_803A6754(0, 1);
    userdata->values[visible_row] = text;
    text->pos_x = 13.0f;
    text->pos_y = y;
    text->pos_z = 17.0f;
    text->text_color = mn_804D4B64;
    text->default_alignment = 2;
    if (inline_is_row_time(data_row)) {
        text->font_size.x = 0.03f;
        text->font_size.y = 0.03f;
        row_value = mnCount_GetRowValue_Number(data_row);
        mn_8022EA78(buf1, 2, row_value / 60 / 60);
        mn_8022EA78(buf2, 2, row_value / 60 % 60);
        HSD_SisLib_803A6B98(text, 0.0f, 0.0f, "%u:%s", row_value / 60 / 60,
                            buf2);
    } else if (inline_is_row_char(data_row)) {
        text->font_size.x = 0.03f;
        text->font_size.y = 0.03f;
        row_value_2 = mnCount_GetRowValue_Character(data_row);
        if (row_value_2 == NUM_CHARACTERS) {
            HSD_SisLib_803A6B98(text, 0.0f, 0.0f, "－");
        } else {
            gm_80160B40(text, gm_8016400C(row_value_2), 0);
        }
    } else {
        text->font_size.x = 0.03f;
        text->font_size.y = 0.03f;
        HSD_SisLib_803A6B98(text, 0.0f, 0.0f, "%u",
                            mnCount_GetRowValue_Number(data_row));
    }
}

void mnCount_HandleUserInput(HSD_GObj* gobj)
{
    MnCountData* userdata = GET_MNCOUNT(menu_gobj);
    long long x;
    if (mn_804D6BC8.cooldown != 0) {
        Menu_DecrementAnimTimer();
    } else {
        x = mn_804A04F0.buttons = mn_80229624(4);
        if (x & MenuInput_Back) {
            sfxBack();
            mn_804A04F0.entering_menu = 0;
            mn_80229894(MENU_KIND_RECORDS, 2, 3);
        } else if (x & MenuInput_Up) {
            if (userdata->scroll_pos != 0) {
                userdata->scroll_pos -= 1;
                sfxMove();
                inline_update_entries(menu_gobj);
            }
        } else if (x & MenuInput_Down) {
            if (userdata->scroll_pos < MAX_SCROLL) {
                sfxMove();
                userdata->scroll_pos += 1;
                inline_update_entries(menu_gobj);
            }
        }
    }
}

void mnCount_UpdateArrowIndicators(HSD_GObj* gobj)
{
    MnCountData* userdata = GET_MNCOUNT(gobj);
    HSD_JObj* jobj = gobj->hsd_obj; // GET_JOBJ breaks this
    HSD_JObj* child;

    // up arrow
    lb_80011E24(jobj, &child, 2, -1);
    if (userdata->scroll_pos != 0) {
        HSD_JObjClearFlagsAll(child, JOBJ_HIDDEN);
    } else {
        HSD_JObjSetFlagsAll(child, JOBJ_HIDDEN);
    }

    // down arrow
    lb_80011E24(jobj, &child, 1, -1);
    if (userdata->scroll_pos < MAX_SCROLL) {
        HSD_JObjClearFlagsAll(child, JOBJ_HIDDEN);
    } else {
        HSD_JObjSetFlagsAll(child, JOBJ_HIDDEN);
    }

    mn_8022ED6C(jobj, &mnCount_803EFAA0);
}

static void mnCount_UpdateArrowIndicators_noinline(HSD_GObj* gobj)
{
    mnCount_UpdateArrowIndicators(gobj);
}

void fn_802514B8(HSD_GObj* gobj)
{
    HSD_GObjPLink_80390228(gobj);
}

void fn_802514D8(HSD_GObj* gobj)
{
    MnCountData* userdata = GET_MNCOUNT(gobj);
    HSD_GObjProc* proc;
    if (mn_804A04F0.cur_menu != MENU_KIND_RECORDS_MISC) {
        HSD_GObjProc_8038FE24(HSD_GObj_804D7838);
        proc = HSD_GObj_SetupProc(gobj, fn_802514B8, 0);
        proc->flags_3 = HSD_GObj_804D783C;
        {
            // inline_free_text

            MnCountData* userdata2 = GET_MNCOUNT(gobj);
            MnCountData* userdata3 = userdata2;
            int i;

            for (i = 0; i < MNCOUNT_VISIBLE_ROWS; i++) {
                if (userdata2->labels[i] != NULL) {
                    HSD_SisLib_803A5CC4(userdata3->labels[i]);
                    userdata2->labels[i] = NULL;
                }
                if (userdata2->values[i] != NULL) {
                    HSD_SisLib_803A5CC4(userdata3->values[i]);
                    userdata2->values[i] = NULL;
                }
            }

            HSD_SisLib_803A5CC4(userdata->title);
        }
    } else {
        // mnCount_UpdateArrowIndicators

        HSD_JObj* jobj = gobj->hsd_obj;
        HSD_JObj* child;

        // up arrow
        lb_80011E24(jobj, &child, 2, -1);
        if (userdata->scroll_pos != 0) {
            HSD_JObjClearFlagsAll(child, JOBJ_HIDDEN);
        } else {
            HSD_JObjSetFlagsAll(child, JOBJ_HIDDEN);
        }

        // down arrow
        lb_80011E24(jobj, &child, 1, -1);
        if (userdata->scroll_pos < MAX_SCROLL) {
            HSD_JObjClearFlagsAll(child, JOBJ_HIDDEN);
        } else {
            HSD_JObjSetFlagsAll(child, JOBJ_HIDDEN);
        }

        mn_8022ED6C(jobj, &mnCount_803EFAA0);
    }
}

void fn_80251640(HSD_GObj* gobj)
{
    MnCountData* userdata = GET_MNCOUNT(gobj);
    HSD_GObjProc* proc;
    int i;
    HSD_JObj* jobj;
    StaticModelDesc* md;

    if (mn_804A04F0.cur_menu != MENU_KIND_RECORDS_MISC) {
        HSD_GObjProc_8038FE24(HSD_GObj_804D7838);
        proc = HSD_GObj_SetupProc(gobj, fn_802514B8, 0);
        proc->flags_3 = HSD_GObj_804D783C;
        {
            // inline_free_text

            MnCountData* userdata2 = GET_MNCOUNT(gobj);
            MnCountData* userdata3 = userdata2;
            int i;

            for (i = 0; i < MNCOUNT_VISIBLE_ROWS; i++) {
                if (userdata2->labels[i] != NULL) {
                    HSD_SisLib_803A5CC4(userdata3->labels[i]);
                    userdata2->labels[i] = NULL;
                }
                if (userdata2->values[i] != NULL) {
                    HSD_SisLib_803A5CC4(userdata3->values[i]);
                    userdata2->values[i] = NULL;
                }
            }

            HSD_SisLib_803A5CC4(userdata->title);
        }
        return;
    }

    if (userdata->expand_anim_duration != 0) {
        userdata->expand_anim_duration--;
        return;
    }

    for (i = 0; i < MNCOUNT_VISIBLE_ROWS; i++) {
        mnCount_CreateRow(gobj, i, userdata->scroll_pos + i);
    }

    md = &model_desc;
    jobj = HSD_JObjLoadJoint(md->joint);
    HSD_GObjObject_80390A70(gobj, HSD_GObj_804D7849, jobj);
    GObj_SetupGXLink(gobj, HSD_GObj_JObjCallback, 4, 0x80);
    HSD_JObjAddAnimAll(jobj, md->animjoint, md->matanim_joint,
                       md->shapeanim_joint);
    HSD_JObjReqAnimAll(jobj, 0.0f);
    mnCount_UpdateArrowIndicators_noinline(gobj);
    HSD_GObjProc_8038FE24(HSD_GObj_804D7838);
    proc = HSD_GObj_SetupProc(gobj, fn_802514D8, 0);
    proc->flags_3 = HSD_GObj_804D783C;
}

void mnCount_InitUserData(MnCountData* userdata)
{
    int i;
    userdata->scroll_pos = 0;
    userdata->expand_anim_duration = 10;
    for (i = 0; i < MNCOUNT_VISIBLE_ROWS; i++) {
        userdata->labels[i] = NULL;
        userdata->values[i] = NULL;
    }
}

static void mnCount_InitUserData_noinline(MnCountData* userdata)
{
    mnCount_InitUserData(userdata);
}

void mnCount_Create(void)
{
    HSD_GObj* gobj;
    MnCountData* userdata;
    HSD_GObjProc* proc;

    mn_804D6BC8.cooldown = 5;
    mn_804A04F0.prev_menu = mn_804A04F0.cur_menu;
    mn_804A04F0.cur_menu = MENU_KIND_RECORDS_MISC;
    mn_804A04F0.hovered_selection = 0;

    lbArchive_LoadSections(
        mn_804D6BB8, (void**) &model_desc.joint, "MenMainConCo_Top_joint",
        &model_desc.animjoint, "MenMainConCo_Top_animjoint",
        &model_desc.matanim_joint, "MenMainConCo_Top_matanim_joint",
        &model_desc.shapeanim_joint, "MenMainConCo_Top_shapeanim_joint", 0);

    gobj = GObj_Create(6, 7, 0x80);
    menu_gobj = gobj;

    userdata = HSD_MemAlloc(sizeof(MnCountData));
    HSD_ASSERTREPORT(0x512, userdata, "Can't get user_data.\n");
    mnCount_InitUserData_noinline(userdata);
    GObj_InitUserData(gobj, 0, HSD_Free, userdata);

    proc = HSD_GObj_SetupProc(gobj, fn_80251640, 0);
    proc->flags_3 = HSD_GObj_804D783C;
    mnCount_8025186C_inline(gobj);

    gobj = GObj_Create(0, 1, 0x80);
    proc = HSD_GObj_SetupProc(gobj, mnCount_HandleUserInput, 0);
    proc->flags_3 = HSD_GObj_804D783C;
}
