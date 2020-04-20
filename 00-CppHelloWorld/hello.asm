
;--- INICIO DEL PROGRAMA ---
; compilar con "nasm -felf64 main.asm" y luego "ld main.o -o play"
; y luego arrancar con ./play   (puede que necesite "sudo ./play")

global _start 
                 
section .data    


  mensaje db 'Hola!', 10,'este es un programa en C++', 10,'Chau!',10, 0     
  
  
section .text      

_start:            

    mov rax, mensaje    
    call nuestro_cout
    
;___Una vez desplegado el mensaje, cerramos el programa

    mov rax, 60
    mov rdi, 0
    syscall
  
;-- FUNCIONES -------------------------  

nuestro_cout: 

  xor rdx, rdx   ; Limpio el rdx, donde contaré la cantidad de caracteres de la cadena
  push rax       ; Me guardo el valor de la dirección de "mensaje" en la pila
  
  ;Ahora a contar los caracteres de la cadena.
   
.loop1:

  inc rdx         ; Incremento el rdx en una unidad
  
  cmp byte [rax], 0    ; El valor que está en la posición es igual a cero ? (fin de la cadena)
  je .continuar        ; si lo es, saltá a .continuar. 
  
  inc rax         ; Incremento la dirección de mensaje en una unidad, lo que hará que me posicione
                  ; en el siguiente caracter.
  
  jmp .loop1
  
  
.continuar:
 
  pop rsi        ; necesitamos que la dirección de "mensaje" esté en rsi. Así lo pide este syscall
  mov rax, 1     ; rax = 1  implica que se va a usar el syscall llamado SYS_WRITE, para escribir
  mov rdi, 1     ; con rdi = 1  se usará la salida estándar
                 ; en rdx está el argumento que indica la cantidad de caracteres a imprimir (ya lo calculamos)
  syscall 
  
  
  ret             
  
  ;--- FIN DEL PROGRAMA ---
