/*
 * IdleThr.cpp
 *
 *  Created on: Sep 15, 2021
 *      Author: OS1
 */

#include "IdleThr.h"
#include "PCB.h"
#include "System.h"


IdleThr::IdleThr(): Thread(defaultStackSize, 1) {}
IdleThr::~IdleThr(){}
void IdleThr::run() {

	while(1) {}

}

