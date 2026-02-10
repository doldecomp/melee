#include "mndiagram2.h"

#include "mndiagram2.static.h"

#include "baselib/forward.h"

#include <stdbool.h>
#include <baselib/gobj.h>
#include <baselib/gobjgxlink.h>
#include <baselib/gobjobject.h>
#include <baselib/gobjplink.h>
#include <baselib/gobjproc.h>
#include <baselib/gobjuserdata.h>
#include <baselib/jobj.h>
#include <baselib/memory.h>
#include <baselib/sislib.h>
#include <melee/gm/gm_1601.h>
#include <melee/gm/gmmain_lib.h>
#include <melee/lb/lb_00B0.h>
#include <melee/lb/lb_00F9.h>
#include <melee/lb/lbaudio_ax.h>
#include <melee/mn/mndiagram.h>
#include <melee/mn/mndiagram3.h>
#include <melee/mn/mnmain.h>
#include <melee/mn/mnname.h>

/* GetPersistentNameData and GetPersistentFighterData are in gm/gmmain_lib.h */

/* Wrapper macros for index functions */
#define mnDiagram_GetNameByIndex_s(x) ((int) mnDiagram_GetNameByIndex(x))
#define mnDiagram_GetFighterByIndex_s(x) ((int) mnDiagram_GetFighterByIndex(x))
#define mnDiagram_GetFighterByIndex_BBC(x) mnDiagram_GetFighterByIndex_s(x)

/// @brief Gets entity index based on mode (name or fighter).
static inline u8 mnDiagram_GetEntityByIndex(u8 is_name_mode, u8 idx)
{
    if (is_name_mode != 0) {
        return mnDiagram_GetNameByIndex(idx);
    }
    return mnDiagram_GetFighterByIndex(idx);
}

/* Union for 64-bit sorting operations */
typedef union {
    struct {
        u8 name;
        char pad1[7];
        s32 x8;
        s32 xC;
    };
    struct {
        f64 d0;
        f64 d8;
    };
    struct {
        char pad2[8];
        u64 value;
    };
} mnDiagram2_SortEntry;

/// Container struct with JObj at offset 0x10.
/// @@todo Identify the actual type - may be archive-related.
typedef struct {
    /* 0x00 */ char x0[0x10];
    /* 0x10 */ HSD_JObj* jobj;
} JObjContainer;

/// User data for detail view GObj (used in mnDiagram2_ClearDetailView).
typedef struct {
    /* 0x00 */ char x0[0x20];
    /* 0x20 */ JObjContainer* jobj_container; ///< Container for removable JObj
    /* 0x24 */ char x24[0x34];
    /* 0x58 */ HSD_Text* title_text; ///< Title text object
    /* 0x5C */ HSD_Text* x5C;
    /* 0x60 */ HSD_Text* detail_texts[5]; ///< Detail value text objects
} Diagram2DetailView;

/* Diagram2 struct is defined in mn/types.h */

/* mnDiagram_ArchiveData, mnDiagram2_804D6C18, mnDiagram_804A0834 defined in
 * mndiagram2.static.h */

/// @brief Checks if stat type uses time format (H:MM:SS).
/// @param stat_type The stat type index (VSRecordsStatType)
/// @return true if stat should display as time
/// @details Only VSSTAT_PLAY_TIME (0x0B) uses time display format.
bool mnDiagram2_IsTimeStat(u8 stat_type)
{
    switch (stat_type) {
    case VSSTAT_PLAY_TIME:
        return true;
    default:
        return false;
    }
}

/// @brief Checks if stat type is a distance stat (shown in feet).
/// @param stat_type The stat type index (VSRecordsStatType)
/// @return true if stat shows distance in ft.
/// @details Distance stats: Walk, Run, Fall, Peak Height (0x0E-0x11).
bool mnDiagram2_IsDistanceStat(u8 stat_type)
{
    switch (stat_type) {
    case VSSTAT_WALK_DISTANCE:
    case VSSTAT_RUN_DISTANCE:
    case VSSTAT_FALL_DISTANCE:
    case VSSTAT_PEAK_HEIGHT:
        return true;
    default:
        return false;
    }
}

/// @brief Checks if stat type is a percentage stat.
/// @param stat_type The stat type index (VSRecordsStatType)
/// @return true if stat displays with decimal percentage
/// @details Percentage stats: Hit %, Play %, Avg Players (0x03, 0x0C, 0x0D).
bool mnDiagram2_IsPercentageStat(u8 stat_type)
{
    switch (stat_type) {
    case VSSTAT_HIT_PERCENTAGE:
    case VSSTAT_PLAY_PERCENTAGE:
    case VSSTAT_AVG_PLAYERS:
        return true;
    default:
        return false;
    }
}

/// @brief Checks if stat type displays as icon only (no numeric value).
/// @param stat_type The stat type index (VSRecordsStatType)
/// @return true if stat displays character icons only
/// @details Icon-only stats: Most/2nd/Least played fighter (0x15-0x17).
///          These are only shown in Name mode and display a character icon.
bool mnDiagram2_IsIconOnlyStat(u8 stat_type)
{
    switch (stat_type) {
    case VSSTAT_MOST_PLAYED:
    case VSSTAT_SECOND_PLAYED:
    case VSSTAT_LEAST_PLAYED:
        return true;
    default:
        return false;
    }
}

/// @brief Clears all stat row text objects and icon JObjs.
/// @param gobj The diagram GObj
void mnDiagram2_ClearStatRows(HSD_GObj* gobj)
{
    Diagram2* ptr;
    Diagram2* data;
    int i;
    HSD_JObj* jobj;

    ptr = data = (Diagram2*) HSD_GObjGetUserData(gobj);

    for (i = 0; i < 10; i++) {
        if (data->row_labels[i] != NULL) {
            HSD_SisLib_803A5CC4(ptr->row_labels[i]);
            data->row_labels[i] = NULL;
        }
        if (data->row_values[i] != NULL) {
            HSD_SisLib_803A5CC4(ptr->row_values[i]);
            data->row_values[i] = NULL;
        }
        if (data->row_icons[i] != NULL) {
            HSD_SisLib_803A5CC4(ptr->row_icons[i]);
            data->row_icons[i] = NULL;
        }
    }

    jobj = HSD_JObjGetChild(data->icon_parent);
    if (jobj != NULL) {
        HSD_JObjRemoveAll(jobj);
    }
}

