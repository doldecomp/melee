#include "ftdata.h"

#include "ft_0877.h"

#include <platform.h>

#include "ef/efasync.h"

#include "forward.h"

#include "ft/fighter.h"

#include "ft/forward.h"

#include "ft/ftdata.h"
#include "ft/inlines.h"
#include "ft/types.h"
#include "ftCaptain/ftcaptain.h"
#include "ftCaptain/ftcaptainspecialhi.h"
#include "ftCaptain/ftcaptainspeciallw.h"
#include "ftCaptain/ftcaptainspecialn.h"
#include "ftCaptain/ftcaptainspecials.h"
#include "ftCLink/ftclink.h"
#include "ftCrazyHand/ftcrazyhand.h"
#include "ftDonkey/ftdonkey.h"
#include "ftDonkey/ftdonkeyspecialhi.h"
#include "ftDonkey/ftdonkeyspeciallw.h"
#include "ftDonkey/ftdonkeyspecialn.h"
#include "ftDonkey/ftdonkeyspecials.h"
#include "ftDrMario/ftdrmario.h"
#include "ftEmblem/ftemblem.h"
#include "ftFalco/ftfalco.h"
#include "ftFox/ftfox.h"
#include "ftFox/ftfoxspecialhi.h"
#include "ftFox/ftfoxspeciallw.h"
#include "ftFox/ftfoxspecialn.h"
#include "ftFox/ftfoxspecials.h"
#include "ftGameWatch/ftgamewatch.h"
#include "ftGameWatch/ftgamewatchspecialhi.h"
#include "ftGameWatch/ftgamewatchspeciallw.h"
#include "ftGameWatch/ftgamewatchspecialn.h"
#include "ftGameWatch/ftgamewatchspecials.h"
#include "ftGanon/ftganon.h"
#include "ftGigaKoopa/ftgkoopa.h"
#include "ftKirby/ftkirby.h"
#include "ftKirby/ftkirbyspecialhi.h"
#include "ftKoopa/ftkoopa.h"
#include "ftKoopa/ftkoopaspecialhi.h"
#include "ftKoopa/ftkoopaspeciallw.h"
#include "ftKoopa/ftkoopaspecialn.h"
#include "ftKoopa/ftkoopaspecials.h"
#include "ftLink/ftlink.h"
#include "ftLink/ftlinkspecialhi.h"
#include "ftLink/ftlinkspeciallw.h"
#include "ftLink/ftlinkspecialn.h"
#include "ftLink/ftlinkspecials.h"
#include "ftLuigi/ftluigi.h"
#include "ftLuigi/ftluigispecialhi.h"
#include "ftLuigi/ftluigispeciallw.h"
#include "ftLuigi/ftluigispecialn.h"
#include "ftLuigi/ftluigispecials.h"
#include "ftMario/ftmario.h"
#include "ftMario/ftmariospecialhi.h"
#include "ftMario/ftmariospeciallw.h"
#include "ftMario/ftmariospecialn.h"
#include "ftMario/ftmariospecials.h"
#include "ftMario/ftmariostrings.h"
#include "ftMars/ftmars.h"
#include "ftMars/ftmarsspecialhi.h"
#include "ftMars/ftmarsspeciallw.h"
#include "ftMars/ftmarsspecialn.h"
#include "ftMars/ftmarsspecials.h"
#include "ftMasterHand/ftmasterhand.h"
#include "ftMewtwo/ftmewtwo.h"
#include "ftMewtwo/ftmewtwospecialhi.h"
#include "ftMewtwo/ftmewtwospeciallw.h"
#include "ftMewtwo/ftmewtwospecialn.h"
#include "ftMewtwo/ftmewtwospecials.h"
#include "ftNana/ftnana.h"
#include "ftNess/ftness.h"
#include "ftNess/ftnessspecialhi.h"
#include "ftNess/ftnessspeciallw.h"
#include "ftNess/ftnessspecialn.h"
#include "ftNess/ftnessspecials.h"
#include "ftPeach/ftpeach.h"
#include "ftPeach/ftpeachspecialhi.h"
#include "ftPeach/ftpeachspeciallw.h"
#include "ftPeach/ftpeachspecialn.h"
#include "ftPeach/ftpeachspecials.h"
#include "ftPichu/ftpichu.h"
#include "ftPikachu/ftpikachu.h"
#include "ftPikachu/ftpikachuspecialhi.h"
#include "ftPikachu/ftpikachuspeciallw.h"
#include "ftPikachu/ftpikachuspecialn.h"
#include "ftPikachu/ftpikachuspecials.h"
#include "ftPopo/ftpopo.h"
#include "ftPopo/ftpopospecialhi.h"
#include "ftPopo/ftpopospeciallw.h"
#include "ftPopo/ftpopospecialn.h"
#include "ftPopo/ftpopospecials.h"
#include "ftPurin/ftpurin.h"
#include "ftPurin/ftpurinspecialhi.h"
#include "ftPurin/ftpurinspeciallw.h"
#include "ftPurin/ftpurinspecialn.h"
#include "ftPurin/ftpurinspecials.h"
#include "ftSamus/ftsamus.h"
#include "ftSamus/ftsamusspecialhi.h"
#include "ftSamus/ftsamusspeciallw1.h"
#include "ftSamus/ftsamusspecialn.h"
#include "ftSamus/ftsamusspecials.h"
#include "ftSandbag/ftsandbag.h"
#include "ftSeak/ftseak.h"
#include "ftSeak/ftseakspecialhi.h"
#include "ftSeak/ftseakspeciallw.h"
#include "ftSeak/ftseakspecialn.h"
#include "ftSeak/ftseakspecials.h"
#include "ftYoshi/ftyoshi.h"
#include "ftYoshi/ftyoshiguard.h"
#include "ftYoshi/ftyoshispecialhi.h"
#include "ftYoshi/ftyoshispecialn.h"
#include "ftYoshi/ftyoshispecials.h"
#include "ftZakoBoy/ftboy.h"
#include "ftZakoGirl/ftgirl.h"
#include "ftZelda/ftzelda.h"
#include "ftZelda/ftzeldaspecialhi.h"
#include "ftZelda/ftzeldaspeciallw.h"
#include "ftZelda/ftzeldaspecialn.h"
#include "ftZelda/ftzeldaspecials.h"
#include "lb/lbarchive.h"
#include "lb/lbarq.h"
#include "lb/lbdvd.h"
#include "lb/lbfile.h"
#include "pl/player.h"

#include <baselib/forward.h>

#include <string.h>
#include <baselib/debug.h>
#include <baselib/gobj.h>
#include <baselib/jobj.h>
#include <baselib/objalloc.h>

typedef struct ft_8045993C_t {
    /* +0 */ u32 pad_x0;
    /* +4 */ u8 pad_x4[0x2];
    /* +6:0 */ u16 x6_b0 : 1;
    /* +6:1-2 */ u16 x6_b1_b2 : 2;
} ft_8045993C_t;

/* 4598B8 */ ftData* gFtDataList[FTKIND_MAX];
/* 45993C */ ft_8045993C_t ft_8045993C[6];
/* 45996C */ int ft_8045996C[FTKIND_MAX];

/// @todo All one struct maybe?
#ifdef MUST_MATCH
static void order_bss(void)
{
    (void) gFtDataList;
    (void) ft_8045993C;
    (void) ft_8045996C;
}
#endif

void ft_8008521C(HSD_GObj* gobj)
{
    Fighter* fp = GET_FIGHTER(gobj);
    HSD_JObj* jobj = GET_JOBJ(gobj);
    Vec3 pos;

    HSD_JObjGetTranslation(jobj, &pos);
    fp->self_vel.x = pos.x - fp->cur_pos.x;
    fp->self_vel.y = pos.y - fp->cur_pos.y;
    fp->self_vel.z = pos.z - fp->cur_pos.z;
}

static inline void ft_800852B0_Reset_ft_8045993C(ftData** list, int i)
{
    /// @todo Bitfields seem off
    ((ft_8045993C_t*) &list[FTKIND_MAX])[i].pad_x0 = 0;
    ((ft_8045993C_t*) &list[FTKIND_MAX])[i].x6_b0 = 0;
    ((ft_8045993C_t*) &list[FTKIND_MAX])[i].x6_b1_b2 = 0;
}

