#include <MSL/string.h>
#define EOF -1

#ifdef __MWERKS__
#pragma push
#pragma ANSI_strict off
#endif

static unsigned int K1 = 0x80808080L; // = K1
static unsigned int K2 = 0xfefefeffL; // = K2

typedef struct {
    const char* NextChar;
    int NullCharDetected;
} __InStrCtrl;

enum __ReadProcActions {
    __GetAChar,
    __UngetAChar,
    __TestForError
};

unsigned long(strlen)(const char* s)
{
    unsigned long k = -1;
    unsigned char* p = (unsigned char*) s - 1;
    do {
        k++;
    } while (*++p);

    return k;
}

char* strcpy(char* dst, const char* src)
{
    /*
     *	strcpy routine designed to minimized the number of
     *	loads and stores.  We make sure that all the loads and
     *  stores are properly aligned.
     *
     */
    register unsigned char *destb, *fromb;
    register unsigned int w, t, align;
    register unsigned int k1;
    register unsigned int k2;

    fromb = (unsigned char*) src;
    destb = (unsigned char*) dst;

    /*
     *	If either the destination or the source are not
     *	aligned on the same boundary, we do a byte copy.
     *	Otherwise we align them to a word boundary.
     */
    if ((align = ((unsigned int) fromb & 3u)) != ((unsigned int) destb & 3u)) {
        goto bytecopy;
    }

    if (align) {
        if ((*destb = *fromb) == 0) {
            return (dst);
        }
        for (align = 3u - align; align; align--) {
            if ((*(++destb) = *(++fromb)) == 0) {
                return (dst);
            }
        }
        ++destb;
        ++fromb;
    }
    /*	Source and destination are word aligned */

    k1 = K1;
    k2 = K2;

    /*	Load a word and test for a null byte. */
    w = *((unsigned int*) (fromb));
    /*
     *	Here we need to test if one of the bytes in w is 0, in
     *	which case we have reached the end of the string.  If we
     *	reach the end of the string we go to the one-byte-copy
     *	block.  This code is endian-neutral.
     *	The naive way would be to test each byte of the word, but
     *	that would require at least four comparisons, few shifts,
     *	and few branches.  This would be extremely costly especially
     *	on machines where the conditional branch destroys the cache.
     *
     *	Assertion:
     *	----------
     *	Let B be a byte.  The most significant bit of
     *	(B-1) & ~B will be set, if and only if B==0.
     *
     *	Proof:
     *	------
     * 		B			| 	00	| 01..7F|	80	| 81..FF|
     * 		B-1			|	FF	| 00..7E|	7F	| 80..FE|
     * 		~B			|	FF	| FE..80|	7F	| 7E..00|
     *	MSB((B-1)&~B)	|	1	| 0		|	0	| 0		|
     *
     *	Adding 0xFF to a byte will always generate a carry
     *	except when the byte is 0.  So when working with 4
     *	bytes at a time, we will add FF to the first byte and
     *	FE to the other bytes because the carry will come
     *	from the preceding byte.
     */
    t = w + k2;
    /*
     *	Extract the most significant bit of each byte.  If one
     *	bit is left it means we have seen a 0.
     */
    t &= k1;
    if (t) {
        goto bytecopy;
    }

    destb -= sizeof(int);

    for (;;) {
        /*	Put the tested word into the incremented destination. */
        destb += sizeof(int);
        *((unsigned int*) (destb)) = w;

        /*	Load a word and increment source for testing. */
        fromb += sizeof(int);
        w = *((unsigned int*) (fromb));

        t = w + k2;
        t & w;
        t &= k1;
        if (t) {
            goto adjust;
        }
    }

adjust:
    destb += sizeof(int);
bytecopy:
    if ((*destb = *fromb) == 0) {
        return (dst);
    }
    for (;;) {
        if ((*(++destb) = *(++fromb)) == 0) {
            return (dst);
        }
    }
}

char* strncpy(char* dst, const char* src, unsigned long n)
{
    const unsigned char* p = (const unsigned char*) src - 1;
    unsigned char* q = (unsigned char*) dst - 1;

    n++;
    while (--n) {
        if (!(*++q = *++p)) {
            while (--n) {
                *++q = 0u;
            }
            break;
        }
    }
    return (dst);
}

