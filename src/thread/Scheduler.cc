#include "thread/Scheduler.h"
#include "lib/Debugger.h"

    // Einfuegen eines neuen Elements in die Ready-Liste.
	void Scheduler::schedule(Schedulable* sched)
    {
        readylist.enqueue(sched);
    }

	// Entfernen eines Elements von der Ready-Liste.
	void Scheduler::remove(Schedulable* sched)
    {
        readylist.remove(sched);
    }

	// Aktiviert das vorderste der Liste mittels activate.
	void Scheduler::reschedule()
    {
        Schedulable* sched = (Schedulable*) (readylist.dequeue());
        activate(sched);
        
    }