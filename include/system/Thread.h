#ifndef Thread_h
#define Thread_h

#include "thread/Activity.h"
#include "sync/KernelLock.h"
#include "thread/ActivityScheduler.h"

/** 	Diese Klasse implementiert die Systemschnittstelle für leichtgewichtige
 *	Prozesse in Co-Stubs. Die run-Methode entspricht der main eines Threads.
 *
 *	Beachte, das Thread private von Activity erbt, in abgeleiteten Klassen
 *	kann also nicht direkt auf Methoden von Activity zugegriffen werden.
 *
 *	In abgeleiteten Klassen nicht vergessen den virtuellen Destruktor
 *	zu definieren, wenn eine Synchronisation aufs Ende erforderlich ist.
 *	Nutze dazu die Methoden join oder kill.
 *
 *	Da die Methoden hier sehr kurz sind, können sie alle inline implementiert
 *	werden.
 */
class Thread: private Activity {
public:
	Thread(int slice=1)
	{
	}

	Thread(void* tos, int slice=1)
	{
	}

	/** Die Implementierung der body-Methode geerbt von Coroutine.
	 */
	virtual void body(){
	}

	/** Die Methode für den Anwendungscode eines Threads.
	 */
	virtual void run()=0;

	/** Den gerade laufenden Thread ermitteln.
	 */
	static Thread* self()
	{
	}

	/** Synchronisation auf das Ende eines Threads
	 */
	void join()
	{
	}

	/** Ein Thread wird explizit gestartet.
	 */
	void start()
	{
	}

	/** Explizites beenden eines Threads.
	 */
	void exit()
	{
	}

	/** Abgabe der CPU.
	 */
	void yield()
	{
	}

};

#endif

