#include <melee/gr/ground.h>

#include <MSL/trigf.h>
#include <dolphin/mtx/vec.h>
#include <dolphin/os/os.h>
#include <melee/cm/camera.h>
#include <melee/ft/ftlib.h>
#include <melee/gr/grdatfiles.h>
#include <melee/lb/lbarchive.h>
#include <melee/lb/lbshadow.h>
#include <melee/lb/lbunknown_003.h>
#include <melee/lb/lbvector.h>
#include <melee/pl/player.h>
#include <sysdolphin/baselib/gobjgxlink.h>
#include <sysdolphin/baselib/gobjobject.h>
#include <sysdolphin/baselib/gobjuserdata.h>
#include <sysdolphin/baselib/jobj.h>
#include <sysdolphin/baselib/memory.h>
#include <sysdolphin/baselib/random.h>
#include <sysdolphin/baselib/wobj.h>

StageInfo stage_info;

static StageData lbl_803DFEA8 = {
    0,
    NULL,
    NULL,
    func_801BFFA8,
    func_801BFFAC,
    func_801BFFA8,
    func_801BFFA8,
};

extern StageData
    lbl_803DFEA8, lbl_803E5764, lbl_803E11A4, lbl_803E4ECC, lbl_803E1800,
    lbl_803E52E0, lbl_803E3F6C, lbl_803E5130, lbl_803E1B2C, lbl_803E4D0C,
    lbl_803E274C, lbl_803E51CC, lbl_803E0E5C, lbl_803E76D0, lbl_803E1F08,
    lbl_803E54CC, lbl_803E1334, lbl_803E6A3C, lbl_803E33DC, lbl_803E2D20,
    lbl_803E2858, lbl_803E3D94, lbl_803E4800, lbl_803E4950, lbl_803E4C00,
    lbl_803E7A00, lbl_803E6748, lbl_803E650C, lbl_803E65E8, lbl_803E584C,
    lbl_803E5988, lbl_803E5E0C, lbl_803E617C, lbl_803E5764, lbl_803E7E38,
    lbl_803E7F90, lbl_803E7D34, lbl_803E7B10, lbl_803E85A4, lbl_803E8664,
    lbl_803E872C, lbl_803E87EC, lbl_803E88AC, lbl_803E8974, lbl_803E8A34,
    lbl_803E8AF4, lbl_803E8C0C, lbl_803E8CCC, lbl_803E8D8C, lbl_803E8E4C,
    lbl_803E8F0C, lbl_803E8FCC, lbl_803E908C, lbl_803E914C, lbl_803E920C,
    lbl_803E92CC, lbl_803E9394, lbl_803E9454, lbl_803E9514, lbl_803E95D4,
    lbl_803E9694, lbl_803E9754, lbl_803E981C, lbl_803E98DC, lbl_803E84C4,
    lbl_803E821C, lbl_803E62C0, lbl_803E6370, lbl_803E6420, lbl_803E5764;

static StageData* lbl_803DFEDC[] = {
    &lbl_803DFEA8, &lbl_803E5764, &lbl_803E11A4,
    &lbl_803E4ECC, &lbl_803E1800, &lbl_803E52E0,
    &lbl_803E3F6C, &lbl_803E5130, &lbl_803E1B2C,
    &lbl_803E4D0C, &lbl_803E274C, &lbl_803E51CC,
    &lbl_803E0E5C, &lbl_803E76D0, &lbl_803E1F08,
    &lbl_803E54CC, &lbl_803E1334, &lbl_803E6A3C,
    &lbl_803E33DC, &lbl_803E2D20, &lbl_803E2858,
    &lbl_803E3D94, &lbl_803E4800, NULL,
    &lbl_803E4950, &lbl_803E4C00, NULL,
    &lbl_803E7A00, &lbl_803E6748, &lbl_803E650C,
    &lbl_803E65E8, &lbl_803E584C, &lbl_803E5988,
    &lbl_803E5E0C, &lbl_803E617C, &lbl_803E5764,
    &lbl_803E7E38, &lbl_803E7F90, &lbl_803E7D34,
    &lbl_803E7B10, &lbl_803E85A4, &lbl_803E8664,
    &lbl_803E872C, &lbl_803E87EC, &lbl_803E88AC,
    &lbl_803E8974, &lbl_803E8A34, &lbl_803E8AF4,
    &lbl_803E8C0C, &lbl_803E8CCC, &lbl_803E8D8C,
    &lbl_803E8E4C, &lbl_803E8F0C, &lbl_803E8FCC,
    &lbl_803E908C, &lbl_803E914C, &lbl_803E920C,
    &lbl_803E92CC, &lbl_803E9394, &lbl_803E9454,
    &lbl_803E9514, &lbl_803E95D4, &lbl_803E9694,
    &lbl_803E9754, &lbl_803E981C, &lbl_803E98DC,
    &lbl_803E84C4, &lbl_803E821C, &lbl_803E62C0,
    &lbl_803E6370, &lbl_803E6420, &lbl_803E5764,
    &lbl_803E5764, &lbl_803E5764, &lbl_803E5764,
    &lbl_803E5764, &lbl_803E5764, &lbl_803E5764,
    &lbl_803E5764, &lbl_803E5764, &lbl_803E5764,
    &lbl_803E5764, &lbl_803E5764, &lbl_803E5764,
    &lbl_803E5764, &lbl_803E5764, &lbl_803E5764,
    &lbl_803E5764, &lbl_803E5764, &lbl_803E5764,
    &lbl_803E5764, &lbl_803E5764, &lbl_803E5764,
    &lbl_803E5764, &lbl_803E5764, &lbl_803E5764,
    &lbl_803E5764, &lbl_803E5764, &lbl_803E5764,
    &lbl_803E5764, &lbl_803E5764, &lbl_803E5764,
    &lbl_803E5764, &lbl_803E5764, &lbl_803E5764,
    &lbl_803E5764, &lbl_803E5764, &lbl_803E5764,
    &lbl_803E5764, &lbl_803E5764, &lbl_803E5764,
};

static u8* lbl_804D6950;

static void func_801BFFA8(void)
{
}

static void func_801BFFAC(s32)
{
}

void func_801BFFB0(void)
{
    int i;
    u32 unused[2];

    func_801C6288();
    stage_info.x84 = 0;
    stage_info.x6D0 = -1;
    stage_info.x6D2 = 0;
    stage_info.x6D4 = 0;
    stage_info.x6D8 = 0;
    stage_info.x6DC = 0;
    stage_info.x724 = -10000;
    stage_info.x12C = NULL;
    stage_info.unk8C.b3 = 0;
    stage_info.unk8C.b2 = 1;
    stage_info.x178 = 0;
    stage_info.x17C = NULL;
    stage_info.unk8C.b4 = 0;
    stage_info.unk8C.b5 = 0;
    stage_info.unk8C.b6 = 0;
    stage_info.x714 = -1;
    stage_info.x90 = 0;
    stage_info.unk8C.b7 = 0;
    stage_info.x720 = -1;
    stage_info.x94 = 0;
    for (i = 0; i < 64; i++) {
        stage_info.x180[i] = NULL;
    }
    for (i = 0; i < 261; i++) {
        stage_info.x280[i] = NULL;
    }
    stage_info.x694[0] = NULL;
    stage_info.x694[1] = NULL;
    stage_info.x694[2] = NULL;
    stage_info.x694[3] = NULL;
    stage_info.x6A4 = NULL;
    stage_info.cam_info.cam_bounds_left = -170;
    stage_info.cam_info.cam_bounds_right = 170;
    stage_info.cam_info.cam_bounds_top = 120;
    stage_info.cam_info.cam_bounds_bottom = -60;
    stage_info.cam_info.cam_x_offset = 0;
    stage_info.cam_info.cam_y_offset = 0;
    stage_info.cam_info.cam_vertical_tilt = 30;
    stage_info.cam_info.cam_pan_degrees = -10;
    stage_info.cam_info.x20 = 0.2;
    stage_info.cam_info.x24 = 0.2;
    stage_info.cam_info.cam_zoom_rate = 82;
    stage_info.cam_info.cam_max_depth = 1000;
    stage_info.blast_zone.left = -99999;
    stage_info.blast_zone.right = 99999;
    stage_info.blast_zone.top = 99999;
    stage_info.blast_zone.bottom = -99999;
    stage_info.internal_stage_id = -1;
    stage_info.x6D2 = 0;
    stage_info.x6D4 = 0;
    stage_info.x98 = -1;
    stage_info.x9C = 0;
    stage_info.x72C = 0;
    stage_info.x6E0 = 0;
    stage_info.x708 = 0;
    stage_info.x740 = 0;
}

void func_801C0378(void)
{
    int i;
    func_800C06C0();
    lbl_804D6950 = HSD_MemAlloc(0x40U);
    for (i = 0; i < 0x40; i++) {
        lbl_804D6950[i] = 0;
    }
}

void func_801C0478(void* ptr)
{
    HSD_Free(ptr);
}

f32 func_801C0498(void)
{
    UnkStage6B0* temp_r3 = stage_info.x6B0;
    if (temp_r3 != NULL) {
        return temp_r3->x0;
    } else {
        return 1;
    }
}

static char get_userdata_ground[] = "%s:%d: couldn t get user data(Ground)\n";

void func_801C04BC(f32 arg8)
{
    UnkStage6B0* temp_r3 = stage_info.x6B0;
    if (temp_r3 != NULL) {
        temp_r3->x0 = arg8;
    } else {
        assert_line(521, 0);
    }
}

s32 func_801C0508(void)
{
    UnkStage6B0* temp_r3 = stage_info.x6B0;
    return temp_r3 != NULL ? temp_r3->x4 : 128;
}

void func_801C052C(s32* arg0)
{
    UnkStage6B0* x = stage_info.x6B0;
    x->xB8 = *arg0;
}

void func_801C0544(s32* arg0)
{
    UnkStage6B0* x = stage_info.x6B0;
    x->xC0 = *arg0;
}

void func_801C055C(s32* arg0)
{
    UnkStage6B0* x = stage_info.x6B0;
    x->xD0 = *arg0;
}

void func_801C0574(s32* arg0)
{
    UnkStage6B0* x = stage_info.x6B0;
    x->xD8 = *arg0;
}

void func_801C058C(s32* arg0)
{
    UnkStage6B0* x = stage_info.x6B0;
    x->xC4 = *arg0;
}

void func_801C05A4(s32* arg0)
{
    UnkStage6B0* x = stage_info.x6B0;
    x->xCC = *arg0;
}

void func_801C05BC(s32* arg0)
{
    UnkStage6B0* x = stage_info.x6B0;
    x->xD4 = *arg0;
}

void func_801C05D4(s32* arg0)
{
    UnkStage6B0* x = stage_info.x6B0;
    x->xBC = *arg0;
}

void func_801C05EC(s32* arg0)
{
    UnkStage6B0* x = stage_info.x6B0;
    x->xC8 = *arg0;
}

s32* func_801C0604(void)
{
    UnkStage6B0* x = stage_info.x6B0;
    return &x->xB8;
}

s32* func_801C0618(void)
{
    UnkStage6B0* x = stage_info.x6B0;
    return &x->xC0;
}

s32* func_801C062C(void)
{
    UnkStage6B0* x = stage_info.x6B0;
    return &x->xD0;
}

s32* func_801C0640(void)
{
    UnkStage6B0* x = stage_info.x6B0;
    return &x->xD8;
}

s32* func_801C0654(void)
{
    UnkStage6B0* x = stage_info.x6B0;
    return &x->xC4;
}

s32* func_801C0668(void)
{
    UnkStage6B0* x = stage_info.x6B0;
    return &x->xCC;
}

s32* func_801C067C(void)
{
    UnkStage6B0* x = stage_info.x6B0;
    return &x->xD4;
}

s32* func_801C0690(void)
{
    UnkStage6B0* x = stage_info.x6B0;
    return &x->xBC;
}

s32* func_801C06A4(void)
{
    UnkStage6B0* x = stage_info.x6B0;
    return &x->xC8;
}

void func_801C06B8(s32 arg0)
{
    if (lbl_803DFEDC[arg0] == NULL) {
        return;
    }
    if (lbl_803DFEDC[arg0]->data1 != NULL) {
        func_800178E8(4, lbl_803DFEDC[arg0]->data1, 4, 4, 0, 1, 7, 16, 0);
    }
    switch (arg0) {
    case 12:
        func_801CD2D4();
        break;
    case 16:
        func_801D511C();
        break;
    }
}

void func_801C0754(StructPairWithStageID* pair)
{
    StageData* stage;
    s32 arg3;

    func_801BFFB0();
    stage_info.internal_stage_id = pair->stage_id;
    stage = lbl_803DFEDC[pair->stage_id];
    arg3 = (pair->list_idx == 0x55) ? 0 : 1;
    func_801C6038(stage->data1, 0, arg3);
    func_801C28CC(stage_info.xA0, pair->list_idx);
    stage_info.x178 = stage->callback5;
    stage_info.x17C = stage->callback6;
    func_801C5878();
}

extern struct {
    u8 x0_pad[0x1D4];
    struct {
        u8 x0_pad[0xC];
        struct {
            u8 x0_pad[0xC];
            s32 xC;
        }* xC;
    }* x1D4;
}* lbl_804D6D38;

void func_801C0800(StructPairWithStageID* pair)
{
    StageData* stage_data;
    struct {
        s32 unk0;
        s32 unk4;
    }* temp_r4_3;
    s32 i;

    stage_data = lbl_803DFEDC[pair->stage_id];
    func_801C38D0(stage_info.x6B0->x8, stage_info.x6B0->x14, stage_info.x6B0->x1C, stage_info.x6B0->x18);
    func_801C38EC(stage_info.x6B0->x10, stage_info.x6B0->xC);
    func_801C3970(stage_info.x6B0->x28);
    func_801C3900(stage_info.x6B0->x2E, stage_info.x6B0->x30, stage_info.x6B0->x34, stage_info.x6B0->x38,
                  stage_info.x6B0->x3C, stage_info.x6B0->x40, stage_info.x6B0->x44, stage_info.x6B0->x48);
    func_801C392C(stage_info.x6B0->x50, stage_info.x6B0->x54, stage_info.x6B0->x58,
                  stage_info.x6B0->x5C, stage_info.x6B0->x60, stage_info.x6B0->x64);
    func_801C3960(stage_info.x6B0->x20);
    func_801C3950(stage_info.x6B0->x24);
    if (stage_info.x6A8 != NULL) {
        for (i = 0; stage_info.x6A8[i] != NULL; i++) {
            func_8026B40C(stage_info.x6A8[i]->unk4, stage_info.x6A8[i]->unk0);
        }
    }
    if (stage_info.x6B4 != NULL) {
        for (i = 1; stage_info.x6B4[i] != 0; i++) {
            lbl_804D6D38->x1D4->xC[i].xC = stage_info.x6B4[i];
        }
    }
    if (stage_info.x6B8 != NULL && stage_info.x6BC != NULL) {
        func_803984F4(0x1E, stage_info.x6B8, stage_info.x6BC, 0, 0);
    }
    func_8004D288(stage_info.x6AC);
    func_80058820();
    func_801C1E94();
    func_801C466C();
    stage_data->callback0();
}

#include <sysdolphin/baselib/random.h>

static BOOL func_801C0A70(Point3d* pos)
{
    if (HSD_Randi(2) != 0) {
        s32 enabled_stages[] = {
            CASTLE,
            RCRUISE,
            KONGO,
            GARDEN,
            GREATBAY,
            SHRINE,
            ZEBES,
            KRAID,
            STORY,
            YORSTER,
            IZUMI,
            GREENS,
            CORNERIA,
            VENOM,
            PSTADIUM,
            PURA,
            MUTECITY,
            BIGBLUE,
            ONETT,
            FOURSIDE,
            // ICEMTN disabled
            // id 0x17 unused/unknown?
            INISHIE1,
            INISHIE2,
            // id 0x1A unused/unknown?
            // FLATZONE disabled
            OLDPUPUPU,
            OLDYOSHI,
            OLDKONGO,
            // TODO what stages are these?
            36,
            37,
        };

        s32 player_slot;
        s32 nstages = sizeof(enabled_stages) / sizeof(enabled_stages[0]);
        int unused[5];
        u32 i;

        s32 stage_id = stage_info.internal_stage_id;
        for (i = 0; i < nstages; i++) {
            if (stage_id == enabled_stages[i]) {
                break;
            }
        }
        if (i != nstages) {
            player_slot = HSD_Randi(4);
            if (Player_GetEntity(player_slot) != NULL) {
                s32 xoff;
                Player_LoadPlayerCoords(player_slot, pos);
                pos->y = -5.0f + Stage_GetBlastZoneTopOffset();
                xoff = HSD_Randi(0x64) - 0x32;
                pos->x += xoff;
                return TRUE;
            }
        }
    }
    if (Stage_80224FDC(pos) != 0) {
        return TRUE;
    } else {
        return FALSE;
    }
}

#include <melee/gm/code_801601C4.h>

extern u32 lbl_803B7DEC[];
extern void func_8026BE84();
static asm void func_801C0C2C()
{
    nofralloc
/* 801C0C2C 001BD80C  7C 08 02 A6 */	mflr r0
/* 801C0C30 001BD810  3C 60 80 4A */	lis r3, stage_info@ha
/* 801C0C34 001BD814  90 01 00 04 */	stw r0, 4(r1)
/* 801C0C38 001BD818  94 21 FF 70 */	stwu r1, -0x90(r1)
/* 801C0C3C 001BD81C  DB E1 00 88 */	stfd f31, 0x88(r1)
/* 801C0C40 001BD820  DB C1 00 80 */	stfd f30, 0x80(r1)
/* 801C0C44 001BD824  DB A1 00 78 */	stfd f29, 0x78(r1)
/* 801C0C48 001BD828  DB 81 00 70 */	stfd f28, 0x70(r1)
/* 801C0C4C 001BD82C  93 E1 00 6C */	stw r31, 0x6c(r1)
/* 801C0C50 001BD830  3B E3 E6 C8 */	addi r31, r3, stage_info@l
/* 801C0C54 001BD834  93 C1 00 68 */	stw r30, 0x68(r1)
/* 801C0C58 001BD838  3B DF 00 8C */	addi r30, r31, 0x8c
/* 801C0C5C 001BD83C  93 A1 00 64 */	stw r29, 0x64(r1)
/* 801C0C60 001BD840  93 81 00 60 */	stw r28, 0x60(r1)
/* 801C0C64 001BD844  88 7F 00 8C */	lbz r3, 0x8c(r31)
/* 801C0C68 001BD848  54 60 FF FF */	rlwinm. r0, r3, 0x1f, 0x1f, 0x1f
/* 801C0C6C 001BD84C  40 82 00 0C */	bne lbl_801C0C78
/* 801C0C70 001BD850  54 60 07 FF */	clrlwi. r0, r3, 0x1f
/* 801C0C74 001BD854  41 82 02 2C */	beq lbl_801C0EA0
lbl_801C0C78:
/* 801C0C78 001BD858  48 00 4B 2D */	bl func_801C57A4
/* 801C0C7C 001BD85C  7C 7D 1B 79 */	or. r29, r3, r3
/* 801C0C80 001BD860  41 82 02 20 */	beq lbl_801C0EA0
/* 801C0C84 001BD864  7F A3 EB 78 */	mr r3, r29
/* 801C0C88 001BD868  4B EC 63 95 */	bl func_8008701C
/* 801C0C8C 001BD86C  2C 03 00 00 */	cmpwi r3, 0
/* 801C0C90 001BD870  40 82 02 10 */	bne lbl_801C0EA0
/* 801C0C94 001BD874  38 7D 00 00 */	addi r3, r29, 0
/* 801C0C98 001BD878  38 81 00 50 */	addi r4, r1, 0x50
/* 801C0C9C 001BD87C  4B EC 59 A9 */	bl func_80086644
/* 801C0CA0 001BD880  88 1E 00 00 */	lbz r0, 0(r30)
/* 801C0CA4 001BD884  54 00 FF FF */	rlwinm. r0, r0, 0x1f, 0x1f, 0x1f
/* 801C0CA8 001BD888  41 82 00 F8 */	beq lbl_801C0DA0
/* 801C0CAC 001BD88C  C3 BF 07 0C */	lfs f29, 0x70c(r31)
/* 801C0CB0 001BD890  3B 80 00 00 */	li r28, 0
/* 801C0CB4 001BD894  C3 9F 07 10 */	lfs f28, 0x710(r31)
/* 801C0CB8 001BD898  3B A0 00 99 */	li r29, 0x99
/* 801C0CBC 001BD89C  FF E0 E8 50 */	fneg f31, f29
/* 801C0CC0 001BD8A0  FF C0 E0 50 */	fneg f30, f28
lbl_801C0CC4:
/* 801C0CC4 001BD8A4  38 7D 00 00 */	addi r3, r29, 0
/* 801C0CC8 001BD8A8  38 81 00 44 */	addi r4, r1, 0x44
/* 801C0CCC 001BD8AC  48 00 20 59 */	bl func_801C2D24
/* 801C0CD0 001BD8B0  2C 03 00 00 */	cmpwi r3, 0
/* 801C0CD4 001BD8B4  41 82 00 98 */	beq lbl_801C0D6C
/* 801C0CD8 001BD8B8  C0 41 00 50 */	lfs f2, 0x50(r1)
/* 801C0CDC 001BD8BC  38 00 00 00 */	li r0, 0
/* 801C0CE0 001BD8C0  C0 01 00 44 */	lfs f0, 0x44(r1)
/* 801C0CE4 001BD8C4  7C 03 03 78 */	mr r3, r0
/* 801C0CE8 001BD8C8  C0 21 00 54 */	lfs f1, 0x54(r1)
/* 801C0CEC 001BD8CC  EC 42 00 28 */	fsubs f2, f2, f0
/* 801C0CF0 001BD8D0  C0 01 00 48 */	lfs f0, 0x48(r1)
/* 801C0CF4 001BD8D4  7C 04 03 78 */	mr r4, r0
/* 801C0CF8 001BD8D8  EC 01 00 28 */	fsubs f0, f1, f0
/* 801C0CFC 001BD8DC  FC 02 F8 40 */	fcmpo cr0, f2, f31
/* 801C0D00 001BD8E0  40 81 00 10 */	ble lbl_801C0D10
/* 801C0D04 001BD8E4  FC 02 E8 40 */	fcmpo cr0, f2, f29
/* 801C0D08 001BD8E8  40 80 00 08 */	bge lbl_801C0D10
/* 801C0D0C 001BD8EC  38 80 00 01 */	li r4, 1
lbl_801C0D10:
/* 801C0D10 001BD8F0  2C 04 00 00 */	cmpwi r4, 0
/* 801C0D14 001BD8F4  41 82 00 10 */	beq lbl_801C0D24
/* 801C0D18 001BD8F8  FC 00 F0 40 */	fcmpo cr0, f0, f30
/* 801C0D1C 001BD8FC  40 81 00 08 */	ble lbl_801C0D24
/* 801C0D20 001BD900  38 60 00 01 */	li r3, 1
lbl_801C0D24:
/* 801C0D24 001BD904  2C 03 00 00 */	cmpwi r3, 0
/* 801C0D28 001BD908  41 82 00 10 */	beq lbl_801C0D38
/* 801C0D2C 001BD90C  FC 00 E0 40 */	fcmpo cr0, f0, f28
/* 801C0D30 001BD910  40 80 00 08 */	bge lbl_801C0D38
/* 801C0D34 001BD914  38 00 00 01 */	li r0, 1
lbl_801C0D38:
/* 801C0D38 001BD918  2C 00 00 00 */	cmpwi r0, 0
/* 801C0D3C 001BD91C  41 82 00 30 */	beq lbl_801C0D6C
/* 801C0D40 001BD920  81 9F 00 90 */	lwz r12, 0x90(r31)
/* 801C0D44 001BD924  28 0C 00 00 */	cmplwi r12, 0
/* 801C0D48 001BD928  41 82 00 1C */	beq lbl_801C0D64
/* 801C0D4C 001BD92C  7D 88 03 A6 */	mtlr r12
/* 801C0D50 001BD930  38 9D 00 00 */	addi r4, r29, 0
/* 801C0D54 001BD934  38 61 00 50 */	addi r3, r1, 0x50
/* 801C0D58 001BD938  4E 80 00 21 */	blrl 
/* 801C0D5C 001BD93C  2C 03 00 00 */	cmpwi r3, 0
/* 801C0D60 001BD940  41 82 00 0C */	beq lbl_801C0D6C
lbl_801C0D64:
/* 801C0D64 001BD944  3B 80 00 01 */	li r28, 1
/* 801C0D68 001BD948  48 00 00 10 */	b lbl_801C0D78
lbl_801C0D6C:
/* 801C0D6C 001BD94C  3B BD 00 01 */	addi r29, r29, 1
/* 801C0D70 001BD950  2C 1D 00 B3 */	cmpwi r29, 0xb3
/* 801C0D74 001BD954  41 80 FF 50 */	blt lbl_801C0CC4
lbl_801C0D78:
/* 801C0D78 001BD958  2C 1C 00 00 */	cmpwi r28, 0
/* 801C0D7C 001BD95C  41 82 00 0C */	beq lbl_801C0D88
/* 801C0D80 001BD960  93 BF 07 14 */	stw r29, 0x714(r31)
/* 801C0D84 001BD964  48 00 00 0C */	b lbl_801C0D90
lbl_801C0D88:
/* 801C0D88 001BD968  38 00 FF FF */	li r0, -1
/* 801C0D8C 001BD96C  90 1F 07 14 */	stw r0, 0x714(r31)
lbl_801C0D90:
/* 801C0D90 001BD970  88 1E 00 00 */	lbz r0, 0(r30)
/* 801C0D94 001BD974  38 60 00 00 */	li r3, 0
/* 801C0D98 001BD978  50 60 0F BC */	rlwimi r0, r3, 1, 0x1e, 0x1e
/* 801C0D9C 001BD97C  98 1E 00 00 */	stb r0, 0(r30)
lbl_801C0DA0:
/* 801C0DA0 001BD980  88 1E 00 00 */	lbz r0, 0(r30)
/* 801C0DA4 001BD984  54 00 07 FF */	clrlwi. r0, r0, 0x1f
/* 801C0DA8 001BD988  41 82 00 F8 */	beq lbl_801C0EA0
/* 801C0DAC 001BD98C  C3 9F 07 18 */	lfs f28, 0x718(r31)
/* 801C0DB0 001BD990  3B A0 00 00 */	li r29, 0
/* 801C0DB4 001BD994  C3 BF 07 1C */	lfs f29, 0x71c(r31)
/* 801C0DB8 001BD998  3B 80 00 BD */	li r28, 0xbd
/* 801C0DBC 001BD99C  FF C0 E0 50 */	fneg f30, f28
/* 801C0DC0 001BD9A0  FF E0 E8 50 */	fneg f31, f29
lbl_801C0DC4:
/* 801C0DC4 001BD9A4  38 7C 00 00 */	addi r3, r28, 0
/* 801C0DC8 001BD9A8  38 81 00 38 */	addi r4, r1, 0x38
/* 801C0DCC 001BD9AC  48 00 1F 59 */	bl func_801C2D24
/* 801C0DD0 001BD9B0  2C 03 00 00 */	cmpwi r3, 0
/* 801C0DD4 001BD9B4  41 82 00 98 */	beq lbl_801C0E6C
/* 801C0DD8 001BD9B8  C0 41 00 50 */	lfs f2, 0x50(r1)
/* 801C0DDC 001BD9BC  38 00 00 00 */	li r0, 0
/* 801C0DE0 001BD9C0  C0 01 00 38 */	lfs f0, 0x38(r1)
/* 801C0DE4 001BD9C4  7C 03 03 78 */	mr r3, r0
/* 801C0DE8 001BD9C8  C0 21 00 54 */	lfs f1, 0x54(r1)
/* 801C0DEC 001BD9CC  EC 42 00 28 */	fsubs f2, f2, f0
/* 801C0DF0 001BD9D0  C0 01 00 3C */	lfs f0, 0x3c(r1)
/* 801C0DF4 001BD9D4  7C 04 03 78 */	mr r4, r0
/* 801C0DF8 001BD9D8  EC 01 00 28 */	fsubs f0, f1, f0
/* 801C0DFC 001BD9DC  FC 02 F0 40 */	fcmpo cr0, f2, f30
/* 801C0E00 001BD9E0  40 81 00 10 */	ble lbl_801C0E10
/* 801C0E04 001BD9E4  FC 02 E0 40 */	fcmpo cr0, f2, f28
/* 801C0E08 001BD9E8  40 80 00 08 */	bge lbl_801C0E10
/* 801C0E0C 001BD9EC  38 80 00 01 */	li r4, 1
lbl_801C0E10:
/* 801C0E10 001BD9F0  2C 04 00 00 */	cmpwi r4, 0
/* 801C0E14 001BD9F4  41 82 00 10 */	beq lbl_801C0E24
/* 801C0E18 001BD9F8  FC 00 F8 40 */	fcmpo cr0, f0, f31
/* 801C0E1C 001BD9FC  40 81 00 08 */	ble lbl_801C0E24
/* 801C0E20 001BDA00  38 60 00 01 */	li r3, 1
lbl_801C0E24:
/* 801C0E24 001BDA04  2C 03 00 00 */	cmpwi r3, 0
/* 801C0E28 001BDA08  41 82 00 10 */	beq lbl_801C0E38
/* 801C0E2C 001BDA0C  FC 00 E8 40 */	fcmpo cr0, f0, f29
/* 801C0E30 001BDA10  40 80 00 08 */	bge lbl_801C0E38
/* 801C0E34 001BDA14  38 00 00 01 */	li r0, 1
lbl_801C0E38:
/* 801C0E38 001BDA18  2C 00 00 00 */	cmpwi r0, 0
/* 801C0E3C 001BDA1C  41 82 00 30 */	beq lbl_801C0E6C
/* 801C0E40 001BDA20  81 9F 00 94 */	lwz r12, 0x94(r31)
/* 801C0E44 001BDA24  28 0C 00 00 */	cmplwi r12, 0
/* 801C0E48 001BDA28  41 82 00 1C */	beq lbl_801C0E64
/* 801C0E4C 001BDA2C  7D 88 03 A6 */	mtlr r12
/* 801C0E50 001BDA30  38 9C 00 00 */	addi r4, r28, 0
/* 801C0E54 001BDA34  38 61 00 50 */	addi r3, r1, 0x50
/* 801C0E58 001BDA38  4E 80 00 21 */	blrl 
/* 801C0E5C 001BDA3C  2C 03 00 00 */	cmpwi r3, 0
/* 801C0E60 001BDA40  41 82 00 0C */	beq lbl_801C0E6C
lbl_801C0E64:
/* 801C0E64 001BDA44  3B A0 00 01 */	li r29, 1
/* 801C0E68 001BDA48  48 00 00 10 */	b lbl_801C0E78
lbl_801C0E6C:
/* 801C0E6C 001BDA4C  3B 9C 00 01 */	addi r28, r28, 1
/* 801C0E70 001BDA50  2C 1C 00 C7 */	cmpwi r28, 0xc7
/* 801C0E74 001BDA54  41 80 FF 50 */	blt lbl_801C0DC4
lbl_801C0E78:
/* 801C0E78 001BDA58  2C 1D 00 00 */	cmpwi r29, 0
/* 801C0E7C 001BDA5C  41 82 00 0C */	beq lbl_801C0E88
/* 801C0E80 001BDA60  93 9F 07 20 */	stw r28, 0x720(r31)
/* 801C0E84 001BDA64  48 00 00 0C */	b lbl_801C0E90
lbl_801C0E88:
/* 801C0E88 001BDA68  38 00 FF FF */	li r0, -1
/* 801C0E8C 001BDA6C  90 1F 07 20 */	stw r0, 0x720(r31)
lbl_801C0E90:
/* 801C0E90 001BDA70  88 1E 00 00 */	lbz r0, 0(r30)
/* 801C0E94 001BDA74  38 60 00 00 */	li r3, 0
/* 801C0E98 001BDA78  50 60 07 FE */	rlwimi r0, r3, 0, 0x1f, 0x1f
/* 801C0E9C 001BDA7C  98 1E 00 00 */	stb r0, 0(r30)
lbl_801C0EA0:
/* 801C0EA0 001BDA80  4B FA A3 99 */	bl func_8016B238
/* 801C0EA4 001BDA84  2C 03 00 00 */	cmpwi r3, 0
/* 801C0EA8 001BDA88  41 82 00 A0 */	beq lbl_801C0F48
/* 801C0EAC 001BDA8C  4B FA A0 31 */	bl func_8016AEDC
/* 801C0EB0 001BDA90  2C 03 04 B0 */	cmpwi r3, 0x4b0
/* 801C0EB4 001BDA94  40 81 00 94 */	ble lbl_801C0F48
/* 801C0EB8 001BDA98  38 9F 00 9C */	addi r4, r31, 0x9c
/* 801C0EBC 001BDA9C  80 1F 00 9C */	lwz r0, 0x9c(r31)
/* 801C0EC0 001BDAA0  7C 00 18 50 */	subf r0, r0, r3
/* 801C0EC4 001BDAA4  28 00 00 1E */	cmplwi r0, 0x1e
/* 801C0EC8 001BDAA8  40 81 00 80 */	ble lbl_801C0F48
/* 801C0ECC 001BDAAC  90 64 00 00 */	stw r3, 0(r4)
/* 801C0ED0 001BDAB0  38 61 00 2C */	addi r3, r1, 0x2c
/* 801C0ED4 001BDAB4  4B FF FB 9D */	bl func_801C0A70
/* 801C0ED8 001BDAB8  2C 03 00 00 */	cmpwi r3, 0
/* 801C0EDC 001BDABC  41 82 00 6C */	beq lbl_801C0F48
/* 801C0EE0 001BDAC0  3C 60 80 3B */	lis r3, lbl_803B7DEC@ha
/* 801C0EE4 001BDAC4  80 A1 00 2C */	lwz r5, 0x2c(r1)
/* 801C0EE8 001BDAC8  39 03 7D EC */	addi r8, r3, lbl_803B7DEC@l
/* 801C0EEC 001BDACC  80 81 00 30 */	lwz r4, 0x30(r1)
/* 801C0EF0 001BDAD0  80 E8 00 00 */	lwz r7, 0(r8)
/* 801C0EF4 001BDAD4  38 61 00 0C */	addi r3, r1, 0xc
/* 801C0EF8 001BDAD8  80 C8 00 04 */	lwz r6, 4(r8)
/* 801C0EFC 001BDADC  80 01 00 34 */	lwz r0, 0x34(r1)
/* 801C0F00 001BDAE0  90 E1 00 0C */	stw r7, 0xc(r1)
/* 801C0F04 001BDAE4  90 C1 00 10 */	stw r6, 0x10(r1)
/* 801C0F08 001BDAE8  80 E8 00 08 */	lwz r7, 8(r8)
/* 801C0F0C 001BDAEC  80 C8 00 0C */	lwz r6, 0xc(r8)
/* 801C0F10 001BDAF0  90 E1 00 14 */	stw r7, 0x14(r1)
/* 801C0F14 001BDAF4  90 C1 00 18 */	stw r6, 0x18(r1)
/* 801C0F18 001BDAF8  80 E8 00 10 */	lwz r7, 0x10(r8)
/* 801C0F1C 001BDAFC  80 C8 00 14 */	lwz r6, 0x14(r8)
/* 801C0F20 001BDB00  90 E1 00 1C */	stw r7, 0x1c(r1)
/* 801C0F24 001BDB04  90 C1 00 20 */	stw r6, 0x20(r1)
/* 801C0F28 001BDB08  80 E8 00 18 */	lwz r7, 0x18(r8)
/* 801C0F2C 001BDB0C  80 C8 00 1C */	lwz r6, 0x1c(r8)
/* 801C0F30 001BDB10  90 E1 00 24 */	stw r7, 0x24(r1)
/* 801C0F34 001BDB14  90 C1 00 28 */	stw r6, 0x28(r1)
/* 801C0F38 001BDB18  90 A1 00 14 */	stw r5, 0x14(r1)
/* 801C0F3C 001BDB1C  90 81 00 18 */	stw r4, 0x18(r1)
/* 801C0F40 001BDB20  90 01 00 1C */	stw r0, 0x1c(r1)
/* 801C0F44 001BDB24  48 0A AF 41 */	bl func_8026BE84
lbl_801C0F48:
/* 801C0F48 001BDB28  80 01 00 94 */	lwz r0, 0x94(r1)
/* 801C0F4C 001BDB2C  CB E1 00 88 */	lfd f31, 0x88(r1)
/* 801C0F50 001BDB30  CB C1 00 80 */	lfd f30, 0x80(r1)
/* 801C0F54 001BDB34  CB A1 00 78 */	lfd f29, 0x78(r1)
/* 801C0F58 001BDB38  CB 81 00 70 */	lfd f28, 0x70(r1)
/* 801C0F5C 001BDB3C  83 E1 00 6C */	lwz r31, 0x6c(r1)
/* 801C0F60 001BDB40  83 C1 00 68 */	lwz r30, 0x68(r1)
/* 801C0F64 001BDB44  83 A1 00 64 */	lwz r29, 0x64(r1)
/* 801C0F68 001BDB48  83 81 00 60 */	lwz r28, 0x60(r1)
/* 801C0F6C 001BDB4C  38 21 00 90 */	addi r1, r1, 0x90
/* 801C0F70 001BDB50  7C 08 03 A6 */	mtlr r0
/* 801C0F74 001BDB54  4E 80 00 20 */	blr 
}
#pragma peephole on

