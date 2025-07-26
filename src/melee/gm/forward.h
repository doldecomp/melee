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

typedef enum MinorSceneKind {
    /* +00 */ MN_TITLE,
    /* +01 */ MN_MENU,
    /* +02 */ MN_VS,
    /* +03 */ MN_SUDDEN_DEATH,
    /* +04 */ MN_TRAINING_MODE,
    /* +05 */ MN_RESULTS,
    /* +06 */ MN_0x6,                       ///< Unused? It is skipped in the table entirely
    /* +07 */ MN_DEBUG_MENU,
    /* +08 */ MN_CSS,
    /* +09 */ MN_SSS,
    /* +0A */ MN_0xA,                       ///< Unused? Empty in the table
    /* +0B */ MN_TOY_GALLERY,
    /* +0C */ MN_TOY_LOTTERY,
    /* +0D */ MN_TOY_COLLECTION,
    /* +0E */ MN_INTRO_NORMAL,              ///< Adventure Mode intro
    /* +0F */ MN_REGEND_TOYFALL,            ///< Trophy fall scene that happens when you win in 1p mode
    /* +10 */ MN_REGEND_CONGRATS,           ///< "REG" may refer to any 1p mode
    /* +11 */ MN_CUTSCENE_LUIGI,            ///< "Vi0102.dat" - "visual0102Scene"
    /* +12 */ MN_CUTSCENE_BRINSTAR,         ///< "Vi0401.dat" - "visual0401Scene" - "visual0401InfoScene"
    /* +13 */ MN_CUTSCENE_EXPLOSION,        ///< Planet Explosion / "Vi0402.dat" - "visual0402Scene"
    /* +14 */ MN_CUTSCENE_3KIRBYS,          ///< "Vi0501.dat" - "visual0501Scene"
    /* +15 */ MN_CUTSCENE_GIANTKIRBY,       ///< "Vi0502.dat" - "visual0502Scene"
    /* +16 */ MN_CUTSCENE_STARFOX,          ///< "Vi0601.dat" - "visual0601Scene"
    /* +17 */ MN_CUTSCENE_FZERO,            ///< "Vi0801.dat" - "visual0801Scene"
    /* +18 */ MN_CUTSCENE_METAL,            ///< Metal Mario/Luigi / "Vi1101.dat" - "visual1101Scene" - "visual1101Cam2Scene"
    /* +19 */ MN_CUTSCENE_BOWSERTOY,        ///< "Vi1201v1.dat" - "visual1201v1Scene"
    /* +1A */ MN_CUTSCENE_GIGATRANSFORM,    ///< "Vi1201v2.dat" - "visual1201v2Scene"
    /* +1B */ MN_CUTSCENE_GIGADEFEATED,     ///< "Vi1202.dat" - "visual1202Scene"
    /* +1C */ MN_MOVIE_OPENING,
    /* +1D */ MN_MOVIE_END,                 ///< 1p mode ending movie
    /* +1E */ MN_MOVIE_HOWTO,
    /* +1F */ MN_MOVIE_OMAKE15,             ///< "Special Movie"
    /* +20 */ MN_INTRO_EASY,                ///< Classic Mode splash screen
    /* +21 */ MN_INTRO_ALLSTAR,             ///< Unused?
    /* +22 */ MN_GAMEOVER,
    /* +23 */ MN_COMING_SOON,
    /* +24 */ MN_TOU,
    /* +25 */ MN_TOU_BRACKET,
    /* +26 */ MN_TOU_FINISH,
    /* +27 */ MN_PRIZE_INTERFACE,           ///< Achievement/Special Message Pop-up
    /* +28 */ MN_PROG_SCAN,
    /* +29 */ MN_APPROACH,                  ///< Challenger Approaching
    /* +2A */ MN_MEMCARD,                   ///< Memcard Prompt
    /* +2B */ MN_STAFFROLL,                 ///< Credits
    /* +2C */ MN_CAMERA_VS,
    /* +2D */ MN_COUNT
} MinorSceneKind;

typedef enum MatchOutcome {
    OUTCOME_NONE,
    OUTCOME_TIMEOUT,
    OUTCOME_ELIMINATION,
    OUTCOME_0x3,
    OUTCOME_0x4,
    OUTCOME_0x5,
    OUTCOME_0x6,
    OUTCOME_LRASTART,
    OUTCOME_RETRY,
    OUTCOME_0x9,
} MatchOutcome;

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
typedef struct ResultsData ResultsData;
typedef struct CameraVsData CameraVsData;

#endif
