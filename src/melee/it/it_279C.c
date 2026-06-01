#include "it_279C.h"

#include "it_266F.h"
#include "it_2725.h"
#include "ithitbox.h"
#include "itzako.h"

#include "db/db.h"
#include "ef/efsync.h"
#include "ft/fighter.h"
#include "ft/ft_0892.h"
#include "ft/ftlib.h"
#include "gm/gm_unsplit.h"
#include "it/items/it_2ADA.h"
#include "it/items/it_2E5A.h"
#include "it/items/it_2E6A.h"
#include "it/items/it_2F28.h"
#include "it/items/itarwinglaser.h"
#include "it/items/itcerebi.h"
#include "it/items/itchicorita.h"
#include "it/items/itclimbersblizzard.h"
#include "it/items/itclimbersice.h"
#include "it/items/itclimbersstring.h"
#include "it/items/itclinkmilk.h"
#include "it/items/itcrazyhandbomb.h"
#include "it/items/itdrmariopill.h"
#include "it/items/itentei.h"
#include "it/items/itfire.h"
#include "it/items/itfoxblaster.h"
#include "it/items/itfoxlaser.h"
#include "it/items/itfreezer.h"
#include "it/items/itfushigibana.h"
#include "it/items/itgamewatchbreath.h"
#include "it/items/itgamewatchchef.h"
#include "it/items/itgamewatchfire.h"
#include "it/items/itgamewatchgreenhouse.h"
#include "it/items/itgamewatchjudge.h"
#include "it/items/itgamewatchmanhole.h"
#include "it/items/itgamewatchpanic.h"
#include "it/items/itgamewatchparachute.h"
#include "it/items/itgamewatchrescue.h"
#include "it/items/itgamewatchturtle.h"
#include "it/items/itgreatfoxlaser.h"
#include "it/items/ithassam.h"
#include "it/items/itheiho.h"
#include "it/items/ithinoarashi.h"
#include "it/items/ithitodeman.h"
#include "it/items/ithouou.h"
#include "it/items/itkabigon.h"
#include "it/items/itkamex.h"
#include "it/items/itkirbycutterbeam.h"
#include "it/items/itkirbygamewatchchefpan.h"
#include "it/items/itkirbyhammer.h"
#include "it/items/itkireihana.h"
#include "it/items/itklap.h"
#include "it/items/itkoopaflame.h"
#include "it/items/itkyasarin.h"
#include "it/items/itkyasarinegg.h"
#include "it/items/itleadead.h"
#include "it/items/itlikelike.h"
#include "it/items/itlinkbomb.h"
#include "it/items/itlinkbow.h"
#include "it/items/itlinkhookshot.h"
#include "it/items/itlizardon.h"
#include "it/items/itlucky.h"
#include "it/items/itlugia.h"
#include "it/items/itluigifireball.h"
#include "it/items/itmaril.h"
#include "it/items/itmariocape.h"
#include "it/items/itmariofireball.h"
#include "it/items/itmarumine.h"
#include "it/items/itmasterhandbullet.h"
#include "it/items/itmasterhandlaser.h"
#include "it/items/itmatadogas.h"
#include "it/items/itmato.h"
#include "it/items/itmetamon.h"
#include "it/items/itmew.h"
#include "it/items/itmewtwodisable.h"
#include "it/items/itmewtwoshadowball.h"
#include "it/items/itnessbat.h"
#include "it/items/itnesspkfire.h"
#include "it/items/itnesspkfirepillar.h"
#include "it/items/itnesspkflash.h"
#include "it/items/itnesspkflashexplode.h"
#include "it/items/itnesspkthunderball.h"
#include "it/items/itnesspkthundertrail.h"
#include "it/items/itnessyoyo.h"
#include "it/items/itnokonoko.h"
#include "it/items/itoctarock.h"
#include "it/items/itoctarockstone.h"
#include "it/items/itoldkuri.h"
#include "it/items/itoldottosea.h"
#include "it/items/itpatapata.h"
#include "it/items/itpeachexplode.h"
#include "it/items/itpeachparasol.h"
#include "it/items/itpeachtoad.h"
#include "it/items/itpeachtoadspore.h"
#include "it/items/itpeachturnip.h"
#include "it/items/itpikachuthunder.h"
#include "it/items/itpikachutjoltair.h"
#include "it/items/itpikachutjoltground.h"
#include "it/items/itpippi.h"
#include "it/items/itporygon2.h"
#include "it/items/itraikou.h"
#include "it/items/itsamusbomb.h"
#include "it/items/itsamuschargeshot.h"
#include "it/items/itsamusgrapple.h"
#include "it/items/itsamusmissile.h"
#include "it/items/itseakchain.h"
#include "it/items/itseakneedleheld.h"
#include "it/items/itseakneedlethrown.h"
#include "it/items/itseakvanish.h"
#include "it/items/itsonans.h"
#include "it/items/itsuikun.h"
#include "it/items/itthunder.h"
#include "it/items/ittincle.h"
#include "it/items/ittogepy.h"
#include "it/items/ittools.h"
#include "it/items/ittosakinto.h"
#include "it/items/itunknown.h"
#include "it/items/itwhispyapple.h"
#include "it/items/itwhitebea.h"
#include "it/items/ityoshieggthrow.h"
#include "it/items/ityoshistar.h"
#include "it/items/itzeldadinfire.h"
#include "it/items/itzeldadinfireexplode.h"
#include "it/items/itzgshell.h"
#include "it/items/itzrshell.h"
#include "items/itcoin.h"
#include "items/itfoxillusion.h"
#include "items/itlinkarrow.h"
#include "items/itlinkboomerang.h"
#include "items/ityoshiegglay.h"
#include "lb/lbvector.h"
#include "pl/plattack.h"
#include "pl/plbonuslib.h"
#include "pl/plstale.h"
#include "pl/pltrick.h"

#define IT_M_PI_2 1.5707963267948966

const Quaternion it_803B8588 = { 0.0f, 0.0f, 0.0f, 0.0f };
const Quaternion it_803B8598 = { 0.0f, 0.0f, 0.0f, 0.0f };

/// Pokemon items
struct sdata_ItemGXLink it_803F2310[47] = {
    it_8026EECC, it_8026EECC, it_8026EECC, it_8026EECC, it_8026EECC,
    it_8026EECC, it_8026EECC, it_8026EECC, it_8026EECC, it_8026EECC,
    it_8026EECC, it_8026EECC, it_8026EECC, it_8026EECC, it_8026EECC,
    it_8026EECC, it_8026EECC, it_8026EECC, it_8026EECC, it_8026EECC,
    it_8026EECC, it_8026EECC, it_8026EECC, it_8026EECC, it_8026EECC,
    it_8026EECC, it_8026EECC, it_8026EECC, it_8026EECC, it_8026EECC,
    it_8026EECC, it_8026EECC, it_8026EECC, it_8026EECC, it_8026EECC,
    it_8026EECC, it_8026EECC, it_8026EECC, it_8026EECC, it_8026EECC,
    it_8026EECC, it_8026EECC, it_8026EECC, it_8026EECC, it_8026EECC,
    it_8026EECC, it_8026EECC,
};

ItemLogicTable it_803F23CC[ARRAY_SIZE(it_803F2310)] = {
    {
        // Tosakinto (Goldeen)
        it_803F7A48,
        it_802C8F4C,
        itTosakinto_Logic0_Destroyed,
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
        it_802C8FC4,
    },
    {
        // Chicorita
        it_803F7A98,
        it_802C9588,
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
        itChicorita_Logic1_EvtUnk,
    },
    {
        // Kabigon (Snorlax)
        it_803F7AD8,
        it_802C9D40,
        itKabigon_Logic2_Destroyed,
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
        it_802C9E24,
    },
    {
        // Kamex (Blastoise)
        it_803F7B08,
        it_802CA49C,
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
        it_802CA538,
    },
    {
        // Matadogas (Weezing)
        it_803F7B58,
        it_802CAFD4,
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
        it_802CB0F8,
    },
    {
        // Lizardon (Charizard)
        it_803F7BC0,
        it_802CB8AC,
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
        it_802CB940,
    },
    {
        // Fire (Moltres)
        it_803F7C10,
        itFire_Logic6_Spawned,
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
        itFire_Logic6_EvtUnk,
    },
    {
        // Thunder (Zapdos)
        it_803F7C40,
        itThunder_Logic7_Spawned,
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
        it_802CCB14,
    },
    {
        // Freezer (Articuno)
        it_803F7C70,
        itFreezer_802CCF9C,
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
        itFreezer_802CD000,
    },
    {
        // Sonans (Wobbuffet)
        it_803F7CA0,
        it_802CD44C,
        NULL,
        NULL,
        NULL,
        NULL,
        itSonans_Logic9_DmgDealt,
        it_802CD7D4,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        it_802CD4DC,
    },
    {
        // Hassam (Scizor)
        it_803F7CF8,
        itHassam_802CDBE0,
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
        itHassam_802CDC60,
    },
    {
        // Unknown (Unown)
        it_803F7D60,
        it_802CE710,
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
        it_802CE7D0,
    },
    {
        // Entei
        it_803F7DC8,
        it_802CF3E0,
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
        it_802CF450,
    },
    {
        // Raikou
        it_803F7DE8,
        it_802CF814,
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
        it_802CF884,
    },
    {
        // Suikun (Suicune)
        it_803F7E08,
        itSuikun_Logic14_Spawned,
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
        it_802CFCB8,
    },
    {
        // Kireihana (Bellossom)
        it_803F7E28,
        itKireihana_Logic15_Spawned,
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
        itKireihana_Logic15_EvtUnk,
    },
    {
        // Marumine (Electrode)
        it_803F7E78,
        itMarumine_Logic16_Spawned,
        NULL,
        it_802D0D18,
        it_802D0E30,
        it_802D0E90,
        it_802D0AD0,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        it_802D0AB0,
    },
    {
        // Lugia
        it_803F7EE8,
        it_2725_Logic17_Spawned,
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
        itLugia_Logic17_EvtUnk,
    },
    {
        // Houou (Ho-oh)
        it_803F7F58,
        it_2725_Logic18_Spawned,
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
        it_802D25BC,
    },
    {
        // Metamon (Ditto)
        it_803F7FC8,
        it_802D3008,
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
        itMetamon_Logic19_EvtUnk,
    },
    {
        // Pippi (Clefairy)
        it_803F7FF8,
        itPippi_Logic20_Spawned,
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
        it_802D32DC,
    },
    {
        // Togepy
        it_803F8058,
        itTogepy_Logic21_Spawned,
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
        itTogepy_Logic21_EvtUnk,
    },
    {
        // Mew
        it_803F80C8,
        itMew_Logic22_Spawned,
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
        it_802D3B6C,
    },
    {
        // Cerebi
        it_803F80F8,
        itCerebi_Logic23_Spawned,
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
        it_802D3F4C,
    },
    {
        // Hitodeman (Staryu)
        it_803F8128,
        it_2725_Logic24_Spawned,
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
        it_802D43B0,
    },
    {
        // Lucky (Chansey)
        it_803F8190,
        it_802D5050,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        it_802D5648,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        it_802D56F0,
    },
    {
        // Porygon2
        it_803F8250,
        itPorygon2_Logic26_Spawned,
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
        it_802D5CD8,
    },
    {
        // Hinoarashi (Cyndaquil)
        it_803F8270,
        it_802D5CF8,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        it_2725_Logic27_DmgReceived,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        it_802D61A8,
    },
    {
        // Maril
        it_803F82B0,
        itMaril_Logic28_Spawned,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        it_802D6F00,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        it_802D6FB0,
    },
    {
        // Fushigibana (Venusaur)
        it_803F82F0,
        itFushigibana_Logic29_Spawned,
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
        itOldKuri_Logic29_EvtUnk,
    },
    {
        // Chicorita leaf
        it_803F7AC8,
        itChicoritaLeaf_Logic30_Spawned,
        NULL,
        NULL,
        NULL,
        NULL,
        itChicoritaLeaf_Logic30_HitShield,
        NULL,
        NULL,
        itChicoritaLeaf_Logic30_Reflected,
        itChicoritaLeaf_Logic30_HitShield,
        itChicoritaLeaf_Logic30_HitShield,
        NULL,
        itChicoritaLeaf_Logic30_HitShield,
        itChicoritaLeaf_Logic30_EvtUnk,
    },
    {
        // Kamex hydro pump
        it_803F7B48,
        it_2725_Logic31_Spawned,
        NULL,
        NULL,
        NULL,
        NULL,
        itKamex_Logic31_DmgDealt,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        itKamex_Logic31_HitShield,
        itKamex_Logic31_EvtUnk,
    },
    {
        // Matadogas gas 1
        it_803F7BB0,
        it_2725_Logic32_Spawned,
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
        itMatadogas_Logic33_EvtUnk,
    },
    {
        // Matadogas gas 2
        it_803F7BB0,
        it_2725_Logic33_Spawned,
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
        itMatadogas_Logic33_EvtUnk,
    },
    {
        // Lizardon flame 1
        it_803F7C00,
        itLizardon_Logic34_Spawned,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        itLizardon_Logic37_Reflected,
        NULL,
        itLizardon_Logic37_Absorbed,
        NULL,
        itLizardon_Logic37_HitShield,
        itLizardon_Logic37_EvtUnk,
    },
    {
        // Lizardon flame 2
        it_803F7C00,
        itLizardon_Logic35_Spawned,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        itLizardon_Logic37_Reflected,
        NULL,
        itLizardon_Logic37_Absorbed,
        NULL,
        itLizardon_Logic37_HitShield,
        itLizardon_Logic37_EvtUnk,
    },
    {
        // Lizardon flame 3
        it_803F7C00,
        itLizardon_Logic36_Spawned,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        itLizardon_Logic37_Reflected,
        NULL,
        itLizardon_Logic37_Absorbed,
        NULL,
        itLizardon_Logic37_HitShield,
        itLizardon_Logic37_EvtUnk,
    },
    {
        // Lizardon flame 4
        it_803F7C00,
        itLizardon_Logic37_Spawned,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        itLizardon_Logic37_Reflected,
        NULL,
        itLizardon_Logic37_Absorbed,
        NULL,
        itLizardon_Logic37_HitShield,
        itLizardon_Logic37_EvtUnk,
    },
    {
        // Unknown swarm (mini-unowns)
        &it_803F7D60[3],
        it_2725_Logic38_Spawned,
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
        itUnknown_Logic38_EvtUnk,
    },
    {
        // Lugia aeroblast 1
        it_803F7F48,
        itLugia_Logic39_Spawned,
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
        it_802D23D4,
    },
    {
        // Lugia aeroblast 2
        it_803F7F48,
        itLugia_Logic40_Spawned,
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
        it_802D23D4,
    },
    {
        // Lugia aeroblast 3
        it_803F7F48,
        itLugia_Logic41_Spawned,
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
        it_802D23D4,
    },
    {
        // Houou sacred fire
        it_803F7FB8,
        it_2725_Logic42_Spawned,
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
        it_802D2ED0,
    },
    {
        // Hitodeman star
        it_803F8180,
        it_2725_Logic43_Spawned,
        NULL,
        NULL,
        NULL,
        NULL,
        it_802D4EF4,
        NULL,
        NULL,
        it_802D4F28,
        NULL,
        itHitodeman_Logic43_Absorbed,
        it_802D4F08,
        it_802D4F50,
        it_802D4F58,
    },
    {
        // Lucky egg
        it_803F8200,
        itLucky_Logic44_Spawned,
        NULL,
        itLucky_Logic44_PickedUp,
        itLucky_Logic44_Dropped,
        NULL,
        NULL,
        NULL,
        itLucky_Logic44_EnteredAir,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        itLucky_Logic44_EvtUnk,
    },
    {
        // Hinoarashi flame
        it_803F82A0,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        it_802D6808,
        NULL,
        NULL,
        it_802D6810,
        it_802D6830,
        it_802D6838,
        it_802D6840,
        it_802D6848,
        it_802D6850,
    },
    {
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
    },
};

