#include "thread/Activity.h"
#include "thread/Coroutine.h"
#include "thread/Schedulable.h"
#include "thread/ActivityScheduler.h"
#include "interrupts/IntLock.h"
#include "sync/KernelLock.h"



    /* Aufsetzen eines Threads, der initiale Zustand ist "Blocked",
	 * da der Thread erst laufen darf, wenn der spezielle Konstruktor
	 * der abgeleiteten Klasse abgearbeitet ist. Die Aktivierung
	 * erfolgt von der abgeleiteten Klasse mittels "wakeup".
	*/
	Activity::Activity(void* tos): Coroutine(tos), s(BLOCKED), joined(0)
    {
		
    }

	/* Verpacken des aktuellen Kontrollflusses als Thread.
	 * Wird nur f�r den Hauptkontrollfluss "main" ben�tigt.
	 * Es wird hier kein Stack initialisiert.
	 * Beachte das Activity wegen der Vererbungsbeziehung von
	 * Coroutine abstrakt ist. Bei Bedarf muss "body" direkt
	 * aufgerufen werden.
	 */
	Activity::Activity() : Coroutine(), s(BLOCKED), joined(0)
    {
		this->s = RUNNING;
	    scheduler.start(this);
    }


	/* Im Destruktor muss ein explizites Terminieren dieser Aktivitaet erfolgen.
	 * Das muss geschehen, da aufgrund der Aufrufreihenfolge von
	 * Destruktoren bereits der abgeleitete Teil des Activity-Objekts zerstoert
	 * wurde und diese Aktivitaet daher keine Laufzeit mehr erhalten darf.
	 * Das Warten auf die Beendigung (mittels join()) muss im Destruktor der
	 * von Activity am weitesten abgeleiteten Klasse erfolgen.
	 */
	Activity::~Activity()
    {
		//IntLock lock;
        scheduler.kill(this);
    }

	/* Veranlasst den Scheduler, diese Aktivitaet zu suspendieren.
	 */
	void Activity::sleep()
    {
		//KernelLock lock; //Statusaenderung sichern um inkonsistenz zu vermeiden

		//falls die activity nicht laeuft muss nur der status geaendert werden
		if (!this->isRunning()) 
		{
			this->changeTo(BLOCKED);
			scheduler.remove(this);
		}
		else
		{
			scheduler.suspend();	
		}
		
		
    }

	/* Veranlasst den Scheduler, diese Aktivitaet aufzuwecken.
	 */
	void Activity::wakeup()
    {
		//KernelLock lock; //Statusaenderung sichern um inkonsistenz zu vermeiden

		//um zu verhindern das auf nicht wartenden activities wakeup aufgerufen wird
		if (this->isBlocked())
		{
			this->changeTo(READY);
			scheduler.schedule(this);
		}
    }

	/* Diese Aktivitaet gibt die CPU vorruebergehend ab.
	 */
	void Activity::yield()
    {
		//KernelLock lock; //Statusaenderung sichern um inkonsistenz zu vermeiden

		this->changeTo(READY);
		
		scheduler.reschedule();
		
    }

	/* Diese Aktivitaet wird terminiert. Hier muss eine eventuell
	 * auf die Beendigung wartende Aktivit�t geweckt werden.
	 */
	void Activity::exit()
    {
		//IntLock lock;

		if (joined != 0)
		{
			joined->wakeup();
		}

		scheduler.exit();
		

    }

	/* Der aktuelle Prozess wird solange schlafen gelegt, bis der
	 * Prozess auf dem join aufgerufen wird beendet ist. Das
	 * Wecken des wartenden Prozesses �bernimmt exit.
	 */
	void Activity::join()
    {
		//IntLock lock;

		Activity* running = (Activity*) scheduler.active();
		joined = running;

		while (!isZombie())
		{
			running->sleep();
			
		}	
		
    }
