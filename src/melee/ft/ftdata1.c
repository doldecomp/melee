#include "forward.h"
#include <baselib/forward.h>

#include "ft_unknown_006.h"
#include "ftdata.h"
#include "types.h"

#include "ftCaptain/ftCaptain_Init.h"
#include "ftCaptain/ftCaptain_SpecialHi.h"
#include "ftCaptain/ftCaptain_SpecialLw.h"
#include "ftCaptain/ftCaptain_SpecialN.h"
#include "ftCaptain/ftCaptain_SpecialS.h"
#include "ftCLink/ftCLink_Init.h"
#include "ftCrazyHand/ftcrazyhand.h"
#include "ftDonkey/ftdonkey_callbacks.h"
#include "ftDonkey/ftdonkey_SpecialHi.h"
#include "ftDonkey/ftdonkey_SpecialLw.h"
#include "ftDonkey/ftdonkey_SpecialN.h"
#include "ftDonkey/ftdonkey_SpecialS.h"
#include "ftDrMario/ftdrmario.h"
#include "ftEmblem/ftemblem.h"
#include "ftFalco/ftfalco.h"
#include "ftFox/ftfox.h"
#include "ftGameWatch/ftgamewatch.h"
#include "ftGanon/ftganon.h"
#include "ftGigaKoopa/ftgigakoopa.h"
#include "ftIceClimber/fticeclimber.h"
#include "ftIceClimber/fticeclimber1.h"
#include "ftIceClimber/fticeclimber2_nana.h"
#include "ftKirby/ftkirby.h"
#include "ftKoopa/ftkoopa.h"
#include "ftLink/ftlink.h"
#include "ftLuigi/ftluigi.h"
#include "ftMario/ftMario_Init.h"
#include "ftMario/ftMario_SpecialHi.h"
#include "ftMario/ftMario_SpecialLw.h"
#include "ftMario/ftMario_SpecialN.h"
#include "ftMario/ftMario_SpecialS.h"
#include "ftMario/ftMario_Strings.h"
#include "ftMars/ftMars.h"
#include "ftMasterHand/ftMasterHand_01.h"
#include "ftMasterHand/ftMasterHand_02.h"
#include "ftMewtwo/ftmewtwo.h"
#include "ftNess/ftNess.h"
#include "ftPeach/ftpeach.h"
#include "ftPichu/ftpichu.h"
#include "ftPikachu/ftpikachu.h"
#include "ftPikachu/ftpikachu1.h"
#include "ftPurin/ftpurin.h"
#include "ftSamus/ftsamus1.h"
#include "ftSamus/ftsamus3.h"
#include "ftSamus/ftsamus4.h"
#include "ftSamus/ftsamus5.h"
#include "ftSamus/ftsamus6.h"
#include "ftSandbag/ftsandbag.h"
#include "ftSeak/ftSeak_Init.h"
#include "ftSeak/ftSeak_SpecialHi.h"
#include "ftSeak/ftSeak_SpecialLw.h"
#include "ftSeak/ftSeak_SpecialN.h"
#include "ftSeak/ftSeak_SpecialS.h"
#include "ftYoshi/ftyoshi1.h"
#include "ftYoshi/ftyoshi2.h"
#include "ftYoshi/ftyoshi4.h"
#include "ftZakoBoy/ftzakoboy.h"
#include "ftZakoGirl/ftzakogirl.h"
#include "ftZelda/ftzelda.h"
#include "ftZelda/ftZelda_Init.h"

#include <dolphin/mtx/types.h>

typedef struct ftData_UnkCountStruct {
    /// Always zero; could be #NULL or the high part of a 64-bit integer.
    int zero;

    /// A count or msid.
    int count;
} ftData_UnkCountStruct;

ftData_UnkCountStruct lbl_803C0FC8[FTKIND_MAX] = {
    { 0, 303 }, { 0, 327 }, { 0, 318 }, { 0, 337 }, { 0, 479 }, { 0, 316 },
    { 0, 314 }, { 0, 317 }, { 0, 326 }, { 0, 318 }, { 0, 321 }, { 0, 321 },
    { 0, 320 }, { 0, 313 }, { 0, 314 }, { 0, 327 }, { 0, 314 }, { 0, 312 },
    { 0, 327 }, { 0, 311 }, { 0, 314 }, { 0, 303 }, { 0, 327 }, { 0, 320 },
    { 0, 323 }, { 0, 318 }, { 0, 327 }, { 0, 345 }, { 0, 344 }, { 0, 295 },
    { 0, 295 }, { 0, 316 }, { 0, 296 },
};

Event lbl_803C10D0[FTKIND_MAX] = {
    NULL, NULL, NULL, NULL, func_800EE528, NULL, NULL, NULL, NULL, NULL, NULL,
    NULL, NULL, NULL, NULL, func_8013C2F8, NULL, NULL, NULL, NULL, NULL, NULL,
    NULL, NULL, NULL, NULL, NULL,          NULL, NULL, NULL, NULL, NULL, NULL,
};

HSD_GObjEvent ft_OnLoad[FTKIND_MAX] = {
    ftMario_OnLoad,      ftFox_OnLoad,        ftCaptain_OnLoad,
    ftDonkey_OnLoad,     ftKirby_OnLoad,      ftKoopa_OnLoad,
    ftLink_OnLoad,       ftSeak_OnLoad,       ftNess_OnLoad,
    ftPeach_OnLoad,      ftIceClimber_OnLoad, ftNana_OnLoad,
    ftPikachu_OnLoad,    ftSamus_OnLoad,      ftYoshi_OnLoad,
    ftPurin_OnLoad,      ftMewtwo_OnLoad,     ftLuigi_OnLoad,
    ftMars_OnLoad,       ftZelda_OnLoad,      ftCLink_OnLoad,
    ftDrMario_OnLoad,    ftFalco_OnLoad,      ftPichu_OnLoad,
    ftGameWatch_OnLoad,  ftGanon_OnLoad,      ftRoy_OnLoad,
    ftMasterhand_OnLoad, ftCrazyhand_OnLoad,  ftZakoBoy_OnLoad,
    ftZakoGirl_OnLoad,   ftGKoopa_OnLoad,     ftSandbag_OnLoad,
};

