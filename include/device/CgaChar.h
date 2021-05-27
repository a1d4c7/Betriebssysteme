#ifndef CgaChar_h
#define CgaChar_h

#include "device/CgaAttr.h"

/*
 * CgaChar:
 * 
 *	Diese Klasse stellt den Prototyp eines
 *	Zeichens des Bildschirms dar.
 *	Dieses besteht aus darstellbarem Zeichen
 *	und Darstellungsattributen.
 */


class CgaChar {

public:

	// setzen des Zeichens
	void setChar(char c) 
	{
		ch = c;
	}
	
	// auslesen des Zeichens
	char getChar()
	{
		return ch;
	}
	
	// setzen der Darstellungsattribure
	void setAttr(const CgaAttr& attr)
	{
		at = attr;
	}
	
	// auslesen der Darstellungsattribute
	CgaAttr getAttr()
	{
		return at;
	}

private:
	char ch;
	CgaAttr at;

};

#endif

