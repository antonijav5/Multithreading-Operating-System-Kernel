#ifndef LIST_H
#define LIST_H
#define nullptr 0L
#include "System.h"
#include "PCB.H"
#include <iostream.h>
//class PCB;
#include "SCHEDULE.H"
struct Node {
    PCB* pNode;
    Node* next;

    Node(PCB* pcb_, Node* next_ = nullptr) : pNode(pcb_), next(next_) {}
};

class List {
private:
    Node* head;
    Node* tail;
    Node* current;

public:
    List() : head(nullptr), tail(nullptr), current(nullptr) {}
    ~List() {
        while (head) {
            get();
        }
        head = nullptr;
        tail = nullptr;
        current = nullptr;
    }

void put(PCB* pcb_) {
 //lock();
        Node* node = new Node(pcb_);
        if (head == nullptr) {
            head = node;
        } else {
            tail->next = node;
        }
        tail = node;
  //System::unlock();
}

PCB* List::get() {
   // LOCKED (
        PCB* ret = nullptr;
        if (head) {
            ret = head->pNode;
            Node* old = head;
            head = head->next;
            if (head == nullptr) {
                tail = nullptr;
                current = nullptr;
            }
          //  tail=
            delete old;
        }
   // )
    return ret;
}

PCB* List::search (ID num){
	for (Node* cur=head; cur;cur=cur->next ){
		if (cur->pNode->id==num) return cur->pNode;
	}
	return 0;
}
void List::remove(PCB* pcb_) {

        Node* temp ;
        Node* prev = nullptr;



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

}}
};


#endif