HSD_GObjEvent ft_OnDeath[FTKIND_MAX] = {
    ftMario_OnDeath,      ftFox_OnDeath,        ftCaptain_OnDeath,
    ftDonkey_OnDeath,     ftKirby_OnDeath,      ftKoopa_OnDeath,
    ftLink_OnDeath,       ftSeak_OnDeath,       ftNess_OnDeath,
    ftPeach_OnDeath,      ftIceClimber_OnDeath, ftNana_OnDeath,
    ftPikachu_OnDeath,    ftSamus_OnDeath,      ftYoshi_OnDeath,
    ftPurin_OnDeath,      ftMewtwo_OnDeath,     ftLuigi_OnDeath,
    ftMars_OnDeath,       ftZelda_OnDeath,      ftCLink_OnDeath,
    ftDrMario_OnDeath,    ftFalco_OnDeath,      ftPichu_OnDeath,
    ftGameWatch_OnDeath,  ftGanon_OnDeath,      ftRoy_OnDeath,
    ftMasterhand_OnDeath, ftCrazyhand_OnDeath,  ftZakoBoy_OnDeath,
    ftZakoGirl_OnDeath,   ftGKoopa_OnDeath,     ftSandbag_OnDeath,
};

HSD_GObjEvent ft_OnUserDataRemove[FTKIND_MAX] = {
    NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
    NULL, NULL, NULL, NULL, NULL, NULL, NULL, ftPurin_OnUserDataRemove,
    NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
    NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
    NULL,
};

MotionState* MotionStateTableByCharacter[FTKIND_MAX] = {
    ms_table_mario,
    ms_table_fox,
    ms_table_captain,
    ms_table_donkey,
    ms_table_kirby,
    ms_table_koopa,
    ms_table_link,
    ms_table_seak,
    ms_table_ness,
    ms_table_peach,
    ms_table_iceclimber,
    ms_table_nana,
    ms_table_pikachu,
    ms_table_samus,
    ms_table_yoshi,
    ms_table_purin,
    ms_table_mewtwo,
    ms_table_luigi,
    ms_table_mars,
    ms_table_zelda,
    ms_table_clink,
    ms_table_drmario,
    ms_table_falco,
    ms_table_pichu,
    ms_table_gamewatch,
    ms_table_ganon,
    ms_table_roy,
    ms_table_masterhand,
    ms_table_crazyhand,
    NULL,
    NULL,
    ms_table_gkoopa,
    ms_table_sandbag,
};

MotionState* lbl_803C1364[FTKIND_MAX] = {
    lbl_803C7260, NULL, NULL, NULL,         lbl_803CA04C, NULL, NULL,
    NULL,         NULL, NULL, NULL,         NULL,         NULL, NULL,
    NULL,         NULL, NULL, lbl_803D0868, NULL,         NULL, NULL,
    NULL,         NULL, NULL, NULL,         NULL,         NULL, NULL,
    NULL,         NULL, NULL, lbl_803D38C8, NULL,
};

HSD_GObjEvent ft_SpecialS[FTKIND_MAX] = {
    ftMario_SpecialS_StartMotion,
    ftFox_SpecialS_StartMotion,
    ftCaptain_SpecialS_StartMotion,
    ftDonkey_SpecialS_StartMotion,
    ftKirby_SpecialS_StartMotion,
    ftKoopa_SpecialS_StartMotion,
    ftLink_SpecialS_StartMotion,
    ftSeak_SpecialS_StartMotion,
    ftNess_SpecialS_StartMotion,
    ftPeach_SpecialS_StartMotion,
    ftIceClimber_SpecialS_StartMotion,
    NULL,
    ftPikachu_SpecialS_StartMotion,
    ftSamus_SpecialS_StartMotion,
    ftYoshi_SpecialS_StartMotion,
    ftPurin_SpecialS_StartMotion,
    ftMewtwo_SpecialS_StartMotion,
    ftLuigi_SpecialS_StartMotion,
    ftMars_SpecialS_StartMotion,
    ftZelda_SpecialS_StartMotion,
    ftLink_SpecialS_StartMotion,
    ftMario_SpecialS_StartMotion,
    ftFox_SpecialS_StartMotion,
    ftPikachu_SpecialS_StartMotion,
    ftGameWatch_SpecialS_StartMotion,
    ftCaptain_SpecialS_StartMotion,
    ftMars_SpecialS_StartMotion,
    NULL,
    NULL,
    NULL,
    NULL,
    ftKoopa_SpecialS_StartMotion,
    NULL,
};

