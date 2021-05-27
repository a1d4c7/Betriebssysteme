#ifndef CgaScreen_h
#define CgaScreen_h

#include "device/CgaAttr.h"
#include "device/CgaChar.h"
#include "io/IOPort.h"

/*
 * CgaScreen:	Diese Klasse ist der Softwareprototyp fuer den
 *		CGA-Bildschirm
 *		
 *      Hier soll es ausschliesslich um die Kontrolle der Hardware
 *      gehen. Komplexere Aufgaben koennen in den erbenden Klassen
 *      implementiert werden.
 */


class CgaScreen {

private:

	// Die I/O-Ports des Grafikcontrollers
	enum Ports  {
		INDEX = 0x3d4, // nur schreiben
		DATA = 0x3d5   // lesen und schreiben
	};

	// Die Kommandos zum Cursor setzen
	enum Cursor {
	};

	// Die Adresse des Video RAMs
	enum Video  {
		V_RAM_START = 0xb8000, // plus (25 * 80) * 2 = 4000 = (0x0FA0) also 0xb8000 + 0x0FA0 = 0xb8FA0
		V_RAM_ENDE = 0xb8FA0
	};

public:
	// Die Bildschirmdimensionen
	enum Screen {
		ROWS = 25,
		COLUMNS = 80
	};

	// Standardattribute waehlen und Bildschirm loeschen
	CgaScreen();

	// Angegebene Attribute setzen und Bildschirm loeschen
	explicit CgaScreen(CgaAttr attr);

	// Loeschen des Bildschirms
	void clear ();

	// Verschieben des Bildschirms um eine Zeile
	void scroll();

	// Setzen/Lesen der globalen Bildschirmattribute
	void setAttr(const CgaAttr& attr)
	{
		this->attr = attr;
	}

	void getAttr(CgaAttr& attr)
	{
		attr = this->attr;
	}

	// Setzen/Lesen des HW-Cursors
	void setCursor(int column, int row);
	void getCursor(int& column, int& row);


	// Anzeigen von c an aktueller Cursorposition
    	// Darstellung mit angegebenen Bildschirmattributen
	void show(char ch, const CgaAttr& attr);

	// Anzeigen von c an aktueller Cursorposition
    	// Darstellung mit aktuellen Bildschirmattributen
	void show(char ch)
	{
		show(ch, attr);
	}

	void writeChar(CgaChar ch, int pos);
	CgaChar readChar(int pos);
	void moveCursorByOne();
	void scrollOneRow(int row);
	void overwriteScreen(CgaAttr attr);

protected:

	CgaAttr attr;
	IOPort8 index = IOPort8(INDEX);
	IOPort8 data = IOPort8(DATA);
	CgaChar* screen;
};

#endif