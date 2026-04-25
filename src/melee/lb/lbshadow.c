#include "lbshadow.h"

#include <MSL/math_ppc.h>
#include <dolphin/gx/GXVert.h>
#include <sysdolphin/baselib/debug.h>
#include <sysdolphin/baselib/gobj.h>
#include <sysdolphin/baselib/initialize.h>
#include <sysdolphin/baselib/lobj.h>
#include <sysdolphin/baselib/perf.h>
#include <sysdolphin/baselib/pobj.h>
#include <sysdolphin/baselib/shadow.h>
#include <sysdolphin/baselib/spline.h>
#include <sysdolphin/baselib/state.h>
#include <sysdolphin/baselib/tev.h>
#include <sysdolphin/baselib/util.h>
#include <sysdolphin/baselib/video.h>
#include <melee/cm/types.h>
#include <melee/ft/ftdrawcommon.h>
#include <melee/ft/ftlib.h>
#include <melee/ft/types.h>
#include <melee/gr/ground.h>
#include <melee/lb/lbvector.h>
#include <melee/lb/types.h>

void lbShadow_8000E9F0(Vec3* p, HSD_Spline* spline, f32 u)
{
    Vec3* cp;
    s16 idx;
    f32 t;

    PAD_STACK(16);

    if (u < 0.0F || u > 1.0F) {
        return;
    }

    t = u * (spline->numcv - 1);
    idx = (s16) t;
    t = t - (f32) idx;

    switch (spline->type) {
    case 0:
        if (u == 1.0F) {
            idx -= 1;
        }
        cp = &spline->cv[idx];
        p->x = cp[1].x - cp[0].x;
        p->y = cp[1].y - cp[0].y;
        p->z = cp[1].z - cp[0].z;
        return;
    case 1: {
        f32 t2, u_1, bez1, bez0, bez2;
        cp = &spline->cv[idx * 3];
        bez1 = -((4.0F * t) - 1.0F);
        t2 = 3.0F * (t * t);
        u_1 = t - 1.0F;
        bez1 = 3.0F * (bez1 + t2);
        bez0 = -3.0F * u_1 * u_1;
        bez2 = 3.0F * ((2.0F * t) - t2);
        p->x = (cp[3].x * t2) + ((cp[2].x * bez2) + ((cp[0].x * bez0) + (cp[1].x * bez1)));
        p->y = (cp[3].y * t2) + ((cp[2].y * bez2) + ((cp[0].y * bez0) + (cp[1].y * bez1)));
        p->z = (cp[3].z * t2) + ((cp[2].z * bez2) + ((cp[0].z * bez0) + (cp[1].z * bez1)));
        return;
    }
    case 2: {
        f32 u2, u_1, half, b1, b0, b2, b3;
        cp = &spline->cv[idx];
        u2 = t * t;
        u_1 = 1.0F - t;
        half = 0.5F;
        b1 = half * ((3.0F * u2) - (4.0F * t));
        b0 = u_1 * (-half * u_1);
        b2 = half * (1.0F + ((-3.0F * u2) + (2.0F * t)));
        b3 = half * u2;
        p->x = (cp[3].x * b3) + ((cp[2].x * b2) + ((cp[0].x * b0) + (cp[1].x * b1)));
        p->y = (cp[3].y * b3) + ((cp[2].y * b2) + ((cp[0].y * b0) + (cp[1].y * b1)));
        p->z = (cp[3].z * b3) + ((cp[2].z * b2) + ((cp[0].z * b0) + (cp[1].z * b1)));
        return;
    }
    case 3: {
        f32 tension = spline->tension;
        f32 u2 = t * t;
        f32 car1, car0, car3, car2;
        cp = &spline->cv[idx];
        car1 = (3.0F * (2.0F - tension) * u2) + (2.0F * (tension - 3.0F) * t);
        car0 = tension * (((-3.0F * u2) + (4.0F * t)) - 1.0F);
        car3 = tension * ((3.0F * u2) - (2.0F * t));
        car2 = tension + ((3.0F * (tension - 2.0F) * u2) + (2.0F * -((2.0F * tension) - 3.0F) * t));
        p->x = (cp[3].x * car3) + ((cp[2].x * car2) + ((cp[0].x * car0) + (cp[1].x * car1)));
        p->y = (cp[3].y * car3) + ((cp[2].y * car2) + ((cp[0].y * car0) + (cp[1].y * car1)));
        p->z = (cp[3].z * car3) + ((cp[2].z * car2) + ((cp[0].z * car0) + (cp[1].z * car1)));
        break;
    }
    }
}

