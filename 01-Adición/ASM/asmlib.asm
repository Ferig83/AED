; Estas son funciones que se van a ir creando
; para usar en la cursada de Algoritmos y Estructura
; de Datos. Todas las funciones tienen el prefijo "ASMLIB_"

; Los argumentos van en este orden
;
; 1) rax
; 2) rdi
; 3) rsi
; 4) rdx
; 5 en adelante) pila      
;
; IMPORTANTE: 
; rax, rdi, rsi, rdx , r10, r8 y r9  los voy a considerar volátiles, es decir
; No voy a garantizar que conserven su valor. Esto está sujeto a cambios 



%define SYS_READ 0
%define SYS_WRITE 1


;---------------------------------------------------------------------
; FUNCIONES	 
;---------------------------------------------------------------------


ASMLIB_Cout:            ; Parametros:   RAX: puntero a cadena a imprimir


	xor rdx, rdx   ; En RDX voy a contar los caracteres de la cadena
	push rax       ; Me guardo el valor de la dirección de "mensaje" en la pila
  

;_______Ahora a contar los caracteres de la cadena:
;	Por cada loop voy a ir chequeando caracter a caracter hasta toparme con el 
;	cero (caracter nulo), que representa la terminación de la cadena. Por cada
;	vuelta sumo rdx una unidad así cuento cuantos caracteres tiene.


.loop1:   


  	inc rdx                
  
  	cmp byte [rax], 0    ; El valor que está en la posición es igual a cero ? 
 	je .continuar1       ; si lo es, saltá a ".continuar" 
  
  	inc rax        		; Incremento la dirección de mensaje en una unidad, lo que hará que me posicione
           		        ; en el siguiente caracter.
  
  	jmp .loop1
  
  
.continuar1:
 
  	pop rsi                ; necesitamos que la dirección de "mensaje" esté en rsi. Así lo pide este syscall. La 
			       ; sacamos de la pila (al principio la pusheamos)
 
 	mov rax, SYS_WRITE     
  	mov rdi, 1             ; con rdi = 1  se usará la salida estándar
                               ; en rdx está el argumento que indica la cantidad de caracteres a imprimir (ya lo calculamos)
  	syscall 
  

  
  	ret             
  



;---------------------------------------------------------------------  

ASMLIB_Cin:    ; Parámetros:   RAX:puntero a variable de entrada 



	mov r8, rax	       	; Me guardo lo que hay en rax, porque como voy a multiplicar necesito este registro

	push rbp                ; Configuro una sección de la pila para uso y posterior descarte 
	mov rbp, rsp	       
 	sub rsp, 64             ; Expandible a mássss, 64 bytes de momento 
	

;_______Primero voy a limpiar la parte de la pila que me armé, lo cual simplemente
;	muevo la dirección de la base de la pila en rcx y voy llenando de ceros
;	posición a posición hasta encontrarme con el puntero de pila RSP

		
	mov rcx, rbp

.loop1:

	mov byte [rcx], 0
	cmp rcx, rsp
	je .continuar1
	dec rcx
	jmp .loop1
	
.continuar1:



;_______Ahora voy a volcar el contenido de sys_read en la pila

	mov rsi, rsp
	mov rax, SYS_READ
	mov rdi, 0          ; rdi = 0  sería la entrada estandar
	mov rdx, 63         ; Dejo un byte fuera por las dudas         
	syscall

	
;_______Ahora voy a volcar lo de la pila a la variable destino, simplemente
;	es ir recorriendo la pila e ir volcando los bytes en la variable
;	(recordar que el puntero es r8)
		

.loop2:

	cmp byte [rsp], 10    ; Recordar que el último caracter es el salto de línea
	je .continuar2        ; por lo que voy a usarlo para saber hasta donde debo parar

	mov dl, [rsp]
	mov [r8], dl
	inc rsp
	inc r8

	jmp .loop2
	
