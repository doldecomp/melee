#include <Runtime/Gecko_ExceptionPPC.h>

static int fragmentID = -2;

__declspec(section ".init") extern __eti_init_info _eti_init_info_[];

static asm char* GetR2(void)
{ // clang-format off
    mr r3, r2
} // clang-format on

void __fini_cpp_exceptions(void)
{
    if (fragmentID != -2) {
        __unregister_fragment(fragmentID);
        fragmentID = -2;
    }
}

/**
 * @todo HACK: #_eti_init_info_ should be @c _eti_init_info, we can't use
 * the appropriate name yet due to the linker not being able to generate it
 */
void __init_cpp_exceptions(void)
{
    if (fragmentID == -2) {
        fragmentID = __register_fragment(_eti_init_info_, GetR2());
    }
}
