#include <math.h>
#include <placeholder.h>
#include <string.h>
#include <dolphin/mtx/vec.h>
#include <dolphin/os/os.h>
#include <baselib/mtx.h>
#include <baselib/robj.h>

HSD_ObjAllocData robj_alloc_data;   // robj_alloc_data
HSD_ObjAllocData rvalue_alloc_data; // rvalue_alloc_data

static u32 arg_buf;
static u32 arg_buf_size;

extern const f64 HSD_RObj_804DE6A0; // 1.75

void HSD_RObjInitAllocData(void)
{
    HSD_ObjAllocInit(&robj_alloc_data, sizeof(HSD_RObj), 4);
    HSD_ObjAllocInit(&rvalue_alloc_data, sizeof(HSD_Rvalue), 4);
}

HSD_ObjAllocData* HSD_RObjGetAllocData(void)
{
    return &robj_alloc_data;
}

HSD_ObjAllocData* HSD_RvalueObjGetAllocData(void)
{
    return &rvalue_alloc_data;
}

void HSD_RObjSetFlags(HSD_RObj* robj, u32 flags)
{
    if (robj != NULL) {
        robj->flags |= flags;
    }
}

HSD_RObj* HSD_RObjGetByType(HSD_RObj* robj, u32 type, u32 subtype)
{
    bool has_type;
    HSD_RObj* curr;

    if (robj == NULL) {
        return NULL;
    }

    for (curr = robj; curr != NULL; curr = curr->next) {
        if (curr->flags & 0x80000000) {
            has_type = true;
        } else {
            has_type = false;
        }

        if (has_type) {
            if ((curr->flags & ROBJ_TYPE_MASK) == type &&
                (!subtype || subtype == (curr->flags & 0xFFFFFFF)))
            {
                return curr;
            }
        }
    }

    return NULL;
}

static void RObjUpdateFunc(void* obj, enum_t type, HSD_ObjData* val)
{
    HSD_RObj* robj;

    if (obj == NULL) {
        return;
    }

    if (type != TYPE_ROBJ) {
        return;
    }

    robj = (HSD_RObj*) obj;
    if (val->fv >= HSD_RObj_804DE6A0) {
        robj->flags = robj->flags | 0x80000000;
        return;
    }
    robj->flags = robj->flags & 0x7fffffff;
}

void HSD_RObjAnim(HSD_RObj* robj)
{
    if (robj == NULL) {
        return;
    }

    HSD_AObjInterpretAnim(robj->aobj, robj, RObjUpdateFunc);
}

void HSD_RObjAnimAll(HSD_RObj* robj)
{
    HSD_RObj* curr;

    if (robj == NULL) {
        return;
    }

    for (curr = robj; curr != NULL; curr = curr->next) {
        HSD_RObjAnim(curr);
    }
}

void HSD_RObjRemoveAnimByFlags(HSD_RObj* robj, u32 flags)
{
    if (robj == NULL) {
        return;
    }

    if (robj->aobj != NULL && (flags & 0x80) != 0) {
        HSD_AObjRemove(robj->aobj);
        robj->aobj = NULL;
    }
}

void HSD_RObjRemoveAnimAllByFlags(HSD_RObj* robj, u32 flags)
{
    if (robj == NULL) {
        return;
    }

    for (; robj != NULL; robj = robj->next) {
        HSD_RObjRemoveAnimByFlags(robj, flags);
    }
}

void HSD_RObjRemoveAnimAll(HSD_RObj* robj)
{
    HSD_RObjRemoveAnimAllByFlags(robj, 0x7FF);
}

void HSD_RObjReqAnimByFlags(HSD_RObj* robj, f32 startframe, u32 flags)
{
    if (robj == NULL) {
        return;
    }

    if (robj->aobj != NULL && (flags & 0x80) != 0) {
        HSD_AObjReqAnim(robj->aobj, startframe);
    }
}

void HSD_RObjReqAnimAllByFlags(HSD_RObj* robj, f32 startframe, u32 flags)
{
    if (robj == NULL) {
        return;
    }

    for (; robj != NULL; robj = robj->next) {
        HSD_RObjReqAnimByFlags(robj, startframe, flags);
    }
}

void HSD_RObjReqAnimAll(HSD_RObj* robj, f32 startframe)
{
    HSD_RObjReqAnimAllByFlags(robj, startframe, 0x7FF);
}

void HSD_RObjAddAnim(HSD_RObj* robj, HSD_RObjAnimJoint* anim)
{
    if (robj == NULL || anim == NULL) {
        return;
    }

    if (robj->aobj != NULL) {
        HSD_AObjRemove(robj->aobj);
    }
    robj->aobj = HSD_AObjLoadDesc(anim->aobjdesc);
}

void HSD_RObjAddAnimAll(HSD_RObj* robj, HSD_RObjAnimJoint* anim)
{
    HSD_RObj* i;
    HSD_RObjAnimJoint* j;

    if (robj == NULL || anim == NULL) {
        return;
    }

    for (i = robj, j = anim; i != NULL && j != NULL; i = i->next, j = j->next)
    {
        HSD_RObjAddAnim(i, j);
    }
}

static u32 HSD_RObjGetConstraintType(HSD_RObj* robj)
{
    if (robj == NULL) {
        return 0;
    }

    return robj->flags & 0x0FFFFFFF;
}

int HSD_RObjGetGlobalPosition(HSD_RObj* robj, int type, Vec3* p)
{
    Vec3 v = { 0, 0, 0 };
    HSD_RObj* rp;
    int n = 0;

    if (robj == NULL) {
        return 0;
    }
    for (rp = robj; rp != NULL; rp = rp->next) {
        if (((rp->flags & ROBJ_TYPE_MASK) == REFTYPE_JOBJ ? 1 : 0) != 0) {
            if (((rp->flags & 0x80000000) ? 1 : 0) != 0 &&
                type == HSD_RObjGetConstraintType(rp))
            {
                HSD_ASSERT(498, rp->u.jobj);
                HSD_JObjSetupMatrix(rp->u.jobj);
                n += 1;
                v.x += rp->u.jobj->mtx[0][3];
                v.y += rp->u.jobj->mtx[1][3];
                v.z += rp->u.jobj->mtx[2][3];
            }
        }
    }
    if (n != 0) {
        f32 f = (f32) 1.0 / (f32) n;
        p->x = f * v.x;
        p->y = f * v.y;
        p->z = f * v.z;
    }
    return n;
}

static void set_dirup_matrix(Vec3* dir_ptr, Vec3* uv_ptr, Vec3* scale_ptr,
                             void* obj, HSD_ObjUpdateFunc update_func)
{
    Vec3 z_vec;
    Vec3 v;
    f32 kz;
    f32 kdir;

    PSVECCrossProduct(dir_ptr, uv_ptr, &z_vec);
    kdir =
        sqrtf(1.0F / (1.00000001335e-10f + PSVECDotProduct(dir_ptr, dir_ptr)));
    PSVECScale(dir_ptr, dir_ptr, kdir);
    kz = sqrtf(1.0F / (1.00000001335e-10f + PSVECDotProduct(&z_vec, &z_vec)));
    PSVECScale(&z_vec, &z_vec, kz);
    PSVECCrossProduct(&z_vec, dir_ptr, uv_ptr);
    v.x = dir_ptr->x * scale_ptr->x;
    v.y = dir_ptr->y * scale_ptr->x;
    v.z = dir_ptr->z * scale_ptr->x;
    update_func(obj, 50, (HSD_ObjData*) &v);
    v.x = uv_ptr->x * scale_ptr->y;
    v.y = uv_ptr->y * scale_ptr->y;
    v.z = uv_ptr->z * scale_ptr->y;
    update_func(obj, 51, (HSD_ObjData*) &v);
    v.x = z_vec.x * scale_ptr->z;
    v.y = z_vec.y * scale_ptr->z;
    v.z = z_vec.z * scale_ptr->z;
    update_func(obj, 52, (HSD_ObjData*) &v);
    update_func(obj, 55, NULL);
}

static void resolveCnsDirUp(HSD_RObj* robj, void* obj,
                            HSD_ObjUpdateFunc update_func)
{
    Vec3 this_scale = { 1.0f, 1.0f, 1.0f };
    Vec3 up = { 0.0f, 1.0f, 0.0f };
    Vec3 this_pos;
    Vec3 dir;
    f32 k;

    if (HSD_RObjGetGlobalPosition(robj, 2, &this_pos) != 0) {
        dir.x = ((HSD_JObj*) obj)->mtx[0][3];
        dir.y = ((HSD_JObj*) obj)->mtx[1][3];
        dir.z = ((HSD_JObj*) obj)->mtx[2][3];
        PSVECSubtract(&this_pos, &dir, &this_pos);
        if (HSD_RObjGetGlobalPosition(robj, 3, &up) != 0) {
            PSVECSubtract(&up, &dir, &up);
        } else {
            k = 1.0f - PSVECDotProduct(&this_pos, &up);
            if (fabsf_bitwise(k) < 1.00000001335e-10f) {
                up.x = 0.0f;
                up.y = 0.0f;
                up.z = 1.0;
            }
        }

        if (((HSD_JObj*) obj)->scl != NULL) {
            this_scale = *((HSD_JObj*) obj)->scl;
        }
        set_dirup_matrix(&this_pos, &up, &this_scale, obj, update_func);
    }
}

