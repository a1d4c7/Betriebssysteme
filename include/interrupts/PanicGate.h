#ifndef PanicGate_h
#define PanicGate_h

#include "interrupts/Gate.h"

/*
 * 	PanicGate: Alle Eintrage in der Vektortabelle werden initial auf
 *		   dieses Gate gesetzt
 *
 *      Das PanicGate wird bei unbekannten Traps/Interrupts aktiviert,
 *      macht eine entsprechende Ausgabe und haelt die CPU an.
 */
class PanicGate: public Gate {
public:
	PanicGate();

	bool prologue();
};

#endif
