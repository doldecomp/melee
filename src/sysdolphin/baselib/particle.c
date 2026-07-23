#include "particle.h"

#include "generator.h"

typedef struct {
    /* 0x00 */ void* next;
    /* 0x04 */ s32 type;
    /* 0x08 */ union {
        u8 bytes[0x80];
        char text[0x80];
        struct {
            s32 count;
            u32 color;
        } bars[16];
        struct {
            f32 pos;
            u32 color;
        } gradient[16];
    } content;
} PerfDispItem;

#include "particle.static.h"

#include <math.h>
#include <math_ppc.h>
#include <trigf.h>
#include <dolphin/gx.h>
#include <dolphin/gx/GXGeometry.h>
#include <dolphin/mcc.h>
#include <dolphin/os.h>
#include <dolphin/pad.h>
#include <dolphin/vi.h>
#include <baselib/cobj.h>
#include <baselib/gobj.h>
#include <baselib/gobjgxlink.h>
#include <baselib/gobjobject.h>
#include <baselib/list.h>
#include <baselib/memory.h>
#include <baselib/mtx.h>
#include <baselib/perf.h>
#include <baselib/psappsrt.h>
#include <baselib/psstructs.h>
#include <baselib/random.h>
#include <baselib/state.h>
#include <baselib/video.h>
#include <MetroTRK/ppc_reg.h>

static HSD_JObj* hsd_804D08E8[8];
static void* hsd_804D0908[0x144 / 4];
static HSD_PSFormGroup** psFormGroupArray[65];
/* 4D0B50 */ static HSD_PSTexGroup** psTexGroupArray[65];
/* 4D0D58 */ static int psNumCmdList[65];
/* 4D0C54 */ static HSD_PSCmdList** psCmdListArray[65];
/* 4D0E5C */ static u32* ptclref_804D0E5C[65];
/* 4D0F60 */ struct hsd_804D0F60_t hsd_804D0F60;

typedef struct PSNode {
    /* 0x00 */ struct PSNode* child;
    /* 0x04 */ u8 _pad[4];
    /* 0x08 */ void (*callback)(struct PSNode*);
} PSNode;

typedef union {
    f32 f;
    u8 bytes[4];
} ParticleFloatBytes;

void hsd_803983A4(HSD_Generator* gen)
{
    HSD_JObj* jobj;

    if (gen == NULL) {
        return;
    }

    if (gen->kind & 0x800) {
        return;
    }

    if (!(gen->type & 0x100)) {
        return;
    }

    if ((jobj = gen->jobj) == NULL) {
        return;
    }

    HSD_JObjSetupMatrix(jobj);

    if (gen->type & 0x200) {
        gen->pos.x = gen->jobj->mtx[0][3];
        gen->pos.y = gen->jobj->mtx[1][3];
        gen->pos.z = gen->jobj->mtx[2][3];
    }

    if (gen->type & 0x800) {
        if (gen->appsrt != NULL && gen->appsrt->gp == gen) {
            gen->appsrt->translate.x = gen->jobj->mtx[0][3];
            gen->appsrt->translate.y = gen->jobj->mtx[1][3];
            gen->appsrt->translate.z = gen->jobj->mtx[2][3];
        }
    }

    if (gen->type & 0x1000) {
        if (gen->appsrt != NULL && gen->appsrt->gp == gen) {
            HSD_MtxGetScale(gen->jobj->mtx, &gen->appsrt->scale);
        }
    }
}

// @TODO: Currently 96.40% match - lis hoisting and r29/r30 register swap
void psInitDataBankLoad(int bank, int* cmdBank, int* texBank, u32* ref,
                        int* formBank)
{
    s32* base = (s32*) hsd_804D08E8;
    u16 version;

    if (formBank != NULL && *formBank != *texBank) {
        OSPanic(__FILE__, 177,
                "illigal form data (strange number of group)\n");
    }

    (base + bank)[0x60 / 4] = (s32) ref;
    (base + bank)[0x164 / 4] = *texBank;
    (base + bank)[0x268 / 4] = (s32) (texBank + 1);

    if (formBank != NULL) {
        (base + bank)[0x36C / 4] = (s32) (formBank + 1);
    } else {
        (base + bank)[0x36C / 4] = 0;
    }

    version = *(u16*) cmdBank;
    switch (version) {
    case 0:
        (base + bank)[0x470 / 4] = cmdBank[1];
        (base + bank)[0x574 / 4] = (s32) (cmdBank + 2);
        break;
    case 0x40:
    case 0x41:
    case 0x42:
    case 0x43: {
        s32 count = cmdBank[1];
        (base + bank)[0x470 / 4] = cmdBank[2] + count;
        (base + bank)[0x574 / 4] = (s32) (cmdBank + 3 - count);
        break;
    }
    default:
        OSPanic(__FILE__, 207, "psInitDataBanks: unknown version\n");
    }
}

// @TODO: Register allocation and branch structure differences
void psInitDataBankLocate(HSD_Archive* cmdBank, HSD_Archive* texBank,
                          int* formBank)
{
    s32 num;
    s32 i;
    s32 num2;
    s32* ptr;
    s32* base;
    s32 version;

    version = *(u16*) cmdBank;
    if (version < 0x40) {
        if (version == 0) {
            goto version0;
        }
        goto done_cmd;
    }
    if (version >= 0x44) {
        goto done_cmd;
    }
    goto version40;

version0:
    num2 = ((s32*) cmdBank)[1];
    base = (s32*) ((u8*) cmdBank + 8);
    num = 0;
    for (i = 0; i < num2; i++) {
        ((s32*) cmdBank)[i + 2] += (s32) cmdBank;
    }
    goto done_cmd;

version40:
    num = ((s32*) cmdBank)[1];
    num2 = ((s32*) cmdBank)[2] + num;
    base = (s32*) cmdBank + 3 - num;
    ptr = (s32*) cmdBank;
    i = 0;
    while (i < (s32) cmdBank->header.nb_reloc) {
        if (ptr[3] != 0) {
            ptr[3] += (s32) cmdBank;
        }
        ptr++;
        i++;
    }

done_cmd:
    /* Phase 2: Fix cmdList kind bits */
    ptr = base + num;
    for (i = num; i < num2; i++) {
        s32* cmd = (s32*) ptr[0];
        if (cmd != NULL) {
            cmd[2] = cmd[2] & 0xF1FFFFFF;
            cmd = (s32*) ptr[0];
            cmd[2] = cmd[2] | 0x08000000;
        }
        ptr++;
    }

    /* Phase 3: texBank relocation */
    {
        s32 num_groups = ((s32*) texBank)[0];
        s32* groups = (s32*) texBank + 1;
        s32* cur = groups;
        s32 k;

        if (num_groups >= 1) {
            k = num_groups;
            do {
                if (cur[0] != 0) {
                    cur[0] += (s32) texBank;
                }
                cur++;
            } while (--k != 0);
        }

        cur = groups;
        {
            for (k = 0; k < num_groups; k++) {
                HSD_PSTexGroup* tg = (HSD_PSTexGroup*) cur[0];
                if (tg == NULL) {
                    goto next_group;
                }

                /* Relocate texture pointers in the group */
                {
                    s32 ti;
                    s32 ofs;
                    for (ti = 0, ofs = 0;
                         (u32) ti < ((HSD_PSTexGroup*) cur[0])->num;
                         ti++, ofs += 4)
                    {
                        u32* entry_ptr =
                            (u32*) ((u8*) ((HSD_PSTexGroup*) cur[0]) + 24 +
                                    ofs);
                        if (*entry_ptr != 0U) {
                            *entry_ptr += (u32) texBank;
                        }
                    }
                    tg = (HSD_PSTexGroup*) cur[0];
                }

                /* Check format for palette relocation */
                {
                    u32 fmt = tg->fmt;
                    if (fmt != 8 && (fmt - 9) > 1) {
                        goto next_group;
                    }
                }

                /* Palette relocation */
                if (tg->palflag & 1) {
                    /* Single palette pointer */
                    s32 ofs = tg->num * 4 + 24;
                    if (*(u32*) ((u8*) tg + ofs) == 0U) {
                        goto next_group;
                    }
                    *(u32*) ((u8*) tg + ofs) += (u32) texBank;
                } else if (tg->palnum != 0) {
                    /* Multiple palette pointers (palnum > 0) */
                    s32 ti;
                    s32 ofs;
                    ti = (s32) tg->num;
                    (void) ti;
                    ofs = ti * 4;
                    for (; (u32) ti < ((HSD_PSTexGroup*) cur[0])->num +
                                          ((HSD_PSTexGroup*) cur[0])->palnum;
                         ti++, ofs += 4)
                    {
                        HSD_PSTexGroup* tg2 = (HSD_PSTexGroup*) cur[0];
                        u32* entry_ptr = (u32*) ((u8*) tg2 + 24 + ofs);
                        if (*entry_ptr != 0U) {
                            *entry_ptr += (u32) texBank;
                        }
                    }
                } else {
                    /* palnum == 0: relocate double the num entries */
                    s32 ti;
                    s32 ofs;
                    ti = (s32) tg->num;
                    ofs = ti * 4;
                    for (; (u32) ti < ((HSD_PSTexGroup*) cur[0])->num * 2;
                         ti++, ofs += 4)
                    {
                        HSD_PSTexGroup* tg2 = (HSD_PSTexGroup*) cur[0];
                        u32* entry_ptr = (u32*) ((u8*) tg2 + 24 + ofs);
                        if (*entry_ptr != 0U) {
                            *entry_ptr += (u32) texBank;
                        }
                    }
                }

            next_group:
                cur++;
            }
        }

        /* Phase 4: formBank relocation */
        if (formBank == NULL) {
            return;
        }
        {
            s32* groups = (s32*) formBank + 1;

            for (i = 0; i < num_groups; i++) {
                if (groups[0] == 0) {
                    goto next_form;
                }
                groups[0] += (s32) formBank;
                {
                    HSD_PSFormGroup* fg = (HSD_PSFormGroup*) groups[0];
                    u32* p2 = (u32*) fg;
                    s32 fi;
                    for (fi = 0; (u32) fi < fg->num; fi++) {
                        if (p2[1] != 0U) {
                            p2[1] += (u32) formBank;
                        }
                        p2++;
                    }
                }
            next_form:
                groups++;
            }
        }
    }
}

void psInitDataBank(int bank, int* cmdBank, int* texBank, u32* ref,
                    int* formBank)
{
    if (bank < 65) {
        psInitDataBankLocate((HSD_Archive*) cmdBank, (HSD_Archive*) texBank,
                             formBank);
        psInitDataBankLoad(bank, cmdBank, texBank, ref, formBank);
    }
}

// @TODO: Currently 62.67% match - ASM bytes identical, relocation differences
void hsd_80398A08(u32 unused)
{
    extern u16 hsd_804D78DC;
    s32 i;

    HSD_ObjAllocInit(&hsd_804D0F60.alloc_data, 0x98, 4);
    PAD_STACK(24);

    i = 0;
    hsd_804D0908[0] = NULL;
    hsd_804D0908[1] = NULL;
    hsd_804D0908[2] = NULL;
    hsd_804D0908[3] = NULL;
    hsd_804D0908[4] = NULL;
    hsd_804D0908[5] = NULL;
    hsd_804D0908[6] = NULL;
    hsd_804D0908[7] = NULL;
    hsd_804D0908[8] = NULL;
    hsd_804D0908[9] = NULL;
    hsd_804D0908[10] = NULL;
    hsd_804D0908[11] = NULL;
    hsd_804D0908[12] = NULL;
    hsd_804D0908[13] = NULL;
    hsd_804D0908[14] = NULL;
    hsd_804D0908[15] = NULL;
    hsd_804D78E2[0] = 0;
    hsd_804D78DC = 0;
    for (i = 0; i < 0x41; i++) {
        psCmdListArray[i] = NULL;
        psNumCmdList[i] = 0;
        psFormGroupArray[i] = NULL;
        ptclref_804D0E5C[i] = NULL;
        psTexGroupArray[i] = NULL;
        hsd_804D0908[i] = NULL;
    }
    psCallback = NULL;
    hsd_804D08E8[0] = NULL;
    hsd_804D08E8[1] = NULL;
    hsd_804D08E8[2] = NULL;
    hsd_804D08E8[3] = NULL;
    hsd_804D08E8[4] = NULL;
    hsd_804D08E8[5] = NULL;
    hsd_804D08E8[6] = NULL;
    hsd_804D08E8[7] = NULL;
}

