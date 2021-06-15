#include "tools/Calc.h"

#include "device/CgaChannel.h" // ermöglicht Kontrolle über Cursor
#include "device/Keyboard.h" // ermöglicht Eingaben durch Tastatur
#include "io/PrintStream.h" // ermöglicht Linefeeds und Ausgabe von Zahlen
#include "tools/Interp.h"

extern CgaChannel cga;
extern PrintStream out;

Calculator::Calculator()
{
    init();
}

Calculator::Calculator(void* sp)
    : Activity(sp)
{
    init();
    wakeup();
}

void Calculator::init()
{
    clearBuffer();
    cga.clear();
}

void Calculator::body()
{
    char c;
    Key key;
    do{
        key = keyboard.read();
        c = key.getValue();

        //eingegebenes zeichen ist ein ascii-char
        if (key.isAscii()) 
        {
            insert(c);
        }
        else //ist kein ascii-char
        {
            if (key.getValue() == CodeTable::LEFT) moveLeft();
            if (key.getValue() == CodeTable::RIGHT) moveRight();
            
            if(key.getValue() == CodeTable::DEL)
            {
                int col, row;
                cga.getCursor(col, row);

                for (int i = col; i < EXPR_SIZE_MAX; i++)
                {
                    buffer[i] = buffer[i + 1]; //Zeichen rechts vom Cursor werden nach links geshiftet
                }

                renderBuffer();
                
            }
        }
    }
    while(c!=(char) 27); //TODO-Test ende bei eingabe von ESC
}


/**
 * Behandelt die Eingabe eines ASCII-Zeichens.
 *
 * Falls möglich, wird das Zeichen an der aktuellen Position eingefügt.
 *
 * Hierzu müssen ggf. bereits eingegebene Zeichen verschoben werden
 * Überlegt euch, wie ihr verfahrt wenn, die maximale Ausdruckslänge
 * durch die Eingabe des neuen Zeichens überschritten wird.
 *
 * Beachtet außerdem, dass jedes gültige Zeichen gepuffert werden muss,
 * damit der Interpreter den insgesamten Ausdruck auswerten kann.
 *
 * @param c
 *      Ein ASCII-Zeichen
 */
void Calculator::insert(char c)
{
    //falls enter gedrueckt wurde
    if (c == '\n') 
    {
        enter();
        clearBuffer(); 
        return;
    }

    //falls backspace gedrueckt wurde
    if (c == (char) 8)
    {
        int col, row;
        cga.getCursor(col, row);
        
        if (col == 0) return;

        for (int i = col - 1; i < EXPR_SIZE_MAX; i++)
        {
            buffer[i] = buffer[i + 1]; //Zeichen rechts vom Cursor werden nach links geshiftet
        }

        cga.setCursor(col - 1, row);

        renderBuffer();
        return;
    }

    
    
    //TODO was wenn nicht enter (zeichen, ungueltiges zeichen,...)
    //ungültiges Zeichen wahrscheinlich vernachlässigbar, weil bei enter überprüft wird
    //gültige Zeichen: 0-9, a-f, (b), x, +-*/% 
    int col, row;
    cga.getCursor(col, row);
    if (col < EXPR_SIZE_MAX) 
    {
        //Zeichen rechts vom Cursor werden nach rechts geshiftet
        //bei Erreichen maximaler Länge wird letztes Zeichen gelöscht
        for (int i = EXPR_SIZE_MAX - 1; i > col; i--)
        {
            buffer[i] = buffer[i - 1];                         
        }

        buffer[col] = c; //Übergebenes Zeichen wird an Corsorposition eingefügt

        
        if (col < EXPR_SIZE_MAX - 1) cga.setCursor(col + 1, row);
    }
    
    renderBuffer();
}


/**
 * Behandelt das Betätigen der Eingabe-Taste.
 *
 * Das Betätigen der Eingabe-Taste soll zur Folge haben,
 * der aktuell gepufferte Ausdruck ausgewertet wird.
 *
 * Ist die Auswertung erfolgreich, soll das Ergebnis ausgegeben werden.
 * Andernfalls ist eine dem Rückgabe-Status angemessene Fehlermeldung
 * auszugeben. Dies erfolgt in der nächsten Zeile.
 *
 * Für die Eingabe des nächsten Ausdrucks sollte der Cursor
 * entsprechend positioniert werden.
 */
void Calculator::enter()
{
    out.println();

    Interpreter interp;
    int result = 0;
    unsigned status = interp.eval(buffer, result);

    if (status != 0)
    {
        printErrorMsg(status);
        out.println(); //TODO-Test Scrollen
        return;
    }

     
    //ergebnis ausgabe
    out.print("= ");
    out.print(result);
    out.println(); //TODO-Test Scrollen
}

void Calculator::moveLeft()
{
    int col, row;
    cga.getCursor(col, row);

    if (col > 0)
    {
        cga.setCursor(col - 1, row);
    }    
}

void Calculator::moveRight()
{
    int col, row;
    cga.getCursor(col, row);

    if (col < EXPR_SIZE_MAX - 1) //entweder moven cursor nur in expression reichweite oder ganze zeile
    {
        cga.setCursor(col + 1, row);
    } 
}

void Calculator::renderBuffer()
{
    // Cursor sichern
    int column, row;
    cga.getCursor(column, row);

    // Zeile schreiben
    cga.setCursor(0, row);
    cga.write(buffer, EXPR_SIZE_MAX);

    // Cursor wiederherstellen
    cga.setCursor(column, row);
}

void Calculator::clearBuffer()
{
    // Alle Zeichen nullen und Null-Byte hinter der höchsten Stelle setzen
    for (unsigned i=0; i<=EXPR_SIZE_MAX; ++i)
        buffer[i] = 0;
}

void Calculator::printErrorMsg(unsigned code)
{
    switch (code) {
    case Interpreter::UNEXP_EOT:
        out.print("Error: Unexpected end of expression!");
        break;

    case Interpreter::UNEXP_SYMBOL:
        out.print("Error: Unexpected symbol!");
        break;

    case Interpreter::ARITHM_ERROR:
        out.print("Error: Arithmetic error!");
        break;

    case Interpreter::BAD_BUFFER:
        out.print("Error: Invalid buffer!");
        break;

    default:
        break;
    }
}
