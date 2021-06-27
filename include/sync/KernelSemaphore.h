#ifndef KernelSemaphore_h
#define KernelSemaphore_h

#include "lib/Queue.h"

/**
 * KernelSemaphore: Semaphorenimplementation f�r kooperative
 * Prozesse oder zur Anwendung innerhalb des Kernels.
 */
class KernelSemaphore {
public:
	// Initialisierung des Zaehlers
	KernelSemaphore(int count = 1)
	{
		counter = count;
	}

	void wait();
	void signal();

private:
	volatile int counter;
	Queue waiting;

};

#endif

