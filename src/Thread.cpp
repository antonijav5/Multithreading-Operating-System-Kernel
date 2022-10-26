/*
 * Thread.cpp
 *
 *  Created on: Sep 12, 2021
 *      Author: OS1
 */

#include "Thread.h"
#include "PCB.h"
#include "SCHEDULE.H"
#include "List.h"
#include <iostream.h>
#include "MainThr.h"
#include "Semaphor.h"
void Thread::start() {


		if (this->myPCB->status!=PCB::IDLE) {

			Scheduler::put(this->myPCB);


	this->myPCB->status=PCB::READY;
		}

}

void Thread::waitToComplete() {
	myPCB->waitToComplete();


}

Thread::~Thread() {
waitToComplete();
		delete myPCB;
		myPCB = 0;
}
PCB* Thread:: getPCB(){ return this->myPCB;}
ID Thread::getId() {
	return this->myPCB->id;
}

ID Thread::getRunningId() {
	return System::running->id;
}

Thread* Thread::getThreadById(ID idT) {
	return PCB::created->search(idT)->myThread;

}

Thread::Thread(StackSize stackSize, Time timeSlice) {

	myPCB=new PCB(stackSize,timeSlice,this);


}

Thread * child = 0;

ID Thread::fork() {
	System::lock();
ID ret;
if (System::running->flagChild==1)
	System::running->flagChild=0;
	child=0;
		child=System::running->myThread->clone();
	if (!child ) {System::unlock(); return -1;}
	PCB::fork();
	if (System::running->flagChild==1) ret=0;
	else ret=System::running->forkID;
	System::unlock();
	return ret;
}

void Thread::exit() {
	if (System::running->status != PCB::FINISHED) {
		PCB::destroyEverything();

	}
}

void Thread::waitForForkChildren() {

	while (System::running->numOfChildren > 0) {
			System::running->waitForChildren->wait(0);
		System::running->numOfChildren--;
	}

}

Thread* Thread::clone() const {
	return new Thread();
}