asm static void resolveCnsOrientation(HSD_RObj* robj, void* obj,
                                      HSD_ObjUpdateFunc update_func)
{ // clang-format off
    nofralloc
/* 8037B7B0 00378390  7C 08 02 A6 */	mflr r0
/* 8037B7B4 00378394  90 01 00 04 */	stw r0, 4(r1)
/* 8037B7B8 00378398  94 21 FF 08 */	stwu r1, -0xf8(r1)
/* 8037B7BC 0037839C  DB E1 00 F0 */	stfd f31, 0xf0(r1)
/* 8037B7C0 003783A0  DB C1 00 E8 */	stfd f30, 0xe8(r1)
/* 8037B7C4 003783A4  DB A1 00 E0 */	stfd f29, 0xe0(r1)
/* 8037B7C8 003783A8  DB 81 00 D8 */	stfd f28, 0xd8(r1)
/* 8037B7CC 003783AC  DB 61 00 D0 */	stfd f27, 0xd0(r1)
/* 8037B7D0 003783B0  BF 21 00 B4 */	stmw r25, 0xb4(r1)
/* 8037B7D4 003783B4  7C 9D 23 79 */	or. r29, r4, r4
/* 8037B7D8 003783B8  3B 23 00 00 */	addi r25, r3, 0
/* 8037B7DC 003783BC  3B C5 00 00 */	addi r30, r5, 0
/* 8037B7E0 003783C0  40 82 00 14 */	bne L_8037B7F4
/* 8037B7E4 003783C4  38 6D A8 18 */	addi r3, r13, HSD_RObj_804D5EB8
/* 8037B7E8 003783C8  38 80 02 76 */	li r4, 0x276
/* 8037B7EC 003783CC  38 AD A8 30 */	addi r5, r13, HSD_RObj_804D5ED0
/* 8037B7F0 003783D0  48 00 CA 31 */	bl __assert
L_8037B7F4:
/* 8037B7F4 003783D4  28 19 00 00 */	cmplwi r25, 0
/* 8037B7F8 003783D8  40 82 00 0C */	bne L_8037B804
/* 8037B7FC 003783DC  3B 80 00 00 */	li r28, 0
/* 8037B800 003783E0  48 00 00 5C */	b L_8037B85C
L_8037B804:
/* 8037B804 003783E4  7F 3C CB 78 */	mr r28, r25
/* 8037B808 003783E8  48 00 00 48 */	b L_8037B850
L_8037B80C:
/* 8037B80C 003783EC  80 9C 00 04 */	lwz r4, 4(r28)
/* 8037B810 003783F0  54 80 00 01 */	rlwinm. r0, r4, 0, 0, 0
/* 8037B814 003783F4  41 82 00 0C */	beq L_8037B820
/* 8037B818 003783F8  38 00 00 01 */	li r0, 1
/* 8037B81C 003783FC  48 00 00 08 */	b L_8037B824
L_8037B820:
/* 8037B820 00378400  38 00 00 00 */	li r0, 0
L_8037B824:
/* 8037B824 00378404  2C 00 00 00 */	cmpwi r0, 0
/* 8037B828 00378408  41 82 00 24 */	beq L_8037B84C
/* 8037B82C 0037840C  54 83 00 46 */	rlwinm r3, r4, 0, 1, 3
/* 8037B830 00378410  3C 03 F0 00 */	addis r0, r3, 0xf000
/* 8037B834 00378414  28 00 00 00 */	cmplwi r0, 0
/* 8037B838 00378418  40 82 00 14 */	bne L_8037B84C
/* 8037B83C 0037841C  54 80 01 3E */	clrlwi r0, r4, 4
/* 8037B840 00378420  28 00 00 04 */	cmplwi r0, 4
/* 8037B844 00378424  40 82 00 08 */	bne L_8037B84C
/* 8037B848 00378428  48 00 00 14 */	b L_8037B85C
L_8037B84C:
/* 8037B84C 0037842C  83 9C 00 00 */	lwz r28, 0(r28)
L_8037B850:
/* 8037B850 00378430  28 1C 00 00 */	cmplwi r28, 0
/* 8037B854 00378434  40 82 FF B8 */	bne L_8037B80C
/* 8037B858 00378438  3B 80 00 00 */	li r28, 0
L_8037B85C:
/* 8037B85C 0037843C  28 1C 00 00 */	cmplwi r28, 0
/* 8037B860 00378440  41 82 04 FC */	beq L_8037BD5C
/* 8037B864 00378444  80 7C 00 08 */	lwz r3, 8(r28)
/* 8037B868 00378448  4B FF 64 81 */	bl HSD_JObjGetFlags
/* 8037B86C 0037844C  54 60 07 39 */	rlwinm. r0, r3, 0, 0x1c, 0x1c
/* 8037B870 00378450  41 82 00 24 */	beq L_8037B894
/* 8037B874 00378454  83 5C 00 08 */	lwz r26, 8(r28)
/* 8037B878 00378458  28 1A 00 00 */	cmplwi r26, 0
/* 8037B87C 0037845C  40 82 00 0C */	bne L_8037B888
/* 8037B880 00378460  38 00 00 00 */	li r0, 0
/* 8037B884 00378464  48 00 00 08 */	b L_8037B88C
L_8037B888:
/* 8037B888 00378468  80 1A 00 0C */	lwz r0, 0xc(r26)
L_8037B88C:
/* 8037B88C 0037846C  28 00 00 00 */	cmplwi r0, 0
/* 8037B890 00378470  40 82 01 58 */	bne L_8037B9E8
L_8037B894:
/* 8037B894 00378474  83 5C 00 08 */	lwz r26, 8(r28)
/* 8037B898 00378478  28 1A 00 00 */	cmplwi r26, 0
/* 8037B89C 0037847C  40 82 00 14 */	bne L_8037B8B0
/* 8037B8A0 00378480  38 6D A8 20 */	addi r3, r13, HSD_RObj_804D5EC0
/* 8037B8A4 00378484  38 80 04 78 */	li r4, 0x478
/* 8037B8A8 00378488  38 AD A8 28 */	addi r5, r13, HSD_RObj_804D5EC8
/* 8037B8AC 0037848C  48 00 C9 75 */	bl __assert
L_8037B8B0:
/* 8037B8B0 00378490  7F 43 D3 78 */	mr r3, r26
/* 8037B8B4 00378494  4B C8 C4 B5 */	bl lbColl_JObjSetupMatrix
/* 8037B8B8 00378498  38 7A 00 44 */	addi r3, r26, 0x44
/* 8037B8BC 0037849C  38 81 00 80 */	addi r4, r1, 0x80
/* 8037B8C0 003784A0  4B FC 69 11 */	bl PSMTXCopy
/* 8037B8C4 003784A4  3B 20 00 00 */	li r25, 0
/* 8037B8C8 003784A8  C3 E2 EC D8 */	lfs f31, HSD_RObj_804DE6B8(r2)
/* 8037B8CC 003784AC  3C 60 80 40 */	lis r3, HSD_RObj_80406E74@ha
/* 8037B8D0 003784B0  C3 C2 EC C8 */	lfs f30, HSD_RObj_804DE6A8(r2)
/* 8037B8D4 003784B4  57 24 10 3A */	slwi r4, r25, 2
/* 8037B8D8 003784B8  C3 A2 EC DC */	lfs f29, HSD_RObj_804DE6BC(r2)
/* 8037B8DC 003784BC  38 03 6E 74 */	addi r0, r3, HSD_RObj_80406E74@l
/* 8037B8E0 003784C0  CB 82 EC C0 */	lfd f28, HSD_RObj_804DE6A0(r2)
/* 8037B8E4 003784C4  CB 62 EC E0 */	lfd f27, HSD_RObj_804DE6C0(r2)
/* 8037B8E8 003784C8  7F E0 22 14 */	add r31, r0, r4
/* 8037B8EC 003784CC  3B 9D 00 00 */	addi r28, r29, 0
/* 8037B8F0 003784D0  3B 61 00 80 */	addi r27, r1, 0x80
L_8037B8F4:
/* 8037B8F4 003784D4  C0 1B 00 00 */	lfs f0, 0(r27)
/* 8037B8F8 003784D8  38 61 00 70 */	addi r3, r1, 0x70
/* 8037B8FC 003784DC  D0 01 00 70 */	stfs f0, 0x70(r1)
/* 8037B900 003784E0  C0 1B 00 10 */	lfs f0, 0x10(r27)
/* 8037B904 003784E4  D0 01 00 74 */	stfs f0, 0x74(r1)
/* 8037B908 003784E8  C0 1B 00 20 */	lfs f0, 0x20(r27)
/* 8037B90C 003784EC  D0 01 00 78 */	stfs f0, 0x78(r1)
/* 8037B910 003784F0  4B FC 74 ED */	bl PSVECMag
/* 8037B914 003784F4  FC 01 F8 40 */	fcmpo cr0, f1, f31
/* 8037B918 003784F8  40 81 00 08 */	ble L_8037B920
/* 8037B91C 003784FC  EC 3E 08 24 */	fdivs f1, f30, f1
L_8037B920:
/* 8037B920 00378500  C0 5C 00 54 */	lfs f2, 0x54(r28)
/* 8037B924 00378504  C0 1C 00 44 */	lfs f0, 0x44(r28)
/* 8037B928 00378508  EC 42 00 B2 */	fmuls f2, f2, f2
/* 8037B92C 0037850C  C0 7C 00 64 */	lfs f3, 0x64(r28)
/* 8037B930 00378510  EC 00 00 32 */	fmuls f0, f0, f0
/* 8037B934 00378514  EC 63 00 F2 */	fmuls f3, f3, f3
/* 8037B938 00378518  EC 02 00 2A */	fadds f0, f2, f0
/* 8037B93C 0037851C  EC 63 00 2A */	fadds f3, f3, f0
/* 8037B940 00378520  FC 03 E8 40 */	fcmpo cr0, f3, f29
/* 8037B944 00378524  40 81 00 48 */	ble L_8037B98C
/* 8037B948 00378528  FC 40 18 34 */	frsqrte f2, f3
/* 8037B94C 0037852C  FC 02 00 B2 */	fmul f0, f2, f2
/* 8037B950 00378530  FC 5C 00 B2 */	fmul f2, f28, f2
/* 8037B954 00378534  FC 03 D8 3C */	fnmsub f0, f3, f0, f27
/* 8037B958 00378538  FC 42 00 32 */	fmul f2, f2, f0
/* 8037B95C 0037853C  FC 02 00 B2 */	fmul f0, f2, f2
/* 8037B960 00378540  FC 5C 00 B2 */	fmul f2, f28, f2
/* 8037B964 00378544  FC 03 D8 3C */	fnmsub f0, f3, f0, f27
/* 8037B968 00378548  FC 42 00 32 */	fmul f2, f2, f0
/* 8037B96C 0037854C  FC 02 00 B2 */	fmul f0, f2, f2
/* 8037B970 00378550  FC 5C 00 B2 */	fmul f2, f28, f2
/* 8037B974 00378554  FC 03 D8 3C */	fnmsub f0, f3, f0, f27
/* 8037B978 00378558  FC 02 00 32 */	fmul f0, f2, f0
/* 8037B97C 0037855C  FC 03 00 32 */	fmul f0, f3, f0
/* 8037B980 00378560  FC 00 00 18 */	frsp f0, f0
/* 8037B984 00378564  D0 01 00 38 */	stfs f0, 0x38(r1)
/* 8037B988 00378568  C0 61 00 38 */	lfs f3, 0x38(r1)
L_8037B98C:
/* 8037B98C 0037856C  EC 21 00 F2 */	fmuls f1, f1, f3
/* 8037B990 00378570  C0 01 00 70 */	lfs f0, 0x70(r1)
/* 8037B994 00378574  39 9E 00 00 */	addi r12, r30, 0
/* 8037B998 00378578  7D 88 03 A6 */	mtlr r12
/* 8037B99C 0037857C  38 7D 00 00 */	addi r3, r29, 0
/* 8037B9A0 00378580  EC 00 00 72 */	fmuls f0, f0, f1
/* 8037B9A4 00378584  38 A1 00 70 */	addi r5, r1, 0x70
/* 8037B9A8 00378588  D0 01 00 70 */	stfs f0, 0x70(r1)
/* 8037B9AC 0037858C  C0 01 00 74 */	lfs f0, 0x74(r1)
/* 8037B9B0 00378590  EC 00 00 72 */	fmuls f0, f0, f1
/* 8037B9B4 00378594  D0 01 00 74 */	stfs f0, 0x74(r1)
/* 8037B9B8 00378598  C0 01 00 78 */	lfs f0, 0x78(r1)
/* 8037B9BC 0037859C  EC 00 00 72 */	fmuls f0, f0, f1
/* 8037B9C0 003785A0  D0 01 00 78 */	stfs f0, 0x78(r1)
/* 8037B9C4 003785A4  80 9F 00 00 */	lwz r4, 0(r31)
/* 8037B9C8 003785A8  4E 80 00 21 */	blrl
/* 8037B9CC 003785AC  3B 39 00 01 */	addi r25, r25, 1
/* 8037B9D0 003785B0  2C 19 00 03 */	cmpwi r25, 3
/* 8037B9D4 003785B4  3B 7B 00 04 */	addi r27, r27, 4
/* 8037B9D8 003785B8  3B 9C 00 04 */	addi r28, r28, 4
/* 8037B9DC 003785BC  3B FF 00 04 */	addi r31, r31, 4
/* 8037B9E0 003785C0  41 80 FF 14 */	blt L_8037B8F4
/* 8037B9E4 003785C4  48 00 03 60 */	b L_8037BD44
L_8037B9E8:
/* 8037B9E8 003785C8  28 1A 00 00 */	cmplwi r26, 0
/* 8037B9EC 003785CC  40 82 00 0C */	bne L_8037B9F8
/* 8037B9F0 003785D0  3B E0 00 00 */	li r31, 0
/* 8037B9F4 003785D4  48 00 00 08 */	b L_8037B9FC
L_8037B9F8:
/* 8037B9F8 003785D8  83 FA 00 0C */	lwz r31, 0xc(r26)
L_8037B9FC:
/* 8037B9FC 003785DC  28 1A 00 00 */	cmplwi r26, 0
/* 8037BA00 003785E0  40 82 00 14 */	bne L_8037BA14
/* 8037BA04 003785E4  38 6D A8 20 */	addi r3, r13, HSD_RObj_804D5EC0
/* 8037BA08 003785E8  38 80 04 78 */	li r4, 0x478
/* 8037BA0C 003785EC  38 AD A8 28 */	addi r5, r13, HSD_RObj_804D5EC8
/* 8037BA10 003785F0  48 00 C8 11 */	bl __assert
L_8037BA14:
/* 8037BA14 003785F4  7F 43 D3 78 */	mr r3, r26
/* 8037BA18 003785F8  4B C8 C3 51 */	bl lbColl_JObjSetupMatrix
/* 8037BA1C 003785FC  28 1F 00 00 */	cmplwi r31, 0
/* 8037BA20 00378600  3B 7A 00 44 */	addi r27, r26, 0x44
/* 8037BA24 00378604  40 82 00 14 */	bne L_8037BA38
/* 8037BA28 00378608  38 6D A8 20 */	addi r3, r13, HSD_RObj_804D5EC0
/* 8037BA2C 0037860C  38 80 04 78 */	li r4, 0x478
/* 8037BA30 00378610  38 AD A8 28 */	addi r5, r13, HSD_RObj_804D5EC8
/* 8037BA34 00378614  48 00 C7 ED */	bl __assert
L_8037BA38:
/* 8037BA38 00378618  7F E3 FB 78 */	mr r3, r31
/* 8037BA3C 0037861C  4B C8 C3 2D */	bl lbColl_JObjSetupMatrix
/* 8037BA40 00378620  38 7F 00 44 */	addi r3, r31, 0x44
/* 8037BA44 00378624  38 9B 00 00 */	addi r4, r27, 0
/* 8037BA48 00378628  38 A1 00 40 */	addi r5, r1, 0x40
/* 8037BA4C 0037862C  4B FF DB 4D */	bl HSD_MtxInverseConcat
/* 8037BA50 00378630  3B E1 00 40 */	addi r31, r1, 0x40
/* 8037BA54 00378634  C3 62 EC D8 */	lfs f27, HSD_RObj_804DE6B8(r2)
/* 8037BA58 00378638  C3 82 EC C8 */	lfs f28, HSD_RObj_804DE6A8(r2)
/* 8037BA5C 0037863C  7F FB FB 78 */	mr r27, r31
/* 8037BA60 00378640  C3 A2 EC DC */	lfs f29, HSD_RObj_804DE6BC(r2)
/* 8037BA64 00378644  7F BA EB 78 */	mr r26, r29
/* 8037BA68 00378648  CB C2 EC C0 */	lfd f30, HSD_RObj_804DE6A0(r2)
/* 8037BA6C 0037864C  CB E2 EC E0 */	lfd f31, HSD_RObj_804DE6C0(r2)
/* 8037BA70 00378650  3B 20 00 00 */	li r25, 0
L_8037BA74:
/* 8037BA74 00378654  C0 1B 00 00 */	lfs f0, 0(r27)
/* 8037BA78 00378658  38 61 00 70 */	addi r3, r1, 0x70
/* 8037BA7C 0037865C  D0 01 00 70 */	stfs f0, 0x70(r1)
/* 8037BA80 00378660  C0 1B 00 10 */	lfs f0, 0x10(r27)
/* 8037BA84 00378664  D0 01 00 74 */	stfs f0, 0x74(r1)
/* 8037BA88 00378668  C0 1B 00 20 */	lfs f0, 0x20(r27)
/* 8037BA8C 0037866C  D0 01 00 78 */	stfs f0, 0x78(r1)
/* 8037BA90 00378670  4B FC 73 6D */	bl PSVECMag
/* 8037BA94 00378674  FC 01 D8 40 */	fcmpo cr0, f1, f27
/* 8037BA98 00378678  40 81 00 08 */	ble L_8037BAA0
/* 8037BA9C 0037867C  EC 3C 08 24 */	fdivs f1, f28, f1
L_8037BAA0:
/* 8037BAA0 00378680  C0 5A 00 54 */	lfs f2, 0x54(r26)
/* 8037BAA4 00378684  C0 1A 00 44 */	lfs f0, 0x44(r26)
/* 8037BAA8 00378688  EC 42 00 B2 */	fmuls f2, f2, f2
/* 8037BAAC 0037868C  C0 7A 00 64 */	lfs f3, 0x64(r26)
/* 8037BAB0 00378690  EC 00 00 32 */	fmuls f0, f0, f0
/* 8037BAB4 00378694  EC 63 00 F2 */	fmuls f3, f3, f3
/* 8037BAB8 00378698  EC 02 00 2A */	fadds f0, f2, f0
/* 8037BABC 0037869C  EC 63 00 2A */	fadds f3, f3, f0
/* 8037BAC0 003786A0  FC 03 E8 40 */	fcmpo cr0, f3, f29
/* 8037BAC4 003786A4  40 81 00 48 */	ble L_8037BB0C
/* 8037BAC8 003786A8  FC 40 18 34 */	frsqrte f2, f3
/* 8037BACC 003786AC  FC 02 00 B2 */	fmul f0, f2, f2
/* 8037BAD0 003786B0  FC 5E 00 B2 */	fmul f2, f30, f2
/* 8037BAD4 003786B4  FC 03 F8 3C */	fnmsub f0, f3, f0, f31
/* 8037BAD8 003786B8  FC 42 00 32 */	fmul f2, f2, f0
/* 8037BADC 003786BC  FC 02 00 B2 */	fmul f0, f2, f2
/* 8037BAE0 003786C0  FC 5E 00 B2 */	fmul f2, f30, f2
/* 8037BAE4 003786C4  FC 03 F8 3C */	fnmsub f0, f3, f0, f31
/* 8037BAE8 003786C8  FC 42 00 32 */	fmul f2, f2, f0
/* 8037BAEC 003786CC  FC 02 00 B2 */	fmul f0, f2, f2
/* 8037BAF0 003786D0  FC 5E 00 B2 */	fmul f2, f30, f2
/* 8037BAF4 003786D4  FC 03 F8 3C */	fnmsub f0, f3, f0, f31
/* 8037BAF8 003786D8  FC 02 00 32 */	fmul f0, f2, f0
/* 8037BAFC 003786DC  FC 03 00 32 */	fmul f0, f3, f0
/* 8037BB00 003786E0  FC 00 00 18 */	frsp f0, f0
/* 8037BB04 003786E4  D0 01 00 34 */	stfs f0, 0x34(r1)
/* 8037BB08 003786E8  C0 61 00 34 */	lfs f3, 0x34(r1)
L_8037BB0C:
/* 8037BB0C 003786EC  EC 21 00 F2 */	fmuls f1, f1, f3
/* 8037BB10 003786F0  C0 01 00 70 */	lfs f0, 0x70(r1)
/* 8037BB14 003786F4  3B 39 00 01 */	addi r25, r25, 1
/* 8037BB18 003786F8  2C 19 00 03 */	cmpwi r25, 3
/* 8037BB1C 003786FC  EC 00 00 72 */	fmuls f0, f0, f1
/* 8037BB20 00378700  3B 5A 00 04 */	addi r26, r26, 4
/* 8037BB24 00378704  D0 01 00 70 */	stfs f0, 0x70(r1)
/* 8037BB28 00378708  C0 01 00 74 */	lfs f0, 0x74(r1)
/* 8037BB2C 0037870C  EC 00 00 72 */	fmuls f0, f0, f1
/* 8037BB30 00378710  D0 01 00 74 */	stfs f0, 0x74(r1)
/* 8037BB34 00378714  C0 01 00 78 */	lfs f0, 0x78(r1)
/* 8037BB38 00378718  EC 00 00 72 */	fmuls f0, f0, f1
/* 8037BB3C 0037871C  D0 01 00 78 */	stfs f0, 0x78(r1)
/* 8037BB40 00378720  C0 01 00 70 */	lfs f0, 0x70(r1)
/* 8037BB44 00378724  D0 1B 00 00 */	stfs f0, 0(r27)
/* 8037BB48 00378728  C0 01 00 74 */	lfs f0, 0x74(r1)
/* 8037BB4C 0037872C  D0 1B 00 10 */	stfs f0, 0x10(r27)
/* 8037BB50 00378730  C0 01 00 78 */	lfs f0, 0x78(r1)
/* 8037BB54 00378734  D0 1B 00 20 */	stfs f0, 0x20(r27)
/* 8037BB58 00378738  3B 7B 00 04 */	addi r27, r27, 4
/* 8037BB5C 0037873C  41 80 FF 18 */	blt L_8037BA74
/* 8037BB60 00378740  80 7C 00 08 */	lwz r3, 8(r28)
/* 8037BB64 00378744  28 03 00 00 */	cmplwi r3, 0
/* 8037BB68 00378748  40 82 00 0C */	bne L_8037BB74
/* 8037BB6C 0037874C  38 00 00 00 */	li r0, 0
/* 8037BB70 00378750  48 00 00 08 */	b L_8037BB78
L_8037BB74:
/* 8037BB74 00378754  80 03 00 0C */	lwz r0, 0xc(r3)
L_8037BB78:
/* 8037BB78 00378758  C3 82 EC D8 */	lfs f28, HSD_RObj_804DE6B8(r2)
/* 8037BB7C 0037875C  7C 19 03 78 */	mr r25, r0
/* 8037BB80 00378760  C3 62 EC C8 */	lfs f27, HSD_RObj_804DE6A8(r2)
/* 8037BB84 00378764  48 00 01 60 */	b L_8037BCE4
L_8037BB88:
/* 8037BB88 00378768  28 19 00 00 */	cmplwi r25, 0
/* 8037BB8C 0037876C  40 82 00 0C */	bne L_8037BB98
/* 8037BB90 00378770  38 00 00 00 */	li r0, 0
/* 8037BB94 00378774  48 00 00 08 */	b L_8037BB9C
L_8037BB98:
/* 8037BB98 00378778  80 19 00 0C */	lwz r0, 0xc(r25)
L_8037BB9C:
/* 8037BB9C 0037877C  28 00 00 00 */	cmplwi r0, 0
/* 8037BBA0 00378780  41 82 00 70 */	beq L_8037BC10
/* 8037BBA4 00378784  28 19 00 00 */	cmplwi r25, 0
/* 8037BBA8 00378788  40 82 00 0C */	bne L_8037BBB4
/* 8037BBAC 0037878C  3B 80 00 00 */	li r28, 0
/* 8037BBB0 00378790  48 00 00 08 */	b L_8037BBB8
L_8037BBB4:
/* 8037BBB4 00378794  83 99 00 0C */	lwz r28, 0xc(r25)
L_8037BBB8:
/* 8037BBB8 00378798  28 19 00 00 */	cmplwi r25, 0
/* 8037BBBC 0037879C  40 82 00 14 */	bne L_8037BBD0
/* 8037BBC0 003787A0  38 6D A8 20 */	addi r3, r13, HSD_RObj_804D5EC0
/* 8037BBC4 003787A4  38 80 04 78 */	li r4, 0x478
/* 8037BBC8 003787A8  38 AD A8 28 */	addi r5, r13, HSD_RObj_804D5EC8
/* 8037BBCC 003787AC  48 00 C6 55 */	bl __assert
L_8037BBD0:
/* 8037BBD0 003787B0  7F 23 CB 78 */	mr r3, r25
/* 8037BBD4 003787B4  4B C8 C1 95 */	bl lbColl_JObjSetupMatrix
/* 8037BBD8 003787B8  28 1C 00 00 */	cmplwi r28, 0
/* 8037BBDC 003787BC  3B 79 00 44 */	addi r27, r25, 0x44
/* 8037BBE0 003787C0  40 82 00 14 */	bne L_8037BBF4
/* 8037BBE4 003787C4  38 6D A8 20 */	addi r3, r13, HSD_RObj_804D5EC0
/* 8037BBE8 003787C8  38 80 04 78 */	li r4, 0x478
/* 8037BBEC 003787CC  38 AD A8 28 */	addi r5, r13, HSD_RObj_804D5EC8
/* 8037BBF0 003787D0  48 00 C6 31 */	bl __assert
L_8037BBF4:
/* 8037BBF4 003787D4  7F 83 E3 78 */	mr r3, r28
/* 8037BBF8 003787D8  4B C8 C1 71 */	bl lbColl_JObjSetupMatrix
/* 8037BBFC 003787DC  38 7C 00 44 */	addi r3, r28, 0x44
/* 8037BC00 003787E0  38 9B 00 00 */	addi r4, r27, 0
/* 8037BC04 003787E4  38 A1 00 80 */	addi r5, r1, 0x80
/* 8037BC08 003787E8  4B FF D9 91 */	bl HSD_MtxInverseConcat
/* 8037BC0C 003787EC  48 00 00 30 */	b L_8037BC3C
L_8037BC10:
/* 8037BC10 003787F0  28 19 00 00 */	cmplwi r25, 0
/* 8037BC14 003787F4  40 82 00 14 */	bne L_8037BC28
/* 8037BC18 003787F8  38 6D A8 20 */	addi r3, r13, HSD_RObj_804D5EC0
/* 8037BC1C 003787FC  38 80 04 78 */	li r4, 0x478
/* 8037BC20 00378800  38 AD A8 28 */	addi r5, r13, HSD_RObj_804D5EC8
/* 8037BC24 00378804  48 00 C5 FD */	bl __assert
L_8037BC28:
/* 8037BC28 00378808  7F 23 CB 78 */	mr r3, r25
/* 8037BC2C 0037880C  4B C8 C1 3D */	bl lbColl_JObjSetupMatrix
/* 8037BC30 00378810  38 79 00 44 */	addi r3, r25, 0x44
/* 8037BC34 00378814  38 81 00 80 */	addi r4, r1, 0x80
/* 8037BC38 00378818  4B FC 65 99 */	bl PSMTXCopy
L_8037BC3C:
/* 8037BC3C 0037881C  3B 60 00 00 */	li r27, 0
/* 8037BC40 00378820  3B 41 00 80 */	addi r26, r1, 0x80
L_8037BC44:
/* 8037BC44 00378824  C0 1A 00 00 */	lfs f0, 0(r26)
/* 8037BC48 00378828  38 61 00 70 */	addi r3, r1, 0x70
/* 8037BC4C 0037882C  D0 01 00 70 */	stfs f0, 0x70(r1)
/* 8037BC50 00378830  C0 1A 00 10 */	lfs f0, 0x10(r26)
/* 8037BC54 00378834  D0 01 00 74 */	stfs f0, 0x74(r1)
/* 8037BC58 00378838  C0 1A 00 20 */	lfs f0, 0x20(r26)
/* 8037BC5C 0037883C  D0 01 00 78 */	stfs f0, 0x78(r1)
/* 8037BC60 00378840  4B FC 71 9D */	bl PSVECMag
/* 8037BC64 00378844  FC 01 E0 40 */	fcmpo cr0, f1, f28
/* 8037BC68 00378848  40 81 00 08 */	ble L_8037BC70
/* 8037BC6C 0037884C  EC 3B 08 24 */	fdivs f1, f27, f1
L_8037BC70:
/* 8037BC70 00378850  C0 01 00 70 */	lfs f0, 0x70(r1)
/* 8037BC74 00378854  3B 7B 00 01 */	addi r27, r27, 1
/* 8037BC78 00378858  2C 1B 00 03 */	cmpwi r27, 3
/* 8037BC7C 0037885C  EC 00 00 72 */	fmuls f0, f0, f1
/* 8037BC80 00378860  D0 01 00 70 */	stfs f0, 0x70(r1)
/* 8037BC84 00378864  C0 01 00 74 */	lfs f0, 0x74(r1)
/* 8037BC88 00378868  EC 00 00 72 */	fmuls f0, f0, f1
/* 8037BC8C 0037886C  D0 01 00 74 */	stfs f0, 0x74(r1)
/* 8037BC90 00378870  C0 01 00 78 */	lfs f0, 0x78(r1)
/* 8037BC94 00378874  EC 00 00 72 */	fmuls f0, f0, f1
/* 8037BC98 00378878  D0 01 00 78 */	stfs f0, 0x78(r1)
/* 8037BC9C 0037887C  C0 01 00 70 */	lfs f0, 0x70(r1)
/* 8037BCA0 00378880  D0 1A 00 00 */	stfs f0, 0(r26)
/* 8037BCA4 00378884  C0 01 00 74 */	lfs f0, 0x74(r1)
/* 8037BCA8 00378888  D0 1A 00 10 */	stfs f0, 0x10(r26)
/* 8037BCAC 0037888C  C0 01 00 78 */	lfs f0, 0x78(r1)
/* 8037BCB0 00378890  D0 1A 00 20 */	stfs f0, 0x20(r26)
/* 8037BCB4 00378894  3B 5A 00 04 */	addi r26, r26, 4
/* 8037BCB8 00378898  41 80 FF 8C */	blt L_8037BC44
/* 8037BCBC 0037889C  38 81 00 40 */	addi r4, r1, 0x40
/* 8037BCC0 003788A0  38 A4 00 00 */	addi r5, r4, 0
/* 8037BCC4 003788A4  38 61 00 80 */	addi r3, r1, 0x80
/* 8037BCC8 003788A8  4B FC 65 3D */	bl PSMTXConcat
/* 8037BCCC 003788AC  28 19 00 00 */	cmplwi r25, 0
/* 8037BCD0 003788B0  40 82 00 0C */	bne L_8037BCDC
/* 8037BCD4 003788B4  38 00 00 00 */	li r0, 0
/* 8037BCD8 003788B8  48 00 00 08 */	b L_8037BCE0
L_8037BCDC:
/* 8037BCDC 003788BC  80 19 00 0C */	lwz r0, 0xc(r25)
L_8037BCE0:
/* 8037BCE0 003788C0  7C 19 03 78 */	mr r25, r0
L_8037BCE4:
/* 8037BCE4 003788C4  28 19 00 00 */	cmplwi r25, 0
/* 8037BCE8 003788C8  40 82 FE A0 */	bne L_8037BB88
/* 8037BCEC 003788CC  3B 60 00 00 */	li r27, 0
/* 8037BCF0 003788D0  3C 60 80 40 */	lis r3, HSD_RObj_80406E74@ha
/* 8037BCF4 003788D4  57 64 10 3A */	slwi r4, r27, 2
/* 8037BCF8 003788D8  38 03 6E 74 */	addi r0, r3, HSD_RObj_80406E74@l
/* 8037BCFC 003788DC  7F 40 22 14 */	add r26, r0, r4
L_8037BD00:
/* 8037BD00 003788E0  C0 1F 00 00 */	lfs f0, 0(r31)
/* 8037BD04 003788E4  39 9E 00 00 */	addi r12, r30, 0
/* 8037BD08 003788E8  7D 88 03 A6 */	mtlr r12
/* 8037BD0C 003788EC  38 7D 00 00 */	addi r3, r29, 0
/* 8037BD10 003788F0  D0 01 00 70 */	stfs f0, 0x70(r1)
/* 8037BD14 003788F4  38 A1 00 70 */	addi r5, r1, 0x70
/* 8037BD18 003788F8  C0 1F 00 10 */	lfs f0, 0x10(r31)
/* 8037BD1C 003788FC  D0 01 00 74 */	stfs f0, 0x74(r1)
/* 8037BD20 00378900  C0 1F 00 20 */	lfs f0, 0x20(r31)
/* 8037BD24 00378904  D0 01 00 78 */	stfs f0, 0x78(r1)
/* 8037BD28 00378908  80 9A 00 00 */	lwz r4, 0(r26)
/* 8037BD2C 0037890C  4E 80 00 21 */	blrl
/* 8037BD30 00378910  3B 7B 00 01 */	addi r27, r27, 1
/* 8037BD34 00378914  2C 1B 00 03 */	cmpwi r27, 3
/* 8037BD38 00378918  3B FF 00 04 */	addi r31, r31, 4
/* 8037BD3C 0037891C  3B 5A 00 04 */	addi r26, r26, 4
/* 8037BD40 00378920  41 80 FF C0 */	blt L_8037BD00
L_8037BD44:
/* 8037BD44 00378924  39 9E 00 00 */	addi r12, r30, 0
/* 8037BD48 00378928  7D 88 03 A6 */	mtlr r12
/* 8037BD4C 0037892C  38 7D 00 00 */	addi r3, r29, 0
/* 8037BD50 00378930  38 80 00 37 */	li r4, 0x37
/* 8037BD54 00378934  38 A0 00 00 */	li r5, 0
/* 8037BD58 00378938  4E 80 00 21 */	blrl
L_8037BD5C:
/* 8037BD5C 0037893C  BB 21 00 B4 */	lmw r25, 0xb4(r1)
/* 8037BD60 00378940  80 01 00 FC */	lwz r0, 0xfc(r1)
/* 8037BD64 00378944  CB E1 00 F0 */	lfd f31, 0xf0(r1)
/* 8037BD68 00378948  CB C1 00 E8 */	lfd f30, 0xe8(r1)
/* 8037BD6C 0037894C  CB A1 00 E0 */	lfd f29, 0xe0(r1)
/* 8037BD70 00378950  CB 81 00 D8 */	lfd f28, 0xd8(r1)
/* 8037BD74 00378954  CB 61 00 D0 */	lfd f27, 0xd0(r1)
/* 8037BD78 00378958  38 21 00 F8 */	addi r1, r1, 0xf8
/* 8037BD7C 0037895C  7C 08 03 A6 */	mtlr r0
/* 8037BD80 00378960  4E 80 00 20 */	blr
} // clang-format on

