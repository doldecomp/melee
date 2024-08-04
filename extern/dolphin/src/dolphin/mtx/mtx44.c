#include <dolphin.h>
#include <dolphin/mtx.h>
#include "fake_tgmath.h"

// functions
void MTXFrustum(Mtx m, f32 t, f32 b, f32 l, f32 r, f32 n, f32 f);
void MTXPerspective(Mtx m, f32 fovY, f32 aspect, f32 n, f32 f);
void MTXOrtho(Mtx m, f32 t, f32 b, f32 l, f32 r, f32 n, f32 f);

void MTXFrustum(Mtx m, f32 t, f32 b, f32 l, f32 r, f32 n, f32 f) {
    f32 tmp;

    ASSERTMSGLINE(0x4C, m, "MTXFrustum():  NULL Mtx44Ptr 'm' ");
    ASSERTMSGLINE(0x4D, t != b, "MTXFrustum():  't' and 'b' clipping planes are equal ");
    ASSERTMSGLINE(0x4E, l != r, "MTXFrustum():  'l' and 'r' clipping planes are equal ");
    ASSERTMSGLINE(0x4F, n != f, "MTXFrustum():  'n' and 'f' clipping planes are equal ");
    tmp = 1 / (r - l);
    m[0][0] = (2 * n * tmp);
    m[0][1] = 0;
    m[0][2] = (tmp * (r + l));
    m[0][3] = 0;
    tmp = 1 / (t - b);
    m[1][0] = 0;
    m[1][1] = (2 * n * tmp);
    m[1][2] = (tmp * (t + b));
    m[1][3] = 0;
    m[2][0] = 0;
    m[2][1] = 0;
    tmp = 1 / (f - n);
    m[2][2] = (-n * tmp);
    m[2][3] = (tmp * -(f * n));
    m[3][0] = 0;
    m[3][1] = 0;
    m[3][2] = -1;
    m[3][3] = 0;
}

void MTXPerspective(Mtx m, f32 fovY, f32 aspect, f32 n, f32 f) {
    f32 angle;
    f32 cot;
    f32 tmp;

    ASSERTMSGLINE(0x93, m, "MTXPerspective():  NULL Mtx44Ptr 'm' ");
    ASSERTMSGLINE(0x94, (fovY > 0.0) && (fovY < 180.0), "MTXPerspective():  'fovY' out of range ");
    ASSERTMSGLINE(0x95, 0.0f != aspect, "MTXPerspective():  'aspect' is 0 ");

    angle = (0.5f * fovY);
    angle = angle * 0.017453293f;
    cot = 1 / tanf(angle);
    m[0][0] = (cot / aspect);
    m[0][1] = 0;
    m[0][2] = 0;
    m[0][3] = 0;
    m[1][0] = 0;
    m[1][1] = (cot);
    m[1][2] = 0;
    m[1][3] = 0;
    m[2][0] = 0;
    m[2][1] = 0;
    tmp = 1 / (f - n);
    m[2][2] = (-n * tmp);
    m[2][3] = (tmp * -(f * n));
    m[3][0] = 0;
    m[3][1] = 0;
    m[3][2] = -1;
    m[3][3] = 0;
}

void MTXOrtho(Mtx m, f32 t, f32 b, f32 l, f32 r, f32 n, f32 f) {
    f32 tmp;

    ASSERTMSGLINE(0xDB, m, "MTXOrtho():  NULL Mtx44Ptr 'm' ");
    ASSERTMSGLINE(0xDC, t != b, "MTXOrtho():  't' and 'b' clipping planes are equal ");
    ASSERTMSGLINE(0xDD, l != r, "MTXOrtho():  'l' and 'r' clipping planes are equal ");
    ASSERTMSGLINE(0xDE, n != f, "MTXOrtho():  'n' and 'f' clipping planes are equal ");
    tmp = 1 / (r - l);
    m[0][0] = 2 * tmp;
    m[0][1] = 0;
    m[0][2] = 0;
    m[0][3] = (tmp * -(r + l));
    tmp = 1 / (t - b);
    m[1][0] = 0;
    m[1][1] = 2 * tmp;
    m[1][2] = 0;
    m[1][3] = (tmp * -(t + b));
    m[2][0] = 0;
    m[2][1] = 0;
    tmp = 1 / (f - n);
    m[2][2] = (-1 * tmp);
    m[2][3] = (-f * tmp);
    m[3][0] = 0;
    m[3][1] = 0;
    m[3][2] = 0;
    m[3][3] = 1;
}