HSD_GObjEvent ft_SpecialAirHi[FTKIND_MAX] = {
    ftMario_SpecialAirHi_StartMotion,
    ftFox_SpecialAirHi_StartMotion,
    ftCaptain_SpecialAirHi_StartMotion,
    ftDonkey_SpecialAirHi_StartMotion,
    ftKirby_SpecialAirHi_StartMotion,
    ftKoopa_SpecialAirHi_StartMotion,
    ftLink_SpecialAirHi_StartMotion,
    ftSeak_SpecialAirHi_StartMotion,
    ftNess_SpecialAirHiStart_Action,
    ftPeach_SpecialAirHi_StartMotion,
    ftIceClimber_SpecialAirHi_StartMotion,
    NULL,
    ftPikachu_SpecialAirHi_StartMotion,
    ftSamus_SpecialAirHi_StartMotion,
    ftYoshi_SpecialAirHi_StartMotion,
    ftPurin_SpecialAirHi_StartMotion,
    ftMewtwo_SpecialAirHi_StartMotion,
    ftLuigi_SpecialAirHi_StartMotion,
    ftMars_SpecialAirHi_StartMotion,
    ftZelda_SpecialAirHi_StartMotion,
    ftLink_SpecialAirHi_StartMotion,
    ftMario_SpecialAirHi_StartMotion,
    ftFox_SpecialAirHi_StartMotion,
    ftPikachu_SpecialAirHi_StartMotion,
    ftGameWatch_SpecialAirHi_StartMotion,
    ftCaptain_SpecialAirHi_StartMotion,
    ftMars_SpecialAirHi_StartMotion,
    NULL,
    NULL,
    NULL,
    NULL,
    ftKoopa_SpecialAirHi_StartMotion,
    NULL,
};

HSD_GObjEvent ft_SpecialAirLw[FTKIND_MAX] = {
    ftMario_SpecialAirLw_StartMotion,
    ftFox_SpecialAirLw_StartMotion,
    ftCaptain_SpecialAirLw_StartMotion,
    NULL,
    ftKirby_SpecialAirLw_StartMotion,
    ftKoopa_SpecialAirLw_StartMotion,
    ftLink_SpecialAirLw_StartMotion,
    ftSeak_SpecialAirLw_StartMotion,
    ftNess_SpecialAirLwStart_Action,
    ftPeach_SpecialAirLw_StartMotion,
    ftIceClimber_SpecialAirLw_StartMotion,
    ftIceClimber_SpecialAirLw_StartMotion,
    ftPikachu_SpecialAirLw_StartMotion,
    ftSamus_SpecialAirLw_StartMotion,
    ftYoshi_SpecialAirLw_StartMotion,
    ftPurin_SpecialAirLw_StartMotion,
    ftMewtwo_SpecialAirLw_StartMotion,
    ftLuigi_SpecialAirLw_StartMotion,
    ftMars_SpecialAirLw_StartMotion,
    ftZelda_SpecialAirLw_StartMotion,
    ftLink_SpecialAirLw_StartMotion,
    ftMario_SpecialAirLw_StartMotion,
    ftFox_SpecialAirLw_StartMotion,
    ftPikachu_SpecialAirLw_StartMotion,
    ftGameWatch_SpecialAirLw_StartMotion,
    ftCaptain_SpecialAirLw_StartMotion,
    ftMars_SpecialAirLw_StartMotion,
    NULL,
    NULL,
    NULL,
    NULL,
    ftKoopa_SpecialAirLw_StartMotion,
    NULL,
};

HSD_GObjEvent ft_SpecialAirS[FTKIND_MAX] = {
    ftMario_SpecialAirS_StartMotion,
    ftFox_SpecialAirS_StartMotion,
    ftCaptain_SpecialAirS_StartMotion,
    ftDonkey_SpecialAirS_StartMotion,
    ftKirby_SpecialAirS_StartMotion,
    ftKoopa_SpecialAirS_StartMotion,
    ftLink_SpecialAirS_StartMotion,
    ftSeak_SpecialAirS_StartMotion,
    ftNess_SpecialAirS_Action,
    ftPeach_SpecialAirS_StartMotion,
    ftIceClimber_SpecialAirS_StartMotion,
    NULL,
    ftPikachu_SpecialAirS_StartMotion,
    ftSamus_SpecialAirS_StartMotion,
    ftYoshi_SpecialAirS_StartMotion,
    ftPurin_SpecialAirS_StartMotion,
    ftMewtwo_SpecialAirS_StartMotion,
    ftLuigi_SpecialAirS_StartMotion,
    ftMars_SpecialAirS_StartMotion,
    ftZelda_SpecialAirS_StartMotion,
    ftLink_SpecialAirS_StartMotion,
    ftMario_SpecialAirS_StartMotion,
    ftFox_SpecialAirS_StartMotion,
    ftPikachu_SpecialAirS_StartMotion,
    ftGameWatch_SpecialAirS_StartMotion,
    ftCaptain_SpecialAirS_StartMotion,
    ftMars_SpecialAirS_StartMotion,
    NULL,
    NULL,
    NULL,
    NULL,
    ftKoopa_SpecialAirS_StartMotion,
    NULL,
};

HSD_GObjEvent ft_SpecialAirN[FTKIND_MAX] = {
    ftMario_SpecialAirN_StartMotion,
    ftFox_SpecialAirN_StartMotion,
    ftCaptain_SpecialAirN_StartMotion,
    ftDonkey_SpecialAirN_StartMotion,
    ftKirby_SpecialAirN_StartMotion,
    ftKoopa_SpecialAirN_StartMotion,
    ftLink_SpecialAirN_StartMotion,
    ftSeak_SpecialAirN_StartMotion,
    ftNess_SpecialAirNStart_Action,
    ftPeach_SpecialAirN_StartMotion,
    ftIceClimber_SpecialAirN_StartMotion,
    ftIceClimber_SpecialAirN_StartMotion,
    ftPikachu_SpecialAirN_StartMotion,
    ftSamus_SpecialAirN_StartMotion,
    ftYoshi_SpecialAirN_StartMotion,
    ftPurin_SpecialAirN_StartMotion,
    ftMewtwo_SpecialAirN_StartMotion,
    ftLuigi_SpecialAirN_StartMotion,
    ftMars_SpecialAirN_StartMotion,
    ftZelda_SpecialAirN_StartMotion,
    ftLink_SpecialAirN_StartMotion,
    ftMario_SpecialAirN_StartMotion,
    ftFox_SpecialAirN_StartMotion,
    ftPikachu_SpecialAirN_StartMotion,
    ftGameWatch_SpecialAirN_StartMotion,
    ftCaptain_SpecialAirN_StartMotion,
    ftMars_SpecialAirN_StartMotion,
    NULL,
    NULL,
    NULL,
    NULL,
    ftKoopa_SpecialAirN_StartMotion,
    NULL,
};

