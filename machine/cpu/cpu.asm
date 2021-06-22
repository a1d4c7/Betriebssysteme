;*****************************************************************************
;* Betriebssysteme I, Uni-Magdeburg, SS 98, OO-Stubs                         *
;* Betriebssysteme I, BTU-Cottbus, SS 10
;*---------------------------------------------------------------------------*
;*                                                                           *
;*                                   C P U                                   *
;*                                                                           *
;*---------------------------------------------------------------------------*
;* Dieses Assembler-Modul unterstuetzt die Klasse CPU.                       *
;*****************************************************************************

; INCLUDES

%include "../machine/csym.inc"  ; Innerhalb des Include-Files 'csym.m4'
                                ; wird das Macro CSYM(name) definiert,
                                ; das dem uebergebenen Symbolnamen in
                                ; Abhaegigkeit vom verwendeten Generierungs-
                                ; system einen Unterstrich ('_') voranstellt.

; EXPORTIERTE FUNKTIONEN

csym int_enable
csym int_disable
csym cpu_halt
csym get_cr2

[GLOBAL int_enable]
[GLOBAL int_disable]
[GLOBAL cpu_halt]
[GLOBAL get_cr2]

; IMPLEMENTIERUNG DER FUNKTIONEN

[SECTION .text]

; INT_ENABLE: Erlauben von (Hardware-)Interrupts
;
;       C-Prototyp: void int_enable ();

int_enable:
	sti
	ret

; INT_DISABLE: Interrupts werden ignoriert/verboten
;
;       C-Prototyp: unsigned int_disable (); flags zurueck

int_disable:
	pushfd
	cli
	pop	eax
	and 	eax, 0x200  ; Maskieren mit InterrupFlag (IF) Bit 9
	ret

; CPU_HALT : Haelt den Prozessor an.
;
; C Prototyp: void cpu_halt (void)

cpu_halt:
	hlt
	ret

; GET_CR2 : Liefert den Wert des CR2 Registers
;
; C Prototyp: void* get_cr2 (void)
get_cr2:
    push    ebp
    mov     ebp, esp
    mov     eax, cr2
    pop     ebp
    ret
