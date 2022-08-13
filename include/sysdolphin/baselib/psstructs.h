#ifndef SYSDOLPHIN_BASELIB_PSSTRUCTS_H
#define SYSDOLPHIN_BASELIB_PSSTRUCTS_H

#include <dolphin/types.h>
#include <dolphin/mtx/mtxtypes.h>
#include <sysdolphin/baselib/jobj.h>

typedef unk_t HSD_PSAppSRT;
typedef unk_t GXPosNrmMtx;

struct _HSD_JObj;

struct _generator;

struct _psAppSRT;

enum HSD_ParticleKind
{
    Tornado = 1 << 2,
    TexEdge = 1 << 3,
    ComTLUT = 1 << 4,
    MirrorS = 1 << 5,
    MirrorT = 1 << 6,
    PrimEnv = 1 << 7,
    TexInterpNear = 1 << 9,
    DispTexture = 1 << 10,
    TexFlipS = 1 << 18,
    TexFlipT = 1 << 19,
    Trail = 1 << 20,
    DirVec = 1 << 21,
    DispFog = 1 << 24,
    NoZComp = 1 << 28,
    DispPoint = 1 << 30,
    DispLighting = 1 << 31
};

/* size: 0x1C */
typedef struct _HSD_PSTexGroup
{
    u32 num; /* 0x0 */

    u32 fmt;     /* 0x4 */
    u32 tlutfmt; /* 0x8 */

    u32 width;  /* 0xC */
    u32 height; /* 0x10 */

    u16 palnum;  /* 0x14 */
    u16 palflag; /* 0x16 */

    u8 *texTable[1]; /* 0x18 */
} HSD_PSTexGroup;

/* size: 0x8 */
typedef struct _HSD_PSFormGroup
{
    u32 num;          /* 0x0 */
    u8 *formTable[1]; /* 0x4 */
} HSD_PSFormGroup;

/* size: 0x40 */
typedef struct _HSD_PSCmdList
{
    u16 type;     /* 0x0 */
    u16 texGroup; /* 0x2 */

    u16 genLife; /* 0x4 */
    u16 life;    /* 0x6 */

    u32 kind; /* 0x8 */

    float grav; /* 0xC */
    float fric; /* 0x10 */

    float vx; /* 0x14 */
    float vy; /* 0x18 */
    float vz; /* 0x1C */

    float radius; /* 0x20 */
    float angle;  /* 0x24 */
    float random; /* 0x28 */
    float size;   /* 0x2C */

    float param1; /* 0x30 */
    float param2; /* 0x34 */
    float param3; /* 0x38 */

    u8 cmdList[1]; /* 0x3C */
} HSD_PSCmdList;

struct _particle;
typedef struct _particle HSD_Particle;

/* size: 0x9C */
struct _particle
{
    HSD_Particle *next; /* 0x0 */

    u32 kind; /* 0x4 */

    u8 bank;     /* 0x8 */
    u8 texGroup; /* 0x9 */

    u8 poseNum; /* 0xA */
    u8 palNum;  /* 0xB */

    u16 sizeCount; /* 0xC */

    u16 primColCount; /* 0xE */
    u16 envColCount;  /* 0x10 */
    GXColor primCol;  /* 0x12 */
    GXColor envCol;   /* 0x16 */

    u16 cmdWait; /* 0x1A */

    u8 loopCount; /* 0x1C */

    u8 linkNo; /* 0x1D */

    u16 idnum; /* 0x1E */

    u8 *cmdList;    /* 0x20 */
    u16 cmdPtr;     /* 0x24 */
    u16 cmdMarkPtr; /* 0x26 */
    u16 cmdLoopPtr; /* 0x28 */

    u16 life; /* 0x2A */

    float vx; /* 0x2C */
    float vy; /* 0x30 */
    float vz; /* 0x34 */

    float grav; /* 0x38 */
    float fric; /* 0x3C */

    float x; /* 0x40 */
    float y; /* 0x44 */
    float z; /* 0x48 */

    float size;   /* 0x4C */
    float rotate; /* 0x50 */

    u16 aCmpCount; /* 0x54 */
    u8 aCmpMode;   /* 0x56 */
    u8 aCmpParam1; /* 0x57 */
    u8 aCmpParam2; /* 0x58 */

    u8 pJObjOfs; /* 0x59 */

    u16 matColCount; /* 0x5A */
    u16 ambColCount; /* 0x5C */
    u16 rotateCount; /* 0x5E */

    float sizeTarget;   /* 0x60 */
    float rotateTarget; /* 0x64 */
    float rotateAcc;    /* 0x68 */

    u16 primColRemain;     /* 0x6C */
    u16 envColRemain;      /* 0x6E */
    GXColor primColTarget; /* 0x70 */
    GXColor envColTarget;  /* 0x74 */

    u16 matColRemain; /* 0x78 */

    u16 ambColRemain;    /* 0x7A */
    u16 aCmpRemain;      /* 0x7C */
    u8 aCmpParam1Target; /* 0x7E */
    u8 aCmpParam2Target; /* 0x7F */

    u8 matRGB; /* 0x80 */
    u8 matA;   /* 0x81 */

    u8 ambRGB; /* 0x82 */
    u8 ambA;   /* 0x83 */

    u8 matRGBTarget; /* 0x84 */
    u8 matATarget;   /* 0x85 */

    u8 ambRGBTarget; /* 0x86 */
    u8 ambATarget;   /* 0x87 */

    float trail; /* 0x88 */