void func_801C0F78(StructPairWithStageID* pair)
{
    lbl_803DFEDC[pair->stage_id]->callback2();
}

void func_801C0FB8(StructPairWithStageID* pair)
{
    struct {
        void* unk0;
        s32 unk4;
        void (*unk8)(s32);
    }* cur;
    void* next;

    lbl_803DFEDC[pair->stage_id]->callback3();

    for (cur = stage_info.x6A4; cur != NULL; cur = next) {
        next = cur->unk0;
        cur->unk8(cur->unk4);
        HSD_Free(cur);
    }
    stage_info.x6A4 = NULL;

    func_8038FD54(func_803901F0(3, 5, 0), func_801C0C2C, 10);
}

void func_801C1074(StructPairWithStageID* pair, s32 arg1)
{
    lbl_803DFEDC[pair->stage_id]->callback1(arg1);
}

void func_801C10B8(s32 arg0, s32 arg1)
{
    struct {
        void* unk0;
        s32 unk4, unk8;
    }* temp_r3;

    temp_r3 = HSD_MemAlloc(0xC);
    if (temp_r3 != NULL) {
        temp_r3->unk0 = stage_info.x6A4;
        temp_r3->unk4 = arg0;
        temp_r3->unk8 = arg1;
        stage_info.x6A4 = temp_r3;
    } else {
        OSReport("%s:%d: assert\n", __FILE__, 1119);
        OSPanic(__FILE__, 1120, "");
    }
}

void func_801C1154()
{
}

void func_801C1158(void)
{
    switch (stage_info.internal_stage_id) {
    case 16:
        func_801D39A0(func_801C2BA4(1));
        break;
    case 14:
    case 15:
        func_801E2A6C();
        break;
    }
}

void func_801C11AC(HSD_GObj* gobj)
{
    HSD_JObj* jobj;
    Vec3 scale;
    f32 tmp = 1.0f;
    jobj = gobj->hsd_obj;
    scale.z = tmp;
    scale.y = tmp;
    scale.x = tmp;
    HSD_JObjSetScale(jobj, &scale);
}

static HSD_Joint* func_801C126C(HSD_Joint* node, s32* depth)
{
    HSD_Joint* result;
    *depth -= 1;
    if (*depth < 0) {
        return node;
    }
    if (node->child != NULL) {
        if ((result = func_801C126C(node->child, depth)) != NULL) {
            return result;
        }
    }
    if (node->next != NULL) {
        if ((result = func_801C126C(node->next, depth)) != NULL) {
            return result;
        }
    }
    return NULL;
}

HSD_JObj* func_801C13D0(s32 arg0, s32 depth)
{
    HSD_JObj* result = NULL;
    UnkArchiveStruct* archive = func_801C6330(arg0);
    if (archive != NULL && arg0 < archive->unk4->unkC) {
        HSD_Joint* joint;
        if (depth == 0) {
            joint = archive->unk4->unk8[arg0].unk0;
        } else {
            s32 tmp_depth = depth;
            joint = func_801C126C(archive->unk4->unk8[arg0].unk0, &tmp_depth);
        }
        result = HSD_JObjLoadJoint(joint);
    }
    return result;
}

#include <sysdolphin/baselib/gobjplink.h>

char lbl_804D44F8[8] = "archive";
extern HSD_Joint lbl_803B7E0C;
extern u8 lbl_804D784B[5];
extern void lbl_801C5F60();
extern u8 lbl_804D7849;
extern void PSMTXIdentity();
extern void func_8000F9F8();
extern void func_80013B14();
extern void HSD_JObjAddNext();

asm struct _HSD_GObj* func_801C14D0(s32)
{
    nofralloc
/* 801C14D0 001BE0B0  7C 08 02 A6 */	mflr r0
/* 801C14D4 001BE0B4  3C A0 80 3E */	lis r5, lbl_803DFEA8@ha
/* 801C14D8 001BE0B8  90 01 00 04 */	stw r0, 4(r1)
/* 801C14DC 001BE0BC  3C 80 80 4A */	lis r4, stage_info@ha
/* 801C14E0 001BE0C0  94 21 FF 30 */	stwu r1, -0xd0(r1)
/* 801C14E4 001BE0C4  BE E1 00 AC */	stmw r23, 0xac(r1)
/* 801C14E8 001BE0C8  3B C3 00 00 */	addi r30, r3, 0
/* 801C14EC 001BE0CC  3B 65 FE A8 */	addi r27, r5, lbl_803DFEA8@l
/* 801C14F0 001BE0D0  3B 84 E6 C8 */	addi r28, r4, stage_info@l
/* 801C14F4 001BE0D4  38 60 00 03 */	li r3, 3
/* 801C14F8 001BE0D8  38 80 00 05 */	li r4, 5
/* 801C14FC 001BE0DC  38 A0 00 00 */	li r5, 0
/* 801C1500 001BE0E0  48 1C EC F1 */	bl func_803901F0
/* 801C1504 001BE0E4  7C 7F 1B 79 */	or. r31, r3, r3
/* 801C1508 001BE0E8  40 82 00 20 */	bne lbl_801C1528
/* 801C150C 001BE0EC  38 7B 02 50 */	addi r3, r27, 0x250
/* 801C1510 001BE0F0  4C C6 31 82 */	crclr 6
/* 801C1514 001BE0F4  38 9B 02 18 */	addi r4, r27, 0x218
/* 801C1518 001BE0F8  38 A0 05 22 */	li r5, 0x522
/* 801C151C 001BE0FC  48 18 41 8D */	bl OSReport
/* 801C1520 001BE100  38 60 00 00 */	li r3, 0
/* 801C1524 001BE104  48 00 04 E8 */	b lbl_801C1A0C
lbl_801C1528:
/* 801C1528 001BE108  38 60 02 04 */	li r3, 0x204
/* 801C152C 001BE10C  48 1B DC B9 */	bl HSD_MemAlloc
/* 801C1530 001BE110  7C 7A 1B 79 */	or. r26, r3, r3
/* 801C1534 001BE114  40 82 00 18 */	bne lbl_801C154C
/* 801C1538 001BE118  38 7B 01 F0 */	addi r3, r27, 0x1f0
/* 801C153C 001BE11C  4C C6 31 82 */	crclr 6
/* 801C1540 001BE120  38 9B 02 18 */	addi r4, r27, 0x218
/* 801C1544 001BE124  38 A0 01 DA */	li r5, 0x1da
/* 801C1548 001BE128  48 18 41 61 */	bl OSReport
lbl_801C154C:
/* 801C154C 001BE12C  28 1A 00 00 */	cmplwi r26, 0
/* 801C1550 001BE130  38 DA 00 00 */	addi r6, r26, 0
/* 801C1554 001BE134  40 82 00 14 */	bne lbl_801C1568
/* 801C1558 001BE138  7F E3 FB 78 */	mr r3, r31
/* 801C155C 001BE13C  48 1C EC CD */	bl func_80390228
/* 801C1560 001BE140  38 60 00 00 */	li r3, 0
/* 801C1564 001BE144  48 00 04 A8 */	b lbl_801C1A0C
lbl_801C1568:
/* 801C1568 001BE148  3C 60 80 1C */	lis r3, func_801C0478@ha
/* 801C156C 001BE14C  38 A3 04 78 */	addi r5, r3, func_801C0478@l
/* 801C1570 001BE150  38 7F 00 00 */	addi r3, r31, 0
/* 801C1574 001BE154  38 80 00 03 */	li r4, 3
/* 801C1578 001BE158  48 1C F5 F1 */	bl GObj_InitUserData
/* 801C157C 001BE15C  93 DA 00 14 */	stw r30, 0x14(r26)
/* 801C1580 001BE160  38 C0 00 00 */	li r6, 0
/* 801C1584 001BE164  38 A0 00 01 */	li r5, 1
/* 801C1588 001BE168  93 FA 00 04 */	stw r31, 4(r26)
/* 801C158C 001BE16C  38 00 FF FF */	li r0, -1
/* 801C1590 001BE170  38 7F 00 00 */	addi r3, r31, 0
/* 801C1594 001BE174  88 9A 00 10 */	lbz r4, 0x10(r26)
/* 801C1598 001BE178  50 C4 3E 30 */	rlwimi r4, r6, 7, 0x18, 0x18
/* 801C159C 001BE17C  98 9A 00 10 */	stb r4, 0x10(r26)
/* 801C15A0 001BE180  88 9A 00 10 */	lbz r4, 0x10(r26)
/* 801C15A4 001BE184  50 C4 36 72 */	rlwimi r4, r6, 6, 0x19, 0x19
/* 801C15A8 001BE188  98 9A 00 10 */	stb r4, 0x10(r26)
/* 801C15AC 001BE18C  88 9A 00 10 */	lbz r4, 0x10(r26)
/* 801C15B0 001BE190  50 A4 2E B4 */	rlwimi r4, r5, 5, 0x1a, 0x1a
/* 801C15B4 001BE194  98 9A 00 10 */	stb r4, 0x10(r26)
/* 801C15B8 001BE198  90 DA 00 08 */	stw r6, 8(r26)
/* 801C15BC 001BE19C  90 DA 00 0C */	stw r6, 0xc(r26)
/* 801C15C0 001BE1A0  90 DA 00 1C */	stw r6, 0x1c(r26)
/* 801C15C4 001BE1A4  88 9A 00 10 */	lbz r4, 0x10(r26)
/* 801C15C8 001BE1A8  50 C4 17 7A */	rlwimi r4, r6, 2, 0x1d, 0x1d
/* 801C15CC 001BE1AC  98 9A 00 10 */	stb r4, 0x10(r26)
/* 801C15D0 001BE1B0  88 9A 00 10 */	lbz r4, 0x10(r26)
/* 801C15D4 001BE1B4  50 C4 0F BC */	rlwimi r4, r6, 1, 0x1e, 0x1e
/* 801C15D8 001BE1B8  98 9A 00 10 */	stb r4, 0x10(r26)
/* 801C15DC 001BE1BC  88 9A 00 11 */	lbz r4, 0x11(r26)
/* 801C15E0 001BE1C0  50 C4 2E 34 */	rlwimi r4, r6, 5, 0x18, 0x1a
/* 801C15E4 001BE1C4  98 9A 00 11 */	stb r4, 0x11(r26)
/* 801C15E8 001BE1C8  88 9A 00 10 */	lbz r4, 0x10(r26)
/* 801C15EC 001BE1CC  50 C4 07 FE */	rlwimi r4, r6, 0, 0x1f, 0x1f
/* 801C15F0 001BE1D0  98 9A 00 10 */	stb r4, 0x10(r26)
/* 801C15F4 001BE1D4  90 DA 00 18 */	stw r6, 0x18(r26)
/* 801C15F8 001BE1D8  88 9A 00 10 */	lbz r4, 0x10(r26)
/* 801C15FC 001BE1DC  50 C4 26 F6 */	rlwimi r4, r6, 4, 0x1b, 0x1b
/* 801C1600 001BE1E0  98 9A 00 10 */	stb r4, 0x10(r26)
/* 801C1604 001BE1E4  90 1A 00 20 */	stw r0, 0x20(r26)
/* 801C1608 001BE1E8  90 1A 00 24 */	stw r0, 0x24(r26)
/* 801C160C 001BE1EC  90 1A 00 28 */	stw r0, 0x28(r26)
/* 801C1610 001BE1F0  90 1A 00 2C */	stw r0, 0x2c(r26)
/* 801C1614 001BE1F4  90 1A 00 30 */	stw r0, 0x30(r26)
/* 801C1618 001BE1F8  90 1A 00 34 */	stw r0, 0x34(r26)
/* 801C161C 001BE1FC  90 1A 00 38 */	stw r0, 0x38(r26)
/* 801C1620 001BE200  90 1A 00 3C */	stw r0, 0x3c(r26)
/* 801C1624 001BE204  48 00 7F A1 */	bl func_801C95C4
/* 801C1628 001BE208  48 00 4C FD */	bl func_801C6324
/* 801C162C 001BE20C  7C 77 1B 79 */	or. r23, r3, r3
/* 801C1630 001BE210  40 82 00 14 */	bne lbl_801C1644
/* 801C1634 001BE214  38 7B 02 18 */	addi r3, r27, 0x218
/* 801C1638 001BE218  38 80 05 4E */	li r4, 0x54e
/* 801C163C 001BE21C  38 AD 8E 58 */	addi r5, r13, lbl_804D44F8
/* 801C1640 001BE220  48 1C 6B E1 */	bl __assert
lbl_801C1644:
/* 801C1644 001BE224  80 77 00 04 */	lwz r3, 4(r23)
/* 801C1648 001BE228  80 03 00 0C */	lwz r0, 0xc(r3)
/* 801C164C 001BE22C  7C 1E 00 00 */	cmpw r30, r0
/* 801C1650 001BE230  40 80 02 4C */	bge lbl_801C189C
/* 801C1654 001BE234  7F C3 F3 78 */	mr r3, r30
/* 801C1658 001BE238  48 00 4C D9 */	bl func_801C6330
/* 801C165C 001BE23C  7C 7D 1B 78 */	mr r29, r3
/* 801C1660 001BE240  80 63 00 04 */	lwz r3, 4(r3)
/* 801C1664 001BE244  1F 3E 00 34 */	mulli r25, r30, 0x34
/* 801C1668 001BE248  80 63 00 08 */	lwz r3, 8(r3)
/* 801C166C 001BE24C  7F 03 C8 2E */	lwzx r24, r3, r25
/* 801C1670 001BE250  7F 03 C3 78 */	mr r3, r24
/* 801C1674 001BE254  48 1A F7 D1 */	bl HSD_JObjLoadJoint
/* 801C1678 001BE258  3A E3 00 00 */	addi r23, r3, 0
/* 801C167C 001BE25C  38 7E 00 00 */	addi r3, r30, 0
/* 801C1680 001BE260  38 97 00 00 */	addi r4, r23, 0
/* 801C1684 001BE264  38 B8 00 00 */	addi r5, r24, 0
/* 801C1688 001BE268  48 00 1E 25 */	bl func_801C34AC
/* 801C168C 001BE26C  80 7C 06 B0 */	lwz r3, 0x6b0(r28)
/* 801C1690 001BE270  28 03 00 00 */	cmplwi r3, 0
/* 801C1694 001BE274  41 82 00 0C */	beq lbl_801C16A0
/* 801C1698 001BE278  C0 03 00 00 */	lfs f0, 0(r3)
/* 801C169C 001BE27C  48 00 00 08 */	b lbl_801C16A4
lbl_801C16A0:
/* 801C16A0 001BE280  C0 02 B2 E4 */	lfs f0, 1.0f
lbl_801C16A4:
/* 801C16A4 001BE284  3C 60 80 3B */	lis r3, lbl_803B7E0C@ha
/* 801C16A8 001BE288  38 A3 7E 0C */	addi r5, r3, lbl_803B7E0C@l
/* 801C16AC 001BE28C  80 85 00 00 */	lwz r4, 0(r5)
/* 801C16B0 001BE290  38 61 00 58 */	addi r3, r1, 0x58
/* 801C16B4 001BE294  80 05 00 04 */	lwz r0, 4(r5)
/* 801C16B8 001BE298  90 81 00 58 */	stw r4, 0x58(r1)
/* 801C16BC 001BE29C  90 01 00 5C */	stw r0, 0x5c(r1)
/* 801C16C0 001BE2A0  80 85 00 08 */	lwz r4, 8(r5)
/* 801C16C4 001BE2A4  80 05 00 0C */	lwz r0, 0xc(r5)
/* 801C16C8 001BE2A8  90 81 00 60 */	stw r4, 0x60(r1)
/* 801C16CC 001BE2AC  90 01 00 64 */	stw r0, 0x64(r1)
/* 801C16D0 001BE2B0  80 85 00 10 */	lwz r4, 0x10(r5)
/* 801C16D4 001BE2B4  80 05 00 14 */	lwz r0, 0x14(r5)
/* 801C16D8 001BE2B8  90 81 00 68 */	stw r4, 0x68(r1)
/* 801C16DC 001BE2BC  90 01 00 6C */	stw r0, 0x6c(r1)
/* 801C16E0 001BE2C0  80 85 00 18 */	lwz r4, 0x18(r5)
/* 801C16E4 001BE2C4  80 05 00 1C */	lwz r0, 0x1c(r5)
/* 801C16E8 001BE2C8  90 81 00 70 */	stw r4, 0x70(r1)
/* 801C16EC 001BE2CC  90 01 00 74 */	stw r0, 0x74(r1)
/* 801C16F0 001BE2D0  80 85 00 20 */	lwz r4, 0x20(r5)
/* 801C16F4 001BE2D4  80 05 00 24 */	lwz r0, 0x24(r5)
/* 801C16F8 001BE2D8  90 81 00 78 */	stw r4, 0x78(r1)
/* 801C16FC 001BE2DC  90 01 00 7C */	stw r0, 0x7c(r1)
/* 801C1700 001BE2E0  80 85 00 28 */	lwz r4, 0x28(r5)
/* 801C1704 001BE2E4  80 05 00 2C */	lwz r0, 0x2c(r5)
/* 801C1708 001BE2E8  90 81 00 80 */	stw r4, 0x80(r1)
/* 801C170C 001BE2EC  90 01 00 84 */	stw r0, 0x84(r1)
/* 801C1710 001BE2F0  80 85 00 30 */	lwz r4, 0x30(r5)
/* 801C1714 001BE2F4  80 05 00 34 */	lwz r0, 0x34(r5)
/* 801C1718 001BE2F8  90 81 00 88 */	stw r4, 0x88(r1)
/* 801C171C 001BE2FC  90 01 00 8C */	stw r0, 0x8c(r1)
/* 801C1720 001BE300  80 85 00 38 */	lwz r4, 0x38(r5)
/* 801C1724 001BE304  80 05 00 3C */	lwz r0, 0x3c(r5)
/* 801C1728 001BE308  90 81 00 90 */	stw r4, 0x90(r1)
/* 801C172C 001BE30C  90 01 00 94 */	stw r0, 0x94(r1)
/* 801C1730 001BE310  D0 01 00 80 */	stfs f0, 0x80(r1)
/* 801C1734 001BE314  D0 01 00 7C */	stfs f0, 0x7c(r1)
/* 801C1738 001BE318  D0 01 00 78 */	stfs f0, 0x78(r1)
/* 801C173C 001BE31C  48 1A F7 09 */	bl HSD_JObjLoadJoint
/* 801C1740 001BE320  7C 78 1B 79 */	or. r24, r3, r3
/* 801C1744 001BE324  40 82 00 1C */	bne lbl_801C1760
/* 801C1748 001BE328  38 7B 02 34 */	addi r3, r27, 0x234
/* 801C174C 001BE32C  4C C6 31 82 */	crclr 6
/* 801C1750 001BE330  38 9B 02 18 */	addi r4, r27, 0x218
/* 801C1754 001BE334  38 A0 04 C4 */	li r5, 0x4c4
/* 801C1758 001BE338  48 18 3F 51 */	bl OSReport
lbl_801C175C:
/* 801C175C 001BE33C  48 00 00 00 */	b lbl_801C175C
lbl_801C1760:
/* 801C1760 001BE340  38 77 00 00 */	addi r3, r23, 0
/* 801C1764 001BE344  38 98 00 00 */	addi r4, r24, 0
/* 801C1768 001BE348  48 1B 02 9D */	bl HSD_JObjAddNext
/* 801C176C 001BE34C  28 18 00 00 */	cmplwi r24, 0
/* 801C1770 001BE350  40 82 00 28 */	bne lbl_801C1798
/* 801C1774 001BE354  7F E3 FB 78 */	mr r3, r31
/* 801C1778 001BE358  48 1C EA B1 */	bl func_80390228
/* 801C177C 001BE35C  38 7B 02 34 */	addi r3, r27, 0x234
/* 801C1780 001BE360  4C C6 31 82 */	crclr 6
/* 801C1784 001BE364  38 9B 02 18 */	addi r4, r27, 0x218
/* 801C1788 001BE368  38 A0 05 5D */	li r5, 0x55d
/* 801C178C 001BE36C  48 18 3F 1D */	bl OSReport
/* 801C1790 001BE370  38 60 00 00 */	li r3, 0
/* 801C1794 001BE374  48 00 02 78 */	b lbl_801C1A0C
lbl_801C1798:
/* 801C1798 001BE378  80 1C 00 88 */	lwz r0, 0x88(r28)
/* 801C179C 001BE37C  1C 7E 00 14 */	mulli r3, r30, 0x14
/* 801C17A0 001BE380  54 00 10 3A */	slwi r0, r0, 2
/* 801C17A4 001BE384  7C 9B 02 14 */	add r4, r27, r0
/* 801C17A8 001BE388  80 84 00 34 */	lwz r4, 0x34(r4)
/* 801C17AC 001BE38C  38 03 00 10 */	addi r0, r3, 0x10
/* 801C17B0 001BE390  80 64 00 04 */	lwz r3, 4(r4)
/* 801C17B4 001BE394  7C 03 00 AE */	lbzx r0, r3, r0
/* 801C17B8 001BE398  54 00 DF FE */	rlwinm r0, r0, 0x1b, 0x1f, 0x1f
/* 801C17BC 001BE39C  28 00 00 01 */	cmplwi r0, 1
/* 801C17C0 001BE3A0  40 82 00 88 */	bne lbl_801C1848
/* 801C17C4 001BE3A4  80 7D 00 04 */	lwz r3, 4(r29)
/* 801C17C8 001BE3A8  80 03 00 08 */	lwz r0, 8(r3)
/* 801C17CC 001BE3AC  7C 60 CA 14 */	add r3, r0, r25
/* 801C17D0 001BE3B0  80 03 00 10 */	lwz r0, 0x10(r3)
/* 801C17D4 001BE3B4  28 00 00 00 */	cmplwi r0, 0
/* 801C17D8 001BE3B8  41 82 00 70 */	beq lbl_801C1848
/* 801C17DC 001BE3BC  38 60 00 11 */	li r3, 0x11
/* 801C17E0 001BE3C0  38 80 00 13 */	li r4, 0x13
/* 801C17E4 001BE3C4  38 A0 00 00 */	li r5, 0
/* 801C17E8 001BE3C8  48 1C EA 09 */	bl func_803901F0
/* 801C17EC 001BE3CC  80 9D 00 04 */	lwz r4, 4(r29)
/* 801C17F0 001BE3D0  7C 77 1B 78 */	mr r23, r3
/* 801C17F4 001BE3D4  80 04 00 08 */	lwz r0, 8(r4)
/* 801C17F8 001BE3D8  7C 60 CA 14 */	add r3, r0, r25
/* 801C17FC 001BE3DC  80 63 00 10 */	lwz r3, 0x10(r3)
/* 801C1800 001BE3E0  4B E5 23 15 */	bl func_80013B14
/* 801C1804 001BE3E4  3B 63 00 00 */	addi r27, r3, 0
/* 801C1808 001BE3E8  88 8D C1 AB */	lbz r4, lbl_804D784B
/* 801C180C 001BE3EC  38 77 00 00 */	addi r3, r23, 0
/* 801C1810 001BE3F0  38 BB 00 00 */	addi r5, r27, 0
/* 801C1814 001BE3F4  48 1C F2 5D */	bl func_80390A70
/* 801C1818 001BE3F8  3C 60 80 1C */	lis r3, lbl_801C5F60@ha
/* 801C181C 001BE3FC  38 83 5F 60 */	addi r4, r3, lbl_801C5F60@l
/* 801C1820 001BE400  38 77 00 00 */	addi r3, r23, 0
/* 801C1824 001BE404  38 A0 00 05 */	li r5, 5
/* 801C1828 001BE408  48 1C EF 35 */	bl GObj_SetupGXLinkMax
/* 801C182C 001BE40C  38 00 00 08 */	li r0, 8
/* 801C1830 001BE410  90 17 00 24 */	stw r0, 0x24(r23)
/* 801C1834 001BE414  38 00 00 00 */	li r0, 0
/* 801C1838 001BE418  38 7B 00 00 */	addi r3, r27, 0
/* 801C183C 001BE41C  90 17 00 20 */	stw r0, 0x20(r23)
/* 801C1840 001BE420  92 FA 00 18 */	stw r23, 0x18(r26)
/* 801C1844 001BE424  48 00 13 91 */	bl func_801C2BD4
lbl_801C1848:
/* 801C1848 001BE428  88 8D C1 A9 */	lbz r4, lbl_804D7849
/* 801C184C 001BE42C  38 7F 00 00 */	addi r3, r31, 0
/* 801C1850 001BE430  38 B8 00 00 */	addi r5, r24, 0
/* 801C1854 001BE434  48 1C F2 1D */	bl func_80390A70
/* 801C1858 001BE438  80 7D 00 04 */	lwz r3, 4(r29)
/* 801C185C 001BE43C  80 03 00 08 */	lwz r0, 8(r3)
/* 801C1860 001BE440  7C 60 CA 14 */	add r3, r0, r25
/* 801C1864 001BE444  83 03 00 30 */	lwz r24, 0x30(r3)
/* 801C1868 001BE448  82 E3 00 2C */	lwz r23, 0x2c(r3)
/* 801C186C 001BE44C  48 00 00 24 */	b lbl_801C1890
lbl_801C1870:
/* 801C1870 001BE450  7F E3 FB 78 */	mr r3, r31
/* 801C1874 001BE454  A8 97 00 00 */	lha r4, 0(r23)
/* 801C1878 001BE458  48 00 27 2D */	bl func_801C3FA4
/* 801C187C 001BE45C  28 03 00 00 */	cmplwi r3, 0
/* 801C1880 001BE460  41 82 00 08 */	beq lbl_801C1888
/* 801C1884 001BE464  4B E4 E1 75 */	bl func_8000F9F8
lbl_801C1888:
/* 801C1888 001BE468  3B 18 FF FF */	addi r24, r24, -1
/* 801C188C 001BE46C  3A F7 00 02 */	addi r23, r23, 2
lbl_801C1890:
/* 801C1890 001BE470  2C 18 00 00 */	cmpwi r24, 0
/* 801C1894 001BE474  40 82 FF DC */	bne lbl_801C1870
/* 801C1898 001BE478  48 00 01 3C */	b lbl_801C19D4
lbl_801C189C:
/* 801C189C 001BE47C  48 1B 08 71 */	bl HSD_JObjAlloc
/* 801C18A0 001BE480  7C 79 1B 79 */	or. r25, r3, r3
/* 801C18A4 001BE484  41 82 00 14 */	beq lbl_801C18B8
/* 801C18A8 001BE488  38 79 00 44 */	addi r3, r25, 0x44
/* 801C18AC 001BE48C  48 18 08 F9 */	bl PSMTXIdentity
/* 801C18B0 001BE490  38 00 00 00 */	li r0, 0
/* 801C18B4 001BE494  90 19 00 74 */	stw r0, 0x74(r25)
lbl_801C18B8:
/* 801C18B8 001BE498  80 7C 06 B0 */	lwz r3, 0x6b0(r28)
/* 801C18BC 001BE49C  28 03 00 00 */	cmplwi r3, 0
/* 801C18C0 001BE4A0  41 82 00 0C */	beq lbl_801C18CC
/* 801C18C4 001BE4A4  C0 03 00 00 */	lfs f0, 0(r3)
/* 801C18C8 001BE4A8  48 00 00 08 */	b lbl_801C18D0
lbl_801C18CC:
/* 801C18CC 001BE4AC  C0 02 B2 E4 */	lfs f0, 1.0f
lbl_801C18D0:
/* 801C18D0 001BE4B0  3C 60 80 3B */	lis r3, lbl_803B7E0C@ha
/* 801C18D4 001BE4B4  38 A3 7E 0C */	addi r5, r3, lbl_803B7E0C@l
/* 801C18D8 001BE4B8  80 85 00 00 */	lwz r4, 0(r5)
/* 801C18DC 001BE4BC  38 61 00 14 */	addi r3, r1, 0x14
/* 801C18E0 001BE4C0  80 05 00 04 */	lwz r0, 4(r5)
/* 801C18E4 001BE4C4  90 81 00 14 */	stw r4, 0x14(r1)
/* 801C18E8 001BE4C8  90 01 00 18 */	stw r0, 0x18(r1)
/* 801C18EC 001BE4CC  80 85 00 08 */	lwz r4, 8(r5)
/* 801C18F0 001BE4D0  80 05 00 0C */	lwz r0, 0xc(r5)
/* 801C18F4 001BE4D4  90 81 00 1C */	stw r4, 0x1c(r1)
/* 801C18F8 001BE4D8  90 01 00 20 */	stw r0, 0x20(r1)
/* 801C18FC 001BE4DC  80 85 00 10 */	lwz r4, 0x10(r5)
/* 801C1900 001BE4E0  80 05 00 14 */	lwz r0, 0x14(r5)
/* 801C1904 001BE4E4  90 81 00 24 */	stw r4, 0x24(r1)
/* 801C1908 001BE4E8  90 01 00 28 */	stw r0, 0x28(r1)
/* 801C190C 001BE4EC  80 85 00 18 */	lwz r4, 0x18(r5)
/* 801C1910 001BE4F0  80 05 00 1C */	lwz r0, 0x1c(r5)
/* 801C1914 001BE4F4  90 81 00 2C */	stw r4, 0x2c(r1)
/* 801C1918 001BE4F8  90 01 00 30 */	stw r0, 0x30(r1)
/* 801C191C 001BE4FC  80 85 00 20 */	lwz r4, 0x20(r5)
/* 801C1920 001BE500  80 05 00 24 */	lwz r0, 0x24(r5)
/* 801C1924 001BE504  90 81 00 34 */	stw r4, 0x34(r1)
/* 801C1928 001BE508  90 01 00 38 */	stw r0, 0x38(r1)
/* 801C192C 001BE50C  80 85 00 28 */	lwz r4, 0x28(r5)
/* 801C1930 001BE510  80 05 00 2C */	lwz r0, 0x2c(r5)
/* 801C1934 001BE514  90 81 00 3C */	stw r4, 0x3c(r1)
/* 801C1938 001BE518  90 01 00 40 */	stw r0, 0x40(r1)
/* 801C193C 001BE51C  80 85 00 30 */	lwz r4, 0x30(r5)
/* 801C1940 001BE520  80 05 00 34 */	lwz r0, 0x34(r5)
/* 801C1944 001BE524  90 81 00 44 */	stw r4, 0x44(r1)
/* 801C1948 001BE528  90 01 00 48 */	stw r0, 0x48(r1)
/* 801C194C 001BE52C  80 85 00 38 */	lwz r4, 0x38(r5)
/* 801C1950 001BE530  80 05 00 3C */	lwz r0, 0x3c(r5)
/* 801C1954 001BE534  90 81 00 4C */	stw r4, 0x4c(r1)
/* 801C1958 001BE538  90 01 00 50 */	stw r0, 0x50(r1)
/* 801C195C 001BE53C  D0 01 00 3C */	stfs f0, 0x3c(r1)
/* 801C1960 001BE540  D0 01 00 38 */	stfs f0, 0x38(r1)
/* 801C1964 001BE544  D0 01 00 34 */	stfs f0, 0x34(r1)
/* 801C1968 001BE548  48 1A F4 DD */	bl HSD_JObjLoadJoint
/* 801C196C 001BE54C  7C 77 1B 79 */	or. r23, r3, r3
/* 801C1970 001BE550  40 82 00 1C */	bne lbl_801C198C
/* 801C1974 001BE554  38 7B 02 34 */	addi r3, r27, 0x234
/* 801C1978 001BE558  4C C6 31 82 */	crclr 6
/* 801C197C 001BE55C  38 9B 02 18 */	addi r4, r27, 0x218
/* 801C1980 001BE560  38 A0 04 C4 */	li r5, 0x4c4
/* 801C1984 001BE564  48 18 3D 25 */	bl OSReport
lbl_801C1988:
/* 801C1988 001BE568  48 00 00 00 */	b lbl_801C1988
lbl_801C198C:
/* 801C198C 001BE56C  38 79 00 00 */	addi r3, r25, 0
/* 801C1990 001BE570  38 97 00 00 */	addi r4, r23, 0
/* 801C1994 001BE574  48 1B 00 71 */	bl HSD_JObjAddNext
/* 801C1998 001BE578  28 17 00 00 */	cmplwi r23, 0
/* 801C199C 001BE57C  40 82 00 28 */	bne lbl_801C19C4
/* 801C19A0 001BE580  7F E3 FB 78 */	mr r3, r31
/* 801C19A4 001BE584  48 1C E8 85 */	bl func_80390228
/* 801C19A8 001BE588  38 7B 02 34 */	addi r3, r27, 0x234
/* 801C19AC 001BE58C  4C C6 31 82 */	crclr 6
/* 801C19B0 001BE590  38 9B 02 18 */	addi r4, r27, 0x218
/* 801C19B4 001BE594  38 A0 05 98 */	li r5, 0x598
/* 801C19B8 001BE598  48 18 3C F1 */	bl OSReport
/* 801C19BC 001BE59C  38 60 00 00 */	li r3, 0
/* 801C19C0 001BE5A0  48 00 00 4C */	b lbl_801C1A0C
lbl_801C19C4:
/* 801C19C4 001BE5A4  88 8D C1 A9 */	lbz r4, lbl_804D7849
/* 801C19C8 001BE5A8  38 7F 00 00 */	addi r3, r31, 0
/* 801C19CC 001BE5AC  38 B7 00 00 */	addi r5, r23, 0
/* 801C19D0 001BE5B0  48 1C F0 A1 */	bl func_80390A70
lbl_801C19D4:
/* 801C19D4 001BE5B4  3C 60 80 1C */	lis r3, func_801C1CD0@ha
/* 801C19D8 001BE5B8  38 83 1C D0 */	addi r4, r3, func_801C1CD0@l
/* 801C19DC 001BE5BC  38 7F 00 00 */	addi r3, r31, 0
/* 801C19E0 001BE5C0  38 A0 00 01 */	li r5, 1
/* 801C19E4 001BE5C4  48 1C E3 71 */	bl func_8038FD54
/* 801C19E8 001BE5C8  3C 60 80 1C */	lis r3, func_801C1D38@ha
/* 801C19EC 001BE5CC  38 83 1D 38 */	addi r4, r3, func_801C1D38@l
/* 801C19F0 001BE5D0  38 7F 00 00 */	addi r3, r31, 0
/* 801C19F4 001BE5D4  38 A0 00 04 */	li r5, 4
/* 801C19F8 001BE5D8  48 1C E3 5D */	bl func_8038FD54
/* 801C19FC 001BE5DC  38 7F 00 00 */	addi r3, r31, 0
/* 801C1A00 001BE5E0  38 9E 00 00 */	addi r4, r30, 0
/* 801C1A04 001BE5E4  48 00 11 B9 */	bl func_801C2BBC
/* 801C1A08 001BE5E8  7F E3 FB 78 */	mr r3, r31
lbl_801C1A0C:
/* 801C1A0C 001BE5EC  BA E1 00 AC */	lmw r23, 0xac(r1)
/* 801C1A10 001BE5F0  80 01 00 D4 */	lwz r0, 0xd4(r1)
/* 801C1A14 001BE5F4  38 21 00 D0 */	addi r1, r1, 0xd0
/* 801C1A18 001BE5F8  7C 08 03 A6 */	mtlr r0
/* 801C1A1C 001BE5FC  4E 80 00 20 */	blr 
}
#pragma peephole on

