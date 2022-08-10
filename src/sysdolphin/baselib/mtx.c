#include "sysdolphin/baselib/mtx.h"


#define EPSILON 0.0000000001f
#define FLOAT_MIN  1.1754943E-38f

HSD_ObjAllocData lbl_804C2310;
HSD_ObjAllocData lbl_804C233C;


//Calculates the determinant of the top 3x3 section of a 3x4 matrix
inline f32 HSD_CalcDeterminantMatrix3x4(Mtx m)
{
    return m[0][0]*m[1][1]*m[2][2] + m[0][1]*m[1][2]*m[2][0] + m[0][2]*m[1][0]*m[2][1] 
    - m[2][0]*m[1][1]*m[0][2]  - m[1][0]*m[0][1]*m[2][2] - m[0][0]*m[2][1]*m[1][2];
}

void func_80379310(Mtx src, Mtx dest)
{
    Mtx tempMatrix;
    Mtx* m;
    f32 det = HSD_CalcDeterminantMatrix3x4(src);

    if (fabsf_bitwise(det) < EPSILON) {
        PSMTXIdentity(dest);
        return;
    }

    if (src == dest) {
        PSMTXCopy(src, tempMatrix);
        m = &tempMatrix;
    } else {
        m = (Mtx*)src;
    }

    det = 1.0f/det;

    dest[0][0] = ((*m)[1][1] * (*m)[2][2] - (*m)[2][1] * (*m)[1][2]) * det;
    dest[0][1] = -((*m)[0][1] * (*m)[2][2] - (*m)[2][1] * (*m)[0][2]) * det;
    dest[0][2] = ((*m)[0][1] * (*m)[1][2] - (*m)[1][1] * (*m)[0][2]) * det;
    dest[1][0] = -((*m)[1][0] * (*m)[2][2] - (*m)[2][0] * (*m)[1][2]) * det;
    dest[1][1] = ((*m)[0][0] * (*m)[2][2] - (*m)[2][0] * (*m)[0][2]) * det;
    dest[1][2] =  -((*m)[0][0] * (*m)[1][2] - (*m)[1][0] * (*m)[0][2]) * det;
    dest[2][0] = ((*m)[1][0] * (*m)[2][1] - (*m)[2][0] * (*m)[1][1]) * det;
    dest[2][1] = -((*m)[0][0] * (*m)[2][1] - (*m)[2][0] * (*m)[0][1]) * det;
    dest[2][2] = ((*m)[0][0] * (*m)[1][1] - (*m)[1][0] * (*m)[0][1]) * det;

    dest[0][3] = -(dest[0][2] * src[2][3] - (-dest[0][0] * src[0][3] - dest[0][1] * src[1][3]));
    dest[1][3] = -(dest[1][2] * src[2][3] - (-dest[1][0] * src[0][3] - dest[1][1] * src[1][3]));
    dest[2][3] = -(dest[2][2] * src[2][3] - (-dest[2][0] * src[0][3] - dest[2][1] * src[1][3]));
}

