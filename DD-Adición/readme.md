# Adición

## Etapa \#1

* Analisis del problema

Nuestro objetivo es sumar dos números enteros. Segun el diagrama de IPO, para su procesamiento debemos tener
espacio y tiempo. 

COLOCAR DIAGRAMA

Como se tratará de una operación sencilla, no se discutirá el tema del tiempo pero sí lo
haremos con el espacio: nuestro procesador nos obliga a colocar en memoria todo lo que se procesa (incluyendo
los mensajes que luego irán a la salida).

Para los mensajes de salida que usaremos en esta aplicación, en C++ no necesitaremos declarar variables (más allá de que internamente sí hay un almacenamiento en memoria de todas las cadenas). Sin embargo, sí debemos reservar espacio
para los números:

Paso 1: Reservar "numero1", "numero2", "resultado" de tipo entero (BCD , 32 bits)

FALTA TERMINAR



## Versión en NASM

En este trabajo práctico se incluye el código en C++ de un algoritmo simple en donde se suman 
dos valores. En la carpeta ASM incluyo el código que contiene la versión en lenguaje ensamblador
(seguimos con Netwide Assembler bajo Linux x64) y además una librería de funciones que
voy a ir ampliando. La librería tiene:


* ASMLIB_Cout  : Nuestro intento por copiar el std::cout

* ASMLIB_Cin   : Idem para std::cin

* ASMLIB_Entero_a_Cadena : Para convertir un número entero positivo a cadena

* ASMLIB_Cadena_a_Entero: Para convertir a entero una cadena de caracteres numéricos finalizada en 0


Lo nuevo de este código es la inclusión de funciones que representan la entrada de datos, y nos encontramos
con la tarea de convertir datos que representan cadenas (arreglo de datos tipo "char") con datos que 
representan "números" (datos tipo "int" o "enteros"). Este tipo de conversión como se puede ver no es muy 
compleja ya que prácticamente debemos convertir caracter por caracter, en formato ASCII, al valor que la
máquina reconoce y puede operar como número. Si nos fijamos en una tabla de código ASCII, veremos que
con restarle el número 48 a cada caracter se lo convertirá en número, y sumándole 48 pasaríamos de 
número a caracter.

Sin embargo vemos que en el código en C++ no se necesitó en ningún momento que hagamos esta conversión. El 
"std::cin" hizo esta conversión por nosotros o detectó el tipo de dato?  Es posible que internamente se esté
haciendo uso de "templates" donde para cada tipo de dato tendremos diferentes métodos en cout que indiquen
cómo comportarse en cada caso. Nuestro código fallará si hubiesemos declarado la variable numero1 como "char\[\]" 
por lo que bajo esta evidencia podríamos deducir que no se hacen conversiones de datos.


NOTA: Es importante aclarar que no pretendo (y de hecho sería bastante desacertado) decir que reproduje la misma 
funcionalidad del std::cin y el std::cout  en assembler, pero trataremos de acercarnos lo más que podamos).





