#ifndef MELEE_GM_FORWARD_H
#define MELEE_GM_FORWARD_H

#include <platform.h>

typedef enum GameModeKind {
    /* 00 */ GM_TITLE,
    /* 01 */ GM_MENU,
    /* 02 */ GM_VS,
    /* 03 */ GM_CLASSIC,
    /* 04 */ GM_ADVENTURE,
    /* 05 */ GM_ALLSTAR,
    /* 06 */ GM_DEBUG,
    /* 07 */ GM_DEBUG_SOUND_TEST,
    /* 08 */ GM_HANYU_CSS,
    /* 09 */ GM_HANYU_SSS,
    /* 0A */ GM_CAMERA_MODE,
    /* 0B */ GM_TOY_GALLERY,
    /* 0C */ GM_TOY_LOTTERY,
    /* 0D */ GM_TOY_COLLECTION,
    /* 0E */ GM_DEBUG_VS,
    /* 0F */ GM_TARGET_TEST,
    /* 10 */ GM_SUPER_SUDDEN_DEATH_VS,
    /* 11 */ GM_INVISIBLE_VS,
    /* 12 */ GM_SLOMO_VS,
    /* 13 */ GM_LIGHTNING_VS,
    /* 14 */ GM_CHALLENGER_APPROACH,
    /* 15 */ GM_CLASSIC_GOVER,
    /* 16 */ GM_ADVENTURE_GOVER,
    /* 17 */ GM_ALLSTAR_GOVER,
    /* 18 */ GM_OPENING_MV,
    /* 19 */ GM_DEBUG_CUTSCENE,
    /* 1A */ GM_DEBUG_GOVER, ///< trophy fall and 'congrats'
    /* 1B */ GM_TOURNAMENT,
    /* 1C */ GM_TRAINING,
    /* 1D */ GM_TINY_VS,
    /* 1E */ GM_GIANT_VS,
    /* 1F */ GM_STAMINA_VS,
    /* 20 */ GM_HOME_RUN_CONTEST,
    /* 21 */ GM_10MAN_VS,
    /* 22 */ GM_100MAN_VS,
    /* 23 */ GM_3MIN_VS,
    /* 24 */ GM_15MIN_VS,
    /* 25 */ GM_ENDLESS_VS,
    /* 26 */ GM_CRUEL_VS,
    /* 27 */ GM_PROGRESSIVE_SCAN,
    /* 28 */ GM_BOOT,
    /* 29 */ GM_MEMCARD,
    /* 2A */ GM_FIXED_CAMERA_VS,
    /* 2B */ GM_EVENT,
    /* 2C */ GM_SINGLE_BUTTON_VS,
    /* 2D */ GM_COUNT,
} GameModeKind;

typedef enum GameSceneKind {
    /* +00 */ GS_TITLE,
    /* +01 */ GS_MENU,
    /* +02 */ GS_VS,
    /* +03 */ GS_SUDDEN_DEATH,
    /* +04 */ GS_TRAINING_MODE,
    /* +05 */ GS_RESULTS,
    /* +06 */ GS_0x6, ///< Unused? It is skipped in the table entirely
    /* +07 */ GS_DEBUG_MENU,
    /* +08 */ GS_CSS,
    /* +09 */ GS_SSS,
    /* +0A */ GS_0xA, ///< Unused? Empty in the table
    /* +0B */ GS_TOY_GALLERY,
    /* +0C */ GS_TOY_LOTTERY,
    /* +0D */ GS_TOY_COLLECTION,
    /* +0E */ GS_INTRO_NORMAL,    ///< Adventure Mode intro
    /* +0F */ GS_REGEND_TOYFALL,  ///< Trophy fall scene that happens when you
                                  ///< win in 1p mode
    /* +10 */ GS_REGEND_CONGRATS, ///< "REG" may refer to any 1p mode
    /* +11 */ GS_CUTSCENE_LUIGI,  ///< "Vi0102.dat" - "visual0102Scene"
    /* +12 */ GS_CUTSCENE_BRINSTAR,   ///< "Vi0401.dat" - "visual0401Scene" -
                                      ///< "visual0401InfoScene"
    /* +13 */ GS_CUTSCENE_EXPLOSION,  ///< Planet Explosion / "Vi0402.dat" -
                                      ///< "visual0402Scene"
    /* +14 */ GS_CUTSCENE_3KIRBYS,    ///< "Vi0501.dat" - "visual0501Scene"
    /* +15 */ GS_CUTSCENE_GIANTKIRBY, ///< "Vi0502.dat" - "visual0502Scene"
    /* +16 */ GS_CUTSCENE_STARFOX,    ///< "Vi0601.dat" - "visual0601Scene"
    /* +17 */ GS_CUTSCENE_FZERO,      ///< "Vi0801.dat" - "visual0801Scene"
    /* +18 */ GS_CUTSCENE_METAL,      ///< Metal Mario/Luigi / "Vi1101.dat" -
                                 ///< "visual1101Scene" - "visual1101Cam2Scene"
    /* +19 */ GS_CUTSCENE_BOWSERTOY, ///< "Vi1201v1.dat" - "visual1201v1Scene"
    /* +1A */ GS_CUTSCENE_GIGATRANSFORM, ///< "Vi1201v2.dat" -
                                         ///< "visual1201v2Scene"
    /* +1B */ GS_CUTSCENE_GIGADEFEATED,  ///< "Vi1202.dat" - "visual1202Scene"
    /* +1C */ GS_MOVIE_OPENING,
    /* +1D */ GS_MOVIE_END, ///< 1p mode ending movie
    /* +1E */ GS_MOVIE_HOWTO,
    /* +1F */ GS_MOVIE_OMAKE15, ///< "Special Movie"
    /* +20 */ GS_INTRO_EASY,    ///< Classic Mode splash screen
    /* +21 */ GS_INTRO_ALLSTAR, ///< Unused?
    /* +22 */ GS_GAMEOVER,
    /* +23 */ GS_COMING_SOON,
    /* +24 */ GS_TOU_SETUP,       ///< Selections and settings
    /* +25 */ GS_TOU_BRACKET,     ///< Tournament "Match Type"
    /* +26 */ GS_TOU_ALT,         ///< Winner Out/Loser Out "Match Type"
    /* +27 */ GS_PRIZE_INTERFACE, ///< Achievement/Special Message Pop-up
    /* +28 */ GS_PROG_SCAN,
    /* +29 */ GS_APPROACH,  ///< Challenger Approaching
    /* +2A */ GS_MEMCARD,   ///< Memcard Prompt
    /* +2B */ GS_STAFFROLL, ///< Credits
    /* +2C */ GS_CAMERA_VS,
    /* +2D */ GS_COUNT
} GameSceneKind;

