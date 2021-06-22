#ifndef TOOLS_SCANNER_H
#define TOOLS_SCANNER_H

/**
 * Diese Klasse stellt wichtige Grundfunktion zum Parsen eines Ausdrucks zur Verfügung.
 *
 * Dazu verfügt jeder Scanner über einen Zeiger auf die gewünschte Zeichenkette. Diese
 * muss mit Hilfe eines Null-Bytes terminiert sein, der Scanner sonst nicht die Länge
 * der Eingabe ermitteln kann.
 *
 * Der Scanner verfügt über einen Lesekopf (siehe 'position'), mit dessen Hilfe er
 * über lookahead() das aktuelle Zeichen auslesen kann. Der Lesekopf wird mit
 * consume() verschoben (d.h. das aktuelle Zeichen wird konsumiert) und kann
 * nicht zurückgeschoben werden.
 *
 * Außerdem verfügt der Scanner über die Möglichkeit zu entscheiden, ob es sich
 * bei einem Zeichen um eine Ziffer oder um Whitespace (Leerzeichen o.ä.) handelt.
 */
class Scanner
{
public:
    /**
     * Bewegt den Lesekopf um eine Position nach rechts.
     * Hat keinen Effekt wenn das Ende des Puffers erreicht ist.
     */
    void consume();

    /**
     * Bewegt den Lesekopf zum nächsten Zeichen, das kein Whitespace ist.
     * Dadurch werden alle aufeinanderfolgenden Whitespaces übersprungen.
     * Hat keinen Effekt wenn das Ende des Puffers erreicht ist.
     */
    void consumeWS();

    /**
     * Liefert das Zeichen an der aktuellen Position.
     *
     * @return
     *      Zeichen an der aktuellen Position. Kann auch ein Null-Byte sein.
     */
    char lookahead();

    /**
     * Speichert das Zeichen an der aktuellen Leseposition in 'dest'.
     * Prüft außerdem, ob das Ende des Puffers erreicht ist. Das ist
     * hilfreich, wenn das aktuelle Zeichen nur dann verarbeitet
     * werden soll, wenn es nicht das Null-Byte ist.
     *
     * @param dest
     *      Ziel zum Speichern des aktuellen Zeichens.
     * @return
     *      True wenn aktuelles Zeichen nicht das Null-Byte ist, sonst false.
     */
    bool lookahead(char* dest);

    /**
     * Prüft, ob das Zeichen eine Ziffer repräsentiert [0..9]
     *
     * @param ch
     *       Ein ASCII-Zeichen.
     * @return
     *       True wenn das Zeichen eine Ziffer repräsentiert, sonst false.
     */
    bool isDigit(char ch);

    /**
     * Prüft, ob es sich bei dem Zeichen um ein Whitespace-Zeichen handelt.
     *
     * @param ch
     *       Ein ASCII-Zeichen.
     * @return
     *       True wenn es sich um ein Whitespace-Zeichen handelt, sonst false.
     */
    bool isWhitespace(char ch);

protected:
    /**
     * (Re-)Initialisiert diesen Scanner.
     *
     * Diese Funktion muss aufgerufen werden, damit der Scanner
     * auf die gewünschte Eingabe zugreifen kann. Außerdem werden
     * alle Attribute wie der Lesekopf etc. zurückgesetzt.
     *
     * @param input
     *      Zeiger auf die zu lesende Zeichenkette.
     */
    void init(char* input);

private:
    /** Zeiger auf die zu lesende Zeichenkette */
    char* input;

    /** Länge der aktuellen Zeichenkette */
    unsigned length;

    /** Aktuelle Position des Lesekopfes */
    unsigned position;
};

#endif
