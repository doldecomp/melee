#include "tydisplay.h"

#include "gm/gm_1A3F.h"
#include "gm/gm_1A45.h"
#include "if/textdraw.h"
#include "if/textlib.h"
#include "lb/lblanguage.h"
#include "ty/toy.h"
#include "ty/tyfigupon.h"
#include "ty/tylist.h"
#include "ty/types.h"

#include <placeholder.h>

#include <MSL/math_ppc.h>
#include <MSL/trigf.h>

#include <baselib/archive.h>
#include <baselib/cobj.h>
#include <baselib/debug.h>
#include <baselib/fog.h>
#include <baselib/gobj.h>
#include <baselib/gobjgxlink.h>
#include <baselib/gobjobject.h>
#include <baselib/gobjplink.h>
#include <baselib/gobjproc.h>
#include <baselib/jobj.h>
#include <baselib/lobj.h>
#include <baselib/memory.h>
#include <baselib/random.h>

#include <dolphin/os.h>

#include "lb/lb_00B0.h"
#include "lb/lb_00CE.h"
#include "lb/lb_00F9.h"
#include "lb/lbaudio_ax.h"
#include "lb/lbarchive.h"
#include "lb/lbvector.h"

#include "mn/mnmain.h"

#include "db/db.h"

extern char un_804D5AC0[2];
extern DevText* un_804D6F24;
extern s32 un_804A2DE8[];
extern char un_804A2D98[0x38];

typedef struct TyDspBgData {
    /* 0x00 */ HSD_GObj* gobj0;
    /* 0x04 */ HSD_GObj* gobj4;
    /* 0x08 */ u8 pad8[4];
    /* 0x0C */ HSD_JObj* jobj;
    /* 0x10 */ u8 pad10[0x3C];
    /* 0x4C */ HSD_Archive* archive;
} TyDspBgData;

extern TyDspBgData* un_804D6F1C;
extern s32 un_804D6F20;
extern HSD_GObj** un_804D6F18;
extern HSD_GObj* un_804D6F2C;
extern s32 un_804D6F28;
extern u8 un_804A2DD0[0x18];

typedef struct TyDspArchNames {
    const char* entries[43];
} TyDspArchNames;

typedef struct TyDspNameTables {
    const char* jobj_names[43];
    const char* matanim_names[43];
    TyDspArchNames arch_names;
    s32 terminator;
} TyDspNameTables;

extern const TyDspNameTables un_803B8988;
extern const TyDspArchNames un_803B8A34;

typedef struct TyDspEntry {
    /* 0x00 */ s32 x00;
    /* 0x04 */ u8 x04;
    /* 0x05 */ u8 x05;
    /* 0x06 */ u8 pad_06[2];
    /* 0x08 */ f32 x08;
    /* 0x0C */ f32 x0C;
} TyDspEntry;

typedef struct TyDspSceneGfx {
    /* 0x00 */ HSD_GObj* x00;
    /* 0x04 */ HSD_GObj* x04;
    /* 0x08 */ HSD_GObj* x08;
} TyDspSceneGfx;

typedef struct TyDspPos {
    /* 0x00 */ f32 x;
    /* 0x04 */ f32 z;
} TyDspPos;

typedef struct TyDspGrid {
    /* 0x000 */ s32 x00;
    /* 0x004 */ f32 x04;
    /* 0x008 */ f32 x08;
    /* 0x00C */ f32 x0C;
    /* 0x010 */ f32 x10;
    /* 0x014 */ TySortElemI sort[301];
    /* 0x97C */ TyDspPos pos[301];
} TyDspGrid;

/// #un_803181BC

void un_803182D4_OnFrame(void)
{
    TyModeState* state = (TyModeState*) un_804A284C;

    if (state->x4 != 0) {
        un_803181BC();
        gm_801A4B60();
    }
}

void un_8031830C(TySortElem* base, s32 lo, s32 hi)
{
    TySortElem tmp;
    PAD_STACK(8);

    if (lo < hi) {
        s32 mid = (lo + hi) / 2;
        s32 pivot, i;
        TySortElem* p;
        TySortElem* q;

        if (lo != mid) {
            p = &base[lo];
            q = &base[mid];
            tmp = *p;
            *p = *q;
            *q = tmp;
        }

        i = lo + 1;
        pivot = lo;
        p = &base[lo];
        for (q = &base[i]; i <= hi; i++, q++) {
            if (q->val < p->val) {
                pivot += 1;
                if (pivot != i) {
                    TySortElem* s = &base[pivot];
                    tmp = *s;
                    *s = *q;
                    *q = tmp;
                }
            }
        }

        if (lo != pivot) {
            q = &base[pivot];
            tmp = *p;
            *p = *q;
            *q = tmp;
        }

        if (lo < pivot - 1) {
            s32 mid2 = (pivot + lo - 1) / 2;
            s32 pivot2, j2;

            p = &base[lo];
            if (lo != mid2) {
                q = &base[mid2];
                tmp = *p;
                *p = *q;
                *q = tmp;
            }

            j2 = lo + 1;
            pivot2 = lo;
            for (q = &base[lo + 1]; j2 <= pivot - 1; j2++, q++) {
                if (q->val < p->val) {
                    pivot2 += 1;
                    if (pivot2 != j2) {
                        TySortElem* s = &base[pivot2];
                        tmp = *s;
                        *s = *q;
                        *q = tmp;
                    }
                }
            }

            if (lo != pivot2) {
                q = &base[pivot2];
                tmp = *p;
                *p = *q;
                *q = tmp;
            }

            un_8031830C(base, lo, pivot2 - 1);
            un_8031830C(base, pivot2 + 1, pivot - 1);
        }

        if (pivot + 1 < hi) {
            s32 mid3 = (pivot + hi + 1) / 2;
            s32 pivot3, j3;
            TySortElem* rp;

            rp = &base[pivot + 1];
            if (pivot + 1 != mid3) {
                q = &base[mid3];
                tmp = *rp;
                *rp = *q;
                *q = tmp;
            }

            j3 = pivot + 2;
            pivot3 = pivot + 1;
            for (q = &base[j3]; j3 <= hi; j3++, q++) {
                if (q->val < rp->val) {
                    pivot3 += 1;
                    if (pivot3 != j3) {
                        TySortElem* s = &base[pivot3];
                        tmp = *s;
                        *s = *q;
                        *q = tmp;
                    }
                }
            }

            if (pivot + 1 != pivot3) {
                q = &base[pivot3];
                tmp = *rp;
                *rp = *q;
                *q = tmp;
            }

            un_8031830C(base, pivot + 1, pivot3 - 1);
            un_8031830C(base, pivot3 + 1, hi);
        }
    }
}

void un_80318714(TySortElemI* base, s32 lo, s32 hi)
{
    TySortElemI tmp;
    PAD_STACK(8);

    if (lo < hi) {
        s32 mid = (lo + hi) / 2;
        s32 pivot, i;
        TySortElemI* p;
        TySortElemI* q;

        if (lo != mid) {
            p = &base[lo];
            q = &base[mid];
            tmp = *p;
            *p = *q;
            *q = tmp;
        }

        i = lo + 1;
        pivot = lo;
        p = &base[lo];
        for (q = &base[i]; i <= hi; i++, q++) {
            if (q->val > p->val) {
                pivot += 1;
                if (pivot != i) {
                    TySortElemI* s = &base[pivot];
                    tmp = *s;
                    *s = *q;
                    *q = tmp;
                }
            }
        }

        if (lo != pivot) {
            q = &base[pivot];
            tmp = *p;
            *p = *q;
            *q = tmp;
        }

        if (lo < pivot - 1) {
            s32 mid2 = (pivot + lo - 1) / 2;
            s32 pivot2, j2;

            p = &base[lo];
            if (lo != mid2) {
                q = &base[mid2];
                tmp = *p;
                *p = *q;
                *q = tmp;
            }

            j2 = lo + 1;
            pivot2 = lo;
            for (q = &base[lo + 1]; j2 <= pivot - 1; j2++, q++) {
                if (q->val > p->val) {
                    pivot2 += 1;
                    if (pivot2 != j2) {
                        TySortElemI* s = &base[pivot2];
                        tmp = *s;
                        *s = *q;
                        *q = tmp;
                    }
                }
            }

            if (lo != pivot2) {
                q = &base[pivot2];
                tmp = *p;
                *p = *q;
                *q = tmp;
            }

            un_80318714(base, lo, pivot2 - 1);
            un_80318714(base, pivot2 + 1, pivot - 1);
        }

        if (pivot + 1 < hi) {
            s32 mid3 = (pivot + hi + 1) / 2;
            s32 pivot3, j3;
            TySortElemI* rp;

            rp = &base[pivot + 1];
            if (pivot + 1 != mid3) {
                q = &base[mid3];
                tmp = *rp;
                *rp = *q;
                *q = tmp;
            }

            j3 = pivot + 2;
            pivot3 = pivot + 1;
            for (q = &base[j3]; j3 <= hi; j3++, q++) {
                if (q->val > rp->val) {
                    pivot3 += 1;
                    if (pivot3 != j3) {
                        TySortElemI* s = &base[pivot3];
                        tmp = *s;
                        *s = *q;
                        *q = tmp;
                    }
                }
            }

            if (pivot + 1 != pivot3) {
                q = &base[pivot3];
                tmp = *rp;
                *rp = *q;
                *q = tmp;
            }

            un_80318714(base, pivot + 1, pivot3 - 1);
            un_80318714(base, pivot3 + 1, hi);
        }
    }
}

extern u8* un_804D6F14;
extern void* un_804D6F10;

