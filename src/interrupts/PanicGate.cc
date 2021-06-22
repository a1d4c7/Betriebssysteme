#include "interrupts/PanicGate.h"
#include "device/CgaChannel.h"
#include "device/CPU.h"
extern CPU cpu;
extern CgaChannel screen;

PanicGate::PanicGate(): Gate(-1) { }

bool PanicGate::prologue()
{
 screen.blueScreen("Panic: Illegal Trap/Interrupt!");
	cpu.halt();
	return false;
}
