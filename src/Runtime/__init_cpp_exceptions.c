#include <Runtime/Gecko_ExceptionPPC.h>

#include <placeholder.h>

static int fragmentID = -2;

#if defined(__MWERKS__) && defined(GEKKO)
__declspec(section ".init")
#endif
    /**
     * @todo HACK: Should be @c _eti_init_info. We can't use the appropriate
     * name yet due to the linker not being able to generate it.
     */
    extern __eti_init_info _eti_init_info_[];

#if defined(__MWERKS__) && defined(GEKKO)

static asm char* GetR2(void)
{ // clang-format off
    mr r3, r2
} // clang-format on

#endif

void __fini_cpp_exceptions(void)
{
    if (fragmentID != -2) {
        __unregister_fragment(fragmentID);
        fragmentID = -2;
    }
}

#if defined(__MWERKS__) && defined(GEKKO)

void __init_cpp_exceptions(void)
{
    if (fragmentID == -2)
        fragmentID = __register_fragment(_eti_init_info_, GetR2());
}

#else

void __init_cpp_exceptions(void)
{
    NOT_IMPLEMENTED;
}

#endif