ItemKind it_803F2ED0[22] = {
    // Common Pokemon
    Pokemon_Tosakinto,      Pokemon_Chicorita,
    Pokemon_Kabigon,        Pokemon_Kamex,
    Pokemon_Matadogas,      Pokemon_Lizardon,
    Pokemon_Sonans,         Pokemon_Hassam,
    Pokemon_Unknown,        Pokemon_Kireihana,
    Pokemon_Marumine,       Pokemon_Metamon,
    Pokemon_Pippi,          Pokemon_Togepy,
    Pokemon_Hitodeman,      Pokemon_Lucky,
    Pokemon_Porygon2,       Pokemon_Hinoarashi,
    Pokemon_Maril,          Pokemon_Fushigibana,
    Pokemon_Chicorita_Leaf, 0x00,
};

/// Character-specific items
struct sdata_ItemGXLink it_803F2F28[118] = {
    it_8026EECC, it_8026EECC, it_8026EECC, it_8026EECC, it_8026EECC,
    it_8026EECC, it_8026EECC, it_8026EECC, it_8026EECC, it_8026EECC,

    it_8026EECC, it_8026EECC, it_8026EECC, it_8029CD18, it_8029CD18,

    it_8026EECC, it_8026EECC, it_8029FDDC, it_8029FDDC, it_8026EECC,
    it_8026EECC, it_802A7D8C, it_802A7D8C, it_8026EECC, it_8026EECC,

    it_8026EECC, it_8026EECC, it_8026EECC, it_8026EECC, it_8026EECC,
    it_8026EECC, it_8026EECC, it_8026EECC, it_8026EECC, it_8026EECC,
    it_8026EECC, it_8026EECC, it_8026EECC, it_8026EECC, it_8026EECC,
    it_8026EECC, it_8026EECC, it_8026EECC, it_8026EECC, it_8026EECC,
    it_8026EECC, it_8026EECC, it_8026EECC, it_8026EECC, it_8026EECC,
    it_8026EECC, it_8026EECC, it_8026EECC, it_8026EECC, it_8026EECC,
    it_8026EECC, it_8026EECC, it_8026EECC, it_8026EECC, it_8026EECC,
    it_8026EECC, it_8026EECC, it_8026EECC, it_8026EECC, it_8026EECC,
    it_8026EECC, it_8026EECC, it_8026EECC, it_8026EECC, it_8026EECC,
    it_8026EECC, it_8026EECC, it_8026EECC, it_8026EECC, it_8026EECC,
    it_8026EECC, it_8026EECC, it_8026EECC, it_8026EECC, it_8026EECC,
    it_8026EECC, it_8026EECC, it_8026EECC, it_8026EECC, it_8026EECC,
    it_8026EECC, it_8026EECC, it_8026EECC, it_8026EECC, it_8026EECC,
    it_8026EECC, it_8026EECC, it_8026EECC, it_8026EECC, it_8026EECC,

    it_8026EECC, it_8026EECC, it_802A7D8C, it_802A7D8C, it_8026EECC,

    it_8026EECC, it_8026EECC, it_8026EECC, it_8026EECC, it_8026EECC,
    it_8026EECC, it_8026EECC, it_8026EECC, it_8026EECC, it_8026EECC,
    it_8026EECC, it_8026EECC, it_8026EECC, it_8026EECC, it_8026EECC,

    it_8026EECC, it_802F13B4, it_8026EECC,
};