HSD_Particle* hsd_80398C04(HSD_Particle** head, int linkNo, int bank, u32 kind,
                           u16 texGroup, u8* list, int life, int palflag,
                           f32 x, f32 y, f32 z, f32 vx, f32 vy, f32 vz,
                           f32 size, f32 grav, f32 fric, HSD_Generator* gp,
                           int flgInterpret)
{
    HSD_Particle* pp;
    HSD_Particle** slot;
    s16 cmd_wait;

    pp = HSD_ObjAlloc(&hsd_804D0F60.alloc_data);
    if (pp != NULL) {
        memset(pp, 0, 0x98);
    }
    if (pp == NULL) {
        return NULL;
    }

    hsd_804D78E2[0] += 1;
    if (hsd_804D78E2[0] > numPeakParticles) {
        numPeakParticles = hsd_804D78E2[0];
    }

    if (gp != NULL) {
        pp->idnum = gp->idnum;
    } else {
        pp->idnum = hsd_8039D1EC();
    }

    pp->appsrt = NULL;
    if (gp != NULL && gp->appsrt != NULL) {
        psAttachParticleAppSRT(pp, gp->appsrt);
    }

    if (head == NULL) {
        slot = (HSD_Particle**) &hsd_804D0908[linkNo];
        pp->next = *slot;
        *slot = pp;
    } else {
        pp->next = *head;
        *head = pp;
    }

    pp->bank = bank;
    pp->linkNo = linkNo;
    pp->kind = kind;
    pp->texGroup = texGroup;
    pp->pos.x = x;
    pp->pos.y = y;
    pp->pos.z = z;
    pp->vel.x = vx;
    pp->vel.y = vy;
    pp->vel.z = vz;
    pp->size = size;
    pp->grav = grav;
    pp->fric = fric;
    pp->life = (u16) (life + 1);
    pp->cmdList = list;
    pp->cmdMarkPtr = 0;
    pp->cmdPtr = 0;

    if (palflag != 0) {
        pp->kind = pp->kind | 0x10;
    }

    if (list != NULL) {
        cmd_wait = 1;
    } else {
        cmd_wait = 0;
    }
    pp->cmdWait = cmd_wait;
    pp->poseNum = 0;
    pp->palNum = 0xFF;
    pp->primCol.a = 0xFF;
    pp->primCol.b = 0xFF;
    pp->primCol.g = 0xFF;
    pp->primCol.r = 0xFF;
    pp->envCol.a = 0;
    pp->envCol.b = 0;
    pp->envCol.g = 0;
    pp->envCol.r = 0;
    pp->envColCount = 0;
    pp->primColCount = 0;
    pp->sizeCount = 0;
    pp->envColRemain = 0;
    pp->primColRemain = 0;
    pp->aCmpMode = 0x33;
    pp->aCmpParam1 = 1;
    pp->aCmpParam2 = 0xFF;
    pp->aCmpRemain = 0;
    pp->aCmpCount = 0;
    pp->rotateCount = 0;
    pp->rotateTarget = 0.0F;
    pp->rotate = 0.0F;
    pp->gen = gp;
    if (gp != NULL) {
        gp->numChild = gp->numChild + 1;
    }

    pp->pJObjOfs = 0;
    pp->matColRemain = 0;
    pp->matColCount = 0;
    pp->matRGB = 0xFF;
    pp->matA = 0xFF;
    pp->ambColRemain = 0;
    pp->ambColCount = 0;
    pp->ambRGB = 0xFF;
    pp->ambA = 0xFF;
    pp->trail = 1.0F;
    pp->userdata = NULL;

    if (gp != NULL) {
        if (gp->userfunc != NULL) {
            if (gp->userfunc->hookCreate != NULL) {
                gp->userfunc->hookCreate(pp);
            }
        }
    }

    pp->callback = NULL;
    if (flgInterpret != 0) {
        hsd_8039930C(pp, 0);
    }
    return pp;
}

#pragma push
#pragma dont_inline on
void hsd_80398F0C(s32 linkNo, s32 bank, s32 kind, u16 texGroup, s32 cmdList,
                  s32 life, s32 zero, s32 gen, f32 pos_x, f32 pos_y, f32 pos_z,
                  f32 vel_x, f32 vel_y, f32 vel_z, f32 fric, f32 rate,
                  f32 angle3)
{
    hsd_80398C04(0, linkNo, bank, kind, texGroup, (u8*) cmdList, life, zero,
                 pos_x, pos_y, pos_z, vel_x, vel_y, vel_z, fric, rate, angle3,
                 (HSD_Generator*) gen, 1);
}
#pragma pop

void hsd_80398F8C(HSD_Particle* pp, f32 angle)
{
    f32 vx = pp->vel.x;
    f32 vz = pp->vel.z;
    f32 vy = pp->vel.y;
    f32 sin_a, cos_a;
    f32 sin_e, cos_e;
    f32 cos_rand, sin_rand;
    f32 rand_angle;
    f32 angle_copy;
    f32 sin_angle, cos_angle;
    f32 abs_z;
    f32 temp;
    f32 abs_temp;
    vf32 magnitude;
    PAD_STACK(16);

    {
        f32 azimuth;

        abs_z = vz;
        *(s32*) &abs_z &= 0x7FFFFFFF;
        if (abs_z < 1.1754944e-38F) {
            if (vy >= 0.0F) {
                azimuth = 1.5707964F;
            } else {
                azimuth = -1.5707964F;
            }
        } else {
            azimuth = atan2f(vy, vz);
        }

        sin_a = sinf(azimuth);
        cos_a = cosf(azimuth);
    }

    {
        f32 azimuth;

        temp = vy * sin_a + vz * cos_a;
        abs_temp = temp;
        *(s32*) &abs_temp &= 0x7FFFFFFF;
        if (abs_temp < 1.1754944e-38F) {
            if (vx >= 0.0F) {
                azimuth = 1.5707964F;
            } else {
                azimuth = -1.5707964F;
            }
        } else {
            azimuth = atan2f(vx, temp);
        }

        sin_e = sinf(azimuth);
        cos_e = cosf(azimuth);
    }

    vx = (vx * vx + vy * vy) + vz * vz;
    if (vx > 0.0F) {
        f64 x = __frsqrte((f64) vx);
        x = 0.5 * x * -(((f64) vx * (x * x)) - 3.0);
        x = 0.5 * x * -(((f64) vx * (x * x)) - 3.0);
        x = 0.5 * x * -(((f64) vx * (x * x)) - 3.0);
        magnitude = (f32) ((f64) vx * x);
        vx = magnitude;
    }

    rand_angle = (f32) (3.141592653589793 * HSD_Randf() * 2.0);

    angle_copy = angle;
    sin_angle = vx * sinf(angle_copy);
    cos_rand = sin_angle * cosf(rand_angle);
    sin_rand = sin_angle * sinf(rand_angle);
    cos_angle = vx * cosf(angle_copy);

    pp->vel.x = cos_rand * cos_e + cos_angle * sin_e;
    pp->vel.y = cos_e * (cos_angle * sin_a) +
                (sin_e * (-cos_rand * sin_a) + sin_rand * cos_a);
    pp->vel.z = cos_e * (cos_angle * cos_a) +
                (sin_e * (-cos_rand * cos_a) - sin_rand * sin_a);
}

s32 hsd_803991D8(HSD_Generator* gen, HSD_JObj* jobj, f32 force, f32 range)
{
    f32 dx, dy, dz;
    f32 dist_sq;
    f32 scale;

    if (jobj == NULL || range < 0.0F) {
        return 0;
    }

    HSD_JObjSetupMatrix(jobj);

    dx = jobj->mtx[0][3] - gen->fric;
    dy = jobj->mtx[1][3] - gen->size;
    dz = jobj->mtx[2][3] - gen->radius;
    dist_sq = dx * dx + dy * dy + dz * dz;

    if (dist_sq <= range * range) {
        return 1;
    }

    if (dist_sq == 0.0F) {
        return 0;
    }

    scale = force / dist_sq;
    gen->pos.z += scale * dx;
    gen->vel.x += scale * dy;
    gen->vel.y += scale * dz;
    return 0;
}

