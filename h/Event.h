// File: event.h
#ifndef _event_h_
#define _event_h_

typedef unsigned char IVTNo;

#define PREPAREENTRY(numEntry,oldI)\
		void interrupt inter##numEntry(...);\
		IVTEntry newEntry##numEntry(numEntry,inter##numEntry);\
		void interrupt inter##numEntry(...){\
			newEntry##numEntry.signal();\
			if(oldI!=0)\
				newEntry##numEntry.callOld();\
		}

class KernelEv;
class Event {
public:
 Event (IVTNo ivtNo);
 ~Event ();
 void wait ();
protected:
 friend class KernelEv;
 void signal(); // can call KernelEv
private:
 KernelEv* myImpl;
};
#endif
