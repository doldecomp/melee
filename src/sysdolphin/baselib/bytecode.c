/**
 * @file bytecode.c
 * @brief SysDolphin Bytecode Virtual Machine
 * @details Implements a simple stack-based interpreter for executing bytecode scripts.
 * Often used for evaluating mathematical expressions or subaction event parameters.
 */
#include "bytecode.h"

#include <Runtime/platform.h>

#include <math.h>

#include "debug.h"
#include "list.h"
#include "random.h"
#include "util.h"
#include <dolphin/os.h>

typedef union {
    void* p;
    int i;
    f32 f;
} ByteCodeVal;

/**
 * @brief Evaluates a bytecode expression and returns a float result.
 * @param bytecode Pointer to the bytecode instruction stream.
 * @param args Array of float arguments passed to the script.
 * @param nb_args Number of arguments in the args array.
 * @return The final evaluated float value.
 */
float HSD_ByteCodeEval(u8* bytecode, const f32* args, s32 nb_args)
{
    HSD_SList* eval_stack;
    int i;
    u8 opcode;
    s32 operand_count;
    u32 instruction_operand;
    HSD_SList* list;
    f32 float_result, float_op1, float_op2;
    s32 int_op1, int_op2;

    eval_stack = NULL;
    operand_count = 0;

    if (bytecode == NULL) {
        return 0.0F;
    }

    for (;;) {
        if (operand_count > 0) {
            operand_count--;
            instruction_operand = (instruction_operand << 8) | *bytecode;
            bytecode++;

            if (operand_count != 0) {
                continue;
            }

            switch (opcode) {
            case 2: // PUSH_ARG
                HSD_ASSERT(281, instruction_operand < nb_args);
                eval_stack = HSD_SListAllocAndPrepend(
                    eval_stack, (void*) ((ByteCodeVal*) &args[instruction_operand])->i);
                break;
            case 5: // POP
                for (i = 0; i < instruction_operand; i++) {
                    eval_stack = HSD_SListRemove(eval_stack);
                }
                break;
            case 0x3C: { // DUP_N (Push from stack offset)
                list = eval_stack;
                i = 0;
                while (list != NULL && i < instruction_operand) {
                    list = list->next;
                    i++;
                }
                if (list == NULL) {
                    OSReport("specified stack doesn't exist (%d).\n", instruction_operand);
                    HSD_Panic(__FILE__, 299, "");
                } else {
                    eval_stack = HSD_SListAllocAndPrepend(eval_stack, list->data);
                }
                break;
            }
            case 3: // JUMP_IF_TRUE
                HSD_ASSERT(307, eval_stack);
                if ((int) eval_stack->data != 0) {
                    bytecode += instruction_operand;
                }
                eval_stack = HSD_SListRemove(eval_stack);
                break;
            case 4: // JUMP
                bytecode += instruction_operand;
                break;
            case 6: // PUSH_INT
                eval_stack = HSD_SListAllocAndPrepend(eval_stack, (void*) instruction_operand);
                break;
            case 0xFF: // NOT_IMPLEMENTED
                HSD_Panic(__FILE__, 323, "not yet implemented.\n");
                /* fallthrough */
            default:
                HSD_Panic(__FILE__, 326, "unexpected byte code.\n");
                break;
            }
            continue;
        }

        opcode = *bytecode++;
        switch (opcode) {
        case 0: // NOP
            break;
        case 1: // RETURN
            HSD_ASSERT(339, eval_stack);
            float_op1 = ((ByteCodeVal*) &eval_stack->data)->f;
            while (eval_stack != NULL) {
                eval_stack = HSD_SListRemove(eval_stack);
            }
            return float_op1;
        case 5:
        case 0x3C:
        case 0xFF:
            operand_count = 1;
            instruction_operand = 0;
            break;
        case 2:
        case 3:
        case 4:
            operand_count = 2;
            instruction_operand = 0;
            break;
        case 6:
            operand_count = 4;
            instruction_operand = 0;
            break;
        case 7: // FLOAT_TO_INT
            HSD_ASSERT(376, eval_stack);
            {
                ((ByteCodeVal*) &eval_stack->data)->i =
                    (int) ((ByteCodeVal*) &eval_stack->data)->f;
            }
            break;
        case 8: // INT_TO_FLOAT
            HSD_ASSERT(381, eval_stack);
            {
                float_result = (f32) ((ByteCodeVal*) &eval_stack->data)->i;
                eval_stack->data = *(void**) &float_result;
            }
            break;
        case 9: // NEG_FLOAT
            HSD_ASSERT(387, eval_stack);
            float_result = -(((ByteCodeVal*) &eval_stack->data)->f);
            eval_stack->data = *(void**) &float_result;
            break;
        case 0x0A: // NEG_INT
            HSD_ASSERT(393, eval_stack);
            ((ByteCodeVal*) &eval_stack->data)->i =
                -((ByteCodeVal*) &eval_stack->data)->i;
            break;
        case 0x0B: // RAND_INT_2
            HSD_ASSERT(399, eval_stack);
            ((ByteCodeVal*) &eval_stack->data)->i = HSD_Randi(2);
            break;
        case 0x0C: // RAND_FLOAT
            HSD_ASSERT(405, eval_stack);
            float_result = HSD_Randf();
            eval_stack->data = *(void**) &float_result;
            break;
        case 0x0D: // SIND
            HSD_ASSERT(411, eval_stack);
            float_result = sinf(
                (f32) (DEG_TO_RAD * (f64) ((ByteCodeVal*) &eval_stack->data)->f));
            eval_stack->data = *(void**) &float_result;
            break;
        case 0x0E: // COSD
            HSD_ASSERT(417, eval_stack);
            float_result = cosf(
                (f32) (DEG_TO_RAD * (f64) ((ByteCodeVal*) &eval_stack->data)->f));
            eval_stack->data = *(void**) &float_result;
            break;
        case 0x0F: // TAND
            HSD_ASSERT(423, eval_stack);
            float_result = tanf(
                (f32) (DEG_TO_RAD * (f64) ((ByteCodeVal*) &eval_stack->data)->f));
            eval_stack->data = *(void**) &float_result;
            break;
        case 0x10: // ASIND
            HSD_ASSERT(429, eval_stack);
            float_result = (f32) (RAD_TO_DEG * asinf(((ByteCodeVal*) &eval_stack->data)->f));
            eval_stack->data = *(void**) &float_result;
            break;
        case 0x11: // ACOSD
            HSD_ASSERT(435, eval_stack);
            float_result = (f32) (RAD_TO_DEG * acosf(((ByteCodeVal*) &eval_stack->data)->f));
            eval_stack->data = *(void**) &float_result;
            break;
        case 0x12: // ATAND
            HSD_ASSERT(441, eval_stack);
            float_result = (f32) (RAD_TO_DEG * atanf(((ByteCodeVal*) &eval_stack->data)->f));
            eval_stack->data = *(void**) &float_result;
            break;
        case 0x13: // LOGF
            HSD_ASSERT(447, eval_stack);
            float_result = logf(((ByteCodeVal*) &eval_stack->data)->f);
            eval_stack->data = *(void**) &float_result;
            break;
        case 0x14: // EXPF
            HSD_ASSERT(453, eval_stack);
            float_result = expf(((ByteCodeVal*) &eval_stack->data)->f);
            eval_stack->data = *(void**) &float_result;
            break;
        case 0x15: // ABS_FLOAT
            HSD_ASSERT(459, eval_stack);
            if (((ByteCodeVal*) &eval_stack->data)->f < 0.0F) {
                float_result = -(((ByteCodeVal*) &eval_stack->data)->f);
                eval_stack->data = *(void**) &float_result;
            }
            break;
        case 0x28: // ABS_INT
            HSD_ASSERT(467, eval_stack);
            {
                int_op1 = ((ByteCodeVal*) &eval_stack->data)->i;
                if (int_op1 < 0) {
                    ((ByteCodeVal*) &eval_stack->data)->i = -int_op1;
                }
            }
            break;
        case 0x16: // SQRTF
            HSD_ASSERT(474, eval_stack);
            float_result = sqrtf(((ByteCodeVal*) &eval_stack->data)->f);
            eval_stack->data = *(void**) &float_result;
            break;
        case 0x31: // NOT_LOGICAL
            HSD_ASSERT(480, eval_stack);
            eval_stack->data = (void*) !(s32) eval_stack->data;
            break;
        case 0x17: // ADD_FLOAT
            HSD_ASSERT(501, eval_stack);
            HSD_ASSERT(501, eval_stack->next);
            float_op1 = ((ByteCodeVal*) &eval_stack->data)->f;
            eval_stack = HSD_SListRemove(eval_stack);
            float_result = ((ByteCodeVal*) &eval_stack->data)->f + float_op1;
            eval_stack->data = *(void**) &float_result;
            break;
        case 0x18: // SUB_FLOAT
            HSD_ASSERT(507, eval_stack);
            HSD_ASSERT(507, eval_stack->next);
            float_op1 = ((ByteCodeVal*) &eval_stack->data)->f;
            eval_stack = HSD_SListRemove(eval_stack);
            float_result = ((ByteCodeVal*) &eval_stack->data)->f - float_op1;
            eval_stack->data = *(void**) &float_result;
            break;
        case 0x19: // MUL_FLOAT
            HSD_ASSERT(513, eval_stack);
            HSD_ASSERT(513, eval_stack->next);
            float_op1 = ((ByteCodeVal*) &eval_stack->data)->f;
            eval_stack = HSD_SListRemove(eval_stack);
            float_result = ((ByteCodeVal*) &eval_stack->data)->f * float_op1;
            eval_stack->data = *(void**) &float_result;
            break;
        case 0x1A: // DIV_FLOAT
            HSD_ASSERT(519, eval_stack);
            HSD_ASSERT(519, eval_stack->next);
            float_op1 = ((ByteCodeVal*) &eval_stack->data)->f;
            eval_stack = HSD_SListRemove(eval_stack);
            float_result = ((ByteCodeVal*) &eval_stack->data)->f / float_op1;
            eval_stack->data = *(void**) &float_result;
            break;
        case 0x1B: // FMOD
            HSD_ASSERT(525, eval_stack);
            HSD_ASSERT(525, eval_stack->next);
            float_op1 = ((ByteCodeVal*) &eval_stack->data)->f;
            eval_stack = HSD_SListRemove(eval_stack);
            float_op2 =
#ifdef MUST_MATCH
                float_op2 =
#endif
                    ((ByteCodeVal*) &eval_stack->data)->f;
            float_result = fmodf(float_op2, float_op1);
            eval_stack->data = *(void**) &float_result;
            break;
        case 0x1C: // ADD_INT
            HSD_ASSERT(531, eval_stack);
            HSD_ASSERT(531, eval_stack->next);
            int_op2 = ((ByteCodeVal*) &eval_stack->data)->i;
            eval_stack = HSD_SListRemove(eval_stack);
            ((ByteCodeVal*) &eval_stack->data)->i =
                (((ByteCodeVal*) &eval_stack->data)->i + int_op2);
            break;
        case 0x1D: // SUB_INT
            HSD_ASSERT(536, eval_stack);
            HSD_ASSERT(536, eval_stack->next);
            int_op2 = ((ByteCodeVal*) &eval_stack->data)->i;
            eval_stack = HSD_SListRemove(eval_stack);
            ((ByteCodeVal*) &eval_stack->data)->i =
                (((ByteCodeVal*) &eval_stack->data)->i - int_op2);
            break;
        case 0x1E: // MUL_INT
            HSD_ASSERT(541, eval_stack);
            HSD_ASSERT(541, eval_stack->next);
            int_op2 = ((ByteCodeVal*) &eval_stack->data)->i;
            eval_stack = HSD_SListRemove(eval_stack);
            ((ByteCodeVal*) &eval_stack->data)->i =
                (((ByteCodeVal*) &eval_stack->data)->i * int_op2);
            break;
        case 0x1F: // DIV_INT
            HSD_ASSERT(546, eval_stack);
            HSD_ASSERT(546, eval_stack->next);
            int_op2 = ((ByteCodeVal*) &eval_stack->data)->i;
            eval_stack = HSD_SListRemove(eval_stack);
            ((ByteCodeVal*) &eval_stack->data)->i =
                (((ByteCodeVal*) &eval_stack->data)->i / int_op2);
            break;
        case 0x20: // MOD_INT
            HSD_ASSERT(551, eval_stack);
            HSD_ASSERT(551, eval_stack->next);
            int_op2 = ((ByteCodeVal*) &eval_stack->data)->i;
            eval_stack = HSD_SListRemove(eval_stack);
            int_op1 = ((ByteCodeVal*) &eval_stack->data)->i;
            ((ByteCodeVal*) &eval_stack->data)->i = (int_op1 % int_op2);
            break;
        case 0x21: // POWF
            HSD_ASSERT(556, eval_stack);
            HSD_ASSERT(556, eval_stack->next);
            float_op1 = ((ByteCodeVal*) &eval_stack->data)->f;
            eval_stack = HSD_SListRemove(eval_stack);
            float_result = powf(((ByteCodeVal*) &eval_stack->data)->f, float_op1);
            eval_stack->data = *(void**) &float_result;
            break;
        case 0x22: // MAX_FLOAT
            HSD_ASSERT(562, eval_stack);
            HSD_ASSERT(562, eval_stack->next);
            float_op1 = ((ByteCodeVal*) &eval_stack->data)->f;
            eval_stack = HSD_SListRemove(eval_stack);
            if (((ByteCodeVal*) &eval_stack->data)->f > float_op1) {
                eval_stack->data = *(void**) &float_op1;
            }
            break;
        case 0x23: // MIN_FLOAT
            HSD_ASSERT(569, eval_stack);
            HSD_ASSERT(569, eval_stack->next);
            float_op1 = ((ByteCodeVal*) &eval_stack->data)->f;
            eval_stack = HSD_SListRemove(eval_stack);
            if (((ByteCodeVal*) &eval_stack->data)->f < float_op1) {
                eval_stack->data = *(void**) &float_op1;
            }
            break;
        case 0x24: // MAX_INT
            HSD_ASSERT(576, eval_stack);
            HSD_ASSERT(576, eval_stack->next);
            int_op2 = ((ByteCodeVal*) &eval_stack->data)->i;
            eval_stack = HSD_SListRemove(eval_stack);
            if (((ByteCodeVal*) &eval_stack->data)->i > int_op2) {
                ((ByteCodeVal*) &eval_stack->data)->i = int_op2;
            }
            break;
        case 0x25: // MIN_INT
            HSD_ASSERT(583, eval_stack);
            HSD_ASSERT(583, eval_stack->next);
            int_op2 = ((ByteCodeVal*) &eval_stack->data)->i;
            eval_stack = HSD_SListRemove(eval_stack);
            if (((ByteCodeVal*) &eval_stack->data)->i < int_op2) {
                ((ByteCodeVal*) &eval_stack->data)->i = int_op2;
            }
            break;
        case 0x26: // ATAN2D
            HSD_ASSERT(590, eval_stack);
            HSD_ASSERT(590, eval_stack->next);
            float_op1 = ((ByteCodeVal*) &eval_stack->data)->f;
            eval_stack = HSD_SListRemove(eval_stack);
            float_op2 = ((ByteCodeVal*) &eval_stack->data)->f;
            if (fabsf_bitwise(float_op1) == 0.0F) {
                float_result = float_op2 >= 0.0F ? 90.0F : -90.0F;
            } else {
                float_result = (f32) (RAD_TO_DEG * atan2f(float_op2, float_op1));
            }
            eval_stack->data = *(void**) &float_result;
            break;
        case 0x33: // LT_FLOAT
            HSD_ASSERT(603, eval_stack);
            HSD_ASSERT(603, eval_stack->next);
            float_op1 = ((ByteCodeVal*) &eval_stack->data)->f;
            eval_stack = HSD_SListRemove(eval_stack);
            float_op2 = ((ByteCodeVal*) &eval_stack->data)->f;
            ((ByteCodeVal*) &eval_stack->data)->i = (float_op2 < float_op1);
            break;
        case 0x34: // GT_FLOAT
            HSD_ASSERT(608, eval_stack);
            HSD_ASSERT(608, eval_stack->next);
            float_op1 = ((ByteCodeVal*) &eval_stack->data)->f;
            eval_stack = HSD_SListRemove(eval_stack);
            float_op2 = ((ByteCodeVal*) &eval_stack->data)->f;
            ((ByteCodeVal*) &eval_stack->data)->i = (float_op2 > float_op1);
            break;
        case 0x35: // LE_FLOAT
            HSD_ASSERT(613, eval_stack);
            HSD_ASSERT(613, eval_stack->next);
            float_op1 = ((ByteCodeVal*) &eval_stack->data)->f;
            eval_stack = HSD_SListRemove(eval_stack);
            ((ByteCodeVal*) &eval_stack->data)->i =
                (((ByteCodeVal*) &eval_stack->data)->f <= float_op1);
            break;
        case 0x36: // GE_FLOAT
            HSD_ASSERT(618, eval_stack);
            HSD_ASSERT(618, eval_stack->next);
            float_op1 = ((ByteCodeVal*) &eval_stack->data)->f;
            eval_stack = HSD_SListRemove(eval_stack);
            float_op2 = ((ByteCodeVal*) &eval_stack->data)->f;
            ((ByteCodeVal*) &eval_stack->data)->i = (float_op2 >= float_op1);
            break;
        case 0x37: // EQ_FLOAT
            HSD_ASSERT(623, eval_stack);
            HSD_ASSERT(623, eval_stack->next);
            float_op1 = ((ByteCodeVal*) &eval_stack->data)->f;
            eval_stack = HSD_SListRemove(eval_stack);
            float_op2 = ((ByteCodeVal*) &eval_stack->data)->f;
            ((ByteCodeVal*) &eval_stack->data)->i = (float_op2 == float_op1);
            break;
        case 0x38: // NE_FLOAT
            HSD_ASSERT(628, eval_stack);
            HSD_ASSERT(628, eval_stack->next);
            float_op1 = ((ByteCodeVal*) &eval_stack->data)->f;
            eval_stack = HSD_SListRemove(eval_stack);
            float_op2 = ((ByteCodeVal*) &eval_stack->data)->f;
            ((ByteCodeVal*) &eval_stack->data)->i = (float_op2 != float_op1);
            break;
        case 0x29: // LT_INT
            HSD_ASSERT(633, eval_stack);
            HSD_ASSERT(633, eval_stack->next);
            int_op2 = ((ByteCodeVal*) &eval_stack->data)->i;
            eval_stack = HSD_SListRemove(eval_stack);
            ((ByteCodeVal*) &eval_stack->data)->i =
                (((ByteCodeVal*) &eval_stack->data)->i < int_op2);
            break;
        case 0x2A: // GT_INT
            HSD_ASSERT(638, eval_stack);
            HSD_ASSERT(638, eval_stack->next);
            int_op2 = ((ByteCodeVal*) &eval_stack->data)->i;
            eval_stack = HSD_SListRemove(eval_stack);
            ((ByteCodeVal*) &eval_stack->data)->i =
                (((ByteCodeVal*) &eval_stack->data)->i > int_op2);
            break;
        case 0x2B: // LE_INT
            HSD_ASSERT(643, eval_stack);
            HSD_ASSERT(643, eval_stack->next);
            int_op2 = ((ByteCodeVal*) &eval_stack->data)->i;
            eval_stack = HSD_SListRemove(eval_stack);
            ((ByteCodeVal*) &eval_stack->data)->i =
                (((ByteCodeVal*) &eval_stack->data)->i <= int_op2);
            break;
        case 0x2C: // GE_INT
            HSD_ASSERT(648, eval_stack);
            HSD_ASSERT(648, eval_stack->next);
            int_op2 = ((ByteCodeVal*) &eval_stack->data)->i;
            eval_stack = HSD_SListRemove(eval_stack);
            ((ByteCodeVal*) &eval_stack->data)->i =
                (((ByteCodeVal*) &eval_stack->data)->i >= int_op2);
            break;
        case 0x2D: // EQ_INT
            HSD_ASSERT(653, eval_stack);
            HSD_ASSERT(653, eval_stack->next);
            int_op2 = ((ByteCodeVal*) &eval_stack->data)->i;
            eval_stack = HSD_SListRemove(eval_stack);
            ((ByteCodeVal*) &eval_stack->data)->i =
                (((ByteCodeVal*) &eval_stack->data)->i == int_op2);
            break;
        case 0x2E: // NE_INT
            HSD_ASSERT(658, eval_stack);
            HSD_ASSERT(658, eval_stack->next);
            int_op2 = ((ByteCodeVal*) &eval_stack->data)->i;
            eval_stack = HSD_SListRemove(eval_stack);
            ((ByteCodeVal*) &eval_stack->data)->i =
                (((ByteCodeVal*) &eval_stack->data)->i != int_op2);
            break;
        case 0x2F: // AND_LOGICAL
            HSD_ASSERT(663, eval_stack);
            HSD_ASSERT(663, eval_stack->next);
            int_op2 = ((ByteCodeVal*) &eval_stack->data)->i;
            eval_stack = HSD_SListRemove(eval_stack);
            int_op1 = ((ByteCodeVal*) &eval_stack->data)->i;
            {
                int val = 0;
                if (int_op1 != 0 && int_op2 != 0) {
                    val = 1;
                }
                ((ByteCodeVal*) &eval_stack->data)->i = val;
            }
            break;
        case 0x30: // OR_LOGICAL
            HSD_ASSERT(668, eval_stack);
            HSD_ASSERT(668, eval_stack->next);
            int_op2 = ((ByteCodeVal*) &eval_stack->data)->i;
            eval_stack = HSD_SListRemove(eval_stack);
            int_op1 = ((ByteCodeVal*) &eval_stack->data)->i;
            {
                int val = 1;
                if (int_op1 == 0 && int_op2 == 0) {
                    val = 0;
                }
                ((ByteCodeVal*) &eval_stack->data)->i = val;
            }
            break;
        case 0x32: // XOR_LOGICAL
            HSD_ASSERT(673, eval_stack);
            HSD_ASSERT(673, eval_stack->next);
            int_op2 = ((ByteCodeVal*) &eval_stack->data)->i;
            eval_stack = HSD_SListRemove(eval_stack);
            int_op1 = ((ByteCodeVal*) &eval_stack->data)->i;
            ((ByteCodeVal*) &eval_stack->data)->i =
                (int_op1 == 0 && int_op2 != 0) || (int_op1 != 0 && int_op2 == 0);
            break;
        case 0x39: // BITWISE_AND
            HSD_ASSERT(678, eval_stack);
            HSD_ASSERT(678, eval_stack->next);
            int_op2 = ((ByteCodeVal*) &eval_stack->data)->i;
            eval_stack = HSD_SListRemove(eval_stack);
            eval_stack->data = (void*) (((ByteCodeVal*) &eval_stack->data)->i & int_op2);
            break;
        case 0x3A: // BITWISE_OR
            HSD_ASSERT(683, eval_stack);
            HSD_ASSERT(683, eval_stack->next);
            int_op2 = ((ByteCodeVal*) &eval_stack->data)->i;
            eval_stack = HSD_SListRemove(eval_stack);
            eval_stack->data = (void*) (((ByteCodeVal*) &eval_stack->data)->i | int_op2);
            break;
        case 0x3B: // BITWISE_XOR
            HSD_ASSERT(688, eval_stack);
            HSD_ASSERT(688, eval_stack->next);
            int_op2 = ((ByteCodeVal*) &eval_stack->data)->i;
            eval_stack = HSD_SListRemove(eval_stack);
            eval_stack->data = (void*) (((ByteCodeVal*) &eval_stack->data)->i ^ int_op2);
            break;
        case 0x27: // RANDI_RANGE
            HSD_ASSERT(694, eval_stack);
            HSD_ASSERT(694, eval_stack->next);
            int_op2 = ((ByteCodeVal*) &eval_stack->data)->i;
            eval_stack = HSD_SListRemove(eval_stack);
            int_op1 = ((ByteCodeVal*) &eval_stack->data)->i;
            ((ByteCodeVal*) &eval_stack->data)->i = (int_op1 + HSD_Randi((int_op2 - int_op1) + 1));
            break;
        default:
            OSReport("unexpected opcode 0x%x.\n", opcode);
            HSD_Panic(__FILE__, 700, "");
            break;
        }
    }
}