HSD_GObjEvent ft_SpecialN[FTKIND_MAX] = {
    ftMario_SpecialN_StartMotion,
    ftFox_SpecialN_StartMotion,
    ftCaptain_SpecialN_StartMotion,
    ftDonkey_SpecialN_StartMotion,
    ftKirby_SpecialN_StartMotion,
    ftKoopa_SpecialN_StartMotion,
    ftLink_SpecialN_StartMotion,
    ftSeak_SpecialN_StartMotion,
    ftNess_SpecialNStart_Action,
    ftPeach_SpecialN_StartMotion,
    ftIceClimber_SpecialN_StartMotion,
    ftIceClimber_SpecialN_StartMotion,
    ftPikachu_SpecialN_StartMotion,
    ftSamus_SpecialN_StartMotion,
    ftYoshi_SpecialN_StartMotion,
    ftPurin_SpecialN_StartMotion,
    ftMewtwo_SpecialN_StartMotion,
    ftLuigi_SpecialN_StartMotion,
    ftMars_SpecialN_StartMotion,
    ftZelda_SpecialN_StartMotion,
    ftLink_SpecialN_StartMotion,
    ftMario_SpecialN_StartMotion,
    ftFox_SpecialN_StartMotion,
    ftPikachu_SpecialN_StartMotion,
    ftGameWatch_SpecialN_StartMotion,
    ftCaptain_SpecialN_StartMotion,
    ftMars_SpecialN_StartMotion,
    NULL,
    NULL,
    NULL,
    NULL,
    ftKoopa_SpecialN_StartMotion,
    NULL,
};

HSD_GObjEvent ft_SpecialLw[FTKIND_MAX] = {
    ftMario_SpecialLw_StartMotion,
    ftFox_SpecialLw_StartMotion,
    ftCaptain_SpecialLw_StartMotion,
    ftDonkey_SpecialLw_StartMotion,
    ftKirby_SpecialLw_StartMotion,
    ftKoopa_SpecialLw_StartMotion,
    ftLink_SpecialLw_StartMotion,
    ftSeak_SpecialLw_StartMotion,
    ftNess_SpecialLwStart_Action,
    ftPeach_SpecialLw_StartMotion,
    ftIceClimber_SpecialLw_StartMotion,
    ftIceClimber_SpecialLw_StartMotion,
    ftPikachu_SpecialLw_StartMotion,
    ftSamus_SpecialLw_StartMotion,
    ftYoshi_SpecialLw_StartMotion,
    ftPurin_SpecialLw_StartMotion,
    ftMewtwo_SpecialLw_StartMotion,
    ftLuigi_SpecialLw_StartMotion,
    ftMars_SpecialLw_StartMotion,
    ftZelda_SpecialLw_StartMotion,
    ftLink_SpecialLw_StartMotion,
    ftMario_SpecialLw_StartMotion,
    ftFox_SpecialLw_StartMotion,
    ftPikachu_SpecialLw_StartMotion,
    ftGameWatch_SpecialLw_StartMotion,
    ftCaptain_SpecialLw_StartMotion,
    ftMars_SpecialLw_StartMotion,
    NULL,
    NULL,
    NULL,
    NULL,
    ftKoopa_SpecialLw_StartMotion,
    NULL,
};

HSD_GObjEvent ft_SpecialHi[FTKIND_MAX] = {
    ftMario_SpecialHi_StartMotion,
    ftFox_SpecialHi_StartMotion,
    ftCaptain_SpecialHi_StartMotion,
    ftDonkey_SpecialHi_StartMotion,
    ftKirby_SpecialHi_StartMotion,
    ftKoopa_SpecialHi_StartMotion,
    ftLink_SpecialHi_StartMotion,
    ftSeak_SpecialHi_StartMotion,
    ftNess_SpecialHi_StartMotion,
    ftPeach_SpecialHi_StartMotion,
    ftIceClimber_SpecialHi_StartMotion,
    NULL,
    ftPikachu_SpecialHi_StartMotion,
    ftSamus_SpecialHi_StartMotion,
    ftYoshi_SpecialHi_StartMotion,
    ftPurin_SpecialHi_StartMotion,
    ftMewtwo_SpecialHi_StartMotion,
    ftLuigi_SpecialHi_StartMotion,
    ftMars_SpecialHi_StartMotion,
    ftZelda_SpecialHi_StartMotion,
    ftLink_SpecialHi_StartMotion,
    ftMario_SpecialHi_StartMotion,
    ftFox_SpecialHi_StartMotion,
    ftPikachu_SpecialHi_StartMotion,
    ftGameWatch_SpecialHi_StartMotion,
    ftCaptain_SpecialHi_StartMotion,
    ftMars_SpecialHi_StartMotion,
    NULL,
    NULL,
    NULL,
    NULL,
    ftKoopa_SpecialHi_StartMotion,
    NULL,
};

HSD_GObjEvent ft_OnAbsorb[FTKIND_MAX] = {
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    ftNess_OnAbsorb,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    ftGameWatch_OnAbsorb,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
};

