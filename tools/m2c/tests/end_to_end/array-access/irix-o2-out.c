extern s32 *D_410110;

void test(struct A *a, s32 b) {
    D_410110 = a->array[b];
    D_410110 = (s32 *) &a->array[b];
    D_410110 = (s32 *) a->array2[b].x;
    D_410110 = &a->array2[b].x;
    D_410110 = (s32 *) a[b].y;
    D_410110 = (s32 *) a->array2[3].x;
    D_410110 = &a->array2[3].x;
}