char get_jobj[] = "%s:%d: couldn t get jobj\n";
char get_gobj[] = "%s:%d: couldn t get gobj!\n";

HSD_GObj* func_801C1A20(HSD_Joint* arg0, s32 arg1)
{
    HSD_GObj* temp_r30;
    HSD_JObj* temp_r29;
    HSD_JObj* temp_r3_4;
    void* temp_r3;
    f32 phi_f0;
    Map* gp;
    int i;
    u32 unused;
    HSD_Joint sp18;

    temp_r30 = func_803901F0(3, 5, 0);
    if (temp_r30 == NULL) {
        OSReport(get_gobj, __FILE__, 0x5B8);
        return NULL;
    }
    temp_r3 = HSD_MemAlloc(0x204);
    if (temp_r3 == NULL) {
        OSReport(get_userdata_ground, __FILE__, 0x1DA);
    }
    gp = temp_r3;

    if (gp == NULL) {
        func_80390228(temp_r30);
        return NULL;
    }
    GObj_InitUserData(temp_r30, 3, func_801C0478, gp);
    gp->map_id = arg1;
    gp->gobj = temp_r30;
    gp->x10_flags.b0 = 0;
    gp->x10_flags.b1 = 0;
    gp->x10_flags.b2 = 1;
    gp->x8_callback = NULL;
    gp->xC_callback = NULL;
    gp->x1C_callback = NULL;
    gp->x10_flags.b5 = 0;
    gp->x18 = NULL;
    gp->x10_flags.b3 = 0;
    for (i = 0; i < 8; i++) {
        gp->x20[i] = -1;
    }
    func_801C95C4(temp_r30);
    temp_r29 = HSD_JObjLoadJoint(arg0);
    func_801C34AC(arg1, temp_r29, arg0);
    phi_f0 = func_801C0498();
    sp18 = lbl_803B7E0C;
    sp18.scale.z = phi_f0;
    sp18.scale.y = phi_f0;
    sp18.scale.x = phi_f0;
    temp_r3_4 = HSD_JObjLoadJoint(&sp18);
    if (temp_r3_4 == NULL) {
        OSReport(get_jobj, __FILE__, 0x4C4);
        while (TRUE) {}
    }
    HSD_JObjAddNext(temp_r29, temp_r3_4);
    if (temp_r3_4 == NULL) {
        func_80390228(temp_r30);
        OSReport(get_jobj, __FILE__, 0x5E8);
        return NULL;
    }
    func_80390A70(temp_r30, lbl_804D7849, temp_r3_4);
    func_8038FD54(temp_r30, func_801C1CD0, 1);
    func_8038FD54(temp_r30, func_801C1D38, 4);
    return temp_r30;
}

extern s32 lbl_804D64AC;
static void func_801C1CD0(HSD_GObj* gobj)
{
    u32 unused[2];
    HSD_JObj* jobj = gobj->hsd_obj;
    Map* gp = gobj->user_data;
    HSD_JObjAnimAll(jobj);
    func_801C9698(gobj);
    lbl_804D64AC += 1;
    if (gp->x8_callback != NULL) {
        gp->x8_callback(gobj);
    }
}

static void func_801C1D38(HSD_GObj* gobj)
{
    Map* gp = gobj->user_data;
    if (gp->xC_callback != NULL) {
        gp->xC_callback(gobj);
    }
}

void func_801C1D6C(u32 arg0)
{
    stage_info.x84 |= arg0;
}

u32 func_801C1D84(void)
{
    return stage_info.x84 & 0x330;
}

u32 func_801C1D98(void)
{
    return stage_info.x84 & 0x20;
}

u32 func_801C1DAC(void)
{
    return stage_info.x84 & 0x100;
}

u32 func_801C1DC0(void)
{
    return stage_info.x84 & 0x80;
}

s16 func_801C1DD4(void)
{
    return stage_info.x6D0;
}

void func_801C1DE4(s32* arg0, s32* arg1)
{
    *arg0 = stage_info.x6D4;
    *arg1 = stage_info.x6D2;
}

void func_801C1E00(s32 arg0)
{
    stage_info.unk8C.b2 = arg0;
}

s32 func_801C1E18(void)
{
    return stage_info.unk8C.b2;
}

static void func_801C1E2C(HSD_GObj* gobj)
{
    u32 flag;
    HSD_JObj* jobj;
    if (func_80030A78()) {
        return;
    }
    flag = stage_info.unk8C.b2;
    if (!flag) {
        return;
    }
    jobj = gobj->hsd_obj;
    if (jobj != NULL) {
        HSD_FogSet(gobj->hsd_obj);
    }
}

void* func_801C1E84(void)
{
    return stage_info.x12C;
}

extern u8 lbl_804D7848;
extern void func_80030740();
extern void HSD_FogLoadDesc();
static asm void func_801C1E94(void)
{
    nofralloc
/* 801C1E94 001BEA74  7C 08 02 A6 */	mflr r0
/* 801C1E98 001BEA78  3C 60 80 4A */	lis r3, stage_info@ha
/* 801C1E9C 001BEA7C  90 01 00 04 */	stw r0, 4(r1)
/* 801C1EA0 001BEA80  94 21 FF E0 */	stwu r1, -0x20(r1)
/* 801C1EA4 001BEA84  93 E1 00 1C */	stw r31, 0x1c(r1)
/* 801C1EA8 001BEA88  3B E3 E6 C8 */	addi r31, r3, stage_info@l
/* 801C1EAC 001BEA8C  93 C1 00 18 */	stw r30, 0x18(r1)
/* 801C1EB0 001BEA90  93 A1 00 14 */	stw r29, 0x14(r1)
/* 801C1EB4 001BEA94  48 00 44 71 */	bl func_801C6324
/* 801C1EB8 001BEA98  48 00 44 6D */	bl func_801C6324
/* 801C1EBC 001BEA9C  80 BF 00 88 */	lwz r5, 0x88(r31)
/* 801C1EC0 001BEAA0  3C 80 80 3E */	lis r4, lbl_803DFEDC@ha
/* 801C1EC4 001BEAA4  80 63 00 04 */	lwz r3, 4(r3)
/* 801C1EC8 001BEAA8  38 04 FE DC */	addi r0, r4, lbl_803DFEDC@l
/* 801C1ECC 001BEAAC  54 A4 10 3A */	slwi r4, r5, 2
/* 801C1ED0 001BEAB0  7C 80 22 14 */	add r4, r0, r4
/* 801C1ED4 001BEAB4  83 C3 00 0C */	lwz r30, 0xc(r3)
/* 801C1ED8 001BEAB8  80 64 00 00 */	lwz r3, 0(r4)
/* 801C1EDC 001BEABC  83 A3 00 04 */	lwz r29, 4(r3)
/* 801C1EE0 001BEAC0  48 00 44 45 */	bl func_801C6324
/* 801C1EE4 001BEAC4  2C 1E 00 00 */	cmpwi r30, 0
/* 801C1EE8 001BEAC8  7F C9 03 A6 */	mtctr r30
/* 801C1EEC 001BEACC  3B C0 00 00 */	li r30, 0
/* 801C1EF0 001BEAD0  40 81 00 40 */	ble lbl_801C1F30
lbl_801C1EF4:
/* 801C1EF4 001BEAD4  88 1D 00 10 */	lbz r0, 0x10(r29)
/* 801C1EF8 001BEAD8  54 00 D7 FE */	rlwinm r0, r0, 0x1a, 0x1f, 0x1f
/* 801C1EFC 001BEADC  28 00 00 01 */	cmplwi r0, 1
/* 801C1F00 001BEAE0  40 82 00 24 */	bne lbl_801C1F24
/* 801C1F04 001BEAE4  7F C3 F3 78 */	mr r3, r30
/* 801C1F08 001BEAE8  48 00 44 29 */	bl func_801C6330
/* 801C1F0C 001BEAEC  80 63 00 04 */	lwz r3, 4(r3)
/* 801C1F10 001BEAF0  1C 1E 00 34 */	mulli r0, r30, 0x34
/* 801C1F14 001BEAF4  80 63 00 08 */	lwz r3, 8(r3)
/* 801C1F18 001BEAF8  7C 63 02 14 */	add r3, r3, r0
/* 801C1F1C 001BEAFC  80 03 00 1C */	lwz r0, 0x1c(r3)
/* 801C1F20 001BEB00  48 00 00 14 */	b lbl_801C1F34
lbl_801C1F24:
/* 801C1F24 001BEB04  3B BD 00 14 */	addi r29, r29, 0x14
/* 801C1F28 001BEB08  3B DE 00 01 */	addi r30, r30, 1
/* 801C1F2C 001BEB0C  42 00 FF C8 */	bdnz lbl_801C1EF4
lbl_801C1F30:
/* 801C1F30 001BEB10  38 00 00 00 */	li r0, 0
lbl_801C1F34:
/* 801C1F34 001BEB14  28 00 00 00 */	cmplwi r0, 0
/* 801C1F38 001BEB18  7C 1D 03 78 */	mr r29, r0
/* 801C1F3C 001BEB1C  41 82 00 94 */	beq lbl_801C1FD0
/* 801C1F40 001BEB20  38 60 00 0A */	li r3, 0xa
/* 801C1F44 001BEB24  38 80 00 0B */	li r4, 0xb
/* 801C1F48 001BEB28  38 A0 00 00 */	li r5, 0
/* 801C1F4C 001BEB2C  48 1C E2 A5 */	bl func_803901F0
/* 801C1F50 001BEB30  3B C3 00 00 */	addi r30, r3, 0
/* 801C1F54 001BEB34  38 7D 00 00 */	addi r3, r29, 0
/* 801C1F58 001BEB38  48 1B BC E1 */	bl HSD_FogLoadDesc
/* 801C1F5C 001BEB3C  3B A3 00 00 */	addi r29, r3, 0
/* 801C1F60 001BEB40  88 8D C1 A8 */	lbz r4, lbl_804D7848
/* 801C1F64 001BEB44  38 7E 00 00 */	addi r3, r30, 0
/* 801C1F68 001BEB48  38 BD 00 00 */	addi r5, r29, 0
/* 801C1F6C 001BEB4C  48 1C EB 05 */	bl func_80390A70
/* 801C1F70 001BEB50  3C 60 80 1C */	lis r3, func_801C1E2C@ha
/* 801C1F74 001BEB54  38 83 1E 2C */	addi r4, r3, func_801C1E2C@l
/* 801C1F78 001BEB58  38 7E 00 00 */	addi r3, r30, 0
/* 801C1F7C 001BEB5C  38 A0 00 00 */	li r5, 0
/* 801C1F80 001BEB60  38 C0 00 00 */	li r6, 0
/* 801C1F84 001BEB64  48 1C E7 19 */	bl GObj_SetupGXLink
/* 801C1F88 001BEB68  80 7F 06 B0 */	lwz r3, 0x6b0(r31)
/* 801C1F8C 001BEB6C  28 03 00 00 */	cmplwi r3, 0
/* 801C1F90 001BEB70  41 82 00 0C */	beq lbl_801C1F9C
/* 801C1F94 001BEB74  C0 23 00 00 */	lfs f1, 0(r3)
/* 801C1F98 001BEB78  48 00 00 08 */	b lbl_801C1FA0
lbl_801C1F9C:
/* 801C1F9C 001BEB7C  C0 22 B2 E4 */	lfs f1, 1.0f
lbl_801C1FA0:
/* 801C1FA0 001BEB80  C0 1D 00 10 */	lfs f0, 0x10(r29)
/* 801C1FA4 001BEB84  EC 00 00 72 */	fmuls f0, f0, f1
/* 801C1FA8 001BEB88  D0 1D 00 10 */	stfs f0, 0x10(r29)
/* 801C1FAC 001BEB8C  C0 1D 00 14 */	lfs f0, 0x14(r29)
/* 801C1FB0 001BEB90  EC 00 00 72 */	fmuls f0, f0, f1
/* 801C1FB4 001BEB94  D0 1D 00 14 */	stfs f0, 0x14(r29)
/* 801C1FB8 001BEB98  88 7D 00 18 */	lbz r3, 0x18(r29)
/* 801C1FBC 001BEB9C  88 9D 00 19 */	lbz r4, 0x19(r29)
/* 801C1FC0 001BEBA0  88 BD 00 1A */	lbz r5, 0x1a(r29)
/* 801C1FC4 001BEBA4  4B E6 E7 7D */	bl func_80030740
/* 801C1FC8 001BEBA8  93 DF 01 2C */	stw r30, 0x12c(r31)
/* 801C1FCC 001BEBAC  48 00 00 14 */	b lbl_801C1FE0
lbl_801C1FD0:
/* 801C1FD0 001BEBB0  38 60 00 00 */	li r3, 0
/* 801C1FD4 001BEBB4  38 80 00 00 */	li r4, 0
/* 801C1FD8 001BEBB8  38 A0 00 00 */	li r5, 0
/* 801C1FDC 001BEBBC  4B E6 E7 65 */	bl func_80030740
lbl_801C1FE0:
/* 801C1FE0 001BEBC0  80 01 00 24 */	lwz r0, 0x24(r1)
/* 801C1FE4 001BEBC4  83 E1 00 1C */	lwz r31, 0x1c(r1)
/* 801C1FE8 001BEBC8  83 C1 00 18 */	lwz r30, 0x18(r1)
/* 801C1FEC 001BEBCC  83 A1 00 14 */	lwz r29, 0x14(r1)
/* 801C1FF0 001BEBD0  38 21 00 20 */	addi r1, r1, 0x20
/* 801C1FF4 001BEBD4  7C 08 03 A6 */	mtlr r0
/* 801C1FF8 001BEBD8  4E 80 00 20 */	blr 
}
#pragma peephole on

void func_801C1FFC(void)
{
    if (stage_info.x12C != NULL && stage_info.x12C->ptr != NULL) {
        func_80030740(stage_info.x12C->ptr->color.r,
                      stage_info.x12C->ptr->color.g,
                      stage_info.x12C->ptr->color.b);
    } else {
        func_80030740(0, 0, 0);
    }
}

void func_801C205C(GXColor* color)
{
    if (stage_info.x12C != NULL && color != NULL && stage_info.x12C->ptr != NULL) {
        stage_info.x12C->ptr->color = *color;
    }
}

BOOL func_801C2090(GXColor* color)
{
    if (stage_info.x12C != NULL && color != NULL && stage_info.x12C->ptr != NULL) {
        *color = stage_info.x12C->ptr->color;
        return TRUE;
    }
    return FALSE;
}

f32 func_801C20D0(void)
{
    return stage_info.cam_info.cam_vertical_tilt;
}

