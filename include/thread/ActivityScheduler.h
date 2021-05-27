#ifndef ActivityScheduler_h
#define ActivityScheduler_h

/*
 * ActivityScheduler: 	Diese Klasse implementiert die Zustandsverwaltung
 * 			f�r Activities
 *
 */

#include "lib/Queue.h"
#include "thread/Activity.h"
#include "thread/Dispatcher.h"
#include "thread/Scheduler.h"

class ActivityScheduler: public Dispatcher, public Scheduler {
public:
	ActivityScheduler()
	{
	}

	/* Initialisieren der ersten Aktivit�t, des Schedulers
	 * und des Dispatchers.
	 * Wird nur einmal aufgerufen.
	 */
	void start(Activity* act)
	{
		//TODO eventuell
		init(act);
	}

	/* Suspendieren des aktiven Prozesses
	 * Der korrekte Ausfuehrungszustand ist zu setzen
	 * und danach der naechste lauffaehige Prozess zu aktivieren.
	 */
	void suspend();

	/* Explizites Terminieren des angegebenen Prozesses
	 * Der Prozesszustand ist korrekt zu setzen
	 * und der Prozess aus der Ready-Liste des Schedulers
	 * zu entfernen. Falls der aktive Prozess zerstoert wird,
	 * ist dem naechsten lauffaehigen Prozess die CPU
	 * zuzuteilen.
	 */
	void kill(Activity*);

	/* Terminieren des aktiven Prozesses,
	 * und Wechsel zum naechsten lauffaehigen Prozess
	 */
	void exit();

protected:
	/* Der aktive Prozess ist, sofern er sich nicht im Zustand
	 * Blocked oder Zombie befindet, wieder auf die Ready-Liste
	 * zu setzen. Danach ist "to" mittels dispatch die Kontrolle
	 * zu �bergeben.
	 */
	virtual void activate(Schedulable* to);

private:

};

extern ActivityScheduler scheduler;

#endif
