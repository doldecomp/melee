/// @file Creates trailing "afterimages" for swords in motion

#include "ftafterimage.h"

#include <placeholder.h>

#include "baselib/debug.h"

#include <dolphin/gx.h>
#include <dolphin/mtx.h>
#include <baselib/cobj.h>
#include <baselib/state.h>
#include <sysdolphin/baselib/gobj.h>
#include <melee/ft/chara/ftLink/types.h>
#include <melee/ft/chara/ftMars/types.h>
#include <melee/ft/inlines.h>
#include <melee/it/it_26B1.h>
#include <melee/it/item.h>
#include <melee/it/items/itsword.h>
#include <melee/lb/lb_00B0.h>
#include <melee/lb/lbvector.h>
#include <MSL/math_ppc.h>

typedef struct AfterimageVtx {
    f32 x, y, z;
    u8 r, g, b, a;
} AfterimageVtx;

#define AFTERIMAGE_ANGLE_STEP 0.0872664600610733f

void ftCo_800C2600(Fighter_GObj* gobj, u32 arg1)
{
    Fighter* fp;
    itSword_UnkBytes* params;
    AfterimageVtx vtx_buf[152];
    f32 cumDist[3];
    Vec3 delta, prevPos, crossProd, tempDir;
    s32 numVerts;
    s32 nextIdx;

    if (arg1 != 2) {
        return;
    }

    fp = gobj->user_data;

    if ((s8) (u8) fp->x2100 <= 1) {
        return;
    }

    GXSetColorUpdate(1);
    GXSetAlphaUpdate(0);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_NOOP);
    GXSetAlphaCompare(GX_GREATER, 0, GX_AOP_AND, GX_GREATER, 0);
    GXSetZMode(1, GX_LEQUAL, 0);
    GXSetZCompLoc(0);
    GXSetNumTexGens(0);
    GXSetTevClampMode(0, 0);
    GXSetNumTevStages(1);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
    GXSetTevOp(GX_TEVSTAGE0, GX_PASSCLR);
    GXSetNumChans(1);
    GXSetChanCtrl(GX_COLOR0A0, 0, GX_SRC_REG, GX_SRC_VTX, 0, GX_DF_NONE,
                  GX_AF_NONE);
    GXSetCullMode(GX_CULL_NONE);

    if (fp->x2101_bits_8) {
        s32 kind = itGetKind(fp->item_gobj);
        if (kind == It_Kind_Sword) {
            params = it_80285300(fp->item_gobj);
        } else {
            HSD_ASSERTREPORT(0x7C, NULL, "no afterimage item!\n");
        }
    } else {
        switch (fp->kind) {
        case FTKIND_SEAK:
        case FTKIND_NESS:
        case FTKIND_PEACH:
        case FTKIND_POPO:
        case FTKIND_NANA:
        case FTKIND_PIKACHU:
        case FTKIND_SAMUS:
        case FTKIND_YOSHI:
        case FTKIND_PURIN:
        case FTKIND_MEWTWO:
        case FTKIND_LUIGI:
        case FTKIND_ZELDA:
        case FTKIND_DRMARIO:
        case FTKIND_FALCO:
        case FTKIND_PICHU:
        case FTKIND_GAMEWATCH:
        case FTKIND_GANON:
            break;
        case FTKIND_LINK:
        case FTKIND_CLINK: {
            ftLk_DatAttrs* da = fp->dat_attrs;
            params = (itSword_UnkBytes*) &da->x64;
            break;
        }
        case FTKIND_MARS:
        case FTKIND_EMBLEM: {
            MarsAttributes* da = fp->dat_attrs;
            params = (itSword_UnkBytes*) &da->x78;
            break;
        }
        }
    }

    {
        f32 x20F8 = fp->x20F8;
        f32 x20FC = fp->x20FC;
        s32 ringIdx;
        f32 totalDist;
        f32* dp;

        {
            s32 idx = fp->x2101_bits_0to6;
            if (idx != 0) {
                ringIdx = idx - 1;
            } else {
                ringIdx = 2;
            }
        }

        cumDist[0] = 0.0f;
        totalDist = 0.0f;
        prevPos.x = prevPos.y = prevPos.z = 0.0f;
        dp = &cumDist[1];

        {
            s32 i;
            s32 curIdx = ringIdx;

            for (i = (s8) (u8) fp->x2100 - 1; i >= 0; i--) {
                struct Fighter_x20B0_t* entry = &fp->x20B0[curIdx];

                delta.x = entry->xC.x * x20FC + entry->x0.x - prevPos.x;
                delta.y = entry->xC.y * x20FC + entry->x0.y - prevPos.y;
                delta.z = entry->xC.z * x20FC + entry->x0.z - prevPos.z;

                if (i != (s8) (u8) fp->x2100 - 1) {
                    f32 d2 = delta.z * delta.z +
                             (delta.x * delta.x + delta.y * delta.y);
                    if (d2 > 0.0f) {
                        d2 = sqrtf(d2);
                    }
                    totalDist += d2;
                    *dp = totalDist;
                    dp++;
                }

                prevPos = delta;

                if (i != 0) {
                    if (curIdx != 0) {
                        nextIdx = curIdx - 1;
                    } else {
                        nextIdx = 2;
                    }
                }
                curIdx = nextIdx;
            }
        }

        if (totalDist < 0.00001f) {
            totalDist = 1.0f;
        }

        {
            f32 scaleDiff = x20FC - x20F8;
            s32 curIdx2;
            f32 blendedInner = params->x0 * scaleDiff + x20F8;
            f32 blendedOuter = params->x4 * scaleDiff + x20F8;
            f32 interpFactor = 1.0f;
            f32 innerDiff = x20F8 - blendedInner;
            f32 outerDiff = x20FC - blendedOuter;
            s32 remaining;
            f32* distPtr;
            AfterimageVtx* vp;

            numVerts = 0;

            {
                s32 idx2 = fp->x2101_bits_0to6;
                if (idx2 != 0) {
                    curIdx2 = idx2 - 1;
                } else {
                    curIdx2 = 2;
                }
            }

            remaining = (s8) (u8) fp->x2100 - 1;
            distPtr = &cumDist[0];
            vp = &vtx_buf[0];

            while (remaining >= 0) {
                struct Fighter_x20B0_t* curEntry;
                f32 outerScale, innerScale;
                s32 alpha;

                curEntry = &fp->x20B0[curIdx2];
                outerScale = interpFactor * outerDiff + blendedOuter;
                innerScale = interpFactor * innerDiff + blendedInner;
                numVerts += 2;
                distPtr++;

                alpha = (s32) (interpFactor * (f32) (params->x8 - params->x9) +
                               (f32) params->x9);

                vp->x = curEntry->xC.x * innerScale + curEntry->x0.x;
                vp->y = curEntry->xC.y * innerScale + curEntry->x0.y;
                vp->z = curEntry->xC.z * innerScale + curEntry->x0.z;
                vp->r = params->xA;
                vp->g = params->xB;
                vp->b = params->xC;
                vp->a = alpha;

                (vp + 1)->x = curEntry->xC.x * outerScale + curEntry->x0.x;
                (vp + 1)->y = curEntry->xC.y * outerScale + curEntry->x0.y;
                (vp + 1)->z = curEntry->xC.z * outerScale + curEntry->x0.z;
                (vp + 1)->r = params->xE;
                (vp + 1)->g = params->xF;
                (vp + 1)->b = params->x10;
                (vp + 1)->a = alpha;

                vp += 2;

                if (remaining != 0) {
                    s32 nextRingIdx;
                    struct Fighter_x20B0_t* nextEntry;

                    if (curIdx2 != 0) {
                        nextRingIdx = curIdx2 - 1;
                    } else {
                        nextRingIdx = 2;
                    }
                    nextEntry = &fp->x20B0[nextRingIdx];
                    nextIdx = nextRingIdx;

                    if (lbVector_CrossprodNormalized(
                            &curEntry->xC, &nextEntry->xC, &crossProd) != NULL)
                    {
                        f32 angle =
                            lbVector_Angle(&curEntry->xC, &nextEntry->xC);
                        f32 subdivAngle = angle / AFTERIMAGE_ANGLE_STEP;
                        s32 numSubdiv = (s32) subdivAngle;
                        interpFactor = 1.0f - (*distPtr / totalDist);

                        if (numSubdiv != 0) {
                            f32 frac;
                            s32 j;
                            f32 cumAngle = 0.0f;
                            f32 interpInner2, interpOuter2;
                            f32 basePosX, basePosY, basePosZ;
                            f32 stepPosX, stepPosY, stepPosZ;
                            s32 alphaStep;

                            tempDir = curEntry->xC;

                            frac = 1.0f / (f32) (numSubdiv + 1);

                            interpInner2 =
                                frac *
                                ((interpFactor * innerDiff + blendedInner) -
                                 innerScale);
                            interpOuter2 =
                                frac *
                                ((interpFactor * outerDiff + blendedOuter) -
                                 outerScale);

                            basePosX = curEntry->x0.x;
                            basePosY = curEntry->x0.y;
                            basePosZ = curEntry->x0.z;

                            stepPosX = frac * (nextEntry->x0.x - basePosX);
                            stepPosY = frac * (nextEntry->x0.y - basePosY);
                            stepPosZ = frac * (nextEntry->x0.z - basePosZ);

                            alphaStep =
                                (s32) (frac *
                                       ((interpFactor *
                                             (f32) (params->x8 - params->x9) +
                                         (f32) params->x9) -
                                        (f32) alpha));

                            for (j = 0; j < numSubdiv; j++) {
                                cumAngle += angle * frac;
                                basePosX += stepPosX;
                                basePosY += stepPosY;
                                basePosZ += stepPosZ;
                                innerScale += interpInner2;
                                outerScale += interpOuter2;
                                alpha += alphaStep;

                                tempDir = curEntry->xC;
                                lbVector_RotateAboutUnitAxis(
                                    &tempDir, &crossProd, cumAngle);

                                numVerts += 2;
                                vp->x = tempDir.x * innerScale + basePosX;
                                vp->y = tempDir.y * innerScale + basePosY;
                                vp->z = tempDir.z * innerScale + basePosZ;
                                vp->r = params->xA;
                                vp->g = params->xB;
                                vp->b = params->xC;
                                vp->a = alpha;
                                (vp + 1)->x =
                                    tempDir.x * outerScale + basePosX;
                                (vp + 1)->y =
                                    tempDir.y * outerScale + basePosY;
                                (vp + 1)->z =
                                    tempDir.z * outerScale + basePosZ;
                                (vp + 1)->r = params->xE;
                                (vp + 1)->g = params->xF;
                                (vp + 1)->b = params->x10;
                                (vp + 1)->a = alpha;
                                vp += 2;
                            }
                        }
                    }
                }

                curIdx2 = nextIdx;
                remaining--;
            }

            GXClearVtxDesc();
            GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_TEX_ST, GX_RGBA6, 0);
            GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_TEX_ST, GX_RGBA8, 0);
            GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
            GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
            {
                HSD_CObj* cobj = HSD_CObjGetCurrent();
                GXLoadPosMtxImm(HSD_CObjGetViewingMtxPtrDirect(cobj), 0);
            }
            GXSetCurrentMtx(0);
            GXBegin(GX_TRIANGLESTRIP, GX_VTXFMT0, numVerts + 1);

            GXPosition3f32(vtx_buf[0].x, vtx_buf[0].y, vtx_buf[0].z);
            GXColor4u8(vtx_buf[0].r, vtx_buf[0].g, vtx_buf[0].b, vtx_buf[0].a);
            GXPosition3f32(vtx_buf[2].x, vtx_buf[2].y, vtx_buf[2].z);
            GXColor4u8(vtx_buf[2].r, vtx_buf[2].g, vtx_buf[2].b, vtx_buf[2].a);

            if (numVerts > 1) {
                AfterimageVtx* p = &vtx_buf[1];
                u32 count = (u32) (numVerts - 1);
                u32 n4 = count >> 2;
                if (n4 != 0) {
                    do {
                        GXPosition3f32(p[0].x, p[0].y, p[0].z);
                        GXColor4u8(p[0].r, p[0].g, p[0].b, p[0].a);
                        GXPosition3f32(p[1].x, p[1].y, p[1].z);
                        GXColor4u8(p[1].r, p[1].g, p[1].b, p[1].a);
                        GXPosition3f32(p[2].x, p[2].y, p[2].z);
                        GXColor4u8(p[2].r, p[2].g, p[2].b, p[2].a);
                        GXPosition3f32(p[3].x, p[3].y, p[3].z);
                        GXColor4u8(p[3].r, p[3].g, p[3].b, p[3].a);
                        p += 4;
                        n4--;
                    } while (n4 != 0);
                    count &= 3;
                    if (count != 0) {
                        goto remainder;
                    }
                } else {
                remainder:
                    do {
                        GXPosition3f32(p->x, p->y, p->z);
                        GXColor4u8(p->r, p->g, p->b, p->a);
                        p++;
                        count--;
                    } while (count != 0);
                }
            }
        }
    }

    HSD_StateInvalidate(-1);
}

