#ifndef InputChannel_h
#define InputChannel_h

/**	InputChannel:
 * 	Diese Klasse ist die Abstraktion für einen Eingabekanal.
 *
 *	Beachte, dass die 'read'- Methode
 *	eine so genannte pure virtuelle Methode ist,
 *	fuer die hier keine Implementierung
 *	angegeben wird. Daher ist InputChannel
 *	eine sogenannte abstrakte Klasse.
 */

class InputChannel {
public:
	/** Diese Methode kehrt zurück, wenn die Anzahl der mit size angegebenen
	 *  Zeichen erreicht ist oder ein '\n' vorliegt. Es werden alle
	 *  Ascii-zeichen in den Datenbereich geschrieben.
	 */
	virtual int read(char* data, int size) = 0;
};

#endif
