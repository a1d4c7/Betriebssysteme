#ifndef Gate_h
#define Gate_h

#include "lib/Chain.h"

/*
 * Gate: Ein Trap/Interrupt Tor
 *
 *     	Alle Treiber, die Geraete mit Interrupts steuern
 *     	muessen fuer jeden Interrupt ein Gate-Objekt anlegen.
 *	Die Gate-Objekte tragen sich selber in die logische
 *	Interrupt-Tabelle ein.
 *	Sobald dies geschehen ist, werden alle an diesem Gate
 *	auftretenden Interrupts ueber die handle()-Methode
 *	dem Treiber mitgeteilt.
 *
 *	Achtung: Gates muessen definiert sein,
 *	*bevor* der zugehoerige Interrupt zugelassen wird!!!!
 */
class Gate : public Chain {
public:
	// Definition eines Gates fuer Vektornummer "num"
	Gate (int num);

	//  Automatisches Abmelden des Gates
	virtual ~Gate ();


	/** 	Nur was sofort in der Interruptbehandlung gemacht werden
	 *	muss, darf im Prolog gemacht werden.
	 */
	virtual bool prologue() = 0;

	/** Nicht jeder Interrupthandler muss einen Epilog haben.
	 */
	virtual void epilogue(){}

	int getNumber()
	{
		return num;
	}

	bool isDeferred()
	{
		return deferred;
	}

	void setDeferred(bool value)
	{
		deferred = value;
	}

private:
	int num;
	bool deferred;
};

#endif
