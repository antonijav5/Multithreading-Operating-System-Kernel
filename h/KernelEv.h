/*
 * KernelEv.h
 *
 *  Created on: Sep 18, 2021
 *      Author: OS1
 */

#ifndef KERNELEV_H_
#define KERNELEV_H_
#include "Event.h"
#include "PCB.h"
class Event;
class KernelEv {
public:
	friend class Event;
	KernelEv(IVTNo ivtNo);
	IVTNo entry;
	PCB* myThread;
	PCB* blocked;
	int val;
 ~KernelEv();
	void wait();
	void signal();
};

#endif /* KERNELEV_H_ */
