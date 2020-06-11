; Definimos los años con estas bellas macros
    
  %define YEAR1 2000
  %define YEAR2 2004
  %define YEAR3 1990
  %define YEAR4 1992   
  %define YEAR5 2020
  %define YEAR6 1900



global _start


section .data

        error_assert db 'ERROR!', 10, 0
	
section .text

_start:

	push rbp
	mov rbp, rsp
	sub rsp, 32     ; Lo hago porque no quiero perder la costumbre
	
  
  ;Probamos cada añito. 
  
	mov rcx, YEAR1   
	call _IsBisiesto                
	call _pseudo_assert_true

	mov rcx, YEAR2
	call _IsBisiesto
	call _pseudo_assert_true

	
	mov rcx, YEAR3
	call _IsBisiesto
	call _pseudo_assert_false


	mov rcx, YEAR4
	call _IsBisiesto
	call _pseudo_assert_true


	mov rcx, YEAR5
	call _IsBisiesto
	call _pseudo_assert_true

	mov rcx, YEAR6
	call _IsBisiesto
	call _pseudo_assert_false


; Desarmamos la pila y cerramos 

	xor rax, rax
	mov rsp, rbp
	pop rbp
	
	mov rax, 60
	mov rdi, 0
	syscall      


;--- FUNCIONES--------------------------------------------------

;Este mini-assert compara por igual a "true"

_pseudo_assert_true:

	cmp al, 1
	je .todo_ok
	
	mov rax, 1
	mov rdi, 1
	mov rsi, error_assert
	mov rdx, 8
	syscall
	
	mov rax, 60
	mov rdi, -1
	syscall

.todo_ok:

	ret

;--------------------

;Y este otro mini-assert compara por igual a "false"

_pseudo_assert_false:

	cmp al, 0
	je .todo_ok
	mov rax, 1
	mov rdi, 1
	mov rsi, error_assert
	mov rdx, 8
	syscall
	
	mov rax, 60
	mov rdi, -1
	syscall
	

.todo_ok:
	ret


;-------------------

;La función estrella: IsBisiesto. Recibe un entero y devuelve un booleano

_IsBisiesto:

;_______Empezamos por "p". Movemos el valor a RAX y lo dividimos por 4 
;	(limpiamos RDX ya que, si está limpio, ahí se guardará el resto)

	mov rax, rcx
	xor rdx, rdx
	mov rbx, 4
	div rbx

;_______Comparo si rdx es igual a cero y paso el Zero Flag a r8b  
;	("sete" sería "Set if Equal", pero sabemos que CMP hace una resta y ve si el 
;	resultado da cero así que prácticamente estamos pasando el Zero Flag)

	cmp rdx, 0
	sete r8b

;______Ahora vamos a hacer lo mismo con "q". Vamos a colocarlo en r9b

	mov rax, rcx
	xor rdx, rdx
	mov rbx, 100
	div rbx

	cmp rdx, 0
	sete r9b

;_______Por último vamos con "r". Lo colocamos en r10b.

	mov rax, rcx
	xor rdx, rdx
	mov rbx, 400
	div rbx
	
	cmp rdx, 0
	sete r10b

;_______Ahora vamos a emplear el bonito árbol de operaciones que nos hizo hacer
;	el profesor. Debemos hacer p ^ ((q ^ r) v !q). 

	xor rax, rax  ; soy un tipo precavido
	mov al, r9b   
	and al, r10b
	not r9b
	or al, r9b
	and al, r8b   

;_______Listo, nuestro trabajo aquí ha terminado

	ret
