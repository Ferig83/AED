## Tipos de Datos:  Assembler

Como mencioné en el Readme de la parte de C++, podríamos decir que no hay muchos tipos de datos definidos para lenguaje
ensamblador. No es que no existan los tipos de datos, sino que no están concretamente definidos. Podemos reservar memoria y 
asignarles etiquetas, meter en pila y demás tantos bytes como podamos. Sin embargo para los números de coma flotante usaremos
registros e instrucciones especiales del procesador (pueden hacerse con los registros normales como se hacía antaño pero es
tedioso).

Lo que sí se puede considerar es que cada vez que reservamos un espacio en memoria, usamos tamaños como:

BYTE  (1 byte)
WORD  (2 bytes)
DWORD (4 bytes)
QWORD (8 bytes)
TWORD (10 bytes)

Estos tamaños están predefinidos en NASM, y además también contamos con la posibilidad de hacer estructuras. 

### Impresión de Números FLOAT (32 bits):

Estoy implementando una especie de "biblioteca" (sin compilar en objeto) para imprimir cadenas, enteros, floats de 
precisión simple y  enteros grandes (big integers). Aun queda mucho por hacer pero servirá para mostrar la impresión de una
cadena, un entero grande y un float. De momento voy a mostrar simplemente la impresión de un float de precisión simple, pero
el objetivo es mejorar esa biblioteca, incluir la parte de cadenas de caracteres y agregar las operaciones de Big Integers.