.continuar2:

	mov byte [r8], 0     ; Sello la cadena con un cero

 	mov rsp, rbp         ; Desarmamos la pila
  	pop rbp

 
  	ret
  

;---------------------------------------------------------------------


ASMLIB_Cadena_a_Entero:    ; Parámetros:  RAX: puntero a cadena // Devuelve en RAX el número


	push rbx
	push rdx

	mov rbx, rax
	xor rdx, rdx
	xor r8,r8
;	mov r9, 10             ;;TODO; BORRAR    
	xor r10,r10
	
.loop1:

;_______Este loop cumple tres cosas: 1) Chequeo si solo se metieron numeros y no 
;	otros caracteres 2) Cuento la cantidad de dígitos en R10 para el loop2
;	en donde tengo que multiplicar cada dígito por su peso (1,10,100,1000.. etc)
;       3) Pone el puntero en RBX en posición para ir desde las unidades en adelante

	; Comparo si la cadena terminó   
 
	cmp byte [rbx], 0      
	je .continuar1

	; Si terminó, termina el loop. De paso, veo si alguno de los
	; caracteres no corresponde a un número (pueden ingresar letras o símbolos)
	; Como son caracteres, me baso en que 48 = '0'  y  57 = '9'  ambos en ASCII

	cmp byte [rbx], 48
	jb .error1             ; Si es menor a 48, ese caracter no es un número. Chau
	
	cmp byte [rbx], 57     ; Si es mayor a 57, ese caracter no es un número. Chau
	ja .error1
 
	inc r10
	inc rbx

	
	jmp .loop1



.continuar1:

 
;_______Ahora en rdx tengo la cantidad de dígitos. Como dijimos vamos a usarlos
;	para multiplicar cada cifra por su peso correspondiente

	
	mov rcx, 1      ; iniciamos el peso de las unidades
	xor rax, rax   



.loop2:

    
	cmp r10, 0            ; Llegamos terminar con todos los digitos?
	je .continuar2        ; Si llegamos, salimos del loop

	dec rbx		      ; Vamos desde las unidades hacia arriba
	xor rax, rax
	mov al, [rbx]
	sub al, 48            ; Le resto 48 para convertir de ASCII a número
	mul rcx               ; Multiplicamos el peso correspondiente
	
	add r8, rax           ; Vamos metiendo las sumas en r8
	
	mov rax, rcx          ; Con este procedimiento subo un nivel el peso
	mov rcx, 10           ; (unidades a decenas, decenas a centenas, etc)
	
	mul rcx
	mov rcx, rax
	
	dec r10               ; Un digito menos
	

	jmp .loop2



.continuar2:
	
	mov rax, r8
	pop rdx
	pop rbx

	ret


;Errores!

.error1:  ;  Si no es un número, devuelvo el cero

	
	mov rax, 0  
	pop rdx
	pop rbx
	ret

;--------------------------------------------------------------------

ASMLIB_Entero_a_Cadena:    ; Parametros (RAX : Entero (el numero, no el puntero); RDI : puntero a cadena)

	
	
	push rax

	push rbp            ; Seteo mi porción de pila
	mov rbp, rsp
	sub rsp, 32         ; Creo que los int de 64 bits no llegan a 25 digitos igual, pero lo mantengo multiplo de 16

	mov byte [rsp], 0
	inc rsp


;_______El primer loop simplemente recupera los restos de ir dividiendo por 10
;       



.loop1:

	
	xor rdx, rdx
	mov rcx, 10
	div rcx

	add dl, 48
	mov [rsp], dl
	inc rsp
	xor rdx, rdx
		
	cmp rax, 0
	jne .loop1
	


.loop2:

	dec rsp	
	mov al, [rsp]  
	mov [rdi], al
	inc rdi
	cmp byte [rsp], 0
	jne .loop2
		

	mov rsp, rbp
	pop rbp


	pop rax
	ret


	
;--------------------------------------------------------------------	
	
	

	
	





  
  
  
  
  
  
  
  
