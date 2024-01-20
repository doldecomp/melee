struct A;
struct A {
    char value;
    int array[5];
    float array_3d[2][3][4];
    int *pointer_array[2];
    struct A *self_pointer;
};

//void extern_fn(struct A *a);
//extern float extern_float;
//void static_fn(struct A *a) { }

static int static_int;
static struct A static_bss_A;
static struct A *static_A_ptr = &static_bss_A;
static struct A static_A = {
    1,
    {1, 2, 3, 4, 5},
    { { {1.0f, 2.0f, 3.0f, 4.0f},
        {5.0f, 6.0f, 7.0f, 8.0f},
        {9.0f, 0.0f, 1.0f, 2.0f} },
      { {1.5f, 2.5f, 3.5f, 4.5f},
        {5.5f, 6.5f, 7.5f, 8.5f},
        {9.5f, 0.5f, 1.5f, 2.5f} } },
    { (void *) 0, &static_int },
    &static_bss_A,
};

static int static_array[3] = {2, 4, 6};
static short unused_static_array[3] = {-8, 10, 12};
static char unused_static_string[4] = "abc";
static const int static_ro_array[] = {7, 8, -9};
static const unsigned int unused_static_ro_array[] = {10, -11, 12};
static int static_bss_array[3];

int test(void) {
    static_int *= 456;
    extern_float *= 456.0f;
    static_fn(&static_A);
    extern_fn(static_A_ptr);
    static_bss_array[0] = static_array[0] + static_ro_array[0];
    return static_int;
}
