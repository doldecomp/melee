#include "tylist.h"

#include "gm/gmmain_lib.h"
#include "if/textlib.h"
#include "lb/lb_00B0.h"
#include "lb/lbarchive.h"
#include "lb/lblanguage.h"
#include "ty/toy.h"

#include <m2c_macros.h>
#include <baselib/archive.h>
#include <baselib/cobj.h>
#include <baselib/controller.h>
#include <baselib/displayfunc.h>
#include <baselib/fog.h>
#include <baselib/gobj.h>
#include <baselib/gobjgxlink.h>
#include <baselib/gobjobject.h>
#include <baselib/gobjplink.h>
#include <baselib/gobjproc.h>
#include <baselib/sislib.h>
#include <baselib/video.h>

typedef struct {
    u8 pad[0x28];
    HSD_CObj* cobj;
} TyListData;

typedef struct TyListArg {
    /* 0x00 */ void* x0;
    /* 0x04 */ void* x4;
    /* 0x08 */ void* x8;
    /* 0x0C */ HSD_JObj* xC;
    /* 0x10 */ HSD_JObj* x10;
    /* 0x14 */ HSD_JObj* x14;
    /* 0x18 */ u8 pad_18[0x26 - 0x18];
    /* 0x26 */ s16 idx;
    /* 0x28 */ u8 pad_28[0x2C - 0x28];
    /* 0x2C */ float x2C;
    /* 0x30 */ float x30;
} TyListArg;

void un_803124BC(void)
{
    char* strs = un_803FDD18;
    u16* table1;
    s16* list;
    u16* table2;
    s32 i;

    table1 = gmMainLib_8015CC78();
    table2 = gmMainLib_8015CC84();

    if (un_804D6ED0 == NULL) {
        char* archiveName;
        if (lbLang_IsSavedLanguageJP()) {
            archiveName = strs + 0x608;
        } else {
            archiveName = strs + 0x614;
        }
        un_804D6ED0 = lbArchive_LoadSymbols(
            archiveName, &un_804D6EC4, strs + 0x9DC, &un_804D6EC0,
            strs + 0x9EC, &un_804D6EBC, strs + 0x9FC, &un_804D6EB8,
            strs + 0xA0C, &un_804D6EB4, strs + 0xA20, &un_804D6EB0,
            strs + 0xA30, &un_804D6EAC, strs + 0xA44, NULL);
    }

    i = 0;
loop: {
    s32 skip;
    s16 val;

    list = un_804D6EB4;
    if (lbLang_IsSettingUS()) {
        while ((val = *list) != -1) {
            if (val == i) {
                skip = 0;
                goto check;
            }
            list++;
        }
    }
    skip = 1;
check:
    if (skip != 0 && (s32) un_803060BC(i, 6) == 2) {
        *table1 |= 0x4000;
    }
}
    i++;
    table1++;
    if (i < 0x125) {
        goto loop;
    }

    *table2 |= 4;
    un_804A284C[3] |= 4;
}

