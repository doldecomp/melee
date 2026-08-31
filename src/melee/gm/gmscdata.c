#include "gmscdata.h"

#include "gm_1A33.h"
#include "gm_unsplit.h"
#include "gmadventure.h"
#include "gmallstar.h"
#include "gmapproach.h"
#include "gmclassic.h"
#include "gmdebugmode.h"
#include "gmfixedcamera.h"
#include "gmgiant.h"
#include "gmhanyucss.h"
#include "gmhanyusss.h"
#include "gmhomerun.h"
#include "gmhowto.h"
#include "gminvisible.h"
#include "gmlightning.h"
#include "gmmenu.h"
#include "gmmenumode.h"
#include "gmmovieend.h"
#include "gmmultiman.h"
#include "gmomake15.h"
#include "gmopening.h"
#include "gmprogressive.h"
#include "gmregtyfall.h"
#include "gmresult.h"
#include "gmsinglebutton.h"
#include "gmslomo.h"
#include "gmstaffroll.h"
#include "gmstamina.h"
#include "gmsupersudden.h"
#include "gmtiny.h"
#include "gmtitle.h"
#include "gmtitlemode.h"
#include "gmtoulib.h"
#include "gmtoumode.h"
#include "gmtoycollection.h"
#include "gmtoygallery.h"
#include "gmtoylottery.h"
#include "gmtrainingmode.h"
#include "gmvsmelee.h"
#include "gmvsmode.h"
#include "types.h"

#include "gm/gmcameramode.h"
#include "gm/gmmenumode.h"
#include "gm/gmprogressivemode.h"
#include "gm/gmtrainingmode.h"
#include "if/ifprize.h"
#include "mn/mncharsel.h"
#include "mn/mnmain.h"
#include "mn/mnstagesel.h"
#include "ty/toy.h"
#include "ty/tydisplay.h"
#include "ty/tyfigupon.h"
#include "vi/vi0102.h"
#include "vi/vi0401.h"
#include "vi/vi0402.h"
#include "vi/vi0501.h"
#include "vi/vi0502.h"
#include "vi/vi0601.h"
#include "vi/vi0801.h"
#include "vi/vi1101.h"
#include "vi/vi1201v1.h"
#include "vi/vi1201v2.h"
#include "vi/vi1202.h"

