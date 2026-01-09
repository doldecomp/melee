#ifndef MELEE_MN_FORWARD_H
#define MELEE_MN_FORWARD_H

typedef struct AnimLoopSettings AnimLoopSettings;
typedef struct CountEntry CountEntry;
typedef struct CSSData CSSData;
typedef struct CSSDoor CSSDoor;
typedef struct CSSDoorsData CSSDoorsData;
typedef struct CSSIcon CSSIcon;
typedef struct CSSIconsData CSSIconsData;
typedef struct CSSKOStar CSSKOStar;
typedef struct CSSModeInfo CSSModeInfo;
typedef struct CSSTag CSSTag;
typedef struct CSSTagData CSSTagData;
typedef struct MenuKindData MenuKindData;
typedef struct PlayerInitData PlayerInitData;
typedef struct SSSData SSSData;
typedef struct StartMeleeData StartMeleeData;
typedef struct StartMeleeRules StartMeleeRules;
typedef struct VsModeData VsModeData;

typedef unsigned char MenuKind8;
typedef unsigned char MenuState8;

typedef enum _Mode {
    Mode_Time,
    Mode_Stock,
    Mode_Coin,
    Mode_Bonus
} Mode;

typedef enum _StageSelectMode {
    StageSelectMode_On,
    StageSelectMode_Random,
    StageSelectMode_Ordered,
    StageSelectMode_Turns,
    StageSelectMode_Loser
} StageSelectMode;

// Not same as CharacterKind bc not as many characters as icons (missing Sheik,
// Master Hand, etc)
typedef enum CSSIconHud {
    ICONHUD_CAPTAIN = 0x00,
    ICONHUD_DONKEY = 0x01,
    ICONHUD_FOX = 0x02,
    ICONHUD_GAMEWATCH = 0x03,
    ICONHUD_KIRBY = 0x04,
    ICONHUD_KOOPA = 0x05,
    ICONHUD_LINK = 0x06,
    ICONHUD_LUIGI = 0x07,
    ICONHUD_MARIO = 0x08,
    ICONHUD_MARS = 0x09,
    ICONHUD_MEWTWO = 0x0A,
    ICONHUD_NESS = 0x0B,
    ICONHUD_PEACH = 0x0C,
    ICONHUD_PIKACHU = 0x0D,
    ICONHUD_POPONANA = 0x0E,
    ICONHUD_PURIN = 0x0F,
    ICONHUD_SAMUS = 0x10,
    ICONHUD_YOSHI = 0x11,
    ICONHUD_ZELDA = 0x12,
    ICONHUD_FALCO = 0x13,
    ICONHUD_CLINK = 0x14,
    ICONHUD_DRMARIO = 0x15,
    ICONHUD_EMBLEM = 0x16,
    ICONHUD_PICHU = 0x17,
    ICONHUD_GANON = 0x18
} CSSIconHud;

typedef enum MenuKind {
    /* +00 */ MENU_KIND_MAIN = 0,
    /* +01 */ MENU_KIND_1P = 1,
    /* +02 */ MENU_KIND_VS = 2,
    /* +03 */ MENU_KIND_TOY = 3,
    /* +04 */ MENU_KIND_SETTINGS = 4,
    /* +05 */ MENU_KIND_DATA = 5,
    /* +06 */ MENU_KIND_REG = 6,
    /* +07 */ MENU_KIND_7 = 7, ///< debug event?
    /* +08 */ MENU_KIND_8 = 8,
    /* +09 */ MENU_KIND_STADIUM = 9,
    /* +0A */ MENU_KIND_10 = 10,
    /* +0B */ MENU_KIND_11 = 11,
    /* +0C */ MENU_KIND_SPECIAL = 12,
    /* +0D */ MENU_KIND_RULES = 13,
    /* +0E */ MENU_KIND_14 = 14,
    /* +0F */ MENU_KIND_RULES_EXTRA = 15,
    /* +10 */ MENU_KIND_RULES_ITEMS = 16,
    /* +11 */ MENU_KIND_RULES_STAGE = 17,
    /* +12 */ MENU_KIND_NAME_ENTRY = 18,
    /* +13 */ MENU_KIND_SETTINGS_RUMBLE = 19,
    /* +14 */ MENU_KIND_SETTINGS_SOUND = 20,
    /* +15 */ MENU_KIND_DISPLAY = 21,
    /* +16 */ MENU_KIND_22 = 22,
    /* +17 */ MENU_KIND_SETTINGS_LANG = 23,
    /* +18 */ MENU_KIND_SETTINGS_ERASE = 24,
    /* +19 */ MENU_KIND_DATA_SNAP = 25,
    /* +1A */ MENU_KIND_DATA_ARCHIVES = 26,
    /* +1B */ MENU_KIND_27 = 27,
    /* +1C */ MENU_KIND_RECORDS = 28,
    /* +1D */ MENU_KIND_DATA_SPECIAL = 29,
    /* +1E */ MENU_KIND_RECORDS_VS = 30,
    /* +1F */ MENU_KIND_RECORDS_BONUS = 31,
    /* +20 */ MENU_KIND_RECORDS_MISC = 32,
    /* +21 */ MENU_KIND_33 = 33, ///< debug css?
    /* +22 */ MENU_KIND_34 = 34,
} MenuKind;

