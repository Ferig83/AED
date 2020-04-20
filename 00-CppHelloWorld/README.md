# Hola, Mundo!  
## (pero más difícil)

En este documento voy a explicar cada detalle que pueda del "Hola, Mundo!". Como ya tengo algo de experiencia usando C++ y me 
apasionan muchísimo los lenguajes ensambladores, me es de mucho interés aprovechar esta cursada para analizar cómo 
se compilaría el código en lenguaje ensamblador. Vamos a usar NASM (Netwide Assembler) para explicar cada parte del código.  
Y aclaro que se programará para procesadores de 64 bits.

IMPORTANTE! No voy a "desensamblar" el código generado por el compilador. Simplemente estoy analizando cómo se podría
implementar.


Si bien podemos programar para Windows en NASM, dependeríamos mucho de las librerías dinámicas (las famosas WINAPI32) ya que
prácticamente estamos forzados a utilizarlas en este sistema operativo (los valores de los syscalls cambian  en cada versión 
de Windows, probablemente con el objetivo de evitar que se usen mal). Por lo tanto vamos a programar en Linux que mantiene 
constante los números de las syscall. Aclaro también que no conozco el alcance de la cursada de AED por lo que probablemente
lo anterior esté sujeto a cambios.

Aclarado todo, empezamos! Primero vamos a mostrar el código en C++ 


#include <iostream>   

	int main() {
		std::cout << "Hola!\neste es un programa en C++\nChau!\n";
	}
  

La versión en ensamblador puede ser un poco más extensa si utilizamos el concepto de clases, objetos 
y sobrecarga de operadores (de hecho, actualmente no tengo idea de cómo implementar objetos en assembler).
Por lo que vamos a evitar "pasar a assembler" el std::cout y vamos a implementar la misma funcionalidad 
en lenguaje ensamblador (que es la de imprimir una cadena de caracteres). De paso podemos hacer la comparación 
y ver un poco cómo creo/imagino que funcionaría cada instrucción de C++  (dicen que C es como assembler con muchas
macros... veremos cuántas!)

El código en assembler es el siguiente. El codigo igual está en hello.asm (sin los comentarios), pero lo siguiente
se puede hacer un copy/paste y compilar.

;--- INICIO DEL PROGRAMA ---
; compilar con "nasm -felf64 main.asm" y luego "ld main.o -o play"
; y luego arrancar con ./play   (puede que necesite "sudo ./play")

global _start     ; Sabemos que el main() es la función que se ejecuta primero. Las funciones
                  ; no serían más que "posiciones" determinadas en el código. Ponemos "_start" 
                  ; en reemplazo a la palabra "main".

                 
section .data    

; Podría decirse que acá iría la declaración de variables globales. En assembler no tenemos 
; "variables" propiamente dichas, sino direcciones de memoria donde están los datos (bueno, la 
; verdad es que es así sea en assembler o en cualquier lenguaje!).


  mensaje db 'Hola!', 10,'este es un programa en C++', 10,'Chau!',10, 0     ;bueno, no... no es en C++ ahora!
  

; Aclaro que el valor 10 corresponde al salto de linea que en C++ usamos como "\n" 


; Lo que podemos observar es que en nuestro código en C++ no vemos declaraciones de variables. 
; Sin embargo, sí o sí necesitamos que la cadena que se va a imprimir esté primero en la memoria, 
; por lo que podemos deducir que al crearse "cout" habrá una variable que guarde la cadena. También vamos
; a necesitar la longitud en caracteres de la cadena (incluyendo el caracter nulo que da por
; terminada la misma, y los saltos de línea), por lo que COUT seguro tendrá una función que cuente estos 
; caracteres (y la vamos a implementar).

  
section .text       ; Acá comienzan las instrucciones que no impliquen declaración de "variables"

_start:             ; Este es nuestro "main()", la posición donde empiezan las instrucciones
                    ; de nuestro programa.

;___Llamamos a la función "nuestro_cout", pasándole como argumento la dirección de memoria
;   que tiene el mensaje.
    
    mov rax, mensaje    
    call nuestro_cout
    
;___Una vez desplegado el mensaje, cerramos el programa

    mov rax, 60
    mov rdi, 0
    syscall
  
  
;Y ahora, la implementación de nuestro_cout!

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
  
  
  ret             ; Finaliza la función y volvemos donde fue llamada
  
  ;--- FIN DEL PROGRAMA ---
  
  
  NOTAS!  no creamos lo que se llamaría el stack frame y utilizamos solo los registros, pero lo vamos a hacer a partir
  de la siguiente lección para de paso explicar los "scope" y empezar a utilizar las variables "locales". 
 
  Calculo también que en no muchos días tendremos que imprimir un float. Y eso será complicado, lo sé (tengo implementado
  ya el Dragon2 de Steele y White, ya que el algoritmo de Dragon4 no lo entiendo).
  
  Y el int de "int main"? bueno, eso es algo que quedará en el registro rax que es el valor que suelen retornar 
  los syscall. Como acá no lo estoy recuperando, nos olvidamos de esa parte. Lo mismo con #include ya que no estamos
  usando bibliotecas  ( se pueden llamar en NASM con "extern" o %include para llamar a los encabezados).
  
  También se pudo llamar a funciones como printf desde el assembler, pero creo que no tendría sentido el no implementar
  nuestras propias funciones de salida y de hecho es por esto que lo estoy haciendo en Linux (igual el SO está entre mi
  aplicación y el hardware así que tampoco estoy inventando funcionalidades nuevas más de las que me provee el SO)
  
  
  
  
   
  
 