// TODO attempt decomp once param types are known
char lightset[9] = "lightset";
char plightset[10] = "*lightset";
static asm void* func_801C20E0()
{
    nofralloc
/* 801C20E0 001BECC0  7C 08 02 A6 */	mflr r0
/* 801C20E4 001BECC4  90 01 00 04 */	stw r0, 4(r1)
/* 801C20E8 001BECC8  94 21 FF D8 */	stwu r1, -0x28(r1)
/* 801C20EC 001BECCC  BF 41 00 10 */	stmw r26, 0x10(r1)
/* 801C20F0 001BECD0  7C 9C 23 79 */	or. r28, r4, r4
/* 801C20F4 001BECD4  3C 80 80 3E */	lis r4, lbl_803DFEA8@ha
/* 801C20F8 001BECD8  3B 63 00 00 */	addi r27, r3, 0
/* 801C20FC 001BECDC  3B 44 FE A8 */	addi r26, r4, lbl_803DFEA8@l
/* 801C2100 001BECE0  40 82 00 14 */	bne lbl_801C2114
/* 801C2104 001BECE4  38 7A 02 18 */	addi r3, r26, 0x218
/* 801C2108 001BECE8  38 BA 02 6C */	addi r5, r26, 0x26c
/* 801C210C 001BECEC  38 80 07 73 */	li r4, 0x773
/* 801C2110 001BECF0  48 1C 61 11 */	bl __assert
lbl_801C2114:
/* 801C2114 001BECF4  80 1C 00 00 */	lwz r0, 0(r28)
/* 801C2118 001BECF8  28 00 00 00 */	cmplwi r0, 0
/* 801C211C 001BECFC  40 82 00 14 */	bne lbl_801C2130
/* 801C2120 001BED00  38 7A 02 18 */	addi r3, r26, 0x218
/* 801C2124 001BED04  38 BA 02 78 */	addi r5, r26, 0x278
/* 801C2128 001BED08  38 80 07 74 */	li r4, 0x774
/* 801C212C 001BED0C  48 1C 60 F5 */	bl __assert
lbl_801C2130:
/* 801C2130 001BED10  39 1C 00 00 */	addi r8, r28, 0
/* 801C2134 001BED14  39 20 00 00 */	li r9, 0
/* 801C2138 001BED18  48 00 00 A0 */	b lbl_801C21D8
lbl_801C213C:
/* 801C213C 001BED1C  80 DB 00 04 */	lwz r6, 4(r27)
/* 801C2140 001BED20  80 83 00 00 */	lwz r4, 0(r3)
/* 801C2144 001BED24  80 06 00 1C */	lwz r0, 0x1c(r6)
/* 801C2148 001BED28  2C 00 00 00 */	cmpwi r0, 0
/* 801C214C 001BED2C  41 82 00 5C */	beq lbl_801C21A8
/* 801C2150 001BED30  38 60 00 00 */	li r3, 0
/* 801C2154 001BED34  7C 09 03 A6 */	mtctr r0
/* 801C2158 001BED38  38 A3 00 00 */	addi r5, r3, 0
/* 801C215C 001BED3C  40 81 00 4C */	ble lbl_801C21A8
lbl_801C2160:
/* 801C2160 001BED40  80 E6 00 18 */	lwz r7, 0x18(r6)
/* 801C2164 001BED44  7C 07 28 2E */	lwzx r0, r7, r5
/* 801C2168 001BED48  7C 00 20 40 */	cmplw r0, r4
/* 801C216C 001BED4C  40 82 00 30 */	bne lbl_801C219C
/* 801C2170 001BED50  54 63 18 38 */	slwi r3, r3, 3
/* 801C2174 001BED54  38 63 00 04 */	addi r3, r3, 4
/* 801C2178 001BED58  7C 67 1A 14 */	add r3, r7, r3
/* 801C217C 001BED5C  8B E3 00 00 */	lbz r31, 0(r3)
/* 801C2180 001BED60  38 00 00 01 */	li r0, 1
/* 801C2184 001BED64  8B C3 00 00 */	lbz r30, 0(r3)
/* 801C2188 001BED68  8B A3 00 00 */	lbz r29, 0(r3)
/* 801C218C 001BED6C  57 FF D7 FE */	rlwinm r31, r31, 0x1a, 0x1f, 0x1f
/* 801C2190 001BED70  57 DE CF FE */	rlwinm r30, r30, 0x19, 0x1f, 0x1f
/* 801C2194 001BED74  57 BD DF FE */	rlwinm r29, r29, 0x1b, 0x1f, 0x1f
/* 801C2198 001BED78  48 00 00 14 */	b lbl_801C21AC
lbl_801C219C:
/* 801C219C 001BED7C  38 A5 00 08 */	addi r5, r5, 8
/* 801C21A0 001BED80  38 63 00 01 */	addi r3, r3, 1
/* 801C21A4 001BED84  42 00 FF BC */	bdnz lbl_801C2160
lbl_801C21A8:
/* 801C21A8 001BED88  38 00 00 00 */	li r0, 0
lbl_801C21AC:
/* 801C21AC 001BED8C  2C 00 00 00 */	cmpwi r0, 0
/* 801C21B0 001BED90  41 82 00 24 */	beq lbl_801C21D4
/* 801C21B4 001BED94  2C 1F 00 00 */	cmpwi r31, 0
/* 801C21B8 001BED98  40 82 00 14 */	bne lbl_801C21CC
/* 801C21BC 001BED9C  2C 1E 00 00 */	cmpwi r30, 0
/* 801C21C0 001BEDA0  40 82 00 0C */	bne lbl_801C21CC
/* 801C21C4 001BEDA4  2C 1D 00 00 */	cmpwi r29, 0
/* 801C21C8 001BEDA8  41 82 00 0C */	beq lbl_801C21D4
lbl_801C21CC:
/* 801C21CC 001BEDAC  39 20 00 01 */	li r9, 1
/* 801C21D0 001BEDB0  48 00 00 14 */	b lbl_801C21E4
lbl_801C21D4:
/* 801C21D4 001BEDB4  39 08 00 04 */	addi r8, r8, 4
lbl_801C21D8:
/* 801C21D8 001BEDB8  80 68 00 00 */	lwz r3, 0(r8)
/* 801C21DC 001BEDBC  28 03 00 00 */	cmplwi r3, 0
/* 801C21E0 001BEDC0  40 82 FF 5C */	bne lbl_801C213C
lbl_801C21E4:
/* 801C21E4 001BEDC4  2C 09 00 00 */	cmpwi r9, 0
/* 801C21E8 001BEDC8  40 82 00 0C */	bne lbl_801C21F4
/* 801C21EC 001BEDCC  7F 83 E3 78 */	mr r3, r28
/* 801C21F0 001BEDD0  48 00 01 70 */	b lbl_801C2360
lbl_801C21F4:
/* 801C21F4 001BEDD4  7F 83 E3 78 */	mr r3, r28
/* 801C21F8 001BEDD8  48 00 01 58 */	b lbl_801C2350
lbl_801C21FC:
/* 801C21FC 001BEDDC  80 C4 00 00 */	lwz r6, 0(r4)
/* 801C2200 001BEDE0  A0 06 00 08 */	lhz r0, 8(r6)
/* 801C2204 001BEDE4  39 26 00 08 */	addi r9, r6, 8
/* 801C2208 001BEDE8  54 00 07 BF */	clrlwi. r0, r0, 0x1e
/* 801C220C 001BEDEC  41 82 01 40 */	beq lbl_801C234C
/* 801C2210 001BEDF0  80 FB 00 04 */	lwz r7, 4(r27)
/* 801C2214 001BEDF4  80 07 00 1C */	lwz r0, 0x1c(r7)
/* 801C2218 001BEDF8  2C 00 00 00 */	cmpwi r0, 0
/* 801C221C 001BEDFC  41 82 00 5C */	beq lbl_801C2278
/* 801C2220 001BEE00  38 80 00 00 */	li r4, 0
/* 801C2224 001BEE04  7C 09 03 A6 */	mtctr r0
/* 801C2228 001BEE08  38 A4 00 00 */	addi r5, r4, 0
/* 801C222C 001BEE0C  40 81 00 4C */	ble lbl_801C2278
lbl_801C2230:
/* 801C2230 001BEE10  81 07 00 18 */	lwz r8, 0x18(r7)
/* 801C2234 001BEE14  7C 08 28 2E */	lwzx r0, r8, r5
/* 801C2238 001BEE18  7C 00 30 40 */	cmplw r0, r6
/* 801C223C 001BEE1C  40 82 00 30 */	bne lbl_801C226C
/* 801C2240 001BEE20  54 84 18 38 */	slwi r4, r4, 3
/* 801C2244 001BEE24  38 84 00 04 */	addi r4, r4, 4
/* 801C2248 001BEE28  7C 88 22 14 */	add r4, r8, r4
/* 801C224C 001BEE2C  8B E4 00 00 */	lbz r31, 0(r4)
/* 801C2250 001BEE30  38 00 00 01 */	li r0, 1
/* 801C2254 001BEE34  8B C4 00 00 */	lbz r30, 0(r4)
/* 801C2258 001BEE38  8B A4 00 00 */	lbz r29, 0(r4)
/* 801C225C 001BEE3C  57 FF D7 FE */	rlwinm r31, r31, 0x1a, 0x1f, 0x1f
/* 801C2260 001BEE40  57 DE CF FE */	rlwinm r30, r30, 0x19, 0x1f, 0x1f
/* 801C2264 001BEE44  57 BD DF FE */	rlwinm r29, r29, 0x1b, 0x1f, 0x1f
/* 801C2268 001BEE48  48 00 00 14 */	b lbl_801C227C
lbl_801C226C:
/* 801C226C 001BEE4C  38 A5 00 08 */	addi r5, r5, 8
/* 801C2270 001BEE50  38 84 00 01 */	addi r4, r4, 1
/* 801C2274 001BEE54  42 00 FF BC */	bdnz lbl_801C2230
lbl_801C2278:
/* 801C2278 001BEE58  38 00 00 00 */	li r0, 0
lbl_801C227C:
/* 801C227C 001BEE5C  2C 00 00 00 */	cmpwi r0, 0
/* 801C2280 001BEE60  41 82 00 1C */	beq lbl_801C229C
/* 801C2284 001BEE64  2C 1F 00 00 */	cmpwi r31, 0
/* 801C2288 001BEE68  40 82 00 38 */	bne lbl_801C22C0
/* 801C228C 001BEE6C  2C 1E 00 00 */	cmpwi r30, 0
/* 801C2290 001BEE70  40 82 00 30 */	bne lbl_801C22C0
/* 801C2294 001BEE74  2C 1D 00 00 */	cmpwi r29, 0
/* 801C2298 001BEE78  40 82 00 28 */	bne lbl_801C22C0
lbl_801C229C:
/* 801C229C 001BEE7C  7C 64 1B 78 */	mr r4, r3
lbl_801C22A0:
/* 801C22A0 001BEE80  80 04 00 04 */	lwz r0, 4(r4)
/* 801C22A4 001BEE84  28 00 00 00 */	cmplwi r0, 0
/* 801C22A8 001BEE88  90 04 00 00 */	stw r0, 0(r4)
/* 801C22AC 001BEE8C  41 82 00 0C */	beq lbl_801C22B8
/* 801C22B0 001BEE90  38 84 00 04 */	addi r4, r4, 4
/* 801C22B4 001BEE94  4B FF FF EC */	b lbl_801C22A0
lbl_801C22B8:
/* 801C22B8 001BEE98  38 63 FF FC */	addi r3, r3, -4
/* 801C22BC 001BEE9C  48 00 00 90 */	b lbl_801C234C
lbl_801C22C0:
/* 801C22C0 001BEEA0  2C 1F 00 00 */	cmpwi r31, 0
/* 801C22C4 001BEEA4  41 82 00 14 */	beq lbl_801C22D8
/* 801C22C8 001BEEA8  A0 09 00 00 */	lhz r0, 0(r9)
/* 801C22CC 001BEEAC  60 00 00 04 */	ori r0, r0, 4
/* 801C22D0 001BEEB0  B0 09 00 00 */	sth r0, 0(r9)
/* 801C22D4 001BEEB4  48 00 00 10 */	b lbl_801C22E4
lbl_801C22D8:
/* 801C22D8 001BEEB8  A0 09 00 00 */	lhz r0, 0(r9)
/* 801C22DC 001BEEBC  54 00 07 B8 */	rlwinm r0, r0, 0, 0x1e, 0x1c
/* 801C22E0 001BEEC0  B0 09 00 00 */	sth r0, 0(r9)
lbl_801C22E4:
/* 801C22E4 001BEEC4  2C 1E 00 00 */	cmpwi r30, 0
/* 801C22E8 001BEEC8  41 82 00 1C */	beq lbl_801C2304
/* 801C22EC 001BEECC  80 83 00 00 */	lwz r4, 0(r3)
/* 801C22F0 001BEED0  80 84 00 00 */	lwz r4, 0(r4)
/* 801C22F4 001BEED4  A0 04 00 08 */	lhz r0, 8(r4)
/* 801C22F8 001BEED8  60 00 00 08 */	ori r0, r0, 8
/* 801C22FC 001BEEDC  B0 04 00 08 */	sth r0, 8(r4)
/* 801C2300 001BEEE0  48 00 00 18 */	b lbl_801C2318
lbl_801C2304:
/* 801C2304 001BEEE4  80 83 00 00 */	lwz r4, 0(r3)
/* 801C2308 001BEEE8  80 84 00 00 */	lwz r4, 0(r4)
/* 801C230C 001BEEEC  A0 04 00 08 */	lhz r0, 8(r4)
/* 801C2310 001BEEF0  54 00 07 76 */	rlwinm r0, r0, 0, 0x1d, 0x1b
/* 801C2314 001BEEF4  B0 04 00 08 */	sth r0, 8(r4)
lbl_801C2318:
/* 801C2318 001BEEF8  2C 1D 00 00 */	cmpwi r29, 0
/* 801C231C 001BEEFC  41 82 00 1C */	beq lbl_801C2338
/* 801C2320 001BEF00  80 83 00 00 */	lwz r4, 0(r3)
/* 801C2324 001BEF04  80 84 00 00 */	lwz r4, 0(r4)
/* 801C2328 001BEF08  A0 04 00 08 */	lhz r0, 8(r4)
/* 801C232C 001BEF0C  60 00 04 00 */	ori r0, r0, 0x400
/* 801C2330 001BEF10  B0 04 00 08 */	sth r0, 8(r4)
/* 801C2334 001BEF14  48 00 00 18 */	b lbl_801C234C
lbl_801C2338:
/* 801C2338 001BEF18  80 83 00 00 */	lwz r4, 0(r3)
/* 801C233C 001BEF1C  80 84 00 00 */	lwz r4, 0(r4)
/* 801C2340 001BEF20  A0 04 00 08 */	lhz r0, 8(r4)
/* 801C2344 001BEF24  54 00 05 A8 */	rlwinm r0, r0, 0, 0x16, 0x14
/* 801C2348 001BEF28  B0 04 00 08 */	sth r0, 8(r4)
lbl_801C234C:
/* 801C234C 001BEF2C  38 63 00 04 */	addi r3, r3, 4
lbl_801C2350:
/* 801C2350 001BEF30  80 83 00 00 */	lwz r4, 0(r3)
/* 801C2354 001BEF34  28 04 00 00 */	cmplwi r4, 0
/* 801C2358 001BEF38  40 82 FE A4 */	bne lbl_801C21FC
/* 801C235C 001BEF3C  7F 83 E3 78 */	mr r3, r28
lbl_801C2360:
/* 801C2360 001BEF40  BB 41 00 10 */	lmw r26, 0x10(r1)
/* 801C2364 001BEF44  80 01 00 2C */	lwz r0, 0x2c(r1)
/* 801C2368 001BEF48  38 21 00 28 */	addi r1, r1, 0x28
/* 801C236C 001BEF4C  7C 08 03 A6 */	mtlr r0
/* 801C2370 001BEF50  4E 80 00 20 */	blr 
}
#pragma peephole on

#include <sysdolphin/baselib/lobj.h>

void func_801C2374(HSD_LObj* lobj)
{
    Vec3 sp10;
    Vec3* vtmp;
    HSD_LObj* cur;
    f32 phi_f31;

    cur = lobj;
    phi_f31 = func_801C0498();
    while (cur != NULL) {
        if (HSD_LObjGetPosition(cur, &sp10)) {
            vtmp = &sp10;
            sp10.x *= phi_f31;
            sp10.y *= phi_f31;
            sp10.z *= phi_f31;
            HSD_LObjSetPosition(cur, vtmp);
        }
        if (HSD_LObjGetInterest(cur, &sp10)) {
            vtmp = &sp10;
            sp10.x *= phi_f31;
            sp10.y *= phi_f31;
            sp10.z *= phi_f31;
            HSD_LObjSetInterest(cur, vtmp);
        }
        cur = cur == NULL ? NULL : cur->next;
    }
}

s32 func_801C247C(s32 arg0, s32 arg1)
{
    UnkArchiveStruct* archive = func_801C6330(arg0);
    if (archive == NULL) {
        __assert(__FILE__, 0x7E1, lbl_804D44F8);
    }
    if (archive->unk4 != NULL && arg1 < archive->unk4->unk14) {
        return archive->unk4->unk10[arg1];
    } else {
        return 0;
    }
}

extern s32 func_8002305C(s32, s32);
extern BOOL func_80164600(void);
extern BOOL func_80164ABC(void);
extern BOOL func_803048C0(s32);

static const int BGM_Undefined = -1;

static BOOL func_801C24F8(s32 arg0, u32 arg1, s32* arg2) {
    s32 temp_r25;
    UnkBgmStruct* phi_r30;
    UnkBgmStruct* phi_r30_0;
    s32 i;
    s32 bgm;
    BOOL result;

    phi_r30_0 = stage_info.x6B0->xB0;
    bgm = -1;
    result = FALSE;
    for (i = 0; i < stage_info.x6B0->xB4; i++) {
        phi_r30 = &phi_r30_0[i];
        if (phi_r30->x0 == arg0) {
            if (arg1 & 4) {
                temp_r25 = arg1 & 0x40;
                switch (phi_r30->x14) {
                case 0:
                    if (temp_r25) {
                        arg1 |= 2;
                    } else {
                        arg1 |= 1;
                    }
                    break;
                case 1:
                    if (HSD_Randi(0xC) == 0 || temp_r25) {
                        arg1 |= 2;
                    } else {
                        arg1 |= 1;
                    }
                    break;
                case 8:
                    arg1 |= 1;
                    break;
                case 2:
                    if (phi_r30->x16 > HSD_Randi(0x64) || temp_r25) {
                        arg1 |= 2;
                    } else {
                        arg1 |= 1;
                    }
                    break;
                case 3:
                    if (func_80164840(9) && (phi_r30->x16 > HSD_Randi(0x64) || temp_r25)) {
                        arg1 |= 2;
                    } else {
                        arg1 |= 1;
                    }
                    break;
                case 4:
                    if (func_80164840(21) && (phi_r30->x16 > HSD_Randi(0x64) || temp_r25)) {
                        arg1 |= 2;
                    } else {
                        arg1 |= 1;
                    }
                    break;
                case 5:
                    if (func_803048C0(0x11A) && (phi_r30->x16 > HSD_Randi(0x64) || temp_r25)) {
                        arg1 |= 2;
                    } else {
                        arg1 |= 1;
                    }
                    break;
                case 6:
                    if (func_80164ABC() && (phi_r30->x16 > HSD_Randi(0x64) || temp_r25)) {
                        arg1 |= 2;
                    } else {
                        arg1 |= 1;
                    }
                    break;
                case 7:
                    if (func_80164600() && (phi_r30->x16 > HSD_Randi(0x64) || temp_r25)) {
                        arg1 |= 2;
                    } else {
                        arg1 |= 1;
                    }
                    break;
                }
            }
            if (arg1 & 0x10) {
                stage_info.unk8C.b0 = 0;
                if (arg1 & 1) {
                    bgm = phi_r30->xC;
                } else if (arg1 & 2) {
                    if (phi_r30->x10 != -1) {
                        bgm = phi_r30->x10;
                        result = TRUE;
                    } else {
                        bgm = phi_r30->xC;
                    }
                }
            } else if (arg1 & 0x20) {
                if (arg1 & 1) {
                    bgm = phi_r30->xC;
                    stage_info.unk8C.b0 = 0;
                } else if (arg1 & 2) {
                    if (phi_r30->x10 != -1U) {
                        bgm = phi_r30->x10;
                        stage_info.unk8C.b0 = 1;
                        result = TRUE;
                    } else {
                        bgm = phi_r30->xC;
                        stage_info.unk8C.b0 = 0;
                    }
                }
            } else if (arg1 & 1) {
                bgm = phi_r30->x4;
                stage_info.unk8C.b0 = 0;
            } else if (arg1 & 2) {
                if (phi_r30->x8 != -1U) {
                    bgm = phi_r30->x8;
                    stage_info.unk8C.b0 = 1;
                    result = TRUE;
                } else {
                    bgm = phi_r30->x4;
                    stage_info.unk8C.b0 = 0;
                }
            }
            break;
        }
    }
    assert_line(2242, bgm!=BGM_Undefined);
    if (bgm == -2) {
        *arg2 = func_8002305C(Player_GetPlayerCharacter(0), HSD_Randi(2));
    } else {
        *arg2 = bgm;
    }
    return result;
}

BOOL func_801C28AC(s32 arg0, u32 arg1, s32* arg2)
{
    return func_801C24F8(arg0, arg1, arg2);
}

char str1[] = "%s:%d: not found stage param in DAT(grkind=%d stkind=%d,num=%d)\n";
char str2[] = "             check StageParam.csv or StageItem.csv, stdata.c\n";
char str3[] = " stageid=%d\n";
static asm void func_801C28CC(void*, s32)
{
    nofralloc
/* 801C28CC 001BF4AC  7C 08 02 A6 */	mflr r0
/* 801C28D0 001BF4B0  3C A0 80 4A */	lis r5, stage_info@ha
/* 801C28D4 001BF4B4  90 01 00 04 */	stw r0, 4(r1)
/* 801C28D8 001BF4B8  38 A5 E6 C8 */	addi r5, r5, stage_info@l
/* 801C28DC 001BF4BC  94 21 FF D0 */	stwu r1, -0x30(r1)
/* 801C28E0 001BF4C0  BF 61 00 1C */	stmw r27, 0x1c(r1)
/* 801C28E4 001BF4C4  3B E5 06 B0 */	addi r31, r5, 0x6b0
/* 801C28E8 001BF4C8  80 C5 06 B0 */	lwz r6, 0x6b0(r5)
/* 801C28EC 001BF4CC  3C A0 80 3E */	lis r5, lbl_803DFEA8@ha
/* 801C28F0 001BF4D0  3B 85 FE A8 */	addi r28, r5, lbl_803DFEA8@l
/* 801C28F4 001BF4D4  83 66 00 B4 */	lwz r27, 0xb4(r6)
/* 801C28F8 001BF4D8  80 E6 00 B0 */	lwz r7, 0xb0(r6)
/* 801C28FC 001BF4DC  2C 1B 00 00 */	cmpwi r27, 0
/* 801C2900 001BF4E0  7F 69 03 A6 */	mtctr r27
/* 801C2904 001BF4E4  40 81 01 44 */	ble lbl_801C2A48
lbl_801C2908:
/* 801C2908 001BF4E8  80 07 00 00 */	lwz r0, 0(r7)
/* 801C290C 001BF4EC  7C 00 20 00 */	cmpw r0, r4
/* 801C2910 001BF4F0  40 82 01 30 */	bne lbl_801C2A40
/* 801C2914 001BF4F4  38 00 00 04 */	li r0, 4
/* 801C2918 001BF4F8  7C 09 03 A6 */	mtctr r0
/* 801C291C 001BF4FC  38 87 00 00 */	addi r4, r7, 0
/* 801C2920 001BF500  38 C3 00 00 */	addi r6, r3, 0
/* 801C2924 001BF504  39 00 00 00 */	li r8, 0
/* 801C2928 001BF508  38 A0 00 00 */	li r5, 0
lbl_801C292C:
/* 801C292C 001BF50C  81 7F 00 00 */	lwz r11, 0(r31)
/* 801C2930 001BF510  39 45 00 6A */	addi r10, r5, 0x6a
/* 801C2934 001BF514  A8 04 00 1A */	lha r0, 0x1a(r4)
/* 801C2938 001BF518  39 25 00 6C */	addi r9, r5, 0x6c
/* 801C293C 001BF51C  7D 4B 52 AE */	lhax r10, r11, r10
/* 801C2940 001BF520  3B A5 00 6E */	addi r29, r5, 0x6e
/* 801C2944 001BF524  7C 0A 01 D6 */	mullw r0, r10, r0
/* 801C2948 001BF528  90 06 00 00 */	stw r0, 0(r6)
/* 801C294C 001BF52C  3B C5 00 70 */	addi r30, r5, 0x70
/* 801C2950 001BF530  39 85 00 72 */	addi r12, r5, 0x72
/* 801C2954 001BF534  83 9F 00 00 */	lwz r28, 0(r31)
/* 801C2958 001BF538  39 65 00 74 */	addi r11, r5, 0x74
/* 801C295C 001BF53C  A8 04 00 1C */	lha r0, 0x1c(r4)
/* 801C2960 001BF540  39 45 00 76 */	addi r10, r5, 0x76
/* 801C2964 001BF544  7F 9C 4A AE */	lhax r28, r28, r9
/* 801C2968 001BF548  39 25 00 78 */	addi r9, r5, 0x78
/* 801C296C 001BF54C  7C 1C 01 D6 */	mullw r0, r28, r0
/* 801C2970 001BF550  90 06 00 04 */	stw r0, 4(r6)
/* 801C2974 001BF554  38 A5 00 10 */	addi r5, r5, 0x10
/* 801C2978 001BF558  39 08 00 08 */	addi r8, r8, 8
/* 801C297C 001BF55C  83 9F 00 00 */	lwz r28, 0(r31)
/* 801C2980 001BF560  A8 04 00 1E */	lha r0, 0x1e(r4)
/* 801C2984 001BF564  7F BC EA AE */	lhax r29, r28, r29
/* 801C2988 001BF568  7C 1D 01 D6 */	mullw r0, r29, r0
/* 801C298C 001BF56C  90 06 00 08 */	stw r0, 8(r6)
/* 801C2990 001BF570  83 BF 00 00 */	lwz r29, 0(r31)
/* 801C2994 001BF574  A8 04 00 20 */	lha r0, 0x20(r4)
/* 801C2998 001BF578  7F DD F2 AE */	lhax r30, r29, r30
/* 801C299C 001BF57C  7C 1E 01 D6 */	mullw r0, r30, r0
/* 801C29A0 001BF580  90 06 00 0C */	stw r0, 0xc(r6)
/* 801C29A4 001BF584  83 DF 00 00 */	lwz r30, 0(r31)
/* 801C29A8 001BF588  A8 04 00 22 */	lha r0, 0x22(r4)
/* 801C29AC 001BF58C  7D 9E 62 AE */	lhax r12, r30, r12
/* 801C29B0 001BF590  7C 0C 01 D6 */	mullw r0, r12, r0
/* 801C29B4 001BF594  90 06 00 10 */	stw r0, 0x10(r6)
/* 801C29B8 001BF598  81 9F 00 00 */	lwz r12, 0(r31)
/* 801C29BC 001BF59C  A8 04 00 24 */	lha r0, 0x24(r4)
/* 801C29C0 001BF5A0  7D 6C 5A AE */	lhax r11, r12, r11
/* 801C29C4 001BF5A4  7C 0B 01 D6 */	mullw r0, r11, r0
/* 801C29C8 001BF5A8  90 06 00 14 */	stw r0, 0x14(r6)
/* 801C29CC 001BF5AC  81 7F 00 00 */	lwz r11, 0(r31)
/* 801C29D0 001BF5B0  A8 04 00 26 */	lha r0, 0x26(r4)
/* 801C29D4 001BF5B4  7D 4B 52 AE */	lhax r10, r11, r10
/* 801C29D8 001BF5B8  7C 0A 01 D6 */	mullw r0, r10, r0
/* 801C29DC 001BF5BC  90 06 00 18 */	stw r0, 0x18(r6)
/* 801C29E0 001BF5C0  81 5F 00 00 */	lwz r10, 0(r31)
/* 801C29E4 001BF5C4  A8 04 00 28 */	lha r0, 0x28(r4)
/* 801C29E8 001BF5C8  38 84 00 10 */	addi r4, r4, 0x10
/* 801C29EC 001BF5CC  7D 2A 4A AE */	lhax r9, r10, r9
/* 801C29F0 001BF5D0  7C 09 01 D6 */	mullw r0, r9, r0
/* 801C29F4 001BF5D4  90 06 00 1C */	stw r0, 0x1c(r6)
/* 801C29F8 001BF5D8  38 C6 00 20 */	addi r6, r6, 0x20
/* 801C29FC 001BF5DC  42 00 FF 30 */	bdnz lbl_801C292C
/* 801C2A00 001BF5E0  48 00 00 B0 */	b lbl_801C2AB0
lbl_801C2A04:
/* 801C2A04 001BF5E4  20 08 00 23 */	subfic r0, r8, 0x23
/* 801C2A08 001BF5E8  2C 08 00 23 */	cmpwi r8, 0x23
/* 801C2A0C 001BF5EC  7C 09 03 A6 */	mtctr r0
/* 801C2A10 001BF5F0  40 80 00 B4 */	bge lbl_801C2AC4
lbl_801C2A14:
/* 801C2A14 001BF5F4  80 9F 00 00 */	lwz r4, 0(r31)
/* 801C2A18 001BF5F8  38 69 00 6A */	addi r3, r9, 0x6a
/* 801C2A1C 001BF5FC  A8 05 00 1A */	lha r0, 0x1a(r5)
/* 801C2A20 001BF600  38 A5 00 02 */	addi r5, r5, 2
/* 801C2A24 001BF604  7C 64 1A AE */	lhax r3, r4, r3
/* 801C2A28 001BF608  39 29 00 02 */	addi r9, r9, 2
/* 801C2A2C 001BF60C  7C 03 01 D6 */	mullw r0, r3, r0
/* 801C2A30 001BF610  90 06 00 00 */	stw r0, 0(r6)
/* 801C2A34 001BF614  38 C6 00 04 */	addi r6, r6, 4
/* 801C2A38 001BF618  42 00 FF DC */	bdnz lbl_801C2A14
/* 801C2A3C 001BF61C  48 00 00 88 */	b lbl_801C2AC4
lbl_801C2A40:
/* 801C2A40 001BF620  38 E7 00 64 */	addi r7, r7, 0x64
/* 801C2A44 001BF624  42 00 FE C4 */	bdnz lbl_801C2908
lbl_801C2A48:
/* 801C2A48 001BF628  3C 60 80 4A */	lis r3, stage_info@ha
/* 801C2A4C 001BF62C  4C C6 31 82 */	crclr 6
/* 801C2A50 001BF630  38 63 E6 C8 */	addi r3, r3, stage_info@l
/* 801C2A54 001BF634  80 C3 00 88 */	lwz r6, 0x88(r3)
/* 801C2A58 001BF638  38 E4 00 00 */	addi r7, r4, 0
/* 801C2A5C 001BF63C  39 1B 00 00 */	addi r8, r27, 0
/* 801C2A60 001BF640  38 7C 02 BC */	addi r3, r28, 0x2bc
/* 801C2A64 001BF644  38 9C 02 18 */	addi r4, r28, 0x218
/* 801C2A68 001BF648  38 A0 09 06 */	li r5, 0x906
/* 801C2A6C 001BF64C  48 18 2C 3D */	bl OSReport
/* 801C2A70 001BF650  38 7C 03 00 */	addi r3, r28, 0x300
/* 801C2A74 001BF654  4C C6 31 82 */	crclr 6
/* 801C2A78 001BF658  48 18 2C 31 */	bl OSReport
/* 801C2A7C 001BF65C  80 7F 00 00 */	lwz r3, 0(r31)
/* 801C2A80 001BF660  3B C0 00 00 */	li r30, 0
/* 801C2A84 001BF664  83 A3 00 B0 */	lwz r29, 0xb0(r3)
/* 801C2A88 001BF668  48 00 00 1C */	b lbl_801C2AA4
lbl_801C2A8C:
/* 801C2A8C 001BF66C  80 9D 00 00 */	lwz r4, 0(r29)
/* 801C2A90 001BF670  38 7C 03 40 */	addi r3, r28, 0x340
/* 801C2A94 001BF674  4C C6 31 82 */	crclr 6
/* 801C2A98 001BF678  48 18 2C 11 */	bl OSReport
/* 801C2A9C 001BF67C  3B DE 00 01 */	addi r30, r30, 1
/* 801C2AA0 001BF680  3B BD 00 64 */	addi r29, r29, 0x64
lbl_801C2AA4:
/* 801C2AA4 001BF684  7C 1E D8 00 */	cmpw r30, r27
/* 801C2AA8 001BF688  41 80 FF E4 */	blt lbl_801C2A8C
lbl_801C2AAC:
/* 801C2AAC 001BF68C  48 00 00 00 */	b lbl_801C2AAC
lbl_801C2AB0:
/* 801C2AB0 001BF690  55 09 08 3C */	slwi r9, r8, 1
/* 801C2AB4 001BF694  55 00 10 3A */	slwi r0, r8, 2
/* 801C2AB8 001BF698  7C A7 4A 14 */	add r5, r7, r9
/* 801C2ABC 001BF69C  7C C3 02 14 */	add r6, r3, r0
/* 801C2AC0 001BF6A0  4B FF FF 44 */	b lbl_801C2A04
lbl_801C2AC4:
/* 801C2AC4 001BF6A4  BB 61 00 1C */	lmw r27, 0x1c(r1)
/* 801C2AC8 001BF6A8  80 01 00 34 */	lwz r0, 0x34(r1)
/* 801C2ACC 001BF6AC  38 21 00 30 */	addi r1, r1, 0x30
/* 801C2AD0 001BF6B0  7C 08 03 A6 */	mtlr r0
/* 801C2AD4 001BF6B4  4E 80 00 20 */	blr 
}
#pragma peephole on

u8* func_801C2AD8(void)
{
    return stage_info.xA0;
}

f32 func_801C2AE8(s32 arg0)
{
    UnkBgmStruct* phi_r5 = stage_info.x6B0->xB0;
    int i;
    for (i = 0; i < stage_info.x6B0->xB4; i++) {
        if (phi_r5->x0 == arg0) {
            return (0.01f * stage_info.x6B0->x68) * (0.01f * phi_r5->x18);
        }
        phi_r5 += 1;
    }
    OSReport("%s:%d: not found stage param in DAT\n", "ground.c", 0x927);
    while (1) {}
}

HSD_GObj* func_801C2BA4(s32 i)
{
    return stage_info.x180[i];
}

static void func_801C2BBC(HSD_GObj* arg0, s32 i)
{
    stage_info.x180[i] = arg0;
}

static const int Gr_CObj_Max = 4;

static void func_801C2BD4(void* arg0)
{
    int i;
    for (i = 0; i < 4; i++) {
        if (stage_info.x694[i] == arg0) {
            return;
        }
    }

    for (i = 0; i < 4; i++) {
        if (stage_info.x694[i] == NULL) {
            stage_info.x694[i] = arg0;
            break;
        }
    }
    assert_line(0x94D, i!=Gr_CObj_Max);
}

BOOL func_801C2C8C(void* arg0)
{
    int i;
    for (i = 0; i < 4; i++) {
        if (stage_info.x694[i] == arg0) {
            return TRUE;
        }
    }
    return FALSE;
}

HSD_JObj* func_801C2CF4(s32 i)
{
    return stage_info.x280[i];
}

void func_801C2D0C(s32 i, HSD_JObj* jobj)
{
    stage_info.x280[i] = jobj;
}

