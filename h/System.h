/*
 * System.h
 *
 *  Created on: Sep 12, 2021
 *      Author: OS1
 */

#ifndef SYSTEM_H_
#define SYSTEM_H_
//#include <dos.h>

#define nullptr 0L
typedef void interrupt  (*pInterrupt)(...);
class PCB;
class Thread;
class List;
class ListSem;
class Semaphore;
class System {
public:
	System();
	 ~System();
	friend class Thread;
	friend class PCB;
	friend class MainThr;
		friend class List;
		friend class Semaphore;
		//friend class ListSem;
		volatile static int waitToCompleteTest;
		volatile static int lck;
		volatile static int explicitContextChange;
		volatile static PCB* running;

		volatile static PCB* idleThr;
        volatile static int counter;
      static ListSem* listSem;
static void decSem();
static pInterrupt old;
		volatile static PCB* mainThr;


		static void inic();
			static void restore();
			static void lock();
			static void unlock();
static void interrupt timer();

};

#endif /* SYSTEM_H_ */
