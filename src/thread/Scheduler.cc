#include "thread/Scheduler.h"
#include "interrupts/IntLock.h"

    // Einfuegen eines neuen Elements in die Ready-Liste.
	void Scheduler::schedule(Schedulable* sched)
    {
        IntLock lock;

        readylist.enqueue(sched);
    }

	// Entfernen eines Elements von der Ready-Liste.
	void Scheduler::remove(Schedulable* sched)
    {
        IntLock lock;
        
        readylist.remove(sched);
    }

	// Aktiviert das vorderste der Liste mittels activate.
	void Scheduler::reschedule()
    {
        IntLock lock;
        
        Schedulable* sched = (Schedulable*) (readylist.dequeue());
        activate(sched);
        
    }