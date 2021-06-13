#ifndef UPNauswerter_h
#define UPNauswerter_h

#include "lib/Calculator/Op.h"
#include "lib/Queue.h"
#include "lib/Stack.h"

class UPNauswerter {
public:
    /**
	 * wertet einen UPN Ausdruck aus
	 * 
	 * @param upnListe der UPN Ausdruck der ausgewertet werden soll
	 */
	static void upnAuswerten() 
    {

	}

private:
	/**
	 * rechnet das Ergbnis von zwei Operanden und deren Operator aus
	 * 
	 * @param operand1 der erste Operand
	 * @param operand2 der zweite Operand
	 * @param operator der Operator
	 * @return gibt einen Operand zur�ck als Ergebnis
	 */
	static Op rechnen() 
    {
		
	}

	/**
	 * bringt die upnListe in die richtige Reihenfolge zum auswerten
	 * 
	 * @param upnListe die zu sortierende Liste
	 * @return gibt die sortierte Liste zurueck
	 */
	static void sortieren() 
    {
		
	}

    /**
     * turns string expression in Op-stack with the Shunting-Yard Algorithm 
     */
    static void shuntingYardAlg()
    {

    }
    
};

#endif
