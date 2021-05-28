    #include "device/Clock.h"
    #include "interrupts/InterruptVector.h"
	#include "device/PIC.h"
	#include "thread/ActivityScheduler.h"


	#include "io/PrintStream.h" //propeller test
	extern PrintStream out; 

    /**	Spaetere Initialisierung...
	 *	Hier ist nur im Konstruktor dafuer zu sorgen,
	 *	dass sich Gate korrekt initialisieren kann
	 */
	Clock::Clock () : Gate(Timer), PIT(), tickCount(0)
    {
    }

	/**	Initialisierung des "Ticks" der Uhr
	 *	Standardmaessig setzen wir das
	 *	Uhrenintervall auf 20 Millisekunden
	 *	und wir bekommen damit 50 Interrupts pro Sekunde
	 *
	 *	Zum Testen koennt Ihr bei Bedarf einen hoeheren Wert einstellen
	 *	Weitere Hinweise zur Implementierung siehe "windup"
	 */
	Clock::Clock (int us) : Gate(Timer), PIT(), tickCount(0)
    {
		windup(us);
    }

	/**	Initialisierung des "Ticks" der Uhr
	 * 	Die Einheit sind Mikrosekunden.
	 * 	Hier ist der PIT geeignet zu initialisieren
	 * 	und der PIT beim PIC anzustellen.
	 */
	void Clock::windup(int us)
    {
		interval(us);

		pic.enable(PIC::PIT);
    }

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
	void Clock::handle()
    {
		pic.ack();
		tickCount += 1;

		scheduler.reschedule(); //noch zu testen

		//scheduler.checkSlice(); //noch zu testen


		//testfaelle

		//if (tickCount % 40 == 0) out.print("#"); //ein zeichen pro sekunde ausgeben

		/* //propeller
		if (tickCount % 40 == 0) 
		{
			switch (tickCount % 160)
			{
				case 0 * 40: out.print("\r/"); break;
				case 1 * 40: out.print("\r-"); break;
				case 2 * 40: out.print("\r\\"); break;
				case 3 * 40: out.print("\r|"); break;	
				default:
					break;
			}
		}
		// */

    }