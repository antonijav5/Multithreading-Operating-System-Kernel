/*
 * IdleThr.h
 *
 *  Created on: Sep 15, 2021
 *      Author: OS1
 */

#ifndef IDLETHR_H_
#define IDLETHR_H_

#include "Thread.h";
#include "PCB.h";
class IdleThr:public Thread {

public:

	IdleThr();
~IdleThr();
void run();
};
#endif
