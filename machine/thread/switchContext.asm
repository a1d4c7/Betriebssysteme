%include "../machine/csym.inc"	; Innerhalb des Include-Files 'csym.inc'
				; wird das Macro CSYM(name) definiert,
				; das dem uebergebenen Symbolnamen in
				; Abhaegigkeit vom verwendeten Generierungs-
				; system einen Unterstrich ('_') voranstellt.

; EXPORTIERTE FUNKTIONEN

csym switchContext	

[GLOBAL switchContext]

; IMPLEMENTIERUNG DER FUNKTIONEN

[SECTION .text]

; switchContext: Der Coroutinenwechsel
;
; C-Prototyp:
;
;     void switchContext (void*& from, void*& to);
;


;stack:
;	to  			<-- ebp + 12
;	from			<-- ebp + 8
;	return adresse
;	ebp				<-- ebp 
;	ebx	
;	esi 
;	edi		      	<-- esp

switchContext:
	;fuegt hier Euren Code ein!

	;register sichern
	push ebp

	mov ebp, esp 		;ebp setzen fuer verwendung 

	push ebx
	push esi
	push edi



	;------------------
	
	mov eax, [ebp + 8]	;adresse von "from" in "eax" schreiben
	mov [eax], esp 		;in "from" "esp" sichern

	mov eax, [ebp + 12]	;adresse von "to" in "eax" schreiben
	mov esp, [eax] 		;"to" in "esp" schreiben

	;------------------

	;register wiederherstellen

	pop edi
	pop esi
	pop ebx
	pop ebp


	;------------------

	ret		; Ruecksprung zum Aufrufer