s32 un_80318B1C(s32 arg0)
{
    TyDspGrid* grid = (TyDspGrid*) un_804D6F14;
    s32 start;
    s32 placed;
    s32 i;
    s32 rand_id;
    TyDspEntry* check;

    if (arg0 > 1) {
        start = HSD_Randi(arg0 - 1);
    } else {
        start = 0;
    }

    if (arg0 > 0x125) {
        placed = 0;
        i = 0;
        while (placed < arg0) {
            if (i >= 0x125) {
                rand_id = HSD_Randi(0x124);
                check = (TyDspEntry*) un_8031B9DC(rand_id);
                while (check->x00 == -1) {
                    rand_id = HSD_Randi(0x124);
                    check = (TyDspEntry*) un_8031B9DC(rand_id);
                }
                grid->sort[start].key = rand_id;
                grid->sort[start].val =
                    (s32) un_803060BC(grid->sort[start].key, 7);
                start++;
                if (start >= arg0) {
                    start = 0;
                }
                placed++;
            } else {
                check = (TyDspEntry*) un_8031B9DC(i);
                if (check->x00 != -1) {
                    grid->sort[start].key = i;
                    grid->sort[start].val = (s32) un_803060BC(i, 7);
                    start++;
                    if (start >= arg0) {
                        start = 0;
                    }
                    placed++;
                }
            }
            i++;
        }
    } else {
        i = 0;
        do {
            if (un_803048C0(i) != 0) {
                un_8031B9DC(i);
                grid->sort[start].key = i;
                grid->sort[start].val = (s32) un_803060BC(i, 7);
                start++;
                if (start >= arg0) {
                    start = 0;
                }
            }
            i++;
        } while (i < 0x125);
    }
}

void un_80318CB4(s32 arg0)
{
    u8* grid = (u8*) un_804D6F14;
    u8* cfg = (u8*) un_804D6F18;
    s32 prev_ring_size;
    s32 ring_count = 0;
    s32 ring_max = 6;
    f32 angle = 0.0f;
    f32 radius;
    f32 base_step;
    s32 i;
    s32 count;
    s32 n2;
    s32 mid;
    s32 pivot;
    s32 j;
    s32 n;
    u8* ptr;

    PAD_STACK(0x48);

    memzero(grid, 0x12E4);
    *(f32*)(grid + 0x08) = -3.5f;
    *(f32*)(grid + 0x04) = -3.5f;
    *(f32*)(grid + 0x10) = 3.5f;
    *(f32*)(grid + 0x0C) = 3.5f;

    if (arg0 != 0) {
        base_step = 9.0f;
    } else {
        base_step = 11.0f;
    }
    radius = base_step;

    ptr = grid;
    for (i = 0; i < *(s32*)(cfg + 0x08); i++) {
        if (i == 0) {
            *(f32*)(ptr + 0x97C) = 0.0f;
            *(f32*)(ptr + 0x980) = 0.0f;
        } else {
            f32 rad = 0.017453292f * angle;
            *(f32*)(ptr + 0x97C) = radius * cosf(rad);
            *(f32*)(ptr + 0x980) = radius * sinf(rad);
            if (arg0 == 0) {
                *(f32*)(ptr + 0x97C) = 2.0f * HSD_Randf() + *(f32*)(ptr + 0x97C);
                *(f32*)(ptr + 0x980) = 2.0f * HSD_Randf() + *(f32*)(ptr + 0x980);
            }
            if (HSD_Randi(3) != 0) {
                f32 theta = atan2f(*(f32*)(ptr + 0x980), *(f32*)(ptr + 0x97C));
                f32 mag = sqrtf(*(f32*)(ptr + 0x97C) * *(f32*)(ptr + 0x97C) + *(f32*)(ptr + 0x980) * *(f32*)(ptr + 0x980));
                s32 tries;
                s32 start;
                s32 collided;

                if (i < 0x24) {
                    start = 0;
                } else {
                    start = i - (prev_ring_size * 2 - 6);
                }

                collided = 0;
retry:
                if (collided == 0) {
                    s32 k;
                    u8* other;
                    *(f32*)(ptr + 0x97C) = mag * cosf(theta);
                    *(f32*)(ptr + 0x980) = mag * sinf(theta);
                    tries = (s32)(mag / 0.1f);
                    if (HSD_Randi(2) != 0) {
                        f32 half = mag * 0.5f;
                        if ((s32) half > 1) {
                            tries -= HSD_Randi((s32) half);
                        }
                    }
                    k = i - 1;
                    other = grid + (k * 8);
                    while (k >= start) {
                        f32 dx = *(f32*)(ptr + 0x97C) - *(f32*)(other + 0x97C);
                        f32 dz = *(f32*)(ptr + 0x980) - *(f32*)(other + 0x980);
                        f32 dist = sqrtf(dx * dx + dz * dz);
                        if (dist > 2.1474836e9f || dist < -2.1474836e9f) {
                            OSReport("*** tyDisplay Atari Irregul!\n");
                            __assert("tydisplay.c", 0xC6U, "0");
                        }
                        if ((s32) dist <= (s32) 8.0f) {
                            collided = 1;
                            break;
                        }
                        other -= 8;
                        k -= 1;
                    }
                    if (tries != 0) {
                        if (collided == 0) {
                            mag -= 0.1f;
                        }
                        collided = 0;
                        goto retry;
                    }
                }
            }
            ring_count += 1;
            if (ring_count >= ring_max) {
                if (arg0 != 0) {
                    radius += 9.0f;
                } else {
                    radius += 11.0f;
                }
                prev_ring_size = ring_max;
                ring_count = 0;
                ring_max += 6;
                if (arg0 != 0) {
                    angle = 0.0f;
                } else {
                    angle = (f32) HSD_Randi(0x1E);
                }
            } else {
                angle += 360.0f / (f32) ring_max;
            }
        }
        {
            f32 x = *(f32*)(ptr + 0x97C);
            if (x < *(f32*)(grid + 0x04)) *(f32*)(grid + 0x04) = x;
        }
        {
            f32 x = *(f32*)(ptr + 0x97C);
            if (x > *(f32*)(grid + 0x0C)) *(f32*)(grid + 0x0C) = x;
        }
        {
            f32 z = *(f32*)(ptr + 0x980);
            if (z < *(f32*)(grid + 0x08)) *(f32*)(grid + 0x08) = z;
        }
        {
            f32 z = *(f32*)(ptr + 0x980);
            if (z > *(f32*)(grid + 0x10)) *(f32*)(grid + 0x10) = z;
        }
        ptr += 8;
    }

    count = *(s32*)(cfg + 0x08);
    if (count > 1) {
        n2 = count - 1;
        if (n2 > 0) {
            TySortElem tmp;
            TySortElem* sort = (TySortElem*)(grid + 0x97C);
            mid = n2 / 2;

            if (mid != 0) {
                tmp = sort[0];
                sort[0] = sort[mid];
                sort[mid] = tmp;
            }

            pivot = 0;
            j = 0;
            for (ptr = (u8*)&sort[1], n = 1; n2 >= n; n++, ptr += 8) {
                if (*(f32*)(ptr + 4) < sort[0].val) {
                    pivot += 1;
                    j += 8;
                    if (pivot != n) {
                        TySortElem* s = (TySortElem*)(grid + j + 0x97C);
                        tmp = *s;
                        *s = *(TySortElem*)ptr;
                        *(TySortElem*)ptr = tmp;
                    }
                }
            }

            if (pivot != 0) {
                TySortElem* s = &sort[pivot];
                tmp = sort[0];
                sort[0] = *s;
                *s = tmp;
            }

            un_8031830C(sort, 0, pivot - 1);
            un_8031830C(sort, pivot + 1, n2);
        }
    }

    un_80318B1C(*(s32*)(cfg + 0x08));

    count = *(s32*)(cfg + 0x08);
    if (count > 1) {
        n2 = (count / 3) * 2;
        if (n2 > 0) {
            TySortElemI tmp;
            TySortElemI* sort = (TySortElemI*)(grid + 0x14);
            mid = n2 / 2;

            if (mid != 0) {
                tmp = sort[0];
                sort[0] = sort[mid];
                sort[mid] = tmp;
            }

            pivot = 0;
            j = 0;
            for (ptr = (u8*)&sort[1], n = 1; n2 >= n; n++, ptr += 8) {
                if (*(s32*)(ptr + 4) > sort[0].val) {
                    pivot += 1;
                    j += 8;
                    if (pivot != n) {
                        TySortElemI* s = (TySortElemI*)(grid + j + 0x14);
                        tmp = *s;
                        *s = *(TySortElemI*)ptr;
                        *(TySortElemI*)ptr = tmp;
                    }
                }
            }

            if (pivot != 0) {
                TySortElemI* s = &sort[pivot];
                tmp = sort[0];
                sort[0] = *s;
                *s = tmp;
            }

            un_80318714(sort, 0, pivot - 1);
            un_80318714(sort, pivot + 1, n2);
        }
    }

    {
        s32 k;
        s32 off = 0;
        u8* posptr = grid;
        ptr = grid;
        for (k = 0; k < *(s32*)(cfg + 0x08); k++) {
            HSD_GObj* gobj;
            HSD_JObj** jobjArr;
            *(HSD_GObj**)(cfg + 0x78) = un_8031BC54(*(s32*)(ptr + 0x14));
            gobj = *(HSD_GObj**)(cfg + 0x78);
            if (gobj != NULL) {
                jobjArr = un_804D6F10;
                *(HSD_JObj**)((u8*)jobjArr + off) = (HSD_JObj*) gobj->hsd_obj;
                {
                    f32 xpos = *(f32*)(posptr + 0x97C);
                    HSD_JObj* jobj = *(HSD_JObj**)((u8*)jobjArr + off);
                    HSD_JObjSetTranslateX(jobj, xpos);
                }
                {
                    f32 zpos = *(f32*)(posptr + 0x980);
                    HSD_JObj* jobj = *(HSD_JObj**)((u8*)jobjArr + off);
                    HSD_JObjSetTranslateZ(jobj, zpos);
                }
                off += 4;
                posptr += 8;
            }
            ptr += 8;
        }
    }
}