Fighter_ItemEvent ft_OnItemPickupExt[FTKIND_MAX] = {
    ftMario_OnItemPickup,
    ftFox_OnItemPickup,
    ftCaptain_OnItemPickup,
    ftDonkey_OnItemPickup,
    ftKirby_OnItemPickup,
    ftKoopa_OnItemPickup,
    ftLink_OnItemPickupExt,
    ftSeak_OnItemPickup,
    ftNess_OnItemPickup,
    ftPeach_OnItemPickup,
    ftIceClimber_OnItemPickup,
    ftIceClimber_OnItemPickup,
    ftPikachu_OnItemPickup,
    ftSamus_OnItemPickup,
    ftYoshi_OnItemPickup,
    ftPurin_OnItemPickup,
    ftMewTwo_OnItemPickup,
    ftLuigi_OnItemPickup,
    ftMars_OnItemPickup,
    ftZelda_OnItemPickup,
    ftCLink_OnItemPickupExt,
    ftDrMario_OnItemPickup,
    ftFalco_OnItemPickup,
    ftPichu_OnItemPickup,
    ftGameWatch_OnItemPickup,
    ftGanon_OnItemPickup,
    ftRoy_OnItemPickup,
    NULL,
    NULL,
    ftZakoBoy_OnItemPickup,
    ftZakoGirl_OnItemPickup,
    ftGKoopa_OnItemPickup,
    NULL,
};

HSD_GObjEvent ft_OnItemInvisible[FTKIND_MAX] = {
    ftMario_OnItemInvisible,
    ftFox_OnItemInvisible,
    ftCaptain_OnItemInvisible,
    ftDonkey_OnItemInvisible,
    ftKirby_OnItemInvisible,
    ftKoopa_OnItemInvisible,
    ftLink_OnItemInvisible,
    ftSeak_OnItemInvisible,
    ftNess_OnItemInvisible,
    ftPeach_OnItemInvisible,
    ftIceClimber_OnItemInvisible,
    ftIceClimber_OnItemInvisible,
    ftPikachu_OnItemInvisible,
    ftSamus_OnItemInvisible,
    ftYoshi_OnItemInvisible,
    ftPurin_OnItemInvisible,
    ftMewTwo_OnItemInvisible,
    ftLuigi_OnItemInvisible,
    ftMars_OnItemInvisible,
    ftZelda_OnItemInvisible,
    ftCLink_OnItemInvisible,
    ftDrMario_OnItemInvisible,
    ftFalco_OnItemInvisible,
    ftPichu_OnItemInvisible,
    ftGameWatch_OnItemInvisible,
    ftGanon_OnItemInvisible,
    ftRoy_OnItemInvisible,
    NULL,
    NULL,
    ftZakoBoy_OnItemInvisible,
    ftZakoGirl_OnItemInvisible,
    ftGKoopa_OnItemInvisible,
    NULL,
};

HSD_GObjEvent ft_OnItemVisible[FTKIND_MAX] = {
    ftMario_OnItemVisible,
    ftFox_OnItemVisible,
    ftCaptain_OnItemVisible,
    ftDonkey_OnItemVisible,
    ftKirby_OnItemVisible,
    ftKoopa_OnItemVisible,
    ftLink_OnItemVisible,
    ftSeak_OnItemVisible,
    ftNess_OnItemVisible,
    ftPeach_OnItemVisible,
    ftIceClimber_OnItemVisible,
    ftIceClimber_OnItemVisible,
    ftPikachu_OnItemVisible,
    ftSamus_OnItemVisible,
    ftYoshi_OnItemVisible,
    ftPurin_OnItemVisible,
    ftMewTwo_OnItemVisible,
    ftLuigi_OnItemVisible,
    ftMars_OnItemVisible,
    ftZelda_OnItemVisible,
    ftCLink_OnItemVisible,
    ftDrMario_OnItemVisible,
    ftFalco_OnItemVisible,
    ftPichu_OnItemVisible,
    ftGameWatch_OnItemVisible,
    ftGanon_OnItemVisible,
    ftRoy_OnItemVisible,
    NULL,
    NULL,
    ftZakoBoy_OnItemVisible,
    ftZakoGirl_OnItemVisible,
    ftGKoopa_OnItemVisible,
    NULL,
};

Fighter_ItemEvent ft_OnItemDropExt[FTKIND_MAX] = {
    ftMario_OnItemDrop,
    ftFox_OnItemDrop,
    ftCaptain_OnItemDrop,
    ftDonkey_OnItemDrop,
    ftKirby_OnItemDrop,
    ftKoopa_OnItemDrop,
    ftLink_OnItemDropExt,
    ftSeak_OnItemDrop,
    ftNess_OnItemDrop,
    ftPeach_OnItemDrop,
    ftIceClimber_OnItemDrop,
    ftIceClimber_OnItemDrop,
    ftPikachu_OnItemDrop,
    ftSamus_OnItemDrop,
    ftYoshi_OnItemDrop,
    ftPurin_OnItemDrop,
    ftMewTwo_OnItemDrop,
    ftLuigi_OnItemDrop,
    ftMars_OnItemDrop,
    ftZelda_OnItemDrop,
    ftCLink_OnItemDropExt,
    ftDrMario_OnItemDrop,
    ftFalco_OnItemDrop,
    ftPichu_OnItemDrop,
    ftGameWatch_OnItemDrop,
    ftGanon_OnItemDrop,
    ftRoy_OnItemDrop,
    NULL,
    NULL,
    ftZakoBoy_OnItemDrop,
    ftZakoGirl_OnItemDrop,
    ftGKoopa_OnItemDrop,
    NULL,
};

