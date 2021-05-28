#include "device/PIT.h"

    /** Default-Konstruktor. Das Interval wird spaeter
	  * mit der interval-Methode initialisiert */
	PIT::PIT () : ctrl(CONTROL_PORT), data(DATA_PORT)
    {

    }

	/** Initialisiert den Timers, sodass alle "us" Mikrosekunden ein Interrupt
	  * ausgeloest wird */
	PIT::PIT (int us) : ctrl(CONTROL_PORT), data(DATA_PORT)
    {
		interval(us);
    }

	/** Setzt das Timer-Intervall, sodass alle "us" Mikrosekunden ein Interrupt
	  * ausgeloest wird.
	  * 
	  * BEACHTE: Hier muss die Hardware korrekt programmiert werden.
	  * Naeheres steht in der Web-Dokumentation.
	  */
	void PIT::interval (int us)
    {
		//Steuerreg
		// 00 - zaehler | 11 - low -> high bits | 010 - modus 2 | 0 - binaere zaehlung
		// 00 11 010 0

		//zaehlerreg
		// us & 0xff dann (us >> 8) & 0xff

		char c =                      0b00110100; 	//ctrl wort
		char l =  (us * TIME_BASE)        & 0xff;	//niedrige 8 bit
		char h = ((us * TIME_BASE) >> 8)  & 0xff; 	//hohe     8 bit
		
		ctrl.write(c);
		data.write(l);
		data.write(h);
    }