#include "device/CgaScreen.h"

#include "device/CgaAttr.h"
#include "device/CgaChar.h"
#include "io/IOPort.h"
#include "lib/tools.h"

/*
 * CgaScreen:	Diese Klasse ist der Softwareprototyp fuer den
 *		CGA-Bildschirm
 *		
 *      Hier soll es ausschliesslich um die Kontrolle der Hardware
 *      gehen. Komplexere Aufgaben koennen in den erbenden Klassen
 *      implementiert werden.
 */



// Standardattribute waehlen und Bildschirm loeschen
CgaScreen::CgaScreen()
{          
    attr = CgaAttr();
	screen = (CgaChar*) V_RAM_START;
    clear();

}

// Angegebene Attribute setzen und Bildschirm loeschen
CgaScreen::CgaScreen(CgaAttr attr)
{
	this->attr = attr;
	screen = (CgaChar*) V_RAM_START;
    clear();
}


// Loeschen des Bildschirms
void CgaScreen::clear()
{  
   CgaAttr at = CgaAttr();
   overwriteScreen(at);
}

// Verschieben des Bildschirms um eine Zeile
void CgaScreen::scroll()
{
    setCursor(0, ROWS - 1);

    for (int i = 1; i < ROWS; i++)
    {
        scrollOneRow(i); 
    }

    //clearen letzte zeile
    for (int i = 0; i < COLUMNS; i++)
    {
        int pos = (ROWS - 1) * COLUMNS + i;
        CgaChar ch = CgaChar();
        ch.setChar(' ');

        CgaAttr at = CgaAttr();
        getAttr(at);
        ch.setAttr(at);
        
        writeChar(ch, pos);
    }

          
    setCursor(0, ROWS - 1);
    
}

//verschieben einer einzelnen zeile um eins nach oben
void CgaScreen::scrollOneRow(int row)
{
    for (int i = 0; i < COLUMNS; i++)
    {
        int pos = row * COLUMNS + i;
        CgaChar ch = CgaChar();
        ch = readChar(pos);
        
        writeChar(ch, pos - COLUMNS);
          
    }
}

// Setzen/Lesen des HW-Cursors
void CgaScreen::setCursor(int column, int row)
{
	unsigned pos = row * COLUMNS + column;
    
    index.write(14);
    data.write((pos & 0xff00) >> 8);

    index.write(15);
    data.write(pos & 0x00ff);
}

void CgaScreen::getCursor(int &column, int &row)
{ 
    index.write(14);
    unsigned pos = data.read();

    index.write(15);
    pos = (pos << 8) | data.read();

    row = pos / COLUMNS;
	column = pos % COLUMNS;
}

// Anzeigen von c an aktueller Cursorposition
// Darstellung mit angegebenen Bildschirmattributen
void CgaScreen::show(char ch, const CgaAttr &attr)
{
    int row, col = 0;
    getCursor(col, row);

    int pos = row * COLUMNS + col;
    CgaChar c = CgaChar();
    c.setAttr(attr);
    c.setChar(ch);
    writeChar(c, pos);

    moveCursorByOne();
}

//schreibt ein cga zeichen aus dem speicher
void CgaScreen::writeChar(CgaChar ch, int pos) {
    unsigned char c = ch.getChar();
    unsigned char a = ch.getAttr().createCgaAttrByte();

    short zeichen = ((0x0000 | a) << 8) | c;
    short* i = (short*) screen + pos;
	*i = zeichen;
}

//liest ein cga zeichen aus dem speicher
CgaChar CgaScreen::readChar(int pos) 
{
    short* i = (short*) screen + pos;
	short zeichen  = *i;

    unsigned char a = (zeichen >> 8) & 0x00ff;
    unsigned char c = zeichen & 0x00ff;


    CgaAttr at = CgaAttr();
    at.findAttributes(a);


    CgaChar ch = CgaChar();
    ch.setAttr(at);
    ch.setChar((char) c);

    return ch;  
    
}



//setz den cursor um eine position weiter
//prueft ob zeilenende ueberschritten wird
void CgaScreen::moveCursorByOne()
{
    int row, column;
	getCursor(column, row);

    if (column + 1 >= COLUMNS)
	{
        if (row + 1 >= ROWS)
        {
            scroll();
            getCursor(column, row);
        } 
        else
        {
            row += 1;
		    column = 0;
        }	
	}
    else
	{
		column += 1;
	}

    setCursor(column, row);
}

//komplettes ueberschreiben des bildschirms mit dem attribut
void CgaScreen::overwriteScreen(CgaAttr at)
{
    setCursor(0,0);

    CgaChar ch = CgaChar();
    ch.setAttr(at);
    char c = ' ';
    ch.setChar(c);

    for (int i = 0; i < ROWS * COLUMNS; i++)
    {
        writeChar(ch, i);
    }

    setCursor(0,0);
}

