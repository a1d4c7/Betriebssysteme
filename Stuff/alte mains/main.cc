#include "device/CgaChannel.h"
#include "io/PrintStream.h"

//der Wert sollte variiert werden oder man bastelt sich lieber eine rein "zeitabhängige" Pause ;)
#define PAUSE 50000


CgaChannel cga;        // unser CGA-Ausgabekanal
PrintStream out(cga);    // unseren PrintStream mit Ausgabekanal verknuepfen

int main()
{
/*
  out.printBlink();
  out.println();
  for(int i = 0; i < PAUSE; i++){
    out.print("\r|\r\\\r-\r/");
  }
    cga.clear();
*/
    out.println("Test der formatierten Ausgabe zur Basis:");

    for(int i = -30; i < 30; i++)
    {
        if (i % 6 == 0)
        {
            out.print("Dezimal: ");
            out.print(i);
            out.print(" ; Binaer: ");
            out.print(i, 2);
            out.print(" ; Hexadezimal: ");
            out.print(i, 16);
            out.println();
        }
    }

    out.println();
    out.print("Test mit falscher Basis: out.print(133,7): ");
    out.print(133, 7);
    out.println();
    out.print("Test mit falscher Basis: out.print(133,1): ");
    out.print(133, 1);
    out.println();
    out.print("Test mit falscher Basis: out.print(133,0): ");
    out.print(133, 0);
    out.println();
    out.print("Test mit falscher Basis: out.print(133,-2): ");
    out.print(133, -2);
    out.println();
    out.print("Test mit falscher Basis: out.print(133,120): ");
    out.print(133, 120);
    out.println();

    out.println();
    out.println("Es folgen alle Farbkombinationen:");
    for(int blink = 0; blink < 2; blink++)
    {
        for(int bg = 0; bg < 8; bg++)
        {
            for(int fg = 0; fg < 16; fg++)
            {
                cga.setAttr(CgaAttr((CgaAttr::Color) (fg), (CgaAttr::Color) (bg), (CgaAttr::Color) blink));
                out.print("X");
            }
        }
    }

    out.println("\n");
    //kurze Pause
    for(int i = 0; i < PAUSE; i++)
    {
        out.print("\r|\r\\\r-\r/");
    };

    //~ int i = 0;
	bool sharpBlink = false;
	CgaAttr attr;

	cga.clear();
	cga.setAttr(CgaAttr((CgaAttr::Color) CgaAttr::WHITE, (CgaAttr::Color) CgaAttr::BLACK, (CgaAttr::Color) false));
	out.println();
	out.println("Hier Bildschirm sollten im unteren Bereich bunte Spalten erscheinen. Bei diesen sollten jeweils im Wechsel acht Spalten ohne und acht Spalten mit dem #-Zeichen versehen sein. Darueber hinaus sollten diese kaskadierend blinken. Das Bild muss mit einer schwarzen Spalte beginnen.");
	out.println();


	for (int k = 0; k < ((19 * 80) -1); k++) {

		attr.setBlinkState(sharpBlink);
		sharpBlink = not sharpBlink;

		switch (k % 16) {
			case 0:
				attr.setForeground(attr.BLACK);
				attr.setBackground(attr.BLACK);
				break;
			case 1:
				attr.setForeground(attr.BLUE);
				attr.setBackground(attr.BLUE);
				break;
			case 2:
				attr.setForeground(attr.GREEN);
				attr.setBackground(attr.GREEN);
				break;
			case 3:
				attr.setForeground(attr.CYAN);
				attr.setBackground(attr.CYAN);
				break;
			case 4:
				attr.setForeground(attr.RED);
				attr.setBackground(attr.RED);
				break;
			case 5:
				attr.setForeground(attr.MAGENTA);
				attr.setBackground(attr.MAGENTA);
				break;
			case 6:
				attr.setForeground(attr.BROWN);
				attr.setBackground(attr.BROWN);
				break;
			case 7:
				attr.setForeground(attr.LIGHT_GRAY);
				attr.setBackground(attr.LIGHT_GRAY);
				break;
			case 8:
				attr.setForeground(attr.GRAY);
				attr.setBackground(attr.GRAY);
				break;
			case 9:
				attr.setForeground(attr.LIGHT_BLUE);
				attr.setBackground(attr.LIGHT_BLUE);
				break;
			case 10:
				attr.setForeground(attr.LIGHT_GREEN);
				attr.setBackground(attr.LIGHT_GREEN);
				break;
			case 11:
				attr.setForeground(attr.LIGHT_CYAN);
				attr.setBackground(attr.LIGHT_CYAN);
				break;
			case 12:
				attr.setForeground(attr.LIGHT_RED);
				attr.setBackground(attr.LIGHT_RED);
				break;
			case 13:
				attr.setForeground(attr.LIGHT_MAGENTA);
				attr.setBackground(attr.LIGHT_MAGENTA);
				break;
			case 14:
				attr.setForeground(attr.YELLOW);
				attr.setBackground(attr.YELLOW);
				break;
			case 15:
				attr.setForeground(attr.WHITE);
				attr.setBackground(attr.WHITE);
				break;
		}
		cga.setAttr(attr);
		out.print('#');
	}

	attr.setForeground(attr.WHITE);
	attr.setBackground(attr.BLACK);
	attr.setBlinkState(false);
	cga.setAttr(attr);

    for(int i = 0; i < PAUSE; i++)
    {
        out.print("\r|\r\\\r-\r/");
    };

    cga.setAttr(CgaAttr());
    cga.clear();
    cga.setAttr(CgaAttr(CgaAttr::RED, CgaAttr::YELLOW, false));
    for(int i = 0; i < 19; i++)
    {
	    cga.setCursor(i, (i < 9)?i:(18-i));
        out.println("x");

        cga.setCursor(i+19, (i < 9)?i:(18-i));
        out.println("x");

        cga.setCursor(i+38, (i < 9)?i:(18-i));
        out.println("x");

        cga.setCursor(i+57, (i < 9)?i:(18-i));
        out.println("x");
    }
    cga.setCursor(0,11);
    cga.setAttr(CgaAttr());

    out.println("Test der Sonderzeicheninterpretation:");
    out.println("Hier stehen jetzt fuenf Worte\nund auf der naechsten Zeile geht es weiter.\nHier wird gleich \"Hier\" ueberschrieben");


    //kurze Pause zum Test
    for(int i = 0; i < PAUSE; i++)
    {
        out.print("\r|\r\\\r-\r/");
    };

    out.print("\r ");

	int row, column;
	cga.getCursor(column, row);
	cga.setCursor(column,row - 1);
    cga.setAttr(CgaAttr(CgaAttr::GREEN, CgaAttr::BLUE, false));

    out.println("\rDort\n");

    out.println("Das ist ein Testsatz, der laenger als 80 Zeichen sein soll. Mal sehen, ob der Zeilenumbruch klappt. Haha Haha Haha Haha Haha Haha Haha Haha.\n");

    out.println("Gleich wird das Scrollen getestet. Das Scrollen sollte uebrigens mit der selber zu schreibenden memcpy-Methode geloest werden - Zusatzaufgabe (und nicht mit einer einfachen Zuweisung).");
    out.println("\n");
    //kurze Pause

    for(int i = 0; i < PAUSE; i++)
    {
        out.print("\r|\r\\\r-\r/");
    };

    for (int i = 0; i < 40; i++)
    {
        cga.setAttr(CgaAttr((CgaAttr::Color) (i % 16), (CgaAttr::Color) (8), (CgaAttr::Color) false));
        out.print("Gleich wird das Scrollen getestet. Das Scrollen sollte uebrigens mit der selber zu schreibenden memcpy-Methode geloest werden - Zusatzaufgabe (und nicht mit einer einfachen Zuweisung).");
        for(int j = 0; j < 5000000; j++){

        }
    };

    for(int i = 0; i < PAUSE; i++)
    {
        out.print("\r|\r\\\r-\r/");
    };

    cga.blueScreen("Damn Fucking Error\n I hope that will never happen again\n\n BLUBB \n");

    for(int i = 0; i < PAUSE; i++)
    {
        out.print("\r|\r\\\r-\r/");
    };

    cga.clear();
    cga.setAttr(CgaAttr(CgaAttr::WHITE, CgaAttr::BLACK, false));
    out.println("\n\nSonderzeichentest:\näöü;,:.-_");

    out.println();

    out.println("Ausgabe von Adressen...");
    out.println("Wie weit liegen sie auseinander? Warum?");
    int x = 5;
    int y = 6;
    out.print("x: ");
    out.print(&x);
    out.print("; y: ");
    out.print(&y);
	out.println("\n");


    out.println("Test von Grenzwerten:");
    unsigned ux = 0;
    out.print("0x0: ");
    out.print(ux, 16);
    out.println();
    ux = 0xFFFFFFFF;
    out.print("0xFFFFFFFF: ");
    out.print(ux, 16);

    out.println("\n");
    out.println("Ende.");
    out.println("\n");


    //kurze Pause
    //~
    for(int i = 0; i < PAUSE; i++)
      //for( ; ; )
    {
        out.print("\r|\r\\\r-\r/");
    };


    for (;;);
    return 0;

    /*
    CgaAttr attr = CgaAttr();
    attr.setBackground(CgaAttr::LIGHT_GRAY);
    attr.setForeground(CgaAttr::CYAN);
    attr.setBlinkState(true);
    attr.setBlinkState(false);
    cga.setAttr(attr);
    out.print("Vordergrund: ");
    out.println((int) attr.getForeground());

    out.print("Hintergrund: ");
    out.println((int) attr.getBackground());

    out.print("Blink: ");
    out.println((int) attr.getBlinkState());
    */
}
