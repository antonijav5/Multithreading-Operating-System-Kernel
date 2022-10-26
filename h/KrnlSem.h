/*
 * KernelSem.h
 *
 *  Created on: Sep 17, 2021
 *      Author: OS1
 */

#ifndef KERNELSEM_H_
#define KERNELSEM_H_
#include "Semaphor.h"
class Semaphore;
class KernelSem {
public:
friend class Semaphore;
friend class List;
friend class ListTime;
Semaphore *sem;
int val;

//List* blockedSem;
ListTime * blockedLim;
int wait(Time maxTimeToWait);
void signal();
KernelSem(int init, Semaphore *sem1);
 ~KernelSem();
void block(Time timeToWait);
void unblock();
};

#endif /* KERNELSEM_H_ */