int strcmp(const char* str1, const char* str2)
{
    /*
     *	strcmp routine designed to minimized the number of
     *	loads and stores.  We make sure that all the loads and
     *  stores are properly aligned.
     *
     */
    register unsigned char* left = (unsigned char*) str1;
    register unsigned char* right = (unsigned char*) str2;
    unsigned int k1, k2, align, l1, r1, x;
    int result;

    /*	Check the simple case of the first byte being different. */
    l1 = *left;
    r1 = *right;
    result = (int) l1 - (int) r1;
    if (result) {
        return l1 - r1;
    }

    /*
     *	If either the destination or the source are not
     *	aligned on the same boundary, we do a byte copy.
     *	Otherwise we align them to a word boundary.
     */
    if ((align = ((unsigned int) left & 3u)) != ((unsigned int) right & 3u)) {
        goto bytecopy;
    }
    if (align) {
        /*	Continuation of test of first byte. */
        if (l1 == 0u) {
            return (0);
        }
        for (align = 3u - align; align; align--) {
            l1 = *(++left);
            r1 = *(++right);
            result = (int) l1 - (int) r1;
            if (result) {
                return result;
            }
            if (l1 == 0u) {
                return (0);
            }
        }
        left++;
        right++;
    }

    /*	Strings are word aligned */

    k1 = K1;
    k2 = K2;

    /*	Load a word from each string. */
    l1 = *(unsigned int*) left;
    r1 = *(unsigned int*) right;
    /*	See comments in strcpy function. */
    x = l1 + k2;
    if (x & k1) {
        goto adjust;
    }
    while (l1 == r1) {
        /*	Load a word and increment strings. */
        left += sizeof(unsigned int);
        l1 = *((unsigned int*) left);
        right += sizeof(unsigned int);
        r1 = *((unsigned int*) right);
        x = l1 + k2;
        if (x & k1) {
            goto adjust;
        }
    }

    if (l1 > r1) {
        return 1;
    } else {
        return -1;
    }

adjust:
    l1 = *left;
    r1 = *right;
    result = (int) l1 - (int) r1;
    if (result) {
        return (int) l1 - (int) r1;
    }
bytecopy:
    if (l1 == 0u) {
        return (0);
    }
    for (;;) {
        r1 = *(++left);
        l1 = *(++right);
        result = (int) r1 - (int) l1;
        if (result) {
            return result;
        }
        if (r1 == 0u) {
            return (0);
        }
    }
}

int strncmp(const char* str1, const char* str2, unsigned long n)
{
    const unsigned char* p1 = (unsigned char*) str1 - 1;
    const unsigned char* p2 = (unsigned char*) str2 - 1;
    unsigned long c1, c2;

    n++;
    while (--n) {
        if ((c1 = *++p1) != (c2 = *++p2)) {
            return ((int) c1 - (int) c2);
        } else {
            if (!c1) {
                break;
            }
        }
    }
    return (0);
}

char* strchr(const char* str, int chr)
{
    const unsigned char* p = (unsigned char*) str - 1;
    unsigned long int c = ((unsigned long int) chr & 0xffu);
    unsigned long int ch;
    while ((ch = *++p)) {
        if (ch == c) {
            return ((char*) p);
        }
    }
    return c ? 0 : (char*) p;
}

int __StringRead(void* isc, int ch, int Action)
{
    char RetVal;

    __InStrCtrl* Iscp = (__InStrCtrl*) isc;
    switch (Action) {
    case __GetAChar:
        RetVal = *(Iscp->NextChar);
        if (RetVal == '\0') {
            Iscp->NullCharDetected = 1;
            return EOF;
        } else {
            Iscp->NextChar++;
            return (int) RetVal;
        }
    case __UngetAChar:
        if (!Iscp->NullCharDetected) {
            Iscp->NextChar--;
        } else {
            Iscp->NullCharDetected = 0;
        }
        return ch;
    case __TestForError:
        return Iscp->NullCharDetected;
    default:
        return 0;
    }
}

#ifdef __MWERKS__
#pragma pop
#endif
