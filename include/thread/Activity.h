#ifndef Activity_h
#define Activity_h

/*
 * Activity:
 * Diese Klasse implementiert kooperative aktive Objekte
 * fuer Co-Stubs.
 *
 * Anmerkung:
 * Im Gegensatz zur Coroutine wird eine
 * Instanz der Klasse Activity von einem Scheduler verwaltet.
 * Ein explizites Umschalten zu einer anderen Coroutine
 * wird damit hinfaellig.
 */

#include "thread/Schedulable.h"
#include "thread/Coroutine.h"
#include "lib/Queue.h"

class Activity: public Schedulable, public Coroutine {
public:
	/* Die logischen Ausfuehrungszustaende
	 * fuer diese Aktivitaet
	 */
	enum State {
		BLOCKED,	//Prozesse die auf etwas warten
		READY,     	//Prozesse die aktiviert werden k�nnen
		RUNNING,	//Status des aktiven Prozesses
		ZOMBIE,		//Kindprozesse die vor den Eltern beendet werden
		WAITING		//Elternprozesse die vor den Kindern beendet werden
	};

	/* Aufsetzen eines Threads, der initiale Zustand ist "Blocked",
	 * da der Thread erst laufen darf, wenn der spezielle Konstruktor
	 * der abgeleiteten Klasse abgearbeitet ist. Die Aktivierung
	 * erfolgt von der abgeleiteten Klasse mittels "wakeup".
	*/
	Activity(void* tos);

	/* Verpacken des aktuellen Kontrollflusses als Thread.
	 * Wird nur f�r den Hauptkontrollfluss "main" ben�tigt.
	 * Es wird hier kein Stack initialisiert.
	 * Beachte das Activity wegen der Vererbungsbeziehung von
	 * Coroutine abstrakt ist. Bei Bedarf muss "body" direkt
	 * aufgerufen werden.
	 */
	Activity();

	/* Im Destruktor muss ein explizites Terminieren dieser Aktivitaet erfolgen.
	 * Das muss geschehen, da aufgrund der Aufrufreihenfolge von
	 * Destruktoren bereits der abgeleitete Teil des Activity-Objekts zerstoert
	 * wurde und diese Aktivitaet daher keine Laufzeit mehr erhalten darf.
	 * Das Warten auf die Beendigung (mittels join()) muss im Destruktor der
	 * von Activity am weitesten abgeleiteten Klasse erfolgen.
	 */
	~Activity();

	/* Veranlasst den Scheduler, diese Aktivitaet zu suspendieren.
	 */
	void sleep();

	/* Veranlasst den Scheduler, diese Aktivitaet aufzuwecken.
	 */
	void wakeup();

	/* Diese Aktivitaet gibt die CPU vorruebergehend ab.
	 */
	void yield();

	/* Diese Aktivitaet wird terminiert. Hier muss eine eventuell
	 * auf die Beendigung wartende Aktivit�t geweckt werden.
	 */
	void exit();

	/* Der aktuelle Prozess wird solange schlafen gelegt, bis der
	 * Prozess auf dem join aufgerufen wird beendet ist. Das
	 * Wecken des wartenden Prozesses �bernimmt exit.
	 */
	void join();


	// Folgende Methoden d�rfen "inline" implementiert werden

	/* �ndern des Ausf�hrungszustandes. Diese Methode sollte nur vom
	 * Scheduler verwendet werden.
	 */
	void changeTo(State state)
	{
		s = state;
	}

	// Ausf�hrungszustand abfragen.
	bool isBlocked()
	{
		if (s == BLOCKED)
		{
			return true;
		}

		return false;
	}

	bool isReady()
	{
		if (s == READY)
		{
			return true;
		}

		return false;
	}

	bool isRunning()
	{
		if (s == RUNNING)
		{
			return true;
		}

		return false;
	}

	bool isZombie()
	{
		if (s == ZOMBIE)
		{
			return true;
		}

		return false;
	}

	State getState()
	{
		return s;
	}

	Activity* getJoined()
	{
		return joined;
	}

	void setJoined(Activity* a)
	{
		joined = a;
	}

	Queue* getSecondary()
	{
		return &secondary;
	}




private:
	State s;			//state einer activity
	Activity* joined;	//activity die wieder geweckt werden muss
	Queue secondary;	//activities die noch laufen, auf die evtl gewartet werden muss
};

#endif