//https://decomp.me/scratch/kalJY
void HSD_MtxInverseConcat(Mtx inv, Mtx src, Mtx dest)
{
    Mtx m; 
    f32 det;
    f32 temp1;
    f32 temp2;
    f32 temp3;
    f32 temp4;
    f32 temp5;
    f32 temp6;
    f32 temp7;
    f32 temp8;
    f32 temp9;
    f32 temp10;
    f32 temp11;
    f32 temp12;
    f32 new_var; // TODO: try to get rid of this

    det = HSD_CalcDeterminantMatrix3x4(inv);
    
    if (fabsf_bitwise(det) < EPSILON) {
        if (src != dest) {
            PSMTXCopy(src, dest);
        }
    } else {
        det = 1.0f / det;
        temp1 = ((inv[1][1] * inv[2][2]) - (inv[2][1] * inv[1][2])) * det;
        temp2 = (-((inv[0][1] * inv[2][2]) - (inv[2][1] * inv[0][2]))) * det;
        new_var = inv[1][1];
        temp3 = (-((inv[1][0] * inv[2][2]) - (inv[2][0] * inv[1][2]))) * det;
        temp7 = ((inv[0][1] * inv[1][2]) - (new_var * inv[0][2])) * det;
        temp4 = ((inv[0][0] * inv[2][2]) - (inv[2][0] * inv[0][2])) * det;
        temp8 = (-((inv[0][0] * inv[1][2]) - (inv[1][0] * inv[0][2]))) * det;
        temp5 = ((inv[1][0] * inv[2][1]) - (inv[2][0] * new_var)) * det;
        temp6 = (-((inv[0][0] * inv[2][1]) - (inv[2][0] * inv[0][1]))) * det;
        temp9 = ((inv[0][0] * inv[1][1]) - (inv[1][0] * inv[0][1])) * det;
        temp10 = -((temp7 * inv[2][3]) - (((-temp1) * inv[0][3]) - (temp2 * inv[1][3])));
        temp11 = -((temp8 * inv[2][3]) - (((-temp3) * inv[0][3]) - (temp4 * inv[1][3])));
        temp12 = -((temp9 * inv[2][3]) - (((-temp5) * (new_var = inv[0][3])) - (temp6 * inv[1][3])));
        
        if (inv == dest || src == dest) {
            m[0][0] = temp7 * src[2][0] + (temp1 * src[0][0] + temp2 * src[1][0]);
            m[0][1] = temp7 * src[2][1] + (temp1 * src[0][1] + temp2 * src[1][1]);
            m[0][2] = temp7 * src[2][2] + (temp1 * src[0][2] + temp2 * src[1][2]);
            m[0][3] = temp7 * src[2][3] + (temp1 * src[0][3] + temp2 * src[1][3]) + temp10;
            m[1][0] = temp8 * src[2][0] + (temp3 * src[0][0] + temp4 * src[1][0]);
            m[1][1] = temp8 * src[2][1] + (temp3 * src[0][1] + temp4 * src[1][1]);
            m[1][2] = temp8 * src[2][2] + (temp3 * src[0][2] + temp4 * src[1][2]);
            m[1][3] = temp8 * src[2][3] + (temp3 * src[0][3] + temp4 * src[1][3]) + temp11;
            m[2][0] = temp9 * src[2][0] + (temp5 * src[0][0] + temp6 * src[1][0]);
            m[2][1] = temp9 * src[2][1] + (temp5 * src[0][1] + temp6 * src[1][1]);
            m[2][2] = temp9 * src[2][2] + (temp5 * src[0][2] + temp6 * src[1][2]);
            m[2][3] = temp9 * src[2][3] + (temp5 * src[0][3] + temp6 * src[1][3]) + temp12;
            
            PSMTXCopy(m, dest);
        } else {
            dest[0][0] = temp7 * src[2][0] + (temp1 * src[0][0] + temp2 * src[1][0]);
            dest[0][1] = temp7 * src[2][1] + (temp1 * src[0][1] + temp2 * src[1][1]);
            dest[0][2] = temp7 * src[2][2] + (temp1 * src[0][2] + temp2 * src[1][2]);
            dest[0][3] = temp7 * src[2][3] + (temp1 * src[0][3] + temp2 * src[1][3]) + temp10;
            dest[1][0] = temp8 * src[2][0] + (temp3 * src[0][0] + temp4 * src[1][0]);
            dest[1][1] = temp8 * src[2][1] + (temp3 * src[0][1] + temp4 * src[1][1]);
            dest[1][2] = temp8 * src[2][2] + (temp3 * src[0][2] + temp4 * src[1][2]);
            dest[1][3] = temp8 * src[2][3] + (temp3 * src[0][3] + temp4 * src[1][3]) + temp11;
            dest[2][0] = temp9 * src[2][0] + (temp5 * src[0][0] + temp6 * src[1][0]);
            dest[2][1] = temp9 * src[2][1] + (temp5 * src[0][1] + temp6 * src[1][1]);
            dest[2][2] = temp9 * src[2][2] + (temp5 * src[0][2] + temp6 * src[1][2]);
            dest[2][3] = temp9 * src[2][3] + (temp5 * src[0][3] + temp6 * src[1][3]) + temp12;
        }
    }
}

