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

#endif
