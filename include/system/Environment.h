#ifndef SystemEnvironment_h
#define SystemEnvironment_h

#include "device/CgaChannel.h"
#include "device/Clock.h"
#include "device/CPU.h"
#include "device/PIC.h"
#include "device/PIT.h"
#include "device/Keyboard.h"
#include "io/PrintStream.h"
#include "sync/Monitor.h"
#include "thread/ActivityScheduler.h"
#include "system/Console.h"

extern CPU cpu;
extern Console console;
extern Monitor monitor;
extern PIC pic;
extern PIT pit;
extern Clock clock;
extern Keyboard keyboard;
extern CgaChannel screen;
extern PrintStream out;
extern ActivityScheduler scheduler;

#endif