void lbShadow_8000ED54(LbShadow* lbshadow, HSD_JObj* jobj)
{
    HSD_Shadow* shadow;

    if (lbshadow == NULL) {
        __assert("lbshadow.c", 0x36, "lbshadow");
    }
    shadow = HSD_ShadowAlloc();
    if (shadow != NULL) {
        HSD_CObjSetProjectionType(shadow->camera, PROJ_ORTHO);
        HSD_CObjSetNear(shadow->camera, 0.001F);
        HSD_CObjSetFar(shadow->camera, 5000.0F);
        HSD_CObjSetFlags(shadow->camera, 1);
        HSD_ShadowSetSize(shadow, 0x100, 0x100);
        if (shadow == NULL) {
            __assert("shadow.h", 0x63, "shadow");
        }
        shadow->intensity = 0xC0;
        shadow->scaleS = +0.45F;
        shadow->scaleT = -0.45F;
        HSD_ShadowAddObject(shadow, jobj);
        HSD_ShadowSetActive(shadow, true);
    }
    lbshadow->x0_b0 = false;
    lbshadow->x0_b1 = false;
    lbshadow->x0_b3 = false;
    lbshadow->x0_b4 = false;
    lbshadow->x0_b5 = false;
    lbshadow->shadow = shadow;
}

void lbShadow_8000EE8C(LbShadow* lbshadow)
{
    if (lbshadow == NULL) {
        __assert("lbshadow.c", 0x62U, "lbshadow");
    }
    if (lbshadow->shadow != NULL) {
        HSD_ShadowRemove(lbshadow->shadow);
    }
}

void lbShadow_8000EEE0(HSD_GObj* gobj)
{
    LbShadow* lbshadow;

    if (ftLib_80086960(gobj)) {
        lbshadow = ftLib_800872B0(gobj);
        if (lbshadow != NULL) {
            bool var_r4 = lbshadow->x0_b0 || lbshadow->x0_b1 ||
                          lbshadow->x0_b2 || lbshadow->x0_b3 ||
                          lbshadow->x0_b4 || lbshadow->x0_b5;
            if (!var_r4 && ftLib_800872BC(gobj)) {
                HSD_ShadowSetActive(lbshadow->shadow, 1);
            } else {
                HSD_ShadowSetActive(lbshadow->shadow, 0);
            }
        }
    }
}

void lbShadow_8000EFEC(void)
{
    int count;
    HSD_GObj* var_r30;
    HSD_GObj* cur;
    LbShadow* lbshadow;

    PAD_STACK(0x18);

    count = 0;

    for (var_r30 = HSD_GObj_Entities->fighters; var_r30 != NULL;
         var_r30 = var_r30->next)
    {
        lbshadow = ftLib_800872B0(var_r30);
        if (lbshadow != NULL) {
            lbshadow->x0_b2 = false;
        }
    }

    for (cur = HSD_GObj_Entities->fighters; cur != NULL; cur = cur->next) {
        lbshadow = ftLib_800872B0(cur);
        if (lbshadow != NULL) {
            bool var_r5 = lbshadow->x0_b0 || lbshadow->x0_b1 ||
                          lbshadow->x0_b2 || lbshadow->x0_b3 ||
                          lbshadow->x0_b4 || lbshadow->x0_b5;

            if (!var_r5) {
                count++;
                if (count > 5) {
                    lbshadow->x0_b2 = true;
                }
            }

            lbShadow_8000EEE0(cur);
        }
    }
}

static HSD_Chan lbShadow_803BA0FC = {
    NULL,
    GX_COLOR0A0,
    0,
    {
        0,
        0,
        0,
        0,
    },
    {
        0,
        0,
        0,
        0xFF,
    },
    0,
    GX_SRC_REG,
    GX_SRC_REG,
    GX_LIGHT_NULL,
    GX_DF_CLAMP,
    GX_AF_NONE,
    NULL,
};

