#include "device/PIT.h"

    /** Default-Konstruktor. Das Interval wird spaeter
	  * mit der interval-Methode initialisiert */
	PIT::PIT ()
    {

    }

	/** Initialisiert den Timers, sodass alle "us" Mikrosekunden ein Interrupt
	  * ausgeloest wird */
	PIT::PIT (int us)
    {

    }

	/** Setzt das Timer-Intervall, sodass alle "us" Mikrosekunden ein Interrupt
	  * ausgeloest wird.
	  * 
	  * BEACHTE: Hier muss die Hardware korrekt programmiert werden.
	  * Naeheres steht in der Web-Dokumentation.
	  */
	void PIT::interval (int us)
    {

    }