#ifndef InterruptVector_h
#define InterruptVector_h

enum InterruptVector {
	Panic 			= -1,
	PageFault 		= 14,
	Timer 			= 32,
	KeyboardInterrupt 	= 33,
	SpuriousInterrupt	= 39,
	NrOfInterrupts 		= 64
};

#endif