static void resolveLimits(HSD_RObj* robj, void* obj)
{
    HSD_JObj* jobj = (HSD_JObj*) obj;
    HSD_RObj* rp;
    bool update_mtx = false;

    HSD_ASSERT(0x2E1, jobj);

    rp = robj;
    while (rp != NULL) {
        if (RObjHasLimitReftype(rp)) {
            break;
        }
        rp = rp->next;
    }

    if (rp != NULL) {
        for (rp = robj; rp != NULL; rp = rp->next) {
            if (RObjHasLimitReftype(rp)) {
                switch (rp->flags & 0xFFFFFFF) {
                default:
                    continue;
                case 1:
                    if (jobj->rotate.x < rp->u.limit) {
                        jobj->rotate.x = rp->u.limit;
                    }
                    break;

                case 2:
                    if (jobj->rotate.x > rp->u.limit) {
                        (jobj->rotate).x = rp->u.limit;
                    }
                    break;

                case 3:
                    if (jobj->rotate.y < rp->u.limit) {
                        jobj->rotate.y = rp->u.limit;
                    }
                    break;

                case 4:
                    if (jobj->rotate.y > rp->u.limit) {
                        jobj->rotate.y = rp->u.limit;
                    }
                    break;

                case 5:
                    if (jobj->rotate.z < rp->u.limit) {
                        jobj->rotate.z = rp->u.limit;
                    }
                    break;

                case 6:
                    if (jobj->rotate.z > rp->u.limit) {
                        jobj->rotate.z = rp->u.limit;
                    }
                    break;

                case 7:
                    if (jobj->translate.x < rp->u.limit) {
                        jobj->translate.x = rp->u.limit;
                    }
                    break;

                case 8:
                    if (jobj->translate.x > rp->u.limit) {
                        jobj->translate.x = rp->u.limit;
                    }
                    break;

                case 9:
                    if (jobj->translate.y < rp->u.limit) {
                        jobj->translate.y = rp->u.limit;
                    }
                    break;

                case 10:
                    if (jobj->translate.y > rp->u.limit) {
                        jobj->translate.y = rp->u.limit;
                    }
                    break;

                case 11:
                    if (jobj->translate.y < rp->u.limit) {
                        jobj->translate.y = rp->u.limit;
                    }
                    break;

                case 12:
                    if (jobj->translate.y > rp->u.limit) {
                        jobj->translate.y = rp->u.limit;
                    }
                    break;
                }
                update_mtx = true;
            }
        }
        if (update_mtx) {
            HSD_JObjMakeMatrix(jobj);
        }
    }
}

