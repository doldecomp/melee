#include <dolphin/types.h>

f32 cos__Ff(f32);
f32 sin__Ff(f32);
f32 cosf(f32);
f32 sinf(f32);

f32 tanf(f32 x)
{
    return sin__Ff(x) / cos__Ff(x);
}

f32 cos__Ff(f32 x)
{
    return cosf(x);
}

f32 sin__Ff(f32 x)
{
    return sinf(x);
}