void func_80379A20(Mtx src, Mtx dest)
{
    Mtx* m;
    Mtx tempMatrix;
    f32 det = HSD_CalcDeterminantMatrix3x4(src);

    m = (Mtx*)src;
    
    if (fabsf_bitwise(det) < EPSILON) {
        if (*m != dest) {
            PSMTXCopy(*m, dest);
        }
    } else {
        if (*m == dest) {
            PSMTXCopy(*m, tempMatrix);
            m = &tempMatrix;
        }
        
        det = 1.0f / det;

        // This needs to be in a different order than in func_80379310 for some reason
        dest[0][0] = (((*m)[1][1] * (*m)[2][2]) - ((*m)[2][1] * (*m)[1][2])) * det;
        dest[1][0] = -(((*m)[0][1] * (*m)[2][2]) - ((*m)[2][1] * (*m)[0][2])) * det;
        dest[2][0] = (((*m)[0][1] * (*m)[1][2]) - ((*m)[1][1] * (*m)[0][2])) * det;
        dest[0][1] = -(((*m)[1][0] * (*m)[2][2]) - ((*m)[2][0] * (*m)[1][2])) * det;
        dest[1][1] = (((*m)[0][0] * (*m)[2][2]) - ((*m)[2][0] * (*m)[0][2])) * det;
        dest[2][1] = -(((*m)[0][0] * (*m)[1][2]) - ((*m)[1][0] * (*m)[0][2])) * det;
        dest[0][2] = (((*m)[1][0] * (*m)[2][1]) - ((*m)[2][0] * (*m)[1][1])) * det;
        dest[1][2] = -(((*m)[0][0] * (*m)[2][1]) - ((*m)[2][0] * (*m)[0][1])) * det;
        dest[2][2] = (((*m)[0][0] * (*m)[1][1]) - ((*m)[1][0] * (*m)[0][1])) * det;
        dest[0][3] = 0;
        dest[1][3] = 0;
        dest[2][3] = 0;
    }
}

inline f32 calcVal(f32 x, f32 y)
{
    if (fabsf_bitwise(x) <= FLOAT_MIN) {
        if (y >= 0) {
            return M_PI/2;
        } else {
            return -M_PI/2;
        }
    } else {
        return atan2f(y, x);
    }
}

void func_80379C24(Mtx m, Vec* vec)
{
    f32 length0;
    f32 length1;
    f32 length2;
    f32 testVal_1;
    f32 val_01;
    
    length0 = sqrtf(m[0][0]*m[0][0] + m[1][0]*m[1][0] + m[2][0]*m[2][0]);
    if (!(length0 < FLOAT_MIN)) {
        
        length1 = sqrtf(m[0][1]*m[0][1] + m[1][1]*m[1][1] + m[2][1]*m[2][1]);
        if (!(length1 < FLOAT_MIN)) {
            
            length2 = sqrtf(m[0][2]*m[0][2] + m[1][2]*m[1][2] + m[2][2]*m[2][2]);
            if (!(length2 < FLOAT_MIN)) {
                testVal_1 = -m[2][0];
                testVal_1 /= length0;
                
                if (testVal_1 >= 1.0f) {
                    val_01 = M_PI/2;
                } else if (testVal_1 <= -1) {
                    val_01 = -M_PI/2;
                } else {
                    val_01 = func_80022DBC(testVal_1);
                }
                
                vec->y = val_01;
                
                if (cosf(vec->y) >= FLOAT_MIN) {
                    f32 testVal_2_pre = m[2][2] / length2;
                    f32 testVal_3_pre = m[2][1] / length1;
                    
                    vec->x = calcVal(testVal_2_pre, testVal_3_pre);         
                    vec->z = calcVal(m[0][0], m[1][0]);
                    return;
                }
                
                vec->x = calcVal(m[1][1], m[0][1]);
                vec->z = 0;
                return;
            }
        }
    }

    vec->x = 0;
    vec->y = 0;
    vec->z = 0;
}

// These parameters may not be right
void func_80379F6C(Mtx mat, Vec* vec)
{
    vec->x = mat[0][3];
    vec->y = mat[1][3];
    vec->z = mat[2][3];
}