BOOL func_801C2D24(s32 arg0, Vec3* arg1)
{
    Vec3 sp20;
    Vec3 sp14;
    u32 unused;

    if (arg0 == 8) {
        func_801C2D24(4, arg1);
        func_801C2D24(5, &sp20);
        lbvector_Add(arg1, &sp20);
        arg1->x *= 0.5f;
        arg1->y *= 0.5f;
        arg1->z *= 0.5f;
        return TRUE;
    }
    if (arg0 == 9) {
        func_801C2D24(6, arg1);
        func_801C2D24(7, &sp14);
        lbvector_Add(arg1, &sp14);
        arg1->x *= 0.5f;
        arg1->y *= 0.5f;
        arg1->z *= 0.5f;
        return TRUE;
    }
    if (stage_info.x280[arg0] != NULL) {
        func_8000B1CC(stage_info.x280[arg0], NULL, arg1);
        return TRUE;
    }
    if (arg0 - 1 <= 2U) {
        return func_801C2D24(0, arg1);
    }
    if (arg0 - 5 <= 2U) {
        return func_801C2D24(4, arg1);
    }
    if (arg0 == 0x7F) {
        if (func_801C2D24(0x94, arg1)) {
            arg1->y += 50;
            return TRUE;
        }
        return func_801C2D24(0, arg1);
    }
    if (arg0 == 4) {
        Stage_UnkSetVec3TCam_Offset(arg1);
        return TRUE;
    }
    return FALSE;
}

extern void func_80057424(s16);

BOOL func_801C2ED0(HSD_JObj* jobj, s32 arg1)
{
    UnkArchiveStruct* temp_r3;
    S16Vec* cur;
    s32 i;
    s32 max;
    BOOL result = FALSE;
    u32 unused;

    temp_r3 = func_801C6330(arg1);
    if (temp_r3 != NULL) {
        cur = temp_r3->unk4->unk8[arg1].unk20;
        max = temp_r3->unk4->unk8[arg1].unk24;
        for (i = 0; i < max;) {
            func_800552B0(cur->x, jobj, cur->z);
            func_80055E9C(cur->x);
            func_80057424(cur->x);
            result = TRUE;
            i++;
            cur++;
        }
    }
    max = lbl_803DFEDC[stage_info.internal_stage_id]->x30;
    cur = lbl_803DFEDC[stage_info.internal_stage_id]->x2C;
    for (i = 0; i < max;) {
        if (cur->y == arg1) {
            func_800552B0(cur->x, jobj, cur->z);
            func_80055E9C(cur->x);
            func_80057424(cur->x);
            result = TRUE;
        }
        i++;
        cur++;
    }
    func_801C3214(arg1);
    return result;
}

static s16 lbl_804D6954;
extern void func_8004D17C();
asm void func_801C2FE0()
{
    nofralloc
/* 801C2FE0 001BFBC0  7C 08 02 A6 */	mflr r0
/* 801C2FE4 001BFBC4  90 01 00 04 */	stw r0, 4(r1)
/* 801C2FE8 001BFBC8  94 21 FF D0 */	stwu r1, -0x30(r1)
/* 801C2FEC 001BFBCC  BF 41 00 18 */	stmw r26, 0x18(r1)
/* 801C2FF0 001BFBD0  80 83 00 2C */	lwz r4, 0x2c(r3)
/* 801C2FF4 001BFBD4  80 6D B2 B0 */	lwz r3, lbl_804D6950
/* 801C2FF8 001BFBD8  80 84 00 14 */	lwz r4, 0x14(r4)
/* 801C2FFC 001BFBDC  7C 03 20 AE */	lbzx r0, r3, r4
/* 801C3000 001BFBE0  3B C4 00 00 */	addi r30, r4, 0
/* 801C3004 001BFBE4  28 00 00 00 */	cmplwi r0, 0
/* 801C3008 001BFBE8  40 82 01 08 */	bne lbl_801C3110
/* 801C300C 001BFBEC  3B A0 00 00 */	li r29, 0
/* 801C3010 001BFBF0  4B E8 A1 6D */	bl func_8004D17C
/* 801C3014 001BFBF4  A8 CD B2 B4 */	lha r6, lbl_804D6954
/* 801C3018 001BFBF8  3C A0 80 4A */	lis r5, stage_info@ha
/* 801C301C 001BFBFC  3C 80 80 3E */	lis r4, lbl_803DFEDC@ha
/* 801C3020 001BFC00  38 06 00 01 */	addi r0, r6, 1
/* 801C3024 001BFC04  B0 0D B2 B4 */	sth r0, lbl_804D6954
/* 801C3028 001BFC08  38 A5 E6 C8 */	addi r5, r5, stage_info@l
/* 801C302C 001BFC0C  38 04 FE DC */	addi r0, r4, lbl_803DFEDC@l
/* 801C3030 001BFC10  80 85 00 88 */	lwz r4, 0x88(r5)
/* 801C3034 001BFC14  3B E3 00 00 */	addi r31, r3, 0
/* 801C3038 001BFC18  3B 80 00 00 */	li r28, 0
/* 801C303C 001BFC1C  54 83 10 3A */	slwi r3, r4, 2
/* 801C3040 001BFC20  7C 60 1A 14 */	add r3, r0, r3
/* 801C3044 001BFC24  80 63 00 00 */	lwz r3, 0(r3)
/* 801C3048 001BFC28  83 43 00 30 */	lwz r26, 0x30(r3)
/* 801C304C 001BFC2C  83 63 00 2C */	lwz r27, 0x2c(r3)
/* 801C3050 001BFC30  48 00 00 38 */	b lbl_801C3088
lbl_801C3054:
/* 801C3054 001BFC34  A8 1B 00 02 */	lha r0, 2(r27)
/* 801C3058 001BFC38  7C 00 F0 00 */	cmpw r0, r30
/* 801C305C 001BFC3C  40 82 00 24 */	bne lbl_801C3080
/* 801C3060 001BFC40  A8 7B 00 00 */	lha r3, 0(r27)
/* 801C3064 001BFC44  4B E9 2E 39 */	bl func_80055E9C
/* 801C3068 001BFC48  A8 1B 00 00 */	lha r0, 0(r27)
/* 801C306C 001BFC4C  3B A0 00 01 */	li r29, 1
/* 801C3070 001BFC50  A8 8D B2 B4 */	lha r4, lbl_804D6954
/* 801C3074 001BFC54  1C 60 00 34 */	mulli r3, r0, 0x34
/* 801C3078 001BFC58  38 03 00 0C */	addi r0, r3, 0xc
/* 801C307C 001BFC5C  7C 9F 03 2E */	sthx r4, r31, r0
lbl_801C3080:
/* 801C3080 001BFC60  3B 9C 00 01 */	addi r28, r28, 1
/* 801C3084 001BFC64  3B 7B 00 06 */	addi r27, r27, 6
lbl_801C3088:
/* 801C3088 001BFC68  7C 1C D0 00 */	cmpw r28, r26
/* 801C308C 001BFC6C  41 80 FF C8 */	blt lbl_801C3054
/* 801C3090 001BFC70  7F C3 F3 78 */	mr r3, r30
/* 801C3094 001BFC74  48 00 32 9D */	bl func_801C6330
/* 801C3098 001BFC78  28 03 00 00 */	cmplwi r3, 0
/* 801C309C 001BFC7C  41 82 00 6C */	beq lbl_801C3108
/* 801C30A0 001BFC80  80 63 00 04 */	lwz r3, 4(r3)
/* 801C30A4 001BFC84  1C 1E 00 34 */	mulli r0, r30, 0x34
/* 801C30A8 001BFC88  80 63 00 08 */	lwz r3, 8(r3)
/* 801C30AC 001BFC8C  3B 60 00 00 */	li r27, 0
/* 801C30B0 001BFC90  7C 63 02 14 */	add r3, r3, r0
/* 801C30B4 001BFC94  83 83 00 20 */	lwz r28, 0x20(r3)
/* 801C30B8 001BFC98  83 C3 00 24 */	lwz r30, 0x24(r3)
/* 801C30BC 001BFC9C  48 00 00 44 */	b lbl_801C3100
lbl_801C30C0:
/* 801C30C0 001BFCA0  A8 7C 00 00 */	lha r3, 0(r28)
/* 801C30C4 001BFCA4  A8 AD B2 B4 */	lha r5, lbl_804D6954
/* 801C30C8 001BFCA8  1C 83 00 34 */	mulli r4, r3, 0x34
/* 801C30CC 001BFCAC  38 04 00 0C */	addi r0, r4, 0xc
/* 801C30D0 001BFCB0  7C 1F 02 AE */	lhax r0, r31, r0
/* 801C30D4 001BFCB4  7C 05 00 00 */	cmpw r5, r0
/* 801C30D8 001BFCB8  41 82 00 20 */	beq lbl_801C30F8
/* 801C30DC 001BFCBC  4B E9 2D C1 */	bl func_80055E9C
/* 801C30E0 001BFCC0  A8 1C 00 00 */	lha r0, 0(r28)
/* 801C30E4 001BFCC4  3B A0 00 01 */	li r29, 1
/* 801C30E8 001BFCC8  A8 8D B2 B4 */	lha r4, lbl_804D6954
/* 801C30EC 001BFCCC  1C 60 00 34 */	mulli r3, r0, 0x34
/* 801C30F0 001BFCD0  38 03 00 0C */	addi r0, r3, 0xc
/* 801C30F4 001BFCD4  7C 9F 03 2E */	sthx r4, r31, r0
lbl_801C30F8:
/* 801C30F8 001BFCD8  3B 7B 00 01 */	addi r27, r27, 1
/* 801C30FC 001BFCDC  3B 9C 00 06 */	addi r28, r28, 6
lbl_801C3100:
/* 801C3100 001BFCE0  7C 1B F0 00 */	cmpw r27, r30
/* 801C3104 001BFCE4  41 80 FF BC */	blt lbl_801C30C0
lbl_801C3108:
/* 801C3108 001BFCE8  7F A3 EB 78 */	mr r3, r29
/* 801C310C 001BFCEC  48 00 00 08 */	b lbl_801C3114
lbl_801C3110:
/* 801C3110 001BFCF0  38 60 00 00 */	li r3, 0
lbl_801C3114:
/* 801C3114 001BFCF4  BB 41 00 18 */	lmw r26, 0x18(r1)
/* 801C3118 001BFCF8  80 01 00 34 */	lwz r0, 0x34(r1)
/* 801C311C 001BFCFC  38 21 00 30 */	addi r1, r1, 0x30
/* 801C3120 001BFD00  7C 08 03 A6 */	mtlr r0
/* 801C3124 001BFD04  4E 80 00 20 */	blr 
}
#pragma peephole on

BOOL func_801C3128(s32 arg0, void (*arg1)(s16))
{
    StageData* stage_data;
    UnkArchiveStruct* tmp;
    BOOL result;
    S16Vec* cur;
    s32 max;
    s32 i;

    func_8004D17C();
    result = FALSE;
    max = lbl_803DFEDC[stage_info.internal_stage_id]->x30;
    cur = lbl_803DFEDC[stage_info.internal_stage_id]->x2C;
    for (i = 0; i < max; i++, cur++) {
        if (cur->y == arg0) {
            arg1(cur->x);
            result = TRUE;
        }
    }
    tmp = func_801C6330(arg0);
    if (tmp != 0U) {
        cur = tmp->unk4->unk8[arg0].unk20;
        max = tmp->unk4->unk8[arg0].unk24;
        for (i = 0; i < max; i++, cur++) {
            arg1(cur->x);
            result = TRUE;
        }
    }
    return result;
}

extern void func_80057638(s16);
BOOL func_801C3214(s32 arg0)
{
    if (lbl_804D6950[arg0] == 1) {
        lbl_804D6950[arg0] = 0;
        return func_801C3128(arg0, func_80057638);
    }
    return FALSE;
}

extern void func_80057BC0(s16);
BOOL func_801C3260(s32 arg0)
{
    if (lbl_804D6950[arg0] == 0) {
        lbl_804D6950[arg0] = 1;
        return func_801C3128(arg0, func_80057BC0);
    }
    return FALSE;
}

void func_801C32AC(s32 arg0)
{
    func_801C3128(arg0, func_80057424);
}

s32 func_801C32D4(s32 arg0, s32 arg1)
{
    UnkArchiveStruct* tmp;
    s32 max;
    S16Vec* cur;
    s32 i;
    s32 result;
    u32 unused;

    func_8004D17C();
    max = lbl_803DFEDC[stage_info.internal_stage_id]->x30;
    cur = lbl_803DFEDC[stage_info.internal_stage_id]->x2C;
    result = -1;
    for (i = 0; i < max; cur++, i++) {
        if (cur->y == arg0 && cur->z == arg1) {
            result = cur->x;
        }
    }
    tmp = func_801C6330(arg0);
    if (tmp != NULL) {
        max = tmp->unk4->unk8[arg0].unk24;
        cur = tmp->unk4->unk8[arg0].unk20;
        for (i = 0; i < max; cur++, i++) {
            if (cur->z == arg1) {
                result = cur->x;
            }
        }
    }
    return result;
}

s32 func_801C33C0(s32 arg0, s32 arg1)
{
    UnkArchiveStruct* tmp;
    s32 max;
    S16Vec* cur;
    s32 i;
    s32 result;
    u32 unused;

    func_8004D17C();
    max = lbl_803DFEDC[stage_info.internal_stage_id]->x30;
    cur = lbl_803DFEDC[stage_info.internal_stage_id]->x2C;
    result = -1;
    for (i = 0; i < max; cur++, i++) {
        if (cur->y == arg0 && cur->x == arg1) {
            result = cur->z;
        }
    }
    tmp = func_801C6330(arg0);
    if (tmp != NULL) {
        max = tmp->unk4->unk8[arg0].unk24;
        cur = tmp->unk4->unk8[arg0].unk20;
        for (i = 0; i < max; cur++, i++) {
            if (cur->x == arg1) {
                result = cur->z;
            }
        }
    }
    return result;
}

u32 unknown[] = {
    0x00000002,
    0,
    0x42C80000,
    0x43270000,
    0,
    0x00000002,
    0x00000001,
    0x42C80000,
    0x43270000,
    0,
    0x00000002,
    0x00000002,
    0x42C80000,
    0x43270000,
    0,
    0x00000002,
    0x00000003,
    0x42C80000,
    0x43270000,
    0,
    0x00000002,
    0x00000004,
    0x42C80000,
    0x43480000,
    0,
    0x00000002,
    0x00000094,
    0,
    0x433B0000,
    0,
    0x0000000E,
    0,
    0xC28E0000,
    0x436E0000,
    0,
    0x0000000E,
    0x00000001,
    0xC28E0000,
    0x436E0000,
    0,
    0x0000000E,
    0x00000002,
    0xC28E0000,
    0x436E0000,
    0,
    0x0000000E,
    0x00000003,
    0xC28E0000,
    0x436E0000,
    0,
    0x0000000E,
    0x00000094,
    0,
    0x43750000,
    0,
    0x00000015,
    0x00000004,
    0x41100000,
    0x426C0000,
    0,
    0x00000015,
    0,
    0xC1100000,
    0x42860000,
    0,
    0x00000015,
    0x00000001,
    0x42580000,
    0x40000000,
    0,
    0x00000015,
    0x00000002,
    0xC2960000,
    0x40800000,
    0,
    0x00000015,
    0x00000003,
    0x42AE0000,
    0xC1500000,
    0,
    0x0000001F,
    0,
    0xC4750000,
    0x42540000,
    0,
    0x0000001F,
    0x00000004,
    0xC4750000,
    0x42F00000,
    0,
    0x0000001F,
    0x00000099,
    0x44C96000,
    0x43480000,
    0,
    0x00000020,
    0,
    0x43700000,
    0xC3928000,
    0,
    0x00000020,
    0x00000099,
    0x41200000,
    0x40000000,
    0,
    0x00000020,
    0x00000004,
    0x43700000,
    0,
    0,
    0x00000021,
    0x00000099,
    0,
    0x446EC000,
    0,
    0x00000022,
    0,
    0xC47A0000,
    0x42B00000,
    0,
    0x00000022,
    0x00000004,
    0xC47A0000,
    0x42C80000,
    0,
    0x00000027,
    0,
    0x43C30000,
    0x44610000,
    0,
    0x00000027,
    0x00000094,
    0x43C30000,
    0x44610000,
    0,
    0x00000027,
    0x00000004,
    0x43C30000,
    0x44610000,
    0,
    0x00000013,
    0,
    0xC2480000,
    0x42700000,
    0,
    0x00000013,
    0x00000004,
    0x41F00000,
    0x42C80000,
    0,
    0x00000006,
    0,
    0x41F00000,
    0x42700000,
    0,
    0x00000006,
    0x00000004,
    0xC2200000,
    0x42700000,
    0,
    0xFFFFFFFF,
    0,
    0,
    0x40A00000,
    0,
    0xFFFFFFFF,
    0x00000001,
    0,
    0x40A00000,
    0,
    0xFFFFFFFF,
    0x00000002,
    0,
    0x40A00000,
    0,
    0xFFFFFFFF,
    0x00000003,
    0,
    0x40A00000,
    0,
    0xFFFFFFFF,
    0x00000094,
    0,
    0,
    0,
    0xFFFFFFFF,
    0xFFFFFFFF,
    0,
    0,
    0,
};
char unkmsg[] = "%s:%d:Error (root=%08x joint=%08x)\n";
static asm void func_801C34AC(s32, HSD_JObj*, HSD_Joint*)
{
    nofralloc
/* 801C34AC 001C008C  7C 08 02 A6 */	mflr r0
/* 801C34B0 001C0090  90 01 00 04 */	stw r0, 4(r1)
/* 801C34B4 001C0094  94 21 FF D0 */	stwu r1, -0x30(r1)
/* 801C34B8 001C0098  BF 61 00 1C */	stmw r27, 0x1c(r1)
/* 801C34BC 001C009C  3B C4 00 00 */	addi r30, r4, 0
/* 801C34C0 001C00A0  3C 80 80 3E */	lis r4, lbl_803DFEA8@ha
/* 801C34C4 001C00A4  3B 65 00 00 */	addi r27, r5, 0
/* 801C34C8 001C00A8  3B FE 00 00 */	addi r31, r30, 0
/* 801C34CC 001C00AC  3B A4 FE A8 */	addi r29, r4, lbl_803DFEA8@l
/* 801C34D0 001C00B0  3B 80 FF FF */	li r28, -1
/* 801C34D4 001C00B4  48 00 2E 5D */	bl func_801C6330
/* 801C34D8 001C00B8  28 03 00 00 */	cmplwi r3, 0
/* 801C34DC 001C00BC  41 82 02 04 */	beq lbl_801C36E0
/* 801C34E0 001C00C0  28 1E 00 00 */	cmplwi r30, 0
/* 801C34E4 001C00C4  41 82 00 0C */	beq lbl_801C34F0
/* 801C34E8 001C00C8  28 1B 00 00 */	cmplwi r27, 0
/* 801C34EC 001C00CC  40 82 00 24 */	bne lbl_801C3510
lbl_801C34F0:
/* 801C34F0 001C00D0  38 9D 02 18 */	addi r4, r29, 0x218
/* 801C34F4 001C00D4  4C C6 31 82 */	crclr 6
/* 801C34F8 001C00D8  38 A4 00 00 */	addi r5, r4, 0
/* 801C34FC 001C00DC  38 DE 00 00 */	addi r6, r30, 0
/* 801C3500 001C00E0  38 FB 00 00 */	addi r7, r27, 0
/* 801C3504 001C00E4  38 7D 06 80 */	addi r3, r29, 0x680
/* 801C3508 001C00E8  48 18 21 A1 */	bl OSReport
/* 801C350C 001C00EC  48 00 01 D4 */	b lbl_801C36E0
lbl_801C3510:
/* 801C3510 001C00F0  80 63 00 04 */	lwz r3, 4(r3)
/* 801C3514 001C00F4  80 83 00 04 */	lwz r4, 4(r3)
/* 801C3518 001C00F8  2C 04 00 00 */	cmpwi r4, 0
/* 801C351C 001C00FC  41 82 01 C4 */	beq lbl_801C36E0
/* 801C3520 001C0100  38 A0 00 00 */	li r5, 0
/* 801C3524 001C0104  80 C3 00 00 */	lwz r6, 0(r3)
lbl_801C3528:
/* 801C3528 001C0108  7C 05 20 00 */	cmpw r5, r4
/* 801C352C 001C010C  40 80 01 B4 */	bge lbl_801C36E0
/* 801C3530 001C0110  80 06 00 00 */	lwz r0, 0(r6)
/* 801C3534 001C0114  7C 00 D8 40 */	cmplw r0, r27
/* 801C3538 001C0118  41 82 00 18 */	beq lbl_801C3550
/* 801C353C 001C011C  48 00 00 08 */	b lbl_801C3544
/* 801C3540 001C0120  48 00 01 A0 */	b lbl_801C36E0
lbl_801C3544:
/* 801C3544 001C0124  38 C6 00 0C */	addi r6, r6, 0xc
/* 801C3548 001C0128  38 A5 00 01 */	addi r5, r5, 1
/* 801C354C 001C012C  4B FF FF DC */	b lbl_801C3528
lbl_801C3550:
/* 801C3550 001C0130  80 86 00 08 */	lwz r4, 8(r6)
/* 801C3554 001C0134  3C 60 80 4A */	lis r3, stage_info@ha
/* 801C3558 001C0138  80 C6 00 04 */	lwz r6, 4(r6)
/* 801C355C 001C013C  38 03 E6 C8 */	addi r0, r3, stage_info@l
/* 801C3560 001C0140  2C 04 00 00 */	cmpwi r4, 0
/* 801C3564 001C0144  7C 89 03 A6 */	mtctr r4
/* 801C3568 001C0148  40 81 01 78 */	ble lbl_801C36E0
lbl_801C356C:
/* 801C356C 001C014C  A8 86 00 00 */	lha r4, 0(r6)
/* 801C3570 001C0150  7C 1C 20 00 */	cmpw r28, r4
/* 801C3574 001C0154  41 81 00 0C */	bgt lbl_801C3580
/* 801C3578 001C0158  2C 1C FF FF */	cmpwi r28, -1
/* 801C357C 001C015C  40 82 00 10 */	bne lbl_801C358C
lbl_801C3580:
/* 801C3580 001C0160  3B FE 00 00 */	addi r31, r30, 0
/* 801C3584 001C0164  38 A0 00 00 */	li r5, 0
/* 801C3588 001C0168  48 00 01 34 */	b lbl_801C36BC
lbl_801C358C:
/* 801C358C 001C016C  7F 85 E3 78 */	mr r5, r28
/* 801C3590 001C0170  48 00 01 2C */	b lbl_801C36BC
lbl_801C3594:
/* 801C3594 001C0174  7C 05 20 00 */	cmpw r5, r4
/* 801C3598 001C0178  41 82 01 2C */	beq lbl_801C36C4
/* 801C359C 001C017C  80 7F 00 14 */	lwz r3, 0x14(r31)
/* 801C35A0 001C0180  54 63 04 E7 */	rlwinm. r3, r3, 0, 0x13, 0x13
/* 801C35A4 001C0184  40 82 00 3C */	bne lbl_801C35E0
/* 801C35A8 001C0188  28 1F 00 00 */	cmplwi r31, 0
/* 801C35AC 001C018C  40 82 00 0C */	bne lbl_801C35B8
/* 801C35B0 001C0190  38 60 00 00 */	li r3, 0
/* 801C35B4 001C0194  48 00 00 08 */	b lbl_801C35BC
lbl_801C35B8:
/* 801C35B8 001C0198  80 7F 00 10 */	lwz r3, 0x10(r31)
lbl_801C35BC:
/* 801C35BC 001C019C  28 03 00 00 */	cmplwi r3, 0
/* 801C35C0 001C01A0  41 82 00 20 */	beq lbl_801C35E0
/* 801C35C4 001C01A4  28 1F 00 00 */	cmplwi r31, 0
/* 801C35C8 001C01A8  40 82 00 0C */	bne lbl_801C35D4
/* 801C35CC 001C01AC  38 60 00 00 */	li r3, 0
/* 801C35D0 001C01B0  48 00 00 08 */	b lbl_801C35D8
lbl_801C35D4:
/* 801C35D4 001C01B4  80 7F 00 10 */	lwz r3, 0x10(r31)
lbl_801C35D8:
/* 801C35D8 001C01B8  7C 7F 1B 78 */	mr r31, r3
/* 801C35DC 001C01BC  48 00 00 DC */	b lbl_801C36B8
lbl_801C35E0:
/* 801C35E0 001C01C0  28 1F 00 00 */	cmplwi r31, 0
/* 801C35E4 001C01C4  40 82 00 0C */	bne lbl_801C35F0
/* 801C35E8 001C01C8  38 60 00 00 */	li r3, 0
/* 801C35EC 001C01CC  48 00 00 08 */	b lbl_801C35F4
lbl_801C35F0:
/* 801C35F0 001C01D0  80 7F 00 08 */	lwz r3, 8(r31)
lbl_801C35F4:
/* 801C35F4 001C01D4  28 03 00 00 */	cmplwi r3, 0
/* 801C35F8 001C01D8  41 82 00 20 */	beq lbl_801C3618
/* 801C35FC 001C01DC  28 1F 00 00 */	cmplwi r31, 0
/* 801C3600 001C01E0  40 82 00 0C */	bne lbl_801C360C
/* 801C3604 001C01E4  38 60 00 00 */	li r3, 0
/* 801C3608 001C01E8  48 00 00 08 */	b lbl_801C3610
lbl_801C360C:
/* 801C360C 001C01EC  80 7F 00 08 */	lwz r3, 8(r31)
lbl_801C3610:
/* 801C3610 001C01F0  7C 7F 1B 78 */	mr r31, r3
/* 801C3614 001C01F4  48 00 00 A4 */	b lbl_801C36B8
lbl_801C3618:
/* 801C3618 001C01F8  28 1F 00 00 */	cmplwi r31, 0
/* 801C361C 001C01FC  40 82 00 0C */	bne lbl_801C3628
/* 801C3620 001C0200  38 60 00 00 */	li r3, 0
/* 801C3624 001C0204  48 00 00 08 */	b lbl_801C362C
lbl_801C3628:
/* 801C3628 001C0208  80 7F 00 0C */	lwz r3, 0xc(r31)
lbl_801C362C:
/* 801C362C 001C020C  28 03 00 00 */	cmplwi r3, 0
/* 801C3630 001C0210  40 82 00 0C */	bne lbl_801C363C
/* 801C3634 001C0214  3B E0 00 00 */	li r31, 0
/* 801C3638 001C0218  48 00 00 80 */	b lbl_801C36B8
lbl_801C363C:
/* 801C363C 001C021C  28 1F 00 00 */	cmplwi r31, 0
/* 801C3640 001C0220  40 82 00 0C */	bne lbl_801C364C
/* 801C3644 001C0224  38 60 00 00 */	li r3, 0
/* 801C3648 001C0228  48 00 00 08 */	b lbl_801C3650
lbl_801C364C:
/* 801C364C 001C022C  80 7F 00 0C */	lwz r3, 0xc(r31)
lbl_801C3650:
/* 801C3650 001C0230  28 03 00 00 */	cmplwi r3, 0
/* 801C3654 001C0234  40 82 00 0C */	bne lbl_801C3660
/* 801C3658 001C0238  38 60 00 00 */	li r3, 0
/* 801C365C 001C023C  48 00 00 08 */	b lbl_801C3664
lbl_801C3660:
/* 801C3660 001C0240  80 63 00 08 */	lwz r3, 8(r3)
lbl_801C3664:
/* 801C3664 001C0244  28 03 00 00 */	cmplwi r3, 0
/* 801C3668 001C0248  41 82 00 34 */	beq lbl_801C369C
/* 801C366C 001C024C  28 1F 00 00 */	cmplwi r31, 0
/* 801C3670 001C0250  40 82 00 0C */	bne lbl_801C367C
/* 801C3674 001C0254  38 60 00 00 */	li r3, 0
/* 801C3678 001C0258  48 00 00 08 */	b lbl_801C3680
lbl_801C367C:
/* 801C367C 001C025C  80 7F 00 0C */	lwz r3, 0xc(r31)
lbl_801C3680:
/* 801C3680 001C0260  28 03 00 00 */	cmplwi r3, 0
/* 801C3684 001C0264  40 82 00 0C */	bne lbl_801C3690
/* 801C3688 001C0268  38 60 00 00 */	li r3, 0
/* 801C368C 001C026C  48 00 00 08 */	b lbl_801C3694
lbl_801C3690:
/* 801C3690 001C0270  80 63 00 08 */	lwz r3, 8(r3)
lbl_801C3694:
/* 801C3694 001C0274  7C 7F 1B 78 */	mr r31, r3
/* 801C3698 001C0278  48 00 00 20 */	b lbl_801C36B8
lbl_801C369C:
/* 801C369C 001C027C  28 1F 00 00 */	cmplwi r31, 0
/* 801C36A0 001C0280  40 82 00 0C */	bne lbl_801C36AC
/* 801C36A4 001C0284  38 60 00 00 */	li r3, 0
/* 801C36A8 001C0288  48 00 00 08 */	b lbl_801C36B0
lbl_801C36AC:
/* 801C36AC 001C028C  80 7F 00 0C */	lwz r3, 0xc(r31)
lbl_801C36B0:
/* 801C36B0 001C0290  7C 7F 1B 78 */	mr r31, r3
/* 801C36B4 001C0294  4B FF FF 64 */	b lbl_801C3618
lbl_801C36B8:
/* 801C36B8 001C0298  38 A5 00 01 */	addi r5, r5, 1
lbl_801C36BC:
/* 801C36BC 001C029C  28 1F 00 00 */	cmplwi r31, 0
/* 801C36C0 001C02A0  40 82 FE D4 */	bne lbl_801C3594
lbl_801C36C4:
/* 801C36C4 001C02A4  A8 66 00 02 */	lha r3, 2(r6)
/* 801C36C8 001C02A8  3B 85 00 00 */	addi r28, r5, 0
/* 801C36CC 001C02AC  38 C6 00 04 */	addi r6, r6, 4
/* 801C36D0 001C02B0  54 63 10 3A */	slwi r3, r3, 2
/* 801C36D4 001C02B4  7C 60 1A 14 */	add r3, r0, r3
/* 801C36D8 001C02B8  93 E3 02 80 */	stw r31, 0x280(r3)
/* 801C36DC 001C02BC  42 00 FE 90 */	bdnz lbl_801C356C
lbl_801C36E0:
/* 801C36E0 001C02C0  BB 61 00 1C */	lmw r27, 0x1c(r1)
/* 801C36E4 001C02C4  80 01 00 34 */	lwz r0, 0x34(r1)
/* 801C36E8 001C02C8  38 21 00 30 */	addi r1, r1, 0x30
/* 801C36EC 001C02CC  7C 08 03 A6 */	mtlr r0
/* 801C36F0 001C02D0  4E 80 00 20 */	blr 
}
#pragma peephole on

