#ifndef Scheduler_h
#define Scheduler_h

/*
 * Scheduler: 	Diese Klasse implementiert die Zuteilungsstrategie
 *		fuer die CPU.
 *
 *	Anmerkung: Hier wird ein einfacher First-Come-First-Served
 *	Algorithmus implementiert, der sich auf eine
 *	ready-liste stuetzt, in dem alle lauffaehigen Prozesse
 *	miteinander verkettet sind.
 */

#include "lib/Queue.h"
#include "thread/Schedulable.h"

class Scheduler {
public:

	// Einfuegen eines neuen Elements in die Ready-Liste.
	void schedule(Schedulable* sched);

	// Entfernen eines Elements von der Ready-Liste.
	void remove(Schedulable* sched);

	// Aktiviert das vorderste der Liste mittels activate.
	void reschedule();


protected:
	/* Diese pur-virtuelle Methode stellt die Schnittstelle zum
	 * ActivityScheduler dar, der diese Klasse erweitert. Siehe
	 * die Beschreibung dort.
	 */
	virtual void activate(Schedulable* to) = 0;

	// Die Ready-Liste
	Queue readylist;

};

#endif