void func_80379F88(Mtx arg0, Vec* arg1)
{
    f64 scale;
    f64 filler;
    Vec vec1;
    Vec vec2;
    Vec vec3;
    Vec vec4;

    vec1.x = arg0[0][0];
    vec1.y = arg0[1][0];
    vec1.z = arg0[2][0];
    
    arg1->x = PSVECMag(&vec1);
    PSVECNormalize(&vec1, &vec1);
    
    vec2.x = arg0[0][1];
    vec2.y = arg0[1][1];
    vec2.z = arg0[2][1];
    
    PSVECScale(&vec1, &vec4, PSVECDotProduct(&vec1, &vec2));
    PSVECSubtract(&vec2, &vec4, &vec2);
    arg1->y = PSVECMag(&vec2);
    PSVECNormalize(&vec2, &vec2);
    
    vec3.x = arg0[0][2];
    vec3.y = arg0[1][2];
    vec3.z = arg0[2][2];
    
    PSVECScale(&vec2, &vec4, PSVECDotProduct(&vec2, &vec3));
    PSVECSubtract(&vec3, &vec4, &vec3);
    PSVECScale(&vec1, &vec4, PSVECDotProduct(&vec1, &vec3));
    PSVECSubtract(&vec3, &vec4, &vec3);
    arg1->z = PSVECMag(&vec3);
    PSVECNormalize(&vec3, &vec3);
    PSVECCrossProduct(&vec2, &vec3, &vec4);
    
    if (PSVECDotProduct(&vec1, &vec4) < 0.0) {
        scale = -1.0;
        arg1->x *= scale;
        arg1->y *= scale;
        arg1->z *= scale;
    }
}

void func_8037A120(Mtx arg0, Vec* arg1)
{
    f32 sinX;
    f32 cosX;
    f32 sinY;
    f32 cosY;
    f32 sinZ;
    f32 cosZ;
    f32 temp1;
    f32 temp2;

    sinX = sinf(arg1->x);
    cosX = cosf(arg1->x);
    sinY = sinf(arg1->y);
    cosY = cosf(arg1->y);
    sinZ = sinf(arg1->z);
    cosZ = cosf(arg1->z);
    
    temp1 = sinX * sinY;
    arg0[0][0] = cosY * cosZ;
    arg0[1][0] = cosY * sinZ;
    arg0[2][0] = -sinY;
    temp2 = cosX * sinY;
    arg0[0][1] = (cosZ * temp1) - (cosX * sinZ);
    arg0[1][1] = (sinZ * temp1) + (cosX * cosZ);
    arg0[2][1] = sinX * cosY;
    arg0[0][2] = (cosZ * temp2) + (sinX * sinZ);
    arg0[1][2] = (sinZ * temp2) - (sinX * cosZ);
    arg0[2][2] = cosX * cosY;
    arg0[0][3] = 0;
    arg0[1][3] = 0;
    arg0[2][3] = 0;
}

void func_8037A230(Mtx arg0, Quaternion* arg1)
{
    PSMTXQuat(arg0, arg1);
}

void func_8037A250(Mtx m, Vec* vec1, Vec* vec2, Vec* vec3, Vec* vec4)
{
    f32 vec1x_2;
    f32 vec1y_2;
    f32 vec1z_2;
    f32 vec1x_1;
    f32 vec1y_1;
    f32 vec1z_1;
    f32 vec1x;
    f32 vec1y;
    f32 vec1z;
    
    f32 sinX = sinf(vec2->x);
    f32 cosX = cosf(vec2->x);
    f32 sinY = sinf(vec2->y);
    f32 cosY = cosf(vec2->y);
    f32 sinZ = sinf(vec2->z);
    f32 cosZ = cosf(vec2->z);
    
    vec1x_2 = vec1x_1 = vec1x = vec1->x;
    vec1y_2 = vec1y_1 = vec1y = vec1->y;
    vec1z_2 = vec1z_1 = vec1z = vec1->z;
    
    if (vec4 != NULL) {   
        f32 temp1 = 1.0/vec4->x;
        f32 temp2 = 1.0/vec4->y;
        f32 temp3 = 1.0/vec4->z;
        
        vec1y_2 *= vec4->y * temp1;
        vec1z_2 *= vec4->z * temp1;
        vec1x_1 *= vec4->x * temp2;
        vec1z_1 *= vec4->z * temp2;
        vec1x *= vec4->x * temp3;
        vec1y *= vec4->y * temp3;
    }
    
    
    m[0][0] = cosZ * (vec1x_2 * cosY);
    m[1][0] = sinZ * (vec1x_1 * cosY);
    m[2][0] = -vec1x * sinY;
    m[0][1] = vec1y_2 * ((cosZ * (sinX * sinY)) - (cosX * sinZ));
    m[1][1] = vec1y_1 * ((sinZ * (sinX * sinY)) + (cosX * cosZ));
    m[2][1] = cosY * (vec1y * sinX);
    m[0][2] = vec1z_2 * ((cosZ * (cosX * sinY)) + (sinX * sinZ));
    m[1][2] = vec1z_1 * ((sinZ * (cosX * sinY)) - (sinX * cosZ));
    m[2][2] = cosY * (vec1z * cosX);
    m[0][3] = vec3->x;
    m[1][3] = vec3->y;
    m[2][3] = vec3->z;
}

