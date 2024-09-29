#include <platform.h>

#include <dolphin/mtx/forward.h>

#include <dolphin/mtx.h>
#include <MSL/math.h>

void C_MTXFrustum(Mtx44 m, f32 t, f32 b, f32 l, f32 r, f32 n, f32 f)
{
    f32 temp_f8;
    f32 temp_f6;
    f32 temp_f9;
    f32 temp_f11;

    temp_f11 = 1.0F / (r - l);
    temp_f8 = 2.0F * n;
    temp_f9 = 1.0F / (t - b);
    temp_f6 = 1.0F / (f - n);

    m[0][0] = temp_f8 * temp_f11;
    m[0][1] = 0.0F;
    m[0][2] = temp_f11 * (r + l);
    m[0][3] = 0.0F;

    m[1][0] = 0.0F;
    m[1][1] = temp_f8 * temp_f9;
    m[1][2] = temp_f9 * (t + b);
    m[1][3] = 0.0F;

    m[2][0] = 0.0F;
    m[2][1] = 0.0F;
    m[2][2] = -n * temp_f6;
    m[2][3] = temp_f6 * -(f * n);

    m[3][0] = 0.0F;
    m[3][1] = 0.0F;
    m[3][2] = -1.0F;
    m[3][3] = 0.0F;
}

void C_MTXPerspective(Mtx44 m, f32 fovY, f32 aspect, f32 n, f32 f)
{
    f32 temp_f3;
    f32 temp_f4;

    fovY = 0.5F * fovY;

    temp_f4 = 1.0F / tanf(0.017453292F * (fovY));
    temp_f3 = 1.0F / (f - n);

    m[0][0] = temp_f4 / aspect;
    m[0][1] = 0.0F;
    m[0][2] = 0.0F;
    m[0][3] = 0.0F;

    m[1][0] = 0.0F;
    m[1][1] = temp_f4;
    m[1][2] = 0.0F;
    m[1][3] = 0.0F;

    m[2][0] = 0.0F;
    m[2][1] = 0.0F;
    m[2][2] = -n * temp_f3;
    m[2][3] = temp_f3 * -(f * n);

    m[3][0] = 0.0F;
    m[3][1] = 0.0F;
    m[3][2] = -1.0F;
    m[3][3] = 0.0F;
}

void C_MTXOrtho(Mtx44 m, f32 t, f32 b, f32 l, f32 r, f32 n, f32 f)
{
    f32 temp_f8;
    f32 temp_f10;
    f32 temp_f4;

    temp_f10 = 1.0F / (r - l);
    m[0][0] = 2.0F * temp_f10;
    m[0][1] = 0.0F;
    m[0][2] = 0.0F;
    m[0][3] = temp_f10 * -(r + l);

    temp_f8 = 1.0F / (t - b);
    m[1][0] = 0.0F;
    m[1][1] = 2.0F * temp_f8;
    m[1][2] = 0.0F;
    m[1][3] = temp_f8 * -(t + b);

    temp_f4 = 1.0F / (f - n);
    m[2][0] = 0.0F;
    m[2][1] = 0.0F;
    m[2][2] = -1.0F * temp_f4;
    m[2][3] = -f * temp_f4;

    m[3][0] = 0.0F;
    m[3][1] = 0.0F;
    m[3][2] = 0.0F;
    m[3][3] = 1.0F;
}
