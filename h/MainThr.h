/*
 * MainThr.h
 *
 *  Created on: Sep 13, 2021
 *      Author: OS1
 */

#ifndef MAINTHR_H_
#define MAINTHR_H_
#include "Thread.h"
#include "PCB.h"
#include "System.h"
//class Thread;
 int userMain(int argc, char** argv);
extern int syncPrintf(const char *format, ...);
class MainThr:public Thread {
public:

	int argc,ret;
	char** argv;
	MainThr(int argc,char** argv):Thread(){
		this->argc=argc;
		this->argv=argv;
		ret=0;

	}
 ~MainThr(){

waitToComplete();

						//delete this->getPCB();
						//this->getPCB() = 0;

	}
protected:
	void run();

};

#endif /* MAINTHR_H_ */
