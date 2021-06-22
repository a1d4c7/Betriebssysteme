#include "interrupts/SpuriousGate.h"
#include "interrupts/InterruptVector.h"
#include "device/PIC.h"

SpuriousGate::SpuriousGate(): Gate(SpuriousInterrupt) { }

bool SpuriousGate::prologue()
{
	pic.ack();
	return false;
}