void ft_800852B0(void)
{
    ftData** list;
    ftData_UnkCountStruct* unk0 =
        (ftData_UnkCountStruct*) &CostumeListsForeachCharacter[FTKIND_MAX];
    ftData_UnkCountStruct* pairs =
        (ftData_UnkCountStruct*) ((u8*) CostumeListsForeachCharacter + 5940);
    int i;
    int new_var = 0;

    for (i = 0; i < FTKIND_MAX; ++i) {
        int costume_idx = new_var;
        list = gFtDataList;
        list[i] = NULL;
        for (costume_idx = new_var;
             costume_idx < (s32) CostumeListsForeachCharacter[i].numCostumes;
             ++costume_idx)
        {
            CostumeListsForeachCharacter[i].costume_list[costume_idx].joint =
                NULL;
            CostumeListsForeachCharacter[i].costume_list[costume_idx].pad_x8 =
                0;
        }
        unk0[i].data = NULL;
        pairs[i].data = NULL;
    }
    ft_800852B0_Reset_ft_8045993C(list, new_var);
    ft_800852B0_Reset_ft_8045993C(list, 1);
    ft_800852B0_Reset_ft_8045993C(list, 2);
    ft_800852B0_Reset_ft_8045993C(list, 3);
    ft_800852B0_Reset_ft_8045993C(list, 4);
    ft_800852B0_Reset_ft_8045993C(list, 5);
}

void ft_8008549C(void)
{
    int i;
    for (i = 0; i < FTKIND_MAX; i++) {
        ft_8045996C[i] = 0;
    }
}

/* 3C0EC0 */ struct UnkCostumeList CostumeListsForeachCharacter[FTKIND_MAX] = {
    { ftMr_CostumeList, ARRAY_SIZE(ftMr_CostumeList) },
    { ftFx_CostumeList, ARRAY_SIZE(ftFx_CostumeList) },
    { ftCa_CostumeList, ARRAY_SIZE(ftCa_CostumeList) },
    { ftDk_CostumeList, ARRAY_SIZE(ftDk_CostumeList) },
    { ftKb_CostumeList, ARRAY_SIZE(ftKb_CostumeList) },
    { ftKp_CostumeList, ARRAY_SIZE(ftKp_CostumeList) },
    { ftLk_CostumeList, ARRAY_SIZE(ftLk_CostumeList) },
    { ftSk_CostumeList, ARRAY_SIZE(ftSk_CostumeList) },
    { ftNs_CostumeList, ARRAY_SIZE(ftNs_CostumeList) },
    { ftPe_CostumeList, ARRAY_SIZE(ftPe_CostumeList) },
    { ftPp_CostumeList, ARRAY_SIZE(ftPp_CostumeList) },
    { ftNn_CostumeList, FTNANA_COSTUME_COUNT },
    { ftPk_CostumeList, ARRAY_SIZE(ftPk_CostumeList) },
    { ftSs_CostumeList, ARRAY_SIZE(ftSs_CostumeList) },
    { ftYs_CostumeList, ARRAY_SIZE(ftYs_CostumeList) },
    { ftPr_CostumeList, ARRAY_SIZE(ftPr_CostumeList) },
    { ftMt_CostumeList, ARRAY_SIZE(ftMt_CostumeList) },
    { ftLg_CostumeList, ARRAY_SIZE(ftLg_CostumeList) },
    { ftMs_CostumeList, ARRAY_SIZE(ftMs_CostumeList) },
    { ftZd_CostumeList, ARRAY_SIZE(ftZd_CostumeList) },
    { ftCl_CostumeList, ARRAY_SIZE(ftCl_CostumeList) },
    { ftDr_CostumeList, ARRAY_SIZE(ftDr_CostumeList) },
    { ftFc_CostumeList, ARRAY_SIZE(ftFc_CostumeList) },
    { ftPc_CostumeList, ARRAY_SIZE(ftPc_CostumeList) },
    { ftGw_CostumeList, ARRAY_SIZE(ftGw_CostumeList) },
    { ftGn_CostumeList, ARRAY_SIZE(ftGn_CostumeList) },
    { ftFe_CostumeList, ARRAY_SIZE(ftFe_CostumeList) },
    { ftMh_CostumeList, ARRAY_SIZE(ftMh_CostumeList) },
    { ftCh_CostumeList, ARRAY_SIZE(ftCh_CostumeList) },
    { ftBo_CostumeList, ARRAY_SIZE(ftBo_CostumeList) },
    { ftGl_CostumeList, ARRAY_SIZE(ftGl_CostumeList) },
    { ftGk_CostumeList, ARRAY_SIZE(ftGk_CostumeList) },
    { ftSb_CostumeList, ARRAY_SIZE(ftSb_CostumeList) }
};

ftData_UnkCountStruct ftData_Table_Unk0[FTKIND_MAX] = {
    { 0, 303 }, { 0, 327 }, { 0, 318 }, { 0, 337 }, { 0, 479 }, { 0, 316 },
    { 0, 314 }, { 0, 317 }, { 0, 326 }, { 0, 318 }, { 0, 321 }, { 0, 321 },
    { 0, 320 }, { 0, 313 }, { 0, 314 }, { 0, 327 }, { 0, 314 }, { 0, 312 },
    { 0, 327 }, { 0, 311 }, { 0, 314 }, { 0, 303 }, { 0, 327 }, { 0, 320 },
    { 0, 323 }, { 0, 318 }, { 0, 327 }, { 0, 345 }, { 0, 344 }, { 0, 295 },
    { 0, 295 }, { 0, 316 }, { 0, 296 },
};

