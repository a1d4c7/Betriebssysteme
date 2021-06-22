#include "device/PIC.h"

void PIC::enable (int num)
{
	if (num < 8) // PIC 1
		imr1.write (imr1.read () & (~(1 << num)));
	else         // PIC 2
		imr2.write (imr2.read () & (~(1 << (num-8))));
}


void PIC::disable (int num)
{
	if (num < 8) // PIC 1
		imr1.write (imr1.read () | (1 << num));
	else         // PIC 2
		imr2.write (imr2.read () | (1 << (num-8)));
}

void PIC::ack (int num)
{
	ack();
}

void PIC::ack ()
{
	ctrl1.write (ACK); // Unspez. EOI-Befehl an PIC 1
	ctrl2.write (ACK); // Unspez. EOI-Befehl an PIC 2
}