void un_8031263C(void)
{
    char* strs = un_803FDD18;
    s32 i;
    u16* table1;
    u16* table2;

    M2C_FIELD(un_804A284C, u8*, 4) = 0;
    table1 = gmMainLib_8015CC78();
    table2 = gmMainLib_8015CC84();

    if (un_804D6ED0 == NULL) {
        char* archiveName;
        if (lbLang_IsSavedLanguageJP()) {
            archiveName = strs + 0x608;
        } else {
            archiveName = strs + 0x614;
        }
        un_804D6ED0 = lbArchive_LoadSymbols(
            archiveName, &un_804D6EC4, strs + 0x9DC, &un_804D6EC0,
            strs + 0x9EC, &un_804D6EBC, strs + 0x9FC, &un_804D6EB8,
            strs + 0xA0C, &un_804D6EB4, strs + 0xA20, &un_804D6EB0,
            strs + 0xA30, &un_804D6EAC, strs + 0xA44, NULL);
    }

    i = 0;
    do {
        if (un_80304CC8(i) != 0) {
            if ((s32) un_803060BC(i, 6) == 2) {
                *table1 |= 0x4000;
            }
        }
        i++;
        table1++;
    } while (i < 0x125);

    *table2 |= 4;
    un_804A284C[3] |= 4;

    if (un_804D6ECC == NULL) {
        un_804D6ECC =
            lbArchive_LoadSymbols(strs + 0xA58, &un_804D6EA8, strs + 0xA64,
                                  &un_804D6EA4, strs + 0xA74, NULL);
    }

    un_8031234C(0);
}
void un_803127D4(void)
{
    un_804D6ED0 = NULL;
    un_804D6EC4 = NULL;
    un_804D6EC0 = NULL;
    un_804D6EBC = NULL;
    un_804D6EB8 = NULL;
    un_804D6EB4 = NULL;
    un_804D6EB0 = NULL;
    un_804D6EAC = NULL;
    un_804D6ECC = NULL;
    un_804D6EA8 = NULL;
    un_804D6EA4 = NULL;
    un_804D6EC8 = NULL;
    memzero(un_804A2AA8, 0x14);
}

/// Formats a number into a string buffer using digit glyphs from the font.
void un_80312834(char* buf, u32 num)
{
    /// @todo Extract font digit lookup struct - offset 0x4E8 in SIS font data
    u8* lookup = M2C_FIELD(HSD_SisLib_804D1124[0], u8**, 0x4E8);
    u32 idx;
    u32 original = num;

    if (num >= 100) {
        idx = (num / 100) * 2;
        *buf++ = lookup[idx];
        *buf++ = lookup[idx + 1];
        num = num % 100;
    }

    if (num >= 10) {
        idx = (num / 10) * 2;
        *buf++ = lookup[idx];
        *buf++ = lookup[idx + 1];
        num = num % 10;
    } else if (original >= 100) {
        *buf++ = lookup[0];
        *buf++ = lookup[1];
    }

    idx = num * 2;
    *buf++ = lookup[idx];
    *buf++ = lookup[idx + 1];
    *buf = 0;
}

/// #un_80312904

/// #un_80312BAC

void un_80312E88(TyListArg* arg, float delta)
{
    TyListArg* ptr;
    HSD_JObj* jobj;
    char* data;
    s32 i;
    PAD_STACK(8);

    arg->x30 = arg->x30 + delta;

    if (un_804DDE4C == delta) {
        arg->x30 = arg->x2C;
    } else if (delta < un_804DDE48) {
        if (arg->x30 < arg->x2C) {
            arg->x30 = arg->x2C;
        }
    } else {
        if (arg->x30 > arg->x2C) {
            arg->x30 = arg->x2C;
        }
    }

    ptr = arg;
    data = un_804A2AC0;
    i = 0;
loop:
    if ((jobj = M2C_FIELD(ptr, HSD_JObj**, 0xC)) == NULL) {
        goto next;
    }
    if (i == 2) {
        goto next;
    }
    {
        float pos = arg->x30;
        if (jobj == NULL) {
            __assert(&un_804D5A78, 0x3B3, &un_804D5A80);
        }
        jobj->translate.y = pos;
    }

    if ((jobj->flags & 0x02000000) == 0) {
        if (jobj == NULL) {
            goto skip_dirty;
        }
        if (jobj == NULL) {
            __assert(&un_804D5A78, 0x234, &un_804D5A80);
        }
        {
            u32 flags = jobj->flags;
            s32 skip = 0;
            if ((flags & 0x800000) == 0 && (flags & 0x40)) {
                skip = 1;
            }
            if (skip == 0) {
                HSD_JObjSetMtxDirtySub(jobj);
            }
        }
    }
skip_dirty:

    if (arg->idx == un_80304870() - 1) {
        float pos;
        jobj = M2C_FIELD(data, HSD_JObj**, 0x28C);
        pos = arg->x30;
        if (jobj == NULL) {
            __assert(&un_804D5A78, 0x3B3, &un_804D5A80);
        }
        jobj->translate.y = pos;

        if ((jobj->flags & 0x02000000) == 0) {
            if (jobj == NULL) {
                goto next;
            }
            if (jobj == NULL) {
                __assert(&un_804D5A78, 0x234, &un_804D5A80);
            }
            {
                u32 flags = jobj->flags;
                s32 skip = 0;
                if ((flags & 0x800000) == 0 && (flags & 0x40)) {
                    skip = 1;
                }
                if (skip == 0) {
                    HSD_JObjSetMtxDirtySub(jobj);
                }
            }
        }
    }

next:
    i = i + 1;
    ptr = (TyListArg*) ((s8*) ptr + 4);
    if (i < 3) {
        goto loop;
    }

    un_80312904(arg, 0x63);
    un_80313464(arg);
}
/// #un_8031305C

