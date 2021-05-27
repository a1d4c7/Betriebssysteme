#ifndef OutputChannel_h
#define OutputChannel_h

/**
 * OutputChannel:
 * Diese Klasse ist die Abstraktion eines Ausgabekanals.
 *
 * Beachte, dass die 'write'- Methode
 * eine so genannte pure virtuelle Methode ist,
 * fuer die hier keine Implementierung
 * angegeben wird. Daher ist OutputChannel
 * eine sogenannte abstrakte Klasse.
 *
 * Man beachte:
 * Unter den auszugebenden Zeichen befinden
 * sich sogenannte Steuerzeichen, die geeignet
 * zu interpretieren sind.
 * Z.B. newline, carriage return, backspace usw.
 *
 */

class OutputChannel {
public:
	// write ist hier nicht definiert
	// erst abgeleitete Klassen implementieren diese Methode
	// Hinweis: der Rückgabewert spiegelt die Anzahl der ausgegebenen Zeichen wieder
	virtual int write(const char* data, int size) = 0;

	// Methode zur Ausgabe einzelner Zeichen
	// ... aus reiner Bequemlichkeit
   	int write(char c)
	{
		return write(&c, sizeof(c));
	}

	// Bluescreen mit eigener Fehlermeldung
	virtual void blueScreen(const char* error) = 0;
};

#endif