typedef enum MatchOutcome {
    /* 0 */ OUTCOME_NONE, ///< Match in progress, or no match played since boot
    /* 1 */ OUTCOME_TIMEOUT,
    /* 2 */ OUTCOME_ELIMINATION,
    /* 3 */ OUTCOME_TEAM_ELIMINATION, ///< Seen when a team battle ends
                                      ///< Also seen when player beats any 1p mode stage that is a single non-horde,
                                      ///< non-event-match battle
    /* 4 */ OUTCOME_1P_GAME_OVER,
    /* 5 */ OUTCOME_UNK_1P_HORDE_BATTLE_VICTORY, ///< Applies to any victory in story mode against a horde of (usually weak) enemies.
    /* 6 */ OUTCOME_UNK_1P_BONUS_STAGE_END,  ///< Applies to all stages that aren't just a single match. Target Test,
                                             ///< Undergrond Maze, Grand Prix, Race to the finish, etc;
    /* 7 */ OUTCOME_NO_CONTEST,
    /* 8 */ OUTCOME_RETRY,
    /* 9 */ OUTCOME_TERMINATED,
} MatchOutcome;

struct gm_801677C0_s;
struct lbl_8046B488_t;
typedef struct CameraVsData CameraVsData;
typedef struct datetime datetime;
typedef struct DebugGameOverData DebugGameOverData;
typedef struct GameMode GameMode;
typedef struct GameRules GameRules;
typedef struct GameScene GameScene;
typedef struct GameSceneHandler GameSceneHandler;
typedef struct GameSceneInfo GameSceneInfo;
typedef struct gm_8016A92C_arg0_t gm_8016A92C_arg0_t;
typedef struct gm_8017DB6C_arg0_t gm_8017DB6C_arg0_t;
typedef struct gmm_x0_528_t gmm_x0_528_t;
typedef struct lbl_8046B6A0_24C_t lbl_8046B6A0_24C_t;
typedef struct lbl_8046B6A0_t lbl_8046B6A0_t;
typedef struct lbl_8046DBD8_t lbl_8046DBD8_t;
typedef struct MatchEnd MatchEnd;
typedef struct MatchExitInfo MatchExitInfo;
typedef struct MatchPlayerData MatchPlayerData;
typedef struct MenuEnterData MenuEnterData;
typedef struct MenuExitData MenuExitData;
typedef struct Placeholder_8016AE38_flags Placeholder_8016AE38_flags;
typedef struct Placeholder_8016AE38_flags_2 Placeholder_8016AE38_flags_2;
typedef struct Placeholder_8016AE50_ret_val Placeholder_8016AE50_ret_val;
typedef struct ResultsData ResultsData;
typedef struct ResultsMatchInfo ResultsMatchInfo;
typedef struct TmAnimTimers TmAnimTimers;
typedef struct TmData TmData;
typedef struct TmVsData TmVsData;
typedef struct Unk1PData Unk1PData;
typedef struct Unk1PData_x24 Unk1PData_x24;
typedef struct UnkAdventureData UnkAdventureData;
typedef struct UnkAllstarData UnkAllstarData;
typedef struct UnkMultimanData UnkMultimanData;
typedef struct VsApproachData VsApproachData;

typedef bool (*GmRouteCallback)(int);

#endif
