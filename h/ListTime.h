#ifndef LISTTIME_H
#define LISTTIME_H
#define nullptr 0L
#include "System.h"
#include "PCB.H"
#include <iostream.h>
//class PCB;
#include "SCHEDULE.H"
extern int syncPrintf(const char* format,...);
struct _node_ {
    PCB* pNode;
    _node_* next;
    Time time;

    _node_(PCB* pcb_, _node_* next_ = nullptr,Time time1) : pNode(pcb_), next(next_), time(time1) {}
};

class ListTime {
private:
    _node_* head;
    _node_* tail;
    _node_* current;

public:
    ListTime() : head(nullptr), tail(nullptr), current(nullptr) {}
    ~ListTime() {
        while (head) {
            get();
        }
        head = nullptr;
        tail = nullptr;
        current = nullptr;
    }

void put(PCB* pcb_,Time time1) {

        _node_* node = new _node_(pcb_,0,time1);
        if (head == nullptr) {
            head = node;
        } else {
            tail->next = node;
        }
        tail = node;

}

PCB* ListTime::get() {

        PCB* ret = nullptr;
        if (head) {
            ret = head->pNode;
            _node_* old = head;
            head = head->next;
            if (head == nullptr) {
                tail = nullptr;
                current = nullptr;
            }
            delete old;
        }

    return ret;
}


void ListTime::remove(PCB* pcb_) {

        _node_* temp ;
        _node_* prev = nullptr;



        temp = head;
        while (temp && temp->pNode != pcb_) {
            prev = temp;
            temp = temp->next;
        }
        if (temp != nullptr) {

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

void ListTime::decTime(){
	System::lock();
_node_* old=nullptr;
_node_ * prev=nullptr;
_node_ * temp=head;
while (temp){
	if (temp->time!=-1){

	     if (--temp->time==0){
	    	 prev=temp;
	    	 temp=temp->next;
		prev->pNode->timedOut=1;
		prev->pNode->status=PCB::READY;
		Scheduler::put(prev->pNode);
		remove(prev->pNode);
		//temp=temp->next;
		}
	     else temp=temp->next;
	}
	else temp=temp->next;

	}

System::unlock();
}



//System::unlock();

void decAll(){
	_node_* n=head;
	while (n){
		n->time--;
	}
}

_node_* getTail(){
	return tail;
}
_node_* getHead(){
	return head;
}

void ListTime::removeBlocked(){
if (head!=0 ){
	_node_* cur=head;
	_node_* old=0;
	while (cur){
		cur->pNode->status=PCB::READY;
		Scheduler::put(cur->pNode);
		old=cur;
		cur=cur->next;
		delete old;
	}
	head=tail=0;

}}
};
#endif