// @TODO: Currently 93.95% match - register allocation differences (stmw
// r20 vs r21), r27/r28 swap, and PC advance codegen patterns
void* hsd_8039930C(void* pp_arg, void* prev_arg)
{
    HSD_Particle* pp = pp_arg;
    HSD_Particle* prev = prev_arg;
    u8* pc;
    int operand;
    u8 opcode;
    u8 cls;
    HSD_Particle* child;
    HSD_Generator* gchild;
    HSD_PSCmdList* cl;
    HSD_PSTexGroup* tg;
    PAD_STACK(456);

#define fval (*(f32*) &hsd_804D78D0)
#define fbytes (*(ParticleFloatBytes*) &hsd_804D78D0).bytes

    /* Early exit: bit 11 of kind set */
    if (pp->kind & 0x800) {
        return pp->next;
    }

    /* --- Timer interpolation --- */

    /* Size interpolation */
    if (pp->sizeCount != 0) {
        pp->size += (pp->sizeTarget - pp->size) / (f32) pp->sizeCount;
        pp->sizeCount--;
    }

    /* Primary color countdown */
    if (pp->primColCount != 0) {
        pp->primColRemain--;
        if (pp->primColRemain == 0) {
            pp->primColCount = 0;
            pp->primCol.r = pp->primColTarget.r;
            pp->primCol.g = pp->primColTarget.g;
            pp->primCol.b = pp->primColTarget.b;
            pp->primCol.a = pp->primColTarget.a;
        }
    }

    /* Environment color countdown */
    if (pp->envColCount != 0) {
        pp->envColRemain--;
        if (pp->envColRemain == 0) {
            pp->envColCount = 0;
            pp->envCol.r = pp->envColTarget.r;
            pp->envCol.g = pp->envColTarget.g;
            pp->envCol.b = pp->envColTarget.b;
            pp->envCol.a = pp->envColTarget.a;
        }
    }

    /* Material color countdown */
    if (pp->matColCount != 0) {
        pp->matColRemain--;
        if (pp->matColRemain == 0) {
            pp->matColCount = 0;
            pp->matRGB = pp->matRGBTarget;
            pp->matA = pp->matATarget;
        }
    }

    /* Ambient color countdown */
    if (pp->ambColCount != 0) {
        pp->ambColRemain--;
        if (pp->ambColRemain == 0) {
            pp->ambColCount = 0;
            pp->ambRGB = pp->ambRGBTarget;
            pp->ambA = pp->ambATarget;
        }
    }

    /* Alpha compare countdown */
    if (pp->aCmpCount != 0) {
        pp->aCmpRemain--;
        if (pp->aCmpRemain == 0) {
            pp->aCmpCount = 0;
            pp->aCmpParam1 = pp->aCmpParam1Target;
            pp->aCmpParam2 = pp->aCmpParam2Target;
        }
    }

    /* Rotate interpolation */
    if (pp->rotateCount != 0) {
        pp->rotate += (pp->rotateTarget - pp->rotate) / (f32) pp->rotateCount;
        pp->rotateCount--;
    }

    /* --- Command wait check --- */
    if (pp->cmdWait == 0) {
        goto do_life;
    }
    if (--pp->cmdWait != 0) {
        goto do_life;
    }

    /* --- Bytecode loop --- */
    operand = 0;
    pc = pp->cmdList + pp->cmdPtr;

    for (;;) {
        opcode = *pc++;

        if (opcode < 0x80) {
            /* Low opcode range */
            operand = opcode & 0x1F;
            if (opcode & 0x20) {
                operand = (operand << 8) + *pc++;
            }
            switch (opcode & 0xC0) {
            case 0x00:
                /* Wait/nop: operand is wait count */
                break;
            case 0x40: {
                /* Texture command */
                u8 pn = *pc++;
                pp->poseNum = pn;
                {
                    HSD_PSTexGroup** tga;
                    HSD_PSTexGroup* texGrp;
                    u8 bank = pp->bank;
                    u8 tgIdx = pp->texGroup;

                    tga = psTexGroupArray[bank];
                    texGrp = tga[tgIdx];
                    if (texGrp != NULL && texGrp->texTable != NULL) {
                        if (texGrp->texTable[pp->poseNum] != NULL) {
                            pp->kind |= DispTexture;
                        }
                    }
                }
                break;
            }
            }
        } else {
            /* High opcode: classify */
            operand = 0;
            cls = opcode & 0xF8;
            if (cls > 0x98) {
                cls = opcode & 0xF0;
                if (cls != 0xC0 && cls != 0xD0) {
                    cls = opcode;
                }
            }

            switch (cls) {
            case 0x80:
                /* Set position */
                if (opcode & 1) {
                    u8* _p = pc + 1;
                    ((u8*) &fval)[0] = pc[0];
                    _p += 3;
                    ((u8*) &fval)[1] = pc[1];
                    ((u8*) &fval)[2] = pc[2];
                    ((u8*) &fval)[3] = pc[3];
                    pc = _p;
                    pp->pos.x = fval;
                }
                if (opcode & 2) {
                    u8* _p = pc + 1;
                    ((u8*) &fval)[0] = pc[0];
                    _p += 3;
                    ((u8*) &fval)[1] = pc[1];
                    ((u8*) &fval)[2] = pc[2];
                    ((u8*) &fval)[3] = pc[3];
                    pc = _p;
                    pp->pos.y = fval;
                }
                if (opcode & 4) {
                    u8* _p = pc + 1;
                    ((u8*) &fval)[0] = pc[0];
                    _p += 3;
                    ((u8*) &fval)[1] = pc[1];
                    ((u8*) &fval)[2] = pc[2];
                    ((u8*) &fval)[3] = pc[3];
                    pc = _p;
                    pp->pos.z = fval;
                }
                break;

            case 0x88:
                /* Add to position */
                if (opcode & 1) {
                    ((u8*) &fval)[0] = pc[0];
                    ((u8*) &fval)[1] = pc[1];
                    ((u8*) &fval)[2] = pc[2];
                    ((u8*) &fval)[3] = pc[3];
                    pc += 4;
                    pp->pos.x += fval;
                }
                if (opcode & 2) {
                    ((u8*) &fval)[0] = pc[0];
                    ((u8*) &fval)[1] = pc[1];
                    ((u8*) &fval)[2] = pc[2];
                    ((u8*) &fval)[3] = pc[3];
                    pc += 4;
                    pp->pos.y += fval;
                }
                if (opcode & 4) {
                    ((u8*) &fval)[0] = pc[0];
                    ((u8*) &fval)[1] = pc[1];
                    ((u8*) &fval)[2] = pc[2];
                    ((u8*) &fval)[3] = pc[3];
                    pc += 4;
                    pp->pos.z += fval;
                }
                break;

            case 0x90:
                /* Set velocity */
                if (opcode & 1) {
                    ((u8*) &fval)[0] = pc[0];
                    ((u8*) &fval)[1] = pc[1];
                    ((u8*) &fval)[2] = pc[2];
                    ((u8*) &fval)[3] = pc[3];
                    pc += 4;
                    pp->vel.x = fval;
                }
                if (opcode & 2) {
                    ((u8*) &fval)[0] = pc[0];
                    ((u8*) &fval)[1] = pc[1];
                    ((u8*) &fval)[2] = pc[2];
                    ((u8*) &fval)[3] = pc[3];
                    pc += 4;
                    pp->vel.y = fval;
                }
                if (opcode & 4) {
                    ((u8*) &fval)[0] = pc[0];
                    ((u8*) &fval)[1] = pc[1];
                    ((u8*) &fval)[2] = pc[2];
                    ((u8*) &fval)[3] = pc[3];
                    pc += 4;
                    pp->vel.z = fval;
                }
                break;

            case 0x98:
                /* Add to velocity */
                if (opcode & 1) {
                    ((u8*) &fval)[0] = pc[0];
                    ((u8*) &fval)[1] = pc[1];
                    ((u8*) &fval)[2] = pc[2];
                    ((u8*) &fval)[3] = pc[3];
                    pc += 4;
                    pp->vel.x += fval;
                }
                if (opcode & 2) {
                    ((u8*) &fval)[0] = pc[0];
                    ((u8*) &fval)[1] = pc[1];
                    ((u8*) &fval)[2] = pc[2];
                    ((u8*) &fval)[3] = pc[3];
                    pc += 4;
                    pp->vel.y += fval;
                }
                if (opcode & 4) {
                    ((u8*) &fval)[0] = pc[0];
                    ((u8*) &fval)[1] = pc[1];
                    ((u8*) &fval)[2] = pc[2];
                    ((u8*) &fval)[3] = pc[3];
                    pc += 4;
                    pp->vel.z += fval;
                }
                break;

            case 0xA0:
                /* Set size interpolation target */
                {
                    pp->sizeCount = *pc++;
                    {
                        u16 cnt = pp->sizeCount;
                        if (cnt & 0x80) {
                            cnt = ((cnt & 0x7F) << 8) + *pc++;
                            pp->sizeCount = cnt;
                        }
                    }
                    ((u8*) &fval)[0] = pc[0];
                    ((u8*) &fval)[1] = pc[1];
                    ((u8*) &fval)[2] = pc[2];
                    ((u8*) &fval)[3] = pc[3];
                    pc += 4;
                    pp->sizeTarget = fval;
                    if (pp->sizeCount == 0) {
                        pp->size = pp->sizeTarget;
                    }
                }
                break;

            case 0xA1:
                /* Clear DispTexture flag */
                pp->kind &= ~DispTexture;
                break;

            case 0xA2:
                /* Set gravity */
                ((u8*) &fval)[0] = pc[0];
                ((u8*) &fval)[1] = pc[1];
                ((u8*) &fval)[2] = pc[2];
                ((u8*) &fval)[3] = pc[3];
                pc += 4;
                pp->grav = fval;
                if (pp->grav == 0.0F) {
                    pp->kind &= ~1;
                } else {
                    pp->kind |= 1;
                }
                break;

            case 0xA3:
                /* Set friction */
                ((u8*) &fval)[0] = pc[0];
                ((u8*) &fval)[1] = pc[1];
                ((u8*) &fval)[2] = pc[2];
                ((u8*) &fval)[3] = pc[3];
                pc += 4;
                pp->fric = fval;
                if (pp->fric == 1.0F) {
                    pp->kind &= ~2;
                } else {
                    pp->kind |= 2;
                }
                break;

            case 0xA4:
                /* Spawn child particle by cmdList ID */
                {
                    int linkNo = pp->linkNo;
                    int bank = pp->bank;
                    int idx;
                    int palflag;

                    idx = (pc[0] << 8) + pc[1];
                    pc += 2;

                    if (linkNo >= 8) {
                        child = NULL;
                    } else if (bank >= 65) {
                        child = NULL;
                    } else if (idx >= psNumCmdList[bank]) {
                        child = NULL;
                    } else {
                        cl = psCmdListArray[bank][idx];
                        if (cl == NULL) {
                            child = NULL;
                        } else {
                            tg = psTexGroupArray[bank][cl->texGroup];
                            if (tg != NULL) {
                                palflag = tg->palflag;
                            } else {
                                palflag = 0;
                            }
                            child = psGenerateParticle0(
                                pp, linkNo, bank, cl->kind, cl->texGroup,
                                cl->cmdList, cl->life, 0.0F, 0.0F, 0.0F,
                                cl->vx, cl->vy, cl->vz, cl->size, cl->grav,
                                cl->fric, palflag, NULL, 0);
                        }
                    }
                    if (child != NULL) {
                        child->idnum = pp->idnum;
                        child->gen = pp->gen;
                        if (pp->gen != NULL) {
                            pp->gen->numChild++;
                        }
                        psAttachParticleAppSRT(child, pp->appsrt);
                        child->pos.x = pp->pos.x;
                        child->pos.y = pp->pos.y;
                        child->pos.z = pp->pos.z;
                        hsd_8039930C(child, pp);
                    }
                }
                break;

            case 0xF1:
                /* Spawn child particle from ptclref remap */
                {
                    int idx;
                    int palflag;
                    int linkNo;
                    int bank;

                    bank = pp->bank;
                    idx = (pc[0] << 8) + pc[1];
                    pc += 2;

                    if (ptclref_804D0E5C[bank] != NULL) {
                        idx = ptclref_804D0E5C[bank][idx];
                    }

                    linkNo = pp->linkNo;
                    (void) linkNo;
                    if (linkNo >= 8) {
                        child = NULL;
                    } else if (bank >= 65) {
                        child = NULL;
                    } else if (idx >= psNumCmdList[bank]) {
                        child = NULL;
                    } else {
                        cl = psCmdListArray[bank][idx];
                        if (cl == NULL) {
                            child = NULL;
                        } else {
                            tg = psTexGroupArray[bank][cl->texGroup];
                            if (tg != NULL) {
                                palflag = tg->palflag;
                            } else {
                                palflag = 0;
                            }
                            child = psGenerateParticle0(
                                pp, linkNo, bank, cl->kind, cl->texGroup,
                                cl->cmdList, cl->life, 0.0F, 0.0F, 0.0F,
                                cl->vx, cl->vy, cl->vz, cl->size, cl->grav,
                                cl->fric, palflag, NULL, 0);
                        }
                    }
                    if (child != NULL) {
                        child->idnum = pp->idnum;
                        child->gen = pp->gen;
                        if (pp->gen != NULL) {
                            pp->gen->numChild++;
                        }
                        psAttachParticleAppSRT(child, pp->appsrt);
                        child->pos.x = pp->pos.x;
                        child->pos.y = pp->pos.y;
                        child->pos.z = pp->pos.z;
                        hsd_8039930C(child, pp);
                    }
                }
                break;

            case 0xA5:
                /* Spawn child generator */
                {
                    int idx;

                    idx = (pc[0] << 8) + pc[1];
                    pc += 2;
                    gchild = hsd_8039F05C(pp->linkNo, pp->bank, idx);
                    if (gchild != NULL) {
                        HSD_psAppSRT* srt;
                        gchild->idnum = pp->idnum;
                        if (pp->gen != NULL) {
                            HSD_JObj* jobj = pp->gen->jobj;
                            gchild->jobj = jobj;
                            ref_INC(jobj);
                        }
                        gchild->type |= 0x100;
                        if (pp->gen != NULL) {
                            gchild->type |= pp->gen->type & 0x1E00;
                            if (gchild->kind & (1 << 17)) {
                                gchild->type &= ~(1 << 9);
                            }
                        }
                        if ((srt = pp->appsrt) != NULL) {
                            psAttachGeneratorAppSRT(gchild, srt);
                        }
                        if (pp->appsrt != NULL) {
                            if (gchild->appsrt == NULL) {
                                break;
                            }
                            if (pp->appsrt == gchild->appsrt) {
                                gchild->pos.x = pp->pos.x;
                                gchild->pos.y = pp->pos.y;
                                gchild->pos.z = pp->pos.z;
                            } else {
                                gchild->appsrt->translate.x =
                                    pp->appsrt->translate.x;
                                gchild->appsrt->translate.y =
                                    pp->appsrt->translate.y;
                                gchild->appsrt->translate.z =
                                    pp->appsrt->translate.z;
                            }
                        } else if (gchild->appsrt != NULL) {
                            gchild->appsrt->translate.x = pp->pos.x;
                            gchild->appsrt->translate.y = pp->pos.y;
                            gchild->appsrt->translate.z = pp->pos.z;
                        } else {
                            gchild->pos.x = pp->pos.x;
                            gchild->pos.y = pp->pos.y;
                            gchild->pos.z = pp->pos.z;
                        }
                    }
                }
                break;

            case 0xEF:
                /* Spawn generator with kind flags */
                {
                    int idx;
                    u8 flags;
                    HSD_psAppSRT* srt;

                    idx = (pc[0] << 8) + pc[1];
                    flags = pc[2];
                    pc += 3;
                    gchild = hsd_8039F05C(pp->linkNo, pp->bank, idx);
                    if (gchild == NULL) {
                        break;
                    }
                    gchild->idnum = pp->idnum;
                    if (pp->gen != NULL) {
                        HSD_JObj* jobj = pp->gen->jobj;
                        gchild->jobj = jobj;
                        ref_INC(jobj);
                    }
                    gchild->type |= 0x100;
                    if (pp->gen != NULL) {
                        gchild->type |= pp->gen->type & 0x1E00;
                        if (gchild->kind & (1 << 17)) {
                            gchild->type &= ~(1 << 9);
                        }
                    }
                    if ((srt = pp->appsrt) != NULL) {
                        psAttachGeneratorAppSRT(gchild, srt);
                    }
                    gchild->kind &= 0xF1FFFFFF;
                    gchild->kind |= ((flags & 7) << 25);
                    if (pp->appsrt != NULL) {
                        if (gchild->appsrt == NULL) {
                            break;
                        }
                        if (pp->appsrt == gchild->appsrt) {
                            gchild->pos.x = pp->pos.x;
                            gchild->pos.y = pp->pos.y;
                            gchild->pos.z = pp->pos.z;
                        } else {
                            gchild->appsrt->translate.x =
                                pp->appsrt->translate.x;
                            gchild->appsrt->translate.y =
                                pp->appsrt->translate.y;
                            gchild->appsrt->translate.z =
                                pp->appsrt->translate.z;
                        }
                    } else if (gchild->appsrt != NULL) {
                        gchild->appsrt->translate.x = pp->pos.x;
                        gchild->appsrt->translate.y = pp->pos.y;
                        gchild->appsrt->translate.z = pp->pos.z;
                    } else {
                        gchild->pos.x = pp->pos.x;
                        gchild->pos.y = pp->pos.y;
                        gchild->pos.z = pp->pos.z;
                    }
                }
                break;

            case 0xF0:
                /* Spawn generator with kind flags + ptclref remap */
                {
                    int idx;
                    u8 flags;
                    HSD_psAppSRT* srt;

                    idx = (pc[0] << 8) + pc[1];
                    flags = pc[2];
                    pc += 3;

                    if (ptclref_804D0E5C[pp->bank] != NULL) {
                        idx = ptclref_804D0E5C[pp->bank][idx];
                    }

                    gchild = hsd_8039F05C(pp->linkNo, pp->bank, idx);
                    if (gchild == NULL) {
                        break;
                    }
                    gchild->idnum = pp->idnum;
                    if (pp->gen != NULL) {
                        HSD_JObj* jobj = pp->gen->jobj;
                        gchild->jobj = jobj;
                        ref_INC(jobj);
                    }
                    gchild->type |= 0x100;
                    if (pp->gen != NULL) {
                        gchild->type |= pp->gen->type & 0x1E00;
                        if (gchild->kind & (1 << 17)) {
                            gchild->type &= ~(1 << 9);
                        }
                    }
                    if ((srt = pp->appsrt) != NULL) {
                        psAttachGeneratorAppSRT(gchild, srt);
                    }
                    gchild->kind &= 0xF1FFFFFF;
                    gchild->kind |= ((flags & 7) << 25);
                    if (pp->appsrt != NULL) {
                        if (gchild->appsrt == NULL) {
                            break;
                        }
                        if (pp->appsrt == gchild->appsrt) {
                            gchild->pos.x = pp->pos.x;
                            gchild->pos.y = pp->pos.y;
                            gchild->pos.z = pp->pos.z;
                        } else {
                            gchild->appsrt->translate.x =
                                pp->appsrt->translate.x;
                            gchild->appsrt->translate.y =
                                pp->appsrt->translate.y;
                            gchild->appsrt->translate.z =
                                pp->appsrt->translate.z;
                        }
                    } else if (gchild->appsrt != NULL) {
                        gchild->appsrt->translate.x = pp->pos.x;
                        gchild->appsrt->translate.y = pp->pos.y;
                        gchild->appsrt->translate.z = pp->pos.z;
                    } else {
                        gchild->pos.x = pp->pos.x;
                        gchild->pos.y = pp->pos.y;
                        gchild->pos.z = pp->pos.z;
                    }
                }
                break;

            case 0xA6:
                /* Set life with random offset */
                {
                    int baseLife;
                    int randomRange;
                    baseLife = (pc[0] << 8) + pc[1];
                    randomRange = (pc[2] << 8) + pc[3];
                    pc += 4;
                    pp->life =
                        baseLife + (s32) ((f32) randomRange * HSD_Randf());
                }
                break;

            case 0xA7:
                /* Conditional kill */
                {
                    u8 threshold = *pc++;
                    if (threshold >= (s32) (100.0F * HSD_Randf())) {
                        pp->life = 1;
                        goto exit_loop;
                    }
                }
                break;

            case 0xA8:
                /* Position random offset */
                {
                    u8* pc2;
                    fbytes[0] = *pc++;
                    fbytes[1] = *pc++;
                    fbytes[2] = *pc++;
                    fbytes[3] = *pc++;
                    pp->pos.x += 2.0F * fval * HSD_Randf() - fval;
                    pc2 = pc + 4;
                    fbytes[0] = pc[0];
                    fbytes[1] = pc[1];
                    fbytes[2] = pc[2];
                    fbytes[3] = pc[3];
                    pp->pos.y += 2.0F * fval * HSD_Randf() - fval;
                    pc = pc2 + 4;
                    fbytes[0] = pc2[0];
                    fbytes[1] = pc2[1];
                    fbytes[2] = pc2[2];
                    fbytes[3] = pc2[3];
                    pp->pos.z += 2.0F * fval * HSD_Randf() - fval;
                }
                break;

            case 0xA9:
                /* Call force function with float parameter */
                ((u8*) &fval)[0] = pc[0];
                ((u8*) &fval)[1] = pc[1];
                ((u8*) &fval)[2] = pc[2];
                ((u8*) &fval)[3] = pc[3];
                pc += 4;
                hsd_80398F8C(pp, fval);
                break;

            case 0xAA:
                /* Spawn child particle with random ptclref index */
                {
                    int baseIdx;
                    int randomRange;
                    int idx;
                    int palflag;
                    int linkNo;
                    int bank;

                    baseIdx = (pc[0] << 8) + pc[1];
                    randomRange = (pc[2] << 8) + pc[3];
                    pc += 4;

                    idx = baseIdx + (s32) ((f32) randomRange * HSD_Randf());

                    if (ptclref_804D0E5C[pp->bank] != NULL) {
                        idx = ptclref_804D0E5C[pp->bank][idx];
                    }

                    linkNo = pp->linkNo;
                    bank = pp->bank;
                    if (linkNo >= 8) {
                        child = NULL;
                    } else if (bank >= 65) {
                        child = NULL;
                    } else if (idx >= psNumCmdList[bank]) {
                        child = NULL;
                    } else {
                        cl = psCmdListArray[bank][idx];
                        if (cl == NULL) {
                            child = NULL;
                        } else {
                            tg = psTexGroupArray[bank][cl->texGroup];
                            if (tg != NULL) {
                                palflag = tg->palflag;
                            } else {
                                palflag = 0;
                            }
                            child = psGenerateParticle0(
                                pp, linkNo, bank, cl->kind, cl->texGroup,
                                cl->cmdList, cl->life, 0.0F, 0.0F, 0.0F,
                                cl->vx, cl->vy, cl->vz, cl->size, cl->grav,
                                cl->fric, palflag, NULL, 0);
                        }
                    }
                    if (child != NULL) {
                        child->pos.x = pp->pos.x;
                        child->pos.y = pp->pos.y;
                        child->pos.z = pp->pos.z;
                        child->idnum = pp->idnum;
                        child->gen = pp->gen;
                        if (pp->gen != NULL) {
                            pp->gen->numChild++;
                        }
                        {
                            HSD_psAppSRT* srt;
                            if ((srt = pp->appsrt) != NULL) {
                                psAttachParticleAppSRT(child, srt);
                            }
                        }
                        hsd_8039930C(child, pp);
                    }
                }
                break;

            case 0xAB:
                /* Velocity scale */
                ((u8*) &fval)[0] = pc[0];
                ((u8*) &fval)[1] = pc[1];
                ((u8*) &fval)[2] = pc[2];
                ((u8*) &fval)[3] = pc[3];
                pc += 4;
                pp->vel.x *= fval;
                pp->vel.y *= fval;
                pp->vel.z *= fval;
                break;

            case 0xAC:
                /* Size interpolation with random */
                {
                    f32 range;
                    pp->sizeCount = *pc++;
                    {
                        u16 cnt = pp->sizeCount;
                        if (cnt & 0x80) {
                            cnt = ((cnt & 0x7F) << 8) + *pc++;
                            pp->sizeCount = cnt;
                        }
                    }
                    ((u8*) &fval)[0] = pc[0];
                    ((u8*) &fval)[1] = pc[1];
                    ((u8*) &fval)[2] = pc[2];
                    ((u8*) &fval)[3] = pc[3];
                    pp->sizeTarget = fval;
                    ((u8*) &fval)[0] = pc[4];
                    ((u8*) &fval)[1] = pc[5];
                    ((u8*) &fval)[2] = pc[6];
                    ((u8*) &fval)[3] = pc[7];
                    range = fval;
                    pc += 8;
                    pp->sizeTarget += range * HSD_Randf();
                    if (pp->sizeCount == 0) {
                        pp->size = pp->sizeTarget;
                    }
                }
                break;

            case 0xAD:
                /* Set PrimEnv flag */
                pp->kind |= PrimEnv;
                break;

            case 0xAE:
                /* Clear Mirror flags */
                pp->kind &= ~(MirrorS | MirrorT);
                break;

            case 0xAF:
                /* Set MirrorS */
                pp->kind &= ~MirrorT;
                pp->kind |= MirrorS;
                break;

            case 0xB0:
                /* Set MirrorT */
                pp->kind &= ~MirrorS;
                pp->kind |= MirrorT;
                break;

            case 0xB1:
                /* Set MirrorS | MirrorT */
                pp->kind |= (MirrorS | MirrorT);
                break;

            case 0xB2:
                /* AppSRT matrix transform and detach */
                {
                    HSD_psAppSRT* srt = pp->appsrt;
                    if (srt == NULL) {
                        break;
                    }
                    if ((u8) srt->xA2 != 0) {
                        break;
                    }
                    hsd_803983A4(srt->gp);
                    srt = pp->appsrt;
                    {
                        Quaternion* rot = &srt->rot;
                        HSD_MtxSRT(srt->mmtx, &srt->scale, (Vec3*) rot,
                                   &srt->translate, NULL);
                    }
                    pp->pos.x = pp->appsrt->mmtx[0][1] * pp->pos.y +
                                pp->appsrt->mmtx[0][0] * pp->pos.x +
                                pp->appsrt->mmtx[0][2] * pp->pos.z +
                                pp->appsrt->mmtx[0][3];
                    pp->pos.y = pp->appsrt->mmtx[1][1] * pp->pos.y +
                                pp->appsrt->mmtx[1][0] * pp->pos.x +
                                pp->appsrt->mmtx[1][2] * pp->pos.z +
                                pp->appsrt->mmtx[1][3];
                    pp->pos.z = pp->appsrt->mmtx[2][1] * pp->pos.y +
                                pp->appsrt->mmtx[2][0] * pp->pos.x +
                                pp->appsrt->mmtx[2][2] * pp->pos.z +
                                pp->appsrt->mmtx[2][3];
                    psRemoveParticleAppSRT(pp);
                }
                break;

            case 0xB3:
                /* Alpha compare interpolation setup */
                {
                    s32 step;

                    if (pp->aCmpCount != 0) {
                        step =
                            ((s32) pp->aCmpRemain << 16) / (s32) pp->aCmpCount;
                        pp->aCmpParam1 =
                            (u8) ((((s32) pp->aCmpParam1Target << 16) +
                                   step * ((s32) pp->aCmpParam1 -
                                           (s32) pp->aCmpParam1Target)) >>
                                  16);
                        pp->aCmpParam2 =
                            (u8) ((((s32) pp->aCmpParam2Target << 16) +
                                   step * ((s32) pp->aCmpParam2 -
                                           (s32) pp->aCmpParam2Target)) >>
                                  16);
                    }
                    {
                        pp->aCmpCount = *pc++;
                        {
                            u16 cnt = pp->aCmpCount;
                            if (cnt & 0x80) {
                                cnt = ((cnt & 0x7F) << 8) + *pc++;
                                pp->aCmpCount = cnt;
                            }
                        }
                    }
                    pp->aCmpMode = *pc++;
                    pp->aCmpParam1Target = *pc++;
                    pp->aCmpParam2Target = *pc++;
                    if (pp->aCmpCount == 0) {
                        pp->aCmpParam1 = pp->aCmpParam1Target;
                        pp->aCmpParam2 = pp->aCmpParam2Target;
                        pp->aCmpRemain = 0;
                        pp->aCmpCount = 0;
                    } else {
                        pp->aCmpRemain = pp->aCmpCount;
                    }
                }
                break;

            case 0xB4:
                /* Set TexInterpNear */
                pp->kind |= TexInterpNear;
                break;

            case 0xB5:
                /* Clear TexInterpNear */
                pp->kind &= ~TexInterpNear;
                break;

            case 0xB6:
                /* Rotate interpolation setup */
                {
                    pp->rotateCount = *pc++;
                    {
                        u16 cnt = pp->rotateCount;
                        if (cnt & 0x80) {
                            cnt = ((cnt & 0x7F) << 8) + *pc++;
                            pp->rotateCount = cnt;
                        }
                    }
                    ((u8*) &fval)[0] = pc[0];
                    ((u8*) &fval)[1] = pc[1];
                    ((u8*) &fval)[2] = pc[2];
                    ((u8*) &fval)[3] = pc[3];
                    pc += 4;
                    pp->rotateTarget += fval;
                    if (pp->rotateCount == 0) {
                        pp->rotate = pp->rotateTarget;
                    }
                }
                break;

            case 0xB7:
                /* Aim velocity toward JObj */
                {
                    int idx = *pc++;
                    HSD_JObj* jobj;
                    f32 dx, dy, dz, dist_sq, dist;
                    f32 vel_mag_sq, vel_mag;

                    jobj = hsd_804D08E8[idx + pp->pJObjOfs];
                    if (jobj == NULL) {
                        break;
                    }
                    HSD_JObjSetupMatrix(jobj);
                    vel_mag_sq = pp->vel.x * pp->vel.x + pp->vel.y * pp->vel.y;
                    dx = jobj->mtx[0][3];
                    dx -= pp->pos.x;
                    vel_mag_sq += pp->vel.z * pp->vel.z;
                    dy = jobj->mtx[1][3];
                    dy -= pp->pos.y;
                    dz = jobj->mtx[2][3];
                    dz -= pp->pos.z;
                    vel_mag = sqrtf(vel_mag_sq);
                    dist_sq = dy * dy + dx * dx;
                    dist_sq += dz * dz;
                    if (dist_sq == 0.0) {
                        break;
                    }
                    dist = sqrtf(dist_sq);
                    {
                        f32 scale = vel_mag / dist;
                        pp->vel.x = dx * scale;
                        pp->vel.y = dy * scale;
                        pp->vel.z = dz * scale;
                    }
                }
                break;

            case 0xB8:
                /* Force toward JObj with kill on proximity */
                {
                    int idx = *pc++;
                    f32 force, range;

                    ((u8*) &fval)[0] = *pc++;
                    ((u8*) &fval)[1] = *pc++;
                    ((u8*) &fval)[2] = *pc++;
                    ((u8*) &fval)[3] = *pc++;
                    force = fval;
                    ((u8*) &fval)[0] = *pc++;
                    ((u8*) &fval)[1] = *pc++;
                    ((u8*) &fval)[2] = *pc++;
                    ((u8*) &fval)[3] = *pc++;
                    range = fval;
                    {
                        HSD_JObj* jobj = hsd_804D08E8[idx + pp->pJObjOfs];
                        if (hsd_803991D8((HSD_Generator*) pp, jobj, force,
                                         range) != 0)
                        {
                            pp->life = 1;
                            goto exit_loop;
                        }
                    }
                }
                break;

            case 0xB9:
                /* Spawn child particle + inherit pos and vel */
                {
                    int linkNo = pp->linkNo;
                    int bank = pp->bank;
                    int idx;
                    int palflag;

                    idx = (pc[0] << 8) + pc[1];
                    pc += 2;

                    if (linkNo >= 8) {
                        child = NULL;
                    } else if (bank >= 65) {
                        child = NULL;
                    } else if (idx >= psNumCmdList[bank]) {
                        child = NULL;
                    } else {
                        cl = psCmdListArray[bank][idx];
                        if (cl == NULL) {
                            child = NULL;
                        } else {
                            tg = psTexGroupArray[bank][cl->texGroup];
                            if (tg != NULL) {
                                palflag = tg->palflag;
                            } else {
                                palflag = 0;
                            }
                            child = psGenerateParticle0(
                                pp, linkNo, bank, cl->kind, cl->texGroup,
                                cl->cmdList, cl->life, 0.0F, 0.0F, 0.0F,
                                cl->vx, cl->vy, cl->vz, cl->size, cl->grav,
                                cl->fric, palflag, NULL, 0);
                        }
                    }
                    if (child != NULL) {
                        HSD_psAppSRT* srt;
                        child->pos.x = pp->pos.x;
                        child->pos.y = pp->pos.y;
                        child->pos.z = pp->pos.z;
                        child->vel.x = pp->vel.x;
                        child->vel.y = pp->vel.y;
                        child->vel.z = pp->vel.z;
                        child->idnum = pp->idnum;
                        child->gen = pp->gen;
                        if (pp->gen != NULL) {
                            pp->gen->numChild++;
                        }
                        if ((srt = pp->appsrt) != NULL) {
                            psAttachParticleAppSRT(child, srt);
                        }
                        hsd_8039930C(child, pp);
                    }
                }
                break;

            case 0xF2:
                /* Spawn child + inherit pos/vel + ptclref remap */
                {
                    int idx;
                    int palflag;
                    int linkNo;
                    int bank;

                    bank = pp->bank;
                    idx = (pc[0] << 8) + pc[1];
                    pc += 2;

                    if (ptclref_804D0E5C[bank] != NULL) {
                        idx = ptclref_804D0E5C[bank][idx];
                    }

                    linkNo = pp->linkNo;
                    if (linkNo >= 8) {
                        child = NULL;
                    } else if (bank >= 65) {
                        child = NULL;
                    } else if (idx >= psNumCmdList[bank]) {
                        child = NULL;
                    } else {
                        cl = psCmdListArray[bank][idx];
                        if (cl == NULL) {
                            child = NULL;
                        } else {
                            tg = psTexGroupArray[bank][cl->texGroup];
                            if (tg != NULL) {
                                palflag = tg->palflag;
                            } else {
                                palflag = 0;
                            }
                            child = psGenerateParticle0(
                                pp, linkNo, bank, cl->kind, cl->texGroup,
                                cl->cmdList, cl->life, 0.0F, 0.0F, 0.0F,
                                cl->vx, cl->vy, cl->vz, cl->size, cl->grav,
                                cl->fric, palflag, NULL, 0);
                        }
                    }
                    if (child != NULL) {
                        child->pos.x = pp->pos.x;
                        child->pos.y = pp->pos.y;
                        child->pos.z = pp->pos.z;
                        child->vel.x = pp->vel.x;
                        child->vel.y = pp->vel.y;
                        child->vel.z = pp->vel.z;
                        child->idnum = pp->idnum;
                        child->gen = pp->gen;
                        if (pp->gen != NULL) {
                            pp->gen->numChild++;
                        }
                        {
                            HSD_psAppSRT* srt;
                            if ((srt = pp->appsrt) != NULL) {
                                psAttachParticleAppSRT(child, srt);
                            }
                        }
                        hsd_8039930C(child, pp);
                    }
                }
                break;

            case 0xBA:
                /* PrimCol delta with random */
                {
                    s32 step;
                    s8 delta;
                    f32 rand_val;
                    f32 val;

                    if (pp->primColCount != 0) {
                        step = ((s32) pp->primColRemain << 16) /
                               (s32) pp->primColCount;
                        pp->primCol.r =
                            (u8) ((((s32) pp->primColTarget.r << 16) +
                                   step * ((s32) pp->primCol.r -
                                           (s32) pp->primColTarget.r)) >>
                                  16);
                        pp->primCol.g =
                            (u8) ((((s32) pp->primColTarget.g << 16) +
                                   step * ((s32) pp->primCol.g -
                                           (s32) pp->primColTarget.g)) >>
                                  16);
                        pp->primCol.b =
                            (u8) ((((s32) pp->primColTarget.b << 16) +
                                   step * ((s32) pp->primCol.b -
                                           (s32) pp->primColTarget.b)) >>
                                  16);
                        pp->primCol.a =
                            (u8) ((((s32) pp->primColTarget.a << 16) +
                                   step * ((s32) pp->primCol.a -
                                           (s32) pp->primColTarget.a)) >>
                                  16);
                    }

                    rand_val = HSD_Randf();
                    delta = (s8) *pc++;
                    rand_val *= (f32) (delta * 2);
                    val = (f32) pp->primColTarget.r + rand_val;
                    if (val < 0.0F) {
                        val = 0.0F;
                    }
                    if (val > 255.0F) {
                        val = 255.0F;
                    }
                    pp->primColTarget.r = (u8) (s32) val;

                    rand_val = HSD_Randf();
                    delta = (s8) *pc++;
                    rand_val *= (f32) (delta * 2);
                    val = (f32) pp->primColTarget.g + rand_val;
                    if (val < 0.0F) {
                        val = 0.0F;
                    }
                    if (val > 255.0F) {
                        val = 255.0F;
                    }
                    pp->primColTarget.g = (u8) (s32) val;

                    rand_val = HSD_Randf();
                    delta = (s8) *pc++;
                    rand_val *= (f32) (delta * 2);
                    val = (f32) pp->primColTarget.b + rand_val;
                    if (val < 0.0F) {
                        val = 0.0F;
                    }
                    if (val > 255.0F) {
                        val = 255.0F;
                    }
                    pp->primColTarget.b = (u8) (s32) val;

                    rand_val = HSD_Randf();
                    delta = (s8) *pc++;
                    rand_val *= (f32) (delta * 2);
                    val = (f32) pp->primColTarget.a + rand_val;
                    if (val < 0.0F) {
                        val = 0.0F;
                    }
                    if (val > 255.0F) {
                        val = 255.0F;
                    }
                    pp->primColTarget.a = (u8) (s32) val;

                    if (pp->primColCount == 0) {
                        pp->primCol = pp->primColTarget;
                    } else {
                        pp->primColRemain = pp->primColCount;
                    }
                }
                break;

            case 0xBB:
                /* EnvCol delta with random */
                {
                    s32 step;
                    s8 delta;
                    f32 rand_val;
                    f32 val;

                    if (pp->envColCount != 0) {
                        step = ((s32) pp->envColRemain << 16) /
                               (s32) pp->envColCount;
                        pp->envCol.r =
                            (u8) ((((s32) pp->envColTarget.r << 16) +
                                   step * ((s32) pp->envCol.r -
                                           (s32) pp->envColTarget.r)) >>
                                  16);
                        pp->envCol.g =
                            (u8) ((((s32) pp->envColTarget.g << 16) +
                                   step * ((s32) pp->envCol.g -
                                           (s32) pp->envColTarget.g)) >>
                                  16);
                        pp->envCol.b =
                            (u8) ((((s32) pp->envColTarget.b << 16) +
                                   step * ((s32) pp->envCol.b -
                                           (s32) pp->envColTarget.b)) >>
                                  16);
                        pp->envCol.a =
                            (u8) ((((s32) pp->envColTarget.a << 16) +
                                   step * ((s32) pp->envCol.a -
                                           (s32) pp->envColTarget.a)) >>
                                  16);
                    }

                    rand_val = HSD_Randf();
                    delta = (s8) *pc++;
                    rand_val *= (f32) (delta * 2);
                    val = (f32) pp->envColTarget.r + rand_val;
                    if (val < 0.0F) {
                        val = 0.0F;
                    }
                    if (val > 255.0F) {
                        val = 255.0F;
                    }
                    pp->envColTarget.r = (u8) (s32) val;

                    rand_val = HSD_Randf();
                    delta = (s8) *pc++;
                    rand_val *= (f32) (delta * 2);
                    val = (f32) pp->envColTarget.g + rand_val;
                    if (val < 0.0F) {
                        val = 0.0F;
                    }
                    if (val > 255.0F) {
                        val = 255.0F;
                    }
                    pp->envColTarget.g = (u8) (s32) val;

                    rand_val = HSD_Randf();
                    delta = (s8) *pc++;
                    rand_val *= (f32) (delta * 2);
                    val = (f32) pp->envColTarget.b + rand_val;
                    if (val < 0.0F) {
                        val = 0.0F;
                    }
                    if (val > 255.0F) {
                        val = 255.0F;
                    }
                    pp->envColTarget.b = (u8) (s32) val;

                    rand_val = HSD_Randf();
                    delta = (s8) *pc++;
                    rand_val *= (f32) (delta * 2);
                    val = (f32) pp->envColTarget.a + rand_val;
                    if (val < 0.0F) {
                        val = 0.0F;
                    }
                    if (val > 255.0F) {
                        val = 255.0F;
                    }
                    pp->envColTarget.a = (u8) (s32) val;

                    if (pp->envColCount == 0) {
                        pp->envCol = pp->envColTarget;
                    } else {
                        pp->envColRemain = pp->envColCount;
                    }
                }
                break;

            case 0xBC:
                /* PoseNum with random */
                {
                    int randRange;

                    pp->poseNum = *pc++;
                    randRange = *pc++;
                    pp->poseNum = (u8) (s32) ((f32) randRange * HSD_Randf() +
                                              (f32) pp->poseNum);
                    {
                        u8 bank = pp->bank;
                        u8 tgIdx = pp->texGroup;
                        HSD_PSTexGroup** tga;
                        HSD_PSTexGroup* texGrp;

                        tga = psTexGroupArray[bank];
                        texGrp = tga[tgIdx];
                        if (texGrp != NULL && texGrp->texTable != NULL) {
                            if (texGrp->texTable[pp->poseNum] != NULL) {
                                pp->kind |= DispTexture;
                            }
                        }
                    }
                }
                break;

            case 0xBD:
                /* Normalize velocity to target speed */
                {
                    f32 base_speed, random_range, target_speed;
                    f32 mag;

                    ((u8*) &fval)[0] = pc[0];
                    ((u8*) &fval)[1] = pc[1];
                    ((u8*) &fval)[2] = pc[2];
                    ((u8*) &fval)[3] = pc[3];
                    base_speed = fval;
                    ((u8*) &fval)[0] = pc[4];
                    ((u8*) &fval)[1] = pc[5];
                    ((u8*) &fval)[2] = pc[6];
                    ((u8*) &fval)[3] = pc[7];
                    random_range = fval;
                    pc += 8;
                    target_speed = base_speed + random_range * HSD_Randf();
                    mag = pp->vel.x * pp->vel.x + pp->vel.y * pp->vel.y +
                          pp->vel.z * pp->vel.z;
                    mag = sqrtf(mag);
                    if (mag > 0.0F) {
                        target_speed /= mag;
                        pp->vel.x *= target_speed;
                        pp->vel.y *= target_speed;
                        pp->vel.z *= target_speed;
                    }
                }
                break;

            case 0xBE:
                /* Velocity component multiply */
                ((u8*) &fval)[0] = pc[0];
                ((u8*) &fval)[1] = pc[1];
                ((u8*) &fval)[2] = pc[2];
                ((u8*) &fval)[3] = pc[3];
                pp->vel.x *= fval;
                ((u8*) &fval)[0] = pc[4];
                ((u8*) &fval)[1] = pc[5];
                ((u8*) &fval)[2] = pc[6];
                ((u8*) &fval)[3] = pc[7];
                pp->vel.y *= fval;
                ((u8*) &fval)[0] = pc[8];
                ((u8*) &fval)[1] = pc[9];
                ((u8*) &fval)[2] = pc[10];
                ((u8*) &fval)[3] = pc[11];
                pc += 12;
                pp->vel.z *= fval;
                break;

            case 0xBF:
                /* JObj offset */
                {
                    u8 idx = *pc++;
                    pp->kind |= (((idx + pp->pJObjOfs) & 7) << 12) | 0x8000;
                }
                break;

            case 0xC0:
                /* PrimCol selective channel setup */
                {
                    s32 step;
                    u16 cnt;

                    if (pp->primColCount != 0) {
                        step = ((s32) pp->primColRemain << 16) /
                               (s32) pp->primColCount;
                        pp->primCol.r =
                            (u8) ((((s32) pp->primColTarget.r << 16) +
                                   step * ((s32) pp->primCol.r -
                                           (s32) pp->primColTarget.r)) >>
                                  16);
                        pp->primCol.g =
                            (u8) ((((s32) pp->primColTarget.g << 16) +
                                   step * ((s32) pp->primCol.g -
                                           (s32) pp->primColTarget.g)) >>
                                  16);
                        pp->primCol.b =
                            (u8) ((((s32) pp->primColTarget.b << 16) +
                                   step * ((s32) pp->primCol.b -
                                           (s32) pp->primColTarget.b)) >>
                                  16);
                        pp->primCol.a =
                            (u8) ((((s32) pp->primColTarget.a << 16) +
                                   step * ((s32) pp->primCol.a -
                                           (s32) pp->primColTarget.a)) >>
                                  16);
                    }
                    pp->primColCount = *pc++;
                    cnt = pp->primColCount;
                    if (cnt & 0x80) {
                        cnt = ((cnt & 0x7F) << 8) + *pc++;
                        pp->primColCount = cnt;
                    }
                    pp->primColTarget = pp->primCol;
                    if (opcode & 1) {
                        pp->primColTarget.r = *pc++;
                    }
                    if (opcode & 2) {
                        pp->primColTarget.g = *pc++;
                    }
                    if (opcode & 4) {
                        pp->primColTarget.b = *pc++;
                    }
                    if (opcode & 8) {
                        pp->primColTarget.a = *pc++;
                    }
                    if (pp->primColCount == 0) {
                        pp->primCol = pp->primColTarget;
                        pp->primColRemain = 0;
                    } else {
                        pp->primColRemain = pp->primColCount;
                    }
                }
                break;

            case 0xD0:
                /* EnvCol selective channel setup */
                {
                    s32 step;
                    u16 cnt;

                    if (pp->envColCount != 0) {
                        step = ((s32) pp->envColRemain << 16) /
                               (s32) pp->envColCount;
                        pp->envCol.r =
                            (u8) ((((s32) pp->envColTarget.r << 16) +
                                   step * ((s32) pp->envCol.r -
                                           (s32) pp->envColTarget.r)) >>
                                  16);
                        pp->envCol.g =
                            (u8) ((((s32) pp->envColTarget.g << 16) +
                                   step * ((s32) pp->envCol.g -
                                           (s32) pp->envColTarget.g)) >>
                                  16);
                        pp->envCol.b =
                            (u8) ((((s32) pp->envColTarget.b << 16) +
                                   step * ((s32) pp->envCol.b -
                                           (s32) pp->envColTarget.b)) >>
                                  16);
                        pp->envCol.a =
                            (u8) ((((s32) pp->envColTarget.a << 16) +
                                   step * ((s32) pp->envCol.a -
                                           (s32) pp->envColTarget.a)) >>
                                  16);
                    }
                    pp->envColCount = *pc++;
                    cnt = pp->envColCount;
                    if (cnt & 0x80) {
                        cnt = ((cnt & 0x7F) << 8) + *pc++;
                        pp->envColCount = cnt;
                    }
                    pp->envColTarget = pp->envCol;
                    if (opcode & 1) {
                        pp->envColTarget.r = *pc++;
                    }
                    if (opcode & 2) {
                        pp->envColTarget.g = *pc++;
                    }
                    if (opcode & 4) {
                        pp->envColTarget.b = *pc++;
                    }
                    if (opcode & 8) {
                        pp->envColTarget.a = *pc++;
                    }
                    if (pp->envColCount == 0) {
                        pp->envCol = pp->envColTarget;
                        pp->envColRemain = 0;
                    } else {
                        pp->envColRemain = pp->envColCount;
                    }
                }
                break;

            case 0xE0:
                /* Dual delta PrimCol + EnvCol */
                {
                    s32 step;
                    s8 delta;
                    f32 rand_val;
                    f32 val;

                    if (pp->primColCount != 0) {
                        step = ((s32) pp->primColRemain << 16) /
                               (s32) pp->primColCount;
                        pp->primCol.r =
                            (u8) ((((s32) pp->primColTarget.r << 16) +
                                   step * ((s32) pp->primCol.r -
                                           (s32) pp->primColTarget.r)) >>
                                  16);
                        pp->primCol.g =
                            (u8) ((((s32) pp->primColTarget.g << 16) +
                                   step * ((s32) pp->primCol.g -
                                           (s32) pp->primColTarget.g)) >>
                                  16);
                        pp->primCol.b =
                            (u8) ((((s32) pp->primColTarget.b << 16) +
                                   step * ((s32) pp->primCol.b -
                                           (s32) pp->primColTarget.b)) >>
                                  16);
                        pp->primCol.a =
                            (u8) ((((s32) pp->primColTarget.a << 16) +
                                   step * ((s32) pp->primCol.a -
                                           (s32) pp->primColTarget.a)) >>
                                  16);
                    }
                    if (pp->envColCount != 0) {
                        step = ((s32) pp->envColRemain << 16) /
                               (s32) pp->envColCount;
                        pp->envCol.r =
                            (u8) ((((s32) pp->envColTarget.r << 16) +
                                   step * ((s32) pp->envCol.r -
                                           (s32) pp->envColTarget.r)) >>
                                  16);
                        pp->envCol.g =
                            (u8) ((((s32) pp->envColTarget.g << 16) +
                                   step * ((s32) pp->envCol.g -
                                           (s32) pp->envColTarget.g)) >>
                                  16);
                        pp->envCol.b =
                            (u8) ((((s32) pp->envColTarget.b << 16) +
                                   step * ((s32) pp->envCol.b -
                                           (s32) pp->envColTarget.b)) >>
                                  16);
                        pp->envCol.a =
                            (u8) ((((s32) pp->envColTarget.a << 16) +
                                   step * ((s32) pp->envCol.a -
                                           (s32) pp->envColTarget.a)) >>
                                  16);
                    }

                    rand_val = HSD_Randf();

                    delta = (s8) *pc++;
                    rand_val *= (f32) (delta * 2);
                    val = rand_val + (f32) pp->primColTarget.r;
                    if (val < 0.0F) {
                        val = 0.0F;
                    }
                    if (val > 255.0F) {
                        val = 255.0F;
                    }
                    pp->primColTarget.r = (u8) (s32) val;
                    val = rand_val + (f32) pp->envColTarget.r;
                    if (val < 0.0F) {
                        val = 0.0F;
                    }
                    if (val > 255.0F) {
                        val = 255.0F;
                    }
                    pp->envColTarget.r = (u8) (s32) val;

                    rand_val = HSD_Randf();
                    delta = (s8) *pc++;
                    rand_val *= (f32) (delta * 2);
                    val = rand_val + (f32) pp->primColTarget.g;
                    if (val < 0.0F) {
                        val = 0.0F;
                    }
                    if (val > 255.0F) {
                        val = 255.0F;
                    }
                    pp->primColTarget.g = (u8) (s32) val;
                    val = rand_val + (f32) pp->envColTarget.g;
                    if (val < 0.0F) {
                        val = 0.0F;
                    }
                    if (val > 255.0F) {
                        val = 255.0F;
                    }
                    pp->envColTarget.g = (u8) (s32) val;

                    rand_val = HSD_Randf();
                    delta = (s8) *pc++;
                    rand_val *= (f32) (delta * 2);
                    val = rand_val + (f32) pp->primColTarget.b;
                    if (val < 0.0F) {
                        val = 0.0F;
                    }
                    if (val > 255.0F) {
                        val = 255.0F;
                    }
                    pp->primColTarget.b = (u8) (s32) val;
                    val = rand_val + (f32) pp->envColTarget.b;
                    if (val < 0.0F) {
                        val = 0.0F;
                    }
                    if (val > 255.0F) {
                        val = 255.0F;
                    }
                    pp->envColTarget.b = (u8) (s32) val;

                    rand_val = HSD_Randf();
                    delta = (s8) *pc++;
                    rand_val *= (f32) (delta * 2);
                    val = rand_val + (f32) pp->primColTarget.a;
                    if (val < 0.0F) {
                        val = 0.0F;
                    }
                    if (val > 255.0F) {
                        val = 255.0F;
                    }
                    pp->primColTarget.a = (u8) (s32) val;
                    val = rand_val + (f32) pp->envColTarget.a;
                    if (val < 0.0F) {
                        val = 0.0F;
                    }
                    if (val > 255.0F) {
                        val = 255.0F;
                    }
                    pp->envColTarget.a = (u8) (s32) val;

                    if (pp->primColCount == 0) {
                        pp->primCol = pp->primColTarget;
                    }
                    pp->primColRemain = pp->primColCount;
                    if (pp->envColCount == 0) {
                        pp->envCol = pp->envColTarget;
                    }
                    pp->envColRemain = pp->envColCount;
                }
                break;

            case 0xE9:
                /* Dual PrimCol + EnvCol interp + selective random delta */
                {
                    s32 step;
                    int timing;
                    int flags;
                    f32 scale;
                    s8 delta;
                    f32 delta_float;
                    f32 val;

                    /* Interpolate primCol */
                    if (pp->primColCount != 0) {
                        step = ((s32) pp->primColRemain << 16) /
                               (s32) pp->primColCount;
                        pp->primCol.r =
                            (u8) ((((s32) pp->primColTarget.r << 16) +
                                   step * ((s32) pp->primCol.r -
                                           (s32) pp->primColTarget.r)) >>
                                  16);
                        pp->primCol.g =
                            (u8) ((((s32) pp->primColTarget.g << 16) +
                                   step * ((s32) pp->primCol.g -
                                           (s32) pp->primColTarget.g)) >>
                                  16);
                        pp->primCol.b =
                            (u8) ((((s32) pp->primColTarget.b << 16) +
                                   step * ((s32) pp->primCol.b -
                                           (s32) pp->primColTarget.b)) >>
                                  16);
                        pp->primCol.a =
                            (u8) ((((s32) pp->primColTarget.a << 16) +
                                   step * ((s32) pp->primCol.a -
                                           (s32) pp->primColTarget.a)) >>
                                  16);
                    }

                    /* Interpolate envCol */
                    if (pp->envColCount != 0) {
                        step = ((s32) pp->envColRemain << 16) /
                               (s32) pp->envColCount;
                        pp->envCol.r =
                            (u8) ((((s32) pp->envColTarget.r << 16) +
                                   step * ((s32) pp->envCol.r -
                                           (s32) pp->envColTarget.r)) >>
                                  16);
                        pp->envCol.g =
                            (u8) ((((s32) pp->envColTarget.g << 16) +
                                   step * ((s32) pp->envCol.g -
                                           (s32) pp->envColTarget.g)) >>
                                  16);
                        pp->envCol.b =
                            (u8) ((((s32) pp->envColTarget.b << 16) +
                                   step * ((s32) pp->envCol.b -
                                           (s32) pp->envColTarget.b)) >>
                                  16);
                        pp->envCol.a =
                            (u8) ((((s32) pp->envColTarget.a << 16) +
                                   step * ((s32) pp->envCol.a -
                                           (s32) pp->envColTarget.a)) >>
                                  16);
                    }

                    /* Read timing and flags from bytecode */
                    flags = *pc++;
                    timing = *pc++;

                    /* Compute scale from timing */
                    if (timing != 0) {
                        scale =
                            (f32) (s32) ((f32) (timing + 1) * HSD_Randf()) /
                            (f32) timing;
                    } else {
                        scale = HSD_Randf();
                    }

                    /* R channel delta */
                    if (flags & 0x01) {
                        delta = (s8) *pc++;
                        delta_float = scale * (f32) (delta * 2);
                        if (flags & 0x10) {
                            val = delta_float + (f32) pp->primColTarget.r;
                            if (val < 0.0F) {
                                val = 0.0F;
                            }
                            if (val > 255.0F) {
                                val = 255.0F;
                            }
                            pp->primColTarget.r = (u8) (s32) val;
                        }
                        if (flags & 0x20) {
                            val = delta_float + (f32) pp->envColTarget.r;
                            if (val < 0.0F) {
                                val = 0.0F;
                            }
                            if (val > 255.0F) {
                                val = 255.0F;
                            }
                            pp->envColTarget.r = (u8) (s32) val;
                        }
                    }

                    /* G channel delta */
                    if (flags & 0x02) {
                        delta = (s8) *pc++;
                        delta_float = scale * (f32) (delta * 2);
                        if (flags & 0x10) {
                            val = delta_float + (f32) pp->primColTarget.g;
                            if (val < 0.0F) {
                                val = 0.0F;
                            }
                            if (val > 255.0F) {
                                val = 255.0F;
                            }
                            pp->primColTarget.g = (u8) (s32) val;
                        }
                        if (flags & 0x20) {
                            val = delta_float + (f32) pp->envColTarget.g;
                            if (val < 0.0F) {
                                val = 0.0F;
                            }
                            if (val > 255.0F) {
                                val = 255.0F;
                            }
                            pp->envColTarget.g = (u8) (s32) val;
                        }
                    }

                    /* B channel delta */
                    if (flags & 0x04) {
                        delta = (s8) *pc++;
                        delta_float = scale * (f32) (delta * 2);
                        if (flags & 0x10) {
                            val = delta_float + (f32) pp->primColTarget.b;
                            if (val < 0.0F) {
                                val = 0.0F;
                            }
                            if (val > 255.0F) {
                                val = 255.0F;
                            }
                            pp->primColTarget.b = (u8) (s32) val;
                        }
                        if (flags & 0x20) {
                            val = delta_float + (f32) pp->envColTarget.b;
                            if (val < 0.0F) {
                                val = 0.0F;
                            }
                            if (val > 255.0F) {
                                val = 255.0F;
                            }
                            pp->envColTarget.b = (u8) (s32) val;
                        }
                    }

                    /* A channel delta (separate random) */
                    if (flags & 0x08) {
                        f32 a_rand;
                        a_rand = HSD_Randf();
                        delta = (s8) *pc++;
                        delta_float =
                            (f32) (s32) ((f32) (timing + 1) * a_rand) /
                            (f32) timing * (f32) (delta * 2);
                        if (flags & 0x10) {
                            val = delta_float + (f32) pp->primColTarget.a;
                            if (val < 0.0F) {
                                val = 0.0F;
                            }
                            if (val > 255.0F) {
                                val = 255.0F;
                            }
                            pp->primColTarget.a = (u8) (s32) val;
                        }
                        if (flags & 0x20) {
                            val = delta_float + (f32) pp->envColTarget.a;
                            if (val < 0.0F) {
                                val = 0.0F;
                            }
                            if (val > 255.0F) {
                                val = 255.0F;
                            }
                            pp->envColTarget.a = (u8) (s32) val;
                        }
                    }

                    /* Final: sync current from target if count is 0 */
                    if (pp->primColCount == 0) {
                        pp->primCol = pp->primColTarget;
                    }
                    pp->primColRemain = pp->primColCount;
                    if (pp->envColCount == 0) {
                        pp->envCol = pp->envColTarget;
                    }
                    pp->envColRemain = pp->envColCount;
                }
                break;

            case 0xE1:
                /* Callback set */
                {
                    int idx = *pc++;
                    if (idx == 0) {
                        pp->callback = NULL;
                    } else {
                        pp->callback = psCallback[idx - 1];
                    }
                }
                break;

            case 0xEC:
                /* UserData set */
                {
                    int idx = *pc++;
                    ((u8*) &fval)[0] = pc[0];
                    ((u8*) &fval)[1] = pc[1];
                    ((u8*) &fval)[2] = pc[2];
                    ((u8*) &fval)[3] = pc[3];
                    pc += 4;
                    if (pp->gen->userfunc != NULL &&
                        pp->gen->userfunc->setUserData != NULL)
                    {
                        pp->gen->userfunc->setUserData(pp, idx, fval);
                    } else if (pp->userdata != NULL) {
                        pp->userdata[idx] = fval;
                    }
                }
                break;

            case 0xE2:
                /* Set TexEdge (kill) bit */
                pp->kind |= TexEdge;
                break;

            case 0xE3:
                /* Set palNum */
                pp->palNum = *pc++;
                break;

            case 0xE4:
                /* TexFlipS control */
                {
                    u8 mode = *pc++ & 0x3;
                    switch (mode) {
                    case 0:
                        pp->kind &= ~TexFlipS;
                        break;
                    case 1:
                        pp->kind |= TexFlipS;
                        break;
                    case 2:
                        pp->kind ^= TexFlipS;
                        break;
                    case 3:
                        if (HSD_Randf() < 0.5F) {
                            pp->kind &= ~TexFlipS;
                        } else {
                            pp->kind |= TexFlipS;
                        }
                        break;
                    }
                }
                break;

            case 0xE5:
                /* TexFlipT control */
                {
                    u8 mode = *pc++ & 0x3;
                    switch (mode) {
                    case 0:
                        pp->kind &= ~TexFlipT;
                        break;
                    case 1:
                        pp->kind |= TexFlipT;
                        break;
                    case 2:
                        pp->kind ^= TexFlipT;
                        break;
                    case 3:
                        if (HSD_Randf() < 0.5F) {
                            pp->kind &= ~TexFlipT;
                        } else {
                            pp->kind |= TexFlipT;
                        }
                        break;
                    }
                }
                break;

            case 0xE6:
                /* Set DirVec */
                pp->kind |= DirVec;
                break;

            case 0xE7:
                /* Clear DirVec */
                pp->kind &= ~DirVec;
                break;

            case 0xE8:
                /* Trail control */
                ((u8*) &fval)[0] = pc[0];
                ((u8*) &fval)[1] = pc[1];
                ((u8*) &fval)[2] = pc[2];
                ((u8*) &fval)[3] = pc[3];
                pc += 4;
                if (fval < 0.0F) {
                    pp->kind &= ~Trail;
                } else {
                    pp->kind |= Trail;
                    pp->trail = fval;
                }
                break;

            case 0xEA:
                /* MatCol interpolation setup */
                {
                    s32 step;
                    u16 cnt;
                    u8 flags;

                    if (pp->matColCount != 0) {
                        step = ((s32) pp->matColRemain << 16) /
                               (s32) pp->matColCount;
                        pp->matRGB = (u8) ((((s32) pp->matRGBTarget << 16) +
                                            step * ((s32) pp->matRGB -
                                                    (s32) pp->matRGBTarget)) >>
                                           16);
                        pp->matA = (u8) ((((s32) pp->matATarget << 16) +
                                          step * ((s32) pp->matA -
                                                  (s32) pp->matATarget)) >>
                                         16);
                    }
                    pp->matColCount = *pc++;
                    cnt = pp->matColCount;
                    if (cnt & 0x80) {
                        cnt = ((cnt & 0x7F) << 8) + *pc++;
                        pp->matColCount = cnt;
                    }
                    flags = *pc++;
                    pp->matRGBTarget = pp->matRGB;
                    if (flags & 1) {
                        pp->matRGBTarget = *pc++;
                    }
                    if (flags & 8) {
                        pp->matATarget = *pc++;
                    }
                    if (pp->matColCount == 0) {
                        pp->matRGB = pp->matRGBTarget;
                        pp->matColRemain = 0;
                    } else {
                        pp->matColRemain = pp->matColCount;
                    }
                }
                break;

            case 0xEB:
                /* AmbCol interpolation setup */
                {
                    s32 step;
                    u16 cnt;
                    u8 flags;

                    if (pp->ambColCount != 0) {
                        step = ((s32) pp->ambColRemain << 16) /
                               (s32) pp->ambColCount;
                        pp->ambRGB = (u8) ((((s32) pp->ambRGBTarget << 16) +
                                            step * ((s32) pp->ambRGB -
                                                    (s32) pp->ambRGBTarget)) >>
                                           16);
                        pp->ambA = (u8) ((((s32) pp->ambATarget << 16) +
                                          step * ((s32) pp->ambA -
                                                  (s32) pp->ambATarget)) >>
                                         16);
                    }
                    pp->ambColCount = *pc++;
                    cnt = pp->ambColCount;
                    if (cnt & 0x80) {
                        cnt = ((cnt & 0x7F) << 8) + *pc++;
                        pp->ambColCount = cnt;
                    }
                    flags = *pc++;
                    pp->ambRGBTarget = pp->ambRGB;
                    if (flags & 1) {
                        pp->ambRGBTarget = *pc++;
                    }
                    if (flags & 8) {
                        pp->ambATarget = *pc++;
                    }
                    if (pp->ambColCount == 0) {
                        pp->ambRGB = pp->ambRGBTarget;
                        pp->ambColRemain = 0;
                    } else {
                        pp->ambColRemain = pp->ambColCount;
                    }
                }
                break;

            case 0xED:
                /* Rotate interpolation with random */
                {
                    f32 base_val;
                    f32 range_val;
                    int timing;
                    f32 result;

                    ((u8*) &fval)[0] = pc[0];
                    ((u8*) &fval)[1] = pc[1];
                    ((u8*) &fval)[2] = pc[2];
                    ((u8*) &fval)[3] = pc[3];
                    base_val = fval;
                    ((u8*) &fval)[0] = pc[4];
                    ((u8*) &fval)[1] = pc[5];
                    ((u8*) &fval)[2] = pc[6];
                    ((u8*) &fval)[3] = pc[7];
                    range_val = fval;
                    timing = pc[8];
                    pc += 9;

                    if (timing != 0) {
                        s32 randi = (s32) ((f32) (timing + 1) * HSD_Randf());
                        result =
                            base_val + range_val * (f32) randi / (f32) timing;
                    } else {
                        result = base_val + range_val * HSD_Randf();
                    }
                    pp->rotateTarget += result;
                    pp->rotate += result;
                }
                break;

            case 0xFA:
                /* Loop mark */
                pp->loopCount = *pc++;
                pp->cmdLoopPtr = (u16) (pc - pp->cmdList);
                break;

            case 0xFB:
                /* Loop back */
                if (--pp->loopCount != 0) {
                    pc = pp->cmdList + pp->cmdLoopPtr;
                }
                break;

            case 0xFC:
                /* Mark set */
                pp->cmdMarkPtr = (u16) (pc - pp->cmdList);
                break;

            case 0xFD:
                /* Mark jump */
                pc = pp->cmdList + pp->cmdMarkPtr;
                break;

            case 0xFE:
            case 0xFF:
                /* End: set life to 1 */
                pp->life = 1;
                goto exit_loop;

            default:
                break;
            }
        }

        /* Loop continuation check */
        if (operand != 0) {
            break;
        }
    }

exit_loop:
    /* Save bytecode state */
    pp->cmdPtr = (u16) (pc - pp->cmdList);
    pp->cmdWait = operand;

do_life:
    /* Life countdown */
    if (--pp->life == 0) {
        /* Call hookDelete if available */
        if (pp->gen != NULL && pp->gen->userfunc != NULL &&
            pp->gen->userfunc->hookDelete != NULL)
        {
            pp->gen->userfunc->hookDelete(pp);
        }

        /* Unlink from list */
        if (prev == NULL) {
            hsd_804D0908[pp->linkNo] = pp->next;
        } else {
            prev->next = pp->next;
        }

        /* Decrement generator child count */
        {
            HSD_Particle* next_pp = pp->next;
            if (pp->gen != NULL) {
                pp->gen->numChild--;
            }

            /* Free appsrt */
            if (pp->appsrt != NULL) {
                if (psRemoveParticleAppSRT(pp) == 0 && prev == NULL) {
                    HSD_Particle* head = hsd_804D0908[pp->linkNo];
                    if (head != next_pp) {
                        next_pp = head;
                    }
                }
            }

            /* Free particle */
            hsd_8039D048(pp);
            HSD_ObjFree(&hsd_804D0F60.alloc_data, pp);
            hsd_804D78E2[0]--;
            return next_pp;
        }
    }

    /* --- Physics update --- */
    if (pp->kind & Tornado) {
        /* Tornado rotational physics */
        HSD_Generator* gp = pp->gen;
        f32 sinA, sinB, cosA, cosB;
        f32 R;
        f32 d, e, nd, vz;
        f32 t0, t1, t2, t3, t4;

        sinA = sinf(pp->grav);
        sinB = sinf(pp->fric);
        cosA = cosf(pp->grav);
        cosB = cosf(pp->fric);

        pp->vel.z += gp->aux.tornado.vel;

        R = gp->radius;
        if (R < 0.0F) {
            R = -R;
        }
        {
            f32 ang = gp->angle;
            if (ang < 0.0F) {
                ang = -ang;
            }
            R = pp->vel.z * tanf(ang) + R;
        }
        pp->vel.x += gp->grav;
        R *= pp->vel.y;

        d = R * cosf(pp->vel.x);
        e = R * sinf(pp->vel.x);
        nd = -d;
        vz = pp->vel.z;

        /* Rotation matrix application */
        t0 = vz * sinB;
        t1 = e * cosA;
        t2 = nd * sinA;
        t3 = d * cosB + t0;
        t0 = vz * sinA;
        t1 = sinB * t2 + t1;
        pp->pos.x = gp->pos.x + t3;
        t2 = nd * cosA;
        t4 = e * sinA;
        t1 = cosB * t0 + t1;
        t0 = vz * cosA;
        t4 = sinB * t2 - t4;
        pp->pos.y = gp->pos.y + t1;
        t4 = cosB * t0 + t4;
        pp->pos.z = gp->pos.z + t4;
    } else {
        /* Simple physics */
        if (pp->kind & 1) {
            pp->vel.y -= pp->grav;
        }
        if (pp->kind & 2) {
            pp->vel.x *= pp->fric;
            pp->vel.y *= pp->fric;
            pp->vel.z *= pp->fric;
        }
        pp->pos.x += pp->vel.x;
        pp->pos.y += pp->vel.y;
        pp->pos.z += pp->vel.z;
    }

    /* JObj attachment - update JObj position to match particle */
    if (pp->kind & 0x8000) {
        s32 jobj_idx = (pp->kind >> 12) & 7;
        HSD_JObj* jobj;
        HSD_JObj** jobj_slot;

        /* Allocate JObj if slot is empty */
        if (hsd_804D08E8[jobj_idx] == NULL) {
            HSD_JObj* new_jobj = HSD_JObjAlloc();
            if (new_jobj != NULL) {
                hsd_8039CF4C(jobj_idx + 1, new_jobj);
                HSD_JObjUnref(new_jobj);
            }
        }

        jobj_slot = &hsd_804D08E8[jobj_idx];
        jobj = *jobj_slot;

        if (jobj != NULL) {
            HSD_JObjSetupMatrix(jobj);

            jobj = *jobj_slot;
            HSD_JObjAddTranslationX(jobj, pp->pos.x - jobj->mtx[0][3]);

            jobj = *jobj_slot;
            HSD_JObjAddTranslationY(jobj, pp->pos.y - jobj->mtx[1][3]);

            jobj = *jobj_slot;
            HSD_JObjAddTranslationZ(jobj, pp->pos.z - jobj->mtx[2][3]);
        }
    }

    /* Callback */
    if (pp->callback != NULL) {
        int result = pp->callback(pp);
        if (result == -1) {
            goto do_life;
        }
    }

    return pp->next;
#undef fbytes
#undef fval
}