void lbShadow_8000F214(HSD_Shadow* shadow)
{
    HSD_ImageDesc* imagedesc;
    f32 y0;
    f32 y1;
    f32 x0;
    f32 x1;
    f32 z;

    const int num_edges = 4;

    HSD_CObj* cobj = shadow->camera;
    HSD_SetupChannelAll(&lbShadow_803BA0FC);
    imagedesc = shadow->texture->imagedesc;
    GXSetScissor(0, 0, imagedesc->width, imagedesc->height);
    GXLoadPosMtxImm(HSD_identityMtx, GX_PNMTX0);
    HSD_PerfCurrentStat.nb_mtx_load++;
    GXSetCurrentMtx(GX_PNMTX0);
    HSD_ClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_TEX_ST, GX_RGBA6, 0);
    HSD_StateSetCullMode(GX_CULL_BACK);

    y0 = HSD_CObjGetTop(cobj);
    y1 = HSD_CObjGetBottom(cobj);
    x0 = HSD_CObjGetLeft(cobj);
    x1 = HSD_CObjGetRight(cobj);
    z = HSD_CObjGetNear(cobj);

    y0 *= 1.2F;
    y1 *= 1.2F;
    x0 *= 1.2F;
    x1 *= 1.2F;
    z *= -1.1F;

    GXBegin(GX_QUADS, GX_VTXFMT0, num_edges);

    GXWGFifo.f32 = x0;
    GXWGFifo.f32 = y0;
    GXWGFifo.f32 = z;

    GXWGFifo.f32 = x1;
    GXWGFifo.f32 = y0;
    GXWGFifo.f32 = z;

    GXWGFifo.f32 = x1;
    GXWGFifo.f32 = y1;
    GXWGFifo.f32 = z;

    GXWGFifo.f32 = x0;
    GXWGFifo.f32 = y1;
    GXWGFifo.f32 = z;

    GXEnd();
}

