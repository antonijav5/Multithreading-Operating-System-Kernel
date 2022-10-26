/*
 * PCB.h
 *
 *  Created on: Sep 12, 2021
 *      Author: OS1
 */

#ifndef PCB_H_
#define PCB_H_
#include "Thread.h"
class Thread;
class List;
class KernelSem;
class Semaphore;
class PCB {
public:

	friend class IdleThr;
	ID id;
	Thread* myThread;
	Time timeSlice;
	static List* created;

	List* blocked;
	typedef enum Status {IDLE,CREATED, READY, RUNNING,BLOCKED, FINISHED} Status;

	StackSize stackSize;
	unsigned* stack;
	unsigned ss;
	unsigned sp;
	unsigned bp;
Status status;
void setState(Status s) volatile;
	static void wrapper();
	void waitToComplete();
	int flagChild;
	     int numOfChildren;
	     int forkID;
		Thread *parent;
		Semaphore * waitForChildren;
static void destroyEverything();
		static void interrupt fork();
		PCB( StackSize stackSize1=defaultStackSize,Time timeSlice1=defaultTimeSlice,Thread* myThread1=0);
int timedOut;
static void dispatch();

 ~PCB();



};

#endif /* PCB_H_ */
