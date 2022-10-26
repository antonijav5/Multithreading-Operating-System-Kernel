/*
 * Event.cpp
 *
 *  Created on: Sep 18, 2021
 *      Author: OS1
 */

#include "Event.h"
#include "KernelEv.h"


Event::Event(IVTNo ivtNo) {
myImpl=new KernelEv(ivtNo);
}

Event::~Event() {
delete myImpl;
myImpl=0;
}

void Event::wait() {
myImpl->wait();
}

void Event::signal() {
 myImpl->signal();
}
