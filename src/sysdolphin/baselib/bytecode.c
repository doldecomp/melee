#include "bytecode.h"

#include <placeholder.h>
#include <platform.h>

#include "baselib/debug.h"
#include "baselib/list.h"
#include "baselib/random.h"
#include "baselib/util.h"

#include <dolphin/os.h>
#include <melee/lb/lb_00CE.h>
#include <MSL/math.h>
#include <MSL/math_ppc.h>
#include <MSL/trigf.h>

typedef union {
    void* p;
    int i;
    f32 f;
} ByteCodeVal;

static inline float fmodf(float x, float m)
{
    return __fabsf(x) > __fabsf(m) ? x : (m - x * (long long) (m / x));
}

float HSD_ByteCodeEval(u8* bytecode, float* args, int nb_args)
{
    HSD_SList *stack, *list;
    u32 i;
    u8 last_command;
    int operand_count;
    u32 operand;
    f32 fv, f0, f1;
    int d0, d1;

    stack = NULL;
    operand_count = 0;

    if (bytecode == NULL) {
        return 0.0F;
    }

    for (;;) {
        if (operand_count > 0) {
            operand_count--;
            operand = (operand << 8) | *bytecode;
            bytecode++;

            if (operand_count != 0) {
                continue;
            }

            switch (last_command) {
            case 2:
                HSD_ASSERT(281, operand < nb_args);
                stack = HSD_SListAllocAndPrepend(
                    stack, (void*) ((ByteCodeVal*) &args[operand])->i);
                break;
            case 5:
                for (i = 0; i < operand; i++) {
                    stack = HSD_SListRemove(stack);
                }
                break;
            case 0x3C: {
                list = stack;
                i = 0;
                while (list != NULL && i < operand) {
                    list = list->next;
                    i++;
                }
                if (list == NULL) {
                    OSReport("specified stack doesn't exist (%d).\n", operand);
                    HSD_Panic(__FILE__, 299, "");
                } else {
                    stack = HSD_SListAllocAndPrepend(stack, list->data);
                }
                break;
            }
            case 3:
                HSD_ASSERT(307, stack);
                if ((int) stack->data != 0) {
                    bytecode += operand;
                }
                stack = HSD_SListRemove(stack);
                break;
            case 4:
                bytecode += operand;
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

        last_command = *bytecode++;
        switch (last_command) {
        case 0:
            break;
        case 1:
            HSD_ASSERT(339, stack);
            f0 = ((ByteCodeVal*) &stack->data)->f;
            while (stack != NULL) {
                stack = HSD_SListRemove(stack);
            }
            return f0;
        case 5:
        case 0x3C:
        case 0xFF:
            operand_count = 1;
            operand = 0;
            break;
        case 2:
        case 3:
        case 4:
            operand_count = 2;
            operand = 0;
            break;
        case 6:
            operand_count = 4;
            operand = 0;
            break;
        case 7:
            HSD_ASSERT(376, stack);
            {
                ((ByteCodeVal*) &stack->data)->i =
                    (int) ((ByteCodeVal*) &stack->data)->f;
            }
            break;
        case 8:
            HSD_ASSERT(381, stack);
            {
                fv = (f32) ((ByteCodeVal*) &stack->data)->i;
                stack->data = *(void**) &fv;
            }
            break;
        case 9:
            HSD_ASSERT(387, stack);
            fv = -(((ByteCodeVal*) &stack->data)->f);
            stack->data = *(void**) &fv;
            break;
        case 0x0A:
            HSD_ASSERT(393, stack);
            ((ByteCodeVal*) &stack->data)->i =
                -((ByteCodeVal*) &stack->data)->i;
            break;
        case 0x0B:
            HSD_ASSERT(399, stack);
            ((ByteCodeVal*) &stack->data)->i = HSD_Randi(2);
            break;
        case 0x0C:
            HSD_ASSERT(405, stack);
            fv = HSD_Randf();
            stack->data = *(void**) &fv;
            break;
        case 0x0D:
            HSD_ASSERT(411, stack);
            fv = sinf(
                (f32) (DEG_TO_RAD * (f64) ((ByteCodeVal*) &stack->data)->f));
            stack->data = *(void**) &fv;
            break;
        case 0x0E:
            HSD_ASSERT(417, stack);
            fv = cosf(
                (f32) (DEG_TO_RAD * (f64) ((ByteCodeVal*) &stack->data)->f));
            stack->data = *(void**) &fv;
            break;
        case 0x0F:
            HSD_ASSERT(423, stack);
            fv = tanf(
                (f32) (DEG_TO_RAD * (f64) ((ByteCodeVal*) &stack->data)->f));
            stack->data = *(void**) &fv;
            break;
        case 0x10:
            HSD_ASSERT(429, stack);
            fv = (f32) (RAD_TO_DEG * asinf(((ByteCodeVal*) &stack->data)->f));
            stack->data = *(void**) &fv;
            break;
        case 0x11:
            HSD_ASSERT(435, stack);
            fv = (f32) (RAD_TO_DEG * acosf(((ByteCodeVal*) &stack->data)->f));
            stack->data = *(void**) &fv;
            break;
        case 0x12:
            HSD_ASSERT(441, stack);
            fv = (f32) (RAD_TO_DEG * atanf(((ByteCodeVal*) &stack->data)->f));
            stack->data = *(void**) &fv;
            break;
        case 0x13:
            HSD_ASSERT(447, stack);
            fv = logf(((ByteCodeVal*) &stack->data)->f);
            stack->data = *(void**) &fv;
            break;
        case 0x14:
            HSD_ASSERT(453, stack);
            fv = expf(((ByteCodeVal*) &stack->data)->f);
            stack->data = *(void**) &fv;
            break;
        case 0x15:
            HSD_ASSERT(459, stack);
            if (((ByteCodeVal*) &stack->data)->f < 0.0F) {
                fv = -(((ByteCodeVal*) &stack->data)->f);
                stack->data = *(void**) &fv;
            }
            break;
        case 0x28:
            HSD_ASSERTMSG(467, stack, "stack");
            {
                d0 = ((ByteCodeVal*) &stack->data)->i;
                if (d0 < 0) {
                    ((ByteCodeVal*) &stack->data)->i = -d0;
                }
            }
            break;
        case 0x16:
            HSD_ASSERT(474, stack);
            fv = sqrtf(((ByteCodeVal*) &stack->data)->f);
            stack->data = *(void**) &fv;
            break;
        case 0x31:
            HSD_ASSERTMSG(480, stack, "stack");
            stack->data = (void*) !(s32) stack->data;
            break;
        case 0x17:
            HSD_ASSERT(501, stack);
            HSD_ASSERTMSG(501, stack->next, "stack->next");
            f0 = ((ByteCodeVal*) &stack->data)->f;
            stack = HSD_SListRemove(stack);
            fv = ((ByteCodeVal*) &stack->data)->f + f0;
            stack->data = *(void**) &fv;
            break;
        case 0x18:
            HSD_ASSERT(507, stack);
            HSD_ASSERTMSG(507, stack->next, "stack->next");
            f0 = ((ByteCodeVal*) &stack->data)->f;
            stack = HSD_SListRemove(stack);
            fv = ((ByteCodeVal*) &stack->data)->f - f0;
            stack->data = *(void**) &fv;
            break;
        case 0x19:
            HSD_ASSERT(513, stack);
            HSD_ASSERTMSG(513, stack->next, "stack->next");
            f0 = ((ByteCodeVal*) &stack->data)->f;
            stack = HSD_SListRemove(stack);
            fv = ((ByteCodeVal*) &stack->data)->f * f0;
            stack->data = *(void**) &fv;
            break;
        case 0x1A:
            HSD_ASSERT(519, stack);
            HSD_ASSERTMSG(519, stack->next, "stack->next");
            f0 = ((ByteCodeVal*) &stack->data)->f;
            stack = HSD_SListRemove(stack);
            fv = ((ByteCodeVal*) &stack->data)->f / f0;
            stack->data = *(void**) &fv;
            break;
        case 0x1B:
            HSD_ASSERT(525, stack);
            HSD_ASSERTMSG(525, stack->next, "stack->next");
            f0 = ((ByteCodeVal*) &stack->data)->f;
            stack = HSD_SListRemove(stack);
            f1 = ((ByteCodeVal*) &stack->data)->f;
            fv = fmodf(f0, f1);
            stack->data = *(void**) &fv;
            break;
        case 0x1C:
            HSD_ASSERT(531, stack);
            HSD_ASSERTMSG(531, stack->next, "stack->next");
            d1 = ((ByteCodeVal*) &stack->data)->i;
            stack = HSD_SListRemove(stack);
            ((ByteCodeVal*) &stack->data)->i =
                (((ByteCodeVal*) &stack->data)->i + d1);
            break;
        case 0x1D:
            HSD_ASSERT(536, stack);
            HSD_ASSERTMSG(536, stack->next, "stack->next");
            d1 = ((ByteCodeVal*) &stack->data)->i;
            stack = HSD_SListRemove(stack);
            ((ByteCodeVal*) &stack->data)->i =
                (((ByteCodeVal*) &stack->data)->i - d1);
            break;
        case 0x1E:
            HSD_ASSERT(541, stack);
            HSD_ASSERTMSG(541, stack->next, "stack->next");
            d1 = ((ByteCodeVal*) &stack->data)->i;
            stack = HSD_SListRemove(stack);
            ((ByteCodeVal*) &stack->data)->i =
                (((ByteCodeVal*) &stack->data)->i * d1);
            break;
        case 0x1F:
            HSD_ASSERT(546, stack);
            HSD_ASSERTMSG(546, stack->next, "stack->next");
            d1 = ((ByteCodeVal*) &stack->data)->i;
            stack = HSD_SListRemove(stack);
            ((ByteCodeVal*) &stack->data)->i =
                (((ByteCodeVal*) &stack->data)->i / d1);
            break;
        case 0x20:
            HSD_ASSERT(551, stack);
            HSD_ASSERTMSG(551, stack->next, "stack->next");
            d1 = ((ByteCodeVal*) &stack->data)->i;
            stack = HSD_SListRemove(stack);
            d0 = ((ByteCodeVal*) &stack->data)->i;
            ((ByteCodeVal*) &stack->data)->i = (d0 % d1);
            break;
        case 0x21:
            HSD_ASSERT(556, stack);
            HSD_ASSERTMSG(556, stack->next, "stack->next");
            f0 = ((ByteCodeVal*) &stack->data)->f;
            stack = HSD_SListRemove(stack);
            fv = powf(((ByteCodeVal*) &stack->data)->f, f0);
            stack->data = *(void**) &fv;
            break;
        case 0x22:
            HSD_ASSERT(562, stack);
            HSD_ASSERTMSG(562, stack->next, "stack->next");
            f0 = ((ByteCodeVal*) &stack->data)->f;
            stack = HSD_SListRemove(stack);
            if (((ByteCodeVal*) &stack->data)->f > f0) {
                stack->data = *(void**) &f0;
            }
            break;
        case 0x23:
            HSD_ASSERT(569, stack);
            HSD_ASSERTMSG(569, stack->next, "stack->next");
            f0 = ((ByteCodeVal*) &stack->data)->f;
            stack = HSD_SListRemove(stack);
            if (((ByteCodeVal*) &stack->data)->f < f0) {
                stack->data = *(void**) &f0;
            }
            break;
        case 0x24:
            HSD_ASSERT(576, stack);
            HSD_ASSERTMSG(576, stack->next, "stack->next");
            d1 = ((ByteCodeVal*) &stack->data)->i;
            stack = HSD_SListRemove(stack);
            if (((ByteCodeVal*) &stack->data)->i > d1) {
                ((ByteCodeVal*) &stack->data)->i = d1;
            }
            break;
        case 0x25:
            HSD_ASSERT(583, stack);
            HSD_ASSERTMSG(583, stack->next, "stack->next");
            d1 = ((ByteCodeVal*) &stack->data)->i;
            stack = HSD_SListRemove(stack);
            if (((ByteCodeVal*) &stack->data)->i < d1) {
                ((ByteCodeVal*) &stack->data)->i = d1;
            }
            break;
        case 0x26:
            HSD_ASSERT(590, stack);
            HSD_ASSERTMSG(590, stack->next, "stack->next");
            f0 = ((ByteCodeVal*) &stack->data)->f;
            stack = HSD_SListRemove(stack);
            f1 = ((ByteCodeVal*) &stack->data)->f;
            {
                {
                    if (fabsf_bitwise(f0) == 0.0F) {
                        fv = f1 >= 0.0F ? 90.0F : -90.0F;
                    } else {
                        fv = (f32) (RAD_TO_DEG * atan2f(f1, f0));
                    }
                }
                stack->data = *(void**) &fv;
            }
            break;
        case 0x33:
            HSD_ASSERT(603, stack);
            HSD_ASSERTMSG(603, stack->next, "stack->next");
            f0 = ((ByteCodeVal*) &stack->data)->f;
            stack = HSD_SListRemove(stack);
            f1 = ((ByteCodeVal*) &stack->data)->f;
            ((ByteCodeVal*) &stack->data)->i = (f1 < f0);
            break;
        case 0x34:
            HSD_ASSERT(608, stack);
            HSD_ASSERTMSG(608, stack->next, "stack->next");
            f0 = ((ByteCodeVal*) &stack->data)->f;
            stack = HSD_SListRemove(stack);
            f1 = ((ByteCodeVal*) &stack->data)->f;
            ((ByteCodeVal*) &stack->data)->i = (f1 > f0);
            break;
        case 0x35:
            HSD_ASSERT(613, stack);
            HSD_ASSERTMSG(613, stack->next, "stack->next");
            f0 = ((ByteCodeVal*) &stack->data)->f;
            stack = HSD_SListRemove(stack);
            ((ByteCodeVal*) &stack->data)->i =
                (((ByteCodeVal*) &stack->data)->f <= f0);
            break;
        case 0x36:
            HSD_ASSERT(618, stack);
            HSD_ASSERTMSG(618, stack->next, "stack->next");
            f0 = ((ByteCodeVal*) &stack->data)->f;
            stack = HSD_SListRemove(stack);
            f1 = ((ByteCodeVal*) &stack->data)->f;
            ((ByteCodeVal*) &stack->data)->i = (f1 >= f0);
            break;
        case 0x37:
            HSD_ASSERT(623, stack);
            HSD_ASSERTMSG(623, stack->next, "stack->next");
            f0 = ((ByteCodeVal*) &stack->data)->f;
            stack = HSD_SListRemove(stack);
            f1 = ((ByteCodeVal*) &stack->data)->f;
            ((ByteCodeVal*) &stack->data)->i = (f1 == f0);
            break;
        case 0x38:
            HSD_ASSERT(628, stack);
            HSD_ASSERTMSG(628, stack->next, "stack->next");
            f0 = ((ByteCodeVal*) &stack->data)->f;
            stack = HSD_SListRemove(stack);
            f1 = ((ByteCodeVal*) &stack->data)->f;
            ((ByteCodeVal*) &stack->data)->i = (f1 != f0);
            break;
        case 0x29:
            HSD_ASSERT(633, stack);
            HSD_ASSERTMSG(633, stack->next, "stack->next");
            d1 = ((ByteCodeVal*) &stack->data)->i;
            stack = HSD_SListRemove(stack);
            ((ByteCodeVal*) &stack->data)->i =
                (((ByteCodeVal*) &stack->data)->i < d1);
            break;
        case 0x2A:
            HSD_ASSERT(638, stack);
            HSD_ASSERTMSG(638, stack->next, "stack->next");
            d1 = ((ByteCodeVal*) &stack->data)->i;
            stack = HSD_SListRemove(stack);
            ((ByteCodeVal*) &stack->data)->i =
                (((ByteCodeVal*) &stack->data)->i > d1);
            break;
        case 0x2B:
            HSD_ASSERT(643, stack);
            HSD_ASSERTMSG(643, stack->next, "stack->next");
            d1 = ((ByteCodeVal*) &stack->data)->i;
            stack = HSD_SListRemove(stack);
            ((ByteCodeVal*) &stack->data)->i =
                (((ByteCodeVal*) &stack->data)->i <= d1);
            break;
        case 0x2C:
            HSD_ASSERT(648, stack);
            HSD_ASSERTMSG(648, stack->next, "stack->next");
            d1 = ((ByteCodeVal*) &stack->data)->i;
            stack = HSD_SListRemove(stack);
            ((ByteCodeVal*) &stack->data)->i =
                (((ByteCodeVal*) &stack->data)->i >= d1);
            break;
        case 0x2D:
            HSD_ASSERT(653, stack);
            HSD_ASSERTMSG(653, stack->next, "stack->next");
            d1 = ((ByteCodeVal*) &stack->data)->i;
            stack = HSD_SListRemove(stack);
            ((ByteCodeVal*) &stack->data)->i =
                (((ByteCodeVal*) &stack->data)->i == d1);
            break;
        case 0x2E:
            HSD_ASSERT(658, stack);
            HSD_ASSERTMSG(658, stack->next, "stack->next");
            d1 = ((ByteCodeVal*) &stack->data)->i;
            stack = HSD_SListRemove(stack);
            ((ByteCodeVal*) &stack->data)->i =
                (((ByteCodeVal*) &stack->data)->i != d1);
            break;
        case 0x2F:
            HSD_ASSERT(663, stack);
            HSD_ASSERTMSG(663, stack->next, "stack->next");
            d1 = ((ByteCodeVal*) &stack->data)->i;
            stack = HSD_SListRemove(stack);
            d0 = ((ByteCodeVal*) &stack->data)->i;
            {
                int val = 0;
                if (d0 != 0 && d1 != 0) {
                    val = 1;
                }
                ((ByteCodeVal*) &stack->data)->i = val;
            }
            break;
        case 0x30:
            HSD_ASSERT(668, stack);
            HSD_ASSERTMSG(668, stack->next, "stack->next");
            d1 = ((ByteCodeVal*) &stack->data)->i;
            stack = HSD_SListRemove(stack);
            d0 = ((ByteCodeVal*) &stack->data)->i;
            {
                int val = 1;
                if (d0 == 0 && d1 == 0) {
                    val = 0;
                }
                ((ByteCodeVal*) &stack->data)->i = val;
            }
            break;
        case 0x32:
            HSD_ASSERT(673, stack);
            HSD_ASSERTMSG(673, stack->next, "stack->next");
            {
                bool c, val;
                d1 = ((ByteCodeVal*) &stack->data)->i;
                stack = HSD_SListRemove(stack);
                d0 = ((ByteCodeVal*) &stack->data)->i;
                val = true;
                c = false;
                if ((d0 == 0 && d1 != 0)) {
                    c = true;
                }
                if (c == false) {
                    c = false;
                    if (d0 != 0 && d1 == 0) {
                        c = true;
                    }
                    if (c == false) {
                        val = false;
                    }
                }
                ((ByteCodeVal*) &stack->data)->i = val;
            }
            break;
        case 0x39:
            HSD_ASSERT(678, stack);
            HSD_ASSERTMSG(678, stack->next, "stack->next");
            d1 = ((ByteCodeVal*) &stack->data)->i;
            stack = HSD_SListRemove(stack);
            stack->data = (void*) (((ByteCodeVal*) &stack->data)->i & d1);
            break;
        case 0x3A:
            HSD_ASSERT(683, stack);
            HSD_ASSERTMSG(683, stack->next, "stack->next");
            d1 = ((ByteCodeVal*) &stack->data)->i;
            stack = HSD_SListRemove(stack);
            stack->data = (void*) (((ByteCodeVal*) &stack->data)->i | d1);
            break;
        case 0x3B:
            HSD_ASSERT(688, stack);
            HSD_ASSERTMSG(688, stack->next, "stack->next");
            d1 = ((ByteCodeVal*) &stack->data)->i;
            stack = HSD_SListRemove(stack);
            stack->data = (void*) (((ByteCodeVal*) &stack->data)->i ^ d1);
            break;
        case 0x27:
            HSD_ASSERT(694, stack);
            HSD_ASSERTMSG(694, stack->next, "stack->next");
            d1 = ((ByteCodeVal*) &stack->data)->i;
            stack = HSD_SListRemove(stack);
            d0 = ((ByteCodeVal*) &stack->data)->i;
            ((ByteCodeVal*) &stack->data)->i = (d0 + HSD_Randi((d1 - d0) + 1));
            break;
        default:
            OSReport("unexpected opcode 0x%x.\n", last_command);
            HSD_Panic(__FILE__, 700, "");
            break;
        }
    }
}
