#include "__mem.h"

void* memset(void* dst, int val, unsigned long /*size_t*/ n)
{
	__fill_mem(dst, val, n);
	
	return(dst);
}

void __fill_mem(void * dst, int val, unsigned long n)
{
	unsigned long			v = (unsigned char) val;
	unsigned long			i;
	
	((unsigned char *) dst) = ((unsigned char *) dst) - 1;
	
	if (n >= 32)
	{
		i = (~ (unsigned long) dst) & 3;

		if (i) {
			n -= i;
			
			do {
				*++(((unsigned char *) dst)) = v;
			} while (--i);
		}
	
		if (v)
			v |= v << 24 | v << 16 | v <<  8;
		
		((unsigned long *) dst) = ((unsigned long *) (((unsigned char *) dst) + 1)) - 1;
		
		i = n >> 5;
		
		if (i) {
			do {
				*++((unsigned long *) dst) = v;
				*++((unsigned long *) dst) = v;
				*++((unsigned long *) dst) = v;
				*++((unsigned long *) dst) = v;
				*++((unsigned long *) dst) = v;
				*++((unsigned long *) dst) = v;
				*++((unsigned long *) dst) = v;
				*++((unsigned long *) dst) = v;
			} while (--i);
		}
		
		i = (n & 31) >> 2;
		
		if (i) {
			do {
				*++((unsigned long *) dst) = v;
			} while (--i);
		}
		
		((unsigned char *) dst) = ((unsigned char *) (((unsigned long *) dst) + 1)) - 1;
		
		n &= 3;
	}
	
	if (n)
		do {
			*++((unsigned char *) dst) = v;
		} while (--n);
	
	return;
}
