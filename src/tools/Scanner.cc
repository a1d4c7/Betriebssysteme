#include "tools/Scanner.h"

void Scanner::consume()
{
    if (lookahead() != '\0')
        ++position;
}

void Scanner::consumeWS()
{
    char ch;
    while (lookahead(&ch) && isWhitespace(ch))
        consume();
}

char Scanner::lookahead()
{
    if (position >= length)
        return 0;

    return input[position];
}

bool Scanner::lookahead(char* dest)
{
    if (dest == 0)
        return false;

    if (position >= length)
        return false;

    *dest = input[position];
    return (*dest != '\0');
}

bool Scanner::isDigit(char ch)
{
   return false;
}

bool Scanner::isWhitespace(char ch)
{
   return false;
}

void Scanner::init(char* input)
{
    this->input = input;
    position = 0;
    length = 0;
    for (; *input != 0; ++input)
        ++length;
}
