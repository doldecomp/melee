#include "gmscdata.h"

#include "gm/forward.h"

#include "if/ifprize.h"

#include <melee/gm/gm_unsplit.h>
#include <melee/gm/gmadventure.h>
#include <melee/gm/gmallstar.h>
#include <melee/gm/gmapproach.h>
#include <melee/gm/gmcamera.h>
#include <melee/gm/gmclassic.h>
#include <melee/gm/gmfixedcamera.h>
#include <melee/gm/gmgiant.h>
#include <melee/gm/gmhomerun.h>
#include <melee/gm/gmhowto.h>
#include <melee/gm/gminvisible.h>
#include <melee/gm/gmlightning.h>
#include <melee/gm/gmmenu.h>
#include <melee/gm/gmmovieend.h>
#include <melee/gm/gmmultiman.h>
#include <melee/gm/gmomake15.h>
#include <melee/gm/gmopening.h>
#include <melee/gm/gmprogressive.h>
#include <melee/gm/gmregtyfall.h>
#include <melee/gm/gmresult.h>
#include <melee/gm/gmsinglebutton.h>
#include <melee/gm/gmslomo.h>
#include <melee/gm/gmstaffroll.h>
#include <melee/gm/gmstamina.h>
#include <melee/gm/gmsupersudden.h>
#include <melee/gm/gmtiny.h>
#include <melee/gm/gmtitle.h>
#include <melee/gm/gmtou.h>
#include <melee/gm/gmvsmelee.h>
#include <melee/gm/types.h>
#include <melee/mn/mncharsel.h>
#include <melee/mn/mnmain.h>
#include <melee/mn/mnstagesel.h>
#include <melee/ty/toy.h>
#include <melee/ty/tydisplay.h>
#include <melee/ty/tyfigupon.h>
#include <melee/vi/vi0102.h>
#include <melee/vi/vi0401.h>
#include <melee/vi/vi0402.h>
#include <melee/vi/vi0501.h>
#include <melee/vi/vi0502.h>
#include <melee/vi/vi0601.h>
#include <melee/vi/vi0801.h>
#include <melee/vi/vi1101.h>
#include <melee/vi/vi1201v1.h>
#include <melee/vi/vi1201v2.h>
#include <melee/vi/vi1202.h>

