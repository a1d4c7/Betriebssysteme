#ifndef BoundedBuffer_h
#define BoundedBuffer_h


/** Diese Klasse stellt einen begrenzten synchronisierten
 *  Puffer dar, welcher von Interruptbehandlungsroutinen
 *  gefüllt werden kann.
 *
 *  Die Klasse ist eine Templateklasse. Das bedeutet für euch
 *  erstmal nur, das ihr alle Methoden hier im Header implementieren
 *  müsst.
 */
template<typename T,unsigned size>
class BoundedBuffer {
public:

	BoundedBuffer()
	{
	}

	/** Diese Methode wird vom Interrupthandler aufgerufen, um
	 *  ein etwas in den Puffer zu schreiben. Ist der Puffer voll,
	 *  werden die zu schreibenden Daten verworfen.
	 *  Prozesse die auf eine Eingabe warten müssen hier geweckt werden.
	 */
	void add(T& elem)
	{
	}

	/** Diese Methode wird von Prozessen aufgerufen, um Daten aus dem
	 *  Puffer zu lesen. Ist dieser leer wird der lesende Prozess schlafen
	 *  gelegt. Achtet hier besonders auf die Synchronisierung.
	 */
	T get()
	{
	}

private:
	T buffer[size];
};

#endif

