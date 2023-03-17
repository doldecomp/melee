#include <dolphin/mtx/types.h>
#include <melee/ft/chara/ftCaptain/ftCaptain.h>
#include <melee/ft/chara/ftCLink/ftclink.h>
#include <melee/ft/chara/ftCrazyHand/ftcrazyhand.h>
#include <melee/ft/chara/ftDonkey/ftdonkey_callbacks.h>
#include <melee/ft/chara/ftDonkey/ftdonkey_SpecialHi.h>
#include <melee/ft/chara/ftDonkey/ftdonkey_SpecialLw.h>
#include <melee/ft/chara/ftDonkey/ftdonkey_SpecialN.h>
#include <melee/ft/chara/ftDonkey/ftdonkey_SpecialS.h>
#include <melee/ft/chara/ftDrMario/ftdrmario.h>
#include <melee/ft/chara/ftEmblem/ftemblem.h>
#include <melee/ft/chara/ftFalco/ftfalco.h>
#include <melee/ft/chara/ftFox/ftfox.h>
#include <melee/ft/chara/ftGameWatch/ftgamewatch.h>
#include <melee/ft/chara/ftGanon/ftganon.h>
#include <melee/ft/chara/ftGigaKoopa/ftgigakoopa.h>
#include <melee/ft/chara/ftIceClimber/fticeclimber.h>
#include <melee/ft/chara/ftIceClimber/fticeclimber1.h>
#include <melee/ft/chara/ftIceClimber/fticeclimber2_nana.h>
#include <melee/ft/chara/ftKirby/ftkirby.h>
#include <melee/ft/chara/ftKoopa/ftkoopa.h>
#include <melee/ft/chara/ftLink/ftlink.h>
#include <melee/ft/chara/ftLuigi/ftluigi.h>
#include <melee/ft/chara/ftMario/ftmario.h>
#include <melee/ft/chara/ftMario/ftmario2.h>
#include <melee/ft/chara/ftMars/ftMars.h>
#include <melee/ft/chara/ftMasterHand/ftMasterHand.h>
#include <melee/ft/chara/ftMewtwo/ftmewtwo.h>
#include <melee/ft/chara/ftNess/ftNess.h>
#include <melee/ft/chara/ftPeach/ftpeach.h>
#include <melee/ft/chara/ftPichu/ftpichu.h>
#include <melee/ft/chara/ftPikachu/ftpikachu.h>
#include <melee/ft/chara/ftPikachu/ftpikachu1.h>
#include <melee/ft/chara/ftPurin/ftpurin.h>
#include <melee/ft/chara/ftSamus/ftsamus1.h>
#include <melee/ft/chara/ftSamus/ftsamus3.h>
#include <melee/ft/chara/ftSamus/ftsamus4.h>
#include <melee/ft/chara/ftSamus/ftsamus5.h>
#include <melee/ft/chara/ftSamus/ftsamus6.h>
#include <melee/ft/chara/ftSandbag/ftsandbag.h>
#include <melee/ft/chara/ftSeak/ftSeak_Init.h>
#include <melee/ft/chara/ftSeak/ftSeak_SpecialHi.h>
#include <melee/ft/chara/ftSeak/ftSeak_SpecialLw.h>
#include <melee/ft/chara/ftSeak/ftSeak_SpecialN.h>
#include <melee/ft/chara/ftSeak/ftSeak_SpecialS.h>
#include <melee/ft/chara/ftYoshi/ftyoshi1.h>
#include <melee/ft/chara/ftYoshi/ftyoshi2.h>
#include <melee/ft/chara/ftYoshi/ftyoshi4.h>
#include <melee/ft/chara/ftZakoBoy/ftzakoboy.h>
#include <melee/ft/chara/ftZakoGirl/ftzakogirl.h>
#include <melee/ft/chara/ftZelda/ftzelda.h>
#include <melee/ft/forward.h>
#include <melee/ft/ft_unknown_006.h>
#include <melee/ft/ftdata.h>
#include <melee/ft/types.h>
#include <sysdolphin/baselib/forward.h>