void lbShadow_8000F38C(s32 arg0)
{
    HSD_ViewingRect rect;
    Vec3 lightPos;
    Vec3 lightDir;
    Vec3 upVec;
    Vec3 lightVec;
    Vec3 rightVec;
    Vec3 normDir;
    Vec3 eyePos;
    Vec3 interestPos;
    Vec3 camPos;
    f32 dist;
    s32 noLight;
    HSD_GObj* gobj;
    HSD_LObj* lobj;
    HSD_LObj* fallback;

    PAD_STACK(0x48);

    noLight = 0;

    for (gobj = HSD_GObj_Entities->fighters; gobj != NULL;
         gobj = gobj->next)
    {
        LbShadow* lbs = ftLib_800872B0(gobj);
        if (lbs != NULL) {
            lbs->x0_b2 = false;
        }
    }

    lobj = NULL;
    fallback = lobj;
    {
        HSD_GObj* lgobj;
        for (lgobj = HSD_GObjGXLinkHead[4]; lgobj != NULL;) {
            HSD_GObj* nextGx = lgobj->next_gx;
            lobj = (HSD_LObj*) lgobj->hsd_obj;
            while (lobj != NULL) {
                if (lobj->flags & 3) {
                    fallback = lobj;
                }
                if (HSD_LObjGetFlags(lobj) & 0x400) {
                    nextGx = NULL;
                    break;
                }
                if (lobj == NULL) {
                    lobj = NULL;
                } else {
                    lobj = lobj->next;
                }
            }
            lgobj = nextGx;
        }
    }

    if (lobj == NULL && fallback != NULL) {
        lobj = fallback;
    }
    HSD_ASSERT(0x181, lobj);

    if (!HSD_LObjGetPosition(lobj, &lightPos)) {
        HSD_ASSERTREPORT(0x184, NULL, "couldn't get light position");
    }

    if (HSD_LObjGetInterest(lobj, &lightDir)) {
        lbVector_Sub(&lightPos, &lightDir);
        lightDir.z = 0.0f;
        lightDir.y = 0.0f;
        lightDir.x = 0.0f;
    } else {
        lightDir.z = 0.0f;
        lightDir.y = 0.0f;
        lightDir.x = 0.0f;
    }

    lbVector_Diff(&lightPos, &lightDir, &lightVec);

    dist = lightVec.x * lightVec.x;
    dist = (lightVec.z * lightVec.z) + (dist + (lightVec.y * lightVec.y));
    if (dist > 0.0f) {
        dist = sqrtf(dist);
    }

    if (dist < 0.001f) {
        noLight = 1;
        lightPos.x = 0.0f;
        lightDir.x = 0.0f;
        upVec.x = 0.0f;
        lightPos.y = 0.0f;
        lightDir.y = 0.0f;
        upVec.y = 1.0f;
        lightPos.z = 1.0f;
        lightDir.z = 0.0f;
        upVec.z = 0.0f;
    } else {
        f32 xz_sq =
            (lightVec.x * lightVec.x) + (lightVec.z * lightVec.z);
        if (xz_sq > 0.0000010000001f) {
            upVec.z = 0.0f;
            upVec.y = 1.0f;
            upVec.x = 0.0f;
            lbVector_Diff(&lightDir, &lightPos, &normDir);
            if (lbVector_Normalize(&normDir) < 100.0f) {
                lightPos.x = -((100.0f * normDir.x) - lightDir.x);
                lightPos.y = -((100.0f * normDir.y) - lightDir.y);
                lightPos.z = -((100.0f * normDir.z) - lightDir.z);
            }
            lbVector_CrossprodNormalized(&upVec, &normDir, &rightVec);
            lbVector_CrossprodNormalized(&normDir, &rightVec, &upVec);
        } else {
            upVec.y = 0.0f;
            upVec.x = 0.0f;
            upVec.z = -1.0f;
        }
    }

    ftDrawCommon_80081200();

    for (gobj = HSD_GObj_Entities->fighters; gobj != NULL;
         gobj = gobj->next)
    {
        Fighter* fp = gobj->user_data;
        CmSubject* cm = fp->x890_cameraBox;

        if (noLight) {
            fp->x20A4.x0_b0 = true;
        } else {
            fp->x20A4.x0_b0 = false;
        }

        {
            Fighter* fp2 = gobj->user_data;
            if (fp2->x20A4.shadow != NULL) {
                s32 hasObj = 0;
                HSD_ShadowDeleteObject(fp2->x20A4.shadow, NULL);

                if (fp2->x21FC_flag.b7) {
                    if (!fp2->invisible && !fp2->x221E_b5 &&
                        fp2->x5AC.xC[1] != NULL)
                    {
                        HSD_ShadowAddObject(fp2->x20A4.shadow,
                                            (HSD_JObj*) gobj->hsd_obj);
                        hasObj = 1;
                    }
                    if (fp2->x20A0_accessory != NULL) {
                        HSD_ShadowAddObject(fp2->x20A4.shadow,
                                            fp2->x20A0_accessory);
                        hasObj = 1;
                    }
                }

                if (hasObj) {
                    fp2->x20A4.x0_b3 = false;
                } else {
                    fp2->x20A4.x0_b3 = true;
                }
            }
        }

        if (ftLib_80086960(gobj)) {
            LbShadow* lbs = ftLib_800872B0(gobj);
            if (lbs != NULL) {
                bool anyFlag = lbs->x0_b0 || lbs->x0_b1 ||
                               lbs->x0_b2 || lbs->x0_b3 ||
                               lbs->x0_b4 || lbs->x0_b5;
                if (!anyFlag && ftLib_800872BC(gobj)) {
                    HSD_ShadowSetActive(lbs->shadow, 1);
                } else {
                    HSD_ShadowSetActive(lbs->shadow, 0);
                }
            }
        }

        if (fp->x20A4.shadow != NULL && cm != NULL &&
            !fp->x20A4.x0_b3)
        {
            u8 intensity = Ground_801C0508();
            HSD_Shadow* shadow2 = fp->x20A4.shadow;

            if (shadow2 == NULL) {
                __assert("shadow.h", 0x63, "shadow");
            }
            shadow2->intensity = intensity;

            PSVECAdd(&cm->x1C, &lightPos, &eyePos);
            PSVECAdd(&cm->x1C, &lightDir, &interestPos);
            HSD_CObjSetEyePosition(fp->x20A4.shadow->camera, &eyePos);
            HSD_CObjSetInterest(fp->x20A4.shadow->camera, &interestPos);
            HSD_CObjSetUpVector(fp->x20A4.shadow->camera, &upVec);

            if (cm != NULL) {
                camPos = cm->x1C;
                HSD_ViewingRectInit(&rect, &eyePos, &interestPos,
                                    &upVec, 0);

                {
                    s32 i = 0;
                    do {
                        f32 scale = cm->x48.z;
                        f32 top = 1.2f * scale;
                        f32 bot = 1.2f * -scale;
                        HSD_ViewingRectAddRect(&rect, &camPos, top,
                                               bot, bot, top);
                        if (HSD_ViewingRectCheck(&rect) != 0) {
                            break;
                        }
                        i++;
                    } while (i < 0x14);

                    if (i < 0x14) {
                        HSD_ShadowSetViewingRect(fp->x20A4.shadow,
                                                 rect.top, rect.bottom,
                                                 rect.left, rect.right);
                    } else {
                        HSD_CObjSetOrtho(fp->x20A4.shadow->camera,
                                         128.0f, -128.0f, -128.0f,
                                         128.0f);
                    }
                }
            }

            HSD_ShadowInit(fp->x20A4.shadow);
            HSD_StartRender(HSD_RP_OFFSCREEN);
            HSD_GObj_804D7814 = gobj;
            HSD_ShadowStartRender(fp->x20A4.shadow);
            if (arg0 != 0) {
                lbShadow_8000F214(fp->x20A4.shadow);
            }
            HSD_ShadowEndRender(fp->x20A4.shadow);
            HSD_Init_803755A8();
        }
    }

    ftDrawCommon_80081168();
}