struct ItemLogicTable it_803F3100[ARRAY_SIZE(it_803F2F28)] = {
    {
        // Kuriboh
        it_803F8320,
        it_802D73F0,
        it_2725_Logic9_Destroyed,
        itOldKuri_Logic0_PickedUp,
        it_2725_Logic0_Dropped,
        it_2725_Logic0_Thrown,
        NULL,
        it_2725_Logic0_DmgReceived,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        // Leadead
        it_803F8EB0,
        it_802E8BCC,
        itLeadead_Logic1_Destroyed,
        itLeadead_Logic1_PickedUp,
        itLeadead_Logic1_Dropped,
        itLeadead_Logic1_Thrown,
        NULL,
        it_802E8CD8,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        // Octarock
        it_803F8B48,
        it_802E4A44,
        it_2725_Logic9_Destroyed,
        itOctarock_Logic2_PickedUp,
        itOctarock_Logic2_Dropped,
        itOctarock_Logic2_Thrown,
        NULL,
        it_802E4B00,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        it_802E5AA4,
    },
    {
        // Ottosea
        it_803F89C8,
        it_802E2470,
        it_2725_Logic3_Destroyed,
        it_802E31F8,
        it_802E32B4,
        it_802E3314,
        NULL,
        it_2725_Logic8_DmgReceived,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        it_802E3784,
    },
    {
        // Octarock stone
        it_803F8E90,
        itOctarockstone_802E878C,
        NULL,
        NULL,
        NULL,
        NULL,
        itOctarockstone_Logic4_DmgDealt,
        NULL,
        NULL,
        itOctarockstone_Logic4_Reflected,
        itOctarockstone_Logic4_Clanked,
        itOctarockstone_Logic4_Absorbed,
        itOctarockstone_Logic4_ShieldBounced,
        itOctarockstone_Logic4_HitShield,
        itOctarockstone_802E89B0,
    },
    {
        // Mario fireball
        it_803F6788,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        itMarioFireball_Logic87_DmgDealt,
        NULL,
        NULL,
        itMarioFireball_Logic87_Reflected,
        itMarioFireball_Logic87_Clanked,
        itMarioFireball_Logic87_Absorbed,
        itMarioFireball_Logic87_ShieldBounced,
        itMarioFireball_Logic87_HitShield,
        itMarioFireball_Logic87_EvtUnk,
    },
    {
        // Dr Mario pill
        it_803F75D0,
        NULL,
        NULL,
        itDrMarioPill_PickedUp,
        NULL,
        NULL,
        itDrMarioPill_DmgDealt,
        NULL,
        NULL,
        itDrMarioPill_Reflected,
        itDrMarioPill_Clanked,
        itDrMarioPill_Absorbed,
        itDrMarioPill_ShieldBounced,
        itDrMarioPill_HitShield,
        itDrMarioPill_EvtUnk,
    },
    {
        // Kirby cutter beam
        it_803F6798,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        itKirbyCutterBeam_Logic7_DmgDealt,
        NULL,
        NULL,
        it_2725_Logic7_Reflected,
        itKirbyCutterBeam_Logic7_Clanked,
        itKirbyCutterBeam_Logic7_Absorbed,
        it_2725_Logic7_ShieldBounced,
        itKirbyCutterBeam_Logic7_HitShield,
        it_8029C4B4,
    },
    {
        // Kirby hammer
        it_803F6C98,
        NULL,
        itKirbyHammer_Logic8_Destroyed,
        itKirbyHammer_Logic8_PickedUp,
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
        it_802ADDB0,
    },
    {
        it_803F6C88,
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
        it_802ADBE4,
    },
    {
        it_803F9470,
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
        it_802F2BDC,
    },
    {
        // Fox laser
        it_803F67D0,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        itFoxLaser_Logic94_Clanked,
        NULL,
        NULL,
        itFoxLaser_Logic94_Reflected,
        itFoxLaser_Logic94_Clanked,
        itFoxLaser_Logic94_Absorbed,
        itFoxLaser_Logic94_ShieldBounced,
        itFoxLaser_Logic94_HitShield,
        itFoxLaser_Logic94_EvtUnk,
    },
    {
        // Falco laser
        it_803F67D0,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        itFoxLaser_Logic94_Clanked,
        NULL,
        NULL,
        itFoxLaser_Logic94_Reflected,
        itFoxLaser_Logic94_Clanked,
        itFoxLaser_Logic94_Absorbed,
        itFoxLaser_Logic94_ShieldBounced,
        itFoxLaser_Logic94_HitShield,
        itFoxLaser_Logic94_EvtUnk,
    },
    {
        // Fox illusion
        it_803F6818,
        NULL,
        itFoxIllusion_Logic14_Destroyed,
        NULL,
        NULL,
        NULL,
        itFoxIllusion_Logic14_DmgDealt,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        it_8029D948,
    },
    {
        // Falco phantasm
        it_803F6818,
        NULL,
        itFoxIllusion_Logic14_Destroyed,
        NULL,
        NULL,
        NULL,
        itFoxIllusion_Logic14_DmgDealt,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        it_8029D948,
    },
    {
        // Link bomb
        it_803F6888,
        NULL,
        NULL,
        it_8029DEB0,
        it_8029EC34,
        it_8029E5D0,
        it_8029F960,
        itLinkBomb_Logic16_DmgReceived,
        itLinkBomb_Logic16_EnteredAir,
        itLinkBomb_Logic16_Reflected,
        NULL,
        NULL,
        itLinkBomb_Logic16_ShieldBounced,
        itLinkBomb_Logic16_HitShield,
        it_8029FD84,
    },
    {
        // Young Link bomb
        it_803F6888,
        NULL,
        NULL,
        it_8029DEB0,
        it_8029EC34,
        it_8029E5D0,
        it_8029F960,
        itLinkBomb_Logic16_DmgReceived,
        itLinkBomb_Logic16_EnteredAir,
        itLinkBomb_Logic16_Reflected,
        NULL,
        NULL,
        itLinkBomb_Logic16_ShieldBounced,
        itLinkBomb_Logic16_HitShield,
        it_8029FD84,
    },
    {
        // Link boomerang
        it_803F6920,
        NULL,
        itLinkBoomerang_Logic18_Destroyed,
        it_802A0E70,
        it_802A0F84,
        it_802A0F88,
        it_802A1F08,
        NULL,
        NULL,
        it_802A20E8,
        it_802A1FA8,
        itLinkBoomerang_Logic18_Absorbed,
        it_802A2320,
        it_802A2288,
        it_802A23CC,
    },
    {
        // Young Link boomerang
        it_803F6920,
        NULL,
        itLinkBoomerang_Logic18_Destroyed,
        it_802A0E70,
        it_802A0F84,
        it_802A0F88,
        it_802A1F08,
        NULL,
        NULL,
        it_802A20E8,
        it_802A1FA8,
        itLinkBoomerang_Logic18_Absorbed,
        it_802A2320,
        it_802A2288,
        it_802A23CC,
    },
    {
        // Link hookshot
        it_803F6998,
        it_802A2418,
        NULL,
        itLinkHookshot_Logic20_PickedUp,
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
        it_802A7D40,
    },
    {
        // Young Link hookshot
        it_803F6998,
        NULL,
        NULL,
        itLinkHookshot_Logic20_PickedUp,
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
        it_802A7D40,
    },
    {
        // Link arrow
        it_803F6A28,
        NULL,
        itLinkArrow_Logic98_Destroyed,
        itLinkArrow_Logic98_PickedUp,
        NULL,
        NULL,
        itLinkArrow_Logic98_DmgDealt,
        NULL,
        NULL,
        itLinkArrow_Logic98_Reflected,
        itLinkArrow_Logic98_Clanked,
        NULL,
        NULL,
        itLinkArrow_Logic98_HitShield,
        itLinkArrow_Logic98_EvtUnk,
    },
    {
        // Young Link arrow
        it_803F6A28,
        NULL,
        itLinkArrow_Logic98_Destroyed,
        itLinkArrow_Logic98_PickedUp,
        NULL,
        NULL,
        itLinkArrow_Logic98_DmgDealt,
        NULL,
        NULL,
        itLinkArrow_Logic98_Reflected,
        itLinkArrow_Logic98_Clanked,
        NULL,
        NULL,
        itLinkArrow_Logic98_HitShield,
        itLinkArrow_Logic98_EvtUnk,
    },
    {
        // Ness PK fire
        it_803F6B28,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        it_2725_Logic23_DmgDealt,
        NULL,
        NULL,
        itNessPKFire_Logic23_Reflected,
        it_2725_Logic23_Clanked,
        itNessPKFire_Logic23_Absorbed,
        it_2725_Logic23_ShieldBounced,
        itNessPKFire_Logic23_HitShield,
        it_802AA474,
    },
    {
        // Ness PK fire pillar
        it_803F6B60,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        itNesspkfirepillar_Logic24_DmgReceived,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        itNesspkfirepillar_Logic24_EvtUnk,
    },
    {
        // Ness PK flash
        it_803F6B70,
        NULL,
        it_2725_Logic102_Destroyed,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        itNesspkflash_Logic102_Reflected,
        itNesspkflash_Logic102_Clanked,
        itNesspkflash_Logic102_Absorbed,
        NULL,
        NULL,
        itNesspkflash_Logic102_EvtUnk,
    },
    {
        // Ness PK thunder ball
        it_803F6BC8,
        NULL,
        it_802AB90C,
        NULL,
        NULL,
        NULL,
        itNessPKThunderball_Logic26_DmgDealt,
        NULL,
        NULL,
        it_802AC098,
        it_802AC074,
        it_802AC338,
        it_802AC35C,
        it_802AC3F8,
        it_802AC41C,
    },
    {
        // Ness PK thunder trail 1
        it_803F6C08,
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
    },
    {
        // Ness PK thunder trail 2
        it_803F6C08,
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
    },
    {
        // Ness PK thunder trail 3
        it_803F6C08,
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
    },
    {
        // Ness PK thunder trail 4
        it_803F6C08,
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
    },
    {
        // Fox blaster
        it_803F6CA8,
        NULL,
        NULL,
        itFoxBlaster_Logic96_PickedUp,
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
        itFoxBlaster_Logic96_EvtUnk,
    },
    {
        // Falco blaster
        it_803F6CA8,
        NULL,
        NULL,
        itFoxBlaster_Logic96_PickedUp,
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
        itFoxBlaster_Logic96_EvtUnk,
    },
    {
        // Link bow
        it_803F6E98,
        NULL,
        itLinkBow_Logic100_Destroyed,
        itLinkBow_Logic100_PickedUp,
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
        itLinkBow_Logic100_EvtUnk,
    },
    {
        // Young Link bow
        it_803F6E98,
        NULL,
        itLinkBow_Logic100_Destroyed,
        itLinkBow_Logic100_PickedUp,
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
        itLinkBow_Logic100_EvtUnk,
    },
    {
        // Ness PK flush explode
        it_803F6F40,
        NULL,
        it_2725_Logic103_Destroyed,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        itNessPKFlashExplode_Logic103_Clanked,
        itNessPKFlashExplode_Logic103_Absorbed,
        itNessPKFlashExplode_Logic103_ShieldBounced,
        itNessPKFlashExplode_Logic103_HitShield,
        itNessPKFlashExplode_Logic103_EvtUnk,
    },
    {
        // Sheik needle thrown
        it_803F6F50.states,
        NULL,
        itSeakNeedleThrown_Logic109_Destroyed,
        NULL,
        NULL,
        NULL,
        it_2725_Logic109_DmgDealt,
        it_2725_Logic109_DmgReceived,
        NULL,
        it_2725_Logic109_Reflected,
        it_2725_Logic109_Clanked,
        NULL,
        it_2725_Logic109_ShieldBounced,
        it_2725_Logic109_HitShield,
        itSeakNeedleThrown_Logic109_EvtUnk,
    },
    {
        // Sheik needle held
        it_803F70A8,
        NULL,
        NULL,
        itSeakNeedleHeld_Logic110_PickedUp,
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
        itSeakNeedleHeld_Logic110_EvtUnk,
    },
    {
        // Pikachu thunder
        it_803F70C8,
        NULL,
        it_2725_Logic39_Destroyed,
        NULL,
        NULL,
        NULL,
        itPikachuThunder_Logic39_DmgDealt,
        NULL,
        NULL,
        NULL,
        itPikachuThunder_Logic39_Clanked,
        itPikachuThunder_Logic39_Absorbed,
        NULL,
        itPikachuThunder_Logic39_HitShield,
        itPikachuThunder_Logic39_EvtUnk,
    },
    {
        // Pichu thunder
        it_803F70C8,
        NULL,
        it_2725_Logic39_Destroyed,
        NULL,
        NULL,
        NULL,
        itPikachuThunder_Logic39_DmgDealt,
        NULL,
        NULL,
        NULL,
        itPikachuThunder_Logic39_Clanked,
        itPikachuThunder_Logic39_Absorbed,
        NULL,
        itPikachuThunder_Logic39_HitShield,
        itPikachuThunder_Logic39_EvtUnk,
    },
    {
        // Mario cape
        it_803F70F8,
        NULL,
        itMarioCape_Logic41_Destroyed,
        it_2725_Logic41_PickedUp,
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
        it_802B2870,
    },
    {
        // Dr Mario cape
        it_803F70F8,
        NULL,
        itMarioCape_Logic41_Destroyed,
        it_2725_Logic41_PickedUp,
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
        it_802B2870,
    },
    {
        // Sheik vanish
        it_803F70B8,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        itSeakVanish_Logic42_DmgDealt,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        it_802B1DCC,
    },
    {
        // Yoshi egg throw
        it_803F7118,
        NULL,
        NULL,
        itYoshiEggThrow_Logic43_PickedUp,
        NULL,
        NULL,
        it_802B2C04,
        NULL,
        NULL,
        it_802B2E5C,
        it_2725_Logic43_Clanked,
        NULL,
        it_802B2F88,
        it_802B2E7C,
        it_802B2FA8,
    },
    {
        // Yoshi egg lay
        it_803F94A0,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        it_27CF_Logic114_DmgReceived,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        it_27CF_Logic114_EvtUnk,
    },
    {
        // Yoshi star
        it_803F7158,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        it_802B309C,
        NULL,
        NULL,
        it_802B314C,
        it_802B30C0,
        it_802B3108,
        it_802B312C,
        it_802B30E4,
        it_802B3348,
    },
    {
        // Pikachu tjolt ground
        it_803F7190,
        NULL,
        it_2725_Logic106_Destroyed,
        NULL,
        NULL,
        NULL,
        it_2725_Logic106_DmgDealt,
        NULL,
        NULL,
        it_2725_Logic106_Reflected,
        it_2725_Logic106_Clanked,
        it_2725_Logic106_Absorbed,
        it_2725_Logic106_ShieldBounced,
        it_2725_Logic106_HitShield,
        itPikachuTJoltGround_Logic106_EvtUnk,
    },
    {
        // Pikachu tjolt air
        it_803F71D8,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        it_2725_Logic107_DmgDealt,
        NULL,
        NULL,
        it_2725_Logic107_Reflected,
        it_2725_Logic107_Clanked,
        it_2725_Logic107_Absorbed,
        it_2725_Logic107_ShieldBounced,
        it_2725_Logic107_HitShield,
        itPikachuTJoltAir_Logic107_EvtUnk,
    },
    {
        // Pichu tjolt ground
        it_803F7190,
        NULL,
        it_2725_Logic106_Destroyed,
        NULL,
        NULL,
        NULL,
        it_2725_Logic106_DmgDealt,
        NULL,
        NULL,
        it_2725_Logic106_Reflected,
        it_2725_Logic106_Clanked,
        it_2725_Logic106_Absorbed,
        it_2725_Logic106_ShieldBounced,
        it_2725_Logic106_HitShield,
        itPikachuTJoltGround_Logic106_EvtUnk,
    },
    {
        // Pichu tjolt air
        it_803F71D8,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        it_2725_Logic107_DmgDealt,
        NULL,
        NULL,
        it_2725_Logic107_Reflected,
        it_2725_Logic107_Clanked,
        it_2725_Logic107_Absorbed,
        it_2725_Logic107_ShieldBounced,
        it_2725_Logic107_HitShield,
        itPikachuTJoltAir_Logic107_EvtUnk,
    },
    {
        // Samus bomb
        it_803F7220,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        itSamusBomb_Logic50_DmgDealt,
        NULL,
        itSamusBomb_Logic50_EnteredAir,
        it_2725_Logic50_Reflected,
        itSamusBomb_Logic50_Clanked,
        NULL,
        itSamusBomb_Logic50_ShieldBounced,
        itSamusBomb_Logic50_HitShield,
        itSamusBomb_Logic50_EvtUnk,
    },
    {
        // Samus charge shot
        it_803F7288,
        NULL,
        it_2725_Logic108_Destroyed,
        it_2725_Logic108_PickedUp,
        NULL,
        NULL,
        itSamusChargeshot_Logic108_DmgDealt,
        NULL,
        NULL,
        it_2725_Logic108_Reflected,
        itSamusChargeshot_Logic108_Clanked,
        itSamusChargeshot_Logic108_Absorbed,
        it_2725_Logic108_ShieldBounced,
        itSamusChargeshot_Logic108_HitShield,
        itSamusChargeshot_Logic108_EvtUnk,
    },
    {
        // Samus missile
        it_803F7340,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        it_2725_Logic52_DmgDealt,
        NULL,
        NULL,
        it_2725_Logic52_Reflected,
        it_2725_Logic52_Clanked,
        NULL,
        it_2725_Logic52_ShieldBounced,
        it_2725_Logic52_HitShield,
        it_2725_Logic52_EvtUnk,
    },
    {
        // Samus grapple beam
        it_803F73A8,
        itSamusGrapple_Logic53_Spawned,
        NULL,
        itSamusGrapple_Logic53_PickedUp,
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
        itSamusGrapple_Logic53_EvtUnk,
    },
    {
        // Sheik chain
        it_803F7438,
        NULL,
        NULL,
        it_2725_Logic54_PickedUp,
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
        itSeakChain_Logic54_EvtUnk,
    },
    {
        // Peach explode
        it_803F7488,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        itPeachExplode_Logic55_DmgDealt,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        itPeachExplode_Logic55_EvtUnk,
    },
    {
        // Peach turnip
        it_803F74A8,
        NULL,
        itPeachTurnip_Logic56_Destroyed,
        itPeachTurnip_Logic56_PickedUp,
        itPeachTurnip_Logic56_Dropped,
        itPeachTurnip_Logic56_Thrown,
        itPeachTurnip_Logic56_DmgDealt,
        NULL,
        NULL,
        itPeachTurnip_Logic56_Reflected,
        itPeachTurnip_Logic56_Clanked,
        NULL,
        itPeachTurnip_Logic56_ShieldBounced,
        itPeachTurnip_Logic56_HitShield,
        itPeachTurnip_Logic56_EvtUnk,
    },
    {
        // Bowser flame
        ItemStateTable_KoopaFlame,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        itKoopaFlame_Logic111_DmgDealt,
        NULL,
        NULL,
        itKoopaFlame_Logic111_Reflected,
        itKoopaFlame_Logic111_Clanked,
        itKoopaFlame_Logic111_Absorbed,
        itKoopaFlame_Logic111_ShieldBounced,
        itKoopaFlame_Logic111_HitShield,
        itKoopaFlame_Logic111_EvtUnk,
    },
    {
        // Ness bat
        it_803F6C68,
        NULL,
        NULL,
        it_2725_Logic58_PickedUp,
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
        itNessBat_Logic58_EvtUnk,
    },
    {
        // Ness yo-yo
        it_803F7558,
        NULL,
        NULL,
        itNessYoyo_Logic59_PickedUp,
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
        it_2725_Logic59_EvtUnk,
    },
    {
        // Peach parasol
        it_803F74F8,
        NULL,
        itPeachParasol_Logic60_Destroyed,
        itPeachParasol_Logic60_PickedUp,
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
        itPeachParasol_Logic60_EvtUnk,
    },
    {
        // Peach toad
        it_803F7528,
        NULL,
        itPeachToad_Logic91_Destroyed,
        itPeachToad_Logic91_PickedUp,
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
        itPeachToad_Logic91_EvtUnk,
    },
    {
        // Luigi fireball
        it_803F75C0,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        itLuigiFireball_Logic89_DmgDealt,
        NULL,
        NULL,
        itLuigiFireball_Logic89_Reflected,
        itLuigiFireball_Logic89_Clanked,
        itLuigiFireball_Logic89_Absorbed,
        itLuigiFireball_Logic89_ShieldBounced,
        itLuigiFireball_Logic89_HitShield,
        itLuigiFireball_Logic89_EvtUnk,
    },
    {
        // Ice Climbers ice
        it_803F7668,
        NULL,
        it_2725_Logic90_Destroyed,
        NULL,
        NULL,
        NULL,
        itClimbersIce_Logic90_DmgDealt,
        NULL,
        NULL,
        itClimbersIce_Logic90_Reflected,
        itClimbersIce_Logic90_Clanked,
        itClimbersIce_Logic90_Absorbed,
        itClimbersIce_Logic90_ShieldBounced,
        it_2725_Logic90_HitShield,
        itClimbersIce_Logic90_EvtUnk,
    },
    {
        // Ice Climbers blizzard
        it_803F76A8,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        itClimbersBlizzard_DmgDealt,
        NULL,
        NULL,
        itClimbersBlizzard_Reflected,
        itClimbersBlizzard_Clanked,
        itClimbersBlizzard_Absorbed,
        itClimbersBlizzard_ShieldBounced,
        itClimbersBlizzard_HitShield,
        itClimbersBlizzard_EvtUnk,
    },
    {
        // Zelda din fire
        ItemStateTable_ZeldaDinFire,
        NULL,
        itZeldaDinFire_Logic65_Destroyed,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        itZeldaDinFire_Logic65_Reflected,
        itZeldaDinFire_Logic65_Clanked,
        itZeldaDinFire_Logic65_Absorbed,
        NULL,
        NULL,
        itZeldaDinFire_Logic65_EvtUnk,
    },
    {
        // Zelda din fire explode
        it_803F7740,
        NULL,
        itZeldaDinFireExplode_Logic66_Destroyed,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        itZeldaDinFireExplode_Logic66_Clanked,
        itZeldaDinFireExplode_Logic66_Absorbed,
        itZeldaDinFireExplode_Logic66_ShieldBounced,
        itZeldaDinFireExplode_Logic66_HitShield,
        itZeldaDinFireExplode_Logic66_EvtUnk,
    },
    {
        // Mewtwo disable
        it_803F7750,
        NULL,
        itMewtwoDisable_Logic67_Destroyed,
        NULL,
        NULL,
        NULL,
        itMewtwoDisable_Logic67_DmgDealt,
        NULL,
        NULL,
        itMewtwoDisable_Logic67_Reflected,
        itMewtwoDisable_Logic67_Clanked,
        itMewtwoDisable_Logic67_Absorbed,
        itMewtwoDisable_Logic67_ShieldBounced,
        itMewtwoDisable_Logic67_HitShield,
        itMewtwoDisable_Logic67_EvtUnk,
    },
    {
        // Peach toad spore
        it_803F7548,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        itPeachToadSpore_Logic92_DmgDealt,
        NULL,
        NULL,
        itPeachToadSpore_Logic68_Reflected,
        itPeachToadSpore_Logic68_Clanked,
        itPeachToadSpore_Logic68_Absorbed,
        itPeachToadSpore_Logic68_ShieldBounced,
        itPeachToadSpore_Logic68_HitShield,
        itPeachToadSpore_Logic92_EvtUnk,
    },
    {
        // Mewtwo shadow ball
        it_803F7760,
        NULL,
        it_2725_Logic101_Destroyed,
        it_2725_Logic101_PickedUp,
        NULL,
        NULL,
        itMewtwoShadowball_Logic101_DmgDealt,
        NULL,
        NULL,
        it_2725_Logic101_Reflected,
        itMewtwoShadowball_Logic101_Clanked,
        itMewtwoShadowball_Logic101_Absorbed,
        it_2725_Logic101_ShieldBounced,
        itMewtwoShadowball_Logic101_HitShield,
        itMewtwoShadowball_Logic101_EvtUnk,
    },
    {
        // Ice Climbers string (belay)
        it_803F76B8,
        NULL,
        NULL,
        it_2725_Logic70_PickedUp,
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
        it_2725_Logic70_EvtUnk,
    },
    {
        // Game & Watch greenhouse (insecticide spray)
        it_803F7898,
        NULL,
        itGamewatchGreenhouse_Destroyed,
        itGamewatchGreenhouse_PickedUp,
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
        itGamewatchGreenhouse_EvtUnk,
    },
    {
        // Game & Watch manhole
        it_803F78D8,
        NULL,
        itGameWatchManhole_Logic72_Destroyed,
        itGameWatchManhole_Logic72_PickedUp,
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
        itGameWatchManhole_Logic72_EvtUnk,
    },
    {
        // Game & Watch fire
        it_803F78E8,
        NULL,
        itGamewatchFire_Destroyed,
        itGamewatchFire_PickedUp,
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
        itGamewatchFire_EvtUnk,
    },
    {
        // Game & Watch parachute
        it_803F78F8,
        NULL,
        itGameWatchParachute_Logic74_Destroyed,
        itGameWatchParachute_Logic74_PickedUp,
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
        itGameWatchParachute_Logic74_EvtUnk,
    },
    {
        // Game & Watch turtle
        it_803F7918,
        NULL,
        itGameWatchTurtle_Logic75_Destroyed,
        itGameWatchTurtle_Logic75_PickedUp,
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
        itGameWatchTurtle_Logic75_EvtUnk,
    },
    {
        // Game & Watch breath
        it_803F7938,
        NULL,
        itGameWatchBreath_Logic76_Destroyed,
        itGameWatchBreath_Logic76_PickedUp,
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
        itGameWatchBreath_Logic76_EvtUnk,
    },
    {
        // Game & Watch judge
        it_803F7968,
        NULL,
        itGameWatchJudge_Logic77_Destroyed,
        it_2725_Logic77_PickedUp,
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
        itGameWatchJudge_Logic77_EvtUnk,
    },
    {
        // Game & Watch panic
        it_803F79A0,
        NULL,
        itGameWatchPanic_Logic78_Destroyed,
        itGameWatchPanic_Logic78_PickedUp,
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
        itGameWatchPanic_Logic78_EvtUnk,
    },
    {
        // Game & Watch chef
        it_803F79E0,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        itGameWatchChef_Logic112_DmgDealt,
        NULL,
        NULL,
        itGameWatchChef_Logic112_Reflected,
        it_2725_Logic112_Clanked,
        it_2725_Logic112_Absorbed,
        itGameWatchChef_Logic112_ShieldBounced,
        it_2725_Logic112_HitShield,
        itGameWatchChef_Logic112_EvtUnk,
    },
    {
        // Young Link milk
        it_803F7A28,
        NULL,
        NULL,
        it_2725_Logic80_PickedUp,
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
        itCLinkMilk_Logic80_EvtUnk,
    },
    {
        // Game & Watch rescue
        it_803F79C0,
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
        itGameWatchRescue_Logic81_EvtUnk,
    },
    {
        // Master Hand laser
        it_803F9378,
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
        itMasterHandLaser_Logic84_EvtUnk,
    },
    {
        // Master Hand bullet
        it_803F9388,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        itMasterHandBullet_Logic83_DmgDealt,
        NULL,
        NULL,
        itMasterHandBullet_Logic83_Reflected,
        itMasterHandBullet_Logic83_Clanked,
        itMasterHandBullet_Logic83_Absorbed,
        itMasterHandBullet_Logic83_ShieldBounced,
        itMasterHandBullet_Logic83_HitShield,
        itMasterHandBullet_Logic85_EvtUnk,
    },
    {
        // Crazy Hand laser
        it_803F9378,
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
        itMasterHandLaser_Logic84_EvtUnk,
    },
    {
        // Crazy Hand bullet
        it_803F9388,
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
        itMasterHandBullet_Logic85_EvtUnk,
    },
    {
        // Crazy Hand bomb
        it_803F93A8,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        itCrazyHandBomb_Logic86_DmgDealt,
        NULL,
        NULL,
        itCrazyHandBomb_Logic86_Reflected,
        NULL,
        NULL,
        NULL,
        NULL,
        itCrazyHandBomb_Logic86_EvtUnk,
    },
    {
        it_803F6788,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        itMarioFireball_Logic87_DmgDealt,
        NULL,
        NULL,
        itMarioFireball_Logic87_Reflected,
        itMarioFireball_Logic87_Clanked,
        itMarioFireball_Logic87_Absorbed,
        itMarioFireball_Logic87_ShieldBounced,
        itMarioFireball_Logic87_HitShield,
        itMarioFireball_Logic87_EvtUnk,
    },
    {
        it_803F75D0,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        itDrMarioPill_DmgDealt,
        NULL,
        NULL,
        itDrMarioPill_Reflected,
        itDrMarioPill_Clanked,
        itDrMarioPill_Absorbed,
        itDrMarioPill_ShieldBounced,
        itDrMarioPill_HitShield,
        itDrMarioPill_EvtUnk,
    },
    {
        it_803F75C0,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        itLuigiFireball_Logic89_DmgDealt,
        NULL,
        NULL,
        itLuigiFireball_Logic89_Reflected,
        itLuigiFireball_Logic89_Clanked,
        itLuigiFireball_Logic89_Absorbed,
        itLuigiFireball_Logic89_ShieldBounced,
        itLuigiFireball_Logic89_HitShield,
        itLuigiFireball_Logic89_EvtUnk,
    },
    {
        it_803F7668,
        NULL,
        it_2725_Logic90_Destroyed,
        NULL,
        NULL,
        NULL,
        itClimbersIce_Logic90_DmgDealt,
        NULL,
        NULL,
        itClimbersIce_Logic90_Reflected,
        itClimbersIce_Logic90_Clanked,
        itClimbersIce_Logic90_Absorbed,
        itClimbersIce_Logic90_ShieldBounced,
        it_2725_Logic90_HitShield,
        itClimbersIce_Logic90_EvtUnk,
    },
    {
        it_803F7528,
        NULL,
        itPeachToad_Logic91_Destroyed,
        itPeachToad_Logic91_PickedUp,
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
        itPeachToad_Logic91_EvtUnk,
    },
    {
        it_803F7548,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        itPeachToadSpore_Logic92_DmgDealt,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        itPeachToadSpore_Logic92_EvtUnk,
    },
    {
        it_803F67D0,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        itFoxLaser_Logic94_Clanked,
        NULL,
        NULL,
        itFoxLaser_Logic94_Reflected,
        itFoxLaser_Logic94_Clanked,
        itFoxLaser_Logic94_Absorbed,
        itFoxLaser_Logic94_ShieldBounced,
        itFoxLaser_Logic94_HitShield,
        itFoxLaser_Logic94_EvtUnk,
    },
    {
        it_803F67D0,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        itFoxLaser_Logic94_Clanked,
        NULL,
        NULL,
        itFoxLaser_Logic94_Reflected,
        itFoxLaser_Logic94_Clanked,
        itFoxLaser_Logic94_Absorbed,
        itFoxLaser_Logic94_ShieldBounced,
        itFoxLaser_Logic94_HitShield,
        itFoxLaser_Logic94_EvtUnk,
    },
    {
        it_803F6CA8,
        NULL,
        NULL,
        itFoxBlaster_Logic96_PickedUp,
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
        itFoxBlaster_Logic96_EvtUnk,
    },
    {
        it_803F6CA8,
        NULL,
        NULL,
        itFoxBlaster_Logic96_PickedUp,
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
        itFoxBlaster_Logic96_EvtUnk,
    },
    {
        it_803F6A28,
        NULL,
        itLinkArrow_Logic98_Destroyed,
        itLinkArrow_Logic98_PickedUp,
        NULL,
        NULL,
        itLinkArrow_Logic98_DmgDealt,
        NULL,
        NULL,
        itLinkArrow_Logic98_Reflected,
        itLinkArrow_Logic98_Clanked,
        NULL,
        NULL,
        itLinkArrow_Logic98_HitShield,
        itLinkArrow_Logic98_EvtUnk,
    },
    {
        it_803F6A28,
        NULL,
        itLinkArrow_Logic98_Destroyed,
        itLinkArrow_Logic98_PickedUp,
        NULL,
        NULL,
        itLinkArrow_Logic98_DmgDealt,
        NULL,
        NULL,
        itLinkArrow_Logic98_Reflected,
        itLinkArrow_Logic98_Clanked,
        NULL,
        NULL,
        itLinkArrow_Logic98_HitShield,
        itLinkArrow_Logic98_EvtUnk,
    },
    {
        it_803F6E98,
        NULL,
        itLinkBow_Logic100_Destroyed,
        itLinkBow_Logic100_PickedUp,
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
        itLinkBow_Logic100_EvtUnk,
    },
    {
        it_803F6E98,
        NULL,
        itLinkBow_Logic100_Destroyed,
        itLinkBow_Logic100_PickedUp,
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
        itLinkBow_Logic100_EvtUnk,
    },
    {
        it_803F7760,
        NULL,
        it_2725_Logic101_Destroyed,
        it_2725_Logic101_PickedUp,
        NULL,
        NULL,
        itMewtwoShadowball_Logic101_DmgDealt,
        NULL,
        NULL,
        it_2725_Logic101_Reflected,
        itMewtwoShadowball_Logic101_Clanked,
        itMewtwoShadowball_Logic101_Absorbed,
        it_2725_Logic101_ShieldBounced,
        itMewtwoShadowball_Logic101_HitShield,
        itMewtwoShadowball_Logic101_EvtUnk,
    },
    {
        it_803F6B70,
        NULL,
        it_2725_Logic102_Destroyed,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        itNesspkflash_Logic102_Reflected,
        itNesspkflash_Logic102_Clanked,
        itNesspkflash_Logic102_Absorbed,
        NULL,
        NULL,
        itNesspkflash_Logic102_EvtUnk,
    },
    {
        it_803F6F40,
        NULL,
        it_2725_Logic103_Destroyed,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        itNessPKFlashExplode_Logic103_Clanked,
        itNessPKFlashExplode_Logic103_Absorbed,
        itNessPKFlashExplode_Logic103_ShieldBounced,
        itNessPKFlashExplode_Logic103_HitShield,
        itNessPKFlashExplode_Logic103_EvtUnk,
    },
    {
        it_803F7190,
        NULL,
        it_2725_Logic106_Destroyed,
        NULL,
        NULL,
        NULL,
        it_2725_Logic106_DmgDealt,
        NULL,
        NULL,
        it_2725_Logic106_Reflected,
        it_2725_Logic106_Clanked,
        it_2725_Logic106_Absorbed,
        it_2725_Logic106_ShieldBounced,
        it_2725_Logic106_HitShield,
        itPikachuTJoltGround_Logic106_EvtUnk,
    },
    {
        it_803F71D8,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        it_2725_Logic107_DmgDealt,
        NULL,
        NULL,
        it_2725_Logic107_Reflected,
        it_2725_Logic107_Clanked,
        it_2725_Logic107_Absorbed,
        it_2725_Logic107_ShieldBounced,
        it_2725_Logic107_HitShield,
        itPikachuTJoltAir_Logic107_EvtUnk,
    },
    {
        it_803F7190,
        NULL,
        it_2725_Logic106_Destroyed,
        NULL,
        NULL,
        NULL,
        it_2725_Logic106_DmgDealt,
        NULL,
        NULL,
        it_2725_Logic106_Reflected,
        it_2725_Logic106_Clanked,
        it_2725_Logic106_Absorbed,
        it_2725_Logic106_ShieldBounced,
        it_2725_Logic106_HitShield,
        itPikachuTJoltGround_Logic106_EvtUnk,
    },
    {
        it_803F71D8,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        it_2725_Logic107_DmgDealt,
        NULL,
        NULL,
        it_2725_Logic107_Reflected,
        it_2725_Logic107_Clanked,
        it_2725_Logic107_Absorbed,
        it_2725_Logic107_ShieldBounced,
        it_2725_Logic107_HitShield,
        itPikachuTJoltAir_Logic107_EvtUnk,
    },
    {
        it_803F7288,
        NULL,
        it_2725_Logic108_Destroyed,
        it_2725_Logic108_PickedUp,
        NULL,
        NULL,
        itSamusChargeshot_Logic108_DmgDealt,
        NULL,
        NULL,
        it_2725_Logic108_Reflected,
        itSamusChargeshot_Logic108_Clanked,
        itSamusChargeshot_Logic108_Absorbed,
        it_2725_Logic108_ShieldBounced,
        itSamusChargeshot_Logic108_HitShield,
        itSamusChargeshot_Logic108_EvtUnk,
    },
    {
        it_803F6F50.states,
        NULL,
        itSeakNeedleThrown_Logic109_Destroyed,
        NULL,
        NULL,
        NULL,
        it_2725_Logic109_DmgDealt,
        it_2725_Logic109_DmgReceived,
        NULL,
        it_2725_Logic109_Reflected,
        it_2725_Logic109_Clanked,
        NULL,
        it_2725_Logic109_ShieldBounced,
        it_2725_Logic109_HitShield,
        itSeakNeedleThrown_Logic109_EvtUnk,
    },
    {
        it_803F70A8,
        NULL,
        NULL,
        itSeakNeedleHeld_Logic110_PickedUp,
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
        itSeakNeedleHeld_Logic110_EvtUnk,
    },
    {
        ItemStateTable_KoopaFlame,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        itKoopaFlame_Logic111_DmgDealt,
        NULL,
        NULL,
        itKoopaFlame_Logic111_Reflected,
        itKoopaFlame_Logic111_Clanked,
        itKoopaFlame_Logic111_Absorbed,
        itKoopaFlame_Logic111_ShieldBounced,
        itKoopaFlame_Logic111_HitShield,
        itKoopaFlame_Logic111_EvtUnk,
    },
    {
        it_803F79E0,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        itGameWatchChef_Logic112_DmgDealt,
        NULL,
        NULL,
        itGameWatchChef_Logic112_Reflected,
        it_2725_Logic112_Clanked,
        it_2725_Logic112_Absorbed,
        itGameWatchChef_Logic112_ShieldBounced,
        it_2725_Logic112_HitShield,
        itGameWatchChef_Logic112_EvtUnk,
    },
    {
        it_803F7958,
        NULL,
        itKirbyGameWatchChefPan_Logic113_Destroyed,
        itKirbyGameWatchChefPan_Logic113_PickedUp,
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
        itKirbyGameWatchChefPan_Logic113_EvtUnk,
    },
    {
        it_803F94A0,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        it_27CF_Logic114_DmgReceived,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        it_27CF_Logic114_EvtUnk,
    },
    {
        // Unk4
        it_803F8BD8,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        it_2E5A_Logic115_DmgDealt,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        it_2E5A_Logic115_EvtUnk,
    },
    {
        // Coin
        it_803F93C8,
        itCoin_Logic116_Spawned,
        itCoin_Logic116_Destroyed,
        itCoin_Logic116_PickedUp,
        itCoin_Logic116_Thrown,
        itCoin_Logic116_Thrown,
        NULL,
        itCoin_Logic116_DmgReceived,
        itCoin_Logic116_EnteredAir,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        itCoin_Logic116_EvtUnk,
    },
    {
        // Pokemon random
        it_803F8C8C,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        it_2E6A_Logic117_DmgDealt,
        it_2E6A_Logic117_DmgReceived,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        it_2E6A_Logic117_EvtUnk,
    },
};

