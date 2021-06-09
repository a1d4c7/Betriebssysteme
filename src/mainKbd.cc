// Testprogramm fuer kooperative Threads

#include "device/CgaChannel.h"
#include "device/CPU.h"
#include "io/PrintStream.h"
#include "thread/Activity.h"
#include "thread/ActivityScheduler.h"
#include "device/PIC.h"
#include "device/Clock.h"
#include "interrupts/InterruptGuardian.h"
#include "interrupts/IntLock.h"
#include "device/Keyboard.h"

// Hello: Eine kooperative Aktivitaet
//
// Anmerkung: Diese Klasse dient
// zu Testzwecken und der Einfacheit halber sind
// alle Methoden dieser Klasse ausnahmsweise inline deklariert
// Das sollte normalerweise *nicht* der Fall sein!
class Echo: public Activity {
public:
	explicit Echo(PrintStream& out)
		: cout(out)
	{
	}

	explicit Echo(PrintStream& out, void* sp)
		: Activity(sp), cout(out)
	{
		wakeup();
	}

	void body()
	{
		char c;
		Key key;
		do{
			key = keyboard.read();
				c = key.getValue();
				cout.print(c);
		}while(c!='x');
	}

private:
	PrintStream& cout;
};

//////////////////////////////////////////////////////////////////////////
// Die Systemobjekte von Co-Stubs

CPU cpu;

InterruptGuardian interruptGuardian;
PIC pic;
Clock clock(2500);

Keyboard keyboard;

// globale Ein-/Ausgabeobjekte
CgaChannel cga;         // unser CGA-Ausgabekanal
PrintStream out(cga);   // unseren PrintStream mit Ausgabekanal verknuepfen

// Objekte der Prozessverwaltung
ActivityScheduler scheduler;   // der Scheduler

int main()
{
	Echo echo(out);

	cpu.enableInterrupts();
	echo.body();
}
