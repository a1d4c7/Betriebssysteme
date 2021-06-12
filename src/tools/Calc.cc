#include "tools/Calc.h"

#include "device/CgaChannel.h" // ermöglicht Kontrolle über Cursor
#include "device/Keyboard.h" // ermöglicht Eingaben durch Tastatur
#include "io/PrintStream.h" // ermöglicht Linefeeds und Ausgabe von Zahlen

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
            //TODO
            //left, right behandlung, TODO delete
            if (key.getValue() == CodeTable::LEFT) moveLeft();
            if (key.getValue() == CodeTable::RIGHT) moveRight();
            
        }
    }
    while(c!='x');
}

void Calculator::insert(char c)
{
    //falls enter gedrueckt wurde
    if (c == '\n') 
    {
        enter(); 
        return;
    }
    
    //TODO was wenn nicht enter (zeichen, ungueltiges zeichen,...)
}

void Calculator::enter()
{
    //legenede:
    //zahl: 0-9
    //rechenzeichen: +-*/
    //trennungszeichen: ()
    //expr: 
    //zahl^n, rechenzeichen, zahl^n
    //zahl^n, rechenzeichen, trennungszeichen, expr, trennungszeichen
    //expr, rechenzeichen, expr

    //                expr
    //           expr  rz         expr
    //       zahl rz  zahl   |  (zahl rz expr)
    //....   

    //https://en.wikipedia.org/wiki/Shunting-yard_algorithm
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
