#ifndef __GALE01_23EA2C
#define __GALE01_23EA2C

#include "mndiagram.h" // IWYU pragma: export

#include <placeholder.h>

#include <m2c_macros.h>
#include <melee/gm/gmmain_lib.h>
#include <melee/gm/types.h>
#include <melee/lb/lblanguage.h>
#include <melee/mn/mnmain.h>
#include <melee/mn/mnname.h>

extern char mnDiagram_804D4FA4;
extern SDATA char mnDiagram_804D4FA8[];
extern SDATA char mnDiagram_804D4FB0[];
extern f32 mnDiagram_803EE774[];
extern f32 mnDiagram_803EE758[];
extern void* mnDiagram_804A0814[4];
extern void* mnDiagram_804A07E4[4];
extern void* mnDiagram_804A07F4[4];
extern void* mnDiagram_804A0804[4];
extern void* mnDiagram_804A0824[4];
extern void* mnDiagram_804A0834[4];
extern HSD_GObj* mnDiagram_804D6C10;
extern u8 HSD_GObj_804D7849;

/// Sorted fighter indices array (25 fighters + padding)
struct mnDiagram_804A0750_t {
    u8 sorted_fighters[0x19]; // Sorted by total KOs
    u8 pad_19[3];
};
STATIC_ASSERT(sizeof(struct mnDiagram_804A0750_t) == 0x1C);

/// Sorted name indices array (120 names)
struct mnDiagram_804A076C_t {
    u8 sorted_names[0x78]; // Sorted by total KOs
};
STATIC_ASSERT(sizeof(struct mnDiagram_804A076C_t) == 0x78);

/* 4A0750 */ extern struct mnDiagram_804A0750_t mnDiagram_804A0750;
/* 4A076C */ extern struct mnDiagram_804A076C_t mnDiagram_804A076C;

/// Archive asset pointers struct (for mnDiagram_802437E8)
/// Cast from &mnDiagram_804A0750 to access asset arrays
typedef struct mnDiagram_Assets {
    /* 0x00 */ u8 sorted_fighters[0x19];
    /* 0x19 */ u8 pad_19[3];
    /* 0x1C */ u8 sorted_names[0x78];
    /* 0x94 */ void* SubB1[4];
    /* 0xA4 */ void* ConB2[4];
    /* 0xB4 */ void* ConB3[4];
    /* 0xC4 */ void* CursorB3[4];
    /* 0xD4 */ void* ConB1[4];
    /* 0xE4 */ void* CursorB1_FaceB[4];
    /* 0xF4 */ void* FaceB_NmB[4];
    /* 0x104 */ void* NmB_shape[1];
} mnDiagram_Assets;
STATIC_ASSERT(sizeof(mnDiagram_Assets) == 0x108);

/// Main user data struct for VS Records diagram (0x50 bytes)
typedef struct mnDiagram_Data {
    /* 0x00 */ u8 saved_menu; ///< Saved menu ID on entry
    /* 0x01 */ u8 pad_1;
    /* 0x02 */ u16 saved_selection; ///< Saved hovered selection on entry
    /* 0x04 */ u8 anim_state;       ///< 0 = idle, 1 = intro anim playing
    /* 0x05 */ u8 pad_5[3];
    /* 0x08 */ HSD_JObj* jobjs[13]; ///< JObj references, filled by lb_80011E24
    /* 0x3C */ u16
        fighter_cursor_pos;          ///< Fighter mode cursor (row << 8 | col)
    /* 0x3E */ u16 name_cursor_pos;  ///< Name mode cursor (row << 8 | col)
    /* 0x40 */ HSD_GObj* popup_gobj; ///< Popup window GObj (or NULL)
    /* 0x44 */ u8 is_name_mode;      ///< 0 = fighter mode, 1 = name mode
    /* 0x45 */ u8 pad_45[3];
    /* 0x48 */ HSD_Text* col_header_text; ///< Column header text object
    /* 0x4C */ HSD_Text* row_header_text; ///< Row header text object
} mnDiagram_Data;
STATIC_ASSERT(sizeof(mnDiagram_Data) == 0x50);

/// User data structure for mnDiagram_PopupCleanup callback.
/// Overlay of mnDiagram_PopupData - only accesses text array.
typedef struct mnDiagram_CleanupData {
    /* 0x00 */ char jobjs_reserved[0x38]; ///< JObj array (unused by cleanup)
    /* 0x38 */ HSD_Text* text[6];         ///< Text objects to free
} mnDiagram_CleanupData;

/// User data structure for mnDiagram_ExitAnimProc callback.
/// Overlay of mnDiagram_Data - only accesses jobj at offset 0x0C.
typedef struct mnDiagram_AnimData {
    /* 0x00 */ char header_reserved[0x0C]; ///< menu state (unused by anim)
    /* 0x0C */ HSD_JObj* jobj;             ///< JObj for exit animation
} mnDiagram_AnimData;

#endif
