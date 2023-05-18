#include <platform.h>

#include <__init_cpp_exceptions.h>
#include <Gecko_ExceptionPPC.h>
#include <placeholder.h>

static int fragmentID = -2;

/**
 * @todo HACK: Should be @c _eti_init_info. We can't use the appropriate
 * name yet due to the linker not being able to generate it.
 */
SECTION_INIT extern __eti_init_info _eti_init_info_[];

#ifdef MWERKS_GEKKO

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

#ifdef MWERKS_GEKKO

void __init_cpp_exceptions(void)
{
    if (fragmentID == -2) {
        fragmentID = __register_fragment(_eti_init_info_, GetR2());
    }
}

#else

void __init_cpp_exceptions(void)
{
    NOT_IMPLEMENTED;
}

#endif
