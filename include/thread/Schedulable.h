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
 *	Gegenwaertig brauchen wir diese Informationen
 *	aber noch nicht und die Klasse ist deshalb vorlaeufig leer.
 *
 */

#include "lib/Chain.h"

class Schedulable: public Chain {
public:

private:
};

#endif
