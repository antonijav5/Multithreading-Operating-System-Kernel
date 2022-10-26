/*


 * System.cpp
 *
 *  Created on: Sep 12, 2021
 *      Author: OS1
 */

#include "System.h"
#include "SCHEDULE.H"
#include "PCB.h"
#include "Thread.h"
#include <dos.h>
#include "MainThr.h"
//#include "Semaphore.h"
#include "List.h"
#include "ListSem.h"
#include "ListTime.h"

extern int syncPrintf(const char *format, ...);
typedef void interrupt (*pInterrupt)(...);
volatile  unsigned tss;
volatile  unsigned tbp;
volatile  unsigned tsp;

 pInterrupt System::old=0;
System::System() {

}

System::~System() {
idleThr=0;
mainThr=0;
}

volatile PCB* System:: mainThr = 0;

volatile PCB* System:: running=0;

volatile PCB* System::idleThr = 0;
volatile int System::lck=0;

volatile int System::counter=0;
volatile int System::explicitContextChange=0;
 ListSem* System::listSem=new ListSem();

void System::inic(){
	lock();

#ifndef BCC_BLOCK_IGNORE
	old = getvect(0x8);
	setvect(0x8,(pInterrupt)System::timer);
	setvect(0x60,old);
#endif
	unlock();

}

void System::restore() {
	lock();
#ifndef BCC_BLOCK_IGNORE
	setvect(0x8,old);
#endif
unlock();

}

void System::lock() {
	++lck;

}

void System::unlock() {

	if (--lck==0 && explicitContextChange==1) PCB::dispatch();
}
extern void tick();
void interrupt System::timer(){

		if(explicitContextChange==0)

		{ System::decSem();

			counter--;



		}
			if (counter==0  || explicitContextChange)
			{



#ifndef BCC_BLOCK_IGNORE
					asm {
						mov tss, ss
						mov tsp, sp
						mov tbp, bp
					}
#endif

					running->ss = tss;
					running->sp = tsp;
					running->bp = tbp;
					if (running->status != PCB::BLOCKED && running->status!=PCB::FINISHED
					&& running!=idleThr)
					{
						Scheduler::put((PCB*)(running));
					running->status=PCB::READY;
					}



					running = Scheduler::get();

					if (running==0) {


					running = idleThr;}

					else {
						running->status=PCB::RUNNING;
					}
					tsp = running->sp;
					tss = running->ss;
					tbp = running->bp;


					counter = ((PCB*)running)->timeSlice;
#ifndef BCC_BLOCK_IGNORE
					asm{
						mov ss,tss
						mov sp, tsp
						mov bp, tbp

		}
#endif
			}

				if(explicitContextChange==0) {


                   tick();

#ifndef BCC_BLOCK_IGNORE
                   asm int 60h
#endif
				   }
				explicitContextChange=0;

}
void System::decSem(){

	((ListSem*)System::listSem)->dec();

}
