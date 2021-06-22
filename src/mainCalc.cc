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
#include "tools/Calc.h"

//////////////////////////////////////////////////////////////////////////
// Die Systemobjekte von Co-Stubs

CPU cpu;

InterruptGuardian interruptGuardian;
PIC pic;
Clock clock(2500);

Keyboard keyboard;

// Objekte der Prozessverwaltung
ActivityScheduler scheduler;   // der Scheduler

// globale Ein-/Ausgabeobjekte
CgaChannel cga;         // unser CGA-Ausgabekanal
PrintStream out(cga);   // unseren PrintStream mit Ausgabekanal verknuepfen

int main()
{
    Calculator calc;
    cpu.enableInterrupts();
    calc.body();
    scheduler.kill(&calc);
}