/// @brief Updates the header display with fighter/name icon and text.
/// @param gobj The diagram GObj
/// @param is_name_mode 0 = Fighter mode, 1 = Name mode
/// @param entity_idx Fighter or Name selection index
void mnDiagram2_UpdateHeader(HSD_GObj* gobj, u8 is_name_mode, u8 entity_idx)
{
    Vec3 sp18;
    int name;
    Diagram2* data;
    HSD_Text* text;
    void* tmp;
    HSD_JObj* jobj;
    PAD_STACK(8);

    data = gobj->user_data;
    name = mnDiagram_GetEntityByIndex(is_name_mode, entity_idx);

    if (is_name_mode == 0) {
        tmp = data->x18;
        if (tmp == NULL) {
            tmp = NULL;
        } else {
            tmp = ((HSD_JObj*) tmp)->child;
        }
        jobj = tmp;
        if (jobj != NULL) {
            HSD_JObjRemoveAll(jobj);
        }
        HSD_JObjAddChild(data->x18, mnDiagram_80242B38((u8) name, 0));
    }

    if (data->header_text != NULL) {
        HSD_SisLib_803A5CC4(data->header_text);
    }

    text = HSD_SisLib_803A6754(0, 1);
    data->header_text = text;

    if (is_name_mode != 0) {
        lb_8000B1CC(data->x24, (Vec3*) &mnDiagram2_803EEAD0, &sp18);
    } else {
        lb_8000B1CC(data->x1C, (Vec3*) &mnDiagram2_803EEAD0, &sp18);
    }

    {
        f32 font = mnDiagram2_804DBFC8;
        text->font_size.x = font;
        text->font_size.y = font;
    }
    text->text_color = mnDiagram2_804D4FB8;
    {
        f32 y = sp18.y;
        f32 z = sp18.z;
        text->pos_x = sp18.x;
        text->pos_y = -y;
        text->pos_z = z;
    }
    text->default_alignment = 1;

    if (is_name_mode != 0) {
        char* str = GetNameText(name);
        HSD_SisLib_803A6B98(text, mnDiagram2_804DBFCC, mnDiagram2_804DBFCC,
                            str);
    } else {
        gm_80160B40(text, gm_8016400C(name), 0);
    }
}

/// @brief Clears and repopulates stat rows based on current selection.
/// @details Reads is_name_mode to determine which entity index to use.
static inline void mnDiagram2_RefreshStatRows(void)
{
    Diagram2* data = mnDiagram2_804D6C18->user_data;
    u8 entity_idx;

    mnDiagram2_ClearStatRows(mnDiagram2_804D6C18);
    if (data->is_name_mode != 0) {
        entity_idx = data->selected_name_idx;
    } else {
        entity_idx = data->selected_fighter_idx;
    }
    mnDiagram2_PopulateStatRows(mnDiagram2_804D6C18, (u8) data->scroll_offset,
                                data->is_name_mode, entity_idx);
}

