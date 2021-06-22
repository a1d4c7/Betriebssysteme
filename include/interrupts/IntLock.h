#ifndef IntLock_h
#define IntLock_h

/*
 * IntLock: 	Diese Klasse dient dazu,
 *		innerhalb eines Blockes die Interrupts zu sperren
 *		und bei Verlassen des Blockes den alten Interruptstatus
 *		automatisch wiederherzustellen.
 */

#include "device/CPU.h"

class IntLock {
public:
	// Sperren!
	IntLock() { lock(); }

	// Restaurieren
	~IntLock() { restore(); }

	// Sperren!
	void lock() { previousState = CPU::disableInterrupts(); }

	// Restaurieren
	void restore() {
		if(previousState){
			CPU::enableInterrupts();
		}
	}

private:
	unsigned previousState;
};

#endif