static void expEvaluate(HSD_Exp* exp, u32 type, void* obj,
                        HSD_ObjUpdateFunc update_func);

void HSD_RObjUpdateAll(HSD_RObj* robj, void* obj,
                       HSD_ObjUpdateFunc update_func)
{
    HSD_RObj* rp;
    Vec3 vec;

    if (robj != NULL) {
        if (HSD_RObjGetGlobalPosition(robj, 1, &vec) != 0) {
            update_func(obj, 0x35, (HSD_ObjData*) &vec);
            update_func(obj, 0x38, NULL);
        }
        resolveCnsDirUp(robj, obj, update_func);
        resolveCnsOrientation(robj, obj, update_func);
        resolveLimits(robj, obj);

        for (rp = robj; rp != NULL; rp = rp->next) {
            if (RObjHasFlags(rp) && RObjHasFlags2(rp)) {
                expEvaluate(&rp->u.exp, rp->flags & 0xFFFFFFF, obj,
                            update_func);
            }
        }
    }
}

void HSD_RObjResolveRefs(HSD_RObj* robj, HSD_RObjDesc* desc)
{
    if (robj != NULL && desc != NULL) {
        switch (desc->flags & ROBJ_TYPE_MASK) {
        case REFTYPE_JOBJ:
            HSD_JObjUnrefThis(robj->u.jobj);
            robj->u.jobj = HSD_IDGetData((u32) desc->u.joint, NULL);
            HSD_ASSERT(883, robj->u.jobj);
            if (robj->u.jobj != NULL) {
                iref_INC(robj->u.jobj);
            }
            break;
        case 0x0:
            HSD_RvalueResolveRefsAll(robj->u.exp.rvalue, desc->u.exp->rvalue);
            break;
        }
    }
}