/// Monster and Stage-specific Items
struct sdata_ItemGXLink it_803F4CA8[30] = {
    it_8026EECC, it_8026EECC, it_8026EECC, it_8026EECC, it_8026EECC,
    it_8026EECC, it_8026EECC, it_8026EECC, it_8026EECC, it_8026EECC,
    it_8026EECC, it_8026EECC, it_8026EECC, it_8026EECC, it_8026EECC,
    it_8026EECC, it_8026EECC, it_8026EECC, it_8026EECC, it_8026EECC,
    it_8026EECC, it_8026EECC, it_8026EECC, it_8026EECC, it_8026EECC,
    it_8026EECC, it_8026EECC, it_8026EECC, it_8026EECC, NULL,
};

struct ItemLogicTable it_803F4D20[ARRAY_SIZE(it_803F4CA8)] = {
    {
        // Old Goomba (old-Kuri)
        it_803F8320,
        it_802D73F0,
        it_2725_Logic9_Destroyed,
        NULL,
        NULL,
        NULL,
        NULL,
        it_2725_Logic0_DmgReceived,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        it_802D84D8,
    },
    {
        // Target (Mato)
        it_803F83E0,
        it_802D84F8,
        it_2725_Logic9_Destroyed,
        NULL,
        NULL,
        NULL,
        NULL,
        it_802D85F4,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        // Yoshi's Story Shy Guy (Heiho)
        it_803F83F0,
        it_802D8688,
        it_2725_Logic9_Destroyed,
        NULL,
        NULL,
        NULL,
        NULL,
        it_802D8EC8,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        it_802D9A0C,
    },
    {
        // Koopa Troopa (Green) (Nokonoko)
        it_803F85F0,
        it_802DC69C,
        it_2725_Logic9_Destroyed,
        it_802DD4F4,
        it_802DD59C,
        it_802DD67C,
        NULL,
        itNokonoko_Logic3_DmgReceived,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        it_802DD7D0,
    },
    {
        // Koopa Troopa (Red) (Patapata)
        it_803F88C0,
        it_802E05A0,
        it_2725_Logic9_Destroyed,
        itPatapata_Logic4_PickedUp,
        it_2725_Logic4_Dropped,
        it_2725_Logic4_Thrown,
        NULL,
        it_2725_Logic4_DmgReceived,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        it_802E16D8,
    },
    {
        // Like-Like (likelike)
        it_803F8468,
        it_802D9BA8,
        itLikeLike_Logic5_Destroyed,
        itLikeLike_Logic5_PickedUp,
        it_2725_Logic5_Dropped,
        itLikeLike_Logic5_Thrown,
        NULL,
        it_2725_Logic5_DmgReceived,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        it_802E16D8,
    },
    {
        // Old Redead (old-lead) [invalid]
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
    },
    {
        // Old Octorok (old-octa) [invalid]
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
    },
    {
        // Old Ottosea (old-otto)
        it_803F89C8,
        it_802E2470,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        it_2725_Logic8_DmgReceived,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    },
    {
        // Polar Bear (whitebea)
        it_803F8A88,
        it_802E37BC,
        it_2725_Logic9_Destroyed,
        itWhiteBea_Logic9_PickedUp,
        it_2725_Logic9_Dropped,
        it_2725_Logic9_Thrown,
        NULL,
        it_802E3884,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        it_802E4A24,
    },
    {
        // Klaptrap (klap)
        it_803F8940,
        it_802E1820,
        itKlap_Logic10_Destroyed,
        NULL,
        NULL,
        NULL,
        NULL,
        it_2725_Logic10_DmgReceived,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        it_802E2450,
    },
    {
        // Green Shell (zgshell)
        it_803F86C8,
        it_802DE040,
        itZGShell_Logic11_Destroyed,
        it_2725_Logic11_PickedUp,
        itZGShell_Logic11_Dropped,
        itZGShell_Logic11_Thrown,
        itZGShell_Logic11_DmgDealt,
        itZGShell_Logic11_DmgReceived,
        it_2725_Logic11_EnteredAir,
        itZGShell_Logic11_Reflected,
        it_2725_Logic11_Clanked,
        NULL,
        itZGShell_Logic11_ShieldBounced,
        it_2725_Logic11_HitShield,
        it_802DFED4,
    },
    {
        // Red Shell (green act) (zrshell)
        it_803F87F0,
        it_802E02E8,
        itZRShell_Logic12_Destroyed,
        itZRShell_Logic12_PickedUp,
        itZRShell_Logic12_Dropped,
        itZRShell_Logic12_Thrown,
        itZRShell_Logic12_DmgDealt,
        itZRShell_Logic12_DmgReceived,
        itZRShell_Logic12_EnteredAir,
        itZRShell_Logic12_Reflected,
        itZRShell_Logic12_Clanked,
        NULL,
        itZRShell_Logic12_ShieldBounced,
        itZRShell_Logic12_HitShield,
        it_802E0468,
    },
    {
        // Tingle (Tincle) (on balloon)
        it_803F9000,
        it_802EB5C8,
        NULL,
        NULL,
        NULL,
        NULL,
        itTincle_Logic13_DmgDealt,
        itTincle_Logic13_DmgReceived,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        it_802EC850,
    },
    {
        // [Invalid]
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
    },
    {
        // [Invalid]
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
    },
    {
        // [Invalid]
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
    },
    {
        // Whispy Apple
        it_803F91D0,
        NULL,
        NULL,
        it_802EEA08,
        it_802EEA70,
        it_802EEB28,
        it_802EEED0,
        NULL,
        itWhispyApple_Logic18_EnteredAir,
        it_802EEF10,
        it_802EEED8,
        NULL,
        it_802EEF68,
        it_802EEF30,
        it_802EEF88,
    },
    {
        // Whispy's Healing Apple
        it_803F91D0,
        NULL,
        NULL,
        it_802EEA08,
        it_802EEA70,
        it_802EEB28,
        it_802EEED0,
        NULL,
        itWhispyApple_Logic18_EnteredAir,
        it_802EEF10,
        it_802EEED8,
        NULL,
        it_802EEF68,
        it_802EEF30,
        it_802EEF88,
    },
    {
        // [Invalid]
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
    },
    {
        // [Invalid]
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
    },
    {
        // [Invalid]
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
    },
    {
        // Tool (Flatzone)
        it_803F9260,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        itTools_Logic22_DmgDealt,
        itTools_Logic22_DmgReceived,
        NULL,
        itTools_Logic22_Reflected,
        it_2725_Logic22_Clanked,
        it_2725_Logic22_Absorbed,
        itTools_Logic22_ShieldBounced,
        it_2725_Logic22_HitShield,
        it_802EFA24,
    },
    {
        // [Invalid]
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
    },
    {
        // [Invalid]
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
    },
    {
        // Birdo (Kyasarin)
        it_803F90D0,
        it_802ECE90,
        itKyasarin_Logic25_Destroyed,
        NULL,
        NULL,
        NULL,
        NULL,
        it_802EDDC0,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        it_802EE1E0,
    },
    {
        // Arwing Laser
        it_803F8DE8,
        NULL,
        it_802E79C8,
        NULL,
        NULL,
        NULL,
        it_802E838C,
        NULL,
        NULL,
        it_802E8420,
        it_802E838C,
        it_802E8418,
        it_802E85F4,
        it_802E8784,
        NULL,
    },
    {
        // Great Fox's Laser
        it_803F8FD0,
        it_802EB1EC,
        NULL,
        NULL,
        NULL,
        NULL,
        itGreatFoxLaser_Logic27_DmgDealt,
        NULL,
        NULL,
        it_2725_Logic27_Reflected,
        itGreatFoxLaser_Logic27_Clanked,
        itGreatFoxLaser_Logic27_Absorbed,
        NULL,
        NULL,
        it_802EB5A8,
    },
    {
        // Birdo's Egg
        it_803F9328,
        NULL,
        NULL,
        itKyasarinEgg_Logic28_PickedUp,
        itKyasarinEgg_Logic28_Dropped,
        itKyasarinEgg_Logic28_Thrown,
        it_2725_Logic28_DmgDealt,
        it_802F022C,
        NULL,
        it_2725_Logic28_Reflected,
        it_2725_Logic28_Clanked,
        NULL,
        itKyasarinEgg_Logic28_ShieldBounced,
        it_2725_Logic28_HitShield,
        it_802F0320,
    },
    {
        // NULL
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
    },
};

