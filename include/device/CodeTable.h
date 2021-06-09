#ifndef CodeTable_h
#define CodeTable_h

/** Die Code Tabelle beschreibt die Umsetzung von Scancodes der Tastatur
 *  auf ASCII-Zeichen. Weiterhin wird festgelegt welche Scancodes als
 *  Steuerzeichen betrachtet werden, und nicht in ein ASCII-Zeichen
 *  umgesetzt werden.
 */
struct CodeTable {
public:

	/** Hier werden Zeichen definiert, welche nicht zu einem AsciiZeichen
	 *  umgewandelt werden sollen, da sie als Steuerzeichen dienen.
	 */
	enum {
		CTRL 		= 29,
		SHIFT_LEFT 	= 42,
		SHIFT_RIGHT 	= 54,
		ALT 		= 56,
		CAPS_LOCK 	= 58,
		NUM_LOCK 	= 69,
		SCROLL_LOCK 	= 70,
		POS1 		= 71,
		UP 		= 72,
		PAGE_UP 	= 73,
		LEFT 		= 75,
		RIGHT 		= 77,
		END 		= 79,
		DOWN 		= 80,
		PAGE_DOWN 	= 81,
		INS 		= 82,
		DEL 		= 83
	};

	CodeTable()
	{
		lookup[CTRL] = true;
		lookup[SHIFT_LEFT] = true;
		lookup[SHIFT_RIGHT] = true;
		lookup[ALT] = true;
		lookup[CAPS_LOCK] = true;
		lookup[NUM_LOCK] = true;
		lookup[SCROLL_LOCK] = true;
		lookup[POS1] = true;
		lookup[UP] = true;
		lookup[PAGE_UP] = true;
		lookup[LEFT] = true;
		lookup[RIGHT] = true;
		lookup[END] = true;
		lookup[DOWN] = true;
		lookup[PAGE_DOWN] = true;
		lookup[INS] = true;
		lookup[DEL] = true;
	}

	static bool isControl(unsigned char scanCode)
	{
		return lookup[scanCode];
	}

	static const unsigned char normalAscii[];
	static const unsigned char shiftAscii[];
	static const unsigned char strgAscii[];
	static const unsigned char altAscii[];
	static const unsigned char numblockAscii[];

private:
	static bool lookup[];
};

#endif

