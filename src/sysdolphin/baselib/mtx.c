#include "sysdolphin/baselib/mtx.h"


#define epsilon 0.0000000001f

extern const f32 lbl_804DE65C; // 1.0f
extern const f32 lbl_804DE660; // 0.0f


// Calculates the determinant of the top 3x3 section of a 3x4 matrix
inline f32 HSD_CalcDeterminantMatrix3x4(Mtx m)
{
    f32 det;
    f32 m12 = m[1][2];
    f32 m00 = m[0][0];
    f32 m21 = m[2][1];
    f32 m22 = m[2][2];
    f32 m02 = m[0][2];
    f32 m20 = m[2][0];
    f32 m11 = m[1][1];
    f32 m10 = m[1][0];
    f32 m01 = m[0][1];

    // Very likely a fakematch
    // TODO: try to rewrite this
    det = __fnmsubs(m12, (m00 * m21), __fnmsubs(m22, (m10 * m01), __fnmsubs(m02 , (m20 * m11), (m21 * (m02 * m10) + (m22 * (m00 * m11) + (m01 * m12 * m20))))));
    
    return det;
}

void func_80379310(Mtx src, Mtx dest)
{
    Mtx tempMatrix;
    Mtx* m;
    f32 det;
    f32 temp;

    det = HSD_CalcDeterminantMatrix3x4(src);

    temp = det;
    // why???
    FABSF(temp);
    
    if (temp < epsilon) {
        PSMTXIdentity(dest);
        return;
    }

    if (src == dest) {
        PSMTXCopy(src, tempMatrix);
        m = &tempMatrix;
    } else {
        m = (Mtx*)src;
    }

    det = lbl_804DE65C/det;

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
    f32 detTemp;
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
    detTemp = det;
    FABSF(detTemp);
    
    if (detTemp < epsilon) {
        if (src != dest) {
            PSMTXCopy(src, dest);
        }
    } else {
        det = lbl_804DE65C / det;
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
    f32 temp;
    f32 det;

    m = (Mtx*)src;
    
    det = HSD_CalcDeterminantMatrix3x4(src);
    temp = det;
    FABSF(temp);
    
    if (temp < epsilon) {
        if (*m != dest) {
            PSMTXCopy(*m, dest);
        }
    } else {
        if (*m == dest) {
            PSMTXCopy(*m, tempMatrix);
            m = &tempMatrix;
        }
        
        det = lbl_804DE65C / det;

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
        dest[0][3] = lbl_804DE660;
        dest[1][3] = lbl_804DE660;
        dest[2][3] = lbl_804DE660;
    }
}