;******************************************************************************
;* Betriebssysteme I, Uni-Magdeburg, SS 97                                    *
;* Betriebssysteme I, BTU-Cottbus, SS 10                                      *
;*----------------------------------------------------------------------------*
;*                                                                            *
;*                        S T A R T U P . A S M                               *
;*                                                                            *
;*----------------------------------------------------------------------------*
;* 'startup' ist der Eintrittspunkt des eigentlichen Systems. Die Umschaltung *
;* in den 'Protected Mode' ist bereits erfolgt. Es wird alles vorbereitet,    *
;* damit so schnell wie moeglich die weitere Ausfuehrung durch C-Code erfol-  *
;* gen kann.                                                                  *
;******************************************************************************

%include "../machine/csym.inc"	; Innerhalb des Include-Files 'csym.m4'
				; wird das Macro CSYM(name) definiert,
				; das dem uebergebenen Symbolnamen in
				; Abhaegigkeit vom verwendeten Generierungs-
				; system einen Unterstrich ('_') voranstellt.

;
;   System
;

csym idt
csym main
csym guardian
csym _init
csym _fini
csym virtualPanic
csym __pure_virtual
csym __cxa_pure_virtual
csym __builtin_delete
csym _ZdlPv
csym __cxa_atexit
csym _alloca


[GLOBAL get_protected]
[GLOBAL idt]
[GLOBAL __builtin_delete]
[GLOBAL __pure_virtual]
[GLOBAL __cxa_pure_virtual]
[GLOBAL _ZdlPv]
[GLOBAL __cxa_atexit]
[GLOBAL _alloca]


[EXTERN main]
[EXTERN guardian]
[EXTERN _init]
[EXTERN _fini]
[EXTERN virtualPanic]
[EXTERN call_ctors]
[EXTERN call_dtors]

[SECTION .init]
MODULEALIGN equ  1<<0                   ; align loaded modules on page boundaries
MEMINFO     equ  1<<1                   ; provide memory map
FLAGS       equ  MODULEALIGN | MEMINFO  ; this is the Multiboot 'flag' field
MAGIC       equ    0x1BADB002           ; 'magic number' lets bootloader find the header
CHECKSUM    equ -(MAGIC + FLAGS)        ; checksum required
 
align 4
MultiBootHeader:
   dd MAGIC
   dd FLAGS
   dd CHECKSUM


[SECTION .text]

get_protected:
    cli
    mov al, 0x80
    out 0x70, al
    lgdt [gdt.pointer]


; GCC-kompilierter Code erwartet das so.

	cld

; Globales Datensegment

	mov	ax,0x10
	mov	ds,ax
	mov	es,ax
	mov	fs,ax
	mov	gs,ax
	mov	ss,ax

    jmp 0x08:startup

startup:

; Stack festlegen
	mov	esp,init_stack+4096

; Unterbrechungsbehandlung sicherstellen

	call	setup_idt
	call	reprogram_pics

; minimales Paging aufsetzen
; es wird eine PageTable mit 1024 Eintraegen erstellt
; bei Page 0 wird das Present-Bit nicht gesetzt, damit es knallt 
; damit haben wir 4MB - 4KB Platz (ab Adresse 0x1000)

    ; page dir auf page table 0 verweisen lassen
    mov     eax, page_dir
    mov     ebx, page_table0 ; temp page dir entry
    or      bl, 0x3          ; r/w und p bits
    mov     [eax], ebx

    ; page table 0 erzeugen
    mov     ecx, 1023 ; Achtung, macht die 0 nicht mit (gewollt!)
pte_setup:
    mov     ebx, page_table0
    mov     eax, ecx    ; aktueller zaehler
    shl     eax, 2      ; mit 4 multiplizieren
    add     ebx, eax    ; zu basisadresse hinzuaddieren

    shl     eax, 10     ; mit 1024 multiplizieren
    or      al, 0x3     ; r/w und p bits
    mov     [ebx], eax  ; ab ins pt damit

    loop    pte_setup 

; page 0 start - hilft vllt bei Fehlersuche, wenn Page 0 doch mal drin sein soll
    ; mov     ebx, page_table0
    ; mov     eax, ecx    ; aktueller zaehler
    ; shl     eax, 2      ; mit 4 multiplizieren
    ; add     ebx, eax    ; zu basisadresse hinzuaddieren

    ; shl     eax, 10     ; mit 1024 multiplizieren
    ; or      al, 0x3     ; r/w und p bits
    ; mov     [ebx], eax  ; ab ins pt damit
; page 0 end

; paging anschalten
    mov     ebx, page_dir
    mov     cr3, ebx
    ; mov     ebx, cr0
    mov     eax, 0x80000001
    mov     cr0, eax
; Aufruf des C-Codes

	call	call_ctors		; Konstruktoren globaler Objekte ausfuehren
	call	main		; C/C++ Level System
	call	call_dtors		; Destruktoren globaler Objekte aufrufen
	hlt

; Default Interrupt Behandlung

; Spezifischer Kopf der Unterbrechungsbehandlungsroutinen

%macro wrapper 1
wrapper_%1:
	push	eax
	mov	al,%1
	jmp	wrapper_body
%endmacro

; ... wird automatisch erzeugt.
%assign i 0
%rep 256
wrapper i
%assign i i+1
%endrep

; Gemeinsamer Rumpf
wrapper_body:
	cld			; das erwartet der gcc so.
	push	ecx		; Sichern der fluechtigen Register
	push	edx
	and	eax,0xff	; Der generierte Wrapper liefert nur 8 Bits
	push	eax		; Nummer der Unterbrechung uebergeben
	call	guardian	; XXX noch nicht benoetigt fuer auf1!
	add	esp,4		; Parameter vom Stack entfernen
	pop	edx		; fluechtige Register wieder herstellen
	pop	ecx
	pop	eax
	iret			; fertig!