void un_80313358(void* arg1, s8 arg2, s8 arg3, s8 arg4)
{
    u8* ptr = arg1;
    int i;

    if (arg2 != -1) {
        M2C_FIELD(ptr, u8*, 0x29E) = arg2;
        M2C_FIELD(ptr, u8*, 0x2A1) = arg4;
    }

    M2C_FIELD(ptr, u8*, 0x29F) = arg3;
    M2C_FIELD(ptr, float*, 0x2A4) =
        M2C_FIELD(ptr, float*, 0x2A8) / (float) arg3;

    if (M2C_FIELD(ptr, s8*, 0x2A1) == 0) {
        for (i = 0; i < M2C_FIELD(ptr, s8*, 0x29A); i++) {
            void** entry = (void**) (ptr + i * 0x34);
            u8* sub = entry[0];
            M2C_FIELD(ptr, float*, i * 0x34 + 0x2C) =
                M2C_FIELD(sub, float*, 0x30);
            un_80312904(entry, M2C_FIELD(ptr, u8*, 0x29A) + 1);
        }
    } else {
        for (i = 0; i < M2C_FIELD(ptr, s8*, 0x29A); i++) {
            void** entry = (void**) (ptr + i * 0x34);
            u8* sub = entry[1];
            M2C_FIELD(ptr, float*, i * 0x34 + 0x2C) =
                M2C_FIELD(sub, float*, 0x30);
            un_80312904(entry, M2C_FIELD(ptr, u8*, 0x29A) + 1);
        }
    }
}

