#include "tydisplay.h"

#include "math.h"
#include "math_ppc.h" // IWYU pragma: keep
#include "placeholder.h"
#include "platform.h"
#include "stddef.h"
#include "toy.h"
#include "trigf.h" // IWYU pragma: keep

#include <placeholder.h>
#include <platform.h>

#include "baselib/archive.h"
#include "baselib/cobj.h"
#include "baselib/debug.h"
#include "baselib/dobj.h"
#include "baselib/fog.h"
#include "baselib/gobj.h"
#include "baselib/gobjgxlink.h"
#include "baselib/gobjobject.h"
#include "baselib/gobjplink.h"
#include "baselib/gobjproc.h"
#include "baselib/jobj.h"
#include "baselib/lobj.h"
#include "baselib/memory.h"
#include "baselib/mobj.h"
#include "baselib/random.h"
#include "baselib/tobj.h"
#include "baselib/wobj.h"
#include "db/db.h"
#include "dolphin/gx.h"
#include "dolphin/mtx.h"
#include "dolphin/os.h"
#include "gm/gm_1A45.h"
#include "if/textdraw.h"
#include "if/textlib.h"
#include "if/types.h"
#include "lb/lb_00B0.h"
#include "lb/lb_00CE.h"
#include "lb/lbarchive.h"
#include "lb/lbaudio_ax.h"
#include "lb/lblanguage.h"
#include "lb/lbspdisplay.h"
#include "lb/lbvector.h"
#include "melee/if/textlib.h"
#include "mn/mnmain.h"
#include "MSL/math.h"
#include "MSL/math_ppc.h"
#include "sc/types.h"
#include "ty/toy.h"
#include "ty/types.h"

/* 31830C */ static void _tyDisplay_8031830C(TySortElem*, s32, s32);
/* 318714 */ static void _tyDisplay_80318714(TySortElem*, s32, s32);
/* 318B1C */ static void _tyDisplay_80318B1C(s32 arg0);
/* 318CB4 */ static void _tyDisplay_80318CB4(s32);
/* 319540 */ static void _tyDisplay_80319540(s32);
/* 319994 */ static void _tyDisplay_80319994(s32);
/* 319EF0 */ static void _tyDisplay_80319EF0(void);
/* 31A4EC */ static void _tyDisplay_8031A4EC(HSD_GObj*);
/* 31A94C */ static void _tyDisplay_8031A94C(HSD_GObj*);
/* 31B1FC */ static void _tyDisplay_8031B1FC(void);
/* 31B328 */ static void _tyDisplay_8031B328(void);
/* 31B850 */ static void _tyDisplay_8031B850(void);
/* 31BA78 */ static void _tyDisplay_8031BA78(s32, s32, f32);
/* 31BBF4 */ static s32 _tyDisplay_8031BBF4(s8);
/* 31BC54 */ static HSD_GObj* _tyDisplay_8031BC54(s32);
/* 31BF34 */ static void _tyDisplay_8031BF34(s32 arg0);
/* 31C1D0 */ static void _tyDisplay_8031C1D0(void);
/* 4A2D98 */ static char _tyDisplay_devtext_buf[9 * (3 * 2)];
/* 4A2DD0 */ static TyDspArchiveHolder _tyDisplay_804A2DD0;
/* 4A2DE8 */ static HSD_Archive*
    _tyDisplay_804A2DE8[0xB0 / sizeof(HSD_Archive*)];
/* 4D6F10 */ static HSD_JObj** _tyDisplay_804D6F10;
/* 4D6F14 */ static TyDspGrid* _tyDisplay_804D6F14;
/* 4D6F18 */ static TyDspConfig* _tyDisplay_804D6F18;
/* 4D6F1C */ static TyDspBgData* _tyDisplay_804D6F1C;
/* 4D6F20 */ static s32 _tyDisplay_804D6F20;
/* 4D6F24 */ static DevText* _tyDisplay_804D6F24;
/* 4D6F28 */ static s32 _tyDisplay_804D6F28;
/* 4D6F2C */ static HSD_GObj* _tyDisplay_804D6F2C;

STATIC_ASSERT(sizeof(_tyDisplay_devtext_buf) == 0x36);
STATIC_ASSERT(sizeof(_tyDisplay_804A2DD0) == 0x18);

/// @todo .data order hack
static void order_data_0(void)
{
    /*  +0 */ (void) "ToyDspPanel_Top_joint";
    /* +18 */ (void) "ToyDspBg_Top_joint";
}

/// @todo Not de-duplicated in #tyDisplay_8031BB34, therefore not a literal?
static char _tyDisplay_803FF01C[] = "ToyDspStand_Top_joint";

/// @todo .data order hack
static void order_data_44(void)
{
    /* +44 */ (void) "ScMenDisplay_fog";
}

static inline void quicksort(TySortElem* base, s32 lo, s32 hi)
{
    TySortElem tmp;
    PAD_STACK(16);

    if (lo < hi) {
        s32 mid = (lo + hi) / 2;
        s32 pivot, i;

        if (lo != mid) {
            tmp = base[lo];
            base[lo] = base[mid];
            base[mid] = tmp;
        }

        pivot = lo;
        for (i = lo + 1; i <= hi; i++) {
            if (base[i].val < base[lo].val) {
                pivot++;
                if (pivot != i) {
                    tmp = base[pivot];
                    base[pivot] = base[i];
                    base[i] = tmp;
                }
            }
        }

        if (lo != pivot) {
            tmp = base[lo];
            base[lo] = base[pivot];
            base[pivot] = tmp;
        }

        if (lo < pivot - 1) {
            s32 mid2 = (pivot + lo - 1) / 2;
            s32 pivot2;

            if (lo != mid2) {
                tmp = base[lo];
                base[lo] = base[mid2];
                base[mid2] = tmp;
            }

            pivot2 = lo;
            for (i = lo + 1; i <= pivot - 1; i++) {
                if (base[i].val < base[lo].val) {
                    pivot2++;
                    if (pivot2 != i) {
                        tmp = base[pivot2];
                        base[pivot2] = base[i];
                        base[i] = tmp;
                    }
                }
            }

            if (lo != pivot2) {
                tmp = base[lo];
                base[lo] = base[pivot2];
                base[pivot2] = tmp;
            }

            _tyDisplay_8031830C(base, lo, pivot2 - 1);
            _tyDisplay_8031830C(base, pivot2 + 1, pivot - 1);
        }

        if (pivot + 1 < hi) {
            s32 mid3 = (pivot + hi + 1) / 2;
            s32 pivot3;

            if (pivot + 1 != mid3) {
                tmp = base[pivot + 1];
                base[pivot + 1] = base[mid3];
                base[mid3] = tmp;
            }

            pivot3 = pivot + 1;
            for (i = pivot + 2; i <= hi; i++) {
                if (base[i].val < base[pivot + 1].val) {
                    pivot3++;
                    if (pivot3 != i) {
                        tmp = base[pivot3];
                        base[pivot3] = base[i];
                        base[i] = tmp;
                    }
                }
            }

            if (pivot + 1 != pivot3) {
                tmp = base[pivot + 1];
                base[pivot + 1] = base[pivot3];
                base[pivot3] = tmp;
            }

            _tyDisplay_8031830C(base, pivot + 1, pivot3 - 1);
            _tyDisplay_8031830C(base, pivot3 + 1, hi);
        }
    }
}

/// @todo .sdata2 order hack
static void order_sdata2_0(void)
{
    /*  +0 */ (void) 7.0f;
    /*  +4 */ (void) 0.0f;
    /*  +8 */ (void) 0.5;
    /* +10 */ (void) 3.0;
    /* +18 */ (void) 2147483600.0f;
    /* +1C */ (void) -2147483600.0f;
    /* +20 */ (void) -3.5f;
    /* +24 */ (void) 3.5f;
    /* +28 */ (void) 9.0f;
    /* +2C */ (void) 11.0f;
    /* +30 */ (void) deg_to_rad;
    /* +34 */ (void) 2.0f;
    /* +38 */ (void) 0.1f;
    /* +3C */ (void) 0.5f;
}

void _tyDisplay_8031830C(TySortElem* base, s32 lo, s32 hi)
{
    PAD_STACK(16);
    quicksort(base, lo, hi);
}

typedef struct TySortElemInt {
    s32 key;
    s32 val;
} TySortElemInt;

