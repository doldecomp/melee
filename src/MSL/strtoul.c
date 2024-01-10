#include <MSL/ctype.h>
#include <MSL/errno.h>
#include <MSL/limits.h>
#include <MSL/scanf.h>
#include <MSL/string.h>
#include <MSL/strtoul.h>

enum scan_states {
    start = 0x01,
    check_for_zero = 0x02,
    leading_zero = 0x04,
    need_digit = 0x08,
    digit_loop = 0x10,
    finished = 0x20,
    failure = 0x40
};

#define final_state(scan_state) (scan_state & (finished | failure))
#define success(scan_state)                                                   \
    (scan_state & (leading_zero | digit_loop | finished))
#define fetch() (count++, (*ReadProc)(ReadProcArg, 0, __GetAChar))
#define unfetch(c) (*ReadProc)(ReadProcArg, c, __UngetAChar)

unsigned long strtoul(const char* str, char** end, int base)
{
    unsigned long value;
    int count, negative, overflow;

    __InStrCtrl isc;
    isc.NextChar = (char*) str;
    isc.NullCharDetected = 0;

    value = __strtoul(base, 0x7FFFFFFF, &__StringRead, (void*) &isc, &count,
                      &negative, &overflow);

    if (end) {
        *end = (char*) str + count;
    }

    if (overflow) {
        value = ULONG_MAX;
        errno = 0x22;
    } else if (negative) {
        value = -value;
    }

    return value;
}