Fighter_ItemEvent ft_OnItemPickup[FTKIND_MAX] = {
    ftMario_OnItemPickup,
    ftFox_OnItemPickup,
    ftCaptain_OnItemPickup,
    ftDonkey_OnItemPickup,
    ftKirby_OnItemPickup,
    ftKoopa_OnItemPickup,
    ftLink_OnItemPickup,
    ftSeak_OnItemPickup,
    ftNess_OnItemPickup,
    ftPeach_OnItemPickup,
    ftIceClimber_OnItemPickup,
    ftIceClimber_OnItemPickup,
    ftPikachu_OnItemPickup,
    ftSamus_OnItemPickup,
    ftYoshi_OnItemPickup,
    ftPurin_OnItemPickup,
    ftMewTwo_OnItemPickup,
    ftLuigi_OnItemPickup,
    ftMars_OnItemPickup,
    ftZelda_OnItemPickup,
    ftCLink_OnItemPickup,
    ftDrMario_OnItemPickup,
    ftFalco_OnItemPickup,
    ftPichu_OnItemPickup,
    ftGameWatch_OnItemPickup,
    ftGanon_OnItemPickup,
    ftRoy_OnItemPickup,
    NULL,
    NULL,
    ftZakoBoy_OnItemPickup,
    ftZakoGirl_OnItemPickup,
    ftGKoopa_OnItemPickup,
    NULL,
};

Fighter_ItemEvent ft_OnItemDrop[FTKIND_MAX] = {
    ftMario_OnItemDrop,
    ftFox_OnItemDrop,
    ftCaptain_OnItemDrop,
    ftDonkey_OnItemDrop,
    ftKirby_OnItemDrop,
    ftKoopa_OnItemDrop,
    ftLink_OnItemDrop,
    ftSeak_OnItemDrop,
    ftNess_OnItemDrop,
    ftPeach_OnItemDrop,
    ftIceClimber_OnItemDrop,
    ftIceClimber_OnItemDrop,
    ftPikachu_OnItemDrop,
    ftSamus_OnItemDrop,
    ftYoshi_OnItemDrop,
    ftPurin_OnItemDrop,
    ftMewTwo_OnItemDrop,
    ftLuigi_OnItemDrop,
    ftMars_OnItemDrop,
    ftZelda_OnItemDrop,
    ftCLink_OnItemDrop,
    ftDrMario_OnItemDrop,
    ftFalco_OnItemDrop,
    ftPichu_OnItemDrop,
    ftGameWatch_OnItemDrop,
    ftGanon_OnItemDrop,
    ftRoy_OnItemDrop,
    NULL,
    NULL,
    ftZakoBoy_OnItemDrop,
    ftZakoGirl_OnItemDrop,
    ftGKoopa_OnItemDrop,
    NULL,
};

HSD_GObjEvent lbl_803C1BA4[FTKIND_MAX] = {
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    ftPikachu_8012467C,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
};

HSD_GObjEvent lbl_803C1C28[FTKIND_MAX] = {
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    ftPikachu_801246C0,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
};

HSD_GObjEvent ft_OnKnockbackEnter[FTKIND_MAX] = {
    ftMario_OnKnockbackEnter,
    ftFox_OnKnockbackEnter,
    NULL,
    ftDonkey_OnKnockbackEnter,
    ftKirby_OnKnockbackEnter,
    ftKoopa_OnKnockbackEnter,
    ftLink_OnKnockbackEnter,
    ftSeak_OnKnockbackEnter,
    ftNess_OnKnockbackEnter,
    ftPeach_OnKnockbackEnter,
    ftIceClimber_OnKnockbackEnter,
    ftIceClimber_OnKnockbackEnter,
    ftPikachu_OnKnockbackEnter,
    NULL,
    ftYoshi_OnKnockbackEnter,
    ftPurin_OnKnockbackEnter,
    ftMewTwo_OnKnockbackEnter,
    ftLuigi_OnKnockbackEnter,
    ftMars_OnKnockbackEnter,
    ftZelda_OnKnockbackEnter,
    ftCLink_OnKnockbackEnter,
    ftDrMario_OnKnockbackEnter,
    ftFalco_OnKnockbackEnter,
    ftPichu_OnKnockbackEnter,
    NULL,
    ftGanon_OnKnockbackEnter,
    ftRoy_OnKnockbackEnter,
    NULL,
    NULL,
    NULL,
    NULL,
    ftGKoopa_OnKnockbackEnter,
    ftSandbag_OnKnockbackEnter,
};

HSD_GObjEvent ft_OnKnockbackExit[FTKIND_MAX] = {
    ftMario_OnKnockbackExit,
    ftFox_OnKnockbackExit,
    NULL,
    ftDonkey_OnKnockbackExit,
    ftKirby_OnKnockbackExit,
    ftKoopa_OnKnockbackExit,
    ftLink_OnKnockbackExit,
    ftSeak_OnKnockbackExit,
    ftNess_OnKnockbackExit,
    ftPeach_OnKnockbackExit,
    ftIceClimber_OnKnockbackExit,
    ftIceClimber_OnKnockbackExit,
    ftPikachu_OnKnockbackExit,
    NULL,
    ftYoshi_OnKnockbackExit,
    ftPurin_OnKnockbackExit,
    ftMewTwo_OnKnockbackExit,
    ftLuigi_OnKnockbackExit,
    ftMars_OnKnockbackExit,
    ftZelda_OnKnockbackExit,
    ftCLink_OnKnockbackExit,
    ftDrMario_OnKnockbackExit,
    ftFalco_OnKnockbackExit,
    ftPichu_OnKnockbackExit,
    NULL,
    ftGanon_OnKnockbackExit,
    ftRoy_OnKnockbackExit,
    NULL,
    NULL,
    NULL,
    NULL,
    ftGKoopa_OnKnockbackExit,
    ftSandbag_OnKnockbackExit,
};

HSD_GObjEvent lbl_803C1DB4[FTKIND_MAX] = {
    NULL, NULL, NULL, NULL, func_800F1B6C, func_80132A64, NULL, NULL, NULL,
    NULL, NULL, NULL, NULL, NULL,          NULL,          NULL, NULL, NULL,
    NULL, NULL, NULL, NULL, NULL,          NULL,          NULL, NULL, NULL,
    NULL, NULL, NULL, NULL, func_8014F698, NULL,
};