void _tyDisplay_80318714(TySortElem* base_, s32 lo, s32 hi)
{
    TySortElemInt* base = (TySortElemInt*) base_;
    TySortElemInt tmp0, tmp1, tmp2, tmp3, tmp4, tmp5, tmp6, tmp7, tmp8;
    PAD_STACK(16);

    if (lo < hi) {
        s32 mid = (lo + hi) / 2;
        s32 pivot2, pivot, i;

        if (lo != mid) {
            tmp0 = base[lo];
            base[lo] = base[mid];
            base[mid] = tmp0;
        }

        pivot = lo;
        for (i = lo + 1; i <= hi; i++) {
            if (base[i].val > base[lo].val) {
                pivot++;
                if (pivot != i) {
                    tmp1 = base[pivot];
                    base[pivot] = base[i];
                    base[i] = tmp1;
                }
            }
        }

        if (lo != pivot) {
            tmp2 = base[lo];
            base[lo] = base[pivot];
            base[pivot] = tmp2;
        }

        if (lo < pivot - 1) {
            s32 mid2 = (pivot + lo - 1) / 2;

            if (lo != mid2) {
                tmp3 = base[lo];
                base[lo] = base[mid2];
                base[mid2] = tmp3;
            }

            pivot2 = lo;
            for (i = lo + 1; i <= pivot - 1; i++) {
                if (base[i].val > base[lo].val) {
                    pivot2++;
                    if (pivot2 != i) {
                        tmp4 = base[pivot2];
                        base[pivot2] = base[i];
                        base[i] = tmp4;
                    }
                }
            }

            if (lo != pivot2) {
                tmp5 = base[lo];
                base[lo] = base[pivot2];
                base[pivot2] = tmp5;
            }

            _tyDisplay_80318714(base_, lo, pivot2 - 1);
            _tyDisplay_80318714(base_, pivot2 + 1, pivot - 1);
        }

        if (pivot + 1 < hi) {
            s32 mid3 = (pivot + hi + 1) / 2;
            s32 pivot3;

            if (pivot + 1 != mid3) {
                tmp6 = base[pivot + 1];
                base[pivot + 1] = base[mid3];
                base[mid3] = tmp6;
            }

            pivot3 = pivot + 1;
            for (i = pivot + 2; i <= hi; i++) {
                if (base[i].val > base[pivot + 1].val) {
                    pivot3++;
                    if (pivot3 != i) {
                        tmp7 = base[pivot3];
                        base[pivot3] = base[i];
                        base[i] = tmp7;
                    }
                }
            }

            if (pivot + 1 != pivot3) {
                tmp8 = base[pivot + 1];
                base[pivot + 1] = base[pivot3];
                base[pivot3] = tmp8;
            }

            _tyDisplay_80318714(base_, pivot + 1, pivot3 - 1);
            _tyDisplay_80318714(base_, pivot3 + 1, hi);
        }
    }
}


