/*
 * IVTEntry.h
 *
 *  Created on: Sep 18, 2021
 *      Author: OS1
 */

#ifndef IVTENTRY_H_
#define IVTENTRY_H_
#include "KernelEv.h"
#include "System.h"
typedef void interrupt (*pInterrupt)(...);
typedef unsigned char IVTNo;


class IVTEntry {
public:
	IVTEntry(IVTNo ivtNo,pInterrupt intr);
	 ~IVTEntry();

	friend class Event;
	friend class Semaphore;
	friend class KernelEv;

	KernelEv* myKernelEv;
	IVTNo ivtNo;
	pInterrupt old;
void callOld();
	void signal();

	 static IVTEntry* entries[256];

};

#endif /* IVTENTRY_H_ */
