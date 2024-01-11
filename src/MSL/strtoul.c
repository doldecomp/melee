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

unsigned long __strtoul(int base, int max_width,
                        int (*ReadProc)(void*, int, int), void* ReadProcArg,
                        int* chars_scanned, int* negative, int* overflow)
{
    int scan_state = start;
    int count = 0;
    unsigned long value = 0;
    unsigned long value_max = 0;
    int c;

    *negative = *overflow = 0;

    if (base < 0 || base == 1 || base > 36 || max_width < 1) {
        scan_state = failure;
    } else {
        c = fetch();
    }

    if (base != 0) {
        value_max = ULONG_MAX / base;
    }

    while (count <= max_width && c != -1 && !final_state(scan_state)) {
        switch (scan_state) {
        case start:
            if (isspace(c)) {
                c = fetch();
                break;
            }

            if (c == '+') {
                c = fetch();
            } else if (c == '-') {
                c = fetch();
                *negative = 1;
            }

            scan_state = check_for_zero;
            break;

        case check_for_zero:
            if (base == 0 || base == 16) {
                if (c == '0') {
                    scan_state = leading_zero;
                    c = fetch();
                    break;
                }
            }

            scan_state = need_digit;
            break;

        case 4:
            if (c == 'X' || c == 'x') {
                base = 16;
                scan_state = need_digit;
                c = fetch();
                break;
            }

            if (base == 0) {
                base = 8;
            }

            scan_state = digit_loop;
            break;

        case need_digit:
        case digit_loop:
            if (base == 0) {
                base = 10;
            }

            if (!value_max) {
                value_max = ULONG_MAX / base;
            }

            if (isdigit(c)) {
                if ((c -= '0') >= base) {
                    if (scan_state == digit_loop) {
                        scan_state = finished;
                    } else {
                        scan_state = failure;
                    }

                    c += '0';
                    break;
                }
            } else if (!isalpha(c) || (toupper(c) - 'A' + 10) >= base) {
                if (scan_state == digit_loop) {
                    scan_state = finished;
                } else {
                    scan_state = failure;
                }

                break;
            } else {
                c = toupper(c) - 'A' + 10;
            }

            if (value > value_max) {
                *overflow = 1;
            }

            value *= base;

            if ((unsigned long) c > (ULONG_MAX - value)) {
                *overflow = 1;
            }

            value += c;
            scan_state = digit_loop;
            c = fetch();
            break;
        }
    }

    if (!success(scan_state)) {
        count = value = 0;
    } else {
        --count;
    }

    *chars_scanned = count;
    unfetch(c);
    return value;
}
