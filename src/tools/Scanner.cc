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
    switch (ch)
    {
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            return true;
            break;

        default:
            break;
    }
    
   return false;
}

bool Scanner::isWhitespace(char ch)
{
   if (ch == ' ') return true;
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