void un_80319540(s32 arg0)
{
    u8* grid = un_804D6F14;
    u8* cfg = (u8*) un_804D6F18;
    s32 count;
    s32 col, row, remainder;
    s32 i;
    u8* ptr;
    s32 n2;
    PAD_STACK(0x28);

    memzero(grid, 0x12E4);

    *(f32*)(grid + 0x08) = -3.5f;
    *(f32*)(grid + 0x04) = -3.5f;
    *(f32*)(grid + 0x10) = 3.5f;
    *(f32*)(grid + 0x0C) = 3.5f;

    count = *(s32*)(cfg + 0x08);
    if (count <= 1) {
        remainder = 0;
    } else {
        remainder = count % *(s8*)(cfg + 0x75);
    }

    col = 0;
    row = 0;
    ptr = grid;
    for (i = 0; i < count; i++) {
        if (i == 0) {
            *(f32*)(ptr + 0x97C) = 0.0f;
            *(f32*)(ptr + 0x980) = 0.0f;
        } else {
            f32 x = 9.0f * (f32) col;
            if (arg0 != 0 && (row % 2) != 0) {
                x = x + 3.5f;
            }
            *(f32*)(ptr + 0x97C) = x;
            *(f32*)(ptr + 0x980) = 9.0f * (f32) row;
        }

        col += 1;
        if (remainder != 0) {
            remainder -= 1;
            if (remainder == 0) {
                col = 0;
                row += 1;
            }
        } else if (col >= *(s8*)(cfg + 0x75)) {
            col = 0;
            row += 1;
        }

        {
            f32 px = *(f32*)(ptr + 0x97C);
            if (px < *(f32*)(grid + 0x04)) {
                *(f32*)(grid + 0x04) = px;
            }
        }
        {
            f32 px = *(f32*)(ptr + 0x97C);
            if (px > *(f32*)(grid + 0x0C)) {
                *(f32*)(grid + 0x0C) = px;
            }
        }
        {
            f32 pz = *(f32*)(ptr + 0x980);
            if (pz < *(f32*)(grid + 0x08)) {
                *(f32*)(grid + 0x08) = pz;
            }
        }
        {
            f32 pz = *(f32*)(ptr + 0x980);
            if (pz > *(f32*)(grid + 0x10)) {
                *(f32*)(grid + 0x10) = pz;
            }
        }

        ptr += 8;
        count = *(s32*)(cfg + 0x08);
    }

    un_80318B1C(count);

    if (count > 1) {
        n2 = (count / 3) * 2;
        if (n2 > 0) {
            s32 mid = n2 / 2;
            s32 pivot, j, n;
                        TySortElemI tmp;
            TySortElemI* sort = (TySortElemI*)(grid + 0x14);

            if (mid != 0) {
                tmp = sort[0];
                sort[0] = sort[mid];
                sort[mid] = tmp;
            }

            pivot = 0;
            j = 0;
            for (ptr = (u8*)&sort[1], n = 1; n2 >= n; n++, ptr += 8) {
                if (*(s32*)(ptr + 4) > sort[0].val) {
                    pivot += 1;
                    j += 8;
                    if (pivot != n) {
                        TySortElemI* s = (TySortElemI*)(grid + j + 0x14);
                        tmp = *s;
                        *s = *(TySortElemI*)ptr;
                        *(TySortElemI*)ptr = tmp;
                    }
                }
            }

            if (pivot != 0) {
                TySortElemI* s = &sort[pivot];
                tmp = sort[0];
                sort[0] = *s;
                *s = tmp;
            }

            un_80318714(sort, 0, pivot - 1);
            un_80318714(sort, pivot + 1, n2);
        }
    }

    ptr = grid;
    {
        s32 k;
        s32 off = 0;

        for (k = 0; k < *(s32*)(cfg + 0x08); k++) {
            HSD_GObj* gobj;
            HSD_JObj** jobjArr;
            *(HSD_GObj**)(cfg + 0x78) = un_8031BC54(*(s32*)(ptr + 0x14));
            gobj = *(HSD_GObj**)(cfg + 0x78);
            if (gobj != NULL) {
                jobjArr = un_804D6F10;
                *(HSD_JObj**)((u8*)jobjArr + off) = (HSD_JObj*) gobj->hsd_obj;
                {
                    f32 xpos = *(f32*)(ptr + 0x97C);
                    HSD_JObj* jobj = *(HSD_JObj**)((u8*)jobjArr + off);
                    HSD_JObjSetTranslateX(jobj, xpos);
                }
                {
                    f32 zpos = *(f32*)(ptr + 0x980);
                    HSD_JObj* jobj = *(HSD_JObj**)((u8*)jobjArr + off);
                    HSD_JObjSetTranslateZ(jobj, zpos);
                }
            }
            ptr += 8;
            off += 4;
        }
    }
}

void un_80319994(s32 arg0)
{
    u8* grid = (u8*) un_804D6F14;
    u8* cfg = (u8*) un_804D6F18;
    f32 xoff = 0.0f;
    s32 col = 0;
    s32 row = 0;
    s32 ring = 1;
    s32 i;
    s32 count;
    s32 n2;
    s32 mid;
    s32 pivot;
    s32 j;
    s32 n;
    u8* ptr;

    PAD_STACK(0x38);

    memzero(grid, 0x12E4);
    ptr = grid;
    *(f32*)(grid + 0x08) = -3.5f;
    *(f32*)(grid + 0x04) = -3.5f;
    *(f32*)(grid + 0x10) = 3.5f;
    *(f32*)(grid + 0x0C) = 3.5f;

    for (i = 0; i < *(s32*)(cfg + 0x08); i++) {
        if (i == 0) {
            *(f32*)(ptr + 0x97C) = 0.0f;
            *(f32*)(ptr + 0x980) = 0.0f;
        } else {
            *(f32*)(ptr + 0x97C) = 9.0f * (f32)col + xoff;
            if (arg0 != 0) {
                *(f32*)(ptr + 0x980) = -9.0f * (f32)row;
            } else {
                *(f32*)(ptr + 0x980) = 9.0f * (f32)row;
            }
        }
        col += 1;
        if (col >= ring) {
            xoff -= 4.5f;
            col = 0;
            row += 1;
            ring += 1;
        }
        {
            f32 x = *(f32*)(ptr + 0x97C);
            if (x < *(f32*)(grid + 0x04)) {
                *(f32*)(grid + 0x04) = x;
            }
        }
        {
            f32 x = *(f32*)(ptr + 0x97C);
            if (x > *(f32*)(grid + 0x0C)) {
                *(f32*)(grid + 0x0C) = x;
            }
        }
        {
            f32 z = *(f32*)(ptr + 0x980);
            if (z < *(f32*)(grid + 0x08)) {
                *(f32*)(grid + 0x08) = z;
            }
        }
        {
            f32 z = *(f32*)(ptr + 0x980);
            if (z > *(f32*)(grid + 0x10)) {
                *(f32*)(grid + 0x10) = z;
            }
        }
        ptr += 8;
    }

    count = *(s32*)(cfg + 0x08);
    if (arg0 != 0 && count > 1) {
        n2 = count - 1;
        if (n2 > 0) {
            TySortElem tmp;
            TySortElem* sort = (TySortElem*)(grid + 0x97C);
            mid = n2 / 2;

            if (mid != 0) {
                tmp = sort[0];
                sort[0] = sort[mid];
                sort[mid] = tmp;
            }

            pivot = 0;
            j = 0;
            for (ptr = (u8*)&sort[1], n = 1; n2 >= n; n++, ptr += 8) {
                if (*(f32*)(ptr + 4) < sort[0].val) {
                    pivot += 1;
                    j += 8;
                    if (pivot != n) {
                        TySortElem* s = (TySortElem*)(grid + j + 0x97C);
                        tmp = *s;
                        *s = *(TySortElem*)ptr;
                        *(TySortElem*)ptr = tmp;
                    }
                }
            }

            if (pivot != 0) {
                TySortElem* s = &sort[pivot];
                tmp = sort[0];
                sort[0] = *s;
                *s = tmp;
            }

            un_8031830C(sort, 0, pivot - 1);
            un_8031830C(sort, pivot + 1, n2);
        }
    }

    un_80318B1C(*(s32*)(cfg + 0x08));

    count = *(s32*)(cfg + 0x08);
    if (count > 1) {
        n2 = (count / 3) * 2;
        if (n2 > 0) {
            TySortElemI tmp;
            TySortElemI* sort = (TySortElemI*)(grid + 0x14);
            mid = n2 / 2;

            if (mid != 0) {
                tmp = sort[0];
                sort[0] = sort[mid];
                sort[mid] = tmp;
            }

            pivot = 0;
            j = 0;
            for (ptr = (u8*)&sort[1], n = 1; n2 >= n; n++, ptr += 8) {
                if (*(s32*)(ptr + 4) > sort[0].val) {
                    pivot += 1;
                    j += 8;
                    if (pivot != n) {
                        TySortElemI* s = (TySortElemI*)(grid + j + 0x14);
                        tmp = *s;
                        *s = *(TySortElemI*)ptr;
                        *(TySortElemI*)ptr = tmp;
                    }
                }
            }

            if (pivot != 0) {
                TySortElemI* s = &sort[pivot];
                tmp = sort[0];
                sort[0] = *s;
                *s = tmp;
            }

            un_80318714(sort, 0, pivot - 1);
            un_80318714(sort, pivot + 1, n2);
        }
    }

    ptr = grid;
    {
        s32 k;
        s32 off = 0;

        for (k = 0; k < *(s32*)(cfg + 0x08); k++) {
            HSD_GObj* gobj;
            HSD_JObj** jobjArr;
            *(HSD_GObj**)(cfg + 0x78) = un_8031BC54(*(s32*)(ptr + 0x14));
            gobj = *(HSD_GObj**)(cfg + 0x78);
            if (gobj != NULL) {
                jobjArr = un_804D6F10;
                *(HSD_JObj**)((u8*)jobjArr + off) = (HSD_JObj*) gobj->hsd_obj;
                {
                    f32 xpos = *(f32*)(ptr + 0x97C);
                    HSD_JObj* jobj = *(HSD_JObj**)((u8*)jobjArr + off);
                    HSD_JObjSetTranslateX(jobj, xpos);
                }
                {
                    f32 zpos = *(f32*)(ptr + 0x980);
                    HSD_JObj* jobj = *(HSD_JObj**)((u8*)jobjArr + off);
                    HSD_JObjSetTranslateZ(jobj, zpos);
                }
            }
            ptr += 8;
            off += 4;
        }
    }
}

