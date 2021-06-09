#include "tools/Interp.h"

unsigned Interpreter::eval(char* input, int& result)
{
    if (!input)
        return BAD_BUFFER;

    // Lesenkopf etc. initialisieren
    Scanner::init(input);
    status = 0;

    if (lookahead() == '*') {
        consume();
        result = evalDump();
    }
    else {
        result = evalExpr();
    }
    return status;
}

int Interpreter::evalExpr()
{
    return evalSum();
}

int Interpreter::evalSum()
{
    return evalSumTail(evalProd());
}

int Interpreter::evalSumTail(int lhs)
{
    // Whitespace überspringen
    consumeWS();

    // Passende Regel auswählen
    switch (lookahead()) {
        case '+':
            consume();
            return lhs + evalSumTail(evalProd());

        case '-':
            consume();
            // Operation ist linksassoziativ, muss also von linksbündig ausgewertet werden.
            return evalSumTail(lhs - evalProd());

        // Mögliche Zeichen bei Epsilon-Regel
        case '\0':
        case ')':
            return lhs;

        default:
            status = UNEXP_SYMBOL;
    }
    return 0;
}

int Interpreter::evalProd()
{
    return evalProdTail(evalFactor());
}

int Interpreter::evalProdTail(int lhs)
{
    // Whitespace überspringen
    consumeWS();

    // Passende Regel auswählen
    switch (lookahead()) {
        case '*':
            consume();
            return lhs * evalProdTail(evalFactor());

        case '/':
            consume();
            // Prüfen, ob factor nicht negativ ist (Division durch null ist nicht erlaubt)
            if (int nextFactor = evalFactor())
                // Operation ist linksassoziativ, muss also von linksbündig ausgewertet werden.
                return evalProdTail(lhs / nextFactor);

            status = ARITHM_ERROR;
            return 0;

        case '%':
            consume();
            // Prüfen, ob factor nicht negativ ist (Division durch null ist nicht erlaubt)
            if (int nextFactor = evalFactor())
                // Operation ist linksassoziativ, muss also von linksbündig ausgewertet werden.
                return evalProdTail(lhs % nextFactor);

            status = ARITHM_ERROR;
            return 0;

        // Mögliche Zeichen bei Epsilon-Regel
        case '+':
        case '-':
        case ')':
        case '\0':
            return lhs;

        default:
            status = UNEXP_SYMBOL;
    }
    return 0;
}

int Interpreter::evalFactor()
{
    // Whitespace überspringen
    consumeWS();

    // Passende Regel auswählen
    char LA = lookahead();
    if (LA == '(') { // Öffnende Klammer
        consume();
        // Werte geschachtelten Ausdruck aus
        int ret = evalExpr();
        if (lookahead() != ')') { // Schließende Klammer
            status = UNEXP_SYMBOL;
            return 0;
        }
        consume();
        return ret;
    }
    else if (isDigit(LA)) { // Ziffer
        return evalNum();
    }
    else if (LA == '\0') { // Ende des Puffers
        status = UNEXP_EOT;
    }
    else {
        status = UNEXP_SYMBOL;
    }
    return 0;
}

int Interpreter::evalNum()
{
    char ch = lookahead();

    // Abbrechen, falls Lookahead keine Ziffer ist
    if (!isDigit(ch)) {
        status = UNEXP_SYMBOL;
        return 0;
    }

    // Basis für Interpretation von Zahlen (wird überschrieben, falls 0x oder 0b gefunden werden)
    int base = 10;

    // Das Ergebnis (entsteht durch Addition, daher 0 als neutrales Element)
    int numValue = 0;

    // Prüfe auf führende null (mögliches Anzeichen für Formatpräfix wie 0x oder 0b)
    if (ch == '0') {

        // Gehe zu nächsten Symbol (aktuelle Ziffer ist unerheblich für Resultat)
        consume();
        ch = lookahead();

        // Prüfe auf Formatpräfix für binäre bzw. hexadezimale Zahlen und passe ggf. die Basis an.
        if (ch == 'b') {
            base = 2;
            consume();
        }
        else if (ch == 'x') {
            base = 16;
            consume();
        }
    }

    // Führe Reduktion mittels Addition über Folge von Ziffern aus.
    // Das Polynom lautet (((0 * base + d0) * base + d1) * ... ) * base + dn.
    while (lookahead(&ch)) {
        // Multipliziere Basis mit Zwischenergebnis um 'Platz zu schaffen' für nächste Ziffer
        int tmp = numValue * base;

        // Konvertiere Ziffern passend zur Basis und addiere auf Zwischenergebnis
        if (isDigit(ch))
            tmp += ch - '0';
        else if (base == 16 && ch >= 'a' && ch <= 'f')
            tmp += ch - 'a' + 10;
        else if (base == 16 && ch >= 'A' && ch <= 'F')
            tmp += ch - 'A' + 10;
        else
            break;

        // Aktualisiere das Zwischenergebnis, jetzt wo wir wissen, dass eine gültige Ziffer vorlag
        numValue = tmp;
        consume();
    }
    return numValue;
}

int Interpreter::evalDump()
{
    return 0;
}
