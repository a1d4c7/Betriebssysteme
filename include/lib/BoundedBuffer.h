#ifndef BoundedBuffer_h
#define BoundedBuffer_h

#include "thread/Activity.h"
#include "thread/ActivityScheduler.h"
#include "interrupts/IntLock.h"
#include "lib/Queue.h"


/** Diese Klasse stellt einen begrenzten synchronisierten
 *  Puffer dar, welcher von Interruptbehandlungsroutinen
 *  gef�llt werden kann.
 *
 *  Die Klasse ist eine Templateklasse. Das bedeutet f�r euch
 *  erstmal nur, das ihr alle Methoden hier im Header implementieren
 *  m�sst.
 */
template<typename T,unsigned size>
class BoundedBuffer {
public:

	BoundedBuffer()
	{
		in = startArray;
		out = startArray;
		
		isEmpty = true;
		isFull = false;

		//TODO ?
		//array initialisieren mit leeren T's
		/*
		for (unsigned int i = 0; i < size; i++)
		{
			buffer[i] = T();
		}
		*/
	}

	/** Diese Methode wird vom Interrupthandler aufgerufen, um
	 *  ein etwas in den Puffer zu schreiben. Ist der Puffer voll,
	 *  werden die zu schreibenden Daten verworfen.
	 *  Prozesse die auf eine Eingabe warten m�ssen hier geweckt werden.
	 */
	void add(T& elem)
	{
		
		//TODO
		//intlock ueberdenken da in aufgabe steht add darf nicht blockieren
		//brauchen aber das intlock in der if (!isFull) weil in moveIn() pointer veraendert werden
		//ausserdem wird in der while(toWake) mit dequeue auf eine queue zugegegriffen
		IntLock lock; //aendern von pointern

		if (!isFull)
		{
			*in = elem; //schreiben an die stelle auf die in zeigt das element
			//in verschieben
			moveIn();
		}
		
		//wecken der wartenden prozesse
		bool toWake = true;
		while (toWake)
		{
			Activity* sleeping = (Activity*) waitList.dequeue();
			if (sleeping != 0)
			{
				sleeping->wakeup();
			}
			else 
			{
				toWake = false;
			}
		}
	}

	/** Diese Methode wird von Prozessen aufgerufen, um Daten aus dem
	 *  Puffer zu lesen. Ist dieser leer wird der lesende Prozess schlafen
	 *  gelegt. Achtet hier besonders auf die Synchronisierung.
	 */
	T get()
	{
		IntLock lock; //aendern von pointern

		while (isEmpty)
		{
			//lesenden prozess schlafen legen und merken
			Activity* running = (Activity*) scheduler.active();
			waitList.enqueue(running);
			running->sleep();
		}

		T elem;
		elem = *out; //lesen das elem was an out steht

		//out verschieben
		moveOut();

		return elem;
	}

private:
	T buffer[size];
	/*volatile*/ T* in;  //naechstes zu schreibender Platz
	/*volatile*/ T* out; //naechstes zu lesendes element

	volatile bool isEmpty;
	volatile bool isFull;

	T* startArray = buffer;
	T* endArray   = buffer + size - 1;
	
	Queue waitList;//queue fuer prozesse die aufgeweckt werden muessen


	//prueft ob in und out pointer gleich sind
	bool isEqual()
	{
		if (in == out)
		{
			return true;
		}

		return false;
	}

	//verschiebt den in pointer beim schreiben in den puffer
	//gehen davon aus das wir in den puffer schreiben koennen (nicht voll)
	void moveIn() 
	{
		//falls der puffer leer war ist er es jetzt nicht mehr
		if (isEqual()) isEmpty = false;

		//in verschieben
		if (in == endArray) //falls in auf die letzte stelle im array zeigt
		{
			in = startArray; //setze in auf den anfang des arrays
		}
		else
		{
			in += 1; //sonst eins nach rechts verschieben
		}

		//pruefen ob der puffer jetzt voll ist
		if (isEqual()) isFull = true;
	}

	//verschiebt den out pointer beim lesen aus dem puffer
	//gehen davon aus das der puffer nicht leer ist
	void moveOut()
	{
		//falls der puffer voll war ist er es jetzt nicht mehr
		if (isEqual()) isFull = false;

		//out verschieben
		if (out == endArray) //falls out auf die letzte stelle im array zeigt
		{
			out = startArray; //setze in auf den anfang des arrays
		}
		else
		{
			out += 1; //sonst eins nach rechts verschieben
		}

		//pruefen ob der puffer jetzt leer ist
		if (isEqual()) isEmpty = true; 
	}
};

#endif