void func_8037A43C(Mtx arg0, Vec* arg1, Quaternion* arg2, Vec* arg3, Vec* arg4) {
    Mtx temp;

    PSMTXScale(arg0, arg1->x, arg1->y, arg1->z);
    
    if (arg4 != NULL) {
        PSMTXScale(temp, arg4->x, arg4->y, arg4->z);
        PSMTXConcat(temp, arg0, arg0);
    }
    
    PSMTXQuat(temp, arg2);
    PSMTXConcat(temp, arg0, arg0);
    
    if (arg4 != NULL) {
        PSMTXScale(temp, 1.0/arg4->x, 1.0/arg4->y, 1.0/arg4->z);
        PSMTXConcat(temp, arg0, arg0);
    }
    
    PSMTXTrans(temp, arg3->x, arg3->y, arg3->z);
    PSMTXConcat(temp, arg0, arg0);
}

// might be a fakematch?
void func_8037A54C(Mtx arg0, Mtx arg1, Mtx arg2, f32 arg3)
{
    f32 *arr0 = (f32*)&arg0[0][0];
    f32 *arr1 = (f32*)&arg1[0][0];
    f32 *arr2 = (f32*)&arg2[0][0];

    *(arr2)++ = *(arr1)++ + (arg3 * *(arr0)++);
    *(arr2)++ = *(arr1)++ + (arg3 * *(arr0)++);
    *(arr2)++ = *(arr1)++ + (arg3 * *(arr0)++);
    *(arr2)++ = *(arr1)++ + (arg3 * *(arr0)++);
    
    *(arr2)++ = *(arr1)++ + (arg3 * *(arr0)++);
    *(arr2)++ = *(arr1)++ + (arg3 * *(arr0)++);
    *(arr2)++ = *(arr1)++ + (arg3 * *(arr0)++);
    *(arr2)++ = *(arr1)++ + (arg3 * *(arr0)++);

    *(arr2)++ = *(arr1)++ + (arg3 * *(arr0)++);
    *(arr2)++ = *(arr1)++ + (arg3 * *(arr0)++);
    *(arr2)++ = *(arr1)++ + (arg3 * *(arr0)++);
    *(arr2)++ = *(arr1)++ + (arg3 * *(arr0)++);
}

void* func_8037A610(void)
{
    void* vec = HSD_ObjAlloc(&lbl_804C2310);
    
    if (vec == NULL) {
        __assert("mtx.c", 0x335, "vec");
    }
    
    return vec;
}

void func_8037A65C(void* arg0)
{
    if (arg0 != NULL) {
        HSD_ObjFree(&lbl_804C2310, arg0);
    }
}

void* func_8037A68C(void)
{
    void* mtx;

    mtx = HSD_ObjAlloc(&lbl_804C233C);
    if (mtx == NULL) {
        __assert("mtx.c", 0x354, "mtx");
    }
    return mtx;
}

void func_8037A6D8(void* arg0)
{
    if (arg0 != NULL) {
        HSD_ObjFree(&lbl_804C233C, arg0);
    }
}

HSD_ObjAllocData* HSD_VecGetAllocData(void)
{
    return &lbl_804C2310;
}

void HSD_VecInitAllocData(void)
{
    HSD_ObjAllocInit(&lbl_804C2310, 0xC, 4);
}

HSD_ObjAllocData* HSD_MtxGetAllocData(void)
{
    return &lbl_804C233C;
}

void HSD_MtxInitAllocData(void)
{
    HSD_ObjAllocInit(&lbl_804C233C, 0x30, 4);
}