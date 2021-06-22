#ifndef TOOLS_INTERP_H
#define TOOLS_INTERP_H

#include "Scanner.h"

/*
    Diese Klasse realisiert einen Interpreter für arithmetische Ausdrücke. Da ein Interpreter,
    ähnlich wie ein Compiler, in der Lage sein muss, einzelne Symbole zu untersuchen, wird an
    dieser Stelle von der Klasse Scanner geerbt (d.h. ein Interpreter IST ein Scanner).

    Die folgende Grammatik beschreibt die Sprache, die von diesem Interpreter akzeptiert wird.

    Eine Grammatik ist ein Regelsystem, das eigentlich der Beschreibung von Sprachen dient.
    Man kann sie aber auch zur Erkennung von Sprachen verwenden. Unsere Sprache ist in
    diesem Fall die Menge aller gültigen arithmetischen Ausdrücke. Wer darüber mehr
    erfahren will, bitte die theoretische Informatik besuchen :)

    Der Interpreter hat volle Kenntnis der Grammatik und versucht anhand ihrer Regeln
    die Zeichen im Eingabepuffer geeignet zu interpretieren. Dafür schreitet er Zeichen
    für Zeichen durch die Eingabe. Das geschieht mit consume(). Beachtet, dass diese
    Operation nicht umkehrbar ist. Das aktuelle Zeichen bezeichnet man im Bereich des
    Compilerbau als Lookahead. Leerzeichen o.ä. (auch Whitespace genannt) sind
    unbedeutend und müssen explizit übersprungen werden. Die Klasse Scanner
    liefert hierfür hilfreiche Funktionen.

    Es handelt sich um eine LL(1)-Grammatik, d.h. u.a. dass es genügt, das aktuelle Zeichen zu
    betrachten, um die nächste Regel auszuwählen. LL steht dabei für 'left to right, left-most
    derivation'. Damit gehört sie zu den einfachen Grammatiken. Die Grammatik von C++ z.B.
    ist nicht in LL(1)-Form. Sie ist nicht mal mit den mächtigeren LR(1)-Parsern erkennbar.
    Im Falle unserer Sprache genügt aber ein einfacher Recursive-Descent-Parser.
    Wer darüber mehr erfahren will, dem sei das Modul Compilerbau empfohlen :)

    Start   -> * Dump | Expr
    Expr    -> Sum
    Sum     -> Prod Sum'
    Sum'    -> + Prod Sum' | - Prod Sum' | eps
    Prod    -> Factor Prod'
    Prod'   -> * Factor Prod' | / Factor Prod' | % Factor Prod' | eps
    Factor  -> Num | Ident | ( Expr )
    Num     -> (1 | ... | 9) (0 | ... | 9)*
    Dump    -> Expr
*/
class Interpreter : public Scanner
{
public:
    /** Verschiedene Fehlercodes */
    enum Error {
        UNEXP_EOT = 1,  // Unerwartetes Ende des Puffers
        UNEXP_SYMBOL,   // Unerwartetes Symbol
        ARITHM_ERROR,   // Arithmetischer Fehler
        BAD_BUFFER      // Ungültiger Puffer
    };

    Interpreter()
        : status(0)
    {}

    /**
     * Wertet den gegebenen Ausdruck aus. Das Ergebnis wird in 'result' gespeichert.
     * Tritt während der Auswertung ein Fehler auf, wird ein von null verschiedener
     * Fehlercode zurückgegeben.
     *
     * @param input
     *      Eingabepuffer
     *
     * @param result
     *      Ausgabeparameter, der das Ergebnis speichert.
     *
     * @return
     *      Null, wenn die Auswertung erfolgreich war; sonst einen Fehlercode.
     */
    unsigned eval(char* input, int& result);

private:
    /*
        Diese Funktionen kümmern sich um das Parsen und Auswerten
        von arithmetischen Ausdrücken auf Basis des Eingabepuffers.
        Da der Interpreter genau die obige Grammatik realisieren muss,
        gibt es analog zu jeder Regel eine designierte Funktion. Abhängig
        von den jeweiligen Regeln der Grammatik, können sich diese Funktionen
        gegenseitig aufrufen, ggf. auch rekursiv. Jede Funktion liefert das
        von ihr berechnete Zwischenergebnis als Rückgabewert zurück.
    */
    int evalExpr();
    int evalSum();
    int evalSumTail(int lhs); // lhs steht für ein linksseitiges Zwischenergebnis
    int evalProd();
    int evalProdTail(int lhs); // lhs steht für ein linksseitiges Zwischenergebnis
    int evalFactor();
    int evalNum();
    int evalDump();

    /** Status des Interpreters. Null, wenn alles OK ist, ansonsten ein Fehlercode. */
    unsigned status;
};

#endif
