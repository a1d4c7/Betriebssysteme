#include "system/Environment.h"
#include "user/Init.h"

CPU cpu;
Monitor monitor;
PIC pic;
PIT pit;
Clock clock(20000);
Keyboard keyboard;
CgaChannel screen;
Console console(keyboard,screen);
PrintStream out(console);
ActivityScheduler scheduler;

int main()
{
	out.println("main: starting appl...");

	Init init;

	out.println("main: marking kernel as free ...");

	// Kernel initial freigeben
	monitor.leave();

	// Interrupts an!
	out.println("main: enabling interrupts ...");
	cpu.enableInterrupts();

	// Wir starten hier die Applikation
	init.run();

	// Das System wird heruntergefahren...
	// ... Interrupts ausstellen
	cpu.disableInterrupts();

	// nun ist wirklich Schluss...
	out.println("main: system terminating...");

}
