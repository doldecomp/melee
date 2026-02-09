#include "bytecode.h"

#include <platform.h>
#include <placeholder.h>

#include "baselib/debug.h"
#include "baselib/list.h"
#include "baselib/random.h"

#include <dolphin/os.h>

#include <MSL/math.h>
#include <MSL/trigf.h>
#include <melee/lb/lb_00CE.h>

static inline float fmod(float a, float b)
{
    long long quotient;
    if (__fabs(b) > __fabs(a)) {
        return a;
    }
    quotient = a / b;
    return a - b * quotient;
}

#define DEG_TO_RAD 0.017453292519943295
#define RAD_TO_DEG 57.29577951308232

float HSD_ByteCodeEval(u8* pc, float* args, u32 nb_args)
{
    HSD_SList* stack;
    s32 extra_bytes;
    u32 operand;
    int opcode;
    f32 fv;
    u32 i;
    s32 a;

    stack = NULL;
    extra_bytes = 0;

    if (pc == NULL) {
        return 0.0F;
    }

    for (;;) {
        if (extra_bytes > 0) {
            extra_bytes--;
            operand = (operand << 8) | *pc;
            pc++;

            if (extra_bytes != 0) {
                continue;
            }

            switch (opcode) {
            case 2:
                HSD_ASSERT(281, operand < nb_args);
                stack = HSD_SListAllocAndPrepend(
                    stack, (void*) *(s32*) &args[operand]);
                break;
            case 5:
                for (i = 0; i < operand; i++) {
                    stack = HSD_SListRemove(stack);
                }
                break;
            case 0x3C:
            {
                HSD_SList* p = stack;
                i = 0;
                while (p != NULL && i < operand) {
                    p = p->next;
                    i++;
                }
                if (p == NULL) {
                    OSReport("specified stack doesn't exist (%d).\n",
                             operand);
                    HSD_Panic("bytecode.c", 299, NULL);
                } else {
                    stack = HSD_SListAllocAndPrepend(
                        stack, p->data);
                }
                break;
            }
            case 3:
                HSD_ASSERT(307, stack);
                if ((s32) stack->data != 0) {
                    pc += operand;
                }
                stack = HSD_SListRemove(stack);
                break;
            case 4:
                pc += operand;
                break;
            case 6:
                stack = HSD_SListAllocAndPrepend(stack, (void*) operand);
                break;
            case 0xFF:
                HSD_Panic("bytecode.c", 323, "not yet implemented.\n");
                /* fallthrough */
            default:
                HSD_Panic("bytecode.c", 326, "unexpected byte code.\n");
                break;
            }
            continue;
        }

        opcode = *pc;
        pc++;

        switch (opcode) {
        case 0:
            break;
        case 1:
            HSD_ASSERT(339, stack);
            fv = *(f32*) &stack->data;
            while (stack != NULL) {
                stack = HSD_SListRemove(stack);
            }
            return fv;
        case 5:
        case 0x3C:
        case 0xFF:
            extra_bytes = 1;
            operand = 0;
            break;
        case 2:
        case 3:
        case 4:
            extra_bytes = 2;
            operand = 0;
            break;
        case 6:
            extra_bytes = 4;
            operand = 0;
            break;
        case 7:
            HSD_ASSERT(376, stack);
            fv = *(f32*) &stack->data;
            {
                s32 iv = (s32) fv;
                stack->data = (void*) iv;
            }
            break;
        case 8:
            HSD_ASSERT(381, stack);
            {
                s32 iv = (s32) stack->data;
                fv = (f32) iv;
                stack->data = *(void**) &fv;
            }
            break;
        case 9:
            HSD_ASSERT(387, stack);
            fv = -(*(f32*) &stack->data);
            stack->data = *(void**) &fv;
            break;
        case 0x0A:
            HSD_ASSERT(393, stack);
            stack->data = (void*) -(s32) stack->data;
            break;
        case 0x0B:
            HSD_ASSERT(399, stack);
            stack->data = (void*) HSD_Randi(2);
            break;
        case 0x0C:
            HSD_ASSERT(405, stack);
            fv = HSD_Randf();
            stack->data = *(void**) &fv;
            break;
        case 0x0D:
            HSD_ASSERT(411, stack);
            fv = sinf((f32) (DEG_TO_RAD * (f64) *(f32*) &stack->data));
            stack->data = *(void**) &fv;
            break;
        case 0x0E:
            HSD_ASSERT(417, stack);
            fv = cosf((f32) (DEG_TO_RAD * (f64) *(f32*) &stack->data));
            stack->data = *(void**) &fv;
            break;
        case 0x0F:
            HSD_ASSERT(423, stack);
            fv = tanf((f32) (DEG_TO_RAD * (f64) *(f32*) &stack->data));
            stack->data = *(void**) &fv;
            break;
        case 0x10:
            HSD_ASSERT(429, stack);
            fv = (f32) (RAD_TO_DEG * asinf(*(f32*) &stack->data));
            stack->data = *(void**) &fv;
            break;
        case 0x11:
            HSD_ASSERT(435, stack);
            fv = (f32) (RAD_TO_DEG * acosf(*(f32*) &stack->data));
            stack->data = *(void**) &fv;
            break;
        case 0x12:
            HSD_ASSERT(441, stack);
            fv = (f32) (RAD_TO_DEG * atanf(*(f32*) &stack->data));
            stack->data = *(void**) &fv;
            break;
        case 0x13:
            HSD_ASSERT(447, stack);
            fv = logf(*(f32*) &stack->data);
            stack->data = *(void**) &fv;
            break;
        case 0x14:
            HSD_ASSERT(453, stack);
            fv = expf(*(f32*) &stack->data);
            stack->data = *(void**) &fv;
            break;
        case 0x15:
            HSD_ASSERT(459, stack);
            fv = *(f32*) &stack->data;
            if (fv < 0.0F) {
                fv = -fv;
                stack->data = *(void**) &fv;
            }
            break;
        case 0x28:
            HSD_ASSERTMSG(467, stack, "stack");
            {
                s32 iv = (s32) stack->data;
                if (iv < 0) {
                    stack->data = (void*) -iv;
                }
            }
            break;
        case 0x16:
            HSD_ASSERT(474, stack);
            fv = *(f32*) &stack->data;
            if (fv > 0.0F) {
                f64 guess = __frsqrte((f64) fv);
                guess = 0.5 * guess *
                        -(((f64) fv * (guess * guess)) - 3.0);
                guess = 0.5 * guess *
                        -(((f64) fv * (guess * guess)) - 3.0);
                fv = (f32) ((f64) fv *
                            (0.5 * guess *
                             -(((f64) fv * (guess * guess)) - 3.0)));
            }
            stack->data = *(void**) &fv;
            break;
        case 0x31:
            HSD_ASSERTMSG(480, stack, "stack");
            stack->data = (void*) ((s32) stack->data == 0);
            break;
        case 0x17:
            HSD_ASSERT(501, stack);
            HSD_ASSERTMSG(501, stack->next, "stack->next");
            fv = *(f32*) &stack->data;
            stack = HSD_SListRemove(stack);
            fv = *(f32*) &stack->data + fv;
            stack->data = *(void**) &fv;
            break;
        case 0x18:
            HSD_ASSERT(507, stack);
            HSD_ASSERTMSG(507, stack->next, "stack->next");
            fv = *(f32*) &stack->data;
            stack = HSD_SListRemove(stack);
            fv = *(f32*) &stack->data - fv;
            stack->data = *(void**) &fv;
            break;
        case 0x19:
            HSD_ASSERT(513, stack);
            HSD_ASSERTMSG(513, stack->next, "stack->next");
            fv = *(f32*) &stack->data;
            stack = HSD_SListRemove(stack);
            fv = *(f32*) &stack->data * fv;
            stack->data = *(void**) &fv;
            break;
        case 0x1A:
            HSD_ASSERT(519, stack);
            HSD_ASSERTMSG(519, stack->next, "stack->next");
            fv = *(f32*) &stack->data;
            stack = HSD_SListRemove(stack);
            fv = *(f32*) &stack->data / fv;
            stack->data = *(void**) &fv;
            break;
        case 0x1B:
            HSD_ASSERT(525, stack);
            HSD_ASSERTMSG(525, stack->next, "stack->next");
            fv = *(f32*) &stack->data;
            stack = HSD_SListRemove(stack);
            {
                f32 fa = fmod(*(f32*) &stack->data, fv);
                stack->data = *(void**) &fa;
            }
            break;
        case 0x1C:
            HSD_ASSERT(531, stack);
            HSD_ASSERTMSG(531, stack->next, "stack->next");
            a = (s32) stack->data;
            stack = HSD_SListRemove(stack);
            stack->data = (void*) ((s32) stack->data + a);
            break;
        case 0x1D:
            HSD_ASSERT(536, stack);
            HSD_ASSERTMSG(536, stack->next, "stack->next");
            a = (s32) stack->data;
            stack = HSD_SListRemove(stack);
            stack->data = (void*) ((s32) stack->data - a);
            break;
        case 0x1E:
            HSD_ASSERT(541, stack);
            HSD_ASSERTMSG(541, stack->next, "stack->next");
            a = (s32) stack->data;
            stack = HSD_SListRemove(stack);
            stack->data = (void*) ((s32) stack->data * a);
            break;
        case 0x1F:
            HSD_ASSERT(546, stack);
            HSD_ASSERTMSG(546, stack->next, "stack->next");
            a = (s32) stack->data;
            stack = HSD_SListRemove(stack);
            stack->data = (void*) ((s32) stack->data / a);
            break;
        case 0x20:
            HSD_ASSERT(551, stack);
            HSD_ASSERTMSG(551, stack->next, "stack->next");
            a = (s32) stack->data;
            stack = HSD_SListRemove(stack);
            {
                s32 b = (s32) stack->data;
                stack->data = (void*) (b % a);
            }
            break;
        case 0x21:
            HSD_ASSERT(556, stack);
            HSD_ASSERTMSG(556, stack->next, "stack->next");
            fv = *(f32*) &stack->data;
            stack = HSD_SListRemove(stack);
            fv = powf(*(f32*) &stack->data, fv);
            stack->data = *(void**) &fv;
            break;
        case 0x22:
            HSD_ASSERT(562, stack);
            HSD_ASSERTMSG(562, stack->next, "stack->next");
            fv = *(f32*) &stack->data;
            stack = HSD_SListRemove(stack);
            if (*(f32*) &stack->data > fv) {
                stack->data = *(void**) &fv;
            }
            break;
        case 0x23:
            HSD_ASSERT(569, stack);
            HSD_ASSERTMSG(569, stack->next, "stack->next");
            fv = *(f32*) &stack->data;
            stack = HSD_SListRemove(stack);
            if (*(f32*) &stack->data < fv) {
                stack->data = *(void**) &fv;
            }
            break;
        case 0x24:
            HSD_ASSERT(576, stack);
            HSD_ASSERTMSG(576, stack->next, "stack->next");
            a = (s32) stack->data;
            stack = HSD_SListRemove(stack);
            if ((s32) stack->data > a) {
                stack->data = (void*) a;
            }
            break;
        case 0x25:
            HSD_ASSERT(583, stack);
            HSD_ASSERTMSG(583, stack->next, "stack->next");
            a = (s32) stack->data;
            stack = HSD_SListRemove(stack);
            if ((s32) stack->data < a) {
                stack->data = (void*) a;
            }
            break;
        case 0x26:
            HSD_ASSERT(590, stack);
            HSD_ASSERTMSG(590, stack->next, "stack->next");
            fv = *(f32*) &stack->data;
            stack = HSD_SListRemove(stack);
            {
                f32 fb = *(f32*) &stack->data;
                f32 result;
                {
                    f32 abs_fv = fv;
                    *(s32*) &abs_fv &= 0x7FFFFFFF;
                    if (abs_fv == 0.0F) {
                        if (fb >= 0.0F) {
                            result = 90.0F;
                        } else {
                            result = -90.0F;
                        }
                    } else {
                        result = (f32) (RAD_TO_DEG * atan2f(fb, fv));
                    }
                }
                *(f32*) &stack->data = result;
            }
            break;
        case 0x33:
            HSD_ASSERT(603, stack);
            HSD_ASSERTMSG(603, stack->next, "stack->next");
            fv = *(f32*) &stack->data;
            stack = HSD_SListRemove(stack);
            stack->data = (void*) (*(f32*) &stack->data < fv);
            break;
        case 0x34:
            HSD_ASSERT(608, stack);
            HSD_ASSERTMSG(608, stack->next, "stack->next");
            fv = *(f32*) &stack->data;
            stack = HSD_SListRemove(stack);
            stack->data = (void*) (*(f32*) &stack->data > fv);
            break;
        case 0x35:
            HSD_ASSERT(613, stack);
            HSD_ASSERTMSG(613, stack->next, "stack->next");
            fv = *(f32*) &stack->data;
            stack = HSD_SListRemove(stack);
            stack->data = (void*) (*(f32*) &stack->data <= fv);
            break;
        case 0x36:
            HSD_ASSERT(618, stack);
            HSD_ASSERTMSG(618, stack->next, "stack->next");
            fv = *(f32*) &stack->data;
            stack = HSD_SListRemove(stack);
            stack->data = (void*) (*(f32*) &stack->data >= fv);
            break;
        case 0x37:
            HSD_ASSERT(623, stack);
            HSD_ASSERTMSG(623, stack->next, "stack->next");
            fv = *(f32*) &stack->data;
            stack = HSD_SListRemove(stack);
            stack->data = (void*) (*(f32*) &stack->data == fv);
            break;
        case 0x38:
            HSD_ASSERT(628, stack);
            HSD_ASSERTMSG(628, stack->next, "stack->next");
            fv = *(f32*) &stack->data;
            stack = HSD_SListRemove(stack);
            stack->data = (void*) (*(f32*) &stack->data != fv);
            break;
        case 0x29:
            HSD_ASSERT(633, stack);
            HSD_ASSERTMSG(633, stack->next, "stack->next");
            a = (s32) stack->data;
            stack = HSD_SListRemove(stack);
            stack->data = (void*) ((s32) stack->data < a);
            break;
        case 0x2A:
            HSD_ASSERT(638, stack);
            HSD_ASSERTMSG(638, stack->next, "stack->next");
            a = (s32) stack->data;
            stack = HSD_SListRemove(stack);
            stack->data = (void*) ((s32) stack->data > a);
            break;
        case 0x2B:
            HSD_ASSERT(643, stack);
            HSD_ASSERTMSG(643, stack->next, "stack->next");
            a = (s32) stack->data;
            stack = HSD_SListRemove(stack);
            stack->data = (void*) ((s32) stack->data <= a);
            break;
        case 0x2C:
            HSD_ASSERT(648, stack);
            HSD_ASSERTMSG(648, stack->next, "stack->next");
            a = (s32) stack->data;
            stack = HSD_SListRemove(stack);
            stack->data = (void*) ((s32) stack->data >= a);
            break;
        case 0x2D:
            HSD_ASSERT(653, stack);
            HSD_ASSERTMSG(653, stack->next, "stack->next");
            a = (s32) stack->data;
            stack = HSD_SListRemove(stack);
            stack->data = (void*) (a == (s32) stack->data);
            break;
        case 0x2E:
            HSD_ASSERT(658, stack);
            HSD_ASSERTMSG(658, stack->next, "stack->next");
            a = (s32) stack->data;
            stack = HSD_SListRemove(stack);
            stack->data = (void*) (a != (s32) stack->data);
            break;
        case 0x2F:
            HSD_ASSERT(663, stack);
            HSD_ASSERTMSG(663, stack->next, "stack->next");
            {
                s32 b;
                a = (s32) stack->data;
                stack = HSD_SListRemove(stack);
                b = (s32) stack->data;
                {
                    s32 val = 0;
                    if (b != 0 && a != 0) {
                        val = 1;
                    }
                    stack->data = (void*) val;
                }
            }
            break;
        case 0x30:
            HSD_ASSERT(668, stack);
            HSD_ASSERTMSG(668, stack->next, "stack->next");
            {
                s32 b;
                a = (s32) stack->data;
                stack = HSD_SListRemove(stack);
                b = (s32) stack->data;
                {
                    s32 val = 1;
                    if (b == 0 && a == 0) {
                        val = 0;
                    }
                    stack->data = (void*) val;
                }
            }
            break;
        case 0x32:
            HSD_ASSERT(673, stack);
            HSD_ASSERTMSG(673, stack->next, "stack->next");
            {
                s32 b;
                s32 val;
                a = (s32) stack->data;
                stack = HSD_SListRemove(stack);
                b = (s32) stack->data;
                val = 1;
                {
                    s32 c = 0;
                    if (b == 0 && a != 0) {
                        c = 1;
                    }
                    if (c == 0) {
                        c = 0;
                        if (b != 0 && a == 0) {
                            c = 1;
                        }
                        if (c == 0) {
                            val = 0;
                        }
                    }
                }
                stack->data = (void*) val;
            }
            break;
        case 0x39:
            HSD_ASSERT(678, stack);
            HSD_ASSERTMSG(678, stack->next, "stack->next");
            a = (s32) stack->data;
            stack = HSD_SListRemove(stack);
            stack->data = (void*) ((s32) stack->data & a);
            break;
        case 0x3A:
            HSD_ASSERT(683, stack);
            HSD_ASSERTMSG(683, stack->next, "stack->next");
            a = (s32) stack->data;
            stack = HSD_SListRemove(stack);
            stack->data = (void*) ((s32) stack->data | a);
            break;
        case 0x3B:
            HSD_ASSERT(688, stack);
            HSD_ASSERTMSG(688, stack->next, "stack->next");
            a = (s32) stack->data;
            stack = HSD_SListRemove(stack);
            stack->data = (void*) ((s32) stack->data ^ a);
            break;
        case 0x27:
            HSD_ASSERT(694, stack);
            HSD_ASSERTMSG(694, stack->next, "stack->next");
            {
                s32 lo;
                a = (s32) stack->data;
                stack = HSD_SListRemove(stack);
                lo = (s32) stack->data;
                stack->data =
                    (void*) (lo + HSD_Randi((a - lo) + 1));
            }
            break;
        default:
            OSReport("unexpected opcode 0x%x.\n");
            HSD_Panic("bytecode.c", 700, NULL);
            break;
        }
    }
}
