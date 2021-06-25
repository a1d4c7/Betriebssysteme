#include "system/Console.h"




	Console::Console(InputChannel& input, OutputChannel& output) : input(input), output(output)
    {   
        sync = Semaphore(1); //semaphore ist direkt frei gegeben
    }

	/** 	Konsole reservieren
	 */
	void Console::attach()
    { 
        sync.wait(); //semaphore besetzen
    }

	/** 	Konsole wieder freigeben
	 */
	void Console::detach()
    {  
        sync.signal(); //semaphore freigeben
    }

	/** 	Daten auf der Console ausgeben
	 */
	int Console::write(const char* data, int size)
    {  
        return output.write(data,size);        
    }

	/** 	Jedes von der Tastatur eingelesene Zeichen
	 * 	soll auf dem Bildschirm dargestellt werden (Echo Funktion!)
	 * 	Wenn ein '\n' erkannt wurde oder bereits "size" Zeichen
	 *	gelesen wurden, ist eine Zeile zuende und read() kehrt zurueck.
	 *	Alle gelesenen Ascii-zeichen sind in den Puffer einzutragen
	 *	und zaehlen als gueltiges Zeichen!
	 */
	int Console::read(char* data, int size)
    {  
        return input.read(data, size);
    }

	/** 	Liefert das n�chste Zeichen aus dem Eingabepuffer zur�ck.
	 */
	char Console::read()
    {  
        char c;
        input.read(&c, 1);
        return c;
    }