void un_80319EF0(void)
{
    Vec3 interest;
    Vec3 sp28;
    Vec3 eyepos;
    u8* grid = (u8*) un_804D6F14;
    u8* cfg = (u8*) un_804D6F18;
    TyDspBgData* bg = un_804D6F1C;
    HSD_CObj* cobj;
    f32 range;
    f32 scale;

    PAD_STACK(0x18);

    cobj = (HSD_CObj*)(*(HSD_GObj**)(cfg + 0x00))->hsd_obj;

    range = *(f32*)(grid + 0x0C) - *(f32*)(grid + 0x04);
    if (range < 0.0f) {
        range = -range;
    }
    interest.x = range * 0.5f + *(f32*)(grid + 0x04);
    if (*(s32*)(grid + 0x00) == 3) {
        interest.x = 0.0f;
    }
    interest.y = 0.0f;
    {
        f32 zmin = *(f32*)(grid + 0x08);
        f32 zrange = *(f32*)(grid + 0x10) - zmin;
        if (zrange < 0.0f) {
            zrange = -zrange;
        }
        interest.z = zrange * 0.5f + zmin;
    }
    eyepos = interest;
    interest.z -= 10.0f;
    *(Vec3*)(cfg + 0x5C) = interest;
    HSD_CObjGetEyePosition(cobj, &sp28);
    sp28.x = eyepos.x;
    sp28.z = 500.0f + eyepos.z;
    *(Vec3*)(cfg + 0x68) = sp28;
    HSD_CObjSetInterest(cobj, &interest);
    HSD_CObjSetEyePosition(cobj, &sp28);

    {
        f32 xrange = *(f32*)(grid + 0x0C) - *(f32*)(grid + 0x04);
        if (xrange < 0.0f) {
            xrange = -xrange;
        }
        *(f32*)(cfg + 0x40) = 14.0f + xrange;
    }
    *(f32*)(cfg + 0x44) = 1.0f;

    while (500.0f * tanf(0.017453292f * (*(f32*)(cfg + 0x44) * 0.5f)) < *(f32*)(cfg + 0x40) * 0.5f) {
        *(f32*)(cfg + 0x44) = *(f32*)(cfg + 0x44) + 0.1f;
    }

    if (*(f32*)(cfg + 0x44) < 3.0f) {
        *(f32*)(cfg + 0x44) = 3.2f;
    }
    HSD_CObjSetFov(cobj, *(f32*)(cfg + 0x44));

    *(f32*)(cfg + 0x4C) = (f32)*(s32*)(cfg + 0x08) * 0.0033333334f + 3.0f;
    {
        f32 fov2 = *(f32*)(cfg + 0x44);
        *(f32*)(cfg + 0x50) = fov2 + fov2 / 5.0f;
    }
    if (*(f32*)(cfg + 0x44) < 3.0f) {
        *(f32*)(cfg + 0x48) = (*(f32*)(cfg + 0x50) - *(f32*)(cfg + 0x4C)) / 30.0f;
    } else {
        *(f32*)(cfg + 0x48) = (*(f32*)(cfg + 0x50) - *(f32*)(cfg + 0x4C)) / 60.0f;
    }

    {
        s32 mode = *(s32*)(grid + 0x00);
        switch (mode) {
        default:
            *(f32*)(cfg + 0x54) = -((14.0f + *(f32*)(cfg + 0x40)) * 0.5f - *(f32*)(cfg + 0x5C));
            *(f32*)(cfg + 0x58) = (14.0f + *(f32*)(cfg + 0x40)) * 0.5f + *(f32*)(cfg + 0x5C);
            break;
        case 2:
            *(f32*)(cfg + 0x54) = -((7.0f + *(f32*)(cfg + 0x40)) * 0.5f - *(f32*)(cfg + 0x5C));
            *(f32*)(cfg + 0x58) = (7.0f + *(f32*)(cfg + 0x40)) * 0.5f + *(f32*)(cfg + 0x5C);
            break;
        case 3:
            *(f32*)(cfg + 0x54) = -(*(f32*)(cfg + 0x40) * 0.5f - *(f32*)(cfg + 0x5C));
            *(f32*)(cfg + 0x58) = *(f32*)(cfg + 0x40) * 0.5f + *(f32*)(cfg + 0x5C);
            break;
        }
    }

    *(f32*)(cfg + 0x1C) = 57.29578f * lb_8000D008((*(f32*)(cfg + 0x58) - *(f32*)(cfg + 0x54)) * 0.5f, 500.0f);
    *(f32*)(cfg + 0x18) = 57.29578f * lb_8000D008(*(f32*)(cfg + 0x40) * 0.5f, 500.0f);

    {
        HSD_JObj* jobj = (HSD_JObj*) bg->gobj4->hsd_obj;
        HSD_JObjSetTranslate(jobj, &eyepos);
    }

    {
        f32 zrange = 14.0f + (*(f32*)(grid + 0x10) - *(f32*)(grid + 0x08));
        f32 xrange = *(f32*)(grid + 0x0C) - *(f32*)(grid + 0x04);
        scale = (f32)(*(s32*)(cfg + 0x08) / 30);
        if (zrange < xrange) {
            zrange = 14.0f + xrange;
        }
        if (38.0f * scale < zrange) {
            while (38.0f * scale < zrange) {
                scale += 0.1f;
            }
        } else {
            while (38.0f * scale > zrange) {
                scale -= 0.1f;
            }
        }
        if (scale > 2.1474836e9f || scale < -2.1474836e9f) {
            OSReport("*** tyDisplay Table Scale Irregul!\n");
            __assert("tydisplay.c", 0x28CU, "0");
        }
        if ((s32) scale != 0) {
            HSD_JObjSetScaleX(bg->jobj, scale);
            HSD_JObjSetScaleZ(bg->jobj, scale);
        }
    }
}

void fn_8031A4EC(HSD_GObj* arg0)
{
    Vec3 interest;
    Vec3 eye;
    Vec3 sp40;
    f32 sp3C;
    f32 sp38;
    f32 sp34;
    Vec3 sp28;
    f32 sp24;
    f32 sp20;
    f32 sp1C;
    HSD_CObj* cobj = (HSD_CObj*) arg0->hsd_obj;
    u8* cfg = (u8*) un_804D6F18;
    f32 fov;
    f32 val;
    s32 sign;

    PAD_STACK(0x18);

    HSD_CObjGetInterest(cobj, &interest);
    HSD_CObjGetEyePosition(cobj, &eye);
    fov = HSD_CObjGetFov(cobj);

    *(f32*)(cfg + 0x20) = un_80305D00();
    *(f32*)(cfg + 0x24) = un_80305DB0();

    val = *(f32*)(cfg + 0x20);
    if (val > -0.2f && val < 0.2f) {
        *(f32*)(cfg + 0x20) = 0.0f;
    } else {
        if (val > 0.0f) {
            sign = 1;
        } else {
            sign = -1;
        }
        *(f32*)(cfg + 0x20) = -(0.2f * (f32)sign - val) / 0.8f;
    }

    val = *(f32*)(cfg + 0x24);
    if (val > -0.2f && val < 0.2f) {
        *(f32*)(cfg + 0x24) = 0.0f;
    } else {
        if (val > 0.0f) {
            sign = 1;
        } else {
            sign = -1;
        }
        *(f32*)(cfg + 0x24) = -(0.2f * (f32)sign - val) / 0.8f;
    }

    *(f32*)(cfg + 0x30) = un_80305EB4();
    *(f32*)(cfg + 0x34) = un_80305FB8();

    val = *(f32*)(cfg + 0x30);
    if (val > -0.2f && val < 0.2f) {
        *(f32*)(cfg + 0x30) = 0.0f;
    } else {
        if (val > 0.0f) {
            sign = 1;
        } else {
            sign = -1;
        }
        *(f32*)(cfg + 0x30) = -(0.2f * (f32)sign - val) / 0.8f;
    }

    val = *(f32*)(cfg + 0x34);
    if (val > -0.2f && val < 0.2f) {
        *(f32*)(cfg + 0x34) = 0.0f;
    } else {
        if (val > 0.0f) {
            sign = 1;
        } else {
            sign = -1;
        }
        *(f32*)(cfg + 0x34) = -(0.2f * (f32)sign - val) / 0.8f;
    }

    if (*(s8*)(cfg + 0x74) != 0) {
        *(u8*)(cfg + 0x74) = *(u8*)(cfg + 0x74) - 1;
        return;
    }

    if (mn_8022F218() != 0) {
        lbAudioAx_80024030(0);
        mn_8022F268();
        ((TyModeState*)un_804A284C)->x4 = 1;
        return;
    }

    if (un_80305B88() & 0x1200) {
        lbAudioAx_80024030(0);
        ((TyModeState*)un_804A284C)->x4 = 1;
        return;
    }

    {
        f32 stick = *(f32*)(cfg + 0x20);
        if (stick != 0.0f) {
            *(f32*)(cfg + 0x10) = -(stick * (0.02f * fov) - *(f32*)(cfg + 0x10));
            if (*(f32*)(cfg + 0x10) < -*(f32*)(cfg + 0x1C)) {
                *(f32*)(cfg + 0x10) = -*(f32*)(cfg + 0x1C);
            }
            if (*(f32*)(cfg + 0x10) > *(f32*)(cfg + 0x1C)) {
                *(f32*)(cfg + 0x10) = *(f32*)(cfg + 0x1C);
            }
        }
    }

    {
        f32 stick = *(f32*)(cfg + 0x24);
        if (stick != 0.0f) {
            *(f32*)(cfg + 0x0C) = (stick * (0.02f * fov)) + *(f32*)(cfg + 0x0C);
            if (*(f32*)(cfg + 0x0C) < -*(f32*)(cfg + 0x18)) {
                *(f32*)(cfg + 0x0C) = -*(f32*)(cfg + 0x18);
            }
            if (*(f32*)(cfg + 0x0C) > *(f32*)(cfg + 0x18)) {
                *(f32*)(cfg + 0x0C) = *(f32*)(cfg + 0x18);
            }
        }
    }

    if (un_80305C44() & 0x424) {
        fov += *(f32*)(cfg + 0x48);
        if (fov > *(f32*)(cfg + 0x50)) {
            fov = *(f32*)(cfg + 0x50);
        }
        HSD_CObjSetFov(cobj, fov);
    }

    if (un_80305C44() & 0x848) {
        fov -= *(f32*)(cfg + 0x48);
        if (fov < *(f32*)(cfg + 0x4C)) {
            fov = *(f32*)(cfg + 0x4C);
        }
        HSD_CObjSetFov(cobj, fov);
    }

    if (un_80305B88() & 0x100) {
        HSD_CObjSetInterest(cobj, (Vec3*)(cfg + 0x5C));
        HSD_CObjSetFov(cobj, *(f32*)(cfg + 0x44));
        *(f32*)(cfg + 0x10) = 0.0f;
        *(f32*)(cfg + 0x0C) = 0.0f;
        HSD_CObjSetEyePosition(cobj, (Vec3*)(cfg + 0x68));
    }

    {
        HSD_CObj* cobj2 = (HSD_CObj*)(*(HSD_GObj**)(cfg + 0x00))->hsd_obj;
        HSD_CObjGetInterest(cobj2, &sp40);
        HSD_CObjGetEyePosition(cobj2, &sp28);
        sp34 = *(f32*)(cfg + 0x68);
        sp38 = 0.0f;
        sp3C = -500.0f;
        sp1C = 0.017453292f * *(f32*)(cfg + 0x0C);
        sp20 = 0.017453292f * *(f32*)(cfg + 0x10);
        sp24 = 0.0f;
        lbVector_ApplyEulerRotation((Vec3*)&sp34, (Vec3*)&sp1C);
        sp3C = *(f32*)(cfg + 0x64);
        HSD_CObjSetInterest(cobj2, (Vec3*)&sp34);
    }
}

