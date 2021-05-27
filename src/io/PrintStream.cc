#include "io/PrintStream.h"
#include "device/CgaChannel.h"

#include "io/OutputChannel.h"

/*
 * PrintStream:	Diese Klasse ist aehnlich der Java-PrintStream Klasse
 *		Sie konvertiert u.A. numerische Werte in sichtbare Zeichen
 *		und gibt Sie auf dem im Konstruktor spezifizierten
 *		Ausgabekanal aus.
 *		Daraus ergeben sich 2 Teilaufgaben:
 *
 *		1. Die Feststellung der Ziffern einer Zahl
 *		2. Die Umwandlung der Ziffern in darstellbare Zeichen
 *
 *		Man beachte, dass diese Klasse unabhaengig
 *		von dem tatsaechlich verwendeten Ausgabekanal arbeitet.
 *
 *		Anmerkung: Diese Klasse werden wir spaeter noch in
 *		C++ konforme Ausgabe umwandeln.
 */

	

	PrintStream::PrintStream(OutputChannel* chan) : channel(*chan) 
	{
	}

	PrintStream::PrintStream(OutputChannel& chan) : channel(chan)
	{
	}

    	
	void PrintStream::print(const char* str)
	{
		int size = strSizeP(str);
		channel.write(str, size);
	}

	void PrintStream::print(char ch) 
	{
		int size = 1;
		const char* str = (char*) &ch;
		channel.write(str, size);
	}

	// Ausgabe eines Strings mit anschliessendem Zeilenvorschub
	void PrintStream::println(const char* str)
	{
        char c = '\n';
        
        int size = strSizeP(str);
        char newStr [size + 1];

        appendString(str, c, newStr);


		channel.write(newStr, size + 1);
	}

	// Zeilenvorschub
	void PrintStream::println() 
	{
		print('\n');
	}

	// numerische Werte werden zur Basis 'base' Ausgegeben
	// implementiere die Basen 2, 10 und 16
	void PrintStream::print(int x, int base)
	{		
		if (base == 2 || base == 10 || base == 16) 
		{
			if (x < 0) // *-1, - anzeigen
			{
				print('-');
				x = x * (-1);
			}

			int size = countDigits(x, base);
			char str [size];
			
			numberToString((unsigned) x, base, str);

			channel.write(str,size);
		}
		else
		{
			char* str = "Falsche Basis";
			int size = strSizeP(str);
			channel.write(str, size);
		}
		
	}


	void PrintStream::print(unsigned x, int base) 
	{
		int size = countDigits(x, base);
		char str [size];
			
		numberToString(x, base, str);
			
		channel.write(str,size);
	}

	// Zeigertypen werden immer zur Basis 16 ausgegeben!
	void PrintStream::print(void* p)
	{
		print(int(p), 16);
	}

	//brechnet groesse von einem string bis zum nullbyte
	int PrintStream::strSizeP(const char *str)
	{
		int size = 0;
		while (str[size] != '\0')
		{
			size += 1;
		}

		return size;
    
	}

	
	//converts given number to its string representation
	void PrintStream::numberToString(unsigned int number, int base , char* str)
	{
		int digits = countDigits(number, base);
		
		for (int i = 1; i <= digits; i++)
		{
			int remainder = number % base;
			number = number / base;

			char c = getDigitAsChar(remainder);

			str[digits - i] = c;
		}
		
	}


	//brechnet anzahl der stellen einer zahl
	int PrintStream::countDigits(unsigned int number, int base)
	{
		if (number == 0) return 1;

		int digits = 0;
		
		while (number > 0)
		{
			number = number / base;
			digits += 1;				
		}
		

		return digits;
	}
	

	//48 = 0, .... 57 = 9
	//gibt den entsprechenden char wert einer ziffer zurueck (0-9), evtl hex?
	char PrintStream::getDigitAsChar(int n)
	{
		switch (n)
		{
			case 0:
				return '0';		
				break;
			case 1:
				return '1';	
				break;
			case 2:
				return '2';	
				break;
			case 3:
				return '3';	
				break;
			case 4:
				return '4';	
				break;
			case 5:
				return '5';	
				break;
			case 6:
				return '6';	
				break;
			case 7:
				return '7';	
				break;
			case 8:
				return '8';	
				break;
			case 9:
				return '9';	
				break;
			case 10:
				return 'A';	
				break;
			case 11:
				return 'B';	
				break;
			case 12:
				return 'C';	
				break;
			case 13:
				return 'D';	
				break;
			case 14:
				return 'E';	
				break;
			case 15:
				return 'F';	
				break;

			default:
				return ' ';
				break;
		}
	}

	//fuegt ein zeichen an das ende des strings ran, wird als neuer string zurueckgegeben
	void PrintStream::appendString(const char* oldStr, char c, char* newStr)
	{
		int size = strSizeP(oldStr);
		for (int i = 0; i < size + 1; i++)
		{
			if (i < size) 
			{
				newStr[i] = oldStr[i];
			}
			else
			{
				if (i == size) 
				{ 
					newStr[i] = c;
				}
				else
				{
					newStr[i] = '\0';
				}
				
			}
		}
	}