asm void func_801C36F4(s32 map_id, HSD_JObj* jobj, void* unk)
{
    nofralloc
/* 801C36F4 001C02D4  7C 08 02 A6 */	mflr r0
/* 801C36F8 001C02D8  3C C0 80 3E */	lis r6, lbl_803DFEA8@ha
/* 801C36FC 001C02DC  90 01 00 04 */	stw r0, 4(r1)
/* 801C3700 001C02E0  94 21 FF C8 */	stwu r1, -0x38(r1)
/* 801C3704 001C02E4  93 E1 00 34 */	stw r31, 0x34(r1)
/* 801C3708 001C02E8  3B E4 00 00 */	addi r31, r4, 0
/* 801C370C 001C02EC  93 C1 00 30 */	stw r30, 0x30(r1)
/* 801C3710 001C02F0  93 A1 00 2C */	stw r29, 0x2c(r1)
/* 801C3714 001C02F4  3B A6 FE A8 */	addi r29, r6, lbl_803DFEA8@l
/* 801C3718 001C02F8  93 81 00 28 */	stw r28, 0x28(r1)
/* 801C371C 001C02FC  3B 85 00 00 */	addi r28, r5, 0
/* 801C3720 001C0300  48 00 2C 11 */	bl func_801C6330
/* 801C3724 001C0304  7C 7E 1B 79 */	or. r30, r3, r3
/* 801C3728 001C0308  40 82 00 14 */	bne lbl_801C373C
/* 801C372C 001C030C  38 7D 02 18 */	addi r3, r29, 0x218
/* 801C3730 001C0310  38 80 0B 78 */	li r4, 0xb78
/* 801C3734 001C0314  38 AD 8E 58 */	addi r5, r13, lbl_804D44F8
/* 801C3738 001C0318  48 1C 4A E9 */	bl __assert
lbl_801C373C:
/* 801C373C 001C031C  28 1F 00 00 */	cmplwi r31, 0
/* 801C3740 001C0320  41 82 00 0C */	beq lbl_801C374C
/* 801C3744 001C0324  28 1C 00 00 */	cmplwi r28, 0
/* 801C3748 001C0328  40 82 00 24 */	bne lbl_801C376C
lbl_801C374C:
/* 801C374C 001C032C  38 9D 02 18 */	addi r4, r29, 0x218
/* 801C3750 001C0330  4C C6 31 82 */	crclr 6
/* 801C3754 001C0334  38 A4 00 00 */	addi r5, r4, 0
/* 801C3758 001C0338  38 DF 00 00 */	addi r6, r31, 0
/* 801C375C 001C033C  38 FC 00 00 */	addi r7, r28, 0
/* 801C3760 001C0340  38 7D 06 80 */	addi r3, r29, 0x680
/* 801C3764 001C0344  48 18 1F 45 */	bl OSReport
/* 801C3768 001C0348  48 00 00 F8 */	b lbl_801C3860
lbl_801C376C:
/* 801C376C 001C034C  80 7E 00 04 */	lwz r3, 4(r30)
/* 801C3770 001C0350  80 83 00 04 */	lwz r4, 4(r3)
/* 801C3774 001C0354  2C 04 00 00 */	cmpwi r4, 0
/* 801C3778 001C0358  41 82 00 E8 */	beq lbl_801C3860
/* 801C377C 001C035C  38 A0 00 00 */	li r5, 0
/* 801C3780 001C0360  80 63 00 00 */	lwz r3, 0(r3)
lbl_801C3784:
/* 801C3784 001C0364  7C 05 20 00 */	cmpw r5, r4
/* 801C3788 001C0368  40 80 00 D8 */	bge lbl_801C3860
/* 801C378C 001C036C  80 03 00 00 */	lwz r0, 0(r3)
/* 801C3790 001C0370  7C 00 E0 40 */	cmplw r0, r28
/* 801C3794 001C0374  41 82 00 18 */	beq lbl_801C37AC
/* 801C3798 001C0378  48 00 00 08 */	b lbl_801C37A0
/* 801C379C 001C037C  48 00 00 C4 */	b lbl_801C3860
lbl_801C37A0:
/* 801C37A0 001C0380  38 63 00 0C */	addi r3, r3, 0xc
/* 801C37A4 001C0384  38 A5 00 01 */	addi r5, r5, 1
/* 801C37A8 001C0388  4B FF FF DC */	b lbl_801C3784
lbl_801C37AC:
/* 801C37AC 001C038C  38 00 00 57 */	li r0, 0x57
/* 801C37B0 001C0390  3C 60 80 4A */	lis r3, stage_info@ha
/* 801C37B4 001C0394  7C 09 03 A6 */	mtctr r0
/* 801C37B8 001C0398  38 A0 00 00 */	li r5, 0
/* 801C37BC 001C039C  38 63 E6 C8 */	addi r3, r3, stage_info@l
/* 801C37C0 001C03A0  38 05 00 00 */	addi r0, r5, 0
lbl_801C37C4:
/* 801C37C4 001C03A4  80 C3 02 80 */	lwz r6, 0x280(r3)
/* 801C37C8 001C03A8  28 06 00 00 */	cmplwi r6, 0
/* 801C37CC 001C03AC  41 82 00 24 */	beq lbl_801C37F0
/* 801C37D0 001C03B0  48 00 00 08 */	b lbl_801C37D8
lbl_801C37D4:
/* 801C37D4 001C03B4  7C 86 23 78 */	mr r6, r4
lbl_801C37D8:
/* 801C37D8 001C03B8  80 86 00 0C */	lwz r4, 0xc(r6)
/* 801C37DC 001C03BC  28 04 00 00 */	cmplwi r4, 0
/* 801C37E0 001C03C0  40 82 FF F4 */	bne lbl_801C37D4
/* 801C37E4 001C03C4  7C 06 F8 40 */	cmplw r6, r31
/* 801C37E8 001C03C8  40 82 00 08 */	bne lbl_801C37F0
/* 801C37EC 001C03CC  90 03 02 80 */	stw r0, 0x280(r3)
lbl_801C37F0:
/* 801C37F0 001C03D0  80 C3 02 84 */	lwz r6, 0x284(r3)
/* 801C37F4 001C03D4  38 63 00 04 */	addi r3, r3, 4
/* 801C37F8 001C03D8  28 06 00 00 */	cmplwi r6, 0
/* 801C37FC 001C03DC  41 82 00 24 */	beq lbl_801C3820
/* 801C3800 001C03E0  48 00 00 08 */	b lbl_801C3808
lbl_801C3804:
/* 801C3804 001C03E4  7C 86 23 78 */	mr r6, r4
lbl_801C3808:
/* 801C3808 001C03E8  80 86 00 0C */	lwz r4, 0xc(r6)
/* 801C380C 001C03EC  28 04 00 00 */	cmplwi r4, 0
/* 801C3810 001C03F0  40 82 FF F4 */	bne lbl_801C3804
/* 801C3814 001C03F4  7C 06 F8 40 */	cmplw r6, r31
/* 801C3818 001C03F8  40 82 00 08 */	bne lbl_801C3820
/* 801C381C 001C03FC  90 03 02 80 */	stw r0, 0x280(r3)
lbl_801C3820:
/* 801C3820 001C0400  80 C3 02 84 */	lwz r6, 0x284(r3)
/* 801C3824 001C0404  38 63 00 04 */	addi r3, r3, 4
/* 801C3828 001C0408  38 A5 00 01 */	addi r5, r5, 1
/* 801C382C 001C040C  28 06 00 00 */	cmplwi r6, 0
/* 801C3830 001C0410  41 82 00 24 */	beq lbl_801C3854
/* 801C3834 001C0414  48 00 00 08 */	b lbl_801C383C
lbl_801C3838:
/* 801C3838 001C0418  7C 86 23 78 */	mr r6, r4
lbl_801C383C:
/* 801C383C 001C041C  80 86 00 0C */	lwz r4, 0xc(r6)
/* 801C3840 001C0420  28 04 00 00 */	cmplwi r4, 0
/* 801C3844 001C0424  40 82 FF F4 */	bne lbl_801C3838
/* 801C3848 001C0428  7C 06 F8 40 */	cmplw r6, r31
/* 801C384C 001C042C  40 82 00 08 */	bne lbl_801C3854
/* 801C3850 001C0430  90 03 02 80 */	stw r0, 0x280(r3)
lbl_801C3854:
/* 801C3854 001C0434  38 63 00 04 */	addi r3, r3, 4
/* 801C3858 001C0438  38 A5 00 01 */	addi r5, r5, 1
/* 801C385C 001C043C  42 00 FF 68 */	bdnz lbl_801C37C4
lbl_801C3860:
/* 801C3860 001C0440  80 01 00 3C */	lwz r0, 0x3c(r1)
/* 801C3864 001C0444  83 E1 00 34 */	lwz r31, 0x34(r1)
/* 801C3868 001C0448  83 C1 00 30 */	lwz r30, 0x30(r1)
/* 801C386C 001C044C  83 A1 00 2C */	lwz r29, 0x2c(r1)
/* 801C3870 001C0450  83 81 00 28 */	lwz r28, 0x28(r1)
/* 801C3874 001C0454  38 21 00 38 */	addi r1, r1, 0x38
/* 801C3878 001C0458  7C 08 03 A6 */	mtlr r0
/* 801C387C 001C045C  4E 80 00 20 */	blr 
}
#pragma peephole on

void func_801C3880(f32 val)
{
    stage_info.cam_info.cam_bounds_top = val;
}

void func_801C3890(f32 val)
{
    stage_info.cam_info.cam_bounds_bottom = val;
}

void func_801C38A0(f32 val)
{
    stage_info.cam_info.cam_bounds_left = val;
}

void func_801C38AC(f32 val)
{
    stage_info.cam_info.cam_bounds_right = val;
}

void func_801C38BC(f32 x, f32 y)
{
    stage_info.cam_info.cam_x_offset = x;
    stage_info.cam_info.cam_y_offset = y;
}

void func_801C38D0(f32 tilt, f32 pan, f32 a, f32 b)
{
    stage_info.cam_info.cam_vertical_tilt = tilt;
    stage_info.cam_info.cam_pan_degrees = pan;
    stage_info.cam_info.x20 = a;
    stage_info.cam_info.x24 = b;
}

void func_801C38EC(f32 depth, f32 zoom)
{
    stage_info.cam_info.cam_max_depth = depth;
    stage_info.cam_info.cam_zoom_rate = zoom;
}

void func_801C3900(f32 arg8, f32 arg9, f32 argA, f32 argB,
                   f32 up, f32 down, f32 left, f32 right)
{
    stage_info.cam_info.x3C = arg8;
    stage_info.cam_info.pausecam_zpos_min = arg9;
    stage_info.cam_info.pausecam_zpos_init = argA;
    stage_info.cam_info.pausecam_zpos_max = argB;
    stage_info.cam_info.cam_angle_up = up;
    stage_info.cam_info.cam_angle_down = down;
    stage_info.cam_info.cam_angle_left = left;
    stage_info.cam_info.cam_angle_right = right;
}

void func_801C392C(f32 x, f32 y, f32 z, f32 fov, f32 vert, f32 horz)
{
    stage_info.cam_info.fixed_cam_pos.x = x;
    stage_info.cam_info.fixed_cam_pos.y = y;
    stage_info.cam_info.fixed_cam_pos.z = z;
    stage_info.cam_info.fixed_cam_fov = fov;
    stage_info.cam_info.fixed_cam_vert_angle = vert;
    stage_info.cam_info.fixed_cam_horz_angle = horz;
}

void func_801C3950(f32 zoom)
{
    stage_info.cam_info.cam_fixed_zoom = zoom;
}

void func_801C3960(f32 ratio)
{
    stage_info.cam_info.cam_track_ratio = ratio;
}

void func_801C3970(f32 smooth)
{
    stage_info.cam_info.cam_track_smooth = smooth;
}

void func_801C3980(f32 top)
{
    stage_info.blast_zone.top = top;
}

void func_801C3990(f32 bottom)
{
    stage_info.blast_zone.bottom = bottom;
}

void func_801C39A0(f32 left)
{
    stage_info.blast_zone.left = left;
}

void func_801C39B0(f32 right)
{
    stage_info.blast_zone.right = right;
}

void func_801C39C0(void)
{
    Vec3 sp20;
    Vec3 sp14;
    Vec3 sp8;
    f32 phi_f3;
    f32 phi_f4;
    f32 phi_f5;
    f32 phi_f0;
    f32 phi_f1;
    f32 phi_f2;

    if (func_801C2D24(0x95, &sp20) && func_801C2D24(0x96, &sp14) &&
        func_801C2D24(0x94, &sp8)) {
        if (sp20.x < sp14.x) {
            phi_f3 = sp20.x - sp8.x;
            phi_f4 = sp14.x - sp8.x;
        } else {
            phi_f3 = sp14.x - sp8.x;
            phi_f4 = sp20.x - sp8.x;
        }
        if (sp20.y < sp14.y) {
            phi_f5 = sp20.y - sp8.y;
            phi_f0 = sp14.y - sp8.y;
        } else {
            phi_f5 = sp14.y - sp8.y;
            phi_f0 = sp20.y - sp8.y;
        }
        phi_f1 = sp8.x;
        phi_f2 = sp8.y;
    } else {
        OSReport("use dummy CamRange ...!\n");
        switch (stage_info.internal_stage_id) {
        default:
            phi_f1 = 0;
            phi_f3 = -170;
            phi_f2 = 0;
            phi_f4 = 170;
            phi_f0 = 120;
            phi_f5 = -60;
            break;
        case 2:
            phi_f3 = -170;
            phi_f4 = 170;
            phi_f0 = 120;
            phi_f5 = -100;
            phi_f1 = 0;
            phi_f2 = 180;
            break;
        case 14:
            phi_f3 = -470;
            phi_f4 = 470;
            phi_f0 = 120;
            phi_f5 = -60;
            phi_f1 = 0;
            phi_f2 = 300;
            break;
        case 26:
            phi_f3 = -470;
            phi_f4 = 470;
            phi_f0 = 180;
            phi_f5 = -60;
            phi_f1 = 0;
            phi_f2 = 130;
            break;
        case 25:
            phi_f3 = -200;
            phi_f4 = 200;
            phi_f0 = 200;
            phi_f5 = -60;
            phi_f1 = 0;
            phi_f2 = 130;
            break;
        case 3:
            phi_f1 = 0;
            phi_f3 = -200;
            phi_f2 = 0;
            phi_f4 = 200;
            phi_f0 = 150;
            phi_f5 = -160;
            break;
        case 11:
            phi_f1 = 0;
            phi_f3 = -170;
            phi_f2 = 0;
            phi_f4 = 170;
            phi_f0 = 180;
            phi_f5 = -60;
            break;
        case 18:
            phi_f1 = 0;
            phi_f3 = -170;
            phi_f2 = 0;
            phi_f4 = 170;
            phi_f0 = 180;
            phi_f5 = 10;
            break;
        }
    }
    stage_info.cam_info.cam_bounds_top = phi_f0;
    stage_info.cam_info.cam_bounds_bottom = phi_f5;
    stage_info.cam_info.cam_bounds_left = phi_f3;
    stage_info.cam_info.cam_bounds_right = phi_f4;
    stage_info.cam_info.cam_x_offset = phi_f1;
    stage_info.cam_info.cam_y_offset = phi_f2;
}

void func_801C3BB4(void)
{
    Point3d sp1C;
    Point3d sp10;
    u32 unused[2];
    f32 top;
    f32 bot;
    f32 lft;
    f32 rgt;

    if (func_801C2D24(0x97, &sp1C) && func_801C2D24(0x98, &sp10)) {
        if (sp1C.x < sp10.x) {
            top = sp1C.x - stage_info.cam_info.cam_x_offset;
            bot = sp10.x - stage_info.cam_info.cam_x_offset;
        } else {
            top = sp10.x - stage_info.cam_info.cam_x_offset;
            bot = sp1C.x - stage_info.cam_info.cam_x_offset;
        }
        if (sp1C.y < sp10.y) {
            rgt = sp1C.y - stage_info.cam_info.cam_y_offset;
            lft = sp10.y - stage_info.cam_info.cam_y_offset;
        } else {
            rgt = sp10.y - stage_info.cam_info.cam_y_offset;
            lft = sp1C.y - stage_info.cam_info.cam_y_offset;
        }
    } else {
        OSReport("use dummy DeadRange ...\n");
        switch (stage_info.internal_stage_id) {
        default:
            top = -250;
            bot = 250;
            lft = 200;
            rgt = -100;
            break;
        case 2:
            top = -250;
            bot = 250;
            lft = 180;
            rgt = -150;
            break;
        case 14:
            top = -550;
            bot = 550;
            lft = 200;
            rgt = -100;
            break;
        case 26:
            top = -600;
            bot = 600;
            lft = 200;
            rgt = -100;
            break;
        case 7:
            top = -550;
            bot = 550;
            lft = 200;
            rgt = -150;
            break;
        case 25:
            top = -300;
            bot = 300;
            lft = 300;
            rgt = -160;
            break;
        case 3:
            top = -300;
            bot = 300;
            lft = 270;
            rgt = -240;
            break;
        case 11:
            top = -300;
            bot = 300;
            lft = 210;
            rgt = -240;
            break;
        }
    }
    stage_info.blast_zone.top = lft;
    stage_info.blast_zone.bottom = rgt;
    stage_info.blast_zone.left = top;
    stage_info.blast_zone.right = bot;
}

s32 func_801C3D44(s32 arg0, f32 arg8, f32 arg9)
{
    stage_info.unk8C.b6 = 1;
    stage_info.x70C = 0.5f * arg8;
    stage_info.x710 = 0.5f * arg9;
    stage_info.x90 = arg0;
    if (stage_info.x714 != -1) {
        stage_info.x84 |= 0x10;
        stage_info.x6D0 = stage_info.x714;
    } else {
        stage_info.x84 &= 0xFFFFFFEF;
    }
    return stage_info.x714;
}

s32 func_801C3DB4(s32 arg0, f32 arg8, f32 arg9)
{
    stage_info.unk8C.b7 = 1;
    stage_info.x718 = 0.5f * arg8;
    stage_info.x71C = 0.5f * arg9;
    stage_info.x94 = arg0;
    if (stage_info.x720 != -1) {
        stage_info.x84 |= 0x40;
    } else {
        stage_info.x84 &= 0xFFFFFFBF;
    }
    return stage_info.x720;
}

static HSD_AObj* func_801C3E18(HSD_JObj* jobj)
{
    HSD_AObj* result;
    if (jobj == NULL) {
        return NULL;
    }
    if (jobj->aobj != NULL) {
        return jobj->aobj;
    }
    result = func_801C3E18(jobj->child);
    if (result != NULL) {
        return result;
    }
    result = func_801C3E18(jobj->next);
    if (result != NULL) {
        return result;
    }
    return NULL;
}

f32 func_801C3F20(HSD_JObj* arg0)
{
    HSD_AObj* result = func_801C3E18(arg0);
    if (result != NULL) {
        return result->curr_frame;
    }
    return 0;
}

asm HSD_JObj* func_801C3FA4(HSD_GObj* gobj, s32 depth)
{
    nofralloc
/* 801C3FA4 001C0B84  80 63 00 28 */	lwz r3, 0x28(r3)
/* 801C3FA8 001C0B88  28 03 00 00 */	cmplwi r3, 0
/* 801C3FAC 001C0B8C  40 82 00 0C */	bne lbl_801C3FB8
/* 801C3FB0 001C0B90  38 60 00 00 */	li r3, 0
/* 801C3FB4 001C0B94  4E 80 00 20 */	blr 
lbl_801C3FB8:
/* 801C3FB8 001C0B98  40 82 00 0C */	bne lbl_801C3FC4
/* 801C3FBC 001C0B9C  38 60 00 00 */	li r3, 0
/* 801C3FC0 001C0BA0  48 00 00 08 */	b lbl_801C3FC8
lbl_801C3FC4:
/* 801C3FC4 001C0BA4  80 63 00 10 */	lwz r3, 0x10(r3)
lbl_801C3FC8:
/* 801C3FC8 001C0BA8  28 03 00 00 */	cmplwi r3, 0
/* 801C3FCC 001C0BAC  40 82 01 20 */	bne lbl_801C40EC
/* 801C3FD0 001C0BB0  38 60 00 00 */	li r3, 0
/* 801C3FD4 001C0BB4  4E 80 00 20 */	blr 
/* 801C3FD8 001C0BB8  48 00 01 14 */	b lbl_801C40EC
lbl_801C3FDC:
/* 801C3FDC 001C0BBC  80 03 00 14 */	lwz r0, 0x14(r3)
/* 801C3FE0 001C0BC0  38 84 FF FF */	addi r4, r4, -1
/* 801C3FE4 001C0BC4  54 00 04 E7 */	rlwinm. r0, r0, 0, 0x13, 0x13
/* 801C3FE8 001C0BC8  40 82 00 38 */	bne lbl_801C4020
/* 801C3FEC 001C0BCC  28 03 00 00 */	cmplwi r3, 0
/* 801C3FF0 001C0BD0  40 82 00 0C */	bne lbl_801C3FFC
/* 801C3FF4 001C0BD4  38 00 00 00 */	li r0, 0
/* 801C3FF8 001C0BD8  48 00 00 08 */	b lbl_801C4000
lbl_801C3FFC:
/* 801C3FFC 001C0BDC  80 03 00 10 */	lwz r0, 0x10(r3)
lbl_801C4000:
/* 801C4000 001C0BE0  28 00 00 00 */	cmplwi r0, 0
/* 801C4004 001C0BE4  41 82 00 1C */	beq lbl_801C4020
/* 801C4008 001C0BE8  28 03 00 00 */	cmplwi r3, 0
/* 801C400C 001C0BEC  40 82 00 0C */	bne lbl_801C4018
/* 801C4010 001C0BF0  38 60 00 00 */	li r3, 0
/* 801C4014 001C0BF4  48 00 00 D8 */	b lbl_801C40EC
lbl_801C4018:
/* 801C4018 001C0BF8  80 63 00 10 */	lwz r3, 0x10(r3)
/* 801C401C 001C0BFC  48 00 00 D0 */	b lbl_801C40EC
lbl_801C4020:
/* 801C4020 001C0C00  28 03 00 00 */	cmplwi r3, 0
/* 801C4024 001C0C04  40 82 00 0C */	bne lbl_801C4030
/* 801C4028 001C0C08  38 00 00 00 */	li r0, 0
/* 801C402C 001C0C0C  48 00 00 08 */	b lbl_801C4034
lbl_801C4030:
/* 801C4030 001C0C10  80 03 00 08 */	lwz r0, 8(r3)
lbl_801C4034:
/* 801C4034 001C0C14  28 00 00 00 */	cmplwi r0, 0
/* 801C4038 001C0C18  41 82 00 1C */	beq lbl_801C4054
/* 801C403C 001C0C1C  28 03 00 00 */	cmplwi r3, 0
/* 801C4040 001C0C20  40 82 00 0C */	bne lbl_801C404C
/* 801C4044 001C0C24  38 60 00 00 */	li r3, 0
/* 801C4048 001C0C28  48 00 00 A4 */	b lbl_801C40EC
lbl_801C404C:
/* 801C404C 001C0C2C  80 63 00 08 */	lwz r3, 8(r3)
/* 801C4050 001C0C30  48 00 00 9C */	b lbl_801C40EC
lbl_801C4054:
/* 801C4054 001C0C34  28 03 00 00 */	cmplwi r3, 0
/* 801C4058 001C0C38  40 82 00 0C */	bne lbl_801C4064
/* 801C405C 001C0C3C  38 00 00 00 */	li r0, 0
/* 801C4060 001C0C40  48 00 00 08 */	b lbl_801C4068
lbl_801C4064:
/* 801C4064 001C0C44  80 03 00 0C */	lwz r0, 0xc(r3)
lbl_801C4068:
/* 801C4068 001C0C48  28 00 00 00 */	cmplwi r0, 0
/* 801C406C 001C0C4C  40 82 00 0C */	bne lbl_801C4078
/* 801C4070 001C0C50  38 60 00 00 */	li r3, 0
/* 801C4074 001C0C54  48 00 00 78 */	b lbl_801C40EC
lbl_801C4078:
/* 801C4078 001C0C58  28 03 00 00 */	cmplwi r3, 0
/* 801C407C 001C0C5C  40 82 00 0C */	bne lbl_801C4088
/* 801C4080 001C0C60  38 A0 00 00 */	li r5, 0
/* 801C4084 001C0C64  48 00 00 08 */	b lbl_801C408C
lbl_801C4088:
/* 801C4088 001C0C68  80 A3 00 0C */	lwz r5, 0xc(r3)
lbl_801C408C:
/* 801C408C 001C0C6C  28 05 00 00 */	cmplwi r5, 0
/* 801C4090 001C0C70  40 82 00 0C */	bne lbl_801C409C
/* 801C4094 001C0C74  38 00 00 00 */	li r0, 0
/* 801C4098 001C0C78  48 00 00 08 */	b lbl_801C40A0
lbl_801C409C:
/* 801C409C 001C0C7C  80 05 00 08 */	lwz r0, 8(r5)
lbl_801C40A0:
/* 801C40A0 001C0C80  28 00 00 00 */	cmplwi r0, 0
/* 801C40A4 001C0C84  41 82 00 30 */	beq lbl_801C40D4
/* 801C40A8 001C0C88  28 03 00 00 */	cmplwi r3, 0
/* 801C40AC 001C0C8C  40 82 00 0C */	bne lbl_801C40B8
/* 801C40B0 001C0C90  38 60 00 00 */	li r3, 0
/* 801C40B4 001C0C94  48 00 00 08 */	b lbl_801C40BC
lbl_801C40B8:
/* 801C40B8 001C0C98  80 63 00 0C */	lwz r3, 0xc(r3)
lbl_801C40BC:
/* 801C40BC 001C0C9C  28 03 00 00 */	cmplwi r3, 0
/* 801C40C0 001C0CA0  40 82 00 0C */	bne lbl_801C40CC
/* 801C40C4 001C0CA4  38 60 00 00 */	li r3, 0
/* 801C40C8 001C0CA8  48 00 00 24 */	b lbl_801C40EC
lbl_801C40CC:
/* 801C40CC 001C0CAC  80 63 00 08 */	lwz r3, 8(r3)
/* 801C40D0 001C0CB0  48 00 00 1C */	b lbl_801C40EC
lbl_801C40D4:
/* 801C40D4 001C0CB4  28 03 00 00 */	cmplwi r3, 0
/* 801C40D8 001C0CB8  40 82 00 0C */	bne lbl_801C40E4
/* 801C40DC 001C0CBC  38 60 00 00 */	li r3, 0
/* 801C40E0 001C0CC0  4B FF FF 74 */	b lbl_801C4054
lbl_801C40E4:
/* 801C40E4 001C0CC4  80 63 00 0C */	lwz r3, 0xc(r3)
/* 801C40E8 001C0CC8  4B FF FF 6C */	b lbl_801C4054
lbl_801C40EC:
/* 801C40EC 001C0CCC  28 03 00 00 */	cmplwi r3, 0
/* 801C40F0 001C0CD0  4D 82 00 20 */	beqlr 
/* 801C40F4 001C0CD4  2C 04 00 00 */	cmpwi r4, 0
/* 801C40F8 001C0CD8  40 82 FE E4 */	bne lbl_801C3FDC
/* 801C40FC 001C0CDC  4E 80 00 20 */	blr 
}
#pragma peephole on

inline HSD_JObj* jobj_parent(HSD_JObj* jobj)
{
    if (jobj == NULL) {
        return NULL;
    }
    return jobj->parent;
}
inline HSD_JObj* jobj_child(HSD_JObj* jobj)
{
    if (jobj == NULL) {
        return NULL;
    }
    return jobj->child;
}
inline HSD_JObj* jobj_next(HSD_JObj* jobj)
{
    if (jobj == NULL) {
        return NULL;
    }
    return jobj->next;
}

HSD_JObj* func_801C4100(HSD_JObj* jobj)
{
    if (!(jobj->flags & JOBJ_INSTANCE) && jobj_child(jobj) != NULL) {
        return jobj_child(jobj);
    }
    if (jobj_next(jobj) != NULL) {
        return jobj_next(jobj);
    }
    while (1) {
        if (jobj_parent(jobj) == NULL) {
            return NULL;
        }
        if (jobj_next(jobj_parent(jobj)) != NULL) {
            return jobj_next(jobj_parent(jobj));
        }
        jobj = jobj_parent(jobj);
    }
}

#include <melee/it/code_80266F3C.h>
#include <melee/it/enums.h>

s32 func_801C4210(void)
{
    u32 unused;
    s32 count = 0;
    int i;
    for (i = 199; i < 220; i++) {
        if (stage_info.x280[i] != NULL &&
            func_8027B5B0(It_Kind_Mato, 0, stage_info.x280[i], 0, 0) != NULL) {
            count++;
        }
    }
    stage_info.x6D4 = count;
    stage_info.x6D2 = count;
    return count;
}

void func_801C42AC(void)
{
    struct {
        u8 x0_pad[4];
        void* x4;
        Vec3 x8;
        s32 x14;
        u8 x18_pad[4];
        struct {
            u8 b0 : 1;
        } x1C;
    } sp8;
    HSD_JObj* jobj;
    int i;

    for (i = 0xFC; i < 0x104; i++) {
        jobj = stage_info.x280[i];
        if (jobj != NULL) {
            sp8.x14 = 0x14;
            sp8.x4 = jobj;
            sp8.x1C.b0 = 1;
            func_8026BE84(&sp8);
        }
    }
}

void func_801C4338(void)
{
    stage_info.x6D4--;
    if (stage_info.x6D4 == 0) {
        stage_info.x84 |= 0x20;
    }
}

void func_801C4368(f32* arg0, f32* arg1)
{
    *arg0 = stage_info.x724;
    *arg1 = stage_info.x724 - stage_info.x728;
}

void func_801C438C(f32 val)
{
    stage_info.x728 = stage_info.x724;
    stage_info.x724 = val;
}

void func_801C43A4(void* unk)
{
    func_801DA3F4(unk);
}

BOOL func_801C43C4(void* arg0)
{
    UnkStageDat* tmp;
    s32 max;
    struct {
        void* unk0;
        u8 flag : 1;
    }* phi_r4;
    int i;

    tmp = func_801C6324()->unk4;
    phi_r4 = tmp->unk20;
    max = tmp->unk24;
    if (arg0 != NULL && max != 0) {
        for (i = 0; i != max; i++) {
            if (phi_r4->unk0 == arg0) {
                if (phi_r4->flag) {
                    return TRUE;
                } else {
                    return FALSE;
                }
            }
            phi_r4++;
        }
        assert_line(3652, 0);
    }
    return FALSE;
}