HSD_GObjEvent lbl_803C1E38[FTKIND_MAX] = {
    NULL,
    NULL,
    NULL,
    func_8010D96C,
    func_800EE818,
    NULL,
    NULL,
    ftSeak_801101CC,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    ftSamus_80128628,
    NULL,
    NULL,
    ftMewTwo_80144F58,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    ftGameWatch_8014A77C,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
};

HSD_GObjEvent ft_LoadSpecialAttrs[FTKIND_MAX] = {
    ftMario_LoadSpecialAttrs,      ftFox_LoadSpecialAttrs,
    ftCaptain_LoadSpecialAttrs,    ftDonkey_LoadSpecialAttrs,
    ftKirby_LoadSpecialAttrs,      ftKoopa_LoadSpecialAttrs,
    ftLink_LoadSpecialAttrs,       ftSeak_LoadSpecialAttrs,
    ftNess_LoadSpecialAttrs,       ftPeach_LoadSpecialAttrs,
    ftIceClimber_LoadSpecialAttrs, ftNana_LoadSpecialAttrs,
    ftPikachu_LoadSpecialAttrs,    ftSamus_LoadSpecialAttrs,
    ftYoshi_LoadSpecialAttrs,      ftPurin_LoadSpecialAttrs,
    ftMewTwo_LoadSpecialAttrs,     ftLuigi_LoadSpecialAttrs,
    ftMars_LoadSpecialAttrs,       ftZelda_LoadSpecialAttrs,
    ftCLink_LoadSpecialAttrs,      ftDrMario_LoadSpecialAttrs,
    ftFalco_LoadSpecialAttrs,      ftPichu_LoadSpecialAttrs,
    ftGameWatch_LoadSpecialAttrs,  ftGanon_LoadSpecialAttrs,
    ftRoy_LoadSpecialAttrs,        ftMasterHand_LoadSpecialAttrs,
    ftCrazyHand_LoadSpecialAttrs,  ftZakoBoy_LoadSpecialAttrs,
    ftZakoGirl_LoadSpecialAttrs,   ftGKoopa_LoadSpecialAttrs,
    ftSandbag_LoadSpecialAttrs,
};

/// Standard Character .dat File Names
char* lbl_803C1F40[FTKIND_MAX * 2] = {
    lbl_803C57D0, lbl_803C57DC, lbl_803C7BE8,         lbl_803C7BF4,
    lbl_803C7598, lbl_803C75A4, lbl_803CBDF8,         lbl_803CBE04,
    lbl_803CA308, lbl_803CA314, lbl_803CF0A0,         lbl_803CF0AC,
    lbl_803C80B8, lbl_803C80C4, lbl_803CC360,         lbl_803CC36C,
    lbl_803CCAD0, lbl_803CCADC, ftPeach_str_PlPe_dat, ftPeach_str_ftDataPeach,
    lbl_803CD610, lbl_803CD61C, lbl_803CDB78,         lbl_803CDB84,
    lbl_803CE0B8, lbl_803CE0C4, lbl_803CE510,         lbl_803CE51C,
    lbl_803CEA98, lbl_803CEAA4, lbl_803D02F0,         lbl_803D02FC,
    lbl_803D0D80, lbl_803D0D8C, lbl_803D08A8,         lbl_803D08B4,
    lbl_803CF820, lbl_803CF82C, lbl_803CFC98,         lbl_803CFCA4,
    lbl_803D1240, lbl_803D124C, lbl_803D15D8,         lbl_803D15E4,
    lbl_803D1CA8, lbl_803D1CB4, lbl_803D21E8,         lbl_803D21F4,
    lbl_803D28E8, lbl_803D28F4, lbl_803D2CD8,         lbl_803D2CE4,
    lbl_803D3280, lbl_803D328C, lbl_803D4070,         lbl_803D407C,
    lbl_803D4818, lbl_803D4824, lbl_803D34E8,         lbl_803D34F4,
    lbl_803D3568, lbl_803D3574, lbl_803D38E8,         lbl_803D38F4,
    lbl_803D39B8, lbl_803D39C4,
};

HSD_GObjEvent lbl_803C2048[FTKIND_MAX] = {
    NULL, NULL, NULL, NULL, func_800EEE9C, NULL, NULL, NULL, NULL, NULL, NULL,
    NULL, NULL, NULL, NULL, NULL,          NULL, NULL, NULL, NULL, NULL, NULL,
    NULL, NULL, NULL, NULL, NULL,          NULL, NULL, NULL, NULL, NULL, NULL,
};

Fighter_UnkMtxEvent lbl_803C20CC[FTKIND_MAX] = {
    NULL, NULL, NULL, NULL, func_800EEF04, NULL, NULL, NULL, NULL, NULL, NULL,
    NULL, NULL, NULL, NULL, func_8013C4F0, NULL, NULL, NULL, NULL, NULL, NULL,
    NULL, NULL, NULL, NULL, NULL,          NULL, NULL, NULL, NULL, NULL, NULL,
};

/// Character model group (e.g. high poly, low poly, metal) visibility change
/// callbacks
ftData_UnkModelStruct lbl_803C2150 = {
    {
        NULL, NULL, NULL, NULL, func_800EF87C, NULL, NULL,          NULL, NULL,
        NULL, NULL, NULL, NULL, NULL,          NULL, func_8013C614, NULL, NULL,
        NULL, NULL, NULL, NULL, NULL,          NULL, NULL,          NULL, NULL,
        NULL, NULL, NULL, NULL, NULL,          NULL,
    },
    {
        NULL, NULL, NULL, NULL, func_800EF028, NULL, NULL,          NULL, NULL,
        NULL, NULL, NULL, NULL, NULL,          NULL, func_8013C664, NULL, NULL,
        NULL, NULL, NULL, NULL, NULL,          NULL, NULL,          NULL, NULL,
        NULL, NULL, NULL, NULL, NULL,          NULL,
    },
};