void un_80313464(TyListArg* arg)
{
    char* data = un_804A2AC0;
    s32 val;
    PAD_STACK(24);

    val = un_804D6EDC[arg->idx];

    un_803083D8(arg->x14, val);

    if (arg->x10 != NULL) {
        HSD_JObjUnref(arg->x10);
        arg->x10 = NULL;
    }

    if (un_80304924(val) != 0) {
        arg->x10 = un_80313508(M2C_FIELD(data, void**, 0x27C), un_803FE8D0,
                               un_804DDE60, arg->x30, un_804DDE48);
    }
}
HSD_JObj* un_80313508(void* parent, void* symbol, float x, float y, float z)
{
    HSD_JObj* jobj;
    void* archive;
    void* joint;
    PAD_STACK(8);

    archive = un_804D6ED8;
    joint =
        HSD_ArchiveGetPublicAddress(M2C_FIELD(archive, void**, 0x50), symbol);

    if (joint == NULL) {
        OSPanic(un_803FE8F0, 0x337, un_803FE8FC);
        return NULL;
    }

    jobj = HSD_JObjLoadJoint(joint);

    if (x != un_804DDE48 || y != un_804DDE48 || z != un_804DDE48) {
        // Set X
        if (jobj == NULL) {
            __assert(&un_804D5A78, 0x3A4, &un_804D5A80);
        }
        jobj->translate.x = x;

        if ((jobj->flags & 0x02000000) == 0) {
            if (jobj == NULL) {
                goto skip_x;
            }
            if (jobj == NULL) {
                __assert(&un_804D5A78, 0x234, &un_804D5A80);
            }
            {
                u32 flags = jobj->flags;
                s32 skip = 0;
                if ((flags & 0x800000) == 0 && (flags & 0x40)) {
                    skip = 1;
                }
                if (skip == 0) {
                    HSD_JObjSetMtxDirtySub(jobj);
                }
            }
        }
    skip_x:

        // Set Y
        if (jobj == NULL) {
            __assert(&un_804D5A78, 0x3B3, &un_804D5A80);
        }
        jobj->translate.y = y;

        if ((jobj->flags & 0x02000000) == 0) {
            if (jobj == NULL) {
                goto skip_y;
            }
            if (jobj == NULL) {
                __assert(&un_804D5A78, 0x234, &un_804D5A80);
            }
            {
                u32 flags = jobj->flags;
                s32 skip = 0;
                if ((flags & 0x800000) == 0 && (flags & 0x40)) {
                    skip = 1;
                }
                if (skip == 0) {
                    HSD_JObjSetMtxDirtySub(jobj);
                }
            }
        }
    skip_y:

        // Set Z
        if (jobj == NULL) {
            __assert(&un_804D5A78, 0x3C2, &un_804D5A80);
        }
        jobj->translate.z = z;

        if ((jobj->flags & 0x02000000) == 0) {
            if (jobj == NULL) {
                goto skip_z;
            }
            if (jobj == NULL) {
                __assert(&un_804D5A78, 0x234, &un_804D5A80);
            }
            {
                u32 flags = jobj->flags;
                s32 skip = 0;
                if ((flags & 0x800000) == 0 && (flags & 0x40)) {
                    skip = 1;
                }
                if (skip == 0) {
                    HSD_JObjSetMtxDirtySub(jobj);
                }
            }
        }
    skip_z:;
    }

    if (parent != NULL) {
        HSD_JObj* parentJobj = M2C_FIELD(parent, HSD_JObj**, 0x28);
        HSD_JObj* child;
        HSD_JObjAddChild(parentJobj, jobj);
        child = parentJobj->child;
        while (child->next != NULL) {
            child = child->next;
        }
    } else {
        HSD_GObj* gobj;
        gobj = GObj_Create(6, 7, 0);
        HSD_GObjObject_80390A70(gobj, (u8) HSD_GObj_804D7849, jobj);
        GObj_SetupGXLink(gobj, HSD_GObj_JObjCallback, 0x39, 0);
    }

    return jobj;
}

/// #un_80313774

/// #fn_80313BD8

/// #fn_8031438C

void fn_80314504(HSD_GObj* gobj)
{
    TyListData* data = (TyListData*) gobj;

    if ((s32) HSD_CObjSetCurrent(data->cobj) != 0) {
        HSD_SetEraseColor(0, 0, 0, 0xFF);
        HSD_CObjEraseScreen(data->cobj, 1, 0, 0);
        HSD_GObj_80390ED0(gobj, 7);
        HSD_FogSet(0);
        HSD_CObjEndCurrent();
    }
}

/// #un_8031457C

void un_803147C4(void)
{
    char* data = un_804A2AC0;
    char* strs = un_803FE880;
    void* archive;
    HSD_GObj** gobj_ptr;
    HSD_JObj* jobj;
    PAD_STACK(8);

    memzero(&M2C_FIELD(data, u8*, 0x2AC), 0x18);
    un_8031457C();
    memzero(&M2C_FIELD(data, u8*, 0x2C4), 0x14);

    archive = un_804D6ED8;
    gobj_ptr = (HSD_GObj**) (data + 0x2C4);

    if (M2C_FIELD(archive, void**, 0x50) == NULL) {
        OSReport(strs + 0x14C);
        OSPanic(strs + 0x70, 0x636, un_804D5A8C);
    }

    jobj = HSD_ArchiveGetPublicAddress(M2C_FIELD(archive, void**, 0x50),
                                       strs + 0x170);
    if (jobj != NULL) {
        *gobj_ptr = GObj_Create(2, 3, 0);
        HSD_GObjObject_80390A70(*gobj_ptr, (u8) HSD_GObj_804D784A,
                                un_80306EEC(jobj, 0));
        GObj_SetupGXLink(*gobj_ptr, HSD_GObj_LObjCallback, 0x34, 0);
    }

    un_80307470(0);
    if (un_80304870() != 0) {
        memzero(&M2C_FIELD(data, u8*, 0), 0x2AC);
        un_80313774();
    }
    HSD_PadRenewStatus();
}