typedef enum PokemonKind {
    Pokemon_ID_Tosakinto,   // Goldeen (Tosakinto)
    Pokemon_ID_Chicorita,   // Chikorita (Chicorita)
    Pokemon_ID_Kabigon,     // Snorlax (Kabigon)
    Pokemon_ID_Kamex,       // Blastoise (Kamex)
    Pokemon_ID_Matadogas,   // Weezing (Matadogas)
    Pokemon_ID_Lizardon,    // Charizard (Lizardon)
    Pokemon_ID_Fire,        // Moltres (Fire)
    Pokemon_ID_Thunder,     // Zapdos (Thunder)
    Pokemon_ID_Freezer,     // Articuno (Freezer)
    Pokemon_ID_Sonans,      // Wobbuffet (Sonans)
    Pokemon_ID_Hassam,      // Scizor (Hassam)
    Pokemon_ID_Unknown,     // Unown (Unknown)
    Pokemon_ID_Entei,       // Entei
    Pokemon_ID_Raikou,      // Raikou
    Pokemon_ID_Suikun,      // Suicune (Suikun)
    Pokemon_ID_Kireihana,   // Bellossom (Kireihana)
    Pokemon_ID_Marumine,    // Electrode (Marumine)
    Pokemon_ID_Lugia,       // Lugia
    Pokemon_ID_Houou,       // Ho-oh (Houou)
    Pokemon_ID_Metamon,     // Ditto (Metamon)
    Pokemon_ID_Pippi,       // Clefairy (Pippi)
    Pokemon_ID_Togepy,      // Togepi (Togepy)
    Pokemon_ID_Mew,         // Mew
    Pokemon_ID_Cerebi,      // Celebi (Cerebi)
    Pokemon_ID_Hitodeman,   // Staryu (Hitodeman)
    Pokemon_ID_Lucky,       // Chansey (Lucky)
    Pokemon_ID_Porygon2,    // Porygon2
    Pokemon_ID_Hinoarashi,  // Cyndaquil (Hinoarashi)
    Pokemon_ID_Maril,       // Marill (Maril)
    Pokemon_ID_Fushigibana, // Venusaur (Fushigibana)
} PokemonKind;

