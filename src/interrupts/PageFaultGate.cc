#include "interrupts/PageFaultGate.h"
#include "interrupts/InterruptVector.h"
#include "io/PrintStream.h"
#include "device/CgaChannel.h"
#include "device/CPU.h"
extern CPU cpu;
extern PrintStream out;
extern CgaChannel cga;

PageFaultGate::PageFaultGate(): Gate(PageFault) { }

void PageFaultGate::handle()
{
	cga.blueScreen("Panic! PageFault at address: ");
    out.print(CPU::getCR2());
	cpu.halt();
}
