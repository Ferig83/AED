global _start


%include 'asmlib.asm'

%define ENDL 10
%define NULL 0



;--- BSS ------------------------------------------------------------

section .bss

	numero_1_cadena resb 25
	numero_2_cadena resb 25
	numero_1_int resq 1
	numero_2_int resq 1
	resultado_cadena resb 25


;--- DATA -----------------------------------------------------------

section .data

	mensaje_entrada1 db 'Ingrese el primer numero:',ENDL,'>',NULL
	mensaje_entrada2 db 'Ingrese el segundo numero:',ENDL,'>',NULL
	mensaje_resultado db 'El resultado es : ',NULL
	salto_linea db ENDL, NULL        


;--- TEXT -----------------------------------------------------------

section .text



_start:


	mov rax, salto_linea            ; Salto de línea, así se ve mejor
	call ASMLIB_Cout


;_______Se pide ingresar el primer numero

	mov rax, mensaje_entrada1 
	call ASMLIB_Cout

	mov rax, numero_1_cadena
	call ASMLIB_Cin
	
;_______Lo paso a entero

	mov rax, numero_1_cadena
	call ASMLIB_Cadena_a_Entero
	mov [numero_1_int], rax


;_______Se pide ingresar el segundo numero
	
	mov rax, mensaje_entrada2
	call ASMLIB_Cout
	
	mov rax, numero_2_cadena
	call ASMLIB_Cin

;_______Lo paso a entero también

	mov rax, numero_2_cadena
	call ASMLIB_Cadena_a_Entero
	mov [numero_2_int], rax
	

;_______Hago las sumas

	mov rax, [numero_1_int]
	mov rbx, [numero_2_int]
	add rbx, rax                   
	

;_______Muestro los resultados

	push rbx
	
	mov rax, mensaje_resultado
	call ASMLIB_Cout

	pop rax
	mov rdi, resultado_cadena
	call ASMLIB_Entero_a_Cadena

	
	mov rax, resultado_cadena
	call ASMLIB_Cout

	mov rax, salto_linea            ; Doble salto de línea
	call ASMLIB_Cout	
        mov rax, salto_linea
	call ASMLIB_Cout	
	
;_______Finalizo

	mov rax, 60
	mov rdi, 0
	syscall      ; nos bimo
	
	
	








