#ifndef Stack_h
#define Stack_h

#include "lib/Chain.h"

class Stack {
public:
	Stack () { tos = 0; }

	// Einfuegen eines Elementes auf den Stack
	void push(Chain* item);

	// Entfernen des obersten Stackelements, gibt 0 zurueck wenn leer
	Chain* pop();

    //gibt das oberste element im stack zurueck ohne es zu entfernen
    Chain* peek();

    bool empty()
    {
       if (tos == 0)
       {
           return true;
       }

       return false;
    }

private:
	Chain* tos;
};

#endif