void fn_8031A94C(HSD_GObj* arg0)
{
    Vec3 sp7C;
    Vec3 sp70;
    Vec3 sp5C;
    f32 sp58;
    f32 sp54;
    f32 sp50;
    Vec3 sp44;
    f32 sp40;
    f32 sp3C;
    f32 sp38;
    u8* cfg = (u8*) un_804D6F18;
    HSD_CObj* cobj = (HSD_CObj*) arg0->hsd_obj;
    HSD_JObj* trophy = ((HSD_JObj*)(*(HSD_GObj**)(cfg + 0x78))->hsd_obj)->child;
    f32 fov;
    f32 val;
    s32 sign;

    PAD_STACK(0x28);

    HSD_CObjGetInterest(cobj, &sp7C);
    HSD_CObjGetEyePosition(cobj, &sp70);
    fov = HSD_CObjGetFov(cobj);

    *(f32*)(cfg + 0x20) = un_80305D00();
    *(f32*)(cfg + 0x24) = un_80305DB0();

    val = *(f32*)(cfg + 0x20);
    if (val > -0.2f && val < 0.2f) {
        *(f32*)(cfg + 0x20) = 0.0f;
    } else {
        if (val > 0.0f) sign = 1; else sign = -1;
        *(f32*)(cfg + 0x20) = -(0.2f * (f32)sign - val) / 0.8f;
    }

    val = *(f32*)(cfg + 0x24);
    if (val > -0.2f && val < 0.2f) {
        *(f32*)(cfg + 0x24) = 0.0f;
    } else {
        if (val > 0.0f) sign = 1; else sign = -1;
        *(f32*)(cfg + 0x24) = -(0.2f * (f32)sign - val) / 0.8f;
    }

    *(f32*)(cfg + 0x30) = un_80305EB4();
    *(f32*)(cfg + 0x34) = un_80305FB8();

    val = *(f32*)(cfg + 0x30);
    if (val > -0.2f && val < 0.2f) {
        *(f32*)(cfg + 0x30) = 0.0f;
    } else {
        if (val > 0.0f) sign = 1; else sign = -1;
        *(f32*)(cfg + 0x30) = -(0.2f * (f32)sign - val) / 0.8f;
    }

    val = *(f32*)(cfg + 0x34);
    if (val > -0.2f && val < 0.2f) {
        *(f32*)(cfg + 0x34) = 0.0f;
    } else {
        if (val > 0.0f) sign = 1; else sign = -1;
        *(f32*)(cfg + 0x34) = -(0.2f * (f32)sign - val) / 0.8f;
    }

    if (*(s8*)(cfg + 0x74) != 0) {
        *(u8*)(cfg + 0x74) = *(u8*)(cfg + 0x74) - 1;
        return;
    }

    if (un_80305C44() & 0x200) {
        un_804D6F28 += 1;
        if (un_804D6F28 > 0x78) {
            lbAudioAx_80024030(0);
            ((TyModeState*)un_804A284C)->x4 = 1;
        }
    } else {
        un_804D6F28 = 0;
        if ((un_80305C44() & 0x100 && *(f32*)(cfg + 0x20) < -0.8f) || (un_80305B88() & 1)) {
            HSD_JObjAddTranslationX(trophy, -0.01f);
            un_8031BA78(*(s32*)(cfg + 0x7C), 0, HSD_JObjGetTranslationX(trophy));
        }
        if ((un_80305C44() & 0x100 && *(f32*)(cfg + 0x20) > 0.8f) || (un_80305B88() & 2)) {
            HSD_JObjAddTranslationX(trophy, 0.01f);
            un_8031BA78(*(s32*)(cfg + 0x7C), 0, HSD_JObjGetTranslationX(trophy));
        }
        if ((un_80305C44() & 0x100 && *(f32*)(cfg + 0x24) > 0.8f) || (un_80305B88() & 8)) {
            HSD_JObjAddTranslationZ(trophy, -0.01f);
            un_8031BA78(*(s32*)(cfg + 0x7C), 2, HSD_JObjGetTranslationZ(trophy));
        }
        if ((un_80305C44() & 0x100 && *(f32*)(cfg + 0x24) < -0.8f) || (un_80305B88() & 4)) {
            HSD_JObjAddTranslationZ(trophy, 0.01f);
            un_8031BA78(*(s32*)(cfg + 0x7C), 2, HSD_JObjGetTranslationZ(trophy));
        }
        if (un_80305B88() & 0x20) {
            HSD_GObjPLink_80390228(*(HSD_GObj**)(cfg + 0x78));
            *(HSD_GObj**)(cfg + 0x78) = NULL;
            do {
                *(s32*)(cfg + 0x7C) = *(s32*)(cfg + 0x7C) + 1;
                if (*(s32*)(cfg + 0x7C) >= 0x125) {
                    *(s32*)(cfg + 0x7C) = 0;
                }
                *(HSD_GObj**)(cfg + 0x78) = un_8031BC54(*(s32*)(cfg + 0x7C));
            } while (*(HSD_GObj**)(cfg + 0x78) == NULL);
            return;
        }
        if (un_80305B88() & 0x40) {
            HSD_GObjPLink_80390228(*(HSD_GObj**)(cfg + 0x78));
            *(HSD_GObj**)(cfg + 0x78) = NULL;
            do {
                *(s32*)(cfg + 0x7C) = *(s32*)(cfg + 0x7C) - 1;
                if (*(s32*)(cfg + 0x7C) < 0) {
                    *(s32*)(cfg + 0x7C) = 0x124;
                }
                *(HSD_GObj**)(cfg + 0x78) = un_8031BC54(*(s32*)(cfg + 0x7C));
            } while (*(HSD_GObj**)(cfg + 0x78) == NULL);
            return;
        }
        if (!(un_80305C44() & 0x100)) {
            f32 stick = *(f32*)(cfg + 0x20);
            if (stick != 0.0f) {
                *(f32*)(cfg + 0x10) = -(stick * (0.02f * fov) - *(f32*)(cfg + 0x10));
                if (*(f32*)(cfg + 0x10) < -*(f32*)(cfg + 0x1C)) {
                    *(f32*)(cfg + 0x10) = -*(f32*)(cfg + 0x1C);
                }
                if (*(f32*)(cfg + 0x10) > *(f32*)(cfg + 0x1C)) {
                    *(f32*)(cfg + 0x10) = *(f32*)(cfg + 0x1C);
                }
            }
            {
                f32 stick2 = *(f32*)(cfg + 0x24);
                if (stick2 != 0.0f) {
                    *(f32*)(cfg + 0x0C) = (stick2 * (0.02f * fov)) + *(f32*)(cfg + 0x0C);
                    if (*(f32*)(cfg + 0x0C) < -*(f32*)(cfg + 0x18)) {
                        *(f32*)(cfg + 0x0C) = -*(f32*)(cfg + 0x18);
                    }
                    if (*(f32*)(cfg + 0x0C) > *(f32*)(cfg + 0x18)) {
                        *(f32*)(cfg + 0x0C) = *(f32*)(cfg + 0x18);
                    }
                }
            }
        }
        if (*(f32*)(cfg + 0x34) > 0.8f) {
            sp70.y += 1.0f;
            HSD_CObjSetEyePosition(cobj, &sp70);
        }
        if (*(f32*)(cfg + 0x34) < -0.8f) {
            sp70.y -= 1.0f;
            HSD_CObjSetEyePosition(cobj, &sp70);
        }
        if (un_80305C44() & 0x400) {
            fov += *(f32*)(cfg + 0x48);
            if (fov > *(f32*)(cfg + 0x50)) {
                fov = *(f32*)(cfg + 0x50);
            }
            HSD_CObjSetFov(cobj, fov);
        }
        if (un_80305C44() & 0x800) {
            fov -= *(f32*)(cfg + 0x48);
            if (fov < *(f32*)(cfg + 0x4C)) {
                fov = *(f32*)(cfg + 0x4C);
            }
            HSD_CObjSetFov(cobj, fov);
        }
        if (un_80305B88() & 0x1000) {
            HSD_CObjSetInterest(cobj, (Vec3*)(cfg + 0x5C));
            HSD_CObjSetFov(cobj, *(f32*)(cfg + 0x44));
            *(f32*)(cfg + 0x10) = 0.0f;
            *(f32*)(cfg + 0x0C) = 0.0f;
            HSD_CObjSetEyePosition(cobj, (Vec3*)(cfg + 0x68));
        }
        {
            HSD_CObj* cobj2 = (HSD_CObj*)(*(HSD_GObj**)(cfg + 0x00))->hsd_obj;
            HSD_CObjGetInterest(cobj2, &sp5C);
            HSD_CObjGetEyePosition(cobj2, &sp44);
            sp50 = *(f32*)(cfg + 0x68);
            sp54 = 0.0f;
            sp58 = -500.0f;
            sp38 = 0.017453292f * *(f32*)(cfg + 0x0C);
            sp3C = 0.017453292f * *(f32*)(cfg + 0x10);
            sp40 = 0.0f;
            lbVector_ApplyEulerRotation((Vec3*)&sp50, (Vec3*)&sp38);
            sp58 = *(f32*)(cfg + 0x64);
            HSD_CObjSetInterest(cobj2, (Vec3*)&sp50);
        }
    }
}

