#ifndef Background_h
#define Background_h

#include "system/Thread.h"
#include "user/Environment.h"


// Ein Hintergrundprozess, der einfach mitlaeuft ...

class Background: public Thread {
public:
	Background(void* sp, int show): Thread(sp)
	{
		this->show = show;
		start();
	}

	~Background()
	{
		out.println("Background should be killed now!");
	}

private:
	void run()
	{
		out.println("Background is running!");

		for(int i=0;;i++) {
			if (i % show == 0)
				out.print("*");
			yield();
		}

	}

	int show;
};

#endif
