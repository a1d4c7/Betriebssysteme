#ifndef CgaChannel_h
#define CgaChannel_h

#include "io/OutputChannel.h"
#include "device/CgaScreen.h"

/*
 * CgaChannel:	Diese Klasse implementiert einen Ausgabekanal
 *		fuer den CGA-Bildschirm
 *
 *		Sie *muss* die 'write' Methode implementieren,
 *		und alle write() Aufrufe geeignet auf den CgaScreen abbilden.
 *
 *      Man beachte:
 *		Unter den auszugebenden Zeichen befinden
 *		sich sogenannte Steuerzeichen, die geeignet
 *		zu interpretieren sind.
 *
 *		Es reicht fuer diese Uebung, wenn Ihr die
 *		Steuerzeichen '\n' (newline, NL) und '\r' (Carriage Return, CR)
 *		interpretiert.
 *		Bei CR ist der Cursor auf den Anfang der aktuellen Zeile
 *		zu setzen. Bei NL wird der Cursor auf den Anfang
 *		der naechsten Zeile gesetzt.
 */

class CgaChannel: public OutputChannel, public CgaScreen {
public:
	// Ausgabekanal mit Standardattributen
	CgaChannel();

	// Ausgabekanal mit spezifischen Attributen
	explicit CgaChannel(const CgaAttr& attr);

	// Die von OutputChannel deklarierte Ausgaberoutine
	virtual int write(const char* data, int size);

	// Bluescreen mit standard Fehlermeldung
	void blueScreen()
	{
		blueScreen("ERROR");
	}

	// Bluescreen mit eigener Fehlermeldung
	virtual void blueScreen(const char* error);

	int strSizeC(const char *str);
};

#endif
