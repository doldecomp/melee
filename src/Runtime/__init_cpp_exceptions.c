#include <placeholder.h>
#include <platform.h>

#include <__init_cpp_exceptions.h>
#include <Gecko_ExceptionPPC.h>

static int fragmentID = -2;

SECTION_INIT extern __eti_init_info _eti_init_info[];

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

void __init_cpp_exceptions(void)
{
#ifdef MWERKS_GEKKO
    if (fragmentID == -2) {
        fragmentID = __register_fragment(_eti_init_info, GetR2());
    }
#else
    NOT_IMPLEMENTED;
#endif
}

SECTION_CTORS void* const __init_cpp_exceptions_reference =
    __init_cpp_exceptions;
SECTION_DTORS void* const __destroy_global_chain_reference =
    __destroy_global_chain;
SECTION_DTORS void* const __fini_cpp_exceptions_reference =
    __fini_cpp_exceptions;
