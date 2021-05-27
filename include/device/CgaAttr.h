#ifndef CgaAttr_h
#define CgaAttr_h

/*
 * CgaAttr: 	Softwareprototyp fuer CGA Darstellungsattribute
 *		Hier braucht man Bitoperationen!
 *
 *		Da *alle* Operationen sehr einfach und kurz sind,
 *		duerft Ihr sie direkt in der Klasse
 *		als inline Methoden deklarieren.
 */

class CgaAttr {
private:
	enum AttrMaskAndShifts {
		MASK_FOREGROUND = 0b00001111, // 4 bits foreground 0-3
		MASK_BACKGROUND = 0b01110000, // 3 bits background 4-6
		MASK_BLINKSTATE = 0b10000000, // 1 bits blinkstate 7
		
		SHIFT_FOREGROUND = 0,
		SHIFT_BACKGROUND = 4,
		SHIFT_BLINKSTATE = 7
	};	
	
public:
	/** 	Diese Aufz�hlung enth�lt die CGA-Farben als Farbkonstanten
	 *	Tragt hier *alle* CGA Farben mit den richtigen Werten ein
	 */
	enum Color {
		BLACK           = 0b000, 
        BLUE            = 0b001, 
        GREEN           = 0b010, 
        CYAN            = 0b011, 
        RED             = 0b100,
        MAGENTA         = 0b101, 
        BROWN           = 0b110, 
        LIGHT_GRAY      = 0b111, 
        GRAY            = 0b1000, 
        LIGHT_BLUE      = 0b1001,   
        LIGHT_GREEN     = 0b1010,
        LIGHT_CYAN      = 0b1011,
        LIGHT_RED       = 0b1100, 
        LIGHT_MAGENTA   = 0b1101, 
        YELLOW          = 0b1110, 
        WHITE           = 0b1111 
	};


	/** Konstruktor. Erzeugt ein CgaAttr-Objekt mit den uebergebenen Werten f�r
	  * Vorder- und Hintergrundfarbe. Werden keine Parameter uebergeben,
	  * so werden die Defaultwerte (Vordergrund weiss, Hintergrund schwarz, Blinken deaktiviert)
	  * verwendet.
	  */
	CgaAttr(Color fg=WHITE, Color bg=BLACK, bool blink=false)
	{
		foreground = fg;
		background = bg;
		blinkState = blink;
	}

	// setzen der Schriftfarbe
	void setForeground(Color col)
	{
		foreground = col;
	}

	// setzen der Hintergrundfarbe
	void setBackground(Color col)
	{
		background = col;
	}

	// setzen blinkender/nicht blinkender Text
	void setBlinkState(bool blink)
	{
		blinkState = blink;
	}

	// setzen aller Attribute
	void setAttr(CgaAttr attr)
	{
		foreground = attr.foreground;
		background = attr.background;
		blinkState = attr.blinkState;
	}

	// ermitteln der Schriftfarbe
	Color getForeground()
	{
		return foreground;
	}

	// ermitteln der Hintergrundfarbe
	Color getBackground()
	{
		return background;
	}

	// ermitteln ob Blink-Flag gesetzt ist
	bool getBlinkState()
	{
		return blinkState;
	}

	//Erstellt aus den einzelnen Attributwerten das Attribut-Byte
	char createCgaAttrByte() 
	{
		unsigned char fg = MASK_FOREGROUND & ((0xff & getForeground()) << SHIFT_FOREGROUND);
		unsigned char bg = MASK_BACKGROUND & ((0xff & getBackground()) << SHIFT_BACKGROUND);
		unsigned char bs = MASK_BLINKSTATE & ((0xff & getBlinkState()) << SHIFT_BLINKSTATE);

		return (fg | bg | bs);
	}

	void findAttributes(unsigned char a) 
	{
		findForegroundColor((a & MASK_FOREGROUND) >> SHIFT_FOREGROUND);
		findBackgroundColor((a & MASK_BACKGROUND) >> SHIFT_BACKGROUND);
		findBlinkState((a & MASK_BLINKSTATE) >> SHIFT_BLINKSTATE);
	}

	void findForegroundColor(unsigned char a) 
	{
		switch (a)
		{
			case BLACK: 
				setForeground(BLACK); 
				break;          
			case BLUE: 
				setForeground(BLUE); 
				break;
			case GREEN: 
				setForeground(GREEN); 
				break;
			case CYAN: 
				setForeground(CYAN); 
				break;
			case RED: 
				setForeground(RED);
				break;
			case MAGENTA: 
				setForeground(MAGENTA); 
				break;
			case BROWN: 
				setForeground(BROWN); 
				break;
			case LIGHT_GRAY: 
				setForeground(LIGHT_GRAY); 
				break;
			case GRAY: 
				setForeground(GRAY);
				break;
			case LIGHT_BLUE: 
				setForeground(LIGHT_BLUE); 
				break;
			case LIGHT_GREEN: 
				setForeground(LIGHT_GREEN); 
				break;
			case LIGHT_CYAN: 
				setForeground(LIGHT_CYAN); 
				break;
			case LIGHT_RED: 
				setForeground(LIGHT_RED); 
				break;
			case LIGHT_MAGENTA: 
				setForeground(LIGHT_MAGENTA); 
				break;
			case YELLOW: 
				setForeground(YELLOW); 
				break;
			case WHITE: 
				setForeground(WHITE); 
				break;
			
			default:
				break;
		}
		
	}

	void findBackgroundColor(unsigned char a) 
	{
		switch (a)
		{
			case BLACK: 
				setBackground(BLACK); 
				break;          
			case BLUE: 
				setBackground(BLUE); 
				break;
			case GREEN: 
				setBackground(GREEN); 
				break;
			case CYAN: 
				setBackground(CYAN); 
				break;
			case RED: 
				setBackground(RED);
				break;
			case MAGENTA: 
				setBackground(MAGENTA); 
				break;
			case BROWN: 
				setBackground(BROWN); 
				break;
			case LIGHT_GRAY: 
				setBackground(LIGHT_GRAY); 
				break;
			default:
			break;
		}
	}

	void findBlinkState(unsigned char a) 
	{
		if (a == 1)
		{
			setBlinkState(true);
		} else {
			setBlinkState(false);
		}
	}

private:

	Color foreground;
	Color background;
	bool blinkState;
};

#endif