/// #un_8031B1FC

static char un_804D5AA8[] = "0";
static u16 un_804D5ABC = 0x15;

void un_8031B1FC(void)
{
    TyDspBgData* ptr = un_804D6F1C;
    HSD_GObj* gobj;
    HSD_Joint* joint;
    HSD_JObj* jobj;

    PAD_STACK(0x18);

    if (ptr->archive == NULL) {
        OSReport("*** BG data aren't being loaded!\n");
        __assert("tydisplay.c", 0x3FD, un_804D5AA8);
    }

    gobj = ptr->gobj0;
    if (gobj != NULL) {
        HSD_GObjPLink_80390228(gobj);
        ptr->gobj0 = NULL;
    }

    gobj = ptr->gobj4;
    if (gobj != NULL) {
        HSD_GObjPLink_80390228(gobj);
        ptr->gobj4 = NULL;
    }

    joint = HSD_ArchiveGetPublicAddress(ptr->archive,
                                        "ToyDspBg_Top_joint");
    if (joint != NULL) {
        ptr->gobj4 = GObj_Create(9, 9, 0);
        jobj = HSD_JObjLoadJoint(joint);
        HSD_GObjObject_80390A70(ptr->gobj4, HSD_GObj_804D7849, jobj);
        GObj_SetupGXLink(ptr->gobj4, HSD_GObj_JObjCallback, 0x3C, 0);
        lb_8001204C(jobj, &ptr->jobj, &un_804D5ABC, 1);
        return;
    }

    OSReport("*** Can not Load Panel Label(%s)\n",
             "ToyDspBg_Top_joint");
    __assert("tydisplay.c", 0x43E, un_804D5AA8);
}

/// #un_8031B328

static s32 un_804DE018 = (s32) 0xC8C8C8FF;
static f32 un_804DE01C = 0.6f;

void un_8031B328(void)
{
    TyDspBgData* ptr = un_804D6F1C;
    TyDspSceneGfx* scene = (TyDspSceneGfx*) un_804D6ED4;
    HSD_LObj* lobj;
    void* lightData;
    HSD_FogDesc* fogDesc;

    PAD_STACK(24);






    if (ptr->archive == NULL) {
        OSReport("*** BG data aren't being loaded!\n");
        OSPanic("tydisplay.c", 0x459, un_804D5AC0);
    }

    lightData = HSD_ArchiveGetPublicAddress(ptr->archive,
                                            "ScMenDisplay_scene_lights");
    if (lightData != NULL) {
        scene->x00 = GObj_Create(2, 3, 0);
        lobj = un_80306EEC(lightData, 0);
        HSD_GObjObject_80390A70(scene->x00,
                                HSD_GObj_804D784A, lobj);
        GObj_SetupGXLink(scene->x00,
                         HSD_GObj_LObjCallback, 0x34, 0);
    }

    if (un_804D6F20 != 0) {
        HSD_LObjSetColor(lobj, *(GXColor*) &un_804DE018);
    }

    fogDesc = HSD_ArchiveGetPublicAddress(ptr->archive,
                                          "ScMenDisplay_fog");
    if (fogDesc != NULL) {
        scene->x08 = GObj_Create(3, 4, 0);
        HSD_GObjObject_80390A70(scene->x08,
                                HSD_GObj_804D7848,
                                HSD_FogLoadDesc(fogDesc));
        GObj_SetupGXLink(scene->x08,
                         un_80306930, 0x35, 0);
    }
}

static char un_803FEFF0[] = "ToyDspPanel_Top_joint";

void un_8031B460_OnEnter(void* arg0)
{
    s32 sp18;
    HSD_GObj** gobj_arr;
    u8* scene;
    u8* base;
    HSD_CObj* cobj;
    HSD_GObj* gobj;
    int i;
    char* strbase = (char*) un_803FEFF0;
    PAD_STACK(8);

    un_804D6F10 = HSD_MemAlloc(0x4B0);
    un_804D6F14 = HSD_MemAlloc(0x12E4);
    un_804D6F18 = HSD_MemAlloc(0x80);
    un_804D6F1C = HSD_MemAlloc(0x108);
    un_804D6ED4 = HSD_MemAlloc(0xE4);

    gobj_arr = un_804D6F18;
    scene = (u8*) un_804D6F1C;
    base = un_804D6F14;

    if (un_80305C44() & 0x40) {
        *(s32*) base = 2;
    } else if (un_80305C44() & 0x20) {
        *(s32*) base = 1;
    } else if (un_80305C44() & 0x800) {
        *(s32*) base = 3;
    } else {
        *(s32*) base = 0;
    }

    un_804D6F20 = 0;
    un_804D6F2C = 0;
    un_804D6F24 = NULL;

    if ((s32) g_debugLevel >= 3 && (un_80305C44() & 0x10)) {
        un_804D6F20 = 1;
        *(s32*) ((u8*) gobj_arr + 0x7C) = 0;
    }

    un_8031263C();
    memzero(un_804D6F1C, 0x108);
    memzero(un_804D6F18, 0x80);
    memzero(un_804D6ED4, 0xE4);

    *(s32*) ((u8*) gobj_arr + 0x08) = un_80304870();

    if ((s32) un_804D6F20 != 0) {
        *(s32*) ((u8*) gobj_arr + 0x08) = 1;
        un_8031C1D0();
    }

    {
        s32 mode = *(s32*) base;
        if (mode >= 2) goto check_high;
        if (mode >= 0) goto case01;
        goto grid_done;

    check_high:
        if (mode >= 4) goto grid_done;
        goto case23;

    case01:
        {
            s32 count = *(s32*) ((u8*) gobj_arr + 0x08);
            s32 toggle = 0;
            u8 r;
            *(u8*) ((u8*) gobj_arr + 0x75) = 1;
            *(u8*) ((u8*) gobj_arr + 0x76) = 1;
            goto check_grid1;
        loop1:
            toggle ^= 1;
            if (toggle != 0 && (s8) r < 0x14) {
                *(u8*) ((u8*) gobj_arr + 0x75) =
                    (u8)(*(u8*) ((u8*) gobj_arr + 0x75) + 1);
            } else {
                *(u8*) ((u8*) gobj_arr + 0x76) =
                    (u8)(*(u8*) ((u8*) gobj_arr + 0x76) + 1);
            }
        check_grid1:
            r = *(u8*) ((u8*) gobj_arr + 0x75);
            if ((s8) r *
                    (s8) *(u8*) ((u8*) gobj_arr + 0x76) < count)
            {
                goto loop1;
            }
            *(u8*) ((u8*) gobj_arr + 0x75) = (u8)(r + 1);
            *(u8*) ((u8*) gobj_arr + 0x76) =
                (u8)(*(u8*) ((u8*) gobj_arr + 0x76) + 1);
        }
        goto grid_done;

    case23:
        {
            s32 count = *(s32*) ((u8*) gobj_arr + 0x08);
            s32 toggle = 0;
            u8 r;
            *(u8*) ((u8*) gobj_arr + 0x75) = 1;
            *(u8*) ((u8*) gobj_arr + 0x76) = 1;
            goto check_grid2;
        loop2:
            toggle ^= 1;
            if (toggle != 0 && (s8) r < 0x14) {
                *(u8*) ((u8*) gobj_arr + 0x75) =
                    (u8)(*(u8*) ((u8*) gobj_arr + 0x75) + 1);
            } else {
                *(u8*) ((u8*) gobj_arr + 0x76) =
                    (u8)(*(u8*) ((u8*) gobj_arr + 0x76) + 1);
            }
        check_grid2:
            r = *(u8*) ((u8*) gobj_arr + 0x75);
            if ((s8) r *
                    (s8) *(u8*) ((u8*) gobj_arr + 0x76) < count)
            {
                goto loop2;
            }
        }

    grid_done:;
    }

    {
        s32 jp = lbLang_IsSavedLanguageJP();
        char* archname;
        if (jp != 0) {
            archname = strbase + 0xA8;
        } else {
            archname = strbase + 0xB8;
        }
        *(HSD_Archive**) (scene + 0x4C) =
            lbArchive_80016DBC(archname, &sp18, strbase + 0x18, 0);
    }

    {
        u8* ptr = scene;
        i = 0;
        do {
            s32 ret = un_8031BBF4((s8) i);
            *(HSD_Archive**) (ptr + 0x50) =
                lbArchive_LoadSymbols((char*) ret, NULL);
            i += 1;
            ptr += 4;
        } while (i < 0x2B);
    }

    *(s16*) (scene + 0x104) = 0;

    {
        HSD_GObj** arr2 = un_804D6F18;
        cobj = lb_80013B14(HSD_ArchiveGetPublicAddress(
            *(HSD_Archive**) ((u8*) un_804D6F1C + 0x4C),
            strbase + 0x18C));

        arr2[0] = GObj_Create(1, 2, 0);
        HSD_GObjObject_80390A70(arr2[0], HSD_GObj_804D784B, cobj);
        GObj_SetupGXLinkMax(arr2[0], (GObj_RenderFunc) un_803068E0, 0);

        gobj = arr2[0];
        *(s32*) ((u8*) gobj + 0x24) = 0;
        *(s32*) ((u8*) gobj + 0x20) = 0x12300000;

        if ((s32) un_804D6F20 != 0) {
            HSD_GObj_SetupProc(arr2[0], (HSD_GObjEvent) fn_8031A94C, 0);
        } else {
            HSD_GObj_SetupProc(arr2[0], (HSD_GObjEvent) fn_8031A4EC, 0);
        }
        HSD_GObj_80390CD4(arr2[0]);
    }

    un_8031B328();
    un_8031B1FC();

    if ((s32) un_804D6F20 != 0) {
        memzero(base, 0x12E4);
        *(f32*) (base + 0x08) = -3.5f;
        *(f32*) (base + 0x04) = -3.5f;
        *(f32*) (base + 0x10) = 3.5f;
        *(f32*) (base + 0x0C) = 3.5f;
        *(HSD_GObj**) ((u8*) gobj_arr + 0x78) =
            un_8031BC54(*(s32*) ((u8*) gobj_arr + 0x7C));
    } else {
        s32 m = *(s32*) base;
        switch (m) {
        case 0:
        case 1:
            un_80318CB4(m);
            break;
        case 2:
            un_80319540(HSD_Randi(2));
            break;
        case 3:
            un_80319994(HSD_Randi(2));
            break;
        }
    }

    un_80319EF0();
}

