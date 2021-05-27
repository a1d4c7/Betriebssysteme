#ifndef Debugger_h
#define Debugger_h

#include "io/PrintStream.h"

/*
 * Debugger: 	Diese Klasse implementiert nichts lol
 * 			
 *
 */



class Debugger {
public:
	Debugger(PrintStream& out) : mitteilungsAusgabekanal(out)
	{
		//join = false;
	}

	void fehler(const char* str)
	{
		mitteilungsAusgabekanal.print(str);
	}

	void line(const char* str)
	{
		mitteilungsAusgabekanal.println(str);
	}

	void ausgabePointer(const char* name, void* p)
	{
		mitteilungsAusgabekanal.print(name);
		mitteilungsAusgabekanal.print(": ");
		mitteilungsAusgabekanal.print(p);
		mitteilungsAusgabekanal.print(", ");
	}

	//bool join;

protected:
	
private:
	PrintStream& mitteilungsAusgabekanal;

};

extern Debugger debuggi;

#endif