/// @brief Handles input for the VS Records character details page.
/// @param gobj The diagram GObj (unused, uses global mnDiagram2_804D6C18)
/// @details Input mapping:
///   - Up/Down: Scroll stat rows
///   - Left/Right: Change character/name selection
///   - B: Exit to main menu
///   - L/R shoulder: Cycle to prev/next VS Records page
///   - L/R triggers: Toggle Fighter/Name mode
void mnDiagram2_HandleInput(HSD_GObj* gobj)
{
    Diagram2* data;
    Diagram2* data2;
    int result;
    u8 x46;
    u8 x47;
    u8 x48;
    u8 var_r6;
    u8 var_r5;
    u8 var_r28;
    u8 new_val;

    data = mnDiagram2_804D6C18->user_data;
    result = mn_80229624(4);
    mn_804A04F0.buttons = result;
    var_r28 = 0;

    if (result & 0x20) {
        lbAudioAx_80024030(0);
        mn_804A04F0.entering_menu = 0;
        data2 = mnDiagram2_804D6C18->user_data;
        x46 = data2->selected_fighter_idx;
        gmMainLib_8015CC34()->x12 = x46;
        x47 = data2->selected_name_idx;
        gmMainLib_8015CC34()->x13 = x47;
        x48 = data2->is_name_mode;
        gmMainLib_8015CC34()->xD = x48;
        mn_80229894(0x1C, 0, 3);
        mnDiagram2_ClearStatRows(mnDiagram2_804D6C18);
        return;
    }

    if (result & 0xC0) {
        lbAudioAx_80024030(1);
        data2 = mnDiagram2_804D6C18->user_data;
        x46 = data2->selected_fighter_idx;
        gmMainLib_8015CC34()->x12 = x46;
        x47 = data2->selected_name_idx;
        gmMainLib_8015CC34()->x13 = x47;
        x48 = data2->is_name_mode;
        gmMainLib_8015CC34()->xD = x48;
        mnDiagram2_ClearStatRows(mnDiagram2_804D6C18);
        HSD_GObjPLink_80390228(gobj);
        if (result & 0x40) {
            mnDiagram_802437E8(0, 0);
            return;
        }
        mnDiagram3_8024714C(NULL);
        return;
    }

    if (result & 0xC00) {
        if (GetNameCount() == 0) {
            lbAudioAx_80024030(3);
            return;
        }
        lbAudioAx_80024030(1);
        if (data->is_name_mode == 0) {
            var_r28 = 1;
        }
        data->is_name_mode = var_r28;
        if (data->is_name_mode == 0 && (s32) (data->scroll_offset + 10) > 0x15)
        {
            data->scroll_offset = 0;
        }
        mnDiagram2_RefreshStatRows();
        if (data->is_name_mode != 0) {
            var_r5 = data->selected_name_idx;
        } else {
            var_r5 = data->selected_fighter_idx;
        }
        mnDiagram2_UpdateHeader(mnDiagram2_804D6C18, data->is_name_mode,
                                var_r5);
        x48 = data->is_name_mode;
        data2 = mnDiagram2_804D6C18->user_data;
        if (x48 != 0) {
            HSD_JObjSetFlagsAll(data2->fighter_mode_header, 0x10);
            HSD_JObjClearFlagsAll(data2->name_mode_header, 0x10);
        } else {
            HSD_JObjClearFlagsAll(data2->fighter_mode_header, 0x10);
            HSD_JObjSetFlagsAll(data2->name_mode_header, 0x10);
        }
        if (x48 != 0) {
            var_r5 = data2->selected_name_idx;
        } else {
            var_r5 = data2->selected_fighter_idx;
        }
        mnDiagram2_UpdateHeader(mnDiagram2_804D6C18, x48, var_r5);
        return;
    }

    if (data->is_name_mode != 0) {
        GetNameCount();
        if (result & 1) {
            if (data->scroll_offset != 0) {
                lbAudioAx_80024030(2);
                data->scroll_offset = data->scroll_offset - 1;
                mnDiagram2_RefreshStatRows();
            }
        } else if (result & 2) {
            if ((s32) (data->scroll_offset + 10) < 0x18) {
                lbAudioAx_80024030(2);
                data->scroll_offset = data->scroll_offset + 1;
                mnDiagram2_RefreshStatRows();
            }
        } else if (result & 4) {
            new_val = mnDiagram_GetPrevNameIndex(data->selected_name_idx);
            if ((s32) data->selected_name_idx != (s32) new_val) {
                lbAudioAx_80024030(2);
                data->selected_name_idx = new_val;
                mnDiagram2_RefreshStatRows();
                mnDiagram2_UpdateHeader(mnDiagram2_804D6C18,
                                        data->is_name_mode,
                                        data->selected_name_idx);
            }
        } else if (result & 8) {
            new_val = mnDiagram_GetNextNameIndex(data->selected_name_idx);
            if ((s32) data->selected_name_idx != (s32) new_val) {
                lbAudioAx_80024030(2);
                data->selected_name_idx = new_val;
                mnDiagram2_RefreshStatRows();
                mnDiagram2_UpdateHeader(mnDiagram2_804D6C18,
                                        data->is_name_mode,
                                        data->selected_name_idx);
            }
        }
    } else {
        mnDiagram_CountUnlockedFighters();
        if (result & 1) {
            if (data->scroll_offset != 0) {
                lbAudioAx_80024030(2);
                data->scroll_offset = data->scroll_offset - 1;
                mnDiagram2_RefreshStatRows();
            }
        } else if (result & 2) {
            if ((s32) (data->scroll_offset + 10) < 0x15) {
                lbAudioAx_80024030(2);
                data->scroll_offset = data->scroll_offset + 1;
                mnDiagram2_RefreshStatRows();
            }
        } else if (result & 4) {
            new_val =
                mnDiagram_GetPrevFighterIndex(data->selected_fighter_idx);
            if ((s32) data->selected_fighter_idx != (s32) new_val) {
                lbAudioAx_80024030(2);
                data->selected_fighter_idx = new_val;
                mnDiagram2_RefreshStatRows();
                mnDiagram2_UpdateHeader(mnDiagram2_804D6C18,
                                        data->is_name_mode,
                                        data->selected_fighter_idx);
            }
        } else if (result & 8) {
            new_val =
                mnDiagram_GetNextFighterIndex(data->selected_fighter_idx);
            if ((s32) data->selected_fighter_idx != (s32) new_val) {
                lbAudioAx_80024030(2);
                data->selected_fighter_idx = new_val;
                mnDiagram2_RefreshStatRows();
                mnDiagram2_UpdateHeader(mnDiagram2_804D6C18,
                                        data->is_name_mode,
                                        data->selected_fighter_idx);
            }
        }
    }
}

