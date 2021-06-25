#include "sync/KernelSemaphore.h"
#include "thread/Activity.h"
#include "thread/ActivityScheduler.h"


void KernelSemaphore::wait()
{
    //TODO locks
    if (counter > 0) //es sind signale im haus
    {
        counter -= 1; //Signal wegnehmen
    }
    else //wenn keine signale da sind dann schlafen
    {
        Activity* running = (Activity*) scheduler.active();
        waiting.enqueue(running);
        running->sleep();
    }
    
}

void KernelSemaphore::signal()
{
    //TODO locks
    Activity* next = (Activity*) waiting.dequeue();

    if (next == 0) //warten gerade auf niemanden
    {
        counter += 1;
    }
    else //nächsten prozess aufwecken
    {
        next->wakeup();
    }
    
}