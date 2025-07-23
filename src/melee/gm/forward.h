#ifndef MELEE_GM_FORWARD_H
#define MELEE_GM_FORWARD_H

typedef enum MajorSceneKind {
    /* 00 */ MJ_TITLE,
    /* 01 */ MJ_MENU,
    /* 02 */ MJ_VS,
    /* 03 */ MJ_CLASSIC,
    /* 04 */ MJ_ADVENTURE,
    /* 05 */ MJ_ALLSTAR,
    /* 06 */ MJ_DEBUG,
    /* 07 */ MJ_DEBUG_SOUND_TEST,
    /* 08 */ MJ_HANYU_CSS,
    /* 09 */ MJ_HANYU_SSS,
    /* 0A */ MJ_CAMERA_MODE,
    /* 0B */ MJ_TOY_GALLERY,
    /* 0C */ MJ_TOY_LOTTERY,
    /* 0D */ MJ_TOY_COLLECTION,
    /* 0E */ MJ_DEBUG_VS,
    /* 0F */ MJ_TARGET_TEST,
    /* 10 */ MJ_SUPER_SUDDEN_DEATH_VS,
    /* 11 */ MJ_INVISIBLE_VS,
    /* 12 */ MJ_SLOMO_VS,
    /* 13 */ MJ_LIGHTNING_VS,
    /* 14 */ MJ_CHALLENGER_APPROACH,
    /* 15 */ MJ_CLASSIC_GOVER,
    /* 16 */ MJ_ADVENTURE_GOVER,
    /* 17 */ MJ_ALLSTAR_GOVER,
    /* 18 */ MJ_OPENING_MV,
    /* 19 */ MJ_DEBUG_CUTSCENE,
    /* 1A */ MJ_DEBUG_GOVER, ///< trophy fall and 'congrats'
    /* 1B */ MJ_TOURNAMENT,
    /* 1C */ MJ_TRAINING,
    /* 1D */ MJ_TINY_VS,
    /* 1E */ MJ_GIANT_VS,
    /* 1F */ MJ_STAMINA_VS,
    /* 20 */ MJ_HOME_RUN_CONTEST,
    /* 21 */ MJ_10MAN_VS,
    /* 22 */ MJ_100MAN_VS,
    /* 23 */ MJ_3MIN_VS,
    /* 24 */ MJ_15MIN_VS,
    /* 25 */ MJ_ENDLESS_VS,
    /* 26 */ MJ_CRUEL_VS,
    /* 27 */ MJ_PROGRESSIVE_SCAN,
    /* 28 */ MJ_BOOT,
    /* 29 */ MJ_MEMCARD,
    /* 2A */ MJ_FIXED_CAMERA_VS,
    /* 2B */ MJ_EVENT,
    /* 2C */ MJ_SINGLE_BUTTON_VS,
    /* 2D */ MJ_COUNT,
} MajorSceneKind;

typedef struct MajorScene MajorScene;
typedef struct MinorScene MinorScene;
typedef struct MinorSceneHandler MinorSceneHandler;
typedef struct MinorSceneInfo MinorSceneInfo;

typedef struct datetime datetime;
typedef struct GameRules GameRules;
typedef struct gm_8016A92C_arg0_t gm_8016A92C_arg0_t;
typedef struct gm_8017DB6C_arg0_t gm_8017DB6C_arg0_t;
typedef struct lbl_8046B6A0_t lbl_8046B6A0_t;
typedef struct lbl_8046B6A0_24C_t lbl_8046B6A0_24C_t;
typedef struct Placeholder_8016AE38_flags Placeholder_8016AE38_flags;
typedef struct Placeholder_8016AE38_flags_2 Placeholder_8016AE38_flags_2;
typedef struct Placeholder_8016AE50_ret_val Placeholder_8016AE50_ret_val;
typedef struct MatchPlayerData MatchPlayerData;
typedef struct MatchEnd MatchEnd;
typedef struct MatchExitInfo MatchExitInfo;
typedef struct TmData TmData;

#endif
