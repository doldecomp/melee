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
#include <melee/ft/chara/ftSeak/ftseak.h>
#include <melee/ft/chara/ftYoshi/ftyoshi1.h>
#include <melee/ft/chara/ftYoshi/ftyoshi4.h>
#include <melee/ft/chara/ftZakoBoy/ftzakoboy.h>
#include <melee/ft/chara/ftZakoGirl/ftzakogirl.h>
#include <melee/ft/types.h>
#include <sysdolphin/baselib/forward.h>

struct {
    /// Always zero; could be #NULL or the high part of a 64-bit integer.
    int zero;

    /// A count or ASID.
    int count;
} lbl_803C0FC8[FTKIND_MAX] = {
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
    as_table_cfalcon,
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
    ftCFalcon_SpecialAirHi_StartAction,
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
    ftCFalcon_SpecialAirHi_StartAction,
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
    ftCFalcon_SpecialAirLw_StartAction,
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
    ftCFalcon_SpecialAirLw_StartAction,
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
    ftCFalcon_SpecialLw_StartAction,
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
    ftCFalcon_SpecialLw_StartAction,
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
    ftFalcon_SpecialHi_StartAction,
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
    ftFalcon_SpecialHi_StartAction,
    ftMars_SpecialHi_StartAction,
    NULL,
    NULL,
    NULL,
    NULL,
    ftKoopa_SpecialHi_StartAction,
    NULL,
};