void it_80279C48(Item_GObj* item_gobj)
{
    Vec3 v;
    Item* item = GET_ITEM(item_gobj);
    HSD_GObj* gobj = ftLib_8008627C(&item->pos, item->owner);
    f32 dir;
    if (gobj != NULL) {
        ftLib_80086644(gobj, &v);
        if ((item->pos.x - v.x) > 0.0f) {
            item->facing_dir = -1.0f;
            return;
        }
        item->facing_dir = 1.0f;
        return;
    }
    if (HSD_Randi(2) != 0) {
        dir = 1.0f;
    } else {
        dir = -1.0f;
    }
    item->facing_dir = dir;
}

#pragma push
#pragma dont_inline on

void it_80279CDC(Item_GObj* item_gobj, f32 scale)
{
    it_8027A13C(item_gobj);
    it_80279D5C(item_gobj, scale);
    it_8026B3A8(item_gobj);
    it_802756D0(item_gobj);
    it_8026BDB4(item_gobj);
}

#pragma pop

void it_80279D38(Item_GObj* item_gobj)
{
    it_8027B964(item_gobj, false);
}

void it_80279D5C(Item_GObj* item_gobj, f32 scale)
{
    Vec3 sp18;
    HSD_JObj* item_jobj;
    u32 temp_r4;
    Item* item;

    // item_jobj = GET_JOBJ( item_gobj);
    item_jobj = item_gobj->hsd_obj;
    item = GET_ITEM(item_gobj);
    sp18.z = scale;
    sp18.y = scale;
    sp18.x = scale;
    item->xDD4_itemVar.pokemon_spawn.x4C = scale;
    item->xDD4_itemVar.pokemon_spawn.x5C = 0;
    HSD_JObjSetScale(item_jobj, &sp18);
}

static inline void it_80279E24_inline(Item_GObj* item_gobj)
{
    HSD_JObj* jobj = item_gobj->hsd_obj;
    Item* item = item_gobj->user_data;
    f32 scale = HSD_JObjGetScaleX(jobj);
    it_80272F7C(jobj, item->xDD4_itemVar.pokemon_spawn
                          .x2C[item->xDD4_itemVar.pokemon_spawn.x58]);
    item->xDD4_itemVar.pokemon_spawn.x58++;
    item->xDD4_itemVar.pokemon_spawn.x4C =
        (item->xDD4_itemVar.pokemon_spawn
             .x2C[item->xDD4_itemVar.pokemon_spawn.x58] -
         scale) /
        item->xDD4_itemVar.pokemon_spawn.x44;
}

