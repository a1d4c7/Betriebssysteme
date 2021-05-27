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
	}

	void quantum(int slice)
	{ 
		this->slice = slice;
	}

	int quantum()
	{ 
		return slice;
	}

private:
	int slice;
};

#endif