void HSD_RObjResolveRefsAll(HSD_RObj* robj, HSD_RObjDesc* desc)
{
    for (; robj != NULL && desc != NULL; robj = robj->next, desc = desc->next)
    {
        HSD_RObjResolveRefs(robj, desc);
    }
}

static void bcexpLoadDesc(HSD_Exp* exp, HSD_ByteCodeExpDesc* desc);
static void expLoadDesc(HSD_Exp* exp, HSD_ExpDesc* desc);

HSD_RObj* HSD_RObjLoadDesc(HSD_RObjDesc* robjdesc)
{
    HSD_RObj* robj;

    if (robjdesc != NULL) {
        robj = HSD_RObjAlloc();
        robj->next = HSD_RObjLoadDesc((HSD_RObjDesc*) robjdesc->next);
        robj->flags = robjdesc->flags;
        switch (robj->flags & 0x70000000) {
        case REFTYPE_JOBJ:
            break;
        case REFTYPE_LIMIT: {
            switch (robj->flags & 0xFFFFFFF) {
            case 1:
            case 2:
            case 3:
            case 4:
            case 5:
            case 6:
                robj->u.limit = 0.01754533f * robjdesc->u.limit;
                break;
            default:
                robj->u.limit = robjdesc->u.limit;
                break;
            }
        } break;
        case REFTYPE_EXP:
            expLoadDesc(&robj->u.exp, robjdesc->u.exp);
            break;
        case REFTYPE_BYTECODE:
            bcexpLoadDesc(&robj->u.exp, robjdesc->u.bcexp);
            robj->flags &= 0x8FFFFFFF;
            break;
        case REFTYPE_IKHINT:
            robj->u.ik_hint.bone_length = robjdesc->u.ik_hint->bone_length;
            robj->u.ik_hint.rotate_x = robjdesc->u.ik_hint->rotate_x;
            break;
        default:
            HSD_Panic(__FILE__, 0x3C0, "unexpected type of robj.\n");
            break;
        }
        return robj;
    }
    return NULL;
}

void HSD_RObjRemove(HSD_RObj* robj)
{
    s32 flags;

    if (robj != NULL) {
        switch (robj->flags & ROBJ_TYPE_MASK) {
        case REFTYPE_JOBJ:
            HSD_JObjUnrefThis(robj->u.jobj);
            break;
        case 0x0:
            HSD_RvalueRemoveAll(robj->u.exp.rvalue);
            break;
        }
        HSD_AObjRemove(robj->aobj);
        HSD_RObjFree(robj);
    }
}

void HSD_RObjRemoveAll(HSD_RObj* robj)
{
    HSD_RObj* next;

    for (; robj != NULL; robj = next) {
        next = robj->next;
        HSD_RObjRemove(robj);
    }
}

