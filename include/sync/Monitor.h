#ifndef Monitor_h
#define Monitor_h

#include "lib/Queue.h"
#include "interrupts/Gate.h"

/** 	Die Monitorimplementierung für den Kern.
 *	Beachte das der Monitor synchron (Anwendung) als auch asynchron
 * 	(Interrupt) betreten werden kann.
 */
class Monitor {
public:
	/** 	Initial ist der Monitor gesperrt. Erst nach der Initialisierung des Systems
	 *	darf er freigeschaltet werden.
	 */
	Monitor()
	{
		free = false;
	}

	/** 	Die Methode zum betreten, sperren des Monitors, aus der Anwendung heraus.
	 */
	void enter() { free = false; }

	/** 	Wenn der Monitor verlassen wird, müssen alle ausstehenden Epiloge sofort
	 *	abgearbeitet werden.
	 */
	void leave();

	bool isFree()
	{
		return free;
	}

	/** 	Diese Methode wird während der Interruptbehandlung aufgerufen, wenn ein
	 *	Epilog abgearbeitet werden muss. Ist der Monitor besetzt muss der Epilog
	 *	in die Warteschlange eingereiht werden, darf aber maximal einmal in der
	 *	Warteschlange sein.
	 */
	void runEpilogue(Gate *gate);

private:
	bool free;	// Monitor-Sperre
	Queue deferred; // Liste der vermerkten Epiloge
};

extern Monitor monitor;

#endif
