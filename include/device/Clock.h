#ifndef Clock_h
#define Clock_h

/*
 * Clock: Der Treiber fuer die Systemuhr
 *
 *
 * Alle "us" Mikrosekunden wird durch einen Interrupt
 * ein Ticken der Uhr ausgel"ost
 */

#include "interrupts/Gate.h"
#include "device/PIT.h"

class Clock: public Gate, public PIT {
public:

	/**	Initialisierung des "Ticks" der Uhr
	 *	Standardmaessig setzen wir das
	 *	Uhrenintervall auf 20 Millisekunden
	 *	und wir bekommen damit 50 Interrupts pro Sekunde
	 *
	 *	Zum Testen koennt Ihr bei Bedarf einen hoeheren Wert einstellen
	 *	Weitere Hinweise zur Implementierung siehe "windup"
	 */
	Clock (int us);


	/**	Spaetere Initialisierung...
	 *	Hier ist nur im Konstruktor dafuer zu sorgen,
	 *	dass sich Gate korrekt initialisieren kann
	 */
	Clock ();


	/**	Initialisierung des "Ticks" der Uhr
	 * 	Die Einheit sind Mikrosekunden.
	 * 	Hier ist der PIT geeignet zu initialisieren
	 * 	und der PIT beim PIC anzustellen.
	 */
	void windup(int us);

	/** 	Der Interrupt-Handler fuer die Uhr.
	 *	Hier ist der Interrupt am PIC zu bestaetigen
	 *	und die Systemzeit zu aktualisieren.
	 *	Die Systemzeit wird in Uhrenticks gemessen,
	 *	Ihr muesst hier also nur mitzaehlen,
	 *	wie oft die Uhr getickt hat.
	 *
	 *	Ueberpruefe zunaechst die Funktion des Timers
	 *	indem Du jede Sekunde eine Ausgabe an der Bildschirmstelle (0,0)
	 *	in Form eines rotierenden Propellers machst, der sich pro Sekunde
	 *	ein kleines Stueck weiterdreht, wie der Sekundenzeiger einer Uhr.
	 *	Der Propeller besteht aus der Zeichenfolge '/', '-', '\\', '|',
	 *	d.h. nach 4 Sekunden ist eine komplette Umdrehung geschafft.
	 *
	 *	Achtung: Kommentiert alle anderen Ausgaben Eures Testprogrammes
	 *	aus, sonst seht Ihr nichts!
	 *
	 *	Wenn der Uhrentest erfolgreich verlaufen ist, kommentiert
	 *	den Propeller wieder aus und ruft stattdessen
	 *	die "checkSlice" Methode des Schedulers auf,
	 *	um diesen ggf. zum praeemptiven Rescheduling zu veranlassen.
	 */
	bool prologue();
	void epilogue();

	/* 	Liefert die Systemzeit in Ticks zurueck
	 *	Kann hier "inline" implementiert werden
	 */
	int ticks()
	{
	}

private:
};

extern Clock clock;

#endif
