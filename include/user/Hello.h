#ifndef Hello_h
#define Hello_h

#include "system/Thread.h"
#include "system/Console.h"

class Hello: public Thread {
public:
	enum { LINE_SIZE = 512 };

	/** Konstruktor mit den bekannten Argumenten..
	 */
	Hello(const char* name, int runs, int slice, void* sp);

	/* Im Destruktor muss auf die Beendigung von "body()"
	 * gewartet werden!
	 */
	~Hello();

	virtual void run();

private:

	int runs;		// Anzahl der Durchlaeufe
	const char* name; 	// Name dieses Threads

	char line[LINE_SIZE];  	// Zeilenpuffer
};

#endif
