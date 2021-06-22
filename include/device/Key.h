#ifndef Key_h
#define Key_h

/** Die Klasse Key beschreibt ein logisches Zeichen,
 *  das heiﬂt ein ASCII-Zeichen oder ein Steuerzeichen.
 */
class Key {
public:
	enum Type {
		CTRL,
		ASCII
	};

	/** Diese Methode initialisiert das Zeichen als Ascii-Zeichen.
	 */
	void setAscii(unsigned char ascii)
	{
		type = ASCII;
		value = ascii;
	}

	/** Diese Methode initialisiert das Zeichen als Steuerzeichen.
	 */
	void setControl(unsigned char control)
	{
		type = CTRL;
		value = (unsigned char)control;
	}

	char getValue()
	{
		return value;
	}

	bool isAscii()
	{
		return type==ASCII;
	}

private:
	Type type;
	unsigned char value;
};

#endif