void hsd_8039CEAC(u32 mask)
{
    void* cur;
    void* prev;
    s32 i;
    u32 bits;
    void* next;

    bits = mask;
    for (i = 0; i < 16; i++) {
        if (!(bits & 0x10000)) {
            cur = hsd_804D0908[i];
            prev = NULL;
            while (cur != NULL) {
                next = hsd_8039930C(cur, prev);
                if (prev == NULL) {
                    if (hsd_804D0908[i] != next) {
                        prev = cur;
                    }
                } else {
                    if (next != *(void**) prev) {
                        prev = cur;
                    }
                }
                cur = next;
            }
        }
        bits >>= 1;
    }
}

void hsd_8039CF4C(s32 index, HSD_JObj* jobj)
{
    if (index < 0 || index > 8) {
        return;
    }

    if (index != 0) {
        HSD_JObj** p = hsd_804D08E8;
        HSD_JObj* old;
        p += index;
        old = *--p;
        if (old != jobj) {
            if (old != NULL) {
                HSD_JObjUnref(jobj);
            }
            *p = jobj;
            ref_INC(jobj);
        }
    } else {
        s32 i;
        for (i = 0; i < 8; i++) {
            if (hsd_804D08E8[i] == jobj) {
                HSD_JObjUnref(hsd_804D08E8[i]);
                hsd_804D08E8[i] = NULL;
            }
        }
    }
}

