/*
 * KernelEv.cpp
 *
 *  Created on: Sep 18, 2021
 *      Author: OS1
 */

#include "KernelEv.h"
#include "Event.h"
#include "IVTEntry.h"
#include "SCHEDULE.h"
KernelEv::KernelEv(IVTNo ivtNo) {
	System::lock();
	this->val=0;
	this->entry=ivtNo;
	this->myThread=(PCB*)System::running;
	this->blocked=0;
	IVTEntry::entries[ivtNo]->myKernelEv=this;
System::unlock();
}

KernelEv::~KernelEv() {

	if (blocked) {
		blocked->status=PCB::READY;
		Scheduler::put(blocked);
	}

myThread=0;

blocked=0;

IVTEntry::entries[entry]->myKernelEv=0;


}

void KernelEv::wait() {

	if (myThread==System::running){
		System::lock();
		if (val==0){
			val=1;
			blocked=myThread;
			myThread->status=PCB::BLOCKED;
			System::unlock();
			PCB::dispatch();
		}
		else {
			System::unlock();
		}
	}
	else {
		return;
	}

}

void KernelEv::signal() {
	System::lock();
	if (val==1)
	 { val=0;
		myThread->status=PCB::READY;
		Scheduler::put(myThread);
        blocked=0;
        System::unlock();
	}

	else {
		System::unlock();
		}


}