    struct _generator *gen;              /* 0x8C */
    struct _psAppSRT *appsrt;            /* 0x90 */
    float *userdata;                     /* 0x94 */
    int (*callback)(HSD_Particle *part); /* 0x98 */
};

struct _psAppSRT
{
    HSD_PSAppSRT *next; /* 0x0 */

    struct _generator *gp; /* 0x4 */

    Vec tra;        /* 0x8 */
    Quaternion rot; /* 0x14 */
    Vec sca;        /* 0x24 */

    u8 status; /* 0x30 */

    u8 frameNum;   /* 0x31 */
    u16 usedCount; /* 0x32 */

    Mtx mmtx;  /* 0x34 */
    float ssx; /* 0x64 */
    float ssy; /* 0x68 */

    void (*freefunc)(HSD_PSAppSRT *appSrt); /* 0x6C */

    u16 idnum;    /* 0x70 */
    u8 billboard; /* 0x72 */
    u8 dummy;     /* 0x73 */
};

/* size: 0xC */
typedef struct _PSUserFunc
{
    int (*hookCreate)(HSD_Particle *part);                               /* 0x0 */
    int (*hookDelete)(HSD_Particle *part);                               /* 0x4 */
    int (*setUserData)(HSD_Particle *part, u8 unknown1, float unknown2); /* 0x8 */
} HSD_PSUserFunc;

extern u32 *ptclref[64];

extern int psNumTexGroup[64];
extern HSD_PSTexGroup **psTexGroupArray[64];

extern HSD_PSFormGroup **psFormGroupArray[64];

extern int psNumCmdList[64];
extern HSD_PSCmdList **psCmdListArray[64];

extern u16 numActiveParticles;
extern u16 numPeakParticles;

extern int (**psCallback)(HSD_Particle *part);

#define PS_TEXDIRECTION
#ifdef PS_TEXDIRECTION
extern int texc[4][4];
extern int td;
#endif

#ifndef _NFUNCPROTO
void psSetFog(struct _HSD_Fog *fog);

void psRemoveFog(void);
#endif

inline void setBlendMode(int blendmode);

inline void setupChanCtrl(struct _particle *pp);
inline void setupChanReg(struct _particle *pp);
inline void getClrTrail(struct _particle *pp, GXColor *col);
inline void setupTevReg(struct _particle *pp);
inline void psSetCurrentMtx(GXPosNrmMtx idx);
inline struct _particle *psDispSubPoint(struct _particle *pp);
inline struct _particle *psDispSubPointTrail(struct _particle *pp);
inline void psDispSubMakePolygon(
    struct _particle *pp,
    u8 *texform,
    float x, float y, float z,
    float ppvx, float ppvy, float ppvz,
    float x0, float y0, float z0,
    float x1, float y1, float z1);

inline void psDispSub(struct _particle *pp, u8 *texform);

#define PS_APPSRT
#ifdef PS_APPSRT
inline void psDispSubAppSRT(struct _particle *pp, u8 *texform);
inline void psDispSubAPPSRTPoint(struct _particle *pp);
#endif

void psDispParticles(u32 target_link, u32 sw);

void psInitDataBankLoad(
    int bank,
    int *cmdBank,
    int *texBank,
    u32 *ref,
    int *formBank);

void psInitDataBankLocate(int *cmdBank, int *texBank, int *formBank);

void psInitDataBankRelocate(
    int *cmdBank,
    int *texBank,
    int *formBank,
    int *newCmdBank,
    int *newTexBank,
    int *newFormBank);

void psInitDataBank(
    int bank,
    int *cmdBank,
    int *texBank,
    u32 *ref,
    int *formBank);

void psInitParticle(int num);

void psRemoveParticle(void);

HSD_Particle *psGenerateParticle0(
    HSD_Particle *p,
    int linkNo,
    int bank,
    u32 kind,
    u16 texGroup,
    u8 *list,
    int life,
    float x, float y, float z,
    float vx, float vy, float vz,
    float size,
    float grav,
    float fric,
    int palflag,
    struct _generator *gp,
    int flgInterpret);

HSD_Particle *psGenerateParticleID0(
    HSD_Particle *p,
    int linkNo,
    int bank,
    int id,
    int flgInterpret);

HSD_Particle *psGenerateParticle(
    int linkNo,
    int bank,
    u32 kind,
    u16 texGroup,
    u8 *list,
    int life,
    float x, float y, float z,
    float vx, float vy, float vz,
    float size,
    float grav,
    float fric,
    int palflag,
    struct _generator *gp);

HSD_Particle *psGenerateParticleIDPV(
    int linkNo,
    int bank,
    int id,
    float px, float py, float pz,
    float vx, float vy, float vz);

HSD_Particle *psGenerateParticleID(int linkNo, int bank, int id);
HSD_Particle *psGenerateParticleIDN(int linkNo, int bank, int id);

void psKillParticle(HSD_Particle *pp);
void psKillAllParticle(void);

void psSetPointJObj(int no, struct _HSD_JObj *jobj);
void psSetPointJObjNodup(struct _HSD_JObj *jobj, int no);

void psClearPointJObj(void);

void psDeletePntJObjwithParticle(HSD_Particle *pp);

void psKillFamily(u16 idnum, int linkNo);
void psKillGeneratorChild(struct _generator *gp);

void psAddOffsetAll(float xofs, float yofs, float zofs);

void psPauseFamily(u16 idnum, int linkNo);
void psRestartFamily(u16 idnum, int linkNo);

void psSetCallback(int (**callback)(HSD_Particle *part));

void psSetUserFunc(struct _generator *gp, HSD_PSUserFunc *userfunc);

inline void psRemoveBillboardCamera(void);

#endif