HSD_GObjEvent lbl_803C2258[][FTKIND_MAX] = {
    {
        NULL,          NULL, NULL, NULL, NULL, NULL, NULL, NULL, func_800EF9BC,
        func_800EF9FC, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
        NULL,          NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
        NULL,          NULL, NULL, NULL, NULL, NULL,
    },
    {
        NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
        NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
        NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
    }

};

struct {
    /// Costume and Joint Strings
    Fighter_CostumeStrings* costume_strings[FTKIND_MAX];
    /// Animation .dat Filenames
    char* anim_dat_filenames[FTKIND_MAX];
} lbl_803C2360 = {
    {
        ftMario_CostumeStrings, lbl_803C7D9C,
        lbl_803C773C,           lbl_803CC020,
        lbl_803CA5B4,           lbl_803CF26C,
        lbl_803C82B0,           lbl_803CC558,
        lbl_803CCC84,           ftPeach_str_arr_Costumes,
        lbl_803CD7C4,           lbl_803CDD2C,
        lbl_803CE2A0,           lbl_803CE678,
        lbl_803CECFC,           lbl_803D0508,
        lbl_803D0F5C,           lbl_803D0AB4,
        lbl_803CFA18,           lbl_803CFEB0,
        lbl_803D1458,           lbl_803D180C,
        lbl_803D1E74,           lbl_803D23B4,
        lbl_803D29C8,           lbl_803D2E40,
        lbl_803D34A8,           lbl_803D40C4,
        lbl_803D4868,           lbl_803D3558,
        lbl_803D35D8,           lbl_803D3988,
        lbl_803D3A24,
    },
    {
        lbl_803C595C, lbl_803C7D10, lbl_803C76A0, lbl_803CBF88, lbl_803CA4E0,
        lbl_803CF1E0, lbl_803C8224, lbl_803CC4CC, lbl_803CCBF8, str_PlPeAJ_dat,
        lbl_803CD738, lbl_803CDCA0, lbl_803CE204, lbl_803CE5EC, lbl_803CEC70,
        lbl_803D047C, lbl_803D0EC4, lbl_803D09E8, lbl_803CF98C, lbl_803CFE24,
        lbl_803D13CC, lbl_803D1770, lbl_803D1DE8, lbl_803D2328, lbl_803D292C,
        lbl_803D2DB4, lbl_803D3410, lbl_803D40B8, lbl_803D485C, lbl_803D3520,
        lbl_803D35A0, lbl_803D3948, lbl_803D3A18,
    }

};

/// Demo Lookup Strings
Fighter_DemoStrings* lbl_803C2468[FTKIND_MAX] = {
    &ftMario_DemoMotionFilenames,
    &lbl_803C7D8C,
    &lbl_803C772C,
    &lbl_803CC010,
    &lbl_803CA55C,
    &lbl_803CF25C,
    &lbl_803C82A0,
    &lbl_803CC548,
    &lbl_803CCC74,
    &ftPeach_str_arr_ftDemo,
    &lbl_803CD7B4,
    &lbl_803CDD1C,
    &lbl_803CE290,
    &lbl_803CE668,
    &lbl_803CECEC,
    &lbl_803D04F8,
    &lbl_803D0F4C,
    &lbl_803D0A64,
    &lbl_803CFA08,
    &lbl_803CFEA0,
    &lbl_803D1448,
    &lbl_803D17FC,
    &lbl_803D1E64,
    &lbl_803D23A4,
    &lbl_803D29B8,
    &lbl_803D2E30,
    &lbl_803D3498,
    NULL,
    NULL,
    NULL,
    NULL,
    &lbl_803D3954,
    NULL,
};

Fighter_MotionFileStringGetter lbl_803C24EC[FTKIND_MAX] = {
    ftMario_GetMotionFileString,
    NULL,
    NULL,
    NULL,
    ftKirby_GetMotionFileString,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    ftLuigi_GetMotionFileString,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    ftGigaKoopa_GetMotionFileString,
    NULL,
};

Fighter_UnkPtrEvent lbl_803C2570[FTKIND_MAX] = {
    ftMario_800E0CAC,
    NULL,
    NULL,
    NULL,
    func_800EEBC0,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    ftLuigi_8014260C,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    func_8014F98C,
    NULL,
};

ftData_UnkCountStruct lbl_803C25F4[FTKIND_MAX] = {
    { 0, 16 }, { 0, 14 }, { 0, 14 }, { 0, 14 }, { 0, 18 }, { 0, 14 },
    { 0, 14 }, { 0, 14 }, { 0, 14 }, { 0, 14 }, { 0, 14 }, { 0, 14 },
    { 0, 14 }, { 0, 14 }, { 0, 14 }, { 0, 14 }, { 0, 14 }, { 0, 16 },
    { 0, 14 }, { 0, 14 }, { 0, 14 }, { 0, 14 }, { 0, 14 }, { 0, 14 },
    { 0, 14 }, { 0, 14 }, { 0, 14 }, { 0, 14 }, { 0, 14 }, { 0, 14 },
    { 0, 14 }, { 0, 15 }, { 0, 14 },
};

s8 lbl_803C26FC[FTKIND_MAX] = {
    1,  3,  4,  8, 5, 12, 6, 17, 10, 15, 14, 14, 7,  2,  9,  11, 13,
    18, 16, 17, 6, 1, 3,  7, -1, 19, 49, -1, -1, -1, -1, 12, -1,
};