void func_801C445C(HSD_LObj* lobj)
{
    Vec3 sp38;
    Vec3 sp2C;
    Vec3 sp20;
    Vec3 sp14;
    u32 unused[1];
    HSD_WObj* wobj;
    HSD_LObj* cur;
    f32 phi_f1;

    if (lobj == NULL) {
        return;
    }
    for (cur = lobj; cur != NULL; cur = cur->next) {

        wobj = HSD_LObjGetPositionWObj(lobj);
        if (wobj != NULL) {
            HSD_WObjGetPosition(wobj, &sp38);
        }

        wobj = HSD_LObjGetInterestWObj(lobj);
        if (wobj != NULL) {
            HSD_WObjGetPosition(wobj, &sp20);
        }

        HSD_LObjAnim(cur);

        wobj = HSD_LObjGetPositionWObj(lobj);
        if (wobj != NULL) {
            HSD_WObjGetPosition(wobj, &sp2C);
            if (sp38.x != sp2C.x || sp38.y != sp2C.y || sp38.z != sp2C.z) {
                phi_f1 = stage_info.x6B0 != NULL ? stage_info.x6B0->x0 : 1;
                sp2C.x *= phi_f1;
                sp2C.y *= phi_f1;
                sp2C.z *= phi_f1;
                HSD_WObjSetPosition(wobj, &sp2C);
            }
        }

        wobj = HSD_LObjGetInterestWObj(lobj);
        if (wobj != NULL) {
            HSD_WObjGetPosition(wobj, &sp14);
            if (sp20.x != sp14.x || sp20.y != sp14.y || sp20.z != sp14.z) {
                phi_f1 = stage_info.x6B0 != NULL ? stage_info.x6B0->x0 : 1;
                sp14.x *= phi_f1;
                sp14.y *= phi_f1;
                sp14.z *= phi_f1;
                HSD_WObjSetPosition(wobj, &sp14);
            }
        }
    }
}

static void lbl_801C461C(HSD_GObj* gobj)
{
    func_801C445C(gobj->hsd_obj);
}

static void lbl_801C4640(HSD_GObj* gobj)
{
    func_803668EC(gobj->hsd_obj);
    HSD_LObjSetupInit(HSD_CObjGetCurrent());
}

#include <sysdolphin/baselib/aobj.h>

static asm void func_801C466C(void)
{
    nofralloc
/* 801C466C 001C124C  7C 08 02 A6 */	mflr r0
/* 801C4670 001C1250  3C 60 80 3E */	lis r3, lbl_803DFEA8@ha
/* 801C4674 001C1254  90 01 00 04 */	stw r0, 4(r1)
/* 801C4678 001C1258  94 21 FF C0 */	stwu r1, -0x40(r1)
/* 801C467C 001C125C  DB E1 00 38 */	stfd f31, 0x38(r1)
/* 801C4680 001C1260  BF 41 00 20 */	stmw r26, 0x20(r1)
/* 801C4684 001C1264  3B E3 FE A8 */	addi r31, r3, lbl_803DFEA8@l
/* 801C4688 001C1268  48 00 1C 9D */	bl func_801C6324
/* 801C468C 001C126C  3C 80 80 4A */	lis r4, stage_info@ha
/* 801C4690 001C1270  80 63 00 04 */	lwz r3, 4(r3)
/* 801C4694 001C1274  38 84 E6 C8 */	addi r4, r4, stage_info@l
/* 801C4698 001C1278  80 04 00 88 */	lwz r0, 0x88(r4)
/* 801C469C 001C127C  83 83 00 0C */	lwz r28, 0xc(r3)
/* 801C46A0 001C1280  54 00 10 3A */	slwi r0, r0, 2
/* 801C46A4 001C1284  7C 7F 02 14 */	add r3, r31, r0
/* 801C46A8 001C1288  80 63 00 34 */	lwz r3, 0x34(r3)
/* 801C46AC 001C128C  83 43 00 04 */	lwz r26, 4(r3)
/* 801C46B0 001C1290  48 00 1C 75 */	bl func_801C6324
/* 801C46B4 001C1294  2C 1C 00 00 */	cmpwi r28, 0
/* 801C46B8 001C1298  7F 89 03 A6 */	mtctr r28
/* 801C46BC 001C129C  3B 80 00 00 */	li r28, 0
/* 801C46C0 001C12A0  40 81 00 44 */	ble lbl_801C4704
lbl_801C46C4:
/* 801C46C4 001C12A4  88 1A 00 10 */	lbz r0, 0x10(r26)
/* 801C46C8 001C12A8  54 00 CF FE */	rlwinm r0, r0, 0x19, 0x1f, 0x1f
/* 801C46CC 001C12AC  28 00 00 01 */	cmplwi r0, 1
/* 801C46D0 001C12B0  40 82 00 28 */	bne lbl_801C46F8
/* 801C46D4 001C12B4  7F 83 E3 78 */	mr r3, r28
/* 801C46D8 001C12B8  48 00 1C 59 */	bl func_801C6330
/* 801C46DC 001C12BC  80 83 00 04 */	lwz r4, 4(r3)
/* 801C46E0 001C12C0  1C 1C 00 34 */	mulli r0, r28, 0x34
/* 801C46E4 001C12C4  80 84 00 08 */	lwz r4, 8(r4)
/* 801C46E8 001C12C8  7C 84 02 14 */	add r4, r4, r0
/* 801C46EC 001C12CC  80 84 00 18 */	lwz r4, 0x18(r4)
/* 801C46F0 001C12D0  4B FF D9 F1 */	bl func_801C20E0
/* 801C46F4 001C12D4  48 00 00 14 */	b lbl_801C4708
lbl_801C46F8:
/* 801C46F8 001C12D8  3B 5A 00 14 */	addi r26, r26, 0x14
/* 801C46FC 001C12DC  3B 9C 00 01 */	addi r28, r28, 1
/* 801C4700 001C12E0  42 00 FF C4 */	bdnz lbl_801C46C4
lbl_801C4704:
/* 801C4704 001C12E4  38 60 00 00 */	li r3, 0
lbl_801C4708:
/* 801C4708 001C12E8  7C 7C 1B 79 */	or. r28, r3, r3
/* 801C470C 001C12EC  40 82 00 08 */	bne lbl_801C4714
/* 801C4710 001C12F0  3B 9F 08 20 */	addi r28, r31, 0x820
lbl_801C4714:
/* 801C4714 001C12F4  38 60 00 0D */	li r3, 0xd
/* 801C4718 001C12F8  38 80 00 03 */	li r4, 3
/* 801C471C 001C12FC  38 A0 00 00 */	li r5, 0
/* 801C4720 001C1300  48 1C BA D1 */	bl func_803901F0
/* 801C4724 001C1304  7C 7E 1B 79 */	or. r30, r3, r3
/* 801C4728 001C1308  40 82 00 1C */	bne lbl_801C4744
/* 801C472C 001C130C  38 7F 08 2C */	addi r3, r31, 0x82c
/* 801C4730 001C1310  4C C6 31 82 */	crclr 6
/* 801C4734 001C1314  38 9F 02 18 */	addi r4, r31, 0x218
/* 801C4738 001C1318  38 A0 0E AF */	li r5, 0xeaf
/* 801C473C 001C131C  48 18 0F 6D */	bl OSReport
lbl_801C4740:
/* 801C4740 001C1320  48 00 00 00 */	b lbl_801C4740
lbl_801C4744:
/* 801C4744 001C1324  7F 83 E3 78 */	mr r3, r28
/* 801C4748 001C1328  4B E4 D3 7D */	bl func_80011AC4
/* 801C474C 001C132C  7C 7D 1B 79 */	or. r29, r3, r3
/* 801C4750 001C1330  40 82 00 1C */	bne lbl_801C476C
/* 801C4754 001C1334  38 7F 08 48 */	addi r3, r31, 0x848
/* 801C4758 001C1338  4C C6 31 82 */	crclr 6
/* 801C475C 001C133C  38 9F 02 18 */	addi r4, r31, 0x218
/* 801C4760 001C1340  38 A0 0E B1 */	li r5, 0xeb1
/* 801C4764 001C1344  48 18 0F 45 */	bl OSReport
lbl_801C4768:
/* 801C4768 001C1348  48 00 00 00 */	b lbl_801C4768
lbl_801C476C:
/* 801C476C 001C134C  88 8D C1 AA */	lbz r4, lbl_804D784A
/* 801C4770 001C1350  38 7E 00 00 */	addi r3, r30, 0
/* 801C4774 001C1354  38 BD 00 00 */	addi r5, r29, 0
/* 801C4778 001C1358  48 1C C2 F9 */	bl func_80390A70
/* 801C477C 001C135C  3C 60 80 1C */	lis r3, lbl_801C4640@ha
/* 801C4780 001C1360  38 83 46 40 */	addi r4, r3, lbl_801C4640@l
/* 801C4784 001C1364  38 7E 00 00 */	addi r3, r30, 0
/* 801C4788 001C1368  38 A0 00 00 */	li r5, 0
/* 801C478C 001C136C  38 C0 00 00 */	li r6, 0
/* 801C4790 001C1370  48 1C BF 0D */	bl GObj_SetupGXLink
/* 801C4794 001C1374  3C 60 80 4A */	lis r3, stage_info@ha
/* 801C4798 001C1378  38 63 E6 C8 */	addi r3, r3, stage_info@l
/* 801C479C 001C137C  80 63 06 B0 */	lwz r3, 0x6b0(r3)
/* 801C47A0 001C1380  3B 7D 00 00 */	addi r27, r29, 0
/* 801C47A4 001C1384  28 03 00 00 */	cmplwi r3, 0
/* 801C47A8 001C1388  41 82 00 0C */	beq lbl_801C47B4
/* 801C47AC 001C138C  C3 E3 00 00 */	lfs f31, 0(r3)
/* 801C47B0 001C1390  48 00 00 08 */	b lbl_801C47B8
lbl_801C47B4:
/* 801C47B4 001C1394  C3 E2 B2 E4 */	lfs f31, 1.0f
lbl_801C47B8:
/* 801C47B8 001C1398  3B 41 00 10 */	addi r26, r1, 0x10
/* 801C47BC 001C139C  48 00 00 A0 */	b lbl_801C485C
lbl_801C47C0:
/* 801C47C0 001C13A0  38 7B 00 00 */	addi r3, r27, 0
/* 801C47C4 001C13A4  38 81 00 10 */	addi r4, r1, 0x10
/* 801C47C8 001C13A8  48 1A 25 A9 */	bl HSD_LObjGetPosition
/* 801C47CC 001C13AC  2C 03 00 00 */	cmpwi r3, 0
/* 801C47D0 001C13B0  41 82 00 34 */	beq lbl_801C4804
/* 801C47D4 001C13B4  C0 01 00 10 */	lfs f0, 0x10(r1)
/* 801C47D8 001C13B8  38 7B 00 00 */	addi r3, r27, 0
/* 801C47DC 001C13BC  38 9A 00 00 */	addi r4, r26, 0
/* 801C47E0 001C13C0  EC 00 07 F2 */	fmuls f0, f0, f31
/* 801C47E4 001C13C4  D0 01 00 10 */	stfs f0, 0x10(r1)
/* 801C47E8 001C13C8  C0 01 00 14 */	lfs f0, 0x14(r1)
/* 801C47EC 001C13CC  EC 00 07 F2 */	fmuls f0, f0, f31
/* 801C47F0 001C13D0  D0 01 00 14 */	stfs f0, 0x14(r1)
/* 801C47F4 001C13D4  C0 01 00 18 */	lfs f0, 0x18(r1)
/* 801C47F8 001C13D8  EC 00 07 F2 */	fmuls f0, f0, f31
/* 801C47FC 001C13DC  D0 01 00 18 */	stfs f0, 0x18(r1)
/* 801C4800 001C13E0  48 1A 24 E9 */	bl HSD_LObjSetPosition
lbl_801C4804:
/* 801C4804 001C13E4  38 7B 00 00 */	addi r3, r27, 0
/* 801C4808 001C13E8  38 81 00 10 */	addi r4, r1, 0x10
/* 801C480C 001C13EC  48 1A 26 2D */	bl HSD_LObjGetInterest
/* 801C4810 001C13F0  2C 03 00 00 */	cmpwi r3, 0
/* 801C4814 001C13F4  41 82 00 34 */	beq lbl_801C4848
/* 801C4818 001C13F8  C0 01 00 10 */	lfs f0, 0x10(r1)
/* 801C481C 001C13FC  38 7B 00 00 */	addi r3, r27, 0
/* 801C4820 001C1400  38 9A 00 00 */	addi r4, r26, 0
/* 801C4824 001C1404  EC 00 07 F2 */	fmuls f0, f0, f31
/* 801C4828 001C1408  D0 01 00 10 */	stfs f0, 0x10(r1)
/* 801C482C 001C140C  C0 01 00 14 */	lfs f0, 0x14(r1)
/* 801C4830 001C1410  EC 00 07 F2 */	fmuls f0, f0, f31
/* 801C4834 001C1414  D0 01 00 14 */	stfs f0, 0x14(r1)
/* 801C4838 001C1418  C0 01 00 18 */	lfs f0, 0x18(r1)
/* 801C483C 001C141C  EC 00 07 F2 */	fmuls f0, f0, f31
/* 801C4840 001C1420  D0 01 00 18 */	stfs f0, 0x18(r1)
/* 801C4844 001C1424  48 1A 25 6D */	bl HSD_LObjSetInterest
lbl_801C4848:
/* 801C4848 001C1428  28 1B 00 00 */	cmplwi r27, 0
/* 801C484C 001C142C  40 82 00 0C */	bne lbl_801C4858
/* 801C4850 001C1430  3B 60 00 00 */	li r27, 0
/* 801C4854 001C1434  48 00 00 08 */	b lbl_801C485C
lbl_801C4858:
/* 801C4858 001C1438  83 7B 00 0C */	lwz r27, 0xc(r27)
lbl_801C485C:
/* 801C485C 001C143C  28 1B 00 00 */	cmplwi r27, 0
/* 801C4860 001C1440  40 82 FF 60 */	bne lbl_801C47C0
/* 801C4864 001C1444  7F A3 EB 78 */	mr r3, r29
/* 801C4868 001C1448  C0 22 B2 C4 */	lfs f1, 0.0f
/* 801C486C 001C144C  48 1A 0E 8D */	bl HSD_LObjReqAnimAll
/* 801C4870 001C1450  3C 60 80 36 */	lis r3, HSD_AObjSetRate@ha
/* 801C4874 001C1454  C8 22 B3 58 */	lfd f1, 1.0
/* 801C4878 001C1458  3F E0 00 01 */	lis r31, 0x0000FFFF@ha
/* 801C487C 001C145C  4C C6 32 42 */	crset 6
/* 801C4880 001C1460  38 C3 53 0C */	addi r6, r3, HSD_AObjSetRate@l
/* 801C4884 001C1464  38 7D 00 00 */	addi r3, r29, 0
/* 801C4888 001C1468  38 BF FF FF */	addi r5, r31, 0x0000FFFF@l
/* 801C488C 001C146C  38 80 00 07 */	li r4, 7
/* 801C4890 001C1470  38 E0 00 01 */	li r7, 1
/* 801C4894 001C1474  48 1A 03 75 */	bl HSD_ForeachAnim
/* 801C4898 001C1478  80 7C 00 00 */	lwz r3, 0(r28)
/* 801C489C 001C147C  3B 7C 00 00 */	addi r27, r28, 0
/* 801C48A0 001C1480  3B 5D 00 00 */	addi r26, r29, 0
/* 801C48A4 001C1484  80 03 00 04 */	lwz r0, 4(r3)
/* 801C48A8 001C1488  28 00 00 00 */	cmplwi r0, 0
/* 801C48AC 001C148C  41 82 00 AC */	beq lbl_801C4958
/* 801C48B0 001C1490  3C 60 80 36 */	lis r3, HSD_AObjSetFlags@ha
/* 801C48B4 001C1494  3B 83 40 1C */	addi r28, r3, HSD_AObjSetFlags@l
/* 801C48B8 001C1498  48 00 00 98 */	b lbl_801C4950
lbl_801C48BC:
/* 801C48BC 001C149C  80 7B 00 00 */	lwz r3, 0(r27)
/* 801C48C0 001C14A0  80 63 00 04 */	lwz r3, 4(r3)
/* 801C48C4 001C14A4  80 63 00 00 */	lwz r3, 0(r3)
/* 801C48C8 001C14A8  4B FF FA FD */	bl func_801C43C4
/* 801C48CC 001C14AC  2C 03 00 00 */	cmpwi r3, 0
/* 801C48D0 001C14B0  41 82 00 68 */	beq lbl_801C4938
/* 801C48D4 001C14B4  80 7A 00 48 */	lwz r3, 0x48(r26)
/* 801C48D8 001C14B8  28 03 00 00 */	cmplwi r3, 0
/* 801C48DC 001C14BC  41 82 00 0C */	beq lbl_801C48E8
/* 801C48E0 001C14C0  3C 80 20 00 */	lis r4, 0x2000
/* 801C48E4 001C14C4  48 19 F7 39 */	bl HSD_AObjSetFlags
lbl_801C48E8:
/* 801C48E8 001C14C8  80 7A 00 18 */	lwz r3, 0x18(r26)
/* 801C48EC 001C14CC  28 03 00 00 */	cmplwi r3, 0
/* 801C48F0 001C14D0  41 82 00 20 */	beq lbl_801C4910
/* 801C48F4 001C14D4  4C C6 31 82 */	crclr 6
/* 801C48F8 001C14D8  38 DC 00 00 */	addi r6, r28, 0
/* 801C48FC 001C14DC  38 BF FF FF */	addi r5, r31, -1
/* 801C4900 001C14E0  38 80 00 0C */	li r4, 0xc
/* 801C4904 001C14E4  38 E0 00 03 */	li r7, 3
/* 801C4908 001C14E8  3D 00 20 00 */	lis r8, 0x2000
/* 801C490C 001C14EC  48 1A 02 FD */	bl HSD_ForeachAnim
lbl_801C4910:
/* 801C4910 001C14F0  80 7A 00 1C */	lwz r3, 0x1c(r26)
/* 801C4914 001C14F4  28 03 00 00 */	cmplwi r3, 0
/* 801C4918 001C14F8  41 82 00 20 */	beq lbl_801C4938
/* 801C491C 001C14FC  4C C6 31 82 */	crclr 6
/* 801C4920 001C1500  38 DC 00 00 */	addi r6, r28, 0
/* 801C4924 001C1504  38 BF FF FF */	addi r5, r31, -1
/* 801C4928 001C1508  38 80 00 0C */	li r4, 0xc
/* 801C492C 001C150C  38 E0 00 03 */	li r7, 3
/* 801C4930 001C1510  3D 00 20 00 */	lis r8, 0x2000
/* 801C4934 001C1514  48 1A 02 D5 */	bl HSD_ForeachAnim
lbl_801C4938:
/* 801C4938 001C1518  28 1A 00 00 */	cmplwi r26, 0
/* 801C493C 001C151C  40 82 00 0C */	bne lbl_801C4948
/* 801C4940 001C1520  3B 40 00 00 */	li r26, 0
/* 801C4944 001C1524  48 00 00 08 */	b lbl_801C494C
lbl_801C4948:
/* 801C4948 001C1528  83 5A 00 0C */	lwz r26, 0xc(r26)
lbl_801C494C:
/* 801C494C 001C152C  3B 7B 00 04 */	addi r27, r27, 4
lbl_801C4950:
/* 801C4950 001C1530  28 1A 00 00 */	cmplwi r26, 0
/* 801C4954 001C1534  40 82 FF 68 */	bne lbl_801C48BC
lbl_801C4958:
/* 801C4958 001C1538  7F A3 EB 78 */	mr r3, r29
/* 801C495C 001C153C  48 1A 0D 1D */	bl HSD_LObjAnimAll
/* 801C4960 001C1540  3C 60 80 1C */	lis r3, lbl_801C461C@ha
/* 801C4964 001C1544  38 83 46 1C */	addi r4, r3, lbl_801C461C@l
/* 801C4968 001C1548  38 7E 00 00 */	addi r3, r30, 0
/* 801C496C 001C154C  38 A0 00 00 */	li r5, 0
/* 801C4970 001C1550  48 1C B3 E5 */	bl func_8038FD54
/* 801C4974 001C1554  BB 41 00 20 */	lmw r26, 0x20(r1)
/* 801C4978 001C1558  80 01 00 44 */	lwz r0, 0x44(r1)
/* 801C497C 001C155C  CB E1 00 38 */	lfd f31, 0x38(r1)
/* 801C4980 001C1560  38 21 00 40 */	addi r1, r1, 0x40
/* 801C4984 001C1564  7C 08 03 A6 */	mtlr r0
/* 801C4988 001C1568  4E 80 00 20 */	blr 
}
#pragma peephole on

HSD_GObj* func_801C498C(void)
{
    HSD_GObj* gobj;
    for (gobj = lbl_804D782C->xC; gobj != NULL; gobj = gobj->next) {
        if (gobj->classifier == 13) {
            break;
        }
    }
    return gobj;
}

extern void* lbl_803E06C8[]; // unknown type

unk_t func_801C49B4(void)
{
    UnkArchiveStruct* archive = func_801C6324();
    if (stage_info.x6C4 != NULL) {
        return func_801C20E0(archive, stage_info.x6C4);
    }
    return &lbl_803E06C8;
}

void* func_801C49F8(void)
{
    return stage_info.x6C0;
}

inline void remove_stage_gobj(HSD_GObj* gobj)
{
    void* obj = gobj->hsd_obj;
    int i;
    for (i = 0; i < 4; i++) {
        if (stage_info.x694[i] == obj) {
            stage_info.x694[i] = NULL;
            break;
        }
    }
}

// Stage destroy map gobj
void func_801C4A08(HSD_GObj* gobj)
{
    UnkArchiveStruct* archive;
    Map* gp;
    HSD_JObj* jobj;
    s32 map_id;
    u32 unused[6];

    if (gobj == NULL) {
        return;
    }
    gp = gobj->user_data;
    jobj = gobj->hsd_obj;
    if (gp != NULL) {
        map_id = gp->map_id;
        if (gp->x1C_callback != NULL) {
            gp->x1C_callback(gobj);
        }
        if (stage_info.x180[map_id] == gobj) {
            stage_info.x180[map_id] = NULL;
        }
        func_801C55AC(gp);
        if (gp->x18 != NULL) {
            remove_stage_gobj(gp->x18);
            func_80390228(gp->x18);
        }
        if (gobj->hsd_obj != NULL && lbl_804D6950[map_id] == 0) {
            lbl_804D6950[map_id] = 1;
            func_801C3128(map_id, func_80057BC0);
        }
        archive = func_801C6330(gp->map_id);
        if (archive != NULL) {
            func_801C36F4(gp->map_id, jobj, archive->unk4->unk8[map_id].unk0);
        }
    }
    func_80390228(gobj);
}

#include <math.h>

void func_801C4B50(s32 arg0, s32 arg1, Vec3* arg2, f32 arg8)
{
    Vec3 sp30;
    Vec3 sp24;
    Vec3 sp18;
    f32 result_x;
    f32 phi_f31;
    f32 result_y;
    f32 result_z;
    f32 phi_f2;
    f32 phi_f1;

    splGetSplinePoint(arg1, arg0);
    func_8000E9F0(&sp30, arg0, arg8);
    lbvector_Normalize(&sp30);
    phi_f1 = sp30.y;
    if (sp30.y < 0) {
        phi_f1 = -sp30.y;
    }
    if (phi_f1 > 0.9) {
        sp18.x = sp18.y = 0;
        sp18.z = 1;
    } else {
        sp18.x = sp18.z = 0;
        sp18.y = 1;
    }
    lbvector_CrossprodNormalized(&sp30, &sp18, &sp24);
    lbvector_CrossprodNormalized(&sp24, &sp30, &sp18);
    result_y = func_80022DBC(sp24.z);
    phi_f2 = sp24.z;
    if (sp24.z < 0) {
        phi_f2 = -sp24.z;
    }
    if (phi_f2 >= 0.99999f) {
        phi_f31 = func_80022DBC(-sp30.y);
        if (sp30.x * cosf(phi_f31) * sinf(result_y) < 0) {
            phi_f31 = M_PI - phi_f31;
        }
        result_x = phi_f31;
        result_z = 0;
    } else {
        result_x = func_80022DBC(sp18.z / cosf(result_y));
        if (sp30.z * cosf(result_x) * cosf(result_y) < 0) {
            result_x = M_PI - result_x;
        }
        result_z = func_80022DBC(-sp24.y / cosf(result_y));
        if (-sp24.x * cosf(result_y) * cosf(result_z) < 0) {
            result_z = M_PI - result_z;
        }
    }
    arg2->x = result_x;
    arg2->y = result_y;
    arg2->z = result_z;
}

BOOL func_801C4D70(s32 arg0, Vec3* arg1, f32 arg8)
{
    stage_info.x72C = arg0;
    stage_info.x730 = *arg1;
    stage_info.x73C = arg8;
    return TRUE;
}

BOOL func_801C4DA0(Vec3* arg0, f32* arg1)
{
    *arg0 = stage_info.x730;
    *arg1 = stage_info.x73C;
    return TRUE;
}

BOOL func_801C4DD0(void)
{
    s32 stage_id = stage_info.internal_stage_id;
    if (stage_id == 4) {
        func_801D8270(stage_info.x72C);
    } else if (stage_id == 30) {
        func_802105AC(stage_info.x72C);
    }
    return TRUE;
}

BOOL func_801C4E20(void)
{
    s32 stage_id = stage_info.internal_stage_id;
    if (stage_id == 4) {
        func_801D828C(stage_info.x72C);
    } else if (stage_id == 30) {
        func_802105C8(stage_info.x72C);
    }
    return TRUE;
}

void func_801C4E70(HSD_JObj* arg0, HSD_JObj* arg1, HSD_JObj* arg2,
                   HSD_JObj* arg3, HSD_JObj* arg4, HSD_JObj* arg5)
{
    Vec3 sp20;
    stage_info.unk8C.b3 = 1;
    func_8000B1CC(arg0, NULL, &sp20);
    stage_info.x130 = sp20;
    func_8000B1CC(arg1, NULL, &sp20);
    stage_info.x13C = sp20;
    func_8000B1CC(arg2, NULL, &sp20);
    stage_info.x148 = sp20;
    func_8000B1CC(arg3, NULL, &sp20);
    stage_info.x154 = sp20;
    func_8000B1CC(arg4, NULL, &sp20);
    stage_info.x160 = sp20;
    func_8000B1CC(arg5, NULL, &sp20);
    stage_info.x16C = sp20;
}

