/*
 * IVTEntry.cpp
 *
 *  Created on: Sep 18, 2021
 *      Author: OS1
 */
#include <iostream.h>
#include <dos.h>
#include "IVTEntry.h"
#include "KernelEv.h"
#include "Event.h"
 IVTEntry* IVTEntry::entries[256]={0};

IVTEntry::IVTEntry(IVTNo ivtNo, pInterrupt intr) {
this->ivtNo=ivtNo;
this->myKernelEv=0;
#ifndef BCC_BLOCK_IGNORE
this->old = getvect(ivtNo);
setvect(ivtNo,intr);
#endif
IVTEntry::entries[ivtNo]=this;


}

IVTEntry::~IVTEntry() {

callOld();
#ifndef BCC_BLOCK_IGNORE
	setvect(ivtNo,old);
#endif
	IVTEntry::entries[ivtNo]=0;
}

void IVTEntry::signal() {
if (myKernelEv!=0)	myKernelEv->signal();
}

void IVTEntry::callOld(){
	if (old != 0)(*old)();
}
