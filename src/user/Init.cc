#include "user/Init.h"
#include "user/Background.h"
#include "user/Hello.h"
#include "user/Environment.h"
#include "sync/Monitor.h"

// die Stacks fuer unsere Threads
static unsigned stack0[1024];
static unsigned stack1[1024];
static unsigned stack2[1024];
static unsigned stack3[1024];


// Hier startet das Hauptprogramm der Applikation!

void Init::run()
{
	console.attach();
	out.println("Application::body() is running\n");
	console.detach();

	monitor.enter();
	Hello anton("Anton", 10, 1, &stack0[1024]);
	Hello berta("Berta", 10, 1, &stack1[1024]);
	Background bg(&stack3[1024], 3000);
	Hello caesar("Caesar", 3, 1, &stack2[1024]);
	monitor.leave();

	console.attach();
	out.println("Application::body() threads created!\n");
	console.detach();
}