Event ftData_Table_Unk1[FTKIND_MAX] = {
    NULL,
    NULL,
    NULL,
    NULL,
    ftKb_Init_800EE528,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    ftPr_Init_8013C2F8,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
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

HSD_GObjEvent ftData_OnLoad[FTKIND_MAX] = {
    ftMr_Init_OnLoad, ftFx_Init_OnLoad, ftCa_Init_OnLoad, ftDk_Init_OnLoad,
    ftKb_Init_OnLoad, ftKp_Init_OnLoad, ftLk_Init_OnLoad, ftSk_Init_OnLoad,
    ftNs_Init_OnLoad, ftPe_Init_OnLoad, ftPp_Init_OnLoad, ftNn_Init_OnLoad,
    ftPk_Init_OnLoad, ftSs_Init_OnLoad, ftYs_Init_OnLoad, ftPr_Init_OnLoad,
    ftMt_Init_OnLoad, ftLg_Init_OnLoad, ftMs_Init_OnLoad, ftZd_Init_OnLoad,
    ftCl_Init_OnLoad, ftDr_Init_OnLoad, ftFc_Init_OnLoad, ftPc_Init_OnLoad,
    ftGw_Init_OnLoad, ftGn_Init_OnLoad, ftFe_Init_OnLoad, ftMh_Init_OnLoad,
    ftCh_Init_OnLoad, ftBo_Init_OnLoad, ftGl_Init_OnLoad, ftGk_Init_OnLoad,
    ftSb_Init_OnLoad,
};

HSD_GObjEvent ftData_OnDeath[FTKIND_MAX] = {
    ftMr_Init_OnDeath, ftFx_Init_OnDeath, ftCa_Init_OnDeath, ftDk_Init_OnDeath,
    ftKb_Init_OnDeath, ftKp_Init_OnDeath, ftLk_Init_OnDeath, ftSk_Init_OnDeath,
    ftNs_Init_OnDeath, ftPe_Init_OnDeath, ftPp_Init_OnDeath, ftNn_Init_OnDeath,
    ftPk_Init_OnDeath, ftSs_Init_OnDeath, ftYs_Init_OnDeath, ftPr_Init_OnDeath,
    ftMt_Init_OnDeath, ftLg_Init_OnDeath, ftMs_Init_OnDeath, ftZd_Init_OnDeath,
    ftCl_Init_OnDeath, ftDr_Init_OnDeath, ftFc_Init_OnDeath, ftPc_Init_OnDeath,
    ftGw_Init_OnDeath, ftGn_Init_OnDeath, ftFe_Init_OnDeath, ftMh_Init_OnDeath,
    ftCh_Init_OnDeath, ftBo_Init_OnDeath, ftGl_Init_OnDeath, ftGk_Init_OnDeath,
    ftSb_Init_OnDeath,
};

HSD_GObjEvent ftData_OnUserDataRemove[FTKIND_MAX] = {
    NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
    NULL, NULL, NULL, NULL, NULL, NULL, NULL, ftPr_Init_OnUserDataRemove,
    NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
    NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
    NULL,
};

MotionState* ftData_CharacterStateTables[FTKIND_MAX] = {
    ftMr_Init_MotionStateTable,
    ftFx_Init_MotionStateTable,
    ftCa_Init_MotionStateTable,
    ftDk_Init_MotionStateTable,
    ftKb_Init_MotionStateTable,
    ftKp_Init_MotionStateTable,
    ftLk_Init_MotionStateTable,
    ftSk_Init_MotionStateTable,
    ftNs_Init_MotionStateTable,
    ftPe_Init_MotionStateTable,
    ftPp_Init_MotionStateTable,
    ftNn_Init_MotionStateTable,
    ftPk_Init_MotionStateTable,
    ftSs_Init_MotionStateTable,
    ftYs_Init_MotionStateTable,
    ftPr_Init_MotionStateTable,
    ftMt_Init_MotionStateTable,
    ftLg_Init_MotionStateTable,
    ftMs_Init_MotionStateTable,
    ftZd_Init_MotionStateTable,
    ftCl_Init_MotionStateTable,
    ftDr_Init_MotionStateTable,
    ftFc_Init_MotionStateTable,
    ftPc_Init_MotionStateTable,
    ftGw_Init_MotionStateTable,
    ftGn_Init_MotionStateTable,
    ftFe_Init_MotionStateTable,
    ftMh_Init_MotionStateTable,
    ftCh_Init_MotionStateTable,
    NULL,
    NULL,
    ftGk_Init_MotionStateTable,
    ftSb_Init_MotionStateTable,
};

MotionState* ftData_UnkMotionStates0[FTKIND_MAX] = {
    ftMr_Init_UnkMotionStates0,
    NULL,
    NULL,
    NULL,
    ftKb_Init_UnkMotionStates0,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    ftLg_Init_UnkMotionStates0,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    ftGk_Init_UnkMotionStates0,
    NULL,
};

HSD_GObjEvent ftData_SpecialS[FTKIND_MAX] = {
    ftMr_SpecialS_Enter,
    ftFx_SpecialSStart_Enter,
    ftCa_SpecialS_Enter,
    ftDk_SpecialS_Enter,
    ftKb_SpecialS_Enter,
    ftKp_SpecialS_Enter,
    ftLk_SpecialS_Enter,
    ftSk_SpecialS_Enter,
    ftNs_SpecialS_Enter,
    ftPe_SpecialS_Enter,
    ftPp_SpecialS_Enter,
    NULL,
    ftPk_SpecialS_Enter,
    ftSs_SpecialS_Enter,
    ftYs_SpecialS_Enter,
    ftPr_SpecialS_Enter,
    ftMt_SpecialS_Enter,
    ftLg_SpecialS_Enter,
    ftMs_SpecialS_Enter,
    ftZd_SpecialS_Enter,
    ftLk_SpecialS_Enter,
    ftMr_SpecialS_Enter,
    ftFx_SpecialSStart_Enter,
    ftPk_SpecialS_Enter,
    ftGw_SpecialS_Enter,
    ftCa_SpecialS_Enter,
    ftMs_SpecialS_Enter,
    NULL,
    NULL,
    NULL,
    NULL,
    ftKp_SpecialS_Enter,
    NULL,
};

HSD_GObjEvent ftData_SpecialAirHi[FTKIND_MAX] = {
    ftMr_SpecialAirHi_Enter,
    ftFx_SpecialAirHiStart_Enter,
    ftCa_SpecialAirHi_Enter,
    ftDk_SpecialAirHi_Enter,
    ftKb_SpecialAirHi_Enter,
    ftKp_SpecialAirHi_Enter,
    ftLk_SpecialAirHi_Enter,
    ftSk_SpecialAirHi_Enter,
    ftNs_SpecialAirHiStart_Enter,
    ftPe_SpecialAirHi_Enter,
    ftPp_SpecialAirHi_Enter,
    NULL,
    ftPk_SpecialAirHi_Enter,
    ftSs_SpecialAirHi_Enter,
    ftYs_SpecialAirHi_Enter,
    ftPr_SpecialAirHi_Enter,
    ftMt_SpecialAirHiStart_Enter,
    ftLg_SpecialAirHi_Enter,
    ftMs_SpecialAirHi_Enter,
    ftZd_SpecialAirHi_Enter,
    ftLk_SpecialAirHi_Enter,
    ftMr_SpecialAirHi_Enter,
    ftFx_SpecialAirHiStart_Enter,
    ftPk_SpecialAirHi_Enter,
    ftGw_SpecialAirHi_Enter,
    ftCa_SpecialAirHi_Enter,
    ftMs_SpecialAirHi_Enter,
    NULL,
    NULL,
    NULL,
    NULL,
    ftKp_SpecialAirHi_Enter,
    NULL,
};

HSD_GObjEvent ftData_SpecialAirLw[FTKIND_MAX] = {
    ftMr_SpecialAirLw_Enter,
    ftFx_SpecialAirLw_Enter,
    ftCa_SpecialAirLw_Enter,
    NULL,
    ftKb_SpecialAirLw_Enter,
    ftKp_SpecialAirLw_Enter,
    ftLk_SpecialAirLw_Enter,
    ftSk_SpecialAirLw_Enter,
    ftNs_SpecialAirLwStart_Enter,
    ftPe_SpecialAirLw_Enter,
    ftPp_SpecialAirLw_Enter,
    ftPp_SpecialAirLw_Enter,
    ftPk_SpecialAirLw_Enter,
    ftSs_SpecialAirLw_Enter,
    ftYs_SpecialAirLw_Enter,
    ftPr_SpecialAirLw_Enter,
    ftMt_SpecialAirLw_Enter,
    ftLg_SpecialAirLw_Enter,
    ftMs_SpecialAirLw_Enter,
    ftZd_SpecialAirLw_Enter,
    ftLk_SpecialAirLw_Enter,
    ftMr_SpecialAirLw_Enter,
    ftFx_SpecialAirLw_Enter,
    ftPk_SpecialAirLw_Enter,
    ftGw_SpecialAirLw_Enter,
    ftCa_SpecialAirLw_Enter,
    ftMs_SpecialAirLw_Enter,
    NULL,
    NULL,
    NULL,
    NULL,
    ftKp_SpecialAirLw_Enter,
    NULL,
};

HSD_GObjEvent ftData_SpecialAirS[FTKIND_MAX] = {
    ftMr_SpecialAirS_Enter,
    ftFx_SpecialAirSStart_Enter,
    ftCa_SpecialAirS_Enter,
    ftDk_SpecialAirS_Enter,
    ftKb_SpecialAirS_Enter,
    ftKp_SpecialAirS_Enter,
    ftLk_SpecialAirS_Enter,
    ftSk_SpecialAirS_Enter,
    ftNs_SpecialAirS_Enter,
    ftPe_SpecialAirS_Enter,
    ftPp_SpecialAirS_Enter,
    NULL,
    ftPk_SpecialAirS_Enter,
    ftSs_SpecialAirS_Enter,
    ftYs_SpecialAirS_Enter,
    ftPr_SpecialAirS_Enter,
    ftMt_SpecialAirS_Enter,
    ftLg_SpecialAirS_Enter,
    ftMs_SpecialAirS_Enter,
    ftZd_SpecialAirS_Enter,
    ftLk_SpecialAirS_Enter,
    ftMr_SpecialAirS_Enter,
    ftFx_SpecialAirSStart_Enter,
    ftPk_SpecialAirS_Enter,
    ftGw_SpecialAirS_Enter,
    ftCa_SpecialAirS_Enter,
    ftMs_SpecialAirS_Enter,
    NULL,
    NULL,
    NULL,
    NULL,
    ftKp_SpecialAirS_Enter,
    NULL,
};

HSD_GObjEvent ftData_SpecialAirN[FTKIND_MAX] = {
    ftMr_SpecialAirN_Enter,
    ftFx_SpecialAirN_Enter,
    ftCa_SpecialAirN_Enter,
    ftDk_SpecialAirN_Enter,
    ftKb_SpecialAirN_Enter,
    ftKp_SpecialAirN_Enter,
    ftLk_SpecialAirN_Enter,
    ftSk_SpecialAirN_Enter,
    ftNs_SpecialAirNStart_Enter,
    ftPe_SpecialAirN_Enter,
    ftPp_SpecialAirN_Enter,
    ftPp_SpecialAirN_Enter,
    ftPk_SpecialAirN_Enter,
    ftSs_SpecialAirN_Enter,
    ftYs_SpecialAirN_Enter,
    ftPr_SpecialAirN_Enter,
    ftMt_SpecialAirN_Enter,
    ftLg_SpecialAirN_Enter,
    ftMs_SpecialAirN_Enter,
    ftZd_SpecialAirN_Enter,
    ftLk_SpecialAirN_Enter,
    ftMr_SpecialAirN_Enter,
    ftFx_SpecialAirN_Enter,
    ftPk_SpecialAirN_Enter,
    ftGw_SpecialAirN_Enter,
    ftCa_SpecialAirN_Enter,
    ftMs_SpecialAirN_Enter,
    NULL,
    NULL,
    NULL,
    NULL,
    ftKp_SpecialAirN_Enter,
    NULL,
};

HSD_GObjEvent ftData_SpecialN[FTKIND_MAX] = {
    ftMr_SpecialN_Enter,
    ftFx_SpecialN_Enter,
    ftCa_SpecialN_Enter,
    ftDk_SpecialN_Enter,
    ftKb_SpecialN_Enter,
    ftKp_SpecialN_Enter,
    ftLk_SpecialN_Enter,
    ftSk_SpecialN_Enter,
    ftNs_SpecialNStart_Enter,
    ftPe_SpecialN_Enter,
    ftPp_SpecialN_Enter,
    ftPp_SpecialN_Enter,
    ftPk_SpecialN_Enter,
    ftSs_SpecialN_Enter,
    ftYs_SpecialN_Enter,
    ftPr_SpecialN_Enter,
    ftMt_SpecialN_Enter,
    ftLg_SpecialN_Enter,
    ftMs_SpecialN_Enter,
    ftZd_SpecialN_Enter,
    ftLk_SpecialN_Enter,
    ftMr_SpecialN_Enter,
    ftFx_SpecialN_Enter,
    ftPk_SpecialN_Enter,
    ftGw_SpecialN_Enter,
    ftCa_SpecialN_Enter,
    ftMs_SpecialN_Enter,
    NULL,
    NULL,
    NULL,
    NULL,
    ftKp_SpecialN_Enter,
    NULL,
};

HSD_GObjEvent ftData_SpecialLw[FTKIND_MAX] = {
    ftMr_SpecialLw_Enter,
    ftFx_SpecialLw_Enter,
    ftCa_SpecialLw_Enter,
    ftDk_SpecialLw_Enter,
    ftKb_SpecialLw_Enter,
    ftKp_SpecialLw_Enter,
    ftLk_SpecialLw_Enter,
    ftSk_SpecialLw_Enter,
    ftNs_SpecialLwStart_Enter,
    ftPe_SpecialLw_Enter,
    ftPp_SpecialLw_Enter,
    ftPp_SpecialLw_Enter,
    ftPk_SpecialLw_Enter,
    ftSs_SpecialLw_Enter,
    ftYs_SpecialLw_Enter,
    ftPr_SpecialLw_Enter,
    ftMt_SpecialLw_Enter,
    ftLg_SpecialLw_Enter,
    ftMs_SpecialLw_Enter,
    ftZd_SpecialLw_Enter,
    ftLk_SpecialLw_Enter,
    ftMr_SpecialLw_Enter,
    ftFx_SpecialLw_Enter,
    ftPk_SpecialLw_Enter,
    ftGw_SpecialLw_Enter,
    ftCa_SpecialLw_Enter,
    ftMs_SpecialLw_Enter,
    NULL,
    NULL,
    NULL,
    NULL,
    ftKp_SpecialLw_Enter,
    NULL,
};

HSD_GObjEvent ftData_SpecialHi[FTKIND_MAX] = {
    ftMr_SpecialHi_Enter,
    ftFx_SpecialHi_Enter,
    ftCa_SpecialHi_Enter,
    ftDk_SpecialHi_Enter,
    ftKb_SpecialHi_Enter,
    ftKp_SpecialHi_Enter,
    ftLk_SpecialHi_Enter,
    ftSk_SpecialHi_Enter,
    ftNs_SpecialHiStart_Enter,
    ftPe_SpecialHi_Enter,
    ftPp_SpecialHi_Enter,
    NULL,
    ftPk_SpecialHi_Enter,
    ftSs_SpecialHi_Enter,
    ftYs_SpecialHi_Enter,
    ftPr_SpecialHi_Enter,
    ftMt_SpecialHiStart_Enter,
    ftLg_SpecialHi_Enter,
    ftMs_SpecialHi_Enter,
    ftZd_SpecialHi_Enter,
    ftLk_SpecialHi_Enter,
    ftMr_SpecialHi_Enter,
    ftFx_SpecialHi_Enter,
    ftPk_SpecialHi_Enter,
    ftGw_SpecialHi_Enter,
    ftCa_SpecialHi_Enter,
    ftMs_SpecialHi_Enter,
    NULL,
    NULL,
    NULL,
    NULL,
    ftKp_SpecialHi_Enter,
    NULL,
};

HSD_GObjEvent ftData_OnAbsorb[FTKIND_MAX] = {
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    ftNs_Init_OnAbsorb,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    ftGw_Init_OnAbsorb,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
};

Fighter_ItemEvent ftData_OnItemPickupExt[FTKIND_MAX] = {
    ftMr_Init_OnItemPickup,
    ftFx_Init_OnItemPickup,
    ftCa_Init_OnItemPickup,
    ftDk_Init_OnItemPickup,
    ftKb_Init_OnItemPickup,
    ftKp_Init_OnItemPickup,
    ftLk_Init_OnItemPickupExt,
    ftSk_Init_OnItemPickup,
    ftNs_Init_OnItemPickup,
    ftPe_Init_OnItemPickup,
    ftPp_Init_OnItemPickup,
    ftPp_Init_OnItemPickup,
    ftPk_Init_OnItemPickup,
    ftSs_Init_OnItemPickup,
    ftYs_Init_OnItemPickup,
    ftPr_Init_OnItemPickup,
    ftMt_Init_OnItemPickup,
    ftLg_Init_OnItemPickup,
    ftMs_Init_OnItemPickup,
    ftZd_Init_OnItemPickup,
    ftCl_Init_OnItemPickupExt,
    ftDr_Init_OnItemPickup,
    ftFc_Init_OnItemPickup,
    ftPc_Init_OnItemPickup,
    ftGw_Init_OnItemPickup,
    ftGn_Init_OnItemPickup,
    ftFe_Init_OnItemPickup,
    NULL,
    NULL,
    ftBo_Init_OnItemPickup,
    ftGl_Init_OnItemPickup,
    ftGk_Init_OnItemPickup,
    NULL,
};

HSD_GObjEvent ftData_OnItemInvisible[FTKIND_MAX] = {
    ftMr_Init_OnItemInvisible,
    ftFx_Init_OnItemInvisible,
    ftCa_Init_OnItemInvisible,
    ftDk_Init_OnItemInvisible,
    ftKb_Init_OnItemInvisible,
    ftKp_Init_OnItemInvisible,
    ftLk_Init_OnItemInvisible,
    ftSk_Init_OnItemInvisible,
    ftNs_Init_OnItemInvisible,
    ftPe_Init_OnItemInvisible,
    ftPp_Init_OnItemInvisible,
    ftPp_Init_OnItemInvisible,
    ftPk_Init_OnItemInvisible,
    ftSs_Init_OnItemInvisible,
    ftYs_Init_OnItemInvisible,
    ftPr_Init_OnItemInvisible,
    ftMt_Init_OnItemInvisible,
    ftLg_Init_OnItemInvisible,
    ftMs_Init_OnItemInvisible,
    ftZd_Init_OnItemInvisible,
    ftCl_Init_OnItemInvisible,
    ftDr_Init_OnItemInvisible,
    ftFc_Init_OnItemInvisible,
    ftPc_Init_OnItemInvisible,
    ftGw_Init_OnItemInvisible,
    ftGn_Init_OnItemInvisible,
    ftFe_Init_OnItemInvisible,
    NULL,
    NULL,
    ftBo_Init_OnItemInvisible,
    ftGl_Init_OnItemInvisible,
    ftGk_Init_OnItemInvisible,
    NULL,
};

HSD_GObjEvent ftData_OnItemVisible[FTKIND_MAX] = {
    ftMr_Init_OnItemVisible,
    ftFx_Init_OnItemVisible,
    ftCa_Init_OnItemVisible,
    ftDk_Init_OnItemVisible,
    ftKb_Init_OnItemVisible,
    ftKp_Init_OnItemVisible,
    ftLk_Init_OnItemVisible,
    ftSk_Init_OnItemVisible,
    ftNs_Init_OnItemVisible,
    ftPe_Init_OnItemVisible,
    ftPp_Init_OnItemVisible,
    ftPp_Init_OnItemVisible,
    ftPk_Init_OnItemVisible,
    ftSs_Init_OnItemVisible,
    ftYs_Init_OnItemVisible,
    ftPr_Init_OnItemVisible,
    ftMt_Init_OnItemVisible,
    ftLg_Init_OnItemVisible,
    ftMs_Init_OnItemVisible,
    ftZd_Init_OnItemVisible,
    ftCl_Init_OnItemVisible,
    ftDr_Init_OnItemVisible,
    ftFc_Init_OnItemVisible,
    ftPc_Init_OnItemVisible,
    ftGw_Init_OnItemVisible,
    ftGn_Init_OnItemVisible,
    ftFe_Init_OnItemVisible,
    NULL,
    NULL,
    ftBo_Init_OnItemVisible,
    ftGl_Init_OnItemVisible,
    ftGk_Init_OnItemVisible,
    NULL,
};

Fighter_ItemEvent ftData_OnItemDropExt[FTKIND_MAX] = {
    ftMr_Init_OnItemDrop,
    ftFx_Init_OnItemDrop,
    ftCa_Init_OnItemDrop,
    ftDk_Init_OnItemDrop,
    ftKb_Init_OnItemDrop,
    ftKp_Init_OnItemDrop,
    ftLk_Init_OnItemDropExt,
    ftSk_Init_OnItemDrop,
    ftNs_Init_OnItemDrop,
    ftPe_Init_OnItemDrop,
    ftPp_Init_OnItemDrop,
    ftPp_Init_OnItemDrop,
    ftPk_Init_OnItemDrop,
    ftSs_Init_OnItemDrop,
    ftYs_Init_OnItemDrop,
    ftPr_Init_OnItemDrop,
    ftMt_Init_OnItemDrop,
    ftLg_Init_OnItemDrop,
    ftMs_Init_OnItemDrop,
    ftZd_Init_OnItemDrop,
    ftCl_Init_OnItemDropExt,
    ftDr_Init_OnItemDrop,
    ftFc_Init_OnItemDrop,
    ftPc_Init_OnItemDrop,
    ftGw_Init_OnItemDrop,
    ftGn_Init_OnItemDrop,
    ftFe_Init_OnItemDrop,
    NULL,
    NULL,
    ftBo_Init_OnItemDrop,
    ftGl_Init_OnItemDrop,
    ftGk_Init_OnItemDrop,
    NULL,
};

Fighter_ItemEvent ftData_OnItemPickup[FTKIND_MAX] = {
    ftMr_Init_OnItemPickup,
    ftFx_Init_OnItemPickup,
    ftCa_Init_OnItemPickup,
    ftDk_Init_OnItemPickup,
    ftKb_Init_OnItemPickup,
    ftKp_Init_OnItemPickup,
    ftLk_Init_OnItemPickup,
    ftSk_Init_OnItemPickup,
    ftNs_Init_OnItemPickup,
    ftPe_Init_OnItemPickup,
    ftPp_Init_OnItemPickup,
    ftPp_Init_OnItemPickup,
    ftPk_Init_OnItemPickup,
    ftSs_Init_OnItemPickup,
    ftYs_Init_OnItemPickup,
    ftPr_Init_OnItemPickup,
    ftMt_Init_OnItemPickup,
    ftLg_Init_OnItemPickup,
    ftMs_Init_OnItemPickup,
    ftZd_Init_OnItemPickup,
    ftCl_Init_OnItemPickup,
    ftDr_Init_OnItemPickup,
    ftFc_Init_OnItemPickup,
    ftPc_Init_OnItemPickup,
    ftGw_Init_OnItemPickup,
    ftGn_Init_OnItemPickup,
    ftFe_Init_OnItemPickup,
    NULL,
    NULL,
    ftBo_Init_OnItemPickup,
    ftGl_Init_OnItemPickup,
    ftGk_Init_OnItemPickup,
    NULL,
};

Fighter_ItemEvent ftData_OnItemDrop[FTKIND_MAX] = {
    ftMr_Init_OnItemDrop,
    ftFx_Init_OnItemDrop,
    ftCa_Init_OnItemDrop,
    ftDk_Init_OnItemDrop,
    ftKb_Init_OnItemDrop,
    ftKp_Init_OnItemDrop,
    ftLk_Init_OnItemDrop,
    ftSk_Init_OnItemDrop,
    ftNs_Init_OnItemDrop,
    ftPe_Init_OnItemDrop,
    ftPp_Init_OnItemDrop,
    ftPp_Init_OnItemDrop,
    ftPk_Init_OnItemDrop,
    ftSs_Init_OnItemDrop,
    ftYs_Init_OnItemDrop,
    ftPr_Init_OnItemDrop,
    ftMt_Init_OnItemDrop,
    ftLg_Init_OnItemDrop,
    ftMs_Init_OnItemDrop,
    ftZd_Init_OnItemDrop,
    ftCl_Init_OnItemDrop,
    ftDr_Init_OnItemDrop,
    ftFc_Init_OnItemDrop,
    ftPc_Init_OnItemDrop,
    ftGw_Init_OnItemDrop,
    ftGn_Init_OnItemDrop,
    ftFe_Init_OnItemDrop,
    NULL,
    NULL,
    ftBo_Init_OnItemDrop,
    ftGl_Init_OnItemDrop,
    ftGk_Init_OnItemDrop,
    NULL,
};

HSD_GObjEvent ftData_UnkMotionStates1[FTKIND_MAX] = {
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    ftPk_Init_UnkMotionStates1,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
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

HSD_GObjEvent ftData_UnkMotionStates2[FTKIND_MAX] = {
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    ftPk_Init_UnkMotionStates2,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
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

HSD_GObjEvent ftData_OnKnockbackEnter[FTKIND_MAX] = {
    ftMr_Init_OnKnockbackEnter,
    ftFx_Init_OnKnockbackEnter,
    NULL,
    ftDk_Init_OnKnockbackEnter,
    ftKb_Init_OnKnockbackEnter,
    ftKp_Init_OnKnockbackEnter,
    ftLk_Init_OnKnockbackEnter,
    ftSk_Init_OnKnockbackEnter,
    ftNs_Init_OnKnockbackEnter,
    ftPe_Init_OnKnockbackEnter,
    ftPp_Init_OnKnockbackEnter,
    ftPp_Init_OnKnockbackEnter,
    ftPk_Init_OnKnockbackEnter,
    NULL,
    ftYs_Init_OnKnockbackEnter,
    ftPr_Init_OnKnockbackEnter,
    ftMt_Init_OnKnockbackEnter,
    ftLg_Init_OnKnockbackEnter,
    ftMs_Init_OnKnockbackEnter,
    ftZd_Init_OnKnockbackEnter,
    ftCl_Init_OnKnockbackEnter,
    ftDr_Init_OnKnockbackEnter,
    ftFc_Init_OnKnockbackEnter,
    ftPc_Init_OnKnockbackEnter,
    NULL,
    ftGn_Init_OnKnockbackEnter,
    ftFe_Init_OnKnockbackEnter,
    NULL,
    NULL,
    NULL,
    NULL,
    ftGk_Init_OnKnockbackEnter,
    ftSb_Init_OnKnockbackEnter,
};

HSD_GObjEvent ftData_OnKnockbackExit[FTKIND_MAX] = {
    ftMr_Init_OnKnockbackExit,
    ftFx_Init_OnKnockbackExit,
    NULL,
    ftDk_Init_OnKnockbackExit,
    ftKb_Init_OnKnockbackExit,
    ftKp_Init_OnKnockbackExit,
    ftLk_Init_OnKnockbackExit,
    ftSk_Init_OnKnockbackExit,
    ftNs_Init_OnKnockbackExit,
    ftPe_Init_OnKnockbackExit,
    ftPp_Init_OnKnockbackExit,
    ftPp_Init_OnKnockbackExit,
    ftPk_Init_OnKnockbackExit,
    NULL,
    ftYs_Init_OnKnockbackExit,
    ftPr_Init_OnKnockbackExit,
    ftMt_Init_OnKnockbackExit,
    ftLg_Init_OnKnockbackExit,
    ftMs_Init_OnKnockbackExit,
    ftZd_Init_OnKnockbackExit,
    ftCl_Init_OnKnockbackExit,
    ftDr_Init_OnKnockbackExit,
    ftFc_Init_OnKnockbackExit,
    ftPc_Init_OnKnockbackExit,
    NULL,
    ftGn_Init_OnKnockbackExit,
    ftFe_Init_OnKnockbackExit,
    NULL,
    NULL,
    NULL,
    NULL,
    ftGk_Init_OnKnockbackExit,
    ftSb_Init_OnKnockbackExit,
};

HSD_GObjEvent ftData_UnkMotionStates3[FTKIND_MAX] = {
    NULL,
    NULL,
    NULL,
    NULL,
    ftKb_Init_UnkMotionStates3,
    ftKp_Init_UnkMotionStates3,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    ftGk_Init_UnkMotionStates3,
    NULL,
};

HSD_GObjEvent ftData_UnkMotionStates4[FTKIND_MAX] = {
    NULL,
    NULL,
    NULL,
    ftDk_Init_UnkMotionStates4,
    ftKb_Init_UnkMotionStates4,
    NULL,
    NULL,
    ftSk_Init_UnkMotionStates4,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    ftSs_Init_UnkMotionStates4,
    NULL,
    NULL,
    ftMt_Init_UnkMotionStates4,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    ftGw_Init_UnkMotionStates4,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
};

HSD_GObjEvent ftKindCalcIndiviParamTable[FTKIND_MAX] = {
    ftMr_Init_LoadSpecialAttrs, ftFx_Init_LoadSpecialAttrs,
    ftCa_Init_LoadSpecialAttrs, ftDk_Init_LoadSpecialAttrs,
    ftKb_Init_LoadSpecialAttrs, ftKp_Init_LoadSpecialAttrs,
    ftLk_Init_LoadSpecialAttrs, ftSk_Init_LoadSpecialAttrs,
    ftNs_Init_LoadSpecialAttrs, ftPe_Init_LoadSpecialAttrs,
    ftPp_Init_LoadSpecialAttrs, ftNn_Init_LoadSpecialAttrs,
    ftPk_Init_LoadSpecialAttrs, ftSs_Init_LoadSpecialAttrs,
    ftYs_Init_LoadSpecialAttrs, ftPr_Init_LoadSpecialAttrs,
    ftMt_Init_LoadSpecialAttrs, ftLg_Init_LoadSpecialAttrs,
    ftMs_Init_LoadSpecialAttrs, ftZd_Init_LoadSpecialAttrs,
    ftCl_Init_LoadSpecialAttrs, ftDr_Init_LoadSpecialAttrs,
    ftFc_Init_LoadSpecialAttrs, ftPc_Init_LoadSpecialAttrs,
    ftGw_Init_LoadSpecialAttrs, ftGn_Init_LoadSpecialAttrs,
    ftFe_Init_LoadSpecialAttrs, ftMh_Init_LoadSpecialAttrs,
    ftCh_Init_LoadSpecialAttrs, ftBo_Init_LoadSpecialAttrs,
    ftGl_Init_LoadSpecialAttrs, ftGk_Init_LoadSpecialAttrs,
    ftSb_Init_LoadSpecialAttrs,
};

/// Standard Character .dat File Names
struct StringPair {
    char* a;
    char* b;
};

struct StringPair ftData_803C1F40[FTKIND_MAX] = {
    { ftMr_Init_DatFilename, ftMr_Init_DataName },
    { ftFx_Init_DatFilename, ftFx_Init_DataName },
    { ftCa_Init_DatFilename, ftCa_Init_DataName },
    { ftDk_Init_DatFilename, ftDk_Init_DataName },
    { ftKb_Init_DatFilename, ftKb_Init_DataName },
    { ftKp_Init_DatFilename, ftKp_Init_DataName },
    { ftLk_Init_DatFilename, ftLk_Init_DataName },
    { ftSk_Init_DatFilename, ftSk_Init_DataName },
    { ftNs_Init_DatFilename, ftNs_Init_DataName },
    { ftPe_Init_DatFilename, ftPe_Init_DataName },
    { ftPp_Init_DatFilename, ftPp_Init_DataName },
    { ftNn_Init_DatFilename, ftNn_Init_DataName },
    { ftPk_Init_DatFilename, ftPk_Init_DataName },
    { ftSs_Init_DatFilename, ftSs_Init_DataName },
    { ftYs_Init_DatFilename, ftYs_Init_DataName },
    { ftPr_Init_DatFilename, ftPr_Init_DataName },
    { ftMt_Init_DatFilename, ftMt_Init_DataName },
    { ftLg_Init_DatFilename, ftLg_Init_DataName },
    { ftMs_Init_DatFilename, ftMs_Init_DataName },
    { ftZd_Init_DatFilename, ftZd_Init_DataName },
    { ftCl_Init_DatFilename, ftCl_Init_DataName },
    { ftDr_Init_DatFilename, ftDr_Init_DataName },
    { ftFc_Init_DatFilename, ftFc_Init_DataName },
    { ftPc_Init_DatFilename, ftPc_Init_DataName },
    { ftGw_Init_DatFilename, ftGw_Init_DataName },
    { ftGn_Init_DatFilename, ftGn_Init_DataName },
    { ftFe_Init_DatFilename, ftFe_Init_DataName },
    { ftMh_Init_DatFilename, ftMh_Init_DataName },
    { ftCh_Init_DatFilename, ftCh_Init_DataName },
    { ftBo_Init_DatFilename, ftBo_Init_DataName },
    { ftGl_Init_DatFilename, ftGl_Init_DataName },
    { ftGk_Init_DatFilename, ftGk_Init_DataName },
    { ftSb_Init_DatFilename, ftSb_Init_DataName },
};

Event ftData_UnkMotionStates5[FTKIND_MAX] = {
    NULL, NULL, NULL, NULL, ftKb_Init_UnkMotionStates5,
    NULL, NULL, NULL, NULL, NULL,
    NULL, NULL, NULL, NULL, NULL,
    NULL, NULL, NULL, NULL, NULL,
    NULL, NULL, NULL, NULL, NULL,
    NULL, NULL, NULL, NULL, NULL,
    NULL, NULL, NULL,
};

Fighter_UnkMtxEvent ftData_UnkMtxFunc0[FTKIND_MAX] = {
    NULL,
    NULL,
    NULL,
    NULL,
    ftKb_UnkMtxFunc0,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    ftPr_Init_UnkMtxFunc0,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
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

/// Character model group (e.g. high poly, low poly, metal) visibility change
/// callbacks
ftData_UnkModelStruct ftData_UnkIntBoolFunc0 = {
    {
        NULL,
        NULL,
        NULL,
        NULL,
        ftKb_UnkIntBoolFunc0,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        ftPr_Init_UnkIntBoolFunc0,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
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
        NULL,
        NULL,
        NULL,
        NULL,
        ftKb_Init_UnkMotionStates6,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        ftPr_Init_UnkMotionStates6,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
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

struct {
    HSD_GObjEvent x0;
    void (*x4)(Fighter_GObj*, int, float frame);
} ftData_UnkCallbackPairs0[FTKIND_MAX] = {
    { NULL, NULL },
    { NULL, NULL },
    { NULL, NULL },
    { NULL, NULL },
    { ftKb_Init_UnkCallbackPairs0_0, ftKb_Init_UnkCallbackPairs0_1 },
};

/// Costume and Joint Strings
Fighter_CostumeStrings* ftData_803C2360[FTKIND_MAX] = {
    ftMr_Init_CostumeStrings, ftFx_Init_CostumeStrings,
    ftCa_Init_CostumeStrings, ftDk_Init_CostumeStrings,
    ftKb_Init_CostumeStrings, ftKp_Init_CostumeStrings,
    ftLk_Init_CostumeStrings, ftSk_Init_CostumeStrings,
    ftNs_Init_CostumeStrings, ftPe_Init_CostumeStrings,
    ftPp_Init_CostumeStrings, ftNn_Init_CostumeStrings,
    ftPk_Init_CostumeStrings, ftSs_Init_CostumeStrings,
    ftYs_Init_CostumeStrings, ftPr_Init_CostumeStrings,
    ftMt_Init_CostumeStrings, ftLg_Init_CostumeStrings,
    ftMs_Init_CostumeStrings, ftZd_Init_CostumeStrings,
    ftCl_Init_CostumeStrings, ftDr_Init_CostumeStrings,
    ftFc_Init_CostumeStrings, ftPc_Init_CostumeStrings,
    ftGw_Init_CostumeStrings, ftGn_Init_CostumeStrings,
    ftFe_Init_CostumeStrings, ftMh_Init_CostumeStrings,
    ftCh_Init_CostumeStrings, ftBo_Init_CostumeStrings,
    ftGl_Init_CostumeStrings, ftGk_Init_CostumeStrings,
    ftSb_Init_CostumeStrings,

};

char* ftData_803C23E4[FTKIND_MAX] = {
    ftMr_Init_AnimDatFilename, ftFx_Init_AnimDatFilename,
    ftCa_Init_AnimDatFilename, ftDk_Init_AnimDatFilename,
    ftKb_Init_AnimDatFilename, ftKp_Init_AnimDatFilename,
    ftLk_Init_AnimDatFilename, ftSk_Init_AnimDatFilename,
    ftNs_Init_AnimDatFilename, ftPe_Init_AnimDatFilename,
    ftPp_Init_AnimDatFilename, ftNn_Init_AnimDatFilename,
    ftPk_Init_AnimDatFilename, ftSs_Init_AnimDatFilename,
    ftYs_Init_AnimDatFilename, ftPr_Init_AnimDatFilename,
    ftMt_Init_AnimDatFilename, ftLg_Init_AnimDatFilename,
    ftMs_Init_AnimDatFilename, ftZd_Init_AnimDatFilename,
    ftCl_Init_AnimDatFilename, ftDr_Init_AnimDatFilename,
    ftFc_Init_AnimDatFilename, ftPc_Init_AnimDatFilename,
    ftGw_Init_AnimDatFilename, ftGn_Init_AnimDatFilename,
    ftFe_Init_AnimDatFilename, ftMh_Init_AnimDatFilename,
    ftCh_Init_AnimDatFilename, ftBo_Init_AnimDatFilename,
    ftGl_Init_AnimDatFilename, ftGk_Init_AnimDatFilename,
    ftSb_Init_AnimDatFilename,
};

/// Demo Lookup Strings
Fighter_DemoStrings* ftData_803C2468[FTKIND_MAX] = {
    &ftMr_Init_DemoMotionFilenames,
    &ftFx_Init_DemoMotionFilenames,
    &ftCa_Init_DemoMotionFilenames,
    &ftDk_Init_DemoMotionFilenames,
    &ftKb_Init_DemoMotionFilenames,
    &ftKp_Init_DemoMotionFilenames,
    &ftLk_Init_DemoMotionFilenames,
    &ftSk_Init_DemoMotionFilenames,
    &ftNs_Init_DemoMotionFilenames,
    &ftPe_Init_DemoMotionFilenames,
    &ftPp_Init_DemoMotionFilenames,
    &ftNn_Init_DemoMotionFilenames,
    &ftPk_Init_DemoMotionFilenames,
    &ftSs_Init_DemoMotionFilenames,
    &ftYs_Init_DemoMotionFilenames,
    &ftPr_Init_DemoMotionFilenames,
    &ftMt_Init_DemoMotionFilenames,
    &ftLg_Init_DemoMotionFilenames,
    &ftMs_Init_DemoMotionFilenames,
    &ftZd_Init_DemoMotionFilenames,
    &ftCl_Init_DemoMotionFilenames,
    &ftDr_Init_DemoMotionFilenames,
    &ftFc_Init_DemoMotionFilenames,
    &ftPc_Init_DemoMotionFilenames,
    &ftGw_Init_DemoMotionFilenames,
    &ftGn_Init_DemoMotionFilenames,
    &ftFe_Init_DemoMotionFilenames,
    NULL,
    NULL,
    NULL,
    NULL,
    &ftGk_Init_DemoMotionFilenames,
    NULL,
};

Fighter_MotionFileStringGetter ftData_803C24EC[FTKIND_MAX] = {
    ftMr_Init_GetMotionFileString,
    NULL,
    NULL,
    NULL,
    ftKb_Init_GetMotionFileString,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    ftLg_Init_GetMotionFileString,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    ftGk_Init_GetMotionFileString,
    NULL,
};

Fighter_UnkPtrEvent ftData_UnkDemoCallbacks0[FTKIND_MAX] = {
    ftMr_Init_UnkDemoCallbacks0,
    NULL,
    NULL,
    NULL,
    ftKb_Init_UnkDemoCallbacks0,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    ftLg_Init_UnkDemoCallbacks0,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    ftGk_Init_UnkDemoCallbacks0,
    NULL,
};

ftData_UnkCountStruct ftData_UnkIntPairs[FTKIND_MAX] = {
    { 0, 16 }, { 0, 14 }, { 0, 14 }, { 0, 14 }, { 0, 18 }, { 0, 14 },
    { 0, 14 }, { 0, 14 }, { 0, 14 }, { 0, 14 }, { 0, 14 }, { 0, 14 },
    { 0, 14 }, { 0, 14 }, { 0, 14 }, { 0, 14 }, { 0, 14 }, { 0, 16 },
    { 0, 14 }, { 0, 14 }, { 0, 14 }, { 0, 14 }, { 0, 14 }, { 0, 14 },
    { 0, 14 }, { 0, 14 }, { 0, 14 }, { 0, 14 }, { 0, 14 }, { 0, 14 },
    { 0, 14 }, { 0, 15 }, { 0, 14 },
};

u8 ftData_UnkBytePerCharacter[FTKIND_MAX] = {
    1,  3,  4,  8, 5, 12, 6, 17, 10, 15, 14, 14, 7,  2,  9,  11, 13,
    18, 16, 17, 6, 1, 3,  7, -1, 19, 49, -1, -1, -1, -1, 12, -1,
};

void ftData_80085560(int idx, int increment)
{
    ft_8045996C[idx] += increment;
    if (ft_8045996C[idx] < 0) {
        OSReport("fighter reference counter error!\n");
        HSD_ASSERT(1944, 0);
    }
}

char ftData_assert_msg_0[] = "cant get corps model array!\n";
char ftData_assert_msg_1[] = "HSD_ArchiveParse error!\n";

void ftData_800855C8(FighterKind kind, u8 color)
{
    int i;
    int lo;
    int hi;

    if (color != 0xFF &&
        color >= CostumeListsForeachCharacter[kind].numCostumes)
    {
        color = 0;
    }
    if (ftData_803C1F40[kind].a != NULL) {
        lbDvd_800178E8(2, ftData_803C1F40[kind].a, 4, 4, 0, 1, 4, 2, 0);
    }
    if (color == 0xFF) {
        lo = 0;
        hi = CostumeListsForeachCharacter[kind].numCostumes;
    } else {
        lo = color;
        hi = color + 1;
    }
    for (i = lo; i < hi; i++) {
        if (ftData_803C2360[kind][i].dat_filename != NULL) {
            lbDvd_800178E8(2, ftData_803C2360[kind][i].dat_filename, 4, 4, 0,
                           1, 3, 1, 0);
        }
    }
    if (ftData_UnkBytePerCharacter[kind] != (char) -1) {
        efAsync_LoadAsync(ftData_UnkBytePerCharacter[kind]);
    }
    if (ftData_803C23E4[kind] != NULL) {
        lbDvd_800178E8(1, ftData_803C23E4[kind], 5, 5, 0, 0, 1, 8, 0);
    }
}

void ftData_8008572C(FighterKind kind)
{
    if (gFtDataList[kind] == NULL) {
        lbArchive_80017040(NULL, ftData_803C1F40[kind].a, &gFtDataList[kind],
                           ftData_803C1F40[kind].b, 0);
    }
}

void ftData_8008578C(int arg0, u8 color)
{
    if (color != 0xFF &&
        color >= CostumeListsForeachCharacter[FTKIND_KIRBY].numCostumes)
    {
        color = 0;
    }
    ftKb_SpecialN_800EEC34(
        arg0, color, CostumeListsForeachCharacter[FTKIND_KIRBY].numCostumes);
}

void ftData_800857E0(FighterKind kind)
{
    if (ftData_UnkMotionStates5[kind] != NULL) {
        ftData_UnkMotionStates5[kind]();
    }
}

void ftData_80085820(FighterKind kind, int costume_id)
{
    UnkCostumeStruct* temp_r5 =
        &CostumeListsForeachCharacter[kind].costume_list[costume_id];
    if (temp_r5->joint == NULL) {
        if (ftData_803C2360[kind][costume_id].matanim_joint_name != NULL) {
            lbArchive_80017040(
                &temp_r5->x14_archive,
                ftData_803C2360[kind][costume_id].dat_filename, temp_r5,
                ftData_803C2360[kind][costume_id].joint_name, &temp_r5->x4,
                ftData_803C2360[kind][costume_id].matanim_joint_name, 0);
        } else {
            lbArchive_80017040(
                &temp_r5->x14_archive,
                ftData_803C2360[kind][costume_id].dat_filename, temp_r5,
                ftData_803C2360[kind][costume_id].joint_name, 0,
                ftData_803C2360[kind][costume_id].matanim_joint_name);
            CostumeListsForeachCharacter[kind].costume_list[costume_id].x4 =
                NULL;
        }
    }
}

void ftData_800858E4(FighterKind kind, int costume_id)
{
    UnkCostumeStruct* temp_r5 =
        &CostumeListsForeachCharacter[kind].costume_list[costume_id];
    if (temp_r5->joint == NULL) {
        if (ftData_803C2360[kind][costume_id].matanim_joint_name != NULL) {
            lbArchive_80017040(
                &temp_r5->x14_archive,
                ftData_803C2360[kind][costume_id].dat_filename, temp_r5,
                ftData_803C2360[kind][costume_id].joint_name, &temp_r5->x4,
                ftData_803C2360[kind][costume_id].matanim_joint_name, 0);
        } else {
            lbArchive_80017040(
                &temp_r5->x14_archive,
                ftData_803C2360[kind][costume_id].dat_filename, temp_r5,
                ftData_803C2360[kind][costume_id].joint_name, 0,
                ftData_803C2360[kind][costume_id].matanim_joint_name);
            CostumeListsForeachCharacter[kind].costume_list[costume_id].x4 =
                NULL;
        }
    }
}

void ftData_800859A8(Fighter* fp)
{
    HSD_GObj* gobj;
    s8 temp_r6 = fp->x61C;
    if (temp_r6 == -1) {
        return;
    }
    for (gobj = HSD_GObj_Entities->fighters; gobj != NULL; gobj = gobj->next) {
        Fighter* cur_fp = GET_FIGHTER(gobj);
        if (fp != cur_fp && temp_r6 == cur_fp->x61C) {
            return;
        }
    }
    ft_8045993C[temp_r6].x6_b0 = false;
}

void ftData_80085A14(FighterKind kind)
{
    void* sp18;
    void* a_head;
    ftData* temp_r27 = gFtDataList[kind];
    u32 temp_r0;
    int i;
    u8 _[4];
    size_t sp10;

    PAD_STACK(4);

    if (ftData_Table_Unk0[kind].data == NULL) {
        lbFile_800168A0(1, ftData_803C23E4[kind], &sp18, &sp10);
        a_head = sp18;
        HSD_ASSERT(0x974, a_head);
        for (i = 0; i < (u32) ftData_Table_Unk0[kind].count; i++) {
            temp_r0 = temp_r27->xC[i].x8;
            if (temp_r0 != 0) {
                if (temp_r0 > 0x8000) {
                    HSD_ASSERTREPORT(0x9AF, 0, "fighter figatree over! %x\n",
                                     temp_r0);
                }
                temp_r27->xC[i].x14 =
                    (uintptr_t) ((u8*) a_head + temp_r27->xC[i].x4);
            }
        }
        ftData_Table_Unk0[kind].data = a_head;
    }
}

void ftData_80085B10(Fighter* fp)
{
    FighterKind kind = fp->kind;
    fp->x59C = HSD_ObjAlloc(&fighter_x59C_alloc_data);
    fp->x5A0 = HSD_ObjAlloc(&fighter_x59C_alloc_data);
    fp->x5A4 = NULL;
    fp->x5A8 = NULL;
    fp->x58C = ftData_Table_Unk0[kind].count;
    ftData_80085A14(kind);
}

void ftData_80085B98(Fighter* fp, int arg1, int arg2)
{
    u32 temp_r30;
    int i;
    u32 temp_r0;
    struct Fighter_WaitAnimData* temp_r3;

    temp_r30 = (u32) ftData_UnkIntPairs[fp->kind].data;
    fp->x59C = HSD_ObjAlloc(&fighter_x59C_alloc_data);
    fp->x5A0 = HSD_ObjAlloc(&fighter_x59C_alloc_data);
    fp->x5A4 = 0;
    fp->x5A8 = 0;
    fp->x58C = ftData_UnkIntPairs[fp->kind].count;
    if (arg2 >= fp->x58C) {
        HSD_ASSERTREPORT(0x9D2, 0, "Demo Status error! %d\n", arg2);
    }
    if (temp_r30 != 0U) {
        for (i = arg1; i <= arg2; i++) {
            temp_r3 = &fp->ft_data->x14[i];
            temp_r0 = temp_r3->x8;
            if (temp_r3->x8 != 0U) {
                if (temp_r0 > 0xB000) {
                    HSD_ASSERTREPORT(0x9DC, 0, "fighter figatree over! %x\n",
                                     temp_r0);
                }
                temp_r3 = &fp->ft_data->x14[i];
                temp_r3->x14 = temp_r30 + temp_r3->x4;
            }
        }
        ftData_UnkIntPairs[fp->kind].data = 0;
    }
}

void ftData_80085CD8(Fighter* fp, Fighter* arg1, int msid)
{
    HSD_Archive sp14;
    Fighter* temp_r3_3;
    s32 temp_ret;
    s32 temp_ret_2;
    struct Fighter_x59C_t* temp_r4;
    struct Fighter_WaitAnimData* temp_r3;
    u32 temp_r3_2;
    u32 temp_r4_2;

    if (msid < arg1->x58C) {
        temp_r3 = (struct Fighter_WaitAnimData*) ftData_80085FD4(arg1, msid);
        temp_r3_2 = temp_r3->x14;
        if (temp_r3_2 != (u32) fp->x5A4) {
            if (temp_r3_2 != 0) {
                temp_r3_3 = ftData_80086060(fp);
                if ((temp_r3_3 != NULL) &&
                    (temp_r3->x14 == (u32) temp_r3_3->x5A4))
                {
                    memcpy(fp->x59C, temp_r3_3->x59C, temp_r3->x8);
                    temp_r4 = fp->x59C;
                    temp_ret = lbArchiveRelocate(
                        &sp14, temp_r4->x0, temp_r3->x8,
                        (intptr_t) temp_r4 - (intptr_t) temp_r3_3->x59C);
                    if (temp_ret == -1) {
                        HSD_ASSERTREPORT(
                            0x9FA, 0, "lbArchiveRelocate error! %x\n", msid);
                    }
                } else {
                    temp_r4_2 = temp_r3->x14;
                    if (temp_r4_2 < 0x80000000) {
                        lbArq_80014BD0(temp_r4_2, fp->x59C,
                                       OSRoundUp32B(temp_r3->x8), 0, 0);
                    } else {
                        memcpy(fp->x59C, (void*) temp_r4_2, temp_r3->x8);
                    }
                    temp_ret_2 =
                        HSD_ArchiveParse(&sp14, fp->x59C->x0, temp_r3->x8);
                    if (temp_ret_2 == -1) {
                        HSD_ASSERTREPORT(0xA0F, 0,
                                         "HSD_ArchiveParse error! %x\n", msid);
                    }
                }
                fp->x590 = HSD_ArchiveGetPublicAddress(&sp14, temp_r3->x0);
            } else {
                fp->x590 = NULL;
            }
            fp->x5A4 = (void*) temp_r3->x14;
        }
    }
}

FigaTree* ftData_80085E50(Fighter* arg0, int msid)
{
    HSD_Archive sp10;
    Fighter* temp_r3_3;
    int temp_ret;
    int temp_ret_2;
    struct Fighter_x59C_t* temp_r4;
    struct ftData_80085FD4_ret* temp_r3;
    u32 temp_r3_2;
    u32 temp_r4_2;

    if (msid < arg0->x58C) {
        temp_r3 = ftData_80085FD4(arg0, msid);
        temp_r3_2 = temp_r3->x14;
        if (temp_r3_2 != (u32) arg0->x5A8) {
            if (temp_r3_2 != 0) {
                temp_r3_3 = ftData_80086060(arg0);
                if ((temp_r3_3 != NULL) &&
                    (temp_r3->x14 == (u32) temp_r3_3->x5A4))
                {
                    memcpy(arg0->x59C, temp_r3_3->x59C, temp_r3->x8);
                    temp_r4 = arg0->x59C;
                    temp_ret = lbArchiveRelocate(
                        &sp10, temp_r4->x0, temp_r3->x8,
                        (intptr_t) temp_r4 - (intptr_t) temp_r3_3->x59C);
                    if (temp_ret == -1) {
                        HSD_ASSERTREPORT(
                            0xA30, 0, "lbArchiveRelocate error! %x\n", msid);
                    }
                } else {
                    temp_r4_2 = temp_r3->x14;
                    if (temp_r4_2 < 0x80000000) {
                        lbArq_80014BD0(temp_r4_2, arg0->x5A0,
                                       OSRoundUp32B(temp_r3->x8), 0, 0);
                    } else {
                        memcpy(arg0->x5A0, (void*) temp_r4_2, temp_r3->x8);
                    }
                    temp_ret_2 =
                        HSD_ArchiveParse(&sp10, arg0->x5A0->x0, temp_r3->x8);
                    if (temp_ret_2 == -1) {
                        HSD_ASSERTREPORT(0xA45, 0,
                                         "HSD_ArchiveParse error! %x\n", msid);
                    }
                }
                arg0->x598 = HSD_ArchiveGetPublicAddress(&sp10, temp_r3->x0);
            } else {
                arg0->x598 = 0;
            }
            arg0->x5A8 = (void*) temp_r3->x14;
        }
        return arg0->x598;
    }
    return NULL;
}

struct ftData_80085FD4_ret* ftData_80085FD4(Fighter* fp, int msid)
{
    if (fp->kind == FTKIND_NANA &&
        Player_GetPlayerSlotType(fp->player_id) != Gm_PKind_Demo &&
        fp->x24[msid].x14 == 0)
    {
        return (struct ftData_80085FD4_ret*) &gFtDataList[FTKIND_POPO]
            ->xC[msid];
    }
    return (struct ftData_80085FD4_ret*) &fp->x24[msid];
}

Fighter* ftData_80086060(Fighter* fp)
{
    if (fp->kind == FTKIND_NANA &&
        Player_GetPlayerSlotType(fp->player_id) != Gm_PKind_Demo)
    {
        Fighter_GObj* gobj = Player_GetEntityAtIndex(fp->player_id, 0);
        if (gobj != NULL) {
            return GET_FIGHTER(gobj);
        }
    }
    return NULL;
}