/// @brief Retrieves a stat value for a fighter or name entry.
/// @param is_name_mode 0 = Fighter mode, 1 = Name mode
/// @param stat_type Stat category (0x00-0x17), passed as HSD_GObj* due to ABI
/// @param entity_idx Fighter or Name index
/// @return The stat value for the given category and entity
int mnDiagram2_GetStatValue(int is_name_mode, u8 stat_type, u8 entity_idx)
{
    u8 typeVal;
    u8 idxVal;

    typeVal = stat_type;
    idxVal = entity_idx;

    switch (typeVal) {
    case VSSTAT_TOTAL_KOS:
        if ((u8) is_name_mode) {
            return mnDiagram_GetNameTotalKOs(idxVal);
        }
        return mnDiagram_GetFighterTotalKOs(idxVal);

    case VSSTAT_TOTAL_FALLS:
        if ((u8) is_name_mode) {
            return mnDiagram_GetNameTotalFalls(idxVal);
        }
        return mnDiagram_GetFighterTotalFalls(idxVal);

    case VSSTAT_SD_COUNT:
        if ((u8) is_name_mode) {
            return GetPersistentNameData(idxVal)->sd_count;
        }
        return GetPersistentFighterData(idxVal)->sd_count;

    case VSSTAT_HIT_PERCENTAGE:
        return mnDiagram_GetHitPercentage((u8) is_name_mode, idxVal);

    case VSSTAT_DAMAGE_DEALT:
        if ((u8) is_name_mode) {
            return GetPersistentNameData(idxVal)->damage_dealt;
        }
        return GetPersistentFighterData(idxVal)->damage_dealt;

    case VSSTAT_DAMAGE_TAKEN:
        if ((u8) is_name_mode) {
            return GetPersistentNameData(idxVal)->damage_taken;
        }
        return GetPersistentFighterData(idxVal)->damage_taken;

    case VSSTAT_DAMAGE_RECOVERED:
        if ((u8) is_name_mode) {
            return GetPersistentNameData(idxVal)->damage_recovered;
        }
        return GetPersistentFighterData(idxVal)->damage_recovered;

    case VSSTAT_PEAK_DAMAGE:
        if ((u8) is_name_mode) {
            return GetPersistentNameData(idxVal)->peak_damage;
        }
        return GetPersistentFighterData(idxVal)->peak_damage;

    case VSSTAT_MATCH_COUNT:
        if ((u8) is_name_mode) {
            return GetPersistentNameData(idxVal)->match_count;
        }
        return GetPersistentFighterData(idxVal)->match_count;

    case VSSTAT_VICTORIES:
        if ((u8) is_name_mode) {
            return GetPersistentNameData(idxVal)->victories;
        }
        return GetPersistentFighterData(idxVal)->victories;

    case VSSTAT_LOSSES:
        if ((u8) is_name_mode) {
            return GetPersistentNameData(idxVal)->losses;
        }
        return GetPersistentFighterData(idxVal)->losses;

    case VSSTAT_PLAY_TIME:
        if ((u8) is_name_mode) {
            return GetPersistentNameData(idxVal)->play_time;
        }
        return GetPersistentFighterData(idxVal)->play_time;

    case VSSTAT_PLAY_PERCENTAGE:
        return mnDiagram_GetPlayPercentage((u8) is_name_mode, idxVal);

    case VSSTAT_AVG_PLAYERS:
        return mnDiagram_GetAveragePlayerCount((u8) is_name_mode, idxVal);

    case VSSTAT_WALK_DISTANCE:
        if ((u8) is_name_mode) {
            return GetPersistentNameData(idxVal)->walk_distance;
        }
        return GetPersistentFighterData(idxVal)->walk_distance;

    case VSSTAT_RUN_DISTANCE:
        if ((u8) is_name_mode) {
            return GetPersistentNameData(idxVal)->run_distance;
        }
        return GetPersistentFighterData(idxVal)->run_distance;

    case VSSTAT_FALL_DISTANCE:
        if ((u8) is_name_mode) {
            return GetPersistentNameData(idxVal)->fall_distance;
        }
        return GetPersistentFighterData(idxVal)->fall_distance;

    case VSSTAT_PEAK_HEIGHT:
        if ((u8) is_name_mode) {
            return GetPersistentNameData(idxVal)->peak_height;
        }
        return GetPersistentFighterData(idxVal)->peak_height;

    case VSSTAT_COINS_COLLECTED:
        if ((u8) is_name_mode) {
            return GetPersistentNameData(idxVal)->coins_collected;
        }
        return GetPersistentFighterData(idxVal)->coins_collected;

    case VSSTAT_COINS_SWIPED:
        if ((u8) is_name_mode) {
            return GetPersistentNameData(idxVal)->coins_swiped;
        }
        return GetPersistentFighterData(idxVal)->coins_swiped;

    case VSSTAT_COINS_LOST:
        if ((u8) is_name_mode) {
            return GetPersistentNameData(idxVal)->coins_lost;
        }
        return GetPersistentFighterData(idxVal)->coins_lost;

    case VSSTAT_MOST_PLAYED:
        return mnDiagram_GetRankedFighterForName(
            0, idxVal, (void*) mnDiagram_GetNamePlayTimeByFighter);

    case VSSTAT_SECOND_PLAYED:
        return mnDiagram_GetRankedFighterForName(
            1, idxVal, (void*) mnDiagram_GetNamePlayTimeByFighter);

    case VSSTAT_LEAST_PLAYED:
        return mnDiagram_GetLeastPlayedFighter(idxVal);

    default:
        break;
    }
    return 0;
}