void un_803148E4(s32 arg0)
{
    char* data = un_804A2AC0;
    char* ptr1 = data + 0x2AC;
    void* archive = un_804D6ED8;
    char* ptr2 = data + 0x2C4;
    PAD_STACK(8);

    if (un_80304870() != 0) {
        if (arg0 != 0) {
            un_804A284C[0x12A] = M2C_FIELD(data, s16*, 0x298);
            un_804A284C[0x12B] = un_804D6EDC[M2C_FIELD(data, s16*, 0x298)];
            M2C_FIELD(un_804A284C, u8*, 1) = M2C_FIELD(data, u8*, 0x29B);
            M2C_FIELD(un_804A284C, u8*, 2) = M2C_FIELD(data, u8*, 0x29C);
            M2C_FIELD(un_804A284C, u8*, 3) = M2C_FIELD(ptr1, u8*, 0xC);
        } else {
            if (un_80304870() != 0) {
                s16 val = un_804D6EDC[M2C_FIELD(data, s16*, 0x298)];
                un_803067BC(0, 0);
                M2C_FIELD(data, u16*, 0x298) = un_803062BC(val);
            }
            un_804A284C[0x12A] = M2C_FIELD(data, s16*, 0x298);
            un_804A284C[0x12B] = un_804D6EDC[M2C_FIELD(data, s16*, 0x298)];
            M2C_FIELD(un_804A284C, u8*, 1) = 0;
            M2C_FIELD(un_804A284C, u8*, 2) = 0;
            M2C_FIELD(un_804A284C, u8*, 3) = 0;
        }

        if (un_80304924(un_804D6EDC[M2C_FIELD(data, s16*, 0x298)]) != 0) {
            un_80304988(un_804D6EDC[M2C_FIELD(data, s16*, 0x298)]);
        }
    }

    if (M2C_FIELD(data, void**, 0x27C) != NULL) {
        if (arg0 != 0) {
            HSD_GObjPLink_80390228(M2C_FIELD(data, HSD_GObj**, 0x27C));
        }
        M2C_FIELD(data, void**, 0x27C) = NULL;
    }

    if (arg0 != 0) {
        HSD_SisLib_803A5E70();
    }

    if (M2C_FIELD(archive, void**, 0) != NULL) {
        if (arg0 != 0) {
            HSD_GObjPLink_80390228(M2C_FIELD(archive, HSD_GObj**, 0));
        }
        M2C_FIELD(archive, void**, 0) = NULL;
    }

    if (M2C_FIELD(ptr2, void**, 0) != NULL && arg0 != 0) {
        HSD_GObjPLink_80390228(M2C_FIELD(ptr2, HSD_GObj**, 0));
    }

    if (M2C_FIELD(ptr1, void**, 0) != NULL) {
        HSD_GObjProc_8038FED4(M2C_FIELD(ptr1, HSD_GObj**, 0));
        if (arg0 != 0) {
            HSD_GObjPLink_80390228(M2C_FIELD(ptr1, HSD_GObj**, 0));
        }
    }

    if (M2C_FIELD(ptr1, void**, 4) != NULL && arg0 != 0) {
        HSD_GObjPLink_80390228(M2C_FIELD(ptr1, HSD_GObj**, 4));
    }
}
