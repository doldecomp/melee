#ifndef DOLPHIN_TYPES_H
#define DOLPHIN_TYPES_H

#include <ctypes.h>

#define FLT_MAX 3.4028235E38

#define assert_line(line, cond)                                                \
    ((cond) ? ((void) 0) : __assert(__FILE__, line, #cond))

#define STRUCT_PLACEHOLDER(module, number) extern struct _ ## module ## _Unk ## number; \
typedef struct _ ## module ## _Unk ## number module ## _Unk ## number;

#define CALLBACK_PLACEHOLDER(module, number) typedef void (*module ## _UnkCallback ## number)();

#define UNK_FUNC(name) unk_t name()

#pragma region "macros.inc"
#define qr0 0
#define qr1 1
#define qr2 2
#define qr3 3
#define qr4 4
#define qr5 5
#define qr6 6
#define qr7 7
#pragma endregion

// TODO! DO NOT LEAVE THIS IN!
#include <dolphin/mtx/types.h>

#endif
