;--------------------------------------------------------------------
;
;	¡Atención! solo para uso en Windows o Linux (64 bits) y uso con Netwide 
;	Assembler (NASM).
;
; Nota: Tengo que probar si es portable con Linux (creo que sí porque veo que
; no usé nada de la WINAPI.
;
;	Autor: Fernando Gustavo Riganti
;	Email: fernando.riganti@mgail.com
;
;
;	MANUAL DE USO:
;       --------------
;_______[Float_a_Cadena]  
;
;	¿Qué hace? Cargás un float de precisión simple (32 bits) y la cadena
;	donde lo querés transformar. 
;
;
;_______[Funcion_Piso]  ; DE MOMENTO SOLO PARA NUMEROS POSITIVOS!!
;
;	¿Qué hace? Cargás un float de precisión simple (32 bits) y te devuelve 
;       un entero en RAX pero redondeado hacia el número menor.
;	Ej:  si el float es 3.94, te devuelve 3
;	     si el float es -3.94, te devuelve -4  (NO IMPLEMENTADO AUN PARA NEGATIVOS)
;
;	Simplemente hay que poner la etiqueta del float en RCX (NO el float en sí)
;
;_______[Cargar_BigInt]
;
;	¿Qué hace? Carga un "Big Integer" POSITIVO en la etiqueta que se le especifique.
;	 
;	Cargar en RCX la etiqueta de la memoria donde se cargarán los números y luego
;	cargar en la pila dichas partes (un push por cada parte, en el orden natural). 
;	Luego cargar al final en la pila la cantidad de partes que se ingresaron (MUY IMPORTANTE)
;
;	Por ejemplo, si quiero cargar el número 234788 en tres partes, puedo hacer:
;
;		mov rcx, numero      ; la etiqueta
;		push 23		     ; primera parte 
;		push 4		     ; segunda parte
;		push 788  	     ; tercera parte
;		push 3               ; cantidad de partes (¡no olvidarse de esto!)	
;		call Cargar_BigInt
;
;	El espacio reservado bajo la etiqueta debe ser el siguiente: un "QWord" para
;	la cantidad de partes en las cuales se va a dividir el número y tantos qwords
;	como partes tenga el número  (cuidado si se va a a almacenar un resultado de no
;	exceder la memoria usada (en ese orden).
;
;	El número quedará de esta forma:
;
;	[cantidad de partes (8 bytes)][número menos significativo]...[número más significativo]
;	
;	NOTA: Sé que se puede usar un solo byte para cargar la cantidad de 
;	partes pero lo dejé así para mayor comodidad. Más adelante declaro una 
;	estructura y de paso ponemos signo.
;
;
;_______[BigInt_a_Cadena]
;
;	Poner en RCX la dirección del número y en RDX la dirección de la cadena 
;
;	Falta hacer la parte del negativo, esto requiere que rearme la estructura
;	La otra es mejorar el algoritmo cosa de poner el número derecho de entrada
;
;--------------------------------------------------------------------


section .text

;--------------------------------------------------------------------	

Funcion_Piso:


	push rbp	;
	mov rbp, rsp	;  Seteo mi partecita de pila
	sub rsp, 32+8 	;  32 bytes de shadowspace + 8 de argumentos
	

	fld dword [rcx]  	    ; Cargo el float
	fistp dword [rsp + 4 * 8]   ; Paso el número a entero


	fild dword [rsp + 4 * 8]    ; Cargo el mismo entero y el float
	fld dword [rcx]

	fsub st1		    ; Al float le resto el entero
	fldz			    ; Cargo el cero para comparar y ver si dio negativo
				    ; st0 = 0  ;  st1 : (float - int)  ; st2 = int

	fcomi st0, st1 		       ; comparo 0 con la resta 
	jbe .no_corregir_redondeo      ; Si el cero es menor (resultado positivo) o igual, salta
				       ; y no corrige nada porque ya tenés la función piso hecha.

	;Aclaración!  se usa jb y ja, no usar jl y jg porque se ve que los eflags que setea el fcomi
	;son para usar con los saltos sin signo


.corregir_redondeo:

	fstp st0  ;limpio todo  (prefiero asegurar legibilidad)
	fstp st0  
	fstp st0  

	fld1	 			; Cargo el número 1 para restar
	fild dword [rsp + 4 * 8]    	; st0 = int  ; st1 = 1 
	fsub st1			; Resto 1 y listo
	fistp dword [rsp + 4 * 8]       ; Guardo el nuevo entero

	fstp st0  			; limpio estooooy	
	
	jmp .redondeo_correcto		

.no_corregir_redondeo:

	fstp st0  ;limpio todo
	fstp st0  
	fstp st0  

.redondeo_correcto:

	mov rax, [rsp + 4 * 8]		; Meto el resultado en RAX
	
	mov rsp, rbp			; 
	pop rbp				; Desarmo la sección de pila que armé

	ret

;--------------------------------------------------------------------


; hacer eso del carry. Quizás no es necesario si especificás que el
; entero debe valer menos de 4.000.000.000.000.000 por trozo. Me parece
; que así es mejor porque evitás que se pasen y pisen la memoria
; de al lado.


Cargar_BigInt:

	pop rax
	pop r8            ; saco la cantidad de trozos y la 
	mov [rcx], r8     ; meto en la primera parte del número
	add rcx, 8
	 
.loop1:

	pop r10
	mov [rcx], r10
	add rcx, 8 
	dec r8
	cmp r8, 0
	jne .loop1
	push rax
	ret

;--------------------------------------------------------------------

BigInt_a_Cadena:

; POSIBLE BUG: la cadena auxiliar debería ser limpiada en cada loop1
; porque puede que cada trozo tenga números diferentes. Tal vez no haga falta, ojo, estudiarlo


;Explicación breve del algoritmo:  Tomo el primer trozo del Big Integer (el último de la estructura), 
;lo convierto a cadena y lo imprimo, y luego continúo con el siguiente. Con la información que trae el
;BigInt sobre la cantidad de trozos puedo determinar cuándo frenar el loop.


	push rbp
	mov rbp, rsp 
	sub rsp, 32+224 ;        32 de shadow + el resto para la cadena auxiliar 

	%define BigInt_a_Cadena.cadena_auxiliar  rbp - 224   

	push rbx  ;
	push r12  ;
	push r13  ; Me guardo los registros (estos no son volátiles, el resto se asume que se pierden)


	mov r12, rdx    ; Guardo la dirección de la cadena en r12

	mov r10, [rcx]  ; Me guardo la cantidad de trozos en r10  (primer trozo = cantidades)
	inc r10		; Incremento la cantidad de trozos en 1, porque en la cantidad no se incluye el primer trozo 
	mov rax, 8      ; Multiplico por 8 (bytes) por la cantidad de trozos, así leo de adelante para atrás
	xor rdx, rdx
	mul r10		; El final del BigInt es "(cantidad de trozos + 1) * 8" 
	add rcx, rax    ; Coloco el resultado en rcx, así puedo leer todo desde el final de la memoria hacia el principio 
 	mov r8, 10	; Puse este número porque más adelante voy a tener que divir por 10


;_______Este loop1 va ir yendo de trozo en trozo (del BigInt) para imprimir cada uno, desde el último al primero
;	ya que ese es el orden real del número 

	
.loop1:

	lea r9, [REL BigInt_a_Cadena.cadena_auxiliar]   
	sub rcx, 8					; Resto 8 para colocarme en el inicio del trozo a imprimir
	mov rax, [rcx]  			        ; Guardo el contenido del bigint


;_______Hasta acá tengo el trozo del BigInt que voy a imprimir en RAX, el loop2 
;	y el loop3 son los encargados de imprimir el número. 
;	El loop2 sirve ir dividiendo el número y cargar los restos en una cadena
;	auxiliar (en pila). Esto me va a dar el número en ASCII, pero al revés
;	(si adentro estaba el 123, voy a tener en ASCII el 321)

	
.loop2:

	xor rdx, rdx	   ; Limpio para almacenar acá el resto (si no está limpio no lo almacena)
	div r8             ; Cargo el 10 que voy a usar para dividir
	add dl, 48	   ; Sumo 48 al número para transformar al ASCII
	mov [r9], dl	   ; Lo paso a la cadena auxiliar
	inc r9		   ; Avanzo una posición en la cadena auxiliar
	cmp rax, 0	   ; Si el resultado de las divisiones es 0, es que terminé (me voy del loop)
	jne .loop2	   ;  y sino, repito el loop2.
	xor rbx, rbx	   

;_______Fin del loop2. Ahora tengo en la cadena auxiliar el número al revés. Lo vuelco al derecho
;	con el loop3.

.loop3: 

	dec r9 			; retrocedo una posición en la cadena auxiliar
	mov bl, [r9]		; Paso su contenido a BL (es un byte)
	mov [r12], bl                   
	inc r12		        ; Avanzo en la cadena final

	lea r13, [REL BigInt_a_Cadena.cadena_auxiliar]  ; cargo la dirección original de la cadena auxiliar
	cmp r9, r13 					; Comparo la dirección que estoy manejando de la cadena auxiliar
	jne .loop3					;   con el inicio de la misma. Si es igual es porque terminé, y sino
							;   sigo con el loop3

;_______Fin del loop3. Ahora vemos si repetimos el loop1 (es decir, todo lo anterior)
;	para eso, 


	dec r10      ; Resto 1 a la cantidad de trozos
	cmp r10, 1   ; Comparo con el 1 (anteultimo trozo), porque si comparo con el cero 
	jne .loop1   ;  estaría imprimiendo también el trozo que contiene la cantidad de trozos

;_______Fin del loop1. Terminamos de volcar todo a la cadena.


	mov byte [r12], 0   ; Finalizo la cadena con un cero para poder imprimirse.


	%undef BigInt_a_Cadena.cadena_auxiliar       ; Borro la etiqueta de la pila


	; Perdón por usar tanto los registros y que sea todo confuso pero es más rápido
	;  pero supuestamente con los registros va todo más rápido! Espero que se entienda 
	;  el algoritmo.


	push r13 ;
	push r12 ;
	push rbx ; Con esto cargo los registros guardados que no son volatiles

	mov rsp, rbp
	pop rbp		; Restauro la pila como estaba antes
	
	ret		; Nos bimo


;--------------------------------------------------------------------


; Va en rcx el número y en rdx la etiqueta de la cadena


; Puede que el problema esté en los defines y eso, o puede que esté al llamar la función_piso
; revisar igual todo el algoritmo a ver si tiene sentido con las nuevas definiciones.


Float_a_Cadena:

	push rbp
	mov rbp, rsp
	sub rsp, 32+97+15      ; 32 de shadowspace + 97 en variables que voy a meter (aun no lo implementé)
				; + 15 para alinear a múltiplo de 16


%define Float_a_Cadena.numero_float 			rbp - 97		 ; 4 bytes
%define Float_a_Cadena.float_flags_viejos 		rbp - 93	         ; 2 bytes
%define Float_a_Cadena.float_near 			rbp - 91		 ; 2 bytes
%define Float_a_Cadena.float_down 			rbp - 89		 ; 2 bytes
%define Float_a_Cadena.float_up 			rbp - 87		 ; 2 bytes
%define Float_a_Cadena.float_zero 			rbp - 85 		 ; 2 bytes
%define Float_a_Cadena.base_10 				rbp - 83	         ; 4 bytes
%define Float_a_Cadena.cadena_auxiliar 			rbp - 79  	         ; 35 bytes
%define Float_a_Cadena.parte_entera 			rbp - 44   	   	 ; 8 bytes
%define Float_a_Cadena.piso_RxB 			rbp - 36		 ; 8 bytes
%define Float_a_Cadena.unidad_int 			rbp - 28	 	 ; 4 bytes
%define Float_a_Cadena.unidad_float 			rbp - 24	 	 ; 4 bytes 
%define Float_a_Cadena.parte_fraccionaria_float 	rbp - 20                 ; 4 bytes
%define Float_a_Cadena.parte_fraccionaria_int 		rbp - 12	         ; 8 bytes
%define Float_a_Cadena.M_float 				rbp - 4			 ; 4 bytes


		
	mov eax, 0x41200000    				; Este es el 10.0 en float 32-bits
	mov [Float_a_Cadena.base_10], eax
	mov r12, rdx 		    ; Meto la dirección de la cadena acá, porque es más cómodo
	
	mov eax, [rcx]
	and eax, 10000000000000000000000000000000b ;  Si no había signo, eso debe valer todo cero
	cmp eax, 0
	je .positivo
	jmp .negativo

.positivo:
	
	mov byte [r12], '+'
	jmp .fin_if_signo

.negativo:
		
	mov byte [r12], '-'

.fin_if_signo:

	inc r12
	
	mov eax, [rcx]
	and eax, 01111111111111111111111111111111b  ; le quito el signo así, a lo Sandokan
	mov [Float_a_Cadena.numero_float], eax	    ;  y lo guardo como valor absoluto	
	

	xor rdx, rdx		    ;   Limpio registros (este es super necesario para las multip.)
	xor rcx,rcx
	xor rax,rax

	
;_______Primero hago los preparativos  (corregir: no es necesario porque solo necesito que 
;	redondee bien)


	fstcw [Float_a_Cadena.float_flags_viejos]
	mov ax, [Float_a_Cadena.float_flags_viejos]
	and ah, 11110011b
	or [Float_a_Cadena.float_near], ax
	or [Float_a_Cadena.float_down], ax
	or [Float_a_Cadena.float_up], ax
	or [Float_a_Cadena.float_zero], ax	

	xor r8, r8
	xor rax,rax  		    ; Limpio registros



	
;_______Cargo la parte entera

	fld dword [Float_a_Cadena.numero_float]
	fstp dword [Float_a_Cadena.parte_fraccionaria_float]
	
	
	lea rcx, [REL Float_a_Cadena.parte_fraccionaria_float]


	call Funcion_Piso


	mov [Float_a_Cadena.parte_entera], rax
	xor rax, rax
	
	mov eax, [Float_a_Cadena.parte_entera]




;_______Paso el entero a la cadena
		
	xor rdx, rdx
	mov rbx, 10
	lea r8, [REL Float_a_Cadena.cadena_auxiliar]
	
	
	
.loop:

	div rbx
	add dl, 48
	mov [r8], dl
	xor rdx, rdx
	inc r8
	cmp rax, 0
	jne .loop
	xor rbx, rbx

.loop2: 

	dec r8
	mov bl, [r8]
	mov [r12], bl
	inc r12
	lea rax, [REL Float_a_Cadena.cadena_auxiliar]   ;;;;;;; se está usando RAX aca?
	cmp r8, rax
	jne .loop2


;_______Ahora agrego la coma 


	mov al, ','  		    ; Le pongo una coma de antemano.
	mov [r12], al  



;_______Ahora tocaría el turno de imprimir la parte decimal. Pero antes
;	necesito cargar la parte decimal del float en parte_fraccionaria_float

	lea rcx, [REL Float_a_Cadena.parte_fraccionaria_float]
	call Funcion_Piso         ; lo uso para obtener la parte entera 
	mov [Float_a_Cadena.parte_fraccionaria_int], rax
	
	
	fldcw word [Float_a_Cadena.float_near]   ; Seteo el FPU a redondeo normal


	fild dword [Float_a_Cadena.parte_fraccionaria_int] 
	fld dword [Float_a_Cadena.parte_fraccionaria_float]


	fsub st1                   				 ; Restandole la parte entera al float, tengo la parte decimal
	fstp dword [Float_a_Cadena.parte_fraccionaria_float]	 ; El parte_fraccionaria_float ahora está en el intervalo [0,1)
	fstp st0	


;_______Listo, los preparativos están hechos. Ahora entro al loop del Dragon2 

  
	mov r9, 0   ; mi contador, porque aun no implementé el M verificador de error


.loop3:

	
	inc r9
	inc r12


;_______Hago que unidad_int sea igual a piso(parte_fraccionaria_float x base_10)


	fld dword [Float_a_Cadena.parte_fraccionaria_float]
	fld dword [Float_a_Cadena.base_10]
	fmul st1              			  ; st0 = parte_fraccionaria_float x base_10 ; st1 = parte_fraccionaria_float


	fstp dword [Float_a_Cadena.unidad_float]     ; Tengo RxB en unidad_float, ahora quiero hacerle la función piso
	fstp st0

	lea rcx, [REL Float_a_Cadena.unidad_float]
	call Funcion_Piso
	mov [Float_a_Cadena.unidad_int], al         ; Listo! debería ser un dígito porque le estoy haciendo piso a 
						    ; un número menor a 10



;_______Hago que parte_fraccionaria_float = (parte_fraccionaria_float x Base10) - piso(parte_fraccionaria_float x Base_10) 
;	ya sé que puedo aprovechar los cálculos pero prefiero hacerlo así
;	para tener más legibilidad.


	fld dword [Float_a_Cadena.parte_fraccionaria_float]
	fld dword [Float_a_Cadena.base_10]
	fmul st1               ; st0 = parte_fraccionaria_float x 10

	fst dword [Float_a_Cadena.piso_RxB]    ; piso_RxB = parte_fraccionaria_float x 10
	fstp dword [Float_a_Cadena.parte_fraccionaria_float]    ; parte_fraccionaria_float = parte_fraccionaria_float x 10
	fstp st0		 

	lea rcx, [REL Float_a_Cadena.piso_RxB]
	call Funcion_Piso
	mov [Float_a_Cadena.piso_RxB], rax
		

	fild dword [Float_a_Cadena.piso_RxB]
	fld dword [Float_a_Cadena.parte_fraccionaria_float]
	fsub st1

	fstp dword [Float_a_Cadena.parte_fraccionaria_float]
	fstp st0
	
	
;:::	;falta el control de M y 1-M!!!!!  así no imprime decimales de más



	xor r10, r10
	mov r10b, [Float_a_Cadena.unidad_int]     
	add r10b, 48
	mov [r12], r10b
	
	cmp r9, 4           ; 4 es la cantidad de decimales que muestra  (númerito mágico)
	jne .loop3 

		
	inc r12
	mov byte [r12], 0   ; cierro la cadena

	fldcw [Float_a_Cadena.float_flags_viejos] 	

	xor rax, rax   ; Restauro pila
	mov rsp, rbp
	pop rbp

%undef Float_a_Cadena.numero_float 			
%undef Float_a_Cadena.float_flags_viejos 		
%undef Float_a_Cadena.float_near 			
%undef Float_a_Cadena.float_down 			
%undef Float_a_Cadena.float_up 			
%undef Float_a_Cadena.float_zero 			
%undef Float_a_Cadena.base_10 				
%undef Float_a_Cadena.cadena_auxiliar 			
%undef Float_a_Cadena.parte_entera 			
%undef Float_a_Cadena.piso_RxB 			
%undef Float_a_Cadena.unidad_int 			
%undef Float_a_Cadena.unidad_float 			 
%undef Float_a_Cadena.parte_fraccionaria_float 	
%undef Float_a_Cadena.parte_fraccionaria_int 		
%undef Float_a_Cadena.M_float 				



	ret		; nos bimo


;--------------------------------------------------------------------


