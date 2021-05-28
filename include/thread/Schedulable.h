#ifndef Schedulable_h
#define Schedulable_h

/*
 * Schedulable: Diese Klasse implementiert ein Element
 *		der Ready-Liste des Schedulers
 *
 *	Anmerkung: Die Klasse ist von Chain abgeleitet,
 *	damit Instanzen dieser Klasse verkettet werden koennen.
 *	Hier wuerden typischerweise Informationen
 *	wie prozesspezifische Laufzeitstatistiken,
 *	Prioritaeten etc. verwaltet werden.
 *
 */

#include "lib/Chain.h"

class Schedulable: public Chain {
public:
	explicit Schedulable(int slice = 1)
	{ 
		quantum(slice);
		setTicks(0); 
	}

	//setzt das zeit maximum
	void quantum(int slice)
	{ 
		this->slice = slice;
	}

	//returned das zeit maximum
	int quantum()
	{ 
		return slice;
	}

	//adds one to tick count
	void tick()
	{
		ticks += 1;
	}

	//sets tick count
	void setTicks(int i)
	{
		this->ticks = i;
	}

	//returns current tick count
	int getTicks()
	{
		return ticks;
	}

private:
	//maximal moegliche zeit
	int slice;

	//aktuelle zeit
	int ticks;
};

#endif
