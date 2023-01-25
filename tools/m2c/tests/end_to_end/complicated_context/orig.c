int globali;
float globalf;

#define IGNORED
#define IGNORED2(...) a \
    line \
    continuation
union SomeUnion {
    double double_innerfield;
    char char_innerfield;
};

typedef int Int;
typedef Int Int;

enum SomeEnum
{
    FIRST_ELEM,
    SECOND_ELEM = 2,
    THIRD_ELEM = SECOND_ELEM * 3,
    FOURTH_ELEM,
    FIFTH_ELEM,
};

struct SomeBitfield {
    char char_bit : 1;
    Int int_bit : 4;
    short short_bit : 16;
    char : 0;
    unsigned char unsigned_bit : 7;
};

struct SomeStruct
{
    Int int_field;
    float float_field;
    void *pointer_field;
    union SomeUnion data_field;
    enum SomeEnum enum_field;
    enum {
        MORE_ENUM = SECOND_ELEM,
    } anon_enum_field;
    struct {
        int sub;
    } anon_struct_field;
    struct SubStruct {
        int x;
    };
    union {
        int anon_union_field1;
        float anon_union_field2;
    };
    struct SubStruct inner_struct_field;
    long long long_long_field;
    struct SomeBitfield bitfield_field;
    char array_arithmetic_1[1 + 1];
    char array_arithmetic_2[2 - 1];
    char array_arithmetic_3[1 * 1];
    char array_arithmetic_4[1 << 1];
    char array_arithmetic_5[2 >> 1];
    char array_arithmetic_6[SECOND_ELEM];
    char array_arithmetic_7[16 + (~1)];
    char array_arithmetic_8[16 + (!0)];
    char array_arithmetic_9[16 + (-1)];
    char array_arithmetic_10[16 + 5 / 2];
    char array_arithmetic_11[16 + (-5) / 2];
    char array_arithmetic_12[16 + (-5) / (-2)];
    char array_arithmetic_13[16 + 5 / (-2)];
    char array_arithmetic_14[16 + 5 % 2];
    char array_arithmetic_15[16 + (-5) % 2];
    char array_arithmetic_16[16 + (-5) % (-2)];
    char array_arithmetic_17[16 + 5 % (-2)];
    char array_arithmetic_18[16 + (0 && (1/0))];
    char array_arithmetic_19[16 + (1 && 0)];
    char array_arithmetic_20[16 + (1 && 1)];
    char array_arithmetic_21[16 + (1 || (1/0))];
    char array_arithmetic_22[16 + (0 || 0)];
    char array_arithmetic_23[16 + (0 || 1)];
    char array_arithmetic_24[16 + (1 >= 0)];
    char array_arithmetic_25[16 + (1 > 0)];
    char array_arithmetic_26[16 + (1 <= 0)];
    char array_arithmetic_27[16 + (1 < 0)];
    char array_arithmetic_28[16 + (1 == 0)];
    char array_arithmetic_29[16 + (1 != 0)];
    char array_arithmetic_30[16 + (5 ^ 3)];
    char array_arithmetic_31[16 + (5 & 3)];
    char array_arithmetic_32[16 + (5 | 3)];
    char array_arithmetic_33[16 + (1 ? 2 : 3)];
    char array_arithmetic_34[16 + (0 ? 2 : 3)];
    char array_arithmetic_35[16 + (2, 3)];
    char array_arithmetic_36[16 + sizeof(s32)];
    char array_arithmetic_37[16 + sizeof(void*[4][4])];
    char array_arithmetic_38[16 + sizeof(struct SomeBitfield)];
    char array_arithmetic_39[16 + (int)1];
    char array_arithmetic_40[16 + (unsigned char)0x101];
    char array_arithmetic_41[16 + _Alignof(s32[4])];
    char char_array[2];
    int int_array[2];
    struct {
        int a;
        struct {
            int c;
        } b[3];
    } sub_array[2];
    int multidim_array[2][3];
    char end;
};

extern struct SubStruct extern_inner_struct_field;

enum {
    YET_MORE_ENUM = MORE_ENUM
};

void func_decl(void) {
    globali = 0;
}

short test(struct SomeStruct *arg, unsigned char should, union SomeUnion union_arg, ...)
{
    // This comment should be stripped
    /* This comment should also be stripped */
    /**
     * Even multi-line comments.
     */
    union SomeUnion stack_union;
    stack_union.double_innerfield = union_arg.double_innerfield;

    if (should)
    {
        globalf = arg->float_field;
        globali = arg->int_field;
        arg->data_field.char_innerfield = should;
    }
    else
    {
        arg->pointer_field = (void *)0;
        arg->data_field.double_innerfield = 0.;
    }
    return (short)arg->int_field;
}