typedef struct ftData_UnkCountStruct {
    /// Always zero; could be #NULL or the high part of a 64-bit integer.
    int zero;

    /// A count or ASID.
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

ActionState* ActionStateTableByCharacter[FTKIND_MAX] = {
    as_table_mario,
    as_table_fox,
    as_table_captain,
    as_table_donkey,
    as_table_kirby,
    as_table_koopa,
    as_table_link,
    as_table_seak,
    as_table_ness,
    as_table_peach,
    as_table_iceclimber,
    as_table_nana,
    as_table_pikachu,
    as_table_samus,
    as_table_yoshi,
    as_table_purin,
    as_table_mewtwo,
    as_table_luigi,
    as_table_mars,
    as_table_zelda,
    as_table_clink,
    as_table_drmario,
    as_table_falco,
    as_table_pichu,
    as_table_gamewatch,
    as_table_ganon,
    as_table_roy,
    as_table_masterhand,
    as_table_crazyhand,
    NULL,
    NULL,
    as_table_gkoopa,
    as_table_sandbag,
};

ActionState* lbl_803C1364[FTKIND_MAX] = {
    lbl_803C7260, NULL, NULL, NULL,         lbl_803CA04C, NULL, NULL,
    NULL,         NULL, NULL, NULL,         NULL,         NULL, NULL,
    NULL,         NULL, NULL, lbl_803D0868, NULL,         NULL, NULL,
    NULL,         NULL, NULL, NULL,         NULL,         NULL, NULL,
    NULL,         NULL, NULL, lbl_803D38C8, NULL,
};

HSD_GObjEvent ft_SpecialS[FTKIND_MAX] = {
    ftMario_SpecialS_StartAction,
    ftFox_SpecialS_StartAction,
    ftCaptain_SpecialS_StartAction,
    ftDonkey_SpecialS_StartAction,
    ftKirby_SpecialS_StartAction,
    ftKoopa_SpecialS_StartAction,
    ftLink_SpecialS_StartAction,
    ftSeak_SpecialS_StartAction,
    ftNess_SpecialS_StartAction,
    ftPeach_SpecialS_StartAction,
    ftIceClimber_SpecialS_StartAction,
    NULL,
    ftPikachu_SpecialS_StartAction,
    ftSamus_SpecialS_StartAction,
    ftYoshi_SpecialS_StartAction,
    ftPurin_SpecialS_StartAction,
    ftMewtwo_SpecialS_StartAction,
    ftLuigi_SpecialS_StartAction,
    ftMars_SpecialS_StartAction,
    ftZelda_SpecialS_StartAction,
    ftLink_SpecialS_StartAction,
    ftMario_SpecialS_StartAction,
    ftFox_SpecialS_StartAction,
    ftPikachu_SpecialS_StartAction,
    ftGameWatch_SpecialS_StartAction,
    ftCaptain_SpecialS_StartAction,
    ftMars_SpecialS_StartAction,
    NULL,
    NULL,
    NULL,
    NULL,
    ftKoopa_SpecialS_StartAction,
    NULL,
};

HSD_GObjEvent ft_SpecialAirHi[FTKIND_MAX] = {
    ftMario_SpecialAirHi_StartAction,
    ftFox_SpecialAirHi_StartAction,
    ftCaptain_SpecialAirHi_StartAction,
    ftDonkey_SpecialAirHi_StartAction,
    ftKirby_SpecialAirHi_StartAction,
    ftKoopa_SpecialAirHi_StartAction,
    ftLink_SpecialAirHi_StartAction,
    ftSeak_SpecialAirHi_StartAction,
    ftNess_SpecialAirHiStart_Action,
    ftPeach_SpecialAirHi_StartAction,
    ftIceClimber_SpecialAirHi_StartAction,
    NULL,
    ftPikachu_SpecialAirHi_StartAction,
    ftSamus_SpecialAirHi_StartAction,
    ftYoshi_SpecialAirHi_StartAction,
    ftPurin_SpecialAirHi_StartAction,
    ftMewtwo_SpecialAirHi_StartAction,
    ftLuigi_SpecialAirHi_StartAction,
    ftMars_SpecialAirHi_StartAction,
    ftZelda_SpecialAirHi_StartAction,
    ftLink_SpecialAirHi_StartAction,
    ftMario_SpecialAirHi_StartAction,
    ftFox_SpecialAirHi_StartAction,
    ftPikachu_SpecialAirHi_StartAction,
    ftGameWatch_SpecialAirHi_StartAction,
    ftCaptain_SpecialAirHi_StartAction,
    ftMars_SpecialAirHi_StartAction,
    NULL,
    NULL,
    NULL,
    NULL,
    ftKoopa_SpecialAirHi_StartAction,
    NULL,
};

HSD_GObjEvent ft_SpecialAirLw[FTKIND_MAX] = {
    ftMario_SpecialAirLw_StartAction,
    ftFox_SpecialAirLw_StartAction,
    ftCaptain_SpecialAirLw_StartAction,
    NULL,
    ftKirby_SpecialAirLw_StartAction,
    ftKoopa_SpecialAirLw_StartAction,
    ftLink_SpecialAirLw_StartAction,
    ftSeak_SpecialAirLw_StartAction,
    ftNess_SpecialAirLwStart_Action,
    ftPeach_SpecialAirLw_StartAction,
    ftIceClimber_SpecialAirLw_StartAction,
    ftIceClimber_SpecialAirLw_StartAction,
    ftPikachu_SpecialAirLw_StartAction,
    ftSamus_SpecialAirLw_StartAction,
    ftYoshi_SpecialAirLw_StartAction,
    ftPurin_SpecialAirLw_StartAction,
    ftMewtwo_SpecialAirLw_StartAction,
    ftLuigi_SpecialAirLw_StartAction,
    ftMars_SpecialAirLw_StartAction,
    ftZelda_SpecialAirLw_StartAction,
    ftLink_SpecialAirLw_StartAction,
    ftMario_SpecialAirLw_StartAction,
    ftFox_SpecialAirLw_StartAction,
    ftPikachu_SpecialAirLw_StartAction,
    ftGameWatch_SpecialAirLw_StartAction,
    ftCaptain_SpecialAirLw_StartAction,
    ftMars_SpecialAirLw_StartAction,
    NULL,
    NULL,
    NULL,
    NULL,
    ftKoopa_SpecialAirLw_StartAction,
    NULL,
};

HSD_GObjEvent ft_SpecialAirS[FTKIND_MAX] = {
    ftMario_SpecialAirS_StartAction,
    ftFox_SpecialAirS_StartAction,
    ftCaptain_SpecialAirS_StartAction,
    ftDonkey_SpecialAirS_StartAction,
    ftKirby_SpecialAirS_StartAction,
    ftKoopa_SpecialAirS_StartAction,
    ftLink_SpecialAirS_StartAction,
    ftSeak_SpecialAirS_StartAction,
    ftNess_SpecialAirS_Action,
    ftPeach_SpecialAirS_StartAction,
    ftIceClimber_SpecialAirS_StartAction,
    NULL,
    ftPikachu_SpecialAirS_StartAction,
    ftSamus_SpecialAirS_StartAction,
    ftYoshi_SpecialAirS_StartAction,
    ftPurin_SpecialAirS_StartAction,
    ftMewtwo_SpecialAirS_StartAction,
    ftLuigi_SpecialAirS_StartAction,
    ftMars_SpecialAirS_StartAction,
    ftZelda_SpecialAirS_StartAction,
    ftLink_SpecialAirS_StartAction,
    ftMario_SpecialAirS_StartAction,
    ftFox_SpecialAirS_StartAction,
    ftPikachu_SpecialAirS_StartAction,
    ftGameWatch_SpecialAirS_StartAction,
    ftCaptain_SpecialAirS_StartAction,
    ftMars_SpecialAirS_StartAction,
    NULL,
    NULL,
    NULL,
    NULL,
    ftKoopa_SpecialAirS_StartAction,
    NULL,
};

HSD_GObjEvent ft_SpecialAirN[FTKIND_MAX] = {
    ftMario_SpecialAirN_StartAction,
    ftFox_SpecialAirN_StartAction,
    ftCaptain_SpecialAirN_StartAction,
    ftDonkey_SpecialAirN_StartAction,
    ftKirby_SpecialAirN_StartAction,
    ftKoopa_SpecialAirN_StartAction,
    ftLink_SpecialAirN_StartAction,
    ftSeak_SpecialAirN_StartAction,
    ftNess_SpecialAirNStart_Action,
    ftPeach_SpecialAirN_StartAction,
    ftIceClimber_SpecialAirN_StartAction,
    ftIceClimber_SpecialAirN_StartAction,
    ftPikachu_SpecialAirN_StartAction,
    ftSamus_SpecialAirN_StartAction,
    ftYoshi_SpecialAirN_StartAction,
    ftPurin_SpecialAirN_StartAction,
    ftMewtwo_SpecialAirN_StartAction,
    ftLuigi_SpecialAirN_StartAction,
    ftMars_SpecialAirN_StartAction,
    ftZelda_SpecialAirN_StartAction,
    ftLink_SpecialAirN_StartAction,
    ftMario_SpecialAirN_StartAction,
    ftFox_SpecialAirN_StartAction,
    ftPikachu_SpecialAirN_StartAction,
    ftGameWatch_SpecialAirN_StartAction,
    ftCaptain_SpecialAirN_StartAction,
    ftMars_SpecialAirN_StartAction,
    NULL,
    NULL,
    NULL,
    NULL,
    ftKoopa_SpecialAirN_StartAction,
    NULL,
};

HSD_GObjEvent ft_SpecialN[FTKIND_MAX] = {
    ftMario_SpecialN_StartAction,
    ftFox_SpecialN_StartAction,
    ftCaptain_SpecialN_StartAction,
    ftDonkey_SpecialN_StartAction,
    ftKirby_SpecialN_StartAction,
    ftKoopa_SpecialN_StartAction,
    ftLink_SpecialN_StartAction,
    ftSeak_SpecialN_StartAction,
    ftNess_SpecialNStart_Action,
    ftPeach_SpecialN_StartAction,
    ftIceClimber_SpecialN_StartAction,
    ftIceClimber_SpecialN_StartAction,
    ftPikachu_SpecialN_StartAction,
    ftSamus_SpecialN_StartAction,
    ftYoshi_SpecialN_StartAction,
    ftPurin_SpecialN_StartAction,
    ftMewtwo_SpecialN_StartAction,
    ftLuigi_SpecialN_StartAction,
    ftMars_SpecialN_StartAction,
    ftZelda_SpecialN_StartAction,
    ftLink_SpecialN_StartAction,
    ftMario_SpecialN_StartAction,
    ftFox_SpecialN_StartAction,
    ftPikachu_SpecialN_StartAction,
    ftGameWatch_SpecialN_StartAction,
    ftCaptain_SpecialN_StartAction,
    ftMars_SpecialN_StartAction,
    NULL,
    NULL,
    NULL,
    NULL,
    ftKoopa_SpecialN_StartAction,
    NULL,
};

HSD_GObjEvent ft_SpecialLw[FTKIND_MAX] = {
    ftMario_SpecialLw_StartAction,
    ftFox_SpecialLw_StartAction,
    ftCaptain_SpecialLw_StartAction,
    ftDonkey_SpecialLw_StartAction,
    ftKirby_SpecialLw_StartAction,
    ftKoopa_SpecialLw_StartAction,
    ftLink_SpecialLw_StartAction,
    ftSeak_SpecialLw_StartAction,
    ftNess_SpecialLwStart_Action,
    ftPeach_SpecialLw_StartAction,
    ftIceClimber_SpecialLw_StartAction,
    ftIceClimber_SpecialLw_StartAction,
    ftPikachu_SpecialLw_StartAction,
    ftSamus_SpecialLw_StartAction,
    ftYoshi_SpecialLw_StartAction,
    ftPurin_SpecialLw_StartAction,
    ftMewtwo_SpecialLw_StartAction,
    ftLuigi_SpecialLw_StartAction,
    ftMars_SpecialLw_StartAction,
    ftZelda_SpecialLw_StartAction,
    ftLink_SpecialLw_StartAction,
    ftMario_SpecialLw_StartAction,
    ftFox_SpecialLw_StartAction,
    ftPikachu_SpecialLw_StartAction,
    ftGameWatch_SpecialLw_StartAction,
    ftCaptain_SpecialLw_StartAction,
    ftMars_SpecialLw_StartAction,
    NULL,
    NULL,
    NULL,
    NULL,
    ftKoopa_SpecialLw_StartAction,
    NULL,
};

HSD_GObjEvent ft_SpecialHi[FTKIND_MAX] = {
    ftMario_SpecialHi_StartAction,
    ftFox_SpecialHi_StartAction,
    ftCaptain_SpecialHi_StartAction,
    ftDonkey_SpecialHi_StartAction,
    ftKirby_SpecialHi_StartAction,
    ftKoopa_SpecialHi_StartAction,
    ftLink_SpecialHi_StartAction,
    ftSeak_SpecialHi_StartAction,
    ftNess_SpecialHi_StartAction,
    ftPeach_SpecialHi_StartAction,
    ftIceClimber_SpecialHi_StartAction,
    NULL,
    ftPikachu_SpecialHi_StartAction,
    ftSamus_SpecialHi_StartAction,
    ftYoshi_SpecialHi_StartAction,
    ftPurin_SpecialHi_StartAction,
    ftMewtwo_SpecialHi_StartAction,
    ftLuigi_SpecialHi_StartAction,
    ftMars_SpecialHi_StartAction,
    ftZelda_SpecialHi_StartAction,
    ftLink_SpecialHi_StartAction,
    ftMario_SpecialHi_StartAction,
    ftFox_SpecialHi_StartAction,
    ftPikachu_SpecialHi_StartAction,
    ftGameWatch_SpecialHi_StartAction,
    ftCaptain_SpecialHi_StartAction,
    ftMars_SpecialHi_StartAction,
    NULL,
    NULL,
    NULL,
    NULL,
    ftKoopa_SpecialHi_StartAction,
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
        lbl_803C5A28, lbl_803C7D9C,
        lbl_803C773C, lbl_803CC020,
        lbl_803CA5B4, lbl_803CF26C,
        lbl_803C82B0, lbl_803CC558,
        lbl_803CCC84, ftPeach_str_arr_Costumes,
        lbl_803CD7C4, lbl_803CDD2C,
        lbl_803CE2A0, lbl_803CE678,
        lbl_803CECFC, lbl_803D0508,
        lbl_803D0F5C, lbl_803D0AB4,
        lbl_803CFA18, lbl_803CFEB0,
        lbl_803D1458, lbl_803D180C,
        lbl_803D1E74, lbl_803D23B4,
        lbl_803D29C8, lbl_803D2E40,
        lbl_803D34A8, lbl_803D40C4,
        lbl_803D4868, lbl_803D3558,
        lbl_803D35D8, lbl_803D3988,
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
    &lbl_803C59D8, &lbl_803C7D8C,
    &lbl_803C772C, &lbl_803CC010,
    &lbl_803CA55C, &lbl_803CF25C,
    &lbl_803C82A0, &lbl_803CC548,
    &lbl_803CCC74, &ftPeach_str_arr_ftDemo,
    &lbl_803CD7B4, &lbl_803CDD1C,
    &lbl_803CE290, &lbl_803CE668,
    &lbl_803CECEC, &lbl_803D04F8,
    &lbl_803D0F4C, &lbl_803D0A64,
    &lbl_803CFA08, &lbl_803CFEA0,
    &lbl_803D1448, &lbl_803D17FC,
    &lbl_803D1E64, &lbl_803D23A4,
    &lbl_803D29B8, &lbl_803D2E30,
    &lbl_803D3498, NULL,
    NULL,          NULL,
    NULL,          &lbl_803D3954,
    NULL,
};

Fighter_DemoGetter lbl_803C24EC[FTKIND_MAX] = {
    ftMario_func_800E0CE0,
    NULL,
    NULL,
    NULL,
    func_800EEBF8,
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
    func_80142640,
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
    func_8014F9A4,
    NULL,
};

Fighter_UnkPtrEvent lbl_803C2570[FTKIND_MAX] = {
    ftMario_func_800E0CAC,
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
    { 0, 16 }, { 0, 14 }, { 0, 14 }, { 0, 14 }, { 0, 18 }, { 0, 14 }, { 0, 14 },
    { 0, 14 }, { 0, 14 }, { 0, 14 }, { 0, 14 }, { 0, 14 }, { 0, 14 }, { 0, 14 },
    { 0, 14 }, { 0, 14 }, { 0, 14 }, { 0, 16 }, { 0, 14 }, { 0, 14 }, { 0, 14 },
    { 0, 14 }, { 0, 14 }, { 0, 14 }, { 0, 14 }, { 0, 14 }, { 0, 14 }, { 0, 14 },
    { 0, 14 }, { 0, 14 }, { 0, 14 }, { 0, 15 }, { 0, 14 },
};

s8 lbl_803C26FC[FTKIND_MAX] = {
    1,  3,  4,  8, 5, 12, 6, 17, 10, 15, 14, 14, 7,  2,  9,  11, 13,
    18, 16, 17, 6, 1, 3,  7, -1, 19, 49, -1, -1, -1, -1, 12, -1,
};
