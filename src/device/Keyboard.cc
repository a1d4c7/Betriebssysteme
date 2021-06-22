#include "device/Keyboard.h"

#include "device/PIC.h"
#include "interrupts/InterruptVector.h"


Keyboard::Keyboard() :
					Gate(KeyboardInterrupt),
					dataPort(DATA),
					ctrlPort(CTRL)
{
	mode = 0;
	setLed(SCROLL_LOCK_LED,false);
	setLed(NUM_LOCK_LED,false);
	setLed(CAPS_LOCK_LED,false);
	setRepeatRate(0,0);

	pic.enable(PIC::KEYBOARD);
}

void Keyboard::handle()
{
	if(ctrlPort.read() & AUX_BIT){
		//behandle hier die Maus
	}else{
		scanCode = dataPort.read();
		analyzeScanCode();
	}
	pic.ack(PIC::KEYBOARD);
}


Key Keyboard::read()
{
	return buffer.get();
}

int Keyboard::read(char* data, int size)
{
	int count = 0;
	while(count<size){
		Key tmp = buffer.get();
		if(tmp.isAscii()){
			data[count++]=tmp.getValue();
			if(tmp.getValue() == '\n'){
				break;
			}
		}
	}
	return count;
}

void Keyboard::analyzeScanCode()
{
	if(	(mode & (CTRL_LEFT | ALT_LEFT)) &&
		(scanCode == CodeTable::DEL)){
			reboot();
	}
	if(scanCode == PREFIX1 || scanCode == PREFIX2){
		prefix = scanCode;
		return;
	}
	if(scanCode & BREAK_BIT){
		keyReleased();
	}else{
		keyHit();
	}
	prefix = 0;
}

void Keyboard::keyReleased()
{
	scanCode &= ~BREAK_BIT;     // Der Break Code einer Taste ist gleich dem
	                    // Make Code mit gesetzten break_bit.
	switch (scanCode)
	{
		case CodeTable::CTRL:
			mode &= ~((prefix == PREFIX1)?CTRL_RIGHT:CTRL_LEFT);
			break;
		case CodeTable::SHIFT_LEFT:
			mode &= ~SHIFT_LEFT;
			break;
		case CodeTable::SHIFT_RIGHT:
	 		mode &= ~SHIFT_RIGHT;
			break;
		case CodeTable::ALT:
	 		mode &= ~((prefix == PREFIX1)?ALT_RIGHT:ALT_LEFT);
			break;
	 }
}

void Keyboard::keyHit()
{
	switch (scanCode)
	{
		case CodeTable::CTRL:
			mode |= (prefix == PREFIX1)?CTRL_RIGHT:CTRL_LEFT;
			break;
		case CodeTable::SHIFT_LEFT:
			mode |= SHIFT_LEFT;
			break;
		case CodeTable::SHIFT_RIGHT:
			mode |= SHIFT_RIGHT;
			break;
		case CodeTable::ALT:
	 		mode |= (prefix == PREFIX1)?ALT_RIGHT:ALT_LEFT;
			break;
		case CodeTable::CAPS_LOCK:
			mode = mode xor CAPS_LOCK; //toggling
			setLed(CAPS_LOCK_LED,(mode & CAPS_LOCK));
			break;
		case CodeTable::SCROLL_LOCK:
			mode = mode xor SCROLL_LOCK; //toggling
			setLed(SCROLL_LOCK_LED,(mode & SCROLL_LOCK));
			break;
		case CodeTable::NUM_LOCK: // Numlock oder Pause ?
			if (mode & CTRL_LEFT){  // Pause Taste
		  		// Auf alten Tastaturen konnte die Pause-Funktion wohl nur
		  		// ueber Ctrl+NUM_LOCK erreicht werden. Moderne MF-II Tastaturen
		  		// senden daher diese Codekombination.
				determineAsciiCode();
			} else  {
				mode = mode xor NUM_LOCK;
				setLed(NUM_LOCK_LED,(mode & NUM_LOCK));
			}
			break;

		default: // alle anderen Tasten
			// ASCII Codes aus den entsprechenden Tabellen auslesen, fertig.
			determineAsciiCode();
	}
}

