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

#endif
