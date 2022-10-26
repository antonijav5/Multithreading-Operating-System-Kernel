/*


* KernelSem.cpp
 *
 *  Created on: Sep 17, 2021
 *      Author: OS1
 */

#include "KrnlSem.h"
#include "ListSem.h"
#include "List.h"
#include "Semaphor.h"
#include "System.h"
#include "ListTime.h"
#include "PCB.h"

extern int syncPrintf(const char* format,...);

int KernelSem::wait(Time maxTimeToWait) {


	int ret=1;

	if (--val<0){
		System::lock();

			System::running->status=PCB::BLOCKED;
			if (maxTimeToWait!=0){


				((ListTime*)blockedLim)->put((PCB*)System::running,maxTimeToWait);
			}
			else {


				((ListTime*)blockedLim)->put((PCB*)System::running,((Time)-1));
			}
System::unlock();

		PCB::dispatch();
		if (System::running->timedOut==1 ) {
			System::running->timedOut=0;
			ret=0;
		}


	}

return ret;
}

void KernelSem::signal() {


	if (val++<0) {

		System::lock();
		PCB* t1=blockedLim->get();

			if (!t1 ) {

          System::unlock();
				return;
			}

	t1->status=PCB::READY;
	Scheduler::put(t1);
	System::unlock();


		}




}

KernelSem::KernelSem(int init, Semaphore* sem) {

	val=init;
	this->sem=sem;

	blockedLim=new ListTime();
	((ListSem*)System::listSem)->put(this);

}

KernelSem::~KernelSem() {

	((ListTime*)blockedLim)->removeBlocked();

	((ListSem*)System::listSem)->removeK(this);

}





