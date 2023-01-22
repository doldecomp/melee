#include <dolphin/mtx/types.h>
#include <melee/ft/chara/ftCaptain/ftCaptain.h>
#include <melee/ft/chara/ftCLink/ftclink.h>
#include <melee/ft/chara/ftCrazyHand/ftcrazyhand.h>
#include <melee/ft/chara/ftDonkey/ftdonkey_callbacks.h>
#include <melee/ft/chara/ftDrMario/ftdrmario.h>
#include <melee/ft/chara/ftEmblem/ftemblem.h>
#include <melee/ft/chara/ftFalco/ftfalco.h>
#include <melee/ft/chara/ftFox/ftfox.h>
#include <melee/ft/chara/ftGameWatch/ftgamewatch.h>
#include <melee/ft/chara/ftGanon/ftganon.h>
#include <melee/ft/chara/ftGigaKoopa/ftgigakoopa.h>
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
#include <melee/ft/chara/ftPurin/ftpurin.h>
#include <melee/ft/chara/ftSamus/ftsamus1.h>
#include <melee/ft/chara/ftSandbag/ftsandbag.h>
#include <melee/ft/chara/ftSeak/ftseak.h>
#include <melee/ft/chara/ftYoshi/ftyoshi1.h>
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
