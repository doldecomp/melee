#include "gr/grdatfiles.h"

#include "gr/types.h"
#include "lb/lb_00B0.h"
#include "lb/lbarchive.h"
#include "lb/lbheap.h"

#include <baselib/archive.h>
#include <baselib/debug.h>
#include <baselib/particle.h>
#include <baselib/psstructs.h>

extern StageInfo stage_info;

/// @todo Bad split?
/* static */ extern UnkStage6B0 grDatFiles_803E0848;

static UnkArchiveStruct grDatFiles_8049EE10[4];

/// @todo Bad split?
/* static */ extern UnkStageDat grDatFiles_803E0924;

void grDatFiles_801C5FC0(HSD_Archive* archive, void* data, u32 length)
{
    HSD_Archive* map_ptcl;
    HSD_Archive* map_texg;
    lbArchive_InitializeDAT(archive, data, length);
    map_ptcl = HSD_ArchiveGetPublicAddress(archive, "map_ptcl");
    map_texg = HSD_ArchiveGetPublicAddress(archive, "map_texg");

    if (map_ptcl != NULL && map_texg != NULL) {
        psInitDataBankLocate(map_ptcl, map_texg, NULL);
    }
}

void grDatFiles_801C6038(void* arg0, s32 arg1, s32 arg2)
{
    UnkArchiveStruct* temp_r3 = grDatFiles_801C62B4();
    if (arg0 != NULL) {
        HSD_Archive* sp14;
        s32 phi_r28;
        void* r4 = arg0;
        if (arg2 != 0) {
            phi_r28 =
                lbArchive_800171CC(&sp14, r4, &temp_r3->unk4, "map_head", 0);
        } else {
            sp14 =
                lbArchive_80016DBC(r4, (void**) &temp_r3->unk4, "map_head", 0);
            phi_r28 = 0;
        }
        temp_r3->unk8 = 0;
        if (arg1 == 0) {
            stage_info.coll_data =
                HSD_ArchiveGetPublicAddress(sp14, "coll_data");
            stage_info.param =
                HSD_ArchiveGetPublicAddress(sp14, "grGroundParam");
            stage_info.itemdata =
                HSD_ArchiveGetPublicAddress(sp14, "itemdata");
            stage_info.ald_yaku_all =
                HSD_ArchiveGetPublicAddress(sp14, "ALDYakuAll");
            stage_info.map_ptcl =
                HSD_ArchiveGetPublicAddress(sp14, "map_ptcl");
            stage_info.map_texg =
                HSD_ArchiveGetPublicAddress(sp14, "map_texg");
            stage_info.yakumono_param =
                HSD_ArchiveGetPublicAddress(sp14, "yakumono_param");
            stage_info.map_plit =
                HSD_ArchiveGetPublicAddress(sp14, "map_plit");
            stage_info.quake_model_set =
                HSD_ArchiveGetPublicAddress(sp14, "quake_model_set");
        }
        temp_r3->unk0 = sp14;
        if (stage_info.map_ptcl != NULL && stage_info.map_texg != NULL) {
            if (phi_r28 != 0) {
                psInitDataBankLoad(0x40, stage_info.map_ptcl,
                                   stage_info.map_texg, 0, 0);
            } else {
                psInitDataBank(0x40, stage_info.map_ptcl, stage_info.map_texg,
                               0, 0);
            }
        }
        grDatFiles_801C6228(temp_r3->unk4);
    } else {
        temp_r3->unk4 = &grDatFiles_803E0924;
        if (arg1 == 0) {
            stage_info.coll_data = NULL;
            stage_info.param = &grDatFiles_803E0848;
            stage_info.itemdata = NULL;
            stage_info.ald_yaku_all = NULL;
            stage_info.map_ptcl = NULL;
            stage_info.map_texg = NULL;
            stage_info.yakumono_param = NULL;
            stage_info.map_plit = NULL;
            stage_info.x6C8 = NULL;
        }
        temp_r3->unk0 = (void*) -1;
    }
}

static void grDatFiles_801C6228(UnkStageDat* arg0)
{
    if (arg0 != NULL && arg0->unk28 != NULL && arg0->unk2C != 0) {
        s32 i;
        for (i = 0; i < arg0->unk2C; i++) {
            UnkStageDatInternal* temp_r4 = arg0->unk28[i];
            if (temp_r4 != NULL) {
                temp_r4->unk4 |= 0x4000000;
            }
        }
    }
}

void grDatFiles_801C6288(void)
{
    lb_8000C160(&grDatFiles_8049EE10, 0x30);
}

static UnkArchiveStruct* grDatFiles_801C62B4(void)
{
    s32 i;
    for (i = 0; i < 4; i++) {
        if (grDatFiles_8049EE10[i].unk0 == NULL) {
            return &grDatFiles_8049EE10[i];
        }
    }
    HSD_ASSERT(229, 0);

#ifdef BUGFIX
    // Asserts 0 but the compiler doesn't know that.
    return NULL;
#endif
}

UnkArchiveStruct* grDatFiles_801C6324(void)
{
    return grDatFiles_8049EE10;
}

UnkArchiveStruct* grDatFiles_801C6330(s32 arg0)
{
    if (arg0 >= 0) {
        s32 i;
        for (i = 0; i < 4; i++) {
            if (grDatFiles_8049EE10[i].unk0 != NULL) {
                UnkStageDat* temp_r7 = grDatFiles_8049EE10[i].unk4;
                if (temp_r7 != NULL && temp_r7->unkC > arg0 &&
                    temp_r7->unk8[arg0].unk0 != 0)
                {
                    return &grDatFiles_8049EE10[i];
                }
            }
        }
    }
    return NULL;
}

UnkArchiveStruct* grDatFiles_801C6478(void* data, s32 length)
{
    UnkArchiveStruct* arc;

    HSD_Archive* archive = lbHeap_80015BD0(0, 0x44);
    lbArchive_InitializeDAT(archive, data, length);
    arc = grDatFiles_801C62B4();
    HSD_ASSERT(290, arc);
    arc->unk0 = archive;
    arc->unk4 = HSD_ArchiveGetPublicAddress(archive, "map_head");
    arc->unk8 = 1;

    grDatFiles_801C6228(arc->unk4);

    return arc;
}

static UnkBgmStruct grDatFiles_803E07E4 = {
    0, -1, -1, 0, 0, 0, 0, 0, { 0 },
};

UnkStage6B0 grDatFiles_803E0848 = {
    1,  0x80, { 0 }, 0x1E, 0,  1,     0x8000, 10,
    0,  0,    1,     1,    1,  { 0 }, 40,     10,
    50, 100,  10,    10,   10, 10,    false,  0,
    0,  0,    30,    10,   0,  0,     { 0 },  &grDatFiles_803E07E4,
    1,
};

UnkStageDat grDatFiles_803E0924 = { 0 };
