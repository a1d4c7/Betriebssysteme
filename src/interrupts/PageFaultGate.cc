#include "interrupts/PageFaultGate.h"
#include "interrupts/InterruptVector.h"
#include "io/PrintStream.h"
#include "device/CgaChannel.h"
#include "device/CPU.h"
extern CPU cpu;
extern PrintStream out;
extern CgaChannel screen;

PageFaultGate::PageFaultGate(): Gate(PageFault) { }

bool PageFaultGate::prologue()
{
	screen.blueScreen("Panic! PageFault at address: ");
    out.print(CPU::getCR2());
	cpu.halt();
	return false;
}