static GameScene scenes[] = {
    {
        GS_TITLE,
        gm_Scene_Title_OnFrame,
        gm_Scene_Title_OnEnter,
        NULL,
        NULL,
    },
    {
        GS_MENU,
        mnMain_Scene_OnFrame,
        mnMain_Scene_OnEnter,
        NULL,
        NULL,
    },
    {
        GS_VS,
        gm_Scene_Vs_OnFrame,
        gm_Scene_Vs_OnEnter,
        gm_Scene_Vs_OnExit,
        NULL,
    },
    {
        GS_SUDDEN_DEATH,
        gm_Scene_Vs_OnFrame,
        gm_Scene_SuddenDeath_OnEnter,
        gm_Scene_Vs_OnExit,
        NULL,
    },
    {
        GS_TRAINING,
        gm_Scene_Training_OnFrame,
        gm_Scene_Training_OnEnter,
        gm_Scene_Vs_OnExit,
        NULL,
    },
    {
        GS_RESULTS,
        NULL,
        gm_Scene_Results_OnEnter,
        gm_Scene_Results_OnExit,
        NULL,
    },
    {
        GS_DEBUG_MENU,
        NULL,
        gm_Scene_DebugMenu_OnEnter,
        NULL,
        NULL,
    },
    {
        GS_CSS,
        mnCharSel_Scene_OnFrame,
        mnCharSel_Scene_OnEnter,
        mnCharSel_Scene_OnExit,
        NULL,
    },
    {
        GS_SSS,
        mnStageSel_Scene_OnFrame,
        mnStageSel_Scene_OnEnter,
        mnStageSel_Scene_OnExit,
        NULL,
    },
    {
        GS_UNK10,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        GS_TOY_GALLERY,
        Toy_Scene_OnFrame,
        Toy_Scene_OnEnter,
        NULL,
        NULL,
    },
    {
        GS_TOY_LOTTERY,
        tyFigupon_Scene_OnFrame,
        tyFigupon_Scene_OnEnter,
        NULL,
        NULL,
    },
    {
        GS_TOY_COLLECTION,
        tyDisplay_Scene_OnFrame,
        tyDisplay_Scene_OnEnter,
        NULL,
        NULL,
    },
    {
        GS_INTRO_NORMAL,
        gm_Scene_IntroNormal_OnFrame,
        gm_Scene_IntroNormal_OnEnter,
        gm_Scene_IntroNormal_OnLeave,
        NULL,
    },
    {
        GS_REGEND_TOYFALL,
        gm_Scene_ToyFall_OnFrame,
        gm_Scene_ToyFall_OnEnter,
        NULL,
        NULL,
    },
    {
        GS_REGEND_CONGRATS,
        gm_Scene_Congrats_OnFrame,
        gm_Scene_Congrats_OnEnter,
        NULL,
        NULL,
    },
    {
        GS_CUTSCENE_LUIGI,
        vi0102_Scene_OnFrame,
        vi0102_Scene_OnEnter,
        NULL,
        NULL,
    },
    {
        GS_CUTSCENE_BRINSTAR,
        vi0401_Scene_OnFrame,
        vi0401_Scene_OnEnter,
        NULL,
        NULL,
    },
    {
        GS_CUTSCENE_EXPLOSION,
        vi0402_Scene_OnFrame,
        vi0402_Scene_OnEnter,
        NULL,
        NULL,
    },
    {
        GS_CUTSCENE_3KIRBYS,
        vi0501_Scene_OnFrame,
        vi0501_Scene_OnEnter,
        NULL,
        NULL,
    },
    {
        GS_CUTSCENE_GIANTKIRBY,
        vi0502_Scene_OnFrame,
        vi0502_Scene_OnEnter,
        NULL,
        NULL,
    },
    {
        GS_CUTSCENE_STARFOX,
        vi0601_Scene_OnFrame,
        vi0601_Scene_OnEnter,
        NULL,
        NULL,
    },
    {
        GS_CUTSCENE_FZERO,
        vi0801_Scene_OnFrame,
        vi0801_Scene_OnEnter,
        NULL,
        NULL,
    },
    {
        GS_CUTSCENE_METAL,
        vi1101_Scene_OnFrame,
        vi1101_Scene_OnEnter,
        NULL,
        NULL,
    },
    {
        GS_CUTSCENE_BOWSERTOY,
        vi1201v1_Scene_OnFrame,
        vi1201v1_Scene_OnEnter,
        NULL,
        NULL,
    },
    {
        GS_CUTSCENE_GIGATRANSFORM,
        vi1201v2_Scene_OnFrame,
        vi1201v2_Scene_OnEnter,
        NULL,
        NULL,
    },
    {
        GS_CUTSCENE_GIGADEFEATED,
        vi1202_Scene_OnFrame,
        vi1202_Scene_OnEnter,
        NULL,
        NULL,
    },
    {
        GS_MOVIE_OPENING,
        gm_Scene_Opening_OnFrame,
        gm_Scene_Opening_OnEnter,
        NULL,
        NULL,
    },
    {
        GS_MOVIE_END,
        gm_Scene_MovieEnd_OnFrame,
        gm_Scene_MovieEnd_OnEnter,
        NULL,
        NULL,
    },
    {
        GS_MOVIE_HOWTO,
        gm_Scene_HowTo_OnFrame,
        gm_Scene_HowTo_OnEnter,
        NULL,
        NULL,
    },
    {
        GS_MOVIE_OMAKE15,
        gm_Scene_Omake15_OnFrame,
        gm_Scene_Omake15_OnEnter,
        NULL,
        NULL,
    },
    {
        GS_INTRO_EASY,
        gm_Scene_IntroEasy_OnFrame,
        gm_Scene_IntroEasy_OnEnter,
        NULL,
        NULL,
    },
    {
        GS_INTRO_ALLSTAR,
        gm_Scene_IntroAllstar_OnFrame,
        gm_Scene_IntroAllstar_OnEnter,
        NULL,
        NULL,
    },
    {
        GS_GAMEOVER,
        NULL,
        gm_Scene_GOver_OnEnter,
        gm_Scene_GOver_OnExit,
        NULL,
    },
    {
        GS_COMING_SOON,
        NULL,
        gm_Scene_ComingSoon_OnEnter,
        gm_Scene_ComingSoon_OnExit,
        NULL,
    },
    {
        GS_TOU_SETUP,
        gm_Scene_TouSetup_OnFrame,
        gm_Scene_TouSetup_OnEnter,
        gm_Scene_TouSetup_OnExit,
        NULL,
    },
    {
        GS_TOU_BRACKET,
        gm_Scene_TouBracket_OnFrame,
        gm_Scene_TouBracket_OnEnter,
        gm_Scene_TouBracket_OnExit,
        NULL,
    },
    {
        GS_TOU_ALT,
        gm_Scene_TouAlt_OnFrame,
        gm_Scene_TouAlt_OnEnter,
        gm_Scene_TouAlt_OnExit,
        NULL,
    },
    {
        GS_PRIZE_INTERFACE,
        NULL,
        ifPrize_Scene_OnEnter,
        ifPrize_Scene_OnExit,
        NULL,
    },
    {
        GS_PROG_SCAN,
        gm_Scene_ProgScan_OnFrame,
        gm_Scene_ProgScan_OnEnter,
        gm_Scene_ProgScan_OnExit,
        NULL,
    },
    {
        GS_APPROACH,
        gm_Scene_Approach_OnFrame,
        gm_Scene_Approach_OnEnter,
        gm_Scene_Approach_OnExit,
        NULL,
    },
    {
        GS_MEMCARD,
        gm_Scene_MemCard_OnFrame,
        gm_Scene_MemCard_OnEnter,
        gm_Scene_MemCard_OnExit,
        NULL,
    },
    {
        GS_STAFFROLL,
        gm_Scene_StaffRoll_OnFrame,
        gm_Scene_StaffRoll_OnEnter,
        gm_Scene_StaffRoll_OnExit,
        NULL,
    },
    {
        GS_CAMERA_VS,
        gm_Scene_CameraVs_OnFrame,
        gm_Scene_CameraVs_OnEnter,
        gm_Scene_CameraVs_OnExit,
        NULL,
    },
    {
        GS_COUNT,
        NULL,
        NULL,
        NULL,
        NULL,
    },
};

