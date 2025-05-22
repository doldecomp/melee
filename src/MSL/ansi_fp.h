#ifndef _ANSI_FP
#define _ANSI_FP

#define SIGDIGLEN 36

typedef struct decimal {
    char sign;
    char unk1;
    short exp;
    struct {
        unsigned char length;
        unsigned char text[36];
        unsigned char unk41;
    } sig;
} decimal;

typedef struct decform {
    char style;
    char unk1;
    short digits;
} decform;

void __num2dec(const decform* f, double x, decimal* d);

#endif
