// Testprogramm fuer Coroutinen

#include "device/CgaChannel.h"
#include "io/PrintStream.h"
#include "thread/Coroutine.h"

// Eine Coroutinen-Klasse
//
// Anmerkung: Diese Klasse dient
// zu Testzwecken und der Einfacheit halber sind
// alle Methoden dieser Klasse ausnahmsweise inline deklariert
// Das sollte normalerweise *nicht* der Fall sein!

class Hello: public Coroutine {
public:
	Hello(const char* name, PrintStream& out)
		: cout(out)
	{
		this->name = name;
	}

	Hello(const char* name, PrintStream& out, void* sp)
		: Coroutine(sp), cout(out)
	{
		this->name = name;
	}

	void link(Coroutine& next)
	{
		this->next = &next;
	}

	void body()
	{
		for(int i=0; i<5; i++) {
			cout.print(name);
			cout.print(" ");
			cout.print(i);
			cout.println();

			resume(next);	
		}
	}

	void exit()
	{
		cout.print("Panic!!!!");
		cout.println();
	}

	const char* name;
	Coroutine* next;

	PrintStream& cout;
};

//////////////////////////////////////////////////////////////////////////
// Die Systemobjekte von Co-Stubs

// globale Ein-/Ausgabeobjekte

CgaChannel cga;         // unser CGA-Ausgabekanal
PrintStream out(cga);   // unseren PrintStream mit Ausgabekanal verknuepfen

// die Stacks fuer unsere Prozesse/Coroutinen

unsigned stack0[1024];
unsigned stack1[1024];

int main()
{
	
	
	Hello anton("Anton", out); // anton benutzt den Stack von main
	Hello berta("Berta", out, &stack0[1024]);
	Hello caesar("Caesar", out, &stack1[1024]);

	

	// alle Coroutinen zyklisch verketten
	anton.link(berta);
	berta.link(caesar);
	caesar.link(anton);
	

	
	// los geht's
	anton.body(); 

	/*
	//loesung fuer ende von coroutinen
	const char* name = berta.name;
	out.print(name);
	out.print(" ");
	berta.exit();
	*/
}