HSD_RObj* HSD_RObjAlloc(void)
{
    HSD_RObj* new = HSD_ObjAlloc(&robj_alloc_data);
    HSD_ASSERT(1032, new);
    memset(new, 0, 0x1C);
    return new;
}

void HSD_RObjFree(HSD_RObj* robj)
{
    HSD_ObjFree(&robj_alloc_data, robj);
}

asm static void expEvaluate(HSD_Exp* exp, u32 type, void* obj,
                            HSD_ObjUpdateFunc update_func)
{ // clang-format off
    nofralloc
/* 8037C4CC 003790AC  7C 08 02 A6 */	mflr r0
/* 8037C4D0 003790B0  90 01 00 04 */	stw r0, 4(r1)
/* 8037C4D4 003790B4  94 21 FF 68 */	stwu r1, -0x98(r1)
/* 8037C4D8 003790B8  DB E1 00 90 */	stfd f31, 0x90(r1)
/* 8037C4DC 003790BC  BD E1 00 4C */	stmw r15, 0x4c(r1)
/* 8037C4E0 003790C0  7C 7A 1B 78 */	mr r26, r3
/* 8037C4E4 003790C4  3B 64 00 00 */	addi r27, r4, 0
/* 8037C4E8 003790C8  3B 85 00 00 */	addi r28, r5, 0
/* 8037C4EC 003790CC  3B A6 00 00 */	addi r29, r6, 0
/* 8037C4F0 003790D0  80 63 00 08 */	lwz r3, 8(r3)
/* 8037C4F4 003790D4  3C 03 00 01 */	addis r0, r3, 1
/* 8037C4F8 003790D8  28 00 FF FF */	cmplwi r0, 0xffff
/* 8037C4FC 003790DC  40 82 00 2C */	bne L_8037C528
/* 8037C500 003790E0  82 1A 00 04 */	lwz r16, 4(r26)
/* 8037C504 003790E4  39 E0 00 00 */	li r15, 0
/* 8037C508 003790E8  48 00 00 14 */	b L_8037C51C
L_8037C50C:
/* 8037C50C 003790EC  80 70 00 04 */	lwz r3, 4(r16)
/* 8037C510 003790F0  4B FF E2 DD */	bl HSD_GetNbBits
/* 8037C514 003790F4  7D EF 1A 14 */	add r15, r15, r3
/* 8037C518 003790F8  82 10 00 00 */	lwz r16, 0(r16)
L_8037C51C:
/* 8037C51C 003790FC  28 10 00 00 */	cmplwi r16, 0
/* 8037C520 00379100  40 82 FF EC */	bne L_8037C50C
/* 8037C524 00379104  91 FA 00 08 */	stw r15, 8(r26)
L_8037C528:
/* 8037C528 00379108  80 0D C0 48 */	lwz r0, arg_buf(r13)
/* 8037C52C 0037910C  28 00 00 00 */	cmplwi r0, 0
/* 8037C530 00379110  40 82 00 28 */	bne L_8037C558
/* 8037C534 00379114  80 0D C0 4C */	lwz r0, arg_buf_size(r13)
/* 8037C538 00379118  28 00 00 00 */	cmplwi r0, 0
/* 8037C53C 0037911C  40 82 00 0C */	bne L_8037C548
/* 8037C540 00379120  38 00 00 64 */	li r0, 0x64
/* 8037C544 00379124  90 0D C0 4C */	stw r0, arg_buf_size(r13)
L_8037C548:
/* 8037C548 00379128  80 0D C0 4C */	lwz r0, arg_buf_size(r13)
/* 8037C54C 0037912C  54 03 10 3A */	slwi r3, r0, 2
/* 8037C550 00379130  48 00 2C 95 */	bl HSD_MemAlloc
/* 8037C554 00379134  90 6D C0 48 */	stw r3, arg_buf(r13)
L_8037C558:
/* 8037C558 00379138  80 AD C0 4C */	lwz r5, arg_buf_size(r13)
/* 8037C55C 0037913C  80 9A 00 08 */	lwz r4, 8(r26)
/* 8037C560 00379140  7C 05 20 40 */	cmplw r5, r4
/* 8037C564 00379144  40 80 00 24 */	bge L_8037C588
/* 8037C568 00379148  3C 60 80 40 */	lis r3, HSD_RObj_80406F2C@ha
/* 8037C56C 0037914C  4C C6 31 82 */	crclr 6
/* 8037C570 00379150  38 63 6F 2C */	addi r3, r3, HSD_RObj_80406F2C@l
/* 8037C574 00379154  4B FC 91 35 */	bl OSReport
/* 8037C578 00379158  38 6D A8 18 */	addi r3, r13, HSD_RObj_804D5EB8
/* 8037C57C 0037915C  38 80 04 5E */	li r4, 0x45e
/* 8037C580 00379160  38 AD A8 38 */	addi r5, r13, HSD_RObj_804D5ED8
/* 8037C584 00379164  48 00 BC F5 */	bl HSD_Panic
L_8037C588:
/* 8037C588 00379168  83 CD C0 48 */	lwz r30, arg_buf(r13)
/* 8037C58C 0037916C  3F 20 02 00 */	lis r25, 0x200
/* 8037C590 00379170  83 FA 00 04 */	lwz r31, 4(r26)
/* 8037C594 00379174  3F 00 00 40 */	lis r24, 0x40
/* 8037C598 00379178  C3 E2 EC EC */	lfs f31, HSD_RObj_804DE6CC(r2)
/* 8037C59C 0037917C  3E C0 01 00 */	lis r22, 0x100
/* 8037C5A0 00379180  3E E0 00 80 */	lis r23, 0x80
/* 8037C5A4 00379184  3E A0 00 04 */	lis r21, 4
/* 8037C5A8 00379188  3E 80 00 10 */	lis r20, 0x10
/* 8037C5AC 0037918C  3E 20 00 20 */	lis r17, 0x20
/* 8037C5B0 00379190  3E 40 00 02 */	lis r18, 2
/* 8037C5B4 00379194  3E 60 00 01 */	lis r19, 1
/* 8037C5B8 00379198  48 00 03 0C */	b L_8037C8C4
L_8037C5BC:
/* 8037C5BC 0037919C  82 1F 00 08 */	lwz r16, 8(r31)
/* 8037C5C0 003791A0  28 10 00 00 */	cmplwi r16, 0
/* 8037C5C4 003791A4  40 82 00 14 */	bne L_8037C5D8
/* 8037C5C8 003791A8  38 6D A8 18 */	addi r3, r13, HSD_RObj_804D5EB8
/* 8037C5CC 003791AC  38 80 04 67 */	li r4, 0x467
/* 8037C5D0 003791B0  38 AD A8 28 */	addi r5, r13, HSD_RObj_804D5EC8
/* 8037C5D4 003791B4  48 00 BC 4D */	bl __assert
L_8037C5D8:
/* 8037C5D8 003791B8  81 FF 00 08 */	lwz r15, 8(r31)
/* 8037C5DC 003791BC  28 0F 00 00 */	cmplwi r15, 0
/* 8037C5E0 003791C0  41 82 00 44 */	beq L_8037C624
/* 8037C5E4 003791C4  40 82 00 14 */	bne L_8037C5F8
/* 8037C5E8 003791C8  38 6D A8 20 */	addi r3, r13, HSD_RObj_804D5EC0
/* 8037C5EC 003791CC  38 80 02 34 */	li r4, 0x234
/* 8037C5F0 003791D0  38 AD A8 28 */	addi r5, r13, HSD_RObj_804D5EC8
/* 8037C5F4 003791D4  48 00 BC 2D */	bl __assert
L_8037C5F8:
/* 8037C5F8 003791D8  80 8F 00 14 */	lwz r4, 0x14(r15)
/* 8037C5FC 003791DC  38 60 00 00 */	li r3, 0
/* 8037C600 003791E0  54 80 02 11 */	rlwinm. r0, r4, 0, 8, 8
/* 8037C604 003791E4  40 82 00 10 */	bne L_8037C614
/* 8037C608 003791E8  54 80 06 73 */	rlwinm. r0, r4, 0, 0x19, 0x19
/* 8037C60C 003791EC  41 82 00 08 */	beq L_8037C614
/* 8037C610 003791F0  38 60 00 01 */	li r3, 1
L_8037C614:
/* 8037C614 003791F4  2C 03 00 00 */	cmpwi r3, 0
/* 8037C618 003791F8  41 82 00 0C */	beq L_8037C624
/* 8037C61C 003791FC  7D E3 7B 78 */	mr r3, r15
/* 8037C620 00379200  4B FF 6A 59 */	bl HSD_JObjSetupMatrixSub
L_8037C624:
/* 8037C624 00379204  39 E0 00 01 */	li r15, 1
/* 8037C628 00379208  48 00 02 84 */	b L_8037C8AC
L_8037C62C:
/* 8037C62C 0037920C  7C 00 78 38 */	and r0, r0, r15
/* 8037C630 00379210  2C 00 04 00 */	cmpwi r0, 0x400
/* 8037C634 00379214  41 82 02 74 */	beq L_8037C8A8
/* 8037C638 00379218  40 80 00 7C */	bge L_8037C6B4
/* 8037C63C 0037921C  2C 00 00 20 */	cmpwi r0, 0x20
/* 8037C640 00379220  41 82 01 38 */	beq L_8037C778
/* 8037C644 00379224  40 80 00 40 */	bge L_8037C684
/* 8037C648 00379228  2C 00 00 04 */	cmpwi r0, 4
/* 8037C64C 0037922C  41 82 01 08 */	beq L_8037C754
/* 8037C650 00379230  40 80 00 1C */	bge L_8037C66C
/* 8037C654 00379234  2C 00 00 02 */	cmpwi r0, 2
/* 8037C658 00379238  41 82 00 E8 */	beq L_8037C740
/* 8037C65C 0037923C  40 80 02 4C */	bge L_8037C8A8
/* 8037C660 00379240  2C 00 00 01 */	cmpwi r0, 1
/* 8037C664 00379244  40 80 00 C8 */	bge L_8037C72C
/* 8037C668 00379248  48 00 02 40 */	b L_8037C8A8
L_8037C66C:
/* 8037C66C 0037924C  2C 00 00 10 */	cmpwi r0, 0x10
/* 8037C670 00379250  41 82 00 F8 */	beq L_8037C768
/* 8037C674 00379254  40 80 02 34 */	bge L_8037C8A8
/* 8037C678 00379258  2C 00 00 08 */	cmpwi r0, 8
/* 8037C67C 0037925C  41 82 02 2C */	beq L_8037C8A8
/* 8037C680 00379260  48 00 02 28 */	b L_8037C8A8
L_8037C684:
/* 8037C684 00379264  2C 00 01 00 */	cmpwi r0, 0x100
/* 8037C688 00379268  41 82 01 20 */	beq L_8037C7A8
/* 8037C68C 0037926C  40 80 00 1C */	bge L_8037C6A8
/* 8037C690 00379270  2C 00 00 80 */	cmpwi r0, 0x80
/* 8037C694 00379274  41 82 01 04 */	beq L_8037C798
/* 8037C698 00379278  40 80 02 10 */	bge L_8037C8A8
/* 8037C69C 0037927C  2C 00 00 40 */	cmpwi r0, 0x40
/* 8037C6A0 00379280  41 82 00 E8 */	beq L_8037C788
/* 8037C6A4 00379284  48 00 02 04 */	b L_8037C8A8
L_8037C6A8:
/* 8037C6A8 00379288  2C 00 02 00 */	cmpwi r0, 0x200
/* 8037C6AC 0037928C  41 82 01 0C */	beq L_8037C7B8
/* 8037C6B0 00379290  48 00 01 F8 */	b L_8037C8A8
L_8037C6B4:
/* 8037C6B4 00379294  7C 00 88 00 */	cmpw r0, r17
/* 8037C6B8 00379298  41 82 01 80 */	beq L_8037C838
/* 8037C6BC 0037929C  40 80 00 40 */	bge L_8037C6FC
/* 8037C6C0 003792A0  7C 00 90 00 */	cmpw r0, r18
/* 8037C6C4 003792A4  41 82 01 24 */	beq L_8037C7E8
/* 8037C6C8 003792A8  40 80 00 1C */	bge L_8037C6E4
/* 8037C6CC 003792AC  7C 00 98 00 */	cmpw r0, r19
/* 8037C6D0 003792B0  41 82 00 F8 */	beq L_8037C7C8
/* 8037C6D4 003792B4  40 80 01 D4 */	bge L_8037C8A8
/* 8037C6D8 003792B8  2C 00 08 00 */	cmpwi r0, 0x800
/* 8037C6DC 003792BC  41 82 01 CC */	beq L_8037C8A8
/* 8037C6E0 003792C0  48 00 01 C8 */	b L_8037C8A8
L_8037C6E4:
/* 8037C6E4 003792C4  7C 00 A0 00 */	cmpw r0, r20
/* 8037C6E8 003792C8  41 82 01 40 */	beq L_8037C828
/* 8037C6EC 003792CC  40 80 01 BC */	bge L_8037C8A8
/* 8037C6F0 003792D0  7C 00 A8 00 */	cmpw r0, r21
/* 8037C6F4 003792D4  41 82 01 14 */	beq L_8037C808
/* 8037C6F8 003792D8  48 00 01 B0 */	b L_8037C8A8
L_8037C6FC:
/* 8037C6FC 003792DC  7C 00 B0 00 */	cmpw r0, r22
/* 8037C700 003792E0  41 82 01 74 */	beq L_8037C874
/* 8037C704 003792E4  40 80 00 1C */	bge L_8037C720
/* 8037C708 003792E8  7C 00 B8 00 */	cmpw r0, r23
/* 8037C70C 003792EC  41 82 01 4C */	beq L_8037C858
/* 8037C710 003792F0  40 80 01 98 */	bge L_8037C8A8
/* 8037C714 003792F4  7C 00 C0 00 */	cmpw r0, r24
/* 8037C718 003792F8  41 82 01 30 */	beq L_8037C848
/* 8037C71C 003792FC  48 00 01 8C */	b L_8037C8A8
L_8037C720:
/* 8037C720 00379300  7C 00 C8 00 */	cmpw r0, r25
/* 8037C724 00379304  41 82 01 6C */	beq L_8037C890
/* 8037C728 00379308  48 00 01 80 */	b L_8037C8A8
L_8037C72C:
/* 8037C72C 0037930C  C0 10 00 1C */	lfs f0, 0x1c(r16)
/* 8037C730 00379310  EC 1F 00 32 */	fmuls f0, f31, f0
/* 8037C734 00379314  D0 1E 00 00 */	stfs f0, 0(r30)
/* 8037C738 00379318  3B DE 00 04 */	addi r30, r30, 4
/* 8037C73C 0037931C  48 00 01 6C */	b L_8037C8A8
L_8037C740:
/* 8037C740 00379320  C0 10 00 20 */	lfs f0, 0x20(r16)
/* 8037C744 00379324  EC 1F 00 32 */	fmuls f0, f31, f0
/* 8037C748 00379328  D0 1E 00 00 */	stfs f0, 0(r30)
/* 8037C74C 0037932C  3B DE 00 04 */	addi r30, r30, 4
/* 8037C750 00379330  48 00 01 58 */	b L_8037C8A8
L_8037C754:
/* 8037C754 00379334  C0 10 00 24 */	lfs f0, 0x24(r16)
/* 8037C758 00379338  EC 1F 00 32 */	fmuls f0, f31, f0
/* 8037C75C 0037933C  D0 1E 00 00 */	stfs f0, 0(r30)
/* 8037C760 00379340  3B DE 00 04 */	addi r30, r30, 4
/* 8037C764 00379344  48 00 01 44 */	b L_8037C8A8
L_8037C768:
/* 8037C768 00379348  C0 10 00 38 */	lfs f0, 0x38(r16)
/* 8037C76C 0037934C  D0 1E 00 00 */	stfs f0, 0(r30)
/* 8037C770 00379350  3B DE 00 04 */	addi r30, r30, 4
/* 8037C774 00379354  48 00 01 34 */	b L_8037C8A8
L_8037C778:
/* 8037C778 00379358  C0 10 00 3C */	lfs f0, 0x3c(r16)
/* 8037C77C 0037935C  D0 1E 00 00 */	stfs f0, 0(r30)
/* 8037C780 00379360  3B DE 00 04 */	addi r30, r30, 4
/* 8037C784 00379364  48 00 01 24 */	b L_8037C8A8
L_8037C788:
/* 8037C788 00379368  C0 10 00 40 */	lfs f0, 0x40(r16)
/* 8037C78C 0037936C  D0 1E 00 00 */	stfs f0, 0(r30)
/* 8037C790 00379370  3B DE 00 04 */	addi r30, r30, 4
/* 8037C794 00379374  48 00 01 14 */	b L_8037C8A8
L_8037C798:
/* 8037C798 00379378  C0 10 00 2C */	lfs f0, 0x2c(r16)
/* 8037C79C 0037937C  D0 1E 00 00 */	stfs f0, 0(r30)
/* 8037C7A0 00379380  3B DE 00 04 */	addi r30, r30, 4
/* 8037C7A4 00379384  48 00 01 04 */	b L_8037C8A8
L_8037C7A8:
/* 8037C7A8 00379388  C0 10 00 30 */	lfs f0, 0x30(r16)
/* 8037C7AC 0037938C  D0 1E 00 00 */	stfs f0, 0(r30)
/* 8037C7B0 00379390  3B DE 00 04 */	addi r30, r30, 4
/* 8037C7B4 00379394  48 00 00 F4 */	b L_8037C8A8
L_8037C7B8:
/* 8037C7B8 00379398  C0 10 00 34 */	lfs f0, 0x34(r16)
/* 8037C7BC 0037939C  D0 1E 00 00 */	stfs f0, 0(r30)
/* 8037C7C0 003793A0  3B DE 00 04 */	addi r30, r30, 4
/* 8037C7C4 003793A4  48 00 00 E4 */	b L_8037C8A8
L_8037C7C8:
/* 8037C7C8 003793A8  38 70 00 44 */	addi r3, r16, 0x44
/* 8037C7CC 003793AC  38 81 00 2C */	addi r4, r1, 0x2c
/* 8037C7D0 003793B0  4B FF D4 55 */	bl HSD_MtxGetRotation
/* 8037C7D4 003793B4  C0 01 00 2C */	lfs f0, 0x2c(r1)
/* 8037C7D8 003793B8  EC 1F 00 32 */	fmuls f0, f31, f0
/* 8037C7DC 003793BC  D0 1E 00 00 */	stfs f0, 0(r30)
/* 8037C7E0 003793C0  3B DE 00 04 */	addi r30, r30, 4
/* 8037C7E4 003793C4  48 00 00 C4 */	b L_8037C8A8
L_8037C7E8:
/* 8037C7E8 003793C8  38 70 00 44 */	addi r3, r16, 0x44
/* 8037C7EC 003793CC  38 81 00 2C */	addi r4, r1, 0x2c
/* 8037C7F0 003793D0  4B FF D4 35 */	bl HSD_MtxGetRotation
/* 8037C7F4 003793D4  C0 01 00 30 */	lfs f0, 0x30(r1)
/* 8037C7F8 003793D8  EC 1F 00 32 */	fmuls f0, f31, f0
/* 8037C7FC 003793DC  D0 1E 00 00 */	stfs f0, 0(r30)
/* 8037C800 003793E0  3B DE 00 04 */	addi r30, r30, 4
/* 8037C804 003793E4  48 00 00 A4 */	b L_8037C8A8
L_8037C808:
/* 8037C808 003793E8  38 70 00 44 */	addi r3, r16, 0x44
/* 8037C80C 003793EC  38 81 00 2C */	addi r4, r1, 0x2c
/* 8037C810 003793F0  4B FF D4 15 */	bl HSD_MtxGetRotation
/* 8037C814 003793F4  C0 01 00 34 */	lfs f0, 0x34(r1)
/* 8037C818 003793F8  EC 1F 00 32 */	fmuls f0, f31, f0
/* 8037C81C 003793FC  D0 1E 00 00 */	stfs f0, 0(r30)
/* 8037C820 00379400  3B DE 00 04 */	addi r30, r30, 4
/* 8037C824 00379404  48 00 00 84 */	b L_8037C8A8
L_8037C828:
/* 8037C828 00379408  C0 10 00 50 */	lfs f0, 0x50(r16)
/* 8037C82C 0037940C  D0 1E 00 00 */	stfs f0, 0(r30)
/* 8037C830 00379410  3B DE 00 04 */	addi r30, r30, 4
/* 8037C834 00379414  48 00 00 74 */	b L_8037C8A8
L_8037C838:
/* 8037C838 00379418  C0 10 00 60 */	lfs f0, 0x60(r16)
/* 8037C83C 0037941C  D0 1E 00 00 */	stfs f0, 0(r30)
/* 8037C840 00379420  3B DE 00 04 */	addi r30, r30, 4
/* 8037C844 00379424  48 00 00 64 */	b L_8037C8A8
L_8037C848:
/* 8037C848 00379428  C0 10 00 70 */	lfs f0, 0x70(r16)
/* 8037C84C 0037942C  D0 1E 00 00 */	stfs f0, 0(r30)
/* 8037C850 00379430  3B DE 00 04 */	addi r30, r30, 4
/* 8037C854 00379434  48 00 00 54 */	b L_8037C8A8
L_8037C858:
/* 8037C858 00379438  38 70 00 44 */	addi r3, r16, 0x44
/* 8037C85C 0037943C  38 81 00 3C */	addi r4, r1, 0x3c
/* 8037C860 00379440  4B FF D7 29 */	bl HSD_MtxGetScale
/* 8037C864 00379444  C0 01 00 3C */	lfs f0, 0x3c(r1)
/* 8037C868 00379448  D0 1E 00 00 */	stfs f0, 0(r30)
/* 8037C86C 0037944C  3B DE 00 04 */	addi r30, r30, 4
/* 8037C870 00379450  48 00 00 38 */	b L_8037C8A8
L_8037C874:
/* 8037C874 00379454  38 70 00 44 */	addi r3, r16, 0x44
/* 8037C878 00379458  38 81 00 3C */	addi r4, r1, 0x3c
/* 8037C87C 0037945C  4B FF D7 0D */	bl HSD_MtxGetScale
/* 8037C880 00379460  C0 01 00 40 */	lfs f0, 0x40(r1)
/* 8037C884 00379464  D0 1E 00 00 */	stfs f0, 0(r30)
/* 8037C888 00379468  3B DE 00 04 */	addi r30, r30, 4
/* 8037C88C 0037946C  48 00 00 1C */	b L_8037C8A8
L_8037C890:
/* 8037C890 00379470  38 70 00 44 */	addi r3, r16, 0x44
/* 8037C894 00379474  38 81 00 3C */	addi r4, r1, 0x3c
/* 8037C898 00379478  4B FF D6 F1 */	bl HSD_MtxGetScale
/* 8037C89C 0037947C  C0 01 00 44 */	lfs f0, 0x44(r1)
/* 8037C8A0 00379480  D0 1E 00 00 */	stfs f0, 0(r30)
/* 8037C8A4 00379484  3B DE 00 04 */	addi r30, r30, 4
L_8037C8A8:
/* 8037C8A8 00379488  55 EF 08 3C */	slwi r15, r15, 1
L_8037C8AC:
/* 8037C8AC 0037948C  2C 0F 00 00 */	cmpwi r15, 0
/* 8037C8B0 00379490  41 82 00 10 */	beq L_8037C8C0
/* 8037C8B4 00379494  80 1F 00 04 */	lwz r0, 4(r31)
/* 8037C8B8 00379498  7C 0F 00 40 */	cmplw r15, r0
/* 8037C8BC 0037949C  40 81 FD 70 */	ble L_8037C62C
L_8037C8C0:
/* 8037C8C0 003794A0  83 FF 00 00 */	lwz r31, 0(r31)
L_8037C8C4:
/* 8037C8C4 003794A4  28 1F 00 00 */	cmplwi r31, 0
/* 8037C8C8 003794A8  40 82 FC F4 */	bne L_8037C5BC
/* 8037C8CC 003794AC  88 1A 00 0C */	lbz r0, 0xc(r26)
/* 8037C8D0 003794B0  28 00 00 00 */	cmplwi r0, 0
/* 8037C8D4 003794B4  41 82 00 1C */	beq L_8037C8F0
/* 8037C8D8 003794B8  80 7A 00 00 */	lwz r3, 0(r26)
/* 8037C8DC 003794BC  80 8D C0 48 */	lwz r4, arg_buf(r13)
/* 8037C8E0 003794C0  80 BA 00 08 */	lwz r5, 8(r26)
/* 8037C8E4 003794C4  48 00 3C F9 */	bl HSD_ByteCodeEval
/* 8037C8E8 003794C8  D0 21 00 1C */	stfs f1, 0x1c(r1)
/* 8037C8EC 003794CC  48 00 00 18 */	b L_8037C904
L_8037C8F0:
/* 8037C8F0 003794D0  81 9A 00 00 */	lwz r12, 0(r26)
/* 8037C8F4 003794D4  80 6D C0 48 */	lwz r3, arg_buf(r13)
/* 8037C8F8 003794D8  7D 88 03 A6 */	mtlr r12
/* 8037C8FC 003794DC  4E 80 00 21 */	blrl
/* 8037C900 003794E0  D0 21 00 1C */	stfs f1, 0x1c(r1)
L_8037C904:
/* 8037C904 003794E4  38 1B FF FF */	addi r0, r27, -1
/* 8037C908 003794E8  28 00 00 02 */	cmplwi r0, 2
/* 8037C90C 003794EC  41 81 00 14 */	bgt L_8037C920
/* 8037C910 003794F0  C0 22 EC E8 */	lfs f1, HSD_RObj_804DE6C8(r2)
/* 8037C914 003794F4  C0 01 00 1C */	lfs f0, 0x1c(r1)
/* 8037C918 003794F8  EC 01 00 32 */	fmuls f0, f1, f0
/* 8037C91C 003794FC  D0 01 00 1C */	stfs f0, 0x1c(r1)
L_8037C920:
/* 8037C920 00379500  39 9D 00 00 */	addi r12, r29, 0
/* 8037C924 00379504  7D 88 03 A6 */	mtlr r12
/* 8037C928 00379508  38 7C 00 00 */	addi r3, r28, 0
/* 8037C92C 0037950C  38 9B 00 00 */	addi r4, r27, 0
/* 8037C930 00379510  38 A1 00 1C */	addi r5, r1, 0x1c
/* 8037C934 00379514  4E 80 00 21 */	blrl
/* 8037C938 00379518  B9 E1 00 4C */	lmw r15, 0x4c(r1)
/* 8037C93C 0037951C  80 01 00 9C */	lwz r0, 0x9c(r1)
/* 8037C940 00379520  CB E1 00 90 */	lfd f31, 0x90(r1)
/* 8037C944 00379524  38 21 00 98 */	addi r1, r1, 0x98
/* 8037C948 00379528  7C 08 03 A6 */	mtlr r0
/* 8037C94C 0037952C  4E 80 00 20 */	blr
} // clang-format on