/// @brief Creates a single stat row entry in the VS Records display.
/// @param gobj The diagram GObj
/// @param is_name_mode 0 = Fighter mode, 1 = Name mode
/// @param stat_type Stat category index (0-23)
/// @param row_idx Row position (0-9, 10 visible rows)
/// @param entity_idx Fighter or Name index for stat lookup
void mnDiagram2_CreateStatRow(HSD_GObj* gobj, u8 is_name_mode, u8 stat_type,
                              u8 row_idx, u8 entity_idx)
{
    Vec3 sp20;
    u8 str[4];
    int pad[4];
    Diagram2* data;
    HSD_JObj* jobj2C;
    HSD_JObj* jobj30;
    char* base;
    u16* table;
    HSD_Text* text;
    f32 f31;
    f32 f30;

    data = gobj->user_data;
    base = (char*) &mnDiagram2_803EEAD0;

    jobj2C = data->row0_ref;
    if (jobj2C == NULL) {
        __assert(mnDiagram2_804D4FC0, 0x3EE, mnDiagram2_804D4FC8);
    }

    jobj30 = data->row1_ref;
    f31 = jobj2C->translate.y;
    if (jobj30 == NULL) {
        __assert(mnDiagram2_804D4FC0, 0x3EE, mnDiagram2_804D4FC8);
    }

    f30 = jobj30->translate.y - f31;

    lb_8000B1CC(data->row0_ref, (Vec3*) (base + 0xC), &sp20);

    {
        int r22 = (u8) row_idx;
        f32 temp_f31 = -f30 * (f32) r22;
        text = HSD_SisLib_803A5ACC(0, 1, sp20.x, -sp20.y + temp_f31, sp20.z,
                                   mnDiagram2_804DBFD0, mnDiagram2_804DBFD4);

        {
            int r29 = row_idx << 2;
            Diagram2* temp_r22 = (Diagram2*) ((u8*) data + r29);
            temp_r22->row_labels[0] = text;

            table = (u16*) (base + ((stat_type << 1) & 0x1FE));
            {
                int r23 = (u8) stat_type;
                HSD_SisLib_803A6368(text, table[0x18]);

                {
                    u16 iconId = table[0x30];
                    int r21 = iconId;
                    if (iconId != 0xFFFF) {
                        HSD_Text* text2;
                        int var_r3;
                        lb_8000B1CC(data->row0_ref, (Vec3*) (base + 0xC),
                                    &sp20);
                        text2 = HSD_SisLib_803A5ACC(
                            0, 1, mnDiagram2_804DBFD8 + sp20.x,
                            -sp20.y + temp_f31, sp20.z, mnDiagram2_804DBFDC,
                            mnDiagram2_804DBFDC);

                        temp_r22->row_icons[0] = text2;
                        text2->default_alignment = 1;
                        text2->text_color = mnDiagram2_804D4FB8;

                        if (r23 >= 0x12) {
                            var_r3 = 0;
                        } else if (r23 >= 0xE) {
                            var_r3 = 1;
                        } else {
                            var_r3 = 0;
                        }

                        if (var_r3 != 0) {
                            u32 stat_val = mnDiagram2_GetStatValue(
                                is_name_mode, stat_type, entity_idx);
                            if (mnDiagram_IsDistanceOverflow(stat_val)) {
                                HSD_SisLib_803A6368(text2, 0x7F);
                            } else {
                                HSD_SisLib_803A6368(text2, r21);
                            }
                        } else {
                            HSD_SisLib_803A6368(text2, r21);
                        }
                    }
                }

                {
                    int var_r0;
                    if (r23 >= 0x18) {
                        var_r0 = 0;
                    } else if (r23 >= 0x15) {
                        var_r0 = 1;
                    } else {
                        var_r0 = 0;
                    }

                    if (var_r0 != 0 &&
                        (u32) mnDiagram2_GetStatValue(is_name_mode, stat_type,
                                                      entity_idx) < 0x19)
                    {
                        HSD_JObj* jobj = mnDiagram_80242B38(
                            (u8) mnDiagram2_GetStatValue(
                                is_name_mode, stat_type, entity_idx),
                            0);
                        HSD_JObjSetTranslateX(jobj, *(f32*) (base + 0x24));
                        HSD_JObjSetTranslateY(jobj, (f30 * (f32) row_idx) +
                                                        *(f32*) (base + 0x28));
                        HSD_JObjSetTranslateZ(jobj, *(f32*) (base + 0x2C));

                        HSD_JObjAddChild(data->icon_parent, jobj);
                        return;
                    }
                }

                {
                    HSD_Text* text3 = HSD_SisLib_803A6754(0, 1);
                    temp_r22->row_values[0] = text3;
                    text3->font_size.x = mnDiagram2_804DBFE0;
                    text3->font_size.y = mnDiagram2_804DBFE4;
                    lb_8000B1CC(data->icon_parent, (Vec3*) (base + 0x18),
                                &sp20);
                    text3->pos_x = sp20.x;
                    text3->pos_y = -sp20.y + temp_f31;
                    text3->pos_z = sp20.z;
                    text3->text_color = mnDiagram2_804D4FB8;
                    text3->default_alignment = 2;

                    if (r23 == 0xB) {
                        int val = mnDiagram2_GetStatValue(
                            is_name_mode, stat_type, entity_idx);
                        if ((u32) val > 0x927BF) {
                            val = 0x927BF;
                        }
                        mnDiagram_FormatTime((char*) str, val);
                    } else {
                        int var_r0_3;
                        if (r23 >= 0x12) {
                            var_r0_3 = 0;
                        } else if (r23 >= 0xE) {
                            var_r0_3 = 1;
                        } else {
                            var_r0_3 = 0;
                        }

                        if (var_r0_3 != 0) {
                            u32 val = mnDiagram2_GetStatValue(
                                is_name_mode, stat_type, entity_idx);
                            val = mnDiagram_ConvertDistanceForDisplay(val);
                            if (val > 0x98967F) {
                                val = 0x98967F;
                            }
                            mnDiagram_IntToStr((char*) str, val);
                        } else {
                            int var_r0_4;
                            if (r23 >= 0xC) {
                                if (r23 < 0xE) {
                                    var_r0_4 = 1;
                                } else {
                                    var_r0_4 = 0;
                                }
                            } else if (r23 == 3) {
                                var_r0_4 = 1;
                            } else {
                                var_r0_4 = 0;
                            }

                            if (var_r0_4 != 0) {
                                int val = mnDiagram2_GetStatValue(
                                    is_name_mode, stat_type, entity_idx);
                                if ((u32) val > 0xF423F) {
                                    val = 0xF423F;
                                }
                                mnDiagram_FormatDecimalNumber((char*) str, val,
                                                              2);
                            } else {
                                int var_r0_5;
                                if (r23 >= 0x18) {
                                    var_r0_5 = 0;
                                } else if (r23 >= 0x15) {
                                    var_r0_5 = 1;
                                } else {
                                    var_r0_5 = 0;
                                }

                                if (var_r0_5 != 0) {
                                    str[0] = mnDiagram2_804D4FD0[0];
                                    str[1] = mnDiagram2_804D4FD0[1];
                                    str[2] = mnDiagram2_804D4FD0[2];
                                } else {
                                    int val = mnDiagram2_GetStatValue(
                                        is_name_mode, stat_type, entity_idx);
                                    if ((u32) val > 0x98967F) {
                                        val = 0x98967F;
                                    }
                                    mnDiagram_FormatDecimalNumber((char*) str,
                                                                  val, 0);
                                }
                            }
                        }
                    }

                    HSD_SisLib_803A6B98(text3, mnDiagram2_804DBFCC,
                                        mnDiagram2_804DBFCC, (char*) str);
                }
            }
        }
    }
}

/// @brief Populates all 10 visible stat rows in the diagram.
/// @param gobj The diagram GObj
/// @param scroll_offset Current scroll position (stat type offset)
/// @param is_name_mode 0 = Fighter mode, 1 = Name mode
/// @param entity_idx Fighter or Name selection index
void mnDiagram2_PopulateStatRows(HSD_GObj* gobj, u8 scroll_offset,
                                 u8 is_name_mode, u8 entity_idx)
{
    int limit;
    int idx;
    int i;
    u8 var_r28;

    if (is_name_mode != 0) {
        var_r28 = mnDiagram_GetNameByIndex(entity_idx);
    } else {
        var_r28 = mnDiagram_GetFighterByIndex(entity_idx);
    }

    if (is_name_mode != 0) {
        limit = 0x18;
    } else {
        limit = 0x15;
    }

    i = 0;
    idx = (u8) scroll_offset;
    do {
        int val;
        if (idx >= limit) {
            val = idx - limit;
        } else {
            val = idx;
        }
        mnDiagram2_CreateStatRow(gobj, is_name_mode, val, i, var_r28);
        i++;
        idx++;
    } while (i < 10);
}

