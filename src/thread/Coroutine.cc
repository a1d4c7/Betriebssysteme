#include "thread/Coroutine.h"
#include "lib/Debugger.h"
#include "device/CPU.h"

    struct SetupFrame {
        unsigned edi; // nichtfl. Register
        unsigned esi; // nichtfl. Register
        unsigned ebx; // nichtfl. Register
        void* bp; // Register fuer lokale basis
        
        void (*coroutine) (Coroutine*); // Startadresse der Corout.
        
        void* nirwana; // simulierte Ruecksprungadresse
        
        //Parameter arg; // Parameter an funktion/coroutine
        Coroutine* arg;
    };


    /* Diese Funktion hat nur die Aufgabe
	 * den Rumpf der uebergebenen Coroutine aufzurufen
	 * und nach der Rueckkehr exit() aufzurufen,
	 * um die Termination des Rumpfes bekanntzugeben.
	 * Diese Prozedur dient so als eine Bruecke zwischen der
	 * nicht objektorientierten und der objektorientierten Welt
	 * Beachte, das "startup" als "static deklariert ist
	 * und deshalb keinen impliziten "this"-Zeiger uebergeben bekommt.
	 */
	void Coroutine::startup(Coroutine* obj)
    {
        CPU::enableInterrupts();
        
        obj->body();
        //debuggi.fehler("call exit");
        obj->exit();

    }

	/* Aufsetzen einer neuen Coroutine.
	 * Der Parameter "tos" (top of stack) ist der
	 * initiale Stackpointerwert fuer die neue Coroutine
	 * ACHTUNG: tos kann NULL sein (siehe Constructor)!
	 */
	void Coroutine::setup(void* tos)
    {
        SetupFrame frame;
        frame.edi = 0;
        frame.esi = 0;
        frame.ebx = 0;
        frame.bp  = 0;

        frame.coroutine = startup;  //wichtig

        frame.nirwana = 0;

        frame.arg = this;           //wichtig
        
        /*  Stack aufbau:
        -niedrig

        edi                     - tos - 24
        esi                     - tos - 20
        ebx                     - tos - 16
        ebp/bp                  - tos - 12
        coroutine/startup/init  - tos - 8
        nirwana/ret             - tos - 4
        arg/param               - tos - 0

        -hoch
        */

        int i = 0;

        if (tos == 0) //ist eine mglk fuer den fehler / esp von main
        {
            __asm("movl %%esp, %%eax;" : "=a" (tos));
        }
        
        
        
        //arg tos - 0
        int* el = (int*) (tos - 4 * i);
        *el = (int) frame.arg;     
        i += 1;

        //nirwana tos - 4
        el = (int*) (tos - 4 * i);
        *el = (int) frame.nirwana;
        i += 1;

        //startup tos - 8
        el = (int*) (tos - 4 * i);
        *el = (int) frame.coroutine;
        i += 1;

        //ebp tos - 12
        el = (int*) (tos - 4 * i);
        *el = (int) frame.bp;
        i += 1;

        //ebx tos - 16
        el = (int*) (tos - 4 * i);
        *el = (int) frame.ebx;
        i += 1;

        //esi tos - 20
        el = (int*) (tos - 4 * i);
        *el = (int) frame.esi;
        i += 1;

        //edi tos - 24
        el = (int*) (tos - 4 * i);
        *el = (int) frame.edi;
    
        //"retten" des stackpointers
        this->sp = (tos - 4 * i);
    }