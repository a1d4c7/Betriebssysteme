#include "thread/ActivityScheduler.h"
#include "thread/Activity.h"
#include "interrupts/IntLock.h"
#include "device/Clock.h"
#include "sync/KernelLock.h"

#include "lib/Debugger.h"

    /* Suspendieren des aktiven Prozesses
	 * Der korrekte Ausfuehrungszustand ist zu setzen
	 * und danach der naechste lauffaehige Prozess zu aktivieren.
	 */
	void ActivityScheduler::suspend()
    {
        KernelLock lock;

        Activity* running = (Activity*) active();
        running->changeTo(Activity::BLOCKED);
        scheduler.reschedule();
    }

	/* Explizites Terminieren des angegebenen Prozesses
	 * Der Prozesszustand ist korrekt zu setzen
	 * und der Prozess aus der Ready-Liste des Schedulers
	 * zu entfernen. Falls der aktive Prozess zerstoert wird,
	 * ist dem naechsten lauffaehigen Prozess die CPU
	 * zuzuteilen.
	 */
	void ActivityScheduler::kill(Activity* a)
    {
        KernelLock lock;
        
        a->changeTo(Activity::ZOMBIE);

        Activity* running = (Activity*) active();
        
 
        if (a == running)
        {
            scheduler.reschedule();
        } 
        else
        {
            scheduler.remove(a);
        }        

    }

	/* Terminieren des aktiven Prozesses,
	 * und Wechsel zum naechsten lauffaehigen Prozess
	 */
	void ActivityScheduler::exit()
    {
        //IntLock lock; //keine Statusaenderung, keine gemeinsame Daten

        Activity* running = (Activity*) active();

        this->kill(running);
    }


	/* Der aktive Prozess ist, sofern er sich nicht im Zustand
	 * Blocked oder Zombie befindet, wieder auf die Ready-Liste
	 * zu setzen. Danach ist "to" mittels dispatch die Kontrolle
	 * zu �bergeben.
	 */
	void ActivityScheduler::activate(Schedulable* to)
    {     
        //IntLock lock;

        Activity* run = (Activity*) active();
        if (!(run->isBlocked() || run->isZombie()))
        {
            if (run->isRunning()) run->changeTo(Activity::READY);
            
            if (to == 0)
            {
                to = run;
            }
            else 
            {
                scheduler.schedule(run);
            }
        }  

        //wenn to = 0 ist dann ist readyliste leer
        //falls readyliste leer ist, auf naechste activity warten
        if (to == 0)
        {
            isEmpty = true;

            while (isEmpty)
            {
                {
                    KernelLock lock;
                    CPU::enableInterrupts();
                    CPU::halt();
                }
                
                //interrupts wieder sperren da sie vorher ja aus waren durch reschedule
                //und um dequeue zu schuetzen
                to = (Schedulable*) readylist.dequeue();

                if (to != 0) 
                {
                    isEmpty = false;    
                }
            }
        }

        //falls activate durch checkslice -> reschedule aufgerufen dann doppelt zurueckgesetzt
        //aber wichtig wenn geyielded wird
        clock.resetTicks();

        ((Activity*) to)->changeTo(Activity::RUNNING);
        dispatch((Activity*) to);
    
    }


    /* Ueberprueft ob die Zeitscheibe des aktuell laufenden
	 * Prozesses abgelaufen ist. Wenn ja, soll ein 
	 * Rescheduling veranlast werden.
	 */
	void ActivityScheduler::checkSlice()
    {
        KernelLock lock;
        
        if (isEmpty) return;

        Activity* running = (Activity*) active();

        //running kann null sein da wir in activate den while loop interrupts zulassen
        //dadurch kann checkslice auf einen null pointer aufgerufen werden
        //sollte aber doch nicht der fall sein, da running nie auf einen null prozess gesetzt werden kann
        //der alte prozess steht immer noch in running obwohl er ja garnicht mehr wirklich running ist
        if (running != 0) 
        {
            if (clock.ticks() >= running->quantum())
            {
                clock.resetTicks();
                reschedule();
            }
        }
        else 
        {
            clock.resetTicks();
            reschedule();
        }
        

        
    } 