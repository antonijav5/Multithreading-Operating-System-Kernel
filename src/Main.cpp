/*
 * Main.cpp
 *
 *  Created on: Sep 15, 2021
 *      Author: OS1
 */

#include "Thread.h"
#include "PCB.h"
#include "System.h"
#include "List.h"
#include "MainThr.h"
#include "IdleThr.h"


int main(int argc, char* argv[]){

	PCB* mainPCB=new PCB(0,defaultTimeSlice,0);
	mainPCB->status=PCB::RUNNING;

	System::running=mainPCB;


	System::inic();
	MainThr* user = new MainThr(argc, argv);
	IdleThr* idle=new IdleThr();
	System::idleThr=idle->getPCB();
	System::idleThr->status=PCB::IDLE;




	user->start();

	user->waitToComplete();



	System::restore();


	return 0;
	}
