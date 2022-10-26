#ifndef LISTSEM_H
#define LISTSEM_H
#define nullptr 0L
#include "System.h"
#include "PCB.H"
#include "Semaphor.h"
#include "KrnlSem.h"
#include <iostream.h>
#include "ListTime.h"
//class PCB;
#include "SCHEDULE.H"
extern int syncPrintf(const char* format,...);
struct node {
    KernelSem* sNode;
    node* next;

    node(KernelSem* s, node* next_ = nullptr) : sNode(s), next(next_) {}
};

class ListSem {
private:
    node* head;
    node* tail;
    node* current;

public:
    ListSem() : head(nullptr), tail(nullptr), current(nullptr) {}
    ~ListSem() {
        while (head) {
            remove();
        }
        head = nullptr;
        tail = nullptr;
        current = nullptr;
    }

void put(KernelSem* s) {

        node* node_ = new node(s);
        if (head == nullptr) {
            head = node_;
        } else {
            tail->next = node_;
        }
        tail = node_;

}

KernelSem* ListSem::get() {
   // LOCKED (
        KernelSem* ret = nullptr;
        if (head) {
            ret = head->sNode;
            node* old = head;
            head = head->next;
            if (head == nullptr) {
                tail = nullptr;
                current = nullptr;
            }

        }
   // )
    return ret;
}

KernelSem* ListSem::remove() {
   // LOCKED (
        KernelSem* ret = nullptr;
        if (head) {
            ret = head->sNode;
            node* old = head;
            head = head->next;
            if (head == nullptr) {
                tail = nullptr;
                current = nullptr;
            }
delete old;
        }
   // )
    return ret;
}


void ListSem::removeK(KernelSem* k) {
	 node* temp ;
	 node* prev = nullptr;



	        temp = head;
	        while (temp && temp->sNode != k) {
	            prev = temp;
	            temp = temp->next;
	        }
	        if (temp) {

	            if (temp == head) {
	                head = head->next;

	            } else if (temp == tail) {
	                prev->next = nullptr;
	                tail = prev;

	            } else {
	                prev->next = temp->next;

	            }
	            delete temp;
	        }
}


void ListSem::dec(){
	node* temp=head;
	KernelSem* sem;
	while (temp) {

	     ((ListTime*)temp->sNode->blockedLim)->decTime();

	            temp= temp->next;

	}

//	        }
	//syncPrintf("prvi put izasao\n");
//



}

/*
 void List::removeBlocked(){
if (head!=0 ){
	Node* cur=head;
	Node* old=0;
	while (cur){
		cur->pNode->status=PCB::READY;
		Scheduler::put(cur->pNode);
		old=cur;
		cur=cur->next;
		delete old;
	}
	head=tail=0;

}}*/
};


#endif