/* Local struct for mnDiagram2_OnAnimComplete */
typedef struct {
    /* 0x00 */ char pad0[0x0C];
    /* 0x0C */ HSD_JObj* jobj;
} mnDiagram2_AnimCompleteData;

/// @brief Animation completion callback - destroys GObj when animation ends.
void mnDiagram2_OnAnimComplete(HSD_GObj* gobj)
{
    mnDiagram2_AnimCompleteData* data;
    HSD_JObj* jobj;
    AnimLoopSettings* table;
    int pad;

    data = gobj->user_data;
    jobj = data->jobj;
    table = &mnDiagram2_803EEB60;
    pad = 0;
    if (mn_8022ED6C(jobj, table) >= table->end_frame) {
        HSD_GObjPLink_80390228(gobj);
    }
}
/// @brief Updates navigation arrow visibility based on scroll/selection state.
/// @param gobj The diagram GObj
/// @details Shows/hides arrows:
///   - down_arrow (x34): hidden when at bottom
///   - up_arrow (x38): hidden when scroll_offset == 0
///   - left_arrow (x3C): hidden when at first selection
///   - right_arrow (x40): hidden when at last selection
void mnDiagram2_UpdateScrollArrows(HSD_GObj* gobj)
{
    Diagram2* data;
    AnimLoopSettings* table;
    HSD_JObj* jobj;

    data = gobj->user_data;
    table = (AnimLoopSettings*) ((u8*) &mnDiagram2_803EEAD0 + 0x9C);

    jobj = data->down_arrow;
    mn_8022ED6C(jobj, table);
    if (data->is_name_mode) {
        if (data->scroll_offset + 10 < 0x18) {
            HSD_JObjClearFlagsAll(jobj, 0x10);
        } else {
            HSD_JObjSetFlagsAll(jobj, 0x10);
        }
    } else {
        if (data->scroll_offset + 10 < 0x15) {
            HSD_JObjClearFlagsAll(jobj, 0x10);
        } else {
            HSD_JObjSetFlagsAll(jobj, 0x10);
        }
    }

    jobj = data->up_arrow;
    mn_8022ED6C(jobj, table);
    if (data->scroll_offset) {
        HSD_JObjClearFlagsAll(jobj, 0x10);
    } else {
        HSD_JObjSetFlagsAll(jobj, 0x10);
    }

    jobj = data->left_arrow;
    mn_8022ED6C(jobj, table);
    if (data->is_name_mode) {
        if (data->selected_name_idx) {
            HSD_JObjClearFlagsAll(jobj, 0x10);
        } else {
            HSD_JObjSetFlagsAll(jobj, 0x10);
        }
    } else {
        if (data->selected_fighter_idx != 0) {
            HSD_JObjClearFlagsAll(jobj, 0x10);
        } else {
            HSD_JObjSetFlagsAll(jobj, 0x10);
        }
    }

    jobj = data->right_arrow;
    mn_8022ED6C(jobj, table);
    if (data->is_name_mode != 0) {
        if (data->selected_name_idx !=
            (u8) mnDiagram_GetNextNameIndex(data->selected_name_idx))
        {
            HSD_JObjClearFlagsAll(jobj, 0x10);
        } else {
            HSD_JObjSetFlagsAll(jobj, 0x10);
        }
    } else {
        if (data->selected_fighter_idx !=
            (u8) mnDiagram_GetNextFighterIndex(data->selected_fighter_idx))
        {
            HSD_JObjClearFlagsAll(jobj, 0x10);
        } else {
            HSD_JObjSetFlagsAll(jobj, 0x10);
        }
    }
}
/// @brief Per-frame callback that updates scroll arrows or starts exit
/// animation.
/// @param gobj The diagram GObj
void mnDiagram2_Think(HSD_GObj* gobj)
{
    Diagram2* data;
    u8* src;
    u8 mode;
    PAD_STACK(8);

    src = (u8*) &mn_804A04F0;
    data = gobj->user_data;
    mode = src[0];
    if (mode != 0x1E || src[0x10] != 1) {
        if (mode == 0x1E) {
            HSD_GObjPLink_80390228(gobj);
        } else {
            HSD_GObjProc* proc;

            HSD_GObjProc_8038FE24(HSD_GObj_804D7838);
            proc = HSD_GObjProc_8038FD54(gobj, mnDiagram2_OnAnimComplete, 0);
            proc->flags_3 = HSD_GObj_804D783C;
            HSD_JObjSetFlagsAll(((HSD_JObj**) data)[4], 0x10);
            if (data->header_text != NULL) {
                HSD_SisLib_803A5CC4(data->header_text);
                data->header_text = NULL;
            }
            return;
        }
    }
    mnDiagram2_UpdateScrollArrows(gobj);
}
/// @brief GObj destructor callback that frees user data.
/// @param data The user data to free
void mnDiagram2_FreeUserData(Diagram2* data)
{
    if (data->header_text != NULL) {
        HSD_SisLib_803A5CC4(data->header_text);
    }
    HSD_Free(data);
}
/// @brief Initializes user data fields to default values.
/// @param arg The user data struct to initialize
void mnDiagram2_InitUserData(void* arg)
{
    Diagram2* data = arg;
    u8* src = (u8*) &mn_804A04F0;
    int i;

    data->saved_menu = src[0];
    data->saved_selection = *(u16*) (src + 2);
    data->anim_state = 1;
    data->scroll_offset = 0;
    data->selected_fighter_idx = 0;
    data->selected_name_idx = 0;
    data->is_name_mode = gmMainLib_8015CC34()->xD;

    for (i = 0; i < 10; i++) {
        data->row_labels[i] = NULL;
        data->row_values[i] = NULL;
        data->row_icons[i] = NULL;
    }

    data->header_text = NULL;
}

