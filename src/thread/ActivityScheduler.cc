#include "thread/ActivityScheduler.h"
#include "thread/Activity.h"

#include "lib/Debugger.h"

    /* Suspendieren des aktiven Prozesses
	 * Der korrekte Ausfuehrungszustand ist zu setzen
	 * und danach der naechste lauffaehige Prozess zu aktivieren.
	 */
	void ActivityScheduler::suspend()
    {
        //debuggi.fehler(" AS:suspend ");
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
        //debuggi.fehler(" AS:kill ");
        //TODO eventuell
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
        //debuggi.fehler(" AS:exit ");
        //TODO eventuell
        //debuggi.fehler("exit von AS");

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
        //TODO
       
        //wenn to = 0 sind dann ist readyliste leer
        //falls readyliste leer ist, auf naechste activity warten
        if (to == 0)
        {
            bool empty = true;

            //debuggi.join = true;

            while (empty)
            {
                //if (debuggi.join) 
                //debuggi.line("empty queue loop");
                //if (debuggi.join) debuggi.join = false;


                to = (Schedulable*) readylist.dequeue();
                if (to != 0) empty = false;
            }
        }
             
        ((Activity*) to)->changeTo(Activity::RUNNING);
        dispatch((Activity*) to);
    
    } 