/// #un_8031B850

void un_8031B850(void)
{
    ToyAnimState* anim = &un_804A2AA8;
    TyDspBgData* ptr = un_804D6F1C;
    HSD_GObj** pgobj = un_804D6F18;
    TyDspSceneGfx* scene = (TyDspSceneGfx*) un_804D6ED4;
    HSD_GObj* gobj;

    if (ptr->archive != NULL) {
        ptr->archive = NULL;
    }

    if (un_804D6EC8 != NULL) {
        un_804D6EC8 = NULL;
    }

    if (anim->gobj != NULL) {
        anim->gobj = NULL;
        anim->jobj[1] = NULL;
        anim->jobj[0] = NULL;
    }

    if (ptr->gobj0 != NULL) {
        ptr->gobj0 = NULL;
    }

    if (ptr->gobj4 != NULL) {
        ptr->gobj4 = NULL;
    }

    if (scene->x00 != NULL) {
        scene->x00 = NULL;
    }

    if (scene->x04 != NULL) {
        scene->x04 = NULL;
    }

    if (scene->x08 != NULL) {
        scene->x08 = NULL;
    }

    gobj = *pgobj;
    if (gobj != NULL) {
        HSD_GObjProc_8038FED4(gobj);
        *pgobj = NULL;
    }

    if (un_804D6F2C != NULL) {
        if (*(HSD_Archive**)(un_804A2DD0 + 0x14) != NULL) {
            lbArchive_80016EFC(*(HSD_Archive**)(un_804A2DD0 + 0x14));
            *(HSD_Archive**)(un_804A2DD0 + 0x14) = NULL;
        }
        HSD_GObjPLink_80390228(un_804D6F2C);
        un_804D6F2C = NULL;
    }

    if (un_804D6F24 != NULL) {
        DevText_Remove(&un_804D6F24);
        un_804D6F24 = NULL;
    }
}

void un_8031B9A4_OnFrame(void)
{
    TyModeState* state = (TyModeState*) un_804A284C;

    if (state->x4 != 0) {
        un_8031B850();
        gm_801A4B60();
    }
}

void* un_8031B9DC(s32 id)
{
    s32* p;
    s32 val;
    bool found = false;

    if (lbLang_IsSettingUS()) {
        p = un_804D6EAC;
        while (val = *p, val != -1) {
            if (val == id) {
                found = true;
                break;
            }
            p = (s32*) ((u8*) p + 0x10);
        }
    }

    if (!found) {
        p = un_804D6EB0;
        while (val = *p, val != -1) {
            if (val == id) {
                break;
            }
            p = (s32*) ((u8*) p + 0x10);
        }
    }

    return p;
}

static char un_803FF19C[] = "X  %3.2f\nZ  %3.2f";
static f32 un_804DE020 = 12.0f;
static s32 un_804DE024 = (s32) 0xE2E2E2FF;
static s32 un_804DE028 = (s32) 0x4080D060;
static f32 un_804DE02C = 18.0f;
static f64 un_804DE030 = 0.0;

/// #un_8031BA78
void un_8031BA78(s32 arg0, s32 arg1, f32 farg0)
{
    char buf[24];
    TyDspEntry* data;

    data = (TyDspEntry*) un_8031B9DC(arg0);
    switch (arg1) {
    case 1:
        break;
    case 0:
        data->x08 = farg0;
        break;
    case 2:
        data->x0C = farg0;
        break;
    }
    if (un_804D6F24 != NULL) {
        DevText_Erase(un_804D6F24);
        DevText_SetCursorXY(un_804D6F24, 0, 0);
        sprintf(buf, un_803FF19C, data->x08, data->x0C);
        DevText_Print(un_804D6F24, buf);
    }
}

s32 un_8031BB34(s8 idx)
{
    char* table[] = {
        "ToyDspQues_Top_joint",       "ToyDspMycharaCmA_Top_joint",
        "ToyDspMycharaCmB_Top_joint", "ToyDspMycharaCmC_Top_joint",
        "ToyDspMycharaCmD_Top_joint", "ToyDspMycharaCmE_Top_joint",
        "ToyDspMycharaR1A_Top_joint", "ToyDspMycharaR1B_Top_joint",
        "ToyDspMycharaR1C_Top_joint", "ToyDspMycharaR1D_Top_joint",
        "ToyDspMycharaR1E_Top_joint", "ToyDspMycharaR2A_Top_joint",
        "ToyDspMycharaR2B_Top_joint", "ToyDspMycharaR2C_Top_joint",
        "ToyDspMycharaR2D_Top_joint", "ToyDspMycharaR2E_Top_joint",
        "ToyDspMapA_Top_joint",       "ToyDspMapB_Top_joint",
        "ToyDspMapC_Top_joint",       "ToyDspMapD_Top_joint",
        "ToyDspMapE_Top_joint",       "ToyDspFgseriesA_Top_joint",
        "ToyDspFgseriesB_Top_joint",  "ToyDspFgseriesC_Top_joint",
        "ToyDspFgseriesD_Top_joint",  "ToyDspFgseriesE_Top_joint",
        "ToyDspFgetcA_Top_joint",     "ToyDspFgetcB_Top_joint",
        "ToyDspFgetcC_Top_joint",     "ToyDspFgetcD_Top_joint",
        "ToyDspFgetcE_Top_joint",     "ToyDspPokemonA_Top_joint",
        "ToyDspPokemonB_Top_joint",   "ToyDspPokemonC_Top_joint",
        "ToyDspPokemonD_Top_joint",   "ToyDspPokemonE_Top_joint",
        "ToyDspItemA_Top_joint",      "ToyDspItemB_Top_joint",
        "ToyDspItemC_Top_joint",      "ToyDspItemD_Top_joint",
        "ToyDspItemE_Top_joint",      "ToyDspStand_Top_joint",
        "ToyDspQues_Top_joint",
    };

    if (idx == -1) {
        idx = 0;
    }

    return (s32) table[idx];
}

char* un_8031BB94(s8 idx)
{
    char* table[] = {
        un_804D5AC0,
        "ToyDspMycharaCmA_Top_matanim_joint",
        "ToyDspMycharaCmB_Top_matanim_joint",
        "ToyDspMycharaCmC_Top_matanim_joint",
        "ToyDspMycharaCmD_Top_matanim_joint",
        "ToyDspMycharaCmE_Top_matanim_joint",
        "ToyDspMycharaR1A_Top_matanim_joint",
        "ToyDspMycharaR1B_Top_matanim_joint",
        "ToyDspMycharaR1C_Top_matanim_joint",
        "ToyDspMycharaR1D_Top_matanim_joint",
        "ToyDspMycharaR1E_Top_matanim_joint",
        "ToyDspMycharaR2A_Top_matanim_joint",
        "ToyDspMycharaR2B_Top_matanim_joint",
        "ToyDspMycharaR2C_Top_matanim_joint",
        "ToyDspMycharaR2D_Top_matanim_joint",
        "ToyDspMycharaR2E_Top_matanim_joint",
        "ToyDspMapA_Top_matanim_joint",
        "ToyDspMapB_Top_matanim_joint",
        "ToyDspMapC_Top_matanim_joint",
        "ToyDspMapD_Top_matanim_joint",
        "ToyDspMapE_Top_matanim_joint",
        "ToyDspFgseriesA_Top_matanim_joint",
        "ToyDspFgseriesB_Top_matanim_joint",
        "ToyDspFgseriesC_Top_matanim_joint",
        "ToyDspFgseriesD_Top_matanim_joint",
        "ToyDspFgseriesE_Top_matanim_joint",
        "ToyDspFgetcA_Top_matanim_joint",
        "ToyDspFgetcB_Top_matanim_joint",
        "ToyDspFgetcC_Top_matanim_joint",
        "ToyDspFgetcD_Top_matanim_joint",
        "ToyDspFgetcE_Top_matanim_joint",
        "ToyDspPokemonA_Top_matanim_joint",
        "ToyDspPokemonB_Top_matanim_joint",
        "ToyDspPokemonC_Top_matanim_joint",
        "ToyDspPokemonD_Top_matanim_joint",
        "ToyDspPokemonE_Top_matanim_joint",
        "ToyDspItemA_Top_matanim_joint",
        "ToyDspItemB_Top_matanim_joint",
        "ToyDspItemC_Top_matanim_joint",
        "ToyDspItemD_Top_matanim_joint",
        "ToyDspItemE_Top_matanim_joint",
        un_804D5AC0,
        un_804D5AC0,
    };

    if (idx == -1) {
        idx = 0;
    }

    return table[idx];
}

s32 un_8031BBF4(s8 arg0)
{
    char* table[] = {
        "TyQuesD.dat",  "TyMycCmA.dat", "TyMycCmB.dat", "TyMycCmC.dat",
        "TyMycCmD.dat", "TyMycCmE.dat", "TyMycR1A.dat", "TyMycR1B.dat",
        "TyMycR1C.dat", "TyMycR1D.dat", "TyMycR1E.dat", "TyMycR2A.dat",
        "TyMycR2B.dat", "TyMycR2C.dat", "TyMycR2D.dat", "TyMycR2E.dat",
        "TyMapA.dat",   "TyMapB.dat",   "TyMapC.dat",   "TyMapD.dat",
        "TyMapE.dat",   "TySeriA.dat",  "TySeriB.dat",  "TySeriC.dat",
        "TySeriD.dat",  "TySeriE.dat",  "TyEtcA.dat",   "TyEtcB.dat",
        "TyEtcC.dat",   "TyEtcD.dat",   "TyEtcE.dat",   "TyPokeA.dat",
        "TyPokeB.dat",  "TyPokeC.dat",  "TyPokeD.dat",  "TyPokeE.dat",
        "TyItemA.dat",  "TyItemB.dat",  "TyItemC.dat",  "TyItemD.dat",
        "TyItemE.dat",  "TyStandD.dat", "TyQuesD.dat",
    };
    if (arg0 == -1) {
        arg0 = 0;
    }
    return (s32) table[arg0];
}