;
; setup_idt
;
; Relokation der Eintraege in der IDT und Setzen des IDTR

setup_idt:
	mov	eax,wrapper_0	; ax: niederwertige 16 Bit
	mov	ebx,eax
	shr	ebx,16		; bx: hoeherwertige 16 Bit
	mov	ecx,256		; Zaehler
.loop:	add	[idt+8*ecx+0],ax
	adc	[idt+8*ecx+6],bx
	dec	ecx
	jge	.loop

	lidt	[idt_descr]
	ret

;
; reprogram_pics
;
; Neuprogrammierung der PICs (Programmierbare Interrupt-Controller), damit
; alle 15 Hardware-Interrupts nacheinander in der idt liegen.

reprogram_pics:
	mov	al,0x11
	out	0x20,al
	call	delay
	out	0xa0,al
	call	delay
	mov	al,0x20
	out	0x21,al
	call	delay
	mov	al,0x28
	out	0xa1,al
	call	delay
	mov	al,0x04
	out	0x21,al
	call	delay
	mov	al,0x02
	out	0xa1,al
	call	delay
	mov	al,0x01
	out	0x21,al
	call	delay
	out	0xa1,al
	call	delay

	mov	al,0xff		; Hardware-Interrupts durch PICs
	out	0xa1,al		; ausmaskieren. Nur der Interrupt 2,
	call	delay		; der der Kaskadierung der beiden
	mov	al,0xfb		; PICs dient, ist erlaubt.
	out	0x21,al

	ret

; delay
;
; Kurze Verzoegerung fuer in/out Befehle.

delay:
	jmp	.L2
.L2:	ret

; Die Funktion wird beim abarbeiten der globalen Konstruktoren aufgerufen
; (unter Linux). Das Label muss definiert sein (fuer den Linker). Die
; Funktion selbst kann aber leer sein, da bei StuBs keine Freigabe des
; Speichers erfolgen muss.

__pure_virtual:
__cxa_pure_virtual:
__builtin_delete:
_ZdlPv:
__cxa_atexit:
_alloca:
        ret

[SECTION .data]

;  'interrupt descriptor table' mit 256 Eintraegen.

idt:

%macro idt_entry 1
	dw	(wrapper_%1 - wrapper_0) & 0xffff
	dw	0x0008
	dw	0x8e00
	dw	((wrapper_%1 - wrapper_0) & 0xffff0000) >> 16
%endmacro

; ... wird automatisch erzeugt.

%assign i 0
%rep 256
idt_entry i
%assign i i+1
%endrep

idt_descr:
	dw	256*8-1		; idt enthaelt 256 Eintraege
	dd	idt

page_fault_handler: ; gibt Fehlermeldung und die Adresse, an der es geknallt hat, aus
    xor     eax, eax        ; eax nullen
    mov     edi, 0xb8000    ; start video ram
    add     edi, 0xf00      ; unten links
    mov     ebx, page_fault_string
.print_string:
    cld                     ; stosw soll inkrementieren
    mov     al, [ebx]       ; Anfang vom String
    mov     ah, 0x0f        ; Format fuer Screen
    stosw                   ; ausgeben
    cmp     al, 0           ; Ende vom String erreicht?
    je     .print_end
    inc     ebx             ; naechstes Zeichen
    jmp     .print_string
.print_end:
    mov     ecx, cr2        ; Adresse noch ausgeben

    add     edi, 16         ; Platz fuer max. 8 Zeichen schaffen
    mov     eax, ecx
.print_pointer: ; bekommt Pointer in ecx, VideoRam Position in edi
    std                     ; stosw soll dekrementieren
    mov     ebx, 16         ; Divisor
    xor     edx, edx        ; wichtig vor Division!
    div     ebx             ; Rest landet in edx
    mov     ebx, lookup_table ; char dazu suchen
    add     ebx, edx     
    mov     edx, eax        ; Ergebnis von div sichern
    mov     al, [ebx]       
    mov     ah, 0x0f
    stosw                   ; ausgeben
    mov     eax, edx        ; Ergebnis wieder herstellen
    cmp     eax, 0
    jne     .print_pointer

    ; noch 0x davor schreiben, damit es schick aussieht
    mov     al, 'x'
    mov     ah, 0x0f
    stosw
    mov     al, '0'
    mov     ah, 0x0f
    stosw

    ; und CPU anhalten
    hlt

[SECTION .data]

page_fault_string:
    db      "Panic! PageFault at address: ",  0, 0
lookup_table:
    db      "0123456789abcdef", 0, 0
gdt:
    dw 0,0,0,0	; Null Descriptor
.code:
	dw 0xFFFF
    	dw 0x0000
    	dw 0x9A00
    	dw 0x00CF

.data:
    	dw 0xFFFF
    	dw 0x0000
    	dw 0x9200
    	dw 0x00CF


.pointer: 
    dw $-gdt-1
    dd gdt

idt_48:
	dw	0		; idt limit=0
	dw	0,0		; idt base=0L
;   Stack und interrupt descriptor table im BSS Bereich

;   Stack und interrupt descriptor table im BSS Bereich

[SECTION .bss]

init_stack:
	resb	4096

[SECTION .paging]
page_dir:
    resb    4096 ; alles mit 0 fuellen - page dir
page_table0:
    resb    4096 ; alles mit 0 fuellen - page table 0