static GameSceneHandler gm_803DA920[] = {
    {
        GS_TITLE,
        gmTitle_801A1C18_OnFrame,
        gmTitle_801A1E20_OnEnter,
        NULL,
        NULL,
    },
    {
        GS_MENU,
        mn_8022DD38_OnFrame,
        (void*) mn_8022DDA8_OnEnter,
        NULL,
        NULL,
    },
    {
        GS_VS,
        gm_8016D800,
        gm_8016E934_OnEnter,
        gm_8016E9C8,
        NULL,
    },
    {
        GS_SUDDEN_DEATH,
        gm_8016D800,
        gm_8016EBC0_OnEnter,
        gm_8016E9C8,
        NULL,
    },
    {
        GS_TRAINING_MODE,
        gm_8016D32C_OnFrame,
        gm_8016EC28_OnEnter,
        gm_8016E9C8,
        NULL,
    },
    {
        GS_RESULTS,
        NULL,
        gm_80177368_OnEnter,
        gm_80177704_OnLeave,
        NULL,
    },
    {
        GS_DEBUG_MENU,
        NULL,
        gm_801A632C_OnEnter,
        NULL,
        NULL,
    },
    {
        GS_CSS,
        mnCharSel_802669F4_OnFrame,
        mnCharSel_8026688C_OnEnter,
        mnCharSel_80266D70_OnLeave,
        NULL,
    },
    {
        GS_SSS,
        mnStageSel_8025B850_OnFrame,
        mnStageSel_8025A998_OnEnter,
        mnStageSel_8025BB5C_OnLeave,
        NULL,
    },
    {
        GS_0xA,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        GS_TOY_GALLERY,
        un_80312018_OnFrame,
        un_80311AB0_OnEnter,
        NULL,
        NULL,
    },
    {
        GS_TOY_LOTTERY,
        un_803182D4_OnFrame,
        un_80317D80_OnEnter,
        NULL,
        NULL,
    },
    {
        GS_TOY_COLLECTION,
        un_8031B9A4_OnFrame,
        un_8031B460_OnEnter,
        NULL,
        NULL,
    },
    {
        GS_INTRO_NORMAL,
        gm_8018838C_OnFrame,
        gm_80187F48_OnEnter,
        gm_80188364_OnLeave,
        NULL,
    },
    {
        GS_REGEND_TOYFALL,
        gm_801A79D4_OnFrame,
        gm_801A7070_OnEnter,
        NULL,
        NULL,
    },
    {
        GS_REGEND_CONGRATS,
        gm_801A9D0C_OnFrame,
        gm_801A9B30_OnEnter,
        NULL,
        NULL,
    },
    {
        GS_CUTSCENE_LUIGI,
        vi0102_8031D000_OnFrame,
        vi0102_Initialize_OnEnter,
        NULL,
        NULL,
    },
    {
        GS_CUTSCENE_BRINSTAR,
        un_8031D698_OnFrame,
        un_8031D288_OnEnter,
        NULL,
        NULL,
    },
    {
        GS_CUTSCENE_EXPLOSION,
        vi_8031D9C4_OnFrame,
        un_8031D858_OnEnter,
        NULL,
        NULL,
    },
    {
        GS_CUTSCENE_3KIRBYS,
        vi_8031E0F0_OnFrame,
        un_8031DE58_OnEnter,
        NULL,
        NULL,
    },
    {
        GS_CUTSCENE_GIANTKIRBY,
        vi_8031E6CC_OnFrame,
        un_8031E444_OnEnter,
        NULL,
        NULL,
    },
    {
        GS_CUTSCENE_STARFOX,
        vi_8031ED50_OnFrame,
        un_8031EBBC_OnEnter,
        NULL,
        NULL,
    },
    {
        GS_CUTSCENE_FZERO,
        vi0801_OnFrame,
        vi0801_OnEnter,
        NULL,
        NULL,
    },
    {
        GS_CUTSCENE_METAL,
        un_8031F960_OnFrame,
        un_8031F714_OnEnter,
        NULL,
        NULL,
    },
    {
        GS_CUTSCENE_BOWSERTOY,
        un_80320490_OnFrame,
        un_8031FD18_OnEnter,
        NULL,
        NULL,
    },
    {
        GS_CUTSCENE_GIGATRANSFORM,
        un_803210EC_OnFrame,
        un_80320A40_OnEnter,
        NULL,
        NULL,
    },
    {
        GS_CUTSCENE_GIGADEFEATED,
        vi1202_OnFrame,
        vi1202_OnEnter,
        NULL,
        NULL,
    },
    {
        GS_MOVIE_OPENING,
        gm_801AA28C_OnFrame,
        gm_801AA110_OnEnter,
        NULL,
        NULL,
    },
    {
        GS_MOVIE_END,
        gm_801A64A8_OnFrame,
        gm_801A637C_OnEnter,
        NULL,
        NULL,
    },
    {
        GS_MOVIE_HOWTO,
        gm_801ACD8C_OnFrame,
        gm_801ACCA0_OnEnter,
        NULL,
        NULL,
    },
    {
        GS_MOVIE_OMAKE15,
        gm_801ACF8C_OnFrame,
        gm_801ACE94_OnEnter,
        NULL,
        NULL,
    },
    {
        GS_INTRO_EASY,
        gm_80186DFC_OnFrame,
        gm_80186E30_OnEnter,
        NULL,
        NULL,
    },
    {
        GS_INTRO_ALLSTAR,
        gm_8018776C_OnFrame,
        gm_801877A8_OnEnter,
        NULL,
        NULL,
    },
    {
        GS_GAMEOVER,
        NULL,
        gm_801A0A10_OnEnter,
        gm_801A0B18_OnLeave,
        NULL,
    },
    {
        GS_COMING_SOON,
        NULL,
        gm_801A0C6C_OnEnter,
        gm_801A0E0C_OnLeave,
        NULL,
    },
    {
        GS_TOU_SETUP,
        gm_8019628C_OnFrame,
        gm_801963B4_OnEnter,
        gm_801964A4_OnLeave,
        NULL,
    },
    {
        GS_TOU_BRACKET,
        gm_8019B2DC_OnFrame,
        gm_8019B8C4_OnEnter,
        gm_8019B9C8_OnLeave,
        NULL,
    },
    {
        GS_TOU_ALT,
        gm_8019DF8C_OnFrame,
        gm_8019ECAC_OnEnter,
        gm_8019EE54_OnLeave,
        NULL,
    },
    {
        GS_PRIZE_INTERFACE,
        NULL,
        un_802FEBE0_OnEnter,
        un_802FED10_OnLeave,
        NULL,
    },
    {
        GS_PROG_SCAN,
        gm_801AD620_OnFrame,
        gm_801AD874_OnEnter,
        gm_801AD8EC_OnLeave,
        NULL,
    },
    {
        GS_APPROACH,
        gm_801ADC88_OnFrame,
        gm_801ADCE4_OnEnter,
        gm_801ADDA8_OnLeave,
        NULL,
    },
    {
        GS_MEMCARD,
        gm_801AF568_OnFrame,
        (void*) gm_801B0264_OnEnter,
        (void*) gm_801B0304_OnLeave,
        NULL,
    },
    {
        GS_STAFFROLL,
        gm_801AA7C4_OnFrame,
        gm_801AC6D8_OnEnter,
        gm_801ACC90_OnLeave,
        NULL,
    },
    {
        GS_CAMERA_VS,
        gmCamera_801A34FC_OnFrame,
        gmCamera_801A3634_OnEnter,
        gmCamera_801A367C_OnLeave,
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

extern GameScene gm_803DD6A0_Scenes[], gm_803DD6D0_Scenes[],
    gm_803DD888_Scenes[], gm_803DD8B8_Scenes[],
    gm_803DD9A0_Scenes[], gm_803DDA78_Scenes[],
    gm_803DDAC0_Scenes[], gm_803DDB80_Scenes[],
    gm_803DDBE0_Scenes[], gm_803DDC58_Scenes[],
    gm_803DE1B8_Scenes[], gm_803DE930_Scenes[],
    gm_803DECB8_Scenes[], gm_803DED00_Scenes[],
    gm_803DED48_Scenes[], gm_803DED90_Scenes[],
    gm_803DEDD8_Scenes[], gm_803DEE20_Scenes[],
    gm_803DEE68_Scenes[], gm_803DEEB0_Scenes[],
    gm_803DEF88_Scenes[], gm_803DF060_Scenes[],
    gm_803DF138_Scenes[], gm_803DF198_Scenes[],
    gm_803DF1E0_Scenes[], gm_803DF2B8_Scenes[],
    gm_803DF390_Scenes[], gm_803DF468_Scenes[],
    gm_803DF540_Scenes[], gm_803DF618_Scenes[],
    gm_803DFA18_Scenes[], gm_803DFA48_Scenes[],
    gm_803DFA78_Scenes[], gm_803DFAA8_Scenes[],
    gm_803DFAD8_Scenes[], gm_803DFB08[], gm_803DFB80_Scenes[],
    gm_803DFBC8_Scenes[], gm_803DFC70_Scenes[],
    gm_803DFDA8_Scenes[], gm_803DFDD8_Scenes[],
    gm_803DFE18_Scenes[], gm_803DFE48_Scenes[];

GameMode gm_803DACA4[] = {
    {
        1,
        GM_TITLE,
        NULL,
        NULL,
        NULL,
        gm_803DD6A0_Scenes,
    },
    {
        0,
        GM_VS,
        gm_801A55EC_OnLoad,
        gm_801A5614_OnUnload,
        gm_801A5598_OnInit,
        gm_803DD9A0_Scenes,
    },
    {
        1,
        GM_CLASSIC,
        gmClassic_OnLoad,
        NULL,
        gmClassic_OnInit,
        gm_803DDC58_Scenes,
    },
    {
        0,
        GM_ADVENTURE,
        gm_801B5214_OnLoad,
        NULL,
        gm_801B51CC_OnInit,
        gm_803DE1B8_Scenes,
    },
    {
        1,
        GM_ALLSTAR,
        gm_801B60A4_OnLoad,
        NULL,
        gm_801B62D8_OnInit,
        gm_803DE930_Scenes,
    },
    {
        0,
        GM_DEBUG,
        NULL,
        NULL,
        NULL,
        gm_803DD6D0_Scenes,
    },
    {
        0,
        GM_DEBUG_SOUND_TEST,
        NULL,
        NULL,
        NULL,
        gm_803DD888_Scenes,
    },
    {
        0,
        GM_HANYU_CSS,
        NULL,
        NULL,
        NULL,
        gm_803DFAA8_Scenes,
    },
    {
        0,
        GM_HANYU_SSS,
        NULL,
        NULL,
        NULL,
        gm_803DFAD8_Scenes,
    },
    {
        0x01,
        GM_CAMERA_MODE,
        NULL,
        NULL,
        gm_801B2B7C_OnInit,
        gm_803DDBE0_Scenes,
    },
    {
        0,
        GM_TOY_GALLERY,
        NULL,
        NULL,
        un_803122D0_OnInit,
        gm_803DFA18_Scenes,
    },
    {
        0,
        GM_TOY_LOTTERY,
        NULL,
        NULL,
        NULL,
        gm_803DFA48_Scenes,
    },
    {
        0,
        GM_TOY_COLLECTION,
        NULL,
        NULL,
        NULL,
        gm_803DFA78_Scenes,
    },
    {
        0,
        GM_DEBUG_VS,
        NULL,
        NULL,
        NULL,
        gm_803DDA78_Scenes,
    },
    {
        1,
        GM_TARGET_TEST,
        gm_801B6808_OnLoad,
        NULL,
        gm_801B67E8_OnInit,
        gm_803DECB8_Scenes,
    },
    {
        0,
        GM_SUPER_SUDDEN_DEATH_VS,
        gm_801B8D88_OnLoad,
        NULL,
        gm_801B8D60_OnInit,
        gm_803DEEB0_Scenes,
    },
    {
        0,
        GM_INVISIBLE_VS,
        gm_801BA4EC_OnLoad,
        NULL,
        gm_801BA4C4_OnInit,
        gm_803DF390_Scenes,
    },
    {
        0,
        GM_SLOMO_VS,
        gm_801BA6E4_OnLoad,
        NULL,
        gm_801BA6BC_OnInit,
        gm_803DF468_Scenes,
    },
    {
        0,
        GM_LIGHTNING_VS,
        gm_801BA8DC_OnLoad,
        NULL,
        gm_801BA8B4_OnInit,
        gm_803DF540_Scenes,
    },
    {
        0,
        GM_CHALLENGER_APPROACH,
        gm_801737E8_OnLoad,
        NULL,
        NULL,
        gm_803DFE48_Scenes,
    },
    {
        1,
        GM_MENU,
        NULL,
        NULL,
        NULL,
        gm_803DD8B8_Scenes,
    },
    {
        0,
        GM_CLASSIC_GOVER,
        gm_801A50B8_OnLoad,
        NULL,
        NULL,
        gm_803DFB08,
    },
    {
        0,
        GM_ADVENTURE_GOVER,
        gm_801A5130_OnLoad,
        NULL,
        NULL,
        gm_803DFB08,
    },
    {
        0,
        GM_ALLSTAR_GOVER,
        gm_801A51A8_OnLoad,
        NULL,
        NULL,
        gm_803DFB08,
    },
    {
        1,
        GM_OPENING_MV,
        gm_801A5220_OnLoad,
        NULL,
        NULL,
        gm_803DFBC8_Scenes,
    },
    {
        0,
        GM_DEBUG_CUTSCENE,
        NULL,
        NULL,
        NULL,
        gm_803DFC70_Scenes,
    },
    {
        0,
        GM_DEBUG_GOVER,
        NULL,
        NULL,
        NULL,
        gm_803DFB80_Scenes,
    },
    {
        1,
        GM_TOURNAMENT,
        NULL,
        NULL,
        NULL,
        gm_803DDAC0_Scenes,
    },
    {
        1,
        GM_TRAINING,
        gm_801B23C4_OnLoad,
        NULL,
        gm_801B2298_OnInit,
        gm_803DDB80_Scenes,
    },
    {
        0,
        GM_TINY_VS,
        gm_801B8F98_OnLoad,
        NULL,
        gm_801B8F70_OnInit,
        gm_803DEF88_Scenes,
    },
    {
        0,
        GM_GIANT_VS,
        gm_801B91A8_OnLoad,
        NULL,
        gm_801B9180_OnInit,
        gm_803DF060_Scenes,
    },
    {
        1,
        GM_STAMINA_VS,
        gm_801B95D8_OnLoad,
        NULL,
        gm_801B95B0_OnInit,
        gm_803DF138_Scenes,
    },
    {
        1,
        GM_HOME_RUN_CONTEST,
        gm_801B9EE4_OnLoad,
        NULL,
        gm_801B9EB8_OnInit,
        gm_803DF198_Scenes,
    },
    {
        1,
        GM_10MAN_VS,
        gm_801B685C,
        NULL,
        gm_801B6834,
        gm_803DED00_Scenes,
    },
    {
        1,
        GM_100MAN_VS,
        gm_801B685C,
        NULL,
        gm_801B6834,
        gm_803DED48_Scenes,
    },
    {
        1,
        GM_3MIN_VS,
        gm_801B685C,
        NULL,
        gm_801B6834,
        gm_803DED90_Scenes,
    },
    {
        1,
        GM_15MIN_VS,
        gm_801B685C,
        NULL,
        gm_801B6834,
        gm_803DEDD8_Scenes,
    },
    {
        1,
        GM_ENDLESS_VS,
        gm_801B685C,
        NULL,
        gm_801B6834,
        gm_803DEE20_Scenes,
    },
    {
        1,
        GM_CRUEL_VS,
        gm_801B685C,
        NULL,
        gm_801B6834,
        gm_803DEE68_Scenes,
    },
    {
        0,
        GM_PROGRESSIVE_SCAN,
        NULL,
        NULL,
        NULL,
        gm_803DFDA8_Scenes,
    },
    {
        1,
        GM_BOOT,
        NULL,
        NULL,
        NULL,
        gm_803DFDD8_Scenes,
    },
    {
        1,
        GM_MEMCARD,
        NULL,
        NULL,
        NULL,
        gm_803DFE18_Scenes,
    },
    {
        0,
        GM_FIXED_CAMERA_VS,
        gm_801BA0EC_OnLoad,
        NULL,
        gm_801BA0C4_OnInit,
        gm_803DF1E0_Scenes,
    },
    {
        1,
        GM_EVENT,
        gm_801BBEA8_OnLoad,
        gm_801BBFE4_OnUnload,
        gm_801BBA60_OnInit,
        gm_803DF618_Scenes,
    },
    {
        0,
        GM_SINGLE_BUTTON_VS,
        gm_801BA2EC_OnLoad,
        NULL,
        gm_801BA2C4_OnInit,
        gm_803DF2B8_Scenes,
    },
    {
        0,
        GM_COUNT,
        NULL,
        NULL,
        NULL,
        NULL,
    },
};

GameSceneHandler* gm_801A50A0(void)
{
    return gm_803DA920;
}

GameMode* gm_801A50AC(void)
{
    return gm_803DACA4;
}
