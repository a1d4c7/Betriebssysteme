#ifndef KernelLock_h
#define KernelLock_h

#include "sync/Monitor.h"

/**	Diese Klasse dient dazu	innerhalb eines Blockes den Kernel-Monitor
 *	zu sperren. Dabei kann KernelLock auch verschachtelt verwendet
 *	werden.
 */
class KernelLock {
public:
	KernelLock() { lock(); }
	~KernelLock() { unlock(); }

	void lock()
	{
		wasFree = monitor.isFree();
		monitor.enter();
	}

	void unlock()
	{
		if (wasFree)
			monitor.leave();
	}
private:
	bool wasFree; // vorheriger Zustand des Monitors
};

#endif
