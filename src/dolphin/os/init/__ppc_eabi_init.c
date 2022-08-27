#include <dolphin/os/init/__ppc_eabi_init.h>

typedef void (*voidfunc)(void);

extern voidfunc __ctors[];

static void __init_cpp(void);

extern void PPCHalt(void);

void __init_user(void)
{
    __init_cpp();
}

#pragma push
#pragma peephole off
static void __init_cpp(void)
{
    voidfunc* constructor;

    for (constructor = __ctors; *constructor; constructor++) {
        (*constructor)();
    }
}
#pragma pop

void _ExitProcess(void)
{
    PPCHalt();
}