void ftCo_800C2FD8(Fighter_GObj* gobj)
{
    Fighter* fp;
    HSD_JObj* jobj;
    struct Fighter_x20B0_t* temp_r30;
    int var_r29;
    struct SwordAttrs* var_r5;
    int var_r0;
    PAD_STACK(0x8);

    fp = GET_FIGHTER(gobj);
    if (fp->x2100 == -1) {
        return;
    }

    temp_r30 = &fp->x20B0[fp->x2101_bits_0to6];
    if (fp->x2101_bits_8) {
        if (fp->item_gobj == NULL) {
            fp->x2100 = -1;
            return;
        }
        switch (itGetKind(fp->item_gobj)) {
        case It_Kind_Sword: {
            it_802852B8(fp->item_gobj, &fp->x20F8, &fp->x20FC);
            var_r29 = 1;
            break;
        }
        default: {
            HSD_ASSERTREPORT(0x16D, 0, "no afterimage item!\n");
        }
        }
        jobj = it_80285314(fp->item_gobj);
    } else {
        switch (fp->kind) {
        case FTKIND_SEAK:
        case FTKIND_NESS:
        case FTKIND_PEACH:
        case FTKIND_POPO:
        case FTKIND_NANA:
        case FTKIND_PIKACHU:
        case FTKIND_SAMUS:
        case FTKIND_YOSHI:
        case FTKIND_PURIN:
        case FTKIND_MEWTWO:
        case FTKIND_LUIGI:
        case FTKIND_ZELDA:
        case FTKIND_DRMARIO:
        case FTKIND_FALCO:
        case FTKIND_PICHU:
        case FTKIND_GAMEWATCH:
        case FTKIND_GANON:
            /// @bug Undefined behavior if the fighter doesn't have a sword!
            break;
        case FTKIND_LINK:
        case FTKIND_CLINK: {
            ftLk_DatAttrs* da = fp->dat_attrs;
            var_r5 = &da->x64;
            break;
        }
        case FTKIND_MARS:
        case FTKIND_EMBLEM: {
            MarsAttributes* da = fp->dat_attrs;
            var_r5 = &da->x78;
            break;
        }
        }
        var_r29 = 0;
        fp->x20F8 = var_r5->x18;
        fp->x20FC = var_r5->x1C;
        jobj = fp->parts[var_r5->x14].joint;
    }
    lb_8000B1CC(jobj, NULL, &temp_r30->x0);
    temp_r30->xC.x = jobj->mtx[0][var_r29];
    temp_r30->xC.y = jobj->mtx[1][var_r29];
    temp_r30->xC.z = jobj->mtx[2][var_r29];
    if (fp->x2101_bits_0to6 == 2) {
        var_r0 = 0;
    } else {
        var_r0 = fp->x2101_bits_0to6 + 1;
    }
    fp->x2101_bits_0to6 = var_r0;
    if (fp->x2100 < 3) {
        fp->x2100++;
    }
}
