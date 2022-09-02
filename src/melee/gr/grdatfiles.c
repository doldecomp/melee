#include <melee/gr/grdatfiles.h>

#include <sysdolphin/baselib/archive.h>
#include <sysdolphin/baselib/debug.h>

extern StageInfo stage_info;

typedef struct _UnkStageDatInternal {
    u8 x0_fill[0x4];
    u32 unk4; // flags
} UnkStageDatInternal;

extern UnkStage6B0 lbl_803E0848;

static UnkArchiveStruct lbl_8049EE10[4];
extern UnkStageDat lbl_803E0924;

void func_801C5FC0(HSD_Archive* archive, void* data, u32 length)
{
    HSD_Archive* map_ptcl;
    HSD_Archive* map_texg;
    lbArchive_InitializeDAT(archive, data, length);
    map_ptcl = HSD_ArchiveGetPublicAddress(archive, "map_ptcl");
    map_texg = HSD_ArchiveGetPublicAddress(archive, "map_texg");
    if (map_ptcl != NULL && map_texg != NULL) {
        func_80398614(map_ptcl, map_texg, 0);
    }
}

void func_801C6038(void* arg0, s32 arg1, s32 arg2)
{
    UnkArchiveStruct* temp_r3 = func_801C62B4();
    if (arg0 != NULL) {
        HSD_Archive* sp14;
        s32 phi_r28;
        void* r4 = arg0;
        if (arg2 != 0) {
            phi_r28 = func_800171CC(&sp14, r4, &temp_r3->unk4, "map_head", 0);
        } else {
            sp14 = func_80016DBC(r4, &temp_r3->unk4, "map_head", 0);
            phi_r28 = 0;
        }
        temp_r3->unk8 = 0;
        if (arg1 == 0) {
            stage_info.x6AC = HSD_ArchiveGetPublicAddress(sp14, "coll_data");
            stage_info.x6B0 = HSD_ArchiveGetPublicAddress(sp14, "grGroundParam");
            stage_info.x6A8 = HSD_ArchiveGetPublicAddress(sp14, "itemdata");
            stage_info.x6B4 = HSD_ArchiveGetPublicAddress(sp14, "ALDYakuAll");
            stage_info.x6B8 = HSD_ArchiveGetPublicAddress(sp14, "map_ptcl");
            stage_info.x6BC = HSD_ArchiveGetPublicAddress(sp14, "map_texg");
            stage_info.x6C0 = HSD_ArchiveGetPublicAddress(sp14, "yakumono_param");
            stage_info.x6C4 = HSD_ArchiveGetPublicAddress(sp14, "map_plit");
            stage_info.x6CC = HSD_ArchiveGetPublicAddress(sp14, "quake_model_set");
        }
        temp_r3->unk0 = sp14;
        if (stage_info.x6B8 != NULL && stage_info.x6BC != NULL) {
            if (phi_r28 != 0) {
                func_803984F4(0x40, stage_info.x6B8, stage_info.x6BC, 0, 0);
            } else {
                func_803989A0(0x40, stage_info.x6B8, stage_info.x6BC, 0, 0);
            }
        }
        func_801C6228(temp_r3->unk4);
    } else {
        temp_r3->unk4 = &lbl_803E0924;
        if (arg1 == 0) {
            stage_info.x6AC = NULL;
            stage_info.x6B0 = &lbl_803E0848;
            stage_info.x6A8 = NULL;
            stage_info.x6B4 = NULL;
            stage_info.x6B8 = NULL;
            stage_info.x6BC = NULL;
            stage_info.x6C0 = NULL;
            stage_info.x6C4 = NULL;
            stage_info.x6C8 = NULL;
        }
        temp_r3->unk0 = (void*) -1;
    }
}

static void func_801C6228(UnkStageDat* arg0)
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

void func_801C6288(void)
{
    func_8000C160(&lbl_8049EE10, 0x30);
}

static UnkArchiveStruct* func_801C62B4(void)
{
    s32 i;
    for (i = 0; i < 4; i++) {
        if (lbl_8049EE10[i].unk0 == NULL) {
            return &lbl_8049EE10[i];
        }
    }
    assert_line(229, 0);
}

UnkArchiveStruct* func_801C6324(void)
{
    return lbl_8049EE10;
}

UnkArchiveStruct* func_801C6330(s32 arg0)
{
    if (arg0 >= 0) {
        s32 i;
        for (i = 0; i < 4; i++) {
            if (lbl_8049EE10[i].unk0 != NULL) {
                UnkStageDat* temp_r7 = lbl_8049EE10[i].unk4;
                if (temp_r7 != NULL && temp_r7->unkC > arg0 &&
                    temp_r7->unk8[arg0].unk0 != 0) {
                    return &lbl_8049EE10[i];
                }
            }
        }
    }
    return NULL;
}

UnkArchiveStruct* func_801C6478(void* data, s32 length)
{
    UnkArchiveStruct* arc;

    HSD_Archive* archive = func_80015BD0(0, 0x44);
    lbArchive_InitializeDAT(archive, data, length);
    arc = func_801C62B4();
    assert_line(290, arc);
    arc->unk0 = archive;
    arc->unk4 = HSD_ArchiveGetPublicAddress(archive, "map_head");
    arc->unk8 = 1;

    func_801C6228(arc->unk4);

    return arc;
}

static UnkBgmStruct lbl_803E07E4 = { 0, -1, -1 };

static UnkStage6B0 lbl_803E0848 = {
    1, 0x80, {}, 0x1E, 0, 1, 0x8000, 10,
    0, 0, 1, 1, 1,
    {},
    40, 10, 50, 100,
    10, 10, 10, 10,
    FALSE,
    0, 0, 0, 30, 10, 0,
    0,
    {},
    &lbl_803E07E4,
    1,
};

UnkStageDat lbl_803E0924 = { 0 };