void _tyDisplay_80318B1C(s32 arg0)
{
    s32 i;
    s32 start;
    s32 placed;
    TyDspGrid* grid = _tyDisplay_804D6F14;
    s32 rand_id;
    TyDspEntry* check;
    s32 rand_result;

    if (arg0 > 1) {
        rand_result = HSD_Randi(arg0 - 1);
    } else {
        rand_result = 0;
    }
    start = rand_result;

    if (arg0 > 0x125) {
        placed = 0;
        i = 0;
        while (placed < arg0) {
            if (i >= 0x125) {
                rand_id = HSD_Randi(0x124);
                check = tyDisplay_8031B9DC(rand_id);
                while (check->x00 == -1) {
                    rand_id = HSD_Randi(0x124);
                    check = tyDisplay_8031B9DC(rand_id);
                }
                grid->sort[start].key = rand_id;
                *(s32*) &grid->sort[start].val =
                    (s32) Toy_803060BC(grid->sort[start].key, 7);
                start++;
                if (start >= arg0) {
                    start = 0;
                }
                placed++;
            } else {
                check = tyDisplay_8031B9DC(i);
                if (check->x00 != -1) {
                    grid->sort[start].key = i;
                    *(s32*) &grid->sort[start].val = (s32) Toy_803060BC(i, 7);
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
            if (Toy_803048C0(i) != 0) {
                tyDisplay_8031B9DC(i);
                grid->sort[start].key = i;
                *(s32*) &grid->sort[start].val = (s32) Toy_803060BC(i, 7);
                start++;
                if (start >= arg0) {
                    start = 0;
                }
            }
            i++;
        } while (i < 0x125);
    }
}
void _tyDisplay_80318CB4(s32 arg0)
{
    s32 n2;
    TyDspGrid* grid = _tyDisplay_804D6F14;
    s32 i;
    s32 prev_ring_size;
    s32 ring_count;
    s32 ring_max;
    f32 angle;
    f32 radius;
    f32 base_step;
    f32 dist_limit;
    s32 count;
    TyDspConfig* cfg = _tyDisplay_804D6F18;
    s32 mid;
    s32 pivot;
    s32 n;

    PAD_STACK(0x48);

    memzero(grid, 0x12E4);
    grid->x08_min_z = -3.5f;
    grid->x04_min_x = -3.5f;
    grid->x10_max_z = 3.5f;
    grid->x0C_max_x = 3.5f;
    ring_count = 0;
    ring_max = 6;
    angle = 0.0f;

    if (arg0 != 0) {
        base_step = 9.0f;
    } else {
        base_step = 11.0f;
    }
    radius = base_step;
    dist_limit = 8.0f;

    for (i = 0; i < cfg->x08; i++) {
        if (i == 0) {
            grid->pos[i].x = 0.0f;
            grid->pos[i].z = 0.0f;
        } else {
            f32 rad = 0.017453292f * angle;
            grid->pos[i].x = radius * cosf(rad);
            grid->pos[i].z = radius * sinf(rad);
            if (arg0 == 0) {
                grid->pos[i].x = 2.0f * HSD_Randf() + grid->pos[i].x;
                grid->pos[i].z = 2.0f * HSD_Randf() + grid->pos[i].z;
            }
            if (HSD_Randi(3) != 0) {
                f32 theta = atan2f(grid->pos[i].z, grid->pos[i].x);
                f32 mag = sqrtf(grid->pos[i].x * grid->pos[i].x +
                                grid->pos[i].z * grid->pos[i].z);
                s32 start;
                s32 collided;
                s32 dist_limit_i;

                if (i < 0x24) {
                    start = 0;
                } else {
                    start = i - (prev_ring_size * 2 - 6);
                }

                dist_limit_i = (s32) dist_limit;
                collided = 0;
                while (collided == 0) {
                    s32 tries;
                    s32 k;
                    grid->pos[i].x = mag * cosf(theta);
                    grid->pos[i].z = mag * sinf(theta);
                    tries = (s32) (mag / 0.1f);
                    if (HSD_Randi(2) != 0) {
                        f32 half = mag * 0.5f;
                        if ((s32) half > 1) {
                            tries -= HSD_Randi((s32) half);
                        }
                    }
                    for (k = i - 1; k >= start; k--) {
                        f32 dx = grid->pos[i].x - grid->pos[k].x;
                        f32 dz = grid->pos[i].z - grid->pos[k].z;
                        f32 dist = sqrtf(dx * dx + dz * dz);
                        if (dist > 2.1474836e9f || dist < -2.1474836e9f) {
                            OSReport("*** tyDisplay Atari Irregul!\n");
                            HSD_ASSERT(0xC6, 0);
                        }
                        {
                            s32 near;
                            if ((s32) dist <= dist_limit_i) {
                                near = 1;
                            } else {
                                near = 0;
                            }
                            if (near != 0) {
                                collided = 1;
                                break;
                            }
                        }
                    }
                    if (tries == 0) {
                        break;
                    }
                    if (collided == 0) {
                        mag -= 0.1f;
                    }
                }
            }
            ring_count += 1;
            if (ring_count >= ring_max) {
                if (arg0 != 0) {
                    base_step = 9.0f;
                } else {
                    base_step = 11.0f;
                }
                radius += base_step;
                prev_ring_size = ring_max;
                ring_count = 0;
                ring_max += 6;
                angle = arg0 != 0 ? 0.0f : (f32) HSD_Randi(0x1E);
            } else {
                angle += 360.0f / (f32) ring_max;
            }
        }

        if (grid->pos[i].x < grid->x04_min_x) {
            grid->x04_min_x = grid->pos[i].x;
        }
        if (grid->pos[i].x > grid->x0C_max_x) {
            grid->x0C_max_x = grid->pos[i].x;
        }
        if (grid->pos[i].z < grid->x08_min_z) {
            grid->x08_min_z = grid->pos[i].z;
        }
        if (grid->pos[i].z > grid->x10_max_z) {
            grid->x10_max_z = grid->pos[i].z;
        }
    }

    count = cfg->x08;
    if (count > 1) {
        n2 = count - 1;
        if (n2 > 0) {
            TyDspPos tmp;
            mid = n2 / 2;

            if (mid != 0) {
                tmp = grid->pos[0];
                grid->pos[0] = grid->pos[mid];
                grid->pos[mid] = tmp;
            }

            pivot = 0;
            for (n = 1; n <= n2; n++) {
                if (grid->pos[n].z < grid->pos[0].z) {
                    pivot += 1;
                    if (pivot != n) {
                        TyDspPos* p = &grid->pos[pivot];
                        tmp = *p;
                        *p = grid->pos[n];
                        grid->pos[n] = tmp;
                    }
                }
            }

            if (pivot != 0) {
                tmp = grid->pos[0];
                grid->pos[0] = grid->pos[pivot];
                grid->pos[pivot] = tmp;
            }

            _tyDisplay_8031830C((TySortElem*) grid->pos, 0, pivot - 1);
            _tyDisplay_8031830C((TySortElem*) grid->pos, pivot + 1, n2);
        }
    }

    _tyDisplay_80318B1C(cfg->x08);

    count = cfg->x08;
    if (count > 1) {
        n2 = (count / 3) * 2;
        if (n2 > 0) {
            TySortElem tmp;
            mid = n2 / 2;

            if (mid != 0) {
                {
                    TySortElem tmp2 = grid->sort[0];
                    tmp = tmp2;
                }
                grid->sort[0] = grid->sort[mid];
                grid->sort[mid] = tmp;
            }

            pivot = 0;
            for (n = 1; n <= n2; n++) {
                if (grid->sort[n].val > grid->sort[0].val) {
                    pivot += 1;
                    if (pivot != n) {
                        TySortElem* s = &grid->sort[pivot];
                        {
                            TySortElem tmp2 = *s;
                            tmp = tmp2;
                        }
                        *s = grid->sort[n];
                        grid->sort[n] = tmp;
                    }
                }
            }

            if (pivot != 0) {
                tmp = grid->sort[0];
                grid->sort[0] = grid->sort[pivot];
                grid->sort[pivot] = tmp;
            }

            _tyDisplay_80318714(grid->sort, 0, pivot - 1);
            _tyDisplay_80318714(grid->sort, pivot + 1, n2);
        }
    }

    {
        s32 k;
        s32 posIdx = 0;
        s32 jobjIdx = 0;
        for (k = 0; k < cfg->x08; k++) {
            HSD_GObj* gobj;
            cfg->x78 = _tyDisplay_8031BC54(grid->sort[k].key);
            gobj = cfg->x78;
            if (gobj != NULL) {
                _tyDisplay_804D6F10[jobjIdx] = (HSD_JObj*) gobj->hsd_obj;
                HSD_JObjSetTranslateX(_tyDisplay_804D6F10[jobjIdx],
                                      grid->pos[posIdx].x);
                HSD_JObjSetTranslateZ(_tyDisplay_804D6F10[jobjIdx],
                                      grid->pos[posIdx].z);
                jobjIdx++;
                posIdx++;
            }
        }
    }
}

void _tyDisplay_80319540(s32 arg0)
{
    TyDspGrid* grid = _tyDisplay_804D6F14;
    TyDspConfig* cfg = _tyDisplay_804D6F18;
    s32 count;
    s32 col, row, remainder;
    s32 i;
    s32 n2;
    PAD_STACK(0x28);

    memzero(grid, 0x12E4);

    grid->x08_min_z = -3.5f;
    grid->x04_min_x = -3.5f;
    grid->x10_max_z = 3.5f;
    grid->x0C_max_x = 3.5f;

    count = cfg->x08;
    if (count <= 1) {
        remainder = 0;
    } else {
        remainder = count % (s8) cfg->x75;
    }

    col = 0;
    row = 0;
    for (i = 0; i < count; i++) {
        if (i == 0) {
            grid->pos[i].x = 0.0f;
            grid->pos[i].z = 0.0f;
        } else {
            f32 x = 9.0f * (f32) col;
            if (arg0 != 0 && (row % 2) != 0) {
                x = x + 3.5f;
            }
            grid->pos[i].x = x;
            grid->pos[i].z = 9.0f * (f32) row;
        }

        col += 1;
        if (remainder != 0) {
            remainder -= 1;
            if (remainder == 0) {
                col = 0;
                row += 1;
            }
        } else if (col >= (s8) cfg->x75) {
            col = 0;
            row += 1;
        }

        {
            f32 px = grid->pos[i].x;
            if (px < grid->x04_min_x) {
                grid->x04_min_x = px;
            }
        }
        {
            f32 px = grid->pos[i].x;
            if (px > grid->x0C_max_x) {
                grid->x0C_max_x = px;
            }
        }
        {
            f32 pz = grid->pos[i].z;
            if (pz < grid->x08_min_z) {
                grid->x08_min_z = pz;
            }
        }
        {
            f32 pz = grid->pos[i].z;
            if (pz > grid->x10_max_z) {
                grid->x10_max_z = pz;
            }
        }

        count = cfg->x08;
    }

    _tyDisplay_80318B1C(count);

    if (count > 1) {
        n2 = (count / 3) * 2;
        if (n2 > 0) {
            s32 mid = n2 / 2;
            s32 pivot, j, n;
            TySortElem tmp;
            TySortElem* sort = grid->sort;

            if (mid != 0) {
                tmp = sort[0];
                sort[0] = sort[mid];
                sort[mid] = tmp;
            }

            pivot = 0;
            j = 0;
            for (n = 1; n2 >= n; n++) {
                if (sort[n].val > sort[0].val) {
                    pivot += 1;
                    j += 8;
                    if (pivot != n) {
                        TySortElem* s = (TySortElem*) ((u8*) grid->sort + j);
                        tmp = *s;
                        *s = sort[n];
                        sort[n] = tmp;
                    }
                }
            }

            if (pivot != 0) {
                TySortElem* s = &sort[pivot];
                tmp = sort[0];
                sort[0] = *s;
                *s = tmp;
            }

            _tyDisplay_80318714(sort, 0, pivot - 1);
            _tyDisplay_80318714(sort, pivot + 1, n2);
        }
    }

    {
        s32 k;
        s32 off = 0;

        for (k = 0; k < cfg->x08; k++) {
            HSD_GObj* gobj;
            HSD_JObj** jobjArr;
            cfg->x78 = _tyDisplay_8031BC54(grid->sort[0].key);
            gobj = cfg->x78;
            if (gobj != NULL) {
                jobjArr = _tyDisplay_804D6F10;
                jobjArr[k] = (HSD_JObj*) gobj->hsd_obj;
                {
                    f32 xpos = grid->pos[k].x;
                    HSD_JObj* jobj = jobjArr[k];
                    HSD_JObjSetTranslateX(jobj, xpos);
                }
                {
                    f32 zpos = grid->pos[k].z;
                    HSD_JObj* jobj = jobjArr[k];
                    HSD_JObjSetTranslateZ(jobj, zpos);
                }
            }
            off += 4;
        }
    }
}

void _tyDisplay_80319994(s32 arg0)
{
    TyDspGrid* grid = _tyDisplay_804D6F14;
    TyDspConfig* cfg = _tyDisplay_804D6F18;
    f32 xoff = 0.0f;
    s32 n2;
    s32 pivot;
    s32 count;

    PAD_STACK(0x38);

    pivot = arg0;
    memzero(grid, 0x12E4);
    grid->x08_min_z = -3.5f;
    grid->x04_min_x = -3.5f;
    grid->x10_max_z = 3.5f;
    grid->x0C_max_x = 3.5f;

    {
        TyDspGrid* cur = grid;
        s32 ring = 1;
        s32 i = 0;
        s32 col = 0;
        s32 row = 0;

        for (; i < (count = cfg->x08); i++) {
            if (i == 0) {
                cur->pos[0].x = 0.0f;
                cur->pos[0].z = 0.0f;
            } else {
                cur->pos[0].x = 9.0f * (f32) col + xoff;
                if (pivot != 0) {
                    cur->pos[0].z = -9.0f * (f32) row;
                } else {
                    cur->pos[0].z = 9.0f * (f32) row;
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
                f32 x = cur->pos[0].x;
                if (x < grid->x04_min_x) {
                    grid->x04_min_x = x;
                }
            }
            {
                f32 x = cur->pos[0].x;
                if (x > grid->x0C_max_x) {
                    grid->x0C_max_x = x;
                }
            }
            {
                f32 z = cur->pos[0].z;
                if (z < grid->x08_min_z) {
                    grid->x08_min_z = z;
                }
            }
            {
                f32 z = cur->pos[0].z;
                if (z > grid->x10_max_z) {
                    grid->x10_max_z = z;
                }
            }
            cur = (TyDspGrid*) ((size_t) cur + sizeof(TyDspPos));
        }
    }

    {
        if (pivot != 0 && count > 1) {
            n2 = count - 1;
            if (n2 > 0) {
                TyDspPos tmp;
                s32 mid = n2 / 2;
                s32 n, j;

                if (mid != 0) {
                    tmp = grid->pos[0];
                    grid->pos[0] = grid->pos[mid];
                    grid->pos[mid] = tmp;
                }

                pivot = 0;
                j = 0;
                for (n = 1; n2 >= n; n++) {
                    if (grid->pos[n].z < grid->pos[0].z) {
                        pivot += 1;
                        j += 8;
                        if (pivot != n) {
                            TyDspPos* p = (TyDspPos*) ((size_t) grid->pos + j);
                            tmp = *p;
                            *p = grid->pos[n];
                            grid->pos[n] = tmp;
                        }
                    }
                }

                if (pivot != 0) {
                    tmp = grid->pos[0];
                    grid->pos[0] = grid->pos[pivot];
                    grid->pos[pivot] = tmp;
                }

                _tyDisplay_8031830C((TySortElem*) grid->pos, 0, pivot - 1);
                _tyDisplay_8031830C((TySortElem*) grid->pos, pivot + 1, n2);
            }
        }
    }

    _tyDisplay_80318B1C(cfg->x08);

    {
        count = cfg->x08;
        if (count > 1) {
            n2 = (count / 3) * 2;
            if (n2 > 0) {
                TySortElem tmp;
                s32 mid = n2 / 2;
                s32 n, j;

                if (mid != 0) {
                    tmp = grid->sort[0];
                    grid->sort[0] = grid->sort[mid];
                    grid->sort[mid] = tmp;
                }

                pivot = 0;
                j = 0;
                for (n = 1; n2 >= n; n++) {
                    if (*(s32*) &grid->sort[n].val >
                        *(s32*) &grid->sort[0].val)
                    {
                        pivot += 1;
                        j += 8;
                        if (pivot != n) {
                            TySortElem* s = (TySortElem*) ((size_t) grid->sort + j);
                            tmp = *s;
                            *s = grid->sort[n];
                            grid->sort[n] = tmp;
                        }
                    }
                }

                if (pivot != 0) {
                    tmp = grid->sort[0];
                    grid->sort[0] = grid->sort[pivot];
                    grid->sort[pivot] = tmp;
                }

                _tyDisplay_80318714(grid->sort, 0, pivot - 1);
                _tyDisplay_80318714(grid->sort, pivot + 1, n2);
            }
        }
    }

    {
        struct TyDspGridElemIter {
            u8 pad_sort[0x14];
            TySortElem sort;
            u8 pad_pos[0x960];
            TyDspPos pos;
        }* cur = (struct TyDspGridElemIter*) grid;
        s32 k;
        s32 off = 0;

        for (k = 0; k < cfg->x08; k++) {
            HSD_GObj* gobj;
            cfg->x78 = _tyDisplay_8031BC54(cur->sort.key);
            gobj = cfg->x78;
            if (gobj != NULL) {
                *(HSD_JObj**) ((size_t) _tyDisplay_804D6F10 + off) =
                    (HSD_JObj*) gobj->hsd_obj;
                {
                    f32 xpos = cur->pos.x;
                    HSD_JObj* jobj =
                        *(HSD_JObj**) ((size_t) _tyDisplay_804D6F10 + off);
                    HSD_JObjSetTranslateX(jobj, xpos);
                }
                {
                    f32 zpos = cur->pos.z;
                    HSD_JObj* jobj =
                        *(HSD_JObj**) ((size_t) _tyDisplay_804D6F10 + off);
                    HSD_JObjSetTranslateZ(jobj, zpos);
                }
            }
            cur = (struct TyDspGridElemIter*) ((size_t) cur + sizeof(TyDspPos));
            off += 4;
        }
    }
}

void _tyDisplay_80319EF0(void)
{
    u8 _[8];
    Vec3 interest;
    Vec3 sp28;
    Vec3 eyepos;
    TyDspGrid* grid = _tyDisplay_804D6F14;
    TyDspConfig* cfg = _tyDisplay_804D6F18;
    HSD_CObj* cobj = (HSD_CObj*) cfg->x00->hsd_obj;
    TyDspBgData* bg = _tyDisplay_804D6F1C;
    f32 range;
    f32 scale;
    PAD_STACK(16);

    range = grid->x0C_max_x;
    range -= grid->x04_min_x;
    if (range < 0.0f) {
        range = -range;
    }
    interest.x = range * 0.5f + grid->x04_min_x;
    if (grid->x00 == 3) {
        interest.x = 0.0f;
    }
    interest.y = 0.0f;
    {
        f32 zmin = grid->x08_min_z;
        f32 zrange = grid->x10_max_z;
        zrange -= zmin;
        if (zrange < 0.0f) {
            zrange = -zrange;
        }
        interest.z = zrange * 0.5f + zmin;
    }
    eyepos = interest;
    interest.z -= 10.0f;
    cfg->x5C = interest;
    HSD_CObjGetEyePosition(cobj, &sp28);
    sp28.x = eyepos.x;
    sp28.z = 500.0f + eyepos.z;
    cfg->x68 = sp28;
    HSD_CObjSetInterest(cobj, &interest);
    HSD_CObjSetEyePosition(cobj, &sp28);

    {
        f32 xrange = grid->x0C_max_x - grid->x04_min_x;
        if (xrange < 0.0f) {
            xrange = -xrange;
        }
        cfg->x40 = 14.0f + xrange;
    }
    cfg->x44 = 1.0f;

    while (500.0f * tanf(0.017453292f * (cfg->x44 * 0.5f)) < cfg->x40 * 0.5f) {
        cfg->x44 += 0.1f;
    }

    if (cfg->x44 < 3.0f) {
        cfg->x44 = 3.2f;
    }
    HSD_CObjSetFov(cobj, cfg->x44);

    cfg->x4C = (f32) cfg->x08 * 0.0033333334f + 3.0f;
    {
        f32 fov2 = cfg->x44;
        cfg->x50 = fov2 + fov2 / 5.0f;
    }
    if (cfg->x44 < 3.0f) {
        cfg->x48 = (cfg->x50 - cfg->x4C) / 30.0f;
    } else {
        cfg->x48 = (cfg->x50 - cfg->x4C) / 60.0f;
    }

    {
        s32 mode = grid->x00;
        switch (mode) {
        case 0:
        case 1:
            cfg->x54 = -((14.0f + cfg->x40) * 0.5f - cfg->x5C.x);
            cfg->x58 = (14.0f + cfg->x40) * 0.5f + cfg->x5C.x;
            break;
        case 2:
            cfg->x54 = -((7.0f + cfg->x40) * 0.5f - cfg->x5C.x);
            cfg->x58 = (7.0f + cfg->x40) * 0.5f + cfg->x5C.x;
            break;
        case 3:
            cfg->x54 = -(cfg->x40 * 0.5f - cfg->x5C.x);
            cfg->x58 = cfg->x40 * 0.5f + cfg->x5C.x;
            break;
        }
    }

    {
        f32 xdiff = cfg->x58 - cfg->x54;
        cfg->x1C = 57.29578f * lb_8000D008(xdiff * 0.5f, 500.0f);
    }
    cfg->x18 = 57.29578f * lb_8000D008(cfg->x40 * 0.5f, 500.0f);

    {
        HSD_JObjSetTranslate((HSD_JObj*) bg->gobj4->hsd_obj, &eyepos);
    }

    {
        f32 zrange = 14.0f + (grid->x10_max_z - grid->x08_min_z);
        f32 xrange = grid->x0C_max_x - grid->x04_min_x;
        scale = (f32) (cfg->x08 / 30);
        if (xrange > zrange) {
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
            HSD_ASSERT(0x28C, 0);
        }
        if ((s32) scale != 0) {
            HSD_JObjSetScaleX(bg->jobj, scale);
            HSD_JObjSetScaleZ(bg->jobj, scale);
        }
    }
}

/// @todo .data order hack
static void order_data_A8(void)
{
    /* +A8 */ (void) "TyMnDisp.dat";
    /* +B8 */ (void) "TyMnDisp.usd";
}

void _tyDisplay_8031A4EC(HSD_GObj* arg0)
{
    float zero;
    Vec3 interest;
    Vec3 eye;
    u8 _1[0x8];
    HSD_CObj* cobj = (HSD_CObj*) arg0->hsd_obj;
    TyDspConfig* cfg = _tyDisplay_804D6F18;
    f32 fov;
    f32 val;
    s32 sign;
    Vec3 interest2;
    Vec3 tempvec1;
    Vec3 eye2;
    Vec3 tempvec2;
    HSD_CObj* cobj2;
    f32 stick;
    u8 _2[0x10];

    HSD_CObjGetInterest(cobj, &interest);
    HSD_CObjGetEyePosition(cobj, &eye);
    fov = HSD_CObjGetFov(cobj);

    cfg->x20 = Toy_80305D00();
    cfg->x24 = Toy_80305DB0();

    val = cfg->x20;
    if (val > -0.2f && val < 0.2f) {
        cfg->x20 = 0.0f;
    } else {
        if (val > 0.0f) {
            sign = 1;
        } else {
            sign = -1;
        }
        cfg->x20 = -(0.2f * (f32) sign - val) / 0.8f;
    }

    zero = 0;
    val = cfg->x24;
    if (val > -0.2f && val < 0.2f) {
        cfg->x24 = 0.0f;
    } else {
        if (val > zero) {
            sign = 1;
        } else {
            sign = -1;
        }
        cfg->x24 = -(0.2f * (f32) sign - val) / 0.8f;
    }

    cfg->x30 = Toy_80305EB4();
    cfg->x34 = Toy_80305FB8();

    val = cfg->x30;
    if (val > -0.2f && val < 0.2f) {
        cfg->x30 = 0.0f;
    } else {
        if (val > 0.0f) {
            sign = 1;
        } else {
            sign = -1;
        }
        cfg->x30 = -(0.2f * (f32) sign - val) / 0.8f;
    }

    val = cfg->x34;
    if (val > -0.2f && val < 0.2f) {
        cfg->x34 = 0.0f;
    } else {
        if (val > 0.0f) {
            sign = 1;
        } else {
            sign = -1;
        }
        cfg->x34 = -(0.2f * (f32) sign - val) / 0.8f;
    }

    if (cfg->x74 != 0) {
        cfg->x74 = cfg->x74 - 1;
        return;
    }

    if (mn_8022F218() != 0) {
        lbAudioAx_80024030(0);
        mn_8022F268();
        ((TyModeState*) Toy_804A284C)->x4 = 1;
        return;
    }

    if (Toy_80305B88() & 0x1200) {
        lbAudioAx_80024030(0);
        ((TyModeState*) Toy_804A284C)->x4 = 1;
        return;
    }

    {
        stick = cfg->x20;
        if (stick != zero) {
            cfg->x10 = -(stick * (0.02f * fov) - cfg->x10);
            if (cfg->x10 < -cfg->x1C) {
                cfg->x10 = -cfg->x1C;
            }
            if (cfg->x10 > cfg->x1C) {
                cfg->x10 = cfg->x1C;
            }
        }
    }

    {
        stick = cfg->x24;
        if (stick != zero) {
            cfg->x0C = (stick * (0.02f * fov)) + cfg->x0C;
            if (cfg->x0C < -cfg->x18) {
                cfg->x0C = -cfg->x18;
            }
            if (cfg->x0C > cfg->x18) {
                cfg->x0C = cfg->x18;
            }
        }
    }

    if (Toy_80305C44() & 0x424) {
        fov += cfg->x48;
        if (fov > cfg->x50) {
            fov = cfg->x50;
        }
        HSD_CObjSetFov(cobj, fov);
    }

    if (Toy_80305C44() & 0x848) {
        fov -= cfg->x48;
        if (fov < cfg->x4C) {
            fov = cfg->x4C;
        }
        HSD_CObjSetFov(cobj, fov);
    }

    if (Toy_80305B88() & 0x100) {
        HSD_CObjSetInterest(cobj, &cfg->x5C);
        HSD_CObjSetFov(cobj, cfg->x44);
        cfg->x10 = 0.0f;
        cfg->x0C = 0.0f;
        HSD_CObjSetEyePosition(cobj, &cfg->x68);
    }

    {
        cobj2 = (HSD_CObj*) cfg->x00->hsd_obj;
        HSD_CObjGetInterest(cobj2, &interest2);
        HSD_CObjGetEyePosition(cobj2, &eye2);
        tempvec1.x = cfg->x68.x;
        tempvec1.y = 0.0f;
        tempvec1.z = -500.0f;
        tempvec2.x = 0.017453292f * cfg->x0C;
        tempvec2.y = 0.017453292f * cfg->x10;
        tempvec2.z = 0.0f;
        lbVector_ApplyEulerRotation(&tempvec1, &tempvec2);
        tempvec1.z = cfg->x5C.z;
        HSD_CObjSetInterest(cobj2, &tempvec1);
    }
}

void _tyDisplay_8031A94C(HSD_GObj* arg0)
{
    u8 _1[0x4];
    Vec3 sp7C;
    Vec3 sp70;
    u8 _3[0x8];
    Vec3 interest2;
    Vec3 tempvec1;
    Vec3 eye2;
    Vec3 tempvec2;
    u8 _2[0x8];
    TyDspConfig* cfg = _tyDisplay_804D6F18;
    HSD_CObj* cobj = GET_COBJ(arg0);
    HSD_JObj* trophy = GET_JOBJ(cfg->x78)->child;
    f32 fov;
    f32 val;
    s32 sign;

    HSD_CObjGetInterest(cobj, &sp7C);
    HSD_CObjGetEyePosition(cobj, &sp70);
    fov = HSD_CObjGetFov(cobj);

    cfg->x20 = Toy_80305D00();
    cfg->x24 = Toy_80305DB0();

    val = cfg->x20;
    if (val > -0.2f && val < 0.2f) {
        cfg->x20 = 0.0f;
    } else {
        if (val > 0.0f) {
            sign = 1;
        } else {
            sign = -1;
        }
        cfg->x20 = -(0.2f * (f32) sign - val) / 0.8f;
    }

    val = cfg->x24;
    if (val > -0.2f && val < 0.2f) {
        cfg->x24 = 0.0f;
    } else {
        if (val > 0.0f) {
            sign = 1;
        } else {
            sign = -1;
        }
        cfg->x24 = -(0.2f * (f32) sign - val) / 0.8f;
    }

    cfg->x30 = Toy_80305EB4();
    cfg->x34 = Toy_80305FB8();

    val = cfg->x30;
    if (val > -0.2f && val < 0.2f) {
        cfg->x30 = 0.0f;
    } else {
        if (val > 0.0f) {
            sign = 1;
        } else {
            sign = -1;
        }
        cfg->x30 = -(0.2f * (f32) sign - val) / 0.8f;
    }

    val = cfg->x34;
    if (val > -0.2f && val < 0.2f) {
        cfg->x34 = 0.0f;
    } else {
        if (val > 0.0f) {
            sign = 1;
        } else {
            sign = -1;
        }
        cfg->x34 = -(0.2f * (f32) sign - val) / 0.8f;
    }

    if (cfg->x74 != 0) {
        cfg->x74 = cfg->x74 - 1;
        return;
    }

    if (Toy_80305C44() & 0x200) {
        _tyDisplay_804D6F28 += 1;
        if (_tyDisplay_804D6F28 > 0x78) {
            lbAudioAx_80024030(0);
            ((TyModeState*) Toy_804A284C)->x4 = 1;
        }
    } else {
        _tyDisplay_804D6F28 = 0;
        if ((Toy_80305C44() & 0x100 && cfg->x20 < -0.8f) ||
            (Toy_80305B88() & 1))
        {
            HSD_JObjAddTranslationX(trophy, -0.01f);
            _tyDisplay_8031BA78(cfg->x7C, 0, HSD_JObjGetTranslationX(trophy));
        }
        if ((Toy_80305C44() & 0x100 && cfg->x20 > 0.8f) ||
            (Toy_80305B88() & 2))
        {
            HSD_JObjAddTranslationX(trophy, 0.01f);
            _tyDisplay_8031BA78(cfg->x7C, 0, HSD_JObjGetTranslationX(trophy));
        }
        if ((Toy_80305C44() & 0x100 && cfg->x24 > 0.8f) ||
            (Toy_80305B88() & 8))
        {
            HSD_JObjAddTranslationZ(trophy, -0.01f);
            _tyDisplay_8031BA78(cfg->x7C, 2, HSD_JObjGetTranslationZ(trophy));
        }
        if ((Toy_80305C44() & 0x100 && cfg->x24 < -0.8f) ||
            (Toy_80305B88() & 4))
        {
            HSD_JObjAddTranslationZ(trophy, 0.01f);
            _tyDisplay_8031BA78(cfg->x7C, 2, HSD_JObjGetTranslationZ(trophy));
        }
        if (Toy_80305B88() & 0x20) {
            HSD_GObjPLink_80390228(cfg->x78);
            cfg->x78 = NULL;
            while (cfg->x78 == NULL) {
                cfg->x7C = cfg->x7C + 1;
                if (cfg->x7C >= 0x125) {
                    cfg->x7C = 0;
                }
                cfg->x78 = _tyDisplay_8031BC54(cfg->x7C);
            }
            return;
        }
        if (Toy_80305B88() & 0x40) {
            HSD_GObjPLink_80390228(cfg->x78);
            cfg->x78 = NULL;
            while (cfg->x78 == NULL) {
                cfg->x7C = cfg->x7C - 1;
                if (cfg->x7C < 0) {
                    cfg->x7C = 0x124;
                }
                cfg->x78 = _tyDisplay_8031BC54(cfg->x7C);
            }
            return;
        }
        if (!(Toy_80305C44() & 0x100)) {
            f32 stick = cfg->x20;
            f32 zero = 0.0f;
            if (stick != zero) {
                cfg->x10 = -(stick * (0.02f * fov) - cfg->x10);
                if (cfg->x10 < -cfg->x1C) {
                    cfg->x10 = -cfg->x1C;
                }
                if (cfg->x10 > cfg->x1C) {
                    cfg->x10 = cfg->x1C;
                }
            }
            {
                f32 stick2 = cfg->x24;
                if (stick2 != zero) {
                    cfg->x0C = (stick2 * (0.02f * fov)) + cfg->x0C;
                    if (cfg->x0C < -cfg->x18) {
                        cfg->x0C = -cfg->x18;
                    }
                    if (cfg->x0C > cfg->x18) {
                        cfg->x0C = cfg->x18;
                    }
                }
            }
        }
        if (cfg->x34 > 0.8f) {
            sp70.y += 1.0f;
            HSD_CObjSetEyePosition(cobj, &sp70);
        }
        if (cfg->x34 < -0.8f) {
            sp70.y -= 1.0f;
            HSD_CObjSetEyePosition(cobj, &sp70);
        }
        if (Toy_80305C44() & 0x400) {
            fov += cfg->x48;
            if (fov > cfg->x50) {
                fov = cfg->x50;
            }
            HSD_CObjSetFov(cobj, fov);
        }
        if (Toy_80305C44() & 0x800) {
            fov -= cfg->x48;
            if (fov < cfg->x4C) {
                fov = cfg->x4C;
            }
            HSD_CObjSetFov(cobj, fov);
        }
        if (Toy_80305B88() & 0x1000) {
            HSD_CObjSetInterest(cobj, &cfg->x5C);
            HSD_CObjSetFov(cobj, cfg->x44);
            cfg->x10 = 0.0f;
            cfg->x0C = 0.0f;
            HSD_CObjSetEyePosition(cobj, &cfg->x68);
        }
        {
            HSD_CObj* cobj2 = (HSD_CObj*) cfg->x00->hsd_obj;
            HSD_CObjGetInterest(cobj2, &interest2);
            HSD_CObjGetEyePosition(cobj2, &eye2);
            tempvec1.x = cfg->x68.x;
            tempvec1.y = 0.0f;
            tempvec1.z = -500.0f;
            tempvec2.x = 0.017453292f * cfg->x0C;
            tempvec2.y = 0.017453292f * cfg->x10;
            tempvec2.z = 0.0f;
            lbVector_ApplyEulerRotation(&tempvec1, &tempvec2);
            tempvec1.z = cfg->x5C.z;
            HSD_CObjSetInterest(cobj2, &tempvec1);
        }
    }
}

static u16 _tyDisplay_804D5ABC[] = { 0x15 };

void _tyDisplay_8031B1FC(void)
{
    HSD_Joint* joint;
    TyDspBgData* ptr = _tyDisplay_804D6F1C;
    HSD_GObj* gobj4;
    HSD_GObj* gobj;
    int zero;
    u8 temp;
    HSD_JObj* jobj;
    gobj4 = ptr->gobj4;
    zero = 0;
    do {
        UNUSED unsigned char _[(0x10)];
    } while (zero);

    if (ptr->archive == NULL) {
        OSReport("*** BG data aren't being loaded!\n");
        HSD_ASSERT(0x3FD, 0);
    }

    gobj = ptr->gobj0;
    if ((ptr->gobj4 && ptr->gobj4) && gobj4) {
    }
    if (gobj != NULL) {
        HSD_GObjPLink_80390228(gobj);
        ptr->gobj0 = NULL;
    }

    gobj = ptr->gobj4;
    if (gobj != NULL) {
        HSD_GObjPLink_80390228(gobj);
        ptr->gobj4 = NULL;
    }

    joint = HSD_ArchiveGetPublicAddress(ptr->archive, "ToyDspBg_Top_joint");
    if (joint != NULL) {
        ptr->gobj4 = GObj_Create(9, 9, zero);
        jobj = HSD_JObjLoadJoint(joint);
        HSD_GObjObject_80390A70(ptr->gobj4, temp = HSD_GObj_804D7849, jobj);
        GObj_SetupGXLink(ptr->gobj4, HSD_GObj_JObjCallback, 0x3C, zero);
        lb_8001204C(jobj, &ptr->jobj, _tyDisplay_804D5ABC, 1);
        return;
    }

    OSReport("*** Can not Load Panel Label(%s)\n", "ToyDspBg_Top_joint");
    HSD_ASSERT(0x43E, 0);
}

static GXColor const _tyDisplay_color_C8C8C8FF = { 0xC8, 0xC8, 0xC8, 0xFF };

/// @todo .data order hack
static void order_data_110(void)
{
    /* +110 */ (void) "ScMenDisplay_scene_lights";
}

/* 3FF11C */ static HSD_WObjDesc _tyDisplay_803FF11C = {
    NULL,
    { 0.0f, 130.0f, 500.0f },
    NULL,
};
/* 3FF130 */ static HSD_WObjDesc _tyDisplay_803FF130 = {
    NULL,
    { 0.0f, 0.0f, 0.0f },
    NULL,
};
/* 3FF144 */ static HSD_CameraDescPerspective _tyDisplay_803FF144 = {
    NULL,
    0,
    PROJ_PERSPECTIVE,
    { 0, 640, 0, 480 },
    { 0, 640, 0, 480 },
    &_tyDisplay_803FF11C,
    &_tyDisplay_803FF130,
    0.0f,
    NULL,
    0.1f,
    (float) 0x8000,
    30.0f,
    913.0f / 750.0f,
};

/// @todo .data order hack
static void order_data_18C(void)
{
    /* +18C */ (void) "ScMenDisplay_cam_int1_camera";
}

void _tyDisplay_8031B328(void)
{
    TyDspBgData* ptr = _tyDisplay_804D6F1C;
    ToyCameraControl* scene = (ToyCameraControl*) Toy_sbss_804D6ED4;
    char* strbase = "ToyDspPanel_Top_joint";
    LightList** lightData;
    HSD_FogDesc* fogDesc;
    TyDspBgData* temp3;
    s8 temp2;
    HSD_LObj* lobj;
    HSD_GObj* temp;

    PAD_STACK(24);

    if ((temp3 = ptr)->archive == NULL) {
        OSReport("*** BG data aren't being loaded!\n");
        OSPanic(__FILE__, 1113, "");
    }

    if ((lightData = HSD_ArchiveGetPublicAddress(
             temp3->archive, "ScMenDisplay_scene_lights")) != NULL)
    {
        scene->x00 = GObj_Create(2, 3, 0);
        lobj = Toy_LoadLObjList(lightData, 0);
        HSD_GObjObject_80390A70(scene->x00, (unsigned long) HSD_GObj_804D784A,
                                lobj);
        temp = scene->x00;
        GObj_SetupGXLink(temp, HSD_GObj_LObjCallback, 0x34, 0);
    }
    if (_tyDisplay_804D6F20 != 0) {
        HSD_LObjSetColor(lobj, _tyDisplay_color_C8C8C8FF);
    }

    if ((fogDesc = HSD_ArchiveGetPublicAddress(temp3->archive,
                                                strbase + 0x44)) != NULL)
    {
        scene->x08 = GObj_Create(3, 4, 0);
        HSD_GObjObject_80390A70(scene->x08, temp2 = HSD_GObj_804D7848,
                                HSD_FogLoadDesc(fogDesc));
        GObj_SetupGXLink(scene->x08, Toy_80306930, 0x35, 0);
    }
}

void tyDisplay_OnEnter_8031B460(void* arg0)
{
    s32 sp18;
    TyDspConfig* cfg;
    TyDspBgData* data;
    TyDspGrid* grid;
    HSD_CObj* cobj;
    HSD_GObj* gobj;
    int i;
    char* strbase = (char*) 0x803FEFF0;
    PAD_STACK(8);

    _tyDisplay_804D6F10 = HSD_MemAlloc(0x4B0);
    _tyDisplay_804D6F14 = HSD_MemAlloc(0x12E4);
    _tyDisplay_804D6F18 = HSD_MemAlloc(0x80);
    _tyDisplay_804D6F1C = HSD_MemAlloc(0x108);
    Toy_sbss_804D6ED4 = HSD_MemAlloc(0xE4);

    cfg = _tyDisplay_804D6F18;
    data = _tyDisplay_804D6F1C;
    grid = _tyDisplay_804D6F14;

    if (Toy_80305C44() & 0x40) {
        grid->x00 = 2;
    } else if (Toy_80305C44() & 0x20) {
        grid->x00 = 1;
    } else if (Toy_80305C44() & 0x800) {
        grid->x00 = 3;
    } else {
        grid->x00 = 0;
    }

    _tyDisplay_804D6F20 = 0;
    _tyDisplay_804D6F2C = 0;
    _tyDisplay_804D6F24 = NULL;

    if ((s32) DbLevel >= 3 && (Toy_80305C44() & 0x10)) {
        _tyDisplay_804D6F20 = 1;
        cfg->x7C = 0;
    }

    Toy_8031263C();
    memzero(_tyDisplay_804D6F1C, 0x108);
    memzero(_tyDisplay_804D6F18, 0x80);
    memzero(Toy_sbss_804D6ED4, 0xE4);

    cfg->x08 = Toy_GetTrophyTotal();

    if ((s32) _tyDisplay_804D6F20 != 0) {
        cfg->x08 = 1;
        _tyDisplay_8031C1D0();
    }

    switch (grid->x00) {
    case 0:
    case 1: {
        s32 count = cfg->x08;
        s32 toggle = 0;
        cfg->x75 = 1;
        cfg->x76 = 1;
        while ((s8) cfg->x75 * (s8) cfg->x76 < count) {
            toggle ^= 1;
            if (toggle != 0 && (s8) cfg->x75 < 0x14) {
                cfg->x75++;
            } else {
                cfg->x76++;
            }
        }
        cfg->x75++;
        cfg->x76++;
        break;
    }
    case 2:
    case 3: {
        s32 count = cfg->x08;
        s32 toggle = 0;
        cfg->x75 = 1;
        cfg->x76 = 1;
        while ((s8) cfg->x75 * (s8) cfg->x76 < count) {
            toggle ^= 1;
            if (toggle != 0 && (s8) cfg->x75 < 0x14) {
                cfg->x75++;
            } else {
                cfg->x76++;
            }
        }
        break;
    }
    }

    {
        s32 jp = lbLang_IsSavedLanguageJP();
        char* archname;
        if (jp != 0) {
            archname = strbase + 0xA8;
        } else {
            archname = strbase + 0xB8;
        }
        data->archive = lbArchive_80016DBC(archname, &sp18, strbase + 0x18, 0);
    }

    for (i = 0; i < 0x2B; i++) {
        s32 ret = _tyDisplay_8031BBF4((s8) i);
        data->archives[i] = lbArchive_LoadSymbols((char*) ret, 0L);
    }

    data->x104 = 0;

    {
        TyDspConfig* cfg2 = _tyDisplay_804D6F18;
        cobj = lb_80013B14(HSD_ArchiveGetPublicAddress(
            _tyDisplay_804D6F1C->archive, strbase + 0x18C));

        cfg2->x00 = GObj_Create(1, 2, 0);
        HSD_GObjObject_80390A70(cfg2->x00, HSD_GObj_804D784B, cobj);
        GObj_SetupGXLinkMax(cfg2->x00, (GObj_RenderFunc) (Event) Toy_803068E0,
                            0);

        gobj = cfg2->x00;
        gobj->gxlink_prios = 0x1230000000000000ULL;

        if ((s32) _tyDisplay_804D6F20 != 0) {
            HSD_GObj_SetupProc(cfg2->x00, (HSD_GObjEvent) _tyDisplay_8031A94C,
                               0);
        } else {
            HSD_GObj_SetupProc(cfg2->x00, (HSD_GObjEvent) _tyDisplay_8031A4EC,
                               0);
        }
        HSD_GObj_80390CD4(cfg2->x00);
    }

    _tyDisplay_8031B328();
    _tyDisplay_8031B1FC();

    if ((s32) _tyDisplay_804D6F20 != 0) {
        memzero(grid, 0x12E4);
        grid->x08_min_z = -3.5f;
        grid->x04_min_x = -3.5f;
        grid->x10_max_z = 3.5f;
        grid->x0C_max_x = 3.5f;
        cfg->x78 = _tyDisplay_8031BC54(cfg->x7C);
    } else {
        s32 m = grid->x00;
        switch (m) {
        case 0:
        case 1:
            _tyDisplay_80318CB4(m);
            break;
        case 2:
            _tyDisplay_80319540(HSD_Randi(2));
            break;
        case 3:
            _tyDisplay_80319994(HSD_Randi(2));
            break;
        }
    }
    _tyDisplay_80319EF0();
}

void _tyDisplay_8031B850(void)
{
    ToyAnimState* anim = &Toy_804A2AA8;
    TyDspBgData* ptr = _tyDisplay_804D6F1C;
    TyDspConfig* pgobj = _tyDisplay_804D6F18;
    HSD_GObj** temp;
    ToyCameraControl* scene = (ToyCameraControl*) Toy_sbss_804D6ED4;
    HSD_GObj* gobj;

    if (ptr->archive != NULL) {
        ptr->archive = NULL;
    }

    if (Toy_sbss_804D6EC8 != NULL) {
        Toy_sbss_804D6EC8 = NULL;
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

    gobj = *(temp = &pgobj->x00);
    if (gobj != NULL) {
        HSD_GObjProc_8038FED4(gobj);
        *temp = NULL;
    }

    if (_tyDisplay_804D6F2C != NULL) {
        if (_tyDisplay_804A2DD0.archive != NULL) {
            lbArchive_80016EFC(_tyDisplay_804A2DD0.archive);
            _tyDisplay_804A2DD0.archive = NULL;
        }
        HSD_GObjPLink_80390228(_tyDisplay_804D6F2C);
        _tyDisplay_804D6F2C = NULL;
    }

    if (_tyDisplay_804D6F24 != NULL) {
        DevText_Remove(&_tyDisplay_804D6F24);
        _tyDisplay_804D6F24 = NULL;
    }
}

void tyDisplay_OnFrame_8031B9A4(void)
{
    TyModeState* state = (TyModeState*) Toy_804A284C;

    if (state->x4 != 0) {
        _tyDisplay_8031B850();
        gm_801A4B60();
    }
}

TyDspEntry* tyDisplay_8031B9DC(s32 id)
{
    TyDspEntry* p;
    s32 val;
    bool found = false;

    if (lbLang_IsSettingUS()) {
        p = Toy_sbss_804D6EAC;

        while (val = p->x00, val != -1) {
            if (val == id) {
                found = true;
                break;
            }
            p++;
        }
    }

    if (found == 0) {
        p = Toy_sbss_804D6EB0;

        while (val = p->x00, val != -1) {
            if (val == id) {
                found = true;
                break;
            }
            p++;
        }
    }

    return p;
}

void _tyDisplay_8031BA78(s32 arg0, s32 arg1, f32 farg0)
{
    char buf[24];
    TyDspEntry* data;

    data = tyDisplay_8031B9DC(arg0);
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
    if (_tyDisplay_804D6F24 != NULL) {
        DevText_Erase(_tyDisplay_804D6F24);
        DevText_SetCursorXY(_tyDisplay_804D6F24, 0, 0);
        sprintf(buf, "X  %3.2f\nZ  %3.2f", data->x08, data->x0C);
        DevText_Print(_tyDisplay_804D6F24, buf);
    }
}

s32 tyDisplay_8031BB34(s8 idx)
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

        "ToyDspQues_Top_joint"
    };

    if (idx == -1) {
        idx = 0;
    }

    return (s32) table[idx];
}

char* tyDisplay_8031BB94(s8 idx)
{
    char* table[] = {
        "",
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
        "",
        "",
    };

    if (idx == -1) {
        idx = 0;
    }

    return table[idx];
}

s32 _tyDisplay_8031BBF4(s8 arg0)
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

HSD_GObj* _tyDisplay_8031BC54(s32 arg0)
{
#if 0
    char buf[44];
    HSD_GObj* gobj;
    s32 id = arg0;
    TyDspEntry* entry;
    TyDspBgData* data = _tyDisplay_804D6F1C;
    TyDspArchNames jobj_names;
    TyDspArchNames matanim_names;
    HSD_JObj* root;
    HSD_JObj* child;
    u8 cat;
    u32 c;
    u32 c2;

    entry = tyDisplay_8031B9DC(id);
    gobj = GObj_Create(6, 7, 0);
    root = HSD_JObjAlloc();
    HSD_GObjObject_80390A70(gobj, HSD_GObj_804D7849, root);
    GObj_SetupGXLink(gobj, HSD_GObj_JObjCallback, 0x3C, 0);
    cat = (c = entry->x04);
    jobj_names = *(TyDspArchNames*) _tyDisplay_803B8988.jobj_names;
    if ((s8) c == -1) {
        cat = 0;
    }

    {
        const char* temp;
        temp = jobj_names.entries[(s8) cat];
        child = HSD_JObjLoadJoint(
            HSD_ArchiveGetPublicAddress(data->archives[c], temp));
    }

    HSD_JObjAddChild(root, child);

    c2 = entry->x04;
    cat = c2;
    matanim_names = _tyDisplay_803B8A34;
    if ((s8) c2 == -1) {
        cat = 0;
    }

    {
        char* temp2;
        temp2 = (char*) matanim_names.entries[(s8) cat];
        Toy_80306A48(child, NULL, temp2, NULL, data->archives[c2],
                     (long) entry->x05);
    }
    HSD_JObjRemoveAnimAll(child);

    HSD_JObjSetTranslateX(child, entry->x08);
    HSD_JObjSetTranslateZ(child, entry->x0C);

    HSD_JObjAddChild(root, HSD_JObjLoadJoint(HSD_ArchiveGetPublicAddress(
                               data->archives[41], "ToyDspStand_Top_joint")));

    if (_tyDisplay_804D6F24 != NULL) {
        DevText_Erase(_tyDisplay_804D6F24);
        DevText_SetCursorXY(_tyDisplay_804D6F24, 0, 0);
        sprintf(buf, "X  %3.2f\nZ  %3.2f", entry->x08, entry->x0C);
        DevText_Print(_tyDisplay_804D6F24, buf);
        _tyDisplay_8031BF34(id);
    }

    return gobj;
#else
    NOT_IMPLEMENTED;
#endif
}

static inline HSD_JObj* un_8031BF34_inline(void)
{
    return (HSD_JObj*) _tyDisplay_804D6F2C->hsd_obj;
}

void _tyDisplay_8031BF34(s32 arg0)
{
    TyDspArchiveHolder* a = &_tyDisplay_804A2DD0;
    ToyAnimState* anim = &Toy_804A2AA8;
    HSD_JObj* jobj;

    PAD_STACK(8);

    if (_tyDisplay_804D6F2C != NULL) {
        if (_tyDisplay_804A2DD0.archive != NULL) {
            lbArchive_80016EFC(_tyDisplay_804A2DD0.archive);
            _tyDisplay_804A2DD0.archive = NULL;
        }
    }

    Toy_80308250(a->x0, (s16) (u16) arg0, 0);
    _tyDisplay_804D6F2C = Toy_803087F4(a->x0);

    HSD_JObjClearFlagsAll(anim->jobj[0], JOBJ_HIDDEN);
    HSD_JObjSetFlagsAll(anim->jobj[1], JOBJ_HIDDEN);
    HSD_JObjClearFlagsAll(anim->jobj[0], JOBJ_HIDDEN);

    jobj = un_8031BF34_inline();

    HSD_JObjSetScaleX(jobj, 0.6f);
    HSD_JObjSetScaleY(jobj, 0.6f);
    HSD_JObjSetScaleZ(jobj, 0.6f);
    HSD_JObjAddTranslationX(jobj, 12.0f);
}

static GXColor const _tyDisplay_804DE024 = { 0xE2, 0xE2, 0xE2, 0xFF };
static GXColor const _tyDisplay_804DE028 = { 0x40, 0x80, 0xD0, 0x60 };

void _tyDisplay_8031C1D0(void)
{
    s32 savedColor;
    s32 bgColor;
    char buf[28];
    HSD_GObj* gobj;

    savedColor = *(s32 const*) &_tyDisplay_804DE024;
    _tyDisplay_804D6F24 =
        DevText_Create(1, 40, 40, 9, 3, _tyDisplay_devtext_buf);
    if (_tyDisplay_804D6F24 != NULL) {
        gobj = DevText_GetGObj();
        bgColor = *(s32 const*) &_tyDisplay_804DE028;
        DevText_Show(gobj, _tyDisplay_804D6F24);
        DevText_HideCursor(_tyDisplay_804D6F24);
        DevText_80302AC0(_tyDisplay_804D6F24);
        DevText_SetBGColor(_tyDisplay_804D6F24, *(GXColor*) &bgColor);
        DevText_SetScale(_tyDisplay_804D6F24, 12.0f, 18.0f);
        DevText_Erase(_tyDisplay_804D6F24);
        DevText_SetCursorXY(_tyDisplay_804D6F24, 0, 0);
        DevText_StoreColorIndex(_tyDisplay_804D6F24, 0);
        DevText_SetTextColor(_tyDisplay_804D6F24, *(GXColor*) &savedColor);
        sprintf(buf, "X  %3.2f\nZ  %3.2f", 0.0, 0.0);
        DevText_Print(_tyDisplay_804D6F24, buf);
    }
}

void tyDisplay_8031C2CC(void)
{
    Toy_803124BC();
}

s32 tyDisplay_8031C2EC(void)
{
    if (Toy_80304B0C(5) != 0) {
        if (HSD_Randi(2) == 0) {
            return Toy_80305058(2, 5, 1, 65.0f);
        }
    }
    return Toy_80305058(2, 0, 1, 60.0f);
}

s32 tyDisplay_8031C354(s32 id, s32 buf[], s32 max, s32 kind)
{
    TyDspEntry* data;
    TyDspEntry* other;
    s32 i;
    s32 count;
    s32 val;
    PAD_STACK(0x8);

    if (id == -1) {
        return 0;
    }

    data = tyDisplay_8031B9DC(id);

    if (kind == 99) {
        kind = (s32) Toy_803060BC(id, 6);
    }

    count = 0;
    for (i = 0; i < 0x125; i++) {
        if (i == id) {
            continue;
        }
        if (Toy_80304CC8(i) == 0) {
            continue;
        }
        if (Toy_803049F4(i) == 0) {
            continue;
        }
        other = tyDisplay_8031B9DC(i);
        val = (s32) Toy_803060BC(i, 6);
        if ((other->x04 != data->x04)) {
            continue;
        }
        if (val != kind) {
            continue;
        }
        count++;
        *buf = i;
        buf++;
        if (count >= max) {
            break;
        }
    }

    return count;
}

s32 tyDisplay_8031C454(s32 arg0)
{
#if 0
    HSD_Archive* temp2;
    TyDspArchNames names1;
    TyDspArchNames names2;
    const TyDspNameTables* temp;
    TyDspArchNames names3;
    TyDspEntry* entry;
    u8 idx;
    s32 result;
    HSD_Archive** archArr;
    const TyDspNameTables* tables;

    PAD_STACK(0x4);
    tables = &_tyDisplay_803B8988;
    result = 0;
    archArr = _tyDisplay_804A2DE8;

    Toy_803124BC();

    if (arg0 == -1) {
        return -1;
    }

    entry = tyDisplay_8031B9DC(arg0);
    idx = entry->x04;

    temp = tables;
    if (archArr[idx] == NULL) {
        idx = entry->x04;
        names1 = temp->arch_names;
        if ((s8) idx == -1) {
            idx = 0;
        }
        archArr[entry->x04] =
            lbArchive_LoadSymbols(names1.entries[(s8) idx], NULL);
    } else {
        result = 1;
    }

    if (archArr[42] == NULL) {
        names2 = tables->arch_names;
        archArr[42] = lbArchive_LoadSymbols(names2.entries[42], NULL);
    }
    temp2 = archArr[41];
    if (temp2 == NULL) {
        do {
            names3 = temp->arch_names;
            archArr[41] = lbArchive_LoadSymbols(names3.entries[41], 0L);
        } while (entry->x04 * 0);
    }

    return result;
#else
    NOT_IMPLEMENTED;
#endif
}

inline void* un_8031C5E4_inline(HSD_Archive** arg0, u8 arg1, const char* arg2)
{
    return HSD_ArchiveGetPublicAddress(arg0[arg1], arg2);
}

HSD_JObj* tyDisplay_8031C5E4(s32 arg0)
{
#if 0
    u8 _1[12];
    TyDspArchNames jobj_names1;
    char* temp;
    TyDspArchNames matanim_names1;
    TyDspArchNames jobj_names2;
    u8 _2[4];
    TyDspArchNames jobj_names3;
    TyDspEntry* entry;
    HSD_JObj* root;
    HSD_JObj* child;
    u8 cat;
    const TyDspNameTables* tables = &_tyDisplay_803B8988;

    HSD_Archive** archives = _tyDisplay_804A2DE8;
    u8 _3[4];

    entry = tyDisplay_8031B9DC(arg0);
    if (archives[entry->x04] == NULL) {
        return NULL;
    }

    root = HSD_JObjAlloc();

    {
        u8 c = entry->x04;
        cat = c;
        jobj_names1 = *(TyDspArchNames*) tables->jobj_names;
        if ((s8) c == -1) {
            cat = 0;
        }
        child = HSD_JObjLoadJoint(
            un_8031C5E4_inline(archives, c, jobj_names1.entries[(s8) cat]));
        HSD_JObjAddChild(root, child);
    }

    {
        u8 c = entry->x04;
        cat = c;
        matanim_names1 = *(TyDspArchNames*) tables->matanim_names;
        if ((s8) c == -1) {
            cat = 0;
        }
        temp = (char*) matanim_names1.entries[(s8) cat];
        Toy_80306A48(child, NULL, (char*) temp, NULL, archives[c], entry->x05);
    }
    HSD_JObjRemoveAnimAll(child);
    HSD_JObjSetTranslateX(child, entry->x08);
    HSD_JObjSetTranslateZ(child, entry->x0C);

    jobj_names2 = *(TyDspArchNames*) tables->jobj_names;
    HSD_JObjAddChild(root, HSD_JObjLoadJoint(un_8031C5E4_inline(
                               archives, 42, jobj_names2.entries[42])));

    jobj_names3 = *(TyDspArchNames*) tables->jobj_names;
    HSD_JObjAddChild(root, HSD_JObjLoadJoint(un_8031C5E4_inline(
                               archives, 41, jobj_names3.entries[41])));

    return root;
#else
    NOT_IMPLEMENTED;
}
#endif

void tyDisplay_8031C8B8(void)
{
    s32 i;

    for (i = 0; 0x2B > i; i++) {
        _tyDisplay_804A2DE8[i] = NULL;
    }
}
