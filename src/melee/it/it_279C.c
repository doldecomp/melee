#include "it_279C.h"

#include "it_2725.h"
#include "ithitbox.h"
#include "itzako.h"

#include "baselib/random.h"
#include "db/db.h"
#include "ef/efsync.h"
#include "ft/fighter.h"
#include "ft/ft_0892.h"
#include "ft/ftlib.h"
#include "gm/gm_unsplit.h"
#include "it/inlines.h"
#include "it/itdraw.h"
#include "it/items/itcerebi.h"
#include "it/items/itchicorita.h"
#include "it/items/itentei.h"
#include "it/items/itfire.h"
#include "it/items/itfreezer.h"
#include "it/items/itfushigibana.h"
#include "it/items/ithassam.h"
#include "it/items/ithinoarashi.h"
#include "it/items/ithitodeman.h"
#include "it/items/ithouou.h"
#include "it/items/itkabigon.h"
#include "it/items/itkamex.h"
#include "it/items/itkireihana.h"
#include "it/items/itlizardon.h"
#include "it/items/itlucky.h"
#include "it/items/itlugia.h"
#include "it/items/itmaril.h"
#include "it/items/itmarumine.h"
#include "it/items/itmatadogas.h"
#include "it/items/itmetamon.h"
#include "it/items/itmew.h"
#include "it/items/itoldkuri.h"
#include "it/items/itpippi.h"
#include "it/items/itporygon2.h"
#include "it/items/itraikou.h"
#include "it/items/itsonans.h"
#include "it/items/itsuikun.h"
#include "it/items/itthunder.h"
#include "it/items/ittogepy.h"
#include "it/items/ittosakinto.h"
#include "it/items/itunknown.h"
#include "it/itgroundcoll.h"
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

static ItemKind common_pokemon[] = {
    // Common Pokemon
    It_PKind_Tosakinto, It_PKind_Chicorita,   It_PKind_Kabigon,
    It_PKind_Kamex,     It_PKind_Matadogas,   It_PKind_Lizardon,
    It_PKind_Sonans,    It_PKind_Hassam,      It_PKind_Unknown,
    It_PKind_Kireihana, It_PKind_Marumine,    It_PKind_Metamon,
    It_PKind_Pippi,     It_PKind_Togepy,      It_PKind_Hitodeman,
    It_PKind_Lucky,     It_PKind_Porygon2,    It_PKind_Hinoarashi,
    It_PKind_Maril,     It_PKind_Fushigibana, It_PKind_Terminate,
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

#ifdef MUST_MATCH
#pragma push
#pragma dont_inline on
#endif

void it_80279CDC(Item_GObj* item_gobj, f32 scale)
{
    it_8027A13C(item_gobj);
    it_80279D5C(item_gobj, scale);
    it_8026B3A8(item_gobj);
    it_802756D0(item_gobj);
    it_8026BDB4(item_gobj);
}

#ifdef MUST_MATCH
#pragma pop
#endif

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
        if (item->xDD4_itemVar.pokemon_spawn.x54 <=
            item->xDD4_itemVar.pokemon_spawn.x58)
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

#ifdef MUST_MATCH
#pragma push
#pragma dont_inline on
#endif

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

#ifdef MUST_MATCH
#pragma pop
#endif

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

s32 it_8027A364(Item* item)
{
    itPokemonSpawn_DatAttrs* attr =
        item->xC4_article_data->x4_specialAttributes;
    int ret_val = 1;
    int i;
    int start = It_PKind_Start;
    int end = It_PKind_Terminate;

    for (i = start; i < end; i++) {
        if (Item_804A0E24.x != i && Item_804A0E24.y != i) {
            ret_val += attr->pokemon_spawn_weights[i - It_PKind_Start];
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
    for (i = It_PKind_Start; i < It_PKind_Terminate; i++) {
        int y = Item_804A0E24.y;
        int x = Item_804A0E24.x;
        if (x != i && y != i) {
            var_r3 += attr->pokemon_spawn_weights[i - It_PKind_Start];
            if (var_r3 >= rand_int) {
                Item_804A0E24.y = x;
                Item_804A0E24.x = i;
                return i - It_PKind_Start;
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
        if (kind == It_PKind_Terminate) {
            break;
        }
        if (x != kind && y != kind) {
            buf->x = kind;
            cnt++;
            buf->y = attr->pokemon_spawn_weights[((ItemKind*) arg1)[i] -
                                                 It_PKind_Start];
            total += buf->y;
            buf++;
        }
    }
    rand_int = HSD_Randi(total);
    accum = 0;
    result = It_PKind_Sonans;
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
    return result - It_PKind_Start;
}

s32 it_8027A9B8(Item* item)
{
    void* vec;

    vec = gm_801BEC54();
    if (vec == NULL) {
        return It_PKind_Sonans;
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
    if (arg2 == It_PKind_Marumine) {
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
    return attr->pokemon_spawn_weights[index - It_PKind_Start];
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
    index = It_PKind_Start;
    for (var_ctr = 30; var_ctr != 0; var_ctr--) {
        if (recent_x_val != index && recent_y_val != index) {
            var_r4 += it_8027AB64_SpawnWeight(attr, index);
            if (var_r4 >= rand_int) {
                Item_804A0E24.y = recent_x_val;
                Item_804A0E24.x = index;
                return index - It_PKind_Start;
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
    index = It_PKind_Start;
    for (var_ctr = 30; var_ctr != 0; var_ctr--) {
        if (recent_x_val != index && recent_y_val != index) {
            var_r4 += *(spawn_weights - 0x92);
            if (var_r4 >= rand_int) {
                Item_804A0E24.y = recent_x_val;
                Item_804A0E24.x = index;
                return index - It_PKind_Start;
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
            spawn.kind = temp_r3 - It_PKind_Start;
        }
    } else if (gm_8018841C()) {
        spawn.kind =
#ifdef MUST_MATCH
            (&common_pokemon == NULL) ? It_PKind_Sonans :
#endif
                                      it_8027A780(item, &common_pokemon);

    } else if (gm_GetCurrentGameMode() == GM_OPENING_MV) {
        spawn.kind = it_8027AB64_SelectKind(item);
    } else {
        spawn.kind = db_GetCurrentlySelectedPokemon();
        if (spawn.kind == (enum ItemKind) Pokemon_ID_Tosakinto) {
            spawn.kind = it_8027A4D4(item);
        } else {
            spawn.kind--;
        }
        if (spawn.kind == (enum ItemKind) Pokemon_ID_Metamon &&
            (it_8026B3C0(It_PKind_Metamon) != 0 || ftLib_800860C4() == 4))
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
        spawn.kind = spawn.kind + It_PKind_Start;
        spawn.x0_parent_gobj = item2->owner;
        spawn.x4_parent_gobj2 = item_gobj;
        spawn.x44_flag.b0 = 1;
        spawn.x40 = 0;
        if (spawn.kind == It_PKind_Cerebi) {
            gm_80172C04();
        }
        if (spawn.kind == It_PKind_Mew) {
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
