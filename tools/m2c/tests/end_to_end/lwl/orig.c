
struct A {
    char pad;
    struct {
        char ar[4];
    } data;
} a1, a2, a3[1];

void foo(void* x) {}

char* strcpy(char* dst, const char* src);
#pragma intrinsic (strcpy)

char buf[100];

void test(void) {
    // The last 3 bytes are loaded using lwr, then stored using swr
    char str[7] = "abcdef";
    foo(str);
    // 4 bytes being loaded using lwl+lwr, then stored using swl/swr
    a1.data = a2.data;
    // 5 bytes being loaded using lwl+lwr+lbu, then stored using sw+sb
    a3[0] = a1;
    // 4 bytes being loaded using lwl+lwr, then stored using sw
    strcpy(buf, "ghi");
}
