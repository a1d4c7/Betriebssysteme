#include "interrupts/PanicGate.h"
#include "device/CgaChannel.h"
#include "device/CPU.h"
extern CPU cpu;
extern CgaChannel cga;

PanicGate::PanicGate(): Gate(-1) { }

bool PanicGate::prologue()
{
 	cga.blueScreen("Panic: Illegal Trap/Interrupt!");
	cpu.halt();
	return false;
}
