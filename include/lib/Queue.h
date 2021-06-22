#ifndef Queue_h
#define Queue_h

#include "lib/Chain.h"

class Queue {
public:
	Queue () { head = 0; tail = &head; }

	// Einfuegen eines Elementes an das Ende der Liste
	void enqueue(Chain* item);

	// Entfernen des Listenkopfes
	Chain* dequeue();

	// Entfernen des angegebenen Elementes
	void remove(Chain* item);

private:
	Chain* head;	// der Listenkopf
	Chain** tail;	// Zeiger auf den Zeiger auf das Listenende
};

#endif