typedef enum MenuState {
    MENU_STATE_IDLE = 0,
    MENU_STATE_ENTER_TO = 1,
    MENU_STATE_EXIT_FROM = 2,
    MENU_STATE_EXIT_TO = 3,
    MENU_STATE_ENTER_FROM = 4,
    MENU_STATE_5 = 5,
} MenuState;

/// @brief selection refers to the invidual options inside menus/submenus
/// @todo should these be moved into their respective TU's?
typedef enum MainMenuSelection {
    SEL_MAIN_1P = 0,
    SEL_MAIN_VS = 1,
    SEL_MAIN_TOY = 2,
    SEL_MAIN_SETTINGS = 3,
    SEL_MAIN_DATA = 4,
} MainMenuSelection;

typedef enum OnePlayerMenuSelection {
    SEL_1P_REG = 0,
    SEL_1P_EVENT = 1,
    SEL_1P_2 = 2, ///< hidden
    SEL_1P_STADIUM = 3,
    SEL_1P_TRAINING = 4,
} OnePlayerMenuSelection;

typedef enum RegMatchMenuSelection {
    SEL_REG_CLASSIC = 0,
    SEL_REG_ADVENTURE = 1,
    SEL_REG_ALLSTAR = 2,
} RegMatchMenuSelection;

typedef enum StadiumMenuSelection {
    SEL_STADIUM_TARGET = 0,
    SEL_STADIUM_HOMERUN = 1,
    SEL_STADIUM_MULTIMAN = 2,
} StadiumMenuSelection;

typedef enum VsMenuSelection {
    SEL_VS_MELEE = 0,
    SEL_VS_TOURNAMENT = 1,
    SEL_VS_SPECIAL = 2,
    SEL_VS_RULES = 3,
    SEL_VS_NAME = 4,
} VsMenuSelection;

typedef enum SpecialVsMenuSelection {
    SEL_SPECIAL_VS_CAMERA = 0,
    SEL_SPECIAL_VS_STAMINA = 1,
    SEL_SPECIAL_VS_SUDDEN_DEATH = 2,
    SEL_SPECIAL_VS_GIANT = 3,
    SEL_SPECIAL_VS_TINY = 4,
    SEL_SPECIAL_VS_INVISIBLE = 5,
    SEL_SPECIAL_VS_FIXED_CAMERA = 6,
    SEL_SPECIAL_VS_SINGLE_BUTTON = 7,
    SEL_SPECIAL_VS_LIGHTNING = 8,
    SEL_SPECIAL_VS_SLOMO = 9,
} SpecialVsMenuSelection;

typedef enum SettingsMenuSelection {
    SEL_SETTINGS_RUMBLE = 0,
    SEL_SETTINGS_SOUND = 1,
    SEL_SETTINGS_DISPLAY = 2,
    SEL_SETTINGS_3 = 3, ///< hidden
    SEL_SETTINGS_LANG = 4,
    SEL_SETTINGS_ERASE = 5,
} SettingsMenuSelection;

typedef enum DataMenuSelection {
    SEL_DATA_SNAP = 0,
    SEL_DATA_ARCHIVES = 1,
    SEL_DATA_SOUND = 2,
    SEL_DATA_RECORDS = 3,
    SEL_DATA_SPECIAL = 4,
} DataMenuSelection;

typedef enum RecordsMenuSelection {
    SEL_RECORDS_VS = 0,
    SEL_RECORDS_BONUS = 1,
    SEL_RECORDS_MISC = 2,
} RecordsMenuSelection;

typedef enum TrophyMenuSelection {
    SEL_TOY_GALLERY = 0,
    SEL_TOY_LOTTERY = 1,
    SEL_TOY_2 = 2, ///< hidden
    SEL_TOY_COLLECTION = 3,
} TrophyMenuSelection;

#endif
