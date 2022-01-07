#define EOF -1
#pragma ANSI_strict off

static int lbl_804D5B58 = 80808080L; // = K1
static int lbl_804D5B5C = 0xfefefeffL; // = K2

typedef struct
{
    const char * NextChar;
    int    NullCharDetected;
} __InStrCtrl;

enum __ReadProcActions
{
	__GetAChar,
	__UngetAChar,
	__TestForError
};

//func_803257E8
int __StringRead(void * isc, int ch, int Action) {
    char RetVal;

    __InStrCtrl * Iscp = (__InStrCtrl*)isc;
    switch (Action) {
        case __GetAChar:
            RetVal = *(Iscp->NextChar);
            if (RetVal == '\0') {
                Iscp->NullCharDetected = 1;
                return EOF;
            } else {
                Iscp->NextChar++;
                return (int)RetVal;
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

//func_80325878
char* strchr(char *str, int chr) {
    const unsigned char *p = (unsigned char*) str - 1;
    unsigned long int c = ((unsigned long int)chr & 0xffu);
    unsigned long int ch;
    while ((ch = *++p)) {
        if (ch == c) {
            return ((char *) p);
        }
    }
    return c ? 0 : (char *) p;
}

//strcmp
int strcmp(const char * str1, const char * str2)
{
    /*
        *	strcmp routine designed to minimized the number of
        *	loads and stores.  We make sure that all the loads and
        *  stores are properly aligned.
        *
        */
    register unsigned char *left = (unsigned char *)str1;
    register unsigned char *right = (unsigned char *)str2;
    unsigned int k1, k2, align, l1, r1, x;
    int result;

    /*	Check the simple case of the first byte being different. */
    l1 = *left;
    r1 = *right;
    result = (int)l1 - (int)r1;
    if (result) {
        return result;
    }

    /*
        *	If either the destination or the source are not
        *	aligned on the same boundary, we do a byte copy.
        *	Otherwise we align them to a word boundary.
        */
    if ((align = ((unsigned int)left & 3u)) != ((unsigned int)right & 3u)) {
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
            result = (int)l1 - (int)r1;
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

    k1 = lbl_804D5B58;
    k2 = lbl_804D5B5C;

    /*	Load a word from each string. */
    l1 = *(unsigned int*)left;
    r1 = *(unsigned int*)right;
    /*	See comments in strcpy function. */
    x = l1 + k2;
    x &= ~l1;
    if (x & k1) {
        goto adjust;
    }
    while(l1 == r1) {
        /*	Load a word and increment strings. */
        left += sizeof(unsigned int);
        l1 = *((unsigned int*)left);
        right += sizeof(unsigned int);
        r1 = *((unsigned int*)right);
        x = l1 + k2;
        if (x & k1) {
            goto adjust;
        }
    }

adjust:
    // Deleting the next two lines may be semantically equivalent and it produces closer asm.
    l1 = *left;
    r1 = *right;
    result = (int)l1 - (int)r1;
    if (result > 0) {
        return 1;
    } else if (result < 0) {
        return -1;
    }
bytecopy:
    if (l1 == 0u) {
        return (0);
    }
    for(;;) {
        l1 = *(++left);
        r1 = *(++right);
        result = (int)l1 - (int)r1;
        if (result) {
            return result;
        }
        if (l1 == 0u) {
            return (0);
        }
    }
}

//func_803258A8
int strncmp(const char * str1, const char * str2, unsigned long n)
{
    const	unsigned char * p1 = (unsigned char *) str1 - 1;
    const	unsigned char * p2 = (unsigned char *) str2 - 1;
            unsigned long		c1, c2;

    n++;
    while (--n) {
        if ((c1 = *++p1) != (c2 = *++p2)) {
            return ((int)c1 - (int)c2);
        } else { if (!c1) {
            break;
        }}
    }
	return(0);
}

//func_80325A0C
char * strncpy(char * __restrict dst, const char * __restrict src, unsigned long n)
{
	const	unsigned char * p		= (const unsigned char *) src - 1;
		unsigned char * q		= (unsigned char *) dst - 1;

		n++;
		while (--n) {
			if (!(*++q = *++p)) {
				while (--n) {
					*++q = 0u;
				}
				break;
			}
		}
	return(dst);
}

//func_80325B04
unsigned long (strlen)(const char* s) {
    unsigned long k = -1;
    unsigned char * p = (unsigned char *) s - 1;
    do { k++; } while (*++p);

    return k;
}