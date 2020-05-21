; compilar con  :  nasm -felf64 main.asm
;		   ld main.o -o play
;		   
; ejecutar  con ./play



%define NUMERO_FLOAT -1446.1982


%include 'matlib.asm'

;----------------------------------------

global _start


section .data

	numero_float dd NUMERO_FLOAT
  salto_de_linea dd 10

section .bss

	cadena_float resb 35     ; acá va a ir el float pasado a cadena (ASCII)
	
section .text

_start:

	push rbp
	mov rbp, rsp
	sub rsp, 128    ; No estoy usando el stack frame pero lo dejo así para evitar
                  ; que alguien me contrate por esto ("si no está roto no lo arregles...")
                  ;    ... ("y menos por 128 bytes").
	
	mov rcx, numero_float   
	mov rdx, cadena_float
	call Float_a_Cadena
	
.mostramos_numero:

;___Muestro el número contando a mano los caracteres necesarios (luego implemento esto para que sea automático)

	mov rax, 1
	mov rdi, 1
	mov rsi, cadena_float
	mov rdx, 11+1 				; (por el null final)
	syscall
  
  mov rax, 1
  mov rdi, 1
  mov rsi, salto_de_linea     ; eramos tan pobres...
  mov rdx, 1
  syscall
	
	
;___Reseteo la pila y me voy



	xor rax, rax
	mov rsp, rbp
	pop rbp
	xor rcx, rcx
	xor rax, rax
	
	mov rax, 60
	mov rdi, 0
	syscall         ; nos bimo