/// @brief Creates the VS Records diagram GObj and populates initial stat rows.
/// @param arg0 Unused parameter
void mnDiagram2_Create(int arg0)
{
    char* base = (char*) &mnDiagram2_803EEAD0;
    mnDiagram_ArchiveData* archive = &mnDiagram_804A0834;
    HSD_GObj* gobj;
    HSD_JObj* jobj;
    Diagram2* data;
    int i;
    int threshold;
    u32 var_r29;
    int idx;
    u8 x46_or_x47;
    int offset;
    Diagram2* user_data;

    gobj = GObj_Create(6, 7, 0x80);
    mnDiagram2_804D6C18 = gobj;
    jobj = HSD_JObjLoadJoint(archive->x0);
    HSD_GObjObject_80390A70(gobj, HSD_GObj_804D7849, jobj);
    GObj_SetupGXLink(gobj, HSD_GObj_JObjCallback, 6, 0x80);
    HSD_JObjAddAnimAll(jobj, archive->x4, archive->x8, archive->xC);
    HSD_JObjReqAnimAll(jobj, mnDiagram2_804DBFCC);

    data = (Diagram2*) HSD_MemAlloc(0xC8);
    if (data == NULL) {
        OSReport(base + 0x108);
        __assert(base + 0x120, 0x3E6, base + 0x130);
    }
    mnDiagram2_InitUserData(data);
    GObj_InitUserData(gobj, 0, (void (*)(void*)) mnDiagram2_FreeUserData,
                      data);

    for (i = 0; i < 15; i++) {
        lb_80011E24(jobj, (HSD_JObj**) ((u8*) data + (i << 2) + 8), i, -1);
    }

    HSD_GObjProc_8038FD54(gobj, mnDiagram2_Think, 0);

    if (data->is_name_mode) {
        x46_or_x47 = data->selected_name_idx;
        var_r29 = (u8) mnDiagram_GetNameByIndex(x46_or_x47);
        threshold = 0x18;
    } else {
        x46_or_x47 = data->selected_fighter_idx;
        var_r29 = (u8) mnDiagram_GetFighterByIndex(x46_or_x47);
        threshold = 0x15;
    }

    idx = (u8) data->scroll_offset;
    for (i = 0; i < 10; i++) {
        if (idx >= threshold) {
            offset = idx - threshold;
        } else {
            offset = idx;
        }
        mnDiagram2_CreateStatRow(gobj, data->is_name_mode, offset, i, var_r29);
    }

    user_data = gobj->user_data;
    if (data->is_name_mode) {
        HSD_JObjSetFlagsAll(user_data->fighter_mode_header, 0x10);
        HSD_JObjClearFlagsAll(user_data->name_mode_header, 0x10);
    } else {
        HSD_JObjClearFlagsAll(user_data->fighter_mode_header, 0x10);
        HSD_JObjSetFlagsAll(user_data->name_mode_header, 0x10);
    }

    if (data->is_name_mode) {
        x46_or_x47 = user_data->selected_name_idx;
    } else {
        x46_or_x47 = user_data->selected_fighter_idx;
    }
    mnDiagram2_UpdateHeader(gobj, data->is_name_mode, x46_or_x47);
}

/// @brief Entry point for VS Records page 2 - initializes diagram and input
/// handler.
void mnDiagram2_Init(void)
{
    MenuFlow* data = &mn_804A04F0;
    HSD_GObjProc* gobj;

    data->x10 = 1;
    data->hovered_selection = 0;
    mnDiagram2_Create(0);
    gobj = HSD_GObjProc_8038FD54(GObj_Create(0, 1, 0x80),
                                 mnDiagram2_HandleInput, 0);
    gobj->flags_3 = HSD_GObj_804D783C;
}

/// @brief Returns the fighter at rank N for a given stat type.
/// @param stat_type The stat type to rank by
/// @param rank The rank to retrieve (0 = highest, 1 = second highest, etc.)
/// @return Fighter ID at the given rank, or 25 if no data
u8 mnDiagram2_GetRankedFighter(u8 stat_type, u8 rank)
{
    mnDiagram2_SortEntry entries[25];
    f64 temp0;
    f64 temp8;
    mnDiagram2_SortEntry* base;
    mnDiagram2_SortEntry* ptr;
    mnDiagram2_SortEntry* curr;
    int i;
    int j;
    int k;
    int maxIdx;
    int zero;
    int neg1;
    u8 name;

    base = entries;
    ptr = base;
    i = 0;
    zero = 0;
    neg1 = -1;

    for (i = 0; i < 25; i++) {
        name = mnDiagram_GetFighterByIndex(i);
        ptr->name = name;
        if (mn_IsFighterUnlocked(name) != 0) {
            ptr->xC = mnDiagram2_GetStatValue(0, stat_type, name);
            ptr->x8 = zero;
        } else {
            ptr->xC = neg1;
            ptr->x8 = neg1;
        }
    }

    // Selection sort with -1 handling
    i = 0;
    do {
        k = i + 1;
        maxIdx = i;
        curr = &entries[k];
        while (k < 25) {
            // Skip entries with -1 value
            if (curr->value != (u64) neg1) {
                // Update if curr > entries[maxIdx] OR entries[maxIdx] == -1
                u64 maxVal = entries[maxIdx].value;
                if (curr->value > maxVal || maxVal == (u64) neg1) {
                    maxIdx = k;
                }
            }
            curr++;
            k++;
        }

        if (maxIdx != i) {
            ptr = &entries[maxIdx];
            j = maxIdx - i;
            temp0 = ptr->d0;
            temp8 = ptr->d8;

            while (j > 0) {
                ptr->d0 = (ptr - 1)->d0;
                ptr->d8 = (ptr - 1)->d8;
                ptr--;
                j--;
            }
            base->d0 = temp0;
            base->d8 = temp8;
        }
        base++;
        i++;
    } while (i < 25);

    // Return
    ptr = &entries[rank];
    if (ptr->value == (u64) -1) {
        return 25;
    }
    return entries[rank].name;
}

