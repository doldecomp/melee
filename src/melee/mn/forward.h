#ifndef MELEE_MN_FORWARD_H
#define MELEE_MN_FORWARD_H

typedef struct CSSData CSSData;
typedef struct PlayerInitData PlayerInitData;
typedef struct StartMeleeData StartMeleeData;
typedef struct StartMeleeRules StartMeleeRules;
typedef struct VsModeData VsModeData;
typedef struct CSSModeInfo CSSModeInfo;
typedef struct CSSIcon CSSIcon;
typedef struct CSSIconsData CSSIconsData;
typedef struct CSSDoor CSSDoor;
typedef struct CSSTagData CSSTagData;
typedef struct CSSTag CSSTag;
typedef struct CSSKOStar CSSKOStar;
typedef struct CSSDoorsData CSSDoorsData;
typedef struct SSSData SSSData;
typedef struct AnimLoopSettings AnimLoopSettings;

#define MENU_BTN_UP      (1 << 0)   // 0x001
#define MENU_BTN_DOWN    (1 << 1)   // 0x002
#define MENU_BTN_LEFT    (1 << 2)   // 0x004
#define MENU_BTN_RIGHT   (1 << 3)   // 0x008
#define MENU_BTN_CONFIRM (1 << 4)   // 0x010
#define MENU_BTN_B       (1 << 5)   // 0x020
#define MENU_BTN_L       (1 << 6)   // 0x040
#define MENU_BTN_R       (1 << 7)   // 0x080
#define MENU_BTN_START   (1 << 8)   // 0x100
#define MENU_BTN_A       (1 << 9)   // 0x200
#define MENU_BTN_X       (1 << 10)  // 0x400
#define MENU_BTN_Y       (1 << 11)  // 0x800

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
    MENU_KIND_MAIN = 0,
    MENU_KIND_1P = 1,
    MENU_KIND_VS = 2,
    MENU_KIND_TOY = 3,
    MENU_KIND_SETTINGS = 4,
    MENU_KIND_DATA = 5,
    MENU_KIND_REG = 6,
    MENU_KIND_7 = 7,
    MENU_KIND_8 = 8,
    MENU_KIND_STADIUM = 9,
    MENU_KIND_10 = 10,
    MENU_KIND_11 = 11,
    MENU_KIND_SPECIAL = 12,
    MENU_KIND_RULES = 13,
    MENU_KIND_14 = 14,
    MENU_KIND_RULES_EXTRA = 15,
    MENU_KIND_RULES_ITEMS = 16,
    MENU_KIND_RULES_STAGE = 17,
    MENU_KIND_NAME_ENTRY = 18,
    MENU_KIND_SETTINGS_RUMBLE = 19,
    MENU_KIND_SETTINGS_SOUND = 20,
    MENU_KIND_DISPLAY = 21,
    MENU_KIND_22 = 22,
    MENU_KIND_SETTINGS_LANG = 23,
    MENU_KIND_SETTINGS_ERASE = 24,
    MENU_KIND_DATA_SNAP = 25,
    MENU_KIND_DATA_ARCHIVES = 26,
    MENU_KIND_27 = 27,
    MENU_KIND_RECORDS = 28,
    MENU_KIND_DATA_SPECIAL = 29,
    MENU_KIND_RECORDS_VS = 30,
    MENU_KIND_RECORDS_BONUS = 31,
    MENU_KIND_RECORDS_MISC = 32,
    MENU_KIND_33 = 33,
    MENU_KIND_34 = 34,
} MenuKind;

typedef enum MenuState {
    MENU_STATE_IDLE = 0,
    MENU_STATE_ENTER_TO = 1,
    MENU_STATE_EXIT_FROM = 2,
    MENU_STATE_EXIT_TO = 3,
    MENU_STATE_ENTER_FROM = 4,
    MENU_STATE_COUNT = 5,
} MenuState;

typedef enum MenuOptions_Main {
    MENU_OPTION_MAIN_1P = 0,
    MENU_OPTION_MAIN_VS = 1,
    MENU_OPTION_MAIN_TOY = 2,
    MENU_OPTION_MAIN_SETTINGS = 3,
    MENU_OPTION_MAIN_DATA = 4,
    MENU_OPTION_5 = 5,
} MenuOptions_Main;

typedef enum MenuOptions_1P {
    MENU_OPTION_1P_REG = 0,
    MENU_OPTION_1P_EVENT = 1,
    MENU_OPTION_1P_STADIUM = 2,
    MENU_OPTION_1P_TRAINING = 3,
} MenuOptions_1P;

typedef enum MenuOptions_Vs {
    MENU_OPTION_VS_MELEE = 0,
    MENU_OPTION_VS_TOU = 1,
    MENU_OPTION_VS_SPECIAL = 2,
    MENU_OPTION_VS_RULES = 3,
    MENU_OPTION_VS_NAME = 4,
} MenuOptions_Vs;

typedef enum MenuOptions_Settings {
    MENU_OPTION_SETTINGS_RUMBLE = 0,
    MENU_OPTION_SETTINGS_SOUND = 1,
    MENU_OPTION_SETTINGS_DISPLAY = 2,
    MENU_OPTION_SETTINGS_0x3 = 3,
    MENU_OPTION_SETTINGS_LANG = 4,
    MENU_OPTION_SETTINGS_ERASE = 5,
} MenuOptions_Settings;

typedef enum MenuOptions_Data {
    MENU_OPTION_DATA_SNAP = 0,
    MENU_OPTION_DATA_ARCHIVES = 1,
    MENU_OPTION_DATA_SOUND = 2,
    MENU_OPTION_DATA_RECORDS = 3,
    MENU_OPTION_DATA_SPECIAL = 4,
} MenuOptions_Data;

typedef enum MenuOptions_Records {
    MENU_OPTION_RECORDS_VS = 0,
    MENU_OPTION_RECORDS_BONUS = 1,
    MENU_OPTION_RECORDS_MISC = 2,
} MenuOptions_Records;

#endif