static GameMode modes[] = {
    {
        true,
        GM_TITLE,
        NULL,
        NULL,
        NULL,
        gm_Mode_Title_States,
    },
    {
        false,
        GM_VS,
        gm_Mode_Vs_OnLoad,
        gm_Mode_Vs_OnUnload,
        gm_Mode_Vs_OnInit,
        gm_Mode_Vs_States,
    },
    {
        true,
        GM_CLASSIC,
        gm_Mode_Classic_OnLoad,
        NULL,
        gm_Mode_Classic_OnInit,
        gm_Mode_Classic_States,
    },
    {
        false,
        GM_ADVENTURE,
        gm_Mode_Adventure_OnLoad,
        NULL,
        gm_Mode_Adventure_OnInit,
        gm_Mode_Adventure_States,
    },
    {
        true,
        GM_ALLSTAR,
        gm_Mode_AllStar_OnLoad,
        NULL,
        gm_Mode_AllStar_OnInit,
        gm_Mode_AllStar_States,
    },
    {
        false,
        GM_DEBUG,
        NULL,
        NULL,
        NULL,
        gm_Mode_Debug_States,
    },
    {
        false,
        GM_DEBUG_SOUND_TEST,
        NULL,
        NULL,
        NULL,
        gm_Mode_DebugMenu_States,
    },
    {
        false,
        GM_HANYU_CSS,
        NULL,
        NULL,
        NULL,
        gm_Mode_HanyuCss_States,
    },
    {
        false,
        GM_HANYU_SSS,
        NULL,
        NULL,
        NULL,
        gm_Mode_HanyuSss_States,
    },
    {
        true,
        GM_CAMERA_MODE,
        NULL,
        NULL,
        gm_Mode_Camera_OnInit,
        gm_Mode_Camera_States,
    },
    {
        false,
        GM_TOY_GALLERY,
        NULL,
        NULL,
        Toy_Mode_OnInit,
        gm_Mode_ToyGallery_States,
    },
    {
        false,
        GM_TOY_LOTTERY,
        NULL,
        NULL,
        NULL,
        gm_Mode_ToyLottery_States,
    },
    {
        false,
        GM_TOY_COLLECTION,
        NULL,
        NULL,
        NULL,
        gm_Mode_ToyCollection_States,
    },
    {
        false,
        GM_DEBUG_VS,
        NULL,
        NULL,
        NULL,
        gm_Mode_DebugVs_States,
    },
    {
        true,
        GM_TARGET_TEST,
        gm_Mode_TargetTest_OnLoad,
        NULL,
        gm_Mode_TargetTest_OnInit,
        gm_Mode_TargetTest_States,
    },
    {
        false,
        GM_SUPER_SUDDEN_DEATH_VS,
        gm_Mode_SuperSuddenDeath_OnLoad,
        NULL,
        gm_Mode_SuperSuddenDeath_OnInit,
        gm_Mode_SuperSuddenDeath_States,
    },
    {
        false,
        GM_INVISIBLE_VS,
        gm_Mode_InvisibleVs_OnLoad,
        NULL,
        gm_Mode_InvisibleVs_OnInit,
        gm_Mode_InvisibleVs_States,
    },
    {
        false,
        GM_SLOMO_VS,
        gm_Mode_SlowMo_OnLoad,
        NULL,
        gm_Mode_SlowMo_OnInit,
        gm_Mode_SlowMo_States,
    },
    {
        false,
        GM_LIGHTNING_VS,
        gm_Mode_LightningVs_OnLoad,
        NULL,
        gm_Mode_LightningVs_OnInit,
        gm_Mode_LightningVs_States,
    },
    {
        false,
        GM_CHALLENGER_APPROACH,
        gm_Mode_ChallengerApproach_OnLoad,
        NULL,
        NULL,
        gm_Mode_ChallengerApproach_States,
    },
    {
        true,
        GM_MENU,
        NULL,
        NULL,
        NULL,
        gm_Mode_Menu_States,
    },
    {
        false,
        GM_CLASSIC_GOVER,
        gm_Mode_ClassicGOver_OnLoad,
        NULL,
        NULL,
        gm_Mode_GOver_States,
    },
    {
        false,
        GM_ADVENTURE_GOVER,
        gm_Mode_AdventureGOver_OnLoad,
        NULL,
        NULL,
        gm_Mode_GOver_States,
    },
    {
        false,
        GM_ALLSTAR_GOVER,
        gm_Mode_AllstarGOver_OnLoad,
        NULL,
        NULL,
        gm_Mode_GOver_States,
    },
    {
        true,
        GM_OPENING_MV,
        gm_Mode_Opening_OnLoad,
        NULL,
        NULL,
        gm_Mode_Opening_States,
    },
    {
        false,
        GM_DEBUG_CUTSCENE,
        NULL,
        NULL,
        NULL,
        gm_Mode_DebugCutscene_States,
    },
    {
        false,
        GM_DEBUG_GOVER,
        NULL,
        NULL,
        NULL,
        gm_Mode_DebugGOver_States,
    },
    {
        true,
        GM_TOURNAMENT,
        NULL,
        NULL,
        NULL,
        gm_Mode_Tournament_States,
    },
    {
        true,
        GM_TRAINING,
        gm_Mode_Training_OnLoad,
        NULL,
        gm_Mode_Training_OnInit,
        gm_Mode_Training_States,
    },
    {
        false,
        GM_TINY_VS,
        gm_Mode_TinyVs_OnLoad,
        NULL,
        gm_Mode_TinyVs_OnInit,
        gm_Mode_TinyVs_States,
    },
    {
        false,
        GM_GIANT_VS,
        gm_Mode_GiantVs_OnLoad,
        NULL,
        gm_Mode_GiantVs_OnInit,
        gm_Mode_GiantVs_States,
    },
    {
        true,
        GM_STAMINA_VS,
        gm_Mode_StaminaVs_OnLoad,
        NULL,
        gm_Mode_StaminaVs_OnInit,
        gm_Mode_StaminaVs_States,
    },
    {
        true,
        GM_HOME_RUN_CONTEST,
        gm_Mode_Homerun_OnLoad,
        NULL,
        gm_Mode_Homerun_OnInit,
        gm_Mode_Homerun_States,
    },
    {
        true,
        GM_10MAN_VS,
        gm_Mode_10ManVs_OnLoad,
        NULL,
        gm_Mode_10ManVs_OnInit,
        gm_Mode_10ManVs_States,
    },
    {
        true,
        GM_100MAN_VS,
        gm_Mode_10ManVs_OnLoad,
        NULL,
        gm_Mode_10ManVs_OnInit,
        gm_Mode_100ManVs_States,
    },
    {
        true,
        GM_3MIN_VS,
        gm_Mode_10ManVs_OnLoad,
        NULL,
        gm_Mode_10ManVs_OnInit,
        gm_Mode_3Min_States,
    },
    {
        true,
        GM_15MIN_VS,
        gm_Mode_10ManVs_OnLoad,
        NULL,
        gm_Mode_10ManVs_OnInit,
        gm_Mode_15Min_States,
    },
    {
        true,
        GM_ENDLESS_VS,
        gm_Mode_10ManVs_OnLoad,
        NULL,
        gm_Mode_10ManVs_OnInit,
        gm_Mode_EndlessVs_States,
    },
    {
        true,
        GM_CRUEL_VS,
        gm_Mode_10ManVs_OnLoad,
        NULL,
        gm_Mode_10ManVs_OnInit,
        gm_Mode_CruelVs_States,
    },
    {
        false,
        GM_PROGRESSIVE_SCAN,
        NULL,
        NULL,
        NULL,
        gm_Mode_ProgScan_States,
    },
    {
        true,
        GM_BOOT,
        NULL,
        NULL,
        NULL,
        gm_Mode_Boot_States,
    },
    {
        true,
        GM_MEMCARD,
        NULL,
        NULL,
        NULL,
        gm_Mode_MemCard_States,
    },
    {
        false,
        GM_CAMERA_VS,
        gm_Mode_CameraVs_OnLoad,
        NULL,
        gm_Mode_CameraVs_OnInit,
        gm_Mode_CameraVs_States,
    },
    {
        true,
        GM_EVENT,
        gm_Mode_Event_OnLoad,
        gm_Mode_Event_OnUnload,
        gm_Mode_Event_OnInit,
        gm_Mode_Event_States,
    },
    {
        false,
        GM_SINGLE_BUTTON_VS,
        gm_Mode_SingleButtonVs_OnLoad,
        NULL,
        gm_Mode_SingleButtonVs_OnInit,
        gm_Mode_SingleButtonVs_States,
    },
    {
        false,
        GM_COUNT,
        NULL,
        NULL,
        NULL,
        NULL,
    },
};

GameScene* gm_GetAllGameScenes(void)
{
    return scenes;
}

GameMode* gm_GetAllGameModes(void)
{
    return modes;
}
