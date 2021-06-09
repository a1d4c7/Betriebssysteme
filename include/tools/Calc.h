#ifndef TOOLS_CALC_H
#define TOOLS_CALC_H

#include "thread/Activity.h"
#include "tools/Interp.h"

/** Ein einfacher interaktiver Taschenrechner */
class Calculator : public Activity
{
public:
    /** Erzeugt einen Calculator, der auf dem Kernel-Stack läuft */
    explicit Calculator();

    /** Erzeugt einen Calculator, der auf einem User-Stack läuft */
    explicit Calculator(void* sp);

    /**
     * Initialisiert den Calculator.
     *
     * Um in einen definierten Anfangszustand zu gelangen, sollte
     * (1) der Eingabepuffer initialisiert werden und (2) der
     * Bildschirm geleert werden.
     *
     * Sollte aufgerufen werden, bevor die eigentliche Ausführung
     * des Calculators beginnt.
     */
    void init();

    /**
     * Das eigentliche Programm des Calculators.
     *
     * Bei dem Calculator handelt es sich im Prinzip um eine sogenannte
     * Read-Eval-Print-Loop (REPL). Ihr lest also wiederholt Zeichen
     * von der Tastatur ein, puffert diese und wertet die
     * resultierende Zeichenkette auf Bestätigung aus.
     *
     * Beim Einlesen und Puffern von Zeichen muss darauf geachtet werden,
     * dass nur ASCII-Zeichen gepuffert werden, während andere Zeichen
     * wie Zeilenumbrüche oder Pfeil-Tasten separat behandelt werden.
     * Bei Eingabe der Escape-Taste, soll das Programm beenden.
     *
     * Ist die Auswertung erfolgreich, wird das Ergebnis ausgegeben.
     * Andernfalls soll eine Fehlermeldung ausgegeben werden.
     * Die jeweilige Ausgabe erfolgt auf einer neuen Zeile.
     *
     * Die Eingabe eines weiteren Ausdrucks erfolgt stets
     * auf einer neuen Zeile. Ein Ausdruck darf dabei nie
     * länger sein als der zugrunde liegende Eingabepuffer.
     * Letzterer wiederum darf nicht mehr Zeichen als
     * eine Zeile auf dem CGA-Bildschirm haben (siehe
     * EXPR_SIZE_MAX).
     */
    void body();

private:
    /** Interne Konstanten */
    enum {
        // Maximale Länge eines Ausdrucks (darf die Zeilenlänge (= 80) nicht überschreiten)
        EXPR_SIZE_MAX = 32
    };

    // ========================================================================
    // Funktionen zur Eingabebehandlung
    // ========================================================================

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
    void insert(char c);

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
    void enter();

    /**
     * Behandelt das Betätigen der Pfeil-Links-Taste.
     *
     * Das Betätigen der Pfeil-Links-Taste soll den Cursor
     * genau eine Position nach links bewegen. Beachtet
     * hierbei etwaige Randfälle.
     */
    void moveLeft();

    /**
     * Behandelt das Betätigen der Pfeil-Rechts-Taste.
     *
     * Das Betätigen der Pfeil-Rechts-Taste soll den Cursor
     * genau eine Position nach rechts bewegen. Beachtet
     * hierbei etwaige Randfälle.
     */
    void moveRight();

    // ========================================================================
    // Hilfsmethoden
    // ========================================================================

    /** Schreibt den Eingabe-Puffer in den Grafikspeicher */
    void renderBuffer();

    /** Leert den Eingabepuffer */
    void clearBuffer();

    /**
    * Gibt eine Fehlermeldung für einen Fehlercode des Interpreters aus.
    *
    * So ein Fehlercode tritt auf, wenn während der Auswertung eines
    * Ausdrucks durch den Interpreter ein Fehler auftritt.
    *
    * @param code
    *      Ein Fehlercode des Interpreters.
    */
    void printErrorMsg(unsigned code);

    // ========================================================================
    // Attribute
    // ========================================================================

    /** Wertet vom Benutzer eingegebene Ausdrücke aus */
    Interpreter interp;

    /** Eingabepuffer. Speichert den Inhalt der aktuellen Zeile sowie ein Null-Byte. */
    char buffer[EXPR_SIZE_MAX + 1];
};

#endif