/// @brief Returns the name entry at rank N for a given stat type.
/// @param stat_type The stat type to rank by
/// @param rank The rank to retrieve (0 = highest, 1 = second highest, etc.)
/// @return Name ID at the given rank, or 0x78 if rank exceeds name count
u8 mnDiagram2_GetRankedName(u8 stat_type, u8 rank)
{
    mnDiagram2_SortEntry entries[120];
    mnDiagram2_SortEntry* base;
    mnDiagram2_SortEntry* ptr;
    int count;
    int i;
    int j;
    int maxIdx;
    int zero;

    count = GetNameCount();
    if ((s32) rank >= count) {
        return 0x78;
    }

    base = entries;
    ptr = base;
    i = 0;
    zero = 0;
    while (i < count) {
        ptr->name = mnDiagram_GetNameByIndex(i);
        ptr->xC =
            mnDiagram2_GetStatValue(1, stat_type, mnDiagram_GetNameByIndex(i));
        i++;
        ptr->x8 = zero;
        ptr++;
    }

    i = 0;
    while (i < count) {
        mnDiagram2_SortEntry* inner;
        f64 temp0;
        f64 temp8;

        j = i + 1;
        maxIdx = i;
        inner = &entries[j];
        while (j < count) {
            u64 a = inner->value;
            u64 b = entries[maxIdx].value;
            if (a > b) {
                maxIdx = j;
            }
            inner++;
            j++;
        }

        if (maxIdx != i) {
            ptr = &entries[maxIdx];
            temp0 = ptr->d0;
            j = maxIdx - i;
            temp8 = ptr->d8;

            while (j > 0) {
                ptr->d0 = (ptr - 1)->d0;
                ptr->d8 = (ptr - 1)->d8;
                ptr--;
                j--;
            }
            base->d0 = temp0;
            base->d8 = temp8;
        }
        base++;
        i++;
    }

    return entries[rank].name;
}

/// @brief Computes aggregated fighter ranking across all saved names for icon
/// stats.
/// @param out Output buffer (cast to SortEntry*) for result
/// @param type Stat type (0x15=Most Played, 0x16=2nd Most, 0x17=Least Played)
/// @param idx Rank index to retrieve
void mnDiagram2_GetAggregatedFighterRank(u8* out, u8 type, u8 idx)
{
    mnDiagram2_SortEntry entries[25];
    f64 temp0;
    f64 temp8;
    mnDiagram2_SortEntry* base;
    mnDiagram2_SortEntry* curr;
    void* funcTable;
    int count;
    int res;
    mnDiagram2_SortEntry* ptr;
    mnDiagram2_SortEntry* arr;
    int i;
    int j;
    int k;
    int zero;

    base = entries;
    ptr = base;
    i = 0;
    zero = 0;

    do {
        ptr->name = mnDiagram_GetFighterByIndex(i);
        i++;
        ptr->xC = zero;
        ptr->x8 = zero;
        ptr++;
    } while (i < 25);

    count = GetNameCount();
    funcTable = (void*) mnDiagram_GetNamePlayTimeByFighter;
    arr = entries;

    i = 0;
    while (i < count) {
        switch ((s32) type) {
        case 0x15:
            res = mnDiagram_GetRankedFighterForName(0, i, funcTable);
            break;
        case 0x16:
            res = mnDiagram_GetRankedFighterForName(1, i, funcTable);
            break;
        case 0x17:
            res = mnDiagram_GetLeastPlayedFighter((u8) i);
            break;
        default:
            goto next;
        }

        if (res != 25) {
            ptr = base;
            k = 0;
            for (j = 25; j > 0; j--) {
                if (res == ptr->name) {
                    arr[k].value += 1;
                    break;
                }
                ptr++;
                k++;
            }
        }
    next:
        i++;
    }

    // Bubble sort
    j = 0;
    do {
        k = j + 1;
        curr = &entries[k];
        while (k < 25) {
            u64 a = base->value;
            u64 b = curr->value;
            if (a < b) {
                temp0 = base->d0;
                temp8 = base->d8;
                base->d0 = curr->d0;
                base->d8 = curr->d8;
                curr->d0 = temp0;
                curr->d8 = temp8;
            }
            curr++;
            k++;
        }
        base++;
        j++;
    } while (j < 25);

    // Write result to output buffer
    curr = &entries[idx];
    if (curr->value == 0) {
        curr->name = 25;
    }
    ((mnDiagram2_SortEntry*) out)->d0 = curr->d0;
    ((mnDiagram2_SortEntry*) out)->d8 = curr->d8;
}

/// @brief Clears the detail view by freeing text objects and removing JObj.
/// @param gobj The GObj containing the detail view data
void mnDiagram2_ClearDetailView(HSD_GObj* gobj)
{
    Diagram2DetailView* data;
    Diagram2DetailView* ptr;
    void* tmp;
    HSD_JObj* jobj;
    int i;

    ptr = data = (Diagram2DetailView*) HSD_GObjGetUserData(gobj);

    if (data->title_text != NULL) {
        HSD_SisLib_803A5CC4(data->title_text);
        data->title_text = NULL;
    }

    for (i = 0; i < 5; i++) {
        if (data->detail_texts[i] != NULL) {
            HSD_SisLib_803A5CC4(ptr->detail_texts[i]);
            data->detail_texts[i] = NULL;
        }
    }

    if (data->x5C != NULL) {
        HSD_SisLib_803A5CC4(data->x5C);
        data->x5C = NULL;
    }

    tmp = data->jobj_container;
    if (tmp == NULL) {
        tmp = NULL;
    } else {
        tmp = data->jobj_container->jobj;
    }
    jobj = tmp;
    if (jobj != NULL) {
        HSD_JObjRemoveAll(jobj);
    }
}
