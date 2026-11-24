#ifndef RUNTIME_FMA_H
#define RUNTIME_FMA_H

/// @file
/// Multiply-adds that the GameCube compiler fuses into one instruction
/// (@c fmadds, @c fmsubs, @c fnmsubs, ...), which rounds once instead of
/// twice.
///
/// With Metrowerks each macro expands to the original expression, so the
/// matching build is unchanged. With any other compiler it computes the fused
/// result, so a port rounds the way the console does.
///
/// Arguments are in source order: @c FMA_MUL_ADD(a, b, c) is <tt>a * b +
/// c</tt>,
/// @c FMA_ADD_MUL(c, a, b) is <tt>c + a * b</tt>, @c FMA_ADD_TO(x, a, b) is
/// <tt>x += a * b</tt>, and so on.

#ifdef __MWERKS__

#define FMA_MUL_ADD(a, b, c) ((a) * (b) + (c))
#define FMA_ADD_MUL(c, a, b) ((c) + (a) * (b))
#define FMA_MUL_SUB(a, b, c) ((a) * (b) - (c))
#define FMA_SUB_MUL(c, a, b) ((c) - (a) * (b))
#define FMA_ADD_TO(x, a, b) ((x) += (a) * (b))
#define FMA_SUB_FROM(x, a, b) ((x) -= (a) * (b))

#else

/// fmaf or fma, by the type of <tt>a * b + c</tt>, as the console would use
/// fmadds or fmadd.
#define FMA_(a, b, c)                                                         \
    _Generic((a) * (b) + (c), float: __builtin_fmaf, default: __builtin_fma)( \
        (a), (b), (c))

#define FMA_MUL_ADD(a, b, c) FMA_((a), (b), (c))
#define FMA_ADD_MUL(c, a, b) FMA_((a), (b), (c))
#define FMA_MUL_SUB(a, b, c) FMA_((a), (b), -(c))
/// fnmsubs is -(a * b - c): negating the fused result keeps the sign of zero.
#define FMA_SUB_MUL(c, a, b) (-FMA_((a), (b), -(c)))
#define FMA_ADD_TO(x, a, b) ((x) = FMA_((a), (b), (x)))
#define FMA_SUB_FROM(x, a, b) ((x) = -FMA_((a), (b), -(x)))

#endif

#endif
