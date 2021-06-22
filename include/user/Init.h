#ifndef Init_h
#define Init_h

/** Die erste richtige Anwendung
 */
#include "system/Thread.h"

class Init: public Thread {
 public:
 Init(int slice=1) :
	Thread(slice)
	{
	}
	
	~Init()
		{
			join();
		}
	
	virtual void run();
 private:
};

#endif
