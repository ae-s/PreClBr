/* PreClBr
 * Copyright 2010 Duncan Smith
 *
 * This file is licensed under the GNU GPL.  No warranty is provided.
 */

#include <tigcclib.h>

#define TSR_NAME "PreClBr "

#define OPTIMIZE_ROM_CALLS

#define USE_TI89

void Install_TSR(void);
void EventHandler(EVENT *ev);


/* EV_hook header
 */
asm(".ascii \"evHk" TSR_NAME "\"");
asm(".globl	gpOldHandler");
asm("gpOldHandler:");
asm(".long	0");
asm("__jmp__Event_Hook__:");
asm("jmp	Install_TSR:l");

#ifndef NO_CALC_DETECT
asm(".global__calculator");
asm("__calculator:");
asm(".word	0");
#endif

extern EVENT_HANDLER gpOldHandler;

/* Install function, run once
 */
void Install_TSR(void)
{
	extern char __jmp__Event_Hook__;
	char *ptr = &__jmp__Event_Hook__;

	*(unsigned long *)&ptr[2] = (unsigned long)event_handler;

#ifndef NO_CALC_DETECT
		asm volatile("
		/* Start Of Calculator Detection Code -- From TIGCC Sources */
				move.l 0xC8,%%a0
				/* Calculator Detection */
				moveq #1,%%d0
				move.l %%a0,%%d1
				and.l #0x400000,%%d1
				jbne __calc_in_d0__
				clr.w %%d0
				move.l (%%a0,0x2F*4),%%a1 /* ScrRect */
				cmp.b #200,2(%%a1)
				jbcs __calc_in_d0__
				moveq #3,%%d0
			__calc_in_d0__:
				lea __calculator(%%pc),%%a1
				move.w %%d0,(%%a1)
		/* End Of Calculator Detection Code -- From TIGCC Sources */"
		:
		:
		: "a0", "a1", "d1");
#endif

		return;
}

void event_handler(EVENT *ev)
{


void _main(char **argc, int *argv)
{
	
}



