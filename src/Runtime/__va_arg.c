#include <placeholder.h>

#include <stdarg.h>

#ifdef __MWERKS__

#define ALIGN(addr, size) (((uintptr_t) (addr) + ((size) - 1)) & ~((size) - 1))

void* __va_arg(va_list v_list, unsigned char type)
{
    char* addr;
    char* reg = &v_list->gpr;
    int g_reg = v_list->gpr;
    int maxsize = 8;
    int size = 4;
    int increment = 1;
    int even = 0;
    int fpr_offset = 0;
    int regsize = 4;

    if (type == 4) {
        addr = (char*) ALIGN(v_list->input_arg_area, 16);
        v_list->input_arg_area = addr + 0x10;
        return addr;
    }
    if (type == 3) {
        reg = &v_list->fpr;
        g_reg = v_list->fpr;
        size = 8;
        fpr_offset = 32;
        regsize = 8;
    }
    if (type == 2) {
        size = 8;
        maxsize--;
        if (g_reg & 1) {
            even = 1;
        }
        increment = 2;
    }
    if (g_reg < maxsize) {
        g_reg += even;
        addr = v_list->reg_save_area + fpr_offset + (g_reg * regsize);
        *reg = g_reg + increment;
    } else {
        *reg = 8;
        addr = v_list->input_arg_area;
        addr = (char*) ALIGN(addr, size);
        v_list->input_arg_area = addr + size;
    }
    if (type == 0) {
        addr = *((char**) addr);
    }

    return addr;
}

#else

void* __va_arg(va_list v_list, unsigned char type)
{
    NOT_IMPLEMENTED;
}

#endif