void it_80279E24(Item_GObj* item_gobj)
{
    HSD_JObj* item_jobj = item_gobj->hsd_obj;
    Item* item = HSD_GObjGetUserData(item_gobj);
    f32 scale = HSD_JObjGetScaleX(item_jobj);
    PAD_STACK(24);

    if (item->xDD4_itemVar.pokemon_spawn.x50 <= 0.0f) {
        item->xDD4_itemVar.pokemon_spawn.x50 =
            item->xDD4_itemVar.pokemon_spawn.x44;
        if (item->xDD4_itemVar.pokemon_spawn.x58 & 1) {
            if (item->xDD4_itemVar.pokemon_spawn
                    .x2C[item->xDD4_itemVar.pokemon_spawn.x58] <= scale)
            {
                it_80279E24_inline(item_gobj);
            }
        } else {
            if (item->xDD4_itemVar.pokemon_spawn
                    .x2C[item->xDD4_itemVar.pokemon_spawn.x58] >= scale)
            {
                it_80279E24_inline(item_gobj);
            }
        }
        if ((s32) item->xDD4_itemVar.pokemon_spawn.x54 <=
            (s32) item->xDD4_itemVar.pokemon_spawn.x58)
        {
            item->xDD4_itemVar.pokemon_spawn.x5C = 2;
            return;
        }
    }
    item->xDD4_itemVar.pokemon_spawn.x50 -= 1.0f;
    it_80272DE4(item_jobj, item->xDD4_itemVar.pokemon_spawn.x4C);
}

void it_80279FF8(Item_GObj* item_gobj)
{
    HSD_JObj* item_jobj;
    Item* item = HSD_GObjGetUserData(item_gobj);
    PAD_STACK(16);

    if (item->xDD4_itemVar.pokemon_spawn.x5C == 0) {
        item_jobj = HSD_GObjGetHSDObj(item_gobj);
        if (item->xCC_item_attr->x60_scale >
            (item->xDD4_itemVar.pokemon_spawn.x48 +
             HSD_JObjGetScaleX(item_jobj)))
        {
            it_80272DE4(item_jobj, item->xDD4_itemVar.pokemon_spawn.x48);
            return;
        }
        it_80272F7C(item_jobj, item->xCC_item_attr->x60_scale);
        item->xDD4_itemVar.pokemon_spawn.x5C = 1;
        return;
    }
    if (item->xDD4_itemVar.pokemon_spawn.x5C != 2) {
        it_80279E24(item_gobj);
    }
}

#pragma push
#pragma dont_inline on

bool it_8027A09C(Item_GObj* item_gobj)
{
    Item* item;
    PAD_STACK(8);

    item = item_gobj->user_data;
    it_80272860(item_gobj, item->xDD4_itemVar.pokemon_spawn.x1C,
                item->xDD4_itemVar.pokemon_spawn.x20);
    if (item->xDD4_itemVar.pokemon_spawn.x24 <= 0.0f) {
        it_80272F7C(item_gobj->hsd_obj, item->xCC_item_attr->x60_scale);
        return true;
    }
    item->xDD4_itemVar.pokemon_spawn.x24 -= 1.0f;
    return false;
}

#pragma pop

bool it_8027A118(Item_GObj* item_gobj, HSD_GObjEvent arg1)
{
    it_8026E4D0(item_gobj, arg1);
    return false;
}

void it_8027A13C(Item_GObj* item_gobj)
{
    Item* item;

    item = item_gobj->user_data;
    item->xDD4_itemVar.pokemon_spawn.x10.z = 0.0f;
    item->xDD4_itemVar.pokemon_spawn.x10.y = 0.0f;
    item->xDD4_itemVar.pokemon_spawn.x10.x = 0.0f;
    item->xDD4_itemVar.pokemon_spawn.x4.z = 0.0f;
    item->xDD4_itemVar.pokemon_spawn.x4.y = 0.0f;
    item->xDD4_itemVar.pokemon_spawn.x4.x = 0.0f;
}

void it_8027A160(HSD_JObj* bone, Item* item)
{
    Vec3 sp1C;
    Vec3 sp10;
    f32 var_f1;
    f32 var_f1_2;
    f32 var_f1_3;

    if (bone != NULL) {
        sp1C.z = 0.0f;
        sp1C.y = 0.0f;
        sp1C.x = 0.0f;
        HSD_JObjGetTranslation(bone, &sp10);
        sp10.x *= item->xCC_item_attr->x60_scale;
        sp10.y *= item->xCC_item_attr->x60_scale;
        sp10.z *= item->xCC_item_attr->x60_scale;
        var_f1 = sp10.x;
        if (var_f1 < 0.0f) {
            var_f1 = -var_f1;
        }
        if (var_f1 < 0.001f) {
            sp10.x = 0.0f;
        }
        var_f1_2 = sp10.y;
        if (var_f1_2 < 0.0f) {
            var_f1_2 = -var_f1_2;
        }
        if (var_f1_2 < 0.001f) {
            sp10.y = 0.0f;
        }
        var_f1_3 = sp10.z;
        if (var_f1_3 < 0.0f) {
            var_f1_3 = -var_f1_3;
        }
        if (var_f1_3 < 0.001f) {
            sp10.z = 0.0f;
        }
        item->xDD4_itemVar.pokemon_spawn.x4.x =
            sp10.x - item->xDD4_itemVar.pokemon_spawn.x10.x;
        item->xDD4_itemVar.pokemon_spawn.x4.y =
            sp10.y - item->xDD4_itemVar.pokemon_spawn.x10.y;
        item->xDD4_itemVar.pokemon_spawn.x4.z =
            sp10.z - item->xDD4_itemVar.pokemon_spawn.x10.z;
        item->xDD4_itemVar.pokemon_spawn.x10 = sp10;
        HSD_JObjSetTranslate(bone, &sp1C);
    }
}

void it_8027A344(Item_GObj* item_gobj)
{
    Item* item;

    item = item_gobj->user_data;
    item->x40_vel.x = item->xDD4_itemVar.pokemon_spawn.x4.z * item->facing_dir;
    item->x40_vel.y = item->xDD4_itemVar.pokemon_spawn.x4.y;
}

#define PK_START (Pokemon_Tosakinto)
#define PK_END (Pokemon_Tosakinto + 30)

s32 it_8027A364(Item* item)
{
    itPokemonSpawn_DatAttrs* attr =
        item->xC4_article_data->x4_specialAttributes;
    int ret_val = 1;
    int i;
    int start = Pokemon_Tosakinto;
    int end = Pokemon_Tosakinto + 30;

    for (i = start; i < end; i++) {
        if (Item_804A0E24.x != i && Item_804A0E24.y != i) {
            ret_val += attr->pokemon_spawn_weights[i - Pokemon_Tosakinto];
        }
    }

    return ret_val;
}

s32 it_8027A4D4(Item* item)
{
    int rand_int;
    int i;
    int var_r3;

    itPokemonSpawn_DatAttrs* attr =
        item->xC4_article_data->x4_specialAttributes;

    if (HSD_Randi(251) == 0 && Item_804A0E24.z == 0 && gm_80165084()) {
        Item_804A0E24.z = 1;
        gm_80172C04();
        return 23;
    }
    if (HSD_Randi(251) == 0 && Item_804A0E24.z == 0 && gm_80164ABC()) {
        Item_804A0E24.z = 1;
        gm_80172BC4();
        return 22;
    }
    rand_int = HSD_Randi(it_8027A364(item));
    var_r3 = 0;
    for (i = PK_START; i < PK_END; i++) {
        int y = Item_804A0E24.y;
        int x = Item_804A0E24.x;
        if (x != i && y != i) {
            var_r3 += attr->pokemon_spawn_weights[i - Pokemon_Tosakinto];
            if (var_r3 >= rand_int) {
                Item_804A0E24.y = x;
                Item_804A0E24.x = i;
                return i - Pokemon_Tosakinto;
            }
        }
    }
    return 0;
}

s32 it_8027A780(Item* item, void* arg1)
{
    u8 _pad[8];
    S32Vec2 sp10[30];
    S32Vec2* base;
    S32Vec2* buf;
    s32 x;
    s32 y;
    itPokemonSpawn_DatAttrs* attr;
    s32 total;
    s32 cnt;
    s32 rand_int;
    s32 idx;
    s32 result;
    s32 accum;
    int i;

    base = sp10;
    buf = base;
    cnt = 0;
    attr = item->xC4_article_data->x4_specialAttributes;
    total = 0;
    x = Item_804A0E24.x;
    y = Item_804A0E24.y;
    for (i = 0; i < 30; i++) {
        ItemKind kind = ((ItemKind*) arg1)[i];
        if (kind == Pokemon_Chicorita_Leaf) {
            break;
        }
        if (x != kind && y != kind) {
            buf->x = kind;
            cnt++;
            buf->y = attr->pokemon_spawn_weights[((ItemKind*) arg1)[i] -
                                                 Pokemon_Tosakinto];
            total += buf->y;
            buf++;
        }
    }
    rand_int = HSD_Randi(total);
    accum = 0;
    result = Pokemon_Sonans;
    idx = 0;
    while (cnt > 0) {
        accum += base->y;
        if (rand_int < accum) {
            result = sp10[idx].x;
            break;
        }
        base++;
        idx++;
        cnt--;
    }
    Item_804A0E24.y = Item_804A0E24.x;
    Item_804A0E24.x = result;
    return result - Pokemon_Tosakinto;
}

s32 it_8027A9B8(Item* item)
{
    void* vec;

    vec = gm_801BEC54();
    if (vec == NULL) {
        return Pokemon_Sonans;
    }
    if ((HSD_Randi(251U) == 0) && (Item_804A0E24.z == 0) && gm_80165084()) {
        Item_804A0E24.z = 1;
        gm_80172C04();
        return 23U;
    }
    if ((HSD_Randi(251U) == 0) && (Item_804A0E24.z == 0) && gm_80164ABC()) {
        Item_804A0E24.z = 1;
        gm_80172BC4();
        return 22U;
    }
    return it_8027A780(item, vec);
}

void it_8027AAA0(Item_GObj* item1_gobj, Item* item2, s32 arg2)
{
    Item* var_r6;

    Item* it = GET_ITEM(item1_gobj);
    itPokemonSpawn_DatAttrs* attr = it->xC4_article_data->x4_specialAttributes;
    if (arg2 == Pokemon_Marumine) {
        item2->xDD4_itemVar.pokemon_spawn.x1C = 0.0f;
        item2->xDD4_itemVar.pokemon_spawn.x20 = 0.0f;
    } else {
        item2->xDD4_itemVar.pokemon_spawn.x1C = attr->xC;
        item2->xDD4_itemVar.pokemon_spawn.x20 = attr->x10;
    }
    item2->xDD4_itemVar.pokemon_spawn.x24 = attr->x14;
    var_r6 = item2;
    item2->xDD4_itemVar.pokemon_spawn.x28 = attr->x18;
    item2->xDD4_itemVar.pokemon_spawn.x48 =
        (item2->xCC_item_attr->x60_scale -
         item2->xDD4_itemVar.pokemon_spawn.x4C) /
        item2->xDD4_itemVar.pokemon_spawn.x28;
    item2->xDD4_itemVar.pokemon_spawn.x44 = attr->x34;
    item2->xDD4_itemVar.pokemon_spawn.x54 = attr->x38;
    item2->xDD4_itemVar.pokemon_spawn.x5C = 0.0f;
    item2->xDD4_itemVar.pokemon_spawn.x58 = 0.0f;
    item2->xDD4_itemVar.pokemon_spawn.x50 = 0.0f;

    {
        int i;
        for (i = 0; i < attr->x38; i++) {
            item2->xDD4_itemVar.pokemon_spawn.x2C[i] =
                attr->x1C[i] * item2->xCC_item_attr->x60_scale;
        }
    }
}

#if 0
static inline s32 it_8027AB64_SpawnWeight(itPokemonSpawn_DatAttrs* attr,
                                          s32 index)
{
    return attr->pokemon_spawn_weights[index - Pokemon_Tosakinto];
}

