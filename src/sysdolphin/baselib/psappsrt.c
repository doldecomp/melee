#include "psappsrt.h"

#include "objalloc.h"
#include "psstructs.h"

#include <string.h>

/* 004D4538 */ extern u16 HSD_PSAppSrt_804D7958[4];
/* 004CDC90 */ extern HSD_ObjAllocData HSD_PSAppSrt_804D10B0;
extern u16 hsd_804D78DE;
extern u16 hsd_804D78D8;

bool psInitAppSRT(int num, int size)
{
    hsd_804D78DE = 0;
    hsd_804D78D8 = 0;
    HSD_PSAppSrt_804D7958[0] = (u16) size;
    HSD_ObjAllocInit(&HSD_PSAppSrt_804D10B0, size, 4U);
    return 0;
}

HSD_psAppSRT* psAddGeneratorAppSRT(s32 status, u16 idnum)
{
    HSD_psAppSRT* srt;

    srt = HSD_ObjAlloc(&HSD_PSAppSrt_804D10B0);
    if (srt != NULL) {
        memset(srt, 0, HSD_PSAppSrt_804D7958[0]);
    }
    if (srt != NULL) {
        srt->next = NULL;
        srt->usedCount = 1;
        srt->frameNum = 0;
        srt->status = status;
        srt->translate.z = 0.0F;
        srt->translate.y = 0.0F;
        srt->translate.x = 0.0F;
        srt->rot.z = 0.0F;
        srt->rot.y = 0.0F;
        srt->rot.x = 0.0F;
        srt->scale.z = 1.0F;
        srt->scale.y = 1.0F;
        srt->scale.x = 1.0F;
        srt->freefunc = NULL;
        srt->xA2 = 0;
        srt->gp = NULL;
        srt->idnum = idnum;
        hsd_804D78DE += 1;
        if ((u16) hsd_804D78DE > (u16) hsd_804D78D8) {
            hsd_804D78D8 = hsd_804D78DE;
        }
    }
    return srt;
}

void HSD_PSAppSrt_803A425C(HSD_Particle* pp, s32 status)
{
    pp->appsrt = psAddGeneratorAppSRT(status, pp->idnum);
}

HSD_psAppSRT* psAddGeneratorAppSRT_begin(HSD_Generator* gp, s32 status)
{
    return gp->appsrt = psAddGeneratorAppSRT(status, gp->idnum);
}

int psAttachParticleAppSRT(HSD_Particle* pp, HSD_psAppSRT* srt)
{
    if (srt == NULL || pp == NULL || pp->appsrt != NULL) {
        return -1;
    }
    pp->appsrt = srt;
    return (u16) ++srt->usedCount;
}

int psAttachGeneratorAppSRT(HSD_Generator* gp, HSD_psAppSRT* srt)
{
    if (srt == NULL || gp == NULL || gp->appsrt != NULL) {
        return -1;
    }
    gp->appsrt = srt;
    return (u16) ++srt->usedCount;
}

int psRemoveParticleAppSRT(HSD_Particle* pp)
{
    HSD_psAppSRT* srt;
    int count;

    srt = pp->appsrt;
    if (srt == NULL) {
        return -1;
    }
    count = --srt->usedCount;
    if (count == 0) {
        srt = pp->appsrt;
        if (srt->freefunc != NULL) {
            srt->freefunc(srt);
        }
        HSD_ObjFree(&HSD_PSAppSrt_804D10B0, srt);
        hsd_804D78DE--;
    }
    pp->appsrt = NULL;
    return count;
}

int psRemoveGeneratorSRT(HSD_Generator* gp)
{
    HSD_psAppSRT* srt;
    int count;

    srt = gp->appsrt;
    if (srt == NULL) {
        return -1;
    }
    {
        HSD_Generator** gpp = &srt->gp;
        if (*gpp == gp) {
            *gpp = NULL;
        }
    }
    srt = gp->appsrt;
    count = --srt->usedCount;
    if (count == 0) {
        srt = gp->appsrt;
        if (srt->freefunc != NULL) {
            srt->freefunc(srt);
        }
        HSD_ObjFree(&HSD_PSAppSrt_804D10B0, srt);
        hsd_804D78DE--;
    }
    gp->appsrt = NULL;
    return count;
}