void Keyboard::determineAsciiCode()
{
	Key key;
	if(codeTable.isControl(scanCode)){
		if ((mode & NUM_LOCK) && !prefix && scanCode>=71 && scanCode<=83) {
			// Anhand der Modifierbits muss die richtige Tabelle ausgewaehlt
			// werden. Der Einfachheit halber hat NUM_LOCK Vorrang vor Alt,
			// Shift und CAPS_LOCK. Fuer Ctrl gibt es keine eigene Tabelle.

			// Bei eingeschaltetem NUM_LOCK und der Betaetigung einer der
			// Tasten des separaten Ziffernblocks (Codes 71-83), sollen
			// nicht die Scancodes der Cursortasten, sondern ASCII und
			// Scancodes der ensprechenden Zifferntasten geliefert werden.
			// Die Tasten des Cursorblocks (prefix == prefix1) sollen
			// natuerlich weiterhin zur Cursorsteuerung genutzt werden
			// koennen. Sie senden dann uebrigens noch ein Shift, aber das
			// sollte nicht weiter stoeren.
			key.setAscii(codeTable.numblockAscii[scanCode-71]);
       	} else {
			key.setControl(scanCode);
		}
	}else if (scanCode == 53 && prefix == PREFIX1) { // Divisionstaste des Ziffernblocks
		// Sonderfall Scancode 53: Dieser Code wird sowohl von der Minustaste
		// des normalen Tastaturbereichs, als auch von der Divisionstaste des
		// Ziffernblocks gesendet. Damit in beiden Faellen ein Code heraus-
		// kommt, der der Aufschrift entspricht, muss im Falle des Ziffern-
		// blocks eine Umsetzung auf den richtigen Code der Divisionstaste
		// erfolgen.
		key.setAscii('/');
	} else if ((mode & NUM_LOCK) && !prefix && scanCode==76){
		key.setAscii(codeTable.numblockAscii[scanCode-71]);
	} else if (mode & ALT_RIGHT) {
		key.setAscii(codeTable.altAscii[scanCode]);

	} else if (mode & (SHIFT_LEFT | SHIFT_RIGHT)) {
		key.setAscii(codeTable.shiftAscii[scanCode]);
	} else if (mode & CAPS_LOCK) { // Die Umschaltung soll nur bei Buchstaben gelten
		if ((scanCode>=16 && scanCode<=26) ||
			(scanCode>=30 && scanCode<=40) ||
			(scanCode>=44 && scanCode<=50)) {
			key.setAscii(codeTable.shiftAscii[scanCode]);
		} else {
			key.setAscii(codeTable.normalAscii[scanCode]);
		}
	} else {
		key.setAscii(codeTable.normalAscii[scanCode]);
	}
	if(key.getValue()){
		buffer.add(key);
	}
}

/** Fuehrt einen Neustart des Rechners durch. Ja, beim PC macht
 * das der Tastaturcontroller.
 */
void Keyboard::reboot ()
{
	// Dem BIOS mitteilen, dass das Reset beabsichtigt war
	// und kein Speichertest durchgefuehrt werden muss.
	*(unsigned short*) 0x472 = 0x1234;

	waitForWrite();
	ctrlPort.write (RESET_CODE);     // Reset auslösen
}


/* Funktion zum Einstellen der Wiederholungsrate der
 * Tastatur. delay bestimmt, wie lange eine Taste ge-
 * drueckt werden muss, bevor die Wiederholung einsetzt.
 * Erlaubt sind Werte zwischen 0 (minimale Wartezeit)
 * und 7 (maximale Wartezeit). speed bestimmt, wie
 * schnell die Tastencodes aufeinander folgen soll.
 * Erlaubt sind Werte zwischen 0 (sehr schnell) und 31
 * (sehr langsam).
 */
void Keyboard::setRepeatRate(int speed, int delay)
{
	pic.disable (PIC::KEYBOARD);

	dataPort.write (SET_SPEED);    // Kommando an die Tastatur

	waitForRead();
	int reply = dataPort.read ();

	if(reply & ACKNOWLEDGE)             // ok
	{
		dataPort.write (((delay & 0x3) << 5) | (speed & 0x1f));   // Parameter

		waitForRead();
		reply = dataPort.read ();
	}

	pic.enable (PIC::KEYBOARD);
}


/** setzt oder loescht die angegebene Leuchtdiode
 */
void Keyboard::setLed(char led, bool on)
{
	pic.disable (PIC::KEYBOARD);

	dataPort.write(SET_LED);       // Kommando an die Tastatur

	waitForRead();
	int reply = dataPort.read();                // Antwort entgegennehmen

	if(reply & ACKNOWLEDGE) {             // ok
		if (on){
			 leds |= led;
		}else{
			 leds &= ~led;
		}

		dataPort.write (leds);              // Parameter

		waitForRead();
		reply = dataPort.read ();           // Antwort entgegennehmen
	}
	pic.enable (PIC::KEYBOARD);
}

void Keyboard::waitForRead()
{
	int status;
	do {
		status = ctrlPort.read();
	} while ((status & OUTPUT_BIT) == 0);
}

void Keyboard::waitForWrite()
{
	int status;
	do {
		status = ctrlPort.read ();  // warten, bis das letzte Kommando
	} while (status & INPUT_BIT);   	// verarbeitet wurde.
}

