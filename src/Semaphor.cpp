/*
 * Semaphore.cpp
 *
 *  Created on: Sep 17, 2021
 *      Author: OS1
 */

#include "Semaphor.h"
#include "KrnlSem.h"
#include "Thread.h"
#include "PCB.h"
#include "SCHEDULE.H"
#include "List.h"
#include <iostream.h>
#include "MainThr.h"

Semaphore::Semaphore(int init) {
	myImpl = new KernelSem(init,this);
}

Semaphore::~Semaphore() {
	//delete myImpl;
	if(myImpl != nullptr){
	            delete myImpl;
	            myImpl = nullptr;
	        }
}

int Semaphore::wait(Time maxTimeToWait) {
return myImpl->wait(maxTimeToWait);
}

void Semaphore::signal() {
	myImpl->signal();
}

int Semaphore::val() const {
	return myImpl->val;
}


