#ifndef RUNTIME_GECKO_SETJMP_H
#define RUNTIME_GECKO_SETJMP_H

#include <platform.h>

typedef struct __jmp_buf {
    unsigned long pc;       /*	0: saved PC			*/
    unsigned long cr;       /*	4: saved CR			*/
    unsigned long sp;       /*  8: saved SP			*/
    unsigned long rtoc;     /* 12: saved RTOC		*/
    unsigned long reserved; /* 16: not used			*/
    unsigned long gprs[19]; /* 20: saved R13-R31	*/
    double fp14;            /* 96: saved FP14-FP31	 */
    double fp15;
    double fp16;
    double fp17;
    double fp18;
    double fp19;
    double fp20;
    double fp21;
    double fp22;
    double fp23;
    double fp24;
    double fp25;
    double fp26;
    double fp27;
    double fp28;
    double fp29;
    double fp30;
    double fp31;
    double fpscr; /* 240: saved FPSCR		*/
} __jmp_buf;

int __setjmp(register __jmp_buf*);
void longjmp(register __jmp_buf* env, register int val);

#endif
