;*****************************************************************************
;* Betriebssysteme I, Uni-Magdeburg, SS 98, OO-Stubs                         *
;*---------------------------------------------------------------------------*
;*                                                                           *
;*                             I O _ P O R T                                 *
;*                                                                           *
;*---------------------------------------------------------------------------*
;* Die hier definierten Funktionen stellen die Maschinebefehle 'in' und      *
;* 'out' fuer die Klasse IO_Port zur Verfuegung.                             *
;*****************************************************************************

; INCLUDES

%include "../machine/csym.inc"  ; Innerhalb des Include-Files 'csym.inc'
				; wird das Macro CSYM(name) definiert,
				; das dem uebergebenen Symbolnamen in
				; Abhaegigkeit vom verwendeten Generierungs-
				; system einen Unterstrich ('_') voranstellt.

; EXPORTIERTE FUNKTIONEN

csym outb
csym outw
csym inb
csym inw

[GLOBAL outb]
[GLOBAL outw]
[GLOBAL inb]
[GLOBAL inw]


; IMPLEMENTIERUNG DER FUNKTIONEN

[SECTION .text]

; OUTB: Byteweise Ausgabe eines Wertes ueber einen I/O-Port.
;
;       C-Prototyp: void outb (int port, int value);

outb:
	push	ebp
	mov	ebp,esp
	mov	edx,[8+ebp]
	mov	eax,[12+ebp]
	out	dx,al
	pop	ebp
	ret


; OUTW: Wortweise Ausgabe eines Wertes ueber einen I/O-Port.
;
;       C-Prototyp: void outw (int port, int value);

outw:
	push	ebp
	mov	ebp,esp
	mov	edx,[8+ebp]
	mov	eax,[12+ebp]
	out	dx,ax
	pop	ebp
	ret


; INB: Byteweises Einlesen eines Wertes ueber einen I/O-Port.
;
;      C-Prototyp: int inb (int port);

inb:
	push	ebp
	mov	ebp,esp
	mov	edx,[8+ebp]
	xor	eax,eax
	in	al,dx
	pop	ebp
	ret


; INW: Wortweises Einlesen eines Wertes ueber einen I/O-Port.
;
;      C-Prototyp: int inw (int port);

inw:
	push	ebp
	mov	ebp,esp
	mov	edx,[8+ebp]
	xor	eax,eax
	in	ax,dx
	pop	ebp
	ret