extern char lbl_804D4524[8];
extern char lbl_804D452C[8];
extern void func_80368784();
extern void func_8036885C();
asm void func_801C4FAC()
{
    nofralloc
/* 801C4FAC 001C1B8C  7C 08 02 A6 */	mflr r0
/* 801C4FB0 001C1B90  3C 80 80 4A */	lis r4, stage_info@ha
/* 801C4FB4 001C1B94  90 01 00 04 */	stw r0, 4(r1)
/* 801C4FB8 001C1B98  94 21 FF 68 */	stwu r1, -0x98(r1)
/* 801C4FBC 001C1B9C  DB E1 00 90 */	stfd f31, 0x90(r1)
/* 801C4FC0 001C1BA0  DB C1 00 88 */	stfd f30, 0x88(r1)
/* 801C4FC4 001C1BA4  93 E1 00 84 */	stw r31, 0x84(r1)
/* 801C4FC8 001C1BA8  3B E4 E6 C8 */	addi r31, r4, stage_info@l
/* 801C4FCC 001C1BAC  93 C1 00 80 */	stw r30, 0x80(r1)
/* 801C4FD0 001C1BB0  3B C3 00 00 */	addi r30, r3, 0
/* 801C4FD4 001C1BB4  88 1F 00 8C */	lbz r0, 0x8c(r31)
/* 801C4FD8 001C1BB8  54 00 E7 FF */	rlwinm. r0, r0, 0x1c, 0x1f, 0x1f
/* 801C4FDC 001C1BBC  41 82 03 F0 */	beq lbl_801C53CC
/* 801C4FE0 001C1BC0  38 7E 00 00 */	addi r3, r30, 0
/* 801C4FE4 001C1BC4  38 81 00 74 */	addi r4, r1, 0x74
/* 801C4FE8 001C1BC8  48 1A 38 75 */	bl func_8036885C
/* 801C4FEC 001C1BCC  80 7F 01 30 */	lwz r3, 0x130(r31)
/* 801C4FF0 001C1BD0  80 1F 01 34 */	lwz r0, 0x134(r31)
/* 801C4FF4 001C1BD4  C0 41 00 74 */	lfs f2, 0x74(r1)
/* 801C4FF8 001C1BD8  90 61 00 68 */	stw r3, 0x68(r1)
/* 801C4FFC 001C1BDC  C0 02 B2 C4 */	lfs f0, 0.0f
/* 801C5000 001C1BE0  90 01 00 6C */	stw r0, 0x6c(r1)
/* 801C5004 001C1BE4  FC 02 00 40 */	fcmpo cr0, f2, f0
/* 801C5008 001C1BE8  80 1F 01 38 */	lwz r0, 0x138(r31)
/* 801C500C 001C1BEC  90 01 00 70 */	stw r0, 0x70(r1)
/* 801C5010 001C1BF0  80 7F 01 3C */	lwz r3, 0x13c(r31)
/* 801C5014 001C1BF4  80 1F 01 40 */	lwz r0, 0x140(r31)
/* 801C5018 001C1BF8  90 61 00 5C */	stw r3, 0x5c(r1)
/* 801C501C 001C1BFC  90 01 00 60 */	stw r0, 0x60(r1)
/* 801C5020 001C1C00  80 1F 01 44 */	lwz r0, 0x144(r31)
/* 801C5024 001C1C04  90 01 00 64 */	stw r0, 0x64(r1)
/* 801C5028 001C1C08  40 80 00 38 */	bge lbl_801C5060
/* 801C502C 001C1C0C  80 7F 01 48 */	lwz r3, 0x148(r31)
/* 801C5030 001C1C10  80 1F 01 4C */	lwz r0, 0x14c(r31)
/* 801C5034 001C1C14  90 61 00 50 */	stw r3, 0x50(r1)
/* 801C5038 001C1C18  90 01 00 54 */	stw r0, 0x54(r1)
/* 801C503C 001C1C1C  80 1F 01 50 */	lwz r0, 0x150(r31)
/* 801C5040 001C1C20  90 01 00 58 */	stw r0, 0x58(r1)
/* 801C5044 001C1C24  80 7F 01 54 */	lwz r3, 0x154(r31)
/* 801C5048 001C1C28  80 1F 01 58 */	lwz r0, 0x158(r31)
/* 801C504C 001C1C2C  90 61 00 44 */	stw r3, 0x44(r1)
/* 801C5050 001C1C30  90 01 00 48 */	stw r0, 0x48(r1)
/* 801C5054 001C1C34  80 1F 01 5C */	lwz r0, 0x15c(r31)
/* 801C5058 001C1C38  90 01 00 4C */	stw r0, 0x4c(r1)
/* 801C505C 001C1C3C  48 00 00 34 */	b lbl_801C5090
lbl_801C5060:
/* 801C5060 001C1C40  80 7F 01 60 */	lwz r3, 0x160(r31)
/* 801C5064 001C1C44  80 1F 01 64 */	lwz r0, 0x164(r31)
/* 801C5068 001C1C48  90 61 00 50 */	stw r3, 0x50(r1)
/* 801C506C 001C1C4C  90 01 00 54 */	stw r0, 0x54(r1)
/* 801C5070 001C1C50  80 1F 01 68 */	lwz r0, 0x168(r31)
/* 801C5074 001C1C54  90 01 00 58 */	stw r0, 0x58(r1)
/* 801C5078 001C1C58  80 7F 01 6C */	lwz r3, 0x16c(r31)
/* 801C507C 001C1C5C  80 1F 01 70 */	lwz r0, 0x170(r31)
/* 801C5080 001C1C60  90 61 00 44 */	stw r3, 0x44(r1)
/* 801C5084 001C1C64  90 01 00 48 */	stw r0, 0x48(r1)
/* 801C5088 001C1C68  80 1F 01 74 */	lwz r0, 0x174(r31)
/* 801C508C 001C1C6C  90 01 00 4C */	stw r0, 0x4c(r1)
lbl_801C5090:
/* 801C5090 001C1C70  C0 01 00 7C */	lfs f0, 0x7c(r1)
/* 801C5094 001C1C74  C0 22 B2 C4 */	lfs f1, 0.0f
/* 801C5098 001C1C78  FC 00 08 40 */	fcmpo cr0, f0, f1
/* 801C509C 001C1C7C  40 80 01 4C */	bge lbl_801C51E8
/* 801C50A0 001C1C80  EC 00 00 32 */	fmuls f0, f0, f0
/* 801C50A4 001C1C84  EC 82 00 BA */	fmadds f4, f2, f2, f0
/* 801C50A8 001C1C88  FC 04 08 40 */	fcmpo cr0, f4, f1
/* 801C50AC 001C1C8C  40 81 00 50 */	ble lbl_801C50FC
/* 801C50B0 001C1C90  FC 20 20 34 */	frsqrte f1, f4
/* 801C50B4 001C1C94  C8 62 B3 78 */	lfd f3, 0.5
/* 801C50B8 001C1C98  C8 42 B3 80 */	lfd f2, 3.0
/* 801C50BC 001C1C9C  FC 01 00 72 */	fmul f0, f1, f1
/* 801C50C0 001C1CA0  FC 23 00 72 */	fmul f1, f3, f1
/* 801C50C4 001C1CA4  FC 04 10 3C */	fnmsub f0, f4, f0, f2
/* 801C50C8 001C1CA8  FC 21 00 32 */	fmul f1, f1, f0
/* 801C50CC 001C1CAC  FC 01 00 72 */	fmul f0, f1, f1
/* 801C50D0 001C1CB0  FC 23 00 72 */	fmul f1, f3, f1
/* 801C50D4 001C1CB4  FC 04 10 3C */	fnmsub f0, f4, f0, f2
/* 801C50D8 001C1CB8  FC 21 00 32 */	fmul f1, f1, f0
/* 801C50DC 001C1CBC  FC 01 00 72 */	fmul f0, f1, f1
/* 801C50E0 001C1CC0  FC 23 00 72 */	fmul f1, f3, f1
/* 801C50E4 001C1CC4  FC 04 10 3C */	fnmsub f0, f4, f0, f2
/* 801C50E8 001C1CC8  FC 01 00 32 */	fmul f0, f1, f0
/* 801C50EC 001C1CCC  FC 04 00 32 */	fmul f0, f4, f0
/* 801C50F0 001C1CD0  FC 00 00 18 */	frsp f0, f0
/* 801C50F4 001C1CD4  D0 01 00 1C */	stfs f0, 0x1c(r1)
/* 801C50F8 001C1CD8  C0 81 00 1C */	lfs f4, 0x1c(r1)
lbl_801C50FC:
/* 801C50FC 001C1CDC  C0 02 B2 E4 */	lfs f0, 1.0f
/* 801C5100 001C1CE0  C0 21 00 74 */	lfs f1, 0x74(r1)
/* 801C5104 001C1CE4  EC 60 20 24 */	fdivs f3, f0, f4
/* 801C5108 001C1CE8  C0 02 B2 C4 */	lfs f0, 0.0f
/* 801C510C 001C1CEC  FC 01 00 40 */	fcmpo cr0, f1, f0
/* 801C5110 001C1CF0  40 80 00 08 */	bge lbl_801C5118
/* 801C5114 001C1CF4  FC 20 08 50 */	fneg f1, f1
lbl_801C5118:
/* 801C5118 001C1CF8  C0 41 00 7C */	lfs f2, 0x7c(r1)
/* 801C511C 001C1CFC  EC 83 00 72 */	fmuls f4, f3, f1
/* 801C5120 001C1D00  C0 02 B2 C4 */	lfs f0, 0.0f
/* 801C5124 001C1D04  FC 02 00 40 */	fcmpo cr0, f2, f0
/* 801C5128 001C1D08  40 80 00 08 */	bge lbl_801C5130
/* 801C512C 001C1D0C  FC 40 10 50 */	fneg f2, f2
lbl_801C5130:
/* 801C5130 001C1D10  EC A3 00 B2 */	fmuls f5, f3, f2
/* 801C5134 001C1D14  C0 61 00 50 */	lfs f3, 0x50(r1)
/* 801C5138 001C1D18  C0 41 00 44 */	lfs f2, 0x44(r1)
/* 801C513C 001C1D1C  38 61 00 68 */	addi r3, r1, 0x68
/* 801C5140 001C1D20  C0 21 00 68 */	lfs f1, 0x68(r1)
/* 801C5144 001C1D24  C0 01 00 5C */	lfs f0, 0x5c(r1)
/* 801C5148 001C1D28  EC 63 01 32 */	fmuls f3, f3, f4
/* 801C514C 001C1D2C  EC 42 01 32 */	fmuls f2, f2, f4
/* 801C5150 001C1D30  38 81 00 50 */	addi r4, r1, 0x50
/* 801C5154 001C1D34  EC 21 01 72 */	fmuls f1, f1, f5
/* 801C5158 001C1D38  EC 00 01 72 */	fmuls f0, f0, f5
/* 801C515C 001C1D3C  D0 61 00 50 */	stfs f3, 0x50(r1)
/* 801C5160 001C1D40  38 A1 00 38 */	addi r5, r1, 0x38
/* 801C5164 001C1D44  D0 41 00 44 */	stfs f2, 0x44(r1)
/* 801C5168 001C1D48  C0 61 00 54 */	lfs f3, 0x54(r1)
/* 801C516C 001C1D4C  D0 21 00 68 */	stfs f1, 0x68(r1)
/* 801C5170 001C1D50  C0 41 00 48 */	lfs f2, 0x48(r1)
/* 801C5174 001C1D54  EC 63 01 32 */	fmuls f3, f3, f4
/* 801C5178 001C1D58  D0 01 00 5C */	stfs f0, 0x5c(r1)
/* 801C517C 001C1D5C  C0 21 00 6C */	lfs f1, 0x6c(r1)
/* 801C5180 001C1D60  EC 42 01 32 */	fmuls f2, f2, f4
/* 801C5184 001C1D64  C0 01 00 60 */	lfs f0, 0x60(r1)
/* 801C5188 001C1D68  EC 21 01 72 */	fmuls f1, f1, f5
/* 801C518C 001C1D6C  D0 61 00 54 */	stfs f3, 0x54(r1)
/* 801C5190 001C1D70  EC 00 01 72 */	fmuls f0, f0, f5
/* 801C5194 001C1D74  D0 41 00 48 */	stfs f2, 0x48(r1)
/* 801C5198 001C1D78  C0 61 00 58 */	lfs f3, 0x58(r1)
/* 801C519C 001C1D7C  D0 21 00 6C */	stfs f1, 0x6c(r1)
/* 801C51A0 001C1D80  C0 41 00 4C */	lfs f2, 0x4c(r1)
/* 801C51A4 001C1D84  EC 63 01 32 */	fmuls f3, f3, f4
/* 801C51A8 001C1D88  D0 01 00 60 */	stfs f0, 0x60(r1)
/* 801C51AC 001C1D8C  C0 21 00 70 */	lfs f1, 0x70(r1)
/* 801C51B0 001C1D90  EC 42 01 32 */	fmuls f2, f2, f4
/* 801C51B4 001C1D94  C0 01 00 64 */	lfs f0, 0x64(r1)
/* 801C51B8 001C1D98  EC 21 01 72 */	fmuls f1, f1, f5
/* 801C51BC 001C1D9C  D0 61 00 58 */	stfs f3, 0x58(r1)
/* 801C51C0 001C1DA0  EC 00 01 72 */	fmuls f0, f0, f5
/* 801C51C4 001C1DA4  D0 41 00 4C */	stfs f2, 0x4c(r1)
/* 801C51C8 001C1DA8  D0 21 00 70 */	stfs f1, 0x70(r1)
/* 801C51CC 001C1DAC  D0 01 00 64 */	stfs f0, 0x64(r1)
/* 801C51D0 001C1DB0  48 17 DB 85 */	bl PSVECAdd
/* 801C51D4 001C1DB4  38 61 00 5C */	addi r3, r1, 0x5c
/* 801C51D8 001C1DB8  38 81 00 44 */	addi r4, r1, 0x44
/* 801C51DC 001C1DBC  38 A1 00 2C */	addi r5, r1, 0x2c
/* 801C51E0 001C1DC0  48 17 DB 75 */	bl PSVECAdd
/* 801C51E4 001C1DC4  48 00 00 34 */	b lbl_801C5218
lbl_801C51E8:
/* 801C51E8 001C1DC8  80 61 00 50 */	lwz r3, 0x50(r1)
/* 801C51EC 001C1DCC  80 01 00 44 */	lwz r0, 0x44(r1)
/* 801C51F0 001C1DD0  90 61 00 38 */	stw r3, 0x38(r1)
/* 801C51F4 001C1DD4  80 61 00 54 */	lwz r3, 0x54(r1)
/* 801C51F8 001C1DD8  90 01 00 2C */	stw r0, 0x2c(r1)
/* 801C51FC 001C1DDC  80 01 00 48 */	lwz r0, 0x48(r1)
/* 801C5200 001C1DE0  90 61 00 3C */	stw r3, 0x3c(r1)
/* 801C5204 001C1DE4  80 61 00 58 */	lwz r3, 0x58(r1)
/* 801C5208 001C1DE8  90 01 00 30 */	stw r0, 0x30(r1)
/* 801C520C 001C1DEC  80 01 00 4C */	lwz r0, 0x4c(r1)
/* 801C5210 001C1DF0  90 61 00 40 */	stw r3, 0x40(r1)
/* 801C5214 001C1DF4  90 01 00 34 */	stw r0, 0x34(r1)
lbl_801C5218:
/* 801C5218 001C1DF8  38 7E 00 00 */	addi r3, r30, 0
/* 801C521C 001C1DFC  38 81 00 20 */	addi r4, r1, 0x20
/* 801C5220 001C1E00  48 1A 35 65 */	bl func_80368784
/* 801C5224 001C1E04  80 7F 01 2C */	lwz r3, 0x12c(r31)
/* 801C5228 001C1E08  28 03 00 00 */	cmplwi r3, 0
/* 801C522C 001C1E0C  41 82 01 A0 */	beq lbl_801C53CC
/* 801C5230 001C1E10  83 C3 00 28 */	lwz r30, 0x28(r3)
/* 801C5234 001C1E14  28 1E 00 00 */	cmplwi r30, 0
/* 801C5238 001C1E18  41 82 01 94 */	beq lbl_801C53CC
/* 801C523C 001C1E1C  C0 61 00 38 */	lfs f3, 0x38(r1)
/* 801C5240 001C1E20  C0 41 00 20 */	lfs f2, 0x20(r1)
/* 801C5244 001C1E24  C0 21 00 3C */	lfs f1, 0x3c(r1)
/* 801C5248 001C1E28  EC 43 10 28 */	fsubs f2, f3, f2
/* 801C524C 001C1E2C  C0 01 00 24 */	lfs f0, 0x24(r1)
/* 801C5250 001C1E30  C0 61 00 40 */	lfs f3, 0x40(r1)
/* 801C5254 001C1E34  EC 81 00 28 */	fsubs f4, f1, f0
/* 801C5258 001C1E38  C0 01 00 28 */	lfs f0, 0x28(r1)
/* 801C525C 001C1E3C  EC 63 00 28 */	fsubs f3, f3, f0
/* 801C5260 001C1E40  C0 22 B2 C4 */	lfs f1, 0.0f
/* 801C5264 001C1E44  EC 42 00 B2 */	fmuls f2, f2, f2
/* 801C5268 001C1E48  EC 04 01 32 */	fmuls f0, f4, f4
/* 801C526C 001C1E4C  EC 63 00 F2 */	fmuls f3, f3, f3
/* 801C5270 001C1E50  EC 02 00 2A */	fadds f0, f2, f0
/* 801C5274 001C1E54  EC 03 00 2A */	fadds f0, f3, f0
/* 801C5278 001C1E58  FC 00 08 40 */	fcmpo cr0, f0, f1
/* 801C527C 001C1E5C  40 81 00 50 */	ble lbl_801C52CC
/* 801C5280 001C1E60  FC 40 00 34 */	frsqrte f2, f0
/* 801C5284 001C1E64  C8 82 B3 78 */	lfd f4, 0.5
/* 801C5288 001C1E68  C8 62 B3 80 */	lfd f3, 3.0
/* 801C528C 001C1E6C  FC 22 00 B2 */	fmul f1, f2, f2
/* 801C5290 001C1E70  FC 44 00 B2 */	fmul f2, f4, f2
/* 801C5294 001C1E74  FC 20 18 7C */	fnmsub f1, f0, f1, f3
/* 801C5298 001C1E78  FC 42 00 72 */	fmul f2, f2, f1
/* 801C529C 001C1E7C  FC 22 00 B2 */	fmul f1, f2, f2
/* 801C52A0 001C1E80  FC 44 00 B2 */	fmul f2, f4, f2
/* 801C52A4 001C1E84  FC 20 18 7C */	fnmsub f1, f0, f1, f3
/* 801C52A8 001C1E88  FC 42 00 72 */	fmul f2, f2, f1
/* 801C52AC 001C1E8C  FC 22 00 B2 */	fmul f1, f2, f2
/* 801C52B0 001C1E90  FC 44 00 B2 */	fmul f2, f4, f2
/* 801C52B4 001C1E94  FC 20 18 7C */	fnmsub f1, f0, f1, f3
/* 801C52B8 001C1E98  FC 22 00 72 */	fmul f1, f2, f1
/* 801C52BC 001C1E9C  FC 00 00 72 */	fmul f0, f0, f1
/* 801C52C0 001C1EA0  FC 00 00 18 */	frsp f0, f0
/* 801C52C4 001C1EA4  D0 01 00 18 */	stfs f0, 0x18(r1)
/* 801C52C8 001C1EA8  C0 01 00 18 */	lfs f0, 0x18(r1)
lbl_801C52CC:
/* 801C52CC 001C1EAC  C0 81 00 2C */	lfs f4, 0x2c(r1)
/* 801C52D0 001C1EB0  FF E0 00 90 */	fmr f31, f0
/* 801C52D4 001C1EB4  C0 61 00 20 */	lfs f3, 0x20(r1)
/* 801C52D8 001C1EB8  C0 41 00 30 */	lfs f2, 0x30(r1)
/* 801C52DC 001C1EBC  C0 21 00 24 */	lfs f1, 0x24(r1)
/* 801C52E0 001C1EC0  EC 64 18 28 */	fsubs f3, f4, f3
/* 801C52E4 001C1EC4  C0 81 00 34 */	lfs f4, 0x34(r1)
/* 801C52E8 001C1EC8  EC 42 08 28 */	fsubs f2, f2, f1
/* 801C52EC 001C1ECC  C0 21 00 28 */	lfs f1, 0x28(r1)
/* 801C52F0 001C1ED0  EC 63 00 F2 */	fmuls f3, f3, f3
/* 801C52F4 001C1ED4  EC 84 08 28 */	fsubs f4, f4, f1
/* 801C52F8 001C1ED8  C0 22 B2 C4 */	lfs f1, 0.0f
/* 801C52FC 001C1EDC  EC 42 00 B2 */	fmuls f2, f2, f2
/* 801C5300 001C1EE0  EC 84 01 32 */	fmuls f4, f4, f4
/* 801C5304 001C1EE4  EC 43 10 2A */	fadds f2, f3, f2
/* 801C5308 001C1EE8  EC A4 10 2A */	fadds f5, f4, f2
/* 801C530C 001C1EEC  FC 05 08 40 */	fcmpo cr0, f5, f1
/* 801C5310 001C1EF0  40 81 00 50 */	ble lbl_801C5360
/* 801C5314 001C1EF4  FC 40 28 34 */	frsqrte f2, f5
/* 801C5318 001C1EF8  C8 82 B3 78 */	lfd f4, 0.5
/* 801C531C 001C1EFC  C8 62 B3 80 */	lfd f3, 3.0
/* 801C5320 001C1F00  FC 22 00 B2 */	fmul f1, f2, f2
/* 801C5324 001C1F04  FC 44 00 B2 */	fmul f2, f4, f2
/* 801C5328 001C1F08  FC 25 18 7C */	fnmsub f1, f5, f1, f3
/* 801C532C 001C1F0C  FC 42 00 72 */	fmul f2, f2, f1
/* 801C5330 001C1F10  FC 22 00 B2 */	fmul f1, f2, f2
/* 801C5334 001C1F14  FC 44 00 B2 */	fmul f2, f4, f2
/* 801C5338 001C1F18  FC 25 18 7C */	fnmsub f1, f5, f1, f3
/* 801C533C 001C1F1C  FC 42 00 72 */	fmul f2, f2, f1
/* 801C5340 001C1F20  FC 22 00 B2 */	fmul f1, f2, f2
/* 801C5344 001C1F24  FC 44 00 B2 */	fmul f2, f4, f2
/* 801C5348 001C1F28  FC 25 18 7C */	fnmsub f1, f5, f1, f3
/* 801C534C 001C1F2C  FC 22 00 72 */	fmul f1, f2, f1
/* 801C5350 001C1F30  FC 25 00 72 */	fmul f1, f5, f1
/* 801C5354 001C1F34  FC 20 08 18 */	frsp f1, f1
/* 801C5358 001C1F38  D0 21 00 14 */	stfs f1, 0x14(r1)
/* 801C535C 001C1F3C  C0 A1 00 14 */	lfs f5, 0x14(r1)
lbl_801C5360:
/* 801C5360 001C1F40  C0 22 B3 28 */	lfs f1, 10.0f
/* 801C5364 001C1F44  FF C0 28 90 */	fmr f30, f5
/* 801C5368 001C1F48  FC 05 08 40 */	fcmpo cr0, f5, f1
/* 801C536C 001C1F4C  40 80 00 08 */	bge lbl_801C5374
/* 801C5370 001C1F50  FF C0 08 90 */	fmr f30, f1
lbl_801C5374:
/* 801C5374 001C1F54  C0 22 B3 88 */	lfs f1, 5.0f
/* 801C5378 001C1F58  FC 00 08 40 */	fcmpo cr0, f0, f1
/* 801C537C 001C1F5C  40 80 00 08 */	bge lbl_801C5384
/* 801C5380 001C1F60  FF E0 08 90 */	fmr f31, f1
lbl_801C5384:
/* 801C5384 001C1F64  FC 1F F0 40 */	fcmpo cr0, f31, f30
/* 801C5388 001C1F68  40 81 00 0C */	ble lbl_801C5394
/* 801C538C 001C1F6C  C0 02 B2 E4 */	lfs f0, 1.0f
/* 801C5390 001C1F70  EF C0 F8 2A */	fadds f30, f0, f31
lbl_801C5394:
/* 801C5394 001C1F74  28 1E 00 00 */	cmplwi r30, 0
/* 801C5398 001C1F78  40 82 00 14 */	bne lbl_801C53AC
/* 801C539C 001C1F7C  38 6D 8E 84 */	addi r3, r13, lbl_804D4524
/* 801C53A0 001C1F80  38 80 00 B4 */	li r4, 0xb4
/* 801C53A4 001C1F84  38 AD 8E 8C */	addi r5, r13, lbl_804D452C
/* 801C53A8 001C1F88  48 1C 2E 79 */	bl __assert
lbl_801C53AC:
/* 801C53AC 001C1F8C  28 1E 00 00 */	cmplwi r30, 0
/* 801C53B0 001C1F90  D3 FE 00 10 */	stfs f31, 0x10(r30)
/* 801C53B4 001C1F94  40 82 00 14 */	bne lbl_801C53C8
/* 801C53B8 001C1F98  38 6D 8E 84 */	addi r3, r13, lbl_804D4524
/* 801C53BC 001C1F9C  38 80 00 BF */	li r4, 0xbf
/* 801C53C0 001C1FA0  38 AD 8E 8C */	addi r5, r13, lbl_804D452C
/* 801C53C4 001C1FA4  48 1C 2E 5D */	bl __assert
lbl_801C53C8:
/* 801C53C8 001C1FA8  D3 DE 00 14 */	stfs f30, 0x14(r30)
lbl_801C53CC:
/* 801C53CC 001C1FAC  80 01 00 9C */	lwz r0, 0x9c(r1)
/* 801C53D0 001C1FB0  CB E1 00 90 */	lfd f31, 0x90(r1)
/* 801C53D4 001C1FB4  CB C1 00 88 */	lfd f30, 0x88(r1)
/* 801C53D8 001C1FB8  83 E1 00 84 */	lwz r31, 0x84(r1)
/* 801C53DC 001C1FBC  83 C1 00 80 */	lwz r30, 0x80(r1)
/* 801C53E0 001C1FC0  38 21 00 98 */	addi r1, r1, 0x98
/* 801C53E4 001C1FC4  7C 08 03 A6 */	mtlr r0
/* 801C53E8 001C1FC8  4E 80 00 20 */	blr 
}
#pragma peephole on

#include <melee/lb/lbaudio_ax.h>

void func_801C53EC(u32 arg0)
{
    func_800237A8(arg0, 0x7F, 0x40);
}

void func_801C5414(void* arg0, s32 arg1)
{
    func_80023870(arg0, 0x7F, 0x40, arg1);
}

void func_801C5440(Map* gp, s32 i, u32 arg2)
{
    if (i < 0 || i >= 8) {
        return;
    }
    if (gp == NULL) {
        return;
    }
    if (arg2 == 540000) {
        return;
    }
    if (arg2 != 540001) {
        if (gp->x20[i] != -1) {
            Map* tmp_gp = gp;
            func_800236B8(tmp_gp->x20[i]);
        }
        gp->x20[i] = func_800237A8(arg2, 0x7F, 0x40);
    } else {
        func_801C5544(gp, i);
    }
}

BOOL func_801C54DC(Map* gp, s32 i)
{
    if (i < 0 || i >= 8) {
        return FALSE;
    }
    if (gp != NULL && gp->x20[i] != -1 && func_80023710(gp->x20[i])) {
        return TRUE;
    }
    return FALSE;
}

void func_801C5544(Map* gp, s32 i)
{
    if (i < 0 || i >= 8) {
        return;
    }
    if (gp == NULL) {
        return;
    }
    if (gp->x20[i] != -1) {
        Map* tmp_gp = gp;
        func_800236B8(tmp_gp->x20[i]);
    }
    gp->x20[i] = -1;
}

static void func_801C55AC(Map* gp)
{
    int i;
    if (gp == NULL) {
        return;
    }
    for (i = 0; i < 8; i++) {
        func_801C5544(gp, i);
    }
}

void func_801C5630(Map* gp, s32 i, f32 val)
{
    if (i < 0 || i >= 8) {
        return;
    }
    if (gp != NULL && gp->x20[i] != -1) {
        func_80024B58(gp->x20[i], 127 * val);
    }
}

void func_801C5694(Map* gp, s32 i, f32 val)
{
    if (i < 0 || i >= 8) {
        return;
    }
    if (gp != NULL && gp->x20[i] != -1) {
        func_80024B1C(gp->x20[i], 63.5f * (val + 1));
    }
}

BOOL func_801C5700(s32 i)
{
    if (stage_info.x178 != NULL) {
        return stage_info.x178(i);
    }
    return FALSE;
}

void func_801C5740(s32 arg0)
{
    stage_info.x6D8 = arg0;
}

void func_801C5750(void)
{
    stage_info.x6D8 = 0;
}

s32 func_801C5764(void)
{
    return stage_info.x6D8;
}

s16 func_801C5774(void)
{
    return stage_info.x6DC;
}

void func_801C5784(s32 arg0)
{
    stage_info.x740 = arg0;
}

s32 func_801C5794(void)
{
    return stage_info.x740;
}

HSD_GObj* func_801C57A4(void)
{
    return Player_GetEntity(0);
}

HSD_GObj* func_801C57C8(void)
{
    return Player_GetEntityAtIndex(0, 1);
}

f32 func_801C57F0(void)
{
    return stage_info.x6E0;
}

void func_801C5800(void)
{
    if (stage_info.x6B0->x4C_fixed_cam) {
        func_8002F8F4();
    } else {
        func_8002F474();
    }
}

s32 func_801C5840(void)
{
    s32 i = HSD_Randi(1);
    return stage_info.x6E4[i];
}

extern void func_8031C454();
extern void func_8031C2EC();
extern void func_8016B498();
extern void func_8031C2CC();
static asm void func_801C5878(void)
{
    nofralloc
/* 801C5878 001C2458  7C 08 02 A6 */	mflr r0
/* 801C587C 001C245C  90 01 00 04 */	stw r0, 4(r1)
/* 801C5880 001C2460  94 21 FF E8 */	stwu r1, -0x18(r1)
/* 801C5884 001C2464  93 E1 00 14 */	stw r31, 0x14(r1)
/* 801C5888 001C2468  93 C1 00 10 */	stw r30, 0x10(r1)
/* 801C588C 001C246C  48 15 6A 41 */	bl func_8031C2CC
/* 801C5890 001C2470  4B FA 5C 09 */	bl func_8016B498
/* 801C5894 001C2474  2C 03 00 00 */	cmpwi r3, 0
/* 801C5898 001C2478  41 82 00 20 */	beq lbl_801C58B8
/* 801C589C 001C247C  3C 60 80 4A */	lis r3, stage_info@ha
/* 801C58A0 001C2480  3B E3 E6 C8 */	addi r31, r3, stage_info@l
/* 801C58A4 001C2484  48 15 6A 49 */	bl func_8031C2EC
/* 801C58A8 001C2488  7C 7E 1B 78 */	mr r30, r3
/* 801C58AC 001C248C  48 15 6B A9 */	bl func_8031C454
/* 801C58B0 001C2490  93 DF 06 E4 */	stw r30, 0x6e4(r31)
/* 801C58B4 001C2494  48 00 00 14 */	b lbl_801C58C8
lbl_801C58B8:
/* 801C58B8 001C2498  3C 60 80 4A */	lis r3, stage_info@ha
/* 801C58BC 001C249C  38 63 E6 C8 */	addi r3, r3, stage_info@l
/* 801C58C0 001C24A0  38 00 FF FF */	li r0, -1
/* 801C58C4 001C24A4  90 03 06 E4 */	stw r0, 0x6e4(r3)
lbl_801C58C8:
/* 801C58C8 001C24A8  80 01 00 1C */	lwz r0, 0x1c(r1)
/* 801C58CC 001C24AC  83 E1 00 14 */	lwz r31, 0x14(r1)
/* 801C58D0 001C24B0  83 C1 00 10 */	lwz r30, 0x10(r1)
/* 801C58D4 001C24B4  38 21 00 18 */	addi r1, r1, 0x18
/* 801C58D8 001C24B8  7C 08 03 A6 */	mtlr r0
/* 801C58DC 001C24BC  4E 80 00 20 */	blr 
}
#pragma peephole on

s32 func_801C58E0(s32 arg0, s32 arg1)
{
    s32 tmp = arg0;
    s32 result;
    Vec3 sp10;

    func_801C2D24(arg1, &sp10);
    result = func_802F2094(0, &sp10, tmp, 0);
    func_80304A58(tmp);
    return result;
}

inline s32 randi(s32 max)
{
    if (max != 0) {
        return HSD_Randi(max);
    }
    return 0;
}

s32 func_801C5940(void)
{
    struct {
        u8 x0_pad[0x4];
        struct {
            s16 a, b;
        }* unk4;
        s32 unk8;
    }* phi_r8;
    int i, j;
    UnkArchiveStruct* archive;
    s32 out_idx;
    const u32 out_size = 0x20U;
    u32 unused;
    s32 sp8[out_size];

    archive = func_801C6324();
    out_idx = 0;
    if (archive->unk4->unk4 == 0) {
        return -1;
    }
    phi_r8 = archive->unk4->unk0;
    for (i = 0; i < archive->unk4->unk4; i++, phi_r8++) {
        s32 max = phi_r8->unk8;
        for (j = 0; j < max; j++) {
            s16 val = phi_r8->unk4[j].b;
            if (val >= 220 && val < 252 && out_idx < out_size) {
                sp8[out_idx] = val;
                out_idx++;
            }
        }
    }
    if (out_idx == 0) {
        return -1;
    }
    return sp8[randi(out_idx)];
}

void func_801C5A28(void)
{
    func_803124BC();
    func_8031234C(0);
    func_80305918(0, 0, 1);
}

void func_801C5A60(void)
{
    func_8031234C(1);
}

void func_801C5A84(s32 arg0)
{
    stage_info.x98 = arg0;
}

s32 func_801C5A94(void)
{
    return stage_info.x98;
}

void func_801C5AA4(BOOL arg0)
{
    stage_info.unk8C.b1 = arg0;
}

BOOL func_801C5ABC(void)
{
    return stage_info.unk8C.b1;
}

u32 func_801C5AD0(s32 i)
{
    return lbl_803DFEDC[i]->flags2;
}

inline f32 fabsf(f32 x)
{
    if (x < 0) {
        return -x;
    } else {
        return x;
    }
}

void func_801C5AEC(Vec3* v, Vec3* arg1, Vec3* arg2, Vec3* arg3)
{
    lbvector_EulerAnglesFromONB(v, arg1, arg2, arg3);
    if (!(fabsf(v->x) < 30000)) {
        v->x = 0;
    }
    if (!(fabsf(v->y) < 30000)) {
        v->y = 0;
    }
    if (!(fabsf(v->z) < 30000)) {
        v->z = 0;
    }
}