static f32 dummy_func(void)
{
    return 0.0f;
}

HSD_Rvalue* HSD_RvalueAlloc(void)
{
    HSD_Rvalue* rvalue = HSD_ObjAlloc(&rvalue_alloc_data);
    HSD_ASSERT(1224, rvalue);
    memset(rvalue, 0, sizeof(HSD_Rvalue));
    return rvalue;
}

void HSD_RvalueRemove(HSD_Rvalue* rvalue)
{
    if (rvalue != NULL) {
        HSD_JObjUnrefThis(rvalue->jobj);
        HSD_ObjFree(&rvalue_alloc_data, rvalue);
    }
}

void HSD_RvalueRemoveAll(HSD_Rvalue* rvalue)
{
    HSD_Rvalue* next;

    for (; rvalue != NULL; rvalue = next) {
        next = rvalue->next;
        HSD_RvalueRemove(rvalue);
    }
}

static HSD_Rvalue* loadRvalue(HSD_RvalueList* list)
{
    HSD_Rvalue* rp;
    HSD_SList rv;

    rv.next = NULL;
    rp = (HSD_Rvalue*) &rv;
    if (list == NULL) {
        return NULL;
    } else {
        for (; list->joint != NULL; list++) {
            rp->next = HSD_RvalueAlloc();
            rp->next->flags = list->flags;
            rp = rp->next;
        }
    }
    return (HSD_Rvalue*) rv.next;
}

