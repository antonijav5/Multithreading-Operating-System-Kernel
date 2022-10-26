/*
 * PCB.cpp
 *
 *  Created on: Sep 12, 2021
 *      Author: OS1
 */

#include "PCB.h"
#include "System.h"
#include <dos.h>
#include "Semaphor.h"
#include "Thread.h"
#include "List.h"
#include "IdleThr.h"
#include "MainThr.h"
#include "KernelEv.h"

const StackSize MAX_STACK_SIZE=65535;
const StackSize MIN_STACK_SIZE=1024;

static ID total=0;

List* PCB::created=new List();

void PCB::wrapper() {
	System::lock();
	PCB* temp;

	System::running->myThread->run();

System::running->status=PCB::FINISHED;

temp=System::running->blocked->get();
while (temp!=0)
{

temp->status=PCB::READY;
Scheduler::put(temp);
temp=System::running->blocked->get();

}
System::unlock();
dispatch();
}

void PCB::dispatch(){

#ifndef BCC_BLOCK_IGNORE
	asm cli
		System::explicitContextChange = 1;
		System::timer();

		asm sti
#endif
}
void PCB::setState(Status s) volatile{
	status=s;
}



void PCB::waitToComplete(){
	if (status==FINISHED || status==CREATED || status==IDLE	|| this==System::running ) {
		 return; }
	{ System::lock();

	System::running->setState(PCB::BLOCKED);

	blocked->put((PCB*)System::running);

	System::unlock();
	}
dispatch();

}



PCB::PCB( StackSize stackSize,Time timeSlice, Thread* myThread) {
this->timeSlice=timeSlice;
this->timedOut=0;

this->status=PCB::CREATED;
this->myThread=myThread;
this->id=++total;

this->blocked=new List();
flagChild=0;
numOfChildren = 0;
parent = 0;
forkID=0;
waitForChildren = new Semaphore(0);
ss=0;
sp=0;
bp=0;
stack=0;
if (myThread!=0){
//if (stackSize>MAX_STACK_SIZE) stackSize=MAX_STACK_SIZE;
//if (stackSize<MIN_STACK_SIZE) stackSize=MIN_STACK_SIZE;
stackSize/=sizeof(unsigned);
this->stackSize=stackSize;
stack=new unsigned [stackSize];
	stack[stackSize-1] = 0x200;
#ifndef BCC_BLOCK_IGNORE
	stack[stackSize-2] = FP_SEG(PCB::wrapper);
	stack[stackSize-3] = FP_OFF(PCB::wrapper);

	this->ss = FP_SEG(this->stack +stackSize-12);
	this->sp = FP_OFF(this->stack + stackSize-12);
	this->bp = this->sp;

#endif
}

	created->put(this);

}
extern Thread * child;
static unsigned tbp, tss,oldChildOffset,oldParentOffset,newChildOffset,newParentOffset;


void interrupt PCB::fork() {
	    delete[] child->myPCB->stack;
	    child->myPCB->stackSize = System::running->stackSize;
		child->myPCB->stack = new unsigned[System::running->stackSize];
		child->myPCB->timeSlice = System::running->timeSlice;
		child->myPCB->parent = ((PCB*)System::running)->myThread;
		child->myPCB->flagChild= 1;
        System::running->forkID=child->myPCB->id;
		System::running->numOfChildren++;
		memcpy(child->myPCB->stack, System::running->stack, System::running->stackSize * sizeof(unsigned));
#ifndef BCC_BLOCK_IGNORE
			asm {
				mov tbp, bp
				mov tss, ss
			}

			child->myPCB->ss = FP_SEG(child->myPCB->stack);
			oldParentOffset = FP_OFF(System::running->stack);
				oldChildOffset = FP_OFF(child->myPCB->stack);
#endif
				child->myPCB->bp = child->myPCB->sp = tbp - oldParentOffset + oldChildOffset;
				oldParentOffset = tbp;
				oldChildOffset = child->myPCB->bp;

				while (1) {
#ifndef BCC_BLOCK_IGNORE
					newParentOffset = *((unsigned *) MK_FP(tss, oldParentOffset));
					newChildOffset = *((unsigned *) MK_FP(child->myPCB->ss, oldChildOffset));
#endif
					if( newParentOffset == 0) {
						newChildOffset = 0;
						break;
					}

					newChildOffset = newParentOffset - oldParentOffset + oldChildOffset;
					oldParentOffset = newParentOffset;
					oldChildOffset = newChildOffset;
				}

				child->start();
}

void PCB::destroyEverything() {
	System::running->status = FINISHED;
	if (System::running->parent!=0) {
		System::running->parent->myPCB->waitForChildren->signal();
		}
	PCB* temp=System::running->blocked->get();

	while (temp!=0)
	{

	temp->status=PCB::READY;
	Scheduler::put(temp);
	temp=System::running->blocked->get();

	}
	dispatch();

}

PCB::~PCB() {


blocked->removeBlocked();



	if(stack) delete[] stack;
	delete blocked;

	blocked = 0;
	 }