void hsd_8039D048(void* particle)
{
    u32 flags = ((HSD_Particle*) particle)->kind;
    if (flags & 0x8000) {
        HSD_JObj** p = &hsd_804D08E8[(flags >> 12) & 7];
        if (*p != NULL) {
            HSD_JObjUnref(*p);
            *p = NULL;
        }
    }
}

void hsd_8039D0A0(HSD_Generator* gen)
{
    typedef struct {
        HSD_JObj* jobj[8];
        HSD_Particle* particle[146];
        u8 pad[0x410];
        HSD_ObjAllocData alloc_data;
    } ParticleData;
    ParticleData* data = (ParticleData*) hsd_804D08E8;
    HSD_Particle* prev;
    HSD_Particle* prt;
    HSD_Particle* next;
    HSD_Particle** head;
    u16 idnum;

    prev = NULL;
    idnum = gen->idnum;
    head = &data->particle[gen->linkNo];
    prt = *head;

    while (prt != NULL) {
        next = prt->next;
        if (prt->idnum == idnum && prt->gen != NULL && prt->gen == gen) {
            if (prt->gen != NULL && prt->gen->userfunc != NULL &&
                prt->gen->userfunc->hookDelete != NULL)
            {
                prt->gen->userfunc->hookDelete(prt);
            }

            if (prev == NULL) {
                *head = prt->next;
            } else {
                prev->next = prt->next;
            }

            if (prt->gen != NULL) {
                prt->gen->numChild--;
            }

            if (prt->appsrt != NULL) {
                psRemoveParticleAppSRT(prt);
            }

            if (prt->kind & 0x8000) {
                s32 jidx = (prt->kind >> 12) & 7;
                if (data->jobj[jidx] != NULL) {
                    HSD_JObjUnref(data->jobj[jidx]);
                    data->jobj[jidx] = NULL;
                }
            }

            HSD_ObjFree(&data->alloc_data, prt);
            hsd_804D78E2[0]--;
        } else {
            prev = prt;
        }
        prt = next;
    }
}
