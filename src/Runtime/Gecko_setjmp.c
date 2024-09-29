#include <platform.h>
#include <placeholder.h>

#include <Gecko_setjmp.h>

#ifdef MWERKS_GEKKO
asm int __setjmp(register __jmp_buf* env)
{ // clang-format off
    nofralloc
    mflr	r5
    mfcr	r6
    stw		r5,env->pc		//	save PC (LR)
    stw		r6,env->cr		//	save CR
    stw		SP,env->sp		//	save SP
    stw		RTOC,env->rtoc	//	save #RTOC
    stmw	r13,env->gprs	//	save R13-R31
    mffs	fp0
    stfd	fp14,env->fp14	//	save FP14-FP31
    stfd	fp15,env->fp15
    stfd	fp16,env->fp16
    stfd	fp17,env->fp17
    stfd	fp18,env->fp18
    stfd	fp19,env->fp19
    stfd	fp20,env->fp20
    stfd	fp21,env->fp21
    stfd	fp22,env->fp22
    stfd	fp23,env->fp23
    stfd	fp24,env->fp24
    stfd	fp25,env->fp25
    stfd	fp26,env->fp26
    stfd	fp27,env->fp27
    stfd	fp28,env->fp28
    stfd	fp29,env->fp29
    stfd	fp30,env->fp30
    stfd	fp31,env->fp31
    stfd	fp0,env->fpscr	//	save FPSCR
    li		r3,0
    blr
} // clang-format on
#else
int __setjmp(register __jmp_buf* env)
{
    NOT_IMPLEMENTED;
}
#endif

#ifdef MWERKS_GEKKO
asm void longjmp(register __jmp_buf* env, register int val)
{ // clang-format off
    nofralloc
    lwz		r5,env->pc
    lwz		r6,env->cr
    mtlr	r5				//	restore PC (LR)
    mtcrf	255,r6			//	restore CR
    lwz		SP,env->sp		//	restore SP
    lwz		RTOC,env->rtoc	//	restore RTOC
    lmw		r13,env->gprs	//	restore R13-R31
    lfd		fp14,env->fp14	//	restore FP14-FP31
    lfd		fp15,env->fp15
    lfd		fp16,env->fp16
    lfd		fp17,env->fp17
    lfd		fp18,env->fp18
    lfd		fp19,env->fp19
    lfd		fp20,env->fp20
    lfd		fp21,env->fp21
    lfd		fp22,env->fp22
    lfd		fp23,env->fp23
    lfd		fp24,env->fp24
    lfd		fp25,env->fp25
    lfd		fp26,env->fp26
    lfd		fp27,env->fp27
    lfd		fp28,env->fp28
    lfd		fp29,env->fp29
    lfd		fp30,env->fp30
    lfd		fp0,env->fpscr
    lfd		fp31,env->fp31
    cmpwi	val,0
    mr		r3,val
    mtfsf	255,fp0			//	restore FPSCR
    bnelr					//	return 'val'
    li		r3,1			//	return 1
    blr
} // clang-format on
#else
void longjmp(register __jmp_buf* env, register int val)
{
    NOT_IMPLEMENTED;
}
#endif