static char un_803FF01C[] = "ToyDspStand_Top_joint";

HSD_GObj* un_8031BC54(s32 arg0)
{
    char buf[44];
    TyDspArchNames jobj_names;
    TyDspArchNames matanim_names;
    u8* entry;
    HSD_GObj* gobj;
    HSD_JObj* root;
    HSD_JObj* child;
    u8 cat;
    u8 c;
    TyDspBgData* data = un_804D6F1C;

    entry = (u8*) un_8031B9DC(arg0);
    gobj = GObj_Create(6, 7, 0);
    root = HSD_JObjAlloc();
    HSD_GObjObject_80390A70(gobj, HSD_GObj_804D7849, root);
    GObj_SetupGXLink(gobj, HSD_GObj_JObjCallback, 0x3C, 0);

    c = entry[4];
    jobj_names = *(TyDspArchNames*) un_803B8988.jobj_names;
    cat = c;
    if ((s8) c == -1) {
        cat = 0;
    }
    child = HSD_JObjLoadJoint(
        HSD_ArchiveGetPublicAddress(
            *(HSD_Archive**) ((u8*) data + c * 4 + 0x50),
            jobj_names.entries[(s8) cat]));
    HSD_JObjAddChild(root, child);

    c = entry[4];
    matanim_names = un_803B8A34;
    cat = c;
    if ((s8) c == -1) {
        cat = 0;
    }
    un_80306A48(child, NULL,
                (char*) matanim_names.entries[(s8) cat],
                NULL,
                *(HSD_Archive**) ((u8*) data + c * 4 + 0x50),
                (long) entry[5]);
    HSD_JObjRemoveAnimAll(child);

    HSD_JObjSetTranslateX(child, *(f32*) (entry + 8));
    HSD_JObjSetTranslateZ(child, *(f32*) (entry + 0xC));

    HSD_JObjAddChild(root, HSD_JObjLoadJoint(
        HSD_ArchiveGetPublicAddress(
            *(HSD_Archive**) ((u8*) data + 0xF4),
            un_803FF01C)));

    if (un_804D6F24 != NULL) {
        DevText_Erase(un_804D6F24);
        DevText_SetCursorXY(un_804D6F24, 0, 0);
        sprintf(buf, un_803FF19C,
                *(f32*) (entry + 8), *(f32*) (entry + 0xC));
        DevText_Print(un_804D6F24, buf);
        un_8031BF34(arg0);
    }

    return gobj;
}

static char un_804D5AAC[] = "jobj.h";
static char un_804D5AB4[] = "jobj";

void un_8031BF34(s32 arg0)
{
    u8* base = (u8*) &un_804A2D98;
    ToyAnimState* anim = &un_804A2AA8;
    HSD_JObj* jobj;

    PAD_STACK(8);

    if (un_804D6F2C != NULL) {
        HSD_Archive** archp = (HSD_Archive**) (base + 0x4C);
        HSD_Archive* arch = *archp;
        if (arch != NULL) {
            lbArchive_80016EFC(arch);
            *archp = NULL;
        }
    }

    un_80308250(base + 0x38, (s16) arg0, 0);
    un_804D6F2C = un_803087F4(base + 0x38);

    HSD_JObjClearFlagsAll(anim->jobj[0], 0x10);
    HSD_JObjSetFlagsAll(anim->jobj[1], 0x10);
    HSD_JObjClearFlagsAll(anim->jobj[0], 0x10);

    jobj = (HSD_JObj*) un_804D6F2C->hsd_obj;

    HSD_JObjSetScaleX(jobj, 0.6f);
    HSD_JObjSetScaleY(jobj, 0.6f);
    HSD_JObjSetScaleZ(jobj, 0.6f);
    HSD_JObjAddTranslationX(jobj, 12.0f);
}

/// #un_8031C1D0
void un_8031C1D0(void)
{
    s32 savedColor;
    s32 bgColor;
    char buf[28];
    HSD_GObj* gobj;

    savedColor = un_804DE024;
    un_804D6F24 = DevText_Create(1, 0x28, 0x28, 9, 3, un_804A2D98);
    if (un_804D6F24 != NULL) {
        gobj = DevText_GetGObj();
        bgColor = un_804DE028;
        DevText_Show(gobj, un_804D6F24);
        DevText_HideCursor(un_804D6F24);
        DevText_80302AC0(un_804D6F24);
        DevText_SetBGColor(un_804D6F24, *(GXColor*) &bgColor);
        DevText_SetScale(un_804D6F24, un_804DE020, un_804DE02C);
        DevText_Erase(un_804D6F24);
        DevText_SetCursorXY(un_804D6F24, 0, 0);
        DevText_StoreColorIndex(un_804D6F24, 0);
        DevText_SetTextColor(un_804D6F24, *(GXColor*) &savedColor);
        sprintf(buf, un_803FF19C, un_804DE030, un_804DE030);
        DevText_Print(un_804D6F24, buf);
    }
}

void tyDisplay_8031C2CC(void)
{
    un_803124BC();
}

s32 tyDisplay_8031C2EC(void)
{
    if (un_80304B0C(5) != 0) {
        if (HSD_Randi(2) == 0) {
            return un_80305058(2, 5, 1, 65.0f);
        }
    }
    return un_80305058(2, 0, 1, 60.0f);
}

s32 un_8031C354(s32 id, s32 (*buf)[], s32 max, s32 kind)
{
    void* data;
    void* other;
    s32 i;
    s32 count;
    s32 val;


    if (id == -1) {
        return 0;
    }

    data = un_8031B9DC(id);

    if (kind == 99) {
        kind = (s32) un_803060BC(id, 6);
    }

    count = 0;
    for (i = 0; i < 0x125; i++) {
        if (i == id) {
            continue;
        }
        if (un_80304CC8(i) == 0) {
            continue;
        }
        if (un_803049F4(i) == 0) {
            continue;
        }
        other = un_8031B9DC(i);
        val = (s32) un_803060BC(i, 6);
        if (((u8*) other)[4] != ((u8*) data)[4]) {
            continue;
        }
        if (val != kind) {
            continue;
        }
        count++;
        (*buf)[0] = i;
        buf = (s32(*)[])((u8*) buf + 4);
        if (count >= max) {
            break;
        }
    }

    return count;
}

s32 un_8031C454(s32 arg0)
{
    TyDspArchNames names1;
    TyDspArchNames names2;
    TyDspArchNames names3;
    TyDspEntry* entry;
    u8 idx;
    s32 result;
    s32* archArr;
    const TyDspNameTables* tables;

    PAD_STACK(16);
    result = 0;
    archArr = un_804A2DE8;
    tables = &un_803B8988;

    un_803124BC();

    if (arg0 == -1) {
        return -1;
    }

    entry = (TyDspEntry*) un_8031B9DC(arg0);
    idx = entry->x04;

    if ((u32) archArr[idx] == 0U) {
        names1 = tables->arch_names;
        if ((s8) idx == -1) {
            idx = 0;
        }
        archArr[entry->x04] =
            (s32) lbArchive_LoadSymbols(names1.entries[(s8) idx], NULL);
    } else {
        result = 1;
    }

    if ((HSD_Archive*) archArr[42] == NULL) {
        names2 = tables->arch_names;
        archArr[42] =
            (s32) lbArchive_LoadSymbols(names2.entries[42], NULL);
    }

    if ((HSD_Archive*) archArr[41] == NULL) {
        names3 = tables->arch_names;
        archArr[41] =
            (s32) lbArchive_LoadSymbols(names3.entries[41], NULL);
    }

    return result;
}

HSD_JObj* un_8031C5E4(s32 arg0)
{
    TyDspArchNames jobj_names1;
    TyDspArchNames matanim_names1;
    TyDspArchNames jobj_names2;
    TyDspArchNames jobj_names3;
    u8* entry;
    HSD_JObj* root;
    HSD_JObj* child;
    u8 cat;
    const TyDspNameTables* tables = &un_803B8988;
    s32* archives = un_804A2DE8;

    PAD_STACK(16);

    entry = (u8*) un_8031B9DC(arg0);

    if ((u32) archives[entry[4]] == 0U) {
        return NULL;
    }

    root = HSD_JObjAlloc();

    {
        u8 c = entry[4];
        jobj_names1 = *(TyDspArchNames*) tables->jobj_names;
        cat = c;
        if ((s8) c == -1) {
            cat = 0;
        }
        child = HSD_JObjLoadJoint(
            HSD_ArchiveGetPublicAddress(
                (HSD_Archive*) archives[c],
                jobj_names1.entries[(s8) cat]));
        HSD_JObjAddChild(root, child);
    }

    {
        u8 c = entry[4];
        matanim_names1 = *(TyDspArchNames*) tables->matanim_names;
        cat = c;
        if ((s8) c == -1) {
            cat = 0;
        }
        un_80306A48(child, NULL,
                    (char*) matanim_names1.entries[(s8) cat],
                    NULL,
                    (HSD_Archive*) archives[c],
                    (long) entry[5]);
    }
    HSD_JObjRemoveAnimAll(child);

    HSD_JObjSetTranslateX(child, *(f32*) (entry + 8));
    HSD_JObjSetTranslateZ(child, *(f32*) (entry + 0xC));

    jobj_names2 = *(TyDspArchNames*) tables->jobj_names;
    HSD_JObjAddChild(root, HSD_JObjLoadJoint(
        HSD_ArchiveGetPublicAddress(
            (HSD_Archive*) archives[42],
            jobj_names2.entries[42])));

    jobj_names3 = *(TyDspArchNames*) tables->jobj_names;
    HSD_JObjAddChild(root, HSD_JObjLoadJoint(
        HSD_ArchiveGetPublicAddress(
            (HSD_Archive*) archives[41],
            jobj_names3.entries[41])));

    return root;
}

/// #un_8031C8B8
void un_8031C8B8(void)
{
    s32 i;

    for (i = 0; i < 0x2B; i++) {
        un_804A2DE8[i] = 0;
    }
}
