#ifndef Gate_h
#define Gate_h


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
class Gate {
public:
	// Definition eines Gates fuer Vektornummer "num"
	explicit Gate (int num);

	//  Automatisches Abmelden des Gates
	virtual ~Gate ();

	virtual void handle() = 0;



	int getNumber()
	{
		return num;
	}



    // alle Klassen mit virtuellen Destruktoren brauchen die
    // folgende Operator-Ueberladung:
    static void operator delete(void* p) {}

private:
	int num;
};

#endif
