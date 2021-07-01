#ifndef Thread_h
#define Thread_h

#include "thread/Activity.h"
#include "sync/KernelLock.h"
#include "thread/ActivityScheduler.h"

/** 	Diese Klasse implementiert die Systemschnittstelle f�r leichtgewichtige
 *	Prozesse in Co-Stubs. Die run-Methode entspricht der main eines Threads.
 *
 *	Beachte, das Thread private von Activity erbt, in abgeleiteten Klassen
 *	kann also nicht direkt auf Methoden von Activity zugegriffen werden.
 *
 *	In abgeleiteten Klassen nicht vergessen den virtuellen Destruktor
 *	zu definieren, wenn eine Synchronisation aufs Ende erforderlich ist.
 *	Nutze dazu die Methoden join oder kill.
 *
 *	Da die Methoden hier sehr kurz sind, k�nnen sie alle inline implementiert
 *	werden.
 */
class Thread: private Activity {
public:
	Thread(int slice=1)
	{
		this->quantum(slice);
	}

	Thread(void* tos, int slice=1) : Activity(tos)
	{
		this->quantum(slice);
	}

	/** Die Implementierung der body-Methode geerbt von Coroutine.
	 */
	virtual void body()
	{
		this->run();
	}

	/** Die Methode f�r den Anwendungscode eines Threads.
	 */
	virtual void run()=0;

	/** Den gerade laufenden Thread ermitteln.
	 */
	static Thread* self()
	{
		return ((Thread*) scheduler.active());
	}

	/** Synchronisation auf das Ende eines Threads
	 */
	void join()
	{
		KernelLock lock;
		Activity::join();
	}

	/** Ein Thread wird explizit gestartet.
	 */
	void start()
	{
		KernelLock lock;
		Activity::wakeup();
	}

	/** Explizites beenden eines Threads.
	 */
	void exit()
	{
		KernelLock lock;
		Activity::exit();
	}

	/** Abgabe der CPU.
	 */
	void yield()
	{
		KernelLock lock;
		Activity::yield();
	}

};

#endif