static void expLoadDesc(HSD_Exp* exp, HSD_ExpDesc* desc)
{
    memset(exp, 0, sizeof(HSD_Exp));
    if (desc != NULL) {
        if (desc->func != NULL) {
            exp->expr.func = dummy_func;
        } else {
            exp->expr.func = NULL;
        }
        exp->rvalue = loadRvalue(desc->rvalue);
        exp->nb_args = -1;
    }
}

static void bcexpLoadDesc(HSD_Exp* exp, HSD_ByteCodeExpDesc* desc)
{
    memset(exp, 0, sizeof(HSD_Exp));
    if (desc != NULL) {
        if (desc->bytecode != NULL) {
            exp->expr.bytecode = desc->bytecode;
        } else {
            exp->expr.bytecode = NULL;
        }
        exp->rvalue = loadRvalue(desc->rvalue);
        exp->nb_args = -1;
        exp->is_bytecode = 1;
    }
}

void HSD_RvalueResolveRefs(HSD_Rvalue* rvalue, HSD_RvalueList* list)
{
    if (rvalue != NULL && list != NULL) {
        HSD_JObjUnrefThis(rvalue->jobj);
        rvalue->jobj = HSD_IDGetData((u32) list->joint, NULL);
        HSD_ASSERT(1333, rvalue->jobj);
        iref_INC(rvalue->jobj);
    }
}

void HSD_RvalueResolveRefsAll(HSD_Rvalue* rvalue, HSD_RvalueList* list)
{
    if (list == NULL) {
        return;
    }
    for (; rvalue != NULL && list->joint != NULL;
         rvalue = rvalue->next, list++)
    {
        HSD_RvalueResolveRefs(rvalue, list);
    }
}

static inline void ref_JObj(HSD_RObj* robj, HSD_JObj* o)
{
    HSD_JObj* jobj;
    bool isDesc;

    if (isDesc = hsdObjIsDescendantOf(&o->object, &hsdJObj.parent.parent),
        isDesc != 0)
    {
        robj->u.jobj = o;
        iref_INC(o);
    } else {
        OSReport("constraint only support jobj target.\n");
        HSD_ASSERT(1376, 0);
    }
}

void HSD_RObjSetConstraintObj(HSD_RObj* robj, void* obj)
{
    HSD_JObj* jobj;

    if (robj != NULL) {
        if (robj->u.jobj != NULL) {
            HSD_JObjUnrefThis(robj->u.jobj);
            robj->u.jobj = NULL;
        }

        ref_JObj(robj, obj);
    }
}

void _HSD_RObjForgetMemory(void* low, void* high)
{
    if (((u32) low <= arg_buf) && (arg_buf < (u32) high)) {
        arg_buf = 0U;
        arg_buf_size = 0U;
    }
}
