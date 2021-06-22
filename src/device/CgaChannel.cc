#include "device/CgaChannel.h"

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



// Ausgabekanal mit Standardattributen
CgaChannel::CgaChannel()
{
    this->attr = CgaAttr();

}

// Ausgabekanal mit spezifischen Attributen
CgaChannel::CgaChannel(const CgaAttr &attr)
{
    setAttr(attr);
}

// Die von OutputChannel deklarierte Ausgaberoutine
int CgaChannel::write(const char *data, int size)
{
    CgaAttr attr;
    getAttr(attr);
	for (int i = 0; i < size; i++)
    {
        char c = data[i];
        if (c == '\n')
        {
            int col, row;
            getCursor(col, row);
             
            for (int i = 0; i < COLUMNS - col; i++)
            {
                moveCursorByOne();
            }
            
        } 
        else if (c == '\r')
        {
            int col, row;
            getCursor(col, row);
            setCursor(0, row);
        } 
        else 
        {
            show(c, attr);
        }
        
    }

    return 0;
    
}

// Bluescreen mit eigener Fehlermeldung
void CgaChannel::blueScreen(const char *error)
{
    CgaAttr attr = CgaAttr(CgaAttr::WHITE, CgaAttr::BLUE, false);
    setAttr(attr);
    overwriteScreen(attr);

    int size = strSizeC(error);
	write(error, size);
}

//berechnet string size
int CgaChannel::strSizeC(const char *str)
{
    int size = 0;
    while (str[size] != '\0')
    {
        size++;
    }

    return size;
    
}