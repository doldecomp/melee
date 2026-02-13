#ifndef SYSDOLPHIN_BASELIB_PSSTRUCTS_H
#define SYSDOLPHIN_BASELIB_PSSTRUCTS_H

#include <platform.h>

#include "baselib/archive.h"

#include "baselib/forward.h" // IWYU pragma: export

#include "baselib/jobj.h"

#include <dolphin/gx.h>
#include <dolphin/gx/GXEnum.h>
#include <dolphin/mtx.h>

struct HSD_Fog;

enum HSD_ParticleKind {
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
typedef struct _HSD_PSTexGroup {
    u32 num; /* 0x0 */

    u32 fmt;     /* 0x4 */
    u32 tlutfmt; /* 0x8 */

    u32 width;  /* 0xC */
    u32 height; /* 0x10 */

    u16 palnum;  /* 0x14 */
    u16 palflag; /* 0x16 */

    u8* texTable[1]; /* 0x18 */
} HSD_PSTexGroup;

/* size: 0x8 */
typedef struct _HSD_PSFormGroup {
    u32 num;          /* 0x0 */
    u8* formTable[1]; /* 0x4 */
} HSD_PSFormGroup;

/* size: 0x40 */
typedef struct _HSD_PSCmdList {
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

struct HSD_psAppSRT {
    struct HSD_psAppSRT* next; /* 0x0 */

    struct HSD_Generator* gp; /* 0x4 */

    Vec3 translate; /* 0x8 */
    Quaternion rot; /* 0x14 */
    Vec3 scale;     /* 0x24 */

    u8 status; /* 0x30 */

    u8 frameNum;   /* 0x31 */
    u16 usedCount; /* 0x32 */

    Mtx mmtx;  /* 0x34 */
    float ssx; /* 0x64 */
    float ssy; /* 0x68 */

    u8 x6C_fill[0x9C - 0x6C]; /* 0x6C */

    void (*freefunc)(struct HSD_psAppSRT* appSrt); /* 0x9C */

    u16 idnum; /* 0xA0 */
    s8 xA2;    /* 0xA2 */
};

/* size: 0x98 */
struct HSD_Particle {
    HSD_Particle* next; /* 0x0 */

    u32 kind; /* 0x4 */

    u8 bank;     /* 0x8 */
    u8 texGroup; /* 0x9 */

    u8 poseNum; /* 0xA */
    u8 palNum;  /* 0xB */

    u16 sizeCount;

    u16 primColCount; /* 0xE */
    u16 envColCount;  /* 0x10 */
    GXColor primCol;  /* 0x12 */
    GXColor envCol;   /* 0x16 */

    u16 cmdWait;

    u8 loopCount;

    u8 linkNo; /* 0x1D */

    u16 idnum;

    u8* cmdList;
    u16 cmdPtr;
    u16 cmdMarkPtr;
    u16 cmdLoopPtr;

    u16 life;

    Vec3 vel; /* 0x2C */

    float grav; /* 0x38 */
    float fric; /* 0x3C */

    Vec3 pos; /* 0x40 */

    float size;   /* 0x4C */
    float rotate; /* 0x50 */

    u16 aCmpCount; /* 0x54 */
    u8 aCmpMode;   /* 0x56 */
    u8 aCmpParam1; /* 0x57 */
    u8 aCmpParam2; /* 0x58 */

    u8 pJObjOfs; /* 0x59 */

    u16 matColCount; /* 0x5A */
    u16 ambColCount; /* 0x5C */
    u16 rotateCount;

    float sizeTarget;
    float rotateTarget;

    u16 primColRemain;     /* 0x68 */
    u16 envColRemain;      /* 0x6A */
    GXColor primColTarget; /* 0x6C */
    GXColor envColTarget;  /* 0x70 */

    u16 matColRemain; /* 0x74 */
    u16 ambColRemain; /* 0x76 */

    u16 aCmpRemain;      /* 0x78 */
    u8 aCmpParam1Target; /* 0x7A */
    u8 aCmpParam2Target; /* 0x7B */

    u8 matRGB; /* 0x7C */
    u8 matA;   /* 0x7D */

    u8 ambRGB; /* 0x7E */
    u8 ambA;   /* 0x7F */

    u8 matRGBTarget; /* 0x80 */
    u8 matATarget;   /* 0x81 */
    u8 ambRGBTarget; /* 0x82 */
    u8 ambATarget;   /* 0x83 */

    float trail; /* 0x84 */

    struct HSD_Generator* gen;           /* 0x88 */
    struct HSD_psAppSRT* appsrt;         /* 0x8C */
    float* userdata;                     /* 0x90 */
    int (*callback)(HSD_Particle* part); /* 0x94 */
};

/* size: 0xC */
typedef struct _PSUserFunc {
    int (*hookCreate)(HSD_Particle* part); /* 0x0 */
    int (*hookDelete)(HSD_Particle* part); /* 0x4 */
    int (*setUserData)(HSD_Particle* part, u8 unknown1,
                       float unknown2); /* 0x8 */
} HSD_PSUserFunc;

typedef struct _auxDisc {
    f32 minAngle;
    f32 maxAngle;
} auxDisc;

typedef struct _auxLine {
    f32 x2;
    f32 y2;
    f32 z2;
} auxLine;

typedef struct _auxTornado {
    f32 vel;
} auxTornado;

typedef struct _auxRect {
    f32 x;
    f32 y;
    f32 z;
    f32 xx;
    f32 xy;
    f32 xz;
    f32 yx;
    f32 yy;
    f32 yz;
    f32 zx;
    f32 zy;
    f32 zz;
    u16 flag;
} auxRect;

typedef struct _auxCone {
    f32 minAngle;
    f32 maxAngle;
    f32 height;
} auxCone;

typedef struct _auxSphere {
    f32 speed;
    f32 latMid;
    f32 latRange;
    f32 lonMid;
    f32 lonRange;
} auxSphere;

struct HSD_Generator {
    HSD_Generator* next;                  // 0x0
    u32 kind;                             // 0x4
    f32 random;                           // 0x8
    f32 count;                            // 0xC
    HSD_JObj* jobj;                       // 0x10
    u16 genLife;                          // 0x14
    u16 type;                             // 0x16
    u8 bank;                              // 0x18
    u8 linkNo;                            // 0x19
    u8 texGroup;                          // x1A
    u8 dummy;                             // 0x1B
    u16 idnum;                            // 0x1C
    u16 life;                             // 0x1E
    u8* cmdList;                          // 0x20
    Vec3 pos;                             // 0x24
    Vec3 vel;                             // 0x30
    f32 grav;                             // 0x3C
    f32 fric;                             // 0x40
    f32 size;                             // 0x44
    f32 radius;                           // 0x48
    f32 angle;                            // 0x4C
    u32 numChild;                         // 0x50
    HSD_psAppSRT* appsrt;                 // 0x54
    HSD_PSUserFunc* userfunc;             // 0x58
    int (*callback)(HSD_Generator* part); // 0x5C
    union {
        auxDisc disc;
        auxLine line;
        auxTornado tornado;
        auxRect rect;
        auxCone cone;
        auxSphere sphere;
    } aux; // 0x60
};

extern u32* ptclref[65];

extern int psNumTexGroup[65];
extern HSD_PSTexGroup** psTexGroupArray[65];

extern HSD_PSFormGroup** psFormGroupArray[65];

extern int psNumCmdList[65];
extern HSD_PSCmdList** psCmdListArray[65];

extern u16 numActiveParticles;
extern u16 numPeakParticles;

extern int (**psCallback)(HSD_Particle* part);

#define PS_TEXDIRECTION
#ifdef PS_TEXDIRECTION
extern int texc[4][4];
extern int td;
#endif

#ifndef _NFUNCPROTO
void psSetFog(struct HSD_Fog* fog);

void psRemoveFog(void);
#endif

static inline void setBlendMode(int blendmode);

static inline void setupChanCtrl(HSD_Particle* pp);
static inline void setupChanReg(HSD_Particle* pp);
static inline void getClrTrail(HSD_Particle* pp, GXColor* col);
static inline void setupTevReg(HSD_Particle* pp);
static inline void psSetCurrentMtx(GXPosNrmMtx idx);
static inline HSD_Particle* psDispSubPoint(HSD_Particle* pp);
static inline HSD_Particle* psDispSubPointTrail(HSD_Particle* pp);
static inline void psDispSubMakePolygon(HSD_Particle* pp, u8* texform, float x,
                                        float y, float z, float ppvx,
                                        float ppvy, float ppvz, float x0,
                                        float y0, float z0, float x1, float y1,
                                        float z1);

static inline void psDispSub(HSD_Particle* pp, u8* texform);

void psInitDataBank(int bank, int* cmdBank, int* texBank, u32* ref,
                    int* formBank);

void psInitParticle(int num);

void psRemoveParticle(void);

HSD_Particle* psGenerateParticle0(HSD_Particle* p, int linkNo, int bank,
                                  u32 kind, u16 texGroup, u8* list, int life,
                                  float x, float y, float z, float vx,
                                  float vy, float vz, float size, float grav,
                                  float fric, int palflag, HSD_Generator* gp,
                                  int flgInterpret);

HSD_Particle* psGenerateParticleID0(HSD_Particle* p, int linkNo, int bank,
                                    int id, int flgInterpret);

HSD_Particle* psGenerateParticle(int linkNo, int bank, u32 kind, u16 texGroup,
                                 u8* list, int life, float x, float y, float z,
                                 float vx, float vy, float vz, float size,
                                 float grav, float fric, int palflag,
                                 HSD_Generator* gp);

HSD_Particle* psGenerateParticleIDPV(int linkNo, int bank, int id, float px,
                                     float py, float pz, float vx, float vy,
                                     float vz);

HSD_Particle* psGenerateParticleID(int linkNo, int bank, int id);
HSD_Particle* psGenerateParticleIDN(int linkNo, int bank, int id);

void psKillParticle(HSD_Particle* pp);
void psKillAllParticle(void);

void psSetPointJObj(int no, HSD_JObj* jobj);
void psSetPointJObjNodup(HSD_JObj* jobj, int no);

void psClearPointJObj(void);

void psDeletePntJObjwithParticle(HSD_Particle* pp);

void psKillFamily(u16 idnum, int linkNo);
void psKillGeneratorChild(HSD_Generator* gp);

void psAddOffsetAll(float xofs, float yofs, float zofs);

void psPauseFamily(u16 idnum, int linkNo);
void psRestartFamily(u16 idnum, int linkNo);

void psSetCallback(int (**callback)(HSD_Particle* part));

void psSetUserFunc(HSD_Generator* gp, HSD_PSUserFunc* userfunc);

static inline void psRemoveBillboardCamera(void);

#endif