static inline s32 it_8027AB64_SelectKind(Item* item)
{
    itPokemonSpawn_DatAttrs* attr =
        item->xC4_article_data->x4_specialAttributes;
    s32 rand_int = HSD_Randi(it_8027A364(item));
    s32 recent_y_val = Item_804A0E24.y;
    s32 recent_x_val = Item_804A0E24.x;
    s32 index;
    s32 var_r4;
    s32 var_ctr;

    var_r4 = 0;
    index = Pokemon_Tosakinto;
    for (var_ctr = 30; var_ctr != 0; var_ctr--) {
        if (recent_x_val != index && recent_y_val != index) {
            var_r4 += it_8027AB64_SpawnWeight(attr, index);
            if (var_r4 >= rand_int) {
                Item_804A0E24.y = recent_x_val;
                Item_804A0E24.x = index;
                return index - Pokemon_Tosakinto;
            }
        }
        index++;
    }
    return 0;
}
#else
static inline s32 it_8027AB64_SelectKind(Item* item)
{
    itPokemonSpawn_DatAttrs* attr =
        item->xC4_article_data->x4_specialAttributes;
    s32 rand_int = HSD_Randi(it_8027A364(item));
    s32 recent_x_val = Item_804A0E24.x;
    s32 recent_y_val = Item_804A0E24.y;
    s32* spawn_weights =
        (s32*) ((u8*) attr + 0x284); // fake, but we'll fix it in post
    s32 index;
    s32 var_r4;
    s32 var_ctr;

    var_r4 = 0;
    index = Pokemon_Tosakinto;
    for (var_ctr = 30; var_ctr != 0; var_ctr--) {
        if (recent_x_val != index && recent_y_val != index) {
            var_r4 += *(spawn_weights - 0x92);
            if (var_r4 >= rand_int) {
                Item_804A0E24.y = recent_x_val;
                Item_804A0E24.x = index;
                return index - Pokemon_Tosakinto;
            }
        }
        spawn_weights++;
        index++;
    }
    return 0;
}
#endif

bool it_8027AB64(Item_GObj* item_gobj)
{
    u8 _pad[8];
    SpawnItem spawn;
    Item* item2; // permuterslop
    Item* item;
    u32 temp_r3;
    PAD_STACK(16);

    item = item_gobj->user_data;
    temp_r3 = gm_8016AEB8();
    if (temp_r3 != 0) {
        if (temp_r3 == 1) {
            spawn.kind = it_8027A9B8(item);
        } else {
            spawn.kind = temp_r3 - Pokemon_Tosakinto;
        }
    } else if (gm_8018841C()) {
        spawn.kind = (&it_803F2ED0 == NULL) ? Pokemon_Sonans
                                            : it_8027A780(item, &it_803F2ED0);
    } else if (gm_801A4310() == 0x18) {
        spawn.kind = it_8027AB64_SelectKind(item);
    } else {
        spawn.kind = db_GetCurrentlySelectedPokemon();
        if (spawn.kind == (enum ItemKind) Pokemon_ID_Tosakinto) {
            spawn.kind = it_8027A4D4(item);
        } else {
            spawn.kind--;
        }
        if (spawn.kind == (enum ItemKind) Pokemon_ID_Metamon &&
            (it_8026B3C0(Pokemon_Metamon) != 0 || ftLib_800860C4() == 4))
        {
            spawn.kind = (enum ItemKind) Pokemon_ID_Tosakinto;
        }
    }

    item2 = item_gobj->user_data;
    {
        itPokemonSpawn_DatAttrs* attrs =
            item2->xC4_article_data->x4_specialAttributes;
        Vec3* prev_pos = &spawn.prev_pos;
        spawn.vel.z = 0.0f;
        spawn.vel.x = 0.0f;
        spawn.vel.y = attrs->x8;
        *prev_pos = item2->pos;
        prev_pos->z = 0.0f;
        it_8026BB88(item_gobj, &spawn.pos);
        spawn.x3C_damage = 0;
        spawn.facing_dir = it_8026B6A8(prev_pos, item2->owner);
        spawn.kind = spawn.kind + Pokemon_Tosakinto;
        spawn.x0_parent_gobj = item2->owner;
        spawn.x4_parent_gobj2 = item_gobj;
        spawn.x44_flag.b0 = 1;
        spawn.x40 = 0;
        if (spawn.kind == Pokemon_Cerebi) {
            gm_80172C04();
        }
        if (spawn.kind == Pokemon_Mew) {
            gm_80172BC4();
        }
    }
    {
        Item_GObj* spawn_gobj = Item_80268B18(&spawn);
        if (spawn_gobj != NULL) {
            it_8027AAA0(item_gobj, spawn_gobj->user_data, spawn.kind);
            pl_8003E70C(spawn_gobj);
            db_80225DD8(spawn_gobj, item->owner);
            it_8027B288(spawn_gobj, 0x440060);
            it_8027B564(spawn_gobj);
            return true;
        }
    }
    return false;
}

void it_8027ADEC(int arg0, Item_GObj* item_gobj, HSD_JObj* arg2, f32 arg3)
{
    f32 sp1C;
    Item* item = GET_ITEM(item_gobj);
    sp1C = 1.0F;
    sp1C = item->xCC_item_attr->x60_scale * (1.0F / arg3);
    efSync_Spawn(arg0, item_gobj, arg2, &sp1C);
}

bool it_8027AE34(Item_GObj* item_gobj)
{
    Quaternion rotate;
    HSD_JObj* item_jobj;
    Item* item;
    PAD_STACK(4);

    item_jobj = item_gobj->hsd_obj;
    item = GET_ITEM(item_gobj);
    rotate = it_803B8588;
    item->x40_vel.x = -item->x40_vel.x * item->xC70;
    item->facing_dir = -item->facing_dir;
    item->xD44_lifeTimer = item->xD48_halfLifeTimer;
    rotate.y = IT_M_PI_2 * item->facing_dir;
    HSD_JObjSetRotation(item_jobj, &rotate);
    return false;
}

bool it_8027AF50(Item_GObj* item_gobj)
{
    Quaternion rotate;
    Item* item = GET_ITEM(item_gobj);
    HSD_JObj* item_jobj = GET_JOBJ(item_gobj);
    rotate = it_803B8598;
    lbVector_Mirror(&item->x40_vel, &item->xC58);
    it_80272980(item_gobj);
    rotate.y = IT_M_PI_2 * item->facing_dir;
    HSD_JObjSetRotation(item_jobj, &rotate);
    return false;
}

void it_8027B070(Item_GObj* item_gobj, Fighter_GObj* owner_gobj)
{
    Item* item = GET_ITEM(item_gobj);
    Fighter* fighter = GET_FIGHTER(owner_gobj);
    item->xD88_attackID = fighter->x2068_attackID;
    item->xD8C_attack_instance = fighter->x206C_attack_instance;
    item->xD90 = fighter->x2070;
    item->xD94 = fighter->x2074.x2074_vec;
    item->xD9C = fighter->x2074.x207C;
    item->xDA4_word = fighter->x2074.x2084;
    item->xDA8_short = fighter->x2074.x2088;
}

void it_8027B0C4(Item_GObj* item_gobj, SpawnItem* spawn)
{
    u8 _2[8];
    union Struct2070 sp24;

    if (ftLib_80086960(spawn->x0_parent_gobj)) {
        if (ftLib_80086960(spawn->x4_parent_gobj2)) {
            it_8027B070(item_gobj, spawn->x4_parent_gobj2);
        } else {
            Item* owner_item = spawn->x4_parent_gobj2->user_data;
            Item* spawn_item = GET_ITEM(item_gobj);
            spawn_item->xD88_attackID = owner_item->xD88_attackID;
            spawn_item->xD8C_attack_instance =
                owner_item->xD8C_attack_instance;
            spawn_item->xD90 = owner_item->xD90;
            spawn_item->xD94 = owner_item->xD94;
            spawn_item->xD9C = owner_item->xD9C;
            spawn_item->xDA4_word = owner_item->xDA4_word;
            spawn_item->xDA8_short = owner_item->xDA8_short;
        }
    } else {
        Item* spawn_item = GET_ITEM(item_gobj);
        sp24.x2070_int = 0;
        spawn_item->xD88_attackID = 1;
        spawn_item->xD8C_attack_instance = 0;
        spawn_item->xD90 = sp24;
        ft_80089768(&spawn_item->xD94);
        spawn_item->xDA8_short = 0;
    }
}

void it_8027B1F4(Item_GObj* item_gobj)
{
    Item* item = GET_ITEM(item_gobj);
    union Struct2070 sp10;

    sp10.x2070_int = 0;
    item->xD88_attackID = 1;
    item->xD8C_attack_instance = 0;
    item->xD90 = sp10;
    item->xDA8_short = 0;
    if (ftLib_80086960(item->owner)) {
        struct Struct2074* temp_r3 = ft_800898A8((Fighter_GObj*) item->owner);
        item->xD94 = temp_r3->x2074_vec;
        item->xD9C = temp_r3->x207C;
        item->xDA4_word = temp_r3->x2084;
        return;
    }
    ft_80089768(&item->xD94);
}

void it_8027B288(Item_GObj* item_gobj, volatile u32 arg1)
{
    union Struct2070 sp14;
    Item* item;
    struct Struct2074* temp_r3;
    PAD_STACK(4);

    item = item_gobj->user_data;
    sp14.x2070_int = arg1;
    if ((sp14.x2073 == 0) || (sp14.x2073 != item->xD90.x2073)) {
        item->xDA8_short = plAttack_80037B08();
    }
    item->xD90 = sp14;
    if (ftLib_80086960(item->owner)) {
        temp_r3 = ft_800898A8(item->owner);
        item->xD94 = temp_r3->x2074_vec;
        item->xD9C = temp_r3->x207C;
        item->xDA4_word = temp_r3->x2084;
        return;
    }
    ft_80089768(&item->xD94);
}

void it_8027B330(Item_GObj* item_gobj, u32 arg1)
{
    Item* item = GET_ITEM(item_gobj);
    if (arg1 == 1 || arg1 != item->xD88_attackID) {
        item->xD88_attackID = arg1;
        item->xD8C_attack_instance = plStale_IncrementAttackInstance();
    }
}

void it_8027B378(Fighter_GObj* fighter_gobj, Item_GObj* item_gobj, f32 arg2)
{
    s32 temp_r31;
    u8 temp_r30;
    u16 temp_r3;
    PAD_STACK(4);

    if (it_8026B6C8(item_gobj)) {
        temp_r30 = ft_80089884(fighter_gobj)->x2073;
        temp_r31 = ftLib_800874BC(fighter_gobj);
        temp_r3 = ftLib_80086BE0(fighter_gobj);
        pl_8003EB30(arg2, temp_r3, temp_r31, 6, 0, temp_r30);
    }
}

void it_8027B408(Item_GObj* item_gobj1, Item_GObj* item_gobj2, f32 arg8)
{
    s32 temp_r31;
    Item* item1;
    u16 temp_r3;

    if (it_8026B6C8(item_gobj2)) {
        item1 = item_gobj1->user_data;
        if (ftLib_80086960(item1->owner)) {
            HSD_GObj* owner = item1->owner;
            temp_r31 = ftLib_800874BC(owner);
            temp_r3 = ftLib_80086BE0(owner);
            pl_8003EB30(arg8, temp_r3, temp_r31, 6, 0, item1->xD90.x2073);
        }
    }
}

void it_8027B4A4(Fighter_GObj* item_gobj1, Item_GObj* item_gobj2)
{
    void* temp_r31;

    if (it_8026B6C8(item_gobj2)) {
        temp_r31 = (void*) ft_800898A8(item_gobj1);
        pl_800384DC(item_gobj1, ft_80089884(item_gobj1)->x2073, temp_r31);
    }
}

void it_8027B508(Item_GObj* item_gobj1, Item_GObj* item_gobj2)
{
    if (it_8026B6C8(item_gobj2)) {
        Item* item1 = GET_ITEM(item_gobj1);
        if (ftLib_80086960(item1->owner)) {
            pl_800384DC(item1->owner, item1->xD90.x2073, &item1->xD94);
        }
    }
}

void it_8027B564(Item_GObj* item_gobj)
{
    union Struct2070 sp10;
    Item* item;

    item = GET_ITEM(item_gobj);
    if (ftLib_80086960(item->owner)) {
        sp10 = item->xD90;
        pl_80037DF4(item->owner, &sp10);
    }
}
