static float D_410150 = 1.23f; // single value
static float D_410154[3] = {3, 4, 5}; // array
static float D_410160[] = {6, 7, 8}; // VLA
static float D_410170[3]; // BSS

static const float D_400120[3] = {10, 11, 12}; // const array
static const float D_40012C[] = {14, 15, 16, 17, 18}; // const VLA

float test(int i) {
    // This is some random math to use all of the above values
    D_410170[i] = D_410160[i] + D_400120[i];
    D_410150 *= D_410170[i] * 5.67f + D_40012C[i];
    return D_410150 / D_410170[i];
}
